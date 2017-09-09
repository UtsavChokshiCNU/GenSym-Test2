/* web.c
 * Input file:  web.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "web.h"


/* ABANDON-SHIP */
Object g2int_abandon_ship varargs_1(int, n)
{
    Object format_string;
    Object arg;
    Declare_varargs_nonrelocating;

    x_note_fn_call(58,0);
    INIT_ARGS_nonrelocating();
    format_string = REQUIRED_ARG_nonrelocating();
    arg = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    format((SI_Long)2L,T,"~%Error occured:~%    ");
    formatn(3,T,format_string,arg);
    return g2int_thread_kill(G2int_current_thread);
}

static Object string_constant;     /* "Error: ~D" */

/* ABANDON-SHIP-ERRCODE */
Object g2int_abandon_ship_errcode(code)
    Object code;
{
    x_note_fn_call(58,1);
    return g2int_abandon_ship(2,string_constant,code);
}

Object G2int_currently_open_tcpip_sockets = UNBOUND;

Object G2int_the_type_description_of_client_socket = UNBOUND;

Object G2int_chain_of_available_client_sockets = UNBOUND;

Object G2int_client_socket_count = UNBOUND;

/* RECLAIM-CLIENT-SOCKET-1 */
Object g2int_reclaim_client_socket_1(client_socket)
    Object client_socket;
{
    Object svref_new_value;

    x_note_fn_call(58,2);
    inline_note_reclaim_cons(client_socket,Nil);
    svref_new_value = G2int_chain_of_available_client_sockets;
    SVREF(client_socket,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_client_sockets = client_socket;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CLIENT-SOCKET */
Object g2int_reclaim_structure_for_client_socket(client_socket)
    Object client_socket;
{
    x_note_fn_call(58,3);
    return g2int_reclaim_client_socket_1(client_socket);
}

static Object Qg2_defstruct_structure_name_client_socket_g2_struct;  /* g2-defstruct-structure-name::client-socket-g2-struct */

/* MAKE-PERMANENT-CLIENT-SOCKET-STRUCTURE-INTERNAL */
Object g2int_make_permanent_client_socket_structure_internal()
{
    Object def_structure_client_socket_variable, client_socket_count_new_value;
    Object defstruct_g2_client_socket_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(58,4);
    def_structure_client_socket_variable = Nil;
    client_socket_count_new_value = FIXNUM_ADD1(G2int_client_socket_count);
    G2int_client_socket_count = client_socket_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_client_socket_variable = Nil;
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
	defstruct_g2_client_socket_variable = the_array;
	SVREF(defstruct_g2_client_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_client_socket_g2_struct;
	SVREF(defstruct_g2_client_socket_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_client_socket_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_client_socket_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_client_socket_variable,FIX((SI_Long)4L)) = Nil;
	def_structure_client_socket_variable = 
		defstruct_g2_client_socket_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_client_socket_variable);
}

static Object Kborn;               /* :born */

/* MAKE-CLIENT-SOCKET-1 */
Object g2int_make_client_socket_1()
{
    Object def_structure_client_socket_variable, svref_new_value;

    x_note_fn_call(58,5);
    def_structure_client_socket_variable = 
	    G2int_chain_of_available_client_sockets;
    if (def_structure_client_socket_variable) {
	G2int_chain_of_available_client_sockets = 
		ISVREF(def_structure_client_socket_variable,(SI_Long)0L);
	SVREF(def_structure_client_socket_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_client_socket_g2_struct;
    }
    else
	def_structure_client_socket_variable = 
		g2int_make_permanent_client_socket_structure_internal();
    inline_note_allocate_cons(def_structure_client_socket_variable,Nil);
    svref_new_value = G2int_current_thread;
    SVREF(def_structure_client_socket_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_client_socket_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_client_socket_variable,FIX((SI_Long)3L)) = Kborn;
    ISVREF(def_structure_client_socket_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_client_socket_variable);
}

static Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

static Object Qg2int_socket_connect;  /* socket-connect */

/* SOCKET-CONNECT */
Object g2int_socket_connect(client_socket,host,port)
    Object client_socket, host, port;
{
    Object gensymed_symbol, inheritance_path, method, next_path;
    Object result;

    x_note_fn_call(58,6);
    gensymed_symbol = ISVREF(client_socket,(SI_Long)0L);
    inheritance_path = 
	    ISVREF(g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)2L);
    result = g2int_slowly_lookup_next_method(Qg2int_socket_connect,
	    inheritance_path);
    MVS_2(result,method,next_path);
    return FUNCALL_4(method,next_path,client_socket,host,port);
}

static Object Kok;                 /* :ok */

static Object Kconnect_failure;    /* :connect-failure */

/* M-SOCKET-CONNECT-CLIENT-SOCKET-1 */
Object g2int_m_socket_connect_client_socket_1(path,client_socket,host,port)
    Object path, client_socket, host, port;
{
    volatile Object exit_ok;
    SI_Long ab_loop_repeat_;
    int socket_number_or_errcode;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,7);
    SAVE_STACK();
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	socket_number_or_errcode = 
		g2pvt_tcpip_connect(ISTRING(g2int_coerce_into_foreign_string_pad(host)),
		INTEGER_TO_INT(port));
	if (socket_number_or_errcode < (SI_Long)0L)
	    SAVE_VALUES(g2int_note_issue_with_socket(client_socket,
		    INT_TO_INTEGER(socket_number_or_errcode)));
	else {
	    g2int_socket_install(client_socket,
		    INT_TO_INTEGER(socket_number_or_errcode));
	    ab_loop_repeat_ = (SI_Long)30L;
	  next_loop:
	    if ( !((SI_Long)0L < ab_loop_repeat_))
		goto end_loop;
	    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	    if (EQ(Kok,
		    g2int_tcp_connection_check(INT_TO_INTEGER(socket_number_or_errcode)))) 
			{
		SAVE_VALUES(VALUES_1(Nil));
		goto end;
	    }
	    lsleep(FIX((SI_Long)1L));
	    goto next_loop;
	  end_loop:
	    g2int_note_issue_with_socket(client_socket,Kconnect_failure);
	    SAVE_VALUES(VALUES_1(Qnil));
	  end:;
	}
	exit_ok = T;
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)4L,T,"socket-connect ~A:~D",host,port);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Kpending;            /* :pending */

static Object Kdead;               /* :dead */

static Object Ktcpip_connect_retry_select_failed;  /* :tcpip_connect_retry_select_failed */

/* TCP-CONNECTION-CHECK */
Object g2int_tcp_connection_check(socket_number)
    Object socket_number;
{
    volatile Object exit_ok;
    int result_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,8);
    SAVE_STACK();
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	result_1 = gw_tcpip_connection_check(IFIX(socket_number));
	if ((SI_Long)1L == result_1)
	    SAVE_VALUES(VALUES_1(Kok));
	else if ((SI_Long)0L == result_1)
	    SAVE_VALUES(VALUES_1(Kpending));
	else if ((SI_Long)-1L == result_1)
	    SAVE_VALUES(VALUES_1(Kdead));
	else if ((SI_Long)-6L == result_1)
	    SAVE_VALUES(VALUES_1(Ktcpip_connect_retry_select_failed));
	else
	    SAVE_VALUES(g2int_abandon_ship_errcode(INT_TO_INTEGER(result_1)));
	exit_ok = T;
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)2L,T,"checking status of connection");
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* SOCKET-WRITE-STRING */
Object g2int_socket_write_string(socket_1,string_1)
    Object socket_1, string_1;
{
    volatile Object exit_ok;
    Object temp, temp_2;
    char *temp_1;
    int result_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,9);
    SAVE_STACK();
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = ISVREF(socket_1,(SI_Long)2L);
	temp_1 = ISTRING(g2int_coerce_into_foreign_string_pad(string_1));
	temp_2 = length(string_1);
	result_1 = gw_socket_write(INTEGER_TO_INT(temp),temp_1,(SI_Long)0L,
		INTEGER_TO_INT(temp_2));
	if ( !(result_1 == IFIX(length(string_1))))
	    SAVE_VALUES(g2int_note_issue_with_socket(socket_1,
		    INT_TO_INTEGER(result_1)));
	else
	    SAVE_VALUES(VALUES_1(Nil));
	exit_ok = T;
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)2L,T,"Sending data");
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_1;   /* "socket-write-line ~S /= ~S" */

