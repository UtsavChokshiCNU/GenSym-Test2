/* win3a.c
 * Input file:  windows3a.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "win3a.h"


Object The_type_description_of_graph_rendering = UNBOUND;

Object Chain_of_available_graph_renderings = UNBOUND;

Object Graph_rendering_count = UNBOUND;

/* GRAPH-RENDERING-STRUCTURE-MEMORY-USAGE */
Object graph_rendering_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(53,0);
    temp = Graph_rendering_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)21L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GRAPH-RENDERING-COUNT */
Object outstanding_graph_rendering_count()
{
    Object def_structure_graph_rendering_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(53,1);
    gensymed_symbol = IFIX(Graph_rendering_count);
    def_structure_graph_rendering_variable = 
	    Chain_of_available_graph_renderings;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_graph_rendering_variable))
	goto end_loop;
    def_structure_graph_rendering_variable = 
	    ISVREF(def_structure_graph_rendering_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end;
    gensymed_symbol_1 = IFIX(Qnil);
  end:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GRAPH-RENDERING-1 */
Object reclaim_graph_rendering_1(graph_rendering)
    Object graph_rendering;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(53,2);
    inline_note_reclaim_cons(graph_rendering,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = graph_rendering;
    remove_lru_element(ISVREF(graph_rendering,(SI_Long)1L));
    SVREF(graph_rendering,FIX((SI_Long)1L)) = Nil;
    reclaim_gensym_list_1(ISVREF(graph_rendering,(SI_Long)10L));
    SVREF(graph_rendering,FIX((SI_Long)10L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_graph_renderings;
    SVREF(graph_rendering,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_graph_renderings = graph_rendering;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GRAPH-RENDERING */
Object reclaim_structure_for_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(53,3);
    return reclaim_graph_rendering_1(graph_rendering);
}

static Object Qg2_defstruct_structure_name_graph_rendering_g2_struct;  /* g2-defstruct-structure-name::graph-rendering-g2-struct */

/* MAKE-PERMANENT-GRAPH-RENDERING-STRUCTURE-INTERNAL */
Object make_permanent_graph_rendering_structure_internal()
{
    Object def_structure_graph_rendering_variable, temp;
    Object defstruct_g2_graph_rendering_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(53,4);
    def_structure_graph_rendering_variable = Nil;
    temp = FIXNUM_ADD1(Graph_rendering_count);
    Graph_rendering_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_graph_rendering_variable = Nil;
	gensymed_symbol_1 = (SI_Long)21L;
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
	defstruct_g2_graph_rendering_variable = the_array;
	SVREF(defstruct_g2_graph_rendering_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_rendering_g2_struct;
	SVREF(defstruct_g2_graph_rendering_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_graph_rendering_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_graph_rendering_variable = 
		defstruct_g2_graph_rendering_variable;
	SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)2L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = Chain_of_available_graph_renderings;
	SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)0L)) = temp;
	Chain_of_available_graph_renderings = 
		def_structure_graph_rendering_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_graph_rendering_variable);
}

/* MAKE-GRAPH-RENDERING-INTERNAL-1 */
Object make_graph_rendering_internal_1(line_drawing_description_for_graph_rendering_qm,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_rendered_graph,height_of_rendered_graph,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,
	    corresponding_graph_grid_or_chart_qm,
	    window_for_graph_rendering,graph_rendering_parent_qm)
    Object line_drawing_description_for_graph_rendering_qm;
    Object format_of_graph_rendering_structure, x_scale_of_graph_rendering;
    Object y_scale_of_graph_rendering, grid_border_width;
    Object width_of_rendered_graph, height_of_rendered_graph;
    Object width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure;
    Object corresponding_graph_grid_or_chart_qm, window_for_graph_rendering;
    Object graph_rendering_parent_qm;
{
    Object def_structure_graph_rendering_variable;

    x_note_fn_call(53,5);
    def_structure_graph_rendering_variable = 
	    Chain_of_available_graph_renderings;
    if (def_structure_graph_rendering_variable) {
	Chain_of_available_graph_renderings = 
		ISVREF(def_structure_graph_rendering_variable,(SI_Long)0L);
	SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_graph_rendering_g2_struct;
    }
    else
	def_structure_graph_rendering_variable = 
		make_permanent_graph_rendering_structure_internal();
    inline_note_allocate_cons(def_structure_graph_rendering_variable,Nil);
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)8L)) = 
	    line_drawing_description_for_graph_rendering_qm;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)6L)) = 
	    format_of_graph_rendering_structure;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)3L)) = 
	    x_scale_of_graph_rendering;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)4L)) = 
	    y_scale_of_graph_rendering;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)11L)) = 
	    grid_border_width;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)14L)) = 
	    width_of_rendered_graph;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)15L)) = 
	    height_of_rendered_graph;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)12L)) = 
	    width_of_graph_rendering_structure;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)13L)) = 
	    height_of_graph_rendering_structure;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)16L)) = 
	    corresponding_graph_grid_or_chart_qm;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)17L)) = 
	    window_for_graph_rendering;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)20L)) = 
	    graph_rendering_parent_qm;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_graph_rendering_variable,FIX((SI_Long)19L)) = Nil;
    return VALUES_1(def_structure_graph_rendering_variable);
}

Object Graph_rendering_memory_limit_info = UNBOUND;

Object Graph_rendering_lru_queue = UNBOUND;

/* DECACHE-GRAPH-RENDERING */
Object decache_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    Object size_of_structure, limit_info, svref_new_value;

    x_note_fn_call(53,6);
    size_of_structure = compute_size_of_graph_rendering(graph_rendering);
    limit_info = 
	    get_memory_limit_info_given_size(Graph_rendering_memory_limit_info,
	    size_of_structure);
    if (limit_info) {
	svref_new_value = FIXNUM_MINUS(ISVREF(limit_info,(SI_Long)1L),
		size_of_structure);
	SVREF(limit_info,FIX((SI_Long)1L)) = svref_new_value;
    }
    Decache_occurred_since_last_update_qm = T;
    return delete_graph_rendering_and_reclaim_icp_index(graph_rendering);
}

/* MAKE-GRAPH-RENDERING */
Object make_graph_rendering(line_drawing_description_for_graph_rendering_qm,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_rendered_graph,height_of_rendered_graph,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,
	    corresponding_graph_grid_or_chart_qm,
	    window_for_graph_rendering,frame_serial_number_of_parent_qm)
    Object line_drawing_description_for_graph_rendering_qm;
    Object format_of_graph_rendering_structure, x_scale_of_graph_rendering;
    Object y_scale_of_graph_rendering, grid_border_width;
    Object width_of_rendered_graph, height_of_rendered_graph;
    Object width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure;
    Object corresponding_graph_grid_or_chart_qm, window_for_graph_rendering;
    Object frame_serial_number_of_parent_qm;
{
    x_note_fn_call(53,7);
    return install_lru_element_in_queue(make_graph_rendering_internal_1(line_drawing_description_for_graph_rendering_qm,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_rendered_graph,height_of_rendered_graph,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,
	    corresponding_graph_grid_or_chart_qm,
	    window_for_graph_rendering,frame_serial_number_of_parent_qm),
	    Graph_rendering_lru_queue);
}

static Object list_constant;       /* # */

static Object Qcompute_cost_of_decaching_graph_rendering;  /* compute-cost-of-decaching-graph-rendering */

static Object Qdecache_graph_rendering;  /* decache-graph-rendering */

/* MAKE-DECACHEABLE-GRAPH-RENDERING */
Object make_decacheable_graph_rendering varargs_1(int, n)
{
    Object line_drawing_description_for_graph_rendering_qm;
    Object format_of_graph_rendering_structure, x_scale_of_graph_rendering;
    Object y_scale_of_graph_rendering, grid_border_width;
    Object width_of_rendered_graph, height_of_rendered_graph;
    Object width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure;
    Object corresponding_graph_grid_or_chart_qm, window_for_graph_rendering;
    Object frame_serial_number_of_parent_qm, size;
    Object dont_decache_qm, limit_info, gensymed_symbol, new_structure;
    Object size_of_new_structure, svref_new_value, minimum_size, maximum_size;
    Object queue_head, lru_element_qm, count_1, ab_loop_iter_flag_;
    Object window_for_structure, structure_to_decache_qm;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(53,8);
    INIT_ARGS_nonrelocating();
    line_drawing_description_for_graph_rendering_qm = REQUIRED_ARG_nonrelocating();
    format_of_graph_rendering_structure = REQUIRED_ARG_nonrelocating();
    x_scale_of_graph_rendering = REQUIRED_ARG_nonrelocating();
    y_scale_of_graph_rendering = REQUIRED_ARG_nonrelocating();
    grid_border_width = REQUIRED_ARG_nonrelocating();
    width_of_rendered_graph = REQUIRED_ARG_nonrelocating();
    height_of_rendered_graph = REQUIRED_ARG_nonrelocating();
    width_of_graph_rendering_structure = REQUIRED_ARG_nonrelocating();
    height_of_graph_rendering_structure = REQUIRED_ARG_nonrelocating();
    corresponding_graph_grid_or_chart_qm = REQUIRED_ARG_nonrelocating();
    window_for_graph_rendering = REQUIRED_ARG_nonrelocating();
    frame_serial_number_of_parent_qm = REQUIRED_ARG_nonrelocating();
    size = REQUIRED_ARG_nonrelocating();
    dont_decache_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    limit_info = 
	    get_memory_limit_info_given_size(Graph_rendering_memory_limit_info,
	    size);
    if (dont_decache_qm ||  !TRUEP(limit_info) || 
	    FIXNUM_LT(ISVREF(limit_info,(SI_Long)1L),ISVREF(limit_info,
	    (SI_Long)2L))) {
	gensymed_symbol = limit_info;
	new_structure = 
		make_graph_rendering(line_drawing_description_for_graph_rendering_qm,
		format_of_graph_rendering_structure,
		x_scale_of_graph_rendering,y_scale_of_graph_rendering,
		grid_border_width,width_of_rendered_graph,
		height_of_rendered_graph,
		width_of_graph_rendering_structure,
		height_of_graph_rendering_structure,
		corresponding_graph_grid_or_chart_qm,
		window_for_graph_rendering,frame_serial_number_of_parent_qm);
	size_of_new_structure = compute_size_of_graph_rendering(new_structure);
	if (gensymed_symbol) {
	    svref_new_value = FIXNUM_ADD(ISVREF(gensymed_symbol,
		    (SI_Long)1L),size_of_new_structure);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	}
	return VALUES_1(new_structure);
    }
    else {
	result = get_bracketing_sizes(size,list_constant);
	MVS_2(result,minimum_size,maximum_size);
	if (minimum_size) {
	    queue_head = ISVREF(Graph_rendering_lru_queue,(SI_Long)1L);
	    lru_element_qm =  !EQ(queue_head,Graph_rendering_lru_queue) ? 
		    queue_head : Nil;
	    count_1 = FIX((SI_Long)0L);
	    size = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if ( !TRUEP(lru_element_qm))
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		count_1 = FIXNUM_ADD1(count_1);
	    if (EQ(lru_element_qm,Graph_rendering_lru_queue))
		goto end_loop;
	    size = compute_size_of_graph_rendering(lru_element_qm);
	    if (FIXNUM_GT(size,minimum_size) && FIXNUM_LE(size,maximum_size)) {
		window_for_structure = ISVREF(lru_element_qm,(SI_Long)17L);
		temp =  !TRUEP(printing_window_p(window_for_structure)) ? 
			EQ(window_for_structure,Current_window) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		structure_to_decache_qm = lru_element_qm;
		goto end;
	    }
	    ab_loop_iter_flag_ = Nil;
	    lru_element_qm = ISVREF(lru_element_qm,(SI_Long)1L);
	    goto next_loop;
	  end_loop:
	    structure_to_decache_qm = Qnil;
	  end:;
	}
	else
	    structure_to_decache_qm = Nil;
	if (structure_to_decache_qm)
	    accumulate_thrashing_cost_and_decache(structure_to_decache_qm,
		    limit_info,Qcompute_cost_of_decaching_graph_rendering,
		    Qdecache_graph_rendering);
	gensymed_symbol = limit_info;
	new_structure = 
		make_graph_rendering(line_drawing_description_for_graph_rendering_qm,
		format_of_graph_rendering_structure,
		x_scale_of_graph_rendering,y_scale_of_graph_rendering,
		grid_border_width,width_of_rendered_graph,
		height_of_rendered_graph,
		width_of_graph_rendering_structure,
		height_of_graph_rendering_structure,
		corresponding_graph_grid_or_chart_qm,
		window_for_graph_rendering,frame_serial_number_of_parent_qm);
	size_of_new_structure = compute_size_of_graph_rendering(new_structure);
	if (gensymed_symbol) {
	    svref_new_value = FIXNUM_ADD(ISVREF(gensymed_symbol,
		    (SI_Long)1L),size_of_new_structure);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	}
	return VALUES_1(new_structure);
    }
}

/* COMPUTE-COST-OF-DECACHING-GRAPH-RENDERING */
Object compute_cost_of_decaching_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(53,9);
    if ( !TRUEP(ISVREF(graph_rendering,(SI_Long)16L)))
	return VALUES_1(FIX((SI_Long)0L));
    else
	return VALUES_1(FIX((SI_Long)2000L));
}

/* COMPUTE-SIZE-OF-GRAPH-RENDERING */
Object compute_size_of_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(53,10);
    return compute_size_of_graph_rendering_1(ISVREF(graph_rendering,
	    (SI_Long)12L),ISVREF(graph_rendering,(SI_Long)13L));
}

/* COMPUTE-SIZE-OF-GRAPH-RENDERING-1 */
Object compute_size_of_graph_rendering_1(width,height)
    Object width, height;
{
    x_note_fn_call(53,11);
    return VALUES_1(FIXNUM_MAX(width,height));
}

