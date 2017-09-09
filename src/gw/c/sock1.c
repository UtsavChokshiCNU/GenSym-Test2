/* sock1.c
 * Input file:  socket1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sock1.h"


Object G2int_the_type_description_of_tcp_socket = UNBOUND;

Object G2int_chain_of_available_tcp_sockets = UNBOUND;

Object G2int_tcp_socket_count = UNBOUND;

/* RECLAIM-TCP-SOCKET-1 */
Object g2int_reclaim_tcp_socket_1(tcp_socket)
    Object tcp_socket;
{
    Object old_structure_being_reclaimed, thing, vector_1, schedule_task_qm;
    Object old_structure_being_reclaimed_1, svref_new_value;

    x_note_fn_call(52,0);
    inline_note_reclaim_cons(tcp_socket,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = tcp_socket;
    thing = ISVREF(tcp_socket,(SI_Long)1L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	g2int_reclaim_wide_string(thing);
    SVREF(tcp_socket,FIX((SI_Long)1L)) = Nil;
    vector_1 = ISVREF(tcp_socket,(SI_Long)5L);
    if (vector_1)
	g2int_reclaim_variable_fill_icp_buffer(vector_1);
    SVREF(tcp_socket,FIX((SI_Long)5L)) = Nil;
    g2int_reclaim_if_socket_buffer(ISVREF(tcp_socket,(SI_Long)8L));
    SVREF(tcp_socket,FIX((SI_Long)8L)) = Nil;
    schedule_task_qm = ISVREF(tcp_socket,(SI_Long)9L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed_1 = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = schedule_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    SVREF(tcp_socket,FIX((SI_Long)9L)) = svref_new_value;
    SVREF(tcp_socket,FIX((SI_Long)9L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_tcp_sockets;
    SVREF(tcp_socket,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_tcp_sockets = tcp_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TCP-SOCKET */
Object g2int_reclaim_structure_for_tcp_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(52,1);
    return g2int_reclaim_tcp_socket_1(tcp_socket);
}

static Object Qg2_defstruct_structure_name_tcp_socket_g2_struct;  /* g2-defstruct-structure-name::tcp-socket-g2-struct */

/* MAKE-PERMANENT-TCP-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_tcp_socket_structure_internal()
{
    Object def_structure_tcp_socket_variable, tcp_socket_count_new_value;
    Object defstruct_g2_tcp_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(52,2);
    def_structure_tcp_socket_variable = Nil;
    tcp_socket_count_new_value = FIXNUM_ADD1(G2int_tcp_socket_count);
    G2int_tcp_socket_count = tcp_socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_tcp_socket_variable = Nil;
	gensymed_symbol = (SI_Long)10L;
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
	defstruct_g2_tcp_socket_variable = the_array;
	SVREF(defstruct_g2_tcp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tcp_socket_g2_struct;
	def_structure_tcp_socket_variable = defstruct_g2_tcp_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_tcp_socket_variable);
}

/* MAKE-TCP-SOCKET-1 */
Object g2int_make_tcp_socket_1()
{
    Object def_structure_tcp_socket_variable;

    x_note_fn_call(52,3);
    def_structure_tcp_socket_variable = G2int_chain_of_available_tcp_sockets;
    if (def_structure_tcp_socket_variable) {
	G2int_chain_of_available_tcp_sockets = 
		ISVREF(def_structure_tcp_socket_variable,(SI_Long)0L);
	SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tcp_socket_g2_struct;
    }
    else
	def_structure_tcp_socket_variable = 
		g2int_make_permanent_tcp_socket_structure_internal();
    inline_note_allocate_cons(def_structure_tcp_socket_variable,Nil);
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)4L)) = T;
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_tcp_socket_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_tcp_socket_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_tcp_socket_variable);
}

static Object string_constant;     /* "TCP_IP:~a:~a" */

static Object string_constant_1;   /* "~a" */

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* CONNECT-SOCKET */
Object g2int_connect_socket(socket_1,host,port,secure_qm)
    Object socket_1, host, port, secure_qm;
{
    Object network_pathname, port_string, handle, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(52,4);
    network_pathname = g2int_tformat_gensym_string(3,string_constant,host,
	    port);
    port_string = g2int_tformat_gensym_string(2,string_constant_1,port);
    handle = g2int_network_connect(4,network_pathname,host,port_string,
	    secure_qm);
    g2int_reclaim_gensym_string(network_pathname);
    g2int_reclaim_gensym_string(port_string);
    if ( !(IFIX(handle) < (SI_Long)0L)) {
	svref_new_value = g2int_copy_text_string(host);
	SVREF(socket_1,FIX((SI_Long)1L)) = svref_new_value;
	SVREF(socket_1,FIX((SI_Long)2L)) = port;
	SVREF(socket_1,FIX((SI_Long)3L)) = handle;
	g2int_register_socket_to_handle(socket_1,handle);
	if ( !((SI_Long)0L == ne_connected_p(IFIX(handle)))) {
	    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
		    (SI_Long)9L),(SI_Long)22L);
	    gensymed_symbol_1 = socket_1;
	    gensymed_symbol_2 = ne_last_error_code(IFIX(handle));
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    FIX(gensymed_symbol_2));
	}
	temp = socket_1;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* HANDLE-NETWORK-CONNECT-FOR-TCP-SOCKET */
Object g2int_handle_network_connect_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    x_note_fn_call(52,5);
    return VALUES_1(Nil);
}