/* SOCKET-WRITE-LINE */
Object g2int_socket_write_line(socket_1,line)
    Object socket_1, line;
{
    volatile Object exit_ok;
    Object length_1, temp;
    int result_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,10);
    SAVE_STACK();
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	length_1 = add(FIX((SI_Long)2L),length(line));
	temp = ISVREF(socket_1,(SI_Long)2L);
	result_1 = gw_socket_write(INTEGER_TO_INT(temp),
		ISTRING(g2int_coerce_into_foreign_string_pad_with_crlf(line)),
		(SI_Long)0L,INTEGER_TO_INT(length_1));
	if ( !(result_1 == IFIX(length_1))) {
	    g2int_notify_user_at_console(3,string_constant_1,
		    INT_TO_INTEGER(result_1),length_1);
	    SAVE_VALUES(g2int_note_issue_with_socket(socket_1,
		    INT_TO_INTEGER(result_1)));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
	exit_ok = T;
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)2L,T,"Sending data");
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Keof;                /* :eof */

/* SOCKET-READ-STRING */
Object g2int_socket_read_string(socket_1)
    Object socket_1;
{
    volatile Object exit_ok;
    Object temp;
    int result_1, errno_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,11);
    SAVE_STACK();
    g2int_socket_poll_status(socket_1);
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	temp = ISVREF(socket_1,(SI_Long)2L);
	result_1 = gw_socket_read(INTEGER_TO_INT(temp),
		ISTRING(G2int_current_foreign_string_pad),
		INTEGER_TO_INT(G2int_max_of_foreign_string_pad));
	errno_1 = gw_fetch_errno();
	if ((SI_Long)0L == result_1 || (SI_Long)-1L == result_1 && 
		(IFIX(G2int_enetreset) == errno_1 || 
		IFIX(G2int_econnaborted) == errno_1))
	    temp = Keof;
	else if ((SI_Long)0L < result_1)
	    temp = 
		    g2int_make_text_string_from_foreign_string_pad(INT_TO_INTEGER(result_1));
	else {
	    g2int_note_issue_with_socket(socket_1,INT_TO_INTEGER(result_1));
	    temp = Keof;
	}
	exit_ok = T;
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)2L,T,"Reading data");
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    temp = result;
    g2int_socket_poll_status(socket_1);
    RESTORE_STACK();
    return VALUES_1(temp);
}

/* SOCKET-DATA-AVAILABLE-P */
Object g2int_socket_data_available_p(socket_1)
    Object socket_1;
{
    volatile Object exit_ok;
    int result_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(58,12);
    SAVE_STACK();
    g2int_socket_poll_status(socket_1);
    exit_ok = Nil;
    if (PUSH_UNWIND_PROTECT(0)) {
	result_1 = gw_socket_data_available_p(IFIX(ISVREF(socket_1,
		(SI_Long)2L)));
	if ((SI_Long)0L == result_1)
	    SAVE_VALUES(VALUES_1(Nil));
	else if ((SI_Long)1L == result_1)
	    SAVE_VALUES(VALUES_1(T));
	else
	    SAVE_VALUES(VALUES_1(Qnil));
	exit_ok = T;
    }
    POP_UNWIND_PROTECT(0);
    if ( !TRUEP(exit_ok)) {
	format((SI_Long)2L,T,"~%");
	format((SI_Long)2L,T,"Polling for data");
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object G2int_fetch_style_info_prop = UNBOUND;

Object G2int_the_type_description_of_fetch_style_info = UNBOUND;

Object G2int_chain_of_available_fetch_style_infos = UNBOUND;

Object G2int_fetch_style_info_count = UNBOUND;

/* RECLAIM-FETCH-STYLE-INFO-1 */
Object g2int_reclaim_fetch_style_info_1(fetch_style_info)
    Object fetch_style_info;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(58,13);
    inline_note_reclaim_cons(fetch_style_info,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = fetch_style_info;
    g2int_reclaim_gensym_string(ISVREF(fetch_style_info,(SI_Long)9L));
    SVREF(fetch_style_info,FIX((SI_Long)9L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_fetch_style_infos;
    SVREF(fetch_style_info,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_fetch_style_infos = fetch_style_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FETCH-STYLE-INFO */
Object g2int_reclaim_structure_for_fetch_style_info(fetch_style_info)
    Object fetch_style_info;
{
    x_note_fn_call(58,14);
    return g2int_reclaim_fetch_style_info_1(fetch_style_info);
}

static Object Qg2_defstruct_structure_name_fetch_style_info_g2_struct;  /* g2-defstruct-structure-name::fetch-style-info-g2-struct */

/* MAKE-PERMANENT-FETCH-STYLE-INFO-STRUCTURE-INTERNAL */
Object g2int_make_permanent_fetch_style_info_structure_internal()
{
    Object def_structure_fetch_style_info_variable;
    Object fetch_style_info_count_new_value;
    Object defstruct_g2_fetch_style_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(58,15);
    def_structure_fetch_style_info_variable = Nil;
    fetch_style_info_count_new_value = 
	    FIXNUM_ADD1(G2int_fetch_style_info_count);
    G2int_fetch_style_info_count = fetch_style_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_fetch_style_info_variable = Nil;
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
	defstruct_g2_fetch_style_info_variable = the_array;
	SVREF(defstruct_g2_fetch_style_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fetch_style_info_g2_struct;
	def_structure_fetch_style_info_variable = 
		defstruct_g2_fetch_style_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_fetch_style_info_variable);
}

static Object string_constant_2;   /* "" */

/* MAKE-FETCH-STYLE-INFO-1 */
Object g2int_make_fetch_style_info_1(name_of_fetch_style,
	    verb_of_fetch_style_info,maximum_size_for_resource,
	    return_server_prefix_of_fetch_style,
	    return_resource_of_fetch_style,
	    return_cache_filename_of_fetch_style,
	    ignore_cache_of_fetch_style,note_progress_while_fetching)
    Object name_of_fetch_style, verb_of_fetch_style_info;
    Object maximum_size_for_resource, return_server_prefix_of_fetch_style;
    Object return_resource_of_fetch_style;
    Object return_cache_filename_of_fetch_style, ignore_cache_of_fetch_style;
    Object note_progress_while_fetching;
{
    Object def_structure_fetch_style_info_variable, svref_new_value;

    x_note_fn_call(58,16);
    def_structure_fetch_style_info_variable = 
	    G2int_chain_of_available_fetch_style_infos;
    if (def_structure_fetch_style_info_variable) {
	G2int_chain_of_available_fetch_style_infos = 
		ISVREF(def_structure_fetch_style_info_variable,(SI_Long)0L);
	SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fetch_style_info_g2_struct;
    }
    else
	def_structure_fetch_style_info_variable = 
		g2int_make_permanent_fetch_style_info_structure_internal();
    inline_note_allocate_cons(def_structure_fetch_style_info_variable,Nil);
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)1L)) = 
	    name_of_fetch_style;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)2L)) = 
	    verb_of_fetch_style_info;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)3L)) = 
	    maximum_size_for_resource;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)4L)) = 
	    return_server_prefix_of_fetch_style;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)5L)) = 
	    return_resource_of_fetch_style;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)6L)) = 
	    return_cache_filename_of_fetch_style;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)7L)) = 
	    ignore_cache_of_fetch_style;
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)8L)) = 
	    note_progress_while_fetching;
    svref_new_value = g2int_copy_gensym_string(string_constant_2);
    SVREF(def_structure_fetch_style_info_variable,FIX((SI_Long)9L)) = 
	    svref_new_value;
    return VALUES_1(def_structure_fetch_style_info_variable);
}

static Object Qg2int_fetch_style_info;  /* fetch-style-info */

/* INSTALL-FETCH-STYLE */
Object g2int_install_fetch_style(name,fetch_style_info)
    Object name, fetch_style_info;
{
    Object old_definition_qm;

    x_note_fn_call(58,17);
    old_definition_qm = 
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qg2int_fetch_style_info);
    if (old_definition_qm)
	g2int_reclaim_fetch_style_info_1(old_definition_qm);
    return g2int_mutate_global_property(name,fetch_style_info,
	    Qg2int_fetch_style_info);
}

static Object Qg2int_default;      /* default */

