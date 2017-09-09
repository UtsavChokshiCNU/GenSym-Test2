/* grphs2.c
 * Input file:  graphs2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "grphs2.h"


/* UPDATE-DISPLAY-FOR-GRAPH */
Object update_display_for_graph(graph,update_even_if_value_unchanged_qm,
	    wake_up_qm,update_even_if_not_showing_qm)
    Object graph, update_even_if_value_unchanged_qm, wake_up_qm;
    Object update_even_if_not_showing_qm;
{
    Object redraw_as_well_as_reformat_p, temp, graph_grid;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,0);
    if (((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & (SI_Long)1L) || 
	    (SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)4L)) & 
	    (SI_Long)16777216L)) && (update_even_if_not_showing_qm || 
	    rectangle_visible_p(graph))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if ( !((SI_Long)0L != (IFIX(ISVREF(graph,(SI_Long)5L)) & 
		    (SI_Long)2048L))) {
		redraw_as_well_as_reformat_p = T;
		temp = ISVREF(graph,(SI_Long)19L);
		temp = FIRST(temp);
		graph_grid = FIRST(temp);
		PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
			0);
		  result = make_or_reformat_graph_grid(5,Nil,graph_grid,
			  ISVREF(graph,(SI_Long)22L),
			  update_even_if_not_showing_qm,T);
		POP_SPECIAL();
	    }
	    else
		result = VALUES_1(Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qgraph_reformatted_since_start_qm;  /* graph-reformatted-since-start? */

/* CLEAR-DISPLAY-FOR-GRAPH */
Object clear_display_for_graph(graph)
    Object graph;
{
    Object redraw_as_well_as_reformat_p, temp, graph_grid, plot, ab_loop_list_;
    Declare_special(1);

    x_note_fn_call(173,1);
    redraw_as_well_as_reformat_p = Nil;
    temp = ISVREF(graph,(SI_Long)19L);
    temp = FIRST(temp);
    graph_grid = FIRST(temp);
    PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
	    0);
      plot = Nil;
      ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      plot = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      clear_plot(plot);
      goto next_loop;
    end_loop:;
      make_or_reformat_graph_grid(5,Nil,graph_grid,ISVREF(graph,
	      (SI_Long)22L),T,Nil);
      if ( !TRUEP(Transfer_in_progress))
	  update_images_of_graph_grid_and_data(Nil,graph_grid);
    POP_SPECIAL();
    return set_non_savable_lookup_slot_value(graph,
	    Qgraph_reformatted_since_start_qm,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Painting_for_graph_activation_p, Qpainting_for_graph_activation_p);

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qdisplay_wait_interval;  /* display-wait-interval */

static Object Qdisplay_update_interval;  /* display-update-interval */

static Object float_constant;      /* -1.0 */

static Object Qdisplay_update_priority;  /* display-update-priority */

static Object Qupdate_display_for_graph;  /* update-display-for-graph */

static Object Qgraph;              /* graph */

/* ACTIVATE-FOR-GRAPH */
Object activate_for_graph(graph)
    Object graph;
{
    Object old, new_1, def_structure_schedule_task_variable, temp, temp_1;
    Object svref_new_value, task, thing, structure_being_reclaimed, frame;
    Object sub_vector_qm, method_function_qm, temp_2, graph_grid_qm;
    Object redraw_as_well_as_reformat_p, painting_for_graph_activation_p;
    SI_Long index_1, ab_loop_bind_;
    char svref_new_value_1;
    double gensymed_symbol, gensymed_symbol_1, aref_new_value;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,2);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(graph,(SI_Long)20L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,temp_1) = svref_new_value;
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
	temp = ISVREF(task,(SI_Long)1L);
	gensymed_symbol = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	gensymed_symbol_1 = FIXNUMP(get_lookup_slot_value(graph,
		Qdisplay_wait_interval)) ? 
		(double)IFIX(get_lookup_slot_value(graph,
		Qdisplay_wait_interval)) : 
		DFLOAT_ISAREF_1(get_lookup_slot_value(graph,
		Qdisplay_wait_interval),(SI_Long)0L);
	aref_new_value = gensymed_symbol + gensymed_symbol_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp_1 = ISVREF(task,(SI_Long)1L);
	if (FIXNUMP(get_lookup_slot_value(graph,Qdisplay_update_interval)))
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(get_lookup_slot_value(graph,
		    Qdisplay_update_interval)));
	else {
	    thing = get_lookup_slot_value(graph,Qdisplay_update_interval);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(get_lookup_slot_value(graph,
			Qdisplay_update_interval),(SI_Long)0L));
	    else
		temp = float_constant;
	}
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	temp = get_lookup_slot_value(graph,Qdisplay_update_priority);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qupdate_display_for_graph;
	temp = SYMBOL_FUNCTION(Qupdate_display_for_graph);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)4L);
	SVREF(task,FIX((SI_Long)13L)) = graph;
	SVREF(task,FIX((SI_Long)14L)) = Nil;
	SVREF(task,FIX((SI_Long)15L)) = Nil;
	SVREF(task,FIX((SI_Long)16L)) = Nil;
	new_1 = task;
	if (CAS_SVREF(graph,(SI_Long)20L,old,new_1)) {
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
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = old;
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
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    frame = graph;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgraph)) {
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
    set_non_savable_lookup_slot_value(graph,
	    Qgraph_reformatted_since_start_qm,Nil);
    temp_2 = ISVREF(graph,(SI_Long)19L);
    temp_2 = FIRST(temp_2);
    graph_grid_qm = FIRST(temp_2);
    if (graph_grid_qm) {
	make_graph_not_up_to_date(graph_grid_qm);
	redraw_as_well_as_reformat_p = Transfer_in_progress ? Nil : T;
	painting_for_graph_activation_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Painting_for_graph_activation_p,Qpainting_for_graph_activation_p,painting_for_graph_activation_p,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		  0);
	    result = make_or_reformat_graph_grid(5,Nil,graph_grid_qm,
		    ISVREF(graph,(SI_Long)22L),T,T);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qdisplay_up_to_date_qm;  /* display-up-to-date? */

static Object Qthings_this_display_is_interested_in;  /* things-this-display-is-interested-in */

/* DEACTIVATE-FOR-GRAPH */
Object deactivate_for_graph(graph)
    Object graph;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object gensymed_symbol_1, variable, ab_loop_list_, pruned_interest_list;
    Object eval_list, last_1, next_qm, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(173,3);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(graph,(SI_Long)20L);
    if (CAS_SVREF(graph,(SI_Long)20L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
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
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = ISVREF(graph,(SI_Long)21L);
    if (CAS_SVREF(graph,(SI_Long)21L,gensymed_symbol,Nil)) {
	if (gensymed_symbol) {
	    if (EQ(gensymed_symbol,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(gensymed_symbol,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol);
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    structure_being_reclaimed = gensymed_symbol;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(gensymed_symbol,(SI_Long)9L));
	      SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol;
	}
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(graph,(SI_Long)1L),
	    (SI_Long)11L),(SI_Long)21L),(SI_Long)1L);
    gensymed_symbol_1 = graph;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    set_non_savable_lookup_slot_value(graph,Qdisplay_up_to_date_qm,Nil);
    variable = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(graph,
	    Qthings_this_display_is_interested_in,Nil);
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pruned_interest_list = delete_eval_element_1(graph,ISVREF(variable,
	    (SI_Long)36L));
    ISVREF(variable,(SI_Long)36L) = pruned_interest_list;
    if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable,
	    (SI_Long)38L)))
	withdraw_backward_chaining(variable);
    goto next_loop_2;
  end_loop_2:;
    eval_list = get_lookup_slot_value_given_default(graph,
	    Qthings_this_display_is_interested_in,Nil);
    if (eval_list) {
	last_1 = eval_list;
	next_qm = Nil;
      next_loop_3:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_3;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_3;
      end_loop_3:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = eval_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    set_non_savable_lookup_slot_value(graph,
	    Qthings_this_display_is_interested_in,Nil);
    frame = graph;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_4:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_4;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgraph)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_3;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_4;
  end_loop_4:
    method_function_qm = Qnil;
  end_3:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

/* CLEAR-PLOT */
Object clear_plot(plot)
    Object plot;
{
    Object data_buffer_for_plot, current_block_of_dependent_frame;
    Object svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(173,4);
    data_buffer_for_plot = ISVREF(plot,(SI_Long)5L);
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      svref_new_value = store_managed_number_or_value_function(ISVREF(plot,
	      (SI_Long)6L),Nil);
      ISVREF(plot,(SI_Long)6L) = svref_new_value;
      svref_new_value = store_managed_number_or_value_function(ISVREF(plot,
	      (SI_Long)7L),Nil);
      ISVREF(plot,(SI_Long)7L) = svref_new_value;
      svref_new_value = store_managed_number_or_value_function(ISVREF(plot,
	      (SI_Long)8L),Nil);
      ISVREF(plot,(SI_Long)8L) = svref_new_value;
      svref_new_value = store_managed_number_or_value_function(ISVREF(plot,
	      (SI_Long)9L),Nil);
      ISVREF(plot,(SI_Long)9L) = svref_new_value;
      if (data_buffer_for_plot) {
	  ISVREF(data_buffer_for_plot,(SI_Long)2L) = FIX((SI_Long)0L);
	  ISVREF(data_buffer_for_plot,(SI_Long)1L) = FIX((SI_Long)0L);
	  SVREF(data_buffer_for_plot,FIX((SI_Long)3L)) = T;
	  result = clear_plot_marker_data(data_buffer_for_plot);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qexpressions_to_display;  /* expressions-to-display */

/* MAKE-HORIZONTAL-AXIS-GRAPH-HEADING-TEXT */
Object make_horizontal_axis_graph_heading_text(graph)
    Object graph;
{
    x_note_fn_call(173,5);
    return make_horizontal_axis_graph_heading_text_1(graph,
	    Qexpressions_to_display,Nil);
}

static Object Qformat_frame;       /* format-frame */

static Object Qgraph_horizontal_axis_heading_text_cell_format;  /* graph-horizontal-axis-heading-text-cell-format */

/* MAKE-HORIZONTAL-AXIS-GRAPH-HEADING-TEXT-1 */
Object make_horizontal_axis_graph_heading_text_1(graph,slot_name,
	    class_qualifier_qm)
    Object graph, slot_name, class_qualifier_qm;
{
    Object temp, temp_1;

    x_note_fn_call(173,6);
    temp = get_type_of_slot_if_any(2,graph,slot_name);
    temp_1 = get_instance_with_name_if_any(Qformat_frame,
	    Qgraph_horizontal_axis_heading_text_cell_format);
    if (temp_1);
    else
	temp_1 = 
		make_format_frame(Qgraph_horizontal_axis_heading_text_cell_format);
    return make_text_cell_for_slot(5,graph,slot_name,class_qualifier_qm,
	    temp,temp_1);
}

static Object Qdefault_graph_format;  /* default-graph-format */

static Object Qgraph_format;       /* graph-format */

static Object Qslot_group_for_block_qm;  /* slot-group-for-block? */

static Object Qtable_rows;         /* table-rows */

static Object Qtable_format_for_graphs;  /* table-format-for-graphs */

/* MAKE-GRAPH */
Object make_graph(graph_type)
    Object graph_type;
{
    Object new_graph, new_graph_format, redraw_as_well_as_reformat_p;
    Object new_graph_grid, gensymed_symbol, gensymed_symbol_1, slot_group_qm;
    Object temp, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(173,7);
    new_graph = make_frame(graph_type);
    new_graph_format = get_instance_with_name_if_any(Qformat_frame,
	    Qdefault_graph_format);
    if (new_graph_format);
    else
	new_graph_format = make_format_frame(Qdefault_graph_format);
    redraw_as_well_as_reformat_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
	    0);
      new_graph_grid = Nil;
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(new_graph,Qgraph_format);
      SVREF(new_graph,FIX((SI_Long)22L)) = new_graph_format;
      new_graph_grid = make_or_reformat_graph_grid(5,new_graph,Nil,
	      ISVREF(new_graph,(SI_Long)22L),Nil,Nil);
      gensymed_symbol = new_graph_grid;
      gensymed_symbol_1 = Nil;
      slot_group_qm = ISVREF(gensymed_symbol,(SI_Long)14L);
      gensymed_symbol_1 = new_graph;
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
      add_subblock(new_graph_grid,new_graph);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(new_graph,Qtable_rows);
      temp_1 = slot_value_cons_1(new_graph_grid,Nil);
      temp = slot_value_list_2(temp_1,
	      slot_value_cons_1(make_horizontal_axis_graph_heading_text(new_graph),
	      Nil));
      SVREF(new_graph,FIX((SI_Long)19L)) = temp;
      temp_1 = get_instance_with_name_if_any(Qformat_frame,
	      Qtable_format_for_graphs);
      if (temp_1);
      else
	  temp_1 = make_format_frame(Qtable_format_for_graphs);
      make_or_reformat_table(3,new_graph,temp_1,Nil);
      put_up_label_for_graph_horizontal_axis(new_graph_grid,new_graph_format);
      add_frame_representation_if_necessary(new_graph,new_graph);
      result = VALUES_1(new_graph);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_grid_width, Qminimum_grid_width);

DEFINE_VARIABLE_WITH_SYMBOL(Minimum_grid_height, Qminimum_grid_height);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_low_value_for_horizontal_axis, Qdesired_low_value_for_horizontal_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_high_value_for_horizontal_axis, Qdesired_high_value_for_horizontal_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_low_value_for_vertical_axis, Qdesired_low_value_for_vertical_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Desired_high_value_for_vertical_axis, Qdesired_high_value_for_vertical_axis);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_horizontal_grid_lines, Qnumber_of_horizontal_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_vertical_grid_lines, Qnumber_of_vertical_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Low_value_for_horizontal_grid_lines, Qlow_value_for_horizontal_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(High_value_for_horizontal_grid_lines, Qhigh_value_for_horizontal_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Interval_between_horizontal_grid_lines, Qinterval_between_horizontal_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Low_value_for_vertical_grid_lines, Qlow_value_for_vertical_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(High_value_for_vertical_grid_lines, Qhigh_value_for_vertical_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Interval_between_vertical_grid_lines, Qinterval_between_vertical_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Label_scale_for_vertical_grid_lines, Qlabel_scale_for_vertical_grid_lines);

DEFINE_VARIABLE_WITH_SYMBOL(Problems_reformatting_graph_qm, Qproblems_reformatting_graph_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Finished_storing_in_plot_data_1_qm, Qfinished_storing_in_plot_data_1_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Changing_graph_margins_qm, Qchanging_graph_margins_qm);

static Object Qgraph_grid;         /* graph-grid */

static Object Qwithout_tickmark_labels;  /* without-tickmark-labels */

static Object Qhorizontal;         /* horizontal */

static Object Qvertical;           /* vertical */

/* MAKE-OR-REFORMAT-GRAPH-GRID */
Object make_or_reformat_graph_grid varargs_1(int, n)
{
    Object new_graph_qm, graph_grid_qm, graph_format, enforce_reformatting_qm;
    Object refresh_plot_data_buffers_qm;
    Object delta_left_edge_qm, delta_top_edge_qm, delta_right_edge_qm;
    Object delta_bottom_edge_qm, graph_grid, graph, gensymed_symbol;
    Object current_computation_frame, current_computation_instance;
    Object minimum_grid_width, minimum_grid_height;
    Object horizontal_axis_grid_format_not_changed_p;
    Object vertical_axis_grid_format_not_changed_p;
    Object problems_reformatting_graph_qm, parse_var;
    Object without_horizontal_labels_qm, without_vertical_labels_qm;
    Object minimum_graph_left_and_right_margin_width;
    Object minimum_graph_top_and_bottom_margin_width, svref_new_value, temp;
    Object temp_1, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, width_of_graph_grid_block;
    SI_Long height_of_graph_grid_block, svref_new_value_1, temp_4;
    char graph_grid_slots_not_cached_qm;
    double temp_3;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,8);
    INIT_ARGS_nonrelocating();
    new_graph_qm = REQUIRED_ARG_nonrelocating();
    graph_grid_qm = REQUIRED_ARG_nonrelocating();
    graph_format = REQUIRED_ARG_nonrelocating();
    enforce_reformatting_qm = REQUIRED_ARG_nonrelocating();
    refresh_plot_data_buffers_qm = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    delta_left_edge_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    delta_top_edge_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    delta_right_edge_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    delta_bottom_edge_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    graph_grid = graph_grid_qm ? graph_grid_qm : make_frame(Qgraph_grid);
    graph = new_graph_qm;
    if (graph);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
    }
    LOCK(Working_on_lexical_computation_of_frame);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_computation_frame = graph;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		4);
	  current_computation_instance = graph;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		  3);
	    minimum_grid_width = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Minimum_grid_width,Qminimum_grid_width,minimum_grid_width,
		    2);
	      minimum_grid_height = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Minimum_grid_height,Qminimum_grid_height,minimum_grid_height,
		      1);
		horizontal_axis_grid_format_not_changed_p = Nil;
		vertical_axis_grid_format_not_changed_p = Nil;
		graph_grid_slots_not_cached_qm =  !TRUEP(ISVREF(graph_grid,
			(SI_Long)38L));
		problems_reformatting_graph_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Problems_reformatting_graph_qm,Qproblems_reformatting_graph_qm,problems_reformatting_graph_qm,
			0);
		  parse_var = ISVREF(graph,(SI_Long)23L);
		  if (CONSP(parse_var) && EQ(CAR(parse_var),
			  Qwithout_tickmark_labels))
		      result = VALUES_2(CDR(parse_var),T);
		  else
		      result = VALUES_2(parse_var,Nil);
		  gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
		  without_horizontal_labels_qm = gensymed_symbol;
		  parse_var = ISVREF(graph,(SI_Long)24L);
		  if (CONSP(parse_var) && EQ(CAR(parse_var),
			  Qwithout_tickmark_labels))
		      result = VALUES_2(CDR(parse_var),T);
		  else
		      result = VALUES_2(parse_var,Nil);
		  gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
		  without_vertical_labels_qm = gensymed_symbol;
		  if (bad_plot_range_specs_qm(graph) || 
			  bad_desired_range_too_small_qm(graph) || 
			  bad_horizontal_range_zero_qm(graph))
		      enforce_reformatting_qm = T;
		  delete_all_frame_notes_for_graph(graph);
		  if (graph_grid_slots_not_cached_qm || 
			  Changing_graph_margins_qm) {
		      minimum_graph_left_and_right_margin_width = 
			      ISVREF(graph_format,(SI_Long)24L);
		      minimum_graph_top_and_bottom_margin_width = 
			      ISVREF(graph_format,(SI_Long)25L);
		      ISVREF(graph_grid,(SI_Long)38L) = 
			      minimum_graph_left_and_right_margin_width;
		      svref_new_value = 
			      lfloor(minimum_graph_left_and_right_margin_width,
			      FIX((SI_Long)16L));
		      ISVREF(graph_grid,(SI_Long)39L) = svref_new_value;
		      svref_new_value = 
			      lfloor(minimum_graph_top_and_bottom_margin_width,
			      FIX((SI_Long)4L));
		      ISVREF(graph_grid,(SI_Long)40L) = svref_new_value;
		      ISVREF(graph_grid,(SI_Long)41L) = 
			      minimum_graph_top_and_bottom_margin_width;
		      if (without_horizontal_labels_qm) {
			  remove_axis_labels_from_graph_grid(Qhorizontal,
				  graph_grid);
			  ISVREF(graph_grid,(SI_Long)41L) = FIX((SI_Long)2L);
		      }
		      if (without_vertical_labels_qm) {
			  remove_axis_labels_from_graph_grid(Qvertical,
				  graph_grid);
			  ISVREF(graph_grid,(SI_Long)38L) = FIX((SI_Long)5L);
		      }
		      if ( !TRUEP(delta_left_edge_qm)) {
			  delta_left_edge_qm = FIX((SI_Long)0L);
			  delta_right_edge_qm = FIX((SI_Long)0L);
			  delta_top_edge_qm = FIX((SI_Long)0L);
			  delta_bottom_edge_qm = FIX((SI_Long)0L);
		      }
		  }
		  if (new_graph_qm || delta_left_edge_qm) {
		      if (new_graph_qm)
			  set_edges_of_block(graph_grid,FIX((SI_Long)0L),
				  FIX((SI_Long)0L),ISVREF(graph_format,
				  (SI_Long)31L),ISVREF(graph_format,
				  (SI_Long)32L));
		      else {
			  decache_and_remove_all_graph_renderings_from_graph_grid(graph_grid);
			  gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)0L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol_2 = IFIX(delta_left_edge_qm);
			  temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
			  gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)1L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol_2 = IFIX(delta_top_edge_qm);
			  temp_1 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
			  gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)2L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol_2 = IFIX(delta_right_edge_qm);
			  temp_2 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
			  gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
			  gensymed_symbol = gensymed_symbol ? 
				  ISVREF(gensymed_symbol,(SI_Long)3L) : 
				  FIX((SI_Long)0L);
			  gensymed_symbol_1 = IFIX(gensymed_symbol);
			  gensymed_symbol_2 = IFIX(delta_bottom_edge_qm);
			  change_edges_of_block(graph_grid,temp,temp_1,
				  temp_2,FIX(gensymed_symbol_1 + 
				  gensymed_symbol_2));
		      }
		  }
		  if (graph_grid_slots_not_cached_qm || new_graph_qm || 
			  delta_left_edge_qm) {
		      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)2L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)0L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_2 = IFIX(gensymed_symbol);
		      width_of_graph_grid_block = gensymed_symbol_1 - 
			      gensymed_symbol_2;
		      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)3L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_1 = IFIX(gensymed_symbol);
		      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		      gensymed_symbol = gensymed_symbol ? 
			      ISVREF(gensymed_symbol,(SI_Long)1L) : 
			      FIX((SI_Long)0L);
		      gensymed_symbol_2 = IFIX(gensymed_symbol);
		      height_of_graph_grid_block = gensymed_symbol_1 - 
			      gensymed_symbol_2;
		      svref_new_value_1 = width_of_graph_grid_block - 
			      IFIX(FIXNUM_ADD(ISVREF(graph_grid,
			      (SI_Long)38L),ISVREF(graph_grid,(SI_Long)39L)));
		      ISVREF(graph_grid,(SI_Long)34L) = FIX(svref_new_value_1);
		      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			  temp_3 = DOUBLE_FLOAT_TO_DOUBLE(Erase_zone_ratio);
			  temp_4 = 
				  inline_floor_1((double)IFIX(ISVREF(graph_grid,
				  (SI_Long)34L)) * temp_3);
			  svref_new_value_1 = temp_4 + 
				  IFIX(ISVREF(graph_grid,(SI_Long)34L));
		      }
		      POP_LOCAL_ALLOCATION(0,0);
		      ISVREF(graph_grid,(SI_Long)59L) = FIX(svref_new_value_1);
		      svref_new_value_1 = height_of_graph_grid_block - 
			      IFIX(FIXNUM_ADD(ISVREF(graph_grid,
			      (SI_Long)40L),ISVREF(graph_grid,(SI_Long)41L)));
		      ISVREF(graph_grid,(SI_Long)35L) = FIX(svref_new_value_1);
		  }
		  Minimum_grid_width = ISVREF(graph_grid,(SI_Long)34L);
		  Minimum_grid_height = ISVREF(graph_grid,(SI_Long)35L);
		  if (graph_grid_qm && 
			  get_lookup_slot_value_given_default(graph,
			  Qgraph_reformatted_since_start_qm,Nil) && 
			  get_lookup_slot_value_given_default(graph,
			  Qdisplay_up_to_date_qm,Nil) &&  
			  !TRUEP(enforce_reformatting_qm) && 
			  ISVREF(graph_format,(SI_Long)52L) &&  
			  !TRUEP(graph_must_be_refreshed_for_old_data_qm(graph_grid))) 
			      {
		      if ( 
			      !(need_to_reformat_horizontal_axis_qm(graph_grid,
			      graph_format,refresh_plot_data_buffers_qm) 
			      && 
			      compute_new_parameters_for_horizontal_axis_of_grid(5,
			      graph_grid,graph_format,
			      refresh_plot_data_buffers_qm,T,ISVREF(graph,
			      (SI_Long)25L))))
			  horizontal_axis_grid_format_not_changed_p = T;
		      if (refresh_plot_data_buffers_qm)
			  refresh_data_for_plots(graph_grid,graph_format,
				  horizontal_axis_grid_format_not_changed_p);
		      if (need_to_reformat_vertical_axis_qm(graph_grid,
			      graph_format)) {
			  if (horizontal_axis_grid_format_not_changed_p) {
			      horizontal_axis_grid_format_not_changed_p = Nil;
			      compute_new_parameters_for_horizontal_axis_of_grid(3,
				      graph_grid,graph_format,
				      refresh_plot_data_buffers_qm);
			      if (refresh_plot_data_buffers_qm)
				  refresh_data_for_plots(graph_grid,
					  graph_format,
					  horizontal_axis_grid_format_not_changed_p);
			  }
			  compute_new_parameters_for_vertical_axis_of_grid(graph_grid,
				  graph_format);
		      }
		      else
			  vertical_axis_grid_format_not_changed_p = T;
		  }
		  else {
		      compute_new_parameters_for_horizontal_axis_of_grid(3,
			      graph_grid,graph_format,
			      refresh_plot_data_buffers_qm);
		      if (refresh_plot_data_buffers_qm)
			  refresh_data_for_plots(graph_grid,graph_format,Nil);
		      compute_new_parameters_for_vertical_axis_of_grid(graph_grid,
			      graph_format);
		  }
		  scale_y_data_for_plots_if_necessary(graph_grid);
		  if ( !TRUEP(without_horizontal_labels_qm)) {
		      if ( !TRUEP(horizontal_axis_grid_format_not_changed_p)) {
			  parse_var = ISVREF(graph,(SI_Long)23L);
			  if (CONSP(parse_var) && EQ(CAR(parse_var),
				  Qwithout_tickmark_labels))
			      temp = CDR(parse_var);
			  else
			      temp = parse_var;
			  put_up_new_labels_for_horizontal_graph_axis(graph_grid,
				  graph_format, 
				  !TRUEP(absolute_range_specified_p(temp)) 
				  ? T : Nil);
		      }
		      else if ( !FIXNUM_EQ(ISVREF(graph_grid,(SI_Long)50L),
			      ISVREF(graph_grid,(SI_Long)49L)))
			  put_up_new_high_value_label_for_horizontal_axis(graph_grid);
		  }
		  if ( !TRUEP(without_vertical_labels_qm)) {
		      if ( !TRUEP(vertical_axis_grid_format_not_changed_p))
			  put_up_new_labels_for_vertical_graph_axis(graph_grid,
				  graph_format);
		  }
		  set_non_savable_lookup_slot_value(graph,
			  Qdisplay_up_to_date_qm,T);
		  if (Redraw_as_well_as_reformat_p) {
		      if (horizontal_axis_grid_format_not_changed_p && 
			      vertical_axis_grid_format_not_changed_p &&  
			      !TRUEP(enforce_reformatting_qm))
			  update_images_of_only_new_data_for_graph_grid(Nil,
				  graph_grid);
		      else
			  update_images_of_graph_grid_and_data(Nil,graph_grid);
		  }
		  set_non_savable_lookup_slot_value(graph,
			  Qgraph_reformatted_since_start_qm,T);
		  if (Redraw_as_well_as_reformat_p && 
			  Problems_reformatting_graph_qm)
		      post_reformat_warning_note_for_graph(graph);
		  SAVE_VALUES(VALUES_1(graph_grid));
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Working_on_lexical_computation_of_frame);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object Minimum_grid_width_for_resizing_graph = UNBOUND;

Object Minimum_grid_height_for_resizing_graph = UNBOUND;