/* C-NETWORK-WRITE-STRING */
Object g2int_c_network_write_string(handle,buffer,offset,length_1)
    Object handle, buffer, offset, length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(52,6);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_network_write(IFIX(handle),ISTRING(temp),IFIX(offset),
	    IFIX(length_1)));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_socket_output_buffer = UNBOUND;

Object G2int_chain_of_available_socket_output_buffers = UNBOUND;

Object G2int_socket_output_buffer_count = UNBOUND;

/* RECLAIM-SOCKET-OUTPUT-BUFFER-1 */
Object g2int_reclaim_socket_output_buffer_1(socket_output_buffer)
    Object socket_output_buffer;
{
    Object old_structure_being_reclaimed, vector_1, svref_new_value;

    x_note_fn_call(52,7);
    inline_note_reclaim_cons(socket_output_buffer,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = socket_output_buffer;
    g2int_reclaim_socket_buffer_data(ISVREF(socket_output_buffer,(SI_Long)1L));
    SVREF(socket_output_buffer,FIX((SI_Long)1L)) = Nil;
    vector_1 = ISVREF(socket_output_buffer,(SI_Long)3L);
    if (vector_1)
	g2int_reclaim_variable_fill_icp_buffer(vector_1);
    SVREF(socket_output_buffer,FIX((SI_Long)3L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_socket_output_buffers;
    SVREF(socket_output_buffer,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_socket_output_buffers = socket_output_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SOCKET-OUTPUT-BUFFER */
Object g2int_reclaim_structure_for_socket_output_buffer(socket_output_buffer)
    Object socket_output_buffer;
{
    x_note_fn_call(52,8);
    return g2int_reclaim_socket_output_buffer_1(socket_output_buffer);
}

static Object Qg2_defstruct_structure_name_socket_output_buffer_g2_struct;  /* g2-defstruct-structure-name::socket-output-buffer-g2-struct */

/* MAKE-PERMANENT-SOCKET-OUTPUT-BUFFER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_socket_output_buffer_structure_internal()
{
    Object def_structure_socket_output_buffer_variable;
    Object socket_output_buffer_count_new_value;
    Object defstruct_g2_socket_output_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(52,9);
    def_structure_socket_output_buffer_variable = Nil;
    socket_output_buffer_count_new_value = 
	    FIXNUM_ADD1(G2int_socket_output_buffer_count);
    G2int_socket_output_buffer_count = socket_output_buffer_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_socket_output_buffer_variable = Nil;
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
	defstruct_g2_socket_output_buffer_variable = the_array;
	SVREF(defstruct_g2_socket_output_buffer_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_socket_output_buffer_g2_struct;
	def_structure_socket_output_buffer_variable = 
		defstruct_g2_socket_output_buffer_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_socket_output_buffer_variable);
}

/* MAKE-SOCKET-OUTPUT-BUFFER-1 */
Object g2int_make_socket_output_buffer_1()
{
    Object def_structure_socket_output_buffer_variable;

    x_note_fn_call(52,10);
    def_structure_socket_output_buffer_variable = 
	    G2int_chain_of_available_socket_output_buffers;
    if (def_structure_socket_output_buffer_variable) {
	G2int_chain_of_available_socket_output_buffers = 
		ISVREF(def_structure_socket_output_buffer_variable,
		(SI_Long)0L);
	SVREF(def_structure_socket_output_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_output_buffer_g2_struct;
    }
    else
	def_structure_socket_output_buffer_variable = 
		g2int_make_permanent_socket_output_buffer_structure_internal();
    inline_note_allocate_cons(def_structure_socket_output_buffer_variable,Nil);
    SVREF(def_structure_socket_output_buffer_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_socket_output_buffer_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_socket_output_buffer_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_socket_output_buffer_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_socket_output_buffer_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_socket_output_buffer_variable);
}

/* RECLAIM-SOCKET-BUFFER-DATA */
Object g2int_reclaim_socket_buffer_data(data)
    Object data;
{
    Object temp;

    x_note_fn_call(52,11);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(data) != (SI_Long)0L ? 
	    g2int_reclaim_text_string(data) : Nil;
    return VALUES_1(temp);
}

/* RECLAIM-IF-SOCKET-BUFFER */
Object g2int_reclaim_if_socket_buffer(socket_buffer)
    Object socket_buffer;
{
    Object temp;

    x_note_fn_call(52,12);
    temp = socket_buffer ? 
	    g2int_reclaim_socket_output_buffer_1(socket_buffer) : Nil;
    return VALUES_1(temp);
}

/* ADD-BUFFER-TO-SOCKET */
Object g2int_add_buffer_to_socket(sob,tcp_socket)
    Object sob, tcp_socket;
{
    Object prev;

    x_note_fn_call(52,13);
    if (ISVREF(tcp_socket,(SI_Long)8L)) {
	prev = ISVREF(tcp_socket,(SI_Long)8L);
      next_loop:
	if ( !TRUEP(ISVREF(prev,(SI_Long)5L)))
	    goto end_loop;
	prev = ISVREF(prev,(SI_Long)5L);
	goto next_loop;
      end_loop:
	SVREF(prev,FIX((SI_Long)5L)) = sob;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(SVREF(tcp_socket,FIX((SI_Long)8L)) = sob);
}

static Object Qg2int_blocked;      /* blocked */

/* WRITE-TO-SOCKET */
Object g2int_write_to_socket(tcp_socket,string_1)
    Object tcp_socket, string_1;
{
    Object length_1, bytes_written, temp, sob, svref_new_value;

    x_note_fn_call(52,14);
    length_1 = g2int_text_string_length(string_1);
    bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
	    g2int_c_network_write_string(ISVREF(tcp_socket,(SI_Long)3L),
	    string_1,FIX((SI_Long)0L),length_1) : FIX((SI_Long)-1L);
    temp = FIXNUM_EQ(bytes_written,length_1) ? T : Nil;
    if (temp);
    else if (IFIX(bytes_written) >= (SI_Long)0L) {
	sob = g2int_make_socket_output_buffer_1();
	svref_new_value = g2int_copy_text_string(string_1);
	SVREF(sob,FIX((SI_Long)1L)) = svref_new_value;
	SVREF(sob,FIX((SI_Long)4L)) = bytes_written;
	g2int_add_buffer_to_socket(sob,tcp_socket);
	temp = Qg2int_blocked;
    }
    else
	temp = Qerror;
    return VALUES_1(temp);
}

static Object string_constant_2;   /* "Error sending socket buffer" */

static Object string_constant_3;   /* "ERROR: Unrecognized value type in network I/O.  Some data may be dropped." */

/* TRY-TO-SEND-SOCKET-BUFFER */
Object g2int_try_to_send_socket_buffer(tcp_socket)
    Object tcp_socket;
{
    Object sob, temp, thing, string_1, current, length_1, bytes_written;
    Object svref_new_value, incff_1_arg;

    x_note_fn_call(52,15);
    sob = ISVREF(tcp_socket,(SI_Long)8L);
    temp =  !TRUEP(sob) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	thing = ISVREF(sob,(SI_Long)1L);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L) {
	    string_1 = ISVREF(sob,(SI_Long)1L);
	    current = ISVREF(sob,(SI_Long)4L);
	    length_1 = FIXNUM_MINUS(g2int_text_string_length(string_1),
		    current);
	    bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
		    g2int_c_network_write_string(ISVREF(tcp_socket,
		    (SI_Long)3L),string_1,current,length_1) : 
		    FIX((SI_Long)-1L);
	    if (FIXNUM_EQ(bytes_written,length_1)) {
		svref_new_value = ISVREF(sob,(SI_Long)5L);
		SVREF(tcp_socket,FIX((SI_Long)8L)) = svref_new_value;
		g2int_reclaim_socket_output_buffer_1(sob);
		return g2int_try_to_send_socket_buffer(tcp_socket);
	    }
	    else if (IFIX(bytes_written) >= (SI_Long)0L) {
		incff_1_arg = bytes_written;
		svref_new_value = FIXNUM_ADD(ISVREF(sob,(SI_Long)4L),
			incff_1_arg);
		return VALUES_1(SVREF(sob,FIX((SI_Long)4L)) = svref_new_value);
	    }
	    else
		return g2int_notify_user_at_console(1,string_constant_2);
	}
	else {
	    g2int_notify_user_at_console(1,string_constant_3);
	    svref_new_value = ISVREF(sob,(SI_Long)5L);
	    SVREF(tcp_socket,FIX((SI_Long)8L)) = svref_new_value;
	    g2int_reclaim_socket_output_buffer_1(sob);
	    return g2int_try_to_send_socket_buffer(tcp_socket);
	}
    }
}

/* HANDLE-WRITE-EVENT-FOR-TCP-SOCKET */
Object g2int_handle_write_event_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    x_note_fn_call(52,16);
    g2int_try_to_send_socket_buffer(tcp_socket);
    return VALUES_1(Nil);
}

/* HANDLE-READ-EVENT-FOR-TCP-SOCKET */
Object g2int_handle_read_event_for_tcp_socket(tcp_socket,error_code,block_p)
    Object tcp_socket, error_code, block_p;
{
    x_note_fn_call(52,17);
    return VALUES_1(Nil);
}

/* READ-BUFFER-FROM-SOCKET */
Object g2int_read_buffer_from_socket(tcp_socket)
    Object tcp_socket;
{
    Object svref_new_value, octets_read_or_status, handle, temp;

    x_note_fn_call(52,18);
    if ( !TRUEP(ISVREF(tcp_socket,(SI_Long)5L))) {
	svref_new_value = g2int_make_variable_fill_icp_buffer();
	SVREF(tcp_socket,FIX((SI_Long)5L)) = svref_new_value;
    }
    octets_read_or_status = Nil;
    handle = ISVREF(tcp_socket,(SI_Long)3L);
    octets_read_or_status = handle ? FIX(g2ext_network_read(IFIX(handle),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(ISVREF(tcp_socket,(SI_Long)5L)),
	    IFIX(ISVREF(tcp_socket,(SI_Long)7L)),(SI_Long)4096L)) : 
	    G2int_ne_eof_value;
    if (IFIX(octets_read_or_status) > (SI_Long)0L) {
	svref_new_value = add(ISVREF(tcp_socket,(SI_Long)7L),
		octets_read_or_status);
	SVREF(tcp_socket,FIX((SI_Long)7L)) = svref_new_value;
	temp = T;
    }
    else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_blocked_value))
	temp = Nil;
    else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_eof_value)) {
	g2int_close_socket(1,tcp_socket);
	temp = Nil;
    }
    else if (FIXNUM_EQ(octets_read_or_status,G2int_ne_error_value)) {
	g2int_close_socket(1,tcp_socket);
	temp = Nil;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* DATA-AVAILABLE-P */
Object g2int_data_available_p(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(52,19);
    return VALUES_1(FIXNUM_GT(ISVREF(tcp_socket,(SI_Long)7L),
	    ISVREF(tcp_socket,(SI_Long)6L)) ? T : Nil);
}

/* MAYBE-READ-BUFFER-FROM-SOCKET */
Object g2int_maybe_read_buffer_from_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(52,20);
    if (ISVREF(tcp_socket,(SI_Long)4L) && IFIX(ISVREF(tcp_socket,
	    (SI_Long)7L)) < (SI_Long)4096L)
	g2int_read_buffer_from_socket(tcp_socket);
    return g2int_data_available_p(tcp_socket);
}

/* PEEK-SOCKET */
Object g2int_peek_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(52,21);
    if (g2int_maybe_read_buffer_from_socket(tcp_socket))
	return VALUES_1(FIX(UBYTE_8_ISAREF_1(ISVREF(tcp_socket,
		(SI_Long)5L),IFIX(ISVREF(tcp_socket,(SI_Long)6L)))));
    else
	return VALUES_1(Nil);
}

