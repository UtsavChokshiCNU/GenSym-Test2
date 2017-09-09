/* int2.c
 * Input file:  int2.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int2.h"


Object G2int_localnet_queued_icp_buffer_limit = UNBOUND;

static Object Qg2int_localnet;     /* localnet */

static Object Qg2int_generic;      /* generic */

/* RECEIVE-NEXT-ICP-BUFFER-IF-ANY */
Object g2int_receive_next_icp_buffer_if_any(icp_input_port)
    Object icp_input_port;
{
    Object next_icp_buffer, temp, icp_socket, corresponding_icp_socket;
    Object corresponding_icp_output_port, svref_new_value;

    x_note_fn_call(39,0);
    next_icp_buffer = ISVREF(icp_input_port,(SI_Long)7L);
    if (next_icp_buffer) {
	temp = ISVREF(ISVREF(icp_input_port,(SI_Long)2L),(SI_Long)1L);
	if (EQ(temp,Qg2int_localnet)) {
	    icp_socket = ISVREF(icp_input_port,(SI_Long)2L);
	    corresponding_icp_socket = ISVREF(icp_socket,(SI_Long)42L);
	    corresponding_icp_output_port = corresponding_icp_socket ? 
		    ISVREF(corresponding_icp_socket,(SI_Long)4L) : Nil;
	    if (corresponding_icp_output_port && 
		    ISVREF(corresponding_icp_output_port,(SI_Long)4L))
		g2int_enqueue_write_event(corresponding_icp_socket,
			FIX((SI_Long)0L));
	}
	else if (EQ(temp,Qg2int_generic));
	svref_new_value = ISVREF(next_icp_buffer,(SI_Long)1L);
	SVREF(icp_input_port,FIX((SI_Long)7L)) = svref_new_value;
	SVREF(next_icp_buffer,FIX((SI_Long)1L)) = Nil;
	return VALUES_1(next_icp_buffer);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_icp_socket_index = UNBOUND;

Object G2int_shutdown_interval_for_disallowed_icp_connection_in_seconds = UNBOUND;

Object G2int_shutdown_interval_for_disallowed_icp_connection = UNBOUND;

Object G2int_negative_shutdown_interval_for_disallowed_icp_connection = UNBOUND;

Object G2int_refused_icp_listener_connections = UNBOUND;

static Object Qg2int_g2;           /* g2 */

static Object Qg2int_execute;      /* execute */

/* ITEM-REMOTELY-CALLABLE-P */
Object g2int_item_remotely_callable_p(item)
    Object item;
{
    x_note_fn_call(39,1);
    return g2int_network_access_allowed_p(3,Qg2int_g2,Qg2int_execute,item);
}

static Object Qg2int_ab;           /* ab */

static Object Qg2int_connect;      /* connect */

static Object Qg2int_telewindows;  /* telewindows */

/* ALL-REMOTE-CONNECTIONS-RESTRICTED-P */
Object g2int_all_remote_connections_restricted_p()
{
    Object temp;

    x_note_fn_call(39,2);
    temp = EQ(G2int_current_system_name,Qg2int_ab) &&  
	    !TRUEP(g2int_network_access_allowed_p(2,Qg2int_g2,
	    Qg2int_connect)) ? ( !TRUEP(g2int_network_access_allowed_p(2,
	    Qg2int_telewindows,Qg2int_connect)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* GET-FORBIDDEN-LISTENER-CLIENTS-IF-ANY */
Object g2int_get_forbidden_listener_clients_if_any()
{
    Object forbidden_listener_clients_qm, temp;

    x_note_fn_call(39,3);
    if (EQ(G2int_current_system_name,Qg2int_ab)) {
	forbidden_listener_clients_qm = Nil;
	if ( !TRUEP(g2int_network_access_allowed_p(2,Qg2int_g2,
		Qg2int_connect)))
	    forbidden_listener_clients_qm = g2int_gensym_cons_1(Qg2int_g2,
		    forbidden_listener_clients_qm);
	if ( !TRUEP(g2int_network_access_allowed_p(2,Qg2int_telewindows,
		Qg2int_connect)))
	    forbidden_listener_clients_qm = 
		    g2int_gensym_cons_1(Qg2int_telewindows,
		    forbidden_listener_clients_qm);
	temp = forbidden_listener_clients_qm;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2int_inform;       /* inform */

/* REMOTE-INFORM-RESTRICTED-P */
Object g2int_remote_inform_restricted_p()
{
    x_note_fn_call(39,4);
    return VALUES_1( !TRUEP(g2int_network_access_allowed_p(2,Qg2int_g2,
	    Qg2int_inform)) ? T : Nil);
}

/* PRINT-ICP-BUFFER-CONTENTS */
Object g2int_print_icp_buffer_contents(buffer)
    Object buffer;
{
    Object bv, array;
    SI_Long n_1, start, end, count_1, i, ab_loop_bind_, ab_loop_step_by_, j;
    SI_Long temp, ab_loop_bind__1, icp_position, position_1;

    x_note_fn_call(39,5);
    n_1 = (SI_Long)16L;
    bv = ISVREF(buffer,(SI_Long)4L);
    start = IFIX(ISVREF(buffer,(SI_Long)2L)) >>  -  - (SI_Long)1L;
    end = IFIX(ISVREF(buffer,(SI_Long)3L)) >>  -  - (SI_Long)1L;
    count_1 = end - start;
    i = (SI_Long)0L;
    ab_loop_bind_ = count_1;
    ab_loop_step_by_ = n_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    terpri(_);
    j = i;
    temp = i + n_1;
    ab_loop_bind__1 = MIN(count_1,temp);
  next_loop_1:
    if (j >= ab_loop_bind__1)
	goto end_loop_1;
    array = bv;
    icp_position = j + start;
    position_1 = icp_position + icp_position;
    format((SI_Long)3L,T," ~D",FIX((UBYTE_8_ISAREF_1(array,position_1) << 
	    (SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + (SI_Long)1L)));
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    i = i + ab_loop_step_by_;
    goto next_loop;
  end_loop:;
    return terpri(_);
}

/* PRINT-ICP-BUFFER-BYTE-CONTENTS */
Object g2int_print_icp_buffer_byte_contents(buffer)
    Object buffer;
{
    Object bv, start, end, count_1;
    SI_Long n_1, i, ab_loop_bind_, ab_loop_step_by_, j, temp, ab_loop_bind__1;

    x_note_fn_call(39,6);
    n_1 = (SI_Long)16L;
    bv = ISVREF(buffer,(SI_Long)4L);
    start = ISVREF(buffer,(SI_Long)2L);
    end = ISVREF(buffer,(SI_Long)3L);
    count_1 = FIXNUM_MINUS(end,start);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
    ab_loop_step_by_ = n_1;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    terpri(_);
    j = i;
    temp = i + n_1;
    ab_loop_bind__1 = MIN(IFIX(count_1),temp);
  next_loop_1:
    if (j >= ab_loop_bind__1)
	goto end_loop_1;
    format((SI_Long)3L,T," ~D",FIX(UBYTE_8_ISAREF_1(bv,j + IFIX(start))));
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    i = i + ab_loop_step_by_;
    goto next_loop;
  end_loop:;
    return terpri(_);
}

/* RESET-COUNTERS-FOR-ALL-ICP-SOCKETS */
Object g2int_reset_counters_for_all_icp_sockets()
{
    Object icp_socket, ab_loop_list_;

    x_note_fn_call(39,7);
    icp_socket = Nil;
    ab_loop_list_ = G2int_active_icp_sockets;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    icp_socket = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    SVREF(icp_socket,FIX((SI_Long)7L)) = Nil;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qg2int_gsi;          /* gsi */

static Object Kfnord;              /* :fnord */

/* RESTORE-ICP-INDEX-TO-ORIGINAL-STATE */
Object g2int_restore_icp_index_to_original_state()
{
    Object temp, icp_socket_index_new_value;

    x_note_fn_call(39,8);
    if (EQ(G2int_current_system_name,Qg2int_telewindows))
	return VALUES_1(Nil);
    else if (EQ(G2int_current_system_name,Qg2int_gsi))
	return VALUES_1(Nil);
    else if (IFIX(G2int_icp_socket_index) == (SI_Long)1000L) {
	G2int_icp_socket_index = FIX((SI_Long)0L);
	temp = ISVREF(G2int_saved_initial_status,(SI_Long)1L);
	if (FOURTH(temp))
	    return g2int_replace_format_using_equivalent_font(Kfnord);
	else
	    return VALUES_1(Nil);
    }
    else {
	icp_socket_index_new_value = FIXNUM_ADD1(G2int_icp_socket_index);
	G2int_icp_socket_index = icp_socket_index_new_value;
	return VALUES_1(G2int_icp_socket_index);
    }
}

/* ICP-OUTPUT-PORT-FLUSHED? */
Object g2int_icp_output_port_flushedqm(icp_output_port)
    Object icp_output_port;
{
    x_note_fn_call(39,9);
    if (EQ(ISVREF(icp_output_port,(SI_Long)12L),ISVREF(icp_output_port,
	    (SI_Long)13L)))
	return VALUES_1( !TRUEP(ISVREF(icp_output_port,(SI_Long)4L)) ? T : 
		Nil);
    else
	return VALUES_1(Nil);
}

Object G2int_inhibit_icp_message_processing_enabled = UNBOUND;

Object G2int_inhibit_icp_message_processing = UNBOUND;

static Object Qg2int_gensym;       /* gensym */

/* SCHEDULE-PROCESSING-FOR-INHIBITED-MESSAGES */
Object g2int_schedule_processing_for_inhibited_messages()
{
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, icp_socket, gensym_pop_store;
    Object cons_1, next_cons, cdr_new_value;
    Declare_special(1);

    x_note_fn_call(39,10);
    if (G2int_icp_sockets_waiting_for_icp_message_processing) {
	if ( !TRUEP(G2int_inhibit_icp_message_processing)) {
	    G2int_icp_sockets_waiting_for_icp_message_processing = 
		    nreverse(G2int_icp_sockets_waiting_for_icp_message_processing);
	    outer_with_icp_buffer_coelescing_scope_qm = 
		    G2int_with_icp_buffer_coelescing_scopeqm;
	    with_icp_buffer_coelescing_scope_qm = T;
	    PUSH_SPECIAL(G2int_with_icp_buffer_coelescing_scopeqm,with_icp_buffer_coelescing_scope_qm,
		    0);
	      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
		  if (G2int_icp_output_ports_to_flush)
		      g2int_flush_icp_output_ports();
	      }
	      icp_socket = Nil;
	    next_loop:
	      if ( 
		      !TRUEP(G2int_icp_sockets_waiting_for_icp_message_processing))
		  goto end_loop;
	      gensym_pop_store = Nil;
	      cons_1 = G2int_icp_sockets_waiting_for_icp_message_processing;
	      if (cons_1) {
		  gensym_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qg2int_gensym);
		  cdr_new_value = G2int_available_gensym_conses;
		  M_CDR(cons_1) = cdr_new_value;
		  G2int_available_gensym_conses = cons_1;
	      }
	      else
		  next_cons = Nil;
	      G2int_icp_sockets_waiting_for_icp_message_processing = next_cons;
	      icp_socket = gensym_pop_store;
	      if (icp_socket)
		  g2int_call_or_schedule_handle_queued_icp_messages(icp_socket,
			  T);
	      goto next_loop;
	    end_loop:;
	      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
		  if (G2int_icp_output_ports_to_flush)
		      g2int_flush_icp_output_ports();
	      }
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

/* ICP-SOCKET-IS-FOR-UI-CLIENT-INTERFACE-P */
Object g2int_icp_socket_is_for_ui_client_interface_p(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(39,11);
    return VALUES_1(Nil);
}

Object G2int_handle_ui_client_interface_messages_immediately_p = UNBOUND;

Object G2int_abort_for_icp_catcherqm = UNBOUND;

static Object Qg2int_handle_icp_messages;  /* handle-icp-messages */

static Object Qg2int_handle_queued_icp_messages_task;  /* handle-queued-icp-messages-task */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* CALL-OR-SCHEDULE-HANDLE-QUEUED-ICP-MESSAGES */
Object g2int_call_or_schedule_handle_queued_icp_messages(icp_socket,
	    force_schedule_p)
    Object icp_socket, force_schedule_p;
{
    Object abort_for_icp_catcher_qm, more_to_do_immediately_qm;
    Object future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_11, schedule_task_qm;
    Object old_structure_being_reclaimed, temp;
    Object def_structure_schedule_task_variable, task;
    Object current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11, ctask, p, v, q;
    Object gensymed_symbol_2, def_structure_queue_element_variable;
    Object gensymed_symbol_3;
    char svref_new_value, g2_p;
    double gensymed_symbol, gensymed_symbol_1;
    double future_task_schedule_modify_arg_3, aref_new_value;
    Declare_catch(1);
    Declare_special(1);

    x_note_fn_call(39,12);
    if (G2int_inhibit_icp_message_processing) {
	if ( !TRUEP(g2int_memq_function(icp_socket,
		G2int_icp_sockets_waiting_for_icp_message_processing)))
	    G2int_icp_sockets_waiting_for_icp_message_processing = 
		    g2int_gensym_cons_1(icp_socket,
		    G2int_icp_sockets_waiting_for_icp_message_processing);
	return VALUES_1(Nil);
    }
    else if (EQ(ISVREF(icp_socket,(SI_Long)25L),Qg2int_telewindows) || 
	    G2int_handle_ui_client_interface_messages_immediately_p && ( 
	    !TRUEP(ISVREF(icp_socket,(SI_Long)25L)) || 
	    g2int_icp_socket_is_for_ui_client_interface_p(icp_socket)) || 
	    G2int_during_ffi_callqm) {
	if (PUSH_CATCH(Qg2int_handle_icp_messages,0)) {
	    abort_for_icp_catcher_qm = Qg2int_handle_icp_messages;
	    PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,
		    0);
	      more_to_do_immediately_qm = 
		      g2int_handle_queued_icp_messages(icp_socket);
	    POP_SPECIAL();
	}
	else
	    more_to_do_immediately_qm = CATCH_VALUES();
	POP_CATCH(0);
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		G2int_icp_connection_closed)) {
	    g2int_finalize_and_reclaim_icp_socket(icp_socket);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(more_to_do_immediately_qm);
    }
    else {
	gensymed_symbol = 
		g2int_icp_socket_is_for_ui_client_interface_p(icp_socket) ?
		 0.1 : 0.2;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(G2int_current_real_time,
		(SI_Long)0L);
	future_task_schedule_modify_arg_3 = gensymed_symbol + 
		gensymed_symbol_1;
	future_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_handle_queued_icp_messages_task);
	future_task_schedule_modify_arg_11 = icp_socket;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)34L);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,G2int_current_schedule_task))
		G2int_current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = schedule_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    temp = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	def_structure_schedule_task_variable = 
		G2int_chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    G2int_chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    g2int_make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,future_task_schedule_modify_arg_3);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
	SVREF(task,FIX((SI_Long)4L)) = G2int_highest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_handle_queued_icp_messages_task;
	SVREF(task,FIX((SI_Long)8L)) = future_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)11L)) = future_task_schedule_modify_arg_11;
	g2int_future_task_schedule_2(task);
	SVREF(icp_socket,FIX((SI_Long)34L)) = task;
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_handle_queued_icp_messages_task);
	current_task_schedule_modify_arg_11 = icp_socket;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)35L);
	if (schedule_task_qm) {
	    if (EQ(schedule_task_qm,G2int_current_schedule_task))
		G2int_current_schedule_task = Nil;
	    if (ISVREF(schedule_task_qm,(SI_Long)6L))
		g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	    inline_note_reclaim_cons(schedule_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = schedule_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    temp = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	def_structure_schedule_task_variable = 
		G2int_chain_of_available_schedule_tasks;
	if (def_structure_schedule_task_variable) {
	    G2int_chain_of_available_schedule_tasks = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    g2int_make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	SVREF(task,FIX((SI_Long)4L)) = G2int_lowest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_handle_queued_icp_messages_task;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol_2 = ISVREF(q,(SI_Long)1L);
	def_structure_queue_element_variable = 
		G2int_chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    G2int_chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    g2int_make_permanent_queue_element_structure_internal();
	inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = q;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
		gensymed_symbol_2;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_3 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol_2,FIX((SI_Long)0L)) = gensymed_symbol_3;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_3;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_3;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)35L)) = task;
	return VALUES_1(Nil);
    }
}

