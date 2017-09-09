/* int4.c
 * Input file:  int4.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int4.h"


static Object Qg2int_do_not_use;   /* do-not-use */

static Object Qg2int_wide_string;  /* wide-string */

static Object string_constant;     /* "~a:~(~a~):~a" */

/* MAKE-NETWORK-PATHNAME */
Object g2int_make_network_pathname(icp_connection_configuration)
    Object icp_connection_configuration;
{
    Object protocol, host, listener, local_string, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, simple_or_wide_character, thing, temp, schar_arg_2;
    Object schar_new_value, modified_protocol, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(44,0);
    protocol = FIRST(icp_connection_configuration);
    host = SECOND(icp_connection_configuration);
    listener = THIRD(icp_connection_configuration);
    local_string = SYMBOLP(protocol) ? 
	    g2int_symbol_name_text_string(protocol) : protocol;
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(g2int_lengthw(local_string));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(local_string,i));
	      simple_or_wide_character = (SI_Long)45L == IFIX(c) ? 
		      FIX((SI_Long)95L) : c;
	      if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
		  thing = simple_or_wide_character;
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
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = 
			  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
		  G2int_fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      modified_protocol = g2int_copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_1 = g2int_tformat_text_string(4,string_constant,modified_protocol,
	    host,listener);
    g2int_reclaim_text_string(modified_protocol);
    return VALUES_1(temp_1);
}

static Object Qg2int_vms_process;  /* vms-process */

static Object Qg2int_localnet;     /* localnet */

static Object Qg2int_g2;           /* g2 */

/* MAKE-ICP-CONNECTION */
Object g2int_make_icp_connection varargs_1(int, n)
{
    Object icp_connection_configuration;
    Object remote_system_name, application_name, connect_timeout, thing, temp;
    Object temp_1, icp_socket;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,1);
    INIT_ARGS_nonrelocating();
    icp_connection_configuration = REQUIRED_ARG_nonrelocating();
    remote_system_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    application_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !(EQ(Qg2int_vms_process,FIRST(icp_connection_configuration)) || 
	    EQ(Qg2int_localnet,FIRST(icp_connection_configuration))))
	g2int_get_local_host_name();
    if (EQ(Qg2int_localnet,CAR(icp_connection_configuration))) {
	thing = SECOND(icp_connection_configuration);
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
		g2int_copy_text_string(thing) : thing;
	temp_1 = remote_system_name;
	if (temp_1);
	else
	    temp_1 = Qg2int_g2;
	icp_socket = g2int_make_localnet_connection(3,temp,temp_1,
		connect_timeout);
    }
    else
	icp_socket = g2int_make_network_connection(2,
		icp_connection_configuration,connect_timeout);
    if (icp_socket) {
	SVREF(icp_socket,FIX((SI_Long)52L)) = application_name;
	return VALUES_1(icp_socket);
    }
    else
	return VALUES_1(Nil);
}

/* TIME-INTERVAL-ELAPSED-P */
Object g2int_time_interval_elapsed_p(time_interval_limit,start_time)
    Object time_interval_limit, start_time;
{
    x_note_fn_call(44,2);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* GET-TCPIP-LISTENER-SPECIFICATION */
Object g2int_get_tcpip_listener_specification()
{
    Object specific_network_transport_types_qm;
    Object specific_network_transport_type, ab_loop_list_, ab_loop_it_;
    Object tcpip_transport_type_specified_p, temp;

    x_note_fn_call(44,3);
    specific_network_transport_types_qm = 
	    g2int_get_all_command_line_keyword_arguments(array_constant);
    specific_network_transport_type = Nil;
    ab_loop_list_ = specific_network_transport_types_qm;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    specific_network_transport_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = g2int_string_equalw(specific_network_transport_type,
	    array_constant_1);
    if (ab_loop_it_) {
	tcpip_transport_type_specified_p = ab_loop_it_;
	goto end;
    }
    goto next_loop;
  end_loop:
    tcpip_transport_type_specified_p = Qnil;
  end:;
    if ( !TRUEP(specific_network_transport_types_qm) || 
	    tcpip_transport_type_specified_p) {
	temp = g2int_get_command_line_keyword_argument_as_integer(1,
		array_constant_2);
	if (temp);
	else
	    temp = 
		    g2int_read_number_for_gensym_environment_variable(array_constant_3);
	if (temp);
	else
	    temp = Kdefault;
    }
    else
	temp = Nil;
    g2int_reclaim_gensym_list_1(specific_network_transport_types_qm);
    return VALUES_1(temp);
}

static Object Qg2int_generic;      /* generic */

/* MAKE-AND-INSTALL-NETWORK-ICP-SOCKET */
Object g2int_make_and_install_network_icp_socket varargs_1(int, n)
{
    Object input_connection_handle, output_connection_handle;
    Object external_process_name, initially_open_p;
    Object parent_listener_qm, connect_timeout, icp_socket;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,4);
    INIT_ARGS_nonrelocating();
    input_connection_handle = REQUIRED_ARG_nonrelocating();
    output_connection_handle = REQUIRED_ARG_nonrelocating();
    external_process_name = REQUIRED_ARG_nonrelocating();
    initially_open_p = REQUIRED_ARG_nonrelocating();
    parent_listener_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    icp_socket = g2int_make_icp_socket(external_process_name,
	    Qg2int_generic,input_connection_handle,
	    output_connection_handle,Nil,T,initially_open_p,
	    parent_listener_qm,G2int_current_system_name,connect_timeout);
    g2int_register_socket_to_handle(icp_socket,input_connection_handle);
    g2int_add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

/* MAKE-AND-INSTALL-NETWORK-LISTENER */
Object g2int_make_and_install_network_listener(listener_handle,network_address)
    Object listener_handle, network_address;
{
    Object icp_socket, svref_new_value;

    x_note_fn_call(44,5);
    icp_socket = g2int_make_icp_socket(network_address,Qg2int_generic,
	    listener_handle,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    svref_new_value = G2int_icp_socket_listening;
    SVREF(icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    g2int_register_socket_to_handle(icp_socket,listener_handle);
    g2int_add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

static Object string_constant_1;   /* "~a" */

static Object Qg2int_default;      /* default */

/* MAKE-NETWORK-CONNECTION */
Object g2int_make_network_connection varargs_1(int, n)
{
    Object connection_configuration;
    Object connect_timeout, network_pathname, port_string, secure_p;
    Object connection_handle, nascent_socket, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,6);
    INIT_ARGS_nonrelocating();
    connection_configuration = REQUIRED_ARG_nonrelocating();
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    network_pathname = g2int_make_network_pathname(connection_configuration);
    port_string = g2int_tformat_text_string(2,string_constant_1,
	    THIRD(connection_configuration));
    secure_p = FIXNUM_GT(length(connection_configuration),
	    FIX((SI_Long)3L)) ? (EQ(FOURTH(connection_configuration),
	    Qg2int_default) ? Nil : FOURTH(connection_configuration)) : 
	    G2int_secure_icp_default_p;
    connection_handle = g2int_network_connect(4,network_pathname,
	    SECOND(connection_configuration),port_string,secure_p);
    g2int_reclaim_text_string(port_string);
    if ( !(IFIX(connection_handle) >= (SI_Long)0L)) {
	g2int_reclaim_text_string(network_pathname);
	return VALUES_1(Nil);
    }
    nascent_socket = g2int_make_and_install_network_icp_socket(6,
	    connection_handle,connection_handle,network_pathname,T,Nil,
	    connect_timeout);
    svref_new_value = G2int_icp_connection_connect_in_progress;
    SVREF(nascent_socket,FIX((SI_Long)15L)) = svref_new_value;
    return VALUES_1(nascent_socket);
}

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* SETUP-NETWORK-CONNECTION-FOR-CONNECT */
Object g2int_setup_network_connection_for_connect varargs_1(int, n)
{
    Object icp_socket;
    Object user_connect_callback, temp, connection_handle, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,7);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    user_connect_callback = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (icp_socket && EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_connect_in_progress)) {
	if (user_connect_callback)
	    g2int_register_icp_connect_callback(user_connect_callback,
		    icp_socket);
	temp = ISVREF(icp_socket,(SI_Long)1L);
	if (EQ(temp,Qg2int_localnet))
	    g2int_handle_icp_connect(icp_socket);
	else if (EQ(temp,Qg2int_generic)) {
	    connection_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),
		    (SI_Long)1L);
	    if ( !((SI_Long)0L == ne_connected_p(IFIX(connection_handle)))) {
		gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
		gensymed_symbol = 
			ISVREF(ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qg2int_type_description_of_unique_type_name_of_gensym_structure),
			(SI_Long)9L),(SI_Long)22L);
		gensymed_symbol_1 = icp_socket;
		gensymed_symbol_2 = 
			ne_last_error_code(IFIX(connection_handle));
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			FIX(gensymed_symbol_2));
	    }
	}
    }
    return VALUES_1(icp_socket);
}

