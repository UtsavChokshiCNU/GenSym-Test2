/* int2.c
 * Input file:  int2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int2.h"


Object Localnet_queued_icp_buffer_limit = UNBOUND;

static Object Qlocalnet;           /* localnet */

static Object Qgeneric;            /* generic */

/* RECEIVE-NEXT-ICP-BUFFER-IF-ANY */
Object receive_next_icp_buffer_if_any(icp_input_port)
    Object icp_input_port;
{
    Object next_icp_buffer, temp, icp_socket, corresponding_icp_socket;
    Object corresponding_icp_output_port, svref_new_value;

    x_note_fn_call(50,0);
    next_icp_buffer = ISVREF(icp_input_port,(SI_Long)7L);
    if (next_icp_buffer) {
	temp = ISVREF(ISVREF(icp_input_port,(SI_Long)2L),(SI_Long)1L);
	if (EQ(temp,Qlocalnet)) {
	    icp_socket = ISVREF(icp_input_port,(SI_Long)2L);
	    corresponding_icp_socket = ISVREF(icp_socket,(SI_Long)42L);
	    corresponding_icp_output_port = corresponding_icp_socket ? 
		    ISVREF(corresponding_icp_socket,(SI_Long)4L) : Nil;
	    if (corresponding_icp_output_port && 
		    ISVREF(corresponding_icp_output_port,(SI_Long)4L))
		enqueue_write_event(corresponding_icp_socket,FIX((SI_Long)0L));
	}
	else if (EQ(temp,Qgeneric));
	svref_new_value = ISVREF(next_icp_buffer,(SI_Long)1L);
	SVREF(icp_input_port,FIX((SI_Long)7L)) = svref_new_value;
	SVREF(next_icp_buffer,FIX((SI_Long)1L)) = Nil;
	return VALUES_1(next_icp_buffer);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_index, Qicp_socket_index);

DEFINE_VARIABLE_WITH_SYMBOL(Shutdown_interval_for_disallowed_icp_connection_in_seconds, Qshutdown_interval_for_disallowed_icp_connection_in_seconds);

DEFINE_VARIABLE_WITH_SYMBOL(Shutdown_interval_for_disallowed_icp_connection, Qshutdown_interval_for_disallowed_icp_connection);

DEFINE_VARIABLE_WITH_SYMBOL(Negative_shutdown_interval_for_disallowed_icp_connection, Qnegative_shutdown_interval_for_disallowed_icp_connection);

DEFINE_VARIABLE_WITH_SYMBOL(Refused_icp_listener_connections, Qrefused_icp_listener_connections);

static Object Qg2;                 /* g2 */

static Object Qexecute;            /* execute */

/* ITEM-REMOTELY-CALLABLE-P */
Object item_remotely_callable_p(item)
    Object item;
{
    x_note_fn_call(50,1);
    return network_access_allowed_p(3,Qg2,Qexecute,item);
}

/* ITEM-REMOTELY-VISIBLE-P */
Object item_remotely_visible_p(item)
    Object item;
{
    Object temp;

    x_note_fn_call(50,2);
    temp = network_access_allowed_p(3,Qg2,Qread,item);
    return VALUES_1(temp);
}

/* ITEM-REMOTELY-MODIFIABLE-P */
Object item_remotely_modifiable_p(item)
    Object item;
{
    Object temp;

    x_note_fn_call(50,3);
    temp = network_access_allowed_p(3,Qg2,Qwrite,item);
    return VALUES_1(temp);
}

static Object Qab;                 /* ab */

static Object Qconnect;            /* connect */

static Object Qtelewindows;        /* telewindows */

/* ALL-REMOTE-CONNECTIONS-RESTRICTED-P */
Object all_remote_connections_restricted_p()
{
    Object temp;

    x_note_fn_call(50,4);
    temp = EQ(Current_system_name,Qab) &&  
	    !TRUEP(network_access_allowed_p(2,Qg2,Qconnect)) ? ( 
	    !TRUEP(network_access_allowed_p(2,Qtelewindows,Qconnect)) ? T :
	     Nil) : Qnil;
    return VALUES_1(temp);
}

/* GET-FORBIDDEN-LISTENER-CLIENTS-IF-ANY */
Object get_forbidden_listener_clients_if_any()
{
    Object forbidden_listener_clients_qm, temp;

    x_note_fn_call(50,5);
    if (EQ(Current_system_name,Qab)) {
	forbidden_listener_clients_qm = Nil;
	if ( !TRUEP(network_access_allowed_p(2,Qg2,Qconnect)))
	    forbidden_listener_clients_qm = icp_cons_1(Qg2,
		    forbidden_listener_clients_qm);
	if ( !TRUEP(network_access_allowed_p(2,Qtelewindows,Qconnect)))
	    forbidden_listener_clients_qm = icp_cons_1(Qtelewindows,
		    forbidden_listener_clients_qm);
	temp = forbidden_listener_clients_qm;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qinform;             /* inform */

/* REMOTE-INFORM-RESTRICTED-P */
Object remote_inform_restricted_p()
{
    x_note_fn_call(50,6);
    return VALUES_1( !TRUEP(network_access_allowed_p(2,Qg2,Qinform)) ? T : 
	    Nil);
}

/* PRINT-ICP-BUFFER-CONTENTS */
Object print_icp_buffer_contents(buffer)
    Object buffer;
{
    Object bv, array;
    SI_Long n_1, start, end_1, count_1, i, ab_loop_bind_, ab_loop_step_by_, j;
    SI_Long temp, ab_loop_bind__1, icp_position, position_1;

    x_note_fn_call(50,7);
    n_1 = (SI_Long)16L;
    bv = ISVREF(buffer,(SI_Long)4L);
    start = IFIX(ISVREF(buffer,(SI_Long)2L)) >>  -  - (SI_Long)1L;
    end_1 = IFIX(ISVREF(buffer,(SI_Long)3L)) >>  -  - (SI_Long)1L;
    count_1 = end_1 - start;
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
Object print_icp_buffer_byte_contents(buffer)
    Object buffer;
{
    Object bv, start, end_1, count_1;
    SI_Long n_1, i, ab_loop_bind_, ab_loop_step_by_, j, temp, ab_loop_bind__1;

    x_note_fn_call(50,8);
    n_1 = (SI_Long)16L;
    bv = ISVREF(buffer,(SI_Long)4L);
    start = ISVREF(buffer,(SI_Long)2L);
    end_1 = ISVREF(buffer,(SI_Long)3L);
    count_1 = FIXNUM_MINUS(end_1,start);
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
Object reset_counters_for_all_icp_sockets()
{
    Object icp_socket, ab_loop_list_;

    x_note_fn_call(50,9);
    icp_socket = Nil;
    ab_loop_list_ = Active_icp_sockets;
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

DEFINE_VARIABLE_WITH_SYMBOL(Saved_initial_status, Qsaved_initial_status);

static Object Qgsi;                /* gsi */

static Object Kfnord;              /* :fnord */

/* RESTORE-ICP-INDEX-TO-ORIGINAL-STATE */
Object restore_icp_index_to_original_state()
{
    Object temp, icp_socket_index_new_value;

    x_note_fn_call(50,10);
    if (EQ(Current_system_name,Qtelewindows))
	return VALUES_1(Nil);
    else if (EQ(Current_system_name,Qgsi))
	return VALUES_1(Nil);
    else if (IFIX(Icp_socket_index) == (SI_Long)1000L) {
	Icp_socket_index = FIX((SI_Long)0L);
	temp = ISVREF(Saved_initial_status,(SI_Long)1L);
	if (FOURTH(temp))
	    return replace_format_using_equivalent_font(Kfnord);
	else
	    return VALUES_1(Nil);
    }
    else {
	icp_socket_index_new_value = FIXNUM_ADD1(Icp_socket_index);
	Icp_socket_index = icp_socket_index_new_value;
	return VALUES_1(Icp_socket_index);
    }
}

/* ICP-OUTPUT-PORT-FLUSHED? */
Object icp_output_port_flushed_qm(icp_output_port)
    Object icp_output_port;
{
    x_note_fn_call(50,11);
    if (EQ(ISVREF(icp_output_port,(SI_Long)12L),ISVREF(icp_output_port,
	    (SI_Long)13L)))
	return VALUES_1( !TRUEP(ISVREF(icp_output_port,(SI_Long)4L)) ? T : 
		Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_icp_message_processing_enabled, Qinhibit_icp_message_processing_enabled);

DEFINE_VARIABLE_WITH_SYMBOL(Inhibit_icp_message_processing, Qinhibit_icp_message_processing);

static Object Qab_gensym;          /* gensym */

/* SCHEDULE-PROCESSING-FOR-INHIBITED-MESSAGES */
Object schedule_processing_for_inhibited_messages()
{
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm, icp_socket, gensym_pop_store;
    Object cons_1, next_cons, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(50,12);
    if (Icp_sockets_waiting_for_icp_message_processing) {
	if ( !TRUEP(Inhibit_icp_message_processing)) {
	    Icp_sockets_waiting_for_icp_message_processing = 
		    nreverse(Icp_sockets_waiting_for_icp_message_processing);
	    outer_with_icp_buffer_coelescing_scope_qm = 
		    With_icp_buffer_coelescing_scope_qm;
	    with_icp_buffer_coelescing_scope_qm = T;
	    PUSH_SPECIAL_WITH_SYMBOL(With_icp_buffer_coelescing_scope_qm,Qwith_icp_buffer_coelescing_scope_qm,with_icp_buffer_coelescing_scope_qm,
		    0);
	      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
		  if (Icp_output_ports_to_flush)
		      flush_icp_output_ports();
	      }
	      icp_socket = Nil;
	    next_loop:
	      if ( !TRUEP(Icp_sockets_waiting_for_icp_message_processing))
		  goto end_loop;
	      gensym_pop_store = Nil;
	      cons_1 = Icp_sockets_waiting_for_icp_message_processing;
	      if (cons_1) {
		  gensym_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qab_gensym);
		  if (ISVREF(Available_gensym_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = ISVREF(Available_gensym_conses_tail_vector,
			      IFIX(Current_thread_index));
		      M_CDR(temp) = cons_1;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  else {
		      temp = Available_gensym_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		      temp = Available_gensym_conses_tail_vector;
		      svref_arg_2 = Current_thread_index;
		      SVREF(temp,svref_arg_2) = cons_1;
		  }
		  M_CDR(cons_1) = Nil;
	      }
	      else
		  next_cons = Nil;
	      Icp_sockets_waiting_for_icp_message_processing = next_cons;
	      icp_socket = gensym_pop_store;
	      if (icp_socket)
		  call_or_schedule_handle_queued_icp_messages(icp_socket,T);
	      goto next_loop;
	    end_loop:;
	      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
		  if (Icp_output_ports_to_flush)
		      flush_icp_output_ports();
	      }
	    POP_SPECIAL();
	}
    }
    return VALUES_1(Nil);
}

static Object Qui_client_interface;  /* ui-client-interface */

/* ICP-SOCKET-IS-FOR-UI-CLIENT-INTERFACE-P */
Object icp_socket_is_for_ui_client_interface_p(icp_socket)
    Object icp_socket;
{
    Object interface_qm, temp;

    x_note_fn_call(50,13);
    interface_qm = ISVREF(icp_socket,(SI_Long)5L);
    temp = of_class_p_function(interface_qm,Qui_client_interface) ? ( 
	    !TRUEP(frame_has_been_reprocessed_p_function(interface_qm,
	    ISVREF(icp_socket,(SI_Long)6L))) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Handle_ui_client_interface_messages_immediately_p, Qhandle_ui_client_interface_messages_immediately_p);

DEFINE_VARIABLE_WITH_SYMBOL(Abort_for_icp_catcher_qm, Qabort_for_icp_catcher_qm);

static Object Qhandle_icp_messages;  /* handle-icp-messages */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qhandle_queued_icp_messages_task;  /* handle-queued-icp-messages-task */

/* CALL-OR-SCHEDULE-HANDLE-QUEUED-ICP-MESSAGES */
Object call_or_schedule_handle_queued_icp_messages(icp_socket,force_schedule_p)
    Object icp_socket, force_schedule_p;
{
    Object abort_for_icp_catcher_qm, more_to_do_immediately_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed, ctask, p, v, q;
    char svref_new_value_1, g2_p;
    double gensymed_symbol, gensymed_symbol_1, aref_new_value;
    Declare_catch(1);
    Declare_special(1);

    x_note_fn_call(50,14);
    if (Inhibit_icp_message_processing) {
	if ( !TRUEP(memq_function(icp_socket,
		Icp_sockets_waiting_for_icp_message_processing)))
	    Icp_sockets_waiting_for_icp_message_processing = 
		    gensym_cons_1(icp_socket,
		    Icp_sockets_waiting_for_icp_message_processing);
	return VALUES_1(Nil);
    }
    else if (EQ(ISVREF(icp_socket,(SI_Long)25L),Qtelewindows) || 
	    Handle_ui_client_interface_messages_immediately_p && ( 
	    !TRUEP(ISVREF(icp_socket,(SI_Long)25L)) || 
	    icp_socket_is_for_ui_client_interface_p(icp_socket)) || 
	    During_ffi_call_qm) {
	if (PUSH_CATCH(Qhandle_icp_messages,0)) {
	    abort_for_icp_catcher_qm = Qhandle_icp_messages;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      more_to_do_immediately_qm = 
		      handle_queued_icp_messages(icp_socket);
	    POP_SPECIAL();
	}
	else
	    more_to_do_immediately_qm = CATCH_VALUES();
	POP_CATCH(0);
	if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_closed)) {
	    finalize_and_reclaim_icp_socket(icp_socket);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(more_to_do_immediately_qm);
    }
    else {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)34L);
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
	gensymed_symbol = 
		icp_socket_is_for_ui_client_interface_p(icp_socket) ? 0.1 :
		 0.2;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L);
	aref_new_value = gensymed_symbol + gensymed_symbol_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	SVREF(task,FIX((SI_Long)4L)) = Highest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = Qhandle_queued_icp_messages_task;
	temp = SYMBOL_FUNCTION(Qhandle_queued_icp_messages_task);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)34L,old,new_1)) {
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
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(icp_socket,(SI_Long)35L);
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
	SVREF(task,FIX((SI_Long)4L)) = Lowest_system_priority;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qhandle_queued_icp_messages_task;
	temp = SYMBOL_FUNCTION(Qhandle_queued_icp_messages_task);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)35L,old,new_1)) {
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
	    goto end_2;
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
	goto next_loop_1;
      end_loop_1:
      end_2:;
	return VALUES_1(Nil);
    }
}

