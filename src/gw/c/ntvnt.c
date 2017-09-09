/* ntvnt.c
 * Input file:  netevent.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntvnt.h"


Object G2int_icp_error_table = UNBOUND;

Object G2int_icp_success = UNBOUND;

Object G2int_icp_read_event_error = UNBOUND;

Object G2int_icp_received_data_on_invalid_socket = UNBOUND;

Object G2int_icp_read_call_returned_error = UNBOUND;

Object G2int_icp_write_event_error = UNBOUND;

Object G2int_icp_wrote_data_on_invalid_socket = UNBOUND;

Object G2int_icp_write_call_returned_error = UNBOUND;

Object G2int_icp_connect_event_error = UNBOUND;

Object G2int_icp_connect_on_invalid_socket = UNBOUND;

Object G2int_icp_accept_on_invalid_socket = UNBOUND;

Object G2int_icp_accept_event_error = UNBOUND;

Object G2int_icp_close_event_error = UNBOUND;

Object G2int_icp_connection_closed_error = UNBOUND;

Object G2int_icp_shutdown_aborted = UNBOUND;

Object G2int_icp_connection_reset = UNBOUND;

Object G2int_icp_accept_failure = UNBOUND;

Object G2int_icp_error_obtaining_error_string = UNBOUND;

static Object array_constant;      /* # */

static Object string_constant;     /* "~A" */

/* ICP-ERROR-ON-SOCKET */
Object g2int_icp_error_on_socket varargs_1(int, n)
{
    Object icp_socket, error_code;
    Object network_error_code, network_error_string, icp_socket_description;
    Object error_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(40,0);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    error_code = REQUIRED_ARG_nonrelocating();
    network_error_code = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    network_error_string = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (FIXNUM_EQ(ISVREF(ISVREF(array_constant,IFIX(error_code)),
	    (SI_Long)2L),G2int_error_severity_fatal)) {
	icp_socket_description = g2int_icp_socket_description(icp_socket);
	error_string = g2int_tformat_text_string(4,
		ISVREF(ISVREF(array_constant,IFIX(error_code)),
		(SI_Long)1L),icp_socket_description,network_error_code,
		network_error_string);
	g2int_reclaim_text_string(icp_socket_description);
	if (network_error_string)
	    g2int_reclaim_text_string(network_error_string);
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		G2int_icp_socket_listening)) {
	    g2int_notify_user_at_console(2,string_constant,error_string);
	    g2int_reclaim_text_string(error_string);
	}
	else
	    g2int_shutdown_icp_socket_connection(2,icp_socket,error_string);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_no_event = UNBOUND;

Object G2int_read_event = UNBOUND;

Object G2int_write_event = UNBOUND;

Object G2int_connect_event = UNBOUND;

Object G2int_accept_event = UNBOUND;

Object G2int_close_event = UNBOUND;

Object G2int_scheduler_event = UNBOUND;

Object G2int_display_event = UNBOUND;

Object G2int_read_and_block_event = UNBOUND;

Object G2int_watch_event = UNBOUND;

Object G2int_quit_event = UNBOUND;

Object G2int_error_event = UNBOUND;

Object G2int_network_status_success = UNBOUND;

Object G2int_network_octet_buffer_length = UNBOUND;

Object G2int_last_event_socket_handle_holder = UNBOUND;

Object G2int_last_event_socket_handle = UNBOUND;

Object G2int_last_event_status_code_holder = UNBOUND;

Object G2int_last_event_status_code = UNBOUND;

Object G2int_last_event_status_code_0 = UNBOUND;

Object G2int_last_event_status_code_1 = UNBOUND;

Object G2int_handle_to_socket_mapping = UNBOUND;

/* G2-EVENT-READY-P */
Object g2int_g2_event_ready_p()
{
    Object temp;

    x_note_fn_call(40,1);
    temp = (SI_Long)0L != g2_event_ready((SI_Long)0L) ? T : Nil;
    return VALUES_1(temp);
}

/* G2-EVENT-CYCLE-HANDLING-WINDOWS-QUIT */
Object g2int_g2_event_cycle_handling_windows_quit()
{
    Object temp;

    x_note_fn_call(40,2);
    temp = (SI_Long)0L != g2_event_cycle((SI_Long)1L) ? 
	    g2int_shutdown_or_exit(0) : Nil;
    return VALUES_1(temp);
}

Object G2int_internal_events_handling_trigger = UNBOUND;

/* GSI-EVENT-CYCLE-HANDLING-WINDOWS-QUIT */
Object g2int_gsi_event_cycle_handling_windows_quit()
{
    Object temp;

    x_note_fn_call(40,3);
    temp = (SI_Long)0L != g2_event_cycle((SI_Long)0L) ? 
	    g2int_shutdown_or_exit(0) : Nil;
    return VALUES_1(temp);
}

/* C-NETWORK-GET-LAST-ERROR-STRING */
Object g2int_c_network_get_last_error_string(socket_handle,output_buffer)
    Object socket_handle, output_buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(40,4);
    gensymed_symbol = 
	    g2int_copy_foreign_string_arg_if_appropriate(output_buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = output_buffer;
    ne_last_error_string(IFIX(socket_handle),ISTRING(temp));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

/* NETWORK-GET-LAST-ERROR-STRING */
Object g2int_network_get_last_error_string(handle)
    Object handle;
{
    Object buffer, temp;
    SI_Long length_1;

    x_note_fn_call(40,5);
    length_1 = ne_last_error_length(IFIX(handle));
    if ((SI_Long)0L < length_1) {
	buffer = g2int_obtain_simple_gensym_string(FIX(length_1));
	g2int_c_network_get_last_error_string(handle,buffer);
	temp = g2int_copy_partial_text_string(buffer,FIX(length_1));
	g2int_reclaim_gensym_string(buffer);
	return VALUES_1(temp);
    }
    else
	return g2int_copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)30L));
}

/* LOOKUP-SOCKET-FROM-HANDLE */
Object g2int_lookup_socket_from_handle(socket_handle)
    Object socket_handle;
{
    Object temp, socket_1;

    x_note_fn_call(40,6);
    temp = g2int_assq_function(socket_handle,G2int_handle_to_socket_mapping);
    socket_1 = CDR(temp);
    return VALUES_1(socket_1);
}

/* REGISTER-SOCKET-TO-HANDLE */
Object g2int_register_socket_to_handle(socket_1,socket_handle)
    Object socket_1, socket_handle;
{
    Object mapping_qm;

    x_note_fn_call(40,7);
    mapping_qm = g2int_assq_function(socket_handle,
	    G2int_handle_to_socket_mapping);
    if (mapping_qm)
	M_CDR(mapping_qm) = socket_1;
    else
	G2int_handle_to_socket_mapping = 
		g2int_gensym_cons_1(g2int_gensym_cons_1(socket_handle,
		socket_1),G2int_handle_to_socket_mapping);
    return VALUES_1(Nil);
}