/* INITIALIZE-FETCH-STYLES-OF-CONTEXT */
Object g2int_initialize_fetch_styles_of_context()
{
    x_note_fn_call(58,18);
    return g2int_install_fetch_style(Qg2int_default,
	    g2int_make_fetch_style_info_1(Qg2int_default,Qget,
	    FIX((SI_Long)0L),Nil,T,Nil,T,T));
}

/* SHUTDOWN-FETCH-STYLES-OF-CONTEXT */
Object g2int_shutdown_fetch_styles_of_context()
{
    x_note_fn_call(58,19);
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_fetch_thread = UNBOUND;

Object G2int_chain_of_available_fetch_threads = UNBOUND;

Object G2int_fetch_thread_count = UNBOUND;

/* RECLAIM-FETCH-THREAD-1 */
Object g2int_reclaim_fetch_thread_1(fetch_thread)
    Object fetch_thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(58,20);
    inline_note_reclaim_cons(fetch_thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = fetch_thread;
    g2int_reclaim_sockets(ISVREF(fetch_thread,(SI_Long)11L));
    SVREF(fetch_thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(fetch_thread,(SI_Long)12L));
    SVREF(fetch_thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_fetch_threads;
    SVREF(fetch_thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_fetch_threads = fetch_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FETCH-THREAD */
Object g2int_reclaim_structure_for_fetch_thread(fetch_thread)
    Object fetch_thread;
{
    x_note_fn_call(58,21);
    return g2int_reclaim_fetch_thread_1(fetch_thread);
}

static Object Qg2_defstruct_structure_name_fetch_thread_g2_struct;  /* g2-defstruct-structure-name::fetch-thread-g2-struct */

/* MAKE-PERMANENT-FETCH-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_fetch_thread_structure_internal()
{
    Object def_structure_fetch_thread_variable, temp;
    Object defstruct_g2_fetch_thread_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(58,22);
    def_structure_fetch_thread_variable = Nil;
    temp = FIXNUM_ADD1(G2int_fetch_thread_count);
    G2int_fetch_thread_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_fetch_thread_variable = Nil;
	gensymed_symbol_1 = (SI_Long)23L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_fetch_thread_variable = the_array;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fetch_thread_g2_struct;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_fetch_thread_variable,FIX((SI_Long)18L)) = Nil;
	def_structure_fetch_thread_variable = 
		defstruct_g2_fetch_thread_variable;
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)18L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_fetch_threads;
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_fetch_threads = 
		def_structure_fetch_thread_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_fetch_thread_variable);
}

static Object Knew;                /* :new */

static Object Kallocated;          /* :allocated */

static Object Qg2int_null_thread_contour_wrapper;  /* null-thread-contour-wrapper */

/* MAKE-FETCH-THREAD-1 */
Object g2int_make_fetch_thread_1()
{
    Object def_structure_fetch_thread_variable, svref_new_value;

    x_note_fn_call(58,23);
    def_structure_fetch_thread_variable = 
	    G2int_chain_of_available_fetch_threads;
    if (def_structure_fetch_thread_variable) {
	G2int_chain_of_available_fetch_threads = 
		ISVREF(def_structure_fetch_thread_variable,(SI_Long)0L);
	SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_fetch_thread_g2_struct;
    }
    else
	def_structure_fetch_thread_variable = 
		g2int_make_permanent_fetch_thread_structure_internal();
    inline_note_allocate_cons(def_structure_fetch_thread_variable,Nil);
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)8L)) = Kallocated;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_fetch_thread_variable,(SI_Long)10L) = 
	    FIX((SI_Long)100L);
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)14L)) = 
	    svref_new_value;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_fetch_thread_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_fetch_thread_variable);
}

/* M-THREAD-FEED-TRACE-FETCH-THREAD-1 */
Object g2int_m_thread_feed_trace_fetch_thread_1(path,fetch_thread)
    Object path, fetch_thread;
{
    x_note_fn_call(58,24);
    return format((SI_Long)5L,T,"~&Feeding ~S ~S ~S",fetch_thread,
	    ISVREF(fetch_thread,(SI_Long)19L),ISVREF(fetch_thread,
	    (SI_Long)21L));
}

static Object Kquantum_in_progress;  /* :quantum-in-progress */

static Object Kinitialize;         /* :initialize */

static Object Qg2int_awaiting_connection;  /* awaiting-connection */

static Object string_constant_3;   /* "Unable to connect to HTTP proxy server." */

static Object Qg2int_unable_to_connect_to_http_proxy;  /* unable-to-connect-to-http-proxy */

static Object Qg2int_requesting_resource;  /* requesting-resource */

static Object Qg2int_awaiting_resource;  /* awaiting-resource */

static Object Kcheck_for_data;     /* :check-for-data */

static Object Kcleanup;            /* :cleanup */

static Object Qg2int_resource_fetched;  /* resource-fetched */

static Object Qg2int_resource_too_large;  /* resource-too-large */

static Object string_constant_4;   /* "Resource was larger than maximum set in fetch-style" */

static Object Kend_data;           /* :end-data */

static Object Kreturn;             /* :return */

static Object Qg2int_fetching_resource;  /* fetching-resource */

static Object Kadd_data;           /* :add-data */

static Object Knot_runnable;       /* :not-runnable */

static Object Kio_wait;            /* :io-wait */

static Object Kcontinuation_taken_care_of;  /* :continuation-taken-care-of */

/* MT-DO-WEB-QUERY */
Object g2int_mt_do_web_query()
{
    Object program_counter, pending_continuation, frame, proxy_server;
    Object proxy_port, url, document_qm, data_handler, status_callback;
    Object socket_1, byte_count, svref_arg_1;
    volatile Object exit_ok;
    Object data_or_eof, max_1, incf_arg;
    Declare_stack_pointer;
    Declare_catch(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(58,25);
    SAVE_STACK();
    if (PUSH_AREA(Dynamic_area,0)) {
	program_counter = ISVREF(G2int_current_thread,(SI_Long)16L);
	pending_continuation = Nil;
	frame = ISVREF(G2int_current_thread,(SI_Long)13L);
	proxy_server = ISVREF(frame,(SI_Long)5L);
	proxy_port = ISVREF(frame,(SI_Long)6L);
	url = ISVREF(frame,(SI_Long)7L);
	document_qm = ISVREF(frame,(SI_Long)8L);
	data_handler = ISVREF(frame,(SI_Long)9L);
	status_callback = ISVREF(frame,(SI_Long)10L);
	socket_1 = ISVREF(frame,(SI_Long)11L);
	byte_count = ISVREF(frame,(SI_Long)12L);
	svref_arg_1 = G2int_current_thread;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kquantum_in_progress;
	if (EQ(program_counter,Kinitialize)) {
	    FUNCALL_3(status_callback,Qg2int_awaiting_connection,
		    FIX((SI_Long)-1L),FIX((SI_Long)-1L));
	    socket_1 = g2int_make_client_socket_1();
	    g2int_socket_connect(socket_1,proxy_server,proxy_port);
	    if (ISVREF(socket_1,(SI_Long)3L)) {
		g2int_notify_user_at_console(1,string_constant_3);
		g2int_signal_from_rpc(Qg2int_unable_to_connect_to_http_proxy,
			string_constant_3);
	    }
	    exit_ok = Nil;
	    if (PUSH_UNWIND_PROTECT(0)) {
		FUNCALL_3(status_callback,Qg2int_requesting_resource,
			FIX((SI_Long)-1L),FIX((SI_Long)-1L));
		g2int_socket_write_http_request(socket_1,url,
			ISVREF(G2int_current_thread,(SI_Long)20L),document_qm);
		exit_ok = T;
	    }
	    POP_UNWIND_PROTECT(0);
	    if ( !TRUEP(exit_ok)) {
		format((SI_Long)2L,T,"~%");
		format((SI_Long)2L,T,"Writing Query");
	    }
	    CONTINUE_UNWINDING(0);
	    FUNCALL_3(status_callback,Qg2int_awaiting_resource,
		    FIX((SI_Long)-1L),FIX((SI_Long)-1L));
	    pending_continuation = Kcheck_for_data;
	}
	else if (EQ(program_counter,Kcleanup)) {
	    if (socket_1) {
		g2int_socket_close_it(socket_1);
		g2int_reclaim_client_socket_1(socket_1);
	    }
	}
	else if (EQ(program_counter,Kcheck_for_data)) {
	    if (g2int_socket_data_available_p(socket_1)) {
		data_or_eof = g2int_socket_read_string(socket_1);
		if (EQ(data_or_eof,Keof)) {
		    FUNCALL_3(status_callback,Qg2int_resource_fetched,
			    byte_count,FIX((SI_Long)-1L));
		    max_1 = ISVREF(ISVREF(G2int_current_thread,
			    (SI_Long)20L),(SI_Long)3L);
		    if ((SI_Long)0L < IFIX(max_1) && FIXNUM_LT(max_1,
			    byte_count))
			g2int_signal_from_rpc(Qg2int_resource_too_large,
				string_constant_4);
		    FUNCALL_2(data_handler,Kend_data,Nil);
		    pending_continuation = Kreturn;
		}
		else {
		    incf_arg = length(data_or_eof);
		    byte_count = add(byte_count,incf_arg);
		    FUNCALL_3(status_callback,Qg2int_fetching_resource,
			    byte_count,FIX((SI_Long)-1L));
		    FUNCALL_2(data_handler,Kadd_data,data_or_eof);
		    pending_continuation = Kcheck_for_data;
		}
	    }
	    else {
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)7L)) = Knot_runnable;
		svref_arg_1 = G2int_current_thread;
		SVREF(svref_arg_1,FIX((SI_Long)8L)) = Kio_wait;
		pending_continuation = Kcheck_for_data;
	    }
	}
	else
	    error((SI_Long)1L,"No handler for this continuation.");
	SVREF(frame,FIX((SI_Long)5L)) = proxy_server;
	SVREF(frame,FIX((SI_Long)6L)) = proxy_port;
	SVREF(frame,FIX((SI_Long)7L)) = url;
	SVREF(frame,FIX((SI_Long)8L)) = document_qm;
	SVREF(frame,FIX((SI_Long)9L)) = data_handler;
	SVREF(frame,FIX((SI_Long)10L)) = status_callback;
	SVREF(frame,FIX((SI_Long)11L)) = socket_1;
	SVREF(frame,FIX((SI_Long)12L)) = byte_count;
	if ( !TRUEP(pending_continuation) &&  !EQ(Kcleanup,program_counter))
	    error((SI_Long)1L,"No continuation.");
	if ( !EQ(Kcontinuation_taken_care_of,pending_continuation)) {
	    svref_arg_1 = G2int_current_thread;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    pending_continuation);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_AREA(0);
    RESTORE_STACK();
    return result;
}