/* HANDLE-QUEUED-ICP-MESSAGES-TASK */
Object g2int_handle_queued_icp_messages_task(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm;
    double gensymed_symbol_1;
    Declare_special(1);

    x_note_fn_call(39,13);
    gensymed_symbol = Nil;
    gensymed_symbol_1 = 0.0;
    gensymed_symbol_1 = 0.0;
    outer_with_icp_buffer_coelescing_scope_qm = 
	    G2int_with_icp_buffer_coelescing_scopeqm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL(G2int_with_icp_buffer_coelescing_scopeqm,with_icp_buffer_coelescing_scope_qm,
	    0);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
      if (g2int_handle_queued_icp_messages(icp_socket))
	  g2int_continue_reading_from_icp_socket(icp_socket);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-QUEUED-ICP-MESSAGES */
Object g2int_handle_queued_icp_messages(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;
    Object more_to_do_immediately_qm, abort_for_icp_catcher_qm, icp_input_port;
    Object did_something_qm, time_slice_expired_qm, can_process_messages_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,14);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)34L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)34L)) = svref_new_value;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)35L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(icp_socket,FIX((SI_Long)35L)) = svref_new_value;
    if (G2int_inhibit_icp_message_processing) {
	if ( !TRUEP(g2int_memq_function(icp_socket,
		G2int_icp_sockets_waiting_for_icp_message_processing)))
	    G2int_icp_sockets_waiting_for_icp_message_processing = 
		    g2int_gensym_cons_1(icp_socket,
		    G2int_icp_sockets_waiting_for_icp_message_processing);
	return VALUES_1(Nil);
    }
    G2int_icp_socket_for_handle_icp_messages = icp_socket;
    more_to_do_immediately_qm = Nil;
    abort_for_icp_catcher_qm = Qg2int_handle_icp_messages;
    PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
      icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
      did_something_qm = Nil;
      time_slice_expired_qm = Nil;
      can_process_messages_qm = Nil;
    next_loop:
      did_something_qm = 
	      g2int_process_next_icp_message_group_if_ready(icp_input_port);
      time_slice_expired_qm =  !TRUEP(G2int_during_ffi_callqm) ? 
	      g2int_time_slice_expired_p() : Qnil;
      can_process_messages_qm = 
	      g2int_icp_connection_can_process_messagesqm(icp_socket);
      if (time_slice_expired_qm ||  !TRUEP(did_something_qm) ||  
	      !TRUEP(can_process_messages_qm))
	  goto end_loop;
      goto next_loop;
    end_loop:
      if (can_process_messages_qm)
	  more_to_do_immediately_qm = did_something_qm ? 
		  g2int_call_or_schedule_handle_queued_icp_messages(icp_socket,
		  T) : T;
      if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	      G2int_icp_connection_closed))
	  g2int_finalize_and_reclaim_icp_socket(icp_socket);
      result = VALUES_1(more_to_do_immediately_qm);
    POP_SPECIAL();
    return result;
}

static Object Qg2int_broken_while_transmitting;  /* broken-while-transmitting */

