/* grphs1.c
 * Input file:  graphs1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "grphs1.h"


DEFINE_VARIABLE_WITH_SYMBOL(Current_plot, Qcurrent_plot);

DEFINE_VARIABLE_WITH_SYMBOL(Low_and_high_values_specified_for_vertical_axis_qm, Qlow_and_high_values_specified_for_vertical_axis_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Scale_y_data_points_qm, Qscale_y_data_points_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Current_graph_grid, Qcurrent_graph_grid);

DEFINE_VARIABLE_WITH_SYMBOL(Current_data_buffer_for_plot, Qcurrent_data_buffer_for_plot);

DEFINE_VARIABLE_WITH_SYMBOL(Current_plot_number, Qcurrent_plot_number);

DEFINE_VARIABLE_WITH_SYMBOL(Low_value_for_horizontal_axis, Qlow_value_for_horizontal_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Many_more_data_points_than_pixels_qm, Qmany_more_data_points_than_pixels_qm);

DEFINE_VARIABLE_WITH_SYMBOL(History_time_to_evaluate_display_expression_with, Qhistory_time_to_evaluate_display_expression_with);

DEFINE_VARIABLE_WITH_SYMBOL(Ring_buffer_for_history_time, Qring_buffer_for_history_time);

DEFINE_VARIABLE_WITH_SYMBOL(Current_cascaded_ring_buffer, Qcurrent_cascaded_ring_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_extremum_maximum_for_pixel_p, Qmost_recent_extremum_maximum_for_pixel_p);

DEFINE_VARIABLE_WITH_SYMBOL(Index_for_stop_time, Qindex_for_stop_time);

DEFINE_VARIABLE_WITH_SYMBOL(Most_recent_extremum_maximum_p, Qmost_recent_extremum_maximum_p);

DEFINE_VARIABLE_WITH_SYMBOL(X_data_min_set_qm, Qx_data_min_set_qm);

DEFINE_VARIABLE_WITH_SYMBOL(X_value_on_graph, Qx_value_on_graph);

DEFINE_VARIABLE_WITH_SYMBOL(Interval_between_plot_markers, Qinterval_between_plot_markers);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_marker_qm, Qplot_marker_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_and_maximum_y_value_set_qm, Qminimum_and_maximum_y_value_set_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_minimum_y_value, Qfixnum_minimum_y_value);

DEFINE_VARIABLE_WITH_SYMBOL(Fixnum_maximum_y_value, Qfixnum_maximum_y_value);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_min_and_max_qm, Qplot_min_and_max_qm);

DEFINE_VARIABLE_WITH_SYMBOL(History_time_per_pixel, Qhistory_time_per_pixel);

DEFINE_VARIABLE_WITH_SYMBOL(Last_history_time_for_data_point_on_pixel, Qlast_history_time_for_data_point_on_pixel);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_y_value_for_pixel, Qminimum_y_value_for_pixel);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_y_value_for_pixel, Qmaximum_y_value_for_pixel);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_y_value, Qminimum_y_value);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_y_value, Qmaximum_y_value);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_min_qm, Qplot_min_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_max_qm, Qplot_max_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Vertical_axis_range, Qvertical_axis_range);

DEFINE_VARIABLE_WITH_SYMBOL(Low_value_for_vertical_axis, Qlow_value_for_vertical_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Handy_float_1, Qhandy_float_1);

/* INITIALIZE-TO-MANAGED-FLOAT-BOX */
Object initialize_to_managed_float_box()
{
    x_note_fn_call(172,0);
    return allocate_managed_float_box();
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_duration_for_data_point, Qdefault_duration_for_data_point);

Object Default_graph_left_margin_width = UNBOUND;

Object Default_graph_right_margin_width = UNBOUND;

Object Default_data_point_y_size = UNBOUND;

Object Erase_zone_ratio = UNBOUND;

Object Minimum_range_to_maximum_value_ratio = UNBOUND;

Object Default_axis_half_range = UNBOUND;

Object Default_interval_between_vertical_grid_lines = UNBOUND;

Object Default_number_of_vertical_grid_lines = UNBOUND;

Object Maximum_number_of_horizontal_grid_lines = UNBOUND;

Object Default_number_of_markers = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Redraw_as_well_as_reformat_p, Qredraw_as_well_as_reformat_p);

/* SPOT-GENERATOR-FOR-TABLE-FORMAT-FOR-GRAPHS */
Object spot_generator_for_table_format_for_graphs(table_for_graph,
	    mouse_pointer)
    Object table_for_graph, mouse_pointer;
{
    Object input_table_spot, table_cell_qm, tightness;

    x_note_fn_call(172,1);
    input_table_spot = make_graph_table_spot_1();
    fill_out_table_spot(input_table_spot,table_for_graph,mouse_pointer);
    table_cell_qm = ISVREF(input_table_spot,(SI_Long)18L);
    tightness = ISVREF(input_table_spot,(SI_Long)6L);
    if (CONSP(table_cell_qm) && IFIX(tightness) < (SI_Long)100L)
	generate_spot_for_input_table(table_for_graph,mouse_pointer,
		input_table_spot);
    else
	push_last_spot(mouse_pointer,input_table_spot,table_for_graph);
    return VALUES_1(Nil);
}

/* MAKE-GRAPH-NOT-UP-TO-DATE */
Object make_graph_not_up_to_date(graph_grid)
    Object graph_grid;
{
    x_note_fn_call(172,2);
    reclaim_graph_list_1(ISVREF(graph_grid,(SI_Long)53L));
    ISVREF(graph_grid,(SI_Long)52L) = Nil;
    return VALUES_1(ISVREF(graph_grid,(SI_Long)53L) = Nil);
}

static Object Qitem_reference;     /* item-reference */

static Object Qgraph_reformatted_since_start_qm;  /* graph-reformatted-since-start? */

static Object Qtrend_chart;        /* trend-chart */

/* REMOVE-GRAPH-RENDERING-FROM-GRAPH-GRID */
Object remove_graph_rendering_from_graph_grid(graph_rendering,
	    graph_grid_or_chart)
    Object graph_rendering, graph_grid_or_chart;
{
    Object item_or_value, gensymed_symbol, sub_class_bit_vector;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_1, svref_arg_2, graph;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(172,3);
    item_or_value = ISVREF(graph_rendering,(SI_Long)20L);
    if (CONSP(item_or_value) && EQ(M_CDR(item_or_value),Qitem_reference) ? 
	    TRUEP(ISVREF(M_CAR(item_or_value),(SI_Long)3L)) : 
	    TRUEP(item_or_value)) {
	gensymed_symbol = ISVREF(graph_grid_or_chart,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Graph_grid_class_description,(SI_Long)18L));
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
	    gensymed_symbol = graph_rendering;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = ISVREF(graph_grid_or_chart,(SI_Long)42L);
	  next_loop:
	    if ( !TRUEP(gensymed_symbol_5))
		goto end_loop;
	    if (EQ(CAR(gensymed_symbol_5),gensymed_symbol)) {
		if (gensymed_symbol_4) {
		    temp_1 = CDR(gensymed_symbol_5);
		    M_CDR(gensymed_symbol_4) = temp_1;
		}
		else {
		    temp_1 = CDR(gensymed_symbol_5);
		    ISVREF(graph_grid_or_chart,(SI_Long)42L) = temp_1;
		}
		inline_note_reclaim_cons(gensymed_symbol_5,Qeval);
		if (ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = ISVREF(Available_eval_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = gensymed_symbol_5;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = gensymed_symbol_5;
		}
		else {
		    temp_1 = Available_eval_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = gensymed_symbol_5;
		    temp_1 = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = gensymed_symbol_5;
		}
		M_CDR(gensymed_symbol_5) = Nil;
		goto end_1;
	    }
	    gensymed_symbol_4 = gensymed_symbol_5;
	    gensymed_symbol_5 = CDR(gensymed_symbol_5);
	    goto next_loop;
	  end_loop:
	  end_1:;
	    if ( !(printing_p() && printing_window_p(Current_window))) {
		make_graph_not_up_to_date(graph_grid_or_chart);
		gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid_or_chart,
			(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		graph = gensymed_symbol;
		if (graph)
		    return set_non_savable_lookup_slot_value(graph,
			    Qgraph_reformatted_since_start_qm,Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Chart_class_description,(SI_Long)18L));
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
		return remove_graph_rendering_from_chart(graph_rendering,
			graph_grid_or_chart);
	    else {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(Qtrend_chart,
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
		    return remove_graph_rendering_from_trend_chart(graph_rendering,
			    graph_grid_or_chart);
		else
		    return VALUES_1(Qnil);
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

/* DECACHE-AND-REMOVE-ALL-GRAPH-RENDERINGS-FROM-GRAPH-GRID */
Object decache_and_remove_all_graph_renderings_from_graph_grid(graph_grid)
    Object graph_grid;
{
    Object gensymed_symbol, graph;

    x_note_fn_call(172,4);
    decache_all_graph_renderings_of_graph_grid(graph_grid);
    reclaim_eval_list_1(ISVREF(graph_grid,(SI_Long)42L));
    ISVREF(graph_grid,(SI_Long)42L) = Nil;
    make_graph_not_up_to_date(graph_grid);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    if (graph)
	return set_non_savable_lookup_slot_value(graph,
		Qgraph_reformatted_since_start_qm,Nil);
    else
	return VALUES_1(Nil);
}

/* DECACHE-ALL-GRAPH-RENDERINGS-OF-GRAPH-GRID */
Object decache_all_graph_renderings_of_graph_grid(graph_grid)
    Object graph_grid;
{
    Object graph_rendering, ab_loop_list_;

    x_note_fn_call(172,5);
    graph_rendering = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)42L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    graph_rendering = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    decache_graph_rendering(graph_rendering);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qgraph;              /* graph */

static Object Qexpressions_to_display;  /* expressions-to-display */

/* CLEANUP-FOR-GRAPH */
Object cleanup_for_graph(graph)
    Object graph;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(172,6);
    frame = graph;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgraph)) {
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
    return change_slot_value(3,graph,Qexpressions_to_display,Nil);
}

static Object Qgraph_grid;         /* graph-grid */

/* CLEANUP-FOR-GRAPH-GRID */
Object cleanup_for_graph_grid(graph_grid)
    Object graph_grid;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(172,7);
    frame = graph_grid;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgraph_grid)) {
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
    return decache_all_graph_renderings_of_graph_grid(graph_grid);
}

/* RECLAIM-LINE-DRAWING-DESCRIPTION-FOR-GRAPH-GRID?-VALUE */
Object reclaim_line_drawing_description_for_graph_grid_qm_value(line_drawing_description_for_graph_grid_qm,
	    graph_grid)
    Object line_drawing_description_for_graph_grid_qm, graph_grid;
{
    x_note_fn_call(172,8);
    reclaim_graph_tree_1(line_drawing_description_for_graph_grid_qm);
    ISVREF(graph_grid,(SI_Long)56L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-TAIL-POINTER-FOR-LINE-DRAWING-DESCRIPTION-VALUE */
Object reclaim_tail_pointer_for_line_drawing_description_value(tail_pointer_for_line_drawing_description,
	    graph_grid)
    Object tail_pointer_for_line_drawing_description, graph_grid;
{
    x_note_fn_call(172,9);
    ISVREF(graph_grid,(SI_Long)57L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-TAIL-POINTER-FOR-LINE-SEGMENTS-VALUE */
Object reclaim_tail_pointer_for_line_segments_value(tail_pointer_for_line_segments,
	    graph_grid)
    Object tail_pointer_for_line_segments, graph_grid;
{
    x_note_fn_call(172,10);
    ISVREF(graph_grid,(SI_Long)58L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-LOW-VALUE-FOR-HORIZONTAL-AXIS-VALUE */
Object reclaim_desired_low_value_for_horizontal_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,11);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)16L));
    ISVREF(frame,(SI_Long)16L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-HIGH-VALUE-FOR-HORIZONTAL-AXIS-VALUE */
Object reclaim_desired_high_value_for_horizontal_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,12);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)17L));
    ISVREF(frame,(SI_Long)17L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-LOW-VALUE-FOR-VERTICAL-AXIS-VALUE */
Object reclaim_desired_low_value_for_vertical_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,13);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)18L));
    ISVREF(frame,(SI_Long)18L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-DESIRED-HIGH-VALUE-FOR-VERTICAL-AXIS-VALUE */
Object reclaim_desired_high_value_for_vertical_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,14);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)19L));
    ISVREF(frame,(SI_Long)19L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES-VALUE */
Object reclaim_interval_between_horizontal_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,15);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)20L));
    ISVREF(frame,(SI_Long)20L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-LOW-VALUE-FOR-HORIZONTAL-GRID-LINES-VALUE */
Object reclaim_low_value_for_horizontal_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,16);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)21L));
    ISVREF(frame,(SI_Long)21L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-HORIZONTAL-GRID-LINES-VALUE */
Object reclaim_high_value_for_horizontal_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,17);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)22L));
    ISVREF(frame,(SI_Long)22L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HORIZONTAL-GRID-LINE-SPACING-VALUE */
Object reclaim_horizontal_grid_line_spacing_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,18);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)24L));
    ISVREF(frame,(SI_Long)24L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-INTERVAL-BETWEEN-VERTICAL-GRID-LINES-VALUE */
Object reclaim_interval_between_vertical_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,19);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)26L));
    ISVREF(frame,(SI_Long)26L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-LOW-VALUE-FOR-VERTICAL-GRID-LINES-VALUE */
Object reclaim_low_value_for_vertical_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,20);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)27L));
    ISVREF(frame,(SI_Long)27L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-VERTICAL-GRID-LINES-VALUE */
Object reclaim_high_value_for_vertical_grid_lines_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,21);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)28L));
    ISVREF(frame,(SI_Long)28L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-VERTICAL-GRID-LINE-SPACING-VALUE */
Object reclaim_vertical_grid_line_spacing_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,22);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)30L));
    ISVREF(frame,(SI_Long)30L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-LOW-VALUE-FOR-HORIZONTAL-AXIS-VALUE */
Object reclaim_low_value_for_horizontal_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,23);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)44L));
    ISVREF(frame,(SI_Long)44L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-HORIZONTAL-AXIS-VALUE */
Object reclaim_high_value_for_horizontal_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,24);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)46L));
    ISVREF(frame,(SI_Long)46L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-LOW-VALUE-FOR-VERTICAL-AXIS-VALUE */
Object reclaim_low_value_for_vertical_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,25);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)47L));
    ISVREF(frame,(SI_Long)47L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HIGH-VALUE-FOR-VERTICAL-AXIS-VALUE */
Object reclaim_high_value_for_vertical_axis_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,26);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)48L));
    ISVREF(frame,(SI_Long)48L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-HORIZONTAL-AXIS-RANGE-VALUE */
Object reclaim_horizontal_axis_range_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,27);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)36L));
    ISVREF(frame,(SI_Long)36L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-VERTICAL-AXIS-RANGE-VALUE */
Object reclaim_vertical_axis_range_value(value,frame)
    Object value, frame;
{
    Object svref_new_value;

    x_note_fn_call(172,28);
    svref_new_value = 
	    reclaim_managed_number_or_value_function(ISVREF(frame,
	    (SI_Long)37L));
    ISVREF(frame,(SI_Long)37L) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

static Object Qplot_color;         /* plot-color */

/* PUT-PLOT-PATTERN-WHERE-SLOT-IS-ABSENT */
Object put_plot_pattern_where_slot_is_absent(plot,old_value)
    Object plot, old_value;
{
    Object current_block_of_dependent_frame;
    Declare_special(1);

    x_note_fn_call(172,29);
    if (old_value) {
	current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		0);
	  change_slot_value(3,plot,Qplot_color,
		  slot_value_list_2(ISVREF(plot,(SI_Long)4L),old_value));
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* PLOT-COLOR-GIVEN-PLOT */
Object plot_color_given_plot(plot)
    Object plot;
{
    Object plot_color_and_info;

    x_note_fn_call(172,30);
    plot_color_and_info = ISVREF(plot,(SI_Long)4L);
    if (CONSP(plot_color_and_info))
	return VALUES_1(CAR(plot_color_and_info));
    else
	return VALUES_1(plot_color_and_info);
}

/* PLOT-MARKER-AND-OR-LINE-WIDTH */
Object plot_marker_and_or_line_width(plot)
    Object plot;
{
    Object plot_color_and_info;

    x_note_fn_call(172,31);
    plot_color_and_info = ISVREF(plot,(SI_Long)4L);
    if (CONSP(plot_color_and_info))
	return VALUES_1(SECOND(plot_color_and_info));
    else
	return VALUES_1(Nil);
}

static Object Qnupec;              /* nupec */

/* PLOT-MARKER-OR-SHADING-KEY-GIVEN-PLOT */
Object plot_marker_or_shading_key_given_plot(plot)
    Object plot;
{
    Object plot_marker_and_or_line_width_1;

    x_note_fn_call(172,32);
    plot_marker_and_or_line_width_1 = plot_marker_and_or_line_width(plot);
    if (SYMBOLP(plot_marker_and_or_line_width_1))
	return VALUES_1(plot_marker_and_or_line_width_1);
    else if (CONSP(plot_marker_and_or_line_width_1)) {
	if (EQ(CAR(plot_marker_and_or_line_width_1),Qnupec))
	    return VALUES_1(plot_marker_and_or_line_width_1);
	else
	    return VALUES_1(CAR(plot_marker_and_or_line_width_1));
    }
    else
	return VALUES_1(Qnil);
}

/* PLOT-LINE-WIDTH-GIVEN-PLOT */
Object plot_line_width_given_plot(plot)
    Object plot;
{
    Object plot_marker_and_or_line_width_1;

    x_note_fn_call(172,33);
    plot_marker_and_or_line_width_1 = plot_marker_and_or_line_width(plot);
    if (NUMBERP(plot_marker_and_or_line_width_1))
	return VALUES_1(plot_marker_and_or_line_width_1);
    else if (CONSP(plot_marker_and_or_line_width_1)) {
	if ( !EQ(CAR(plot_marker_and_or_line_width_1),Qnupec))
	    return VALUES_1(CDR(plot_marker_and_or_line_width_1));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qshading;            /* shading */

/* PLOT-MARKER-GIVEN-PLOT */
Object plot_marker_given_plot(plot)
    Object plot;
{
    Object plot_marker_or_shading_key;

    x_note_fn_call(172,34);
    plot_marker_or_shading_key = plot_marker_or_shading_key_given_plot(plot);
    if ( !EQ(plot_marker_or_shading_key,Qshading))
	return VALUES_1(plot_marker_or_shading_key);
    else
	return VALUES_1(Nil);
}

/* PLOT-SHADING-GIVEN-PLOT */
Object plot_shading_given_plot(plot)
    Object plot;
{
    Object plot_marker_or_shading_key;

    x_note_fn_call(172,35);
    plot_marker_or_shading_key = plot_marker_or_shading_key_given_plot(plot);
    return VALUES_1(EQ(plot_marker_or_shading_key,Qshading) ? T : Nil);
}

/* PLOT-MIN-AND-MAX-GIVEN-PLOT */
Object plot_min_and_max_given_plot(plot)
    Object plot;
{
    Object plot_color_and_info;

    x_note_fn_call(172,36);
    plot_color_and_info = ISVREF(plot,(SI_Long)4L);
    if (CONSP(plot_color_and_info))
	return VALUES_1(THIRD(plot_color_and_info));
    else
	return VALUES_1(Nil);
}

static Object float_constant;      /* 0.0 */

/* PLOT-MIN-GIVEN-PLOT-MIN-AND-MAX */
Object plot_min_given_plot_min_and_max(plot_min_and_max)
    Object plot_min_and_max;
{
    Object slot_value_number, temp;

    x_note_fn_call(172,37);
    slot_value_number = CAR(plot_min_and_max);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	temp = slot_value_number;
    return lfloat(temp,float_constant);
}

/* PLOT-MAX-GIVEN-PLOT-MIN-AND-MAX */
Object plot_max_given_plot_min_and_max(plot_min_and_max)
    Object plot_min_and_max;
{
    Object slot_value_number, temp;

    x_note_fn_call(172,38);
    slot_value_number = CDR(plot_min_and_max);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	temp = slot_value_number;
    return lfloat(temp,float_constant);
}

/* GENERATE-SPOT-FOR-GRAPH-AXIS-LABEL */
Object generate_spot_for_graph_axis_label(graph_axis_label,mouse_pointer)
    Object graph_axis_label, mouse_pointer;
{
    x_note_fn_call(172,39);
    return generate_spot_for_aggregate(graph_axis_label,mouse_pointer);
}

Object The_type_description_of_plot_data_ring_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_plot_data_ring_buffers, Qchain_of_available_plot_data_ring_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Plot_data_ring_buffer_count, Qplot_data_ring_buffer_count);

Object Chain_of_available_plot_data_ring_buffers_vector = UNBOUND;

/* PLOT-DATA-RING-BUFFER-STRUCTURE-MEMORY-USAGE */
Object plot_data_ring_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(172,40);
    temp = Plot_data_ring_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PLOT-DATA-RING-BUFFER-COUNT */
Object outstanding_plot_data_ring_buffer_count()
{
    Object def_structure_plot_data_ring_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(172,41);
    gensymed_symbol = IFIX(Plot_data_ring_buffer_count);
    def_structure_plot_data_ring_buffer_variable = 
	    Chain_of_available_plot_data_ring_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_plot_data_ring_buffer_variable))
	goto end_loop;
    def_structure_plot_data_ring_buffer_variable = 
	    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PLOT-DATA-RING-BUFFER-1 */
Object reclaim_plot_data_ring_buffer_1(plot_data_ring_buffer)
    Object plot_data_ring_buffer;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(172,42);
    inline_note_reclaim_cons(plot_data_ring_buffer,Nil);
    structure_being_reclaimed = plot_data_ring_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_ring_buffer_vector(ISVREF(plot_data_ring_buffer,(SI_Long)6L));
      SVREF(plot_data_ring_buffer,FIX((SI_Long)6L)) = Nil;
      reclaim_ring_buffer_vector(ISVREF(plot_data_ring_buffer,(SI_Long)7L));
      SVREF(plot_data_ring_buffer,FIX((SI_Long)7L)) = Nil;
      reclaim_plot_marker_indices(ISVREF(plot_data_ring_buffer,(SI_Long)11L));
      SVREF(plot_data_ring_buffer,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_plot_data_ring_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(plot_data_ring_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_plot_data_ring_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = plot_data_ring_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PLOT-DATA-RING-BUFFER */
Object reclaim_structure_for_plot_data_ring_buffer(plot_data_ring_buffer)
    Object plot_data_ring_buffer;
{
    x_note_fn_call(172,43);
    return reclaim_plot_data_ring_buffer_1(plot_data_ring_buffer);
}

static Object Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct;  /* g2-defstruct-structure-name::plot-data-ring-buffer-g2-struct */

/* MAKE-PERMANENT-PLOT-DATA-RING-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_plot_data_ring_buffer_structure_internal()
{
    Object def_structure_plot_data_ring_buffer_variable;
    Object defstruct_g2_plot_data_ring_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(172,44);
    def_structure_plot_data_ring_buffer_variable = Nil;
    atomic_incff_symval(Qplot_data_ring_buffer_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_plot_data_ring_buffer_variable = Nil;
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
	defstruct_g2_plot_data_ring_buffer_variable = the_array;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_plot_data_ring_buffer_variable,
		FIX((SI_Long)5L)) = Nil;
	def_structure_plot_data_ring_buffer_variable = 
		defstruct_g2_plot_data_ring_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_plot_data_ring_buffer_variable);
}

/* MAKE-PLOT-DATA-RING-BUFFER-1 */
Object make_plot_data_ring_buffer_1()
{
    Object def_structure_plot_data_ring_buffer_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(172,45);
    def_structure_plot_data_ring_buffer_variable = 
	    ISVREF(Chain_of_available_plot_data_ring_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_plot_data_ring_buffer_variable) {
	svref_arg_1 = Chain_of_available_plot_data_ring_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_plot_data_ring_buffer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_plot_data_ring_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct;
    }
    else
	def_structure_plot_data_ring_buffer_variable = 
		make_permanent_plot_data_ring_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_plot_data_ring_buffer_variable,
	    Nil);
    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)3L)) = T;
    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)7L)) = Nil;
    ISVREF(def_structure_plot_data_ring_buffer_variable,(SI_Long)8L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)10L)) 
	    = Nil;
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)11L)) 
	    = Nil;
    SVREF(def_structure_plot_data_ring_buffer_variable,FIX((SI_Long)12L)) 
	    = Nil;
    return VALUES_1(def_structure_plot_data_ring_buffer_variable);
}

/* COPY-PLOT-DATA-RING-BUFFER */
Object copy_plot_data_ring_buffer varargs_1(int, n)
{
    Object ring_buffer;
    Object copier_function_for_additional_slots, new_shell, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(172,46);
    INIT_ARGS_nonrelocating();
    ring_buffer = REQUIRED_ARG_nonrelocating();
    copier_function_for_additional_slots = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    new_shell = make_plot_data_ring_buffer_1();
    copy_ring_buffer_shell_slots(ring_buffer,new_shell);
    svref_new_value = copy_ring_buffer_vector(ISVREF(ring_buffer,(SI_Long)6L));
    SVREF(new_shell,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = copy_ring_buffer_vector(ISVREF(ring_buffer,(SI_Long)7L));
    SVREF(new_shell,FIX((SI_Long)7L)) = svref_new_value;
    svref_new_value = copier_function_for_additional_slots ? 
	    FUNCALL_1(copier_function_for_additional_slots,
	    ISVREF(ring_buffer,(SI_Long)8L)) : ISVREF(ring_buffer,(SI_Long)8L);
    SVREF(new_shell,FIX((SI_Long)8L)) = svref_new_value;
    svref_new_value = copier_function_for_additional_slots ? 
	    FUNCALL_1(copier_function_for_additional_slots,
	    ISVREF(ring_buffer,(SI_Long)9L)) : ISVREF(ring_buffer,(SI_Long)9L);
    SVREF(new_shell,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = copier_function_for_additional_slots ? 
	    FUNCALL_1(copier_function_for_additional_slots,
	    ISVREF(ring_buffer,(SI_Long)10L)) : ISVREF(ring_buffer,
	    (SI_Long)10L);
    SVREF(new_shell,FIX((SI_Long)10L)) = svref_new_value;
    svref_new_value = copier_function_for_additional_slots ? 
	    FUNCALL_1(copier_function_for_additional_slots,
	    ISVREF(ring_buffer,(SI_Long)11L)) : ISVREF(ring_buffer,
	    (SI_Long)11L);
    SVREF(new_shell,FIX((SI_Long)11L)) = svref_new_value;
    svref_new_value = copier_function_for_additional_slots ? 
	    FUNCALL_1(copier_function_for_additional_slots,
	    ISVREF(ring_buffer,(SI_Long)12L)) : ISVREF(ring_buffer,
	    (SI_Long)12L);
    SVREF(new_shell,FIX((SI_Long)12L)) = svref_new_value;
    return VALUES_1(new_shell);
}

/* RECLAIM-PLOT-MARKER-INDICES */
Object reclaim_plot_marker_indices(indices)
    Object indices;
{
    x_note_fn_call(172,47);
    return reclaim_graph_list_1(indices);
}

/* CLEAR-PLOT-MARKER-DATA */
Object clear_plot_marker_data(plot_data_ring_buffer)
    Object plot_data_ring_buffer;
{
    x_note_fn_call(172,48);
    reclaim_plot_marker_indices(ISVREF(plot_data_ring_buffer,(SI_Long)11L));
    SVREF(plot_data_ring_buffer,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(SVREF(plot_data_ring_buffer,FIX((SI_Long)11L)) = Nil);
}

/* RECLAIM-DATA-BUFFER-FOR-PLOT-VALUE */
Object reclaim_data_buffer_for_plot_value(data_buffer_for_plot,plot)
    Object data_buffer_for_plot, plot;
{
    x_note_fn_call(172,49);
    reclaim_plot_data_ring_buffer_1(data_buffer_for_plot);
    return VALUES_1(Nil);
}

/* DATA-EXISTS-FOR-PLOT-P */
Object data_exists_for_plot_p(plot)
    Object plot;
{
    Object data_buffer_for_plot;

    x_note_fn_call(172,50);
    data_buffer_for_plot = ISVREF(plot,(SI_Long)5L);
    if (data_buffer_for_plot)
	return VALUES_1( !TRUEP(ISVREF(data_buffer_for_plot,(SI_Long)3L)) ?
		 T : Nil);
    else
	return VALUES_1(Nil);
}

/* EXPAND-PLOT-DATA-RING-BUFFER */
Object expand_plot_data_ring_buffer(data_buffer_for_plot)
    Object data_buffer_for_plot;
{
    Object current_size, ring_buffer, index_1;
    Object oldest_active_element_index_for_ring_buffer;
    Object old_data_boundary_index, length_up_to_old_data_boundary_index;
    Object oldest_active_element_index, next_larger_size, thing;
    Object svref_new_value;
    SI_Long length_up_to_new_data_boundary_index, ring_buffer_length;
    SI_Long svref_new_value_1;

    x_note_fn_call(172,51);
    current_size = ISVREF(data_buffer_for_plot,(SI_Long)4L);
    if (FIXNUM_LT(current_size,Largest_ring_buffer_vector_size)) {
	ring_buffer = data_buffer_for_plot;
	index_1 = ISVREF(data_buffer_for_plot,(SI_Long)8L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	length_up_to_new_data_boundary_index = FIXNUM_GE(index_1,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
	old_data_boundary_index = ISVREF(data_buffer_for_plot,(SI_Long)9L);
	if (old_data_boundary_index) {
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(data_buffer_for_plot,(SI_Long)2L);
	    length_up_to_old_data_boundary_index = 
		    FIXNUM_GE(old_data_boundary_index,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(old_data_boundary_index,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(old_data_boundary_index,
		    ISVREF(data_buffer_for_plot,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer));
	}
	else
	    length_up_to_old_data_boundary_index = Nil;
	oldest_active_element_index = ISVREF(data_buffer_for_plot,(SI_Long)2L);
	ring_buffer = data_buffer_for_plot;
	index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	ring_buffer_length = FIXNUM_GE(index_1,
		oldest_active_element_index_for_ring_buffer) ? 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		oldest_active_element_index_for_ring_buffer))) : 
		IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)));
	next_larger_size = Nil;
	if (next_larger_size);
	else
	    next_larger_size = 
		    compute_next_larger_size_for_ring_buffer_vectors(current_size);
	thing = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    rotate_managed_array(ISVREF(data_buffer_for_plot,(SI_Long)6L),
		    oldest_active_element_index);
	    svref_new_value = adjust_managed_array(2,
		    ISVREF(data_buffer_for_plot,(SI_Long)6L),next_larger_size);
	    SVREF(data_buffer_for_plot,FIX((SI_Long)6L)) = svref_new_value;
	}
	else {
	    rotate_managed_float_array(ISVREF(data_buffer_for_plot,
		    (SI_Long)6L),oldest_active_element_index);
	    svref_new_value = adjust_managed_float_array(2,
		    ISVREF(data_buffer_for_plot,(SI_Long)6L),next_larger_size);
	    SVREF(data_buffer_for_plot,FIX((SI_Long)6L)) = svref_new_value;
	}
	thing = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Managed_array_unique_marker)) {
	    rotate_managed_array(ISVREF(data_buffer_for_plot,(SI_Long)7L),
		    oldest_active_element_index);
	    svref_new_value = adjust_managed_array(2,
		    ISVREF(data_buffer_for_plot,(SI_Long)7L),next_larger_size);
	    SVREF(data_buffer_for_plot,FIX((SI_Long)7L)) = svref_new_value;
	}
	else {
	    rotate_managed_float_array(ISVREF(data_buffer_for_plot,
		    (SI_Long)7L),oldest_active_element_index);
	    svref_new_value = adjust_managed_float_array(2,
		    ISVREF(data_buffer_for_plot,(SI_Long)7L),next_larger_size);
	    SVREF(data_buffer_for_plot,FIX((SI_Long)7L)) = svref_new_value;
	}
	ISVREF(data_buffer_for_plot,(SI_Long)2L) = FIX((SI_Long)0L);
	svref_new_value_1 = ring_buffer_length - (SI_Long)1L;
	ISVREF(data_buffer_for_plot,(SI_Long)1L) = FIX(svref_new_value_1);
	SVREF(data_buffer_for_plot,FIX((SI_Long)4L)) = next_larger_size;
	svref_new_value_1 = length_up_to_new_data_boundary_index - (SI_Long)1L;
	ISVREF(data_buffer_for_plot,(SI_Long)8L) = FIX(svref_new_value_1);
	if (old_data_boundary_index) {
	    svref_new_value = 
		    FIXNUM_SUB1(length_up_to_old_data_boundary_index);
	    return VALUES_1(SVREF(data_buffer_for_plot,FIX((SI_Long)9L)) = 
		    svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_distance_for_data_points, Qminimum_distance_for_data_points);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_background_color_value, Qgraph_background_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Horizontal_grid_line_width, Qhorizontal_grid_line_width);

