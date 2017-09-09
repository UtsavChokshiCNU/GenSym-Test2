/* wbgsi.c
 * Input file:  web-gsi.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "wbgsi.h"


Object G2int_count_of_gw_ping = UNBOUND;

static Object Qg2int_gsi_web;      /* gsi-web */

/* RETURN-FROM-ZGW-PING-1 */
Object g2int_return_from_zgw_ping_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,0);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object Qg2int_rpc_signal;   /* rpc-signal */

static Object Qg2int_ok;           /* ok */

static Object string_constant;     /* "" */

/* SHARED-ZGW-PING */
void g2int_shared_zgw_ping(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, count_of_gw_ping_new_value, signal_name;
    Object signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,1);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  count_of_gw_ping_new_value = add1(G2int_count_of_gw_ping);
	  G2int_count_of_gw_ping = count_of_gw_ping_new_value;
	  g2int_return_from_zgw_ping_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_ping_1(signal_name,signal_description);
    POP_SPECIAL();
}

static Object string_constant_1;   /* "zgw_ping" */

static Object Qg2int_gsi_catch;    /* gsi-catch */

/* ZGW-PING */
DLLEXPORT void zgw_ping(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,2);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_1);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_ping(c_argument_vector,count_1,call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_ping(c_argument_vector,count_1,
			    call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_1);
}

Object G2int_shutdown_requested = UNBOUND;

/* RETURN-FROM-ZGW-KILL-BRIDGE-1 */
Object g2int_return_from_zgw_kill_bridge_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,3);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object string_constant_2;   /* "G2 Killed Me." */

static Object Kshutdown;           /* :shutdown */

/* SHARED-ZGW-KILL-BRIDGE */
void g2int_shared_zgw_kill_bridge(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,4);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  g2int_notify_user_at_console(1,string_constant_2);
	  g2int_return_from_zgw_kill_bridge_1(Qg2int_ok,string_constant);
	  G2int_shutdown_requested = Kshutdown;
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_kill_bridge_1(signal_name,signal_description);
    POP_SPECIAL();
}

static Object string_constant_3;   /* "zgw_kill_bridge" */

/* ZGW-KILL-BRIDGE */
DLLEXPORT void zgw_kill_bridge(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,5);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_3);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_kill_bridge(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_kill_bridge(c_argument_vector,count_1,
			    call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_3);
}

Object G2int_count_of_gw_configure_bridge = UNBOUND;

/* RETURN-FROM-ZGW-CONFIGURE-BRIDGE-1 */
Object g2int_return_from_zgw_configure_bridge_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,6);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object string_constant_4;   /* "Configure-bridge" */

static Object Qg2int_maximum_count_of_simultaneous_transactions;  /* maximum-count-of-simultaneous-transactions */

static Object Qg2int_message_pool_size;  /* message-pool-size */

/* SHARED-ZGW-CONFIGURE-BRIDGE */
void g2int_shared_zgw_configure_bridge(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector;
    Object bridge_configuration_item, temp, svref_new_value, signal_name;
    Object signal_description;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(60,7);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      bridge_configuration_item = ISVREF(argument_vector,(SI_Long)0L + 
	      (SI_Long)1L);
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  g2int_notify_user_at_console(1,string_constant_4);
	  temp = add1(G2int_count_of_gw_configure_bridge);
	  G2int_count_of_gw_configure_bridge = temp;
	  if (PUSH_AREA(Dynamic_area,0)) {
	      temp = G2int_the_bridge_configuration_info;
	      SVREF(temp,FIX((SI_Long)1L)) = T;
	      temp = G2int_the_bridge_configuration_info;
	      svref_new_value = 
		      g2int_lgsi_get_attribute_value(bridge_configuration_item,
		      Qg2int_maximum_count_of_simultaneous_transactions);
	      SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
	      temp = G2int_the_bridge_configuration_info;
	      svref_new_value = 
		      g2int_lgsi_get_attribute_value(bridge_configuration_item,
		      Qg2int_message_pool_size);
	      SVREF(temp,FIX((SI_Long)7L)) = svref_new_value;
	  }
	  POP_AREA(0);
	  g2int_return_from_zgw_configure_bridge_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_configure_bridge_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_5;   /* "zgw_configure_bridge" */

/* ZGW-CONFIGURE-BRIDGE */
DLLEXPORT void zgw_configure_bridge(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,8);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_5);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_configure_bridge(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_configure_bridge(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_5);
}

Object G2int_count_of_url_requests_upon_g2 = UNBOUND;

static Object string_constant_6;   /* "Ask G2: ~S" */

/* REQUEST-URL-FROM-G2 */
Object g2int_request_url_from_g2(number_of_request,details_of_request)
    Object number_of_request, details_of_request;
{
    Object count_of_url_requests_upon_g2_new_value;

    x_note_fn_call(60,9);
    count_of_url_requests_upon_g2_new_value = 
	    add1(G2int_count_of_url_requests_upon_g2);
    G2int_count_of_url_requests_upon_g2 = 
	    count_of_url_requests_upon_g2_new_value;
    g2int_notify_user_at_console(2,string_constant_6,details_of_request);
    return g2int_request_url_from_g2_1(number_of_request,details_of_request);
}

/* REQUEST-URL-FROM-G2-1 */
Object g2int_request_url_from_g2_1(number_of_request,details_of_request)
    Object number_of_request, details_of_request;
{
    Object c_vector_of_items, magic_number, arguments;

    x_note_fn_call(60,10);
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    arguments = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(arguments,(SI_Long)0L + 
	    (SI_Long)1L),number_of_request);
    g2int_set_simple_value_in_item(ISVREF(arguments,(SI_Long)1L + 
	    (SI_Long)1L),details_of_request);
    return VALUES_1(VOID_TO_NULL(rpc_start_for_gw_request_for_url(inline_extract_c_array(arguments,
	    G2int_gsi_magic_offset))));
}

/* RETURN-FROM-ZGW-DECLINE-TO-SERVE-URL-1 */
Object g2int_return_from_zgw_decline_to_serve_url_1(signal_name,
	    signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,11);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object string_constant_7;   /* "404 Not Found" */

/* SHARED-ZGW-DECLINE-TO-SERVE-URL */
void g2int_shared_zgw_decline_to_serve_url(c_argument_vector,count_1,
	    call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector;
    Object number_of_request, apology, thread_of_request, encoded_string;
    Object signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,12);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      number_of_request = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      apology = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  thread_of_request = g2int_validate_fetch_id(number_of_request);
	  g2int_emit_headers_of_response(thread_of_request,string_constant_7);
	  encoded_string = g2int_encode_weblink_html_text(apology,
		  thread_of_request);
	  g2int_enqueue_text_into_reply(thread_of_request,encoded_string);
	  g2int_reclaim_gensym_string(encoded_string);
	  g2int_enqueue_finish_into_reply(thread_of_request);
	  g2int_return_from_zgw_decline_to_serve_url_1(Qg2int_ok,
		  string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_decline_to_serve_url_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_8;   /* "zgw_decline_to_serve_url" */

/* ZGW-DECLINE-TO-SERVE-URL */
DLLEXPORT void zgw_decline_to_serve_url(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,13);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_8);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_decline_to_serve_url(c_argument_vector,
		    count_1,call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_decline_to_serve_url(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_8);
}

/* RETURN-FROM-ZGW-SET-HEADER-FIELD-1 */
Object g2int_return_from_zgw_set_header_field_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,14);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object Qg2int_invalid_header;  /* invalid-header */

static Object string_constant_9;   /* "Can't set header fields after URL data sending has begun." */

/* SHARED-ZGW-SET-HEADER-FIELD */
void g2int_shared_zgw_set_header_field(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector, message_id;
    Object header, data, thread_of_request, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,15);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      message_id = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      header = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      data = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)2L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  thread_of_request = g2int_validate_fetch_id(message_id);
	  if (ISVREF(thread_of_request,(SI_Long)21L))
	      g2int_signal_from_rpc(Qg2int_invalid_header,string_constant_9);
	  g2int_add_message_header_field(thread_of_request,header,data);
	  g2int_return_from_zgw_set_header_field_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_set_header_field_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_10;  /* "zgw_set_header_field" */

/* ZGW-SET-HEADER-FIELD */
DLLEXPORT void zgw_set_header_field(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,16);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_10);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_set_header_field(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_set_header_field(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_10);
}

/* RETURN-FROM-ZGW-SET-URL-REPLY-CHARSET-1 */
Object g2int_return_from_zgw_set_url_reply_charset_1(signal_name,
	    signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,17);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object string_constant_11;  /* "Can't set header fields (URL reply charset) after URL data sending has begun." */

/* SHARED-ZGW-SET-URL-REPLY-CHARSET */
void g2int_shared_zgw_set_url_reply_charset(c_argument_vector,count_1,
	    call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector, message_id;
    Object charset_name, thread_of_request, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,18);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      message_id = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      charset_name = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  thread_of_request = g2int_validate_fetch_id(message_id);
	  if (ISVREF(thread_of_request,(SI_Long)21L))
	      g2int_signal_from_rpc(Qg2int_invalid_header,string_constant_11);
	  if (g2int_map_and_validate_charset_name(charset_name))
	      SVREF(thread_of_request,FIX((SI_Long)23L)) = charset_name;
	  g2int_return_from_zgw_set_url_reply_charset_1(Qg2int_ok,
		  string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_set_url_reply_charset_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_12;  /* "zgw_set_url_reply_charset" */

/* ZGW-SET-URL-REPLY-CHARSET */
DLLEXPORT void zgw_set_url_reply_charset(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,19);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_12);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_set_url_reply_charset(c_argument_vector,
		    count_1,call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_set_url_reply_charset(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_12);
}

/* RETURN-FROM-ZGW-ADD-TO-URL-REPLY-1 */
Object g2int_return_from_zgw_add_to_url_reply_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,20);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

