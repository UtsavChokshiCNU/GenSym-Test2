/* ntvnt.c
 * Input file:  netevent.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "ntvnt.h"


Object Icp_error_table = UNBOUND;

Object Icp_success = UNBOUND;

Object Icp_read_event_error = UNBOUND;

Object Icp_received_data_on_invalid_socket = UNBOUND;

Object Icp_read_call_returned_error = UNBOUND;

Object Icp_write_event_error = UNBOUND;

Object Icp_wrote_data_on_invalid_socket = UNBOUND;

Object Icp_write_call_returned_error = UNBOUND;

Object Icp_connect_event_error = UNBOUND;

Object Icp_connect_on_invalid_socket = UNBOUND;

Object Icp_accept_on_invalid_socket = UNBOUND;

Object Icp_accept_event_error = UNBOUND;

Object Icp_close_event_error = UNBOUND;

Object Icp_connection_closed_error = UNBOUND;

Object Icp_shutdown_aborted = UNBOUND;

Object Icp_connection_reset = UNBOUND;

Object Icp_accept_failure = UNBOUND;

Object Icp_error_obtaining_error_string = UNBOUND;

static Object array_constant;      /* # */

/* ICP-ERROR-ON-SOCKET */
Object icp_error_on_socket varargs_1(int, n)
{
    Object icp_socket, error_code;
    Object network_error_code, network_error_string, icp_socket_description_1;
    Object error_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(49,0);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    error_code = REQUIRED_ARG_nonrelocating();
    network_error_code = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    network_error_string = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (FIXNUM_EQ(ISVREF(ISVREF(array_constant,IFIX(error_code)),
	    (SI_Long)2L),Error_severity_fatal)) {
	icp_socket_description_1 = icp_socket_description(icp_socket);
	error_string = tformat_text_string(4,ISVREF(ISVREF(array_constant,
		IFIX(error_code)),(SI_Long)1L),icp_socket_description_1,
		network_error_code,network_error_string);
	reclaim_text_string(icp_socket_description_1);
	if (network_error_string)
	    reclaim_text_string(network_error_string);
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_socket_listening)) {
	    write_warning_message_string(FIX((SI_Long)2L),error_string);
	    reclaim_text_string(error_string);
	}
	else
	    shutdown_icp_socket_connection(2,icp_socket,error_string);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

Object No_event = UNBOUND;

Object Read_event = UNBOUND;

Object Write_event = UNBOUND;

Object Connect_event = UNBOUND;

Object Accept_event = UNBOUND;

Object Close_event = UNBOUND;

Object Scheduler_event = UNBOUND;

Object Display_event = UNBOUND;

Object Read_and_block_event = UNBOUND;

Object Watch_event = UNBOUND;

Object Quit_event = UNBOUND;

Object Error_event = UNBOUND;

Object Network_status_success = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Network_octet_buffer_length, Qnetwork_octet_buffer_length);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_socket_handle_holder, Qlast_event_socket_handle_holder);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_socket_handle, Qlast_event_socket_handle);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_status_code_holder, Qlast_event_status_code_holder);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_status_code, Qlast_event_status_code);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_status_code_0, Qlast_event_status_code_0);

DEFINE_VARIABLE_WITH_SYMBOL(Last_event_status_code_1, Qlast_event_status_code_1);

DEFINE_VARIABLE_WITH_SYMBOL(Handle_to_socket_mapping, Qhandle_to_socket_mapping);

/* G2-EVENT-READY-P */
Object g2_event_ready_p()
{
    Object temp;

    x_note_fn_call(49,1);
    temp = (SI_Long)0L != g2_event_ready((SI_Long)0L) ? T : Nil;
    return VALUES_1(temp);
}

/* G2-EVENT-CYCLE-HANDLING-WINDOWS-QUIT */
Object g2_event_cycle_handling_windows_quit()
{
    Object temp;

    x_note_fn_call(49,2);
    temp = (SI_Long)0L != g2_event_cycle((SI_Long)1L) ? 
	    shutdown_or_exit(0) : Nil;
    return VALUES_1(temp);
}

Object Internal_events_handling_trigger = UNBOUND;

/* GSI-EVENT-CYCLE-HANDLING-WINDOWS-QUIT */
Object gsi_event_cycle_handling_windows_quit()
{
    Object temp;

    x_note_fn_call(49,3);
    temp = (SI_Long)0L != g2_event_cycle((SI_Long)0L) ? 
	    shutdown_or_exit(0) : Nil;
    return VALUES_1(temp);
}

/* C-NETWORK-GET-LAST-ERROR-STRING */
Object c_network_get_last_error_string(socket_handle,output_buffer)
    Object socket_handle, output_buffer;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(49,4);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(output_buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = output_buffer;
    ne_last_error_string(IFIX(socket_handle),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

/* NETWORK-GET-LAST-ERROR-STRING */
Object network_get_last_error_string(handle)
    Object handle;
{
    Object buffer, temp;
    SI_Long length_1;

    x_note_fn_call(49,5);
    length_1 = ne_last_error_length(IFIX(handle));
    if ((SI_Long)0L < length_1) {
	buffer = obtain_simple_gensym_string(FIX(length_1));
	c_network_get_last_error_string(handle,buffer);
	temp = copy_partial_text_string(buffer,FIX(length_1));
	reclaim_gensym_string(buffer);
	return VALUES_1(temp);
    }
    else
	return copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)30L));
}

/* LOOKUP-SOCKET-FROM-HANDLE */
Object lookup_socket_from_handle(socket_handle)
    Object socket_handle;
{
    Object temp, socket_1;

    x_note_fn_call(49,6);
    temp = assq_function(socket_handle,Handle_to_socket_mapping);
    socket_1 = CDR(temp);
    return VALUES_1(socket_1);
}