DEFINE_VARIABLE_WITH_SYMBOL(Vertical_grid_line_width, Qvertical_grid_line_width);

DEFINE_VARIABLE_WITH_SYMBOL(Vertical_grid_line_color_qm, Qvertical_grid_line_color_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Horizontal_grid_line_color_qm, Qhorizontal_grid_line_color_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Graph_grid_for_data, Qgraph_grid_for_data);

DEFINE_VARIABLE_WITH_SYMBOL(Grid_width, Qgrid_width);

DEFINE_VARIABLE_WITH_SYMBOL(Grid_height, Qgrid_height);

DEFINE_VARIABLE_WITH_SYMBOL(Default_graph_line_color_value, Qdefault_graph_line_color_value);

DEFINE_VARIABLE_WITH_SYMBOL(Joes_graph_hax_p, Qjoes_graph_hax_p);

DEFINE_VARIABLE_WITH_SYMBOL(Joes_graph_hax_trace_p, Qjoes_graph_hax_trace_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_graph_grid_in_minimal_update, Qcurrent_graph_grid_in_minimal_update);

static Object Qforeground;         /* foreground */

static Object Qbackground_colors;  /* background-colors */

static Object Qbackground;         /* background */

static Object Qworkspace_foreground;  /* workspace-foreground */

static Object Qtransparent;        /* transparent */

/* DRAW-FOR-GRAPH */
Object draw_for_graph(graph)
    Object graph;
{
    Object temp, graph_background_color, color_value, old_color_value;
    Object current_background_color_value;
    Declare_stack_pointer;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,52);
    SAVE_STACK();
    if ((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & (SI_Long)2048L)) {
	result = draw_block_outline_in_current_image_plane(2,graph,
		Qforeground);
	RESTORE_STACK();
	return result;
    }
    else {
	temp = get_lookup_slot_value(graph,Qbackground_colors);
	graph_background_color = CAR(temp);
	if (EQ(graph_background_color,Qbackground))
	    color_value = Current_background_color_value;
	else if (EQ(graph_background_color,Qforeground) || 
		EQ(graph_background_color,Qworkspace_foreground))
	    color_value = Current_foreground_color_value;
	else if (EQ(graph_background_color,Qtransparent))
	    color_value = Current_background_color_value;
	else
	    color_value = map_to_color_value(graph_background_color);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(color_value);
	  paint_background_for_opaque_block(graph);
	  SAVE_VALUES(draw_for_table(graph));
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

/* GRAPH-RENDERING-HAS-WRONG-SCALE? */
Object graph_rendering_has_wrong_scale_qm(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(172,53);
    return VALUES_1( !(FIXNUM_EQ(Current_image_x_scale,
	    ISVREF(graph_rendering,(SI_Long)3L)) && 
	    FIXNUM_EQ(Current_image_y_scale,ISVREF(graph_rendering,
	    (SI_Long)4L))) ? T : Nil);
}

static Object Qdisplay_up_to_date_qm;  /* display-up-to-date? */

/* GRAPH-NEEDS-FORMATTING? */
Object graph_needs_formatting_qm(graph,graph_grid,
	    graph_rendering_has_wrong_scale_qm_1)
    Object graph, graph_grid, graph_rendering_has_wrong_scale_qm_1;
{
    Object temp;

    x_note_fn_call(172,54);
    temp =  !TRUEP(ISVREF(graph_grid,(SI_Long)24L)) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(ISVREF(graph_grid,(SI_Long)38L)) ? T : Nil;
    if (temp);
    else
	temp = graph_rendering_has_wrong_scale_qm_1;
    if (temp)
	return VALUES_1(temp);
    else if ((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & 
	    (SI_Long)1L) || (SI_Long)0L != (IFIX(ISVREF(graph,
	    (SI_Long)4L)) & (SI_Long)16777216L))
	return VALUES_1( !TRUEP(get_lookup_slot_value_given_default(graph,
		Qdisplay_up_to_date_qm,Nil)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* GET-GRAPH-RENDERING-FOR-CURRENT-WINDOW */
Object get_graph_rendering_for_current_window(graph_grid)
    Object graph_grid;
{
    Object graph_rendering, ab_loop_list_;

    x_note_fn_call(172,55);
    graph_rendering = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)42L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    graph_rendering = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(Current_window,ISVREF(graph_rendering,(SI_Long)17L)))
	return VALUES_1(graph_rendering);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qscrolling;          /* scrolling */

/* DRAW-FOR-GRAPH-GRID */
Object draw_for_graph_grid(graph_grid)
    Object graph_grid;
{
    Object gensymed_symbol, graph, current_graph_rendering_qm;
    Object graph_rendering_has_wrong_scale_qm_1, redraw_as_well_as_reformat_p;
    Object gensymed_symbol_1, temp_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(172,56);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    current_graph_rendering_qm = 
	    get_graph_rendering_for_current_window(graph_grid);
    graph_rendering_has_wrong_scale_qm_1 = Nil;
    if (current_graph_rendering_qm) {
	graph_rendering_has_wrong_scale_qm_1 = 
		graph_rendering_has_wrong_scale_qm(current_graph_rendering_qm);
	temp = TRUEP(graph_rendering_has_wrong_scale_qm_1);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	decache_graph_rendering(current_graph_rendering_qm);
    if (printing_p());
    else if (graph_needs_formatting_qm(graph,graph_grid,
	    graph_rendering_has_wrong_scale_qm_1)) {
	redraw_as_well_as_reformat_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		0);
	  make_or_reformat_graph_grid(5,Nil,graph_grid,ISVREF(graph,
		  (SI_Long)22L),T,T);
	POP_SPECIAL();
	if (Joes_graph_hax_p)
	    Current_graph_grid_in_minimal_update = Nil;
	make_graph_not_up_to_date(graph_grid);
    }
    else if (EQ(ISVREF(graph_grid,(SI_Long)52L),Qscrolling) &&  
	    !TRUEP(memq_function(Current_image_plane,ISVREF(graph_grid,
	    (SI_Long)53L)))) {
	reclaim_graph_list_1(ISVREF(graph_grid,(SI_Long)53L));
	ISVREF(graph_grid,(SI_Long)53L) = Nil;
	redraw_as_well_as_reformat_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		0);
	  make_or_reformat_graph_grid(5,Nil,graph_grid,ISVREF(graph,
		  (SI_Long)22L),T,T);
	POP_SPECIAL();
	if (Joes_graph_hax_p) {
	    format((SI_Long)2L,T,"__+__+__+__Clobbering~%");
	    Current_graph_grid_in_minimal_update = Nil;
	}
	make_graph_not_up_to_date(graph_grid);
	set_non_savable_lookup_slot_value(graph,
		Qgraph_reformatted_since_start_qm,Nil);
    }
    draw_graph_grid_and_data(graph_grid,printing_p() && 
	    EQ(Printing_pass_number,FIX((SI_Long)2L)) ? Nil :  
	    !TRUEP(memq_function(Current_image_plane,ISVREF(graph_grid,
	    (SI_Long)53L))) ? T : Nil);
    if ( !TRUEP(Joes_graph_hax_p) ||  
	    !EQ(Current_graph_grid_in_minimal_update,graph_grid) ||  
	    !TRUEP(Current_graph_grid_in_minimal_update)) {
	gensymed_symbol = ISVREF(graph_grid,(SI_Long)53L);
	gensymed_symbol_1 = Current_image_plane;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = gensymed_symbol_1;
	    new_cons = ISVREF(Available_graph_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_graph_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_graph_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_graph_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
	    ISVREF(graph_grid,(SI_Long)53L) = gensymed_symbol_2;
	    return VALUES_1(temp_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Bogus_preflight_from_printing_to_graphs, Qbogus_preflight_from_printing_to_graphs);

/* BOGUS-PREFLIGHT-FROM-PRINTING-TO-GRAPHS */
Object bogus_preflight_from_printing_to_graphs(workspace)
    Object workspace;
{
    Object bogus_preflight_from_printing_to_graphs_1, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,57);
    bogus_preflight_from_printing_to_graphs_1 = T;
    PUSH_SPECIAL_WITH_SYMBOL(Bogus_preflight_from_printing_to_graphs,Qbogus_preflight_from_printing_to_graphs,bogus_preflight_from_printing_to_graphs_1,
	    0);
      gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
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
      ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	      ab_queue_form_);
      sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	  reformat_graph_based_on_edit_if_necessary(subblock,Nil);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qadd_graph_rendering;  /* add-graph-rendering */

/* DRAW-CURRENT-GRAPH-RENDERING */
Object draw_current_graph_rendering(left_edge_in_window,top_edge_in_window,
	    right_edge_in_window,bottom_edge_in_window)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window;
{
    Object previous_tail, next_element, previous_element, temp;
    Object svref_new_value;

    x_note_fn_call(172,58);
    previous_tail = ISVREF(Graph_rendering_lru_queue,(SI_Long)2L);
    if ( !EQ(Current_graph_rendering,previous_tail)) {
	next_element = ISVREF(Current_graph_rendering,(SI_Long)1L);
	previous_element = ISVREF(Current_graph_rendering,(SI_Long)2L);
	SVREF(previous_element,FIX((SI_Long)1L)) = next_element;
	SVREF(next_element,FIX((SI_Long)2L)) = previous_element;
	temp = Current_graph_rendering;
	SVREF(previous_tail,FIX((SI_Long)1L)) = temp;
	temp = Current_graph_rendering;
	SVREF(temp,FIX((SI_Long)2L)) = previous_tail;
	temp = Current_graph_rendering;
	svref_new_value = Graph_rendering_lru_queue;
	SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	temp = Graph_rendering_lru_queue;
	svref_new_value = Current_graph_rendering;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    return draw_graphic_element(7,Qadd_graph_rendering,left_edge_in_window,
	    top_edge_in_window,right_edge_in_window,bottom_edge_in_window,
	    ISVREF(Current_graph_rendering,(SI_Long)10L),
	    Current_graph_rendering);
}

/* COMPUTE-ERASE-DATELINE-1 */
Object compute_erase_dateline_1(graph_grid,dateline)
    Object graph_grid, dateline;
{
    Object total_range, managed_number_or_value, temp;

    x_note_fn_call(172,59);
    total_range = ISVREF(graph_grid,(SI_Long)60L);
    managed_number_or_value = ISVREF(graph_grid,(SI_Long)36L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
    else if (text_string_p(managed_number_or_value))
	temp = copy_text_string(managed_number_or_value);
    else
	temp = managed_number_or_value;
    return mod(add(dateline,minus(total_range,temp)),total_range);
}

/* COMPUTE-ERASE-DATELINE */
Object compute_erase_dateline(graph_grid)
    Object graph_grid;
{
    x_note_fn_call(172,60);
    return compute_erase_dateline_1(graph_grid,ISVREF(graph_grid,
	    (SI_Long)49L));
}

/* ROUND-FOR-GRAPHS */
Object round_for_graphs(x)
    Object x;
{
    double arg, arg_1, temp;

    x_note_fn_call(172,61);
    arg = DFLOAT_ISAREF_1(x,(SI_Long)0L);
    arg_1 = 0.0;
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	temp = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	arg = temp - inline_ffloor_1(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	arg_1 = 0.5;
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(x,
		    (SI_Long)0L))));
	else
	    return VALUES_1(LONG_TO_FIXNUM(inline_ceiling_1(DFLOAT_ISAREF_1(x,
		    (SI_Long)0L))));
    }
    else {
	temp = DFLOAT_ISAREF_1(x,(SI_Long)0L);
	arg = temp - (double)inline_ceiling_1(DFLOAT_ISAREF_1(x,(SI_Long)0L));
	arg_1 = -0.5;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    return VALUES_1(LONG_TO_FIXNUM(inline_ceiling_1(DFLOAT_ISAREF_1(x,
		    (SI_Long)0L))));
	else
	    return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(DFLOAT_ISAREF_1(x,
		    (SI_Long)0L))));
    }
}

/* COMPUTE-X-VALUE-ON-GRAPH */
Object compute_x_value_on_graph(x_value_on_offset_horizontal_axis,graph_grid)
    Object x_value_on_offset_horizontal_axis, graph_grid;
{
    Object aref_arg_1;
    double gensymed_symbol, gensymed_symbol_1, aref_new_value;

    x_note_fn_call(172,62);
    aref_arg_1 = Handy_float_1;
    gensymed_symbol = (double)IFIX(ISVREF(graph_grid,(SI_Long)59L)) * 
	    (double)IFIX(x_value_on_offset_horizontal_axis) / 
	    (double)IFIX(ISVREF(graph_grid,(SI_Long)60L));
    gensymed_symbol_1 = (double)IFIX(FIXNUM_ADD1(ISVREF(graph_grid,
	    (SI_Long)59L)));
    aref_new_value = MIN(gensymed_symbol,gensymed_symbol_1);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    return round_for_graphs(Handy_float_1);
}

/* DRAW-GRAPH-GRID-AND-DATA */
Object draw_graph_grid_and_data(graph_grid,repaint_raster_qm)
    Object graph_grid, repaint_raster_qm;
{
    Object gensymed_symbol, graph, graph_format;
    Object default_graph_line_color_value, temp, color_or_metacolor;
    Object graph_background_color_value, grid_background_color_value;
    Object line_to_background_color_difference, horizontal_grid_line_width;
    Object vertical_grid_line_width, graph_grid_for_data;
    Object graph_margin_color_qm, graph_margin_color_value;
    Object horizontal_grid_line_color_qm, vertical_grid_line_color_qm;
    Object grid_width, grid_height, current_graph_rendering;
    Object graph_rendering_is_new_qm, update_graph_description_qm;
    Object svref_new_value, extra_grid_lines_qm, grid_border_width;
    Object ab_queue_form_, ab_next_queue_element_, subblock;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_grid;
    SI_Long top_edge_of_grid, right_edge_of_grid, bottom_edge_of_grid;
    SI_Long unshifted_result, left_edge_of_grid_in_window;
    SI_Long top_edge_of_grid_in_window, right_edge_of_grid_in_window;
    SI_Long bottom_edge_of_grid_in_window;
    Declare_special(10);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,63);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    graph_format = ISVREF(graph,(SI_Long)22L);
    default_graph_line_color_value = 
	    compute_graph_line_color_value(graph_grid,graph_format);
    PUSH_SPECIAL_WITH_SYMBOL(Default_graph_line_color_value,Qdefault_graph_line_color_value,default_graph_line_color_value,
	    9);
      temp = get_lookup_slot_value(graph,Qbackground_colors);
      color_or_metacolor = CAR(temp);
      if (EQ(color_or_metacolor,Qbackground))
	  graph_background_color_value = Current_background_color_value;
      else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	      Qworkspace_foreground))
	  graph_background_color_value = Current_foreground_color_value;
      else if (EQ(color_or_metacolor,Qtransparent))
	  graph_background_color_value = Current_background_color_value;
      else
	  graph_background_color_value = 
		  map_to_color_value(color_or_metacolor);
      PUSH_SPECIAL_WITH_SYMBOL(Graph_background_color_value,Qgraph_background_color_value,graph_background_color_value,
	      8);
	temp = get_lookup_slot_value(graph,Qbackground_colors);
	color_or_metacolor = CDR(temp);
	if (EQ(color_or_metacolor,Qbackground))
	    grid_background_color_value = Current_background_color_value;
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground))
	    grid_background_color_value = Current_foreground_color_value;
	else if (EQ(color_or_metacolor,Qtransparent))
	    grid_background_color_value = Current_background_color_value;
	else
	    grid_background_color_value = 
		    map_to_color_value(color_or_metacolor);
	line_to_background_color_difference = 
		FIXNUM_LOGXOR(Default_graph_line_color_value,
		Graph_background_color_value);
	horizontal_grid_line_width = ISVREF(graph_format,(SI_Long)27L);
	PUSH_SPECIAL_WITH_SYMBOL(Horizontal_grid_line_width,Qhorizontal_grid_line_width,horizontal_grid_line_width,
		7);
	  vertical_grid_line_width = ISVREF(graph_format,(SI_Long)29L);
	  PUSH_SPECIAL_WITH_SYMBOL(Vertical_grid_line_width,Qvertical_grid_line_width,vertical_grid_line_width,
		  6);
	    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)38L));
	    left_edge_of_grid = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)40L));
	    top_edge_of_grid = gensymed_symbol_1 + gensymed_symbol_2;
	    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)39L));
	    right_edge_of_grid = gensymed_symbol_1 - gensymed_symbol_2;
	    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)41L));
	    bottom_edge_of_grid = gensymed_symbol_1 - gensymed_symbol_2;
	    graph_grid_for_data = graph_grid;
	    PUSH_SPECIAL_WITH_SYMBOL(Graph_grid_for_data,Qgraph_grid_for_data,graph_grid_for_data,
		    5);
	      graph_margin_color_qm = ISVREF(graph_format,(SI_Long)26L);
	      if (graph_margin_color_qm) {
		  if (EQ(graph_margin_color_qm,Qbackground))
		      graph_margin_color_value = 
			      Current_background_color_value;
		  else if (EQ(graph_margin_color_qm,Qforeground) || 
			  EQ(graph_margin_color_qm,Qworkspace_foreground))
		      graph_margin_color_value = 
			      Current_foreground_color_value;
		  else if (EQ(graph_margin_color_qm,Qtransparent))
		      graph_margin_color_value = 
			      Current_background_color_value;
		  else
		      graph_margin_color_value = 
			      map_to_color_value(graph_margin_color_qm);
	      }
	      else
		  graph_margin_color_value = Graph_background_color_value;
	      horizontal_grid_line_color_qm = ISVREF(graph_format,
		      (SI_Long)28L);
	      PUSH_SPECIAL_WITH_SYMBOL(Horizontal_grid_line_color_qm,Qhorizontal_grid_line_color_qm,horizontal_grid_line_color_qm,
		      4);
		vertical_grid_line_color_qm = ISVREF(graph_format,
			(SI_Long)30L);
		PUSH_SPECIAL_WITH_SYMBOL(Vertical_grid_line_color_qm,Qvertical_grid_line_color_qm,vertical_grid_line_color_qm,
			3);
		  grid_width = ISVREF(graph_grid,(SI_Long)34L);
		  PUSH_SPECIAL_WITH_SYMBOL(Grid_width,Qgrid_width,grid_width,
			  2);
		    grid_height = ISVREF(graph_grid,(SI_Long)35L);
		    PUSH_SPECIAL_WITH_SYMBOL(Grid_height,Qgrid_height,grid_height,
			    1);
		      current_graph_rendering = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering,Qcurrent_graph_rendering,current_graph_rendering,
			      0);
			graph_rendering_is_new_qm = Nil;
			update_graph_description_qm =  
				!TRUEP(ISVREF(graph_grid,(SI_Long)52L)) ? 
				T : Nil;
			if (Joes_graph_hax_trace_p)
			    format((SI_Long)4L,T,
				    "grid and data ugd\?=~s cggimu=~s~%",
				    update_graph_description_qm,
				    Current_graph_grid_in_minimal_update);
			result = get_or_make_graph_rendering(graph_grid);
			MVS_2(result,Current_graph_rendering,
				graph_rendering_is_new_qm);
			if (graph_rendering_is_new_qm) {
			    repaint_raster_qm = T;
			    update_graph_description_qm = T;
			}
			if (repaint_raster_qm)
			    update_color_values_for_graph(graph_grid,graph,
				    Current_graph_rendering,
				    grid_background_color_value);
			if (update_graph_description_qm && 
				(Joes_graph_hax_p ?  
				!EQ(Current_graph_grid_in_minimal_update,
				graph_grid) : TRUEP(T))) {
			    reclaim_graph_tree_1(ISVREF(graph_grid,
				    (SI_Long)56L));
			    svref_new_value = 
				    graph_cons_1(graph_cons_1(Qgraph,Nil),Nil);
			    ISVREF(graph_grid,(SI_Long)56L) = svref_new_value;
			    svref_new_value = ISVREF(graph_grid,(SI_Long)56L);
			    ISVREF(graph_grid,(SI_Long)57L) = svref_new_value;
			    ISVREF(graph_grid,(SI_Long)58L) = Nil;
			    ISVREF(graph_grid,(SI_Long)49L) = FIX((SI_Long)0L);
			    ISVREF(graph_grid,(SI_Long)50L) = FIX((SI_Long)0L);
			    ISVREF(graph_grid,(SI_Long)62L) = FIX((SI_Long)0L);
			    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
				add_graph_new_dateline(FIX((SI_Long)0L),
					compute_x_value_on_graph(compute_erase_dateline(graph_grid),
					graph_grid));
			    POP_LOCAL_ALLOCATION(0,0);
			    add_graph_clear();
			    if (ISVREF(graph,(SI_Long)27L))
				draw_graph_grid(graph_grid,graph);
			    else {
				extra_grid_lines_qm = ISVREF(graph,
					(SI_Long)29L);
				if (extra_grid_lines_qm)
				    draw_extra_grid_lines(graph_grid,
					    extra_grid_lines_qm,
					    FIX((SI_Long)0L),
					    ISVREF(graph_grid,(SI_Long)59L));
			    }
			    draw_data_for_graph_grid(graph_grid,graph_format);
			}
			grid_border_width = ISVREF(Current_graph_rendering,
				(SI_Long)11L);
			gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
			if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			    gensymed_symbol_2 = left_edge_of_grid;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				Current_image_x_scale) && 
				FIXNUM_LT(Current_image_x_scale,
				Isqrt_of_most_positive_fixnum) && 
				IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				< left_edge_of_grid && left_edge_of_grid < 
				IFIX(Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(Current_image_x_scale) 
				    * left_edge_of_grid + (SI_Long)2048L;
			    gensymed_symbol_2 = unshifted_result >>  -  - 
				    (SI_Long)12L;
			}
			else
			    gensymed_symbol_2 = 
				    IFIX(scalef_function(Current_image_x_scale,
				    FIX(left_edge_of_grid)));
			left_edge_of_grid_in_window = gensymed_symbol_1 + 
				gensymed_symbol_2;
			gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
			if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			    gensymed_symbol_2 = top_edge_of_grid;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				Current_image_y_scale) && 
				FIXNUM_LT(Current_image_y_scale,
				Isqrt_of_most_positive_fixnum) && 
				IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				< top_edge_of_grid && top_edge_of_grid < 
				IFIX(Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(Current_image_y_scale) 
				    * top_edge_of_grid + (SI_Long)2048L;
			    gensymed_symbol_2 = unshifted_result >>  -  - 
				    (SI_Long)12L;
			}
			else
			    gensymed_symbol_2 = 
				    IFIX(scalef_function(Current_image_y_scale,
				    FIX(top_edge_of_grid)));
			top_edge_of_grid_in_window = gensymed_symbol_1 + 
				gensymed_symbol_2;
			gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
			if (IFIX(Current_image_x_scale) == (SI_Long)4096L)
			    gensymed_symbol_2 = right_edge_of_grid;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				Current_image_x_scale) && 
				FIXNUM_LT(Current_image_x_scale,
				Isqrt_of_most_positive_fixnum) && 
				IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				< right_edge_of_grid && right_edge_of_grid 
				< IFIX(Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(Current_image_x_scale) 
				    * right_edge_of_grid + (SI_Long)2048L;
			    gensymed_symbol_2 = unshifted_result >>  -  - 
				    (SI_Long)12L;
			}
			else
			    gensymed_symbol_2 = 
				    IFIX(scalef_function(Current_image_x_scale,
				    FIX(right_edge_of_grid)));
			right_edge_of_grid_in_window = gensymed_symbol_1 + 
				gensymed_symbol_2;
			gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
			if (IFIX(Current_image_y_scale) == (SI_Long)4096L)
			    gensymed_symbol_2 = bottom_edge_of_grid;
			else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
				Current_image_y_scale) && 
				FIXNUM_LT(Current_image_y_scale,
				Isqrt_of_most_positive_fixnum) && 
				IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
				< bottom_edge_of_grid && 
				bottom_edge_of_grid < 
				IFIX(Isqrt_of_most_positive_fixnum)) {
			    unshifted_result = IFIX(Current_image_y_scale) 
				    * bottom_edge_of_grid + (SI_Long)2048L;
			    gensymed_symbol_2 = unshifted_result >>  -  - 
				    (SI_Long)12L;
			}
			else
			    gensymed_symbol_2 = 
				    IFIX(scalef_function(Current_image_y_scale,
				    FIX(bottom_edge_of_grid)));
			bottom_edge_of_grid_in_window = gensymed_symbol_1 
				+ gensymed_symbol_2;
			draw_rectangle_outline_in_window(FIX(left_edge_of_grid_in_window),
				FIX(top_edge_of_grid_in_window),
				FIX(right_edge_of_grid_in_window),
				FIX(bottom_edge_of_grid_in_window),
				line_to_background_color_difference,
				grid_border_width,grid_border_width);
			clear_data_clipping_rectangles();
			if (repaint_raster_qm && (Joes_graph_hax_p ?  
				!EQ(Current_graph_grid_in_minimal_update,
				graph_grid) : TRUEP(T)))
			    update_graph_rendering();
			else if (repaint_raster_qm)
			    update_colors_of_current_graph_rendering();
			draw_current_graph_rendering(FIX(left_edge_of_grid_in_window 
				+ IFIX(grid_border_width)),
				FIX(top_edge_of_grid_in_window + 
				IFIX(grid_border_width)),
				FIX(right_edge_of_grid_in_window - 
				IFIX(grid_border_width)),
				FIX(bottom_edge_of_grid_in_window - 
				IFIX(grid_border_width)));
			if ( !(Joes_graph_hax_p && 
				EQ(Current_graph_grid_in_minimal_update,
				graph_grid)))
			    ISVREF(graph_grid,(SI_Long)52L) = T;
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
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
	    draw_graph_axis_label(graph_grid,subblock);
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* DRAW-GRAPH-GRID-CURRENT-TIME-DISPLAY */
Object draw_graph_grid_current_time_display(graph_grid)
    Object graph_grid;
{
    Object time_display_text_box_qm;

    x_note_fn_call(172,64);
    time_display_text_box_qm = ISVREF(graph_grid,(SI_Long)55L);
    if (time_display_text_box_qm)
	return draw_graph_axis_label(graph_grid,time_display_text_box_qm);
    else
	return VALUES_1(Nil);
}