/* HANDLE-QUEUED-ICP-MESSAGES-TASK */
Object handle_queued_icp_messages_task(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, aref_arg_1;
    Object outer_with_icp_buffer_coelescing_scope_qm;
    Object with_icp_buffer_coelescing_scope_qm;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(1);

    x_note_fn_call(50,15);
    gensymed_symbol = Nil;
    gensymed_symbol_1 = 0.0;
    gensymed_symbol_2 = 0.0;
    if (Profiling_enabled_qm) {
	gensymed_symbol = T;
	gensymed_symbol_1 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_2 = g2ext_unix_time_as_float();
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,gensymed_symbol_2);
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
      if (handle_queued_icp_messages(icp_socket))
	  continue_reading_from_icp_socket(icp_socket);
      if ( !TRUEP(outer_with_icp_buffer_coelescing_scope_qm)) {
	  if (Icp_output_ports_to_flush)
	      flush_icp_output_ports();
      }
    POP_SPECIAL();
    if (Profiling_enabled_qm) {
	gensymed_symbol_3 = g2ext_unix_time_as_float();
	gensymed_symbol_4 = DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)2L),(SI_Long)0L);
	gensymed_symbol_5 = gensymed_symbol_3 - gensymed_symbol_4;
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)6L);
	aref_new_value = gensymed_symbol_5 + 
		DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)6L),
		(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	aref_new_value = gensymed_symbol ? gensymed_symbol_1 + 
		gensymed_symbol_5 + (gensymed_symbol_4 - 
		gensymed_symbol_2) : gensymed_symbol_3;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
    }
    return VALUES_1(Nil);
}

/* HANDLE-QUEUED-ICP-MESSAGES */
Object handle_queued_icp_messages(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object more_to_do_immediately_qm, abort_for_icp_catcher_qm, icp_input_port;
    Object did_something_qm, time_slice_expired_qm, can_process_messages_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(50,16);
    gensymed_symbol = Nil;
  next_loop:
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
    if (Inhibit_icp_message_processing) {
	if ( !TRUEP(memq_function(icp_socket,
		Icp_sockets_waiting_for_icp_message_processing)))
	    Icp_sockets_waiting_for_icp_message_processing = 
		    gensym_cons_1(icp_socket,
		    Icp_sockets_waiting_for_icp_message_processing);
	return VALUES_1(Nil);
    }
    Icp_socket_for_handle_icp_messages = icp_socket;
    more_to_do_immediately_qm = Nil;
    abort_for_icp_catcher_qm = Qhandle_icp_messages;
    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
	    0);
      icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
      did_something_qm = Nil;
      time_slice_expired_qm = Nil;
      can_process_messages_qm = Nil;
    next_loop_2:
      did_something_qm = 
	      process_next_icp_message_group_if_ready(icp_input_port);
      time_slice_expired_qm =  !TRUEP(During_ffi_call_qm) ? 
	      time_slice_expired_p() : Qnil;
      can_process_messages_qm = 
	      icp_connection_can_process_messages_qm(icp_socket);
      if (time_slice_expired_qm ||  !TRUEP(did_something_qm) ||  
	      !TRUEP(can_process_messages_qm))
	  goto end_loop_2;
      goto next_loop_2;
    end_loop_2:
      if (can_process_messages_qm)
	  more_to_do_immediately_qm = did_something_qm ? 
		  call_or_schedule_handle_queued_icp_messages(icp_socket,
		  T) : T;
      if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_closed))
	  finalize_and_reclaim_icp_socket(icp_socket);
      result = VALUES_1(more_to_do_immediately_qm);
    POP_SPECIAL();
    return result;
}

static Object Qbroken_while_transmitting;  /* broken-while-transmitting */