/* READ-BYTE-FROM-SOCKET */
Object g2int_read_byte_from_socket(tcp_socket)
    Object tcp_socket;
{
    Object temp, svref_new_value;

    x_note_fn_call(52,22);
    if (g2int_maybe_read_buffer_from_socket(tcp_socket)) {
	temp = FIX(UBYTE_8_ISAREF_1(ISVREF(tcp_socket,(SI_Long)5L),
		IFIX(ISVREF(tcp_socket,(SI_Long)6L))));
	svref_new_value = FIXNUM_ADD1(ISVREF(tcp_socket,(SI_Long)6L));
	SVREF(tcp_socket,FIX((SI_Long)6L)) = svref_new_value;
	if (IFIX(ISVREF(tcp_socket,(SI_Long)6L)) == (SI_Long)4096L) {
	    ISVREF(tcp_socket,(SI_Long)6L) = FIX((SI_Long)0L);
	    ISVREF(tcp_socket,(SI_Long)7L) = FIX((SI_Long)0L);
	}
	return VALUES_1(temp);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

/* READ-FROM-SOCKET */
Object g2int_read_from_socket(tcp_socket)
    Object tcp_socket;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object got_data, temp, schar_arg_2, schar_new_value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_, simple_or_wide_character, thing;
    Declare_special(5);
    Object result;

    x_note_fn_call(52,23);
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
	      got_data = Nil;
	    next_loop:
	      got_data = g2int_maybe_read_buffer_from_socket(tcp_socket);
	      if ( !TRUEP(got_data))
		  goto end_loop;
	      index_1 = IFIX(ISVREF(tcp_socket,(SI_Long)6L));
	      ab_loop_bind_ = IFIX(ISVREF(tcp_socket,(SI_Long)7L));
	    next_loop_1:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop_1;
	      simple_or_wide_character = 
		      UBYTE_8_ISAREF_1(ISVREF(tcp_socket,(SI_Long)5L),index_1);
	      if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		  thing = simple_or_wide_character;
		  g2int_twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
	      }
	      else {
		  if ( 
			  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			  G2int_total_length_of_current_gensym_string))
		      g2int_extend_current_gensym_string(0);
		  temp = G2int_current_gensym_string;
		  schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = 
			  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		  G2int_fill_pointer_for_current_gensym_string = temp;
	      }
	      index_1 = index_1 + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      if (IFIX(ISVREF(tcp_socket,(SI_Long)7L)) != (SI_Long)4096L) {
		  temp = ISVREF(tcp_socket,(SI_Long)7L);
		  SVREF(tcp_socket,FIX((SI_Long)6L)) = temp;
	      }
	      else {
		  ISVREF(tcp_socket,(SI_Long)6L) = FIX((SI_Long)0L);
		  ISVREF(tcp_socket,(SI_Long)7L) = FIX((SI_Long)0L);
	      }
	      goto next_loop;
	    end_loop:;
	      result = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* READ-FROM-SOCKET-UNTIL-CHAR */