/* SHARED-ZGW-ADD-TO-URL-REPLY */
void g2int_shared_zgw_add_to_url_reply(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector;
    Object number_of_request, more_data, thread_of_request, encoded_string;
    Object signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,21);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      number_of_request = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      more_data = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  thread_of_request = g2int_validate_fetch_id(number_of_request);
	  encoded_string = g2int_encode_weblink_html_text(more_data,
		  thread_of_request);
	  g2int_enqueue_text_into_reply(thread_of_request,encoded_string);
	  g2int_reclaim_gensym_string(encoded_string);
	  g2int_return_from_zgw_add_to_url_reply_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_add_to_url_reply_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_13;  /* "zgw_add_to_url_reply" */

/* ZGW-ADD-TO-URL-REPLY */
DLLEXPORT void zgw_add_to_url_reply(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,22);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_13);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_add_to_url_reply(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_add_to_url_reply(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_13);
}

/* RETURN-FROM-ZGW-FINISH-URL-REPLY-1 */
Object g2int_return_from_zgw_finish_url_reply_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,23);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

/* SHARED-ZGW-FINISH-URL-REPLY */
void g2int_shared_zgw_finish_url_reply(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector;
    Object number_of_request, thread_of_request, signal_name;
    Object signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,24);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      number_of_request = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  thread_of_request = g2int_validate_fetch_id(number_of_request);
	  g2int_enqueue_finish_into_reply(thread_of_request);
	  g2int_return_from_zgw_finish_url_reply_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_finish_url_reply_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_14;  /* "zgw_finish_url_reply" */

/* ZGW-FINISH-URL-REPLY */
DLLEXPORT void zgw_finish_url_reply(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,25);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_14);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_finish_url_reply(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_finish_url_reply(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_14);
}

/* RETURN-FROM-ZGW-GET-ATTRIBUTE-OF-REQUEST-1 */
Object g2int_return_from_zgw_get_attribute_of_request_1(signal_name,
	    signal_description,result_1)
    Object signal_name, signal_description, result_1;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,26);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)3L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)2L + 
	    (SI_Long)1L),result_1);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)3L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

/* SHARED-ZGW-GET-ATTRIBUTE-OF-REQUEST */
void g2int_shared_zgw_get_attribute_of_request(c_argument_vector,count_1,
	    call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector;
    Object number_of_request, argument_name, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,27);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      number_of_request = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      argument_name = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  g2int_return_from_zgw_get_attribute_of_request_1(Qg2int_ok,
		  string_constant,
		  g2int_built_in_argument_of_fetch_id(number_of_request,
		  argument_name));
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_get_attribute_of_request_1(signal_name,
		  signal_description,string_constant);
    POP_SPECIAL();
}

static Object string_constant_15;  /* "zgw_get_attribute_of_request" */

/* ZGW-GET-ATTRIBUTE-OF-REQUEST */
DLLEXPORT void zgw_get_attribute_of_request(c_argument_vector,count_1,
	    call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,28);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_15);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_get_attribute_of_request(c_argument_vector,
		    count_1,call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_get_attribute_of_request(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_15);
}

Object G2int_count_of_gw_install_fetch_style = UNBOUND;

static Object string_constant_16;  /* "HTTP/" */

static Object string_constant_17;  /* "." */

static Object Qg2int_error_message_from_server;  /* error-message-from-server */

static Object Qg2int_major_version_of_http;  /* major-version-of-http */

static Object Qg2int_minor_version_of_http;  /* minor-version-of-http */

static Object Qg2int_error_code_from_server;  /* error-code-from-server */

/* CONSUME-HEADER-IF-ANY */
Object g2int_consume_header_if_any(mark_to_leave_at_resource_start)
    Object mark_to_leave_at_resource_start;
{
    Object mark_of_resource_min, major_version, minor_version, error_code;
    Object mark, current_left_of_parsing, current_right_of_parsing;
    char temp;
    Declare_special(2);

    x_note_fn_call(60,29);
    mark_of_resource_min = mark_to_leave_at_resource_start;
    major_version = FIX((SI_Long)0L);
    minor_version = FIX((SI_Long)9L);
    error_code = FIX((SI_Long)200L);
    mark = mark_of_resource_min;
    current_left_of_parsing = g2int_mark_copy(mark);
    PUSH_SPECIAL(G2int_current_left_of_parsing,current_left_of_parsing,1);
      current_right_of_parsing = g2int_mark_copy(mark);
      PUSH_SPECIAL(G2int_current_right_of_parsing,current_right_of_parsing,0);
	if (g2int_scan_text(string_constant_16)) {
	    major_version = g2int_scan_integer();
	    temp = TRUEP(major_version);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(g2int_scan_text(string_constant_17)) : TRUEP(Nil)) {
	    minor_version = g2int_scan_integer();
	    temp = TRUEP(minor_version);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? TRUEP(g2int_scan_one_or_more_spaces_and_tabs()) : 
		TRUEP(Nil)) {
	    error_code = g2int_scan_integer();
	    temp = TRUEP(error_code);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    g2int_scan_to_end_of_line();
	    if ( !TRUEP(error_code))
		error_code = FIX((SI_Long)10099L);
	    if ( !(IFIX(error_code) == (SI_Long)200L))
		g2int_set_property_of_buffer(mark_of_resource_min,
			Qg2int_error_message_from_server,
			g2int_get_simple_text_from_last_scan());
	    g2int_scan_to_beginning_of_next_line();
	    if ((SI_Long)1L <= IFIX(major_version)) {
	      next_loop:
		if ( !TRUEP(g2int_scan_header_line(mark)))
		    goto end_loop;
		goto next_loop;
	      end_loop:
		g2int_scan_to_beginning_of_next_line();
	    }
	    g2int_mark_set(mark_of_resource_min,
		    G2int_current_right_of_parsing);
	}
	g2int_mark_kill(G2int_current_left_of_parsing);
	g2int_mark_kill(G2int_current_right_of_parsing);
      POP_SPECIAL();
    POP_SPECIAL();
    g2int_set_property_of_buffer(mark_of_resource_min,
	    Qg2int_major_version_of_http,major_version);
    g2int_set_property_of_buffer(mark_of_resource_min,
	    Qg2int_minor_version_of_http,minor_version);
    return g2int_set_property_of_buffer(mark_of_resource_min,
	    Qg2int_error_code_from_server,error_code);
}

Object G2int_cache_name_counter = UNBOUND;

/* INIT-CACHE-NAME-COUNTER */
Object g2int_init_cache_name_counter()
{
    Object second_1, minute, hour, day, month, year;
    Object result;

    x_note_fn_call(60,30);
    result = g2int_get_decoded_real_time();
    MVS_6(result,second_1,minute,hour,day,month,year);
    G2int_cache_name_counter = FIX((IFIX(year) - (SI_Long)1900L << 
	    (SI_Long)20L) + (IFIX(month) << (SI_Long)16L) + (IFIX(day) << 
	    (SI_Long)12L) + (IFIX(hour) << (SI_Long)8L) + (IFIX(minute) << 
	    (SI_Long)4L) + IFIX(second_1));
    return VALUES_1(G2int_cache_name_counter);
}

static Object Qg2int_wide_string;  /* wide-string */

/* TWRITE-CACHE-NUMBER */
Object g2int_twrite_cache_number(positive_fixnum_init,radix_init)
    Object positive_fixnum_init, radix_init;
{
    Object simple_or_wide_character, thing, temp_1, schar_arg_2;
    Object schar_new_value;
    SI_Long positive_fixnum, radix, temp, quotient, remainder_1;

    x_note_fn_call(60,31);
    positive_fixnum = IFIX(positive_fixnum_init);
    radix = IFIX(radix_init);
    if (positive_fixnum >= radix) {
	temp = positive_fixnum / radix;
	quotient = temp;
	temp = positive_fixnum % radix;
	remainder_1 = temp;
	g2int_twrite_cache_number(FIX(quotient),FIX(radix));
	simple_or_wide_character = digit_char(FIX(remainder_1),FIX(radix),_);
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    else {
	simple_or_wide_character = digit_char(FIX(positive_fixnum),
		FIX(radix),_);
	if (EQ(G2int_current_twriting_output_type,Qg2int_wide_string)) {
	    thing = simple_or_wide_character;
	    g2int_twrite_wide_character(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	}
	else {
	    if ( !FIXNUM_LT(G2int_fill_pointer_for_current_gensym_string,
		    G2int_total_length_of_current_gensym_string))
		g2int_extend_current_gensym_string(0);
	    temp_1 = G2int_current_gensym_string;
	    schar_arg_2 = G2int_fill_pointer_for_current_gensym_string;
	    thing = simple_or_wide_character;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
		    CHAR_CODE(thing) : thing);
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(G2int_fill_pointer_for_current_gensym_string);
	    G2int_fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    return VALUES_1(Nil);
}

static Object Qg2int_gensym_string;  /* gensym-string */

static Object array_constant;      /* # */

/* GENERATE-RESOURCE-CACHE-NAME */
Object g2int_generate_resource_cache_name()
{
    Object current_gensym_string, fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object cache_name_counter_new_value, name, pathname_1, temp;
    Declare_special(4);

    x_note_fn_call(60,32);
    if ( !TRUEP(G2int_cache_name_counter))
	g2int_init_cache_name_counter();
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
	    g2int_twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)2L));
	    cache_name_counter_new_value = 
		    FIXNUM_ADD1(G2int_cache_name_counter);
	    G2int_cache_name_counter = cache_name_counter_new_value;
	    g2int_twrite_cache_number(G2int_cache_name_counter,
		    FIX((SI_Long)32L));
	    name = g2int_copy_out_current_gensym_string();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    pathname_1 = g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
	    ISVREF(G2int_the_bridge_configuration_info,(SI_Long)5L),name,
	    Nil,Nil,Nil);
    temp = g2int_gensym_namestring(1,pathname_1);
    g2int_reclaim_gensym_string(name);
    g2int_reclaim_gensym_pathname(pathname_1);
    return VALUES_1(temp);
}

static Object string_constant_18;  /* "toc" */

