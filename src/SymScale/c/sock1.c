/* sock1.c
 * Input file:  socket1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sock1.h"


Object The_type_description_of_tcp_socket = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_tcp_sockets, Qchain_of_available_tcp_sockets);

DEFINE_VARIABLE_WITH_SYMBOL(Tcp_socket_count, Qtcp_socket_count);

Object Chain_of_available_tcp_sockets_vector = UNBOUND;

/* TCP-SOCKET-STRUCTURE-MEMORY-USAGE */
Object tcp_socket_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(240,0);
    temp = Tcp_socket_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)10L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TCP-SOCKET-COUNT */
Object outstanding_tcp_socket_count()
{
    Object def_structure_tcp_socket_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(240,1);
    gensymed_symbol = IFIX(Tcp_socket_count);
    def_structure_tcp_socket_variable = Chain_of_available_tcp_sockets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_tcp_socket_variable))
	goto end_loop;
    def_structure_tcp_socket_variable = 
	    ISVREF(def_structure_tcp_socket_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TCP-SOCKET-1 */
Object reclaim_tcp_socket_1(tcp_socket)
    Object tcp_socket;
{
    Object structure_being_reclaimed, thing, vector_1, gensymed_symbol, temp;
    Object svref_arg_2;
    Declare_special(2);

    x_note_fn_call(240,2);
    inline_note_reclaim_cons(tcp_socket,Nil);
    structure_being_reclaimed = tcp_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      thing = ISVREF(tcp_socket,(SI_Long)1L);
      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	  reclaim_wide_string(thing);
      SVREF(tcp_socket,FIX((SI_Long)1L)) = Nil;
      vector_1 = ISVREF(tcp_socket,(SI_Long)5L);
      if (vector_1)
	  reclaim_variable_fill_icp_buffer(vector_1);
      SVREF(tcp_socket,FIX((SI_Long)5L)) = Nil;
      reclaim_if_socket_buffer(ISVREF(tcp_socket,(SI_Long)8L));
      SVREF(tcp_socket,FIX((SI_Long)8L)) = Nil;
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(tcp_socket,(SI_Long)9L);
      if (CAS_SVREF(tcp_socket,(SI_Long)9L,gensymed_symbol,Nil)) {
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
      SVREF(tcp_socket,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_tcp_sockets_vector,
	    IFIX(Current_thread_index));
    SVREF(tcp_socket,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_tcp_sockets_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = tcp_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TCP-SOCKET */
Object reclaim_structure_for_tcp_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(240,3);
    return reclaim_tcp_socket_1(tcp_socket);
}

static Object Qg2_defstruct_structure_name_tcp_socket_g2_struct;  /* g2-defstruct-structure-name::tcp-socket-g2-struct */

/* MAKE-PERMANENT-TCP-SOCKET-STRUCTURE-INTERNAL */
Object make_permanent_tcp_socket_structure_internal()
{
    Object def_structure_tcp_socket_variable, defstruct_g2_tcp_socket_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(240,4);
    def_structure_tcp_socket_variable = Nil;
    atomic_incff_symval(Qtcp_socket_count,FIX((SI_Long)1L));
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
Object make_tcp_socket_1()
{
    Object def_structure_tcp_socket_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(240,5);
    def_structure_tcp_socket_variable = 
	    ISVREF(Chain_of_available_tcp_sockets_vector,
	    IFIX(Current_thread_index));
    if (def_structure_tcp_socket_variable) {
	svref_arg_1 = Chain_of_available_tcp_sockets_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_tcp_socket_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_tcp_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tcp_socket_g2_struct;
    }
    else
	def_structure_tcp_socket_variable = 
		make_permanent_tcp_socket_structure_internal();
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

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* CONNECT-SOCKET */
Object connect_socket(socket_1,host,port,secure_qm)
    Object socket_1, host, port, secure_qm;
{
    Object network_pathname, port_string, handle, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(240,6);
    network_pathname = tformat_gensym_string(3,string_constant,host,port);
    port_string = tformat_gensym_string(2,string_constant_1,port);
    handle = network_connect(4,network_pathname,host,port_string,secure_qm);
    reclaim_gensym_string(network_pathname);
    reclaim_gensym_string(port_string);
    if ( !(IFIX(handle) < (SI_Long)0L)) {
	svref_new_value = copy_text_string(host);
	SVREF(socket_1,FIX((SI_Long)1L)) = svref_new_value;
	SVREF(socket_1,FIX((SI_Long)2L)) = port;
	SVREF(socket_1,FIX((SI_Long)3L)) = handle;
	register_socket_to_handle(socket_1,handle);
	if ( !((SI_Long)0L == ne_connected_p(IFIX(handle)))) {
	    gensymed_symbol = ISVREF(socket_1,(SI_Long)0L);
	    gensymed_symbol = 
		    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qtype_description_of_unique_type_name_of_gensym_structure),
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
Object handle_network_connect_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    x_note_fn_call(240,7);
    return VALUES_1(Nil);
}

/* C-NETWORK-WRITE-STRING */
Object c_network_write_string(handle,buffer,offset,length_1)
    Object handle, buffer, offset, length_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(240,8);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    temp = FIX(g2ext_network_write(IFIX(handle),ISTRING(temp),IFIX(offset),
	    IFIX(length_1)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

Object The_type_description_of_socket_output_buffer = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_socket_output_buffers, Qchain_of_available_socket_output_buffers);

DEFINE_VARIABLE_WITH_SYMBOL(Socket_output_buffer_count, Qsocket_output_buffer_count);

Object Chain_of_available_socket_output_buffers_vector = UNBOUND;

/* SOCKET-OUTPUT-BUFFER-STRUCTURE-MEMORY-USAGE */
Object socket_output_buffer_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(240,9);
    temp = Socket_output_buffer_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SOCKET-OUTPUT-BUFFER-COUNT */
Object outstanding_socket_output_buffer_count()
{
    Object def_structure_socket_output_buffer_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(240,10);
    gensymed_symbol = IFIX(Socket_output_buffer_count);
    def_structure_socket_output_buffer_variable = 
	    Chain_of_available_socket_output_buffers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_socket_output_buffer_variable))
	goto end_loop;
    def_structure_socket_output_buffer_variable = 
	    ISVREF(def_structure_socket_output_buffer_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SOCKET-OUTPUT-BUFFER-1 */
Object reclaim_socket_output_buffer_1(socket_output_buffer)
    Object socket_output_buffer;
{
    Object structure_being_reclaimed, vector_1, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(240,11);
    inline_note_reclaim_cons(socket_output_buffer,Nil);
    structure_being_reclaimed = socket_output_buffer;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_socket_buffer_data(ISVREF(socket_output_buffer,(SI_Long)1L));
      SVREF(socket_output_buffer,FIX((SI_Long)1L)) = Nil;
      vector_1 = ISVREF(socket_output_buffer,(SI_Long)3L);
      if (vector_1)
	  reclaim_variable_fill_icp_buffer(vector_1);
      SVREF(socket_output_buffer,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_socket_output_buffers_vector,
	    IFIX(Current_thread_index));
    SVREF(socket_output_buffer,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_socket_output_buffers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = socket_output_buffer;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SOCKET-OUTPUT-BUFFER */
Object reclaim_structure_for_socket_output_buffer(socket_output_buffer)
    Object socket_output_buffer;
{
    x_note_fn_call(240,12);
    return reclaim_socket_output_buffer_1(socket_output_buffer);
}

static Object Qg2_defstruct_structure_name_socket_output_buffer_g2_struct;  /* g2-defstruct-structure-name::socket-output-buffer-g2-struct */

/* MAKE-PERMANENT-SOCKET-OUTPUT-BUFFER-STRUCTURE-INTERNAL */
Object make_permanent_socket_output_buffer_structure_internal()
{
    Object def_structure_socket_output_buffer_variable;
    Object defstruct_g2_socket_output_buffer_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(240,13);
    def_structure_socket_output_buffer_variable = Nil;
    atomic_incff_symval(Qsocket_output_buffer_count,FIX((SI_Long)1L));
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
Object make_socket_output_buffer_1()
{
    Object def_structure_socket_output_buffer_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(240,14);
    def_structure_socket_output_buffer_variable = 
	    ISVREF(Chain_of_available_socket_output_buffers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_socket_output_buffer_variable) {
	svref_arg_1 = Chain_of_available_socket_output_buffers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_socket_output_buffer_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_socket_output_buffer_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_socket_output_buffer_g2_struct;
    }
    else
	def_structure_socket_output_buffer_variable = 
		make_permanent_socket_output_buffer_structure_internal();
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
Object reclaim_socket_buffer_data(data)
    Object data;
{
    Object temp;

    x_note_fn_call(240,15);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(data) != (SI_Long)0L)
	temp = reclaim_text_string(data);
    else if (CONSP(data) && EQ(M_CDR(data),Qsequence))
	temp = reclaim_evaluation_sequence(data);
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* RECLAIM-IF-SOCKET-BUFFER */
Object reclaim_if_socket_buffer(socket_buffer)
    Object socket_buffer;
{
    Object temp;

    x_note_fn_call(240,16);
    temp = socket_buffer ? reclaim_socket_output_buffer_1(socket_buffer) : Nil;
    return VALUES_1(temp);
}

/* ADD-BUFFER-TO-SOCKET */
Object add_buffer_to_socket(sob,tcp_socket)
    Object sob, tcp_socket;
{
    Object prev;

    x_note_fn_call(240,17);
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

static Object Qblocked;            /* blocked */

/* WRITE-TO-SOCKET */
Object write_to_socket(tcp_socket,string_1)
    Object tcp_socket, string_1;
{
    Object length_1, bytes_written, temp, sob, svref_new_value;

    x_note_fn_call(240,18);
    length_1 = text_string_length(string_1);
    bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
	    c_network_write_string(ISVREF(tcp_socket,(SI_Long)3L),string_1,
	    FIX((SI_Long)0L),length_1) : FIX((SI_Long)-1L);
    temp = FIXNUM_EQ(bytes_written,length_1) ? T : Nil;
    if (temp);
    else if (IFIX(bytes_written) >= (SI_Long)0L) {
	sob = make_socket_output_buffer_1();
	svref_new_value = copy_text_string(string_1);
	SVREF(sob,FIX((SI_Long)1L)) = svref_new_value;
	SVREF(sob,FIX((SI_Long)4L)) = bytes_written;
	add_buffer_to_socket(sob,tcp_socket);
	temp = Qblocked;
    }
    else
	temp = Qerror;
    return VALUES_1(temp);
}

static Object Qwrite_bytes_to_socket;  /* write-bytes-to-socket */

/* WRITE-BYTES-TO-SOCKET */
Object write_bytes_to_socket(tcp_socket,sequence)
    Object tcp_socket, sequence;
{
    Object tag_temp, buffer, octet, ab_loop_iter_flag_, sob, length_1;
    Object new_sequence;
    SI_Long s_index, ab_loop_bind_, stop, b_index, gensymed_symbol;
    SI_Long bytes_written, svref_new_value;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(240,19);
    SAVE_STACK();
    tag_temp = UNIQUE_TAG(Qwrite_bytes_to_socket);
    if (PUSH_CATCH(tag_temp,1)) {
	buffer = make_variable_fill_icp_buffer();
	if (PUSH_UNWIND_PROTECT(0)) {
	    s_index = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),
		    (SI_Long)1L)));
	    octet = Nil;
	    stop = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L))) 
		    - (SI_Long)1L;
	    b_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (s_index >= ab_loop_bind_)
		goto end_loop;
	    octet = evaluation_sequence_aref(sequence,FIX(s_index));
	    if ( !TRUEP(ab_loop_iter_flag_))
		b_index = b_index + (SI_Long)1L;
	    gensymed_symbol = IFIX(octet) & (SI_Long)255L;
	    UBYTE_8_ISASET_1(buffer,b_index,gensymed_symbol);
	    if (b_index == (SI_Long)4096L - (SI_Long)1L || s_index == stop) {
		bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
			g2ext_network_write(IFIX(ISVREF(tcp_socket,
			(SI_Long)3L)),
			UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),(SI_Long)0L,
			b_index + (SI_Long)1L) : (SI_Long)-1L;
		if (bytes_written == b_index + (SI_Long)1L)
		    b_index = (SI_Long)-1L;
		else if (bytes_written >= (SI_Long)0L) {
		    sob = make_socket_output_buffer_1();
		    length_1 = FIXNUM_SUB1(ISVREF(M_CAR(sequence),
			    (SI_Long)1L));
		    new_sequence = 
			    allocate_empty_evaluation_sequence(length_1);
		    copy_evaluation_sequence_elements(sequence,
			    FIX((SI_Long)0L),length_1,new_sequence,
			    FIX((SI_Long)0L));
		    SVREF(sob,FIX((SI_Long)1L)) = new_sequence;
		    svref_new_value = s_index - (b_index - bytes_written);
		    ISVREF(sob,(SI_Long)4L) = FIX(svref_new_value);
		    add_buffer_to_socket(sob,tcp_socket);
		    result = VALUES_1(Qblocked);
		    THROW(tag_temp,result);
		}
		else {
		    result = VALUES_1(Qerror);
		    THROW(tag_temp,result);
		}
	    }
	    ab_loop_iter_flag_ = Nil;
	    s_index = s_index + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    SAVE_VALUES(VALUES_1(Qnil));
	}
	POP_UNWIND_PROTECT(0);
	reclaim_variable_fill_icp_buffer(buffer);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object Qtry_to_send_socket_sequence;  /* try-to-send-socket-sequence */

/* TRY-TO-SEND-SOCKET-SEQUENCE */
Object try_to_send_socket_sequence(tcp_socket)
    Object tcp_socket;
{
    Object tag_temp, sob, sequence, buffer, octet, ab_loop_iter_flag_;
    Object svref_new_value_1;
    SI_Long s_index, ab_loop_bind_, stop, b_index, gensymed_symbol;
    SI_Long bytes_written, svref_new_value;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(240,20);
    SAVE_STACK();
    tag_temp = UNIQUE_TAG(Qtry_to_send_socket_sequence);
    if (PUSH_CATCH(tag_temp,1)) {
	sob = ISVREF(tcp_socket,(SI_Long)8L);
	sequence = ISVREF(sob,(SI_Long)1L);
	buffer = make_variable_fill_icp_buffer();
	if (PUSH_UNWIND_PROTECT(0)) {
	    s_index = IFIX(ISVREF(sob,(SI_Long)4L));
	    ab_loop_bind_ = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),
		    (SI_Long)1L)));
	    octet = Nil;
	    stop = IFIX(FIXNUM_SUB1(ISVREF(M_CAR(sequence),(SI_Long)1L))) 
		    - (SI_Long)1L;
	    b_index = (SI_Long)0L;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (s_index >= ab_loop_bind_)
		goto end_loop;
	    octet = evaluation_sequence_aref(sequence,FIX(s_index));
	    if ( !TRUEP(ab_loop_iter_flag_))
		b_index = b_index + (SI_Long)1L;
	    gensymed_symbol = IFIX(octet) & (SI_Long)255L;
	    UBYTE_8_ISASET_1(buffer,b_index,gensymed_symbol);
	    if (b_index == (SI_Long)4096L - (SI_Long)1L || s_index == stop) {
		bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
			g2ext_network_write(IFIX(ISVREF(tcp_socket,
			(SI_Long)3L)),
			UBYTE_16_SARRAY_TO_USHORT_PTR(buffer),(SI_Long)0L,
			b_index + (SI_Long)1L) : (SI_Long)-1L;
		if (bytes_written == b_index + (SI_Long)1L)
		    b_index = (SI_Long)-1L;
		else if (bytes_written >= (SI_Long)0L) {
		    svref_new_value = s_index - (b_index - bytes_written);
		    ISVREF(sob,(SI_Long)4L) = FIX(svref_new_value);
		    result = VALUES_1(Qblocked);
		    THROW(tag_temp,result);
		}
		else {
		    result = VALUES_1(Qerror);
		    THROW(tag_temp,result);
		}
	    }
	    ab_loop_iter_flag_ = Nil;
	    s_index = s_index + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	POP_UNWIND_PROTECT(0);
	reclaim_variable_fill_icp_buffer(buffer);
	CONTINUE_UNWINDING(0);
	svref_new_value_1 = ISVREF(sob,(SI_Long)5L);
	SVREF(tcp_socket,FIX((SI_Long)8L)) = svref_new_value_1;
	reclaim_socket_output_buffer_1(sob);
	result = try_to_send_socket_buffer(tcp_socket);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object string_constant_2;   /* "Error sending socket buffer" */

static Object string_constant_3;   /* "ERROR: Unrecognized value type in network I/O.  Some data may be dropped." */

/* TRY-TO-SEND-SOCKET-BUFFER */
Object try_to_send_socket_buffer(tcp_socket)
    Object tcp_socket;
{
    Object sob, temp, thing, string_1, current, length_1, bytes_written;
    Object svref_new_value, incff_1_arg, item_or_evaluation_value;

    x_note_fn_call(240,21);
    sob = ISVREF(tcp_socket,(SI_Long)8L);
    temp =  !TRUEP(sob) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	thing = ISVREF(sob,(SI_Long)1L);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L) {
	    string_1 = ISVREF(sob,(SI_Long)1L);
	    current = ISVREF(sob,(SI_Long)4L);
	    length_1 = FIXNUM_MINUS(text_string_length(string_1),current);
	    bytes_written = ISVREF(tcp_socket,(SI_Long)3L) ? 
		    c_network_write_string(ISVREF(tcp_socket,(SI_Long)3L),
		    string_1,current,length_1) : FIX((SI_Long)-1L);
	    if (FIXNUM_EQ(bytes_written,length_1)) {
		svref_new_value = ISVREF(sob,(SI_Long)5L);
		SVREF(tcp_socket,FIX((SI_Long)8L)) = svref_new_value;
		reclaim_socket_output_buffer_1(sob);
		return try_to_send_socket_buffer(tcp_socket);
	    }
	    else if (IFIX(bytes_written) >= (SI_Long)0L) {
		incff_1_arg = bytes_written;
		svref_new_value = FIXNUM_ADD(ISVREF(sob,(SI_Long)4L),
			incff_1_arg);
		return VALUES_1(SVREF(sob,FIX((SI_Long)4L)) = svref_new_value);
	    }
	    else
		return notify_user_at_console(1,string_constant_2);
	}
	else {
	    item_or_evaluation_value = ISVREF(sob,(SI_Long)1L);
	    if (CONSP(item_or_evaluation_value) && 
		    EQ(M_CDR(item_or_evaluation_value),Qsequence))
		return try_to_send_socket_sequence(tcp_socket);
	    else {
		notify_user_at_console(1,string_constant_3);
		svref_new_value = ISVREF(sob,(SI_Long)5L);
		SVREF(tcp_socket,FIX((SI_Long)8L)) = svref_new_value;
		reclaim_socket_output_buffer_1(sob);
		return try_to_send_socket_buffer(tcp_socket);
	    }
	}
    }
}

/* HANDLE-WRITE-EVENT-FOR-TCP-SOCKET */
Object handle_write_event_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    x_note_fn_call(240,22);
    try_to_send_socket_buffer(tcp_socket);
    return VALUES_1(Nil);
}

/* HANDLE-READ-EVENT-FOR-TCP-SOCKET */
Object handle_read_event_for_tcp_socket(tcp_socket,error_code,block_p)
    Object tcp_socket, error_code, block_p;
{
    x_note_fn_call(240,23);
    return VALUES_1(Nil);
}

/* READ-BUFFER-FROM-SOCKET */
Object read_buffer_from_socket(tcp_socket)
    Object tcp_socket;
{
    Object svref_new_value, octets_read_or_status, handle, temp;

    x_note_fn_call(240,24);
    if ( !TRUEP(ISVREF(tcp_socket,(SI_Long)5L))) {
	svref_new_value = make_variable_fill_icp_buffer();
	SVREF(tcp_socket,FIX((SI_Long)5L)) = svref_new_value;
    }
    octets_read_or_status = Nil;
    handle = ISVREF(tcp_socket,(SI_Long)3L);
    octets_read_or_status = handle ? FIX(g2ext_network_read(IFIX(handle),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(ISVREF(tcp_socket,(SI_Long)5L)),
	    IFIX(ISVREF(tcp_socket,(SI_Long)7L)),(SI_Long)4096L)) : 
	    Ne_eof_value;
    if (IFIX(octets_read_or_status) > (SI_Long)0L) {
	svref_new_value = add(ISVREF(tcp_socket,(SI_Long)7L),
		octets_read_or_status);
	SVREF(tcp_socket,FIX((SI_Long)7L)) = svref_new_value;
	temp = T;
    }
    else if (FIXNUM_EQ(octets_read_or_status,Ne_blocked_value))
	temp = Nil;
    else if (FIXNUM_EQ(octets_read_or_status,Ne_eof_value)) {
	close_socket(1,tcp_socket);
	temp = Nil;
    }
    else if (FIXNUM_EQ(octets_read_or_status,Ne_error_value)) {
	close_socket(1,tcp_socket);
	temp = Nil;
    }
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* DATA-AVAILABLE-P */
Object data_available_p(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(240,25);
    return VALUES_1(FIXNUM_GT(ISVREF(tcp_socket,(SI_Long)7L),
	    ISVREF(tcp_socket,(SI_Long)6L)) ? T : Nil);
}

/* MAYBE-READ-BUFFER-FROM-SOCKET */
Object maybe_read_buffer_from_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(240,26);
    if (ISVREF(tcp_socket,(SI_Long)4L) && IFIX(ISVREF(tcp_socket,
	    (SI_Long)7L)) < (SI_Long)4096L)
	read_buffer_from_socket(tcp_socket);
    return data_available_p(tcp_socket);
}

/* PEEK-SOCKET */
Object peek_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(240,27);
    if (maybe_read_buffer_from_socket(tcp_socket))
	return VALUES_1(FIX(UBYTE_8_ISAREF_1(ISVREF(tcp_socket,
		(SI_Long)5L),IFIX(ISVREF(tcp_socket,(SI_Long)6L)))));
    else
	return VALUES_1(Nil);
}

/* READ-BYTE-FROM-SOCKET */
Object read_byte_from_socket(tcp_socket)
    Object tcp_socket;
{
    Object temp, svref_new_value;

    x_note_fn_call(240,28);
    if (maybe_read_buffer_from_socket(tcp_socket)) {
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

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* READ-FROM-SOCKET */
Object read_from_socket(tcp_socket)
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

    x_note_fn_call(240,29);
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
	      got_data = Nil;
	    next_loop:
	      got_data = maybe_read_buffer_from_socket(tcp_socket);
	      if ( !TRUEP(got_data))
		  goto end_loop;
	      index_1 = IFIX(ISVREF(tcp_socket,(SI_Long)6L));
	      ab_loop_bind_ = IFIX(ISVREF(tcp_socket,(SI_Long)7L));
	    next_loop_1:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop_1;
	      simple_or_wide_character = 
		      UBYTE_8_ISAREF_1(ISVREF(tcp_socket,(SI_Long)5L),index_1);
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			  CHAR_CODE(FIX(thing)) : FIX(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
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
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* READ-FROM-SOCKET-UNTIL-CHAR */
Object read_from_socket_until_char(tcp_socket,end_char)
    Object tcp_socket, end_char;
{
    Object keep_going, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object got_data, char_1, thing, temp, schar_arg_2, schar_new_value, value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(240,30);
    keep_going = T;
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
	      got_data = Nil;
	    next_loop:
	      got_data = maybe_read_buffer_from_socket(tcp_socket);
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
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = char_1;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = char_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
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
	      value = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(value,keep_going);
}

/* READ-N-CHARS-FROM-SOCKET */
Object read_n_chars_from_socket(tcp_socket,n_1)
    Object tcp_socket, n_1;
{
    Object remaining, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object got_data, char_1, thing, temp, schar_arg_2, schar_new_value, value;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_, ab_loop_repeat_;
    Declare_special(5);

    x_note_fn_call(240,31);
    remaining = n_1;
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
	      got_data = Nil;
	    next_loop:
	      got_data = maybe_read_buffer_from_socket(tcp_socket);
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
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = char_1;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = char_1;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
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
	      value = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(value,remaining);
}

static Object string_constant_4;   /* "Error ~a on socket ~a before accept" */

static Object Qwould_block;        /* would-block */

/* HANDLE-NETWORK-ACCEPT-INTERNALS */
Object handle_network_accept_internals(listener_socket,new_socket,error_code)
    Object listener_socket, new_socket, error_code;
{
    Object listener_handle, svref_new_value;
    SI_Long new_socket_handle;

    x_note_fn_call(240,32);
    listener_handle = ISVREF(listener_socket,(SI_Long)3L);
    if ( !(listener_handle && FIXNUM_EQ(error_code,Network_status_success)))
	notify_user_at_console(3,string_constant_4,error_code,listener_handle);
    new_socket_handle = g2ext_network_accept(IFIX(listener_handle));
    if (new_socket_handle > (SI_Long)0L) {
	ISVREF(new_socket,(SI_Long)3L) = FIX(new_socket_handle);
	svref_new_value = network_peer_address_string(FIX(new_socket_handle));
	SVREF(new_socket,FIX((SI_Long)1L)) = svref_new_value;
	register_socket_to_handle(new_socket,FIX(new_socket_handle));
	return VALUES_1(T);
    }
    else if (new_socket_handle == IFIX(Ne_blocked_value))
	return VALUES_1(Qwould_block);
    else
	return VALUES_1(Nil);
}

/* HANDLE-NETWORK-CLOSE-FOR-TCP-SOCKET */
Object handle_network_close_for_tcp_socket(tcp_socket,error_code)
    Object tcp_socket, error_code;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3;

    x_note_fn_call(240,33);
    gensymed_symbol = ISVREF(tcp_socket,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)20L);
    gensymed_symbol_1 = tcp_socket;
    gensymed_symbol_2 = error_code;
    gensymed_symbol_3 = Nil;
    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3);
    if (ISVREF(tcp_socket,(SI_Long)4L))
	return close_socket(1,tcp_socket);
    else
	return VALUES_1(Nil);
}

/* CLOSE-SOCKET */
Object close_socket varargs_1(int, n)
{
    Object tcp_socket;
    Object force;
    Declare_varargs_nonrelocating;

    x_note_fn_call(240,34);
    INIT_ARGS_nonrelocating();
    tcp_socket = REQUIRED_ARG_nonrelocating();
    force = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (ISVREF(tcp_socket,(SI_Long)4L)) {
	g2ext_network_close(IFIX(ISVREF(tcp_socket,(SI_Long)3L)));
	SVREF(tcp_socket,FIX((SI_Long)4L)) = Nil;
	register_socket_to_handle(Nil,ISVREF(tcp_socket,(SI_Long)3L));
	SVREF(tcp_socket,FIX((SI_Long)3L)) = Nil;
    }
    if (force ||  !TRUEP(data_available_p(tcp_socket)))
	return enqueue_tcp_cleanups(tcp_socket);
    else
	return VALUES_1(Nil);
}

/* SOCKET-CLOSE-CLEANUPS */
Object socket_close_cleanups(tcp_socket)
    Object tcp_socket;
{
    Object thing, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(240,35);
    SVREF(tcp_socket,FIX((SI_Long)2L)) = Nil;
    thing = ISVREF(tcp_socket,(SI_Long)1L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    SVREF(tcp_socket,FIX((SI_Long)1L)) = Nil;
    gensymed_symbol = ISVREF(tcp_socket,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = tcp_socket;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qsocket_close_cleanups;  /* socket-close-cleanups */

/* ENQUEUE-TCP-CLEANUPS */
Object enqueue_tcp_cleanups(tcp_socket)
    Object tcp_socket;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(240,36);
    schedule_task_qm = ISVREF(tcp_socket,(SI_Long)9L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(tcp_socket,(SI_Long)9L);
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
	SVREF(task,FIX((SI_Long)7L)) = Qsocket_close_cleanups;
	temp = SYMBOL_FUNCTION(Qsocket_close_cleanups);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = tcp_socket;
	new_1 = task;
	if (CAS_SVREF(tcp_socket,(SI_Long)9L,old,new_1)) {
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

/* HANDLE-G2-RESET-FOR-TCP-SOCKET */
Object handle_g2_reset_for_tcp_socket(tcp_socket)
    Object tcp_socket;
{
    x_note_fn_call(240,37);
    return close_socket(2,tcp_socket,T);
}

/* C-GET-PEER-ADDRESS-STRING */
Object c_get_peer_address_string(socket_number,buffer,max_1)
    Object socket_number, buffer, max_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(240,38);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2ext_get_peer_address_string(IFIX(socket_number),ISTRING(temp),
	    IFIX(max_1));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* C-GET-PEER-HOSTNAME */
Object c_get_peer_hostname(socket_number,buffer,max_1)
    Object socket_number, buffer, max_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(240,39);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2ext_get_peer_hostname(IFIX(socket_number),ISTRING(temp),IFIX(max_1));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* NETWORK-PEER-ADDRESS-STRING */
Object network_peer_address_string(handle)
    Object handle;
{
    Object buf, temp;

    x_note_fn_call(240,40);
    buf = obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    c_get_peer_address_string(FIX(g2ext_network_get_fd_from_handle(IFIX(handle))),
	    buf,FIX((SI_Long)4096L));
    temp = copy_null_terminated_string_as_text_string(buf);
    reclaim_gensym_string(buf);
    return VALUES_1(temp);
}

/* NETWORK-PEER-NAME */
Object network_peer_name(handle)
    Object handle;
{
    Object buf, temp;

    x_note_fn_call(240,41);
    buf = obtain_simple_gensym_string_of_quantized_length(FIX((SI_Long)4096L));
    c_get_peer_hostname(FIX(g2ext_network_get_fd_from_handle(IFIX(handle))),
	    buf,FIX((SI_Long)4096L));
    temp = copy_null_terminated_string_as_text_string(buf);
    reclaim_gensym_string(buf);
    return VALUES_1(temp);
}

void socket1_INIT()
{
    Object temp, reclaim_structure_for_tcp_socket_1;
    Object handle_network_connect_for_tcp_socket_1;
    Object reclaim_structure_for_socket_output_buffer_1;
    Object handle_write_event_for_tcp_socket_1;
    Object handle_read_event_for_tcp_socket_1;
    Object handle_network_close_for_tcp_socket_1;
    Object handle_g2_reset_for_tcp_socket_1;
    Object Qtcp_socket, Qhandle_g2_reset, AB_package;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qhandle_network_close;
    Object Qhandle_read_event, Qhandle_write_event, Qsocket_output_buffer;
    Object Qreclaim_structure, Qoutstanding_socket_output_buffer_count;
    Object Qsocket_output_buffer_structure_memory_usage, Qutilities2;
    Object string_constant_8, Qtype_description_of_type, string_constant_7;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qhandle_network_connect;
    Object Qoutstanding_tcp_socket_count, Qtcp_socket_structure_memory_usage;
    Object string_constant_6, string_constant_5;

    x_note_fn_call(240,42);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_tcp_socket_g2_struct = 
	    STATIC_SYMBOL("TCP-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qtcp_socket = STATIC_SYMBOL("TCP-SOCKET",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    Qtcp_socket,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qtcp_socket,
	    Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_tcp_socket == UNBOUND)
	The_type_description_of_tcp_socket = Nil;
    string_constant_5 = 
	    STATIC_STRING("43Dy8m837Vy1o837Vy832ky8n8k1l832ky0000001l1m8x832kykuk0k0");
    temp = The_type_description_of_tcp_socket;
    The_type_description_of_tcp_socket = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_5));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_tcp_socket_g2_struct,
	    The_type_description_of_tcp_socket,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qtcp_socket,The_type_description_of_tcp_socket,
	    Qtype_description_of_type);
    Qoutstanding_tcp_socket_count = 
	    STATIC_SYMBOL("OUTSTANDING-TCP-SOCKET-COUNT",AB_package);
    Qtcp_socket_structure_memory_usage = 
	    STATIC_SYMBOL("TCP-SOCKET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_6 = STATIC_STRING("1q837Vy8s83-sHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_tcp_socket_count);
    push_optimized_constant(Qtcp_socket_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_6));
    Qchain_of_available_tcp_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TCP-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_tcp_sockets,
	    Chain_of_available_tcp_sockets);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_tcp_sockets,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qtcp_socket_count = STATIC_SYMBOL("TCP-SOCKET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtcp_socket_count,Tcp_socket_count);
    record_system_variable(Qtcp_socket_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_tcp_sockets_vector == UNBOUND)
	Chain_of_available_tcp_sockets_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtcp_socket_structure_memory_usage,
	    STATIC_FUNCTION(tcp_socket_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_tcp_socket_count,
	    STATIC_FUNCTION(outstanding_tcp_socket_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_tcp_socket_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_tcp_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtcp_socket,
	    reclaim_structure_for_tcp_socket_1);
    string_constant = STATIC_STRING("TCP_IP:~a:~a");
    string_constant_1 = STATIC_STRING("~a");
    Qhandle_network_connect = STATIC_SYMBOL("HANDLE-NETWORK-CONNECT",
	    AB_package);
    handle_network_connect_for_tcp_socket_1 = 
	    STATIC_FUNCTION(handle_network_connect_for_tcp_socket,NIL,
	    FALSE,2,2);
    record_direct_structure_method(Qhandle_network_connect,Qtcp_socket,
	    handle_network_connect_for_tcp_socket_1);
    Qg2_defstruct_structure_name_socket_output_buffer_g2_struct = 
	    STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsocket_output_buffer = STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    Qsocket_output_buffer,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsocket_output_buffer,
	    Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_socket_output_buffer == UNBOUND)
	The_type_description_of_socket_output_buffer = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83nIy1n83nIy8n8k1l8n0000000kqk0k0");
    temp = The_type_description_of_socket_output_buffer;
    The_type_description_of_socket_output_buffer = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    mutate_global_property(Qg2_defstruct_structure_name_socket_output_buffer_g2_struct,
	    The_type_description_of_socket_output_buffer,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsocket_output_buffer,
	    The_type_description_of_socket_output_buffer,
	    Qtype_description_of_type);
    Qoutstanding_socket_output_buffer_count = 
	    STATIC_SYMBOL("OUTSTANDING-SOCKET-OUTPUT-BUFFER-COUNT",AB_package);
    Qsocket_output_buffer_structure_memory_usage = 
	    STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_8 = STATIC_STRING("1q83nIy8s83-qDy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_socket_output_buffer_count);
    push_optimized_constant(Qsocket_output_buffer_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_socket_output_buffers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SOCKET-OUTPUT-BUFFERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_socket_output_buffers,
	    Chain_of_available_socket_output_buffers);
    record_system_variable(Qchain_of_available_socket_output_buffers,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsocket_output_buffer_count = 
	    STATIC_SYMBOL("SOCKET-OUTPUT-BUFFER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsocket_output_buffer_count,
	    Socket_output_buffer_count);
    record_system_variable(Qsocket_output_buffer_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_socket_output_buffers_vector == UNBOUND)
	Chain_of_available_socket_output_buffers_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsocket_output_buffer_structure_memory_usage,
	    STATIC_FUNCTION(socket_output_buffer_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_socket_output_buffer_count,
	    STATIC_FUNCTION(outstanding_socket_output_buffer_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_socket_output_buffer_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_socket_output_buffer,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsocket_output_buffer,
	    reclaim_structure_for_socket_output_buffer_1);
    Qblocked = STATIC_SYMBOL("BLOCKED",AB_package);
    Qwrite_bytes_to_socket = STATIC_SYMBOL("WRITE-BYTES-TO-SOCKET",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_bytes_to_socket,
	    STATIC_FUNCTION(write_bytes_to_socket,NIL,FALSE,2,2));
    Qtry_to_send_socket_sequence = 
	    STATIC_SYMBOL("TRY-TO-SEND-SOCKET-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qtry_to_send_socket_sequence,
	    STATIC_FUNCTION(try_to_send_socket_sequence,NIL,FALSE,1,1));
    string_constant_2 = STATIC_STRING("Error sending socket buffer");
    string_constant_3 = 
	    STATIC_STRING("ERROR: Unrecognized value type in network I/O.  Some data may be dropped.");
    Qhandle_write_event = STATIC_SYMBOL("HANDLE-WRITE-EVENT",AB_package);
    handle_write_event_for_tcp_socket_1 = 
	    STATIC_FUNCTION(handle_write_event_for_tcp_socket,NIL,FALSE,2,2);
    record_direct_structure_method(Qhandle_write_event,Qtcp_socket,
	    handle_write_event_for_tcp_socket_1);
    Qhandle_read_event = STATIC_SYMBOL("HANDLE-READ-EVENT",AB_package);
    handle_read_event_for_tcp_socket_1 = 
	    STATIC_FUNCTION(handle_read_event_for_tcp_socket,NIL,FALSE,3,3);
    record_direct_structure_method(Qhandle_read_event,Qtcp_socket,
	    handle_read_event_for_tcp_socket_1);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_4 = STATIC_STRING("Error ~a on socket ~a before accept");
    Qwould_block = STATIC_SYMBOL("WOULD-BLOCK",AB_package);
    Qhandle_network_close = STATIC_SYMBOL("HANDLE-NETWORK-CLOSE",AB_package);
    handle_network_close_for_tcp_socket_1 = 
	    STATIC_FUNCTION(handle_network_close_for_tcp_socket,NIL,FALSE,2,2);
    record_direct_structure_method(Qhandle_network_close,Qtcp_socket,
	    handle_network_close_for_tcp_socket_1);
    Qsocket_close_cleanups = STATIC_SYMBOL("SOCKET-CLOSE-CLEANUPS",AB_package);
    SET_SYMBOL_FUNCTION(Qsocket_close_cleanups,
	    STATIC_FUNCTION(socket_close_cleanups,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qhandle_g2_reset = STATIC_SYMBOL("HANDLE-G2-RESET",AB_package);
    handle_g2_reset_for_tcp_socket_1 = 
	    STATIC_FUNCTION(handle_g2_reset_for_tcp_socket,NIL,FALSE,1,1);
    record_direct_structure_method(Qhandle_g2_reset,Qtcp_socket,
	    handle_g2_reset_for_tcp_socket_1);
}
