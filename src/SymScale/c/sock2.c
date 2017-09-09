/* sock2.c
 * Input file:  socket2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sock2.h"


Object The_type_description_of_code_body_continuation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_code_body_continuations, Qchain_of_available_code_body_continuations);

DEFINE_VARIABLE_WITH_SYMBOL(Code_body_continuation_count, Qcode_body_continuation_count);

Object Chain_of_available_code_body_continuations_vector = UNBOUND;

/* CODE-BODY-CONTINUATION-STRUCTURE-MEMORY-USAGE */
Object code_body_continuation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(241,0);
    temp = Code_body_continuation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CODE-BODY-CONTINUATION-COUNT */
Object outstanding_code_body_continuation_count()
{
    Object def_structure_code_body_continuation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(241,1);
    gensymed_symbol = IFIX(Code_body_continuation_count);
    def_structure_code_body_continuation_variable = 
	    Chain_of_available_code_body_continuations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_code_body_continuation_variable))
	goto end_loop;
    def_structure_code_body_continuation_variable = 
	    ISVREF(def_structure_code_body_continuation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CODE-BODY-CONTINUATION-1 */
Object reclaim_code_body_continuation_1(code_body_continuation)
    Object code_body_continuation;
{
    Object temp, svref_arg_2;

    x_note_fn_call(241,2);
    inline_note_reclaim_cons(code_body_continuation,Nil);
    temp = ISVREF(Chain_of_available_code_body_continuations_vector,
	    IFIX(Current_thread_index));
    SVREF(code_body_continuation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_code_body_continuations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = code_body_continuation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CODE-BODY-CONTINUATION */
Object reclaim_structure_for_code_body_continuation(code_body_continuation)
    Object code_body_continuation;
{
    x_note_fn_call(241,3);
    return reclaim_code_body_continuation_1(code_body_continuation);
}

static Object Qg2_defstruct_structure_name_code_body_continuation_g2_struct;  /* g2-defstruct-structure-name::code-body-continuation-g2-struct */

/* MAKE-PERMANENT-CODE-BODY-CONTINUATION-STRUCTURE-INTERNAL */
Object make_permanent_code_body_continuation_structure_internal()
{
    Object def_structure_code_body_continuation_variable;
    Object defstruct_g2_code_body_continuation_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(241,4);
    def_structure_code_body_continuation_variable = Nil;
    atomic_incff_symval(Qcode_body_continuation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_code_body_continuation_variable = Nil;
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
	defstruct_g2_code_body_continuation_variable = the_array;
	SVREF(defstruct_g2_code_body_continuation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_code_body_continuation_g2_struct;
	def_structure_code_body_continuation_variable = 
		defstruct_g2_code_body_continuation_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_code_body_continuation_variable);
}

/* MAKE-CODE-BODY-CONTINUATION-1-1 */
Object make_code_body_continuation_1_1(code_body_continuation_invocation,
	    code_body_continuation_name,code_body_continuation_variable,
	    code_body_continuation_completion_form)
    Object code_body_continuation_invocation, code_body_continuation_name;
    Object code_body_continuation_variable;
    Object code_body_continuation_completion_form;
{
    Object def_structure_code_body_continuation_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(241,5);
    def_structure_code_body_continuation_variable = 
	    ISVREF(Chain_of_available_code_body_continuations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_code_body_continuation_variable) {
	svref_arg_1 = Chain_of_available_code_body_continuations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_code_body_continuation_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_code_body_continuation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_code_body_continuation_g2_struct;
    }
    else
	def_structure_code_body_continuation_variable = 
		make_permanent_code_body_continuation_structure_internal();
    inline_note_allocate_cons(def_structure_code_body_continuation_variable,
	    Nil);
    SVREF(def_structure_code_body_continuation_variable,FIX((SI_Long)1L)) 
	    = code_body_continuation_invocation;
    SVREF(def_structure_code_body_continuation_variable,FIX((SI_Long)2L)) 
	    = code_body_continuation_name;
    SVREF(def_structure_code_body_continuation_variable,FIX((SI_Long)3L)) 
	    = code_body_continuation_variable;
    SVREF(def_structure_code_body_continuation_variable,FIX((SI_Long)4L)) 
	    = code_body_continuation_completion_form;
    return VALUES_1(def_structure_code_body_continuation_variable);
}

static Object Qcomplete_code_body_continuation;  /* complete-code-body-continuation */

/* MAKE-CODE-BODY-CONTINUATION */
Object make_code_body_continuation varargs_1(int, n)
{
    Object name, ret_var;
    Object completion_form, continuation;
    Declare_varargs_nonrelocating;

    x_note_fn_call(241,6);
    INIT_ARGS_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ret_var = REQUIRED_ARG_nonrelocating();
    completion_form = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    continuation = 
	    make_code_body_continuation_1_1(Current_computation_instance,
	    name,ret_var,completion_form);
    install_code_body_invocation_completion_form(Current_computation_instance,
	    gensym_list_2(Qcomplete_code_body_continuation,continuation));
    return VALUES_1(continuation);
}

/* COMPLETE-CODE-BODY-CONTINUATION */
Object complete_code_body_continuation(completion_form)
    Object completion_form;
{
    Object continuation, sub_completion_form, temp;

    x_note_fn_call(241,7);
    continuation = SECOND(completion_form);
    sub_completion_form = ISVREF(continuation,(SI_Long)4L);
    SVREF(continuation,FIX((SI_Long)1L)) = Nil;
    if (sub_completion_form) {
	temp = SYMBOL_FUNCTION(CAR(sub_completion_form));
	FUNCALL_1(temp,sub_completion_form);
    }
    reclaim_code_body_continuation_1(continuation);
    reclaim_gensym_list_1(completion_form);
    return VALUES_1(Nil);
}

static Object Qg2_socket_status;   /* g2-socket-status */

/* UPDATE-G2-SOCKET-STATUS */
Object update_g2_socket_status(g2_socket,status)
    Object g2_socket, status;
{
    Object current_computation_frame;
    Declare_special(1);
    Object result;

    x_note_fn_call(241,8);
    if ( !TRUEP(g2_socket))
	return VALUES_1(Nil);
    else {
	current_computation_frame = g2_socket;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		0);
	  result = change_slot_value(3,g2_socket,Qg2_socket_status,status);
	POP_SPECIAL();
	return result;
    }
}

static Object Qconnected;          /* connected */

static Object Qconnected_secure;   /* connected-secure */

/* MAYBE-FIX-SOCKET-STATUS */
Object maybe_fix_socket_status(blocking_socket,g2_socket)
    Object blocking_socket, g2_socket;
{
    x_note_fn_call(241,9);
    if (ISVREF(blocking_socket,(SI_Long)3L) && 
	    g2ext_secure_socket_p(IFIX(ISVREF(blocking_socket,
	    (SI_Long)3L))) == (SI_Long)1L && EQ(ISVREF(g2_socket,
	    (SI_Long)21L),Qconnected))
	return update_g2_socket_status(g2_socket,Qconnected_secure);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_blocking_socket = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_blocking_sockets, Qchain_of_available_blocking_sockets);

DEFINE_VARIABLE_WITH_SYMBOL(Blocking_socket_count, Qblocking_socket_count);

Object Chain_of_available_blocking_sockets_vector = UNBOUND;

/* BLOCKING-SOCKET-STRUCTURE-MEMORY-USAGE */
Object blocking_socket_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(241,10);
    temp = Blocking_socket_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BLOCKING-SOCKET-COUNT */
Object outstanding_blocking_socket_count()
{
    Object def_structure_blocking_socket_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(241,11);
    gensymed_symbol = IFIX(Blocking_socket_count);
    def_structure_blocking_socket_variable = 
	    Chain_of_available_blocking_sockets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_blocking_socket_variable))
	goto end_loop;
    def_structure_blocking_socket_variable = 
	    ISVREF(def_structure_blocking_socket_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BLOCKING-SOCKET-1 */
Object reclaim_blocking_socket_1(blocking_socket)
    Object blocking_socket;
{
    Object structure_being_reclaimed, thing, vector_1, gensymed_symbol, temp;
    Object svref_arg_2;
    Declare_special(2);

    x_note_fn_call(241,12);
    inline_note_reclaim_cons(blocking_socket,Nil);
    structure_being_reclaimed = blocking_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      thing = ISVREF(blocking_socket,(SI_Long)1L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(blocking_socket,FIX((SI_Long)1L)) = Nil;
      vector_1 = ISVREF(blocking_socket,(SI_Long)5L);
      if (vector_1)
	  reclaim_variable_fill_icp_buffer(vector_1);
      SVREF(blocking_socket,FIX((SI_Long)5L)) = Nil;
      reclaim_if_socket_buffer(ISVREF(blocking_socket,(SI_Long)8L));
      SVREF(blocking_socket,FIX((SI_Long)8L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(blocking_socket,(SI_Long)9L);
      if (CAS_SVREF(blocking_socket,(SI_Long)9L,gensymed_symbol,Nil)) {
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
      SVREF(blocking_socket,FIX((SI_Long)9L)) = Nil;
      cleanup_blocking_socket(ISVREF(blocking_socket,(SI_Long)11L));
      SVREF(blocking_socket,FIX((SI_Long)11L)) = Nil;
      reclaim_blocking_socket_partial_data(ISVREF(blocking_socket,
	      (SI_Long)12L));
      SVREF(blocking_socket,FIX((SI_Long)12L)) = Nil;
      reclaim_blocking_socket_queue(ISVREF(blocking_socket,(SI_Long)14L));
      SVREF(blocking_socket,FIX((SI_Long)14L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_blocking_sockets_vector,
	    IFIX(Current_thread_index));
    SVREF(blocking_socket,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_blocking_sockets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = blocking_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BLOCKING-SOCKET */
Object reclaim_structure_for_blocking_socket(blocking_socket)
    Object blocking_socket;
{
    x_note_fn_call(241,13);
    return reclaim_blocking_socket_1(blocking_socket);
}

static Object Qg2_defstruct_structure_name_blocking_socket_g2_struct;  /* g2-defstruct-structure-name::blocking-socket-g2-struct */

/* MAKE-PERMANENT-BLOCKING-SOCKET-STRUCTURE-INTERNAL */
Object make_permanent_blocking_socket_structure_internal()
{
    Object def_structure_blocking_socket_variable;
    Object defstruct_g2_blocking_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(241,14);
    def_structure_blocking_socket_variable = Nil;
    atomic_incff_symval(Qblocking_socket_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_blocking_socket_variable = Nil;
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
	defstruct_g2_blocking_socket_variable = the_array;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_blocking_socket_g2_struct;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_blocking_socket_variable,FIX((SI_Long)9L)) = Nil;
	def_structure_blocking_socket_variable = 
		defstruct_g2_blocking_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_blocking_socket_variable);
}

/* MAKE-BLOCKING-SOCKET-1 */
Object make_blocking_socket_1()
{
    Object def_structure_blocking_socket_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(241,15);
    def_structure_blocking_socket_variable = 
	    ISVREF(Chain_of_available_blocking_sockets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_blocking_socket_variable) {
	svref_arg_1 = Chain_of_available_blocking_sockets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_blocking_socket_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_blocking_socket_g2_struct;
    }
    else
	def_structure_blocking_socket_variable = 
		make_permanent_blocking_socket_structure_internal();
    inline_note_allocate_cons(def_structure_blocking_socket_variable,Nil);
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)4L)) = T;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_blocking_socket_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_blocking_socket_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)12L)) = Nil;
    ISVREF(def_structure_blocking_socket_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_blocking_socket_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_blocking_socket_variable);
}

/* MAKE-BLOCKING-SOCKET-WITH-CONTINUATION */
Object make_blocking_socket_with_continuation(name,variable)
    Object name, variable;
{
    Object socket_1;

    x_note_fn_call(241,16);
    socket_1 = make_blocking_socket_1();
    set_blocking_socket_continuation(socket_1,name,variable);
    return VALUES_1(socket_1);
}

static Object Qcomplete_blocking_socket_continuation;  /* complete-blocking-socket-continuation */

/* SET-BLOCKING-SOCKET-CONTINUATION */
Object set_blocking_socket_continuation(socket_1,name,variable)
    Object socket_1, name, variable;
{
    Object svref_new_value;

    x_note_fn_call(241,17);
    svref_new_value = make_code_body_continuation(3,name,variable,
	    gensym_list_2(Qcomplete_blocking_socket_continuation,socket_1));
    SVREF(socket_1,FIX((SI_Long)10L)) = svref_new_value;
    return VALUES_1(Nil);
}

/* COMPLETE-BLOCKING-SOCKET-CONTINUATION */
Object complete_blocking_socket_continuation(completion_form)
    Object completion_form;
{
    Object svref_arg_1;

    x_note_fn_call(241,18);
    svref_arg_1 = SECOND(completion_form);
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = Nil;
    reclaim_gensym_list_1(completion_form);
    return VALUES_1(Nil);
}

/* RECLAIM-BLOCKING-SOCKET-PARTIAL-DATA */
Object reclaim_blocking_socket_partial_data(data)
    Object data;
{
    Object struct_1, ab_loop_list_;

    x_note_fn_call(241,19);
    if (text_string_p(data))
	return reclaim_text_string(data);
    else if (CONSP(data)) {
	struct_1 = Nil;
	ab_loop_list_ = data;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	struct_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_evaluation_structure(struct_1);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

/* RECLAIM-OUTPUT-QUEUE-ELEMENT */
Object reclaim_output_queue_element(elem)
    Object elem;
{
    x_note_fn_call(241,20);
    if (text_string_p(CAR(elem)))
	reclaim_text_string(CAR(elem));
    else
	reclaim_evaluation_sequence(CAR(elem));
    return reclaim_gensym_cons_1(elem);
}

/* RECLAIM-BLOCKING-SOCKET-QUEUE */
Object reclaim_blocking_socket_queue(queue)
    Object queue;
{
    Object elem;

    x_note_fn_call(241,21);
    if (queue) {
	elem = Nil;
      next_loop:
	if (queue_empty_p(queue))
	    goto end_loop;
	elem = queue_pop(queue);
	complete_tcp_write_task(elem,Nil);
	goto next_loop;
      end_loop:;
	return reclaim_queue(queue);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinternal_socket_qm;  /* internal-socket? */

/* CLEANUP-BLOCKING-SOCKET */
Object cleanup_blocking_socket(g2_socket)
    Object g2_socket;
{
    x_note_fn_call(241,22);
    if (g2_socket)
	return set_non_savable_lookup_slot_value(g2_socket,
		Qinternal_socket_qm,Nil);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-INTERNAL-SOCKET?-VALUE */
Object reclaim_internal_socket_qm_value(blocking_socket,gensymed_symbol)
    Object blocking_socket, gensymed_symbol;
{
    x_note_fn_call(241,23);
    if (blocking_socket)
	SVREF(blocking_socket,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(Nil);
}

static Object Qg2_socket;          /* g2-socket */

static Object Qconnection_closed;  /* connection-closed */

static Object Qg2_socket_remote_host;  /* g2-socket-remote-host */

static Object Qg2_socket_port;     /* g2-socket-port */

/* CREATE-ASSOCIATED-G2-SOCKET */
Object create_associated_g2_socket(blocking_socket)
    Object blocking_socket;
{
    Object g2sock;

    x_note_fn_call(241,24);
    g2sock = make_transient_item(Qg2_socket);
    set_non_savable_lookup_slot_value(g2sock,Qinternal_socket_qm,
	    blocking_socket);
    update_g2_socket_status(g2sock,ISVREF(blocking_socket,(SI_Long)3L) ? 
	    (g2ext_secure_socket_p(IFIX(ISVREF(blocking_socket,
	    (SI_Long)3L))) == (SI_Long)1L ? Qconnected_secure : 
	    Qconnected) : Qconnection_closed);
    if (ISVREF(blocking_socket,(SI_Long)1L))
	change_slot_value(3,g2sock,Qg2_socket_remote_host,
		copy_text_string(ISVREF(blocking_socket,(SI_Long)1L)));
    if (ISVREF(blocking_socket,(SI_Long)2L))
	change_slot_value(3,g2sock,Qg2_socket_port,ISVREF(blocking_socket,
		(SI_Long)2L));
    SVREF(blocking_socket,FIX((SI_Long)11L)) = g2sock;
    return VALUES_1(g2sock);
}

static Object string_constant;     /* "Error message unavailable for closed socket" */

static Object string_constant_1;   /* "Network ~a failure: ~s (error code ~d)" */

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* NETWORK-STACK-ERROR */
Object network_stack_error(type,error_code,socket_1)
    Object type, error_code, socket_1;
{
    Object error_string, gensymed_symbol, gensymed_symbol_1, top_of_stack;
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long gensymed_symbol_2, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_special(7);

    x_note_fn_call(241,25);
    error_string = ISVREF(socket_1,(SI_Long)3L) ? 
	    network_get_last_error_string(ISVREF(socket_1,(SI_Long)3L)) : 
	    copy_text_string(string_constant);
    if (Inside_handle_event) {
	notify_user_at_console(4,string_constant_1,type,error_string,
		error_code);
	reclaim_text_string(error_string);
	close_socket(1,socket_1);
	gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)24L);
	gensymed_symbol_1 = socket_1;
	gensymed_symbol_2 = (SI_Long)0L;
	return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		FIX(gensymed_symbol_2)));
    }
    else {
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  5);
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
		      tformat(4,string_constant_1,type,error_string,
			      error_code);
		      reclaim_text_string(error_string);
		      close_socket(1,socket_1);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object Qg2_tcp_connect;     /* g2-tcp-connect */

static Object Qsecure;             /* secure */

/* G2-TCP-CONNECT */
Object g2_tcp_connect(host_as_evaluation_value,port_as_evaluation_value,
	    ret_var_as_evaluation_value,options_as_evaluation_value)
    Object host_as_evaluation_value, port_as_evaluation_value;
    Object ret_var_as_evaluation_value, options_as_evaluation_value;
{
    Object host, port, ret_var, options, blocking_socket, temp;
    char secure_p;

    x_note_fn_call(241,26);
    host = host_as_evaluation_value;
    port = port_as_evaluation_value;
    ret_var = ret_var_as_evaluation_value;
    options = IDENTITY(options_as_evaluation_value);
    blocking_socket = 
	    make_blocking_socket_with_continuation(Qg2_tcp_connect,ret_var);
    temp = estructure_slot(options,Qsecure,Evaluation_false_value);
    secure_p = EQUAL(temp,Evaluation_true_value);
    connect_socket(blocking_socket,host,port,secure_p ? T : Nil);
    reclaim_evaluation_structure(options);
    reclaim_text_string(host_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    return VALUES_0();
}

static Object string_constant_2;   /* "connection" */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* HANDLE-NETWORK-CONNECT-FOR-BLOCKING-SOCKET */
Object handle_network_connect_for_blocking_socket(blocking_socket,error_code)
    Object blocking_socket, error_code;
{
    Object g2sock, gensymed_symbol, invocation, x2;
    char temp;

    x_note_fn_call(241,27);
    if (ISVREF(blocking_socket,(SI_Long)10L) && 
	    EQ(ISVREF(ISVREF(blocking_socket,(SI_Long)10L),(SI_Long)2L),
	    Qg2_tcp_connect)) {
	g2sock = create_associated_g2_socket(blocking_socket);
	if ( !FIXNUM_EQ(error_code,Network_status_success))
	    network_stack_error(string_constant_2,error_code,blocking_socket);
	gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
	invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
	if (invocation) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
	    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
	    if (SIMPLE_VECTOR_P(g2sock) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2sock)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(g2sock,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(g2sock,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		set_local_name_value_validating_environment(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),g2sock);
	    else
		set_code_body_invocation_local_name_value(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),g2sock);
	    return wake_up_code_body_invocation(invocation);
	}
	else
	    return VALUES_1(Nil);
    }
    else if ( !FIXNUM_EQ(error_code,Network_status_success))
	return network_stack_error(string_constant_2,error_code,
		blocking_socket);
    else
	return VALUES_1(Nil);
}

/* G2-TCP-CLOSE */
Object g2_tcp_close(g2_socket_as_evaluation_value)
    Object g2_socket_as_evaluation_value;
{
    Object g2_socket, socket_1, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(241,28);
    g2_socket = IDENTITY(g2_socket_as_evaluation_value);
    socket_1 = get_lookup_slot_value_given_default(g2_socket,
	    Qinternal_socket_qm,Nil);
    if (socket_1) {
	if (ISVREF(socket_1,(SI_Long)4L)) {
	    close_socket(2,socket_1,T);
	    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)24L);
	    gensymed_symbol_1 = socket_1;
	    gensymed_symbol_2 = (SI_Long)0L;
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    FIX(gensymed_symbol_2));
	}
	else if ( !TRUEP(ISVREF(socket_1,(SI_Long)9L)))
	    enqueue_tcp_cleanups(socket_1);
    }
    delete_frame(g2_socket);
    IDENTITY(g2_socket_as_evaluation_value);
    return VALUES_0();
}

static Object Qconnection_closed_with_unread_data;  /* connection-closed-with-unread-data */

/* HANDLE-NETWORK-CLOSE-FOR-BLOCKING-SOCKET */
Object handle_network_close_for_blocking_socket(blocking_socket,error_code)
    Object blocking_socket, error_code;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(241,29);
    temp = ISVREF(blocking_socket,(SI_Long)11L);
    update_g2_socket_status(temp,data_available_p(blocking_socket) ? 
	    Qconnection_closed_with_unread_data : Qconnection_closed);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_blocking_socket,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)24L);
    gensymed_symbol_1 = blocking_socket;
    gensymed_symbol_2 = error_code;
    return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
	    gensymed_symbol_2));
}

