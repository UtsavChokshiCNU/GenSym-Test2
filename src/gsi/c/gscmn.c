/* gscmn.c
 * Input file:  gsi-common.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gscmn.h"


Object G2int_gsi_magic_number = UNBOUND;

/* RECLAIM-GSI-LIST-FUNCTION */
Object g2int_reclaim_gsi_list_function(gsi_list)
    Object gsi_list;
{
    x_note_fn_call(43,0);
    g2int_reclaim_gensym_list_1(gsi_list);
    return VALUES_1(Nil);
}

Object G2int_gsi_allocated_array_listqm = UNBOUND;

Object G2int_gsi_allocated_string_listqm = UNBOUND;

Object G2int_gsi_reclaim_list_level = UNBOUND;

Object G2int_index_to_array_of_transfer_wrappers = UNBOUND;

Object G2int_gsi_vector_length = UNBOUND;

Object G2int_make_gsi_instance_existing_instance = UNBOUND;

Object G2int_gsi_context_to_socket_map = UNBOUND;

Object G2int_number_of_contexts_allocated = UNBOUND;

/* ALLOCATE-GSI-CONTEXT-NUMBER */
Object g2int_allocate_gsi_context_number()
{
    Object temp, map_1, context, svref_new_value;
    SI_Long svref_arg_2;

    x_note_fn_call(43,1);
    temp = FIXNUM_ADD1(G2int_number_of_contexts_allocated);
    G2int_number_of_contexts_allocated = temp;
    map_1 = G2int_gsi_context_to_socket_map;
    context = g2int_assign_index_in_index_space(map_1);
    if (FIXNUM_GE(context,ISVREF(map_1,(SI_Long)4L)))
	g2int_enlarge_index_space(map_1,context);
    temp = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(context) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(context) & (SI_Long)1023L;
    svref_new_value = G2int_current_icp_socket;
    ISVREF(temp,svref_arg_2) = svref_new_value;
    return VALUES_1(context);
}

/* FREE-GSI-CONTEXT-NUMBER */
Object g2int_free_gsi_context_number(context)
    Object context;
{
    Object temp, map_1, temp_1;
    SI_Long svref_arg_2;

    x_note_fn_call(43,2);
    if ((SI_Long)0L <= IFIX(context)) {
	if (IFIX(G2int_number_of_contexts_allocated) > (SI_Long)0L) {
	    temp = FIXNUM_SUB1(G2int_number_of_contexts_allocated);
	    G2int_number_of_contexts_allocated = temp;
	}
	map_1 = G2int_gsi_context_to_socket_map;
	if (FIXNUM_GE(context,ISVREF(map_1,(SI_Long)4L)))
	    g2int_enlarge_index_space(map_1,context);
	temp = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(context) >>  -  - 
		(SI_Long)10L);
	svref_arg_2 = IFIX(context) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = Nil;
	g2int_deassign_index_in_index_space(context,map_1);
	temp_1 = G2int_gsi_undefined_context;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

Object G2int_gsi_maximum_number_of_contexts = UNBOUND;

static Object Qg2int_gsi_context_to_socket_map;  /* gsi-context-to-socket-map */

/* INITIALIZE-GSI-CONTEXT-NUMBER-TABLE */
Object g2int_initialize_gsi_context_number_table(maximum_number_of_contexts)
    Object maximum_number_of_contexts;
{
    x_note_fn_call(43,3);
    if ( !TRUEP(G2int_gsi_context_to_socket_map)) {
	G2int_gsi_context_to_socket_map = 
		g2int_make_index_space_1(Qg2int_gsi_context_to_socket_map,Nil);
	g2int_enlarge_index_space(G2int_gsi_context_to_socket_map,
		FIX((SI_Long)20L));
    }
    G2int_gsi_maximum_number_of_contexts = maximum_number_of_contexts;
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_gsi_extension_data = UNBOUND;

Object G2int_chain_of_available_gsi_extension_datas = UNBOUND;

Object G2int_gsi_extension_data_count = UNBOUND;

/* RECLAIM-GSI-EXTENSION-DATA-INTERNAL-1 */
Object g2int_reclaim_gsi_extension_data_internal_1(gsi_extension_data)
    Object gsi_extension_data;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(43,4);
    inline_note_reclaim_cons(gsi_extension_data,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = gsi_extension_data;
    g2int_reclaim_gsi_transfer_wrapper_array(ISVREF(gsi_extension_data,
	    (SI_Long)3L));
    SVREF(gsi_extension_data,FIX((SI_Long)3L)) = Nil;
    g2int_reclaim_gsi_remote_procedures(ISVREF(gsi_extension_data,
	    (SI_Long)4L));
    SVREF(gsi_extension_data,FIX((SI_Long)4L)) = Nil;
    g2int_reclaim_gsi_list_function(ISVREF(gsi_extension_data,(SI_Long)5L));
    SVREF(gsi_extension_data,FIX((SI_Long)5L)) = Nil;
    g2int_reclaim_if_text_or_gensym_string_function(ISVREF(gsi_extension_data,
	    (SI_Long)6L));
    SVREF(gsi_extension_data,FIX((SI_Long)6L)) = Nil;
    g2int_reclaim_if_gsi_instance_for_context(ISVREF(gsi_extension_data,
	    (SI_Long)14L));
    SVREF(gsi_extension_data,FIX((SI_Long)14L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_gsi_extension_datas;
    SVREF(gsi_extension_data,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_extension_datas = gsi_extension_data;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-EXTENSION-DATA */
Object g2int_reclaim_structure_for_gsi_extension_data(gsi_extension_data)
    Object gsi_extension_data;
{
    x_note_fn_call(43,5);
    return g2int_reclaim_gsi_extension_data_internal_1(gsi_extension_data);
}

static Object Qg2_defstruct_structure_name_gsi_extension_data_g2_struct;  /* g2-defstruct-structure-name::gsi-extension-data-g2-struct */

/* MAKE-PERMANENT-GSI-EXTENSION-DATA-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_extension_data_structure_internal()
{
    Object def_structure_gsi_extension_data_variable;
    Object gsi_extension_data_count_new_value;
    Object defstruct_g2_gsi_extension_data_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,6);
    def_structure_gsi_extension_data_variable = Nil;
    gsi_extension_data_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_extension_data_count);
    G2int_gsi_extension_data_count = gsi_extension_data_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_extension_data_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_gsi_extension_data_variable = the_array;
	SVREF(defstruct_g2_gsi_extension_data_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_extension_data_g2_struct;
	def_structure_gsi_extension_data_variable = 
		defstruct_g2_gsi_extension_data_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_extension_data_variable);
}

/* MAKE-GSI-EXTENSION-DATA-1 */
Object g2int_make_gsi_extension_data_1()
{
    Object def_structure_gsi_extension_data_variable, svref_new_value;

    x_note_fn_call(43,7);
    def_structure_gsi_extension_data_variable = 
	    G2int_chain_of_available_gsi_extension_datas;
    if (def_structure_gsi_extension_data_variable) {
	G2int_chain_of_available_gsi_extension_datas = 
		ISVREF(def_structure_gsi_extension_data_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_extension_data_g2_struct;
    }
    else
	def_structure_gsi_extension_data_variable = 
		g2int_make_permanent_gsi_extension_data_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_extension_data_variable,Nil);
    ISVREF(def_structure_gsi_extension_data_variable,(SI_Long)1L) = 
	    FIX((SI_Long)-2L);
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)2L)) = Nil;
    svref_new_value = 
	    g2int_create_transfer_wrapper_array(G2int_size_of_array_of_transfer_wrappers);
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)3L)) = 
	    svref_new_value;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)10L)) = Nil;
    ISVREF(def_structure_gsi_extension_data_variable,(SI_Long)11L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_gsi_extension_data_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_gsi_extension_data_variable);
}

/* RECLAIM-GSI-EXTENSION-DATA */
Object g2int_reclaim_gsi_extension_data(extension_data)
    Object extension_data;
{
    Object socket_context_number, temp;

    x_note_fn_call(43,8);
    socket_context_number = ISVREF(extension_data,(SI_Long)1L);
    if ( !FIXNUM_EQ(socket_context_number,G2int_gsi_undefined_context))
	g2int_free_gsi_context_number(socket_context_number);
    temp = g2int_reclaim_gsi_extension_data_internal_1(extension_data);
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_define_gsi_interface;  /* send-icp-define-gsi-interface */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* SEND-ICP-DEFINE-GSI-INTERFACE */
Object g2int_send_icp_define_gsi_interface(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,9);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_define_gsi_interface;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)77L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_define_gsi_interface,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_define_gsi_interface,top,Nil);
		goto end_send_icp_define_gsi_interface;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_define_gsi_interface;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)77L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_define_gsi_interface);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_gsi_interface;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_gsi_interface:
    return result;
}

/* HANDLE-ICP-DEFINE-GSI-INTERFACE--BODY */
Object g2int_handle_icp_define_gsi_interface__body(corresponding_icp_object_index)
    Object corresponding_icp_object_index;
{
    x_note_fn_call(43,10);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_gsi_interface;  /* handle-icp-define-gsi-interface */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-DEFINE-GSI-INTERFACE */
Object g2int_handle_icp_define_gsi_interface()
{
    Object corresponding_icp_object_index, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,11);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_gsi_interface__body(corresponding_icp_object_index);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_define_gsi_interface,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_define_gsi_interface,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_interface);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_gsi_interface__body(corresponding_icp_object_index);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_send_data_values_if_any;  /* send-icp-send-data-values-if-any */

/* SEND-ICP-SEND-DATA-VALUES-IF-ANY */
Object g2int_send_icp_send_data_values_if_any(gsi_interface,year,month,day,
	    hour,minute,second_1)
    Object gsi_interface, year, month, day, hour, minute, second_1;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,12);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_send_data_values_if_any;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)73L));
	  g2int_write_icp_unsigned_integer(gsi_interface);
	  g2int_write_icp_integer(year);
	  g2int_write_icp_integer(month);
	  g2int_write_icp_integer(day);
	  g2int_write_icp_integer(hour);
	  g2int_write_icp_integer(minute);
	  g2int_write_icp_integer(second_1);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_send_data_values_if_any,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_send_data_values_if_any,top,Nil);
		goto end_send_icp_send_data_values_if_any;
	    }
	}
	gsi_interface = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_interface;
	year = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : year;
	month = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : month;
	day = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : day;
	hour = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : hour;
	minute = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : minute;
	second_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : second_1;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_send_data_values_if_any;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)73L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    case 5:
		      goto l5;
		      break;
		    case 6:
		      goto l6;
		      break;
		    case 7:
		      goto l7;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(gsi_interface))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(year))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(month))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(day))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(hour))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(minute))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(second_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(second_1);
	      g2int_resumable_icp_push(minute);
	      g2int_resumable_icp_push(hour);
	      g2int_resumable_icp_push(day);
	      g2int_resumable_icp_push(month);
	      g2int_resumable_icp_push(year);
	      g2int_resumable_icp_push(gsi_interface);
	      g2int_resumable_icp_push(Qg2int_send_icp_send_data_values_if_any);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_send_data_values_if_any;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_send_data_values_if_any:
    return result;
}

/* HANDLE-ICP-SEND-DATA-VALUES-IF-ANY--BODY */
Object g2int_handle_icp_send_data_values_if_any__body(gsi_interface,year,
	    month,day,hour,minute,second_1)
    Object gsi_interface, year, month, day, hour, minute, second_1;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, extension_data;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(43,13);
    if (FIXNUM_EQ(G2int_gsi_connection_established,
	    ISVREF(G2int_current_icp_socket,(SI_Long)28L))) {
	current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	    temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		    (SI_Long)53L) : Nil;
	    if (temp);
	    else
		temp = Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(G2int_writing_icp_message_group);
			      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					&&  
					!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					    {
				    g2int_send_icp_receive_value_for_ping_request(gsi_interface,
					    year,month,day,hour,minute,
					    second_1,
					    G2int_gsi_interface_running_ok);
				    g2int_end_icp_message_group();
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
	g2int_call_gsi_callback(1,G2int_gsi_g2_poll);
    }
    else {
	extension_data = ISVREF(G2int_current_icp_socket,(SI_Long)29L);
	SVREF(extension_data,FIX((SI_Long)7L)) = gsi_interface;
	if (!(IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)8L))
	    g2int_gsi_reply_to_initial_ping();
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_send_data_values_if_any;  /* handle-icp-send-data-values-if-any */

/* HANDLE-ICP-SEND-DATA-VALUES-IF-ANY */
Object g2int_handle_icp_send_data_values_if_any()
{
    Object gsi_interface, year, month, day, hour, minute, second_1;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,14);
    if (G2int_disable_resumability) {
	gsi_interface = g2int_read_icp_unsigned_integer();
	year = g2int_read_icp_integer();
	month = g2int_read_icp_integer();
	day = g2int_read_icp_integer();
	hour = g2int_read_icp_integer();
	minute = g2int_read_icp_integer();
	second_1 = g2int_read_icp_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_send_data_values_if_any__body(gsi_interface,
		  year,month,day,hour,minute,second_1);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_send_data_values_if_any,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_send_data_values_if_any,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_interface = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_interface = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    year = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    year = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    month = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    month = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    day = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    day = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    hour = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    hour = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    minute = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(hour);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    minute = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    second_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(minute);
		g2int_resumable_icp_push(hour);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_send_data_values_if_any);
		return VALUES_1(G2int_icp_suspend);
	    }
	    second_1 = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_send_data_values_if_any__body(gsi_interface,
		  year,month,day,hour,minute,second_1);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GSI-SEND-REPLY-TO-INITIAL-PING-INTERNAL */
Object g2int_gsi_send_reply_to_initial_ping_internal(icp_socket)
    Object icp_socket;
{
    Object svref_new_value, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(43,15);
    svref_new_value = G2int_gsi_connection_established;
    SVREF(icp_socket,FIX((SI_Long)28L)) = svref_new_value;
    current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = Nil;
	disable_resumability = temp;
	PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(G2int_writing_icp_message_group);
			  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
				    &&  
				    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					{
				g2int_send_icp_receive_value_for_ping_request(ISVREF(ISVREF(icp_socket,
					(SI_Long)29L),(SI_Long)7L),
					FIX((SI_Long)0L),FIX((SI_Long)0L),
					FIX((SI_Long)0L),FIX((SI_Long)1L),
					FIX((SI_Long)1L),
					FIX((SI_Long)1970L),
					G2int_gsi_interface_running_ok);
				g2int_end_icp_message_group();
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
    return VALUES_1(Nil);
}

/* GSI-REPLY-TO-INITIAL-PING */
Object g2int_gsi_reply_to_initial_ping()
{
    Object icp_socket, temp;

    x_note_fn_call(43,16);
    if ( !TRUEP(g2int_call_initialize_context_and_maybe_reject_connection())) {
	icp_socket = G2int_current_icp_socket;
	temp = FIXNUM_EQ(G2int_gsi_connection_initializing,
		ISVREF(icp_socket,(SI_Long)28L)) ? 
		g2int_gsi_send_reply_to_initial_ping_internal(icp_socket) :
		 Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_receive_value_for_ping_request;  /* send-icp-receive-value-for-ping-request */

/* SEND-ICP-RECEIVE-VALUE-FOR-PING-REQUEST */
Object g2int_send_icp_receive_value_for_ping_request(gsi_interface,year,
	    month,day,hour,minute,second_1,status)
    Object gsi_interface, year, month, day, hour, minute, second_1, status;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,17);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_ping_request;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)67L));
	  g2int_write_icp_unsigned_integer(gsi_interface);
	  g2int_write_icp_integer(year);
	  g2int_write_icp_integer(month);
	  g2int_write_icp_integer(day);
	  g2int_write_icp_integer(hour);
	  g2int_write_icp_integer(minute);
	  g2int_write_icp_integer(second_1);
	  g2int_write_icp_integer(status);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_receive_value_for_ping_request,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_value_for_ping_request,top,
			Nil);
		goto end_send_icp_receive_value_for_ping_request;
	    }
	}
	gsi_interface = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_interface;
	year = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : year;
	month = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : month;
	day = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : day;
	hour = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : hour;
	minute = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : minute;
	second_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : second_1;
	status = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : status;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_ping_request;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)67L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(gsi_interface))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(year))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(month))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(day))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(hour))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(minute))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(second_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l8:
	  if (EQ(icp_suspend_1,g2int_write_icp_integer(status))) {
	      g2int_resumable_icp_push(FIX((SI_Long)8L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(status);
	      g2int_resumable_icp_push(second_1);
	      g2int_resumable_icp_push(minute);
	      g2int_resumable_icp_push(hour);
	      g2int_resumable_icp_push(day);
	      g2int_resumable_icp_push(month);
	      g2int_resumable_icp_push(year);
	      g2int_resumable_icp_push(gsi_interface);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_value_for_ping_request);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_value_for_ping_request;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_value_for_ping_request:
    return result;
}

/* HANDLE-ICP-RECEIVE-VALUE-FOR-PING-REQUEST--BODY */
Object g2int_handle_icp_receive_value_for_ping_request__body(gsi_interface,
	    year,month,day,hour,minute,second_1,status)
    Object gsi_interface, year, month, day, hour, minute, second_1, status;
{
    Object current_icp_port, temp;
    Declare_special(1);

    x_note_fn_call(43,18);
    current_icp_port = ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),
	    (SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,0);
      temp = g2int_get_corresponding_icp_object(gsi_interface);
    POP_SPECIAL();
    g2int_gsi_receive_value_for_ping_request(temp,year,month,day,hour,
	    minute,second_1,status);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_value_for_ping_request;  /* handle-icp-receive-value-for-ping-request */

/* HANDLE-ICP-RECEIVE-VALUE-FOR-PING-REQUEST */
Object g2int_handle_icp_receive_value_for_ping_request()
{
    Object gsi_interface, year, month, day, hour, minute, second_1, status;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,19);
    if (G2int_disable_resumability) {
	gsi_interface = g2int_read_icp_unsigned_integer();
	year = g2int_read_icp_integer();
	month = g2int_read_icp_integer();
	day = g2int_read_icp_integer();
	hour = g2int_read_icp_integer();
	minute = g2int_read_icp_integer();
	second_1 = g2int_read_icp_integer();
	status = g2int_read_icp_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_ping_request__body(gsi_interface,
		  year,month,day,hour,minute,second_1,status);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_receive_value_for_ping_request,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_value_for_ping_request,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_interface = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_interface = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    year = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    year = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    month = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    month = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    day = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    day = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    hour = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    hour = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    minute = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(hour);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    minute = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    second_1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(minute);
		g2int_resumable_icp_push(hour);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    second_1 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    status = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(second_1);
		g2int_resumable_icp_push(minute);
		g2int_resumable_icp_push(hour);
		g2int_resumable_icp_push(day);
		g2int_resumable_icp_push(month);
		g2int_resumable_icp_push(year);
		g2int_resumable_icp_push(gsi_interface);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_ping_request);
		return VALUES_1(G2int_icp_suspend);
	    }
	    status = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_ping_request__body(gsi_interface,
		  year,month,day,hour,minute,second_1,status);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_gsi_history = UNBOUND;

Object G2int_chain_of_available_gsi_historys = UNBOUND;

Object G2int_gsi_history_count = UNBOUND;

/* RECLAIM-GSI-HISTORY-1-1 */
Object g2int_reclaim_gsi_history_1_1(gsi_history)
    Object gsi_history;
{
    Object svref_new_value;

    x_note_fn_call(43,20);
    inline_note_reclaim_cons(gsi_history,Nil);
    svref_new_value = G2int_chain_of_available_gsi_historys;
    SVREF(gsi_history,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_historys = gsi_history;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-HISTORY */
Object g2int_reclaim_structure_for_gsi_history(gsi_history)
    Object gsi_history;
{
    x_note_fn_call(43,21);
    return g2int_reclaim_gsi_history_1_1(gsi_history);
}

static Object Qg2_defstruct_structure_name_gsi_history_g2_struct;  /* g2-defstruct-structure-name::gsi-history-g2-struct */

/* MAKE-PERMANENT-GSI-HISTORY-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_history_structure_internal()
{
    Object def_structure_gsi_history_variable, gsi_history_count_new_value;
    Object defstruct_g2_gsi_history_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,22);
    def_structure_gsi_history_variable = Nil;
    gsi_history_count_new_value = FIXNUM_ADD1(G2int_gsi_history_count);
    G2int_gsi_history_count = gsi_history_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_history_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_gsi_history_variable = the_array;
	SVREF(defstruct_g2_gsi_history_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_history_g2_struct;
	def_structure_gsi_history_variable = defstruct_g2_gsi_history_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_history_variable);
}

/* MAKE-GSI-HISTORY-1-1 */
Object g2int_make_gsi_history_1_1(gsi_history_length,gsi_history_values,
	    gsi_history_timestamps,gsi_history_counter)
    Object gsi_history_length, gsi_history_values, gsi_history_timestamps;
    Object gsi_history_counter;
{
    Object def_structure_gsi_history_variable;

    x_note_fn_call(43,23);
    def_structure_gsi_history_variable = G2int_chain_of_available_gsi_historys;
    if (def_structure_gsi_history_variable) {
	G2int_chain_of_available_gsi_historys = 
		ISVREF(def_structure_gsi_history_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_history_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_history_g2_struct;
    }
    else
	def_structure_gsi_history_variable = 
		g2int_make_permanent_gsi_history_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_history_variable,Nil);
    SVREF(def_structure_gsi_history_variable,FIX((SI_Long)1L)) = 
	    gsi_history_length;
    SVREF(def_structure_gsi_history_variable,FIX((SI_Long)2L)) = 
	    gsi_history_values;
    SVREF(def_structure_gsi_history_variable,FIX((SI_Long)3L)) = 
	    gsi_history_timestamps;
    SVREF(def_structure_gsi_history_variable,FIX((SI_Long)6L)) = 
	    gsi_history_counter;
    return VALUES_1(def_structure_gsi_history_variable);
}

Object G2int_the_type_description_of_gsi_attribute = UNBOUND;

Object G2int_chain_of_available_gsi_attributes = UNBOUND;

Object G2int_gsi_attribute_count = UNBOUND;

/* RECLAIM-GSI-ATTRIBUTE-1-1 */
Object g2int_reclaim_gsi_attribute_1_1(gsi_attribute)
    Object gsi_attribute;
{
    Object svref_new_value;

    x_note_fn_call(43,24);
    inline_note_reclaim_cons(gsi_attribute,Nil);
    svref_new_value = G2int_chain_of_available_gsi_attributes;
    SVREF(gsi_attribute,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_attributes = gsi_attribute;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-ATTRIBUTE */
Object g2int_reclaim_structure_for_gsi_attribute(gsi_attribute)
    Object gsi_attribute;
{
    x_note_fn_call(43,25);
    return g2int_reclaim_gsi_attribute_1_1(gsi_attribute);
}

static Object Qg2_defstruct_structure_name_gsi_attribute_g2_struct;  /* g2-defstruct-structure-name::gsi-attribute-g2-struct */

/* MAKE-PERMANENT-GSI-ATTRIBUTE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_attribute_structure_internal()
{
    Object def_structure_gsi_attribute_variable, gsi_attribute_count_new_value;
    Object defstruct_g2_gsi_attribute_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,26);
    def_structure_gsi_attribute_variable = Nil;
    gsi_attribute_count_new_value = FIXNUM_ADD1(G2int_gsi_attribute_count);
    G2int_gsi_attribute_count = gsi_attribute_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_attribute_variable = Nil;
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
	defstruct_g2_gsi_attribute_variable = the_array;
	SVREF(defstruct_g2_gsi_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_attribute_g2_struct;
	def_structure_gsi_attribute_variable = 
		defstruct_g2_gsi_attribute_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_attribute_variable);
}

/* MAKE-GSI-ATTRIBUTE-1-1 */
Object g2int_make_gsi_attribute_1_1(gsi_attribute_spec,
	    gsi_attribute_instance,gsi_attribute_owner)
    Object gsi_attribute_spec, gsi_attribute_instance, gsi_attribute_owner;
{
    Object def_structure_gsi_attribute_variable;

    x_note_fn_call(43,27);
    def_structure_gsi_attribute_variable = 
	    G2int_chain_of_available_gsi_attributes;
    if (def_structure_gsi_attribute_variable) {
	G2int_chain_of_available_gsi_attributes = 
		ISVREF(def_structure_gsi_attribute_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_attribute_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_attribute_g2_struct;
    }
    else
	def_structure_gsi_attribute_variable = 
		g2int_make_permanent_gsi_attribute_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_attribute_variable,Nil);
    SVREF(def_structure_gsi_attribute_variable,FIX((SI_Long)1L)) = 
	    gsi_attribute_spec;
    SVREF(def_structure_gsi_attribute_variable,FIX((SI_Long)4L)) = 
	    gsi_attribute_instance;
    SVREF(def_structure_gsi_attribute_variable,FIX((SI_Long)5L)) = 
	    gsi_attribute_owner;
    SVREF(def_structure_gsi_attribute_variable,FIX((SI_Long)2L)) = Nil;
    ISVREF(def_structure_gsi_attribute_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_gsi_attribute_variable);
}

/* SET-GSI-ATTRIBUTE-IS-TRANSIENT-P */
Object g2int_set_gsi_attribute_is_transient_p(gsi_attribute,new_value)
    Object gsi_attribute, new_value;
{
    Object flags;
    SI_Long svref_new_value;

    x_note_fn_call(43,28);
    flags = ISVREF(gsi_attribute,(SI_Long)3L);
    svref_new_value = new_value ? (SI_Long)1L | IFIX(flags) : (SI_Long)-2L 
	    & IFIX(flags);
    ISVREF(gsi_attribute,(SI_Long)3L) = FIX(svref_new_value);
    return VALUES_1(new_value);
}

/* SET-GSI-ATTRIBUTE-IS-IDENTIFYING-P */
Object g2int_set_gsi_attribute_is_identifying_p(gsi_attribute,new_value)
    Object gsi_attribute, new_value;
{
    Object flags;
    SI_Long svref_new_value;

    x_note_fn_call(43,29);
    flags = ISVREF(gsi_attribute,(SI_Long)3L);
    svref_new_value = new_value ? (SI_Long)2L | IFIX(flags) : (SI_Long)-3L 
	    & IFIX(flags);
    ISVREF(gsi_attribute,(SI_Long)3L) = FIX(svref_new_value);
    return VALUES_1(new_value);
}

Object G2int_the_type_description_of_gsi_transfer_wrapper = UNBOUND;

Object G2int_chain_of_available_gsi_transfer_wrappers = UNBOUND;

Object G2int_gsi_transfer_wrapper_count = UNBOUND;

/* RECLAIM-GSI-TRANSFER-WRAPPER-1-1 */
Object g2int_reclaim_gsi_transfer_wrapper_1_1(gsi_transfer_wrapper)
    Object gsi_transfer_wrapper;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(43,30);
    inline_note_reclaim_cons(gsi_transfer_wrapper,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = gsi_transfer_wrapper;
    g2int_reclaim_if_managed_float(ISVREF(gsi_transfer_wrapper,(SI_Long)3L));
    SVREF(gsi_transfer_wrapper,FIX((SI_Long)3L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_gsi_transfer_wrappers;
    SVREF(gsi_transfer_wrapper,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_transfer_wrappers = gsi_transfer_wrapper;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-TRANSFER-WRAPPER */
Object g2int_reclaim_structure_for_gsi_transfer_wrapper(gsi_transfer_wrapper)
    Object gsi_transfer_wrapper;
{
    x_note_fn_call(43,31);
    return g2int_reclaim_gsi_transfer_wrapper_1_1(gsi_transfer_wrapper);
}

static Object Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct;  /* g2-defstruct-structure-name::gsi-transfer-wrapper-g2-struct */

/* MAKE-PERMANENT-GSI-TRANSFER-WRAPPER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_transfer_wrapper_structure_internal()
{
    Object def_structure_gsi_transfer_wrapper_variable;
    Object gsi_transfer_wrapper_count_new_value;
    Object defstruct_g2_gsi_transfer_wrapper_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,32);
    def_structure_gsi_transfer_wrapper_variable = Nil;
    gsi_transfer_wrapper_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_transfer_wrapper_count);
    G2int_gsi_transfer_wrapper_count = gsi_transfer_wrapper_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_transfer_wrapper_variable = Nil;
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
	defstruct_g2_gsi_transfer_wrapper_variable = the_array;
	SVREF(defstruct_g2_gsi_transfer_wrapper_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct;
	def_structure_gsi_transfer_wrapper_variable = 
		defstruct_g2_gsi_transfer_wrapper_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_transfer_wrapper_variable);
}

/* MAKE-GSI-TRANSFER-WRAPPER-1-1 */
Object g2int_make_gsi_transfer_wrapper_1_1(gsi_transfer_sensor_or_index,
	    gsi_transfer_status,gsi_transfer_update_interval,
	    gsi_transfer_instance,gsi_transfer_owner)
    Object gsi_transfer_sensor_or_index, gsi_transfer_status;
    Object gsi_transfer_update_interval, gsi_transfer_instance;
    Object gsi_transfer_owner;
{
    Object def_structure_gsi_transfer_wrapper_variable;

    x_note_fn_call(43,33);
    def_structure_gsi_transfer_wrapper_variable = 
	    G2int_chain_of_available_gsi_transfer_wrappers;
    if (def_structure_gsi_transfer_wrapper_variable) {
	G2int_chain_of_available_gsi_transfer_wrappers = 
		ISVREF(def_structure_gsi_transfer_wrapper_variable,
		(SI_Long)0L);
	SVREF(def_structure_gsi_transfer_wrapper_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct;
    }
    else
	def_structure_gsi_transfer_wrapper_variable = 
		g2int_make_permanent_gsi_transfer_wrapper_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_transfer_wrapper_variable,Nil);
    SVREF(def_structure_gsi_transfer_wrapper_variable,FIX((SI_Long)1L)) = 
	    gsi_transfer_sensor_or_index;
    SVREF(def_structure_gsi_transfer_wrapper_variable,FIX((SI_Long)2L)) = 
	    gsi_transfer_status;
    SVREF(def_structure_gsi_transfer_wrapper_variable,FIX((SI_Long)3L)) = 
	    gsi_transfer_update_interval;
    SVREF(def_structure_gsi_transfer_wrapper_variable,FIX((SI_Long)4L)) = 
	    gsi_transfer_instance;
    SVREF(def_structure_gsi_transfer_wrapper_variable,FIX((SI_Long)5L)) = 
	    gsi_transfer_owner;
    return VALUES_1(def_structure_gsi_transfer_wrapper_variable);
}

static Object Qg2int_user;         /* user */

/* MAKE-GSI-USER-TRANSFER-WRAPPER */
Object g2int_make_gsi_user_transfer_wrapper()
{
    Object temp;

    x_note_fn_call(43,34);
    temp = g2int_make_gsi_transfer_wrapper_1_1(Nil,FIX((SI_Long)0L),Nil,
	    Nil,Qg2int_user);
    return VALUES_1(temp);
}

static Object Qg2int_context;      /* context */

/* CREATE-TRANSFER-WRAPPER-ARRAY */
Object g2int_create_transfer_wrapper_array(size)
    Object size;
{
    Object transfer_wrapper_array, svref_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(43,35);
    transfer_wrapper_array = 
	    g2int_gsi_allocate_managed_array(FIXNUM_ADD1(size));
    svref_new_value = G2int_gsi_magic_number;
    SVREF(transfer_wrapper_array,FIX((SI_Long)0L)) = svref_new_value;
    i = IFIX(G2int_gsi_magic_offset);
    ab_loop_bind_ = IFIX(FIXNUM_ADD1(size));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    svref_new_value = g2int_make_gsi_transfer_wrapper_1_1(Nil,
	    FIX((SI_Long)0L),Nil,Nil,Qg2int_context);
    ISVREF(transfer_wrapper_array,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(transfer_wrapper_array);
}

Object G2int_the_type_description_of_gsi_instance = UNBOUND;

Object G2int_chain_of_available_gsi_instances = UNBOUND;

Object G2int_gsi_instance_count = UNBOUND;

/* RECLAIM-GSI-INSTANCE-1-1 */
Object g2int_reclaim_gsi_instance_1_1(gsi_instance)
    Object gsi_instance;
{
    Object svref_new_value;

    x_note_fn_call(43,36);
    inline_note_reclaim_cons(gsi_instance,Nil);
    svref_new_value = G2int_chain_of_available_gsi_instances;
    SVREF(gsi_instance,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_instances = gsi_instance;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-INSTANCE */
Object g2int_reclaim_structure_for_gsi_instance(gsi_instance)
    Object gsi_instance;
{
    x_note_fn_call(43,37);
    return g2int_reclaim_gsi_instance_1_1(gsi_instance);
}

static Object Qg2_defstruct_structure_name_gsi_instance_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-g2-struct */

/* MAKE-PERMANENT-GSI-INSTANCE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_instance_structure_internal()
{
    Object def_structure_gsi_instance_variable, gsi_instance_count_new_value;
    Object defstruct_g2_gsi_instance_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,38);
    def_structure_gsi_instance_variable = Nil;
    gsi_instance_count_new_value = FIXNUM_ADD1(G2int_gsi_instance_count);
    G2int_gsi_instance_count = gsi_instance_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_instance_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_gsi_instance_variable = the_array;
	SVREF(defstruct_g2_gsi_instance_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_instance_g2_struct;
	def_structure_gsi_instance_variable = 
		defstruct_g2_gsi_instance_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_instance_variable);
}

/* MAKE-GSI-INSTANCE-1-1 */
Object g2int_make_gsi_instance_1_1()
{
    Object def_structure_gsi_instance_variable;

    x_note_fn_call(43,39);
    def_structure_gsi_instance_variable = 
	    G2int_chain_of_available_gsi_instances;
    if (def_structure_gsi_instance_variable) {
	G2int_chain_of_available_gsi_instances = 
		ISVREF(def_structure_gsi_instance_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_instance_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_instance_g2_struct;
    }
    else
	def_structure_gsi_instance_variable = 
		g2int_make_permanent_gsi_instance_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_instance_variable,Nil);
    ISVREF(def_structure_gsi_instance_variable,(SI_Long)1L) = FIX((SI_Long)0L);
    SVREF(def_structure_gsi_instance_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_gsi_instance_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_gsi_instance_variable);
}

/* GSI-INSTANCE-VALUE-FUNCTION */
Object g2int_gsi_instance_value_function(gsi_instance)
    Object gsi_instance;
{
    Object temp;

    x_note_fn_call(43,40);
    temp = ISVREF(gsi_instance,(SI_Long)2L);
    return VALUES_1(temp);
}

/* SET-GSI-INSTANCE-VALUE-TYPE */
Object g2int_set_gsi_instance_value_type(gsi_instance,value)
    Object gsi_instance, value;
{
    SI_Long svref_new_value;

    x_note_fn_call(43,41);
    svref_new_value = IFIX(ISVREF(gsi_instance,(SI_Long)1L)) & (SI_Long)7L 
	    | IFIX(value) << (SI_Long)3L;
    return VALUES_1(ISVREF(gsi_instance,(SI_Long)1L) = FIX(svref_new_value));
}

static Object Qg2int_gsi;          /* gsi */

static Object Qg2int_gsi_event_queue;  /* gsi-event-queue */

static Object Qg2int_gsi_input_queue;  /* gsi-input-queue */

/* SET-GSI-INSTANCE-OWNER */
Object g2int_set_gsi_instance_owner(gsi_instance,value)
    Object gsi_instance, value;
{
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;

    x_note_fn_call(43,42);
    gensymed_symbol = IFIX(ISVREF(gsi_instance,(SI_Long)1L)) >>  -  - 
	    (SI_Long)3L << (SI_Long)3L;
    if (EQ(value,Qg2int_gsi))
	gensymed_symbol_1 = (SI_Long)0L;
    else if (EQ(value,Qg2int_user))
	gensymed_symbol_1 = (SI_Long)1L;
    else if (EQ(value,Qg2int_context))
	gensymed_symbol_1 = (SI_Long)2L;
    else if (EQ(value,Qg2int_gsi_event_queue))
	gensymed_symbol_1 = (SI_Long)3L;
    else if (EQ(value,Qg2int_gsi_input_queue))
	gensymed_symbol_1 = (SI_Long)4L;
    else
	gensymed_symbol_1 = (SI_Long)0L;
    svref_new_value = gensymed_symbol | gensymed_symbol_1;
    ISVREF(gsi_instance,(SI_Long)1L) = FIX(svref_new_value);
    return VALUES_1(value);
}

Object G2int_the_type_description_of_gsi_instance_extension = UNBOUND;

Object G2int_chain_of_available_gsi_instance_extensions = UNBOUND;

Object G2int_gsi_instance_extension_count = UNBOUND;

/* RECLAIM-GSI-INSTANCE-EXTENSION-1-1 */
Object g2int_reclaim_gsi_instance_extension_1_1(gsi_instance_extension)
    Object gsi_instance_extension;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(43,43);
    inline_note_reclaim_cons(gsi_instance_extension,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = gsi_instance_extension;
    g2int_reclaim_gensym_list_1(ISVREF(gsi_instance_extension,(SI_Long)5L));
    SVREF(gsi_instance_extension,FIX((SI_Long)5L)) = Nil;
    g2int_reclaim_if_managed_float(ISVREF(gsi_instance_extension,
	    (SI_Long)10L));
    SVREF(gsi_instance_extension,FIX((SI_Long)10L)) = Nil;
    g2int_reclaim_if_managed_float(ISVREF(gsi_instance_extension,
	    (SI_Long)11L));
    SVREF(gsi_instance_extension,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_gensym_list_1(ISVREF(gsi_instance_extension,(SI_Long)13L));
    SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_gsi_instance_extensions;
    SVREF(gsi_instance_extension,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_instance_extensions = gsi_instance_extension;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-INSTANCE-EXTENSION */
Object g2int_reclaim_structure_for_gsi_instance_extension(gsi_instance_extension)
    Object gsi_instance_extension;
{
    x_note_fn_call(43,44);
    return g2int_reclaim_gsi_instance_extension_1_1(gsi_instance_extension);
}

static Object Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-extension-g2-struct */

/* MAKE-PERMANENT-GSI-INSTANCE-EXTENSION-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_instance_extension_structure_internal()
{
    Object def_structure_gsi_instance_extension_variable;
    Object gsi_instance_extension_count_new_value;
    Object defstruct_g2_gsi_instance_extension_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,45);
    def_structure_gsi_instance_extension_variable = Nil;
    gsi_instance_extension_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_instance_extension_count);
    G2int_gsi_instance_extension_count = 
	    gsi_instance_extension_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_instance_extension_variable = Nil;
	gensymed_symbol = (SI_Long)15L;
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
	defstruct_g2_gsi_instance_extension_variable = the_array;
	SVREF(defstruct_g2_gsi_instance_extension_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct;
	def_structure_gsi_instance_extension_variable = 
		defstruct_g2_gsi_instance_extension_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_instance_extension_variable);
}

/* MAKE-GSI-INSTANCE-EXTENSION-1 */
Object g2int_make_gsi_instance_extension_1()
{
    Object def_structure_gsi_instance_extension_variable;

    x_note_fn_call(43,46);
    def_structure_gsi_instance_extension_variable = 
	    G2int_chain_of_available_gsi_instance_extensions;
    if (def_structure_gsi_instance_extension_variable) {
	G2int_chain_of_available_gsi_instance_extensions = 
		ISVREF(def_structure_gsi_instance_extension_variable,
		(SI_Long)0L);
	SVREF(def_structure_gsi_instance_extension_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct;
    }
    else
	def_structure_gsi_instance_extension_variable = 
		g2int_make_permanent_gsi_instance_extension_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_instance_extension_variable,
	    Nil);
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)1L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)2L)) 
	    = Nil;
    ISVREF(def_structure_gsi_instance_extension_variable,(SI_Long)3L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)4L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)5L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)6L)) 
	    = Nil;
    ISVREF(def_structure_gsi_instance_extension_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)8L)) 
	    = Nil;
    ISVREF(def_structure_gsi_instance_extension_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)10L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)11L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)12L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)13L)) 
	    = Nil;
    SVREF(def_structure_gsi_instance_extension_variable,FIX((SI_Long)14L)) 
	    = Nil;
    return VALUES_1(def_structure_gsi_instance_extension_variable);
}