Object g2int_read_from_socket_until_char(tcp_socket,end_char)
    Object tcp_socket, end_char;
{
    Object keep_going, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object got_data, char_1, thing, temp, schar_arg_2, schar_new_value, value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(52,24);
    keep_going = T;
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
	      got_data = Nil;
	    next_loop:
	      got_data = g2int_maybe_read_buffer_from_socket(tcp_socket);
	      if ( !(keep_going && got_data))
		  goto end_loop;
	      index_1 = IFIX(ISVREF(tcp_socket,(SI_Long)6L));
	      ab_loop_bind_ = IFIX(ISVREF(tcp_socket,(SI_Long)7L));
	      char_1 = Nil;
	    next_loop_1:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop_1;
	      char_1 = FIX(UBYTE_8_ISAREF_1(ISVREF(tcp_socket,(SI_Long)5L),
		      index_1));
	      if ( !TRUEP(keep_going))
		  goto end_loop_1;
	      if (FIXNUM_EQ(char_1,end_char))
		  keep_going = Nil;
	      if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		  thing = char_1;
		  g2int_twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( 
			  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			  G2int_total_length_of_current_gensym_string))
		      g2int_extend_current_gensym_string(0);
		  temp = G2int_current_gensym_string;
		  schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		  thing = char_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = 
			  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		  G2int_fill_pointer_for_current_gensym_string = temp;
	      }
	      index_1 = index_1 + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      if (index_1 < (SI_Long)4096L)
		  ISVREF(tcp_socket,(SI_Long)6L) = FIX(index_1);
	      else {
		  ISVREF(tcp_socket,(SI_Long)6L) = FIX((SI_Long)0L);
		  ISVREF(tcp_socket,(SI_Long)7L) = FIX((SI_Long)0L);
	      }
	      goto next_loop;
	    end_loop:;
	      value = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(value,keep_going);
}