/* REGISTER-SOCKET-TO-HANDLE */
Object register_socket_to_handle(socket_1,socket_handle)
    Object socket_1, socket_handle;
{
    Object mapping_qm;

    x_note_fn_call(49,7);
    mapping_qm = assq_function(socket_handle,Handle_to_socket_mapping);
    if (mapping_qm)
	M_CDR(mapping_qm) = socket_1;
    else
	Handle_to_socket_mapping = icp_cons_1(icp_cons_1(socket_handle,
		socket_1),Handle_to_socket_mapping);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_sockets_waiting_for_icp_message_processing, Qicp_sockets_waiting_for_icp_message_processing);

static Object Qgeneric;            /* generic */

static Object Qlocalnet;           /* localnet */

/* CLOSE-AND-DISCONNECT-ICP-SOCKET-HANDLE */
Object close_and_disconnect_icp_socket_handle(icp_socket)
    Object icp_socket;
{
    Object temp, input_port, output_port, handle, connection_type;
    Object gensymed_symbol, structure_being_reclaimed, svref_arg_2, element;
    Object cons_qm, corresponding_localnet_socket;
    Declare_special(1);

    x_note_fn_call(49,8);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_closed)) {
	temp = Icp_connection_closed;
	SVREF(icp_socket,FIX((SI_Long)15L)) = temp;
	input_port = ISVREF(icp_socket,(SI_Long)3L);
	output_port = ISVREF(icp_socket,(SI_Long)4L);
	handle = ISVREF(input_port,(SI_Long)1L);
	connection_type = ISVREF(icp_socket,(SI_Long)1L);
	SVREF(input_port,FIX((SI_Long)1L)) = Nil;
	if (output_port)
	    SVREF(output_port,FIX((SI_Long)1L)) = Nil;
	clear_read_event(icp_socket);
	clear_write_event(icp_socket);
	clear_close_event(icp_socket);
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)36L);
	if (CAS_SVREF(icp_socket,(SI_Long)36L,gensymed_symbol,Nil)) {
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
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)16L);
	if (CAS_SVREF(icp_socket,(SI_Long)16L,gensymed_symbol,Nil)) {
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
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
      end_2:;
	gensymed_symbol = Nil;
      next_loop_2:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)38L);
	if (CAS_SVREF(icp_socket,(SI_Long)38L,gensymed_symbol,Nil)) {
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
	    goto end_3;
	}
	goto next_loop_2;
      end_loop_2:
      end_3:;
	gensymed_symbol = Nil;
      next_loop_3:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)47L);
	if (CAS_SVREF(icp_socket,(SI_Long)47L,gensymed_symbol,Nil)) {
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
	    goto end_4;
	}
	goto next_loop_3;
      end_loop_3:
      end_4:;
	gensymed_symbol = Nil;
      next_loop_4:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)34L);
	if (CAS_SVREF(icp_socket,(SI_Long)34L,gensymed_symbol,Nil)) {
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
	    goto end_5;
	}
	goto next_loop_4;
      end_loop_4:
      end_5:;
	gensymed_symbol = Nil;
      next_loop_5:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)35L);
	if (CAS_SVREF(icp_socket,(SI_Long)35L,gensymed_symbol,Nil)) {
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
	    goto end_6;
	}
	goto next_loop_5;
      end_loop_5:
      end_6:;
	gensymed_symbol = Nil;
      next_loop_6:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)51L);
	if (CAS_SVREF(icp_socket,(SI_Long)51L,gensymed_symbol,Nil)) {
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
	    goto end_7;
	}
	goto next_loop_6;
      end_loop_6:
      end_7:;
	element = memq_function(icp_socket,
		Icp_sockets_waiting_for_icp_message_processing);
	if (element)
	    M_CAR(element) = Nil;
	if (output_port) {
	    cons_qm = ISVREF(output_port,(SI_Long)18L);
	    if (cons_qm) {
		M_CAR(cons_qm) = Nil;
		SVREF(output_port,FIX((SI_Long)18L)) = Nil;
	    }
	}
	if (EQ(connection_type,Qgeneric)) {
	    if (handle) {
		g2ext_network_close(IFIX(handle));
		register_socket_to_handle(Nil,handle);
	    }
	}
	else if (EQ(connection_type,Qlocalnet)) {
	    corresponding_localnet_socket = ISVREF(icp_socket,(SI_Long)42L);
	    SVREF(icp_socket,FIX((SI_Long)42L)) = Nil;
	    if (corresponding_localnet_socket) {
		SVREF(corresponding_localnet_socket,FIX((SI_Long)42L)) = Nil;
		enqueue_close_event(corresponding_localnet_socket,
			Network_status_success);
	    }
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_sockets_to_be_reclaimed, Qicp_sockets_to_be_reclaimed);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_for_handle_icp_messages, Qicp_socket_for_handle_icp_messages);

static Object Qole;                /* ole */

static Object Qgsi;                /* gsi */

static Object Qg2;                 /* g2 */

/* ICP-SOCKET-NOTIFIES-USER-ON-ERROR-P */
Object icp_socket_notifies_user_on_error_p(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(49,9);
    temp = ISVREF(icp_socket,(SI_Long)25L);
    if (EQ(temp,Qole))
	temp = Nil;
    else if (EQ(temp,Qgsi))
	temp = Nil;
    else if (EQ(temp,Qg2))
	temp = Nil;
    else
	temp = T;
    return VALUES_1(temp);
}

static Object Qshutdown;           /* shutdown */

/* FINALIZE-AND-RECLAIM-ICP-SOCKET */
Object finalize_and_reclaim_icp_socket(icp_socket)
    Object icp_socket;
{
    Object reason_for_shutdown_qm;

    x_note_fn_call(49,10);
    if ( !TRUEP(memq_function(icp_socket,Active_icp_sockets)))
	return VALUES_1(Nil);
    if (EQ(icp_socket,Icp_socket_for_handle_icp_messages))
	Icp_socket_for_handle_icp_messages = Nil;
    Active_icp_sockets = delete_icp_element_1(icp_socket,Active_icp_sockets);
    reason_for_shutdown_qm = ISVREF(icp_socket,(SI_Long)9L);
    execute_icp_connection_loss_callbacks(icp_socket, 
	    !TRUEP(reason_for_shutdown_qm) ? T : Nil);
    if (text_string_p(reason_for_shutdown_qm)) {
	if (icp_socket_notifies_user_on_error_p(icp_socket))
	    write_warning_message_string(FIX((SI_Long)2L),
		    reason_for_shutdown_qm);
	reclaim_text_string(reason_for_shutdown_qm);
	SVREF(icp_socket,FIX((SI_Long)9L)) = Qshutdown;
    }
    delete_all_representations_for_icp_socket(icp_socket);
    Icp_sockets_to_be_reclaimed = icp_cons_1(icp_socket,
	    Icp_sockets_to_be_reclaimed);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_icp_socket_reclamation, Qinhibit_icp_socket_reclamation);