Object G2int_icp_sockets_waiting_for_icp_message_processing = UNBOUND;

static Object Qg2int_generic;      /* generic */

static Object Qg2int_localnet;     /* localnet */

/* CLOSE-AND-DISCONNECT-ICP-SOCKET-HANDLE */
Object g2int_close_and_disconnect_icp_socket_handle(icp_socket)
    Object icp_socket;
{
    Object svref_new_value, input_port, output_port, handle, connection_type;
    Object schedule_task_qm, old_structure_being_reclaimed, element, cons_qm;
    Object corresponding_localnet_socket;

    x_note_fn_call(40,8);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_closed)) {
	svref_new_value = G2int_icp_connection_closed;
	SVREF(icp_socket,FIX((SI_Long)15L)) = svref_new_value;
	input_port = ISVREF(icp_socket,(SI_Long)3L);
	output_port = ISVREF(icp_socket,(SI_Long)4L);
	handle = ISVREF(input_port,(SI_Long)1L);
	connection_type = ISVREF(icp_socket,(SI_Long)1L);
	SVREF(input_port,FIX((SI_Long)1L)) = Nil;
	if (output_port)
	    SVREF(output_port,FIX((SI_Long)1L)) = Nil;
	g2int_clear_read_event(icp_socket);
	g2int_clear_write_event(icp_socket);
	g2int_clear_close_event(icp_socket);
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)36L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)36L)) = svref_new_value;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)16L)) = svref_new_value;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)38L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)38L)) = svref_new_value;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)47L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)47L)) = svref_new_value;
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
	    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
		    (SI_Long)9L));
	    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)35L)) = svref_new_value;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)51L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)51L)) = svref_new_value;
	element = g2int_memq_function(icp_socket,
		G2int_icp_sockets_waiting_for_icp_message_processing);
	if (element)
	    M_CAR(element) = Nil;
	if (output_port) {
	    cons_qm = ISVREF(output_port,(SI_Long)18L);
	    if (cons_qm) {
		M_CAR(cons_qm) = Nil;
		SVREF(output_port,FIX((SI_Long)18L)) = Nil;
	    }
	}
	if (EQ(connection_type,Qg2int_generic)) {
	    if (handle) {
		g2ext_network_close(IFIX(handle));
		g2int_register_socket_to_handle(Nil,handle);
	    }
	}
	else if (EQ(connection_type,Qg2int_localnet)) {
	    corresponding_localnet_socket = ISVREF(icp_socket,(SI_Long)42L);
	    SVREF(icp_socket,FIX((SI_Long)42L)) = Nil;
	    if (corresponding_localnet_socket) {
		SVREF(corresponding_localnet_socket,FIX((SI_Long)42L)) = Nil;
		g2int_enqueue_close_event(corresponding_localnet_socket,
			G2int_network_status_success);
	    }
	}
    }
    return VALUES_1(Nil);
}

Object G2int_icp_sockets_to_be_reclaimed = UNBOUND;

Object G2int_icp_socket_for_handle_icp_messages = UNBOUND;

/* ICP-SOCKET-NOTIFIES-USER-ON-ERROR-P */
Object g2int_icp_socket_notifies_user_on_error_p(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(40,9);
    return VALUES_1(Nil);
}

static Object Qg2int_shutdown;     /* shutdown */

/* FINALIZE-AND-RECLAIM-ICP-SOCKET */
Object g2int_finalize_and_reclaim_icp_socket(icp_socket)
    Object icp_socket;
{
    Object reason_for_shutdown_qm;

    x_note_fn_call(40,10);
    if ( !TRUEP(g2int_memq_function(icp_socket,G2int_active_icp_sockets)))
	return VALUES_1(Nil);
    if (EQ(icp_socket,G2int_icp_socket_for_handle_icp_messages))
	G2int_icp_socket_for_handle_icp_messages = Nil;
    G2int_active_icp_sockets = g2int_delete_gensym_element_1(icp_socket,
	    G2int_active_icp_sockets);
    reason_for_shutdown_qm = ISVREF(icp_socket,(SI_Long)9L);
    g2int_execute_icp_connection_loss_callbacks(icp_socket, 
	    !TRUEP(reason_for_shutdown_qm) ? T : Nil);
    if (g2int_text_string_p(reason_for_shutdown_qm)) {
	if (g2int_icp_socket_notifies_user_on_error_p(icp_socket))
	    g2int_notify_user_at_console(2,string_constant,
		    reason_for_shutdown_qm);
	g2int_reclaim_text_string(reason_for_shutdown_qm);
	SVREF(icp_socket,FIX((SI_Long)9L)) = Qg2int_shutdown;
    }
    G2int_icp_sockets_to_be_reclaimed = g2int_gensym_cons_1(icp_socket,
	    G2int_icp_sockets_to_be_reclaimed);
    return VALUES_1(Nil);
}

Object G2int_inhibit_icp_socket_reclamation = UNBOUND;

static Object Qg2int_gensym;       /* gensym */