/* GET-GSI-INSTANCE-PLIST-VALUE */
Object g2int_get_gsi_instance_plist_value(gsi_instance,property_1)
    Object gsi_instance, property_1;
{
    Object gsi_instance_extension;

    x_note_fn_call(43,47);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    return getf(gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)5L) : Nil,property_1,_);
}

/* SET-GSI-INSTANCE-PLIST-VALUE */
Object g2int_set_gsi_instance_plist_value(gsi_instance,property_1,value)
    Object gsi_instance, property_1, value;
{
    Object gsi_instance_extension, plist, m, car_arg;

    x_note_fn_call(43,48);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    plist = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)5L) : Nil;
    m = g2int_memq_function(property_1,plist);
    if ( !TRUEP(m)) {
	m = g2int_gensym_cons_1(property_1,g2int_gensym_cons_1(Nil,plist));
	gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_instance,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	SVREF(gsi_instance_extension,FIX((SI_Long)5L)) = m;
    }
    car_arg = M_CDR(m);
    M_CAR(car_arg) = value;
    return VALUES_1(value);
}

Object G2int_the_type_description_of_gsi_array_wrapper = UNBOUND;

Object G2int_chain_of_available_gsi_array_wrappers = UNBOUND;

Object G2int_gsi_array_wrapper_count = UNBOUND;

/* RECLAIM-GSI-ARRAY-WRAPPER-1 */
Object g2int_reclaim_gsi_array_wrapper_1(gsi_array_wrapper)
    Object gsi_array_wrapper;
{
    Object svref_new_value;

    x_note_fn_call(43,49);
    inline_note_reclaim_cons(gsi_array_wrapper,Nil);
    svref_new_value = G2int_chain_of_available_gsi_array_wrappers;
    SVREF(gsi_array_wrapper,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_array_wrappers = gsi_array_wrapper;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-ARRAY-WRAPPER */
Object g2int_reclaim_structure_for_gsi_array_wrapper(gsi_array_wrapper)
    Object gsi_array_wrapper;
{
    x_note_fn_call(43,50);
    return g2int_reclaim_gsi_array_wrapper_1(gsi_array_wrapper);
}

static Object Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct;  /* g2-defstruct-structure-name::gsi-array-wrapper-g2-struct */

/* MAKE-PERMANENT-GSI-ARRAY-WRAPPER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_array_wrapper_structure_internal()
{
    Object def_structure_gsi_array_wrapper_variable;
    Object gsi_array_wrapper_count_new_value;
    Object defstruct_g2_gsi_array_wrapper_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,51);
    def_structure_gsi_array_wrapper_variable = Nil;
    gsi_array_wrapper_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_array_wrapper_count);
    G2int_gsi_array_wrapper_count = gsi_array_wrapper_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_array_wrapper_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_gsi_array_wrapper_variable = the_array;
	SVREF(defstruct_g2_gsi_array_wrapper_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct;
	def_structure_gsi_array_wrapper_variable = 
		defstruct_g2_gsi_array_wrapper_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_array_wrapper_variable);
}

/* MAKE-GSI-ARRAY-WRAPPER-1 */
Object g2int_make_gsi_array_wrapper_1(gsi_array_type,gsi_array)
    Object gsi_array_type, gsi_array;
{
    Object def_structure_gsi_array_wrapper_variable;

    x_note_fn_call(43,52);
    def_structure_gsi_array_wrapper_variable = 
	    G2int_chain_of_available_gsi_array_wrappers;
    if (def_structure_gsi_array_wrapper_variable) {
	G2int_chain_of_available_gsi_array_wrappers = 
		ISVREF(def_structure_gsi_array_wrapper_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_array_wrapper_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct;
    }
    else
	def_structure_gsi_array_wrapper_variable = 
		g2int_make_permanent_gsi_array_wrapper_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_array_wrapper_variable,Nil);
    SVREF(def_structure_gsi_array_wrapper_variable,FIX((SI_Long)1L)) = 
	    gsi_array_type;
    SVREF(def_structure_gsi_array_wrapper_variable,FIX((SI_Long)2L)) = 
	    gsi_array;
    return VALUES_1(def_structure_gsi_array_wrapper_variable);
}

/* GSI-SENSOR-P-FUNCTION */
Object g2int_gsi_sensor_p_function(sensor)
    Object sensor;
{
    Object gsi_instance_extension, temp;

    x_note_fn_call(43,53);
    if (SIMPLE_VECTOR_P(sensor) && EQ(ISVREF(sensor,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_instance_g2_struct)) {
	gsi_instance_extension = ISVREF(sensor,(SI_Long)3L);
	temp =  ! !(gsi_instance_extension ? 
		TRUEP(ISVREF(gsi_instance_extension,(SI_Long)11L)) : 
		TRUEP(Nil)) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GSI-SENSOR-INDEX */
Object g2int_gsi_sensor_index(gsi_sensor)
    Object gsi_sensor;
{
    Object gsi_instance_extension, temp;

    x_note_fn_call(43,54);
    gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
    temp = last(gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)13L) : Nil,_);
    return VALUES_1(CAR(temp));
}

/* RECLAIM-GSI-INSTANCE-FOR-GSI */
Object g2int_reclaim_gsi_instance_for_gsi(gsi_instance)
    Object gsi_instance;
{
    x_note_fn_call(43,55);
    g2int_reclaim_gsi_instance(gsi_instance,Qg2int_gsi);
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-INSTANCE-FOR-CONTEXT */
Object g2int_reclaim_gsi_instance_for_context(gsi_instance)
    Object gsi_instance;
{
    x_note_fn_call(43,56);
    g2int_reclaim_gsi_instance(gsi_instance,Qg2int_context);
    return VALUES_1(Nil);
}

/* RECLAIM-IF-GSI-INSTANCE-FOR-CONTEXT */
Object g2int_reclaim_if_gsi_instance_for_context(gsi_instance)
    Object gsi_instance;
{
    x_note_fn_call(43,57);
    if (gsi_instance)
	g2int_reclaim_gsi_instance(gsi_instance,Qg2int_context);
    return VALUES_1(Nil);
}

/* RECLAIM-GSI-INSTANCE-FOR-USER */
Object g2int_reclaim_gsi_instance_for_user(gsi_instance)
    Object gsi_instance;
{
    x_note_fn_call(43,58);
    g2int_reclaim_gsi_instance(gsi_instance,Qg2int_user);
    return VALUES_1(Nil);
}

static Object Qg2int_item_index_space;  /* item-index-space */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-GSI-INSTANCE */
Object g2int_establish_new_object_index_for_gsi_instance varargs_1(int, n)
{
    Object gsi_instance, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, gsi_instance_extension;
    Object gsi_instance_extension_1, svref_new_value;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(43,59);
    INIT_ARGS_nonrelocating();
    gsi_instance = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = g2int_assign_corresponding_icp_object_index(gsi_instance,
	    Qg2int_item_index_space,send_enlarge_message_p);
    MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(gsi_instance,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    gsi_instance_extension_1 = ISVREF(gsi_instance,(SI_Long)3L);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    gsi_instance_extension_1 ? ISVREF(gsi_instance_extension_1,
	    (SI_Long)13L) : Nil));
    SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = svref_new_value;
    if (send_enlarge_message_p)
	return VALUES_1(corresponding_icp_object_index);
    else
	return VALUES_2(corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
}

Object G2int_corresponding_icp_object_index_for_item_reference = UNBOUND;

/* MAKE-CORRESPONDING-ICP-GSI-INSTANCE */
Object g2int_make_corresponding_icp_gsi_instance(gsi_instance)
    Object gsi_instance;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, gsi_instance_extension, temp;
    Object gsi_instance_extension_1, svref_new_value;
    Object corresponding_icp_object_index_for_item_reference;
    Declare_special(2);
    Object result;

    x_note_fn_call(43,60);
    g2int_write_icp_maybe_suspend();
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    1);
      result = g2int_assign_corresponding_icp_object_index(gsi_instance,
	      Qg2int_item_index_space,T);
      MVS_2(result,corresponding_icp_object_index,new_index_limit_plus_one_qm);
      gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
      if ( !TRUEP(gsi_instance_extension)) {
	  gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	  SVREF(gsi_instance,FIX((SI_Long)3L)) = gsi_instance_extension;
      }
      temp = G2int_current_icp_port;
      gsi_instance_extension_1 = ISVREF(gsi_instance,(SI_Long)3L);
      svref_new_value = g2int_gensym_cons_1(temp,
	      g2int_gensym_cons_1(corresponding_icp_object_index,
	      gsi_instance_extension_1 ? ISVREF(gsi_instance_extension_1,
	      (SI_Long)13L) : Nil));
      SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = svref_new_value;
      if (T);
      else {
	  temp = corresponding_icp_object_index;
	  corresponding_icp_object_index = temp;
      }
      if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	  corresponding_icp_object_index_for_item_reference = 
		  corresponding_icp_object_index;
	  PUSH_SPECIAL(G2int_corresponding_icp_object_index_for_item_reference,corresponding_icp_object_index_for_item_reference,
		  0);
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)12L)
		g2int_send_icp_create_item_reference(gsi_instance);
	  POP_SPECIAL();
      }
      result = VALUES_1(corresponding_icp_object_index);
    POP_SPECIAL();
    return result;
}

/* GET-ICP-OBJECT-INDEX-FOR-GSI-INSTANCE */
Object g2int_get_icp_object_index_for_gsi_instance(gsi_instance,icp_port)
    Object gsi_instance, icp_port;
{
    Object gsi_instance_extension;

    x_note_fn_call(43,61);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    return g2int_getfq_function_no_default(gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)13L) : Nil,icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-GSI-INSTANCE */
Object g2int_set_icp_object_index_for_gsi_instance(gsi_instance,
	    corresponding_icp_object_index,icp_port)
    Object gsi_instance, corresponding_icp_object_index, icp_port;
{
    Object gsi_instance_extension, gsi_instance_extension_1, svref_new_value;

    x_note_fn_call(43,62);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(gsi_instance,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    gsi_instance_extension_1 = ISVREF(gsi_instance,(SI_Long)3L);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    gsi_instance_extension_1 ? ISVREF(gsi_instance_extension_1,
	    (SI_Long)13L) : Nil));
    return VALUES_1(SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-GSI-INSTANCE */
Object g2int_reclaim_icp_object_map_for_gsi_instance(gsi_instance)
    Object gsi_instance;
{
    Object gsi_instance_extension, icp_object_map;

    x_note_fn_call(43,63);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    icp_object_map = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)13L) : Nil;
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(gsi_instance,icp_object_map,
		Qg2int_item_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_gsi_instance;  /* set-access-form-for-gsi-instance */

/* RECLAIM-ICP-PORT-ENTRY-FOR-GSI-INSTANCE */
Object g2int_reclaim_icp_port_entry_for_gsi_instance(gsi_instance,icp_port)
    Object gsi_instance, icp_port;
{
    Object gsi_instance_extension;

    x_note_fn_call(43,64);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    return g2int_reclaim_icp_port_entry(icp_port,gsi_instance,
	    gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)13L) : Nil,Qg2int_set_access_form_for_gsi_instance);
}

/* SET-ACCESS-FORM-FOR-GSI-INSTANCE */
Object g2int_set_access_form_for_gsi_instance(gsi_instance,new_value)
    Object gsi_instance, new_value;
{
    Object gsi_instance_extension;

    x_note_fn_call(43,65);
    gsi_instance_extension = ISVREF(gsi_instance,(SI_Long)3L);
    if ( !TRUEP(gsi_instance_extension)) {
	gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	SVREF(gsi_instance,FIX((SI_Long)3L)) = gsi_instance_extension;
    }
    return VALUES_1(SVREF(gsi_instance_extension,FIX((SI_Long)13L)) = 
	    new_value);
}

Object G2int_gsi_user_data_of_symbol_prop = UNBOUND;

Object G2int_gsi_most_recent_error = UNBOUND;

Object G2int_gsi_most_recent_error_message = UNBOUND;

Object G2int_gsi_most_recent_error_remote_procedure_identifier = UNBOUND;

Object G2int_in_unprotected_gsi_api_call_p = UNBOUND;

Object G2int_gsi_protect_inner_calls_p = UNBOUND;

/* PROTECT-GSI-API-CALL-P */
Object g2int_protect_gsi_api_call_p()
{
    Object temp;

    x_note_fn_call(43,66);
    temp =  !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1( ! !TRUEP(G2int_gsi_protect_inner_calls_p) ? T : Nil);
}

static Object Qg2int_gsi_typed_array;  /* gsi-typed-array */

/* GSI-STRING-TYPE-P */
Object g2int_gsi_string_type_p(type)
    Object type;
{
    Object temp;

    x_note_fn_call(43,67);
    if (ATOM(type)) {
	if (SYMBOLP(type))
	    return get(type,Qstringp,_);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(CAR(type),Qg2int_gsi_typed_array)) {
	temp = EQ(CADR(type),Qstring) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(EQ(CADR(type),Qsymbol) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GSI-API-SYMBOL-TO-SYMBOL-OR-NIL-1 */
Object g2int_gsi_api_symbol_to_symbol_or_nil_1(api_symbol,wide_api_p)
    Object api_symbol, wide_api_p;
{
    Object temp;

    x_note_fn_call(43,68);
    temp = g2int_gsi_option_is_set_p(G2int_gsi_new_symbol_api) ? 
	    api_symbol :  !TRUEP(api_symbol) ? Nil : 
	    g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(api_symbol) : 
	    g2int_c_string_to_gensym_string(api_symbol));
    return VALUES_1(temp);
}

Object G2int_gsi_encoded_symbol_names_prop = UNBOUND;

static Object Qg2int_gsi_encoded_symbol_names;  /* gsi-encoded-symbol-names */

/* GSI-STRING-FOR-SYMBOL */
Object g2int_gsi_string_for_symbol(symbol,wide_api_p)
    Object symbol, wide_api_p;
{
    Object temp, style_number, name_plist, string_1, new_name_plist;

    x_note_fn_call(43,69);
    if (wide_api_p)
	temp = g2int_symbol_name_text_string(symbol);
    else {
	style_number = g2int_current_gsi_string_conversion_style();
	if ((SI_Long)0L == IFIX(style_number))
	    temp = SYMBOL_NAME(symbol);
	else {
	    name_plist = 
		    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		    Qg2int_gsi_encoded_symbol_names);
	    temp = g2int_getfq_function_no_default(name_plist,style_number);
	    if (temp);
	    else {
		string_1 = 
			g2int_wide_string_to_gensym_string_for_gsi(g2int_symbol_name_text_string(symbol));
		new_name_plist = g2int_gensym_cons_1(style_number,
			g2int_gensym_cons_1(string_1,name_plist));
		g2int_mutate_global_property(symbol,new_name_plist,
			Qg2int_gsi_encoded_symbol_names);
		temp = string_1;
	    }
	}
    }
    return VALUES_1(temp);
}

/* SYMBOL-FOR-GSI-STRING */
Object g2int_symbol_for_gsi_string(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,70);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	temp = string_1;
    else if ((SI_Long)0L == IFIX(g2int_current_gsi_string_conversion_style()))
	temp = string_1;
    else {
	temp = g2int_gensym_string_to_wide_string_for_gsi(string_1);
	g2int_reclaim_gensym_string(string_1);
    }
    temp = g2int_gsi_intern(temp);
    return VALUES_1(temp);
}

/* GSI-INCOMING-SYMBOL-NAME */
Object g2int_gsi_incoming_symbol_name(symbol)
    Object symbol;
{
    x_note_fn_call(43,71);
    return VALUES_1(symbol);
}

/* GSI-OUTGOING-SYMBOL-NAME */
Object g2int_gsi_outgoing_symbol_name(symbol_qm)
    Object symbol_qm;
{
    x_note_fn_call(43,72);
    if (symbol_qm)
	return VALUES_1(inline_extract_c_string(SYMBOL_NAME(symbol_qm)));
    else
	return VALUES_1(Nil);
}

/* C-STRING-TO-TEXT-STRING */
Object g2int_c_string_to_text_string(c_string)
    Object c_string;
{
    Object gensym_string, text_string;

    x_note_fn_call(43,73);
    gensym_string = g2int_c_string_to_gensym_string(c_string);
    text_string = g2int_gensym_string_to_wide_string_for_gsi(gensym_string);
    g2int_reclaim_gensym_string(gensym_string);
    return VALUES_1(text_string);
}

/* C-WIDE-STRING-TO-TEXT-STRING */
Object g2int_c_wide_string_to_text_string(c_wide_string)
    Object c_wide_string;
{
    Object wide_string_bv16, temp, lisp_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;

    x_note_fn_call(43,74);
    if ( !TRUEP(c_wide_string)) {
	wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	temp = wide_string_bv16;
    }
    else {
	length_1 = IFIX(inline_get_length_of_c_wide_string(c_wide_string));
	wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_1 + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = length_1 & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | length_1 >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)0L);
	lisp_string = wide_string_bv16;
	inline_copy_byte_vector_16_portion_c_to_lisp(c_wide_string,
		(SI_Long)0L,UBYTE_16_SARRAY_TO_USHORT_PTR(lisp_string),
		(SI_Long)0L,length_1);
	temp = lisp_string;
    }
    return VALUES_1(temp);
}