/* RECLAIM-GRAPH-RENDERING-AND-RASTER-1 */
Object reclaim_graph_rendering_and_raster_1(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(53,12);
    reclaim_graph_rendering_and_raster(graph_rendering);
    return VALUES_1(Nil);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_graph_rendering;  /* establish-new-object-index-for-graph-rendering */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-GRAPH-RENDERING */
Object establish_new_object_index_for_graph_rendering varargs_1(int, n)
{
    Object graph_rendering, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(53,13);
    INIT_ARGS_nonrelocating();
    graph_rendering = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(graph_rendering,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(graph_rendering,(SI_Long)5L)));
	SVREF(graph_rendering,FIX((SI_Long)5L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qestablish_new_object_index_for_graph_rendering,top))
		return icp_error_internal(Qerror,string_constant,
			Qestablish_new_object_index_for_graph_rendering,
			top,Nil);
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(graph_rendering,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(graph_rendering,(SI_Long)5L)));
	SVREF(graph_rendering,FIX((SI_Long)5L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_graph_rendering;  /* make-corresponding-icp-graph-rendering */

/* MAKE-CORRESPONDING-ICP-GRAPH-RENDERING */
Object make_corresponding_icp_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(53,14);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(Writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(graph_rendering,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(graph_rendering,(SI_Long)5L)));
	  SVREF(graph_rendering,FIX((SI_Long)5L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making))
	      send_icp_begin_making_graph_rendering(corresponding_icp_object_index,
		      ISVREF(graph_rendering,(SI_Long)6L),
		      ISVREF(graph_rendering,(SI_Long)3L),
		      ISVREF(graph_rendering,(SI_Long)4L),
		      ISVREF(graph_rendering,(SI_Long)11L),
		      ISVREF(graph_rendering,(SI_Long)12L),
		      ISVREF(graph_rendering,(SI_Long)13L),
		      ISVREF(graph_rendering,(SI_Long)14L),
		      ISVREF(graph_rendering,(SI_Long)15L));
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_graph_rendering,top))
		return icp_error_internal(Qerror,string_constant,
			Qmake_corresponding_icp_graph_rendering,top,Nil);
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    temp = resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(Icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : Nil;
	PUSH_SPECIAL(Writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = resumable_icp_pop();
	  else {
	      result = assign_corresponding_icp_object_index(graph_rendering,
		      Qstandard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = gensym_cons_1(Current_icp_port,
		      gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(graph_rendering,(SI_Long)5L)));
	      SVREF(graph_rendering,FIX((SI_Long)5L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) ||  
		  !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      if (EQ(icp_suspend_1,
		      send_icp_begin_making_graph_rendering(corresponding_icp_object_index,
		      ISVREF(graph_rendering,(SI_Long)6L),
		      ISVREF(graph_rendering,(SI_Long)3L),
		      ISVREF(graph_rendering,(SI_Long)4L),
		      ISVREF(graph_rendering,(SI_Long)11L),
		      ISVREF(graph_rendering,(SI_Long)12L),
		      ISVREF(graph_rendering,(SI_Long)13L),
		      ISVREF(graph_rendering,(SI_Long)14L),
		      ISVREF(graph_rendering,(SI_Long)15L)))) {
		  resumable_icp_push(corresponding_icp_object_index);
		  resumable_icp_push(Writing_resumable_icp_messages_p);
		  resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    resumable_icp_push(graph_rendering);
	    resumable_icp_push(Qmake_corresponding_icp_graph_rendering);
	    return VALUES_1(Icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-GRAPH-RENDERING */
Object get_icp_object_index_for_graph_rendering(graph_rendering,icp_port)
    Object graph_rendering, icp_port;
{
    x_note_fn_call(53,15);
    return getfq_function_no_default(ISVREF(graph_rendering,(SI_Long)5L),
	    icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-GRAPH-RENDERING */
Object set_icp_object_index_for_graph_rendering(graph_rendering,
	    corresponding_icp_object_index,icp_port)
    Object graph_rendering, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(53,16);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(graph_rendering,(SI_Long)5L)));
    return VALUES_1(SVREF(graph_rendering,FIX((SI_Long)5L)) = svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-GRAPH-RENDERING */
Object reclaim_icp_object_map_for_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    Object icp_object_map;

    x_note_fn_call(53,17);
    icp_object_map = ISVREF(graph_rendering,(SI_Long)5L);
    if (icp_object_map)
	return reclaim_icp_object_map(graph_rendering,icp_object_map,
		Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_graph_rendering;  /* set-access-form-for-graph-rendering */

/* RECLAIM-ICP-PORT-ENTRY-FOR-GRAPH-RENDERING */
Object reclaim_icp_port_entry_for_graph_rendering(graph_rendering,icp_port)
    Object graph_rendering, icp_port;
{
    x_note_fn_call(53,18);
    return reclaim_icp_port_entry(icp_port,graph_rendering,
	    ISVREF(graph_rendering,(SI_Long)5L),
	    Qset_access_form_for_graph_rendering);
}

/* SET-ACCESS-FORM-FOR-GRAPH-RENDERING */
Object set_access_form_for_graph_rendering(graph_rendering,new_value)
    Object graph_rendering, new_value;
{
    x_note_fn_call(53,19);
    return VALUES_1(SVREF(graph_rendering,FIX((SI_Long)5L)) = new_value);
}

static Object Qsend_icp_begin_making_graph_rendering;  /* send-icp-begin-making-graph-rendering */

static Object Qcorresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

static Object Qbegin_making_graph_rendering;  /* begin-making-graph-rendering */

static Object string_constant_1;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qcorresponding_icp_object_index;  /* corresponding-icp-object-index */

static Object string_constant_2;   /* "[value arg]" */

static Object Qargument;           /* argument */

static Object Qformat_of_graph_rendering_structure;  /* format-of-graph-rendering-structure */

static Object string_constant_3;   /* "[object arg]" */

static Object Qx_scale_of_graph_rendering;  /* x-scale-of-graph-rendering */

static Object Qy_scale_of_graph_rendering;  /* y-scale-of-graph-rendering */

static Object Qgrid_border_width;  /* grid-border-width */

static Object Qwidth_of_graph_rendering_structure;  /* width-of-graph-rendering-structure */

static Object Qheight_of_graph_rendering_structure;  /* height-of-graph-rendering-structure */

static Object Qwidth_of_rendered_graph;  /* width-of-rendered-graph */

static Object Qheight_of_rendered_graph;  /* height-of-rendered-graph */

/* SEND-ICP-BEGIN-MAKING-GRAPH-RENDERING */
Object send_icp_begin_making_graph_rendering(corresponding_icp_object_index,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,width_of_rendered_graph,
	    height_of_rendered_graph)
    Object corresponding_icp_object_index, format_of_graph_rendering_structure;
    Object x_scale_of_graph_rendering, y_scale_of_graph_rendering;
    Object grid_border_width, width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure, width_of_rendered_graph;
    Object height_of_rendered_graph;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,20);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_begin_making_graph_rendering;
	  }
	  temp_1 = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(format_of_graph_rendering_structure),
		  Qcorresponding_icp_object_map_for_symbol);
	  temp_1 = getfq_function_no_default(temp_1,Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_symbol(format_of_graph_rendering_structure);
	  format_of_graph_rendering_structure = temp_1;
	  start_writing_icp_message(FIX((SI_Long)150L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_making_graph_rendering,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(corresponding_icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(corresponding_icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(format_of_graph_rendering_structure);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qformat_of_graph_rendering_structure,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(format_of_graph_rendering_structure);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(x_scale_of_graph_rendering);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qx_scale_of_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(x_scale_of_graph_rendering);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(y_scale_of_graph_rendering);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qy_scale_of_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(y_scale_of_graph_rendering);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qgrid_border_width,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(grid_border_width);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qgrid_border_width,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(grid_border_width);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(width_of_graph_rendering_structure);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qwidth_of_graph_rendering_structure,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(width_of_graph_rendering_structure);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(height_of_graph_rendering_structure);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qheight_of_graph_rendering_structure,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(height_of_graph_rendering_structure);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(width_of_rendered_graph);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qwidth_of_rendered_graph,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(width_of_rendered_graph);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_integer(height_of_rendered_graph);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qheight_of_rendered_graph,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_integer(height_of_rendered_graph);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_making_graph_rendering,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(corresponding_icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(corresponding_icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(format_of_graph_rendering_structure);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(format_of_graph_rendering_structure);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(x_scale_of_graph_rendering);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(x_scale_of_graph_rendering);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(y_scale_of_graph_rendering);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(y_scale_of_graph_rendering);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qgrid_border_width,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(grid_border_width);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qgrid_border_width,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(grid_border_width);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(width_of_graph_rendering_structure);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(width_of_graph_rendering_structure);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(height_of_graph_rendering_structure);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(height_of_graph_rendering_structure);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(width_of_rendered_graph);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(width_of_rendered_graph);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_integer(height_of_rendered_graph);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(height_of_rendered_graph);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_begin_making_graph_rendering,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_begin_making_graph_rendering,top,Nil);
		goto end_send_icp_begin_making_graph_rendering;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : corresponding_icp_object_index;
	format_of_graph_rendering_structure = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : format_of_graph_rendering_structure;
	x_scale_of_graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : x_scale_of_graph_rendering;
	y_scale_of_graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : y_scale_of_graph_rendering;
	grid_border_width = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : grid_border_width;
	width_of_graph_rendering_structure = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : width_of_graph_rendering_structure;
	height_of_graph_rendering_structure = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : height_of_graph_rendering_structure;
	width_of_rendered_graph = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : width_of_rendered_graph;
	height_of_rendered_graph = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : height_of_rendered_graph;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_begin_making_graph_rendering;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()))
	      value = resumable_icp_pop();
	  else {
	      temp_1 = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(format_of_graph_rendering_structure),
		      Qcorresponding_icp_object_map_for_symbol);
	      value = getfq_function_no_default(temp_1,Current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      format_of_graph_rendering_structure = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_symbol(format_of_graph_rendering_structure);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      format_of_graph_rendering_structure = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)150L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_making_graph_rendering,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3_1;
			    break;
			  case 4:
			    goto l4;
			    break;
			  case 5:
			    goto l5;
			    break;
			  case 6:
			    goto l6;
			    break;
			  case 7:
			    goto l7;
			    break;
			  case 8:
			    goto l8;
			    break;
			  case 9:
			    goto l9;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(corresponding_icp_object_index))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qcorresponding_icp_object_index,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(corresponding_icp_object_index))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(format_of_graph_rendering_structure))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qformat_of_graph_rendering_structure,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(format_of_graph_rendering_structure))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(x_scale_of_graph_rendering))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qx_scale_of_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(x_scale_of_graph_rendering))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(y_scale_of_graph_rendering))) 
				  {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qy_scale_of_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(y_scale_of_graph_rendering))) 
			    {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qgrid_border_width,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(grid_border_width))) {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qgrid_border_width,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(grid_border_width))) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(width_of_graph_rendering_structure))) 
				  {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qwidth_of_graph_rendering_structure,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(width_of_graph_rendering_structure))) 
			    {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l7:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(height_of_graph_rendering_structure))) 
				  {
			  resumable_icp_push(FIX((SI_Long)7L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qheight_of_graph_rendering_structure,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(height_of_graph_rendering_structure))) 
			    {
		    resumable_icp_push(FIX((SI_Long)7L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l8:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(width_of_rendered_graph))) {
			  resumable_icp_push(FIX((SI_Long)8L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qwidth_of_rendered_graph,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(width_of_rendered_graph))) {
		    resumable_icp_push(FIX((SI_Long)8L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l9:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(height_of_rendered_graph))) {
			  resumable_icp_push(FIX((SI_Long)9L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qheight_of_rendered_graph,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_integer(height_of_rendered_graph))) {
		    resumable_icp_push(FIX((SI_Long)9L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_making_graph_rendering,
			    string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_2;
			  break;
			case 4:
			  goto l4_1;
			  break;
			case 5:
			  goto l5_1;
			  break;
			case 6:
			  goto l6_1;
			  break;
			case 7:
			  goto l7_1;
			  break;
			case 8:
			  goto l8_1;
			  break;
			case 9:
			  goto l9_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(corresponding_icp_object_index))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(corresponding_icp_object_index))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(format_of_graph_rendering_structure))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(format_of_graph_rendering_structure))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(x_scale_of_graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(x_scale_of_graph_rendering))) 
			  {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(y_scale_of_graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(y_scale_of_graph_rendering))) 
			  {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qgrid_border_width,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(grid_border_width))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qgrid_border_width,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(grid_border_width))) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(width_of_graph_rendering_structure))) 
				{
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(width_of_graph_rendering_structure))) {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l7_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(height_of_graph_rendering_structure))) 
				{
			resumable_icp_push(FIX((SI_Long)7L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(height_of_graph_rendering_structure))) 
			  {
		  resumable_icp_push(FIX((SI_Long)7L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l8_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(width_of_rendered_graph))) {
			resumable_icp_push(FIX((SI_Long)8L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(width_of_rendered_graph))) {
		  resumable_icp_push(FIX((SI_Long)8L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l9_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_integer(height_of_rendered_graph))) {
			resumable_icp_push(FIX((SI_Long)9L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_integer(height_of_rendered_graph))) {
		  resumable_icp_push(FIX((SI_Long)9L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(height_of_rendered_graph);
	      resumable_icp_push(width_of_rendered_graph);
	      resumable_icp_push(height_of_graph_rendering_structure);
	      resumable_icp_push(width_of_graph_rendering_structure);
	      resumable_icp_push(grid_border_width);
	      resumable_icp_push(y_scale_of_graph_rendering);
	      resumable_icp_push(x_scale_of_graph_rendering);
	      resumable_icp_push(format_of_graph_rendering_structure);
	      resumable_icp_push(corresponding_icp_object_index);
	      resumable_icp_push(Qsend_icp_begin_making_graph_rendering);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_begin_making_graph_rendering;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_begin_making_graph_rendering:
    return result;
}

/* HANDLE-ICP-BEGIN-MAKING-GRAPH-RENDERING--BODY */
Object handle_icp_begin_making_graph_rendering__body(corresponding_icp_object_index,
	    format_of_graph_rendering_structure,x_scale_of_graph_rendering,
	    y_scale_of_graph_rendering,grid_border_width,
	    width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,width_of_rendered_graph,
	    height_of_rendered_graph)
    Object corresponding_icp_object_index, format_of_graph_rendering_structure;
    Object x_scale_of_graph_rendering, y_scale_of_graph_rendering;
    Object grid_border_width, width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure, width_of_rendered_graph;
    Object height_of_rendered_graph;
{
    Object graph_rendering, svref_new_value;

    x_note_fn_call(53,21);
    graph_rendering = 
	    store_corresponding_icp_object(corresponding_icp_object_index,
	    make_graph_rendering(Nil,format_of_graph_rendering_structure,
	    x_scale_of_graph_rendering,y_scale_of_graph_rendering,
	    grid_border_width,width_of_rendered_graph,
	    height_of_rendered_graph,width_of_graph_rendering_structure,
	    height_of_graph_rendering_structure,Nil,Current_window,Nil));
    svref_new_value = 
	    make_graph_rendering_structure(width_of_graph_rendering_structure);
    SVREF(graph_rendering,FIX((SI_Long)7L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qhandle_icp_begin_making_graph_rendering;  /* handle-icp-begin-making-graph-rendering */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-BEGIN-MAKING-GRAPH-RENDERING */
Object handle_icp_begin_making_graph_rendering()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, corresponding_icp_object_index;
    Object index_1, index_space, format_of_graph_rendering_structure;
    Object x_scale_of_graph_rendering, y_scale_of_graph_rendering;
    Object grid_border_width, width_of_graph_rendering_structure;
    Object height_of_graph_rendering_structure, width_of_rendered_graph;
    Object height_of_rendered_graph, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,22);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qbegin_making_graph_rendering,string_constant_1,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  corresponding_icp_object_index = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,T,
				result_of_read,Nil,Nil);
		    format_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      format_of_graph_rendering_structure = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      format_of_graph_rendering_structure = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    x_scale_of_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  x_scale_of_graph_rendering = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    y_scale_of_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  y_scale_of_graph_rendering = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgrid_border_width,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgrid_border_width,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    grid_border_width = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  grid_border_width = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    width_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  width_of_graph_rendering_structure = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    height_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  height_of_graph_rendering_structure = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    width_of_rendered_graph = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  width_of_rendered_graph = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    height_of_rendered_graph = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  height_of_rendered_graph = read_icp_integer();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_begin_making_graph_rendering__body(corresponding_icp_object_index,
			format_of_graph_rendering_structure,
			x_scale_of_graph_rendering,
			y_scale_of_graph_rendering,grid_border_width,
			width_of_graph_rendering_structure,
			height_of_graph_rendering_structure,
			width_of_rendered_graph,height_of_rendered_graph);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qbegin_making_graph_rendering,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else
		corresponding_icp_object_index = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qformat_of_graph_rendering_structure,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,T,result_of_read,
			      Nil,Nil);
		  format_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    format_of_graph_rendering_structure = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    format_of_graph_rendering_structure = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qx_scale_of_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  x_scale_of_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else
		x_scale_of_graph_rendering = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qy_scale_of_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  y_scale_of_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else
		y_scale_of_graph_rendering = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgrid_border_width,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgrid_border_width,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  grid_border_width = result_of_read;
		POP_SPECIAL();
	    }
	    else
		grid_border_width = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qwidth_of_graph_rendering_structure,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  width_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else
		width_of_graph_rendering_structure = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qheight_of_graph_rendering_structure,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  height_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else
		height_of_graph_rendering_structure = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qwidth_of_rendered_graph,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  width_of_rendered_graph = result_of_read;
		POP_SPECIAL();
	    }
	    else
		width_of_rendered_graph = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qheight_of_rendered_graph,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  height_of_rendered_graph = result_of_read;
		POP_SPECIAL();
	    }
	    else
		height_of_rendered_graph = read_icp_integer();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,0);
	      handle_icp_begin_making_graph_rendering__body(corresponding_icp_object_index,
		      format_of_graph_rendering_structure,
		      x_scale_of_graph_rendering,
		      y_scale_of_graph_rendering,grid_border_width,
		      width_of_graph_rendering_structure,
		      height_of_graph_rendering_structure,
		      width_of_rendered_graph,height_of_rendered_graph);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_begin_making_graph_rendering,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_begin_making_graph_rendering,top,Nil);
		goto end_handle_icp_begin_making_graph_rendering;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qbegin_making_graph_rendering,string_constant_1,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcorresponding_icp_object_index,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    corresponding_icp_object_index = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  corresponding_icp_object_index = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  format_of_graph_rendering_structure = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(corresponding_icp_object_index);
			    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_begin_making_graph_rendering;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qformat_of_graph_rendering_structure,
				string_constant_3,Qargument,T,
				result_of_read,Nil,Nil);
		    format_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_begin_making_graph_rendering;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      format_of_graph_rendering_structure = 
			      ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      format_of_graph_rendering_structure = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  x_scale_of_graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qx_scale_of_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    x_scale_of_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  x_scale_of_graph_rendering = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  y_scale_of_graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qy_scale_of_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    y_scale_of_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  y_scale_of_graph_rendering = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  grid_border_width = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgrid_border_width,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(y_scale_of_graph_rendering);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgrid_border_width,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    grid_border_width = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  grid_border_width = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  width_of_graph_rendering_structure = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(grid_border_width);
			resumable_icp_push(y_scale_of_graph_rendering);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwidth_of_graph_rendering_structure,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    width_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  width_of_graph_rendering_structure = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  height_of_graph_rendering_structure = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(width_of_graph_rendering_structure);
			resumable_icp_push(grid_border_width);
			resumable_icp_push(y_scale_of_graph_rendering);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qheight_of_graph_rendering_structure,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    height_of_graph_rendering_structure = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  height_of_graph_rendering_structure = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  width_of_rendered_graph = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(height_of_graph_rendering_structure);
			resumable_icp_push(width_of_graph_rendering_structure);
			resumable_icp_push(grid_border_width);
			resumable_icp_push(y_scale_of_graph_rendering);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qwidth_of_rendered_graph,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    width_of_rendered_graph = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(height_of_graph_rendering_structure);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  width_of_rendered_graph = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  height_of_rendered_graph = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(width_of_rendered_graph);
			resumable_icp_push(height_of_graph_rendering_structure);
			resumable_icp_push(width_of_graph_rendering_structure);
			resumable_icp_push(grid_border_width);
			resumable_icp_push(y_scale_of_graph_rendering);
			resumable_icp_push(x_scale_of_graph_rendering);
			resumable_icp_push(format_of_graph_rendering_structure);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qheight_of_rendered_graph,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    height_of_rendered_graph = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(width_of_rendered_graph);
		      resumable_icp_push(height_of_graph_rendering_structure);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  height_of_rendered_graph = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_begin_making_graph_rendering__body(corresponding_icp_object_index,
			format_of_graph_rendering_structure,
			x_scale_of_graph_rendering,
			y_scale_of_graph_rendering,grid_border_width,
			width_of_graph_rendering_structure,
			height_of_graph_rendering_structure,
			width_of_rendered_graph,height_of_rendered_graph);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qbegin_making_graph_rendering,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcorresponding_icp_object_index,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcorresponding_icp_object_index,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  corresponding_icp_object_index = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		corresponding_icp_object_index = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		format_of_graph_rendering_structure = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qformat_of_graph_rendering_structure,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(corresponding_icp_object_index);
			  resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_begin_making_graph_rendering;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qformat_of_graph_rendering_structure,
			      string_constant_3,Qargument,T,result_of_read,
			      Nil,Nil);
		  format_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(corresponding_icp_object_index);
			resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_begin_making_graph_rendering;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    format_of_graph_rendering_structure = 
			    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			    IFIX(index_1) >>  -  - (SI_Long)10L),
			    IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    format_of_graph_rendering_structure = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		x_scale_of_graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qx_scale_of_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qx_scale_of_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  x_scale_of_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		x_scale_of_graph_rendering = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		y_scale_of_graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qy_scale_of_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qy_scale_of_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  y_scale_of_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		y_scale_of_graph_rendering = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		grid_border_width = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgrid_border_width,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgrid_border_width,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  grid_border_width = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(y_scale_of_graph_rendering);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		grid_border_width = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		width_of_graph_rendering_structure = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qwidth_of_graph_rendering_structure,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwidth_of_graph_rendering_structure,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  width_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(grid_border_width);
		    resumable_icp_push(y_scale_of_graph_rendering);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		width_of_graph_rendering_structure = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		height_of_graph_rendering_structure = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qheight_of_graph_rendering_structure,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qheight_of_graph_rendering_structure,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  height_of_graph_rendering_structure = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(width_of_graph_rendering_structure);
		    resumable_icp_push(grid_border_width);
		    resumable_icp_push(y_scale_of_graph_rendering);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		height_of_graph_rendering_structure = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		width_of_rendered_graph = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qwidth_of_rendered_graph,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(height_of_graph_rendering_structure);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qwidth_of_rendered_graph,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  width_of_rendered_graph = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(height_of_graph_rendering_structure);
		    resumable_icp_push(width_of_graph_rendering_structure);
		    resumable_icp_push(grid_border_width);
		    resumable_icp_push(y_scale_of_graph_rendering);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		width_of_rendered_graph = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		height_of_rendered_graph = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qheight_of_rendered_graph,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(width_of_rendered_graph);
		      resumable_icp_push(height_of_graph_rendering_structure);
		      resumable_icp_push(width_of_graph_rendering_structure);
		      resumable_icp_push(grid_border_width);
		      resumable_icp_push(y_scale_of_graph_rendering);
		      resumable_icp_push(x_scale_of_graph_rendering);
		      resumable_icp_push(format_of_graph_rendering_structure);
		      resumable_icp_push(corresponding_icp_object_index);
		      resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_making_graph_rendering;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qheight_of_rendered_graph,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  height_of_rendered_graph = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(width_of_rendered_graph);
		    resumable_icp_push(height_of_graph_rendering_structure);
		    resumable_icp_push(width_of_graph_rendering_structure);
		    resumable_icp_push(grid_border_width);
		    resumable_icp_push(y_scale_of_graph_rendering);
		    resumable_icp_push(x_scale_of_graph_rendering);
		    resumable_icp_push(format_of_graph_rendering_structure);
		    resumable_icp_push(corresponding_icp_object_index);
		    resumable_icp_push(Qhandle_icp_begin_making_graph_rendering);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_making_graph_rendering;
		}
		height_of_rendered_graph = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,0);
	      handle_icp_begin_making_graph_rendering__body(corresponding_icp_object_index,
		      format_of_graph_rendering_structure,
		      x_scale_of_graph_rendering,
		      y_scale_of_graph_rendering,grid_border_width,
		      width_of_graph_rendering_structure,
		      height_of_graph_rendering_structure,
		      width_of_rendered_graph,height_of_rendered_graph);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_begin_making_graph_rendering:
    return result;
}

/* DELETE-GRAPH-RENDERING-AND-RECLAIM-ICP-INDEX */
Object delete_graph_rendering_and_reclaim_icp_index(graph_rendering)
    Object graph_rendering;
{
    x_note_fn_call(53,23);
    reclaim_icp_object_map_for_graph_rendering(graph_rendering);
    return reclaim_graph_rendering_and_raster(graph_rendering);
}

Object The_type_description_of_ring_raster_for_graph = UNBOUND;

Object Chain_of_available_ring_raster_for_graphs = UNBOUND;

Object Ring_raster_for_graph_count = UNBOUND;

/* RING-RASTER-FOR-GRAPH-STRUCTURE-MEMORY-USAGE */
Object ring_raster_for_graph_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(53,24);
    temp = Ring_raster_for_graph_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RING-RASTER-FOR-GRAPH-COUNT */
Object outstanding_ring_raster_for_graph_count()
{
    Object def_structure_ring_raster_for_graph_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(53,25);
    gensymed_symbol = IFIX(Ring_raster_for_graph_count);
    def_structure_ring_raster_for_graph_variable = 
	    Chain_of_available_ring_raster_for_graphs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_ring_raster_for_graph_variable))
	goto end_loop;
    def_structure_ring_raster_for_graph_variable = 
	    ISVREF(def_structure_ring_raster_for_graph_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end;
    gensymed_symbol_1 = IFIX(Qnil);
  end:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RING-RASTER-FOR-GRAPH-1 */
Object reclaim_ring_raster_for_graph_1(ring_raster_for_graph)
    Object ring_raster_for_graph;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(53,26);
    inline_note_reclaim_cons(ring_raster_for_graph,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = ring_raster_for_graph;
    reclaim_gensym_tree_1(ISVREF(ring_raster_for_graph,(SI_Long)1L));
    SVREF(ring_raster_for_graph,FIX((SI_Long)1L)) = Nil;
    reclaim_gensym_list_1(ISVREF(ring_raster_for_graph,(SI_Long)4L));
    SVREF(ring_raster_for_graph,FIX((SI_Long)4L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_ring_raster_for_graphs;
    SVREF(ring_raster_for_graph,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_ring_raster_for_graphs = ring_raster_for_graph;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RING-RASTER-FOR-GRAPH */
Object reclaim_structure_for_ring_raster_for_graph(ring_raster_for_graph)
    Object ring_raster_for_graph;
{
    x_note_fn_call(53,27);
    return reclaim_ring_raster_for_graph_1(ring_raster_for_graph);
}

static Object Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct;  /* g2-defstruct-structure-name::ring-raster-for-graph-g2-struct */

/* MAKE-PERMANENT-RING-RASTER-FOR-GRAPH-STRUCTURE-INTERNAL */
Object make_permanent_ring_raster_for_graph_structure_internal()
{
    Object def_structure_ring_raster_for_graph_variable;
    Object ring_raster_for_graph_count_new_value;
    Object defstruct_g2_ring_raster_for_graph_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(53,28);
    def_structure_ring_raster_for_graph_variable = Nil;
    ring_raster_for_graph_count_new_value = 
	    FIXNUM_ADD1(Ring_raster_for_graph_count);
    Ring_raster_for_graph_count = ring_raster_for_graph_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_ring_raster_for_graph_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
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
	defstruct_g2_ring_raster_for_graph_variable = the_array;
	SVREF(defstruct_g2_ring_raster_for_graph_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct;
	def_structure_ring_raster_for_graph_variable = 
		defstruct_g2_ring_raster_for_graph_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_ring_raster_for_graph_variable);
}

/* MAKE-RING-RASTER-FOR-GRAPH-1 */
Object make_ring_raster_for_graph_1()
{
    Object def_structure_ring_raster_for_graph_variable;

    x_note_fn_call(53,29);
    def_structure_ring_raster_for_graph_variable = 
	    Chain_of_available_ring_raster_for_graphs;
    if (def_structure_ring_raster_for_graph_variable) {
	Chain_of_available_ring_raster_for_graphs = 
		ISVREF(def_structure_ring_raster_for_graph_variable,
		(SI_Long)0L);
	SVREF(def_structure_ring_raster_for_graph_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct;
    }
    else
	def_structure_ring_raster_for_graph_variable = 
		make_permanent_ring_raster_for_graph_structure_internal();
    inline_note_allocate_cons(def_structure_ring_raster_for_graph_variable,
	    Nil);
    SVREF(def_structure_ring_raster_for_graph_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_ring_raster_for_graph_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_ring_raster_for_graph_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_ring_raster_for_graph_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_ring_raster_for_graph_variable);
}

/* COMPUTE-TRUE-SIZE-OF-GRAPH-RENDERING */
Object compute_true_size_of_graph_rendering(graph_rendering)
    Object graph_rendering;
{
    Object graph_rendering_structure_qm, raster_or_rasters_qm;
    Object size_of_one_raster, raster_count;

    x_note_fn_call(53,30);
    graph_rendering_structure_qm = ISVREF(graph_rendering,(SI_Long)7L);
    raster_or_rasters_qm = graph_rendering_structure_qm ? 
	    ISVREF(graph_rendering_structure_qm,(SI_Long)1L) : Nil;
    size_of_one_raster = 
	    compute_true_size_of_graph_rendering_1(ISVREF(graph_rendering,
	    (SI_Long)12L),ISVREF(graph_rendering,(SI_Long)13L));
    if (CONSP(raster_or_rasters_qm))
	raster_count = length(raster_or_rasters_qm);
    else if (raster_or_rasters_qm)
	raster_count = FIX((SI_Long)1L);
    else
	raster_count = FIX((SI_Long)0L);
    return VALUES_1(FIXNUM_TIMES(raster_count,size_of_one_raster));
}

/* COMPUTE-TRUE-SIZE-OF-GRAPH-RENDERING-1 */
Object compute_true_size_of_graph_rendering_1(width,height)
    Object width, height;
{
    SI_Long temp;

    x_note_fn_call(53,31);
    temp = IFIX(l_round(FIXNUM_TIMES(width,height),FIX((SI_Long)32L)));
    return VALUES_1(FIX(MAX((SI_Long)1L,temp)));
}

static Object Qpolychrome_raster;  /* polychrome-raster */

static Object list_constant_1;     /* # */

/* RECLAIM-GRAPH-RENDERING-AND-RASTER */
Object reclaim_graph_rendering_and_raster(graph_rendering)
    Object graph_rendering;
{
    Object corresponding_graph_grid_or_chart_qm, ring_raster_qm;
    Object raster_or_rasters, window_for_graph_rendering;
    Object adjusted_allocation_width, adjusted_allocation_height;
    Object raster_in_list_qm, ab_loop_list_, raster, temp;
    SI_Long minimum_depth;

    x_note_fn_call(53,32);
    corresponding_graph_grid_or_chart_qm = ISVREF(graph_rendering,
	    (SI_Long)16L);
    ring_raster_qm = ISVREF(graph_rendering,(SI_Long)7L);
    if (corresponding_graph_grid_or_chart_qm)
	remove_graph_rendering_from_graph_grid(graph_rendering,
		corresponding_graph_grid_or_chart_qm);
    if (ring_raster_qm) {
	raster_or_rasters = ISVREF(ring_raster_qm,(SI_Long)1L);
	window_for_graph_rendering = ISVREF(graph_rendering,(SI_Long)17L);
	if (raster_or_rasters) {
	    minimum_depth = EQ(ISVREF(graph_rendering,(SI_Long)6L),
		    Qpolychrome_raster) ? (SI_Long)8L : (SI_Long)1L;
	    adjusted_allocation_width = FIXNUM_ADD1(ISVREF(graph_rendering,
		    (SI_Long)12L));
	    adjusted_allocation_height = 
		    FIXNUM_ADD1(ISVREF(graph_rendering,(SI_Long)13L));
	    raster_in_list_qm = Nil;
	    ab_loop_list_ = ATOM(raster_or_rasters) ? list_constant_1 : 
		    raster_or_rasters;
	    raster = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    raster_in_list_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = raster_in_list_qm;
	    if (temp);
	    else
		temp = raster_or_rasters;
	    raster = temp;
	    reclaim_stored_raster(raster,window_for_graph_rendering,
		    adjusted_allocation_width,adjusted_allocation_height,
		    FIX(minimum_depth),Nil);
	    goto next_loop;
	  end_loop:;
	}
	reclaim_ring_raster_for_graph_1(ring_raster_qm);
    }
    return reclaim_graph_rendering_1(graph_rendering);
}

Object Current_graph_rendering_structure = UNBOUND;

Object Current_graph_rendering = UNBOUND;

static Object Qsend_icp_prepare_for_painting_graph;  /* send-icp-prepare-for-painting-graph */

static Object Qprepare_for_painting_graph;  /* prepare-for-painting-graph */

static Object Qgraph_rendering;    /* graph-rendering */

/* SEND-ICP-PREPARE-FOR-PAINTING-GRAPH */
Object send_icp_prepare_for_painting_graph(graph_rendering)
    Object graph_rendering;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,33);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_prepare_for_painting_graph;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		  (SI_Long)5L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = make_corresponding_icp_graph_rendering(graph_rendering);
	  graph_rendering = temp_1;
	  start_writing_icp_message(FIX((SI_Long)158L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qprepare_for_painting_graph,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(graph_rendering);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qgraph_rendering,string_constant_3,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(graph_rendering);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprepare_for_painting_graph,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
			  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_corresponding_object_index(graph_rendering);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qgraph_rendering,string_constant_3,Qargument,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_corresponding_object_index(graph_rendering);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_prepare_for_painting_graph,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qsend_icp_prepare_for_painting_graph,top,Nil);
		goto end_send_icp_prepare_for_painting_graph;
	    }
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qsend_icp_prepare_for_painting_graph;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(graph_rendering,
		  (SI_Long)5L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      graph_rendering = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_graph_rendering(graph_rendering);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      graph_rendering = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)158L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qprepare_for_painting_graph,string_constant_1,
			  Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(graph_rendering))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qgraph_rendering,string_constant_3,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(graph_rendering))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qprepare_for_painting_graph,string_constant_1,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
			  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(graph_rendering))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qgraph_rendering,string_constant_3,Qargument,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_corresponding_object_index(graph_rendering))) {
	      resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(graph_rendering);
	      resumable_icp_push(Qsend_icp_prepare_for_painting_graph);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_prepare_for_painting_graph;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_prepare_for_painting_graph:
    return result;
}