static Object Qcomplete_tcp_write_continuation;  /* complete-tcp-write-continuation */

/* ADD-TASK-TO-OUTPUT-QUEUE */
Object add_task_to_output_queue(task,blocking_socket)
    Object task, blocking_socket;
{
    Object temp, svref_new_value;

    x_note_fn_call(241,30);
    if ( !TRUEP(ISVREF(blocking_socket,(SI_Long)14L))) {
	temp = make_queue();
	SVREF(blocking_socket,FIX((SI_Long)14L)) = temp;
    }
    queue_insert(ISVREF(blocking_socket,(SI_Long)14L),task);
    temp = CDR(task);
    svref_new_value = gensym_list_2(Qcomplete_tcp_write_continuation,task);
    return VALUES_1(SVREF(temp,FIX((SI_Long)4L)) = svref_new_value);
}

/* COMPLETE-TCP-WRITE-CONTINUATION */
Object complete_tcp_write_continuation(completion_form)
    Object completion_form;
{
    Object task;

    x_note_fn_call(241,31);
    task = SECOND(completion_form);
    if (CDR(task))
	M_CDR(task) = Nil;
    else
	reclaim_output_queue_element(task);
    reclaim_gensym_list_1(completion_form);
    return VALUES_1(Nil);
}

/* COMPLETE-TCP-WRITE-TASK */
Object complete_tcp_write_task(task,success_p)
    Object task, success_p;
{
    Object value, gensymed_symbol, invocation, x2;
    char temp;

    x_note_fn_call(241,32);
    if (CDR(task)) {
	value = success_p ? Evaluation_true_value : Evaluation_false_value;
	gensymed_symbol = CDR(task);
	invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
	if (invocation) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
	    M_CDR(task) = Nil;
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		set_local_name_value_validating_environment(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),value);
	    else
		set_code_body_invocation_local_name_value(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),value);
	    wake_up_code_body_invocation(invocation);
	}
	M_CDR(task) = Nil;
    }
    else
	reclaim_output_queue_element(task);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "Invalid socket ~NF" */