/* C-UNSIGNED-SHORT-VECTOR-TO-TEXT-STRING */
Object g2int_c_unsigned_short_vector_to_text_string(c_unsigned_short_vector,
	    length_init)
    Object c_unsigned_short_vector, length_init;
{
    Object wide_string_bv16, lisp_string;
    SI_Long length_1, bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(43,75);
    length_1 = IFIX(length_init);
    wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_1 + 
	    (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = length_1 & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | length_1 >>  -  - (SI_Long)16L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)0L);
    lisp_string = wide_string_bv16;
    inline_copy_byte_vector_16_portion_c_to_lisp(c_unsigned_short_vector,
	    (SI_Long)0L,UBYTE_16_SARRAY_TO_USHORT_PTR(lisp_string),
	    (SI_Long)0L,length_1);
    return VALUES_1(lisp_string);
}

/* C-WIDE-STRING-TO-GENSYM-STRING */
Object g2int_c_wide_string_to_gensym_string(c_wide_string)
    Object c_wide_string;
{
    Object wide_string_bv16, lisp_string, text_string, gensym_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;

    x_note_fn_call(43,76);
    if ( !TRUEP(c_wide_string)) {
	wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
    }
    else {
	length_1 = IFIX(inline_get_length_of_c_wide_string(c_wide_string));
	wide_string_bv16 = g2int_allocate_byte_vector_16(FIX(length_1 + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = length_1 & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | length_1 >>  -  - (SI_Long)16L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,length_1,(SI_Long)0L);
	lisp_string = wide_string_bv16;
	inline_copy_byte_vector_16_portion_c_to_lisp(c_wide_string,
		(SI_Long)0L,UBYTE_16_SARRAY_TO_USHORT_PTR(lisp_string),
		(SI_Long)0L,length_1);
    }
    text_string = g2int_c_wide_string_to_text_string(c_wide_string);
    gensym_string = g2int_wide_string_to_gensym_string_for_gsi(text_string);
    g2int_reclaim_text_string(text_string);
    return VALUES_1(gensym_string);
}

Object G2int_temporary_string_buffer = UNBOUND;

/* LISP-STRING-TO-C-STRING */
Object g2int_lisp_string_to_c_string(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,77);
    if ( !(INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L))
	temp = string_1;
    else {
	if (G2int_temporary_string_buffer)
	    g2int_reclaim_text_or_gensym_string(G2int_temporary_string_buffer);
	G2int_temporary_string_buffer = 
		g2int_wide_string_to_gensym_string_for_gsi(string_1);
	temp = G2int_temporary_string_buffer;
    }
    temp = inline_extract_c_string(temp);
    return VALUES_1(temp);
}

/* LISP-STRING-TO-C-WIDE-STRING */
Object g2int_lisp_string_to_c_wide_string(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,78);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(string_1) != (SI_Long)0L)
	temp = string_1;
    else {
	if (G2int_temporary_string_buffer)
	    g2int_reclaim_text_or_gensym_string(G2int_temporary_string_buffer);
	G2int_temporary_string_buffer = 
		g2int_gensym_string_to_wide_string_for_gsi(string_1);
	temp = G2int_temporary_string_buffer;
    }
    temp = inline_extract_c_wide_string(temp);
    return VALUES_1(temp);
}

/* LISP-STRING-TO-C-UNSIGNED-SHORT-VECTOR */
Object g2int_lisp_string_to_c_unsigned_short_vector(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,79);
    temp = inline_extract_c_wide_string(string_1);
    return VALUES_1(temp);
}

/* GENSYM-STRING-TO-WIDE-STRING-FOR-GSI */
Object g2int_gensym_string_to_wide_string_for_gsi(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,80);
    temp = g2int_import_text_string_per_text_conversion_style(4,string_1,
	    g2int_text_conversion_style_for_gsi(g2int_current_gsi_string_conversion_style(),
	    Nil),Nil,Nil);
    return VALUES_1(temp);
}

/* WIDE-STRING-TO-GENSYM-STRING-FOR-GSI */
Object g2int_wide_string_to_gensym_string_for_gsi(string_1)
    Object string_1;
{
    Object temp;

    x_note_fn_call(43,81);
    temp = g2int_export_text_string_per_text_conversion_style(4,string_1,
	    g2int_text_conversion_style_for_gsi(g2int_current_gsi_string_conversion_style(),
	    Nil),Nil,Nil);
    return VALUES_1(temp);
}

/* GSI-RECLAIM-DISPLACED-ARRAY */
Object g2int_gsi_reclaim_displaced_array(displaced_array_qm)
    Object displaced_array_qm;
{
    x_note_fn_call(43,82);
    if (displaced_array_qm)
	return g2int_gsi_reclaim_managed_array(displaced_array_qm);
    else
	return VALUES_1(Nil);
}

Object G2int_gsi_timestamp_upper_bound = UNBOUND;

static Object string_constant_1;   /* "Out-of-range timestamp seen in ~a:~%~
				    *      timestamp: ~d  Valid range: 0.0 < t < ~d"
				    */

/* NOTIFY-USER-OF-OUT-OF-BOUNDS-TIMESTAMP */
Object g2int_notify_user_of_out_of_bounds_timestamp(where,timestamp)
    Object where, timestamp;
{
    Object temp;

    x_note_fn_call(43,83);
    temp = g2int_notify_user_at_console(4,string_constant_1,where,
	    timestamp,G2int_gsi_timestamp_upper_bound);
    return VALUES_1(temp);
}

Object G2int_last_gsi_timestamp_year = UNBOUND;

Object G2int_last_gsi_timestamp_month = UNBOUND;

Object G2int_last_gsi_timestamp_day = UNBOUND;

Object G2int_last_gsi_timestamp_hour = UNBOUND;

Object G2int_last_gsi_timestamp_unix_time = UNBOUND;

static Object Qg2int_read_icp_gsi_timestamp;  /* read-icp-gsi-timestamp */

static Object Qg2int_gensym;       /* gensym */

static Object Qg2int_true;         /* true */

static Object Qg2int_false;        /* false */

/* READ-ICP-GSI-TIMESTAMP */
Object g2int_read_icp_gsi_timestamp()
{
    Object tag_temp, amf_available_array_cons_qm, amf_array, temp;
    Object svref_new_value, amf_result, incff_1_arg, new_float, temp_1, year;
    Object month, day, hour, minute, second_1, resumable_icp_state_1;
    Object icp_suspend_1, top, test, arg1, value_1;
    char temp_2;
    double aref_new_value, new_cached_gsi_timestamp_unix_time, value;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(43,84);
    tag_temp = UNIQUE_TAG(Qg2int_read_icp_gsi_timestamp);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
			(SI_Long)5L) {
		    amf_available_array_cons_qm = 
			    ISVREF(G2int_vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = G2int_vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qg2int_gensym);
			temp = G2int_available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp;
			G2int_available_gensym_conses = 
				amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp = 
				FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			G2int_created_simple_float_array_pool_arrays = temp;
			incff_1_arg = 
				g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp = 
				FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				incff_1_arg);
			G2int_simple_float_array_pool_memory_usage = temp;
			amf_result = 
				g2int_generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = g2int_read_icp_double_float_1();
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_1 = new_float;
		}
		else {
		    year = g2int_read_icp_integer();
		    month = g2int_read_icp_integer();
		    day = g2int_read_icp_integer();
		    hour = g2int_read_icp_integer();
		    minute = g2int_read_icp_integer();
		    second_1 = g2int_read_icp_integer();
		    if (IFIX(year) == (SI_Long)0L && IFIX(month) == 
			    (SI_Long)0L && IFIX(day) == (SI_Long)0L)
			temp_1 = 
				g2int_gensym_encode_unix_time_as_managed_float(FIX((SI_Long)0L),
				FIX((SI_Long)0L),FIX((SI_Long)0L),
				FIX((SI_Long)1L),FIX((SI_Long)1L),
				FIX((SI_Long)1970L));
		    else if (FIXNUM_EQ(hour,G2int_last_gsi_timestamp_hour) 
			    && FIXNUM_EQ(day,G2int_last_gsi_timestamp_day) 
			    && FIXNUM_EQ(month,
			    G2int_last_gsi_timestamp_month) && 
			    FIXNUM_EQ(year,G2int_last_gsi_timestamp_year)) {
			amf_available_array_cons_qm = 
				ISVREF(G2int_vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp = G2int_vector_of_simple_float_array_pools;
			    svref_new_value = 
				    M_CDR(amf_available_array_cons_qm);
			    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qg2int_gensym);
			    temp = G2int_available_gensym_conses;
			    M_CDR(amf_available_array_cons_qm) = temp;
			    G2int_available_gensym_conses = 
				    amf_available_array_cons_qm;
			    amf_result = amf_array;
			}
			else {
			    temp = 
				    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			    G2int_created_simple_float_array_pool_arrays = 
				    temp;
			    incff_1_arg = 
				    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			    temp = 
				    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				    incff_1_arg);
			    G2int_simple_float_array_pool_memory_usage = temp;
			    amf_result = 
				    g2int_generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				DFLOAT_ISAREF_1(G2int_last_gsi_timestamp_unix_time,
				(SI_Long)0L) + (double)((SI_Long)60L * 
				IFIX(minute) + IFIX(second_1));
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = new_float;
		    }
		    else {
			temp_1 = 
				g2int_gensym_encode_unix_time_as_gensym_float(FIX((SI_Long)0L),
				FIX((SI_Long)0L),hour,day,month,year);
			new_cached_gsi_timestamp_unix_time = 
				DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			temp = G2int_last_gsi_timestamp_unix_time;
			DFLOAT_ISASET_1(temp,(SI_Long)0L,
				new_cached_gsi_timestamp_unix_time);
			G2int_last_gsi_timestamp_year = year;
			G2int_last_gsi_timestamp_month = month;
			G2int_last_gsi_timestamp_day = day;
			G2int_last_gsi_timestamp_hour = hour;
			amf_available_array_cons_qm = 
				ISVREF(G2int_vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp = G2int_vector_of_simple_float_array_pools;
			    svref_new_value = 
				    M_CDR(amf_available_array_cons_qm);
			    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qg2int_gensym);
			    temp = G2int_available_gensym_conses;
			    M_CDR(amf_available_array_cons_qm) = temp;
			    G2int_available_gensym_conses = 
				    amf_available_array_cons_qm;
			    amf_result = amf_array;
			}
			else {
			    temp = 
				    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			    G2int_created_simple_float_array_pool_arrays = 
				    temp;
			    incff_1_arg = 
				    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			    temp = 
				    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				    incff_1_arg);
			    G2int_simple_float_array_pool_memory_usage = temp;
			    amf_result = 
				    g2int_generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				new_cached_gsi_timestamp_unix_time + 
				(double)((SI_Long)60L * IFIX(minute) + 
				IFIX(second_1));
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = new_float;
		    }
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_read_icp_gsi_timestamp,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,Qg2int_read_icp_gsi_timestamp,
			    top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_2 = TRUEP(test);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2 ? EQ(test,Qg2int_true) : 
			IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)21L)) >= (SI_Long)5L) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			arg1 = g2int_resumable_icp_pop();
		    else {
			value = g2int_read_icp_double_float_1();
			if (EQ(icp_suspend_1,DOUBLE_TO_DOUBLE_FLOAT(value))) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			arg1 = DOUBLE_TO_DOUBLE_FLOAT(value);
		    }
		    amf_available_array_cons_qm = 
			    ISVREF(G2int_vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp = G2int_vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qg2int_gensym);
			temp = G2int_available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp;
			G2int_available_gensym_conses = 
				amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp = 
				FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			G2int_created_simple_float_array_pool_arrays = temp;
			incff_1_arg = 
				g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp = 
				FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				incff_1_arg);
			G2int_simple_float_array_pool_memory_usage = temp;
			amf_result = 
				g2int_generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(arg1);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    temp_1 = new_float;
		}
		else {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			year = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			year = value_1;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			month = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(year);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			month = value_1;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			day = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(month);
			    g2int_resumable_icp_push(year);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			day = value_1;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			hour = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(day);
			    g2int_resumable_icp_push(month);
			    g2int_resumable_icp_push(year);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			hour = value_1;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			minute = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(hour);
			    g2int_resumable_icp_push(day);
			    g2int_resumable_icp_push(month);
			    g2int_resumable_icp_push(year);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			minute = value_1;
		    }
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			second_1 = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(minute);
			    g2int_resumable_icp_push(hour);
			    g2int_resumable_icp_push(day);
			    g2int_resumable_icp_push(month);
			    g2int_resumable_icp_push(year);
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(Qg2int_read_icp_gsi_timestamp);
			    result = VALUES_1(G2int_icp_suspend);
			    THROW(tag_temp,result);
			}
			second_1 = value_1;
		    }
		    if (IFIX(year) == (SI_Long)0L && IFIX(month) == 
			    (SI_Long)0L && IFIX(day) == (SI_Long)0L)
			temp_1 = 
				g2int_gensym_encode_unix_time_as_managed_float(FIX((SI_Long)0L),
				FIX((SI_Long)0L),FIX((SI_Long)0L),
				FIX((SI_Long)1L),FIX((SI_Long)1L),
				FIX((SI_Long)1970L));
		    else if (FIXNUM_EQ(hour,G2int_last_gsi_timestamp_hour) 
			    && FIXNUM_EQ(day,G2int_last_gsi_timestamp_day) 
			    && FIXNUM_EQ(month,
			    G2int_last_gsi_timestamp_month) && 
			    FIXNUM_EQ(year,G2int_last_gsi_timestamp_year)) {
			amf_available_array_cons_qm = 
				ISVREF(G2int_vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp = G2int_vector_of_simple_float_array_pools;
			    svref_new_value = 
				    M_CDR(amf_available_array_cons_qm);
			    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qg2int_gensym);
			    temp = G2int_available_gensym_conses;
			    M_CDR(amf_available_array_cons_qm) = temp;
			    G2int_available_gensym_conses = 
				    amf_available_array_cons_qm;
			    amf_result = amf_array;
			}
			else {
			    temp = 
				    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			    G2int_created_simple_float_array_pool_arrays = 
				    temp;
			    incff_1_arg = 
				    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			    temp = 
				    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				    incff_1_arg);
			    G2int_simple_float_array_pool_memory_usage = temp;
			    amf_result = 
				    g2int_generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				DFLOAT_ISAREF_1(G2int_last_gsi_timestamp_unix_time,
				(SI_Long)0L) + (double)((SI_Long)60L * 
				IFIX(minute) + IFIX(second_1));
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = new_float;
		    }
		    else {
			temp_1 = 
				g2int_gensym_encode_unix_time_as_gensym_float(FIX((SI_Long)0L),
				FIX((SI_Long)0L),hour,day,month,year);
			new_cached_gsi_timestamp_unix_time = 
				DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			temp = G2int_last_gsi_timestamp_unix_time;
			DFLOAT_ISASET_1(temp,(SI_Long)0L,
				new_cached_gsi_timestamp_unix_time);
			G2int_last_gsi_timestamp_year = year;
			G2int_last_gsi_timestamp_month = month;
			G2int_last_gsi_timestamp_day = day;
			G2int_last_gsi_timestamp_hour = hour;
			amf_available_array_cons_qm = 
				ISVREF(G2int_vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp = G2int_vector_of_simple_float_array_pools;
			    svref_new_value = 
				    M_CDR(amf_available_array_cons_qm);
			    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qg2int_gensym);
			    temp = G2int_available_gensym_conses;
			    M_CDR(amf_available_array_cons_qm) = temp;
			    G2int_available_gensym_conses = 
				    amf_available_array_cons_qm;
			    amf_result = amf_array;
			}
			else {
			    temp = 
				    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			    G2int_created_simple_float_array_pool_arrays = 
				    temp;
			    incff_1_arg = 
				    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			    temp = 
				    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				    incff_1_arg);
			    G2int_simple_float_array_pool_memory_usage = temp;
			    amf_result = 
				    g2int_generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			aref_new_value = 
				new_cached_gsi_timestamp_unix_time + 
				(double)((SI_Long)60L * IFIX(minute) + 
				IFIX(second_1));
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			temp_1 = new_float;
		    }
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp_1);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

static Object Qg2int_write_icp_gsi_timestamp;  /* write-icp-gsi-timestamp */

/* WRITE-ICP-GSI-TIMESTAMP */
Object g2int_write_icp_gsi_timestamp(gsi_timestamp)
    Object gsi_timestamp;
{
    Object tag_temp, temp, year, month, day, hour, minute, second_1;
    Object resumable_icp_state_1, icp_suspend_1, top, test, value, temp_2;
    Object temp_3, temp_4, temp_5, temp_6, v1, v2, v3;
    char temp_1;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(43,85);
    tag_temp = UNIQUE_TAG(Qg2int_write_icp_gsi_timestamp);
    if (PUSH_CATCH(tag_temp,0)) {
	if (G2int_disable_resumability) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)5L)
		    temp = 
			    g2int_write_icp_double_float_1(DFLOAT_ISAREF_1(gsi_timestamp,
			    (SI_Long)0L));
		else {
		    result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gsi_timestamp,
			    (SI_Long)0L)));
		    MVS_6(result,year,month,day,hour,minute,second_1);
		    g2int_write_icp_integer(year);
		    g2int_write_icp_integer(month);
		    g2int_write_icp_integer(day);
		    g2int_write_icp_integer(hour);
		    g2int_write_icp_integer(minute);
		    temp = g2int_write_icp_integer(second_1);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	    icp_suspend_1 = G2int_icp_suspend;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		top = g2int_resumable_icp_pop();
		if ( !EQ(Qg2int_write_icp_gsi_timestamp,top)) {
		    result = g2int_icp_error_internal(Qerror,
			    string_constant,Qg2int_write_icp_gsi_timestamp,
			    top,Nil);
		    THROW(tag_temp,result);
		}
	    }
	    gsi_timestamp = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : gsi_timestamp;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)22L)) >= (SI_Long)5L) {
		    value = 
			    g2int_write_icp_double_float_1(DFLOAT_ISAREF_1(gsi_timestamp,
			    (SI_Long)0L));
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(gsi_timestamp);
			g2int_resumable_icp_push(Qg2int_write_icp_gsi_timestamp);
			result = VALUES_1(G2int_icp_suspend);
			THROW(tag_temp,result);
		    }
		    temp = value;
		}
		else {
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp_2 = g2int_resumable_icp_pop();
			temp_3 = g2int_resumable_icp_pop();
			temp_4 = g2int_resumable_icp_pop();
			temp_5 = g2int_resumable_icp_pop();
			temp_6 = g2int_resumable_icp_pop();
			temp = g2int_resumable_icp_pop();
			result = VALUES_6(temp_2,temp_3,temp_4,temp_5,
				temp_6,temp);
		    }
		    else
			result = g2int_gensym_decode_unix_time(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(gsi_timestamp,
				(SI_Long)0L)));
		    MVS_6(result,year,month,day,hour,minute,second_1);
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				goto l1;
				break;
			      case 2:
				goto l2;
				break;
			      case 3:
				goto l3;
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
			      default:
				break;
			    }
		    }
		  l1:
		    if (EQ(icp_suspend_1,g2int_write_icp_integer(year))) {
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		  l2:
		    if (EQ(icp_suspend_1,g2int_write_icp_integer(month))) {
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		  l3:
		    if (EQ(icp_suspend_1,g2int_write_icp_integer(day))) {
			g2int_resumable_icp_push(FIX((SI_Long)3L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		  l4:
		    if (EQ(icp_suspend_1,g2int_write_icp_integer(hour))) {
			g2int_resumable_icp_push(FIX((SI_Long)4L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		  l5:
		    if (EQ(icp_suspend_1,g2int_write_icp_integer(minute))) {
			g2int_resumable_icp_push(FIX((SI_Long)5L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		  l6:
		    value = g2int_write_icp_integer(second_1);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(FIX((SI_Long)6L));
			result = VALUES_1(G2int_icp_suspend);
			goto end_block;
		    }
		    result = VALUES_1(value);
		    goto end_block;
		  end_block:
		    MVS_3(result,v1,v2,v3);
		    if (EQ(icp_suspend_1,v1)) {
			g2int_resumable_icp_push(second_1);
			g2int_resumable_icp_push(minute);
			g2int_resumable_icp_push(hour);
			g2int_resumable_icp_push(day);
			g2int_resumable_icp_push(month);
			g2int_resumable_icp_push(year);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(gsi_timestamp);
			g2int_resumable_icp_push(Qg2int_write_icp_gsi_timestamp);
			result = VALUES_1(G2int_icp_suspend);
			THROW(tag_temp,result);
		    }
		    temp = v1;
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	result = VALUES_1(temp);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

Object G2int_rpc_argument_list_error = UNBOUND;

static Object Qg2int_read_icp_returned_gsi_sensor;  /* read-icp-returned-gsi-sensor */

/* READ-ICP-RETURNED-GSI-SENSOR */
Object g2int_read_icp_returned_gsi_sensor()
{
    Object temp, rpc_argument_list_error, handle_or_item;
    Object resumable_icp_state_1, icp_suspend_1, top, test, key, value;
    Object gensymed_symbol;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,86);
    if (G2int_disable_resumability) {
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)18L) {
	    temp = g2int_peek_icp_byte();
	    if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		    FIXNUM_LE(temp,FIX((SI_Long)127L)))) {
		rpc_argument_list_error = Nil;
		PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
			0);
		  temp = g2int_read_icp_item_reference();
		  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(G2int_rpc_argument_list_error) 
			  != (SI_Long)0L)
		      g2int_reclaim_wide_string(G2int_rpc_argument_list_error);
		  handle_or_item = temp;
		POP_SPECIAL();
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    g2int_read_icp_byte();
		    handle_or_item = g2int_read_icp_integer();
		    break;
		  default:
		    rpc_argument_list_error = Nil;
		    PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
			    0);
		      temp = g2int_read_icp_item_reference();
		      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(G2int_rpc_argument_list_error) 
			      != (SI_Long)0L)
			  g2int_reclaim_wide_string(G2int_rpc_argument_list_error);
		      handle_or_item = temp;
		    POP_SPECIAL();
		    break;
		}
	}
	else
	    handle_or_item = g2int_read_icp_unsigned_integer();
	temp = FIXNUMP(handle_or_item) ? 
		g2int_get_from_icp_port_if_any(ISVREF(ISVREF(G2int_current_icp_port,
		(SI_Long)2L),(SI_Long)4L),handle_or_item,
		Qg2int_item_index_space) : handle_or_item;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_returned_gsi_sensor,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_returned_gsi_sensor,top,Nil);
		goto end_read_icp_returned_gsi_sensor;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    handle_or_item = g2int_resumable_icp_pop();
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : 
		    IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)18L) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    key = g2int_resumable_icp_pop();
		else {
		    value = g2int_peek_icp_byte();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_read_icp_returned_gsi_sensor);
			result = VALUES_1(G2int_icp_suspend);
			goto end_read_icp_returned_gsi_sensor;
		    }
		    key = value;
		}
		if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) 
			&& FIXNUM_LE(key,FIX((SI_Long)127L)))) {
		    rpc_argument_list_error = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : Nil;
		    PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
			    0);
		      if ((resumable_icp_state_1 ? 
			      TRUEP(G2int_starresumable_icp_statestar) : 
			      TRUEP(Nil)) &&  
			      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			  gensymed_symbol = g2int_resumable_icp_pop();
		      else {
			  value = g2int_read_icp_item_reference();
			  if (EQ(icp_suspend_1,value)) {
			      g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			      g2int_resumable_icp_push(G2int_rpc_argument_list_error);
			      g2int_resumable_icp_push(key);
			      g2int_resumable_icp_push(Qg2int_true);
			      g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			      g2int_resumable_icp_push(Qg2int_read_icp_returned_gsi_sensor);
			      result = VALUES_1(G2int_icp_suspend);
			      POP_SPECIAL();
			      goto end_read_icp_returned_gsi_sensor;
			  }
			  gensymed_symbol = value;
		      }
		      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(G2int_rpc_argument_list_error) 
			      != (SI_Long)0L)
			  g2int_reclaim_wide_string(G2int_rpc_argument_list_error);
		      handle_or_item = gensymed_symbol;
		    POP_SPECIAL();
		}
		else
		    switch (INTEGER_TO_CHAR(key)) {
		      case 1:
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    temp = g2int_resumable_icp_pop();
			    if (! !(FIXNUMP(temp) && 
				    FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				    FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
			if (EQ(icp_suspend_1,g2int_read_icp_byte())) {
			    g2int_resumable_icp_push(FIX((SI_Long)1L));
			    value = G2int_icp_suspend;
			    goto end_block;
			}
		      l2:
			value = g2int_read_icp_integer();
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(FIX((SI_Long)2L));
			    value = G2int_icp_suspend;
			    goto end_block;
			}
			goto end_block;
		      end_block:
			if (EQ(icp_suspend_1,value)) {
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_returned_gsi_sensor);
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_read_icp_returned_gsi_sensor;
			}
			handle_or_item = value;
			break;
		      default:
			rpc_argument_list_error = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			PUSH_SPECIAL(G2int_rpc_argument_list_error,rpc_argument_list_error,
				0);
			  if ((resumable_icp_state_1 ? 
				  TRUEP(G2int_starresumable_icp_statestar) 
				  : TRUEP(Nil)) &&  
				  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			      gensymed_symbol = g2int_resumable_icp_pop();
			  else {
			      value = g2int_read_icp_item_reference();
			      if (EQ(icp_suspend_1,value)) {
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(G2int_rpc_argument_list_error);
				  g2int_resumable_icp_push(key);
				  g2int_resumable_icp_push(Qg2int_true);
				  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				  g2int_resumable_icp_push(Qg2int_read_icp_returned_gsi_sensor);
				  result = VALUES_1(G2int_icp_suspend);
				  POP_SPECIAL();
				  goto end_read_icp_returned_gsi_sensor;
			      }
			      gensymed_symbol = value;
			  }
			  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(G2int_rpc_argument_list_error) 
				  != (SI_Long)0L)
			      g2int_reclaim_wide_string(G2int_rpc_argument_list_error);
			  handle_or_item = gensymed_symbol;
			POP_SPECIAL();
			break;
		    }
	    }
	    else {
		value = g2int_read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_read_icp_returned_gsi_sensor);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_icp_returned_gsi_sensor;
		}
		handle_or_item = value;
	    }
	}
	temp = FIXNUMP(handle_or_item) ? 
		g2int_get_from_icp_port_if_any(ISVREF(ISVREF(G2int_current_icp_port,
		(SI_Long)2L),(SI_Long)4L),handle_or_item,
		Qg2int_item_index_space) : handle_or_item;
    }
    result = VALUES_1(temp);
  end_read_icp_returned_gsi_sensor:
    return result;
}

static Object Qg2int_write_icp_returned_gsi_sensor;  /* write-icp-returned-gsi-sensor */