/* CACHE-TOC-NAMESTRING */
Object g2int_cache_toc_namestring()
{
    Object pathname_1, temp;

    x_note_fn_call(60,33);
    pathname_1 = g2int_gensym_make_pathname_with_copied_components(Nil,Nil,
	    ISVREF(G2int_the_bridge_configuration_info,(SI_Long)5L),
	    string_constant_18,Nil,Nil,Nil);
    temp = g2int_gensym_namestring(1,pathname_1);
    g2int_reclaim_gensym_pathname(pathname_1);
    return VALUES_1(temp);
}

static Object Qg2int_unbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object Qg2int_begining_of_resource;  /* begining-of-resource */

/* WRITE-RESOURCE-TO-FILE */
Object g2int_write_resource_to_file(resource,file_ascii_namestring)
    Object resource, file_ascii_namestring;
{
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object stream;
    Object start_of_resource, end_of_buffer, start_mark, end_mark;
    Object last_fragment, fragment, last_fragment_qm, text_string, start, end;
    Object text, temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(60,34);
    SAVE_STACK();
    if (g2int_g2_stream_probe_file_for_exist(file_ascii_namestring))
	g2int_g2_stream_delete_file(file_ascii_namestring);
    pathname_used_p = Qg2int_unbound_in_protected_let;
    namestring_1 = Qg2int_unbound_in_protected_let;
    stream = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_used_p = SIMPLE_VECTOR_P(file_ascii_namestring) ? 
		(EQ(ISVREF(file_ascii_namestring,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		T : Nil) : Qnil;
	namestring_1 = SIMPLE_VECTOR_P(file_ascii_namestring) && 
		EQ(ISVREF(file_ascii_namestring,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		g2int_gensym_namestring(1,file_ascii_namestring) : 
		file_ascii_namestring;
	stream = g2int_g2_stream_open_for_output(namestring_1);
	if (stream) {
	    start_of_resource = 
		    g2int_mark_copy(g2int_get_property_of_buffer(resource,
		    Qg2int_begining_of_resource));
	    end_of_buffer = g2int_mark_copy(start_of_resource);
	    g2int_mark_move_to_end(end_of_buffer);
	    start_mark = start_of_resource;
	    end_mark = end_of_buffer;
	    last_fragment = ISVREF(end_mark,(SI_Long)3L);
	    fragment = ISVREF(start_mark,(SI_Long)3L);
	    last_fragment_qm = Nil;
	    text_string = Nil;
	    start = ISVREF(start_mark,(SI_Long)4L);
	    end = Nil;
	    last_fragment_qm = EQ(last_fragment,fragment) ? T : Nil;
	    text_string = ISVREF(fragment,(SI_Long)2L);
	  next_loop:
	    end = last_fragment_qm ? ISVREF(end_mark,(SI_Long)4L) : 
		    ISVREF(fragment,(SI_Long)4L);
	    if ((SI_Long)0L == IFIX(start))
		g2int_g2_stream_write_from_buffer(text_string,end,stream);
	    else {
		text = g2int_gensym_string_substring(text_string,start,end);
		g2int_g2_stream_write_from_buffer(text,FIXNUM_MINUS(end,
			start),stream);
		g2int_reclaim_gensym_string(text);
	    }
	    if (last_fragment_qm) {
		temp = Nil;
		goto end_1;
	    }
	    fragment = ISVREF(fragment,(SI_Long)1L);
	    last_fragment_qm = EQ(last_fragment,fragment) ? T : Nil;
	    text_string = ISVREF(fragment,(SI_Long)2L);
	    start = FIX((SI_Long)0L);
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	    g2int_mark_kill(end_of_buffer);
	    SAVE_VALUES(VALUES_1(temp));
	    g2int_mark_kill(start_of_resource);
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(0);
    if (stream) {
	if ( !EQ(stream,Qg2int_unbound_in_protected_let))
	    g2int_g2_stream_close(stream);
    }
    if (namestring_1) {
	if ( !EQ(namestring_1,Qg2int_unbound_in_protected_let)) {
	    if (pathname_used_p)
		g2int_reclaim_text_string(namestring_1);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* READ-RESOURCE-FROM-FILE */
Object g2int_read_resource_from_file(resource,namestring_1)
    Object resource, namestring_1;
{
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Object insert_mark, count_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(60,35);
    SAVE_STACK();
    if ( !TRUEP(g2int_g2_stream_probe_file_for_exist(namestring_1))) {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
    else {
	pathname_used_p = Qg2int_unbound_in_protected_let;
	namestring_2 = Qg2int_unbound_in_protected_let;
	stream = Qg2int_unbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(0)) {
	    pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
		    (EQ(ISVREF(namestring_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		    ? T : Nil) : Qnil;
	    namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
		    EQ(ISVREF(namestring_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		    ? g2int_gensym_namestring(1,namestring_1) : namestring_1;
	    stream = g2int_g2_stream_open_for_input(namestring_2);
	    insert_mark = g2int_mark_copy(resource);
	    count_qm = Nil;
	  next_loop:
	    count_qm = 
		    g2int_g2_stream_read_into_buffer(G2int_current_foreign_string_pad,
		    G2int_max_of_foreign_string_pad,stream);
	    if ( !TRUEP(count_qm))
		error((SI_Long)1L,"Error reading resource cache.");
	    else if (IFIX(count_qm) == (SI_Long)0L)
		goto end;
	    else
		g2int_insert_subtext_at_mark(insert_mark,
			G2int_current_foreign_string_pad,FIX((SI_Long)0L),
			count_qm);
	    goto next_loop;
	  end_loop:
	  end:;
	    g2int_mark_kill(insert_mark);
	}
	POP_UNWIND_PROTECT(0);
	if (stream) {
	    if ( !EQ(stream,Qg2int_unbound_in_protected_let))
		g2int_g2_stream_close(stream);
	}
	if (namestring_2) {
	    if ( !EQ(namestring_2,Qg2int_unbound_in_protected_let)) {
		if (pathname_used_p)
		    g2int_reclaim_text_string(namestring_2);
	    }
	}
	CONTINUE_UNWINDING(0);
	RESTORE_STACK();
	return VALUES_1(resource);
    }
}

Object G2int_items_in_resource_cache = UNBOUND;

static Object Qg2int_cache_filename;  /* cache-filename */

static Object Qg2int_url;          /* url */

static Object Qg2int_mimi_headers_from_server;  /* mimi-headers-from-server */

/* ENTER-RESOURCE-INTO-CACHE */
Object g2int_enter_resource_into_cache(resource)
    Object resource;
{
    Object mark, resource_buffer, buffer_plist, url, cache_filename;
    Object mimi_headers_from_server, key, value, ab_loop_list_, temp;
    Object gensymed_symbol, gensymed_symbol_1, plist;

    x_note_fn_call(60,36);
    if ( !TRUEP(g2int_get_property_of_buffer(resource,
		Qg2int_cache_filename))) {
	g2int_set_property_of_buffer(resource,Qg2int_cache_filename,
		g2int_generate_resource_cache_name());
	g2int_write_resource_to_file(resource,
		g2int_get_property_of_buffer(resource,Qg2int_cache_filename));
	mark = resource;
	resource_buffer = ISVREF(mark,(SI_Long)1L);
	buffer_plist = ISVREF(resource_buffer,(SI_Long)3L);
	url = Nil;
	cache_filename = Nil;
	mimi_headers_from_server = Nil;
	key = Nil;
	value = Nil;
	ab_loop_list_ = buffer_plist;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	key = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	if (EQ(key,Qg2int_url))
	    url = g2int_copy_resource_plist_value(value);
	else if (EQ(key,Qg2int_cache_filename))
	    cache_filename = g2int_copy_resource_plist_value(value);
	else if (EQ(key,Qg2int_mimi_headers_from_server))
	    mimi_headers_from_server = g2int_copy_resource_plist_value(value);
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	g2int_remove_url_from_cache(url,Nil);
	gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)6L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qg2int_url;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = url;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qg2int_cache_filename;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = cache_filename;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qg2int_mimi_headers_from_server;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = mimi_headers_from_server;
	plist = gensymed_symbol;
	goto end;
	plist = Qnil;
      end:;
	G2int_items_in_resource_cache = g2int_gensym_cons_1(plist,
		G2int_items_in_resource_cache);
	return g2int_write_cache_toc(G2int_items_in_resource_cache);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-URL-FROM-CACHE */
Object g2int_remove_url_from_cache(url,write_cache_toc_qm)
    Object url, write_cache_toc_qm;
{
    Object entries_to_remove, cache_entry, ab_loop_list_, url_of_entry;
    Object filename, entry;

    x_note_fn_call(60,37);
    entries_to_remove = Nil;
    cache_entry = Nil;
    ab_loop_list_ = G2int_items_in_resource_cache;
    url_of_entry = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cache_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    url_of_entry = getf(cache_entry,Qg2int_url,_);
    if (string_eq(2,url,url_of_entry)) {
	filename = getf(cache_entry,Qg2int_cache_filename,_);
	g2int_gensym_delete_file(filename);
	entries_to_remove = g2int_gensym_cons_1(cache_entry,entries_to_remove);
    }
    goto next_loop;
  end_loop:
    if (entries_to_remove) {
	entry = Nil;
	ab_loop_list_ = entries_to_remove;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	G2int_items_in_resource_cache = 
		g2int_delete_gensym_element_1(entry,
		G2int_items_in_resource_cache);
	goto next_loop_1;
      end_loop_1:;
	g2int_reclaim_gensym_list_1(entries_to_remove);
	if (write_cache_toc_qm)
	    g2int_write_cache_toc(G2int_items_in_resource_cache);
    }
    return VALUES_1(Qnil);
}

/* RELOAD-FROM-CACHE-INFO */
Object g2int_reload_from_cache_info(cache_info)
    Object cache_info;
{
    Object resource, read_ok_qm, svref_arg_1, key, value, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(60,38);
    resource = g2int_make_mark_into_new_empty_resource_buffer();
    read_ok_qm = g2int_read_resource_from_file(resource,getf(cache_info,
	    Qg2int_cache_filename,_));
    if ( !TRUEP(read_ok_qm)) {
	g2int_reclaim_resource_buffer_of_mark(resource);
	return VALUES_1(Nil);
    }
    else {
	svref_arg_1 = ISVREF(resource,(SI_Long)1L);
	key = Nil;
	value = Nil;
	ab_loop_list_ = cache_info;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	key = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value = CAR(temp);
	temp = key;
	ab_loopvar__2 = g2int_gensym_list_2(temp,
		g2int_copy_resource_plist_value(value));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	goto end;
	ab_loopvar_ = Qnil;
      end:;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = ab_loopvar_;
	g2int_set_property_of_buffer(resource,Qg2int_begining_of_resource,
		g2int_make_mark_at_start(resource));
	return VALUES_1(resource);
    }
}

/* IS-URL-IN-CACHE? */
Object g2int_is_url_in_cacheqm(url)
    Object url;
{
    Object cache_info, ab_loop_list_, cache_url;

    x_note_fn_call(60,39);
    cache_info = Nil;
    ab_loop_list_ = G2int_items_in_resource_cache;
    cache_url = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cache_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    cache_url = getf(cache_info,Qg2int_url,_);
    if (string_eq(2,cache_url,url))
	return VALUES_1(cache_info);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RELEASE-FROM-CACHE */
Object g2int_release_from_cache(cache_info)
    Object cache_info;
{
    Object filename;

    x_note_fn_call(60,40);
    filename = getf(cache_info,Qg2int_cache_filename,_);
    if (g2int_g2_stream_probe_file_for_exist(filename))
	g2int_g2_stream_delete_file(filename);
    G2int_items_in_resource_cache = 
	    g2int_delete_gensym_element_1(cache_info,
	    G2int_items_in_resource_cache);
    return g2int_reclaim_plist_of_resource_buffer(cache_info);
}

static Object string_constant_19;  /* "Writing table of contents for cache (~D entries)" */

static Object string_constant_20;  /* "Cache directory (~S) doesn't exist or isn't writable." */

static Object string_constant_21;  /* "gm-toc-1.0" */

static Object string_constant_22;  /* ";;; Machine Generated -- Do Not Modify" */

/* WRITE-CACHE-TOC */
Object g2int_write_cache_toc(entries)
    Object entries;
{
    Object namestring_1;
    volatile Object ok_qm;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(60,41);
    SAVE_STACK();
    g2int_notify_user_at_console(2,string_constant_19,length(entries));
    namestring_1 = g2int_cache_toc_namestring();
    ok_qm = T;
    if (g2int_g2_stream_probe_file_for_exist(namestring_1))
	g2int_g2_stream_delete_file(namestring_1);
    pathname_used_p = Qg2int_unbound_in_protected_let;
    namestring_2 = Qg2int_unbound_in_protected_let;
    stream = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
		(EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		T : Nil) : Qnil;
	namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
		EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		g2int_gensym_namestring(1,namestring_1) : namestring_1;
	stream = g2int_g2_stream_open_for_output(namestring_2);
	if ( !TRUEP(stream)) {
	    g2int_notify_user_at_console(2,string_constant_20,
		    g2int_gensym_namestring(1,namestring_1));
	    ok_qm = Nil;
	}
	else {
	    g2int_g2_stream_write_line(string_constant_21,stream);
	    g2int_g2_stream_write_line(string_constant_22,stream);
	    g2int_write_cache_toc_1(entries,stream);
	}
    }
    POP_UNWIND_PROTECT(0);
    if (stream) {
	if ( !EQ(stream,Qg2int_unbound_in_protected_let))
	    g2int_g2_stream_close(stream);
    }
    if (namestring_2) {
	if ( !EQ(namestring_2,Qg2int_unbound_in_protected_let)) {
	    if (pathname_used_p)
		g2int_reclaim_text_string(namestring_2);
	}
    }
    CONTINUE_UNWINDING(0);
    g2int_reclaim_gensym_string(namestring_1);
    RESTORE_STACK();
    return VALUES_1(ok_qm);
}

static Object string_constant_23;  /* "S~D|~S" */

static Object string_constant_24;  /* "T~D|~A" */

static Object string_constant_25;  /* "C" */

static Object string_constant_26;  /* "L~D|" */

/* WRITE-CACHE-TOC-1 */
Object g2int_write_cache_toc_1(data,stream)
    Object data, stream;
{
    Object result_string, temp, length_1, tail;
    char temp_1;

    x_note_fn_call(60,42);
    if ( !TRUEP(data))
	return g2int_g2_stream_write_char(CHR('N'),stream);
    else if (SYMBOLP(data)) {
	result_string = g2int_tformat_text_string(3,string_constant_23,
		length(SYMBOL_NAME(data)),data);
	g2int_g2_stream_write_string(result_string,stream);
	return g2int_reclaim_text_string(result_string);
    }
    else if (STRINGP(data)) {
	result_string = g2int_tformat_text_string(3,string_constant_24,
		length(data),data);
	g2int_g2_stream_write_string(result_string,stream);
	return g2int_reclaim_text_string(result_string);
    }
    else {
	if (CONSP(data)) {
	    temp = CDR(data);
	    temp_1 =  !LISTP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    result_string = g2int_tformat_text_string(3,string_constant_25,
		    length(data),data);
	    g2int_g2_stream_write_string(result_string,stream);
	    g2int_reclaim_text_string(result_string);
	    g2int_write_cache_toc_1(CAR(data),stream);
	    return g2int_write_cache_toc_1(CDR(data),stream);
	}
	else if (LISTP(data)) {
	    length_1 = length(data);
	    tail = data;
	    result_string = g2int_tformat_text_string(2,string_constant_26,
		    length_1);
	    g2int_g2_stream_write_string(result_string,stream);
	    g2int_reclaim_text_string(result_string);
	    g2int_g2_stream_terpri(stream);
	  next_loop:
	    if ( !TRUEP(tail))
		goto end_loop;
	    g2int_write_cache_toc_1(CAR(tail),stream);
	    g2int_g2_stream_terpri(stream);
	    temp = CDR(tail);
	    if ( !LISTP(temp)) {
		g2int_g2_stream_write_char(CHR('X'),stream);
		g2int_write_cache_toc_1(CDR(tail),stream);
	    }
	    tail = M_CDR(tail);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
}

static Object string_constant_27;  /* "Read table of contents for cache (~D entries)" */

/* READ-CACHE-TOC */
Object g2int_read_cache_toc()
{
    Object namestring_1;
    volatile Object ok_qm;
    volatile Object no_log_qm;
    volatile Object pathname_used_p;
    volatile Object namestring_2;
    volatile Object stream;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(60,43);
    SAVE_STACK();
    namestring_1 = g2int_cache_toc_namestring();
    ok_qm = T;
    no_log_qm = Nil;
    pathname_used_p = Qg2int_unbound_in_protected_let;
    namestring_2 = Qg2int_unbound_in_protected_let;
    stream = Qg2int_unbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_used_p = SIMPLE_VECTOR_P(namestring_1) ? 
		(EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		T : Nil) : Qnil;
	namestring_2 = SIMPLE_VECTOR_P(namestring_1) && 
		EQ(ISVREF(namestring_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
		g2int_gensym_namestring(1,namestring_1) : namestring_1;
	stream = g2int_g2_stream_open_for_input(namestring_2);
	if ( !(stream && string_eq(2,g2int_g2_stream_read_line(stream),
		string_constant_21))) {
	    no_log_qm = T;
	    ok_qm = g2int_write_cache_toc(Nil);
	    temp = Nil;
	}
	else
	    temp = g2int_read_cache_toc_1(stream);
	SAVE_VALUES(VALUES_1(temp));
    }
    POP_UNWIND_PROTECT(0);
    if (stream) {
	if ( !EQ(stream,Qg2int_unbound_in_protected_let))
	    g2int_g2_stream_close(stream);
    }
    if (namestring_2) {
	if ( !EQ(namestring_2,Qg2int_unbound_in_protected_let)) {
	    if (pathname_used_p)
		g2int_reclaim_text_string(namestring_2);
	}
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    G2int_items_in_resource_cache = result;
    g2int_reclaim_gensym_string(namestring_1);
    if ( !TRUEP(no_log_qm))
	g2int_notify_user_at_console(2,string_constant_27,
		length(G2int_items_in_resource_cache));
    RESTORE_STACK();
    return VALUES_1(ok_qm);
}

static Object Qcdrcode_marker;     /* #:cdrcode-marker */

/* READ-CACHE-TOC-1 */
Object g2int_read_cache_toc_1(stream)
    Object stream;
{
    Object dispatch, length_1, result_1, tail, temp, last_element, temp_1;
    Object text;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(60,44);
  restart:
    dispatch = g2int_g2_stream_read_char(stream);
    if ( !CHARACTERP(dispatch))
	return VALUES_1(Nil);
    else
	switch (ICHAR_CODE(dispatch)) {
	  case ';':
	    g2int_reclaim_text_string(g2int_g2_stream_read_line(stream));
	    goto restart;
	  case '\r':
	  case '\n':
	  case ' ':
	    goto restart;
	  case 'X':
	    return VALUES_1(Qcdrcode_marker);
	  case 'L':
	    length_1 = g2int_read_cache_toc_count(stream);
	    result_1 = g2int_gensym_cons_1(g2int_read_cache_toc_1(stream),Nil);
	    tail = result_1;
	    i = (SI_Long)2L;
	    ab_loop_bind_ = IFIX(length_1);
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    temp = g2int_gensym_cons_1(g2int_read_cache_toc_1(stream),Nil);
	    tail = M_CDR(tail) = temp;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    if ((SI_Long)1L == IFIX(length_1))
		return VALUES_1(result_1);
	    last_element = g2int_read_cache_toc_1(stream);
	    temp = EQ(Qcdrcode_marker,last_element) ? last_element : 
		    g2int_gensym_cons_1(last_element,Nil);
	    M_CDR(tail) = temp;
	    return VALUES_1(result_1);
	    return VALUES_1(Qnil);
	  case 'C':
	    temp_1 = g2int_read_cache_toc_1(stream);
	    return g2int_gensym_cons_1(temp_1,g2int_read_cache_toc_1(stream));
	  case 'T':
	    length_1 = g2int_read_cache_toc_count(stream);
	    text = g2int_obtain_simple_gensym_string(length_1);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_1);
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    temp = g2int_g2_stream_read_char(stream);
	    SET_ICHAR(text,i,ICHAR_CODE(temp));
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    return VALUES_1(text);
	  case 'S':
	    length_1 = g2int_read_cache_toc_count(stream);
	    text = g2int_obtain_simple_gensym_string(length_1);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_1);
	  next_loop_2:
	    if (i >= ab_loop_bind_)
		goto end_loop_2;
	    temp = g2int_g2_stream_read_char(stream);
	    SET_ICHAR(text,i,ICHAR_CODE(temp));
	    i = i + (SI_Long)1L;
	    goto next_loop_2;
	  end_loop_2:;
	    return g2int_intern_gensym_string(1,text);
	  case 'N':
	    return VALUES_1(Nil);
	  default:
	    return VALUES_1(Nil);
	}
    return VALUES_1(Qnil);
}

/* READ-CACHE-TOC-COUNT */
Object g2int_read_cache_toc_count(stream)
    Object stream;
{
    Object result_1, c;

    x_note_fn_call(60,45);
    result_1 = FIX((SI_Long)0L);
    c = Nil;
  next_loop:
    c = g2int_g2_stream_read_char(stream);
    if (EQ(CHR('|'),c) ||  !TRUEP(c))
	goto end_loop;
    result_1 = FIX((SI_Long)10L * IFIX(result_1) + IFIX(digit_char_p(c,_)));
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* PREFLIGHT-CACHE-DIRECTORY */
Object g2int_preflight_cache_directory()
{
    x_note_fn_call(60,46);
    return g2int_read_cache_toc();
}

Object G2int_count_of_gw_fetch_url_contents = UNBOUND;

static Object Kadd_data;           /* :add-data */

static Object Kend_data;           /* :end-data */

static Object Qg2int_end_of_transmission_recieved;  /* end-of-transmission-recieved */

/* FILTER-DATA-FOR-GET-LINE-FROM-URL */
Object g2int_filter_data_for_get_line_from_url(status,string_qm)
    Object status, string_qm;
{
    Object incomming_mark, c;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(60,47);
    incomming_mark = ISVREF(G2int_current_thread,(SI_Long)22L);
    if (EQ(status,Kadd_data)) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(string_qm));
	c = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	c = CHR(ICHAR(string_qm,i));
	g2int_insert_character_at_mark(incomming_mark,c);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	return g2int_reclaim_gensym_string(string_qm);
    }
    else if (EQ(status,Kend_data))
	return g2int_set_property_of_buffer(incomming_mark,
		Qg2int_end_of_transmission_recieved,T);
    else
	return VALUES_1(Qnil);
}

/* POSTPROCESS-RESULT-FRAGMENTS */
Object g2int_postprocess_result_fragments(mark)
    Object mark;
{
    Object fetch_style_info, temp, mark_of_resource_min, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object min_mark, max_mark, ascii_string, dumb_gensym_string;
    Declare_special(4);
    Object result;

    x_note_fn_call(60,48);
    fetch_style_info = ISVREF(G2int_current_thread,(SI_Long)20L);
    temp = g2int_mark_copy(mark);
    mark_of_resource_min = g2int_set_property_of_buffer(mark,
	    Qg2int_begining_of_resource,g2int_mark_tab(temp,
	    g2int_point_min(mark)));
    g2int_consume_header_if_any(mark_of_resource_min);
    g2int_enter_resource_into_cache(mark);
    if (ISVREF(fetch_style_info,(SI_Long)6L)) {
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
		g2int_twrite_gensym_characters_from_ascii_string(1,
			g2int_get_property_of_buffer(mark,
			Qg2int_cache_filename));
		result = g2int_copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else {
	min_mark = g2int_mark_copy(mark_of_resource_min);
	max_mark = g2int_mark_copy(mark_of_resource_min);
	if (ISVREF(fetch_style_info,(SI_Long)4L)) {
	    g2int_mark_tab(min_mark,g2int_point_min(min_mark));
	    g2int_mark_move(max_mark,FIX((SI_Long)-2L));
	}
	if (ISVREF(fetch_style_info,(SI_Long)5L))
	    g2int_mark_tab(max_mark,g2int_point_max(max_mark));
	ascii_string = g2int_copy_text_between_marks(min_mark,max_mark);
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
		g2int_twrite_gensym_characters_from_ascii_string(1,
			ascii_string);
		dumb_gensym_string = g2int_copy_out_current_gensym_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = g2int_coerce_to_simple_gensym_string(dumb_gensym_string);
	g2int_reclaim_gensym_string(ascii_string);
	g2int_reclaim_gensym_string(dumb_gensym_string);
	g2int_mark_kill(max_mark);
	g2int_mark_kill(min_mark);
	return VALUES_1(temp);
    }
}

/* COERCE-TO-SIMPLE-GENSYM-STRING */
Object g2int_coerce_to_simple_gensym_string(text_string)
    Object text_string;
{
    Object length_1, result_1;
    SI_Long i, ab_loop_bind_;
    char char_new_value;

    x_note_fn_call(60,49);
    length_1 = length(text_string);
    result_1 = g2int_obtain_simple_gensym_string(length(text_string));
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    char_new_value = ICHAR(text_string,i);
    SET_ICHAR(result_1,i,char_new_value);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* RETURN-FROM-ZGW-START-HTTP-SERVER-1 */
Object g2int_return_from_zgw_start_http_server_1(signal_name,
	    signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,50);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object Qg2int_http_startup_failed;  /* http-startup-failed */

static Object string_constant_28;  /* "Failed to start HTTP server." */

/* SHARED-ZGW-START-HTTP-SERVER */
void g2int_shared_zgw_start_http_server(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector, port_number;
    Object signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,51);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      port_number = 
	      g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  g2int_startup_http_server(port_number);
	  if ( !TRUEP(G2int_the_http_server_threadqm))
	      g2int_signal_from_rpc(Qg2int_http_startup_failed,
		      string_constant_28);
	  g2int_return_from_zgw_start_http_server_1(Qg2int_ok,string_constant);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_start_http_server_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_29;  /* "zgw_start_http_server" */

/* ZGW-START-HTTP-SERVER */
DLLEXPORT void zgw_start_http_server(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,52);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_29);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_start_http_server(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_start_http_server(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_29);
}

/* RETURN-FROM-ZGW-TENDER-RESOURCES-1 */
Object g2int_return_from_zgw_tender_resources_1(signal_name,signal_description)
    Object signal_name, signal_description;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,53);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)2L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)2L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

static Object Qg2int_tender_failed;  /* tender-failed */

static Object string_constant_30;  /* "Tender index must be in range 0 to 1000" */

static Object string_constant_31;  /* "The HTTP Server is not currently running." */

static Object string_constant_32;  /* "Tendering ~D ~S ~S" */

static Object string_constant_33;  /* "Tendering failed: ~D" */

static Object string_constant_34;  /* "Tendering failed" */

/* SHARED-ZGW-TENDER-RESOURCES */
void g2int_shared_zgw_tender_resources(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector, index_1;
    Object pattern, method, result_1, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(60,54);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      index_1 = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      pattern = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)1L + (SI_Long)1L));
      method = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)2L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  if ( !TRUEP(num_len(3,FIX((SI_Long)0L),index_1,FIX((SI_Long)1000L))))
	      g2int_signal_from_rpc(Qg2int_tender_failed,string_constant_30);
	  if ( !TRUEP(G2int_the_http_server_threadqm))
	      g2int_signal_from_rpc(Qg2int_tender_failed,string_constant_31);
	  if (PUSH_AREA(Dynamic_area,0)) {
	      g2int_notify_user_at_console(4,string_constant_32,index_1,
		      pattern,method);
	      result_1 = g2int_install_tender_of_resource(index_1,pattern,
		      method);
	      if ( !((SI_Long)0L == IFIX(result_1))) {
		  g2int_notify_user_at_console(2,string_constant_33,result_1);
		  g2int_signal_from_rpc(Qg2int_tender_failed,
			  string_constant_34);
	      }
	      g2int_return_from_zgw_tender_resources_1(Qg2int_ok,
		      string_constant);
	  }
	  POP_AREA(0);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_tender_resources_1(signal_name,
		  signal_description);
    POP_SPECIAL();
}

static Object string_constant_35;  /* "zgw_tender_resources" */

/* ZGW-TENDER-RESOURCES */
DLLEXPORT void zgw_tender_resources(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,55);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_35);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_tender_resources(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_tender_resources(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_35);
}

/* RETURN-FROM-ZGW-MAKE-BASE64-ENCODED-1 */
Object g2int_return_from_zgw_make_base64_encoded_1(signal_name,
	    signal_description,result_1)
    Object signal_name, signal_description, result_1;
{
    Object call_handle, c_vector_of_items, magic_number, result_items, temp;

    x_note_fn_call(60,56);
    call_handle = G2int_current_rpc_call_handle;
    c_vector_of_items = gsi_make_items((SI_Long)3L);
    magic_number = inline_gsi_get_magic_header(c_vector_of_items);
    result_items = IFIX(magic_number) == (SI_Long)5472500L ? 
	    inline_get_array_from_c(c_vector_of_items,
	    G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	    G2int_gsi_bad_magic_number);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)0L + 
	    (SI_Long)1L),signal_name);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)1L + 
	    (SI_Long)1L),signal_description);
    g2int_set_simple_value_in_item(ISVREF(result_items,(SI_Long)2L + 
	    (SI_Long)1L),result_1);
    if ( !EQ(FIX((SI_Long)-1L),call_handle)) {
	temp = inline_extract_c_array(result_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_return_values(temp,(SI_Long)3L,call_handle,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
    }
    g2int_shared_gsi_reclaim_items(inline_extract_c_array(result_items,
	    G2int_gsi_magic_offset));
    return g2int_clear_thread_pool(G2int_root_thread);
}

/* SHARED-ZGW-MAKE-BASE64-ENCODED */
void g2int_shared_zgw_make_base64_encoded(c_argument_vector,count_1,
	    call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object current_rpc_call_handle, magic_number, argument_vector, input;
    Object output, signal_name, signal_description;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(60,57);
    current_rpc_call_handle = call_handle;
    PUSH_SPECIAL(G2int_current_rpc_call_handle,current_rpc_call_handle,0);
      magic_number = inline_gsi_get_magic_header(c_argument_vector);
      argument_vector = IFIX(magic_number) == (SI_Long)5472500L ? 
	      inline_get_array_from_c(c_argument_vector,
	      G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
	      G2int_gsi_bad_magic_number);
      input = g2int_get_value_of_any_simple_type(ISVREF(argument_vector,
	      (SI_Long)0L + (SI_Long)1L));
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  output = g2int_convert_text_to_base64_encoding(input);
	  g2int_return_from_zgw_make_base64_encoded_1(Qg2int_ok,
		  string_constant,output);
	  g2int_reclaim_gensym_string(output);
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name)
	  g2int_return_from_zgw_make_base64_encoded_1(signal_name,
		  signal_description,string_constant);
    POP_SPECIAL();
}

static Object string_constant_36;  /* "zgw_make_base64_encoded" */

/* ZGW-MAKE-BASE64-ENCODED */
DLLEXPORT void zgw_make_base64_encoded(c_argument_vector,count_1,call_handle)
    Object c_argument_vector, call_handle;
    SI_Long count_1;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(60,58);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_36);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_zgw_make_base64_encoded(c_argument_vector,count_1,
		    call_handle);
	  POP_SPECIAL();
      }
      else {
	  if (PUSH_CATCH(Qg2int_gsi_catch,0)) {
	      shutdown_catch_tag = Qg2int_gsi_catch;
	      top_level_error_catcher_tag = Qg2int_gsi_catch;
	      abort_level_0_tag = Qg2int_gsi_catch;
	      PUSH_SPECIAL(G2int_abort_level_0_tag,abort_level_0_tag,2);
		PUSH_SPECIAL(G2int_top_level_error_catcher_tag,top_level_error_catcher_tag,
			1);
		  PUSH_SPECIAL(G2int_shutdown_catch_tag,shutdown_catch_tag,0);
		    g2int_shared_zgw_make_base64_encoded(c_argument_vector,
			    count_1,call_handle);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_36);
}