/* TRANSMIT-NEXT-NETWORK-ICP-BUFFER */
Object transmit_next_network_icp_buffer(icp_output_port)
    Object icp_output_port;
{
    Object icp_socket, icp_buffer_queue_head, icp_buffer;
    Object character_to_start_at, characters_to_send, temp;
    SI_Long characters_sent, svref_new_value;

    x_note_fn_call(50,17);
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
	reclaim_icp_buffer(icp_buffer_queue_head);
	SVREF(icp_output_port,FIX((SI_Long)12L)) = icp_buffer;
	temp = T;
    }
    else if (characters_sent >= (SI_Long)0L) {
	SVREF(icp_output_port,FIX((SI_Long)4L)) = T;
	execute_icp_write_callbacks(icp_socket,Nil);
	svref_new_value = IFIX(character_to_start_at) + characters_sent;
	ISVREF(icp_buffer,(SI_Long)2L) = FIX(svref_new_value);
	SVREF(icp_output_port,FIX((SI_Long)7L)) = icp_buffer;
	temp = Nil;
    }
    else {
	shutdown_icp_socket_connection(2,ISVREF(icp_output_port,
		(SI_Long)2L),Qbroken_while_transmitting);
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* TRANSMIT-NEXT-LOCALNET-ICP-BUFFER */
Object transmit_next_localnet_icp_buffer(icp_output_port)
    Object icp_output_port;
{
    Object icp_socket, icp_buffer_queue_head, icp_buffer;
    Object corresponding_icp_socket, corresponding_icp_input_port;
    Object buffer_chain_copy, buffer_for_callback, last_buffer, next_buffer;

    x_note_fn_call(50,18);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    icp_buffer_queue_head = ISVREF(icp_output_port,(SI_Long)12L);
    icp_buffer = ISVREF(icp_buffer_queue_head,(SI_Long)1L);
    corresponding_icp_socket = ISVREF(icp_socket,(SI_Long)42L);
    corresponding_icp_input_port = ISVREF(corresponding_icp_socket,
	    (SI_Long)3L);
    buffer_chain_copy = copy_icp_buffer_chain(icp_buffer);
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
    reclaim_icp_buffer(icp_buffer_queue_head);
    icp_buffer_queue_head = last_buffer;
    last_buffer = next_buffer;
    goto next_loop_1;
  end_loop_1:;
    SVREF(icp_output_port,FIX((SI_Long)12L)) = icp_buffer_queue_head;
    if (ISVREF(corresponding_icp_input_port,(SI_Long)4L))
	enqueue_read_event(corresponding_icp_socket,FIX((SI_Long)0L));
    return VALUES_1(T);
}

/* TRANSMIT-ICP-OUTPUT-IF-READY */
Object transmit_icp_output_if_ready(icp_output_port,flush_partial_buffers)
    Object icp_output_port, flush_partial_buffers;
{
    Object icp_socket, type_of_icp_connection, tail, head;
    char localnetp_1;

    x_note_fn_call(50,19);
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    type_of_icp_connection = ISVREF(icp_socket,(SI_Long)1L);
    localnetp_1 = EQ(type_of_icp_connection,Qlocalnet);
    if (localnetp_1 &&  !TRUEP(ISVREF(icp_socket,(SI_Long)42L))) {
	if ( !FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_closed))
	    shutdown_icp_socket_connection(2,icp_socket,
		    Qbroken_while_transmitting);
	return VALUES_1(Nil);
    }
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_running) 
	    &&  !TRUEP(ISVREF(icp_output_port,(SI_Long)4L))) {
	tail = ISVREF(icp_output_port,(SI_Long)13L);
	head = Nil;
      next_loop:
	head = ISVREF(icp_output_port,(SI_Long)12L);
	if (EQ(head,tail) ||  !TRUEP(flush_partial_buffers) && 
		EQ(ISVREF(head,(SI_Long)1L),tail) && IFIX(ISVREF(tail,
		(SI_Long)3L)) < (SI_Long)4096L)
	    goto end_loop;
	if ( !(localnetp_1 ? 
		TRUEP(transmit_next_localnet_icp_buffer(icp_output_port)) :
		 TRUEP(transmit_next_network_icp_buffer(icp_output_port))))
	    goto end_loop;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qend_of_message_group;  /* end-of-message-group */

/* ENQUEUE-NEXT-ICP-BUFFER-IF-ANY */
Object enqueue_next_icp_buffer_if_any(icp_input_port)
    Object icp_input_port;
{
    Object icp_buffer_qm, icp_buffer_start_icp_offset, tail, svref_new_value_1;
    Object icp_socket, i_am_alive_info_qm, contains_end_of_message_group_qm;
    Object number_of_icp_bytes_left_in_buffer;
    Object number_of_icp_bytes_still_needed_for_message_series;
    Object index_of_icp_byte_position, array, current_icp_port, temp;
    SI_Long incff_1_arg, svref_new_value, icp_position, position_1;
    SI_Long message_series_byte_count;
    Declare_special(1);

    x_note_fn_call(50,20);
    icp_buffer_qm = receive_next_icp_buffer_if_any(icp_input_port);
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
	    reclaim_icp_buffer(icp_buffer_qm);
	    icp_buffer_qm = tail;
	}
	else {
	    SVREF(tail,FIX((SI_Long)1L)) = icp_buffer_qm;
	    SVREF(icp_input_port,FIX((SI_Long)13L)) = icp_buffer_qm;
	}
	icp_socket = ISVREF(icp_input_port,(SI_Long)2L);
	i_am_alive_info_qm = ISVREF(icp_socket,(SI_Long)24L);
	if (i_am_alive_info_qm) {
	    incff_1_arg = (IFIX(ISVREF(icp_buffer_qm,(SI_Long)3L)) >>  -  
		    - (SI_Long)1L) - (IFIX(ISVREF(icp_buffer_qm,
		    (SI_Long)2L)) >>  -  - (SI_Long)1L) - 
		    IFIX(icp_buffer_start_icp_offset);
	    svref_new_value = IFIX(ISVREF(i_am_alive_info_qm,(SI_Long)6L)) 
		    + incff_1_arg;
	    ISVREF(i_am_alive_info_qm,(SI_Long)6L) = FIX(svref_new_value);
	    send_i_am_alive_if_necessary(icp_socket,i_am_alive_info_qm);
	}
	update_gsi_interface_countdown_timer(ISVREF(icp_input_port,
		(SI_Long)2L));
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
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    0);
	      icp_out_of_synch(1,FIX((SI_Long)1L));
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
	temp = contains_end_of_message_group_qm ? Qend_of_message_group : T;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Priority_of_icp_message_service, Qpriority_of_icp_message_service);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_of_rpc_service, Qpriority_of_rpc_service);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_of_icp_control_messages, Qpriority_of_icp_control_messages);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_priority_of_gsi_data_service, Qresumable_priority_of_gsi_data_service);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_priority_of_gsi_rpc_service, Qresumable_priority_of_gsi_rpc_service);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icp_buffer, Qcurrent_icp_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Current_read_icp_byte_position, Qcurrent_read_icp_byte_position);

DEFINE_VARIABLE_WITH_SYMBOL(Current_write_icp_byte_position, Qcurrent_write_icp_byte_position);

DEFINE_VARIABLE_WITH_SYMBOL(Writing_resumable_icp_messages_p, Qwriting_resumable_icp_messages_p);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_error_suspend_p, Qicp_error_suspend_p);

DEFINE_VARIABLE_WITH_SYMBOL(Current_resumable_icp_read_task, Qcurrent_resumable_icp_read_task);

DEFINE_VARIABLE_WITH_SYMBOL(Resumable_icp_read_ignore_p, Qresumable_icp_read_ignore_p);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_left_in_current_buffer, Qnumber_of_icp_bytes_left_in_current_buffer);

/* READ-ICP-SKIP-TO-MESSAGE-GROUP-END */
Object read_icp_skip_to_message_group_end()
{
    Object current_resumable_icp_read_task, temp_1;
    SI_Long length_1, incff_1_arg, temp_2, decff_1_arg;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(50,21);
    current_resumable_icp_read_task = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_resumable_icp_read_task,Qcurrent_resumable_icp_read_task,current_resumable_icp_read_task,
	    0);
    next_loop:
      length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
      temp = (SI_Long)0L < length_1;
      if (temp);
      else {
	  temp_1 = ensure_next_icp_message_series();
	  length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	  temp = TRUEP(temp_1);
      }
      if ( !temp) {
	  process_end_of_message_group(T,Nil);
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_read_icp_skip_to_message_group_end;
      }
      else {
	  incff_1_arg = length_1;
	  temp_2 = IFIX(Current_read_icp_byte_position) + incff_1_arg;
	  Current_read_icp_byte_position = FIX(temp_2);
	  decff_1_arg = length_1;
	  temp_2 = IFIX(Number_of_icp_bytes_ready_to_read) - decff_1_arg;
	  Number_of_icp_bytes_ready_to_read = FIX(temp_2);
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
Object read_icp_byte_or_message_group_end()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(50,22);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = process_end_of_message_group(T,T);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	Current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	Number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* READ-ICP-BYTE-IF-ANY */
Object read_icp_byte_if_any()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(50,23);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = process_end_of_message_group(T,Nil);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	Current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	Number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* READ-ICP-BYTE */
Object read_icp_byte()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(50,24);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = process_end_of_message_group(Nil,Nil);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	Current_read_icp_byte_position = FIXNUM_ADD1(FIXNUM_SUB1(start));
	Number_of_icp_bytes_ready_to_read = FIX(length_1 - (SI_Long)1L);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* PEEK-ICP-BYTE-IF-ANY */
Object peek_icp_byte_if_any()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(50,25);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = process_end_of_message_group(T,Nil);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* PEEK-ICP-BYTE */
Object peek_icp_byte()
{
    Object temp_1, array, start, array_1;
    SI_Long length_1, icp_position, position_1;
    char temp;

    x_note_fn_call(50,26);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	temp_1 = process_end_of_message_group(Nil,Nil);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	array_1 = array;
	icp_position = IFIX(start);
	position_1 = icp_position + icp_position;
	temp_1 = FIX((UBYTE_8_ISAREF_1(array_1,position_1) << (SI_Long)8L) 
		+ UBYTE_8_ISAREF_1(array_1,position_1 + (SI_Long)1L));
    }
    return VALUES_1(temp_1);
}

/* GET-ICP-READ-BUFFER */
Object get_icp_read_buffer()
{
    Object temp_1, array, start;
    SI_Long length_1;
    char temp;

    x_note_fn_call(50,27);
    length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
    temp = (SI_Long)0L < length_1;
    if (temp);
    else {
	temp_1 = ensure_next_icp_message_series();
	length_1 = IFIX(Number_of_icp_bytes_ready_to_read);
	temp = TRUEP(temp_1);
    }
    if ( !temp)
	return VALUES_1(Nil);
    else {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = FIXNUM_ADD1(Current_read_icp_byte_position);
	return VALUES_3(array,start,FIX(length_1));
    }
}