/* WRITE-ICP-RETURNED-GSI-SENSOR */
Object g2int_write_icp_returned_gsi_sensor(returned_gsi_sensor)
    Object returned_gsi_sensor;
{
    Object temp, current_icp_input_port, gsi_instance_extension;
    Object icp_object_map, resumable_icp_state_1, icp_suspend_1, top, test;
    Object value, v1, v2, v3;
    char temp_1;
    Object result;

    x_note_fn_call(43,87);
    if (G2int_disable_resumability) {
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)18L) {
	    if (FIXNUMP(returned_gsi_sensor)) {
		g2int_write_icp_byte(FIX((SI_Long)1L));
		temp = g2int_write_icp_integer(returned_gsi_sensor);
	    }
	    else
		temp = g2int_write_icp_item_reference(returned_gsi_sensor);
	}
	else {
	    if (FIXNUMP(returned_gsi_sensor))
		temp = returned_gsi_sensor;
	    else {
		current_icp_input_port = 
			ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),
			(SI_Long)3L);
		gsi_instance_extension = ISVREF(returned_gsi_sensor,
			(SI_Long)3L);
		icp_object_map = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)13L) : Nil;
		temp = g2int_getfq_function_no_default(icp_object_map,
			current_icp_input_port);
	    }
	    temp = g2int_write_icp_unsigned_integer(temp);
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_returned_gsi_sensor,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_returned_gsi_sensor,top,Nil);
	}
	returned_gsi_sensor = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : returned_gsi_sensor;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)18L) {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_1 = TRUEP(test);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(test,Qg2int_true) : FIXNUMP(returned_gsi_sensor)) {
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    temp = g2int_resumable_icp_pop();
		    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),
			    temp) && FIXNUM_LE(temp,FIX((SI_Long)127L))))
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
		if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)1L)))) {
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	      l2:
		value = g2int_write_icp_integer(returned_gsi_sensor);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
		result = VALUES_1(value);
		goto end_block;
	      end_block:
		MVS_3(result,v1,v2,v3);
		if (EQ(icp_suspend_1,v1)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(returned_gsi_sensor);
		    g2int_resumable_icp_push(Qg2int_write_icp_returned_gsi_sensor);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = v1;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || T) {
		value = g2int_write_icp_item_reference(returned_gsi_sensor);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(returned_gsi_sensor);
		    g2int_resumable_icp_push(Qg2int_write_icp_returned_gsi_sensor);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else
		temp = Qnil;
	}
	else {
	    if (FIXNUMP(returned_gsi_sensor))
		temp = returned_gsi_sensor;
	    else {
		current_icp_input_port = 
			ISVREF(ISVREF(G2int_current_icp_port,(SI_Long)2L),
			(SI_Long)3L);
		gsi_instance_extension = ISVREF(returned_gsi_sensor,
			(SI_Long)3L);
		icp_object_map = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)13L) : Nil;
		temp = g2int_getfq_function_no_default(icp_object_map,
			current_icp_input_port);
	    }
	    value = g2int_write_icp_unsigned_integer(temp);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(returned_gsi_sensor);
		g2int_resumable_icp_push(Qg2int_write_icp_returned_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_never;        /* never */

static Object Qg2int_attribute;    /* attribute */

static Object Qg2int_class_qualified_name;  /* class-qualified-name */

static Object Qg2int_read_icp_gsi_value_vector;  /* read-icp-gsi-value-vector */

/* READ-ICP-GSI-VALUE-VECTOR */
Object g2int_read_icp_gsi_value_vector()
{
    Object vector_length, element_name, element_value_qm, timestamp_present_qm;
    Object timestamp_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top, value, test;
    Object arg1;
    SI_Long count_1, ab_loop_bind_;
    char temp_2;

    x_note_fn_call(43,88);
    if (G2int_disable_resumability) {
	vector_length = g2int_read_icp_byte();
	count_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(vector_length);
	element_name = Nil;
	element_value_qm = Nil;
	timestamp_present_qm = Nil;
	timestamp_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (count_1 >= ab_loop_bind_)
	    goto end_loop;
	element_name = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) 
		>= (SI_Long)8L ? g2int_read_icp_icp_tree() : 
		g2int_intern_text_string(1,g2int_read_icp_text_string());
	element_value_qm = g2int_read_icp_remote_value();
	timestamp_present_qm = g2int_read_icp_boolean();
	timestamp_qm = timestamp_present_qm ? 
		g2int_read_icp_gsi_timestamp() : Qg2int_never;
	if (CONSP(element_name) && EQ(CAR(element_name),Qg2int_attribute)) {
	    if ( !TRUEP(SECOND(element_name))) {
		temp = THIRD(element_name);
		g2int_reclaim_gensym_list_1(element_name);
	    }
	    else {
		M_CAR(element_name) = Qg2int_class_qualified_name;
		temp = element_name;
	    }
	}
	else
	    temp = element_name;
	temp_1 = g2int_convert_value_to_gsi_value(element_value_qm);
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_gensym_list_3(temp,
		temp_1,timestamp_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end;
	temp_1 = Qnil;
      end:;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gsi_value_vector,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gsi_value_vector,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    vector_length = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_byte();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    vector_length = value;
	}
	count_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	ab_loop_bind_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		IFIX(g2int_resumable_icp_pop()) : IFIX(vector_length);
	element_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	element_value_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	timestamp_present_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	timestamp_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar_ = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	ab_loopvar__2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp_1 = g2int_resumable_icp_pop();
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
		  case 4:
		    goto l4;
		    break;
		  default:
		    break;
		}
	}
      next_loop_1:
	if (count_1 >= ab_loop_bind_)
	    goto end_loop_1;
      l1:
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(test,Qg2int_true) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)8L) {
	    value = g2int_read_icp_icp_tree();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(FIX((SI_Long)1L));
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(timestamp_qm);
		g2int_resumable_icp_push(timestamp_present_qm);
		g2int_resumable_icp_push(element_value_qm);
		g2int_resumable_icp_push(element_name);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(count_1));
		g2int_resumable_icp_push(vector_length);
		g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    element_name = value;
	}
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(FIX((SI_Long)1L));
		    g2int_resumable_icp_push(ab_loopvar__2);
		    g2int_resumable_icp_push(ab_loopvar__1);
		    g2int_resumable_icp_push(ab_loopvar_);
		    g2int_resumable_icp_push(timestamp_qm);
		    g2int_resumable_icp_push(timestamp_present_qm);
		    g2int_resumable_icp_push(element_value_qm);
		    g2int_resumable_icp_push(element_name);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(count_1));
		    g2int_resumable_icp_push(vector_length);
		    g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg1 = value;
	    }
	    element_name = g2int_intern_text_string(1,arg1);
	}
      l2:
	value = g2int_read_icp_remote_value();
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(FIX((SI_Long)2L));
	    g2int_resumable_icp_push(ab_loopvar__2);
	    g2int_resumable_icp_push(ab_loopvar__1);
	    g2int_resumable_icp_push(ab_loopvar_);
	    g2int_resumable_icp_push(timestamp_qm);
	    g2int_resumable_icp_push(timestamp_present_qm);
	    g2int_resumable_icp_push(element_value_qm);
	    g2int_resumable_icp_push(element_name);
	    g2int_resumable_icp_push(FIX(ab_loop_bind_));
	    g2int_resumable_icp_push(FIX(count_1));
	    g2int_resumable_icp_push(vector_length);
	    g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
	    return VALUES_1(G2int_icp_suspend);
	}
	element_value_qm = value;
      l3:
	value = g2int_read_icp_boolean();
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(FIX((SI_Long)3L));
	    g2int_resumable_icp_push(ab_loopvar__2);
	    g2int_resumable_icp_push(ab_loopvar__1);
	    g2int_resumable_icp_push(ab_loopvar_);
	    g2int_resumable_icp_push(timestamp_qm);
	    g2int_resumable_icp_push(timestamp_present_qm);
	    g2int_resumable_icp_push(element_value_qm);
	    g2int_resumable_icp_push(element_name);
	    g2int_resumable_icp_push(FIX(ab_loop_bind_));
	    g2int_resumable_icp_push(FIX(count_1));
	    g2int_resumable_icp_push(vector_length);
	    g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
	    return VALUES_1(G2int_icp_suspend);
	}
	timestamp_present_qm = value;
      l4:
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		timestamp_present_qm) {
	    value = g2int_read_icp_gsi_timestamp();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(FIX((SI_Long)4L));
		g2int_resumable_icp_push(ab_loopvar__2);
		g2int_resumable_icp_push(ab_loopvar__1);
		g2int_resumable_icp_push(ab_loopvar_);
		g2int_resumable_icp_push(timestamp_qm);
		g2int_resumable_icp_push(timestamp_present_qm);
		g2int_resumable_icp_push(element_value_qm);
		g2int_resumable_icp_push(element_name);
		g2int_resumable_icp_push(FIX(ab_loop_bind_));
		g2int_resumable_icp_push(FIX(count_1));
		g2int_resumable_icp_push(vector_length);
		g2int_resumable_icp_push(Qg2int_read_icp_gsi_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    timestamp_qm = value;
	}
	else
	    timestamp_qm = Qg2int_never;
	if (CONSP(element_name) && EQ(CAR(element_name),Qg2int_attribute)) {
	    if ( !TRUEP(SECOND(element_name))) {
		temp = THIRD(element_name);
		g2int_reclaim_gensym_list_1(element_name);
	    }
	    else {
		M_CAR(element_name) = Qg2int_class_qualified_name;
		temp = element_name;
	    }
	}
	else
	    temp = element_name;
	temp_1 = g2int_convert_value_to_gsi_value(element_value_qm);
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_gensym_list_3(temp,
		temp_1,timestamp_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	count_1 = count_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    return VALUES_1(temp_1);
}

/* RECLAIM-GSI-VALUE-VECTOR */
Object g2int_reclaim_gsi_value_vector(value_vector)
    Object value_vector;
{
    x_note_fn_call(43,89);
    return VALUES_1(value_vector);
}

static Object Qg2int_send_icp_initialize_gsi_interface;  /* send-icp-initialize-gsi-interface */

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

/* SEND-ICP-INITIALIZE-GSI-INTERFACE */
Object g2int_send_icp_initialize_gsi_interface(interface_name,class_name,
	    keep_connection_on_g2_reset,listener_network_type,
	    listener_host_name,listener_port_name,
	    remote_process_initialization_string)
    Object interface_name, class_name, keep_connection_on_g2_reset;
    Object listener_network_type, listener_host_name, listener_port_name;
    Object remote_process_initialization_string;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,90);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_initialize_gsi_interface;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(interface_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(interface_name);
	  interface_name = temp_1;
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_name),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(class_name);
	  class_name = temp_1;
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(listener_network_type),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(listener_network_type);
	  listener_network_type = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)338L));
	  g2int_write_icp_corresponding_object_index(interface_name);
	  g2int_write_icp_corresponding_object_index(class_name);
	  g2int_write_icp_boolean(keep_connection_on_g2_reset);
	  g2int_write_icp_corresponding_object_index(listener_network_type);
	  g2int_write_icp_text_string(listener_host_name);
	  g2int_write_icp_text_string(listener_port_name);
	  g2int_write_icp_text_string(remote_process_initialization_string);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_initialize_gsi_interface,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_initialize_gsi_interface,top,Nil);
		goto end_send_icp_initialize_gsi_interface;
	    }
	}
	interface_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : interface_name;
	class_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : class_name;
	keep_connection_on_g2_reset = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : keep_connection_on_g2_reset;
	listener_network_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : listener_network_type;
	listener_host_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : listener_host_name;
	listener_port_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : listener_port_name;
	remote_process_initialization_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		remote_process_initialization_string;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_initialize_gsi_interface;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
		    case 4:
		      goto l4;
		      break;
		    case 5:
		      goto l5;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(interface_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      interface_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(interface_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      interface_name = value_1;
	  }
	l2:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_name),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      class_name = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(class_name);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      class_name = value_1;
	  }
	l3:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(listener_network_type),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      listener_network_type = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(listener_network_type);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      listener_network_type = value_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)338L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l5:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		      goto l4_1;
		      break;
		    case 5:
		      goto l5_1;
		      break;
		    case 6:
		      goto l6;
		      break;
		    case 7:
		      goto l7;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(interface_name))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(class_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_boolean(keep_connection_on_g2_reset))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(listener_network_type))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_text_string(listener_host_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_text_string(listener_port_name))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_text_string(remote_process_initialization_string))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(remote_process_initialization_string);
	      g2int_resumable_icp_push(listener_port_name);
	      g2int_resumable_icp_push(listener_host_name);
	      g2int_resumable_icp_push(listener_network_type);
	      g2int_resumable_icp_push(keep_connection_on_g2_reset);
	      g2int_resumable_icp_push(class_name);
	      g2int_resumable_icp_push(interface_name);
	      g2int_resumable_icp_push(Qg2int_send_icp_initialize_gsi_interface);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_initialize_gsi_interface;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_initialize_gsi_interface:
    return result;
}

static Object Qg2int_g2;           /* g2 */

/* HANDLE-ICP-INITIALIZE-GSI-INTERFACE--BODY */
Object g2int_handle_icp_initialize_gsi_interface__body(interface_name,
	    class_name,keep_connection_on_g2_reset,listener_network_type,
	    listener_host_name,listener_port_name,
	    remote_process_initialization_string)
    Object interface_name, class_name, keep_connection_on_g2_reset;
    Object listener_network_type, listener_host_name, listener_port_name;
    Object remote_process_initialization_string;
{
    x_note_fn_call(43,91);
    g2int_receive_initial_message(Qg2int_g2,Qg2int_gsi);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_initialize_gsi_interface;  /* handle-icp-initialize-gsi-interface */

/* HANDLE-ICP-INITIALIZE-GSI-INTERFACE */
Object g2int_handle_icp_initialize_gsi_interface()
{
    Object index_1, index_space, interface_name, class_name;
    Object keep_connection_on_g2_reset, listener_network_type;
    Object listener_host_name, listener_port_name;
    Object remote_process_initialization_string, abort_for_icp_catcher_qm;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,92);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    interface_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    interface_name = Nil;
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    class_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    class_name = Nil;
	keep_connection_on_g2_reset = g2int_read_icp_boolean();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    listener_network_type = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    listener_network_type = Nil;
	listener_host_name = g2int_read_icp_text_string();
	listener_port_name = g2int_read_icp_text_string();
	remote_process_initialization_string = g2int_read_icp_text_string();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_initialize_gsi_interface__body(interface_name,
		  class_name,keep_connection_on_g2_reset,
		  listener_network_type,listener_host_name,
		  listener_port_name,remote_process_initialization_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(listener_host_name);
	g2int_reclaim_text_string(listener_port_name);
	g2int_reclaim_text_string(remote_process_initialization_string);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_initialize_gsi_interface,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_initialize_gsi_interface,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    interface_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		interface_name = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		interface_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    class_name = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(interface_name);
		    g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		class_name = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		class_name = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    keep_connection_on_g2_reset = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(class_name);
		g2int_resumable_icp_push(interface_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		return VALUES_1(G2int_icp_suspend);
	    }
	    keep_connection_on_g2_reset = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    listener_network_type = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(keep_connection_on_g2_reset);
		    g2int_resumable_icp_push(class_name);
		    g2int_resumable_icp_push(interface_name);
		    g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		listener_network_type = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		listener_network_type = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    listener_host_name = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(listener_network_type);
		g2int_resumable_icp_push(keep_connection_on_g2_reset);
		g2int_resumable_icp_push(class_name);
		g2int_resumable_icp_push(interface_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		return VALUES_1(G2int_icp_suspend);
	    }
	    listener_host_name = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    listener_port_name = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(listener_host_name);
		g2int_resumable_icp_push(listener_network_type);
		g2int_resumable_icp_push(keep_connection_on_g2_reset);
		g2int_resumable_icp_push(class_name);
		g2int_resumable_icp_push(interface_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		return VALUES_1(G2int_icp_suspend);
	    }
	    listener_port_name = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_process_initialization_string = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(listener_port_name);
		g2int_resumable_icp_push(listener_host_name);
		g2int_resumable_icp_push(listener_network_type);
		g2int_resumable_icp_push(keep_connection_on_g2_reset);
		g2int_resumable_icp_push(class_name);
		g2int_resumable_icp_push(interface_name);
		g2int_resumable_icp_push(Qg2int_handle_icp_initialize_gsi_interface);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_process_initialization_string = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_initialize_gsi_interface__body(interface_name,
		  class_name,keep_connection_on_g2_reset,
		  listener_network_type,listener_host_name,
		  listener_port_name,remote_process_initialization_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(listener_host_name);
	g2int_reclaim_text_string(listener_port_name);
	g2int_reclaim_text_string(remote_process_initialization_string);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_return_initialize_gsi_interface_status;  /* send-icp-return-initialize-gsi-interface-status */

/* SEND-ICP-RETURN-INITIALIZE-GSI-INTERFACE-STATUS */
Object g2int_send_icp_return_initialize_gsi_interface_status(error_information)
    Object error_information;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,93);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_return_initialize_gsi_interface_status;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)339L));
	  g2int_write_icp_text_string(error_information);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_return_initialize_gsi_interface_status,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_return_initialize_gsi_interface_status,
			top,Nil);
		goto end_send_icp_return_initialize_gsi_interface_status;
	    }
	}
	error_information = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_information;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_return_initialize_gsi_interface_status;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)339L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_text_string(error_information))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(error_information);
	      g2int_resumable_icp_push(Qg2int_send_icp_return_initialize_gsi_interface_status);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_return_initialize_gsi_interface_status;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_return_initialize_gsi_interface_status:
    return result;
}

static Object Qg2int_gsi_initiate_connection;  /* gsi_initiate_connection */

/* HANDLE-ICP-RETURN-INITIALIZE-GSI-INTERFACE-STATUS--BODY */
Object g2int_handle_icp_return_initialize_gsi_interface_status__body(error_information)
    Object error_information;
{
    x_note_fn_call(43,94);
    g2int_gsi_connection_error(3,Qg2int_gsi_initiate_connection,
	    G2int_gsi_error_in_connect,error_information);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_return_initialize_gsi_interface_status;  /* handle-icp-return-initialize-gsi-interface-status */

/* HANDLE-ICP-RETURN-INITIALIZE-GSI-INTERFACE-STATUS */
Object g2int_handle_icp_return_initialize_gsi_interface_status()
{
    Object error_information, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,95);
    if (G2int_disable_resumability) {
	error_information = g2int_read_icp_text_string();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_return_initialize_gsi_interface_status__body(error_information);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_information);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_return_initialize_gsi_interface_status,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_return_initialize_gsi_interface_status,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_information = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_return_initialize_gsi_interface_status);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_information = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_return_initialize_gsi_interface_status__body(error_information);
	POP_SPECIAL();
	g2int_reclaim_text_string(error_information);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GSI-INITIALIZE-ICP-SOCKET */
Object g2int_gsi_initialize_icp_socket(icp_socket)
    Object icp_socket;
{
    Object gsi_extension_data_qm, current_icp_socket;
    Declare_special(1);

    x_note_fn_call(43,96);
    gsi_extension_data_qm = ISVREF(icp_socket,(SI_Long)29L);
    if ( !TRUEP(gsi_extension_data_qm)) {
	current_icp_socket = icp_socket;
	PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
	  gsi_extension_data_qm = g2int_make_gsi_extension_data_1();
	POP_SPECIAL();
	SVREF(icp_socket,FIX((SI_Long)29L)) = gsi_extension_data_qm;
    }
    return VALUES_1(gsi_extension_data_qm);
}

static Object Qg2int_send_icp_pause_data_server;  /* send-icp-pause-data-server */

/* SEND-ICP-PAUSE-DATA-SERVER */
Object g2int_send_icp_pause_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,97);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_pause_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)71L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_pause_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_pause_data_server,top,Nil);
		goto end_send_icp_pause_data_server;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_pause_data_server;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)71L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_pause_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_pause_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_pause_data_server:
    return result;
}

/* HANDLE-ICP-PAUSE-DATA-SERVER--BODY */
Object g2int_handle_icp_pause_data_server__body()
{
    x_note_fn_call(43,98);
    g2int_call_gsi_callback(1,G2int_gsi_pause_context);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_pause_data_server;  /* handle-icp-pause-data-server */

/* HANDLE-ICP-PAUSE-DATA-SERVER */
Object g2int_handle_icp_pause_data_server()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,99);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_pause_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_pause_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_pause_data_server,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_pause_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_resume_data_server;  /* send-icp-resume-data-server */

/* SEND-ICP-RESUME-DATA-SERVER */
Object g2int_send_icp_resume_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,100);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resume_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)72L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_resume_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_resume_data_server,top,Nil);
		goto end_send_icp_resume_data_server;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_resume_data_server;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)72L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_resume_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resume_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resume_data_server:
    return result;
}

/* HANDLE-ICP-RESUME-DATA-SERVER--BODY */
Object g2int_handle_icp_resume_data_server__body()
{
    x_note_fn_call(43,101);
    g2int_call_gsi_callback(1,G2int_gsi_resume_context);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_resume_data_server;  /* handle-icp-resume-data-server */

/* HANDLE-ICP-RESUME-DATA-SERVER */
Object g2int_handle_icp_resume_data_server()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,102);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resume_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_resume_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_resume_data_server,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_resume_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_start_data_server;  /* send-icp-start-data-server */

/* SEND-ICP-START-DATA-SERVER */
Object g2int_send_icp_start_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,103);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_start_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)363L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_start_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_start_data_server,top,Nil);
		goto end_send_icp_start_data_server;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_start_data_server;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)363L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_start_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_start_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_start_data_server:
    return result;
}

/* HANDLE-ICP-START-DATA-SERVER--BODY */
Object g2int_handle_icp_start_data_server__body()
{
    x_note_fn_call(43,104);
    g2int_call_gsi_callback(1,G2int_gsi_start_context);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_start_data_server;  /* handle-icp-start-data-server */

/* HANDLE-ICP-START-DATA-SERVER */
Object g2int_handle_icp_start_data_server()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,105);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_start_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_start_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_start_data_server,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_start_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_reset_data_server;  /* send-icp-reset-data-server */

/* SEND-ICP-RESET-DATA-SERVER */
Object g2int_send_icp_reset_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,106);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_reset_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)364L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_reset_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_reset_data_server,top,Nil);
		goto end_send_icp_reset_data_server;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_reset_data_server;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)364L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_reset_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_reset_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_reset_data_server:
    return result;
}

/* HANDLE-ICP-RESET-DATA-SERVER--BODY */
Object g2int_handle_icp_reset_data_server__body()
{
    x_note_fn_call(43,107);
    g2int_call_gsi_callback(1,G2int_gsi_reset_context);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_reset_data_server;  /* handle-icp-reset-data-server */

/* HANDLE-ICP-RESET-DATA-SERVER */
Object g2int_handle_icp_reset_data_server()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,108);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_reset_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_reset_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_reset_data_server,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_reset_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_initialize_data_server;  /* send-icp-initialize-data-server */

/* SEND-ICP-INITIALIZE-DATA-SERVER */
Object g2int_send_icp_initialize_data_server(text_string)
    Object text_string;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,109);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_initialize_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)69L));
	  g2int_write_icp_text_string(text_string);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_initialize_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_initialize_data_server,top,Nil);
		goto end_send_icp_initialize_data_server;
	    }
	}
	text_string = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : text_string;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_initialize_data_server;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)69L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,g2int_write_icp_text_string(text_string))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(text_string);
	      g2int_resumable_icp_push(Qg2int_send_icp_initialize_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_initialize_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_initialize_data_server:
    return result;
}

static Object Qg2int_initialize_data_server_message;  /* initialize-data-server-message */

/* HANDLE-ICP-INITIALIZE-DATA-SERVER--BODY */
Object g2int_handle_icp_initialize_data_server__body(text_string)
    Object text_string;
{
    Object gsi_extension_data, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(43,110);
    g2int_receive_initial_message(Qg2int_gsi,Qg2int_g2);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	gsi_extension_data = ISVREF(G2int_current_icp_socket,(SI_Long)29L);
	if ( !((SI_Long)0L <= IFIX(ISVREF(gsi_extension_data,(SI_Long)1L)))) {
	    if (IFIX(G2int_gsi_maximum_number_of_contexts) >= (SI_Long)0L 
		    && FIXNUM_GE(G2int_number_of_contexts_allocated,
		    G2int_gsi_maximum_number_of_contexts)) {
		current_icp_port = ISVREF(G2int_current_icp_socket,
			(SI_Long)4L);
		PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
		  current_icp_socket = ISVREF(G2int_current_icp_port,
			  (SI_Long)2L);
		  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
		    temp = IFIX(ISVREF(G2int_current_icp_socket,
			    (SI_Long)22L)) >= (SI_Long)17L ? 
			    ISVREF(G2int_current_icp_socket,(SI_Long)53L) :
			     Nil;
		    if (temp);
		    else
			temp = Nil;
		    disable_resumability = temp;
		    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			    9);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      8);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
				7);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
				  6);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
			    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				    5);
			      number_of_icp_bytes_to_fill_buffer = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				      4);
				current_icp_buffer = Nil;
				PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
					3);
				  current_write_icp_byte_position = Nil;
				  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
					  2);
				    number_of_icp_bytes_in_message_group = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					    1);
				      writing_icp_message_group = 
					      FIXNUM_ADD1(G2int_writing_icp_message_group);
				      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					      0);
					gensymed_symbol = Nil;
					gensymed_symbol_1 = 0.0;
					gensymed_symbol_1 = 0.0;
					if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
						&&  
						!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						    {
					    if (IFIX(ISVREF(G2int_current_icp_socket,
						    (SI_Long)22L)) >= 
						    (SI_Long)5L)
						g2int_send_icp_acknowledge_shutdown();
					    else
						g2int_send_icp_shut_down_data_server();
					    g2int_end_icp_message_group();
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
		g2int_flush_icp_output_ports();
		g2int_gsi_connection_error(3,
			Qg2int_initialize_data_server_message,
			G2int_gsi_maximum_contexts_exceeded,
			G2int_gsi_maximum_number_of_contexts);
	    }
	    temp_1 = g2int_allocate_gsi_context_number();
	    SVREF(gsi_extension_data,FIX((SI_Long)1L)) = temp_1;
	}
	temp_1 = G2int_current_icp_socket;
	SVREF(temp_1,FIX((SI_Long)25L)) = Qg2int_g2;
	temp_1 = 
		g2int_convert_value_to_gsi_value(g2int_copy_text_string(text_string));
	SVREF(gsi_extension_data,FIX((SI_Long)6L)) = temp_1;
	g2int_send_version_info();
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_initialize_data_server;  /* handle-icp-initialize-data-server */

/* HANDLE-ICP-INITIALIZE-DATA-SERVER */
Object g2int_handle_icp_initialize_data_server()
{
    Object text_string, abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,111);
    if (G2int_disable_resumability) {
	text_string = g2int_read_icp_text_string();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_initialize_data_server__body(text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_initialize_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_initialize_data_server,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    text_string = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_initialize_data_server);
		return VALUES_1(G2int_icp_suspend);
	    }
	    text_string = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_initialize_data_server__body(text_string);
	POP_SPECIAL();
	g2int_reclaim_text_string(text_string);
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object string_constant_2;   /* "Connection request received - context ~A~A~%" */

static Object Ksecure_p;           /* :secure-p */

/* CALL-INITIALIZE-CONTEXT-CALLBACK */
Object g2int_call_initialize_context_callback()
{
    Object gsi_extension_data, temp, svref_new_value, string_1;

    x_note_fn_call(43,112);
    gsi_extension_data = ISVREF(G2int_current_icp_socket,(SI_Long)29L);
    temp = g2int_gsi_current_context_number();
    g2int_gsi_message(3,string_constant_2,temp,g2int_secure_icp_string(2,
	    Ksecure_p,
	    g2int_icp_connection_is_secure(G2int_current_icp_socket)));
    SVREF(gsi_extension_data,FIX((SI_Long)8L)) = T;
    svref_new_value = 
	    g2int_find_or_load_gsi_application(ISVREF(G2int_current_icp_socket,
	    (SI_Long)52L));
    SVREF(gsi_extension_data,FIX((SI_Long)9L)) = svref_new_value;
    if ( !TRUEP(ISVREF(gsi_extension_data,(SI_Long)9L)))
	return VALUES_1(T);
    temp = ISVREF(gsi_extension_data,(SI_Long)6L);
    SVREF(gsi_extension_data,FIX((SI_Long)6L)) = Nil;
    string_1 = temp;
    temp = g2int_gsi_failure_p(g2int_call_gsi_callback(3,
	    G2int_gsi_initialize_context,string_1,g2int_lengthw(string_1)));
    g2int_reclaim_text_or_gensym_string(string_1);
    return VALUES_1(temp);
}

static Object string_constant_3;   /* "Connection ~A - context ~A~A~%" */

static Object string_constant_4;   /* "rejected" */

static Object string_constant_5;   /* "accepted" */

/* CALL-INITIALIZE-CONTEXT-AND-MAYBE-REJECT-CONNECTION */
Object g2int_call_initialize_context_and_maybe_reject_connection()
{
    Object failurep, temp;

    x_note_fn_call(43,113);
    failurep = g2int_call_initialize_context_callback();
    temp = g2int_gsi_current_context_number();
    g2int_gsi_message(4,string_constant_3,failurep ? string_constant_4 : 
	    string_constant_5,temp,g2int_secure_icp_string(2,Ksecure_p,
	    g2int_icp_connection_is_secure(G2int_current_icp_socket)));
    if (failurep) {
	g2int_flush_and_shutdown_icp_socket(G2int_current_icp_socket);
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* SEND-VERSION-INFO */
Object g2int_send_version_info()
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(43,114);
    current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
      current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		(SI_Long)53L) : Nil;
	if (temp);
	else
	    temp = Nil;
	disable_resumability = temp;
	PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,9);
	  number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		  8);
	    icp_buffers_for_message_group = Nil;
	    PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
		    7);
	      icp_buffer_of_start_of_message_series_qm = Nil;
	      PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
		      6);
		icp_byte_position_of_start_of_message_series_qm = Nil;
		PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			5);
		  number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		  PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			  4);
		    current_icp_buffer = Nil;
		    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
			    3);
		      current_write_icp_byte_position = Nil;
		      PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
			      2);
			number_of_icp_bytes_in_message_group = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				1);
			  writing_icp_message_group = 
				  FIXNUM_ADD1(G2int_writing_icp_message_group);
			  PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				  0);
			    gensymed_symbol = Nil;
			    gensymed_symbol_1 = 0.0;
			    gensymed_symbol_1 = 0.0;
			    if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
				    &&  
				    !TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					{
				temp = 
					g2int_get_system_major_version(G2int_current_system_name);
				temp = 
					g2int_send_icp_return_peer_version(temp,
					g2int_get_system_minor_version(G2int_current_system_name));
				g2int_end_icp_message_group();
			    }
			    else
				temp = Nil;
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
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_return_peer_version;  /* send-icp-return-peer-version */