static Object Qicp;                /* icp */

/* RECLAIM-ICP-SOCKETS */
Object reclaim_icp_sockets()
{
    Object icp_socket, icp_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(49,11);
    if ( !TRUEP(Inhibit_icp_socket_reclamation)) {
	icp_socket = Nil;
      next_loop:
	if ( !TRUEP(Icp_sockets_to_be_reclaimed))
	    goto end_loop;
	icp_pop_store = Nil;
	cons_1 = Icp_sockets_to_be_reclaimed;
	if (cons_1) {
	    icp_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qicp);
	    if (ISVREF(Available_icp_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_icp_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_icp_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_icp_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	Icp_sockets_to_be_reclaimed = next_cons;
	icp_socket = icp_pop_store;
	reclaim_icp_socket(icp_socket);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scheduler_enabled_qm, Qscheduler_enabled_qm);

/* SCHEDULER-ENABLED-P */
Object scheduler_enabled_p()
{
    x_note_fn_call(49,12);
    return VALUES_1(Scheduler_enabled_qm);
}

/* RUN-SCHEDULER-FOR-CURRENT-SYSTEM */
Object run_scheduler_for_current_system()
{
    Object scheduler_enabled_qm;
    char display_events_were_enabled;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(49,13);
    SAVE_STACK();
    display_events_were_enabled = (SI_Long)0L != ne_display_events_enabled();
    ne_disable_display_events();
    if (PUSH_UNWIND_PROTECT(0)) {
	scheduler_enabled_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scheduler_enabled_qm,Qscheduler_enabled_qm,scheduler_enabled_qm,
		0);
	  SAVE_VALUES(run_one_scheduler_cycle());
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

static Object Qhandle_icp_messages;  /* handle-icp-messages */

/* GET-PENDING-NETWORK-EVENTS */
Object get_pending_network_events()
{
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(49,14);
    SAVE_STACK();
    if ( !TRUEP(Scheduler_enabled_qm)) {
	if (g2_event_ready_p()) {
	    if (PUSH_UNWIND_PROTECT(1)) {
		if (PUSH_CATCH(Qhandle_icp_messages,0)) {
		  next_loop:
		    g2_event_cycle_handling_windows_quit();
		    if ( !TRUEP(g2_event_ready_p()))
			goto end_loop;
		    goto next_loop;
		  end_loop:;
		}
		POP_CATCH(0);
	    }
	    POP_UNWIND_PROTECT(1);
	    if (Icp_socket_for_handle_icp_messages && 
		    FIXNUM_EQ(ISVREF(Icp_socket_for_handle_icp_messages,
		    (SI_Long)15L),Icp_connection_closed))
		finalize_and_reclaim_icp_socket(Icp_socket_for_handle_icp_messages);
	    CONTINUE_UNWINDING(1);
	}
    }
    RESTORE_STACK();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inside_handle_event, Qinside_handle_event);

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* HANDLE-READ-EVENT-FUNCTION */
Object handle_read_event_function(socket_1,error_code,block_p)
    Object socket_1, error_code, block_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(49,15);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)20L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    gensymed_symbol_3 = block_p;
    return VALUES_1(inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2,gensymed_symbol_3));
}

/* HANDLE-WRITE-EVENT-FUNCTION */
Object handle_write_event_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(49,16);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)21L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-CONNECT-FUNCTION */
Object handle_network_connect_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(49,17);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)22L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-ACCEPT-FUNCTION */
Object handle_network_accept_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(49,18);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)23L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-NETWORK-CLOSE-FUNCTION */
Object handle_network_close_function(socket_1,error_code)
    Object socket_1, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(49,19);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)24L);
    gensymed_symbol_1 = socket_1;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

/* HANDLE-G2-RESET-FUNCTION */
Object handle_g2_reset_function(socket_1)
    Object socket_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(49,20);
    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)25L);
    gensymed_symbol_1 = socket_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object string_constant;     /* "Unknown event code ~d seen." */

static Object string_constant_1;   /* "Error event! ~% socket-handle is ~s, event-status is ~s.~%" */