static Object Qg2_tcp_write;       /* g2-tcp-write */

/* G2-TCP-WRITE */
Object g2_tcp_write(handle_as_evaluation_value,text_as_evaluation_value,
	    ret_var_as_evaluation_value)
    Object handle_as_evaluation_value, text_as_evaluation_value;
    Object ret_var_as_evaluation_value;
{
    Object handle, text, ret_var, socket_1, top_of_stack, message_1, temp;

    x_note_fn_call(241,33);
    handle = IDENTITY(handle_as_evaluation_value);
    text = text_as_evaluation_value;
    ret_var = ret_var_as_evaluation_value;
    socket_1 = get_lookup_slot_value_given_default(handle,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(socket_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		handle);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    temp = copy_text_string(text);
    add_task_to_output_queue(gensym_cons_1(temp,
	    make_code_body_continuation(2,Qg2_tcp_write,ret_var)),socket_1);
    if ( !TRUEP(ISVREF(socket_1,(SI_Long)8L)))
	execute_tcp_write(socket_1);
    IDENTITY(handle_as_evaluation_value);
    reclaim_text_string(text_as_evaluation_value);
    return VALUES_0();
}

/* G2-TCP-WRITE-BYTES */
Object g2_tcp_write_bytes(handle_as_evaluation_value,
	    seq_as_evaluation_value,ret_var_as_evaluation_value)
    Object handle_as_evaluation_value, seq_as_evaluation_value;
    Object ret_var_as_evaluation_value;
{
    Object handle, seq, ret_var, socket_1, top_of_stack, message_1;

    x_note_fn_call(241,34);
    handle = IDENTITY(handle_as_evaluation_value);
    seq = IDENTITY(seq_as_evaluation_value);
    ret_var = ret_var_as_evaluation_value;
    socket_1 = get_lookup_slot_value_given_default(handle,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(socket_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		handle);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    add_task_to_output_queue(gensym_cons_1(seq,
	    make_code_body_continuation(2,Qg2_tcp_write,ret_var)),socket_1);
    if ( !TRUEP(ISVREF(socket_1,(SI_Long)8L)))
	execute_tcp_write(socket_1);
    IDENTITY(handle_as_evaluation_value);
    IDENTITY(seq_as_evaluation_value);
    return VALUES_0();
}

static Object Qblocked;            /* blocked */

static Object Qconnection_write_error;  /* connection-write-error */

/* EXECUTE-TCP-WRITE */
Object execute_tcp_write(blocking_socket)
    Object blocking_socket;
{
    Object task, data, status, temp;

    x_note_fn_call(241,35);
    task = queue_peek(ISVREF(blocking_socket,(SI_Long)14L));
    data = CAR(task);
    status = text_string_p(data) ? write_to_socket(blocking_socket,data) : 
	    write_bytes_to_socket(blocking_socket,data);
    if (EQ(status,T)) {
	complete_tcp_write_task(task,T);
	return queue_pop(ISVREF(blocking_socket,(SI_Long)14L));
    }
    else {
	temp = EQ(status,Qblocked) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else {
	    update_g2_socket_status(ISVREF(blocking_socket,(SI_Long)11L),
		    Qconnection_write_error);
	    complete_tcp_write_task(task,Nil);
	    return queue_pop(ISVREF(blocking_socket,(SI_Long)14L));
	}
    }
}

/* HANDLE-WRITE-EVENT-FOR-BLOCKING-SOCKET */
Object handle_write_event_for_blocking_socket(blocking_socket,error_code)
    Object blocking_socket, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, task;

    x_note_fn_call(241,36);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_blocking_socket,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)21L);
    gensymed_symbol_1 = blocking_socket;
    gensymed_symbol_2 = error_code;
    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2);
    if (ISVREF(blocking_socket,(SI_Long)14L)) {
	if ( !TRUEP(ISVREF(blocking_socket,(SI_Long)8L))) {
	    task = queue_pop(ISVREF(blocking_socket,(SI_Long)14L));
	    if (task)
		complete_tcp_write_task(task,T);
	    if ( !TRUEP(queue_empty_p(ISVREF(blocking_socket,(SI_Long)14L))))
		return execute_tcp_write(blocking_socket);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* APPEND-CONTINUATION-DATA */
Object append_continuation_data(blocking_socket,new_data)
    Object blocking_socket, new_data;
{
    Object current, svref_new_value;

    x_note_fn_call(241,37);
    current = ISVREF(blocking_socket,(SI_Long)12L);
    if (current) {
	svref_new_value = concatenate_text_strings(current,new_data);
	SVREF(blocking_socket,FIX((SI_Long)12L)) = svref_new_value;
	reclaim_text_string(new_data);
	return reclaim_text_string(current);
    }
    else
	return VALUES_1(SVREF(blocking_socket,FIX((SI_Long)12L)) = new_data);
}

static Object Qg2_tcp_read_block;  /* g2-tcp-read-block */

static Object Qg2_tcp_read_byte;   /* g2-tcp-read-byte */

static Object Qg2_tcp_read_line;   /* g2-tcp-read-line */

static Object Qg2_tcp_read_n_bytes;  /* g2-tcp-read-n-bytes */

/* RETURN-NETWORK-DATA-TO-SOCKET-CONTINUATION-IF-ANY */
Object return_network_data_to_socket_continuation_if_any(blocking_socket)
    Object blocking_socket;
{
    Object temp, data, value, gensymed_symbol, invocation, x2, byte_qm;
    Object partial_data, more_to_do, text, n_1, remaining;
    char temp_1;
    Object result;

    x_note_fn_call(241,38);
    if (ISVREF(blocking_socket,(SI_Long)10L)) {
	temp = ISVREF(ISVREF(blocking_socket,(SI_Long)10L),(SI_Long)2L);
	if (EQ(temp,Qg2_tcp_read_block)) {
	    data = read_from_socket(blocking_socket);
	    if (ISVREF(blocking_socket,(SI_Long)4L) && 
		    zerop(text_string_length(data)))
		reclaim_text_string(data);
	    else {
		value = data;
		gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
		invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (invocation) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
		    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			set_local_name_value_validating_environment(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    else
			set_code_body_invocation_local_name_value(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    wake_up_code_body_invocation(invocation);
		}
	    }
	}
	else if (EQ(temp,Qg2_tcp_read_byte)) {
	    byte_qm = read_byte_from_socket(blocking_socket);
	    if (byte_qm ||  !TRUEP(ISVREF(blocking_socket,(SI_Long)4L))) {
		value = byte_qm;
		if (value);
		else
		    value = FIX((SI_Long)-1L);
		gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
		invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (invocation) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
		    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			set_local_name_value_validating_environment(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    else
			set_code_body_invocation_local_name_value(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    wake_up_code_body_invocation(invocation);
		}
	    }
	}
	else if (EQ(temp,Qg2_tcp_read_line)) {
	    result = read_from_socket_until_char(blocking_socket,
		    CHAR_CODE(CHR('\n')));
	    MVS_2(result,partial_data,more_to_do);
	    append_continuation_data(blocking_socket,partial_data);
	    if ( !(more_to_do && ISVREF(blocking_socket,(SI_Long)4L))) {
		text = ISVREF(blocking_socket,(SI_Long)12L);
		SVREF(blocking_socket,FIX((SI_Long)12L)) = Nil;
		value = text;
		gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
		invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (invocation) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
		    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			set_local_name_value_validating_environment(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    else
			set_code_body_invocation_local_name_value(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    wake_up_code_body_invocation(invocation);
		}
	    }
	}
	else if (EQ(temp,Qg2_tcp_read_n_bytes)) {
	    n_1 = ISVREF(blocking_socket,(SI_Long)13L);
	    result = read_n_chars_from_socket(blocking_socket,n_1);
	    MVS_2(result,partial_data,remaining);
	    append_continuation_data(blocking_socket,partial_data);
	    if ( !TRUEP(ISVREF(blocking_socket,(SI_Long)4L)) || 
		    (SI_Long)0L == IFIX(remaining)) {
		text = ISVREF(blocking_socket,(SI_Long)12L);
		SVREF(blocking_socket,FIX((SI_Long)12L)) = Nil;
		value = text;
		gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
		invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (invocation) {
		    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
		    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
		    if (SIMPLE_VECTOR_P(value) && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			    Qavailable_frame_vector)) {
			x2 = ISVREF(value,(SI_Long)1L);
			temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_class_description_g2_struct) 
				? TRUEP(x2) : TRUEP(Qnil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			set_local_name_value_validating_environment(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    else
			set_code_body_invocation_local_name_value(invocation,
				ISVREF(gensymed_symbol,(SI_Long)3L),value);
		    wake_up_code_body_invocation(invocation);
		}
	    }
	    else
		SVREF(blocking_socket,FIX((SI_Long)13L)) = remaining;
	}
	if ( !TRUEP(ISVREF(blocking_socket,(SI_Long)4L))) {
	    temp = ISVREF(blocking_socket,(SI_Long)11L);
	    update_g2_socket_status(temp,data_available_p(blocking_socket) 
		    ? Qconnection_closed_with_unread_data : 
		    Qconnection_closed);
	}
    }
    return VALUES_1(Nil);
}

static Object Qline;               /* line */

static Object string_constant_4;   /* "Mode ~s is not a valid read mode.  Must be BLOCK, LINE, or BYTE" */

/* G2-TCP-READ */
Object g2_tcp_read(handle_as_evaluation_value,
	    read_mode_as_evaluation_value,ret_var_as_evaluation_value)
    Object handle_as_evaluation_value, read_mode_as_evaluation_value;
    Object ret_var_as_evaluation_value;
{
    Object handle, read_mode, ret_var, socket_1, top_of_stack, message_1, temp;

    x_note_fn_call(241,39);
    handle = IDENTITY(handle_as_evaluation_value);
    read_mode = read_mode_as_evaluation_value;
    ret_var = ret_var_as_evaluation_value;
    socket_1 = get_lookup_slot_value_given_default(handle,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(socket_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		handle);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (EQ(read_mode,Qblock))
	temp = Qg2_tcp_read_block;
    else if (EQ(read_mode,Qline))
	temp = Qg2_tcp_read_line;
    else if (EQ(read_mode,Qbyte))
	temp = Qg2_tcp_read_byte;
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_4,
		read_mode);
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    set_blocking_socket_continuation(socket_1,temp,ret_var);
    return_network_data_to_socket_continuation_if_any(socket_1);
    IDENTITY(handle_as_evaluation_value);
    return VALUES_0();
}

static Object string_constant_5;   /* "Request to read ~d bytes which exceeds the ~
				    *                     maximum G2 text length, ~d"
				    */

/* G2-TCP-READ-BYTES-AS-TEXT */
Object g2_tcp_read_bytes_as_text(handle_as_evaluation_value,
	    n_as_evaluation_value,ret_var_as_evaluation_value)
    Object handle_as_evaluation_value, n_as_evaluation_value;
    Object ret_var_as_evaluation_value;
{
    Object handle, n_1, ret_var, top_of_stack, message_1, socket_1;

    x_note_fn_call(241,40);
    handle = IDENTITY(handle_as_evaluation_value);
    n_1 = n_as_evaluation_value;
    ret_var = ret_var_as_evaluation_value;
    if (FIXNUM_GE(n_1,Maximum_length_for_user_text_strings)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_5,
		n_1,Maximum_length_for_user_text_strings);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    socket_1 = get_lookup_slot_value_given_default(handle,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(socket_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		handle);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    set_blocking_socket_continuation(socket_1,Qg2_tcp_read_n_bytes,ret_var);
    SVREF(socket_1,FIX((SI_Long)13L)) = n_1;
    return_network_data_to_socket_continuation_if_any(socket_1);
    IDENTITY(handle_as_evaluation_value);
    return VALUES_0();
}

static Object string_constant_6;   /* "read" */

/* HANDLE-READ-EVENT-FOR-BLOCKING-SOCKET */
Object handle_read_event_for_blocking_socket(blocking_socket,error_code,
	    block_p)
    Object blocking_socket, error_code, block_p;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(241,41);
    if (FIXNUM_EQ(error_code,Network_status_success)) {
	gensymed_symbol = 
		ISVREF(ISVREF(ISVREF(The_type_description_of_blocking_socket,
		(SI_Long)9L),(SI_Long)0L),(SI_Long)20L);
	gensymed_symbol_1 = blocking_socket;
	gensymed_symbol_2 = error_code;
	gensymed_symbol_3 = block_p;
	inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
	maybe_fix_socket_status(blocking_socket,ISVREF(blocking_socket,
		(SI_Long)11L));
	return return_network_data_to_socket_continuation_if_any(blocking_socket);
    }
    else
	return network_stack_error(string_constant_6,error_code,
		blocking_socket);
}

static Object string_constant_7;   /* "Could not make exact TCP connection" */

static Object string_constant_8;   /* "DECnet not supported by this product on this platform" */

/* START-LISTENING */
Object start_listening(port,exact_p,secure_p)
    Object port, exact_p, secure_p;
{
    Object top_of_stack, message_1, listener_socket, netpath, delimiter_count;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, thing, temp, schar_arg_2, schar_new_value, port_string;
    SI_Long listen_status, listener_handle, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, i, ab_loop_bind_, j;
    Declare_special(5);

    x_note_fn_call(241,42);
    listen_status = g2ext_network_listen(IFIX(Use_tcpip_protocol_only),
	    IFIX(port),exact_p ? (SI_Long)1L : (SI_Long)0L,
	    IFIX(G2_product_tag),secure_p ? (SI_Long)1L : (SI_Long)0L);
    if ( !((SI_Long)-128L <= listen_status && listen_status <= 
		(SI_Long)127L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_7);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	switch ((char)listen_status) {
	  case 1:
	    listener_handle = ne_get_listener_handle((SI_Long)0L);
	    listener_socket = make_blocking_socket_1();
	    ISVREF(listener_socket,(SI_Long)3L) = FIX(listener_handle);
	    register_socket_to_handle(listener_socket,FIX(listener_handle));
	    netpath = get_accept_pathname(FIX(listener_handle));
	    delimiter_count = FIX((SI_Long)0L);
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
		      i = (SI_Long)0L;
		      ab_loop_bind_ = IFIX(lengthw(netpath));
		      c = Nil;
		    next_loop:
		      if (i >= ab_loop_bind_)
			  goto end_loop;
		      c = FIX(UBYTE_16_ISAREF_1(netpath,i));
		      if (IFIX(delimiter_count) == (SI_Long)2L)
			  goto end_loop;
		      if (IFIX(c) == (SI_Long)58L)
			  delimiter_count = FIXNUM_ADD1(delimiter_count);
		      i = i + (SI_Long)1L;
		      goto next_loop;
		    end_loop:
		      j = i;
		      ab_loop_bind_ = IFIX(lengthw(netpath));
		      c = Nil;
		    next_loop_1:
		      if (j >= ab_loop_bind_)
			  goto end_loop_1;
		      c = FIX(UBYTE_16_ISAREF_1(netpath,j));
		      if (IFIX(c) == (SI_Long)58L)
			  goto end_loop_1;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = c;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = c;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      j = j + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      port_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = read_number_from_text_string(1,port_string);
	    SVREF(listener_socket,FIX((SI_Long)2L)) = temp;
	    reclaim_text_string(netpath);
	    reclaim_text_string(port_string);
	    return VALUES_1(listener_socket);
	  case -2:
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_8);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	  default:
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_7);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
}

static Object Qexact;              /* exact */

static Object Qcertificate;        /* certificate */

static Object Qlistening_secure;   /* listening-secure */

static Object Qlistening;          /* listening */

/* G2-TCP-LISTEN */
Object g2_tcp_listen(port_as_evaluation_value,options_as_evaluation_value)
    Object port_as_evaluation_value, options_as_evaluation_value;
{
    Object port, options, value_1, temp, certificate, listener_socket;
    char exact_p, secure_p;

    x_note_fn_call(241,43);
    port = port_as_evaluation_value;
    options = IDENTITY(options_as_evaluation_value);
    value_1 = Nil;
    temp = estructure_slot(options,Qexact,Evaluation_false_value);
    exact_p = EQUAL(temp,Evaluation_true_value);
    temp = estructure_slot(options,Qsecure,Evaluation_false_value);
    secure_p = EQUAL(temp,Evaluation_true_value);
    certificate = estructure_slot(options,Qcertificate,Nil);
    listener_socket = Nil;
    if (secure_p &&  !TRUEP(Secure_icp_initialized_p)) {
	if (certificate)
	    update_server_certificate(certificate);
	set_up_secure_icp(0);
    }
    listener_socket = start_listening(port,exact_p ? T : Nil,secure_p ? T :
	     Nil);
    reclaim_evaluation_structure(options);
    temp = create_associated_g2_socket(listener_socket);
    update_g2_socket_status(ISVREF(listener_socket,(SI_Long)11L),secure_p ?
	     Qlistening_secure : Qlistening);
    value_1 = temp;
    IDENTITY(options_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

static Object string_constant_9;   /* "accept new connection" */

/* TRY-NETWORK-ACCEPT */
Object try_network_accept(blocking_socket,error_code)
    Object blocking_socket, error_code;
{
    Object new_socket, network_return, g2sock, gensymed_symbol, invocation, x2;
    Object gensymed_symbol_1;
    char temp;

    x_note_fn_call(241,44);
    new_socket = make_blocking_socket_1();
    network_return = handle_network_accept_internals(blocking_socket,
	    new_socket,error_code);
    if (EQ(network_return,T)) {
	g2sock = create_associated_g2_socket(new_socket);
	gensymed_symbol = ISVREF(blocking_socket,(SI_Long)10L);
	invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
	if (invocation) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
	    SVREF(blocking_socket,FIX((SI_Long)10L)) = Nil;
	    if (SIMPLE_VECTOR_P(g2sock) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2sock)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(g2sock,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(g2sock,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		set_local_name_value_validating_environment(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),g2sock);
	    else
		set_code_body_invocation_local_name_value(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),g2sock);
	    return wake_up_code_body_invocation(invocation);
	}
	else
	    return VALUES_1(Nil);
    }
    else if ( !TRUEP(network_return)) {
	gensymed_symbol = ISVREF(new_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = new_socket;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	return network_stack_error(string_constant_9,
		ISVREF(blocking_socket,(SI_Long)3L) ? 
		FIX(ne_last_error_code(IFIX(ISVREF(blocking_socket,
		(SI_Long)3L)))) : FIX((SI_Long)-1L),blocking_socket);
    }
    else {
	gensymed_symbol = ISVREF(new_socket,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)3L);
	gensymed_symbol_1 = new_socket;
	return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
}

static Object Qg2_tcp_accept;      /* g2-tcp-accept */

/* HANDLE-NETWORK-ACCEPT-FOR-BLOCKING-SOCKET */
Object handle_network_accept_for_blocking_socket(blocking_socket,error_code)
    Object blocking_socket, error_code;
{
    x_note_fn_call(241,45);
    if (FIXNUM_EQ(error_code,Network_status_success)) {
	if (ISVREF(blocking_socket,(SI_Long)10L) && 
		EQ(ISVREF(ISVREF(blocking_socket,(SI_Long)10L),
		(SI_Long)2L),Qg2_tcp_accept))
	    return try_network_accept(blocking_socket,error_code);
	else
	    return VALUES_1(Nil);
    }
    else
	return network_stack_error(string_constant_9,error_code,
		blocking_socket);
}

/* G2-TCP-ACCEPT */
Object g2_tcp_accept(handle_as_evaluation_value,ret_var_as_evaluation_value)
    Object handle_as_evaluation_value, ret_var_as_evaluation_value;
{
    Object handle, ret_var, socket_1, top_of_stack, message_1;

    x_note_fn_call(241,46);
    handle = IDENTITY(handle_as_evaluation_value);
    ret_var = ret_var_as_evaluation_value;
    socket_1 = get_lookup_slot_value_given_default(handle,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(socket_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		handle);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    set_blocking_socket_continuation(socket_1,Qg2_tcp_accept,ret_var);
    try_network_accept(socket_1,Network_status_success);
    IDENTITY(handle_as_evaluation_value);
    return VALUES_0();
}

Object The_type_description_of_icmp_socket = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_icmp_sockets, Qchain_of_available_icmp_sockets);

DEFINE_VARIABLE_WITH_SYMBOL(Icmp_socket_count, Qicmp_socket_count);

Object Chain_of_available_icmp_sockets_vector = UNBOUND;

/* ICMP-SOCKET-STRUCTURE-MEMORY-USAGE */
Object icmp_socket_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(241,47);
    temp = Icmp_socket_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ICMP-SOCKET-COUNT */
Object outstanding_icmp_socket_count()
{
    Object def_structure_icmp_socket_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(241,48);
    gensymed_symbol = IFIX(Icmp_socket_count);
    def_structure_icmp_socket_variable = Chain_of_available_icmp_sockets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_icmp_socket_variable))
	goto end_loop;
    def_structure_icmp_socket_variable = 
	    ISVREF(def_structure_icmp_socket_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ICMP-SOCKET-1 */
Object reclaim_icmp_socket_1(icmp_socket)
    Object icmp_socket;
{
    Object structure_being_reclaimed, thing, vector_1, gensymed_symbol, temp;
    Object svref_arg_2;
    Declare_special(2);

    x_note_fn_call(241,49);
    inline_note_reclaim_cons(icmp_socket,Nil);
    structure_being_reclaimed = icmp_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      thing = ISVREF(icmp_socket,(SI_Long)1L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(icmp_socket,FIX((SI_Long)1L)) = Nil;
      vector_1 = ISVREF(icmp_socket,(SI_Long)5L);
      if (vector_1)
	  reclaim_variable_fill_icp_buffer(vector_1);
      SVREF(icmp_socket,FIX((SI_Long)5L)) = Nil;
      reclaim_if_socket_buffer(ISVREF(icmp_socket,(SI_Long)8L));
      SVREF(icmp_socket,FIX((SI_Long)8L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(icmp_socket,(SI_Long)9L);
      if (CAS_SVREF(icmp_socket,(SI_Long)9L,gensymed_symbol,Nil)) {
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
      SVREF(icmp_socket,FIX((SI_Long)9L)) = Nil;
      cleanup_blocking_socket(ISVREF(icmp_socket,(SI_Long)11L));
      SVREF(icmp_socket,FIX((SI_Long)11L)) = Nil;
      reclaim_blocking_socket_partial_data(ISVREF(icmp_socket,(SI_Long)12L));
      SVREF(icmp_socket,FIX((SI_Long)12L)) = Nil;
      reclaim_blocking_socket_queue(ISVREF(icmp_socket,(SI_Long)14L));
      SVREF(icmp_socket,FIX((SI_Long)14L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_icmp_sockets_vector,
	    IFIX(Current_thread_index));
    SVREF(icmp_socket,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_icmp_sockets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = icmp_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ICMP-SOCKET */
Object reclaim_structure_for_icmp_socket(icmp_socket)
    Object icmp_socket;
{
    x_note_fn_call(241,50);
    return reclaim_icmp_socket_1(icmp_socket);
}

static Object Qg2_defstruct_structure_name_icmp_socket_g2_struct;  /* g2-defstruct-structure-name::icmp-socket-g2-struct */

/* MAKE-PERMANENT-ICMP-SOCKET-STRUCTURE-INTERNAL */
Object make_permanent_icmp_socket_structure_internal()
{
    Object def_structure_icmp_socket_variable;
    Object defstruct_g2_icmp_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(241,51);
    def_structure_icmp_socket_variable = Nil;
    atomic_incff_symval(Qicmp_socket_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_icmp_socket_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_icmp_socket_variable = the_array;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icmp_socket_g2_struct;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_icmp_socket_variable,FIX((SI_Long)14L)) = Nil;
	def_structure_icmp_socket_variable = defstruct_g2_icmp_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_icmp_socket_variable);
}

/* MAKE-ICMP-SOCKET-1 */
Object make_icmp_socket_1()
{
    Object def_structure_icmp_socket_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(241,52);
    def_structure_icmp_socket_variable = 
	    ISVREF(Chain_of_available_icmp_sockets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_icmp_socket_variable) {
	svref_arg_1 = Chain_of_available_icmp_sockets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_icmp_socket_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_icmp_socket_g2_struct;
    }
    else
	def_structure_icmp_socket_variable = 
		make_permanent_icmp_socket_structure_internal();
    inline_note_allocate_cons(def_structure_icmp_socket_variable,Nil);
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)4L)) = T;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_icmp_socket_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_icmp_socket_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)12L)) = Nil;
    ISVREF(def_structure_icmp_socket_variable,(SI_Long)13L) = FIX((SI_Long)0L);
    SVREF(def_structure_icmp_socket_variable,FIX((SI_Long)14L)) = Nil;
    return VALUES_1(def_structure_icmp_socket_variable);
}

/* C-ICMP-OPEN */
Object c_icmp_open(host,dotted_address,buffer_size)
    Object host, dotted_address, buffer_size;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(241,53);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(host);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(dotted_address);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = host;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = dotted_address;
    temp = FIX(g2ext_icmp_open(temp_1,ISTRING(temp),IFIX(buffer_size)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ping_seq_id_array, Qping_seq_id_array);

static Object Qttl;                /* ttl */

static Object Qseq;                /* seq */

static Object Qid;                 /* id */

static Object string_constant_10;  /* "Failed to open ping socket: ~s" */

static Object Qicmp_error_status;  /* icmp-error-status */

static Object string_constant_11;  /* "Failed to send ping request: " */

static Object Qicmp_waiting_reply;  /* icmp-waiting-reply */

/* G2-INITIATE-PING */
Object g2_initiate_ping(host_as_evaluation_value,seq_as_evaluation_value,
	    options_as_evaluation_value)
    Object host_as_evaluation_value, seq_as_evaluation_value;
    Object options_as_evaluation_value;
{
    Object host, seq, options, value_1, dotted_addr, handle, ttl, seqnum, id;
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_string, message_1, socket_1, buffer, g2sock, buflen, temp, c;
    Object temp_1, thing, schar_arg_2, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_repeat_;
    Declare_special(7);

    x_note_fn_call(241,54);
    host = host_as_evaluation_value;
    seq = IDENTITY(seq_as_evaluation_value);
    options = IDENTITY(options_as_evaluation_value);
    value_1 = Nil;
    dotted_addr = 
	    obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    handle = c_icmp_open(host,dotted_addr,FIX((SI_Long)4096L));
    ttl = estructure_slot(options,Qttl,FIX((SI_Long)0L));
    seqnum = estructure_slot(options,Qseq,FIX((SI_Long)0L));
    id = estructure_slot(options,Qid,FIX((SI_Long)0L));
    reclaim_evaluation_structure(options);
    if (IFIX(handle) < (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  5);
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
		      error_string = 
			      copy_null_terminated_string_as_text_string(dotted_addr);
		      tformat(2,string_constant_10,error_string);
		      reclaim_gensym_string(dotted_addr);
		      reclaim_evaluation_sequence(seq);
		      reclaim_text_string(error_string);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    socket_1 = make_icmp_socket_1();
    buffer = make_variable_fill_icp_buffer();
    g2sock = make_transient_item(Qg2_socket);
    buflen = FIXNUM_SUB1(ISVREF(M_CAR(seq),(SI_Long)1L));
    SVREF(socket_1,FIX((SI_Long)3L)) = handle;
    register_socket_to_handle(socket_1,handle);
    set_non_savable_lookup_slot_value(g2sock,Qinternal_socket_qm,socket_1);
    SVREF(socket_1,FIX((SI_Long)11L)) = g2sock;
    temp = copy_null_terminated_string_as_text_string(dotted_addr);
    SVREF(socket_1,FIX((SI_Long)1L)) = temp;
    change_slot_value(3,g2sock,Qg2_socket_remote_host,
	    copy_text_string(ISVREF(socket_1,(SI_Long)1L)));
    i = (SI_Long)0L;
    ab_loop_repeat_ = IFIX(buflen);
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    temp = evaluation_sequence_aref(seq,FIX(i));
    UBYTE_8_ISASET_1(buffer,i,IFIX(temp));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (g2ext_icmp_write(IFIX(handle),IFIX(ttl),IFIX(id),IFIX(seqnum),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),IFIX(buflen),
	    (SI_Long)4096L) < (SI_Long)0L) {
	update_g2_socket_status(g2sock,Qicmp_error_status);
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  5);
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
		      twrite(string_constant_11);
		      i = (SI_Long)0L;
		      c = Nil;
		    next_loop_1:
		      c = FIX(UBYTE_8_ISAREF_1(buffer,i));
		      temp_1 = FIX((SI_Long)0L);
		      if (NUM_EQ(c,temp_1))
			  goto end_loop_1;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = c;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = c;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      i = i + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	SVREF(socket_1,FIX((SI_Long)15L)) = buflen;
	update_g2_socket_status(g2sock,Qicmp_waiting_reply);
    }
    reclaim_gensym_string(dotted_addr);
    reclaim_evaluation_sequence(seq);
    reclaim_variable_fill_icp_buffer(buffer);
    value_1 = g2sock;
    reclaim_text_string(host_as_evaluation_value);
    IDENTITY(seq_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    temp_1 = IDENTITY(value_1);
    return VALUES_1(temp_1);
}

static Object Qicmp_unknown;       /* icmp_unknown */

static Object Qicmp_echoreply;     /* icmp_echoreply */

static Object Qicmp_unreach;       /* icmp_unreach */

static Object Qicmp_sourcequench;  /* icmp_sourcequench */

static Object Qicmp_redirect;      /* icmp_redirect */

static Object Qicmp_echo;          /* icmp_echo */

static Object Qicmp_routeradvert;  /* icmp_routeradvert */

static Object Qicmp_routersolicit;  /* icmp_routersolicit */

static Object Qicmp_timxceed;      /* icmp_timxceed */

static Object Qicmp_paramprob;     /* icmp_paramprob */

static Object Qicmp_tstamp;        /* icmp_tstamp */

static Object Qicmp_tstampreply;   /* icmp_tstampreply */

static Object Qicmp_ireq;          /* icmp_ireq */

static Object Qicmp_ireqreply;     /* icmp_ireqreply */

static Object Qicmp_maskreq;       /* icmp_maskreq */

static Object Qicmp_maskreply;     /* icmp_maskreply */

/* TRANSLATE-ICMP-CODE */
Object translate_icmp_code(code)
    Object code;
{
    x_note_fn_call(241,55);
    if ( !(FIXNUMP(code) && FIXNUM_LE(FIX((SI_Long)-128L),code) && 
	    FIXNUM_LE(code,FIX((SI_Long)127L))))
	return VALUES_1(Qicmp_unknown);
    else
	switch (INTEGER_TO_CHAR(code)) {
	  case 0:
	    return VALUES_1(Qicmp_echoreply);
	  case 3:
	    return VALUES_1(Qicmp_unreach);
	  case 4:
	    return VALUES_1(Qicmp_sourcequench);
	  case 5:
	    return VALUES_1(Qicmp_redirect);
	  case 8:
	    return VALUES_1(Qicmp_echo);
	  case 9:
	    return VALUES_1(Qicmp_routeradvert);
	  case 10:
	    return VALUES_1(Qicmp_routersolicit);
	  case 11:
	    return VALUES_1(Qicmp_timxceed);
	  case 12:
	    return VALUES_1(Qicmp_paramprob);
	  case 13:
	    return VALUES_1(Qicmp_tstamp);
	  case 14:
	    return VALUES_1(Qicmp_tstampreply);
	  case 15:
	    return VALUES_1(Qicmp_ireq);
	  case 16:
	    return VALUES_1(Qicmp_ireqreply);
	  case 17:
	    return VALUES_1(Qicmp_maskreq);
	  case 18:
	    return VALUES_1(Qicmp_maskreply);
	  default:
	    return VALUES_1(Qicmp_unknown);
	}
}

static Object Qhost;               /* host */

static Object Qbytes;              /* bytes */

static Object Qab_structure;       /* structure */

/* HANDLE-READ-EVENT-FOR-ICMP-SOCKET */
Object handle_read_event_for_icmp_socket(icmp_socket,error_code,block_p)
    Object icmp_socket, error_code, block_p;
{
    Object handle, buffer, fbuffer, temp, typecode, host, bytes, struct_1;
    Object temp_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, thing, temp_3, schar_new_value, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol, item_or_value, x2, invocation;
    Object gensym_push_modify_macro_arg, car_1, cdr_1;
    SI_Long i, bv16_length, temp_2, aref_new_value, length_1, ab_loop_bind_;
    SI_Long gensymed_symbol_1, item_or_value_1;
    char temp_4;
    Declare_special(5);

    x_note_fn_call(241,56);
    handle = ISVREF(icmp_socket,(SI_Long)3L);
    buffer = make_variable_fill_icp_buffer();
    fbuffer = 
	    obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    i = (SI_Long)0L;
  next_loop:
    if (i >= (SI_Long)3L)
	goto end_loop;
    temp = Ping_seq_id_array;
    UBYTE_16_ISASET_1(temp,i,(SI_Long)0L);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    typecode = Nil;
    host = Nil;
    bytes = Nil;
    struct_1 = Nil;
  next_loop_1:
    typecode = FIX(g2ext_icmp_read(IFIX(handle),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),(SI_Long)4096L,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(fbuffer),(SI_Long)4096L,
	    UBYTE_16_SARRAY_TO_USHORT_PTR(Ping_seq_id_array)));
    temp_1 = FIX((SI_Long)0L);
    if ( !NUM_GE(typecode,temp_1))
	goto end_loop_1;
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
	      (SI_Long)3L));
      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
      temp_2 = bv16_length - (SI_Long)2L;
      aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
      temp_2 = bv16_length - (SI_Long)1L;
      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
      UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
	      c = Nil;
	    next_loop_2:
	      c = CHR(ISCHAR(fbuffer,i));
	      if (EQ(c,CHR('\000')))
		  goto end_loop_2;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = c;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  temp_3 = Fill_pointer_for_current_gensym_string;
		  thing = c;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,temp_3,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_2;
	    end_loop_2:;
	      host = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(icmp_socket,(SI_Long)15L));
    c = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_3:
    if (i >= ab_loop_bind_)
	goto end_loop_3;
    c = FIX(UBYTE_8_ISAREF_1(buffer,i));
    ab_loopvar__2 = eval_cons_1(c,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    i = i + (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:
    bytes = ab_loopvar_;
    goto end_1;
    bytes = Qnil;
  end_1:;
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)12L + 
	    (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,temp_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,temp_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qtype;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qtype;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = translate_icmp_code(typecode);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = translate_icmp_code(typecode);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qhost;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qhost;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = host;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = host;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qbytes;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qbytes;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(bytes);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(bytes);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qid;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qid;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)0L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)0L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(temp,FIX((SI_Long)8L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qseq;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qseq;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(temp,FIX((SI_Long)10L)) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)13L)) = Qttl;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)11L)) = Qttl;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)2L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(gensymed_symbol,FIX((SI_Long)14L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value_1 = UBYTE_16_ISAREF_1(Ping_seq_id_array,(SI_Long)2L);
	if (SIMPLE_VECTOR_P(FIX(item_or_value_1)) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(FIX(item_or_value_1))) > 
		(SI_Long)2L &&  !EQ(ISVREF(FIX(item_or_value_1),
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(FIX(item_or_value_1),(SI_Long)1L);
	    temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_4 = TRUEP(Nil);
	temp_3 = temp_4 ? get_reference_to_item(FIX(item_or_value_1)) : 
		FIX(item_or_value_1);
	SVREF(temp,FIX((SI_Long)12L)) = temp_3;
    }
    struct_1 = eval_cons_1(gensymed_symbol,Qab_structure);
    if (ISVREF(icmp_socket,(SI_Long)10L)) {
	gensymed_symbol = ISVREF(icmp_socket,(SI_Long)10L);
	invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
	if (invocation) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
	    SVREF(icmp_socket,FIX((SI_Long)10L)) = Nil;
	    if (SIMPLE_VECTOR_P(struct_1) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(struct_1)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(struct_1,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(struct_1,(SI_Long)1L);
		temp_4 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    if (temp_4)
		set_local_name_value_validating_environment(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),struct_1);
	    else
		set_code_body_invocation_local_name_value(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),struct_1);
	    wake_up_code_body_invocation(invocation);
	}
    }
    else {
	gensym_push_modify_macro_arg = struct_1;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(icmp_socket,(SI_Long)12L);
	temp = gensym_cons_1(car_1,cdr_1);
	SVREF(icmp_socket,FIX((SI_Long)12L)) = temp;
    }
    goto next_loop_1;
  end_loop_1:
    if (FIXNUM_EQ(typecode,Ne_error_value))
	update_g2_socket_status(ISVREF(icmp_socket,(SI_Long)11L),
		Qicmp_error_status);
    reclaim_variable_fill_icp_buffer(buffer);
    return reclaim_gensym_string(fbuffer);
}

/* HANDLE-NETWORK-CLOSE-FOR-ICMP-SOCKET */
Object handle_network_close_for_icmp_socket(icmp_socket,network_error_code)
    Object icmp_socket, network_error_code;
{
    x_note_fn_call(241,57);
    return VALUES_1(Nil);
}

static Object Qg2_read_ping;       /* g2-read-ping */

static Object Qab_gensym;          /* gensym */

/* READ-PING-STREAM */
Object read_ping_stream(g2_socket_as_evaluation_value,
	    ret_var_as_evaluation_value)
    Object g2_socket_as_evaluation_value, ret_var_as_evaluation_value;
{
    Object g2_socket, ret_var, icmp_socket, top_of_stack, message_1;
    Object gensym_pop_store, cons_1, next_cons, temp, svref_arg_2, value;
    Object gensymed_symbol, invocation, x2;
    char temp_1;

    x_note_fn_call(241,58);
    g2_socket = IDENTITY(g2_socket_as_evaluation_value);
    ret_var = ret_var_as_evaluation_value;
    icmp_socket = get_lookup_slot_value_given_default(g2_socket,
	    Qinternal_socket_qm,Nil);
    if ( !TRUEP(icmp_socket)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_3,
		g2_socket);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(ISVREF(icmp_socket,(SI_Long)10L)))
	set_blocking_socket_continuation(icmp_socket,Qg2_read_ping,ret_var);
    if (ISVREF(icmp_socket,(SI_Long)12L)) {
	gensym_pop_store = Nil;
	cons_1 = ISVREF(icmp_socket,(SI_Long)12L);
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
	SVREF(icmp_socket,FIX((SI_Long)12L)) = next_cons;
	value = gensym_pop_store;
	gensymed_symbol = ISVREF(icmp_socket,(SI_Long)10L);
	invocation = ISVREF(gensymed_symbol,(SI_Long)1L);
	if (invocation) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = Nil;
	    SVREF(icmp_socket,FIX((SI_Long)10L)) = Nil;
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		set_local_name_value_validating_environment(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),value);
	    else
		set_code_body_invocation_local_name_value(invocation,
			ISVREF(gensymed_symbol,(SI_Long)3L),value);
	    wake_up_code_body_invocation(invocation);
	}
    }
    IDENTITY(g2_socket_as_evaluation_value);
    return VALUES_0();
}