/* TRANSMIT-NEXT-NETWORK-ICP-BUFFER */
Object g2int_transmit_next_network_icp_buffer(icp_output_port)
    Object icp_output_port;
{
    Object icp_socket, icp_buffer_queue_head, icp_buffer;
    Object character_to_start_at, characters_to_send, temp;
    SI_Long characters_sent, svref_new_value;

    x_note_fn_call(39,15);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    icp_buffer_queue_head = ISVREF(icp_output_port,(SI_Long)12L);
    icp_buffer = ISVREF(icp_buffer_queue_head,(SI_Long)1L);
    character_to_start_at = ISVREF(icp_buffer,(SI_Long)2L);
    characters_to_send = FIXNUM_MINUS(ISVREF(icp_buffer,(SI_Long)3L),
	    character_to_start_at);
    characters_sent = g2ext_network_write(IFIX(ISVREF(icp_output_port,
	    (SI_Long)1L)),UBYTE_16_SARRAY_TO_USHORT_PTR(ISVREF(icp_buffer,
	    (SI_Long)4L)),IFIX(character_to_start_at),
	    IFIX(characters_to_send));
    if (characters_sent == IFIX(characters_to_send)) {
	g2int_reclaim_icp_buffer(icp_buffer_queue_head);
	SVREF(icp_output_port,FIX((SI_Long)12L)) = icp_buffer;
	temp = T;
    }
    else if (characters_sent >= (SI_Long)0L) {
	SVREF(icp_output_port,FIX((SI_Long)4L)) = T;
	g2int_execute_icp_write_callbacks(icp_socket,Nil);
	svref_new_value = IFIX(character_to_start_at) + characters_sent;
	ISVREF(icp_buffer,(SI_Long)2L) = FIX(svref_new_value);
	SVREF(icp_output_port,FIX((SI_Long)7L)) = icp_buffer;
	temp = Nil;
    }
    else {
	g2int_shutdown_icp_socket_connection(2,ISVREF(icp_output_port,
		(SI_Long)2L),Qg2int_broken_while_transmitting);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* TRANSMIT-NEXT-LOCALNET-ICP-BUFFER */
Object g2int_transmit_next_localnet_icp_buffer(icp_output_port)
    Object icp_output_port;
{
    Object icp_socket, icp_buffer_queue_head, icp_buffer;
    Object corresponding_icp_socket, corresponding_icp_input_port;
    Object buffer_chain_copy, buffer_for_callback, last_buffer, next_buffer;

    x_note_fn_call(39,16);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    icp_buffer_queue_head = ISVREF(icp_output_port,(SI_Long)12L);
    icp_buffer = ISVREF(icp_buffer_queue_head,(SI_Long)1L);
    corresponding_icp_socket = ISVREF(icp_socket,(SI_Long)42L);
    corresponding_icp_input_port = ISVREF(corresponding_icp_socket,
	    (SI_Long)3L);
    buffer_chain_copy = g2int_copy_icp_buffer_chain(icp_buffer);
    buffer_for_callback = ISVREF(corresponding_icp_input_port,(SI_Long)7L);
    if ( !TRUEP(buffer_for_callback))
	SVREF(corresponding_icp_input_port,FIX((SI_Long)7L)) = 
		buffer_chain_copy;
    else {
	last_buffer = buffer_for_callback;
	next_buffer = Nil;
      next_loop:
	next_buffer = ISVREF(last_buffer,(SI_Long)1L);
	if ( !TRUEP(next_buffer))
	    goto end_loop;
	last_buffer = next_buffer;
	goto next_loop;
      end_loop:
	SVREF(last_buffer,FIX((SI_Long)1L)) = buffer_chain_copy;
    }
    last_buffer = icp_buffer;
    next_buffer = Nil;
  next_loop_1:
    if ( !TRUEP(last_buffer))
	goto end_loop_1;
    next_buffer = ISVREF(last_buffer,(SI_Long)1L);
    g2int_reclaim_icp_buffer(icp_buffer_queue_head);
    icp_buffer_queue_head = last_buffer;
    last_buffer = next_buffer;
    goto next_loop_1;
  end_loop_1:;
    SVREF(icp_output_port,FIX((SI_Long)12L)) = icp_buffer_queue_head;
    if (ISVREF(corresponding_icp_input_port,(SI_Long)4L))
	g2int_enqueue_read_event(corresponding_icp_socket,FIX((SI_Long)0L));
    return VALUES_1(T);
}

/* TRANSMIT-ICP-OUTPUT-IF-READY */
Object g2int_transmit_icp_output_if_ready(icp_output_port,
	    flush_partial_buffers)
    Object icp_output_port, flush_partial_buffers;
{
    Object icp_socket, type_of_icp_connection, tail, head;
    char localnetp;

    x_note_fn_call(39,17);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    type_of_icp_connection = ISVREF(icp_socket,(SI_Long)1L);
    localnetp = EQ(type_of_icp_connection,Qg2int_localnet);
    if (localnetp &&  !TRUEP(ISVREF(icp_socket,(SI_Long)42L))) {
	if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		G2int_icp_connection_closed))
	    g2int_shutdown_icp_socket_connection(2,icp_socket,
		    Qg2int_broken_while_transmitting);
	return VALUES_1(Nil);
    }
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running) &&  
	    !TRUEP(ISVREF(icp_output_port,(SI_Long)4L))) {
	tail = ISVREF(icp_output_port,(SI_Long)13L);
	head = Nil;
      next_loop:
	head = ISVREF(icp_output_port,(SI_Long)12L);
	if (EQ(head,tail) ||  !TRUEP(flush_partial_buffers) && 
		EQ(ISVREF(head,(SI_Long)1L),tail) && IFIX(ISVREF(tail,
		(SI_Long)3L)) < (SI_Long)4096L)
	    goto end_loop;
	if ( !(localnetp ? 
		TRUEP(g2int_transmit_next_localnet_icp_buffer(icp_output_port)) 
		: 
		TRUEP(g2int_transmit_next_network_icp_buffer(icp_output_port))))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_end_of_message_group;  /* end-of-message-group */

/* ENQUEUE-NEXT-ICP-BUFFER-IF-ANY */
Object g2int_enqueue_next_icp_buffer_if_any(icp_input_port)
    Object icp_input_port;
{
    Object icp_buffer_qm, icp_buffer_start_icp_offset, tail, svref_new_value_1;
    Object contains_end_of_message_group_qm;
    Object number_of_icp_bytes_left_in_buffer;
    Object number_of_icp_bytes_still_needed_for_message_series;
    Object index_of_icp_byte_position, array, current_icp_port, temp;
    SI_Long incff_1_arg, svref_new_value, icp_position, position_1;
    SI_Long message_series_byte_count;
    Declare_special(1);

    x_note_fn_call(39,18);
    icp_buffer_qm = g2int_receive_next_icp_buffer_if_any(icp_input_port);
    icp_buffer_start_icp_offset = FIX((SI_Long)0L);
    if (icp_buffer_qm) {
	tail = ISVREF(icp_input_port,(SI_Long)13L);
	if (EQ(ISVREF(tail,(SI_Long)4L),ISVREF(icp_buffer_qm,(SI_Long)4L))) {
	    if (EQ(ISVREF(icp_input_port,(SI_Long)12L),tail)) {
		incff_1_arg = (IFIX(ISVREF(icp_buffer_qm,(SI_Long)3L)) >>  
			-  - (SI_Long)1L) - (IFIX(ISVREF(icp_buffer_qm,
			(SI_Long)2L)) >>  -  - (SI_Long)1L);
		svref_new_value = IFIX(ISVREF(icp_input_port,
			(SI_Long)17L)) + incff_1_arg;
		ISVREF(icp_input_port,(SI_Long)17L) = FIX(svref_new_value);
	    }
	    icp_buffer_start_icp_offset = FIX((IFIX(ISVREF(icp_buffer_qm,
		    (SI_Long)2L)) >>  -  - (SI_Long)1L) - 
		    (IFIX(ISVREF(tail,(SI_Long)2L)) >>  -  - (SI_Long)1L));
	    svref_new_value_1 = ISVREF(icp_buffer_qm,(SI_Long)3L);
	    SVREF(tail,FIX((SI_Long)3L)) = svref_new_value_1;
	    g2int_reclaim_icp_buffer(icp_buffer_qm);
	    icp_buffer_qm = tail;
	}
	else {
	    SVREF(tail,FIX((SI_Long)1L)) = icp_buffer_qm;
	    SVREF(icp_input_port,FIX((SI_Long)13L)) = icp_buffer_qm;
	}
	contains_end_of_message_group_qm = Nil;
	number_of_icp_bytes_left_in_buffer = 
		FIX((IFIX(ISVREF(icp_buffer_qm,(SI_Long)3L)) >>  -  - 
		(SI_Long)1L) - (IFIX(ISVREF(icp_buffer_qm,(SI_Long)2L)) >> 
		 -  - (SI_Long)1L) - IFIX(icp_buffer_start_icp_offset));
	number_of_icp_bytes_still_needed_for_message_series = 
		ISVREF(icp_input_port,(SI_Long)14L);
	index_of_icp_byte_position = 
		FIX(IFIX(number_of_icp_bytes_still_needed_for_message_series) 
		+ (IFIX(ISVREF(icp_buffer_qm,(SI_Long)2L)) >>  -  - 
		(SI_Long)1L) + IFIX(icp_buffer_start_icp_offset));
      next_loop:
	if ( 
		!FIXNUM_LT(number_of_icp_bytes_still_needed_for_message_series,
		number_of_icp_bytes_left_in_buffer))
	    goto end_loop;
	number_of_icp_bytes_left_in_buffer = 
		FIXNUM_MINUS(number_of_icp_bytes_left_in_buffer,
		number_of_icp_bytes_still_needed_for_message_series);
	array = ISVREF(icp_buffer_qm,(SI_Long)4L);
	icp_position = IFIX(index_of_icp_byte_position);
	position_1 = icp_position + icp_position;
	message_series_byte_count = (UBYTE_8_ISAREF_1(array,position_1) << 
		(SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + 
		(SI_Long)1L);
	if (message_series_byte_count == (SI_Long)1L) {
	    contains_end_of_message_group_qm = T;
	    SVREF(icp_input_port,FIX((SI_Long)15L)) = icp_buffer_qm;
	    SVREF(icp_input_port,FIX((SI_Long)16L)) = 
		    index_of_icp_byte_position;
	}
	else if (message_series_byte_count == (SI_Long)0L) {
	    current_icp_port = icp_input_port;
	    PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,0);
	      g2int_icp_out_of_synch(1,FIX((SI_Long)1L));
	    POP_SPECIAL();
	}
	number_of_icp_bytes_still_needed_for_message_series = 
		FIX(message_series_byte_count);
	index_of_icp_byte_position = FIXNUM_ADD(index_of_icp_byte_position,
		number_of_icp_bytes_still_needed_for_message_series);
	goto next_loop;
      end_loop:
	svref_new_value_1 = 
		FIXNUM_MINUS(number_of_icp_bytes_still_needed_for_message_series,
		number_of_icp_bytes_left_in_buffer);
	SVREF(icp_input_port,FIX((SI_Long)14L)) = svref_new_value_1;
	temp = contains_end_of_message_group_qm ? 
		Qg2int_end_of_message_group : T;
	goto end;
	temp = Qnil;
      end:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_priority_of_icp_message_service = UNBOUND;

Object G2int_priority_of_rpc_service = UNBOUND;

Object G2int_priority_of_icp_control_messages = UNBOUND;

Object G2int_resumable_priority_of_gsi_data_service = UNBOUND;

Object G2int_resumable_priority_of_gsi_rpc_service = UNBOUND;

Object G2int_current_icp_buffer = UNBOUND;

Object G2int_current_read_icp_byte_position = UNBOUND;

Object G2int_current_write_icp_byte_position = UNBOUND;

Object G2int_writing_resumable_icp_messages_p = UNBOUND;

Object G2int_icp_error_suspend_p = UNBOUND;

Object G2int_current_resumable_icp_read_task = UNBOUND;

Object G2int_resumable_icp_read_ignore_p = UNBOUND;

Object G2int_number_of_icp_bytes_left_in_current_buffer = UNBOUND;

/* READ-ICP-SKIP-TO-MESSAGE-GROUP-END */
Object g2int_read_icp_skip_to_message_group_end()
{
    Object current_resumable_icp_read_task, temp_1;
    SI_Long length_1, incff_1_arg, temp_2, decff_1_arg;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,19);
    current_resumable_icp_read_task = Nil;
    PUSH_SPECIAL(G2int_current_resumable_icp_read_task,current_resumable_icp_read_task,
	    0);
    next_loop:
      length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
      temp = (SI_Long)0L < length_1;
      if (temp);
      else {
	  temp_1 = g2int_ensure_next_icp_message_series();
	  length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	  temp = TRUEP(temp_1);
      }
      if ( !temp) {
	  g2int_process_end_of_message_group(T,Nil);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_icp_skip_to_message_group_end;
      }
      else {
	  incff_1_arg = length_1;
	  temp_2 = IFIX(G2int_current_read_icp_byte_position) + incff_1_arg;
	  G2int_current_read_icp_byte_position = FIX(temp_2);
	  decff_1_arg = length_1;
	  temp_2 = IFIX(G2int_number_of_icp_bytes_ready_to_read) - decff_1_arg;
	  G2int_number_of_icp_bytes_ready_to_read = FIX(temp_2);
      }
      goto next_loop;
    end_loop:
      temp_1 = Qnil;
    POP_SPECIAL();
    result = VALUES_1(temp_1);
  end_read_icp_skip_to_message_group_end:
    return result;
}

/* READ-ICP-BYTE-OR-MESSAGE-GROUP-END */
Object g2int_read_icp_byte_or_message_group_end()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(39,20);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = g2int_process_end_of_message_group(T,T);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	G2int_current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	G2int_number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* READ-ICP-BYTE-IF-ANY */
Object g2int_read_icp_byte_if_any()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(39,21);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = g2int_process_end_of_message_group(T,Nil);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	G2int_current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	G2int_number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* READ-ICP-BYTE */
Object g2int_read_icp_byte()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(39,22);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = g2int_process_end_of_message_group(Nil,Nil);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	G2int_current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	G2int_number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* PEEK-ICP-BYTE-IF-ANY */
Object g2int_peek_icp_byte_if_any()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(39,23);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = g2int_process_end_of_message_group(T,Nil);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* PEEK-ICP-BYTE */
Object g2int_peek_icp_byte()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(39,24);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = g2int_process_end_of_message_group(Nil,Nil);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* GET-ICP-READ-BUFFER */
Object g2int_get_icp_read_buffer()
{
    Object temp_1, array, start;
    SI_Long length_1;
    char temp;

    x_note_fn_call(39,25);
    length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = g2int_ensure_next_icp_message_series();
	length_1 = IFIX(G2int_number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	return VALUES_1(Nil);
    else {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	return VALUES_3(array,start,FIX(length_1));
    }
}

/* ENSURE-NEXT-ICP-MESSAGE-SERIES */
Object g2int_ensure_next_icp_message_series()
{
    Object array, temp, number_of_icp_bytes_left_in_current_buffer;
    Object svref_arg_1, svref_new_value;
    SI_Long icp_position, position_1;
    Declare_special(1);

    x_note_fn_call(39,26);
    g2int_ensure_next_icp_byte();
    if (IFIX(G2int_number_of_icp_bytes_left_in_message_series) == 
		(SI_Long)0L) {
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	icp_position = IFIX(FIXNUM_ADD1(G2int_current_read_icp_byte_position));
	position_1 = icp_position + icp_position;
	temp = (SI_Long)1L == (UBYTE_8_ISAREF_1(array,position_1) << 
		(SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + 
		(SI_Long)1L) ? Nil : g2int_start_next_message_series();
    }
    else {
	number_of_icp_bytes_left_in_current_buffer = 
		ISVREF(G2int_current_icp_port,(SI_Long)17L);
	PUSH_SPECIAL(G2int_number_of_icp_bytes_left_in_current_buffer,number_of_icp_bytes_left_in_current_buffer,
		0);
	  G2int_number_of_icp_bytes_ready_to_read = 
		  FIXNUM_MIN(G2int_number_of_icp_bytes_left_in_current_buffer,
		  G2int_number_of_icp_bytes_left_in_message_series);
	  G2int_number_of_icp_bytes_left_in_message_series = 
		  FIXNUM_MINUS(G2int_number_of_icp_bytes_left_in_message_series,
		  G2int_number_of_icp_bytes_ready_to_read);
	  svref_arg_1 = G2int_current_icp_port;
	  svref_new_value = 
		  FIXNUM_MINUS(G2int_number_of_icp_bytes_left_in_current_buffer,
		  G2int_number_of_icp_bytes_ready_to_read);
	  SVREF(svref_arg_1,FIX((SI_Long)17L)) = svref_new_value;
	  temp = T;
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

/* ENSURE-NEXT-ICP-BYTE */
Object g2int_ensure_next_icp_byte()
{
    Object icp_buffer_queue_head, next_head, svref_arg_1, temp;
    SI_Long svref_new_value;

    x_note_fn_call(39,27);
    if ((SI_Long)0L == IFIX(ISVREF(G2int_current_icp_port,(SI_Long)17L))) {
	icp_buffer_queue_head = ISVREF(G2int_current_icp_port,(SI_Long)12L);
	next_head = ISVREF(icp_buffer_queue_head,(SI_Long)1L);
	G2int_current_icp_buffer = next_head;
	if ( !TRUEP(G2int_current_icp_buffer))
	    g2int_icp_out_of_synch(1,FIX((SI_Long)4L));
	svref_arg_1 = G2int_current_icp_port;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = next_head;
	g2int_reclaim_icp_buffer(icp_buffer_queue_head);
	svref_arg_1 = G2int_current_icp_port;
	svref_new_value = (IFIX(ISVREF(G2int_current_icp_buffer,
		(SI_Long)3L)) >>  -  - (SI_Long)1L) - 
		(IFIX(ISVREF(G2int_current_icp_buffer,(SI_Long)2L)) >>  -  
		- (SI_Long)1L);
	ISVREF(svref_arg_1,(SI_Long)17L) = FIX(svref_new_value);
	G2int_current_read_icp_byte_position = FIX((SI_Long)-1L);
	temp = G2int_current_read_icp_byte_position;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant;     /* "[reading message series]" */

static Object Qg2int_message_series;  /* message-series */

/* START-NEXT-MESSAGE-SERIES */
Object g2int_start_next_message_series()
{
    Object temp, array, number_of_icp_bytes_left_in_current_buffer, temp_1;
    Object decff_1_arg, svref_new_value;
    SI_Long icp_position, position_1;
    Declare_special(1);

    x_note_fn_call(39,28);
    temp = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
    G2int_current_read_icp_byte_position = temp;
    array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
    icp_position = IFIX(G2int_current_read_icp_byte_position);
    position_1 = icp_position + icp_position;
    G2int_number_of_icp_bytes_left_in_message_series = 
	    FIXNUM_SUB1(FIX((UBYTE_8_ISAREF_1(array,position_1) << 
	    (SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + (SI_Long)1L)));
    temp = G2int_current_icp_port;
    number_of_icp_bytes_left_in_current_buffer = FIXNUM_SUB1(ISVREF(temp,
	    (SI_Long)17L));
    SVREF(temp,FIX((SI_Long)17L)) = number_of_icp_bytes_left_in_current_buffer;
    PUSH_SPECIAL(G2int_number_of_icp_bytes_left_in_current_buffer,number_of_icp_bytes_left_in_current_buffer,
	    0);
      if (IFIX(G2int_number_of_icp_bytes_left_in_current_buffer) == 
	      (SI_Long)0L)
	  temp_1 = g2int_ensure_next_icp_message_series();
      else {
	  if (G2int_icp_read_trace_cutoff_levelqm && 
		  (EQ(G2int_icp_read_trace_cutoff_levelqm,T) || 
		  IFIX(G2int_icp_read_trace_cutoff_levelqm) >= (SI_Long)1L))
	      g2int_emit_icp_read_trace(Nil,FIX((SI_Long)0L),
		      FIXNUM_ADD1(G2int_number_of_icp_bytes_left_in_message_series),
		      string_constant,Nil,Qg2int_message_series,Nil,Nil,T,Nil);
	  G2int_number_of_icp_bytes_ready_to_read = 
		  FIXNUM_MIN(G2int_number_of_icp_bytes_left_in_current_buffer,
		  G2int_number_of_icp_bytes_left_in_message_series);
	  decff_1_arg = G2int_number_of_icp_bytes_ready_to_read;
	  temp = 
		  FIXNUM_MINUS(G2int_number_of_icp_bytes_left_in_message_series,
		  decff_1_arg);
	  G2int_number_of_icp_bytes_left_in_message_series = temp;
	  temp = G2int_current_icp_port;
	  decff_1_arg = G2int_number_of_icp_bytes_ready_to_read;
	  svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)17L),
		  decff_1_arg);
	  SVREF(temp,FIX((SI_Long)17L)) = svref_new_value;
	  temp_1 = T;
      }
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* READ-ICP-SUSPEND */
Object g2int_read_icp_suspend()
{
    Object temp;

    x_note_fn_call(39,29);
    if (g2int_current_icp_read_task_resumable_p()) {
	G2int_starresumable_icp_statestar = Nil;
	temp = G2int_icp_suspend;
    }
    else
	temp = g2int_icp_out_of_synch(1,FIX((SI_Long)5L));
    return VALUES_1(temp);
}

static Object string_constant_1;   /* "read \"end-of-message-group\" message series" */

/* PROCESS-END-OF-MESSAGE-GROUP */
Object g2int_process_end_of_message_group(ok_if_none_qm,
	    read_message_group_end_p)
    Object ok_if_none_qm, read_message_group_end_p;
{
    Object temp, svref_new_value;

    x_note_fn_call(39,30);
    if ( !TRUEP(read_message_group_end_p) && 
	    g2int_current_icp_read_task_resumable_p()) {
	G2int_starresumable_icp_statestar = Nil;
	return VALUES_1(G2int_icp_suspend);
    }
    if ( !TRUEP(ok_if_none_qm))
	g2int_icp_out_of_synch(1,FIX((SI_Long)5L));
    if (read_message_group_end_p) {
	temp = FIXNUM_ADD1(G2int_current_read_icp_byte_position);
	G2int_current_read_icp_byte_position = temp;
	temp = G2int_current_icp_port;
	svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)17L));
	SVREF(temp,FIX((SI_Long)17L)) = svref_new_value;
    }
    if (G2int_icp_read_trace_cutoff_levelqm && 
	    (EQ(G2int_icp_read_trace_cutoff_levelqm,T) || 
	    IFIX(G2int_icp_read_trace_cutoff_levelqm) >= (SI_Long)1L))
	g2int_emit_icp_read_trace(Nil,FIX((SI_Long)0L),FIX((SI_Long)1L),
		string_constant_1,Nil,Qg2int_message_series,Nil,Nil,T,Nil);
    return VALUES_1(Nil);
}

Object G2int_at_end_of_icp_message_groupqm = UNBOUND;

/* ALL-MESSAGES-PROCESSED? */
Object g2int_all_messages_processedqm(head_icp_buffer,
	    icp_byte_index_of_end_of_message_group_qm,icp_input_port)
    Object head_icp_buffer, icp_byte_index_of_end_of_message_group_qm;
    Object icp_input_port;
{
    Object icp_buffer, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(39,31);
    if (EQ(head_icp_buffer,ISVREF(icp_input_port,(SI_Long)15L))) {
	icp_buffer = ISVREF(icp_input_port,(SI_Long)12L);
	gensymed_symbol = (IFIX(ISVREF(icp_buffer,(SI_Long)3L)) >>  -  - 
		(SI_Long)1L) - (IFIX(ISVREF(icp_buffer,(SI_Long)2L)) >>  - 
		 - (SI_Long)1L);
	gensymed_symbol_1 = IFIX(ISVREF(icp_input_port,(SI_Long)17L));
	gensymed_symbol_2 = (SI_Long)1L;
	temp = FIXNUM_EQ(FIX(gensymed_symbol - gensymed_symbol_1 - 
		gensymed_symbol_2),
		icp_byte_index_of_end_of_message_group_qm) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* READY-FOR-NEXT-ICP-MESSAGE-GROUP */
Object g2int_ready_for_next_icp_message_group(icp_input_port)
    Object icp_input_port;
{
    Object message_group_complete_qm, temp, head_icp_buffer;

    x_note_fn_call(39,32);
    message_group_complete_qm = ISVREF(icp_input_port,(SI_Long)16L);
    temp = ISVREF(icp_input_port,(SI_Long)12L);
    head_icp_buffer = CAR(temp);
    temp = message_group_complete_qm ? ( 
	    !TRUEP(g2int_all_messages_processedqm(head_icp_buffer,
	    message_group_complete_qm,icp_input_port)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* PROCESS-NEXT-ICP-MESSAGE-GROUP-IF-READY */
Object g2int_process_next_icp_message_group_if_ready(icp_input_port)
    Object icp_input_port;
{
    Object icp_socket, disable_resumability, current_icp_socket, system_name;
    Object current_system_name, message_group_complete_qm, head_icp_buffer;
    Object ready_for_next_message_group_p, current_icp_port;
    Object current_standard_icp_object_index_space;
    Object current_temporary_icp_object_index_space;
    Object number_of_icp_bytes_left_in_message_series, current_icp_buffer;
    Object number_of_icp_bytes_ready_to_read, at_end_of_icp_message_group_qm;
    Object current_read_icp_byte_position, icp_buffer, schedule_task_qm;
    Object old_structure_being_reclaimed, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(12);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(39,33);
    icp_socket = ISVREF(icp_input_port,(SI_Long)2L);
    disable_resumability = IFIX(ISVREF(icp_socket,(SI_Long)21L)) >= 
	    (SI_Long)17L ? ISVREF(icp_socket,(SI_Long)53L) : Nil;
    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,11);
      current_icp_socket = icp_socket;
      PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	system_name = ISVREF(icp_socket,(SI_Long)49L);
	current_system_name = EQ(system_name,Qg2int_g2) ? Qg2int_ab : 
		system_name;
	PUSH_SPECIAL(G2int_current_system_name,current_system_name,9);
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      message_group_complete_qm = ISVREF(icp_input_port,(SI_Long)16L);
	      head_icp_buffer = ISVREF(icp_input_port,(SI_Long)12L);
	      ready_for_next_message_group_p = message_group_complete_qm ? 
		      ( 
		      !TRUEP(g2int_all_messages_processedqm(head_icp_buffer,
		      message_group_complete_qm,icp_input_port)) ? T : 
		      Nil) : Qnil;
	      if (ready_for_next_message_group_p) {
		  current_icp_port = icp_input_port;
		  PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,8);
		    current_icp_socket = ISVREF(G2int_current_icp_port,
			    (SI_Long)2L);
		    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,
			    7);
		      current_standard_icp_object_index_space = 
			      ISVREF(G2int_current_icp_port,(SI_Long)8L);
		      PUSH_SPECIAL(G2int_current_standard_icp_object_index_space,current_standard_icp_object_index_space,
			      6);
			current_temporary_icp_object_index_space = 
				ISVREF(G2int_current_icp_port,(SI_Long)19L);
			PUSH_SPECIAL(G2int_current_temporary_icp_object_index_space,current_temporary_icp_object_index_space,
				5);
			  number_of_icp_bytes_left_in_message_series = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL(G2int_number_of_icp_bytes_left_in_message_series,number_of_icp_bytes_left_in_message_series,
				  4);
			    current_icp_buffer = head_icp_buffer;
			    PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				    3);
			      number_of_icp_bytes_ready_to_read = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL(G2int_number_of_icp_bytes_ready_to_read,number_of_icp_bytes_ready_to_read,
				      2);
				at_end_of_icp_message_group_qm = Nil;
				PUSH_SPECIAL(G2int_at_end_of_icp_message_groupqm,at_end_of_icp_message_group_qm,
					1);
				  current_read_icp_byte_position = Nil;
				  PUSH_SPECIAL(G2int_current_read_icp_byte_position,current_read_icp_byte_position,
					  0);
				    if ((SI_Long)0L < 
					    IFIX(ISVREF(icp_input_port,
					    (SI_Long)17L))) {
					icp_buffer = ISVREF(icp_input_port,
						(SI_Long)12L);
					gensymed_symbol = 
						(IFIX(ISVREF(icp_buffer,
						(SI_Long)3L)) >>  -  - 
						(SI_Long)1L) - 
						(IFIX(ISVREF(icp_buffer,
						(SI_Long)2L)) >>  -  - 
						(SI_Long)1L);
					gensymed_symbol_1 = 
						IFIX(ISVREF(icp_input_port,
						(SI_Long)17L));
					gensymed_symbol_2 = (SI_Long)1L;
					G2int_current_read_icp_byte_position 
						= FIX(gensymed_symbol - 
						gensymed_symbol_1 - 
						gensymed_symbol_2);
				    }
				    if (ISVREF(icp_socket,(SI_Long)17L)) {
					schedule_task_qm = 
						ISVREF(icp_socket,
						(SI_Long)16L);
					if (schedule_task_qm) {
					    if (EQ(schedule_task_qm,
						    G2int_current_schedule_task))
						G2int_current_schedule_task 
							= Nil;
					    if (ISVREF(schedule_task_qm,
						    (SI_Long)6L))
						g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
					    inline_note_reclaim_cons(schedule_task_qm,
						    Nil);
					    old_structure_being_reclaimed 
						    = 
						    G2int_structure_being_reclaimed;
					    G2int_structure_being_reclaimed 
						    = schedule_task_qm;
					    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
						    (SI_Long)9L));
					    SVREF(schedule_task_qm,
						    FIX((SI_Long)9L)) = Nil;
					    G2int_structure_being_reclaimed 
						    = 
						    old_structure_being_reclaimed;
					    svref_new_value = 
						    G2int_chain_of_available_schedule_tasks;
					    SVREF(schedule_task_qm,
						    FIX((SI_Long)0L)) = 
						    svref_new_value;
					    G2int_chain_of_available_schedule_tasks 
						    = schedule_task_qm;
					}
					svref_new_value = Nil;
					SVREF(icp_socket,
						FIX((SI_Long)16L)) = 
						svref_new_value;
				    }
				    g2int_handle_icp_messages(Nil);
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
	      result = VALUES_1(ready_for_next_message_group_p);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_icp_socket_transacting_message_group = UNBOUND;

Object G2int_at_end_of_icp_message_blockqm = UNBOUND;

Object G2int_icp_message_trace_streamqm = UNBOUND;

Object G2int_handling_solitary_i_am_aliveqm = UNBOUND;

static Object Qg2int_unknown_message;  /* unknown-message */

static Object Qg2int_handle_icp_acknowledge_shutdown;  /* handle-icp-acknowledge-shutdown */

static Object Qg2int_handle_icp_message_group_id;  /* handle-icp-message-group-id */

static Object Qg2int_handle_icp_i_am_alive;  /* handle-icp-i-am-alive */

/* HANDLE-ICP-MESSAGES */
Object g2int_handle_icp_messages(exit_at_end_of_message_block_qm)
    Object exit_at_end_of_message_block_qm;
{
    Object current_resumable_icp_read_task, resumable_icp_read_ignore_p;
    Object parent_icp_socket, at_end_of_icp_message_block_qm;
    Object icp_socket_transacting_message_group;
    Object current_icp_message_handler_array, icp_byte_qm, index_1;
    Object function_qm, handler_name, previous_handler_name;
    Object ab_loop_iter_flag_, index_of_top_of_backtrace_stack, temp;
    Object svref_arg_2, handling_solitary_i_am_alive_qm;
    SI_Long message_count;
    char ignore_p;
    Declare_special(6);
    Object result;

    x_note_fn_call(39,34);
    current_resumable_icp_read_task = Nil;
    PUSH_SPECIAL(G2int_current_resumable_icp_read_task,current_resumable_icp_read_task,
	    5);
      resumable_icp_read_ignore_p = Nil;
      PUSH_SPECIAL(G2int_resumable_icp_read_ignore_p,resumable_icp_read_ignore_p,
	      4);
	parent_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	at_end_of_icp_message_block_qm = Nil;
	PUSH_SPECIAL(G2int_at_end_of_icp_message_blockqm,at_end_of_icp_message_block_qm,
		3);
	  icp_socket_transacting_message_group = parent_icp_socket;
	  PUSH_SPECIAL(G2int_icp_socket_transacting_message_group,icp_socket_transacting_message_group,
		  2);
	    ignore_p = FIXNUM_EQ(ISVREF(parent_icp_socket,(SI_Long)15L),
		    G2int_icp_connection_awaiting_acknowledgement);
	    current_icp_message_handler_array = 
		    G2int_icp_message_handler_array;
	    icp_byte_qm = Nil;
	    message_count = (SI_Long)1L;
	    index_1 = Nil;
	    function_qm = Nil;
	    handler_name = Nil;
	    previous_handler_name = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    icp_byte_qm = g2int_read_icp_byte_or_message_group_end();
	    if ( !TRUEP(ab_loop_iter_flag_))
		message_count = message_count + (SI_Long)1L;
	    G2int_at_end_of_icp_message_groupqm =  !TRUEP(icp_byte_qm) ? T 
		    : Nil;
	    if (G2int_at_end_of_icp_message_groupqm)
		goto end_loop;
	    index_1 = FIX(IFIX(icp_byte_qm) - (SI_Long)64000L);
	    if ( !TRUEP(ab_loop_iter_flag_))
		previous_handler_name = handler_name;
	    if (IFIX(index_1) <= (SI_Long)0L || IFIX(index_1) >= (SI_Long)750L)
		g2int_icp_out_of_synch(2,FIX((SI_Long)3L),index_1);
	    else {
		function_qm = ISVREF(current_icp_message_handler_array,
			IFIX(index_1));
		if ( !TRUEP(function_qm))
		    g2int_icp_out_of_synch(2,Qg2int_unknown_message,index_1);
	    }
	    handler_name = ISVREF(G2int_icp_message_handler_name_array,
		    IFIX(index_1));
	    index_of_top_of_backtrace_stack = 
		    G2int_index_of_top_of_backtrace_stack;
	    PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		    1);
	      if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		      G2int_size_of_basic_backtrace_information),
		      G2int_maximum_index_in_backtrace_stack_for_internal_error)) 
			  {
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
		  SVREF(temp,svref_arg_2) = handler_name;
	      }
	      temp = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)8L)) = index_1;
	      if (ignore_p) {
		next_loop_1:
		  if ( !TRUEP(g2int_read_icp_byte_if_any()))
		      goto end_loop_1;
		  goto next_loop_1;
		end_loop_1:
		  if (EQ(handler_name,Qg2int_handle_icp_acknowledge_shutdown))
		      g2int_handle_icp_acknowledge_shutdown();
	      }
	      else if (G2int_current_resumable_icp_read_task)
		  g2int_resume_icp_task_1(function_qm);
	      else if (message_count == (SI_Long)2L && EQ(handler_name,
		      Qg2int_handle_icp_message_group_id) && 
		      EQ(previous_handler_name,Qg2int_handle_icp_i_am_alive)) {
		  handling_solitary_i_am_alive_qm = T;
		  PUSH_SPECIAL(G2int_handling_solitary_i_am_aliveqm,handling_solitary_i_am_alive_qm,
			  0);
		    inline_funcall_0(function_qm);
		  POP_SPECIAL();
	      }
	      else
		  inline_funcall_0(function_qm);
	    POP_SPECIAL();
	    g2int_ensure_remote_icp_version_info(parent_icp_socket,
		    handler_name);
	    if (exit_at_end_of_message_block_qm && 
		    G2int_at_end_of_icp_message_blockqm || 
		    G2int_at_end_of_icp_message_groupqm ||  
		    !TRUEP(g2int_icp_connection_can_process_messagesqm(parent_icp_socket)))
		goto end_loop;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    g2int_maybe_finish_current_icp_read_task();
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