/* CHANGE-SIZE-OF-GRAPH */
Object change_size_of_graph(graph,left_edge_of_bounding_box,
	    top_edge_of_bounding_box,right_edge_of_bounding_box,
	    bottom_edge_of_bounding_box)
    Object graph, left_edge_of_bounding_box, top_edge_of_bounding_box;
    Object right_edge_of_bounding_box, bottom_edge_of_bounding_box;
{
    Object region_invalidation_is_preferred, gensymed_symbol_1;
    Object redraw_as_well_as_reformat_p, temp, graph_grid, temp_1, temp_2;
    Object temp_4, width_adjustment, height_adjustment;
    SI_Long gensymed_symbol, gensymed_symbol_2, delta_left_edge;
    SI_Long delta_top_edge, gensymed_symbol_3;
    char temp_3;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,9);
    region_invalidation_is_preferred = T;
    PUSH_SPECIAL_WITH_SYMBOL(Region_invalidation_is_preferred,Qregion_invalidation_is_preferred,region_invalidation_is_preferred,
	    1);
      update_images_of_block(graph,T,Nil);
      gensymed_symbol = IFIX(left_edge_of_bounding_box);
      gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)0L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      delta_left_edge = gensymed_symbol - gensymed_symbol_2;
      gensymed_symbol = IFIX(top_edge_of_bounding_box);
      gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
      gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	      (SI_Long)1L) : FIX((SI_Long)0L);
      gensymed_symbol_2 = IFIX(gensymed_symbol_1);
      delta_top_edge = gensymed_symbol - gensymed_symbol_2;
      change_edges_of_block(graph,left_edge_of_bounding_box,
	      top_edge_of_bounding_box,Nil,Nil);
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  redraw_as_well_as_reformat_p = Nil;
	  temp = ISVREF(graph,(SI_Long)19L);
	  temp = FIRST(temp);
	  graph_grid = FIRST(temp);
	  PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		  0);
	    temp = ISVREF(graph,(SI_Long)19L);
	    temp = FIRST(temp);
	    temp = FIRST(temp);
	    temp_1 = ISVREF(graph,(SI_Long)22L);
	    gensymed_symbol = IFIX(right_edge_of_bounding_box);
	    gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    temp_2 = FIX(gensymed_symbol - gensymed_symbol_2);
	    gensymed_symbol = IFIX(bottom_edge_of_bounding_box);
	    gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    make_or_reformat_graph_grid(9,Nil,temp,temp_1,T,T,
		    FIX(delta_left_edge),FIX(delta_top_edge),temp_2,
		    FIX(gensymed_symbol - gensymed_symbol_2));
	    reformat_table_in_place(1,graph);
	    gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    if (FIXNUM_EQ(left_edge_of_bounding_box,gensymed_symbol_1)) {
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		temp_3 = FIXNUM_EQ(top_edge_of_bounding_box,gensymed_symbol_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		temp_3 = FIXNUM_EQ(right_edge_of_bounding_box,
			gensymed_symbol_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		temp_3 = FIXNUM_EQ(bottom_edge_of_bounding_box,
			gensymed_symbol_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if ( !temp_3) {
		temp = ISVREF(graph,(SI_Long)22L);
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(left_edge_of_bounding_box);
		temp_1 = FIX(gensymed_symbol - gensymed_symbol_2);
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(top_edge_of_bounding_box);
		temp_2 = FIX(gensymed_symbol - gensymed_symbol_2);
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(right_edge_of_bounding_box);
		temp_4 = FIX(gensymed_symbol - gensymed_symbol_2);
		gensymed_symbol_1 = ISVREF(graph,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = IFIX(bottom_edge_of_bounding_box);
		make_or_reformat_graph_grid(9,Nil,graph_grid,temp,T,T,
			temp_1,temp_2,temp_4,FIX(gensymed_symbol - 
			gensymed_symbol_2));
		reformat_table_in_place(1,graph);
	    }
	    width_adjustment = FIX((SI_Long)0L);
	    height_adjustment = FIX((SI_Long)0L);
	    gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    if (FIXNUM_LT(FIX(gensymed_symbol - gensymed_symbol_2),
		    FIXNUM_ADD(FIXNUM_ADD(ISVREF(graph_grid,(SI_Long)38L),
		    ISVREF(graph_grid,(SI_Long)39L)),
		    Minimum_grid_width_for_resizing_graph))) {
		gensymed_symbol = 
			IFIX(FIXNUM_ADD(FIXNUM_ADD(ISVREF(graph_grid,
			(SI_Long)38L),ISVREF(graph_grid,(SI_Long)39L)),
			Minimum_grid_height_for_resizing_graph));
		gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)2L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)0L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		width_adjustment = FIX(gensymed_symbol - gensymed_symbol_2);
	    }
	    gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    if (FIXNUM_LT(FIX(gensymed_symbol - gensymed_symbol_2),
		    FIXNUM_ADD(FIXNUM_ADD(ISVREF(graph_grid,(SI_Long)40L),
		    ISVREF(graph_grid,(SI_Long)41L)),
		    Minimum_grid_width_for_resizing_graph))) {
		gensymed_symbol = 
			IFIX(FIXNUM_ADD(FIXNUM_ADD(ISVREF(graph_grid,
			(SI_Long)40L),ISVREF(graph_grid,(SI_Long)41L)),
			Minimum_grid_height_for_resizing_graph));
		gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)3L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol_1);
		gensymed_symbol_1 = ISVREF(graph_grid,(SI_Long)14L);
		gensymed_symbol_1 = gensymed_symbol_1 ? 
			ISVREF(gensymed_symbol_1,(SI_Long)1L) : 
			FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol_1);
		gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
		height_adjustment = FIX(gensymed_symbol - gensymed_symbol_2);
	    }
	    if (IFIX(width_adjustment) != (SI_Long)0L || 
		    IFIX(height_adjustment) != (SI_Long)0L) {
		make_or_reformat_graph_grid(9,Nil,graph_grid,ISVREF(graph,
			(SI_Long)22L),T,T,FIX((SI_Long)0L),
			FIX((SI_Long)0L),width_adjustment,height_adjustment);
		reformat_table_in_place(1,graph);
	    }
	  POP_SPECIAL();
      }
      POP_LOCAL_ALLOCATION(0,0);
      enlarge_workspace_for_block_rectangle_if_necessary(graph,Nil);
      result = update_images_of_graph(Nil,graph);
    POP_SPECIAL();
    return result;
}

/* RESTORE-GRAPH-TO-NORMAL-SIZE */
Object restore_graph_to_normal_size(graph)
    Object graph;
{
    Object temp, graph_grid, gensymed_symbol, redraw_as_well_as_reformat_p;
    Object changing_colors_of_graphic_elements_qm;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, delta_right_edge;
    SI_Long delta_bottom_edge;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,10);
    update_images_of_block(graph,T,Nil);
    temp = ISVREF(graph,(SI_Long)19L);
    temp = FIRST(temp);
    graph_grid = FIRST(temp);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(graph,(SI_Long)22L),(SI_Long)31L));
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    delta_right_edge = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(ISVREF(graph,(SI_Long)22L),(SI_Long)32L));
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    delta_bottom_edge = gensymed_symbol_1 - gensymed_symbol_2;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	redraw_as_well_as_reformat_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Redraw_as_well_as_reformat_p,Qredraw_as_well_as_reformat_p,redraw_as_well_as_reformat_p,
		0);
	  make_or_reformat_graph_grid(9,Nil,graph_grid,ISVREF(graph,
		  (SI_Long)22L),T,T,FIX((SI_Long)0L),FIX((SI_Long)0L),
		  FIX(delta_right_edge),FIX(delta_bottom_edge));
	POP_SPECIAL();
	reformat_table_in_place(1,graph);
    }
    POP_LOCAL_ALLOCATION(0,0);
    changing_colors_of_graphic_elements_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
	    0);
      result = update_images_of_block(graph,Nil,Nil);
    POP_SPECIAL();
    return result;
}

/* UPDATE-IMAGES-OF-GRAPH */
Object update_images_of_graph(erase_qm,graph)
    Object erase_qm, graph;
{
    Object temp, graph_grid, changing_colors_of_graphic_elements_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(173,11);
    temp = ISVREF(graph,(SI_Long)19L);
    temp = FIRST(temp);
    graph_grid = FIRST(temp);
    make_graph_not_up_to_date(graph_grid);
    changing_colors_of_graphic_elements_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
	    0);
      result = update_images_of_block(graph,erase_qm,T);
    POP_SPECIAL();
    return result;
}

/* UPDATE-IMAGES-OF-GRAPH-GRID-AND-DATA */
Object update_images_of_graph_grid_and_data(erase_qm,graph_grid)
    Object erase_qm, graph_grid;
{
    Object gensymed_symbol;

    x_note_fn_call(173,12);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    return update_images_of_graph(erase_qm,gensymed_symbol);
}

static Object Qdraw_only_new_data_for_graph_grid;  /* draw-only-new-data-for-graph-grid */