static Object Qmonochrome_raster_list;  /* monochrome-raster-list */

/* HANDLE-ICP-PREPARE-FOR-PAINTING-GRAPH--BODY */
Object handle_icp_prepare_for_painting_graph__body(graph_rendering)
    Object graph_rendering;
{
    Object current_graph_rendering, current_graph_rendering_structure;
    Object adjusted_allocation_width, adjusted_allocation_height;
    Object raster_or_rasters, current_scratchpad_raster_type;
    Object current_scratchpad_raster, current_scratchpad_raster_tiled_p;
    Object current_scratchpad_raster_width, current_scratchpad_raster_height;
    Object current_scratchpad_raster_depth, on_monochrome_raster_list_p;
    Object color_value_list, current_scratchpad_raster_list;
    Object current_scratchpad_color_value_list, stored_raster, ab_loop_list_;
    Declare_special(11);

    x_note_fn_call(53,34);
    current_graph_rendering = graph_rendering;
    PUSH_SPECIAL(Current_graph_rendering,current_graph_rendering,10);
      current_graph_rendering_structure = ISVREF(graph_rendering,(SI_Long)7L);
      PUSH_SPECIAL(Current_graph_rendering_structure,current_graph_rendering_structure,
	      9);
	adjusted_allocation_width = FIXNUM_ADD1(ISVREF(graph_rendering,
		(SI_Long)12L));
	adjusted_allocation_height = FIXNUM_ADD1(ISVREF(graph_rendering,
		(SI_Long)13L));
	raster_or_rasters = ISVREF(Current_graph_rendering_structure,
		(SI_Long)1L);
	if (EQ(ISVREF(graph_rendering,(SI_Long)6L),Qpolychrome_raster)) {
	    current_scratchpad_raster_type = ISVREF(Current_window,
		    (SI_Long)23L);
	    PUSH_SPECIAL(Current_scratchpad_raster_type,current_scratchpad_raster_type,
		    6);
	      current_scratchpad_raster = raster_or_rasters;
	      PUSH_SPECIAL(Current_scratchpad_raster,current_scratchpad_raster,
		      5);
		current_scratchpad_raster_tiled_p = Nil;
		PUSH_SPECIAL(Current_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			4);
		  current_scratchpad_raster_width = adjusted_allocation_width;
		  PUSH_SPECIAL(Current_scratchpad_raster_width,current_scratchpad_raster_width,
			  3);
		    current_scratchpad_raster_height = 
			    adjusted_allocation_height;
		    PUSH_SPECIAL(Current_scratchpad_raster_height,current_scratchpad_raster_height,
			    2);
		      current_scratchpad_raster_depth = FIX((SI_Long)8L);
		      PUSH_SPECIAL(Current_scratchpad_raster_depth,current_scratchpad_raster_depth,
			      1);
			on_monochrome_raster_list_p = Nil;
			PUSH_SPECIAL(On_monochrome_raster_list_p,on_monochrome_raster_list_p,
				0);
			  handle_icp_messages(T);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else if (EQ(ISVREF(graph_rendering,(SI_Long)6L),
		Qmonochrome_raster_list)) {
	    color_value_list = ISVREF(Current_graph_rendering_structure,
		    (SI_Long)4L);
	    current_scratchpad_raster_type = ISVREF(Current_window,
		    (SI_Long)23L);
	    PUSH_SPECIAL(Current_scratchpad_raster_type,current_scratchpad_raster_type,
		    8);
	      current_scratchpad_raster_tiled_p = Nil;
	      PUSH_SPECIAL(Current_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
		      7);
		current_scratchpad_raster_width = adjusted_allocation_width;
		PUSH_SPECIAL(Current_scratchpad_raster_width,current_scratchpad_raster_width,
			6);
		  current_scratchpad_raster_height = 
			  adjusted_allocation_height;
		  PUSH_SPECIAL(Current_scratchpad_raster_height,current_scratchpad_raster_height,
			  5);
		    current_scratchpad_raster_depth = FIX((SI_Long)1L);
		    PUSH_SPECIAL(Current_scratchpad_raster_depth,current_scratchpad_raster_depth,
			    4);
		      on_monochrome_raster_list_p = T;
		      PUSH_SPECIAL(On_monochrome_raster_list_p,on_monochrome_raster_list_p,
			      3);
			current_scratchpad_raster_list = raster_or_rasters;
			PUSH_SPECIAL(Current_scratchpad_raster_list,current_scratchpad_raster_list,
				2);
			  current_scratchpad_color_value_list = 
				  color_value_list;
			  PUSH_SPECIAL(Current_scratchpad_color_value_list,current_scratchpad_color_value_list,
				  1);
			    current_scratchpad_raster = Nil;
			    PUSH_SPECIAL(Current_scratchpad_raster,current_scratchpad_raster,
				    0);
			      handle_icp_messages(T);
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
	    stored_raster = Nil;
	    ab_loop_list_ = raster_or_rasters;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    stored_raster = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    current_scratchpad_raster_type = ISVREF(Current_window,
		    (SI_Long)23L);
	    PUSH_SPECIAL(Current_scratchpad_raster_type,current_scratchpad_raster_type,
		    6);
	      current_scratchpad_raster = stored_raster;
	      PUSH_SPECIAL(Current_scratchpad_raster,current_scratchpad_raster,
		      5);
		current_scratchpad_raster_tiled_p = Nil;
		PUSH_SPECIAL(Current_scratchpad_raster_tiled_p,current_scratchpad_raster_tiled_p,
			4);
		  current_scratchpad_raster_width = adjusted_allocation_width;
		  PUSH_SPECIAL(Current_scratchpad_raster_width,current_scratchpad_raster_width,
			  3);
		    current_scratchpad_raster_height = 
			    adjusted_allocation_height;
		    PUSH_SPECIAL(Current_scratchpad_raster_height,current_scratchpad_raster_height,
			    2);
		      current_scratchpad_raster_depth = FIX((SI_Long)1L);
		      PUSH_SPECIAL(Current_scratchpad_raster_depth,current_scratchpad_raster_depth,
			      1);
			on_monochrome_raster_list_p = Nil;
			PUSH_SPECIAL(On_monochrome_raster_list_p,on_monochrome_raster_list_p,
				0);
			  handle_icp_messages(T);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    goto next_loop;
	  end_loop:;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_prepare_for_painting_graph;  /* handle-icp-prepare-for-painting-graph */

/* HANDLE-ICP-PREPARE-FOR-PAINTING-GRAPH */
Object handle_icp_prepare_for_painting_graph()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object graph_rendering, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,35);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qprepare_for_painting_graph,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_prepare_for_painting_graph__body(graph_rendering);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qprepare_for_painting_graph,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,0);
	      handle_icp_prepare_for_painting_graph__body(graph_rendering);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_prepare_for_painting_graph,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_prepare_for_painting_graph,top,Nil);
		goto end_handle_icp_prepare_for_painting_graph;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qprepare_for_painting_graph,
			string_constant_1,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_prepare_for_painting_graph);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_prepare_for_painting_graph;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_prepare_for_painting_graph);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_prepare_for_painting_graph;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_prepare_for_painting_graph__body(graph_rendering);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qprepare_for_painting_graph,string_constant_1,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_prepare_for_painting_graph);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_prepare_for_painting_graph;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_prepare_for_painting_graph);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_prepare_for_painting_graph;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL(Abort_for_icp_catcher_qm,abort_for_icp_catcher_qm,0);
	      handle_icp_prepare_for_painting_graph__body(graph_rendering);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_prepare_for_painting_graph:
    return result;
}

static Object Qupdate_ring_raster_for_graph_given_color_values;  /* update-ring-raster-for-graph-given-color-values */

static Object Qicp;                /* icp */

static Object Qnumber_of_rasters_needed;  /* number-of-rasters-needed */

static Object Qprinter;            /* printer */

/* UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES */
Object update_ring_raster_for_graph_given_color_values(graph_rendering,
	    number_of_rasters_needed)
    Object graph_rendering, number_of_rasters_needed;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, ring_raster;
    Object raster_or_rasters_qm, raster_surplus, width, height, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, rest_of_rasters, ab_loop_iter_flag_;
    Object graph_raster_list, resumable_icp_state_1, icp_suspend_1, top, key;
    Object value, value_1;
    SI_Long x, ab_loop_bind_;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,36);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qupdate_ring_raster_for_graph_given_color_values;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qupdate_ring_raster_for_graph_given_color_values);
	      temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
	      graph_rendering = temp_1;
	      start_writing_icp_message(FIX((SI_Long)157L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_ring_raster_for_graph_given_color_values,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_corresponding_object_index(graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qnumber_of_rasters_needed,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_unsigned_integer(number_of_rasters_needed);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qnumber_of_rasters_needed,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_unsigned_integer(number_of_rasters_needed);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_ring_raster_for_graph_given_color_values,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qnumber_of_rasters_needed,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_unsigned_integer(number_of_rasters_needed);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qnumber_of_rasters_needed,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(number_of_rasters_needed);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)157L));
	      FUNCALL_2(temp_1,graph_rendering,number_of_rasters_needed);
	  }
	  else {
	      ring_raster = ISVREF(graph_rendering,(SI_Long)7L);
	      raster_or_rasters_qm = ISVREF(ring_raster,(SI_Long)1L);
	      if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),
			  Qpolychrome_raster)) {
		  raster_surplus = 
			  FIXNUM_MINUS(length(raster_or_rasters_qm),
			  number_of_rasters_needed);
		  if (IFIX(raster_surplus) < (SI_Long)0L) {
		      width = FIXNUM_ADD1(ISVREF(graph_rendering,
			      (SI_Long)12L));
		      height = FIXNUM_ADD1(ISVREF(graph_rendering,
			      (SI_Long)13L));
		      x = (SI_Long)-1L;
		      ab_loop_bind_ = IFIX(raster_surplus);
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop:
		      if (x < ab_loop_bind_)
			  goto end_loop;
		      ab_loopvar__2 = 
			      gensym_cons_1(allocate_stored_raster_1(Current_window,
			      width,height,FIX((SI_Long)1L),Nil),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      x = x - (SI_Long)1L;
		      goto next_loop;
		    end_loop:
		      temp_1 = ab_loopvar_;
		      goto end;
		      temp_1 = Qnil;
		    end:;
		      temp = nconc2(raster_or_rasters_qm,temp_1);
		      SVREF(ring_raster,FIX((SI_Long)1L)) = temp;
		  }
		  else if (IFIX(raster_surplus) > (SI_Long)0L) {
		      x = (SI_Long)1L;
		      ab_loop_bind_ = IFIX(number_of_rasters_needed);
		      rest_of_rasters = raster_or_rasters_qm;
		      ab_loop_iter_flag_ = T;
		    next_loop_1:
		      if (x > ab_loop_bind_)
			  goto end_loop_1;
		      if ( !TRUEP(ab_loop_iter_flag_))
			  rest_of_rasters = M_CDR(rest_of_rasters);
		      if ( !TRUEP(rest_of_rasters))
			  goto end_loop_1;
		      ab_loop_iter_flag_ = Nil;
		      x = x + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:
		      graph_raster_list = CDR(rest_of_rasters);
		      reclaim_gensym_list_1(graph_raster_list);
		      M_CDR(rest_of_rasters) = Nil;
		  }
	      }
	      else if ( !TRUEP(raster_or_rasters_qm)) {
		  temp = allocate_stored_raster_1(Current_window,
			  FIXNUM_ADD1(ISVREF(graph_rendering,
			  (SI_Long)12L)),
			  FIXNUM_ADD1(ISVREF(graph_rendering,
			  (SI_Long)13L)),FIX((SI_Long)8L),Nil);
		  SVREF(ring_raster,FIX((SI_Long)1L)) = temp;
	      }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qupdate_ring_raster_for_graph_given_color_values,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qupdate_ring_raster_for_graph_given_color_values,
			top,Nil);
		goto end_update_ring_raster_for_graph_given_color_values;
	    }
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	number_of_rasters_needed = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : number_of_rasters_needed;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qupdate_ring_raster_for_graph_given_color_values;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			case 3:
			  goto l3;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qupdate_ring_raster_for_graph_given_color_values);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  graph_rendering = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  graph_rendering = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)157L)))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l3:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_ring_raster_for_graph_given_color_values,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_corresponding_object_index(graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qnumber_of_rasters_needed,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_unsigned_integer(number_of_rasters_needed))) 
				      {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qnumber_of_rasters_needed,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(number_of_rasters_needed))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_ring_raster_for_graph_given_color_values,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_corresponding_object_index(graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(graph_rendering))) 
			      {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qnumber_of_rasters_needed,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_unsigned_integer(number_of_rasters_needed))) 
				    {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qnumber_of_rasters_needed,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(number_of_rasters_needed))) 
			      {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(number_of_rasters_needed);
		  resumable_icp_push(graph_rendering);
		  resumable_icp_push(Qupdate_ring_raster_for_graph_given_color_values);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_update_ring_raster_for_graph_given_color_values;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)157L));
	      FUNCALL_2(temp_1,graph_rendering,number_of_rasters_needed);
	  }
	  else {
	      ring_raster = ISVREF(graph_rendering,(SI_Long)7L);
	      raster_or_rasters_qm = ISVREF(ring_raster,(SI_Long)1L);
	      if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),
			  Qpolychrome_raster)) {
		  raster_surplus = 
			  FIXNUM_MINUS(length(raster_or_rasters_qm),
			  number_of_rasters_needed);
		  if (IFIX(raster_surplus) < (SI_Long)0L) {
		      width = FIXNUM_ADD1(ISVREF(graph_rendering,
			      (SI_Long)12L));
		      height = FIXNUM_ADD1(ISVREF(graph_rendering,
			      (SI_Long)13L));
		      x = (SI_Long)-1L;
		      ab_loop_bind_ = IFIX(raster_surplus);
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_2:
		      if (x < ab_loop_bind_)
			  goto end_loop_2;
		      ab_loopvar__2 = 
			      gensym_cons_1(allocate_stored_raster_1(Current_window,
			      width,height,FIX((SI_Long)1L),Nil),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      x = x - (SI_Long)1L;
		      goto next_loop_2;
		    end_loop_2:
		      temp_1 = ab_loopvar_;
		      goto end_1;
		      temp_1 = Qnil;
		    end_1:;
		      temp = nconc2(raster_or_rasters_qm,temp_1);
		      SVREF(ring_raster,FIX((SI_Long)1L)) = temp;
		  }
		  else if (IFIX(raster_surplus) > (SI_Long)0L) {
		      x = (SI_Long)1L;
		      ab_loop_bind_ = IFIX(number_of_rasters_needed);
		      rest_of_rasters = raster_or_rasters_qm;
		      ab_loop_iter_flag_ = T;
		    next_loop_3:
		      if (x > ab_loop_bind_)
			  goto end_loop_3;
		      if ( !TRUEP(ab_loop_iter_flag_))
			  rest_of_rasters = M_CDR(rest_of_rasters);
		      if ( !TRUEP(rest_of_rasters))
			  goto end_loop_3;
		      ab_loop_iter_flag_ = Nil;
		      x = x + (SI_Long)1L;
		      goto next_loop_3;
		    end_loop_3:
		      graph_raster_list = CDR(rest_of_rasters);
		      reclaim_gensym_list_1(graph_raster_list);
		      M_CDR(rest_of_rasters) = Nil;
		  }
	      }
	      else if ( !TRUEP(raster_or_rasters_qm)) {
		  temp = allocate_stored_raster_1(Current_window,
			  FIXNUM_ADD1(ISVREF(graph_rendering,
			  (SI_Long)12L)),
			  FIXNUM_ADD1(ISVREF(graph_rendering,
			  (SI_Long)13L)),FIX((SI_Long)8L),Nil);
		  SVREF(ring_raster,FIX((SI_Long)1L)) = temp;
	      }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_update_ring_raster_for_graph_given_color_values:
    return result;
}

static Object string_constant_4;   /* "[msg funct]" */

static Object Qhandle_icp_update_ring_raster_for_graph_given_color_values;  /* handle-icp-update-ring-raster-for-graph-given-color-values */

/* HANDLE-ICP-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES */
Object handle_icp_update_ring_raster_for_graph_given_color_values()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object graph_rendering, number_of_rasters_needed, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,37);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qupdate_ring_raster_for_graph_given_color_values,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnumber_of_rasters_needed,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_rasters_needed,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    number_of_rasters_needed = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  number_of_rasters_needed = read_icp_unsigned_integer();
	      result_of_read = 
		      update_ring_raster_for_graph_given_color_values(graph_rendering,
		      number_of_rasters_needed);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_ring_raster_for_graph_given_color_values,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnumber_of_rasters_needed,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_rasters_needed,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  number_of_rasters_needed = result_of_read;
		POP_SPECIAL();
	    }
	    else
		number_of_rasters_needed = read_icp_unsigned_integer();
	    update_ring_raster_for_graph_given_color_values(graph_rendering,
		    number_of_rasters_needed);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_update_ring_raster_for_graph_given_color_values,
		    top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_update_ring_raster_for_graph_given_color_values,
			top,Nil);
		goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qupdate_ring_raster_for_graph_given_color_values,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  number_of_rasters_needed = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qnumber_of_rasters_needed,string_constant_2,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qnumber_of_rasters_needed,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    number_of_rasters_needed = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		  }
		  number_of_rasters_needed = value;
	      }
	      result_of_read = 
		      update_ring_raster_for_graph_given_color_values(graph_rendering,
		      number_of_rasters_needed);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_ring_raster_for_graph_given_color_values,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		number_of_rasters_needed = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qnumber_of_rasters_needed,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qnumber_of_rasters_needed,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  number_of_rasters_needed = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_ring_raster_for_graph_given_color_values;
		}
		number_of_rasters_needed = value;
	    }
	    update_ring_raster_for_graph_given_color_values(graph_rendering,
		    number_of_rasters_needed);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_update_ring_raster_for_graph_given_color_values:
    return result;
}

static Object Qupdate_ring_raster_for_graph_given_color_values_2;  /* update-ring-raster-for-graph-given-color-values-2 */

static Object Qcolor_values_for_rasters_qm;  /* color-values-for-rasters? */

/* UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2 */
Object update_ring_raster_for_graph_given_color_values_2(graph_rendering,
	    color_values_for_rasters_qm)
    Object graph_rendering, color_values_for_rasters_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, ring_raster_for_graph;
    Object resumable_icp_state_1, icp_suspend_1, top, key, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,38);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qupdate_ring_raster_for_graph_given_color_values_2;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qupdate_ring_raster_for_graph_given_color_values_2);
	      temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
	      graph_rendering = temp_1;
	      start_writing_icp_message(FIX((SI_Long)182L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_ring_raster_for_graph_given_color_values_2,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_corresponding_object_index(graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_values_for_rasters_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_ring_raster_for_graph_given_color_values_2,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qcolor_values_for_rasters_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)182L));
	      FUNCALL_2(temp_1,graph_rendering,color_values_for_rasters_qm);
	  }
	  else {
	      update_ring_raster_for_graph_given_color_values(graph_rendering,
		      length(color_values_for_rasters_qm));
	      if (EQ(ISVREF(graph_rendering,(SI_Long)6L),
		      Qmonochrome_raster_list)) {
		  ring_raster_for_graph = ISVREF(graph_rendering,(SI_Long)7L);
		  reclaim_gensym_list_1(ISVREF(ring_raster_for_graph,
			  (SI_Long)4L));
		  temp = 
			  copy_list_using_gensym_conses_1(color_values_for_rasters_qm);
		  SVREF(ring_raster_for_graph,FIX((SI_Long)4L)) = temp;
	      }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qupdate_ring_raster_for_graph_given_color_values_2,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qupdate_ring_raster_for_graph_given_color_values_2,
			top,Nil);
		goto end_update_ring_raster_for_graph_given_color_values_2;
	    }
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	color_values_for_rasters_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : color_values_for_rasters_qm;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qupdate_ring_raster_for_graph_given_color_values_2;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			case 3:
			  goto l3;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qupdate_ring_raster_for_graph_given_color_values_2);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  graph_rendering = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  graph_rendering = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)182L)))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l3:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_ring_raster_for_graph_given_color_values_2,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_corresponding_object_index(graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				      {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_values_for_rasters_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_ring_raster_for_graph_given_color_values_2,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_corresponding_object_index(graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(graph_rendering))) 
			      {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qcolor_values_for_rasters_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				    {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
			      {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(color_values_for_rasters_qm);
		  resumable_icp_push(graph_rendering);
		  resumable_icp_push(Qupdate_ring_raster_for_graph_given_color_values_2);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_update_ring_raster_for_graph_given_color_values_2;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)182L));
	      FUNCALL_2(temp_1,graph_rendering,color_values_for_rasters_qm);
	  }
	  else {
	      update_ring_raster_for_graph_given_color_values(graph_rendering,
		      length(color_values_for_rasters_qm));
	      if (EQ(ISVREF(graph_rendering,(SI_Long)6L),
		      Qmonochrome_raster_list)) {
		  ring_raster_for_graph = ISVREF(graph_rendering,(SI_Long)7L);
		  reclaim_gensym_list_1(ISVREF(ring_raster_for_graph,
			  (SI_Long)4L));
		  temp = 
			  copy_list_using_gensym_conses_1(color_values_for_rasters_qm);
		  SVREF(ring_raster_for_graph,FIX((SI_Long)4L)) = temp;
	      }
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_update_ring_raster_for_graph_given_color_values_2:
    return result;
}