/* RECLAIM-ICP-SOCKETS */
Object g2int_reclaim_icp_sockets()
{
    Object icp_socket, gensym_pop_store, cons_1, next_cons, cdr_new_value;

    x_note_fn_call(40,11);
    if ( !TRUEP(G2int_inhibit_icp_socket_reclamation)) {
	icp_socket = Nil;
      next_loop:
	if ( !TRUEP(G2int_icp_sockets_to_be_reclaimed))
	    goto end_loop;
	gensym_pop_store = Nil;
	cons_1 = G2int_icp_sockets_to_be_reclaimed;
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
	G2int_icp_sockets_to_be_reclaimed = next_cons;
	icp_socket = gensym_pop_store;
	g2int_reclaim_icp_socket(icp_socket);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

Object G2int_starscheduler_enabledqmstar = UNBOUND;

/* SCHEDULER-ENABLED-P */
Object g2int_scheduler_enabled_p()
{
    x_note_fn_call(40,12);
    return VALUES_1(G2int_starscheduler_enabledqmstar);
}

/* RUN-SCHEDULER-FOR-CURRENT-SYSTEM */
Object g2int_run_scheduler_for_current_system()
{
    Object scheduler_enabled_qm;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(40,13);
    SAVE_STACK();
    display_events_were_enabled = (SI_Long)0L != ne_display_events_enabled();
    ne_disable_display_events();
    if (PUSH_UNWIND_PROTECT(0)) {
	scheduler_enabled_qm = Nil;
	PUSH_SPECIAL(G2int_starscheduler_enabledqmstar,scheduler_enabled_qm,0);
	  SAVE_VALUES(g2int_run_one_gsi_scheduler_cycle());
	POP_SPECIAL();
    }
    POP_UNWIND_PROTECT(0);
    if (display_events_were_enabled)
	ne_enable_display_events();
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qg2int_handle_icp_messages;  /* handle-icp-messages */

/* GET-PENDING-NETWORK-EVENTS */
Object g2int_get_pending_network_events()
{
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(40,14);
    SAVE_STACK();
    if ( !TRUEP(G2int_starscheduler_enabledqmstar)) {
	if (g2int_g2_event_ready_p()) {
	    if (PUSH_UNWIND_PROTECT(1)) {
		if (PUSH_CATCH(Qg2int_handle_icp_messages,0)) {
		  next_loop:
		    g2int_g2_event_cycle_handling_windows_quit();
		    if ( !TRUEP(g2int_g2_event_ready_p()))
			goto end_loop;
		    goto next_loop;
		  end_loop:;
		}
		POP_CATCH(0);
	    }
	    POP_UNWIND_PROTECT(1);
	    if (G2int_icp_socket_for_handle_icp_messages && 
		    FIXNUM_EQ(ISVREF(G2int_icp_socket_for_handle_icp_messages,
		    (SI_Long)15L),G2int_icp_connection_closed))
		g2int_finalize_and_reclaim_icp_socket(G2int_icp_socket_for_handle_icp_messages);
	    CONTINUE_UNWINDING(1);
	}
    }
    RESTORE_STACK();
    return VALUES_1(Nil);
}

Object G2int_inside_handle_event = UNBOUND;

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* HANDLE-READ-EVENT-FUNCTION */
Object g2int_handle_read_event_function(socket_1,error_code,block_p)
    Object socket_1, error_code, block_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(40,15);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)20L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    gensymed_symbol_3 = block_p;
    return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3));
}

/* HANDLE-WRITE-EVENT-FUNCTION */
Object g2int_handle_write_event_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(40,16);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)21L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-CONNECT-FUNCTION */
Object g2int_handle_network_connect_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(40,17);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)22L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-ACCEPT-FUNCTION */
Object g2int_handle_network_accept_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(40,18);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)23L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-CLOSE-FUNCTION */
Object g2int_handle_network_close_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(40,19);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)24L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-G2-RESET-FUNCTION */
Object g2int_handle_g2_reset_function(socket_1)
    Object socket_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(40,20);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)25L);
    gensymed_symbol_1 = socket_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object string_constant_1;   /* "Unknown event code ~d seen." */

/* HANDLE-EVENT-INTERNAL */
Object g2int_handle_event_internal(event_code,event_socket_handle,
	    event_status_code)
    Object event_code, event_socket_handle, event_status_code;
{
    Object inside_handle_event, temp, socket_1, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    char gensymed_symbol_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(40,21);
    inside_handle_event = T;
    PUSH_SPECIAL(G2int_inside_handle_event,inside_handle_event,0);
      if (IFIX(g2int_rule_invocation_updates_needed_p()) == (SI_Long)1L)
	  g2int_cache_deferred_rule_invocation_indices();
      g2int_reclaim_icp_sockets();
      temp = event_code;
      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	      FIX((SI_Long)127L))))
	  g2int_notify_user_at_console(2,string_constant_1,event_code);
      else
	  switch (INTEGER_TO_CHAR(temp)) {
	    case 1:
	    case 8:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	      socket_1 = g2int_lookup_socket_from_handle(event_socket_handle);
	      if ( !TRUEP(socket_1));
	      else {
		  temp = event_code;
		  if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
			  FIXNUM_LE(temp,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp)) {
			case 1:
			case 8:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)20L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  gensymed_symbol_3 = IFIX(event_code) == (SI_Long)8L;
			  inline_funcall_3(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2,
				  gensymed_symbol_3 ? T : Nil);
			  break;
			case 2:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)21L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 3:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)22L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 4:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)23L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 5:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)24L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			default:
			  break;
		      }
	      }
	      break;
	    case 6:
	      if (g2int_scheduler_enabled_p())
		  g2int_run_scheduler_for_current_system();
	      break;
	    case 7:
	      g2int_handle_display_event();
	      break;
	    case -1:
	      g2int_signal_gsi_network_error(event_socket_handle,
		      event_status_code);
	      break;
	    default:
	      g2int_notify_user_at_console(2,string_constant_1,event_code);
	      break;
	  }
      temp = event_code;
      if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	      FIX((SI_Long)127L))))
	  switch (INTEGER_TO_CHAR(temp)) {
	    case 1:
	    case 8:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	      break;
	    default:
	      break;
	  }
      if (G2int_starscheduler_enabledqmstar)
	  g2int_enqueue_scheduler_events_if_necessary(Nil);
      temp = FIX((SI_Long)0L);
      g2int_reclaim_icp_sockets();
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

static Object Qg2int_handle_read_event_function;  /* handle-read-event-function */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* ENQUEUE-READ-EVENT */
Object g2int_enqueue_read_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11;
    Object current_task_schedule_modify_arg_12, old_structure_being_reclaimed;
    Object temp, def_structure_schedule_task_variable, task, ctask, p, v, q;
    Object gensymed_symbol, def_structure_queue_element_variable;
    Object gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(40,22);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,G2int_current_schedule_task)))) {
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_handle_read_event_function);
	current_task_schedule_modify_arg_11 = icp_socket;
	current_task_schedule_modify_arg_12 = network_error_code;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_handle_read_event_function;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)3L);
	SVREF(task,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	SVREF(task,FIX((SI_Long)12L)) = current_task_schedule_modify_arg_12;
	SVREF(task,FIX((SI_Long)13L)) = Nil;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
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
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)43L)) = task;
    }
    return VALUES_1(Nil);
}

/* CLEAR-READ-EVENT */
Object g2int_clear_read_event(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(40,23);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
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
    SVREF(icp_socket,FIX((SI_Long)43L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* HANDLE-READ-EVENT-FOR-ICP-SOCKET */
Object g2int_handle_read_event_for_icp_socket(icp_socket,
	    network_error_code,block_p)
    Object icp_socket, network_error_code, block_p;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(40,24);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
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
    SVREF(icp_socket,FIX((SI_Long)43L)) = svref_new_value;
    if (EQ(Qg2int_localnet,ISVREF(icp_socket,(SI_Long)1L)))
	return g2int_handle_localnet_read(icp_socket);
    else
	return g2int_handle_network_read(icp_socket,network_error_code,
		block_p);
}

static Object Qg2int_handle_write_event_function;  /* handle-write-event-function */

/* ENQUEUE-WRITE-EVENT */
Object g2int_enqueue_write_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11;
    Object current_task_schedule_modify_arg_12, old_structure_being_reclaimed;
    Object temp, def_structure_schedule_task_variable, task, ctask, p, v, q;
    Object gensymed_symbol, def_structure_queue_element_variable;
    Object gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(40,25);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,G2int_current_schedule_task)))) {
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_handle_write_event_function);
	current_task_schedule_modify_arg_11 = icp_socket;
	current_task_schedule_modify_arg_12 = network_error_code;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_handle_write_event_function;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	SVREF(task,FIX((SI_Long)12L)) = current_task_schedule_modify_arg_12;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
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
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)44L)) = task;
    }
    return VALUES_1(Nil);
}