/* GET-ACCEPT-PATHNAME */
Object g2int_get_accept_pathname(accept_handle)
    Object accept_handle;
{
    Object result_code;

    x_note_fn_call(44,8);
    result_code = g2int_c_get_connection_pathname(accept_handle,
	    G2int_gensym_environment_variable_buffer,FIX((SI_Long)1023L));
    if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(result_code)) {
	  case 1:
	    return g2int_copy_null_terminated_string_as_text_string(G2int_gensym_environment_variable_buffer);
	  case -1:
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

/* GET-NETWORK-LISTENER */
Object g2int_get_network_listener(position_1)
    Object position_1;
{
    Object listener_buffer_as_simple_gensym_string, length_1, temp;
    SI_Long buffer_size;

    x_note_fn_call(44,9);
    buffer_size = (SI_Long)300L;
    listener_buffer_as_simple_gensym_string = 
	    g2int_obtain_simple_gensym_string(FIX(buffer_size));
    length_1 = g2int_c_get_network_listener(position_1,
	    listener_buffer_as_simple_gensym_string,FIX(buffer_size));
    temp = (SI_Long)0L < IFIX(length_1) ? 
	    g2int_copy_partial_text_string(listener_buffer_as_simple_gensym_string,
	    length_1) : Nil;
    g2int_reclaim_gensym_string(listener_buffer_as_simple_gensym_string);
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

/* GET-LOCAL-HOST-ADDRESSES */
Object g2int_get_local_host_addresses()
{
    Object listeners, listener, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, thing, temp, schar_arg_2, schar_new_value, temp_1;
    Object delimiter_count, temp_2;
    SI_Long listener_count, listener_pos, ab_loop_bind_, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, i, ab_loop_bind__1, j;
    Declare_special(5);

    x_note_fn_call(44,10);
    listener_count = g2ext_network_listener_count();
    listeners = Nil;
    listener_pos = (SI_Long)0L;
    ab_loop_bind_ = listener_count;
    listener = Nil;
  next_loop:
    if (listener_pos >= ab_loop_bind_)
	goto end_loop;
    listener = g2int_get_network_listener(FIX(listener_pos));
    if (listener) {
	if ( !TRUEP(g2int_stringeqw(listener,array_constant_4))) {
	    current_wide_string_list = Qg2int_do_not_use;
	    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L));
		  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qg2int_wide_string;
		    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			    0);
		      i = (SI_Long)0L;
		      ab_loop_bind__1 = IFIX(g2int_lengthw(listener));
		      c = Nil;
		    next_loop_1:
		      if (i >= ab_loop_bind__1)
			  goto end_loop_1;
		      c = FIX(UBYTE_16_ISAREF_1(listener,i));
		      if (IFIX(c) == (SI_Long)58L)
			  goto end_loop_1;
		      if (EQ(G2int_current_twriting_output_type,
			      Qg2int_wide_string)) {
			  thing = c;
			  g2int_twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				  G2int_total_length_of_current_gensym_string))
			      g2int_extend_current_gensym_string(0);
			  temp = G2int_current_gensym_string;
			  schar_arg_2 = 
				  G2int_fill_pointer_for_current_gensym_string;
			  thing = c;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			  G2int_fill_pointer_for_current_gensym_string = temp;
		      }
		      i = i + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      temp_1 = g2int_copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    delimiter_count = FIX((SI_Long)0L);
	    current_wide_string_list = Qg2int_do_not_use;
	    PUSH_SPECIAL(G2int_current_wide_string_list,current_wide_string_list,
		    4);
	      wide_string_bv16 = 
		      g2int_allocate_byte_vector_16(FIX((SI_Long)2048L + 
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
	      PUSH_SPECIAL(G2int_current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(G2int_fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(G2int_current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(G2int_current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(G2int_current_wide_string,
			  length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			  (SI_Long)16L));
		  PUSH_SPECIAL(G2int_total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qg2int_wide_string;
		    PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
			    0);
		      i = (SI_Long)0L;
		      ab_loop_bind__1 = IFIX(g2int_lengthw(listener));
		      c = Nil;
		    next_loop_2:
		      if (i >= ab_loop_bind__1)
			  goto end_loop_2;
		      c = FIX(UBYTE_16_ISAREF_1(listener,i));
		      if (IFIX(delimiter_count) == (SI_Long)2L)
			  goto end_loop_2;
		      if (IFIX(c) == (SI_Long)58L)
			  delimiter_count = FIXNUM_ADD1(delimiter_count);
		      i = i + (SI_Long)1L;
		      goto next_loop_2;
		    end_loop_2:
		      j = i;
		      ab_loop_bind__1 = IFIX(g2int_lengthw(listener));
		      c = Nil;
		    next_loop_3:
		      if (j >= ab_loop_bind__1)
			  goto end_loop_3;
		      c = FIX(UBYTE_16_ISAREF_1(listener,j));
		      if (IFIX(c) == (SI_Long)58L)
			  goto end_loop_3;
		      if (EQ(G2int_current_twriting_output_type,
			      Qg2int_wide_string)) {
			  thing = c;
			  g2int_twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
				  G2int_total_length_of_current_gensym_string))
			      g2int_extend_current_gensym_string(0);
			  temp = G2int_current_gensym_string;
			  schar_arg_2 = 
				  G2int_fill_pointer_for_current_gensym_string;
			  thing = c;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
			  G2int_fill_pointer_for_current_gensym_string = temp;
		      }
		      j = j + (SI_Long)1L;
		      goto next_loop_3;
		    end_loop_3:;
		      temp_2 = g2int_copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_1 = g2int_gensym_list_3(temp_1,temp_2,
		    g2ext_secure_socket_p(ne_get_listener_handle(listener_pos)) 
		    == (SI_Long)1L ? T : Nil);
	    listeners = g2int_gensym_cons_1(temp_1,listeners);
	}
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(listener) != (SI_Long)0L)
	    g2int_reclaim_wide_string(listener);
    }
    listener_pos = listener_pos + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(listeners);
    return VALUES_1(Qnil);
}

/* RECLAIM-NETWORK-ADDRESSES */
Object g2int_reclaim_network_addresses(network_addresses)
    Object network_addresses;
{
    x_note_fn_call(44,11);
    return g2int_reclaim_gensym_tree_with_text_strings(network_addresses);
}

/* GET-UNIX-HOST-NAME */
Object g2int_get_unix_host_name()
{
    Object gensym_string, length_1, temp;

    x_note_fn_call(44,12);
    gensym_string = g2int_obtain_simple_gensym_string(FIX((SI_Long)100L));
    length_1 = g2int_gethostname_1(gensym_string,
	    SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string));
    if (IFIX(length_1) < (SI_Long)0L)
	temp = Nil;
    else if (IFIX(length_1) == (SI_Long)0L)
	temp = Nil;
    else
	temp = g2int_copy_text_string_portion(gensym_string,
		FIX((SI_Long)0L),length_1);
    g2int_reclaim_gensym_string(gensym_string);
    return VALUES_1(temp);
}

Object G2int_icp_connection_succeeded_tag = UNBOUND;

Object G2int_icp_connection_failed_tag = UNBOUND;

Object G2int_icp_noop_network_code_accessed = UNBOUND;

/* ICP-CONNECTION-LOSS-NOTIFIER */
Object g2int_icp_connection_loss_notifier(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    x_note_fn_call(44,13);
    return VALUES_1(Nil);
}