Object G2int_debug_out_of_synch = UNBOUND;

/* DEBUG-OUT-OF-SYNCH */
Object g2int_debug_out_of_synch(code,icp_byte,current_icp_buffer,
	    read_icp_byte_position,number_of_icp_bytes_ready_to_read,
	    icp_socket)
    Object code, icp_byte, current_icp_buffer, read_icp_byte_position;
    Object number_of_icp_bytes_ready_to_read, icp_socket;
{
    Declare_special(2);
    Object result;

    x_note_fn_call(39,35);
    PUSH_SPECIAL(G2int_number_of_icp_bytes_ready_to_read,number_of_icp_bytes_ready_to_read,
	    1);
      PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,0);
	if (G2int_debug_out_of_synch) {
	    format((SI_Long)4L,T,"~%ICP out of synch ~D on socket ~A",code,
		    g2int_wide_string_to_gensym_string(g2int_icp_socket_description(icp_socket)));
	    format((SI_Long)3L,T,"~%icp-byte=~D",icp_byte);
	    format((SI_Long)3L,T,"~%icp-byte-position=~D",
		    read_icp_byte_position);
	    format((SI_Long)3L,T,"~%icp-bytes-ready-to-read=~d",
		    G2int_number_of_icp_bytes_ready_to_read);
	    g2int_print_icp_buffer_byte_contents(G2int_current_icp_buffer);
	    result = format((SI_Long)2L,T,"~%");
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_2;   /* "ICP ~A on " */

static Object Qg2int_warning;      /* warning */

static Object string_constant_3;   /* "warning" */

static Object string_constant_4;   /* "error" */

static Object string_constant_5;   /* "socket " */

static Object string_constant_6;   /* ")" */

static Object string_constant_7;   /* ": " */

/* TWRITE-ICP-ERROR */
Object g2int_twrite_icp_error varargs_1(int, n)
{
    Object error_type, error_string_or_out_of_synch_case;
    Object arg1, arg2, arg3, interface_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(39,36);
    INIT_ARGS_nonrelocating();
    error_type = REQUIRED_ARG_nonrelocating();
    error_string_or_out_of_synch_case = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    g2int_tformat(2,string_constant_2,EQ(error_type,Qg2int_warning) ? 
	    string_constant_3 : string_constant_4);
    interface_1 = Nil;
    if ( !TRUEP(interface_1))
	g2int_tformat(1,string_constant_5);
    g2int_twrite_icp_socket_connection_name(G2int_current_icp_socket);
    if (interface_1)
	g2int_tformat(1,string_constant_6);
    g2int_tformat(1,string_constant_7);
    return g2int_tformat(4,error_string_or_out_of_synch_case,arg1,arg2,arg3);
}

static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

/* ICP-ERROR-MESSAGE-STRING */
Object g2int_icp_error_message_string(error_type,
	    error_string_or_out_of_synch_case,arg1,arg2,arg3)
    Object error_type, error_string_or_out_of_synch_case, arg1, arg2, arg3;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(39,37);
    current_wide_string_list = Qg2int_do_not_use;
    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,4);
      wide_string_bv16 = g2int_allocate_byte_vector_16(FIX((SI_Long)2048L 
	      + (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      aref_arg_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      aref_arg_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
      current_wide_string = wide_string_bv16;
      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 
		  - (SI_Long)2L) + 
		  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qg2int_wide_string;
	    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		    0);
	      g2int_twrite_icp_error(5,error_type,
		      error_string_or_out_of_synch_case,arg1,arg2,arg3);
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qg2int_output;       /* output */

static Object Qg2int_resumable_error;  /* resumable-error */

static Object Qg2int_icp_error;    /* icp_error */

static Object Qg2int_input;        /* input */

/* ICP-ERROR-INTERNAL */
Object g2int_icp_error_internal(error_type,
	    error_string_or_out_of_synch_case,arg1,arg2,arg3)
    Object error_type, error_string_or_out_of_synch_case, arg1, arg2, arg3;
{
    Object resumable_icp_state, direction, resumable_output_p, shutdownp;
    Object string2, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(39,38);
    resumable_icp_state = Nil;
    PUSH_SPECIAL(G2int_starresumable_icp_statestar,resumable_icp_state,0);
      direction = ISVREF(G2int_current_icp_port,(SI_Long)3L);
      resumable_output_p = EQ(direction,Qg2int_output) && 
	      G2int_writing_resumable_icp_messages_p ? ( !TRUEP(Nil) ? T : 
	      Nil) : Qnil;
      if (EQ(error_type,Qg2int_warning))
	  shutdownp = Nil;
      else if (EQ(error_type,Qg2int_resumable_error))
	  shutdownp =  !TRUEP(resumable_output_p) ? T : Nil;
      else
	  shutdownp = T;
      string2 = g2int_icp_error_message_string(error_type,
	      error_string_or_out_of_synch_case,arg1,arg2,arg3);
      if (shutdownp)
	  g2int_gsi_connection_error(3,Qg2int_icp_error,
		  G2int_gsi_connection_lost,string2);
      else
	  g2int_gsi_warning(3,Qg2int_icp_error,
		  G2int_gsi_resumable_icp_error,string2);
      g2int_reclaim_text_string(string2);
      if ( !EQ(error_type,Qg2int_warning)) {
	  if (resumable_output_p) {
	      G2int_icp_error_suspend_p = T;
	      temp = G2int_icp_suspend;
	  }
	  else if (G2int_abort_for_icp_catcherqm) {
	      if (EQ(Qg2int_input,direction))
		  g2int_kill_current_icp_read_task();
	      result = VALUES_1(Nil);
	      THROW(G2int_abort_for_icp_catcherqm,result);
	  }
	  else
	      temp = Nil;
      }
      else
	  temp = Nil;
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* ABORT-FOR-ICP */
Object g2int_abort_for_icp()
{
    Object result;

    x_note_fn_call(39,39);
    if (G2int_abort_for_icp_catcherqm) {
	result = VALUES_1(Nil);
	THROW(G2int_abort_for_icp_catcherqm,result);
    }
    else
	g2int_abort(0);
    return VALUES_1(Nil);
}

static Object string_constant_8;   /* "ICP: Socket ~a (~a) received unknown message code ~a; ~
				    *              closing broken connection after message ~a"
				    */

static Object string_constant_9;   /* "ICP: Protocol out-of-synch (case ~d) ~
				    *              for ICP socket ~a with ~a; ~
				    *              closing broken connection after message ~a"
				    */

static Object Qg2int_protocol_out_of_synch_1;  /* protocol-out-of-synch-1 */

static Object Qg2int_protocol_out_of_synch_3;  /* protocol-out-of-synch-3 */

static Object Qg2int_protocol_out_of_synch_4;  /* protocol-out-of-synch-4 */

static Object Qg2int_protocol_out_of_synch_5;  /* protocol-out-of-synch-5 */

static Object Qg2int_protocol_out_of_synch_6;  /* protocol-out-of-synch-6 */

static Object Qg2int_protocol_out_of_synch_7;  /* protocol-out-of-synch-7 */

/* ICP-OUT-OF-SYNCH */
Object g2int_icp_out_of_synch varargs_1(int, n)
{
    Object case_1;
    Object message_code, parent_socket, icp_socket_transacting_message_group;
    Object temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(39,40);
    INIT_ARGS_nonrelocating();
    case_1 = REQUIRED_ARG_nonrelocating();
    message_code = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    parent_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
    if ( !(G2int_abort_for_icp_catcherqm || EQ(case_1,FIX((SI_Long)3L)) || 
	    EQ(case_1,Qg2int_unknown_message))) {
	if (EQ(case_1,Qg2int_unknown_message))
	    g2int_notify_user_at_console(5,string_constant_8,
		    ISVREF(parent_socket,(SI_Long)1L),ISVREF(parent_socket,
		    (SI_Long)2L),message_code,ISVREF(parent_socket,
		    (SI_Long)8L));
	else
	    g2int_notify_user_at_console(5,string_constant_9,case_1,
		    ISVREF(parent_socket,(SI_Long)1L),ISVREF(parent_socket,
		    (SI_Long)2L),ISVREF(parent_socket,(SI_Long)8L));
    }
    icp_socket_transacting_message_group = Nil;
    PUSH_SPECIAL(G2int_icp_socket_transacting_message_group,icp_socket_transacting_message_group,
	    0);
      if (EQ(case_1,Qg2int_unknown_message))
	  temp = Qg2int_unknown_message;
      else if (EQ(case_1,FIX((SI_Long)1L)))
	  temp = Qg2int_protocol_out_of_synch_1;
      else if (EQ(case_1,FIX((SI_Long)3L)))
	  temp = Qg2int_protocol_out_of_synch_3;
      else if (EQ(case_1,FIX((SI_Long)4L)))
	  temp = Qg2int_protocol_out_of_synch_4;
      else if (EQ(case_1,FIX((SI_Long)5L)))
	  temp = Qg2int_protocol_out_of_synch_5;
      else if (EQ(case_1,FIX((SI_Long)6L)))
	  temp = Qg2int_protocol_out_of_synch_6;
      else if (EQ(case_1,FIX((SI_Long)7L)))
	  temp = Qg2int_protocol_out_of_synch_7;
      else
	  temp = Qnil;
      g2int_shutdown_icp_socket_connection(2,parent_socket,temp);
    POP_SPECIAL();
    return g2int_abort_for_icp();
}

Object G2int_icp_buffers_for_message_group = UNBOUND;

Object G2int_icp_byte_position_of_start_of_message_seriesqm = UNBOUND;

Object G2int_icp_buffer_of_start_of_message_seriesqm = UNBOUND;

Object G2int_number_of_icp_bytes_in_message_group = UNBOUND;

/* WRITE-ICP-MAYBE-SUSPEND */
Object g2int_write_icp_maybe_suspend()
{
    Object temp;

    x_note_fn_call(39,41);
    if (G2int_writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer),
	    G2int_minimum_message_series_size_before_suspending)) {
	G2int_starresumable_icp_statestar = Nil;
	temp = G2int_icp_suspend;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* WRITE-ICP-BYTE */
Object g2int_write_icp_byte(icp_byte)
    Object icp_byte;
{
    Object temp, array, array_1;
    SI_Long length_1, start, icp_position, position_1, value, temp_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(39,42);
    if (G2int_writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer),
	    G2int_minimum_message_series_size_before_suspending)) {
	G2int_starresumable_icp_statestar = Nil;
	temp = G2int_icp_suspend;
    }
    else {
	length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	if ((SI_Long)0L == length_1) {
	    g2int_write_get_new_buffer();
	    length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	}
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = IFIX(FIXNUM_ADD1(G2int_current_write_icp_byte_position));
	G2int_current_write_icp_byte_position = FIX(start - (SI_Long)1L + 
		(SI_Long)1L);
	G2int_number_of_icp_bytes_to_fill_buffer = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = start;
	position_1 = icp_position + icp_position;
	value = IFIX(icp_byte);
	temp_1 = value >>  -  - (SI_Long)8L;
	UBYTE_8_ISASET_1(array_1,position_1,temp_1);
	temp_1 = position_1 + (SI_Long)1L;
	gensymed_symbol = (SI_Long)255L & value;
	UBYTE_8_ISASET_1(array_1,temp_1,gensymed_symbol);
	temp = FIX(value);
    }
    return VALUES_1(temp);
}