/* GSI-GET-TCP-PORT */
SI_Long gsi_get_tcp_port()
{
    SI_Long result_1;

    x_note_fn_call(60,59);
    result_1 = (SI_Long)7736L;
    return result_1;
}

static Object Kpaused;             /* :paused */

static Object string_constant_37;  /* "G2 was paused" */

/* GSI-PAUSE-CONTEXT */
SI_Long gsi_pause_context()
{
    SI_Long result_1;

    x_note_fn_call(60,60);
    G2int_the_state_of_g2 = Kpaused;
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_37));
    return result_1;
}

static Object Krunning;            /* :running */

static Object string_constant_38;  /* "G2 was resumed" */

/* GSI-RESUME-CONTEXT */
SI_Long gsi_resume_context()
{
    SI_Long result_1;

    x_note_fn_call(60,61);
    G2int_the_state_of_g2 = Krunning;
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_38));
    return result_1;
}

static Object string_constant_39;  /* "poll" */

/* GSI-G2-POLL */
SI_Long gsi_g2_poll()
{
    SI_Long result_1;

    x_note_fn_call(60,62);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_39));
    return result_1;
}

static Object string_constant_40;  /* "receive-registration" */

/* GSI-RECEIVE-REGISTRATION */
SI_Long gsi_receive_registration(registration)
    Object registration;
{
    SI_Long result_1;

    x_note_fn_call(60,63);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_40));
    return result_1;
}