static Object Qg2int_mt_do_web_query;  /* mt-do-web-query */

/* DO-WEB-QUERY */
Object g2int_do_web_query(return_continuation,proxy_server,proxy_port,url,
	    document_qm,data_handler,status_callback)
    Object return_continuation, proxy_server, proxy_port, url, document_qm;
    Object data_handler, status_callback;
{
    Object frame, socket_1;
    SI_Long byte_count;

    x_note_fn_call(58,26);
    frame = g2int_prolog_thread_function(return_continuation,
	    SYMBOL_FUNCTION(Qg2int_mt_do_web_query),FIX((SI_Long)13L));
    SVREF(frame,FIX((SI_Long)5L)) = proxy_server;
    SVREF(frame,FIX((SI_Long)6L)) = proxy_port;
    SVREF(frame,FIX((SI_Long)7L)) = url;
    SVREF(frame,FIX((SI_Long)8L)) = document_qm;
    SVREF(frame,FIX((SI_Long)9L)) = data_handler;
    SVREF(frame,FIX((SI_Long)10L)) = status_callback;
    socket_1 = Nil;
    byte_count = (SI_Long)0L;
    SVREF(frame,FIX((SI_Long)11L)) = socket_1;
    return VALUES_1(ISVREF(frame,(SI_Long)12L) = FIX(byte_count));
}

static Object Qg2int_gensym_string;  /* gensym-string */

static Object string_constant_5;   /* "GET " */

static Object Qg2int_post;         /* post */

static Object string_constant_6;   /* "POST " */

static Object Qg2int_put;          /* put */

static Object string_constant_7;   /* "PUT " */

static Object string_constant_8;   /* " HTTP/1.0" */

static Object string_constant_9;   /* "User-Agent: gensym-web-gsi/0.1" */

static Object string_constant_10;  /* "Accept: text/plain, image/gif" */

static Object string_constant_11;  /* "Content-Length: ~D" */

/* SOCKET-WRITE-HTTP-REQUEST */
Object g2int_socket_write_http_request(socket_1,url,fetch_style_info,
	    document_qm)
    Object socket_1, url, fetch_style_info, document_qm;
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object document_as_internet_text_qm, temp, verb, str, dst, header;
    Object user_message_headers;
    SI_Long src, ab_loop_bind_;
    char char_new_value;
    Declare_special(4);

    x_note_fn_call(58,27);
    if (document_qm) {
	current_gensym_string = 
		g2int_obtain_simple_gensym_string(FIX((SI_Long)2048L));
	PUSH_SPECIAL(G2int_current_gensym_string,current_gensym_string,3);
	  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
	  PUSH_SPECIAL(G2int_fill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
		  2);
	    total_length_of_current_gensym_string = FIX((SI_Long)2048L);
	    PUSH_SPECIAL(G2int_total_length_of_current_gensym_string,total_length_of_current_gensym_string,
		    1);
	      current_twriting_output_type = Qg2int_gensym_string;
	      PUSH_SPECIAL(G2int_current_twriting_output_type,current_twriting_output_type,
		      0);
		g2int_twrite_text_gensym_pt_to_i_ascii(document_qm);
		document_as_internet_text_qm = 
			g2int_copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	document_as_internet_text_qm = Nil;
    temp = ISVREF(fetch_style_info,(SI_Long)2L);
    if (EQ(temp,Qget))
	verb = string_constant_5;
    else if (EQ(temp,Qg2int_post))
	verb = string_constant_6;
    else if (EQ(temp,Qg2int_put))
	verb = string_constant_7;
    else
	verb = Qnil;
    str = 
	    g2int_obtain_simple_gensym_string(FIX(IFIX(FIXNUM_ADD(length(verb),
	    length(url))) + (SI_Long)9L));
    dst = FIX((SI_Long)0L);
    src = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(verb));
  next_loop:
    if (src >= ab_loop_bind_)
	goto end_loop;
    char_new_value = ICHAR(verb,src);
    SET_CHAR(str,dst,CHR(char_new_value));
    dst = FIXNUM_ADD1(dst);
    src = src + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    src = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(url));
  next_loop_1:
    if (src >= ab_loop_bind_)
	goto end_loop_1;
    char_new_value = ICHAR(url,src);
    SET_CHAR(str,dst,CHR(char_new_value));
    dst = FIXNUM_ADD1(dst);
    src = src + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    src = (SI_Long)0L;
  next_loop_2:
    if (src >= (SI_Long)9L)
	goto end_loop_2;
    char_new_value = ICHAR(string_constant_8,src);
    SET_CHAR(str,dst,CHR(char_new_value));
    dst = FIXNUM_ADD1(dst);
    src = src + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:;
    g2int_socket_write_line(socket_1,str);
    g2int_reclaim_gensym_string(str);
    g2int_socket_write_line(socket_1,string_constant_9);
    g2int_socket_write_line(socket_1,string_constant_10);
    if (document_as_internet_text_qm) {
	header = g2int_tformat_gensym_string(2,string_constant_11,
		length(document_as_internet_text_qm));
	g2int_socket_write_line(socket_1,header);
	g2int_reclaim_gensym_string(header);
    }
    user_message_headers = ISVREF(fetch_style_info,(SI_Long)9L);
    if ( !((SI_Long)0L == IFIX(length(user_message_headers))))
	g2int_socket_write_string(socket_1,ISVREF(fetch_style_info,
		(SI_Long)9L));
    g2int_socket_write_line(socket_1,string_constant_2);
    g2int_socket_write_line(socket_1,string_constant_2);
    if (document_as_internet_text_qm) {
	g2int_socket_write_string(socket_1,document_as_internet_text_qm);
	return g2int_reclaim_gensym_string(document_as_internet_text_qm);
    }
    else
	return VALUES_1(Nil);
}

Object G2int_the_type_description_of_bridge_configuration_info = UNBOUND;

Object G2int_chain_of_available_bridge_configuration_infos = UNBOUND;