/* ICP-CONNECTION-IS-SECURE */
Object g2int_icp_connection_is_secure(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(44,14);
    temp = icp_socket &&  !EQ(ISVREF(icp_socket,(SI_Long)1L),
	    Qg2int_localnet) && ISVREF(icp_socket,(SI_Long)3L) && 
	    ISVREF(ISVREF(icp_socket,(SI_Long)3L),(SI_Long)1L) ? 
	    (g2ext_secure_socket_p(IFIX(ISVREF(ISVREF(icp_socket,
	    (SI_Long)3L),(SI_Long)1L))) == (SI_Long)1L ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

static Object Qg2int_icp_connection_loss_notifier;  /* icp-connection-loss-notifier */

/* REGISTER-ICP-CONNECTION-LOSS-CALLBACK-FUNCTION */
Object g2int_register_icp_connection_loss_callback_function(listener_socket_qm,
	    nascent_socket)
    Object listener_socket_qm, nascent_socket;
{
    x_note_fn_call(44,15);
    if (listener_socket_qm)
	SVREF(nascent_socket,FIX((SI_Long)33L)) = listener_socket_qm;
    return g2int_register_icp_connection_loss_callback(Qg2int_icp_connection_loss_notifier,
	    nascent_socket);
}

/* GET-TCP-LISTENER-PORT-NUMBER */
Object g2int_get_tcp_listener_port_number(tcp_name)
    Object tcp_name;
{
    Object length_1, first_1, second_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(44,16);
    length_1 = g2int_lengthw(tcp_name);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(tcp_name,i) == (SI_Long)58L) {
	first_1 = FIX(i);
	goto end;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    first_1 = Qnil;
  end:;
    if (first_1) {
	i = IFIX(FIXNUM_ADD1(first_1));
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (UBYTE_16_ISAREF_1(tcp_name,i) == (SI_Long)58L) {
	    second_1 = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	second_1 = Qnil;
      end_1:;
    }
    else
	second_1 = Nil;
    if (second_1)
	return g2int_text_string_parse_integer_function(tcp_name,
		FIXNUM_ADD1(second_1),Nil,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_telewindows;  /* telewindows */

static Object Qg2int_gsi;          /* gsi */

static Object array_constant_5;    /* # */

static Object list_constant;       /* # */

static Object string_constant_2;   /* "ERROR: Could not make exact ICP connection~%" */

static Object Qg2int_register_icp_connection_loss_callback_function;  /* register-icp-connection-loss-callback-function */

static Object string_constant_3;   /* "ERROR: DECnet not supported by this product on this platform" */

/* ESTABLISH-G2-NETWORK-LISTENERS */
Object g2int_establish_g2_network_listeners()
{
    Object tcp_port_qm, tcp_ip_exact_p, listener_name_0, listener_socket_0;
    Object listener_handle_1_qm, listener_name_1, listener_socket_1_qm;
    Object tcp_name;
    SI_Long initial_listener_count, temp, listen_status, listener_count;
    SI_Long listener_handle_0;
    char two_listeners_qm;

    x_note_fn_call(44,17);
    if ( !(EQ(Qg2int_telewindows,G2int_current_system_name) || 
	    EQ(Qg2int_gsi,G2int_current_system_name))) {
	if (g2int_secure_icp_requested_p())
	    g2int_set_up_secure_icp(1,Qg2int_default);
	initial_listener_count = g2ext_network_listener_count();
	tcp_port_qm = g2int_get_tcpip_listener_specification();
	tcp_ip_exact_p = g2int_get_command_line_flag_argument(1,
		array_constant_5);
	temp = g2int_memq_function(tcp_port_qm,list_constant) ? 
		(SI_Long)0L : IFIX(tcp_port_qm);
	listen_status = g2ext_network_listen(tcp_port_qm ? 
		IFIX(G2int_use_tcpip_protocol_only) : 
		IFIX(G2int_use_no_network_protocols),temp,tcp_ip_exact_p ? 
		(SI_Long)1L : (SI_Long)0L,IFIX(G2int_g2_product_tag),
		g2int_secure_icp_requested_p() ? (SI_Long)1L : (SI_Long)0L);
	if ( !((SI_Long)-128L <= listen_status && listen_status <= 
		(SI_Long)127L)) {
	    if (tcp_ip_exact_p) {
		g2int_notify_user_in_parent_window(1,string_constant_2);
		return g2int_shut_down_ab_process(0);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    switch ((char)listen_status) {
	      case 1:
		listener_count = g2ext_network_listener_count();
		two_listeners_qm = listener_count - initial_listener_count 
			== (SI_Long)2L;
		listener_handle_0 = ne_get_listener_handle((SI_Long)0L);
		listener_name_0 = g2int_get_network_listener(FIX((SI_Long)0L));
		listener_socket_0 = 
			g2int_make_and_install_network_listener(FIX(listener_handle_0),
			listener_name_0);
		listener_handle_1_qm = two_listeners_qm ? 
			FIX(ne_get_listener_handle((SI_Long)1L)) : Nil;
		listener_name_1 = two_listeners_qm ? 
			g2int_get_network_listener(FIX((SI_Long)1L)) : Nil;
		listener_socket_1_qm = two_listeners_qm ? 
			g2int_make_and_install_network_listener(listener_handle_1_qm,
			listener_name_1) : Nil;
		tcp_name = (SI_Long)84L == 
			UBYTE_16_ISAREF_1(listener_name_0,(SI_Long)0L) ? 
			listener_name_0 : two_listeners_qm && (SI_Long)84L 
			== UBYTE_16_ISAREF_1(listener_name_1,(SI_Long)0L) ?
			 listener_name_1 : Nil;
		if (tcp_name)
		    G2int_tcp_listener_port_number = 
			    g2int_get_tcp_listener_port_number(tcp_name);
		g2int_register_icp_accept_callback(Qg2int_register_icp_connection_loss_callback_function,
			listener_socket_0);
		if (two_listeners_qm)
		    g2int_register_icp_accept_callback(Qg2int_register_icp_connection_loss_callback_function,
			    listener_socket_1_qm);
		return VALUES_1(T);
	      case -2:
		g2int_notify_user_in_parent_window(1,string_constant_3);
		return g2int_shut_down_ab_process(0);
	      default:
		if (tcp_ip_exact_p) {
		    g2int_notify_user_in_parent_window(1,string_constant_2);
		    return g2int_shut_down_ab_process(0);
		}
		else
		    return VALUES_1(Nil);
	    }
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_4;   /* "host: ~a~%" */

static Object string_constant_5;   /* "~a~a: ~a~a~%" */

static Object Knetwork_type;       /* :network-type */

static Object Ksecure_p;           /* :secure-p */

static Object string_constant_6;   /* "WARNING: Could not make ICP connection~%" */

/* REPORT-LISTENER-INFO-TO-PARENT-WINDOW */
Object g2int_report_listener_info_to_parent_window()
{
    Object host_name, port_list, network_type, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object left_hand_slot_lengths_qm, left_hand_slot_length, max_slot_length;
    Object largest_left_hand_slot_qm, address, secure_p, slot_length;
    Object ab_loop_list__1, space_string, temp, length_1, wide_string_bv16;
    Object temp_1, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    Object result;

    x_note_fn_call(44,18);
    if (G2int_generic_listener_initializedqm) {
	result = g2int_get_raw_network_info();
	MVS_2(result,host_name,port_list);
	network_type = Nil;
	ab_loop_list_ = port_list;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	network_type = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = g2int_gensym_cons_1(length(network_type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	left_hand_slot_lengths_qm = ab_loopvar_;
	goto end;
	left_hand_slot_lengths_qm = Qnil;
      end:;
	if (left_hand_slot_lengths_qm) {
	    left_hand_slot_length = Nil;
	    ab_loop_list_ = REST(left_hand_slot_lengths_qm);
	    max_slot_length = FIRST(left_hand_slot_lengths_qm);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    left_hand_slot_length = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (FIXNUM_GT(left_hand_slot_length,max_slot_length))
		max_slot_length = left_hand_slot_length;
	    goto next_loop_1;
	  end_loop_1:
	    largest_left_hand_slot_qm = max_slot_length;
	    goto end_1;
	    largest_left_hand_slot_qm = Qnil;
	  end_1:;
	}
	else
	    largest_left_hand_slot_qm = Nil;
	g2int_notify_user_at_console(2,string_constant_4,host_name);
	if (largest_left_hand_slot_qm) {
	    network_type = Nil;
	    address = Nil;
	    secure_p = Nil;
	    ab_loop_list_ = port_list;
	    slot_length = Nil;
	    ab_loop_list__1 = left_hand_slot_lengths_qm;
	    space_string = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    network_type = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    address = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    temp = CDR(temp);
	    secure_p = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    slot_length = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    length_1 = FIXNUM_MINUS(largest_left_hand_slot_qm,slot_length);
	    wide_string_bv16 = 
		    g2int_allocate_byte_vector_16(FIX(IFIX(length_1) + 
		    (SI_Long)3L));
	    g2int_fill_wide_string_1(wide_string_bv16,FIX((SI_Long)32L),
		    FIX((SI_Long)0L),length_1);
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(length_1) & (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | IFIX(length_1) >>  -  - 
		    (SI_Long)16L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,IFIX(length_1),(SI_Long)0L);
	    space_string = wide_string_bv16;
	    temp = space_string;
	    temp_1 = network_type;
	    temp_2 = address;
	    g2int_notify_user_at_console(5,string_constant_5,temp,temp_1,
		    temp_2,g2int_secure_icp_string(4,Knetwork_type,
		    network_type,Ksecure_p,secure_p));
	    g2int_reclaim_text_string(space_string);
	    goto next_loop_2;
	  end_loop_2:;
	}
	g2int_add_network_info_to_title_if_appropriate(host_name,port_list);
	g2int_reclaim_gensym_list_1(left_hand_slot_lengths_qm);
	return g2int_reclaim_raw_network_info(host_name,port_list);
    }
    else
	return g2int_notify_user_at_console(1,string_constant_6);
}

Object G2int_system_window_title_and_info_text_stringqm = UNBOUND;

/* ADD-NETWORK-INFO-TO-TITLE-IF-APPROPRIATE */
Object g2int_add_network_info_to_title_if_appropriate(host_name,port_list)
    Object host_name, port_list;
{
    x_note_fn_call(44,19);
    return VALUES_1(Nil);
}

static Object Qg2int_localnet_handle;  /* localnet-handle */

/* MAKE-LOCALNET-SOCKET */
Object g2int_make_localnet_socket(external_object_name,local_system_name,
	    connect_timeout)
    Object external_object_name, local_system_name, connect_timeout;
{
    Object icp_socket;

    x_note_fn_call(44,20);
    icp_socket = g2int_make_icp_socket(external_object_name,
	    Qg2int_localnet,Qg2int_localnet_handle,Qg2int_localnet_handle,
	    Nil,T,T,T,local_system_name,connect_timeout);
    g2int_add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

/* MAKE-LOCALNET-CONNECTION */
Object g2int_make_localnet_connection varargs_1(int, n)
{
    Object external_object_name, remote_system_name;
    Object connect_timeout, main_icp_socket, server_icp_socket;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,21);
    INIT_ARGS_nonrelocating();
    external_object_name = REQUIRED_ARG_nonrelocating();
    remote_system_name = REQUIRED_ARG_nonrelocating();
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    main_icp_socket = g2int_make_localnet_socket(external_object_name,
	    G2int_current_system_name,connect_timeout);
    server_icp_socket = 
	    g2int_make_localnet_socket(INLINE_UNSIGNED_BYTE_16_VECTOR_P(external_object_name) 
	    != (SI_Long)0L ? g2int_copy_text_string(external_object_name) :
	     external_object_name,remote_system_name,connect_timeout);
    svref_new_value = G2int_icp_connection_connect_in_progress;
    SVREF(main_icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    SVREF(main_icp_socket,FIX((SI_Long)42L)) = server_icp_socket;
    SVREF(server_icp_socket,FIX((SI_Long)42L)) = main_icp_socket;
    if (EQ(remote_system_name,Qg2int_gsi))
	g2int_register_gsi_connection_callbacks(Nil,server_icp_socket);
    else
	g2int_register_icp_connection_loss_callback_function(Nil,
		server_icp_socket);
    return VALUES_1(main_icp_socket);
}

/* RECLAIM-ICP-BUFFER-LIST */
Object g2int_reclaim_icp_buffer_list(buffer_list)
    Object buffer_list;
{
    Object buffer, next_buffer;

    x_note_fn_call(44,22);
    buffer = buffer_list;
    next_buffer = Nil;
  next_loop:
    if ( !TRUEP(buffer))
	goto end_loop;
    next_buffer = ISVREF(buffer,(SI_Long)1L);
    g2int_reclaim_icp_buffer(buffer);
    buffer = next_buffer;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-BUFFERS-FOR-PORT */
Object g2int_reclaim_icp_buffers_for_port(icp_port)
    Object icp_port;
{
    x_note_fn_call(44,23);
    g2int_reclaim_icp_buffer_list(ISVREF(icp_port,(SI_Long)12L));
    SVREF(icp_port,FIX((SI_Long)12L)) = Nil;
    SVREF(icp_port,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-PORT */
Object g2int_reclaim_icp_port(icp_port)
    Object icp_port;
{
    Object icp_port_for_reclaim;
    Declare_special(1);

    x_note_fn_call(44,24);
    g2int_reclaim_icp_buffers_for_port(icp_port);
    icp_port_for_reclaim = icp_port;
    PUSH_SPECIAL(G2int_icp_port_for_reclaim,icp_port_for_reclaim,0);
      g2int_reclaim_icp_port_internal_1(icp_port);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qg2int_ab;           /* ab */

/* RECLAIM-ICP-INPUT-PORT */
Object g2int_reclaim_icp_input_port(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, system_name, current_system_name;
    Object callback_icp_buffer_list, icp_buffer, next_icp_buffer;
    Declare_special(1);

    x_note_fn_call(44,25);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    system_name = ISVREF(icp_socket,(SI_Long)49L);
    current_system_name = EQ(system_name,Qg2int_g2) ? Qg2int_ab : system_name;
    PUSH_SPECIAL(G2int_current_system_name,current_system_name,0);
      if (icp_input_port) {
	  callback_icp_buffer_list = ISVREF(icp_input_port,(SI_Long)7L);
	  if (callback_icp_buffer_list) {
	      icp_buffer = callback_icp_buffer_list;
	      next_icp_buffer = Nil;
	    next_loop:
	      if ( !TRUEP(icp_buffer))
		  goto end_loop;
	      next_icp_buffer = ISVREF(icp_buffer,(SI_Long)1L);
	      g2int_reclaim_icp_buffer(icp_buffer);
	      icp_buffer = next_icp_buffer;
	      goto next_loop;
	    end_loop:;
	  }
	  g2int_reclaim_icp_port(icp_input_port);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-OUTPUT-PORT */
Object g2int_reclaim_icp_output_port(icp_socket)
    Object icp_socket;
{
    Object icp_output_port;

    x_note_fn_call(44,26);
    icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
    if (icp_output_port) {
	SVREF(icp_socket,FIX((SI_Long)4L)) = Nil;
	g2int_reclaim_icp_port(icp_output_port);
    }
    return VALUES_1(Nil);
}

Object G2int_gsi_throw_to_run_loop_may_be_harmful_p = UNBOUND;

/* RECLAIM-ICP-SOCKET */
Object g2int_reclaim_icp_socket(icp_socket)
    Object icp_socket;
{
    Object gsi_throw_to_run_loop_may_be_harmful_p;
    Declare_special(1);

    x_note_fn_call(44,27);
    gsi_throw_to_run_loop_may_be_harmful_p = T;
    PUSH_SPECIAL(G2int_gsi_throw_to_run_loop_may_be_harmful_p,gsi_throw_to_run_loop_may_be_harmful_p,
	    0);
      g2int_reclaim_icp_input_port(icp_socket);
      g2int_reclaim_icp_output_port(icp_socket);
      g2int_maybe_call_gsi_shutdown_context_callback(icp_socket);
    POP_SPECIAL();
    g2int_reclaim_icp_socket_internal_1(icp_socket);
    return VALUES_1(Nil);
}

Object G2int_icp_socket_for_reclaimqm = UNBOUND;

static Object Qg2int_gsi_instance;  /* gsi-instance */

static Object Qg2int_item_with_handle_index_space;  /* item-with-handle-index-space */

static Object Qg2int_input;        /* input */

static Object Qg2int_reclaimer_for_icp_port_entry;  /* reclaimer-for-icp-port-entry */

static Object Qg2int_shutdown_reclaimer_for_icp_object;  /* shutdown-reclaimer-for-icp-object */

/* REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-1 */
Object g2int_remove_icp_port_entries_from_icp_object_1(icp_object,
	    icp_object_type,icp_port,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object, icp_object_type, icp_port;
    Object name_of_corresponding_icp_object_index_space, shutdownp;
{
    Object deregister_for_gsi_p, index_for_gsi, icp_port_entry_reclaimer_qm;
    Object icp_socket_for_reclaim_qm, shutdown_reclaimer_qm;
    Declare_special(1);

    x_note_fn_call(44,28);
    deregister_for_gsi_p = EQ(icp_object_type,Qg2int_gsi_instance) &&  
	    !EQ(name_of_corresponding_icp_object_index_space,
	    Qg2int_item_with_handle_index_space) ? (EQ(Qg2int_input,
	    ISVREF(icp_port,(SI_Long)3L)) ? T : Nil) : Qnil;
    index_for_gsi = deregister_for_gsi_p ? 
	    g2int_get_icp_object_index_for_gsi_instance(icp_object,
	    icp_port) : Nil;
    icp_port_entry_reclaimer_qm = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type),
	    Qg2int_reclaimer_for_icp_port_entry);
    if (icp_port_entry_reclaimer_qm)
	inline_funcall_2(icp_port_entry_reclaimer_qm,icp_object,icp_port);
    if (deregister_for_gsi_p) {
	icp_socket_for_reclaim_qm = ISVREF(icp_port,(SI_Long)2L);
	PUSH_SPECIAL(G2int_icp_socket_for_reclaimqm,icp_socket_for_reclaim_qm,
		0);
	  g2int_gsi_deregister_items_wrapper_for_known_sensor(icp_object,
		  index_for_gsi);
	POP_SPECIAL();
    }
    if (shutdownp) {
	shutdown_reclaimer_qm = 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type),
		Qg2int_shutdown_reclaimer_for_icp_object);
	if (shutdown_reclaimer_qm)
	    return VALUES_1(inline_funcall_2(shutdown_reclaimer_qm,
		    icp_object,icp_port));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT */
Object g2int_remove_icp_port_entries_from_icp_object(icp_object,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object, name_of_corresponding_icp_object_index_space, shutdownp;
{
    Object icp_object_type_qm;

    x_note_fn_call(44,29);
    if (G2int_icp_port_for_reclaim) {
	icp_object_type_qm = 
		g2int_icp_object_type_given_icp_object(icp_object,
		name_of_corresponding_icp_object_index_space);
	if (icp_object_type_qm)
	    return g2int_remove_icp_port_entries_from_icp_object_1(icp_object,
		    icp_object_type_qm,G2int_icp_port_for_reclaim,
		    name_of_corresponding_icp_object_index_space,shutdownp);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-LIST */
Object g2int_remove_icp_port_entries_from_icp_object_list(icp_object_list,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object_list, name_of_corresponding_icp_object_index_space;
    Object shutdownp;
{
    Object icp_object, ab_loop_list_;

    x_note_fn_call(44,30);
    if (G2int_icp_port_for_reclaim && CONSP(icp_object_list)) {
	icp_object = Nil;
	ab_loop_list_ = icp_object_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	icp_object = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2int_remove_icp_port_entries_from_icp_object(icp_object,
		name_of_corresponding_icp_object_index_space,shutdownp);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* NOTE-ITEM-DELETED-FROM-FRAME-SERIAL-NUMBER-TABLE */
Object g2int_note_item_deleted_from_frame_serial_number_table(item)
    Object item;
{
    x_note_fn_call(44,31);
    return VALUES_1(Nil);
}

static Object Qg2int_output;       /* output */

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_item_index_space;  /* item-index-space */

static Object Qg2int_frame_serial_number;  /* frame-serial-number */

/* RECLAIM-INDEX-SPACE-LOCATION-AND-CORRESPONDING-OBJECTS */
Object g2int_reclaim_index_space_location_and_corresponding_objects(icp_object,
	    icp_port,index_1,index_space_name)
    Object icp_object, icp_port, index_1, index_space_name;
{
    Object port, actual_index_space_name, icp_socket, temp, temp_1;
    Object index_space, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, icp_object_from_index_space, vector_1;
    Object current_icp_socket, will_ack_p, send_p;
    SI_Long gensymed_symbol, temp_2, gensymed_symbol_3, index_2;
    char output_port_p;
    Declare_special(1);

    x_note_fn_call(44,32);
    output_port_p = EQ(Qg2int_output,ISVREF(icp_port,(SI_Long)3L));
    port = icp_port;
    if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	actual_index_space_name = Qg2int_standard_icp_object_index_space;
    else if (EQ(index_space_name,Qg2int_item_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (G2int_inhibit_corresponding_icp_object_making)
	    actual_index_space_name = Qg2int_standard_icp_object_index_space;
	else if (Nil) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		actual_index_space_name = Qg2int_item_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		actual_index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qg2int_item_index_space : 
			Qg2int_frame_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    actual_index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qg2int_item_index_space : 
		    Qg2int_standard_icp_object_index_space;
	}
    }
    else if (EQ(index_space_name,Qg2int_frame_serial_number))
	actual_index_space_name = EQ(ISVREF(port,(SI_Long)3L),
		Qg2int_output) ? Qg2int_item_index_space : 
		Qg2int_frame_serial_number;
    else
	actual_index_space_name = Qg2int_standard_icp_object_index_space;
    if (EQ(actual_index_space_name,Qg2int_standard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(actual_index_space_name,Qg2int_item_index_space))
	index_space = g2int_item_index_space(icp_port);
    else if (EQ(actual_index_space_name,Qg2int_frame_serial_number))
	index_space = g2int_frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(actual_index_space_name,Qg2int_frame_serial_number)) {
	gensymed_symbol = IFIX(g2int_sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	gensymed_symbol_1 = CDR(temp_1);
	gensymed_symbol_2 = index_1;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		icp_object_from_index_space = M_CDR(M_CAR(gensymed_symbol_1));
		goto end;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    icp_object_from_index_space = Qnil;
	  end:;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	icp_object_from_index_space = Qnil;
      end_1:;
    }
    else {
	vector_1 = ISVREF(index_space,(SI_Long)2L);
	index_2 = IFIX(index_1) >>  -  - (SI_Long)10L;
	vector_1 = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
	index_2 = IFIX(index_1) & (SI_Long)1023L;
	icp_object_from_index_space = vector_1 && index_2 < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		ISVREF(vector_1,index_2) : Qnil;
    }
    if ( !EQ(icp_object_from_index_space,icp_object)) {
	if (g2int_item_with_handle_index_space(icp_port) && 
		EQ(actual_index_space_name,Qg2int_item_index_space))
	    return g2int_deregister_item_with_handle_on_port(index_1,
		    icp_object,icp_port);
	else
	    return VALUES_1(Nil);
    }
    else {
	current_icp_socket = ISVREF(icp_port,(SI_Long)2L);
	PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
	  will_ack_p = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		  >= (SI_Long)12L ? (EQ(actual_index_space_name,
		  Qg2int_item_index_space) ? ( !(output_port_p && 
		  G2int_deregister_corresponding_objectqm && 
		  G2int_deregister_and_register_item_p) ? T : Nil) : Qnil) 
		  : Nil;
	POP_SPECIAL();
	send_p = g2int_send_reclaim_index_space_message_p(icp_port,Nil,
		actual_index_space_name);
	if ( 
		!TRUEP(g2int_send_immediate_reclaim_index_space_message(ISVREF(ISVREF(icp_port,
		(SI_Long)2L),(SI_Long)4L),index_1,actual_index_space_name,
		Nil,output_port_p ? T : Nil,send_p))) {
	    if (send_p)
		g2int_enqueue_reclaim_index_space_message(ISVREF(ISVREF(icp_port,
			(SI_Long)2L),(SI_Long)4L),index_1,
			actual_index_space_name,Nil,output_port_p ? T : 
			Nil,T,will_ack_p);
	}
	return g2int_deregister_corresponding_icp_object(icp_object,
		index_1,actual_index_space_name,icp_port,T);
    }
}

/* SEND-RECLAIM-INDEX-SPACE-MESSAGE-P */
Object g2int_send_reclaim_index_space_message_p(icp_port,ack_p,
	    actual_index_space_name)
    Object icp_port, ack_p, actual_index_space_name;
{
    Object current_icp_socket, temp, temp_1;
    char output_port_p, temp_2;
    Declare_special(1);

    x_note_fn_call(44,33);
    current_icp_socket = ISVREF(icp_port,(SI_Long)2L);
    output_port_p = EQ(Qg2int_output,ISVREF(icp_port,(SI_Long)3L));
    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
      if (g2int_icp_connection_open_p(G2int_current_icp_socket)) {
	  if (ack_p)
	      temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) 
		      >= (SI_Long)12L ? T : Nil;
	  else if (output_port_p && EQ(actual_index_space_name,
		  Qg2int_frame_serial_number) && 
		  (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)12L ?  !TRUEP(Nil) : TRUEP(T)))
	      temp = Nil;
	  else if ( !output_port_p) {
	      if (G2int_delete_corresponding_objectqm || 
		      G2int_deregister_corresponding_objectqm) {
		  temp_1 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		  temp = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		  temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)10L ? T 
			  : Nil;
	      }
	      else
		  temp = Nil;
	  }
	  else {
	      if (G2int_delete_corresponding_objectqm) {
		  temp_1 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
		  temp = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
		  temp_2 = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)2L ? 
			  TRUEP(T) : TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  temp =  !TRUEP(G2int_deregister_corresponding_objectqm) ?
			   T : Nil;
		  if (temp);
		  else
		      temp = IFIX(ISVREF(G2int_current_icp_socket,
			      (SI_Long)22L)) >= (SI_Long)5L ? T : Nil;
	      }
	      else
		  temp = Nil;
	  }
      }
      else
	  temp = Nil;
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qg2int_deregister_and_register_corresponding_icp_object;  /* deregister-and-register-corresponding-icp-object */

/* SEND-IMMEDIATE-RECLAIM-INDEX-SPACE-MESSAGE */
Object g2int_send_immediate_reclaim_index_space_message(icp_output_port,
	    index_1,index_space_name,ack_p,output_port_p,send_p)
    Object icp_output_port, index_1, index_space_name, ack_p, output_port_p;
    Object send_p;
{
    Object icp_socket, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, index_list, port, icp_socket_1;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(44,34);
    if ( !TRUEP(ack_p) && output_port_p && 
	    G2int_deregister_and_register_item_p) {
	if (send_p) {
	    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
	    if (g2int_icp_connection_open_p(icp_socket) &&  
		    !TRUEP(g2int_icp_connection_being_shutdownqm(icp_socket))) 
			{
		current_icp_port = icp_output_port;
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
					    temp = 
						    ISVREF(G2int_current_icp_socket,
						    (SI_Long)21L);
					    temp_1 = 
						    ISVREF(G2int_current_icp_socket,
						    (SI_Long)22L);
					    if (IFIX(FIXNUM_MIN(temp,
						    temp_1)) >= (SI_Long)13L) {
						index_list = 
							g2int_gensym_cons_1(index_1,
							Nil);
						g2int_send_icp_deregister_icp_objects(index_space_name,
							Qg2int_deregister_and_register_corresponding_icp_object,
							index_list);
						g2int_reclaim_gensym_list_1(index_list);
					    }
					    else
						g2int_send_icp_deregister_corresponding_icp_object(index_1,
							index_space_name);
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
	    }
	}
	port = icp_output_port;
	if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	    temp = Qg2int_standard_icp_object_index_space;
	else if (EQ(index_space_name,Qg2int_item_index_space)) {
	    icp_socket_1 = ISVREF(port,(SI_Long)2L);
	    if (G2int_inhibit_corresponding_icp_object_making)
		temp = Qg2int_standard_icp_object_index_space;
	    else if (Nil) {
		if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		    temp = Qg2int_item_index_space;
		else {
		    temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		    temp = ISVREF(icp_socket_1,(SI_Long)22L);
		    temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)21L ? 
			    Qg2int_item_index_space : 
			    Qg2int_frame_serial_number;
		}
	    }
	    else {
		temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		temp = ISVREF(icp_socket_1,(SI_Long)22L);
		temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)10L ? 
			Qg2int_item_index_space : 
			Qg2int_standard_icp_object_index_space;
	    }
	}
	else if (EQ(index_space_name,Qg2int_frame_serial_number))
	    temp = EQ(ISVREF(port,(SI_Long)3L),Qg2int_output) ? 
		    Qg2int_item_index_space : Qg2int_frame_serial_number;
	else
	    temp = Qg2int_standard_icp_object_index_space;
	if (EQ(temp,Qg2int_standard_icp_object_index_space))
	    temp = ISVREF(icp_output_port,(SI_Long)8L);
	else if (EQ(temp,Qg2int_item_index_space))
	    temp = g2int_item_index_space(icp_output_port);
	else if (EQ(temp,Qg2int_frame_serial_number))
	    temp = g2int_frame_serial_number_to_item_table(icp_output_port);
	else
	    temp = Qnil;
	g2int_deassign_index_in_index_space(index_1,temp);
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_enqueue_reclaim_index_space_message_interval = UNBOUND;

static Object Qg2int_acknowledge_deregister_corresponding_icp_object;  /* acknowledge-deregister-corresponding-icp-object */

static Object Qg2int_deregister_original_icp_object;  /* deregister-original-icp-object */

static Object Qg2int_delete_icp_object_for_process_with_deassign;  /* delete-icp-object-for-process-with-deassign */

static Object Qg2int_delete_icp_object_for_process;  /* delete-icp-object-for-process */

static Object Qg2int_deregister_corresponding_icp_object_with_deassign;  /* deregister-corresponding-icp-object-with-deassign */

static Object Qg2int_deregister_corresponding_icp_object;  /* deregister-corresponding-icp-object */

static Object Qg2int_send_queued_reclaim_index_space_messages;  /* send-queued-reclaim-index-space-messages */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* ENQUEUE-RECLAIM-INDEX-SPACE-MESSAGE */
Object g2int_enqueue_reclaim_index_space_message(icp_output_port,index_1,
	    index_space_name,ack_p,output_port_p,local_p,will_ack_p)
    Object icp_output_port, index_1, index_space_name, ack_p, output_port_p;
    Object local_p, will_ack_p;
{
    Object type, icp_socket, alist, index_space_name_entry, entry, temp;
    Object type_entry, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object schedule_task_qm, future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_11, old_structure_being_reclaimed;
    Object def_structure_schedule_task_variable, task;
    char svref_new_value;
    double temp_1, future_task_schedule_modify_arg_3, aref_new_value;

    x_note_fn_call(44,35);
    if (ack_p)
	type = Qg2int_acknowledge_deregister_corresponding_icp_object;
    else if ( !TRUEP(output_port_p))
	type = Qg2int_deregister_original_icp_object;
    else if (G2int_deregister_and_register_item_p)
	type = Qg2int_deregister_and_register_corresponding_icp_object;
    else if ( !TRUEP(G2int_deregister_corresponding_objectqm))
	type = local_p &&  !TRUEP(will_ack_p) ? 
		Qg2int_delete_icp_object_for_process_with_deassign : 
		Qg2int_delete_icp_object_for_process;
    else
	type = local_p &&  !TRUEP(will_ack_p) ? 
		Qg2int_deregister_corresponding_icp_object_with_deassign : 
		Qg2int_deregister_corresponding_icp_object;
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    alist = ISVREF(icp_socket,(SI_Long)46L);
    index_space_name_entry = g2int_assq_function(index_space_name,alist);
    if (index_space_name_entry);
    else {
	entry = g2int_gensym_cons_1(index_space_name,Nil);
	temp = g2int_gensym_cons_1(entry,alist);
	SVREF(icp_socket,FIX((SI_Long)46L)) = temp;
	index_space_name_entry = entry;
    }
    type_entry = g2int_assq_function(type,CDR(index_space_name_entry));
    if (type_entry);
    else {
	entry = g2int_gensym_cons_1(type,Nil);
	temp = g2int_gensym_cons_1(entry,CDR(index_space_name_entry));
	M_CDR(index_space_name_entry) = temp;
	type_entry = entry;
    }
    gensym_push_modify_macro_arg = index_1;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = CDR(type_entry);
    temp = g2int_gensym_cons_1(car_1,cdr_1);
    M_CDR(type_entry) = temp;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)47L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,G2int_current_schedule_task)))) {
	temp_1 = 
		DOUBLE_FLOAT_TO_DOUBLE(G2int_enqueue_reclaim_index_space_message_interval);
	future_task_schedule_modify_arg_3 = 
		DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L) + temp_1;
	future_task_schedule_modify_arg_8 = 
		SYMBOL_FUNCTION(Qg2int_send_queued_reclaim_index_space_messages);
	future_task_schedule_modify_arg_11 = icp_socket;
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qg2int_send_queued_reclaim_index_space_messages;
	SVREF(task,FIX((SI_Long)8L)) = future_task_schedule_modify_arg_8;
	ISVREF(task,(SI_Long)10L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)11L)) = future_task_schedule_modify_arg_11;
	g2int_future_task_schedule_2(task);
	SVREF(icp_socket,FIX((SI_Long)47L)) = task;
    }
    return VALUES_1(Nil);
}

/* SEND-QUEUED-RECLAIM-INDEX-SPACE-MESSAGES */
Object g2int_send_queued_reclaim_index_space_messages(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;
    Object current_icp_socket, icp_output_port, icp_objects_alist;
    Object index_space_element, ab_loop_list_, index_space_name, type_alist;
    Object element, ab_loop_list__1, type, type_index_list, index_list;
    Object current_icp_port, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, index_list_tail, next_index_list, index_1;
    Object index_list_old_value, port, actual_index_space_name, icp_socket_1;
    Object index_space, ab_loop_list__2;
    SI_Long i;
    double gensymed_symbol_1;
    Declare_special(13);

    x_note_fn_call(44,36);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)47L);
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
    SVREF(icp_socket,FIX((SI_Long)47L)) = svref_new_value;
    current_icp_socket = icp_socket;
    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,12);
      icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
      icp_objects_alist = ISVREF(icp_socket,(SI_Long)46L);
      index_space_element = Nil;
      ab_loop_list_ = icp_objects_alist;
      index_space_name = Nil;
      type_alist = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      index_space_element = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      index_space_name = CAR(index_space_element);
      type_alist = CDR(index_space_element);
      g2int_reclaim_gensym_cons_1(index_space_element);
      element = Nil;
      ab_loop_list__1 = type_alist;
      type = Nil;
      type_index_list = Nil;
      index_list = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      element = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      type = CAR(element);
      type_index_list = CDR(element);
      index_list = type_index_list;
      g2int_reclaim_gensym_cons_1(element);
      if (g2int_icp_connection_open_p(icp_socket) &&  
	      !TRUEP(g2int_icp_connection_being_shutdownqm(icp_socket))) {
	next_loop_2:
	  if ( !TRUEP(index_list))
	      goto end_loop_2;
	  current_icp_port = icp_output_port;
	  PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	    current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	      temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		      >= (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
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
					      ISVREF(G2int_current_icp_socket,
					      (SI_Long)21L);
				      temp_1 = 
					      ISVREF(G2int_current_icp_socket,
					      (SI_Long)22L);
				      if (IFIX(FIXNUM_MIN(temp,temp_1)) >= 
					      (SI_Long)13L) {
					  index_list_tail = 
						  nthcdr(FIX((SI_Long)199L),
						  index_list);
					  next_index_list = 
						  CDR(index_list_tail);
					  if (index_list_tail)
					      M_CDR(index_list_tail) = Nil;
					  g2int_send_icp_deregister_icp_objects(index_space_name,
						  type,index_list);
					  if (index_list_tail)
					      M_CDR(index_list_tail) = 
						      next_index_list;
					  index_list = next_index_list;
				      }
				      else {
					  i = (SI_Long)0L;
					  index_1 = Nil;
					next_loop_3:
					  if (i >= (SI_Long)200L)
					      goto end_loop_3;
					  if ( !(index_list && 
						  g2int_icp_connection_open_p(icp_socket) 
						  &&  
						  !TRUEP(g2int_icp_connection_being_shutdownqm(icp_socket))))
					      goto end_loop_3;
					  index_list_old_value = index_list;
					  temp = FIRST(index_list_old_value);
					  index_list = 
						  REST(index_list_old_value);
					  index_1 = temp;
					  if (EQ(type,
						  Qg2int_acknowledge_deregister_corresponding_icp_object))
					      g2int_send_icp_acknowledge_deregister_corresponding_icp_object(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qg2int_deregister_original_icp_object))
					      g2int_send_icp_deregister_original_icp_object(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qg2int_delete_icp_object_for_process) 
						  || EQ(type,
						  Qg2int_delete_icp_object_for_process_with_deassign))
					      g2int_send_icp_delete_icp_object_for_process(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qg2int_deregister_corresponding_icp_object) 
						  || EQ(type,
						  Qg2int_deregister_corresponding_icp_object_with_deassign) 
						  || EQ(type,
						  Qg2int_deregister_and_register_corresponding_icp_object))
					      g2int_send_icp_deregister_corresponding_icp_object(index_1,
						      index_space_name);
					  i = i + (SI_Long)1L;
					  goto next_loop_3;
					end_loop_3:;
				      }
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
	  goto next_loop_2;
	end_loop_2:;
      }
      if (EQ(type,Qg2int_delete_icp_object_for_process_with_deassign) || 
	      EQ(type,
	      Qg2int_deregister_corresponding_icp_object_with_deassign)) {
	  port = icp_output_port;
	  if (EQ(index_space_name,Qg2int_standard_icp_object_index_space))
	      actual_index_space_name = Qg2int_standard_icp_object_index_space;
	  else if (EQ(index_space_name,Qg2int_item_index_space)) {
	      icp_socket_1 = ISVREF(port,(SI_Long)2L);
	      if (G2int_inhibit_corresponding_icp_object_making)
		  actual_index_space_name = 
			  Qg2int_standard_icp_object_index_space;
	      else if (Nil) {
		  if (EQ(ISVREF(port,(SI_Long)3L),Qg2int_output))
		      actual_index_space_name = Qg2int_item_index_space;
		  else {
		      temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		      temp = ISVREF(icp_socket_1,(SI_Long)22L);
		      actual_index_space_name = IFIX(FIXNUM_MIN(temp_1,
			      temp)) >= (SI_Long)21L ? 
			      Qg2int_item_index_space : 
			      Qg2int_frame_serial_number;
		  }
	      }
	      else {
		  temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		  temp = ISVREF(icp_socket_1,(SI_Long)22L);
		  actual_index_space_name = IFIX(FIXNUM_MIN(temp_1,temp)) 
			  >= (SI_Long)10L ? Qg2int_item_index_space : 
			  Qg2int_standard_icp_object_index_space;
	      }
	  }
	  else if (EQ(index_space_name,Qg2int_frame_serial_number))
	      actual_index_space_name = EQ(ISVREF(port,(SI_Long)3L),
		      Qg2int_output) ? Qg2int_item_index_space : 
		      Qg2int_frame_serial_number;
	  else
	      actual_index_space_name = Qg2int_standard_icp_object_index_space;
	  if ( !EQ(actual_index_space_name,Qg2int_frame_serial_number)) {
	      if (EQ(actual_index_space_name,
		      Qg2int_standard_icp_object_index_space))
		  index_space = ISVREF(icp_output_port,(SI_Long)8L);
	      else if (EQ(actual_index_space_name,Qg2int_item_index_space))
		  index_space = g2int_item_index_space(icp_output_port);
	      else if (EQ(actual_index_space_name,Qg2int_frame_serial_number))
		  index_space = 
			  g2int_frame_serial_number_to_item_table(icp_output_port);
	      else
		  index_space = Qnil;
	      index_1 = Nil;
	      ab_loop_list__2 = type_index_list;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list__2))
		  goto end_loop_4;
	      index_1 = M_CAR(ab_loop_list__2);
	      ab_loop_list__2 = M_CDR(ab_loop_list__2);
	      g2int_deassign_index_in_index_space(index_1,index_space);
	      goto next_loop_4;
	    end_loop_4:;
	  }
      }
      g2int_reclaim_gensym_list_1(type_index_list);
      goto next_loop_1;
    end_loop_1:;
      g2int_reclaim_gensym_list_1(type_alist);
      goto next_loop;
    end_loop:
      g2int_reclaim_gensym_list_1(icp_objects_alist);
      SVREF(icp_socket,FIX((SI_Long)46L)) = Nil;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* REMOVE-ICP-OBJECT-FROM-INDEX-SPACE */
Object g2int_remove_icp_object_from_index_space(icp_object,icp_port,
	    index_1,name_of_corresponding_icp_object_index_space)
    Object icp_object, icp_port, index_1;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(44,37);
    return g2int_set_in_icp_port(icp_port,index_1,
	    name_of_corresponding_icp_object_index_space,Nil);
}

static Object Qg2int_send_icp_shut_down_data_server;  /* send-icp-shut-down-data-server */

static Object string_constant_7;   /* "resumable icp synch error: ~S expected, ~S found" */

/* SEND-ICP-SHUT-DOWN-DATA-SERVER */
Object g2int_send_icp_shut_down_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,38);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_shut_down_data_server;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)70L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_shut_down_data_server,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_7,
			Qg2int_send_icp_shut_down_data_server,top,Nil);
		goto end_send_icp_shut_down_data_server;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_shut_down_data_server;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)70L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_shut_down_data_server);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_shut_down_data_server;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_shut_down_data_server:
    return result;
}