void socket2_INIT()
{
    Object temp, reclaim_structure_for_code_body_continuation_1, temp_1;
    Object reclaim_structure_for_blocking_socket_1, gensymed_symbol;
    Object handle_network_connect_for_blocking_socket_1;
    Object handle_network_close_for_blocking_socket_1;
    Object handle_write_event_for_blocking_socket_1;
    Object handle_read_event_for_blocking_socket_1;
    Object handle_network_accept_for_blocking_socket_1;
    Object reclaim_structure_for_icmp_socket_1;
    Object handle_read_event_for_icmp_socket_1;
    Object handle_network_close_for_icmp_socket_1;
    Object Qread_ping_stream, AB_package;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qicmp_socket;
    Object Qhandle_network_close, Qhandle_read_event, Qg2_initiate_ping;
    Object list_constant_1, Qreclaim_structure, Qoutstanding_icmp_socket_count;
    Object Qicmp_socket_structure_memory_usage, Qutilities2;
    Object string_constant_34, Qtype_description_of_type, string_constant_33;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qblocking_socket;
    Object Qhandle_network_accept, Qg2_tcp_listen, Qg2_tcp_read_bytes_as_text;
    Object Qg2_tcp_read, Qhandle_write_event, Qg2_tcp_write_bytes;
    Object Qg2_tcp_close, Qhandle_network_connect, Qslot_value_reclaimer;
    Object Qreclaim_internal_socket_qm_value;
    Object Qoutstanding_blocking_socket_count;
    Object Qblocking_socket_structure_memory_usage, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, list_constant;
    Object Qcreate_icon_description, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, Qentity, Qitem;
    Object Qcode_body_continuation, Qoutstanding_code_body_continuation_count;
    Object Qcode_body_continuation_structure_memory_usage, string_constant_13;
    Object string_constant_12;

    x_note_fn_call(241,59);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_code_body_continuation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-CONTINUATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qcode_body_continuation = STATIC_SYMBOL("CODE-BODY-CONTINUATION",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_code_body_continuation_g2_struct,
	    Qcode_body_continuation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qcode_body_continuation,
	    Qg2_defstruct_structure_name_code_body_continuation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_code_body_continuation == UNBOUND)
	The_type_description_of_code_body_continuation = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83g+y1n83g+y8n8k1l8n0000001l1n8y83-3Cy1o83s8y83s9y83sAy83s7ykpk0k0");
    temp = The_type_description_of_code_body_continuation;
    The_type_description_of_code_body_continuation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_code_body_continuation_g2_struct,
	    The_type_description_of_code_body_continuation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qcode_body_continuation,
	    The_type_description_of_code_body_continuation,
	    Qtype_description_of_type);
    Qoutstanding_code_body_continuation_count = 
	    STATIC_SYMBOL("OUTSTANDING-CODE-BODY-CONTINUATION-COUNT",
	    AB_package);
    Qcode_body_continuation_structure_memory_usage = 
	    STATIC_SYMBOL("CODE-BODY-CONTINUATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83g+y8s83-Mqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_code_body_continuation_count);
    push_optimized_constant(Qcode_body_continuation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_code_body_continuations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CODE-BODY-CONTINUATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_code_body_continuations,
	    Chain_of_available_code_body_continuations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_code_body_continuations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcode_body_continuation_count = 
	    STATIC_SYMBOL("CODE-BODY-CONTINUATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcode_body_continuation_count,
	    Code_body_continuation_count);
    record_system_variable(Qcode_body_continuation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_code_body_continuations_vector == UNBOUND)
	Chain_of_available_code_body_continuations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcode_body_continuation_structure_memory_usage,
	    STATIC_FUNCTION(code_body_continuation_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_code_body_continuation_count,
	    STATIC_FUNCTION(outstanding_code_body_continuation_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_code_body_continuation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_code_body_continuation,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcode_body_continuation,
	    reclaim_structure_for_code_body_continuation_1);
    Qcomplete_code_body_continuation = 
	    STATIC_SYMBOL("COMPLETE-CODE-BODY-CONTINUATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcomplete_code_body_continuation,
	    STATIC_FUNCTION(complete_code_body_continuation,NIL,FALSE,1,1));
    Qg2_socket = STATIC_SYMBOL("G2-SOCKET",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qg2_socket,list_constant);
    string_constant_14 = STATIC_STRING("1m1l83Iy1l83Ly");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_15 = 
	    STATIC_STRING("1p4z8r8u8u83NPy83NPy01p8w9k3ky3ky13Jy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-jy83-Ly1n83jy1");
    string_constant_16 = 
	    STATIC_STRING("mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1mk3ky1mkk1o83");
    string_constant_17 = 
	    STATIC_STRING("Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1mn3hy1n1m3hy3h");
    string_constant_18 = 
	    STATIC_STRING("y1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy1n83Oy1mp3Oy1m3Ly3Oy1n83Oy1");
    string_constant_19 = 
	    STATIC_STRING("m3Ly3Oy1m3Ly3Hy1n83Oy1m3Ly3Hy1m3fy3Hy1n83Oy1mz3Gy1mz3Oy1n83Oy1m3Vy3Hy1m3Vy3Qy1p83Jy1m3Ry3Qy1m3Ry3Xy1m3Zy3Xy1m3Zy3Qy1p83Jy1m3Ty3S");
    string_constant_20 = 
	    STATIC_STRING("y1m3Ty3Vy1m3Xy3Vy1m3Xy3Sy1p83Jy1mvx1mv3Gy1m3Fy3Gy1m3Fyx1p83Jy1mxz1mx3Ey1m3Dy3Ey1m3Dyz001o1l8l1l8o1l8z1m83Dy53YySee comment on EN");
    string_constant_21 = 
	    STATIC_STRING("TITY class definition000004z8r83NQy83NQy83NPy83NPy00001p1l8l1l8o1l83Fy1m8p83-qy1l83Hy000004z8r83NSy83NSy83NPy83NPy0835ry001p1l8l");
    string_constant_22 = 
	    STATIC_STRING("1l8o1l83Fy1m8p83-qy1l83Hy000004z8r83NRy83NRy83NPy83NPy00001p1l8l1l8o1l83Fy1m8p83-qy1l83Hy000004z8r83SYy83SYy83NPy83NPy00001n1l83");
    string_constant_23 = STATIC_STRING("Fy1l8l1l83Hy00000");
    string_constant_24 = 
	    STATIC_STRING("1r8q1o83NPy1m83Ry83-+y83Iy83Ly1m8u1p8w9k3ky3ky13Jy1q83-1y2l83*Ny83Ty2l83-Ly83-Wy2l83-ny83-gy2l83-my83-Ry2l83*Uy83Ty1l83-iy1l83-j");
    string_constant_25 = 
	    STATIC_STRING("y83-Ly1n83jy1mkk1m3ky3ky83-ny1q83qy1q1mkk1m3kyk1m3hyn1mnn1mn3hy1mk3ky1n1mkk1m3kyk1m3hyn1n1mnn1mn3hy1mk3ky1n1mkk1m3hyn1mnn1n1mnn1");
    string_constant_26 = 
	    STATIC_STRING("mk3ky1mkk1o83Oy1mp3fy1m3ey3fy1m3eyp83-my1q83qy1q1m3hyn1m3kyk1m3ky3ky1mk3ky1mn3hy1m3hy3hy1n1m3hyn1m3kyk1m3ky3ky1n1m3ky3ky1mk3ky1m");
    string_constant_27 = 
	    STATIC_STRING("n3hy1n1m3hy3hy1m3hyn1m3ky3ky1n1m3ky3ky1mn3hy1m3hy3hy83*Ny1p83Jy1mkk1mk3ky1m3ky3ky1m3kyk83*Ny1o83Oy1m3eyp1mpp1mp3fy1n83Oy1mp3Oy1m");
    string_constant_28 = 
	    STATIC_STRING("3Ly3Oy1n83Oy1m3Ly3Oy1m3Ly3Hy1n83Oy1m3Ly3Hy1m3fy3Hy1n83Oy1mz3Gy1mz3Oy1n83Oy1m3Vy3Hy1m3Vy3Qy1p83Jy1m3Ry3Qy1m3Ry3Xy1m3Zy3Xy1m3Zy3Qy");
    string_constant_29 = 
	    STATIC_STRING("1p83Jy1m3Ty3Sy1m3Ty3Vy1m3Xy3Vy1m3Xy3Sy1p83Jy1mvx1mv3Gy1m3Fy3Gy1m3Fyx1p83Jy1mxz1mx3Ey1m3Dy3Ey1m3Dyz1q83NQy08o83Fy1m8p83-qy83Hy1q8");
    string_constant_30 = 
	    STATIC_STRING("3NSy835ry8o83Fy1m8p83-qy83Hy1q83NRy08o83Fy1m8p83-qy83Hy1p83SYy083Fy8l83Hy");
    temp = regenerate_optimized_constant(string_constant_14);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qg2_socket,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,regenerate_optimized_constant(list(7,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30)),Nil);
    Qg2_socket_status = STATIC_SYMBOL("G2-SOCKET-STATUS",AB_package);
    Qconnected = STATIC_SYMBOL("CONNECTED",AB_package);
    Qconnected_secure = STATIC_SYMBOL("CONNECTED-SECURE",AB_package);
    Qg2_defstruct_structure_name_blocking_socket_g2_struct = 
	    STATIC_SYMBOL("BLOCKING-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qblocking_socket = STATIC_SYMBOL("BLOCKING-SOCKET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_blocking_socket_g2_struct,
	    Qblocking_socket,Qab_name_of_unique_structure_type);
    mutate_global_property(Qblocking_socket,
	    Qg2_defstruct_structure_name_blocking_socket_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_blocking_socket == UNBOUND)
	The_type_description_of_blocking_socket = Nil;
    string_constant_31 = 
	    STATIC_STRING("43Dy8m83B-y1p83B-y837Vy832ky8n8k1l837Vy0000001l1m8x837Vykzk0k0");
    temp = The_type_description_of_blocking_socket;
    The_type_description_of_blocking_socket = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_31));
    mutate_global_property(Qg2_defstruct_structure_name_blocking_socket_g2_struct,
	    The_type_description_of_blocking_socket,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qblocking_socket,
	    The_type_description_of_blocking_socket,Qtype_description_of_type);
    Qoutstanding_blocking_socket_count = 
	    STATIC_SYMBOL("OUTSTANDING-BLOCKING-SOCKET-COUNT",AB_package);
    Qblocking_socket_structure_memory_usage = 
	    STATIC_SYMBOL("BLOCKING-SOCKET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_32 = STATIC_STRING("1q83B-y8s83-Kry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_blocking_socket_count);
    push_optimized_constant(Qblocking_socket_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_32));
    Qchain_of_available_blocking_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BLOCKING-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_blocking_sockets,
	    Chain_of_available_blocking_sockets);
    record_system_variable(Qchain_of_available_blocking_sockets,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qblocking_socket_count = STATIC_SYMBOL("BLOCKING-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblocking_socket_count,Blocking_socket_count);
    record_system_variable(Qblocking_socket_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_blocking_sockets_vector == UNBOUND)
	Chain_of_available_blocking_sockets_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qblocking_socket_structure_memory_usage,
	    STATIC_FUNCTION(blocking_socket_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_blocking_socket_count,
	    STATIC_FUNCTION(outstanding_blocking_socket_count,NIL,FALSE,0,0));
    reclaim_structure_for_blocking_socket_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_blocking_socket,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qblocking_socket,
	    reclaim_structure_for_blocking_socket_1);
    Qcomplete_blocking_socket_continuation = 
	    STATIC_SYMBOL("COMPLETE-BLOCKING-SOCKET-CONTINUATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcomplete_blocking_socket_continuation,
	    STATIC_FUNCTION(complete_blocking_socket_continuation,NIL,
	    FALSE,1,1));
    Qinternal_socket_qm = STATIC_SYMBOL("INTERNAL-SOCKET\?",AB_package);
    Qreclaim_internal_socket_qm_value = 
	    STATIC_SYMBOL("RECLAIM-INTERNAL-SOCKET\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_internal_socket_qm_value,
	    STATIC_FUNCTION(reclaim_internal_socket_qm_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qinternal_socket_qm,
	    SYMBOL_FUNCTION(Qreclaim_internal_socket_qm_value),
	    Qslot_value_reclaimer);
    Qconnection_closed = STATIC_SYMBOL("CONNECTION-CLOSED",AB_package);
    Qg2_socket_remote_host = STATIC_SYMBOL("G2-SOCKET-REMOTE-HOST",AB_package);
    Qg2_socket_port = STATIC_SYMBOL("G2-SOCKET-PORT",AB_package);
    string_constant = 
	    STATIC_STRING("Error message unavailable for closed socket");
    string_constant_1 = 
	    STATIC_STRING("Network ~a failure: ~s (error code ~d)");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2_tcp_connect = STATIC_SYMBOL("G2-TCP-CONNECT",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_connect,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsecure = STATIC_SYMBOL("SECURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_tcp_connect,STATIC_FUNCTION(g2_tcp_connect,NIL,
	    FALSE,4,4));
    Qhandle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    string_constant_2 = STATIC_STRING("connection");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    handle_network_connect_for_blocking_socket_1 = 
	    STATIC_FUNCTION(handle_network_connect_for_blocking_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_network_connect,
	    Qblocking_socket,handle_network_connect_for_blocking_socket_1);
    Qg2_tcp_close = STATIC_SYMBOL("G2-TCP-CLOSE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_close,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_tcp_close,STATIC_FUNCTION(g2_tcp_close,NIL,
	    FALSE,1,1));
    Qhandle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",AB_package);
    Qconnection_closed_with_unread_data = 
	    STATIC_SYMBOL("CONNECTION-CLOSED-WITH-UNREAD-DATA",AB_package);
    handle_network_close_for_blocking_socket_1 = 
	    STATIC_FUNCTION(handle_network_close_for_blocking_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_network_close,Qblocking_socket,
	    handle_network_close_for_blocking_socket_1);
    Qcomplete_tcp_write_continuation = 
	    STATIC_SYMBOL("COMPLETE-TCP-WRITE-CONTINUATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcomplete_tcp_write_continuation,
	    STATIC_FUNCTION(complete_tcp_write_continuation,NIL,FALSE,1,1));
    Qg2_tcp_write = STATIC_SYMBOL("G2-TCP-WRITE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_write,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_3 = STATIC_STRING("Invalid socket ~NF");
    SET_SYMBOL_FUNCTION(Qg2_tcp_write,STATIC_FUNCTION(g2_tcp_write,NIL,
	    FALSE,3,3));
    Qg2_tcp_write_bytes = STATIC_SYMBOL("G2-TCP-WRITE-BYTES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_write_bytes,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_tcp_write_bytes,
	    STATIC_FUNCTION(g2_tcp_write_bytes,NIL,FALSE,3,3));
    Qblocked = STATIC_SYMBOL("BLOCKED",AB_package);
    Qconnection_write_error = STATIC_SYMBOL("CONNECTION-WRITE-ERROR",
	    AB_package);
    Qhandle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    handle_write_event_for_blocking_socket_1 = 
	    STATIC_FUNCTION(handle_write_event_for_blocking_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_write_event,Qblocking_socket,
	    handle_write_event_for_blocking_socket_1);
    Qg2_tcp_read_block = STATIC_SYMBOL("G2-TCP-READ-BLOCK",AB_package);
    Qg2_tcp_read_byte = STATIC_SYMBOL("G2-TCP-READ-BYTE",AB_package);
    Qg2_tcp_read_line = STATIC_SYMBOL("G2-TCP-READ-LINE",AB_package);
    Qg2_tcp_read_n_bytes = STATIC_SYMBOL("G2-TCP-READ-N-BYTES",AB_package);
    Qg2_tcp_read = STATIC_SYMBOL("G2-TCP-READ",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_read,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    string_constant_4 = 
	    STATIC_STRING("Mode ~s is not a valid read mode.  Must be BLOCK, LINE, or BYTE");
    SET_SYMBOL_FUNCTION(Qg2_tcp_read,STATIC_FUNCTION(g2_tcp_read,NIL,FALSE,
	    3,3));
    Qg2_tcp_read_bytes_as_text = STATIC_SYMBOL("G2-TCP-READ-BYTES-AS-TEXT",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_read_bytes_as_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_5 = 
	    STATIC_STRING("Request to read ~d bytes which exceeds the ~\n                    maximum G2 text length, ~d");
    SET_SYMBOL_FUNCTION(Qg2_tcp_read_bytes_as_text,
	    STATIC_FUNCTION(g2_tcp_read_bytes_as_text,NIL,FALSE,3,3));
    Qhandle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    string_constant_6 = STATIC_STRING("read");
    handle_read_event_for_blocking_socket_1 = 
	    STATIC_FUNCTION(handle_read_event_for_blocking_socket,NIL,
	    FALSE,3,3);
    record_direct_structure_method(Qhandle_read_event,Qblocking_socket,
	    handle_read_event_for_blocking_socket_1);
    string_constant_7 = STATIC_STRING("Could not make exact TCP connection");
    string_constant_8 = 
	    STATIC_STRING("DECnet not supported by this product on this platform");
    Qg2_tcp_listen = STATIC_SYMBOL("G2-TCP-LISTEN",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_listen,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qexact = STATIC_SYMBOL("EXACT",AB_package);
    Qcertificate = STATIC_SYMBOL("CERTIFICATE",AB_package);
    Qlistening_secure = STATIC_SYMBOL("LISTENING-SECURE",AB_package);
    Qlistening = STATIC_SYMBOL("LISTENING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_tcp_listen,STATIC_FUNCTION(g2_tcp_listen,NIL,
	    FALSE,2,2));
    string_constant_9 = STATIC_STRING("accept new connection");
    Qhandle_network_accept = STATIC_SYMBOL("HANDLE-NETWORK-ACCEPT",AB_package);
    Qg2_tcp_accept = STATIC_SYMBOL("G2-TCP-ACCEPT",AB_package);
    handle_network_accept_for_blocking_socket_1 = 
	    STATIC_FUNCTION(handle_network_accept_for_blocking_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_network_accept,Qblocking_socket,
	    handle_network_accept_for_blocking_socket_1);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_tcp_accept,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_tcp_accept,STATIC_FUNCTION(g2_tcp_accept,NIL,
	    FALSE,2,2));
    Qg2_defstruct_structure_name_icmp_socket_g2_struct = 
	    STATIC_SYMBOL("ICMP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qicmp_socket = STATIC_SYMBOL("ICMP-SOCKET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_icmp_socket_g2_struct,
	    Qicmp_socket,Qab_name_of_unique_structure_type);
    mutate_global_property(Qicmp_socket,
	    Qg2_defstruct_structure_name_icmp_socket_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_icmp_socket == UNBOUND)
	The_type_description_of_icmp_socket = Nil;
    string_constant_33 = 
	    STATIC_STRING("43Dy8m83iZy1q83iZy83B-y837Vy832ky8n8k1l83B-y0000001l1m8x83B-yk3Cyk0k0");
    temp = The_type_description_of_icmp_socket;
    The_type_description_of_icmp_socket = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_33));
    mutate_global_property(Qg2_defstruct_structure_name_icmp_socket_g2_struct,
	    The_type_description_of_icmp_socket,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qicmp_socket,
	    The_type_description_of_icmp_socket,Qtype_description_of_type);
    Qoutstanding_icmp_socket_count = 
	    STATIC_SYMBOL("OUTSTANDING-ICMP-SOCKET-COUNT",AB_package);
    Qicmp_socket_structure_memory_usage = 
	    STATIC_SYMBOL("ICMP-SOCKET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_34 = STATIC_STRING("1q83iZy8s83-YMy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_icmp_socket_count);
    push_optimized_constant(Qicmp_socket_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_34));
    Qchain_of_available_icmp_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ICMP-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_icmp_sockets,
	    Chain_of_available_icmp_sockets);
    record_system_variable(Qchain_of_available_icmp_sockets,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qicmp_socket_count = STATIC_SYMBOL("ICMP-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicmp_socket_count,Icmp_socket_count);
    record_system_variable(Qicmp_socket_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_icmp_sockets_vector == UNBOUND)
	Chain_of_available_icmp_sockets_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qicmp_socket_structure_memory_usage,
	    STATIC_FUNCTION(icmp_socket_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_icmp_socket_count,
	    STATIC_FUNCTION(outstanding_icmp_socket_count,NIL,FALSE,0,0));
    reclaim_structure_for_icmp_socket_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_icmp_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qicmp_socket,
	    reclaim_structure_for_icmp_socket_1);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    if (Ping_seq_id_array == UNBOUND)
	Ping_seq_id_array = make_array(3,FIX((SI_Long)3L),Kelement_type,
		list_constant_1);
    Qg2_initiate_ping = STATIC_SYMBOL("G2-INITIATE-PING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_initiate_ping,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qttl = STATIC_SYMBOL("TTL",AB_package);
    Qseq = STATIC_SYMBOL("SEQ",AB_package);
    Qid = STATIC_SYMBOL("ID",AB_package);
    string_constant_10 = STATIC_STRING("Failed to open ping socket: ~s");
    Qicmp_error_status = STATIC_SYMBOL("ICMP-ERROR-STATUS",AB_package);
    string_constant_11 = STATIC_STRING("Failed to send ping request: ");
    Qicmp_waiting_reply = STATIC_SYMBOL("ICMP-WAITING-REPLY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_initiate_ping,STATIC_FUNCTION(g2_initiate_ping,
	    NIL,FALSE,3,3));
    Qicmp_unknown = STATIC_SYMBOL("ICMP_UNKNOWN",AB_package);
    Qicmp_echoreply = STATIC_SYMBOL("ICMP_ECHOREPLY",AB_package);
    Qicmp_unreach = STATIC_SYMBOL("ICMP_UNREACH",AB_package);
    Qicmp_sourcequench = STATIC_SYMBOL("ICMP_SOURCEQUENCH",AB_package);
    Qicmp_redirect = STATIC_SYMBOL("ICMP_REDIRECT",AB_package);
    Qicmp_echo = STATIC_SYMBOL("ICMP_ECHO",AB_package);
    Qicmp_routeradvert = STATIC_SYMBOL("ICMP_ROUTERADVERT",AB_package);
    Qicmp_routersolicit = STATIC_SYMBOL("ICMP_ROUTERSOLICIT",AB_package);
    Qicmp_timxceed = STATIC_SYMBOL("ICMP_TIMXCEED",AB_package);
    Qicmp_paramprob = STATIC_SYMBOL("ICMP_PARAMPROB",AB_package);
    Qicmp_tstamp = STATIC_SYMBOL("ICMP_TSTAMP",AB_package);
    Qicmp_tstampreply = STATIC_SYMBOL("ICMP_TSTAMPREPLY",AB_package);
    Qicmp_ireq = STATIC_SYMBOL("ICMP_IREQ",AB_package);
    Qicmp_ireqreply = STATIC_SYMBOL("ICMP_IREQREPLY",AB_package);
    Qicmp_maskreq = STATIC_SYMBOL("ICMP_MASKREQ",AB_package);
    Qicmp_maskreply = STATIC_SYMBOL("ICMP_MASKREPLY",AB_package);
    Qhost = STATIC_SYMBOL("HOST",AB_package);
    Qbytes = STATIC_SYMBOL("BYTES",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    handle_read_event_for_icmp_socket_1 = 
	    STATIC_FUNCTION(handle_read_event_for_icmp_socket,NIL,FALSE,3,3);
    record_direct_structure_method(Qhandle_read_event,Qicmp_socket,
	    handle_read_event_for_icmp_socket_1);
    handle_network_close_for_icmp_socket_1 = 
	    STATIC_FUNCTION(handle_network_close_for_icmp_socket,NIL,FALSE,
	    2,2);
    record_direct_structure_method(Qhandle_network_close,Qicmp_socket,
	    handle_network_close_for_icmp_socket_1);
    Qread_ping_stream = STATIC_SYMBOL("READ-PING-STREAM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qread_ping_stream,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_read_ping = STATIC_SYMBOL("G2-READ-PING",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    SET_SYMBOL_FUNCTION(Qread_ping_stream,STATIC_FUNCTION(read_ping_stream,
	    NIL,FALSE,2,2));
}