/* HANDLE-EVENT-INTERNAL */
Object handle_event_internal(event_code,event_socket_handle,event_status_code)
    Object event_code, event_socket_handle, event_status_code;
{
    Object inside_handle_event, aref_arg_1, temp, socket_1, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    char gensymed_symbol_3;
    double current_time, aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(49,21);
    inside_handle_event = T;
    PUSH_SPECIAL_WITH_SYMBOL(Inside_handle_event,Qinside_handle_event,inside_handle_event,
	    0);
      if (Scheduler_enabled_qm) {
	  if (Profiling_enabled_qm) {
	      current_time = g2ext_unix_time_as_float();
	      aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)3L);
	      aref_new_value = current_time - 
		      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		      (SI_Long)2L),(SI_Long)0L) + 
		      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		      (SI_Long)3L),(SI_Long)0L);
	      DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	      aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	      DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	  }
      }
      if (g2ext_invokation_updates_needed() == (SI_Long)1L)
	  g2ext_cache_deferred_rules();
      reclaim_icp_sockets();
      temp = event_code;
      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	      FIX((SI_Long)127L))))
	  notify_user(2,string_constant,event_code);
      else
	  switch (INTEGER_TO_CHAR(temp)) {
	    case 1:
	    case 8:
	    case 2:
	    case 3:
	    case 4:
	    case 5:
	      socket_1 = lookup_socket_from_handle(event_socket_handle);
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
				  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qtype_description_of_unique_type_name_of_gensym_structure),
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
				  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qtype_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)21L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 3:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qtype_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)22L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 4:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qtype_description_of_unique_type_name_of_gensym_structure),
				  (SI_Long)9L),(SI_Long)23L);
			  gensymed_symbol_1 = socket_1;
			  gensymed_symbol_2 = event_status_code;
			  inline_funcall_2(gensymed_symbol,
				  gensymed_symbol_1,gensymed_symbol_2);
			  break;
			case 5:
			  gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
			  gensymed_symbol = 
				  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
				  Qtype_description_of_unique_type_name_of_gensym_structure),
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
	      if (scheduler_enabled_p())
		  run_scheduler_for_current_system();
	      break;
	    case 7:
	      handle_display_event();
	      break;
	    case -1:
	      notify_user(3,string_constant_1,event_socket_handle,
		      event_status_code);
	      break;
	    default:
	      notify_user(2,string_constant,event_code);
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
	      if (Profiling_enabled_qm) {
		  current_time = g2ext_unix_time_as_float();
		  aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)6L);
		  aref_new_value = current_time - 
			  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
			  (SI_Long)2L),(SI_Long)0L) + 
			  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
			  (SI_Long)6L),(SI_Long)0L);
		  DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
		  aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
		  DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	      }
	      break;
	    default:
	      break;
	  }
      if (Scheduler_enabled_qm)
	  enqueue_scheduler_events_if_necessary(Nil);
      temp = FIX((SI_Long)0L);
      reclaim_icp_sockets();
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qhandle_read_event_function;  /* handle-read-event-function */

/* ENQUEUE-READ-EVENT */
Object enqueue_read_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(49,22);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)43L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)43L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qhandle_read_event_function;
	temp = SYMBOL_FUNCTION(Qhandle_read_event_function);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	SVREF(task,FIX((SI_Long)14L)) = network_error_code;
	SVREF(task,FIX((SI_Long)15L)) = Nil;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)43L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
    return VALUES_1(Nil);
}

/* CLEAR-READ-EVENT */
Object clear_read_event(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(49,23);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)43L);
    if (CAS_SVREF(icp_socket,(SI_Long)43L,gensymed_symbol,Nil)) {
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
    return VALUES_1(Nil);
}

/* HANDLE-READ-EVENT-FOR-ICP-SOCKET */
Object handle_read_event_for_icp_socket(icp_socket,network_error_code,block_p)
    Object icp_socket, network_error_code, block_p;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(49,24);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)43L);
    if (CAS_SVREF(icp_socket,(SI_Long)43L,gensymed_symbol,Nil)) {
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
    if (EQ(Qlocalnet,ISVREF(icp_socket,(SI_Long)1L)))
	return handle_localnet_read(icp_socket);
    else
	return handle_network_read(icp_socket,network_error_code,block_p);
}

static Object Qhandle_write_event_function;  /* handle-write-event-function */

/* ENQUEUE-WRITE-EVENT */
Object enqueue_write_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(49,25);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)44L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)44L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qhandle_write_event_function;
	temp = SYMBOL_FUNCTION(Qhandle_write_event_function);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	SVREF(task,FIX((SI_Long)14L)) = network_error_code;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)44L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
    return VALUES_1(Nil);
}

/* CLEAR-WRITE-EVENT */
Object clear_write_event(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(49,26);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)44L);
    if (CAS_SVREF(icp_socket,(SI_Long)44L,gensymed_symbol,Nil)) {
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
    return VALUES_1(Nil);
}

/* HANDLE-WRITE-EVENT-FOR-ICP-SOCKET */
Object handle_write_event_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(49,27);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)44L);
    if (CAS_SVREF(icp_socket,(SI_Long)44L,gensymed_symbol,Nil)) {
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
    if (EQ(Qlocalnet,ISVREF(icp_socket,(SI_Long)1L)))
	return handle_localnet_write(icp_socket);
    else
	return handle_network_write(icp_socket,network_error_code);
}

static Object Qhandle_close_event;  /* handle-close-event */

/* ENQUEUE-CLOSE-EVENT */
Object enqueue_close_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(49,28);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)45L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)45L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
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
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qhandle_close_event;
	temp = SYMBOL_FUNCTION(Qhandle_close_event);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	SVREF(task,FIX((SI_Long)14L)) = network_error_code;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)45L,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
    return VALUES_1(Nil);
}

