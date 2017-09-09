/* int4.c
 * Input file:  int4.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "int4.h"


static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~a:~(~a~):~a" */

/* MAKE-NETWORK-PATHNAME */
Object make_network_pathname(icp_connection_configuration)
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

    x_note_fn_call(53,0);
    protocol = FIRST(icp_connection_configuration);
    host = SECOND(icp_connection_configuration);
    listener = THIRD(icp_connection_configuration);
    local_string = SYMBOLP(protocol) ? symbol_name_text_string(protocol) : 
	    protocol;
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
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(lengthw(local_string));
	      c = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      c = FIX(UBYTE_16_ISAREF_1(local_string,i));
	      simple_or_wide_character = (SI_Long)45L == IFIX(c) ? 
		      FIX((SI_Long)95L) : c;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = simple_or_wide_character;
		  twrite_wide_character(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = simple_or_wide_character;
		  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
			  CHAR_CODE(thing) : thing);
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      modified_protocol = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_1 = tformat_text_string(4,string_constant,modified_protocol,host,
	    listener);
    reclaim_text_string(modified_protocol);
    return VALUES_1(temp_1);
}

static Object Qvms_process;        /* vms-process */

static Object Qlocalnet;           /* localnet */

static Object Qg2;                 /* g2 */

/* MAKE-ICP-CONNECTION */
Object make_icp_connection varargs_1(int, n)
{
    Object icp_connection_configuration;
    Object remote_system_name, application_name, connect_timeout, temp_1;
    Object temp_2, code, thing, icp_socket;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,1);
    INIT_ARGS_nonrelocating();
    icp_connection_configuration = REQUIRED_ARG_nonrelocating();
    remote_system_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    application_name = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = EQ(Qvms_process,FIRST(icp_connection_configuration));
    if (temp);
    else
	temp = EQ(Qlocalnet,FIRST(icp_connection_configuration));
    if (temp);
    else {
	temp_1 = get_local_host_name();
	temp_2 = SECOND(icp_connection_configuration);
	temp = EQUAL(temp_1,temp_2);
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Listed_continuation_servers));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)4L) != (SI_Long)0L ?
		 TRUEP(M_CAR(M_CDR(Cache_icp_semantics_graph))) : TRUEP(Nil);
    }
    if (temp) {
	if (EQ(Qlocalnet,CAR(icp_connection_configuration))) {
	    thing = SECOND(icp_connection_configuration);
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != 
		    (SI_Long)0L ? copy_text_string(thing) : thing;
	    temp_2 = remote_system_name;
	    if (temp_2);
	    else
		temp_2 = Qg2;
	    icp_socket = make_localnet_connection(3,temp_1,temp_2,
		    connect_timeout);
	}
	else
	    icp_socket = make_network_connection(2,
		    icp_connection_configuration,connect_timeout);
	if (icp_socket) {
	    SVREF(icp_socket,FIX((SI_Long)52L)) = application_name;
	    return VALUES_1(icp_socket);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	parse_icp_schedule_tree();
	return VALUES_1(Nil);
    }
}