static Object Qlist_of_unsigned_integers;  /* list-of-unsigned-integers */

static Object string_constant_5;   /* "[value]" */

static Object Qvalue;              /* value */

static Object Qhandle_icp_update_ring_raster_for_graph_given_color_values_2;  /* handle-icp-update-ring-raster-for-graph-given-color-values-2 */

/* HANDLE-ICP-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2 */
Object handle_icp_update_ring_raster_for_graph_given_color_values_2()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object graph_rendering, tracep_2, byte_count_before_2, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, color_values_for_rasters_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    SI_Long ab_loop_repeat_;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,39);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qupdate_ring_raster_for_graph_given_color_values_2,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			  ab_loopvar_ = Nil;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			next_loop:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  ab_loopvar__2 = 
				  gensym_cons_1(read_icp_unsigned_integer(),
				  Nil);
			  if (ab_loopvar__1)
			      M_CDR(ab_loopvar__1) = ab_loopvar__2;
			  else
			      ab_loopvar_ = ab_loopvar__2;
			  ab_loopvar__1 = ab_loopvar__2;
			  goto next_loop;
			end_loop:
			  result_of_read = ab_loopvar_;
			  goto end;
			  result_of_read = Qnil;
			end:;
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qlist_of_unsigned_integers,
				      string_constant_5,Qvalue,T,
				      result_of_read,Nil,Nil);
			POP_SPECIAL();
		    }
		    else {
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_1:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_1;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			result_of_read = ab_loopvar_;
			goto end_1;
			result_of_read = Qnil;
		      end_1:;
		    }
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_values_for_rasters_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else if (Icp_read_trace_cutoff_level_qm) {
		  tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep_1);
		  else
		      tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			      (SI_Long)4L ? T : Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_unsigned_integers,string_constant_5,
			      Qvalue,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    ab_loopvar__2 = 
			    gensym_cons_1(read_icp_unsigned_integer(),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    result_of_read = ab_loopvar_;
		    goto end_2;
		    result_of_read = Qnil;
		  end_2:;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_unsigned_integers,
				string_constant_5,Qvalue,T,result_of_read,
				Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loopvar__2 = Nil;
		next_loop_3:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_3;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  ab_loopvar__2 = 
			  gensym_cons_1(read_icp_unsigned_integer(),Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
		  goto next_loop_3;
		end_loop_3:
		  color_values_for_rasters_qm = ab_loopvar_;
		  goto end_3;
		  color_values_for_rasters_qm = Qnil;
		end_3:;
	      }
	      update_ring_raster_for_graph_given_color_values_2(graph_rendering,
		      color_values_for_rasters_qm);
	      result_of_read = 
		      reclaim_gensym_list_1(color_values_for_rasters_qm);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_ring_raster_for_graph_given_color_values_2,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcolor_values_for_rasters_qm,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_4:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_4;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_4;
		      end_loop_4:
			result_of_read = ab_loopvar_;
			goto end_4;
			result_of_read = Qnil;
		      end_4:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_5:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_5;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_5;
		    end_loop_5:
		      result_of_read = ab_loopvar_;
		      goto end_5;
		      result_of_read = Qnil;
		    end_5:;
		  }
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_unsigned_integers,string_constant_5,
			    Qvalue,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loopvar__2 = Nil;
		next_loop_6:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_6;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  ab_loopvar__2 = 
			  gensym_cons_1(read_icp_unsigned_integer(),Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
		  goto next_loop_6;
		end_loop_6:
		  result_of_read = ab_loopvar_;
		  goto end_6;
		  result_of_read = Qnil;
		end_6:;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_unsigned_integers,string_constant_5,
			      Qvalue,T,result_of_read,Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_7:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_7;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		ab_loopvar__2 = gensym_cons_1(read_icp_unsigned_integer(),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_7;
	      end_loop_7:
		color_values_for_rasters_qm = ab_loopvar_;
		goto end_7;
		color_values_for_rasters_qm = Qnil;
	      end_7:;
	    }
	    update_ring_raster_for_graph_given_color_values_2(graph_rendering,
		    color_values_for_rasters_qm);
	    reclaim_gensym_list_1(color_values_for_rasters_qm);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2,
		    top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_update_ring_raster_for_graph_given_color_values_2,
			top,Nil);
		goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qupdate_ring_raster_for_graph_given_color_values_2,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  color_values_for_rasters_qm = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			  ab_loopvar_ = Nil;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			next_loop_8:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_8;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  ab_loopvar__2 = 
				  gensym_cons_1(read_icp_unsigned_integer(),
				  Nil);
			  if (ab_loopvar__1)
			      M_CDR(ab_loopvar__1) = ab_loopvar__2;
			  else
			      ab_loopvar_ = ab_loopvar__2;
			  ab_loopvar__1 = ab_loopvar__2;
			  goto next_loop_8;
			end_loop_8:
			  result_of_read = ab_loopvar_;
			  goto end_8;
			  result_of_read = Qnil;
			end_8:;
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qlist_of_unsigned_integers,
				      string_constant_5,Qvalue,T,
				      result_of_read,Nil,Nil);
			  value = result_of_read;
			POP_SPECIAL();
		    }
		    else {
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_9:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_9;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_9;
		      end_loop_9:
			value = ab_loopvar_;
			goto end_9;
			value = Qnil;
		      end_9:;
		    }
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_values_for_rasters_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_10:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_10;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_10;
		      end_loop_10:
			result_of_read = ab_loopvar_;
			goto end_10;
			result_of_read = Qnil;
		      end_10:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_11:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_11;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_11;
		    end_loop_11:
		      value = ab_loopvar_;
		      goto end_11;
		      value = Qnil;
		    end_11:;
		  }
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		  }
		  color_values_for_rasters_qm = value;
	      }
	      update_ring_raster_for_graph_given_color_values_2(graph_rendering,
		      color_values_for_rasters_qm);
	      result_of_read = 
		      reclaim_gensym_list_1(color_values_for_rasters_qm);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_ring_raster_for_graph_given_color_values_2,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		color_values_for_rasters_qm = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcolor_values_for_rasters_qm,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_12:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_12;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_12;
		      end_loop_12:
			result_of_read = ab_loopvar_;
			goto end_12;
			result_of_read = Qnil;
		      end_12:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_13:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_13;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_13;
		    end_loop_13:
		      value = ab_loopvar_;
		      goto end_13;
		      value = Qnil;
		    end_13:;
		  }
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)4L ? T : Nil;
		    if (tracep) {
			emit_icp_read_trace(T,Nil,Nil,
				Qlist_of_unsigned_integers,
				string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			byte_count_before = 
				instantaneous_icp_reader_byte_count();
		    }
		    else
			byte_count_before = Nil;
		    current_icp_read_trace_level = 
			    FIXNUM_ADD1(Current_icp_read_trace_level);
		    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			    0);
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_14:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_14;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_14;
		    end_loop_14:
		      result_of_read = ab_loopvar_;
		      goto end_14;
		      result_of_read = Qnil;
		    end_14:;
		      if (tracep)
			  emit_icp_read_trace(Nil,byte_count_before,
				  instantaneous_icp_reader_byte_count(),
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,T,
				  result_of_read,Nil,Nil);
		      value = result_of_read;
		    POP_SPECIAL();
		}
		else {
		    ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_15:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_15;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    ab_loopvar__2 = 
			    gensym_cons_1(read_icp_unsigned_integer(),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_15;
		  end_loop_15:
		    value = ab_loopvar_;
		    goto end_15;
		    value = Qnil;
		  end_15:;
		}
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_ring_raster_for_graph_given_color_values_2;
		}
		color_values_for_rasters_qm = value;
	    }
	    update_ring_raster_for_graph_given_color_values_2(graph_rendering,
		    color_values_for_rasters_qm);
	    reclaim_gensym_list_1(color_values_for_rasters_qm);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_update_ring_raster_for_graph_given_color_values_2:
    return result;
}

static Object Qset_graph_rendering_foreground_only_mode;  /* set-graph-rendering-foreground-only-mode */

static Object Qforeground_only_mode;  /* foreground-only-mode */

/* SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE */
Object set_graph_rendering_foreground_only_mode(graph_rendering,
	    foreground_only_mode)
    Object graph_rendering, foreground_only_mode;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, key, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,40);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qset_graph_rendering_foreground_only_mode;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qset_graph_rendering_foreground_only_mode);
	      temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
	      graph_rendering = temp_1;
	      start_writing_icp_message(FIX((SI_Long)192L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qset_graph_rendering_foreground_only_mode,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_corresponding_object_index(graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qforeground_only_mode,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_boolean(foreground_only_mode);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qforeground_only_mode,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_boolean(foreground_only_mode);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qset_graph_rendering_foreground_only_mode,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qforeground_only_mode,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_boolean(foreground_only_mode);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qforeground_only_mode,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_boolean(foreground_only_mode);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)192L));
	      FUNCALL_2(temp_1,graph_rendering,foreground_only_mode);
	  }
	  else
	      SVREF(graph_rendering,FIX((SI_Long)19L)) = foreground_only_mode;
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qset_graph_rendering_foreground_only_mode,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qset_graph_rendering_foreground_only_mode,top,Nil);
		goto end_set_graph_rendering_foreground_only_mode;
	    }
	}
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	foreground_only_mode = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : foreground_only_mode;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qset_graph_rendering_foreground_only_mode;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			case 3:
			  goto l3;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qset_graph_rendering_foreground_only_mode);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  graph_rendering = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  graph_rendering = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)192L)))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l3:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qset_graph_rendering_foreground_only_mode,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_corresponding_object_index(graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qforeground_only_mode,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_boolean(foreground_only_mode))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qforeground_only_mode,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_boolean(foreground_only_mode))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qset_graph_rendering_foreground_only_mode,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_corresponding_object_index(graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(graph_rendering))) 
			      {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qforeground_only_mode,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_boolean(foreground_only_mode))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qforeground_only_mode,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_boolean(foreground_only_mode))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(foreground_only_mode);
		  resumable_icp_push(graph_rendering);
		  resumable_icp_push(Qset_graph_rendering_foreground_only_mode);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_set_graph_rendering_foreground_only_mode;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)192L));
	      FUNCALL_2(temp_1,graph_rendering,foreground_only_mode);
	  }
	  else
	      SVREF(graph_rendering,FIX((SI_Long)19L)) = foreground_only_mode;
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_set_graph_rendering_foreground_only_mode:
    return result;
}

static Object Qhandle_icp_set_graph_rendering_foreground_only_mode;  /* handle-icp-set-graph-rendering-foreground-only-mode */

/* HANDLE-ICP-SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE */
Object handle_icp_set_graph_rendering_foreground_only_mode()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, index_1, index_space, result_of_read;
    Object graph_rendering, foreground_only_mode, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,41);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qset_graph_rendering_foreground_only_mode,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qforeground_only_mode,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_boolean();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qforeground_only_mode,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    foreground_only_mode = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  foreground_only_mode = read_icp_boolean();
	      result_of_read = 
		      set_graph_rendering_foreground_only_mode(graph_rendering,
		      foreground_only_mode);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qset_graph_rendering_foreground_only_mode,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qforeground_only_mode,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_boolean();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qforeground_only_mode,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  foreground_only_mode = result_of_read;
		POP_SPECIAL();
	    }
	    else
		foreground_only_mode = read_icp_boolean();
	    set_graph_rendering_foreground_only_mode(graph_rendering,
		    foreground_only_mode);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_set_graph_rendering_foreground_only_mode,
			top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_set_graph_rendering_foreground_only_mode,
			top,Nil);
		goto end_handle_icp_set_graph_rendering_foreground_only_mode;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qset_graph_rendering_foreground_only_mode,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_set_graph_rendering_foreground_only_mode;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  foreground_only_mode = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qforeground_only_mode,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_boolean();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qforeground_only_mode,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    foreground_only_mode = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		  }
		  foreground_only_mode = value;
	      }
	      result_of_read = 
		      set_graph_rendering_foreground_only_mode(graph_rendering,
		      foreground_only_mode);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qset_graph_rendering_foreground_only_mode,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		foreground_only_mode = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qforeground_only_mode,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qforeground_only_mode,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  foreground_only_mode = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_boolean();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(Qhandle_icp_set_graph_rendering_foreground_only_mode);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_set_graph_rendering_foreground_only_mode;
		}
		foreground_only_mode = value;
	    }
	    set_graph_rendering_foreground_only_mode(graph_rendering,
		    foreground_only_mode);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_set_graph_rendering_foreground_only_mode:
    return result;
}

Object Clipping_rectangles_for_new_data_qm = UNBOUND;

static Object Qx11_window;         /* x11-window */

/* ADD-FROM-GRAPH-RING-RASTER-TO-CURRENT-WINDOW */
Object add_from_graph_ring_raster_to_current_window(clipped_left_edge,
	    clipped_top_edge,clipped_right_edge,clipped_bottom_edge,
	    color_value,grid_background_color_value,first_raster_qm,
	    graph_rendering,ring_raster,raster,left_edge_in_stored_raster,
	    top_edge_in_stored_raster,left_edge_of_new_data_in_ring_raster,
	    top_edge_of_new_data_in_ring_raster,
	    right_edge_of_new_data_in_ring_raster,
	    bottom_edge_of_new_data_in_ring_raster)
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, color_value, grid_background_color_value;
    Object first_raster_qm, graph_rendering, ring_raster, raster;
    Object left_edge_in_stored_raster, top_edge_in_stored_raster;
    Object left_edge_of_new_data_in_ring_raster;
    Object top_edge_of_new_data_in_ring_raster;
    Object right_edge_of_new_data_in_ring_raster;
    Object bottom_edge_of_new_data_in_ring_raster;
{
    Object border_width, erase_raster_dateline, raster_width;
    Object raster_width_to_right_of_erase_dateline, clipped_region_width;
    Object clipped_region_height, right_edge_in_stored_raster;
    Object bottom_edge_in_stored_raster, background_color_value, stored_raster;
    Object new_left_edge_in_stored_raster, width_of_region_a;
    Object clipped_edge_for_dateline, clipped_right_edge_1;
    SI_Long n_2nd_alu_function, alu_function, left_edge_in_stored_raster_1;

    x_note_fn_call(53,42);
    border_width = ISVREF(graph_rendering,(SI_Long)11L);
    left_edge_in_stored_raster = FIXNUM_ADD(left_edge_in_stored_raster,
	    border_width);
    top_edge_in_stored_raster = FIXNUM_ADD(top_edge_in_stored_raster,
	    border_width);
    erase_raster_dateline = ISVREF(ring_raster,(SI_Long)3L);
    raster_width = ISVREF(graph_rendering,(SI_Long)12L);
    raster_width_to_right_of_erase_dateline = FIXNUM_MINUS(raster_width,
	    erase_raster_dateline);
    clipped_region_width = FIXNUM_MINUS(clipped_right_edge,clipped_left_edge);
    clipped_region_height = FIXNUM_MINUS(clipped_bottom_edge,clipped_top_edge);
    right_edge_in_stored_raster = FIXNUM_ADD(left_edge_in_stored_raster,
	    clipped_region_width);
    bottom_edge_in_stored_raster = FIXNUM_ADD(top_edge_in_stored_raster,
	    clipped_region_height);
    if (left_edge_of_new_data_in_ring_raster) {
	left_edge_of_new_data_in_ring_raster = 
		FIXNUM_LT(left_edge_of_new_data_in_ring_raster,
		erase_raster_dateline) ? 
		FIXNUM_ADD(left_edge_of_new_data_in_ring_raster,
		raster_width_to_right_of_erase_dateline) : 
		FIXNUM_MINUS(left_edge_of_new_data_in_ring_raster,
		erase_raster_dateline);
	right_edge_of_new_data_in_ring_raster = 
		FIXNUM_LT(right_edge_of_new_data_in_ring_raster,
		erase_raster_dateline) ? 
		FIXNUM_ADD(right_edge_of_new_data_in_ring_raster,
		raster_width_to_right_of_erase_dateline) : 
		FIXNUM_MINUS(right_edge_of_new_data_in_ring_raster,
		erase_raster_dateline);
	if (FIXNUM_GT(left_edge_of_new_data_in_ring_raster,
		left_edge_in_stored_raster)) {
	    clipped_left_edge = FIXNUM_ADD(clipped_left_edge,
		    FIXNUM_MINUS(left_edge_of_new_data_in_ring_raster,
		    left_edge_in_stored_raster));
	    left_edge_in_stored_raster = left_edge_of_new_data_in_ring_raster;
	}
	if (FIXNUM_GT(top_edge_of_new_data_in_ring_raster,
		top_edge_in_stored_raster)) {
	    clipped_top_edge = FIXNUM_ADD(clipped_top_edge,
		    FIXNUM_MINUS(top_edge_of_new_data_in_ring_raster,
		    top_edge_in_stored_raster));
	    top_edge_in_stored_raster = top_edge_of_new_data_in_ring_raster;
	}
	if (FIXNUM_LT(right_edge_of_new_data_in_ring_raster,
		right_edge_in_stored_raster))
	    clipped_right_edge = FIXNUM_MINUS(clipped_right_edge,
		    FIXNUM_MINUS(right_edge_in_stored_raster,
		    right_edge_of_new_data_in_ring_raster));
	if (FIXNUM_LT(bottom_edge_of_new_data_in_ring_raster,
		bottom_edge_in_stored_raster))
	    clipped_bottom_edge = FIXNUM_MINUS(clipped_bottom_edge,
		    FIXNUM_MINUS(bottom_edge_in_stored_raster,
		    bottom_edge_of_new_data_in_ring_raster));
	clipped_region_width = FIXNUM_MINUS(clipped_right_edge,
		clipped_left_edge);
    }
    if (FIXNUM_LT(clipped_left_edge,clipped_right_edge) && 
	    FIXNUM_LT(clipped_top_edge,clipped_bottom_edge)) {
	if (FIXNUM_LT(left_edge_in_stored_raster,
		raster_width_to_right_of_erase_dateline)) {
	    if (FIXNUM_LE(FIXNUM_ADD(left_edge_in_stored_raster,
		    clipped_region_width),
		    raster_width_to_right_of_erase_dateline)) {
		left_edge_in_stored_raster = 
			FIXNUM_ADD(left_edge_in_stored_raster,
			erase_raster_dateline);
		if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),
			Qpolychrome_raster)) {
		    n_2nd_alu_function = ISVREF(graph_rendering,
			    (SI_Long)19L) ? IFIX(X11_stippled) : IFIX(X11_xor);
		    alu_function = first_raster_qm ? IFIX(X11_copy) : 
			    n_2nd_alu_function;
		    background_color_value = first_raster_qm ? 
			    grid_background_color_value : FIX((SI_Long)0L);
		    stored_raster = raster;
		    if (EQ(Type_of_current_window,Qx11_window))
			g2ext_copy_pixmap_to_window(IFIX(stored_raster),
				IFIX(Current_native_window_qm),
				IFIX(left_edge_in_stored_raster),
				IFIX(top_edge_in_stored_raster),
				IFIX(clipped_left_edge),
				IFIX(clipped_top_edge),
				IFIX(FIXNUM_MINUS(clipped_right_edge,
				clipped_left_edge)),
				IFIX(FIXNUM_MINUS(clipped_bottom_edge,
				clipped_top_edge)),IFIX(color_value),
				IFIX(background_color_value),alu_function);
		}
		else if (EQ(Type_of_current_window,Qx11_window))
		    g2ext_copy_polychrome_pixmap_to_window(IFIX(raster),
			    IFIX(Current_native_window_qm),
			    IFIX(left_edge_in_stored_raster),
			    IFIX(top_edge_in_stored_raster),
			    IFIX(clipped_left_edge),IFIX(clipped_top_edge),
			    IFIX(FIXNUM_MINUS(clipped_right_edge,
			    clipped_left_edge)),
			    IFIX(FIXNUM_MINUS(clipped_bottom_edge,
			    clipped_top_edge)),IFIX(X11_copy));
	    }
	    else {
		new_left_edge_in_stored_raster = 
			FIXNUM_ADD(left_edge_in_stored_raster,
			erase_raster_dateline);
		width_of_region_a = FIXNUM_MINUS(raster_width,
			new_left_edge_in_stored_raster);
		clipped_edge_for_dateline = FIXNUM_ADD(clipped_left_edge,
			width_of_region_a);
		if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),
			Qpolychrome_raster)) {
		    n_2nd_alu_function = ISVREF(graph_rendering,
			    (SI_Long)19L) ? IFIX(X11_stippled) : IFIX(X11_xor);
		    alu_function = first_raster_qm ? IFIX(X11_copy) : 
			    n_2nd_alu_function;
		    clipped_right_edge_1 = clipped_edge_for_dateline;
		    background_color_value = first_raster_qm ? 
			    grid_background_color_value : FIX((SI_Long)0L);
		    stored_raster = raster;
		    left_edge_in_stored_raster = 
			    new_left_edge_in_stored_raster;
		    if (EQ(Type_of_current_window,Qx11_window))
			g2ext_copy_pixmap_to_window(IFIX(stored_raster),
				IFIX(Current_native_window_qm),
				IFIX(left_edge_in_stored_raster),
				IFIX(top_edge_in_stored_raster),
				IFIX(clipped_left_edge),
				IFIX(clipped_top_edge),
				IFIX(FIXNUM_MINUS(clipped_right_edge_1,
				clipped_left_edge)),
				IFIX(FIXNUM_MINUS(clipped_bottom_edge,
				clipped_top_edge)),IFIX(color_value),
				IFIX(background_color_value),alu_function);
		}
		else if (EQ(Type_of_current_window,Qx11_window))
		    g2ext_copy_polychrome_pixmap_to_window(IFIX(raster),
			    IFIX(Current_native_window_qm),
			    IFIX(new_left_edge_in_stored_raster),
			    IFIX(top_edge_in_stored_raster),
			    IFIX(clipped_left_edge),IFIX(clipped_top_edge),
			    IFIX(FIXNUM_MINUS(clipped_edge_for_dateline,
			    clipped_left_edge)),
			    IFIX(FIXNUM_MINUS(clipped_bottom_edge,
			    clipped_top_edge)),IFIX(X11_copy));
		if (FIXNUM_GT(clipped_right_edge,clipped_edge_for_dateline)) {
		    if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),
			    Qpolychrome_raster)) {
			n_2nd_alu_function = ISVREF(graph_rendering,
				(SI_Long)19L) ? IFIX(X11_stippled) : 
				IFIX(X11_xor);
			alu_function = first_raster_qm ? IFIX(X11_copy) : 
				n_2nd_alu_function;
			clipped_left_edge = clipped_edge_for_dateline;
			background_color_value = first_raster_qm ? 
				grid_background_color_value : FIX((SI_Long)0L);
			stored_raster = raster;
			left_edge_in_stored_raster_1 = (SI_Long)0L;
			if (EQ(Type_of_current_window,Qx11_window))
			    g2ext_copy_pixmap_to_window(IFIX(stored_raster),
				    IFIX(Current_native_window_qm),
				    left_edge_in_stored_raster_1,
				    IFIX(top_edge_in_stored_raster),
				    IFIX(clipped_left_edge),
				    IFIX(clipped_top_edge),
				    IFIX(FIXNUM_MINUS(clipped_right_edge,
				    clipped_left_edge)),
				    IFIX(FIXNUM_MINUS(clipped_bottom_edge,
				    clipped_top_edge)),IFIX(color_value),
				    IFIX(background_color_value),alu_function);
		    }
		    else if (EQ(Type_of_current_window,Qx11_window))
			g2ext_copy_polychrome_pixmap_to_window(IFIX(raster),
				IFIX(Current_native_window_qm),(SI_Long)0L,
				IFIX(top_edge_in_stored_raster),
				IFIX(clipped_edge_for_dateline),
				IFIX(clipped_top_edge),
				IFIX(FIXNUM_MINUS(clipped_right_edge,
				clipped_edge_for_dateline)),
				IFIX(FIXNUM_MINUS(clipped_bottom_edge,
				clipped_top_edge)),IFIX(X11_copy));
		}
	    }
	}
	else {
	    left_edge_in_stored_raster = 
		    FIXNUM_MINUS(left_edge_in_stored_raster,
		    raster_width_to_right_of_erase_dateline);
	    if ( !EQ(ISVREF(graph_rendering,(SI_Long)6L),Qpolychrome_raster)) {
		n_2nd_alu_function = ISVREF(graph_rendering,(SI_Long)19L) ?
			 IFIX(X11_stippled) : IFIX(X11_xor);
		alu_function = first_raster_qm ? IFIX(X11_copy) : 
			n_2nd_alu_function;
		background_color_value = first_raster_qm ? 
			grid_background_color_value : FIX((SI_Long)0L);
		stored_raster = raster;
		if (EQ(Type_of_current_window,Qx11_window))
		    g2ext_copy_pixmap_to_window(IFIX(stored_raster),
			    IFIX(Current_native_window_qm),
			    IFIX(left_edge_in_stored_raster),
			    IFIX(top_edge_in_stored_raster),
			    IFIX(clipped_left_edge),IFIX(clipped_top_edge),
			    IFIX(FIXNUM_MINUS(clipped_right_edge,
			    clipped_left_edge)),
			    IFIX(FIXNUM_MINUS(clipped_bottom_edge,
			    clipped_top_edge)),IFIX(color_value),
			    IFIX(background_color_value),alu_function);
	    }
	    else if (EQ(Type_of_current_window,Qx11_window))
		g2ext_copy_polychrome_pixmap_to_window(IFIX(raster),
			IFIX(Current_native_window_qm),
			IFIX(left_edge_in_stored_raster),
			IFIX(top_edge_in_stored_raster),
			IFIX(clipped_left_edge),IFIX(clipped_top_edge),
			IFIX(FIXNUM_MINUS(clipped_right_edge,
			clipped_left_edge)),
			IFIX(FIXNUM_MINUS(clipped_bottom_edge,
			clipped_top_edge)),IFIX(X11_copy));
	}
    }
    return VALUES_1(Nil);
}