/* CLEAR-CLOSE-EVENT */
Object clear_close_event(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(49,29);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(icp_socket,(SI_Long)45L);
    if (CAS_SVREF(icp_socket,(SI_Long)45L,gensymed_symbol,Nil)) {
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
    return VALUES_1(Nil);
}

/* HANDLE-CLOSE-EVENT */
Object handle_close_event(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(1);

    x_note_fn_call(49,30);
    if (icp_socket) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)45L);
	if (CAS_SVREF(icp_socket,(SI_Long)45L,gensymed_symbol,Nil)) {
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
	if (EQ(Qlocalnet,ISVREF(icp_socket,(SI_Long)1L)))
	    handle_localnet_close(icp_socket);
	else {
	    gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
Object handle_display_event()
{
    x_note_fn_call(49,31);
    poll_native_window_workstation();
    maybe_schedule_service_workstation(Nil,T);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(During_ffi_call_qm, Qduring_ffi_call_qm);

static Object Qin_progress;        /* in-progress */

static Object Qno_data_available;  /* no-data-available */

static Object Qin_progress_with_data;  /* in-progress-with-data */

/* CONTINUE-READING-FROM-ICP-SOCKET */
Object continue_reading_from_icp_socket(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(49,32);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    temp = ISVREF(icp_input_port,(SI_Long)4L);
    if (EQ(temp,Qnil)) {
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)20L);
	gensymed_symbol_1 = icp_socket;
	gensymed_symbol_2 = Network_status_success;
	gensymed_symbol_3 = Nil;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else if (EQ(temp,Qin_progress))
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Qno_data_available;
    else if (EQ(temp,Qin_progress_with_data)) {
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)20L);
	gensymed_symbol_1 = icp_socket;
	gensymed_symbol_2 = Network_status_success;
	gensymed_symbol_3 = T;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    return VALUES_1(Nil);
}

static Object Qend_of_message_group;  /* end-of-message-group */

/* HANDLE-NETWORK-READ */
Object handle_network_read(icp_socket,network_error_code,block_p)
    Object icp_socket, network_error_code, block_p;
{
    Object socket_handle, icp_input_port, temp, connection_state;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, icp_buffer;
    Object octets_read_or_status, incff_1_arg, svref_new_value, end_1, copy;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(49,33);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    if ( !FIXNUM_EQ(network_error_code,Network_status_success)) {
	temp = Icp_read_event_error;
	if (icp_error_on_socket(4,icp_socket,temp,network_error_code,
		network_get_last_error_string(socket_handle))) {
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
    }
    connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(connection_state,Icp_connection_running) || 
	    FIXNUM_EQ(connection_state,
	    Icp_connection_awaiting_acknowledgement))) {
	if (icp_error_on_socket(3,icp_socket,
		Icp_received_data_on_invalid_socket,Nil)) {
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
    }
    if ( !TRUEP(block_p)) {
	if (ISVREF(icp_input_port,(SI_Long)4L)) {
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	    execute_icp_read_callbacks(icp_socket,T);
	}
    }
    else {
	temp = ISVREF(icp_input_port,(SI_Long)4L);
	if (EQ(temp,Qin_progress)) {
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = Qin_progress_with_data;
	    result = VALUES_1(Nil);
	    goto end_handle_network_read;
	}
	else
	    SVREF(icp_input_port,FIX((SI_Long)4L)) = Qin_progress;
    }
    outer_with_icp_buffer_coelescing_scope_qm = 
	    With_icp_buffer_coelescing_scope_qm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm,Qwith_icp_buffer_coelescing_scope_qm,with_icp_buffer_coelescing_scope_qm,
	    0);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
      icp_buffer = Nil;
      octets_read_or_status = Nil;
    next_loop:
      temp = ISVREF(icp_input_port,(SI_Long)7L);
      if (temp);
      else {
	  temp = make_icp_buffer_internal_1(make_variable_fill_icp_buffer());
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
	  end_1 = ISVREF(icp_buffer,(SI_Long)3L);
	  if ( !((SI_Long)0L == ((SI_Long)1L & IFIX(end_1)) && IFIX(end_1) 
		  > (SI_Long)4032L)) {
	      copy = copy_icp_buffer(icp_buffer);
	      SVREF(copy,FIX((SI_Long)2L)) = end_1;
	      SVREF(copy,FIX((SI_Long)3L)) = end_1;
	      SVREF(icp_buffer,FIX((SI_Long)1L)) = copy;
	  }
	  if (EQ(Qend_of_message_group,
		  enqueue_next_icp_buffer_if_any(icp_input_port))) {
	      if ( 
		      !TRUEP(call_or_schedule_handle_queued_icp_messages(icp_socket,
		      Nil))) {
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_handle_network_read;
	      }
	      if (ISVREF(icp_input_port,(SI_Long)4L)) {
		  SVREF(icp_input_port,FIX((SI_Long)4L)) = Qno_data_available;
		  result = VALUES_1(Nil);
		  POP_SPECIAL();
		  goto end_handle_network_read;
	      }
	  }
      }
      else if (FIXNUM_EQ(octets_read_or_status,Ne_blocked_value)) {
	  SVREF(icp_input_port,FIX((SI_Long)4L)) = T;
	  execute_icp_read_callbacks(icp_socket,Nil);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_handle_network_read;
      }
      else if (FIXNUM_EQ(octets_read_or_status,Ne_eof_value)) {
	  gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
	  gensymed_symbol = 
		  ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		  Qtype_description_of_unique_type_name_of_gensym_structure),
		  (SI_Long)9L),(SI_Long)24L);
	  gensymed_symbol_1 = icp_socket;
	  gensymed_symbol_2 = Network_status_success;
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_handle_network_read;
      }
      else if (FIXNUM_EQ(octets_read_or_status,Ne_error_value)) {
	  temp = Icp_read_call_returned_error;
	  temp_1 = FIX(ne_last_error_code(IFIX(socket_handle)));
	  if (icp_error_on_socket(4,icp_socket,temp,temp_1,
		  network_get_last_error_string(socket_handle))) {
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_handle_network_read;
	  }
      }
      goto next_loop;
    end_loop:
      temp = Qnil;
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
    POP_SPECIAL();
    result = VALUES_1(temp);
  end_handle_network_read:
    return result;
}

/* HANDLE-LOCALNET-READ */
Object handle_localnet_read(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, connection_state;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, enqueue_result;
    Declare_special(1);

    x_note_fn_call(49,34);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(connection_state,Icp_connection_running) || 
	    FIXNUM_EQ(connection_state,
	    Icp_connection_awaiting_acknowledgement))) {
	if (icp_error_on_socket(3,icp_socket,
		Icp_received_data_on_invalid_socket,Nil))
	    return VALUES_1(Nil);
    }
    if (ISVREF(icp_input_port,(SI_Long)4L)) {
	SVREF(icp_input_port,FIX((SI_Long)4L)) = Nil;
	execute_icp_read_callbacks(icp_socket,T);
    }
    SVREF(icp_socket,FIX((SI_Long)7L)) = T;
    outer_with_icp_buffer_coelescing_scope_qm = 
	    With_icp_buffer_coelescing_scope_qm;
    with_icp_buffer_coelescing_scope_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm,Qwith_icp_buffer_coelescing_scope_qm,with_icp_buffer_coelescing_scope_qm,
	    0);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
      enqueue_result = Nil;
    next_loop:
      connection_state = ISVREF(icp_socket,(SI_Long)15L);
      if ( !(FIXNUM_EQ(connection_state,Icp_connection_running) || 
	      FIXNUM_EQ(connection_state,
	      Icp_connection_awaiting_acknowledgement) ? 
	      TRUEP(ISVREF(icp_input_port,(SI_Long)7L)) : TRUEP(Nil)))
	  goto end_loop;
      enqueue_result = enqueue_next_icp_buffer_if_any(icp_input_port);
      if ( !( !EQ(Qend_of_message_group,enqueue_result) || 
	      call_or_schedule_handle_queued_icp_messages(icp_socket,Nil)))
	  goto end_loop;
      goto next_loop;
    end_loop:;
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
    POP_SPECIAL();
    if ( !TRUEP(ISVREF(icp_input_port,(SI_Long)7L)))
	SVREF(icp_input_port,FIX((SI_Long)4L)) = T;
    return VALUES_1(Nil);
}