/* DRAW-GRAPH-AXIS-LABEL */
Object draw_graph_axis_label(graph_grid,axis_label_text_box)
    Object graph_grid, axis_label_text_box;
{
    Object temp, text, current_text_box_format, current_text_cell_plist;
    Object gensymed_symbol, graph, color_or_metacolor, background_color_value;
    Object old_color_value, current_background_color_value, scale, value;
    Object temp_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, unshifted_result;
    Declare_stack_pointer;
    Declare_special(3);
    Object result;

    x_note_fn_call(172,65);
    SAVE_STACK();
    temp = ISVREF(axis_label_text_box,(SI_Long)16L);
    text = CDR(temp);
    current_text_box_format = ISVREF(axis_label_text_box,(SI_Long)17L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_text_box_format,Qcurrent_text_box_format,current_text_box_format,
	    2);
      current_text_cell_plist = ISVREF(axis_label_text_box,(SI_Long)18L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_text_cell_plist,Qcurrent_text_cell_plist,current_text_cell_plist,
	      1);
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
	temp = get_lookup_slot_value(graph,Qbackground_colors);
	color_or_metacolor = CAR(temp);
	if (EQ(color_or_metacolor,Qbackground))
	    background_color_value = Current_background_color_value;
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground))
	    background_color_value = Current_foreground_color_value;
	else if (EQ(color_or_metacolor,Qtransparent))
	    background_color_value = Current_background_color_value;
	else
	    background_color_value = map_to_color_value(color_or_metacolor);
	old_color_value = Current_background_color_value;
	current_background_color_value = Current_background_color_value;
	PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
		0);
	  set_current_background_color_value(background_color_value);
	  paint_background_for_opaque_block(axis_label_text_box);
	  gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	  scale = Current_image_x_scale;
	  gensymed_symbol = ISVREF(axis_label_text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  value = gensymed_symbol;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) 
		  && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		      (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	  temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	  scale = Current_image_y_scale;
	  gensymed_symbol = ISVREF(axis_label_text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  value = gensymed_symbol;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) 
		  && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		      (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	  temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  gensymed_symbol_1 = IFIX(Current_x_origin_of_drawing);
	  scale = Current_image_x_scale;
	  gensymed_symbol = ISVREF(axis_label_text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  value = gensymed_symbol;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) 
		  && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		      (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	  temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  gensymed_symbol_1 = IFIX(Current_y_origin_of_drawing);
	  scale = Current_image_y_scale;
	  gensymed_symbol = ISVREF(axis_label_text_box,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  value = gensymed_symbol;
	  if (IFIX(scale) == (SI_Long)4096L)
	      gensymed_symbol_2 = IFIX(value);
	  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		  && FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) 
		  && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	      unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		      (SI_Long)2048L;
	      gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	  }
	  else
	      gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	  SAVE_VALUES(draw_text_segment_1(text,Nil,FIX((SI_Long)0L),temp_1,
		  temp_2,temp,FIX(gensymed_symbol_1 + gensymed_symbol_2)));
	  set_current_background_color_value(old_color_value);
	  result = RESTORE_VALUES();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qtable;              /* table */

/* COMPUTE-GRAPH-LINE-COLOR-VALUE */
Object compute_graph_line_color_value(graph_grid,graph_format)
    Object graph_grid, graph_format;
{
    Object graph_line_color_qm, gensymed_symbol, supertable, ab_loop_it_;
    Object frame, symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(172,66);
    graph_line_color_qm = ISVREF(graph_format,(SI_Long)22L);
    if (graph_line_color_qm);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph_line_color_qm = ISVREF(ISVREF(gensymed_symbol,(SI_Long)16L),
		(SI_Long)22L);
    }
    if (graph_line_color_qm);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	supertable = gensymed_symbol;
	ab_loop_it_ = Nil;
      next_loop:
	ab_loop_it_ = ISVREF(ISVREF(supertable,(SI_Long)16L),(SI_Long)22L);
	if (ab_loop_it_) {
	    graph_line_color_qm = ab_loop_it_;
	    goto end_1;
	}
	gensymed_symbol = ACCESS_ONCE(ISVREF(supertable,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	if (gensymed_symbol) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(supertable,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    frame = gensymed_symbol;
	    symbol = Qtable;
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    goto end_loop;
	gensymed_symbol = ACCESS_ONCE(ISVREF(supertable,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	supertable = gensymed_symbol;
	goto next_loop;
      end_loop:
	graph_line_color_qm = Qnil;
      end_1:;
    }
    if (graph_line_color_qm) {
	if (EQ(graph_line_color_qm,Qbackground))
	    return VALUES_1(Current_background_color_value);
	else if (EQ(graph_line_color_qm,Qforeground) || 
		EQ(graph_line_color_qm,Qworkspace_foreground))
	    return VALUES_1(Current_foreground_color_value);
	else if (EQ(graph_line_color_qm,Qtransparent))
	    return VALUES_1(Current_background_color_value);
	else
	    return map_to_color_value(graph_line_color_qm);
    }
    else
	return VALUES_1(Current_foreground_color_value);
}

/* GET-OR-MAKE-GRAPH-RENDERING */
Object get_or_make_graph_rendering(graph_grid)
    Object graph_grid;
{
    Object current_graph_rendering_qm, new_graph_rendering, gensymed_symbol;
    Object gensymed_symbol_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_2;

    x_note_fn_call(172,67);
    current_graph_rendering_qm = 
	    get_graph_rendering_for_current_window(graph_grid);
    if ( !TRUEP(current_graph_rendering_qm) || 
	    graph_rendering_has_wrong_scale_qm(current_graph_rendering_qm)) {
	if (current_graph_rendering_qm)
	    decache_graph_rendering(current_graph_rendering_qm);
	new_graph_rendering = make_new_graph_rendering(graph_grid,
		Current_image_x_scale,Current_image_y_scale);
	gensymed_symbol = ISVREF(graph_grid,(SI_Long)42L);
	gensymed_symbol_1 = new_graph_rendering;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
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
	    ISVREF(graph_grid,(SI_Long)42L) = gensymed_symbol_2;
	}
	return VALUES_2(new_graph_rendering,T);
    }
    else
	return VALUES_2(current_graph_rendering_qm,Nil);
}

static Object Qpolychrome_raster;  /* polychrome-raster */

static Object Qmonochrome_raster_list;  /* monochrome-raster-list */

static Object Qmonochrome_raster;  /* monochrome-raster */

/* CHOOSE-FORMAT-FOR-GRAPH-RENDERING */
Object choose_format_for_graph_rendering(number_of_colors)
    Object number_of_colors;
{
    x_note_fn_call(172,68);
    if (polychrome_rasters_for_graphs_p(Current_window))
	return VALUES_1(Qpolychrome_raster);
    else if (FIXNUM_LT(Icp_window_protocol_supports_monochrome_raster_lists,
	    ISVREF(Current_window,(SI_Long)11L)))
	return VALUES_1(Qmonochrome_raster_list);
    else
	return VALUES_1(Qmonochrome_raster);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* MAKE-NEW-GRAPH-RENDERING */
Object make_new_graph_rendering(graph_grid,x_scale,y_scale)
    Object graph_grid, x_scale, y_scale;
{
    Object total_width, width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure, size, plot_color_specs_so_far;
    Object gensymed_symbol, temp, grid_background_color, plot, ab_loop_list_;
    Object plot_color_qm, number_of_colors, temp_1, temp_2, temp_3;
    Object item_or_value, x2, graph_rendering, color_or_metacolor;
    SI_Long unshifted_result, number_of_foreground_colors_so_far;
    char temp_4;

    x_note_fn_call(172,69);
    total_width = ISVREF(graph_grid,(SI_Long)59L);
    if (IFIX(x_scale) == (SI_Long)4096L)
	width_of_graph_rendering_structure = total_width;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) && 
	    FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,total_width) 
	    && FIXNUM_LT(total_width,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(x_scale,total_width)) + 
		(SI_Long)2048L;
	width_of_graph_rendering_structure = FIX(unshifted_result >>  -  - 
		(SI_Long)12L);
    }
    else
	width_of_graph_rendering_structure = scalef_function(x_scale,
		total_width);
    if (IFIX(y_scale) == (SI_Long)4096L)
	height_of_graph_rendering_structure = Grid_height;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,Grid_height) 
	    && FIXNUM_LT(Grid_height,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,Grid_height)) + 
		(SI_Long)2048L;
	height_of_graph_rendering_structure = FIX(unshifted_result >>  -  
		- (SI_Long)12L);
    }
    else
	height_of_graph_rendering_structure = scalef_function(y_scale,
		Grid_height);
    size = 
	    compute_size_of_graph_rendering_1(width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure);
    plot_color_specs_so_far = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    temp = get_lookup_slot_value(gensymed_symbol,Qbackground_colors);
    grid_background_color = CDR(temp);
    plot = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    plot_color_qm = Nil;
    number_of_foreground_colors_so_far = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    plot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    plot_color_qm = plot_color_given_plot(plot);
    if ( !TRUEP(plot_color_specs_so_far) ||  !EQ(plot_color_qm,
	    grid_background_color) &&  !(member_eql(plot_color_qm,
	    plot_color_specs_so_far) && T)) {
	plot_color_specs_so_far = gensym_cons_1(plot_color_qm,
		plot_color_specs_so_far);
	number_of_foreground_colors_so_far = 
		number_of_foreground_colors_so_far + (SI_Long)1L;
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(plot_color_specs_so_far);
    number_of_colors = FIX(number_of_foreground_colors_so_far + (SI_Long)1L);
    goto end_1;
    number_of_colors = Qnil;
  end_1:;
    increase_allocation_limit_for_graphs_if_necessary(graph_grid,x_scale,
	    y_scale,size);
    temp_1 = choose_format_for_graph_rendering(number_of_colors);
    temp_2 = Horizontal_grid_line_width;
    temp_3 = Grid_height;
    temp = Current_window;
    item_or_value = graph_grid;
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_4 = TRUEP(Nil);
    graph_rendering = make_decacheable_graph_rendering(13,Nil,temp_1,
	    x_scale,y_scale,temp_2,total_width,temp_3,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,graph_grid,temp,temp_4 ? 
	    get_reference_to_item(item_or_value) : item_or_value,size);
    if (EQ(ISVREF(graph_rendering,(SI_Long)6L),Qmonochrome_raster_list)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp = gensymed_symbol;
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp_3 = get_lookup_slot_value(gensymed_symbol,Qbackground_colors);
	color_or_metacolor = CDR(temp_3);
	if (EQ(color_or_metacolor,Qbackground))
	    temp_3 = Current_background_color_value;
	else if (EQ(color_or_metacolor,Qforeground) || 
		EQ(color_or_metacolor,Qworkspace_foreground))
	    temp_3 = Current_foreground_color_value;
	else if (EQ(color_or_metacolor,Qtransparent))
	    temp_3 = Current_background_color_value;
	else
	    temp_3 = map_to_color_value(color_or_metacolor);
	update_color_values_for_graph(graph_grid,temp,graph_rendering,temp_3);
    }
    return VALUES_1(graph_rendering);
}

/* INCREASE-ALLOCATION-LIMIT-FOR-GRAPHS-IF-NECESSARY */
Object increase_allocation_limit_for_graphs_if_necessary(graph_grid,
	    x_scale,y_scale,size)
    Object graph_grid, x_scale, y_scale, size;
{
    Object limit_info_qm, required_size_qm, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;

    x_note_fn_call(172,70);
    limit_info_qm = 
	    get_memory_limit_info_given_size(Graph_rendering_memory_limit_info,
	    size);
    required_size_qm = 
	    compute_size_for_graphs_of_size_upon_workspace(graph_grid,
	    x_scale,y_scale,size);
    if (limit_info_qm) {
	gensymed_symbol = IFIX(ISVREF(limit_info_qm,(SI_Long)2L));
	temp = required_size_qm;
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(temp);
	svref_new_value = MAX(gensymed_symbol,gensymed_symbol_1);
	return VALUES_1(ISVREF(limit_info_qm,(SI_Long)2L) = 
		FIX(svref_new_value));
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-SIZE-FOR-GRAPHS-OF-SIZE-UPON-WORKSPACE */
Object compute_size_for_graphs_of_size_upon_workspace(graph_grid,x_scale,
	    y_scale,size)
    Object graph_grid, x_scale, y_scale, size;
{
    Object gensymed_symbol, graph, workspace_qm, total_size, size_1;
    Object ab_queue_form_, ab_next_queue_element_, subblock, graph_grid_1;
    Object temp, sub_class_bit_vector, scale, value, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long unshifted_result;
    char temp_1;

    x_note_fn_call(172,71);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    if (graph) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	workspace_qm = gensymed_symbol;
    }
    else
	workspace_qm = Nil;
    if (workspace_qm) {
	total_size = FIX((SI_Long)0L);
	size_1 = Nil;
	gensymed_symbol = ACCESS_ONCE(ISVREF(workspace_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	graph_grid_1 = Nil;
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
	temp = ISVREF(graph,(SI_Long)19L);
	temp = FIRST(temp);
	graph_grid_1 = FIRST(temp);
	sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    scale = x_scale;
	    value = ISVREF(graph_grid_1,(SI_Long)59L);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(scale,value);
	    scale = y_scale;
	    value = ISVREF(graph_grid,(SI_Long)35L);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_2 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_2 = scalef_function(scale,value);
	    size_1 = compute_size_of_graph_rendering_1(temp,temp_2);
	    if (FIXNUM_EQ(size_1,size))
		total_size = FIXNUM_ADD(total_size,size_1);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(total_size);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COLOR-VALUE-GIVEN-COLOR-OR-DEFAULT */
Object color_value_given_color_or_default(color_qm)
    Object color_qm;
{
    Object color_or_metacolor;

    x_note_fn_call(172,72);
    color_or_metacolor = color_qm;
    if (color_or_metacolor);
    else
	color_or_metacolor = Current_default_line_color;
    if (EQ(color_or_metacolor,Qbackground))
	return VALUES_1(Current_background_color_value);
    else if (EQ(color_or_metacolor,Qforeground) || EQ(color_or_metacolor,
	    Qworkspace_foreground))
	return VALUES_1(Current_foreground_color_value);
    else if (EQ(color_or_metacolor,Qtransparent))
	return VALUES_1(Current_background_color_value);
    else
	return map_to_color_value(color_or_metacolor);
}

static Object Qcm;                 /* \, */

/* UPDATE-COLOR-VALUES-FOR-GRAPH */
Object update_color_values_for_graph(graph_grid,graph,graph_rendering,
	    grid_background_color_value)
    Object graph_grid, graph, graph_rendering, grid_background_color_value;
{
    Object plot, ab_loop_list_, plot_color_qm, gensymed_symbol;
    Object gensymed_symbol_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_2, extra_grid_lines_qm;
    Object grid_line_spec;

    x_note_fn_call(172,73);
    if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),Qpolychrome_raster)) {
	reclaim_graph_list_1(ISVREF(graph_rendering,(SI_Long)10L));
	SVREF(graph_rendering,FIX((SI_Long)10L)) = Nil;
	plot = Nil;
	ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
	plot_color_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	plot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	plot_color_qm = plot_color_given_plot(plot);
	gensymed_symbol = ISVREF(graph_rendering,(SI_Long)10L);
	if (plot_color_qm) {
	    if (EQ(plot_color_qm,Qbackground))
		gensymed_symbol_1 = Current_background_color_value;
	    else if (EQ(plot_color_qm,Qforeground) || EQ(plot_color_qm,
		    Qworkspace_foreground))
		gensymed_symbol_1 = Current_foreground_color_value;
	    else if (EQ(plot_color_qm,Qtransparent))
		gensymed_symbol_1 = Current_background_color_value;
	    else
		gensymed_symbol_1 = map_to_color_value(plot_color_qm);
	}
	else
	    gensymed_symbol_1 = Default_graph_line_color_value;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_graph_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_graph_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_graph_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_graph_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
	    SVREF(graph_rendering,FIX((SI_Long)10L)) = gensymed_symbol_2;
	}
	goto next_loop;
      end_loop:;
	gensymed_symbol = ISVREF(graph_rendering,(SI_Long)10L);
	gensymed_symbol_1 = 
		color_value_given_color_or_default(Horizontal_grid_line_color_qm);
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_graph_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_graph_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_graph_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_graph_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
	    SVREF(graph_rendering,FIX((SI_Long)10L)) = gensymed_symbol_2;
	}
	gensymed_symbol = ISVREF(graph_rendering,(SI_Long)10L);
	gensymed_symbol_1 = 
		color_value_given_color_or_default(Vertical_grid_line_color_qm);
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    new_cons = ISVREF(Available_graph_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_graph_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_graph_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_graph_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
	    SVREF(graph_rendering,FIX((SI_Long)10L)) = gensymed_symbol_2;
	}
	extra_grid_lines_qm = ISVREF(graph,(SI_Long)29L);
	if (CONSP(extra_grid_lines_qm) &&  
		!(INLINE_DOUBLE_FLOAT_VECTOR_P(extra_grid_lines_qm) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(extra_grid_lines_qm)) == 
		(SI_Long)1L) && EQ(CAR(extra_grid_lines_qm),Qcm)) {
	    grid_line_spec = Nil;
	    ab_loop_list_ = CDR(extra_grid_lines_qm);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    grid_line_spec = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(graph_rendering,(SI_Long)10L);
	    gensymed_symbol_1 = 
		    color_value_given_color_or_default(CONSP(grid_line_spec) 
		    &&  !(INLINE_DOUBLE_FLOAT_VECTOR_P(grid_line_spec) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == 
		    (SI_Long)1L) ? CDR(grid_line_spec) : 
		    Horizontal_grid_line_color_qm);
	    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
		new_cons = ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_graph_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_graph_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_graph_cons_pool();
		M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		M_CDR(gensymed_symbol_2) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
		SVREF(graph_rendering,FIX((SI_Long)10L)) = gensymed_symbol_2;
	    }
	    goto next_loop_1;
	  end_loop_1:;
	}
	else {
	    gensymed_symbol = ISVREF(graph_rendering,(SI_Long)10L);
	    gensymed_symbol_1 = 
		    color_value_given_color_or_default(CONSP(extra_grid_lines_qm) 
		    &&  
		    !(INLINE_DOUBLE_FLOAT_VECTOR_P(extra_grid_lines_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(extra_grid_lines_qm)) 
		    == (SI_Long)1L) ? CDR(extra_grid_lines_qm) : 
		    Horizontal_grid_line_color_qm);
	    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
		new_cons = ISVREF(Available_graph_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_graph_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_graph_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_graph_cons_pool();
		M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
		M_CDR(gensymed_symbol_2) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_2,Qgraph);
		SVREF(graph_rendering,FIX((SI_Long)10L)) = gensymed_symbol_2;
	    }
	}
    }
    return VALUES_1(SVREF(graph_rendering,FIX((SI_Long)9L)) = 
	    grid_background_color_value);
}

/* COMPUTE-Y-VALUE-ON-GRAPH */
Object compute_y_value_on_graph(y_value_on_vertical_axis,
	    vertical_axis_range,low_value_for_vertical_axis)
    Object y_value_on_vertical_axis, vertical_axis_range;
    Object low_value_for_vertical_axis;
{
    Object temp;
    double temp_1, temp_2, temp_3, gensymed_symbol, gensymed_symbol_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(172,74);
    PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Vertical_axis_range,Qvertical_axis_range,vertical_axis_range,
	      0);
	temp = lfloat(Grid_height,float_constant);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(minus(y_value_on_vertical_axis,
		Low_value_for_vertical_axis),float_constant);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = lfloat(Vertical_axis_range,float_constant);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	gensymed_symbol = temp_1 * temp_2 / temp_3;
	gensymed_symbol_1 = (double)IFIX(FIXNUM_ADD1(Grid_height));
	result = VALUES_1(FIXNUM_MINUS(Grid_height,
		l_round(DOUBLE_TO_DOUBLE_FLOAT(MIN(gensymed_symbol,
		gensymed_symbol_1)),_)));
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPUTE-Y-VALUE-ON-GRAPH-NEW */
Object compute_y_value_on_graph_new(y_value_on_vertical_axis)
    Object y_value_on_vertical_axis;
{
    Object aref_arg_1, gensymed_symbol_2, temp_1;
    double gensymed_symbol, gensymed_symbol_1, temp, aref_new_value;

    x_note_fn_call(172,75);
    aref_arg_1 = Handy_float_1;
    gensymed_symbol = (double)IFIX(Grid_height) * 
	    (DFLOAT_ISAREF_1(y_value_on_vertical_axis,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,(SI_Long)0L)) / 
	    DFLOAT_ISAREF_1(Vertical_axis_range,(SI_Long)0L);
    gensymed_symbol_1 = (double)IFIX(FIXNUM_ADD1(Grid_height));
    gensymed_symbol = MIN(gensymed_symbol,gensymed_symbol_1);
    gensymed_symbol_2 = float_constant;
    temp = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_2);
    aref_new_value = MAX(gensymed_symbol,temp);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    temp_1 = Grid_height;
    return VALUES_1(FIXNUM_MINUS(temp_1,round_for_graphs(Handy_float_1)));
}

/* COMPUTE-Y-VALUE-ON-GRAPH-NEW-WITH-LESS-TRUNCATION */
Object compute_y_value_on_graph_new_with_less_truncation(y_value_on_vertical_axis)
    Object y_value_on_vertical_axis;
{
    Object aref_arg_1, temp;
    SI_Long limit;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(172,76);
    limit = (SI_Long)1000000L;
    aref_arg_1 = Handy_float_1;
    aref_new_value = (double)IFIX(Grid_height) * 
	    (DFLOAT_ISAREF_1(y_value_on_vertical_axis,(SI_Long)0L) - 
	    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,(SI_Long)0L)) / 
	    DFLOAT_ISAREF_1(Vertical_axis_range,(SI_Long)0L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    arg = (double)limit;
    arg_1 = DFLOAT_ISAREF_1(Handy_float_1,(SI_Long)0L);
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	aref_arg_1 = Handy_float_1;
	aref_new_value = (double)limit;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    else {
	arg = (double) - limit;
	arg_1 = DFLOAT_ISAREF_1(Handy_float_1,(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    aref_arg_1 = Handy_float_1;
	    aref_new_value = (double) - limit;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	}
    }
    temp = Grid_height;
    return VALUES_1(FIXNUM_MINUS(temp,round_for_graphs(Handy_float_1)));
}

/* ADJUST-X-VALUE-ACCORDING-TO-DATELINE */
Object adjust_x_value_according_to_dateline(value_on_horizontal_axis,
	    dateline,graph_grid,low_value_for_horizontal_axis_arg)
    Object value_on_horizontal_axis, dateline, graph_grid;
    Object low_value_for_horizontal_axis_arg;
{
    x_note_fn_call(172,77);
    return mod(FIXNUM_ADD(FIXNUM_MINUS(value_on_horizontal_axis,
	    low_value_for_horizontal_axis_arg),dateline),ISVREF(graph_grid,
	    (SI_Long)60L));
}

/* ADJUST-AND-COMPUTE-X-VALUE-ON-GRAPH */
Object adjust_and_compute_x_value_on_graph(value_on_horizontal_axis,
	    dateline,graph_grid,low_value_for_horizontal_axis_arg)
    Object value_on_horizontal_axis, dateline, graph_grid;
    Object low_value_for_horizontal_axis_arg;
{
    x_note_fn_call(172,78);
    return compute_x_value_on_graph(adjust_x_value_according_to_dateline(value_on_horizontal_axis,
	    dateline,graph_grid,low_value_for_horizontal_axis_arg),graph_grid);
}

/* DRAW-GRAPH-GRID */
Object draw_graph_grid(graph_grid,graph)
    Object graph_grid, graph;
{
    x_note_fn_call(172,79);
    if ( !TRUEP(Nil)) {
	draw_horizontal_grid_lines(graph_grid,graph,Nil,Nil);
	return draw_vertical_grid_lines(graph_grid);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Horizontal_grid_line_spacing, Qhorizontal_grid_line_spacing);

/* DRAW-HORIZONTAL-GRID-LINES */
Object draw_horizontal_grid_lines(graph_grid,graph,clipped_left_edge_qm,
	    clipped_right_edge_qm)
    Object graph_grid, graph, clipped_left_edge_qm, clipped_right_edge_qm;
{
    Object left_edge, right_edge, extra_grid_lines_qm, managed_number_or_value;
    Object horizontal_grid_line_spacing;
    Object top_edge_of_horizontal_grid_line_float;
    Object top_edge_of_horizontal_grid_line_in_workspace;
    Object bottom_edge_of_horizontal_grid_line_in_workspace;
    Object number_of_horizontal_grid_lines_drawn, ab_loop_iter_flag_;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,80);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	add_graph_color_to_use(Horizontal_grid_line_color_qm);
	left_edge = clipped_left_edge_qm;
	if (left_edge);
	else
	    left_edge = FIX((SI_Long)0L);
	right_edge = clipped_right_edge_qm;
	if (right_edge);
	else
	    right_edge = ISVREF(graph_grid,(SI_Long)59L);
	extra_grid_lines_qm = ISVREF(graph,(SI_Long)29L);
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)24L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    horizontal_grid_line_spacing = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    horizontal_grid_line_spacing = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    horizontal_grid_line_spacing = 
		    copy_text_string(managed_number_or_value);
	else
	    horizontal_grid_line_spacing = managed_number_or_value;
	PUSH_SPECIAL_WITH_SYMBOL(Horizontal_grid_line_spacing,Qhorizontal_grid_line_spacing,horizontal_grid_line_spacing,
		0);
	  top_edge_of_horizontal_grid_line_float = Nil;
	  top_edge_of_horizontal_grid_line_in_workspace = Nil;
	  bottom_edge_of_horizontal_grid_line_in_workspace = Nil;
	  number_of_horizontal_grid_lines_drawn = FIX((SI_Long)1L);
	  ab_loop_iter_flag_ = T;
	  managed_number_or_value = ISVREF(graph_grid,(SI_Long)25L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      top_edge_of_horizontal_grid_line_float = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      top_edge_of_horizontal_grid_line_float = 
		      aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      top_edge_of_horizontal_grid_line_float = 
		      copy_text_string(managed_number_or_value);
	  else
	      top_edge_of_horizontal_grid_line_float = managed_number_or_value;
	next_loop:
	  top_edge_of_horizontal_grid_line_in_workspace = 
		  l_round(top_edge_of_horizontal_grid_line_float,_);
	  bottom_edge_of_horizontal_grid_line_in_workspace = 
		  FIXNUM_ADD(top_edge_of_horizontal_grid_line_in_workspace,
		  Horizontal_grid_line_width);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      number_of_horizontal_grid_lines_drawn = 
		      FIXNUM_ADD1(number_of_horizontal_grid_lines_drawn);
	  if (FIXNUM_LE(bottom_edge_of_horizontal_grid_line_in_workspace,
		  Grid_height))
	      add_graph_rectangle(left_edge,
		      top_edge_of_horizontal_grid_line_in_workspace,
		      right_edge,
		      bottom_edge_of_horizontal_grid_line_in_workspace);
	  if (IFIX(number_of_horizontal_grid_lines_drawn) >= 
		  IFIX(ISVREF(graph_grid,(SI_Long)23L)) - (SI_Long)2L)
	      goto end_loop;
	  ab_loop_iter_flag_ = Nil;
	  top_edge_of_horizontal_grid_line_float = 
		  add(top_edge_of_horizontal_grid_line_float,
		  Horizontal_grid_line_spacing);
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
	if (extra_grid_lines_qm)
	    result = draw_extra_grid_lines(graph_grid,extra_grid_lines_qm,
		    left_edge,right_edge);
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DRAW-EXTRA-GRID-LINES */
Object draw_extra_grid_lines(graph_grid,extra_grid_lines_qm,left_edge,
	    right_edge)
    Object graph_grid, extra_grid_lines_qm, left_edge, right_edge;
{
    Object managed_number_or_value, vertical_axis_range;
    Object low_value_for_vertical_axis, grid_line_spec, ab_loop_list_;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,81);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)37L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    vertical_axis_range = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    vertical_axis_range = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    vertical_axis_range = copy_text_string(managed_number_or_value);
	else
	    vertical_axis_range = managed_number_or_value;
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)47L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_vertical_axis = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    low_value_for_vertical_axis = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    low_value_for_vertical_axis = 
		    copy_text_string(managed_number_or_value);
	else
	    low_value_for_vertical_axis = managed_number_or_value;
	PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Vertical_axis_range,Qvertical_axis_range,vertical_axis_range,
		  0);
	    if (CONSP(extra_grid_lines_qm) &&  
		    !(INLINE_DOUBLE_FLOAT_VECTOR_P(extra_grid_lines_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(extra_grid_lines_qm)) 
		    == (SI_Long)1L) && EQ(CAR(extra_grid_lines_qm),Qcm)) {
		grid_line_spec = Nil;
		ab_loop_list_ = CDR(extra_grid_lines_qm);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		grid_line_spec = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		draw_extra_horizontal_grid_line(grid_line_spec,
			Vertical_axis_range,Low_value_for_vertical_axis,
			left_edge,right_edge);
		goto next_loop;
	      end_loop:
		result = VALUES_1(Qnil);
	    }
	    else
		result = draw_extra_horizontal_grid_line(extra_grid_lines_qm,
			Vertical_axis_range,Low_value_for_vertical_axis,
			left_edge,right_edge);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DRAW-EXTRA-HORIZONTAL-GRID-LINE */
Object draw_extra_horizontal_grid_line(grid_line_spec,vertical_axis_range,
	    low_value_for_vertical_axis,left_edge,right_edge)
    Object grid_line_spec, vertical_axis_range, low_value_for_vertical_axis;
    Object left_edge, right_edge;
{
    Object y_on_vertical_axis, color;
    Object top_edge_of_horizontal_grid_line_in_workspace;
    Object bottom_edge_of_horizontal_grid_line_in_workspace, slot_value_number;
    Declare_special(2);
    Object result;

    x_note_fn_call(172,82);
    PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Vertical_axis_range,Qvertical_axis_range,vertical_axis_range,
	      0);
	y_on_vertical_axis = Nil;
	color = Horizontal_grid_line_color_qm;
	top_edge_of_horizontal_grid_line_in_workspace = Nil;
	bottom_edge_of_horizontal_grid_line_in_workspace = Nil;
	if (CONSP(grid_line_spec) &&  
		!(INLINE_DOUBLE_FLOAT_VECTOR_P(grid_line_spec) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == 
		(SI_Long)1L)) {
	    slot_value_number = CAR(grid_line_spec);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		y_on_vertical_axis = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		    (SI_Long)1L)
		y_on_vertical_axis = aref1(slot_value_number,FIX((SI_Long)0L));
	    else
		y_on_vertical_axis = slot_value_number;
	    color = CDR(grid_line_spec);
	}
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(grid_line_spec) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == (SI_Long)1L)
	    y_on_vertical_axis = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(grid_line_spec,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(grid_line_spec) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(grid_line_spec)) == (SI_Long)1L)
	    y_on_vertical_axis = aref1(grid_line_spec,FIX((SI_Long)0L));
	else
	    y_on_vertical_axis = grid_line_spec;
	add_graph_color_to_use(color);
	top_edge_of_horizontal_grid_line_in_workspace = 
		compute_y_value_on_graph(y_on_vertical_axis,
		Vertical_axis_range,Low_value_for_vertical_axis);
	bottom_edge_of_horizontal_grid_line_in_workspace = 
		FIXNUM_ADD(top_edge_of_horizontal_grid_line_in_workspace,
		Horizontal_grid_line_width);
	if (IFIX(top_edge_of_horizontal_grid_line_in_workspace) >= 
		(SI_Long)0L && 
		FIXNUM_LE(bottom_edge_of_horizontal_grid_line_in_workspace,
		Grid_height))
	    result = add_graph_rectangle(left_edge,
		    top_edge_of_horizontal_grid_line_in_workspace,
		    right_edge,
		    bottom_edge_of_horizontal_grid_line_in_workspace);
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Vertical_grid_line_spacing, Qvertical_grid_line_spacing);