static Object string_constant_41;  /* "receive-deregistrations" */

/* GSI-RECEIVE-DEREGISTRATIONS */
SI_Long gsi_receive_deregistrations(registration_item_array,count_1)
    Object registration_item_array;
    SI_Long count_1;
{
    SI_Long result_1;

    x_note_fn_call(60,64);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_41));
    return result_1;
}

static Object string_constant_42;  /* "get-data" */

/* GSI-GET-DATA */
SI_Long gsi_get_data(registration_item_array,count_1)
    Object registration_item_array;
    SI_Long count_1;
{
    SI_Long result_1;

    x_note_fn_call(60,65);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_42));
    return result_1;
}

static Object string_constant_43;  /* "set-data" */

/* GSI-SET-DATA */
SI_Long gsi_set_data(registration_item_array,count_1)
    Object registration_item_array;
    SI_Long count_1;
{
    SI_Long result_1;

    x_note_fn_call(60,66);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_43));
    return result_1;
}

static Object string_constant_44;  /* "receive-message" */

/* GSI-RECEIVE-MESSAGE */
SI_Long gsi_receive_message(message,length_1)
    Object message;
    SI_Long length_1;
{
    SI_Long result_1;

    x_note_fn_call(60,67);
    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(1,
	    string_constant_44));
    return result_1;
}