/* READ-N-CHARS-FROM-SOCKET */
Object g2int_read_n_chars_from_socket(tcp_socket,n_1)
    Object tcp_socket, n_1;
{
    Object remaining, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object got_data, char_1, thing, temp, schar_arg_2, schar_new_value, value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_, ab_loop_repeat_;
    Declare_special(5);

    x_note_fn_call(52,25);
    remaining = n_1;
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
	      got_data = Nil;
	    next_loop:
	      got_data = g2int_maybe_read_buffer_from_socket(tcp_socket);
	      if ( !(IFIX(remaining) > (SI_Long)0L && got_data))
		  goto end_loop;
	      index_1 = IFIX(ISVREF(tcp_socket,(SI_Long)6L));
	      ab_loop_bind_ = IFIX(ISVREF(tcp_socket,(SI_Long)7L));
	      ab_loop_repeat_ = IFIX(remaining);
	      char_1 = Nil;
	    next_loop_1:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop_1;
	      if ( !((SI_Long)0L < ab_loop_repeat_))
		  goto end_loop_1;
	      ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	      char_1 = FIX(UBYTE_8_ISAREF_1(ISVREF(tcp_socket,(SI_Long)5L),
		      index_1));
	      if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		  thing = char_1;
		  g2int_twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( 
			  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
			  G2int_total_length_of_current_gensym_string))
		      g2int_extend_current_gensym_string(0);
		  temp = G2int_current_gensym_string;
		  schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
		  thing = char_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = 
			  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		  G2int_fill_pointer_for_current_gensym_string = temp;
	      }
	      index_1 = index_1 + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      remaining = FIX(IFIX(remaining) - (index_1 - 
		      IFIX(ISVREF(tcp_socket,(SI_Long)6L))));
	      if (index_1 < (SI_Long)4096L)
		  ISVREF(tcp_socket,(SI_Long)6L) = FIX(index_1);
	      else {
		  ISVREF(tcp_socket,(SI_Long)6L) = FIX((SI_Long)0L);
		  ISVREF(tcp_socket,(SI_Long)7L) = FIX((SI_Long)0L);
	      }
	      goto next_loop;
	    end_loop:;
	      value = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(value,remaining);
}