/* DRAW-VERTICAL-GRID-LINES */
Object draw_vertical_grid_lines(graph_grid)
    Object graph_grid;
{
    Object managed_number_or_value, vertical_grid_line_spacing;
    Object right_edge_of_vertical_grid_line_float;
    Object right_edge_of_vertical_grid_line_in_workspace;
    Object left_edge_of_vertical_grid_line_in_workspace;
    Object number_of_vertical_grid_lines_drawn, ab_loop_iter_flag_, temp;
    Object temp_1;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,83);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	add_graph_color_to_use(Vertical_grid_line_color_qm);
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)30L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    vertical_grid_line_spacing = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    vertical_grid_line_spacing = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    vertical_grid_line_spacing = 
		    copy_text_string(managed_number_or_value);
	else
	    vertical_grid_line_spacing = managed_number_or_value;
	PUSH_SPECIAL_WITH_SYMBOL(Vertical_grid_line_spacing,Qvertical_grid_line_spacing,vertical_grid_line_spacing,
		0);
	  right_edge_of_vertical_grid_line_float = Nil;
	  right_edge_of_vertical_grid_line_in_workspace = Nil;
	  left_edge_of_vertical_grid_line_in_workspace = Nil;
	  number_of_vertical_grid_lines_drawn = FIX((SI_Long)1L);
	  ab_loop_iter_flag_ = T;
	  temp = ISVREF(graph_grid,(SI_Long)59L);
	  managed_number_or_value = ISVREF(graph_grid,(SI_Long)31L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      temp_1 = copy_text_string(managed_number_or_value);
	  else
	      temp_1 = managed_number_or_value;
	  right_edge_of_vertical_grid_line_float = minus(temp,temp_1);
	next_loop:
	  right_edge_of_vertical_grid_line_in_workspace = 
		  l_round(right_edge_of_vertical_grid_line_float,_);
	  left_edge_of_vertical_grid_line_in_workspace = 
		  FIXNUM_MINUS(right_edge_of_vertical_grid_line_in_workspace,
		  Vertical_grid_line_width);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      number_of_vertical_grid_lines_drawn = 
		      FIXNUM_ADD1(number_of_vertical_grid_lines_drawn);
	  temp = left_edge_of_vertical_grid_line_in_workspace;
	  if (FIXNUM_GE(temp,
		  compute_x_value_on_graph(compute_erase_dateline(graph_grid),
		  graph_grid)))
	      add_graph_rectangle(left_edge_of_vertical_grid_line_in_workspace,
		      FIX((SI_Long)0L),
		      right_edge_of_vertical_grid_line_in_workspace,
		      Grid_height);
	  if (IFIX(number_of_vertical_grid_lines_drawn) >= 
		  IFIX(ISVREF(graph_grid,(SI_Long)29L)) - (SI_Long)2L)
	      goto end_loop;
	  ab_loop_iter_flag_ = Nil;
	  right_edge_of_vertical_grid_line_float = 
		  minus(right_edge_of_vertical_grid_line_float,
		  Vertical_grid_line_spacing);
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DRAW-NEW-SCROLLED-VERTICAL-GRID-LINES */
Object draw_new_scrolled_vertical_grid_lines(graph_grid)
    Object graph_grid;
{
    Object vertical_grid_line_position, ab_loop_list_;
    Object left_edge_of_vertical_grid_line_in_workspace;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,84);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	add_graph_color_to_use(Vertical_grid_line_color_qm);
	vertical_grid_line_position = Nil;
	ab_loop_list_ = ISVREF(graph_grid,(SI_Long)51L);
	left_edge_of_vertical_grid_line_in_workspace = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	vertical_grid_line_position = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	left_edge_of_vertical_grid_line_in_workspace = 
		compute_x_value_on_graph(vertical_grid_line_position,
		graph_grid);
	add_graph_rectangle(left_edge_of_vertical_grid_line_in_workspace,
		FIX((SI_Long)0L),
		FIXNUM_ADD(left_edge_of_vertical_grid_line_in_workspace,
		Vertical_grid_line_width),Grid_height);
	goto next_loop;
      end_loop:
	result = VALUES_1(Qnil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* DRAW-DATA-FOR-GRAPH-GRID */
Object draw_data_for_graph_grid(graph_grid,graph_format)
    Object graph_grid, graph_format;
{
    Object gensymed_symbol, block, data_point_size;
    Object minimum_distance_for_data_points, plot, ab_loop_list_, plot_number;
    Object data_buffer_for_plot, ab_loop_iter_flag_, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,85);
    if ( !TRUEP(Nil)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	block = gensymed_symbol;
	temp =  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)2048L));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	data_point_size = ISVREF(graph_format,(SI_Long)41L);
	minimum_distance_for_data_points = ISVREF(graph_format,(SI_Long)42L);
	PUSH_SPECIAL_WITH_SYMBOL(Minimum_distance_for_data_points,Qminimum_distance_for_data_points,minimum_distance_for_data_points,
		0);
	  plot = Nil;
	  ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
	  plot_number = FIX((SI_Long)1L);
	  data_buffer_for_plot = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  plot = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      plot_number = FIXNUM_ADD1(plot_number);
	  data_buffer_for_plot = ISVREF(plot,(SI_Long)5L);
	  if (data_buffer_for_plot &&  !TRUEP(ISVREF(data_buffer_for_plot,
		  (SI_Long)3L))) {
	      temp_1 = data_buffer_for_plot;
	      temp_2 = ISVREF(data_buffer_for_plot,(SI_Long)2L);
	      temp_3 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	      temp_4 = plot_color_given_plot(plot);
	      temp_5 = plot_marker_given_plot(plot);
	      temp_6 = plot_shading_given_plot(plot);
	      draw_data_for_plot(temp_1,temp_2,temp_3,data_point_size,
		      temp_4,temp_5,temp_6,plot_line_width_given_plot(plot));
	  }
	  ab_loop_iter_flag_ = Nil;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_x_value_for_new_data, Qminimum_x_value_for_new_data);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_y_value_for_new_data, Qminimum_y_value_for_new_data);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_x_value_for_new_data, Qmaximum_x_value_for_new_data);

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_y_value_for_new_data, Qmaximum_y_value_for_new_data);

DEFINE_VARIABLE_WITH_SYMBOL(New_dateline_qm, Qnew_dateline_qm);

/* STORE-NEW-DATA-EXTREMA */
Object store_new_data_extrema(x,y)
    Object x, y;
{
    x_note_fn_call(172,86);
    Minimum_x_value_for_new_data = x;
    Minimum_y_value_for_new_data = y;
    Maximum_x_value_for_new_data = x;
    Maximum_y_value_for_new_data = y;
    return VALUES_1(Maximum_y_value_for_new_data);
}

/* EXTEND-MINIMUM-X-VALUE-IF-NECESSARY */
Object extend_minimum_x_value_if_necessary(x)
    Object x;
{
    x_note_fn_call(172,87);
    Minimum_x_value_for_new_data = FIXNUM_MIN(Minimum_x_value_for_new_data,x);
    return VALUES_1(Minimum_x_value_for_new_data);
}

/* EXTEND-MINIMUM-Y-VALUE-IF-NECESSARY */
Object extend_minimum_y_value_if_necessary(y)
    Object y;
{
    x_note_fn_call(172,88);
    Minimum_y_value_for_new_data = FIXNUM_MIN(Minimum_y_value_for_new_data,y);
    return VALUES_1(Minimum_y_value_for_new_data);
}

/* EXTEND-MAXIMUM-X-VALUE-IF-NECESSARY */
Object extend_maximum_x_value_if_necessary(x)
    Object x;
{
    x_note_fn_call(172,89);
    Maximum_x_value_for_new_data = FIXNUM_MAX(Maximum_x_value_for_new_data,x);
    return VALUES_1(Maximum_x_value_for_new_data);
}

/* EXTEND-MAXIMUM-Y-VALUE-IF-NECESSARY */
Object extend_maximum_y_value_if_necessary(y)
    Object y;
{
    x_note_fn_call(172,90);
    Maximum_y_value_for_new_data = FIXNUM_MAX(Maximum_y_value_for_new_data,y);
    return VALUES_1(Maximum_y_value_for_new_data);
}

/* EXTEND-EXTREMA-IF-NECESSARY */
Object extend_extrema_if_necessary(x,y)
    Object x, y;
{
    x_note_fn_call(172,91);
    extend_minimum_x_value_if_necessary(x);
    extend_minimum_y_value_if_necessary(y);
    extend_maximum_x_value_if_necessary(x);
    return extend_maximum_y_value_if_necessary(y);
}

/* GET-ERASE-DATELINE-ON-GRAPH */
Object get_erase_dateline_on_graph(graph_grid)
    Object graph_grid;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,92);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = compute_x_value_on_graph(compute_erase_dateline(graph_grid),
		graph_grid);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_minimal_grid_draw_has_seen_one_image_plane_p, Qcurrent_minimal_grid_draw_has_seen_one_image_plane_p);

/* DRAW-ONLY-NEW-DATA-FOR-GRAPH-GRID */
Object draw_only_new_data_for_graph_grid(graph_grid)
    Object graph_grid;
{
    Object current_graph_rendering, gensymed_symbol, graph;
    Object graph_grid_for_data, graph_format, default_graph_line_color_value;
    Object horizontal_grid_line_width, vertical_grid_line_width;
    Object horizontal_grid_line_color_qm, vertical_grid_line_color_qm;
    Object minimum_x_value_for_new_data, minimum_y_value_for_new_data;
    Object maximum_x_value_for_new_data, maximum_y_value_for_new_data;
    Object new_dateline_qm, data_point_size, minimum_distance_for_data_points;
    Object grid_width, grid_height, grid_border_width, draw_data_qm;
    Object new_data_qm, new_dateline_in_workspace_units_p, temp;
    Object left_edge_of_rectangle_in_raster, right_edge_of_rectangle_in_raster;
    Object left_edge_of_erase_rectangle, right_edge_of_erase_rectangle;
    Object show_grid_lines_qm, extra_grid_lines_qm, extrema_rectangles_qm;
    Object compute_extrema_qm, plot, ab_loop_list_, plot_number;
    Object data_buffer_for_plot, ab_loop_iter_flag_, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, gensymed_symbol_3, new_cons, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, redraw_as_well_as_reformat_p;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, left_edge_of_grid;
    SI_Long right_edge_of_grid, bottom_edge_of_grid, top_edge_of_grid, arg;
    SI_Long arg_1, arg_2, unshifted_result;
    char update_graph_description_qm;
    Declare_special(15);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,93);
    if ( !TRUEP(Current_minimal_grid_draw_has_seen_one_image_plane_p)) {
	ISVREF(graph_grid,(SI_Long)52L) = Nil;
	Current_minimal_grid_draw_has_seen_one_image_plane_p = T;
    }
    current_graph_rendering = 
	    get_graph_rendering_for_current_window(graph_grid);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering,Qcurrent_graph_rendering,current_graph_rendering,
	    14);
      if (Current_graph_rendering) {
	  graph_grid_for_data = graph_grid;
	  PUSH_SPECIAL_WITH_SYMBOL(Graph_grid_for_data,Qgraph_grid_for_data,graph_grid_for_data,
		  13);
	    graph_format = ISVREF(graph,(SI_Long)22L);
	    default_graph_line_color_value = 
		    compute_graph_line_color_value(graph_grid,graph_format);
	    PUSH_SPECIAL_WITH_SYMBOL(Default_graph_line_color_value,Qdefault_graph_line_color_value,default_graph_line_color_value,
		    12);
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)0L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)38L));
	      left_edge_of_grid = gensymed_symbol_1 + gensymed_symbol_2;
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)39L));
	      right_edge_of_grid = gensymed_symbol_1 - gensymed_symbol_2;
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)3L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)41L));
	      bottom_edge_of_grid = gensymed_symbol_1 - gensymed_symbol_2;
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)1L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)40L));
	      top_edge_of_grid = gensymed_symbol_1 + gensymed_symbol_2;
	      horizontal_grid_line_width = ISVREF(graph_format,(SI_Long)27L);
	      PUSH_SPECIAL_WITH_SYMBOL(Horizontal_grid_line_width,Qhorizontal_grid_line_width,horizontal_grid_line_width,
		      11);
		vertical_grid_line_width = ISVREF(graph_format,(SI_Long)27L);
		PUSH_SPECIAL_WITH_SYMBOL(Vertical_grid_line_width,Qvertical_grid_line_width,vertical_grid_line_width,
			10);
		  horizontal_grid_line_color_qm = ISVREF(graph_format,
			  (SI_Long)28L);
		  PUSH_SPECIAL_WITH_SYMBOL(Horizontal_grid_line_color_qm,Qhorizontal_grid_line_color_qm,horizontal_grid_line_color_qm,
			  9);
		    vertical_grid_line_color_qm = ISVREF(graph_format,
			    (SI_Long)30L);
		    PUSH_SPECIAL_WITH_SYMBOL(Vertical_grid_line_color_qm,Qvertical_grid_line_color_qm,vertical_grid_line_color_qm,
			    8);
		      minimum_x_value_for_new_data = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Minimum_x_value_for_new_data,Qminimum_x_value_for_new_data,minimum_x_value_for_new_data,
			      7);
			minimum_y_value_for_new_data = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Minimum_y_value_for_new_data,Qminimum_y_value_for_new_data,minimum_y_value_for_new_data,
				6);
			  maximum_x_value_for_new_data = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Maximum_x_value_for_new_data,Qmaximum_x_value_for_new_data,maximum_x_value_for_new_data,
				  5);
			    maximum_y_value_for_new_data = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Maximum_y_value_for_new_data,Qmaximum_y_value_for_new_data,maximum_y_value_for_new_data,
				    4);
			      new_dateline_qm = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(New_dateline_qm,Qnew_dateline_qm,new_dateline_qm,
				      3);
				data_point_size = ISVREF(graph_format,
					(SI_Long)41L);
				minimum_distance_for_data_points = 
					ISVREF(graph_format,(SI_Long)42L);
				PUSH_SPECIAL_WITH_SYMBOL(Minimum_distance_for_data_points,Qminimum_distance_for_data_points,minimum_distance_for_data_points,
					2);
				  grid_width = ISVREF(graph_grid,(SI_Long)34L);
				  PUSH_SPECIAL_WITH_SYMBOL(Grid_width,Qgrid_width,grid_width,
					  1);
				    grid_height = ISVREF(graph_grid,
					    (SI_Long)35L);
				    PUSH_SPECIAL_WITH_SYMBOL(Grid_height,Qgrid_height,grid_height,
					    0);
				      grid_border_width = 
					      ISVREF(Current_graph_rendering,
					      (SI_Long)11L);
				      update_graph_description_qm =  
					      !TRUEP(ISVREF(graph_grid,
					      (SI_Long)52L));
				      draw_data_qm = 
					      update_graph_description_qm 
					      &&  !TRUEP(Erase_instead_qm) 
					      ? ( !TRUEP(Nil) ? T : Nil) : 
					      Qnil;
				      new_data_qm = Nil;
				      new_dateline_in_workspace_units_p = Nil;
				      if (update_graph_description_qm) {
					  reclaim_graph_tree_1(ISVREF(graph_grid,
						  (SI_Long)56L));
					  temp = 
						  graph_cons_1(graph_cons_1(Qgraph,
						  Nil),Nil);
					  ISVREF(graph_grid,(SI_Long)56L) 
						  = temp;
					  temp = ISVREF(graph_grid,
						  (SI_Long)56L);
					  ISVREF(graph_grid,(SI_Long)57L) 
						  = temp;
					  ISVREF(graph_grid,(SI_Long)58L) 
						  = Nil;
				      }
				      clear_data_clipping_rectangles();
				      if (draw_data_qm) {
					  if ( 
						  !FIXNUM_EQ(ISVREF(graph_grid,
						  (SI_Long)50L),
						  ISVREF(graph_grid,
						  (SI_Long)49L))) {
					      New_dateline_qm = T;
					      if (PUSH_LOCAL_ALLOCATION(Local_area,
						      0,0)) {
						  left_edge_of_rectangle_in_raster 
							  = 
							  compute_x_value_on_graph(ISVREF(graph_grid,
							  (SI_Long)50L),
							  graph_grid);
						  right_edge_of_rectangle_in_raster 
							  = 
							  compute_x_value_on_graph(ISVREF(graph_grid,
							  (SI_Long)49L),
							  graph_grid);
						  left_edge_of_erase_rectangle 
							  = 
							  compute_x_value_on_graph(compute_erase_dateline_1(graph_grid,
							  ISVREF(graph_grid,
							  (SI_Long)50L)),
							  graph_grid);
						  right_edge_of_erase_rectangle 
							  = 
							  compute_x_value_on_graph(compute_erase_dateline(graph_grid),
							  graph_grid);
						  show_grid_lines_qm = 
							  ISVREF(graph,
							  (SI_Long)27L);
						  extra_grid_lines_qm = 
							  ISVREF(graph,
							  (SI_Long)29L);
						  new_dateline_in_workspace_units_p 
							  =  
							  !FIXNUM_EQ(ISVREF(graph_grid,
							  (SI_Long)62L),
							  right_edge_of_rectangle_in_raster) 
							  ? T : Nil;
						  temp = ISVREF(graph_grid,
							  (SI_Long)49L);
						  ISVREF(graph_grid,
							  (SI_Long)50L) = temp;
						  ISVREF(graph_grid,
							  (SI_Long)62L) = 
							  right_edge_of_rectangle_in_raster;
						  if (new_dateline_in_workspace_units_p)
						      add_graph_new_dateline(right_edge_of_rectangle_in_raster,
							      right_edge_of_erase_rectangle);
						  if (FIXNUM_GT(left_edge_of_erase_rectangle,
							  right_edge_of_erase_rectangle)) 
							      {
						      add_graph_clear_rectangle(left_edge_of_erase_rectangle,
							      FIX((SI_Long)0L),
							      ISVREF(graph_grid,
							      (SI_Long)59L),
							      Grid_height);
						      add_graph_clear_rectangle(FIX((SI_Long)0L),
							      FIX((SI_Long)0L),
							      right_edge_of_erase_rectangle,
							      Grid_height);
						  }
						  else
						      add_graph_clear_rectangle(left_edge_of_erase_rectangle,
							      FIX((SI_Long)0L),
							      right_edge_of_erase_rectangle,
							      Grid_height);
						  if (FIXNUM_GT(left_edge_of_rectangle_in_raster,
							  right_edge_of_rectangle_in_raster)) 
							      {
						      if (show_grid_lines_qm) {
							  draw_horizontal_grid_lines(graph_grid,
								  graph,
								  left_edge_of_rectangle_in_raster,
								  ISVREF(graph_grid,
								  (SI_Long)59L));
							  draw_horizontal_grid_lines(graph_grid,
								  graph,
								  FIX((SI_Long)0L),
								  right_edge_of_rectangle_in_raster);
							  draw_new_scrolled_vertical_grid_lines(graph_grid);
						      }
						      else if (extra_grid_lines_qm) 
								  {
							  draw_extra_grid_lines(graph_grid,
								  extra_grid_lines_qm,
								  left_edge_of_rectangle_in_raster,
								  ISVREF(graph_grid,
								  (SI_Long)59L));
							  draw_extra_grid_lines(graph_grid,
								  extra_grid_lines_qm,
								  FIX((SI_Long)0L),
								  right_edge_of_rectangle_in_raster);
						      }
						  }
						  else if (show_grid_lines_qm) 
							      {
						      draw_horizontal_grid_lines(graph_grid,
							      graph,
							      left_edge_of_rectangle_in_raster,
							      right_edge_of_rectangle_in_raster);
						      draw_new_scrolled_vertical_grid_lines(graph_grid);
						  }
						  else if (extra_grid_lines_qm)
						      draw_extra_grid_lines(graph_grid,
							      extra_grid_lines_qm,
							      left_edge_of_rectangle_in_raster,
							      right_edge_of_rectangle_in_raster);
					      }
					      POP_LOCAL_ALLOCATION(0,0);
					  }
					  extrema_rectangles_qm = Nil;
					  compute_extrema_qm = T;
					  plot = Nil;
					  ab_loop_list_ = 
						  ISVREF(graph_grid,
						  (SI_Long)33L);
					  plot_number = FIX((SI_Long)1L);
					  data_buffer_for_plot = Nil;
					  ab_loop_iter_flag_ = T;
					next_loop:
					  if ( !TRUEP(ab_loop_list_))
					      goto end_loop;
					  plot = M_CAR(ab_loop_list_);
					  ab_loop_list_ = M_CDR(ab_loop_list_);
					  if ( !TRUEP(ab_loop_iter_flag_))
					      plot_number = 
						      FIXNUM_ADD1(plot_number);
					  data_buffer_for_plot = 
						  ISVREF(plot,(SI_Long)5L);
					  if (data_buffer_for_plot &&  
						  !TRUEP(ISVREF(data_buffer_for_plot,
						  (SI_Long)3L))) {
					      if ( !TRUEP(Erase_instead_qm)) {
						  if ( 
							  !FIXNUM_EQ(ISVREF(data_buffer_for_plot,
							  (SI_Long)8L),
							  ISVREF(data_buffer_for_plot,
							  (SI_Long)1L)) || 
							  ISVREF(data_buffer_for_plot,
							  (SI_Long)12L)) {
						      temp_1 = 
							      data_buffer_for_plot;
						      temp_2 = 
							      ISVREF(data_buffer_for_plot,
							      (SI_Long)8L);
						      temp_3 = 
							      ISVREF(data_buffer_for_plot,
							      (SI_Long)1L);
						      temp_4 = 
							      plot_color_given_plot(plot);
						      temp_5 = 
							      plot_marker_given_plot(plot);
						      temp_6 = 
							      plot_shading_given_plot(plot);
						      draw_data_for_plot(temp_1,
							      temp_2,
							      temp_3,
							      data_point_size,
							      temp_4,
							      temp_5,
							      temp_6,
							      plot_line_width_given_plot(plot));
						      new_data_qm = T;
						      temp = 
							      ISVREF(data_buffer_for_plot,
							      (SI_Long)1L);
						      SVREF(data_buffer_for_plot,
							      FIX((SI_Long)8L)) 
							      = temp;
						  }
					      }
					      if ( !TRUEP(New_dateline_qm) 
						      && 
						      compute_extrema_qm 
						      && 
							  Minimum_x_value_for_new_data) {
						  arg = 
							  IFIX(Minimum_x_value_for_new_data);
						  arg_1 = 
							  IFIX(get_erase_dateline_on_graph(graph_grid));
						  arg_2 = 
							  IFIX(Maximum_x_value_for_new_data);
						  if ( !(arg < arg_1 && 
							  arg_1 < arg_2)) {
						      extrema_rectangles_qm 
							      = 
							      combine_new_extrema_with_existing_ones(extrema_rectangles_qm,
							      Minimum_x_value_for_new_data,
							      Minimum_y_value_for_new_data,
							      Maximum_x_value_for_new_data,
							      Maximum_y_value_for_new_data);
						      store_new_data_extrema(Nil,
							      Nil);
						  }
						  else {
						      compute_extrema_qm = Nil;
						      extrema_rectangles_qm 
							      = Nil;
						  }
					      }
					  }
					  ab_loop_iter_flag_ = Nil;
					  goto next_loop;
					end_loop:
					  if (extrema_rectangles_qm)
					      add_graph_data_extrema(extrema_rectangles_qm);
				      }
				      if (new_data_qm || 
					      new_dateline_in_workspace_units_p)
					  ISVREF(graph_grid,(SI_Long)61L) = T;
				      if (ISVREF(graph_grid,(SI_Long)61L)) {
					  update_graph_rendering();
					  gensymed_symbol_1 = 
						  IFIX(Current_x_origin_of_drawing);
					  if (IFIX(Current_image_x_scale) 
						  == (SI_Long)4096L)
					      gensymed_symbol_2 = 
						      left_edge_of_grid;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  Current_image_x_scale) 
						  && 
						  FIXNUM_LT(Current_image_x_scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < left_edge_of_grid && 
						  left_edge_of_grid < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(Current_image_x_scale) 
						      * left_edge_of_grid 
						      + (SI_Long)2048L;
					      gensymed_symbol_2 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_2 = 
						      IFIX(scalef_function(Current_image_x_scale,
						      FIX(left_edge_of_grid)));
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 + 
						  gensymed_symbol_2;
					  gensymed_symbol_2 = 
						  IFIX(grid_border_width);
					  temp_1 = FIX(gensymed_symbol_1 + 
						  gensymed_symbol_2);
					  gensymed_symbol_1 = 
						  IFIX(Current_y_origin_of_drawing);
					  if (IFIX(Current_image_y_scale) 
						  == (SI_Long)4096L)
					      gensymed_symbol_2 = 
						      top_edge_of_grid;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  Current_image_y_scale) 
						  && 
						  FIXNUM_LT(Current_image_y_scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < top_edge_of_grid && 
						  top_edge_of_grid < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(Current_image_y_scale) 
						      * top_edge_of_grid + 
						      (SI_Long)2048L;
					      gensymed_symbol_2 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_2 = 
						      IFIX(scalef_function(Current_image_y_scale,
						      FIX(top_edge_of_grid)));
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 + 
						  gensymed_symbol_2;
					  gensymed_symbol_2 = 
						  IFIX(grid_border_width);
					  temp_2 = FIX(gensymed_symbol_1 + 
						  gensymed_symbol_2);
					  gensymed_symbol_1 = 
						  IFIX(Current_x_origin_of_drawing);
					  if (IFIX(Current_image_x_scale) 
						  == (SI_Long)4096L)
					      gensymed_symbol_2 = 
						      right_edge_of_grid;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  Current_image_x_scale) 
						  && 
						  FIXNUM_LT(Current_image_x_scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < right_edge_of_grid && 
						  right_edge_of_grid < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(Current_image_x_scale) 
						      * right_edge_of_grid 
						      + (SI_Long)2048L;
					      gensymed_symbol_2 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_2 = 
						      IFIX(scalef_function(Current_image_x_scale,
						      FIX(right_edge_of_grid)));
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 + 
						  gensymed_symbol_2;
					  gensymed_symbol_2 = 
						  IFIX(grid_border_width);
					  temp_3 = FIX(gensymed_symbol_1 - 
						  gensymed_symbol_2);
					  gensymed_symbol_1 = 
						  IFIX(Current_y_origin_of_drawing);
					  if (IFIX(Current_image_y_scale) 
						  == (SI_Long)4096L)
					      gensymed_symbol_2 = 
						      bottom_edge_of_grid;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  Current_image_y_scale) 
						  && 
						  FIXNUM_LT(Current_image_y_scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < bottom_edge_of_grid && 
						  bottom_edge_of_grid < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(Current_image_y_scale) 
						      * 
						      bottom_edge_of_grid 
						      + (SI_Long)2048L;
					      gensymed_symbol_2 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_2 = 
						      IFIX(scalef_function(Current_image_y_scale,
						      FIX(bottom_edge_of_grid)));
					  gensymed_symbol_1 = 
						  gensymed_symbol_1 + 
						  gensymed_symbol_2;
					  gensymed_symbol_2 = 
						  IFIX(grid_border_width);
					  draw_current_graph_rendering(temp_1,
						  temp_2,temp_3,
						  FIX(gensymed_symbol_1 - 
						  gensymed_symbol_2));
				      }
				      ISVREF(graph_grid,(SI_Long)52L) = 
					      Qscrolling;
				      gensymed_symbol = ISVREF(graph_grid,
					      (SI_Long)53L);
				      gensymed_symbol_3 = Current_image_plane;
				      if ( 
					      !TRUEP(memq_function(gensymed_symbol_3,
					      gensymed_symbol))) {
					  temp_1 = gensymed_symbol_3;
					  new_cons = 
						  ISVREF(Available_graph_conses_vector,
						  IFIX(Current_thread_index));
					  if (new_cons) {
					      temp = 
						      Available_graph_conses_vector;
					      svref_arg_2 = 
						      Current_thread_index;
					      svref_new_value = 
						      M_CDR(new_cons);
					      SVREF(temp,svref_arg_2) = 
						      svref_new_value;
					      if ( 
						      !TRUEP(ISVREF(Available_graph_conses_vector,
						      IFIX(Current_thread_index)))) 
							  {
						  temp = 
							  Available_graph_conses_tail_vector;
						  svref_arg_2 = 
							  Current_thread_index;
						  SVREF(temp,svref_arg_2) 
							  = Nil;
					      }
					      gensymed_symbol_4 = new_cons;
					  }
					  else
					      gensymed_symbol_4 = Nil;
					  if ( !TRUEP(gensymed_symbol_4))
					      gensymed_symbol_4 = 
						      replenish_graph_cons_pool();
					  M_CAR(gensymed_symbol_4) = 
						  gensymed_symbol_3;
					  M_CDR(gensymed_symbol_4) = 
						  gensymed_symbol;
					  inline_note_allocate_cons(gensymed_symbol_4,
						  Qgraph);
					  ISVREF(graph_grid,(SI_Long)53L) 
						  = gensymed_symbol_4;
					  result = VALUES_1(temp_1);
				      }
				      else
					  result = VALUES_1(Nil);
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
      else {
	  redraw_as_well_as_reformat_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		  0);
	    make_or_reformat_graph_grid(5,Nil,graph_grid,ISVREF(graph,
		    (SI_Long)22L),T,T);
	  POP_SPECIAL();
	  make_graph_not_up_to_date(graph_grid);
	  set_non_savable_lookup_slot_value(graph,
		  Qgraph_reformatted_since_start_qm,Nil);
	  draw_graph_grid_and_data(graph_grid, 
		  !TRUEP(memq_function(Current_image_plane,
		  ISVREF(graph_grid,(SI_Long)53L))) ? T : Nil);
	  gensymed_symbol = ISVREF(graph_grid,(SI_Long)53L);
	  gensymed_symbol_3 = Current_image_plane;
	  if ( !TRUEP(memq_function(gensymed_symbol_3,gensymed_symbol))) {
	      temp_1 = gensymed_symbol_3;
	      new_cons = ISVREF(Available_graph_conses_vector,
		      IFIX(Current_thread_index));
	      if (new_cons) {
		  temp = Available_graph_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  svref_new_value = M_CDR(new_cons);
		  SVREF(temp,svref_arg_2) = svref_new_value;
		  if ( !TRUEP(ISVREF(Available_graph_conses_vector,
			  IFIX(Current_thread_index)))) {
		      temp = Available_graph_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = Nil;
		  }
		  gensymed_symbol_4 = new_cons;
	      }
	      else
		  gensymed_symbol_4 = Nil;
	      if ( !TRUEP(gensymed_symbol_4))
		  gensymed_symbol_4 = replenish_graph_cons_pool();
	      M_CAR(gensymed_symbol_4) = gensymed_symbol_3;
	      M_CDR(gensymed_symbol_4) = gensymed_symbol;
	      inline_note_allocate_cons(gensymed_symbol_4,Qgraph);
	      ISVREF(graph_grid,(SI_Long)53L) = gensymed_symbol_4;
	      result = VALUES_1(temp_1);
	  }
	  else
	      result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    return result;
}