/* UPDATE-IMAGES-OF-ONLY-NEW-DATA-FOR-GRAPH-GRID */
Object update_images_of_only_new_data_for_graph_grid(erase_qm,graph_grid)
    Object erase_qm, graph_grid;
{
    Object gensymed_symbol, graph, current_graph_grid_in_minimal_update;
    Object current_minimal_grid_draw_has_seen_one_image_plane_p;
    Object changing_colors_of_graphic_elements_qm, temp, temp_1, temp_2;
    Declare_special(3);
    Object result;

    x_note_fn_call(173,13);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    current_graph_grid_in_minimal_update = graph_grid;
    current_minimal_grid_draw_has_seen_one_image_plane_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_minimal_grid_draw_has_seen_one_image_plane_p,Qcurrent_minimal_grid_draw_has_seen_one_image_plane_p,current_minimal_grid_draw_has_seen_one_image_plane_p,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_graph_grid_in_minimal_update,Qcurrent_graph_grid_in_minimal_update,current_graph_grid_in_minimal_update,
	      1);
	changing_colors_of_graphic_elements_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Changing_colors_of_graphic_elements_qm,Qchanging_colors_of_graphic_elements_qm,changing_colors_of_graphic_elements_qm,
		0);
	  gensymed_symbol = ISVREF(graph,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  temp = gensymed_symbol;
	  gensymed_symbol = ISVREF(graph,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  temp_1 = gensymed_symbol;
	  gensymed_symbol = ISVREF(graph,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  temp_2 = gensymed_symbol;
	  gensymed_symbol = ISVREF(graph,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  update_images(10,erase_qm,graph,graph,temp,temp_1,temp_2,
		  gensymed_symbol,Nil,Qdraw_only_new_data_for_graph_grid,
		  graph_grid);
	POP_SPECIAL();
	result = VALUES_1(ISVREF(graph_grid,(SI_Long)61L) = Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qdisplay_evaluation_should_use_simulated_values_qm;  /* display-evaluation-should-use-simulated-values? */

static Object Qsimulation_details;  /* simulation-details */

/* GRAPH-MUST-BE-REFRESHED-FOR-OLD-DATA? */
Object graph_must_be_refreshed_for_old_data_qm(graph_grid)
    Object graph_grid;
{
    Object gensymed_symbol, display_evaluation_should_use_simulated_values_qm;
    Object plot, ab_loop_list_, display_expression_for_plot;
    Object variable_or_parameter, simulation_subtable_qm;
    Object history_buffer_of_stored_values, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(173,14);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    display_evaluation_should_use_simulated_values_qm = 
	    get_lookup_slot_value(gensymed_symbol,
	    Qdisplay_evaluation_should_use_simulated_values_qm);
    plot = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    display_expression_for_plot = Nil;
    variable_or_parameter = Nil;
    simulation_subtable_qm = Nil;
    history_buffer_of_stored_values = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    plot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    display_expression_for_plot = ISVREF(plot,(SI_Long)3L);
    variable_or_parameter = 
	    get_variable_given_graph_expression(display_expression_for_plot,
	    display_evaluation_should_use_simulated_values_qm);
    if (variable_or_parameter) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
    simulation_subtable_qm = temp ? 
	    get_lookup_slot_value(variable_or_parameter,
	    Qsimulation_details) : Nil;
    history_buffer_of_stored_values = variable_or_parameter ? 
	    (display_evaluation_should_use_simulated_values_qm ? 
	    (simulation_subtable_qm ? ISVREF(simulation_subtable_qm,
	    (SI_Long)20L) : Nil) : ISVREF(variable_or_parameter,
	    (SI_Long)24L)) : Nil;
    if (history_buffer_of_stored_values && 
	    ISVREF(history_buffer_of_stored_values,(SI_Long)5L)) {
	SVREF(history_buffer_of_stored_values,FIX((SI_Long)5L)) = Nil;
	return VALUES_1(T);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* NEED-TO-REFORMAT-HORIZONTAL-AXIS? */
Object need_to_reformat_horizontal_axis_qm(graph_grid,graph_format,
	    plot_data_buffers_to_be_refreshed_qm)
    Object graph_grid, graph_format, plot_data_buffers_to_be_refreshed_qm;
{
    Object gensymed_symbol, graph, parse_var, temp;
    Object desired_absolute_or_relative_range_qm;
    Object desired_low_value_for_horizontal_axis_qm;
    Object high_and_low_values_specified_qm, high_value_for_horizontal_axis;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,15);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
	parse_var = ISVREF(graph,(SI_Long)23L);
	if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels)) {
	    temp = CDR(parse_var);
	    desired_absolute_or_relative_range_qm = temp;
	}
	else {
	    temp = parse_var;
	    desired_absolute_or_relative_range_qm = temp;
	}
	if (desired_absolute_or_relative_range_qm) {
	    result = parse_desired_absolute_or_relative_range(desired_absolute_or_relative_range_qm);
	    desired_low_value_for_horizontal_axis_qm = 
		    NTH_VALUE((SI_Long)1L, result);
	    high_and_low_values_specified_qm = 
		    desired_low_value_for_horizontal_axis_qm;
	}
	else
	    high_and_low_values_specified_qm = Nil;
	if (high_and_low_values_specified_qm)
	    result = VALUES_1(Nil);
	else if (ISVREF(graph_format,(SI_Long)43L)) {
	    high_value_for_horizontal_axis = 
		    compute_high_value_for_horizontal_axis(graph_grid,
		    plot_data_buffers_to_be_refreshed_qm);
	    if (high_value_for_horizontal_axis) {
		temp = ISVREF(graph_grid,(SI_Long)46L);
		result = VALUES_1(NUM_LE(temp,
			high_value_for_horizontal_axis) ? T : Nil);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* NEED-TO-REFORMAT-VERTICAL-AXIS? */
Object need_to_reformat_vertical_axis_qm(graph_grid,graph_format)
    Object graph_grid, graph_format;
{
    Object gensymed_symbol, graph, parse_var, temp;
    Object desired_absolute_or_relative_range_qm, most_recent_y_extremum;
    Object opposite_y_extremum_of_most_recent;
    Object desired_low_value_for_vertical_axis_qm, plot, ab_loop_list_;
    Object managed_number_or_value, temp_1, high_value_for_vertical_axis;
    Object low_value_for_vertical_axis, max_y_value, min_y_value;
    char temp_2;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,16);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
	parse_var = ISVREF(graph,(SI_Long)24L);
	if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels)) {
	    temp = CDR(parse_var);
	    desired_absolute_or_relative_range_qm = temp;
	}
	else {
	    temp = parse_var;
	    desired_absolute_or_relative_range_qm = temp;
	}
	most_recent_y_extremum = Nil;
	opposite_y_extremum_of_most_recent = Nil;
	if (desired_absolute_or_relative_range_qm) {
	    result = parse_desired_absolute_or_relative_range(desired_absolute_or_relative_range_qm);
	    desired_low_value_for_vertical_axis_qm = NTH_VALUE((SI_Long)1L,
		     result);
	    if (desired_low_value_for_vertical_axis_qm)
		result = VALUES_1(Nil);
	    else if (ISVREF(graph_format,(SI_Long)43L)) {
		plot = Nil;
		ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		plot = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (data_exists_for_plot_p(plot)) {
		    managed_number_or_value = ISVREF(plot,(SI_Long)8L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			most_recent_y_extremum = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			most_recent_y_extremum = 
				aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			most_recent_y_extremum = 
				copy_text_string(managed_number_or_value);
		    else
			most_recent_y_extremum = managed_number_or_value;
		    managed_number_or_value = ISVREF(plot,(SI_Long)9L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			opposite_y_extremum_of_most_recent = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			opposite_y_extremum_of_most_recent = 
				aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			opposite_y_extremum_of_most_recent = 
				copy_text_string(managed_number_or_value);
		    else
			opposite_y_extremum_of_most_recent = 
				managed_number_or_value;
		}
		if (most_recent_y_extremum) {
		    managed_number_or_value = ISVREF(graph_grid,(SI_Long)48L);
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
			temp_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp_1 = copy_text_string(managed_number_or_value);
		    else
			temp_1 = managed_number_or_value;
		    temp = lmax(most_recent_y_extremum,
			    opposite_y_extremum_of_most_recent);
		    temp_2 = NUM_LT(temp_1,temp);
		    if (temp_2);
		    else {
			managed_number_or_value = ISVREF(graph_grid,
				(SI_Long)47L);
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
			    temp_1 = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp_1 = copy_text_string(managed_number_or_value);
			else
			    temp_1 = managed_number_or_value;
			temp = lmin(most_recent_y_extremum,
				opposite_y_extremum_of_most_recent);
			temp_2 = NUM_GT(temp_1,temp);
		    }
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    result = VALUES_1(T);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		result = VALUES_1(Qnil);
	      end_1:;
	    }
	    else
		result = VALUES_1(Nil);
	}
	else if (ISVREF(graph_format,(SI_Long)43L)) {
	    high_value_for_vertical_axis = Nil;
	    low_value_for_vertical_axis = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
		    0);
	      plot = Nil;
	      ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
	      most_recent_y_extremum = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      plot = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (data_exists_for_plot_p(plot)) {
		  managed_number_or_value = ISVREF(plot,(SI_Long)8L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      most_recent_y_extremum = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      most_recent_y_extremum = 
			      aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else if (text_string_p(managed_number_or_value))
		      most_recent_y_extremum = 
			      copy_text_string(managed_number_or_value);
		  else
		      most_recent_y_extremum = managed_number_or_value;
	      }
	      else
		  most_recent_y_extremum = Nil;
	      if (data_exists_for_plot_p(plot)) {
		  managed_number_or_value = ISVREF(plot,(SI_Long)8L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      most_recent_y_extremum = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      most_recent_y_extremum = 
			      aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else if (text_string_p(managed_number_or_value))
		      most_recent_y_extremum = 
			      copy_text_string(managed_number_or_value);
		  else
		      most_recent_y_extremum = managed_number_or_value;
		  managed_number_or_value = ISVREF(plot,(SI_Long)9L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      opposite_y_extremum_of_most_recent = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      opposite_y_extremum_of_most_recent = 
			      aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else if (text_string_p(managed_number_or_value))
		      opposite_y_extremum_of_most_recent = 
			      copy_text_string(managed_number_or_value);
		  else
		      opposite_y_extremum_of_most_recent = 
			      managed_number_or_value;
		  if (most_recent_y_extremum) {
		      max_y_value = lmax(most_recent_y_extremum,
			      opposite_y_extremum_of_most_recent);
		      min_y_value = lmin(most_recent_y_extremum,
			      opposite_y_extremum_of_most_recent);
		      high_value_for_vertical_axis = 
			      high_value_for_vertical_axis ? 
			      lmax(high_value_for_vertical_axis,
			      max_y_value) : max_y_value;
		      Low_value_for_vertical_axis = 
			      Low_value_for_vertical_axis ? 
			      lmin(Low_value_for_vertical_axis,
			      min_y_value) : min_y_value;
		  }
	      }
	      goto next_loop_1;
	    end_loop_1:
	      if (high_value_for_vertical_axis) {
		  if (high_value_for_vertical_axis) {
		      managed_number_or_value = ISVREF(graph_grid,
			      (SI_Long)48L);
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
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		      temp = NUM_LT(temp,high_value_for_vertical_axis) ? T 
			      : Nil;
		  }
		  else
		      temp = Nil;
		  if (temp)
		      result = VALUES_1(temp);
		  else if (Low_value_for_vertical_axis) {
		      managed_number_or_value = ISVREF(graph_grid,
			      (SI_Long)47L);
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
			  temp = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else if (text_string_p(managed_number_or_value))
			  temp = copy_text_string(managed_number_or_value);
		      else
			  temp = managed_number_or_value;
		      result = VALUES_1(NUM_GT(temp,
			      Low_value_for_vertical_axis) ? T : Nil);
		  }
		  else
		      result = VALUES_1(Nil);
	      }
	      else
		  result = VALUES_1(Nil);
	      goto end_2;
	      result = VALUES_1(Qnil);
	    end_2:;
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qsc;                 /* \; */

/* PARSE-DESIRED-ABSOLUTE-OR-RELATIVE-RANGE */
Object parse_desired_absolute_or_relative_range(desired_absolute_or_relative_range)
    Object desired_absolute_or_relative_range;
{
    Object temp, slot_value_number, temp_1;

    x_note_fn_call(173,17);
    if (slot_value_number_p(desired_absolute_or_relative_range)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(desired_absolute_or_relative_range) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(desired_absolute_or_relative_range)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(desired_absolute_or_relative_range,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(desired_absolute_or_relative_range) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(desired_absolute_or_relative_range)) 
		== (SI_Long)1L)
	    temp = aref1(desired_absolute_or_relative_range,FIX((SI_Long)0L));
	else
	    temp = desired_absolute_or_relative_range;
	return VALUES_3(temp,Nil,Nil);
    }
    else if ( !EQ(CAR(desired_absolute_or_relative_range),Qsc)) {
	slot_value_number = CAR(desired_absolute_or_relative_range);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp = slot_value_number;
	return VALUES_3(temp,Nil,Nil);
    }
    else if (slot_value_number_p(SECOND(desired_absolute_or_relative_range))) {
	slot_value_number = SECOND(desired_absolute_or_relative_range);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp = slot_value_number;
	slot_value_number = THIRD(desired_absolute_or_relative_range);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp_1 = slot_value_number;
	return VALUES_3(Nil,temp,temp_1);
    }
    else {
	temp = SECOND(desired_absolute_or_relative_range);
	slot_value_number = CAR(temp);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp = slot_value_number;
	temp_1 = THIRD(desired_absolute_or_relative_range);
	slot_value_number = CAR(temp_1);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp_1 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp_1 = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp_1 = slot_value_number;
	return VALUES_3(Nil,temp,temp_1);
    }
}

/* ABSOLUTE-RANGE-SPECIFIED-P */
Object absolute_range_specified_p(desired_absolute_or_relative_range)
    Object desired_absolute_or_relative_range;
{
    x_note_fn_call(173,18);
    return VALUES_1(EQ(CAR(desired_absolute_or_relative_range),Qsc) ? T : Nil);
}

/* COMPUTE-NEXT-MAXIMUM-X-VALUE */
Object compute_next_maximum_x_value(plot,graph_grid)
    Object plot, graph_grid;
{
    Object temp, gensymed_symbol;

    x_note_fn_call(173,19);
    temp = ISVREF(plot,(SI_Long)3L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    return compute_time_of_newest_data_point(temp,
	    get_lookup_slot_value(gensymed_symbol,
	    Qdisplay_evaluation_should_use_simulated_values_qm));
}

/* COMPUTE-NEXT-MINIMUM-X-VALUE */
Object compute_next_minimum_x_value(plot,graph_grid)
    Object plot, graph_grid;
{
    Object temp, gensymed_symbol;

    x_note_fn_call(173,20);
    temp = ISVREF(plot,(SI_Long)3L);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    return compute_time_of_oldest_data_point(temp,
	    get_lookup_slot_value(gensymed_symbol,
	    Qdisplay_evaluation_should_use_simulated_values_qm));
}

static Object float_constant_1;    /* 0.0 */

/* COMPUTE-NEW-PARAMETERS-FOR-HORIZONTAL-AXIS-OF-GRID */
Object compute_new_parameters_for_horizontal_axis_of_grid varargs_1(int, n)
{
    Object graph_grid, graph_format, plot_data_buffers_to_be_refreshed_qm;
    Object try_scrolling_qm, scroll_continuously_qm, gensymed_symbol, graph;
    Object new_low_value_for_horizontal_axis;
    Object new_high_value_for_horizontal_axis, horizontal_axis_range;
    Object desired_low_value_for_horizontal_axis;
    Object desired_high_value_for_horizontal_axis;
    Object desired_low_value_for_horizontal_axis_qm;
    Object desired_high_value_for_horizontal_axis_qm, parse_var, temp;
    Object desired_absolute_or_relative_horizontal_axis_range_qm;
    Object desired_range_for_horizontal_axis_qm, determine_ruling_qm;
    Object absolute_range_specified_qm, new_shift, managed_number_or_value;
    Object current_shift_qm, svref_new_value, temp_3, slot_value_number;
    Object temp_4, temp_5, temp_6, low_value_for_vertical_grid_lines;
    Object high_value_for_vertical_grid_lines, number_of_vertical_grid_lines;
    Object interval_between_vertical_grid_lines;
    Object label_scale_for_vertical_grid_lines;
    Object store_managed_number_or_value_arg;
    char temp_1;
    double temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(7);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,21);
    INIT_ARGS_nonrelocating();
    graph_grid = REQUIRED_ARG_nonrelocating();
    graph_format = REQUIRED_ARG_nonrelocating();
    plot_data_buffers_to_be_refreshed_qm = REQUIRED_ARG_nonrelocating();
    try_scrolling_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    scroll_continuously_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
	new_low_value_for_horizontal_axis = Nil;
	new_high_value_for_horizontal_axis = Nil;
	horizontal_axis_range = Nil;
	desired_low_value_for_horizontal_axis = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Desired_low_value_for_horizontal_axis,Qdesired_low_value_for_horizontal_axis,desired_low_value_for_horizontal_axis,
		6);
	  desired_high_value_for_horizontal_axis = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Desired_high_value_for_horizontal_axis,Qdesired_high_value_for_horizontal_axis,desired_high_value_for_horizontal_axis,
		  5);
	    desired_low_value_for_horizontal_axis_qm = Nil;
	    desired_high_value_for_horizontal_axis_qm = Nil;
	    if (graph) {
		parse_var = ISVREF(graph,(SI_Long)23L);
		if (CONSP(parse_var) && EQ(CAR(parse_var),
			Qwithout_tickmark_labels)) {
		    temp = CDR(parse_var);
		    desired_absolute_or_relative_horizontal_axis_range_qm 
			    = temp;
		}
		else {
		    temp = parse_var;
		    desired_absolute_or_relative_horizontal_axis_range_qm 
			    = temp;
		}
	    }
	    else
		desired_absolute_or_relative_horizontal_axis_range_qm = Nil;
	    desired_range_for_horizontal_axis_qm = Nil;
	    determine_ruling_qm = T;
	    absolute_range_specified_qm = Nil;
	    new_shift = Nil;
	    if (desired_absolute_or_relative_horizontal_axis_range_qm) {
		result = parse_desired_absolute_or_relative_range(desired_absolute_or_relative_horizontal_axis_range_qm);
		MVS_3(result,desired_range_for_horizontal_axis_qm,
			desired_low_value_for_horizontal_axis_qm,
			desired_high_value_for_horizontal_axis_qm);
	    }
	    if (desired_low_value_for_horizontal_axis_qm) {
		Desired_high_value_for_horizontal_axis = 
			desired_high_value_for_horizontal_axis_qm;
		Desired_low_value_for_horizontal_axis = 
			desired_low_value_for_horizontal_axis_qm;
		absolute_range_specified_qm = T;
	    }
	    else {
		if (desired_range_for_horizontal_axis_qm) {
		    new_high_value_for_horizontal_axis = 
			    compute_high_value_for_horizontal_axis(graph_grid,
			    plot_data_buffers_to_be_refreshed_qm);
		    if (try_scrolling_qm) {
			managed_number_or_value = ISVREF(graph_grid,
				(SI_Long)36L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    horizontal_axis_range = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    horizontal_axis_range = 
				    aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    horizontal_axis_range = 
				    copy_text_string(managed_number_or_value);
			else
			    horizontal_axis_range = managed_number_or_value;
			temp_1 = TRUEP(T);
		    }
		    else {
			new_low_value_for_horizontal_axis = 
				compute_low_value_for_horizontal_axis(graph_grid,
				plot_data_buffers_to_be_refreshed_qm);
			temp_1 = TRUEP(Nil);
		    }
		}
		else {
		    new_high_value_for_horizontal_axis = 
			    compute_high_value_for_horizontal_axis(graph_grid,
			    plot_data_buffers_to_be_refreshed_qm);
		    new_low_value_for_horizontal_axis = 
			    compute_low_value_for_horizontal_axis(graph_grid,
			    plot_data_buffers_to_be_refreshed_qm);
		    if (try_scrolling_qm) {
			temp = minus(new_high_value_for_horizontal_axis,
				new_low_value_for_horizontal_axis);
			managed_number_or_value = ISVREF(graph_grid,
				(SI_Long)36L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    horizontal_axis_range = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    horizontal_axis_range = 
				    aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    horizontal_axis_range = 
				    copy_text_string(managed_number_or_value);
			else
			    horizontal_axis_range = managed_number_or_value;
			temp_1 = NUM_LE(temp,horizontal_axis_range);
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		if (temp_1 ? TRUEP(new_high_value_for_horizontal_axis) : 
			TRUEP(Nil)) {
		    current_shift_qm = ISVREF(graph_grid,(SI_Long)43L);
		    new_shift = compute_shift_for_scrolling(graph_grid,
			    graph,scroll_continuously_qm,
			    horizontal_axis_range,ISVREF(graph_grid,
			    (SI_Long)46L),new_high_value_for_horizontal_axis);
		    temp = current_shift_qm ? minus(new_shift,
			    current_shift_qm) : new_shift;
		    temp_1 = NUM_LT(temp,horizontal_axis_range);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    determine_ruling_qm = Nil;
		    ISVREF(graph_grid,(SI_Long)43L) = new_shift;
		    svref_new_value = mod(new_shift,ISVREF(graph_grid,
			    (SI_Long)60L));
		    ISVREF(graph_grid,(SI_Long)49L) = svref_new_value;
		    svref_new_value = add(ISVREF(graph_grid,(SI_Long)45L),
			    new_shift);
		    ISVREF(graph_grid,(SI_Long)44L) = svref_new_value;
		    svref_new_value = add(ISVREF(graph_grid,(SI_Long)44L),
			    horizontal_axis_range);
		    ISVREF(graph_grid,(SI_Long)46L) = svref_new_value;
		}
		else if (ISVREF(graph_format,(SI_Long)43L)) {
		    if ( !TRUEP(new_high_value_for_horizontal_axis)) {
			temp = 
				lfloat(Default_number_of_vertical_grid_lines,
				float_constant_1);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			new_low_value_for_horizontal_axis = 
				FIXNUM_NEGATE(FIXNUM_TIMES(Default_interval_between_vertical_grid_lines,
				lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
				2.0),_)));
			temp = 
				lfloat(Default_number_of_vertical_grid_lines,
				float_constant_1);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			new_high_value_for_horizontal_axis = 
				FIXNUM_TIMES(Default_interval_between_vertical_grid_lines,
				ceiling(DOUBLE_TO_DOUBLE_FLOAT(temp_2 / 
				2.0),_));
		    }
		    if (desired_range_for_horizontal_axis_qm) {
			Desired_high_value_for_horizontal_axis = 
				new_high_value_for_horizontal_axis;
			Desired_low_value_for_horizontal_axis = 
				minus(Desired_high_value_for_horizontal_axis,
				desired_range_for_horizontal_axis_qm);
		    }
		    else {
			temp_3 = new_high_value_for_horizontal_axis;
			temp = 
				l_abs(lmax(minus(new_high_value_for_horizontal_axis,
				new_low_value_for_horizontal_axis),
				FIX((SI_Long)1L)));
			slot_value_number = ISVREF(graph_format,(SI_Long)49L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				== (SI_Long)1L)
			    temp_4 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(slot_value_number) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
				== (SI_Long)1L)
			    temp_4 = aref1(slot_value_number,FIX((SI_Long)0L));
			else
			    temp_4 = slot_value_number;
			Desired_high_value_for_horizontal_axis = 
				add(temp_3,l_round(ltimes(temp,temp_4),_));
			Desired_low_value_for_horizontal_axis = 
				NUM_EQ(new_high_value_for_horizontal_axis,
				new_low_value_for_horizontal_axis) ? 
				minus(new_low_value_for_horizontal_axis,
				Default_interval_between_vertical_grid_lines) 
				: new_low_value_for_horizontal_axis;
		    }
		}
		else;
	    }
	    if (determine_ruling_qm) {
		temp_5 = Desired_low_value_for_horizontal_axis;
		temp_4 = Desired_high_value_for_horizontal_axis;
		temp_3 = ISVREF(graph_grid,(SI_Long)29L);
		temp = ISVREF(graph_format,(SI_Long)40L);
		slot_value_number = ISVREF(graph_format,(SI_Long)39L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			== (SI_Long)1L)
		    temp_6 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			== (SI_Long)1L)
		    temp_6 = aref1(slot_value_number,FIX((SI_Long)0L));
		else
		    temp_6 = slot_value_number;
		result = determine_ruling_for_time_axis(temp_5,temp_4,
			temp_3,temp,lfloat(temp_6,float_constant_1));
		MVS_5(result,low_value_for_vertical_grid_lines,
			high_value_for_vertical_grid_lines,
			number_of_vertical_grid_lines,
			interval_between_vertical_grid_lines,
			label_scale_for_vertical_grid_lines);
		PUSH_SPECIAL_WITH_SYMBOL(Label_scale_for_vertical_grid_lines,Qlabel_scale_for_vertical_grid_lines,label_scale_for_vertical_grid_lines,
			4);
		  PUSH_SPECIAL_WITH_SYMBOL(Interval_between_vertical_grid_lines,Qinterval_between_vertical_grid_lines,interval_between_vertical_grid_lines,
			  3);
		    PUSH_SPECIAL_WITH_SYMBOL(Number_of_vertical_grid_lines,Qnumber_of_vertical_grid_lines,number_of_vertical_grid_lines,
			    2);
		      PUSH_SPECIAL_WITH_SYMBOL(High_value_for_vertical_grid_lines,Qhigh_value_for_vertical_grid_lines,high_value_for_vertical_grid_lines,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_grid_lines,Qlow_value_for_vertical_grid_lines,low_value_for_vertical_grid_lines,
				0);
			  if ( !TRUEP(absolute_range_specified_qm))
			      High_value_for_vertical_grid_lines = 
				      Desired_high_value_for_horizontal_axis;
			  svref_new_value = Low_value_for_vertical_grid_lines;
			  ISVREF(graph_grid,(SI_Long)27L) = svref_new_value;
			  svref_new_value = High_value_for_vertical_grid_lines;
			  ISVREF(graph_grid,(SI_Long)28L) = svref_new_value;
			  svref_new_value = Number_of_vertical_grid_lines;
			  ISVREF(graph_grid,(SI_Long)29L) = svref_new_value;
			  svref_new_value = 
				  Label_scale_for_vertical_grid_lines;
			  ISVREF(graph_grid,(SI_Long)32L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  Interval_between_vertical_grid_lines;
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)26L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)26L) = svref_new_value;
			  horizontal_axis_range = 
				  compute_horizontal_axis_range(Desired_high_value_for_horizontal_axis,
				  Desired_low_value_for_horizontal_axis,graph);
			  store_managed_number_or_value_arg = 
				  horizontal_axis_range;
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)36L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)36L) = svref_new_value;
			  svref_new_value = 
				  lfloor(divide(lfloat(ltimes(horizontal_axis_range,
				  ISVREF(graph_grid,(SI_Long)59L)),
				  float_constant_1),ISVREF(graph_grid,
				  (SI_Long)34L)),_);
			  ISVREF(graph_grid,(SI_Long)60L) = svref_new_value;
			  svref_new_value = 
				  l_round(divide(lfloat(horizontal_axis_range,
				  float_constant_1),
				  Default_number_of_markers),_);
			  ISVREF(graph_grid,(SI_Long)54L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  divide(ltimes(lfloat(Minimum_grid_width,
				  float_constant_1),
				  Interval_between_vertical_grid_lines),
				  horizontal_axis_range);
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)30L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)30L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  divide(ltimes(lfloat(Minimum_grid_width,
				  float_constant_1),
				  minus(Interval_between_vertical_grid_lines,
				  minus(High_value_for_vertical_grid_lines,
				  Desired_high_value_for_horizontal_axis))),
				  horizontal_axis_range);
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)31L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)31L) = svref_new_value;
			  svref_new_value = 
				  Desired_low_value_for_horizontal_axis;
			  ISVREF(graph_grid,(SI_Long)44L) = svref_new_value;
			  svref_new_value = 
				  Desired_low_value_for_horizontal_axis;
			  ISVREF(graph_grid,(SI_Long)45L) = svref_new_value;
			  svref_new_value = 
				  Desired_high_value_for_horizontal_axis;
			  ISVREF(graph_grid,(SI_Long)46L) = svref_new_value;
			  ISVREF(graph_grid,(SI_Long)49L) = FIX((SI_Long)0L);
			  ISVREF(graph_grid,(SI_Long)50L) = FIX((SI_Long)0L);
			  ISVREF(graph_grid,(SI_Long)43L) = Nil;
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    result = VALUES_1(determine_ruling_qm);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qhorizontal_range_zero;  /* horizontal-range-zero */

/* COMPUTE-HORIZONTAL-AXIS-RANGE */
Object compute_horizontal_axis_range(high_value,low_value,graph)
    Object high_value, low_value, graph;
{
    Object range;

    x_note_fn_call(173,22);
    range = FIXNUM_MINUS(high_value,low_value);
    if (IFIX(range) == (SI_Long)0L) {
	range = FIX((SI_Long)1L);
	Problems_reformatting_graph_qm = T;
	add_frame_note(5,Qhorizontal_range_zero,graph,Nil,T,Nil);
    }
    return VALUES_1(range);
}

/* COMPUTE-HIGH-VALUE-FOR-HORIZONTAL-AXIS */
Object compute_high_value_for_horizontal_axis(graph_grid,
	    plot_data_buffers_to_be_refreshed_qm)
    Object graph_grid, plot_data_buffers_to_be_refreshed_qm;
{
    Object high_value, plot, ab_loop_list_, x_data_maximum;
    Object managed_number_or_value;

    x_note_fn_call(173,23);
    high_value = Nil;
    plot = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    x_data_maximum = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    plot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (plot_data_buffers_to_be_refreshed_qm)
	x_data_maximum = compute_next_maximum_x_value(plot,graph_grid);
    else if (data_exists_for_plot_p(plot)) {
	managed_number_or_value = ISVREF(plot,(SI_Long)7L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    x_data_maximum = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    x_data_maximum = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    x_data_maximum = copy_text_string(managed_number_or_value);
	else
	    x_data_maximum = managed_number_or_value;
    }
    else
	x_data_maximum = Nil;
    if (x_data_maximum)
	high_value = high_value ? lmax(high_value,x_data_maximum) : 
		x_data_maximum;
    goto next_loop;
  end_loop:
    return VALUES_1(high_value);
    return VALUES_1(Qnil);
}

/* COMPUTE-LOW-VALUE-FOR-HORIZONTAL-AXIS */
Object compute_low_value_for_horizontal_axis(graph_grid,
	    plot_data_buffers_to_be_refreshed_qm)
    Object graph_grid, plot_data_buffers_to_be_refreshed_qm;
{
    Object low_value, plot, ab_loop_list_, x_data_minimum;
    Object managed_number_or_value;

    x_note_fn_call(173,24);
    low_value = Nil;
    plot = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    x_data_minimum = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    plot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (plot_data_buffers_to_be_refreshed_qm)
	x_data_minimum = compute_next_minimum_x_value(plot,graph_grid);
    else if (data_exists_for_plot_p(plot)) {
	managed_number_or_value = ISVREF(plot,(SI_Long)6L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    x_data_minimum = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    x_data_minimum = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    x_data_minimum = copy_text_string(managed_number_or_value);
	else
	    x_data_minimum = managed_number_or_value;
    }
    else
	x_data_minimum = Nil;
    if (x_data_minimum)
	low_value = low_value ? lmin(low_value,x_data_minimum) : 
		x_data_minimum;
    goto next_loop;
  end_loop:
    return VALUES_1(low_value);
    return VALUES_1(Qnil);
}

static Object float_constant_2;    /* 100.0 */

/* COMPUTE-SHIFT-FOR-SCROLLING */
Object compute_shift_for_scrolling(graph_grid,graph,scroll_continuously_qm,
	    horizontal_axis_range,high_value_for_horizontal_axis,
	    new_high_value_for_horizontal_axis)
    Object graph_grid, graph, scroll_continuously_qm, horizontal_axis_range;
    Object high_value_for_horizontal_axis, new_high_value_for_horizontal_axis;
{
    Object horizontal_axis_shift, desired_shift, managed_number_or_value;
    Object interval_between_grid_lines, interval_after_last_grid_line, temp_1;
    Object interval_until_next_grid_line, desired_shift_beyond_next_grid_line;
    Object number_of_new_grid_lines, amount_to_shift;
    Object position_of_next_grid_line, svref_new_value;
    SI_Long temp, i, ab_loop_bind_;

    x_note_fn_call(173,25);
    reclaim_graph_list_1(ISVREF(graph_grid,(SI_Long)51L));
    ISVREF(graph_grid,(SI_Long)51L) = Nil;
    horizontal_axis_shift = ISVREF(graph_grid,(SI_Long)43L);
    if (horizontal_axis_shift);
    else
	horizontal_axis_shift = FIX((SI_Long)0L);
    temp = IFIX(l_round(ltimes(divide(ISVREF(graph,(SI_Long)26L),
	    float_constant_2),horizontal_axis_range),_));
    desired_shift = add(minus(new_high_value_for_horizontal_axis,
	    high_value_for_horizontal_axis),FIX(MAX(temp,(SI_Long)1L)));
    managed_number_or_value = ISVREF(graph_grid,(SI_Long)26L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	interval_between_grid_lines = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	interval_between_grid_lines = aref1(managed_number_or_value,
		FIX((SI_Long)0L));
    else if (text_string_p(managed_number_or_value))
	interval_between_grid_lines = 
		copy_text_string(managed_number_or_value);
    else
	interval_between_grid_lines = managed_number_or_value;
    interval_after_last_grid_line = rem(horizontal_axis_shift,
	    interval_between_grid_lines);
    temp_1 = FIX((SI_Long)0L);
    interval_until_next_grid_line = NUM_EQ(interval_after_last_grid_line,
	    temp_1) ? FIX((SI_Long)0L) : minus(interval_between_grid_lines,
	    interval_after_last_grid_line);
    desired_shift_beyond_next_grid_line = minus(desired_shift,
	    interval_until_next_grid_line);
    number_of_new_grid_lines = Nil;
    amount_to_shift = Nil;
    if (scroll_continuously_qm) {
	amount_to_shift = desired_shift;
	temp_1 = FIX((SI_Long)0L);
	if (NUM_GE(desired_shift_beyond_next_grid_line,temp_1))
	    number_of_new_grid_lines = 
		    FIXNUM_ADD1(lfloor(desired_shift_beyond_next_grid_line,
		    interval_between_grid_lines));
    }
    else {
	number_of_new_grid_lines = 
		ceiling(desired_shift_beyond_next_grid_line,
		interval_between_grid_lines);
	amount_to_shift = NUM_GT(interval_until_next_grid_line,
		desired_shift) ? interval_until_next_grid_line : 
		add(interval_until_next_grid_line,
		ltimes(number_of_new_grid_lines,interval_between_grid_lines));
    }
    if (number_of_new_grid_lines) {
	position_of_next_grid_line = add(horizontal_axis_shift,
		interval_until_next_grid_line);
	i = (SI_Long)1L;
	ab_loop_bind_ = IFIX(number_of_new_grid_lines);
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
	svref_new_value = graph_cons_1(mod(position_of_next_grid_line,
		ISVREF(graph_grid,(SI_Long)60L)),ISVREF(graph_grid,
		(SI_Long)51L));
	ISVREF(graph_grid,(SI_Long)51L) = svref_new_value;
	position_of_next_grid_line = add(position_of_next_grid_line,
		interval_between_grid_lines);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return add(horizontal_axis_shift,amount_to_shift);
}

DEFINE_VARIABLE_WITH_SYMBOL(Range_too_small_qm, Qrange_too_small_qm);

static Object Qplot_range_specs_without_vertical_axis_spec;  /* plot-range-specs-without-vertical-axis-spec */

static Object float_constant_3;    /* 2.0 */

static Object Qdesired_range_too_small;  /* desired-range-too-small */

/* COMPUTE-NEW-PARAMETERS-FOR-VERTICAL-AXIS-OF-GRID */
Object compute_new_parameters_for_vertical_axis_of_grid(graph_grid,
	    graph_format)
    Object graph_grid, graph_format;
{
    Object gensymed_symbol, graph, desired_low_value_for_vertical_axis;
    Object desired_high_value_for_vertical_axis;
    Object desired_low_value_for_vertical_axis_qm;
    Object desired_high_value_for_vertical_axis_qm, parse_var, temp;
    Object desired_absolute_or_relative_vertical_axis_range_qm;
    Object desired_range_for_vertical_axis_qm, range_too_small_qm;
    Object data_exists_qm, plot, ab_loop_list_, managed_number_or_value;
    Object most_recent_y_extremum, opposite_y_extremum_of_most_recent;
    Object slot_value_number, temp_2, high_value_for_vertical_axis;
    Object low_value_for_vertical_axis, vertical_axis_data_range;
    Object low_value_for_horizontal_grid_lines;
    Object high_value_for_horizontal_grid_lines;
    Object number_of_horizontal_grid_lines;
    Object interval_between_horizontal_grid_lines, svref_new_value;
    Object store_managed_number_or_value_arg, vertical_axis_range;
    Object exact_specification_qm, thing;
    char temp_1, most_recent_y_extremum_maximum_p;
    Declare_special(9);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,26);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	graph = gensymed_symbol;
	desired_low_value_for_vertical_axis = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Desired_low_value_for_vertical_axis,Qdesired_low_value_for_vertical_axis,desired_low_value_for_vertical_axis,
		8);
	  desired_high_value_for_vertical_axis = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Desired_high_value_for_vertical_axis,Qdesired_high_value_for_vertical_axis,desired_high_value_for_vertical_axis,
		  7);
	    desired_low_value_for_vertical_axis_qm = Nil;
	    desired_high_value_for_vertical_axis_qm = Nil;
	    if (graph) {
		parse_var = ISVREF(graph,(SI_Long)24L);
		if (CONSP(parse_var) && EQ(CAR(parse_var),
			Qwithout_tickmark_labels)) {
		    temp = CDR(parse_var);
		    desired_absolute_or_relative_vertical_axis_range_qm = temp;
		}
		else {
		    temp = parse_var;
		    desired_absolute_or_relative_vertical_axis_range_qm = temp;
		}
	    }
	    else
		desired_absolute_or_relative_vertical_axis_range_qm = Nil;
	    desired_range_for_vertical_axis_qm = Nil;
	    range_too_small_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Range_too_small_qm,Qrange_too_small_qm,range_too_small_qm,
		    6);
	      if (desired_absolute_or_relative_vertical_axis_range_qm) {
		  result = parse_desired_absolute_or_relative_range(desired_absolute_or_relative_vertical_axis_range_qm);
		  MVS_3(result,desired_range_for_vertical_axis_qm,
			  desired_low_value_for_vertical_axis_qm,
			  desired_high_value_for_vertical_axis_qm);
	      }
	      if (desired_low_value_for_vertical_axis_qm) {
		  Desired_high_value_for_vertical_axis = 
			  desired_high_value_for_vertical_axis_qm;
		  Desired_low_value_for_vertical_axis = 
			  desired_low_value_for_vertical_axis_qm;
	      }
	      else {
		  data_exists_qm = Nil;
		  plot = Nil;
		  ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  plot = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (data_exists_for_plot_p(plot))
		      data_exists_qm = T;
		  if (plot_min_and_max_given_plot(plot)) {
		      Problems_reformatting_graph_qm = T;
		      add_frame_note(5,
			      Qplot_range_specs_without_vertical_axis_spec,
			      graph,Nil,T,Nil);
		  }
		  goto next_loop;
		end_loop:
		  temp_1 = TRUEP(data_exists_qm);
		  goto end_1;
		  temp_1 = TRUEP(Qnil);
		end_1:;
		  if (temp_1) {
		      if (ISVREF(graph_format,(SI_Long)43L)) {
			  if (desired_range_for_vertical_axis_qm) {
			      plot = Nil;
			      ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
			    next_loop_1:
			      if ( !TRUEP(ab_loop_list_))
				  goto end_loop_1;
			      plot = M_CAR(ab_loop_list_);
			      ab_loop_list_ = M_CDR(ab_loop_list_);
			      if (data_exists_for_plot_p(plot)) {
				  managed_number_or_value = ISVREF(plot,
					  (SI_Long)8L);
				  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      most_recent_y_extremum = 
					      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					      (SI_Long)0L));
				  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      most_recent_y_extremum = 
					      aref1(managed_number_or_value,
					      FIX((SI_Long)0L));
				  else if (text_string_p(managed_number_or_value))
				      most_recent_y_extremum = 
					      copy_text_string(managed_number_or_value);
				  else
				      most_recent_y_extremum = 
					      managed_number_or_value;
				  managed_number_or_value = ISVREF(plot,
					  (SI_Long)9L);
				  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      opposite_y_extremum_of_most_recent = 
					      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					      (SI_Long)0L));
				  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					  != (SI_Long)0L && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					  == (SI_Long)1L)
				      opposite_y_extremum_of_most_recent = 
					      aref1(managed_number_or_value,
					      FIX((SI_Long)0L));
				  else if (text_string_p(managed_number_or_value))
				      opposite_y_extremum_of_most_recent = 
					      copy_text_string(managed_number_or_value);
				  else
				      opposite_y_extremum_of_most_recent = 
					      managed_number_or_value;
				  most_recent_y_extremum_maximum_p = 
					  NUM_GT(most_recent_y_extremum,
					  opposite_y_extremum_of_most_recent);
				  if (most_recent_y_extremum_maximum_p) {
				      temp = 
					      desired_range_for_vertical_axis_qm;
				      slot_value_number = 
					      ISVREF(graph_format,
					      (SI_Long)51L);
				      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					      == (SI_Long)1L)
					  temp_2 = 
						  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
						  (SI_Long)0L));
				      else if (INLINE_LONG_VECTOR_P(slot_value_number) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					      == (SI_Long)1L)
					  temp_2 = aref1(slot_value_number,
						  FIX((SI_Long)0L));
				      else
					  temp_2 = slot_value_number;
				      Desired_high_value_for_vertical_axis 
					      = add(most_recent_y_extremum,
					      ltimes(temp,lfloat(temp_2,
					      float_constant_1)));
				      Desired_low_value_for_vertical_axis 
					      = 
					      minus(Desired_high_value_for_vertical_axis,
					      desired_range_for_vertical_axis_qm);
				  }
				  else {
				      temp = 
					      desired_range_for_vertical_axis_qm;
				      slot_value_number = 
					      ISVREF(graph_format,
					      (SI_Long)50L);
				      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					      == (SI_Long)1L)
					  temp_2 = 
						  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
						  (SI_Long)0L));
				      else if (INLINE_LONG_VECTOR_P(slot_value_number) 
					      != (SI_Long)0L && 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					      == (SI_Long)1L)
					  temp_2 = aref1(slot_value_number,
						  FIX((SI_Long)0L));
				      else
					  temp_2 = slot_value_number;
				      Desired_low_value_for_vertical_axis 
					      = 
					      minus(most_recent_y_extremum,
					      ltimes(temp,lfloat(temp_2,
					      float_constant_1)));
				      Desired_high_value_for_vertical_axis 
					      = 
					      add(Desired_low_value_for_vertical_axis,
					      desired_range_for_vertical_axis_qm);
				  }
				  goto end_2;
			      }
			      goto next_loop_1;
			    end_loop_1:
			    end_2:;
			  }
			  else {
			      high_value_for_vertical_axis = Nil;
			      low_value_for_vertical_axis = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
				      0);
				plot = Nil;
				ab_loop_list_ = ISVREF(graph_grid,
					(SI_Long)33L);
			      next_loop_2:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop_2;
				plot = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				if (data_exists_for_plot_p(plot)) {
				    managed_number_or_value = ISVREF(plot,
					    (SI_Long)8L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					most_recent_y_extremum = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					most_recent_y_extremum = 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					most_recent_y_extremum = 
						copy_text_string(managed_number_or_value);
				    else
					most_recent_y_extremum = 
						managed_number_or_value;
				    managed_number_or_value = ISVREF(plot,
					    (SI_Long)9L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					opposite_y_extremum_of_most_recent 
						= 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					opposite_y_extremum_of_most_recent 
						= 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					opposite_y_extremum_of_most_recent 
						= 
						copy_text_string(managed_number_or_value);
				    else
					opposite_y_extremum_of_most_recent 
						= managed_number_or_value;
				    most_recent_y_extremum_maximum_p = 
					    NUM_GT(most_recent_y_extremum,
					    opposite_y_extremum_of_most_recent);
				    if (most_recent_y_extremum_maximum_p) {
					high_value_for_vertical_axis = 
						high_value_for_vertical_axis 
						? 
						lmax(high_value_for_vertical_axis,
						most_recent_y_extremum) : 
						most_recent_y_extremum;
					Low_value_for_vertical_axis = 
						Low_value_for_vertical_axis 
						? 
						lmin(Low_value_for_vertical_axis,
						opposite_y_extremum_of_most_recent) 
						: 
						opposite_y_extremum_of_most_recent;
				    }
				    else {
					Low_value_for_vertical_axis = 
						Low_value_for_vertical_axis 
						? 
						lmin(Low_value_for_vertical_axis,
						most_recent_y_extremum) : 
						most_recent_y_extremum;
					high_value_for_vertical_axis = 
						high_value_for_vertical_axis 
						? 
						lmax(high_value_for_vertical_axis,
						opposite_y_extremum_of_most_recent) 
						: 
						opposite_y_extremum_of_most_recent;
				    }
				}
				goto next_loop_2;
			      end_loop_2:
				vertical_axis_data_range = 
					minus(high_value_for_vertical_axis,
					Low_value_for_vertical_axis);
				temp = high_value_for_vertical_axis;
				slot_value_number = ISVREF(graph_format,
					(SI_Long)51L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					== (SI_Long)1L)
				    temp_2 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(slot_value_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					== (SI_Long)1L)
				    temp_2 = aref1(slot_value_number,
					    FIX((SI_Long)0L));
				else
				    temp_2 = slot_value_number;
				Desired_high_value_for_vertical_axis = 
					add(temp,
					ltimes(vertical_axis_data_range,
					lfloat(temp_2,float_constant_1)));
				temp = Low_value_for_vertical_axis;
				slot_value_number = ISVREF(graph_format,
					(SI_Long)50L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					== (SI_Long)1L)
				    temp_2 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(slot_value_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
					== (SI_Long)1L)
				    temp_2 = aref1(slot_value_number,
					    FIX((SI_Long)0L));
				else
				    temp_2 = slot_value_number;
				Desired_low_value_for_vertical_axis = 
					minus(temp,
					ltimes(vertical_axis_data_range,
					lfloat(temp_2,float_constant_1)));
			      POP_SPECIAL();
			  }
		      }
		  }
		  else if (desired_range_for_vertical_axis_qm) {
		      Desired_low_value_for_vertical_axis = 
			      negate(divide(desired_range_for_vertical_axis_qm,
			      float_constant_3));
		      Desired_high_value_for_vertical_axis = 
			      divide(desired_range_for_vertical_axis_qm,
			      float_constant_3);
		  }
		  else {
		      Desired_low_value_for_vertical_axis = 
			      negate(Default_axis_half_range);
		      Desired_high_value_for_vertical_axis = 
			      Default_axis_half_range;
		  }
	      }
	      result = determine_ruling_for_axis(Desired_low_value_for_vertical_axis,
		      Desired_high_value_for_vertical_axis,Nil,graph ? 
		      ISVREF(graph,(SI_Long)28L) : Nil);
	      MVS_4(result,low_value_for_horizontal_grid_lines,
		      high_value_for_horizontal_grid_lines,
		      number_of_horizontal_grid_lines,
		      interval_between_horizontal_grid_lines);
	      PUSH_SPECIAL_WITH_SYMBOL(Interval_between_horizontal_grid_lines,Qinterval_between_horizontal_grid_lines,interval_between_horizontal_grid_lines,
		      5);
		PUSH_SPECIAL_WITH_SYMBOL(Number_of_horizontal_grid_lines,Qnumber_of_horizontal_grid_lines,number_of_horizontal_grid_lines,
			4);
		  PUSH_SPECIAL_WITH_SYMBOL(High_value_for_horizontal_grid_lines,Qhigh_value_for_horizontal_grid_lines,high_value_for_horizontal_grid_lines,
			  3);
		    PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_horizontal_grid_lines,Qlow_value_for_horizontal_grid_lines,low_value_for_horizontal_grid_lines,
			    2);
		      svref_new_value = Number_of_horizontal_grid_lines;
		      ISVREF(graph_grid,(SI_Long)23L) = svref_new_value;
		      store_managed_number_or_value_arg = 
			      Low_value_for_horizontal_grid_lines;
		      svref_new_value = 
			      store_managed_number_or_value_function(ISVREF(graph_grid,
			      (SI_Long)21L),store_managed_number_or_value_arg);
		      ISVREF(graph_grid,(SI_Long)21L) = svref_new_value;
		      store_managed_number_or_value_arg = 
			      High_value_for_horizontal_grid_lines;
		      svref_new_value = 
			      store_managed_number_or_value_function(ISVREF(graph_grid,
			      (SI_Long)22L),store_managed_number_or_value_arg);
		      ISVREF(graph_grid,(SI_Long)22L) = svref_new_value;
		      store_managed_number_or_value_arg = 
			      Interval_between_horizontal_grid_lines;
		      svref_new_value = 
			      store_managed_number_or_value_function(ISVREF(graph_grid,
			      (SI_Long)20L),store_managed_number_or_value_arg);
		      ISVREF(graph_grid,(SI_Long)20L) = svref_new_value;
		      if (Range_too_small_qm && 
			      (desired_low_value_for_vertical_axis_qm || 
			      desired_range_for_vertical_axis_qm)) {
			  Problems_reformatting_graph_qm = T;
			  add_frame_note(5,Qdesired_range_too_small,graph,
				  Nil,T,Nil);
		      }
		      low_value_for_vertical_axis = 
			      Low_value_for_horizontal_grid_lines;
		      high_value_for_vertical_axis = 
			      High_value_for_horizontal_grid_lines;
		      vertical_axis_range = Nil;
		      if ( !TRUEP(Range_too_small_qm) && graph) {
			  exact_specification_qm = 
				  slot_value_number_p(desired_absolute_or_relative_vertical_axis_range_qm);
			  if (exact_specification_qm);
			  else {
			      if (CONSP(desired_absolute_or_relative_vertical_axis_range_qm)) 
					  {
				  temp = 
					  CAR(desired_absolute_or_relative_vertical_axis_range_qm);
				  temp_1 = NUMBERP(temp);
				  if (temp_1);
				  else {
				      thing = 
					      CAR(desired_absolute_or_relative_vertical_axis_range_qm);
				      temp_1 = 
					      INLINE_DOUBLE_FLOAT_VECTOR_P(thing) 
					      != (SI_Long)0L ? 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) 
					      == (SI_Long)1L : TRUEP(Qnil);
				  }
				  temp_1 =  !temp_1;
			      }
			      else
				  temp_1 = TRUEP(Nil);
			      exact_specification_qm = temp_1 ? ( 
				      !TRUEP(FOURTH(desired_absolute_or_relative_vertical_axis_range_qm)) 
				      ? T : Nil) : Nil;
			  }
		      }
		      else
			  exact_specification_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Vertical_axis_range,Qvertical_axis_range,vertical_axis_range,
			      1);
			PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_vertical_axis,Qlow_value_for_vertical_axis,low_value_for_vertical_axis,
				0);
			  if (exact_specification_qm) {
			      Low_value_for_vertical_axis = 
				      Desired_low_value_for_vertical_axis;
			      high_value_for_vertical_axis = 
				      Desired_high_value_for_vertical_axis;
			  }
			  Vertical_axis_range = 
				  minus(high_value_for_vertical_axis,
				  Low_value_for_vertical_axis);
			  store_managed_number_or_value_arg = 
				  Low_value_for_vertical_axis;
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)47L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)47L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  high_value_for_vertical_axis;
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)48L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)48L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  Vertical_axis_range;
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)37L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)37L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  divide(ltimes(lfloat(Minimum_grid_height,
				  float_constant_1),
				  Interval_between_horizontal_grid_lines),
				  Vertical_axis_range);
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)24L),
				  store_managed_number_or_value_arg);
			  ISVREF(graph_grid,(SI_Long)24L) = svref_new_value;
			  store_managed_number_or_value_arg = 
				  divide(ltimes(lfloat(Minimum_grid_height,
				  float_constant_1),
				  minus(Interval_between_horizontal_grid_lines,
				  minus(High_value_for_horizontal_grid_lines,
				  high_value_for_vertical_axis))),
				  Vertical_axis_range);
			  svref_new_value = 
				  store_managed_number_or_value_function(ISVREF(graph_grid,
				  (SI_Long)25L),
				  store_managed_number_or_value_arg);
			  result = VALUES_1(ISVREF(graph_grid,
				  (SI_Long)25L) = svref_new_value);
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
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qbackground_colors;  /* background-colors */