static Object Qg2int_received_shutdown_request;  /* received-shutdown-request */

/* HANDLE-ICP-SHUT-DOWN-DATA-SERVER--BODY */
Object g2int_handle_icp_shut_down_data_server__body()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(44,39);
    index_of_top_of_backtrace_stack = G2int_index_of_top_of_backtrace_stack;
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
	  SVREF(temp,svref_arg_2) = Qg2int_received_shutdown_request;
      }
      g2int_acknowledge_shutdown(G2int_current_icp_socket);
      g2int_shutdown_icp_socket_connection(1,G2int_current_icp_socket);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_shut_down_data_server;  /* handle-icp-shut-down-data-server */

/* HANDLE-ICP-SHUT-DOWN-DATA-SERVER */
Object g2int_handle_icp_shut_down_data_server()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(44,40);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_shut_down_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_shut_down_data_server,top))
		return g2int_icp_error_internal(Qerror,string_constant_7,
			Qg2int_handle_icp_shut_down_data_server,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_shut_down_data_server__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* ACKNOWLEDGE-SHUTDOWN */
Object g2int_acknowledge_shutdown(icp_socket)
    Object icp_socket;
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

    x_note_fn_call(44,41);
    if (g2int_icp_connection_open_p(icp_socket) && ISVREF(icp_socket,
	    (SI_Long)20L)) {
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
				    g2int_send_icp_acknowledge_shutdown();
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
    }
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_acknowledge_shutdown;  /* send-icp-acknowledge-shutdown */

/* SEND-ICP-ACKNOWLEDGE-SHUTDOWN */
Object g2int_send_icp_acknowledge_shutdown()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,42);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_acknowledge_shutdown;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)336L));
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_acknowledge_shutdown,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant_7,
			Qg2int_send_icp_acknowledge_shutdown,top,Nil);
		goto end_send_icp_acknowledge_shutdown;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_acknowledge_shutdown;
	  }
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)336L)))) {
	      g2int_resumable_icp_push(Qg2int_send_icp_acknowledge_shutdown);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_acknowledge_shutdown;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_acknowledge_shutdown:
    return result;
}

/* HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN--BODY */
Object g2int_handle_icp_acknowledge_shutdown__body()
{
    x_note_fn_call(44,43);
    g2int_shutdown_icp_socket_connection(1,G2int_current_icp_socket);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_acknowledge_shutdown;  /* handle-icp-acknowledge-shutdown */

/* HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN */
Object g2int_handle_icp_acknowledge_shutdown()
{
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(44,44);
    if (G2int_disable_resumability) {
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_acknowledge_shutdown__body();
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_acknowledge_shutdown,top))
		return g2int_icp_error_internal(Qerror,string_constant_7,
			Qg2int_handle_icp_acknowledge_shutdown,top,Nil);
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_acknowledge_shutdown__body();
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_in_recursive_gsi_context = UNBOUND;

/* SHUTDOWN-ICP-SOCKET-CONNECTION */
Object g2int_shutdown_icp_socket_connection varargs_1(int, n)
{
    Object icp_socket;
    Object reason_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,45);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    reason_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),G2int_icp_connection_closed))
	return VALUES_1(Nil);
    if ( !TRUEP(ISVREF(icp_socket,(SI_Long)9L)))
	SVREF(icp_socket,FIX((SI_Long)9L)) = reason_qm;
    g2int_close_and_disconnect_icp_socket_handle(icp_socket);
    if ( !EQ(icp_socket,G2int_icp_socket_transacting_message_group) || 
	    G2int_in_recursive_gsi_context)
	return g2int_finalize_and_reclaim_icp_socket(icp_socket);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_time_out_icp_socket;  /* time-out-icp-socket */