/* CLEAR-WRITE-EVENT */
Object g2int_clear_write_event(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(40,26);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
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
    SVREF(icp_socket,FIX((SI_Long)44L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* HANDLE-WRITE-EVENT-FOR-ICP-SOCKET */
Object g2int_handle_write_event_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(40,27);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
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
    SVREF(icp_socket,FIX((SI_Long)44L)) = svref_new_value;
    if (EQ(Qg2int_localnet,ISVREF(icp_socket,(SI_Long)1L)))
	return g2int_handle_localnet_write(icp_socket);
    else
	return g2int_handle_network_write(icp_socket,network_error_code);
}

static Object Qg2int_handle_close_event;  /* handle-close-event */

/* ENQUEUE-CLOSE-EVENT */
Object g2int_enqueue_close_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11;
    Object current_task_schedule_modify_arg_12, old_structure_being_reclaimed;
    Object temp, def_structure_schedule_task_variable, task, ctask, p, v, q;
    Object gensymed_symbol, def_structure_queue_element_variable;
    Object gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(40,28);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,G2int_current_schedule_task)))) {
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_handle_close_event);
	current_task_schedule_modify_arg_11 = icp_socket;
	current_task_schedule_modify_arg_12 = network_error_code;
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_handle_close_event;
	SVREF(task,FIX((SI_Long)8L)) = current_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)11L)) = current_task_schedule_modify_arg_11;
	SVREF(task,FIX((SI_Long)12L)) = current_task_schedule_modify_arg_12;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = G2int_system_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? G2int_current_task_queue_vector : 
		G2int_deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	gensymed_symbol = ISVREF(q,(SI_Long)1L);
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
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(q,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (ctask && FIXNUM_LT(p,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = p;
	SVREF(icp_socket,FIX((SI_Long)45L)) = task;
    }
    return VALUES_1(Nil);
}

/* CLEAR-CLOSE-EVENT */
Object g2int_clear_close_event(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(40,29);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
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
    SVREF(icp_socket,FIX((SI_Long)45L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* HANDLE-CLOSE-EVENT */
Object g2int_handle_close_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(40,30);
    if (icp_socket) {
	schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
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
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
	}
	svref_new_value = Nil;
	SVREF(icp_socket,FIX((SI_Long)45L)) = svref_new_value;
	if (EQ(Qg2int_localnet,ISVREF(icp_socket,(SI_Long)1L)))
	    g2int_handle_localnet_close(icp_socket);
	else {
	    gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)24L);
	    gensymed_symbol_1 = icp_socket;
	    gensymed_symbol_2 = network_error_code;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	}
    }
    return VALUES_1(Nil);
}

/* HANDLE-DISPLAY-EVENT */
Object g2int_handle_display_event()
{
    x_note_fn_call(40,31);
    return VALUES_1(Nil);
}

Object G2int_during_ffi_callqm = UNBOUND;

static Object Qg2int_in_progress;  /* in-progress */

static Object Qg2int_no_data_available;  /* no-data-available */

static Object Qg2int_in_progress_with_data;  /* in-progress-with-data */

/* CONTINUE-READING-FROM-ICP-SOCKET */
Object g2int_continue_reading_from_icp_socket(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(40,32);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    temp = ISVREF(icp_input_port,(SI_Long)4L);
    if (EQ(temp,Qnil)) {
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)20L);
	gensymed_symbol_1 = icp_socket;
	gensymed_symbol_2 = G2int_network_status_success;
	gensymed_symbol_3 = Nil;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else if (EQ(temp,Qg2int_in_progress))
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Qg2int_no_data_available;
    else if (EQ(temp,Qg2int_in_progress_with_data)) {
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)20L);
	gensymed_symbol_1 = icp_socket;
	gensymed_symbol_2 = G2int_network_status_success;
	gensymed_symbol_3 = T;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    return VALUES_1(Nil);
}

static Object Qg2int_end_of_message_group;  /* end-of-message-group */