/* TIME-INTERVAL-ELAPSED-P */
Object time_interval_elapsed_p(time_interval_limit,start_time)
    Object time_interval_limit, start_time;
{
    x_note_fn_call(53,2);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* GET-TCPIP-LISTENER-SPECIFICATION */
Object get_tcpip_listener_specification()
{
    Object specific_network_transport_types_qm;
    Object specific_network_transport_type, ab_loop_list_, ab_loop_it_;
    Object tcpip_transport_type_specified_p, temp;

    x_note_fn_call(53,3);
    specific_network_transport_types_qm = 
	    get_all_command_line_keyword_arguments(array_constant);
    specific_network_transport_type = Nil;
    ab_loop_list_ = specific_network_transport_types_qm;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    specific_network_transport_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = string_equalw(specific_network_transport_type,
	    array_constant_1);
    if (ab_loop_it_) {
	tcpip_transport_type_specified_p = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    tcpip_transport_type_specified_p = Qnil;
  end_1:;
    if ( !TRUEP(specific_network_transport_types_qm) || 
	    tcpip_transport_type_specified_p) {
	temp = get_command_line_keyword_argument_as_integer(1,
		array_constant_2);
	if (temp);
	else
	    temp = 
		    read_number_for_gensym_environment_variable(array_constant_3);
	if (temp);
	else
	    temp = Kdefault;
    }
    else
	temp = Nil;
    reclaim_gensym_list_1(specific_network_transport_types_qm);
    return VALUES_1(temp);
}

static Object Qgeneric;            /* generic */

/* MAKE-AND-INSTALL-NETWORK-ICP-SOCKET */
Object make_and_install_network_icp_socket varargs_1(int, n)
{
    Object input_connection_handle, output_connection_handle;
    Object external_process_name, initially_open_p;
    Object parent_listener_qm, connect_timeout, icp_socket;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,4);
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
    icp_socket = make_icp_socket(external_process_name,Qgeneric,
	    input_connection_handle,output_connection_handle,Nil,T,
	    initially_open_p,parent_listener_qm,Current_system_name,
	    connect_timeout);
    register_socket_to_handle(icp_socket,input_connection_handle);
    add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

/* MAKE-AND-INSTALL-NETWORK-LISTENER */
Object make_and_install_network_listener(listener_handle,network_address)
    Object listener_handle, network_address;
{
    Object icp_socket, svref_new_value;

    x_note_fn_call(53,5);
    icp_socket = make_icp_socket(network_address,Qgeneric,listener_handle,
	    Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    svref_new_value = Icp_socket_listening;
    SVREF(icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    register_socket_to_handle(icp_socket,listener_handle);
    add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

static Object string_constant_1;   /* "~a" */

static Object Qdefault;            /* default */

/* MAKE-NETWORK-CONNECTION */
Object make_network_connection varargs_1(int, n)
{
    Object connection_configuration;
    Object connect_timeout, network_pathname, port_string, secure_p;
    Object connection_handle, nascent_socket, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,6);
    INIT_ARGS_nonrelocating();
    connection_configuration = REQUIRED_ARG_nonrelocating();
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    network_pathname = make_network_pathname(connection_configuration);
    port_string = tformat_text_string(2,string_constant_1,
	    THIRD(connection_configuration));
    secure_p = FIXNUM_GT(length(connection_configuration),
	    FIX((SI_Long)3L)) ? (EQ(FOURTH(connection_configuration),
	    Qdefault) ? Nil : FOURTH(connection_configuration)) : 
	    Secure_icp_default_p;
    connection_handle = network_connect(4,network_pathname,
	    SECOND(connection_configuration),port_string,secure_p);
    reclaim_text_string(port_string);
    if ( !(IFIX(connection_handle) >= (SI_Long)0L)) {
	reclaim_text_string(network_pathname);
	return VALUES_1(Nil);
    }
    nascent_socket = make_and_install_network_icp_socket(6,
	    connection_handle,connection_handle,network_pathname,T,Nil,
	    connect_timeout);
    svref_new_value = Icp_connection_connect_in_progress;
    SVREF(nascent_socket,FIX((SI_Long)15L)) = svref_new_value;
    return VALUES_1(nascent_socket);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* SETUP-NETWORK-CONNECTION-FOR-CONNECT */
Object setup_network_connection_for_connect varargs_1(int, n)
{
    Object icp_socket;
    Object user_connect_callback, temp, connection_handle, gensymed_symbol;
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,7);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    user_connect_callback = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (icp_socket && EQ(ISVREF(icp_socket,(SI_Long)15L),
	    Icp_connection_connect_in_progress)) {
	if (user_connect_callback)
	    register_icp_connect_callback(user_connect_callback,icp_socket);
	temp = ISVREF(icp_socket,(SI_Long)1L);
	if (EQ(temp,Qlocalnet))
	    handle_icp_connect(icp_socket);
	else if (EQ(temp,Qgeneric)) {
	    connection_handle = ISVREF(ISVREF(icp_socket,(SI_Long)3L),
		    (SI_Long)1L);
	    if ( !((SI_Long)0L == ne_connected_p(IFIX(connection_handle)))) {
		gensymed_symbol = ISVREF(icp_socket,(SI_Long)0L);
		gensymed_symbol = 
			ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
			Qtype_description_of_unique_type_name_of_gensym_structure),
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
Object get_accept_pathname(accept_handle)
    Object accept_handle;
{
    Object result_code;

    x_note_fn_call(53,8);
    result_code = c_get_connection_pathname(accept_handle,
	    Gensym_environment_variable_buffer,FIX((SI_Long)1023L));
    if ( !(FIXNUMP(result_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    result_code) && FIXNUM_LE(result_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(result_code)) {
	  case 1:
	    return copy_null_terminated_string_as_text_string(Gensym_environment_variable_buffer);
	  case -1:
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
}

/* GET-NETWORK-LISTENER */
Object get_network_listener(position_1)
    Object position_1;
{
    Object listener_buffer_as_simple_gensym_string, length_1, temp;
    SI_Long buffer_size;

    x_note_fn_call(53,9);
    buffer_size = (SI_Long)300L;
    listener_buffer_as_simple_gensym_string = 
	    obtain_simple_gensym_string(FIX(buffer_size));
    length_1 = c_get_network_listener(position_1,
	    listener_buffer_as_simple_gensym_string,FIX(buffer_size));
    temp = (SI_Long)0L < IFIX(length_1) ? 
	    copy_partial_text_string(listener_buffer_as_simple_gensym_string,
	    length_1) : Nil;
    reclaim_gensym_string(listener_buffer_as_simple_gensym_string);
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

/* GET-LOCAL-HOST-ADDRESSES */
Object get_local_host_addresses()
{
    Object listeners, listener, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object c, thing, temp, schar_arg_2, schar_new_value, temp_1;
    Object delimiter_count, temp_2;
    SI_Long listener_count, listener_pos, ab_loop_bind_, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1, i, ab_loop_bind__1, j;
    Declare_special(5);

    x_note_fn_call(53,10);
    listener_count = g2ext_network_listener_count();
    listeners = Nil;
    listener_pos = (SI_Long)0L;
    ab_loop_bind_ = listener_count;
    listener = Nil;
  next_loop:
    if (listener_pos >= ab_loop_bind_)
	goto end_loop;
    listener = get_network_listener(FIX(listener_pos));
    if (listener) {
	if ( !TRUEP(string_eq_w(listener,array_constant_4))) {
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
		      ab_loop_bind__1 = IFIX(lengthw(listener));
		      c = Nil;
		    next_loop_1:
		      if (i >= ab_loop_bind__1)
			  goto end_loop_1;
		      c = FIX(UBYTE_16_ISAREF_1(listener,i));
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
		      i = i + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      ab_loop_bind__1 = IFIX(lengthw(listener));
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
		      ab_loop_bind__1 = IFIX(lengthw(listener));
		      c = Nil;
		    next_loop_3:
		      if (j >= ab_loop_bind__1)
			  goto end_loop_3;
		      c = FIX(UBYTE_16_ISAREF_1(listener,j));
		      if (IFIX(c) == (SI_Long)58L)
			  goto end_loop_3;
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
		      goto next_loop_3;
		    end_loop_3:;
		      temp_2 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_1 = gensym_list_3(temp_1,temp_2,
		    g2ext_secure_socket_p(ne_get_listener_handle(listener_pos)) 
		    == (SI_Long)1L ? T : Nil);
	    listeners = gensym_cons_1(temp_1,listeners);
	}
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(listener) != (SI_Long)0L)
	    reclaim_wide_string(listener);
    }
    listener_pos = listener_pos + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(listeners);
    return VALUES_1(Qnil);
}

/* RECLAIM-NETWORK-ADDRESSES */
Object reclaim_network_addresses(network_addresses)
    Object network_addresses;
{
    x_note_fn_call(53,11);
    return reclaim_gensym_tree_with_text_strings(network_addresses);
}

/* GET-UNIX-HOST-NAME */
Object get_unix_host_name()
{
    Object gensym_string, length_1, temp;

    x_note_fn_call(53,12);
    gensym_string = obtain_simple_gensym_string(FIX((SI_Long)100L));
    length_1 = gethostname_1(gensym_string,
	    SIMPLE_ARRAY_ANY_1_LENGTH(gensym_string));
    if (IFIX(length_1) < (SI_Long)0L)
	temp = Nil;
    else if (IFIX(length_1) == (SI_Long)0L)
	temp = Nil;
    else
	temp = copy_text_string_portion(gensym_string,FIX((SI_Long)0L),
		length_1);
    reclaim_gensym_string(gensym_string);
    return VALUES_1(temp);
}

Object Icp_connection_succeeded_tag = UNBOUND;

Object Icp_connection_failed_tag = UNBOUND;

Object Icp_noop_network_code_accessed = UNBOUND;

/* ICP-CONNECTION-LOSS-NOTIFIER */
Object icp_connection_loss_notifier(icp_socket,clean_qm)
    Object icp_socket, clean_qm;
{
    x_note_fn_call(53,13);
    return VALUES_1(Nil);
}

/* ICP-CONNECTION-IS-SECURE */
Object icp_connection_is_secure(icp_socket)
    Object icp_socket;
{
    Object temp;

    x_note_fn_call(53,14);
    temp = icp_socket &&  !EQ(ISVREF(icp_socket,(SI_Long)1L),Qlocalnet) && 
	    ISVREF(icp_socket,(SI_Long)3L) && ISVREF(ISVREF(icp_socket,
	    (SI_Long)3L),(SI_Long)1L) ? 
	    (g2ext_secure_socket_p(IFIX(ISVREF(ISVREF(icp_socket,
	    (SI_Long)3L),(SI_Long)1L))) == (SI_Long)1L ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

static Object Qicp_connection_loss_notifier;  /* icp-connection-loss-notifier */

/* REGISTER-ICP-CONNECTION-LOSS-CALLBACK-FUNCTION */
Object register_icp_connection_loss_callback_function(listener_socket_qm,
	    nascent_socket)
    Object listener_socket_qm, nascent_socket;
{
    x_note_fn_call(53,15);
    if (listener_socket_qm)
	SVREF(nascent_socket,FIX((SI_Long)33L)) = listener_socket_qm;
    return register_icp_connection_loss_callback(Qicp_connection_loss_notifier,
	    nascent_socket);
}

/* GET-TCP-LISTENER-PORT-NUMBER */
Object get_tcp_listener_port_number(tcp_name)
    Object tcp_name;
{
    Object length_1, first_1, second_1;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(53,16);
    length_1 = lengthw(tcp_name);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if (UBYTE_16_ISAREF_1(tcp_name,i) == (SI_Long)58L) {
	first_1 = FIX(i);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    first_1 = Qnil;
  end_1:;
    if (first_1) {
	i = IFIX(FIXNUM_ADD1(first_1));
	ab_loop_bind_ = IFIX(FIXNUM_SUB1(length_1));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	if (UBYTE_16_ISAREF_1(tcp_name,i) == (SI_Long)58L) {
	    second_1 = FIX(i);
	    goto end_2;
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	second_1 = Qnil;
      end_2:;
    }
    else
	second_1 = Nil;
    if (second_1)
	return text_string_parse_integer_function(tcp_name,
		FIXNUM_ADD1(second_1),Nil,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qtelewindows;        /* telewindows */

static Object Qgsi;                /* gsi */

static Object array_constant_5;    /* # */

static Object list_constant;       /* # */

static Object string_constant_2;   /* "ERROR: Could not make exact ICP connection~%" */

static Object Qregister_icp_connection_loss_callback_function;  /* register-icp-connection-loss-callback-function */

static Object string_constant_3;   /* "ERROR: DECnet not supported by this product on this platform" */

/* ESTABLISH-G2-NETWORK-LISTENERS */
Object establish_g2_network_listeners()
{
    Object tcp_port_qm, tcp_ip_exact_p, listener_name_0, listener_socket_0;
    Object listener_handle_1_qm, listener_name_1, listener_socket_1_qm;
    Object tcp_name;
    SI_Long initial_listener_count, temp, listen_status, listener_count;
    SI_Long listener_handle_0;
    char two_listeners_qm;

    x_note_fn_call(53,17);
    if ( !(EQ(Qtelewindows,Current_system_name) || EQ(Qgsi,
	    Current_system_name))) {
	if (secure_icp_requested_p())
	    set_up_secure_icp(1,Qdefault);
	initial_listener_count = g2ext_network_listener_count();
	tcp_port_qm = get_tcpip_listener_specification();
	tcp_ip_exact_p = get_command_line_flag_argument(1,array_constant_5);
	temp = memq_function(tcp_port_qm,list_constant) ? (SI_Long)0L : 
		IFIX(tcp_port_qm);
	listen_status = g2ext_network_listen(tcp_port_qm ? 
		IFIX(Use_tcpip_protocol_only) : 
		IFIX(Use_no_network_protocols),temp,tcp_ip_exact_p ? 
		(SI_Long)1L : (SI_Long)0L,IFIX(G2_product_tag),
		secure_icp_requested_p() ? (SI_Long)1L : (SI_Long)0L);
	if ( !((SI_Long)-128L <= listen_status && listen_status <= 
		(SI_Long)127L)) {
	    if (tcp_ip_exact_p) {
		notify_user_in_parent_window(1,string_constant_2);
		return shut_down_ab_process(0);
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
		listener_name_0 = get_network_listener(FIX((SI_Long)0L));
		listener_socket_0 = 
			make_and_install_network_listener(FIX(listener_handle_0),
			listener_name_0);
		listener_handle_1_qm = two_listeners_qm ? 
			FIX(ne_get_listener_handle((SI_Long)1L)) : Nil;
		listener_name_1 = two_listeners_qm ? 
			get_network_listener(FIX((SI_Long)1L)) : Nil;
		listener_socket_1_qm = two_listeners_qm ? 
			make_and_install_network_listener(listener_handle_1_qm,
			listener_name_1) : Nil;
		tcp_name = (SI_Long)84L == 
			UBYTE_16_ISAREF_1(listener_name_0,(SI_Long)0L) ? 
			listener_name_0 : two_listeners_qm && (SI_Long)84L 
			== UBYTE_16_ISAREF_1(listener_name_1,(SI_Long)0L) ?
			 listener_name_1 : Nil;
		if (tcp_name)
		    Tcp_listener_port_number = 
			    get_tcp_listener_port_number(tcp_name);
		register_icp_accept_callback(Qregister_icp_connection_loss_callback_function,
			listener_socket_0);
		if (two_listeners_qm)
		    register_icp_accept_callback(Qregister_icp_connection_loss_callback_function,
			    listener_socket_1_qm);
		return VALUES_1(T);
	      case -2:
		notify_user_in_parent_window(1,string_constant_3);
		return shut_down_ab_process(0);
	      default:
		if (tcp_ip_exact_p) {
		    notify_user_in_parent_window(1,string_constant_2);
		    return shut_down_ab_process(0);
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
Object report_listener_info_to_parent_window()
{
    Object host_name, port_list, network_type, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object left_hand_slot_lengths_qm, left_hand_slot_length, max_slot_length;
    Object largest_left_hand_slot_qm, address, secure_p, slot_length;
    Object ab_loop_list__1, space_string, temp, length_1, wide_string_bv16;
    Object temp_1, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value;
    Object result;

    x_note_fn_call(53,18);
    if (Generic_listener_initialized_qm) {
	result = get_raw_network_info();
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
	ab_loopvar__2 = icp_cons_1(length(network_type),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	left_hand_slot_lengths_qm = ab_loopvar_;
	goto end_1;
	left_hand_slot_lengths_qm = Qnil;
      end_1:;
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
	    goto end_2;
	    largest_left_hand_slot_qm = Qnil;
	  end_2:;
	}
	else
	    largest_left_hand_slot_qm = Nil;
	notify_user_at_console(2,string_constant_4,host_name);
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
	    wide_string_bv16 = allocate_byte_vector_16(FIX(IFIX(length_1) 
		    + (SI_Long)3L));
	    fill_wide_string_1(wide_string_bv16,FIX((SI_Long)32L),
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
	    notify_user_at_console(5,string_constant_5,temp,temp_1,temp_2,
		    secure_icp_string(4,Knetwork_type,network_type,
		    Ksecure_p,secure_p));
	    reclaim_text_string(space_string);
	    goto next_loop_2;
	  end_loop_2:;
	}
	add_network_info_to_title_if_appropriate(host_name,port_list);
	reclaim_icp_list_1(left_hand_slot_lengths_qm);
	return reclaim_raw_network_info(host_name,port_list);
    }
    else
	return notify_user_at_console(1,string_constant_6);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_window_title_and_info_text_string_qm, Qsystem_window_title_and_info_text_string_qm);

static Object Qnetinfo;            /* netinfo */

static Object string_constant_7;   /* "~a - " */

static Object Qsystem_window_title_string;  /* system-window-title-string */

static Object string_constant_8;   /* "[~a" */

static Object string_constant_9;   /* ":~a~a" */

static Object Kuse_default;        /* :use-default */

static Object string_constant_10;  /* "]" */

/* ADD-NETWORK-INFO-TO-TITLE-IF-APPROPRIATE */
Object add_network_info_to_title_if_appropriate(host_name,port_list)
    Object host_name, port_list;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object network_type, address, secure_p, ab_loop_list_, ab_loop_desetq_;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(53,19);
    if (getf(Command_line_arguments,Qnetinfo,_)) {
	if (System_window_title_and_info_text_string_qm)
	    reclaim_text_string(System_window_title_and_info_text_string_qm);
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
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_7,
			  getfq_function_no_default(INLINE_SYMBOL_PLIST(Current_system_name),
			  Qsystem_window_title_string));
		  tformat(2,string_constant_8,host_name);
		  network_type = Nil;
		  address = Nil;
		  secure_p = Nil;
		  ab_loop_list_ = port_list;
		  ab_loop_desetq_ = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  ab_loop_desetq_ = M_CAR(ab_loop_list_);
		  network_type = CAR(ab_loop_desetq_);
		  temp = CDR(ab_loop_desetq_);
		  address = CAR(temp);
		  temp = CDR(ab_loop_desetq_);
		  temp = CDR(temp);
		  secure_p = CAR(temp);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  temp = address;
		  tformat(3,string_constant_9,temp,secure_icp_string(6,
			  Knetwork_type,network_type,Kuse_default,T,
			  Ksecure_p,secure_p));
		  goto next_loop;
		end_loop:;
		  tformat(1,string_constant_10);
		  System_window_title_and_info_text_string_qm = 
			  copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return set_window_title(System_window,
		System_window_title_and_info_text_string_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qlocalnet_handle;    /* localnet-handle */

/* MAKE-LOCALNET-SOCKET */
Object make_localnet_socket(external_object_name,local_system_name,
	    connect_timeout)
    Object external_object_name, local_system_name, connect_timeout;
{
    Object icp_socket;

    x_note_fn_call(53,20);
    icp_socket = make_icp_socket(external_object_name,Qlocalnet,
	    Qlocalnet_handle,Qlocalnet_handle,Nil,T,T,T,local_system_name,
	    connect_timeout);
    add_to_active_icp_sockets(icp_socket);
    return VALUES_1(icp_socket);
}

/* MAKE-LOCALNET-CONNECTION */
Object make_localnet_connection varargs_1(int, n)
{
    Object external_object_name, remote_system_name;
    Object connect_timeout, main_icp_socket, server_icp_socket;
    Object svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,21);
    INIT_ARGS_nonrelocating();
    external_object_name = REQUIRED_ARG_nonrelocating();
    remote_system_name = REQUIRED_ARG_nonrelocating();
    connect_timeout = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    main_icp_socket = make_localnet_socket(external_object_name,
	    Current_system_name,connect_timeout);
    server_icp_socket = 
	    make_localnet_socket(INLINE_UNSIGNED_BYTE_16_VECTOR_P(external_object_name) 
	    != (SI_Long)0L ? copy_text_string(external_object_name) : 
	    external_object_name,remote_system_name,connect_timeout);
    svref_new_value = Icp_connection_connect_in_progress;
    SVREF(main_icp_socket,FIX((SI_Long)15L)) = svref_new_value;
    SVREF(main_icp_socket,FIX((SI_Long)42L)) = server_icp_socket;
    SVREF(server_icp_socket,FIX((SI_Long)42L)) = main_icp_socket;
    if (EQ(remote_system_name,Qgsi))
	register_gsi_connection_callbacks(Nil,server_icp_socket);
    else
	register_icp_connection_loss_callback_function(Nil,server_icp_socket);
    return VALUES_1(main_icp_socket);
}

/* RECLAIM-ICP-BUFFER-LIST */
Object reclaim_icp_buffer_list(buffer_list)
    Object buffer_list;
{
    Object buffer, next_buffer;

    x_note_fn_call(53,22);
    buffer = buffer_list;
    next_buffer = Nil;
  next_loop:
    if ( !TRUEP(buffer))
	goto end_loop;
    next_buffer = ISVREF(buffer,(SI_Long)1L);
    reclaim_icp_buffer(buffer);
    buffer = next_buffer;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-BUFFERS-FOR-PORT */
Object reclaim_icp_buffers_for_port(icp_port)
    Object icp_port;
{
    x_note_fn_call(53,23);
    reclaim_icp_buffer_list(ISVREF(icp_port,(SI_Long)12L));
    SVREF(icp_port,FIX((SI_Long)12L)) = Nil;
    SVREF(icp_port,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-PORT */
Object reclaim_icp_port(icp_port)
    Object icp_port;
{
    Object icp_port_for_reclaim;
    Declare_special(1);

    x_note_fn_call(53,24);
    reclaim_icp_buffers_for_port(icp_port);
    icp_port_for_reclaim = icp_port;
    PUSH_SPECIAL_WITH_SYMBOL(Icp_port_for_reclaim,Qicp_port_for_reclaim,icp_port_for_reclaim,
	    0);
      reclaim_icp_port_internal_1(icp_port);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qab;                 /* ab */

/* RECLAIM-ICP-INPUT-PORT */
Object reclaim_icp_input_port(icp_socket)
    Object icp_socket;
{
    Object icp_input_port, system_name, current_system_name;
    Object callback_icp_buffer_list, icp_buffer, next_icp_buffer;
    Declare_special(1);

    x_note_fn_call(53,25);
    icp_input_port = ISVREF(icp_socket,(SI_Long)3L);
    system_name = ISVREF(icp_socket,(SI_Long)49L);
    current_system_name = EQ(system_name,Qg2) ? Qab : system_name;
    PUSH_SPECIAL_WITH_SYMBOL(Current_system_name,Qcurrent_system_name,current_system_name,
	    0);
      if (icp_input_port) {
	  callback_icp_buffer_list = ISVREF(icp_input_port,(SI_Long)7L);
	  if (callback_icp_buffer_list) {
	      icp_buffer = callback_icp_buffer_list;
	      next_icp_buffer = Nil;
	    next_loop:
	      if ( !TRUEP(icp_buffer))
		  goto end_loop;
	      next_icp_buffer = ISVREF(icp_buffer,(SI_Long)1L);
	      reclaim_icp_buffer(icp_buffer);
	      icp_buffer = next_icp_buffer;
	      goto next_loop;
	    end_loop:;
	  }
	  reclaim_icp_port(icp_input_port);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* RECLAIM-ICP-OUTPUT-PORT */
Object reclaim_icp_output_port(icp_socket)
    Object icp_socket;
{
    Object icp_output_port;

    x_note_fn_call(53,26);
    icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
    if (icp_output_port) {
	SVREF(icp_socket,FIX((SI_Long)4L)) = Nil;
	reclaim_icp_port(icp_output_port);
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_throw_to_run_loop_may_be_harmful_p, Qgsi_throw_to_run_loop_may_be_harmful_p);

/* RECLAIM-ICP-SOCKET */
Object reclaim_icp_socket(icp_socket)
    Object icp_socket;
{
    Object gsi_throw_to_run_loop_may_be_harmful_p;
    Declare_special(1);

    x_note_fn_call(53,27);
    gsi_throw_to_run_loop_may_be_harmful_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Gsi_throw_to_run_loop_may_be_harmful_p,Qgsi_throw_to_run_loop_may_be_harmful_p,gsi_throw_to_run_loop_may_be_harmful_p,
	    0);
      reclaim_icp_input_port(icp_socket);
      reclaim_icp_output_port(icp_socket);
    POP_SPECIAL();
    reclaim_icp_socket_internal_1(icp_socket);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Icp_socket_for_reclaim_qm, Qicp_socket_for_reclaim_qm);

static Object Qreclaimer_for_icp_port_entry;  /* reclaimer-for-icp-port-entry */

static Object Qshutdown_reclaimer_for_icp_object;  /* shutdown-reclaimer-for-icp-object */

/* REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-1 */
Object remove_icp_port_entries_from_icp_object_1(icp_object,
	    icp_object_type,icp_port,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object, icp_object_type, icp_port;
    Object name_of_corresponding_icp_object_index_space, shutdownp;
{
    Object deregister_for_gsi_p, index_for_gsi, icp_port_entry_reclaimer_qm;
    Object shutdown_reclaimer_qm;

    x_note_fn_call(53,28);
    deregister_for_gsi_p = Nil;
    index_for_gsi = Nil;
    icp_port_entry_reclaimer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type),
	    Qreclaimer_for_icp_port_entry);
    if (icp_port_entry_reclaimer_qm)
	inline_funcall_2(icp_port_entry_reclaimer_qm,icp_object,icp_port);
    if (shutdownp) {
	shutdown_reclaimer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(icp_object_type),
		Qshutdown_reclaimer_for_icp_object);
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
Object remove_icp_port_entries_from_icp_object(icp_object,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object, name_of_corresponding_icp_object_index_space, shutdownp;
{
    Object icp_object_type_qm;

    x_note_fn_call(53,29);
    if (Icp_port_for_reclaim) {
	icp_object_type_qm = icp_object_type_given_icp_object(icp_object,
		name_of_corresponding_icp_object_index_space);
	if (icp_object_type_qm)
	    return remove_icp_port_entries_from_icp_object_1(icp_object,
		    icp_object_type_qm,Icp_port_for_reclaim,
		    name_of_corresponding_icp_object_index_space,shutdownp);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-LIST */
Object remove_icp_port_entries_from_icp_object_list(icp_object_list,
	    name_of_corresponding_icp_object_index_space,shutdownp)
    Object icp_object_list, name_of_corresponding_icp_object_index_space;
    Object shutdownp;
{
    Object icp_object, ab_loop_list_;

    x_note_fn_call(53,30);
    if (Icp_port_for_reclaim && CONSP(icp_object_list)) {
	icp_object = Nil;
	ab_loop_list_ = icp_object_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	icp_object = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	remove_icp_port_entries_from_icp_object(icp_object,
		name_of_corresponding_icp_object_index_space,shutdownp);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qitem_index_space;   /* item-index-space */

/* NOTE-ITEM-DELETED-FROM-FRAME-SERIAL-NUMBER-TABLE */
Object note_item_deleted_from_frame_serial_number_table(item)
    Object item;
{
    Object deregister_but_do_not_remove_from_table_p;
    Declare_special(1);

    x_note_fn_call(53,31);
    if (item && Icp_port_for_reclaim) {
	deregister_but_do_not_remove_from_table_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Deregister_but_do_not_remove_from_table_p,Qderegister_but_do_not_remove_from_table_p,deregister_but_do_not_remove_from_table_p,
		0);
	  remove_icp_port_entries_from_icp_object(item,Qitem_index_space,Nil);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qoutput;             /* output */

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qframe_serial_number;  /* frame-serial-number */

/* RECLAIM-INDEX-SPACE-LOCATION-AND-CORRESPONDING-OBJECTS */
Object reclaim_index_space_location_and_corresponding_objects(icp_object,
	    icp_port,index_1,index_space_name)
    Object icp_object, icp_port, index_1, index_space_name;
{
    Object port, actual_index_space_name, icp_socket, temp, temp_1;
    Object index_space, skip_list, key_value, marked, pred, curr, succ;
    Object reference, entry_hash, icp_object_from_index_space, vector_1;
    Object current_icp_socket, will_ack_p, send_p;
    SI_Long gensymed_symbol, temp_2, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, index_2;
    char output_port_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(53,32);
    output_port_p = EQ(Qoutput,ISVREF(icp_port,(SI_Long)3L));
    port = icp_port;
    if (EQ(index_space_name,Qstandard_icp_object_index_space))
	actual_index_space_name = Qstandard_icp_object_index_space;
    else if (EQ(index_space_name,Qitem_index_space)) {
	icp_socket = ISVREF(port,(SI_Long)2L);
	if (Inhibit_corresponding_icp_object_making)
	    actual_index_space_name = Qstandard_icp_object_index_space;
	else if (EQ(Qg2,ISVREF(icp_socket,(SI_Long)25L))) {
	    if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		actual_index_space_name = Qitem_index_space;
	    else {
		temp = ISVREF(icp_socket,(SI_Long)21L);
		temp_1 = ISVREF(icp_socket,(SI_Long)22L);
		actual_index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
			(SI_Long)21L ? Qitem_index_space : 
			Qframe_serial_number;
	    }
	}
	else {
	    temp = ISVREF(icp_socket,(SI_Long)21L);
	    temp_1 = ISVREF(icp_socket,(SI_Long)22L);
	    actual_index_space_name = IFIX(FIXNUM_MIN(temp,temp_1)) >= 
		    (SI_Long)10L ? Qitem_index_space : 
		    Qstandard_icp_object_index_space;
	}
    }
    else if (EQ(index_space_name,Qframe_serial_number))
	actual_index_space_name = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		Qitem_index_space : Qframe_serial_number;
    else
	actual_index_space_name = Qstandard_icp_object_index_space;
    if (EQ(actual_index_space_name,Qstandard_icp_object_index_space))
	index_space = ISVREF(icp_port,(SI_Long)8L);
    else if (EQ(actual_index_space_name,Qitem_index_space))
	index_space = item_index_space(icp_port);
    else if (EQ(actual_index_space_name,Qframe_serial_number))
	index_space = frame_serial_number_to_item_table(icp_port);
    else
	index_space = Qnil;
    if (EQ(actual_index_space_name,Qframe_serial_number)) {
	gensymed_symbol = IFIX(sxhashw(index_1));
	temp_2 = gensymed_symbol % (SI_Long)67L;
	temp_1 = SVREF(index_space,FIX(temp_2));
	skip_list = CDR(temp_1);
	key_value = index_1;
	key_hash_value = gensymed_symbol;
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop:
	if (level < ab_loop_bind_)
	    goto end_loop;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_1:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_1;
      end_loop_2:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop;
      end_loop:;
	icp_object_from_index_space = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
	if (item_with_handle_index_space(icp_port) && 
		EQ(actual_index_space_name,Qitem_index_space))
	    return deregister_item_with_handle_on_port(index_1,icp_object,
		    icp_port);
	else
	    return VALUES_1(Nil);
    }
    else {
	current_icp_socket = ISVREF(icp_port,(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		0);
	  will_ack_p = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		  (SI_Long)12L ? (EQ(actual_index_space_name,
		  Qitem_index_space) ? ( !(output_port_p && 
		  Deregister_corresponding_object_qm && 
		  Deregister_and_register_item_p) ? T : Nil) : Qnil) : Nil;
	POP_SPECIAL();
	send_p = send_reclaim_index_space_message_p(icp_port,Nil,
		actual_index_space_name);
	if ( 
		!TRUEP(send_immediate_reclaim_index_space_message(ISVREF(ISVREF(icp_port,
		(SI_Long)2L),(SI_Long)4L),index_1,actual_index_space_name,
		Nil,output_port_p ? T : Nil,send_p))) {
	    if (send_p)
		enqueue_reclaim_index_space_message(ISVREF(ISVREF(icp_port,
			(SI_Long)2L),(SI_Long)4L),index_1,
			actual_index_space_name,Nil,output_port_p ? T : 
			Nil,T,will_ack_p);
	}
	return deregister_corresponding_icp_object(icp_object,index_1,
		actual_index_space_name,icp_port,T);
    }
}

/* SEND-RECLAIM-INDEX-SPACE-MESSAGE-P */
Object send_reclaim_index_space_message_p(icp_port,ack_p,
	    actual_index_space_name)
    Object icp_port, ack_p, actual_index_space_name;
{
    Object current_icp_socket, temp, temp_1;
    char output_port_p, temp_2;
    Declare_special(1);

    x_note_fn_call(53,33);
    current_icp_socket = ISVREF(icp_port,(SI_Long)2L);
    output_port_p = EQ(Qoutput,ISVREF(icp_port,(SI_Long)3L));
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	    0);
      if (icp_connection_open_p(Current_icp_socket)) {
	  if (ack_p)
	      temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)21L)) >= 
		      (SI_Long)12L ? T : Nil;
	  else if (output_port_p && EQ(actual_index_space_name,
		  Qframe_serial_number) && (IFIX(ISVREF(Current_icp_socket,
		  (SI_Long)22L)) >= (SI_Long)12L ?  
		  !TRUEP(item_references_enabled_p(Current_icp_socket)) : 
		  TRUEP(T)))
	      temp = Nil;
	  else if ( !output_port_p) {
	      if (Delete_corresponding_object_qm || 
		      Deregister_corresponding_object_qm) {
		  temp_1 = ISVREF(Current_icp_socket,(SI_Long)21L);
		  temp = ISVREF(Current_icp_socket,(SI_Long)22L);
		  temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)10L ? T 
			  : Nil;
	      }
	      else
		  temp = Nil;
	  }
	  else {
	      if (Delete_corresponding_object_qm) {
		  temp_1 = ISVREF(Current_icp_socket,(SI_Long)21L);
		  temp = ISVREF(Current_icp_socket,(SI_Long)22L);
		  temp_2 = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)2L ? 
			  TRUEP(T) : TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  temp =  !TRUEP(Deregister_corresponding_object_qm) ? T : Nil;
		  if (temp);
		  else
		      temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			      >= (SI_Long)5L ? T : Nil;
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

static Object Qderegister_and_register_corresponding_icp_object;  /* deregister-and-register-corresponding-icp-object */

/* SEND-IMMEDIATE-RECLAIM-INDEX-SPACE-MESSAGE */
Object send_immediate_reclaim_index_space_message(icp_output_port,index_1,
	    index_space_name,ack_p,output_port_p,send_p)
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
    Object gensymed_symbol, aref_arg_1, temp_1, index_list, port, icp_socket_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(53,34);
    if ( !TRUEP(ack_p) && output_port_p && Deregister_and_register_item_p) {
	if (send_p) {
	    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
	    if (icp_connection_open_p(icp_socket) &&  
		    !TRUEP(icp_connection_being_shutdown_qm(icp_socket))) {
		current_icp_port = icp_output_port;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp);
		    else
			temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
				Qtelewindows) ? T : Nil;
		    disable_resumability = temp;
		    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
			    9);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      8);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
				7);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
				  6);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
				    5);
			      number_of_icp_bytes_to_fill_buffer = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				      4);
				current_icp_buffer = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
					3);
				  current_write_icp_byte_position = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
					  2);
				    number_of_icp_bytes_in_message_group = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					    1);
				      writing_icp_message_group = 
					      FIXNUM_ADD1(Writing_icp_message_group);
				      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					      0);
					gensymed_symbol = Nil;
					gensymed_symbol_1 = 0.0;
					gensymed_symbol_2 = 0.0;
					if (Profiling_enabled_qm) {
					    gensymed_symbol = T;
					    gensymed_symbol_1 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_2 = 
						    g2ext_unix_time_as_float();
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp = 
						    ISVREF(Current_icp_socket,
						    (SI_Long)21L);
					    temp_1 = 
						    ISVREF(Current_icp_socket,
						    (SI_Long)22L);
					    if (IFIX(FIXNUM_MIN(temp,
						    temp_1)) >= (SI_Long)13L) {
						index_list = 
							icp_cons_1(index_1,
							Nil);
						send_icp_deregister_icp_objects(index_space_name,
							Qderegister_and_register_corresponding_icp_object,
							index_list);
						reclaim_icp_list_1(index_list);
					    }
					    else
						send_icp_deregister_corresponding_icp_object(index_1,
							index_space_name);
					    end_icp_message_group();
					}
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    aref_new_value);
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    aref_new_value);
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
	if (EQ(index_space_name,Qstandard_icp_object_index_space))
	    temp = Qstandard_icp_object_index_space;
	else if (EQ(index_space_name,Qitem_index_space)) {
	    icp_socket_1 = ISVREF(port,(SI_Long)2L);
	    if (Inhibit_corresponding_icp_object_making)
		temp = Qstandard_icp_object_index_space;
	    else if (EQ(Qg2,ISVREF(icp_socket_1,(SI_Long)25L))) {
		if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		    temp = Qitem_index_space;
		else {
		    temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		    temp = ISVREF(icp_socket_1,(SI_Long)22L);
		    temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)21L ? 
			    Qitem_index_space : Qframe_serial_number;
		}
	    }
	    else {
		temp_1 = ISVREF(icp_socket_1,(SI_Long)21L);
		temp = ISVREF(icp_socket_1,(SI_Long)22L);
		temp = IFIX(FIXNUM_MIN(temp_1,temp)) >= (SI_Long)10L ? 
			Qitem_index_space : Qstandard_icp_object_index_space;
	    }
	}
	else if (EQ(index_space_name,Qframe_serial_number))
	    temp = EQ(ISVREF(port,(SI_Long)3L),Qoutput) ? 
		    Qitem_index_space : Qframe_serial_number;
	else
	    temp = Qstandard_icp_object_index_space;
	if (EQ(temp,Qstandard_icp_object_index_space))
	    temp = ISVREF(icp_output_port,(SI_Long)8L);
	else if (EQ(temp,Qitem_index_space))
	    temp = item_index_space(icp_output_port);
	else if (EQ(temp,Qframe_serial_number))
	    temp = frame_serial_number_to_item_table(icp_output_port);
	else
	    temp = Qnil;
	deassign_index_in_index_space(index_1,temp);
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object Enqueue_reclaim_index_space_message_interval = UNBOUND;

static Object Qacknowledge_deregister_corresponding_icp_object;  /* acknowledge-deregister-corresponding-icp-object */

static Object Qderegister_original_icp_object;  /* deregister-original-icp-object */

static Object Qdelete_icp_object_for_process_with_deassign;  /* delete-icp-object-for-process-with-deassign */

static Object Qdelete_icp_object_for_process;  /* delete-icp-object-for-process */

static Object Qderegister_corresponding_icp_object_with_deassign;  /* deregister-corresponding-icp-object-with-deassign */

static Object Qderegister_corresponding_icp_object;  /* deregister-corresponding-icp-object */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qsend_queued_reclaim_index_space_messages;  /* send-queued-reclaim-index-space-messages */

/* ENQUEUE-RECLAIM-INDEX-SPACE-MESSAGE */
Object enqueue_reclaim_index_space_message(icp_output_port,index_1,
	    index_space_name,ack_p,output_port_p,local_p,will_ack_p)
    Object icp_output_port, index_1, index_space_name, ack_p, output_port_p;
    Object local_p, will_ack_p;
{
    Object type, icp_socket, alist, index_space_name_entry, entry, temp;
    Object type_entry, icp_push_modify_macro_arg, car_1, cdr_1;
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double temp_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(53,35);
    if (ack_p)
	type = Qacknowledge_deregister_corresponding_icp_object;
    else if ( !TRUEP(output_port_p))
	type = Qderegister_original_icp_object;
    else if (Deregister_and_register_item_p)
	type = Qderegister_and_register_corresponding_icp_object;
    else if ( !TRUEP(Deregister_corresponding_object_qm))
	type = local_p &&  !TRUEP(will_ack_p) ? 
		Qdelete_icp_object_for_process_with_deassign : 
		Qdelete_icp_object_for_process;
    else
	type = local_p &&  !TRUEP(will_ack_p) ? 
		Qderegister_corresponding_icp_object_with_deassign : 
		Qderegister_corresponding_icp_object;
    icp_socket = ISVREF(icp_output_port,(SI_Long)2L);
    alist = ISVREF(icp_socket,(SI_Long)46L);
    index_space_name_entry = assq_function(index_space_name,alist);
    if (index_space_name_entry);
    else {
	entry = icp_cons_1(index_space_name,Nil);
	temp = icp_cons_1(entry,alist);
	SVREF(icp_socket,FIX((SI_Long)46L)) = temp;
	index_space_name_entry = entry;
    }
    type_entry = assq_function(type,CDR(index_space_name_entry));
    if (type_entry);
    else {
	entry = icp_cons_1(type,Nil);
	temp = icp_cons_1(entry,CDR(index_space_name_entry));
	M_CDR(index_space_name_entry) = temp;
	type_entry = entry;
    }
    icp_push_modify_macro_arg = index_1;
    car_1 = icp_push_modify_macro_arg;
    cdr_1 = CDR(type_entry);
    temp = icp_cons_1(car_1,cdr_1);
    M_CDR(type_entry) = temp;
    schedule_task_qm = ISVREF(icp_socket,(SI_Long)47L);
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(icp_socket,(SI_Long)47L);
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
	temp_1 = 
		DOUBLE_FLOAT_TO_DOUBLE(Enqueue_reclaim_index_space_message_interval);
	aref_new_value = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L) + 
		temp_1;
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)0L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	SVREF(task,FIX((SI_Long)7L)) = 
		Qsend_queued_reclaim_index_space_messages;
	temp = SYMBOL_FUNCTION(Qsend_queued_reclaim_index_space_messages);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = icp_socket;
	new_1 = task;
	if (CAS_SVREF(icp_socket,(SI_Long)47L,old,new_1)) {
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
    }
    return VALUES_1(Nil);
}

/* SEND-QUEUED-RECLAIM-INDEX-SPACE-MESSAGES */
Object send_queued_reclaim_index_space_messages(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object current_icp_socket, icp_output_port, icp_objects_alist;
    Object index_space_element, ab_loop_list_, index_space_name, type_alist;
    Object element, ab_loop_list__1, type, type_index_list, index_list;
    Object current_icp_port, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object temp_2, index_list_tail, next_index_list, index_1;
    Object index_list_old_value, port, actual_index_space_name, icp_socket_1;
    Object index_space, ab_loop_list__2;
    SI_Long i;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(13);

    x_note_fn_call(53,36);
    gensymed_symbol = Nil;
  next_loop:
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
    current_icp_socket = icp_socket;
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	    12);
      icp_output_port = ISVREF(icp_socket,(SI_Long)4L);
      icp_objects_alist = ISVREF(icp_socket,(SI_Long)46L);
      index_space_element = Nil;
      ab_loop_list_ = icp_objects_alist;
      index_space_name = Nil;
      type_alist = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      index_space_element = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      index_space_name = CAR(index_space_element);
      type_alist = CDR(index_space_element);
      reclaim_icp_cons_1(index_space_element);
      element = Nil;
      ab_loop_list__1 = type_alist;
      type = Nil;
      type_index_list = Nil;
      index_list = Nil;
    next_loop_2:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_2;
      element = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      type = CAR(element);
      type_index_list = CDR(element);
      index_list = type_index_list;
      reclaim_icp_cons_1(element);
      if (icp_connection_open_p(icp_socket) &&  
	      !TRUEP(icp_connection_being_shutdown_qm(icp_socket))) {
	next_loop_3:
	  if ( !TRUEP(index_list))
	      goto end_loop_3;
	  current_icp_port = icp_output_port;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		  11);
	    current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		    10);
	      temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		      (SI_Long)17L ? ISVREF(Current_icp_socket,
		      (SI_Long)53L) : Nil;
	      if (temp_1);
	      else
		  temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			  Qtelewindows) ? T : Nil;
	      disable_resumability = temp_1;
	      PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		      9);
		number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			8);
		  icp_buffers_for_message_group = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			  7);
		    icp_buffer_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			    6);
		      icp_byte_position_of_start_of_message_series_qm = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			      5);
			number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				4);
			  current_icp_buffer = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				  3);
			    current_write_icp_byte_position = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				    2);
			      number_of_icp_bytes_in_message_group = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				      1);
				writing_icp_message_group = 
					FIXNUM_ADD1(Writing_icp_message_group);
				PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
					0);
				  gensymed_symbol = Nil;
				  gensymed_symbol_1 = 0.0;
				  gensymed_symbol_2 = 0.0;
				  if (Profiling_enabled_qm) {
				      gensymed_symbol = T;
				      gensymed_symbol_1 = 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L),(SI_Long)0L);
				      gensymed_symbol_2 = 
					      g2ext_unix_time_as_float();
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L);
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      gensymed_symbol_2);
				  }
				  if (icp_connection_open_p(Current_icp_socket) 
					  &&  
					  !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					      {
				      temp_1 = ISVREF(Current_icp_socket,
					      (SI_Long)21L);
				      temp_2 = ISVREF(Current_icp_socket,
					      (SI_Long)22L);
				      if (IFIX(FIXNUM_MIN(temp_1,temp_2)) 
					      >= (SI_Long)13L) {
					  index_list_tail = 
						  nthcdr(FIX((SI_Long)199L),
						  index_list);
					  next_index_list = 
						  CDR(index_list_tail);
					  if (index_list_tail)
					      M_CDR(index_list_tail) = Nil;
					  send_icp_deregister_icp_objects(index_space_name,
						  type,index_list);
					  if (index_list_tail)
					      M_CDR(index_list_tail) = 
						      next_index_list;
					  index_list = next_index_list;
				      }
				      else {
					  i = (SI_Long)0L;
					  index_1 = Nil;
					next_loop_4:
					  if (i >= (SI_Long)200L)
					      goto end_loop_4;
					  if ( !(index_list && 
						  icp_connection_open_p(icp_socket) 
						  &&  
						  !TRUEP(icp_connection_being_shutdown_qm(icp_socket))))
					      goto end_loop_4;
					  index_list_old_value = index_list;
					  temp_1 = FIRST(index_list_old_value);
					  index_list = 
						  REST(index_list_old_value);
					  index_1 = temp_1;
					  if (EQ(type,
						  Qacknowledge_deregister_corresponding_icp_object))
					      send_icp_acknowledge_deregister_corresponding_icp_object(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qderegister_original_icp_object))
					      send_icp_deregister_original_icp_object(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qdelete_icp_object_for_process) 
						  || EQ(type,
						  Qdelete_icp_object_for_process_with_deassign))
					      send_icp_delete_icp_object_for_process(index_1,
						      index_space_name);
					  else if (EQ(type,
						  Qderegister_corresponding_icp_object) 
						  || EQ(type,
						  Qderegister_corresponding_icp_object_with_deassign) 
						  || EQ(type,
						  Qderegister_and_register_corresponding_icp_object))
					      send_icp_deregister_corresponding_icp_object(index_1,
						      index_space_name);
					  i = i + (SI_Long)1L;
					  goto next_loop_4;
					end_loop_4:;
				      }
				      end_icp_message_group();
				  }
				  if (Profiling_enabled_qm) {
				      gensymed_symbol_3 = 
					      g2ext_unix_time_as_float();
				      gensymed_symbol_4 = 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L),(SI_Long)0L);
				      gensymed_symbol_5 = 
					      gensymed_symbol_3 - 
					      gensymed_symbol_4;
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L);
				      aref_new_value = gensymed_symbol_5 + 
					      DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					      (SI_Long)6L),(SI_Long)0L);
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      aref_new_value);
				      temp = ISVREF(Profiling_enabled_qm,
					      (SI_Long)2L);
				      aref_new_value = gensymed_symbol ? 
					      gensymed_symbol_1 + 
					      gensymed_symbol_5 + 
					      (gensymed_symbol_4 - 
					      gensymed_symbol_2) : 
					      gensymed_symbol_3;
				      DFLOAT_ISASET_1(temp,(SI_Long)0L,
					      aref_new_value);
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
	  goto next_loop_3;
	end_loop_3:;
      }
      if (EQ(type,Qdelete_icp_object_for_process_with_deassign) || EQ(type,
	      Qderegister_corresponding_icp_object_with_deassign)) {
	  port = icp_output_port;
	  if (EQ(index_space_name,Qstandard_icp_object_index_space))
	      actual_index_space_name = Qstandard_icp_object_index_space;
	  else if (EQ(index_space_name,Qitem_index_space)) {
	      icp_socket_1 = ISVREF(port,(SI_Long)2L);
	      if (Inhibit_corresponding_icp_object_making)
		  actual_index_space_name = Qstandard_icp_object_index_space;
	      else if (EQ(Qg2,ISVREF(icp_socket_1,(SI_Long)25L))) {
		  if (EQ(ISVREF(port,(SI_Long)3L),Qoutput))
		      actual_index_space_name = Qitem_index_space;
		  else {
		      temp_2 = ISVREF(icp_socket_1,(SI_Long)21L);
		      temp_1 = ISVREF(icp_socket_1,(SI_Long)22L);
		      actual_index_space_name = IFIX(FIXNUM_MIN(temp_2,
			      temp_1)) >= (SI_Long)21L ? Qitem_index_space 
			      : Qframe_serial_number;
		  }
	      }
	      else {
		  temp_2 = ISVREF(icp_socket_1,(SI_Long)21L);
		  temp_1 = ISVREF(icp_socket_1,(SI_Long)22L);
		  actual_index_space_name = IFIX(FIXNUM_MIN(temp_2,
			  temp_1)) >= (SI_Long)10L ? Qitem_index_space : 
			  Qstandard_icp_object_index_space;
	      }
	  }
	  else if (EQ(index_space_name,Qframe_serial_number))
	      actual_index_space_name = EQ(ISVREF(port,(SI_Long)3L),
		      Qoutput) ? Qitem_index_space : Qframe_serial_number;
	  else
	      actual_index_space_name = Qstandard_icp_object_index_space;
	  if ( !EQ(actual_index_space_name,Qframe_serial_number)) {
	      if (EQ(actual_index_space_name,Qstandard_icp_object_index_space))
		  index_space = ISVREF(icp_output_port,(SI_Long)8L);
	      else if (EQ(actual_index_space_name,Qitem_index_space))
		  index_space = item_index_space(icp_output_port);
	      else if (EQ(actual_index_space_name,Qframe_serial_number))
		  index_space = 
			  frame_serial_number_to_item_table(icp_output_port);
	      else
		  index_space = Qnil;
	      index_1 = Nil;
	      ab_loop_list__2 = type_index_list;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list__2))
		  goto end_loop_5;
	      index_1 = M_CAR(ab_loop_list__2);
	      ab_loop_list__2 = M_CDR(ab_loop_list__2);
	      deassign_index_in_index_space(index_1,index_space);
	      goto next_loop_5;
	    end_loop_5:;
	  }
      }
      reclaim_icp_list_1(type_index_list);
      goto next_loop_2;
    end_loop_2:;
      reclaim_icp_list_1(type_alist);
      goto next_loop_1;
    end_loop_1:
      reclaim_icp_list_1(icp_objects_alist);
      SVREF(icp_socket,FIX((SI_Long)46L)) = Nil;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* REMOVE-ICP-OBJECT-FROM-INDEX-SPACE */