static Object Qadd_from_graph_rendering_to_current_window;  /* add-from-graph-rendering-to-current-window */

static Object Qsubtract_instead_qm;  /* subtract-instead? */

static Object Qclipped_left_edge;  /* clipped-left-edge */

static Object Qclipped_top_edge;   /* clipped-top-edge */

static Object Qclipped_right_edge;  /* clipped-right-edge */

static Object Qclipped_bottom_edge;  /* clipped-bottom-edge */

static Object Qgrid_background_color_value;  /* grid-background-color-value */

static Object Qleft_edge_in_graph_rendering;  /* left-edge-in-graph-rendering */

static Object Qtop_edge_in_graph_rendering;  /* top-edge-in-graph-rendering */

static Object Qcolor_value;        /* color-value */

/* ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW */
Object add_from_graph_rendering_to_current_window(subtract_instead_qm,
	    clipped_left_edge,clipped_top_edge,clipped_right_edge,
	    clipped_bottom_edge,grid_background_color_value,
	    graph_rendering,left_edge_in_graph_rendering,
	    top_edge_in_graph_rendering,color_value,
	    color_values_for_rasters_qm)
    Object subtract_instead_qm, clipped_left_edge, clipped_top_edge;
    Object clipped_right_edge, clipped_bottom_edge;
    Object grid_background_color_value, graph_rendering;
    Object left_edge_in_graph_rendering, top_edge_in_graph_rendering;
    Object color_value, color_values_for_rasters_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, rendering_structure;
    Object flipped_colors, remaining_color_values_qm, flipped_rasters;
    Object raster_or_rasters_qm, remaining_rasters_qm, first_time_qm;
    Object next_color_value, color_value_or_difference, raster;
    Object rest_of_rectangles, remaining_color_values_qm_old_value;
    Object remaining_rasters_qm_old_value, resumable_icp_state_1;
    Object icp_suspend_1, top, key, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,43);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qadd_from_graph_rendering_to_current_window;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qadd_from_graph_rendering_to_current_window);
	      temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
	      graph_rendering = temp_1;
	      start_writing_icp_message(FIX((SI_Long)151L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qadd_from_graph_rendering_to_current_window,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qsubtract_instead_qm,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_boolean(subtract_instead_qm);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qsubtract_instead_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_boolean(subtract_instead_qm);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_left_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(clipped_left_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_left_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(clipped_left_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_top_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(clipped_top_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_top_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(clipped_top_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_right_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(clipped_right_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_right_edge,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(clipped_right_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_bottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(clipped_bottom_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_bottom_edge,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(clipped_bottom_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgrid_background_color_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_unsigned_integer(grid_background_color_value);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgrid_background_color_value,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_unsigned_integer(grid_background_color_value);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_corresponding_object_index(graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_corresponding_object_index(graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qleft_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(left_edge_in_graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qleft_edge_in_graph_rendering,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(left_edge_in_graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qtop_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_integer(top_edge_in_graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qtop_edge_in_graph_rendering,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(top_edge_in_graph_rendering);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qcolor_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_unsigned_integer(color_value);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_value,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_unsigned_integer(color_value);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_values_for_rasters_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qadd_from_graph_rendering_to_current_window,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qsubtract_instead_qm,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_boolean(subtract_instead_qm);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qsubtract_instead_qm,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_boolean(subtract_instead_qm);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_left_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(clipped_left_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_left_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(clipped_left_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qclipped_top_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(clipped_top_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_top_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(clipped_top_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_right_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_integer(clipped_right_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_right_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(clipped_right_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_bottom_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_integer(clipped_bottom_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_bottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(clipped_bottom_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qgrid_background_color_value,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_unsigned_integer(grid_background_color_value);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgrid_background_color_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(grid_background_color_value);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qleft_edge_in_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_integer(left_edge_in_graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qleft_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(left_edge_in_graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qtop_edge_in_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_integer(top_edge_in_graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qtop_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(top_edge_in_graph_rendering);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qcolor_value,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_unsigned_integer(color_value);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_value,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_unsigned_integer(color_value);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qcolor_values_for_rasters_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_list_of_unsigned_integers(color_values_for_rasters_qm);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter))
	      funcall(12,aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)151L)),subtract_instead_qm,
		      clipped_left_edge,clipped_top_edge,
		      clipped_right_edge,clipped_bottom_edge,
		      grid_background_color_value,graph_rendering,
		      left_edge_in_graph_rendering,
		      top_edge_in_graph_rendering,color_value,
		      color_values_for_rasters_qm);
	  else {
	      rendering_structure = ISVREF(graph_rendering,(SI_Long)7L);
	      flipped_colors = ISVREF(graph_rendering,(SI_Long)19L) ? 
		      nreverse(copy_list_using_gensym_conses_1(color_values_for_rasters_qm)) 
		      : color_values_for_rasters_qm;
	      remaining_color_values_qm = flipped_colors;
	      flipped_rasters = ISVREF(graph_rendering,(SI_Long)19L) ? 
		      nreverse(copy_list_using_gensym_conses_1(ISVREF(rendering_structure,
		      (SI_Long)1L))) : ISVREF(rendering_structure,(SI_Long)1L);
	      raster_or_rasters_qm = flipped_rasters;
	      remaining_rasters_qm = CONSP(raster_or_rasters_qm) ? 
		      raster_or_rasters_qm : Nil;
	      first_time_qm = T;
	      next_color_value = Nil;
	      color_value_or_difference = Nil;
	      raster = Nil;
	    next_loop:
	      next_color_value = remaining_color_values_qm ? 
		      CAR(remaining_color_values_qm) : color_value;
	      color_value_or_difference = first_time_qm ? next_color_value 
		      : ISVREF(graph_rendering,(SI_Long)19L) ? 
		      next_color_value : FIXNUM_LOGXOR(next_color_value,
		      grid_background_color_value);
	      raster = remaining_rasters_qm ? CAR(remaining_rasters_qm) : 
		      raster_or_rasters_qm;
	      if (Clipping_rectangles_for_new_data_qm) {
		  rest_of_rectangles = Clipping_rectangles_for_new_data_qm;
		next_loop_1:
		  if ( !TRUEP(rest_of_rectangles))
		      goto end_loop;
		  add_from_graph_ring_raster_to_current_window(clipped_left_edge,
			  clipped_top_edge,clipped_right_edge,
			  clipped_bottom_edge,color_value_or_difference,
			  grid_background_color_value,first_time_qm,
			  graph_rendering,rendering_structure,raster,
			  left_edge_in_graph_rendering,
			  top_edge_in_graph_rendering,
			  FIRST(rest_of_rectangles),
			  SECOND(rest_of_rectangles),
			  THIRD(rest_of_rectangles),
			  FOURTH(rest_of_rectangles));
		  rest_of_rectangles = nthcdr(FIX((SI_Long)4L),
			  rest_of_rectangles);
		  goto next_loop_1;
		end_loop:;
	      }
	      else
		  add_from_graph_ring_raster_to_current_window(clipped_left_edge,
			  clipped_top_edge,clipped_right_edge,
			  clipped_bottom_edge,color_value_or_difference,
			  grid_background_color_value,first_time_qm,
			  graph_rendering,rendering_structure,raster,
			  left_edge_in_graph_rendering,
			  top_edge_in_graph_rendering,Nil,Nil,Nil,Nil);
	      if ( !TRUEP(remaining_color_values_qm) ||  
		      !TRUEP(CDR(remaining_color_values_qm)))
		  goto end;
	      else {
		  remaining_color_values_qm_old_value = 
			  remaining_color_values_qm;
		  remaining_color_values_qm = 
			  REST(remaining_color_values_qm_old_value);
		  remaining_rasters_qm_old_value = remaining_rasters_qm;
		  remaining_rasters_qm = REST(remaining_rasters_qm_old_value);
	      }
	      first_time_qm = Nil;
	      goto next_loop;
	    end_loop_1:
	      if (ISVREF(graph_rendering,(SI_Long)19L)) {
		  reclaim_gensym_list_1(flipped_colors);
		  reclaim_gensym_list_1(flipped_rasters);
	      }
	    end:;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qadd_from_graph_rendering_to_current_window,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qadd_from_graph_rendering_to_current_window,top,Nil);
		goto end_add_from_graph_rendering_to_current_window;
	    }
	}
	subtract_instead_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : subtract_instead_qm;
	clipped_left_edge = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : clipped_left_edge;
	clipped_top_edge = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : clipped_top_edge;
	clipped_right_edge = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : clipped_right_edge;
	clipped_bottom_edge = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : clipped_bottom_edge;
	grid_background_color_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : grid_background_color_value;
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	left_edge_in_graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : left_edge_in_graph_rendering;
	top_edge_in_graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : top_edge_in_graph_rendering;
	color_value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		 TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : color_value;
	color_values_for_rasters_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : color_values_for_rasters_qm;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qadd_from_graph_rendering_to_current_window;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			case 3:
			  goto l3;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qadd_from_graph_rendering_to_current_window);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  graph_rendering = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  graph_rendering = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)151L)))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l3:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qadd_from_graph_rendering_to_current_window,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      case 3:
				goto l3_1;
				break;
			      case 4:
				goto l4;
				break;
			      case 5:
				goto l5;
				break;
			      case 6:
				goto l6;
				break;
			      case 7:
				goto l7;
				break;
			      case 8:
				goto l8;
				break;
			      case 9:
				goto l9;
				break;
			      case 10:
				goto l10;
				break;
			      case 11:
				goto l11;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qsubtract_instead_qm,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_boolean(subtract_instead_qm))) {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qsubtract_instead_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_boolean(subtract_instead_qm))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_left_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(clipped_left_edge))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_left_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(clipped_left_edge))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l3_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_top_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(clipped_top_edge))) {
			      resumable_icp_push(FIX((SI_Long)3L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_top_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(clipped_top_edge))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l4:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_right_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(clipped_right_edge))) {
			      resumable_icp_push(FIX((SI_Long)4L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_right_edge,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(clipped_right_edge))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l5:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qclipped_bottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(clipped_bottom_edge))) {
			      resumable_icp_push(FIX((SI_Long)5L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qclipped_bottom_edge,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(clipped_bottom_edge))) {
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l6:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgrid_background_color_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_unsigned_integer(grid_background_color_value))) 
				      {
			      resumable_icp_push(FIX((SI_Long)6L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgrid_background_color_value,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(grid_background_color_value))) 
				{
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l7:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_corresponding_object_index(graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)7L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)7L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l8:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qleft_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(left_edge_in_graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)8L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qleft_edge_in_graph_rendering,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(left_edge_in_graph_rendering))) {
			resumable_icp_push(FIX((SI_Long)8L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l9:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qtop_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(top_edge_in_graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)9L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qtop_edge_in_graph_rendering,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(top_edge_in_graph_rendering))) {
			resumable_icp_push(FIX((SI_Long)9L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l10:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qcolor_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_unsigned_integer(color_value))) {
			      resumable_icp_push(FIX((SI_Long)10L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_value,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(color_value))) {
			resumable_icp_push(FIX((SI_Long)10L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l11:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				      {
			      resumable_icp_push(FIX((SI_Long)11L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qcolor_values_for_rasters_qm,
				      string_constant_2,Qargument,Nil,Nil,
				      Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				{
			resumable_icp_push(FIX((SI_Long)11L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qadd_from_graph_rendering_to_current_window,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    case 3:
			      goto l3_2;
			      break;
			    case 4:
			      goto l4_1;
			      break;
			    case 5:
			      goto l5_1;
			      break;
			    case 6:
			      goto l6_1;
			      break;
			    case 7:
			      goto l7_1;
			      break;
			    case 8:
			      goto l8_1;
			      break;
			    case 9:
			      goto l9_1;
			      break;
			    case 10:
			      goto l10_1;
			      break;
			    case 11:
			      goto l11_1;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qsubtract_instead_qm,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_boolean(subtract_instead_qm))) {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qsubtract_instead_qm,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_boolean(subtract_instead_qm))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_left_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(clipped_left_edge))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_left_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(clipped_left_edge))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l3_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qclipped_top_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(clipped_top_edge))) {
			    resumable_icp_push(FIX((SI_Long)3L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_top_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(clipped_top_edge))) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l4_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_right_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(clipped_right_edge))) {
			    resumable_icp_push(FIX((SI_Long)4L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_right_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(clipped_right_edge))) {
		      resumable_icp_push(FIX((SI_Long)4L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l5_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qclipped_bottom_edge,string_constant_2,
				  Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(clipped_bottom_edge))) {
			    resumable_icp_push(FIX((SI_Long)5L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qclipped_bottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(clipped_bottom_edge))) {
		      resumable_icp_push(FIX((SI_Long)5L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l6_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qgrid_background_color_value,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_unsigned_integer(grid_background_color_value))) 
				    {
			    resumable_icp_push(FIX((SI_Long)6L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgrid_background_color_value,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(grid_background_color_value))) 
			      {
		      resumable_icp_push(FIX((SI_Long)6L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l7_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_corresponding_object_index(graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)7L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(graph_rendering))) 
			      {
		      resumable_icp_push(FIX((SI_Long)7L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l8_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qleft_edge_in_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(left_edge_in_graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)8L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qleft_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(left_edge_in_graph_rendering))) {
		      resumable_icp_push(FIX((SI_Long)8L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l9_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qtop_edge_in_graph_rendering,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(top_edge_in_graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)9L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qtop_edge_in_graph_rendering,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_integer(top_edge_in_graph_rendering))) {
		      resumable_icp_push(FIX((SI_Long)9L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l10_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qcolor_value,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_unsigned_integer(color_value))) {
			    resumable_icp_push(FIX((SI_Long)10L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_value,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_unsigned_integer(color_value))) {
		      resumable_icp_push(FIX((SI_Long)10L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l11_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,
				  Qcolor_values_for_rasters_qm,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
				    {
			    resumable_icp_push(FIX((SI_Long)11L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qcolor_values_for_rasters_qm,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_list_of_unsigned_integers(color_values_for_rasters_qm))) 
			      {
		      resumable_icp_push(FIX((SI_Long)11L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(color_values_for_rasters_qm);
		  resumable_icp_push(color_value);
		  resumable_icp_push(top_edge_in_graph_rendering);
		  resumable_icp_push(left_edge_in_graph_rendering);
		  resumable_icp_push(graph_rendering);
		  resumable_icp_push(grid_background_color_value);
		  resumable_icp_push(clipped_bottom_edge);
		  resumable_icp_push(clipped_right_edge);
		  resumable_icp_push(clipped_top_edge);
		  resumable_icp_push(clipped_left_edge);
		  resumable_icp_push(subtract_instead_qm);
		  resumable_icp_push(Qadd_from_graph_rendering_to_current_window);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_add_from_graph_rendering_to_current_window;
	      }
	  }
	  else if (EQ(key,Qprinter))
	      funcall(12,aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)151L)),subtract_instead_qm,
		      clipped_left_edge,clipped_top_edge,
		      clipped_right_edge,clipped_bottom_edge,
		      grid_background_color_value,graph_rendering,
		      left_edge_in_graph_rendering,
		      top_edge_in_graph_rendering,color_value,
		      color_values_for_rasters_qm);
	  else {
	      rendering_structure = ISVREF(graph_rendering,(SI_Long)7L);
	      flipped_colors = ISVREF(graph_rendering,(SI_Long)19L) ? 
		      nreverse(copy_list_using_gensym_conses_1(color_values_for_rasters_qm)) 
		      : color_values_for_rasters_qm;
	      remaining_color_values_qm = flipped_colors;
	      flipped_rasters = ISVREF(graph_rendering,(SI_Long)19L) ? 
		      nreverse(copy_list_using_gensym_conses_1(ISVREF(rendering_structure,
		      (SI_Long)1L))) : ISVREF(rendering_structure,(SI_Long)1L);
	      raster_or_rasters_qm = flipped_rasters;
	      remaining_rasters_qm = CONSP(raster_or_rasters_qm) ? 
		      raster_or_rasters_qm : Nil;
	      first_time_qm = T;
	      next_color_value = Nil;
	      color_value_or_difference = Nil;
	      raster = Nil;
	    next_loop_2:
	      next_color_value = remaining_color_values_qm ? 
		      CAR(remaining_color_values_qm) : color_value;
	      color_value_or_difference = first_time_qm ? next_color_value 
		      : ISVREF(graph_rendering,(SI_Long)19L) ? 
		      next_color_value : FIXNUM_LOGXOR(next_color_value,
		      grid_background_color_value);
	      raster = remaining_rasters_qm ? CAR(remaining_rasters_qm) : 
		      raster_or_rasters_qm;
	      if (Clipping_rectangles_for_new_data_qm) {
		  rest_of_rectangles = Clipping_rectangles_for_new_data_qm;
		next_loop_3:
		  if ( !TRUEP(rest_of_rectangles))
		      goto end_loop_2;
		  add_from_graph_ring_raster_to_current_window(clipped_left_edge,
			  clipped_top_edge,clipped_right_edge,
			  clipped_bottom_edge,color_value_or_difference,
			  grid_background_color_value,first_time_qm,
			  graph_rendering,rendering_structure,raster,
			  left_edge_in_graph_rendering,
			  top_edge_in_graph_rendering,
			  FIRST(rest_of_rectangles),
			  SECOND(rest_of_rectangles),
			  THIRD(rest_of_rectangles),
			  FOURTH(rest_of_rectangles));
		  rest_of_rectangles = nthcdr(FIX((SI_Long)4L),
			  rest_of_rectangles);
		  goto next_loop_3;
		end_loop_2:;
	      }
	      else
		  add_from_graph_ring_raster_to_current_window(clipped_left_edge,
			  clipped_top_edge,clipped_right_edge,
			  clipped_bottom_edge,color_value_or_difference,
			  grid_background_color_value,first_time_qm,
			  graph_rendering,rendering_structure,raster,
			  left_edge_in_graph_rendering,
			  top_edge_in_graph_rendering,Nil,Nil,Nil,Nil);
	      if ( !TRUEP(remaining_color_values_qm) ||  
		      !TRUEP(CDR(remaining_color_values_qm)))
		  goto end_1;
	      else {
		  remaining_color_values_qm_old_value = 
			  remaining_color_values_qm;
		  remaining_color_values_qm = 
			  REST(remaining_color_values_qm_old_value);
		  remaining_rasters_qm_old_value = remaining_rasters_qm;
		  remaining_rasters_qm = REST(remaining_rasters_qm_old_value);
	      }
	      first_time_qm = Nil;
	      goto next_loop_2;
	    end_loop_3:
	      if (ISVREF(graph_rendering,(SI_Long)19L)) {
		  reclaim_gensym_list_1(flipped_colors);
		  reclaim_gensym_list_1(flipped_rasters);
	      }
	    end_1:;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_add_from_graph_rendering_to_current_window:
    return result;
}

static Object Qhandle_icp_add_from_graph_rendering_to_current_window;  /* handle-icp-add-from-graph-rendering-to-current-window */

/* HANDLE-ICP-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW */
Object handle_icp_add_from_graph_rendering_to_current_window()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, subtract_instead_qm;
    Object clipped_left_edge, clipped_top_edge, clipped_right_edge;
    Object clipped_bottom_edge, grid_background_color_value, index_1;
    Object index_space, graph_rendering, left_edge_in_graph_rendering;
    Object top_edge_in_graph_rendering, color_value, tracep_2;
    Object byte_count_before_2, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object color_values_for_rasters_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    SI_Long ab_loop_repeat_;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,44);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qadd_from_graph_rendering_to_current_window,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsubtract_instead_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_boolean();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsubtract_instead_qm,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    subtract_instead_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  subtract_instead_qm = read_icp_boolean();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_left_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_left_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_left_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  clipped_left_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_top_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_top_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_top_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  clipped_top_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_right_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_right_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_right_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  clipped_right_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_bottom_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_bottom_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_bottom_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  clipped_bottom_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qgrid_background_color_value,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgrid_background_color_value,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    grid_background_color_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  grid_background_color_value = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qleft_edge_in_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge_in_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    left_edge_in_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  left_edge_in_graph_rendering = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qtop_edge_in_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge_in_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    top_edge_in_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  top_edge_in_graph_rendering = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcolor_value,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_unsigned_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_value,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  color_value = read_icp_unsigned_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			  ab_loopvar_ = Nil;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			next_loop:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  ab_loopvar__2 = 
				  gensym_cons_1(read_icp_unsigned_integer(),
				  Nil);
			  if (ab_loopvar__1)
			      M_CDR(ab_loopvar__1) = ab_loopvar__2;
			  else
			      ab_loopvar_ = ab_loopvar__2;
			  ab_loopvar__1 = ab_loopvar__2;
			  goto next_loop;
			end_loop:
			  result_of_read = ab_loopvar_;
			  goto end;
			  result_of_read = Qnil;
			end:;
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qlist_of_unsigned_integers,
				      string_constant_5,Qvalue,T,
				      result_of_read,Nil,Nil);
			POP_SPECIAL();
		    }
		    else {
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_1:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_1;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_1;
		      end_loop_1:
			result_of_read = ab_loopvar_;
			goto end_1;
			result_of_read = Qnil;
		      end_1:;
		    }
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_values_for_rasters_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else if (Icp_read_trace_cutoff_level_qm) {
		  tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep_1);
		  else
		      tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			      (SI_Long)4L ? T : Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qlist_of_unsigned_integers,string_constant_5,
			      Qvalue,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    ab_loopvar__2 = 
			    gensym_cons_1(read_icp_unsigned_integer(),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_2;
		  end_loop_2:
		    result_of_read = ab_loopvar_;
		    goto end_2;
		    result_of_read = Qnil;
		  end_2:;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qlist_of_unsigned_integers,
				string_constant_5,Qvalue,T,result_of_read,
				Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loopvar__2 = Nil;
		next_loop_3:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_3;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  ab_loopvar__2 = 
			  gensym_cons_1(read_icp_unsigned_integer(),Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
		  goto next_loop_3;
		end_loop_3:
		  color_values_for_rasters_qm = ab_loopvar_;
		  goto end_3;
		  color_values_for_rasters_qm = Qnil;
		end_3:;
	      }
	      add_from_graph_rendering_to_current_window(subtract_instead_qm,
		      clipped_left_edge,clipped_top_edge,
		      clipped_right_edge,clipped_bottom_edge,
		      grid_background_color_value,graph_rendering,
		      left_edge_in_graph_rendering,
		      top_edge_in_graph_rendering,color_value,
		      color_values_for_rasters_qm);
	      result_of_read = 
		      reclaim_gensym_list_1(color_values_for_rasters_qm);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qadd_from_graph_rendering_to_current_window,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsubtract_instead_qm,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_boolean();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsubtract_instead_qm,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  subtract_instead_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else
		subtract_instead_qm = read_icp_boolean();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_left_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_left_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_left_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		clipped_left_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_top_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_top_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_top_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		clipped_top_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_right_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_right_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_right_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		clipped_right_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_bottom_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_bottom_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_bottom_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		clipped_bottom_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qgrid_background_color_value,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgrid_background_color_value,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  grid_background_color_value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		grid_background_color_value = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qleft_edge_in_graph_rendering,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge_in_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  left_edge_in_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else
		left_edge_in_graph_rendering = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qtop_edge_in_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge_in_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  top_edge_in_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else
		top_edge_in_graph_rendering = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcolor_value,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_unsigned_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_value,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  color_value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		color_value = read_icp_unsigned_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcolor_values_for_rasters_qm,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_4:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_4;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_4;
		      end_loop_4:
			result_of_read = ab_loopvar_;
			goto end_4;
			result_of_read = Qnil;
		      end_4:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_5:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_5;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_5;
		    end_loop_5:
		      result_of_read = ab_loopvar_;
		      goto end_5;
		      result_of_read = Qnil;
		    end_5:;
		  }
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else if (Icp_read_trace_cutoff_level_qm) {
		tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		if (tracep);
		else
		    tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			    (SI_Long)4L ? T : Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qlist_of_unsigned_integers,string_constant_5,
			    Qvalue,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		  ab_loopvar_ = Nil;
		  ab_loopvar__1 = Nil;
		  ab_loopvar__2 = Nil;
		next_loop_6:
		  if ( !((SI_Long)0L < ab_loop_repeat_))
		      goto end_loop_6;
		  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		  ab_loopvar__2 = 
			  gensym_cons_1(read_icp_unsigned_integer(),Nil);
		  if (ab_loopvar__1)
		      M_CDR(ab_loopvar__1) = ab_loopvar__2;
		  else
		      ab_loopvar_ = ab_loopvar__2;
		  ab_loopvar__1 = ab_loopvar__2;
		  goto next_loop_6;
		end_loop_6:
		  result_of_read = ab_loopvar_;
		  goto end_6;
		  result_of_read = Qnil;
		end_6:;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qlist_of_unsigned_integers,string_constant_5,
			      Qvalue,T,result_of_read,Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_7:
		if ( !((SI_Long)0L < ab_loop_repeat_))
		    goto end_loop_7;
		ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		ab_loopvar__2 = gensym_cons_1(read_icp_unsigned_integer(),Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_7;
	      end_loop_7:
		color_values_for_rasters_qm = ab_loopvar_;
		goto end_7;
		color_values_for_rasters_qm = Qnil;
	      end_7:;
	    }
	    add_from_graph_rendering_to_current_window(subtract_instead_qm,
		    clipped_left_edge,clipped_top_edge,clipped_right_edge,
		    clipped_bottom_edge,grid_background_color_value,
		    graph_rendering,left_edge_in_graph_rendering,
		    top_edge_in_graph_rendering,color_value,
		    color_values_for_rasters_qm);
	    reclaim_gensym_list_1(color_values_for_rasters_qm);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qhandle_icp_add_from_graph_rendering_to_current_window,
		    top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_add_from_graph_rendering_to_current_window,
			top,Nil);
		goto end_handle_icp_add_from_graph_rendering_to_current_window;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qadd_from_graph_rendering_to_current_window,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  subtract_instead_qm = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qsubtract_instead_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_boolean();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qsubtract_instead_qm,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    subtract_instead_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  subtract_instead_qm = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  clipped_left_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_left_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_left_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_left_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  clipped_left_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  clipped_top_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_top_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_top_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_top_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  clipped_top_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  clipped_right_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_right_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_right_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_right_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  clipped_right_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  clipped_bottom_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qclipped_bottom_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qclipped_bottom_edge,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    clipped_bottom_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  clipped_bottom_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  grid_background_color_value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qgrid_background_color_value,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgrid_background_color_value,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    grid_background_color_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  grid_background_color_value = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(grid_background_color_value);
			    resumable_icp_push(clipped_bottom_edge);
			    resumable_icp_push(clipped_right_edge);
			    resumable_icp_push(clipped_top_edge);
			    resumable_icp_push(clipped_left_edge);
			    resumable_icp_push(subtract_instead_qm);
			    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_add_from_graph_rendering_to_current_window;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(grid_background_color_value);
			  resumable_icp_push(clipped_bottom_edge);
			  resumable_icp_push(clipped_right_edge);
			  resumable_icp_push(clipped_top_edge);
			  resumable_icp_push(clipped_left_edge);
			  resumable_icp_push(subtract_instead_qm);
			  resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_add_from_graph_rendering_to_current_window;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  left_edge_in_graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qleft_edge_in_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(grid_background_color_value);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge_in_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    left_edge_in_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  left_edge_in_graph_rendering = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  top_edge_in_graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qtop_edge_in_graph_rendering,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(left_edge_in_graph_rendering);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(grid_background_color_value);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge_in_graph_rendering,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    top_edge_in_graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  top_edge_in_graph_rendering = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  color_value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qcolor_value,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_unsigned_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(top_edge_in_graph_rendering);
			resumable_icp_push(left_edge_in_graph_rendering);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(grid_background_color_value);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_value,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge_in_graph_rendering);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  color_value = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  color_values_for_rasters_qm = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  1);
		    if (Icp_read_trace_cutoff_level_qm) {
			tracep_2 = EQ(Icp_read_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_2);
			else
			    tracep_2 = 
				    IFIX(Icp_read_trace_cutoff_level_qm) 
				    >= (SI_Long)4L ? T : Nil;
			if (tracep_2) {
			    emit_icp_read_trace(T,Nil,Nil,
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			    byte_count_before_2 = 
				    instantaneous_icp_reader_byte_count();
			}
			else
			    byte_count_before_2 = Nil;
			current_icp_read_trace_level = 
				FIXNUM_ADD1(Current_icp_read_trace_level);
			PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
				0);
			  ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			  ab_loopvar_ = Nil;
			  ab_loopvar__1 = Nil;
			  ab_loopvar__2 = Nil;
			next_loop_8:
			  if ( !((SI_Long)0L < ab_loop_repeat_))
			      goto end_loop_8;
			  ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			  ab_loopvar__2 = 
				  gensym_cons_1(read_icp_unsigned_integer(),
				  Nil);
			  if (ab_loopvar__1)
			      M_CDR(ab_loopvar__1) = ab_loopvar__2;
			  else
			      ab_loopvar_ = ab_loopvar__2;
			  ab_loopvar__1 = ab_loopvar__2;
			  goto next_loop_8;
			end_loop_8:
			  result_of_read = ab_loopvar_;
			  goto end_8;
			  result_of_read = Qnil;
			end_8:;
			  if (tracep_2)
			      emit_icp_read_trace(Nil,byte_count_before_2,
				      instantaneous_icp_reader_byte_count(),
				      Qlist_of_unsigned_integers,
				      string_constant_5,Qvalue,T,
				      result_of_read,Nil,Nil);
			  value = result_of_read;
			POP_SPECIAL();
		    }
		    else {
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_9:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_9;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_9;
		      end_loop_9:
			value = ab_loopvar_;
			goto end_9;
			value = Qnil;
		      end_9:;
		    }
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(color_value);
			resumable_icp_push(top_edge_in_graph_rendering);
			resumable_icp_push(left_edge_in_graph_rendering);
			resumable_icp_push(graph_rendering);
			resumable_icp_push(grid_background_color_value);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qcolor_values_for_rasters_qm,
				string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    color_values_for_rasters_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_10:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_10;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_10;
		      end_loop_10:
			result_of_read = ab_loopvar_;
			goto end_10;
			result_of_read = Qnil;
		      end_10:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_11:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_11;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_11;
		    end_loop_11:
		      value = ab_loopvar_;
		      goto end_11;
		      value = Qnil;
		    end_11:;
		  }
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(color_value);
		      resumable_icp_push(top_edge_in_graph_rendering);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  color_values_for_rasters_qm = value;
	      }
	      add_from_graph_rendering_to_current_window(subtract_instead_qm,
		      clipped_left_edge,clipped_top_edge,
		      clipped_right_edge,clipped_bottom_edge,
		      grid_background_color_value,graph_rendering,
		      left_edge_in_graph_rendering,
		      top_edge_in_graph_rendering,color_value,
		      color_values_for_rasters_qm);
	      result_of_read = 
		      reclaim_gensym_list_1(color_values_for_rasters_qm);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qadd_from_graph_rendering_to_current_window,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		subtract_instead_qm = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qsubtract_instead_qm,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_boolean();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qsubtract_instead_qm,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  subtract_instead_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_boolean();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		subtract_instead_qm = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		clipped_left_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_left_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_left_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_left_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		clipped_left_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		clipped_top_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_top_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_top_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_top_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		clipped_top_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		clipped_right_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_right_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_right_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_right_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		clipped_right_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		clipped_bottom_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qclipped_bottom_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qclipped_bottom_edge,string_constant_2,
			      Qargument,T,result_of_read,Nil,Nil);
		  clipped_bottom_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		clipped_bottom_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		grid_background_color_value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qgrid_background_color_value,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgrid_background_color_value,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  grid_background_color_value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(clipped_bottom_edge);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		grid_background_color_value = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(grid_background_color_value);
			  resumable_icp_push(clipped_bottom_edge);
			  resumable_icp_push(clipped_right_edge);
			  resumable_icp_push(clipped_top_edge);
			  resumable_icp_push(clipped_left_edge);
			  resumable_icp_push(subtract_instead_qm);
			  resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_add_from_graph_rendering_to_current_window;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(grid_background_color_value);
			resumable_icp_push(clipped_bottom_edge);
			resumable_icp_push(clipped_right_edge);
			resumable_icp_push(clipped_top_edge);
			resumable_icp_push(clipped_left_edge);
			resumable_icp_push(subtract_instead_qm);
			resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_add_from_graph_rendering_to_current_window;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		left_edge_in_graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qleft_edge_in_graph_rendering,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge_in_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  left_edge_in_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(grid_background_color_value);
		    resumable_icp_push(clipped_bottom_edge);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		left_edge_in_graph_rendering = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		top_edge_in_graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qtop_edge_in_graph_rendering,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge_in_graph_rendering,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  top_edge_in_graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(left_edge_in_graph_rendering);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(grid_background_color_value);
		    resumable_icp_push(clipped_bottom_edge);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		top_edge_in_graph_rendering = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		color_value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qcolor_value,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge_in_graph_rendering);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_value,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  color_value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(top_edge_in_graph_rendering);
		    resumable_icp_push(left_edge_in_graph_rendering);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(grid_background_color_value);
		    resumable_icp_push(clipped_bottom_edge);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		color_value = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		color_values_for_rasters_qm = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qcolor_values_for_rasters_qm,string_constant_2,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			1);
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)4L ? T : Nil;
		      if (tracep_1) {
			  emit_icp_read_trace(T,Nil,Nil,
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			  byte_count_before_1 = 
				  instantaneous_icp_reader_byte_count();
		      }
		      else
			  byte_count_before_1 = Nil;
		      current_icp_read_trace_level = 
			      FIXNUM_ADD1(Current_icp_read_trace_level);
		      PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			      0);
			ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
			ab_loopvar_ = Nil;
			ab_loopvar__1 = Nil;
			ab_loopvar__2 = Nil;
		      next_loop_12:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_12;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			ab_loopvar__2 = 
				gensym_cons_1(read_icp_unsigned_integer(),Nil);
			if (ab_loopvar__1)
			    M_CDR(ab_loopvar__1) = ab_loopvar__2;
			else
			    ab_loopvar_ = ab_loopvar__2;
			ab_loopvar__1 = ab_loopvar__2;
			goto next_loop_12;
		      end_loop_12:
			result_of_read = ab_loopvar_;
			goto end_12;
			result_of_read = Qnil;
		      end_12:;
			if (tracep_1)
			    emit_icp_read_trace(Nil,byte_count_before_1,
				    instantaneous_icp_reader_byte_count(),
				    Qlist_of_unsigned_integers,
				    string_constant_5,Qvalue,T,
				    result_of_read,Nil,Nil);
			value = result_of_read;
		      POP_SPECIAL();
		  }
		  else {
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_13:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_13;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_13;
		    end_loop_13:
		      value = ab_loopvar_;
		      goto end_13;
		      value = Qnil;
		    end_13:;
		  }
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(color_value);
		      resumable_icp_push(top_edge_in_graph_rendering);
		      resumable_icp_push(left_edge_in_graph_rendering);
		      resumable_icp_push(graph_rendering);
		      resumable_icp_push(grid_background_color_value);
		      resumable_icp_push(clipped_bottom_edge);
		      resumable_icp_push(clipped_right_edge);
		      resumable_icp_push(clipped_top_edge);
		      resumable_icp_push(clipped_left_edge);
		      resumable_icp_push(subtract_instead_qm);
		      resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_add_from_graph_rendering_to_current_window;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qcolor_values_for_rasters_qm,
			      string_constant_2,Qargument,T,result_of_read,
			      Nil,Nil);
		  color_values_for_rasters_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)4L ? T : Nil;
		    if (tracep) {
			emit_icp_read_trace(T,Nil,Nil,
				Qlist_of_unsigned_integers,
				string_constant_5,Qvalue,Nil,Nil,Nil,Nil);
			byte_count_before = 
				instantaneous_icp_reader_byte_count();
		    }
		    else
			byte_count_before = Nil;
		    current_icp_read_trace_level = 
			    FIXNUM_ADD1(Current_icp_read_trace_level);
		    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			    0);
		      ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		      ab_loopvar_ = Nil;
		      ab_loopvar__1 = Nil;
		      ab_loopvar__2 = Nil;
		    next_loop_14:
		      if ( !((SI_Long)0L < ab_loop_repeat_))
			  goto end_loop_14;
		      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		      ab_loopvar__2 = 
			      gensym_cons_1(read_icp_unsigned_integer(),Nil);
		      if (ab_loopvar__1)
			  M_CDR(ab_loopvar__1) = ab_loopvar__2;
		      else
			  ab_loopvar_ = ab_loopvar__2;
		      ab_loopvar__1 = ab_loopvar__2;
		      goto next_loop_14;
		    end_loop_14:
		      result_of_read = ab_loopvar_;
		      goto end_14;
		      result_of_read = Qnil;
		    end_14:;
		      if (tracep)
			  emit_icp_read_trace(Nil,byte_count_before,
				  instantaneous_icp_reader_byte_count(),
				  Qlist_of_unsigned_integers,
				  string_constant_5,Qvalue,T,
				  result_of_read,Nil,Nil);
		      value = result_of_read;
		    POP_SPECIAL();
		}
		else {
		    ab_loop_repeat_ = IFIX(read_icp_unsigned_integer());
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_15:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_15;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    ab_loopvar__2 = 
			    gensym_cons_1(read_icp_unsigned_integer(),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_15;
		  end_loop_15:
		    value = ab_loopvar_;
		    goto end_15;
		    value = Qnil;
		  end_15:;
		}
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(color_value);
		    resumable_icp_push(top_edge_in_graph_rendering);
		    resumable_icp_push(left_edge_in_graph_rendering);
		    resumable_icp_push(graph_rendering);
		    resumable_icp_push(grid_background_color_value);
		    resumable_icp_push(clipped_bottom_edge);
		    resumable_icp_push(clipped_right_edge);
		    resumable_icp_push(clipped_top_edge);
		    resumable_icp_push(clipped_left_edge);
		    resumable_icp_push(subtract_instead_qm);
		    resumable_icp_push(Qhandle_icp_add_from_graph_rendering_to_current_window);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_add_from_graph_rendering_to_current_window;
		}
		color_values_for_rasters_qm = value;
	    }
	    add_from_graph_rendering_to_current_window(subtract_instead_qm,
		    clipped_left_edge,clipped_top_edge,clipped_right_edge,
		    clipped_bottom_edge,grid_background_color_value,
		    graph_rendering,left_edge_in_graph_rendering,
		    top_edge_in_graph_rendering,color_value,
		    color_values_for_rasters_qm);
	    reclaim_gensym_list_1(color_values_for_rasters_qm);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_add_from_graph_rendering_to_current_window:
    return result;
}

/* MAKE-GRAPH-RENDERING-STRUCTURE */
Object make_graph_rendering_structure(width_of_graph_rendering_structure)
    Object width_of_graph_rendering_structure;
{
    Object ring_raster_for_graph;

    x_note_fn_call(53,45);
    ring_raster_for_graph = make_ring_raster_for_graph_1();
    ISVREF(ring_raster_for_graph,(SI_Long)2L) = FIX((SI_Long)0L);
    SVREF(ring_raster_for_graph,FIX((SI_Long)3L)) = 
	    width_of_graph_rendering_structure;
    return VALUES_1(ring_raster_for_graph);
}

static Object Qupdate_graph_dateline;  /* update-graph-dateline */

static Object Qdateline;           /* dateline */

static Object Qerase_dateline;     /* erase-dateline */

/* UPDATE-GRAPH-DATELINE */
Object update_graph_dateline(dateline,erase_dateline,graph_rendering)
    Object dateline, erase_dateline, graph_rendering;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, key, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,46);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qupdate_graph_dateline;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qupdate_graph_dateline);
	      temp_1 = getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if (temp_1);
	      else
		  temp_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
	      graph_rendering = temp_1;
	      start_writing_icp_message(FIX((SI_Long)153L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_graph_dateline,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qdateline,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(dateline);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qdateline,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(dateline);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qerase_dateline,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(erase_dateline);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qerase_dateline,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(erase_dateline);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = 
				  write_icp_corresponding_object_index(graph_rendering);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_graph_dateline,string_constant_1,
				Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qdateline,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(dateline);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qdateline,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(dateline);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qerase_dateline,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(erase_dateline);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qerase_dateline,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(erase_dateline);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = 
				write_icp_corresponding_object_index(graph_rendering);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_corresponding_object_index(graph_rendering);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)153L));
	      FUNCALL_3(temp_1,dateline,erase_dateline,graph_rendering);
	  }
	  else {
	      temp = ISVREF(graph_rendering,(SI_Long)7L);
	      SVREF(temp,FIX((SI_Long)2L)) = dateline;
	      temp = ISVREF(graph_rendering,(SI_Long)7L);
	      SVREF(temp,FIX((SI_Long)3L)) = erase_dateline;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qupdate_graph_dateline,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qupdate_graph_dateline,top,Nil);
		goto end_update_graph_dateline;
	    }
	}
	dateline = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : dateline;
	erase_dateline = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : erase_dateline;
	graph_rendering = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : graph_rendering;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qupdate_graph_dateline;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			case 3:
			  goto l3;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qupdate_graph_dateline);
	    l1:
	      value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		       TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : 
		      getfq_function_no_default(ISVREF(graph_rendering,
		      (SI_Long)5L),Current_icp_port);
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) && value)
		  graph_rendering = value;
	      else {
		  value_1 = 
			  make_corresponding_icp_graph_rendering(graph_rendering);
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(value);
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  graph_rendering = value_1;
	      }
	    l2:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)153L)))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l3:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_graph_dateline,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      case 3:
				goto l3_1;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qdateline,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,write_icp_integer(dateline))) {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qdateline,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,write_icp_integer(dateline))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qerase_dateline,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_integer(erase_dateline))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qerase_dateline,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_integer(erase_dateline))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l3_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				  write_icp_corresponding_object_index(graph_rendering))) 
				      {
			      resumable_icp_push(FIX((SI_Long)3L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qgraph_rendering,string_constant_3,
				      Qargument,Nil,Nil,Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(graph_rendering))) 
				{
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_graph_dateline,string_constant_1,
				Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    case 3:
			      goto l3_2;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qdateline,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,write_icp_integer(dateline))) {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qdateline,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,write_icp_integer(dateline))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qerase_dateline,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_integer(erase_dateline))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qerase_dateline,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			      write_icp_integer(erase_dateline))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l3_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qgraph_rendering,
				  string_constant_3,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,
				write_icp_corresponding_object_index(graph_rendering))) 
				    {
			    resumable_icp_push(FIX((SI_Long)3L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qgraph_rendering,string_constant_3,
				    Qargument,Nil,Nil,Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,
			  write_icp_corresponding_object_index(graph_rendering))) 
			      {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(graph_rendering);
		  resumable_icp_push(erase_dateline);
		  resumable_icp_push(dateline);
		  resumable_icp_push(Qupdate_graph_dateline);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_update_graph_dateline;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)153L));
	      FUNCALL_3(temp_1,dateline,erase_dateline,graph_rendering);
	  }
	  else {
	      temp = ISVREF(graph_rendering,(SI_Long)7L);
	      SVREF(temp,FIX((SI_Long)2L)) = dateline;
	      temp = ISVREF(graph_rendering,(SI_Long)7L);
	      SVREF(temp,FIX((SI_Long)3L)) = erase_dateline;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_update_graph_dateline:
    return result;
}