/* HANDLE-NETWORK-READ */
Object g2int_handle_network_read(icp_socket,network_error_code,block_p)
    Object icp_socket, network_error_code, block_p;
{
    Object socket_handle, icp_input_port, temp, connection_state;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, icp_buffer;
    Object octets_read_or_status, incff_1_arg, svref_new_value, end, copy;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(40,33);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    if ( !FIXNUM_EQ(network_error_code,G2int_network_status_success)) {
	temp = G2int_icp_read_event_error;
	if (g2int_icp_error_on_socket(4,icp_socket,temp,network_error_code,
		g2int_network_get_last_error_string(socket_handle))) {
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
    }
    connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(connection_state,G2int_icp_connection_running) || 
	    FIXNUM_EQ(connection_state,
	    G2int_icp_connection_awaiting_acknowledgement))) {
	if (g2int_icp_error_on_socket(3,icp_socket,
		G2int_icp_received_data_on_invalid_socket,Nil)) {
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
    }
    if ( !TRUEP(block_p)) {
	if (ISVREF(icp_input_port,(SI_Long)4L)) {
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	    g2int_execute_icp_read_callbacks(icp_socket,T);
	}
    }
    else {
	temp = ISVREF(icp_input_port,(SI_Long)4L);
	if (EQ(temp,Qg2int_in_progress)) {
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = 
		    Qg2int_in_progress_with_data;
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
	else
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = Qg2int_in_progress;
    }
    outer_with_icp_buffer_coelescing_scope_qm = 
	    G2int_with_icp_buffer_coelescing_scopeqm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL(G2int_with_icp_buffer_coelescing_scopeqm,with_icp_buffer_coelescing_scope_qm,
	    0);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
      icp_buffer = Nil;
      octets_read_or_status = Nil;
    next_loop:
      temp = ISVREF(icp_input_port,(SI_Long)7L);
      if (temp);
      else {
	  temp = 
		  g2int_make_icp_buffer_internal_1(g2int_make_variable_fill_icp_buffer());
	  SVREF(icp_input_port,FIX((SI_Long)7L)) = temp;
      }
      icp_buffer = temp;
      octets_read_or_status = FIX(g2ext_network_read(IFIX(socket_handle),
	      UBYTE_16_SARRAY_TO_USHORT_PTR(ISVREF(icp_buffer,
	      (SI_Long)4L)),IFIX(ISVREF(icp_buffer,(SI_Long)3L)),
	      (SI_Long)4096L));
      if (IFIX(octets_read_or_status) > (SI_Long)0L) {
	  SVREF(icp_socket,FIX((SI_Long)7L)) = T;
	  incff_1_arg = octets_read_or_status;
	  svref_new_value = FIXNUM_ADD(ISVREF(icp_buffer,(SI_Long)3L),
		  incff_1_arg);
	  SVREF(icp_buffer,FIX((SI_Long)3L)) = svref_new_value;
	  end = ISVREF(icp_buffer,(SI_Long)3L);
	  if ( !((SI_Long)0L == ((SI_Long)1L & IFIX(end)) && IFIX(end) > 
		  (SI_Long)4032L)) {
	      copy = g2int_copy_icp_buffer(icp_buffer);
	      SVREF(copy,FIX((SI_Long)2L)) = end;
	      SVREF(copy,FIX((SI_Long)3L)) = end;
	      SVREF(icp_buffer,FIX((SI_Long)1L)) = copy;
	  }
	  if (EQ(Qg2int_end_of_message_group,
		  g2int_enqueue_next_icp_buffer_if_any(icp_input_port))) {
	      if ( 
		      !TRUEP(g2int_call_or_schedule_handle_queued_icp_messages(icp_socket,
		      Nil))) {
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_handle_network_read;
	      }
	      if (ISVREF(icp_input_port,(SI_Long)4L)) {
		  SVREF(icp_input_port,FIX((SI_Long)4L)) = 
			  Qg2int_no_data_available;
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_handle_network_read;
	      }
	  }
      }
      else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_blocked_value)) {
	  SVREF(icp_input_port,FIX((SI_Long)4L)) = T;
	  g2int_execute_icp_read_callbacks(icp_socket,Nil);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_handle_network_read;
      }
      else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_eof_value)) {
	  gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	  gensymed_symbol = 
		  ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		  Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		  (SI_Long)9L),(SI_Long)24L);
	  gensymed_symbol_1 = icp_socket;
	  gensymed_symbol_2 = G2int_network_status_success;
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_handle_network_read;
      }
      else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_error_value)) {
	  temp = G2int_icp_read_call_returned_error;
	  temp_1 = FIX(ne_last_error_code(IFIX(socket_handle)));
	  if (g2int_icp_error_on_socket(4,icp_socket,temp,temp_1,
		  g2int_network_get_last_error_string(socket_handle))) {
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_handle_network_read;
	  }
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
    POP_SPECIAL();
    result = VALUES_1(temp);
  end_handle_network_read:
    return result;
}

/* HANDLE-LOCALNET-READ */
Object g2int_handle_localnet_read(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, connection_state;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, enqueue_result;
    Declare_special(1);

    x_note_fn_call(40,34);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(connection_state,G2int_icp_connection_running) || 
	    FIXNUM_EQ(connection_state,
	    G2int_icp_connection_awaiting_acknowledgement))) {
	if (g2int_icp_error_on_socket(3,icp_socket,
		G2int_icp_received_data_on_invalid_socket,Nil))
	    return VALUES_1(Nil);
    }
    if (ISVREF(icp_input_port,(SI_Long)4L)) {
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	g2int_execute_icp_read_callbacks(icp_socket,T);
    }
    SVREF(icp_socket,FIX((SI_Long)7L)) = T;
    outer_with_icp_buffer_coelescing_scope_qm = 
	    G2int_with_icp_buffer_coelescing_scopeqm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL(G2int_with_icp_buffer_coelescing_scopeqm,with_icp_buffer_coelescing_scope_qm,
	    0);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
      enqueue_result = Nil;
    next_loop:
      connection_state = ISVREF(icp_socket,(SI_Long)15L);
      if ( !(FIXNUM_EQ(connection_state,G2int_icp_connection_running) || 
	      FIXNUM_EQ(connection_state,
	      G2int_icp_connection_awaiting_acknowledgement) ? 
	      TRUEP(ISVREF(icp_input_port,(SI_Long)7L)) : TRUEP(Nil)))
	  goto end_loop;
      enqueue_result = g2int_enqueue_next_icp_buffer_if_any(icp_input_port);
      if ( !( !EQ(Qg2int_end_of_message_group,enqueue_result) || 
	      g2int_call_or_schedule_handle_queued_icp_messages(icp_socket,
	      Nil)))
	  goto end_loop;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (G2int_icp_output_ports_to_flush)
	      g2int_flush_icp_output_ports();
      }
    POP_SPECIAL();
    if ( !TRUEP(ISVREF(icp_input_port,(SI_Long)7L)))
	SVREF(icp_input_port,FIX((SI_Long)4L)) = T;
    return VALUES_1(Nil);
}