/* INNER-INITIALIZE-CONTEXT */
SI_Long inner_initialize_context()
{
    SI_Long result_1;

    x_note_fn_call(60,68);
    g2int_initialize_fetch_styles_of_context();
    G2int_the_state_of_g2 = Krunning;
    result_1 = FIXNUM_TO_LONG(G2int_gsi_success);
    return result_1;
}

static Object string_constant_45;  /* "G2 was reset." */

static Object string_constant_46;  /* "Shutting down HTTP server." */

static Object Kunconnected;        /* :unconnected */

/* GSI-SHUTDOWN-CONTEXT */
SI_Long gsi_shutdown_context()
{
    Object svref_arg_1;
    SI_Long result_1;

    x_note_fn_call(60,69);
    g2int_shutdown_fetch_styles_of_context();
    g2int_notify_user_at_console(1,string_constant_45);
    if (G2int_the_http_server_threadqm) {
	g2int_notify_user_at_console(1,string_constant_46);
	g2int_thread_kill(G2int_the_http_server_threadqm);
    }
    svref_arg_1 = G2int_the_bridge_configuration_info;
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = Nil;
    G2int_the_state_of_g2 = Kunconnected;
    result_1 = FIXNUM_TO_LONG(G2int_gsi_success);
    return result_1;
}

static Object string_constant_47;  /* "~%Ignoring -- Error ~D ~S" */

/* GW-ERROR-HANDLER */
SI_Long gw_error_handler(context,number,message)
    SI_Long context, number;
    char *message;
{
    SI_Long result_1;
    XDeclare_area(1);

    x_note_fn_call(60,70);
    if ( !((SI_Long)-32768L <= number && number <= (SI_Long)32767L)) {
	if (PUSH_AREA(Dynamic_area,0))
	    result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(3,
		    string_constant_47,LONG_TO_FIXNUM(number),
		    istring_to_string_or_nil(message)));
	POP_AREA(0);
    }
    else
	switch ((short)number) {
	  case 259:
	    result_1 = FIXNUM_TO_LONG(Nil);
	    break;
	  default:
	    if (PUSH_AREA(Dynamic_area,0))
		result_1 = FIXNUM_TO_LONG(g2int_notify_user_at_console(3,
			string_constant_47,LONG_TO_FIXNUM(number),
			istring_to_string_or_nil(message)));
	    POP_AREA(0);
	    break;
	}
    return result_1;
}

static Object string_constant_48;  /* "Bridge Starting Up" */

/* STARTUP-BRIDGE */
Object g2int_startup_bridge()
{
    x_note_fn_call(60,71);
    g2int_notify_user_at_console(1,string_constant_48);
    g2int_cache_command_line_if_necessary();
    G2int_command_line_arguments = g2int_get_initial_command_line_arguments();
    return VALUES_1(G2int_command_line_arguments);
}

static Object string_constant_49;  /* "Bridge Shutting Down" */

/* SHUTDOWN-BRIDGE */
Object g2int_shutdown_bridge()
{
    x_note_fn_call(60,72);
    g2int_notify_user_at_console(1,string_constant_49);
    return g2int_shutdown_thread_tree();
}

static Object Qg2int_shutdown;     /* shutdown */

static Object Qok;                 /* #:ok */

static Object string_constant_50;  /* "Caught shutdown." */

/* KICK-BRIDGE-TASKS */
Object g2int_kick_bridge_tasks()
{
    Object temp, result_1;
    SI_Long ab_loop_repeat_;
    Declare_catch(1);

    x_note_fn_call(60,73);
    if (PUSH_CATCH(Qg2int_shutdown,0)) {
	g2int_end_io_wait();
	ab_loop_repeat_ = (SI_Long)100L;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	g2int_feed_running_threads();
	temp = FIX((SI_Long)0L);
	if (NUM_EQ(temp,G2int_number_of_running_threads))
	    goto end;
	goto next_loop;
      end_loop:
      end:;
	result_1 = Qok;
    }
    else
	result_1 = CATCH_VALUES();
    POP_CATCH(0);
    if ( !EQ(result_1,Qok)) {
	g2int_notify_user_at_console(1,string_constant_50);
	G2int_shutdown_requested = T;
	return VALUES_1(G2int_shutdown_requested);
    }
    else
	return VALUES_1(Nil);
}