/* ENSURE-NEXT-ICP-MESSAGE-SERIES */
Object ensure_next_icp_message_series()
{
    Object array, temp, number_of_icp_bytes_left_in_current_buffer;
    Object svref_arg_1, svref_new_value;
    SI_Long icp_position, position_1;
    Declare_special(1);

    x_note_fn_call(50,28);
    ensure_next_icp_byte();
    if (IFIX(Number_of_icp_bytes_left_in_message_series) == (SI_Long)0L) {
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	icp_position = IFIX(FIXNUM_ADD1(Current_read_icp_byte_position));
	position_1 = icp_position + icp_position;
	temp = (SI_Long)1L == (UBYTE_8_ISAREF_1(array,position_1) << 
		(SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + 
		(SI_Long)1L) ? Nil : start_next_message_series();
    }
    else {
	number_of_icp_bytes_left_in_current_buffer = 
		ISVREF(Current_icp_port,(SI_Long)17L);
	PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_left_in_current_buffer,Qnumber_of_icp_bytes_left_in_current_buffer,number_of_icp_bytes_left_in_current_buffer,
		0);
	  Number_of_icp_bytes_ready_to_read = 
		  FIXNUM_MIN(Number_of_icp_bytes_left_in_current_buffer,
		  Number_of_icp_bytes_left_in_message_series);
	  Number_of_icp_bytes_left_in_message_series = 
		  FIXNUM_MINUS(Number_of_icp_bytes_left_in_message_series,
		  Number_of_icp_bytes_ready_to_read);
	  svref_arg_1 = Current_icp_port;
	  svref_new_value = 
		  FIXNUM_MINUS(Number_of_icp_bytes_left_in_current_buffer,
		  Number_of_icp_bytes_ready_to_read);
	  SVREF(svref_arg_1,FIX((SI_Long)17L)) = svref_new_value;
	  temp = T;
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

/* ENSURE-NEXT-ICP-BYTE */
Object ensure_next_icp_byte()
{
    Object icp_buffer_queue_head, next_head, svref_arg_1, temp;
    SI_Long svref_new_value;

    x_note_fn_call(50,29);
    if ((SI_Long)0L == IFIX(ISVREF(Current_icp_port,(SI_Long)17L))) {
	icp_buffer_queue_head = ISVREF(Current_icp_port,(SI_Long)12L);
	next_head = ISVREF(icp_buffer_queue_head,(SI_Long)1L);
	Current_icp_buffer = next_head;
	if ( !TRUEP(Current_icp_buffer))
	    icp_out_of_synch(1,FIX((SI_Long)4L));
	svref_arg_1 = Current_icp_port;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = next_head;
	reclaim_icp_buffer(icp_buffer_queue_head);
	svref_arg_1 = Current_icp_port;
	svref_new_value = (IFIX(ISVREF(Current_icp_buffer,(SI_Long)3L)) >> 
		 -  - (SI_Long)1L) - (IFIX(ISVREF(Current_icp_buffer,
		(SI_Long)2L)) >>  -  - (SI_Long)1L);
	ISVREF(svref_arg_1,(SI_Long)17L) = FIX(svref_new_value);
	Current_read_icp_byte_position = FIX((SI_Long)-1L);
	temp = Current_read_icp_byte_position;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant;     /* "[reading message series]" */

static Object Qmessage_series;     /* message-series */

/* START-NEXT-MESSAGE-SERIES */
Object start_next_message_series()
{
    Object temp, array, number_of_icp_bytes_left_in_current_buffer, temp_1;
    Object decff_1_arg, svref_new_value;
    SI_Long icp_position, position_1;
    Declare_special(1);

    x_note_fn_call(50,30);
    temp = FIXNUM_ADD1(Current_read_icp_byte_position);
    Current_read_icp_byte_position = temp;
    array = ISVREF(Current_icp_buffer,(SI_Long)4L);
    icp_position = IFIX(Current_read_icp_byte_position);
    position_1 = icp_position + icp_position;
    Number_of_icp_bytes_left_in_message_series = 
	    FIXNUM_SUB1(FIX((UBYTE_8_ISAREF_1(array,position_1) << 
	    (SI_Long)8L) + UBYTE_8_ISAREF_1(array,position_1 + (SI_Long)1L)));
    temp = Current_icp_port;
    number_of_icp_bytes_left_in_current_buffer = FIXNUM_SUB1(ISVREF(temp,
	    (SI_Long)17L));
    SVREF(temp,FIX((SI_Long)17L)) = number_of_icp_bytes_left_in_current_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_left_in_current_buffer,Qnumber_of_icp_bytes_left_in_current_buffer,number_of_icp_bytes_left_in_current_buffer,
	    0);
      if (IFIX(Number_of_icp_bytes_left_in_current_buffer) == (SI_Long)0L)
	  temp_1 = ensure_next_icp_message_series();
      else {
	  if (Icp_read_trace_cutoff_level_qm && 
		  (EQ(Icp_read_trace_cutoff_level_qm,T) || 
		  IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)1L))
	      emit_icp_read_trace(Nil,FIX((SI_Long)0L),
		      FIXNUM_ADD1(Number_of_icp_bytes_left_in_message_series),
		      string_constant,Nil,Qmessage_series,Nil,Nil,T,Nil);
	  Number_of_icp_bytes_ready_to_read = 
		  FIXNUM_MIN(Number_of_icp_bytes_left_in_current_buffer,
		  Number_of_icp_bytes_left_in_message_series);
	  decff_1_arg = Number_of_icp_bytes_ready_to_read;
	  temp = FIXNUM_MINUS(Number_of_icp_bytes_left_in_message_series,
		  decff_1_arg);
	  Number_of_icp_bytes_left_in_message_series = temp;
	  temp = Current_icp_port;
	  decff_1_arg = Number_of_icp_bytes_ready_to_read;
	  svref_new_value = FIXNUM_MINUS(ISVREF(temp,(SI_Long)17L),
		  decff_1_arg);
	  SVREF(temp,FIX((SI_Long)17L)) = svref_new_value;
	  temp_1 = T;
      }
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* READ-ICP-SUSPEND */
Object read_icp_suspend()
{
    Object temp;

    x_note_fn_call(50,31);
    if (current_icp_read_task_resumable_p()) {
	Resumable_icp_state = Nil;
	temp = Icp_suspend;
    }
    else
	temp = icp_out_of_synch(1,FIX((SI_Long)5L));
    return VALUES_1(temp);
}

static Object string_constant_1;   /* "read \"end-of-message-group\" message series" */

/* PROCESS-END-OF-MESSAGE-GROUP */
Object process_end_of_message_group(ok_if_none_qm,read_message_group_end_p)
    Object ok_if_none_qm, read_message_group_end_p;
{
    Object temp, svref_new_value;

    x_note_fn_call(50,32);
    if ( !TRUEP(read_message_group_end_p) && 
	    current_icp_read_task_resumable_p()) {
	Resumable_icp_state = Nil;
	return VALUES_1(Icp_suspend);
    }
    if ( !TRUEP(ok_if_none_qm))
	icp_out_of_synch(1,FIX((SI_Long)5L));
    if (read_message_group_end_p) {
	temp = FIXNUM_ADD1(Current_read_icp_byte_position);
	Current_read_icp_byte_position = temp;
	temp = Current_icp_port;
	svref_new_value = FIXNUM_SUB1(ISVREF(temp,(SI_Long)17L));
	SVREF(temp,FIX((SI_Long)17L)) = svref_new_value;
    }
    if (Icp_read_trace_cutoff_level_qm && 
	    (EQ(Icp_read_trace_cutoff_level_qm,T) || 
	    IFIX(Icp_read_trace_cutoff_level_qm) >= (SI_Long)1L))
	emit_icp_read_trace(Nil,FIX((SI_Long)0L),FIX((SI_Long)1L),
		string_constant_1,Nil,Qmessage_series,Nil,Nil,T,Nil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(At_end_of_icp_message_group_qm, Qat_end_of_icp_message_group_qm);

/* ALL-MESSAGES-PROCESSED? */
Object all_messages_processed_qm(head_icp_buffer,
	    icp_byte_index_of_end_of_message_group_qm,icp_input_port)
    Object head_icp_buffer, icp_byte_index_of_end_of_message_group_qm;
    Object icp_input_port;
{
    Object icp_buffer, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(50,33);
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
Object ready_for_next_icp_message_group(icp_input_port)
    Object icp_input_port;
{
    Object message_group_complete_qm, temp, head_icp_buffer;

    x_note_fn_call(50,34);
    message_group_complete_qm = ISVREF(icp_input_port,(SI_Long)16L);
    temp = ISVREF(icp_input_port,(SI_Long)12L);
    head_icp_buffer = CAR(temp);
    temp = message_group_complete_qm ? ( 
	    !TRUEP(all_messages_processed_qm(head_icp_buffer,
	    message_group_complete_qm,icp_input_port)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* PROCESS-NEXT-ICP-MESSAGE-GROUP-IF-READY */
Object process_next_icp_message_group_if_ready(icp_input_port)
    Object icp_input_port;
{
    Object icp_socket, disable_resumability, current_icp_socket, system_name;
    Object current_system_name, message_group_complete_qm, head_icp_buffer;
    Object ready_for_next_message_group_p, current_icp_port;
    Object current_standard_icp_object_index_space;
    Object current_temporary_icp_object_index_space;
    Object number_of_icp_bytes_left_in_message_series, current_icp_buffer;
    Object number_of_icp_bytes_ready_to_read, at_end_of_icp_message_group_qm;
    Object current_read_icp_byte_position, icp_buffer, gensymed_symbol_3;
    Object structure_being_reclaimed, temp, svref_arg_2, workstation;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Declare_special(13);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(50,35);
    icp_socket = ISVREF(icp_input_port,(SI_Long)2L);
    disable_resumability = IFIX(ISVREF(icp_socket,(SI_Long)21L)) >= 
	    (SI_Long)17L ? ISVREF(icp_socket,(SI_Long)53L) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
	    12);
      current_icp_socket = icp_socket;
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      11);
	system_name = ISVREF(icp_socket,(SI_Long)49L);
	current_system_name = EQ(system_name,Qg2) ? Qab : system_name;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_name,Qcurrent_system_name,current_system_name,
		10);
	  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      message_group_complete_qm = ISVREF(icp_input_port,(SI_Long)16L);
	      head_icp_buffer = ISVREF(icp_input_port,(SI_Long)12L);
	      ready_for_next_message_group_p = message_group_complete_qm ? 
		      ( !TRUEP(all_messages_processed_qm(head_icp_buffer,
		      message_group_complete_qm,icp_input_port)) ? T : 
		      Nil) : Qnil;
	      if (ready_for_next_message_group_p) {
		  current_icp_port = icp_input_port;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			  9);
		    current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			    8);
		      current_standard_icp_object_index_space = 
			      ISVREF(Current_icp_port,(SI_Long)8L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_standard_icp_object_index_space,Qcurrent_standard_icp_object_index_space,current_standard_icp_object_index_space,
			      7);
			current_temporary_icp_object_index_space = 
				ISVREF(Current_icp_port,(SI_Long)19L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_temporary_icp_object_index_space,Qcurrent_temporary_icp_object_index_space,current_temporary_icp_object_index_space,
				6);
			  number_of_icp_bytes_left_in_message_series = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_left_in_message_series,Qnumber_of_icp_bytes_left_in_message_series,number_of_icp_bytes_left_in_message_series,
				  5);
			    current_icp_buffer = head_icp_buffer;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				    4);
			      number_of_icp_bytes_ready_to_read = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_ready_to_read,Qnumber_of_icp_bytes_ready_to_read,number_of_icp_bytes_ready_to_read,
				      3);
				at_end_of_icp_message_group_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(At_end_of_icp_message_group_qm,Qat_end_of_icp_message_group_qm,at_end_of_icp_message_group_qm,
					2);
				  current_read_icp_byte_position = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_read_icp_byte_position,Qcurrent_read_icp_byte_position,current_read_icp_byte_position,
					  1);
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
					Current_read_icp_byte_position = 
						FIX(gensymed_symbol - 
						gensymed_symbol_1 - 
						gensymed_symbol_2);
				    }
				    if (ISVREF(icp_socket,(SI_Long)17L)) {
					gensymed_symbol_3 = Nil;
				      next_loop:
					gensymed_symbol_3 = 
						ISVREF(icp_socket,
						(SI_Long)16L);
					if (CAS_SVREF(icp_socket,
						(SI_Long)16L,
						gensymed_symbol_3,Nil)) {
					    if (gensymed_symbol_3) {
						if (EQ(gensymed_symbol_3,
							Current_schedule_task))
						    Current_schedule_task 
							    = Nil;
						if (ISVREF(gensymed_symbol_3,
							(SI_Long)6L))
						    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol_3);
						inline_note_reclaim_cons(gensymed_symbol_3,
							Nil);
						structure_being_reclaimed 
							= gensymed_symbol_3;
						PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
							0);
						  reclaim_schedule_task_args(ISVREF(gensymed_symbol_3,
							  (SI_Long)9L));
						  SVREF(gensymed_symbol_3,
							  FIX((SI_Long)9L)) 
							  = Nil;
						POP_SPECIAL();
						temp = 
							ISVREF(Chain_of_available_schedule_tasks_vector,
							IFIX(Current_thread_index));
						SVREF(gensymed_symbol_3,
							FIX((SI_Long)0L)) 
							= temp;
						temp = 
							Chain_of_available_schedule_tasks_vector;
						svref_arg_2 = 
							Current_thread_index;
						SVREF(temp,svref_arg_2) = 
							gensymed_symbol_3;
					    }
					    goto end_1;
					}
					goto next_loop;
				      end_loop:
				      end_1:;
				    }
				    handle_icp_messages(Nil);
				    if (EQ(ISVREF(Current_icp_socket,
					    (SI_Long)25L),Qtelewindows)) {
					workstation = 
						ISVREF(Current_icp_socket,
						(SI_Long)23L);
					if (workstation)
					    maybe_schedule_service_workstation(workstation,
						    T);
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
	      }
	      result = VALUES_1(ready_for_next_message_group_p);
	  }
	  POP_LOCAL_ALLOCATION(0,0);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_transacting_message_group, Qicp_socket_transacting_message_group);