/* HANDLE-NETWORK-WRITE */
Object g2int_handle_network_write(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object socket_handle, temp;

    x_note_fn_call(40,35);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)4L),(SI_Long)1L);
    if ( !FIXNUM_EQ(network_error_code,G2int_network_status_success)) {
	temp = G2int_icp_write_event_error;
	g2int_icp_error_on_socket(4,icp_socket,temp,network_error_code,
		g2int_network_get_last_error_string(socket_handle));
	return VALUES_1(Nil);
    }
    temp = g2int_handle_icp_write(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-LOCALNET-WRITE */
Object g2int_handle_localnet_write(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(40,36);
    temp = g2int_handle_icp_write(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-ICP-WRITE */
Object g2int_handle_icp_write(icp_socket)
    Object icp_socket;
{
    Object icp_output_port, callbacks, callbacks_old_value, temp;
    Object callback_function;

    x_note_fn_call(40,37);
    icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
    if ( !TRUEP(ISVREF(icp_output_port,(SI_Long)4L)))
	return VALUES_1(Nil);
    SVREF(icp_output_port,FIX((SI_Long)4L)) = Nil;
    callbacks = ISVREF(icp_socket,(SI_Long)13L);
  next_loop:
    g2int_transmit_icp_output_if_ready(icp_output_port,T);
    if (ISVREF(icp_output_port,(SI_Long)4L) ||  
	    !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running) ||  !TRUEP(callbacks)) {
	if ( !TRUEP(callbacks))
	    g2ext_note_null_write_callbacks();
	return VALUES_1(Nil);
    }
    callbacks_old_value = callbacks;
    temp = FIRST(callbacks_old_value);
    callbacks = REST(callbacks_old_value);
    callback_function = temp;
    FUNCALL_2(callback_function,icp_socket,T);
    if (ISVREF(icp_output_port,(SI_Long)4L) ||  
	    !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* HANDLE-NETWORK-CONNECT-FOR-ICP-SOCKET */
Object g2int_handle_network_connect_for_icp_socket(icp_socket,
	    network_error_code)
    Object icp_socket, network_error_code;
{
    Object socket_handle, temp;

    x_note_fn_call(40,38);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    if ( !FIXNUM_EQ(network_error_code,G2int_network_status_success)) {
	temp = G2int_icp_connect_event_error;
	g2int_icp_error_on_socket(4,icp_socket,temp,network_error_code,
		g2int_network_get_last_error_string(socket_handle));
	return VALUES_1(Nil);
    }
    return g2int_handle_icp_connect(icp_socket);
}

/* HANDLE-ICP-CONNECT */
Object g2int_handle_icp_connect(icp_socket)
    Object icp_socket;
{
    Object svref_new_value, temp;

    x_note_fn_call(40,39);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_connect_in_progress)) {
	g2int_icp_error_on_socket(2,icp_socket,
		G2int_icp_connect_on_invalid_socket);
	return VALUES_1(Nil);
    }
    svref_new_value = G2int_icp_connection_running;
    SVREF(icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    g2int_send_initial_icp_version_info(icp_socket,T);
    temp =  !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_closed) ? 
	    g2int_execute_icp_connect_callbacks(icp_socket) : Nil;
    return VALUES_1(temp);
}

Object G2int_default_accept_timeout = UNBOUND;

/* HANDLE-NETWORK-ACCEPT-FOR-ICP-SOCKET */
Object g2int_handle_network_accept_for_icp_socket(icp_socket,
	    network_error_code)
    Object icp_socket, network_error_code;
{
    Object listener_handle, temp, new_socket;
    SI_Long new_socket_handle;

    x_note_fn_call(40,40);
    listener_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_socket_listening)) {
	g2int_icp_error_on_socket(2,icp_socket,
		G2int_icp_accept_on_invalid_socket);
	return VALUES_1(Nil);
    }
    if ( !FIXNUM_EQ(network_error_code,G2int_network_status_success)) {
	temp = G2int_icp_accept_event_error;
	g2int_icp_error_on_socket(4,icp_socket,temp,network_error_code,
		g2int_network_get_last_error_string(listener_handle));
	return VALUES_1(Nil);
    }
    new_socket_handle = g2ext_network_accept(IFIX(listener_handle));
    new_socket = Nil;
    if (new_socket_handle > (SI_Long)0L) {
	temp = g2int_get_accept_pathname(FIX(new_socket_handle));
	new_socket = g2int_make_and_install_network_icp_socket(6,
		FIX(new_socket_handle),FIX(new_socket_handle),temp,T,
		listener_handle,G2int_default_accept_timeout);
	return g2int_execute_icp_accept_callbacks(icp_socket,new_socket);
    }
    else if (new_socket_handle == IFIX(G2int_ne_blocked_value))
	return VALUES_1(Nil);
    else {
	temp = G2int_icp_accept_failure;
	return g2int_icp_error_on_socket(4,icp_socket,temp,
		FIX(new_socket_handle),
		g2int_network_get_last_error_string(listener_handle));
    }
}

/* HANDLE-NETWORK-CLOSE-FOR-ICP-SOCKET */
Object g2int_handle_network_close_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    x_note_fn_call(40,41);
    if ( !FIXNUM_EQ(network_error_code,G2int_network_status_success)) {
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		G2int_icp_connection_awaiting_acknowledgement))
	    g2int_icp_error_on_socket(2,icp_socket,G2int_icp_shutdown_aborted);
	else
	    g2int_icp_error_on_socket(2,icp_socket,G2int_icp_connection_reset);
	return VALUES_1(Nil);
    }
    return g2int_handle_icp_close(icp_socket);
}

/* HANDLE-LOCALNET-CLOSE */
Object g2int_handle_localnet_close(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(40,42);
    temp = g2int_handle_icp_close(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-ICP-CLOSE */
Object g2int_handle_icp_close(icp_socket)
    Object icp_socket;
{
    Object icp_socket_connection_state, temp;

    x_note_fn_call(40,43);
    icp_socket_connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(icp_socket_connection_state,
	    G2int_icp_connection_awaiting_acknowledgement) || 
	    EQ(Qg2int_localnet,ISVREF(icp_socket,(SI_Long)1L)))) {
	g2int_icp_error_on_socket(2,icp_socket,
		G2int_icp_connection_closed_error);
	return VALUES_1(Nil);
    }
    temp = g2int_shutdown_icp_socket_connection(1,icp_socket);
    return VALUES_1(temp);
}

/* NOTIFY-SOCKETS-OF-G2-RESET */
Object g2int_notify_sockets_of_g2_reset()
{
    Object handle, socket_1, ab_loop_list_, ab_loop_desetq_, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(40,44);
    handle = Nil;
    socket_1 = Nil;
    ab_loop_list_ = G2int_handle_to_socket_mapping;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    handle = CAR(ab_loop_desetq_);
    socket_1 = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (socket_1) {
	gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)25L);
	gensymed_symbol_1 = socket_1;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* HANDLE-G2-RESET-FOR-ICP-SOCKET */
Object g2int_handle_g2_reset_for_icp_socket(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(40,45);
    return VALUES_1(Nil);
}