void web_gsi_INIT()
{
    Object entry_qm, pushnew_arg, statistic_counters_new_value;
    Object AB_package, Qg2int_return_from_zgw_make_base64_encoded_1;
    Object Qg2int_return_function_of_rpc, Qzgw_make_base64_encoded;
    Object Qg2int_ignored_return_values_for_signals, list_constant;
    Object Qg2int_return_from_zgw_tender_resources_1, Qzgw_tender_resources;
    Object Qg2int_return_from_zgw_start_http_server_1, Qzgw_start_http_server;
    Object string_constant_55, Qg2int_count_of_gw_fetch_url_contents;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_1;
    Object string_constant_54, Qg2int_count_of_gw_install_fetch_style;
    Object Qg2int_return_from_zgw_get_attribute_of_request_1;
    Object Qzgw_get_attribute_of_request;
    Object Qg2int_return_from_zgw_finish_url_reply_1, Qzgw_finish_url_reply;
    Object Qg2int_return_from_zgw_add_to_url_reply_1, Qzgw_add_to_url_reply;
    Object Qg2int_return_from_zgw_set_url_reply_charset_1;
    Object Qzgw_set_url_reply_charset;
    Object Qg2int_return_from_zgw_set_header_field_1, Qzgw_set_header_field;
    Object Qg2int_return_from_zgw_decline_to_serve_url_1;
    Object Qzgw_decline_to_serve_url, string_constant_53;
    Object Qg2int_count_of_url_requests_upon_g2;
    Object Qg2int_return_from_zgw_configure_bridge_1, Qzgw_configure_bridge;
    Object string_constant_52, Qg2int_count_of_gw_configure_bridge;
    Object Qg2int_return_from_zgw_kill_bridge_1, Qzgw_kill_bridge;
    Object Qg2int_shutdown_requested, Qg2int_return_from_zgw_ping_1, Qzgw_ping;
    Object string_constant_51, Qg2int_count_of_gw_ping;

    x_note_fn_call(60,74);
    SET_PACKAGE("AB");
    if (G2int_count_of_gw_ping == UNBOUND)
	G2int_count_of_gw_ping = FIX((SI_Long)0L);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_count_of_gw_ping = STATIC_SYMBOL("COUNT-OF-GW-PING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_gw_ping,G2int_count_of_gw_ping);
    string_constant_51 = STATIC_STRING("~D calls on gw-ping");
    entry_qm = g2int_assq_function(Qg2int_count_of_gw_ping,
	    G2int_statistic_counters);
    if (entry_qm)
	M_SECOND(entry_qm) = string_constant_51;
    else {
	pushnew_arg = LIST_2(Qg2int_count_of_gw_ping,string_constant_51);
	statistic_counters_new_value = adjoin(2,pushnew_arg,
		G2int_statistic_counters);
	G2int_statistic_counters = statistic_counters_new_value;
    }
    Qzgw_ping = STATIC_SYMBOL("ZGW-PING",AB_package);
    Qg2int_ignored_return_values_for_signals = 
	    STATIC_SYMBOL("IGNORED-RETURN-VALUES-FOR-SIGNALS",AB_package);
    g2int_mutate_global_property(Qzgw_ping,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_ping_1 = STATIC_SYMBOL("RETURN-FROM-ZGW-PING-1",
	    AB_package);
    Qg2int_return_function_of_rpc = STATIC_SYMBOL("RETURN-FUNCTION-OF-RPC",
	    AB_package);
    g2int_mutate_global_property(Qzgw_ping,Qg2int_return_from_zgw_ping_1,
	    Qg2int_return_function_of_rpc);
    Qg2int_gsi_web = STATIC_SYMBOL("GSI-WEB",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_ping_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_ping_1,NIL,FALSE,2,2));
    Qg2int_rpc_signal = STATIC_SYMBOL("RPC-SIGNAL",AB_package);
    Qg2int_ok = STATIC_SYMBOL("OK",AB_package);
    string_constant = STATIC_STRING("");
    string_constant_1 = STATIC_STRING("zgw_ping");
    Qg2int_gsi_catch = STATIC_SYMBOL("GSI-CATCH",AB_package);
    Qg2int_shutdown_requested = STATIC_SYMBOL("SHUTDOWN-REQUESTED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_shutdown_requested,
	    G2int_shutdown_requested);
    if (G2int_shutdown_requested == UNBOUND)
	G2int_shutdown_requested = Nil;
    Qzgw_kill_bridge = STATIC_SYMBOL("ZGW-KILL-BRIDGE",AB_package);
    g2int_mutate_global_property(Qzgw_kill_bridge,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_kill_bridge_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-KILL-BRIDGE-1",AB_package);
    g2int_mutate_global_property(Qzgw_kill_bridge,
	    Qg2int_return_from_zgw_kill_bridge_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_kill_bridge_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_kill_bridge_1,NIL,FALSE,
	    2,2));
    string_constant_2 = STATIC_STRING("G2 Killed Me.");
    Kshutdown = STATIC_SYMBOL("SHUTDOWN",Pkeyword);
    string_constant_3 = STATIC_STRING("zgw_kill_bridge");
    if (G2int_count_of_gw_configure_bridge == UNBOUND)
	G2int_count_of_gw_configure_bridge = FIX((SI_Long)0L);
    Qg2int_count_of_gw_configure_bridge = 
	    STATIC_SYMBOL("COUNT-OF-GW-CONFIGURE-BRIDGE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_gw_configure_bridge,
	    G2int_count_of_gw_configure_bridge);
    string_constant_52 = STATIC_STRING("~D calls on gw-configure-bridge");
    entry_qm = g2int_assq_function(Qg2int_count_of_gw_configure_bridge,
	    G2int_statistic_counters);
    if (entry_qm)
	M_SECOND(entry_qm) = string_constant_52;
    else {
	pushnew_arg = LIST_2(Qg2int_count_of_gw_configure_bridge,
		string_constant_52);
	statistic_counters_new_value = adjoin(2,pushnew_arg,
		G2int_statistic_counters);
	G2int_statistic_counters = statistic_counters_new_value;
    }
    Qzgw_configure_bridge = STATIC_SYMBOL("ZGW-CONFIGURE-BRIDGE",AB_package);
    g2int_mutate_global_property(Qzgw_configure_bridge,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_configure_bridge_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-CONFIGURE-BRIDGE-1",AB_package);
    g2int_mutate_global_property(Qzgw_configure_bridge,
	    Qg2int_return_from_zgw_configure_bridge_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_configure_bridge_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_configure_bridge_1,NIL,
	    FALSE,2,2));
    string_constant_4 = STATIC_STRING("Configure-bridge");
    Qg2int_maximum_count_of_simultaneous_transactions = 
	    STATIC_SYMBOL("MAXIMUM-COUNT-OF-SIMULTANEOUS-TRANSACTIONS",
	    AB_package);
    Qg2int_message_pool_size = STATIC_SYMBOL("MESSAGE-POOL-SIZE",AB_package);
    string_constant_5 = STATIC_STRING("zgw_configure_bridge");
    if (G2int_count_of_url_requests_upon_g2 == UNBOUND)
	G2int_count_of_url_requests_upon_g2 = FIX((SI_Long)0L);
    Qg2int_count_of_url_requests_upon_g2 = 
	    STATIC_SYMBOL("COUNT-OF-URL-REQUESTS-UPON-G2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_url_requests_upon_g2,
	    G2int_count_of_url_requests_upon_g2);
    string_constant_53 = STATIC_STRING("~D URL have been requested from G2.");
    entry_qm = g2int_assq_function(Qg2int_count_of_url_requests_upon_g2,
	    G2int_statistic_counters);
    if (entry_qm)
	M_SECOND(entry_qm) = string_constant_53;
    else {
	pushnew_arg = LIST_2(Qg2int_count_of_url_requests_upon_g2,
		string_constant_53);
	statistic_counters_new_value = adjoin(2,pushnew_arg,
		G2int_statistic_counters);
	G2int_statistic_counters = statistic_counters_new_value;
    }
    string_constant_6 = STATIC_STRING("Ask G2: ~S");
    Qzgw_decline_to_serve_url = STATIC_SYMBOL("ZGW-DECLINE-TO-SERVE-URL",
	    AB_package);
    g2int_mutate_global_property(Qzgw_decline_to_serve_url,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_decline_to_serve_url_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-DECLINE-TO-SERVE-URL-1",AB_package);
    g2int_mutate_global_property(Qzgw_decline_to_serve_url,
	    Qg2int_return_from_zgw_decline_to_serve_url_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_decline_to_serve_url_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_decline_to_serve_url_1,
	    NIL,FALSE,2,2));
    string_constant_7 = STATIC_STRING("404 Not Found");
    string_constant_8 = STATIC_STRING("zgw_decline_to_serve_url");
    Qzgw_set_header_field = STATIC_SYMBOL("ZGW-SET-HEADER-FIELD",AB_package);
    g2int_mutate_global_property(Qzgw_set_header_field,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_set_header_field_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-SET-HEADER-FIELD-1",AB_package);
    g2int_mutate_global_property(Qzgw_set_header_field,
	    Qg2int_return_from_zgw_set_header_field_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_set_header_field_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_set_header_field_1,NIL,
	    FALSE,2,2));
    Qg2int_invalid_header = STATIC_SYMBOL("INVALID-HEADER",AB_package);
    string_constant_9 = 
	    STATIC_STRING("Can\'t set header fields after URL data sending has begun.");
    string_constant_10 = STATIC_STRING("zgw_set_header_field");
    Qzgw_set_url_reply_charset = STATIC_SYMBOL("ZGW-SET-URL-REPLY-CHARSET",
	    AB_package);
    g2int_mutate_global_property(Qzgw_set_url_reply_charset,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_set_url_reply_charset_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-SET-URL-REPLY-CHARSET-1",
	    AB_package);
    g2int_mutate_global_property(Qzgw_set_url_reply_charset,
	    Qg2int_return_from_zgw_set_url_reply_charset_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_set_url_reply_charset_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_set_url_reply_charset_1,
	    NIL,FALSE,2,2));
    string_constant_11 = 
	    STATIC_STRING("Can\'t set header fields (URL reply charset) after URL data sending has begun.");
    string_constant_12 = STATIC_STRING("zgw_set_url_reply_charset");
    Qzgw_add_to_url_reply = STATIC_SYMBOL("ZGW-ADD-TO-URL-REPLY",AB_package);
    g2int_mutate_global_property(Qzgw_add_to_url_reply,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_add_to_url_reply_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-ADD-TO-URL-REPLY-1",AB_package);
    g2int_mutate_global_property(Qzgw_add_to_url_reply,
	    Qg2int_return_from_zgw_add_to_url_reply_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_add_to_url_reply_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_add_to_url_reply_1,NIL,
	    FALSE,2,2));
    string_constant_13 = STATIC_STRING("zgw_add_to_url_reply");
    Qzgw_finish_url_reply = STATIC_SYMBOL("ZGW-FINISH-URL-REPLY",AB_package);
    g2int_mutate_global_property(Qzgw_finish_url_reply,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_finish_url_reply_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-FINISH-URL-REPLY-1",AB_package);
    g2int_mutate_global_property(Qzgw_finish_url_reply,
	    Qg2int_return_from_zgw_finish_url_reply_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_finish_url_reply_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_finish_url_reply_1,NIL,
	    FALSE,2,2));
    string_constant_14 = STATIC_STRING("zgw_finish_url_reply");
    Qzgw_get_attribute_of_request = 
	    STATIC_SYMBOL("ZGW-GET-ATTRIBUTE-OF-REQUEST",AB_package);
    list_constant = STATIC_CONS(string_constant,Qnil);
    g2int_mutate_global_property(Qzgw_get_attribute_of_request,
	    list_constant,Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_get_attribute_of_request_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-GET-ATTRIBUTE-OF-REQUEST-1",
	    AB_package);
    g2int_mutate_global_property(Qzgw_get_attribute_of_request,
	    Qg2int_return_from_zgw_get_attribute_of_request_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_get_attribute_of_request_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_get_attribute_of_request_1,
	    NIL,FALSE,3,3));
    string_constant_15 = STATIC_STRING("zgw_get_attribute_of_request");
    if (G2int_count_of_gw_install_fetch_style == UNBOUND)
	G2int_count_of_gw_install_fetch_style = FIX((SI_Long)0L);
    Qg2int_count_of_gw_install_fetch_style = 
	    STATIC_SYMBOL("COUNT-OF-GW-INSTALL-FETCH-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_gw_install_fetch_style,
	    G2int_count_of_gw_install_fetch_style);
    string_constant_54 = STATIC_STRING("~D calls on gw-install-fetch-style");
    entry_qm = g2int_assq_function(Qg2int_count_of_gw_install_fetch_style,
	    G2int_statistic_counters);
    if (entry_qm)
	M_SECOND(entry_qm) = string_constant_54;
    else {
	pushnew_arg = LIST_2(Qg2int_count_of_gw_install_fetch_style,
		string_constant_54);
	statistic_counters_new_value = adjoin(2,pushnew_arg,
		G2int_statistic_counters);
	G2int_statistic_counters = statistic_counters_new_value;
    }
    string_constant_16 = STATIC_STRING("HTTP/");
    string_constant_17 = STATIC_STRING(".");
    Qg2int_error_message_from_server = 
	    STATIC_SYMBOL("ERROR-MESSAGE-FROM-SERVER",AB_package);
    Qg2int_major_version_of_http = STATIC_SYMBOL("MAJOR-VERSION-OF-HTTP",
	    AB_package);
    Qg2int_minor_version_of_http = STATIC_SYMBOL("MINOR-VERSION-OF-HTTP",
	    AB_package);
    Qg2int_error_code_from_server = STATIC_SYMBOL("ERROR-CODE-FROM-SERVER",
	    AB_package);
    G2int_cache_name_counter = Nil;
    Qg2int_wide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qg2int_gensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_1,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)90L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_18 = STATIC_STRING("toc");
    Qg2int_unbound_in_protected_let = 
	    STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_begining_of_resource = STATIC_SYMBOL("BEGINING-OF-RESOURCE",
	    AB_package);
    if (G2int_items_in_resource_cache == UNBOUND)
	G2int_items_in_resource_cache = Nil;
    Qg2int_cache_filename = STATIC_SYMBOL("CACHE-FILENAME",AB_package);
    Qg2int_url = STATIC_SYMBOL("URL",AB_package);
    Qg2int_mimi_headers_from_server = 
	    STATIC_SYMBOL("MIMI-HEADERS-FROM-SERVER",AB_package);
    string_constant_19 = 
	    STATIC_STRING("Writing table of contents for cache (~D entries)");
    string_constant_20 = 
	    STATIC_STRING("Cache directory (~S) doesn\'t exist or isn\'t writable.");
    string_constant_21 = STATIC_STRING("gm-toc-1.0");
    string_constant_22 = 
	    STATIC_STRING(";;; Machine Generated -- Do Not Modify");
    string_constant_23 = STATIC_STRING("S~D|~S");
    string_constant_24 = STATIC_STRING("T~D|~A");
    string_constant_25 = STATIC_STRING("C");
    string_constant_26 = STATIC_STRING("L~D|");
    string_constant_27 = 
	    STATIC_STRING("Read table of contents for cache (~D entries)");
    Qcdrcode_marker = STATIC_SYMBOL("CDRCODE-MARKER",Qnil);
    if (G2int_count_of_gw_fetch_url_contents == UNBOUND)
	G2int_count_of_gw_fetch_url_contents = FIX((SI_Long)0L);
    Qg2int_count_of_gw_fetch_url_contents = 
	    STATIC_SYMBOL("COUNT-OF-GW-FETCH-URL-CONTENTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_count_of_gw_fetch_url_contents,
	    G2int_count_of_gw_fetch_url_contents);
    string_constant_55 = 
	    STATIC_STRING("~D calls on gw-install-fetch-url-contents");
    entry_qm = g2int_assq_function(Qg2int_count_of_gw_fetch_url_contents,
	    G2int_statistic_counters);
    if (entry_qm)
	M_SECOND(entry_qm) = string_constant_55;
    else {
	pushnew_arg = LIST_2(Qg2int_count_of_gw_fetch_url_contents,
		string_constant_55);
	statistic_counters_new_value = adjoin(2,pushnew_arg,
		G2int_statistic_counters);
	G2int_statistic_counters = statistic_counters_new_value;
    }
    Kadd_data = STATIC_SYMBOL("ADD-DATA",Pkeyword);
    Kend_data = STATIC_SYMBOL("END-DATA",Pkeyword);
    Qg2int_end_of_transmission_recieved = 
	    STATIC_SYMBOL("END-OF-TRANSMISSION-RECIEVED",AB_package);
    Qzgw_start_http_server = STATIC_SYMBOL("ZGW-START-HTTP-SERVER",AB_package);
    g2int_mutate_global_property(Qzgw_start_http_server,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_start_http_server_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-START-HTTP-SERVER-1",AB_package);
    g2int_mutate_global_property(Qzgw_start_http_server,
	    Qg2int_return_from_zgw_start_http_server_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_start_http_server_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_start_http_server_1,NIL,
	    FALSE,2,2));
    Qg2int_http_startup_failed = STATIC_SYMBOL("HTTP-STARTUP-FAILED",
	    AB_package);
    string_constant_28 = STATIC_STRING("Failed to start HTTP server.");
    string_constant_29 = STATIC_STRING("zgw_start_http_server");
    Qzgw_tender_resources = STATIC_SYMBOL("ZGW-TENDER-RESOURCES",AB_package);
    g2int_mutate_global_property(Qzgw_tender_resources,Qnil,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_tender_resources_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-TENDER-RESOURCES-1",AB_package);
    g2int_mutate_global_property(Qzgw_tender_resources,
	    Qg2int_return_from_zgw_tender_resources_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_tender_resources_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_tender_resources_1,NIL,
	    FALSE,2,2));
    Qg2int_tender_failed = STATIC_SYMBOL("TENDER-FAILED",AB_package);
    string_constant_30 = 
	    STATIC_STRING("Tender index must be in range 0 to 1000");
    string_constant_31 = 
	    STATIC_STRING("The HTTP Server is not currently running.");
    string_constant_32 = STATIC_STRING("Tendering ~D ~S ~S");
    string_constant_33 = STATIC_STRING("Tendering failed: ~D");
    string_constant_34 = STATIC_STRING("Tendering failed");
    string_constant_35 = STATIC_STRING("zgw_tender_resources");
    Qzgw_make_base64_encoded = STATIC_SYMBOL("ZGW-MAKE-BASE64-ENCODED",
	    AB_package);
    g2int_mutate_global_property(Qzgw_make_base64_encoded,list_constant,
	    Qg2int_ignored_return_values_for_signals);
    Qg2int_return_from_zgw_make_base64_encoded_1 = 
	    STATIC_SYMBOL("RETURN-FROM-ZGW-MAKE-BASE64-ENCODED-1",AB_package);
    g2int_mutate_global_property(Qzgw_make_base64_encoded,
	    Qg2int_return_from_zgw_make_base64_encoded_1,
	    Qg2int_return_function_of_rpc);
    SET_SYMBOL_FUNCTION(Qg2int_return_from_zgw_make_base64_encoded_1,
	    STATIC_FUNCTION(g2int_return_from_zgw_make_base64_encoded_1,
	    NIL,FALSE,3,3));
    string_constant_36 = STATIC_STRING("zgw_make_base64_encoded");
    Kpaused = STATIC_SYMBOL("PAUSED",Pkeyword);
    string_constant_37 = STATIC_STRING("G2 was paused");
    Krunning = STATIC_SYMBOL("RUNNING",Pkeyword);
    string_constant_38 = STATIC_STRING("G2 was resumed");
    string_constant_39 = STATIC_STRING("poll");
    string_constant_40 = STATIC_STRING("receive-registration");
    string_constant_41 = STATIC_STRING("receive-deregistrations");
    string_constant_42 = STATIC_STRING("get-data");
    string_constant_43 = STATIC_STRING("set-data");
    string_constant_44 = STATIC_STRING("receive-message");
    string_constant_45 = STATIC_STRING("G2 was reset.");
    string_constant_46 = STATIC_STRING("Shutting down HTTP server.");
    Kunconnected = STATIC_SYMBOL("UNCONNECTED",Pkeyword);
    string_constant_47 = STATIC_STRING("~%Ignoring -- Error ~D ~S");
    string_constant_48 = STATIC_STRING("Bridge Starting Up");
    string_constant_49 = STATIC_STRING("Bridge Shutting Down");
    Qg2int_shutdown = STATIC_SYMBOL("SHUTDOWN",AB_package);
    Qok = STATIC_SYMBOL("OK",Qnil);
    string_constant_50 = STATIC_STRING("Caught shutdown.");
}