static Object Qhorizontal_or_vertical_axis_label_qm;  /* horizontal-or-vertical-axis-label? */

/* PUT-UP-NEW-LABELS-FOR-HORIZONTAL-GRAPH-AXIS */
Object put_up_new_labels_for_horizontal_graph_axis(graph_grid,graph_format,
	    strip_chart_qm)
    Object graph_grid, graph_format, strip_chart_qm;
{
    Object digits_to_left_of_decimal_point, digits_to_right_of_decimal_point;
    Object horizontal_axis_is_time_axis_qm, managed_number_or_value;
    Object interval_between_grid_lines, gensymed_symbol, y_position_for_label;
    Object previous_x_position_for_label, number_of_vertical_grid_lines, temp;
    Object temp_1, temp_2, temp_3, last_label, first_time_qm, last_time_qm;
    Object new_horizontal_axis_label, width_of_label, half_width_of_label;
    Object x_position_for_label, ab_loop_iter_flag_, gensymed_symbol_5;
    Object gensymed_symbol_6, gensymed_symbol_7;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, x_position_for_last_label, width_of_last_label;
    SI_Long label_number, ab_loop_bind_;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,27);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	remove_axis_labels_from_graph_grid(Qhorizontal,graph_grid);
	ISVREF(graph_grid,(SI_Long)55L) = Nil;
	digits_to_left_of_decimal_point = Nil;
	digits_to_right_of_decimal_point = Nil;
	horizontal_axis_is_time_axis_qm = T;
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)26L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    interval_between_grid_lines = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    interval_between_grid_lines = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    interval_between_grid_lines = 
		    copy_text_string(managed_number_or_value);
	else
	    interval_between_grid_lines = managed_number_or_value;
	if ( !TRUEP(horizontal_axis_is_time_axis_qm)) {
	    result = determine_format_for_non_time_axis_label(interval_between_grid_lines);
	    MVS_2(result,digits_to_left_of_decimal_point,
		    digits_to_right_of_decimal_point);
	}
	gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)35L));
	gensymed_symbol_3 = IFIX(ISVREF(graph_grid,(SI_Long)40L));
	gensymed_symbol_4 = (SI_Long)3L;
	y_position_for_label = l_round(FIX(gensymed_symbol_1 + 
		gensymed_symbol_2 + gensymed_symbol_3 + gensymed_symbol_4),_);
	previous_x_position_for_label = Nil;
	gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)38L));
	x_position_for_last_label = gensymed_symbol_1 + gensymed_symbol_2;
	number_of_vertical_grid_lines = ISVREF(graph_grid,(SI_Long)29L);
	PUSH_SPECIAL_WITH_SYMBOL(Number_of_vertical_grid_lines,Qnumber_of_vertical_grid_lines,number_of_vertical_grid_lines,
		0);
	  temp = FIXNUM_SUB1(Number_of_vertical_grid_lines);
	  temp_1 = digits_to_left_of_decimal_point;
	  temp_2 = digits_to_right_of_decimal_point;
	  gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  if (gensymed_symbol) {
	      gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      temp_3 = get_lookup_slot_value(gensymed_symbol,
		      Qbackground_colors);
	      temp_3 = CAR(temp_3);
	  }
	  else
	      temp_3 = Nil;
	  last_label = make_horizontal_axis_label(9,temp,graph_grid,
		  strip_chart_qm,T,horizontal_axis_is_time_axis_qm,
		  interval_between_grid_lines,temp_1,temp_2,temp_3);
	  gensymed_symbol = ISVREF(last_label,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(last_label,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  width_of_last_label = gensymed_symbol_1 - gensymed_symbol_2;
	  label_number = (SI_Long)-1L;
	  ab_loop_bind_ = IFIX(Number_of_vertical_grid_lines) - (SI_Long)2L;
	  first_time_qm = T;
	  last_time_qm = Nil;
	  new_horizontal_axis_label = Nil;
	  width_of_label = Nil;
	  half_width_of_label = Nil;
	  x_position_for_label = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop:
	  if (label_number > ab_loop_bind_)
	      goto end_loop;
	  if ( !TRUEP(ab_loop_iter_flag_))
	      first_time_qm = Nil;
	  last_time_qm = label_number == 
		  IFIX(Number_of_vertical_grid_lines) - (SI_Long)2L ? T : Nil;
	  if (last_time_qm)
	      new_horizontal_axis_label = last_label;
	  else {
	      temp = FIX(label_number + (SI_Long)1L);
	      temp_1 = digits_to_left_of_decimal_point;
	      temp_2 = digits_to_right_of_decimal_point;
	      gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,
			  (SI_Long)14L));
		  gensymed_symbol = gensymed_symbol ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) 
			  : Nil;
		  temp_3 = get_lookup_slot_value(gensymed_symbol,
			  Qbackground_colors);
		  temp_3 = CAR(temp_3);
	      }
	      else
		  temp_3 = Nil;
	      new_horizontal_axis_label = make_horizontal_axis_label(9,
		      temp,graph_grid,strip_chart_qm,Nil,
		      horizontal_axis_is_time_axis_qm,
		      interval_between_grid_lines,temp_1,temp_2,temp_3);
	  }
	  gensymed_symbol = ISVREF(new_horizontal_axis_label,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(new_horizontal_axis_label,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)0L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  width_of_label = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	  half_width_of_label = FIX(IFIX(width_of_label) >>  -  - (SI_Long)1L);
	  if (first_time_qm) {
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)39L));
	      gensymed_symbol_3 = IFIX(width_of_label);
	      x_position_for_label = FIX(gensymed_symbol_1 - 
		      gensymed_symbol_2 - gensymed_symbol_3);
	  }
	  else if (last_time_qm)
	      x_position_for_label = FIX(x_position_for_last_label);
	  else {
	      gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)2L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)39L));
	      managed_number_or_value = ISVREF(graph_grid,(SI_Long)31L);
	      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		      (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		      == (SI_Long)1L)
		  temp_2 = 
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			  (SI_Long)0L));
	      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		      (SI_Long)0L && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		      == (SI_Long)1L)
		  temp_2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	      else if (text_string_p(managed_number_or_value))
		  temp_2 = copy_text_string(managed_number_or_value);
	      else
		  temp_2 = managed_number_or_value;
	      temp_3 = FIX(label_number);
	      managed_number_or_value = ISVREF(graph_grid,(SI_Long)30L);
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
	      gensymed_symbol_3 = IFIX(l_round(add(temp_2,ltimes(temp_3,
		      add(temp_1,ISVREF(graph_format,(SI_Long)29L)))),_));
	      gensymed_symbol_4 = IFIX(half_width_of_label);
	      x_position_for_label = FIX(gensymed_symbol_1 - 
		      gensymed_symbol_2 - gensymed_symbol_3 - 
		      gensymed_symbol_4);
	  }
	  if ((first_time_qm || last_time_qm || 
		  FIXNUM_GT(FIXNUM_MINUS(previous_x_position_for_label,
		  x_position_for_label),width_of_label) && 
		  IFIX(x_position_for_label) - x_position_for_last_label > 
		  width_of_last_label) && FIXNUM_GT(ISVREF(graph_grid,
		  (SI_Long)34L),width_of_label)) {
	      previous_x_position_for_label = x_position_for_label;
	      set_non_savable_lookup_slot_value(new_horizontal_axis_label,
		      Qhorizontal_or_vertical_axis_label_qm,Qhorizontal);
	      if (first_time_qm)
		  ISVREF(graph_grid,(SI_Long)55L) = new_horizontal_axis_label;
	      gensymed_symbol = 
		      ISVREF(ISVREF(ISVREF(ISVREF(new_horizontal_axis_label,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),(SI_Long)1L);
	      gensymed_symbol_5 = new_horizontal_axis_label;
	      gensymed_symbol_6 = x_position_for_label;
	      gensymed_symbol_7 = y_position_for_label;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_5,
		      gensymed_symbol_6,gensymed_symbol_7);
	      add_subblock(new_horizontal_axis_label,graph_grid);
	  }
	  else {
	      if (first_time_qm)
		  previous_x_position_for_label = x_position_for_label;
	      delete_frame(new_horizontal_axis_label);
	  }
	  ab_loop_iter_flag_ = Nil;
	  label_number = label_number + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* MAKE-HORIZONTAL-AXIS-LABEL */
Object make_horizontal_axis_label varargs_1(int, n)
{
    Object label_number, graph_grid, strip_chart_qm, low_value_label_qm;
    Object horizontal_axis_is_time_axis_qm, interval_between_grid_lines;
    Object digits_to_left_of_decimal_point, digits_to_right_of_decimal_point;
    Object background_color_qm, managed_number_or_value, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(173,28);
    INIT_ARGS_nonrelocating();
    label_number = REQUIRED_ARG_nonrelocating();
    graph_grid = REQUIRED_ARG_nonrelocating();
    strip_chart_qm = REQUIRED_ARG_nonrelocating();
    low_value_label_qm = REQUIRED_ARG_nonrelocating();
    horizontal_axis_is_time_axis_qm = REQUIRED_ARG_nonrelocating();
    interval_between_grid_lines = REQUIRED_ARG_nonrelocating();
    digits_to_left_of_decimal_point = REQUIRED_ARG_nonrelocating();
    digits_to_right_of_decimal_point = REQUIRED_ARG_nonrelocating();
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (horizontal_axis_is_time_axis_qm)
	return make_new_time_axis_label(5,label_number,graph_grid,
		strip_chart_qm,low_value_label_qm,background_color_qm);
    else {
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)44L);
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
	return make_new_variable_axis_label(4,add(temp,ltimes(label_number,
		interval_between_grid_lines)),
		digits_to_left_of_decimal_point,
		digits_to_right_of_decimal_point,background_color_qm);
    }
}

static Object Qdraw_graph_grid_current_time_display;  /* draw-graph-grid-current-time-display */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-UP-NEW-HIGH-VALUE-LABEL-FOR-HORIZONTAL-AXIS */
Object put_up_new_high_value_label_for_horizontal_axis(graph_grid)
    Object graph_grid;
{
    Object new_label, gensymed_symbol, graph, high_value_label;
    Object old_label_text_value, temp, temp_1, temp_2, svref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(173,29);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	new_label = make_text_string_for_time_axis_label(FIX((SI_Long)0L),
		graph_grid,T,Nil);
    POP_LOCAL_ALLOCATION(0,0);
    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    graph = gensymed_symbol;
    high_value_label = ISVREF(graph_grid,(SI_Long)55L);
    old_label_text_value = ISVREF(high_value_label,(SI_Long)16L);
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    update_images(10,T,graph,graph,temp,temp_1,temp_2,gensymed_symbol,Nil,
	    Qdraw_graph_grid_current_time_display,graph_grid);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(high_value_label,Qbox_translation_and_text);
    temp = No_value;
    svref_new_value = slot_value_cons_1(temp,
	    convert_text_string_to_text(new_label));
    SVREF(high_value_label,FIX((SI_Long)16L)) = svref_new_value;
    reclaim_slot_value(old_label_text_value);
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    temp_2 = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    temp_1 = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    temp = gensymed_symbol;
    gensymed_symbol = ISVREF(high_value_label,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return update_images(10,Nil,graph,graph,temp_2,temp_1,temp,
	    gensymed_symbol,Nil,Qdraw_graph_grid_current_time_display,
	    graph_grid);
}

/* LABEL-VALUES-SAME-P */
Object label_values_same_p(value_1,value_2,number_of_grid_lines)
    Object value_1, value_2, number_of_grid_lines;
{
    Object temp;
    double value_1_float, value_2_float, temp_1, arg, temp_2, arg_1;

    x_note_fn_call(173,30);
    temp = lfloat(value_1,float_constant_1);
    value_1_float = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = lfloat(value_2,float_constant_1);
    value_2_float = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp_1 = value_1_float - value_2_float;
    arg = ABS(temp_1);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(Minimum_range_to_maximum_value_ratio);
    temp = lfloat(number_of_grid_lines,float_constant_1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    arg_1 = temp_2 / (temp_1 * 10.0);
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg))
	return VALUES_1( !inline_nanp_for_comparison(arg_1) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* PUT-UP-NEW-LABELS-FOR-VERTICAL-GRAPH-AXIS */
Object put_up_new_labels_for_vertical_graph_axis(graph_grid,graph_format)
    Object graph_grid, graph_format;
{
    Object digits_to_left_of_decimal_point, digits_to_right_of_decimal_point;
    Object managed_number_or_value, interval_between_grid_lines;
    Object previous_y_position_for_label, gensymed_symbol;
    Object number_of_horizontal_grid_lines;
    Object high_value_for_horizontal_grid_lines, low_label_value, temp;
    Object new_vertical_axis_label, height_of_label, x_position_for_label;
    Object y_position_for_label, first_time_qm, last_time_qm, label_value;
    Object skip_qm, ab_loop_iter_flag_, temp_1, temp_2, temp_3;
    Object gensymed_symbol_5, gensymed_symbol_6, gensymed_symbol_7;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, y_position_for_last_label;
    SI_Long label_number, ab_loop_bind_, gensymed_symbol_3, gensymed_symbol_4;
    char skip_last_label_qm;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,31);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	remove_axis_labels_from_graph_grid(Qvertical,graph_grid);
	digits_to_left_of_decimal_point = Nil;
	digits_to_right_of_decimal_point = Nil;
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)20L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    interval_between_grid_lines = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    interval_between_grid_lines = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    interval_between_grid_lines = 
		    copy_text_string(managed_number_or_value);
	else
	    interval_between_grid_lines = managed_number_or_value;
	result = determine_format_for_non_time_axis_label(interval_between_grid_lines);
	MVS_2(result,digits_to_left_of_decimal_point,
		digits_to_right_of_decimal_point);
	previous_y_position_for_label = Nil;
	gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)41L));
	y_position_for_last_label = gensymed_symbol_1 - gensymed_symbol_2;
	number_of_horizontal_grid_lines = ISVREF(graph_grid,(SI_Long)23L);
	PUSH_SPECIAL_WITH_SYMBOL(Number_of_horizontal_grid_lines,Qnumber_of_horizontal_grid_lines,number_of_horizontal_grid_lines,
		1);
	  managed_number_or_value = ISVREF(graph_grid,(SI_Long)22L);
	  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      high_value_for_horizontal_grid_lines = 
		      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		      (SI_Long)0L));
	  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		  (SI_Long)0L && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		  == (SI_Long)1L)
	      high_value_for_horizontal_grid_lines = 
		      aref1(managed_number_or_value,FIX((SI_Long)0L));
	  else if (text_string_p(managed_number_or_value))
	      high_value_for_horizontal_grid_lines = 
		      copy_text_string(managed_number_or_value);
	  else
	      high_value_for_horizontal_grid_lines = managed_number_or_value;
	  PUSH_SPECIAL_WITH_SYMBOL(High_value_for_horizontal_grid_lines,Qhigh_value_for_horizontal_grid_lines,high_value_for_horizontal_grid_lines,
		  0);
	    managed_number_or_value = ISVREF(graph_grid,(SI_Long)47L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		low_label_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		low_label_value = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		low_label_value = copy_text_string(managed_number_or_value);
	    else
		low_label_value = managed_number_or_value;
	    managed_number_or_value = ISVREF(graph_grid,(SI_Long)21L);
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
	    skip_last_label_qm =  
		    !TRUEP(label_values_same_p(low_label_value,temp,
		    Number_of_horizontal_grid_lines));
	    new_vertical_axis_label = Nil;
	    height_of_label = Nil;
	    x_position_for_label = Nil;
	    y_position_for_label = Nil;
	    label_number = (SI_Long)-1L;
	    ab_loop_bind_ = IFIX(Number_of_horizontal_grid_lines) - 
		    (SI_Long)2L;
	    first_time_qm = T;
	    last_time_qm = Nil;
	    label_value = Nil;
	    skip_qm = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (label_number > ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		first_time_qm = Nil;
	    last_time_qm = label_number == 
		    IFIX(Number_of_horizontal_grid_lines) - (SI_Long)2L ? 
		    T : Nil;
	    if (first_time_qm) {
		managed_number_or_value = ISVREF(graph_grid,(SI_Long)48L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    label_value = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    label_value = aref1(managed_number_or_value,
			    FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    label_value = copy_text_string(managed_number_or_value);
		else
		    label_value = managed_number_or_value;
	    }
	    else if (last_time_qm)
		label_value = low_label_value;
	    else
		label_value = minus(High_value_for_horizontal_grid_lines,
			ltimes(FIX(label_number + (SI_Long)1L),
			interval_between_grid_lines));
	    if (first_time_qm)
		skip_qm =  !TRUEP(label_values_same_p(label_value,
			High_value_for_horizontal_grid_lines,
			Number_of_horizontal_grid_lines)) ? T : Nil;
	    else if (last_time_qm)
		skip_qm = skip_last_label_qm ? T : Nil;
	    else
		skip_qm = Qnil;
	    if ( !TRUEP(skip_qm)) {
		temp_1 = label_value;
		temp_2 = digits_to_left_of_decimal_point;
		temp_3 = digits_to_right_of_decimal_point;
		gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
		gensymed_symbol = gensymed_symbol ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
		if (gensymed_symbol) {
		    gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,
			    (SI_Long)14L));
		    gensymed_symbol = gensymed_symbol ? 
			    ACCESS_ONCE(ISVREF(gensymed_symbol,
			    (SI_Long)5L)) : Nil;
		    temp = get_lookup_slot_value(gensymed_symbol,
			    Qbackground_colors);
		    temp = CAR(temp);
		}
		else
		    temp = Nil;
		new_vertical_axis_label = make_new_variable_axis_label(4,
			temp_1,temp_2,temp_3,temp);
		gensymed_symbol = ISVREF(new_vertical_axis_label,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(new_vertical_axis_label,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)1L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		height_of_label = FIX(gensymed_symbol_1 - gensymed_symbol_2);
		gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_1 = IFIX(gensymed_symbol);
		gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)38L));
		gensymed_symbol = ISVREF(new_vertical_axis_label,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)2L) : FIX((SI_Long)0L);
		gensymed_symbol_3 = IFIX(gensymed_symbol);
		gensymed_symbol = ISVREF(new_vertical_axis_label,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		gensymed_symbol_4 = IFIX(gensymed_symbol);
		gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
		gensymed_symbol_3 =  - gensymed_symbol_3;
		gensymed_symbol_4 = (SI_Long)-3L;
		x_position_for_label = FIX(gensymed_symbol_1 + 
			gensymed_symbol_2 + gensymed_symbol_3 + 
			gensymed_symbol_4);
		if (first_time_qm) {
		    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)40L));
		    gensymed_symbol_3 = (SI_Long)-3L;
		    y_position_for_label = FIX(gensymed_symbol_1 + 
			    gensymed_symbol_2 + gensymed_symbol_3);
		}
		else if (last_time_qm)
		    y_position_for_label = FIX(y_position_for_last_label - 
			    IFIX(height_of_label) - (SI_Long)-3L);
		else {
		    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)1L) : 
			    FIX((SI_Long)0L);
		    gensymed_symbol_1 = IFIX(gensymed_symbol);
		    gensymed_symbol_2 = IFIX(ISVREF(graph_grid,(SI_Long)40L));
		    managed_number_or_value = ISVREF(graph_grid,(SI_Long)25L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_3 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_3 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp_3 = copy_text_string(managed_number_or_value);
		    else
			temp_3 = managed_number_or_value;
		    temp = FIX(label_number);
		    managed_number_or_value = ISVREF(graph_grid,(SI_Long)24L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_2 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp_2 = copy_text_string(managed_number_or_value);
		    else
			temp_2 = managed_number_or_value;
		    gensymed_symbol_3 = IFIX(l_round(add(temp_3,
			    ltimes(temp,add(temp_2,ISVREF(graph_format,
			    (SI_Long)27L)))),_));
		    gensymed_symbol_4 =  - (IFIX(height_of_label) >>  -  - 
			    (SI_Long)1L);
		    y_position_for_label = FIX(gensymed_symbol_1 + 
			    gensymed_symbol_2 + gensymed_symbol_3 + 
			    gensymed_symbol_4);
		}
		if ( !TRUEP(previous_y_position_for_label) || 
			(last_time_qm || skip_last_label_qm || 
			y_position_for_last_label - 
			IFIX(y_position_for_label) > IFIX(height_of_label) 
			* (SI_Long)2L) && 
			FIXNUM_GT(FIXNUM_MINUS(y_position_for_label,
			previous_y_position_for_label),height_of_label)) {
		    previous_y_position_for_label = y_position_for_label;
		    set_non_savable_lookup_slot_value(new_vertical_axis_label,
			    Qhorizontal_or_vertical_axis_label_qm,Qvertical);
		    gensymed_symbol = 
			    ISVREF(ISVREF(ISVREF(ISVREF(new_vertical_axis_label,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)32L),
			    (SI_Long)1L);
		    gensymed_symbol_5 = new_vertical_axis_label;
		    gensymed_symbol_6 = x_position_for_label;
		    gensymed_symbol_7 = y_position_for_label;
		    inline_funcall_3(gensymed_symbol,gensymed_symbol_5,
			    gensymed_symbol_6,gensymed_symbol_7);
		    add_subblock(new_vertical_axis_label,graph_grid);
		}
		else
		    delete_frame(new_vertical_axis_label);
	    }
	    ab_loop_iter_flag_ = Nil;
	    label_number = label_number + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qlabel_permanent_qm;  /* label-permanent? */

/* REMOVE-AXIS-LABELS-FROM-GRAPH-GRID */
Object remove_axis_labels_from_graph_grid(axis,graph_grid)
    Object axis, graph_grid;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, axis_label;
    Object temp_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(173,32);
    PUSH_SPECIAL_WITH_SYMBOL(Axis,Qaxis,axis,0);
      gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
      gensymed_symbol = gensymed_symbol ? 
	      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
      ab_queue_form_ = gensymed_symbol;
      ab_next_queue_element_ = Nil;
      axis_label = Nil;
      if (ab_queue_form_)
	  ab_next_queue_element_ = 
		  constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		  ab_queue_form_);
    next_loop:
      if ( !TRUEP(ab_next_queue_element_))
	  goto end_loop;
      axis_label = ISVREF(ab_next_queue_element_,(SI_Long)4L);
      ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	      ab_queue_form_);
      if ( !TRUEP(get_lookup_slot_value_given_default(axis_label,
	      Qlabel_permanent_qm,Nil))) {
	  temp =  !TRUEP(get_lookup_slot_value_given_default(axis_label,
		  Qhorizontal_or_vertical_axis_label_qm,Nil));
	  if (temp);
	  else {
	      temp_1 = get_lookup_slot_value_given_default(axis_label,
		      Qhorizontal_or_vertical_axis_label_qm,Nil);
	      temp = EQ(temp_1,Axis);
	  }
      }
      else
	  temp = TRUEP(Nil);
      if (temp) {
	  remove_as_subblock_if_necessary(1,axis_label);
	  delete_frame(axis_label);
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object float_constant_4;    /* 0.01 */

static Object float_constant_5;    /* 0.1 */

/* DETERMINE-FORMAT-FOR-NON-TIME-AXIS-LABEL */
Object determine_format_for_non_time_axis_label(interval_between_grid_lines)
    Object interval_between_grid_lines;
{
    Object temp;

    x_note_fn_call(173,33);
    if (NUM_LT(interval_between_grid_lines,float_constant_4))
	return VALUES_2(FIX((SI_Long)1L),FIX((SI_Long)3L));
    else if (NUM_LT(interval_between_grid_lines,float_constant_5))
	return VALUES_2(FIX((SI_Long)2L),FIX((SI_Long)2L));
    else {
	temp = FIX((SI_Long)1L);
	if (NUM_LT(interval_between_grid_lines,temp))
	    return VALUES_2(FIX((SI_Long)3L),FIX((SI_Long)1L));
	else
	    return VALUES_2(FIX((SI_Long)4L),FIX((SI_Long)0L));
    }
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* MAKE-NEW-VARIABLE-AXIS-LABEL */
Object make_new_variable_axis_label varargs_1(int, n)
{
    Object label_value, digits_to_left_of_decimal_point;
    Object digits_to_right_of_decimal_point;
    Object background_color_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(173,34);
    INIT_ARGS_nonrelocating();
    label_value = REQUIRED_ARG_nonrelocating();
    digits_to_left_of_decimal_point = REQUIRED_ARG_nonrelocating();
    digits_to_right_of_decimal_point = REQUIRED_ARG_nonrelocating();
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
	      write_floating_point_number(4,label_value,
		      digits_to_left_of_decimal_point,
		      digits_to_right_of_decimal_point,FIX((SI_Long)4L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return make_graph_axis_label(3,temp,Nil,background_color_qm);
}

/* MAKE-NEW-TIME-AXIS-LABEL */
Object make_new_time_axis_label varargs_1(int, n)
{
    Object label_number, graph_grid, strip_chart_qm, low_value_label_qm;
    Object background_color_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(173,35);
    INIT_ARGS_nonrelocating();
    label_number = REQUIRED_ARG_nonrelocating();
    graph_grid = REQUIRED_ARG_nonrelocating();
    strip_chart_qm = REQUIRED_ARG_nonrelocating();
    low_value_label_qm = REQUIRED_ARG_nonrelocating();
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return make_graph_axis_label(3,
	    make_text_string_for_time_axis_label(label_number,graph_grid,
	    strip_chart_qm,low_value_label_qm),Nil,background_color_qm);
}

/* MAKE-TEXT-STRING-FOR-TIME-AXIS-LABEL */
Object make_text_string_for_time_axis_label(label_number,graph_grid,
	    strip_chart_qm,low_value_label_qm)
    Object label_number, graph_grid, strip_chart_qm, low_value_label_qm;
{
    Object managed_number_or_value, label_interval, temp, label_scale_qm;
    Object print_time_relative_to_high_value_qm, second_1, minute, hour, date;
    Object month, year, day_of_week, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, schar_arg_2, schar_new_value, hours, minutes;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    Declare_special(5);
    Object result;

    x_note_fn_call(173,36);
    if (low_value_label_qm) {
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)36L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    label_interval = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    label_interval = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    label_interval = copy_text_string(managed_number_or_value);
	else
	    label_interval = managed_number_or_value;
    }
    else {
	managed_number_or_value = ISVREF(graph_grid,(SI_Long)26L);
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
	label_interval = ltimes(label_number,temp);
    }
    label_scale_qm = ISVREF(graph_grid,(SI_Long)32L);
    print_time_relative_to_high_value_qm = strip_chart_qm ? 
	    (IFIX(label_number) != (SI_Long)0L ? T : Nil) : Qnil;
    second_1 = Nil;
    minute = Nil;
    hour = Nil;
    date = Nil;
    month = Nil;
    year = Nil;
    day_of_week = Nil;
    if ( !TRUEP(print_time_relative_to_high_value_qm)) {
	if (IFIX(label_number) == (SI_Long)0L) {
	    managed_number_or_value = ISVREF(graph_grid,(SI_Long)46L);
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
	}
	else if (low_value_label_qm) {
	    managed_number_or_value = ISVREF(graph_grid,(SI_Long)44L);
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
	}
	else {
	    managed_number_or_value = ISVREF(graph_grid,(SI_Long)28L);
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
	    temp = minus(temp,label_interval);
	}
	result = decode_gensym_time(FIXNUM_ADD(l_round(temp,_),
		Gensym_time_at_start));
	MVS_7(result,second_1,minute,hour,date,month,year,day_of_week);
    }
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
	      if (print_time_relative_to_high_value_qm) {
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)45L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp_1 = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)45L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		      temp_1 = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp_1;
		  }
	      }
	      if (label_scale_qm) {
		  if (! !(FIXNUMP(label_scale_qm) && 
			  FIXNUM_LE(FIX((SI_Long)-2147483648L),
			  label_scale_qm) && FIXNUM_LE(label_scale_qm,
			  FIX((SI_Long)2147483647L))))
		      switch (INTEGER_TO_INT(label_scale_qm)) {
			case 60:
			case 3600:
			  if (print_time_relative_to_high_value_qm) {
			      result = chestnut_floorf_function(label_interval,
				      FIX((SI_Long)60L));
			      MVS_2(result,minute,second_1);
			  }
			  print_minute_and_second(minute,second_1);
			  break;
			case 86400:
			  if (print_time_relative_to_high_value_qm) {
			      result = chestnut_floorf_function(l_round(label_interval,
				      FIX((SI_Long)60L)),FIX((SI_Long)60L));
			      MVS_2(result,hours,minutes);
			      print_relative_hours_and_minutes(hours,minutes);
			  }
			  else
			      print_hour_and_minute(hour,minute);
			  break;
			case 259200:
			  if (print_time_relative_to_high_value_qm)
			      print_relative_hours(l_round(label_interval,
				      FIX((SI_Long)3600L)));
			  else
			      print_day_of_week_and_hour(day_of_week,hour);
			  break;
			case 2419200:
			  if (print_time_relative_to_high_value_qm)
			      print_relative_days(l_round(label_interval,
				      FIX((SI_Long)86400L)));
			  else
			      print_month_and_date(month,date);
			  break;
			default:
			  break;
		      }
	      }
	      else if (print_time_relative_to_high_value_qm)
		  print_relative_weeks(l_round(label_interval,
			  FIX((SI_Long)604800L)));
	      else
		  print_month_and_year(month,year);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* PUT-UP-LABEL-FOR-GRAPH-HORIZONTAL-AXIS */
Object put_up_label_for_graph_horizontal_axis(graph_grid,graph_format)
    Object graph_grid, graph_format;
{
    x_note_fn_call(173,37);
    return VALUES_1(Nil);
}

static Object Qplot;               /* plot */

static Object Qdefault_plot_format;  /* default-plot-format */

/* MAKE-PLOT */
Object make_plot(display_expression,plot_color_qm,plot_pattern_qm,
	    plot_min_and_max_qm,graph_grid)
    Object display_expression, plot_color_qm, plot_pattern_qm;
    Object plot_min_and_max_qm, graph_grid;
{
    Object new_plot, plot_format, plot_color, current_block_of_dependent_frame;
    Object svref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(173,38);
    PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
	    1);
      new_plot = make_frame(Qplot);
      plot_format = get_instance_with_name_if_any(Qformat_frame,
	      Qdefault_plot_format);
      if (plot_format);
      else
	  plot_format = make_format_frame(Qdefault_plot_format);
      plot_color = plot_color_qm;
      if (plot_color);
      else
	  plot_color = ISVREF(plot_format,(SI_Long)22L);
      current_block_of_dependent_frame = graph_grid;
      PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	      0);
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	SVREF(new_plot,FIX((SI_Long)2L)) = plot_format;
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	SVREF(new_plot,FIX((SI_Long)3L)) = display_expression;
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	svref_new_value =  !TRUEP(plot_pattern_qm) &&  
		!TRUEP(Plot_min_and_max_qm) ? plot_color : 
		slot_value_cons_1(plot_color,
		slot_value_cons_1(plot_pattern_qm,Plot_min_and_max_qm ? 
		slot_value_cons_1(Plot_min_and_max_qm,Nil) : Nil));
	SVREF(new_plot,FIX((SI_Long)4L)) = svref_new_value;
	result = VALUES_1(new_plot);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* REFRESH-DATA-FOR-PLOTS */