Object G2int_bridge_configuration_info_count = UNBOUND;

/* RECLAIM-BRIDGE-CONFIGURATION-INFO-1 */
Object g2int_reclaim_bridge_configuration_info_1(bridge_configuration_info)
    Object bridge_configuration_info;
{
    Object svref_new_value;

    x_note_fn_call(58,28);
    inline_note_reclaim_cons(bridge_configuration_info,Nil);
    svref_new_value = G2int_chain_of_available_bridge_configuration_infos;
    SVREF(bridge_configuration_info,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_bridge_configuration_infos = 
	    bridge_configuration_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BRIDGE-CONFIGURATION-INFO */
Object g2int_reclaim_structure_for_bridge_configuration_info(bridge_configuration_info)
    Object bridge_configuration_info;
{
    x_note_fn_call(58,29);
    return g2int_reclaim_bridge_configuration_info_1(bridge_configuration_info);
}

static Object Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct;  /* g2-defstruct-structure-name::bridge-configuration-info-g2-struct */

/* MAKE-PERMANENT-BRIDGE-CONFIGURATION-INFO-STRUCTURE-INTERNAL */
Object g2int_make_permanent_bridge_configuration_info_structure_internal()
{
    Object def_structure_bridge_configuration_info_variable;
    Object bridge_configuration_info_count_new_value;
    Object defstruct_g2_bridge_configuration_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(58,30);
    def_structure_bridge_configuration_info_variable = Nil;
    bridge_configuration_info_count_new_value = 
	    FIXNUM_ADD1(G2int_bridge_configuration_info_count);
    G2int_bridge_configuration_info_count = 
	    bridge_configuration_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_bridge_configuration_info_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_bridge_configuration_info_variable = the_array;
	SVREF(defstruct_g2_bridge_configuration_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct;
	def_structure_bridge_configuration_info_variable = 
		defstruct_g2_bridge_configuration_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_bridge_configuration_info_variable);
}

/* MAKE-BRIDGE-CONFIGURATION-INFO-1-1 */
Object g2int_make_bridge_configuration_info_1_1()
{
    Object def_structure_bridge_configuration_info_variable;

    x_note_fn_call(58,31);
    def_structure_bridge_configuration_info_variable = 
	    G2int_chain_of_available_bridge_configuration_infos;
    if (def_structure_bridge_configuration_info_variable) {
	G2int_chain_of_available_bridge_configuration_infos = 
		ISVREF(def_structure_bridge_configuration_info_variable,
		(SI_Long)0L);
	SVREF(def_structure_bridge_configuration_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct;
    }
    else
	def_structure_bridge_configuration_info_variable = 
		g2int_make_permanent_bridge_configuration_info_structure_internal();
    inline_note_allocate_cons(def_structure_bridge_configuration_info_variable,
	    Nil);
    SVREF(def_structure_bridge_configuration_info_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_bridge_configuration_info_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_bridge_configuration_info_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_bridge_configuration_info_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_bridge_configuration_info_variable,
	    FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_bridge_configuration_info_variable,(SI_Long)6L) = 
	    FIX((SI_Long)10L);
    ISVREF(def_structure_bridge_configuration_info_variable,(SI_Long)7L) = 
	    FIX((SI_Long)30L);
    return VALUES_1(def_structure_bridge_configuration_info_variable);
}

/* MAKE-BRIDGE-CONFIGURATION-INFO */
Object g2int_make_bridge_configuration_info()
{
    x_note_fn_call(58,32);
    return g2int_make_bridge_configuration_info_1_1();
}

Object G2int_the_bridge_configuration_info = UNBOUND;

Object G2int_the_state_of_g2 = UNBOUND;

/* SCAN-HEADER-LINE */
Object g2int_scan_header_line(mark_of_resource_buffer)
    Object mark_of_resource_buffer;
{
    Object field_name, start_field_value, c, temp;
    SI_Long i;

    x_note_fn_call(58,33);
    g2int_mark_set(G2int_current_left_of_parsing,
	    G2int_current_right_of_parsing);
    if (g2int_scan_blank_line()) {
	g2int_mark_set(G2int_current_right_of_parsing,
		G2int_current_left_of_parsing);
	return VALUES_1(Nil);
    }
    else {
	field_name = Nil;
	g2int_scan_upto_character(CHR(':'));
	field_name = g2int_get_simple_text_from_last_scan();
	g2int_mark_move(G2int_current_right_of_parsing,FIX((SI_Long)1L));
	start_field_value = g2int_mark_copy(G2int_current_right_of_parsing);
	i = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(g2int_scan_to_beginning_of_next_line())) {
	    g2int_mark_set(G2int_current_right_of_parsing,
		    G2int_current_left_of_parsing);
	    return VALUES_1(Nil);
	}
	c = g2int_mark_peek_character(G2int_current_right_of_parsing);
	if ( !(EQ(CHR(' '),c) || EQ(CHR('\t'),c))) {
	    temp = field_name;
	    g2int_normalize_server_header_and_save(mark_of_resource_buffer,
		    temp,g2int_copy_text_between_marks(start_field_value,
		    G2int_current_right_of_parsing));
	    return VALUES_1(T);
	}
	if ((SI_Long)1000L < i) {
	    g2int_mark_set(G2int_current_right_of_parsing,
		    G2int_current_left_of_parsing);
	    return VALUES_1(Nil);
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
	g2int_mark_kill(start_field_value);
	return VALUES_1(temp);
    }
}

static Object Qg2int_mimi_headers_from_server;  /* mimi-headers-from-server */

/* NORMALIZE-SERVER-HEADER-AND-SAVE */
Object g2int_normalize_server_header_and_save(mark_of_resource_buffer,
	    field_name,folded_field_value)
    Object mark_of_resource_buffer, field_name, folded_field_value;
{
    Object dst_i, squeeze_white, start_qm, char_1, white_qm, temp, result_1;
    Object unfolded_field_value;
    SI_Long src_i, ab_loop_bind_, i;
    char char_new_value;

    x_note_fn_call(58,34);
    dst_i = FIX((SI_Long)0L);
    squeeze_white = T;
    start_qm = T;
    src_i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(folded_field_value));
    char_1 = Nil;
    white_qm = Nil;
  next_loop:
    if (src_i >= ab_loop_bind_)
	goto end_loop;
    char_1 = CHR(ICHAR(folded_field_value,src_i));
    temp = EQ(CHR(' '),char_1) ? T : Nil;
    if (temp);
    else
	temp = EQ(CHR('\n'),char_1) ? T : Nil;
    if (temp);
    else
	temp = EQ(CHR('\r'),char_1) ? T : Nil;
    if (temp);
    else
	temp = EQ(CHR('\t'),char_1) ? T : Nil;
    white_qm = temp;
    if (squeeze_white && white_qm);
    else if (EQ(CHR('\n'),char_1) || EQ(CHR('\r'),char_1))
	squeeze_white = T;
    else {
	if (squeeze_white &&  !TRUEP(start_qm)) {
	    temp = CHR(' ');
	    SET_CHAR(folded_field_value,dst_i,temp);
	    dst_i = FIXNUM_ADD1(dst_i);
	}
	squeeze_white = Nil;
	start_qm = Nil;
	SET_CHAR(folded_field_value,dst_i,char_1);
	dst_i = FIXNUM_ADD1(dst_i);
    }
    src_i = src_i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    result_1 = g2int_obtain_simple_gensym_string(dst_i);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(dst_i);
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    char_new_value = ICHAR(folded_field_value,i);
    SET_ICHAR(result_1,i,char_new_value);
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    unfolded_field_value = result_1;
    goto end;
    unfolded_field_value = Qnil;
  end:;
    goto end_1;
    unfolded_field_value = Qnil;
  end_1:;
    g2int_reclaim_gensym_string(folded_field_value);
    temp = g2int_gensym_cons_1(field_name,unfolded_field_value);
    return g2int_set_property_of_buffer(mark_of_resource_buffer,
	    Qg2int_mimi_headers_from_server,g2int_gensym_cons_1(temp,
	    g2int_get_property_of_buffer(mark_of_resource_buffer,
	    Qg2int_mimi_headers_from_server)));
}

Object G2int_the_type_description_of_proxy_fetch_thread = UNBOUND;

Object G2int_chain_of_available_proxy_fetch_threads = UNBOUND;

Object G2int_proxy_fetch_thread_count = UNBOUND;

/* RECLAIM-PROXY-FETCH-THREAD-1 */
Object g2int_reclaim_proxy_fetch_thread_1(proxy_fetch_thread)
    Object proxy_fetch_thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(58,35);
    inline_note_reclaim_cons(proxy_fetch_thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = proxy_fetch_thread;
    g2int_reclaim_sockets(ISVREF(proxy_fetch_thread,(SI_Long)11L));
    SVREF(proxy_fetch_thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(proxy_fetch_thread,(SI_Long)12L));
    SVREF(proxy_fetch_thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_proxy_fetch_threads;
    SVREF(proxy_fetch_thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_proxy_fetch_threads = proxy_fetch_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PROXY-FETCH-THREAD */
Object g2int_reclaim_structure_for_proxy_fetch_thread(proxy_fetch_thread)
    Object proxy_fetch_thread;
{
    x_note_fn_call(58,36);
    return g2int_reclaim_proxy_fetch_thread_1(proxy_fetch_thread);
}

static Object Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct;  /* g2-defstruct-structure-name::proxy-fetch-thread-g2-struct */

/* MAKE-PERMANENT-PROXY-FETCH-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_proxy_fetch_thread_structure_internal()
{
    Object def_structure_proxy_fetch_thread_variable, temp;
    Object defstruct_g2_proxy_fetch_thread_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(58,37);
    def_structure_proxy_fetch_thread_variable = Nil;
    temp = FIXNUM_ADD1(G2int_proxy_fetch_thread_count);
    G2int_proxy_fetch_thread_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_proxy_fetch_thread_variable = Nil;
	gensymed_symbol_1 = (SI_Long)20L;
	the_array = make_array(1,FIX(gensymed_symbol_1));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol_1;
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop:;
	defstruct_g2_proxy_fetch_thread_variable = the_array;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)10L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)11L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)12L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)13L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)14L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)15L)) 
		= Nil;
	SVREF(defstruct_g2_proxy_fetch_thread_variable,FIX((SI_Long)16L)) 
		= Nil;
	def_structure_proxy_fetch_thread_variable = 
		defstruct_g2_proxy_fetch_thread_variable;
	SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)5L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_proxy_fetch_threads;
	SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)0L)) 
		= temp;
	G2int_chain_of_available_proxy_fetch_threads = 
		def_structure_proxy_fetch_thread_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_proxy_fetch_thread_variable);
}

/* MAKE-PROXY-FETCH-THREAD-1 */
Object g2int_make_proxy_fetch_thread_1()
{
    Object def_structure_proxy_fetch_thread_variable, svref_new_value;

    x_note_fn_call(58,38);
    def_structure_proxy_fetch_thread_variable = 
	    G2int_chain_of_available_proxy_fetch_threads;
    if (def_structure_proxy_fetch_thread_variable) {
	G2int_chain_of_available_proxy_fetch_threads = 
		ISVREF(def_structure_proxy_fetch_thread_variable,(SI_Long)0L);
	SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct;
    }
    else
	def_structure_proxy_fetch_thread_variable = 
		g2int_make_permanent_proxy_fetch_thread_structure_internal();
    inline_note_allocate_cons(def_structure_proxy_fetch_thread_variable,Nil);
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)8L)) = 
	    Kallocated;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_proxy_fetch_thread_variable,(SI_Long)10L) = 
	    FIX((SI_Long)100L);
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)14L)) = 
	    svref_new_value;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_proxy_fetch_thread_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_proxy_fetch_thread_variable);
}