/* HANDLE-NETWORK-WRITE */
Object handle_network_write(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object socket_handle, temp;

    x_note_fn_call(49,35);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)4L),(SI_Long)1L);
    if ( !FIXNUM_EQ(network_error_code,Network_status_success)) {
	temp = Icp_write_event_error;
	icp_error_on_socket(4,icp_socket,temp,network_error_code,
		network_get_last_error_string(socket_handle));
	return VALUES_1(Nil);
    }
    temp = handle_icp_write(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-LOCALNET-WRITE */
Object handle_localnet_write(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(49,36);
    temp = handle_icp_write(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-ICP-WRITE */
Object handle_icp_write(icp_socket)
    Object icp_socket;
{
    Object icp_output_port, callbacks, callbacks_old_value, temp;
    Object callback_function;

    x_note_fn_call(49,37);
    icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
    if ( !TRUEP(ISVREF(icp_output_port,(SI_Long)4L)))
	return VALUES_1(Nil);
    SVREF(icp_output_port,FIX((SI_Long)4L)) = Nil;
    callbacks = ISVREF(icp_socket,(SI_Long)13L);
  next_loop:
    transmit_icp_output_if_ready(icp_output_port,T);
    if (ISVREF(icp_output_port,(SI_Long)4L) ||  
	    !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    Icp_connection_running) ||  !TRUEP(callbacks)) {
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
	    !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_running))
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* HANDLE-NETWORK-CONNECT-FOR-ICP-SOCKET */
Object handle_network_connect_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object socket_handle, temp;

    x_note_fn_call(49,38);
    socket_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    if ( !FIXNUM_EQ(network_error_code,Network_status_success)) {
	temp = Icp_connect_event_error;
	icp_error_on_socket(4,icp_socket,temp,network_error_code,
		network_get_last_error_string(socket_handle));
	return VALUES_1(Nil);
    }
    return handle_icp_connect(icp_socket);
}

/* HANDLE-ICP-CONNECT */
Object handle_icp_connect(icp_socket)
    Object icp_socket;
{
    Object svref_new_value, temp;

    x_note_fn_call(49,39);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    Icp_connection_connect_in_progress)) {
	icp_error_on_socket(2,icp_socket,Icp_connect_on_invalid_socket);
	return VALUES_1(Nil);
    }
    svref_new_value = Icp_connection_running;
    SVREF(icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    send_initial_icp_version_info(icp_socket,T);
    temp =  !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    Icp_connection_closed) ? 
	    execute_icp_connect_callbacks(icp_socket) : Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Default_accept_timeout, Qdefault_accept_timeout);

/* HANDLE-NETWORK-ACCEPT-FOR-ICP-SOCKET */
Object handle_network_accept_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    Object listener_handle, temp, new_socket;
    SI_Long new_socket_handle;

    x_note_fn_call(49,40);
    listener_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L);
    if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_socket_listening)) {
	icp_error_on_socket(2,icp_socket,Icp_accept_on_invalid_socket);
	return VALUES_1(Nil);
    }
    if ( !FIXNUM_EQ(network_error_code,Network_status_success)) {
	temp = Icp_accept_event_error;
	icp_error_on_socket(4,icp_socket,temp,network_error_code,
		network_get_last_error_string(listener_handle));
	return VALUES_1(Nil);
    }
    new_socket_handle = g2ext_network_accept(IFIX(listener_handle));
    new_socket = Nil;
    if (new_socket_handle > (SI_Long)0L) {
	temp = get_accept_pathname(FIX(new_socket_handle));
	new_socket = make_and_install_network_icp_socket(6,
		FIX(new_socket_handle),FIX(new_socket_handle),temp,T,
		listener_handle,Default_accept_timeout);
	return execute_icp_accept_callbacks(icp_socket,new_socket);
    }
    else if (new_socket_handle == IFIX(Ne_blocked_value))
	return VALUES_1(Nil);
    else {
	temp = Icp_accept_failure;
	return icp_error_on_socket(4,icp_socket,temp,
		FIX(new_socket_handle),
		network_get_last_error_string(listener_handle));
    }
}

/* HANDLE-NETWORK-CLOSE-FOR-ICP-SOCKET */
Object handle_network_close_for_icp_socket(icp_socket,network_error_code)
    Object icp_socket, network_error_code;
{
    x_note_fn_call(49,41);
    if ( !FIXNUM_EQ(network_error_code,Network_status_success)) {
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
		Icp_connection_awaiting_acknowledgement))
	    icp_error_on_socket(2,icp_socket,Icp_shutdown_aborted);
	else
	    icp_error_on_socket(2,icp_socket,Icp_connection_reset);
	return VALUES_1(Nil);
    }
    return handle_icp_close(icp_socket);
}

/* HANDLE-LOCALNET-CLOSE */
Object handle_localnet_close(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(49,42);
    temp = handle_icp_close(icp_socket);
    return VALUES_1(temp);
}