static Object Qg2int_shutdown_timed_out_awaiting_acknowledgement;  /* shutdown-timed-out-awaiting-acknowledgement */

static Object Qg2int_shutdown_icp_socket_after_connect;  /* shutdown-icp-socket-after-connect */

/* FLUSH-AND-SHUTDOWN-ICP-SOCKET */
Object g2int_flush_and_shutdown_icp_socket(icp_socket)
    Object icp_socket;
{
    Object schedule_task_qm, old_structure_being_reclaimed, temp;
    Object current_icp_port, current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_11;
    Object def_structure_schedule_task_variable, task;
    char svref_new_value;
    double gensymed_symbol_1, future_task_schedule_modify_arg_3;
    double aref_new_value;
    Declare_special(12);

    x_note_fn_call(44,46);
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)16L);
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
	temp = G2int_chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_schedule_tasks = schedule_task_qm;
    }
    temp = Nil;
    SVREF(icp_socket,FIX((SI_Long)16L)) = temp;
    if (g2int_icp_connection_open_p(icp_socket)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,11);
	  current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,10);
	    temp_1 = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		    >= (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		    (SI_Long)53L) : Nil;
	    if (temp_1);
	    else
		temp_1 = Nil;
	    disable_resumability = temp_1;
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
	if (g2int_icp_connection_open_p(icp_socket)) {
	    if (ISVREF(icp_socket,(SI_Long)20L)) {
		temp = G2int_icp_connection_awaiting_acknowledgement;
		SVREF(icp_socket,FIX((SI_Long)15L)) = temp;
		g2int_execute_icp_connection_loss_callbacks(icp_socket,T);
		future_task_schedule_modify_arg_3 = 
			DFLOAT_ISAREF_1(G2int_current_real_time,
			(SI_Long)0L) + 
			(double)IFIX(G2int_icp_socket_shutdown_handshake_timeout);
		future_task_schedule_modify_arg_8 = 
			SYMBOL_FUNCTION(Qg2int_time_out_icp_socket);
		future_task_schedule_modify_arg_11 = icp_socket;
		schedule_task_qm = ISVREF(icp_socket,(SI_Long)36L);
		if (schedule_task_qm) {
		    if (EQ(schedule_task_qm,G2int_current_schedule_task))
			G2int_current_schedule_task = Nil;
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    inline_note_reclaim_cons(schedule_task_qm,Nil);
		    old_structure_being_reclaimed = 
			    G2int_structure_being_reclaimed;
		    G2int_structure_being_reclaimed = schedule_task_qm;
		    g2int_reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			    (SI_Long)9L));
		    SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		    G2int_structure_being_reclaimed = 
			    old_structure_being_reclaimed;
		    temp = G2int_chain_of_available_schedule_tasks;
		    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
		    G2int_chain_of_available_schedule_tasks = schedule_task_qm;
		}
		def_structure_schedule_task_variable = 
			G2int_chain_of_available_schedule_tasks;
		if (def_structure_schedule_task_variable) {
		    G2int_chain_of_available_schedule_tasks = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_schedule_task_g2_struct;
		}
		else
		    def_structure_schedule_task_variable = 
			    g2int_make_permanent_schedule_task_structure_internal();
		inline_note_allocate_cons(def_structure_schedule_task_variable,
			Nil);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		DFLOAT_ISASET_1(temp,(SI_Long)0L,
			future_task_schedule_modify_arg_3);
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
		svref_new_value =  !TRUEP(T);
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
		ISVREF(task,(SI_Long)4L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = Qg2int_time_out_icp_socket;
		SVREF(task,FIX((SI_Long)8L)) = 
			future_task_schedule_modify_arg_8;
		ISVREF(task,(SI_Long)10L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)11L)) = 
			future_task_schedule_modify_arg_11;
		SVREF(task,FIX((SI_Long)12L)) = 
			Qg2int_shutdown_timed_out_awaiting_acknowledgement;
		g2int_future_task_schedule_2(task);
		return VALUES_1(SVREF(icp_socket,FIX((SI_Long)36L)) = task);
	    }
	    else
		return g2int_shutdown_icp_socket_connection(1,icp_socket);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (g2int_icp_connection_in_progress_p(icp_socket)) {
	g2int_deregister_all_icp_connect_callbacks(icp_socket);
	return g2int_register_icp_connect_callback(Qg2int_shutdown_icp_socket_after_connect,
		icp_socket);
    }
    else
	return VALUES_1(Qnil);
}