Object remove_icp_object_from_index_space(icp_object,icp_port,index_1,
	    name_of_corresponding_icp_object_index_space)
    Object icp_object, icp_port, index_1;
    Object name_of_corresponding_icp_object_index_space;
{
    x_note_fn_call(53,37);
    return set_in_icp_port(icp_port,index_1,
	    name_of_corresponding_icp_object_index_space,Nil);
}

static Object Qsend_icp_shut_down_data_server;  /* send-icp-shut-down-data-server */

static Object Qshut_down_data_server;  /* shut-down-data-server */

static Object string_constant_11;  /* "[message]" */

static Object Qmessage;            /* message */

static Object string_constant_12;  /* "resumable icp synch error: ~S expected, ~S found" */

/* SEND-ICP-SHUT-DOWN-DATA-SERVER */
Object send_icp_shut_down_data_server()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,38);
    if (Disable_resumability) {
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_shut_down_data_server;
	  }
	  start_writing_icp_message(FIX((SI_Long)70L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qshut_down_data_server,
			  string_constant_11,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qshut_down_data_server,string_constant_11,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_shut_down_data_server,top)) {
		result = icp_error_internal(Qerror,string_constant_12,
			Qsend_icp_shut_down_data_server,top,Nil);
		goto end_send_icp_shut_down_data_server;
	    }
	}
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_shut_down_data_server;
	  }
	  if (EQ(icp_suspend_1,start_writing_icp_message(FIX((SI_Long)70L)))) {
	      resumable_icp_push(Qsend_icp_shut_down_data_server);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_shut_down_data_server;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qshut_down_data_server,
			  string_constant_11,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qshut_down_data_server,string_constant_11,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_shut_down_data_server:
    return result;
}