/* HANDLE-ICP-CLOSE */
Object handle_icp_close(icp_socket)
    Object icp_socket;
{
    Object icp_socket_connection_state, temp;

    x_note_fn_call(49,43);
    icp_socket_connection_state = ISVREF(icp_socket,(SI_Long)15L);
    if ( !(FIXNUM_EQ(icp_socket_connection_state,
	    Icp_connection_awaiting_acknowledgement) || EQ(Qlocalnet,
	    ISVREF(icp_socket,(SI_Long)1L)))) {
	icp_error_on_socket(2,icp_socket,Icp_connection_closed_error);
	return VALUES_1(Nil);
    }
    temp = shutdown_icp_socket_connection(1,icp_socket);
    return VALUES_1(temp);
}

/* NOTIFY-SOCKETS-OF-G2-RESET */
Object notify_sockets_of_g2_reset()
{
    Object handle, socket_1, ab_loop_list_, ab_loop_desetq_, gensymed_symbol;
    Object gensymed_symbol_1;

    x_note_fn_call(49,44);
    handle = Nil;
    socket_1 = Nil;
    ab_loop_list_ = Handle_to_socket_mapping;
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
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)25L);
	gensymed_symbol_1 = socket_1;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* HANDLE-G2-RESET-FOR-ICP-SOCKET */
Object handle_g2_reset_for_icp_socket(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(49,45);
    return VALUES_1(Nil);
}