/* SHUTDOWN-ICP-SOCKET-AFTER-CONNECT */
Object g2int_shutdown_icp_socket_after_connect(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(44,47);
    g2int_flush_and_shutdown_icp_socket(icp_socket);
    return VALUES_1(Nil);
}

/* TIME-OUT-ICP-SOCKET */
Object g2int_time_out_icp_socket(icp_socket,reason)
    Object icp_socket, reason;
{
    x_note_fn_call(44,48);
    g2int_shutdown_icp_socket_connection(2,icp_socket,reason);
    return VALUES_1(Nil);
}

/* CLOSE-AND-DISCONNECT-ALL-SOCKETS */
Object g2int_close_and_disconnect_all_sockets()
{
    Object list_1, icp_socket, next_list, current_icp_port, current_icp_socket;
    Object temp, disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1;
    Declare_special(12);

    x_note_fn_call(44,49);
    list_1 = G2int_active_icp_sockets;
    icp_socket = Nil;
    next_list = Nil;
  next_loop:
    icp_socket = CAR(list_1);
    next_list = CDR(list_1);
    if ( !TRUEP(list_1))
	goto end_loop;
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),
	    G2int_icp_connection_running)) {
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
				    if (IFIX(ISVREF(G2int_current_icp_socket,
					    (SI_Long)22L)) >= (SI_Long)5L)
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
    }
    list_1 = next_list;
    goto next_loop;
  end_loop:
    goto end;
  end:;
    g2int_flush_icp_output_ports();
    list_1 = G2int_active_icp_sockets;
    icp_socket = Nil;
    next_list = Nil;
  next_loop_1:
    icp_socket = CAR(list_1);
    next_list = CDR(list_1);
    if ( !TRUEP(list_1))
	goto end_loop_1;
    g2int_close_and_disconnect_icp_socket_handle(icp_socket);
    list_1 = next_list;
    goto next_loop_1;
  end_loop_1:
    goto end_1;
  end_1:;
    G2int_active_icp_sockets = Nil;
    return VALUES_1(Nil);
}