DEFINE_VARIABLE_WITH_SYMBOL(At_end_of_icp_message_block_qm, Qat_end_of_icp_message_block_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_message_trace_stream_qm, Qicp_message_trace_stream_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Handling_solitary_i_am_alive_qm, Qhandling_solitary_i_am_alive_qm);

static Object Qunknown_message;    /* unknown-message */

static Object Qhandle_icp_acknowledge_shutdown;  /* handle-icp-acknowledge-shutdown */

static Object Qhandle_icp_message_group_id;  /* handle-icp-message-group-id */

static Object Qhandle_icp_i_am_alive;  /* handle-icp-i-am-alive */

/* HANDLE-ICP-MESSAGES */
Object handle_icp_messages(exit_at_end_of_message_block_qm)
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

    x_note_fn_call(50,36);
    current_resumable_icp_read_task = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_resumable_icp_read_task,Qcurrent_resumable_icp_read_task,current_resumable_icp_read_task,
	    5);
      resumable_icp_read_ignore_p = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Resumable_icp_read_ignore_p,Qresumable_icp_read_ignore_p,resumable_icp_read_ignore_p,
	      4);
	parent_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	at_end_of_icp_message_block_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(At_end_of_icp_message_block_qm,Qat_end_of_icp_message_block_qm,at_end_of_icp_message_block_qm,
		3);
	  icp_socket_transacting_message_group = parent_icp_socket;
	  PUSH_SPECIAL_WITH_SYMBOL(Icp_socket_transacting_message_group,Qicp_socket_transacting_message_group,icp_socket_transacting_message_group,
		  2);
	    ignore_p = FIXNUM_EQ(ISVREF(parent_icp_socket,(SI_Long)15L),
		    Icp_connection_awaiting_acknowledgement);
	    current_icp_message_handler_array = Icp_message_handler_array;
	    icp_byte_qm = Nil;
	    message_count = (SI_Long)1L;
	    index_1 = Nil;
	    function_qm = Nil;
	    handler_name = Nil;
	    previous_handler_name = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    icp_byte_qm = read_icp_byte_or_message_group_end();
	    if ( !TRUEP(ab_loop_iter_flag_))
		message_count = message_count + (SI_Long)1L;
	    At_end_of_icp_message_group_qm =  !TRUEP(icp_byte_qm) ? T : Nil;
	    if (At_end_of_icp_message_group_qm)
		goto end_loop;
	    index_1 = FIX(IFIX(icp_byte_qm) - (SI_Long)64000L);
	    if ( !TRUEP(ab_loop_iter_flag_))
		previous_handler_name = handler_name;
	    if (IFIX(index_1) <= (SI_Long)0L || IFIX(index_1) >= (SI_Long)750L)
		icp_out_of_synch(2,FIX((SI_Long)3L),index_1);
	    else {
		function_qm = ISVREF(current_icp_message_handler_array,
			IFIX(index_1));
		if ( !TRUEP(function_qm))
		    icp_out_of_synch(2,Qunknown_message,index_1);
	    }
	    handler_name = ISVREF(Icp_message_handler_name_array,
		    IFIX(index_1));
	    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
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
		  SVREF(temp,svref_arg_2) = handler_name;
	      }
	      temp = ISVREF(Current_icp_port,(SI_Long)2L);
	      SVREF(temp,FIX((SI_Long)8L)) = index_1;
	      if (ignore_p) {
		next_loop_1:
		  if ( !TRUEP(read_icp_byte_if_any()))
		      goto end_loop_1;
		  goto next_loop_1;
		end_loop_1:
		  if (EQ(handler_name,Qhandle_icp_acknowledge_shutdown))
		      handle_icp_acknowledge_shutdown();
	      }
	      else if (Current_resumable_icp_read_task)
		  resume_icp_task_1(function_qm);
	      else if (message_count == (SI_Long)2L && EQ(handler_name,
		      Qhandle_icp_message_group_id) && 
		      EQ(previous_handler_name,Qhandle_icp_i_am_alive)) {
		  handling_solitary_i_am_alive_qm = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Handling_solitary_i_am_alive_qm,Qhandling_solitary_i_am_alive_qm,handling_solitary_i_am_alive_qm,
			  0);
		    inline_funcall_0(function_qm);
		  POP_SPECIAL();
	      }
	      else
		  inline_funcall_0(function_qm);
	    POP_SPECIAL();
	    ensure_remote_icp_version_info(parent_icp_socket,handler_name);
	    if (exit_at_end_of_message_block_qm && 
		    At_end_of_icp_message_block_qm || 
		    At_end_of_icp_message_group_qm ||  
		    !TRUEP(icp_connection_can_process_messages_qm(parent_icp_socket)))
		goto end_loop;
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop;
	  end_loop:
	    maybe_finish_current_icp_read_task();
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Debug_out_of_synch, Qdebug_out_of_synch);