static Object string_constant_4;   /* "Error ~a on socket ~a before accept" */

static Object Qg2int_would_block;  /* would-block */

/* HANDLE-NETWORK-ACCEPT-INTERNALS */
Object g2int_handle_network_accept_internals(listener_socket,new_socket,
	    error_code)
    Object listener_socket, new_socket, error_code;
{
    Object listener_handle, svref_new_value;
    SI_Long new_socket_handle;

    x_note_fn_call(52,26);
    listener_handle = ISVREF(listener_socket,(SI_Long)3L);
    if ( !(listener_handle && FIXNUM_EQ(error_code,
	    G2int_network_status_success)))
	g2int_notify_user_at_console(3,string_constant_4,error_code,
		listener_handle);
    new_socket_handle = g2ext_network_accept(IFIX(listener_handle));
    if (new_socket_handle > (SI_Long)0L) {
	ISVREF(new_socket,(SI_Long)3L) = FIX(new_socket_handle);
	svref_new_value = 
		g2int_network_peer_address_string(FIX(new_socket_handle));
	SVREF(new_socket,FIX((SI_Long)1L)) = svref_new_value;
	g2int_register_socket_to_handle(new_socket,FIX(new_socket_handle));
	return VALUES_1(T);
    }
    else if (new_socket_handle == IFIX(G2int_ne_blocked_value))
	return VALUES_1(Qg2int_would_block);
    else
	return VALUES_1(Nil);
}

/* HANDLE-NETWORK-CLOSE-FOR-TCP-SOCKET */
Object g2int_handle_network_close_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(52,27);
    gensymed_symbol = ISVREF(tcp_socket,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)20L);
    gensymed_symbol_1 = tcp_socket;
    gensymed_symbol_2 = error_code;
    gensymed_symbol_3 = Nil;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3);
    if (ISVREF(tcp_socket,(SI_Long)4L))
	return g2int_close_socket(1,tcp_socket);
    else
	return VALUES_1(Nil);
}

/* CLOSE-SOCKET */
Object g2int_close_socket varargs_1(int, n)
{
    Object tcp_socket;
    Object force;
    Declare_varargs_nonrelocating;

    x_note_fn_call(52,28);
    INIT_ARGS_nonrelocating();
    tcp_socket = REQUIRED_ARG_nonrelocating();
    force = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(tcp_socket,(SI_Long)4L)) {
	g2ext_network_close(IFIX(ISVREF(tcp_socket,(SI_Long)3L)));
	SVREF(tcp_socket,FIX((SI_Long)4L)) = Nil;
	g2int_register_socket_to_handle(Nil,ISVREF(tcp_socket,(SI_Long)3L));
	SVREF(tcp_socket,FIX((SI_Long)3L)) = Nil;
    }
    if (force ||  !TRUEP(g2int_data_available_p(tcp_socket)))
	return g2int_enqueue_tcp_cleanups(tcp_socket);
    else
	return VALUES_1(Nil);
}