/* GET-ICP-WRITE-BUFFER */
Object g2int_get_icp_write_buffer()
{
    Object array;
    SI_Long length_1, start;

    x_note_fn_call(39,43);
    if (G2int_writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer),
	    G2int_minimum_message_series_size_before_suspending)) {
	G2int_starresumable_icp_statestar = Nil;
	return VALUES_1(G2int_icp_suspend);
    }
    else {
	length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	if ((SI_Long)0L == length_1) {
	    g2int_write_get_new_buffer();
	    length_1 = IFIX(G2int_number_of_icp_bytes_to_fill_buffer);
	}
	array = ISVREF(G2int_current_icp_buffer,(SI_Long)4L);
	start = IFIX(FIXNUM_ADD1(G2int_current_write_icp_byte_position));
	return VALUES_3(array,FIX(start),FIX(length_1));
    }
}

/* WRITE-GET-NEW-BUFFER */
Object g2int_write_get_new_buffer()
{
    Object temp, tail, copy, new_icp_buffer;
    SI_Long bytes_available_in_buffer, incff_1_arg;
    SI_Long number_of_icp_bytes_for_message_series_new_value;

    x_note_fn_call(39,44);
    if (G2int_current_icp_buffer) {
	temp = G2int_current_icp_buffer;
	ISVREF(temp,(SI_Long)3L) = FIX((SI_Long)4096L);
    }
    tail = ISVREF(G2int_current_icp_port,(SI_Long)13L);
    if ( !EQ(ISVREF(G2int_current_icp_port,(SI_Long)12L),tail) &&  
	    !TRUEP(ISVREF(tail,(SI_Long)5L)) && IFIX(ISVREF(tail,
	    (SI_Long)3L)) < (SI_Long)4096L) {
	copy = g2int_copy_icp_buffer(tail);
	temp = ISVREF(copy,(SI_Long)3L);
	SVREF(copy,FIX((SI_Long)2L)) = temp;
	new_icp_buffer = copy;
    }
    else
	new_icp_buffer = 
		g2int_make_icp_buffer_internal_1(g2int_make_variable_fill_icp_buffer());
    if (G2int_icp_buffers_for_message_group) {
	temp = G2int_current_icp_buffer;
	SVREF(temp,FIX((SI_Long)1L)) = new_icp_buffer;
    }
    else
	G2int_icp_buffers_for_message_group = new_icp_buffer;
    G2int_current_icp_buffer = new_icp_buffer;
    bytes_available_in_buffer = (SI_Long)2048L - 
	    (IFIX(ISVREF(G2int_current_icp_buffer,(SI_Long)3L)) >>  -  - 
	    (SI_Long)1L);
    G2int_number_of_icp_bytes_to_fill_buffer = FIX(bytes_available_in_buffer);
    incff_1_arg = bytes_available_in_buffer;
    number_of_icp_bytes_for_message_series_new_value = 
	    IFIX(G2int_number_of_icp_bytes_for_message_series) + incff_1_arg;
    G2int_number_of_icp_bytes_for_message_series = 
	    FIX(number_of_icp_bytes_for_message_series_new_value);
    G2int_current_write_icp_byte_position = FIX((SI_Long)2048L - 
	    bytes_available_in_buffer - (SI_Long)1L);
    if ((SI_Long)60952L <= 
	    IFIX(G2int_number_of_icp_bytes_for_message_series) && 
	    G2int_disable_resumability)
	g2int_start_icp_message_series();
    return VALUES_1(Nil);
}