/* DEBUG-OUT-OF-SYNCH */
Object debug_out_of_synch(code,icp_byte,current_icp_buffer,
	    read_icp_byte_position,number_of_icp_bytes_ready_to_read,
	    icp_socket)
    Object code, icp_byte, current_icp_buffer, read_icp_byte_position;
    Object number_of_icp_bytes_ready_to_read, icp_socket;
{
    Declare_special(2);
    Object result;

    x_note_fn_call(50,37);
    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_ready_to_read,Qnumber_of_icp_bytes_ready_to_read,number_of_icp_bytes_ready_to_read,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
	      0);
	if (Debug_out_of_synch) {
	    format((SI_Long)4L,T,"~%ICP out of synch ~D on socket ~A",code,
		    wide_string_to_gensym_string(icp_socket_description(icp_socket)));
	    format((SI_Long)3L,T,"~%icp-byte=~D",icp_byte);
	    format((SI_Long)3L,T,"~%icp-byte-position=~D",
		    read_icp_byte_position);
	    format((SI_Long)3L,T,"~%icp-bytes-ready-to-read=~d",
		    Number_of_icp_bytes_ready_to_read);
	    print_icp_buffer_byte_contents(Current_icp_buffer);
	    result = format((SI_Long)2L,T,"~%");
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_2;   /* "ICP ~A on " */

static Object Qab_warning;         /* warning */

static Object string_constant_3;   /* "warning" */

static Object string_constant_4;   /* "error" */

static Object Qno_error;           /* no-error */

static Object string_constant_5;   /* "interface ~NF (" */

static Object string_constant_6;   /* "socket " */

static Object string_constant_7;   /* ")" */

static Object string_constant_8;   /* ": " */

/* TWRITE-ICP-ERROR */
Object twrite_icp_error varargs_1(int, n)
{
    Object error_type, error_string_or_out_of_synch_case;
    Object arg1, arg2, arg3, interface_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(50,38);
    INIT_ARGS_nonrelocating();
    error_type = REQUIRED_ARG_nonrelocating();
    error_string_or_out_of_synch_case = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tformat(2,string_constant_2,EQ(error_type,Qab_warning) ? 
	    string_constant_3 : string_constant_4);
    interface_1 = Nil;
    interface_1 = find_network_interface_for_icp_socket(Current_icp_socket,
	    Qno_error);
    if (text_string_p(interface_1) || STRINGP(interface_1) ||  
	    !TRUEP(superblock_qm_function(interface_1)))
	interface_1 = Nil;
    if (interface_1)
	tformat(2,string_constant_5,interface_1);
    if ( !TRUEP(interface_1))
	tformat(1,string_constant_6);
    twrite_icp_socket_connection_name(Current_icp_socket);
    if (interface_1)
	tformat(1,string_constant_7);
    tformat(1,string_constant_8);
    return tformat(4,error_string_or_out_of_synch_case,arg1,arg2,arg3);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* ICP-ERROR-MESSAGE-STRING */
Object icp_error_message_string(error_type,
	    error_string_or_out_of_synch_case,arg1,arg2,arg3)
    Object error_type, error_string_or_out_of_synch_case, arg1, arg2, arg3;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(50,39);
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
	      twrite_icp_error(5,error_type,
		      error_string_or_out_of_synch_case,arg1,arg2,arg3);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qoutput;             /* output */

static Object Qresumable_error;    /* resumable-error */

static Object list_constant;       /* # */

static Object Qrpc_error;          /* rpc-error */

static Object Qinput;              /* input */

/* ICP-ERROR-INTERNAL */
Object icp_error_internal(error_type,error_string_or_out_of_synch_case,
	    arg1,arg2,arg3)
    Object error_type, error_string_or_out_of_synch_case, arg1, arg2, arg3;
{
    Object resumable_icp_state, direction, resumable_output_p, shutdownp, temp;
    Object string2, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(50,40);
    resumable_icp_state = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Resumable_icp_state,Qresumable_icp_state,resumable_icp_state,
	    0);
      direction = ISVREF(Current_icp_port,(SI_Long)3L);
      resumable_output_p = EQ(direction,Qoutput) && 
	      Writing_resumable_icp_messages_p ? ( 
	      !EQ(ISVREF(Current_icp_socket,(SI_Long)25L),Qtelewindows) ? 
	      T : Nil) : Qnil;
      if (EQ(error_type,Qab_warning))
	  shutdownp = Nil;
      else if (EQ(error_type,Qresumable_error))
	  shutdownp =  !TRUEP(resumable_output_p) ? T : Nil;
      else
	  shutdownp = T;
      give_icp_error_warning_message(shutdownp,error_type,
	      error_string_or_out_of_synch_case,arg1,arg2,arg3);
      if ( !EQ(error_type,Qab_warning)) {
	  if (memq_function(ISVREF(Current_icp_socket,(SI_Long)25L),
		  list_constant)) {
	      temp = Current_icp_socket;
	      remote_procedure_error(temp,Qrpc_error,
		      icp_error_message_string(error_type,
		      error_string_or_out_of_synch_case,arg1,arg2,arg3),Nil);
	  }
	  else {
	      string2 = icp_error_message_string(error_type,
		      error_string_or_out_of_synch_case,arg1,arg2,arg3);
	      notify_user(1,string2);
	      reclaim_text_string(string2);
	  }
      }
      if (shutdownp)
	  flush_and_shutdown_icp_socket(Current_icp_socket);
      if ( !EQ(error_type,Qab_warning)) {
	  if (resumable_output_p) {
	      Icp_error_suspend_p = T;
	      temp_1 = Icp_suspend;
	  }
	  else if (Abort_for_icp_catcher_qm) {
	      if (EQ(Qinput,direction))
		  kill_current_icp_read_task();
	      result = VALUES_1(Nil);
	      THROW(Abort_for_icp_catcher_qm,result);
	  }
	  else
	      temp_1 = Nil;
      }
      else
	  temp_1 = Nil;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* ABORT-FOR-ICP */
Object abort_for_icp()
{
    Object result;

    x_note_fn_call(50,41);
    if (Abort_for_icp_catcher_qm) {
	result = VALUES_1(Nil);
	THROW(Abort_for_icp_catcher_qm,result);
    }
    else
	abort_g2(0);
    return VALUES_1(Nil);
}

static Object string_constant_9;   /* "ICP: Socket ~a (~a) received unknown message code ~a; ~
				    *              closing broken connection after message ~a"
				    */

static Object string_constant_10;  /* "ICP: Protocol out-of-synch (case ~d) ~
				    *              for ICP socket ~a with ~a; ~
				    *              closing broken connection after message ~a"
				    */

static Object Qprotocol_out_of_synch_1;  /* protocol-out-of-synch-1 */

static Object Qprotocol_out_of_synch_3;  /* protocol-out-of-synch-3 */

static Object Qprotocol_out_of_synch_4;  /* protocol-out-of-synch-4 */

static Object Qprotocol_out_of_synch_5;  /* protocol-out-of-synch-5 */

static Object Qprotocol_out_of_synch_6;  /* protocol-out-of-synch-6 */

static Object Qprotocol_out_of_synch_7;  /* protocol-out-of-synch-7 */

/* ICP-OUT-OF-SYNCH */
Object icp_out_of_synch varargs_1(int, n)
{
    Object case_1;
    Object message_code, parent_socket, icp_socket_transacting_message_group;
    Object temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(50,42);
    INIT_ARGS_nonrelocating();
    case_1 = REQUIRED_ARG_nonrelocating();
    message_code = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    parent_socket = ISVREF(Current_icp_port,(SI_Long)2L);
    if ( !(Abort_for_icp_catcher_qm || EQ(case_1,FIX((SI_Long)3L)) || 
	    EQ(case_1,Qunknown_message))) {
	if (EQ(case_1,Qunknown_message))
	    notify_user(5,string_constant_9,ISVREF(parent_socket,
		    (SI_Long)1L),ISVREF(parent_socket,(SI_Long)2L),
		    message_code,ISVREF(parent_socket,(SI_Long)8L));
	else
	    notify_user(5,string_constant_10,case_1,ISVREF(parent_socket,
		    (SI_Long)1L),ISVREF(parent_socket,(SI_Long)2L),
		    ISVREF(parent_socket,(SI_Long)8L));
    }
    icp_socket_transacting_message_group = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Icp_socket_transacting_message_group,Qicp_socket_transacting_message_group,icp_socket_transacting_message_group,
	    0);
      if (EQ(case_1,Qunknown_message))
	  temp = Qunknown_message;
      else if (EQ(case_1,FIX((SI_Long)1L)))
	  temp = Qprotocol_out_of_synch_1;
      else if (EQ(case_1,FIX((SI_Long)3L)))
	  temp = Qprotocol_out_of_synch_3;
      else if (EQ(case_1,FIX((SI_Long)4L)))
	  temp = Qprotocol_out_of_synch_4;
      else if (EQ(case_1,FIX((SI_Long)5L)))
	  temp = Qprotocol_out_of_synch_5;
      else if (EQ(case_1,FIX((SI_Long)6L)))
	  temp = Qprotocol_out_of_synch_6;
      else if (EQ(case_1,FIX((SI_Long)7L)))
	  temp = Qprotocol_out_of_synch_7;
      else
	  temp = Qnil;
      shutdown_icp_socket_connection(2,parent_socket,temp);
    POP_SPECIAL();
    return abort_for_icp();
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_buffers_for_message_group, Qicp_buffers_for_message_group);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm, Qicp_byte_position_of_start_of_message_series_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm, Qicp_buffer_of_start_of_message_series_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Number_of_icp_bytes_in_message_group, Qnumber_of_icp_bytes_in_message_group);

/* WRITE-ICP-MAYBE-SUSPEND */
Object write_icp_maybe_suspend()
{
    Object temp;

    x_note_fn_call(50,43);
    if (Writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer),
	    Minimum_message_series_size_before_suspending)) {
	Resumable_icp_state = Nil;
	temp = Icp_suspend;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* WRITE-ICP-BYTE */
Object write_icp_byte(icp_byte)
    Object icp_byte;
{
    Object temp, array, array_1;
    SI_Long length_1, start, icp_position, position_1, value, temp_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(50,44);
    if (Writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer),
	    Minimum_message_series_size_before_suspending)) {
	Resumable_icp_state = Nil;
	temp = Icp_suspend;
    }
    else {
	length_1 = IFIX(Number_of_icp_bytes_to_fill_buffer);
	if ((SI_Long)0L == length_1) {
	    write_get_new_buffer();
	    length_1 = IFIX(Number_of_icp_bytes_to_fill_buffer);
	}
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = IFIX(FIXNUM_ADD1(Current_write_icp_byte_position));
	Current_write_icp_byte_position = FIX(start - (SI_Long)1L + 
		(SI_Long)1L);
	Number_of_icp_bytes_to_fill_buffer = FIX(length_1 - (SI_Long)1L);
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
Object get_icp_write_buffer()
{
    Object array;
    SI_Long length_1, start;

    x_note_fn_call(50,45);
    if (Writing_resumable_icp_messages_p && 
	    FIXNUM_GT(FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer),
	    Minimum_message_series_size_before_suspending)) {
	Resumable_icp_state = Nil;
	return VALUES_1(Icp_suspend);
    }
    else {
	length_1 = IFIX(Number_of_icp_bytes_to_fill_buffer);
	if ((SI_Long)0L == length_1) {
	    write_get_new_buffer();
	    length_1 = IFIX(Number_of_icp_bytes_to_fill_buffer);
	}
	array = ISVREF(Current_icp_buffer,(SI_Long)4L);
	start = IFIX(FIXNUM_ADD1(Current_write_icp_byte_position));
	return VALUES_3(array,FIX(start),FIX(length_1));
    }
}

/* WRITE-GET-NEW-BUFFER */
Object write_get_new_buffer()
{
    Object temp, tail, copy, new_icp_buffer;
    SI_Long bytes_available_in_buffer, incff_1_arg;
    SI_Long number_of_icp_bytes_for_message_series_new_value;

    x_note_fn_call(50,46);
    if (Current_icp_buffer) {
	temp = Current_icp_buffer;
	ISVREF(temp,(SI_Long)3L) = FIX((SI_Long)4096L);
    }
    tail = ISVREF(Current_icp_port,(SI_Long)13L);
    if ( !EQ(ISVREF(Current_icp_port,(SI_Long)12L),tail) &&  
	    !TRUEP(ISVREF(tail,(SI_Long)5L)) && IFIX(ISVREF(tail,
	    (SI_Long)3L)) < (SI_Long)4096L) {
	copy = copy_icp_buffer(tail);
	temp = ISVREF(copy,(SI_Long)3L);
	SVREF(copy,FIX((SI_Long)2L)) = temp;
	new_icp_buffer = copy;
    }
    else
	new_icp_buffer = 
		make_icp_buffer_internal_1(make_variable_fill_icp_buffer());
    if (Icp_buffers_for_message_group) {
	temp = Current_icp_buffer;
	SVREF(temp,FIX((SI_Long)1L)) = new_icp_buffer;
    }
    else
	Icp_buffers_for_message_group = new_icp_buffer;
    Current_icp_buffer = new_icp_buffer;
    bytes_available_in_buffer = (SI_Long)2048L - 
	    (IFIX(ISVREF(Current_icp_buffer,(SI_Long)3L)) >>  -  - 
	    (SI_Long)1L);
    Number_of_icp_bytes_to_fill_buffer = FIX(bytes_available_in_buffer);
    incff_1_arg = bytes_available_in_buffer;
    number_of_icp_bytes_for_message_series_new_value = 
	    IFIX(Number_of_icp_bytes_for_message_series) + incff_1_arg;
    Number_of_icp_bytes_for_message_series = 
	    FIX(number_of_icp_bytes_for_message_series_new_value);
    Current_write_icp_byte_position = FIX((SI_Long)2048L - 
	    bytes_available_in_buffer - (SI_Long)1L);
    if ((SI_Long)60952L <= IFIX(Number_of_icp_bytes_for_message_series) && 
	    Disable_resumability)
	start_icp_message_series();
    return VALUES_1(Nil);
}

/* STOP-FILLING-ICP-BUFFER-AT-END-OF-ICP-MESSAGE-GROUP */
Object stop_filling_icp_buffer_at_end_of_icp_message_group()
{
    Object temp, decff_1_arg;
    SI_Long svref_new_value;

    x_note_fn_call(50,47);
    temp = Current_icp_buffer;
    svref_new_value = (SI_Long)2048L - 
	    IFIX(Number_of_icp_bytes_to_fill_buffer) << (SI_Long)1L;
    ISVREF(temp,(SI_Long)3L) = FIX(svref_new_value);
    decff_1_arg = Number_of_icp_bytes_to_fill_buffer;
    temp = FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,decff_1_arg);
    Number_of_icp_bytes_for_message_series = temp;
    Number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Writing_icp_message_group, Qwriting_icp_message_group);

/* NEXT-ICP-MESSAGE-GROUP */
Object next_icp_message_group()
{
    x_note_fn_call(50,48);
    end_icp_message_group();
    Number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
    Icp_buffers_for_message_group = Nil;
    Icp_byte_position_of_start_of_message_series_qm = Nil;
    Number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
    Current_icp_buffer = Nil;
    Current_write_icp_byte_position = Nil;
    Number_of_icp_bytes_in_message_group = FIX((SI_Long)0L);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Do_icp_flow_control_qm, Qdo_icp_flow_control_qm);