static Object Qhandle_icp_update_graph_dateline;  /* handle-icp-update-graph-dateline */

/* HANDLE-ICP-UPDATE-GRAPH-DATELINE */
Object handle_icp_update_graph_dateline()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, dateline, erase_dateline;
    Object index_1, index_space, graph_rendering, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,47);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qupdate_graph_dateline,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qdateline,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qdateline,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    dateline = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  dateline = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerase_dateline,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerase_dateline,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    erase_dateline = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  erase_dateline = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    index_1 = read_icp_corresponding_object_index();
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      result_of_read = update_graph_dateline(dateline,
		      erase_dateline,graph_rendering);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_graph_dateline,string_constant_4,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qdateline,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qdateline,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  dateline = result_of_read;
		POP_SPECIAL();
	    }
	    else
		dateline = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerase_dateline,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerase_dateline,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  erase_dateline = result_of_read;
		POP_SPECIAL();
	    }
	    else
		erase_dateline = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  index_1 = read_icp_corresponding_object_index();
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		index_1 = read_icp_corresponding_object_index();
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    update_graph_dateline(dateline,erase_dateline,graph_rendering);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_update_graph_dateline,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_update_graph_dateline,top,Nil);
		goto end_handle_icp_update_graph_dateline;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qupdate_graph_dateline,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  dateline = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qdateline,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_update_graph_dateline);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_dateline;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qdateline,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    dateline = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_graph_dateline);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_dateline;
		  }
		  dateline = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  erase_dateline = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qerase_dateline,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(dateline);
			resumable_icp_push(Qhandle_icp_update_graph_dateline);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_dateline;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qerase_dateline,string_constant_2,
				Qargument,T,result_of_read,Nil,Nil);
		    erase_dateline = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(dateline);
		      resumable_icp_push(Qhandle_icp_update_graph_dateline);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_dateline;
		  }
		  erase_dateline = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  graph_rendering = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			      string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    if ((resumable_icp_state_1 ? 
			    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
			    !TRUEP(resumable_icp_pop_list_if_end_marker()))
			index_1 = resumable_icp_pop();
		    else {
			value = read_icp_corresponding_object_index();
			if (EQ(icp_suspend_1,value)) {
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(Qresumable_icp_list_end);
			    resumable_icp_push(erase_dateline);
			    resumable_icp_push(dateline);
			    resumable_icp_push(Qhandle_icp_update_graph_dateline);
			    result = VALUES_1(Icp_suspend);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_handle_icp_update_graph_dateline;
			}
			index_1 = value;
		    }
		    index_space = Current_temporary_icp_object_index_space;
		    if (index_space);
		    else
			index_space = Current_standard_icp_object_index_space;
		    if (FIXNUMP(index_1)) {
			if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			    enlarge_index_space(index_space,index_1);
			result_of_read = ISVREF(ISVREF(ISVREF(index_space,
				(SI_Long)2L),IFIX(index_1) >>  -  - 
				(SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		    }
		    else
			result_of_read = Nil;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qgraph_rendering,string_constant_3,
				Qargument,T,result_of_read,Nil,Nil);
		    graph_rendering = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(erase_dateline);
			  resumable_icp_push(dateline);
			  resumable_icp_push(Qhandle_icp_update_graph_dateline);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_graph_dateline;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      graph_rendering = Nil;
	      }
	      result_of_read = update_graph_dateline(dateline,
		      erase_dateline,graph_rendering);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_graph_dateline,string_constant_4,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		dateline = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qdateline,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_graph_dateline);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_dateline;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qdateline,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  dateline = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_update_graph_dateline);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_dateline;
		}
		dateline = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		erase_dateline = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qerase_dateline,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(dateline);
		      resumable_icp_push(Qhandle_icp_update_graph_dateline);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_dateline;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qerase_dateline,string_constant_2,Qargument,
			      T,result_of_read,Nil,Nil);
		  erase_dateline = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(dateline);
		    resumable_icp_push(Qhandle_icp_update_graph_dateline);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_dateline;
		}
		erase_dateline = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		graph_rendering = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qgraph_rendering,
			    string_constant_3,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
			   TRUEP(Nil)) &&  
			  !TRUEP(resumable_icp_pop_list_if_end_marker()))
		      index_1 = resumable_icp_pop();
		  else {
		      value = read_icp_corresponding_object_index();
		      if (EQ(icp_suspend_1,value)) {
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(Qresumable_icp_list_end);
			  resumable_icp_push(erase_dateline);
			  resumable_icp_push(dateline);
			  resumable_icp_push(Qhandle_icp_update_graph_dateline);
			  result = VALUES_1(Icp_suspend);
			  POP_SPECIAL();
			  goto end_handle_icp_update_graph_dateline;
		      }
		      index_1 = value;
		  }
		  index_space = Current_temporary_icp_object_index_space;
		  if (index_space);
		  else
		      index_space = Current_standard_icp_object_index_space;
		  if (FIXNUMP(index_1)) {
		      if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			  enlarge_index_space(index_space,index_1);
		      result_of_read = ISVREF(ISVREF(ISVREF(index_space,
			      (SI_Long)2L),IFIX(index_1) >>  -  - 
			      (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		  }
		  else
		      result_of_read = Nil;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qgraph_rendering,string_constant_3,Qargument,
			      T,result_of_read,Nil,Nil);
		  graph_rendering = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) &&  
			!TRUEP(resumable_icp_pop_list_if_end_marker()))
		    index_1 = resumable_icp_pop();
		else {
		    value = read_icp_corresponding_object_index();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(erase_dateline);
			resumable_icp_push(dateline);
			resumable_icp_push(Qhandle_icp_update_graph_dateline);
			result = VALUES_1(Icp_suspend);
			goto end_handle_icp_update_graph_dateline;
		    }
		    index_1 = value;
		}
		index_space = Current_temporary_icp_object_index_space;
		if (index_space);
		else
		    index_space = Current_standard_icp_object_index_space;
		if (FIXNUMP(index_1)) {
		    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
			enlarge_index_space(index_space,index_1);
		    graph_rendering = ISVREF(ISVREF(ISVREF(index_space,
			    (SI_Long)2L),IFIX(index_1) >>  -  - 
			    (SI_Long)10L),IFIX(index_1) & (SI_Long)1023L);
		}
		else
		    graph_rendering = Nil;
	    }
	    update_graph_dateline(dateline,erase_dateline,graph_rendering);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_update_graph_dateline:
    return result;
}