Object G2int_check_icp_handshaking_p = UNBOUND;

Object G2int_icp_handshake_registry = UNBOUND;

void int4_INIT()
{
    Object AB_package, Qg2int_acknowledge_shutdown;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, float_constant;
    Object Qg2int_remove_icp_port_entries_from_icp_object_list;
    Object Qg2int_remove_icp_port_entries_from_icp_object, Qg2int_int4;
    Object Qg2int_system_window_title_and_info_text_stringqm;
    Object Qg2int_generic_listener_initializedqm, list_constant_1;
    Object Qg2int_get_unix_host_name;

    x_note_fn_call(44,50);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_do_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~a:~(~a~):~a");
    Qg2int_vms_process = STATIC_SYMBOL("VMS-PROCESS",AB_package);
    Qg2int_localnet = STATIC_SYMBOL("LOCALNET",AB_package);
    Qg2int_g2 = STATIC_SYMBOL("G2",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qg2int_generic = STATIC_SYMBOL("GENERIC",AB_package);
    string_constant_1 = STATIC_STRING("~a");
    Qg2int_default = STATIC_SYMBOL("DEFAULT",AB_package);
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qg2int_get_unix_host_name = STATIC_SYMBOL("GET-UNIX-HOST-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_get_unix_host_name,
	    STATIC_FUNCTION(g2int_get_unix_host_name,NIL,FALSE,0,0));
    G2int_icp_connection_succeeded_tag = FIX((SI_Long)1L);
    G2int_icp_connection_failed_tag = FIX((SI_Long)-1L);
    G2int_icp_noop_network_code_accessed = FIX((SI_Long)-2L);
    Qg2int_icp_connection_loss_notifier = 
	    STATIC_SYMBOL("ICP-CONNECTION-LOSS-NOTIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_icp_connection_loss_notifier,
	    STATIC_FUNCTION(g2int_icp_connection_loss_notifier,NIL,FALSE,2,2));
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    list_constant = STATIC_LIST((SI_Long)2L,Qnil,Kdefault);
    string_constant_2 = 
	    STATIC_STRING("ERROR: Could not make exact ICP connection~%");
    Qg2int_register_icp_connection_loss_callback_function = 
	    STATIC_SYMBOL("REGISTER-ICP-CONNECTION-LOSS-CALLBACK-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_register_icp_connection_loss_callback_function,
	    STATIC_FUNCTION(g2int_register_icp_connection_loss_callback_function,
	    NIL,FALSE,2,2));
    string_constant_3 = 
	    STATIC_STRING("ERROR: DECnet not supported by this product on this platform");
    Qg2int_generic_listener_initializedqm = 
	    STATIC_SYMBOL("GENERIC-LISTENER-INITIALIZED\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_generic_listener_initializedqm,
	    G2int_generic_listener_initializedqm);
    Qg2int_int4 = STATIC_SYMBOL("INT4",AB_package);
    g2int_record_system_variable(Qg2int_generic_listener_initializedqm,
	    Qg2int_int4,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_4 = STATIC_STRING("host: ~a~%");
    string_constant_5 = STATIC_STRING("~a~a: ~a~a~%");
    Knetwork_type = STATIC_SYMBOL("NETWORK-TYPE",Pkeyword);
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    string_constant_6 = 
	    STATIC_STRING("WARNING: Could not make ICP connection~%");
    Qg2int_system_window_title_and_info_text_stringqm = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-AND-INFO-TEXT-STRING\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_system_window_title_and_info_text_stringqm,
	    G2int_system_window_title_and_info_text_stringqm);
    g2int_record_system_variable(Qg2int_system_window_title_and_info_text_stringqm,
	    Qg2int_int4,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_localnet_handle = STATIC_SYMBOL("LOCALNET-HANDLE",AB_package);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    if (G2int_gsi_throw_to_run_loop_may_be_harmful_p == UNBOUND)
	G2int_gsi_throw_to_run_loop_may_be_harmful_p = Nil;
    if (G2int_icp_socket_for_reclaimqm == UNBOUND)
	G2int_icp_socket_for_reclaimqm = Nil;
    Qg2int_gsi_instance = STATIC_SYMBOL("GSI-INSTANCE",AB_package);
    Qg2int_item_with_handle_index_space = 
	    STATIC_SYMBOL("ITEM-WITH-HANDLE-INDEX-SPACE",AB_package);
    Qg2int_input = STATIC_SYMBOL("INPUT",AB_package);
    Qg2int_reclaimer_for_icp_port_entry = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-PORT-ENTRY",AB_package);
    Qg2int_shutdown_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("SHUTDOWN-RECLAIMER-FOR-ICP-OBJECT",AB_package);
    Qg2int_remove_icp_port_entries_from_icp_object = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_remove_icp_port_entries_from_icp_object,
	    STATIC_FUNCTION(g2int_remove_icp_port_entries_from_icp_object,
	    NIL,FALSE,3,3));
    Qg2int_remove_icp_port_entries_from_icp_object_list = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_remove_icp_port_entries_from_icp_object_list,
	    STATIC_FUNCTION(g2int_remove_icp_port_entries_from_icp_object_list,
	    NIL,FALSE,3,3));
    Qg2int_output = STATIC_SYMBOL("OUTPUT",AB_package);
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_item_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qg2int_frame_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",
	    AB_package);
    Qg2int_deregister_and_register_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-AND-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    float_constant = STATIC_FLOAT(0.25);
    G2int_enqueue_reclaim_index_space_message_interval = float_constant;
    Qg2int_acknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qg2int_deregister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    Qg2int_delete_icp_object_for_process_with_deassign = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS-WITH-DEASSIGN",
	    AB_package);
    Qg2int_delete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    Qg2int_deregister_corresponding_icp_object_with_deassign = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-WITH-DEASSIGN",
	    AB_package);
    Qg2int_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    Qg2int_send_queued_reclaim_index_space_messages = 
	    STATIC_SYMBOL("SEND-QUEUED-RECLAIM-INDEX-SPACE-MESSAGES",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_queued_reclaim_index_space_messages,
	    STATIC_FUNCTION(g2int_send_queued_reclaim_index_space_messages,
	    NIL,FALSE,1,1));
    Qg2int_send_icp_shut_down_data_server = 
	    STATIC_SYMBOL("SEND-ICP-SHUT-DOWN-DATA-SERVER",AB_package);
    string_constant_7 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_shut_down_data_server,
	    STATIC_FUNCTION(g2int_send_icp_shut_down_data_server,NIL,FALSE,
	    0,0));
    Qg2int_received_shutdown_request = 
	    STATIC_SYMBOL("RECEIVED-SHUTDOWN-REQUEST",AB_package);
    Qg2int_handle_icp_shut_down_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-SHUT-DOWN-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_shut_down_data_server,
	    STATIC_FUNCTION(g2int_handle_icp_shut_down_data_server,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_shut_down_data_server,
	    FIX((SI_Long)70L));
    Qg2int_acknowledge_shutdown = STATIC_SYMBOL("ACKNOWLEDGE-SHUTDOWN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_acknowledge_shutdown,
	    STATIC_FUNCTION(g2int_acknowledge_shutdown,NIL,FALSE,1,1));
    Qg2int_send_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("SEND-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_acknowledge_shutdown,
	    STATIC_FUNCTION(g2int_send_icp_acknowledge_shutdown,NIL,FALSE,
	    0,0));
    Qg2int_handle_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_acknowledge_shutdown,
	    STATIC_FUNCTION(g2int_handle_icp_acknowledge_shutdown,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_acknowledge_shutdown,
	    FIX((SI_Long)336L));
    if (G2int_in_recursive_gsi_context == UNBOUND)
	G2int_in_recursive_gsi_context = Nil;
    Qg2int_time_out_icp_socket = STATIC_SYMBOL("TIME-OUT-ICP-SOCKET",
	    AB_package);
    Qg2int_shutdown_timed_out_awaiting_acknowledgement = 
	    STATIC_SYMBOL("SHUTDOWN-TIMED-OUT-AWAITING-ACKNOWLEDGEMENT",
	    AB_package);
    Qg2int_shutdown_icp_socket_after_connect = 
	    STATIC_SYMBOL("SHUTDOWN-ICP-SOCKET-AFTER-CONNECT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_shutdown_icp_socket_after_connect,
	    STATIC_FUNCTION(g2int_shutdown_icp_socket_after_connect,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2int_time_out_icp_socket,
	    STATIC_FUNCTION(g2int_time_out_icp_socket,NIL,FALSE,2,2));
    if (G2int_check_icp_handshaking_p == UNBOUND)
	G2int_check_icp_handshaking_p = Nil;
    G2int_icp_handshake_registry = Nil;
}