/* UPDATE-I-AM-ALIVE-INFO-AT-END-OF-MESSAGE-GROUP */
Object update_i_am_alive_info_at_end_of_message_group(i_am_alive_info)
    Object i_am_alive_info;
{
    Object message_group_id, gensymed_symbol, first_1, last_1, temp, next;
    SI_Long id_for_last_message_group_written, message_group_final_byte_count;
    SI_Long incff_1_arg, svref_new_value;

    x_note_fn_call(50,49);
    message_group_id = ISVREF(i_am_alive_info,(SI_Long)7L);
    id_for_last_message_group_written = FIXNUM_EQ(message_group_id,
	    Most_positive_fixnum) ? (SI_Long)0L : 
	    IFIX(FIXNUM_ADD1(message_group_id));
    message_group_final_byte_count = 
	    IFIX(FIXNUM_ADD(Number_of_icp_bytes_in_message_group,
	    FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer))) + (SI_Long)3L;
    ISVREF(i_am_alive_info,(SI_Long)7L) = 
	    FIX(id_for_last_message_group_written);
    send_icp_message_group_id(FIX(id_for_last_message_group_written),
	    FIX(message_group_final_byte_count));
    gensymed_symbol = icp_cons_1(FIX(id_for_last_message_group_written),
	    FIX(message_group_final_byte_count));
    gensymed_symbol = icp_cons_1(gensymed_symbol,Nil);
  next_loop:
    first_1 = ISVREF(i_am_alive_info,(SI_Long)12L);
    last_1 = ISVREF(i_am_alive_info,(SI_Long)13L);
    temp = ISVREF(i_am_alive_info,(SI_Long)13L);
    next = CDR(temp);
    if ( !TRUEP(first_1)) {
	if (CAS_SVREF(i_am_alive_info,(SI_Long)12L,first_1,gensymed_symbol)) {
	    CAS_SVREF(i_am_alive_info,(SI_Long)13L,last_1,gensymed_symbol);
	    goto end_1;
	}
    }
    else if (EQ(last_1,ISVREF(i_am_alive_info,(SI_Long)13L))) {
	if ( !TRUEP(next)) {
	    if (CAS_CDR(last_1,next,gensymed_symbol)) {
		CAS_SVREF(i_am_alive_info,(SI_Long)13L,last_1,gensymed_symbol);
		goto end_1;
	    }
	}
	else
	    CAS_SVREF(i_am_alive_info,(SI_Long)13L,last_1,next);
    }
    goto next_loop;
  end_loop:
  end_1:;
    incff_1_arg = message_group_final_byte_count;
    svref_new_value = IFIX(ISVREF(i_am_alive_info,(SI_Long)14L)) + incff_1_arg;
    ISVREF(i_am_alive_info,(SI_Long)14L) = FIX(svref_new_value);
    return update_icp_connection_clogged_p(i_am_alive_info,T);
}

static Object Qhandle_unclogged_connection_if_necessary;  /* handle-unclogged-connection-if-necessary */