static Object Qupdate_graph_data_extrema;  /* update-graph-data-extrema */

static Object Qleft_edge;          /* left-edge */

static Object Qtop_edge;           /* top-edge */

static Object Qright_edge;         /* right-edge */

static Object Qbottom_edge;        /* bottom-edge */

/* UPDATE-GRAPH-DATA-EXTREMA */
Object update_graph_data_extrema(left_edge,top_edge,right_edge,bottom_edge)
    Object left_edge, top_edge, right_edge, bottom_edge;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top, key;
    Declare_special(3);
    Object result;

    x_note_fn_call(53,48);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qupdate_graph_data_extrema;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qupdate_graph_data_extrema);
	      start_writing_icp_message(FIX((SI_Long)154L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_graph_data_extrema,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qleft_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(left_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qleft_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(left_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qtop_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(top_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qtop_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(top_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qright_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(right_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qright_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			write_icp_integer(right_edge);
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qbottom_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  result_of_write = write_icp_integer(bottom_edge);
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qbottom_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else
			result_of_write = write_icp_integer(bottom_edge);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_graph_data_extrema,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else {
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qleft_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(left_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qleft_edge,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(left_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qtop_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(top_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qtop_edge,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(top_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qright_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(right_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qright_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(right_edge);
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qbottom_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			result_of_write = write_icp_integer(bottom_edge);
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qbottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else
		      write_icp_integer(bottom_edge);
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)154L));
	      FUNCALL_4(temp_1,left_edge,top_edge,right_edge,bottom_edge);
	  }
	  else
	      Clipping_rectangles_for_new_data_qm = 
		      nconc2(gensym_list_4(left_edge,top_edge,right_edge,
		      bottom_edge),Clipping_rectangles_for_new_data_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qupdate_graph_data_extrema,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qupdate_graph_data_extrema,top,Nil);
		goto end_update_graph_data_extrema;
	    }
	}
	left_edge = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : left_edge;
	top_edge = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : top_edge;
	right_edge = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : right_edge;
	bottom_edge = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		 TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : bottom_edge;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qupdate_graph_data_extrema;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1;
			  break;
			case 2:
			  goto l2;
			  break;
			default:
			  break;
		      }
	      }
	      icp_message_functions_icp_prologue(Qupdate_graph_data_extrema);
	    l1:
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)154L)))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	    l2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qupdate_graph_data_extrema,string_constant_1,
			      Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  1);
		    if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
			    : TRUEP(Nil)) {
			temp_1 = resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1_1;
				break;
			      case 2:
				goto l2_1;
				break;
			      case 3:
				goto l3;
				break;
			      case 4:
				goto l4;
				break;
			      default:
				break;
			    }
		    }
		  l1_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qleft_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,write_icp_integer(left_edge))) {
			      resumable_icp_push(FIX((SI_Long)1L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qleft_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,write_icp_integer(left_edge))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l2_1:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qtop_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,write_icp_integer(top_edge))) {
			      resumable_icp_push(FIX((SI_Long)2L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qtop_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,write_icp_integer(top_edge))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l3:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qright_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				      write_icp_integer(right_edge))) {
			      resumable_icp_push(FIX((SI_Long)3L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qright_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,write_icp_integer(right_edge))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		  l4:
		    if (Icp_write_trace_cutoff_level_qm) {
			tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? 
				T : Nil;
			if (tracep_1);
			else
			    tracep_1 = 
				    IFIX(Icp_write_trace_cutoff_level_qm) 
				    >= (SI_Long)3L ? T : Nil;
			if (tracep_1) {
			    emit_icp_write_trace(T,Nil,Nil,Qbottom_edge,
				    string_constant_2,Qargument,Nil,Nil,
				    Nil,Nil);
			    byte_count_before_1 = 
				    instantaneous_icp_writer_byte_count();
			}
			else
			    byte_count_before_1 = Nil;
			current_icp_write_trace_level = 
				FIXNUM_ADD1(Current_icp_write_trace_level);
			PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
				0);
			  if (EQ(icp_suspend_1,
				      write_icp_integer(bottom_edge))) {
			      resumable_icp_push(FIX((SI_Long)4L));
			      temp_1 = Icp_suspend;
			      POP_SPECIAL();
			      goto end_block_1;
			  }
			  else
			      result_of_write = Nil;
			  if (tracep_1)
			      emit_icp_write_trace(Nil,byte_count_before_1,
				      instantaneous_icp_writer_byte_count(),
				      Qbottom_edge,string_constant_2,
				      Qargument,Nil,Nil,Nil,Nil);
			  temp_1 = result_of_write;
			POP_SPECIAL();
		    }
		    else if (EQ(icp_suspend_1,
				write_icp_integer(bottom_edge))) {
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			goto end_block_1;
		    }
		    else
			temp_1 = Nil;
		    goto end_block_1;
		  end_block_1:
		    if (EQ(icp_suspend_1,temp_1)) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qupdate_graph_data_extrema,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else {
		  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			  TRUEP(Nil)) {
		      temp_1 = resumable_icp_pop();
		      if (! !(FIXNUMP(temp_1) && 
			      FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			      FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			  switch (INTEGER_TO_CHAR(temp_1)) {
			    case 1:
			      goto l1_2;
			      break;
			    case 2:
			      goto l2_2;
			      break;
			    case 3:
			      goto l3_1;
			      break;
			    case 4:
			      goto l4_1;
			      break;
			    default:
			      break;
			  }
		  }
		l1_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qleft_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,write_icp_integer(left_edge))) {
			    resumable_icp_push(FIX((SI_Long)1L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qleft_edge,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,write_icp_integer(left_edge))) {
		      resumable_icp_push(FIX((SI_Long)1L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l2_2:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qtop_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,write_icp_integer(top_edge))) {
			    resumable_icp_push(FIX((SI_Long)2L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qtop_edge,string_constant_2,Qargument,
				    Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,write_icp_integer(top_edge))) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l3_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qright_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,write_icp_integer(right_edge))) {
			    resumable_icp_push(FIX((SI_Long)3L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qright_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,write_icp_integer(right_edge))) {
		      resumable_icp_push(FIX((SI_Long)3L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		l4_1:
		  if (Icp_write_trace_cutoff_level_qm) {
		      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		      if (tracep);
		      else
			  tracep = IFIX(Icp_write_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		      if (tracep) {
			  emit_icp_write_trace(T,Nil,Nil,Qbottom_edge,
				  string_constant_2,Qargument,Nil,Nil,Nil,Nil);
			  byte_count_before = 
				  instantaneous_icp_writer_byte_count();
		      }
		      else
			  byte_count_before = Nil;
		      current_icp_write_trace_level = 
			      FIXNUM_ADD1(Current_icp_write_trace_level);
		      PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			      0);
			if (EQ(icp_suspend_1,write_icp_integer(bottom_edge))) {
			    resumable_icp_push(FIX((SI_Long)4L));
			    temp_1 = Icp_suspend;
			    POP_SPECIAL();
			    goto end_block_2;
			}
			else
			    result_of_write = Nil;
			if (tracep)
			    emit_icp_write_trace(Nil,byte_count_before,
				    instantaneous_icp_writer_byte_count(),
				    Qbottom_edge,string_constant_2,
				    Qargument,Nil,Nil,Nil,Nil);
			temp_1 = result_of_write;
		      POP_SPECIAL();
		  }
		  else if (EQ(icp_suspend_1,write_icp_integer(bottom_edge))) {
		      resumable_icp_push(FIX((SI_Long)4L));
		      temp_1 = Icp_suspend;
		      goto end_block_2;
		  }
		  else
		      temp_1 = Nil;
		  goto end_block_2;
		end_block_2:
		  if (EQ(icp_suspend_1,temp_1)) {
		      resumable_icp_push(FIX((SI_Long)2L));
		      temp_1 = Icp_suspend;
		      goto end_block;
		  }
		  else
		      temp_1 = Nil;
	      }
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(key);
		  resumable_icp_push(bottom_edge);
		  resumable_icp_push(right_edge);
		  resumable_icp_push(top_edge);
		  resumable_icp_push(left_edge);
		  resumable_icp_push(Qupdate_graph_data_extrema);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_update_graph_data_extrema;
	      }
	  }
	  else if (EQ(key,Qprinter)) {
	      temp_1 = aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)154L));
	      FUNCALL_4(temp_1,left_edge,top_edge,right_edge,bottom_edge);
	  }
	  else
	      Clipping_rectangles_for_new_data_qm = 
		      nconc2(gensym_list_4(left_edge,top_edge,right_edge,
		      bottom_edge),Clipping_rectangles_for_new_data_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_update_graph_data_extrema:
    return result;
}

static Object Qhandle_icp_update_graph_data_extrema;  /* handle-icp-update-graph-data-extrema */

/* HANDLE-ICP-UPDATE-GRAPH-DATA-EXTREMA */
Object handle_icp_update_graph_data_extrema()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, left_edge, top_edge;
    Object right_edge, bottom_edge, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,49);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qupdate_graph_data_extrema,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qleft_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    left_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  left_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtop_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    top_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  top_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qright_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qright_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    right_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  right_edge = read_icp_integer();
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qbottom_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_integer();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qbottom_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    bottom_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  bottom_edge = read_icp_integer();
	      result_of_read = update_graph_data_extrema(left_edge,
		      top_edge,right_edge,bottom_edge);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_graph_data_extrema,string_constant_4,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qleft_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  left_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		left_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtop_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  top_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		top_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qright_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qright_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  right_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		right_edge = read_icp_integer();
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qbottom_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_integer();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qbottom_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  bottom_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else
		bottom_edge = read_icp_integer();
	    update_graph_data_extrema(left_edge,top_edge,right_edge,
		    bottom_edge);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_update_graph_data_extrema,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qhandle_icp_update_graph_data_extrema,top,Nil);
		goto end_handle_icp_update_graph_data_extrema;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qupdate_graph_data_extrema,
			string_constant_4,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  left_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qleft_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_data_extrema;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qleft_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    left_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  left_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  top_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtop_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(left_edge);
			resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_data_extrema;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtop_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    top_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  top_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  right_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qright_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(top_edge);
			resumable_icp_push(left_edge);
			resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_data_extrema;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qright_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    right_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  right_edge = value;
	      }
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  bottom_edge = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qbottom_edge,
			      string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_integer();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(right_edge);
			resumable_icp_push(top_edge);
			resumable_icp_push(left_edge);
			resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_update_graph_data_extrema;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qbottom_edge,string_constant_2,Qargument,T,
				result_of_read,Nil,Nil);
		    bottom_edge = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(right_edge);
		      resumable_icp_push(top_edge);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  bottom_edge = value;
	      }
	      result_of_read = update_graph_data_extrema(left_edge,
		      top_edge,right_edge,bottom_edge);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qupdate_graph_data_extrema,string_constant_4,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		left_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qleft_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qleft_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  left_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_data_extrema;
		}
		left_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		top_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtop_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtop_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  top_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(left_edge);
		    resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_data_extrema;
		}
		top_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		right_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qright_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(top_edge);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qright_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  right_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(top_edge);
		    resumable_icp_push(left_edge);
		    resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_data_extrema;
		}
		right_edge = value;
	    }
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		bottom_edge = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qbottom_edge,
			    string_constant_2,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(right_edge);
		      resumable_icp_push(top_edge);
		      resumable_icp_push(left_edge);
		      resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_update_graph_data_extrema;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qbottom_edge,string_constant_2,Qargument,T,
			      result_of_read,Nil,Nil);
		  bottom_edge = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(right_edge);
		    resumable_icp_push(top_edge);
		    resumable_icp_push(left_edge);
		    resumable_icp_push(Qhandle_icp_update_graph_data_extrema);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_update_graph_data_extrema;
		}
		bottom_edge = value;
	    }
	    update_graph_data_extrema(left_edge,top_edge,right_edge,
		    bottom_edge);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_update_graph_data_extrema:
    return result;
}

static Object Qclear_data_clipping_rectangles;  /* clear-data-clipping-rectangles */

/* CLEAR-DATA-CLIPPING-RECTANGLES */
Object clear_data_clipping_rectangles()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top, key;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,50);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qclear_data_clipping_rectangles;
	  }
	  if (EQ(Type_of_current_window,Qicp)) {
	      icp_message_functions_icp_prologue(Qclear_data_clipping_rectangles);
	      start_writing_icp_message(FIX((SI_Long)162L));
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qclear_data_clipping_rectangles,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qclear_data_clipping_rectangles,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	  }
	  else if (EQ(Type_of_current_window,Qprinter))
	      FUNCALL_0(aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)162L)));
	  else {
	      reclaim_gensym_list_1(Clipping_rectangles_for_new_data_qm);
	      Clipping_rectangles_for_new_data_qm = Nil;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qclear_data_clipping_rectangles,top)) {
		result = icp_error_internal(Qerror,string_constant,
			Qclear_data_clipping_rectangles,top,Nil);
		goto end_clear_data_clipping_rectangles;
	    }
	}
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		1);
	  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
		  Size_of_basic_backtrace_information),
		  Maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	      Index_of_top_of_backtrace_stack = temp;
	      temp = Backtrace_stack_for_internal_error;
	      svref_arg_2 = Index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qclear_data_clipping_rectangles;
	  }
	  key = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : Type_of_current_window;
	  if (EQ(key,Qicp)) {
	      if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)))
		  icp_message_functions_icp_prologue(Qclear_data_clipping_rectangles);
	      if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)162L)))) {
		  resumable_icp_push(key);
		  resumable_icp_push(Qclear_data_clipping_rectangles);
		  result = VALUES_1(Icp_suspend);
		  POP_SPECIAL();
		  goto end_clear_data_clipping_rectangles;
	      }
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)2L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qclear_data_clipping_rectangles,
			      string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL(Current_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qclear_data_clipping_rectangles,
				string_constant_1,Qmessage,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	  }
	  else if (EQ(key,Qprinter))
	      FUNCALL_0(aref1(Icp_printing_message_handler_array,
		      FIX((SI_Long)162L)));
	  else {
	      reclaim_gensym_list_1(Clipping_rectangles_for_new_data_qm);
	      Clipping_rectangles_for_new_data_qm = Nil;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_clear_data_clipping_rectangles:
    return result;
}

static Object Qhandle_icp_clear_data_clipping_rectangles;  /* handle-icp-clear-data-clipping-rectangles */

/* HANDLE-ICP-CLEAR-DATA-CLIPPING-RECTANGLES */
Object handle_icp_clear_data_clipping_rectangles()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object result_of_read, temp, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(53,51);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qclear_data_clipping_rectangles,string_constant_4,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = clear_data_clipping_rectangles();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qclear_data_clipping_rectangles,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else
	    clear_data_clipping_rectangles();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_clear_data_clipping_rectangles,top))
		return icp_error_internal(Qerror,string_constant,
			Qhandle_icp_clear_data_clipping_rectangles,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qclear_data_clipping_rectangles,string_constant_4,
			Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL(Current_icp_read_trace_level,current_icp_read_trace_level,
		    0);
	      result_of_read = clear_data_clipping_rectangles();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qclear_data_clipping_rectangles,
			  string_constant_4,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else
	    clear_data_clipping_rectangles();
	temp = Nil;
    }
    return VALUES_1(temp);
}