static Object Qreceived_shutdown_request;  /* received-shutdown-request */

/* HANDLE-ICP-SHUT-DOWN-DATA-SERVER--BODY */
Object handle_icp_shut_down_data_server__body()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(53,39);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
	  SVREF(temp,svref_arg_2) = Qreceived_shutdown_request;
      }
      acknowledge_shutdown(Current_icp_socket);
      shutdown_icp_socket_connection(1,Current_icp_socket);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_shut_down_data_server;  /* handle-icp-shut-down-data-server */

/* HANDLE-ICP-SHUT-DOWN-DATA-SERVER */
Object handle_icp_shut_down_data_server()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(53,40);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qshut_down_data_server,
			string_constant_11,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_shut_down_data_server__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qshut_down_data_server,string_constant_11,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_shut_down_data_server__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_shut_down_data_server,top))
		return icp_error_internal(Qerror,string_constant_12,
			Qhandle_icp_shut_down_data_server,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qshut_down_data_server,
			string_constant_11,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_shut_down_data_server__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qshut_down_data_server,string_constant_11,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_shut_down_data_server__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* ACKNOWLEDGE-SHUTDOWN */
Object acknowledge_shutdown(icp_socket)
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
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(53,41);
    if (icp_connection_open_p(icp_socket) && ISVREF(icp_socket,(SI_Long)20L)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_acknowledge_shutdown();
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
	flush_icp_output_ports();
    }
    return VALUES_1(Nil);
}