/* SEND-ICP-RETURN-PEER-VERSION */
Object g2int_send_icp_return_peer_version(major_version_number,
	    minor_version_number)
    Object major_version_number, minor_version_number;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,115);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_return_peer_version;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)66L));
	  g2int_write_icp_unsigned_integer(major_version_number);
	  g2int_write_icp_unsigned_integer(minor_version_number);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_return_peer_version,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_return_peer_version,top,Nil);
		goto end_send_icp_return_peer_version;
	    }
	}
	major_version_number = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : major_version_number;
	minor_version_number = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : minor_version_number;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_return_peer_version;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)66L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(major_version_number))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(minor_version_number))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(minor_version_number);
	      g2int_resumable_icp_push(major_version_number);
	      g2int_resumable_icp_push(Qg2int_send_icp_return_peer_version);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_return_peer_version;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_return_peer_version:
    return result;
}

/* HANDLE-ICP-RETURN-PEER-VERSION--BODY */
Object g2int_handle_icp_return_peer_version__body(major_version_number,
	    minor_version_number)
    Object major_version_number, minor_version_number;
{
    Object svref_arg_1;

    x_note_fn_call(43,116);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	if (IFIX(major_version_number) >= (SI_Long)4L) {
	    svref_arg_1 = G2int_current_icp_socket;
	    SVREF(svref_arg_1,FIX((SI_Long)20L)) = T;
	}
	g2int_maybe_update_remote_icp_version_info_for_version(G2int_current_icp_socket,
		major_version_number,minor_version_number);
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= (SI_Long)8L)
	    g2int_gsi_reply_to_initial_ping();
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_return_peer_version;  /* handle-icp-return-peer-version */

/* HANDLE-ICP-RETURN-PEER-VERSION */
Object g2int_handle_icp_return_peer_version()
{
    Object major_version_number, minor_version_number;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,117);
    if (G2int_disable_resumability) {
	major_version_number = g2int_read_icp_unsigned_integer();
	minor_version_number = g2int_read_icp_unsigned_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_return_peer_version__body(major_version_number,
		  minor_version_number);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_return_peer_version,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_return_peer_version,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    major_version_number = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_return_peer_version);
		return VALUES_1(G2int_icp_suspend);
	    }
	    major_version_number = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    minor_version_number = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(major_version_number);
		g2int_resumable_icp_push(Qg2int_handle_icp_return_peer_version);
		return VALUES_1(G2int_icp_suspend);
	    }
	    minor_version_number = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_return_peer_version__body(major_version_number,
		  minor_version_number);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* ROUND-POST4.0-MANAGED-FLOAT */
Object g2int_round_post4dot0_managed_float(variable_collection_interval_qm)
    Object variable_collection_interval_qm;
{
    Object temp;
    double float_interval, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,118);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(variable_collection_interval_qm) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_collection_interval_qm)) 
	    == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    float_interval = 
		    DFLOAT_ISAREF_1(variable_collection_interval_qm,
		    (SI_Long)0L);
	    arg = float_interval;
	    arg_1 = 0.0;
	    if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		temp = FIX((SI_Long)0L);
	    else {
		arg = float_interval;
		arg_1 = 1.0;
		if (arg <= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1))
		    temp = FIX((SI_Long)1L);
		else
		    temp = LONG_TO_FIXNUM(inline_floor_1(float_interval));
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp = variable_collection_interval_qm;
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_gsi_ds_update_interval;  /* write-icp-gsi-ds-update-interval */

/* WRITE-ICP-GSI-DS-UPDATE-INTERVAL */
Object g2int_write_icp_gsi_ds_update_interval(gsi_ds_update_interval)
    Object gsi_ds_update_interval;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object svref_new_value, amf_result, incff_1_arg, new_float, float_to_write;
    Object resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_2;
    double aref_new_value;

    x_note_fn_call(43,119);
    if (G2int_disable_resumability) {
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)5L) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(gsi_ds_update_interval) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_ds_update_interval)) 
		    == (SI_Long)1L)
		temp = 
			g2int_write_icp_managed_double_float(gsi_ds_update_interval);
	    else if (FIXNUMP(gsi_ds_update_interval)) {
		amf_available_array_cons_qm = 
			ISVREF(G2int_vector_of_simple_float_array_pools,
			(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = G2int_vector_of_simple_float_array_pools;
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qg2int_gensym);
		    temp_1 = G2int_available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp_1;
		    G2int_available_gensym_conses = 
			    amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp_1 = 
			    FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
		    G2int_created_simple_float_array_pool_arrays = temp_1;
		    incff_1_arg = 
			    g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp_1 = 
			    FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    G2int_simple_float_array_pool_memory_usage = temp_1;
		    amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		aref_new_value = (double)IFIX(gsi_ds_update_interval);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		float_to_write = new_float;
		g2int_write_icp_managed_double_float(float_to_write);
		g2int_reclaim_managed_simple_float_array_of_length_1(float_to_write);
		temp = Nil;
	    }
	    else
		temp = Qnil;
	}
	else
	    temp = 
		    g2int_write_icp_fixnum(g2int_round_post4dot0_managed_float(gsi_ds_update_interval));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_gsi_ds_update_interval,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_gsi_ds_update_interval,top,Nil);
	}
	gsi_ds_update_interval = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_ds_update_interval;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_2 = TRUEP(test);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? EQ(test,Qg2int_true) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)5L) {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp_2 = TRUEP(test);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ? EQ(test,Qg2int_true) : 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(gsi_ds_update_interval) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gsi_ds_update_interval)) 
		    == (SI_Long)1L) {
		value = 
			g2int_write_icp_managed_double_float(gsi_ds_update_interval);
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(gsi_ds_update_interval);
		    g2int_resumable_icp_push(Qg2int_write_icp_gsi_ds_update_interval);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value;
	    }
	    else if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || FIXNUMP(gsi_ds_update_interval)) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    float_to_write = g2int_resumable_icp_pop();
		else {
		    amf_available_array_cons_qm = 
			    ISVREF(G2int_vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_1 = G2int_vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qg2int_gensym);
			temp_1 = G2int_available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp_1;
			G2int_available_gensym_conses = 
				amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp_1 = 
				FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
			G2int_created_simple_float_array_pool_arrays = temp_1;
			incff_1_arg = 
				g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp_1 = 
				FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
				incff_1_arg);
			G2int_simple_float_array_pool_memory_usage = temp_1;
			amf_result = 
				g2int_generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = (double)IFIX(gsi_ds_update_interval);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    float_to_write = new_float;
		}
		if (EQ(icp_suspend_1,
			g2int_write_icp_managed_double_float(float_to_write))) 
			    {
		    g2int_resumable_icp_push(float_to_write);
		    g2int_resumable_icp_push(Qg2int_false);
		    g2int_resumable_icp_push(Qg2int_true);
		    g2int_resumable_icp_push(gsi_ds_update_interval);
		    g2int_resumable_icp_push(Qg2int_write_icp_gsi_ds_update_interval);
		    return VALUES_1(G2int_icp_suspend);
		}
		g2int_reclaim_managed_simple_float_array_of_length_1(float_to_write);
		temp = Nil;
	    }
	    else
		temp = Qnil;
	}
	else {
	    value = 
		    g2int_write_icp_fixnum(g2int_round_post4dot0_managed_float(gsi_ds_update_interval));
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(gsi_ds_update_interval);
		g2int_resumable_icp_push(Qg2int_write_icp_gsi_ds_update_interval);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_gsi_ds_update_interval;  /* read-icp-gsi-ds-update-interval */

/* READ-ICP-GSI-DS-UPDATE-INTERVAL */
Object g2int_read_icp_gsi_ds_update_interval()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, test, value;
    char temp_1;

    x_note_fn_call(43,120);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L ? g2int_read_icp_managed_double_float() : 
		g2int_read_icp_fixnum();
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gsi_ds_update_interval,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gsi_ds_update_interval,top,Nil);
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)5L) {
	    value = g2int_read_icp_managed_double_float();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_true);
		g2int_resumable_icp_push(Qg2int_read_icp_gsi_ds_update_interval);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else {
	    value = g2int_read_icp_fixnum();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(Qg2int_read_icp_gsi_ds_update_interval);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_define_gsi_sensor;  /* send-icp-define-gsi-sensor */

/* SEND-ICP-DEFINE-GSI-SENSOR */
Object g2int_send_icp_define_gsi_sensor(corresponding_icp_object_index,
	    parameter1,parameter2,parameter3,parameter4,parameter5,parameter6)
    Object corresponding_icp_object_index, parameter1, parameter2, parameter3;
    Object parameter4, parameter5, parameter6;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,121);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_define_gsi_sensor;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)75L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_gsi_permanent_remote_value(parameter1);
	  g2int_write_icp_gsi_permanent_remote_value(parameter2);
	  g2int_write_icp_gsi_permanent_remote_value(parameter3);
	  g2int_write_icp_gsi_permanent_remote_value(parameter4);
	  g2int_write_icp_gsi_permanent_remote_value(parameter5);
	  g2int_write_icp_gsi_permanent_remote_value(parameter6);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_define_gsi_sensor,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_define_gsi_sensor,top,Nil);
		goto end_send_icp_define_gsi_sensor;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	parameter1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter1;
	parameter2 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter2;
	parameter3 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter3;
	parameter4 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter4;
	parameter5 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter5;
	parameter6 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter6;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_define_gsi_sensor;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)75L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    case 5:
		      goto l5;
		      break;
		    case 6:
		      goto l6;
		      break;
		    case 7:
		      goto l7;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter2))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter3))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter4))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter5))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter6))) {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(parameter6);
	      g2int_resumable_icp_push(parameter5);
	      g2int_resumable_icp_push(parameter4);
	      g2int_resumable_icp_push(parameter3);
	      g2int_resumable_icp_push(parameter2);
	      g2int_resumable_icp_push(parameter1);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_define_gsi_sensor);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_gsi_sensor;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_gsi_sensor:
    return result;
}

/* HANDLE-ICP-DEFINE-GSI-SENSOR--BODY */
Object g2int_handle_icp_define_gsi_sensor__body(corresponding_icp_object_index,
	    parameter1,parameter2,parameter3,parameter4,parameter5,parameter6)
    Object corresponding_icp_object_index, parameter1, parameter2, parameter3;
    Object parameter4, parameter5, parameter6;
{
    x_note_fn_call(43,122);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running))
	g2int_gsi_register_new_sensor(7,corresponding_icp_object_index,
		parameter1,parameter2,parameter3,parameter4,parameter5,
		parameter6);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_gsi_sensor;  /* handle-icp-define-gsi-sensor */

/* HANDLE-ICP-DEFINE-GSI-SENSOR */
Object g2int_handle_icp_define_gsi_sensor()
{
    Object corresponding_icp_object_index, parameter1, parameter2, parameter3;
    Object parameter4, parameter5, parameter6, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,123);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	parameter1 = g2int_read_icp_gsi_permanent_remote_value();
	parameter2 = g2int_read_icp_gsi_permanent_remote_value();
	parameter3 = g2int_read_icp_gsi_permanent_remote_value();
	parameter4 = g2int_read_icp_gsi_permanent_remote_value();
	parameter5 = g2int_read_icp_gsi_permanent_remote_value();
	parameter6 = g2int_read_icp_gsi_permanent_remote_value();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_gsi_sensor__body(corresponding_icp_object_index,
		  parameter1,parameter2,parameter3,parameter4,parameter5,
		  parameter6);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_define_gsi_sensor,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_define_gsi_sensor,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter1 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter1 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter2 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter1);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter2 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter3 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter2);
		g2int_resumable_icp_push(parameter1);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter3 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter4 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter3);
		g2int_resumable_icp_push(parameter2);
		g2int_resumable_icp_push(parameter1);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter4 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter5 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter4);
		g2int_resumable_icp_push(parameter3);
		g2int_resumable_icp_push(parameter2);
		g2int_resumable_icp_push(parameter1);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter5 = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter6 = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter5);
		g2int_resumable_icp_push(parameter4);
		g2int_resumable_icp_push(parameter3);
		g2int_resumable_icp_push(parameter2);
		g2int_resumable_icp_push(parameter1);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter6 = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_gsi_sensor__body(corresponding_icp_object_index,
		  parameter1,parameter2,parameter3,parameter4,parameter5,
		  parameter6);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_register_corresponding_icp_object;  /* send-icp-register-corresponding-icp-object */

/* SEND-ICP-REGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_send_icp_register_corresponding_icp_object(corresponding_icp_object_index,
	    name_of_item_qm,class_of_item,parameter1_qm,parameter2_qm,
	    parameter3_qm,parameter4_qm,parameter5_qm,parameter6_qm)
    Object corresponding_icp_object_index, name_of_item_qm, class_of_item;
    Object parameter1_qm, parameter2_qm, parameter3_qm, parameter4_qm;
    Object parameter5_qm, parameter6_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,124);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_register_corresponding_icp_object;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_item_qm),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(name_of_item_qm);
	  name_of_item_qm = temp_1;
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_of_item),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = g2int_make_corresponding_icp_symbol(class_of_item);
	  class_of_item = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)322L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_corresponding_object_index(name_of_item_qm);
	  g2int_write_icp_corresponding_object_index(class_of_item);
	  g2int_write_icp_gsi_permanent_remote_value(parameter1_qm);
	  g2int_write_icp_gsi_permanent_remote_value(parameter2_qm);
	  g2int_write_icp_gsi_permanent_remote_value(parameter3_qm);
	  g2int_write_icp_gsi_permanent_remote_value(parameter4_qm);
	  g2int_write_icp_gsi_permanent_remote_value(parameter5_qm);
	  g2int_write_icp_gsi_permanent_remote_value(parameter6_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_register_corresponding_icp_object,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_register_corresponding_icp_object,
			top,Nil);
		goto end_send_icp_register_corresponding_icp_object;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	name_of_item_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : name_of_item_qm;
	class_of_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : class_of_item;
	parameter1_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter1_qm;
	parameter2_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter2_qm;
	parameter3_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter3_qm;
	parameter4_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter4_qm;
	parameter5_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter5_qm;
	parameter6_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : parameter6_qm;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_register_corresponding_icp_object;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
		    case 4:
		      goto l4;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name_of_item_qm),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      name_of_item_qm = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(name_of_item_qm);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      name_of_item_qm = value_1;
	  }
	l2:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(class_of_item),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      class_of_item = value;
	  else {
	      value_1 = g2int_make_corresponding_icp_symbol(class_of_item);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      class_of_item = value_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)322L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l4:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		      goto l4_1;
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(name_of_item_qm))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(class_of_item))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter1_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter2_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter3_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter4_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l8:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter5_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)8L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l9:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(parameter6_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)9L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(parameter6_qm);
	      g2int_resumable_icp_push(parameter5_qm);
	      g2int_resumable_icp_push(parameter4_qm);
	      g2int_resumable_icp_push(parameter3_qm);
	      g2int_resumable_icp_push(parameter2_qm);
	      g2int_resumable_icp_push(parameter1_qm);
	      g2int_resumable_icp_push(class_of_item);
	      g2int_resumable_icp_push(name_of_item_qm);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_register_corresponding_icp_object);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_register_corresponding_icp_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_register_corresponding_icp_object:
    return result;
}

/* HANDLE-ICP-REGISTER-CORRESPONDING-ICP-OBJECT--BODY */
Object g2int_handle_icp_register_corresponding_icp_object__body(corresponding_icp_object_index,
	    name_of_item_qm,class_of_item,parameter1_qm,parameter2_qm,
	    parameter3_qm,parameter4_qm,parameter5_qm,parameter6_qm)
    Object corresponding_icp_object_index, name_of_item_qm, class_of_item;
    Object parameter1_qm, parameter2_qm, parameter3_qm, parameter4_qm;
    Object parameter5_qm, parameter6_qm;
{
    x_note_fn_call(43,125);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running))
	g2int_call_gsi_callback(2,G2int_gsi_receive_registration,
		g2int_gsi_register_new_sensor(9,
		corresponding_icp_object_index,parameter1_qm,parameter2_qm,
		parameter3_qm,parameter4_qm,parameter5_qm,parameter6_qm,
		name_of_item_qm,class_of_item));
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_register_corresponding_icp_object;  /* handle-icp-register-corresponding-icp-object */

/* HANDLE-ICP-REGISTER-CORRESPONDING-ICP-OBJECT */
Object g2int_handle_icp_register_corresponding_icp_object()
{
    Object corresponding_icp_object_index, index_1, index_space;
    Object name_of_item_qm, class_of_item, parameter1_qm, parameter2_qm;
    Object parameter3_qm, parameter4_qm, parameter5_qm, parameter6_qm;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,126);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    name_of_item_qm = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    name_of_item_qm = Nil;
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    class_of_item = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    class_of_item = Nil;
	parameter1_qm = g2int_read_icp_gsi_permanent_remote_value();
	parameter2_qm = g2int_read_icp_gsi_permanent_remote_value();
	parameter3_qm = g2int_read_icp_gsi_permanent_remote_value();
	parameter4_qm = g2int_read_icp_gsi_permanent_remote_value();
	parameter5_qm = g2int_read_icp_gsi_permanent_remote_value();
	parameter6_qm = g2int_read_icp_gsi_permanent_remote_value();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_register_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_item_qm,class_of_item,parameter1_qm,
		  parameter2_qm,parameter3_qm,parameter4_qm,parameter5_qm,
		  parameter6_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_register_corresponding_icp_object,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_register_corresponding_icp_object,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_item_qm = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		name_of_item_qm = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		name_of_item_qm = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    class_of_item = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(name_of_item_qm);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		class_of_item = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		class_of_item = Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter1_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter1_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter2_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter1_qm);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter2_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter3_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter2_qm);
		g2int_resumable_icp_push(parameter1_qm);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter3_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter4_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter3_qm);
		g2int_resumable_icp_push(parameter2_qm);
		g2int_resumable_icp_push(parameter1_qm);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter4_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter5_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter4_qm);
		g2int_resumable_icp_push(parameter3_qm);
		g2int_resumable_icp_push(parameter2_qm);
		g2int_resumable_icp_push(parameter1_qm);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter5_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    parameter6_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(parameter5_qm);
		g2int_resumable_icp_push(parameter4_qm);
		g2int_resumable_icp_push(parameter3_qm);
		g2int_resumable_icp_push(parameter2_qm);
		g2int_resumable_icp_push(parameter1_qm);
		g2int_resumable_icp_push(class_of_item);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_register_corresponding_icp_object);
		return VALUES_1(G2int_icp_suspend);
	    }
	    parameter6_qm = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_register_corresponding_icp_object__body(corresponding_icp_object_index,
		  name_of_item_qm,class_of_item,parameter1_qm,
		  parameter2_qm,parameter3_qm,parameter4_qm,parameter5_qm,
		  parameter6_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GSI-ADD-NEW-SENSOR-ATTRIBUTE */
Object g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,index_1,
	    parameter)
    Object new_sensor, attributes, index_1, parameter;
{
    Object svref_arg_1;

    x_note_fn_call(43,127);
    g2int_set_gsi_instance_owner(parameter,Qg2int_context);
    svref_arg_1 = ISVREF(attributes,IFIX(FIXNUM_ADD1(index_1)));
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = parameter;
    g2int_gsi_push_onto_appropriate_list(2,parameter,new_sensor);
    return VALUES_1(Nil);
}

static Object Qg2int_gsi_reference_flag;  /* gsi-reference-flag */

/* GSI-REGISTER-NEW-SENSOR */
Object g2int_gsi_register_new_sensor varargs_1(int, n)
{
    Object index_1, parameter1, parameter2, parameter3, parameter4, parameter5;
    Object parameter6;
    Object name_of_item_qm, class_of_item_qm, gsi_reclaim_list_qm;
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, new_sensor, attributes;
    Object gsi_instance_extension;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,128);
    INIT_ARGS_nonrelocating();
    index_1 = REQUIRED_ARG_nonrelocating();
    parameter1 = REQUIRED_ARG_nonrelocating();
    parameter2 = REQUIRED_ARG_nonrelocating();
    parameter3 = REQUIRED_ARG_nonrelocating();
    parameter4 = REQUIRED_ARG_nonrelocating();
    parameter5 = REQUIRED_ARG_nonrelocating();
    parameter6 = REQUIRED_ARG_nonrelocating();
    name_of_item_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    class_of_item_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    g2int_handle_delete_corresponding_icp_object(index_1,
	    Qg2int_item_index_space,G2int_current_icp_port);
    gsi_reclaim_list_qm = Nil;
    PUSH_SPECIAL(G2int_gsi_reclaim_listqm,gsi_reclaim_list_qm,0);
      amf_available_array_cons_qm = 
	      ISVREF(G2int_vector_of_simple_float_array_pools,(SI_Long)1L);
      if (amf_available_array_cons_qm) {
	  amf_array = M_CAR(amf_available_array_cons_qm);
	  temp = G2int_vector_of_simple_float_array_pools;
	  svref_new_value = M_CDR(amf_available_array_cons_qm);
	  SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	  inline_note_reclaim_cons(amf_available_array_cons_qm,Qg2int_gensym);
	  temp = G2int_available_gensym_conses;
	  M_CDR(amf_available_array_cons_qm) = temp;
	  G2int_available_gensym_conses = amf_available_array_cons_qm;
	  amf_result = amf_array;
      }
      else {
	  temp = FIXNUM_ADD1(G2int_created_simple_float_array_pool_arrays);
	  G2int_created_simple_float_array_pool_arrays = temp;
	  incff_1_arg = 
		  g2int_bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	  temp = FIXNUM_ADD(G2int_simple_float_array_pool_memory_usage,
		  incff_1_arg);
	  G2int_simple_float_array_pool_memory_usage = temp;
	  amf_result = g2int_generate_float_vector(FIX((SI_Long)1L));
      }
      new_float = amf_result;
      DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
      new_sensor = g2int_make_gsi_instance(7,Nil,Nil,Nil,Nil,Nil,
	      Qg2int_user,new_float);
      attributes = 
	      g2int_gsi_make_attributes_for_user_or_gsi(FIX((SI_Long)6L),
	      Qg2int_context);
      g2int_set_gsi_instance_owner(new_sensor,Qg2int_context);
      gsi_instance_extension = ISVREF(new_sensor,(SI_Long)3L);
      if ( !TRUEP(gsi_instance_extension)) {
	  gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	  SVREF(new_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
      }
      temp = G2int_gsi_reclaim_listqm;
      SVREF(gsi_instance_extension,FIX((SI_Long)14L)) = temp;
      gsi_instance_extension = ISVREF(new_sensor,(SI_Long)3L);
      if ( !TRUEP(gsi_instance_extension)) {
	  gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	  SVREF(new_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
      }
      SVREF(gsi_instance_extension,FIX((SI_Long)8L)) = attributes;
      gsi_instance_extension = ISVREF(new_sensor,(SI_Long)3L);
      if ( !TRUEP(gsi_instance_extension)) {
	  gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	  SVREF(new_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
      }
      ISVREF(gsi_instance_extension,(SI_Long)9L) = FIX((SI_Long)6L);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)0L),parameter1);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)1L),parameter2);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)2L),parameter3);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)3L),parameter4);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)4L),parameter5);
      g2int_gsi_add_new_sensor_attribute(new_sensor,attributes,
	      FIX((SI_Long)5L),parameter6);
      if (name_of_item_qm) {
	  gsi_instance_extension = ISVREF(new_sensor,(SI_Long)3L);
	  if ( !TRUEP(gsi_instance_extension)) {
	      gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	      SVREF(new_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	  }
	  SVREF(gsi_instance_extension,FIX((SI_Long)4L)) = name_of_item_qm;
      }
      if (class_of_item_qm) {
	  gsi_instance_extension = ISVREF(new_sensor,(SI_Long)3L);
	  if ( !TRUEP(gsi_instance_extension)) {
	      gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	      SVREF(new_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	  }
	  SVREF(gsi_instance_extension,FIX((SI_Long)2L)) = class_of_item_qm;
      }
      g2int_set_icp_object_index_for_gsi_instance(new_sensor,index_1,
	      G2int_current_icp_port);
      g2int_store_corresponding_item(index_1,new_sensor);
      g2int_set_gsi_instance_plist_value(new_sensor,
	      Qg2int_gsi_reference_flag,T);
      result = VALUES_1(new_sensor);
    POP_SPECIAL();
    return result;
}

static Object Qg2int_send_icp_modify_gsi_sensor_definition;  /* send-icp-modify-gsi-sensor-definition */

/* SEND-ICP-MODIFY-GSI-SENSOR-DEFINITION */
Object g2int_send_icp_modify_gsi_sensor_definition(corresponding_icp_object_index,
	    update_interval,value_type,name_of_item_qm,name_of_class)
    Object corresponding_icp_object_index, update_interval, value_type;
    Object name_of_item_qm, name_of_class;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,129);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_modify_gsi_sensor_definition;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)59L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_gsi_ds_update_interval(update_interval);
	  g2int_write_icp_unsigned_integer(value_type);
	  g2int_write_icp_remote_value(name_of_item_qm);
	  g2int_write_icp_remote_value(name_of_class);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_modify_gsi_sensor_definition,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_modify_gsi_sensor_definition,top,Nil);
		goto end_send_icp_modify_gsi_sensor_definition;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	update_interval = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : update_interval;
	value_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_type;
	name_of_item_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : name_of_item_qm;
	name_of_class = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : name_of_class;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_modify_gsi_sensor_definition;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)59L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    case 5:
		      goto l5;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_ds_update_interval(update_interval))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(value_type))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		      g2int_write_icp_remote_value(name_of_item_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,g2int_write_icp_remote_value(name_of_class))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(name_of_class);
	      g2int_resumable_icp_push(name_of_item_qm);
	      g2int_resumable_icp_push(value_type);
	      g2int_resumable_icp_push(update_interval);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_modify_gsi_sensor_definition);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_modify_gsi_sensor_definition;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_modify_gsi_sensor_definition:
    return result;
}

/* HANDLE-ICP-MODIFY-GSI-SENSOR-DEFINITION--BODY */
Object g2int_handle_icp_modify_gsi_sensor_definition__body(corresponding_icp_object_index,
	    update_interval,value_type,name_of_item_qm,name_of_class)
    Object corresponding_icp_object_index, update_interval, value_type;
    Object name_of_item_qm, name_of_class;
{
    Object gsi_sensor, svref_new_value, gsi_instance_extension, old_contents;

    x_note_fn_call(43,130);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	gsi_sensor = g2int_get_from_icp_port(G2int_current_icp_port,
		corresponding_icp_object_index,Qg2int_item_index_space);
	svref_new_value = ISVREF(name_of_item_qm,(SI_Long)2L);
	gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	SVREF(gsi_instance_extension,FIX((SI_Long)4L)) = svref_new_value;
	svref_new_value = ISVREF(name_of_class,(SI_Long)2L);
	gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	SVREF(gsi_instance_extension,FIX((SI_Long)2L)) = svref_new_value;
	if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	    g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	    G2int_gsi_reclaim_listqm = Nil;
	}
	gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
	old_contents = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)11L) : Nil;
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_contents) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_contents)) == (SI_Long)1L)
	    g2int_reclaim_managed_simple_float_array_of_length_1(old_contents);
	gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	SVREF(gsi_instance_extension,FIX((SI_Long)11L)) = update_interval;
	gsi_instance_extension = ISVREF(gsi_sensor,(SI_Long)3L);
	if ( !TRUEP(gsi_instance_extension)) {
	    gsi_instance_extension = g2int_make_gsi_instance_extension_1();
	    SVREF(gsi_sensor,FIX((SI_Long)3L)) = gsi_instance_extension;
	}
	SVREF(gsi_instance_extension,FIX((SI_Long)3L)) = value_type;
	g2int_call_gsi_callback(2,G2int_gsi_receive_registration,gsi_sensor);
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_modify_gsi_sensor_definition;  /* handle-icp-modify-gsi-sensor-definition */