void windows3a_INIT()
{
    Object temp, reclaim_structure_for_graph_rendering_1, new_entry;
    Object entry_cons, reclaim_structure_for_ring_raster_for_graph_1;
    Object aref_arg_1;
    Object AB_package, Qhandler_for_printing_clear_data_clipping_rectangles;
    Object Qhandler_for_printing_update_graph_data_extrema;
    Object Qhandler_for_printing_update_graph_dateline;
    Object Qhandler_for_printing_add_from_graph_rendering_to_current_window;
    Object Qwindows3, Qclipping_rectangles_for_new_data_qm;
    Object Qhandler_for_printing_set_graph_rendering_foreground_only_mode;
    Object Qhandler_for_printing_update_ring_raster_for_graph_given_color_values_2;
    Object Qhandler_for_printing_update_ring_raster_for_graph_given_color_values;
    Object Qring_raster_for_graph, Qreclaim_structure;
    Object Qoutstanding_ring_raster_for_graph_count;
    Object Qring_raster_for_graph_structure_memory_usage, Qutilities2;
    Object Qring_raster_for_graph_count;
    Object Qchain_of_available_ring_raster_for_graphs, string_constant_9;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_8, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qreclaim_icp_port_entry_for_graph_rendering;
    Object Qreclaim_graph_rendering_and_raster_1, list_constant_6;
    Object list_constant_5, Qcorresponding_icp_object_map_for_graph_rendering;
    Object list_constant_4, Qgraph_rendering_lru_queue, Qmake_lru_queue;
    Object Kfuncall, Qwindow_for_graph_rendering;
    Object Qgraph_rendering_memory_limit_info, list_constant_3;
    Object list_constant_2, Qinitialize_memory_limit_info;
    Object Qoutstanding_graph_rendering_count;
    Object Qgraph_rendering_structure_memory_usage, Qgraph_rendering_count;
    Object Qchain_of_available_graph_renderings, string_constant_7;
    Object string_constant_6;

    x_note_fn_call(53,52);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_graph_rendering_g2_struct = 
	    STATIC_SYMBOL("GRAPH-RENDERING-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qgraph_rendering = STATIC_SYMBOL("GRAPH-RENDERING",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graph_rendering_g2_struct,
	    Qgraph_rendering,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qgraph_rendering,
	    Qg2_defstruct_structure_name_graph_rendering_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_graph_rendering == UNBOUND)
	The_type_description_of_graph_rendering = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l83ty1o83ty83Dy8m8k1l83Dy0000001m1n8n831sy1w831Yy830Gy834cy834ey830cy834Xy830fy834Wy830ey83*py834ay830Xy1m8p83Dyk3Hyk0k0");
    temp = The_type_description_of_graph_rendering;
    The_type_description_of_graph_rendering = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_graph_rendering_g2_struct,
	    The_type_description_of_graph_rendering,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qgraph_rendering,
	    The_type_description_of_graph_rendering,Qtype_description_of_type);
    Qoutstanding_graph_rendering_count = 
	    STATIC_SYMBOL("OUTSTANDING-GRAPH-RENDERING-COUNT",AB_package);
    Qgraph_rendering_structure_memory_usage = 
	    STATIC_SYMBOL("GRAPH-RENDERING-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_7 = STATIC_STRING("1q83ty8o8366y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_graph_rendering_count);
    push_optimized_constant(Qgraph_rendering_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_graph_renderings = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GRAPH-RENDERINGS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_graph_renderings,
	    Chain_of_available_graph_renderings);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_graph_renderings,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qgraph_rendering_count = STATIC_SYMBOL("GRAPH-RENDERING-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_rendering_count,Graph_rendering_count);
    record_system_variable(Qgraph_rendering_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qgraph_rendering_structure_memory_usage,
	    STATIC_FUNCTION(graph_rendering_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_graph_rendering_count,
	    STATIC_FUNCTION(outstanding_graph_rendering_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_graph_rendering_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_graph_rendering,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qgraph_rendering,
	    reclaim_structure_for_graph_rendering_1);
    Qgraph_rendering_memory_limit_info = 
	    STATIC_SYMBOL("GRAPH-RENDERING-MEMORY-LIMIT-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgraph_rendering_memory_limit_info,
	    Graph_rendering_memory_limit_info);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_memory_limit_info = 
	    STATIC_SYMBOL("INITIALIZE-MEMORY-LIMIT-INFO",AB_package);
    list_constant = STATIC_LIST((SI_Long)14L,FIX((SI_Long)4L),
	    FIX((SI_Long)8L),FIX((SI_Long)12L),FIX((SI_Long)16L),
	    FIX((SI_Long)24L),FIX((SI_Long)32L),FIX((SI_Long)56L),
	    FIX((SI_Long)64L),FIX((SI_Long)104L),FIX((SI_Long)128L),
	    FIX((SI_Long)152L),FIX((SI_Long)200L),FIX((SI_Long)256L),
	    FIX((SI_Long)400L));
    list_constant_2 = STATIC_LIST((SI_Long)4L,Kfuncall,
	    Qinitialize_memory_limit_info,list_constant,Qgraph_rendering);
    record_system_variable(Qgraph_rendering_memory_limit_info,Qutilities2,
	    list_constant_2,Qnil,Qnil,Qnil,Qnil);
    list_constant_3 = STATIC_CONS(Qgraph_rendering_memory_limit_info,Qnil);
    if ( !TRUEP(memq_function(Qgraph_rendering_memory_limit_info,
	    Memory_limit_variable_names_for_decacheable_structures)))
	Memory_limit_variable_names_for_decacheable_structures = 
		nconc2(Memory_limit_variable_names_for_decacheable_structures,
		list_constant_3);
    Qwindow_for_graph_rendering = 
	    STATIC_SYMBOL("WINDOW-FOR-GRAPH-RENDERING",AB_package);
    Qgraph_rendering_lru_queue = STATIC_SYMBOL("GRAPH-RENDERING-LRU-QUEUE",
	    AB_package);
    Qdecache_graph_rendering = STATIC_SYMBOL("DECACHE-GRAPH-RENDERING",
	    AB_package);
    new_entry = nconc2(LIST_5(Qgraph_rendering,
	    Qgraph_rendering_memory_limit_info,Qwindow_for_graph_rendering,
	    Qgraph_rendering_lru_queue,Qdecache_graph_rendering),
	    copy_list(list_constant));
    entry_cons = Names_and_sizes_for_decacheable_structures;
  next_loop:
    if ( !TRUEP(entry_cons))
	goto end_loop;
    if (EQ(CAAR(entry_cons),CAR(new_entry))) {
	temp = CAR(entry_cons);
	if ( !EQUAL(temp,new_entry))
	    M_CAR(entry_cons) = new_entry;
	goto end;
    }
    entry_cons = M_CDR(entry_cons);
    goto next_loop;
  end_loop:
    Names_and_sizes_for_decacheable_structures = 
	    nconc2(Names_and_sizes_for_decacheable_structures,
	    LIST_1(new_entry));
  end:;
    SET_SYMBOL_VALUE_LOCATION(Qgraph_rendering_lru_queue,
	    Graph_rendering_lru_queue);
    Qmake_lru_queue = STATIC_SYMBOL("MAKE-LRU-QUEUE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,Qmake_lru_queue);
    record_system_variable(Qgraph_rendering_lru_queue,Qutilities2,
	    list_constant_4,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qdecache_graph_rendering,
	    STATIC_FUNCTION(decache_graph_rendering,NIL,FALSE,1,1));
    Qcompute_cost_of_decaching_graph_rendering = 
	    STATIC_SYMBOL("COMPUTE-COST-OF-DECACHING-GRAPH-RENDERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_cost_of_decaching_graph_rendering,
	    STATIC_FUNCTION(compute_cost_of_decaching_graph_rendering,NIL,
	    FALSE,1,1));
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_graph_rendering = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-GRAPH-RENDERING",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_graph_rendering,
	    STATIC_FUNCTION(establish_new_object_index_for_graph_rendering,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_graph_rendering = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-GRAPH-RENDERING",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_graph_rendering,
	    STATIC_FUNCTION(make_corresponding_icp_graph_rendering,NIL,
	    FALSE,1,1));
    Qset_access_form_for_graph_rendering = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-GRAPH-RENDERING",AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_graph_rendering,
	    STATIC_FUNCTION(set_access_form_for_graph_rendering,NIL,FALSE,
	    2,2));
    Qcorresponding_icp_object_map_for_graph_rendering = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-GRAPH-RENDERING",
	    AB_package);
    list_constant_5 = STATIC_CONS(Qgraph_rendering,Qnil);
    list_constant_6 = 
	    STATIC_CONS(Qcorresponding_icp_object_map_for_graph_rendering,
	    list_constant_5);
    initialize_icp_object_type_compile(Qgraph_rendering,
	    Qstandard_icp_object_index_space,list_constant_6);
    Qreclaim_graph_rendering_and_raster_1 = 
	    STATIC_SYMBOL("RECLAIM-GRAPH-RENDERING-AND-RASTER-1",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_graph_rendering_and_raster_1,
	    STATIC_FUNCTION(reclaim_graph_rendering_and_raster_1,NIL,FALSE,
	    1,1));
    Qreclaim_icp_port_entry_for_graph_rendering = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-GRAPH-RENDERING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_graph_rendering,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_graph_rendering,NIL,
	    FALSE,2,2));
    initialize_icp_object_type(Qgraph_rendering,
	    Qreclaim_graph_rendering_and_raster_1,Qnil,
	    Qreclaim_icp_port_entry_for_graph_rendering);
    Qsend_icp_begin_making_graph_rendering = 
	    STATIC_SYMBOL("SEND-ICP-BEGIN-MAKING-GRAPH-RENDERING",AB_package);
    Qcorresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    Qbegin_making_graph_rendering = 
	    STATIC_SYMBOL("BEGIN-MAKING-GRAPH-RENDERING",AB_package);
    string_constant_1 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    Qcorresponding_icp_object_index = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-INDEX",AB_package);
    string_constant_2 = STATIC_STRING("[value arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    Qformat_of_graph_rendering_structure = 
	    STATIC_SYMBOL("FORMAT-OF-GRAPH-RENDERING-STRUCTURE",AB_package);
    string_constant_3 = STATIC_STRING("[object arg]");
    Qx_scale_of_graph_rendering = 
	    STATIC_SYMBOL("X-SCALE-OF-GRAPH-RENDERING",AB_package);
    Qy_scale_of_graph_rendering = 
	    STATIC_SYMBOL("Y-SCALE-OF-GRAPH-RENDERING",AB_package);
    Qgrid_border_width = STATIC_SYMBOL("GRID-BORDER-WIDTH",AB_package);
    Qwidth_of_graph_rendering_structure = 
	    STATIC_SYMBOL("WIDTH-OF-GRAPH-RENDERING-STRUCTURE",AB_package);
    Qheight_of_graph_rendering_structure = 
	    STATIC_SYMBOL("HEIGHT-OF-GRAPH-RENDERING-STRUCTURE",AB_package);
    Qwidth_of_rendered_graph = STATIC_SYMBOL("WIDTH-OF-RENDERED-GRAPH",
	    AB_package);
    Qheight_of_rendered_graph = STATIC_SYMBOL("HEIGHT-OF-RENDERED-GRAPH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_begin_making_graph_rendering,
	    STATIC_FUNCTION(send_icp_begin_making_graph_rendering,NIL,
	    FALSE,9,9));
    Qhandle_icp_begin_making_graph_rendering = 
	    STATIC_SYMBOL("HANDLE-ICP-BEGIN-MAKING-GRAPH-RENDERING",
	    AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_begin_making_graph_rendering,
	    STATIC_FUNCTION(handle_icp_begin_making_graph_rendering,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_begin_making_graph_rendering,
	    FIX((SI_Long)150L));
    Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct = 
	    STATIC_SYMBOL("RING-RASTER-FOR-GRAPH-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qring_raster_for_graph = STATIC_SYMBOL("RING-RASTER-FOR-GRAPH",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct,
	    Qring_raster_for_graph,Qab_name_of_unique_structure_type);
    mutate_global_property(Qring_raster_for_graph,
	    Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_ring_raster_for_graph == UNBOUND)
	The_type_description_of_ring_raster_for_graph = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8l83-by1n83-by8m8k1l8m0000000kpk0k0");
    temp = The_type_description_of_ring_raster_for_graph;
    The_type_description_of_ring_raster_for_graph = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    mutate_global_property(Qg2_defstruct_structure_name_ring_raster_for_graph_g2_struct,
	    The_type_description_of_ring_raster_for_graph,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qring_raster_for_graph,
	    The_type_description_of_ring_raster_for_graph,
	    Qtype_description_of_type);
    Qoutstanding_ring_raster_for_graph_count = 
	    STATIC_SYMBOL("OUTSTANDING-RING-RASTER-FOR-GRAPH-COUNT",
	    AB_package);
    Qring_raster_for_graph_structure_memory_usage = 
	    STATIC_SYMBOL("RING-RASTER-FOR-GRAPH-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q83-by8o8377y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_ring_raster_for_graph_count);
    push_optimized_constant(Qring_raster_for_graph_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_ring_raster_for_graphs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RING-RASTER-FOR-GRAPHS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_ring_raster_for_graphs,
	    Chain_of_available_ring_raster_for_graphs);
    record_system_variable(Qchain_of_available_ring_raster_for_graphs,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qring_raster_for_graph_count = 
	    STATIC_SYMBOL("RING-RASTER-FOR-GRAPH-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qring_raster_for_graph_count,
	    Ring_raster_for_graph_count);
    record_system_variable(Qring_raster_for_graph_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qring_raster_for_graph_structure_memory_usage,
	    STATIC_FUNCTION(ring_raster_for_graph_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_ring_raster_for_graph_count,
	    STATIC_FUNCTION(outstanding_ring_raster_for_graph_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_ring_raster_for_graph_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_ring_raster_for_graph,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qring_raster_for_graph,
	    reclaim_structure_for_ring_raster_for_graph_1);
    Qpolychrome_raster = STATIC_SYMBOL("POLYCHROME-RASTER",AB_package);
    list_constant_1 = STATIC_CONS(Qnil,Qnil);
    Qsend_icp_prepare_for_painting_graph = 
	    STATIC_SYMBOL("SEND-ICP-PREPARE-FOR-PAINTING-GRAPH",AB_package);
    Qprepare_for_painting_graph = 
	    STATIC_SYMBOL("PREPARE-FOR-PAINTING-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_prepare_for_painting_graph,
	    STATIC_FUNCTION(send_icp_prepare_for_painting_graph,NIL,FALSE,
	    1,1));
    Qmonochrome_raster_list = STATIC_SYMBOL("MONOCHROME-RASTER-LIST",
	    AB_package);
    Qhandle_icp_prepare_for_painting_graph = 
	    STATIC_SYMBOL("HANDLE-ICP-PREPARE-FOR-PAINTING-GRAPH",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_prepare_for_painting_graph,
	    STATIC_FUNCTION(handle_icp_prepare_for_painting_graph,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_prepare_for_painting_graph,
	    FIX((SI_Long)158L));
    Qhandler_for_printing_update_ring_raster_for_graph_given_color_values 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)157L),
	    Qhandler_for_printing_update_ring_raster_for_graph_given_color_values);
    Qupdate_ring_raster_for_graph_given_color_values = 
	    STATIC_SYMBOL("UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qnumber_of_rasters_needed = STATIC_SYMBOL("NUMBER-OF-RASTERS-NEEDED",
	    AB_package);
    Qprinter = STATIC_SYMBOL("PRINTER",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_ring_raster_for_graph_given_color_values,
	    STATIC_FUNCTION(update_ring_raster_for_graph_given_color_values,
	    NIL,FALSE,2,2));
    string_constant_4 = STATIC_STRING("[msg funct]");
    Qhandle_icp_update_ring_raster_for_graph_given_color_values = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_update_ring_raster_for_graph_given_color_values,
	    STATIC_FUNCTION(handle_icp_update_ring_raster_for_graph_given_color_values,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_update_ring_raster_for_graph_given_color_values,
	    FIX((SI_Long)157L));
    Qhandler_for_printing_update_ring_raster_for_graph_given_color_values_2 
	    = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)182L),
	    Qhandler_for_printing_update_ring_raster_for_graph_given_color_values_2);
    Qupdate_ring_raster_for_graph_given_color_values_2 = 
	    STATIC_SYMBOL("UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2",
	    AB_package);
    Qcolor_values_for_rasters_qm = 
	    STATIC_SYMBOL("COLOR-VALUES-FOR-RASTERS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_ring_raster_for_graph_given_color_values_2,
	    STATIC_FUNCTION(update_ring_raster_for_graph_given_color_values_2,
	    NIL,FALSE,2,2));
    Qlist_of_unsigned_integers = STATIC_SYMBOL("LIST-OF-UNSIGNED-INTEGERS",
	    AB_package);
    string_constant_5 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qhandle_icp_update_ring_raster_for_graph_given_color_values_2 = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-RING-RASTER-FOR-GRAPH-GIVEN-COLOR-VALUES-2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2,
	    STATIC_FUNCTION(handle_icp_update_ring_raster_for_graph_given_color_values_2,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_update_ring_raster_for_graph_given_color_values_2,
	    FIX((SI_Long)182L));
    Qhandler_for_printing_set_graph_rendering_foreground_only_mode = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)192L),
	    Qhandler_for_printing_set_graph_rendering_foreground_only_mode);
    Qset_graph_rendering_foreground_only_mode = 
	    STATIC_SYMBOL("SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE",
	    AB_package);
    Qforeground_only_mode = STATIC_SYMBOL("FOREGROUND-ONLY-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qset_graph_rendering_foreground_only_mode,
	    STATIC_FUNCTION(set_graph_rendering_foreground_only_mode,NIL,
	    FALSE,2,2));
    Qhandle_icp_set_graph_rendering_foreground_only_mode = 
	    STATIC_SYMBOL("HANDLE-ICP-SET-GRAPH-RENDERING-FOREGROUND-ONLY-MODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_set_graph_rendering_foreground_only_mode,
	    STATIC_FUNCTION(handle_icp_set_graph_rendering_foreground_only_mode,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_set_graph_rendering_foreground_only_mode,
	    FIX((SI_Long)192L));
    Qclipping_rectangles_for_new_data_qm = 
	    STATIC_SYMBOL("CLIPPING-RECTANGLES-FOR-NEW-DATA\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qclipping_rectangles_for_new_data_qm,
	    Clipping_rectangles_for_new_data_qm);
    Qwindows3 = STATIC_SYMBOL("WINDOWS3",AB_package);
    record_system_variable(Qclipping_rectangles_for_new_data_qm,Qwindows3,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qhandler_for_printing_add_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)151L),
	    Qhandler_for_printing_add_from_graph_rendering_to_current_window);
    Qadd_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    Qsubtract_instead_qm = STATIC_SYMBOL("SUBTRACT-INSTEAD\?",AB_package);
    Qclipped_left_edge = STATIC_SYMBOL("CLIPPED-LEFT-EDGE",AB_package);
    Qclipped_top_edge = STATIC_SYMBOL("CLIPPED-TOP-EDGE",AB_package);
    Qclipped_right_edge = STATIC_SYMBOL("CLIPPED-RIGHT-EDGE",AB_package);
    Qclipped_bottom_edge = STATIC_SYMBOL("CLIPPED-BOTTOM-EDGE",AB_package);
    Qgrid_background_color_value = 
	    STATIC_SYMBOL("GRID-BACKGROUND-COLOR-VALUE",AB_package);
    Qleft_edge_in_graph_rendering = 
	    STATIC_SYMBOL("LEFT-EDGE-IN-GRAPH-RENDERING",AB_package);
    Qtop_edge_in_graph_rendering = 
	    STATIC_SYMBOL("TOP-EDGE-IN-GRAPH-RENDERING",AB_package);
    Qcolor_value = STATIC_SYMBOL("COLOR-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qadd_from_graph_rendering_to_current_window,
	    STATIC_FUNCTION(add_from_graph_rendering_to_current_window,NIL,
	    FALSE,11,11));
    Qhandle_icp_add_from_graph_rendering_to_current_window = 
	    STATIC_SYMBOL("HANDLE-ICP-ADD-FROM-GRAPH-RENDERING-TO-CURRENT-WINDOW",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_add_from_graph_rendering_to_current_window,
	    STATIC_FUNCTION(handle_icp_add_from_graph_rendering_to_current_window,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_add_from_graph_rendering_to_current_window,
	    FIX((SI_Long)151L));
    Qhandler_for_printing_update_graph_dateline = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATELINE",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)153L),
	    Qhandler_for_printing_update_graph_dateline);
    Qupdate_graph_dateline = STATIC_SYMBOL("UPDATE-GRAPH-DATELINE",AB_package);
    Qdateline = STATIC_SYMBOL("DATELINE",AB_package);
    Qerase_dateline = STATIC_SYMBOL("ERASE-DATELINE",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_graph_dateline,
	    STATIC_FUNCTION(update_graph_dateline,NIL,FALSE,3,3));
    Qhandle_icp_update_graph_dateline = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-GRAPH-DATELINE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_update_graph_dateline,
	    STATIC_FUNCTION(handle_icp_update_graph_dateline,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_update_graph_dateline,
	    FIX((SI_Long)153L));
    Qhandler_for_printing_update_graph_data_extrema = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-UPDATE-GRAPH-DATA-EXTREMA",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)154L),
	    Qhandler_for_printing_update_graph_data_extrema);
    Qupdate_graph_data_extrema = STATIC_SYMBOL("UPDATE-GRAPH-DATA-EXTREMA",
	    AB_package);
    Qleft_edge = STATIC_SYMBOL("LEFT-EDGE",AB_package);
    Qtop_edge = STATIC_SYMBOL("TOP-EDGE",AB_package);
    Qright_edge = STATIC_SYMBOL("RIGHT-EDGE",AB_package);
    Qbottom_edge = STATIC_SYMBOL("BOTTOM-EDGE",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_graph_data_extrema,
	    STATIC_FUNCTION(update_graph_data_extrema,NIL,FALSE,4,4));
    Qhandle_icp_update_graph_data_extrema = 
	    STATIC_SYMBOL("HANDLE-ICP-UPDATE-GRAPH-DATA-EXTREMA",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_update_graph_data_extrema,
	    STATIC_FUNCTION(handle_icp_update_graph_data_extrema,NIL,FALSE,
	    0,0));
    add_icp_message_handler(Qhandle_icp_update_graph_data_extrema,
	    FIX((SI_Long)154L));
    Qhandler_for_printing_clear_data_clipping_rectangles = 
	    STATIC_SYMBOL("HANDLER-FOR-PRINTING-CLEAR-DATA-CLIPPING-RECTANGLES",
	    AB_package);
    aref_arg_1 = Icp_printing_message_handler_array;
    set_aref1(aref_arg_1,FIX((SI_Long)162L),
	    Qhandler_for_printing_clear_data_clipping_rectangles);
    Qclear_data_clipping_rectangles = 
	    STATIC_SYMBOL("CLEAR-DATA-CLIPPING-RECTANGLES",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_data_clipping_rectangles,
	    STATIC_FUNCTION(clear_data_clipping_rectangles,NIL,FALSE,0,0));
    Qhandle_icp_clear_data_clipping_rectangles = 
	    STATIC_SYMBOL("HANDLE-ICP-CLEAR-DATA-CLIPPING-RECTANGLES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_clear_data_clipping_rectangles,
	    STATIC_FUNCTION(handle_icp_clear_data_clipping_rectangles,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_clear_data_clipping_rectangles,
	    FIX((SI_Long)162L));
}