/* SOCKET-CLOSE-CLEANUPS */
Object g2int_socket_close_cleanups(tcp_socket)
    Object tcp_socket;
{
    Object thing, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(52,29);
    SVREF(tcp_socket,FIX((SI_Long)2L)) = Nil;
    thing = ISVREF(tcp_socket,(SI_Long)1L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	g2int_reclaim_wide_string(thing);
    SVREF(tcp_socket,FIX((SI_Long)1L)) = Nil;
    gensymed_symbol = ISVREF(tcp_socket,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = tcp_socket;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

static Object Qg2int_socket_close_cleanups;  /* socket-close-cleanups */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* ENQUEUE-TCP-CLEANUPS */
Object g2int_enqueue_tcp_cleanups(tcp_socket)
    Object tcp_socket;
{
    Object schedule_task_qm, current_task_schedule_modify_arg_8;
    Object current_task_schedule_modify_arg_11, old_structure_being_reclaimed;
    Object temp, def_structure_schedule_task_variable, task, ctask, p, v, q;
    Object gensymed_symbol, def_structure_queue_element_variable;
    Object gensymed_symbol_1;
    char g2_p;
    double aref_new_value;

    x_note_fn_call(52,30);
    schedule_task_qm = ISVREF(tcp_socket,(SI_Long)9L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,G2int_current_schedule_task)))) {
	current_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_socket_close_cleanups);
	current_task_schedule_modify_arg_11 = tcp_socket;
	schedule_task_qm = ISVREF(tcp_socket,(SI_Long)9L);
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
	SVREF(task,FIX((SI_Long)7L)) = Qg2int_socket_close_cleanups;
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
	SVREF(tcp_socket,FIX((SI_Long)9L)) = task;
    }
    return VALUES_1(Nil);
}

/* HANDLE-G2-RESET-FOR-TCP-SOCKET */
Object g2int_handle_g2_reset_for_tcp_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(52,31);
    return g2int_close_socket(2,tcp_socket,T);
}

/* C-GET-PEER-ADDRESS-STRING */
Object g2int_c_get_peer_address_string(socket_number,buffer,max_1)
    Object socket_number, buffer, max_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(52,32);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2ext_get_peer_address_string(IFIX(socket_number),ISTRING(temp),
	    IFIX(max_1));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* C-GET-PEER-HOSTNAME */
Object g2int_c_get_peer_hostname(socket_number,buffer,max_1)
    Object socket_number, buffer, max_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(52,33);
    gensymed_symbol = g2int_copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2ext_get_peer_hostname(IFIX(socket_number),ISTRING(temp),IFIX(max_1));
    if (gensymed_symbol)
	g2int_reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* NETWORK-PEER-ADDRESS-STRING */
Object g2int_network_peer_address_string(handle)
    Object handle;
{
    Object buf, temp;

    x_note_fn_call(52,34);
    buf = 
	    g2int_obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    g2int_c_get_peer_address_string(FIX(g2ext_network_get_fd_from_handle(IFIX(handle))),
	    buf,FIX((SI_Long)4096L));
    temp = g2int_copy_null_terminated_string_as_text_string(buf);
    g2int_reclaim_gensym_string(buf);
    return VALUES_1(temp);
}

/* NETWORK-PEER-NAME */
Object g2int_network_peer_name(handle)
    Object handle;
{
    Object buf, temp;

    x_note_fn_call(52,35);
    buf = 
	    g2int_obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    g2int_c_get_peer_hostname(FIX(g2ext_network_get_fd_from_handle(IFIX(handle))),
	    buf,FIX((SI_Long)4096L));
    temp = g2int_copy_null_terminated_string_as_text_string(buf);
    g2int_reclaim_gensym_string(buf);
    return VALUES_1(temp);
}