static Object Kdo_fetch;           /* :do-fetch */

static Object Kwrapup;             /* :wrapup */

static Object Qg2int_handle_incomming_data_for_proxy_fetch_thread;  /* handle-incomming-data-for-proxy-fetch-thread */

static Object Qg2int_notify_no_op;  /* notify-no-op */

/* MT-MAIN-FOR-PROXY-FETCH-THREAD */
Object g2int_mt_main_for_proxy_fetch_thread()
{
    Object program_counter, pending_continuation, frame, input_mark;
    Object next_thread, url, svref_arg_1;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(58,39);
    if (PUSH_AREA(Dynamic_area,0)) {
	program_counter = ISVREF(G2int_current_thread,(SI_Long)16L);
	pending_continuation = Nil;
	frame = ISVREF(G2int_current_thread,(SI_Long)13L);
	input_mark = ISVREF(frame,(SI_Long)5L);
	next_thread = ISVREF(frame,(SI_Long)6L);
	url = ISVREF(frame,(SI_Long)7L);
	svref_arg_1 = G2int_current_thread;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Kquantum_in_progress;
	if (EQ(program_counter,Kinitialize)) {
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)17L)) = input_mark;
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)18L)) = next_thread;
	    svref_arg_1 = G2int_current_thread;
	    SVREF(svref_arg_1,FIX((SI_Long)19L)) = url;
	    pending_continuation = Kdo_fetch;
	}
	else if (EQ(program_counter,Kdo_fetch)) {
	    g2int_do_web_query(Kwrapup,
		    ISVREF(G2int_the_bridge_configuration_info,
		    (SI_Long)3L),
		    ISVREF(G2int_the_bridge_configuration_info,
		    (SI_Long)4L),url,Nil,
		    SYMBOL_FUNCTION(Qg2int_handle_incomming_data_for_proxy_fetch_thread),
		    SYMBOL_FUNCTION(Qg2int_notify_no_op));
	    pending_continuation = Kcontinuation_taken_care_of;
	}
	else if (EQ(program_counter,Kwrapup))
	    pending_continuation = Kreturn;
	else if (EQ(program_counter,Kcleanup));
	else
	    error((SI_Long)1L,"No handler for this continuation.");
	SVREF(frame,FIX((SI_Long)5L)) = input_mark;
	SVREF(frame,FIX((SI_Long)6L)) = next_thread;
	SVREF(frame,FIX((SI_Long)7L)) = url;
	if ( !TRUEP(pending_continuation) &&  !EQ(Kcleanup,program_counter))
	    error((SI_Long)1L,"No continuation.");
	if ( !EQ(Kcontinuation_taken_care_of,pending_continuation)) {
	    svref_arg_1 = G2int_current_thread;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    pending_continuation);
	}
	else
	    result = VALUES_1(Nil);
    }
    POP_AREA(0);
    return result;
}

static Object Qg2int_mt_main_for_proxy_fetch_thread;  /* mt-main-for-proxy-fetch-thread */

/* MAIN-FOR-PROXY-FETCH-THREAD */
Object g2int_main_for_proxy_fetch_thread(return_continuation,input_mark,
	    next_thread,url)
    Object return_continuation, input_mark, next_thread, url;
{
    Object frame;

    x_note_fn_call(58,40);
    frame = g2int_prolog_thread_function(return_continuation,
	    SYMBOL_FUNCTION(Qg2int_mt_main_for_proxy_fetch_thread),
	    FIX((SI_Long)8L));
    SVREF(frame,FIX((SI_Long)5L)) = input_mark;
    SVREF(frame,FIX((SI_Long)6L)) = next_thread;
    SVREF(frame,FIX((SI_Long)7L)) = url;
    return VALUES_1(Nil);
}

/* HANDLE-INCOMMING-DATA-FOR-PROXY-FETCH-THREAD */
Object g2int_handle_incomming_data_for_proxy_fetch_thread(status,string_qm)
    Object status, string_qm;
{
    x_note_fn_call(58,41);
    if (EQ(Kadd_data,status)) {
	g2int_insert_text_at_mark(ISVREF(G2int_current_thread,
		(SI_Long)17L),string_qm);
	return g2int_thread_enqueue_event(ISVREF(G2int_current_thread,
		(SI_Long)18L),Kadd_data);
    }
    else if (EQ(Kend_data,status))
	return g2int_thread_enqueue_event(ISVREF(G2int_current_thread,
		(SI_Long)18L),Kend_data);
    else
	return VALUES_1(Qnil);
}

/* NOTIFY-NO-OP */
Object g2int_notify_no_op(status,metric,max_1)
    Object status, metric, max_1;
{
    x_note_fn_call(58,42);
    return VALUES_1(Nil);
}