Object refresh_data_for_plots(graph_grid,graph_format,
	    horizontal_axis_grid_format_not_changed_p)
    Object graph_grid, graph_format, horizontal_axis_grid_format_not_changed_p;
{
    Object width, plot, ab_loop_list_, ab_loop_iter_flag_, temp;
    SI_Long plot_number;

    x_note_fn_call(173,39);
    width = ISVREF(graph_grid,(SI_Long)34L);
    plot = Nil;
    ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    plot_number = (SI_Long)1L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    plot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	plot_number = plot_number + (SI_Long)1L;
    temp = FIX((SI_Long)0L);
    if (NUM_GT(width,temp))
	refresh_plot_data_buffer(plot,graph_grid,graph_format,
		horizontal_axis_grid_format_not_changed_p,FIX(plot_number));
    else
	clear_plot(plot);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COMPUTE-MINIMUM-RIGHT-EDGE-FOR-GRAPH-GRID */
Object compute_minimum_right_edge_for_graph_grid(graph_grid)
    Object graph_grid;
{
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(173,40);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    return VALUES_1(FIX(gensymed_symbol_1 + gensymed_symbol_2));
}

/* COMPUTE-MINIMUM-BOTTOM-EDGE-FOR-GRAPH-GRID */
Object compute_minimum_bottom_edge_for_graph_grid(graph_grid)
    Object graph_grid;
{
    Object gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(173,41);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(graph_grid,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    return VALUES_1(FIX(gensymed_symbol_1 + gensymed_symbol_2));
}

/* RESIZE-FOR-GRAPH-GRID */
Object resize_for_graph_grid(graph_grid,right_edge_for_graph_grid,
	    bottom_edge_for_graph_grid,other_data_for_resizing)
    Object graph_grid, right_edge_for_graph_grid, bottom_edge_for_graph_grid;
    Object other_data_for_resizing;
{
    x_note_fn_call(173,42);
    return VALUES_1(other_data_for_resizing);
}

static Object Qzero_interval_between_horizontal_grid_lines;  /* zero-interval-between-horizontal-grid-lines */

/* DETERMINE-RULING-FOR-AXIS */
Object determine_ruling_for_axis(low_value,high_value,
	    desired_number_of_grid_lines,interval_between_rulings_qm)
    Object low_value, high_value, desired_number_of_grid_lines;
    Object interval_between_rulings_qm;
{
    Object range, absolute_maximum, range_to_absolute_maximum_ratio;
    Object ratio_offset, range_offset, temp, slot_value_number, temp_1;

    x_note_fn_call(173,43);
    range = lfloat(minus(high_value,low_value),float_constant_1);
    absolute_maximum = lmax(l_abs(high_value),l_abs(low_value));
    range_to_absolute_maximum_ratio = Nil;
    ratio_offset = Nil;
    range_offset = Nil;
    temp = FIX((SI_Long)0L);
    if (NUM_EQ(absolute_maximum,temp)) {
	low_value = negate(Minimum_range_to_maximum_value_ratio);
	high_value = Minimum_range_to_maximum_value_ratio;
	Range_too_small_qm = T;
    }
    else {
	range_to_absolute_maximum_ratio = divide(range,absolute_maximum);
	ratio_offset = ltimes(minus(Minimum_range_to_maximum_value_ratio,
		range_to_absolute_maximum_ratio),absolute_maximum);
	temp = FIX((SI_Long)0L);
	if (NUM_GT(ratio_offset,temp)) {
	    low_value = minus(low_value,divide(ratio_offset,FIX((SI_Long)2L)));
	    high_value = add(high_value,divide(ratio_offset,FIX((SI_Long)2L)));
	    Range_too_small_qm = T;
	}
	if (NUM_LT(range,Minimum_range_to_maximum_value_ratio)) {
	    range_offset = minus(Minimum_range_to_maximum_value_ratio,range);
	    low_value = minus(low_value,divide(range_offset,FIX((SI_Long)2L)));
	    high_value = add(high_value,divide(range_offset,FIX((SI_Long)2L)));
	    Range_too_small_qm = T;
	}
    }
    if (interval_between_rulings_qm) {
	slot_value_number = CAR(interval_between_rulings_qm);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == 
		(SI_Long)1L)
	    temp = aref1(slot_value_number,FIX((SI_Long)0L));
	else
	    temp = slot_value_number;
	temp_1 = FIX((SI_Long)0L);
	if (NUM_EQ(temp,temp_1)) {
	    Problems_reformatting_graph_qm = 
		    Qzero_interval_between_horizontal_grid_lines;
	    return determine_rulings_automatically(low_value,high_value);
	}
	else
	    return determine_rulings_based_on_interval(low_value,
		    high_value,interval_between_rulings_qm);
    }
    else
	return determine_rulings_automatically(low_value,high_value);
}

static Object Qtoo_many_grid_lines;  /* too-many-grid-lines */

/* DETERMINE-RULINGS-BASED-ON-INTERVAL */
Object determine_rulings_based_on_interval(low_value,high_value,
	    interval_between_rulings)
    Object low_value, high_value, interval_between_rulings;
{
    Object slot_value_number, interval, temp, base, low_ruling, high_ruling;
    Object number_of_rulings;
    double temp_1, temp_2;

    x_note_fn_call(173,44);
    slot_value_number = CAR(interval_between_rulings);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	interval = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	interval = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	interval = slot_value_number;
    slot_value_number = CDR(interval_between_rulings);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	temp = aref1(slot_value_number,FIX((SI_Long)0L));
    else
	temp = slot_value_number;
    base = rem(temp,interval);
    temp = lfloat(low_value,float_constant_1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = lfloat(base,_);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    low_ruling = minus(ltimes(lfloor(divide(DOUBLE_TO_DOUBLE_FLOAT(temp_1 
	    + temp_2),interval),_),interval),base);
    temp = lfloat(high_value,float_constant_1);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = lfloat(base,_);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    high_ruling = add(ltimes(ceiling(divide(DOUBLE_TO_DOUBLE_FLOAT(temp_1 
	    - temp_2),interval),_),interval),base);
    number_of_rulings = 
	    FIXNUM_ADD1(l_round(divide(lfloat(minus(high_ruling,
	    low_ruling),float_constant_1),interval),_));
    if (FIXNUM_GT(number_of_rulings,Maximum_number_of_horizontal_grid_lines)) {
	Problems_reformatting_graph_qm = T;
	add_frame_note(5,Qtoo_many_grid_lines,Current_computation_frame,
		Nil,T,Nil);
	return determine_rulings_automatically(low_value,high_value);
    }
    else
	return VALUES_4(low_ruling,high_ruling,number_of_rulings,interval);
}

static Object float_constant_6;    /* 1.0 */

static Object float_constant_7;    /* 10.0 */

static Object float_constant_8;    /* 5.0 */

/* DETERMINE-RULINGS-AUTOMATICALLY */
Object determine_rulings_automatically(low_value,high_value)
    Object low_value, high_value;
{
    Object range, l, k, low_ruling, high_ruling, number_of_rulings, quotient;
    Object increment_per_ruling, best_low_ruling, best_high_ruling;
    Object best_number_of_rulings, best_increment_per_ruling;
    Object try_for_more_rulings_qm, temp;

    x_note_fn_call(173,45);
    range = lfloat(minus(high_value,low_value),float_constant_1);
    l = float_constant_6;
    k = float_constant_1;
    low_ruling = Nil;
    high_ruling = Nil;
    number_of_rulings = Nil;
    quotient = Nil;
    increment_per_ruling = Nil;
    best_low_ruling = Nil;
    best_high_ruling = Nil;
    best_number_of_rulings = Nil;
    best_increment_per_ruling = Nil;
    try_for_more_rulings_qm = Nil;
  next_loop:
    increment_per_ruling = expt(float_constant_7,k);
    quotient = divide(range,increment_per_ruling);
    if (NUM_GT(quotient,float_constant_7))
	k = add1(k);
    else if (NUM_LT(quotient,float_constant_5))
	k = sub1(k);
    else {
      next_loop_1:
	low_ruling = ltimes(lfloor(divide(lfloat(low_value,
		float_constant_1),increment_per_ruling),_),
		increment_per_ruling);
	high_ruling = ltimes(ceiling(divide(lfloat(high_value,
		float_constant_1),increment_per_ruling),_),
		increment_per_ruling);
	number_of_rulings = 
		FIXNUM_ADD1(l_round(divide(lfloat(minus(high_ruling,
		low_ruling),float_constant_1),increment_per_ruling),_));
	temp = FIX((SI_Long)4L);
	if (NUM_LT(number_of_rulings,temp))
	    k = sub1(k);
	else {
	    temp = FIX((SI_Long)7L);
	    if (NUM_LE(number_of_rulings,temp)) {
		best_low_ruling = low_ruling;
		best_high_ruling = high_ruling;
		best_number_of_rulings = number_of_rulings;
		best_increment_per_ruling = increment_per_ruling;
		if (IFIX(number_of_rulings) == (SI_Long)7L)
		    goto end_1;
		else {
		    try_for_more_rulings_qm = T;
		    if (NUM_EQ(l,float_constant_6)) {
			k = sub1(k);
			l = float_constant_8;
		    }
		    else if (NUM_EQ(l,float_constant_3))
			l = float_constant_6;
		    else
			l = float_constant_3;
		}
	    }
	    else if (try_for_more_rulings_qm)
		goto end_1;
	    else if (NUM_EQ(l,float_constant_6))
		l = float_constant_3;
	    else if (NUM_EQ(l,float_constant_3))
		l = float_constant_8;
	    else
		error((SI_Long)1L,"Couldn\'t determine rulings~%");
	}
	increment_per_ruling = ltimes(expt(float_constant_7,k),l);
	goto next_loop_1;
      end_loop:
      end_1:
	goto end_2;
    }
    goto next_loop;
  end_loop_1:
  end_2:
    return VALUES_4(best_low_ruling,best_high_ruling,
	    best_number_of_rulings,best_increment_per_ruling);
}

/* DETERMINE-RULING-FOR-TIME-AXIS */
Object determine_ruling_for_time_axis(low_value,high_value,
	    desired_number_of_grid_lines,minimum_number_of_grid_lines,
	    minimum_interval_between_grid_lines)
    Object low_value, high_value, desired_number_of_grid_lines;
    Object minimum_number_of_grid_lines, minimum_interval_between_grid_lines;
{
    Object range, low_ruling, high_ruling, number_of_rulings;
    Object increment_per_ruling, label_scale, temp, second_1, minute, hour;
    Object date, offset_for_low_ruling;
    SI_Long seconds_since_beginning_of_day;
    SI_Long days_since_beginning_of_month_in_seconds;
    double temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,46);
    low_value = lfloor(low_value,_);
    high_value = ceiling(high_value,_);
    range = minus(high_value,low_value);
    low_ruling = Nil;
    high_ruling = Nil;
    number_of_rulings = Nil;
    increment_per_ruling = Nil;
    label_scale = Nil;
    temp = FIX((SI_Long)5L);
    if (NUM_LE(range,temp)) {
	increment_per_ruling = FIX((SI_Long)1L);
	label_scale = FIX((SI_Long)60L);
    }
    else {
	temp = FIX((SI_Long)10L);
	if (NUM_LE(range,temp)) {
	    increment_per_ruling = FIX((SI_Long)2L);
	    label_scale = FIX((SI_Long)60L);
	}
	else {
	    temp = FIX((SI_Long)20L);
	    if (NUM_LE(range,temp)) {
		increment_per_ruling = FIX((SI_Long)5L);
		label_scale = FIX((SI_Long)60L);
	    }
	    else {
		temp = FIX((SI_Long)30L);
		if (NUM_LE(range,temp)) {
		    increment_per_ruling = FIX((SI_Long)10L);
		    label_scale = FIX((SI_Long)60L);
		}
		else {
		    temp = FIX((SI_Long)60L);
		    if (NUM_LE(range,temp)) {
			increment_per_ruling = FIX((SI_Long)15L);
			label_scale = FIX((SI_Long)3600L);
		    }
		    else {
			temp = FIX((SI_Long)300L);
			if (NUM_LE(range,temp)) {
			    increment_per_ruling = FIX((SI_Long)60L);
			    label_scale = FIX((SI_Long)3600L);
			}
			else {
			    temp = FIX((SI_Long)600L);
			    if (NUM_LE(range,temp)) {
				increment_per_ruling = FIX((SI_Long)120L);
				label_scale = FIX((SI_Long)3600L);
			    }
			    else {
				temp = FIX((SI_Long)1800L);
				if (NUM_LE(range,temp)) {
				    increment_per_ruling = FIX((SI_Long)600L);
				    label_scale = FIX((SI_Long)3600L);
				}
				else {
				    temp = FIX((SI_Long)3600L);
				    if (NUM_LE(range,temp)) {
					increment_per_ruling = 
						FIX((SI_Long)1200L);
					label_scale = FIX((SI_Long)86400L);
				    }
				    else {
					temp = FIX((SI_Long)10800L);
					if (NUM_LE(range,temp)) {
					    increment_per_ruling = 
						    FIX((SI_Long)3600L);
					    label_scale = FIX((SI_Long)86400L);
					}
					else {
					    temp = FIX((SI_Long)21600L);
					    if (NUM_LE(range,temp)) {
						increment_per_ruling = 
							FIX((SI_Long)7200L);
						label_scale = 
							FIX((SI_Long)86400L);
					    }
					    else {
						temp = FIX((SI_Long)43200L);
						if (NUM_LE(range,temp)) {
						    increment_per_ruling = 
							    FIX((SI_Long)10800L);
						    label_scale = 
							    FIX((SI_Long)86400L);
						}
						else {
						    temp = 
							    FIX((SI_Long)64800L);
						    if (NUM_LE(range,temp)) {
							increment_per_ruling 
								= 
								FIX((SI_Long)43200L);
							label_scale = 
								FIX((SI_Long)259200L);
						    }
						    else {
							temp = 
								FIX((SI_Long)172800L);
							if (NUM_LE(range,
								    temp)) {
							    increment_per_ruling 
								    = 
								    FIX((SI_Long)86400L);
							    label_scale = 
								    FIX((SI_Long)2419200L);
							}
							else {
							    temp = 
								    FIX((SI_Long)518400L);
							    if (NUM_LE(range,
								    temp)) {
								increment_per_ruling 
									= 
									FIX((SI_Long)172800L);
								label_scale 
									= 
									FIX((SI_Long)2419200L);
							    }
							    else {
								temp = 
									FIX((SI_Long)864000L);
								if (NUM_LE(range,
									temp)) 
									    {
								    increment_per_ruling 
									    = 
									    FIX((SI_Long)259200L);
								    label_scale 
									    = 
									    FIX((SI_Long)2419200L);
								}
								else {
								    temp = 
									    FIX((SI_Long)1814400L);
								    if (NUM_LE(range,
									    temp)) 
										{
									increment_per_ruling 
										= 
										FIX((SI_Long)518400L);
									label_scale 
										= 
										FIX((SI_Long)2419200L);
								    }
								    else {
									temp 
										= 
										FIX((SI_Long)4233600L);
									if (NUM_LE(range,
										temp)) 
										    {
									    increment_per_ruling 
										    = 
										    FIX((SI_Long)1209600L);
									    label_scale 
										    = 
										    FIX((SI_Long)2419200L);
									}
									else {
									    temp 
										    = 
										    FIX((SI_Long)4838400L);
									    if (NUM_LE(range,
										    temp)) 
											{
										increment_per_ruling 
											= 
											FIX((SI_Long)1814400L);
										label_scale 
											= 
											FIX((SI_Long)2419200L);
									    }
									    else {
										temp 
											= 
											FIX((SI_Long)9676800L);
										if (NUM_LE(range,
											temp))
										    increment_per_ruling 
											    = 
											    FIX((SI_Long)2419200L);
										else {
										    temp 
											    = 
											    FIX((SI_Long)19353600L);
										    if (NUM_LE(range,
											    temp))
											increment_per_ruling 
												= 
												FIX((SI_Long)4838400L);
										    else {
											range 
												= 
												FIX((SI_Long)19353600L);
											increment_per_ruling 
												= 
												FIX((SI_Long)4838400L);
											low_value 
												= 
												minus(high_value,
												range);
										    }
										}
									    }
									}
								    }
								}
							    }
							}
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = decode_gensym_time(FIXNUM_ADD(low_value,
		Gensym_time_at_start));
	MVS_4(result,second_1,minute,hour,date);
	seconds_since_beginning_of_day = IFIX(second_1) + (SI_Long)60L * 
		IFIX(minute) + (SI_Long)3600L * IFIX(hour);
	days_since_beginning_of_month_in_seconds = IFIX(date) * 
		(SI_Long)86400L;
	offset_for_low_ruling = Nil;
	temp = FIX((SI_Long)86400L);
	if (NUM_LT(increment_per_ruling,temp)) {
	    temp = lfloat(increment_per_ruling,float_constant_1);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    offset_for_low_ruling = 
		    minus(FIX(seconds_since_beginning_of_day),
		    ltimes(lfloor(DOUBLE_TO_DOUBLE_FLOAT((double)
		    ((float)seconds_since_beginning_of_day) / temp_1),_),
		    increment_per_ruling));
	}
	else {
	    temp = FIX((SI_Long)2419200L);
	    if (NUM_LT(increment_per_ruling,temp))
		offset_for_low_ruling = FIX(seconds_since_beginning_of_day);
	    else
		offset_for_low_ruling = FIX(seconds_since_beginning_of_day 
			+ days_since_beginning_of_month_in_seconds);
	}
	low_ruling = l_round(minus(low_value,offset_for_low_ruling),_);
    }
    POP_LOCAL_ALLOCATION(0,0);
    number_of_rulings = FIXNUM_ADD1(ceiling(divide(lfloat(minus(high_value,
	    low_ruling),float_constant_1),increment_per_ruling),_));
    high_ruling = FIXNUM_ADD(low_ruling,
	    FIXNUM_TIMES(FIXNUM_SUB1(number_of_rulings),increment_per_ruling));
    if (NUM_LT(number_of_rulings,minimum_number_of_grid_lines)) {
	high_ruling = add(high_ruling,ltimes(increment_per_ruling,
		minus(minimum_number_of_grid_lines,number_of_rulings)));
	number_of_rulings = minimum_number_of_grid_lines;
    }
    return VALUES_5(low_ruling,high_ruling,number_of_rulings,
	    increment_per_ruling,label_scale);
}

/* COERCE-MANAGED-FLOAT-OR-FIXNUM-TO-GENSYM-FLOAT */
Object coerce_managed_float_or_fixnum_to_gensym_float(managed_float_or_fixnum)
    Object managed_float_or_fixnum;
{
    x_note_fn_call(173,47);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_float_or_fixnum) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_float_or_fixnum)) == 
	    (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_float_or_fixnum,
		(SI_Long)0L)));
    else
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(managed_float_or_fixnum)));
}

/* MUTATE-PLOT-MIN-GIVEN-PLOT-MIN-AND-MAX */
Object mutate_plot_min_given_plot_min_and_max(plot_min_and_max)
    Object plot_min_and_max;
{
    Object aref_arg_1, slot_value_number, temp;
    double aref_new_value;

    x_note_fn_call(173,48);
    aref_arg_1 = Plot_min_qm;
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
    temp = coerce_managed_float_or_fixnum_to_gensym_float(temp);
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    return VALUES_1(Nil);
}

/* MUTATE-PLOT-MAX-GIVEN-PLOT-MIN-AND-MAX */
Object mutate_plot_max_given_plot_min_and_max(plot_min_and_max)
    Object plot_min_and_max;
{
    Object aref_arg_1, slot_value_number, temp;
    double aref_new_value;

    x_note_fn_call(173,49);
    aref_arg_1 = Plot_max_qm;
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
    temp = coerce_managed_float_or_fixnum_to_gensym_float(temp);
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    return VALUES_1(Nil);
}

static Object Qfloat_array;        /* float-array */

/* STORE-MIN-AND-MAX-PLOT-DATA-POINTS */
Object store_min_and_max_plot_data_points(data_buffer_for_plot,min_y,max_y,
	    x_value_on_graph,most_recent_extremum_maximum_for_pixel_p)
    Object data_buffer_for_plot, min_y, max_y, x_value_on_graph;
    Object most_recent_extremum_maximum_for_pixel_p;
{
    Object elt_1_of_parallel_vector_values, index_1, temp, vector_1, index_2;
    Object value, current_element, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float, ring_buffer;
    Object oldest_active_element_index_for_ring_buffer;
    SI_Long temp_3;
    double aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(173,50);
    PUSH_SPECIAL_WITH_SYMBOL(Most_recent_extremum_maximum_for_pixel_p,Qmost_recent_extremum_maximum_for_pixel_p,most_recent_extremum_maximum_for_pixel_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(X_value_on_graph,Qx_value_on_graph,x_value_on_graph,
	      0);
	elt_1_of_parallel_vector_values = 
		Most_recent_extremum_maximum_for_pixel_p ? min_y : max_y;
	if (ISVREF(data_buffer_for_plot,(SI_Long)3L)) {
	    index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	    SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = elt_1_of_parallel_vector_values;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    SVREF(data_buffer_for_plot,FIX((SI_Long)3L)) = Nil;
	}
	else {
	    ring_buffer = data_buffer_for_plot;
	    index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(ring_buffer,(SI_Long)2L);
	    if (FIXNUM_EQ(FIXNUM_GE(index_2,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)),
		    ISVREF(data_buffer_for_plot,(SI_Long)4L)))
		expand_plot_data_ring_buffer(data_buffer_for_plot);
	    index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    ring_buffer = data_buffer_for_plot;
	    temp_3 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		    (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	    ISVREF(data_buffer_for_plot,(SI_Long)1L) = FIX(temp_3);
	    index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	    SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = elt_1_of_parallel_vector_values;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	}
	elt_1_of_parallel_vector_values = 
		Most_recent_extremum_maximum_for_pixel_p ? max_y : min_y;
	if (ISVREF(data_buffer_for_plot,(SI_Long)3L)) {
	    index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	    SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = elt_1_of_parallel_vector_values;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    result = VALUES_1(SVREF(data_buffer_for_plot,FIX((SI_Long)3L)) 
		    = Nil);
	}
	else {
	    ring_buffer = data_buffer_for_plot;
	    index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(ring_buffer,(SI_Long)2L);
	    if (FIXNUM_EQ(FIXNUM_GE(index_2,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)),
		    ISVREF(data_buffer_for_plot,(SI_Long)4L)))
		expand_plot_data_ring_buffer(data_buffer_for_plot);
	    index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    ring_buffer = data_buffer_for_plot;
	    temp_3 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		    (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	    ISVREF(data_buffer_for_plot,(SI_Long)1L) = FIX(temp_3);
	    index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	    temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	    SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp) = new_float;
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp,temp_3) = new_float;
	    }
	    vector_1 = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = elt_1_of_parallel_vector_values;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
		result = VALUES_1(Nil);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		result = VALUES_1(SVREF(vector_1,temp) = new_float);
	    }
	    else {
		temp = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_3 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		result = VALUES_1(ISVREF(temp,temp_3) = new_float);
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* STORE-NEW-ELEMENT-IN-PLOT-FUNCTION */
Object store_new_element_in_plot_function(data_buffer_for_plot,
	    expansion_function,plot_x_value,plot_y_value)
    Object data_buffer_for_plot, expansion_function, plot_x_value;
    Object plot_y_value;
{
    Object index_1, temp, store_managed_number_or_value_arg, svref_new_value;
    Object svref_arg_2, ring_buffer, index_2;
    Object oldest_active_element_index_for_ring_buffer;
    SI_Long temp_1;

    x_note_fn_call(173,51);
    if (ISVREF(data_buffer_for_plot,(SI_Long)3L)) {
	index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	temp = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	store_managed_number_or_value_arg = plot_x_value;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	}
	else {
	    temp = ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	temp = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	store_managed_number_or_value_arg = plot_y_value;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	}
	else {
	    temp = ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	return VALUES_1(SVREF(data_buffer_for_plot,FIX((SI_Long)3L)) = Nil);
    }
    else {
	ring_buffer = data_buffer_for_plot;
	index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_EQ(FIXNUM_GE(index_2,
		oldest_active_element_index_for_ring_buffer) ? 
		FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		oldest_active_element_index_for_ring_buffer)) : 
		FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		ISVREF(ring_buffer,(SI_Long)4L)),
		oldest_active_element_index_for_ring_buffer)),
		ISVREF(data_buffer_for_plot,(SI_Long)4L)))
	    FUNCALL_1(expansion_function,data_buffer_for_plot);
	index_2 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	ring_buffer = data_buffer_for_plot;
	temp_1 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		(SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	ISVREF(data_buffer_for_plot,(SI_Long)1L) = FIX(temp_1);
	index_1 = ISVREF(data_buffer_for_plot,(SI_Long)1L);
	temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
	SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
	temp = ISVREF(data_buffer_for_plot,(SI_Long)6L);
	store_managed_number_or_value_arg = plot_x_value;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	}
	else {
	    temp = ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value;
	}
	temp = ISVREF(data_buffer_for_plot,(SI_Long)7L);
	store_managed_number_or_value_arg = plot_y_value;
	svref_new_value = 
		store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
		(SI_Long)1L),Maximum_in_place_array_size) ? ISVREF(temp,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),IFIX(index_1) & (SI_Long)1023L),
		store_managed_number_or_value_arg);
	if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	    return VALUES_1(SVREF(temp,svref_arg_2) = svref_new_value);
	}
	else {
	    temp = ISVREF(temp,(IFIX(index_1) >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = IFIX(index_1) & (SI_Long)1023L;
	    return VALUES_1(ISVREF(temp,temp_1) = svref_new_value);
	}
    }
}

/* STORE-NEW-PLOT-DATA-1 */
Object store_new_plot_data_1(use_simulation_history_qm)
    Object use_simulation_history_qm;
{
    x_note_fn_call(173,52);
    if (Many_more_data_points_than_pixels_qm ? 
	    TRUEP(store_data_to_display_for_more_data_than_pixels_case(use_simulation_history_qm)) 
	    : 
	    TRUEP(store_data_to_display_for_enough_pixels_case(use_simulation_history_qm)))
	return set_up_next_plot_marker_if_appropriate_for_new_plot_data();
    else
	return VALUES_1(Nil);
}