/* UPDATE-ICP-CONNECTION-CLOGGED-P */
Object update_icp_connection_clogged_p(i_am_alive_info,
	    side_sending_i_am_alive_p)
    Object i_am_alive_info, side_sending_i_am_alive_p;
{
    Object was_clogged_p, fn, new_clogged_p, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(50,50);
    was_clogged_p = ISVREF(i_am_alive_info,(SI_Long)2L);
    fn = ISVREF(i_am_alive_info,(SI_Long)10L);
    new_clogged_p = fn ? FUNCALL_2(fn,Current_icp_socket,i_am_alive_info) :
	     Qnil;
    SVREF(i_am_alive_info,FIX((SI_Long)2L)) = new_clogged_p;
    if (was_clogged_p &&  !TRUEP(side_sending_i_am_alive_p) &&  
	    !TRUEP(ISVREF(i_am_alive_info,(SI_Long)2L))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(i_am_alive_info,(SI_Long)17L);
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
	SVREF(task,FIX((SI_Long)7L)) = 
		Qhandle_unclogged_connection_if_necessary;
	temp = SYMBOL_FUNCTION(Qhandle_unclogged_connection_if_necessary);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = i_am_alive_info;
	new_1 = task;
	if (CAS_SVREF(i_am_alive_info,(SI_Long)17L,old,new_1)) {
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
	    return VALUES_1(task);
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
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* END-ICP-MESSAGE-GROUP */
Object end_icp_message_group()
{
    Object i_am_alive_info_qm;

    x_note_fn_call(50,51);
    if (Icp_buffers_for_message_group) {
	if ( !TRUEP(Writing_resumable_icp_messages_p)) {
	    i_am_alive_info_qm = ISVREF(Current_icp_socket,(SI_Long)24L);
	    if (i_am_alive_info_qm)
		update_i_am_alive_info_at_end_of_message_group(i_am_alive_info_qm);
	}
	start_icp_message_series();
	stop_filling_icp_buffer_at_end_of_icp_message_group();
	end_icp_message_series_if_any();
	transmit_completed_icp_message_group();
    }
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "message series" */

/* START-WRITING-ICP-MESSAGE */
Object start_writing_icp_message(icp_message_type_code)
    Object icp_message_type_code;
{
    Object bytes_in_current_message_series, writing_resumable_icp_messages_p;
    Declare_special(1);

    x_note_fn_call(50,52);
    bytes_in_current_message_series = 
	    FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
	    Number_of_icp_bytes_to_fill_buffer);
    if ((SI_Long)0L == IFIX(bytes_in_current_message_series) || 
	    FIXNUM_LT(Minimum_message_series_size_before_beginning_new_series,
	    bytes_in_current_message_series)) {
	if (Icp_write_trace_cutoff_level_qm && 
		(EQ(Icp_write_trace_cutoff_level_qm,T) || 
		IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)1L))
	    emit_icp_write_trace(T,Nil,Nil,string_constant_11,Nil,
		    Qmessage_series,Nil,Nil,T,Nil);
	start_icp_message_series();
    }
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      write_icp_byte(FIX(IFIX(icp_message_type_code) + (SI_Long)64000L));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* START-ICP-MESSAGE-SERIES */
Object start_icp_message_series()
{
    Object writing_resumable_icp_messages_p;
    Declare_special(1);

    x_note_fn_call(50,53);
    end_icp_message_series_if_any();
    Number_of_icp_bytes_for_message_series = 
	    Number_of_icp_bytes_to_fill_buffer;
    writing_resumable_icp_messages_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
	    0);
      write_icp_byte(FIX((SI_Long)1L));
    POP_SPECIAL();
    Icp_buffer_of_start_of_message_series_qm = Current_icp_buffer;
    Icp_byte_position_of_start_of_message_series_qm = 
	    Current_write_icp_byte_position;
    return VALUES_1(Nil);
}

Object Icp_message_too_long_warning = UNBOUND;

/* TRANSMIT-COMPLETED-ICP-MESSAGE-GROUP */
Object transmit_completed_icp_message_group()
{
    Object icp_output_port, tail, buffer, svref_new_value, next_buffer;
    Object new_cons;

    x_note_fn_call(50,54);
    icp_output_port = Current_icp_port;
    if (Icp_buffers_for_message_group) {
	tail = ISVREF(icp_output_port,(SI_Long)13L);
	buffer = Icp_buffers_for_message_group;
	if (EQ(ISVREF(tail,(SI_Long)4L),ISVREF(buffer,(SI_Long)4L))) {
	    svref_new_value = ISVREF(buffer,(SI_Long)3L);
	    SVREF(tail,FIX((SI_Long)3L)) = svref_new_value;
	    Icp_buffers_for_message_group = ISVREF(buffer,(SI_Long)1L);
	    reclaim_icp_buffer(buffer);
	}
	if (Icp_buffers_for_message_group) {
	    svref_new_value = Icp_buffers_for_message_group;
	    SVREF(tail,FIX((SI_Long)1L)) = svref_new_value;
	    buffer = Icp_buffers_for_message_group;
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
	    if (With_icp_buffer_coelescing_scope_qm) {
		transmit_icp_output_if_ready(icp_output_port,Nil);
		if ( !TRUEP(ISVREF(icp_output_port,(SI_Long)18L))) {
		    new_cons = gensym_cons_1(icp_output_port,
			    Icp_output_ports_to_flush);
		    SVREF(icp_output_port,FIX((SI_Long)18L)) = new_cons;
		    Icp_output_ports_to_flush = new_cons;
		}
	    }
	    else
		transmit_icp_output_if_ready(icp_output_port,T);
	}
    }
    return VALUES_1(Nil);
}

static Object string_constant_12;  /* "ICP message series too long -- please call Gensym customer support" */

static Object string_constant_13;  /* "wrote \"end-of-message-group\" message series" */

static Object string_constant_14;  /* "[finished writing message series]" */

/* END-ICP-MESSAGE-SERIES-IF-ANY */
Object end_icp_message_series_if_any()
{
    Object message_series_byte_count, array, incff_1_arg;
    Object number_of_icp_bytes_in_message_group_new_value;
    SI_Long icp_position, position_1, value, temp, gensymed_symbol;

    x_note_fn_call(50,55);
    if (Icp_buffers_for_message_group) {
	message_series_byte_count = 
		FIXNUM_MINUS(Number_of_icp_bytes_for_message_series,
		Number_of_icp_bytes_to_fill_buffer);
	if (IFIX(message_series_byte_count) > (SI_Long)63000L)
	    icp_error_internal(Qerror,string_constant_12,Nil,Nil,Nil);
	if (Icp_write_trace_cutoff_level_qm && 
		(EQ(Icp_write_trace_cutoff_level_qm,T) || 
		IFIX(Icp_write_trace_cutoff_level_qm) >= (SI_Long)1L))
	    emit_icp_write_trace(Nil,FIX((SI_Long)0L),
		    message_series_byte_count,
		    IFIX(message_series_byte_count) == (SI_Long)1L ? 
		    string_constant_13 : string_constant_14,Nil,
		    Qmessage_series,Nil,Nil,T,Nil);
	array = ISVREF(Icp_buffer_of_start_of_message_series_qm,(SI_Long)4L);
	icp_position = IFIX(Icp_byte_position_of_start_of_message_series_qm);
	position_1 = icp_position + icp_position;
	value = IFIX(message_series_byte_count);
	temp = value >>  -  - (SI_Long)8L;
	UBYTE_8_ISASET_1(array,position_1,temp);
	temp = position_1 + (SI_Long)1L;
	gensymed_symbol = (SI_Long)255L & value;
	UBYTE_8_ISASET_1(array,temp,gensymed_symbol);
	incff_1_arg = message_series_byte_count;
	number_of_icp_bytes_in_message_group_new_value = 
		FIXNUM_ADD(Number_of_icp_bytes_in_message_group,incff_1_arg);
	Number_of_icp_bytes_in_message_group = 
		number_of_icp_bytes_in_message_group_new_value;
	return VALUES_1(Number_of_icp_bytes_in_message_group);
    }
    else
	return VALUES_1(Nil);
}

void int2_INIT()
{
    Object AB_package, Qint2, G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(50,56);
    SET_PACKAGE("AB");
    Localnet_queued_icp_buffer_limit = FIX((SI_Long)3L);
    AB_package = STATIC_PACKAGE("AB");
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    Qgeneric = STATIC_SYMBOL("GENERIC",AB_package);
    Qicp_socket_index = STATIC_SYMBOL("ICP-SOCKET-INDEX",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_socket_index,Icp_socket_index);
    Qint2 = STATIC_SYMBOL("INT2",AB_package);
    record_system_variable(Qicp_socket_index,Qint2,FIX((SI_Long)0L),Qnil,
	    Qt,Qnil,Qnil);
    if (Shutdown_interval_for_disallowed_icp_connection_in_seconds == UNBOUND)
	Shutdown_interval_for_disallowed_icp_connection_in_seconds = 
		FIX((SI_Long)10L);
    if (Shutdown_interval_for_disallowed_icp_connection == UNBOUND)
	Shutdown_interval_for_disallowed_icp_connection = 
		fixnum_time_interval(FIX((SI_Long)1000L * 
		IFIX(Shutdown_interval_for_disallowed_icp_connection_in_seconds)));
    if (Negative_shutdown_interval_for_disallowed_icp_connection == UNBOUND)
	Negative_shutdown_interval_for_disallowed_icp_connection = 
		FIXNUM_NEGATE(Shutdown_interval_for_disallowed_icp_connection);
    Qrefused_icp_listener_connections = 
	    STATIC_SYMBOL("REFUSED-ICP-LISTENER-CONNECTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrefused_icp_listener_connections,
	    Refused_icp_listener_connections);
    record_system_variable(Qrefused_icp_listener_connections,Qint2,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qexecute = STATIC_SYMBOL("EXECUTE",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qconnect = STATIC_SYMBOL("CONNECT",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    Kfnord = STATIC_SYMBOL("FNORD",Pkeyword);
    if (Inhibit_icp_message_processing_enabled == UNBOUND)
	Inhibit_icp_message_processing_enabled = T;
    if (Inhibit_icp_message_processing == UNBOUND)
	Inhibit_icp_message_processing = Nil;
    if (Icp_sockets_waiting_for_icp_message_processing == UNBOUND)
	Icp_sockets_waiting_for_icp_message_processing = Nil;
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    if (Handle_ui_client_interface_messages_immediately_p == UNBOUND)
	Handle_ui_client_interface_messages_immediately_p = Nil;
    Qhandle_icp_messages = STATIC_SYMBOL("HANDLE-ICP-MESSAGES",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhandle_queued_icp_messages_task = 
	    STATIC_SYMBOL("HANDLE-QUEUED-ICP-MESSAGES-TASK",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_queued_icp_messages_task,
	    STATIC_FUNCTION(handle_queued_icp_messages_task,NIL,FALSE,1,1));
    Qbroken_while_transmitting = STATIC_SYMBOL("BROKEN-WHILE-TRANSMITTING",
	    AB_package);
    Qend_of_message_group = STATIC_SYMBOL("END-OF-MESSAGE-GROUP",AB_package);
    if (Priority_of_icp_message_service == UNBOUND)
	Priority_of_icp_message_service = FIX((SI_Long)3L);
    if (Priority_of_rpc_service == UNBOUND)
	Priority_of_rpc_service = FIX((SI_Long)6L);
    if (Priority_of_icp_control_messages == UNBOUND)
	Priority_of_icp_control_messages = FIX((SI_Long)7L);
    if (Resumable_priority_of_gsi_data_service == UNBOUND)
	Resumable_priority_of_gsi_data_service = FIX((SI_Long)4L);
    if (Resumable_priority_of_gsi_rpc_service == UNBOUND)
	Resumable_priority_of_gsi_rpc_service = FIX((SI_Long)6L);
    Qnumber_of_icp_bytes_left_in_message_series = 
	    STATIC_SYMBOL("NUMBER-OF-ICP-BYTES-LEFT-IN-MESSAGE-SERIES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnumber_of_icp_bytes_left_in_message_series,
	    Number_of_icp_bytes_left_in_message_series);
    record_system_variable(Qnumber_of_icp_bytes_left_in_message_series,
	    Qint2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_icp_buffer = STATIC_SYMBOL("CURRENT-ICP-BUFFER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_icp_buffer,Current_icp_buffer);
    record_system_variable(Qcurrent_icp_buffer,Qint2,Nil,Qnil,Qnil,Qnil,Qnil);
    Qnumber_of_icp_bytes_ready_to_read = 
	    STATIC_SYMBOL("NUMBER-OF-ICP-BYTES-READY-TO-READ",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qnumber_of_icp_bytes_ready_to_read,
	    Number_of_icp_bytes_ready_to_read);
    record_system_variable(Qnumber_of_icp_bytes_ready_to_read,Qint2,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qcurrent_read_icp_byte_position = 
	    STATIC_SYMBOL("CURRENT-READ-ICP-BYTE-POSITION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_read_icp_byte_position,
	    Current_read_icp_byte_position);
    record_system_variable(Qcurrent_read_icp_byte_position,Qint2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcurrent_write_icp_byte_position = 
	    STATIC_SYMBOL("CURRENT-WRITE-ICP-BYTE-POSITION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_write_icp_byte_position,
	    Current_write_icp_byte_position);
    record_system_variable(Qcurrent_write_icp_byte_position,Qint2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    if (Writing_resumable_icp_messages_p == UNBOUND)
	Writing_resumable_icp_messages_p = Nil;
    if (Icp_error_suspend_p == UNBOUND)
	Icp_error_suspend_p = Nil;
    if (Current_resumable_icp_read_task == UNBOUND)
	Current_resumable_icp_read_task = Nil;
    if (Resumable_icp_read_ignore_p == UNBOUND)
	Resumable_icp_read_ignore_p = Nil;
    string_constant = STATIC_STRING("[reading message series]");
    Qmessage_series = STATIC_SYMBOL("MESSAGE-SERIES",AB_package);
    string_constant_1 = 
	    STATIC_STRING("read \"end-of-message-group\" message series");
    Qat_end_of_icp_message_group_qm = 
	    STATIC_SYMBOL("AT-END-OF-ICP-MESSAGE-GROUP\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qat_end_of_icp_message_group_qm,
	    At_end_of_icp_message_group_qm);
    record_system_variable(Qat_end_of_icp_message_group_qm,Qint2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    if (Icp_socket_transacting_message_group == UNBOUND)
	Icp_socket_transacting_message_group = Nil;
    Qicp_message_trace_stream_qm = 
	    STATIC_SYMBOL("ICP-MESSAGE-TRACE-STREAM\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_message_trace_stream_qm,
	    Icp_message_trace_stream_qm);
    record_system_variable(Qicp_message_trace_stream_qm,Qint2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qunknown_message = STATIC_SYMBOL("UNKNOWN-MESSAGE",AB_package);
    Qhandle_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    Qhandle_icp_message_group_id = 
	    STATIC_SYMBOL("HANDLE-ICP-MESSAGE-GROUP-ID",AB_package);
    Qhandle_icp_i_am_alive = STATIC_SYMBOL("HANDLE-ICP-I-AM-ALIVE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_messages,
	    STATIC_FUNCTION(handle_icp_messages,NIL,FALSE,1,1));
    if (Debug_out_of_synch == UNBOUND)
	Debug_out_of_synch = T;
    string_constant_2 = STATIC_STRING("ICP ~A on ");
    Qab_warning = STATIC_SYMBOL("WARNING",AB_package);
    string_constant_3 = STATIC_STRING("warning");
    string_constant_4 = STATIC_STRING("error");
    Qno_error = STATIC_SYMBOL("NO-ERROR",AB_package);
    string_constant_5 = STATIC_STRING("interface ~NF (");
    string_constant_6 = STATIC_STRING("socket ");
    string_constant_7 = STATIC_STRING(")");
    string_constant_8 = STATIC_STRING(": ");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qresumable_error = STATIC_SYMBOL("RESUMABLE-ERROR",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qg2,Qgsi);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qabort_for_icp_catcher_qm = STATIC_SYMBOL("ABORT-FOR-ICP-CATCHER\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qabort_for_icp_catcher_qm,
	    Abort_for_icp_catcher_qm);
    record_system_variable(Qabort_for_icp_catcher_qm,Qint2,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    string_constant_9 = 
	    STATIC_STRING("ICP: Socket ~a (~a) received unknown message code ~a; ~\n             closing broken connection after message ~a");
    string_constant_10 = 
	    STATIC_STRING("ICP: Protocol out-of-synch (case ~d) ~\n             for ICP socket ~a with ~a; ~\n             closing broken connection after message ~a");
    Qprotocol_out_of_synch_1 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-1",
	    AB_package);
    Qprotocol_out_of_synch_3 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-3",
	    AB_package);
    Qprotocol_out_of_synch_4 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-4",
	    AB_package);
    Qprotocol_out_of_synch_5 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-5",
	    AB_package);
    Qprotocol_out_of_synch_6 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-6",
	    AB_package);
    Qprotocol_out_of_synch_7 = STATIC_SYMBOL("PROTOCOL-OUT-OF-SYNCH-7",
	    AB_package);
    if (Writing_icp_message_group == UNBOUND)
	Writing_icp_message_group = FIX((SI_Long)0L);
    Qdo_icp_flow_control_qm = STATIC_SYMBOL("DO-ICP-FLOW-CONTROL\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdo_icp_flow_control_qm,Do_icp_flow_control_qm);
    record_system_variable(Qdo_icp_flow_control_qm,Qint2,T,Qnil,Qnil,Qnil,
	    Qnil);
    Qhandle_unclogged_connection_if_necessary = 
	    STATIC_SYMBOL("HANDLE-UNCLOGGED-CONNECTION-IF-NECESSARY",
	    AB_package);
    string_constant_11 = STATIC_STRING("message series");
    string_constant_12 = 
	    STATIC_STRING("ICP message series too long -- please call Gensym customer support");
    Icp_message_too_long_warning = string_constant_12;
    string_constant_13 = 
	    STATIC_STRING("wrote \"end-of-message-group\" message series");
    string_constant_14 = STATIC_STRING("[finished writing message series]");
}