/* STOP-FILLING-ICP-BUFFER-AT-END-OF-ICP-MESSAGE-GROUP */
Object g2int_stop_filling_icp_buffer_at_end_of_icp_message_group()
{
    Object temp, decff_1_arg;
    SI_Long svref_new_value;

    x_note_fn_call(39,45);
    temp = G2int_current_icp_buffer;
    svref_new_value = (SI_Long)2048L - 
	    IFIX(G2int_number_of_icp_bytes_to_fill_buffer) << (SI_Long)1L;
    ISVREF(temp,(SI_Long)3L) = FIX(svref_new_value);
    decff_1_arg = G2int_number_of_icp_bytes_to_fill_buffer;
    temp = FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    decff_1_arg);
    G2int_number_of_icp_bytes_for_message_series = temp;
    G2int_number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

Object G2int_writing_icp_message_group = UNBOUND;

/* NEXT-ICP-MESSAGE-GROUP */
Object g2int_next_icp_message_group()
{
    x_note_fn_call(39,46);
    g2int_end_icp_message_group();
    G2int_number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
    G2int_icp_buffers_for_message_group = Nil;
    G2int_icp_byte_position_of_start_of_message_seriesqm = Nil;
    G2int_number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
    G2int_current_icp_buffer = Nil;
    G2int_current_write_icp_byte_position = Nil;
    G2int_number_of_icp_bytes_in_message_group = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

Object G2int_do_icp_flow_controlqm = UNBOUND;

/* UPDATE-I-AM-ALIVE-INFO-AT-END-OF-MESSAGE-GROUP */
Object g2int_update_i_am_alive_info_at_end_of_message_group(i_am_alive_info)
    Object i_am_alive_info;
{
    x_note_fn_call(39,47);
    return VALUES_1(Nil);
}

/* UPDATE-ICP-CONNECTION-CLOGGED-P */
Object g2int_update_icp_connection_clogged_p(i_am_alive_info,
	    side_sending_i_am_alive_p)
    Object i_am_alive_info, side_sending_i_am_alive_p;
{
    x_note_fn_call(39,48);
    return VALUES_1(side_sending_i_am_alive_p);
}

/* END-ICP-MESSAGE-GROUP */
Object g2int_end_icp_message_group()
{
    Object i_am_alive_info_qm;

    x_note_fn_call(39,49);
    if (G2int_icp_buffers_for_message_group) {
	if ( !TRUEP(G2int_writing_resumable_icp_messages_p)) {
	    i_am_alive_info_qm = ISVREF(G2int_current_icp_socket,(SI_Long)24L);
	    if (i_am_alive_info_qm)
		g2int_update_i_am_alive_info_at_end_of_message_group(i_am_alive_info_qm);
	}
	g2int_start_icp_message_series();
	g2int_stop_filling_icp_buffer_at_end_of_icp_message_group();
	g2int_end_icp_message_series_if_any();
	g2int_transmit_completed_icp_message_group();
    }
    return VALUES_1(Nil);
}

static Object string_constant_10;  /* "message series" */

/* START-WRITING-ICP-MESSAGE */
Object g2int_start_writing_icp_message(icp_message_type_code)
    Object icp_message_type_code;
{
    Object bytes_in_current_message_series, writing_resumable_icp_messages_p;
    Declare_special(1);

    x_note_fn_call(39,50);
    bytes_in_current_message_series = 
	    FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
	    G2int_number_of_icp_bytes_to_fill_buffer);
    if ((SI_Long)0L == IFIX(bytes_in_current_message_series) || 
	    FIXNUM_LT(G2int_minimum_message_series_size_before_beginning_new_series,
	    bytes_in_current_message_series)) {
	if (G2int_icp_write_trace_cutoff_levelqm && 
		(EQ(G2int_icp_write_trace_cutoff_levelqm,T) || 
		IFIX(G2int_icp_write_trace_cutoff_levelqm) >= (SI_Long)1L))
	    g2int_emit_icp_write_trace(T,Nil,Nil,string_constant_10,Nil,
		    Qg2int_message_series,Nil,Nil,T,Nil);
	g2int_start_icp_message_series();
    }
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      g2int_write_icp_byte(FIX(IFIX(icp_message_type_code) + (SI_Long)64000L));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* START-ICP-MESSAGE-SERIES */
Object g2int_start_icp_message_series()
{
    Object writing_resumable_icp_messages_p;
    Declare_special(1);

    x_note_fn_call(39,51);
    g2int_end_icp_message_series_if_any();
    G2int_number_of_icp_bytes_for_message_series = 
	    G2int_number_of_icp_bytes_to_fill_buffer;
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      g2int_write_icp_byte(FIX((SI_Long)1L));
    POP_SPECIAL();
    G2int_icp_buffer_of_start_of_message_seriesqm = G2int_current_icp_buffer;
    G2int_icp_byte_position_of_start_of_message_seriesqm = 
	    G2int_current_write_icp_byte_position;
    return VALUES_1(Nil);
}

Object G2int_icp_message_too_long_warning = UNBOUND;

/* TRANSMIT-COMPLETED-ICP-MESSAGE-GROUP */
Object g2int_transmit_completed_icp_message_group()
{
    Object icp_output_port, tail, buffer, svref_new_value, next_buffer;
    Object new_cons;

    x_note_fn_call(39,52);
    icp_output_port = G2int_current_icp_port;
    if (G2int_icp_buffers_for_message_group) {
	tail = ISVREF(icp_output_port,(SI_Long)13L);
	buffer = G2int_icp_buffers_for_message_group;
	if (EQ(ISVREF(tail,(SI_Long)4L),ISVREF(buffer,(SI_Long)4L))) {
	    svref_new_value = ISVREF(buffer,(SI_Long)3L);
	    SVREF(tail,FIX((SI_Long)3L)) = svref_new_value;
	    G2int_icp_buffers_for_message_group = ISVREF(buffer,(SI_Long)1L);
	    g2int_reclaim_icp_buffer(buffer);
	}
	if (G2int_icp_buffers_for_message_group) {
	    svref_new_value = G2int_icp_buffers_for_message_group;
	    SVREF(tail,FIX((SI_Long)1L)) = svref_new_value;
	    buffer = G2int_icp_buffers_for_message_group;
	    next_buffer = Nil;
	  next_loop:
	    next_buffer = ISVREF(buffer,(SI_Long)1L);
	    if ( !TRUEP(next_buffer))
		goto end_loop;
	    buffer = next_buffer;
	    goto next_loop;
	  end_loop:
	    SVREF(icp_output_port,FIX((SI_Long)13L)) = buffer;
	}
    }
    if (ISVREF(icp_output_port,(SI_Long)5L)) {
	if ( !EQ(ISVREF(icp_output_port,(SI_Long)12L),
		ISVREF(icp_output_port,(SI_Long)13L))) {
	    if (G2int_with_icp_buffer_coelescing_scopeqm) {
		g2int_transmit_icp_output_if_ready(icp_output_port,Nil);
		if ( !TRUEP(ISVREF(icp_output_port,(SI_Long)18L))) {
		    new_cons = g2int_gensym_cons_1(icp_output_port,
			    G2int_icp_output_ports_to_flush);
		    SVREF(icp_output_port,FIX((SI_Long)18L)) = new_cons;
		    G2int_icp_output_ports_to_flush = new_cons;
		}
	    }
	    else
		g2int_transmit_icp_output_if_ready(icp_output_port,T);
	}
    }
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "wrote \"end-of-message-group\" message series" */

static Object string_constant_12;  /* "[finished writing message series]" */

/* END-ICP-MESSAGE-SERIES-IF-ANY */
Object g2int_end_icp_message_series_if_any()
{
    Object message_series_byte_count, array, incff_1_arg;
    Object number_of_icp_bytes_in_message_group_new_value;
    SI_Long icp_position, position_1, value, temp, gensymed_symbol;

    x_note_fn_call(39,53);
    if (G2int_icp_buffers_for_message_group) {
	message_series_byte_count = 
		FIXNUM_MINUS(G2int_number_of_icp_bytes_for_message_series,
		G2int_number_of_icp_bytes_to_fill_buffer);
	if (IFIX(message_series_byte_count) > (SI_Long)63000L)
	    g2int_signal_gsi_icp_message_too_long_error();
	if (G2int_icp_write_trace_cutoff_levelqm && 
		(EQ(G2int_icp_write_trace_cutoff_levelqm,T) || 
		IFIX(G2int_icp_write_trace_cutoff_levelqm) >= (SI_Long)1L))
	    g2int_emit_icp_write_trace(Nil,FIX((SI_Long)0L),
		    message_series_byte_count,
		    IFIX(message_series_byte_count) == (SI_Long)1L ? 
		    string_constant_11 : string_constant_12,Nil,
		    Qg2int_message_series,Nil,Nil,T,Nil);
	array = ISVREF(G2int_icp_buffer_of_start_of_message_seriesqm,
		(SI_Long)4L);
	icp_position = 
		IFIX(G2int_icp_byte_position_of_start_of_message_seriesqm);
	position_1 = icp_position + icp_position;
	value = IFIX(message_series_byte_count);
	temp = value >>  -  - (SI_Long)8L;
	UBYTE_8_ISASET_1(array,position_1,temp);
	temp = position_1 + (SI_Long)1L;
	gensymed_symbol = (SI_Long)255L & value;
	UBYTE_8_ISASET_1(array,temp,gensymed_symbol);
	incff_1_arg = message_series_byte_count;
	number_of_icp_bytes_in_message_group_new_value = 
		FIXNUM_ADD(G2int_number_of_icp_bytes_in_message_group,
		incff_1_arg);
	G2int_number_of_icp_bytes_in_message_group = 
		number_of_icp_bytes_in_message_group_new_value;
	return VALUES_1(G2int_number_of_icp_bytes_in_message_group);
    }
    else
	return VALUES_1(Nil);
}

void int2_INIT()
{
    Object string_constant_13, Qg2int_int2, Qg2int_do_icp_flow_controlqm;
    Object AB_package, Qg2int_abort_for_icp_catcherqm;
    Object Qg2int_icp_message_trace_streamqm;
    Object Qg2int_at_end_of_icp_message_groupqm;
    Object Qg2int_current_write_icp_byte_position;
    Object Qg2int_current_read_icp_byte_position;
    Object Qg2int_number_of_icp_bytes_ready_to_read, Qg2int_current_icp_buffer;
    Object Qg2int_number_of_icp_bytes_left_in_message_series;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2int_refused_icp_listener_connections, Qg2int_icp_socket_index;

    x_note_fn_call(39,54);
    SET_PACKAGE("AB");
    G2int_localnet_queued_icp_buffer_limit = FIX((SI_Long)3L);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_localnet = STATIC_SYMBOL("LOCALNET",AB_package);
    Qg2int_generic = STATIC_SYMBOL("GENERIC",AB_package);
    Qg2int_icp_socket_index = STATIC_SYMBOL("ICP-SOCKET-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_socket_index,G2int_icp_socket_index);
    Qg2int_int2 = STATIC_SYMBOL("INT2",AB_package);
    g2int_record_system_variable(Qg2int_icp_socket_index,Qg2int_int2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (G2int_shutdown_interval_for_disallowed_icp_connection_in_seconds 
	    == UNBOUND)
	G2int_shutdown_interval_for_disallowed_icp_connection_in_seconds = 
		FIX((SI_Long)10L);
    if (G2int_shutdown_interval_for_disallowed_icp_connection == UNBOUND)
	G2int_shutdown_interval_for_disallowed_icp_connection = 
		g2int_fixnum_time_interval(FIX((SI_Long)1000L * 
		IFIX(G2int_shutdown_interval_for_disallowed_icp_connection_in_seconds)));
    if (G2int_negative_shutdown_interval_for_disallowed_icp_connection == 
	    UNBOUND)
	G2int_negative_shutdown_interval_for_disallowed_icp_connection = 
		FIXNUM_NEGATE(G2int_shutdown_interval_for_disallowed_icp_connection);
    Qg2int_refused_icp_listener_connections = 
	    STATIC_SYMBOL("REFUSED-ICP-LISTENER-CONNECTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_refused_icp_listener_connections,
	    G2int_refused_icp_listener_connections);
    g2int_record_system_variable(Qg2int_refused_icp_listener_connections,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_g2 = STATIC_SYMBOL("G2",AB_package);
    Qg2int_execute = STATIC_SYMBOL("EXECUTE",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_connect = STATIC_SYMBOL("CONNECT",AB_package);
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qg2int_inform = STATIC_SYMBOL("INFORM",AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Kfnord = STATIC_SYMBOL("FNORD",Pkeyword);
    if (G2int_inhibit_icp_message_processing_enabled == UNBOUND)
	G2int_inhibit_icp_message_processing_enabled = T;
    if (G2int_inhibit_icp_message_processing == UNBOUND)
	G2int_inhibit_icp_message_processing = Nil;
    if (G2int_icp_sockets_waiting_for_icp_message_processing == UNBOUND)
	G2int_icp_sockets_waiting_for_icp_message_processing = Nil;
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    if (G2int_handle_ui_client_interface_messages_immediately_p == UNBOUND)
	G2int_handle_ui_client_interface_messages_immediately_p = Nil;
    Qg2int_handle_icp_messages = STATIC_SYMBOL("HANDLE-ICP-MESSAGES",
	    AB_package);
    Qg2int_handle_queued_icp_messages_task = 
	    STATIC_SYMBOL("HANDLE-QUEUED-ICP-MESSAGES-TASK",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_queued_icp_messages_task,
	    STATIC_FUNCTION(g2int_handle_queued_icp_messages_task,NIL,
	    FALSE,1,1));
    Qg2int_broken_while_transmitting = 
	    STATIC_SYMBOL("BROKEN-WHILE-TRANSMITTING",AB_package);
    Qg2int_end_of_message_group = STATIC_SYMBOL("END-OF-MESSAGE-GROUP",
	    AB_package);
    if (G2int_priority_of_icp_message_service == UNBOUND)
	G2int_priority_of_icp_message_service = FIX((SI_Long)3L);
    if (G2int_priority_of_rpc_service == UNBOUND)
	G2int_priority_of_rpc_service = FIX((SI_Long)6L);
    if (G2int_priority_of_icp_control_messages == UNBOUND)
	G2int_priority_of_icp_control_messages = FIX((SI_Long)7L);
    if (G2int_resumable_priority_of_gsi_data_service == UNBOUND)
	G2int_resumable_priority_of_gsi_data_service = FIX((SI_Long)4L);
    if (G2int_resumable_priority_of_gsi_rpc_service == UNBOUND)
	G2int_resumable_priority_of_gsi_rpc_service = FIX((SI_Long)6L);
    Qg2int_number_of_icp_bytes_left_in_message_series = 
	    STATIC_SYMBOL("NUMBER-OF-ICP-BYTES-LEFT-IN-MESSAGE-SERIES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_number_of_icp_bytes_left_in_message_series,
	    G2int_number_of_icp_bytes_left_in_message_series);
    g2int_record_system_variable(Qg2int_number_of_icp_bytes_left_in_message_series,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_icp_buffer = STATIC_SYMBOL("CURRENT-ICP-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_icp_buffer,
	    G2int_current_icp_buffer);
    g2int_record_system_variable(Qg2int_current_icp_buffer,Qg2int_int2,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2int_number_of_icp_bytes_ready_to_read = 
	    STATIC_SYMBOL("NUMBER-OF-ICP-BYTES-READY-TO-READ",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_number_of_icp_bytes_ready_to_read,
	    G2int_number_of_icp_bytes_ready_to_read);
    g2int_record_system_variable(Qg2int_number_of_icp_bytes_ready_to_read,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_read_icp_byte_position = 
	    STATIC_SYMBOL("CURRENT-READ-ICP-BYTE-POSITION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_read_icp_byte_position,
	    G2int_current_read_icp_byte_position);
    g2int_record_system_variable(Qg2int_current_read_icp_byte_position,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_write_icp_byte_position = 
	    STATIC_SYMBOL("CURRENT-WRITE-ICP-BYTE-POSITION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_write_icp_byte_position,
	    G2int_current_write_icp_byte_position);
    g2int_record_system_variable(Qg2int_current_write_icp_byte_position,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_writing_resumable_icp_messages_p == UNBOUND)
	G2int_writing_resumable_icp_messages_p = Nil;
    if (G2int_icp_error_suspend_p == UNBOUND)
	G2int_icp_error_suspend_p = Nil;
    if (G2int_current_resumable_icp_read_task == UNBOUND)
	G2int_current_resumable_icp_read_task = Nil;
    if (G2int_resumable_icp_read_ignore_p == UNBOUND)
	G2int_resumable_icp_read_ignore_p = Nil;
    string_constant = STATIC_STRING("[reading message series]");
    Qg2int_message_series = STATIC_SYMBOL("MESSAGE-SERIES",AB_package);
    string_constant_1 = 
	    STATIC_STRING("read \"end-of-message-group\" message series");
    Qg2int_at_end_of_icp_message_groupqm = 
	    STATIC_SYMBOL("AT-END-OF-ICP-MESSAGE-GROUP\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_at_end_of_icp_message_groupqm,
	    G2int_at_end_of_icp_message_groupqm);
    g2int_record_system_variable(Qg2int_at_end_of_icp_message_groupqm,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_icp_socket_transacting_message_group == UNBOUND)
	G2int_icp_socket_transacting_message_group = Nil;
    Qg2int_icp_message_trace_streamqm = 
	    STATIC_SYMBOL("ICP-MESSAGE-TRACE-STREAM\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_icp_message_trace_streamqm,
	    G2int_icp_message_trace_streamqm);
    g2int_record_system_variable(Qg2int_icp_message_trace_streamqm,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_unknown_message = STATIC_SYMBOL("UNKNOWN-MESSAGE",AB_package);
    Qg2int_handle_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    Qg2int_handle_icp_message_group_id = 
	    STATIC_SYMBOL("HANDLE-ICP-MESSAGE-GROUP-ID",AB_package);
    Qg2int_handle_icp_i_am_alive = STATIC_SYMBOL("HANDLE-ICP-I-AM-ALIVE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_messages,
	    STATIC_FUNCTION(g2int_handle_icp_messages,NIL,FALSE,1,1));
    if (G2int_debug_out_of_synch == UNBOUND)
	G2int_debug_out_of_synch = T;
    string_constant_2 = STATIC_STRING("ICP ~A on ");
    Qg2int_warning = STATIC_SYMBOL("WARNING",AB_package);
    string_constant_3 = STATIC_STRING("warning");
    string_constant_4 = STATIC_STRING("error");
    string_constant_5 = STATIC_STRING("socket ");
    string_constant_6 = STATIC_STRING(")");
    string_constant_7 = STATIC_STRING(": ");
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_resumable_error = STATIC_SYMBOL("RESUMABLE-ERROR",AB_package);
    Qg2int_icp_error = STATIC_SYMBOL("ICP_ERROR",AB_package);
    Qg2int_input = STATIC_SYMBOL("INPUT",AB_package);
    Qg2int_abort_for_icp_catcherqm = 
	    STATIC_SYMBOL("ABORT-FOR-ICP-CATCHER\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_abort_for_icp_catcherqm,
	    G2int_abort_for_icp_catcherqm);
    g2int_record_system_variable(Qg2int_abort_for_icp_catcherqm,
	    Qg2int_int2,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_8 = 
	    STATIC_STRING("ICP: Socket ~a (~a) received unknown message code ~a; ~\n             closing broken connection after message ~a");
    string_constant_9 = 
	    STATIC_STRING("ICP: Protocol out-of-synch (case ~d) ~\n             for ICP socket ~a with ~a; ~\n             closing broken connection after message ~a");
    Qg2int_protocol_out_of_synch_1 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-1",AB_package);
    Qg2int_protocol_out_of_synch_3 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-3",AB_package);
    Qg2int_protocol_out_of_synch_4 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-4",AB_package);
    Qg2int_protocol_out_of_synch_5 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-5",AB_package);
    Qg2int_protocol_out_of_synch_6 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-6",AB_package);
    Qg2int_protocol_out_of_synch_7 = 
	    STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-7",AB_package);
    if (G2int_writing_icp_message_group == UNBOUND)
	G2int_writing_icp_message_group = FIX((SI_Long)0L);
    Qg2int_do_icp_flow_controlqm = STATIC_SYMBOL("DO-ICP-FLOW-CONTROL\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_do_icp_flow_controlqm,
	    G2int_do_icp_flow_controlqm);
    g2int_record_system_variable(Qg2int_do_icp_flow_controlqm,Qg2int_int2,
	    T,Qnil,Qnil,Qnil,Qnil);
    string_constant_10 = STATIC_STRING("message series");
    string_constant_13 = 
	    STATIC_STRING("ICP message series too long -- please call Gensym customer support");
    G2int_icp_message_too_long_warning = string_constant_13;
    string_constant_11 = 
	    STATIC_STRING("wrote \"end-of-message-group\" message series");
    string_constant_12 = STATIC_STRING("[finished writing message series]");
}