/* SET-UP-NEXT-PLOT-MARKER-IF-APPROPRIATE-FOR-NEW-PLOT-DATA */
Object set_up_next_plot_marker_if_appropriate_for_new_plot_data()
{
    Object x_value_for_last_marker_qm, minimum_interval_for_first_marker, temp;
    Object svref_new_value;
    char temp_2;
    double temp_1, aref_new_value;

    x_note_fn_call(173,53);
    if (Plot_marker_qm) {
	x_value_for_last_marker_qm = ISVREF(Current_data_buffer_for_plot,
		(SI_Long)10L);
	if ( !TRUEP(x_value_for_last_marker_qm)) {
	    minimum_interval_for_first_marker = Nil;
	    temp = Handy_float_1;
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Offset_ratio_for_plot_markers);
	    aref_new_value = (double)IFIX(Interval_between_plot_markers) * 
		    temp_1 * (double)IFIX(Current_plot_number);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    minimum_interval_for_first_marker = 
		    round_for_graphs(Handy_float_1);
	    temp_2 = 
		    FIXNUM_GT(FIXNUM_MINUS(History_time_to_evaluate_display_expression_with,
		    Low_value_for_horizontal_axis),
		    minimum_interval_for_first_marker) ? 
		    FIXNUM_GT(History_time_to_evaluate_display_expression_with,
		    minimum_interval_for_first_marker) : TRUEP(Qnil);
	}
	else
	    temp_2 = 
		    FIXNUM_GT(FIXNUM_MINUS(History_time_to_evaluate_display_expression_with,
		    x_value_for_last_marker_qm),Interval_between_plot_markers);
	if (temp_2) {
	    temp = Current_data_buffer_for_plot;
	    svref_new_value = History_time_to_evaluate_display_expression_with;
	    SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
	    temp = Current_data_buffer_for_plot;
	    svref_new_value = 
		    graph_cons_1(ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)1L),ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)11L));
	    return VALUES_1(SVREF(temp,FIX((SI_Long)11L)) = svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdata_point_number_undefined;  /* data-point-number-undefined */

/* SET-UP-TIME-AND-DATA-AT-CURRENT-INDEX */
Object set_up_time_and_data_at_current_index(use_simulation_history_qm)
    Object use_simulation_history_qm;
{
    Object temp, temp_2, svref_new_value, vector_1, managed_number_or_value;
    char temp_3;
    double temp_1, aref_new_value, value, arg, arg_1;

    x_note_fn_call(173,54);
    temp = get_history_current_time(Current_cascaded_ring_buffer,
	    Current_index,use_simulation_history_qm);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    History_time_to_evaluate_display_expression_with = 
	    LONG_TO_FIXNUM(inline_floor_1(temp_1));
    temp_2 = Ring_buffer_for_history_time;
    svref_new_value = FIXNUM_ADD1(ISVREF(Ring_buffer_for_history_time,
	    (SI_Long)5L));
    SVREF(temp_2,FIX((SI_Long)5L)) = svref_new_value;
    vector_1 = ISVREF(Ring_buffer_for_history_time,(SI_Long)6L);
    if (SIMPLE_VECTOR_P(vector_1) && EQ(ISVREF(vector_1,(SI_Long)0L),
	    Managed_array_unique_marker)) {
	managed_number_or_value = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(vector_1,
		IFIX(FIXNUM_ADD(Current_index,
		Managed_array_index_offset))) : ISVREF(ISVREF(vector_1,
		(IFIX(Current_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(Current_index) & (SI_Long)1023L);
	temp_2 = Data_point_value;
	aref_new_value = 
		INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L ? DFLOAT_ISAREF_1(managed_number_or_value,
		(SI_Long)0L) : (double)IFIX(managed_number_or_value);
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
    }
    else {
	temp_2 = Data_point_value;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(vector_1,
		(IFIX(Current_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
		IFIX(Current_index) & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
    }
    value = DFLOAT_ISAREF_1(Data_point_value,(SI_Long)0L);
    arg = value;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_gensym_float);
    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	arg = value;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_gensym_float);
	temp_3 = arg >= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp_3 = TRUEP(Nil);
    if ( !temp_3) {
	Problems_reformatting_graph_qm = Qdata_point_number_undefined;
	temp_2 = Data_point_value;
	DFLOAT_ISASET_1(temp_2,(SI_Long)0L,0.0);
    }
    Finished_storing_in_plot_data_1_qm = FIXNUM_EQ(Current_index,
	    Index_for_stop_time) ? T : Nil;
    if ( !TRUEP(Finished_storing_in_plot_data_1_qm)) {
	Current_index = FIXNUM_EQ(Current_index,
		FIXNUM_SUB1(ISVREF(Ring_buffer_for_history_time,
		(SI_Long)4L))) ? FIX((SI_Long)0L) : FIXNUM_ADD1(Current_index);
	return VALUES_1(Current_index);
    }
    else
	return VALUES_1(Nil);
}

/* STORE-DATA-TO-DISPLAY-FOR-ENOUGH-PIXELS-CASE */
Object store_data_to_display_for_enough_pixels_case(use_simulation_history_qm)
    Object use_simulation_history_qm;
{
    Object temp_1, temp_2, index_1, vector_1, index_2, value, current_element;
    Object amf_available_array_cons_qm, amf_array, temp_3, amf_result;
    Object new_float, ring_buffer, oldest_active_element_index_for_ring_buffer;
    SI_Long temp_4;
    char first_time_qm, temp;
    double managed_float_value_y_value, arg, arg_1, aref_new_value;

    x_note_fn_call(173,55);
    set_up_time_and_data_at_current_index(use_simulation_history_qm);
    if (Scale_y_data_points_qm) {
	if ( !TRUEP(Low_and_high_values_specified_for_vertical_axis_qm)) {
	    first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
	    managed_float_value_y_value = DFLOAT_ISAREF_1(Data_point_value,
		    (SI_Long)0L);
	    temp = first_time_qm;
	    if (temp);
	    else {
		arg = managed_float_value_y_value;
		arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Minimum_y_value;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
			managed_float_value_y_value);
		Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
	    }
	    temp = first_time_qm;
	    if (temp);
	    else {
		arg = managed_float_value_y_value;
		arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Maximum_y_value;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
			managed_float_value_y_value);
		Most_recent_extremum_maximum_p = T;
	    }
	    Minimum_and_maximum_y_value_set_qm = T;
	}
	if (Scale_y_data_points_qm) {
	    if (Plot_min_and_max_qm) {
		temp_1 = Data_point_value;
		aref_new_value = 
			DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			(SI_Long)0L) + DFLOAT_ISAREF_1(Vertical_axis_range,
			(SI_Long)0L) * ((DFLOAT_ISAREF_1(Data_point_value,
			(SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			(SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			(SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			(SI_Long)0L)));
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    }
	}
	X_value_on_graph = 
		adjust_and_compute_x_value_on_graph(History_time_to_evaluate_display_expression_with,
		Erase_dateline,Current_graph_grid,
		ISVREF(Current_graph_grid,(SI_Long)44L));
	if (Scale_y_data_points_qm)
	    Fixnum_minimum_y_value = 
		    compute_y_value_on_graph_new_with_less_truncation(Data_point_value);
	if ( !TRUEP(X_data_min_set_qm)) {
	    temp_1 = Current_plot;
	    temp_2 = History_time_to_evaluate_display_expression_with;
	    ISVREF(temp_1,(SI_Long)6L) = temp_2;
	    X_data_min_set_qm = T;
	}
	if (ISVREF(Current_data_buffer_for_plot,(SI_Long)3L)) {
	    index_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    temp_1 = Current_data_buffer_for_plot;
	    temp_2 = FIXNUM_ADD1(ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)5L));
	    SVREF(temp_1,FIX((SI_Long)5L)) = temp_2;
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = Fixnum_minimum_y_value;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    temp_1 = Current_data_buffer_for_plot;
	    SVREF(temp_1,FIX((SI_Long)3L)) = Nil;
	}
	else {
	    ring_buffer = Current_data_buffer_for_plot;
	    index_2 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(ring_buffer,(SI_Long)2L);
	    if (FIXNUM_EQ(FIXNUM_GE(index_2,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)),
		    ISVREF(Current_data_buffer_for_plot,(SI_Long)4L)))
		expand_plot_data_ring_buffer(Current_data_buffer_for_plot);
	    temp_1 = Current_data_buffer_for_plot;
	    index_2 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    ring_buffer = Current_data_buffer_for_plot;
	    temp_4 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		    (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	    ISVREF(temp_1,(SI_Long)1L) = FIX(temp_4);
	    index_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    temp_1 = Current_data_buffer_for_plot;
	    temp_2 = FIXNUM_ADD1(ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)5L));
	    SVREF(temp_1,FIX((SI_Long)5L)) = temp_2;
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = Fixnum_minimum_y_value;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	}
    }
    else {
	if ( !TRUEP(Low_and_high_values_specified_for_vertical_axis_qm)) {
	    first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
	    managed_float_value_y_value = DFLOAT_ISAREF_1(Data_point_value,
		    (SI_Long)0L);
	    temp = first_time_qm;
	    if (temp);
	    else {
		arg = managed_float_value_y_value;
		arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Minimum_y_value;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
			managed_float_value_y_value);
		Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
	    }
	    temp = first_time_qm;
	    if (temp);
	    else {
		arg = managed_float_value_y_value;
		arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    if (temp) {
		temp_1 = Maximum_y_value;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
			managed_float_value_y_value);
		Most_recent_extremum_maximum_p = T;
	    }
	    Minimum_and_maximum_y_value_set_qm = T;
	}
	if (Scale_y_data_points_qm) {
	    if (Plot_min_and_max_qm) {
		temp_1 = Data_point_value;
		aref_new_value = 
			DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			(SI_Long)0L) + DFLOAT_ISAREF_1(Vertical_axis_range,
			(SI_Long)0L) * ((DFLOAT_ISAREF_1(Data_point_value,
			(SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			(SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			(SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			(SI_Long)0L)));
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    }
	}
	X_value_on_graph = 
		adjust_and_compute_x_value_on_graph(History_time_to_evaluate_display_expression_with,
		Erase_dateline,Current_graph_grid,
		ISVREF(Current_graph_grid,(SI_Long)44L));
	if (Scale_y_data_points_qm)
	    Data_point_value = 
		    compute_y_value_on_graph_new_with_less_truncation(Data_point_value);
	if ( !TRUEP(X_data_min_set_qm)) {
	    temp_1 = Current_plot;
	    temp_2 = History_time_to_evaluate_display_expression_with;
	    ISVREF(temp_1,(SI_Long)6L) = temp_2;
	    X_data_min_set_qm = T;
	}
	if (ISVREF(Current_data_buffer_for_plot,(SI_Long)3L)) {
	    index_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    temp_1 = Current_data_buffer_for_plot;
	    temp_2 = FIXNUM_ADD1(ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)5L));
	    SVREF(temp_1,FIX((SI_Long)5L)) = temp_2;
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = Data_point_value;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    temp_1 = Current_data_buffer_for_plot;
	    SVREF(temp_1,FIX((SI_Long)3L)) = Nil;
	}
	else {
	    ring_buffer = Current_data_buffer_for_plot;
	    index_2 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    oldest_active_element_index_for_ring_buffer = 
		    ISVREF(ring_buffer,(SI_Long)2L);
	    if (FIXNUM_EQ(FIXNUM_GE(index_2,
		    oldest_active_element_index_for_ring_buffer) ? 
		    FIXNUM_ADD1(FIXNUM_MINUS(index_2,
		    oldest_active_element_index_for_ring_buffer)) : 
		    FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_2,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)),
		    ISVREF(Current_data_buffer_for_plot,(SI_Long)4L)))
		expand_plot_data_ring_buffer(Current_data_buffer_for_plot);
	    temp_1 = Current_data_buffer_for_plot;
	    index_2 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    ring_buffer = Current_data_buffer_for_plot;
	    temp_4 = FIXNUM_EQ(index_2,FIXNUM_SUB1(ISVREF(ring_buffer,
		    (SI_Long)4L))) ? (SI_Long)0L : IFIX(FIXNUM_ADD1(index_2));
	    ISVREF(temp_1,(SI_Long)1L) = FIX(temp_4);
	    index_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)1L);
	    temp_1 = Current_data_buffer_for_plot;
	    temp_2 = FIXNUM_ADD1(ISVREF(Current_data_buffer_for_plot,
		    (SI_Long)5L));
	    SVREF(temp_1,FIX((SI_Long)5L)) = temp_2;
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)6L);
	    index_2 = index_1;
	    value = X_value_on_graph;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	    vector_1 = ISVREF(Current_data_buffer_for_plot,(SI_Long)7L);
	    index_2 = index_1;
	    value = Data_point_value;
	    current_element = FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(vector_1,
		    IFIX(FIXNUM_ADD(index_2,Managed_array_index_offset))) :
		     ISVREF(ISVREF(vector_1,(IFIX(index_2) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),IFIX(index_2) & 
		    (SI_Long)1023L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(current_element) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(current_element)) == 
		    (SI_Long)1L) {
		aref_new_value = INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			(SI_Long)1L ? DFLOAT_ISAREF_1(value,(SI_Long)0L) : 
			(double)IFIX(value);
		DFLOAT_ISASET_1(current_element,(SI_Long)0L,aref_new_value);
	    }
	    else if (FIXNUM_LE(ISVREF(vector_1,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(index_2,Managed_array_index_offset);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		SVREF(vector_1,temp_1) = new_float;
	    }
	    else {
		temp_1 = ISVREF(vector_1,(IFIX(index_2) >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_4 = IFIX(index_2) & (SI_Long)1023L;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
			    (SI_Long)1L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			temp_3 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_2 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_2) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			}
			else {
			    temp_2 = Available_float_array_conses_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
			    temp_2 = Available_float_array_conses_tail_vector;
			    temp_3 = Current_thread_index;
			    SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
		    aref_new_value = DFLOAT_ISAREF_1(value,(SI_Long)0L);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		}
		else
		    new_float = value;
		ISVREF(temp_1,temp_4) = new_float;
	    }
	}
    }
    return VALUES_1(T);
}

/* STORE-DATA-TO-DISPLAY-FOR-MORE-DATA-THAN-PIXELS-CASE */
Object store_data_to_display_for_more_data_than_pixels_case(use_simulation_history_qm)
    Object use_simulation_history_qm;
{
    Object extrema_set_qm, rounded_history_time, temp, svref_new_value;
    char first_time_qm, temp_1;
    double aref_new_value, managed_float_value_y_value, arg, arg_1;

    x_note_fn_call(173,56);
    extrema_set_qm = Nil;
    rounded_history_time = Nil;
  next_loop:
    temp = Last_history_time_for_data_point_on_pixel;
    aref_new_value = DFLOAT_ISAREF_1(History_time_per_pixel,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(Last_history_time_for_data_point_on_pixel,
	    (SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    rounded_history_time = 
	    round_for_graphs(Last_history_time_for_data_point_on_pixel);
  next_loop_1:
    set_up_time_and_data_at_current_index(use_simulation_history_qm);
    if (FIXNUM_GT(History_time_to_evaluate_display_expression_with,
	    rounded_history_time))
	goto end_1;
    first_time_qm =  !TRUEP(extrema_set_qm);
    managed_float_value_y_value = DFLOAT_ISAREF_1(Data_point_value,
	    (SI_Long)0L);
    temp_1 = first_time_qm;
    if (temp_1);
    else {
	arg = managed_float_value_y_value;
	arg_1 = DFLOAT_ISAREF_1(Minimum_y_value_for_pixel,(SI_Long)0L);
	temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_1) {
	temp = Minimum_y_value_for_pixel;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,managed_float_value_y_value);
	Most_recent_extremum_maximum_for_pixel_p = first_time_qm ? T : Nil;
    }
    temp_1 = first_time_qm;
    if (temp_1);
    else {
	arg = managed_float_value_y_value;
	arg_1 = DFLOAT_ISAREF_1(Maximum_y_value_for_pixel,(SI_Long)0L);
	temp_1 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    if (temp_1) {
	temp = Maximum_y_value_for_pixel;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,managed_float_value_y_value);
	Most_recent_extremum_maximum_for_pixel_p = T;
    }
    extrema_set_qm = T;
    if (Finished_storing_in_plot_data_1_qm)
	goto end_loop;
    goto next_loop_1;
  end_loop:
  end_1:
    if (extrema_set_qm) {
	if (Scale_y_data_points_qm) {
	    if ( !TRUEP(Low_and_high_values_specified_for_vertical_axis_qm)) {
		first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
		managed_float_value_y_value = 
			DFLOAT_ISAREF_1(Minimum_y_value_for_pixel,(SI_Long)0L);
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Minimum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
		}
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Maximum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = T;
		}
		first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
		managed_float_value_y_value = 
			DFLOAT_ISAREF_1(Maximum_y_value_for_pixel,(SI_Long)0L);
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Minimum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
		}
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Maximum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = T;
		}
		Minimum_and_maximum_y_value_set_qm = T;
	    }
	    if (Scale_y_data_points_qm) {
		if (Plot_min_and_max_qm) {
		    temp = Minimum_y_value_for_pixel;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			    (SI_Long)0L) + 
			    DFLOAT_ISAREF_1(Vertical_axis_range,
			    (SI_Long)0L) * 
			    ((DFLOAT_ISAREF_1(Minimum_y_value_for_pixel,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)));
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		    temp = Maximum_y_value_for_pixel;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			    (SI_Long)0L) + 
			    DFLOAT_ISAREF_1(Vertical_axis_range,
			    (SI_Long)0L) * 
			    ((DFLOAT_ISAREF_1(Maximum_y_value_for_pixel,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)));
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		}
	    }
	    X_value_on_graph = 
		    adjust_and_compute_x_value_on_graph(History_time_to_evaluate_display_expression_with,
		    Erase_dateline,Current_graph_grid,
		    ISVREF(Current_graph_grid,(SI_Long)44L));
	    if (Scale_y_data_points_qm) {
		Fixnum_minimum_y_value = 
			compute_y_value_on_graph_new_with_less_truncation(Minimum_y_value_for_pixel);
		Fixnum_maximum_y_value = 
			compute_y_value_on_graph_new_with_less_truncation(Maximum_y_value_for_pixel);
	    }
	    if ( !TRUEP(X_data_min_set_qm)) {
		temp = Current_plot;
		svref_new_value = 
			History_time_to_evaluate_display_expression_with;
		ISVREF(temp,(SI_Long)6L) = svref_new_value;
		X_data_min_set_qm = T;
	    }
	    store_min_and_max_plot_data_points(Current_data_buffer_for_plot,
		    Fixnum_minimum_y_value,Fixnum_maximum_y_value,
		    X_value_on_graph,Most_recent_extremum_maximum_for_pixel_p);
	}
	else {
	    if ( !TRUEP(Low_and_high_values_specified_for_vertical_axis_qm)) {
		first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
		managed_float_value_y_value = 
			DFLOAT_ISAREF_1(Minimum_y_value_for_pixel,(SI_Long)0L);
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Minimum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
		}
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Maximum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = T;
		}
		first_time_qm =  !TRUEP(Minimum_and_maximum_y_value_set_qm);
		managed_float_value_y_value = 
			DFLOAT_ISAREF_1(Maximum_y_value_for_pixel,(SI_Long)0L);
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Minimum_y_value,(SI_Long)0L);
		    temp_1 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Minimum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = first_time_qm ? T : Nil;
		}
		temp_1 = first_time_qm;
		if (temp_1);
		else {
		    arg = managed_float_value_y_value;
		    arg_1 = DFLOAT_ISAREF_1(Maximum_y_value,(SI_Long)0L);
		    temp_1 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		if (temp_1) {
		    temp = Maximum_y_value;
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,
			    managed_float_value_y_value);
		    Most_recent_extremum_maximum_p = T;
		}
		Minimum_and_maximum_y_value_set_qm = T;
	    }
	    if (Scale_y_data_points_qm) {
		if (Plot_min_and_max_qm) {
		    temp = Minimum_y_value_for_pixel;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			    (SI_Long)0L) + 
			    DFLOAT_ISAREF_1(Vertical_axis_range,
			    (SI_Long)0L) * 
			    ((DFLOAT_ISAREF_1(Minimum_y_value_for_pixel,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)));
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		    temp = Maximum_y_value_for_pixel;
		    aref_new_value = 
			    DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			    (SI_Long)0L) + 
			    DFLOAT_ISAREF_1(Vertical_axis_range,
			    (SI_Long)0L) * 
			    ((DFLOAT_ISAREF_1(Maximum_y_value_for_pixel,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)) / (DFLOAT_ISAREF_1(Plot_max_qm,
			    (SI_Long)0L) - DFLOAT_ISAREF_1(Plot_min_qm,
			    (SI_Long)0L)));
		    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		}
	    }
	    X_value_on_graph = 
		    adjust_and_compute_x_value_on_graph(History_time_to_evaluate_display_expression_with,
		    Erase_dateline,Current_graph_grid,
		    ISVREF(Current_graph_grid,(SI_Long)44L));
	    if (Scale_y_data_points_qm) {
		Minimum_y_value_for_pixel = 
			compute_y_value_on_graph_new_with_less_truncation(Minimum_y_value_for_pixel);
		Maximum_y_value_for_pixel = 
			compute_y_value_on_graph_new_with_less_truncation(Maximum_y_value_for_pixel);
	    }
	    if ( !TRUEP(X_data_min_set_qm)) {
		temp = Current_plot;
		svref_new_value = 
			History_time_to_evaluate_display_expression_with;
		ISVREF(temp,(SI_Long)6L) = svref_new_value;
		X_data_min_set_qm = T;
	    }
	    store_min_and_max_plot_data_points(Current_data_buffer_for_plot,
		    Minimum_y_value_for_pixel,Maximum_y_value_for_pixel,
		    X_value_on_graph,Most_recent_extremum_maximum_for_pixel_p);
	}
	return VALUES_1(T);
    }
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* STORE-NEW-PLOT-DATA-3 */
Object store_new_plot_data_3()
{
    Object svref_arg_1, store_managed_number_or_value_arg, svref_new_value;

    x_note_fn_call(173,57);
    if ( !TRUEP(Low_and_high_values_specified_for_vertical_axis_qm)) {
	if (Most_recent_extremum_maximum_p) {
	    svref_arg_1 = Current_plot;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Maximum_y_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Maximum_y_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(Maximum_y_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = aref1(Maximum_y_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(Maximum_y_value))
		store_managed_number_or_value_arg = 
			copy_text_string(Maximum_y_value);
	    else
		store_managed_number_or_value_arg = Maximum_y_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)8L),store_managed_number_or_value_arg);
	    ISVREF(svref_arg_1,(SI_Long)8L) = svref_new_value;
	    svref_arg_1 = Current_plot;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Minimum_y_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Minimum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Minimum_y_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(Minimum_y_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Minimum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = aref1(Minimum_y_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(Minimum_y_value))
		store_managed_number_or_value_arg = 
			copy_text_string(Minimum_y_value);
	    else
		store_managed_number_or_value_arg = Minimum_y_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)9L),store_managed_number_or_value_arg);
	    return VALUES_1(ISVREF(svref_arg_1,(SI_Long)9L) = svref_new_value);
	}
	else {
	    svref_arg_1 = Current_plot;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Minimum_y_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Minimum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Minimum_y_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(Minimum_y_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Minimum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = aref1(Minimum_y_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(Minimum_y_value))
		store_managed_number_or_value_arg = 
			copy_text_string(Minimum_y_value);
	    else
		store_managed_number_or_value_arg = Minimum_y_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)8L),store_managed_number_or_value_arg);
	    ISVREF(svref_arg_1,(SI_Long)8L) = svref_new_value;
	    svref_arg_1 = Current_plot;
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(Maximum_y_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Maximum_y_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(Maximum_y_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Maximum_y_value)) == 
		    (SI_Long)1L)
		store_managed_number_or_value_arg = aref1(Maximum_y_value,
			FIX((SI_Long)0L));
	    else if (text_string_p(Maximum_y_value))
		store_managed_number_or_value_arg = 
			copy_text_string(Maximum_y_value);
	    else
		store_managed_number_or_value_arg = Maximum_y_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(svref_arg_1,
		    (SI_Long)9L),store_managed_number_or_value_arg);
	    return VALUES_1(ISVREF(svref_arg_1,(SI_Long)9L) = svref_new_value);
	}
    }
    else
	return VALUES_1(Nil);
}

/* STORE-NEW-PLOT-DATA-WITH-SCALING */
Object store_new_plot_data_with_scaling(plot,data_buffer_for_plot,
	    display_expression,
	    display_evaluation_should_use_simulated_values_qm,start_time,
	    newest_time,minimum_time_interval_for_data_points,
	    low_and_high_values_specified_for_vertical_axis_qm_arg,
	    graph_grid,plot_number,low_value_for_horizontal_axis_arg)
    Object plot, data_buffer_for_plot, display_expression;
    Object display_evaluation_should_use_simulated_values_qm, start_time;
    Object newest_time, minimum_time_interval_for_data_points;
    Object low_and_high_values_specified_for_vertical_axis_qm_arg, graph_grid;
    Object plot_number, low_value_for_horizontal_axis_arg;
{
    Object aref_arg_1, temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,58);
    if (T) {
	aref_arg_1 = Vertical_axis_range;
	temp = 
		coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		(SI_Long)37L));
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = Low_value_for_vertical_axis;
	temp = 
		coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		(SI_Long)47L));
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = store_new_plot_data_4(display_expression,graph_grid,
		start_time,plot,newest_time,
		display_evaluation_should_use_simulated_values_qm,
		low_and_high_values_specified_for_vertical_axis_qm_arg,T,
		data_buffer_for_plot,plot_number,
		low_value_for_horizontal_axis_arg);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* STORE-NEW-PLOT-DATA-WITHOUT-SCALING */
Object store_new_plot_data_without_scaling(plot,data_buffer_for_plot,
	    display_expression,
	    display_evaluation_should_use_simulated_values_qm,start_time,
	    newest_time,minimum_time_interval_for_data_points,
	    low_and_high_values_specified_for_vertical_axis_qm_arg,
	    graph_grid,plot_number,low_value_for_horizontal_axis_arg)
    Object plot, data_buffer_for_plot, display_expression;
    Object display_evaluation_should_use_simulated_values_qm, start_time;
    Object newest_time, minimum_time_interval_for_data_points;
    Object low_and_high_values_specified_for_vertical_axis_qm_arg, graph_grid;
    Object plot_number, low_value_for_horizontal_axis_arg;
{
    Object aref_arg_1, temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,59);
    if (Nil) {
	aref_arg_1 = Vertical_axis_range;
	temp = 
		coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		(SI_Long)37L));
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = Low_value_for_vertical_axis;
	temp = 
		coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		(SI_Long)47L));
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = store_new_plot_data_4(display_expression,graph_grid,
		start_time,plot,newest_time,
		display_evaluation_should_use_simulated_values_qm,
		low_and_high_values_specified_for_vertical_axis_qm_arg,Nil,
		data_buffer_for_plot,plot_number,
		low_value_for_horizontal_axis_arg);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* SCALE-Y-DATA-FOR-PLOTS-IF-NECESSARY */