static Object Qsend_icp_acknowledge_shutdown;  /* send-icp-acknowledge-shutdown */

static Object Qacknowledge_shutdown;  /* acknowledge-shutdown */

/* SEND-ICP-ACKNOWLEDGE-SHUTDOWN */
Object send_icp_acknowledge_shutdown()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(53,42);
    if (Disable_resumability) {
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_acknowledge_shutdown;
	  }
	  start_writing_icp_message(FIX((SI_Long)336L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qacknowledge_shutdown,
			  string_constant_11,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qacknowledge_shutdown,string_constant_11,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_acknowledge_shutdown,top)) {
		result = icp_error_internal(Qerror,string_constant_12,
			Qsend_icp_acknowledge_shutdown,top,Nil);
		goto end_send_icp_acknowledge_shutdown;
	    }
	}
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_acknowledge_shutdown;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)336L)))) {
	      resumable_icp_push(Qsend_icp_acknowledge_shutdown);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_acknowledge_shutdown;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qacknowledge_shutdown,
			  string_constant_11,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qacknowledge_shutdown,string_constant_11,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_acknowledge_shutdown:
    return result;
}

/* HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN--BODY */
Object handle_icp_acknowledge_shutdown__body()
{
    x_note_fn_call(53,43);
    shutdown_icp_socket_connection(1,Current_icp_socket);
    return VALUES_1(Nil);
}