void web_INIT()
{
    Object temp, reclaim_structure_for_client_socket;
    Object reclaim_structure_for_fetch_style_info;
    Object reclaim_structure_for_fetch_thread;
    Object reclaim_structure_for_bridge_configuration_info;
    Object reclaim_structure_for_proxy_fetch_thread;
    Object AB_package, Qg2int_proxy_fetch_thread, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_proxy_fetch_thread_count;
    Object Qg2int_chain_of_available_proxy_fetch_threads;
    Object Qg2int_type_description_of_type, string_constant_16;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Kunconnected, list_constant;
    Object Qg2int_web, Qg2int_the_bridge_configuration_info;
    Object Qg2int_make_bridge_configuration_info, Kfuncall;
    Object Qg2int_bridge_configuration_info;
    Object Qg2int_bridge_configuration_info_count;
    Object Qg2int_chain_of_available_bridge_configuration_infos;
    Object string_constant_15, Qg2int_m_thread_feed_trace_fetch_thread_1;
    Object Qg2int_fetch_thread, Qg2int_thread_feed_trace;
    Object Qg2int_fetch_thread_count, Qg2int_chain_of_available_fetch_threads;
    Object string_constant_14, Qg2int_fetch_style_info_count;
    Object Qg2int_chain_of_available_fetch_style_infos, string_constant_13;
    Object Qg2int_m_socket_connect_client_socket_1, Qg2int_client_socket;
    Object Qg2int_client_socket_count;
    Object Qg2int_chain_of_available_client_sockets, string_constant_12;

    x_note_fn_call(58,43);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("Error: ~D");
    if (G2int_currently_open_tcpip_sockets == UNBOUND)
	G2int_currently_open_tcpip_sockets = Nil;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_client_socket_g2_struct = 
	    STATIC_SYMBOL("CLIENT-SOCKET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_client_socket = STATIC_SYMBOL("CLIENT-SOCKET",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_client_socket_g2_struct,
	    Qg2int_client_socket,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_client_socket,
	    Qg2_defstruct_structure_name_client_socket_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_client_socket == UNBOUND)
	G2int_the_type_description_of_client_socket = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8l83hy1o83hy83Ly8m8k1l83Ly0000001m1m8o83Ly1n8n83*hy0kpk0k0");
    temp = G2int_the_type_description_of_client_socket;
    G2int_the_type_description_of_client_socket = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_12));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_client_socket_g2_struct,
	    G2int_the_type_description_of_client_socket,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_client_socket,
	    G2int_the_type_description_of_client_socket,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_client_sockets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CLIENT-SOCKETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_client_sockets,
	    G2int_chain_of_available_client_sockets);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_client_sockets,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_client_socket_count = STATIC_SYMBOL("CLIENT-SOCKET-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_client_socket_count,
	    G2int_client_socket_count);
    g2int_record_system_variable(Qg2int_client_socket_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_client_socket = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_client_socket,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_client_socket,reclaim_structure_for_client_socket);
    Kborn = STATIC_SYMBOL("BORN",Pkeyword);
    Qg2int_socket_connect = STATIC_SYMBOL("SOCKET-CONNECT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_socket_connect,
	    STATIC_FUNCTION(g2int_socket_connect,NIL,FALSE,3,3));
    Kok = STATIC_SYMBOL("OK",Pkeyword);
    Kconnect_failure = STATIC_SYMBOL("CONNECT-FAILURE",Pkeyword);
    Qg2int_m_socket_connect_client_socket_1 = 
	    STATIC_SYMBOL("M-SOCKET-CONNECT-CLIENT-SOCKET-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_socket_connect_client_socket_1,
	    STATIC_FUNCTION(g2int_m_socket_connect_client_socket_1,NIL,
	    FALSE,4,4));
    set_get(Qg2int_socket_connect,Qg2int_client_socket,
	    Qg2int_m_socket_connect_client_socket_1);
    Kpending = STATIC_SYMBOL("PENDING",Pkeyword);
    Kdead = STATIC_SYMBOL("DEAD",Pkeyword);
    Ktcpip_connect_retry_select_failed = 
	    STATIC_SYMBOL("TCPIP_CONNECT_RETRY_SELECT_FAILED",Pkeyword);
    string_constant_1 = STATIC_STRING("socket-write-line ~S /= ~S");
    Keof = STATIC_SYMBOL("EOF",Pkeyword);
    Qg2int_fetch_style_info = STATIC_SYMBOL("FETCH-STYLE-INFO",AB_package);
    G2int_fetch_style_info_prop = Qg2int_fetch_style_info;
    Qg2_defstruct_structure_name_fetch_style_info_g2_struct = 
	    STATIC_SYMBOL("FETCH-STYLE-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_fetch_style_info_g2_struct,
	    Qg2int_fetch_style_info,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_fetch_style_info,
	    Qg2_defstruct_structure_name_fetch_style_info_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_fetch_style_info == UNBOUND)
	G2int_the_type_description_of_fetch_style_info = Nil;
    string_constant_13 = 
	    STATIC_STRING("43Dy8l83xy1n83xy8m8k1l8m0000001l1n8n83*ky1s83=Vy831Fy83=Uy830jy830iy830hy83*-y83=Yykuk0k0");
    temp = G2int_the_type_description_of_fetch_style_info;
    G2int_the_type_description_of_fetch_style_info = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_13));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_fetch_style_info_g2_struct,
	    G2int_the_type_description_of_fetch_style_info,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_fetch_style_info,
	    G2int_the_type_description_of_fetch_style_info,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_fetch_style_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FETCH-STYLE-INFOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_fetch_style_infos,
	    G2int_chain_of_available_fetch_style_infos);
    g2int_record_system_variable(Qg2int_chain_of_available_fetch_style_infos,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_fetch_style_info_count = STATIC_SYMBOL("FETCH-STYLE-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fetch_style_info_count,
	    G2int_fetch_style_info_count);
    g2int_record_system_variable(Qg2int_fetch_style_info_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_fetch_style_info = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_fetch_style_info,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_fetch_style_info,reclaim_structure_for_fetch_style_info);
    string_constant_2 = STATIC_STRING("");
    Qg2int_default = STATIC_SYMBOL("DEFAULT",AB_package);
    Qg2_defstruct_structure_name_fetch_thread_g2_struct = 
	    STATIC_SYMBOL("FETCH-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_fetch_thread = STATIC_SYMBOL("FETCH-THREAD",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_fetch_thread_g2_struct,
	    Qg2int_fetch_thread,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_fetch_thread,
	    Qg2_defstruct_structure_name_fetch_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_fetch_thread == UNBOUND)
	G2int_the_type_description_of_fetch_thread = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8l83-+y1p83-+y83Py83Cy8m8k1l83Py0000001m1m8o83Py1n8n83*ly0k3Jyk0k0");
    temp = G2int_the_type_description_of_fetch_thread;
    G2int_the_type_description_of_fetch_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_14));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_fetch_thread_g2_struct,
	    G2int_the_type_description_of_fetch_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_fetch_thread,
	    G2int_the_type_description_of_fetch_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_fetch_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FETCH-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_fetch_threads,
	    G2int_chain_of_available_fetch_threads);
    g2int_record_system_variable(Qg2int_chain_of_available_fetch_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_fetch_thread_count = STATIC_SYMBOL("FETCH-THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_fetch_thread_count,
	    G2int_fetch_thread_count);
    g2int_record_system_variable(Qg2int_fetch_thread_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_fetch_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_fetch_thread,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_fetch_thread,reclaim_structure_for_fetch_thread);
    Knew = STATIC_SYMBOL("NEW",Pkeyword);
    Kallocated = STATIC_SYMBOL("ALLOCATED",Pkeyword);
    Qg2int_null_thread_contour_wrapper = 
	    STATIC_SYMBOL("NULL-THREAD-CONTOUR-WRAPPER",AB_package);
    Qg2int_thread_feed_trace = STATIC_SYMBOL("THREAD-FEED-TRACE",AB_package);
    Qg2int_m_thread_feed_trace_fetch_thread_1 = 
	    STATIC_SYMBOL("M-THREAD-FEED-TRACE-FETCH-THREAD-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_m_thread_feed_trace_fetch_thread_1,
	    STATIC_FUNCTION(g2int_m_thread_feed_trace_fetch_thread_1,NIL,
	    FALSE,2,2));
    set_get(Qg2int_thread_feed_trace,Qg2int_fetch_thread,
	    Qg2int_m_thread_feed_trace_fetch_thread_1);
    Kquantum_in_progress = STATIC_SYMBOL("QUANTUM-IN-PROGRESS",Pkeyword);
    Kinitialize = STATIC_SYMBOL("INITIALIZE",Pkeyword);
    Qg2int_awaiting_connection = STATIC_SYMBOL("AWAITING-CONNECTION",
	    AB_package);
    string_constant_3 = 
	    STATIC_STRING("Unable to connect to HTTP proxy server.");
    Qg2int_unable_to_connect_to_http_proxy = 
	    STATIC_SYMBOL("UNABLE-TO-CONNECT-TO-HTTP-PROXY",AB_package);
    Qg2int_requesting_resource = STATIC_SYMBOL("REQUESTING-RESOURCE",
	    AB_package);
    Qg2int_awaiting_resource = STATIC_SYMBOL("AWAITING-RESOURCE",AB_package);
    Kcheck_for_data = STATIC_SYMBOL("CHECK-FOR-DATA",Pkeyword);
    Kcleanup = STATIC_SYMBOL("CLEANUP",Pkeyword);
    Qg2int_resource_fetched = STATIC_SYMBOL("RESOURCE-FETCHED",AB_package);
    Qg2int_resource_too_large = STATIC_SYMBOL("RESOURCE-TOO-LARGE",AB_package);
    string_constant_4 = 
	    STATIC_STRING("Resource was larger than maximum set in fetch-style");
    Kend_data = STATIC_SYMBOL("END-DATA",Pkeyword);
    Kreturn = STATIC_SYMBOL("RETURN",Pkeyword);
    Qg2int_fetching_resource = STATIC_SYMBOL("FETCHING-RESOURCE",AB_package);
    Kadd_data = STATIC_SYMBOL("ADD-DATA",Pkeyword);
    Knot_runnable = STATIC_SYMBOL("NOT-RUNNABLE",Pkeyword);
    Kio_wait = STATIC_SYMBOL("IO-WAIT",Pkeyword);
    Kcontinuation_taken_care_of = 
	    STATIC_SYMBOL("CONTINUATION-TAKEN-CARE-OF",Pkeyword);
    Qg2int_mt_do_web_query = STATIC_SYMBOL("MT-DO-WEB-QUERY",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mt_do_web_query,
	    STATIC_FUNCTION(g2int_mt_do_web_query,NIL,FALSE,0,0));
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    string_constant_5 = STATIC_STRING("GET ");
    Qg2int_post = STATIC_SYMBOL("POST",AB_package);
    string_constant_6 = STATIC_STRING("POST ");
    Qg2int_put = STATIC_SYMBOL("PUT",AB_package);
    string_constant_7 = STATIC_STRING("PUT ");
    string_constant_8 = STATIC_STRING(" HTTP/1.0");
    string_constant_9 = STATIC_STRING("User-Agent: gensym-web-gsi/0.1");
    string_constant_10 = STATIC_STRING("Accept: text/plain, image/gif");
    string_constant_11 = STATIC_STRING("Content-Length: ~D");
    Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct = 
	    STATIC_SYMBOL("BRIDGE-CONFIGURATION-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_bridge_configuration_info = 
	    STATIC_SYMBOL("BRIDGE-CONFIGURATION-INFO",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct,
	    Qg2int_bridge_configuration_info,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_bridge_configuration_info,
	    Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_bridge_configuration_info == UNBOUND)
	G2int_the_type_description_of_bridge_configuration_info = Nil;
    string_constant_15 = 
	    STATIC_STRING("43Dy8l83gy1n83gy8m8k1l8m0000001l1n8n83*gy0ksk0k0");
    temp = G2int_the_type_description_of_bridge_configuration_info;
    G2int_the_type_description_of_bridge_configuration_info = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_15));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_bridge_configuration_info_g2_struct,
	    G2int_the_type_description_of_bridge_configuration_info,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_bridge_configuration_info,
	    G2int_the_type_description_of_bridge_configuration_info,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_bridge_configuration_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BRIDGE-CONFIGURATION-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_bridge_configuration_infos,
	    G2int_chain_of_available_bridge_configuration_infos);
    g2int_record_system_variable(Qg2int_chain_of_available_bridge_configuration_infos,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_bridge_configuration_info_count = 
	    STATIC_SYMBOL("BRIDGE-CONFIGURATION-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_bridge_configuration_info_count,
	    G2int_bridge_configuration_info_count);
    g2int_record_system_variable(Qg2int_bridge_configuration_info_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_bridge_configuration_info = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_bridge_configuration_info,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_bridge_configuration_info,
	    reclaim_structure_for_bridge_configuration_info);
    Qg2int_the_bridge_configuration_info = 
	    STATIC_SYMBOL("THE-BRIDGE-CONFIGURATION-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_the_bridge_configuration_info,
	    G2int_the_bridge_configuration_info);
    Qg2int_web = STATIC_SYMBOL("WEB",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_make_bridge_configuration_info = 
	    STATIC_SYMBOL("MAKE-BRIDGE-CONFIGURATION-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_bridge_configuration_info,
	    STATIC_FUNCTION(g2int_make_bridge_configuration_info,NIL,FALSE,
	    0,0));
    list_constant = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_make_bridge_configuration_info);
    g2int_record_system_variable(Qg2int_the_bridge_configuration_info,
	    Qg2int_web,list_constant,Qnil,Qnil,Qnil,Qnil);
    Kunconnected = STATIC_SYMBOL("UNCONNECTED",Pkeyword);
    if (G2int_the_state_of_g2 == UNBOUND)
	G2int_the_state_of_g2 = Kunconnected;
    Qg2int_mimi_headers_from_server = 
	    STATIC_SYMBOL("MIMI-HEADERS-FROM-SERVER",AB_package);
    Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct = 
	    STATIC_SYMBOL("PROXY-FETCH-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_proxy_fetch_thread = STATIC_SYMBOL("PROXY-FETCH-THREAD",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct,
	    Qg2int_proxy_fetch_thread,Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_proxy_fetch_thread,
	    Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_proxy_fetch_thread == UNBOUND)
	G2int_the_type_description_of_proxy_fetch_thread = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8l83=vy1o83=vy83Cy8m8k1l83Cy0000001m1m8o83Cy1n8n83=9y0k3Gyk0k0");
    temp = G2int_the_type_description_of_proxy_fetch_thread;
    G2int_the_type_description_of_proxy_fetch_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_16));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_proxy_fetch_thread_g2_struct,
	    G2int_the_type_description_of_proxy_fetch_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_proxy_fetch_thread,
	    G2int_the_type_description_of_proxy_fetch_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_proxy_fetch_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PROXY-FETCH-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_proxy_fetch_threads,
	    G2int_chain_of_available_proxy_fetch_threads);
    g2int_record_system_variable(Qg2int_chain_of_available_proxy_fetch_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_proxy_fetch_thread_count = 
	    STATIC_SYMBOL("PROXY-FETCH-THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_proxy_fetch_thread_count,
	    G2int_proxy_fetch_thread_count);
    g2int_record_system_variable(Qg2int_proxy_fetch_thread_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_proxy_fetch_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_proxy_fetch_thread,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_proxy_fetch_thread,
	    reclaim_structure_for_proxy_fetch_thread);
    Kdo_fetch = STATIC_SYMBOL("DO-FETCH",Pkeyword);
    Kwrapup = STATIC_SYMBOL("WRAPUP",Pkeyword);
    Qg2int_handle_incomming_data_for_proxy_fetch_thread = 
	    STATIC_SYMBOL("HANDLE-INCOMMING-DATA-FOR-PROXY-FETCH-THREAD",
	    AB_package);
    Qg2int_notify_no_op = STATIC_SYMBOL("NOTIFY-NO-OP",AB_package);
    Qg2int_mt_main_for_proxy_fetch_thread = 
	    STATIC_SYMBOL("MT-MAIN-FOR-PROXY-FETCH-THREAD",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_mt_main_for_proxy_fetch_thread,
	    STATIC_FUNCTION(g2int_mt_main_for_proxy_fetch_thread,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qg2int_handle_incomming_data_for_proxy_fetch_thread,
	    STATIC_FUNCTION(g2int_handle_incomming_data_for_proxy_fetch_thread,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qg2int_notify_no_op,
	    STATIC_FUNCTION(g2int_notify_no_op,NIL,FALSE,3,3));
}