/* HANDLE-ICP-MODIFY-GSI-SENSOR-DEFINITION */
Object g2int_handle_icp_modify_gsi_sensor_definition()
{
    Object corresponding_icp_object_index, update_interval, value_type;
    Object name_of_item_qm, name_of_class, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,131);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	update_interval = g2int_read_icp_gsi_ds_update_interval();
	value_type = g2int_read_icp_unsigned_integer();
	name_of_item_qm = g2int_read_icp_remote_value();
	name_of_class = g2int_read_icp_remote_value();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_modify_gsi_sensor_definition__body(corresponding_icp_object_index,
		  update_interval,value_type,name_of_item_qm,name_of_class);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_modify_gsi_sensor_definition,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_modify_gsi_sensor_definition,top,
			Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_modify_gsi_sensor_definition);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    update_interval = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_ds_update_interval();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_modify_gsi_sensor_definition);
		return VALUES_1(G2int_icp_suspend);
	    }
	    update_interval = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value_type = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(update_interval);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_modify_gsi_sensor_definition);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value_type = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_item_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(value_type);
		g2int_resumable_icp_push(update_interval);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_modify_gsi_sensor_definition);
		return VALUES_1(G2int_icp_suspend);
	    }
	    name_of_item_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    name_of_class = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(name_of_item_qm);
		g2int_resumable_icp_push(value_type);
		g2int_resumable_icp_push(update_interval);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_modify_gsi_sensor_definition);
		return VALUES_1(G2int_icp_suspend);
	    }
	    name_of_class = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_modify_gsi_sensor_definition__body(corresponding_icp_object_index,
		  update_interval,value_type,name_of_item_qm,name_of_class);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_begin_sensor_list;  /* send-icp-begin-sensor-list */

/* SEND-ICP-BEGIN-SENSOR-LIST */
Object g2int_send_icp_begin_sensor_list()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,132);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_begin_sensor_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)60L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_begin_sensor_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_begin_sensor_list,top,Nil);
		goto end_send_icp_begin_sensor_list;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_begin_sensor_list;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)60L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_begin_sensor_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_begin_sensor_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_begin_sensor_list:
    return result;
}

/* HANDLE-ICP-BEGIN-SENSOR-LIST--BODY */
Object g2int_handle_icp_begin_sensor_list__body()
{
    x_note_fn_call(43,133);
    G2int_index_to_array_of_transfer_wrappers = G2int_gsi_magic_offset;
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_begin_sensor_list;  /* handle-icp-begin-sensor-list */

/* HANDLE-ICP-BEGIN-SENSOR-LIST */
Object g2int_handle_icp_begin_sensor_list()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,134);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_begin_sensor_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_begin_sensor_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_begin_sensor_list,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_begin_sensor_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_load_sensor_list_element;  /* send-icp-load-sensor-list-element */

/* SEND-ICP-LOAD-SENSOR-LIST-ELEMENT */
Object g2int_send_icp_load_sensor_list_element(corresponding_icp_object_index,
	    collection_interval_qm,value_to_set_qm)
    Object corresponding_icp_object_index, collection_interval_qm;
    Object value_to_set_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,135);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_load_sensor_list_element;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)61L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_gsi_ds_update_interval(collection_interval_qm);
	  g2int_write_icp_gsi_permanent_remote_value(value_to_set_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_load_sensor_list_element,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_load_sensor_list_element,top,Nil);
		goto end_send_icp_load_sensor_list_element;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	collection_interval_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : collection_interval_qm;
	value_to_set_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_to_set_qm;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_load_sensor_list_element;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)61L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_ds_update_interval(collection_interval_qm))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_permanent_remote_value(value_to_set_qm))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(value_to_set_qm);
	      g2int_resumable_icp_push(collection_interval_qm);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_load_sensor_list_element);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_load_sensor_list_element;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_load_sensor_list_element:
    return result;
}

/* HANDLE-ICP-LOAD-SENSOR-LIST-ELEMENT--BODY */
Object g2int_handle_icp_load_sensor_list_element__body(corresponding_icp_object_index,
	    collection_interval_qm,value_to_set_qm)
    Object corresponding_icp_object_index, collection_interval_qm;
    Object value_to_set_qm;
{
    Object sensor, transfer_wrapper, old_value;
    Object index_to_array_of_transfer_wrappers_new_value;

    x_note_fn_call(43,136);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	sensor = g2int_get_from_icp_port(G2int_current_icp_port,
		corresponding_icp_object_index,Qg2int_item_index_space);
	transfer_wrapper = ISVREF(ISVREF(ISVREF(G2int_current_icp_socket,
		(SI_Long)29L),(SI_Long)3L),
		IFIX(G2int_index_to_array_of_transfer_wrappers));
	SVREF(transfer_wrapper,FIX((SI_Long)1L)) = sensor;
	g2int_reclaim_if_managed_float(ISVREF(transfer_wrapper,(SI_Long)3L));
	ISVREF(transfer_wrapper,(SI_Long)2L) = FIX((SI_Long)0L);
	SVREF(transfer_wrapper,FIX((SI_Long)3L)) = collection_interval_qm;
	old_value = ISVREF(transfer_wrapper,(SI_Long)4L);
	if (old_value)
	    g2int_reclaim_gsi_instance_for_gsi(old_value);
	SVREF(transfer_wrapper,FIX((SI_Long)4L)) = value_to_set_qm;
	index_to_array_of_transfer_wrappers_new_value = 
		FIXNUM_ADD1(G2int_index_to_array_of_transfer_wrappers);
	G2int_index_to_array_of_transfer_wrappers = 
		index_to_array_of_transfer_wrappers_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_load_sensor_list_element;  /* handle-icp-load-sensor-list-element */

/* HANDLE-ICP-LOAD-SENSOR-LIST-ELEMENT */
Object g2int_handle_icp_load_sensor_list_element()
{
    Object corresponding_icp_object_index, collection_interval_qm;
    Object value_to_set_qm, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,137);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	collection_interval_qm = g2int_read_icp_gsi_ds_update_interval();
	value_to_set_qm = g2int_read_icp_gsi_permanent_remote_value();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_load_sensor_list_element__body(corresponding_icp_object_index,
		  collection_interval_qm,value_to_set_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_load_sensor_list_element,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_load_sensor_list_element,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_load_sensor_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    collection_interval_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_ds_update_interval();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_load_sensor_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    collection_interval_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value_to_set_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_permanent_remote_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(collection_interval_qm);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_load_sensor_list_element);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value_to_set_qm = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_load_sensor_list_element__body(corresponding_icp_object_index,
		  collection_interval_qm,value_to_set_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_end_sensor_list;  /* send-icp-end-sensor-list */

/* SEND-ICP-END-SENSOR-LIST */
Object g2int_send_icp_end_sensor_list()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,138);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_end_sensor_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)62L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_end_sensor_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_end_sensor_list,top,Nil);
		goto end_send_icp_end_sensor_list;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_end_sensor_list;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)62L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_end_sensor_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_sensor_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_sensor_list:
    return result;
}

/* HANDLE-ICP-END-SENSOR-LIST--BODY */
Object g2int_handle_icp_end_sensor_list__body()
{
    x_note_fn_call(43,139);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_end_sensor_list;  /* handle-icp-end-sensor-list */

/* HANDLE-ICP-END-SENSOR-LIST */
Object g2int_handle_icp_end_sensor_list()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,140);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_end_sensor_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_end_sensor_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_end_sensor_list,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_end_sensor_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_get_values_for_sensors_in_list;  /* send-icp-get-values-for-sensors-in-list */

/* SEND-ICP-GET-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_send_icp_get_values_for_sensors_in_list()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,141);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_get_values_for_sensors_in_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)63L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_get_values_for_sensors_in_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_get_values_for_sensors_in_list,top,
			Nil);
		goto end_send_icp_get_values_for_sensors_in_list;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_get_values_for_sensors_in_list;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)63L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_get_values_for_sensors_in_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_get_values_for_sensors_in_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_get_values_for_sensors_in_list:
    return result;
}

/* HANDLE-ICP-GET-VALUES-FOR-SENSORS-IN-LIST--BODY */
Object g2int_handle_icp_get_values_for_sensors_in_list__body()
{
    Object temp;

    x_note_fn_call(43,142);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	temp = 
		inline_extract_c_array(ISVREF(ISVREF(G2int_current_icp_socket,
		(SI_Long)29L),(SI_Long)3L),G2int_gsi_magic_offset);
	g2int_call_gsi_callback(3,G2int_gsi_get_data,temp,
		FIXNUM_SUB1(G2int_index_to_array_of_transfer_wrappers));
    }
    if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	G2int_gsi_reclaim_listqm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_get_values_for_sensors_in_list;  /* handle-icp-get-values-for-sensors-in-list */

/* HANDLE-ICP-GET-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_handle_icp_get_values_for_sensors_in_list()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,143);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_get_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_get_values_for_sensors_in_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_get_values_for_sensors_in_list,
			top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_get_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_set_values_for_sensors_in_list;  /* send-icp-set-values-for-sensors-in-list */

/* SEND-ICP-SET-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_send_icp_set_values_for_sensors_in_list()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,144);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_set_values_for_sensors_in_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)64L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_set_values_for_sensors_in_list,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_set_values_for_sensors_in_list,top,
			Nil);
		goto end_send_icp_set_values_for_sensors_in_list;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_set_values_for_sensors_in_list;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)64L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_set_values_for_sensors_in_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_set_values_for_sensors_in_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_set_values_for_sensors_in_list:
    return result;
}

/* HANDLE-ICP-SET-VALUES-FOR-SENSORS-IN-LIST--BODY */
Object g2int_handle_icp_set_values_for_sensors_in_list__body()
{
    Object temp;

    x_note_fn_call(43,145);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	temp = 
		inline_extract_c_array(ISVREF(ISVREF(G2int_current_icp_socket,
		(SI_Long)29L),(SI_Long)3L),G2int_gsi_magic_offset);
	g2int_call_gsi_callback(3,G2int_gsi_set_data,temp,
		FIXNUM_SUB1(G2int_index_to_array_of_transfer_wrappers));
    }
    if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	G2int_gsi_reclaim_listqm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_set_values_for_sensors_in_list;  /* handle-icp-set-values-for-sensors-in-list */

/* HANDLE-ICP-SET-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_handle_icp_set_values_for_sensors_in_list()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,146);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_set_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_set_values_for_sensors_in_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_set_values_for_sensors_in_list,
			top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_set_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_stop_sending_values_for_sensors_in_list;  /* send-icp-stop-sending-values-for-sensors-in-list */

/* SEND-ICP-STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_send_icp_stop_sending_values_for_sensors_in_list()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,147);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_stop_sending_values_for_sensors_in_list;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)74L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_stop_sending_values_for_sensors_in_list,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_stop_sending_values_for_sensors_in_list,
			top,Nil);
		goto end_send_icp_stop_sending_values_for_sensors_in_list;
	    }
	}
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_stop_sending_values_for_sensors_in_list;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)74L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_stop_sending_values_for_sensors_in_list);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_stop_sending_values_for_sensors_in_list;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_stop_sending_values_for_sensors_in_list:
    return result;
}

/* HANDLE-ICP-STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST--BODY */
Object g2int_handle_icp_stop_sending_values_for_sensors_in_list__body()
{
    Object temp;

    x_note_fn_call(43,148);
    if (FIXNUM_EQ(ISVREF(G2int_current_icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
	temp = 
		inline_extract_c_array(ISVREF(ISVREF(G2int_current_icp_socket,
		(SI_Long)29L),(SI_Long)3L),G2int_gsi_magic_offset);
	g2int_call_gsi_callback(3,G2int_gsi_receive_deregistrations,temp,
		FIXNUM_SUB1(G2int_index_to_array_of_transfer_wrappers));
    }
    if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects())) {
	g2int_gsi_reclaim_contents(G2int_gsi_reclaim_listqm,Qg2int_gsi);
	G2int_gsi_reclaim_listqm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_stop_sending_values_for_sensors_in_list;  /* handle-icp-stop-sending-values-for-sensors-in-list */

/* HANDLE-ICP-STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST */
Object g2int_handle_icp_stop_sending_values_for_sensors_in_list()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(43,149);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_stop_sending_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_stop_sending_values_for_sensors_in_list,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_stop_sending_values_for_sensors_in_list,
			top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_stop_sending_values_for_sensors_in_list__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_do_not_reformat_message_p;  /* write-icp-do-not-reformat-message-p */

/* WRITE-ICP-DO-NOT-REFORMAT-MESSAGE-P */
Object g2int_write_icp_do_not_reformat_message_p(do_not_reformat_message_p)
    Object do_not_reformat_message_p;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,150);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)21L ? 
		g2int_write_icp_boolean(do_not_reformat_message_p) : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_do_not_reformat_message_p,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_do_not_reformat_message_p,top,Nil);
	}
	do_not_reformat_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : do_not_reformat_message_p;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)21L) {
	    value = g2int_write_icp_boolean(do_not_reformat_message_p);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(do_not_reformat_message_p);
		g2int_resumable_icp_push(Qg2int_write_icp_do_not_reformat_message_p);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_do_not_reformat_message_p;  /* read-icp-do-not-reformat-message-p */

/* READ-ICP-DO-NOT-REFORMAT-MESSAGE-P */
Object g2int_read_icp_do_not_reformat_message_p()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,151);
    if (G2int_disable_resumability)
	temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)21L ? g2int_read_icp_boolean() : Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_do_not_reformat_message_p,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_do_not_reformat_message_p,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		(SI_Long)21L) {
	    value = g2int_read_icp_boolean();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_read_icp_do_not_reformat_message_p);
		return VALUES_1(G2int_icp_suspend);
	    }
	    temp = value;
	}
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_write_user_message_string;  /* send-icp-write-user-message-string */

/* SEND-ICP-WRITE-USER-MESSAGE-STRING */
Object g2int_send_icp_write_user_message_string(user_message,urgency_qm,
	    duration_qm,do_not_reformat_qm)
    Object user_message, urgency_qm, duration_qm, do_not_reformat_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,152);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_write_user_message_string;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)65L));
	  g2int_write_icp_text_string(user_message);
	  g2int_write_icp_unsigned_integer_or_nil(urgency_qm);
	  g2int_write_icp_unsigned_integer_or_nil(duration_qm);
	  g2int_write_icp_do_not_reformat_message_p(do_not_reformat_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_write_user_message_string,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_write_user_message_string,top,Nil);
		goto end_send_icp_write_user_message_string;
	    }
	}
	user_message = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : user_message;
	urgency_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : urgency_qm;
	duration_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : duration_qm;
	do_not_reformat_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : do_not_reformat_qm;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_write_user_message_string;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)65L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,g2int_write_icp_text_string(user_message))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer_or_nil(urgency_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer_or_nil(duration_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_do_not_reformat_message_p(do_not_reformat_qm))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(do_not_reformat_qm);
	      g2int_resumable_icp_push(duration_qm);
	      g2int_resumable_icp_push(urgency_qm);
	      g2int_resumable_icp_push(user_message);
	      g2int_resumable_icp_push(Qg2int_send_icp_write_user_message_string);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_write_user_message_string;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_write_user_message_string:
    return result;
}

/* HANDLE-ICP-WRITE-USER-MESSAGE-STRING--BODY */
Object g2int_handle_icp_write_user_message_string__body(user_message,
	    urgency_qm,duration_qm,do_not_reformat_qm)
    Object user_message, urgency_qm, duration_qm, do_not_reformat_qm;
{
    x_note_fn_call(43,153);
    g2int_gsi_write_user_message_string(user_message,urgency_qm,
	    duration_qm,do_not_reformat_qm);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_write_user_message_string;  /* handle-icp-write-user-message-string */

/* HANDLE-ICP-WRITE-USER-MESSAGE-STRING */
Object g2int_handle_icp_write_user_message_string()
{
    Object user_message, urgency_qm, duration_qm, do_not_reformat_qm;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,154);
    if (G2int_disable_resumability) {
	user_message = g2int_read_icp_text_string();
	urgency_qm = g2int_read_icp_unsigned_integer_or_nil();
	duration_qm = g2int_read_icp_unsigned_integer_or_nil();
	do_not_reformat_qm = g2int_read_icp_do_not_reformat_message_p();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_write_user_message_string__body(user_message,
		  urgency_qm,duration_qm,do_not_reformat_qm);
	POP_SPECIAL();
	g2int_reclaim_text_string(user_message);
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_write_user_message_string,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_write_user_message_string,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    user_message = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_text_string();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_write_user_message_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    user_message = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    urgency_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer_or_nil();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(user_message);
		g2int_resumable_icp_push(Qg2int_handle_icp_write_user_message_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    urgency_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    duration_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer_or_nil();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(urgency_qm);
		g2int_resumable_icp_push(user_message);
		g2int_resumable_icp_push(Qg2int_handle_icp_write_user_message_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    duration_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    do_not_reformat_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_do_not_reformat_message_p();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(duration_qm);
		g2int_resumable_icp_push(urgency_qm);
		g2int_resumable_icp_push(user_message);
		g2int_resumable_icp_push(Qg2int_handle_icp_write_user_message_string);
		return VALUES_1(G2int_icp_suspend);
	    }
	    do_not_reformat_qm = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_write_user_message_string__body(user_message,
		  urgency_qm,duration_qm,do_not_reformat_qm);
	POP_SPECIAL();
	g2int_reclaim_text_string(user_message);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* GSI-WRITE-USER-MESSAGE-STRING */
Object g2int_gsi_write_user_message_string(user_message,urgency_qm,
	    duration_qm,do_not_reformat_qm)
    Object user_message, urgency_qm, duration_qm, do_not_reformat_qm;
{
    Object temp;

    x_note_fn_call(43,155);
    user_message = 
	    g2int_convert_value_to_gsi_value(g2int_copy_text_string(user_message));
    g2int_call_gsi_callback(3,G2int_gsi_receive_message,user_message,
	    g2int_lengthw(user_message));
    temp = g2int_reclaim_text_or_gensym_string(user_message);
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_gsi_ds_value;  /* read-icp-gsi-ds-value */

/* READ-ICP-GSI-DS-VALUE */
Object g2int_read_icp_gsi_ds_value()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(43,156);
    if (G2int_disable_resumability)
	temp = g2int_read_icp_remote_value();
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gsi_ds_value,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gsi_ds_value,top,Nil);
	}
	value = g2int_read_icp_remote_value();
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(Qg2int_read_icp_gsi_ds_value);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

Object G2int_write_value_of_gsi_item_p = UNBOUND;

static Object Qg2int_write_icp_gsi_ds_value;  /* write-icp-gsi-ds-value */

/* WRITE-ICP-GSI-DS-VALUE */
Object g2int_write_icp_gsi_ds_value(gsi_ds_value)
    Object gsi_ds_value;
{
    Object write_value_of_gsi_item_p, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,157);
    if (G2int_disable_resumability) {
	write_value_of_gsi_item_p = T;
	PUSH_SPECIAL(G2int_write_value_of_gsi_item_p,write_value_of_gsi_item_p,
		0);
	  temp = g2int_write_icp_remote_value(gsi_ds_value);
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_gsi_ds_value,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_gsi_ds_value,top,Nil);
		goto end_write_icp_gsi_ds_value;
	    }
	}
	gsi_ds_value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_ds_value;
	write_value_of_gsi_item_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : T;
	PUSH_SPECIAL(G2int_write_value_of_gsi_item_p,write_value_of_gsi_item_p,
		0);
	  value = g2int_write_icp_remote_value(gsi_ds_value);
	  if (EQ(icp_suspend_1,value)) {
	      g2int_resumable_icp_push(G2int_write_value_of_gsi_item_p);
	      g2int_resumable_icp_push(gsi_ds_value);
	      g2int_resumable_icp_push(Qg2int_write_icp_gsi_ds_value);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_write_icp_gsi_ds_value;
	  }
	  temp = value;
	POP_SPECIAL();
    }
    result = VALUES_1(temp);
  end_write_icp_gsi_ds_value:
    return result;
}

static Object Qg2int_send_icp_receive_value_for_gsi_sensor;  /* send-icp-receive-value-for-gsi-sensor */

/* SEND-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR */
Object g2int_send_icp_receive_value_for_gsi_sensor(gsi_sensor,error_code,value)
    Object gsi_sensor, error_code, value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,158);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_gsi_sensor;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)68L));
	  g2int_write_icp_returned_gsi_sensor(gsi_sensor);
	  g2int_write_icp_unsigned_integer(error_code);
	  g2int_write_icp_gsi_ds_value(value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_receive_value_for_gsi_sensor,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_value_for_gsi_sensor,top,Nil);
		goto end_send_icp_receive_value_for_gsi_sensor;
	    }
	}
	gsi_sensor = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_sensor;
	error_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_code;
	value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_gsi_sensor;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)68L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_returned_gsi_sensor(gsi_sensor))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(error_code))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_ds_value(value))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(value);
	      g2int_resumable_icp_push(error_code);
	      g2int_resumable_icp_push(gsi_sensor);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_value_for_gsi_sensor);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_value_for_gsi_sensor;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_value_for_gsi_sensor:
    return result;
}

/* HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR--BODY */
Object g2int_handle_icp_receive_value_for_gsi_sensor__body(gsi_sensor,
	    error_code,value)
    Object gsi_sensor, error_code, value;
{
    x_note_fn_call(43,159);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_value_for_gsi_sensor;  /* handle-icp-receive-value-for-gsi-sensor */

/* HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR */
Object g2int_handle_icp_receive_value_for_gsi_sensor()
{
    Object gsi_sensor, error_code, value, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value_1;
    Declare_special(1);

    x_note_fn_call(43,160);
    if (G2int_disable_resumability) {
	gsi_sensor = g2int_read_icp_returned_gsi_sensor();
	error_code = g2int_read_icp_unsigned_integer();
	value = g2int_read_icp_gsi_ds_value();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_gsi_sensor__body(gsi_sensor,
		  error_code,value);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_receive_value_for_gsi_sensor,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_value_for_gsi_sensor,top,
			Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_sensor = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_returned_gsi_sensor();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_sensor = value_1;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_code = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_code = value_1;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_gsi_ds_value();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value = value_1;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_gsi_sensor__body(gsi_sensor,
		  error_code,value);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_receive_value_for_gsi_sensor_with_timestamp;  /* receive-value-for-gsi-sensor-with-timestamp */

static Object float_constant;      /* 2.145934799E+# */

/* GSI-RECEIVE-VALUE-FOR-GSI-SENSOR-1 */
Object g2int_gsi_receive_value_for_gsi_sensor_1(gsi_sensor,error_code,
	    value_qm,timestamp_qm)
    Object gsi_sensor, error_code, value_qm, timestamp_qm;
{
    Object collection_time_qm;
    char temp_1;
    double temp, timestamp, arg, arg_1;

    x_note_fn_call(43,161);
    collection_time_qm = Qg2int_never;
    if (value_qm && timestamp_qm) {
	temp = DFLOAT_ISAREF_1(timestamp_qm,(SI_Long)0L);
	timestamp = inline_convert_from_local_float_format(temp,
		g2int_gsi_option_is_set_p(G2int_gsi_use_gfloats) ? 
		(SI_Long)1L : (SI_Long)0L);
	arg = timestamp;
	arg_1 = 0.0;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    arg = timestamp;
	    arg_1 = 2.145934799E+9;
	    temp_1 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    collection_time_qm = timestamp_qm;
	else
	    g2int_gsi_error(4,
		    Qg2int_receive_value_for_gsi_sensor_with_timestamp,
		    G2int_gsi_timestamp_out_of_bounds,
		    DOUBLE_TO_DOUBLE_FLOAT(timestamp),float_constant);
    }
    else
	g2int_reclaim_if_managed_float(timestamp_qm);
    g2int_gsi_receive_value_for_gsi_sensor(gsi_sensor,error_code,value_qm,
	    collection_time_qm,Nil);
    return VALUES_1(Nil);
}

static Object Qg2int_read_icp_gsi_values;  /* read-icp-gsi-values */

/* READ-ICP-GSI-VALUES */
Object g2int_read_icp_gsi_values()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top;

    x_note_fn_call(43,162);
    if (G2int_disable_resumability)
	temp = Nil;
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gsi_values,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gsi_values,top,Nil);
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_receive_values_for_gsi_sensors;  /* send-icp-receive-values-for-gsi-sensors */

/* SEND-ICP-RECEIVE-VALUES-FOR-GSI-SENSORS */
Object g2int_send_icp_receive_values_for_gsi_sensors(gsi_values)
    Object gsi_values;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,163);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_values_for_gsi_sensors;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)80L));
	  g2int_write_icp_gsi_values(gsi_values);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_receive_values_for_gsi_sensors,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_values_for_gsi_sensors,top,
			Nil);
		goto end_send_icp_receive_values_for_gsi_sensors;
	    }
	}
	gsi_values = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_values;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_values_for_gsi_sensors;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)80L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_values(gsi_values))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(gsi_values);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_values_for_gsi_sensors);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_values_for_gsi_sensors;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_values_for_gsi_sensors:
    return result;
}

/* HANDLE-ICP-RECEIVE-VALUES-FOR-GSI-SENSORS--BODY */
Object g2int_handle_icp_receive_values_for_gsi_sensors__body(gsi_values)
    Object gsi_values;
{
    x_note_fn_call(43,164);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_values_for_gsi_sensors;  /* handle-icp-receive-values-for-gsi-sensors */

/* HANDLE-ICP-RECEIVE-VALUES-FOR-GSI-SENSORS */
Object g2int_handle_icp_receive_values_for_gsi_sensors()
{
    Object gsi_values, abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,165);
    if (G2int_disable_resumability) {
	gsi_values = g2int_read_icp_gsi_values();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_values_for_gsi_sensors__body(gsi_values);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_receive_values_for_gsi_sensors,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_values_for_gsi_sensors,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_values = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_values();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_values_for_gsi_sensors);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_values = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_values_for_gsi_sensors__body(gsi_values);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp;  /* send-icp-receive-value-for-gsi-sensor-with-timestamp */

/* SEND-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP */
Object g2int_send_icp_receive_value_for_gsi_sensor_with_timestamp(gsi_sensor,
	    error_code,value_qm,timestamp)
    Object gsi_sensor, error_code, value_qm, timestamp;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,166);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)76L));
	  g2int_write_icp_returned_gsi_sensor(gsi_sensor);
	  g2int_write_icp_unsigned_integer(error_code);
	  g2int_write_icp_gsi_ds_value(value_qm);
	  g2int_write_icp_gsi_timestamp(timestamp);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp,
			top,Nil);
		goto end_send_icp_receive_value_for_gsi_sensor_with_timestamp;
	    }
	}
	gsi_sensor = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_sensor;
	error_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_code;
	value_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_qm;
	timestamp = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : timestamp;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)76L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_returned_gsi_sensor(gsi_sensor))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(error_code))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_ds_value(value_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_timestamp(timestamp))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(timestamp);
	      g2int_resumable_icp_push(value_qm);
	      g2int_resumable_icp_push(error_code);
	      g2int_resumable_icp_push(gsi_sensor);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_value_for_gsi_sensor_with_timestamp;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_value_for_gsi_sensor_with_timestamp:
    return result;
}

/* HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP--BODY */
Object g2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp__body(gsi_sensor,
	    error_code,value_qm,timestamp)
    Object gsi_sensor, error_code, value_qm, timestamp;
{
    x_note_fn_call(43,167);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp;  /* handle-icp-receive-value-for-gsi-sensor-with-timestamp */

/* HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP */
Object g2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp()
{
    Object gsi_sensor, error_code, value_qm, timestamp;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,168);
    if (G2int_disable_resumability) {
	gsi_sensor = g2int_read_icp_returned_gsi_sensor();
	error_code = g2int_read_icp_unsigned_integer();
	value_qm = g2int_read_icp_gsi_ds_value();
	timestamp = g2int_read_icp_gsi_timestamp();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp__body(gsi_sensor,
		  error_code,value_qm,timestamp);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_sensor = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_returned_gsi_sensor();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_sensor = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_code = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_code = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_ds_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    timestamp = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_timestamp();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(value_qm);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp);
		return VALUES_1(G2int_icp_suspend);
	    }
	    timestamp = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp__body(gsi_sensor,
		  error_code,value_qm,timestamp);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_receive_gsi_sensor_value_vector;  /* send-icp-receive-gsi-sensor-value-vector */