static Object Qhandle_icp_acknowledge_shutdown;  /* handle-icp-acknowledge-shutdown */

/* HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN */
Object handle_icp_acknowledge_shutdown()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(53,44);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qacknowledge_shutdown,
			string_constant_11,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_acknowledge_shutdown__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qacknowledge_shutdown,string_constant_11,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_acknowledge_shutdown__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_acknowledge_shutdown,top))
		return icp_error_internal(Qerror,string_constant_12,
			Qhandle_icp_acknowledge_shutdown,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qacknowledge_shutdown,
			string_constant_11,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_acknowledge_shutdown__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qacknowledge_shutdown,string_constant_11,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_acknowledge_shutdown__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(In_recursive_gsi_context, Qin_recursive_gsi_context);

/* SHUTDOWN-ICP-SOCKET-CONNECTION */
Object shutdown_icp_socket_connection varargs_1(int, n)
{
    Object icp_socket;
    Object reason_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(53,45);
    INIT_ARGS_nonrelocating();
    icp_socket = REQUIRED_ARG_nonrelocating();
    reason_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_closed))
	return VALUES_1(Nil);
    if ( !TRUEP(ISVREF(icp_socket,(SI_Long)9L)))
	SVREF(icp_socket,FIX((SI_Long)9L)) = reason_qm;
    close_and_disconnect_icp_socket_handle(icp_socket);
    if ( !EQ(icp_socket,Icp_socket_transacting_message_group) || 
	    In_recursive_gsi_context)
	return finalize_and_reclaim_icp_socket(icp_socket);
    else
	return VALUES_1(Nil);
}

static Object Qtime_out_icp_socket;  /* time-out-icp-socket */

static Object Qshutdown_timed_out_awaiting_acknowledgement;  /* shutdown-timed-out-awaiting-acknowledgement */

static Object Qshutdown_icp_socket_after_connect;  /* shutdown-icp-socket-after-connect */

/* FLUSH-AND-SHUTDOWN-ICP-SOCKET */
Object flush_and_shutdown_icp_socket(icp_socket)
    Object icp_socket;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object current_icp_port, current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object old, new_1, def_structure_schedule_task_variable, svref_new_value;
    Object task;
    char svref_new_value_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(53,46);
    gensymed_symbol = Nil;
  next_loop:
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
    if (icp_connection_open_p(icp_socket)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp_1;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_shut_down_data_server();
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    aref_new_value);
				    temp = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(temp,(SI_Long)0L,
					    aref_new_value);
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
	flush_icp_output_ports();
	if (icp_connection_open_p(icp_socket)) {
	    if (ISVREF(icp_socket,(SI_Long)20L)) {
		temp = Icp_connection_awaiting_acknowledgement;
		SVREF(icp_socket,FIX((SI_Long)15L)) = temp;
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = ISVREF(icp_socket,(SI_Long)36L);
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    SVREF(def_structure_schedule_task_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_schedule_task_g2_struct;
		}
		else
		    def_structure_schedule_task_variable = 
			    make_permanent_schedule_task_structure_internal();
		inline_note_allocate_cons(def_structure_schedule_task_variable,
			Nil);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(Current_real_time,
			(SI_Long)0L) + 
			(double)IFIX(Icp_socket_shutdown_handshake_timeout);
		DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
		svref_new_value_1 =  !TRUEP(T);
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		ISVREF(task,(SI_Long)4L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = Qtime_out_icp_socket;
		temp = SYMBOL_FUNCTION(Qtime_out_icp_socket);
		SVREF(task,FIX((SI_Long)8L)) = temp;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
		SVREF(task,FIX((SI_Long)13L)) = icp_socket;
		SVREF(task,FIX((SI_Long)14L)) = 
			Qshutdown_timed_out_awaiting_acknowledgement;
		new_1 = task;
		if (CAS_SVREF(icp_socket,(SI_Long)36L,old,new_1)) {
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
			temp = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(old,FIX((SI_Long)0L)) = temp;
			temp = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = old;
		    }
		    future_task_schedule_2(new_1);
		    return VALUES_1(new_1);
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
		return VALUES_1(Qnil);
	    }
	    else
		return shutdown_icp_socket_connection(1,icp_socket);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (icp_connection_in_progress_p(icp_socket)) {
	deregister_all_icp_connect_callbacks(icp_socket);
	return register_icp_connect_callback(Qshutdown_icp_socket_after_connect,
		icp_socket);
    }
    else
	return VALUES_1(Qnil);
}

/* SHUTDOWN-ICP-SOCKET-AFTER-CONNECT */
Object shutdown_icp_socket_after_connect(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(53,47);
    flush_and_shutdown_icp_socket(icp_socket);
    return VALUES_1(Nil);
}

/* TIME-OUT-ICP-SOCKET */
Object time_out_icp_socket(icp_socket,reason)
    Object icp_socket, reason;
{
    x_note_fn_call(53,48);
    shutdown_icp_socket_connection(2,icp_socket,reason);
    return VALUES_1(Nil);
}

/* CLOSE-AND-DISCONNECT-ALL-SOCKETS */
Object close_and_disconnect_all_sockets()
{
    Object list_1, icp_socket, next_list, current_icp_port, current_icp_socket;
    Object temp, disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(53,49);
    list_1 = Active_icp_sockets;
    icp_socket = Nil;
    next_list = Nil;
  next_loop:
    icp_socket = CAR(list_1);
    next_list = CDR(list_1);
    if ( !TRUEP(list_1))
	goto end_loop;
    if (FIXNUM_EQ(ISVREF(icp_socket,(SI_Long)15L),Icp_connection_running)) {
	current_icp_port = ISVREF(icp_socket,(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		11);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  10);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    9);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      8);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			7);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  6);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    5);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      4);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				3);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  2);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    1);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      0);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (Profiling_enabled_qm) {
				    gensymed_symbol = T;
				    gensymed_symbol_1 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_2 = 
					    g2ext_unix_time_as_float();
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    if (IFIX(ISVREF(Current_icp_socket,
					    (SI_Long)22L)) >= (SI_Long)5L)
					send_icp_acknowledge_shutdown();
				    else
					send_icp_shut_down_data_server();
				    end_icp_message_group();
				}
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
				    aref_arg_1 = 
					    ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					    aref_new_value);
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
    goto end_1;
  end_1:;
    flush_icp_output_ports();
    list_1 = Active_icp_sockets;
    icp_socket = Nil;
    next_list = Nil;
  next_loop_1:
    icp_socket = CAR(list_1);
    next_list = CDR(list_1);
    if ( !TRUEP(list_1))
	goto end_loop_1;
    close_and_disconnect_icp_socket_handle(icp_socket);
    list_1 = next_list;
    goto next_loop_1;
  end_loop_1:
    goto end_2;
  end_2:;
    Active_icp_sockets = Nil;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Check_icp_handshaking_p, Qcheck_icp_handshaking_p);

Object Icp_handshake_registry = UNBOUND;

