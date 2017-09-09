/* chrts1.c
 * Input file:  charts1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "chrts1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Chart_drawing, Qchart_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_pen_x, Qchart_pen_x);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_pen_y, Qchart_pen_y);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_pen_color, Qchart_pen_color);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_pen_color_value, Qchart_pen_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_really_drawing, Qchart_really_drawing);

DEFINE_VARIABLE_WITH_SYMBOL(Current_chart_raster_color_value, Qcurrent_chart_raster_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_current_raster_is_polychrome_p, Qchart_current_raster_is_polychrome_p);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_current_raster_is_monochrome_raster_list_p, Qchart_current_raster_is_monochrome_raster_list_p);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_color_value_for_this_raster, Qchart_color_value_for_this_raster);

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

/* CHART-PEN-COLOR */
Object chart_pen_color(color)
    Object color;
{
    x_note_fn_call(177,0);
    if ( !EQL(Chart_pen_color,color)) {
	Chart_pen_color = color;
	if (Chart_really_drawing) {
	    if (EQ(color,Qbackground))
		Chart_pen_color_value = Current_background_color_value;
	    else if (EQ(color,Qforeground) || EQ(color,Qworkspace_foreground))
		Chart_pen_color_value = Current_foreground_color_value;
	    else if (EQ(color,Qtransparent))
		Chart_pen_color_value = Current_background_color_value;
	    else
		Chart_pen_color_value = map_to_color_value(color);
	    if (Chart_current_raster_is_monochrome_raster_list_p || 
		    Chart_current_raster_is_polychrome_p)
		Chart_color_value_for_this_raster = Chart_pen_color_value;
	    else if (FIXNUM_EQ(Current_chart_raster_color_value,
		    Chart_pen_color_value))
		Chart_color_value_for_this_raster = FIX((SI_Long)1L);
	    else
		Chart_color_value_for_this_raster = FIX((SI_Long)0L);
	    return VALUES_1(Chart_color_value_for_this_raster);
	}
	else {
	    Chart_pen_color_value = FIX((SI_Long)0L);
	    return VALUES_1(Chart_pen_color_value);
	}
    }
    else
	return VALUES_1(Nil);
}

/* CHART-MOVE-TO */
Object chart_move_to(x,y)
    Object x, y;
{
    x_note_fn_call(177,1);
    Chart_pen_x = x;
    Chart_pen_y = y;
    return VALUES_1(Chart_pen_y);
}

/* CHART-LINE-TO */
Object chart_line_to(x,y)
    Object x, y;
{
    SI_Long temp, temp_1, temp_2, temp_3;

    x_note_fn_call(177,2);
    temp = IFIX(Chart_pen_x);
    temp = MIN(temp,(SI_Long)65534L);
    temp_1 = IFIX(Chart_pen_y);
    temp_1 = MIN(temp_1,(SI_Long)65534L);
    temp_2 = MIN(IFIX(x),(SI_Long)65534L);
    temp_3 = MIN(IFIX(y),(SI_Long)65534L);
    paint_line_in_current_scratchpad_raster(FIX(MAX((SI_Long)-65534L,
	    temp)),FIX(MAX((SI_Long)-65534L,temp_1)),
	    FIX(MAX((SI_Long)-65534L,temp_2)),FIX(MAX((SI_Long)-65534L,
	    temp_3)),Chart_color_value_for_this_raster,T);
    Chart_pen_x = x;
    Chart_pen_y = y;
    return VALUES_1(Chart_pen_y);
}

/* CHART-MOVE */
Object chart_move(dx,dy)
    Object dx, dy;
{
    x_note_fn_call(177,3);
    return chart_move_to(FIXNUM_ADD(Chart_pen_x,dx),FIXNUM_ADD(Chart_pen_y,
	    dy));
}

/* CHART-LINE */
Object chart_line(dx,dy)
    Object dx, dy;
{
    x_note_fn_call(177,4);
    return chart_line_to(FIXNUM_ADD(Chart_pen_x,dx),FIXNUM_ADD(Chart_pen_y,
	    dy));
}

/* CHART-FILL-RECTANGLE */
Object chart_fill_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    SI_Long temp, temp_1, temp_2, temp_3;

    x_note_fn_call(177,5);
    if (FIXNUM_EQ(top,bottom))
	bottom = FIXNUM_ADD1(top);
    if (FIXNUM_EQ(left,right))
	right = FIXNUM_ADD1(left);
    temp = MIN(IFIX(left),(SI_Long)65534L);
    temp_1 = MIN(IFIX(top),(SI_Long)65534L);
    temp_2 = MIN(IFIX(right),(SI_Long)65534L);
    temp_3 = MIN(IFIX(bottom),(SI_Long)65534L);
    return paint_solid_rectangle_in_current_scratchpad_raster(FIX(MAX((SI_Long)-65534L,
	    temp)),FIX(MAX((SI_Long)-65534L,temp_1)),
	    FIX(MAX((SI_Long)-65534L,temp_2)),FIX(MAX((SI_Long)-65534L,
	    temp_3)),Chart_color_value_for_this_raster);
}

/* CHART-FRAME-RECTANGLE */
Object chart_frame_rectangle(left,top,right,bottom)
    Object left, top, right, bottom;
{
    x_note_fn_call(177,6);
    right = FIXNUM_SUB1(right);
    bottom = FIXNUM_SUB1(bottom);
    if (FIXNUM_EQ(top,bottom))
	bottom = FIXNUM_ADD1(top);
    if (FIXNUM_EQ(left,right))
	right = FIXNUM_ADD1(left);
    chart_move_to(left,top);
    chart_line_to(right,top);
    chart_line_to(right,bottom);
    chart_line_to(left,bottom);
    return chart_line_to(left,top);
}

/* CHART-TEXT-WIDTH */
Object chart_text_width(text_string)
    Object text_string;
{
    Object font_map, word_spacing, scale, value;
    SI_Long unshifted_result;

    x_note_fn_call(177,7);
    font_map = ISVREF(Current_text_box_format,(SI_Long)22L);
    word_spacing = ISVREF(Current_text_box_format,(SI_Long)34L);
    scale = Current_image_x_scale;
    value = compute_width_of_text_line(5,text_string,Nil,Nil,font_map,
	    word_spacing);
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

/* COMPUTE-BOUNDING-RECTANGLE-OF-TEXT */
Object compute_bounding_rectangle_of_text(text)
    Object text;
{
    Object text_cell_line_height, text_cell_baseline_position, scale, value;
    Object temp, temp_1, temp_2;
    SI_Long unshifted_result;

    x_note_fn_call(177,8);
    text_cell_line_height = ISVREF(Current_text_box_format,(SI_Long)31L);
    text_cell_baseline_position = ISVREF(Current_text_box_format,(SI_Long)32L);
    scale = Current_image_y_scale;
    value = FIXNUM_NEGATE(text_cell_line_height);
    if (IFIX(scale) == (SI_Long)4096L)
	temp = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(scale,value);
    temp_1 = chart_text_width(text);
    scale = Current_image_y_scale;
    value = FIXNUM_MINUS(text_cell_line_height,text_cell_baseline_position);
    if (IFIX(scale) == (SI_Long)4096L)
	temp_2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp_2 = scalef_function(scale,value);
    return VALUES_4(FIX((SI_Long)0L),temp,temp_1,temp_2);
}

/* CHART-DRAW-TEXT */
Object chart_draw_text(text_string)
    Object text_string;
{
    Object text_cell_font_map, word_spacing, chart_pen_color_1;
    Object chart_pen_color_value, chart_color_value_for_this_raster, left, top;
    Object right, bottom, incff_1_arg;
    Declare_special(3);
    Object result;

    x_note_fn_call(177,9);
    text_cell_font_map = ISVREF(Current_text_box_format,(SI_Long)22L);
    word_spacing = ISVREF(Current_text_box_format,(SI_Long)34L);
    chart_pen_color_1 = Nil;
    chart_pen_color_value = Nil;
    chart_color_value_for_this_raster = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Chart_color_value_for_this_raster,Qchart_color_value_for_this_raster,chart_color_value_for_this_raster,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color_value,Qchart_pen_color_value,chart_pen_color_value,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color,Qchart_pen_color,chart_pen_color_1,
		0);
	  chart_pen_color(ISVREF(Current_text_box_format,(SI_Long)23L));
	  result = compute_bounding_rectangle_of_text(text_string);
	  MVS_4(result,left,top,right,bottom);
	  incff_1_arg = Chart_pen_x;
	  left = FIXNUM_ADD(left,incff_1_arg);
	  incff_1_arg = Chart_pen_y;
	  top = FIXNUM_ADD(top,incff_1_arg);
	  incff_1_arg = Chart_pen_x;
	  right = FIXNUM_ADD(right,incff_1_arg);
	  incff_1_arg = Chart_pen_y;
	  bottom = FIXNUM_ADD(bottom,incff_1_arg);
	  result = paint_from_line_of_text_to_current_scratchpad_raster(left,
		  top,right,bottom,text_string,word_spacing,
		  text_cell_font_map,Chart_color_value_for_this_raster,
		  Current_image_x_scale,Current_image_y_scale,Chart_pen_x,
		  Chart_pen_y);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* RETRACT-FRAME-NOTES-FOR-BLOCK */
Object retract_frame_notes_for_block(block)
    Object block;
{
    x_note_fn_call(177,10);
    return VALUES_1(Nil);
}

/* ASSERT-FRAME-NOTES-FOR-BLOCK */
Object assert_frame_notes_for_block(block)
    Object block;
{
    x_note_fn_call(177,11);
    return VALUES_1(Nil);
}

/* MAKE-MANAGED-FLOAT-ARRAY-GENERATOR */
Object make_managed_float_array_generator(managed_float_array_generator_array,
	    managed_float_array_generator_next_element_index)
    Object managed_float_array_generator_array;
    Object managed_float_array_generator_next_element_index;
{
    x_note_fn_call(177,12);
    return slot_value_cons_function(managed_float_array_generator_array,
	    managed_float_array_generator_next_element_index);
}

/* MANAGED-FLOAT-ARRAY-GENERATOR-OPEN */
Object managed_float_array_generator_open(managed_float_array)
    Object managed_float_array;
{
    x_note_fn_call(177,13);
    return make_managed_float_array_generator(managed_float_array,
	    FIX((SI_Long)0L));
}

/* MANAGED-FLOAT-ARRAY-GENERATOR-NEXT-ELEMENT */
Object managed_float_array_generator_next_element(generator)
    Object generator;
{
    Object index_1, cdr_new_value;

    x_note_fn_call(177,14);
    index_1 = CDR(generator);
    cdr_new_value = FIXNUM_ADD1(index_1);
    M_CDR(generator) = cdr_new_value;
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(CAR(generator),
	    (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(index_1) & (SI_Long)1023L)));
}

/* MANAGED-FLOAT-ARRAY-GENERATOR-EOF */
Object managed_float_array_generator_eof(generator)
    Object generator;
{
    x_note_fn_call(177,15);
    return VALUES_1(FIXNUM_LE(ISVREF(CAR(generator),(SI_Long)1L),
	    CDR(generator)) ? T : Nil);
}

/* MANAGED-FLOAT-ARRAY-GENERATOR-CLOSE */
Object managed_float_array_generator_close(generator)
    Object generator;
{
    x_note_fn_call(177,16);
    return reclaim_slot_value_cons_1(generator);
}

/* INITIALIZE-THE-TRANSFORM */
Object initialize_the_transform()
{
    Object result_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(177,17);
    if (PUSH_AREA(Dynamic_area,0))
	result_1 = make_array(1,FIX((SI_Long)6L));
    POP_AREA(0);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	The_transform = result_1;
	indentity_transform_matrix();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(result_1);
}

static Object float_constant;      /* 1.0 */

static Object float_constant_1;    /* 0.0 */

/* INDENTITY-TRANSFORM-MATRIX */
Object indentity_transform_matrix()
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(177,18);
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)0L),float_constant);
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)1L),float_constant_1);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)2L),float_constant_1);
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)3L),float_constant);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)4L),float_constant_1);
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    svref_arg_1 = The_transform;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)5L),float_constant_1);
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value);
}

/* SCALE-TRANSFORM-MATRIX */
Object scale_transform_matrix(x_scale,y_scale)
    Object x_scale, y_scale;
{
    Object managed_number, a, b, c, d, svref_arg_1, svref_new_value;
    double temp, temp_1, store_managed_number_arg;

    x_note_fn_call(177,19);
    managed_number = ISVREF(The_transform,(SI_Long)0L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	a = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	a = aref1(managed_number,FIX((SI_Long)0L));
    else
	a = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)1L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	b = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	b = aref1(managed_number,FIX((SI_Long)0L));
    else
	b = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)2L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	c = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	c = aref1(managed_number,FIX((SI_Long)0L));
    else
	c = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)3L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	d = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	d = aref1(managed_number,FIX((SI_Long)0L));
    else
	d = managed_number;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(x_scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(a);
    store_managed_number_arg = temp * temp_1;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)0L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(x_scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(b);
    store_managed_number_arg = temp * temp_1;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)1L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(y_scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(c);
    store_managed_number_arg = temp * temp_1;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)2L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(y_scale);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(d);
    store_managed_number_arg = temp * temp_1;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)3L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value);
}

/* OFFSET-TRANSFORM-MATRIX */
Object offset_transform_matrix(x_offset,y_offset)
    Object x_offset, y_offset;
{
    Object managed_number, a, b, c, d, tx, ty, svref_arg_1, svref_new_value;
    double temp, temp_1, temp_2, temp_3, temp_4, store_managed_number_arg;

    x_note_fn_call(177,20);
    managed_number = ISVREF(The_transform,(SI_Long)0L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	a = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	a = aref1(managed_number,FIX((SI_Long)0L));
    else
	a = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)1L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	b = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	b = aref1(managed_number,FIX((SI_Long)0L));
    else
	b = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)2L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	c = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	c = aref1(managed_number,FIX((SI_Long)0L));
    else
	c = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)3L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	d = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	d = aref1(managed_number,FIX((SI_Long)0L));
    else
	d = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)4L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	tx = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	tx = aref1(managed_number,FIX((SI_Long)0L));
    else
	tx = managed_number;
    managed_number = ISVREF(The_transform,(SI_Long)5L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	ty = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	ty = aref1(managed_number,FIX((SI_Long)0L));
    else
	ty = managed_number;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(a);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x_offset);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(c);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y_offset);
    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(tx);
    store_managed_number_arg = temp * temp_1 + temp_2 * temp_3 + temp_4;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)4L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    svref_arg_1 = The_transform;
    temp = DOUBLE_FLOAT_TO_DOUBLE(b);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x_offset);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(d);
    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(y_offset);
    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(ty);
    store_managed_number_arg = temp * temp_1 + temp_2 * temp_3 + temp_4;
    svref_new_value = store_managed_number_function(ISVREF(svref_arg_1,
	    (SI_Long)5L),DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_arg));
    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value);
}

Object Chart_part_description_for_chart_style_prop = UNBOUND;

static Object Qchart_style;        /* chart-style */

static Object Qline_chart_style;   /* line-chart-style */

/* INITIALIZE-FOR-CHART */
Object initialize_for_chart(chart)
    Object chart;
{
    Object frame, sub_vector_qm, method_function_qm, svref_arg_1;
    Object gensymed_symbol, function_qm;
    SI_Long index_1, ab_loop_bind_, method_index;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,21);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)2L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
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
      if ( !TRUEP(ISVREF(Chart,(SI_Long)19L))) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(Chart,Qchart_style);
	  svref_arg_1 = Chart;
	  SVREF(svref_arg_1,FIX((SI_Long)19L)) = Qline_chart_style;
      }
      gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)2L) : FIX((SI_Long)0L);
      if (IFIX(gensymed_symbol) == (SI_Long)0L)
	  set_edges_of_block(Chart,FIX((SI_Long)0L),FIX((SI_Long)0L),
		  Default_chart_width,Default_chart_height);
      method_index = (SI_Long)33L;
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),method_index);
      function_qm = sub_vector_qm ? ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
      if (function_qm)
	  result = inline_funcall_1(function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qstandardize_text_size_feature_in_part_description;  /* standardize-text-size-feature-in-part-description */

static Object Qcomputed_annotations;  /* computed-annotations */

/* INITIALIZE-AFTER-READING-FOR-CHART */
Object initialize_after_reading_for_chart(chart)
    Object chart;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,22);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)4L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
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
      if ( !(IFIX(Kb_flags) >= (SI_Long)231L)) {
	  map_over_part_description(Qstandardize_text_size_feature_in_part_description,
		  ISVREF(Chart,(SI_Long)21L));
	  result = map_over_part_description(Qstandardize_text_size_feature_in_part_description,
		  get_lookup_slot_value_given_default(Chart,
		  Qcomputed_annotations,Nil));
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_chart_spot = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_chart_spots, Qchain_of_available_chart_spots);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_spot_count, Qchart_spot_count);

Object Chain_of_available_chart_spots_vector = UNBOUND;

/* CHART-SPOT-STRUCTURE-MEMORY-USAGE */
Object chart_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(177,23);
    temp = Chart_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CHART-SPOT-COUNT */
Object outstanding_chart_spot_count()
{
    Object def_structure_chart_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(177,24);
    gensymed_symbol = IFIX(Chart_spot_count);
    def_structure_chart_spot_variable = Chain_of_available_chart_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_chart_spot_variable))
	goto end_loop;
    def_structure_chart_spot_variable = 
	    ISVREF(def_structure_chart_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CHART-SPOT-1 */
Object reclaim_chart_spot_1(chart_spot)
    Object chart_spot;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(177,25);
    inline_note_reclaim_cons(chart_spot,Nil);
    structure_being_reclaimed = chart_spot;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_structure_if_any(ISVREF(chart_spot,(SI_Long)2L));
      SVREF(chart_spot,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_chart_spots_vector,
	    IFIX(Current_thread_index));
    SVREF(chart_spot,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_chart_spots_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = chart_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CHART-SPOT */
Object reclaim_structure_for_chart_spot(chart_spot)
    Object chart_spot;
{
    x_note_fn_call(177,26);
    return reclaim_chart_spot_1(chart_spot);
}

static Object Qg2_defstruct_structure_name_chart_spot_g2_struct;  /* g2-defstruct-structure-name::chart-spot-g2-struct */

/* MAKE-PERMANENT-CHART-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_chart_spot_structure_internal()
{
    Object def_structure_chart_spot_variable, defstruct_g2_chart_spot_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(177,27);
    def_structure_chart_spot_variable = Nil;
    atomic_incff_symval(Qchart_spot_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_chart_spot_variable = Nil;
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
	defstruct_g2_chart_spot_variable = the_array;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_chart_spot_g2_struct;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_chart_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_chart_spot_variable = defstruct_g2_chart_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_chart_spot_variable);
}

/* MAKE-CHART-SPOT-1 */
Object make_chart_spot_1()
{
    Object def_structure_chart_spot_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(177,28);
    def_structure_chart_spot_variable = 
	    ISVREF(Chain_of_available_chart_spots_vector,
	    IFIX(Current_thread_index));
    if (def_structure_chart_spot_variable) {
	svref_arg_1 = Chain_of_available_chart_spots_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_chart_spot_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_chart_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_chart_spot_g2_struct;
    }
    else
	def_structure_chart_spot_variable = 
		make_permanent_chart_spot_structure_internal();
    inline_note_allocate_cons(def_structure_chart_spot_variable,Nil);
    SVREF(def_structure_chart_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_chart_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_chart_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_chart_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_chart_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_chart_spot_variable);
}

/* GENERATE-SPOT-FOR-CHART */
Object generate_spot_for_chart(chart,mouse_pointer)
    Object chart, mouse_pointer;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(177,29);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      result = push_last_spot(mouse_pointer,make_chart_spot_1(),Chart);
    POP_SPECIAL();
    return result;
}

static Object Qchart_part_description_for_chart_style;  /* chart-part-description-for-chart-style */

static Object Qfix_up_color_feature_in_chart_part_description;  /* fix-up-color-feature-in-chart-part-description */

/* ASSURE-ALL-CHARTS-ARE-MODERN-1 */
Object assure_all_charts_are_modern_1()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, chart, gensymed_symbol;
    Object svref_arg_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,30);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    chart = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qchart);
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
	Chart = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	gensymed_symbol = ISVREF(Chart,(SI_Long)19L);
	if ( 
		!TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qchart_part_description_for_chart_style))) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(Chart,Qchart_style);
	    svref_arg_1 = Chart;
	    SVREF(svref_arg_1,FIX((SI_Long)19L)) = Qline_chart_style;
	}
	map_over_part_description(Qfix_up_color_feature_in_chart_part_description,
		ISVREF(Chart,(SI_Long)21L));
	map_over_part_description(Qfix_up_color_feature_in_chart_part_description,
		get_lookup_slot_value_given_default(Chart,
		Qcomputed_annotations,Nil));
	goto next_loop;
      end_loop_1:
	result = VALUES_1(Qnil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qcolor;              /* color */

static Object Qline_color;         /* line-color */

/* FIX-UP-COLOR-FEATURE-IN-CHART-PART-DESCRIPTION */
Object fix_up_color_feature_in_chart_part_description(part_description)
    Object part_description;
{
    Object p;

    x_note_fn_call(177,31);
    p = REST(part_description);
  next_loop:
    if ( !TRUEP(p))
	goto end_loop;
    if (EQ(Qcolor,CAR(p)))
	M_CAR(p) = Qline_color;
    p = CDDR(p);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CLEANUP-FOR-CHART */
Object cleanup_for_chart(chart)
    Object chart;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,32);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)1L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
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
      result = change_slot_value(3,Chart,Qdata_series,Nil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-LINE-DRAWING-DESCRIPTION-FOR-CHART-VALUE */
Object reclaim_line_drawing_description_for_chart_value(old_slot_value,
	    gensymed_symbol)
    Object old_slot_value, gensymed_symbol;
{
    x_note_fn_call(177,33);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Working_on_chart, Qworking_on_chart);

DEFINE_VARIABLE_WITH_SYMBOL(Current_chart_frame, Qcurrent_chart_frame);

/* REMOVE-GRAPH-RENDERING-FROM-CHART */
Object remove_graph_rendering_from_chart(graph_rendering,chart)
    Object graph_rendering, chart;
{
    Object svref_arg_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,34);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      svref_arg_1 = Chart;
      svref_new_value = delete_eval_element_1(graph_rendering,ISVREF(Chart,
	      (SI_Long)16L));
      result = VALUES_1(ISVREF(svref_arg_1,(SI_Long)16L) = svref_new_value);
    POP_SPECIAL();
    return result;
}

static Object Qwhite;              /* white */

/* GET-OR-MAKE-GRAPH-RENDERING-FOR-CHART */
Object get_or_make_graph_rendering_for_chart(chart)
    Object chart;
{
    Object current_chart_frame, graph_rendering, ab_loop_list_;
    Object gensymed_symbol, width_of_block_in_window;
    Object height_of_block_in_window, chart_colors_2;
    Object format_of_graph_rendering_structure, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, current_graph_rendering, svref_new_value;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, width_of_block;
    SI_Long height_of_block, unshifted_result;
    Declare_special(3);
    Object result;

    x_note_fn_call(177,35);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,2);
      current_chart_frame = Chart;
      PUSH_SPECIAL_WITH_SYMBOL(Current_chart_frame,Qcurrent_chart_frame,current_chart_frame,
	      1);
	graph_rendering = Nil;
	ab_loop_list_ = ISVREF(Chart,(SI_Long)16L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	graph_rendering = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (FIXNUM_EQ(Current_image_x_scale,ISVREF(graph_rendering,
		(SI_Long)3L)) && FIXNUM_EQ(Current_image_y_scale,
		ISVREF(graph_rendering,(SI_Long)4L)) && EQ(Current_window,
		ISVREF(graph_rendering,(SI_Long)17L))) {
	    result = VALUES_1(graph_rendering);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	width_of_block = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	height_of_block = gensymed_symbol_1 - gensymed_symbol_2;
	if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	    width_of_block_in_window = FIX(width_of_block);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
		Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		width_of_block && width_of_block < 
		IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(Current_image_x_scale) * 
		    width_of_block + (SI_Long)2048L;
	    width_of_block_in_window = FIX(unshifted_result >>  -  - 
		    (SI_Long)12L);
	}
	else
	    width_of_block_in_window = 
		    scalef_function(Current_image_x_scale,FIX(width_of_block));
	if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	    height_of_block_in_window = FIX(height_of_block);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
		Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < 
		height_of_block && height_of_block < 
		IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(Current_image_y_scale) * 
		    height_of_block + (SI_Long)2048L;
	    height_of_block_in_window = FIX(unshifted_result >>  -  - 
		    (SI_Long)12L);
	}
	else
	    height_of_block_in_window = 
		    scalef_function(Current_image_y_scale,
		    FIX(height_of_block));
	chart_colors_2 = chart_colors();
	format_of_graph_rendering_structure = 
		choose_format_for_graph_rendering(length(chart_colors_2));
	temp = ISVREF(Chart,(SI_Long)17L);
	temp_1 = Current_image_x_scale;
	temp_2 = Current_image_y_scale;
	temp_3 = Chart;
	temp_4 = Current_window;
	temp_5 = get_reference_to_item(Chart);
	graph_rendering = make_decacheable_graph_rendering(13,temp,
		format_of_graph_rendering_structure,temp_1,temp_2,
		FIX((SI_Long)0L),FIX(width_of_block),FIX(height_of_block),
		width_of_block_in_window,height_of_block_in_window,temp_3,
		temp_4,temp_5,FIXNUM_MAX(width_of_block_in_window,
		height_of_block_in_window));
	SVREF(graph_rendering,FIX((SI_Long)10L)) = chart_colors_2;
	if (EQ(Qwhite,Qbackground))
	    temp_6 = Current_background_color_value;
	else if (EQ(Qwhite,Qforeground) || EQ(Qwhite,Qworkspace_foreground))
	    temp_6 = Current_foreground_color_value;
	else if (EQ(Qwhite,Qtransparent))
	    temp_6 = Current_background_color_value;
	else
	    temp_6 = map_to_color_value(Qwhite);
	SVREF(graph_rendering,FIX((SI_Long)9L)) = temp_6;
	current_graph_rendering = graph_rendering;
	PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering,Qcurrent_graph_rendering,current_graph_rendering,
		0);
	  paint_graph_rendering_raster();
	POP_SPECIAL();
	temp_6 = Chart;
	svref_new_value = eval_cons_1(graph_rendering,ISVREF(Chart,
		(SI_Long)16L));
	ISVREF(temp_6,(SI_Long)16L) = svref_new_value;
	result = VALUES_1(graph_rendering);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Grid, Qgrid);

DEFINE_VARIABLE_WITH_SYMBOL(Current_grid, Qcurrent_grid);

DEFINE_VARIABLE_WITH_SYMBOL(Grid_color, Qgrid_color);

/* ENTER-PART-FEATURE-GRID-COLOR */
Object enter_part_feature_grid_color(new_value)
    Object new_value;
{
    x_note_fn_call(177,36);
    Part_feature_recall_stack = part_stack_cons_1(Grid_color,
	    Part_feature_recall_stack);
    Grid_color = new_value;
    return VALUES_1(Nil);
}

static Object Qpart_stack;         /* part-stack */

/* EXIT-PART-FEATURE-GRID-COLOR */
Object exit_part_feature_grid_color()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,37);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Grid_color = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Grid_visible, Qgrid_visible);

/* ENTER-PART-FEATURE-GRID-VISIBLE */
Object enter_part_feature_grid_visible(new_value)
    Object new_value;
{
    x_note_fn_call(177,38);
    Part_feature_recall_stack = part_stack_cons_1(Grid_visible,
	    Part_feature_recall_stack);
    Grid_visible = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-GRID-VISIBLE */
Object exit_part_feature_grid_visible()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,39);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Grid_visible = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_chart, Qcurrent_chart);

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_subparts, Qdata_series_subparts);

DEFINE_VARIABLE_WITH_SYMBOL(Chart_left, Qchart_left);

/* ENTER-PART-FEATURE-CHART-LEFT */
Object enter_part_feature_chart_left(new_value)
    Object new_value;
{
    x_note_fn_call(177,40);
    Part_feature_recall_stack = part_stack_cons_1(Chart_left,
	    Part_feature_recall_stack);
    Chart_left = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-LEFT */
Object exit_part_feature_chart_left()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,41);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_left = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_top, Qchart_top);

/* ENTER-PART-FEATURE-CHART-TOP */
Object enter_part_feature_chart_top(new_value)
    Object new_value;
{
    x_note_fn_call(177,42);
    Part_feature_recall_stack = part_stack_cons_1(Chart_top,
	    Part_feature_recall_stack);
    Chart_top = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TOP */
Object exit_part_feature_chart_top()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,43);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_top = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_right, Qchart_right);

/* ENTER-PART-FEATURE-CHART-RIGHT */
Object enter_part_feature_chart_right(new_value)
    Object new_value;
{
    x_note_fn_call(177,44);
    Part_feature_recall_stack = part_stack_cons_1(Chart_right,
	    Part_feature_recall_stack);
    Chart_right = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-RIGHT */
Object exit_part_feature_chart_right()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,45);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_right = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_bottom, Qchart_bottom);

/* ENTER-PART-FEATURE-CHART-BOTTOM */
Object enter_part_feature_chart_bottom(new_value)
    Object new_value;
{
    x_note_fn_call(177,46);
    Part_feature_recall_stack = part_stack_cons_1(Chart_bottom,
	    Part_feature_recall_stack);
    Chart_bottom = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-BOTTOM */
Object exit_part_feature_chart_bottom()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,47);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_bottom = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_right_margin, Qchart_right_margin);

/* ENTER-PART-FEATURE-CHART-RIGHT-MARGIN */
Object enter_part_feature_chart_right_margin(new_value)
    Object new_value;
{
    x_note_fn_call(177,48);
    Part_feature_recall_stack = part_stack_cons_1(Chart_right_margin,
	    Part_feature_recall_stack);
    Chart_right_margin = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-RIGHT-MARGIN */
Object exit_part_feature_chart_right_margin()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,49);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_right_margin = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_top_margin, Qchart_top_margin);

/* ENTER-PART-FEATURE-CHART-TOP-MARGIN */
Object enter_part_feature_chart_top_margin(new_value)
    Object new_value;
{
    x_note_fn_call(177,50);
    Part_feature_recall_stack = part_stack_cons_1(Chart_top_margin,
	    Part_feature_recall_stack);
    Chart_top_margin = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TOP-MARGIN */
Object exit_part_feature_chart_top_margin()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,51);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_top_margin = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_left_margin, Qchart_left_margin);

/* ENTER-PART-FEATURE-CHART-LEFT-MARGIN */
Object enter_part_feature_chart_left_margin(new_value)
    Object new_value;
{
    x_note_fn_call(177,52);
    Part_feature_recall_stack = part_stack_cons_1(Chart_left_margin,
	    Part_feature_recall_stack);
    Chart_left_margin = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-LEFT-MARGIN */
Object exit_part_feature_chart_left_margin()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,53);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_left_margin = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_bottom_margin, Qchart_bottom_margin);

/* ENTER-PART-FEATURE-CHART-BOTTOM-MARGIN */
Object enter_part_feature_chart_bottom_margin(new_value)
    Object new_value;
{
    x_note_fn_call(177,54);
    Part_feature_recall_stack = part_stack_cons_1(Chart_bottom_margin,
	    Part_feature_recall_stack);
    Chart_bottom_margin = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-BOTTOM-MARGIN */
Object exit_part_feature_chart_bottom_margin()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,55);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_bottom_margin = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_tuple_1_minimum, Qchart_tuple_1_minimum);

/* ENTER-PART-FEATURE-CHART-TUPLE-1-MINIMUM */
Object enter_part_feature_chart_tuple_1_minimum(new_value)
    Object new_value;
{
    x_note_fn_call(177,56);
    Part_feature_recall_stack = part_stack_cons_1(Chart_tuple_1_minimum,
	    Part_feature_recall_stack);
    Chart_tuple_1_minimum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TUPLE-1-MINIMUM */
Object exit_part_feature_chart_tuple_1_minimum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,57);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_tuple_1_minimum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_tuple_1_maximum, Qchart_tuple_1_maximum);

/* ENTER-PART-FEATURE-CHART-TUPLE-1-MAXIMUM */
Object enter_part_feature_chart_tuple_1_maximum(new_value)
    Object new_value;
{
    x_note_fn_call(177,58);
    Part_feature_recall_stack = part_stack_cons_1(Chart_tuple_1_maximum,
	    Part_feature_recall_stack);
    Chart_tuple_1_maximum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TUPLE-1-MAXIMUM */
Object exit_part_feature_chart_tuple_1_maximum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,59);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_tuple_1_maximum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_tuple_2_minimum, Qchart_tuple_2_minimum);

/* ENTER-PART-FEATURE-CHART-TUPLE-2-MINIMUM */
Object enter_part_feature_chart_tuple_2_minimum(new_value)
    Object new_value;
{
    x_note_fn_call(177,60);
    Part_feature_recall_stack = part_stack_cons_1(Chart_tuple_2_minimum,
	    Part_feature_recall_stack);
    Chart_tuple_2_minimum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TUPLE-2-MINIMUM */
Object exit_part_feature_chart_tuple_2_minimum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,61);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_tuple_2_minimum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_tuple_2_maximum, Qchart_tuple_2_maximum);

/* ENTER-PART-FEATURE-CHART-TUPLE-2-MAXIMUM */
Object enter_part_feature_chart_tuple_2_maximum(new_value)
    Object new_value;
{
    x_note_fn_call(177,62);
    Part_feature_recall_stack = part_stack_cons_1(Chart_tuple_2_maximum,
	    Part_feature_recall_stack);
    Chart_tuple_2_maximum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-TUPLE-2-MAXIMUM */
Object exit_part_feature_chart_tuple_2_maximum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,63);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_tuple_2_maximum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_origin_x, Qchart_origin_x);

/* ENTER-PART-FEATURE-CHART-ORIGIN-X */
Object enter_part_feature_chart_origin_x(new_value)
    Object new_value;
{
    x_note_fn_call(177,64);
    Part_feature_recall_stack = part_stack_cons_1(Chart_origin_x,
	    Part_feature_recall_stack);
    Chart_origin_x = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-ORIGIN-X */
Object exit_part_feature_chart_origin_x()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,65);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_origin_x = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_origin_y, Qchart_origin_y);

/* ENTER-PART-FEATURE-CHART-ORIGIN-Y */
Object enter_part_feature_chart_origin_y(new_value)
    Object new_value;
{
    x_note_fn_call(177,66);
    Part_feature_recall_stack = part_stack_cons_1(Chart_origin_y,
	    Part_feature_recall_stack);
    Chart_origin_y = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-CHART-ORIGIN-Y */
Object exit_part_feature_chart_origin_y()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,67);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Chart_origin_y = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series, Qdata_series);

DEFINE_VARIABLE_WITH_SYMBOL(Current_data_series, Qcurrent_data_series);

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_index, Qdata_series_index);

/* ENTER-PART-FEATURE-DATA-SERIES-INDEX */
Object enter_part_feature_data_series_index(new_value)
    Object new_value;
{
    x_note_fn_call(177,68);
    Part_feature_recall_stack = part_stack_cons_1(Data_series_index,
	    Part_feature_recall_stack);
    Data_series_index = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-INDEX */
Object exit_part_feature_data_series_index()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,69);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_index = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_source_kind, Qdata_series_source_kind);

/* ENTER-PART-FEATURE-DATA-SERIES-SOURCE-KIND */
Object enter_part_feature_data_series_source_kind(new_value)
    Object new_value;
{
    x_note_fn_call(177,70);
    Part_feature_recall_stack = part_stack_cons_1(Data_series_source_kind,
	    Part_feature_recall_stack);
    Data_series_source_kind = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-SOURCE-KIND */
Object exit_part_feature_data_series_source_kind()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,71);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_source_kind = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_info_1, Qdata_series_info_1);

/* ENTER-PART-FEATURE-DATA-SERIES-INFO-1 */
Object enter_part_feature_data_series_info_1(new_value)
    Object new_value;
{
    x_note_fn_call(177,72);
    Part_feature_recall_stack = part_stack_cons_1(Data_series_info_1,
	    Part_feature_recall_stack);
    Data_series_info_1 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-INFO-1 */
Object exit_part_feature_data_series_info_1()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,73);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_info_1 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_info_2, Qdata_series_info_2);

/* ENTER-PART-FEATURE-DATA-SERIES-INFO-2 */
Object enter_part_feature_data_series_info_2(new_value)
    Object new_value;
{
    x_note_fn_call(177,74);
    Part_feature_recall_stack = part_stack_cons_1(Data_series_info_2,
	    Part_feature_recall_stack);
    Data_series_info_2 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-INFO-2 */
Object exit_part_feature_data_series_info_2()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,75);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_info_2 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_failed_to_compile, Qdata_series_failed_to_compile);

/* ENTER-PART-FEATURE-DATA-SERIES-FAILED-TO-COMPILE */
Object enter_part_feature_data_series_failed_to_compile(new_value)
    Object new_value;
{
    x_note_fn_call(177,76);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_failed_to_compile,
	    Part_feature_recall_stack);
    Data_series_failed_to_compile = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-FAILED-TO-COMPILE */
Object exit_part_feature_data_series_failed_to_compile()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,77);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_failed_to_compile = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* MANAGED-FLOAT-ARRAY?-P */
Object managed_float_array_qm_p(x)
    Object x;
{
    Object temp;

    x_note_fn_call(177,78);
    temp =  !TRUEP(x) ? T : Nil;
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(x) ? (EQ(ISVREF(x,(SI_Long)0L),
		Managed_float_array_unique_marker) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_data_cache_1_qm, Qdata_series_data_cache_1_qm);

/* ENTER-PART-FEATURE-DATA-SERIES-DATA-CACHE-1? */
Object enter_part_feature_data_series_data_cache_1_qm(new_value)
    Object new_value;
{
    x_note_fn_call(177,79);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_data_cache_1_qm,
	    Part_feature_recall_stack);
    Data_series_data_cache_1_qm = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-DATA-CACHE-1? */
Object exit_part_feature_data_series_data_cache_1_qm()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,80);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_data_cache_1_qm = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_data_cache_2_qm, Qdata_series_data_cache_2_qm);

/* ENTER-PART-FEATURE-DATA-SERIES-DATA-CACHE-2? */
Object enter_part_feature_data_series_data_cache_2_qm(new_value)
    Object new_value;
{
    x_note_fn_call(177,81);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_data_cache_2_qm,
	    Part_feature_recall_stack);
    Data_series_data_cache_2_qm = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-DATA-CACHE-2? */
Object exit_part_feature_data_series_data_cache_2_qm()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,82);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_data_cache_2_qm = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_illustration_kind, Qdata_series_illustration_kind);

/* ENTER-PART-FEATURE-DATA-SERIES-ILLUSTRATION-KIND */
Object enter_part_feature_data_series_illustration_kind(new_value)
    Object new_value;
{
    x_note_fn_call(177,83);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_illustration_kind,
	    Part_feature_recall_stack);
    Data_series_illustration_kind = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-ILLUSTRATION-KIND */
Object exit_part_feature_data_series_illustration_kind()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,84);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_illustration_kind = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_generator_info_1, Qdata_series_generator_info_1);

/* ENTER-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-1 */
Object enter_part_feature_data_series_generator_info_1(new_value)
    Object new_value;
{
    x_note_fn_call(177,85);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_generator_info_1,
	    Part_feature_recall_stack);
    Data_series_generator_info_1 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-1 */
Object exit_part_feature_data_series_generator_info_1()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,86);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_generator_info_1 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_generator_info_2, Qdata_series_generator_info_2);

/* ENTER-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-2 */
Object enter_part_feature_data_series_generator_info_2(new_value)
    Object new_value;
{
    x_note_fn_call(177,87);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_generator_info_2,
	    Part_feature_recall_stack);
    Data_series_generator_info_2 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-2 */
Object exit_part_feature_data_series_generator_info_2()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,88);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_generator_info_2 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_series_connect_first_and_last_point, Qdata_series_connect_first_and_last_point);

/* ENTER-PART-FEATURE-DATA-SERIES-CONNECT-FIRST-AND-LAST-POINT */
Object enter_part_feature_data_series_connect_first_and_last_point(new_value)
    Object new_value;
{
    x_note_fn_call(177,89);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_series_connect_first_and_last_point,
	    Part_feature_recall_stack);
    Data_series_connect_first_and_last_point = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-SERIES-CONNECT-FIRST-AND-LAST-POINT */
Object exit_part_feature_data_series_connect_first_and_last_point()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,90);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_series_connect_first_and_last_point = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Chart_data_point, Qchart_data_point);

DEFINE_VARIABLE_WITH_SYMBOL(Current_chart_data_point, Qcurrent_chart_data_point);

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_index, Qdata_point_index);

/* ENTER-PART-FEATURE-DATA-POINT-INDEX */
Object enter_part_feature_data_point_index(new_value)
    Object new_value;
{
    x_note_fn_call(177,91);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_index,
	    Part_feature_recall_stack);
    Data_point_index = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-INDEX */
Object exit_part_feature_data_point_index()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,92);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_index = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_tuple_valid_qm, Qdata_point_tuple_valid_qm);

/* ENTER-PART-FEATURE-DATA-POINT-TUPLE-VALID? */
Object enter_part_feature_data_point_tuple_valid_qm(new_value)
    Object new_value;
{
    x_note_fn_call(177,93);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_point_tuple_valid_qm,
	    Part_feature_recall_stack);
    Data_point_tuple_valid_qm = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-TUPLE-VALID? */
Object exit_part_feature_data_point_tuple_valid_qm()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,94);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_tuple_valid_qm = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_tuple_1, Qdata_point_tuple_1);

/* ENTER-PART-FEATURE-DATA-POINT-TUPLE-1 */
Object enter_part_feature_data_point_tuple_1(new_value)
    Object new_value;
{
    x_note_fn_call(177,95);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_tuple_1,
	    Part_feature_recall_stack);
    Data_point_tuple_1 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-TUPLE-1 */
Object exit_part_feature_data_point_tuple_1()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,96);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_tuple_1 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_tuple_2, Qdata_point_tuple_2);

/* ENTER-PART-FEATURE-DATA-POINT-TUPLE-2 */
Object enter_part_feature_data_point_tuple_2(new_value)
    Object new_value;
{
    x_note_fn_call(177,97);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_tuple_2,
	    Part_feature_recall_stack);
    Data_point_tuple_2 = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-TUPLE-2 */
Object exit_part_feature_data_point_tuple_2()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,98);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_tuple_2 = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_x, Qdata_point_x);

/* ENTER-PART-FEATURE-DATA-POINT-X */
Object enter_part_feature_data_point_x(new_value)
    Object new_value;
{
    x_note_fn_call(177,99);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_x,
	    Part_feature_recall_stack);
    Data_point_x = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-X */
Object exit_part_feature_data_point_x()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,100);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_x = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_y, Qdata_point_y);

/* ENTER-PART-FEATURE-DATA-POINT-Y */
Object enter_part_feature_data_point_y(new_value)
    Object new_value;
{
    x_note_fn_call(177,101);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_y,
	    Part_feature_recall_stack);
    Data_point_y = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-Y */
Object exit_part_feature_data_point_y()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,102);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_y = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_first_x, Qdata_point_first_x);

/* ENTER-PART-FEATURE-DATA-POINT-FIRST-X */
Object enter_part_feature_data_point_first_x(new_value)
    Object new_value;
{
    x_note_fn_call(177,103);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_first_x,
	    Part_feature_recall_stack);
    Data_point_first_x = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-FIRST-X */
Object exit_part_feature_data_point_first_x()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,104);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_first_x = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_first_y, Qdata_point_first_y);

/* ENTER-PART-FEATURE-DATA-POINT-FIRST-Y */
Object enter_part_feature_data_point_first_y(new_value)
    Object new_value;
{
    x_note_fn_call(177,105);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_first_y,
	    Part_feature_recall_stack);
    Data_point_first_y = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-FIRST-Y */
Object exit_part_feature_data_point_first_y()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,106);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_first_y = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_last_x, Qdata_point_last_x);

/* ENTER-PART-FEATURE-DATA-POINT-LAST-X */
Object enter_part_feature_data_point_last_x(new_value)
    Object new_value;
{
    x_note_fn_call(177,107);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_last_x,
	    Part_feature_recall_stack);
    Data_point_last_x = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-LAST-X */
Object exit_part_feature_data_point_last_x()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,108);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_last_x = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_last_y, Qdata_point_last_y);

/* ENTER-PART-FEATURE-DATA-POINT-LAST-Y */
Object enter_part_feature_data_point_last_y(new_value)
    Object new_value;
{
    x_note_fn_call(177,109);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_last_y,
	    Part_feature_recall_stack);
    Data_point_last_y = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-LAST-Y */
Object exit_part_feature_data_point_last_y()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,110);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_last_y = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* ENTER-DATA-POINT-INDICATOR */
Object enter_data_point_indicator(new_value)
    Object new_value;
{
    x_note_fn_call(177,111);
    enter_data_point_indicator_1(new_value);
    return VALUES_1(Nil);
}

/* EXIT-DATA-POINT-INDICATOR */
Object exit_data_point_indicator()
{
    x_note_fn_call(177,112);
    exit_data_point_indicator_1();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_indicator, Qdata_point_indicator);

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_indicator_projection_function, Qdata_point_indicator_projection_function);

/* ENTER-PART-FEATURE-DATA-POINT-INDICATOR-PROJECTION-FUNCTION */
Object enter_part_feature_data_point_indicator_projection_function(new_value)
    Object new_value;
{
    x_note_fn_call(177,113);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_point_indicator_projection_function,
	    Part_feature_recall_stack);
    Data_point_indicator_projection_function = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-INDICATOR-PROJECTION-FUNCTION */
Object exit_part_feature_data_point_indicator_projection_function()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,114);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_indicator_projection_function = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_show_indicator, Qdata_point_show_indicator);

/* ENTER-PART-FEATURE-DATA-POINT-SHOW-INDICATOR */
Object enter_part_feature_data_point_show_indicator(new_value)
    Object new_value;
{
    x_note_fn_call(177,115);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_point_show_indicator,
	    Part_feature_recall_stack);
    Data_point_show_indicator = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-SHOW-INDICATOR */
Object exit_part_feature_data_point_show_indicator()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,116);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_show_indicator = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_point_show_connecting_line, Qdata_point_show_connecting_line);

/* ENTER-PART-FEATURE-DATA-POINT-SHOW-CONNECTING-LINE */
Object enter_part_feature_data_point_show_connecting_line(new_value)
    Object new_value;
{
    x_note_fn_call(177,117);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Data_point_show_connecting_line,
	    Part_feature_recall_stack);
    Data_point_show_connecting_line = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-DATA-POINT-SHOW-CONNECTING-LINE */
Object exit_part_feature_data_point_show_connecting_line()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,118);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Data_point_show_connecting_line = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_axis, Qcurrent_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Axis_heading, Qaxis_heading);

/* ENTER-PART-FEATURE-AXIS-HEADING */
Object enter_part_feature_axis_heading(new_value)
    Object new_value;
{
    x_note_fn_call(177,119);
    Part_feature_recall_stack = part_stack_cons_1(Axis_heading,
	    Part_feature_recall_stack);
    Axis_heading = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-HEADING */
Object exit_part_feature_axis_heading()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,120);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_heading = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_index, Qaxis_index);

/* ENTER-PART-FEATURE-AXIS-INDEX */
Object enter_part_feature_axis_index(new_value)
    Object new_value;
{
    x_note_fn_call(177,121);
    Part_feature_recall_stack = part_stack_cons_1(Axis_index,
	    Part_feature_recall_stack);
    Axis_index = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-INDEX */
Object exit_part_feature_axis_index()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,122);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_index = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* SIMPLE-NUMBER-P */
Object simple_number_p(x)
    Object x;
{
    Object temp;

    x_note_fn_call(177,123);
    temp = slot_value_number_p(x);
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ? T : 
		Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ?
		 T : Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "~DL" */

static Object string_constant_1;   /* "~D" */

/* SIMPLE-NUMBER-TYPE-WRITER */
Object simple_number_type_writer(x)
    Object x;
{
    Object temp;

    x_note_fn_call(177,124);
    if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	return tformat(2,string_constant,aref1(x,FIX((SI_Long)0L)));
    else {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	    temp = aref1(x,FIX((SI_Long)0L));
	else
	    temp = x;
	return tformat(2,string_constant_1,temp);
    }
}

/* SIMPLE-NONNEGATIVE-NUMBER-P */
Object simple_nonnegative_number_p(x)
    Object x;
{
    Object temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,125);
    if (simple_number_p(x)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    arg = 0.0;
	    if (slot_value_number_p(x)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		    temp = aref1(x,FIX((SI_Long)0L));
		else
		    temp = x;
	    }
	    else
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	    temp = lfloat(temp,float_constant_1);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg))
		result = VALUES_1( !inline_nanp_for_comparison(arg_1) ? T :
			 Nil);
	    else
		result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* SIMPLE-NONNEGATIVE-NUMBER-TYPE-WRITER */
Object simple_nonnegative_number_type_writer(x)
    Object x;
{
    Object temp;

    x_note_fn_call(177,126);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
	temp = aref1(x,FIX((SI_Long)0L));
    else
	temp = x;
    return tformat(2,string_constant_1,temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_minimum, Qaxis_minimum);

/* ENTER-PART-FEATURE-AXIS-MINIMUM */
Object enter_part_feature_axis_minimum(new_value)
    Object new_value;
{
    x_note_fn_call(177,127);
    Part_feature_recall_stack = part_stack_cons_1(Axis_minimum,
	    Part_feature_recall_stack);
    Axis_minimum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-MINIMUM */
Object exit_part_feature_axis_minimum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,128);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_minimum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_crossover, Qaxis_crossover);

/* ENTER-PART-FEATURE-AXIS-CROSSOVER */
Object enter_part_feature_axis_crossover(new_value)
    Object new_value;
{
    x_note_fn_call(177,129);
    Part_feature_recall_stack = part_stack_cons_1(Axis_crossover,
	    Part_feature_recall_stack);
    Axis_crossover = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-CROSSOVER */
Object exit_part_feature_axis_crossover()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,130);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_crossover = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_maximum, Qaxis_maximum);

/* ENTER-PART-FEATURE-AXIS-MAXIMUM */
Object enter_part_feature_axis_maximum(new_value)
    Object new_value;
{
    x_note_fn_call(177,131);
    Part_feature_recall_stack = part_stack_cons_1(Axis_maximum,
	    Part_feature_recall_stack);
    Axis_maximum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-MAXIMUM */
Object exit_part_feature_axis_maximum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,132);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_maximum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_count, Qaxis_tickmark_count);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-COUNT */
Object enter_part_feature_axis_tickmark_count(new_value)
    Object new_value;
{
    x_note_fn_call(177,133);
    Part_feature_recall_stack = part_stack_cons_1(Axis_tickmark_count,
	    Part_feature_recall_stack);
    Axis_tickmark_count = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-COUNT */
Object exit_part_feature_axis_tickmark_count()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,134);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_count = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_step, Qaxis_tickmark_step);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-STEP */
Object enter_part_feature_axis_tickmark_step(new_value)
    Object new_value;
{
    x_note_fn_call(177,135);
    Part_feature_recall_stack = part_stack_cons_1(Axis_tickmark_step,
	    Part_feature_recall_stack);
    Axis_tickmark_step = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-STEP */
Object exit_part_feature_axis_tickmark_step()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,136);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_step = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_automatic, Qaxis_automatic);

/* ENTER-PART-FEATURE-AXIS-AUTOMATIC */
Object enter_part_feature_axis_automatic(new_value)
    Object new_value;
{
    x_note_fn_call(177,137);
    Part_feature_recall_stack = part_stack_cons_1(Axis_automatic,
	    Part_feature_recall_stack);
    Axis_automatic = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-AUTOMATIC */
Object exit_part_feature_axis_automatic()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,138);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_automatic = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_count_as_fixnum, Qaxis_tickmark_count_as_fixnum);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-COUNT-AS-FIXNUM */
Object enter_part_feature_axis_tickmark_count_as_fixnum(new_value)
    Object new_value;
{
    x_note_fn_call(177,139);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Axis_tickmark_count_as_fixnum,
	    Part_feature_recall_stack);
    Axis_tickmark_count_as_fixnum = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-COUNT-AS-FIXNUM */
Object exit_part_feature_axis_tickmark_count_as_fixnum()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,140);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_count_as_fixnum = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_label_frequency, Qaxis_tickmark_label_frequency);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-FREQUENCY */
Object enter_part_feature_axis_tickmark_label_frequency(new_value)
    Object new_value;
{
    x_note_fn_call(177,141);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Axis_tickmark_label_frequency,
	    Part_feature_recall_stack);
    Axis_tickmark_label_frequency = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-FREQUENCY */
Object exit_part_feature_axis_tickmark_label_frequency()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,142);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_label_frequency = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_label_max_digits_before_point, Qaxis_tickmark_label_max_digits_before_point);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-BEFORE-POINT */
Object enter_part_feature_axis_tickmark_label_max_digits_before_point(new_value)
    Object new_value;
{
    x_note_fn_call(177,143);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Axis_tickmark_label_max_digits_before_point,
	    Part_feature_recall_stack);
    Axis_tickmark_label_max_digits_before_point = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-BEFORE-POINT */
Object exit_part_feature_axis_tickmark_label_max_digits_before_point()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,144);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_label_max_digits_before_point = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_label_max_digits_after_point, Qaxis_tickmark_label_max_digits_after_point);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-AFTER-POINT */
Object enter_part_feature_axis_tickmark_label_max_digits_after_point(new_value)
    Object new_value;
{
    x_note_fn_call(177,145);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Axis_tickmark_label_max_digits_after_point,
	    Part_feature_recall_stack);
    Axis_tickmark_label_max_digits_after_point = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-AFTER-POINT */
Object exit_part_feature_axis_tickmark_label_max_digits_after_point()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,146);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_label_max_digits_after_point = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_tickmark_label_max_digits_in_exponent, Qaxis_tickmark_label_max_digits_in_exponent);

/* ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-IN-EXPONENT */
Object enter_part_feature_axis_tickmark_label_max_digits_in_exponent(new_value)
    Object new_value;
{
    x_note_fn_call(177,147);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Axis_tickmark_label_max_digits_in_exponent,
	    Part_feature_recall_stack);
    Axis_tickmark_label_max_digits_in_exponent = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-IN-EXPONENT */
Object exit_part_feature_axis_tickmark_label_max_digits_in_exponent()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,148);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Axis_tickmark_label_max_digits_in_exponent = part_stack_pop_store;
    return VALUES_1(Nil);
}

/* SIMPLE-NUMBER-FOR-SIGNIFICANT-DIGITS-P */
Object simple_number_for_significant_digits_p(x)
    Object x;
{
    Object temp;

    x_note_fn_call(177,149);
    if (FIXNUMP(x)) {
	if (IFIX(x) == (SI_Long)-1L)
	    temp = T;
	else if (IFIX(x) > (SI_Long)15L)
	    temp = Nil;
	else if (IFIX(x) < (SI_Long)2L)
	    temp = Nil;
	else
	    temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_significant_digits, Qnumber_of_significant_digits);

/* ENTER-PART-FEATURE-NUMBER-OF-SIGNIFICANT-DIGITS */
Object enter_part_feature_number_of_significant_digits(new_value)
    Object new_value;
{
    x_note_fn_call(177,150);
    Part_feature_recall_stack = 
	    part_stack_cons_1(Number_of_significant_digits,
	    Part_feature_recall_stack);
    Number_of_significant_digits = new_value;
    return VALUES_1(Nil);
}

/* EXIT-PART-FEATURE-NUMBER-OF-SIGNIFICANT-DIGITS */
Object exit_part_feature_number_of_significant_digits()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(177,151);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    Number_of_significant_digits = part_stack_pop_store;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Axis_is_discrete_p, Qaxis_is_discrete_p);

static Object float_constant_2;    /* -7.0 */

/* SAFE-CHART-LOG */
Object safe_chart_log(x)
    Object x;
{
    double temp, x1, arg, arg_1;

    x_note_fn_call(177,152);
    temp = DOUBLE_FLOAT_TO_DOUBLE(x);
    x1 = ABS(temp);
    arg = DOUBLE_FLOAT_TO_DOUBLE(x);
    arg_1 = 1.0E-7;
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return VALUES_1(float_constant_2);
    else
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DOUBLE_LOG(x1,10.0)));
}

/* ESTIMATED-AXIS-GRANULARITY */
Object estimated_axis_granularity(x)
    Object x;
{
    Object temp_1;
    double arg, arg_1, temp, x1, d1, d2, d5;

    x_note_fn_call(177,153);
    arg = DOUBLE_FLOAT_TO_DOUBLE(x);
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return VALUES_1(float_constant);
    else {
	temp = DOUBLE_FLOAT_TO_DOUBLE(x);
	x1 = ABS(temp);
	temp_1 = lftruncate(safe_chart_log(DOUBLE_TO_DOUBLE_FLOAT(x1)),_);
	temp = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	d1 = pow(10.0,temp);
	d2 = d1 + d1;
	d5 = 5.0 * d1;
	arg = d5;
	arg_1 = x1;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(d5));
	else {
	    arg = d2;
	    arg_1 = x1;
	    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(d2));
	    else {
		arg = d1;
		arg_1 = x1;
		if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(d1));
		else
		    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(d1 / 2.0));
	    }
	}
    }
}

/* ESTIMATED-AXIS-BOUNDARIES */
Object estimated_axis_boundaries(data_minimum,data_maximum)
    Object data_minimum, data_maximum;
{
    Object temp_2;
    char temp_3;
    double temp, temp_1, grain, gensymed_symbol, arg, arg_1, gensymed_symbol_1;
    double low, high;

    x_note_fn_call(177,154);
    temp = DOUBLE_FLOAT_TO_DOUBLE(data_minimum);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(data_maximum);
    temp_2 = estimated_axis_granularity(DOUBLE_TO_DOUBLE_FLOAT(temp - temp_1));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    grain = temp_1 / 10.0;
    gensymed_symbol = grain;
    arg = DOUBLE_FLOAT_TO_DOUBLE(data_minimum);
    arg_1 = 0.0;
    temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
	    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    if (temp_3);
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(data_minimum);
	arg_1 = 0.0;
	temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_3) {
	temp_2 = lffloor(data_minimum,DOUBLE_TO_DOUBLE_FLOAT(grain));
	gensymed_symbol_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    }
    else
	gensymed_symbol_1 = 0.0;
    low = gensymed_symbol * gensymed_symbol_1;
    temp_2 = fceiling(data_maximum,DOUBLE_TO_DOUBLE_FLOAT(grain));
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    high = grain * temp_1;
    return VALUES_3(DOUBLE_TO_DOUBLE_FLOAT(low),
	    DOUBLE_TO_DOUBLE_FLOAT(high),DOUBLE_TO_DOUBLE_FLOAT(grain));
}

static Object float_constant_3;    /* -1.0 */

/* COMPUTE-AXIS-BOUNDS-1 */
Object compute_axis_bounds_1(axis_description,data_minimum,data_maximum)
    Object axis_description, data_minimum, data_maximum;
{
    Object requested_axis_minimum_qm, requested_axis_maximum_qm, temp;
    Object computed_axis_minimum, computed_axis_maximum, min_1, max_1, log_1;
    Object bump, max_new_value;
    char temp_3;
    double arg, arg_1, temp_1, tiny, arg_2, arg_3, temp_2, bump_1;
    Object result;

    x_note_fn_call(177,155);
    requested_axis_minimum_qm = get_simple_part_feature(axis_description,
	    Qaxis_minimum);
    requested_axis_maximum_qm = get_simple_part_feature(axis_description,
	    Qaxis_maximum);
    if (requested_axis_minimum_qm) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(requested_axis_minimum_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_axis_minimum_qm)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(requested_axis_minimum_qm,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(requested_axis_minimum_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_axis_minimum_qm)) 
		== (SI_Long)1L)
	    temp = aref1(requested_axis_minimum_qm,FIX((SI_Long)0L));
	else
	    temp = requested_axis_minimum_qm;
	requested_axis_minimum_qm = lfloat(temp,float_constant_1);
    }
    if (requested_axis_maximum_qm) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(requested_axis_maximum_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_axis_maximum_qm)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(requested_axis_maximum_qm,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(requested_axis_maximum_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_axis_maximum_qm)) 
		== (SI_Long)1L)
	    temp = aref1(requested_axis_maximum_qm,FIX((SI_Long)0L));
	else
	    temp = requested_axis_maximum_qm;
	requested_axis_maximum_qm = lfloat(temp,float_constant_1);
    }
    if (requested_axis_minimum_qm && requested_axis_maximum_qm) {
	Axis_minimum = make_slot_value_float(requested_axis_minimum_qm);
	arg = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_minimum_qm);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_maximum_qm);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_minimum_qm);
	    temp = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 1.0);
	}
	else
	    temp = requested_axis_maximum_qm;
	Axis_maximum = make_slot_value_float(temp);
    }
    else {
	result = estimated_axis_boundaries(data_minimum,data_maximum);
	MVS_2(result,computed_axis_minimum,computed_axis_maximum);
	min_1 = computed_axis_minimum;
	max_1 = computed_axis_maximum;
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(computed_axis_minimum);
	log_1 = 
		lftruncate(safe_chart_log(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_1))),
		_);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(log_1);
	tiny = pow(10.0,temp_1 - 5.0);
	bump = float_constant;
	arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
	if ( !(arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    max_new_value = min_1;
	    min_1 = max_1;
	    max_1 = max_new_value;
	    bump = float_constant_3;
	}
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	arg = temp_1 - tiny;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	arg_2 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	arg_3 = temp_1 + tiny;
	if (arg <= arg_1 && arg_1 <= arg_2 && arg_2 <= arg_3 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) &&  
		!inline_nanp_for_comparison(arg_2) &&  
		!inline_nanp_for_comparison(arg_3)) {
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(computed_axis_minimum);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(bump);
	    computed_axis_minimum = DOUBLE_TO_DOUBLE_FLOAT(temp_2 - temp_1);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(computed_axis_maximum);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(bump);
	    computed_axis_maximum = DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_1);
	}
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(data_minimum);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(data_maximum);
	temp_1 = temp_2 - temp_1;
	temp = 
		lftruncate(safe_chart_log(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_1))),
		_);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	bump_1 = pow(10.0,temp_1);
	if (requested_axis_minimum_qm) {
	    arg = DOUBLE_FLOAT_TO_DOUBLE(computed_axis_maximum);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_minimum_qm);
	    temp_3 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_minimum_qm);
	    computed_axis_maximum = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + bump_1);
	}
	if (requested_axis_maximum_qm) {
	    arg = DOUBLE_FLOAT_TO_DOUBLE(computed_axis_minimum);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_maximum_qm);
	    temp_3 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_axis_maximum_qm);
	    computed_axis_minimum = DOUBLE_TO_DOUBLE_FLOAT(temp_1 - bump_1);
	}
	temp = requested_axis_minimum_qm;
	if (temp);
	else
	    temp = computed_axis_minimum;
	Axis_minimum = temp;
	temp = requested_axis_maximum_qm;
	if (temp);
	else
	    temp = computed_axis_maximum;
	Axis_maximum = temp;
	arg = DOUBLE_FLOAT_TO_DOUBLE(Axis_minimum);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Axis_maximum);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Axis_minimum);
	    Axis_maximum = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 1.0);
	}
	Axis_minimum = make_slot_value_float(Axis_minimum);
	Axis_maximum = make_slot_value_float(Axis_maximum);
    }
    return VALUES_2(Axis_minimum,Axis_maximum);
}

/* COMPUTE-AXIS-BOUNDS */
Object compute_axis_bounds(computed_axis_description,
	    requested_axis_description,data_minimum,data_maximum)
    Object computed_axis_description, requested_axis_description, data_minimum;
    Object data_maximum;
{
    Object crossover, axis_minimum, axis_maximum, part;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,156);
    crossover = get_simple_part_feature(requested_axis_description,
	    Qaxis_crossover);
    if (crossover)
	set_simple_part_feature(computed_axis_description,Qaxis_crossover,
		copy_for_slot_value(crossover));
    axis_minimum = Nil;
    axis_maximum = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Axis_maximum,Qaxis_maximum,axis_maximum,1);
      PUSH_SPECIAL_WITH_SYMBOL(Axis_minimum,Qaxis_minimum,axis_minimum,0);
	compute_axis_bounds_1(requested_axis_description,data_minimum,
		data_maximum);
	part = computed_axis_description;
	set_simple_part_feature(part,Qaxis_minimum,Axis_minimum);
	result = set_simple_part_feature(part,Qaxis_maximum,Axis_maximum);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* PIN-CROSSOVER-AS-NECESSARY */
Object pin_crossover_as_necessary(axis_with_crossover,axis)
    Object axis_with_crossover, axis;
{
    Object slot_value_number, temp, min_1, max_1, crossover, max_new_value;
    double arg, arg_1, arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,157);
    PUSH_SPECIAL_WITH_SYMBOL(Axis,Qaxis,axis,0);
      slot_value_number = get_simple_part_feature(Axis,Qaxis_minimum);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
	      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		  (SI_Long)0L));
      else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = aref1(slot_value_number,FIX((SI_Long)0L));
      else
	  temp = slot_value_number;
      min_1 = lfloat(temp,float_constant_1);
      slot_value_number = get_simple_part_feature(Axis,Qaxis_maximum);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
	      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		  (SI_Long)0L));
      else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = aref1(slot_value_number,FIX((SI_Long)0L));
      else
	  temp = slot_value_number;
      max_1 = lfloat(temp,float_constant_1);
      slot_value_number = get_simple_part_feature(axis_with_crossover,
	      Qaxis_crossover);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
	      && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		  (SI_Long)0L));
      else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
	      (SI_Long)1L)
	  temp = aref1(slot_value_number,FIX((SI_Long)0L));
      else
	  temp = slot_value_number;
      crossover = lfloat(temp,float_constant_1);
      arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
      if ( !(arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	      !inline_nanp_for_comparison(arg_1))) {
	  max_new_value = min_1;
	  min_1 = max_1;
	  max_1 = max_new_value;
      }
      arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(crossover);
      arg_2 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
      if ( !(arg <= arg_1 && arg_1 <= arg_2 &&  
	      !inline_nanp_for_comparison(arg) &&  
	      !inline_nanp_for_comparison(arg_1) &&  
	      !inline_nanp_for_comparison(arg_2))) {
	  arg = DOUBLE_FLOAT_TO_DOUBLE(crossover);
	  arg_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	  result = set_simple_part_feature(axis_with_crossover,
		  Qaxis_crossover,make_slot_value_float(arg < arg_1 &&  
		  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1) ? min_1 : max_1));
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* PLOT-NORTH-AXIS-LABEL-TICKMARKS-AS-INTEGERS-P */
Object plot_north_axis_label_tickmarks_as_integers_p(chart_frame)
    Object chart_frame;
{
    Object current_computation_frame, data_series, ab_loop_list_;
    Object data_series_source_temp1, data_series_source_temp2, info_2, x2;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(177,158);
    SAVE_STACK();
    LOCK(Working_on_lexical_computation_of_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_computation_frame = chart_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  if (ISVREF(chart_frame,(SI_Long)20L)) {
	      data_series = Nil;
	      ab_loop_list_ = ISVREF(chart_frame,(SI_Long)20L);
	      PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,0);
		data_series_source_temp1 = Nil;
		data_series_source_temp2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		Data_series = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		data_series_source_temp1 = 
			evaluate_designation(get_simple_part_feature(Data_series,
			Qdata_series_info_1),Nil);
		info_2 = get_simple_part_feature(Data_series,
			Qdata_series_info_2);
		data_series_source_temp2 = info_2 ? 
			evaluate_designation(info_2,Nil) : Nil;
		if ( !TRUEP(get_simple_part_feature(Data_series,
			Qdata_series_info_2))) {
		    if (SIMPLE_VECTOR_P(data_series_source_temp1) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_series_source_temp1)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(data_series_source_temp1,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(data_series_source_temp1,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(data_series_source_temp1,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Integer_array_class_description,
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
			temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
		    }
		    else
			temp_1 = Nil;
		    if (temp_1);
		    else {
			sub_class_bit_vector = 
				ISVREF(ISVREF(data_series_source_temp1,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Integer_list_class_description,
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
			    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
			}
			else
			    temp_1 = Nil;
		    }
		}
		else {
		    if (SIMPLE_VECTOR_P(data_series_source_temp2) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_series_source_temp2)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(data_series_source_temp2,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(data_series_source_temp2,(SI_Long)1L);
			temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if (SIMPLE_VECTOR_P(data_series_source_temp1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_series_source_temp1)) 
				> (SI_Long)2L &&  
				!EQ(ISVREF(data_series_source_temp1,
				(SI_Long)1L),Qavailable_frame_vector)) {
			    x2 = ISVREF(data_series_source_temp1,(SI_Long)1L);
			    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				    (SI_Long)0L),
				    Qg2_defstruct_structure_name_class_description_g2_struct) 
				    ? TRUEP(x2) : TRUEP(Qnil);
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(data_series_source_temp2,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Integer_array_class_description,
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
			    temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
			}
			else
			    temp_1 = Nil;
			if (temp_1);
			else {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(data_series_source_temp2,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Integer_list_class_description,
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
				temp_1 = (SI_Long)0L < gensymed_symbol ? T 
					: Nil;
			    }
			    else
				temp_1 = Nil;
			}
		    }
		    else {
			if (SIMPLE_VECTOR_P(data_series_source_temp1) && 
				EQ(ISVREF(data_series_source_temp1,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_temporary_constant_g2_struct))
			    reclaim_temporary_constant_1(data_series_source_temp1);
			if (SIMPLE_VECTOR_P(data_series_source_temp2) && 
				EQ(ISVREF(data_series_source_temp2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_temporary_constant_g2_struct))
			    reclaim_temporary_constant_1(data_series_source_temp2);
			temp_1 = Nil;
		    }
		}
		if ( !TRUEP(temp_1)) {
		    temp_1 = Nil;
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp_1 = T;
		goto end_1;
		temp_1 = Qnil;
	      end_1:;
	      POP_SPECIAL();
	  }
	  else
	      temp_1 = Nil;
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp_1));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_lexical_computation_of_frame);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    result = VALUES_1(result);
    RESTORE_STACK();
    return result;
}

static Object Qone_g2_quantity_list;  /* one-g2-quantity-list */

static Object Qpair_of_g2_quantity_lists;  /* pair-of-g2-quantity-lists */

/* PLOT-EAST-AXIS-LABEL-TICKMARKS-AS-INTEGERS-P */
Object plot_east_axis_label_tickmarks_as_integers_p(chart_frame)
    Object chart_frame;
{
    Object current_computation_frame, data_series, ab_loop_list_;
    Object data_series_source_temp, temp, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(177,159);
    SAVE_STACK();
    LOCK(Working_on_lexical_computation_of_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_computation_frame = chart_frame;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  if (ISVREF(chart_frame,(SI_Long)20L)) {
	      data_series = Nil;
	      ab_loop_list_ = ISVREF(chart_frame,(SI_Long)20L);
	      PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,0);
		data_series_source_temp = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		Data_series = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		data_series_source_temp = 
			evaluate_designation(get_simple_part_feature(Data_series,
			Qdata_series_info_1),Nil);
		if (EQ(Qone_g2_quantity_list,
			get_simple_part_feature(Data_series,
			Qdata_series_source_kind)))
		    temp = T;
		else if (EQ(Qpair_of_g2_quantity_lists,
			get_simple_part_feature(Data_series,
			Qdata_series_source_kind)) &&  
			!EQ(data_series_source_temp,Nil)) {
		    if (SIMPLE_VECTOR_P(data_series_source_temp) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(data_series_source_temp)) 
			    > (SI_Long)2L &&  
			    !EQ(ISVREF(data_series_source_temp,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(data_series_source_temp,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			sub_class_bit_vector = 
				ISVREF(ISVREF(data_series_source_temp,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Integer_array_class_description,
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
			    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
			}
			else
			    temp = Nil;
			if (temp);
			else {
			    sub_class_bit_vector = 
				    ISVREF(ISVREF(data_series_source_temp,
				    (SI_Long)1L),(SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Integer_list_class_description,
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
				temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
			    }
			    else
				temp = Nil;
			}
		    }
		    else
			temp = Nil;
		}
		else
		    temp = Nil;
		if ( !TRUEP(temp)) {
		    temp = Nil;
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp = T;
		goto end_1;
		temp = Qnil;
	      end_1:;
	      POP_SPECIAL();
	  }
	  else
	      temp = Nil;
	POP_SPECIAL();
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_lexical_computation_of_frame);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    result = VALUES_1(result);
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Tickmark_label_min_height, Qtickmark_label_min_height);

DEFINE_VARIABLE_WITH_SYMBOL(Tickmark_label_char_width, Qtickmark_label_char_width);

DEFINE_VARIABLE_WITH_SYMBOL(Tickmark_label_min_width, Qtickmark_label_min_width);

static Object float_constant_4;    /* 2.0 */

static Object Qeast;               /* east */

static Object Qnorth;              /* north */

static Object list_constant;       /* # */

/* COMPUTE-AXIS-TICKMARKS-AND-STYLE */
Object compute_axis_tickmarks_and_style varargs_1(int, n)
{
    Object requested_axis_description, computed_axis_description;
    Object tickmark_min_width, slot_value_number, temp, min_1, max_1, heading;
    Object requested_tickmark_count_qm, requested_tickmark_step_qm;
    Object gensymed_symbol_1, actual_tickmark_count;
    Object axis_tickmark_label_frequency, discrete_p, actual_tickmark_step;
    Object device_range, label_min_size, label_room, part, feature, value;
    Object ab_loop_list_;
    char temp_3;
    double temp_1, temp_2, range, gensymed_symbol, arg, arg_1;
    double gensymed_symbol_2;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,160);
    INIT_ARGS_nonrelocating();
    requested_axis_description = REQUIRED_ARG_nonrelocating();
    computed_axis_description = REQUIRED_ARG_nonrelocating();
    tickmark_min_width = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Tickmark_label_min_width;
    END_ARGS_nonrelocating();
    slot_value_number = get_simple_part_feature(computed_axis_description,
	    Qaxis_minimum);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	temp = slot_value_number;
    min_1 = lfloat(temp,float_constant_1);
    slot_value_number = get_simple_part_feature(computed_axis_description,
	    Qaxis_maximum);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	temp = slot_value_number;
    max_1 = lfloat(temp,float_constant_1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
    range = temp_1 - temp_2;
    heading = get_simple_part_feature(computed_axis_description,Qaxis_heading);
    requested_tickmark_count_qm = 
	    get_simple_part_feature(requested_axis_description,
	    Qaxis_tickmark_count);
    requested_tickmark_step_qm = 
	    get_simple_part_feature(requested_axis_description,
	    Qaxis_tickmark_step);
    if (requested_tickmark_count_qm) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(requested_tickmark_count_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_tickmark_count_qm)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(requested_tickmark_count_qm,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(requested_tickmark_count_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_tickmark_count_qm)) 
		== (SI_Long)1L)
	    temp = aref1(requested_tickmark_count_qm,FIX((SI_Long)0L));
	else
	    temp = requested_tickmark_count_qm;
	temp = lftruncate(lfloat(temp,float_constant_1),_);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	gensymed_symbol = ABS(temp_2);
	gensymed_symbol_1 = float_constant_1;
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
	actual_tickmark_count = DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol,
		temp_2));
    }
    else
	actual_tickmark_count = float_constant_4;
    axis_tickmark_label_frequency = FIX((SI_Long)1L);
    PUSH_SPECIAL_WITH_SYMBOL(Axis_tickmark_label_frequency,Qaxis_tickmark_label_frequency,axis_tickmark_label_frequency,
	    0);
      discrete_p = EQ(heading,Qeast) ? 
	      plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
	      : Qnil;
      actual_tickmark_step = Nil;
      device_range = Nil;
      label_min_size = Nil;
      label_room = Nil;
      if (requested_tickmark_step_qm) {
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(requested_tickmark_step_qm) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_tickmark_step_qm)) 
		  == (SI_Long)1L)
	      temp = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(requested_tickmark_step_qm,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(requested_tickmark_step_qm) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(requested_tickmark_step_qm)) 
		  == (SI_Long)1L)
	      temp = aref1(requested_tickmark_step_qm,FIX((SI_Long)0L));
	  else
	      temp = requested_tickmark_step_qm;
	  requested_tickmark_step_qm = lfloat(temp,float_constant_1);
      }
      if (requested_tickmark_step_qm) {
	  arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	  arg_1 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
	  if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1)) {
	      arg = 0.0;
	      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(requested_tickmark_step_qm);
	      temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	  }
	  else {
	      arg = DOUBLE_FLOAT_TO_DOUBLE(requested_tickmark_step_qm);
	      arg_1 = 0.0;
	      temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	  }
      }
      else
	  temp_3 = TRUEP(Nil);
      if (temp_3)
	  actual_tickmark_step = requested_tickmark_step_qm;
      else {
	  gensymed_symbol = range;
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_count);
	  gensymed_symbol_2 = temp_2 - 1.0;
	  gensymed_symbol_1 = float_constant;
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_1);
	  gensymed_symbol_2 = MAX(gensymed_symbol_2,temp_2);
	  actual_tickmark_step = DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol / 
		  gensymed_symbol_2);
      }
      if (requested_tickmark_step_qm) {
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_step);
	  temp = lftruncate(DOUBLE_TO_DOUBLE_FLOAT(range / temp_2 + 0.001),_);
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	  actual_tickmark_count = DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_2) + 1.0);
      }
      if (EQ(heading,Qeast)) {
	  device_range = 
		  DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_right,
		  Chart_left),Chart_left_margin),Chart_right_margin)));
	  label_min_size = tickmark_min_width;
      }
      else if (EQ(heading,Qnorth)) {
	  device_range = 
		  DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_bottom,
		  Chart_top),Chart_top_margin),Chart_bottom_margin)));
	  label_min_size = Tickmark_label_min_height;
      }
      if (discrete_p) {
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_step);
	  actual_tickmark_step = 
		  ftruncatee_up(DOUBLE_TO_DOUBLE_FLOAT(0.9999 * temp_2));
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_step);
	  temp = lftruncate(DOUBLE_TO_DOUBLE_FLOAT(range / temp_2 + 0.001),_);
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	  actual_tickmark_count = DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_2) + 1.0);
      }
      arg = 0.0;
      arg_1 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_count);
      if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	      !inline_nanp_for_comparison(arg_1))) {
	  arg = DOUBLE_FLOAT_TO_DOUBLE(label_min_size);
	  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(device_range);
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_count);
	  label_room = DOUBLE_TO_DOUBLE_FLOAT(temp_1 / temp_2);
	  arg_1 = DOUBLE_FLOAT_TO_DOUBLE(label_room);
	  temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
      }
      else
	  temp_3 = TRUEP(Nil);
      if (temp_3) {
	  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(label_min_size);
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(label_room);
	  Axis_tickmark_label_frequency = 
		  LONG_TO_FIXNUM(inline_ceiling_1(temp_1 / temp_2));
	  arg = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_count);
	  arg_1 = 2.0;
	  if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1)) {
	      if (discrete_p) {
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_step);
		  actual_tickmark_step = 
			  ftruncatee_up(DOUBLE_TO_DOUBLE_FLOAT(0.9999 * 
			  temp_2));
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(actual_tickmark_step);
		  temp = lftruncate(DOUBLE_TO_DOUBLE_FLOAT(range / temp_2 
			  + 0.001),_);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		  actual_tickmark_count = 
			  DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_2) + 1.0);
	      }
	  }
      }
      part = computed_axis_description;
      set_simple_part_feature(part,Qaxis_tickmark_step,
	      make_slot_value_float(actual_tickmark_step));
      set_simple_part_feature(part,Qaxis_tickmark_count,
	      make_slot_value_float(actual_tickmark_count));
      set_simple_part_feature(part,Qaxis_tickmark_count_as_fixnum,
	      ltruncate(actual_tickmark_count,_));
      set_simple_part_feature(part,Qaxis_tickmark_label_frequency,
	      Axis_tickmark_label_frequency);
      feature = Nil;
      value = Nil;
      ab_loop_list_ = CDR(requested_axis_description);
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
    next_loop:
      feature = CAR(ab_loop_list_);
      temp = CDR(ab_loop_list_);
      value = CAR(temp);
      if (memq_function(feature,list_constant))
	  set_simple_part_feature(computed_axis_description,feature,value);
      ab_loop_list_ = CDDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* AXIS-SERIES-OPEN-GENERATOR */
Object axis_series_open_generator()
{
    Object temp, data_point_tuple_2_new_value, data_point_tuple_1_new_value;

    x_note_fn_call(177,161);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_minimum) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_minimum,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(Axis_minimum) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) == (SI_Long)1L)
	temp = aref1(Axis_minimum,FIX((SI_Long)0L));
    else
	temp = Axis_minimum;
    Data_point_tuple_1 = make_temporary_constant_no_expiration(lfloat(temp,
	    float_constant_1),Qnumber);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_crossover) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_crossover)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_crossover,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(Axis_crossover) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_crossover)) == (SI_Long)1L)
	temp = aref1(Axis_crossover,FIX((SI_Long)0L));
    else
	temp = Axis_crossover;
    Data_point_tuple_2 = make_temporary_constant_no_expiration(lfloat(temp,
	    float_constant_1),Qnumber);
    if (EQ(Axis_heading,Qnorth)) {
	data_point_tuple_2_new_value = Data_point_tuple_1;
	data_point_tuple_1_new_value = Data_point_tuple_2;
	Data_point_tuple_1 = data_point_tuple_1_new_value;
	Data_point_tuple_2 = data_point_tuple_2_new_value;
    }
    transform_data_tuple_to_device_coordinates();
    if (EQ(Axis_heading,Qnorth))
	Chart_origin_x = Data_point_x;
    else if (EQ(Axis_heading,Qeast))
	Chart_origin_y = Data_point_y;
    return VALUES_1(T);
}

/* AXIS-SERIES-CLOSE-GENERATOR */
Object axis_series_close_generator()
{
    Object temp;

    x_note_fn_call(177,162);
    reclaim_temporary_constant_1(Data_point_tuple_1);
    temp = reclaim_temporary_constant_1(Data_point_tuple_2);
    return VALUES_1(temp);
}

/* AXIS-SERIES-NEXT-TUPLE */
Object axis_series_next_tuple()
{
    Object temp, data_point_tuple_1_new_value, tick_mark_index;
    Object gensymed_symbol, managed_number_or_value, temp_1;
    double gensymed_symbol_1, gensymed_symbol_2;
    double store_managed_number_or_value_arg;

    x_note_fn_call(177,163);
    Data_point_tuple_valid_qm = T;
    if (EQ(Axis_heading,Qnorth)) {
	temp = Data_point_tuple_1;
	data_point_tuple_1_new_value = Data_point_tuple_2;
	Data_point_tuple_1 = data_point_tuple_1_new_value;
	Data_point_tuple_2 = temp;
    }
    tick_mark_index = Data_point_index;
    if ((SI_Long)1L == IFIX(tick_mark_index));
    else if (FIXNUM_LT(Axis_tickmark_count_as_fixnum,tick_mark_index))
	Data_point_tuple_valid_qm = Nil;
    else {
	gensymed_symbol = Data_point_tuple_1;
	managed_number_or_value = ISVREF(Data_point_tuple_1,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    gensymed_symbol_1 = DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L);
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L) {
	    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    gensymed_symbol_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	}
	else
	    gensymed_symbol_1 = 
		    DOUBLE_FLOAT_TO_DOUBLE(managed_number_or_value);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_tickmark_step) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_tickmark_step)) == 
		(SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_tickmark_step,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(Axis_tickmark_step) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_tickmark_step)) == 
		(SI_Long)1L)
	    temp_1 = aref1(Axis_tickmark_step,FIX((SI_Long)0L));
	else
	    temp_1 = Axis_tickmark_step;
	temp_1 = lfloat(temp_1,float_constant_1);
	gensymed_symbol_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	store_managed_number_or_value_arg = gensymed_symbol_1;
	temp = 
		store_managed_number_or_value_function(ISVREF(gensymed_symbol,
		(SI_Long)1L),
		DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
    }
    if (EQ(Axis_heading,Qnorth)) {
	temp = Data_point_tuple_1;
	data_point_tuple_1_new_value = Data_point_tuple_2;
	Data_point_tuple_1 = data_point_tuple_1_new_value;
	Data_point_tuple_2 = temp;
	temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_axis_data_series_instance, Qdefault_axis_data_series_instance);

/* MALFORMED-DATA-SERIES-RETURN-NIL */
Object malformed_data_series_return_nil()
{
    x_note_fn_call(177,164);
    return VALUES_1(Nil);
}

/* FLOAT-AND-FLOAT-FROM-DATA-CACHES-OPEN-GENERATOR */
Object float_and_float_from_data_caches_open_generator()
{
    Object temp, temp_1;

    x_note_fn_call(177,165);
    Data_point_tuple_1 = 
	    make_temporary_constant_no_expiration(float_constant_1,Qnumber);
    Data_point_tuple_2 = 
	    make_temporary_constant_no_expiration(float_constant_1,Qnumber);
    Data_series_generator_info_1 = FIX((SI_Long)-1L);
    temp = ISVREF(Data_series_data_cache_1_qm,(SI_Long)1L);
    temp_1 = ISVREF(Data_series_data_cache_2_qm,(SI_Long)1L);
    Data_series_generator_info_2 = FIXNUM_MIN(temp,temp_1);
    return VALUES_1(T);
}

/* FLOAT-AND-FLOAT-FROM-DATA-CACHES-NEXT-TUPLE */
Object float_and_float_from_data_caches_next_tuple()
{
    Object temp, gensymed_symbol;
    double gensymed_symbol_1, store_managed_number_or_value_arg;

    x_note_fn_call(177,166);
    temp = FIXNUM_ADD1(Data_series_generator_info_1);
    Data_series_generator_info_1 = temp;
    if (FIXNUM_GE(Data_series_generator_info_1,Data_series_generator_info_2))
	Data_point_tuple_valid_qm = Nil;
    else {
	gensymed_symbol = Data_point_tuple_1;
	gensymed_symbol_1 = 
		DFLOAT_ISAREF_1(ISVREF(Data_series_data_cache_1_qm,
		(IFIX(Data_series_generator_info_1) >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),IFIX(Data_series_generator_info_1) & 
		(SI_Long)1023L);
	store_managed_number_or_value_arg = gensymed_symbol_1;
	temp = 
		store_managed_number_or_value_function(ISVREF(gensymed_symbol,
		(SI_Long)1L),
		DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	gensymed_symbol = Data_point_tuple_2;
	gensymed_symbol_1 = 
		DFLOAT_ISAREF_1(ISVREF(Data_series_data_cache_2_qm,
		(IFIX(Data_series_generator_info_1) >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L),IFIX(Data_series_generator_info_1) & 
		(SI_Long)1023L);
	store_managed_number_or_value_arg = gensymed_symbol_1;
	temp = 
		store_managed_number_or_value_function(ISVREF(gensymed_symbol,
		(SI_Long)1L),
		DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	Data_point_tuple_valid_qm = T;
    }
    return VALUES_1(Data_point_tuple_valid_qm);
}

/* FLOAT-AND-FLOAT-FROM-DATA-CACHES-CLOSE-GENERATOR */
Object float_and_float_from_data_caches_close_generator()
{
    x_note_fn_call(177,167);
    reclaim_temporary_constant_1(Data_point_tuple_1);
    reclaim_temporary_constant_1(Data_point_tuple_2);
    return VALUES_1(Nil);
}

static Object Qdata_series_generator_open_method;  /* data-series-generator-open-method */

static Object Qdata_series_generator_next_tuple_method;  /* data-series-generator-next-tuple-method */

static Object Qdata_series_generator_close_method;  /* data-series-generator-close-method */

/* SIMPLE-SCATTER-PLOT-DATA-SERIES-PROJECTION-METHOD */
Object simple_scatter_plot_data_series_projection_method()
{
    Object gensymed_symbol, data_series_generator_next_tuple_method;
    Object data_point_index, tag_temp, data_point_index_new_value;
    Object data_point_x, data_point_y, data_point_last_x, data_point_last_y;
    Declare_catch(1);
    Declare_special(4);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(177,168);
    Data_point_last_x = Nil;
    Data_point_last_y = Nil;
    Data_point_first_x = Nil;
    Data_point_first_x = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	gensymed_symbol = get(Data_series_source_kind,
		Qdata_series_generator_open_method,_);
	if (inline_funcall_0(gensymed_symbol)) {
	    data_series_generator_next_tuple_method = 
		    get(Data_series_source_kind,
		    Qdata_series_generator_next_tuple_method,_);
	    data_point_index = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Data_point_index,Qdata_point_index,data_point_index,
		    0);
	      tag_temp = UNIQUE_TAG(Qnil);
	      if (PUSH_CATCH(tag_temp,0)) {
		  Data_point_index = FIX((SI_Long)1L);
		next_loop:
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      inline_funcall_0(data_series_generator_next_tuple_method);
		      if ( !TRUEP(Data_point_tuple_valid_qm)) {
			  result = VALUES_1(Nil);
			  THROW(tag_temp,result);
		      }
		      transform_data_tuple_to_device_coordinates();
		      if ( !TRUEP(Data_point_first_x)) {
			  Data_point_first_x = Data_point_x;
			  Data_point_first_y = Data_point_y;
		      }
		      if (Data_point_show_indicator)
			  inline_funcall_0(Data_point_indicator_projection_function);
		      if (Data_point_show_connecting_line)
			  project_connecting_line();
		      Data_point_last_x = Data_point_x;
		      Data_point_last_y = Data_point_y;
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  data_point_index_new_value = FIXNUM_ADD1(Data_point_index);
		  Data_point_index = data_point_index_new_value;
		  goto next_loop;
		end_loop:;
	      }
	      POP_CATCH(0);
	      gensymed_symbol = get(Data_series_source_kind,
		      Qdata_series_generator_close_method,_);
	      inline_funcall_0(gensymed_symbol);
	    POP_SPECIAL();
	}
    }
    POP_LOCAL_ALLOCATION(1,1);
    if (Data_series_connect_first_and_last_point && Data_point_last_x) {
	data_point_x = Data_point_last_x;
	data_point_y = Data_point_last_y;
	data_point_last_x = Data_point_first_x;
	data_point_last_y = Data_point_first_y;
	PUSH_SPECIAL_WITH_SYMBOL(Data_point_last_y,Qdata_point_last_y,data_point_last_y,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Data_point_last_x,Qdata_point_last_x,data_point_last_x,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Data_point_y,Qdata_point_y,data_point_y,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Data_point_x,Qdata_point_x,data_point_x,
		      0);
		result = project_connecting_line();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PROJECT-CONNECTING-LINE */
Object project_connecting_line()
{
    x_note_fn_call(177,169);
    if (Data_point_last_x) {
	chart_move_to(Data_point_last_x,Data_point_last_y);
	return chart_line_to(Data_point_x,Data_point_y);
    }
    else
	return VALUES_1(Nil);
}

Object Chart_data_point_indicator_prop = UNBOUND;

/* FLOOR-SLOT-VALUE-NUMBER-TO-FIXNUM */
Object floor_slot_value_number_to_fixnum(slot_value_number)
    Object slot_value_number;
{
    double temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,170);
    if (FIXNUMP(slot_value_number))
	return VALUES_1(slot_value_number);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	    result = VALUES_1(LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L))));
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = DOUBLE_FLOAT_TO_DOUBLE(slot_value_number);
	    result = VALUES_1(LONG_TO_FIXNUM(inline_floor_1(temp)));
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* PROJECT-RECTANGLE-CHART-INDICATOR */
Object project_rectangle_chart_indicator()
{
    Object width, height, scale, value, w1, w2, h1, h2;
    SI_Long unshifted_result;

    x_note_fn_call(177,171);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    chart_frame_rectangle(FIXNUM_MINUS(Data_point_x,w1),
	    FIXNUM_MINUS(Data_point_y,h1),FIXNUM_ADD(Data_point_x,w2),
	    FIXNUM_ADD(Data_point_y,h2));
    return VALUES_1(Nil);
}

/* PROJECT-TRIANGLE-CHART-INDICATOR */
Object project_triangle_chart_indicator()
{
    Object width, height, scale, value, w1, w2, h1, h2;
    SI_Long unshifted_result;

    x_note_fn_call(177,172);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    chart_move_to(Data_point_x,FIXNUM_MINUS(Data_point_y,h1));
    chart_line(w1,FIXNUM_ADD(h1,h2));
    chart_line(FIXNUM_NEGATE(FIXNUM_ADD(w1,w2)),FIX((SI_Long)0L));
    chart_line(w2,FIXNUM_NEGATE(FIXNUM_ADD(h1,h2)));
    chart_move_to(Data_point_x,Data_point_y);
    return VALUES_1(Nil);
}

/* PROJECT-SQUARE-CHART-INDICATOR */
Object project_square_chart_indicator()
{
    Object width, height, scale, value, w1, w2, h1, h2;
    SI_Long unshifted_result;

    x_note_fn_call(177,173);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    chart_fill_rectangle(FIXNUM_MINUS(Data_point_x,w1),
	    FIXNUM_MINUS(Data_point_y,h1),FIXNUM_ADD(Data_point_x,w2),
	    FIXNUM_ADD(Data_point_y,h2));
    return VALUES_1(Nil);
}

/* PROJECT-CROSS-CHART-INDICATOR */
Object project_cross_chart_indicator()
{
    Object width, height, w, scale, value, w1, h, h1;
    SI_Long unshifted_result;

    x_note_fn_call(177,174);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
	w = width;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_x_scale) && FIXNUM_LT(Current_image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
	    FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_x_scale,width)) 
		+ (SI_Long)2048L;
	w = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w = scalef_function(Current_image_x_scale,width);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
	h = height;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Current_image_y_scale) && FIXNUM_LT(Current_image_y_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,height) && 
	    FIXNUM_LT(height,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(Current_image_y_scale,
		height)) + (SI_Long)2048L;
	h = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h = scalef_function(Current_image_y_scale,height);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    chart_move_to(FIXNUM_MINUS(Data_point_x,w1),Data_point_y);
    chart_line(w,FIX((SI_Long)0L));
    chart_move_to(Data_point_x,FIXNUM_MINUS(Data_point_y,h1));
    chart_line(FIX((SI_Long)0L),h);
    return VALUES_1(Nil);
}

/* PROJECT-X-CHART-INDICATOR */
Object project_x_chart_indicator()
{
    Object width, height, scale, value, w1, w2, h1, h2;
    SI_Long unshifted_result;

    x_note_fn_call(177,175);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    chart_move_to(FIXNUM_MINUS(Data_point_x,w1),FIXNUM_MINUS(Data_point_y,h1));
    chart_line(FIXNUM_ADD(w1,w2),FIXNUM_ADD(h1,h2));
    chart_move_to(FIXNUM_ADD(Data_point_x,w2),FIXNUM_MINUS(Data_point_y,h1));
    chart_line(FIX((SI_Long)0L - IFIX(w1) - IFIX(w2)),FIXNUM_ADD(h1,h2));
    chart_move_to(Data_point_x,Data_point_y);
    return VALUES_1(Nil);
}

/* PROJECT-COLUMN-CHART-INDICATOR */
Object project_column_chart_indicator()
{
    Object width, scale, value, w1, w2;
    SI_Long unshifted_result;

    x_note_fn_call(177,176);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    chart_frame_rectangle(FIXNUM_MINUS(Data_point_x,w1),Data_point_y,
	    FIXNUM_ADD(Data_point_x,w2),FIXNUM_ADD1(Chart_origin_y));
    return VALUES_1(Nil);
}

/* PROJECT-BAR-CHART-INDICATOR */
Object project_bar_chart_indicator()
{
    Object height, scale, value, h1, h2;
    SI_Long unshifted_result;

    x_note_fn_call(177,177);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    chart_frame_rectangle(Chart_origin_x,FIXNUM_MINUS(Data_point_y,h1),
	    Data_point_x,FIXNUM_ADD(Data_point_y,h2));
    return VALUES_1(Nil);
}

/* PROJECT-SOLID-COLUMN-CHART-INDICATOR */
Object project_solid_column_chart_indicator()
{
    Object width, scale, value, w1, w2, bottom, top, bottom_new_value;
    SI_Long unshifted_result;

    x_note_fn_call(177,178);
    width = floor_slot_value_number_to_fixnum(Current_width_of_formatted_part);
    scale = Current_image_x_scale;
    value = ltruncate(width,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	w1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w1 = scalef_function(scale,value);
    scale = Current_image_x_scale;
    value = minus(width,ltruncate(width,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	w2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	w2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	w2 = scalef_function(scale,value);
    bottom = Chart_origin_y;
    top = Data_point_y;
    if (FIXNUM_LT(bottom,top)) {
	bottom_new_value = top;
	top = bottom;
	bottom = bottom_new_value;
    }
    chart_fill_rectangle(FIXNUM_MINUS(Data_point_x,w1),top,
	    FIXNUM_ADD(Data_point_x,w2),FIXNUM_ADD1(bottom));
    return VALUES_1(Nil);
}

/* PROJECT-SOLID-BAR-CHART-INDICATOR */
Object project_solid_bar_chart_indicator()
{
    Object height, scale, value, h1, h2, left, right, right_new_value;
    SI_Long unshifted_result;

    x_note_fn_call(177,179);
    height = 
	    floor_slot_value_number_to_fixnum(Current_height_of_formatted_part);
    scale = Current_image_y_scale;
    value = ltruncate(height,FIX((SI_Long)2L));
    if (IFIX(scale) == (SI_Long)4096L)
	h1 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h1 = scalef_function(scale,value);
    scale = Current_image_y_scale;
    value = minus(height,ltruncate(height,FIX((SI_Long)2L)));
    if (IFIX(scale) == (SI_Long)4096L)
	h2 = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	h2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	h2 = scalef_function(scale,value);
    left = Chart_origin_x;
    right = Data_point_x;
    if (FIXNUM_LT(right,left)) {
	right_new_value = left;
	left = right;
	right = right_new_value;
    }
    chart_fill_rectangle(left,FIXNUM_MINUS(Data_point_y,h1),right,
	    FIXNUM_ADD(Data_point_y,h2));
    return VALUES_1(Nil);
}

/* CHART-FULL-LINE-EAST */
Object chart_full_line_east()
{
    Object scale, value;
    SI_Long gensymed_symbol, unshifted_result;

    x_note_fn_call(177,180);
    scale = Current_image_x_scale;
    value = FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_right,Chart_left),
	    Chart_left_margin),Chart_right_margin);
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
    return chart_line(FIX(gensymed_symbol - (SI_Long)1L),FIX((SI_Long)0L));
}

/* CHART-FULL-LINE-NORTH */
Object chart_full_line_north()
{
    Object scale, value, temp;
    SI_Long unshifted_result;

    x_note_fn_call(177,181);
    scale = Current_image_y_scale;
    value = FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_bottom,Chart_top),
	    Chart_top_margin),Chart_bottom_margin);
    if (IFIX(scale) == (SI_Long)4096L)
	temp = value;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) && 
	    FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
	    FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(scale,value);
    return chart_line(FIX((SI_Long)0L),negate(temp));
}

DEFINE_VARIABLE_WITH_SYMBOL(Tick_mark_part_to_draw, Qtick_mark_part_to_draw);

static Object Qtick_mark;          /* tick-mark */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* PROJECT-AXIS-TICK-MARK-CHART-INDICATOR */
Object project_axis_tick_mark_chart_indicator()
{
    Object draw_grid_p, draw_tick_p, managed_number_or_value, tick_amount;
    Object label, left, top, right, bottom, tick_mark_length, long_tick_p;
    Object label_offset, origin_correction, whole_size, fraction_size;
    Object expt_size, fixed_field_width_qm, temp_2, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_3, pen_x, pen_y, old_color, scale, value;
    SI_Long temp_1, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, unshifted_result;
    char first_tick_qm, temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,182);
    draw_grid_p =  !TRUEP(Tick_mark_part_to_draw) ? T : Nil;
    if (draw_grid_p);
    else
	draw_grid_p = EQ(Tick_mark_part_to_draw,Qgrid) ? T : Nil;
    draw_tick_p =  !TRUEP(Tick_mark_part_to_draw) || 
	    EQ(Tick_mark_part_to_draw,Qtick_mark) ? ( 
	    !(IFIX(Axis_tickmark_label_frequency) == (SI_Long)0L) ? T : 
	    Nil) : Qnil;
    if (IFIX(Axis_tickmark_count_as_fixnum) == (SI_Long)0L) {
	if (draw_tick_p) {
	    chart_move_to(Data_point_x,Data_point_y);
	    if (EQ(Axis_heading,Qeast))
		chart_full_line_east();
	    else if (EQ(Axis_heading,Qnorth))
		chart_full_line_north();
	}
    }
    else if (FIXNUM_LE(Data_point_index,Axis_tickmark_count_as_fixnum)) {
	managed_number_or_value = ISVREF(EQ(Axis_heading,Qeast) ? 
		Data_point_tuple_1 : Data_point_tuple_2,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    tick_amount = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    tick_amount = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    tick_amount = copy_text_string(managed_number_or_value);
	else
	    tick_amount = managed_number_or_value;
	label = Nil;
	left = Nil;
	top = Nil;
	right = Nil;
	bottom = Nil;
	tick_mark_length = FIX((SI_Long)4L);
	long_tick_p = Nil;
	label_offset = FIX((SI_Long)4L);
	origin_correction = FIX((SI_Long)0L);
	first_tick_qm =  !TRUEP(Data_point_last_x);
	whole_size = Axis_tickmark_label_max_digits_before_point;
	fraction_size = Axis_tickmark_label_max_digits_after_point;
	expt_size = Axis_tickmark_label_max_digits_in_exponent;
	fixed_field_width_qm = Nil;
	if (draw_tick_p) {
	    temp = IFIX(Data_point_index) == (SI_Long)1L;
	    if (temp);
	    else {
		temp_1 = IFIX(FIXNUM_SUB1(Data_point_index)) % 
			IFIX(Axis_tickmark_label_frequency);
		temp = (SI_Long)0L == temp_1 ?  
			!FIXNUM_LT(FIXNUM_MINUS(Axis_tickmark_count_as_fixnum,
			Data_point_index),Axis_tickmark_label_frequency) : 
			TRUEP(Nil);
	    }
	    if (temp);
	    else
		temp = FIXNUM_EQ(Data_point_index,
			Axis_tickmark_count_as_fixnum) ?  
			!FIXNUM_LT(Data_point_index,
			Axis_tickmark_label_frequency) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    long_tick_p = T;
	    gensymed_symbol = IFIX(whole_size);
	    gensymed_symbol_1 = IFIX(fraction_size);
	    gensymed_symbol_2 = IFIX(expt_size);
	    gensymed_symbol_3 = IFIX(fraction_size) > (SI_Long)0L ? 
		    (SI_Long)1L : (SI_Long)0L;
	    gensymed_symbol_4 = IFIX(expt_size) > (SI_Long)0L ? 
		    (SI_Long)1L : (SI_Long)0L;
	    fixed_field_width_qm = FIX(gensymed_symbol + gensymed_symbol_1 
		    + gensymed_symbol_2 + gensymed_symbol_3 + 
		    gensymed_symbol_4);
	    if (NUM_EQ(tick_amount,float_constant_1)) {
		temp_2 = FIX((SI_Long)3L);
		temp = NUM_GE(fixed_field_width_qm,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_2 = FIX((SI_Long)0L);
		temp = NUM_EQ(expt_size,temp_2);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? TRUEP(Axis_is_discrete_p) : TRUEP(Nil))
		fixed_field_width_qm = FIX((SI_Long)2L);
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
		      temp_2 = IFIX(expt_size) > (SI_Long)0L ? T : Nil;
		      if (fixed_field_width_qm) {
			  gensymed_symbol = IFIX(fixed_field_width_qm);
			  gensymed_symbol_1 = IFIX(whole_size);
			  gensymed_symbol_2 = IFIX(fraction_size) > 
				  (SI_Long)0L ? 
				  IFIX(FIXNUM_ADD1(fraction_size)) : 
				  (SI_Long)0L;
			  gensymed_symbol_3 = IFIX(expt_size) > 
				  (SI_Long)0L ? (SI_Long)1L : (SI_Long)0L;
			  temp_3 = FIX(gensymed_symbol - gensymed_symbol_1 
				  - gensymed_symbol_2 - gensymed_symbol_3);
		      }
		      else
			  temp_3 = Nil;
		      write_floating_point_number(10,tick_amount,
			      whole_size,fraction_size,Nil,Nil,temp_2,Nil,
			      temp_3,fixed_field_width_qm,FIX((SI_Long)35L));
		      label = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    result = compute_bounding_rectangle_of_text(label);
	    MVS_4(result,left,top,right,bottom);
	}
	chart_move_to(Data_point_x,Data_point_y);
	if (EQ(Axis_heading,Qnorth)) {
	    if (first_tick_qm && draw_tick_p) {
		pen_x = Chart_pen_x;
		pen_y = Chart_pen_y;
		old_color = Chart_pen_color;
		temp_2 = Formatted_part_true_line_color;
		if (temp_2);
		else
		    temp_2 = old_color;
		chart_pen_color(temp_2);
		chart_full_line_north();
		chart_pen_color(old_color);
		Chart_pen_x = pen_x;
		Chart_pen_y = pen_y;
	    }
	    pen_x = Chart_pen_x;
	    pen_y = Chart_pen_y;
	    if (Grid_visible) {
		if (draw_grid_p) {
		    if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			temp_2 = Chart_left_margin;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    Current_image_x_scale) && 
			    FIXNUM_LT(Current_image_x_scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    Chart_left_margin) && 
			    FIXNUM_LT(Chart_left_margin,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = 
				IFIX(FIXNUM_TIMES(Current_image_x_scale,
				Chart_left_margin)) + (SI_Long)2048L;
			temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		    }
		    else
			temp_2 = scalef_function(Current_image_x_scale,
				Chart_left_margin);
		    chart_move_to(temp_2,Chart_pen_y);
		    old_color = Chart_pen_color;
		    temp_2 = Grid_color;
		    if (temp_2);
		    else
			temp_2 = old_color;
		    chart_pen_color(temp_2);
		    chart_full_line_east();
		    chart_pen_color(old_color);
		}
	    }
	    else if (draw_tick_p) {
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			tick_mark_length) && FIXNUM_LT(tick_mark_length,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_x_scale,
			    tick_mark_length)) + (SI_Long)2048L;
		    tick_mark_length = FIX(unshifted_result >>  -  - 
			    (SI_Long)12L);
		}
		else
		    tick_mark_length = 
			    scalef_function(Current_image_x_scale,
			    tick_mark_length);
		if (long_tick_p)
		    tick_mark_length = FIXNUM_ADD1(tick_mark_length);
		chart_line(tick_mark_length,FIX((SI_Long)0L));
	    }
	    Chart_pen_x = pen_x;
	    Chart_pen_y = pen_y;
	    if (label && draw_tick_p) {
		if (IFIX(Current_image_x_scale) == (SI_Long)4096L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_x_scale) && 
			FIXNUM_LT(Current_image_x_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			label_offset) && FIXNUM_LT(label_offset,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_x_scale,
			    label_offset)) + (SI_Long)2048L;
		    label_offset = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    label_offset = scalef_function(Current_image_x_scale,
			    label_offset);
		chart_move(FIX((SI_Long)0L - IFIX(label_offset) - 
			IFIX(right)),
			FIXNUM_NEGATE(ltruncate(FIXNUM_ADD(top,bottom),
			FIX((SI_Long)2L))));
		chart_draw_text(label);
	    }
	}
	else if (EQ(Axis_heading,Qeast)) {
	    if (first_tick_qm && Axis_is_discrete_p) {
		scale = Current_image_x_scale;
		value = ltruncate(Tickmark_label_char_width,_);
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol = IFIX(value);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
		}
		else
		    gensymed_symbol = IFIX(scalef_function(scale,value));
		origin_correction = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    if (first_tick_qm && draw_tick_p) {
		pen_x = Chart_pen_x;
		pen_y = Chart_pen_y;
		old_color = Chart_pen_color;
		temp_2 = Formatted_part_true_line_color;
		if (temp_2);
		else
		    temp_2 = old_color;
		chart_pen_color(temp_2);
		chart_full_line_east();
		chart_pen_color(old_color);
		Chart_pen_x = pen_x;
		Chart_pen_y = pen_y;
	    }
	    pen_x = Chart_pen_x;
	    pen_y = Chart_pen_y;
	    if (Grid_visible) {
		if (draw_grid_p) {
		    temp_2 = Chart_pen_x;
		    scale = Current_image_y_scale;
		    value = FIXNUM_MINUS(Chart_bottom,Chart_bottom_margin);
		    if (IFIX(scale) == (SI_Long)4096L)
			temp_3 = value;
		    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    scale) && FIXNUM_LT(scale,
			    Isqrt_of_most_positive_fixnum) && 
			    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			    value) && FIXNUM_LT(value,
			    Isqrt_of_most_positive_fixnum)) {
			unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) 
				+ (SI_Long)2048L;
			temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
		    }
		    else
			temp_3 = scalef_function(scale,value);
		    chart_move_to(temp_2,temp_3);
		    old_color = Chart_pen_color;
		    temp_2 = Grid_color;
		    if (temp_2);
		    else
			temp_2 = old_color;
		    chart_pen_color(temp_2);
		    chart_full_line_north();
		    chart_pen_color(old_color);
		}
	    }
	    else if (draw_tick_p) {
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			tick_mark_length) && FIXNUM_LT(tick_mark_length,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_y_scale,
			    tick_mark_length)) + (SI_Long)2048L;
		    tick_mark_length = FIX(unshifted_result >>  -  - 
			    (SI_Long)12L);
		}
		else
		    tick_mark_length = 
			    scalef_function(Current_image_y_scale,
			    tick_mark_length);
		if (long_tick_p)
		    tick_mark_length = FIXNUM_ADD1(tick_mark_length);
		chart_line(FIX((SI_Long)0L),FIXNUM_NEGATE(tick_mark_length));
	    }
	    Chart_pen_x = pen_x;
	    Chart_pen_y = pen_y;
	    if (label && draw_tick_p) {
		if (IFIX(Current_image_y_scale) == (SI_Long)4096L);
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			Current_image_y_scale) && 
			FIXNUM_LT(Current_image_y_scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			label_offset) && FIXNUM_LT(label_offset,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = 
			    IFIX(FIXNUM_TIMES(Current_image_y_scale,
			    label_offset)) + (SI_Long)2048L;
		    label_offset = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    label_offset = scalef_function(Current_image_y_scale,
			    label_offset);
		chart_move(FIXNUM_ADD(FIXNUM_NEGATE(ltruncate(FIXNUM_ADD(left,
			right),FIX((SI_Long)2L))),origin_correction),
			FIXNUM_ADD(label_offset,FIXNUM_NEGATE(top)));
		chart_draw_text(label);
	    }
	}
	if (label)
	    reclaim_text_string(label);
    }
    return VALUES_1(Nil);
}

/* TRUNCATE-TICKMARK-LABEL */
Object truncate_tickmark_label(label,width,integer_qm)
    Object label, width, integer_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, char_1, thing, temp_1, schar_arg_2, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,183);
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
	      i = (SI_Long)0L;
	      temp = text_string_length(label);
	      ab_loop_bind_ = IFIX(FIXNUM_SUB1(FIXNUM_MIN(temp,width)));
	      char_1 = Nil;
	    next_loop:
	      if (i > ab_loop_bind_)
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(label,i));
	      if (integer_qm && IFIX(char_1) == (SI_Long)46L)
		  goto end_loop;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = char_1;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = char_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ALIGN-TICKMARK-LABEL */
Object align_tickmark_label(label)
    Object label;
{
    Object whole, fraction, expt_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object max_before, max_after, max_expt, pad, temp, schar_arg_2;
    Object schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_repeat_;
    SI_Long thing, temp_1, i, simple_or_wide_character, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,184);
    result = float_string_field_widths(label);
    MVS_3(result,whole,fraction,expt_1);
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
	      max_before = Axis_tickmark_label_max_digits_before_point;
	      max_after = Axis_tickmark_label_max_digits_after_point;
	      max_expt = Axis_tickmark_label_max_digits_in_exponent;
	      pad = FIXNUM_MINUS(max_before,whole);
	      ab_loop_repeat_ = IFIX(pad) >= (SI_Long)0L ? IFIX(pad) : 
		      (SI_Long)0L;
	    next_loop:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = (SI_Long)32L;
		  twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = (SI_Long)32L;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      goto next_loop;
	    end_loop:
	      temp_1 = IFIX(FIXNUM_NEGATE(pad));
	      i = MAX((SI_Long)0L,temp_1);
	      ab_loop_repeat_ = IFIX(FIXNUM_MIN(max_before,whole));
	    next_loop_1:
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_1;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      simple_or_wide_character = UBYTE_16_ISAREF_1(label,i);
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:;
	      if (IFIX(max_after) > (SI_Long)0L) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)46L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)46L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  i = IFIX(FIXNUM_ADD1(whole));
		  ab_loop_repeat_ = IFIX(FIXNUM_MIN(max_after,fraction));
		next_loop_2:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_2;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  simple_or_wide_character = UBYTE_16_ISAREF_1(label,i);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = simple_or_wide_character;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop_2;
		end_loop_2:;
		  temp_1 = IFIX(FIXNUM_MINUS(max_after,fraction));
		  ab_loop_repeat_ = MAX((SI_Long)0L,temp_1);
		next_loop_3:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_3;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)48L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)48L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  goto next_loop_3;
		end_loop_3:;
	      }
	      if (IFIX(max_expt) > (SI_Long)0L) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)101L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)101L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  ab_loop_repeat_ = IFIX(FIXNUM_MINUS(max_expt,expt_1));
		next_loop_4:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_4;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)48L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)48L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  goto next_loop_4;
		end_loop_4:;
		  gensymed_symbol = IFIX(whole);
		  gensymed_symbol_1 = (SI_Long)1L;
		  gensymed_symbol_2 = IFIX(fraction) > (SI_Long)0L ? 
			  IFIX(FIXNUM_ADD1(fraction)) : (SI_Long)0L;
		  i = gensymed_symbol + gensymed_symbol_1 + gensymed_symbol_2;
		  ab_loop_repeat_ = IFIX(FIXNUM_MIN(max_expt,expt_1));
		next_loop_5:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_5;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  simple_or_wide_character = UBYTE_16_ISAREF_1(label,i);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = simple_or_wide_character;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = simple_or_wide_character;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  i = i + (SI_Long)1L;
		  goto next_loop_5;
		end_loop_5:;
	      }
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qchart_data_point_indicator;  /* chart-data-point-indicator */

static Object Qtriangle;           /* triangle */

/* ENTER-DATA-POINT-INDICATOR-1 */
Object enter_data_point_indicator_1(new_value)
    Object new_value;
{
    Object temp;

    x_note_fn_call(177,185);
    Part_feature_recall_stack = part_stack_cons_1(Data_point_indicator,
	    Part_feature_recall_stack);
    Data_point_indicator = new_value;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(new_value),
	    Qchart_data_point_indicator);
    if (temp);
    else
	temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtriangle),
		Qchart_data_point_indicator);
    Data_point_indicator_projection_function = temp;
    return VALUES_1(Nil);
}

/* EXIT-DATA-POINT-INDICATOR-1 */
Object exit_data_point_indicator_1()
{
    Object part_stack_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object new_value, temp_1;

    x_note_fn_call(177,186);
    part_stack_pop_store = Nil;
    cons_1 = Part_feature_recall_stack;
    if (cons_1) {
	part_stack_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qpart_stack);
	if (ISVREF(Available_part_stack_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_part_stack_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_part_stack_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_part_stack_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    Part_feature_recall_stack = next_cons;
    new_value = part_stack_pop_store;
    Data_point_indicator = new_value;
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(new_value),
	    Qchart_data_point_indicator);
    if (temp_1);
    else
	temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtriangle),
		Qchart_data_point_indicator);
    Data_point_indicator_projection_function = temp_1;
    return VALUES_1(Nil);
}

static Object Qformat_frame;       /* format-frame */

static Object Qdynamic_text_cell_format;  /* dynamic-text-cell-format */

static Object Qmark;               /* mark */

static Object list_constant_1;     /* # */

/* COMPUTE-CHART-STATISTICS */
Object compute_chart_statistics()
{
    volatile Object first_data_point_flag;
    Object part_exceptions_from_parents, chart_top, chart_left;
    Object gensymed_symbol, chart_right, chart_bottom, temp;
    Object current_text_box_format, old_current_part_description, new_cons;
    Object temp_1, svref_arg_2, svref_new_value;
    Object old_current_part_description_1, old_current_part_description_2;
    Object current_data_series, ab_loop_list_, current_computed_data_series;
    Object ab_loop_list__1, data_series_index, ab_loop_iter_flag_;
    Object old_current_part_description_3, old_current_part_description_4;
    Object old_current_part_description_5;
    Object data_series_generator_next_tuple_method, data_point_index, tag_temp;
    Object managed_number_or_value, t1, t2, gensymed_symbol_3;
    Object store_managed_number_or_value_arg, gensymed_symbol_4;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    double gensymed_symbol_5, store_managed_number_or_value_arg_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(9);
    XDeclare_area(3);
    XDeclare_frontier(3);
    Object result;

    x_note_fn_call(177,187);
    SAVE_STACK();
    if (PUSH_LOCAL_ALLOCATION(Local_area,2,2)) {
	first_data_point_flag = T;
	part_exceptions_from_parents = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Part_exceptions_from_parents,Qpart_exceptions_from_parents,part_exceptions_from_parents,
		8);
	  chart_top = FIX((SI_Long)0L);
	  chart_left = FIX((SI_Long)0L);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  chart_right = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  chart_bottom = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	  temp = get_instance_with_name_if_any(Qformat_frame,
		  Qdynamic_text_cell_format);
	  if (temp);
	  else
	      temp = make_format_frame(Qdynamic_text_cell_format);
	  current_text_box_format = temp;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
		  7);
	    PUSH_SPECIAL_WITH_SYMBOL(Chart_bottom,Qchart_bottom,chart_bottom,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Chart_right,Qchart_right,chart_right,5);
		PUSH_SPECIAL_WITH_SYMBOL(Chart_left,Qchart_left,chart_left,4);
		  PUSH_SPECIAL_WITH_SYMBOL(Chart_top,Qchart_top,chart_top,3);
		    old_current_part_description = Current_part_description;
		    gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)19L);
		    Current_part_description = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			    Qchart_part_description_for_chart_style);
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    old_current_part_description_1 = Current_part_description;
		    temp = ISVREF(Current_chart_frame,(SI_Long)21L);
		    if (temp);
		    else
			temp = list_constant_1;
		    Current_part_description = temp;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    old_current_part_description_2 = Current_part_description;
		    temp = 
			    get_lookup_slot_value_given_default(Current_chart_frame,
			    Qcomputed_annotations,Nil);
		    if (temp);
		    else
			temp = list_constant_1;
		    Current_part_description = temp;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    current_data_series = Nil;
		    ab_loop_list_ = Data_series_subparts;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_data_series,Qcurrent_data_series,current_data_series,
			    2);
		      current_computed_data_series = Nil;
		      ab_loop_list__1 = 
			      get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
			      Qcomputed_annotations,Nil),Qsubparts,
			      Qdata_series);
		      data_series_index = FIX((SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
			      1);
			ab_loop_iter_flag_ = T;
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			Current_data_series = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop;
			current_computed_data_series = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			if ( !TRUEP(ab_loop_iter_flag_))
			    Data_series_index = FIXNUM_ADD1(Data_series_index);
			old_current_part_description_3 = 
				Current_part_description;
			Current_part_description = Current_data_series;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			old_current_part_description_4 = 
				Current_part_description;
			Current_part_description = 
				lookup_part_exception(Qdata_series,
				Data_series_index);
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			old_current_part_description_5 = 
				Current_part_description;
			Current_part_description = 
				current_computed_data_series;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
			    gensymed_symbol = get(Data_series_source_kind,
				    Qdata_series_generator_open_method,_);
			    if (inline_funcall_0(gensymed_symbol)) {
				data_series_generator_next_tuple_method = 
					get(Data_series_source_kind,
					Qdata_series_generator_next_tuple_method,
					_);
				data_point_index = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Data_point_index,Qdata_point_index,data_point_index,
					0);
				  tag_temp = UNIQUE_TAG(Qnil);
				  if (PUSH_CATCH(tag_temp,0)) {
				      Data_point_index = FIX((SI_Long)1L);
				    next_loop_1:
				      if (PUSH_LOCAL_ALLOCATION(Local_area,
					      0,0)) {
					  inline_funcall_0(data_series_generator_next_tuple_method);
					  if ( 
						  !TRUEP(Data_point_tuple_valid_qm)) 
						      {
					      result = VALUES_1(Nil);
					      THROW(tag_temp,result);
					  }
					  managed_number_or_value = 
						  ISVREF(Data_point_tuple_1,
						  (SI_Long)1L);
					  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						  != (SI_Long)0L && 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						  == (SI_Long)1L)
					      t1 = 
						      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						      (SI_Long)0L));
					  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						  != (SI_Long)0L && 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						  == (SI_Long)1L)
					      t1 = 
						      aref1(managed_number_or_value,
						      FIX((SI_Long)0L));
					  else if (text_string_p(managed_number_or_value))
					      t1 = 
						      copy_text_string(managed_number_or_value);
					  else
					      t1 = managed_number_or_value;
					  managed_number_or_value = 
						  ISVREF(Data_point_tuple_2,
						  (SI_Long)1L);
					  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						  != (SI_Long)0L && 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						  == (SI_Long)1L)
					      t2 = 
						      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						      (SI_Long)0L));
					  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						  != (SI_Long)0L && 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						  == (SI_Long)1L)
					      t2 = 
						      aref1(managed_number_or_value,
						      FIX((SI_Long)0L));
					  else if (text_string_p(managed_number_or_value))
					      t2 = 
						      copy_text_string(managed_number_or_value);
					  else
					      t2 = managed_number_or_value;
					  if (first_data_point_flag) {
					      first_data_point_flag = Nil;
					      gensymed_symbol = 
						      Chart_tuple_1_minimum;
					      gensymed_symbol_3 = t1;
					      store_managed_number_or_value_arg 
						      = gensymed_symbol_3;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      store_managed_number_or_value_arg);
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_1_maximum;
					      gensymed_symbol_3 = t1;
					      store_managed_number_or_value_arg 
						      = gensymed_symbol_3;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      store_managed_number_or_value_arg);
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_2_minimum;
					      gensymed_symbol_3 = t2;
					      store_managed_number_or_value_arg 
						      = gensymed_symbol_3;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      store_managed_number_or_value_arg);
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_2_maximum;
					      gensymed_symbol_3 = t2;
					      store_managed_number_or_value_arg 
						      = gensymed_symbol_3;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      store_managed_number_or_value_arg);
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					  }
					  else {
					      gensymed_symbol = 
						      Chart_tuple_1_minimum;
					      managed_number_or_value = 
						      ISVREF(Chart_tuple_1_minimum,
						      (SI_Long)1L);
					      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
							  (SI_Long)0L));
					      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  aref1(managed_number_or_value,
							  FIX((SI_Long)0L));
					      else if (text_string_p(managed_number_or_value))
						  gensymed_symbol_3 = 
							  copy_text_string(managed_number_or_value);
					      else
						  gensymed_symbol_3 = 
							  managed_number_or_value;
					      gensymed_symbol_4 = t1;
					      temp = 
						      DOUBLE_FLOAT_MIN(gensymed_symbol_3,
						      gensymed_symbol_4);
					      gensymed_symbol_5 = 
						      DOUBLE_FLOAT_TO_DOUBLE(temp);
					      store_managed_number_or_value_arg_1 
						      = gensymed_symbol_5;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_1_maximum;
					      managed_number_or_value = 
						      ISVREF(Chart_tuple_1_maximum,
						      (SI_Long)1L);
					      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
							  (SI_Long)0L));
					      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  aref1(managed_number_or_value,
							  FIX((SI_Long)0L));
					      else if (text_string_p(managed_number_or_value))
						  gensymed_symbol_3 = 
							  copy_text_string(managed_number_or_value);
					      else
						  gensymed_symbol_3 = 
							  managed_number_or_value;
					      gensymed_symbol_4 = t1;
					      temp = 
						      DOUBLE_FLOAT_MAX(gensymed_symbol_3,
						      gensymed_symbol_4);
					      gensymed_symbol_5 = 
						      DOUBLE_FLOAT_TO_DOUBLE(temp);
					      store_managed_number_or_value_arg_1 
						      = gensymed_symbol_5;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_2_minimum;
					      managed_number_or_value = 
						      ISVREF(Chart_tuple_2_minimum,
						      (SI_Long)1L);
					      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
							  (SI_Long)0L));
					      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  aref1(managed_number_or_value,
							  FIX((SI_Long)0L));
					      else if (text_string_p(managed_number_or_value))
						  gensymed_symbol_3 = 
							  copy_text_string(managed_number_or_value);
					      else
						  gensymed_symbol_3 = 
							  managed_number_or_value;
					      gensymed_symbol_4 = t2;
					      temp = 
						      DOUBLE_FLOAT_MIN(gensymed_symbol_3,
						      gensymed_symbol_4);
					      gensymed_symbol_5 = 
						      DOUBLE_FLOAT_TO_DOUBLE(temp);
					      store_managed_number_or_value_arg_1 
						      = gensymed_symbol_5;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					      gensymed_symbol = 
						      Chart_tuple_2_maximum;
					      managed_number_or_value = 
						      ISVREF(Chart_tuple_2_maximum,
						      (SI_Long)1L);
					      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
							  (SI_Long)0L));
					      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
						      != (SI_Long)0L && 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
						      == (SI_Long)1L)
						  gensymed_symbol_3 = 
							  aref1(managed_number_or_value,
							  FIX((SI_Long)0L));
					      else if (text_string_p(managed_number_or_value))
						  gensymed_symbol_3 = 
							  copy_text_string(managed_number_or_value);
					      else
						  gensymed_symbol_3 = 
							  managed_number_or_value;
					      gensymed_symbol_4 = t2;
					      temp = 
						      DOUBLE_FLOAT_MAX(gensymed_symbol_3,
						      gensymed_symbol_4);
					      gensymed_symbol_5 = 
						      DOUBLE_FLOAT_TO_DOUBLE(temp);
					      store_managed_number_or_value_arg_1 
						      = gensymed_symbol_5;
					      temp_1 = 
						      store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						      (SI_Long)1L),
						      DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
					      SVREF(gensymed_symbol,
						      FIX((SI_Long)1L)) = 
						      temp_1;
					  }
				      }
				      POP_LOCAL_ALLOCATION(0,0);
				      temp_1 = FIXNUM_ADD1(Data_point_index);
				      Data_point_index = temp_1;
				      goto next_loop_1;
				    end_loop_1:;
				  }
				  POP_CATCH(0);
				  gensymed_symbol = 
					  get(Data_series_source_kind,
					  Qdata_series_generator_close_method,
					  _);
				  inline_funcall_0(gensymed_symbol);
				POP_SPECIAL();
			    }
			}
			POP_LOCAL_ALLOCATION(1,1);
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_2:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_2;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_2;
		      end_loop_2:;
			Current_part_description = 
				old_current_part_description_5;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_3:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_3;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_3;
		      end_loop_3:;
			Current_part_description = 
				old_current_part_description_4;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_4:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_4;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_4;
		      end_loop_4:;
			Current_part_description = 
				old_current_part_description_3;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			ab_loop_iter_flag_ = Nil;
			goto next_loop;
		      end_loop:
			SAVE_VALUES(VALUES_1(Qnil));
		      POP_SPECIAL();
		    POP_SPECIAL();
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_5:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_5;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_5;
		  end_loop_5:;
		    Current_part_description = old_current_part_description_2;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_6:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_6;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_6;
		  end_loop_6:;
		    Current_part_description = old_current_part_description_1;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_7:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_7;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_7;
		  end_loop_7:;
		    Current_part_description = old_current_part_description;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    result = RESTORE_VALUES();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(2,2);
    RESTORE_STACK();
    return result;
}

/* TRANSFORM-DATA-TUPLE-TO-DEVICE-COORDINATES */
Object transform_data_tuple_to_device_coordinates()
{
    Object managed_number, a, b, c, d, tx, ty, managed_number_or_value, t1, t2;
    double temp, temp_1, temp_2, temp_3, temp_4;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,188);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	managed_number = ISVREF(The_transform,(SI_Long)0L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    a = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    a = aref1(managed_number,FIX((SI_Long)0L));
	else
	    a = managed_number;
	managed_number = ISVREF(The_transform,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    b = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    b = aref1(managed_number,FIX((SI_Long)0L));
	else
	    b = managed_number;
	managed_number = ISVREF(The_transform,(SI_Long)2L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    c = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    c = aref1(managed_number,FIX((SI_Long)0L));
	else
	    c = managed_number;
	managed_number = ISVREF(The_transform,(SI_Long)3L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    d = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    d = aref1(managed_number,FIX((SI_Long)0L));
	else
	    d = managed_number;
	managed_number = ISVREF(The_transform,(SI_Long)4L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    tx = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    tx = aref1(managed_number,FIX((SI_Long)0L));
	else
	    tx = managed_number;
	managed_number = ISVREF(The_transform,(SI_Long)5L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    ty = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    ty = aref1(managed_number,FIX((SI_Long)0L));
	else
	    ty = managed_number;
	managed_number_or_value = ISVREF(Data_point_tuple_1,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    t1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    t1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    t1 = copy_text_string(managed_number_or_value);
	else
	    t1 = managed_number_or_value;
	managed_number_or_value = ISVREF(Data_point_tuple_2,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    t2 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    t2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    t2 = copy_text_string(managed_number_or_value);
	else
	    t2 = managed_number_or_value;
	temp = DOUBLE_FLOAT_TO_DOUBLE(a);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(t1);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(c);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(t2);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(tx);
	Data_point_x = LONG_TO_FIXNUM(inline_floor_1(temp * temp_1 + 
		temp_2 * temp_3 + temp_4));
	temp = DOUBLE_FLOAT_TO_DOUBLE(b);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(t1);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(d);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(t2);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(ty);
	Data_point_y = LONG_TO_FIXNUM(inline_floor_1(temp * temp_1 + 
		temp_2 * temp_3 + temp_4));
	result = VALUES_1(Data_point_y);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* ASSURE-CHART-TRANSFORM-IS-UPTODATE */
Object assure_chart_transform_is_uptodate()
{
    Object horizontal_axis_minimum, horizontal_axis_maximum;
    Object vertical_axis_minimum, vertical_axis_maximum;
    Object part_exceptions_from_parents, chart_top, chart_left;
    Object gensymed_symbol, chart_right, chart_bottom, temp;
    Object current_text_box_format, old_current_part_description, new_cons;
    Object temp_1, svref_arg_2, svref_new_value;
    Object old_current_part_description_1, old_current_part_description_2;
    Object old_current_part_description_3, current_axis, ab_loop_list_;
    Object axis_index, ab_loop_iter_flag_, old_current_part_description_4;
    Object axis_is_discrete_p, part_feature_index, exit_feature_handler;
    Object part_stack_pop_store, cons_1, next_cons;
    Object chart_horizontal_device_range, chart_vertical_device_range;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    double temp_2, temp_3, chart_horizontal_axis_range;
    double chart_vertical_axis_range;
    Declare_special(9);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,189);
    horizontal_axis_minimum = Nil;
    horizontal_axis_maximum = Nil;
    vertical_axis_minimum = Nil;
    vertical_axis_maximum = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	part_exceptions_from_parents = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Part_exceptions_from_parents,Qpart_exceptions_from_parents,part_exceptions_from_parents,
		8);
	  chart_top = FIX((SI_Long)0L);
	  chart_left = FIX((SI_Long)0L);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  chart_right = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  chart_bottom = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	  temp = get_instance_with_name_if_any(Qformat_frame,
		  Qdynamic_text_cell_format);
	  if (temp);
	  else
	      temp = make_format_frame(Qdynamic_text_cell_format);
	  current_text_box_format = temp;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
		  7);
	    PUSH_SPECIAL_WITH_SYMBOL(Chart_bottom,Qchart_bottom,chart_bottom,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Chart_right,Qchart_right,chart_right,5);
		PUSH_SPECIAL_WITH_SYMBOL(Chart_left,Qchart_left,chart_left,4);
		  PUSH_SPECIAL_WITH_SYMBOL(Chart_top,Qchart_top,chart_top,3);
		    old_current_part_description = Current_part_description;
		    gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)19L);
		    Current_part_description = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			    Qchart_part_description_for_chart_style);
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    old_current_part_description_1 = Current_part_description;
		    temp = ISVREF(Current_chart_frame,(SI_Long)21L);
		    if (temp);
		    else
			temp = list_constant_1;
		    Current_part_description = temp;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    old_current_part_description_2 = Current_part_description;
		    temp = 
			    get_lookup_slot_value_given_default(Current_chart_frame,
			    Qcomputed_annotations,Nil);
		    if (temp);
		    else
			temp = list_constant_1;
		    Current_part_description = temp;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    old_current_part_description_3 = Current_part_description;
		    Current_part_description = 
			    Default_axis_data_series_instance;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			temp_1 = Current_part_description;
			M_CAR(gensymed_symbol) = temp_1;
			temp_1 = Stack_of_current_part_descriptions;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Stack_of_current_part_descriptions = gensymed_symbol;
		    }
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_1 = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_1,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    M_CAR(gensymed_symbol) = Qmark;
		    temp_1 = Part_feature_recall_stack;
		    M_CDR(gensymed_symbol) = temp_1;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Part_feature_recall_stack = gensymed_symbol;
		    enter_part_description(Current_part_description);
		    current_axis = Nil;
		    ab_loop_list_ = 
			    get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
			    Qcomputed_annotations,Nil),Qsubparts,Qaxis);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
			    2);
		      axis_index = FIX((SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,
			      1);
			ab_loop_iter_flag_ = T;
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			Current_axis = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if ( !TRUEP(ab_loop_iter_flag_))
			    Axis_index = FIXNUM_ADD1(Axis_index);
			old_current_part_description_4 = 
				Current_part_description;
			Current_part_description = Current_axis;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    new_cons = 
				    ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_part_stack_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = Nil;
				}
				gensymed_symbol = new_cons;
			    }
			    else
				gensymed_symbol = Nil;
			    if ( !TRUEP(gensymed_symbol))
				gensymed_symbol = 
					replenish_part_stack_cons_pool();
			    temp_1 = Current_part_description;
			    M_CAR(gensymed_symbol) = temp_1;
			    temp_1 = Stack_of_current_part_descriptions;
			    M_CDR(gensymed_symbol) = temp_1;
			    inline_note_allocate_cons(gensymed_symbol,
				    Qpart_stack);
			    Stack_of_current_part_descriptions = 
				    gensymed_symbol;
			}
			new_cons = 
				ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_part_stack_conses_vector,
				    IFIX(Current_thread_index)))) {
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol = new_cons;
			}
			else
			    gensymed_symbol = Nil;
			if ( !TRUEP(gensymed_symbol))
			    gensymed_symbol = replenish_part_stack_cons_pool();
			M_CAR(gensymed_symbol) = Qmark;
			temp_1 = Part_feature_recall_stack;
			M_CDR(gensymed_symbol) = temp_1;
			inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
			Part_feature_recall_stack = gensymed_symbol;
			enter_part_description(Current_part_description);
			axis_is_discrete_p = EQ(Axis_heading,Qeast) ? 
				plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
				: 
				plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
			PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
				0);
			  if (EQ(Axis_heading,Qnorth)) {
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_maximum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_maximum,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(Axis_maximum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				      == (SI_Long)1L)
				  temp = aref1(Axis_maximum,FIX((SI_Long)0L));
			      else
				  temp = Axis_maximum;
			      vertical_axis_maximum = lfloat(temp,
				      float_constant_1);
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_minimum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_minimum,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(Axis_minimum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
				      == (SI_Long)1L)
				  temp = aref1(Axis_minimum,FIX((SI_Long)0L));
			      else
				  temp = Axis_minimum;
			      vertical_axis_minimum = lfloat(temp,
				      float_constant_1);
			  }
			  else if (EQ(Axis_heading,Qeast)) {
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_maximum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_maximum,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(Axis_maximum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				      == (SI_Long)1L)
				  temp = aref1(Axis_maximum,FIX((SI_Long)0L));
			      else
				  temp = Axis_maximum;
			      horizontal_axis_maximum = lfloat(temp,
				      float_constant_1);
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_minimum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_minimum,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(Axis_minimum) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
				      == (SI_Long)1L)
				  temp = aref1(Axis_minimum,FIX((SI_Long)0L));
			      else
				  temp = Axis_minimum;
			      horizontal_axis_minimum = lfloat(temp,
				      float_constant_1);
			  }
			POP_SPECIAL();
			part_feature_index = Nil;
			exit_feature_handler = Nil;
		      next_loop_1:
			part_stack_pop_store = Nil;
			cons_1 = Part_feature_recall_stack;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Part_feature_recall_stack = next_cons;
			part_feature_index = part_stack_pop_store;
			if (EQ(part_feature_index,Qmark))
			    goto end_loop_1;
			exit_feature_handler = 
				ISVREF(Part_feature_exit_methods,
				IFIX(part_feature_index));
			inline_funcall_0(exit_feature_handler);
			goto next_loop_1;
		      end_loop_1:;
			Current_part_description = 
				old_current_part_description_4;
			if (Maintain_stack_of_current_part_descriptions_p) {
			    part_stack_pop_store = Nil;
			    cons_1 = Stack_of_current_part_descriptions;
			    if (cons_1) {
				part_stack_pop_store = M_CAR(cons_1);
				next_cons = M_CDR(cons_1);
				inline_note_reclaim_cons(cons_1,Qpart_stack);
				if (ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index))) {
				    temp_1 = 
					    ISVREF(Available_part_stack_conses_tail_vector,
					    IFIX(Current_thread_index));
				    M_CDR(temp_1) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				else {
				    temp_1 = 
					    Available_part_stack_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				    temp_1 = 
					    Available_part_stack_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = cons_1;
				}
				M_CDR(cons_1) = Nil;
			    }
			    else
				next_cons = Nil;
			    Stack_of_current_part_descriptions = next_cons;
			}
			ab_loop_iter_flag_ = Nil;
			goto next_loop;
		      end_loop:;
		      POP_SPECIAL();
		    POP_SPECIAL();
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_2:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_2;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_2;
		  end_loop_2:;
		    Current_part_description = old_current_part_description_3;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_3:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_3;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_3;
		  end_loop_3:;
		    Current_part_description = old_current_part_description_2;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_4:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_4;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_4;
		  end_loop_4:;
		    Current_part_description = old_current_part_description_1;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		    part_feature_index = Nil;
		    exit_feature_handler = Nil;
		  next_loop_5:
		    part_stack_pop_store = Nil;
		    cons_1 = Part_feature_recall_stack;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_1 = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_1) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			else {
			    temp_1 = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			    temp_1 = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_1,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Part_feature_recall_stack = next_cons;
		    part_feature_index = part_stack_pop_store;
		    if (EQ(part_feature_index,Qmark))
			goto end_loop_5;
		    exit_feature_handler = 
			    ISVREF(Part_feature_exit_methods,
			    IFIX(part_feature_index));
		    inline_funcall_0(exit_feature_handler);
		    goto next_loop_5;
		  end_loop_5:;
		    Current_part_description = old_current_part_description;
		    if (Maintain_stack_of_current_part_descriptions_p) {
			part_stack_pop_store = Nil;
			cons_1 = Stack_of_current_part_descriptions;
			if (cons_1) {
			    part_stack_pop_store = M_CAR(cons_1);
			    next_cons = M_CDR(cons_1);
			    inline_note_reclaim_cons(cons_1,Qpart_stack);
			    if (ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_1 = 
					ISVREF(Available_part_stack_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_1) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    else {
				temp_1 = Available_part_stack_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
				temp_1 = 
					Available_part_stack_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = cons_1;
			    }
			    M_CDR(cons_1) = Nil;
			}
			else
			    next_cons = Nil;
			Stack_of_current_part_descriptions = next_cons;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	chart_horizontal_device_range = 
		FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_right,
		Chart_left),Chart_left_margin),Chart_right_margin);
	chart_vertical_device_range = 
		FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_bottom,
		Chart_top),Chart_top_margin),Chart_bottom_margin);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(horizontal_axis_maximum);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(horizontal_axis_minimum);
	chart_horizontal_axis_range = temp_2 - temp_3;
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(vertical_axis_maximum);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(vertical_axis_minimum);
	chart_vertical_axis_range = temp_2 - temp_3;
	indentity_transform_matrix();
	temp = lfloat(Current_image_x_scale,float_constant_1);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(Current_image_y_scale,float_constant_1);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	scale_transform_matrix(DOUBLE_TO_DOUBLE_FLOAT(temp_3 / 
		(double)(SI_Long)4096L),DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
		(double)(SI_Long)4096L));
	offset_transform_matrix(lfloat(Chart_left_margin,float_constant_1),
		DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_ADD(chart_vertical_device_range,
		Chart_top_margin))));
	scale_transform_matrix(float_constant,float_constant_3);
	scale_transform_matrix(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(chart_horizontal_device_range) 
		/ chart_horizontal_axis_range),
		DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(chart_vertical_device_range) 
		/ chart_vertical_axis_range));
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(horizontal_axis_minimum);
	temp = DOUBLE_TO_DOUBLE_FLOAT( - temp_3);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(vertical_axis_minimum);
	result = offset_transform_matrix(temp,DOUBLE_TO_DOUBLE_FLOAT( - 
		temp_3));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qpolychrome_raster;  /* polychrome-raster */

static Object Qmonochrome_raster_list;  /* monochrome-raster-list */

static Object Qblack;              /* black */

static Object Qbackground_color;   /* background-color */

static Object Qdata_series_projection_method;  /* data-series-projection-method */

/* PROJECT-CHART */
Object project_chart()
{
    Object chart_really_drawing, chart_current_raster_is_polychrome_p;
    Object chart_current_raster_is_monochrome_raster_list_p, chart_pen_x;
    Object chart_pen_y, chart_pen_color_1, chart_pen_color_value, temp;
    Object color_or_metacolor, temp_1, scale, gensymed_symbol, value, temp_2;
    Object w1, h1, part_exceptions_from_parents, chart_top, chart_left;
    Object chart_right, chart_bottom, current_text_box_format;
    Object old_current_part_description, new_cons, svref_new_value;
    Object old_current_part_description_1, old_current_part_description_2;
    Object data_series_subparts, chart_origin_x, chart_origin_y, grids_visible;
    Object axis, ab_loop_list_, ab_loop_it_, tick_mark_part_to_draw;
    Object old_current_part_description_3, current_axis, axis_index;
    Object ab_loop_iter_flag_, old_current_part_description_4;
    Object axis_is_discrete_p, part_feature_index, exit_feature_handler;
    Object part_stack_pop_store, cons_1, next_cons, current_data_series;
    Object current_computed_data_series, ab_loop_list__1, data_series_index;
    Object old_current_part_description_5;
    SI_Long gensymed_symbol_1, unshifted_result, gensymed_symbol_2, width;
    SI_Long height, w2, h2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(20);
    Object result;

    x_note_fn_call(177,190);
    SAVE_STACK();
    LOCK(Chart_drawing);
    if (PUSH_UNWIND_PROTECT(0)) {
	chart_really_drawing = T;
	PUSH_SPECIAL_WITH_SYMBOL(Chart_really_drawing,Qchart_really_drawing,chart_really_drawing,
		19);
	  chart_current_raster_is_polychrome_p = 
		  EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		  Qpolychrome_raster) ? T : Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Chart_current_raster_is_polychrome_p,Qchart_current_raster_is_polychrome_p,chart_current_raster_is_polychrome_p,
		  18);
	    chart_current_raster_is_monochrome_raster_list_p = 
		    EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		    Qmonochrome_raster_list) ? T : Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Chart_current_raster_is_monochrome_raster_list_p,Qchart_current_raster_is_monochrome_raster_list_p,chart_current_raster_is_monochrome_raster_list_p,
		    17);
	      chart_pen_x = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_x,Qchart_pen_x,chart_pen_x,
		      16);
		chart_pen_y = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_y,Qchart_pen_y,chart_pen_y,
			15);
		  chart_pen_color_1 = Qblack;
		  PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color,Qchart_pen_color,chart_pen_color_1,
			  14);
		    chart_pen_color_value = Chart_really_drawing ? 
			    map_to_color_value(Qblack) : FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color_value,Qchart_pen_color_value,chart_pen_color_value,
			    13);
		      if (Chart_current_raster_is_monochrome_raster_list_p 
			      || Chart_current_raster_is_polychrome_p)
			  Chart_color_value_for_this_raster = 
				  Chart_pen_color_value;
		      else if (FIXNUM_EQ(Current_chart_raster_color_value,
			      Chart_pen_color_value))
			  Chart_color_value_for_this_raster = FIX((SI_Long)1L);
		      else
			  Chart_color_value_for_this_raster = FIX((SI_Long)0L);
		      temp = Current_graph_rendering;
		      color_or_metacolor = 
			      get_simple_part_feature(ISVREF(Current_chart_frame,
			      (SI_Long)21L),Qbackground_color);
		      if (color_or_metacolor);
		      else
			  color_or_metacolor = Qwhite;
		      if (EQ(color_or_metacolor,Qbackground))
			  temp_1 = Current_background_color_value;
		      else if (EQ(color_or_metacolor,Qforeground) || 
			      EQ(color_or_metacolor,Qworkspace_foreground))
			  temp_1 = Current_foreground_color_value;
		      else if (EQ(color_or_metacolor,Qtransparent))
			  temp_1 = Current_background_color_value;
		      else
			  temp_1 = map_to_color_value(color_or_metacolor);
		      SVREF(temp,FIX((SI_Long)9L)) = temp_1;
		      scale = Current_image_x_scale;
		      gensymed_symbol = ISVREF(Current_chart_frame,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)2L) : 
			      FIX((SI_Long)0L);
		      value = gensymed_symbol;
		      if (IFIX(scale) == (SI_Long)4096L)
			  gensymed_symbol_1 = IFIX(value);
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      scale) && FIXNUM_LT(scale,
			      Isqrt_of_most_positive_fixnum) && 
			      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_1 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_1 = IFIX(scalef_function(scale,
				  value));
		      scale = Current_image_x_scale;
		      gensymed_symbol = ISVREF(Current_chart_frame,
			      (SI_Long)14L);
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
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_2 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_2 = IFIX(scalef_function(scale,
				  value));
		      width = gensymed_symbol_1 - gensymed_symbol_2;
		      scale = Current_image_y_scale;
		      gensymed_symbol = ISVREF(Current_chart_frame,
			      (SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)3L) : 
			      FIX((SI_Long)0L);
		      value = gensymed_symbol;
		      if (IFIX(scale) == (SI_Long)4096L)
			  gensymed_symbol_1 = IFIX(value);
		      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      scale) && FIXNUM_LT(scale,
			      Isqrt_of_most_positive_fixnum) && 
			      FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			      value) && FIXNUM_LT(value,
			      Isqrt_of_most_positive_fixnum)) {
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_1 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_1 = IFIX(scalef_function(scale,
				  value));
		      scale = Current_image_y_scale;
		      gensymed_symbol = ISVREF(Current_chart_frame,
			      (SI_Long)14L);
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
			  unshifted_result = IFIX(FIXNUM_TIMES(scale,
				  value)) + (SI_Long)2048L;
			  gensymed_symbol_2 = unshifted_result >>  -  - 
				  (SI_Long)12L;
		      }
		      else
			  gensymed_symbol_2 = IFIX(scalef_function(scale,
				  value));
		      height = gensymed_symbol_1 - gensymed_symbol_2;
		      temp_2 = ISVREF(Current_chart_frame,(SI_Long)8L);
		      if ( !( !TRUEP(CAR(temp_2)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(Current_chart_frame,
			      (SI_Long)5L)) & (SI_Long)1L) ||  
			      !TRUEP(Inside_breakpoint_p) && (SI_Long)0L 
			      != (IFIX(ISVREF(Current_chart_frame,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != 
			      (IFIX(ISVREF(Current_chart_frame,
			      (SI_Long)4L)) & (SI_Long)8192L)))) ||  
			      !TRUEP(get_lookup_slot_value_given_default(Current_chart_frame,
			      Qcomputed_annotations,Nil))) {
			  w1 = l_round(FIX(width),FIX((SI_Long)12L));
			  h1 = l_round(FIX(height),FIX((SI_Long)12L));
			  w2 = (SI_Long)10L * IFIX(w1);
			  h2 = (SI_Long)10L * IFIX(h1);
			  chart_frame_rectangle(FIX((SI_Long)0L),
				  FIX((SI_Long)0L),FIX(width),FIX(height));
			  chart_move_to(FIXNUM_ADD(w1,w1),h1);
			  chart_line(FIX((SI_Long)0L),FIX(h2));
			  chart_move(FIXNUM_NEGATE(w1),FIXNUM_NEGATE(h1));
			  SAVE_VALUES(chart_line(FIX(w2),FIX((SI_Long)0L)));
		      }
		      else {
			  part_exceptions_from_parents = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Part_exceptions_from_parents,Qpart_exceptions_from_parents,part_exceptions_from_parents,
				  12);
			    chart_top = FIX((SI_Long)0L);
			    chart_left = FIX((SI_Long)0L);
			    gensymed_symbol = ISVREF(Current_chart_frame,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)2L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_1 = IFIX(gensymed_symbol);
			    gensymed_symbol = ISVREF(Current_chart_frame,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)0L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_2 = IFIX(gensymed_symbol);
			    chart_right = FIX(gensymed_symbol_1 - 
				    gensymed_symbol_2);
			    gensymed_symbol = ISVREF(Current_chart_frame,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)3L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_1 = IFIX(gensymed_symbol);
			    gensymed_symbol = ISVREF(Current_chart_frame,
				    (SI_Long)14L);
			    gensymed_symbol = gensymed_symbol ? 
				    ISVREF(gensymed_symbol,(SI_Long)1L) : 
				    FIX((SI_Long)0L);
			    gensymed_symbol_2 = IFIX(gensymed_symbol);
			    chart_bottom = FIX(gensymed_symbol_1 - 
				    gensymed_symbol_2);
			    temp_2 = 
				    get_instance_with_name_if_any(Qformat_frame,
				    Qdynamic_text_cell_format);
			    if (temp_2);
			    else
				temp_2 = 
					make_format_frame(Qdynamic_text_cell_format);
			    current_text_box_format = temp_2;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
				    11);
			      PUSH_SPECIAL_WITH_SYMBOL(Chart_bottom,Qchart_bottom,chart_bottom,
				      10);
				PUSH_SPECIAL_WITH_SYMBOL(Chart_right,Qchart_right,chart_right,
					9);
				  PUSH_SPECIAL_WITH_SYMBOL(Chart_left,Qchart_left,chart_left,
					  8);
				    PUSH_SPECIAL_WITH_SYMBOL(Chart_top,Qchart_top,chart_top,
					    7);
				      old_current_part_description = 
					      Current_part_description;
				      gensymed_symbol = 
					      ISVREF(Current_chart_frame,
					      (SI_Long)19L);
				      Current_part_description = 
					      getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
					      Qchart_part_description_for_chart_style);
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  new_cons = 
						  ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(temp,temp_1) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_part_stack_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = Nil;
					      }
					      gensymed_symbol = new_cons;
					  }
					  else
					      gensymed_symbol = Nil;
					  if ( !TRUEP(gensymed_symbol))
					      gensymed_symbol = 
						      replenish_part_stack_cons_pool();
					  temp = Current_part_description;
					  M_CAR(gensymed_symbol) = temp;
					  temp = 
						  Stack_of_current_part_descriptions;
					  M_CDR(gensymed_symbol) = temp;
					  inline_note_allocate_cons(gensymed_symbol,
						  Qpart_stack);
					  Stack_of_current_part_descriptions 
						  = gensymed_symbol;
				      }
				      new_cons = 
					      ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp = 
						  Available_part_stack_conses_vector;
					  temp_1 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(temp,temp_1) = svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = Nil;
					  }
					  gensymed_symbol = new_cons;
				      }
				      else
					  gensymed_symbol = Nil;
				      if ( !TRUEP(gensymed_symbol))
					  gensymed_symbol = 
						  replenish_part_stack_cons_pool();
				      M_CAR(gensymed_symbol) = Qmark;
				      temp = Part_feature_recall_stack;
				      M_CDR(gensymed_symbol) = temp;
				      inline_note_allocate_cons(gensymed_symbol,
					      Qpart_stack);
				      Part_feature_recall_stack = 
					      gensymed_symbol;
				      enter_part_description(Current_part_description);
				      old_current_part_description_1 = 
					      Current_part_description;
				      temp_2 = ISVREF(Current_chart_frame,
					      (SI_Long)21L);
				      if (temp_2);
				      else
					  temp_2 = list_constant_1;
				      Current_part_description = temp_2;
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  new_cons = 
						  ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(temp,temp_1) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_part_stack_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = Nil;
					      }
					      gensymed_symbol = new_cons;
					  }
					  else
					      gensymed_symbol = Nil;
					  if ( !TRUEP(gensymed_symbol))
					      gensymed_symbol = 
						      replenish_part_stack_cons_pool();
					  temp = Current_part_description;
					  M_CAR(gensymed_symbol) = temp;
					  temp = 
						  Stack_of_current_part_descriptions;
					  M_CDR(gensymed_symbol) = temp;
					  inline_note_allocate_cons(gensymed_symbol,
						  Qpart_stack);
					  Stack_of_current_part_descriptions 
						  = gensymed_symbol;
				      }
				      new_cons = 
					      ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp = 
						  Available_part_stack_conses_vector;
					  temp_1 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(temp,temp_1) = svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = Nil;
					  }
					  gensymed_symbol = new_cons;
				      }
				      else
					  gensymed_symbol = Nil;
				      if ( !TRUEP(gensymed_symbol))
					  gensymed_symbol = 
						  replenish_part_stack_cons_pool();
				      M_CAR(gensymed_symbol) = Qmark;
				      temp = Part_feature_recall_stack;
				      M_CDR(gensymed_symbol) = temp;
				      inline_note_allocate_cons(gensymed_symbol,
					      Qpart_stack);
				      Part_feature_recall_stack = 
					      gensymed_symbol;
				      enter_part_description(Current_part_description);
				      old_current_part_description_2 = 
					      Current_part_description;
				      temp_2 = 
					      get_lookup_slot_value_given_default(Current_chart_frame,
					      Qcomputed_annotations,Nil);
				      if (temp_2);
				      else
					  temp_2 = list_constant_1;
				      Current_part_description = temp_2;
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  new_cons = 
						  ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(temp,temp_1) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_part_stack_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = Nil;
					      }
					      gensymed_symbol = new_cons;
					  }
					  else
					      gensymed_symbol = Nil;
					  if ( !TRUEP(gensymed_symbol))
					      gensymed_symbol = 
						      replenish_part_stack_cons_pool();
					  temp = Current_part_description;
					  M_CAR(gensymed_symbol) = temp;
					  temp = 
						  Stack_of_current_part_descriptions;
					  M_CDR(gensymed_symbol) = temp;
					  inline_note_allocate_cons(gensymed_symbol,
						  Qpart_stack);
					  Stack_of_current_part_descriptions 
						  = gensymed_symbol;
				      }
				      new_cons = 
					      ISVREF(Available_part_stack_conses_vector,
					      IFIX(Current_thread_index));
				      if (new_cons) {
					  temp = 
						  Available_part_stack_conses_vector;
					  temp_1 = Current_thread_index;
					  svref_new_value = M_CDR(new_cons);
					  SVREF(temp,temp_1) = svref_new_value;
					  if ( 
						  !TRUEP(ISVREF(Available_part_stack_conses_vector,
						  IFIX(Current_thread_index)))) 
						      {
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = Nil;
					  }
					  gensymed_symbol = new_cons;
				      }
				      else
					  gensymed_symbol = Nil;
				      if ( !TRUEP(gensymed_symbol))
					  gensymed_symbol = 
						  replenish_part_stack_cons_pool();
				      M_CAR(gensymed_symbol) = Qmark;
				      temp = Part_feature_recall_stack;
				      M_CDR(gensymed_symbol) = temp;
				      inline_note_allocate_cons(gensymed_symbol,
					      Qpart_stack);
				      Part_feature_recall_stack = 
					      gensymed_symbol;
				      enter_part_description(Current_part_description);
				      if (Chart_current_raster_is_polychrome_p) 
						  {
					  chart_pen_color(ISVREF(Current_text_box_format,
						  (SI_Long)24L));
					  chart_fill_rectangle(FIX((SI_Long)0L),
						  FIX((SI_Long)0L),
						  FIX(width),FIX(height));
				      }
				      temp_2 = 
					      ISVREF(Current_text_box_format,
					      (SI_Long)48L);
				      if (temp_2);
				      else
					  temp_2 = Qblack;
				      chart_pen_color(temp_2);
				      chart_frame_rectangle(FIX((SI_Long)0L),
					      FIX((SI_Long)0L),FIX(width),
					      FIX(height));
				      data_series_subparts = 
					      ISVREF(Current_chart_frame,
					      (SI_Long)20L);
				      chart_origin_x = Nil;
				      chart_origin_y = Nil;
				      grids_visible = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Chart_origin_y,Qchart_origin_y,chart_origin_y,
					      6);
					PUSH_SPECIAL_WITH_SYMBOL(Chart_origin_x,Qchart_origin_x,chart_origin_x,
						5);
					  PUSH_SPECIAL_WITH_SYMBOL(Data_series_subparts,Qdata_series_subparts,data_series_subparts,
						  4);
					    chart_pen_color(Formatted_part_true_line_color);
					    assure_chart_transform_is_uptodate();
					    temp_2 = Grid_visible;
					    if (temp_2);
					    else {
						axis = Nil;
						ab_loop_list_ = 
							get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							Qcomputed_annotations,
							Nil),Qsubparts,Qaxis);
						PUSH_SPECIAL_WITH_SYMBOL(Axis,Qaxis,axis,
							0);
						  ab_loop_it_ = Nil;
						next_loop:
						  if ( !TRUEP(ab_loop_list_))
						      goto end_loop;
						  Axis = M_CAR(ab_loop_list_);
						  ab_loop_list_ = 
							  M_CDR(ab_loop_list_);
						  ab_loop_it_ = 
							  get_simple_part_feature(Axis,
							  Qgrid_visible);
						  if (ab_loop_it_) {
						      temp_2 = ab_loop_it_;
						      goto end_1;
						  }
						  goto next_loop;
						end_loop:
						  temp_2 = Qnil;
						end_1:;
						POP_SPECIAL();
					    }
					    grids_visible = temp_2;
					    if (grids_visible) {
						tick_mark_part_to_draw = Qgrid;
						PUSH_SPECIAL_WITH_SYMBOL(Tick_mark_part_to_draw,Qtick_mark_part_to_draw,tick_mark_part_to_draw,
							3);
						  chart_pen_color(Formatted_part_true_line_color);
						  old_current_part_description_3 
							  = 
							  Current_part_description;
						  Current_part_description 
							  = 
							  Default_axis_data_series_instance;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      temp = 
							      Current_part_description;
						      M_CAR(gensymed_symbol) 
							      = temp;
						      temp = 
							      Stack_of_current_part_descriptions;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Stack_of_current_part_descriptions 
							      = 
							      gensymed_symbol;
						  }
						  new_cons = 
							  ISVREF(Available_part_stack_conses_vector,
							  IFIX(Current_thread_index));
						  if (new_cons) {
						      temp = 
							      Available_part_stack_conses_vector;
						      temp_1 = 
							      Current_thread_index;
						      svref_new_value = 
							      M_CDR(new_cons);
						      SVREF(temp,temp_1) = 
							      svref_new_value;
						      if ( 
							      !TRUEP(ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index)))) 
								  {
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = Nil;
						      }
						      gensymed_symbol = 
							      new_cons;
						  }
						  else
						      gensymed_symbol = Nil;
						  if ( !TRUEP(gensymed_symbol))
						      gensymed_symbol = 
							      replenish_part_stack_cons_pool();
						  M_CAR(gensymed_symbol) = 
							  Qmark;
						  temp = 
							  Part_feature_recall_stack;
						  M_CDR(gensymed_symbol) = 
							  temp;
						  inline_note_allocate_cons(gensymed_symbol,
							  Qpart_stack);
						  Part_feature_recall_stack 
							  = gensymed_symbol;
						  enter_part_description(Current_part_description);
						  current_axis = Nil;
						  ab_loop_list_ = 
							  get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							  Qcomputed_annotations,
							  Nil),Qsubparts,
							  Qaxis);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
							  2);
						    axis_index = 
							    FIX((SI_Long)1L);
						    PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,
							    1);
						      ab_loop_iter_flag_ = T;
						    next_loop_1:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_1;
						      Current_axis = 
							      M_CAR(ab_loop_list_);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if ( 
							      !TRUEP(ab_loop_iter_flag_))
							  Axis_index = 
								  FIXNUM_ADD1(Axis_index);
						      old_current_part_description_4 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = Current_axis;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      axis_is_discrete_p = 
							      EQ(Axis_heading,
							      Qeast) ? 
							      plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
							      : 
							      plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
						      PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
							      0);
							FUNCALL_0(get(Data_series_illustration_kind,
								Qdata_series_projection_method,
								_));
						      POP_SPECIAL();
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_2:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_2;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_2;
						    end_loop_2:;
						      Current_part_description 
							      = 
							      old_current_part_description_4;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      ab_loop_iter_flag_ = Nil;
						      goto next_loop_1;
						    end_loop_1:;
						    POP_SPECIAL();
						  POP_SPECIAL();
						  part_feature_index = Nil;
						  exit_feature_handler = Nil;
						next_loop_3:
						  part_stack_pop_store = Nil;
						  cons_1 = 
							  Part_feature_recall_stack;
						  if (cons_1) {
						      part_stack_pop_store 
							      = M_CAR(cons_1);
						      next_cons = 
							      M_CDR(cons_1);
						      inline_note_reclaim_cons(cons_1,
							      Qpart_stack);
						      if (ISVREF(Available_part_stack_conses_tail_vector,
							      IFIX(Current_thread_index))) 
								  {
							  temp = 
								  ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index));
							  M_CDR(temp) = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      else {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      M_CDR(cons_1) = Nil;
						  }
						  else
						      next_cons = Nil;
						  Part_feature_recall_stack 
							  = next_cons;
						  part_feature_index = 
							  part_stack_pop_store;
						  if (EQ(part_feature_index,
							  Qmark))
						      goto end_loop_3;
						  exit_feature_handler = 
							  ISVREF(Part_feature_exit_methods,
							  IFIX(part_feature_index));
						  inline_funcall_0(exit_feature_handler);
						  goto next_loop_3;
						end_loop_3:;
						  Current_part_description 
							  = 
							  old_current_part_description_3;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Stack_of_current_part_descriptions;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Stack_of_current_part_descriptions 
							      = next_cons;
						  }
						  current_data_series = Nil;
						  ab_loop_list_ = 
							  Data_series_subparts;
						  PUSH_SPECIAL_WITH_SYMBOL(Current_data_series,Qcurrent_data_series,current_data_series,
							  1);
						    current_computed_data_series 
							    = Nil;
						    ab_loop_list__1 = 
							    get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							    Qcomputed_annotations,
							    Nil),Qsubparts,
							    Qdata_series);
						    data_series_index = 
							    FIX((SI_Long)1L);
						    PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
							    0);
						      ab_loop_iter_flag_ = T;
						    next_loop_4:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_4;
						      Current_data_series 
							      = 
							      M_CAR(ab_loop_list_);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if ( 
							      !TRUEP(ab_loop_list__1))
							  goto end_loop_4;
						      current_computed_data_series 
							      = 
							      M_CAR(ab_loop_list__1);
						      ab_loop_list__1 = 
							      M_CDR(ab_loop_list__1);
						      if ( 
							      !TRUEP(ab_loop_iter_flag_))
							  Data_series_index 
								  = 
								  FIXNUM_ADD1(Data_series_index);
						      old_current_part_description_3 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = 
							      Current_data_series;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      old_current_part_description_4 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = 
							      lookup_part_exception(Qdata_series,
							      Data_series_index);
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      old_current_part_description_5 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = 
							      current_computed_data_series;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      chart_pen_color(Formatted_part_true_line_color);
						      FUNCALL_0(get(Data_series_illustration_kind,
							      Qdata_series_projection_method,
							      _));
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_5:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_5;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_5;
						    end_loop_5:;
						      Current_part_description 
							      = 
							      old_current_part_description_5;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_6:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_6;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_6;
						    end_loop_6:;
						      Current_part_description 
							      = 
							      old_current_part_description_4;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_7:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_7;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_7;
						    end_loop_7:;
						      Current_part_description 
							      = 
							      old_current_part_description_3;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      ab_loop_iter_flag_ = Nil;
						      goto next_loop_4;
						    end_loop_4:;
						    POP_SPECIAL();
						  POP_SPECIAL();
						  Tick_mark_part_to_draw = 
							  Qtick_mark;
						  old_current_part_description_3 
							  = 
							  Current_part_description;
						  Current_part_description 
							  = 
							  Default_axis_data_series_instance;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      temp = 
							      Current_part_description;
						      M_CAR(gensymed_symbol) 
							      = temp;
						      temp = 
							      Stack_of_current_part_descriptions;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Stack_of_current_part_descriptions 
							      = 
							      gensymed_symbol;
						  }
						  new_cons = 
							  ISVREF(Available_part_stack_conses_vector,
							  IFIX(Current_thread_index));
						  if (new_cons) {
						      temp = 
							      Available_part_stack_conses_vector;
						      temp_1 = 
							      Current_thread_index;
						      svref_new_value = 
							      M_CDR(new_cons);
						      SVREF(temp,temp_1) = 
							      svref_new_value;
						      if ( 
							      !TRUEP(ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index)))) 
								  {
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = Nil;
						      }
						      gensymed_symbol = 
							      new_cons;
						  }
						  else
						      gensymed_symbol = Nil;
						  if ( !TRUEP(gensymed_symbol))
						      gensymed_symbol = 
							      replenish_part_stack_cons_pool();
						  M_CAR(gensymed_symbol) = 
							  Qmark;
						  temp = 
							  Part_feature_recall_stack;
						  M_CDR(gensymed_symbol) = 
							  temp;
						  inline_note_allocate_cons(gensymed_symbol,
							  Qpart_stack);
						  Part_feature_recall_stack 
							  = gensymed_symbol;
						  enter_part_description(Current_part_description);
						  current_axis = Nil;
						  ab_loop_list_ = 
							  get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							  Qcomputed_annotations,
							  Nil),Qsubparts,
							  Qaxis);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
							  2);
						    axis_index = 
							    FIX((SI_Long)1L);
						    PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,
							    1);
						      ab_loop_iter_flag_ = T;
						    next_loop_8:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_8;
						      Current_axis = 
							      M_CAR(ab_loop_list_);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if ( 
							      !TRUEP(ab_loop_iter_flag_))
							  Axis_index = 
								  FIXNUM_ADD1(Axis_index);
						      old_current_part_description_4 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = Current_axis;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      axis_is_discrete_p = 
							      EQ(Axis_heading,
							      Qeast) ? 
							      plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
							      : 
							      plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
						      PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
							      0);
							FUNCALL_0(get(Data_series_illustration_kind,
								Qdata_series_projection_method,
								_));
						      POP_SPECIAL();
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_9:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_9;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_9;
						    end_loop_9:;
						      Current_part_description 
							      = 
							      old_current_part_description_4;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      ab_loop_iter_flag_ = Nil;
						      goto next_loop_8;
						    end_loop_8:
						      SAVE_VALUES(VALUES_1(Qnil));
						    POP_SPECIAL();
						  POP_SPECIAL();
						  part_feature_index = Nil;
						  exit_feature_handler = Nil;
						next_loop_10:
						  part_stack_pop_store = Nil;
						  cons_1 = 
							  Part_feature_recall_stack;
						  if (cons_1) {
						      part_stack_pop_store 
							      = M_CAR(cons_1);
						      next_cons = 
							      M_CDR(cons_1);
						      inline_note_reclaim_cons(cons_1,
							      Qpart_stack);
						      if (ISVREF(Available_part_stack_conses_tail_vector,
							      IFIX(Current_thread_index))) 
								  {
							  temp = 
								  ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index));
							  M_CDR(temp) = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      else {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      M_CDR(cons_1) = Nil;
						  }
						  else
						      next_cons = Nil;
						  Part_feature_recall_stack 
							  = next_cons;
						  part_feature_index = 
							  part_stack_pop_store;
						  if (EQ(part_feature_index,
							  Qmark))
						      goto end_loop_10;
						  exit_feature_handler = 
							  ISVREF(Part_feature_exit_methods,
							  IFIX(part_feature_index));
						  inline_funcall_0(exit_feature_handler);
						  goto next_loop_10;
						end_loop_10:;
						  Current_part_description 
							  = 
							  old_current_part_description_3;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Stack_of_current_part_descriptions;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Stack_of_current_part_descriptions 
							      = next_cons;
						  }
						POP_SPECIAL();
					    }
					    else {
						old_current_part_description_3 
							= 
							Current_part_description;
						Current_part_description = 
							Default_axis_data_series_instance;
						if (Maintain_stack_of_current_part_descriptions_p) 
							    {
						    new_cons = 
							    ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index));
						    if (new_cons) {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							svref_new_value = 
								M_CDR(new_cons);
							SVREF(temp,temp_1) 
								= 
								svref_new_value;
							if ( 
								!TRUEP(ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index)))) 
								    {
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = Nil;
							}
							gensymed_symbol = 
								new_cons;
						    }
						    else
							gensymed_symbol = Nil;
						    if ( 
							    !TRUEP(gensymed_symbol))
							gensymed_symbol = 
								replenish_part_stack_cons_pool();
						    temp = 
							    Current_part_description;
						    M_CAR(gensymed_symbol) 
							    = temp;
						    temp = 
							    Stack_of_current_part_descriptions;
						    M_CDR(gensymed_symbol) 
							    = temp;
						    inline_note_allocate_cons(gensymed_symbol,
							    Qpart_stack);
						    Stack_of_current_part_descriptions 
							    = gensymed_symbol;
						}
						new_cons = 
							ISVREF(Available_part_stack_conses_vector,
							IFIX(Current_thread_index));
						if (new_cons) {
						    temp = 
							    Available_part_stack_conses_vector;
						    temp_1 = 
							    Current_thread_index;
						    svref_new_value = 
							    M_CDR(new_cons);
						    SVREF(temp,temp_1) = 
							    svref_new_value;
						    if ( 
							    !TRUEP(ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index)))) 
								{
							temp = 
								Available_part_stack_conses_tail_vector;
							temp_1 = 
								Current_thread_index;
							SVREF(temp,temp_1) 
								= Nil;
						    }
						    gensymed_symbol = new_cons;
						}
						else
						    gensymed_symbol = Nil;
						if ( !TRUEP(gensymed_symbol))
						    gensymed_symbol = 
							    replenish_part_stack_cons_pool();
						M_CAR(gensymed_symbol) = Qmark;
						temp = 
							Part_feature_recall_stack;
						M_CDR(gensymed_symbol) = temp;
						inline_note_allocate_cons(gensymed_symbol,
							Qpart_stack);
						Part_feature_recall_stack 
							= gensymed_symbol;
						enter_part_description(Current_part_description);
						current_axis = Nil;
						ab_loop_list_ = 
							get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							Qcomputed_annotations,
							Nil),Qsubparts,Qaxis);
						PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
							2);
						  axis_index = 
							  FIX((SI_Long)1L);
						  PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,
							  1);
						    ab_loop_iter_flag_ = T;
						  next_loop_11:
						    if ( !TRUEP(ab_loop_list_))
							goto end_loop_11;
						    Current_axis = 
							    M_CAR(ab_loop_list_);
						    ab_loop_list_ = 
							    M_CDR(ab_loop_list_);
						    if ( 
							    !TRUEP(ab_loop_iter_flag_))
							Axis_index = 
								FIXNUM_ADD1(Axis_index);
						    old_current_part_description_4 
							    = 
							    Current_part_description;
						    Current_part_description 
							    = Current_axis;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							new_cons = 
								ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index));
							if (new_cons) {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    svref_new_value 
								    = 
								    M_CDR(new_cons);
							    SVREF(temp,
								    temp_1) 
								    = 
								    svref_new_value;
							    if ( 
								    !TRUEP(ISVREF(Available_part_stack_conses_vector,
								    IFIX(Current_thread_index)))) 
									{
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= Nil;
							    }
							    gensymed_symbol 
								    = new_cons;
							}
							else
							    gensymed_symbol 
								    = Nil;
							if ( 
								!TRUEP(gensymed_symbol))
							    gensymed_symbol 
								    = 
								    replenish_part_stack_cons_pool();
							temp = 
								Current_part_description;
							M_CAR(gensymed_symbol) 
								= temp;
							temp = 
								Stack_of_current_part_descriptions;
							M_CDR(gensymed_symbol) 
								= temp;
							inline_note_allocate_cons(gensymed_symbol,
								Qpart_stack);
							Stack_of_current_part_descriptions 
								= 
								gensymed_symbol;
						    }
						    new_cons = 
							    ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index));
						    if (new_cons) {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							svref_new_value = 
								M_CDR(new_cons);
							SVREF(temp,temp_1) 
								= 
								svref_new_value;
							if ( 
								!TRUEP(ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index)))) 
								    {
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = Nil;
							}
							gensymed_symbol = 
								new_cons;
						    }
						    else
							gensymed_symbol = Nil;
						    if ( 
							    !TRUEP(gensymed_symbol))
							gensymed_symbol = 
								replenish_part_stack_cons_pool();
						    M_CAR(gensymed_symbol) 
							    = Qmark;
						    temp = 
							    Part_feature_recall_stack;
						    M_CDR(gensymed_symbol) 
							    = temp;
						    inline_note_allocate_cons(gensymed_symbol,
							    Qpart_stack);
						    Part_feature_recall_stack 
							    = gensymed_symbol;
						    enter_part_description(Current_part_description);
						    axis_is_discrete_p = 
							    EQ(Axis_heading,
							    Qeast) ? 
							    plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
							    : 
							    plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
						    PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
							    0);
						      chart_pen_color(Formatted_part_true_line_color);
						      FUNCALL_0(get(Data_series_illustration_kind,
							      Qdata_series_projection_method,
							      _));
						    POP_SPECIAL();
						    part_feature_index = Nil;
						    exit_feature_handler = Nil;
						  next_loop_12:
						    part_stack_pop_store = Nil;
						    cons_1 = 
							    Part_feature_recall_stack;
						    if (cons_1) {
							part_stack_pop_store 
								= 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpart_stack);
							if (ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp = 
								    ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp) = 
								    cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							else {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    Part_feature_recall_stack 
							    = next_cons;
						    part_feature_index = 
							    part_stack_pop_store;
						    if (EQ(part_feature_index,
							    Qmark))
							goto end_loop_12;
						    exit_feature_handler = 
							    ISVREF(Part_feature_exit_methods,
							    IFIX(part_feature_index));
						    inline_funcall_0(exit_feature_handler);
						    goto next_loop_12;
						  end_loop_12:;
						    Current_part_description 
							    = 
							    old_current_part_description_4;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							part_stack_pop_store 
								= Nil;
							cons_1 = 
								Stack_of_current_part_descriptions;
							if (cons_1) {
							    part_stack_pop_store 
								    = 
								    M_CAR(cons_1);
							    next_cons = 
								    M_CDR(cons_1);
							    inline_note_reclaim_cons(cons_1,
								    Qpart_stack);
							    if (ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index))) 
									{
								temp = 
									ISVREF(Available_part_stack_conses_tail_vector,
									IFIX(Current_thread_index));
								M_CDR(temp) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    else {
								temp = 
									Available_part_stack_conses_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    M_CDR(cons_1) 
								    = Nil;
							}
							else
							    next_cons = Nil;
							Stack_of_current_part_descriptions 
								= next_cons;
						    }
						    ab_loop_iter_flag_ = Nil;
						    goto next_loop_11;
						  end_loop_11:;
						  POP_SPECIAL();
						POP_SPECIAL();
						part_feature_index = Nil;
						exit_feature_handler = Nil;
					      next_loop_13:
						part_stack_pop_store = Nil;
						cons_1 = 
							Part_feature_recall_stack;
						if (cons_1) {
						    part_stack_pop_store = 
							    M_CAR(cons_1);
						    next_cons = M_CDR(cons_1);
						    inline_note_reclaim_cons(cons_1,
							    Qpart_stack);
						    if (ISVREF(Available_part_stack_conses_tail_vector,
							    IFIX(Current_thread_index))) 
								{
							temp = 
								ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index));
							M_CDR(temp) = cons_1;
							temp = 
								Available_part_stack_conses_tail_vector;
							temp_1 = 
								Current_thread_index;
							SVREF(temp,temp_1) 
								= cons_1;
						    }
						    else {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							SVREF(temp,temp_1) 
								= cons_1;
							temp = 
								Available_part_stack_conses_tail_vector;
							temp_1 = 
								Current_thread_index;
							SVREF(temp,temp_1) 
								= cons_1;
						    }
						    M_CDR(cons_1) = Nil;
						}
						else
						    next_cons = Nil;
						Part_feature_recall_stack 
							= next_cons;
						part_feature_index = 
							part_stack_pop_store;
						if (EQ(part_feature_index,
							Qmark))
						    goto end_loop_13;
						exit_feature_handler = 
							ISVREF(Part_feature_exit_methods,
							IFIX(part_feature_index));
						inline_funcall_0(exit_feature_handler);
						goto next_loop_13;
					      end_loop_13:;
						Current_part_description = 
							old_current_part_description_3;
						if (Maintain_stack_of_current_part_descriptions_p) 
							    {
						    part_stack_pop_store = Nil;
						    cons_1 = 
							    Stack_of_current_part_descriptions;
						    if (cons_1) {
							part_stack_pop_store 
								= 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpart_stack);
							if (ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp = 
								    ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp) = 
								    cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							else {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    Stack_of_current_part_descriptions 
							    = next_cons;
						}
						current_data_series = Nil;
						ab_loop_list_ = 
							Data_series_subparts;
						PUSH_SPECIAL_WITH_SYMBOL(Current_data_series,Qcurrent_data_series,current_data_series,
							1);
						  current_computed_data_series 
							  = Nil;
						  ab_loop_list__1 = 
							  get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							  Qcomputed_annotations,
							  Nil),Qsubparts,
							  Qdata_series);
						  data_series_index = 
							  FIX((SI_Long)1L);
						  PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
							  0);
						    ab_loop_iter_flag_ = T;
						  next_loop_14:
						    if ( !TRUEP(ab_loop_list_))
							goto end_loop_14;
						    Current_data_series = 
							    M_CAR(ab_loop_list_);
						    ab_loop_list_ = 
							    M_CDR(ab_loop_list_);
						    if ( 
							    !TRUEP(ab_loop_list__1))
							goto end_loop_14;
						    current_computed_data_series 
							    = 
							    M_CAR(ab_loop_list__1);
						    ab_loop_list__1 = 
							    M_CDR(ab_loop_list__1);
						    if ( 
							    !TRUEP(ab_loop_iter_flag_))
							Data_series_index 
								= 
								FIXNUM_ADD1(Data_series_index);
						    old_current_part_description_3 
							    = 
							    Current_part_description;
						    Current_part_description 
							    = 
							    Current_data_series;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							new_cons = 
								ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index));
							if (new_cons) {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    svref_new_value 
								    = 
								    M_CDR(new_cons);
							    SVREF(temp,
								    temp_1) 
								    = 
								    svref_new_value;
							    if ( 
								    !TRUEP(ISVREF(Available_part_stack_conses_vector,
								    IFIX(Current_thread_index)))) 
									{
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= Nil;
							    }
							    gensymed_symbol 
								    = new_cons;
							}
							else
							    gensymed_symbol 
								    = Nil;
							if ( 
								!TRUEP(gensymed_symbol))
							    gensymed_symbol 
								    = 
								    replenish_part_stack_cons_pool();
							temp = 
								Current_part_description;
							M_CAR(gensymed_symbol) 
								= temp;
							temp = 
								Stack_of_current_part_descriptions;
							M_CDR(gensymed_symbol) 
								= temp;
							inline_note_allocate_cons(gensymed_symbol,
								Qpart_stack);
							Stack_of_current_part_descriptions 
								= 
								gensymed_symbol;
						    }
						    new_cons = 
							    ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index));
						    if (new_cons) {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							svref_new_value = 
								M_CDR(new_cons);
							SVREF(temp,temp_1) 
								= 
								svref_new_value;
							if ( 
								!TRUEP(ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index)))) 
								    {
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = Nil;
							}
							gensymed_symbol = 
								new_cons;
						    }
						    else
							gensymed_symbol = Nil;
						    if ( 
							    !TRUEP(gensymed_symbol))
							gensymed_symbol = 
								replenish_part_stack_cons_pool();
						    M_CAR(gensymed_symbol) 
							    = Qmark;
						    temp = 
							    Part_feature_recall_stack;
						    M_CDR(gensymed_symbol) 
							    = temp;
						    inline_note_allocate_cons(gensymed_symbol,
							    Qpart_stack);
						    Part_feature_recall_stack 
							    = gensymed_symbol;
						    enter_part_description(Current_part_description);
						    old_current_part_description_4 
							    = 
							    Current_part_description;
						    Current_part_description 
							    = 
							    lookup_part_exception(Qdata_series,
							    Data_series_index);
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							new_cons = 
								ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index));
							if (new_cons) {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    svref_new_value 
								    = 
								    M_CDR(new_cons);
							    SVREF(temp,
								    temp_1) 
								    = 
								    svref_new_value;
							    if ( 
								    !TRUEP(ISVREF(Available_part_stack_conses_vector,
								    IFIX(Current_thread_index)))) 
									{
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= Nil;
							    }
							    gensymed_symbol 
								    = new_cons;
							}
							else
							    gensymed_symbol 
								    = Nil;
							if ( 
								!TRUEP(gensymed_symbol))
							    gensymed_symbol 
								    = 
								    replenish_part_stack_cons_pool();
							temp = 
								Current_part_description;
							M_CAR(gensymed_symbol) 
								= temp;
							temp = 
								Stack_of_current_part_descriptions;
							M_CDR(gensymed_symbol) 
								= temp;
							inline_note_allocate_cons(gensymed_symbol,
								Qpart_stack);
							Stack_of_current_part_descriptions 
								= 
								gensymed_symbol;
						    }
						    new_cons = 
							    ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index));
						    if (new_cons) {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							svref_new_value = 
								M_CDR(new_cons);
							SVREF(temp,temp_1) 
								= 
								svref_new_value;
							if ( 
								!TRUEP(ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index)))) 
								    {
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = Nil;
							}
							gensymed_symbol = 
								new_cons;
						    }
						    else
							gensymed_symbol = Nil;
						    if ( 
							    !TRUEP(gensymed_symbol))
							gensymed_symbol = 
								replenish_part_stack_cons_pool();
						    M_CAR(gensymed_symbol) 
							    = Qmark;
						    temp = 
							    Part_feature_recall_stack;
						    M_CDR(gensymed_symbol) 
							    = temp;
						    inline_note_allocate_cons(gensymed_symbol,
							    Qpart_stack);
						    Part_feature_recall_stack 
							    = gensymed_symbol;
						    enter_part_description(Current_part_description);
						    old_current_part_description_5 
							    = 
							    Current_part_description;
						    Current_part_description 
							    = 
							    current_computed_data_series;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							new_cons = 
								ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index));
							if (new_cons) {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    svref_new_value 
								    = 
								    M_CDR(new_cons);
							    SVREF(temp,
								    temp_1) 
								    = 
								    svref_new_value;
							    if ( 
								    !TRUEP(ISVREF(Available_part_stack_conses_vector,
								    IFIX(Current_thread_index)))) 
									{
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= Nil;
							    }
							    gensymed_symbol 
								    = new_cons;
							}
							else
							    gensymed_symbol 
								    = Nil;
							if ( 
								!TRUEP(gensymed_symbol))
							    gensymed_symbol 
								    = 
								    replenish_part_stack_cons_pool();
							temp = 
								Current_part_description;
							M_CAR(gensymed_symbol) 
								= temp;
							temp = 
								Stack_of_current_part_descriptions;
							M_CDR(gensymed_symbol) 
								= temp;
							inline_note_allocate_cons(gensymed_symbol,
								Qpart_stack);
							Stack_of_current_part_descriptions 
								= 
								gensymed_symbol;
						    }
						    new_cons = 
							    ISVREF(Available_part_stack_conses_vector,
							    IFIX(Current_thread_index));
						    if (new_cons) {
							temp = 
								Available_part_stack_conses_vector;
							temp_1 = 
								Current_thread_index;
							svref_new_value = 
								M_CDR(new_cons);
							SVREF(temp,temp_1) 
								= 
								svref_new_value;
							if ( 
								!TRUEP(ISVREF(Available_part_stack_conses_vector,
								IFIX(Current_thread_index)))) 
								    {
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = Nil;
							}
							gensymed_symbol = 
								new_cons;
						    }
						    else
							gensymed_symbol = Nil;
						    if ( 
							    !TRUEP(gensymed_symbol))
							gensymed_symbol = 
								replenish_part_stack_cons_pool();
						    M_CAR(gensymed_symbol) 
							    = Qmark;
						    temp = 
							    Part_feature_recall_stack;
						    M_CDR(gensymed_symbol) 
							    = temp;
						    inline_note_allocate_cons(gensymed_symbol,
							    Qpart_stack);
						    Part_feature_recall_stack 
							    = gensymed_symbol;
						    enter_part_description(Current_part_description);
						    chart_pen_color(Formatted_part_true_line_color);
						    FUNCALL_0(get(Data_series_illustration_kind,
							    Qdata_series_projection_method,
							    _));
						    part_feature_index = Nil;
						    exit_feature_handler = Nil;
						  next_loop_15:
						    part_stack_pop_store = Nil;
						    cons_1 = 
							    Part_feature_recall_stack;
						    if (cons_1) {
							part_stack_pop_store 
								= 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpart_stack);
							if (ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp = 
								    ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp) = 
								    cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							else {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    Part_feature_recall_stack 
							    = next_cons;
						    part_feature_index = 
							    part_stack_pop_store;
						    if (EQ(part_feature_index,
							    Qmark))
							goto end_loop_15;
						    exit_feature_handler = 
							    ISVREF(Part_feature_exit_methods,
							    IFIX(part_feature_index));
						    inline_funcall_0(exit_feature_handler);
						    goto next_loop_15;
						  end_loop_15:;
						    Current_part_description 
							    = 
							    old_current_part_description_5;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							part_stack_pop_store 
								= Nil;
							cons_1 = 
								Stack_of_current_part_descriptions;
							if (cons_1) {
							    part_stack_pop_store 
								    = 
								    M_CAR(cons_1);
							    next_cons = 
								    M_CDR(cons_1);
							    inline_note_reclaim_cons(cons_1,
								    Qpart_stack);
							    if (ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index))) 
									{
								temp = 
									ISVREF(Available_part_stack_conses_tail_vector,
									IFIX(Current_thread_index));
								M_CDR(temp) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    else {
								temp = 
									Available_part_stack_conses_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    M_CDR(cons_1) 
								    = Nil;
							}
							else
							    next_cons = Nil;
							Stack_of_current_part_descriptions 
								= next_cons;
						    }
						    part_feature_index = Nil;
						    exit_feature_handler = Nil;
						  next_loop_16:
						    part_stack_pop_store = Nil;
						    cons_1 = 
							    Part_feature_recall_stack;
						    if (cons_1) {
							part_stack_pop_store 
								= 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpart_stack);
							if (ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp = 
								    ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp) = 
								    cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							else {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    Part_feature_recall_stack 
							    = next_cons;
						    part_feature_index = 
							    part_stack_pop_store;
						    if (EQ(part_feature_index,
							    Qmark))
							goto end_loop_16;
						    exit_feature_handler = 
							    ISVREF(Part_feature_exit_methods,
							    IFIX(part_feature_index));
						    inline_funcall_0(exit_feature_handler);
						    goto next_loop_16;
						  end_loop_16:;
						    Current_part_description 
							    = 
							    old_current_part_description_4;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							part_stack_pop_store 
								= Nil;
							cons_1 = 
								Stack_of_current_part_descriptions;
							if (cons_1) {
							    part_stack_pop_store 
								    = 
								    M_CAR(cons_1);
							    next_cons = 
								    M_CDR(cons_1);
							    inline_note_reclaim_cons(cons_1,
								    Qpart_stack);
							    if (ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index))) 
									{
								temp = 
									ISVREF(Available_part_stack_conses_tail_vector,
									IFIX(Current_thread_index));
								M_CDR(temp) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    else {
								temp = 
									Available_part_stack_conses_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    M_CDR(cons_1) 
								    = Nil;
							}
							else
							    next_cons = Nil;
							Stack_of_current_part_descriptions 
								= next_cons;
						    }
						    part_feature_index = Nil;
						    exit_feature_handler = Nil;
						  next_loop_17:
						    part_stack_pop_store = Nil;
						    cons_1 = 
							    Part_feature_recall_stack;
						    if (cons_1) {
							part_stack_pop_store 
								= 
								M_CAR(cons_1);
							next_cons = 
								M_CDR(cons_1);
							inline_note_reclaim_cons(cons_1,
								Qpart_stack);
							if (ISVREF(Available_part_stack_conses_tail_vector,
								IFIX(Current_thread_index))) 
								    {
							    temp = 
								    ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index));
							    M_CDR(temp) = 
								    cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							else {
							    temp = 
								    Available_part_stack_conses_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							    temp = 
								    Available_part_stack_conses_tail_vector;
							    temp_1 = 
								    Current_thread_index;
							    SVREF(temp,
								    temp_1) 
								    = cons_1;
							}
							M_CDR(cons_1) = Nil;
						    }
						    else
							next_cons = Nil;
						    Part_feature_recall_stack 
							    = next_cons;
						    part_feature_index = 
							    part_stack_pop_store;
						    if (EQ(part_feature_index,
							    Qmark))
							goto end_loop_17;
						    exit_feature_handler = 
							    ISVREF(Part_feature_exit_methods,
							    IFIX(part_feature_index));
						    inline_funcall_0(exit_feature_handler);
						    goto next_loop_17;
						  end_loop_17:;
						    Current_part_description 
							    = 
							    old_current_part_description_3;
						    if (Maintain_stack_of_current_part_descriptions_p) 
								{
							part_stack_pop_store 
								= Nil;
							cons_1 = 
								Stack_of_current_part_descriptions;
							if (cons_1) {
							    part_stack_pop_store 
								    = 
								    M_CAR(cons_1);
							    next_cons = 
								    M_CDR(cons_1);
							    inline_note_reclaim_cons(cons_1,
								    Qpart_stack);
							    if (ISVREF(Available_part_stack_conses_tail_vector,
								    IFIX(Current_thread_index))) 
									{
								temp = 
									ISVREF(Available_part_stack_conses_tail_vector,
									IFIX(Current_thread_index));
								M_CDR(temp) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    else {
								temp = 
									Available_part_stack_conses_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
								temp = 
									Available_part_stack_conses_tail_vector;
								temp_1 = 
									Current_thread_index;
								SVREF(temp,
									temp_1) 
									= 
									cons_1;
							    }
							    M_CDR(cons_1) 
								    = Nil;
							}
							else
							    next_cons = Nil;
							Stack_of_current_part_descriptions 
								= next_cons;
						    }
						    ab_loop_iter_flag_ = Nil;
						    goto next_loop_14;
						  end_loop_14:;
						  POP_SPECIAL();
						POP_SPECIAL();
						tick_mark_part_to_draw = 
							Qtick_mark;
						PUSH_SPECIAL_WITH_SYMBOL(Tick_mark_part_to_draw,Qtick_mark_part_to_draw,tick_mark_part_to_draw,
							3);
						  old_current_part_description_3 
							  = 
							  Current_part_description;
						  Current_part_description 
							  = 
							  Default_axis_data_series_instance;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      temp = 
							      Current_part_description;
						      M_CAR(gensymed_symbol) 
							      = temp;
						      temp = 
							      Stack_of_current_part_descriptions;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Stack_of_current_part_descriptions 
							      = 
							      gensymed_symbol;
						  }
						  new_cons = 
							  ISVREF(Available_part_stack_conses_vector,
							  IFIX(Current_thread_index));
						  if (new_cons) {
						      temp = 
							      Available_part_stack_conses_vector;
						      temp_1 = 
							      Current_thread_index;
						      svref_new_value = 
							      M_CDR(new_cons);
						      SVREF(temp,temp_1) = 
							      svref_new_value;
						      if ( 
							      !TRUEP(ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index)))) 
								  {
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = Nil;
						      }
						      gensymed_symbol = 
							      new_cons;
						  }
						  else
						      gensymed_symbol = Nil;
						  if ( !TRUEP(gensymed_symbol))
						      gensymed_symbol = 
							      replenish_part_stack_cons_pool();
						  M_CAR(gensymed_symbol) = 
							  Qmark;
						  temp = 
							  Part_feature_recall_stack;
						  M_CDR(gensymed_symbol) = 
							  temp;
						  inline_note_allocate_cons(gensymed_symbol,
							  Qpart_stack);
						  Part_feature_recall_stack 
							  = gensymed_symbol;
						  enter_part_description(Current_part_description);
						  current_axis = Nil;
						  ab_loop_list_ = 
							  get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
							  Qcomputed_annotations,
							  Nil),Qsubparts,
							  Qaxis);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
							  2);
						    axis_index = 
							    FIX((SI_Long)1L);
						    PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,
							    1);
						      ab_loop_iter_flag_ = T;
						    next_loop_18:
						      if ( 
							      !TRUEP(ab_loop_list_))
							  goto end_loop_18;
						      Current_axis = 
							      M_CAR(ab_loop_list_);
						      ab_loop_list_ = 
							      M_CDR(ab_loop_list_);
						      if ( 
							      !TRUEP(ab_loop_iter_flag_))
							  Axis_index = 
								  FIXNUM_ADD1(Axis_index);
						      old_current_part_description_4 
							      = 
							      Current_part_description;
						      Current_part_description 
							      = Current_axis;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp,
								      temp_1) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  temp = 
								  Current_part_description;
							  M_CAR(gensymed_symbol) 
								  = temp;
							  temp = 
								  Stack_of_current_part_descriptions;
							  M_CDR(gensymed_symbol) 
								  = temp;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Stack_of_current_part_descriptions 
								  = 
								  gensymed_symbol;
						      }
						      new_cons = 
							      ISVREF(Available_part_stack_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(temp,
								  temp_1) 
								  = svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = Nil;
							  }
							  gensymed_symbol 
								  = new_cons;
						      }
						      else
							  gensymed_symbol 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol))
							  gensymed_symbol 
								  = 
								  replenish_part_stack_cons_pool();
						      M_CAR(gensymed_symbol) 
							      = Qmark;
						      temp = 
							      Part_feature_recall_stack;
						      M_CDR(gensymed_symbol) 
							      = temp;
						      inline_note_allocate_cons(gensymed_symbol,
							      Qpart_stack);
						      Part_feature_recall_stack 
							      = 
							      gensymed_symbol;
						      enter_part_description(Current_part_description);
						      axis_is_discrete_p = 
							      EQ(Axis_heading,
							      Qeast) ? 
							      plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
							      : 
							      plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
						      PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
							      0);
							FUNCALL_0(get(Data_series_illustration_kind,
								Qdata_series_projection_method,
								_));
						      POP_SPECIAL();
						      part_feature_index = Nil;
						      exit_feature_handler 
							      = Nil;
						    next_loop_19:
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Part_feature_recall_stack;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Part_feature_recall_stack 
							      = next_cons;
						      part_feature_index = 
							      part_stack_pop_store;
						      if (EQ(part_feature_index,
							      Qmark))
							  goto end_loop_19;
						      exit_feature_handler 
							      = 
							      ISVREF(Part_feature_exit_methods,
							      IFIX(part_feature_index));
						      inline_funcall_0(exit_feature_handler);
						      goto next_loop_19;
						    end_loop_19:;
						      Current_part_description 
							      = 
							      old_current_part_description_4;
						      if (Maintain_stack_of_current_part_descriptions_p) 
								  {
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Stack_of_current_part_descriptions;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      else {
								  temp = 
									  Available_part_stack_conses_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
								  temp = 
									  Available_part_stack_conses_tail_vector;
								  temp_1 = 
									  Current_thread_index;
								  SVREF(temp,
									  temp_1) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Stack_of_current_part_descriptions 
								  = next_cons;
						      }
						      ab_loop_iter_flag_ = Nil;
						      goto next_loop_18;
						    end_loop_18:
						      SAVE_VALUES(VALUES_1(Qnil));
						    POP_SPECIAL();
						  POP_SPECIAL();
						  part_feature_index = Nil;
						  exit_feature_handler = Nil;
						next_loop_20:
						  part_stack_pop_store = Nil;
						  cons_1 = 
							  Part_feature_recall_stack;
						  if (cons_1) {
						      part_stack_pop_store 
							      = M_CAR(cons_1);
						      next_cons = 
							      M_CDR(cons_1);
						      inline_note_reclaim_cons(cons_1,
							      Qpart_stack);
						      if (ISVREF(Available_part_stack_conses_tail_vector,
							      IFIX(Current_thread_index))) 
								  {
							  temp = 
								  ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index));
							  M_CDR(temp) = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      else {
							  temp = 
								  Available_part_stack_conses_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
							  temp = 
								  Available_part_stack_conses_tail_vector;
							  temp_1 = 
								  Current_thread_index;
							  SVREF(temp,
								  temp_1) 
								  = cons_1;
						      }
						      M_CDR(cons_1) = Nil;
						  }
						  else
						      next_cons = Nil;
						  Part_feature_recall_stack 
							  = next_cons;
						  part_feature_index = 
							  part_stack_pop_store;
						  if (EQ(part_feature_index,
							  Qmark))
						      goto end_loop_20;
						  exit_feature_handler = 
							  ISVREF(Part_feature_exit_methods,
							  IFIX(part_feature_index));
						  inline_funcall_0(exit_feature_handler);
						  goto next_loop_20;
						end_loop_20:;
						  Current_part_description 
							  = 
							  old_current_part_description_3;
						  if (Maintain_stack_of_current_part_descriptions_p) 
							      {
						      part_stack_pop_store 
							      = Nil;
						      cons_1 = 
							      Stack_of_current_part_descriptions;
						      if (cons_1) {
							  part_stack_pop_store 
								  = 
								  M_CAR(cons_1);
							  next_cons = 
								  M_CDR(cons_1);
							  inline_note_reclaim_cons(cons_1,
								  Qpart_stack);
							  if (ISVREF(Available_part_stack_conses_tail_vector,
								  IFIX(Current_thread_index))) 
								      {
							      temp = 
								      ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index));
							      M_CDR(temp) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  else {
							      temp = 
								      Available_part_stack_conses_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							      temp = 
								      Available_part_stack_conses_tail_vector;
							      temp_1 = 
								      Current_thread_index;
							      SVREF(temp,
								      temp_1) 
								      = cons_1;
							  }
							  M_CDR(cons_1) = Nil;
						      }
						      else
							  next_cons = Nil;
						      Stack_of_current_part_descriptions 
							      = next_cons;
						  }
						POP_SPECIAL();
					    }
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				      part_feature_index = Nil;
				      exit_feature_handler = Nil;
				    next_loop_21:
				      part_stack_pop_store = Nil;
				      cons_1 = Part_feature_recall_stack;
				      if (cons_1) {
					  part_stack_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qpart_stack);
					  if (ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp = 
						      ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  else {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Part_feature_recall_stack = next_cons;
				      part_feature_index = 
					      part_stack_pop_store;
				      if (EQ(part_feature_index,Qmark))
					  goto end_loop_21;
				      exit_feature_handler = 
					      ISVREF(Part_feature_exit_methods,
					      IFIX(part_feature_index));
				      inline_funcall_0(exit_feature_handler);
				      goto next_loop_21;
				    end_loop_21:;
				      Current_part_description = 
					      old_current_part_description_2;
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  part_stack_pop_store = Nil;
					  cons_1 = 
						  Stack_of_current_part_descriptions;
					  if (cons_1) {
					      part_stack_pop_store = 
						      M_CAR(cons_1);
					      next_cons = M_CDR(cons_1);
					      inline_note_reclaim_cons(cons_1,
						      Qpart_stack);
					      if (ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index))) 
							  {
						  temp = 
							  ISVREF(Available_part_stack_conses_tail_vector,
							  IFIX(Current_thread_index));
						  M_CDR(temp) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      else {
						  temp = 
							  Available_part_stack_conses_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      M_CDR(cons_1) = Nil;
					  }
					  else
					      next_cons = Nil;
					  Stack_of_current_part_descriptions 
						  = next_cons;
				      }
				      part_feature_index = Nil;
				      exit_feature_handler = Nil;
				    next_loop_22:
				      part_stack_pop_store = Nil;
				      cons_1 = Part_feature_recall_stack;
				      if (cons_1) {
					  part_stack_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qpart_stack);
					  if (ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp = 
						      ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  else {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Part_feature_recall_stack = next_cons;
				      part_feature_index = 
					      part_stack_pop_store;
				      if (EQ(part_feature_index,Qmark))
					  goto end_loop_22;
				      exit_feature_handler = 
					      ISVREF(Part_feature_exit_methods,
					      IFIX(part_feature_index));
				      inline_funcall_0(exit_feature_handler);
				      goto next_loop_22;
				    end_loop_22:;
				      Current_part_description = 
					      old_current_part_description_1;
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  part_stack_pop_store = Nil;
					  cons_1 = 
						  Stack_of_current_part_descriptions;
					  if (cons_1) {
					      part_stack_pop_store = 
						      M_CAR(cons_1);
					      next_cons = M_CDR(cons_1);
					      inline_note_reclaim_cons(cons_1,
						      Qpart_stack);
					      if (ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index))) 
							  {
						  temp = 
							  ISVREF(Available_part_stack_conses_tail_vector,
							  IFIX(Current_thread_index));
						  M_CDR(temp) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      else {
						  temp = 
							  Available_part_stack_conses_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      M_CDR(cons_1) = Nil;
					  }
					  else
					      next_cons = Nil;
					  Stack_of_current_part_descriptions 
						  = next_cons;
				      }
				      part_feature_index = Nil;
				      exit_feature_handler = Nil;
				    next_loop_23:
				      part_stack_pop_store = Nil;
				      cons_1 = Part_feature_recall_stack;
				      if (cons_1) {
					  part_stack_pop_store = M_CAR(cons_1);
					  next_cons = M_CDR(cons_1);
					  inline_note_reclaim_cons(cons_1,
						  Qpart_stack);
					  if (ISVREF(Available_part_stack_conses_tail_vector,
						  IFIX(Current_thread_index))) 
						      {
					      temp = 
						      ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index));
					      M_CDR(temp) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  else {
					      temp = 
						      Available_part_stack_conses_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					      temp = 
						      Available_part_stack_conses_tail_vector;
					      temp_1 = Current_thread_index;
					      SVREF(temp,temp_1) = cons_1;
					  }
					  M_CDR(cons_1) = Nil;
				      }
				      else
					  next_cons = Nil;
				      Part_feature_recall_stack = next_cons;
				      part_feature_index = 
					      part_stack_pop_store;
				      if (EQ(part_feature_index,Qmark))
					  goto end_loop_23;
				      exit_feature_handler = 
					      ISVREF(Part_feature_exit_methods,
					      IFIX(part_feature_index));
				      inline_funcall_0(exit_feature_handler);
				      goto next_loop_23;
				    end_loop_23:;
				      Current_part_description = 
					      old_current_part_description;
				      if (Maintain_stack_of_current_part_descriptions_p) 
						  {
					  part_stack_pop_store = Nil;
					  cons_1 = 
						  Stack_of_current_part_descriptions;
					  if (cons_1) {
					      part_stack_pop_store = 
						      M_CAR(cons_1);
					      next_cons = M_CDR(cons_1);
					      inline_note_reclaim_cons(cons_1,
						      Qpart_stack);
					      if (ISVREF(Available_part_stack_conses_tail_vector,
						      IFIX(Current_thread_index))) 
							  {
						  temp = 
							  ISVREF(Available_part_stack_conses_tail_vector,
							  IFIX(Current_thread_index));
						  M_CDR(temp) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      else {
						  temp = 
							  Available_part_stack_conses_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
						  temp = 
							  Available_part_stack_conses_tail_vector;
						  temp_1 = 
							  Current_thread_index;
						  SVREF(temp,temp_1) = cons_1;
					      }
					      M_CDR(cons_1) = Nil;
					  }
					  else
					      next_cons = Nil;
					  Stack_of_current_part_descriptions 
						  = next_cons;
				      }
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
		      }
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Chart_drawing);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* CHART-COLORS */
Object chart_colors()
{
    Object result_1, temp, gensymed_symbol;

    x_note_fn_call(177,191);
    result_1 = Nil;
    result_1 = chart_colors_1(result_1,ISVREF(Current_chart_frame,
	    (SI_Long)21L));
    result_1 = chart_colors_1(result_1,Default_axis_data_series_instance);
    temp = result_1;
    gensymed_symbol = ISVREF(Current_chart_frame,(SI_Long)19L);
    result_1 = chart_colors_1(temp,
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qchart_part_description_for_chart_style));
    return VALUES_1(result_1);
}

static Object list_constant_2;     /* # */

/* CHART-COLORS-1 */
Object chart_colors_1(colors_so_far,part_description)
    Object colors_so_far, part_description;
{
    Object feature_name, feature_value, ab_loop_list_, temp;
    Object subpart_collection, ab_loop_list__1, subpart, ab_loop_list__2;
    Object graph_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_it_;
    char temp_1;

    x_note_fn_call(177,192);
    feature_name = Nil;
    feature_value = Nil;
    ab_loop_list_ = REST(part_description);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    feature_name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    feature_value = CAR(temp);
    if (EQ(feature_name,Qsubparts) || EQ(feature_name,Qsubpart_defaults) 
	    || EQ(feature_name,Qsubpart_exceptions)) {
	subpart_collection = Nil;
	ab_loop_list__1 = feature_value;
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
      next_loop_1:
	temp = CDR(ab_loop_list__1);
	subpart_collection = CAR(temp);
	subpart = Nil;
	ab_loop_list__2 = subpart_collection;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	subpart = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	colors_so_far = chart_colors_1(colors_so_far,subpart);
	goto next_loop_2;
      end_loop_2:;
	ab_loop_list__1 = CDDR(ab_loop_list__1);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	goto next_loop_1;
      end_loop_1:;
    }
    else if (memq_function(feature_name,list_constant_2)) {
	if (EQ(feature_value,Qbackground))
	    graph_modify_macro_using_test_arg_1 = 
		    Current_background_color_value;
	else if (EQ(feature_value,Qforeground) || EQ(feature_value,
		Qworkspace_foreground))
	    graph_modify_macro_using_test_arg_1 = 
		    Current_foreground_color_value;
	else if (EQ(feature_value,Qtransparent))
	    graph_modify_macro_using_test_arg_1 = 
		    Current_background_color_value;
	else
	    graph_modify_macro_using_test_arg_1 = 
		    map_to_color_value(feature_value);
	car_1 = graph_modify_macro_using_test_arg_1;
	cdr_1 = colors_so_far;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp_1 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_3;
      end_loop_3:
	temp_1 = TRUEP(Qnil);
      end_1:;
	colors_so_far = temp_1 ? cdr_1 : graph_cons_1(car_1,cdr_1);
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    return VALUES_1(colors_so_far);
}

/* PROJECT-CHART-CALL-BACK */
Object project_chart_call_back(graph_rendering,
	    current_chart_raster_color_value)
    Object graph_rendering, current_chart_raster_color_value;
{
    Object current_chart_frame, current_computation_frame;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(3);
    Object result;

    x_note_fn_call(177,193);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Current_chart_raster_color_value,Qcurrent_chart_raster_color_value,current_chart_raster_color_value,
	    2);
      LOCK(Working_on_chart);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_chart_frame = ISVREF(graph_rendering,(SI_Long)16L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_chart_frame,Qcurrent_chart_frame,current_chart_frame,
		  1);
	    LOCK(Working_on_lexical_computation_of_frame);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_computation_frame = Current_chart_frame;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			0);
		  SAVE_VALUES(project_chart());
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Working_on_lexical_computation_of_frame);
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_chart);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* WRITE-CHART-STYLE-FROM-SLOT */
Object write_chart_style_from_slot(chart_style,gensymed_symbol)
    Object chart_style, gensymed_symbol;
{
    x_note_fn_call(177,194);
    return twrite_symbol(1,chart_style);
}

static Object string_constant_2;   /* "~S is not a known style for a chart" */

/* COMPILE-CHART-STYLE-FOR-SLOT */
Object compile_chart_style_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(177,195);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(in_directory_of_names_p(parse_result,Qchart_style))) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_2,parse_result);
	return VALUES_2(temp,temp_1);
    }
    else
	return VALUES_1(parse_result);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

/* CHART-STYLE-EVALUATION-SETTER */
Object chart_style_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,196);
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
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_style_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_chart_style_evaluation_setter:
    return result;
}

/* CHART-STYLE-EVALUATION-GETTER */
Object chart_style_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(177,197);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qnone;               /* none */

static Object string_constant_3;   /* "plot " */

static Object string_constant_4;   /* " versus " */

static Object string_constant_5;   /* ";~%" */

/* WRITE-DATA-SERIES-DESCRIPTIONS-FROM-SLOT */
Object write_data_series_descriptions_from_slot(data_series_descriptions,
	    gensymed_symbol)
    Object data_series_descriptions, gensymed_symbol;
{
    Object data_series, remainder_qm, ab_loop_list_, kind, info_1, info_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,198);
    if ( !TRUEP(data_series_descriptions))
	return twrite_symbol(1,Qnone);
    else {
	data_series = Nil;
	remainder_qm = Nil;
	ab_loop_list_ = data_series_descriptions;
	PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,0);
	  kind = Nil;
	  info_1 = Nil;
	  info_2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  Data_series = CAR(ab_loop_list_);
	  remainder_qm = CDR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  kind = get_simple_part_feature(Data_series,Qdata_series_source_kind);
	  info_1 = get_simple_part_feature(Data_series,Qdata_series_info_1);
	  info_2 = get_simple_part_feature(Data_series,Qdata_series_info_2);
	  tformat(1,string_constant_3);
	  if (EQ(kind,Qpair_of_g2_quantity_lists)) {
	      print_designation(info_2);
	      tformat(1,string_constant_4);
	      print_designation(info_1);
	  }
	  else if (EQ(kind,Qone_g2_quantity_list))
	      print_designation(info_1);
	  if (remainder_qm)
	      tformat(1,string_constant_5);
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
}

static Object string_constant_6;   /* "local names are not supported in data series." */

/* WRITE-PLOT-DESIGNATION-MAY-NOT-CONTAIN-LOCAL-NAMES-NOTE */
Object write_plot_designation_may_not_contain_local_names_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(177,199);
    GENSYM_RETURN_ONE(tformat(1,string_constant_6));
    return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qplot_designation_may_not_contain_local_names;  /* plot-designation-may-not-contain-local-names */

static Object Qab_let;             /* let */

/* COMPILE-DATA-SERIES-DESCRIPTIONS-FOR-SLOT */
Object compile_data_series_descriptions_for_slot varargs_1(int, n)
{
    Object parse_result, chart, gensymed_symbol;
    volatile Object compilation_result;
    Object bad_phrase_qm, current_annotated_frame, slot_description, new_cons;
    Object temp, temp_1, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, current_computation_frame;
    Object component_particulars_with_frame_notes_1;
    Object current_computation_component_particulars_1, ab_loop_list_;
    Object current_computation_component_particulars, data_series;
    Object data_series_index, designation_1, designation_2_qm;
    Object compilation_1_qm, compilation_2_qm, ab_loop_iter_flag_;
    Object frame_and_slot_or_atom, ab_loop_it_, temp_3, stack_change_pop_store;
    Object cons_1, next_cons;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(177,200);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    chart = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,6);
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      END_ARGS_nonrelocating();
      compilation_result = Nil;
      bad_phrase_qm = Nil;
      if (EQ(Qnone,parse_result))
	  compilation_result = Nil;
      else {
	  LOCK(Working_on_annotated_frame);
	  if (PUSH_UNWIND_PROTECT(0)) {
	      current_annotated_frame = Chart;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		      5);
		slot_description = 
			get_slot_description_of_class_description_function(Qframe_status_and_notes,
			ISVREF(Chart,(SI_Long)1L),Nil);
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_stack_change_conses_vector;
		    temp_1 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,temp_1) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_stack_change_conses_tail_vector;
			temp_1 = Current_thread_index;
			SVREF(temp,temp_1) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_stack_change_cons_pool();
		if (Nil)
		    gensymed_symbol_1 = nconc2(stack_change_list_2(Chart,
			    slot_description),stack_change_cons_1(Nil,Nil));
		else {
		    new_cons = ISVREF(Available_stack_change_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp = Available_stack_change_conses_vector;
			temp_1 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp,temp_1) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_stack_change_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp = Available_stack_change_conses_tail_vector;
			    temp_1 = Current_thread_index;
			    SVREF(temp,temp_1) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_stack_change_cons_pool();
		    temp = Chart;
		    M_CAR(gensymed_symbol_1) = temp;
		    M_CDR(gensymed_symbol_1) = slot_description;
		    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
		}
		M_CAR(gensymed_symbol) = gensymed_symbol_1;
		temp = Stack_of_slot_value_changes;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qstack_change);
		stack_of_slot_value_changes = gensymed_symbol;
		PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
			4);
		  current_computation_frame = Chart;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  1);
		    component_particulars_with_frame_notes_1 = 
			    component_particulars_with_frame_notes();
		    current_computation_component_particulars_1 = Nil;
		    ab_loop_list_ = component_particulars_with_frame_notes_1;
		    current_computation_component_particulars = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			    0);
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      current_computation_component_particulars_1 = 
			      M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      Current_computation_component_particulars = 
			      copy_for_slot_value(current_computation_component_particulars_1);
		      if (CONSP(Current_computation_component_particulars) 
			      && EQ(Qdata_series,
			      CAR(Current_computation_component_particulars))) 
				  {
			  delete_frame_note_if_any(Qplot_designation_may_not_contain_local_names,
				  Chart);
			  delete_all_frame_notes_for_rule_or_expression(Nil);
		      }
		      reclaim_slot_value(Current_computation_component_particulars);
		      goto next_loop;
		    end_loop:
		      reclaim_slot_value_list_1(component_particulars_with_frame_notes_1);
		    POP_SPECIAL();
		  POP_SPECIAL();
		  current_computation_frame = Chart;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			  3);
		    current_computation_component_particulars = 
			    slot_value_list_2(Qdata_series,FIX((SI_Long)0L));
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
			    2);
		      data_series = Nil;
		      ab_loop_list_ = REST(parse_result);
		      PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,
			      1);
			data_series_index = FIX((SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
				0);
			  designation_1 = Nil;
			  designation_2_qm = Nil;
			  compilation_1_qm = Nil;
			  compilation_2_qm = Nil;
			  ab_loop_iter_flag_ = T;
			next_loop_1:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop_1;
			  Data_series = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if ( !TRUEP(ab_loop_iter_flag_))
			      Data_series_index = 
				      FIXNUM_ADD1(Data_series_index);
			  temp = Current_computation_component_particulars;
			  temp_1 = Data_series_index;
			  M_SECOND(temp) = temp_1;
			  designation_1 = 
				  copy_for_phrase(get_simple_part_feature(Data_series,
				  Qdata_series_info_1));
			  designation_2_qm = 
				  copy_for_phrase(get_simple_part_feature(Data_series,
				  Qdata_series_info_2));
			  compilation_1_qm = 
				  compile_expression(designation_1,Nil,Nil);
			  compilation_2_qm = designation_2_qm ? 
				  compile_expression(designation_2_qm,Nil,
				  Nil) : Nil;
			  if (compilation_1_qm && CONSP(compilation_1_qm) 
				  && EQ(Qab_let,M_CAR(compilation_1_qm)) 
				  || designation_2_qm && compilation_2_qm 
				  && CONSP(compilation_2_qm) && EQ(Qab_let,
				  M_CAR(compilation_2_qm))) {
			      compilation_1_qm = Nil;
			      compilation_2_qm = Nil;
			      add_frame_note(2,
				      Qplot_designation_may_not_contain_local_names,
				      Chart);
			  }
			  if ( !TRUEP(compilation_1_qm) || 
				  designation_2_qm &&  
				  !TRUEP(compilation_2_qm))
			      set_simple_part_feature(Data_series,
				      Qdata_series_failed_to_compile,T);
			  if (compilation_1_qm)
			      set_simple_part_feature_without_reclaiming(Data_series,
				      Qdata_series_info_1,compilation_1_qm);
			  if (compilation_2_qm)
			      set_simple_part_feature_without_reclaiming(Data_series,
				      Qdata_series_info_2,compilation_2_qm);
			  ab_loop_iter_flag_ = Nil;
			  goto next_loop_1;
			end_loop_1:
			  reclaim_slot_value_list_1(Current_computation_component_particulars);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  temp_2 = 
			  TRUEP(Suppress_updating_of_slot_value_representations_qm);
		  if (temp_2);
		  else if (M_CDR(Stack_of_slot_value_changes)) {
		      frame_and_slot_or_atom = Nil;
		      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
		      ab_loop_it_ = Nil;
		    next_loop_2:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop_2;
		      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      if (ATOM(frame_and_slot_or_atom))
			  goto end_loop_2;
		      temp_2 = EQ(slot_description,
			      M_CDR(frame_and_slot_or_atom));
		      if (temp_2);
		      else {
			  temp_3 = M_CDR(frame_and_slot_or_atom);
			  temp_2 = CONSP(temp_3) ? EQ(slot_description,
				  SECOND(frame_and_slot_or_atom)) && 
				  EQ(Nil,THIRD(frame_and_slot_or_atom)) && 
				  EQ(Nil,CDDDR(frame_and_slot_or_atom)) : 
				  TRUEP(Nil);
		      }
		      ab_loop_it_ = temp_2 ? (EQ(Chart,
			      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		      if (ab_loop_it_) {
			  temp_2 = TRUEP(ab_loop_it_);
			  goto end_1;
		      }
		      goto next_loop_2;
		    end_loop_2:
		      temp_2 = TRUEP(Qnil);
		    end_1:;
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if ( !temp_2)
		      update_all_representations_of_slot(Chart,
			      slot_description,Nil,Nil);
		  if (ISVREF(slot_description,(SI_Long)14L))
		      update_frame_name_references(Chart);
		  stack_change_pop_store = Nil;
		  cons_1 = Stack_of_slot_value_changes;
		  if (cons_1) {
		      stack_change_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qstack_change);
		      if (ISVREF(Available_stack_change_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = 
				  ISVREF(Available_stack_change_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = cons_1;
			  temp = Available_stack_change_conses_tail_vector;
			  temp_1 = Current_thread_index;
			  SVREF(temp,temp_1) = cons_1;
		      }
		      else {
			  temp = Available_stack_change_conses_vector;
			  temp_1 = Current_thread_index;
			  SVREF(temp,temp_1) = cons_1;
			  temp = Available_stack_change_conses_tail_vector;
			  temp_1 = Current_thread_index;
			  SVREF(temp,temp_1) = cons_1;
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
		  if (temp_2 ?  
			  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
			  : TRUEP(Nil))
		      do_deferred_updates_to_representations_in_tables();
		POP_SPECIAL();
		compilation_result = REST(parse_result);
	      POP_SPECIAL();
	  }
	  POP_UNWIND_PROTECT(0);
	  UNLOCK(Working_on_annotated_frame);
	  CONTINUE_UNWINDING(0);
      }
      result = VALUES_2(compilation_result,bad_phrase_qm);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object array_constant;      /* # */

static Object Qdata_series_descriptions;  /* data-series-descriptions */

/* DATA-SERIES-DESCRIPTIONS-EVALUATION-SETTER */
Object data_series_descriptions_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,201);
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
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_data_series_descriptions_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1);
    else
	temp_1 = array_constant;
    result = parse_text_string(3,temp_1,Qdata_series_descriptions,frame);
  end_data_series_descriptions_evaluation_setter:
    return result;
}

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_7;   /* "[deleted attribute]" */

/* DATA-SERIES-DESCRIPTIONS-EVALUATION-GETTER */
Object data_series_descriptions_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(177,202);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    6);
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
	      5);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		4);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  3);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    2);
	      slot_value_writer_qm = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdata_series_descriptions),
		      Qslot_value_writer);
	      if (slot_value_writer_qm) {
		  write_symbols_in_lower_case_qm = T;
		  write_symbols_parsably_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
			    0);
		      inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else
		  twrite(string_constant_7);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qpart_type;          /* part-type */

static Object Qpart_feature;       /* part-feature */

static Object Qscatter_chart_style;  /* scatter-chart-style */

static Object Qcolumn_chart_style;  /* column-chart-style */

static Object Qpart_type_description;  /* part-type-description */

/* SET-UP-PART-DICTIONARIES */
Object set_up_part_dictionaries(part_type)
    Object part_type;
{
    Object part_feature_description_1, temp, ab_loop_list_, included_part_type;
    Object ab_loop_list__1;

    x_note_fn_call(177,203);
    reclaim_grammar_tree_function(lookup_kb_specific_property_value(Qpart_type,
	    Directory_of_names_kbprop));
    mutate_kb_specific_property_value(Qpart_type,Nil,
	    Directory_of_names_kbprop);
    reclaim_grammar_tree_function(lookup_kb_specific_property_value(Qpart_feature,
	    Directory_of_names_kbprop));
    mutate_kb_specific_property_value(Qpart_feature,Nil,
	    Directory_of_names_kbprop);
    reclaim_grammar_tree_function(lookup_kb_specific_property_value(Qchart_style,
	    Directory_of_names_kbprop));
    mutate_kb_specific_property_value(Qchart_style,Nil,
	    Directory_of_names_kbprop);
    add_to_directory_of_names(Qline_chart_style,Qchart_style);
    add_to_directory_of_names(Qscatter_chart_style,Qchart_style);
    add_to_directory_of_names(Qcolumn_chart_style,Qchart_style);
    part_feature_description_1 = Nil;
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(part_type),
	    Qpart_type_description);
    temp = CDR(temp);
    ab_loop_list_ = CAR(temp);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    temp = CDR(ab_loop_list_);
    part_feature_description_1 = CAR(temp);
    temp = CDDDDR(part_feature_description_1);
    if (CAR(temp)) {
	temp = CDDDR(part_feature_description_1);
	add_to_directory_of_names(CAR(temp),Qpart_feature);
    }
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    included_part_type = Nil;
    ab_loop_list_ = part_type_descendant_part_types(part_type);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    included_part_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(included_part_type),
	    Qpart_type_description);
    temp = CDDR(temp);
    add_to_directory_of_names(CAR(temp),Qpart_type);
    part_feature_description_1 = Nil;
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(included_part_type),
	    Qpart_type_description);
    temp = CDR(temp);
    ab_loop_list__1 = CAR(temp);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
  next_loop_2:
    temp = CDR(ab_loop_list__1);
    part_feature_description_1 = CAR(temp);
    temp = CDDDDR(part_feature_description_1);
    if (CAR(temp)) {
	temp = CDDDR(part_feature_description_1);
	add_to_directory_of_names(CAR(temp),Qpart_feature);
    }
    ab_loop_list__1 = CDDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    goto next_loop_2;
  end_loop_2:;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* REDUCE-ANNOTATION-1 */
Object reduce_annotation_1(parse)
    Object parse;
{
    Object second_new_value, first_new_value;

    x_note_fn_call(177,204);
    second_new_value = FIRST(parse);
    first_new_value = SECOND(parse);
    M_FIRST(parse) = first_new_value;
    M_SECOND(parse) = second_new_value;
    return reduce_annotation(parse);
}

/* COMPILE-CHART-ANNOTATIONS-FOR-SLOT */
Object compile_chart_annotations_for_slot varargs_1(int, n)
{
    Object parse_result, chart, gensymed_symbol;
    volatile Object result_1;
    volatile Object error_message_qm;
    Object current_annotated_frame;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(177,205);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    chart = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      if (OPTIONAL_ARG_P_nonrelocating())
	  OPTIONAL_ARG_nonrelocating();
      END_ARGS_nonrelocating();
      result_1 = Nil;
      error_message_qm = Nil;
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(0)) {
	  current_annotated_frame = Chart;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  0);
	    result = compile_part_description(parse_result,Qchart);
	    MVS_2(result,result_1,error_message_qm);
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(0);
      result = VALUES_2(result_1,error_message_qm);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* WRITE-CHART-ANNOTATIONS-FROM-SLOT */
Object write_chart_annotations_from_slot(annotations_slot_value,
	    gensymed_symbol)
    Object annotations_slot_value, gensymed_symbol;
{
    x_note_fn_call(177,206);
    return write_part_description(1,annotations_slot_value);
}

static Object Qfloat_array;        /* float-array */

static Object Qtruth_value;        /* truth-value */

/* MAKE-EVALUATION-VALUE-BASED-ON-TYPE-AND-SLOT-PRESENCE */
Object make_evaluation_value_based_on_type_and_slot_presence(plist,slot_name)
    Object plist, slot_name;
{
    Object member_result, value, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float, gensymed_symbol;
    double aref_new_value;

    x_note_fn_call(177,207);
    member_result = memq_function(slot_name,plist);
    if (member_result) {
	value = SECOND(member_result);
	if (FIXNUMP(value))
	    temp = value;
	else if ( !TRUEP(value))
	    temp = Evaluation_false_value;
	else if (EQ(value,T))
	    temp = Evaluation_true_value;
	else if (SYMBOLP(value))
	    temp = value;
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_float(value);
	else if (FLOATP(value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp = new_float;
	}
	else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    temp = copy_managed_long(value);
	else if (INLINE_LONG_P(value) != (SI_Long)0L)
	    temp = make_evaluation_long(value);
	else if (text_string_p(value))
	    temp = copy_as_wide_string(value);
	else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	    gensymed_symbol = M_CAR(value);
	    if (FIXNUM_EQ(gensymed_symbol,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(gensymed_symbol,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(gensymed_symbol,Qtruth_value);
	}
	else
	    temp = error((SI_Long)2L,
		    "Bad type ~a for make-evaluation-value-based-on-type.",
		    type_of(value));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qcopy_for_slot_value;  /* copy-for-slot-value */

/* CHART-FEATURES-EVALUATION-SETTER */
Object chart_features_evaluation_setter(chart_features,frame,
	    slot_description,gensymed_symbol)
    Object chart_features, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, list_of_features;
    Object held_vector, feature_name, attribute_value, feature_value;
    SI_Long next_index, length_1, gensymed_symbol_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,208);
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
			  !TRUEP(type_specification_type_p__with_explanation(chart_features,
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(chart_features,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_features_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    list_of_features = Nil;
    gensymed_symbol = chart_features;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    feature_name = Nil;
    attribute_value = Nil;
    feature_value = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    feature_name = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    gensymed_symbol_1 = next_index + (SI_Long)1L;
    attribute_value = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,
	    gensymed_symbol_1 + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(held_vector,(gensymed_symbol_1 >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol_1 & (SI_Long)1023L);
    feature_value = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    temp_1 = phrase_list_2(Qquote,get_internal_spelling(feature_name,
	    Qpart_feature));
    temp_1 = phrase_list_2(temp_1,phrase_list_2(Qcopy_for_slot_value,
	    phrase_list_2(Qquote,CONSP(feature_value) && 
	    EQ(M_CDR(feature_value),Qtruth_value) ? 
	    evaluation_truth_value_is_true_p(feature_value) : 
	    FIXNUMP(feature_value) || feature_value && 
	    SYMBOLP(feature_value) || SIMPLE_VECTOR_P(feature_value) ? 
	    feature_value : copy_if_evaluation_value_1(feature_value))));
    list_of_features = phrase_cons(temp_1,list_of_features);
    goto next_loop;
  end_loop:
    result = VALUES_1(list_of_features);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_chart_features_evaluation_setter:
    return result;
}

static Object Qtext_color;         /* text-color */

static Object Qborder_color;       /* border-color */

static Object Qtext_alignment;     /* text-alignment */

static Object Qtext_size;          /* text-size */

static Object Qwidth;              /* width */

static Object Qheight;             /* height */

static Object Qindicator;          /* indicator */

static Object Qindicator_visible;  /* indicator-visible */

static Object Qconnection_line_visible;  /* connection-line-visible */

static Object Qline_from_last_to_first_point_visible;  /* line-from-last-to-first-point-visible */

static Object Qnumber_of_tickmarks;  /* number-of-tickmarks */

static Object Qtickmark_interval;  /* tickmark-interval */

/* CHART-FEATURES-EVALUATION-GETTER */
Object chart_features_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, value;

    x_note_fn_call(177,209);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qline_color,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qline_color,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qtext_color,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qtext_color,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qbackground_color,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qbackground_color,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qborder_color,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qborder_color,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qgrid_color,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qgrid_color,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qgrid_visible,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qgrid_visible,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qtext_alignment,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qtext_alignment,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qtext_size,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qtext_size,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qwidth,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qwidth,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qheight,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qheight,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qindicator,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qindicator,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qindicator_visible,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qindicator_visible,
		value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qconnection_line_visible,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,
		Qconnection_line_visible,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qline_from_last_to_first_point_visible,
	    Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,
		Qline_from_last_to_first_point_visible,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qaxis_minimum,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qaxis_minimum,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qaxis_maximum,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qaxis_maximum,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qaxis_crossover,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qaxis_crossover,value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qnumber_of_tickmarks,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qnumber_of_tickmarks,
		value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qtickmark_interval,Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qtickmark_interval,
		value);
    value = 
	    make_evaluation_value_based_on_type_and_slot_presence(slot_value,
	    get_internal_spelling(Qnumber_of_significant_digits,
	    Qpart_feature));
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,
		Qnumber_of_significant_digits,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object Qlookup_subpart_of_collection;  /* lookup-subpart-of-collection */

static Object Qpart_name;          /* part-name */

/* FEATURE-PATH-EVALUATION-SETTER */
Object feature_path_evaluation_setter(feature_path,frame,slot_description,
	    gensymed_symbol)
    Object feature_path, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, internal_path;
    Object held_vector, path_element, elt_1, validated_elt, gensymed_symbol_1;
    Object gensymed_symbol_2, car_new_value;
    SI_Long next_index, length_1;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,210);
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
			  !TRUEP(type_specification_type_p__with_explanation(feature_path,
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(feature_path,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_feature_path_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    internal_path = Qcurrent_part_description;
    gensymed_symbol = feature_path;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    path_element = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    path_element = validated_elt;
    gensymed_symbol = path_element;
    gensymed_symbol_1 = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_2 = gensymed_symbol_1;
    M_CAR(gensymed_symbol_2) = Qlookup_subpart_of_collection;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    M_CAR(gensymed_symbol_2) = internal_path;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    car_new_value = phrase_list_2(Qquote,estructure_slot(gensymed_symbol,
	    Qpart_index,Nil) ? Qsubpart_exceptions : Qsubpart_defaults);
    M_CAR(gensymed_symbol_2) = car_new_value;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    car_new_value = phrase_list_2(Qquote,estructure_slot(gensymed_symbol,
	    Qpart_name,Nil));
    M_CAR(gensymed_symbol_2) = car_new_value;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp_2 = FIXNUMP(estructure_slot(gensymed_symbol,Qpart_index,Nil));
    if (temp_2);
    else if (estructure_slot(gensymed_symbol,Qpart_index,Nil)) {
	temp_1 = estructure_slot(gensymed_symbol,Qpart_index,Nil);
	temp_2 = SYMBOLP(temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2);
    else {
	temp_1 = estructure_slot(gensymed_symbol,Qpart_index,Nil);
	temp_2 = SIMPLE_VECTOR_P(temp_1);
    }
    car_new_value = temp_2 ? estructure_slot(gensymed_symbol,Qpart_index,
	    Nil) : 
	    copy_if_evaluation_value_1(estructure_slot(gensymed_symbol,
	    Qpart_index,Nil));
    M_CAR(gensymed_symbol_2) = car_new_value;
    internal_path = gensymed_symbol_1;
    goto next_loop;
  end_loop:
    result = VALUES_1(internal_path);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_feature_path_evaluation_setter:
    return result;
}

/* FEATURE-PATH-EVALUATION-GETTER */
Object feature_path_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(177,211);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object Qattributes;         /* attributes */

static Object Qpath;               /* path */

/* CHART-ANNOTATION-EVALUATION-SETTER */
Object chart_annotation_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,212);
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
			  list_constant_11))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_12,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_annotation_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qattributes,Nil);
    result = import_attributes(2,temp_1,estructure_slot(gensymed_symbol,
	    Qpath,Nil));
  end_chart_annotation_evaluation_setter:
    return result;
}

/* CHART-ANNOTATION-EVALUATION-GETTER */
Object chart_annotation_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(177,213);
    GENSYM_RETURN_ONE(Nil);
    return VALUES_1(Nil);
}

static Object Qchart_features;     /* chart-features */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qfeature_path;       /* feature-path */

static Object Qset_simple_part_feature;  /* set-simple-part-feature */

/* IMPORT-ATTRIBUTES */
Object import_attributes varargs_1(int, n)
{
    Object attributes;
    Object path, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object list_of_features, internal_path, prev_feature, cdr_1, ab_loop_list_;
    Object temp, car_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(177,214);
    INIT_ARGS_nonrelocating();
    attributes = REQUIRED_ARG_nonrelocating();
    path = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_features),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = attributes;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    else
	list_of_features = parse_result_or_bad_phrase;
    if (path) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfeature_path),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = path;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase))
	    return VALUES_2(Bad_phrase,error_string_qm);
	else
	    internal_path = parse_result_or_bad_phrase;
    }
    else
	internal_path = Qcurrent_part_description;
    prev_feature = Nil;
    cdr_1 = Nil;
    ab_loop_list_ = list_of_features;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    prev_feature = CAR(ab_loop_list_);
    cdr_1 = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(cdr_1))
	goto end_loop;
    temp = copy_tree_using_phrase_conses(internal_path);
    car_new_value = phrase_cons(Qset_simple_part_feature,phrase_cons(temp,
	    CAR(cdr_1)));
    M_CAR(cdr_1) = car_new_value;
    goto next_loop;
  end_loop:
    temp = copy_tree_using_phrase_conses(internal_path);
    car_new_value = phrase_cons(Qset_simple_part_feature,phrase_cons(temp,
	    CAR(list_of_features)));
    M_CAR(list_of_features) = car_new_value;
    return VALUES_1(list_of_features);
    return VALUES_1(Qnil);
}

static Object list_constant_13;    /* # */

static Object list_constant_14;    /* # */

static Object Qchart_annotation;   /* chart-annotation */

/* CHART-ANNOTATIONS-SEQUENCE-EVALUATION-SETTER */
Object chart_annotations_sequence_evaluation_setter(annotations,frame,
	    slot_description,gensymed_symbol)
    Object annotations, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object list_of_annotations, held_vector, chart_annotation, new_annotations;
    Object elt_1, validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,215);
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
			  !TRUEP(type_specification_type_p__with_explanation(annotations,
			  list_constant_13))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(annotations,
			      list_constant_14,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_annotations_sequence_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    list_of_annotations = Nil;
    gensymed_symbol = annotations;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    chart_annotation = Nil;
    new_annotations = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    chart_annotation = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotation),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = chart_annotation;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	new_annotations = parse_result_or_bad_phrase;
    list_of_annotations = nconc2(new_annotations,list_of_annotations);
    goto next_loop;
  end_loop:
    result = VALUES_1(list_of_annotations);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_annotations_sequence_evaluation_setter:
    return result;
}

/* CHART-ANNOTATIONS-SEQUENCE-EVALUATION-GETTER */
Object chart_annotations_sequence_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(177,216);
    GENSYM_RETURN_ONE(allocate_evaluation_sequence(subpart_features(slot_value,
	    Nil)));
    return VALUES_1(Nil);
}

static Object Qab_structure;       /* structure */

/* SUBPART-FEATURES */
Object subpart_features(subpart_list,path)
    Object subpart_list, path;
{
    Object subpart_defaults, subpart_exceptions, exceptions_qm, defaults_qm;
    Object part_index_qm, category_evaluator_interface, function;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, attributes, result_1, part, values_1;
    Object ab_loop_list_, temp, value, ab_loop_list__1, temp_1, item_or_value;
    Object x2, svref_new_value, thing;
    SI_Long gensymed_symbol_4, svref_arg_2;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,217);
    subpart_defaults = getfq_function_no_default(subpart_list,
	    Qsubpart_defaults);
    subpart_exceptions = getfq_function_no_default(subpart_list,
	    Qsubpart_exceptions);
    exceptions_qm = getfq_function_no_default(subpart_list,
	    Qsubpart_exceptions);
    defaults_qm = getfq_function_no_default(subpart_list,Qsubpart_defaults);
    part_index_qm = getfq_function_no_default(subpart_list,Qpart_index);
    if ( !TRUEP(exceptions_qm) &&  !TRUEP(defaults_qm) || exceptions_qm && 
	    defaults_qm && FIXNUM_GT(length(subpart_list),part_index_qm ? 
	    FIX((SI_Long)6L) : FIX((SI_Long)4L)) || ( 
	    !TRUEP(exceptions_qm) ||  !TRUEP(defaults_qm)) && 
	    FIXNUM_GT(length(subpart_list),part_index_qm ? 
	    FIX((SI_Long)4L) : FIX((SI_Long)2L))) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_features),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = subpart_list;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    attributes = inline_funcall_3(gensymed_symbol,
		    gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    attributes = Nil;
    }
    else
	attributes = Nil;
    result_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Subpart_exceptions,Qsubpart_exceptions,subpart_exceptions,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Subpart_defaults,Qsubpart_defaults,subpart_defaults,
	      0);
	if (Subpart_defaults) {
	    part = Nil;
	    values_1 = Nil;
	    ab_loop_list_ = Subpart_defaults;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    part = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    values_1 = CAR(temp);
	    value = Nil;
	    ab_loop_list__1 = values_1;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    value = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp = CDR(value);
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_4 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_4 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qpart_name;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qpart_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = part;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = part;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    temp = subpart_features(temp,
		    eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
		    copy_list_using_eval_conses_1(path)));
	    result_1 = nconc2(temp,result_1);
	    goto next_loop_1;
	  end_loop_1:;
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:;
	}
	if (Subpart_exceptions) {
	    part = Nil;
	    values_1 = Nil;
	    ab_loop_list_ = Subpart_exceptions;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	  next_loop_2:
	    part = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    values_1 = CAR(temp);
	    value = Nil;
	    ab_loop_list__1 = values_1;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    value = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp = CDR(value);
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		    (SI_Long)1L));
	    gensymed_symbol_4 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_4 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qpart_name;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qpart_name;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = part;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = part;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qpart_index;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Qpart_index;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		thing = getfq_function_no_default(CDR(value),Qpart_index);
		item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) 
			|| SIMPLE_VECTOR_P(thing) ? thing : 
			copy_if_evaluation_value_1(thing);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		thing = getfq_function_no_default(CDR(value),Qpart_index);
		item_or_value = FIXNUMP(thing) || thing && SYMBOLP(thing) 
			|| SIMPLE_VECTOR_P(thing) ? thing : 
			copy_if_evaluation_value_1(thing);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    temp = subpart_features(temp,
		    eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
		    copy_list_using_eval_conses_1(path)));
	    result_1 = nconc2(temp,result_1);
	    goto next_loop_3;
	  end_loop_3:;
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    goto next_loop_2;
	  end_loop_2:;
	}
	if (attributes) {
	    if (path) {
		gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L 
			+ (SI_Long)1L));
		gensymed_symbol_4 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_4 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattributes;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)1L)) = Qattributes;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = attributes;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = attributes;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qpath;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)3L)) = Qpath;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = 
			    allocate_evaluation_sequence(nreverse(path));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = 
			    allocate_evaluation_sequence(nreverse(path));
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
		}
		temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    }
	    else {
		gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L 
			+ (SI_Long)1L));
		gensymed_symbol_4 = (SI_Long)0L;
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    svref_arg_2 = gensymed_symbol_4 + 
			    IFIX(Managed_array_index_offset);
		    ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_4 >>  
			    -  - (SI_Long)10L) + (SI_Long)2L);
		    svref_arg_2 = gensymed_symbol_4 & (SI_Long)1023L;
		    ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size))
		    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qattributes;
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    SVREF(temp_1,FIX((SI_Long)1L)) = Qattributes;
		}
		if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    item_or_value = attributes;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    temp_1 = temp_2 ? get_reference_to_item(item_or_value) 
			    : item_or_value;
		    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
		}
		else {
		    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		    item_or_value = attributes;
		    if (SIMPLE_VECTOR_P(item_or_value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
			    > (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			    (SI_Long)1L),Qavailable_frame_vector)) {
			x2 = ISVREF(item_or_value,(SI_Long)1L);
			temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_2 = TRUEP(Nil);
		    svref_new_value = temp_2 ? 
			    get_reference_to_item(item_or_value) : 
			    item_or_value;
		    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
		}
		temp = eval_cons_1(gensymed_symbol,Qab_structure);
	    }
	    result_1 = eval_cons_1(temp,result_1);
	}
	else
	    reclaim_eval_list_1(path);
	result = VALUES_1(result_1);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SET-CHART-ANNOTATION-ROOT-DENOTATION */
Object set_chart_annotation_root_denotation varargs_1(int, n)
{
    Object feature, subpart_type;
    Object index_qm, gensymed_symbol, gensymed_symbol_1, car_new_value, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(177,218);
    INIT_ARGS_nonrelocating();
    feature = REQUIRED_ARG_nonrelocating();
    subpart_type = REQUIRED_ARG_nonrelocating();
    index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(CADR(feature),Qcurrent_part_description)) {
	gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qlookup_subpart_of_collection;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qcurrent_part_description;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = phrase_list_2(Qquote,index_qm ? 
		Qsubpart_exceptions : Qsubpart_defaults);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	car_new_value = phrase_list_2(Qquote,subpart_type);
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = index_qm;
	return VALUES_1(M_CADR(feature) = gensymed_symbol);
    }
    else {
	temp = CADR(feature);
	if (CONSP(temp))
	    return set_chart_annotation_root_denotation(3,CADR(feature),
		    subpart_type,index_qm);
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object Qchart_annotations_sequence;  /* chart-annotations-sequence */

static Object Qannotations;        /* annotations */

/* CHART-DATA-POINT-FEATURES-EVALUATION-SETTER */
Object chart_data_point_features_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm, internal_annotations;
    Object annotation, ab_loop_list_;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,219);
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
			  list_constant_15))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_16,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_data_point_features_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qannotations,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	internal_annotations = parse_result_or_bad_phrase;
    annotation = Nil;
    ab_loop_list_ = internal_annotations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    annotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_chart_annotation_root_denotation(2,annotation,Qchart_data_point);
    goto next_loop;
  end_loop:
    result = VALUES_1(internal_annotations);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_data_point_features_evaluation_setter:
    return result;
}

/* CHART-DATA-POINT-FEATURES-EVALUATION-GETTER */
Object chart_data_point_features_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(177,220);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qannotations,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object Qindex;              /* index */

/* CHART-DATA-SERIES-FEATURES-EVALUATION-SETTER */
Object chart_data_series_features_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object internal_annotations, annotation, ab_loop_list_;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,221);
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
			  list_constant_17))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_18,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_data_series_features_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qannotations,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	internal_annotations = parse_result_or_bad_phrase;
    annotation = Nil;
    ab_loop_list_ = internal_annotations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    annotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = annotation;
    set_chart_annotation_root_denotation(3,temp_1,Qdata_series,
	    estructure_slot(gensymed_symbol,Qindex,Nil));
    goto next_loop;
  end_loop:
    result = VALUES_1(internal_annotations);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_data_series_features_evaluation_setter:
    return result;
}

/* CHART-DATA-SERIES-FEATURES-EVALUATION-GETTER */
Object chart_data_series_features_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, thing, value, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(177,222);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    thing = getfq_function_no_default(CDR(slot_value),Qpart_index);
    value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qindex,value);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qannotations,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_19;    /* # */

/* CHART-AXIS-FEATURES-EVALUATION-SETTER */
Object chart_axis_features_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object internal_annotations, annotation, ab_loop_list_;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,223);
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
			  list_constant_19))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_18,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_axis_features_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qannotations,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	internal_annotations = parse_result_or_bad_phrase;
    annotation = Nil;
    ab_loop_list_ = internal_annotations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    annotation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = annotation;
    set_chart_annotation_root_denotation(3,temp_1,Qaxis,
	    estructure_slot(gensymed_symbol,Qindex,Nil));
    goto next_loop;
  end_loop:
    result = VALUES_1(internal_annotations);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_axis_features_evaluation_setter:
    return result;
}

/* CHART-AXIS-FEATURES-EVALUATION-GETTER */
Object chart_axis_features_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, thing, value, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(177,224);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    thing = getfq_function_no_default(CDR(slot_value),Qpart_index);
    value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qindex,value);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_annotations_sequence),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qannotations,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

static Object Qchart_data_point_features;  /* chart-data-point-features */

/* CHART-DATA-POINT-FEATURES-SEQUENCE-EVALUATION-SETTER */
Object chart_data_point_features_sequence_evaluation_setter(features_sequence,
	    frame,slot_description,gensymed_symbol)
    Object features_sequence, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, list_of_features;
    Object held_vector, features_element, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,225);
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
			  !TRUEP(type_specification_type_p__with_explanation(features_sequence,
			  list_constant_20))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(features_sequence,
			      list_constant_21,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_data_point_features_sequence_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    list_of_features = Nil;
    gensymed_symbol = features_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    features_element = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    features_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_point_features),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = features_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    list_of_features = nconc2(temp_1,list_of_features);
    goto next_loop;
  end_loop:
    result = VALUES_1(list_of_features);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_data_point_features_sequence_evaluation_setter:
    return result;
}

/* CHART-DATA-POINT-FEATURES-SEQUENCE-EVALUATION-GETTER */
Object chart_data_point_features_sequence_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(177,226);
    if (slot_value) {
	element = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_point_features),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = element;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_22;    /* # */

static Object list_constant_23;    /* # */

static Object Qchart_data_series_features;  /* chart-data-series-features */

/* CHART-DATA-SERIES-FEATURES-SEQUENCE-EVALUATION-SETTER */
Object chart_data_series_features_sequence_evaluation_setter(features_sequence,
	    frame,slot_description,gensymed_symbol)
    Object features_sequence, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, list_of_features;
    Object held_vector, features_element, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,227);
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
			  !TRUEP(type_specification_type_p__with_explanation(features_sequence,
			  list_constant_22))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(features_sequence,
			      list_constant_23,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_data_series_features_sequence_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    list_of_features = Nil;
    gensymed_symbol = features_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    features_element = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    features_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_series_features),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = features_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    list_of_features = nconc2(temp_1,list_of_features);
    goto next_loop;
  end_loop:
    result = VALUES_1(list_of_features);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_data_series_features_sequence_evaluation_setter:
    return result;
}

/* CHART-DATA-SERIES-FEATURES-SEQUENCE-EVALUATION-GETTER */
Object chart_data_series_features_sequence_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(177,228);
    if (slot_value) {
	element = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_series_features),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = element;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_24;    /* # */

static Object list_constant_25;    /* # */

static Object Qchart_axis_features;  /* chart-axis-features */

/* CHART-AXIS-FEATURES-SEQUENCE-EVALUATION-SETTER */
Object chart_axis_features_sequence_evaluation_setter(features_sequence,
	    frame,slot_description,gensymed_symbol)
    Object features_sequence, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, list_of_features;
    Object held_vector, features_element, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,229);
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
			  !TRUEP(type_specification_type_p__with_explanation(features_sequence,
			  list_constant_24))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(features_sequence,
			      list_constant_25,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_axis_features_sequence_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    list_of_features = Nil;
    gensymed_symbol = features_sequence;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    features_element = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    features_element = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_axis_features),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = features_element;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    list_of_features = nconc2(temp_1,list_of_features);
    goto next_loop;
  end_loop:
    result = VALUES_1(list_of_features);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_safe_category_setter_calling_block:
  end_chart_axis_features_sequence_evaluation_setter:
    return result;
}

/* CHART-AXIS-FEATURES-SEQUENCE-EVALUATION-GETTER */
Object chart_axis_features_sequence_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object element, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(177,230);
    if (slot_value) {
	element = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_axis_features),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = element;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	ab_loopvar__1 = eval_cons_1(temp,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMBINE-LISTS-INTO-ONE-EVAL-LIST */
Object combine_lists_into_one_eval_list(l1,l2)
    Object l1, l2;
{
    Object l3, elt_1, ab_loop_list_;

    x_note_fn_call(177,231);
    l3 = nreverse(copy_list_using_eval_conses_1(l1));
    elt_1 = Nil;
    ab_loop_list_ = l2;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    elt_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    l3 = eval_cons_1(elt_1,l3);
    goto next_loop;
  end_loop:
    return nreverse(l3);
    return VALUES_1(Qnil);
}

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

static Object Qdefault_features;   /* default-features */

static Object Qdata_point_features;  /* data-point-features */

static Object Qchart_data_point_features_sequence;  /* chart-data-point-features-sequence */

static Object Qdata_series_features;  /* data-series-features */

static Object Qchart_data_series_features_sequence;  /* chart-data-series-features-sequence */

static Object Qaxis_features;      /* axis-features */

static Object Qchart_axis_features_sequence;  /* chart-axis-features-sequence */

static Object Qsc;                 /* \; */

static Object string_constant_8;   /* "~NT " */

static Object string_constant_9;   /* "~NV must be one of the following types: ~a" */

/* CHART-ANNOTATIONS-EVALUATION-SETTER */
Object chart_annotations_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object chart_default_features, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, parse_result_or_bad_phrase;
    Object error_string_qm, chart_data_point_features;
    Object chart_data_series_features, chart_axis_features;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(177,232);
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
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_27,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_chart_annotations_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_28))
	result = VALUES_1(Nil);
    else if (type_specification_type_p(gensymed_symbol,list_constant_29)) {
	gensymed_symbol = evaluation_value;
	chart_default_features = estructure_slot(gensymed_symbol,
		Qdefault_features,Nil) ? import_attributes(1,
		estructure_slot(gensymed_symbol,Qdefault_features,Nil)) : Qnil;
	if (estructure_slot(gensymed_symbol,Qdata_point_features,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_point_features_sequence),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			Qdata_point_features,Nil);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		chart_data_point_features = parse_result_or_bad_phrase;
	}
	else
	    chart_data_point_features = Nil;
	if (estructure_slot(gensymed_symbol,Qdata_series_features,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_series_features_sequence),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			Qdata_series_features,Nil);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		chart_data_series_features = parse_result_or_bad_phrase;
	}
	else
	    chart_data_series_features = Nil;
	if (estructure_slot(gensymed_symbol,Qaxis_features,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_axis_features_sequence),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol = estructure_slot(gensymed_symbol,
			Qaxis_features,Nil);
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		chart_axis_features = parse_result_or_bad_phrase;
	}
	else
	    chart_axis_features = Nil;
	result = phrase_cons(Qsc,nconc2(chart_default_features,
		nconc2(chart_data_point_features,
		nconc2(chart_data_series_features,chart_axis_features))));
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
		  tformat(2,string_constant_8,list_constant_28);
		  tformat(2,string_constant_8,list_constant_29);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_9,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_chart_annotations_evaluation_setter:
    return result;
}

/* CHART-ANNOTATIONS-EVALUATION-GETTER */
Object chart_annotations_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object subpart_defaults, subpart_exceptions, default_features_internal;
    Object chart_data_point_defaults, axis_defaults, data_series_defaults;
    Object axis_exceptions, data_series_exceptions;
    Object chart_data_point_features_internal, chart_axis_features_internal;
    Object chart_data_series_features_internal, gensymed_symbol;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, value;
    Object temp;
    Declare_special(2);

    x_note_fn_call(177,233);
    if (slot_value) {
	subpart_defaults = getfq_function_no_default(CDR(slot_value),
		Qsubpart_defaults);
	PUSH_SPECIAL_WITH_SYMBOL(Subpart_defaults,Qsubpart_defaults,subpart_defaults,
		1);
	  subpart_exceptions = getfq_function_no_default(CDR(slot_value),
		  Qsubpart_exceptions);
	  PUSH_SPECIAL_WITH_SYMBOL(Subpart_exceptions,Qsubpart_exceptions,subpart_exceptions,
		  0);
	    default_features_internal =  !TRUEP(Subpart_defaults) &&  
		    !TRUEP(Subpart_exceptions) && IFIX(length(slot_value)) 
		    > (SI_Long)2L || ( !TRUEP(Subpart_defaults) ||  
		    !TRUEP(Subpart_exceptions)) && 
		    IFIX(length(slot_value)) > (SI_Long)4L || 
		    Subpart_defaults && Subpart_exceptions && 
		    IFIX(length(slot_value)) > (SI_Long)5L ? 
		    CDR(slot_value) : Nil;
	    chart_data_point_defaults = 
		    getfq_function_no_default(Subpart_defaults,
		    Qchart_data_point);
	    axis_defaults = getfq_function_no_default(Subpart_defaults,Qaxis);
	    data_series_defaults = 
		    getfq_function_no_default(Subpart_defaults,Qdata_series);
	    axis_exceptions = getfq_function_no_default(Subpart_exceptions,
		    Qaxis);
	    data_series_exceptions = 
		    getfq_function_no_default(Subpart_exceptions,Qdata_series);
	    chart_data_point_features_internal = chart_data_point_defaults;
	    chart_axis_features_internal = 
		    combine_lists_into_one_eval_list(axis_defaults,
		    axis_exceptions);
	    chart_data_series_features_internal = 
		    combine_lists_into_one_eval_list(data_series_defaults,
		    data_series_exceptions);
	    if (default_features_internal || 
		    chart_data_point_features_internal || 
		    chart_data_series_features_internal || 
		    chart_axis_features_internal) {
		gensymed_symbol = allocate_evaluation_structure(Nil);
		if (default_features_internal) {
		    category_evaluator_interface = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_features),
			    Qcategory_evaluator_interface);
		    function = category_evaluator_interface ? 
			    ISVREF(category_evaluator_interface,
			    (SI_Long)2L) : Qnil;
		    if (function) {
			gensymed_symbol_1 = function;
			gensymed_symbol_2 = default_features_internal;
			gensymed_symbol_3 = Nil;
			gensymed_symbol_4 = Nil;
			value = inline_funcall_3(gensymed_symbol_1,
				gensymed_symbol_2,gensymed_symbol_3,
				gensymed_symbol_4);
		    }
		    else
			value = Nil;
		}
		else
		    value = Nil;
		if (value)
		    set_evaluation_structure_slot(gensymed_symbol,
			    Qdefault_features,value);
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_point_features_sequence),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_1 = function;
		    gensymed_symbol_2 = chart_data_point_features_internal;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    value = inline_funcall_3(gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4);
		}
		else
		    value = Nil;
		if (value)
		    set_evaluation_structure_slot(gensymed_symbol,
			    Qdata_point_features,value);
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_data_series_features_sequence),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_1 = function;
		    gensymed_symbol_2 = chart_data_series_features_internal;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    value = inline_funcall_3(gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4);
		}
		else
		    value = Nil;
		if (value)
		    set_evaluation_structure_slot(gensymed_symbol,
			    Qdata_series_features,value);
		category_evaluator_interface = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_axis_features_sequence),
			Qcategory_evaluator_interface);
		function = category_evaluator_interface ? 
			ISVREF(category_evaluator_interface,(SI_Long)2L) : 
			Qnil;
		if (function) {
		    gensymed_symbol_1 = function;
		    gensymed_symbol_2 = chart_axis_features_internal;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    value = inline_funcall_3(gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4);
		}
		else
		    value = Nil;
		if (value)
		    set_evaluation_structure_slot(gensymed_symbol,
			    Qaxis_features,value);
		reclaim_eval_list_1(chart_axis_features_internal);
		reclaim_eval_list_1(chart_data_series_features_internal);
		temp = gensymed_symbol;
	    }
	    else
		temp = Nil;
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* INITIAL-CHART-AXIS-COMPUTED-DETAILS */
Object initial_chart_axis_computed_details(class_1)
    Object class_1;
{
    x_note_fn_call(177,234);
    return VALUES_1(Nil);
}

static Object Qaxis_1;             /* axis-1 */

static Object Qaxis_2;             /* axis-2 */

/* GET-CHART-AXIS-COMPUTED-DETAILS */
Object get_chart_axis_computed_details(chart)
    Object chart;
{
    Object computed_annotations_qm, gensymed_symbol, temp, item_or_value, x2;
    Object svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,235);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      computed_annotations_qm = get_lookup_slot_value_given_default(Chart,
	      Qcomputed_annotations,Nil);
      if (computed_annotations_qm) {
	  gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + 
		  (SI_Long)1L));
	  gensymed_symbol_1 = (SI_Long)0L;
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      svref_arg_2 = gensymed_symbol_1 + 
		      IFIX(Managed_array_index_offset);
	      ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L);
	      svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	      ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qaxis_1;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)1L)) = Qaxis_1;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = build_axis_bounds_structure(Chart,
		      computed_annotations_qm,FIX((SI_Long)0L));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = build_axis_bounds_structure(Chart,
		      computed_annotations_qm,FIX((SI_Long)0L));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size))
	      SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qaxis_2;
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)3L)) = Qaxis_2;
	  }
	  if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		  Maximum_in_place_array_size)) {
	      item_or_value = build_axis_bounds_structure(Chart,
		      computed_annotations_qm,FIX((SI_Long)1L));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      temp = temp_1 ? get_reference_to_item(item_or_value) : 
		      item_or_value;
	      SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
	  }
	  else {
	      temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	      item_or_value = build_axis_bounds_structure(Chart,
		      computed_annotations_qm,FIX((SI_Long)1L));
	      if (SIMPLE_VECTOR_P(item_or_value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(item_or_value,
		      (SI_Long)1L),Qavailable_frame_vector)) {
		  x2 = ISVREF(item_or_value,(SI_Long)1L);
		  temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      svref_new_value = temp_1 ? 
		      get_reference_to_item(item_or_value) : item_or_value;
	      SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
	  }
	  temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
      }
      else
	  temp_2 = Nil;
      result = VALUES_1(temp_2);
    POP_SPECIAL();
    return result;
}

static Object Qaxis_is_discrete;   /* axis-is-discrete */

static Object Qmax_digits_in_exponent;  /* max-digits-in-exponent */

static Object Qmax_digits_before_point;  /* max-digits-before-point */

static Object Qmax_digits_after_point;  /* max-digits-after-point */

/* BUILD-AXIS-BOUNDS-STRUCTURE */
Object build_axis_bounds_structure(chart,computed_annotations,axis_number)
    Object chart, computed_annotations, axis_number;
{
    Object requested_axis, current_chart_frame, current_computation_frame;
    Object slot_value_number, temp, axis_crossover, axis_minimum, axis_maximum;
    Object axis_is_discrete, max_digits_in_exponent, max_digits_before_point;
    Object max_digits_after_point, gensymed_symbol, temp_1, item_or_value, x2;
    Object temp_3, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float, temp_4, structure;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(6);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,236);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,5);
      requested_axis = get_subpart_of_collection(computed_annotations,
	      Qsubparts,Qaxis,axis_number);
      LOCK(Working_on_chart);
      if (PUSH_UNWIND_PROTECT(1)) {
	  current_chart_frame = Chart;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_chart_frame,Qcurrent_chart_frame,current_chart_frame,
		  4);
	    LOCK(Working_on_lexical_computation_of_frame);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_computation_frame = Chart;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			3);
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      slot_value_number = 
			      get_simple_part_feature(requested_axis,
			      Qaxis_crossover);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			      == (SI_Long)1L)
			  temp = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			      == (SI_Long)1L)
			  temp = aref1(slot_value_number,FIX((SI_Long)0L));
		      else
			  temp = slot_value_number;
		      axis_crossover = lfloat(temp,float_constant_1);
		      PUSH_SPECIAL_WITH_SYMBOL(Axis_crossover,Qaxis_crossover,axis_crossover,
			      2);
			slot_value_number = 
				get_simple_part_feature(requested_axis,
				Qaxis_minimum);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				== (SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(slot_value_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				== (SI_Long)1L)
			    temp = aref1(slot_value_number,FIX((SI_Long)0L));
			else
			    temp = slot_value_number;
			axis_minimum = lfloat(temp,float_constant_1);
			PUSH_SPECIAL_WITH_SYMBOL(Axis_minimum,Qaxis_minimum,axis_minimum,
				1);
			  slot_value_number = 
				  get_simple_part_feature(requested_axis,
				  Qaxis_maximum);
			  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				  == (SI_Long)1L)
			      temp = 
				      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
				      (SI_Long)0L));
			  else if (INLINE_LONG_VECTOR_P(slot_value_number) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				  == (SI_Long)1L)
			      temp = aref1(slot_value_number,FIX((SI_Long)0L));
			  else
			      temp = slot_value_number;
			  axis_maximum = lfloat(temp,float_constant_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Axis_maximum,Qaxis_maximum,axis_maximum,
				  0);
			    temp = axis_number;
			    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
				axis_is_discrete = Nil;
			    else
				switch (INTEGER_TO_CHAR(temp)) {
				  case 0:
				    axis_is_discrete = 
					    plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame);
				    break;
				  case 1:
				    axis_is_discrete = 
					    plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
				    break;
				  default:
				    axis_is_discrete = Nil;
				    break;
				}
			    max_digits_in_exponent = 
				    get_simple_part_feature(requested_axis,
				    Qaxis_tickmark_label_max_digits_in_exponent);
			    max_digits_before_point = 
				    get_simple_part_feature(requested_axis,
				    Qaxis_tickmark_label_max_digits_before_point);
			    max_digits_after_point = 
				    get_simple_part_feature(requested_axis,
				    Qaxis_tickmark_label_max_digits_after_point);
			    gensymed_symbol = allocate_managed_array(1,
				    FIX((SI_Long)10L + (SI_Long)1L));
			    gensymed_symbol_1 = (SI_Long)0L;
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				svref_arg_2 = gensymed_symbol_1 + 
					IFIX(Managed_array_index_offset);
				ISVREF(gensymed_symbol,svref_arg_2) = 
					FIX((SI_Long)1L);
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,
					(gensymed_symbol_1 >>  -  - 
					(SI_Long)10L) + (SI_Long)2L);
				svref_arg_2 = gensymed_symbol_1 & 
					(SI_Long)1023L;
				ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),Maximum_in_place_array_size))
				SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
					Qaxis_is_discrete;
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				SVREF(temp_1,FIX((SI_Long)1L)) = 
					Qaxis_is_discrete;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				item_or_value = axis_is_discrete ? 
					Evaluation_true_value : 
					Evaluation_false_value;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(gensymed_symbol,FIX((SI_Long)4L)) = 
					temp_1;
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				item_or_value = axis_is_discrete ? 
					Evaluation_true_value : 
					Evaluation_false_value;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_3 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(temp_1,FIX((SI_Long)2L)) = temp_3;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),Maximum_in_place_array_size))
				SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
					Qaxis_heading;
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				SVREF(temp_1,FIX((SI_Long)3L)) = Qaxis_heading;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				item_or_value = 
					get_simple_part_feature(requested_axis,
					Qaxis_heading);
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(gensymed_symbol,FIX((SI_Long)6L)) = 
					temp_1;
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				item_or_value = 
					get_simple_part_feature(requested_axis,
					Qaxis_heading);
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_3 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(temp_1,FIX((SI_Long)4L)) = temp_3;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),Maximum_in_place_array_size))
				SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
					Qaxis_crossover;
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				SVREF(temp_1,FIX((SI_Long)5L)) = 
					Qaxis_crossover;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_1 = 
					    Vector_of_simple_float_array_pools;
				    temp_3 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_1 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_1) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_1 = 
						Available_float_array_conses_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_crossover);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(gensymed_symbol,FIX((SI_Long)8L)) = 
					temp_1;
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_3 = 
					    Vector_of_simple_float_array_pools;
				    temp_4 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_3 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_3) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_3 = 
						Available_float_array_conses_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_crossover);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_3 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(temp_1,FIX((SI_Long)6L)) = temp_3;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),Maximum_in_place_array_size))
				SVREF(gensymed_symbol,FIX((SI_Long)9L)) = 
					Qaxis_minimum;
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				SVREF(temp_1,FIX((SI_Long)7L)) = Qaxis_minimum;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_1 = 
					    Vector_of_simple_float_array_pools;
				    temp_3 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_1 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_1) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_1 = 
						Available_float_array_conses_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_minimum);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(gensymed_symbol,FIX((SI_Long)10L)) = 
					temp_1;
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_3 = 
					    Vector_of_simple_float_array_pools;
				    temp_4 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_3 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_3) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_3 = 
						Available_float_array_conses_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_minimum);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_3 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(temp_1,FIX((SI_Long)8L)) = temp_3;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),Maximum_in_place_array_size))
				SVREF(gensymed_symbol,FIX((SI_Long)11L)) = 
					Qaxis_maximum;
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				SVREF(temp_1,FIX((SI_Long)9L)) = Qaxis_maximum;
			    }
			    if (FIXNUM_LE(ISVREF(gensymed_symbol,
				    (SI_Long)1L),
					Maximum_in_place_array_size)) {
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_1 = 
					    Vector_of_simple_float_array_pools;
				    temp_3 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_1,FIX((SI_Long)1L)) = temp_3;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_1 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_1) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_1 = 
						Available_float_array_conses_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
					temp_1 = 
						Available_float_array_conses_tail_vector;
					temp_3 = Current_thread_index;
					SVREF(temp_1,temp_3) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_maximum);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_1 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(gensymed_symbol,FIX((SI_Long)12L)) = 
					temp_1;
			    }
			    else {
				temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
				amf_available_array_cons_qm = 
					ISVREF(Vector_of_simple_float_array_pools,
					(SI_Long)1L);
				if (amf_available_array_cons_qm) {
				    amf_array = 
					    M_CAR(amf_available_array_cons_qm);
				    temp_3 = 
					    Vector_of_simple_float_array_pools;
				    temp_4 = 
					    M_CDR(amf_available_array_cons_qm);
				    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
				    inline_note_reclaim_cons(amf_available_array_cons_qm,
					    Qfloat_array);
				    if (ISVREF(Available_float_array_conses_tail_vector,
					    IFIX(Current_thread_index))) {
					temp_3 = 
						ISVREF(Available_float_array_conses_tail_vector,
						IFIX(Current_thread_index));
					M_CDR(temp_3) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    else {
					temp_3 = 
						Available_float_array_conses_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
					temp_3 = 
						Available_float_array_conses_tail_vector;
					temp_4 = Current_thread_index;
					SVREF(temp_3,temp_4) = 
						amf_available_array_cons_qm;
				    }
				    M_CDR(amf_available_array_cons_qm) = Nil;
				    amf_result = amf_array;
				}
				else {
				    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					    FIX((SI_Long)1L));
				    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				    amf_result = 
					    generate_float_vector(FIX((SI_Long)1L));
				}
				new_float = amf_result;
				aref_new_value = 
					DOUBLE_FLOAT_TO_DOUBLE(Axis_maximum);
				DFLOAT_ISASET_1(new_float,(SI_Long)0L,
					aref_new_value);
				item_or_value = new_float;
				if (SIMPLE_VECTOR_P(item_or_value) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(item_or_value,
					(SI_Long)1L),
					    Qavailable_frame_vector)) {
				    x2 = ISVREF(item_or_value,(SI_Long)1L);
				    temp_2 = SIMPLE_VECTOR_P(x2) && 
					    EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? TRUEP(x2) : TRUEP(Qnil);
				}
				else
				    temp_2 = TRUEP(Nil);
				temp_3 = temp_2 ? 
					get_reference_to_item(item_or_value) 
					: item_or_value;
				SVREF(temp_1,FIX((SI_Long)10L)) = temp_3;
			    }
			    structure = eval_cons_1(gensymed_symbol,
				    Qab_structure);
			    if (max_digits_in_exponent)
				set_evaluation_structure_slot(structure,
					Qmax_digits_in_exponent,
					max_digits_in_exponent);
			    if (max_digits_before_point)
				set_evaluation_structure_slot(structure,
					Qmax_digits_before_point,
					max_digits_before_point);
			    if (max_digits_after_point)
				set_evaluation_structure_slot(structure,
					Qmax_digits_after_point,
					max_digits_after_point);
			    temp = structure;
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		POP_SPECIAL();
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Working_on_lexical_computation_of_frame);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    temp = result;
	  POP_SPECIAL();
	  SAVE_VALUES(VALUES_1(temp));
      }
      POP_UNWIND_PROTECT(1);
      UNLOCK(Working_on_chart);
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
      result = VALUES_1(result);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* INITIAL-CHART-DATA-SERIES */
Object initial_chart_data_series(class_1)
    Object class_1;
{
    x_note_fn_call(177,237);
    return VALUES_1(Nil);
}

/* GET-CHART-DATA-SERIES */
Object get_chart_data_series(chart)
    Object chart;
{
    Object data_series, data_series_element, ab_loop_list_, series_list;
    Object ab_loopvar_, ab_loopvar__1, temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,238);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      data_series = 
	      get_subpart_collection(get_lookup_slot_value_given_default(Chart,
	      Qcomputed_annotations,Nil),Qsubparts,Qdata_series);
      PUSH_SPECIAL_WITH_SYMBOL(Data_series,Qdata_series,data_series,0);
	if (Data_series) {
	    data_series_element = Nil;
	    ab_loop_list_ = Data_series;
	    series_list = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    data_series_element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__1 = 
		    eval_cons_1(build_data_series_structure(data_series_element),
		    Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		series_list = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop;
	  end_loop:
	    temp = allocate_evaluation_sequence(series_list);
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else
	    temp = Nil;
      POP_SPECIAL();
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

static Object Qdata_series_cache_1;  /* data-series-cache-1 */

static Object Qdata_series_cache_2;  /* data-series-cache-2 */

/* BUILD-DATA-SERIES-STRUCTURE */
Object build_data_series_structure(data_series_element)
    Object data_series_element;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(177,239);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qdata_series_cache_1;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qdata_series_cache_1;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		make_evaluation_sequence_from_managed_float_array(get_simple_part_feature(data_series_element,
		Qdata_series_data_cache_1_qm));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		make_evaluation_sequence_from_managed_float_array(get_simple_part_feature(data_series_element,
		Qdata_series_data_cache_1_qm));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qdata_series_cache_2;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qdata_series_cache_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		make_evaluation_sequence_from_managed_float_array(get_simple_part_feature(data_series_element,
		Qdata_series_data_cache_2_qm));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		make_evaluation_sequence_from_managed_float_array(get_simple_part_feature(data_series_element,
		Qdata_series_data_cache_2_qm));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qdata_series_source_kind;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qdata_series_source_kind;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = get_simple_part_feature(data_series_element,
		Qdata_series_source_kind);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = get_simple_part_feature(data_series_element,
		Qdata_series_source_kind);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(temp_2);
}

/* MAKE-EVALUATION-SEQUENCE-FROM-MANAGED-FLOAT-ARRAY */
Object make_evaluation_sequence_from_managed_float_array(managed_float_array)
    Object managed_float_array;
{
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    SI_Long index_1, ab_loop_bind_;
    double aref_new_value;

    x_note_fn_call(177,240);
    if (managed_float_array) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_float_array,(SI_Long)1L));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
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
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_float_array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
		(SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	ab_loopvar__2 = eval_cons_1(new_float,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	temp_2 = allocate_evaluation_sequence(temp_2);
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

/* DRAW-FOR-CHART */
Object draw_for_chart(chart)
    Object chart;
{
    Object current_graph_rendering, color_value, old_color_value;
    Object current_background_color_value, scale, gensymed_symbol_1, value;
    Object temp, temp_1, temp_2;
    SI_Long gensymed_symbol, gensymed_symbol_2, unshifted_result;
    Declare_stack_pointer;
    Declare_special(3);
    Object result;

    x_note_fn_call(177,241);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,2);
      if ((SI_Long)0L != (IFIX(ISVREF(Chart,(SI_Long)5L)) & (SI_Long)2048L))
	  result = draw_block_outline_in_current_image_plane(2,Chart,
		  Qforeground);
      else {
	  current_graph_rendering = 
		  get_or_make_graph_rendering_for_chart(Chart);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering,Qcurrent_graph_rendering,current_graph_rendering,
		  1);
	    color_value = ISVREF(Current_graph_rendering,(SI_Long)9L);
	    old_color_value = Current_background_color_value;
	    current_background_color_value = Current_background_color_value;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		    0);
	      set_current_background_color_value(color_value);
	      clear_data_clipping_rectangles();
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      scale = Current_image_x_scale;
	      gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	      gensymed_symbol_1 = gensymed_symbol_1 ? 
		      ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	      value = gensymed_symbol_1;
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
	      temp = FIX(gensymed_symbol + gensymed_symbol_2);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      scale = Current_image_y_scale;
	      gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	      gensymed_symbol_1 = gensymed_symbol_1 ? 
		      ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	      value = gensymed_symbol_1;
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
	      temp_1 = FIX(gensymed_symbol + gensymed_symbol_2);
	      gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	      scale = Current_image_x_scale;
	      gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	      gensymed_symbol_1 = gensymed_symbol_1 ? 
		      ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	      value = gensymed_symbol_1;
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
	      temp_2 = FIX(gensymed_symbol + gensymed_symbol_2);
	      gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	      scale = Current_image_y_scale;
	      gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	      gensymed_symbol_1 = gensymed_symbol_1 ? 
		      ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	      value = gensymed_symbol_1;
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
	      SAVE_VALUES(draw_current_graph_rendering(temp,temp_1,temp_2,
		      FIX(gensymed_symbol + gensymed_symbol_2)));
	      set_current_background_color_value(old_color_value);
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* UPDATE-CHART */
Object update_chart(chart)
    Object chart;
{
    Object current_annotated_frame, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(177,242);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(0)) {
	  current_annotated_frame = Chart;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  0);
	    update_the_computed_annotations(Chart);
	    erase_chart(Chart,Nil);
	    temp =  !((SI_Long)0L != (IFIX(ISVREF(Chart,(SI_Long)5L)) & 
		    (SI_Long)2048L)) ? update_images_of_block(Chart,Nil,T) 
		    : Nil;
	  POP_SPECIAL();
	  SAVE_VALUES(VALUES_1(temp));
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
      result = VALUES_1(result);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* REFRESH-IMAGES-OF-CHART */
Object refresh_images_of_chart(chart)
    Object chart;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(177,243);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      result = update_chart(Chart);
    POP_SPECIAL();
    return result;
}

/* ERASE-CHART */
Object erase_chart(chart,erase_renderings_qm)
    Object chart, erase_renderings_qm;
{
    Object copy_of_renderings, rendering, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,244);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      if (erase_renderings_qm)
	  update_images_of_block(Chart,T,T);
      copy_of_renderings = copy_list_using_eval_conses_1(ISVREF(Chart,
	      (SI_Long)16L));
      rendering = Nil;
      ab_loop_list_ = copy_of_renderings;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      rendering = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(printing_window_p(ISVREF(rendering,(SI_Long)17L))))
	  decache_graph_rendering(rendering);
      goto next_loop;
    end_loop:
      reclaim_eval_list_1(copy_of_renderings);
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* RECOMPUTE-AND-DRAW-CHART */
Object recompute_and_draw_chart(chart)
    Object chart;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(177,245);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      update_the_computed_annotations(Chart);
      result = update_images_of_block(Chart,Nil,T);
    POP_SPECIAL();
    return result;
}

static Object Qchart_data_series;  /* chart-data-series */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object list_constant_30;    /* # */

static Object Qhm14;               /* hm14 */

static Object Qab_font;            /* ab-font */

static Object Qchart_axis_computed_details;  /* chart-axis-computed-details */

/* UPDATE-THE-COMPUTED-ANNOTATIONS */
Object update_the_computed_annotations(chart)
    Object chart;
{
    Object current_chart_frame, temp, chart_really_drawing, chart_pen_x;
    Object chart_pen_y, chart_pen_color_1, chart_pen_color_value;
    Object chart_annotations, requested_horizontal_axis;
    Object requested_vertical_axis, gensymed_symbol, gensymed_symbol_1;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, computed_horizontal_axis, computed_vertical_axis;
    Object result_1, all_computed_data_series, gensymed_symbol_2;
    Object gensymed_symbol_3, new_computed_annotations, chart_tuple_1_minimum;
    Object chart_tuple_1_maximum, chart_tuple_2_minimum, chart_tuple_2_maximum;
    Object current_computation_frame, data_series_subparts;
    Object part_exceptions_from_parents, chart_top, chart_left, chart_right;
    Object chart_bottom, current_text_box_format, old_current_part_description;
    Object new_cons, svref_new_value, old_current_part_description_1;
    Object old_current_part_description_2, managed_number_or_value, temp_3;
    Object font_structure, tickmark_label_char_width;
    Object tickmark_label_min_height, tickmark_label_min_width;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons;
    SI_Long ab_loop_repeat_, gensymed_symbol_4, gensymed_symbol_5;
    double temp_4;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(22);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,246);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,21);
      LOCK(Working_on_chart);
      if (PUSH_UNWIND_PROTECT(2)) {
	  current_chart_frame = Chart;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_chart_frame,Qcurrent_chart_frame,current_chart_frame,
		  20);
	    change_slot_value(3,Chart,Qcomputed_annotations,Nil);
	    temp = ISVREF(Chart,(SI_Long)8L);
	    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(Chart,
		    (SI_Long)5L)) & (SI_Long)1L) ||  
		    !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		    (IFIX(ISVREF(Chart,(SI_Long)4L)) & (SI_Long)16777216L) 
		    &&  !((SI_Long)0L != (IFIX(ISVREF(Chart,(SI_Long)4L)) 
		    & (SI_Long)8192L)))) {
		LOCK(Chart_drawing);
		if (PUSH_UNWIND_PROTECT(1)) {
		    chart_really_drawing = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Chart_really_drawing,Qchart_really_drawing,chart_really_drawing,
			    19);
		      chart_pen_x = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_x,Qchart_pen_x,chart_pen_x,
			      18);
			chart_pen_y = FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_y,Qchart_pen_y,chart_pen_y,
				17);
			  chart_pen_color_1 = Qblack;
			  PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color,Qchart_pen_color,chart_pen_color_1,
				  16);
			    chart_pen_color_value = Chart_really_drawing ? 
				    map_to_color_value(Qblack) : 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Chart_pen_color_value,Qchart_pen_color_value,chart_pen_color_value,
				    15);
			      chart_annotations = ISVREF(Chart,(SI_Long)21L);
			      requested_horizontal_axis = 
				      get_subpart_of_collection(chart_annotations,
				      Qsubpart_exceptions,Qaxis,
				      FIX((SI_Long)1L));
			      requested_vertical_axis = 
				      get_subpart_of_collection(chart_annotations,
				      Qsubpart_exceptions,Qaxis,
				      FIX((SI_Long)2L));
			      gensymed_symbol = 
				      make_slot_value_list_1(FIX((SI_Long)11L));
			      gensymed_symbol_1 = gensymed_symbol;
			      M_CAR(gensymed_symbol_1) = Qaxis;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_heading;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qeast;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_minimum;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_maximum;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,10.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_crossover;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = 
				      Qnumber_of_significant_digits;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = FIX((SI_Long)-1L);
			      computed_horizontal_axis = gensymed_symbol;
			      gensymed_symbol = 
				      make_slot_value_list_1(FIX((SI_Long)11L));
			      gensymed_symbol_1 = gensymed_symbol;
			      M_CAR(gensymed_symbol_1) = Qaxis;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_heading;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qnorth;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_minimum;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_maximum;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,10.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qaxis_crossover;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			      M_CAR(gensymed_symbol_1) = new_float;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = 
				      Qnumber_of_significant_digits;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = FIX((SI_Long)-1L);
			      computed_vertical_axis = gensymed_symbol;
			      result_1 = Nil;
			      ab_loop_repeat_ = IFIX(length(ISVREF(Chart,
				      (SI_Long)20L)));
			    next_loop:
			      if ( !((SI_Long)0L < ab_loop_repeat_))
				  goto end_loop;
			      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			      result_1 = 
				      slot_value_cons_1(slot_value_cons_1(Qdata_series,
				      Nil),result_1);
			      goto next_loop;
			    end_loop:
			      all_computed_data_series = result_1;
			      goto end_1;
			      all_computed_data_series = Qnil;
			    end_1:;
			      gensymed_symbol = 
				      make_slot_value_list_1(FIX((SI_Long)9L));
			      gensymed_symbol_1 = gensymed_symbol;
			      M_CAR(gensymed_symbol_1) = Qchart;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qsubparts;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      temp_1 = slot_value_list_4(Qaxis,
				      slot_value_list_2(computed_horizontal_axis,
				      computed_vertical_axis),Qdata_series,
				      all_computed_data_series);
			      M_CAR(gensymed_symbol_1) = temp_1;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qsubpart_defaults;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      gensymed_symbol_2 = 
				      make_slot_value_list_1(FIX((SI_Long)7L));
			      gensymed_symbol_3 = gensymed_symbol_2;
			      M_CAR(gensymed_symbol_3) = Qaxis;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      M_CAR(gensymed_symbol_3) = Qaxis_minimum;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,-1.0);
			      M_CAR(gensymed_symbol_3) = new_float;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      M_CAR(gensymed_symbol_3) = Qaxis_crossover;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
			      M_CAR(gensymed_symbol_3) = new_float;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      M_CAR(gensymed_symbol_3) = Qaxis_maximum;
			      gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
			      amf_available_array_cons_qm = 
				      ISVREF(Vector_of_simple_float_array_pools,
				      (SI_Long)1L);
			      if (amf_available_array_cons_qm) {
				  amf_array = 
					  M_CAR(amf_available_array_cons_qm);
				  temp_1 = Vector_of_simple_float_array_pools;
				  temp_2 = M_CDR(amf_available_array_cons_qm);
				  SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
				  inline_note_reclaim_cons(amf_available_array_cons_qm,
					  Qfloat_array);
				  if (ISVREF(Available_float_array_conses_tail_vector,
					  IFIX(Current_thread_index))) {
				      temp_1 = 
					      ISVREF(Available_float_array_conses_tail_vector,
					      IFIX(Current_thread_index));
				      M_CDR(temp_1) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  else {
				      temp_1 = 
					      Available_float_array_conses_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				      temp_1 = 
					      Available_float_array_conses_tail_vector;
				      temp_2 = Current_thread_index;
				      SVREF(temp_1,temp_2) = 
					      amf_available_array_cons_qm;
				  }
				  M_CDR(amf_available_array_cons_qm) = Nil;
				  amf_result = amf_array;
			      }
			      else {
				  atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
					  FIX((SI_Long)1L));
				  atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
					  bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
				  amf_result = 
					  generate_float_vector(FIX((SI_Long)1L));
			      }
			      new_float = amf_result;
			      DFLOAT_ISASET_1(new_float,(SI_Long)0L,10.0);
			      M_CAR(gensymed_symbol_3) = new_float;
			      temp_1 = slot_value_list_2(Qaxis,
				      slot_value_cons_1(gensymed_symbol_2,
				      Nil));
			      M_CAR(gensymed_symbol_1) = temp_1;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qgrid_visible;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      temp_1 = 
				      get_simple_part_feature(chart_annotations,
				      Qgrid_visible);
			      M_CAR(gensymed_symbol_1) = temp_1;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      M_CAR(gensymed_symbol_1) = Qgrid_color;
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      temp_1 = 
				      get_simple_part_feature(chart_annotations,
				      Qgrid_color);
			      if (temp_1);
			      else
				  temp_1 = Qblack;
			      M_CAR(gensymed_symbol_1) = temp_1;
			      new_computed_annotations = gensymed_symbol;
			      chart_tuple_1_minimum = 
				      make_temporary_constant_no_expiration(float_constant,
				      Qnumber);
			      chart_tuple_1_maximum = 
				      make_temporary_constant_no_expiration(float_constant,
				      Qnumber);
			      chart_tuple_2_minimum = 
				      make_temporary_constant_no_expiration(float_constant,
				      Qnumber);
			      chart_tuple_2_maximum = 
				      make_temporary_constant_no_expiration(float_constant,
				      Qnumber);
			      PUSH_SPECIAL_WITH_SYMBOL(Chart_tuple_2_maximum,Qchart_tuple_2_maximum,chart_tuple_2_maximum,
				      14);
				PUSH_SPECIAL_WITH_SYMBOL(Chart_tuple_2_minimum,Qchart_tuple_2_minimum,chart_tuple_2_minimum,
					13);
				  PUSH_SPECIAL_WITH_SYMBOL(Chart_tuple_1_maximum,Qchart_tuple_1_maximum,chart_tuple_1_maximum,
					  12);
				    PUSH_SPECIAL_WITH_SYMBOL(Chart_tuple_1_minimum,Qchart_tuple_1_minimum,chart_tuple_1_minimum,
					    11);
				      LOCK(Working_on_lexical_computation_of_frame);
				      if (PUSH_UNWIND_PROTECT(0)) {
					  current_computation_frame = 
						  Current_chart_frame;
					  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
						  10);
					    data_series_subparts = 
						    ISVREF(Current_chart_frame,
						    (SI_Long)20L);
					    PUSH_SPECIAL_WITH_SYMBOL(Data_series_subparts,Qdata_series_subparts,data_series_subparts,
						    9);
					      part_exceptions_from_parents 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Part_exceptions_from_parents,Qpart_exceptions_from_parents,part_exceptions_from_parents,
						      8);
						chart_top = FIX((SI_Long)0L);
						chart_left = FIX((SI_Long)0L);
						gensymed_symbol = 
							ISVREF(Current_chart_frame,
							(SI_Long)14L);
						gensymed_symbol = 
							gensymed_symbol ? 
							ISVREF(gensymed_symbol,
							(SI_Long)2L) : 
							FIX((SI_Long)0L);
						gensymed_symbol_4 = 
							IFIX(gensymed_symbol);
						gensymed_symbol = 
							ISVREF(Current_chart_frame,
							(SI_Long)14L);
						gensymed_symbol = 
							gensymed_symbol ? 
							ISVREF(gensymed_symbol,
							(SI_Long)0L) : 
							FIX((SI_Long)0L);
						gensymed_symbol_5 = 
							IFIX(gensymed_symbol);
						chart_right = 
							FIX(gensymed_symbol_4 
							- gensymed_symbol_5);
						gensymed_symbol = 
							ISVREF(Current_chart_frame,
							(SI_Long)14L);
						gensymed_symbol = 
							gensymed_symbol ? 
							ISVREF(gensymed_symbol,
							(SI_Long)3L) : 
							FIX((SI_Long)0L);
						gensymed_symbol_4 = 
							IFIX(gensymed_symbol);
						gensymed_symbol = 
							ISVREF(Current_chart_frame,
							(SI_Long)14L);
						gensymed_symbol = 
							gensymed_symbol ? 
							ISVREF(gensymed_symbol,
							(SI_Long)1L) : 
							FIX((SI_Long)0L);
						gensymed_symbol_5 = 
							IFIX(gensymed_symbol);
						chart_bottom = 
							FIX(gensymed_symbol_4 
							- gensymed_symbol_5);
						temp = 
							get_instance_with_name_if_any(Qformat_frame,
							Qdynamic_text_cell_format);
						if (temp);
						else
						    temp = 
							    make_format_frame(Qdynamic_text_cell_format);
						current_text_box_format = temp;
						PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
							7);
						  PUSH_SPECIAL_WITH_SYMBOL(Chart_bottom,Qchart_bottom,chart_bottom,
							  6);
						    PUSH_SPECIAL_WITH_SYMBOL(Chart_right,Qchart_right,chart_right,
							    5);
						      PUSH_SPECIAL_WITH_SYMBOL(Chart_left,Qchart_left,chart_left,
							      4);
							PUSH_SPECIAL_WITH_SYMBOL(Chart_top,Qchart_top,chart_top,
								3);
							  old_current_part_description 
								  = 
								  Current_part_description;
							  gensymed_symbol 
								  = 
								  ISVREF(Current_chart_frame,
								  (SI_Long)19L);
							  Current_part_description 
								  = 
								  getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
								  Qchart_part_description_for_chart_style);
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      new_cons = 
								      ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index));
							      if (new_cons) {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  svref_new_value 
									  = 
									  M_CDR(new_cons);
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  svref_new_value;
								  if ( 
									  !TRUEP(ISVREF(Available_part_stack_conses_vector,
									  IFIX(Current_thread_index)))) 
									      {
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      Nil;
								  }
								  gensymed_symbol 
									  = 
									  new_cons;
							      }
							      else
								  gensymed_symbol 
									  = 
									  Nil;
							      if ( 
								      !TRUEP(gensymed_symbol))
								  gensymed_symbol 
									  = 
									  replenish_part_stack_cons_pool();
							      temp_1 = 
								      Current_part_description;
							      M_CAR(gensymed_symbol) 
								      = temp_1;
							      temp_1 = 
								      Stack_of_current_part_descriptions;
							      M_CDR(gensymed_symbol) 
								      = temp_1;
							      inline_note_allocate_cons(gensymed_symbol,
								      Qpart_stack);
							      Stack_of_current_part_descriptions 
								      = 
								      gensymed_symbol;
							  }
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp_1 = 
								      Available_part_stack_conses_vector;
							      temp_2 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp_1,
								      temp_2) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  M_CAR(gensymed_symbol) 
								  = Qmark;
							  temp_1 = 
								  Part_feature_recall_stack;
							  M_CDR(gensymed_symbol) 
								  = temp_1;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Part_feature_recall_stack 
								  = 
								  gensymed_symbol;
							  enter_part_description(Current_part_description);
							  old_current_part_description_1 
								  = 
								  Current_part_description;
							  temp = 
								  ISVREF(Current_chart_frame,
								  (SI_Long)21L);
							  if (temp);
							  else
							      temp = 
								      list_constant_1;
							  Current_part_description 
								  = temp;
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      new_cons = 
								      ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index));
							      if (new_cons) {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  svref_new_value 
									  = 
									  M_CDR(new_cons);
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  svref_new_value;
								  if ( 
									  !TRUEP(ISVREF(Available_part_stack_conses_vector,
									  IFIX(Current_thread_index)))) 
									      {
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      Nil;
								  }
								  gensymed_symbol 
									  = 
									  new_cons;
							      }
							      else
								  gensymed_symbol 
									  = 
									  Nil;
							      if ( 
								      !TRUEP(gensymed_symbol))
								  gensymed_symbol 
									  = 
									  replenish_part_stack_cons_pool();
							      temp_1 = 
								      Current_part_description;
							      M_CAR(gensymed_symbol) 
								      = temp_1;
							      temp_1 = 
								      Stack_of_current_part_descriptions;
							      M_CDR(gensymed_symbol) 
								      = temp_1;
							      inline_note_allocate_cons(gensymed_symbol,
								      Qpart_stack);
							      Stack_of_current_part_descriptions 
								      = 
								      gensymed_symbol;
							  }
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp_1 = 
								      Available_part_stack_conses_vector;
							      temp_2 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp_1,
								      temp_2) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  M_CAR(gensymed_symbol) 
								  = Qmark;
							  temp_1 = 
								  Part_feature_recall_stack;
							  M_CDR(gensymed_symbol) 
								  = temp_1;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Part_feature_recall_stack 
								  = 
								  gensymed_symbol;
							  enter_part_description(Current_part_description);
							  old_current_part_description_2 
								  = 
								  Current_part_description;
							  temp = 
								  get_lookup_slot_value_given_default(Current_chart_frame,
								  Qcomputed_annotations,
								  Nil);
							  if (temp);
							  else
							      temp = 
								      list_constant_1;
							  Current_part_description 
								  = temp;
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      new_cons = 
								      ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index));
							      if (new_cons) {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  svref_new_value 
									  = 
									  M_CDR(new_cons);
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  svref_new_value;
								  if ( 
									  !TRUEP(ISVREF(Available_part_stack_conses_vector,
									  IFIX(Current_thread_index)))) 
									      {
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      Nil;
								  }
								  gensymed_symbol 
									  = 
									  new_cons;
							      }
							      else
								  gensymed_symbol 
									  = 
									  Nil;
							      if ( 
								      !TRUEP(gensymed_symbol))
								  gensymed_symbol 
									  = 
									  replenish_part_stack_cons_pool();
							      temp_1 = 
								      Current_part_description;
							      M_CAR(gensymed_symbol) 
								      = temp_1;
							      temp_1 = 
								      Stack_of_current_part_descriptions;
							      M_CDR(gensymed_symbol) 
								      = temp_1;
							      inline_note_allocate_cons(gensymed_symbol,
								      Qpart_stack);
							      Stack_of_current_part_descriptions 
								      = 
								      gensymed_symbol;
							  }
							  new_cons = 
								  ISVREF(Available_part_stack_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      temp_1 = 
								      Available_part_stack_conses_vector;
							      temp_2 = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(temp_1,
								      temp_2) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_part_stack_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  Nil;
							      }
							      gensymed_symbol 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol))
							      gensymed_symbol 
								      = 
								      replenish_part_stack_cons_pool();
							  M_CAR(gensymed_symbol) 
								  = Qmark;
							  temp_1 = 
								  Part_feature_recall_stack;
							  M_CDR(gensymed_symbol) 
								  = temp_1;
							  inline_note_allocate_cons(gensymed_symbol,
								  Qpart_stack);
							  Part_feature_recall_stack 
								  = 
								  gensymed_symbol;
							  enter_part_description(Current_part_description);
							  setup_chart_data_caches(all_computed_data_series);
							  change_slot_value(3,
								  Chart,
								  Qcomputed_annotations,
								  new_computed_annotations);
							  temp = Chart;
							  update_subscriptions_from_virtual_attribute_change(temp,
								  get_property_value_function(3,
								  get_symbol_properties_function(Qchart_data_series),
								  Qvirtual_attribute,
								  Nil),Nil);
							  compute_chart_statistics();
							  if (PUSH_LOCAL_ALLOCATION(Local_area,
								  0,0)) {
							      managed_number_or_value 
								      = 
								      ISVREF(Chart_tuple_1_minimum,
								      (SI_Long)1L);
							      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp = 
									  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
									  (SI_Long)0L));
							      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp = 
									  aref1(managed_number_or_value,
									  FIX((SI_Long)0L));
							      else if (text_string_p(managed_number_or_value))
								  temp = 
									  copy_text_string(managed_number_or_value);
							      else
								  temp = 
									  managed_number_or_value;
							      managed_number_or_value 
								      = 
								      ISVREF(Chart_tuple_1_maximum,
								      (SI_Long)1L);
							      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp_3 = 
									  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
									  (SI_Long)0L));
							      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp_3 = 
									  aref1(managed_number_or_value,
									  FIX((SI_Long)0L));
							      else if (text_string_p(managed_number_or_value))
								  temp_3 = 
									  copy_text_string(managed_number_or_value);
							      else
								  temp_3 = 
									  managed_number_or_value;
							      compute_axis_bounds(computed_horizontal_axis,
								      requested_horizontal_axis 
								      ? 
								      requested_horizontal_axis 
								      : 
								      list_constant_30,
								      temp,
								      temp_3);
							      managed_number_or_value 
								      = 
								      ISVREF(Chart_tuple_2_minimum,
								      (SI_Long)1L);
							      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp = 
									  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
									  (SI_Long)0L));
							      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp = 
									  aref1(managed_number_or_value,
									  FIX((SI_Long)0L));
							      else if (text_string_p(managed_number_or_value))
								  temp = 
									  copy_text_string(managed_number_or_value);
							      else
								  temp = 
									  managed_number_or_value;
							      managed_number_or_value 
								      = 
								      ISVREF(Chart_tuple_2_maximum,
								      (SI_Long)1L);
							      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp_3 = 
									  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
									  (SI_Long)0L));
							      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
								      != 
								      (SI_Long)0L 
								      && 
								      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
								      == 
								      (SI_Long)1L)
								  temp_3 = 
									  aref1(managed_number_or_value,
									  FIX((SI_Long)0L));
							      else if (text_string_p(managed_number_or_value))
								  temp_3 = 
									  copy_text_string(managed_number_or_value);
							      else
								  temp_3 = 
									  managed_number_or_value;
							      compute_axis_bounds(computed_vertical_axis,
								      requested_vertical_axis 
								      ? 
								      requested_vertical_axis 
								      : 
								      list_constant_30,
								      temp,
								      temp_3);
							      pin_crossover_as_necessary(computed_horizontal_axis,
								      computed_vertical_axis);
							      pin_crossover_as_necessary(computed_vertical_axis,
								      computed_horizontal_axis);
							  }
							  POP_LOCAL_ALLOCATION(0,0);
							  if (PUSH_LOCAL_ALLOCATION(Local_area,
								  0,0)) {
							      temp = 
								      ISVREF(Current_text_box_format,
								      (SI_Long)22L);
							      gensymed_symbol 
								      = 
								      FIRST(temp);
							      if (gensymed_symbol);
							      else
								  gensymed_symbol 
									  = 
									  Qhm14;
							      font_structure 
								      = 
								      getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
								      Qab_font);
							      tickmark_label_char_width 
								      = 
								      DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(font_digit_text_width(font_structure)) 
								      / 256.0);
							      PUSH_SPECIAL_WITH_SYMBOL(Tickmark_label_char_width,Qtickmark_label_char_width,tickmark_label_char_width,
								      2);
								tickmark_label_min_height 
									= 
									DOUBLE_TO_DOUBLE_FLOAT(1000.0 
									* 
									(double)IFIX(ISVREF(font_structure,
									(SI_Long)5L)));
								PUSH_SPECIAL_WITH_SYMBOL(Tickmark_label_min_height,Qtickmark_label_min_height,tickmark_label_min_height,
									1);
								  temp_4 = 
									  DOUBLE_FLOAT_TO_DOUBLE(Tickmark_label_char_width);
								  tickmark_label_min_width 
									  = 
									  DOUBLE_TO_DOUBLE_FLOAT(6.0 
									  * 
									  temp_4);
								  PUSH_SPECIAL_WITH_SYMBOL(Tickmark_label_min_width,Qtickmark_label_min_width,tickmark_label_min_width,
									  0);
								    compute_axis_tickmarks_and_style(2,
									    requested_horizontal_axis,
									    computed_horizontal_axis);
								    compute_axis_tickmarks_and_style(2,
									    requested_vertical_axis,
									    computed_vertical_axis);
								    compute_axis_tickmark_label_field_widths(Chart,
									    requested_vertical_axis,
									    computed_vertical_axis,
									    requested_horizontal_axis,
									    computed_horizontal_axis);
								    temp = 
									    Chart;
								    update_subscriptions_from_virtual_attribute_change(temp,
									    get_property_value_function(3,
									    get_symbol_properties_function(Qchart_axis_computed_details),
									    Qvirtual_attribute,
									    Nil),
									    Nil);
								  POP_SPECIAL();
								POP_SPECIAL();
							      POP_SPECIAL();
							  }
							  POP_LOCAL_ALLOCATION(0,0);
							  part_feature_index 
								  = Nil;
							  exit_feature_handler 
								  = Nil;
							next_loop_1:
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Part_feature_recall_stack;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp_1 = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp_1) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      else {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Part_feature_recall_stack 
								  = next_cons;
							  part_feature_index 
								  = 
								  part_stack_pop_store;
							  if (EQ(part_feature_index,
								  Qmark))
							      goto end_loop_1;
							  exit_feature_handler 
								  = 
								  ISVREF(Part_feature_exit_methods,
								  IFIX(part_feature_index));
							  inline_funcall_0(exit_feature_handler);
							  goto next_loop_1;
							end_loop_1:;
							  Current_part_description 
								  = 
								  old_current_part_description_2;
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      part_stack_pop_store 
								      = Nil;
							      cons_1 = 
								      Stack_of_current_part_descriptions;
							      if (cons_1) {
								  part_stack_pop_store 
									  = 
									  M_CAR(cons_1);
								  next_cons 
									  = 
									  M_CDR(cons_1);
								  inline_note_reclaim_cons(cons_1,
									  Qpart_stack);
								  if (ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index))) 
									      {
								      temp_1 
									      = 
									      ISVREF(Available_part_stack_conses_tail_vector,
									      IFIX(Current_thread_index));
								      M_CDR(temp_1) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  else {
								      temp_1 
									      = 
									      Available_part_stack_conses_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  M_CDR(cons_1) 
									  = 
									  Nil;
							      }
							      else
								  next_cons 
									  = 
									  Nil;
							      Stack_of_current_part_descriptions 
								      = 
								      next_cons;
							  }
							  part_feature_index 
								  = Nil;
							  exit_feature_handler 
								  = Nil;
							next_loop_2:
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Part_feature_recall_stack;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp_1 = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp_1) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      else {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Part_feature_recall_stack 
								  = next_cons;
							  part_feature_index 
								  = 
								  part_stack_pop_store;
							  if (EQ(part_feature_index,
								  Qmark))
							      goto end_loop_2;
							  exit_feature_handler 
								  = 
								  ISVREF(Part_feature_exit_methods,
								  IFIX(part_feature_index));
							  inline_funcall_0(exit_feature_handler);
							  goto next_loop_2;
							end_loop_2:;
							  Current_part_description 
								  = 
								  old_current_part_description_1;
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      part_stack_pop_store 
								      = Nil;
							      cons_1 = 
								      Stack_of_current_part_descriptions;
							      if (cons_1) {
								  part_stack_pop_store 
									  = 
									  M_CAR(cons_1);
								  next_cons 
									  = 
									  M_CDR(cons_1);
								  inline_note_reclaim_cons(cons_1,
									  Qpart_stack);
								  if (ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index))) 
									      {
								      temp_1 
									      = 
									      ISVREF(Available_part_stack_conses_tail_vector,
									      IFIX(Current_thread_index));
								      M_CDR(temp_1) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  else {
								      temp_1 
									      = 
									      Available_part_stack_conses_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  M_CDR(cons_1) 
									  = 
									  Nil;
							      }
							      else
								  next_cons 
									  = 
									  Nil;
							      Stack_of_current_part_descriptions 
								      = 
								      next_cons;
							  }
							  part_feature_index 
								  = Nil;
							  exit_feature_handler 
								  = Nil;
							next_loop_3:
							  part_stack_pop_store 
								  = Nil;
							  cons_1 = 
								  Part_feature_recall_stack;
							  if (cons_1) {
							      part_stack_pop_store 
								      = 
								      M_CAR(cons_1);
							      next_cons = 
								      M_CDR(cons_1);
							      inline_note_reclaim_cons(cons_1,
								      Qpart_stack);
							      if (ISVREF(Available_part_stack_conses_tail_vector,
								      IFIX(Current_thread_index))) 
									  {
								  temp_1 = 
									  ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index));
								  M_CDR(temp_1) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      else {
								  temp_1 = 
									  Available_part_stack_conses_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
								  temp_1 = 
									  Available_part_stack_conses_tail_vector;
								  temp_2 = 
									  Current_thread_index;
								  SVREF(temp_1,
									  temp_2) 
									  = 
									  cons_1;
							      }
							      M_CDR(cons_1) 
								      = Nil;
							  }
							  else
							      next_cons = Nil;
							  Part_feature_recall_stack 
								  = next_cons;
							  part_feature_index 
								  = 
								  part_stack_pop_store;
							  if (EQ(part_feature_index,
								  Qmark))
							      goto end_loop_3;
							  exit_feature_handler 
								  = 
								  ISVREF(Part_feature_exit_methods,
								  IFIX(part_feature_index));
							  inline_funcall_0(exit_feature_handler);
							  goto next_loop_3;
							end_loop_3:;
							  Current_part_description 
								  = 
								  old_current_part_description;
							  if (Maintain_stack_of_current_part_descriptions_p) 
								      {
							      part_stack_pop_store 
								      = Nil;
							      cons_1 = 
								      Stack_of_current_part_descriptions;
							      if (cons_1) {
								  part_stack_pop_store 
									  = 
									  M_CAR(cons_1);
								  next_cons 
									  = 
									  M_CDR(cons_1);
								  inline_note_reclaim_cons(cons_1,
									  Qpart_stack);
								  if (ISVREF(Available_part_stack_conses_tail_vector,
									  IFIX(Current_thread_index))) 
									      {
								      temp_1 
									      = 
									      ISVREF(Available_part_stack_conses_tail_vector,
									      IFIX(Current_thread_index));
								      M_CDR(temp_1) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  else {
								      temp_1 
									      = 
									      Available_part_stack_conses_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								      temp_1 
									      = 
									      Available_part_stack_conses_tail_vector;
								      temp_2 
									      = 
									      Current_thread_index;
								      SVREF(temp_1,
									      temp_2) 
									      = 
									      cons_1;
								  }
								  M_CDR(cons_1) 
									  = 
									  Nil;
							      }
							      else
								  next_cons 
									  = 
									  Nil;
							      Stack_of_current_part_descriptions 
								      = 
								      next_cons;
							  }
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
				      UNLOCK(Working_on_lexical_computation_of_frame);
				      CONTINUE_UNWINDING(0);
				      reclaim_temporary_constant_1(Chart_tuple_1_minimum);
				      reclaim_temporary_constant_1(Chart_tuple_1_maximum);
				      reclaim_temporary_constant_1(Chart_tuple_2_minimum);
				      reclaim_temporary_constant_1(Chart_tuple_2_maximum);
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
		POP_UNWIND_PROTECT(1);
		UNLOCK(Chart_drawing);
		CONTINUE_UNWINDING(1);
	    }
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(2);
      UNLOCK(Working_on_chart);
      CONTINUE_UNWINDING(2);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* COMPUTE-AXIS-TICKMARK-LABEL-FIELD-WIDTHS */
Object compute_axis_tickmark_label_field_widths(chart,
	    requested_vertical_axis,computed_vertical_axis,
	    requested_horizontal_axis,computed_horizontal_axis)
    Object chart, requested_vertical_axis, computed_vertical_axis;
    Object requested_horizontal_axis, computed_horizontal_axis;
{
    Object whole, fraction, expt_1, unaligned_size, label_size, size_in_chars;
    Object left_margin, right_margin, top_margin, bottom_margin, axis;
    Object other_axis, device_range, char_width_sl_2, char_width;
    Object left_margin_from_north_axis, font_structure, east_char_width;
    Object east_tickmark_label_char_width, north_tickmark_label_min_height;
    Object old_current_part_description, new_cons, temp, svref_arg_2;
    Object svref_new_value, gensymed_symbol, current_axis, ab_loop_list_;
    Object axis_index, ab_loop_iter_flag_, old_current_part_description_1;
    Object axis_is_discrete_p, temp_1, label_significant_digits, decff_1_arg;
    Object part, slot_value_number, crossover, min_1, max_1, delta;
    Object part_feature_index, exit_feature_handler, part_stack_pop_store;
    Object cons_1, next_cons, label_count, chart_left_margin;
    Object chart_right_margin, chart_top_margin, chart_bottom_margin;
    SI_Long half_label_width, temp_8;
    char temp_2;
    double arg, arg_1, temp_3, temp_4, temp_5, temp_6, temp_7;
    Declare_special(6);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(177,247);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,5);
      if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	  whole = Nil;
	  fraction = Nil;
	  expt_1 = Nil;
	  unaligned_size = Nil;
	  label_size = Nil;
	  size_in_chars = Nil;
	  left_margin = FIX((SI_Long)0L);
	  right_margin = Nil;
	  top_margin = Nil;
	  bottom_margin = FIX((SI_Long)0L);
	  axis = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Axis,Qaxis,axis,4);
	    other_axis = Nil;
	    device_range = Nil;
	    char_width_sl_2 = Nil;
	    char_width = Nil;
	    left_margin_from_north_axis = Nil;
	    font_structure = Nil;
	    east_char_width = Nil;
	    east_tickmark_label_char_width = Nil;
	    north_tickmark_label_min_height = Nil;
	    old_current_part_description = Current_part_description;
	    Current_part_description = Default_axis_data_series_instance;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		new_cons = ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_part_stack_cons_pool();
		temp = Current_part_description;
		M_CAR(gensymed_symbol) = temp;
		temp = Stack_of_current_part_descriptions;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		Stack_of_current_part_descriptions = gensymed_symbol;
	    }
	    new_cons = ISVREF(Available_part_stack_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_part_stack_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_part_stack_cons_pool();
	    M_CAR(gensymed_symbol) = Qmark;
	    temp = Part_feature_recall_stack;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	    Part_feature_recall_stack = gensymed_symbol;
	    enter_part_description(Current_part_description);
	    current_axis = Nil;
	    ab_loop_list_ = 
		    get_subpart_collection(get_lookup_slot_value_given_default(Current_chart_frame,
		    Qcomputed_annotations,Nil),Qsubparts,Qaxis);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_axis,Qcurrent_axis,current_axis,
		    2);
	      axis_index = FIX((SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Axis_index,Qaxis_index,axis_index,1);
		ab_loop_iter_flag_ = T;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		Current_axis = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    Axis_index = FIXNUM_ADD1(Axis_index);
		old_current_part_description_1 = Current_part_description;
		Current_part_description = Current_axis;
		if (Maintain_stack_of_current_part_descriptions_p) {
		    new_cons = ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp,svref_arg_2) = svref_new_value;
			if ( 
				!TRUEP(ISVREF(Available_part_stack_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = Nil;
			}
			gensymed_symbol = new_cons;
		    }
		    else
			gensymed_symbol = Nil;
		    if ( !TRUEP(gensymed_symbol))
			gensymed_symbol = replenish_part_stack_cons_pool();
		    temp = Current_part_description;
		    M_CAR(gensymed_symbol) = temp;
		    temp = Stack_of_current_part_descriptions;
		    M_CDR(gensymed_symbol) = temp;
		    inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		    Stack_of_current_part_descriptions = gensymed_symbol;
		}
		new_cons = ISVREF(Available_part_stack_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = Nil;
		    }
		    gensymed_symbol = new_cons;
		}
		else
		    gensymed_symbol = Nil;
		if ( !TRUEP(gensymed_symbol))
		    gensymed_symbol = replenish_part_stack_cons_pool();
		M_CAR(gensymed_symbol) = Qmark;
		temp = Part_feature_recall_stack;
		M_CDR(gensymed_symbol) = temp;
		inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		Part_feature_recall_stack = gensymed_symbol;
		enter_part_description(Current_part_description);
		axis_is_discrete_p = EQ(Axis_heading,Qeast) ? 
			plot_east_axis_label_tickmarks_as_integers_p(Current_chart_frame) 
			: 
			plot_north_axis_label_tickmarks_as_integers_p(Current_chart_frame);
		PUSH_SPECIAL_WITH_SYMBOL(Axis_is_discrete_p,Qaxis_is_discrete_p,axis_is_discrete_p,
			0);
		  temp_1 = ISVREF(Current_text_box_format,(SI_Long)22L);
		  gensymed_symbol = FIRST(temp_1);
		  if (gensymed_symbol);
		  else
		      gensymed_symbol = Qhm14;
		  font_structure = 
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			  Qab_font);
		  Tickmark_label_char_width = 
			  DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(font_digit_text_width(font_structure)) 
			  / 256.0);
		  Tickmark_label_min_height = DOUBLE_TO_DOUBLE_FLOAT(1.3 * 
			  (double)IFIX(ISVREF(font_structure,(SI_Long)5L)));
		  char_width = ceiling(Tickmark_label_char_width,_);
		  char_width_sl_2 = FIX(IFIX(char_width) >>  -  - (SI_Long)1L);
		  label_significant_digits = EQ(Axis_heading,Qeast) ? 
			  get_simple_part_feature(computed_horizontal_axis,
			  Qnumber_of_significant_digits) : 
			  get_simple_part_feature(computed_vertical_axis,
			  Qnumber_of_significant_digits);
		  if (IFIX(label_significant_digits) == (SI_Long)-1L)
		      result = compute_current_axis_tickmark_label_field_widths(Nil);
		  else
		      result = compute_current_axis_tickmark_label_field_widths(label_significant_digits);
		  MVS_4(result,size_in_chars,whole,fraction,expt_1);
		  if (EQ(Axis_heading,Qnorth)) {
		      Axis = computed_vertical_axis;
		      other_axis = computed_horizontal_axis;
		      device_range = 
			      FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_right,
			      Chart_left),Chart_left_margin),
			      Chart_right_margin);
		      label_size = FIXNUM_ADD(FIXNUM_TIMES(char_width,
			      FIXNUM_ADD1(size_in_chars)),char_width_sl_2);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_minimum) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_minimum,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(Axis_minimum) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(Axis_minimum,FIX((SI_Long)0L));
		      else
			  temp_1 = Axis_minimum;
		      temp_1 = lfloat(temp_1,float_constant_1);
		      arg = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		      arg_1 = 0.0;
		      temp_2 = arg < arg_1 &&  
			      !inline_nanp_for_comparison(arg) ?  
			      !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		      if (temp_2);
		      else {
			  if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_maximum) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				  == (SI_Long)1L)
			      temp_1 = 
				      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_maximum,
				      (SI_Long)0L));
			  else if (INLINE_LONG_VECTOR_P(Axis_maximum) != 
				  (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_maximum)) 
				  == (SI_Long)1L)
			      temp_1 = aref1(Axis_maximum,FIX((SI_Long)0L));
			  else
			      temp_1 = Axis_maximum;
			  temp_1 = lfloat(temp_1,float_constant_1);
			  arg = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			  arg_1 = 0.0;
			  temp_2 = arg < arg_1 &&  
				  !inline_nanp_for_comparison(arg) ?  
				  !inline_nanp_for_comparison(arg_1) : 
				  TRUEP(Qnil);
		      }
		      if (temp_2) {
			  decff_1_arg = char_width_sl_2;
			  label_size = FIXNUM_MINUS(label_size,decff_1_arg);
		      }
		      if (IFIX(fraction) > (SI_Long)0L) {
			  decff_1_arg = char_width_sl_2;
			  label_size = FIXNUM_MINUS(label_size,decff_1_arg);
		      }
		      temp_1 = ceiling(Tickmark_label_min_height,_);
		      bottom_margin = FIXNUM_MAX(bottom_margin,temp_1);
		      north_tickmark_label_min_height = 
			      Tickmark_label_min_height;
		      left_margin_from_north_axis = char_width;
		  }
		  else if (EQ(Axis_heading,Qeast)) {
		      Axis = computed_horizontal_axis;
		      other_axis = computed_vertical_axis;
		      device_range = 
			      FIXNUM_MINUS(FIXNUM_MINUS(FIXNUM_MINUS(Chart_bottom,
			      Chart_top),Chart_top_margin),
			      Chart_bottom_margin);
		      label_size = FIX((SI_Long)6L + 
			      IFIX(ltruncate(FIX((SI_Long)3L * 
			      IFIX(ceiling(Tickmark_label_min_height,_))),
			      FIX((SI_Long)2L))));
		      unaligned_size = size_in_chars;
		      temp_3 = 
			      DOUBLE_FLOAT_TO_DOUBLE(Tickmark_label_char_width);
		      Tickmark_label_min_width = 
			      DOUBLE_TO_DOUBLE_FLOAT(6.0 * temp_3);
		      east_char_width = char_width;
		      east_tickmark_label_char_width = 
			      Tickmark_label_char_width;
		  }
		  part = Axis;
		  set_simple_part_feature(part,
			  Qaxis_tickmark_label_max_digits_before_point,whole);
		  set_simple_part_feature(part,
			  Qaxis_tickmark_label_max_digits_after_point,
			  fraction);
		  set_simple_part_feature(part,
			  Qaxis_tickmark_label_max_digits_in_exponent,expt_1);
		  slot_value_number = get_simple_part_feature(Axis,
			  Qaxis_crossover);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
		  else
		      temp_1 = slot_value_number;
		  crossover = lfloat(temp_1,float_constant_1);
		  slot_value_number = get_simple_part_feature(other_axis,
			  Qaxis_minimum);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
		  else
		      temp_1 = slot_value_number;
		  min_1 = lfloat(temp_1,float_constant_1);
		  slot_value_number = get_simple_part_feature(other_axis,
			  Qaxis_maximum);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
		  else
		      temp_1 = slot_value_number;
		  max_1 = lfloat(temp_1,float_constant_1);
		  temp_4 = DOUBLE_FLOAT_TO_DOUBLE(crossover);
		  temp_5 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
		  temp_6 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
		  temp_7 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
		  temp_1 = lfloat(device_range,float_constant_1);
		  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		  temp_3 = (temp_4 - temp_5) / (temp_6 - temp_7) * temp_3;
		  delta = FIXNUM_MINUS(label_size,
			  ltruncate(DOUBLE_TO_DOUBLE_FLOAT(ABS(temp_3)),_));
		  if (IFIX(delta) > (SI_Long)0L) {
		      if (EQ(Axis_heading,Qeast))
			  bottom_margin = FIXNUM_MAX(bottom_margin,delta);
		      else if (EQ(Axis_heading,Qnorth)) {
			  left_margin = FIXNUM_MAX(left_margin,delta);
			  left_margin_from_north_axis = left_margin;
		      }
		  }
		POP_SPECIAL();
		part_feature_index = Nil;
		exit_feature_handler = Nil;
	      next_loop_1:
		part_stack_pop_store = Nil;
		cons_1 = Part_feature_recall_stack;
		if (cons_1) {
		    part_stack_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpart_stack);
		    if (ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		Part_feature_recall_stack = next_cons;
		part_feature_index = part_stack_pop_store;
		if (EQ(part_feature_index,Qmark))
		    goto end_loop_1;
		exit_feature_handler = ISVREF(Part_feature_exit_methods,
			IFIX(part_feature_index));
		inline_funcall_0(exit_feature_handler);
		goto next_loop_1;
	      end_loop_1:;
		Current_part_description = old_current_part_description_1;
		if (Maintain_stack_of_current_part_descriptions_p) {
		    part_stack_pop_store = Nil;
		    cons_1 = Stack_of_current_part_descriptions;
		    if (cons_1) {
			part_stack_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qpart_stack);
			if (ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_part_stack_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_part_stack_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_part_stack_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    Stack_of_current_part_descriptions = next_cons;
		}
		ab_loop_iter_flag_ = Nil;
		goto next_loop;
	      end_loop:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	    part_feature_index = Nil;
	    exit_feature_handler = Nil;
	  next_loop_2:
	    part_stack_pop_store = Nil;
	    cons_1 = Part_feature_recall_stack;
	    if (cons_1) {
		part_stack_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qpart_stack);
		if (ISVREF(Available_part_stack_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_part_stack_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_part_stack_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    Part_feature_recall_stack = next_cons;
	    part_feature_index = part_stack_pop_store;
	    if (EQ(part_feature_index,Qmark))
		goto end_loop_2;
	    exit_feature_handler = ISVREF(Part_feature_exit_methods,
		    IFIX(part_feature_index));
	    inline_funcall_0(exit_feature_handler);
	    goto next_loop_2;
	  end_loop_2:;
	    Current_part_description = old_current_part_description;
	    if (Maintain_stack_of_current_part_descriptions_p) {
		part_stack_pop_store = Nil;
		cons_1 = Stack_of_current_part_descriptions;
		if (cons_1) {
		    part_stack_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qpart_stack);
		    if (ISVREF(Available_part_stack_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_part_stack_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_part_stack_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_part_stack_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		Stack_of_current_part_descriptions = next_cons;
	    }
	    half_label_width = IFIX(east_char_width) * 
		    ((IFIX(unaligned_size) >>  -  - (SI_Long)1L) + 
		    (SI_Long)1L);
	    label_count = get_simple_part_feature(computed_horizontal_axis,
		    Qaxis_tickmark_count_as_fixnum);
	    right_margin = FIX(half_label_width);
	    left_margin = IFIX(label_count) > (SI_Long)0L ? 
		    FIX(MAX(IFIX(left_margin),half_label_width)) : 
		    left_margin_from_north_axis;
	    if (IFIX(label_count) <= (SI_Long)1L && FIXNUM_GT(right_margin,
		    east_char_width))
		right_margin = east_char_width;
	    if (FIXNUM_GE(FIXNUM_ADD(left_margin,right_margin),
		    FIXNUM_MINUS(Chart_right,Chart_left))) {
		left_margin = FIX(IFIX(FIXNUM_MINUS(Chart_right,
			Chart_left)) - (IFIX(right_margin) >>  -  - 
			(SI_Long)1L) - IFIX(east_char_width));
		if (FIXNUM_GT(left_margin,char_width))
		    right_margin = east_char_width;
		else {
		    temp_8 = IFIX(FIXNUM_MINUS(FIXNUM_MINUS(Chart_right,
			    Chart_left),east_char_width));
		    left_margin = FIX(MAX((SI_Long)0L,temp_8));
		    left_margin = FIX(IFIX(left_margin) >>  -  - (SI_Long)1L);
		    right_margin = left_margin;
		}
	    }
	    Tickmark_label_min_height = north_tickmark_label_min_height;
	    Tickmark_label_char_width = east_tickmark_label_char_width;
	    top_margin = ceiling(Tickmark_label_min_height,_);
	    part = get_lookup_slot_value_given_default(Chart,
		    Qcomputed_annotations,Nil);
	    set_simple_part_feature(part,Qchart_left_margin,left_margin);
	    set_simple_part_feature(part,Qchart_right_margin,right_margin);
	    set_simple_part_feature(part,Qchart_top_margin,top_margin);
	    set_simple_part_feature(part,Qchart_bottom_margin,bottom_margin);
	    chart_left_margin = left_margin;
	    chart_right_margin = right_margin;
	    chart_top_margin = top_margin;
	    chart_bottom_margin = bottom_margin;
	    PUSH_SPECIAL_WITH_SYMBOL(Chart_bottom_margin,Qchart_bottom_margin,chart_bottom_margin,
		    3);
	      PUSH_SPECIAL_WITH_SYMBOL(Chart_top_margin,Qchart_top_margin,chart_top_margin,
		      2);
		PUSH_SPECIAL_WITH_SYMBOL(Chart_right_margin,Qchart_right_margin,chart_right_margin,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Chart_left_margin,Qchart_left_margin,chart_left_margin,
			  0);
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			temp_3 = 
				DOUBLE_FLOAT_TO_DOUBLE(east_tickmark_label_char_width);
			compute_axis_tickmarks_and_style(3,
				requested_horizontal_axis,
				computed_horizontal_axis,
				DOUBLE_TO_DOUBLE_FLOAT(temp_3 * 
				(double)IFIX(FIXNUM_ADD1(unaligned_size))));
			result = compute_axis_tickmarks_and_style(2,
				requested_vertical_axis,
				computed_vertical_axis);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      POP_LOCAL_ALLOCATION(1,1);
    POP_SPECIAL();
    return result;
}

/* COMPUTE-CURRENT-AXIS-TICKMARK-LABEL-FIELD-WIDTHS */
Object compute_current_axis_tickmark_label_field_widths(significant_digits_qm)
    Object significant_digits_qm;
{
    Object whole_plus_e, fraction_plus_e, expt_plus_e, whole_e, fraction_e;
    Object this_whole_plus_e, this_fraction_plus_e, this_expt_plus_e;
    Object this_whole_e, this_fraction_e, last_whole_e, last_fraction_e;
    Object aligned_size_plus_e, aligned_size_e, unaligned_size_e;
    Object this_expt_value, last_expt_value, last_tick_value, discrete_qm;
    Object this_tick_value, ab_loop_iter_flag_, temp, temp_1;
    Object whole_width_adjustment_qm, fraction_width_adjustment_qm;
    Object adjusted_fraction_plus_e_qm;
    SI_Long ab_loop_repeat_, gensymed_symbol, gensymed_symbol_1;
    char no_fraction_p;
    double arg, arg_1;
    Object result;

    x_note_fn_call(177,248);
    whole_plus_e = Nil;
    fraction_plus_e = Nil;
    expt_plus_e = Nil;
    whole_e = Nil;
    fraction_e = Nil;
    this_whole_plus_e = Nil;
    this_fraction_plus_e = Nil;
    this_expt_plus_e = Nil;
    this_whole_e = Nil;
    this_fraction_e = Nil;
    last_whole_e = Nil;
    last_fraction_e = Nil;
    aligned_size_plus_e = Nil;
    aligned_size_e = Nil;
    unaligned_size_e = Nil;
    this_expt_value = Nil;
    last_expt_value = Nil;
    last_tick_value = Nil;
    discrete_qm = Axis_is_discrete_p;
    whole_plus_e = FIX((SI_Long)1L);
    fraction_plus_e = FIX((SI_Long)0L);
    expt_plus_e = FIX((SI_Long)1L);
    whole_e = FIX((SI_Long)0L);
    fraction_e = FIX((SI_Long)0L);
    unaligned_size_e = FIX((SI_Long)1L);
    last_tick_value = Nil;
    ab_loop_repeat_ = (SI_Long)2L;
    this_tick_value = Axis_minimum;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ab_loop_iter_flag_))
	this_tick_value = Axis_maximum;
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(this_tick_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(this_tick_value)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(this_tick_value,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(this_tick_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(this_tick_value)) == (SI_Long)1L)
	temp = aref1(this_tick_value,FIX((SI_Long)0L));
    else
	temp = this_tick_value;
    this_tick_value = lfloat(temp,float_constant_1);
    result = float_expt_and_size(this_tick_value);
    MVS_2(result,this_expt_value,this_expt_plus_e);
    expt_plus_e = FIXNUM_MAX(expt_plus_e,this_expt_plus_e);
    this_whole_plus_e = FIX((SI_Long)1L);
    arg = DOUBLE_FLOAT_TO_DOUBLE(this_tick_value);
    arg_1 = 0.0;
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	this_whole_plus_e = FIXNUM_ADD1(this_whole_plus_e);
	whole_plus_e = FIXNUM_MAX(whole_plus_e,this_whole_plus_e);
    }
    this_fraction_plus_e = FIX((SI_Long)0L);
    if ( !TRUEP(last_tick_value)) {
	result = float_string_field_widths_without_expt(FIX((SI_Long)0L),
		this_expt_value);
	MVS_2(result,whole_e,fraction_e);
	arg = DOUBLE_FLOAT_TO_DOUBLE(this_tick_value);
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    whole_e = FIXNUM_ADD1(whole_e);
	unaligned_size_e = FIXNUM_ADD(whole_e,IFIX(fraction_e) <= 
		(SI_Long)0L ? fraction_e : FIXNUM_ADD1(fraction_e));
    }
    else {
	temp_1 = this_tick_value;
	temp = last_tick_value;
	this_fraction_plus_e = float_discrimination_precision(temp_1,temp,
		lfloor(safe_chart_log(DOUBLE_TO_DOUBLE_FLOAT((double)
		(IFIX(Axis_tickmark_count_as_fixnum) << (SI_Long)1L))),_));
	fraction_plus_e = FIXNUM_MAX(fraction_plus_e,this_fraction_plus_e);
	result = float_string_field_widths_without_expt(fraction_plus_e,
		this_expt_value);
	MVS_2(result,this_whole_e,this_fraction_e);
	result = float_string_field_widths_without_expt(fraction_plus_e,
		last_expt_value);
	MVS_2(result,last_whole_e,last_fraction_e);
	arg = DOUBLE_FLOAT_TO_DOUBLE(this_tick_value);
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    this_whole_e = FIXNUM_ADD1(this_whole_e);
	arg = DOUBLE_FLOAT_TO_DOUBLE(last_tick_value);
	arg_1 = 0.0;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    last_whole_e = FIXNUM_ADD1(last_whole_e);
	temp = FIXNUM_MAX(whole_e,this_whole_e);
	whole_e = FIXNUM_MAX(temp,last_whole_e);
	if (discrete_qm) {
	    this_fraction_e = FIX((SI_Long)0L);
	    last_fraction_e = FIX((SI_Long)0L);
	    fraction_e = FIX((SI_Long)0L);
	}
	else {
	    temp = FIXNUM_MAX(fraction_e,this_fraction_e);
	    fraction_e = FIXNUM_MAX(temp,last_fraction_e);
	}
	if (EQ(Axis_heading,Qeast)) {
	    temp_1 = unaligned_size_e;
	    temp = FIXNUM_ADD(this_whole_e,IFIX(this_fraction_e) <= 
		    (SI_Long)0L ? this_fraction_e : 
		    FIXNUM_ADD1(this_fraction_e));
	    temp_1 = FIXNUM_MAX(temp_1,temp);
	    temp = FIXNUM_ADD(last_whole_e,IFIX(last_fraction_e) <= 
		    (SI_Long)0L ? last_fraction_e : 
		    FIXNUM_ADD1(last_fraction_e));
	    unaligned_size_e = FIXNUM_MAX(temp_1,temp);
	}
    }
    last_tick_value = this_tick_value;
    last_expt_value = this_expt_value;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    aligned_size_plus_e = FIXNUM_ADD(FIXNUM_ADD(whole_plus_e,
	    IFIX(fraction_plus_e) <= (SI_Long)0L ? fraction_plus_e : 
	    FIXNUM_ADD1(fraction_plus_e)),IFIX(expt_plus_e) <= (SI_Long)0L 
	    ? expt_plus_e : FIXNUM_ADD1(expt_plus_e));
    no_fraction_p = IFIX(fraction_e) == (SI_Long)0L;
    if (significant_digits_qm) {
	if (no_fraction_p)
	    whole_width_adjustment_qm = adjust_for_the_sign_p(Axis_minimum,
		    Axis_maximum) ? FIX((SI_Long)2L) : FIX((SI_Long)0L);
	else {
	    gensymed_symbol = 
		    IFIX(FIXNUM_MINUS(FIXNUM_MINUS(significant_digits_qm,
		    whole_e),fraction_e));
	    gensymed_symbol_1 = adjust_for_the_sign_p(Axis_minimum,
		    Axis_maximum) ? (SI_Long)2L : (SI_Long)0L;
	    whole_width_adjustment_qm = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	}
    }
    else
	whole_width_adjustment_qm = Nil;
    fraction_width_adjustment_qm = significant_digits_qm ? (no_fraction_p ?
	     FIX((SI_Long)0L) : adjust_for_the_sign_p(Axis_minimum,
	    Axis_maximum) ? 
	    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_MINUS(significant_digits_qm,
	    whole_e),fraction_e)) : 
	    FIXNUM_MINUS(FIXNUM_MINUS(significant_digits_qm,whole_e),
	    fraction_e)) : Qnil;
    if (significant_digits_qm) {
	if (IFIX(fraction_plus_e) == (SI_Long)0L)
	    adjusted_fraction_plus_e_qm = FIX((SI_Long)0L);
	else {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Axis_minimum) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) == 
		    (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Axis_minimum,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(Axis_minimum) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Axis_minimum)) == 
		    (SI_Long)1L)
		temp = aref1(Axis_minimum,FIX((SI_Long)0L));
	    else
		temp = Axis_minimum;
	    temp = lfloat(temp,float_constant_1);
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    arg_1 = 0.0;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		adjusted_fraction_plus_e_qm = 
			FIXNUM_SUB1(significant_digits_qm);
	    else
		adjusted_fraction_plus_e_qm = 
			FIXNUM_SUB1(significant_digits_qm);
	}
    }
    else
	adjusted_fraction_plus_e_qm = Nil;
    if (EQ(Axis_heading,Qnorth)) {
	aligned_size_e = FIXNUM_ADD(whole_e,IFIX(fraction_e) <= 
		(SI_Long)0L ? fraction_e : FIXNUM_ADD1(fraction_e));
	if (significant_digits_qm) {
	    if (FIXNUM_GE(significant_digits_qm,FIXNUM_ADD(whole_e,
		    fraction_e))) {
		aligned_size_plus_e = FIXNUM_ADD(aligned_size_e,
			whole_width_adjustment_qm);
		whole_plus_e = whole_e;
		fraction_plus_e = FIXNUM_ADD(fraction_e,
			fraction_width_adjustment_qm);
		expt_plus_e = FIX((SI_Long)0L);
	    }
	    else {
		aligned_size_plus_e = FIXNUM_ADD(aligned_size_plus_e,
			FIXNUM_MINUS(adjusted_fraction_plus_e_qm,
			fraction_plus_e));
		fraction_plus_e = adjusted_fraction_plus_e_qm;
	    }
	}
	else if (discrete_qm && FIXNUM_LE(FIXNUM_ADD(whole_e,fraction_e),
		FIX((SI_Long)7L))) {
	    aligned_size_plus_e = aligned_size_e;
	    whole_plus_e = whole_e;
	    fraction_plus_e = fraction_e;
	    expt_plus_e = FIX((SI_Long)0L);
	}
	else if (FIXNUM_LE(aligned_size_e,aligned_size_plus_e)) {
	    aligned_size_plus_e = aligned_size_e;
	    whole_plus_e = whole_e;
	    fraction_plus_e = fraction_e;
	    expt_plus_e = FIX((SI_Long)0L);
	}
    }
    else if (EQ(Axis_heading,Qeast)) {
	if (significant_digits_qm) {
	    if (FIXNUM_GE(significant_digits_qm,FIXNUM_ADD(whole_e,
		    fraction_e))) {
		aligned_size_plus_e = FIXNUM_ADD(unaligned_size_e,
			whole_width_adjustment_qm);
		whole_plus_e = whole_e;
		fraction_plus_e = FIXNUM_ADD(fraction_e,
			fraction_width_adjustment_qm);
		expt_plus_e = FIX((SI_Long)0L);
	    }
	    else {
		aligned_size_plus_e = FIXNUM_ADD(aligned_size_plus_e,
			FIXNUM_MINUS(adjusted_fraction_plus_e_qm,
			fraction_plus_e));
		fraction_plus_e = adjusted_fraction_plus_e_qm;
	    }
	}
	else if (discrete_qm && IFIX(FIXNUM_ADD(whole_e,fraction_e)) < 
		(SI_Long)7L) {
	    aligned_size_plus_e = unaligned_size_e;
	    whole_plus_e = whole_e;
	    fraction_plus_e = fraction_e;
	    expt_plus_e = FIX((SI_Long)0L);
	}
	else if (FIXNUM_LE(unaligned_size_e,aligned_size_plus_e)) {
	    aligned_size_plus_e = unaligned_size_e;
	    whole_plus_e = whole_e;
	    fraction_plus_e = fraction_e;
	    expt_plus_e = FIX((SI_Long)0L);
	}
    }
    return VALUES_4(aligned_size_plus_e,whole_plus_e,fraction_plus_e,
	    expt_plus_e);
}

/* ADJUST-FOR-THE-SIGN-P */
Object adjust_for_the_sign_p(axis_min,axis_max)
    Object axis_min, axis_max;
{
    Object temp, min_1, max_1;
    double arg, arg_1, temp_1;

    x_note_fn_call(177,249);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(axis_min) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(axis_min)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(axis_min,(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(axis_min) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(axis_min)) == (SI_Long)1L)
	temp = aref1(axis_min,FIX((SI_Long)0L));
    else
	temp = axis_min;
    min_1 = lfloat(temp,float_constant_1);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(axis_max) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(axis_max)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(axis_max,(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(axis_max) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(axis_max)) == (SI_Long)1L)
	temp = aref1(axis_max,FIX((SI_Long)0L));
    else
	temp = axis_max;
    max_1 = lfloat(temp,float_constant_1);
    arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
    arg_1 = 0.0;
    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	temp = Nil;
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(max_1);
	arg_1 = 0.0;
	if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    temp = T;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	    temp = lffloor(DOUBLE_TO_DOUBLE_FLOAT(DOUBLE_LOG( - temp_1,
		    10.0)),_);
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(max_1);
	    temp = lffloor(DOUBLE_TO_DOUBLE_FLOAT(DOUBLE_LOG(temp_1,10.0)),_);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		temp = T;
	    else
		temp = Nil;
	}
    }
    return VALUES_1(temp);
}

/* FLOAT-STRING-FIELD-WIDTHS */
Object float_string_field_widths(float_string)
    Object float_string;
{
    Object size, dot_index, e_index, non_float_qm, char_1, temp, temp_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol;

    x_note_fn_call(177,250);
    size = text_string_length(float_string);
    dot_index = Nil;
    e_index = Nil;
    non_float_qm = Nil;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(size);
    char_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_1 = FIX(UBYTE_16_ISAREF_1(float_string,i));
    temp = char_1;
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L)))) {
	gensymed_symbol = IFIX(char_1);
	if ( !((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) :
		 TRUEP(Nil))) {
	    non_float_qm = T;
	    goto end_loop;
	}
    }
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 46:
	    dot_index = FIX(i);
	    break;
	  case 101:
	    e_index = FIX(i);
	    goto end_loop;
	    break;
	  case 43:
	  case 45:
	    break;
	  default:
	    gensymed_symbol = IFIX(char_1);
	    if ( !((SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		    (SI_Long)57L ? TRUEP(FIX(gensymed_symbol - 
		    (SI_Long)48L)) : TRUEP(Nil))) {
		non_float_qm = T;
		goto end_loop;
	    }
	    break;
	}
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (non_float_qm ||  !TRUEP(dot_index) &&  !TRUEP(e_index))
	return VALUES_3(size,FIX((SI_Long)0L),FIX((SI_Long)0L));
    else if ( !TRUEP(e_index)) {
	temp = FIXNUM_SUB1(FIXNUM_MINUS(size,dot_index));
	return VALUES_3(dot_index,temp,FIX((SI_Long)0L));
    }
    else if ( !TRUEP(dot_index)) {
	temp = FIXNUM_SUB1(FIXNUM_MINUS(size,e_index));
	return VALUES_3(e_index,FIX((SI_Long)0L),temp);
    }
    else {
	temp_1 = FIXNUM_SUB1(FIXNUM_MINUS(e_index,dot_index));
	temp = FIXNUM_SUB1(FIXNUM_MINUS(size,e_index));
	return VALUES_3(dot_index,temp_1,temp);
    }
    return VALUES_1(Qnil);
}

/* FLOAT-STRING-FIELD-WIDTHS-WITHOUT-EXPT */
Object float_string_field_widths_without_expt(precision,expt_1)
    Object precision, expt_1;
{
    Object temp, temp_2;
    SI_Long temp_1;

    x_note_fn_call(177,251);
    if (IFIX(expt_1) >= (SI_Long)0L) {
	temp = FIXNUM_ADD1(expt_1);
	temp_1 = IFIX(FIXNUM_MINUS(precision,expt_1));
	temp_2 = FIX(MAX(temp_1,(SI_Long)1L));
	return VALUES_2(temp,temp_2);
    }
    else {
	temp_2 = FIXNUM_MINUS(precision,expt_1);
	return VALUES_2(FIX((SI_Long)1L),temp_2);
    }
}

static Object list_constant_31;    /* # */

/* FLOAT-STRING-SIGNED-P */
Object float_string_signed_p(string_1)
    Object string_1;
{
    x_note_fn_call(177,252);
    if (IFIX(text_string_length(string_1)) > (SI_Long)0L && 
	    wide_character_member(FIX(UBYTE_16_ISAREF_1(string_1,
	    (SI_Long)0L)),list_constant_31))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

static Object float_constant_5;    /* 10.0 */

/* FLOAT-EXPT-AND-SIZE */
Object float_expt_and_size(float_1)
    Object float_1;
{
    Object expt_1, temp_1;
    SI_Long size;
    char temp_2;
    double arg, arg_1, temp;

    x_note_fn_call(177,253);
    arg = DOUBLE_FLOAT_TO_DOUBLE(float_1);
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	return VALUES_2(FIX((SI_Long)0L),FIX((SI_Long)1L));
    else {
	temp = DOUBLE_FLOAT_TO_DOUBLE(float_1);
	expt_1 = lfloor(DOUBLE_TO_DOUBLE_FLOAT(DOUBLE_LOG(ABS(temp),10.0)),_);
	size = IFIX(expt_1) == (SI_Long)0L ? (SI_Long)1L : 
		IFIX(FIXNUM_ADD1(lfloor(llog(FIXNUM_ABS(expt_1),
		FIX((SI_Long)10L)),_)));
	temp_1 = FIX((SI_Long)0L);
	if (NUM_GT(expt_1,temp_1)) {
	    temp_1 = expt(float_constant_5,FIXNUM_ADD1(expt_1));
	    arg = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    temp = DOUBLE_FLOAT_TO_DOUBLE(float_1);
	    arg_1 = ABS(temp);
	    temp_2 = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    expt_1 = add1(expt_1);
	return VALUES_2(expt_1,IFIX(expt_1) < (SI_Long)0L ? FIX(size + 
		(SI_Long)1L) : FIX(size));
    }
}

/* FLOAT-DISCRIMINATION-PRECISION */
Object float_discrimination_precision(x,y,extra_precision)
    Object x, y, extra_precision;
{
    Object min_1, max_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    double temp, temp_1, x_y, arg, arg_1;

    x_note_fn_call(177,254);
    temp = DOUBLE_FLOAT_TO_DOUBLE(x);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(y);
    x_y = temp - temp_1;
    min_1 = Nil;
    max_1 = Nil;
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(y);
    arg = ABS(temp_1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(x);
    arg_1 = ABS(temp_1);
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	min_1 = y;
	max_1 = x;
    }
    else {
	min_1 = x;
	max_1 = y;
    }
    gensymed_symbol = (SI_Long)1L;
    gensymed_symbol_1 = 
	    IFIX(Maximum_significant_decimal_digits_in_gensym_float);
    arg = x_y;
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	gensymed_symbol_2 = 
		IFIX(Maximum_significant_decimal_digits_in_gensym_float);
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	arg_1 = 0.0;
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    gensymed_symbol_2 = (SI_Long)1L;
	else {
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(min_1);
	    temp_1 = x_y / temp_1;
	    gensymed_symbol_2 = 
		    IFIX(FIXNUM_ADD(FIXNUM_NEGATE(ltruncate(lffloor(DOUBLE_TO_DOUBLE_FLOAT(DOUBLE_LOG(ABS(temp_1),
		    10.0)),_),_)),extra_precision));
	}
    }
    gensymed_symbol_1 = MIN(gensymed_symbol_1,gensymed_symbol_2);
    return VALUES_1(FIX(MAX(gensymed_symbol,gensymed_symbol_1)));
}

static Object Qmalformed_data_series;  /* malformed-data-series */

static Object Qfloat_and_float_from_data_caches;  /* float-and-float-from-data-caches */

/* SETUP-CHART-DATA-CACHES */
Object setup_chart_data_caches(all_computed_data_series)
    Object all_computed_data_series;
{
    Object current_computation_component_particulars, current_data_series;
    Object ab_loop_list_, computed_data_series, ab_loop_list__1;
    Object data_series_index, ab_loop_iter_flag_, old_current_part_description;
    Object new_cons, temp, temp_1, svref_new_value, gensymed_symbol;
    Object computed_data_series_data_cache_1_qm;
    Object computed_data_series_data_cache_2_qm;
    Object computed_data_series_source_kind, part, part_feature_index;
    Object exit_feature_handler, part_stack_pop_store, cons_1, next_cons;
    Declare_special(3);
    Object result;

    x_note_fn_call(177,255);
    current_computation_component_particulars = 
	    slot_value_list_2(Qdata_series,FIX((SI_Long)0L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	    2);
      current_data_series = Nil;
      ab_loop_list_ = Data_series_subparts;
      PUSH_SPECIAL_WITH_SYMBOL(Current_data_series,Qcurrent_data_series,current_data_series,
	      1);
	computed_data_series = Nil;
	ab_loop_list__1 = all_computed_data_series;
	data_series_index = FIX((SI_Long)1L);
	PUSH_SPECIAL_WITH_SYMBOL(Data_series_index,Qdata_series_index,data_series_index,
		0);
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  Current_data_series = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop;
	  computed_data_series = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      Data_series_index = FIXNUM_ADD1(Data_series_index);
	  old_current_part_description = Current_part_description;
	  Current_part_description = Current_data_series;
	  if (Maintain_stack_of_current_part_descriptions_p) {
	      new_cons = ISVREF(Available_part_stack_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_part_stack_conses_vector;
		  temp_1 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,temp_1) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_part_stack_conses_tail_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = Nil;
		  }
		  gensymed_symbol = new_cons;
	      }
	      else
		  gensymed_symbol = Nil;
	      if ( !TRUEP(gensymed_symbol))
		  gensymed_symbol = replenish_part_stack_cons_pool();
	      temp = Current_part_description;
	      M_CAR(gensymed_symbol) = temp;
	      temp = Stack_of_current_part_descriptions;
	      M_CDR(gensymed_symbol) = temp;
	      inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	      Stack_of_current_part_descriptions = gensymed_symbol;
	  }
	  new_cons = ISVREF(Available_part_stack_conses_vector,
		  IFIX(Current_thread_index));
	  if (new_cons) {
	      temp = Available_part_stack_conses_vector;
	      temp_1 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(temp,temp_1) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_part_stack_conses_vector,
		      IFIX(Current_thread_index)))) {
		  temp = Available_part_stack_conses_tail_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = Nil;
	      }
	      gensymed_symbol = new_cons;
	  }
	  else
	      gensymed_symbol = Nil;
	  if ( !TRUEP(gensymed_symbol))
	      gensymed_symbol = replenish_part_stack_cons_pool();
	  M_CAR(gensymed_symbol) = Qmark;
	  temp = Part_feature_recall_stack;
	  M_CDR(gensymed_symbol) = temp;
	  inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
	  Part_feature_recall_stack = gensymed_symbol;
	  enter_part_description(Current_part_description);
	  temp = Current_computation_component_particulars;
	  temp_1 = Data_series_index;
	  M_SECOND(temp) = temp_1;
	  computed_data_series_data_cache_1_qm = Nil;
	  computed_data_series_data_cache_2_qm = Nil;
	  if (EQ(T,Data_series_failed_to_compile))
	      computed_data_series_source_kind = Qmalformed_data_series;
	  else if (EQ(Data_series_source_kind,Qone_g2_quantity_list)) {
	      computed_data_series_data_cache_2_qm = 
		      make_float_data_cache_from_designation_qm(Data_series_info_1);
	      if (computed_data_series_data_cache_2_qm)
		  computed_data_series_data_cache_1_qm = 
			  make_float_data_cache_for_index(ISVREF(computed_data_series_data_cache_2_qm,
			  (SI_Long)1L));
	      computed_data_series_source_kind = 
		      computed_data_series_data_cache_1_qm && 
		      computed_data_series_data_cache_2_qm ? 
		      Qfloat_and_float_from_data_caches : 
		      Qmalformed_data_series;
	  }
	  else if (EQ(Data_series_source_kind,Qpair_of_g2_quantity_lists)) {
	      computed_data_series_data_cache_1_qm = 
		      make_float_data_cache_from_designation_qm(Data_series_info_1);
	      computed_data_series_data_cache_2_qm = 
		      make_float_data_cache_from_designation_qm(Data_series_info_2);
	      computed_data_series_source_kind = 
		      computed_data_series_data_cache_1_qm && 
		      computed_data_series_data_cache_2_qm ? 
		      Qfloat_and_float_from_data_caches : 
		      Qmalformed_data_series;
	  }
	  else
	      computed_data_series_source_kind = Qmalformed_data_series;
	  part = computed_data_series;
	  set_simple_part_feature(part,Qdata_series_data_cache_1_qm,
		  computed_data_series_data_cache_1_qm);
	  set_simple_part_feature(part,Qdata_series_data_cache_2_qm,
		  computed_data_series_data_cache_2_qm);
	  set_simple_part_feature(part,Qdata_series_source_kind,
		  computed_data_series_source_kind);
	  part_feature_index = Nil;
	  exit_feature_handler = Nil;
	next_loop_1:
	  part_stack_pop_store = Nil;
	  cons_1 = Part_feature_recall_stack;
	  if (cons_1) {
	      part_stack_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qpart_stack);
	      if (ISVREF(Available_part_stack_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp = ISVREF(Available_part_stack_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp) = cons_1;
		  temp = Available_part_stack_conses_tail_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = cons_1;
	      }
	      else {
		  temp = Available_part_stack_conses_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = cons_1;
		  temp = Available_part_stack_conses_tail_vector;
		  temp_1 = Current_thread_index;
		  SVREF(temp,temp_1) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Part_feature_recall_stack = next_cons;
	  part_feature_index = part_stack_pop_store;
	  if (EQ(part_feature_index,Qmark))
	      goto end_loop_1;
	  exit_feature_handler = ISVREF(Part_feature_exit_methods,
		  IFIX(part_feature_index));
	  inline_funcall_0(exit_feature_handler);
	  goto next_loop_1;
	end_loop_1:;
	  Current_part_description = old_current_part_description;
	  if (Maintain_stack_of_current_part_descriptions_p) {
	      part_stack_pop_store = Nil;
	      cons_1 = Stack_of_current_part_descriptions;
	      if (cons_1) {
		  part_stack_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qpart_stack);
		  if (ISVREF(Available_part_stack_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = 
			      ISVREF(Available_part_stack_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_part_stack_conses_tail_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		  }
		  else {
		      temp = Available_part_stack_conses_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		      temp = Available_part_stack_conses_tail_vector;
		      temp_1 = Current_thread_index;
		      SVREF(temp,temp_1) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_current_part_descriptions = next_cons;
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop;
	end_loop:
	  reclaim_slot_value_list_1(Current_computation_component_particulars);
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_10;  /* "the designation, i.e. \"~ND\", did not denote anything." */

static Object string_constant_11;  /* "the designation, i.e. \"~ND\", denoted the ~(~a~) ~NV.  A quantity-list or quantity-array was needed." */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object string_constant_12;  /* "the designation, i.e. \"~ND\", denoted the ~(~a~) ~NF.  A quantity-list or quantity-array was needed." */

static Object list_constant_32;    /* # */

static Object string_constant_13;  /* "" */

static Object string_constant_14;  /* "s" */

static Object string_constant_15;  /* "the designation, i.e. \"~ND\", denoted a data-series containing ~A NaN~A ~
				    * ???     (IEEE floating-point Not a Number value~A)"
				    */

static Object string_constant_16;  /* "a" */

/* MAKE-FLOAT-DATA-CACHE-FROM-DESIGNATION? */
Object make_float_data_cache_from_designation_qm(designation_qm)
    Object designation_qm;
{
    Object data_source, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, managed_number_or_value, temp_1, class_1, skip_list;
    Object key_value, marked, pred, curr, succ, reference, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, temp_2, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector, data_values, length_2;
    Object data_cache, nan_count, data_value, ab_loop_list_, value;
    Object ab_loop_iter_flag_, plural_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, key_hash_value;
    SI_Long bottom_level, level, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long gensymed_symbol_5, i;
    char temp_3;
    double aref_new_value_1;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,256);
    if ( !TRUEP(designation_qm))
	return VALUES_1(Nil);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    data_source = evaluate_designation(designation_qm,Nil);
	    if ( !TRUEP(data_source)) {
		if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
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
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  write_warning_message_header(FIX((SI_Long)1L));
				  tformat(2,string_constant_10,designation_qm);
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
		result = VALUES_1(Nil);
	    }
	    else if (SIMPLE_VECTOR_P(data_source) && EQ(ISVREF(data_source,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			{
		if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
			!TRUEP(Debugging_reset)) {
		    if ( !TRUEP(Defer_notifications_qm))
			break_out_of_debug_messages();
		    snapshots_of_related_blocks = Nil;
		    note_blocks_in_tformat = 
			    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
		    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
			    6);
		      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
			      5);
			current_wide_string_list = Qdo_not_use;
			PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				4);
			  wide_string_bv16 = 
				  allocate_byte_vector_16(FIX((SI_Long)2048L 
				  + (SI_Long)3L));
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
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  write_warning_message_header(FIX((SI_Long)1L));
				  temp = ISVREF(data_source,(SI_Long)2L);
				  managed_number_or_value = 
					  ISVREF(data_source,(SI_Long)1L);
				  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      temp_1 = 
					      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					      (SI_Long)0L));
				  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      temp_1 = 
					      aref1(managed_number_or_value,
					      FIX((SI_Long)0L));
				  else if (text_string_p(managed_number_or_value))
				      temp_1 = 
					      copy_text_string(managed_number_or_value);
				  else
				      temp_1 = managed_number_or_value;
				  tformat(4,string_constant_11,
					  designation_qm,temp,temp_1);
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
		result = VALUES_1(Nil);
	    }
	    else {
		class_1 = ISVREF(ISVREF(data_source,(SI_Long)1L),(SI_Long)1L);
		skip_list = CDR(Symbol_properties_table);
		key_value = class_1;
		key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		    gensymed_symbol = class_1;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
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
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
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
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_list_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_3 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3);
		else {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = class_1;
		    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
			    IFIX(Most_positive_fixnum);
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_14;
		  end_loop_13:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_5;
		    goto next_loop_13;
		  end_loop_14:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = class_1;
			temp_1 = Symbol_properties_table;
			temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    temp_2 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(temp_2,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
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
			gensymed_symbol = set_skip_list_entry(temp_1,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
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
		  next_loop_15:
		    if (level < ab_loop_bind_)
			goto end_loop_15;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_16:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_17:
		    if ( !TRUEP(marked))
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_17;
		  end_loop_16:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_6;
		    goto next_loop_16;
		  end_loop_17:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_15;
		  end_loop_15:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
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
		      next_loop_18:
			if (level < ab_loop_bind_)
			    goto end_loop_18;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_19:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_20:
			if ( !TRUEP(marked))
			    goto end_loop_19;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_20;
		      end_loop_19:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_7;
			goto next_loop_19;
		      end_loop_20:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_18;
		      end_loop_18:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
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
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_22:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_23:
			if ( !TRUEP(marked))
			    goto end_loop_22;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_23;
		      end_loop_22:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_8;
			goto next_loop_22;
		      end_loop_23:
		      end_8:
			level = level - (SI_Long)1L;
			goto next_loop_21;
		      end_loop_21:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    gensymed_symbol = resulting_value;
		    if (gensymed_symbol) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Quantity_array_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_3 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_4 = (SI_Long)1L;
			    gensymed_symbol_5 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_4 = gensymed_symbol_4 << 
				    gensymed_symbol_5;
			    gensymed_symbol_3 = gensymed_symbol_3 & 
				    gensymed_symbol_4;
			    temp_3 = (SI_Long)0L < gensymed_symbol_3;
			}
			else
			    temp_3 = TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		if ( !temp_3) {
		    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
			    !TRUEP(Debugging_reset)) {
			if ( !TRUEP(Defer_notifications_qm))
			    break_out_of_debug_messages();
			snapshots_of_related_blocks = Nil;
			note_blocks_in_tformat = 
				SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				6);
			  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				  5);
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
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
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
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      write_warning_message_header(FIX((SI_Long)1L));
				      tformat(4,string_constant_12,
					      designation_qm,
					      ISVREF(ISVREF(data_source,
					      (SI_Long)1L),(SI_Long)1L),
					      data_source);
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
		    result = VALUES_1(Nil);
		}
		else {
		    data_values = 
			    serve_eval_list_of_role_values(list_constant_32,
			    data_source);
		    length_2 = length(data_values);
		    data_cache = allocate_managed_float_array(1,length_2);
		    nan_count = FIX((SI_Long)0L);
		    data_value = Nil;
		    ab_loop_list_ = data_values;
		    i = (SI_Long)0L;
		    value = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_24:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_24;
		    data_value = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if ( !TRUEP(ab_loop_iter_flag_))
			i = i + (SI_Long)1L;
		    managed_number_or_value = ISVREF(data_value,(SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp = copy_text_string(managed_number_or_value);
		    else
			temp = managed_number_or_value;
		    value = lfloat(temp,float_constant_1);
		    if (exceptional_float_p(value))
			nan_count = FIXNUM_ADD1(nan_count);
		    else {
			temp_2 = ISVREF(data_cache,(i >>  -  - 
				(SI_Long)10L) + (SI_Long)2L);
			aref_arg_2 = i & (SI_Long)1023L;
			aref_new_value_1 = DOUBLE_FLOAT_TO_DOUBLE(value);
			DFLOAT_ISASET_1(temp_2,aref_arg_2,aref_new_value_1);
		    }
		    reclaim_temporary_constant_1(data_value);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_24;
		  end_loop_24:
		    if (IFIX(nan_count) > (SI_Long)0L) {
			plural_string = IFIX(nan_count) == (SI_Long)1L ? 
				string_constant_13 : string_constant_14;
			if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
				!TRUEP(Debugging_reset)) {
			    if ( !TRUEP(Defer_notifications_qm))
				break_out_of_debug_messages();
			    snapshots_of_related_blocks = Nil;
			    note_blocks_in_tformat = 
				    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				    6);
			      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				      5);
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
					  write_warning_message_header(FIX((SI_Long)1L));
					  tformat(5,string_constant_15,
						  designation_qm,
						  IFIX(nan_count) == 
						  (SI_Long)1L ? 
						  string_constant_16 : 
						  nan_count,plural_string,
						  plural_string);
					  temp = 
						  copy_out_current_wide_string();
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
			result = VALUES_1(Nil);
			goto end_9;
		    }
		    reclaim_eval_list_1(data_values);
		    result = VALUES_1(data_cache);
		    goto end_9;
		    result = VALUES_1(Qnil);
		  end_9:;
		}
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

/* MAKE-FLOAT-DATA-CACHE-FOR-INDEX */
Object make_float_data_cache_for_index(length_1)
    Object length_1;
{
    Object data_cache, ab_loop_iter_flag_, aref_arg_1;
    SI_Long data_value, ab_loop_bind_, i, aref_arg_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(177,257);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	data_cache = allocate_managed_float_array(1,length_1);
	data_value = (SI_Long)1L;
	ab_loop_bind_ = IFIX(length_1);
	i = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (data_value > ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	aref_arg_1 = ISVREF(data_cache,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = (double)data_value;
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	ab_loop_iter_flag_ = Nil;
	data_value = data_value + (SI_Long)1L;
	goto next_loop;
      end_loop:
	result = VALUES_1(data_cache);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* PUT-CHART-STYLE */
Object put_chart_style(chart,new_chart_style,initializing_qm)
    Object chart, new_chart_style, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,258);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)34L),(SI_Long)1L);
      gensymed_symbol_1 = Chart;
      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Chart,Qchart_style);
      svref_arg_1 = Chart;
      SVREF(svref_arg_1,FIX((SI_Long)19L)) = new_chart_style;
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)33L),(SI_Long)1L);
      gensymed_symbol_1 = Chart;
      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      if ( !TRUEP(initializing_qm))
	  update_chart(Chart);
      result = VALUES_1(new_chart_style);
    POP_SPECIAL();
    return result;
}

/* PUT-DATA-SERIES */
Object put_data_series(chart,new_data_series,initializing_qm)
    Object chart, new_data_series, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object temp_1, frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,259);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      result_1 = Nil;
      current_flag_state_qm = Nil;
      slot_description = 
	      get_slot_description_of_class_description_function(Qframe_status_and_notes,
	      ISVREF(Chart,(SI_Long)1L),Nil);
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
	  gensymed_symbol_1 = nconc2(stack_change_list_2(Chart,
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
	  temp = Chart;
	  M_CAR(gensymed_symbol_1) = temp;
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
	current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(Chart,
		(SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	if ( !TRUEP(current_flag_state_qm)) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = Chart;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = T;
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    temp = Chart;
	    svref_new_value_1 = IFIX(ISVREF(Chart,(SI_Long)5L)) | 
		    (SI_Long)16777216L;
	    ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	}
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)34L),(SI_Long)1L);
	gensymed_symbol_1 = Chart;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(Chart,Qdata_series);
	temp = Chart;
	temp_1 = SVREF(temp,FIX((SI_Long)20L)) = new_data_series;
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)33L),(SI_Long)1L);
	gensymed_symbol_1 = Chart;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	result_1 = temp_1;
	if ( !TRUEP(current_flag_state_qm)) {
	    temp = Chart;
	    svref_new_value_1 = IFIX(ISVREF(Chart,(SI_Long)5L)) &  
		    ~(SI_Long)16777216L;
	    ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value_1);
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	    gensymed_symbol_1 = Chart;
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
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (ATOM(frame_and_slot_or_atom))
		goto end_loop;
	    temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	    if (temp_2);
	    else {
		temp_1 = M_CDR(frame_and_slot_or_atom);
		temp_2 = CONSP(temp_1) ? EQ(slot_description,
			SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	    }
	    ab_loop_it_ = temp_2 ? (EQ(Chart,
		    M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_2 = TRUEP(Nil);
	if ( !temp_2)
	    update_all_representations_of_slot(Chart,slot_description,Nil,Nil);
	if (ISVREF(slot_description,(SI_Long)14L))
	    update_frame_name_references(Chart);
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
      if ( !TRUEP(initializing_qm))
	  update_chart(Chart);
      result = VALUES_1(new_data_series);
    POP_SPECIAL();
    return result;
}

/* PUT-ANNOTATIONS */
Object put_annotations(chart,new_annotations,initializing_qm)
    Object chart, new_annotations, initializing_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, svref_arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,260);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)34L),(SI_Long)1L);
      gensymed_symbol_1 = Chart;
      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Chart,Qannotations);
      svref_arg_1 = Chart;
      SVREF(svref_arg_1,FIX((SI_Long)21L)) = new_annotations;
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(Chart,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)33L),(SI_Long)1L);
      gensymed_symbol_1 = Chart;
      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      if ( !TRUEP(initializing_qm))
	  update_chart(Chart);
      result = VALUES_1(new_annotations);
    POP_SPECIAL();
    return result;
}

static Object Qpriority;           /* priority */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qupdate_chart;       /* update-chart */

/* ACTIVATE-FOR-CHART */
Object activate_for_chart(chart)
    Object chart;
{
    Object current_computation_frame, computation_style_description, priority;
    Object initial_scan_wait_interval, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed, frame;
    Object sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(4);
    Object result;

    x_note_fn_call(177,261);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,3);
      current_computation_frame = Chart;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      2);
	computation_style_description = 
		get_default_computation_style_of_class();
	PUSH_SPECIAL_WITH_SYMBOL(Computation_style_description,Qcomputation_style_description,computation_style_description,
		1);
	  priority = get_simple_part_feature(Computation_style_description,
		  Qpriority);
	  initial_scan_wait_interval = 
		  get_simple_part_feature(Computation_style_description,
		  Qpriority);
	  if ( !TRUEP(In_suspend_resume_p)) {
	      old = Nil;
	      new_1 = Nil;
	    next_loop:
	      old = ISVREF(Chart,(SI_Long)18L);
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
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) 
		      = Nil;
	      SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) 
		      = Nil;
	      task = def_structure_schedule_task_variable;
	      temp = ISVREF(task,(SI_Long)1L);
	      aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,
		      (SI_Long)0L) + (double)IFIX(initial_scan_wait_interval);
	      DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      temp = ISVREF(task,(SI_Long)1L);
	      aref_new_value = -1.0;
	      DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	      svref_new_value_1 =  !TRUEP(Nil);
	      SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	      SVREF(task,FIX((SI_Long)4L)) = priority;
	      SVREF(task,FIX((SI_Long)5L)) = Nil;
	      SVREF(task,FIX((SI_Long)9L)) = Nil;
	      SVREF(task,FIX((SI_Long)10L)) = Nil;
	      SVREF(task,FIX((SI_Long)7L)) = Qupdate_chart;
	      temp = SYMBOL_FUNCTION(Qupdate_chart);
	      SVREF(task,FIX((SI_Long)8L)) = temp;
	      ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	      temp = Chart;
	      SVREF(task,FIX((SI_Long)13L)) = temp;
	      new_1 = task;
	      if (CAS_SVREF(Chart,(SI_Long)18L,old,new_1)) {
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
		      temp = 
			      ISVREF(Chain_of_available_schedule_tasks_vector,
			      IFIX(Current_thread_index));
		      SVREF(old,FIX((SI_Long)0L)) = temp;
		      temp = Chain_of_available_schedule_tasks_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = old;
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
		  temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			  IFIX(Current_thread_index));
		  SVREF(new_1,FIX((SI_Long)0L)) = temp;
		  temp = Chain_of_available_schedule_tasks_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp,svref_arg_2) = new_1;
	      }
	      goto next_loop;
	    end_loop:
	    end_1:;
	  }
	  frame = Chart;
	  sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)6L);
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		  (SI_Long)3L;
	next_loop_1:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop_1;
	  if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
	      method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	      goto end_2;
	  }
	  index_1 = index_1 + (SI_Long)2L;
	  goto next_loop_1;
	end_loop_1:
	  method_function_qm = Qnil;
	end_2:;
	  if (method_function_qm)
	      result = inline_funcall_1(method_function_qm,frame);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DEACTIVATE-FOR-CHART */
Object deactivate_for_chart(chart)
    Object chart;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long svref_new_value, index_1, ab_loop_bind_;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,262);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      if ( !TRUEP(In_suspend_resume_p)) {
	  gensymed_symbol = Nil;
	next_loop:
	  gensymed_symbol = ISVREF(Chart,(SI_Long)18L);
	  if (CAS_SVREF(Chart,(SI_Long)18L,gensymed_symbol,Nil)) {
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
	  temp = Chart;
	  svref_new_value = IFIX(ISVREF(Chart,(SI_Long)5L)) &  ~(SI_Long)1L;
	  ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value);
      }
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)7L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop_1:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop_1;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_2;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop_1;
    end_loop_1:
      method_function_qm = Qnil;
    end_2:;
      if (method_function_qm)
	  inline_funcall_1(method_function_qm,frame);
      if ( !TRUEP(In_suspend_resume_p)) {
	  update_chart(Chart);
	  temp = Chart;
	  svref_new_value = IFIX(ISVREF(Chart,(SI_Long)5L)) | (SI_Long)1L;
	  result = VALUES_1(ISVREF(temp,(SI_Long)5L) = FIX(svref_new_value));
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* CHANGE-SIZE-OF-CHART */
Object change_size_of_chart(chart,left_edge_of_bounding_box,
	    top_edge_of_bounding_box,right_edge_of_bounding_box,
	    bottom_edge_of_bounding_box)
    Object chart, left_edge_of_bounding_box, top_edge_of_bounding_box;
    Object right_edge_of_bounding_box, bottom_edge_of_bounding_box;
{
    Object current_annotated_frame, region_invalidation_is_preferred;
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol, gensymed_symbol_2, delta_left_edge;
    SI_Long delta_top_edge;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(3);
    Object result;

    x_note_fn_call(177,263);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,2);
      LOCK(Working_on_annotated_frame);
      if (PUSH_UNWIND_PROTECT(0)) {
	  current_annotated_frame = Chart;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_annotated_frame,Qcurrent_annotated_frame,current_annotated_frame,
		  1);
	    region_invalidation_is_preferred = T;
	    gensymed_symbol = IFIX(left_edge_of_bounding_box);
	    gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    delta_left_edge = gensymed_symbol - gensymed_symbol_2;
	    gensymed_symbol = IFIX(top_edge_of_bounding_box);
	    gensymed_symbol_1 = ISVREF(Chart,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    delta_top_edge = gensymed_symbol - gensymed_symbol_2;
	    PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
		    0);
	      erase_chart(Chart,T);
	      change_edges_of_block(Chart,left_edge_of_bounding_box,
		      top_edge_of_bounding_box,right_edge_of_bounding_box,
		      bottom_edge_of_bounding_box);
	      if (G2_has_v5_mode_windows_p &&  
		      !TRUEP(Ws_protocol_handle_moves_from_edge_change_p) 
		      && (delta_left_edge != (SI_Long)0L || delta_top_edge 
		      != (SI_Long)0L))
		  send_ws_representations_item_moved(Chart,
			  FIX(delta_left_edge),FIX(delta_top_edge));
	      enlarge_workspace_for_block_rectangle_if_necessary(Chart,Nil);
	      SAVE_VALUES(recompute_and_draw_chart(Chart));
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      POP_UNWIND_PROTECT(0);
      UNLOCK(Working_on_annotated_frame);
      CONTINUE_UNWINDING(0);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* RESTORE-CHART-TO-NORMAL-SIZE */
Object restore_chart_to_normal_size(chart)
    Object chart;
{
    Object gensymed_symbol, left, top, right, bottom;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,264);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      left = gensymed_symbol;
      gensymed_symbol = ISVREF(Chart,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      top = gensymed_symbol;
      right = FIXNUM_ADD(left,Default_chart_width);
      bottom = FIXNUM_ADD(top,Default_chart_height);
      result = change_size_of_chart(Chart,left,top,right,bottom);
    POP_SPECIAL();
    return result;
}

/* WRITE-PATCH-INSTANCE-CHART-NOTE-NOTE */
Object write_patch_instance_chart_note_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(177,265);
    GENSYM_RETURN_ONE(tformat(1,string_constant_13));
    return VALUES_1(Nil);
}

static Object string_constant_17;  /* "the chart will appear empty until some data series are specified" */

/* WRITE-NO-DATA-SERIES-CHART-NOTE-NOTE */
Object write_no_data_series_chart_note_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    x_note_fn_call(177,266);
    GENSYM_RETURN_ONE(tformat(1,string_constant_17));
    return VALUES_1(Nil);
}

static Object Qpatch_instance_chart_note;  /* patch-instance-chart-note */

static Object Qno_data_series_chart_note;  /* no-data-series-chart-note */

/* RETRACT-FRAME-NOTES-FOR-CHART */
Object retract_frame_notes_for_chart(chart)
    Object chart;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,267);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      delete_frame_note_if_any(Qpatch_instance_chart_note,Chart);
      delete_frame_note_if_any(Qno_data_series_chart_note,Chart);
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)34L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_1;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop;
    end_loop:
      method_function_qm = Qnil;
    end_1:;
      if (method_function_qm)
	  result = inline_funcall_1(method_function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* ASSERT-FRAME-NOTES-FOR-CHART */
Object assert_frame_notes_for_chart(chart)
    Object chart;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(177,268);
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,0);
      frame = Chart;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)33L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qchart)) {
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
      if ( !TRUEP(ISVREF(Chart,(SI_Long)20L)))
	  result = add_frame_note(5,Qno_data_series_chart_note,Chart,Nil,T,
		  Nil);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qgraph;              /* graph */

static Object Qtrend_chart;        /* trend-chart */

/* DECACHE-ALL-GRAPH-RENDERINGS-ON-WINDOW */
Object decache_all_graph_renderings_on_window(gensym_window)
    Object gensym_window;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, graph, temp_1, list_1;
    Object graph_rendering, next_list, chart, trend_chart, state_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(177,269);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    graph = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qgraph);
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
      graph = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      temp_1 = ISVREF(graph,(SI_Long)19L);
      temp_1 = FIRST(temp_1);
      list_1 = ISVREF(FIRST(temp_1),(SI_Long)42L);
      graph_rendering = Nil;
      next_list = Nil;
    next_loop_2:
      graph_rendering = CAR(list_1);
      next_list = CDR(list_1);
      if ( !TRUEP(list_1))
	  goto end_loop_2;
      if (EQ(ISVREF(graph_rendering,(SI_Long)17L),gensym_window))
	  decache_graph_rendering(graph_rendering);
      list_1 = next_list;
      goto next_loop_2;
    end_loop_2:
      goto end_1;
    end_1:;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    chart = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Chart,Qchart,chart,1);
      PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	ab_loopvar_ = collect_subclasses(Qchart);
      next_loop_3:
	if ( !TRUEP(ab_loopvar__1)) {
	  next_loop_4:
	    if ( !TRUEP(ab_loopvar_))
		goto end_loop_3;
	    ab_loopvar__1 = 
		    lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		    Instances_specific_to_this_class_kbprop);
	    ab_loopvar_ = M_CDR(ab_loopvar_);
	    if (ab_loopvar__1)
		goto end_loop_3;
	    goto next_loop_4;
	  end_loop_3:
	    temp =  !TRUEP(ab_loopvar__1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    goto end_loop_4;
	Chart = ab_loopvar__1;
	ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	list_1 = ISVREF(Chart,(SI_Long)16L);
	graph_rendering = Nil;
	next_list = Nil;
      next_loop_5:
	graph_rendering = CAR(list_1);
	next_list = CDR(list_1);
	if ( !TRUEP(list_1))
	    goto end_loop_5;
	if (EQ(ISVREF(graph_rendering,(SI_Long)17L),gensym_window))
	    decache_graph_rendering(graph_rendering);
	list_1 = next_list;
	goto next_loop_5;
      end_loop_5:
	goto end_2;
      end_2:;
	goto next_loop_3;
      end_loop_4:;
      POP_SPECIAL();
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    trend_chart = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qtrend_chart);
    next_loop_6:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_7:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_6;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_6;
	  goto next_loop_7;
	end_loop_6:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_7;
      trend_chart = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      list_1 = ISVREF(trend_chart,(SI_Long)26L);
      state_1 = Nil;
      next_list = Nil;
    next_loop_8:
      state_1 = CAR(list_1);
      next_list = CDR(list_1);
      if ( !TRUEP(list_1))
	  goto end_loop_8;
      if (EQ(ISVREF(ISVREF(state_1,(SI_Long)2L),(SI_Long)17L),gensym_window)) {
	  decache_graph_rendering(ISVREF(state_1,(SI_Long)2L));
	  ISVREF(state_1,(SI_Long)2L) = Nil;
      }
      list_1 = next_list;
      goto next_loop_8;
    end_loop_8:
      goto end_3;
    end_3:;
      goto next_loop_6;
    end_loop_7:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

void charts1_INIT()
{
    Object named_dynamic_extent_description, temp, temp_1, temp_2;
    Object reclaim_structure_for_chart_spot_1, type_description;
    Object chart_style_evaluation_setter_1, chart_style_evaluation_getter_1;
    Object write_plot_designation_may_not_contain_local_names_note_1;
    Object data_series_descriptions_evaluation_setter_1;
    Object data_series_descriptions_evaluation_getter_1;
    Object chart_features_evaluation_setter_1;
    Object chart_features_evaluation_getter_1;
    Object feature_path_evaluation_setter_1, feature_path_evaluation_getter_1;
    Object chart_annotation_evaluation_setter_1;
    Object chart_annotation_evaluation_getter_1;
    Object chart_annotations_sequence_evaluation_setter_1;
    Object chart_annotations_sequence_evaluation_getter_1;
    Object chart_data_point_features_evaluation_setter_1;
    Object chart_data_point_features_evaluation_getter_1;
    Object chart_data_series_features_evaluation_setter_1;
    Object chart_data_series_features_evaluation_getter_1;
    Object chart_axis_features_evaluation_setter_1;
    Object chart_axis_features_evaluation_getter_1;
    Object chart_data_point_features_sequence_evaluation_setter_1;
    Object chart_data_point_features_sequence_evaluation_getter_1;
    Object chart_data_series_features_sequence_evaluation_setter_1;
    Object chart_data_series_features_sequence_evaluation_getter_1;
    Object chart_axis_features_sequence_evaluation_setter_1;
    Object chart_axis_features_sequence_evaluation_getter_1;
    Object chart_annotations_evaluation_setter_1;
    Object chart_annotations_evaluation_getter_1;
    Object write_patch_instance_chart_note_note_1;
    Object write_no_data_series_chart_note_note_1;
    double temp_3;
    Object AB_package, Qclasses_which_define, Qassert_frame_notes;
    Object Qassert_frame_notes_for_chart, Qretract_frame_notes;
    Object Qretract_frame_notes_for_chart, Qframe_note_writer_1, Qdeactivate;
    Object Qdeactivate_for_chart, Qactivate, Qactivate_for_chart;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_putter, Qput_annotations;
    Object Qput_data_series, Qput_chart_style, list_constant_168;
    Object Qelement_iterator, Qdraw, Qdraw_for_chart, Qget_chart_data_series;
    Object Qinitial_chart_data_series, list_constant_253, list_constant_252;
    Object list_constant_238, Kwithin_putter, Kevent_updates;
    Object list_constant_251, Qab_or, list_constant_240, list_constant_250;
    Object list_constant_249, list_constant_248, list_constant_247;
    Object list_constant_246, list_constant_245, list_constant_244;
    Object list_constant_243, Qaxis_data_series, list_constant_242;
    Object list_constant_241, Qvirtual_attributes_local_to_class;
    Object Qget_chart_axis_computed_details;
    Object Qinitial_chart_axis_computed_details, list_constant_239;
    Object list_constant_237, list_constant_236, list_constant_235;
    Object list_constant_234, list_constant_233, list_constant_232;
    Object list_constant_231, list_constant_230, list_constant_229, Qmaximum;
    Object Qminimum, list_constant_228, list_constant_227, list_constant_226;
    Object list_constant_225, list_constant_224, list_constant_223;
    Object list_constant_222, list_constant_221, list_constant_220;
    Object list_constant_167, list_constant_219, list_constant_166, Qab_class;
    Object Qchart_annotations, Qnamed, list_constant_218, list_constant_217;
    Object list_constant_216, list_constant_215, list_constant_214;
    Object list_constant_213, list_constant_212, list_constant_211;
    Object list_constant_210, Qtype_specification_simple_expansion;
    Object list_constant_203, list_constant_191, list_constant_209;
    Object list_constant_208, list_constant_206, list_constant_205;
    Object list_constant_207, list_constant_204, list_constant_202;
    Object list_constant_201, list_constant_200, list_constant_199;
    Object list_constant_198, list_constant_197, list_constant_196;
    Object list_constant_195, list_constant_194, list_constant_193;
    Object list_constant_192, list_constant_190, list_constant_189;
    Object list_constant_138, list_constant_188, list_constant_187;
    Object list_constant_186, list_constant_185, list_constant_184;
    Object list_constant_183, list_constant_182, list_constant_181;
    Object list_constant_180, list_constant_179, list_constant_178;
    Object list_constant_177, list_constant_176, list_constant_175;
    Object list_constant_174, list_constant_173, list_constant_172;
    Object list_constant_171, list_constant_170, list_constant_169;
    Object list_constant_165, list_constant_164, Qcolor_or_metacolor;
    Object Qwrite_chart_annotations_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_chart_annotations_for_slot;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object Qfix_up_parse_upon_reduction, Qget_internal_spelling;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object Qreduce_annotation_1, Qreduce_annotation, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object list_constant_163, Qtext, Qno_item;
    Object Qcompile_data_series_descriptions_for_slot;
    Object Qwrite_data_series_descriptions_from_slot, string_constant_40;
    Object string_constant_39, Qdata_series_description;
    Object Qcompile_chart_style_for_slot, Qwrite_chart_style_from_slot;
    Object string_constant_38, list_constant_162, list_constant_156;
    Object list_constant_161, list_constant_150, list_constant_160;
    Object list_constant_148, list_constant_159, list_constant_158;
    Object list_constant_116, list_constant_157, list_constant_155, Qsmall;
    Object list_constant_154, list_constant_153, Qsquare, list_constant_152;
    Object list_constant_151, list_constant_149, list_constant_147;
    Object list_constant_146, Qsimple_scatter_plot, list_constant_145;
    Object list_constant_144, list_constant_143;
    Object Qproject_axis_tick_mark_chart_indicator, Qaxis_tick_mark;
    Object Qproject_solid_bar_chart_indicator, Qsolid_bar;
    Object Qproject_solid_column_chart_indicator, Qsolid_column;
    Object Qproject_bar_chart_indicator, Qbar, Qproject_column_chart_indicator;
    Object Qproject_x_chart_indicator, Qx, Qproject_cross_chart_indicator;
    Object Qcross, Qproject_square_chart_indicator;
    Object Qproject_triangle_chart_indicator;
    Object Qproject_rectangle_chart_indicator, Qrectangle;
    Object Qsimple_scatter_plot_data_series_projection_method;
    Object Qfloat_and_float_from_data_caches_close_generator;
    Object Qfloat_and_float_from_data_caches_next_tuple;
    Object Qfloat_and_float_from_data_caches_open_generator;
    Object Qmalformed_data_series_return_nil, list_constant_142;
    Object list_constant_141, list_constant_140, list_constant_139;
    Object Qaxis_series_close_generator, Qaxis_series_next_tuple;
    Object Qaxis_series_open_generator, float_constant_7, float_constant_6;
    Object list_constant_137, Qexit_part_feature_number_of_significant_digits;
    Object Qenter_part_feature_number_of_significant_digits;
    Object Qsimple_number_for_significant_digits, Qspecial_variable;
    Object Qsymbol_standing_in_for_unbound;
    Object Qsimple_number_for_significant_digits_p, Qtype_error_printer;
    Object string_constant_37, Qsimple_type_specification, list_constant_136;
    Object list_constant_135;
    Object Qexit_part_feature_axis_tickmark_label_max_digits_in_exponent;
    Object Qenter_part_feature_axis_tickmark_label_max_digits_in_exponent;
    Object list_constant_134;
    Object Qexit_part_feature_axis_tickmark_label_max_digits_after_point;
    Object Qenter_part_feature_axis_tickmark_label_max_digits_after_point;
    Object list_constant_133;
    Object Qexit_part_feature_axis_tickmark_label_max_digits_before_point;
    Object Qenter_part_feature_axis_tickmark_label_max_digits_before_point;
    Object list_constant_132, Qexit_part_feature_axis_tickmark_label_frequency;
    Object Qenter_part_feature_axis_tickmark_label_frequency;
    Object list_constant_131, Qexit_part_feature_axis_tickmark_count_as_fixnum;
    Object Qenter_part_feature_axis_tickmark_count_as_fixnum;
    Object list_constant_130, Qexit_part_feature_axis_automatic;
    Object Qenter_part_feature_axis_automatic, Qboolean, list_constant_129;
    Object Qexit_part_feature_axis_tickmark_step;
    Object Qenter_part_feature_axis_tickmark_step, Qsimple_number;
    Object list_constant_128, Qexit_part_feature_axis_tickmark_count;
    Object Qenter_part_feature_axis_tickmark_count, Qsimple_nonnegative_number;
    Object list_constant_127, Qexit_part_feature_axis_maximum;
    Object Qenter_part_feature_axis_maximum, list_constant_126;
    Object Qexit_part_feature_axis_crossover;
    Object Qenter_part_feature_axis_crossover, list_constant_125;
    Object Qexit_part_feature_axis_minimum, Qenter_part_feature_axis_minimum;
    Object string_constant_36, Qsimple_type_writer;
    Object Qsimple_nonnegative_number_type_writer;
    Object Qsimple_nonnegative_number_p, list_constant_124;
    Object Qsimple_number_type_writer, Qsimple_number_p, list_constant_123;
    Object list_constant_122, Qexit_part_feature_axis_index;
    Object Qenter_part_feature_axis_index, list_constant_121;
    Object Qexit_part_feature_axis_heading, Qenter_part_feature_axis_heading;
    Object list_constant_45, Qexit_subpart_exceptions;
    Object Qenter_subpart_exceptions, list_constant_78, list_constant_42;
    Object Qexit_subpart_defaults, Qenter_subpart_defaults, list_constant_39;
    Object Qexit_part_feature_subparts, Qenter_part_feature_subparts;
    Object list_constant_120, list_constant_113, list_constant_119;
    Object list_constant_118, list_constant_117, list_constant_74;
    Object Qallow_defaulting_in_parents, list_constant_115, Qhidden_features;
    Object list_constant_114, Qincludes, Qnamed_dynamic_extent_description;
    Object Qparts, list_constant_112, list_constant_35, string_constant_35;
    Object list_constant_111;
    Object Qexit_part_feature_data_point_show_connecting_line;
    Object Qenter_part_feature_data_point_show_connecting_line;
    Object list_constant_110, Qexit_part_feature_data_point_show_indicator;
    Object Qenter_part_feature_data_point_show_indicator, list_constant_109;
    Object Qexit_part_feature_data_point_indicator_projection_function;
    Object Qenter_part_feature_data_point_indicator_projection_function;
    Object list_constant_108, Qexit_data_point_indicator;
    Object Qenter_data_point_indicator, list_constant_107, list_constant_106;
    Object Qcall_handlers, list_constant_105, list_constant_104;
    Object Qexit_part_feature_data_point_last_y;
    Object Qenter_part_feature_data_point_last_y, list_constant_103;
    Object Qexit_part_feature_data_point_last_x;
    Object Qenter_part_feature_data_point_last_x, list_constant_102;
    Object Qexit_part_feature_data_point_first_y;
    Object Qenter_part_feature_data_point_first_y, list_constant_101;
    Object Qexit_part_feature_data_point_first_x;
    Object Qenter_part_feature_data_point_first_x, list_constant_100;
    Object Qexit_part_feature_data_point_y, Qenter_part_feature_data_point_y;
    Object list_constant_99, Qexit_part_feature_data_point_x;
    Object Qenter_part_feature_data_point_x, list_constant_98;
    Object Qexit_part_feature_data_point_tuple_2;
    Object Qenter_part_feature_data_point_tuple_2, list_constant_97;
    Object Qexit_part_feature_data_point_tuple_1;
    Object Qenter_part_feature_data_point_tuple_1, list_constant_96;
    Object Qexit_part_feature_data_point_tuple_valid_qm;
    Object Qenter_part_feature_data_point_tuple_valid_qm, list_constant_95;
    Object Qexit_part_feature_data_point_index;
    Object Qenter_part_feature_data_point_index, list_constant_38;
    Object list_constant_94, list_constant_72, list_constant_93;
    Object list_constant_92, list_constant_73, list_constant_91;
    Object Qtext_alginment, Qborder_thickness;
    Object Qallow_individual_exceptions_in_parents, Qdata_point;
    Object Quser_spelling, string_constant_34, list_constant_90;
    Object Qexit_part_feature_data_series_connect_first_and_last_point;
    Object Qenter_part_feature_data_series_connect_first_and_last_point;
    Object list_constant_89, Qexit_part_feature_data_series_generator_info_2;
    Object Qenter_part_feature_data_series_generator_info_2, list_constant_88;
    Object Qexit_part_feature_data_series_generator_info_1;
    Object Qenter_part_feature_data_series_generator_info_1, list_constant_87;
    Object Qexit_part_feature_data_series_illustration_kind;
    Object Qenter_part_feature_data_series_illustration_kind, list_constant_86;
    Object Qexit_part_feature_data_series_data_cache_2_qm;
    Object Qenter_part_feature_data_series_data_cache_2_qm;
    Object Qmanaged_float_array_qm, list_constant_85;
    Object Qexit_part_feature_data_series_data_cache_1_qm;
    Object Qenter_part_feature_data_series_data_cache_1_qm, list_constant_84;
    Object Qmanaged_float_array_qm_p, list_constant_83;
    Object Qexit_part_feature_data_series_failed_to_compile;
    Object Qenter_part_feature_data_series_failed_to_compile, list_constant_82;
    Object Qexit_part_feature_data_series_info_2;
    Object Qenter_part_feature_data_series_info_2, list_constant_81;
    Object Qexit_part_feature_data_series_info_1;
    Object Qenter_part_feature_data_series_info_1, list_constant_80;
    Object Qexit_part_feature_data_series_source_kind;
    Object Qenter_part_feature_data_series_source_kind, list_constant_79;
    Object Qexit_part_feature_data_series_index;
    Object Qenter_part_feature_data_series_index, list_constant_77;
    Object Qsubparts_collection, list_constant_56, list_constant_76;
    Object list_constant_75, Qchildren_part_types, string_constant_33;
    Object list_constant_71, Qexit_part_feature_chart_origin_y;
    Object Qenter_part_feature_chart_origin_y, list_constant_70;
    Object Qexit_part_feature_chart_origin_x;
    Object Qenter_part_feature_chart_origin_x, list_constant_69;
    Object Qexit_part_feature_chart_tuple_2_maximum;
    Object Qenter_part_feature_chart_tuple_2_maximum, Qtemporary_constant;
    Object list_constant_68, Qexit_part_feature_chart_tuple_2_minimum;
    Object Qenter_part_feature_chart_tuple_2_minimum, list_constant_67;
    Object Qexit_part_feature_chart_tuple_1_maximum;
    Object Qenter_part_feature_chart_tuple_1_maximum, list_constant_66;
    Object Qexit_part_feature_chart_tuple_1_minimum;
    Object Qenter_part_feature_chart_tuple_1_minimum, list_constant_65;
    Object Qexit_part_feature_chart_bottom_margin;
    Object Qenter_part_feature_chart_bottom_margin, list_constant_64;
    Object Qexit_part_feature_chart_left_margin;
    Object Qenter_part_feature_chart_left_margin, list_constant_63;
    Object Qexit_part_feature_chart_top_margin;
    Object Qenter_part_feature_chart_top_margin, list_constant_62;
    Object Qexit_part_feature_chart_right_margin;
    Object Qenter_part_feature_chart_right_margin, list_constant_61;
    Object Qexit_part_feature_chart_bottom, Qenter_part_feature_chart_bottom;
    Object list_constant_60, Qexit_part_feature_chart_right;
    Object Qenter_part_feature_chart_right, list_constant_59;
    Object Qexit_part_feature_chart_top, Qenter_part_feature_chart_top;
    Object list_constant_58, Qexit_part_feature_chart_left;
    Object Qenter_part_feature_chart_left, list_constant_57, list_constant_55;
    Object list_constant_54, list_constant_53, list_constant_48;
    Object list_constant_52, list_constant_51, list_constant_50;
    Object list_constant_49, Qother_descendant_part_types, string_constant_32;
    Object list_constant_47, Qexit_part_feature_grid_visible;
    Object Qenter_part_feature_grid_visible, list_constant_46;
    Object Qexit_part_feature_grid_color, Qenter_part_feature_grid_color;
    Object list_constant_44, list_constant_43, list_constant_41;
    Object list_constant_40, list_constant_37, list_constant_36;
    Object string_constant_31, Qcharts, string_constant_30;
    Object Qslot_value_reclaimer;
    Object Qreclaim_line_drawing_description_for_chart_value;
    Object Qline_drawing_description_for_chart, Qcleanup, Qcleanup_for_chart;
    Object Qgenerate_spot, Qgenerate_spot_for_chart;
    Object Qtype_of_frame_represented, Qabstract_type, Qimage_plane_spot;
    Object Qenclosing_spot_type, Qinnermost_spot_p, Qtype_description_of_type;
    Object Qchart_spot, Qreclaim_structure, Qoutstanding_chart_spot_count;
    Object Qchart_spot_structure_memory_usage, Qutilities2, string_constant_29;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_28, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_chart, Qinitialize;
    Object Qinitialize_for_chart, string_constant_27, string_constant_26;
    Object list_constant_34, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, Qitem;
    Object Qinitialize_the_transform, list_constant_33, Qcharts1, Kfuncall;
    Object Qassert_frame_notes_for_block, Qretract_frame_notes_for_block;
    Object string_constant_18;

    x_note_fn_call(177,270);
    SET_PACKAGE("AB");
    string_constant_18 = STATIC_STRING("CHART-DRAWING");
    if (Chart_drawing == UNBOUND)
	Chart_drawing = make_recursive_lock(2,Kname,string_constant_18);
    AB_package = STATIC_PACKAGE("AB");
    Qchart_drawing = STATIC_SYMBOL("CHART-DRAWING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_drawing,Chart_drawing);
    Qcharts = STATIC_SYMBOL("CHARTS",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qchart_drawing,Qcharts,
	    Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qchart_drawing,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qretract_frame_notes_for_block = 
	    STATIC_SYMBOL("RETRACT-FRAME-NOTES-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qretract_frame_notes_for_block,
	    STATIC_FUNCTION(retract_frame_notes_for_block,NIL,FALSE,1,1));
    Qretract_frame_notes = STATIC_SYMBOL("RETRACT-FRAME-NOTES",AB_package);
    temp = SYMBOL_FUNCTION(Qretract_frame_notes_for_block);
    set_get(Qblock,Qretract_frame_notes,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qretract_frame_notes),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qretract_frame_notes,temp,Qclasses_which_define);
    Qassert_frame_notes_for_block = 
	    STATIC_SYMBOL("ASSERT-FRAME-NOTES-FOR-BLOCK",AB_package);
    SET_SYMBOL_FUNCTION(Qassert_frame_notes_for_block,
	    STATIC_FUNCTION(assert_frame_notes_for_block,NIL,FALSE,1,1));
    Qassert_frame_notes = STATIC_SYMBOL("ASSERT-FRAME-NOTES",AB_package);
    temp = SYMBOL_FUNCTION(Qassert_frame_notes_for_block);
    set_get(Qblock,Qassert_frame_notes,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qassert_frame_notes),
	    Qclasses_which_define);
    temp = CONS(Qblock,temp_1);
    mutate_global_property(Qassert_frame_notes,temp,Qclasses_which_define);
    Qthe_transform = STATIC_SYMBOL("THE-TRANSFORM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthe_transform,The_transform);
    Qcharts1 = STATIC_SYMBOL("CHARTS1",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_the_transform = STATIC_SYMBOL("INITIALIZE-THE-TRANSFORM",
	    AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_the_transform);
    record_system_variable(Qthe_transform,Qcharts1,list_constant_33,Qnil,
	    Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_the_transform,
	    STATIC_FUNCTION(initialize_the_transform,NIL,FALSE,0,0));
    float_constant = STATIC_FLOAT(1.0);
    float_constant_1 = STATIC_FLOAT(0.0);
    Qchart_part_description_for_chart_style = 
	    STATIC_SYMBOL("CHART-PART-DESCRIPTION-FOR-CHART-STYLE",AB_package);
    Chart_part_description_for_chart_style_prop = 
	    Qchart_part_description_for_chart_style;
    Qchart = STATIC_SYMBOL("CHART",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qitem,Qblock);
    check_if_superior_classes_are_defined(Qchart,list_constant_34);
    string_constant_19 = STATIC_STRING("1l1m8v836dy");
    string_constant_20 = 
	    STATIC_STRING("1s4z8r83-Ey83-Ey836dy836dy03C+y001q1l8l1l8o1m8p01l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I think i");
    string_constant_21 = 
	    STATIC_STRING("ndividual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be supported");
    string_constant_22 = 
	    STATIC_STRING(". This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83Qsy83Qsy836dy836dy00001m1l8l1l8o0000");
    string_constant_23 = 
	    STATIC_STRING("04z8r83Twy83Twy836dy836dy01m1l833My1l83Hsy001n1l8l1l8o1l83Hy000004z8r83Hty83Hty836dy836dy00001n1l8l1l8o1l83Hy000004z8r83Iey83Iey");
    string_constant_24 = 
	    STATIC_STRING("836dy836dy00001m1l83Hy1l8l000004z8r837wy837wy836dy836dy00001o1m8p837wy1l8o1l8l1l8z000004z8r8385y8385y836dy836dy00001o1m8p83BUy1l");
    string_constant_25 = 
	    STATIC_STRING("8o1l8l1l8z000004z8r83Afy83Afy836dy836dy00001o1m8p83B6y1l8o1l8l1l8z00000");
    string_constant_26 = 
	    STATIC_STRING("1u8q1n836dy1m83Ry9k1m8v836dy1m83-Ey3C+y1o83Qsy08l8o1p83Twy1m1l833My1l83Hsy8l8o83Hy1p83Hty08l8o83Hy1o83Iey083Hy8l1q837wy01m8p837w");
    string_constant_27 = 
	    STATIC_STRING("y8o8l8z1q8385y01m8p83BUy8o8l8z1q83Afy01m8p83B6y8o8l8z");
    temp_1 = regenerate_optimized_constant(string_constant_19);
    temp_2 = regenerate_optimized_constant(list(6,string_constant_20,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qchart,list_constant_34,Nil,temp_1,Nil,
	    temp_2,list_constant_34,
	    regenerate_optimized_constant(LIST_2(string_constant_26,
	    string_constant_27)),Nil);
    Chart_class_description = 
	    lookup_global_or_kb_specific_property_value(Qchart,
	    Class_description_gkbprop);
    Default_chart_height = FIX((SI_Long)200L);
    Default_chart_width = FIX((SI_Long)300L);
    Qchart_style = STATIC_SYMBOL("CHART-STYLE",AB_package);
    Qline_chart_style = STATIC_SYMBOL("LINE-CHART-STYLE",AB_package);
    Qinitialize_for_chart = STATIC_SYMBOL("INITIALIZE-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_chart,
	    STATIC_FUNCTION(initialize_for_chart,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_for_chart);
    set_get(Qchart,Qinitialize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qinitialize,temp,Qclasses_which_define);
    Qstandardize_text_size_feature_in_part_description = 
	    STATIC_SYMBOL("STANDARDIZE-TEXT-SIZE-FEATURE-IN-PART-DESCRIPTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qstandardize_text_size_feature_in_part_description,
	    STATIC_FUNCTION(standardize_text_size_feature_in_part_description,
	    NIL,FALSE,1,1));
    Qcomputed_annotations = STATIC_SYMBOL("COMPUTED-ANNOTATIONS",AB_package);
    Qinitialize_after_reading_for_chart = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_chart,
	    STATIC_FUNCTION(initialize_after_reading_for_chart,NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qinitialize_after_reading_for_chart);
    set_get(Qchart,Qinitialize_after_reading,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qinitialize_after_reading,temp,
	    Qclasses_which_define);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_chart_spot_g2_struct = 
	    STATIC_SYMBOL("CHART-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qchart_spot = STATIC_SYMBOL("CHART-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_chart_spot_g2_struct,
	    Qchart_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qchart_spot,
	    Qg2_defstruct_structure_name_chart_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_chart_spot == UNBOUND)
	The_type_description_of_chart_spot = Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8m83fny1o83fny83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp_1 = The_type_description_of_chart_spot;
    The_type_description_of_chart_spot = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_28));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_chart_spot_g2_struct,
	    The_type_description_of_chart_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qchart_spot,The_type_description_of_chart_spot,
	    Qtype_description_of_type);
    Qoutstanding_chart_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-CHART-SPOT-COUNT",AB_package);
    Qchart_spot_structure_memory_usage = 
	    STATIC_SYMBOL("CHART-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_29 = STATIC_STRING("1q83fny8s83-MFy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_chart_spot_count);
    push_optimized_constant(Qchart_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_chart_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CHART-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_chart_spots,
	    Chain_of_available_chart_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_chart_spots,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qchart_spot_count = STATIC_SYMBOL("CHART-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_spot_count,Chart_spot_count);
    record_system_variable(Qchart_spot_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_chart_spots_vector == UNBOUND)
	Chain_of_available_chart_spots_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qchart_spot_structure_memory_usage,
	    STATIC_FUNCTION(chart_spot_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_chart_spot_count,
	    STATIC_FUNCTION(outstanding_chart_spot_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_chart_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_chart_spot,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qchart_spot,
	    reclaim_structure_for_chart_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qchart_spot),
	    Qtype_description_of_type);
    temp = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qchart),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp;
    Qgenerate_spot_for_chart = STATIC_SYMBOL("GENERATE-SPOT-FOR-CHART",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_chart,
	    STATIC_FUNCTION(generate_spot_for_chart,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp = SYMBOL_FUNCTION(Qgenerate_spot_for_chart);
    set_get(Qchart,Qgenerate_spot,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qgenerate_spot,temp,Qclasses_which_define);
    Qfix_up_color_feature_in_chart_part_description = 
	    STATIC_SYMBOL("FIX-UP-COLOR-FEATURE-IN-CHART-PART-DESCRIPTION",
	    AB_package);
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qline_color = STATIC_SYMBOL("LINE-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_up_color_feature_in_chart_part_description,
	    STATIC_FUNCTION(fix_up_color_feature_in_chart_part_description,
	    NIL,FALSE,1,1));
    Qdata_series = STATIC_SYMBOL("DATA-SERIES",AB_package);
    Qcleanup_for_chart = STATIC_SYMBOL("CLEANUP-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_chart,
	    STATIC_FUNCTION(cleanup_for_chart,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp = SYMBOL_FUNCTION(Qcleanup_for_chart);
    set_get(Qchart,Qcleanup,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qcleanup,temp,Qclasses_which_define);
    Qline_drawing_description_for_chart = 
	    STATIC_SYMBOL("LINE-DRAWING-DESCRIPTION-FOR-CHART",AB_package);
    Qreclaim_line_drawing_description_for_chart_value = 
	    STATIC_SYMBOL("RECLAIM-LINE-DRAWING-DESCRIPTION-FOR-CHART-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_line_drawing_description_for_chart_value,
	    STATIC_FUNCTION(reclaim_line_drawing_description_for_chart_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qline_drawing_description_for_chart,
	    SYMBOL_FUNCTION(Qreclaim_line_drawing_description_for_chart_value),
	    Qslot_value_reclaimer);
    string_constant_30 = STATIC_STRING("WORKING-ON-CHART");
    if (Working_on_chart == UNBOUND)
	Working_on_chart = make_recursive_lock(2,Kname,string_constant_30);
    Qworking_on_chart = STATIC_SYMBOL("WORKING-ON-CHART",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworking_on_chart,Working_on_chart);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qworking_on_chart,
	    Qcharts,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qworking_on_chart,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qgrid = STATIC_SYMBOL("GRID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgrid,Grid);
    string_constant_31 = STATIC_STRING("GRID");
    if (Grid == UNBOUND)
	Grid = make_recursive_lock(2,Kname,string_constant_31);
    Qparts = STATIC_SYMBOL("PARTS",AB_package);
    Qbasic_part = STATIC_SYMBOL("BASIC-PART",AB_package);
    list_constant_35 = STATIC_CONS(Qbasic_part,Qnil);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qgrid,Qparts,Nil,Qnil,
	    Qnil,list_constant_35,Nil);
    mutate_global_property(Qgrid,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qsymbol_standing_in_for_unbound = 
	    STATIC_SYMBOL("SYMBOL-STANDING-IN-FOR-UNBOUND",AB_package);
    if (Current_grid == UNBOUND)
	Current_grid = Qsymbol_standing_in_for_unbound;
    def_part_type_1(Qgrid,list_constant_35,Qnil);
    Qsubparts = STATIC_SYMBOL("SUBPARTS",AB_package);
    Qsubparts_collection = STATIC_SYMBOL("SUBPARTS-COLLECTION",AB_package);
    list_constant_38 = STATIC_CONS(Qsubparts_collection,Qnil);
    Qenter_part_feature_subparts = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-SUBPARTS",AB_package);
    Qexit_part_feature_subparts = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-SUBPARTS",AB_package);
    Qcall_handlers = STATIC_SYMBOL("CALL-HANDLERS",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_part_feature_subparts);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_part_feature_subparts);
    list_constant_39 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_36,list_constant_37);
    def_part_feature_1(Qgrid,Qsubparts,list_constant_38,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_39);
    Qsubpart_defaults = STATIC_SYMBOL("SUBPART-DEFAULTS",AB_package);
    Qenter_subpart_defaults = STATIC_SYMBOL("ENTER-SUBPART-DEFAULTS",
	    AB_package);
    Qexit_subpart_defaults = STATIC_SYMBOL("EXIT-SUBPART-DEFAULTS",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_defaults);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_defaults);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_40,list_constant_41);
    def_part_feature_1(Qgrid,Qsubpart_defaults,list_constant_38,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_42);
    Qsubpart_exceptions = STATIC_SYMBOL("SUBPART-EXCEPTIONS",AB_package);
    Qenter_subpart_exceptions = STATIC_SYMBOL("ENTER-SUBPART-EXCEPTIONS",
	    AB_package);
    Qexit_subpart_exceptions = STATIC_SYMBOL("EXIT-SUBPART-EXCEPTIONS",
	    AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_subpart_exceptions);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_subpart_exceptions);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_43,list_constant_44);
    def_part_feature_1(Qgrid,Qsubpart_exceptions,list_constant_38,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_45);
    if (Grid_color == UNBOUND)
	Grid_color = Qsymbol_standing_in_for_unbound;
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qgrid_color = STATIC_SYMBOL("GRID-COLOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgrid_color,Grid_color);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    Qenter_part_feature_grid_color = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-GRID-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_grid_color,
	    STATIC_FUNCTION(enter_part_feature_grid_color,NIL,FALSE,1,1));
    Qexit_part_feature_grid_color = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-GRID-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_grid_color,
	    STATIC_FUNCTION(exit_part_feature_grid_color,NIL,FALSE,0,0));
    Qspecial_variable = STATIC_SYMBOL("SPECIAL-VARIABLE",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qgrid_color);
    def_part_feature_1(Qgrid,Qgrid_color,Qcolor_or_metacolor,Qgrid_color,
	    Qt,SYMBOL_FUNCTION(Qenter_part_feature_grid_color),
	    SYMBOL_FUNCTION(Qexit_part_feature_grid_color),list_constant_46);
    if (Grid_visible == UNBOUND)
	Grid_visible = Qsymbol_standing_in_for_unbound;
    Qgrid_visible = STATIC_SYMBOL("GRID-VISIBLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgrid_visible,Grid_visible);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qenter_part_feature_grid_visible = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-GRID-VISIBLE",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_grid_visible,
	    STATIC_FUNCTION(enter_part_feature_grid_visible,NIL,FALSE,1,1));
    Qexit_part_feature_grid_visible = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-GRID-VISIBLE",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_grid_visible,
	    STATIC_FUNCTION(exit_part_feature_grid_visible,NIL,FALSE,0,0));
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qgrid_visible);
    def_part_feature_1(Qgrid,Qgrid_visible,Qboolean,Qgrid_visible,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_grid_visible),
	    SYMBOL_FUNCTION(Qexit_part_feature_grid_visible),list_constant_47);
    string_constant_32 = STATIC_STRING("CHART");
    if (Chart == UNBOUND)
	Chart = make_recursive_lock(2,Kname,string_constant_32);
    Qformatted_part = STATIC_SYMBOL("FORMATTED-PART",AB_package);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Qformatted_part,Qgrid,
	    list_constant_35);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qchart,Qparts,Nil,Qnil,
	    Qnil,list_constant_48,Nil);
    mutate_global_property(Qchart,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_chart == UNBOUND)
	Current_chart = Qsymbol_standing_in_for_unbound;
    Qincludes = STATIC_SYMBOL("INCLUDES",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qincludes,Qformatted_part,
	    Qgrid);
    Qchildren_part_types = STATIC_SYMBOL("CHILDREN-PART-TYPES",AB_package);
    Qaxis = STATIC_SYMBOL("AXIS",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)3L,Qchildren_part_types,Qaxis,
	    Qdata_series);
    Qother_descendant_part_types = 
	    STATIC_SYMBOL("OTHER-DESCENDANT-PART-TYPES",AB_package);
    Qchart_data_point = STATIC_SYMBOL("CHART-DATA-POINT",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)2L,
	    Qother_descendant_part_types,Qchart_data_point);
    Qhidden_features = STATIC_SYMBOL("HIDDEN-FEATURES",AB_package);
    Qtext_alignment = STATIC_SYMBOL("TEXT-ALIGNMENT",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)4L,Qhidden_features,
	    Qtext_alignment,Qheight,Qwidth);
    list_constant_53 = STATIC_LIST((SI_Long)4L,list_constant_49,
	    list_constant_50,list_constant_51,list_constant_52);
    def_part_type_1(Qchart,list_constant_48,list_constant_53);
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qaxis,Qdata_series);
    list_constant_55 = STATIC_CONS(Qsubparts_collection,list_constant_54);
    def_part_feature_1(Qchart,Qsubparts,list_constant_55,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_39);
    list_constant_56 = STATIC_CONS(Qchart_data_point,Qnil);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)4L,Qsubparts_collection,
	    Qaxis,Qdata_series,list_constant_56);
    def_part_feature_1(Qchart,Qsubpart_defaults,list_constant_57,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_42);
    def_part_feature_1(Qchart,Qsubpart_exceptions,list_constant_57,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_45);
    if (Chart_left == UNBOUND)
	Chart_left = Qsymbol_standing_in_for_unbound;
    Qchart_left = STATIC_SYMBOL("CHART-LEFT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_left,Chart_left);
    Qenter_part_feature_chart_left = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-LEFT",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_left,
	    STATIC_FUNCTION(enter_part_feature_chart_left,NIL,FALSE,1,1));
    Qexit_part_feature_chart_left = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-LEFT",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_left,
	    STATIC_FUNCTION(exit_part_feature_chart_left,NIL,FALSE,0,0));
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qchart_left);
    def_part_feature_1(Qchart,Qchart_left,Qfixnum,Qchart_left,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_left),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_left),list_constant_58);
    if (Chart_top == UNBOUND)
	Chart_top = Qsymbol_standing_in_for_unbound;
    Qchart_top = STATIC_SYMBOL("CHART-TOP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_top,Chart_top);
    Qenter_part_feature_chart_top = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TOP",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_top,
	    STATIC_FUNCTION(enter_part_feature_chart_top,NIL,FALSE,1,1));
    Qexit_part_feature_chart_top = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TOP",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_top,
	    STATIC_FUNCTION(exit_part_feature_chart_top,NIL,FALSE,0,0));
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qchart_top);
    def_part_feature_1(Qchart,Qchart_top,Qfixnum,Qchart_top,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_top),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_top),list_constant_59);
    if (Chart_right == UNBOUND)
	Chart_right = Qsymbol_standing_in_for_unbound;
    Qchart_right = STATIC_SYMBOL("CHART-RIGHT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_right,Chart_right);
    Qenter_part_feature_chart_right = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-RIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_right,
	    STATIC_FUNCTION(enter_part_feature_chart_right,NIL,FALSE,1,1));
    Qexit_part_feature_chart_right = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-RIGHT",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_right,
	    STATIC_FUNCTION(exit_part_feature_chart_right,NIL,FALSE,0,0));
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qchart_right);
    def_part_feature_1(Qchart,Qchart_right,Qfixnum,Qchart_right,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_right),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_right),list_constant_60);
    if (Chart_bottom == UNBOUND)
	Chart_bottom = Qsymbol_standing_in_for_unbound;
    Qchart_bottom = STATIC_SYMBOL("CHART-BOTTOM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_bottom,Chart_bottom);
    Qenter_part_feature_chart_bottom = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-BOTTOM",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_bottom,
	    STATIC_FUNCTION(enter_part_feature_chart_bottom,NIL,FALSE,1,1));
    Qexit_part_feature_chart_bottom = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-BOTTOM",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_bottom,
	    STATIC_FUNCTION(exit_part_feature_chart_bottom,NIL,FALSE,0,0));
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_bottom);
    def_part_feature_1(Qchart,Qchart_bottom,Qfixnum,Qchart_bottom,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_bottom),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_bottom),list_constant_61);
    if (Chart_right_margin == UNBOUND)
	Chart_right_margin = Qsymbol_standing_in_for_unbound;
    Qchart_right_margin = STATIC_SYMBOL("CHART-RIGHT-MARGIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_right_margin,Chart_right_margin);
    Qenter_part_feature_chart_right_margin = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-RIGHT-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_right_margin,
	    STATIC_FUNCTION(enter_part_feature_chart_right_margin,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_right_margin = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-RIGHT-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_right_margin,
	    STATIC_FUNCTION(exit_part_feature_chart_right_margin,NIL,FALSE,
	    0,0));
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_right_margin);
    def_part_feature_1(Qchart,Qchart_right_margin,Qfixnum,
	    Qchart_right_margin,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_right_margin),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_right_margin),
	    list_constant_62);
    if (Chart_top_margin == UNBOUND)
	Chart_top_margin = Qsymbol_standing_in_for_unbound;
    Qchart_top_margin = STATIC_SYMBOL("CHART-TOP-MARGIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_top_margin,Chart_top_margin);
    Qenter_part_feature_chart_top_margin = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TOP-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_top_margin,
	    STATIC_FUNCTION(enter_part_feature_chart_top_margin,NIL,FALSE,
	    1,1));
    Qexit_part_feature_chart_top_margin = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TOP-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_top_margin,
	    STATIC_FUNCTION(exit_part_feature_chart_top_margin,NIL,FALSE,0,0));
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_top_margin);
    def_part_feature_1(Qchart,Qchart_top_margin,Qfixnum,Qchart_top_margin,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_chart_top_margin),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_top_margin),
	    list_constant_63);
    if (Chart_left_margin == UNBOUND)
	Chart_left_margin = Qsymbol_standing_in_for_unbound;
    Qchart_left_margin = STATIC_SYMBOL("CHART-LEFT-MARGIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_left_margin,Chart_left_margin);
    Qenter_part_feature_chart_left_margin = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-LEFT-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_left_margin,
	    STATIC_FUNCTION(enter_part_feature_chart_left_margin,NIL,FALSE,
	    1,1));
    Qexit_part_feature_chart_left_margin = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-LEFT-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_left_margin,
	    STATIC_FUNCTION(exit_part_feature_chart_left_margin,NIL,FALSE,
	    0,0));
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_left_margin);
    def_part_feature_1(Qchart,Qchart_left_margin,Qfixnum,
	    Qchart_left_margin,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_left_margin),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_left_margin),
	    list_constant_64);
    if (Chart_bottom_margin == UNBOUND)
	Chart_bottom_margin = Qsymbol_standing_in_for_unbound;
    Qchart_bottom_margin = STATIC_SYMBOL("CHART-BOTTOM-MARGIN",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_bottom_margin,Chart_bottom_margin);
    Qenter_part_feature_chart_bottom_margin = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-BOTTOM-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_bottom_margin,
	    STATIC_FUNCTION(enter_part_feature_chart_bottom_margin,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_bottom_margin = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-BOTTOM-MARGIN",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_bottom_margin,
	    STATIC_FUNCTION(exit_part_feature_chart_bottom_margin,NIL,
	    FALSE,0,0));
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_bottom_margin);
    def_part_feature_1(Qchart,Qchart_bottom_margin,Qfixnum,
	    Qchart_bottom_margin,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_bottom_margin),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_bottom_margin),
	    list_constant_65);
    if (Chart_tuple_1_minimum == UNBOUND)
	Chart_tuple_1_minimum = Qsymbol_standing_in_for_unbound;
    Qchart_tuple_1_minimum = STATIC_SYMBOL("CHART-TUPLE-1-MINIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_tuple_1_minimum,Chart_tuple_1_minimum);
    Qtemporary_constant = STATIC_SYMBOL("TEMPORARY-CONSTANT",AB_package);
    Qenter_part_feature_chart_tuple_1_minimum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TUPLE-1-MINIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_1_minimum,
	    STATIC_FUNCTION(enter_part_feature_chart_tuple_1_minimum,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_tuple_1_minimum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TUPLE-1-MINIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_1_minimum,
	    STATIC_FUNCTION(exit_part_feature_chart_tuple_1_minimum,NIL,
	    FALSE,0,0));
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_tuple_1_minimum);
    def_part_feature_1(Qchart,Qchart_tuple_1_minimum,Qtemporary_constant,
	    Qchart_tuple_1_minimum,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_1_minimum),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_1_minimum),
	    list_constant_66);
    if (Chart_tuple_1_maximum == UNBOUND)
	Chart_tuple_1_maximum = Qsymbol_standing_in_for_unbound;
    Qchart_tuple_1_maximum = STATIC_SYMBOL("CHART-TUPLE-1-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_tuple_1_maximum,Chart_tuple_1_maximum);
    Qenter_part_feature_chart_tuple_1_maximum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TUPLE-1-MAXIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_1_maximum,
	    STATIC_FUNCTION(enter_part_feature_chart_tuple_1_maximum,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_tuple_1_maximum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TUPLE-1-MAXIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_1_maximum,
	    STATIC_FUNCTION(exit_part_feature_chart_tuple_1_maximum,NIL,
	    FALSE,0,0));
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_tuple_1_maximum);
    def_part_feature_1(Qchart,Qchart_tuple_1_maximum,Qtemporary_constant,
	    Qchart_tuple_1_maximum,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_1_maximum),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_1_maximum),
	    list_constant_67);
    if (Chart_tuple_2_minimum == UNBOUND)
	Chart_tuple_2_minimum = Qsymbol_standing_in_for_unbound;
    Qchart_tuple_2_minimum = STATIC_SYMBOL("CHART-TUPLE-2-MINIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_tuple_2_minimum,Chart_tuple_2_minimum);
    Qenter_part_feature_chart_tuple_2_minimum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TUPLE-2-MINIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_2_minimum,
	    STATIC_FUNCTION(enter_part_feature_chart_tuple_2_minimum,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_tuple_2_minimum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TUPLE-2-MINIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_2_minimum,
	    STATIC_FUNCTION(exit_part_feature_chart_tuple_2_minimum,NIL,
	    FALSE,0,0));
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_tuple_2_minimum);
    def_part_feature_1(Qchart,Qchart_tuple_2_minimum,Qtemporary_constant,
	    Qchart_tuple_2_minimum,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_2_minimum),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_2_minimum),
	    list_constant_68);
    if (Chart_tuple_2_maximum == UNBOUND)
	Chart_tuple_2_maximum = Qsymbol_standing_in_for_unbound;
    Qchart_tuple_2_maximum = STATIC_SYMBOL("CHART-TUPLE-2-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_tuple_2_maximum,Chart_tuple_2_maximum);
    Qenter_part_feature_chart_tuple_2_maximum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-TUPLE-2-MAXIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_2_maximum,
	    STATIC_FUNCTION(enter_part_feature_chart_tuple_2_maximum,NIL,
	    FALSE,1,1));
    Qexit_part_feature_chart_tuple_2_maximum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-TUPLE-2-MAXIMUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_2_maximum,
	    STATIC_FUNCTION(exit_part_feature_chart_tuple_2_maximum,NIL,
	    FALSE,0,0));
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_tuple_2_maximum);
    def_part_feature_1(Qchart,Qchart_tuple_2_maximum,Qtemporary_constant,
	    Qchart_tuple_2_maximum,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_tuple_2_maximum),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_tuple_2_maximum),
	    list_constant_69);
    if (Chart_origin_x == UNBOUND)
	Chart_origin_x = Qsymbol_standing_in_for_unbound;
    Qchart_origin_x = STATIC_SYMBOL("CHART-ORIGIN-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_origin_x,Chart_origin_x);
    Qenter_part_feature_chart_origin_x = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-ORIGIN-X",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_origin_x,
	    STATIC_FUNCTION(enter_part_feature_chart_origin_x,NIL,FALSE,1,1));
    Qexit_part_feature_chart_origin_x = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-ORIGIN-X",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_origin_x,
	    STATIC_FUNCTION(exit_part_feature_chart_origin_x,NIL,FALSE,0,0));
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_origin_x);
    def_part_feature_1(Qchart,Qchart_origin_x,Qfixnum,Qchart_origin_x,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_origin_x),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_origin_x),
	    list_constant_70);
    if (Chart_origin_y == UNBOUND)
	Chart_origin_y = Qsymbol_standing_in_for_unbound;
    Qchart_origin_y = STATIC_SYMBOL("CHART-ORIGIN-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchart_origin_y,Chart_origin_y);
    Qenter_part_feature_chart_origin_y = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-CHART-ORIGIN-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_chart_origin_y,
	    STATIC_FUNCTION(enter_part_feature_chart_origin_y,NIL,FALSE,1,1));
    Qexit_part_feature_chart_origin_y = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-CHART-ORIGIN-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_chart_origin_y,
	    STATIC_FUNCTION(exit_part_feature_chart_origin_y,NIL,FALSE,0,0));
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qchart_origin_y);
    def_part_feature_1(Qchart,Qchart_origin_y,Qfixnum,Qchart_origin_y,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_chart_origin_y),
	    SYMBOL_FUNCTION(Qexit_part_feature_chart_origin_y),
	    list_constant_71);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series,Data_series);
    string_constant_33 = STATIC_STRING("DATA-SERIES");
    if (Data_series == UNBOUND)
	Data_series = make_recursive_lock(2,Kname,string_constant_33);
    list_constant_72 = STATIC_CONS(Qformatted_part,list_constant_35);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qdata_series,Qparts,Nil,
	    Qnil,Qnil,list_constant_72,Nil);
    mutate_global_property(Qdata_series,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_data_series == UNBOUND)
	Current_data_series = Qsymbol_standing_in_for_unbound;
    list_constant_73 = STATIC_LIST((SI_Long)2L,Qincludes,Qformatted_part);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)3L,Qchildren_part_types,
	    Qaxis,list_constant_56);
    Qtext_size = STATIC_SYMBOL("TEXT-SIZE",AB_package);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    Qborder_color = STATIC_SYMBOL("BORDER-COLOR",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)8L,Qhidden_features,Qtext_size,
	    Qheight,Qwidth,Qtext_alignment,Qtext_color,Qborder_color,
	    Qbackground_color);
    list_constant_76 = STATIC_LIST((SI_Long)3L,list_constant_73,
	    list_constant_74,list_constant_75);
    def_part_type_1(Qdata_series,list_constant_72,list_constant_76);
    list_constant_77 = STATIC_CONS(Qaxis,list_constant_56);
    list_constant_78 = STATIC_CONS(Qsubparts_collection,list_constant_77);
    def_part_feature_1(Qdata_series,Qsubparts,list_constant_78,Qsubparts,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_39);
    def_part_feature_1(Qdata_series,Qsubpart_defaults,list_constant_78,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_42);
    def_part_feature_1(Qdata_series,Qsubpart_exceptions,list_constant_78,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_45);
    if (Data_series_index == UNBOUND)
	Data_series_index = Qsymbol_standing_in_for_unbound;
    Qdata_series_index = STATIC_SYMBOL("DATA-SERIES-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_index,Data_series_index);
    Qenter_part_feature_data_series_index = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_index,
	    STATIC_FUNCTION(enter_part_feature_data_series_index,NIL,FALSE,
	    1,1));
    Qexit_part_feature_data_series_index = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_index,
	    STATIC_FUNCTION(exit_part_feature_data_series_index,NIL,FALSE,
	    0,0));
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_index);
    def_part_feature_1(Qdata_series,Qdata_series_index,Qfixnum,
	    Qdata_series_index,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_index),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_index),
	    list_constant_79);
    if (Data_series_source_kind == UNBOUND)
	Data_series_source_kind = Qsymbol_standing_in_for_unbound;
    Qdata_series_source_kind = STATIC_SYMBOL("DATA-SERIES-SOURCE-KIND",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_source_kind,
	    Data_series_source_kind);
    Qenter_part_feature_data_series_source_kind = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-SOURCE-KIND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_source_kind,
	    STATIC_FUNCTION(enter_part_feature_data_series_source_kind,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_series_source_kind = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-SOURCE-KIND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_source_kind,
	    STATIC_FUNCTION(exit_part_feature_data_series_source_kind,NIL,
	    FALSE,0,0));
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_source_kind);
    def_part_feature_1(Qdata_series,Qdata_series_source_kind,Qsymbol,
	    Qdata_series_source_kind,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_source_kind),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_source_kind),
	    list_constant_80);
    if (Data_series_info_1 == UNBOUND)
	Data_series_info_1 = Qsymbol_standing_in_for_unbound;
    Qdata_series_info_1 = STATIC_SYMBOL("DATA-SERIES-INFO-1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_info_1,Data_series_info_1);
    Qenter_part_feature_data_series_info_1 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-INFO-1",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_info_1,
	    STATIC_FUNCTION(enter_part_feature_data_series_info_1,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_series_info_1 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-INFO-1",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_info_1,
	    STATIC_FUNCTION(exit_part_feature_data_series_info_1,NIL,FALSE,
	    0,0));
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_info_1);
    def_part_feature_1(Qdata_series,Qdata_series_info_1,Qt,
	    Qdata_series_info_1,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_info_1),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_info_1),
	    list_constant_81);
    if (Data_series_info_2 == UNBOUND)
	Data_series_info_2 = Qsymbol_standing_in_for_unbound;
    Qdata_series_info_2 = STATIC_SYMBOL("DATA-SERIES-INFO-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_info_2,Data_series_info_2);
    Qenter_part_feature_data_series_info_2 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-INFO-2",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_info_2,
	    STATIC_FUNCTION(enter_part_feature_data_series_info_2,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_series_info_2 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-INFO-2",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_info_2,
	    STATIC_FUNCTION(exit_part_feature_data_series_info_2,NIL,FALSE,
	    0,0));
    list_constant_82 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_info_2);
    def_part_feature_1(Qdata_series,Qdata_series_info_2,Qt,
	    Qdata_series_info_2,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_info_2),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_info_2),
	    list_constant_82);
    if (Data_series_failed_to_compile == UNBOUND)
	Data_series_failed_to_compile = Qsymbol_standing_in_for_unbound;
    Qdata_series_failed_to_compile = 
	    STATIC_SYMBOL("DATA-SERIES-FAILED-TO-COMPILE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_failed_to_compile,
	    Data_series_failed_to_compile);
    Qenter_part_feature_data_series_failed_to_compile = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-FAILED-TO-COMPILE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_failed_to_compile,
	    STATIC_FUNCTION(enter_part_feature_data_series_failed_to_compile,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_failed_to_compile = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-FAILED-TO-COMPILE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_failed_to_compile,
	    STATIC_FUNCTION(exit_part_feature_data_series_failed_to_compile,
	    NIL,FALSE,0,0));
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_failed_to_compile);
    def_part_feature_1(Qdata_series,Qdata_series_failed_to_compile,
	    Qboolean,Qdata_series_failed_to_compile,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_failed_to_compile),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_failed_to_compile),
	    list_constant_83);
    Qmanaged_float_array_qm = STATIC_SYMBOL("MANAGED-FLOAT-ARRAY\?",
	    AB_package);
    Qmanaged_float_array_qm_p = STATIC_SYMBOL("MANAGED-FLOAT-ARRAY\?-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmanaged_float_array_qm_p,
	    STATIC_FUNCTION(managed_float_array_qm_p,NIL,FALSE,1,1));
    list_constant_84 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qmanaged_float_array_qm_p);
    Qsimple_type_specification = STATIC_SYMBOL("SIMPLE-TYPE-SPECIFICATION",
	    AB_package);
    mutate_global_property(Qmanaged_float_array_qm,list_constant_84,
	    Qsimple_type_specification);
    if (Data_series_data_cache_1_qm == UNBOUND)
	Data_series_data_cache_1_qm = Qsymbol_standing_in_for_unbound;
    Qdata_series_data_cache_1_qm = 
	    STATIC_SYMBOL("DATA-SERIES-DATA-CACHE-1\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_data_cache_1_qm,
	    Data_series_data_cache_1_qm);
    Qenter_part_feature_data_series_data_cache_1_qm = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-DATA-CACHE-1\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_data_cache_1_qm,
	    STATIC_FUNCTION(enter_part_feature_data_series_data_cache_1_qm,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_data_cache_1_qm = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-DATA-CACHE-1\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_data_cache_1_qm,
	    STATIC_FUNCTION(exit_part_feature_data_series_data_cache_1_qm,
	    NIL,FALSE,0,0));
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_data_cache_1_qm);
    def_part_feature_1(Qdata_series,Qdata_series_data_cache_1_qm,
	    Qmanaged_float_array_qm,Qdata_series_data_cache_1_qm,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_data_cache_1_qm),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_data_cache_1_qm),
	    list_constant_85);
    if (Data_series_data_cache_2_qm == UNBOUND)
	Data_series_data_cache_2_qm = Qsymbol_standing_in_for_unbound;
    Qdata_series_data_cache_2_qm = 
	    STATIC_SYMBOL("DATA-SERIES-DATA-CACHE-2\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_data_cache_2_qm,
	    Data_series_data_cache_2_qm);
    Qenter_part_feature_data_series_data_cache_2_qm = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-DATA-CACHE-2\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_data_cache_2_qm,
	    STATIC_FUNCTION(enter_part_feature_data_series_data_cache_2_qm,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_data_cache_2_qm = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-DATA-CACHE-2\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_data_cache_2_qm,
	    STATIC_FUNCTION(exit_part_feature_data_series_data_cache_2_qm,
	    NIL,FALSE,0,0));
    list_constant_86 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_data_cache_2_qm);
    def_part_feature_1(Qdata_series,Qdata_series_data_cache_2_qm,
	    Qmanaged_float_array_qm,Qdata_series_data_cache_2_qm,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_data_cache_2_qm),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_data_cache_2_qm),
	    list_constant_86);
    if (Data_series_illustration_kind == UNBOUND)
	Data_series_illustration_kind = Qsymbol_standing_in_for_unbound;
    Qdata_series_illustration_kind = 
	    STATIC_SYMBOL("DATA-SERIES-ILLUSTRATION-KIND",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_illustration_kind,
	    Data_series_illustration_kind);
    Qenter_part_feature_data_series_illustration_kind = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-ILLUSTRATION-KIND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_illustration_kind,
	    STATIC_FUNCTION(enter_part_feature_data_series_illustration_kind,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_illustration_kind = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-ILLUSTRATION-KIND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_illustration_kind,
	    STATIC_FUNCTION(exit_part_feature_data_series_illustration_kind,
	    NIL,FALSE,0,0));
    list_constant_87 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_illustration_kind);
    def_part_feature_1(Qdata_series,Qdata_series_illustration_kind,Qsymbol,
	    Qdata_series_illustration_kind,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_illustration_kind),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_illustration_kind),
	    list_constant_87);
    if (Data_series_generator_info_1 == UNBOUND)
	Data_series_generator_info_1 = Qsymbol_standing_in_for_unbound;
    Qdata_series_generator_info_1 = 
	    STATIC_SYMBOL("DATA-SERIES-GENERATOR-INFO-1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_generator_info_1,
	    Data_series_generator_info_1);
    Qenter_part_feature_data_series_generator_info_1 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_generator_info_1,
	    STATIC_FUNCTION(enter_part_feature_data_series_generator_info_1,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_generator_info_1 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_generator_info_1,
	    STATIC_FUNCTION(exit_part_feature_data_series_generator_info_1,
	    NIL,FALSE,0,0));
    list_constant_88 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_generator_info_1);
    def_part_feature_1(Qdata_series,Qdata_series_generator_info_1,Qt,
	    Qdata_series_generator_info_1,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_generator_info_1),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_generator_info_1),
	    list_constant_88);
    if (Data_series_generator_info_2 == UNBOUND)
	Data_series_generator_info_2 = Qsymbol_standing_in_for_unbound;
    Qdata_series_generator_info_2 = 
	    STATIC_SYMBOL("DATA-SERIES-GENERATOR-INFO-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_generator_info_2,
	    Data_series_generator_info_2);
    Qenter_part_feature_data_series_generator_info_2 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_generator_info_2,
	    STATIC_FUNCTION(enter_part_feature_data_series_generator_info_2,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_generator_info_2 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-GENERATOR-INFO-2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_generator_info_2,
	    STATIC_FUNCTION(exit_part_feature_data_series_generator_info_2,
	    NIL,FALSE,0,0));
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_generator_info_2);
    def_part_feature_1(Qdata_series,Qdata_series_generator_info_2,Qt,
	    Qdata_series_generator_info_2,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_generator_info_2),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_generator_info_2),
	    list_constant_89);
    if (Data_series_connect_first_and_last_point == UNBOUND)
	Data_series_connect_first_and_last_point = 
		Qsymbol_standing_in_for_unbound;
    Qdata_series_connect_first_and_last_point = 
	    STATIC_SYMBOL("DATA-SERIES-CONNECT-FIRST-AND-LAST-POINT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_series_connect_first_and_last_point,
	    Data_series_connect_first_and_last_point);
    Qline_from_last_to_first_point_visible = 
	    STATIC_SYMBOL("LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE",AB_package);
    Qenter_part_feature_data_series_connect_first_and_last_point = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-SERIES-CONNECT-FIRST-AND-LAST-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_series_connect_first_and_last_point,
	    STATIC_FUNCTION(enter_part_feature_data_series_connect_first_and_last_point,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_series_connect_first_and_last_point = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-SERIES-CONNECT-FIRST-AND-LAST-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_series_connect_first_and_last_point,
	    STATIC_FUNCTION(exit_part_feature_data_series_connect_first_and_last_point,
	    NIL,FALSE,0,0));
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_series_connect_first_and_last_point);
    def_part_feature_1(Qdata_series,
	    Qdata_series_connect_first_and_last_point,Qboolean,
	    Qline_from_last_to_first_point_visible,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_series_connect_first_and_last_point),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_series_connect_first_and_last_point),
	    list_constant_90);
    SET_SYMBOL_VALUE_LOCATION(Qchart_data_point,Chart_data_point);
    string_constant_34 = STATIC_STRING("CHART-DATA-POINT");
    if (Chart_data_point == UNBOUND)
	Chart_data_point = make_recursive_lock(2,Kname,string_constant_34);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qchart_data_point,Qparts,
	    Nil,Qnil,Qnil,list_constant_72,Nil);
    mutate_global_property(Qchart_data_point,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_chart_data_point == UNBOUND)
	Current_chart_data_point = Qsymbol_standing_in_for_unbound;
    Quser_spelling = STATIC_SYMBOL("USER-SPELLING",AB_package);
    Qdata_point = STATIC_SYMBOL("DATA-POINT",AB_package);
    list_constant_91 = STATIC_LIST((SI_Long)2L,Quser_spelling,Qdata_point);
    Qallow_individual_exceptions_in_parents = 
	    STATIC_SYMBOL("ALLOW-INDIVIDUAL-EXCEPTIONS-IN-PARENTS",AB_package);
    list_constant_92 = STATIC_LIST((SI_Long)2L,
	    Qallow_individual_exceptions_in_parents,Qnil);
    Qborder_thickness = STATIC_SYMBOL("BORDER-THICKNESS",AB_package);
    Qtext_alginment = STATIC_SYMBOL("TEXT-ALGINMENT",AB_package);
    list_constant_93 = STATIC_LIST((SI_Long)7L,Qhidden_features,
	    Qborder_color,Qbackground_color,Qborder_thickness,
	    Qtext_alginment,Qtext_color,Qtext_size);
    list_constant_94 = STATIC_LIST((SI_Long)4L,list_constant_91,
	    list_constant_73,list_constant_92,list_constant_93);
    def_part_type_1(Qchart_data_point,list_constant_72,list_constant_94);
    def_part_feature_1(Qchart_data_point,Qsubparts,list_constant_38,
	    Qsubparts,Qnil,SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_39);
    def_part_feature_1(Qchart_data_point,Qsubpart_defaults,
	    list_constant_38,Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_42);
    def_part_feature_1(Qchart_data_point,Qsubpart_exceptions,
	    list_constant_38,Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_45);
    if (Data_point_index == UNBOUND)
	Data_point_index = Qsymbol_standing_in_for_unbound;
    Qdata_point_index = STATIC_SYMBOL("DATA-POINT-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_index,Data_point_index);
    Qenter_part_feature_data_point_index = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_index,
	    STATIC_FUNCTION(enter_part_feature_data_point_index,NIL,FALSE,
	    1,1));
    Qexit_part_feature_data_point_index = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_index,
	    STATIC_FUNCTION(exit_part_feature_data_point_index,NIL,FALSE,0,0));
    list_constant_95 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_index);
    def_part_feature_1(Qchart_data_point,Qdata_point_index,Qfixnum,
	    Qdata_point_index,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_index),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_index),
	    list_constant_95);
    if (Data_point_tuple_valid_qm == UNBOUND)
	Data_point_tuple_valid_qm = Qsymbol_standing_in_for_unbound;
    Qdata_point_tuple_valid_qm = STATIC_SYMBOL("DATA-POINT-TUPLE-VALID\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_tuple_valid_qm,
	    Data_point_tuple_valid_qm);
    Qenter_part_feature_data_point_tuple_valid_qm = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-TUPLE-VALID\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_valid_qm,
	    STATIC_FUNCTION(enter_part_feature_data_point_tuple_valid_qm,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_point_tuple_valid_qm = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-TUPLE-VALID\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_valid_qm,
	    STATIC_FUNCTION(exit_part_feature_data_point_tuple_valid_qm,
	    NIL,FALSE,0,0));
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_tuple_valid_qm);
    def_part_feature_1(Qchart_data_point,Qdata_point_tuple_valid_qm,
	    Qboolean,Qdata_point_tuple_valid_qm,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_valid_qm),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_valid_qm),
	    list_constant_96);
    if (Data_point_tuple_1 == UNBOUND)
	Data_point_tuple_1 = Qsymbol_standing_in_for_unbound;
    Qdata_point_tuple_1 = STATIC_SYMBOL("DATA-POINT-TUPLE-1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_tuple_1,Data_point_tuple_1);
    Qenter_part_feature_data_point_tuple_1 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-TUPLE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_1,
	    STATIC_FUNCTION(enter_part_feature_data_point_tuple_1,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_point_tuple_1 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-TUPLE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_1,
	    STATIC_FUNCTION(exit_part_feature_data_point_tuple_1,NIL,FALSE,
	    0,0));
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_tuple_1);
    def_part_feature_1(Qchart_data_point,Qdata_point_tuple_1,Qt,
	    Qdata_point_tuple_1,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_1),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_1),
	    list_constant_97);
    if (Data_point_tuple_2 == UNBOUND)
	Data_point_tuple_2 = Qsymbol_standing_in_for_unbound;
    Qdata_point_tuple_2 = STATIC_SYMBOL("DATA-POINT-TUPLE-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_tuple_2,Data_point_tuple_2);
    Qenter_part_feature_data_point_tuple_2 = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-TUPLE-2",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_2,
	    STATIC_FUNCTION(enter_part_feature_data_point_tuple_2,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_point_tuple_2 = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-TUPLE-2",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_2,
	    STATIC_FUNCTION(exit_part_feature_data_point_tuple_2,NIL,FALSE,
	    0,0));
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_tuple_2);
    def_part_feature_1(Qchart_data_point,Qdata_point_tuple_2,Qt,
	    Qdata_point_tuple_2,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_tuple_2),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_tuple_2),
	    list_constant_98);
    if (Data_point_x == UNBOUND)
	Data_point_x = Qsymbol_standing_in_for_unbound;
    Qdata_point_x = STATIC_SYMBOL("DATA-POINT-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_x,Data_point_x);
    Qenter_part_feature_data_point_x = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-X",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_x,
	    STATIC_FUNCTION(enter_part_feature_data_point_x,NIL,FALSE,1,1));
    Qexit_part_feature_data_point_x = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-X",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_x,
	    STATIC_FUNCTION(exit_part_feature_data_point_x,NIL,FALSE,0,0));
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_x);
    def_part_feature_1(Qchart_data_point,Qdata_point_x,Qt,Qdata_point_x,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_data_point_x),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_x),list_constant_99);
    if (Data_point_y == UNBOUND)
	Data_point_y = Qsymbol_standing_in_for_unbound;
    Qdata_point_y = STATIC_SYMBOL("DATA-POINT-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_y,Data_point_y);
    Qenter_part_feature_data_point_y = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_y,
	    STATIC_FUNCTION(enter_part_feature_data_point_y,NIL,FALSE,1,1));
    Qexit_part_feature_data_point_y = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_y,
	    STATIC_FUNCTION(exit_part_feature_data_point_y,NIL,FALSE,0,0));
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_y);
    def_part_feature_1(Qchart_data_point,Qdata_point_y,Qt,Qdata_point_y,
	    Qnil,SYMBOL_FUNCTION(Qenter_part_feature_data_point_y),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_y),
	    list_constant_100);
    if (Data_point_first_x == UNBOUND)
	Data_point_first_x = Qsymbol_standing_in_for_unbound;
    Qdata_point_first_x = STATIC_SYMBOL("DATA-POINT-FIRST-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_first_x,Data_point_first_x);
    Qenter_part_feature_data_point_first_x = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-FIRST-X",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_first_x,
	    STATIC_FUNCTION(enter_part_feature_data_point_first_x,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_point_first_x = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-FIRST-X",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_first_x,
	    STATIC_FUNCTION(exit_part_feature_data_point_first_x,NIL,FALSE,
	    0,0));
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_first_x);
    def_part_feature_1(Qchart_data_point,Qdata_point_first_x,Qt,
	    Qdata_point_first_x,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_first_x),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_first_x),
	    list_constant_101);
    if (Data_point_first_y == UNBOUND)
	Data_point_first_y = Qsymbol_standing_in_for_unbound;
    Qdata_point_first_y = STATIC_SYMBOL("DATA-POINT-FIRST-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_first_y,Data_point_first_y);
    Qenter_part_feature_data_point_first_y = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-FIRST-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_first_y,
	    STATIC_FUNCTION(enter_part_feature_data_point_first_y,NIL,
	    FALSE,1,1));
    Qexit_part_feature_data_point_first_y = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-FIRST-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_first_y,
	    STATIC_FUNCTION(exit_part_feature_data_point_first_y,NIL,FALSE,
	    0,0));
    list_constant_102 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_first_y);
    def_part_feature_1(Qchart_data_point,Qdata_point_first_y,Qt,
	    Qdata_point_first_y,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_first_y),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_first_y),
	    list_constant_102);
    if (Data_point_last_x == UNBOUND)
	Data_point_last_x = Qsymbol_standing_in_for_unbound;
    Qdata_point_last_x = STATIC_SYMBOL("DATA-POINT-LAST-X",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_last_x,Data_point_last_x);
    Qenter_part_feature_data_point_last_x = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-LAST-X",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_last_x,
	    STATIC_FUNCTION(enter_part_feature_data_point_last_x,NIL,FALSE,
	    1,1));
    Qexit_part_feature_data_point_last_x = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-LAST-X",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_last_x,
	    STATIC_FUNCTION(exit_part_feature_data_point_last_x,NIL,FALSE,
	    0,0));
    list_constant_103 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_last_x);
    def_part_feature_1(Qchart_data_point,Qdata_point_last_x,Qt,
	    Qdata_point_last_x,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_last_x),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_last_x),
	    list_constant_103);
    if (Data_point_last_y == UNBOUND)
	Data_point_last_y = Qsymbol_standing_in_for_unbound;
    Qdata_point_last_y = STATIC_SYMBOL("DATA-POINT-LAST-Y",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_last_y,Data_point_last_y);
    Qenter_part_feature_data_point_last_y = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-LAST-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_last_y,
	    STATIC_FUNCTION(enter_part_feature_data_point_last_y,NIL,FALSE,
	    1,1));
    Qexit_part_feature_data_point_last_y = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-LAST-Y",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_last_y,
	    STATIC_FUNCTION(exit_part_feature_data_point_last_y,NIL,FALSE,
	    0,0));
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_last_y);
    def_part_feature_1(Qchart_data_point,Qdata_point_last_y,Qt,
	    Qdata_point_last_y,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_last_y),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_last_y),
	    list_constant_104);
    Qdata_point_indicator = STATIC_SYMBOL("DATA-POINT-INDICATOR",AB_package);
    Qsquare = STATIC_SYMBOL("SQUARE",AB_package);
    Qrectangle = STATIC_SYMBOL("RECTANGLE",AB_package);
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    Qcross = STATIC_SYMBOL("CROSS",AB_package);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qcolumn = STATIC_SYMBOL("COLUMN",AB_package);
    Qbar = STATIC_SYMBOL("BAR",AB_package);
    Qsolid_column = STATIC_SYMBOL("SOLID-COLUMN",AB_package);
    Qsolid_bar = STATIC_SYMBOL("SOLID-BAR",AB_package);
    list_constant_105 = STATIC_LIST((SI_Long)10L,Qmember,Qsquare,
	    Qrectangle,Qtriangle,Qcross,Qx,Qcolumn,Qbar,Qsolid_column,
	    Qsolid_bar);
    mutate_global_property(Qdata_point_indicator,list_constant_105,
	    Qsimple_type_specification);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_indicator,Data_point_indicator);
    if (Data_point_indicator == UNBOUND)
	Data_point_indicator = Qsymbol_standing_in_for_unbound;
    Qindicator = STATIC_SYMBOL("INDICATOR",AB_package);
    Qenter_data_point_indicator = 
	    STATIC_SYMBOL("ENTER-DATA-POINT-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_data_point_indicator,
	    STATIC_FUNCTION(enter_data_point_indicator,NIL,FALSE,1,1));
    Qexit_data_point_indicator = STATIC_SYMBOL("EXIT-DATA-POINT-INDICATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_data_point_indicator,
	    STATIC_FUNCTION(exit_data_point_indicator,NIL,FALSE,0,0));
    list_constant_106 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qenter_data_point_indicator);
    list_constant_107 = STATIC_LIST((SI_Long)2L,Qfunction,
	    Qexit_data_point_indicator);
    list_constant_108 = STATIC_LIST((SI_Long)3L,Qcall_handlers,
	    list_constant_106,list_constant_107);
    def_part_feature_1(Qchart_data_point,Qdata_point_indicator,
	    Qdata_point_indicator,Qindicator,Qt,
	    SYMBOL_FUNCTION(Qenter_data_point_indicator),
	    SYMBOL_FUNCTION(Qexit_data_point_indicator),list_constant_108);
    if (Data_point_indicator_projection_function == UNBOUND)
	Data_point_indicator_projection_function = 
		Qsymbol_standing_in_for_unbound;
    Qdata_point_indicator_projection_function = 
	    STATIC_SYMBOL("DATA-POINT-INDICATOR-PROJECTION-FUNCTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_indicator_projection_function,
	    Data_point_indicator_projection_function);
    Qenter_part_feature_data_point_indicator_projection_function = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-INDICATOR-PROJECTION-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_indicator_projection_function,
	    STATIC_FUNCTION(enter_part_feature_data_point_indicator_projection_function,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_point_indicator_projection_function = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-INDICATOR-PROJECTION-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_indicator_projection_function,
	    STATIC_FUNCTION(exit_part_feature_data_point_indicator_projection_function,
	    NIL,FALSE,0,0));
    list_constant_109 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_indicator_projection_function);
    def_part_feature_1(Qchart_data_point,
	    Qdata_point_indicator_projection_function,Qt,
	    Qdata_point_indicator_projection_function,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_indicator_projection_function),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_indicator_projection_function),
	    list_constant_109);
    if (Data_point_show_indicator == UNBOUND)
	Data_point_show_indicator = Qsymbol_standing_in_for_unbound;
    Qdata_point_show_indicator = STATIC_SYMBOL("DATA-POINT-SHOW-INDICATOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_show_indicator,
	    Data_point_show_indicator);
    Qindicator_visible = STATIC_SYMBOL("INDICATOR-VISIBLE",AB_package);
    Qenter_part_feature_data_point_show_indicator = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-SHOW-INDICATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_show_indicator,
	    STATIC_FUNCTION(enter_part_feature_data_point_show_indicator,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_point_show_indicator = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-SHOW-INDICATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_show_indicator,
	    STATIC_FUNCTION(exit_part_feature_data_point_show_indicator,
	    NIL,FALSE,0,0));
    list_constant_110 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_show_indicator);
    def_part_feature_1(Qchart_data_point,Qdata_point_show_indicator,
	    Qboolean,Qindicator_visible,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_show_indicator),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_show_indicator),
	    list_constant_110);
    if (Data_point_show_connecting_line == UNBOUND)
	Data_point_show_connecting_line = Qsymbol_standing_in_for_unbound;
    Qdata_point_show_connecting_line = 
	    STATIC_SYMBOL("DATA-POINT-SHOW-CONNECTING-LINE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_point_show_connecting_line,
	    Data_point_show_connecting_line);
    Qconnection_line_visible = STATIC_SYMBOL("CONNECTION-LINE-VISIBLE",
	    AB_package);
    Qenter_part_feature_data_point_show_connecting_line = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-DATA-POINT-SHOW-CONNECTING-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_data_point_show_connecting_line,
	    STATIC_FUNCTION(enter_part_feature_data_point_show_connecting_line,
	    NIL,FALSE,1,1));
    Qexit_part_feature_data_point_show_connecting_line = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-DATA-POINT-SHOW-CONNECTING-LINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_data_point_show_connecting_line,
	    STATIC_FUNCTION(exit_part_feature_data_point_show_connecting_line,
	    NIL,FALSE,0,0));
    list_constant_111 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qdata_point_show_connecting_line);
    def_part_feature_1(Qchart_data_point,Qdata_point_show_connecting_line,
	    Qboolean,Qconnection_line_visible,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_data_point_show_connecting_line),
	    SYMBOL_FUNCTION(Qexit_part_feature_data_point_show_connecting_line),
	    list_constant_111);
    string_constant_35 = STATIC_STRING("AXIS");
    if (Axis == UNBOUND)
	Axis = make_recursive_lock(2,Kname,string_constant_35);
    list_constant_112 = STATIC_CONS(Qgrid,list_constant_35);
    list_constant_113 = STATIC_CONS(Qdata_series,list_constant_112);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qaxis,Qparts,Nil,Qnil,
	    Qnil,list_constant_113,Nil);
    mutate_global_property(Qaxis,named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_axis == UNBOUND)
	Current_axis = Qsymbol_standing_in_for_unbound;
    list_constant_114 = STATIC_CONS(Qgrid,Qnil);
    list_constant_117 = STATIC_LIST_STAR((SI_Long)3L,Qincludes,
	    Qdata_series,list_constant_114);
    list_constant_115 = STATIC_LIST((SI_Long)2L,Qborder_color,
	    Qbackground_color);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)5L,Qhidden_features,
	    Qheight,Qwidth,Qtext_alignment,list_constant_115);
    Qallow_defaulting_in_parents = 
	    STATIC_SYMBOL("ALLOW-DEFAULTING-IN-PARENTS",AB_package);
    list_constant_116 = STATIC_CONS(Qnil,Qnil);
    list_constant_119 = STATIC_CONS(Qallow_defaulting_in_parents,
	    list_constant_116);
    list_constant_120 = STATIC_LIST((SI_Long)4L,list_constant_74,
	    list_constant_117,list_constant_118,list_constant_119);
    def_part_type_1(Qaxis,list_constant_113,list_constant_120);
    def_part_feature_1(Qaxis,Qsubparts,list_constant_78,Qsubparts,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_subparts),
	    SYMBOL_FUNCTION(Qexit_part_feature_subparts),list_constant_39);
    def_part_feature_1(Qaxis,Qsubpart_defaults,list_constant_78,
	    Qsubpart_defaults,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_defaults),
	    SYMBOL_FUNCTION(Qexit_subpart_defaults),list_constant_42);
    def_part_feature_1(Qaxis,Qsubpart_exceptions,list_constant_78,
	    Qsubpart_exceptions,Qnil,
	    SYMBOL_FUNCTION(Qenter_subpart_exceptions),
	    SYMBOL_FUNCTION(Qexit_subpart_exceptions),list_constant_45);
    if (Axis_heading == UNBOUND)
	Axis_heading = Qsymbol_standing_in_for_unbound;
    Qaxis_heading = STATIC_SYMBOL("AXIS-HEADING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_heading,Axis_heading);
    Qenter_part_feature_axis_heading = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-HEADING",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_heading,
	    STATIC_FUNCTION(enter_part_feature_axis_heading,NIL,FALSE,1,1));
    Qexit_part_feature_axis_heading = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-HEADING",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_heading,
	    STATIC_FUNCTION(exit_part_feature_axis_heading,NIL,FALSE,0,0));
    list_constant_121 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_heading);
    def_part_feature_1(Qaxis,Qaxis_heading,Qsymbol,Qaxis_heading,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_heading),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_heading),
	    list_constant_121);
    if (Axis_index == UNBOUND)
	Axis_index = Qsymbol_standing_in_for_unbound;
    Qaxis_index = STATIC_SYMBOL("AXIS-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_index,Axis_index);
    Qenter_part_feature_axis_index = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_index,
	    STATIC_FUNCTION(enter_part_feature_axis_index,NIL,FALSE,1,1));
    Qexit_part_feature_axis_index = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-INDEX",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_index,
	    STATIC_FUNCTION(exit_part_feature_axis_index,NIL,FALSE,0,0));
    list_constant_122 = STATIC_LIST((SI_Long)2L,Qspecial_variable,Qaxis_index);
    def_part_feature_1(Qaxis,Qaxis_index,Qfixnum,Qaxis_index,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_index),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_index),list_constant_122);
    Qsimple_number = STATIC_SYMBOL("SIMPLE-NUMBER",AB_package);
    Qsimple_number_p = STATIC_SYMBOL("SIMPLE-NUMBER-P",AB_package);
    list_constant_123 = STATIC_LIST((SI_Long)2L,Qsatisfies,Qsimple_number_p);
    mutate_global_property(Qsimple_number,list_constant_123,
	    Qsimple_type_specification);
    SET_SYMBOL_FUNCTION(Qsimple_number_p,STATIC_FUNCTION(simple_number_p,
	    NIL,FALSE,1,1));
    string_constant = STATIC_STRING("~DL");
    string_constant_1 = STATIC_STRING("~D");
    Qsimple_number_type_writer = STATIC_SYMBOL("SIMPLE-NUMBER-TYPE-WRITER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsimple_number_type_writer,
	    STATIC_FUNCTION(simple_number_type_writer,NIL,FALSE,1,1));
    Qsimple_type_writer = STATIC_SYMBOL("SIMPLE-TYPE-WRITER",AB_package);
    mutate_global_property(Qsimple_number,Qsimple_number_type_writer,
	    Qsimple_type_writer);
    Qsimple_nonnegative_number = STATIC_SYMBOL("SIMPLE-NONNEGATIVE-NUMBER",
	    AB_package);
    Qsimple_nonnegative_number_p = 
	    STATIC_SYMBOL("SIMPLE-NONNEGATIVE-NUMBER-P",AB_package);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qsimple_nonnegative_number_p);
    mutate_global_property(Qsimple_nonnegative_number,list_constant_124,
	    Qsimple_type_specification);
    SET_SYMBOL_FUNCTION(Qsimple_nonnegative_number_p,
	    STATIC_FUNCTION(simple_nonnegative_number_p,NIL,FALSE,1,1));
    Qsimple_nonnegative_number_type_writer = 
	    STATIC_SYMBOL("SIMPLE-NONNEGATIVE-NUMBER-TYPE-WRITER",AB_package);
    SET_SYMBOL_FUNCTION(Qsimple_nonnegative_number_type_writer,
	    STATIC_FUNCTION(simple_nonnegative_number_type_writer,NIL,
	    FALSE,1,1));
    mutate_global_property(Qsimple_nonnegative_number,
	    Qsimple_nonnegative_number_type_writer,Qsimple_type_writer);
    string_constant_36 = STATIC_STRING("not a nonnegative number");
    Qtype_error_printer = STATIC_SYMBOL("TYPE-ERROR-PRINTER",AB_package);
    mutate_global_property(Qsimple_nonnegative_number,string_constant_36,
	    Qtype_error_printer);
    if (Axis_minimum == UNBOUND)
	Axis_minimum = Qsymbol_standing_in_for_unbound;
    Qaxis_minimum = STATIC_SYMBOL("AXIS-MINIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_minimum,Axis_minimum);
    Qenter_part_feature_axis_minimum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-MINIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_minimum,
	    STATIC_FUNCTION(enter_part_feature_axis_minimum,NIL,FALSE,1,1));
    Qexit_part_feature_axis_minimum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-MINIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_minimum,
	    STATIC_FUNCTION(exit_part_feature_axis_minimum,NIL,FALSE,0,0));
    list_constant_125 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_minimum);
    def_part_feature_1(Qaxis,Qaxis_minimum,Qsimple_number,Qaxis_minimum,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_minimum),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_minimum),
	    list_constant_125);
    if (Axis_crossover == UNBOUND)
	Axis_crossover = Qsymbol_standing_in_for_unbound;
    Qaxis_crossover = STATIC_SYMBOL("AXIS-CROSSOVER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_crossover,Axis_crossover);
    Qenter_part_feature_axis_crossover = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-CROSSOVER",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_crossover,
	    STATIC_FUNCTION(enter_part_feature_axis_crossover,NIL,FALSE,1,1));
    Qexit_part_feature_axis_crossover = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-CROSSOVER",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_crossover,
	    STATIC_FUNCTION(exit_part_feature_axis_crossover,NIL,FALSE,0,0));
    list_constant_126 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_crossover);
    def_part_feature_1(Qaxis,Qaxis_crossover,Qsimple_number,
	    Qaxis_crossover,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_crossover),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_crossover),
	    list_constant_126);
    if (Axis_maximum == UNBOUND)
	Axis_maximum = Qsymbol_standing_in_for_unbound;
    Qaxis_maximum = STATIC_SYMBOL("AXIS-MAXIMUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_maximum,Axis_maximum);
    Qenter_part_feature_axis_maximum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_maximum,
	    STATIC_FUNCTION(enter_part_feature_axis_maximum,NIL,FALSE,1,1));
    Qexit_part_feature_axis_maximum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-MAXIMUM",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_maximum,
	    STATIC_FUNCTION(exit_part_feature_axis_maximum,NIL,FALSE,0,0));
    list_constant_127 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_maximum);
    def_part_feature_1(Qaxis,Qaxis_maximum,Qsimple_number,Qaxis_maximum,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_maximum),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_maximum),
	    list_constant_127);
    if (Axis_tickmark_count == UNBOUND)
	Axis_tickmark_count = Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_count = STATIC_SYMBOL("AXIS-TICKMARK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_count,Axis_tickmark_count);
    Qnumber_of_tickmarks = STATIC_SYMBOL("NUMBER-OF-TICKMARKS",AB_package);
    Qenter_part_feature_axis_tickmark_count = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-COUNT",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_count,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_count,NIL,
	    FALSE,1,1));
    Qexit_part_feature_axis_tickmark_count = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-COUNT",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_count,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_count,NIL,
	    FALSE,0,0));
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_count);
    def_part_feature_1(Qaxis,Qaxis_tickmark_count,
	    Qsimple_nonnegative_number,Qnumber_of_tickmarks,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_count),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_count),
	    list_constant_128);
    if (Axis_tickmark_step == UNBOUND)
	Axis_tickmark_step = Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_step = STATIC_SYMBOL("AXIS-TICKMARK-STEP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_step,Axis_tickmark_step);
    Qtickmark_interval = STATIC_SYMBOL("TICKMARK-INTERVAL",AB_package);
    Qenter_part_feature_axis_tickmark_step = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-STEP",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_step,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_step,NIL,
	    FALSE,1,1));
    Qexit_part_feature_axis_tickmark_step = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-STEP",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_step,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_step,NIL,FALSE,
	    0,0));
    list_constant_129 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_step);
    def_part_feature_1(Qaxis,Qaxis_tickmark_step,Qsimple_number,
	    Qtickmark_interval,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_step),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_step),
	    list_constant_129);
    if (Axis_automatic == UNBOUND)
	Axis_automatic = Qsymbol_standing_in_for_unbound;
    Qaxis_automatic = STATIC_SYMBOL("AXIS-AUTOMATIC",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_automatic,Axis_automatic);
    Qenter_part_feature_axis_automatic = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-AUTOMATIC",AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_automatic,
	    STATIC_FUNCTION(enter_part_feature_axis_automatic,NIL,FALSE,1,1));
    Qexit_part_feature_axis_automatic = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-AUTOMATIC",AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_automatic,
	    STATIC_FUNCTION(exit_part_feature_axis_automatic,NIL,FALSE,0,0));
    list_constant_130 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_automatic);
    def_part_feature_1(Qaxis,Qaxis_automatic,Qboolean,Qaxis_automatic,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_automatic),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_automatic),
	    list_constant_130);
    if (Axis_tickmark_count_as_fixnum == UNBOUND)
	Axis_tickmark_count_as_fixnum = Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_count_as_fixnum = 
	    STATIC_SYMBOL("AXIS-TICKMARK-COUNT-AS-FIXNUM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_count_as_fixnum,
	    Axis_tickmark_count_as_fixnum);
    Qenter_part_feature_axis_tickmark_count_as_fixnum = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-COUNT-AS-FIXNUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_count_as_fixnum,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_count_as_fixnum,
	    NIL,FALSE,1,1));
    Qexit_part_feature_axis_tickmark_count_as_fixnum = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-COUNT-AS-FIXNUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_count_as_fixnum,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_count_as_fixnum,
	    NIL,FALSE,0,0));
    list_constant_131 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_count_as_fixnum);
    def_part_feature_1(Qaxis,Qaxis_tickmark_count_as_fixnum,Qfixnum,
	    Qaxis_tickmark_count_as_fixnum,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_count_as_fixnum),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_count_as_fixnum),
	    list_constant_131);
    if (Axis_tickmark_label_frequency == UNBOUND)
	Axis_tickmark_label_frequency = Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_label_frequency = 
	    STATIC_SYMBOL("AXIS-TICKMARK-LABEL-FREQUENCY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_label_frequency,
	    Axis_tickmark_label_frequency);
    Qenter_part_feature_axis_tickmark_label_frequency = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-FREQUENCY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_frequency,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_label_frequency,
	    NIL,FALSE,1,1));
    Qexit_part_feature_axis_tickmark_label_frequency = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-FREQUENCY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_frequency,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_label_frequency,
	    NIL,FALSE,0,0));
    list_constant_132 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_label_frequency);
    def_part_feature_1(Qaxis,Qaxis_tickmark_label_frequency,Qfixnum,
	    Qaxis_tickmark_label_frequency,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_frequency),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_frequency),
	    list_constant_132);
    if (Axis_tickmark_label_max_digits_before_point == UNBOUND)
	Axis_tickmark_label_max_digits_before_point = 
		Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_label_max_digits_before_point = 
	    STATIC_SYMBOL("AXIS-TICKMARK-LABEL-MAX-DIGITS-BEFORE-POINT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_label_max_digits_before_point,
	    Axis_tickmark_label_max_digits_before_point);
    Qenter_part_feature_axis_tickmark_label_max_digits_before_point = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-BEFORE-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_before_point,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_label_max_digits_before_point,
	    NIL,FALSE,1,1));
    Qexit_part_feature_axis_tickmark_label_max_digits_before_point = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-BEFORE-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_before_point,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_label_max_digits_before_point,
	    NIL,FALSE,0,0));
    list_constant_133 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_label_max_digits_before_point);
    def_part_feature_1(Qaxis,Qaxis_tickmark_label_max_digits_before_point,
	    Qfixnum,Qaxis_tickmark_label_max_digits_before_point,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_before_point),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_before_point),
	    list_constant_133);
    if (Axis_tickmark_label_max_digits_after_point == UNBOUND)
	Axis_tickmark_label_max_digits_after_point = 
		Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_label_max_digits_after_point = 
	    STATIC_SYMBOL("AXIS-TICKMARK-LABEL-MAX-DIGITS-AFTER-POINT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_label_max_digits_after_point,
	    Axis_tickmark_label_max_digits_after_point);
    Qenter_part_feature_axis_tickmark_label_max_digits_after_point = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-AFTER-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_after_point,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_label_max_digits_after_point,
	    NIL,FALSE,1,1));
    Qexit_part_feature_axis_tickmark_label_max_digits_after_point = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-AFTER-POINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_after_point,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_label_max_digits_after_point,
	    NIL,FALSE,0,0));
    list_constant_134 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_label_max_digits_after_point);
    def_part_feature_1(Qaxis,Qaxis_tickmark_label_max_digits_after_point,
	    Qfixnum,Qaxis_tickmark_label_max_digits_after_point,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_after_point),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_after_point),
	    list_constant_134);
    if (Axis_tickmark_label_max_digits_in_exponent == UNBOUND)
	Axis_tickmark_label_max_digits_in_exponent = 
		Qsymbol_standing_in_for_unbound;
    Qaxis_tickmark_label_max_digits_in_exponent = 
	    STATIC_SYMBOL("AXIS-TICKMARK-LABEL-MAX-DIGITS-IN-EXPONENT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaxis_tickmark_label_max_digits_in_exponent,
	    Axis_tickmark_label_max_digits_in_exponent);
    Qenter_part_feature_axis_tickmark_label_max_digits_in_exponent = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-IN-EXPONENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_in_exponent,
	    STATIC_FUNCTION(enter_part_feature_axis_tickmark_label_max_digits_in_exponent,
	    NIL,FALSE,1,1));
    Qexit_part_feature_axis_tickmark_label_max_digits_in_exponent = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-AXIS-TICKMARK-LABEL-MAX-DIGITS-IN-EXPONENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_in_exponent,
	    STATIC_FUNCTION(exit_part_feature_axis_tickmark_label_max_digits_in_exponent,
	    NIL,FALSE,0,0));
    list_constant_135 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qaxis_tickmark_label_max_digits_in_exponent);
    def_part_feature_1(Qaxis,Qaxis_tickmark_label_max_digits_in_exponent,
	    Qfixnum,Qaxis_tickmark_label_max_digits_in_exponent,Qnil,
	    SYMBOL_FUNCTION(Qenter_part_feature_axis_tickmark_label_max_digits_in_exponent),
	    SYMBOL_FUNCTION(Qexit_part_feature_axis_tickmark_label_max_digits_in_exponent),
	    list_constant_135);
    Qsimple_number_for_significant_digits = 
	    STATIC_SYMBOL("SIMPLE-NUMBER-FOR-SIGNIFICANT-DIGITS",AB_package);
    Qsimple_number_for_significant_digits_p = 
	    STATIC_SYMBOL("SIMPLE-NUMBER-FOR-SIGNIFICANT-DIGITS-P",AB_package);
    list_constant_136 = STATIC_LIST((SI_Long)2L,Qsatisfies,
	    Qsimple_number_for_significant_digits_p);
    mutate_global_property(Qsimple_number_for_significant_digits,
	    list_constant_136,Qsimple_type_specification);
    string_constant_37 = 
	    STATIC_STRING("not an integer equal to -1, or in the range 2 to 15");
    mutate_global_property(Qsimple_number_for_significant_digits,
	    string_constant_37,Qtype_error_printer);
    SET_SYMBOL_FUNCTION(Qsimple_number_for_significant_digits_p,
	    STATIC_FUNCTION(simple_number_for_significant_digits_p,NIL,
	    FALSE,1,1));
    if (Number_of_significant_digits == UNBOUND)
	Number_of_significant_digits = Qsymbol_standing_in_for_unbound;
    Qnumber_of_significant_digits = 
	    STATIC_SYMBOL("NUMBER-OF-SIGNIFICANT-DIGITS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnumber_of_significant_digits,
	    Number_of_significant_digits);
    Qenter_part_feature_number_of_significant_digits = 
	    STATIC_SYMBOL("ENTER-PART-FEATURE-NUMBER-OF-SIGNIFICANT-DIGITS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qenter_part_feature_number_of_significant_digits,
	    STATIC_FUNCTION(enter_part_feature_number_of_significant_digits,
	    NIL,FALSE,1,1));
    Qexit_part_feature_number_of_significant_digits = 
	    STATIC_SYMBOL("EXIT-PART-FEATURE-NUMBER-OF-SIGNIFICANT-DIGITS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexit_part_feature_number_of_significant_digits,
	    STATIC_FUNCTION(exit_part_feature_number_of_significant_digits,
	    NIL,FALSE,0,0));
    list_constant_137 = STATIC_LIST((SI_Long)2L,Qspecial_variable,
	    Qnumber_of_significant_digits);
    def_part_feature_1(Qaxis,Qnumber_of_significant_digits,
	    Qsimple_number_for_significant_digits,
	    Qnumber_of_significant_digits,Qt,
	    SYMBOL_FUNCTION(Qenter_part_feature_number_of_significant_digits),
	    SYMBOL_FUNCTION(Qexit_part_feature_number_of_significant_digits),
	    list_constant_137);
    float_constant_2 = STATIC_FLOAT(-7.0);
    float_constant_3 = STATIC_FLOAT(-1.0);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qone_g2_quantity_list = STATIC_SYMBOL("ONE-G2-QUANTITY-LIST",AB_package);
    Qpair_of_g2_quantity_lists = STATIC_SYMBOL("PAIR-OF-G2-QUANTITY-LISTS",
	    AB_package);
    float_constant_6 = STATIC_FLOAT(12.0);
    if (Tickmark_label_min_height == UNBOUND)
	Tickmark_label_min_height = float_constant_6;
    float_constant_7 = STATIC_FLOAT(8.0);
    if (Tickmark_label_char_width == UNBOUND)
	Tickmark_label_char_width = float_constant_7;
    if (Tickmark_label_min_width == UNBOUND) {
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(Tickmark_label_char_width);
	Tickmark_label_min_width = DOUBLE_TO_DOUBLE_FLOAT(6.0 * temp_3);
    }
    float_constant_4 = STATIC_FLOAT(2.0);
    Qeast = STATIC_SYMBOL("EAST",AB_package);
    Qnorth = STATIC_SYMBOL("NORTH",AB_package);
    list_constant_138 = STATIC_CONS(Qnumber_of_significant_digits,Qnil);
    list_constant = STATIC_LIST_STAR((SI_Long)7L,Qtext_color,Qline_color,
	    Qgrid_visible,Qgrid_color,Qborder_color,Qtext_size,
	    list_constant_138);
    Qaxis_series_open_generator = 
	    STATIC_SYMBOL("AXIS-SERIES-OPEN-GENERATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qaxis_series_open_generator,
	    STATIC_FUNCTION(axis_series_open_generator,NIL,FALSE,0,0));
    Qaxis_data_series = STATIC_SYMBOL("AXIS-DATA-SERIES",AB_package);
    Qdata_series_generator_open_method = 
	    STATIC_SYMBOL("DATA-SERIES-GENERATOR-OPEN-METHOD",AB_package);
    temp = SYMBOL_FUNCTION(Qaxis_series_open_generator);
    set_get(Qaxis_data_series,Qdata_series_generator_open_method,temp);
    Qaxis_series_next_tuple = STATIC_SYMBOL("AXIS-SERIES-NEXT-TUPLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qaxis_series_next_tuple,
	    STATIC_FUNCTION(axis_series_next_tuple,NIL,FALSE,0,0));
    Qdata_series_generator_next_tuple_method = 
	    STATIC_SYMBOL("DATA-SERIES-GENERATOR-NEXT-TUPLE-METHOD",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qaxis_series_next_tuple);
    set_get(Qaxis_data_series,Qdata_series_generator_next_tuple_method,temp);
    Qaxis_series_close_generator = 
	    STATIC_SYMBOL("AXIS-SERIES-CLOSE-GENERATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qaxis_series_close_generator,
	    STATIC_FUNCTION(axis_series_close_generator,NIL,FALSE,0,0));
    Qdata_series_generator_close_method = 
	    STATIC_SYMBOL("DATA-SERIES-GENERATOR-CLOSE-METHOD",AB_package);
    temp = SYMBOL_FUNCTION(Qaxis_series_close_generator);
    set_get(Qaxis_data_series,Qdata_series_generator_close_method,temp);
    Qsimple_scatter_plot = STATIC_SYMBOL("SIMPLE-SCATTER-PLOT",AB_package);
    Qaxis_tick_mark = STATIC_SYMBOL("AXIS-TICK-MARK",AB_package);
    list_constant_139 = STATIC_LIST((SI_Long)7L,Qchart_data_point,
	    Qdata_point_show_connecting_line,Qnil,
	    Qdata_point_show_indicator,Qt,Qdata_point_indicator,
	    Qaxis_tick_mark);
    list_constant_140 = STATIC_CONS(list_constant_139,Qnil);
    list_constant_141 = STATIC_LIST((SI_Long)2L,Qchart_data_point,
	    list_constant_140);
    list_constant_142 = STATIC_LIST((SI_Long)11L,Qdata_series,
	    Qdata_series_index,FIX((SI_Long)-1L),Qdata_series_source_kind,
	    Qaxis_data_series,Qdata_series_illustration_kind,
	    Qsimple_scatter_plot,Qdata_series_connect_first_and_last_point,
	    Qnil,Qsubpart_defaults,list_constant_141);
    Default_axis_data_series_instance = list_constant_142;
    Qmalformed_data_series_return_nil = 
	    STATIC_SYMBOL("MALFORMED-DATA-SERIES-RETURN-NIL",AB_package);
    SET_SYMBOL_FUNCTION(Qmalformed_data_series_return_nil,
	    STATIC_FUNCTION(malformed_data_series_return_nil,NIL,FALSE,0,0));
    Qmalformed_data_series = STATIC_SYMBOL("MALFORMED-DATA-SERIES",AB_package);
    temp = SYMBOL_FUNCTION(Qmalformed_data_series_return_nil);
    set_get(Qmalformed_data_series,Qdata_series_generator_open_method,temp);
    temp = SYMBOL_FUNCTION(Qmalformed_data_series_return_nil);
    set_get(Qmalformed_data_series,
	    Qdata_series_generator_next_tuple_method,temp);
    temp = SYMBOL_FUNCTION(Qmalformed_data_series_return_nil);
    set_get(Qmalformed_data_series,Qdata_series_generator_close_method,temp);
    Qfloat_and_float_from_data_caches_open_generator = 
	    STATIC_SYMBOL("FLOAT-AND-FLOAT-FROM-DATA-CACHES-OPEN-GENERATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_open_generator,
	    STATIC_FUNCTION(float_and_float_from_data_caches_open_generator,
	    NIL,FALSE,0,0));
    Qfloat_and_float_from_data_caches = 
	    STATIC_SYMBOL("FLOAT-AND-FLOAT-FROM-DATA-CACHES",AB_package);
    temp = SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_open_generator);
    set_get(Qfloat_and_float_from_data_caches,
	    Qdata_series_generator_open_method,temp);
    Qfloat_and_float_from_data_caches_next_tuple = 
	    STATIC_SYMBOL("FLOAT-AND-FLOAT-FROM-DATA-CACHES-NEXT-TUPLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_next_tuple,
	    STATIC_FUNCTION(float_and_float_from_data_caches_next_tuple,
	    NIL,FALSE,0,0));
    temp = SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_next_tuple);
    set_get(Qfloat_and_float_from_data_caches,
	    Qdata_series_generator_next_tuple_method,temp);
    Qfloat_and_float_from_data_caches_close_generator = 
	    STATIC_SYMBOL("FLOAT-AND-FLOAT-FROM-DATA-CACHES-CLOSE-GENERATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_close_generator,
	    STATIC_FUNCTION(float_and_float_from_data_caches_close_generator,
	    NIL,FALSE,0,0));
    temp = SYMBOL_FUNCTION(Qfloat_and_float_from_data_caches_close_generator);
    set_get(Qfloat_and_float_from_data_caches,
	    Qdata_series_generator_close_method,temp);
    Qdata_series_projection_method = 
	    STATIC_SYMBOL("DATA-SERIES-PROJECTION-METHOD",AB_package);
    Qsimple_scatter_plot_data_series_projection_method = 
	    STATIC_SYMBOL("SIMPLE-SCATTER-PLOT-DATA-SERIES-PROJECTION-METHOD",
	    AB_package);
    set_get(Qsimple_scatter_plot,Qdata_series_projection_method,
	    Qsimple_scatter_plot_data_series_projection_method);
    SET_SYMBOL_FUNCTION(Qsimple_scatter_plot_data_series_projection_method,
	    STATIC_FUNCTION(simple_scatter_plot_data_series_projection_method,
	    NIL,FALSE,0,0));
    Qchart_data_point_indicator = 
	    STATIC_SYMBOL("CHART-DATA-POINT-INDICATOR",AB_package);
    Chart_data_point_indicator_prop = Qchart_data_point_indicator;
    Qproject_rectangle_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-RECTANGLE-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_rectangle_chart_indicator,
	    STATIC_FUNCTION(project_rectangle_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qrectangle,
	    SYMBOL_FUNCTION(Qproject_rectangle_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_triangle_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-TRIANGLE-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_triangle_chart_indicator,
	    STATIC_FUNCTION(project_triangle_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qtriangle,
	    SYMBOL_FUNCTION(Qproject_triangle_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_square_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-SQUARE-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_square_chart_indicator,
	    STATIC_FUNCTION(project_square_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qsquare,
	    SYMBOL_FUNCTION(Qproject_square_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_cross_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-CROSS-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_cross_chart_indicator,
	    STATIC_FUNCTION(project_cross_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qcross,
	    SYMBOL_FUNCTION(Qproject_cross_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_x_chart_indicator = STATIC_SYMBOL("PROJECT-X-CHART-INDICATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qproject_x_chart_indicator,
	    STATIC_FUNCTION(project_x_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qx,SYMBOL_FUNCTION(Qproject_x_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_column_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-COLUMN-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_column_chart_indicator,
	    STATIC_FUNCTION(project_column_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qcolumn,
	    SYMBOL_FUNCTION(Qproject_column_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_bar_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-BAR-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_bar_chart_indicator,
	    STATIC_FUNCTION(project_bar_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qbar,
	    SYMBOL_FUNCTION(Qproject_bar_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_solid_column_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-SOLID-COLUMN-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_solid_column_chart_indicator,
	    STATIC_FUNCTION(project_solid_column_chart_indicator,NIL,FALSE,
	    0,0));
    mutate_global_property(Qsolid_column,
	    SYMBOL_FUNCTION(Qproject_solid_column_chart_indicator),
	    Qchart_data_point_indicator);
    Qproject_solid_bar_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-SOLID-BAR-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_solid_bar_chart_indicator,
	    STATIC_FUNCTION(project_solid_bar_chart_indicator,NIL,FALSE,0,0));
    mutate_global_property(Qsolid_bar,
	    SYMBOL_FUNCTION(Qproject_solid_bar_chart_indicator),
	    Qchart_data_point_indicator);
    if (Tick_mark_part_to_draw == UNBOUND)
	Tick_mark_part_to_draw = Nil;
    Qtick_mark = STATIC_SYMBOL("TICK-MARK",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qproject_axis_tick_mark_chart_indicator = 
	    STATIC_SYMBOL("PROJECT-AXIS-TICK-MARK-CHART-INDICATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qproject_axis_tick_mark_chart_indicator,
	    STATIC_FUNCTION(project_axis_tick_mark_chart_indicator,NIL,
	    FALSE,0,0));
    mutate_global_property(Qaxis_tick_mark,
	    SYMBOL_FUNCTION(Qproject_axis_tick_mark_chart_indicator),
	    Qchart_data_point_indicator);
    list_constant_143 = STATIC_LIST((SI_Long)3L,Qaxis,Qaxis_heading,Qeast);
    list_constant_144 = STATIC_LIST((SI_Long)3L,Qaxis,Qaxis_heading,Qnorth);
    list_constant_145 = STATIC_LIST((SI_Long)2L,list_constant_143,
	    list_constant_144);
    list_constant_150 = STATIC_LIST((SI_Long)2L,Qaxis,list_constant_145);
    list_constant_146 = STATIC_LIST((SI_Long)5L,Qdata_series,
	    Qdata_series_connect_first_and_last_point,Qnil,
	    Qdata_series_illustration_kind,Qsimple_scatter_plot);
    list_constant_148 = STATIC_CONS(list_constant_146,Qnil);
    list_constant_147 = STATIC_LIST((SI_Long)11L,Qchart_data_point,Qwidth,
	    FIX((SI_Long)5L),Qheight,FIX((SI_Long)5L),
	    Qdata_point_indicator,Qsquare,Qdata_point_show_indicator,Qnil,
	    Qdata_point_show_connecting_line,Qt);
    list_constant_149 = STATIC_CONS(list_constant_147,Qnil);
    list_constant_151 = STATIC_LIST((SI_Long)4L,Qdata_series,
	    list_constant_148,Qchart_data_point,list_constant_149);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    list_constant_152 = STATIC_LIST((SI_Long)21L,Qchart,Qsubparts,
	    list_constant_150,Qsubpart_defaults,list_constant_151,
	    Qchart_left_margin,FIX((SI_Long)50L),Qchart_top_margin,
	    FIX((SI_Long)10L),Qchart_right_margin,FIX((SI_Long)25L),
	    Qchart_bottom_margin,FIX((SI_Long)23L),Qline_color,Qblack,
	    Qbackground_color,Qwhite,Qtext_color,Qblack,Qtext_size,Qsmall);
    mutate_global_property(Qline_chart_style,list_constant_152,
	    Qchart_part_description_for_chart_style);
    Qscatter_chart_style = STATIC_SYMBOL("SCATTER-CHART-STYLE",AB_package);
    list_constant_153 = STATIC_LIST_STAR((SI_Long)11L,Qchart_data_point,
	    Qwidth,FIX((SI_Long)5L),Qheight,FIX((SI_Long)5L),
	    Qdata_point_indicator,Qsquare,Qdata_point_show_indicator,Qt,
	    Qdata_point_show_connecting_line,list_constant_116);
    list_constant_154 = STATIC_CONS(list_constant_153,Qnil);
    list_constant_155 = STATIC_LIST((SI_Long)4L,Qdata_series,
	    list_constant_148,Qchart_data_point,list_constant_154);
    list_constant_156 = STATIC_LIST((SI_Long)16L,Qchart_left_margin,
	    FIX((SI_Long)50L),Qchart_top_margin,FIX((SI_Long)10L),
	    Qchart_right_margin,FIX((SI_Long)25L),Qchart_bottom_margin,
	    FIX((SI_Long)23L),Qline_color,Qblack,Qbackground_color,Qwhite,
	    Qtext_color,Qblack,Qtext_size,Qsmall);
    list_constant_157 = STATIC_LIST_STAR((SI_Long)6L,Qchart,Qsubparts,
	    list_constant_150,Qsubpart_defaults,list_constant_155,
	    list_constant_156);
    mutate_global_property(Qscatter_chart_style,list_constant_157,
	    Qchart_part_description_for_chart_style);
    Qcolumn_chart_style = STATIC_SYMBOL("COLUMN-CHART-STYLE",AB_package);
    list_constant_158 = STATIC_LIST_STAR((SI_Long)4L,
	    Qdata_point_show_indicator,Qt,Qdata_point_show_connecting_line,
	    list_constant_116);
    list_constant_159 = STATIC_LIST_STAR((SI_Long)8L,Qchart_data_point,
	    Qwidth,FIX((SI_Long)7L),Qheight,FIX((SI_Long)4L),
	    Qdata_point_indicator,Qcolumn,list_constant_158);
    list_constant_160 = STATIC_CONS(list_constant_159,Qnil);
    list_constant_161 = STATIC_LIST((SI_Long)4L,Qdata_series,
	    list_constant_148,Qchart_data_point,list_constant_160);
    list_constant_162 = STATIC_LIST_STAR((SI_Long)6L,Qchart,Qsubparts,
	    list_constant_150,Qsubpart_defaults,list_constant_161,
	    list_constant_156);
    mutate_global_property(Qcolumn_chart_style,list_constant_162,
	    Qchart_part_description_for_chart_style);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qdynamic_text_cell_format = STATIC_SYMBOL("DYNAMIC-TEXT-CELL-FORMAT",
	    AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    list_constant_1 = STATIC_CONS(Qchart,Qnil);
    Qpolychrome_raster = STATIC_SYMBOL("POLYCHROME-RASTER",AB_package);
    Qmonochrome_raster_list = STATIC_SYMBOL("MONOCHROME-RASTER-LIST",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)5L,Qcolor,Qtext_color,
	    Qline_color,Qgrid_color,Qborder_color);
    string_constant_38 = STATIC_STRING("1l1m837wy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_38));
    Qwrite_chart_style_from_slot = 
	    STATIC_SYMBOL("WRITE-CHART-STYLE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_chart_style_from_slot,
	    STATIC_FUNCTION(write_chart_style_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qchart_style,
	    SYMBOL_FUNCTION(Qwrite_chart_style_from_slot),Qslot_value_writer);
    string_constant_2 = STATIC_STRING("~S is not a known style for a chart");
    Qcompile_chart_style_for_slot = 
	    STATIC_SYMBOL("COMPILE-CHART-STYLE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_chart_style_for_slot,
	    STATIC_FUNCTION(compile_chart_style_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qchart_style,
	    SYMBOL_FUNCTION(Qcompile_chart_style_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qchart_style,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_style),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_4 = STATIC_LIST((SI_Long)4L,Qmember,Qline_chart_style,
	    Qcolumn_chart_style,Qscatter_chart_style);
    define_type_specification_explicit_complex_type(Qchart_style,
	    list_constant_4);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_style);
    chart_style_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_style_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_style,
	    chart_style_evaluation_setter_1);
    chart_style_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_style_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_style,
	    chart_style_evaluation_getter_1);
    Qdata_series_descriptions = STATIC_SYMBOL("DATA-SERIES-DESCRIPTIONS",
	    AB_package);
    Qdata_series_description = STATIC_SYMBOL("DATA-SERIES-DESCRIPTION",
	    AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    add_grammar_rules_for_list(5,Qdata_series_descriptions,
	    Qdata_series_description,Qsc,Nil,Qnone);
    string_constant_39 = 
	    STATIC_STRING("1o1m83-Ply83-VPy1n83-VPy1o1m9k833Wy830By1m9k83-wUy830By1r8385y83-Ppy83-iBy83-Pmyo83-Pnym1m83-Ply83-Poy1n83-Poy1m1m9k833Wy830By1p");
    string_constant_40 = STATIC_STRING("8385y83-Ppy83-hgy83-Pmym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_39,
	    string_constant_40)));
    string_constant_3 = STATIC_STRING("plot ");
    string_constant_4 = STATIC_STRING(" versus ");
    string_constant_5 = STATIC_STRING(";~%");
    Qwrite_data_series_descriptions_from_slot = 
	    STATIC_SYMBOL("WRITE-DATA-SERIES-DESCRIPTIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_data_series_descriptions_from_slot,
	    STATIC_FUNCTION(write_data_series_descriptions_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qdata_series_descriptions,
	    SYMBOL_FUNCTION(Qwrite_data_series_descriptions_from_slot),
	    Qslot_value_writer);
    Qplot_designation_may_not_contain_local_names = 
	    STATIC_SYMBOL("PLOT-DESIGNATION-MAY-NOT-CONTAIN-LOCAL-NAMES",
	    AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_6 = 
	    STATIC_STRING("local names are not supported in data series.");
    write_plot_designation_may_not_contain_local_names_note_1 = 
	    STATIC_FUNCTION(write_plot_designation_may_not_contain_local_names_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qplot_designation_may_not_contain_local_names,
	    write_plot_designation_may_not_contain_local_names_note_1,
	    Qframe_note_writer_1);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    Qcompile_data_series_descriptions_for_slot = 
	    STATIC_SYMBOL("COMPILE-DATA-SERIES-DESCRIPTIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_data_series_descriptions_for_slot,
	    STATIC_FUNCTION(compile_data_series_descriptions_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qdata_series_descriptions,
	    SYMBOL_FUNCTION(Qcompile_data_series_descriptions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qdata_series_descriptions,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    note_text_category_evaluator_interface(Qdata_series_descriptions);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_28 = STATIC_CONS(Qno_item,Qnil);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,list_constant_28);
    set_property_value_function(get_symbol_properties_function(Qdata_series_descriptions),
	    Qtype_specification_simple_expansion,list_constant_6);
    define_type_specification_explicit_complex_type(Qdata_series_descriptions,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qdata_series_descriptions);
    list_constant_163 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_163,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    data_series_descriptions_evaluation_setter_1 = 
	    STATIC_FUNCTION(data_series_descriptions_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qdata_series_descriptions,
	    data_series_descriptions_evaluation_setter_1);
    string_constant_7 = STATIC_STRING("[deleted attribute]");
    data_series_descriptions_evaluation_getter_1 = 
	    STATIC_FUNCTION(data_series_descriptions_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qdata_series_descriptions,
	    data_series_descriptions_evaluation_getter_1);
    Qpart_type = STATIC_SYMBOL("PART-TYPE",AB_package);
    Qpart_feature = STATIC_SYMBOL("PART-FEATURE",AB_package);
    Qpart_type_description = STATIC_SYMBOL("PART-TYPE-DESCRIPTION",AB_package);
    Qchart_annotations = STATIC_SYMBOL("CHART-ANNOTATIONS",AB_package);
    Qchart_annotation = STATIC_SYMBOL("CHART-ANNOTATION",AB_package);
    add_grammar_rules_for_list(5,Qchart_annotations,Qchart_annotation,Qsc,
	    Nil,Qnone);
    string_constant_41 = STATIC_STRING("1m1m83-MEy83why1m83-MEy83-A-y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_41));
    Qreduce_annotation_1 = STATIC_SYMBOL("REDUCE-ANNOTATION-1",AB_package);
    SET_SYMBOL_FUNCTION(Qreduce_annotation_1,
	    STATIC_FUNCTION(reduce_annotation_1,NIL,FALSE,1,1));
    Qreduce_annotation = STATIC_SYMBOL("REDUCE-ANNOTATION",AB_package);
    string_constant_42 = 
	    STATIC_STRING("13Cy1o83why1n1m9k9l1m9k83Tvy83-N8y2lmn9m1o83why1n1m9k9l1m9k83biy83-N8y2lmn9m1o83why1n1m9k9l1m9k83Avy83-N8y2lmn9m1o83why1n1m9k9l1");
    string_constant_43 = 
	    STATIC_STRING("m9k83HHy83-N8y2lmn9m1o83why1n1m9k9l1m9k83-XEy83-N8y2lmn9m1o83why1o1m9k9l1m9k83--fy1m9k83*Iy832Uy1n83BSymo9n1n83-N8y1m1m9k83*Iy83");
    string_constant_44 = 
	    STATIC_STRING("*uy1m83BSym1n83-N8y1o1m9k83-Ty83fmy1m9k83*Iy83*uy1mmo1o83why1o1m9k9l1m9k83-Ehy1m9k83*Iy83-Eiy1n83BSymo9n1o83why1q1m9k9l1m9k83-Eh");
    string_constant_45 = 
	    STATIC_STRING("y1m9k83-Ty83fmy1m9k83*Iy83-Eiy1nomq9n1o83why1o1m9k9l1m9k83bcy1m9k83*Iy83niy1n83BSymo9n1o83why1q1m9k9l1m9k83bcy1m9k83-Ty83fmy1m9k");
    string_constant_46 = 
	    STATIC_STRING("83*Iy83niy1nomq9n1o83why1n1m9k9l1m9k83=sy83-RLy2lmn9m1o83why1n1m9k9l1m9k83*4y83-RLy2lmn9m1n83-RLy1m1m9k9o83-Hy1m83BSym1n83-RLy1o");
    string_constant_47 = STATIC_STRING("1m9k83-Ty83fmy1m9k9o83-Hy1mmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qreduce_annotation_1);
    push_optimized_constant(Qreduce_annotation);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47)));
    string_constant_48 = 
	    STATIC_STRING("13Iy1o83-A-y1q1m9k9l1m9k83-Ziy1m9k83-Ty83fmy1m9k83*Iy83-Zjy1nomq9m1m83-Zjy1m9k83Ygy1m83-Zjy1m9k83ly1m83-Zjy1m9k83amy1m83-Zjy1m9k");
    string_constant_49 = 
	    STATIC_STRING("83-PTy1m83-Zjy1m9k83-H6y1m83-Zjy1m9k83-N9y1m83-Zjy1m9k83-Kay1m83-Zjy1m9k83-qFy1m83-Zjy1m9k83-qEy1o83-A-y1n1m9k9l1m9k83-Zky83-Kuy");
    string_constant_50 = 
	    STATIC_STRING("2lmn9n1o83-A-y1n1m9k9l1m9k83-O2y83-Kuy2lmn9n1o83-A-y1n1m9k9l1m9k83-chy83-Kuy2lmn9n1n83-Kuy1o1m9k83-Ty83fmy1m9k83*Iy832Uy1mmo1o83");
    string_constant_51 = 
	    STATIC_STRING("-A-y1n1m9k9l1m9k83-KKy83-hFy2lmn9n1o83-A-y1n1m9k9l1m9k83-hCy83-hFy2lmn9n1o83-A-y1n1m9k9l1m9k83-KIy83-hFy2lmn9n1o83-A-y1n1m9k9l1m");
    string_constant_52 = 
	    STATIC_STRING("9k83-KJy83-hFy2lmn9n1o83-A-y1n1m9k9l1m9k83-hDy83-hFy2lmn9n1o83-A-y1n1m9k9l1m9k83-suy83-hFy2lmn9n1n83-hFy1o1m9k83-Ty83fmy1m9k9o83");
    string_constant_53 = 
	    STATIC_STRING("-Hy1mmo1o83-A-y1n1m9k9l1m9k83--fy83-Kuy2lmn9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qreduce_annotation);
    push_optimized_constant(Qreduce_annotation_1);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_48,string_constant_49,string_constant_50,
	    string_constant_51,string_constant_52,string_constant_53)));
    Qlookup_subpart_of_collection = 
	    STATIC_SYMBOL("LOOKUP-SUBPART-OF-COLLECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qlookup_subpart_of_collection,
	    STATIC_FUNCTION(lookup_subpart_of_collection,NIL,FALSE,4,4));
    Qget_internal_spelling = STATIC_SYMBOL("GET-INTERNAL-SPELLING",AB_package);
    Qfix_up_parse_upon_reduction = 
	    STATIC_SYMBOL("FIX-UP-PARSE-UPON-REDUCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_up_parse_upon_reduction,
	    STATIC_FUNCTION(fix_up_parse_upon_reduction,NIL,FALSE,1,1));
    string_constant_54 = 
	    STATIC_STRING("1p1o83fmy1o1m9k83=by83-iRy1m9k83-Ty83fmy1p9lo1m9k83-rNy1m9k1n9mm83-iRy09n1o83fmy1o83-iRy83-Hy1m9k83-Ty83fmy1p9lo1m9k83-rOy1m9k1n");
    string_constant_55 = 
	    STATIC_STRING("9ml83-iRym9n1o83fmy1m1m9k83=by83-iRy1p9l83BSy1m9k83-rNy1m9k1n9mm83-iRy09n1o83fmy1m83-iRy83Sy1p9l83BSy1m9k83-rOy1m9k1n9ml83-iRym9");
    string_constant_56 = STATIC_STRING("n1m83-iRy83-6y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qlookup_subpart_of_collection);
    push_optimized_constant(Qget_internal_spelling);
    push_optimized_constant(Qfix_up_parse_upon_reduction);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_54,
	    string_constant_55,string_constant_56)));
    Qcompile_chart_annotations_for_slot = 
	    STATIC_SYMBOL("COMPILE-CHART-ANNOTATIONS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_chart_annotations_for_slot,
	    STATIC_FUNCTION(compile_chart_annotations_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qchart_annotations,
	    SYMBOL_FUNCTION(Qcompile_chart_annotations_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qchart_annotations,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qwrite_chart_annotations_from_slot = 
	    STATIC_SYMBOL("WRITE-CHART-ANNOTATIONS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_chart_annotations_from_slot,
	    STATIC_FUNCTION(write_chart_annotations_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qchart_annotations,
	    SYMBOL_FUNCTION(Qwrite_chart_annotations_from_slot),
	    Qslot_value_writer);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qchart_features = STATIC_SYMBOL("CHART-FEATURES",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_29 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qchart_features),
	    Qtype_specification_simple_expansion,list_constant_29);
    list_constant_164 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    list_constant_165 = STATIC_CONS(list_constant_164,Qnil);
    list_constant_169 = STATIC_CONS(Qline_color,list_constant_165);
    list_constant_170 = STATIC_CONS(Qtext_color,list_constant_165);
    list_constant_171 = STATIC_CONS(Qbackground_color,list_constant_165);
    list_constant_172 = STATIC_CONS(Qborder_color,list_constant_165);
    list_constant_173 = STATIC_CONS(Qgrid_color,list_constant_165);
    list_constant_166 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_174 = STATIC_CONS(Qgrid_visible,list_constant_166);
    list_constant_167 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_175 = STATIC_CONS(Qtext_alignment,list_constant_167);
    list_constant_176 = STATIC_CONS(Qtext_size,list_constant_167);
    list_constant_168 = STATIC_CONS(Qnumber,Qnil);
    list_constant_177 = STATIC_CONS(Qwidth,list_constant_168);
    list_constant_178 = STATIC_CONS(Qheight,list_constant_168);
    list_constant_179 = STATIC_CONS(Qindicator,list_constant_167);
    list_constant_180 = STATIC_CONS(Qindicator_visible,list_constant_166);
    list_constant_181 = STATIC_CONS(Qconnection_line_visible,
	    list_constant_166);
    list_constant_182 = STATIC_CONS(Qline_from_last_to_first_point_visible,
	    list_constant_166);
    list_constant_183 = STATIC_CONS(Qaxis_minimum,list_constant_168);
    list_constant_184 = STATIC_CONS(Qaxis_maximum,list_constant_168);
    list_constant_185 = STATIC_CONS(Qaxis_crossover,list_constant_168);
    list_constant_186 = STATIC_CONS(Qnumber_of_tickmarks,list_constant_168);
    list_constant_187 = STATIC_CONS(Qtickmark_interval,list_constant_168);
    list_constant_188 = STATIC_CONS(Qnumber_of_significant_digits,
	    list_constant_168);
    list_constant_189 = STATIC_LIST((SI_Long)20L,list_constant_169,
	    list_constant_170,list_constant_171,list_constant_172,
	    list_constant_173,list_constant_174,list_constant_175,
	    list_constant_176,list_constant_177,list_constant_178,
	    list_constant_179,list_constant_180,list_constant_181,
	    list_constant_182,list_constant_183,list_constant_184,
	    list_constant_185,list_constant_186,list_constant_187,
	    list_constant_188);
    list_constant_190 = STATIC_LIST_STAR((SI_Long)21L,Qab_or,Qline_color,
	    Qtext_color,Qbackground_color,Qborder_color,Qgrid_color,
	    Qgrid_visible,Qtext_alignment,Qtext_size,Qwidth,Qheight,
	    Qindicator,Qindicator_visible,Qconnection_line_visible,
	    Qline_from_last_to_first_point_visible,Qaxis_minimum,
	    Qaxis_maximum,Qaxis_crossover,Qnumber_of_tickmarks,
	    Qtickmark_interval,list_constant_138);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_189,list_constant_190);
    define_type_specification_explicit_complex_type(Qchart_features,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_features);
    Qcopy_for_slot_value = STATIC_SYMBOL("COPY-FOR-SLOT-VALUE",AB_package);
    chart_features_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_features_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_features,
	    chart_features_evaluation_setter_1);
    chart_features_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_features_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_features,
	    chart_features_evaluation_getter_1);
    Qfeature_path = STATIC_SYMBOL("FEATURE-PATH",AB_package);
    list_constant_191 = STATIC_CONS(Qsequence,Qnil);
    set_property_value_function(get_symbol_properties_function(Qfeature_path),
	    Qtype_specification_simple_expansion,list_constant_191);
    Qpart_name = STATIC_SYMBOL("PART-NAME",AB_package);
    list_constant_192 = STATIC_LIST((SI_Long)4L,Qmember,Qchart_data_point,
	    Qdata_series,Qaxis);
    list_constant_193 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_192,list_constant_167);
    list_constant_194 = STATIC_LIST((SI_Long)2L,Qpart_name,list_constant_193);
    Qpart_index = STATIC_SYMBOL("PART-INDEX",AB_package);
    list_constant_195 = STATIC_CONS(Qpart_index,list_constant_168);
    list_constant_196 = STATIC_LIST((SI_Long)2L,list_constant_194,
	    list_constant_195);
    list_constant_197 = STATIC_LIST((SI_Long)2L,Qand,Qpart_name);
    list_constant_198 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_196,list_constant_197);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_198,
	    FIX((SI_Long)1L));
    define_type_specification_explicit_complex_type(Qfeature_path,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qfeature_path);
    Qcurrent_part_description = STATIC_SYMBOL("CURRENT-PART-DESCRIPTION",
	    AB_package);
    feature_path_evaluation_setter_1 = 
	    STATIC_FUNCTION(feature_path_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfeature_path,
	    feature_path_evaluation_setter_1);
    feature_path_evaluation_getter_1 = 
	    STATIC_FUNCTION(feature_path_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfeature_path,
	    feature_path_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qchart_annotation),
	    Qtype_specification_simple_expansion,list_constant_29);
    Qattributes = STATIC_SYMBOL("ATTRIBUTES",AB_package);
    list_constant_199 = STATIC_LIST((SI_Long)2L,Qattributes,list_constant_7);
    Qpath = STATIC_SYMBOL("PATH",AB_package);
    list_constant_200 = STATIC_LIST((SI_Long)2L,Qpath,list_constant_9);
    list_constant_201 = STATIC_LIST((SI_Long)2L,list_constant_199,
	    list_constant_200);
    list_constant_202 = STATIC_LIST((SI_Long)2L,Qand,Qattributes);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_201,list_constant_202);
    define_type_specification_explicit_complex_type(Qchart_annotation,
	    list_constant_12);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_annotation);
    chart_annotation_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_annotation_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_annotation,
	    chart_annotation_evaluation_setter_1);
    chart_annotation_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_annotation_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_annotation,
	    chart_annotation_evaluation_getter_1);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qset_simple_part_feature = STATIC_SYMBOL("SET-SIMPLE-PART-FEATURE",
	    AB_package);
    Qchart_annotations_sequence = 
	    STATIC_SYMBOL("CHART-ANNOTATIONS-SEQUENCE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_annotations_sequence),
	    Qtype_specification_simple_expansion,list_constant_191);
    list_constant_203 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_11,list_constant_203);
    define_type_specification_explicit_complex_type(Qchart_annotations_sequence,
	    list_constant_14);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_annotations_sequence);
    chart_annotations_sequence_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_annotations_sequence_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_annotations_sequence,
	    chart_annotations_sequence_evaluation_setter_1);
    chart_annotations_sequence_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_annotations_sequence_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_annotations_sequence,
	    chart_annotations_sequence_evaluation_getter_1);
    Qchart_data_point_features = STATIC_SYMBOL("CHART-DATA-POINT-FEATURES",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_data_point_features),
	    Qtype_specification_simple_expansion,list_constant_29);
    Qannotations = STATIC_SYMBOL("ANNOTATIONS",AB_package);
    list_constant_204 = STATIC_LIST((SI_Long)2L,Qannotations,list_constant_13);
    list_constant_205 = STATIC_CONS(list_constant_204,Qnil);
    list_constant_206 = STATIC_LIST((SI_Long)2L,Qand,Qannotations);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_205,list_constant_206);
    define_type_specification_explicit_complex_type(Qchart_data_point_features,
	    list_constant_16);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_data_point_features);
    chart_data_point_features_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_data_point_features_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_data_point_features,
	    chart_data_point_features_evaluation_setter_1);
    chart_data_point_features_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_data_point_features_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_data_point_features,
	    chart_data_point_features_evaluation_getter_1);
    Qchart_data_series_features = 
	    STATIC_SYMBOL("CHART-DATA-SERIES-FEATURES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_data_series_features),
	    Qtype_specification_simple_expansion,list_constant_29);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    list_constant_207 = STATIC_LIST((SI_Long)2L,Qindex,Qinteger);
    list_constant_208 = STATIC_CONS(list_constant_207,list_constant_205);
    list_constant_209 = STATIC_CONS(list_constant_206,Qnil);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_208,list_constant_209);
    define_type_specification_explicit_complex_type(Qchart_data_series_features,
	    list_constant_18);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_data_series_features);
    chart_data_series_features_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_data_series_features_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_data_series_features,
	    chart_data_series_features_evaluation_setter_1);
    chart_data_series_features_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_data_series_features_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_data_series_features,
	    chart_data_series_features_evaluation_getter_1);
    Qchart_axis_features = STATIC_SYMBOL("CHART-AXIS-FEATURES",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_axis_features),
	    Qtype_specification_simple_expansion,list_constant_29);
    define_type_specification_explicit_complex_type(Qchart_axis_features,
	    list_constant_18);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_axis_features);
    chart_axis_features_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_axis_features_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_axis_features,
	    chart_axis_features_evaluation_setter_1);
    chart_axis_features_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_axis_features_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_axis_features,
	    chart_axis_features_evaluation_getter_1);
    Qchart_data_point_features_sequence = 
	    STATIC_SYMBOL("CHART-DATA-POINT-FEATURES-SEQUENCE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_data_point_features_sequence),
	    Qtype_specification_simple_expansion,list_constant_191);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_15,list_constant_203);
    define_type_specification_explicit_complex_type(Qchart_data_point_features_sequence,
	    list_constant_21);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_data_point_features_sequence);
    chart_data_point_features_sequence_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_data_point_features_sequence_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_data_point_features_sequence,
	    chart_data_point_features_sequence_evaluation_setter_1);
    chart_data_point_features_sequence_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_data_point_features_sequence_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_data_point_features_sequence,
	    chart_data_point_features_sequence_evaluation_getter_1);
    Qchart_data_series_features_sequence = 
	    STATIC_SYMBOL("CHART-DATA-SERIES-FEATURES-SEQUENCE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_data_series_features_sequence),
	    Qtype_specification_simple_expansion,list_constant_191);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_17,list_constant_203);
    define_type_specification_explicit_complex_type(Qchart_data_series_features_sequence,
	    list_constant_23);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_data_series_features_sequence);
    chart_data_series_features_sequence_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_data_series_features_sequence_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_data_series_features_sequence,
	    chart_data_series_features_sequence_evaluation_setter_1);
    chart_data_series_features_sequence_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_data_series_features_sequence_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_data_series_features_sequence,
	    chart_data_series_features_sequence_evaluation_getter_1);
    Qchart_axis_features_sequence = 
	    STATIC_SYMBOL("CHART-AXIS-FEATURES-SEQUENCE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qchart_axis_features_sequence),
	    Qtype_specification_simple_expansion,list_constant_191);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_19,list_constant_203);
    define_type_specification_explicit_complex_type(Qchart_axis_features_sequence,
	    list_constant_25);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qchart_axis_features_sequence);
    chart_axis_features_sequence_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_axis_features_sequence_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_axis_features_sequence,
	    chart_axis_features_sequence_evaluation_setter_1);
    chart_axis_features_sequence_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_axis_features_sequence_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_axis_features_sequence,
	    chart_axis_features_sequence_evaluation_getter_1);
    list_constant_210 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_28,
	    list_constant_29);
    set_property_value_function(get_symbol_properties_function(Qchart_annotations),
	    Qtype_specification_simple_expansion,list_constant_210);
    Qdefault_features = STATIC_SYMBOL("DEFAULT-FEATURES",AB_package);
    list_constant_211 = STATIC_CONS(list_constant_7,Qnil);
    list_constant_212 = STATIC_CONS(Qdefault_features,list_constant_211);
    Qdata_point_features = STATIC_SYMBOL("DATA-POINT-FEATURES",AB_package);
    list_constant_213 = STATIC_LIST((SI_Long)2L,Qdata_point_features,
	    list_constant_20);
    Qdata_series_features = STATIC_SYMBOL("DATA-SERIES-FEATURES",AB_package);
    list_constant_214 = STATIC_LIST((SI_Long)2L,Qdata_series_features,
	    list_constant_22);
    Qaxis_features = STATIC_SYMBOL("AXIS-FEATURES",AB_package);
    list_constant_215 = STATIC_LIST((SI_Long)2L,Qaxis_features,
	    list_constant_24);
    list_constant_216 = STATIC_LIST((SI_Long)4L,list_constant_212,
	    list_constant_213,list_constant_214,list_constant_215);
    list_constant_217 = STATIC_LIST((SI_Long)5L,Qab_or,Qdefault_features,
	    Qdata_point_features,Qdata_series_features,Qaxis_features);
    list_constant_218 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_216,list_constant_217);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_28,
	    list_constant_218);
    define_type_specification_explicit_complex_type(Qchart_annotations,
	    list_constant_27);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,Qchart_annotations);
    string_constant_8 = STATIC_STRING("~NT ");
    string_constant_9 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    chart_annotations_evaluation_setter_1 = 
	    STATIC_FUNCTION(chart_annotations_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qchart_annotations,
	    chart_annotations_evaluation_setter_1);
    chart_annotations_evaluation_getter_1 = 
	    STATIC_FUNCTION(chart_annotations_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qchart_annotations,
	    chart_annotations_evaluation_getter_1);
    Qchart_axis_computed_details = 
	    STATIC_SYMBOL("CHART-AXIS-COMPUTED-DETAILS",AB_package);
    temp = CONS(Qchart_axis_computed_details,All_virtual_attributes);
    All_virtual_attributes = temp;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qchart),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qchart_axis_computed_details,temp_1);
    set_property_value_function(get_symbol_properties_function(Qchart),
	    Qvirtual_attributes_local_to_class,temp);
    Qaxis_1 = STATIC_SYMBOL("AXIS-1",AB_package);
    Qaxis_2 = STATIC_SYMBOL("AXIS-2",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_238 = STATIC_CONS(Qab_class,list_constant_1);
    Qaxis_is_discrete = STATIC_SYMBOL("AXIS-IS-DISCRETE",AB_package);
    list_constant_221 = STATIC_CONS(Qaxis_is_discrete,list_constant_166);
    Qmax_digits_in_exponent = STATIC_SYMBOL("MAX-DIGITS-IN-EXPONENT",
	    AB_package);
    list_constant_219 = STATIC_CONS(Qinteger,Qnil);
    list_constant_222 = STATIC_CONS(Qmax_digits_in_exponent,list_constant_219);
    Qmax_digits_before_point = STATIC_SYMBOL("MAX-DIGITS-BEFORE-POINT",
	    AB_package);
    list_constant_223 = STATIC_CONS(Qmax_digits_before_point,
	    list_constant_219);
    Qmax_digits_after_point = STATIC_SYMBOL("MAX-DIGITS-AFTER-POINT",
	    AB_package);
    list_constant_224 = STATIC_CONS(Qmax_digits_after_point,list_constant_219);
    list_constant_225 = STATIC_CONS(Qaxis_heading,list_constant_167);
    list_constant_220 = STATIC_CONS(Qfloat,Qnil);
    list_constant_226 = STATIC_CONS(Qaxis_crossover,list_constant_220);
    Qminimum = STATIC_SYMBOL("MINIMUM",AB_package);
    list_constant_227 = STATIC_CONS(Qminimum,list_constant_220);
    Qmaximum = STATIC_SYMBOL("MAXIMUM",AB_package);
    list_constant_228 = STATIC_CONS(Qmaximum,list_constant_220);
    list_constant_229 = STATIC_LIST((SI_Long)8L,list_constant_221,
	    list_constant_222,list_constant_223,list_constant_224,
	    list_constant_225,list_constant_226,list_constant_227,
	    list_constant_228);
    list_constant_230 = STATIC_LIST((SI_Long)3L,Qand,Qminimum,Qmaximum);
    list_constant_231 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_229,list_constant_230);
    list_constant_232 = STATIC_CONS(list_constant_231,Qnil);
    list_constant_233 = STATIC_CONS(Qaxis_1,list_constant_232);
    list_constant_234 = STATIC_CONS(Qaxis_2,list_constant_232);
    list_constant_235 = STATIC_LIST((SI_Long)2L,list_constant_233,
	    list_constant_234);
    list_constant_236 = STATIC_LIST((SI_Long)3L,Qand,Qaxis_1,Qaxis_2);
    list_constant_237 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_235,list_constant_236);
    list_constant_239 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_28,
	    list_constant_237);
    Qinitial_chart_axis_computed_details = 
	    STATIC_SYMBOL("INITIAL-CHART-AXIS-COMPUTED-DETAILS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_chart_axis_computed_details,
	    STATIC_FUNCTION(initial_chart_axis_computed_details,NIL,FALSE,
	    1,1));
    Qget_chart_axis_computed_details = 
	    STATIC_SYMBOL("GET-CHART-AXIS-COMPUTED-DETAILS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_chart_axis_computed_details,
	    STATIC_FUNCTION(get_chart_axis_computed_details,NIL,FALSE,1,1));
    add_virtual_attribute(Qchart_axis_computed_details,list_constant_238,
	    list_constant_239,Qnil,
	    SYMBOL_FUNCTION(Qinitial_chart_axis_computed_details),
	    SYMBOL_FUNCTION(Qget_chart_axis_computed_details),Nil);
    Qchart_data_series = STATIC_SYMBOL("CHART-DATA-SERIES",AB_package);
    temp = CONS(Qchart_data_series,All_virtual_attributes);
    All_virtual_attributes = temp;
    temp_1 = get_property_value_function(3,
	    get_symbol_properties_function(Qchart),
	    Qvirtual_attributes_local_to_class,Nil);
    temp = CONS(Qchart_data_series,temp_1);
    set_property_value_function(get_symbol_properties_function(Qchart),
	    Qvirtual_attributes_local_to_class,temp);
    Qdata_series_cache_1 = STATIC_SYMBOL("DATA-SERIES-CACHE-1",AB_package);
    list_constant_240 = STATIC_CONS(FIX((SI_Long)0L),Qnil);
    list_constant_241 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qfloat,
	    list_constant_240);
    list_constant_242 = STATIC_CONS(list_constant_241,Qnil);
    list_constant_244 = STATIC_CONS(Qdata_series_cache_1,list_constant_242);
    Qdata_series_cache_2 = STATIC_SYMBOL("DATA-SERIES-CACHE-2",AB_package);
    list_constant_245 = STATIC_CONS(Qdata_series_cache_2,list_constant_242);
    list_constant_243 = STATIC_LIST((SI_Long)4L,Qmember,Qaxis_data_series,
	    Qmalformed_data_series,Qfloat_and_float_from_data_caches);
    list_constant_246 = STATIC_LIST((SI_Long)2L,Qdata_series_source_kind,
	    list_constant_243);
    list_constant_248 = STATIC_LIST((SI_Long)3L,list_constant_244,
	    list_constant_245,list_constant_246);
    list_constant_247 = STATIC_CONS(Qdata_series_source_kind,Qnil);
    list_constant_249 = STATIC_LIST_STAR((SI_Long)4L,Qand,
	    Qdata_series_cache_1,Qdata_series_cache_2,list_constant_247);
    list_constant_250 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_248,list_constant_249);
    list_constant_251 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_250,list_constant_240);
    list_constant_252 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_28,
	    list_constant_251);
    Kevent_updates = STATIC_SYMBOL("EVENT-UPDATES",Pkeyword);
    Kwithin_putter = STATIC_SYMBOL("WITHIN-PUTTER",Pkeyword);
    list_constant_253 = STATIC_LIST((SI_Long)2L,Kevent_updates,Kwithin_putter);
    Qinitial_chart_data_series = STATIC_SYMBOL("INITIAL-CHART-DATA-SERIES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_chart_data_series,
	    STATIC_FUNCTION(initial_chart_data_series,NIL,FALSE,1,1));
    Qget_chart_data_series = STATIC_SYMBOL("GET-CHART-DATA-SERIES",AB_package);
    SET_SYMBOL_FUNCTION(Qget_chart_data_series,
	    STATIC_FUNCTION(get_chart_data_series,NIL,FALSE,1,1));
    add_virtual_attribute(Qchart_data_series,list_constant_238,
	    list_constant_252,list_constant_253,
	    SYMBOL_FUNCTION(Qinitial_chart_data_series),
	    SYMBOL_FUNCTION(Qget_chart_data_series),Nil);
    Qdraw_for_chart = STATIC_SYMBOL("DRAW-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_chart,STATIC_FUNCTION(draw_for_chart,NIL,
	    FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp = SYMBOL_FUNCTION(Qdraw_for_chart);
    set_get(Qchart,Qdraw,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qdraw,temp,Qclasses_which_define);
    Qupdate_chart = STATIC_SYMBOL("UPDATE-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_chart,STATIC_FUNCTION(update_chart,NIL,
	    FALSE,1,1));
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    list_constant_30 = STATIC_CONS(Qaxis,Qnil);
    Qhm14 = STATIC_SYMBOL("HM14",AB_package);
    Qab_font = STATIC_SYMBOL("AB-FONT",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)45L),
	    FIX((SI_Long)43L));
    float_constant_5 = STATIC_FLOAT(10.0);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_10 = 
	    STATIC_STRING("the designation, i.e. \"~ND\", did not denote anything.");
    string_constant_11 = 
	    STATIC_STRING("the designation, i.e. \"~ND\", denoted the ~(~a~) ~NV.  A quantity-list or quantity-array was needed.");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    string_constant_12 = 
	    STATIC_STRING("the designation, i.e. \"~ND\", denoted the ~(~a~) ~NF.  A quantity-list or quantity-array was needed.");
    Qelement_iterator = STATIC_SYMBOL("ELEMENT-ITERATOR",AB_package);
    list_constant_32 = STATIC_CONS(Qelement_iterator,list_constant_168);
    string_constant_13 = STATIC_STRING("");
    string_constant_14 = STATIC_STRING("s");
    string_constant_15 = 
	    STATIC_STRING("the designation, i.e. \"~ND\", denoted a data-series containing ~A NaN~A ~\n\t\t\t     (IEEE floating-point Not a Number value~A)");
    string_constant_16 = STATIC_STRING("a");
    Qput_chart_style = STATIC_SYMBOL("PUT-CHART-STYLE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_chart_style,STATIC_FUNCTION(put_chart_style,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qchart_style,SYMBOL_FUNCTION(Qput_chart_style),
	    Qslot_putter);
    Qput_data_series = STATIC_SYMBOL("PUT-DATA-SERIES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_series,STATIC_FUNCTION(put_data_series,
	    NIL,FALSE,3,3));
    mutate_global_property(Qdata_series,SYMBOL_FUNCTION(Qput_data_series),
	    Qslot_putter);
    Qput_annotations = STATIC_SYMBOL("PUT-ANNOTATIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_annotations,STATIC_FUNCTION(put_annotations,
	    NIL,FALSE,3,3));
    mutate_global_property(Qannotations,SYMBOL_FUNCTION(Qput_annotations),
	    Qslot_putter);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qactivate_for_chart = STATIC_SYMBOL("ACTIVATE-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_chart,
	    STATIC_FUNCTION(activate_for_chart,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp = SYMBOL_FUNCTION(Qactivate_for_chart);
    set_get(Qchart,Qactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qactivate,temp,Qclasses_which_define);
    Qdeactivate_for_chart = STATIC_SYMBOL("DEACTIVATE-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_chart,
	    STATIC_FUNCTION(deactivate_for_chart,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp = SYMBOL_FUNCTION(Qdeactivate_for_chart);
    set_get(Qchart,Qdeactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qdeactivate,temp,Qclasses_which_define);
    Qpatch_instance_chart_note = STATIC_SYMBOL("PATCH-INSTANCE-CHART-NOTE",
	    AB_package);
    write_patch_instance_chart_note_note_1 = 
	    STATIC_FUNCTION(write_patch_instance_chart_note_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qpatch_instance_chart_note,
	    write_patch_instance_chart_note_note_1,Qframe_note_writer_1);
    Qno_data_series_chart_note = STATIC_SYMBOL("NO-DATA-SERIES-CHART-NOTE",
	    AB_package);
    string_constant_17 = 
	    STATIC_STRING("the chart will appear empty until some data series are specified");
    write_no_data_series_chart_note_note_1 = 
	    STATIC_FUNCTION(write_no_data_series_chart_note_note,NIL,FALSE,
	    2,2);
    mutate_global_property(Qno_data_series_chart_note,
	    write_no_data_series_chart_note_note_1,Qframe_note_writer_1);
    Qretract_frame_notes_for_chart = 
	    STATIC_SYMBOL("RETRACT-FRAME-NOTES-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qretract_frame_notes_for_chart,
	    STATIC_FUNCTION(retract_frame_notes_for_chart,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qretract_frame_notes_for_chart);
    set_get(Qchart,Qretract_frame_notes,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qretract_frame_notes),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qretract_frame_notes,temp,Qclasses_which_define);
    Qassert_frame_notes_for_chart = 
	    STATIC_SYMBOL("ASSERT-FRAME-NOTES-FOR-CHART",AB_package);
    SET_SYMBOL_FUNCTION(Qassert_frame_notes_for_chart,
	    STATIC_FUNCTION(assert_frame_notes_for_chart,NIL,FALSE,1,1));
    temp = SYMBOL_FUNCTION(Qassert_frame_notes_for_chart);
    set_get(Qchart,Qassert_frame_notes,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qassert_frame_notes),
	    Qclasses_which_define);
    temp = CONS(Qchart,temp_1);
    mutate_global_property(Qassert_frame_notes,temp,Qclasses_which_define);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
}