void netevent_INIT()
{
    Object svref_arg_1, svref_new_value, handle_read_event_for_icp_socket;
    Object handle_write_event_for_icp_socket;
    Object handle_network_connect_for_icp_socket;
    Object handle_network_accept_for_icp_socket;
    Object handle_network_close_for_icp_socket, handle_g2_reset_for_icp_socket;
    Object Qg2int_icp_socket, Qg2int_handle_g2_reset, AB_package;
    Object Qg2int_handle_network_close, Qg2int_handle_network_accept;
    Object Qg2int_handle_network_connect, Qg2int_handle_write_event;
    Object Qg2int_handle_read_event, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_1, list_constant, array_constant_18;
    Object array_constant_17, array_constant_16, array_constant_15;
    Object array_constant_14, array_constant_13, array_constant_12;
    Object array_constant_11, array_constant_10, array_constant_9;
    Object array_constant_8, array_constant_7, array_constant_6;
    Object array_constant_5, array_constant_4, array_constant_3;
    Object array_constant_2, string_constant_18;
    Object Qg2_defstruct_structure_name_error_code_g2_struct;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object string_constant_2;

    x_note_fn_call(40,46);
    SET_PACKAGE("AB");
    G2int_icp_error_table = make_array(1,FIX((SI_Long)17L));
    G2int_icp_success = FIX((SI_Long)0L);
    string_constant_2 = STATIC_STRING("Operation was successful.");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_success,
	    string_constant_2);
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
    G2int_icp_read_event_error = FIX((SI_Long)1L);
    string_constant_3 = 
	    STATIC_STRING("Read event occurred on socket ~a, network error ~d, \"~a\"");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_3);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
    G2int_icp_received_data_on_invalid_socket = FIX((SI_Long)2L);
    string_constant_4 = 
	    STATIC_STRING("Data present on socket (~a) that is not in a readable state.");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_4);
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
    G2int_icp_read_call_returned_error = FIX((SI_Long)3L);
    string_constant_5 = 
	    STATIC_STRING("Call to network-read on socket ~a returned error ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_5);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    G2int_icp_write_event_error = FIX((SI_Long)4L);
    string_constant_6 = 
	    STATIC_STRING("Write event occurred on socket ~a with error ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_6);
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    G2int_icp_wrote_data_on_invalid_socket = FIX((SI_Long)5L);
    string_constant_7 = 
	    STATIC_STRING("Socket write event occurred on socket ~a, which is not in a writable state.~%");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_7);
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    G2int_icp_write_call_returned_error = FIX((SI_Long)6L);
    string_constant_8 = 
	    STATIC_STRING("Call to network-write on socket ~a returned error ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_8);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    G2int_icp_connect_event_error = FIX((SI_Long)7L);
    string_constant_9 = 
	    STATIC_STRING("Error during connect on socket ~a: ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_9);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    G2int_icp_connect_on_invalid_socket = FIX((SI_Long)8L);
    string_constant_10 = 
	    STATIC_STRING("Server connection finalized on a socket that\'s not connecting.");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_10);
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    G2int_icp_accept_on_invalid_socket = FIX((SI_Long)9L);
    string_constant_11 = 
	    STATIC_STRING("Client connection on a non-listener socket.");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_11);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    G2int_icp_accept_event_error = FIX((SI_Long)10L);
    string_constant_12 = 
	    STATIC_STRING("Error during accept of client connection on listener socket ~a, error was: ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_12);
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
    G2int_icp_close_event_error = FIX((SI_Long)11L);
    string_constant_13 = 
	    STATIC_STRING("Error during close by peer on socket ~a: ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_13);
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = svref_new_value;
    G2int_icp_connection_closed_error = FIX((SI_Long)12L);
    string_constant_14 = 
	    STATIC_STRING("Connection closed by peer for ICP socket ~a");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_14);
    SVREF(svref_arg_1,FIX((SI_Long)12L)) = svref_new_value;
    G2int_icp_shutdown_aborted = FIX((SI_Long)13L);
    string_constant_15 = 
	    STATIC_STRING("ICP connection shutdown handshake aborted by peer on socket ~a");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_15);
    SVREF(svref_arg_1,FIX((SI_Long)13L)) = svref_new_value;
    G2int_icp_connection_reset = FIX((SI_Long)14L);
    string_constant_16 = 
	    STATIC_STRING("ICP connection reset by peer on socket ~a");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_16);
    SVREF(svref_arg_1,FIX((SI_Long)14L)) = svref_new_value;
    G2int_icp_accept_failure = FIX((SI_Long)15L);
    string_constant_17 = 
	    STATIC_STRING("network_accept() call failed, for socket ~a, error code was: ~d, \"~a\".");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_fatal,
	    string_constant_17);
    SVREF(svref_arg_1,FIX((SI_Long)15L)) = svref_new_value;
    G2int_icp_error_obtaining_error_string = FIX((SI_Long)16L);
    string_constant_18 = 
	    STATIC_STRING("Could not obtain error string for platform-specific network error, on socket ~a.");
    svref_arg_1 = G2int_icp_error_table;
    svref_new_value = g2int_make_error_code_1(G2int_error_severity_warning,
	    string_constant_18);
    SVREF(svref_arg_1,FIX((SI_Long)16L)) = svref_new_value;
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)17L));
    array_constant_2 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_error_code_g2_struct = 
	    STATIC_SYMBOL("ERROR-CODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    ISASET_1(array_constant_2,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_2,(SI_Long)1L,string_constant_2);
    ISASET_1(array_constant_2,(SI_Long)2L,FIX((SI_Long)0L));
    array_constant_3 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_3,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_3,(SI_Long)1L,string_constant_3);
    ISASET_1(array_constant_3,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_4 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_4,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_4,(SI_Long)1L,string_constant_4);
    ISASET_1(array_constant_4,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_5 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_5,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_5,(SI_Long)1L,string_constant_5);
    ISASET_1(array_constant_5,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_6 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_6,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_6,(SI_Long)1L,string_constant_6);
    ISASET_1(array_constant_6,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_7 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_7,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_7,(SI_Long)1L,string_constant_7);
    ISASET_1(array_constant_7,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_8 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_8,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_8,(SI_Long)1L,string_constant_8);
    ISASET_1(array_constant_8,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_9 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_9,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_9,(SI_Long)1L,string_constant_9);
    ISASET_1(array_constant_9,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_10 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_10,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_10,(SI_Long)1L,string_constant_10);
    ISASET_1(array_constant_10,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_11 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_11,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_11,(SI_Long)1L,string_constant_11);
    ISASET_1(array_constant_11,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_12 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_12,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_12,(SI_Long)1L,string_constant_12);
    ISASET_1(array_constant_12,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_13 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_13,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_13,(SI_Long)1L,string_constant_13);
    ISASET_1(array_constant_13,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_14 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_14,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_14,(SI_Long)1L,string_constant_14);
    ISASET_1(array_constant_14,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_15 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_15,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_15,(SI_Long)1L,string_constant_15);
    ISASET_1(array_constant_15,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_16 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_16,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_16,(SI_Long)1L,string_constant_16);
    ISASET_1(array_constant_16,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_17 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_17,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_17,(SI_Long)1L,string_constant_17);
    ISASET_1(array_constant_17,(SI_Long)2L,FIX((SI_Long)3L));
    array_constant_18 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)3L));
    ISASET_1(array_constant_18,(SI_Long)0L,
	    Qg2_defstruct_structure_name_error_code_g2_struct);
    ISASET_1(array_constant_18,(SI_Long)1L,string_constant_18);
    ISASET_1(array_constant_18,(SI_Long)2L,FIX((SI_Long)2L));
    ISASET_1(array_constant,(SI_Long)0L,array_constant_2);
    ISASET_1(array_constant,(SI_Long)1L,array_constant_3);
    ISASET_1(array_constant,(SI_Long)2L,array_constant_4);
    ISASET_1(array_constant,(SI_Long)3L,array_constant_5);
    ISASET_1(array_constant,(SI_Long)4L,array_constant_6);
    ISASET_1(array_constant,(SI_Long)5L,array_constant_7);
    ISASET_1(array_constant,(SI_Long)6L,array_constant_8);
    ISASET_1(array_constant,(SI_Long)7L,array_constant_9);
    ISASET_1(array_constant,(SI_Long)8L,array_constant_10);
    ISASET_1(array_constant,(SI_Long)9L,array_constant_11);
    ISASET_1(array_constant,(SI_Long)10L,array_constant_12);
    ISASET_1(array_constant,(SI_Long)11L,array_constant_13);
    ISASET_1(array_constant,(SI_Long)12L,array_constant_14);
    ISASET_1(array_constant,(SI_Long)13L,array_constant_15);
    ISASET_1(array_constant,(SI_Long)14L,array_constant_16);
    ISASET_1(array_constant,(SI_Long)15L,array_constant_17);
    ISASET_1(array_constant,(SI_Long)16L,array_constant_18);
    string_constant = STATIC_STRING("~A");
    G2int_no_event = FIX((SI_Long)0L);
    G2int_read_event = FIX((SI_Long)1L);
    G2int_write_event = FIX((SI_Long)2L);
    G2int_connect_event = FIX((SI_Long)3L);
    G2int_accept_event = FIX((SI_Long)4L);
    G2int_close_event = FIX((SI_Long)5L);
    G2int_scheduler_event = FIX((SI_Long)6L);
    G2int_display_event = FIX((SI_Long)7L);
    G2int_read_and_block_event = FIX((SI_Long)8L);
    G2int_watch_event = FIX((SI_Long)9L);
    G2int_quit_event = FIX((SI_Long)10L);
    G2int_error_event = FIX((SI_Long)-1L);
    G2int_network_status_success = FIX((SI_Long)0L);
    if (G2int_network_octet_buffer_length == UNBOUND)
	G2int_network_octet_buffer_length = FIX((SI_Long)2048L);
    if (G2int_last_event_socket_handle_holder == UNBOUND)
	G2int_last_event_socket_handle_holder = make_array(3,
		FIX((SI_Long)1L),Kelement_type,Qfixnum);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)32L));
    if (G2int_last_event_status_code_holder == UNBOUND)
	G2int_last_event_status_code_holder = make_array(3,
		FIX((SI_Long)1L),Kelement_type,list_constant);
    if (G2int_handle_to_socket_mapping == UNBOUND)
	G2int_handle_to_socket_mapping = Nil;
    G2int_internal_events_handling_trigger = Nil;
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)57344L);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_generic = STATIC_SYMBOL("GENERIC",AB_package);
    Qg2int_localnet = STATIC_SYMBOL("LOCALNET",AB_package);
    if (G2int_icp_sockets_to_be_reclaimed == UNBOUND)
	G2int_icp_sockets_to_be_reclaimed = Nil;
    if (G2int_icp_socket_for_handle_icp_messages == UNBOUND)
	G2int_icp_socket_for_handle_icp_messages = Nil;
    Qg2int_shutdown = STATIC_SYMBOL("SHUTDOWN",AB_package);
    if (G2int_inhibit_icp_socket_reclamation == UNBOUND)
	G2int_inhibit_icp_socket_reclamation = Nil;
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    if (G2int_starscheduler_enabledqmstar == UNBOUND)
	G2int_starscheduler_enabledqmstar = Nil;
    Qg2int_handle_icp_messages = STATIC_SYMBOL("HANDLE-ICP-MESSAGES",
	    AB_package);
    if (G2int_inside_handle_event == UNBOUND)
	G2int_inside_handle_event = Nil;
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    string_constant_1 = STATIC_STRING("Unknown event code ~d seen.");
    Qg2int_handle_read_event_function = 
	    STATIC_SYMBOL("HANDLE-READ-EVENT-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_read_event_function,
	    STATIC_FUNCTION(g2int_handle_read_event_function,NIL,FALSE,3,3));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_handle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    Qg2int_icp_socket = STATIC_SYMBOL("ICP-SOCKET",AB_package);
    handle_read_event_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_read_event_for_icp_socket,NIL,
	    FALSE,3,3);
    g2int_record_direct_structure_method(Qg2int_handle_read_event,
	    Qg2int_icp_socket,handle_read_event_for_icp_socket);
    Qg2int_handle_write_event_function = 
	    STATIC_SYMBOL("HANDLE-WRITE-EVENT-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_write_event_function,
	    STATIC_FUNCTION(g2int_handle_write_event_function,NIL,FALSE,2,2));
    Qg2int_handle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    handle_write_event_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_write_event_for_icp_socket,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_write_event,
	    Qg2int_icp_socket,handle_write_event_for_icp_socket);
    Qg2int_handle_close_event = STATIC_SYMBOL("HANDLE-CLOSE-EVENT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_close_event,
	    STATIC_FUNCTION(g2int_handle_close_event,NIL,FALSE,2,2));
    if (G2int_during_ffi_callqm == UNBOUND)
	G2int_during_ffi_callqm = Nil;
    Qg2int_in_progress = STATIC_SYMBOL("IN-PROGRESS",AB_package);
    Qg2int_no_data_available = STATIC_SYMBOL("NO-DATA-AVAILABLE",AB_package);
    Qg2int_in_progress_with_data = STATIC_SYMBOL("IN-PROGRESS-WITH-DATA",
	    AB_package);
    Qg2int_end_of_message_group = STATIC_SYMBOL("END-OF-MESSAGE-GROUP",
	    AB_package);
    Qg2int_handle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    handle_network_connect_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_network_connect_for_icp_socket,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_network_connect,
	    Qg2int_icp_socket,handle_network_connect_for_icp_socket);
    if (G2int_default_accept_timeout == UNBOUND)
	G2int_default_accept_timeout = 
		FIX(IFIX(G2int_fixnum_time_units_per_second) * 
		(SI_Long)60L * (SI_Long)5L);
    Qg2int_handle_network_accept = STATIC_SYMBOL("HANDLE-NETWORK-ACCEPT",
	    AB_package);
    handle_network_accept_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_network_accept_for_icp_socket,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_network_accept,
	    Qg2int_icp_socket,handle_network_accept_for_icp_socket);
    Qg2int_handle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",
	    AB_package);
    handle_network_close_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_network_close_for_icp_socket,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_network_close,
	    Qg2int_icp_socket,handle_network_close_for_icp_socket);
    Qg2int_handle_g2_reset = STATIC_SYMBOL("HANDLE-G2-RESET",AB_package);
    handle_g2_reset_for_icp_socket = 
	    STATIC_FUNCTION(g2int_handle_g2_reset_for_icp_socket,NIL,FALSE,
	    1,1);
    g2int_record_direct_structure_method(Qg2int_handle_g2_reset,
	    Qg2int_icp_socket,handle_g2_reset_for_icp_socket);
}