/* SEND-ICP-RECEIVE-GSI-SENSOR-VALUE-VECTOR */
Object g2int_send_icp_receive_gsi_sensor_value_vector(gsi_sensor,
	    error_code,value,vector_1)
    Object gsi_sensor, error_code, value, vector_1;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,169);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_gsi_sensor_value_vector;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)78L));
	  g2int_write_icp_returned_gsi_sensor(gsi_sensor);
	  g2int_write_icp_unsigned_integer(error_code);
	  g2int_write_icp_gsi_ds_value(value);
	  g2int_write_icp_gsi_value_vector(vector_1);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_receive_gsi_sensor_value_vector,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_gsi_sensor_value_vector,
			top,Nil);
		goto end_send_icp_receive_gsi_sensor_value_vector;
	    }
	}
	gsi_sensor = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_sensor;
	error_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_code;
	value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value;
	vector_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : vector_1;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_gsi_sensor_value_vector;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)78L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_returned_gsi_sensor(gsi_sensor))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(error_code))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_ds_value(value))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_value_vector(vector_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(vector_1);
	      g2int_resumable_icp_push(value);
	      g2int_resumable_icp_push(error_code);
	      g2int_resumable_icp_push(gsi_sensor);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_gsi_sensor_value_vector);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_gsi_sensor_value_vector;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_gsi_sensor_value_vector:
    return result;
}