void socket1_INIT()
{
    Object temp, reclaim_structure_for_tcp_socket;
    Object handle_network_connect_for_tcp_socket;
    Object reclaim_structure_for_socket_output_buffer;
    Object handle_write_event_for_tcp_socket, handle_read_event_for_tcp_socket;
    Object handle_network_close_for_tcp_socket, handle_g2_reset_for_tcp_socket;
    Object Qg2int_tcp_socket, Qg2int_handle_g2_reset, AB_package;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qg2int_handle_network_close;
    Object Qg2int_handle_read_event, Qg2int_handle_write_event;
    Object Qg2int_socket_output_buffer, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_socket_output_buffer_count;
    Object Qg2int_chain_of_available_socket_output_buffers;
    Object Qg2int_type_description_of_type, string_constant_6;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object Qg2int_handle_network_connect, Qg2int_tcp_socket_count;
    Object Qg2int_chain_of_available_tcp_sockets, string_constant_5;

    x_note_fn_call(52,36);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_tcp_socket_g2_struct = 
	    STATIC_SYMBOL("TCP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_tcp_socket = STATIC_SYMBOL("TCP-SOCKET",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    Qg2int_tcp_socket,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_tcp_socket,
	    Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_tcp_socket == UNBOUND)
	G2int_the_type_description_of_tcp_socket = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8l831-y1o831-y83Jy8m8k1l83Jy0000001l1m8o83Jykuk0k0");
    temp = G2int_the_type_description_of_tcp_socket;
    G2int_the_type_description_of_tcp_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_5));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    G2int_the_type_description_of_tcp_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_tcp_socket,
	    G2int_the_type_description_of_tcp_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_tcp_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TCP-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_tcp_sockets,
	    G2int_chain_of_available_tcp_sockets);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_tcp_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_tcp_socket_count = STATIC_SYMBOL("TCP-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_tcp_socket_count,G2int_tcp_socket_count);
    g2int_record_system_variable(Qg2int_tcp_socket_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_tcp_socket,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_tcp_socket,reclaim_structure_for_tcp_socket);
    string_constant = STATIC_STRING("TCP_IP:~a:~a");
    string_constant_1 = STATIC_STRING("~a");
    Qg2int_handle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    handle_network_connect_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_handle_network_connect_for_tcp_socket,
	    NIL,FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_network_connect,
	    Qg2int_tcp_socket,handle_network_connect_for_tcp_socket);
    Qg2_defstruct_structure_name_socket_output_buffer_g2_struct = 
	    STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_socket_output_buffer = STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    Qg2int_socket_output_buffer,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_socket_output_buffer,
	    Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_socket_output_buffer == UNBOUND)
	G2int_the_type_description_of_socket_output_buffer = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l830xy1n830xy8m8k1l8m0000000kqk0k0");
    temp = G2int_the_type_description_of_socket_output_buffer;
    G2int_the_type_description_of_socket_output_buffer = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_6));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    G2int_the_type_description_of_socket_output_buffer,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_socket_output_buffer,
	    G2int_the_type_description_of_socket_output_buffer,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_socket_output_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SOCKET-OUTPUT-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_socket_output_buffers,
	    G2int_chain_of_available_socket_output_buffers);
    g2int_record_system_variable(Qg2int_chain_of_available_socket_output_buffers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_socket_output_buffer_count = 
	    STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_socket_output_buffer_count,
	    G2int_socket_output_buffer_count);
    g2int_record_system_variable(Qg2int_socket_output_buffer_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_socket_output_buffer = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_socket_output_buffer,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_socket_output_buffer,
	    reclaim_structure_for_socket_output_buffer);
    Qg2int_blocked = STATIC_SYMBOL("BLOCKED",AB_package);
    string_constant_2 = STATIC_STRING("Error sending socket buffer");
    string_constant_3 = 
	    STATIC_STRING("ERROR: Unrecognized value type in network I/O.  Some data may be dropped.");
    Qg2int_handle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    handle_write_event_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_handle_write_event_for_tcp_socket,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_write_event,
	    Qg2int_tcp_socket,handle_write_event_for_tcp_socket);
    Qg2int_handle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    handle_read_event_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_handle_read_event_for_tcp_socket,NIL,
	    FALSE,3,3);
    g2int_record_direct_structure_method(Qg2int_handle_read_event,
	    Qg2int_tcp_socket,handle_read_event_for_tcp_socket);
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_4 = STATIC_STRING("Error ~a on socket ~a before accept");
    Qg2int_would_block = STATIC_SYMBOL("WOULD-BLOCK",AB_package);
    Qg2int_handle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",
	    AB_package);
    handle_network_close_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_handle_network_close_for_tcp_socket,NIL,
	    FALSE,2,2);
    g2int_record_direct_structure_method(Qg2int_handle_network_close,
	    Qg2int_tcp_socket,handle_network_close_for_tcp_socket);
    Qg2int_socket_close_cleanups = STATIC_SYMBOL("SOCKET-CLOSE-CLEANUPS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_socket_close_cleanups,
	    STATIC_FUNCTION(g2int_socket_close_cleanups,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_handle_g2_reset = STATIC_SYMBOL("HANDLE-G2-RESET",AB_package);
    handle_g2_reset_for_tcp_socket = 
	    STATIC_FUNCTION(g2int_handle_g2_reset_for_tcp_socket,NIL,FALSE,
	    1,1);
    g2int_record_direct_structure_method(Qg2int_handle_g2_reset,
	    Qg2int_tcp_socket,handle_g2_reset_for_tcp_socket);
}