Object scale_y_data_for_plots_if_necessary(graph_grid)
    Object graph_grid;
{
    Object grid_height, plot, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(173,60);
    grid_height = ISVREF(graph_grid,(SI_Long)35L);
    PUSH_SPECIAL_WITH_SYMBOL(Grid_height,Qgrid_height,grid_height,0);
      plot = Nil;
      ab_loop_list_ = ISVREF(graph_grid,(SI_Long)33L);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      plot = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (ISVREF(plot,(SI_Long)10L))
	  scale_y_data_for_plot(plot,graph_grid);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* SCALE-Y-DATA-FOR-PLOT */
Object scale_y_data_for_plot(plot,graph_grid)
    Object plot, graph_grid;
{
    Object data_buffer_for_plot, plot_min_and_max_qm, temp, temp_1, plot_index;
    Object store_managed_number_or_value_arg, svref_new_value, svref_arg_2;
    SI_Long svref_arg_2_1;
    double aref_new_value;
    Declare_special(1);
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(173,61);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	data_buffer_for_plot = ISVREF(plot,(SI_Long)5L);
	if ( !TRUEP(ISVREF(data_buffer_for_plot,(SI_Long)3L))) {
	    plot_min_and_max_qm = plot_min_and_max_given_plot(plot);
	    PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
		    0);
	      temp = Vertical_axis_range;
	      temp_1 = 
		      coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		      (SI_Long)37L));
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	      DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      temp = Low_value_for_vertical_axis;
	      temp_1 = 
		      coerce_managed_float_or_fixnum_to_gensym_float(ISVREF(graph_grid,
		      (SI_Long)47L));
	      aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	      DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      if (Plot_min_and_max_qm) {
		  mutate_plot_min_given_plot_min_and_max(Plot_min_and_max_qm);
		  mutate_plot_max_given_plot_min_and_max(Plot_min_and_max_qm);
	      }
	      plot_index = ISVREF(data_buffer_for_plot,(SI_Long)2L);
	    next_loop:
	      if (Plot_min_and_max_qm) {
		  temp = Data_point_value;
		  aref_new_value = 
			  DFLOAT_ISAREF_1(Low_value_for_vertical_axis,
			  (SI_Long)0L) + 
			  DFLOAT_ISAREF_1(Vertical_axis_range,(SI_Long)0L) 
			  * 
			  ((DFLOAT_ISAREF_1(FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,
			  (SI_Long)7L),(SI_Long)1L),
			  Maximum_in_place_array_size) ? 
			  ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
			  IFIX(FIXNUM_ADD(plot_index,
			  Managed_array_index_offset))) : 
			  ISVREF(ISVREF(ISVREF(data_buffer_for_plot,
			  (SI_Long)7L),(IFIX(plot_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),IFIX(plot_index) & 
			  (SI_Long)1023L),(SI_Long)0L) - 
			  DFLOAT_ISAREF_1(Plot_min_qm,(SI_Long)0L)) / 
			  (DFLOAT_ISAREF_1(Plot_max_qm,(SI_Long)0L) - 
			  DFLOAT_ISAREF_1(Plot_min_qm,(SI_Long)0L)));
		  DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      }
	      else {
		  temp = Data_point_value;
		  temp_1 = 
			  coerce_managed_float_or_fixnum_to_gensym_float(FIXNUM_LE(ISVREF(ISVREF(data_buffer_for_plot,
			  (SI_Long)7L),(SI_Long)1L),
			  Maximum_in_place_array_size) ? 
			  ISVREF(ISVREF(data_buffer_for_plot,(SI_Long)7L),
			  IFIX(FIXNUM_ADD(plot_index,
			  Managed_array_index_offset))) : 
			  ISVREF(ISVREF(ISVREF(data_buffer_for_plot,
			  (SI_Long)7L),(IFIX(plot_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),IFIX(plot_index) & 
			  (SI_Long)1023L));
		  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		  DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	      }
	      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		  temp = FIXNUM_ADD1(ISVREF(data_buffer_for_plot,(SI_Long)5L));
		  SVREF(data_buffer_for_plot,FIX((SI_Long)5L)) = temp;
		  temp = ISVREF(data_buffer_for_plot,(SI_Long)7L);
		  store_managed_number_or_value_arg = 
			  compute_y_value_on_graph_new_with_less_truncation(Data_point_value);
		  svref_new_value = 
			  store_managed_number_or_value_function(FIXNUM_LE(ISVREF(temp,
			  (SI_Long)1L),Maximum_in_place_array_size) ? 
			  ISVREF(temp,IFIX(FIXNUM_ADD(plot_index,
			  Managed_array_index_offset))) : 
			  ISVREF(ISVREF(temp,(IFIX(plot_index) >>  -  - 
			  (SI_Long)10L) + (SI_Long)2L),IFIX(plot_index) & 
			  (SI_Long)1023L),store_managed_number_or_value_arg);
		  if (FIXNUM_LE(ISVREF(temp,(SI_Long)1L),
			  Maximum_in_place_array_size)) {
		      svref_arg_2 = FIXNUM_ADD(plot_index,
			      Managed_array_index_offset);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		  }
		  else {
		      temp = ISVREF(temp,(IFIX(plot_index) >>  -  - 
			      (SI_Long)10L) + (SI_Long)2L);
		      svref_arg_2_1 = IFIX(plot_index) & (SI_Long)1023L;
		      ISVREF(temp,svref_arg_2_1) = svref_new_value;
		  }
	      }
	      POP_LOCAL_ALLOCATION(0,0);
	      if (FIXNUM_EQ(plot_index,ISVREF(data_buffer_for_plot,
		      (SI_Long)1L)))
		  goto end_loop;
	      plot_index = FIXNUM_EQ(plot_index,
		      FIXNUM_SUB1(ISVREF(data_buffer_for_plot,
		      (SI_Long)4L))) ? FIX((SI_Long)0L) : 
		      FIXNUM_ADD1(plot_index);
	      goto next_loop;
	    end_loop:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

static Object float_constant_9;    /* 3.0 */

/* REFRESH-PLOT-DATA-BUFFER */
Object refresh_plot_data_buffer(plot,graph_grid,graph_format,
	    horizontal_axis_grid_format_not_changed_p,plot_number)
    Object plot, graph_grid, graph_format;
    Object horizontal_axis_grid_format_not_changed_p, plot_number;
{
    Object current_block_of_dependent_frame, ring_buffer_shell;
    Object svref_new_value, data_buffer_for_plot, display_expression;
    Object gensymed_symbol, graph;
    Object low_and_high_values_specified_for_vertical_axis_qm_1;
    Object display_evaluation_should_use_simulated_values_qm;
    Object minimum_width_of_data_point, high_value_for_horizontal_axis;
    Object low_value_for_horizontal_axis;
    Object minimum_time_interval_for_data_points, time_of_oldest_data_point;
    Object time_of_newest_data_point, start_time, stop_time;
    Object obsolete_data_boundary_time, grid_width, newest_time, temp, temp_1;
    Object managed_number_or_value, store_managed_number_or_value_arg;
    Declare_special(4);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,62);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_block_of_dependent_frame = graph_grid;
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		3);
	  if ( !TRUEP(ISVREF(plot,(SI_Long)5L))) {
	      ring_buffer_shell = make_plot_data_ring_buffer_1();
	      svref_new_value = allocate_managed_array(1,
		      Smallest_ring_buffer_vector_size);
	      SVREF(ring_buffer_shell,FIX((SI_Long)6L)) = svref_new_value;
	      svref_new_value = allocate_managed_array(1,
		      Smallest_ring_buffer_vector_size);
	      SVREF(ring_buffer_shell,FIX((SI_Long)7L)) = svref_new_value;
	      svref_new_value = Smallest_ring_buffer_vector_size;
	      SVREF(ring_buffer_shell,FIX((SI_Long)4L)) = svref_new_value;
	      data_buffer_for_plot = ISVREF(plot,(SI_Long)5L) = 
		      ring_buffer_shell;
	  }
	  else
	      data_buffer_for_plot = ISVREF(plot,(SI_Long)5L);
	  display_expression = ISVREF(plot,(SI_Long)3L);
	  gensymed_symbol = ACCESS_ONCE(ISVREF(graph_grid,(SI_Long)14L));
	  gensymed_symbol = gensymed_symbol ? 
		  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	  graph = gensymed_symbol;
	  low_and_high_values_specified_for_vertical_axis_qm_1 = 
		  low_and_high_values_specified_for_vertical_axis_qm(graph);
	  PUSH_SPECIAL_WITH_SYMBOL(Low_and_high_values_specified_for_vertical_axis_qm,Qlow_and_high_values_specified_for_vertical_axis_qm,low_and_high_values_specified_for_vertical_axis_qm_1,
		  2);
	    display_evaluation_should_use_simulated_values_qm = 
		    get_lookup_slot_value(graph,
		    Qdisplay_evaluation_should_use_simulated_values_qm);
	    minimum_width_of_data_point = divide(ISVREF(graph_format,
		    (SI_Long)42L),float_constant_9);
	    high_value_for_horizontal_axis = ISVREF(graph_grid,(SI_Long)46L);
	    low_value_for_horizontal_axis = ISVREF(graph_grid,(SI_Long)44L);
	    PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_horizontal_axis,Qlow_value_for_horizontal_axis,low_value_for_horizontal_axis,
		    1);
	      minimum_time_interval_for_data_points = 
		      ltimes(minus(high_value_for_horizontal_axis,
		      Low_value_for_horizontal_axis),
		      divide(lfloat(minimum_width_of_data_point,
		      float_constant_1),Minimum_grid_width));
	      time_of_oldest_data_point = 
		      compute_time_of_oldest_data_point(display_expression,
		      display_evaluation_should_use_simulated_values_qm);
	      time_of_newest_data_point = 
		      compute_time_of_newest_data_point(display_expression,
		      display_evaluation_should_use_simulated_values_qm);
	      minimum_time_interval_for_data_points = 
		      lmax(FIX((SI_Long)1L),
		      l_round(minimum_time_interval_for_data_points,_));
	      if (time_of_oldest_data_point) {
		  if ( !TRUEP(horizontal_axis_grid_format_not_changed_p) 
			  || ISVREF(data_buffer_for_plot,(SI_Long)3L)) {
		      ISVREF(data_buffer_for_plot,(SI_Long)2L) = 
			      FIX((SI_Long)0L);
		      ISVREF(data_buffer_for_plot,(SI_Long)1L) = 
			      FIX((SI_Long)0L);
		      SVREF(data_buffer_for_plot,FIX((SI_Long)3L)) = T;
		      clear_plot_marker_data(data_buffer_for_plot);
		      SVREF(data_buffer_for_plot,FIX((SI_Long)9L)) = Nil;
		      svref_new_value = ISVREF(data_buffer_for_plot,
			      (SI_Long)1L);
		      SVREF(data_buffer_for_plot,FIX((SI_Long)8L)) = 
			      svref_new_value;
		      SVREF(data_buffer_for_plot,FIX((SI_Long)12L)) = Nil;
		      start_time = lmax(Low_value_for_horizontal_axis,
			      time_of_oldest_data_point);
		      stop_time = lmin(high_value_for_horizontal_axis,
			      time_of_newest_data_point);
		      if ( !FIXNUM_GT(start_time,stop_time))
			  store_new_plot_data_without_scaling(plot,
				  data_buffer_for_plot,display_expression,
				  display_evaluation_should_use_simulated_values_qm,
				  start_time,stop_time,
				  minimum_time_interval_for_data_points,
				  Low_and_high_values_specified_for_vertical_axis_qm,
				  graph_grid,plot_number,
				  Low_value_for_horizontal_axis);
		      if ( !TRUEP(ISVREF(data_buffer_for_plot,(SI_Long)3L)))
			  SVREF(data_buffer_for_plot,FIX((SI_Long)12L)) = T;
		      result = VALUES_1(ISVREF(plot,(SI_Long)10L) = T);
		  }
		  else {
		      obsolete_data_boundary_time = 
			      lmax(time_of_oldest_data_point,
			      Low_value_for_horizontal_axis);
		      grid_width = ISVREF(graph_grid,(SI_Long)34L);
		      PUSH_SPECIAL_WITH_SYMBOL(Grid_width,Qgrid_width,grid_width,
			      0);
			newest_time = lmin(high_value_for_horizontal_axis,
				time_of_newest_data_point);
			svref_new_value = ISVREF(data_buffer_for_plot,
				(SI_Long)1L);
			SVREF(data_buffer_for_plot,FIX((SI_Long)2L)) = 
				svref_new_value;
			svref_new_value = ISVREF(data_buffer_for_plot,
				(SI_Long)1L);
			SVREF(data_buffer_for_plot,FIX((SI_Long)8L)) = 
				svref_new_value;
			SVREF(data_buffer_for_plot,FIX((SI_Long)12L)) = Nil;
			reclaim_plot_marker_indices(ISVREF(data_buffer_for_plot,
				(SI_Long)11L));
			SVREF(data_buffer_for_plot,FIX((SI_Long)11L)) = Nil;
			temp = Low_value_for_horizontal_axis;
			if (ISVREF(data_buffer_for_plot,(SI_Long)3L))
			    temp_1 = time_of_oldest_data_point;
			else {
			    managed_number_or_value = ISVREF(plot,(SI_Long)7L);
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
				temp_1 = aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				temp_1 = 
					copy_text_string(managed_number_or_value);
			    else
				temp_1 = managed_number_or_value;
			    temp_1 = lmax(time_of_oldest_data_point,
				    add1(temp_1));
			}
			start_time = lmax(temp,temp_1);
			if ( !NUM_GT(start_time,newest_time))
			    store_new_plot_data_with_scaling(plot,
				    data_buffer_for_plot,
				    display_expression,
				    display_evaluation_should_use_simulated_values_qm,
				    start_time,newest_time,
				    minimum_time_interval_for_data_points,
				    Low_and_high_values_specified_for_vertical_axis_qm,
				    graph_grid,plot_number,
				    Low_value_for_horizontal_axis);
			ISVREF(plot,(SI_Long)10L) = Nil;
			store_managed_number_or_value_arg = 
				obsolete_data_boundary_time;
			svref_new_value = 
				store_managed_number_or_value_function(ISVREF(plot,
				(SI_Long)6L),
				store_managed_number_or_value_arg);
			result = VALUES_1(ISVREF(plot,(SI_Long)6L) = 
				svref_new_value);
		      POP_SPECIAL();
		  }
	      }
	      else
		  result = VALUES_1(Nil);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* LOW-AND-HIGH-VALUES-SPECIFIED-FOR-VERTICAL-AXIS? */
Object low_and_high_values_specified_for_vertical_axis_qm(graph)
    Object graph;
{
    Object parse_var, temp, desired_range_qm;

    x_note_fn_call(173,63);
    parse_var = ISVREF(graph,(SI_Long)24L);
    if (CONSP(parse_var) && EQ(CAR(parse_var),Qwithout_tickmark_labels)) {
	temp = CDR(parse_var);
	desired_range_qm = temp;
    }
    else {
	temp = parse_var;
	desired_range_qm = temp;
    }
    if ( !TRUEP(slot_value_number_p(desired_range_qm)) && 
	    CONSP(desired_range_qm))
	return VALUES_1(EQ(CAR(desired_range_qm),Qsc) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* VARIABLE-HAS-SUBSECOND-HISTORY-P */
Object variable_has_subsecond_history_p(variable,use_simulator_p)
    Object variable, use_simulator_p;
{
    Object sub_class_bit_vector, history_spec_qm, granularity_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(173,64);
    if (use_simulator_p) {
	sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
    history_spec_qm = (temp ? TRUEP(get_lookup_slot_value(variable,
	    Qsimulation_details)) : TRUEP(Nil)) ? 
	    ISVREF(get_lookup_slot_value(variable,Qsimulation_details),
	    (SI_Long)21L) : ISVREF(variable,(SI_Long)25L);
    granularity_qm = history_spec_qm ? CADDDR(history_spec_qm) : Qnil;
    if (granularity_qm)
	return VALUES_1(IFIX(granularity_qm) != (SI_Long)1000L ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant;     /* "The graph expression \"~ND\" evaluated to a variable or parameter with subsecond histories." */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_1;   /* "The graph expression \"~ND\" did not evaluate to a variable or parameter." */

/* GET-VARIABLE-GIVEN-GRAPH-EXPRESSION */
Object get_variable_given_graph_expression(graph_expression,
	    display_evaluation_should_use_simulated_values_qm)
    Object graph_expression, display_evaluation_should_use_simulated_values_qm;
{
    Object variables_that_did_not_have_values, current_computation_flags;
    Object variable_qm, x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(173,65);
    if (System_is_running || System_has_paused) {
	variables_that_did_not_have_values = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
		1);
	  current_computation_flags = Current_computation_flags;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    variable_qm = Nil;
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    variable_qm = evaluate_designation(graph_expression,Nil);
	    if (SIMPLE_VECTOR_P(variable_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(variable_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(variable_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(variable_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (variable_has_subsecond_history_p(variable_qm,
			display_evaluation_should_use_simulated_values_qm)) {
		    if (Redraw_as_well_as_reformat_p) {
			if ((SI_Long)1L <= IFIX(Warning_message_level))
			    give_warning_1(3,FIX((SI_Long)1L),
				    string_constant,graph_expression);
		    }
		    result = VALUES_1(Nil);
		}
		else
		    result = VALUES_1(variable_qm);
	    }
	    else {
		if (SIMPLE_VECTOR_P(variable_qm) && EQ(ISVREF(variable_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		    reclaim_temporary_constant_1(variable_qm);
		if (Redraw_as_well_as_reformat_p &&  
			!TRUEP(Painting_for_graph_activation_p)) {
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)1L),
				string_constant_1,graph_expression);
		}
		result = VALUES_1(Nil);
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-TIME-OF-OLDEST-DATA-POINT */
Object compute_time_of_oldest_data_point(display_expression,
	    display_evaluation_should_use_simulated_values_qm)
    Object display_expression;
    Object display_evaluation_should_use_simulated_values_qm;
{
    Object variable_qm;

    x_note_fn_call(173,66);
    variable_qm = get_variable_given_graph_expression(display_expression,
	    display_evaluation_should_use_simulated_values_qm);
    if (variable_qm)
	return compute_time_of_oldest_data_point_given_variable(variable_qm,
		display_evaluation_should_use_simulated_values_qm);
    else
	return VALUES_1(Nil);
}

/* COMPUTE-TIME-OF-OLDEST-DATA-POINT-GIVEN-VARIABLE */
Object compute_time_of_oldest_data_point_given_variable(variable_or_parameter,
	    display_evaluation_should_use_simulated_values_qm)
    Object variable_or_parameter;
    Object display_evaluation_should_use_simulated_values_qm;
{
    Object sub_class_bit_vector, simulation_subtable_qm;
    Object use_simulation_history_qm, history_buffer_of_stored_values, temp_1;
    Object history_ring_buffer_or_cascade;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double temp_2;

    x_note_fn_call(173,67);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    simulation_subtable_qm = temp ? 
	    get_lookup_slot_value(variable_or_parameter,
	    Qsimulation_details) : Nil;
    if (display_evaluation_should_use_simulated_values_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	use_simulation_history_qm =  !temp ? T : Nil;
    }
    else
	use_simulation_history_qm = Nil;
    history_buffer_of_stored_values = use_simulation_history_qm ? 
	    (simulation_subtable_qm ? ISVREF(simulation_subtable_qm,
	    (SI_Long)20L) : Nil) : ISVREF(variable_or_parameter,(SI_Long)24L);
    if (history_buffer_of_stored_values) {
	temp_1 = ISVREF(history_buffer_of_stored_values,(SI_Long)4L);
	history_ring_buffer_or_cascade = CAR(temp_1);
    }
    else
	history_ring_buffer_or_cascade = Nil;
    if (history_ring_buffer_or_cascade &&  
	    !TRUEP(ISVREF(history_ring_buffer_or_cascade,(SI_Long)3L))) {
	temp_1 = get_history_current_time(history_buffer_of_stored_values,
		ISVREF(history_ring_buffer_or_cascade,(SI_Long)2L),
		use_simulation_history_qm);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(temp_2)));
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-TIME-OF-NEWEST-DATA-POINT */
Object compute_time_of_newest_data_point(display_expression,
	    display_evaluation_should_use_simulated_values_qm)
    Object display_expression;
    Object display_evaluation_should_use_simulated_values_qm;
{
    Object variable_qm;

    x_note_fn_call(173,68);
    variable_qm = get_variable_given_graph_expression(display_expression,
	    display_evaluation_should_use_simulated_values_qm);
    if (variable_qm)
	return compute_time_of_newest_data_point_given_variable(variable_qm,
		display_evaluation_should_use_simulated_values_qm);
    else
	return VALUES_1(Nil);
}

/* COMPUTE-TIME-OF-NEWEST-DATA-POINT-GIVEN-VARIABLE */
Object compute_time_of_newest_data_point_given_variable(variable_or_parameter,
	    display_evaluation_should_use_simulated_values_qm)
    Object variable_or_parameter;
    Object display_evaluation_should_use_simulated_values_qm;
{
    Object sub_class_bit_vector, simulation_subtable_qm;
    Object use_simulation_history_qm, history_buffer_of_stored_values, temp_1;
    Object history_ring_buffer_or_cascade;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double temp_2;

    x_note_fn_call(173,69);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    simulation_subtable_qm = temp ? 
	    get_lookup_slot_value(variable_or_parameter,
	    Qsimulation_details) : Nil;
    if (display_evaluation_should_use_simulated_values_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	use_simulation_history_qm =  !temp ? T : Nil;
    }
    else
	use_simulation_history_qm = Nil;
    history_buffer_of_stored_values = use_simulation_history_qm ? 
	    (simulation_subtable_qm ? ISVREF(simulation_subtable_qm,
	    (SI_Long)20L) : Nil) : ISVREF(variable_or_parameter,(SI_Long)24L);
    if (history_buffer_of_stored_values) {
	temp_1 = ISVREF(history_buffer_of_stored_values,(SI_Long)4L);
	history_ring_buffer_or_cascade = CAR(temp_1);
    }
    else
	history_ring_buffer_or_cascade = Nil;
    if (history_ring_buffer_or_cascade &&  
	    !TRUEP(ISVREF(history_ring_buffer_or_cascade,(SI_Long)3L))) {
	temp_1 = get_history_current_time(history_buffer_of_stored_values,
		ISVREF(history_ring_buffer_or_cascade,(SI_Long)1L),
		use_simulation_history_qm);
	temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	return VALUES_1(LONG_TO_FIXNUM(inline_floor_1(temp_2)));
    }
    else
	return VALUES_1(Nil);
}

static Object Qvariable_or_parameter;  /* variable-or-parameter */

/* GET-VALUE-AT-HISTORY-TIME */
Object get_value_at_history_time(display_expression,history_time,
	    display_evaluation_should_use_simulated_values_qm)
    Object display_expression, history_time;
    Object display_evaluation_should_use_simulated_values_qm;
{
    x_note_fn_call(173,70);
    return get_value_at_history_time_given_variable(get_instance_with_name_if_any(Qvariable_or_parameter,
	    display_expression),history_time,
	    display_evaluation_should_use_simulated_values_qm);
}

/* GET-VALUE-AT-HISTORY-TIME-GIVEN-VARIABLE */
Object get_value_at_history_time_given_variable(variable_or_parameter,
	    history_time,display_evaluation_should_use_simulated_values_qm)
    Object variable_or_parameter, history_time;
    Object display_evaluation_should_use_simulated_values_qm;
{
    Object sub_class_bit_vector, simulation_subtable_qm;
    Object history_buffer_of_stored_values;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(173,71);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    simulation_subtable_qm = temp ? 
	    get_lookup_slot_value(variable_or_parameter,
	    Qsimulation_details) : Nil;
    if (display_evaluation_should_use_simulated_values_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
    history_buffer_of_stored_values = temp ? (simulation_subtable_qm ? 
	    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil) : 
	    ISVREF(variable_or_parameter,(SI_Long)24L);
    if (history_buffer_of_stored_values)
	return get_history_element_using_best_search(history_buffer_of_stored_values,
		history_time,T);
    else
	return VALUES_1(Nil);
}

/* GET-RING-BUFFER-IN-CASCADE-FOR-HISTORY-TIME */
Object get_ring_buffer_in_cascade_for_history_time(cascaded_ring_buffer,
	    history_time)
    Object cascaded_ring_buffer, history_time;
{
    Object temp;

    x_note_fn_call(173,72);
    temp = ISVREF(cascaded_ring_buffer,(SI_Long)4L);
    return VALUES_1(CAR(temp));
}

/* STORE-NEW-PLOT-DATA-4 */
Object store_new_plot_data_4(display_expression,graph_grid,start_time,plot,
	    stop_time,display_evaluation_should_use_simulated_values_qm,
	    low_and_high_values_specified_for_vertical_axis_qm_arg,
	    scale_y_data_points_qm_arg,data_buffer_for_plot,plot_number,
	    low_value_for_horizontal_axis_arg)
    Object display_expression, graph_grid, start_time, plot, stop_time;
    Object display_evaluation_should_use_simulated_values_qm;
    Object low_and_high_values_specified_for_vertical_axis_qm_arg;
    Object scale_y_data_points_qm_arg, data_buffer_for_plot, plot_number;
    Object low_value_for_horizontal_axis_arg;
{
    Object low_and_high_values_specified_for_vertical_axis_qm_1;
    Object scale_y_data_points_qm, low_value_for_horizontal_axis, current_plot;
    Object current_graph_grid, current_data_buffer_for_plot;
    Object current_plot_number, minimum_and_maximum_y_value_set_qm;
    Object fixnum_minimum_y_value, fixnum_maximum_y_value;
    Object most_recent_extremum_maximum_p, variable;
    Object previous_cascaded_ring_buffer_accessed;
    Object previous_index_for_ring_buffer, grid_width, grid_height;
    Object plot_min_and_max_qm;
    Object history_time_to_evaluate_display_expression_with, erase_dateline;
    Object plot_marker_qm, interval_between_plot_markers, x_value_on_graph;
    Object most_recent_extremum_maximum_for_pixel_p, sub_class_bit_vector;
    Object simulation_subtable_qm, use_simulation_history_qm;
    Object history_buffer_of_stored_values, current_cascaded_ring_buffer;
    Object ring_buffer_for_history_time, index_for_start_time;
    Object index_for_stop_time, temp_1, current_index;
    Object many_more_data_points_than_pixels_qm, x_data_min_set_qm;
    Object finished_storing_in_plot_data_1_qm, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    SI_Long start_index_time, stop_index_time;
    SI_Long number_of_datapoints_1, temp_3, number_of_pixels_in_time_range;
    SI_Long store_managed_number_or_value_arg;
    char temp;
    double temp_2, aref_new_value;
    Declare_special(29);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(173,73);
    low_and_high_values_specified_for_vertical_axis_qm_1 = 
	    low_and_high_values_specified_for_vertical_axis_qm_arg;
    PUSH_SPECIAL_WITH_SYMBOL(Low_and_high_values_specified_for_vertical_axis_qm,Qlow_and_high_values_specified_for_vertical_axis_qm,low_and_high_values_specified_for_vertical_axis_qm_1,
	    28);
      scale_y_data_points_qm = scale_y_data_points_qm_arg;
      PUSH_SPECIAL_WITH_SYMBOL(Scale_y_data_points_qm,Qscale_y_data_points_qm,scale_y_data_points_qm,
	      27);
	low_value_for_horizontal_axis = low_value_for_horizontal_axis_arg;
	PUSH_SPECIAL_WITH_SYMBOL(Low_value_for_horizontal_axis,Qlow_value_for_horizontal_axis,low_value_for_horizontal_axis,
		26);
	  current_plot = plot;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_plot,Qcurrent_plot,current_plot,25);
	    current_graph_grid = graph_grid;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_graph_grid,Qcurrent_graph_grid,current_graph_grid,
		    24);
	      current_data_buffer_for_plot = data_buffer_for_plot;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_data_buffer_for_plot,Qcurrent_data_buffer_for_plot,current_data_buffer_for_plot,
		      23);
		current_plot_number = plot_number;
		PUSH_SPECIAL_WITH_SYMBOL(Current_plot_number,Qcurrent_plot_number,current_plot_number,
			22);
		  minimum_and_maximum_y_value_set_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Minimum_and_maximum_y_value_set_qm,Qminimum_and_maximum_y_value_set_qm,minimum_and_maximum_y_value_set_qm,
			  21);
		    fixnum_minimum_y_value = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Fixnum_minimum_y_value,Qfixnum_minimum_y_value,fixnum_minimum_y_value,
			    20);
		      fixnum_maximum_y_value = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_maximum_y_value,Qfixnum_maximum_y_value,fixnum_maximum_y_value,
			      19);
			most_recent_extremum_maximum_p = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Most_recent_extremum_maximum_p,Qmost_recent_extremum_maximum_p,most_recent_extremum_maximum_p,
				18);
			  variable = 
				  get_variable_given_graph_expression(display_expression,
				  display_evaluation_should_use_simulated_values_qm);
			  previous_cascaded_ring_buffer_accessed = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Previous_cascaded_ring_buffer_accessed,Qprevious_cascaded_ring_buffer_accessed,previous_cascaded_ring_buffer_accessed,
				  17);
			    previous_index_for_ring_buffer = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Previous_index_for_ring_buffer,Qprevious_index_for_ring_buffer,previous_index_for_ring_buffer,
				    16);
			      grid_width = ISVREF(graph_grid,(SI_Long)34L);
			      PUSH_SPECIAL_WITH_SYMBOL(Grid_width,Qgrid_width,grid_width,
				      15);
				grid_height = ISVREF(graph_grid,(SI_Long)35L);
				PUSH_SPECIAL_WITH_SYMBOL(Grid_height,Qgrid_height,grid_height,
					14);
				  plot_min_and_max_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Plot_min_and_max_qm,Qplot_min_and_max_qm,plot_min_and_max_qm,
					  13);
				    history_time_to_evaluate_display_expression_with 
					    = start_time;
				    PUSH_SPECIAL_WITH_SYMBOL(History_time_to_evaluate_display_expression_with,Qhistory_time_to_evaluate_display_expression_with,history_time_to_evaluate_display_expression_with,
					    12);
				      erase_dateline = 
					      compute_erase_dateline(graph_grid);
				      PUSH_SPECIAL_WITH_SYMBOL(Erase_dateline,Qerase_dateline,erase_dateline,
					      11);
					plot_marker_qm = 
						plot_marker_given_plot(plot);
					PUSH_SPECIAL_WITH_SYMBOL(Plot_marker_qm,Qplot_marker_qm,plot_marker_qm,
						10);
					  interval_between_plot_markers = 
						  ISVREF(graph_grid,
						  (SI_Long)54L);
					  PUSH_SPECIAL_WITH_SYMBOL(Interval_between_plot_markers,Qinterval_between_plot_markers,interval_between_plot_markers,
						  9);
					    x_value_on_graph = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(X_value_on_graph,Qx_value_on_graph,x_value_on_graph,
						    8);
					      most_recent_extremum_maximum_for_pixel_p 
						      = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Most_recent_extremum_maximum_for_pixel_p,Qmost_recent_extremum_maximum_for_pixel_p,most_recent_extremum_maximum_for_pixel_p,
						      7);
						sub_class_bit_vector = 
							ISVREF(ISVREF(variable,
							(SI_Long)1L),
							(SI_Long)19L);
						superior_class_bit_number 
							= 
							IFIX(ISVREF(Variable_class_description,
							(SI_Long)18L));
						sub_class_vector_index = 
							superior_class_bit_number 
							>>  -  - (SI_Long)3L;
						if (sub_class_vector_index 
							< 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							    {
						    gensymed_symbol = 
							    UBYTE_8_ISAREF_1(sub_class_bit_vector,
							    sub_class_vector_index);
						    gensymed_symbol_1 = 
							    (SI_Long)1L;
						    gensymed_symbol_2 = 
							    superior_class_bit_number 
							    & (SI_Long)7L;
						    gensymed_symbol_1 = 
							    gensymed_symbol_1 
							    << 
							    gensymed_symbol_2;
						    gensymed_symbol = 
							    gensymed_symbol 
							    & 
							    gensymed_symbol_1;
						    temp = (SI_Long)0L < 
							    gensymed_symbol;
						}
						else
						    temp = TRUEP(Nil);
						simulation_subtable_qm = 
							temp ? 
							get_lookup_slot_value(variable,
							Qsimulation_details) 
							: Nil;
						if (display_evaluation_should_use_simulated_values_qm) 
							    {
						    sub_class_bit_vector = 
							    ISVREF(ISVREF(variable,
							    (SI_Long)1L),
							    (SI_Long)19L);
						    superior_class_bit_number 
							    = 
							    IFIX(ISVREF(Parameter_class_description,
							    (SI_Long)18L));
						    sub_class_vector_index 
							    = 
							    superior_class_bit_number 
							    >>  -  - 
							    (SI_Long)3L;
						    if (sub_class_vector_index 
							    < 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								{
							gensymed_symbol = 
								UBYTE_8_ISAREF_1(sub_class_bit_vector,
								sub_class_vector_index);
							gensymed_symbol_1 
								= (SI_Long)1L;
							gensymed_symbol_2 
								= 
								superior_class_bit_number 
								& (SI_Long)7L;
							gensymed_symbol_1 
								= 
								gensymed_symbol_1 
								<< 
								gensymed_symbol_2;
							gensymed_symbol = 
								gensymed_symbol 
								& 
								gensymed_symbol_1;
							temp = (SI_Long)0L 
								< 
								gensymed_symbol;
						    }
						    else
							temp = TRUEP(Nil);
						    use_simulation_history_qm 
							    =  !temp ? T : Nil;
						}
						else
						    use_simulation_history_qm 
							    = Nil;
						history_buffer_of_stored_values 
							= 
							use_simulation_history_qm 
							? 
							(simulation_subtable_qm 
							? 
							ISVREF(simulation_subtable_qm,
							(SI_Long)20L) : 
							Nil) : 
							ISVREF(variable,
							(SI_Long)24L);
						current_cascaded_ring_buffer 
							= 
							history_buffer_of_stored_values;
						PUSH_SPECIAL_WITH_SYMBOL(Current_cascaded_ring_buffer,Qcurrent_cascaded_ring_buffer,current_cascaded_ring_buffer,
							6);
						  ring_buffer_for_history_time 
							  = 
							  get_ring_buffer_in_cascade_for_history_time(history_buffer_of_stored_values,
							  start_time);
						  PUSH_SPECIAL_WITH_SYMBOL(Ring_buffer_for_history_time,Qring_buffer_for_history_time,ring_buffer_for_history_time,
							  5);
						    index_for_start_time = 
							    get_history_index_by_binary_search(history_buffer_of_stored_values,
							    start_time,T);
						    index_for_stop_time = 
							    get_history_index_by_binary_search(history_buffer_of_stored_values,
							    stop_time,T);
						    PUSH_SPECIAL_WITH_SYMBOL(Index_for_stop_time,Qindex_for_stop_time,index_for_stop_time,
							    4);
						      temp_1 = 
							      get_history_current_time(history_buffer_of_stored_values,
							      index_for_start_time,
							      use_simulation_history_qm);
						      temp_2 = 
							      DOUBLE_FLOAT_TO_DOUBLE(temp_1);
						      start_index_time = 
							      inline_floor_1(temp_2);
						      temp_1 = 
							      get_history_current_time(history_buffer_of_stored_values,
							      Index_for_stop_time,
							      use_simulation_history_qm);
						      temp_2 = 
							      DOUBLE_FLOAT_TO_DOUBLE(temp_1);
						      stop_index_time = 
							      inline_floor_1(temp_2);
						      current_index = Nil;
						      PUSH_SPECIAL_WITH_SYMBOL(Current_index,Qcurrent_index,current_index,
							      3);
							number_of_datapoints_1 
								= 
								FIXNUM_GE(Index_for_stop_time,
								index_for_start_time) 
								? 
								IFIX(FIXNUM_ADD1(FIXNUM_MINUS(Index_for_stop_time,
								index_for_start_time))) 
								: 
								IFIX(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(Index_for_stop_time,
								ISVREF(Ring_buffer_for_history_time,
								(SI_Long)4L)),
								index_for_start_time)));
							if (PUSH_LOCAL_ALLOCATION(Local_area,
								0,0)) {
							    temp_1 = 
								    lfloat(ISVREF(graph_grid,
								    (SI_Long)59L),
								    float_constant_1);
							    temp_2 = 
								    DOUBLE_FLOAT_TO_DOUBLE(temp_1);
							    temp_3 = 
								    IFIX(FIXNUM_MINUS(ISVREF(graph_grid,
								    (SI_Long)46L),
								    ISVREF(graph_grid,
								    (SI_Long)44L)));
							    number_of_pixels_in_time_range 
								    = 
								    IFIX(FIXNUM_ADD1(l_round(DOUBLE_TO_DOUBLE_FLOAT(temp_2 
								    * 
								    (double)
								    (stop_index_time 
								    - 
								    start_index_time)),
								    FIX(MAX(temp_3,
								    (SI_Long)1L)))));
							}
							POP_LOCAL_ALLOCATION(0,0);
							many_more_data_points_than_pixels_qm 
								= 
								number_of_datapoints_1 
								> 
								(SI_Long)2L 
								* 
								number_of_pixels_in_time_range 
								? T : Nil;
							PUSH_SPECIAL_WITH_SYMBOL(Many_more_data_points_than_pixels_qm,Qmany_more_data_points_than_pixels_qm,many_more_data_points_than_pixels_qm,
								2);
							  x_data_min_set_qm 
								  = Nil;
							  PUSH_SPECIAL_WITH_SYMBOL(X_data_min_set_qm,Qx_data_min_set_qm,x_data_min_set_qm,
								  1);
							    finished_storing_in_plot_data_1_qm 
								    = Nil;
							    PUSH_SPECIAL_WITH_SYMBOL(Finished_storing_in_plot_data_1_qm,Qfinished_storing_in_plot_data_1_qm,finished_storing_in_plot_data_1_qm,
								    0);
							      if (start_index_time 
								      < 
								      IFIX(start_time) 
								      && 
								      FIXNUM_NE(index_for_start_time,
								      ISVREF(Ring_buffer_for_history_time,
								      (SI_Long)1L)) 
								      && 
								      FIXNUM_NE(Index_for_stop_time,
								      index_for_start_time))
								  index_for_start_time 
									  = 
									  FIXNUM_EQ(index_for_start_time,
									  FIXNUM_SUB1(ISVREF(Ring_buffer_for_history_time,
									  (SI_Long)4L))) 
									  ?
									   
									  FIX((SI_Long)0L) 
									  :
									   
									  FIXNUM_ADD1(index_for_start_time);
							      if (stop_index_time 
								      > 
								      IFIX(stop_time) 
								      && 
								      FIXNUM_NE(Index_for_stop_time,
								      ISVREF(Ring_buffer_for_history_time,
								      (SI_Long)2L)) 
								      && 
								      FIXNUM_NE(Index_for_stop_time,
								      index_for_start_time))
								  Index_for_stop_time 
									  = 
									  IFIX(Index_for_stop_time) 
									  == 
									  (SI_Long)0L 
									  ?
									   
									  FIXNUM_SUB1(ISVREF(Ring_buffer_for_history_time,
									  (SI_Long)4L)) 
									  :
									   
									  FIXNUM_SUB1(Index_for_stop_time);
							      Current_index 
								      = 
								      index_for_start_time;
							      temp_4 = 
								      Last_history_time_for_data_point_on_pixel;
							      aref_new_value 
								      = 
								      (double)IFIX(start_time);
							      DFLOAT_ISASET_1(temp_4,
								      (SI_Long)0L,
								      aref_new_value);
							      if (Many_more_data_points_than_pixels_qm) 
									  {
								  temp_4 = 
									  History_time_per_pixel;
								  aref_new_value 
									  = 
									  (double)IFIX(ISVREF(graph_grid,
									  (SI_Long)60L)) 
									  / 
									  (double)IFIX(ISVREF(graph_grid,
									  (SI_Long)59L));
								  DFLOAT_ISASET_1(temp_4,
									  (SI_Long)0L,
									  aref_new_value);
							      }
							      if (Scale_y_data_points_qm) 
									  {
								  Plot_min_and_max_qm 
									  = 
									  plot_min_and_max_given_plot(plot);
								  if (Plot_min_and_max_qm) 
									      {
								      mutate_plot_min_given_plot_min_and_max(Plot_min_and_max_qm);
								      mutate_plot_max_given_plot_min_and_max(Plot_min_and_max_qm);
								  }
							      }
							    next_loop:
							      store_new_plot_data_1(use_simulation_history_qm);
							      if (Finished_storing_in_plot_data_1_qm)
								  goto end_loop;
							      goto next_loop;
							    end_loop:
							      store_new_plot_data_3();
							      temp_1 = 
								      get_previous_history_time();
							      temp_2 = 
								      DOUBLE_FLOAT_TO_DOUBLE(temp_1);
							      store_managed_number_or_value_arg 
								      = 
								      inline_floor_1(temp_2);
							      temp_4 = 
								      store_managed_number_or_value_function(ISVREF(plot,
								      (SI_Long)7L),
								      LONG_TO_FIXNUM(store_managed_number_or_value_arg));
							      ISVREF(plot,
								      (SI_Long)7L) 
								      = temp_4;
							      result = VALUES_1(Qnil);
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
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object List_of_graph_frame_note_types = UNBOUND;

/* DELETE-ALL-FRAME-NOTES-FOR-GRAPH */
Object delete_all_frame_notes_for_graph(graph)
    Object graph;
{
    Object frame_note_type, ab_loop_list_;

    x_note_fn_call(173,74);
    frame_note_type = Nil;
    ab_loop_list_ = List_of_graph_frame_note_types;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    frame_note_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    delete_frame_note_if_any(frame_note_type,graph);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_2;   /* "There were problems reformatting ~a;  the interval between horizontal grid lines is specified to be 0." */

static Object string_constant_3;   /* "There were problems reformatting ~a;  some of the data points are infinity or are undefined numbers." */

static Object string_constant_4;   /* "There were problems reformatting ~a; see its notes for details." */

/* POST-REFORMAT-WARNING-NOTE-FOR-GRAPH */
Object post_reformat_warning_note_for_graph(graph)
    Object graph;
{
    x_note_fn_call(173,75);
    if (EQ(Problems_reformatting_graph_qm,
	    Qzero_interval_between_horizontal_grid_lines))
	return notify_user(2,string_constant_2,
		get_or_make_up_designation_for_block(graph));
    else if (EQ(Problems_reformatting_graph_qm,Qdata_point_number_undefined))
	return notify_user(2,string_constant_3,
		get_or_make_up_designation_for_block(graph));
    else
	return notify_user(2,string_constant_4,
		get_or_make_up_designation_for_block(graph));
}

static Object array_constant;      /* # */

/* WRITE-PLOT-RANGE-SPECS-WITHOUT-VERTICAL-AXIS-SPEC-NOTE */
Object write_plot_range_specs_without_vertical_axis_spec_note(dummy_for_particulars,
	    gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(173,76);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant,
	    FIX((SI_Long)115L)));
    return VALUES_1(Nil);
}

/* BAD-PLOT-RANGE-SPECS? */
Object bad_plot_range_specs_qm(graph)
    Object graph;
{
    x_note_fn_call(173,77);
    return memq_function(Qplot_range_specs_without_vertical_axis_spec,
	    ISVREF(graph,(SI_Long)8L));
}

static Object array_constant_1;    /* # */

/* WRITE-DESIRED-RANGE-TOO-SMALL-NOTE */
Object write_desired_range_too_small_note(dummy_for_particulars,
	    gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(173,78);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_1,
	    FIX((SI_Long)70L)));
    return VALUES_1(Nil);
}