void netevent_INIT()
{
    Object svref_arg_1, svref_new_value, handle_read_event_for_icp_socket_1;
    Object handle_write_event_for_icp_socket_1;
    Object handle_network_connect_for_icp_socket_1;
    Object handle_network_accept_for_icp_socket_1;
    Object handle_network_close_for_icp_socket_1;
    Object handle_g2_reset_for_icp_socket_1;
    Object Qicp_socket, Qhandle_g2_reset, AB_package, Qhandle_network_close;
    Object Qhandle_network_accept, Qhandle_network_connect;
    Object Qhandle_write_event, Qhandle_read_event;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_1, list_constant;
    Object array_constant_18, array_constant_17, array_constant_16;
    Object array_constant_15, array_constant_14, array_constant_13;
    Object array_constant_12, array_constant_11, array_constant_10;
    Object array_constant_9, array_constant_8, array_constant_7;
    Object array_constant_6, array_constant_5, array_constant_4;
    Object array_constant_3, array_constant_2, string_constant_18;
    Object Qg2_defstruct_structure_name_error_code_g2_struct;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, string_constant_6;
    Object string_constant_5, string_constant_4, string_constant_3;
    Object string_constant_2;

    x_note_fn_call(49,46);
    SET_PACKAGE("AB");
    Icp_error_table = make_array(1,FIX((SI_Long)17L));
    Icp_success = FIX((SI_Long)0L);
    string_constant_2 = STATIC_STRING("Operation was successful.");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_success,
	    string_constant_2);
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = svref_new_value;
    Icp_read_event_error = FIX((SI_Long)1L);
    string_constant_3 = 
	    STATIC_STRING("Read event occurred on socket ~a, network error ~d, \"~a\"");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_3);
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = svref_new_value;
    Icp_received_data_on_invalid_socket = FIX((SI_Long)2L);
    string_constant_4 = 
	    STATIC_STRING("Data present on socket (~a) that is not in a readable state.");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_4);
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = svref_new_value;
    Icp_read_call_returned_error = FIX((SI_Long)3L);
    string_constant_5 = 
	    STATIC_STRING("Call to network-read on socket ~a returned error ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_5);
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = svref_new_value;
    Icp_write_event_error = FIX((SI_Long)4L);
    string_constant_6 = 
	    STATIC_STRING("Write event occurred on socket ~a with error ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_6);
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = svref_new_value;
    Icp_wrote_data_on_invalid_socket = FIX((SI_Long)5L);
    string_constant_7 = 
	    STATIC_STRING("Socket write event occurred on socket ~a, which is not in a writable state.~%");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_7);
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    Icp_write_call_returned_error = FIX((SI_Long)6L);
    string_constant_8 = 
	    STATIC_STRING("Call to network-write on socket ~a returned error ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_8);
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    Icp_connect_event_error = FIX((SI_Long)7L);
    string_constant_9 = 
	    STATIC_STRING("Error during connect on socket ~a: ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_9);
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
    Icp_connect_on_invalid_socket = FIX((SI_Long)8L);
    string_constant_10 = 
	    STATIC_STRING("Server connection finalized on a socket that\'s not connecting.");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_10);
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = svref_new_value;
    Icp_accept_on_invalid_socket = FIX((SI_Long)9L);
    string_constant_11 = 
	    STATIC_STRING("Client connection on a non-listener socket.");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_11);
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
    Icp_accept_event_error = FIX((SI_Long)10L);
    string_constant_12 = 
	    STATIC_STRING("Error during accept of client connection on listener socket ~a, error was: ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_12);
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
    Icp_close_event_error = FIX((SI_Long)11L);
    string_constant_13 = 
	    STATIC_STRING("Error during close by peer on socket ~a: ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_13);
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = svref_new_value;
    Icp_connection_closed_error = FIX((SI_Long)12L);
    string_constant_14 = 
	    STATIC_STRING("Connection closed by peer for ICP socket ~a");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_14);
    SVREF(svref_arg_1,FIX((SI_Long)12L)) = svref_new_value;
    Icp_shutdown_aborted = FIX((SI_Long)13L);
    string_constant_15 = 
	    STATIC_STRING("ICP connection shutdown handshake aborted by peer on socket ~a");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_15);
    SVREF(svref_arg_1,FIX((SI_Long)13L)) = svref_new_value;
    Icp_connection_reset = FIX((SI_Long)14L);
    string_constant_16 = 
	    STATIC_STRING("ICP connection reset by peer on socket ~a");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_16);
    SVREF(svref_arg_1,FIX((SI_Long)14L)) = svref_new_value;
    Icp_accept_failure = FIX((SI_Long)15L);
    string_constant_17 = 
	    STATIC_STRING("network_accept() call failed, for socket ~a, error code was: ~d, \"~a\".");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_fatal,
	    string_constant_17);
    SVREF(svref_arg_1,FIX((SI_Long)15L)) = svref_new_value;
    Icp_error_obtaining_error_string = FIX((SI_Long)16L);
    string_constant_18 = 
	    STATIC_STRING("Could not obtain error string for platform-specific network error, on socket ~a.");
    svref_arg_1 = Icp_error_table;
    svref_new_value = make_error_code_1(Error_severity_warning,
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
    No_event = FIX((SI_Long)0L);
    Read_event = FIX((SI_Long)1L);
    Write_event = FIX((SI_Long)2L);
    Connect_event = FIX((SI_Long)3L);
    Accept_event = FIX((SI_Long)4L);
    Close_event = FIX((SI_Long)5L);
    Scheduler_event = FIX((SI_Long)6L);
    Display_event = FIX((SI_Long)7L);
    Read_and_block_event = FIX((SI_Long)8L);
    Watch_event = FIX((SI_Long)9L);
    Quit_event = FIX((SI_Long)10L);
    Error_event = FIX((SI_Long)-1L);
    Network_status_success = FIX((SI_Long)0L);
    if (Network_octet_buffer_length == UNBOUND)
	Network_octet_buffer_length = FIX((SI_Long)2048L);
    if (Last_event_socket_handle_holder == UNBOUND)
	Last_event_socket_handle_holder = make_array(3,FIX((SI_Long)1L),
		Kelement_type,Qfixnum);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)32L));
    if (Last_event_status_code_holder == UNBOUND)
	Last_event_status_code_holder = make_array(3,FIX((SI_Long)1L),
		Kelement_type,list_constant);
    if (Handle_to_socket_mapping == UNBOUND)
	Handle_to_socket_mapping = Nil;
    Internal_events_handling_trigger = Nil;
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
    Qgeneric = STATIC_SYMBOL("GENERIC",AB_package);
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    if (Icp_sockets_to_be_reclaimed == UNBOUND)
	Icp_sockets_to_be_reclaimed = Nil;
    if (Icp_socket_for_handle_icp_messages == UNBOUND)
	Icp_socket_for_handle_icp_messages = Nil;
    Qole = STATIC_SYMBOL("OLE",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qshutdown = STATIC_SYMBOL("SHUTDOWN",AB_package);
    if (Inhibit_icp_socket_reclamation == UNBOUND)
	Inhibit_icp_socket_reclamation = Nil;
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    if (Scheduler_enabled_qm == UNBOUND)
	Scheduler_enabled_qm = Nil;
    Qhandle_icp_messages = STATIC_SYMBOL("HANDLE-ICP-MESSAGES",AB_package);
    if (Inside_handle_event == UNBOUND)
	Inside_handle_event = Nil;
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    string_constant = STATIC_STRING("Unknown event code ~d seen.");
    string_constant_1 = 
	    STATIC_STRING("Error event! ~% socket-handle is ~s, event-status is ~s.~%");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhandle_read_event_function = 
	    STATIC_SYMBOL("HANDLE-READ-EVENT-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_read_event_function,
	    STATIC_FUNCTION(handle_read_event_function,NIL,FALSE,3,3));
    Qhandle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    Qicp_socket = STATIC_SYMBOL("ICP-SOCKET",AB_package);
    handle_read_event_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_read_event_for_icp_socket,NIL,FALSE,3,3);
    record_direct_structure_method(Qhandle_read_event,Qicp_socket,
	    handle_read_event_for_icp_socket_1);
    Qhandle_write_event_function = 
	    STATIC_SYMBOL("HANDLE-WRITE-EVENT-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_write_event_function,
	    STATIC_FUNCTION(handle_write_event_function,NIL,FALSE,2,2));
    Qhandle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    handle_write_event_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_write_event_for_icp_socket,NIL,FALSE,2,2);
    record_direct_structure_method(Qhandle_write_event,Qicp_socket,
	    handle_write_event_for_icp_socket_1);
    Qhandle_close_event = STATIC_SYMBOL("HANDLE-CLOSE-EVENT",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_close_event,
	    STATIC_FUNCTION(handle_close_event,NIL,FALSE,2,2));
    if (During_ffi_call_qm == UNBOUND)
	During_ffi_call_qm = Nil;
    Qin_progress = STATIC_SYMBOL("IN-PROGRESS",AB_package);
    Qno_data_available = STATIC_SYMBOL("NO-DATA-AVAILABLE",AB_package);
    Qin_progress_with_data = STATIC_SYMBOL("IN-PROGRESS-WITH-DATA",AB_package);
    Qend_of_message_group = STATIC_SYMBOL("END-OF-MESSAGE-GROUP",AB_package);
    Qhandle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    handle_network_connect_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_network_connect_for_icp_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_network_connect,Qicp_socket,
	    handle_network_connect_for_icp_socket_1);
    if (Default_accept_timeout == UNBOUND)
	Default_accept_timeout = FIX(IFIX(Fixnum_time_units_per_second) * 
		(SI_Long)60L * (SI_Long)5L);
    Qhandle_network_accept = STATIC_SYMBOL("HANDLE-NETWORK-ACCEPT",AB_package);
    handle_network_accept_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_network_accept_for_icp_socket,NIL,FALSE,
	    2,2);
    record_direct_structure_method(Qhandle_network_accept,Qicp_socket,
	    handle_network_accept_for_icp_socket_1);
    Qhandle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",AB_package);
    handle_network_close_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_network_close_for_icp_socket,NIL,FALSE,2,2);
    record_direct_structure_method(Qhandle_network_close,Qicp_socket,
	    handle_network_close_for_icp_socket_1);
    Qhandle_g2_reset = STATIC_SYMBOL("HANDLE-G2-RESET",AB_package);
    handle_g2_reset_for_icp_socket_1 = 
	    STATIC_FUNCTION(handle_g2_reset_for_icp_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qhandle_g2_reset,Qicp_socket,
	    handle_g2_reset_for_icp_socket_1);
}