/* COMBINE-NEW-EXTREMA-WITH-EXISTING-ONES */
Object combine_new_extrema_with_existing_ones(extrema_rectangles_qm,min_x,
	    min_y,max_x,max_y)
    Object extrema_rectangles_qm, min_x, min_y, max_x, max_y;
{
    Object rectangles_to_combine, combined_min_x, combined_min_y;
    Object combined_max_x, combined_max_y, previous_rest_of_rectangles;
    Object rest_of_rectangles, rectangle_left_edge, rectangle_top_edge;
    Object rectangle_right_edge, rectangle_bottom_edge, rectangle_pointer;
    Object ab_loop_list_, rectangle_to_reclaim_head, cddddr_new_value;
    Object extrema_rectangles_head;

    x_note_fn_call(172,94);
    rectangles_to_combine = Nil;
    combined_min_x = min_x;
    combined_min_y = min_y;
    combined_max_x = max_x;
    combined_max_y = max_y;
    previous_rest_of_rectangles = Nil;
    rest_of_rectangles = extrema_rectangles_qm;
    rectangle_left_edge = Nil;
    rectangle_top_edge = Nil;
    rectangle_right_edge = Nil;
    rectangle_bottom_edge = Nil;
  next_loop:
    if ( !TRUEP(rest_of_rectangles))
	goto end_loop;
    rectangle_left_edge = FIRST(rest_of_rectangles);
    rectangle_top_edge = SECOND(rest_of_rectangles);
    rectangle_right_edge = THIRD(rest_of_rectangles);
    rectangle_bottom_edge = FOURTH(rest_of_rectangles);
    if ((FIXNUM_GE(rectangle_bottom_edge,max_y) && FIXNUM_GE(max_y,
	    rectangle_top_edge) || FIXNUM_GE(max_y,rectangle_bottom_edge) 
	    && FIXNUM_GE(rectangle_bottom_edge,min_y)) && 
	    (FIXNUM_GE(rectangle_right_edge,max_x) && FIXNUM_GE(max_x,
	    rectangle_left_edge) || FIXNUM_GE(max_x,rectangle_right_edge) 
	    && FIXNUM_GE(rectangle_right_edge,min_x))) {
	combined_min_x = FIXNUM_MIN(combined_min_x,rectangle_left_edge);
	combined_min_y = FIXNUM_MIN(combined_min_y,rectangle_top_edge);
	combined_max_x = FIXNUM_MAX(combined_max_x,rectangle_right_edge);
	combined_max_y = FIXNUM_MAX(combined_max_y,rectangle_bottom_edge);
	rectangles_to_combine = graph_cons_1(previous_rest_of_rectangles,
		rectangles_to_combine);
    }
    previous_rest_of_rectangles = rest_of_rectangles;
    rest_of_rectangles = nthcdr(FIX((SI_Long)4L),rest_of_rectangles);
    goto next_loop;
  end_loop:
    if (rectangles_to_combine) {
	rectangle_pointer = Nil;
	ab_loop_list_ = rectangles_to_combine;
	rectangle_to_reclaim_head = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	rectangle_pointer = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	rectangle_to_reclaim_head = nthcdr(FIX((SI_Long)4L),rectangle_pointer);
	if (rectangle_pointer) {
	    cddddr_new_value = nthcdr(FIX((SI_Long)8L),rectangle_pointer);
	    M_CDDDDR(rectangle_pointer) = cddddr_new_value;
	    M_CDDDDR(rectangle_to_reclaim_head) = Nil;
	    reclaim_graph_list_1(rectangle_to_reclaim_head);
	}
	else {
	    extrema_rectangles_head = extrema_rectangles_qm;
	    extrema_rectangles_qm = nthcdr(FIX((SI_Long)4L),
		    extrema_rectangles_qm);
	    M_CDDDDR(extrema_rectangles_head) = Nil;
	    reclaim_graph_list_1(extrema_rectangles_head);
	}
	goto next_loop_1;
      end_loop_1:;
	reclaim_graph_list_1(rectangles_to_combine);
	return graph_cons_1(combined_min_x,graph_cons_1(combined_min_y,
		graph_cons_1(combined_max_x,graph_cons_1(combined_max_y,
		extrema_rectangles_qm))));
    }
    else
	return graph_cons_1(min_x,graph_cons_1(min_y,graph_cons_1(max_x,
		graph_cons_1(max_y,extrema_rectangles_qm))));
    return VALUES_1(Qnil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qicon_description;   /* icon-description */

/* DRAW-DATA-POINT */
Object draw_data_point(x_on_graph,y_on_graph,previous_x_on_graph,
	    previous_y_on_graph,first_time_p,data_point_y_size,plot_marker_qm)
    Object x_on_graph, y_on_graph, previous_x_on_graph, previous_y_on_graph;
    Object first_time_p, data_point_y_size, plot_marker_qm;
{
    Object plot_marker_class, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp, temp_1, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object icon_description_qm, grid_and_erase_zone_width, dx1, dx, dy, dy1;
    Object y1_1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    double ratio;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(172,95);
    PUSH_SPECIAL_WITH_SYMBOL(Plot_marker_qm,Qplot_marker_qm,plot_marker_qm,0);
      if (CONSP(Plot_marker_qm)) {
	  plot_marker_class = CDR(Plot_marker_qm);
	  skip_list = CDR(Symbol_properties_table);
	  key_value = plot_marker_class;
	  key_hash_value = SXHASH_SYMBOL_1(plot_marker_class) & 
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
	  gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if ( !TRUEP(gensymed_symbol)) {
	      gensymed_symbol = plot_marker_class;
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
	  kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		  ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		  (SI_Long)3L) : Nil) : Nil;
	  if (kb_properties);
	  else
	      kb_properties = Nil;
	  if (kb_properties) {
	      skip_list = CDR(kb_properties);
	      key_value = Class_description_gkbprop;
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
	      key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) 
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
	  icon_description_qm = 
		  ISVREF(get_slot_description_of_class_description_function(Qicon_description,
		  gensymed_symbol,Nil),(SI_Long)6L);
	  if (icon_description_qm) {
	      temp = ISVREF(icon_description_qm,(SI_Long)1L);
	      temp_1 = FIX(IFIX(ISVREF(icon_description_qm,(SI_Long)2L)) 
		      >>  -  - (SI_Long)1L);
	      result = draw_plot_marker(plot_marker_class,x_on_graph,
		      y_on_graph,temp,temp_1,
		      get_erase_dateline_on_graph(Graph_grid_for_data));
	  }
	  else
	      result = VALUES_1(Qt);
      }
      else if (FIXNUM_LE(previous_x_on_graph,x_on_graph))
	  result = add_graph_line(first_time_p,previous_x_on_graph,
		  previous_y_on_graph,x_on_graph,y_on_graph);
      else {
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      grid_and_erase_zone_width = ISVREF(Graph_grid_for_data,
		      (SI_Long)59L);
	      dx1 = FIXNUM_MINUS(grid_and_erase_zone_width,
		      previous_x_on_graph);
	      dx = FIXNUM_ADD1(FIXNUM_ADD(x_on_graph,dx1));
	      dy = FIXNUM_MINUS(y_on_graph,previous_y_on_graph);
	      ratio = (double)IFIX(dy) / (double)IFIX(dx);
	      dy1 = l_round(DOUBLE_TO_DOUBLE_FLOAT(ratio * 
		      (double)IFIX(dx1)),_);
	      y1_1 = FIXNUM_ADD(previous_y_on_graph,dy1);
	      add_graph_line(first_time_p,previous_x_on_graph,
		      previous_y_on_graph,grid_and_erase_zone_width,y1_1);
	      add_graph_line(T,FIX((SI_Long)0L),y1_1,x_on_graph,y_on_graph);
	      if (Minimum_x_value_for_new_data) {
		  extend_extrema_if_necessary(grid_and_erase_zone_width,y1_1);
		  result = extend_extrema_if_necessary(FIX((SI_Long)0L),
			  y_on_graph);
	      }
	      else
		  result = VALUES_1(Nil);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
      }
    POP_SPECIAL();
    return result;
}

Object Offset_ratio_for_plot_markers = UNBOUND;

Object Default_marker_size = UNBOUND;

Object Default_marker_half_size = UNBOUND;

Object Plus_sign_marker_size = UNBOUND;

Object Plus_sign_marker_half_size = UNBOUND;

/* DRAW-PLOT-MARKER */
Object draw_plot_marker(plot_marker_qm,marker_x,marker_y,marker_size,
	    marker_half_size,erase_dateline_on_graph)
    Object plot_marker_qm, marker_x, marker_y, marker_size, marker_half_size;
    Object erase_dateline_on_graph;
{
    Object marker_left_edge, grid_and_erase_zone_width;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,96);
    PUSH_SPECIAL_WITH_SYMBOL(Plot_marker_qm,Qplot_marker_qm,plot_marker_qm,0);
      marker_left_edge = FIXNUM_MINUS(marker_x,marker_size);
      add_graph_marker(Plot_marker_qm,marker_x,marker_y);
      if ( !(IFIX(marker_left_edge) < (SI_Long)0L)) {
	  if ( !TRUEP(New_dateline_qm)) {
	      extend_minimum_x_value_if_necessary(marker_left_edge);
	      extend_minimum_y_value_if_necessary(FIXNUM_MINUS(marker_y,
		      marker_half_size));
	      result = extend_maximum_y_value_if_necessary(FIXNUM_ADD(marker_y,
		      marker_half_size));
	  }
	  else
	      result = VALUES_1(Nil);
      }
      else {
	  grid_and_erase_zone_width = ISVREF(Graph_grid_for_data,(SI_Long)59L);
	  if (FIXNUM_LT(marker_x,erase_dateline_on_graph))
	      add_graph_marker(Plot_marker_qm,FIXNUM_ADD(marker_x,
		      ISVREF(Graph_grid_for_data,(SI_Long)59L)),marker_y);
	  if ( !TRUEP(New_dateline_qm)) {
	      extend_minimum_x_value_if_necessary(FIX((SI_Long)0L));
	      extend_minimum_x_value_if_necessary(grid_and_erase_zone_width);
	      extend_minimum_y_value_if_necessary(FIXNUM_MINUS(marker_y,
		      marker_half_size));
	      result = extend_maximum_y_value_if_necessary(FIXNUM_ADD(marker_y,
		      marker_half_size));
	  }
	  else
	      result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    return result;
}

/* DRAW-DATA-FOR-PLOT */
Object draw_data_for_plot(data_buffer_for_plot,plot_data_point_begin_index,
	    plot_data_point_end_index,data_point_y_size,plot_color_qm,
	    plot_marker_qm,plot_shading_qm,plot_line_width_qm)
    Object data_buffer_for_plot, plot_data_point_begin_index;
    Object plot_data_point_end_index, data_point_y_size, plot_color_qm;
    Object plot_marker_qm, plot_shading_qm, plot_line_width_qm;
{
    Object previous_y_on_graph, previous_x_on_graph, plot_data_point_index;
    Object first_time_data_point_drawn_p, first_time_p, ab_loop_iter_flag_;
    Object managed_number_or_value, temp, temp_1, x_begin_value, y_value;
    Object extra_room, erase_dateline_on_graph, index_1, ab_loop_list_;
    Object marker_x, marker_y;
    SI_Long number_of_data_points_to_plot, count_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,97);
    PUSH_SPECIAL_WITH_SYMBOL(Plot_marker_qm,Qplot_marker_qm,plot_marker_qm,0);
      add_graph_color_to_use(plot_color_qm);
      add_graph_shading(plot_shading_qm);
      add_graph_line_width_to_use(plot_line_width_qm);
      data_point_y_size = Default_data_point_y_size;
      previous_y_on_graph = Nil;
      previous_x_on_graph = Nil;
      plot_data_point_index = plot_data_point_begin_index;
      first_time_data_point_drawn_p = T;
      number_of_data_points_to_plot = FIXNUM_GE(plot_data_point_end_index,
	      plot_data_point_begin_index) ? 
	      IFIX(FIXNUM_ADD1(FIXNUM_MINUS(plot_data_point_end_index,
	      plot_data_point_begin_index))) : 
	      IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(plot_data_point_end_index,
	      ISVREF(data_buffer_for_plot,(SI_Long)4L)),
	      plot_data_point_begin_index)));
      count_1 = (SI_Long)1L;
      ab_loop_bind_ = number_of_data_points_to_plot;
      first_time_p = T;
      ab_loop_iter_flag_ = T;
    next_loop:
      if (count_1 > ab_loop_bind_)
	  goto end_loop;
      if ( !TRUEP(ab_loop_iter_flag_))
	  first_time_p = Nil;
      managed_number_or_value = 
	      FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)6L),
	      (SI_Long)1L),Maximum_in_place_array_size) ? 
	      ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)6L),
	      IFIX(FIXNUM_ADD(plot_data_point_index,
	      Managed_array_index_offset))) : 
	      ISVREF(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)6L),
	      (IFIX(plot_data_point_index) >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),IFIX(plot_data_point_index) & (SI_Long)1023L);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	      (SI_Long)1L)
	  temp = 
		  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		  (SI_Long)0L));
      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	      (SI_Long)1L)
	  temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
      else if (text_string_p(managed_number_or_value))
	  temp = copy_text_string(managed_number_or_value);
      else
	  temp = managed_number_or_value;
      managed_number_or_value = 
	      FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
	      (SI_Long)1L),Maximum_in_place_array_size) ? 
	      ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
	      IFIX(FIXNUM_ADD(plot_data_point_index,
	      Managed_array_index_offset))) : 
	      ISVREF(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
	      (IFIX(plot_data_point_index) >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),IFIX(plot_data_point_index) & (SI_Long)1023L);
      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	      (SI_Long)1L)
	  temp_1 = 
		  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		  (SI_Long)0L));
      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
	      (SI_Long)0L && 
	      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	      (SI_Long)1L)
	  temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
      else if (text_string_p(managed_number_or_value))
	  temp_1 = copy_text_string(managed_number_or_value);
      else
	  temp_1 = managed_number_or_value;
      result = VALUES_2(temp,temp_1);
      MVS_2(result,x_begin_value,y_value);
      if ( !TRUEP(previous_x_on_graph)) {
	  previous_x_on_graph = x_begin_value;
	  previous_y_on_graph = y_value;
      }
      if ( !TRUEP(New_dateline_qm)) {
	  if (Minimum_x_value_for_new_data) {
	      if ( !TRUEP(plot_line_width_qm))
		  extend_extrema_if_necessary(x_begin_value,y_value);
	      else {
		  extra_room = ceiling(plot_line_width_qm,FIX((SI_Long)2L));
		  extend_extrema_if_necessary(x_begin_value,
			  FIXNUM_ADD(y_value,extra_room));
		  extend_extrema_if_necessary(x_begin_value,
			  FIXNUM_MINUS(y_value,extra_room));
	      }
	  }
	  else if (plot_shading_qm) {
	      store_new_data_extrema(x_begin_value,y_value);
	      extend_extrema_if_necessary(x_begin_value,Grid_height);
	  }
	  else if ( !TRUEP(plot_line_width_qm))
	      store_new_data_extrema(x_begin_value,y_value);
	  else {
	      extra_room = ceiling(plot_line_width_qm,FIX((SI_Long)2L));
	      store_new_data_extrema(x_begin_value,FIXNUM_ADD(y_value,
		      extra_room));
	      store_new_data_extrema(x_begin_value,FIXNUM_MINUS(y_value,
		      extra_room));
	  }
      }
      plot_data_point_index = FIXNUM_EQ(plot_data_point_index,
	      FIXNUM_SUB1(ISVREF(data_buffer_for_plot,(SI_Long)4L))) ? 
	      FIX((SI_Long)0L) : FIXNUM_ADD1(plot_data_point_index);
      if (ISVREF(data_buffer_for_plot,(SI_Long)12L) ||  !TRUEP(first_time_p)) {
	  draw_data_point(x_begin_value,y_value,previous_x_on_graph,
		  previous_y_on_graph,first_time_data_point_drawn_p,
		  data_point_y_size,Plot_marker_qm);
	  first_time_data_point_drawn_p = Nil;
      }
      previous_x_on_graph = x_begin_value;
      previous_y_on_graph = y_value;
      ab_loop_iter_flag_ = Nil;
      count_1 = count_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      if (Plot_marker_qm && SYMBOLP(Plot_marker_qm)) {
	  erase_dateline_on_graph = 
		  get_erase_dateline_on_graph(Graph_grid_for_data);
	  index_1 = Nil;
	  ab_loop_list_ = ISVREF(data_buffer_for_plot,(SI_Long)11L);
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  index_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  managed_number_or_value = 
		  FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,
		  (SI_Long)6L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)6L),
		  IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		  ISVREF(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)6L),
		  (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		  IFIX(index_1) & (SI_Long)1023L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      temp = copy_text_string(managed_number_or_value);
	  else
	      temp = managed_number_or_value;
	  managed_number_or_value = 
		  FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,
		  (SI_Long)7L),(SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
		  IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		  ISVREF(ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
		  (IFIX(index_1) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		  IFIX(index_1) & (SI_Long)1023L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      temp_1 = copy_text_string(managed_number_or_value);
	  else
	      temp_1 = managed_number_or_value;
	  result = VALUES_2(temp,temp_1);
	  MVS_2(result,marker_x,marker_y);
	  draw_plot_marker(Plot_marker_qm,marker_x,marker_y,
		  Plus_sign_marker_size,Plus_sign_marker_half_size,
		  erase_dateline_on_graph);
	  goto next_loop_1;
	end_loop_1:
	  result = VALUES_1(Qnil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qsolid_rectangle;    /* solid-rectangle */

/* ADD-GRAPH-RECTANGLE */
Object add_graph_rectangle(left_edge_of_rectangle_in_raster,
	    top_edge_of_rectangle_in_raster,
	    right_edge_of_rectangle_in_raster,
	    bottom_edge_of_rectangle_in_raster)
    Object left_edge_of_rectangle_in_raster, top_edge_of_rectangle_in_raster;
    Object right_edge_of_rectangle_in_raster;
    Object bottom_edge_of_rectangle_in_raster;
{
    x_note_fn_call(172,98);
    return add_form_to_graph_line_drawing_description(graph_list_3(Qsolid_rectangle,
	    graph_list_2(left_edge_of_rectangle_in_raster,
	    top_edge_of_rectangle_in_raster),
	    graph_list_2(right_edge_of_rectangle_in_raster,
	    bottom_edge_of_rectangle_in_raster)));
}

static Object Qclear_solid_rectangle;  /* clear-solid-rectangle */

/* ADD-GRAPH-CLEAR-RECTANGLE */
Object add_graph_clear_rectangle(left_edge_of_rectangle_in_raster,
	    top_edge_of_rectangle_in_raster,
	    right_edge_of_rectangle_in_raster,
	    bottom_edge_of_rectangle_in_raster)
    Object left_edge_of_rectangle_in_raster, top_edge_of_rectangle_in_raster;
    Object right_edge_of_rectangle_in_raster;
    Object bottom_edge_of_rectangle_in_raster;
{
    x_note_fn_call(172,99);
    return add_form_to_graph_line_drawing_description(graph_list_3(Qclear_solid_rectangle,
	    graph_list_2(left_edge_of_rectangle_in_raster,
	    top_edge_of_rectangle_in_raster),
	    graph_list_2(right_edge_of_rectangle_in_raster,
	    bottom_edge_of_rectangle_in_raster)));
}

static Object Qgraph_dateline;     /* graph-dateline */

/* ADD-GRAPH-NEW-DATELINE */
Object add_graph_new_dateline(dateline_in_raster,erase_dateline_in_raster)
    Object dateline_in_raster, erase_dateline_in_raster;
{
    x_note_fn_call(172,100);
    return add_form_to_graph_line_drawing_description(graph_list_2(Qgraph_dateline,
	    graph_list_2(dateline_in_raster,erase_dateline_in_raster)));
}

static Object Qdata_extrema;       /* data-extrema */

/* ADD-GRAPH-DATA-EXTREMA */
Object add_graph_data_extrema(extrema_rectangles)
    Object extrema_rectangles;
{
    x_note_fn_call(172,101);
    return add_form_to_graph_line_drawing_description(graph_list_2(Qdata_extrema,
	    extrema_rectangles));
}

static Object Qlines;              /* lines */

/* ADD-GRAPH-LINE */
Object add_graph_line(start_new_line_qm,x1,y1_1,x2,y2)
    Object start_new_line_qm, x1, y1_1, x2, y2;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(172,102);
    if ( !TRUEP(ISVREF(Graph_grid_for_data,(SI_Long)58L))) {
	temp = Graph_grid_for_data;
	temp_1 = ISVREF(Graph_grid_for_data,(SI_Long)56L);
	ISVREF(temp,(SI_Long)58L) = temp_1;
    }
    if ( !TRUEP(start_new_line_qm)) {
	temp = ISVREF(Graph_grid_for_data,(SI_Long)58L);
	temp_1 = graph_cons_1(graph_list_2(x2,y2),Nil);
	M_CDR(temp) = temp_1;
	temp = Graph_grid_for_data;
	temp_2 = ISVREF(Graph_grid_for_data,(SI_Long)58L);
	temp_1 = CDR(temp_2);
	return VALUES_1(ISVREF(temp,(SI_Long)58L) = temp_1);
    }
    else {
	temp = ISVREF(Graph_grid_for_data,(SI_Long)57L);
	temp_1 = graph_cons_1(graph_list_3(Qlines,graph_list_2(x1,y1_1),
		graph_list_2(x2,y2)),Nil);
	M_CDR(temp) = temp_1;
	temp = Graph_grid_for_data;
	temp_2 = ISVREF(Graph_grid_for_data,(SI_Long)57L);
	temp_1 = CDR(temp_2);
	ISVREF(temp,(SI_Long)57L) = temp_1;
	temp = Graph_grid_for_data;
	temp_2 = ISVREF(Graph_grid_for_data,(SI_Long)57L);
	temp_1 = CDDAR(temp_2);
	return VALUES_1(ISVREF(temp,(SI_Long)58L) = temp_1);
    }
}

static Object Qclear_graph;        /* clear-graph */

/* ADD-GRAPH-CLEAR */
Object add_graph_clear()
{
    x_note_fn_call(172,103);
    return add_form_to_graph_line_drawing_description(graph_cons_1(Qclear_graph,
	    Nil));
}

static Object Qgraph_color_to_use;  /* graph-color-to-use */

/* ADD-GRAPH-COLOR-TO-USE */
Object add_graph_color_to_use(color)
    Object color;
{
    x_note_fn_call(172,104);
    return add_form_to_graph_line_drawing_description(graph_list_2(Qgraph_color_to_use,
	    color));
}

static Object Qgraph_shading_qm;   /* graph-shading? */

/* ADD-GRAPH-SHADING */
Object add_graph_shading(shading_qm)
    Object shading_qm;
{
    x_note_fn_call(172,105);
    return add_form_to_graph_line_drawing_description(graph_list_2(Qgraph_shading_qm,
	    shading_qm));
}

static Object Qgraph_line_width_to_use;  /* graph-line-width-to-use */

/* ADD-GRAPH-LINE-WIDTH-TO-USE */
Object add_graph_line_width_to_use(line_width_qm)
    Object line_width_qm;
{
    x_note_fn_call(172,106);
    return add_form_to_graph_line_drawing_description(graph_list_2(Qgraph_line_width_to_use,
	    line_width_qm));
}

static Object Qgraph_marker;       /* graph-marker */

/* ADD-GRAPH-MARKER */
Object add_graph_marker(plot_marker,x_position,y_position)
    Object plot_marker, x_position, y_position;
{
    x_note_fn_call(172,107);
    return add_form_to_graph_line_drawing_description(graph_list_4(Qgraph_marker,
	    plot_marker,x_position,y_position));
}

/* ADD-FORM-TO-GRAPH-LINE-DRAWING-DESCRIPTION */
Object add_form_to_graph_line_drawing_description(form)
    Object form;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(172,108);
    temp = ISVREF(Graph_grid_for_data,(SI_Long)57L);
    temp_1 = graph_cons_1(form,Nil);
    M_CDR(temp) = temp_1;
    temp = Graph_grid_for_data;
    temp_2 = ISVREF(Graph_grid_for_data,(SI_Long)57L);
    temp_1 = CDR(temp_2);
    return VALUES_1(ISVREF(temp,(SI_Long)57L) = temp_1);
}

/* UPDATE-GRAPH-RENDERING */
Object update_graph_rendering()
{
    Object temp, svref_arg_1, svref_new_value;

    x_note_fn_call(172,109);
    temp = ISVREF(Graph_grid_for_data,(SI_Long)56L);
    if (CDR(temp)) {
	svref_arg_1 = Current_graph_rendering;
	svref_new_value = ISVREF(Graph_grid_for_data,(SI_Long)56L);
	SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
	return paint_graph_rendering_raster();
    }
    else
	return VALUES_1(Nil);
}

/* PAINT-GRAPH-FROM-GRAPH-RENDERING */
Object paint_graph_from_graph_rendering(graph_rendering,
	    foreground_color_value_qm,first_time_qm)
    Object graph_rendering, foreground_color_value_qm, first_time_qm;
{
    x_note_fn_call(172,110);
    return paint_graph_on_scratchpad_raster(first_time_qm,
	    foreground_color_value_qm,ISVREF(graph_rendering,(SI_Long)8L),
	    ISVREF(graph_rendering,(SI_Long)14L),ISVREF(graph_rendering,
	    (SI_Long)15L),ISVREF(graph_rendering,(SI_Long)3L),
	    ISVREF(graph_rendering,(SI_Long)4L));
}

/* UPDATE-COLORS-OF-CURRENT-GRAPH-RENDERING */
Object update_colors_of_current_graph_rendering()
{
    x_note_fn_call(172,111);
    if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
	    Qmonochrome_raster_list))
	return update_ring_raster_for_graph_given_color_values_2(Current_graph_rendering,
		ISVREF(Current_graph_rendering,(SI_Long)10L));
    else
	return update_ring_raster_for_graph_given_color_values(Current_graph_rendering,
		length(ISVREF(Current_graph_rendering,(SI_Long)10L)));
}

/* PAINT-GRAPH-RENDERING-RASTER */
Object paint_graph_rendering_raster()
{
    x_note_fn_call(172,112);
    if (native_printing_p() &&  
	    !TRUEP(Bogus_preflight_from_printing_to_graphs))
	return paint_graph_to_native_printer(Current_graph_rendering);
    else
	return paint_graph_rendering_raster_1();
}

static Object Qicp;                /* icp */

/* PAINT-GRAPH-RENDERING-RASTER-1 */
Object paint_graph_rendering_raster_1()
{
    Object current_scratchpad_raster_type;
    Object foreground_color_value_for_current_raster, ab_loop_list_;
    Object first_time_qm, ab_loop_iter_flag_;
    Object current_graph_rendering_structure;
    Object paint_only_target_monochrome_raster_p, stored_raster, minimum_width;
    Object minimum_height, current_scratchpad_raster;
    Object current_scratchpad_raster_tiled_p, current_scratchpad_raster_width;
    Object current_scratchpad_raster_height, current_scratchpad_raster_depth;
    Object on_monochrome_raster_list_p, list_of_stored_rasters;
    Object color_value_list, current_scratchpad_raster_list;
    Object current_scratchpad_color_value_list, stored_raster_1;
    Object ab_loop_list__1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(11);
    Object result;

    x_note_fn_call(172,113);
    SAVE_STACK();
    if (EQ(Type_of_current_window,Qicp)) {
	current_scratchpad_raster_type = Qicp;
	PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
		0);
	  if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		  Qmonochrome_raster_list))
	      update_ring_raster_for_graph_given_color_values_2(Current_graph_rendering,
		      ISVREF(Current_graph_rendering,(SI_Long)10L));
	  else
	      update_ring_raster_for_graph_given_color_values(Current_graph_rendering,
		      length(ISVREF(Current_graph_rendering,(SI_Long)10L)));
	  send_icp_prepare_for_painting_graph(Current_graph_rendering);
	  if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		  Qpolychrome_raster) || EQ(ISVREF(Current_graph_rendering,
		  (SI_Long)6L),Qmonochrome_raster_list)) {
	      paint_graph_from_graph_rendering(Current_graph_rendering,Nil,T);
	      result = send_icp_end_message_block();
	  }
	  else {
	      foreground_color_value_for_current_raster = Nil;
	      ab_loop_list_ = ISVREF(Current_graph_rendering,(SI_Long)10L);
	      first_time_qm = T;
	      ab_loop_iter_flag_ = T;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      foreground_color_value_for_current_raster = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_iter_flag_))
		  first_time_qm = Nil;
	      paint_graph_from_graph_rendering(Current_graph_rendering,
		      foreground_color_value_for_current_raster,first_time_qm);
	      send_icp_end_message_block();
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop;
	    end_loop:
	      result = VALUES_1(Qnil);
	  }
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	make_graph_rendering_structure_if_necessary(Current_graph_rendering);
	current_graph_rendering_structure = ISVREF(Current_graph_rendering,
		(SI_Long)7L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_graph_rendering_structure,Qcurrent_graph_rendering_structure,current_graph_rendering_structure,
		10);
	  if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		  Qmonochrome_raster_list))
	      update_ring_raster_for_graph_given_color_values_2(Current_graph_rendering,
		      ISVREF(Current_graph_rendering,(SI_Long)10L));
	  else
	      update_ring_raster_for_graph_given_color_values(Current_graph_rendering,
		      length(ISVREF(Current_graph_rendering,(SI_Long)10L)));
	  paint_only_target_monochrome_raster_p = 
		  ISVREF(Current_graph_rendering,(SI_Long)19L);
	  PUSH_SPECIAL_WITH_SYMBOL(Paint_only_target_monochrome_raster_p,Qpaint_only_target_monochrome_raster_p,paint_only_target_monochrome_raster_p,
		  9);
	    if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		    Qpolychrome_raster)) {
		stored_raster = ISVREF(Current_graph_rendering_structure,
			(SI_Long)1L);
		minimum_width = FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)12L));
		minimum_height = 
			FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)13L));
		LOCK(Scratchpad_raster);
		if (PUSH_UNWIND_PROTECT(0)) {
		    current_scratchpad_raster_type = ISVREF(Current_window,
			    (SI_Long)23L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			    6);
		      current_scratchpad_raster = stored_raster;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
			      5);
			current_scratchpad_raster_tiled_p = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
				4);
			  current_scratchpad_raster_width = minimum_width;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
				  3);
			    current_scratchpad_raster_height = minimum_height;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
				    2);
			      current_scratchpad_raster_depth = 
				      FIX((SI_Long)8L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				      1);
				on_monochrome_raster_list_p = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
					0);
				  paint_graph_from_graph_rendering(Current_graph_rendering,
					  Nil,T);
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
		UNLOCK(Scratchpad_raster);
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
	    }
	    else if (EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
		    Qmonochrome_raster_list)) {
		list_of_stored_rasters = 
			ISVREF(Current_graph_rendering_structure,(SI_Long)1L);
		color_value_list = 
			ISVREF(Current_graph_rendering_structure,(SI_Long)4L);
		minimum_width = FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)12L));
		minimum_height = 
			FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)13L));
		LOCK(Scratchpad_raster);
		if (PUSH_UNWIND_PROTECT(0)) {
		    current_scratchpad_raster_type = ISVREF(Current_window,
			    (SI_Long)23L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			    8);
		      current_scratchpad_raster_tiled_p = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			      7);
			current_scratchpad_raster_width = minimum_width;
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
				6);
			  current_scratchpad_raster_height = minimum_height;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
				  5);
			    current_scratchpad_raster_depth = FIX((SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				    4);
			      on_monochrome_raster_list_p = T;
			      PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
				      3);
				current_scratchpad_raster_list = 
					list_of_stored_rasters;
				PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_list,Qcurrent_scratchpad_raster_list,current_scratchpad_raster_list,
					2);
				  current_scratchpad_color_value_list = 
					  color_value_list;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_color_value_list,Qcurrent_scratchpad_color_value_list,current_scratchpad_color_value_list,
					  1);
				    current_scratchpad_raster = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
					    0);
				      SAVE_VALUES(paint_graph_from_graph_rendering(Current_graph_rendering,
					      Nil,T));
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
		UNLOCK(Scratchpad_raster);
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
	    }
	    else {
		stored_raster_1 = Nil;
		ab_loop_list_ = ISVREF(Current_graph_rendering_structure,
			(SI_Long)1L);
		foreground_color_value_for_current_raster = Nil;
		ab_loop_list__1 = ISVREF(Current_graph_rendering,(SI_Long)10L);
		first_time_qm = T;
		ab_loop_iter_flag_ = T;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		stored_raster_1 = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		foreground_color_value_for_current_raster = 
			M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    first_time_qm = Nil;
		minimum_width = FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)12L));
		minimum_height = 
			FIXNUM_ADD1(ISVREF(Current_graph_rendering,
			(SI_Long)13L));
		LOCK(Scratchpad_raster);
		if (PUSH_UNWIND_PROTECT(0)) {
		    current_scratchpad_raster_type = ISVREF(Current_window,
			    (SI_Long)23L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_type,Qcurrent_scratchpad_raster_type,current_scratchpad_raster_type,
			    6);
		      current_scratchpad_raster = stored_raster_1;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster,Qcurrent_scratchpad_raster,current_scratchpad_raster,
			      5);
			current_scratchpad_raster_tiled_p = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_tiled_p,Qcurrent_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
				4);
			  current_scratchpad_raster_width = minimum_width;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_width,Qcurrent_scratchpad_raster_width,current_scratchpad_raster_width,
				  3);
			    current_scratchpad_raster_height = minimum_height;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_height,Qcurrent_scratchpad_raster_height,current_scratchpad_raster_height,
				    2);
			      current_scratchpad_raster_depth = 
				      FIX((SI_Long)1L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_scratchpad_raster_depth,Qcurrent_scratchpad_raster_depth,current_scratchpad_raster_depth,
				      1);
				on_monochrome_raster_list_p = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(On_monochrome_raster_list_p,Qon_monochrome_raster_list_p,on_monochrome_raster_list_p,
					0);
				  paint_graph_from_graph_rendering(Current_graph_rendering,
					  foreground_color_value_for_current_raster,
					  first_time_qm);
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Scratchpad_raster);
		CONTINUE_UNWINDING(0);
		ab_loop_iter_flag_ = Nil;
		goto next_loop_1;
	      end_loop_1:
		result = VALUES_1(Qnil);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
}