void int4_INIT()
{
    Object pushnew_arg_1, pushnew_arg_3, icp_handshake_registry_new_value;
    Object list_constant_72, list_constant_71, Qdynamic_data_warm_link;
    Object list_constant_48, list_constant_70, list_constant_69;
    Object list_constant_45, list_constant_44, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_64;
    Object list_constant_65, list_constant_63, list_constant_62;
    Object list_constant_22, list_constant_61, list_constant_40;
    Object list_constant_60, list_constant_38, list_constant_37;
    Object list_constant_15, list_constant_14, list_constant_13;
    Object list_constant_59, Qdynamic_data_acknowledge_6, list_constant_36;
    Object list_constant_5, list_constant_35, Qdynamic_data_unadvise_1;
    Object AB_package, list_constant_58, Qicp_handshake_at_most_once_1;
    Object Qicp_handshake_any_number_1, list_constant_56, list_constant_34;
    Object Qdynamic_data_acknowledge_5, list_constant_57, list_constant_7;
    Object Qdynamic_data_supplied_2, Qdynamic_data_request_1, list_constant_6;
    Object list_constant_55, Qdynamic_data_acknowledge_4, list_constant_54;
    Object list_constant_53, Qdynamic_data_supplied_1, Knull_item, Kremote;
    Object Qdynamic_data_supplied, list_constant_33, list_constant_52;
    Object Qdynamic_data_advise_2, list_constant_29, Qdynamic_data_advise_1;
    Object Kwarm, Qdynamic_data_advise, list_constant_51;
    Object Qdynamic_data_request, Qdynamic_data_unadvise;
    Object Qdynamic_data_terminate, list_constant_27, list_constant_50;
    Object list_constant_49, Qdynamic_data_hot_link, list_constant_47;
    Object list_constant_46, list_constant_43, list_constant_42;
    Object list_constant_41, list_constant_39, list_constant_24;
    Object list_constant_23, Qdynamic_data_terminate_1, list_constant_2;
    Object list_constant_32, Qdynamic_data_acknowledge, list_constant_28;
    Object Qdynamic_data_acknowledge_3, list_constant_31;
    Object Qdynamic_data_acknowledge_2, list_constant_30, Kpositive, Khot;
    Object Qicp_handshake_disjunction_1, Qdynamic_data_initiate;
    Object list_constant_26, list_constant_25, Qdynamic_data_cold_link;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_18, list_constant_17, list_constant_16;
    Object list_constant_10, list_constant_12, Qdynamic_data_terminate_2;
    Object list_constant_4, list_constant_11, list_constant_9, Knegative;
    Object Qdynamic_data_request_2, list_constant_8;
    Object Qdynamic_data_acknowledge_1, list_constant_3;
    Object Qdynamic_data_initiate_1, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object float_constant, Qremove_icp_port_entries_from_icp_object_list;
    Object Qremove_icp_port_entries_from_icp_object, Qint4, list_constant_1;
    Object Qget_unix_host_name;

    x_note_fn_call(53,50);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~a:~(~a~):~a");
    Qvms_process = STATIC_SYMBOL("VMS-PROCESS",AB_package);
    Qlocalnet = STATIC_SYMBOL("LOCALNET",AB_package);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
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
    Qgeneric = STATIC_SYMBOL("GENERIC",AB_package);
    string_constant_1 = STATIC_STRING("~a");
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    Qget_unix_host_name = STATIC_SYMBOL("GET-UNIX-HOST-NAME",AB_package);
    SET_SYMBOL_FUNCTION(Qget_unix_host_name,
	    STATIC_FUNCTION(get_unix_host_name,NIL,FALSE,0,0));
    Icp_connection_succeeded_tag = FIX((SI_Long)1L);
    Icp_connection_failed_tag = FIX((SI_Long)-1L);
    Icp_noop_network_code_accessed = FIX((SI_Long)-2L);
    Qicp_connection_loss_notifier = 
	    STATIC_SYMBOL("ICP-CONNECTION-LOSS-NOTIFIER",AB_package);
    SET_SYMBOL_FUNCTION(Qicp_connection_loss_notifier,
	    STATIC_FUNCTION(icp_connection_loss_notifier,NIL,FALSE,2,2));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
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
    Qregister_icp_connection_loss_callback_function = 
	    STATIC_SYMBOL("REGISTER-ICP-CONNECTION-LOSS-CALLBACK-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qregister_icp_connection_loss_callback_function,
	    STATIC_FUNCTION(register_icp_connection_loss_callback_function,
	    NIL,FALSE,2,2));
    string_constant_3 = 
	    STATIC_STRING("ERROR: DECnet not supported by this product on this platform");
    Qgeneric_listener_initialized_qm = 
	    STATIC_SYMBOL("GENERIC-LISTENER-INITIALIZED\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgeneric_listener_initialized_qm,
	    Generic_listener_initialized_qm);
    Qint4 = STATIC_SYMBOL("INT4",AB_package);
    record_system_variable(Qgeneric_listener_initialized_qm,Qint4,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    string_constant_4 = STATIC_STRING("host: ~a~%");
    string_constant_5 = STATIC_STRING("~a~a: ~a~a~%");
    Knetwork_type = STATIC_SYMBOL("NETWORK-TYPE",Pkeyword);
    Ksecure_p = STATIC_SYMBOL("SECURE-P",Pkeyword);
    string_constant_6 = 
	    STATIC_STRING("WARNING: Could not make ICP connection~%");
    Qsystem_window_title_and_info_text_string_qm = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-AND-INFO-TEXT-STRING\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_window_title_and_info_text_string_qm,
	    System_window_title_and_info_text_string_qm);
    record_system_variable(Qsystem_window_title_and_info_text_string_qm,
	    Qint4,Nil,Qnil,Qnil,Qnil,Qnil);
    Qnetinfo = STATIC_SYMBOL("NETINFO",AB_package);
    string_constant_7 = STATIC_STRING("~a - ");
    Qsystem_window_title_string = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-STRING",AB_package);
    string_constant_8 = STATIC_STRING("[~a");
    string_constant_9 = STATIC_STRING(":~a~a");
    Kuse_default = STATIC_SYMBOL("USE-DEFAULT",Pkeyword);
    string_constant_10 = STATIC_STRING("]");
    Qlocalnet_handle = STATIC_SYMBOL("LOCALNET-HANDLE",AB_package);
    Qab = STATIC_SYMBOL("AB",AB_package);
    if (Gsi_throw_to_run_loop_may_be_harmful_p == UNBOUND)
	Gsi_throw_to_run_loop_may_be_harmful_p = Nil;
    if (Icp_socket_for_reclaim_qm == UNBOUND)
	Icp_socket_for_reclaim_qm = Nil;
    Qreclaimer_for_icp_port_entry = 
	    STATIC_SYMBOL("RECLAIMER-FOR-ICP-PORT-ENTRY",AB_package);
    Qshutdown_reclaimer_for_icp_object = 
	    STATIC_SYMBOL("SHUTDOWN-RECLAIMER-FOR-ICP-OBJECT",AB_package);
    Qremove_icp_port_entries_from_icp_object = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qremove_icp_port_entries_from_icp_object,
	    STATIC_FUNCTION(remove_icp_port_entries_from_icp_object,NIL,
	    FALSE,3,3));
    Qremove_icp_port_entries_from_icp_object_list = 
	    STATIC_SYMBOL("REMOVE-ICP-PORT-ENTRIES-FROM-ICP-OBJECT-LIST",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qremove_icp_port_entries_from_icp_object_list,
	    STATIC_FUNCTION(remove_icp_port_entries_from_icp_object_list,
	    NIL,FALSE,3,3));
    Qitem_index_space = STATIC_SYMBOL("ITEM-INDEX-SPACE",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qframe_serial_number = STATIC_SYMBOL("FRAME-SERIAL-NUMBER",AB_package);
    Qderegister_and_register_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-AND-REGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    float_constant = STATIC_FLOAT(0.25);
    Enqueue_reclaim_index_space_message_interval = float_constant;
    Qacknowledge_deregister_corresponding_icp_object = 
	    STATIC_SYMBOL("ACKNOWLEDGE-DEREGISTER-CORRESPONDING-ICP-OBJECT",
	    AB_package);
    Qderegister_original_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-ORIGINAL-ICP-OBJECT",AB_package);
    Qdelete_icp_object_for_process_with_deassign = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS-WITH-DEASSIGN",
	    AB_package);
    Qdelete_icp_object_for_process = 
	    STATIC_SYMBOL("DELETE-ICP-OBJECT-FOR-PROCESS",AB_package);
    Qderegister_corresponding_icp_object_with_deassign = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT-WITH-DEASSIGN",
	    AB_package);
    Qderegister_corresponding_icp_object = 
	    STATIC_SYMBOL("DEREGISTER-CORRESPONDING-ICP-OBJECT",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsend_queued_reclaim_index_space_messages = 
	    STATIC_SYMBOL("SEND-QUEUED-RECLAIM-INDEX-SPACE-MESSAGES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_queued_reclaim_index_space_messages,
	    STATIC_FUNCTION(send_queued_reclaim_index_space_messages,NIL,
	    FALSE,1,1));
    Qsend_icp_shut_down_data_server = 
	    STATIC_SYMBOL("SEND-ICP-SHUT-DOWN-DATA-SERVER",AB_package);
    Qshut_down_data_server = STATIC_SYMBOL("SHUT-DOWN-DATA-SERVER",AB_package);
    string_constant_11 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_12 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qsend_icp_shut_down_data_server,
	    STATIC_FUNCTION(send_icp_shut_down_data_server,NIL,FALSE,0,0));
    Qreceived_shutdown_request = STATIC_SYMBOL("RECEIVED-SHUTDOWN-REQUEST",
	    AB_package);
    Qhandle_icp_shut_down_data_server = 
	    STATIC_SYMBOL("HANDLE-ICP-SHUT-DOWN-DATA-SERVER",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_shut_down_data_server,
	    STATIC_FUNCTION(handle_icp_shut_down_data_server,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_shut_down_data_server,
	    FIX((SI_Long)70L));
    Qacknowledge_shutdown = STATIC_SYMBOL("ACKNOWLEDGE-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qacknowledge_shutdown,
	    STATIC_FUNCTION(acknowledge_shutdown,NIL,FALSE,1,1));
    Qsend_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("SEND-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_acknowledge_shutdown,
	    STATIC_FUNCTION(send_icp_acknowledge_shutdown,NIL,FALSE,0,0));
    Qhandle_icp_acknowledge_shutdown = 
	    STATIC_SYMBOL("HANDLE-ICP-ACKNOWLEDGE-SHUTDOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_acknowledge_shutdown,
	    STATIC_FUNCTION(handle_icp_acknowledge_shutdown,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_acknowledge_shutdown,
	    FIX((SI_Long)336L));
    if (In_recursive_gsi_context == UNBOUND)
	In_recursive_gsi_context = Nil;
    Qtime_out_icp_socket = STATIC_SYMBOL("TIME-OUT-ICP-SOCKET",AB_package);
    Qshutdown_timed_out_awaiting_acknowledgement = 
	    STATIC_SYMBOL("SHUTDOWN-TIMED-OUT-AWAITING-ACKNOWLEDGEMENT",
	    AB_package);
    Qshutdown_icp_socket_after_connect = 
	    STATIC_SYMBOL("SHUTDOWN-ICP-SOCKET-AFTER-CONNECT",AB_package);
    SET_SYMBOL_FUNCTION(Qshutdown_icp_socket_after_connect,
	    STATIC_FUNCTION(shutdown_icp_socket_after_connect,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtime_out_icp_socket,
	    STATIC_FUNCTION(time_out_icp_socket,NIL,FALSE,2,2));
    if (Check_icp_handshaking_p == UNBOUND)
	Check_icp_handshaking_p = Nil;
    Icp_handshake_registry = Nil;
    Qdynamic_data_cold_link = STATIC_SYMBOL("DYNAMIC-DATA-COLD-LINK",
	    AB_package);
    Qdynamic_data_terminate = STATIC_SYMBOL("DYNAMIC-DATA-TERMINATE",
	    AB_package);
    Qdynamic_data_supplied = STATIC_SYMBOL("DYNAMIC-DATA-SUPPLIED",AB_package);
    Qdynamic_data_request = STATIC_SYMBOL("DYNAMIC-DATA-REQUEST",AB_package);
    Qdynamic_data_acknowledge = STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE",
	    AB_package);
    Qdynamic_data_initiate = STATIC_SYMBOL("DYNAMIC-DATA-INITIATE",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)5L,Qdynamic_data_terminate,
	    Qdynamic_data_supplied,Qdynamic_data_request,
	    Qdynamic_data_acknowledge,Qdynamic_data_initiate);
    Qdynamic_data_initiate_1 = STATIC_SYMBOL("DYNAMIC-DATA-INITIATE-1",
	    AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Kstart,Qnil,
	    Qdynamic_data_initiate_1);
    list_constant_2 = STATIC_CONS(Klocal,Qnil);
    list_constant_3 = STATIC_CONS(Qdynamic_data_initiate,list_constant_2);
    Qdynamic_data_acknowledge_1 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-1",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qdynamic_data_initiate_1,
	    list_constant_3,Qdynamic_data_acknowledge_1);
    Kremote = STATIC_SYMBOL("REMOTE",Pkeyword);
    list_constant_4 = STATIC_CONS(Kremote,Qnil);
    list_constant_5 = STATIC_CONS(Qdynamic_data_acknowledge,list_constant_4);
    Qicp_handshake_disjunction_1 = 
	    STATIC_SYMBOL("ICP-HANDSHAKE-DISJUNCTION-1",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)3L,Qdynamic_data_acknowledge_1,
	    list_constant_5,Qicp_handshake_disjunction_1);
    Qdynamic_data_request_1 = STATIC_SYMBOL("DYNAMIC-DATA-REQUEST-1",
	    AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)3L,
	    Qicp_handshake_disjunction_1,Qnil,Qdynamic_data_request_1);
    Qdynamic_data_request_2 = STATIC_SYMBOL("DYNAMIC-DATA-REQUEST-2",
	    AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)3L,
	    Qicp_handshake_disjunction_1,Qnil,Qdynamic_data_request_2);
    list_constant_6 = STATIC_CONS(Qdynamic_data_request,list_constant_2);
    Qdynamic_data_supplied_1 = STATIC_SYMBOL("DYNAMIC-DATA-SUPPLIED-1",
	    AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qdynamic_data_request_1,
	    list_constant_6,Qdynamic_data_supplied_1);
    list_constant_7 = STATIC_CONS(Qdynamic_data_supplied,list_constant_4);
    Qdynamic_data_acknowledge_2 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-2",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qdynamic_data_supplied_1,
	    list_constant_7,Qdynamic_data_acknowledge_2);
    Kpositive = STATIC_SYMBOL("POSITIVE",Pkeyword);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qdynamic_data_acknowledge,
	    Klocal,Kpositive);
    Qdynamic_data_terminate_1 = STATIC_SYMBOL("DYNAMIC-DATA-TERMINATE-1",
	    AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qdynamic_data_acknowledge_2,
	    list_constant_8,Qdynamic_data_terminate_1);
    Qdynamic_data_acknowledge_3 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-3",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qdynamic_data_request_2,
	    list_constant_6,Qdynamic_data_acknowledge_3);
    Knegative = STATIC_SYMBOL("NEGATIVE",Pkeyword);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qdynamic_data_acknowledge,
	    Kremote,Knegative);
    list_constant_10 = STATIC_CONS(Kend,Qnil);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge_3,list_constant_9,list_constant_10);
    list_constant_11 = STATIC_CONS(Qdynamic_data_terminate,list_constant_2);
    Qdynamic_data_terminate_2 = STATIC_SYMBOL("DYNAMIC-DATA-TERMINATE-2",
	    AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qdynamic_data_terminate_1,
	    list_constant_11,Qdynamic_data_terminate_2);
    list_constant_12 = STATIC_CONS(Qdynamic_data_terminate,list_constant_4);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_terminate_2,list_constant_12,list_constant_10);
    list_constant_26 = STATIC_LIST((SI_Long)12L,list_constant_13,
	    list_constant_14,list_constant_15,list_constant_16,
	    list_constant_17,list_constant_18,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23,list_constant_24);
    pushnew_arg_1 = LIST_3(Qdynamic_data_cold_link,list_constant_25,
	    list_constant_26);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qfirst);
    icp_handshake_registry_new_value = adjoin(4,pushnew_arg_1,
	    Icp_handshake_registry,Kkey,pushnew_arg_3);
    Icp_handshake_registry = icp_handshake_registry_new_value;
    Qdynamic_data_hot_link = STATIC_SYMBOL("DYNAMIC-DATA-HOT-LINK",AB_package);
    Qdynamic_data_unadvise = STATIC_SYMBOL("DYNAMIC-DATA-UNADVISE",AB_package);
    Qdynamic_data_advise = STATIC_SYMBOL("DYNAMIC-DATA-ADVISE",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qdynamic_data_acknowledge,
	    Qdynamic_data_initiate);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)5L,
	    Qdynamic_data_terminate,Qdynamic_data_unadvise,
	    Qdynamic_data_supplied,Qdynamic_data_advise,list_constant_27);
    Qdynamic_data_advise_1 = STATIC_SYMBOL("DYNAMIC-DATA-ADVISE-1",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)3L,
	    Qicp_handshake_disjunction_1,Qnil,Qdynamic_data_advise_1);
    Qdynamic_data_advise_2 = STATIC_SYMBOL("DYNAMIC-DATA-ADVISE-2",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)3L,
	    Qicp_handshake_disjunction_1,Qnil,Qdynamic_data_advise_2);
    Khot = STATIC_SYMBOL("HOT",Pkeyword);
    list_constant_28 = STATIC_LIST((SI_Long)3L,Qdynamic_data_advise,Klocal,
	    Khot);
    list_constant_29 = STATIC_CONS(Qdynamic_data_acknowledge_2,Qnil);
    list_constant_39 = STATIC_LIST_STAR((SI_Long)3L,Qdynamic_data_advise_1,
	    list_constant_28,list_constant_29);
    list_constant_30 = STATIC_CONS(Kpositive,Qnil);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge,Kremote,list_constant_30);
    list_constant_32 = STATIC_CONS(Qdynamic_data_supplied_1,Qnil);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge_2,list_constant_31,list_constant_32);
    list_constant_33 = STATIC_CONS(Qdynamic_data_acknowledge_3,Qnil);
    list_constant_41 = STATIC_LIST_STAR((SI_Long)3L,Qdynamic_data_advise_2,
	    list_constant_28,list_constant_33);
    Qdynamic_data_acknowledge_4 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-4",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qdynamic_data_supplied_1,
	    list_constant_7,Qdynamic_data_acknowledge_4);
    list_constant_34 = STATIC_CONS(Qdynamic_data_acknowledge,list_constant_2);
    Qicp_handshake_any_number_1 = 
	    STATIC_SYMBOL("ICP-HANDSHAKE-ANY-NUMBER-1",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)3L,Qdynamic_data_acknowledge_4,
	    list_constant_34,Qicp_handshake_any_number_1);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,
	    Qicp_handshake_any_number_1,Qnil,list_constant_32);
    Qdynamic_data_unadvise_1 = STATIC_SYMBOL("DYNAMIC-DATA-UNADVISE-1",
	    AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qicp_handshake_any_number_1,
	    Qnil,Qdynamic_data_unadvise_1);
    list_constant_35 = STATIC_CONS(Qdynamic_data_unadvise,list_constant_2);
    Qdynamic_data_acknowledge_5 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-5",AB_package);
    list_constant_46 = STATIC_LIST((SI_Long)3L,Qdynamic_data_unadvise_1,
	    list_constant_35,Qdynamic_data_acknowledge_5);
    list_constant_36 = STATIC_CONS(Qdynamic_data_terminate_1,Qnil);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge_5,list_constant_5,list_constant_36);
    list_constant_48 = STATIC_LIST((SI_Long)2L,list_constant_23,
	    list_constant_24);
    list_constant_50 = STATIC_LIST_STAR((SI_Long)16L,list_constant_13,
	    list_constant_14,list_constant_15,list_constant_37,
	    list_constant_38,list_constant_39,list_constant_40,
	    list_constant_41,list_constant_22,list_constant_42,
	    list_constant_43,list_constant_44,list_constant_45,
	    list_constant_46,list_constant_47,list_constant_48);
    pushnew_arg_1 = LIST_3(Qdynamic_data_hot_link,list_constant_49,
	    list_constant_50);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qfirst);
    icp_handshake_registry_new_value = adjoin(4,pushnew_arg_1,
	    Icp_handshake_registry,Kkey,pushnew_arg_3);
    Icp_handshake_registry = icp_handshake_registry_new_value;
    Qdynamic_data_warm_link = STATIC_SYMBOL("DYNAMIC-DATA-WARM-LINK",
	    AB_package);
    list_constant_51 = STATIC_LIST_STAR((SI_Long)3L,Qdynamic_data_supplied,
	    Qdynamic_data_advise,list_constant_27);
    list_constant_71 = STATIC_LIST_STAR((SI_Long)4L,
	    Qdynamic_data_terminate,Qdynamic_data_unadvise,
	    Qdynamic_data_request,list_constant_51);
    Kwarm = STATIC_SYMBOL("WARM",Pkeyword);
    list_constant_52 = STATIC_LIST((SI_Long)3L,Qdynamic_data_advise,Klocal,
	    Kwarm);
    list_constant_60 = STATIC_LIST_STAR((SI_Long)3L,Qdynamic_data_advise_1,
	    list_constant_52,list_constant_29);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,Qdynamic_data_advise_2,
	    list_constant_52,list_constant_33);
    Knull_item = STATIC_SYMBOL("NULL-ITEM",Pkeyword);
    list_constant_53 = STATIC_LIST((SI_Long)3L,Qdynamic_data_supplied,
	    Kremote,Knull_item);
    list_constant_54 = STATIC_CONS(Qdynamic_data_acknowledge_4,Qnil);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_supplied_1,list_constant_53,list_constant_54);
    list_constant_55 = STATIC_CONS(Qdynamic_data_request_1,Qnil);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge_4,list_constant_34,list_constant_55);
    Qdynamic_data_supplied_2 = STATIC_SYMBOL("DYNAMIC-DATA-SUPPLIED-2",
	    AB_package);
    list_constant_64 = STATIC_LIST((SI_Long)3L,Qdynamic_data_request_1,
	    list_constant_6,Qdynamic_data_supplied_2);
    Qicp_handshake_at_most_once_1 = 
	    STATIC_SYMBOL("ICP-HANDSHAKE-AT-MOST-ONCE-1",AB_package);
    list_constant_56 = STATIC_CONS(Qicp_handshake_at_most_once_1,Qnil);
    list_constant_65 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_request_1,Qnil,list_constant_56);
    list_constant_57 = STATIC_CONS(Qdynamic_data_acknowledge_5,Qnil);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_supplied_2,list_constant_7,list_constant_57);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)3L,
	    Qdynamic_data_acknowledge_5,list_constant_34,list_constant_56);
    list_constant_58 = STATIC_CONS(Qicp_handshake_any_number_1,Qnil);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)3L,
	    Qicp_handshake_at_most_once_1,Qnil,list_constant_58);
    Qdynamic_data_acknowledge_6 = 
	    STATIC_SYMBOL("DYNAMIC-DATA-ACKNOWLEDGE-6",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)3L,Qdynamic_data_unadvise_1,
	    list_constant_35,Qdynamic_data_acknowledge_6);
    list_constant_59 = STATIC_CONS(list_constant_5,list_constant_36);
    list_constant_70 = STATIC_CONS(Qdynamic_data_acknowledge_6,
	    list_constant_59);
    list_constant_72 = STATIC_LIST_STAR((SI_Long)22L,list_constant_13,
	    list_constant_14,list_constant_15,list_constant_37,
	    list_constant_38,list_constant_60,list_constant_40,
	    list_constant_61,list_constant_22,list_constant_62,
	    list_constant_63,list_constant_64,list_constant_65,
	    list_constant_64,list_constant_66,list_constant_67,
	    list_constant_68,list_constant_44,list_constant_45,
	    list_constant_69,list_constant_70,list_constant_48);
    pushnew_arg_1 = LIST_3(Qdynamic_data_warm_link,list_constant_71,
	    list_constant_72);
    pushnew_arg_3 = SYMBOL_FUNCTION(Qfirst);
    icp_handshake_registry_new_value = adjoin(4,pushnew_arg_1,
	    Icp_handshake_registry,Kkey,pushnew_arg_3);
    Icp_handshake_registry = icp_handshake_registry_new_value;
}