/* HANDLE-ICP-RECEIVE-GSI-SENSOR-VALUE-VECTOR--BODY */
Object g2int_handle_icp_receive_gsi_sensor_value_vector__body(gsi_sensor,
	    error_code,value,vector_1)
    Object gsi_sensor, error_code, value, vector_1;
{
    x_note_fn_call(43,170);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_gsi_sensor_value_vector;  /* handle-icp-receive-gsi-sensor-value-vector */

/* HANDLE-ICP-RECEIVE-GSI-SENSOR-VALUE-VECTOR */
Object g2int_handle_icp_receive_gsi_sensor_value_vector()
{
    Object gsi_sensor, error_code, value, vector_1, abort_for_icp_catcher_qm;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value_1;
    Declare_special(1);

    x_note_fn_call(43,171);
    if (G2int_disable_resumability) {
	gsi_sensor = g2int_read_icp_returned_gsi_sensor();
	error_code = g2int_read_icp_unsigned_integer();
	value = g2int_read_icp_gsi_ds_value();
	vector_1 = g2int_read_icp_gsi_value_vector();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_gsi_sensor_value_vector__body(gsi_sensor,
		  error_code,value,vector_1);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_receive_gsi_sensor_value_vector,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_gsi_sensor_value_vector,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_sensor = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_returned_gsi_sensor();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_sensor = value_1;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_code = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_code = value_1;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_gsi_ds_value();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value = value_1;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    vector_1 = g2int_resumable_icp_pop();
	else {
	    value_1 = g2int_read_icp_gsi_value_vector();
	    if (EQ(icp_suspend_1,value_1)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(value);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    vector_1 = value_1;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_gsi_sensor_value_vector__body(gsi_sensor,
		  error_code,value,vector_1);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector;  /* send-icp-receive-timestamped-gsi-sensor-value-vector */

/* SEND-ICP-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR */
Object g2int_send_icp_receive_timestamped_gsi_sensor_value_vector(gsi_sensor,
	    error_code,value_qm,timestamp,timestamped_vector)
    Object gsi_sensor, error_code, value_qm, timestamp, timestamped_vector;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(43,172);
    if (G2int_disable_resumability) {
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)79L));
	  g2int_write_icp_returned_gsi_sensor(gsi_sensor);
	  g2int_write_icp_unsigned_integer(error_code);
	  g2int_write_icp_gsi_ds_value(value_qm);
	  g2int_write_icp_gsi_timestamp(timestamp);
	  g2int_write_icp_gsi_value_vector(timestamped_vector);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector,
		    top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector,
			top,Nil);
		goto end_send_icp_receive_timestamped_gsi_sensor_value_vector;
	    }
	}
	gsi_sensor = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_sensor;
	error_code = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : error_code;
	value_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : value_qm;
	timestamp = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : timestamp;
	timestamped_vector = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : timestamped_vector;
	index_of_top_of_backtrace_stack = 
		G2int_index_of_top_of_backtrace_stack;
	PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		0);
	  if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		  G2int_size_of_basic_backtrace_information),
		  G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = Nil;
	      temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	      G2int_index_of_top_of_backtrace_stack = temp;
	      temp = G2int_backtrace_stack_for_internal_error;
	      svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
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
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)79L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		    case 5:
		      goto l5;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_returned_gsi_sensor(gsi_sensor))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,g2int_write_icp_unsigned_integer(error_code))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_ds_value(value_qm))) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,g2int_write_icp_gsi_timestamp(timestamp))) {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_gsi_value_vector(timestamped_vector))) {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(timestamped_vector);
	      g2int_resumable_icp_push(timestamp);
	      g2int_resumable_icp_push(value_qm);
	      g2int_resumable_icp_push(error_code);
	      g2int_resumable_icp_push(gsi_sensor);
	      g2int_resumable_icp_push(Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_receive_timestamped_gsi_sensor_value_vector;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_receive_timestamped_gsi_sensor_value_vector:
    return result;
}

/* HANDLE-ICP-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR--BODY */
Object g2int_handle_icp_receive_timestamped_gsi_sensor_value_vector__body(gsi_sensor,
	    error_code,value_qm,timestamp,timestamped_vector)
    Object gsi_sensor, error_code, value_qm, timestamp, timestamped_vector;
{
    x_note_fn_call(43,173);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector;  /* handle-icp-receive-timestamped-gsi-sensor-value-vector */

/* HANDLE-ICP-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR */
Object g2int_handle_icp_receive_timestamped_gsi_sensor_value_vector()
{
    Object gsi_sensor, error_code, value_qm, timestamp, timestamped_vector;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(43,174);
    if (G2int_disable_resumability) {
	gsi_sensor = g2int_read_icp_returned_gsi_sensor();
	error_code = g2int_read_icp_unsigned_integer();
	value_qm = g2int_read_icp_gsi_ds_value();
	timestamp = g2int_read_icp_gsi_timestamp();
	timestamped_vector = g2int_read_icp_gsi_value_vector();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_timestamped_gsi_sensor_value_vector__body(gsi_sensor,
		  error_code,value_qm,timestamp,timestamped_vector);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    gsi_sensor = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_returned_gsi_sensor();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    gsi_sensor = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    error_code = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    error_code = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value_qm = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_ds_value();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    value_qm = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    timestamp = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_timestamp();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(value_qm);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    timestamp = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    timestamped_vector = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_gsi_value_vector();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(timestamp);
		g2int_resumable_icp_push(value_qm);
		g2int_resumable_icp_push(error_code);
		g2int_resumable_icp_push(gsi_sensor);
		g2int_resumable_icp_push(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector);
		return VALUES_1(G2int_icp_suspend);
	    }
	    timestamped_vector = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_receive_timestamped_gsi_sensor_value_vector__body(gsi_sensor,
		  error_code,value_qm,timestamp,timestamped_vector);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

void gsi_common_INIT()
{
    Object temp, reclaim_structure_for_gsi_extension_data;
    Object reclaim_structure_for_gsi_history;
    Object reclaim_structure_for_gsi_attribute;
    Object reclaim_structure_for_gsi_transfer_wrapper;
    Object reclaim_structure_for_gsi_instance;
    Object reclaim_structure_for_gsi_instance_extension;
    Object reclaim_structure_for_gsi_array_wrapper;
    Object AB_package, Qg2int_equivalent_icp_value_type;
    Object Qg2int_unsigned_integer, Qg2int_gsi_value_error_code;
    Object list_constant_1, Qg2int_gsi_common;
    Object Qg2int_last_gsi_timestamp_unix_time;
    Object Qg2int_allocate_managed_float_box, Kfuncall;
    Object Qg2int_last_gsi_timestamp_hour, Qg2int_last_gsi_timestamp_day;
    Object Qg2int_last_gsi_timestamp_month, Qg2int_last_gsi_timestamp_year;
    Object Qg2int_gsi_timestamp_upper_bound, Qg2int_gsi_user_data_of_symbol;
    Object Qg2int_reclaim_icp_port_entry_for_gsi_instance, Qg2int_gsi_instance;
    Object list_constant, Qg2int_icp_object_map_for_gsi_instance;
    Object Qg2int_gsi_array_wrapper, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_gsi_array_wrapper_count;
    Object Qg2int_chain_of_available_gsi_array_wrappers;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_12, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_gsi_instance_extension;
    Object Qg2int_gsi_instance_extension_count;
    Object Qg2int_chain_of_available_gsi_instance_extensions;
    Object string_constant_11, Qg2int_gsi_bits_per_instance_owner;
    Object Qg2int_gsi_instance_count, Qg2int_chain_of_available_gsi_instances;
    Object string_constant_10, Qg2int_gsi_transfer_wrapper;
    Object Qg2int_gsi_transfer_wrapper_count;
    Object Qg2int_chain_of_available_gsi_transfer_wrappers, string_constant_9;
    Object Qg2int_gsi_attribute, Qg2int_gsi_attribute_count;
    Object Qg2int_chain_of_available_gsi_attributes, string_constant_8;
    Object Qg2int_gsi_history, Qg2int_gsi_history_count;
    Object Qg2int_chain_of_available_gsi_historys, string_constant_7;
    Object Qg2int_gsi_extension_data, Qg2int_gsi_extension_data_count;
    Object Qg2int_chain_of_available_gsi_extension_datas, string_constant_6;
    Object Qg2int_gsi_magic_offset, Qg2int_index_to_array_of_transfer_wrappers;
    Object Qg2int_global, Qg2int_size_of_array_of_transfer_wrappers;
    Object Qg2int_default_gsi_interface_countdown_timer_limit;
    Object Qg2int_gsi_number_of_callbacks, Qg2int_gsi_not_writing_fd;
    Object Qg2int_gsi_writing_fd, Qg2int_gsi_reset_context;
    Object Qg2int_gsi_start_context, Qg2int_gsi_idle;
    Object Qg2int_gsi_watchdog_function, Qg2int_gsi_missing_procedure_handler;
    Object Qg2int_gsi_error_handler, Qg2int_gsi_run_state_change;
    Object Qg2int_gsi_receive_message, Qg2int_gsi_set_data;
    Object Qg2int_gsi_get_data, Qg2int_gsi_receive_deregistrations;
    Object Qg2int_gsi_receive_registration, Qg2int_gsi_initialize_context;
    Object Qg2int_gsi_close_fd, Qg2int_gsi_open_fd, Qg2int_gsi_write_callback;
    Object Qg2int_gsi_read_callback, Qg2int_gsi_g2_poll;
    Object Qg2int_gsi_shutdown_context, Qg2int_gsi_resume_context;
    Object Qg2int_gsi_pause_context, Qg2int_gsi_get_tcp_port;
    Object Qg2int_gsi_set_up, Qg2int_gsi_number_of_options;
    Object Qg2int_gsi_user_owns_gsi_items, Qg2int_gsi_do_not_reformat_messages;
    Object Qg2int_gsi_protect_inner_calls, Qg2int_gsi_trace_run_loop;
    Object Qg2int_gsi_disable_interleaving, Qg2int_gsi_use_references;
    Object Qg2int_gsi_new_symbol_api, Qg2int_gsi_trace_run_state;
    Object Qg2int_gsi_no_flush, Qg2int_gsi_user_data_for_callbacks;
    Object Qg2int_gsi_wide_string_api, Qg2int_gsi_no_signal_handlers;
    Object Qg2int_gsi_string_check, Qg2int_gsi_non_c, Qg2int_gsi_use_gfloats;
    Object Qg2int_gsi_one_cycle, Qg2int_gsi_interface_waiting_for_shutdown_ack;
    Object Qg2int_gsi_interface_icp_connection_dead;
    Object Qg2int_gsi_interface_assumed_dead, Qg2int_gsi_interface_running_ok;
    Object Qg2int_gsi_interface_waiting_for_response;
    Object Qg2int_gsi_interface_initializing, Qg2int_bad_configuration;
    Object Qg2int_no_error, Qg2int_no_value_to_set, Qg2int_collect_one_now;
    Object Qg2int_cancel_collection;

    x_note_fn_call(43,175);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_cancel_collection = STATIC_SYMBOL("CANCEL-COLLECTION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_cancel_collection,FIX((SI_Long)-1L));
    Qg2int_collect_one_now = STATIC_SYMBOL("COLLECT-ONE-NOW",AB_package);
    SET_SYMBOL_VALUE(Qg2int_collect_one_now,FIX((SI_Long)0L));
    Qg2int_no_value_to_set = STATIC_SYMBOL("NO-VALUE-TO-SET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_value_to_set,Nil);
    Qg2int_no_error = STATIC_SYMBOL("NO-ERROR",AB_package);
    SET_SYMBOL_VALUE(Qg2int_no_error,FIX((SI_Long)0L));
    Qg2int_bad_configuration = STATIC_SYMBOL("BAD-CONFIGURATION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_bad_configuration,FIX((SI_Long)1L));
    if (G2int_gsi_magic_number == UNBOUND)
	G2int_gsi_magic_number = FIX((SI_Long)5472500L);
    Qg2int_gsi_magic_offset = STATIC_SYMBOL("GSI-MAGIC-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_magic_offset,FIX((SI_Long)1L));
    Qg2int_gsi_interface_initializing = 
	    STATIC_SYMBOL("GSI-INTERFACE-INITIALIZING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_initializing,FIX((SI_Long)0L));
    Qg2int_gsi_interface_waiting_for_response = 
	    STATIC_SYMBOL("GSI-INTERFACE-WAITING-FOR-RESPONSE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_waiting_for_response,
	    FIX((SI_Long)1L));
    Qg2int_gsi_interface_running_ok = 
	    STATIC_SYMBOL("GSI-INTERFACE-RUNNING-OK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_running_ok,FIX((SI_Long)2L));
    Qg2int_gsi_interface_assumed_dead = 
	    STATIC_SYMBOL("GSI-INTERFACE-ASSUMED-DEAD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_assumed_dead,FIX((SI_Long)-1L));
    Qg2int_gsi_interface_icp_connection_dead = 
	    STATIC_SYMBOL("GSI-INTERFACE-ICP-CONNECTION-DEAD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_icp_connection_dead,
	    FIX((SI_Long)-2L));
    Qg2int_gsi_interface_waiting_for_shutdown_ack = 
	    STATIC_SYMBOL("GSI-INTERFACE-WAITING-FOR-SHUTDOWN-ACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_interface_waiting_for_shutdown_ack,
	    FIX((SI_Long)-3L));
    Qg2int_gsi_one_cycle = STATIC_SYMBOL("GSI-ONE-CYCLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_one_cycle,FIX((SI_Long)0L));
    G2int_gsi_suppress_output = FIX((SI_Long)1L);
    Qg2int_gsi_use_gfloats = STATIC_SYMBOL("GSI-USE-GFLOATS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_use_gfloats,FIX((SI_Long)2L));
    Qg2int_gsi_non_c = STATIC_SYMBOL("GSI-NON-C",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_non_c,FIX((SI_Long)3L));
    Qg2int_gsi_string_check = STATIC_SYMBOL("GSI-STRING-CHECK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_string_check,FIX((SI_Long)4L));
    Qg2int_gsi_no_signal_handlers = STATIC_SYMBOL("GSI-NO-SIGNAL-HANDLERS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_no_signal_handlers,FIX((SI_Long)5L));
    Qg2int_gsi_wide_string_api = STATIC_SYMBOL("GSI-WIDE-STRING-API",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_wide_string_api,FIX((SI_Long)6L));
    Qg2int_gsi_user_data_for_callbacks = 
	    STATIC_SYMBOL("GSI-USER-DATA-FOR-CALLBACKS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_user_data_for_callbacks,FIX((SI_Long)7L));
    Qg2int_gsi_no_flush = STATIC_SYMBOL("GSI-NO-FLUSH",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_no_flush,FIX((SI_Long)8L));
    Qg2int_gsi_trace_run_state = STATIC_SYMBOL("GSI-TRACE-RUN-STATE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_trace_run_state,FIX((SI_Long)9L));
    Qg2int_gsi_new_symbol_api = STATIC_SYMBOL("GSI-NEW-SYMBOL-API",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_new_symbol_api,FIX((SI_Long)10L));
    Qg2int_gsi_use_references = STATIC_SYMBOL("GSI-USE-REFERENCES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_use_references,FIX((SI_Long)11L));
    Qg2int_gsi_disable_interleaving = 
	    STATIC_SYMBOL("GSI-DISABLE-INTERLEAVING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_disable_interleaving,FIX((SI_Long)12L));
    Qg2int_gsi_trace_run_loop = STATIC_SYMBOL("GSI-TRACE-RUN-LOOP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_trace_run_loop,FIX((SI_Long)13L));
    Qg2int_gsi_protect_inner_calls = 
	    STATIC_SYMBOL("GSI-PROTECT-INNER-CALLS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_protect_inner_calls,FIX((SI_Long)14L));
    Qg2int_gsi_do_not_reformat_messages = 
	    STATIC_SYMBOL("GSI-DO-NOT-REFORMAT-MESSAGES",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_do_not_reformat_messages,FIX((SI_Long)15L));
    Qg2int_gsi_user_owns_gsi_items = 
	    STATIC_SYMBOL("GSI-USER-OWNS-GSI-ITEMS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_user_owns_gsi_items,FIX((SI_Long)16L));
    Qg2int_gsi_number_of_options = STATIC_SYMBOL("GSI-NUMBER-OF-OPTIONS",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_number_of_options,FIX((SI_Long)17L));
    Qg2int_gsi_set_up = STATIC_SYMBOL("GSI-SET-UP",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_set_up,FIX((SI_Long)0L));
    Qg2int_gsi_get_tcp_port = STATIC_SYMBOL("GSI-GET-TCP-PORT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_get_tcp_port,FIX((SI_Long)1L));
    Qg2int_gsi_pause_context = STATIC_SYMBOL("GSI-PAUSE-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_pause_context,FIX((SI_Long)2L));
    Qg2int_gsi_resume_context = STATIC_SYMBOL("GSI-RESUME-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_resume_context,FIX((SI_Long)3L));
    Qg2int_gsi_shutdown_context = STATIC_SYMBOL("GSI-SHUTDOWN-CONTEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_shutdown_context,FIX((SI_Long)4L));
    Qg2int_gsi_g2_poll = STATIC_SYMBOL("GSI-G2-POLL",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_g2_poll,FIX((SI_Long)5L));
    Qg2int_gsi_read_callback = STATIC_SYMBOL("GSI-READ-CALLBACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_read_callback,FIX((SI_Long)6L));
    Qg2int_gsi_write_callback = STATIC_SYMBOL("GSI-WRITE-CALLBACK",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_write_callback,FIX((SI_Long)7L));
    Qg2int_gsi_open_fd = STATIC_SYMBOL("GSI-OPEN-FD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_open_fd,FIX((SI_Long)8L));
    Qg2int_gsi_close_fd = STATIC_SYMBOL("GSI-CLOSE-FD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_close_fd,FIX((SI_Long)9L));
    Qg2int_gsi_initialize_context = STATIC_SYMBOL("GSI-INITIALIZE-CONTEXT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_initialize_context,FIX((SI_Long)10L));
    Qg2int_gsi_receive_registration = 
	    STATIC_SYMBOL("GSI-RECEIVE-REGISTRATION",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_receive_registration,FIX((SI_Long)11L));
    Qg2int_gsi_receive_deregistrations = 
	    STATIC_SYMBOL("GSI-RECEIVE-DEREGISTRATIONS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_receive_deregistrations,FIX((SI_Long)12L));
    Qg2int_gsi_get_data = STATIC_SYMBOL("GSI-GET-DATA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_get_data,FIX((SI_Long)13L));
    Qg2int_gsi_set_data = STATIC_SYMBOL("GSI-SET-DATA",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_set_data,FIX((SI_Long)14L));
    Qg2int_gsi_receive_message = STATIC_SYMBOL("GSI-RECEIVE-MESSAGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_receive_message,FIX((SI_Long)15L));
    Qg2int_gsi_run_state_change = STATIC_SYMBOL("GSI-RUN-STATE-CHANGE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_run_state_change,FIX((SI_Long)16L));
    Qg2int_gsi_error_handler = STATIC_SYMBOL("GSI-ERROR-HANDLER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_error_handler,FIX((SI_Long)17L));
    Qg2int_gsi_missing_procedure_handler = 
	    STATIC_SYMBOL("GSI-MISSING-PROCEDURE-HANDLER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_missing_procedure_handler,FIX((SI_Long)18L));
    Qg2int_gsi_watchdog_function = STATIC_SYMBOL("GSI-WATCHDOG-FUNCTION",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_watchdog_function,FIX((SI_Long)19L));
    Qg2int_gsi_idle = STATIC_SYMBOL("GSI-IDLE",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_idle,FIX((SI_Long)20L));
    Qg2int_gsi_start_context = STATIC_SYMBOL("GSI-START-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_start_context,FIX((SI_Long)21L));
    Qg2int_gsi_reset_context = STATIC_SYMBOL("GSI-RESET-CONTEXT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_reset_context,FIX((SI_Long)22L));
    Qg2int_gsi_writing_fd = STATIC_SYMBOL("GSI-WRITING-FD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_writing_fd,FIX((SI_Long)23L));
    Qg2int_gsi_not_writing_fd = STATIC_SYMBOL("GSI-NOT-WRITING-FD",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_not_writing_fd,FIX((SI_Long)24L));
    Qg2int_gsi_number_of_callbacks = 
	    STATIC_SYMBOL("GSI-NUMBER-OF-CALLBACKS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_number_of_callbacks,FIX((SI_Long)25L));
    Qg2int_default_gsi_interface_countdown_timer_limit = 
	    STATIC_SYMBOL("DEFAULT-GSI-INTERFACE-COUNTDOWN-TIMER-LIMIT",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_gsi_interface_countdown_timer_limit,
	    FIX((SI_Long)10L));
    Qg2int_size_of_array_of_transfer_wrappers = 
	    STATIC_SYMBOL("SIZE-OF-ARRAY-OF-TRANSFER-WRAPPERS",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_of_array_of_transfer_wrappers,
	    FIX((SI_Long)50L));
    G2int_gsi_allocated_array_listqm = Nil;
    G2int_gsi_allocated_string_listqm = Nil;
    if (G2int_gsi_reclaim_listqm == UNBOUND)
	G2int_gsi_reclaim_listqm = Nil;
    Qg2int_global = STATIC_SYMBOL("GLOBAL",AB_package);
    if (G2int_gsi_reclaim_list_level == UNBOUND)
	G2int_gsi_reclaim_list_level = Qg2int_global;
    Qg2int_index_to_array_of_transfer_wrappers = 
	    STATIC_SYMBOL("INDEX-TO-ARRAY-OF-TRANSFER-WRAPPERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_index_to_array_of_transfer_wrappers,
	    G2int_index_to_array_of_transfer_wrappers);
    Qg2int_gsi_common = STATIC_SYMBOL("GSI-COMMON",AB_package);
    g2int_record_system_variable(Qg2int_index_to_array_of_transfer_wrappers,
	    Qg2int_gsi_common,Qg2int_gsi_magic_offset,Qnil,Qnil,Qnil,Qnil);
    if (G2int_make_gsi_instance_existing_instance == UNBOUND)
	G2int_make_gsi_instance_existing_instance = Nil;
    if (G2int_gsi_local_home == UNBOUND)
	G2int_gsi_local_home = Nil;
    if (G2int_gsi_context_to_socket_map == UNBOUND)
	G2int_gsi_context_to_socket_map = Nil;
    if (G2int_number_of_contexts_allocated == UNBOUND)
	G2int_number_of_contexts_allocated = FIX((SI_Long)0L);
    if (G2int_gsi_maximum_number_of_contexts == UNBOUND)
	G2int_gsi_maximum_number_of_contexts = Nil;
    Qg2int_gsi_context_to_socket_map = 
	    STATIC_SYMBOL("GSI-CONTEXT-TO-SOCKET-MAP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_context_to_socket_map,
	    G2int_gsi_context_to_socket_map);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gsi_extension_data_g2_struct = 
	    STATIC_SYMBOL("GSI-EXTENSION-DATA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_extension_data = STATIC_SYMBOL("GSI-EXTENSION-DATA",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_extension_data_g2_struct,
	    Qg2int_gsi_extension_data,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_extension_data,
	    Qg2_defstruct_structure_name_gsi_extension_data_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_extension_data == UNBOUND)
	G2int_the_type_description_of_gsi_extension_data = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l83-By1n83-By8m8k1l8m0000001l1m8p83=Xykzk0k0");
    temp = G2int_the_type_description_of_gsi_extension_data;
    G2int_the_type_description_of_gsi_extension_data = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_6));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_extension_data_g2_struct,
	    G2int_the_type_description_of_gsi_extension_data,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_extension_data,
	    G2int_the_type_description_of_gsi_extension_data,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_extension_datas = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-EXTENSION-DATAS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_extension_datas,
	    G2int_chain_of_available_gsi_extension_datas);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_extension_datas,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_extension_data_count = 
	    STATIC_SYMBOL("GSI-EXTENSION-DATA-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_extension_data_count,
	    G2int_gsi_extension_data_count);
    g2int_record_system_variable(Qg2int_gsi_extension_data_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gsi_extension_data = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_extension_data,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_extension_data,
	    reclaim_structure_for_gsi_extension_data);
    Qg2int_send_icp_define_gsi_interface = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-GSI-INTERFACE",AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_gsi_interface,
	    STATIC_FUNCTION(g2int_send_icp_define_gsi_interface,NIL,FALSE,
	    1,1));
    Qg2int_handle_icp_define_gsi_interface = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-GSI-INTERFACE",AB_package);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_gsi_interface,
	    STATIC_FUNCTION(g2int_handle_icp_define_gsi_interface,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_gsi_interface,
	    FIX((SI_Long)77L));
    Qg2int_send_icp_send_data_values_if_any = 
	    STATIC_SYMBOL("SEND-ICP-SEND-DATA-VALUES-IF-ANY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_send_data_values_if_any,
	    STATIC_FUNCTION(g2int_send_icp_send_data_values_if_any,NIL,
	    FALSE,7,7));
    Qg2int_handle_icp_send_data_values_if_any = 
	    STATIC_SYMBOL("HANDLE-ICP-SEND-DATA-VALUES-IF-ANY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_send_data_values_if_any,
	    STATIC_FUNCTION(g2int_handle_icp_send_data_values_if_any,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_send_data_values_if_any,
	    FIX((SI_Long)73L));
    Qg2int_send_icp_receive_value_for_ping_request = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-VALUE-FOR-PING-REQUEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_value_for_ping_request,
	    STATIC_FUNCTION(g2int_send_icp_receive_value_for_ping_request,
	    NIL,FALSE,8,8));
    Qg2int_handle_icp_receive_value_for_ping_request = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-VALUE-FOR-PING-REQUEST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_value_for_ping_request,
	    STATIC_FUNCTION(g2int_handle_icp_receive_value_for_ping_request,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_value_for_ping_request,
	    FIX((SI_Long)67L));
    Qg2_defstruct_structure_name_gsi_history_g2_struct = 
	    STATIC_SYMBOL("GSI-HISTORY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_history = STATIC_SYMBOL("GSI-HISTORY",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_history_g2_struct,
	    Qg2int_gsi_history,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_history,
	    Qg2_defstruct_structure_name_gsi_history_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_history == UNBOUND)
	G2int_the_type_description_of_gsi_history = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8l83-Cy1n83-Cy8m8k1l8m0000001m1n8n83*Zy1o83-Ey83-Gy83-Fy83-Dy1m8p83=Yykrk0k0");
    temp = G2int_the_type_description_of_gsi_history;
    G2int_the_type_description_of_gsi_history = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_7));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_history_g2_struct,
	    G2int_the_type_description_of_gsi_history,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_history,
	    G2int_the_type_description_of_gsi_history,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_historys = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-HISTORYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_historys,
	    G2int_chain_of_available_gsi_historys);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_historys,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_history_count = STATIC_SYMBOL("GSI-HISTORY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_history_count,
	    G2int_gsi_history_count);
    g2int_record_system_variable(Qg2int_gsi_history_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_history = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_history,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_history,reclaim_structure_for_gsi_history);
    Qg2_defstruct_structure_name_gsi_attribute_g2_struct = 
	    STATIC_SYMBOL("GSI-ATTRIBUTE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_attribute = STATIC_SYMBOL("GSI-ATTRIBUTE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_attribute_g2_struct,
	    Qg2int_gsi_attribute,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_attribute,
	    Qg2_defstruct_structure_name_gsi_attribute_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_attribute == UNBOUND)
	G2int_the_type_description_of_gsi_attribute = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8l83-7y1n83-7y8m8k1l8m0000001m1n8n83*Yy1n83-Ay83-8y83-9y1m8p83=Wykqk0k0");
    temp = G2int_the_type_description_of_gsi_attribute;
    G2int_the_type_description_of_gsi_attribute = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_8));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_attribute_g2_struct,
	    G2int_the_type_description_of_gsi_attribute,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_attribute,
	    G2int_the_type_description_of_gsi_attribute,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_attributes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-ATTRIBUTES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_attributes,
	    G2int_chain_of_available_gsi_attributes);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_attributes,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_attribute_count = STATIC_SYMBOL("GSI-ATTRIBUTE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_attribute_count,
	    G2int_gsi_attribute_count);
    g2int_record_system_variable(Qg2int_gsi_attribute_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_attribute = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_attribute,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_attribute,reclaim_structure_for_gsi_attribute);
    Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct = 
	    STATIC_SYMBOL("GSI-TRANSFER-WRAPPER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_transfer_wrapper = STATIC_SYMBOL("GSI-TRANSFER-WRAPPER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct,
	    Qg2int_gsi_transfer_wrapper,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_transfer_wrapper,
	    Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_transfer_wrapper == UNBOUND)
	G2int_the_type_description_of_gsi_transfer_wrapper = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8l83-Qy1n83-Qy8m8k1l8m0000001m1n8n83*cy1p83-Ny83-Oy83-Py83-Ly83-My1m8p83=cykqk0k0");
    temp = G2int_the_type_description_of_gsi_transfer_wrapper;
    G2int_the_type_description_of_gsi_transfer_wrapper = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_9));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_transfer_wrapper_g2_struct,
	    G2int_the_type_description_of_gsi_transfer_wrapper,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_transfer_wrapper,
	    G2int_the_type_description_of_gsi_transfer_wrapper,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_transfer_wrappers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-TRANSFER-WRAPPERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_transfer_wrappers,
	    G2int_chain_of_available_gsi_transfer_wrappers);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_transfer_wrappers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_transfer_wrapper_count = 
	    STATIC_SYMBOL("GSI-TRANSFER-WRAPPER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_transfer_wrapper_count,
	    G2int_gsi_transfer_wrapper_count);
    g2int_record_system_variable(Qg2int_gsi_transfer_wrapper_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_transfer_wrapper = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_transfer_wrapper,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_transfer_wrapper,
	    reclaim_structure_for_gsi_transfer_wrapper);
    Qg2int_user = STATIC_SYMBOL("USER",AB_package);
    Qg2int_context = STATIC_SYMBOL("CONTEXT",AB_package);
    Qg2_defstruct_structure_name_gsi_instance_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_instance = STATIC_SYMBOL("GSI-INSTANCE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_instance_g2_struct,
	    Qg2int_gsi_instance,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_instance,
	    Qg2_defstruct_structure_name_gsi_instance_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_instance == UNBOUND)
	G2int_the_type_description_of_gsi_instance = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8l83-Hy1n83-Hy8m8k1l8m0000001m1n8n83*ay01m8p83=Zykok0k0");
    temp = G2int_the_type_description_of_gsi_instance;
    G2int_the_type_description_of_gsi_instance = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_10));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_instance_g2_struct,
	    G2int_the_type_description_of_gsi_instance,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_instance,
	    G2int_the_type_description_of_gsi_instance,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_instances = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-INSTANCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_instances,
	    G2int_chain_of_available_gsi_instances);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_instances,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_instance_count = STATIC_SYMBOL("GSI-INSTANCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_instance_count,
	    G2int_gsi_instance_count);
    g2int_record_system_variable(Qg2int_gsi_instance_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_instance = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_instance,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_instance,reclaim_structure_for_gsi_instance);
    Qg2int_gsi_bits_per_instance_owner = 
	    STATIC_SYMBOL("GSI-BITS-PER-INSTANCE-OWNER",AB_package);
    SET_SYMBOL_VALUE(Qg2int_gsi_bits_per_instance_owner,FIX((SI_Long)3L));
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_gsi_event_queue = STATIC_SYMBOL("GSI-EVENT-QUEUE",AB_package);
    Qg2int_gsi_input_queue = STATIC_SYMBOL("GSI-INPUT-QUEUE",AB_package);
    Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-EXTENSION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_instance_extension = STATIC_SYMBOL("GSI-INSTANCE-EXTENSION",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct,
	    Qg2int_gsi_instance_extension,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_instance_extension,
	    Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_instance_extension == UNBOUND)
	G2int_the_type_description_of_gsi_instance_extension = Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8l83-Iy1n83-Iy8m8k1l8m0000001m1n8n83*by01m8p83=aykzk0k0");
    temp = G2int_the_type_description_of_gsi_instance_extension;
    G2int_the_type_description_of_gsi_instance_extension = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_11));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_instance_extension_g2_struct,
	    G2int_the_type_description_of_gsi_instance_extension,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_instance_extension,
	    G2int_the_type_description_of_gsi_instance_extension,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_instance_extensions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-INSTANCE-EXTENSIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_instance_extensions,
	    G2int_chain_of_available_gsi_instance_extensions);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_instance_extensions,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_instance_extension_count = 
	    STATIC_SYMBOL("GSI-INSTANCE-EXTENSION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_instance_extension_count,
	    G2int_gsi_instance_extension_count);
    g2int_record_system_variable(Qg2int_gsi_instance_extension_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_instance_extension = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_instance_extension,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_instance_extension,
	    reclaim_structure_for_gsi_instance_extension);
    Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct = 
	    STATIC_SYMBOL("GSI-ARRAY-WRAPPER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_array_wrapper = STATIC_SYMBOL("GSI-ARRAY-WRAPPER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct,
	    Qg2int_gsi_array_wrapper,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_array_wrapper,
	    Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_array_wrapper == UNBOUND)
	G2int_the_type_description_of_gsi_array_wrapper = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8l83-6y1n83-6y8m8k1l8m0000001l1n8n83*Xy1m83-5y83-4yknk0k0");
    temp = G2int_the_type_description_of_gsi_array_wrapper;
    G2int_the_type_description_of_gsi_array_wrapper = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_12));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_array_wrapper_g2_struct,
	    G2int_the_type_description_of_gsi_array_wrapper,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_array_wrapper,
	    G2int_the_type_description_of_gsi_array_wrapper,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_array_wrappers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-ARRAY-WRAPPERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_array_wrappers,
	    G2int_chain_of_available_gsi_array_wrappers);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_array_wrappers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_array_wrapper_count = 
	    STATIC_SYMBOL("GSI-ARRAY-WRAPPER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_array_wrapper_count,
	    G2int_gsi_array_wrapper_count);
    g2int_record_system_variable(Qg2int_gsi_array_wrapper_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_array_wrapper = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_array_wrapper,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_array_wrapper,reclaim_structure_for_gsi_array_wrapper);
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_set_access_form_for_gsi_instance = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-GSI-INSTANCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_gsi_instance,
	    STATIC_FUNCTION(g2int_set_access_form_for_gsi_instance,NIL,
	    FALSE,2,2));
    Qg2int_icp_object_map_for_gsi_instance = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-GSI-INSTANCE",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_gsi_instance,Qg2int_gsi_instance);
    g2int_initialize_icp_object_type_compile(Qg2int_gsi_instance,
	    Qg2int_item_index_space,list_constant);
    Qg2int_reclaim_icp_port_entry_for_gsi_instance = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-GSI-INSTANCE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_gsi_instance,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_gsi_instance,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_gsi_instance,Qnil,Qnil,
	    Qg2int_reclaim_icp_port_entry_for_gsi_instance);
    Qg2int_gsi_user_data_of_symbol = 
	    STATIC_SYMBOL("GSI-USER-DATA-OF-SYMBOL",AB_package);
    G2int_gsi_user_data_of_symbol_prop = Qg2int_gsi_user_data_of_symbol;
    G2int_gsi_most_recent_error = FIX((SI_Long)0L);
    G2int_gsi_most_recent_error_message = Nil;
    G2int_gsi_most_recent_error_remote_procedure_identifier = Nil;
    if (G2int_in_unprotected_gsi_api_call_p == UNBOUND)
	G2int_in_unprotected_gsi_api_call_p = Nil;
    if (G2int_gsi_protect_inner_calls_p == UNBOUND)
	G2int_gsi_protect_inner_calls_p = Nil;
    Qg2int_gsi_typed_array = STATIC_SYMBOL("GSI-TYPED-ARRAY",AB_package);
    Qg2int_gsi_encoded_symbol_names = 
	    STATIC_SYMBOL("GSI-ENCODED-SYMBOL-NAMES",AB_package);
    G2int_gsi_encoded_symbol_names_prop = Qg2int_gsi_encoded_symbol_names;
    if (G2int_temporary_string_buffer == UNBOUND)
	G2int_temporary_string_buffer = Nil;
    Qg2int_gsi_timestamp_upper_bound = 
	    STATIC_SYMBOL("GSI-TIMESTAMP-UPPER-BOUND",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_timestamp_upper_bound,
	    G2int_gsi_timestamp_upper_bound);
    float_constant = STATIC_FLOAT(2.145934799E+9);
    SET_SYMBOL_VALUE(Qg2int_gsi_timestamp_upper_bound,float_constant);
    string_constant_1 = 
	    STATIC_STRING("Out-of-range timestamp seen in ~a:~%~\n     timestamp: ~d  Valid range: 0.0 < t < ~d");
    Qg2int_last_gsi_timestamp_year = 
	    STATIC_SYMBOL("LAST-GSI-TIMESTAMP-YEAR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_last_gsi_timestamp_year,
	    G2int_last_gsi_timestamp_year);
    g2int_record_system_variable(Qg2int_last_gsi_timestamp_year,
	    Qg2int_gsi_common,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_last_gsi_timestamp_month = 
	    STATIC_SYMBOL("LAST-GSI-TIMESTAMP-MONTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_last_gsi_timestamp_month,
	    G2int_last_gsi_timestamp_month);
    g2int_record_system_variable(Qg2int_last_gsi_timestamp_month,
	    Qg2int_gsi_common,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_last_gsi_timestamp_day = STATIC_SYMBOL("LAST-GSI-TIMESTAMP-DAY",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_last_gsi_timestamp_day,
	    G2int_last_gsi_timestamp_day);
    g2int_record_system_variable(Qg2int_last_gsi_timestamp_day,
	    Qg2int_gsi_common,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_last_gsi_timestamp_hour = 
	    STATIC_SYMBOL("LAST-GSI-TIMESTAMP-HOUR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_last_gsi_timestamp_hour,
	    G2int_last_gsi_timestamp_hour);
    g2int_record_system_variable(Qg2int_last_gsi_timestamp_hour,
	    Qg2int_gsi_common,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_last_gsi_timestamp_unix_time = 
	    STATIC_SYMBOL("LAST-GSI-TIMESTAMP-UNIX-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_last_gsi_timestamp_unix_time,
	    G2int_last_gsi_timestamp_unix_time);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_allocate_managed_float_box = 
	    STATIC_SYMBOL("ALLOCATE-MANAGED-FLOAT-BOX",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_allocate_managed_float_box,
	    STATIC_FUNCTION(g2int_allocate_managed_float_box,NIL,FALSE,0,0));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_allocate_managed_float_box);
    g2int_record_system_variable(Qg2int_last_gsi_timestamp_unix_time,
	    Qg2int_gsi_common,list_constant_1,Qnil,Qnil,Qnil,Qnil);
    Qg2int_read_icp_gsi_timestamp = STATIC_SYMBOL("READ-ICP-GSI-TIMESTAMP",
	    AB_package);
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_true = STATIC_SYMBOL("TRUE",AB_package);
    Qg2int_false = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_timestamp,
	    STATIC_FUNCTION(g2int_read_icp_gsi_timestamp,NIL,FALSE,0,0));
    Qg2int_write_icp_gsi_timestamp = 
	    STATIC_SYMBOL("WRITE-ICP-GSI-TIMESTAMP",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_gsi_timestamp,
	    STATIC_FUNCTION(g2int_write_icp_gsi_timestamp,NIL,FALSE,1,1));
    Qg2int_gsi_value_error_code = STATIC_SYMBOL("GSI-VALUE-ERROR-CODE",
	    AB_package);
    Qg2int_unsigned_integer = STATIC_SYMBOL("UNSIGNED-INTEGER",AB_package);
    Qg2int_equivalent_icp_value_type = 
	    STATIC_SYMBOL("EQUIVALENT-ICP-VALUE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_value_error_code,
	    Qg2int_unsigned_integer,Qg2int_equivalent_icp_value_type);
    Qg2int_read_icp_returned_gsi_sensor = 
	    STATIC_SYMBOL("READ-ICP-RETURNED-GSI-SENSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_returned_gsi_sensor,
	    STATIC_FUNCTION(g2int_read_icp_returned_gsi_sensor,NIL,FALSE,0,0));
    Qg2int_write_icp_returned_gsi_sensor = 
	    STATIC_SYMBOL("WRITE-ICP-RETURNED-GSI-SENSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_returned_gsi_sensor,
	    STATIC_FUNCTION(g2int_write_icp_returned_gsi_sensor,NIL,FALSE,
	    1,1));
    Qg2int_never = STATIC_SYMBOL("NEVER",AB_package);
    Qg2int_attribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qg2int_class_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",
	    AB_package);
    Qg2int_read_icp_gsi_value_vector = 
	    STATIC_SYMBOL("READ-ICP-GSI-VALUE-VECTOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_value_vector,
	    STATIC_FUNCTION(g2int_read_icp_gsi_value_vector,NIL,FALSE,0,0));
    Qg2int_send_icp_initialize_gsi_interface = 
	    STATIC_SYMBOL("SEND-ICP-INITIALIZE-GSI-INTERFACE",AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_initialize_gsi_interface,
	    STATIC_FUNCTION(g2int_send_icp_initialize_gsi_interface,NIL,
	    FALSE,7,7));
    Qg2int_g2 = STATIC_SYMBOL("G2",AB_package);
    Qg2int_handle_icp_initialize_gsi_interface = 
	    STATIC_SYMBOL("HANDLE-ICP-INITIALIZE-GSI-INTERFACE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_initialize_gsi_interface,
	    STATIC_FUNCTION(g2int_handle_icp_initialize_gsi_interface,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_initialize_gsi_interface,
	    FIX((SI_Long)338L));
    Qg2int_send_icp_return_initialize_gsi_interface_status = 
	    STATIC_SYMBOL("SEND-ICP-RETURN-INITIALIZE-GSI-INTERFACE-STATUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_return_initialize_gsi_interface_status,
	    STATIC_FUNCTION(g2int_send_icp_return_initialize_gsi_interface_status,
	    NIL,FALSE,1,1));
    Qg2int_gsi_initiate_connection = 
	    STATIC_SYMBOL("GSI_INITIATE_CONNECTION",AB_package);
    Qg2int_handle_icp_return_initialize_gsi_interface_status = 
	    STATIC_SYMBOL("HANDLE-ICP-RETURN-INITIALIZE-GSI-INTERFACE-STATUS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_return_initialize_gsi_interface_status,
	    STATIC_FUNCTION(g2int_handle_icp_return_initialize_gsi_interface_status,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_return_initialize_gsi_interface_status,
	    FIX((SI_Long)339L));
    Qg2int_send_icp_pause_data_server = 
	    STATIC_SYMBOL("SEND-ICP-PAUSE-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_pause_data_server,
	    STATIC_FUNCTION(g2int_send_icp_pause_data_server,NIL,FALSE,0,0));
    Qg2int_handle_icp_pause_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-PAUSE-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_pause_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_pause_data_server,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_pause_data_server,
	    FIX((SI_Long)71L));
    Qg2int_send_icp_resume_data_server = 
	    STATIC_SYMBOL("SEND-ICP-RESUME-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_resume_data_server,
	    STATIC_FUNCTION(g2int_send_icp_resume_data_server,NIL,FALSE,0,0));
    Qg2int_handle_icp_resume_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUME-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_resume_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_resume_data_server,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_resume_data_server,
	    FIX((SI_Long)72L));
    Qg2int_send_icp_start_data_server = 
	    STATIC_SYMBOL("SEND-ICP-START-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_start_data_server,
	    STATIC_FUNCTION(g2int_send_icp_start_data_server,NIL,FALSE,0,0));
    Qg2int_handle_icp_start_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-START-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_start_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_start_data_server,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_start_data_server,
	    FIX((SI_Long)363L));
    Qg2int_send_icp_reset_data_server = 
	    STATIC_SYMBOL("SEND-ICP-RESET-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_reset_data_server,
	    STATIC_FUNCTION(g2int_send_icp_reset_data_server,NIL,FALSE,0,0));
    Qg2int_handle_icp_reset_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-RESET-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_reset_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_reset_data_server,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_reset_data_server,
	    FIX((SI_Long)364L));
    Qg2int_send_icp_initialize_data_server = 
	    STATIC_SYMBOL("SEND-ICP-INITIALIZE-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_initialize_data_server,
	    STATIC_FUNCTION(g2int_send_icp_initialize_data_server,NIL,
	    FALSE,1,1));
    Qg2int_initialize_data_server_message = 
	    STATIC_SYMBOL("INITIALIZE-DATA-SERVER-MESSAGE",AB_package);
    Qg2int_handle_icp_initialize_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-INITIALIZE-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_initialize_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_initialize_data_server,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_initialize_data_server,
	    FIX((SI_Long)69L));
    string_constant_2 = 
	    STATIC_STRING("Connection request received - context ~A~A~%");
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    string_constant_3 = STATIC_STRING("Connection ~A - context ~A~A~%");
    string_constant_4 = STATIC_STRING("rejected");
    string_constant_5 = STATIC_STRING("accepted");
    Qg2int_send_icp_return_peer_version = 
	    STATIC_SYMBOL("SEND-ICP-RETURN-PEER-VERSION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_return_peer_version,
	    STATIC_FUNCTION(g2int_send_icp_return_peer_version,NIL,FALSE,2,2));
    Qg2int_handle_icp_return_peer_version = 
	    STATIC_SYMBOL("HANDLE-ICP-RETURN-PEER-VERSION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_return_peer_version,
	    STATIC_FUNCTION(g2int_handle_icp_return_peer_version,NIL,FALSE,
	    0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_return_peer_version,
	    FIX((SI_Long)66L));
    Qg2int_write_icp_gsi_ds_update_interval = 
	    STATIC_SYMBOL("WRITE-ICP-GSI-DS-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_gsi_ds_update_interval,
	    STATIC_FUNCTION(g2int_write_icp_gsi_ds_update_interval,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_gsi_ds_update_interval = 
	    STATIC_SYMBOL("READ-ICP-GSI-DS-UPDATE-INTERVAL",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_ds_update_interval,
	    STATIC_FUNCTION(g2int_read_icp_gsi_ds_update_interval,NIL,
	    FALSE,0,0));
    Qg2int_send_icp_define_gsi_sensor = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-GSI-SENSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_gsi_sensor,
	    STATIC_FUNCTION(g2int_send_icp_define_gsi_sensor,NIL,FALSE,7,7));
    Qg2int_handle_icp_define_gsi_sensor = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-GSI-SENSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_gsi_sensor,
	    STATIC_FUNCTION(g2int_handle_icp_define_gsi_sensor,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_gsi_sensor,
	    FIX((SI_Long)75L));
    Qg2int_send_icp_register_corresponding_icp_object = 
	    STATIC_SYMBOL("SEND-ICP-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_register_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_send_icp_register_corresponding_icp_object,
	    NIL,FALSE,9,9));
    Qg2int_handle_icp_register_corresponding_icp_object = 
	    STATIC_SYMBOL("HANDLE-ICP-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_register_corresponding_icp_object,
	    STATIC_FUNCTION(g2int_handle_icp_register_corresponding_icp_object,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_register_corresponding_icp_object,
	    FIX((SI_Long)322L));
    Qg2int_gsi_reference_flag = STATIC_SYMBOL("GSI-REFERENCE-FLAG",AB_package);
    Qg2int_send_icp_modify_gsi_sensor_definition = 
	    STATIC_SYMBOL("SEND-ICP-MODIFY-GSI-SENSOR-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_modify_gsi_sensor_definition,
	    STATIC_FUNCTION(g2int_send_icp_modify_gsi_sensor_definition,
	    NIL,FALSE,5,5));
    Qg2int_handle_icp_modify_gsi_sensor_definition = 
	    STATIC_SYMBOL("HANDLE-ICP-MODIFY-GSI-SENSOR-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_modify_gsi_sensor_definition,
	    STATIC_FUNCTION(g2int_handle_icp_modify_gsi_sensor_definition,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_modify_gsi_sensor_definition,
	    FIX((SI_Long)59L));
    Qg2int_send_icp_begin_sensor_list = 
	    STATIC_SYMBOL("SEND-ICP-BEGIN-SENSOR-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_begin_sensor_list,
	    STATIC_FUNCTION(g2int_send_icp_begin_sensor_list,NIL,FALSE,0,0));
    Qg2int_handle_icp_begin_sensor_list = 
	    STATIC_SYMBOL("HANDLE-ICP-BEGIN-SENSOR-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_begin_sensor_list,
	    STATIC_FUNCTION(g2int_handle_icp_begin_sensor_list,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_begin_sensor_list,
	    FIX((SI_Long)60L));
    Qg2int_send_icp_load_sensor_list_element = 
	    STATIC_SYMBOL("SEND-ICP-LOAD-SENSOR-LIST-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_load_sensor_list_element,
	    STATIC_FUNCTION(g2int_send_icp_load_sensor_list_element,NIL,
	    FALSE,3,3));
    Qg2int_handle_icp_load_sensor_list_element = 
	    STATIC_SYMBOL("HANDLE-ICP-LOAD-SENSOR-LIST-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_load_sensor_list_element,
	    STATIC_FUNCTION(g2int_handle_icp_load_sensor_list_element,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_load_sensor_list_element,
	    FIX((SI_Long)61L));
    Qg2int_send_icp_end_sensor_list = 
	    STATIC_SYMBOL("SEND-ICP-END-SENSOR-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_end_sensor_list,
	    STATIC_FUNCTION(g2int_send_icp_end_sensor_list,NIL,FALSE,0,0));
    Qg2int_handle_icp_end_sensor_list = 
	    STATIC_SYMBOL("HANDLE-ICP-END-SENSOR-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_end_sensor_list,
	    STATIC_FUNCTION(g2int_handle_icp_end_sensor_list,NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_end_sensor_list,
	    FIX((SI_Long)62L));
    Qg2int_send_icp_get_values_for_sensors_in_list = 
	    STATIC_SYMBOL("SEND-ICP-GET-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_get_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_send_icp_get_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    Qg2int_handle_icp_get_values_for_sensors_in_list = 
	    STATIC_SYMBOL("HANDLE-ICP-GET-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_get_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_handle_icp_get_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_get_values_for_sensors_in_list,
	    FIX((SI_Long)63L));
    Qg2int_send_icp_set_values_for_sensors_in_list = 
	    STATIC_SYMBOL("SEND-ICP-SET-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_set_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_send_icp_set_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    Qg2int_handle_icp_set_values_for_sensors_in_list = 
	    STATIC_SYMBOL("HANDLE-ICP-SET-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_set_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_handle_icp_set_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_set_values_for_sensors_in_list,
	    FIX((SI_Long)64L));
    Qg2int_send_icp_stop_sending_values_for_sensors_in_list = 
	    STATIC_SYMBOL("SEND-ICP-STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_stop_sending_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_send_icp_stop_sending_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    Qg2int_handle_icp_stop_sending_values_for_sensors_in_list = 
	    STATIC_SYMBOL("HANDLE-ICP-STOP-SENDING-VALUES-FOR-SENSORS-IN-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_stop_sending_values_for_sensors_in_list,
	    STATIC_FUNCTION(g2int_handle_icp_stop_sending_values_for_sensors_in_list,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_stop_sending_values_for_sensors_in_list,
	    FIX((SI_Long)74L));
    Qg2int_write_icp_do_not_reformat_message_p = 
	    STATIC_SYMBOL("WRITE-ICP-DO-NOT-REFORMAT-MESSAGE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_do_not_reformat_message_p,
	    STATIC_FUNCTION(g2int_write_icp_do_not_reformat_message_p,NIL,
	    FALSE,1,1));
    Qg2int_read_icp_do_not_reformat_message_p = 
	    STATIC_SYMBOL("READ-ICP-DO-NOT-REFORMAT-MESSAGE-P",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_do_not_reformat_message_p,
	    STATIC_FUNCTION(g2int_read_icp_do_not_reformat_message_p,NIL,
	    FALSE,0,0));
    Qg2int_send_icp_write_user_message_string = 
	    STATIC_SYMBOL("SEND-ICP-WRITE-USER-MESSAGE-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_write_user_message_string,
	    STATIC_FUNCTION(g2int_send_icp_write_user_message_string,NIL,
	    FALSE,4,4));
    Qg2int_handle_icp_write_user_message_string = 
	    STATIC_SYMBOL("HANDLE-ICP-WRITE-USER-MESSAGE-STRING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_write_user_message_string,
	    STATIC_FUNCTION(g2int_handle_icp_write_user_message_string,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_write_user_message_string,
	    FIX((SI_Long)65L));
    Qg2int_read_icp_gsi_ds_value = STATIC_SYMBOL("READ-ICP-GSI-DS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_ds_value,
	    STATIC_FUNCTION(g2int_read_icp_gsi_ds_value,NIL,FALSE,0,0));
    Qg2int_write_icp_gsi_ds_value = STATIC_SYMBOL("WRITE-ICP-GSI-DS-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_gsi_ds_value,
	    STATIC_FUNCTION(g2int_write_icp_gsi_ds_value,NIL,FALSE,1,1));
    Qg2int_send_icp_receive_value_for_gsi_sensor = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_value_for_gsi_sensor,
	    STATIC_FUNCTION(g2int_send_icp_receive_value_for_gsi_sensor,
	    NIL,FALSE,3,3));
    Qg2int_handle_icp_receive_value_for_gsi_sensor = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_value_for_gsi_sensor,
	    STATIC_FUNCTION(g2int_handle_icp_receive_value_for_gsi_sensor,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_value_for_gsi_sensor,
	    FIX((SI_Long)68L));
    Qg2int_receive_value_for_gsi_sensor_with_timestamp = 
	    STATIC_SYMBOL("RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP",
	    AB_package);
    Qg2int_read_icp_gsi_values = STATIC_SYMBOL("READ-ICP-GSI-VALUES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_values,
	    STATIC_FUNCTION(g2int_read_icp_gsi_values,NIL,FALSE,0,0));
    Qg2int_send_icp_receive_values_for_gsi_sensors = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-VALUES-FOR-GSI-SENSORS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_values_for_gsi_sensors,
	    STATIC_FUNCTION(g2int_send_icp_receive_values_for_gsi_sensors,
	    NIL,FALSE,1,1));
    Qg2int_handle_icp_receive_values_for_gsi_sensors = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-VALUES-FOR-GSI-SENSORS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_values_for_gsi_sensors,
	    STATIC_FUNCTION(g2int_handle_icp_receive_values_for_gsi_sensors,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_values_for_gsi_sensors,
	    FIX((SI_Long)80L));
    Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_value_for_gsi_sensor_with_timestamp,
	    STATIC_FUNCTION(g2int_send_icp_receive_value_for_gsi_sensor_with_timestamp,
	    NIL,FALSE,4,4));
    Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-VALUE-FOR-GSI-SENSOR-WITH-TIMESTAMP",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp,
	    STATIC_FUNCTION(g2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_value_for_gsi_sensor_with_timestamp,
	    FIX((SI_Long)76L));
    Qg2int_send_icp_receive_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_gsi_sensor_value_vector,
	    STATIC_FUNCTION(g2int_send_icp_receive_gsi_sensor_value_vector,
	    NIL,FALSE,4,4));
    Qg2int_handle_icp_receive_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_gsi_sensor_value_vector,
	    STATIC_FUNCTION(g2int_handle_icp_receive_gsi_sensor_value_vector,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_gsi_sensor_value_vector,
	    FIX((SI_Long)78L));
    Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("SEND-ICP-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_receive_timestamped_gsi_sensor_value_vector,
	    STATIC_FUNCTION(g2int_send_icp_receive_timestamped_gsi_sensor_value_vector,
	    NIL,FALSE,5,5));
    Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector = 
	    STATIC_SYMBOL("HANDLE-ICP-RECEIVE-TIMESTAMPED-GSI-SENSOR-VALUE-VECTOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector,
	    STATIC_FUNCTION(g2int_handle_icp_receive_timestamped_gsi_sensor_value_vector,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_receive_timestamped_gsi_sensor_value_vector,
	    FIX((SI_Long)79L));
}