/* MAKE-GRAPH-RENDERING-STRUCTURE-IF-NECESSARY */
Object make_graph_rendering_structure_if_necessary(graph_rendering)
    Object graph_rendering;
{
    Object svref_new_value;

    x_note_fn_call(172,114);
    if ( !TRUEP(ISVREF(graph_rendering,(SI_Long)7L))) {
	svref_new_value = 
		make_graph_rendering_structure(ISVREF(graph_rendering,
		(SI_Long)12L));
	return VALUES_1(SVREF(graph_rendering,FIX((SI_Long)7L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* PAINT-GRAPH-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object paint_graph_line_in_current_scratchpad_raster(x1,y1_1,x2,y2,
	    graph_line_color_value,shading_qm,line_width_qm)
    Object x1, y1_1, x2, y2, graph_line_color_value, shading_qm, line_width_qm;
{
    x_note_fn_call(172,115);
    if (shading_qm)
	return paint_shaded_line_in_current_scratchpad_raster(x1,y1_1,x2,
		y2,graph_line_color_value);
    else if (line_width_qm)
	return paint_wide_line_in_current_scratchpad_raster(x1,y1_1,x2,y2,
		graph_line_color_value,T,line_width_qm);
    else
	return paint_line_in_current_scratchpad_raster(x1,y1_1,x2,y2,
		graph_line_color_value,T);
}

static Object Qchart_call_back;    /* chart-call-back */

static Object Q2d_call_back_full;  /* 2d-call-back-full */

static Object Q2d_call_back_partial;  /* 2d-call-back-partial */

/* PAINT-GRAPH-ON-SCRATCHPAD-RASTER */
Object paint_graph_on_scratchpad_raster(first_time_qm,
	    foreground_color_value_qm,line_drawing_description,width,
	    height,x_scale,y_scale)
    Object first_time_qm, foreground_color_value_qm, line_drawing_description;
    Object width, height, x_scale, y_scale;
{
    Object graph_fill_color_value, graph_line_color_value, burning_qm;
    Object shading_qm, scaled_line_width_qm, description_element;
    Object ab_loop_list_, description_command, points, temp, temp_1, temp_2;
    Object temp_3, remaining_points, x1, y1_1, x2, y2, x1_scaled, y1_scaled;
    Object x2_scaled, y2_scaled, x3_scaled_qm, y3_scaled_qm;
    Object ab_loop_iter_flag_, scale, value, left_edge_in_window;
    Object top_edge_in_window, right_edge_in_window, bottom_edge_in_window;
    Object rest_of_rectangles;
    SI_Long unshifted_result, number_of_actual_paints, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char graph_rendering_uses_polychrome_rasters_qm;
    char graph_rendering_uses_monochrome_raster_lists_qm;

    x_note_fn_call(172,116);
    graph_rendering_uses_polychrome_rasters_qm = 
	    EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),Qpolychrome_raster);
    graph_rendering_uses_monochrome_raster_lists_qm = 
	    EQ(ISVREF(Current_graph_rendering,(SI_Long)6L),
	    Qmonochrome_raster_list);
    graph_fill_color_value = graph_rendering_uses_polychrome_rasters_qm || 
	    graph_rendering_uses_monochrome_raster_lists_qm ? 
	    ISVREF(Current_graph_rendering,(SI_Long)9L) : Nil;
    if (graph_fill_color_value);
    else
	graph_fill_color_value = FIX((SI_Long)0L);
    graph_line_color_value = FIX((SI_Long)1L);
    burning_qm = Nil;
    shading_qm = Nil;
    scaled_line_width_qm = Nil;
    description_element = Nil;
    ab_loop_list_ = CDR(line_drawing_description);
    description_command = Nil;
    points = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    description_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    description_command = FIRST(description_element);
    points =  !(EQ(description_command,Qgraph_color_to_use) || 
	    EQ(description_command,Qgraph_marker) || 
	    EQ(description_command,Qgraph_shading_qm) || 
	    EQ(description_command,Qgraph_line_width_to_use)) ? 
	    CDR(description_element) : Nil;
    if (EQ(description_command,Qclear_graph)) {
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp = FIX((SI_Long)0L);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < (SI_Long)0L 
		&& (SI_Long)0L < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(x_scale) * (SI_Long)0L + (SI_Long)2048L;
	    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp = scalef_function(x_scale,FIX((SI_Long)0L));
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_1 = FIX((SI_Long)0L);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < (SI_Long)0L 
		&& (SI_Long)0L < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(y_scale) * (SI_Long)0L + (SI_Long)2048L;
	    temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_1 = scalef_function(y_scale,FIX((SI_Long)0L));
	if (IFIX(x_scale) == (SI_Long)4096L)
	    temp_2 = width;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x_scale) 
		&& FIXNUM_LT(x_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,width) && 
		FIXNUM_LT(width,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(x_scale,width)) + 
		    (SI_Long)2048L;
	    temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_2 = scalef_function(x_scale,width);
	if (IFIX(y_scale) == (SI_Long)4096L)
	    temp_3 = height;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) 
		&& FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,height) 
		&& FIXNUM_LT(height,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(y_scale,height)) + 
		    (SI_Long)2048L;
	    temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    temp_3 = scalef_function(y_scale,height);
	paint_solid_rectangle_in_current_scratchpad_raster(temp,temp_1,
		temp_2,temp_3,graph_fill_color_value);
    }
    else if (EQ(description_command,Qlines)) {
	remaining_points = points;
	x1 = Nil;
	y1_1 = Nil;
	x2 = Nil;
	y2 = Nil;
	x1_scaled = Nil;
	y1_scaled = Nil;
	x2_scaled = Nil;
	y2_scaled = Nil;
	x3_scaled_qm = Nil;
	y3_scaled_qm = Nil;
	number_of_actual_paints = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop_1:
	temp = CAR(remaining_points);
	x1 = CAR(temp);
	temp = CAR(remaining_points);
	temp = CDR(temp);
	y1_1 = CAR(temp);
	temp = CDR(remaining_points);
	temp = CAR(temp);
	x2 = CAR(temp);
	temp = CDR(remaining_points);
	temp = CAR(temp);
	temp = CDR(temp);
	y2 = CAR(temp);
	if (ab_loop_iter_flag_) {
	    if (IFIX(x_scale) == (SI_Long)4096L)
		x1_scaled = x1;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x1) 
		    && FIXNUM_LT(x1,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x1)) + 
			(SI_Long)2048L;
		x1_scaled = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		x1_scaled = scalef_function(x_scale,x1);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		y1_scaled = y1_1;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y1_1) 
		    && FIXNUM_LT(y1_1,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y1_1)) + 
			(SI_Long)2048L;
		y1_scaled = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		y1_scaled = scalef_function(y_scale,y1_1);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		x2_scaled = x2;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x2) 
		    && FIXNUM_LT(x2,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x2)) + 
			(SI_Long)2048L;
		x2_scaled = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		x2_scaled = scalef_function(x_scale,x2);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		y2_scaled = y2;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y2) 
		    && FIXNUM_LT(y2,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y2)) + 
			(SI_Long)2048L;
		y2_scaled = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		y2_scaled = scalef_function(y_scale,y2);
	}
	else {
	    x1_scaled = x2_scaled;
	    y1_scaled = y2_scaled;
	    x2_scaled = x3_scaled_qm;
	    y2_scaled = y3_scaled_qm;
	}
	if (CDDR(remaining_points)) {
	    scale = x_scale;
	    temp = CDDR(remaining_points);
	    temp = FIRST(temp);
	    value = FIRST(temp);
	    if (IFIX(scale) == (SI_Long)4096L)
		x3_scaled_qm = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		x3_scaled_qm = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		x3_scaled_qm = scalef_function(scale,value);
	}
	else
	    x3_scaled_qm = Nil;
	if (CDDR(remaining_points)) {
	    scale = y_scale;
	    temp = CDDR(remaining_points);
	    temp = FIRST(temp);
	    value = SECOND(temp);
	    if (IFIX(scale) == (SI_Long)4096L)
		y3_scaled_qm = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		y3_scaled_qm = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		y3_scaled_qm = scalef_function(scale,value);
	}
	else
	    y3_scaled_qm = Nil;
	if (FIXNUM_EQ(x1_scaled,x2_scaled) && FIXNUM_EQ(y1_scaled,y2_scaled))
	    temp = Nil;
	else if (y3_scaled_qm && FIXNUM_EQ(y1_scaled,y2_scaled) && 
		FIXNUM_EQ(y3_scaled_qm,y2_scaled)) {
	    x2_scaled = x1_scaled;
	    temp = Nil;
	}
	else if (x3_scaled_qm && FIXNUM_EQ(x1_scaled,x2_scaled) && 
		FIXNUM_EQ(x3_scaled_qm,x2_scaled)) {
	    y2_scaled = y1_scaled;
	    temp = Nil;
	}
	else if (x3_scaled_qm && y3_scaled_qm && 
		FIXNUM_EQ(FIXNUM_TIMES(FIXNUM_MINUS(y1_scaled,
		y3_scaled_qm),FIXNUM_MINUS(x1_scaled,x2_scaled)),
		FIXNUM_TIMES(FIXNUM_MINUS(x1_scaled,x3_scaled_qm),
		FIXNUM_MINUS(y1_scaled,y2_scaled)))) {
	    x2_scaled = x1_scaled;
	    y2_scaled = y1_scaled;
	    temp = Nil;
	}
	else {
	    paint_graph_line_in_current_scratchpad_raster(x1_scaled,
		    y1_scaled,x2_scaled,y2_scaled,graph_line_color_value,
		    shading_qm,scaled_line_width_qm);
	    temp = T;
	}
	if (temp)
	    number_of_actual_paints = number_of_actual_paints + (SI_Long)1L;
	if ( !TRUEP(CDDR(remaining_points)))
	    goto end_loop_1;
	ab_loop_iter_flag_ = Nil;
	remaining_points = CDR(remaining_points);
	goto next_loop_1;
      end_loop_1:
      nil:;
    }
    else if (EQ(description_command,Qsolid_rectangle) || 
	    EQ(description_command,Qclear_solid_rectangle)) {
	scale = x_scale;
	temp = FIRST(points);
	value = FIRST(temp);
	if (IFIX(scale) == (SI_Long)4096L)
	    left_edge_in_window = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    left_edge_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    left_edge_in_window = scalef_function(scale,value);
	scale = y_scale;
	temp = FIRST(points);
	value = SECOND(temp);
	if (IFIX(scale) == (SI_Long)4096L)
	    top_edge_in_window = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    top_edge_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    top_edge_in_window = scalef_function(scale,value);
	scale = x_scale;
	temp = SECOND(points);
	value = FIRST(temp);
	if (IFIX(scale) == (SI_Long)4096L)
	    right_edge_in_window = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    right_edge_in_window = FIX(unshifted_result >>  -  - (SI_Long)12L);
	}
	else
	    right_edge_in_window = scalef_function(scale,value);
	scale = y_scale;
	temp = SECOND(points);
	value = SECOND(temp);
	if (IFIX(scale) == (SI_Long)4096L)
	    bottom_edge_in_window = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    bottom_edge_in_window = FIX(unshifted_result >>  -  - 
		    (SI_Long)12L);
	}
	else
	    bottom_edge_in_window = scalef_function(scale,value);
	if (EQ(description_command,Qsolid_rectangle)) {
	    temp = FIXNUM_ADD1(left_edge_in_window);
	    temp = FIXNUM_MAX(right_edge_in_window,temp);
	}
	else
	    temp = right_edge_in_window;
	if (EQ(description_command,Qsolid_rectangle)) {
	    temp_1 = FIXNUM_ADD1(top_edge_in_window);
	    temp_1 = FIXNUM_MAX(bottom_edge_in_window,temp_1);
	}
	else
	    temp_1 = bottom_edge_in_window;
	paint_solid_rectangle_in_current_scratchpad_raster(left_edge_in_window,
		top_edge_in_window,temp,temp_1,EQ(description_command,
		Qsolid_rectangle) ? graph_line_color_value : 
		graph_fill_color_value);
    }
    else if (EQ(description_command,Qgraph_marker))
	paint_plot_marker(CDR(description_element),graph_line_color_value,
		x_scale,y_scale);
    else if (EQ(description_command,Qgraph_dateline)) {
	if (first_time_qm) {
	    scale = x_scale;
	    temp = FIRST(points);
	    value = FIRST(temp);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(scale,value);
	    scale = x_scale;
	    temp_1 = FIRST(points);
	    value = SECOND(temp_1);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(scale,value);
	    update_graph_dateline(temp,temp_1,Current_graph_rendering);
	}
    }
    else if (EQ(description_command,Qdata_extrema)) {
	if ( !TRUEP(burning_qm) || 
		graph_rendering_uses_monochrome_raster_lists_qm) {
	    rest_of_rectangles = FIRST(points);
	  next_loop_2:
	    if ( !TRUEP(rest_of_rectangles))
		goto end_loop_2;
	    scale = x_scale;
	    value = FIRST(rest_of_rectangles);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(scale,value);
	    scale = y_scale;
	    value = SECOND(rest_of_rectangles);
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(scale,value);
	    scale = x_scale;
	    value = THIRD(rest_of_rectangles);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = (SI_Long)1L;
	    temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	    scale = y_scale;
	    value = FOURTH(rest_of_rectangles);
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol = IFIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol = IFIX(scalef_function(scale,value));
	    gensymed_symbol_1 = (SI_Long)1L;
	    update_graph_data_extrema(temp,temp_1,temp_2,
		    FIX(gensymed_symbol + gensymed_symbol_1));
	    rest_of_rectangles = nthcdr(FIX((SI_Long)4L),rest_of_rectangles);
	    goto next_loop_2;
	  end_loop_2:;
	}
    }
    else if (EQ(description_command,Qgraph_color_to_use)) {
	if (graph_rendering_uses_polychrome_rasters_qm || 
		graph_rendering_uses_monochrome_raster_lists_qm)
	    graph_line_color_value = 
		    color_value_given_color_or_default(SECOND(description_element));
	else {
	    temp = 
		    color_value_given_color_or_default(SECOND(description_element));
	    if ( !EQL(temp,foreground_color_value_qm)) {
		graph_line_color_value = FIX((SI_Long)0L);
		burning_qm = T;
	    }
	    else {
		graph_line_color_value = FIX((SI_Long)1L);
		burning_qm = Nil;
	    }
	}
    }
    else if (EQ(description_command,Qgraph_shading_qm))
	shading_qm = SECOND(description_element);
    else if (EQ(description_command,Qgraph_line_width_to_use)) {
	if (SECOND(description_element)) {
	    scale = x_scale;
	    value = SECOND(description_element);
	    if (IFIX(scale) == (SI_Long)4096L)
		scaled_line_width_qm = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			(SI_Long)2048L;
		scaled_line_width_qm = FIX(unshifted_result >>  -  - 
			(SI_Long)12L);
	    }
	    else
		scaled_line_width_qm = scalef_function(scale,value);
	}
	else
	    scaled_line_width_qm = Nil;
    }
    else if (EQ(description_command,Qchart_call_back))
	project_chart_call_back(Current_graph_rendering,
		foreground_color_value_qm);
    else if (EQ(description_command,Q2d_call_back_full))
	inner_full_paint_2d_grid(foreground_color_value_qm);
    else if (EQ(description_command,Q2d_call_back_partial))
	inner_partial_paint_2d_grid(foreground_color_value_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* GET-MARKER-DIMENSIONS */
Object get_marker_dimensions(x,y,marker_size,marker_half_size)
    Object x, y, marker_size, marker_half_size;
{
    Object temp, temp_1, temp_2, temp_3;

    x_note_fn_call(172,117);
    temp = FIXNUM_MINUS(y,marker_half_size);
    temp_1 = FIXNUM_ADD(y,marker_half_size);
    temp_2 = FIXNUM_MINUS(x,marker_size);
    temp_3 = FIXNUM_MINUS(x,marker_half_size);
    return VALUES_4(temp,temp_1,temp_2,temp_3);
}

/* PAINT-CLIPPED-RECTANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object paint_clipped_rectangle_in_current_scratchpad_raster(left_edge_in_window,
	    top_edge_in_window,right_edge_in_window,bottom_edge_in_window,
	    color_value)
    Object left_edge_in_window, top_edge_in_window, right_edge_in_window;
    Object bottom_edge_in_window, color_value;
{
    Object temp, temp_1;

    x_note_fn_call(172,118);
    temp = ISVREF(Current_graph_rendering,(SI_Long)12L);
    temp_1 = ISVREF(Current_graph_rendering,(SI_Long)13L);
    return paint_solid_rectangle_in_current_scratchpad_raster(FIX(MAX(IFIX(left_edge_in_window),
	    (SI_Long)0L)),FIX(MAX(IFIX(top_edge_in_window),(SI_Long)0L)),
	    FIXNUM_MIN(right_edge_in_window,temp),
	    FIXNUM_MIN(bottom_edge_in_window,temp_1),color_value);
}

/* PAINT-CLIPPED-TRIANGLE-IN-CURRENT-SCRATCHPAD-RASTER */
Object paint_clipped_triangle_in_current_scratchpad_raster(x1,y1_1,x2,y2,
	    x3,y3,color_value)
    Object x1, y1_1, x2, y2, x3, y3, color_value;
{
    Object temp, clipped_bottom_edge;

    x_note_fn_call(172,119);
    temp = ISVREF(Current_graph_rendering,(SI_Long)13L);
    clipped_bottom_edge = FIXNUM_MIN(y1_1,temp);
    return paint_filled_triangle_in_current_scratchpad_raster(FIX(MAX(IFIX(x1),
	    (SI_Long)0L)),clipped_bottom_edge,FIX(MAX(IFIX(x2),
	    (SI_Long)0L)),FIX(MAX(IFIX(y2),(SI_Long)0L)),x3,
	    clipped_bottom_edge,color_value);
}

/* PAINT-SHADED-LINE-IN-CURRENT-SCRATCHPAD-RASTER */
Object paint_shaded_line_in_current_scratchpad_raster(x1,y1_1,x2,y2,
	    graph_line_color_value)
    Object x1, y1_1, x2, y2, graph_line_color_value;
{
    x_note_fn_call(172,120);
    if (FIXNUM_GT(y1_1,y2)) {
	paint_clipped_triangle_in_current_scratchpad_raster(x1,y1_1,x2,y2,
		x2,y1_1,graph_line_color_value);
	return paint_clipped_rectangle_in_current_scratchpad_raster(x1,
		y1_1,x2,ISVREF(Current_graph_rendering,(SI_Long)13L),
		graph_line_color_value);
    }
    else {
	paint_clipped_triangle_in_current_scratchpad_raster(x1,y2,x1,y1_1,
		x2,y2,graph_line_color_value);
	return paint_clipped_rectangle_in_current_scratchpad_raster(x1,y2,
		x2,ISVREF(Current_graph_rendering,(SI_Long)13L),
		graph_line_color_value);
    }
}

/* POINT-NOT-ON-GRAPH? */
Object point_not_on_graph_qm(y)
    Object y;
{
    Object height;

    x_note_fn_call(172,121);
    if (IFIX(y) < (SI_Long)0L)
	return VALUES_1(FIX((SI_Long)0L));
    else {
	height = ISVREF(Current_graph_rendering,(SI_Long)13L);
	if (FIXNUM_GE(y,height))
	    return VALUES_1(height);
	else
	    return VALUES_1(Nil);
    }
}

static Object Qsquare;             /* square */

static Object Qplus_sign;          /* plus-sign */

static Object Qab_star;            /* star */

static Object Qtriangle;           /* triangle */

/* PAINT-PLOT-MARKER */
Object paint_plot_marker(plot_marker_info,graph_line_color_value,x_scale,
	    y_scale)
    Object plot_marker_info, graph_line_color_value, x_scale, y_scale;
{
    Object plot_marker, x, y, top, bottom, left, middle_x, temp, temp_1;
    Object temp_2, temp_3, scale, temp_4, temp_5;
    SI_Long unshifted_result, value, gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(172,122);
    plot_marker = FIRST(plot_marker_info);
    x = SECOND(plot_marker_info);
    y = THIRD(plot_marker_info);
    top = Nil;
    bottom = Nil;
    left = Nil;
    middle_x = Nil;
    if (IFIX(y_scale) == (SI_Long)4096L)
	temp = y;
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y_scale) && 
	    FIXNUM_LT(y_scale,Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
	    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y)) + (SI_Long)2048L;
	temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
    }
    else
	temp = scalef_function(y_scale,y);
    if ( !TRUEP(point_not_on_graph_qm(temp))) {
	if (EQ(plot_marker,Qsquare)) {
	    result = get_marker_dimensions(x,y,Default_marker_size,
		    Default_marker_half_size);
	    MVS_4(result,top,bottom,left,middle_x);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp = left;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) 
		    && FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,left)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(x_scale,left);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_1 = top;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top) 
		    && FIXNUM_LT(top,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,top)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(y_scale,top);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp_2 = x;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x)) + 
			(SI_Long)2048L;
		temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_2 = scalef_function(x_scale,x);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_3 = bottom;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom) && FIXNUM_LT(bottom,
			Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,bottom)) + 
			(SI_Long)2048L;
		temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_3 = scalef_function(y_scale,bottom);
	    return paint_clipped_rectangle_in_current_scratchpad_raster(temp,
		    temp_1,temp_2,temp_3,graph_line_color_value);
	}
	else if (EQ(plot_marker,Qplus_sign) || EQ(plot_marker,Qab_star)) {
	    result = get_marker_dimensions(x,y,Plus_sign_marker_size,
		    Plus_sign_marker_half_size);
	    MVS_4(result,top,bottom,left,middle_x);
	    scale = x_scale;
	    value = IFIX(middle_x) - (SI_Long)2L;
	    if (IFIX(scale) == (SI_Long)4096L)
		temp = FIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(scale,FIX(value));
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_1 = top;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top) 
		    && FIXNUM_LT(top,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,top)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(y_scale,top);
	    scale = x_scale;
	    value = IFIX(middle_x) + (SI_Long)2L;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol = IFIX(scalef_function(scale,FIX(value)));
	    gensymed_symbol_1 = (SI_Long)0L;
	    temp_2 = FIX(MAX(gensymed_symbol,gensymed_symbol_1));
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_3 = bottom;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom) && FIXNUM_LT(bottom,
			Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,bottom)) + 
			(SI_Long)2048L;
		temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_3 = scalef_function(y_scale,bottom);
	    paint_clipped_rectangle_in_current_scratchpad_raster(temp,
		    temp_1,temp_2,temp_3,graph_line_color_value);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp = left;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) 
		    && FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,left)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(x_scale,left);
	    scale = y_scale;
	    value = IFIX(y) - (SI_Long)2L;
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_1 = FIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(scale,FIX(value));
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp_2 = x;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x)) + 
			(SI_Long)2048L;
		temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_2 = scalef_function(x_scale,x);
	    scale = y_scale;
	    value = IFIX(y) + (SI_Long)2L;
	    if (IFIX(scale) == (SI_Long)4096L)
		temp_3 = FIX(value);
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_3 = scalef_function(scale,FIX(value));
	    return paint_clipped_rectangle_in_current_scratchpad_raster(temp,
		    temp_1,temp_2,temp_3,graph_line_color_value);
	}
	else if (EQ(plot_marker,Qtriangle)) {
	    result = get_marker_dimensions(x,y,Default_marker_size,
		    Default_marker_half_size);
	    MVS_4(result,top,bottom,left,middle_x);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp = left;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,left) 
		    && FIXNUM_LT(left,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,left)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(x_scale,left);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_1 = bottom;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom) && FIXNUM_LT(bottom,
			Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,bottom)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(y_scale,bottom);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp_2 = middle_x;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    middle_x) && FIXNUM_LT(middle_x,
		    Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,middle_x)) + 
			(SI_Long)2048L;
		temp_2 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_2 = scalef_function(x_scale,middle_x);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_3 = top;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,top) 
		    && FIXNUM_LT(top,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,top)) + 
			(SI_Long)2048L;
		temp_3 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_3 = scalef_function(y_scale,top);
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp_4 = x;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x)) + 
			(SI_Long)2048L;
		temp_4 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_4 = scalef_function(x_scale,x);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp_5 = bottom;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    bottom) && FIXNUM_LT(bottom,
			Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,bottom)) + 
			(SI_Long)2048L;
		temp_5 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_5 = scalef_function(y_scale,bottom);
	    return paint_clipped_triangle_in_current_scratchpad_raster(temp,
		    temp_1,temp_2,temp_3,temp_4,temp_5,graph_line_color_value);
	}
	else
	    return paint_nupec_plot_marker(plot_marker,x,y,
		    graph_line_color_value,x_scale,y_scale);
    }
    else
	return VALUES_1(Nil);
}

static Object Qgraph_axis_label;   /* graph-axis-label */

static Object Qlabel_permanent_qm;  /* label-permanent? */

static Object Qbackground_color;   /* background-color */

/* MAKE-GRAPH-AXIS-LABEL */
Object make_graph_axis_label varargs_1(int, n)
{
    Object text_line, label_permanent_qm;
    Object background_color_qm, graph_axis_label;
    Declare_varargs_nonrelocating;

    x_note_fn_call(172,123);
    INIT_ARGS_nonrelocating();
    text_line = REQUIRED_ARG_nonrelocating();
    label_permanent_qm = REQUIRED_ARG_nonrelocating();
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    graph_axis_label = make_free_text_box(2,text_line,Qgraph_axis_label);
    set_non_savable_lookup_slot_value(graph_axis_label,Qlabel_permanent_qm,
	    label_permanent_qm);
    if (background_color_qm)
	change_text_box_property(graph_axis_label,Qbackground_color,
		background_color_qm);
    return VALUES_1(graph_axis_label);
}

static Object Qframe_flags;        /* frame-flags */

/* MAKE-GRAPHS-OPAQUE-1 */
Object make_graphs_opaque_1()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, graph;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(172,124);
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
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(graph,Qframe_flags);
      svref_new_value = IFIX(ISVREF(graph,(SI_Long)4L)) | (SI_Long)1024L;
      ISVREF(graph,(SI_Long)4L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* REFORMAT-AS-APPROPRIATE-FOR-GRAPH */
Object reformat_as_appropriate_for_graph(graph,
	    superblock_will_do_reformatting_qm)
    Object graph, superblock_will_do_reformatting_qm;
{
    Object graph_format_to_reformat_by_qm, temp, graph_grid, gensymed_symbol_1;
    Object redraw_as_well_as_reformat_p;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long grid_width_delta, grid_height_delta;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(172,125);
    graph_format_to_reformat_by_qm = 
	    format_frame_to_reformat_by_if_any(graph,ISVREF(graph,
	    (SI_Long)22L));
    if (graph_format_to_reformat_by_qm) {
	temp = ISVREF(graph,(SI_Long)19L);
	temp = FIRST(temp);
	graph_grid = FIRST(temp);
	gensymed_symbol = IFIX(ISVREF(graph_format_to_reformat_by_qm,
		(SI_Long)31L));
	gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	grid_width_delta = gensymed_symbol - gensymed_symbol_2;
	gensymed_symbol = IFIX(ISVREF(graph_format_to_reformat_by_qm,
		(SI_Long)32L));
	gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	grid_height_delta = gensymed_symbol - gensymed_symbol_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    redraw_as_well_as_reformat_p = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		    0);
	      make_or_reformat_graph_grid(9,Nil,graph_grid,
		      graph_format_to_reformat_by_qm,T,T,FIX((SI_Long)0L),
		      FIX((SI_Long)0L),FIX(grid_width_delta),
		      FIX(grid_height_delta));
	    POP_SPECIAL();
	}
	POP_LOCAL_ALLOCATION(0,0);
	reformat_table_in_place(1,graph);
    }
    return reformat_as_appropriate_for_table(graph,
	    superblock_will_do_reformatting_qm);
}