/* BAD-DESIRED-RANGE-TOO-SMALL? */
Object bad_desired_range_too_small_qm(graph)
    Object graph;
{
    x_note_fn_call(173,79);
    return memq_function(Qdesired_range_too_small,ISVREF(graph,(SI_Long)8L));
}

static Object array_constant_2;    /* # */

/* WRITE-TOO-MANY-GRID-LINES-NOTE */
Object write_too_many_grid_lines_note(dummy_for_particulars,gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(173,80);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_2,
	    FIX((SI_Long)83L)));
    return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

/* WRITE-HORIZONTAL-RANGE-ZERO-NOTE */
Object write_horizontal_range_zero_note(dummy_for_particulars,gensymed_symbol)
    Object dummy_for_particulars, gensymed_symbol;
{
    x_note_fn_call(173,81);
    GENSYM_RETURN_ONE(twrite_beginning_of_wide_string(array_constant_3,
	    FIX((SI_Long)51L)));
    return VALUES_1(Nil);
}

/* BAD-HORIZONTAL-RANGE-ZERO? */
Object bad_horizontal_range_zero_qm(graph)
    Object graph;
{
    x_note_fn_call(173,82);
    return memq_function(Qhorizontal_range_zero,ISVREF(graph,(SI_Long)8L));
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qicon_description;   /* icon-description */

/* PAINT-NUPEC-PLOT-MARKER */
Object paint_nupec_plot_marker(plot_marker_class,x,y,
	    graph_line_color_value,x_scale,y_scale)
    Object plot_marker_class, x, y, graph_line_color_value, x_scale, y_scale;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, icon_description_qm;
    Object current_image_x_scale, current_image_y_scale, icon_rendering;
    Object line_drawing_description, monochrome_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long unshifted_result;
    Declare_special(2);
    Object result;

    x_note_fn_call(173,83);
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
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
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    icon_description_qm = 
	    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
	    gensymed_symbol,Nil),(SI_Long)6L);
    if (icon_description_qm) {
	current_image_x_scale = x_scale;
	current_image_y_scale = y_scale;
	PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
		  0);
	    icon_rendering = 
		    get_or_make_icon_rendering(icon_description_qm,Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	line_drawing_description = ISVREF(icon_rendering,(SI_Long)8L);
	monochrome_qm = 
		single_color_line_drawing_description_p(line_drawing_description);
	if (monochrome_qm) {
	    if (IFIX(x_scale) == (SI_Long)4096L)
		temp_1 = x;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    x_scale) && FIXNUM_LT(x_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,x) && 
		    FIXNUM_LT(x,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(x_scale,x)) + 
			(SI_Long)2048L;
		temp_1 = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp_1 = scalef_function(x_scale,x);
	    if (IFIX(y_scale) == (SI_Long)4096L)
		temp = y;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    y_scale) && FIXNUM_LT(y_scale,
		    Isqrt_of_most_positive_fixnum) && 
		    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,y) && 
		    FIXNUM_LT(y,Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(FIXNUM_TIMES(y_scale,y)) + 
			(SI_Long)2048L;
		temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
	    }
	    else
		temp = scalef_function(y_scale,y);
	    return paint_marker_onto_graph_raster(icon_rendering,temp_1,
		    temp,graph_line_color_value);
	}
	else
	    return VALUES_1(Qt);
    }
    else
	return VALUES_1(Qt);
}

void graphs2_INIT()
{
    Object temp, temp_1;
    Object write_plot_range_specs_without_vertical_axis_spec_note_1;
    Object write_desired_range_too_small_note_1;
    Object write_too_many_grid_lines_note_1;
    Object write_horizontal_range_zero_note_1;
    Object AB_package, Qframe_note_writer_1, list_constant_1, list_constant;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qclasses_which_define, Qresize;
    Object Qresize_for_graph_grid, Qcompute_minimum_bottom_edge;
    Object Qcompute_minimum_bottom_edge_for_graph_grid;
    Object Qcompute_minimum_right_edge;
    Object Qcompute_minimum_right_edge_for_graph_grid, Qdeactivate;
    Object Qdeactivate_for_graph, Qactivate, Qactivate_for_graph;
    Object Qclear_display, Qclear_display_for_graph, Qupdate_display;

    x_note_fn_call(173,84);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qupdate_display_for_graph = STATIC_SYMBOL("UPDATE-DISPLAY-FOR-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_display_for_graph,
	    STATIC_FUNCTION(update_display_for_graph,NIL,FALSE,4,4));
    Qgraph = STATIC_SYMBOL("GRAPH",AB_package);
    Qupdate_display = STATIC_SYMBOL("UPDATE-DISPLAY",AB_package);
    temp = SYMBOL_FUNCTION(Qupdate_display_for_graph);
    set_get(Qgraph,Qupdate_display,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_display),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qupdate_display,temp,Qclasses_which_define);
    Qgraph_reformatted_since_start_qm = 
	    STATIC_SYMBOL("GRAPH-REFORMATTED-SINCE-START\?",AB_package);
    Qclear_display_for_graph = STATIC_SYMBOL("CLEAR-DISPLAY-FOR-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qclear_display_for_graph,
	    STATIC_FUNCTION(clear_display_for_graph,NIL,FALSE,1,1));
    Qclear_display = STATIC_SYMBOL("CLEAR-DISPLAY",AB_package);
    temp = SYMBOL_FUNCTION(Qclear_display_for_graph);
    set_get(Qgraph,Qclear_display,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qclear_display),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qclear_display,temp,Qclasses_which_define);
    if (Painting_for_graph_activation_p == UNBOUND)
	Painting_for_graph_activation_p = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdisplay_wait_interval = STATIC_SYMBOL("DISPLAY-WAIT-INTERVAL",AB_package);
    Qdisplay_update_interval = STATIC_SYMBOL("DISPLAY-UPDATE-INTERVAL",
	    AB_package);
    float_constant = STATIC_FLOAT(-1.0);
    Qdisplay_update_priority = STATIC_SYMBOL("DISPLAY-UPDATE-PRIORITY",
	    AB_package);
    Qactivate_for_graph = STATIC_SYMBOL("ACTIVATE-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_graph,
	    STATIC_FUNCTION(activate_for_graph,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp = SYMBOL_FUNCTION(Qactivate_for_graph);
    set_get(Qgraph,Qactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qactivate,temp,Qclasses_which_define);
    Qdisplay_up_to_date_qm = STATIC_SYMBOL("DISPLAY-UP-TO-DATE\?",AB_package);
    Qthings_this_display_is_interested_in = 
	    STATIC_SYMBOL("THINGS-THIS-DISPLAY-IS-INTERESTED-IN",AB_package);
    Qdeactivate_for_graph = STATIC_SYMBOL("DEACTIVATE-FOR-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_graph,
	    STATIC_FUNCTION(deactivate_for_graph,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp = SYMBOL_FUNCTION(Qdeactivate_for_graph);
    set_get(Qgraph,Qdeactivate,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp = CONS(Qgraph,temp_1);
    mutate_global_property(Qdeactivate,temp,Qclasses_which_define);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qgraph_horizontal_axis_heading_text_cell_format = 
	    STATIC_SYMBOL("GRAPH-HORIZONTAL-AXIS-HEADING-TEXT-CELL-FORMAT",
	    AB_package);
    Qdefault_graph_format = STATIC_SYMBOL("DEFAULT-GRAPH-FORMAT",AB_package);
    Qgraph_format = STATIC_SYMBOL("GRAPH-FORMAT",AB_package);
    Qslot_group_for_block_qm = STATIC_SYMBOL("SLOT-GROUP-FOR-BLOCK\?",
	    AB_package);
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    Qtable_format_for_graphs = STATIC_SYMBOL("TABLE-FORMAT-FOR-GRAPHS",
	    AB_package);
    Qdesired_low_value_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_low_value_for_horizontal_axis,
	    Desired_low_value_for_horizontal_axis);
    Qdesired_high_value_for_horizontal_axis = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-HORIZONTAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_high_value_for_horizontal_axis,
	    Desired_high_value_for_horizontal_axis);
    Qdesired_low_value_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-LOW-VALUE-FOR-VERTICAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_low_value_for_vertical_axis,
	    Desired_low_value_for_vertical_axis);
    Qdesired_high_value_for_vertical_axis = 
	    STATIC_SYMBOL("DESIRED-HIGH-VALUE-FOR-VERTICAL-AXIS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdesired_high_value_for_vertical_axis,
	    Desired_high_value_for_vertical_axis);
    Qlow_value_for_horizontal_grid_lines = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-HORIZONTAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlow_value_for_horizontal_grid_lines,
	    Low_value_for_horizontal_grid_lines);
    Qhigh_value_for_horizontal_grid_lines = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-HORIZONTAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhigh_value_for_horizontal_grid_lines,
	    High_value_for_horizontal_grid_lines);
    Qinterval_between_horizontal_grid_lines = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinterval_between_horizontal_grid_lines,
	    Interval_between_horizontal_grid_lines);
    Qlow_value_for_vertical_grid_lines = 
	    STATIC_SYMBOL("LOW-VALUE-FOR-VERTICAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlow_value_for_vertical_grid_lines,
	    Low_value_for_vertical_grid_lines);
    Qhigh_value_for_vertical_grid_lines = 
	    STATIC_SYMBOL("HIGH-VALUE-FOR-VERTICAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qhigh_value_for_vertical_grid_lines,
	    High_value_for_vertical_grid_lines);
    Qinterval_between_vertical_grid_lines = 
	    STATIC_SYMBOL("INTERVAL-BETWEEN-VERTICAL-GRID-LINES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinterval_between_vertical_grid_lines,
	    Interval_between_vertical_grid_lines);
    if (Changing_graph_margins_qm == UNBOUND)
	Changing_graph_margins_qm = Nil;
    Qgraph_grid = STATIC_SYMBOL("GRAPH-GRID",AB_package);
    Qwithout_tickmark_labels = STATIC_SYMBOL("WITHOUT-TICKMARK-LABELS",
	    AB_package);
    Qhorizontal = STATIC_SYMBOL("HORIZONTAL",AB_package);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Minimum_grid_width_for_resizing_graph = FIX((SI_Long)10L);
    Minimum_grid_height_for_resizing_graph = FIX((SI_Long)10L);
    Qdraw_only_new_data_for_graph_grid = 
	    STATIC_SYMBOL("DRAW-ONLY-NEW-DATA-FOR-GRAPH-GRID",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_only_new_data_for_graph_grid,
	    STATIC_FUNCTION(draw_only_new_data_for_graph_grid,NIL,FALSE,1,1));
    Qdisplay_evaluation_should_use_simulated_values_qm = 
	    STATIC_SYMBOL("DISPLAY-EVALUATION-SHOULD-USE-SIMULATED-VALUES\?",
	    AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    float_constant_1 = STATIC_FLOAT(0.0);
    Qhorizontal_range_zero = STATIC_SYMBOL("HORIZONTAL-RANGE-ZERO",AB_package);
    float_constant_2 = STATIC_FLOAT(100.0);
    Qplot_range_specs_without_vertical_axis_spec = 
	    STATIC_SYMBOL("PLOT-RANGE-SPECS-WITHOUT-VERTICAL-AXIS-SPEC",
	    AB_package);
    float_constant_3 = STATIC_FLOAT(2.0);
    Qdesired_range_too_small = STATIC_SYMBOL("DESIRED-RANGE-TOO-SMALL",
	    AB_package);
    Qbackground_colors = STATIC_SYMBOL("BACKGROUND-COLORS",AB_package);
    Qhorizontal_or_vertical_axis_label_qm = 
	    STATIC_SYMBOL("HORIZONTAL-OR-VERTICAL-AXIS-LABEL\?",AB_package);
    Qdraw_graph_grid_current_time_display = 
	    STATIC_SYMBOL("DRAW-GRAPH-GRID-CURRENT-TIME-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_graph_grid_current_time_display,
	    STATIC_FUNCTION(draw_graph_grid_current_time_display,NIL,FALSE,
	    1,1));
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qlabel_permanent_qm = STATIC_SYMBOL("LABEL-PERMANENT\?",AB_package);
    float_constant_4 = STATIC_FLOAT(0.01);
    float_constant_5 = STATIC_FLOAT(0.1);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qplot = STATIC_SYMBOL("PLOT",AB_package);
    Qdefault_plot_format = STATIC_SYMBOL("DEFAULT-PLOT-FORMAT",AB_package);
    Qcompute_minimum_right_edge_for_graph_grid = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-RIGHT-EDGE-FOR-GRAPH-GRID",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_minimum_right_edge_for_graph_grid,
	    STATIC_FUNCTION(compute_minimum_right_edge_for_graph_grid,NIL,
	    FALSE,1,1));
    Qcompute_minimum_right_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-RIGHT-EDGE",AB_package);
    temp = SYMBOL_FUNCTION(Qcompute_minimum_right_edge_for_graph_grid);
    set_get(Qgraph_grid,Qcompute_minimum_right_edge,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcompute_minimum_right_edge),
	    Qclasses_which_define);
    temp = CONS(Qgraph_grid,temp_1);
    mutate_global_property(Qcompute_minimum_right_edge,temp,
	    Qclasses_which_define);
    Qcompute_minimum_bottom_edge_for_graph_grid = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-BOTTOM-EDGE-FOR-GRAPH-GRID",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_minimum_bottom_edge_for_graph_grid,
	    STATIC_FUNCTION(compute_minimum_bottom_edge_for_graph_grid,NIL,
	    FALSE,1,1));
    Qcompute_minimum_bottom_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-BOTTOM-EDGE",AB_package);
    temp = SYMBOL_FUNCTION(Qcompute_minimum_bottom_edge_for_graph_grid);
    set_get(Qgraph_grid,Qcompute_minimum_bottom_edge,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcompute_minimum_bottom_edge),
	    Qclasses_which_define);
    temp = CONS(Qgraph_grid,temp_1);
    mutate_global_property(Qcompute_minimum_bottom_edge,temp,
	    Qclasses_which_define);
    Qresize_for_graph_grid = STATIC_SYMBOL("RESIZE-FOR-GRAPH-GRID",AB_package);
    SET_SYMBOL_FUNCTION(Qresize_for_graph_grid,
	    STATIC_FUNCTION(resize_for_graph_grid,NIL,FALSE,4,4));
    Qresize = STATIC_SYMBOL("RESIZE",AB_package);
    temp = SYMBOL_FUNCTION(Qresize_for_graph_grid);
    set_get(Qgraph_grid,Qresize,temp);
    temp_1 = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qresize),
	    Qclasses_which_define);
    temp = CONS(Qgraph_grid,temp_1);
    mutate_global_property(Qresize,temp,Qclasses_which_define);
    Qzero_interval_between_horizontal_grid_lines = 
	    STATIC_SYMBOL("ZERO-INTERVAL-BETWEEN-HORIZONTAL-GRID-LINES",
	    AB_package);
    Qtoo_many_grid_lines = STATIC_SYMBOL("TOO-MANY-GRID-LINES",AB_package);
    float_constant_6 = STATIC_FLOAT(1.0);
    float_constant_7 = STATIC_FLOAT(10.0);
    float_constant_8 = STATIC_FLOAT(5.0);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qdata_point_number_undefined = 
	    STATIC_SYMBOL("DATA-POINT-NUMBER-UNDEFINED",AB_package);
    float_constant_9 = STATIC_FLOAT(3.0);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant = 
	    STATIC_STRING("The graph expression \"~ND\" evaluated to a variable or parameter with subsecond histories.");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_1 = 
	    STATIC_STRING("The graph expression \"~ND\" did not evaluate to a variable or parameter.");
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,
	    Qplot_range_specs_without_vertical_axis_spec,
	    Qdesired_range_too_small,Qtoo_many_grid_lines,
	    Qhorizontal_range_zero);
    List_of_graph_frame_note_types = list_constant;
    string_constant_2 = 
	    STATIC_STRING("There were problems reformatting ~a;  the interval between horizontal grid lines is specified to be 0.");
    string_constant_3 = 
	    STATIC_STRING("There were problems reformatting ~a;  some of the data points are infinity or are undefined numbers.");
    string_constant_4 = 
	    STATIC_STRING("There were problems reformatting ~a; see its notes for details.");
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)128L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)42L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)44L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)47L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)48L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)49L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)50L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)51L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)52L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)53L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)54L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)55L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)56L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)57L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)58L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)59L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)60L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)61L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)62L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)63L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)64L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)65L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)66L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)67L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)68L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)69L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)70L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)71L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)72L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)73L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)74L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)75L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)76L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)77L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)78L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)79L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)80L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)81L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)82L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)83L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)84L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)85L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)86L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)87L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)88L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)89L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)90L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)91L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)92L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)93L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)94L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)95L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)96L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)97L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)98L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)99L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)100L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)101L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)102L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)103L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)104L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)105L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)106L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)107L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)108L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)109L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)110L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)111L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)112L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)113L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)114L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)126L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)127L,(SI_Long)57344L);
    write_plot_range_specs_without_vertical_axis_spec_note_1 = 
	    STATIC_FUNCTION(write_plot_range_specs_without_vertical_axis_spec_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qplot_range_specs_without_vertical_axis_spec,
	    write_plot_range_specs_without_vertical_axis_spec_note_1,
	    Qframe_note_writer_1);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)45L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)49L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)51L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)52L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)54L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)55L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)56L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)58L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)59L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)60L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)61L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)62L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)63L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)64L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)65L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)66L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)67L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)68L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)69L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)78L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)79L,(SI_Long)57344L);
    write_desired_range_too_small_note_1 = 
	    STATIC_FUNCTION(write_desired_range_too_small_note,NIL,FALSE,2,2);
    mutate_global_property(Qdesired_range_too_small,
	    write_desired_range_too_small_note_1,Qframe_note_writer_1);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)96L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)44L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)45L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)49L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)51L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)52L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)53L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)56L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)57L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)59L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)60L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)61L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)62L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)63L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)64L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)65L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)66L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)67L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)68L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)69L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)70L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)71L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)72L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)73L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)74L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)75L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)76L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)77L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)78L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)79L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)80L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)81L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)82L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)94L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)95L,(SI_Long)57344L);
    write_too_many_grid_lines_note_1 = 
	    STATIC_FUNCTION(write_too_many_grid_lines_note,NIL,FALSE,2,2);
    mutate_global_property(Qtoo_many_grid_lines,
	    write_too_many_grid_lines_note_1,Qframe_note_writer_1);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)42L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)122L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)49L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)50L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)54L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)55L,(SI_Long)57344L);
    write_horizontal_range_zero_note_1 = 
	    STATIC_FUNCTION(write_horizontal_range_zero_note,NIL,FALSE,2,2);
    mutate_global_property(Qhorizontal_range_zero,
	    write_horizontal_range_zero_note_1,Qframe_note_writer_1);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
}