void graphs1_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_plot_data_ring_buffer_1;
    Object Qclasses_which_define, Qreformat_as_appropriate;
    Object Qreformat_as_appropriate_for_graph, AB_package, Qformat_description;
    Object string_constant_98, Qgraph_axis_label_format, string_constant_97;
    Object Qcorner_empty_text_cell_format;
    Object Qgraph_vertical_axis_heading_text_cell_format, string_constant_96;
    Object Qgraph_horizontal_axis_heading_text_cell_format, string_constant_95;
    Object Qgraph_heading_text_cell_format;
    Object Qmake_graph_rendering_structure_if_necessary, float_constant_6;
    Object Qgraphs1, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qdraw;
    Object Qdraw_for_graph_grid, Qdraw_for_graph, Qslot_value_reclaimer;
    Object Qreclaim_data_buffer_for_plot_value, Qdata_buffer_for_plot;
    Object Qplot_data_ring_buffer, Qreclaim_structure;
    Object Qoutstanding_plot_data_ring_buffer_count;
    Object Qplot_data_ring_buffer_structure_memory_usage, Qutilities2;
    Object string_constant_94, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_93, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qgenerate_spot;
    Object Qgenerate_spot_for_graph_axis_label, string_constant_92;
    Object list_constant_5, string_constant_91, string_constant_90;
    Object string_constant_1, Qtext_box, Qabsent_slot_putter;
    Object Qput_plot_pattern_where_slot_is_absent, Qplot_pattern, Qplot;
    Object string_constant_89, string_constant_88, list_constant_4;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_62, Qdependent_frame;
    Object Qreclaim_vertical_axis_range_value;
    Object Qreclaim_horizontal_axis_range_value, Qhorizontal_axis_range;
    Object Qreclaim_high_value_for_vertical_axis_value;
    Object Qhigh_value_for_vertical_axis;
    Object Qreclaim_low_value_for_vertical_axis_value;
    Object Qreclaim_high_value_for_horizontal_axis_value;
    Object Qhigh_value_for_horizontal_axis;
    Object Qreclaim_low_value_for_horizontal_axis_value;
    Object Qreclaim_vertical_grid_line_spacing_value;
    Object Qreclaim_high_value_for_vertical_grid_lines_value;
    Object Qreclaim_low_value_for_vertical_grid_lines_value;
    Object Qreclaim_interval_between_vertical_grid_lines_value;
    Object Qreclaim_horizontal_grid_line_spacing_value;
    Object Qreclaim_high_value_for_horizontal_grid_lines_value;
    Object Qreclaim_low_value_for_horizontal_grid_lines_value;
    Object Qreclaim_interval_between_horizontal_grid_lines_value;
    Object Qreclaim_desired_high_value_for_vertical_axis_value;
    Object Qreclaim_desired_low_value_for_vertical_axis_value;
    Object Qreclaim_desired_high_value_for_horizontal_axis_value;
    Object Qreclaim_desired_low_value_for_horizontal_axis_value;
    Object Qreclaim_tail_pointer_for_line_segments_value;
    Object Qtail_pointer_for_line_segments;
    Object Qreclaim_tail_pointer_for_line_drawing_description_value;
    Object Qtail_pointer_for_line_drawing_description;
    Object Qreclaim_line_drawing_description_for_graph_grid_qm_value;
    Object Qline_drawing_description_for_graph_grid_qm, Qcleanup;
    Object Qcleanup_for_graph_grid, Qcleanup_for_graph, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, list_constant_3, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object Qdesired_range_for_vertical_axis;
    Object Qdesired_range_for_vertical_axis_qm;
    Object Qdesired_range_for_horizontal_axis;
    Object Qdesired_range_for_horizontal_axis_qm, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, list_constant_2, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, Qitem, string_constant_24, Qdefault_plot_format;
    Object string_constant_23, list_constant_1, Qplot_format;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object Qgraph_format_for_books, Qdefault_graph_format, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, Qgraph_format, float_constant_5;
    Object float_constant_4, float_constant_2, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, string_constant_8;
    Object string_constant_7, string_constant_6, string_constant_5;
    Object string_constant_4, string_constant_3, string_constant_2;
    Object array_constant_2, array_constant_1, array_constant, Qformat_frame;
    Object Qspot_generator_for_table_format_for_graphs;
    Object Qtable_format_spot_generator, Qtable_format_for_graphs;
    Object string_constant, float_constant_3, float_constant_1;
    Object Qinitialize_to_managed_float_box, list_constant, Qgraphs2, Kfuncall;

    x_note_fn_call(172,126);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhistory_time_per_pixel = STATIC_SYMBOL("HISTORY-TIME-PER-PIXEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhistory_time_per_pixel,History_time_per_pixel);
    Qgraphs2 = STATIC_SYMBOL("GRAPHS2",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_to_managed_float_box = 
	    STATIC_SYMBOL("INITIALIZE-TO-MANAGED-FLOAT-BOX",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_to_managed_float_box);
    record_system_variable(Qhistory_time_per_pixel,Qgraphs2,list_constant,
	    Qnil,Qnil,Qnil,Qnil);
    Qlast_history_time_for_data_point_on_pixel = 
	    STATIC_SYMBOL("LAST-HISTORY-TIME-FOR-DATA-POINT-ON-PIXEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlast_history_time_for_data_point_on_pixel,
	    Last_history_time_for_data_point_on_pixel);
    record_system_variable(Qlast_history_time_for_data_point_on_pixel,
	    Qgraphs2,list_constant,Qnil,Qnil,Qnil,Qnil);
    Qdata_point_value = STATIC_SYMBOL("DATA-POINT-VALUE",AB_package);
    record_system_variable(Qdata_point_value,Qgraphs2,list_constant,Qnil,
	    Qnil,Qnil,Qnil);
    Qminimum_y_value_for_pixel = STATIC_SYMBOL("MINIMUM-Y-VALUE-FOR-PIXEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_y_value_for_pixel,
	    Minimum_y_value_for_pixel);
    record_system_variable(Qminimum_y_value_for_pixel,Qgraphs2,
	    list_constant,Qnil,Qnil,Qnil,Qnil);
    Qmaximum_y_value_for_pixel = STATIC_SYMBOL("MAXIMUM-Y-VALUE-FOR-PIXEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_y_value_for_pixel,
	    Maximum_y_value_for_pixel);
    record_system_variable(Qmaximum_y_value_for_pixel,Qgraphs2,
	    list_constant,Qnil,Qnil,Qnil,Qnil);
    Qminimum_y_value = STATIC_SYMBOL("MINIMUM-Y-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_y_value,Minimum_y_value);
    record_system_variable(Qminimum_y_value,Qgraphs2,list_constant,Qnil,
	    Qnil,Qnil,Qnil);
    Qmaximum_y_value = STATIC_SYMBOL("MAXIMUM-Y-VALUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_y_value,Maximum_y_value);
    record_system_variable(Qmaximum_y_value,Qgraphs2,list_constant,Qnil,
	    Qnil,Qnil,Qnil);
    Qplot_min_qm = STATIC_SYMBOL("PLOT-MIN\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplot_min_qm,Plot_min_qm);
    record_system_variable(Qplot_min_qm,Qgraphs2,list_constant,Qnil,Qnil,
	    Qnil,Qnil);
    Qplot_max_qm = STATIC_SYMBOL("PLOT-MAX\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplot_max_qm,Plot_max_qm);
    record_system_variable(Qplot_max_qm,Qgraphs2,list_constant,Qnil,Qnil,
	    Qnil,Qnil);
    Qvertical_axis_range = STATIC_SYMBOL("VERTICAL-AXIS-RANGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvertical_axis_range,Vertical_axis_range);
    record_system_variable(Qvertical_axis_range,Qgraphs2,list_constant,
	    Qnil,Qnil,Qnil,Qnil);
    Qlow_value_for_vertical_axis = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-VERTICAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlow_value_for_vertical_axis,
	    Low_value_for_vertical_axis);
    record_system_variable(Qlow_value_for_vertical_axis,Qgraphs2,
	    list_constant,Qnil,Qnil,Qnil,Qnil);
    Qhandy_float_1 = STATIC_SYMBOL("HANDY-FLOAT-1",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhandy_float_1,Handy_float_1);
    record_system_variable(Qhandy_float_1,Qgraphs2,list_constant,Qnil,Qnil,
	    Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_to_managed_float_box,
	    STATIC_FUNCTION(initialize_to_managed_float_box,NIL,FALSE,0,0));
    Qdefault_duration_for_data_point = 
	    STATIC_SYMBOL("DEFAULT-DURATION-FOR-DATA-POINT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdefault_duration_for_data_point,
	    Default_duration_for_data_point);
    Qgraphs1 = STATIC_SYMBOL("GRAPHS1",AB_package);
    float_constant_1 = STATIC_FLOAT(0.5);
    record_system_variable(Qdefault_duration_for_data_point,Qgraphs1,
	    float_constant_1,Qnil,Qnil,Qnil,Qnil);
    Default_graph_left_margin_width = FIX((SI_Long)60L);
    Default_graph_right_margin_width = FIX((SI_Long)0L);
    Default_data_point_y_size = FIX((SI_Long)4L);
    float_constant_2 = STATIC_FLOAT(0.1);
    Erase_zone_ratio = float_constant_2;
    float_constant_3 = STATIC_FLOAT(0.01);
    Minimum_range_to_maximum_value_ratio = float_constant_3;
    Default_axis_half_range = FIX((SI_Long)1L);
    Default_interval_between_vertical_grid_lines = FIX((SI_Long)1L);
    Default_number_of_vertical_grid_lines = FIX((SI_Long)5L);
    Maximum_number_of_horizontal_grid_lines = FIX((SI_Long)500L);
    Default_number_of_markers = FIX((SI_Long)6L);
    Qtable_format_for_graphs = STATIC_SYMBOL("TABLE-FORMAT-FOR-GRAPHS",
	    AB_package);
    string_constant = STATIC_STRING("1v83*ny8308yl830Ayl8309yl8307yl83=Dyk");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qtable_format_for_graphs,
	    regenerate_optimized_constant(string_constant),
	    Qformat_description);
    Qspot_generator_for_table_format_for_graphs = 
	    STATIC_SYMBOL("SPOT-GENERATOR-FOR-TABLE-FORMAT-FOR-GRAPHS",
	    AB_package);
    Qtable_format_spot_generator = 
	    STATIC_SYMBOL("TABLE-FORMAT-SPOT-GENERATOR",AB_package);
    mutate_global_property(Qtable_format_for_graphs,
	    Qspot_generator_for_table_format_for_graphs,
	    Qtable_format_spot_generator);
    SET_SYMBOL_FUNCTION(Qspot_generator_for_table_format_for_graphs,
	    STATIC_FUNCTION(spot_generator_for_table_format_for_graphs,NIL,
	    FALSE,2,2));
    Qgraph_format = STATIC_SYMBOL("GRAPH-FORMAT",AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    list_constant_1 = STATIC_CONS(Qformat_frame,Qnil);
    check_if_superior_classes_are_defined(Qgraph_format,list_constant_1);
    string_constant_1 = STATIC_STRING("0");
    array_constant = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant,(SI_Long)0L,0.1);
    array_constant_1 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_1,(SI_Long)0L,0.001);
    array_constant_2 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_2,(SI_Long)0L,0.4);
    string_constant_2 = 
	    STATIC_STRING("13Ry4z8r83Qoy83Qoy833Ny833Ny083fy001n1l8o1l8l1l83Cy000004z8r83Qhy83Qhy833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83Vay83Vay833Ny833N");
    string_constant_3 = 
	    STATIC_STRING("y03-Cy001n1l8o1l8l1l83Cy000004z8r83Vby83Vby833Ny833Ny03Gy001n1l8o1l8l1l83Cy000004z8r83Qpy83Qpy833Ny833Ny00001n1l8o1l8l1l83Cy0000");
    string_constant_4 = 
	    STATIC_STRING("04z8r83Qmy83Qmy833Ny833Ny0l001n1l8o1l8l1l83Cy000004z8r83Qly83Qly833Ny833Ny083fy001n1l8o1l8l1l83Cy000004z8r83Qwy83Qwy833Ny833Ny0l");
    string_constant_5 = 
	    STATIC_STRING("001n1l8o1l8l1l83Cy000004z8r83Qvy83Qvy833Ny833Ny083fy001n1l8o1l8l1l83Cy000004z8r83Vcy83Vcy833Ny833Ny030ey001n1l8o1l8l1l83Cy000004");
    string_constant_6 = 
	    STATIC_STRING("z8r83VZy83VZy833Ny833Ny03=4y001n1l8o1l8l1l83Cy000004z8r83Why83Why833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83X+y83X+y833Ny833Ny0000");
    string_constant_7 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83RYy83RYy833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83e-y83e-y833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83Vfy");
    string_constant_8 = 
	    STATIC_STRING("83Vfy833Ny833Ny09k001n1l8o1l8l1l83Cy000004z8r83Vhy83Vhy833Ny833Ny0o001n1l8o1l8l1l83Cy000004z8r83Vgy83Vgy833Ny833Ny09l001n1l8o1l8");
    string_constant_9 = 
	    STATIC_STRING("l1l83Cy000004z8r83Vjy83Vjy833Ny833Ny0n001n1l8o1l8l1l83Cy000004z8r83J5y83J5y833Ny833Ny0u001n1l8o1l8l1l83Cy000004z8r83VYy83VYy833N");
    string_constant_10 = 
	    STATIC_STRING("y833Ny0u001n1l8o1l8l1l83Cy000004z8r83dcy83dcy833Ny833Ny08k001n1l8o1l8l1l83Cy000004z8r83TPy83TPy833Ny833Ny00001n1l8o1l8l1l83Cy000");
    string_constant_11 = 
	    STATIC_STRING("004z8r83TQy83TQy833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83TOy83TOy833Ny833Ny00001n1l8o1l8l1l83Cy000004z8r83TRy83TRy833Ny833Ny0000");
    string_constant_12 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83L7y83L7y833Ny833Ny0k001n1l8o1l8l1l83Cy000004z8r83L5y83L5y833Ny833Ny09m001n1l8o1l8l1l83Cy000004z8r83L8");
    string_constant_13 = 
	    STATIC_STRING("y83L8y833Ny833Ny09n001n1l8o1l8l1l83Cy000004z8r83L6y83L6y833Ny833Ny09o001n1l8o1l8l1l83Cy000004z8r83Yjy83Yjy833Ny833Ny08k001n1l8o1");
    string_constant_14 = STATIC_STRING("l8l1l83Cy00000");
    float_constant_4 = STATIC_FLOAT(0.001);
    float_constant_5 = STATIC_FLOAT(0.4);
    string_constant_15 = 
	    STATIC_STRING("13Ty8q1m833Ny1l831Fy1p83Qoy83fy8o8l83Cy1p83Qhy08o8l83Cy1p83Vay3-Cy8o8l83Cy1p83Vby3Gy8o8l83Cy1p83Qpy08o8l83Cy1p83Qmyl8o8l83Cy1p83");
    string_constant_16 = 
	    STATIC_STRING("Qly83fy8o8l83Cy1p83Qwyl8o8l83Cy1p83Qvy83fy8o8l83Cy1p83Vcy30ey8o8l83Cy1p83VZy3=4y8o8l83Cy1p83Why08o8l83Cy1p83X+y08o8l83Cy1p83RYy0");
    string_constant_17 = 
	    STATIC_STRING("8o8l83Cy1p83e-y08o8l83Cy1p83Vfy9k8o8l83Cy1p83Vhyo8o8l83Cy1p83Vgy9l8o8l83Cy1p83Vjyn8o8l83Cy1p83J5yu8o8l83Cy1p83VYyu8o8l83Cy1p83dc");
    string_constant_18 = 
	    STATIC_STRING("y8k8o8l83Cy1p83TPy08o8l83Cy1p83TQy08o8l83Cy1p83TOy08o8l83Cy1p83TRy08o8l83Cy1p83L7yk8o8l83Cy1p83L5y9m8o8l83Cy1p83L8y9m8o8l83Cy1p8");
    string_constant_19 = STATIC_STRING("3L6y9m8o8l83Cy1p83Yjy8k8o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_1);
    clear_optimized_constants();
    push_optimized_constant(array_constant);
    push_optimized_constant(array_constant_1);
    push_optimized_constant(array_constant_2);
    push_optimized_constant(array_constant_2);
    push_optimized_constant(array_constant_2);
    temp_1 = regenerate_optimized_constant(list(13,string_constant_2,
	    string_constant_3,string_constant_4,string_constant_5,
	    string_constant_6,string_constant_7,string_constant_8,
	    string_constant_9,string_constant_10,string_constant_11,
	    string_constant_12,string_constant_13,string_constant_14));
    clear_optimized_constants();
    push_optimized_constant(float_constant_2);
    push_optimized_constant(float_constant_4);
    push_optimized_constant(float_constant_5);
    add_class_to_environment(9,Qgraph_format,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,
	    regenerate_optimized_constant(LIST_5(string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19)),Nil);
    Qdefault_graph_format = STATIC_SYMBOL("DEFAULT-GRAPH-FORMAT",AB_package);
    string_constant_20 = STATIC_STRING("1l833Ny");
    mutate_global_property(Qdefault_graph_format,
	    regenerate_optimized_constant(string_constant_20),
	    Qformat_description);
    Qgraph_format_for_books = STATIC_SYMBOL("GRAPH-FORMAT-FOR-BOOKS",
	    AB_package);
    mutate_global_property(Qgraph_format_for_books,
	    regenerate_optimized_constant(string_constant_20),
	    Qformat_description);
    Qplot_format = STATIC_SYMBOL("PLOT-FORMAT",AB_package);
    check_if_superior_classes_are_defined(Qplot_format,list_constant_1);
    string_constant_21 = 
	    STATIC_STRING("1n4z8r83Xoy83Xoy834Oy834Oy083fy001m1l8o1l8l000004z8r83Xpy83Xpy834Oy834Oy00001m1l8o1l8l000004z8r83ddy83ddy834Oy834Oy00001m1l8o1l8");
    string_constant_22 = STATIC_STRING("l00000");
    string_constant_23 = 
	    STATIC_STRING("1p8q1m834Oy1l831Fy1o83Xoy83fy8o8l1o83Xpy08o8l1o83ddy08o8l");
    temp = regenerate_optimized_constant(string_constant_1);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_21,
	    string_constant_22));
    add_class_to_environment(9,Qplot_format,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,
	    regenerate_optimized_constant(string_constant_23),Nil);
    Qdefault_plot_format = STATIC_SYMBOL("DEFAULT-PLOT-FORMAT",AB_package);
    string_constant_24 = STATIC_STRING("1l834Oy");
    mutate_global_property(Qdefault_plot_format,
	    regenerate_optimized_constant(string_constant_24),
	    Qformat_description);
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qitem,Qtable);
    check_if_superior_classes_are_defined(Qgraph,list_constant_2);
    string_constant_25 = 
	    STATIC_STRING("1m1l8t1m83-Cy53E6yPossible exported attributes ~\n and attribute-mimics:<br> ~\n <ul><LI>desired-range-for-horizontal-axis: (or no");
    string_constant_26 = 
	    STATIC_STRING("ne [start-value: integer, ~\n start-units: time-unit-symbol, end-value: integer, end-units: ~\n time-unit-symbol, include-tickmark");
    string_constant_27 = 
	    STATIC_STRING("-labels: boolean]),\n <LI>desired-range-for-vertical-axis: (or none [start-value: integer, ~\n start-units: time-unit-symbol, end-");
    string_constant_28 = 
	    STATIC_STRING("value: integer, end-units: ~\n time-unit-symbol, include-tickmark-labels: boolean]), \n <LI>scroll-continuously\?: boolean, \n <LI>p");
    string_constant_29 = 
	    STATIC_STRING("ercentage-extra-space-to-leave: integer, \n <LI>show-grid-lines\?: boolean,\n <LI>interval-between-horizontal-grid-lines\?: (or \'com");
    string_constant_30 = 
	    STATIC_STRING("pute-automatically ~\n [interval: integer, start-value: integer])\n <LI>extra-grid-lines\?: (or \'none ((or none [position: integer,");
    string_constant_31 = 
	    STATIC_STRING(" color: ~\n color-symbol]) *)),\n <LI>background-colors: (color-symbol *), [graph-background: color-symbol, ~\n grid-background: co");
    string_constant_32 = 
	    STATIC_STRING("lor-symbol],\n <LI>expressions-to-display: (numerical-expression-parse *),\n <LI>label-to-display: string, \n <LI>display-update-in");
    string_constant_33 = 
	    STATIC_STRING("terval: time-interval-part,\n <LI>display-wait-interval: time-interval-part,\n <LI>display-update-priority: integer,\n <LI>show-sim");
    string_constant_34 = STATIC_STRING("ulated-values: boolean,</ul>");
    string_constant_35 = 
	    STATIC_STRING("13Jy4z8r83-Ey83-Ey833My833My03C+y001q1l8l1l8o1m8p01l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I think");
    string_constant_36 = 
	    STATIC_STRING(" individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be support");
    string_constant_37 = 
	    STATIC_STRING("ed. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r830dy830dy833My833My00001o1l83-4y1l8");
    string_constant_38 = 
	    STATIC_STRING("o1l8l1l83Hy000004z8r830ry830ry833My833My00001o1l83-4y1l8o1l8l1l83Hy000004z8r833Ny833Ny833My833My00001n1l8o1l8l1l83Cy000004z8r83B");
    string_constant_39 = 
	    STATIC_STRING("my83Bmy833My833My00001o1m8p8391y1l8o1l8l1l8z000004z8r83Bny83Bny833My833My00001o1m8p83ARy1l8o1l8l1l8z000004z8r83Ewy83Ewy833My833M");
    string_constant_40 = 
	    STATIC_STRING("y00001o1m8p83Ky1l8o1l8l1l8z000004z8r83ELy83ELy833My833My0k001o1m8p83Sy1l8o1l8l1l8z000004z8r83F*y83F*y833My833My08k001o1m8p83Ky1l");
    string_constant_41 = 
	    STATIC_STRING("8o1l8l1l8z000004z8r83D5y83D5y833My833My00001o1m8p8392y1l8o1l8l1l8z000004z8r83C=y83C=y833My833My00001o1m8p838Jy1l8o1l8l1l8z000004");
    string_constant_42 = 
	    STATIC_STRING("z8r83Awy83Awy833My833My02l83*2y83*2y001o1m8p838xy1l83Ey1l8l1l8z000004z8r83=gy83=gy833My833My00001p1n8p83DSy83Gy1l83-4y1l83Ey1l8l");
    string_constant_43 = 
	    STATIC_STRING("1l83-5y000004z8r835cy835cy833My833My00001o1n8p83-dy83Gy1l83-4y1l83Ey1l8l000004z8r830wy830wy833My833My00001o1l83-4y1l83Ey1l83Cy1l");
    string_constant_44 = 
	    STATIC_STRING("8l000004z8r830cy830cy833My833My00001n1l83-4y1l83Ey1l8l000004z8r8300y8300y833My833My0p001p1m8p83=Qy1l83-4y1l83Ey1l8l1l8z000004z8r");
    string_constant_45 = 
	    STATIC_STRING("830Hy830Hy833My833My0m001p1m8p83=Qy1l83-4y1l83Ey1l8l1l8z000004z8r830Gy830Gy833My833My0m001p1m8p83-Yy1l83-4y1l83Ey1l8l1l8z000004z");
    string_constant_46 = 
	    STATIC_STRING("8r83=Py83=Py833My833My00001p1m8p83Ky1l83-4y1l83Ey1l8l1l8z000004z8r830xy830xy833My833My00001n1l83-4y1l83Ey1l8l000004z8r830sy830sy");
    string_constant_47 = 
	    STATIC_STRING("833My833My00001n1l83-4y1l83Ey1l8l000004z8r83Qqy83Qqy833My833My00001m1l83Ey1l8l00000");
    string_constant_48 = 
	    STATIC_STRING("13Ly8q1o833My1m83Ry83*Jy8t1m83-Cy53E6yPossible exported attributes ~\n and attribute-mimics:<br> ~\n <ul><LI>desired-range-for-hor");
    string_constant_49 = 
	    STATIC_STRING("izontal-axis: (or none [start-value: integer, ~\n start-units: time-unit-symbol, end-value: integer, end-units: ~\n time-unit-symb");
    string_constant_50 = 
	    STATIC_STRING("ol, include-tickmark-labels: boolean]),\n <LI>desired-range-for-vertical-axis: (or none [start-value: integer, ~\n start-units: ti");
    string_constant_51 = 
	    STATIC_STRING("me-unit-symbol, end-value: integer, end-units: ~\n time-unit-symbol, include-tickmark-labels: boolean]), \n <LI>scroll-continuousl");
    string_constant_52 = 
	    STATIC_STRING("y\?: boolean, \n <LI>percentage-extra-space-to-leave: integer, \n <LI>show-grid-lines\?: boolean,\n <LI>interval-between-horizontal-g");
    string_constant_53 = 
	    STATIC_STRING("rid-lines\?: (or \'compute-automatically ~\n [interval: integer, start-value: integer])\n <LI>extra-grid-lines\?: (or \'none ((or none");
    string_constant_54 = 
	    STATIC_STRING(" [position: integer, color: ~\n color-symbol]) *)),\n <LI>background-colors: (color-symbol *), [graph-background: color-symbol, ~\n");
    string_constant_55 = 
	    STATIC_STRING(" grid-background: color-symbol],\n <LI>expressions-to-display: (numerical-expression-parse *),\n <LI>label-to-display: string, \n <");
    string_constant_56 = 
	    STATIC_STRING("LI>display-update-interval: time-interval-part,\n <LI>display-wait-interval: time-interval-part,\n <LI>display-update-priority: in");
    string_constant_57 = 
	    STATIC_STRING("teger,\n <LI>show-simulated-values: boolean,</ul>1m83-Ey3C+y1q830dy083-4y8o8l83Hy1q830ry083-4y8o8l83Hy1p833Ny08o8l83Cy1q83Bmy01m8");
    string_constant_58 = 
	    STATIC_STRING("p8391y8o8l8z1q83Bny01m8p83ARy8o8l8z1q83Ewy01m8p83Ky8o8l8z1q83ELyk1m8p83Sy8o8l8z1q83F*y8k1m8p83Ky8o8l8z1q83D5y01m8p8392y8o8l8z1q8");
    string_constant_59 = 
	    STATIC_STRING("3C=y01m8p838Jy8o8l8z1q83Awy2l83*2y83*2y1m8p838xy83Ey8l8z1r83=gy01n8p83DSy83Gy83-4y83Ey8l83-5y1q835cy01n8p83-dy83Gy83-4y83Ey8l1q8");
    string_constant_60 = 
	    STATIC_STRING("30wy083-4y83Ey83Cy8l1p830cy083-4y83Ey8l1r8300yp1m8p83=Qy83-4y83Ey8l8z1r830Hym1m8p83=Qy83-4y83Ey8l8z1r830Gym1m8p83-Yy83-4y83Ey8l8");
    string_constant_61 = 
	    STATIC_STRING("z1r83=Py01m8p83Ky83-4y83Ey8l8z1p830xy083-4y83Ey8l1p830sy083-4y83Ey8l1o83Qqy083Ey8l");
    temp = regenerate_optimized_constant(list(10,string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30,string_constant_31,
	    string_constant_32,string_constant_33,string_constant_34));
    temp_1 = regenerate_optimized_constant(list(13,string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38,
	    string_constant_39,string_constant_40,string_constant_41,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47));
    add_class_to_environment(9,Qgraph,list_constant_2,Nil,temp,Nil,temp_1,
	    list_constant_2,regenerate_optimized_constant(list(14,
	    string_constant_48,string_constant_49,string_constant_50,
	    string_constant_51,string_constant_52,string_constant_53,
	    string_constant_54,string_constant_55,string_constant_56,
	    string_constant_57,string_constant_58,string_constant_59,
	    string_constant_60,string_constant_61)),Nil);
    Graph_class_description = 
	    lookup_global_or_kb_specific_property_value(Qgraph,
	    Class_description_gkbprop);
    Qdesired_range_for_horizontal_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-HORIZONTAL-AXIS\?",AB_package);
    Qdesired_range_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-HORIZONTAL-AXIS",AB_package);
    alias_slot_name(3,Qdesired_range_for_horizontal_axis_qm,
	    Qdesired_range_for_horizontal_axis,Qnil);
    Qdesired_range_for_vertical_axis_qm = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-VERTICAL-AXIS\?",AB_package);
    Qdesired_range_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-RANGE-FOR-VERTICAL-AXIS",AB_package);
    alias_slot_name(3,Qdesired_range_for_vertical_axis_qm,
	    Qdesired_range_for_vertical_axis,Qnil);
    Qgraph_grid = STATIC_SYMBOL("GRAPH-GRID",AB_package);
    list_constant_3 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qgraph_grid,list_constant_3);
    string_constant_62 = STATIC_STRING("1l1l8t");
    string_constant_63 = 
	    STATIC_STRING("13hy4z8r83Jdy83Jdy83Qky83Qky00001m1l8o1l8l000004z8r83JZy83JZy83Qky83Qky00001m1l8o1l8l000004z8r83Jfy83Jfy83Qky83Qky00001m1l8o1l8l");
    string_constant_64 = 
	    STATIC_STRING("000004z8r83Jby83Jby83Qky83Qky00001m1l8o1l8l000004z8r83Siy83Siy83Qky83Qky00001m1l8o1l8l000004z8r83UZy83UZy83Qky83Qky00001m1l8o1l8");
    string_constant_65 = 
	    STATIC_STRING("l000004z8r83ROy83ROy83Qky83Qky00001m1l8o1l8l000004z8r83Wgy83Wgy83Qky83Qky00001m1l8o1l8l000004z8r83RXy83RXy83Qky83Qky00001m1l8o1l");
    string_constant_66 = 
	    STATIC_STRING("8l000004z8r83agy83agy83Qky83Qky00001m1l8o1l8l000004z8r83Sky83Sky83Qky83Qky00001m1l8o1l8l000004z8r83Uby83Uby83Qky83Qky00001m1l8o1");
    string_constant_67 = 
	    STATIC_STRING("l8l000004z8r83RRy83RRy83Qky83Qky00001m1l8o1l8l000004z8r83Wxy83Wxy83Qky83Qky00001m1l8o1l8l000004z8r83e+y83e+y83Qky83Qky00001m1l8o");
    string_constant_68 = 
	    STATIC_STRING("1l8l000004z8r83aey83aey83Qky83Qky00001m1l8o1l8l000004z8r83Tay83Tay83Qky83Qky00001m1l8o1l8l000004z8r83U4y83U4y83Qky83Qky00001n1l8");
    string_constant_69 = 
	    STATIC_STRING("o1l8l1l83Cy000004z8r83R*y83R*y83Qky83Qky00001m1l8o1l8l000004z8r83R-y83R-y83Qky83Qky00001m1l8o1l8l000004z8r83RWy83RWy83Qky83Qky00");
    string_constant_70 = 
	    STATIC_STRING("001m1l8o1l8l000004z8r83dxy83dxy83Qky83Qky00001m1l8o1l8l000004z8r83Qny83Qny83Qky83Qky00001m1l8o1l8l000004z8r83Qty83Qty83Qky83Qky0");
    string_constant_71 = 
	    STATIC_STRING("0001m1l8o1l8l000004z8r83Quy83Quy83Qky83Qky00001m1l8o1l8l000004z8r83Qiy83Qiy83Qky83Qky00001m1l8o1l8l000004z8r83Qry83Qry83Qky83Qky");
    string_constant_72 = 
	    STATIC_STRING("00001m1l8o1l8l000004z8r83Zsy83Zsy83Qky83Qky00001m1l8o1l8l000004z8r83UXy83UXy83Qky83Qky00001m1l8o1l8l000004z8r83UYy83UYy83Qky83Qk");
    string_constant_73 = 
	    STATIC_STRING("y00001m1l8o1l8l000004z8r83RNy83RNy83Qky83Qky00001m1l8o1l8l000004z8r83Uay83Uay83Qky83Qky00001m1l8o1l8l000004z8r83RQy83RQy83Qky83Q");
    string_constant_74 = 
	    STATIC_STRING("ky00001m1l8o1l8l000004z8r83J8y83J8y83Qky83Qky0k001m1l8o1l8l000004z8r83X8y83X8y83Qky83Qky0k001m1l8o1l8l000004z8r83WSy83WSy83Qky83");
    string_constant_75 = 
	    STATIC_STRING("Qky00001m1l8o1l8l000004z8r83Qjy83Qjy83Qky83Qky00001m1l8o1l8l000004z8r83J1y83J1y83Qky83Qky00001m1l8o1l8l000004z8r83Sjy83Sjy83Qky8");
    string_constant_76 = 
	    STATIC_STRING("3Qky00001m1l8o1l8l000004z8r83RVy83RVy83Qky83Qky00001m1l8o1l8l000004z8r83Txy83Txy83Qky83Qky00001m1l8o1l8l000004z8r83bMy83bMy83Qky");
    string_constant_77 = 
	    STATIC_STRING("83Qky00001m1l8o1l8l000004z8r83bNy83bNy83Qky83Qky00001m1l8o1l8l000004z8r83R+y83R+y83Qky83Qky00001m1l8o1l8l000004z8r83RUy83RUy83Qk");
    string_constant_78 = 
	    STATIC_STRING("y83Qky00001m1l8o1l8l000004z8r83K8y83K8y83Qky83Qky00001m1l8o1l8l000004z8r83X9y83X9y83Qky83Qky0k001m1l8o1l8l00000");
    string_constant_79 = 
	    STATIC_STRING("13jy8q1n83Qky1l9k8t1o83Jdy08o8l1o83JZy08o8l1o83Jfy08o8l1o83Jby08o8l1o83Siy08o8l1o83UZy08o8l1o83ROy08o8l1o83Wgy08o8l1o83RXy08o8l1");
    string_constant_80 = 
	    STATIC_STRING("o83agy08o8l1o83Sky08o8l1o83Uby08o8l1o83RRy08o8l1o83Wxy08o8l1o83e+y08o8l1o83aey08o8l1o83Tay08o8l1p83U4y08o8l83Cy1o83R*y08o8l1o83R");
    string_constant_81 = 
	    STATIC_STRING("-y08o8l1o83RWy08o8l1o83dxy08o8l1o83Qny08o8l1o83Qty08o8l1o83Quy08o8l1o83Qiy08o8l1o83Qry08o8l1o83Zsy08o8l1o83UXy08o8l1o83UYy08o8l1");
    string_constant_82 = 
	    STATIC_STRING("o83RNy08o8l1o83Uay08o8l1o83RQy08o8l1o83J8yk8o8l1o83X8yk8o8l1o83WSy08o8l1o83Qjy08o8l1o83J1y08o8l1o83Sjy08o8l1o83RVy08o8l1o83Txy08");
    string_constant_83 = 
	    STATIC_STRING("o8l1o83bMy08o8l1o83bNy08o8l1o83R+y08o8l1o83RUy08o8l1o83K8y08o8l1o83X9yk8o8l");
    temp = regenerate_optimized_constant(string_constant_62);
    temp_1 = regenerate_optimized_constant(list(16,string_constant_63,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qgraph_grid,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(LIST_5(string_constant_79,
	    string_constant_80,string_constant_81,string_constant_82,
	    string_constant_83)),Nil);
    Graph_grid_class_description = 
	    lookup_global_or_kb_specific_property_value(Qgraph_grid,
	    Class_description_gkbprop);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qgraph_reformatted_since_start_qm = 
	    STATIC_SYMBOL("GRAPH-REFORMATTED-SINCE-START\?",AB_package);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    Qcleanup_for_graph = STATIC_SYMBOL("CLEANUP-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_graph,
	    STATIC_FUNCTION(cleanup_for_graph,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_graph);
    set_get(Qgraph,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qcleanup_for_graph_grid = STATIC_SYMBOL("CLEANUP-FOR-GRAPH-GRID",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_graph_grid,
	    STATIC_FUNCTION(cleanup_for_graph_grid,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_graph_grid);
    set_get(Qgraph_grid,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph_grid,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qline_drawing_description_for_graph_grid_qm = 
	    STATIC_SYMBOL("LINE-DRAWING-DESCRIPTION-FOR-GRAPH-GRID\?",
	    AB_package);
    Qreclaim_line_drawing_description_for_graph_grid_qm_value = 
	    STATIC_SYMBOL("RECLAIM-LINE-DRAWING-DESCRIPTION-FOR-GRAPH-GRID\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_line_drawing_description_for_graph_grid_qm_value,
	    STATIC_FUNCTION(reclaim_line_drawing_description_for_graph_grid_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qline_drawing_description_for_graph_grid_qm,
	    SYMBOL_FUNCTION(Qreclaim_line_drawing_description_for_graph_grid_qm_value),
	    Qslot_value_reclaimer);
    Qtail_pointer_for_line_drawing_description = 
	    STATIC_SYMBOL("TAIL-POINTER-FOR-LINE-DRAWING-DESCRIPTION",
	    AB_package);
    Qreclaim_tail_pointer_for_line_drawing_description_value = 
	    STATIC_SYMBOL("RECLAIM-TAIL-POINTER-FOR-LINE-DRAWING-DESCRIPTION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_tail_pointer_for_line_drawing_description_value,
	    STATIC_FUNCTION(reclaim_tail_pointer_for_line_drawing_description_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtail_pointer_for_line_drawing_description,
	    SYMBOL_FUNCTION(Qreclaim_tail_pointer_for_line_drawing_description_value),
	    Qslot_value_reclaimer);
    Qtail_pointer_for_line_segments = 
	    STATIC_SYMBOL("TAIL-POINTER-FOR-LINE-SEGMENTS",AB_package);
    Qreclaim_tail_pointer_for_line_segments_value = 
	    STATIC_SYMBOL("RECLAIM-TAIL-POINTER-FOR-LINE-SEGMENTS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_tail_pointer_for_line_segments_value,
	    STATIC_FUNCTION(reclaim_tail_pointer_for_line_segments_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtail_pointer_for_line_segments,
	    SYMBOL_FUNCTION(Qreclaim_tail_pointer_for_line_segments_value),
	    Qslot_value_reclaimer);
    Qdesired_low_value_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    Qreclaim_desired_low_value_for_horizontal_axis_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-LOW-VALUE-FOR-HORIZONTAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_horizontal_axis_value,
	    STATIC_FUNCTION(reclaim_desired_low_value_for_horizontal_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_low_value_for_horizontal_axis,
	    SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_horizontal_axis_value),
	    Qslot_value_reclaimer);
    Qdesired_high_value_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    Qreclaim_desired_high_value_for_horizontal_axis_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-HIGH-VALUE-FOR-HORIZONTAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_horizontal_axis_value,
	    STATIC_FUNCTION(reclaim_desired_high_value_for_horizontal_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_high_value_for_horizontal_axis,
	    SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_horizontal_axis_value),
	    Qslot_value_reclaimer);
    Qdesired_low_value_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-VERTICAL-AXIS",AB_package);
    Qreclaim_desired_low_value_for_vertical_axis_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-LOW-VALUE-FOR-VERTICAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_vertical_axis_value,
	    STATIC_FUNCTION(reclaim_desired_low_value_for_vertical_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_low_value_for_vertical_axis,
	    SYMBOL_FUNCTION(Qreclaim_desired_low_value_for_vertical_axis_value),
	    Qslot_value_reclaimer);
    Qdesired_high_value_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-VERTICAL-AXIS",AB_package);
    Qreclaim_desired_high_value_for_vertical_axis_value = 
	    STATIC_SYMBOL("RECLAIM-DESIRED-HIGH-VALUE-FOR-VERTICAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_vertical_axis_value,
	    STATIC_FUNCTION(reclaim_desired_high_value_for_vertical_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdesired_high_value_for_vertical_axis,
	    SYMBOL_FUNCTION(Qreclaim_desired_high_value_for_vertical_axis_value),
	    Qslot_value_reclaimer);
    Qinterval_between_horizontal_grid_lines = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES",AB_package);
    Qreclaim_interval_between_horizontal_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_interval_between_horizontal_grid_lines_value,
	    STATIC_FUNCTION(reclaim_interval_between_horizontal_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinterval_between_horizontal_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_interval_between_horizontal_grid_lines_value),
	    Qslot_value_reclaimer);
    Qlow_value_for_horizontal_grid_lines = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-HORIZONTAL-GRID-LINES",AB_package);
    Qreclaim_low_value_for_horizontal_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-HORIZONTAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_horizontal_grid_lines_value,
	    STATIC_FUNCTION(reclaim_low_value_for_horizontal_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qlow_value_for_horizontal_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_horizontal_grid_lines_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_horizontal_grid_lines = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-HORIZONTAL-GRID-LINES",AB_package);
    Qreclaim_high_value_for_horizontal_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-HORIZONTAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_horizontal_grid_lines_value,
	    STATIC_FUNCTION(reclaim_high_value_for_horizontal_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhigh_value_for_horizontal_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_horizontal_grid_lines_value),
	    Qslot_value_reclaimer);
    Qhorizontal_grid_line_spacing = 
	    STATIC_SYMBOL("HORIZONTAL-GRID-LINE-SPACING",AB_package);
    Qreclaim_horizontal_grid_line_spacing_value = 
	    STATIC_SYMBOL("RECLAIM-HORIZONTAL-GRID-LINE-SPACING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_horizontal_grid_line_spacing_value,
	    STATIC_FUNCTION(reclaim_horizontal_grid_line_spacing_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qhorizontal_grid_line_spacing,
	    SYMBOL_FUNCTION(Qreclaim_horizontal_grid_line_spacing_value),
	    Qslot_value_reclaimer);
    Qinterval_between_vertical_grid_lines = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-VERTICAL-GRID-LINES",AB_package);
    Qreclaim_interval_between_vertical_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-INTERVAL-BETWEEN-VERTICAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_interval_between_vertical_grid_lines_value,
	    STATIC_FUNCTION(reclaim_interval_between_vertical_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinterval_between_vertical_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_interval_between_vertical_grid_lines_value),
	    Qslot_value_reclaimer);
    Qlow_value_for_vertical_grid_lines = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-VERTICAL-GRID-LINES",AB_package);
    Qreclaim_low_value_for_vertical_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-VERTICAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_vertical_grid_lines_value,
	    STATIC_FUNCTION(reclaim_low_value_for_vertical_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qlow_value_for_vertical_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_vertical_grid_lines_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_vertical_grid_lines = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-VERTICAL-GRID-LINES",AB_package);
    Qreclaim_high_value_for_vertical_grid_lines_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-VERTICAL-GRID-LINES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_vertical_grid_lines_value,
	    STATIC_FUNCTION(reclaim_high_value_for_vertical_grid_lines_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhigh_value_for_vertical_grid_lines,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_vertical_grid_lines_value),
	    Qslot_value_reclaimer);
    Qvertical_grid_line_spacing = 
	    STATIC_SYMBOL("VERTICAL-GRID-LINE-SPACING",AB_package);
    Qreclaim_vertical_grid_line_spacing_value = 
	    STATIC_SYMBOL("RECLAIM-VERTICAL-GRID-LINE-SPACING-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_vertical_grid_line_spacing_value,
	    STATIC_FUNCTION(reclaim_vertical_grid_line_spacing_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qvertical_grid_line_spacing,
	    SYMBOL_FUNCTION(Qreclaim_vertical_grid_line_spacing_value),
	    Qslot_value_reclaimer);
    Qlow_value_for_horizontal_axis = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlow_value_for_horizontal_axis,
	    Low_value_for_horizontal_axis);
    Qreclaim_low_value_for_horizontal_axis_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-HORIZONTAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_horizontal_axis_value,
	    STATIC_FUNCTION(reclaim_low_value_for_horizontal_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qlow_value_for_horizontal_axis,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_horizontal_axis_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_horizontal_axis = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    Qreclaim_high_value_for_horizontal_axis_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-HORIZONTAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_horizontal_axis_value,
	    STATIC_FUNCTION(reclaim_high_value_for_horizontal_axis_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qhigh_value_for_horizontal_axis,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_horizontal_axis_value),
	    Qslot_value_reclaimer);
    Qreclaim_low_value_for_vertical_axis_value = 
	    STATIC_SYMBOL("RECLAIM-LOW-VALUE-FOR-VERTICAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_low_value_for_vertical_axis_value,
	    STATIC_FUNCTION(reclaim_low_value_for_vertical_axis_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlow_value_for_vertical_axis,
	    SYMBOL_FUNCTION(Qreclaim_low_value_for_vertical_axis_value),
	    Qslot_value_reclaimer);
    Qhigh_value_for_vertical_axis = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-VERTICAL-AXIS",AB_package);
    Qreclaim_high_value_for_vertical_axis_value = 
	    STATIC_SYMBOL("RECLAIM-HIGH-VALUE-FOR-VERTICAL-AXIS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_high_value_for_vertical_axis_value,
	    STATIC_FUNCTION(reclaim_high_value_for_vertical_axis_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qhigh_value_for_vertical_axis,
	    SYMBOL_FUNCTION(Qreclaim_high_value_for_vertical_axis_value),
	    Qslot_value_reclaimer);
    Qhorizontal_axis_range = STATIC_SYMBOL("HORIZONTAL-AXIS-RANGE",AB_package);
    Qreclaim_horizontal_axis_range_value = 
	    STATIC_SYMBOL("RECLAIM-HORIZONTAL-AXIS-RANGE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_horizontal_axis_range_value,
	    STATIC_FUNCTION(reclaim_horizontal_axis_range_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qhorizontal_axis_range,
	    SYMBOL_FUNCTION(Qreclaim_horizontal_axis_range_value),
	    Qslot_value_reclaimer);
    Qreclaim_vertical_axis_range_value = 
	    STATIC_SYMBOL("RECLAIM-VERTICAL-AXIS-RANGE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_vertical_axis_range_value,
	    STATIC_FUNCTION(reclaim_vertical_axis_range_value,NIL,FALSE,2,2));
    mutate_global_property(Qvertical_axis_range,
	    SYMBOL_FUNCTION(Qreclaim_vertical_axis_range_value),
	    Qslot_value_reclaimer);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_4 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Qplot,list_constant_4);
    string_constant_84 = 
	    STATIC_STRING("1t4z8r834Oy834Oy833Wy833Wy00001n1l8o1l8l1l83Cy000004z8r83K=y83K=y833Wy833Wy00001n1l8o1l8l1l83Cy000004z8r839gy839gy833Wy833Wy0000");
    string_constant_85 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83J3y83J3y833Wy833Wy00001m1l8o1l8l000004z8r83eey83eey833Wy833Wy00001m1l8o1l8l000004z8r83edy83edy833Wy83");
    string_constant_86 = 
	    STATIC_STRING("3Wy00001m1l8o1l8l000004z8r83W2y83W2y833Wy833Wy00001m1l8o1l8l000004z8r83XFy83XFy833Wy833Wy00001m1l8o1l8l000004z8r83WOy83WOy833Wy8");
    string_constant_87 = STATIC_STRING("33Wy00001m1l8o1l8l00000");
    string_constant_88 = 
	    STATIC_STRING("1v8q1n833Wy1l83=fy8t1p834Oy08o8l83Cy1p83K=y08o8l83Cy1p839gy08o8l83Cy1o83J3y08o8l1o83eey08o8l1o83edy08o8l1o83W2y08o8l1o83XFy08o8l");
    string_constant_89 = STATIC_STRING("1o83WOy08o8l");
    temp = regenerate_optimized_constant(string_constant_62);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_84,
	    string_constant_85,string_constant_86,string_constant_87));
    add_class_to_environment(9,Qplot,list_constant_4,Nil,temp,Nil,temp_1,
	    list_constant_4,
	    regenerate_optimized_constant(LIST_2(string_constant_88,
	    string_constant_89)),Nil);
    Plot_class_description = 
	    lookup_global_or_kb_specific_property_value(Qplot,
	    Class_description_gkbprop);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qplot_color = STATIC_SYMBOL("PLOT-COLOR",AB_package);
    Qplot_pattern = STATIC_SYMBOL("PLOT-PATTERN",AB_package);
    Qput_plot_pattern_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PLOT-PATTERN-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_plot_pattern_where_slot_is_absent,
	    STATIC_FUNCTION(put_plot_pattern_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qplot_pattern,
	    SYMBOL_FUNCTION(Qput_plot_pattern_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    Qshading = STATIC_SYMBOL("SHADING",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qgraph_axis_label = STATIC_SYMBOL("GRAPH-AXIS-LABEL",AB_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    list_constant_5 = STATIC_CONS(Qtext_box,Qnil);
    check_if_superior_classes_are_defined(Qgraph_axis_label,list_constant_5);
    string_constant_90 = 
	    STATIC_STRING("1n4z8r83xy83xy83Qfy83Qfy083Qgy001n1l8l1l83Ey1m83Dy53CyExport, writable000004z8r83TZy83TZy83Qfy83Qfy00001m1l83Ey1l8l000004z8r83RZ");
    string_constant_91 = 
	    STATIC_STRING("y83RZy83Qfy83Qfy00001m1l83Ey1l8l00000");
    string_constant_92 = 
	    STATIC_STRING("1p8q1m83Qfy1l83-ly1m83xy83Qgy1o83TZy083Ey8l1o83RZy083Ey8l");
    temp = regenerate_optimized_constant(string_constant_1);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_90,
	    string_constant_91));
    add_class_to_environment(9,Qgraph_axis_label,list_constant_5,Nil,temp,
	    Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_92),Nil);
    Qgenerate_spot_for_graph_axis_label = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-GRAPH-AXIS-LABEL",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_graph_axis_label,
	    STATIC_FUNCTION(generate_spot_for_graph_axis_label,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_graph_axis_label);
    set_get(Qgraph_axis_label,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph_axis_label,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct = 
	    STATIC_SYMBOL("PLOT-DATA-RING-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qplot_data_ring_buffer = STATIC_SYMBOL("PLOT-DATA-RING-BUFFER",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct,
	    Qplot_data_ring_buffer,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qplot_data_ring_buffer,
	    Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_plot_data_ring_buffer == UNBOUND)
	The_type_description_of_plot_data_ring_buffer = Nil;
    string_constant_93 = 
	    STATIC_STRING("43Dy8m83lXy1o83lXy834Yy8n8k1l834Yy0000001m1m8x834Yy1m8y83-56ykxk0k0");
    temp = The_type_description_of_plot_data_ring_buffer;
    The_type_description_of_plot_data_ring_buffer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_93));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_plot_data_ring_buffer_g2_struct,
	    The_type_description_of_plot_data_ring_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qplot_data_ring_buffer,
	    The_type_description_of_plot_data_ring_buffer,
	    Qtype_description_of_type);
    Qoutstanding_plot_data_ring_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-PLOT-DATA-RING-BUFFER-COUNT",
	    AB_package);
    Qplot_data_ring_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("PLOT-DATA-RING-BUFFER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_94 = STATIC_STRING("1q83lXy8s83-j-y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_plot_data_ring_buffer_count);
    push_optimized_constant(Qplot_data_ring_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_94));
    Qchain_of_available_plot_data_ring_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PLOT-DATA-RING-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_plot_data_ring_buffers,
	    Chain_of_available_plot_data_ring_buffers);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_plot_data_ring_buffers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qplot_data_ring_buffer_count = 
	    STATIC_SYMBOL("PLOT-DATA-RING-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplot_data_ring_buffer_count,
	    Plot_data_ring_buffer_count);
    record_system_variable(Qplot_data_ring_buffer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_plot_data_ring_buffers_vector == UNBOUND)
	Chain_of_available_plot_data_ring_buffers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qplot_data_ring_buffer_structure_memory_usage,
	    STATIC_FUNCTION(plot_data_ring_buffer_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_plot_data_ring_buffer_count,
	    STATIC_FUNCTION(outstanding_plot_data_ring_buffer_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_plot_data_ring_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_plot_data_ring_buffer,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qplot_data_ring_buffer,
	    reclaim_structure_for_plot_data_ring_buffer_1);
    Qdata_buffer_for_plot = STATIC_SYMBOL("DATA-BUFFER-FOR-PLOT",AB_package);
    Qreclaim_data_buffer_for_plot_value = 
	    STATIC_SYMBOL("RECLAIM-DATA-BUFFER-FOR-PLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_data_buffer_for_plot_value,
	    STATIC_FUNCTION(reclaim_data_buffer_for_plot_value,NIL,FALSE,2,2));
    mutate_global_property(Qdata_buffer_for_plot,
	    SYMBOL_FUNCTION(Qreclaim_data_buffer_for_plot_value),
	    Qslot_value_reclaimer);
    if (Joes_graph_hax_p == UNBOUND)
	Joes_graph_hax_p = Nil;
    if (Joes_graph_hax_trace_p == UNBOUND)
	Joes_graph_hax_trace_p = Nil;
    if (Current_graph_grid_in_minimal_update == UNBOUND)
	Current_graph_grid_in_minimal_update = Nil;
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qbackground_colors = STATIC_SYMBOL("BACKGROUND-COLORS",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qdraw_for_graph = STATIC_SYMBOL("DRAW-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_graph,STATIC_FUNCTION(draw_for_graph,NIL,
	    FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_graph);
    set_get(Qgraph,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    Qdisplay_up_to_date_qm = STATIC_SYMBOL("DISPLAY-UP-TO-DATE\?",AB_package);
    Qscrolling = STATIC_SYMBOL("SCROLLING",AB_package);
    Qdraw_for_graph_grid = STATIC_SYMBOL("DRAW-FOR-GRAPH-GRID",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_graph_grid,
	    STATIC_FUNCTION(draw_for_graph_grid,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdraw_for_graph_grid);
    set_get(Qgraph_grid,Qdraw,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph_grid,temp);
    mutate_global_property(Qdraw,temp_2,Qclasses_which_define);
    if (Bogus_preflight_from_printing_to_graphs == UNBOUND)
	Bogus_preflight_from_printing_to_graphs = Nil;
    Qadd_graph_rendering = STATIC_SYMBOL("ADD-GRAPH-RENDERING",AB_package);
    Qpolychrome_raster = STATIC_SYMBOL("POLYCHROME-RASTER",AB_package);
    Qmonochrome_raster_list = STATIC_SYMBOL("MONOCHROME-RASTER-LIST",
	    AB_package);
    Qmonochrome_raster = STATIC_SYMBOL("MONOCHROME-RASTER",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhorizontal_grid_line_spacing,
	    Horizontal_grid_line_spacing);
    SET_SYMBOL_VALUE_LOCATION(Qvertical_grid_line_spacing,
	    Vertical_grid_line_spacing);
    Qminimum_x_value_for_new_data = 
	    STATIC_SYMBOL("MINIMUM-X-VALUE-FOR-NEW-DATA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_x_value_for_new_data,
	    Minimum_x_value_for_new_data);
    record_system_variable(Qminimum_x_value_for_new_data,Qgraphs1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qminimum_y_value_for_new_data = 
	    STATIC_SYMBOL("MINIMUM-Y-VALUE-FOR-NEW-DATA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_y_value_for_new_data,
	    Minimum_y_value_for_new_data);
    record_system_variable(Qminimum_y_value_for_new_data,Qgraphs1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qmaximum_x_value_for_new_data = 
	    STATIC_SYMBOL("MAXIMUM-X-VALUE-FOR-NEW-DATA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_x_value_for_new_data,
	    Maximum_x_value_for_new_data);
    record_system_variable(Qmaximum_x_value_for_new_data,Qgraphs1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qmaximum_y_value_for_new_data = 
	    STATIC_SYMBOL("MAXIMUM-Y-VALUE-FOR-NEW-DATA",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_y_value_for_new_data,
	    Maximum_y_value_for_new_data);
    record_system_variable(Qmaximum_y_value_for_new_data,Qgraphs1,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qnew_dateline_qm = STATIC_SYMBOL("NEW-DATELINE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnew_dateline_qm,New_dateline_qm);
    record_system_variable(Qnew_dateline_qm,Qgraphs1,Nil,Qnil,Qnil,Qnil,Qnil);
    if (Current_minimal_grid_draw_has_seen_one_image_plane_p == UNBOUND)
	Current_minimal_grid_draw_has_seen_one_image_plane_p = Nil;
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    float_constant_6 = STATIC_FLOAT(0.3);
    Offset_ratio_for_plot_markers = float_constant_6;
    Default_marker_size = FIX((SI_Long)10L);
    Default_marker_half_size = FIX((SI_Long)5L);
    Plus_sign_marker_size = FIX((SI_Long)14L);
    Plus_sign_marker_half_size = FIX((SI_Long)7L);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qclear_solid_rectangle = STATIC_SYMBOL("CLEAR-SOLID-RECTANGLE",AB_package);
    Qgraph_dateline = STATIC_SYMBOL("GRAPH-DATELINE",AB_package);
    Qdata_extrema = STATIC_SYMBOL("DATA-EXTREMA",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    Qclear_graph = STATIC_SYMBOL("CLEAR-GRAPH",AB_package);
    Qgraph_color_to_use = STATIC_SYMBOL("GRAPH-COLOR-TO-USE",AB_package);
    Qgraph_shading_qm = STATIC_SYMBOL("GRAPH-SHADING\?",AB_package);
    Qgraph_line_width_to_use = STATIC_SYMBOL("GRAPH-LINE-WIDTH-TO-USE",
	    AB_package);
    Qgraph_marker = STATIC_SYMBOL("GRAPH-MARKER",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qmake_graph_rendering_structure_if_necessary = 
	    STATIC_SYMBOL("MAKE-GRAPH-RENDERING-STRUCTURE-IF-NECESSARY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_graph_rendering_structure_if_necessary,
	    STATIC_FUNCTION(make_graph_rendering_structure_if_necessary,
	    NIL,FALSE,1,1));
    Qchart_call_back = STATIC_SYMBOL("CHART-CALL-BACK",AB_package);
    Q2d_call_back_full = STATIC_SYMBOL("2D-CALL-BACK-FULL",AB_package);
    Q2d_call_back_partial = STATIC_SYMBOL("2D-CALL-BACK-PARTIAL",AB_package);
    Qsquare = STATIC_SYMBOL("SQUARE",AB_package);
    Qplus_sign = STATIC_SYMBOL("PLUS-SIGN",AB_package);
    Qab_star = STATIC_SYMBOL("STAR",AB_package);
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    Qgraph_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-HEADING-TEXT-CELL-FORMAT",AB_package);
    string_constant_95 = STATIC_STRING("1p83-Qy83kyk83iy30ey");
    mutate_global_property(Qgraph_heading_text_cell_format,
	    regenerate_optimized_constant(string_constant_95),
	    Qformat_description);
    Qgraph_horizontal_axis_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-HORIZONTAL-AXIS-HEADING-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_96 = 
	    STATIC_STRING("1v83-Qy83kyk83wy83-cy83aym83cym83iy30ey");
    mutate_global_property(Qgraph_horizontal_axis_heading_text_cell_format,
	    regenerate_optimized_constant(string_constant_96),
	    Qformat_description);
    Qgraph_vertical_axis_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-VERTICAL-AXIS-HEADING-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_97 = STATIC_STRING("1p83-Qy83kyk83iy3-Wy");
    mutate_global_property(Qgraph_vertical_axis_heading_text_cell_format,
	    regenerate_optimized_constant(string_constant_97),
	    Qformat_description);
    Qcorner_empty_text_cell_format = 
	    STATIC_SYMBOL("CORNER-EMPTY-TEXT-CELL-FORMAT",AB_package);
    mutate_global_property(Qcorner_empty_text_cell_format,
	    regenerate_optimized_constant(string_constant_97),
	    Qformat_description);
    Qgraph_axis_label_format = STATIC_SYMBOL("GRAPH-AXIS-LABEL-FORMAT",
	    AB_package);
    string_constant_98 = 
	    STATIC_STRING("13Ny83-My83*=yk83*1yk83*0yk83**yk83byk83ayk83Wyk83cyk83kyk83-=yk83-By083iy32qy83*ay32qy");
    mutate_global_property(Qgraph_axis_label_format,
	    regenerate_optimized_constant(string_constant_98),
	    Qformat_description);
    Qlabel_permanent_qm = STATIC_SYMBOL("LABEL-PERMANENT\?",AB_package);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qreformat_as_appropriate_for_graph = 
	    STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qreformat_as_appropriate_for_graph,
	    STATIC_FUNCTION(reformat_as_appropriate_for_graph,NIL,FALSE,2,2));
    Qreformat_as_appropriate = STATIC_SYMBOL("REFORMAT-AS-APPROPRIATE",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qreformat_as_appropriate_for_graph);
    set_get(Qgraph,Qreformat_as_appropriate,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qreformat_as_appropriate),
	    Qclasses_which_define);
    temp_2 = CONS(Qgraph,temp);
    mutate_global_property(Qreformat_as_appropriate,temp_2,
	    Qclasses_which_define);
}
