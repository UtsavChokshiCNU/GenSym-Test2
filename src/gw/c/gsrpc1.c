/* gsrpc1.c
 * Input file:  gsi-rpc1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gsrpc1.h"


/* LOOKUP-OR-CREATE-GSI-LOCAL-FUNCTION */
Object g2int_lookup_or_create_gsi_local_function(name,create_p)
    Object name, create_p;
{
    Object application, local_function, ab_loop_list_, temp;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(50,0);
    application = g2int_current_gsi_application();
    local_function = Nil;
    ab_loop_list_ = ISVREF(application,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local_function = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(name,ISVREF(local_function,(SI_Long)3L))) {
	temp = local_function;
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    if (temp);
    else if (create_p) {
	local_function = g2int_make_gsi_local_function_1();
	SVREF(local_function,FIX((SI_Long)3L)) = name;
	SVREF(local_function,FIX((SI_Long)2L)) = Nil;
	gensym_push_modify_macro_arg = local_function;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(application,(SI_Long)4L);
	svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	SVREF(application,FIX((SI_Long)4L)) = svref_new_value;
	temp = local_function;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qg2int_gensym;       /* gensym */

/* RECLAIM-LIST-OF-LOCAL-FUNCTIONS */
Object g2int_reclaim_list_of_local_functions(list_1)
    Object list_1;
{
    Object lf, gensym_pop_store, cons_1, next_cons, cdr_new_value;

    x_note_fn_call(50,1);
    lf = Nil;
  next_loop:
    if ( !TRUEP(list_1))
	goto end_loop;
    gensym_pop_store = Nil;
    cons_1 = list_1;
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
    list_1 = next_cons;
    lf = gensym_pop_store;
    g2int_reclaim_gsi_local_function_1(lf);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* GSI-LOOKUP-NEW-REMOTE-PROCEDURE-NAME */
Object g2int_gsi_lookup_new_remote_procedure_name(new_remote_procedure_name)
    Object new_remote_procedure_name;
{
    Object local_function;

    x_note_fn_call(50,2);
    local_function = 
	    g2int_lookup_or_create_gsi_local_function(ISVREF(new_remote_procedure_name,
	    (SI_Long)1L),Nil);
    if (local_function)
	SVREF(new_remote_procedure_name,FIX((SI_Long)3L)) = local_function;
    return VALUES_1(local_function);
}

/* GSI-CALL-MISSING-PROCEDURE-HANDLER */
Object g2int_gsi_call_missing_procedure_handler(new_remote_procedure_name)
    Object new_remote_procedure_name;
{
    Object name_string, name_for_callback;

    x_note_fn_call(50,3);
    name_string = 
	    g2int_symbol_name_text_string(ISVREF(new_remote_procedure_name,
	    (SI_Long)1L));
    name_for_callback = G2int_gsi_wide_api_p ? name_string : 
	    g2int_wide_string_to_gensym_string_for_gsi(name_string);
    g2int_call_gsi_callback(2,G2int_gsi_missing_procedure_handler,
	    name_for_callback);
    if ( !TRUEP(g2int_text_string_p(name_for_callback)))
	g2int_reclaim_gensym_string(name_for_callback);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_remote_proc;  /* handle_icp_define_remote_proc */

/* GSI-HANDLE-DEFINE-REMOTE-PROCEDURE-NAME */
Object g2int_gsi_handle_define_remote_procedure_name(new_remote_procedure_name)
    Object new_remote_procedure_name;
{
    Object temp;

    x_note_fn_call(50,4);
    temp = 
	    g2int_gsi_lookup_new_remote_procedure_name(new_remote_procedure_name);
    if (temp);
    else {
	g2int_gsi_call_missing_procedure_handler(new_remote_procedure_name);
	temp = 
		g2int_gsi_lookup_new_remote_procedure_name(new_remote_procedure_name);
    }
    if (temp);
    else {
	g2int_gsi_warning(3,Qg2int_handle_icp_define_remote_proc,
		G2int_gsi_local_function_undefined,
		ISVREF(new_remote_procedure_name,(SI_Long)1L));
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* SHARED-GSI-RPC-DECLARE-LOCAL-PLAIN */
void g2int_shared_gsi_rpc_declare_local_plain(wide_api_p,function,
	    gsi_fc_outer_function_name_in_g2)
    Object wide_api_p, function, gsi_fc_outer_function_name_in_g2;
{
    Object function_name_in_g2, local_function;

    x_note_fn_call(50,5);
    function_name_in_g2 =  !TRUEP(gsi_fc_outer_function_name_in_g2) ? Nil :
	     g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_function_name_in_g2) 
	    : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_function_name_in_g2));
    local_function = 
	    g2int_lookup_or_create_gsi_local_function(function_name_in_g2,T);
    SVREF(local_function,FIX((SI_Long)1L)) = function;
}

static Object string_constant;     /* "gsi_rpc_declare_local_plain" */

static Object Qg2int_gsi_catch;    /* gsi-catch */

/* GSI-RPC-DECLARE-LOCAL-PLAIN */
DLLEXPORT void gsi_rpc_declare_local_plain(function,function_name_in_g2)
    Object function, function_name_in_g2;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,6);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_rpc_declare_local_plain(G2int_gsi_wide_api_p,
		    function,function_name_in_g2);
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
		    g2int_shared_gsi_rpc_declare_local_plain(G2int_gsi_wide_api_p,
			    function,function_name_in_g2);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant);
}

/* SHARED-GSI-RPC-DECLARE-LOCAL-W-U-D */
void g2int_shared_gsi_rpc_declare_local_w_u_d(wide_api_p,function,
	    user_data,gsi_fc_outer_function_name_in_g2)
    Object wide_api_p, function, user_data, gsi_fc_outer_function_name_in_g2;
{
    Object function_name_in_g2, local_function;

    x_note_fn_call(50,7);
    function_name_in_g2 =  !TRUEP(gsi_fc_outer_function_name_in_g2) ? Nil :
	     g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_function_name_in_g2) 
	    : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_function_name_in_g2));
    local_function = 
	    g2int_lookup_or_create_gsi_local_function(function_name_in_g2,T);
    SVREF(local_function,FIX((SI_Long)1L)) = function;
    SVREF(local_function,FIX((SI_Long)2L)) = user_data;
}

static Object string_constant_1;   /* "gsi_rpc_declare_local_w_u_d" */

/* GSI-RPC-DECLARE-LOCAL-W-U-D */
DLLEXPORT void gsi_rpc_declare_local_w_u_d(function,user_data,
	    function_name_in_g2)
    Object function, user_data, function_name_in_g2;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,8);
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
	    g2int_shared_gsi_rpc_declare_local_w_u_d(G2int_gsi_wide_api_p,
		    function,user_data,function_name_in_g2);
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
		    g2int_shared_gsi_rpc_declare_local_w_u_d(G2int_gsi_wide_api_p,
			    function,user_data,function_name_in_g2);
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

/* GSI-ADD-NEW-REMOTE-PROCEDURE */
Object g2int_gsi_add_new_remote_procedure(remote_function_name,
	    receiver_function,error_receiver_function,user_data,
	    argument_count,return_count,gsi_extension_data_qm)
    Object remote_function_name, receiver_function, error_receiver_function;
    Object user_data, argument_count, return_count, gsi_extension_data_qm;
{
    Object remote_procedure, ab_loop_list_, gsi_remote_procedure;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(50,9);
    remote_procedure = Nil;
    ab_loop_list_ = ISVREF(gsi_extension_data_qm,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    remote_procedure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(remote_procedure,(SI_Long)1L),remote_function_name)) {
	gsi_remote_procedure = remote_procedure;
	goto end;
    }
    goto next_loop;
  end_loop:
    gsi_remote_procedure = Qnil;
  end:;
    if (gsi_remote_procedure);
    else {
	remote_procedure = g2int_make_gsi_remote_procedure_1();
	gensym_push_modify_macro_arg = remote_procedure;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(gsi_extension_data_qm,(SI_Long)4L);
	svref_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	SVREF(gsi_extension_data_qm,FIX((SI_Long)4L)) = svref_new_value;
	gsi_remote_procedure = remote_procedure;
    }
    SVREF(gsi_remote_procedure,FIX((SI_Long)1L)) = remote_function_name;
    SVREF(gsi_remote_procedure,FIX((SI_Long)3L)) = receiver_function;
    SVREF(gsi_remote_procedure,FIX((SI_Long)4L)) = error_receiver_function;
    SVREF(gsi_remote_procedure,FIX((SI_Long)5L)) = user_data;
    SVREF(gsi_remote_procedure,FIX((SI_Long)6L)) = argument_count;
    SVREF(gsi_remote_procedure,FIX((SI_Long)7L)) = return_count;
    return VALUES_1(gsi_remote_procedure);
}

static Object Qg2int_gsi_rpc_declare_remote_plain;  /* |gsi_rpc_declare_remote_plain| */

/* SHARED-GSI-RPC-DECLARE-REMOTE-PLAIN */
void g2int_shared_gsi_rpc_declare_remote_plain(wide_api_p,
	    local_handle_result,gsi_fc_outer_remote_function_name,
	    receiver_function,gsi_fc_outer_argument_count,
	    gsi_fc_outer_return_count,gsi_fc_outer_context)
    Object wide_api_p, local_handle_result, gsi_fc_outer_remote_function_name;
    Object receiver_function;
    SI_Long gsi_fc_outer_argument_count, gsi_fc_outer_return_count;
    SI_Long gsi_fc_outer_context;
{
    Object remote_function_name, argument_count, return_count, context, code;
    Object temp, gsi_remote_procedure;
    SI_Long value;

    x_note_fn_call(50,10);
    remote_function_name =  !TRUEP(gsi_fc_outer_remote_function_name) ? 
	    Nil : g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_remote_function_name) 
	    : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_remote_function_name));
    value = gsi_fc_outer_argument_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    argument_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_return_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    return_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    context = LONG_TO_FIXNUM(value);
    code = g2int_invalid_gsi_context_p(context,Nil);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    temp = ISVREF(g2int_get_icp_socket_from_context(context,Nil),(SI_Long)29L);
    if (temp);
    else {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_malformed_socket,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_plain,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_plain;
    }
    gsi_remote_procedure = 
	    g2int_gsi_add_new_remote_procedure(remote_function_name,
	    receiver_function,Nil,Nil,argument_count,return_count,temp);
    inline_assign_value_to_c_pointer(local_handle_result,gsi_remote_procedure);
  end_shared_gsi_rpc_declare_remote_plain:;
}

static Object string_constant_2;   /* "gsi_rpc_declare_remote_plain" */

/* GSI-RPC-DECLARE-REMOTE-PLAIN */
DLLEXPORT void gsi_rpc_declare_remote_plain(local_handle_result,
	    remote_function_name,receiver_function,argument_count,
	    return_count,context)
    Object local_handle_result, remote_function_name, receiver_function;
    SI_Long argument_count, return_count, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,11);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_2);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_rpc_declare_remote_plain(G2int_gsi_wide_api_p,
		    local_handle_result,remote_function_name,
		    receiver_function,argument_count,return_count,context);
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
		    g2int_shared_gsi_rpc_declare_remote_plain(G2int_gsi_wide_api_p,
			    local_handle_result,remote_function_name,
			    receiver_function,argument_count,return_count,
			    context);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_2);
}

static Object Qg2int_gsi_rpc_declare_remote_w_u_d;  /* |gsi_rpc_declare_remote_w_u_d| */

/* SHARED-GSI-RPC-DECLARE-REMOTE-W-U-D */
void g2int_shared_gsi_rpc_declare_remote_w_u_d(wide_api_p,
	    local_handle_result,gsi_fc_outer_remote_function_name,
	    receiver_function,user_data,gsi_fc_outer_argument_count,
	    gsi_fc_outer_return_count,gsi_fc_outer_context)
    Object wide_api_p, local_handle_result, gsi_fc_outer_remote_function_name;
    Object receiver_function, user_data;
    SI_Long gsi_fc_outer_argument_count, gsi_fc_outer_return_count;
    SI_Long gsi_fc_outer_context;
{
    Object remote_function_name, argument_count, return_count, context, code;
    Object temp, gsi_remote_procedure;
    SI_Long value;

    x_note_fn_call(50,12);
    remote_function_name =  !TRUEP(gsi_fc_outer_remote_function_name) ? 
	    Nil : g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_remote_function_name) 
	    : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_remote_function_name));
    value = gsi_fc_outer_argument_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    argument_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_return_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    return_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    context = LONG_TO_FIXNUM(value);
    code = g2int_invalid_gsi_context_p(context,Nil);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    temp = ISVREF(g2int_get_icp_socket_from_context(context,Nil),(SI_Long)29L);
    if (temp);
    else {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_malformed_socket,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_u_d,Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_u_d;
    }
    gsi_remote_procedure = 
	    g2int_gsi_add_new_remote_procedure(remote_function_name,
	    receiver_function,Nil,user_data,argument_count,return_count,temp);
    inline_assign_value_to_c_pointer(local_handle_result,gsi_remote_procedure);
  end_shared_gsi_rpc_declare_remote_w_u_d:;
}

static Object string_constant_3;   /* "gsi_rpc_declare_remote_w_u_d" */

/* GSI-RPC-DECLARE-REMOTE-W-U-D */
DLLEXPORT void gsi_rpc_declare_remote_w_u_d(local_handle_result,
	    remote_function_name,receiver_function,user_data,
	    argument_count,return_count,context)
    Object local_handle_result, remote_function_name, receiver_function;
    Object user_data;
    SI_Long argument_count, return_count, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,13);
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
	    g2int_shared_gsi_rpc_declare_remote_w_u_d(G2int_gsi_wide_api_p,
		    local_handle_result,remote_function_name,
		    receiver_function,user_data,argument_count,
		    return_count,context);
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
		    g2int_shared_gsi_rpc_declare_remote_w_u_d(G2int_gsi_wide_api_p,
			    local_handle_result,remote_function_name,
			    receiver_function,user_data,argument_count,
			    return_count,context);
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

static Object Qg2int_gsi_rpc_declare_remote_w_e_u_d;  /* |gsi_rpc_declare_remote_w_e_u_d| */

/* SHARED-GSI-RPC-DECLARE-REMOTE-W-E-U-D */
void g2int_shared_gsi_rpc_declare_remote_w_e_u_d(wide_api_p,
	    local_handle_result,gsi_fc_outer_remote_function_name,
	    receiver_function,error_receiver_function,user_data,
	    gsi_fc_outer_argument_count,gsi_fc_outer_return_count,
	    gsi_fc_outer_context)
    Object wide_api_p, local_handle_result, gsi_fc_outer_remote_function_name;
    Object receiver_function, error_receiver_function, user_data;
    SI_Long gsi_fc_outer_argument_count, gsi_fc_outer_return_count;
    SI_Long gsi_fc_outer_context;
{
    Object remote_function_name, argument_count, return_count, context, code;
    Object temp, gsi_remote_procedure;
    SI_Long value;

    x_note_fn_call(50,14);
    remote_function_name =  !TRUEP(gsi_fc_outer_remote_function_name) ? 
	    Nil : g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_remote_function_name) 
	    : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_remote_function_name));
    value = gsi_fc_outer_argument_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    argument_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_return_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    return_count = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    context = LONG_TO_FIXNUM(value);
    code = g2int_invalid_gsi_context_p(context,Nil);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    temp = ISVREF(g2int_get_icp_socket_from_context(context,Nil),(SI_Long)29L);
    if (temp);
    else {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_malformed_socket,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_declare_remote_w_e_u_d,
		Qerror,T);
	goto end_shared_gsi_rpc_declare_remote_w_e_u_d;
    }
    gsi_remote_procedure = 
	    g2int_gsi_add_new_remote_procedure(remote_function_name,
	    receiver_function,error_receiver_function,user_data,
	    argument_count,return_count,temp);
    inline_assign_value_to_c_pointer(local_handle_result,gsi_remote_procedure);
  end_shared_gsi_rpc_declare_remote_w_e_u_d:;
}

static Object string_constant_4;   /* "gsi_rpc_declare_remote_w_e_u_d" */

/* GSI-RPC-DECLARE-REMOTE-W-E-U-D */
DLLEXPORT void gsi_rpc_declare_remote_w_e_u_d(local_handle_result,
	    remote_function_name,receiver_function,error_receiver_function,
	    user_data,argument_count,return_count,context)
    Object local_handle_result, remote_function_name, receiver_function;
    Object error_receiver_function, user_data;
    SI_Long argument_count, return_count, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,15);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_4);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_rpc_declare_remote_w_e_u_d(G2int_gsi_wide_api_p,
		    local_handle_result,remote_function_name,
		    receiver_function,error_receiver_function,user_data,
		    argument_count,return_count,context);
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
		    g2int_shared_gsi_rpc_declare_remote_w_e_u_d(G2int_gsi_wide_api_p,
			    local_handle_result,remote_function_name,
			    receiver_function,error_receiver_function,
			    user_data,argument_count,return_count,context);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_4);
}

static Object Qg2int_gsi_set_rpc_remote_return_v_k;  /* |gsi_set_rpc_remote_return_v_k| */

static Object Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;  /* g2-defstruct-structure-name::gsi-remote-procedure-g2-struct */

static Object Qg2int_by_copy_with_handle;  /* by-copy-with-handle */

static Object Qg2int_handle;       /* handle */

static Object Qg2int_reference;    /* reference */

static Object Qg2int_copy;         /* copy */

static Object Qg2int_value;        /* value */

/* SHARED-GSI-SET-RPC-REMOTE-RETURN-V-K */
void g2int_shared_gsi_set_rpc_remote_return_v_k(wide_api_p,local_handle,
	    gsi_fc_outer_return_value_index,gsi_fc_outer_kind)
    Object wide_api_p, local_handle, gsi_fc_outer_kind;
    SI_Long gsi_fc_outer_return_value_index;
{
    Object return_value_index, kind, temp, kind_list, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    SI_Long value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(50,16);
    value = gsi_fc_outer_return_value_index;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_v_k,
		Qerror,T);
	goto end_shared_gsi_set_rpc_remote_return_v_k;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_v_k,
		Qerror,T);
	goto end_shared_gsi_set_rpc_remote_return_v_k;
    }
    return_value_index = LONG_TO_FIXNUM(value);
    kind =  !TRUEP(gsi_fc_outer_kind) ? Nil : 
	    g2int_symbol_for_gsi_string(wide_api_p ? 
	    g2int_c_wide_string_to_text_string(gsi_fc_outer_kind) : 
	    g2int_c_string_to_gensym_string(gsi_fc_outer_kind));
    if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,Nil,
		Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_v_k,
		Qerror,T);
	goto end_shared_gsi_set_rpc_remote_return_v_k;
    }
    if (EQ(kind,Qg2int_by_copy_with_handle));
    else if (EQ(kind,Qg2int_handle));
    else if (EQ(kind,Qg2int_reference));
    else if (EQ(kind,Qg2int_copy))
	kind = Nil;
    else if (EQ(kind,Qg2int_value))
	kind = Nil;
    else {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_invalid_return_value_kind,Nil,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_v_k,
		Qerror,T);
	goto end_shared_gsi_set_rpc_remote_return_v_k;
    }
    if (IFIX(return_value_index) == (SI_Long)-1L && 
	    IFIX(ISVREF(local_handle,(SI_Long)7L)) == (SI_Long)-1L) {
	temp = g2int_gensym_cons_1(kind,Nil);
	SVREF(local_handle,FIX((SI_Long)8L)) = temp;
    }
    else if (IFIX(return_value_index) < (SI_Long)0L || 
	    FIXNUM_GE(return_value_index,ISVREF(local_handle,(SI_Long)7L))) {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_invalid_return_value_index,Nil,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_v_k,
		Qerror,T);
	goto end_shared_gsi_set_rpc_remote_return_v_k;
    }
    else {
	kind_list = ISVREF(local_handle,(SI_Long)8L);
	if (kind_list);
	else {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(ISVREF(local_handle,(SI_Long)7L));
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    ab_loopvar__2 = g2int_gensym_cons_1(Nil,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    goto end;
	    ab_loopvar_ = Qnil;
	  end:;
	    kind_list = SVREF(local_handle,FIX((SI_Long)8L)) = ab_loopvar_;
	}
	temp = nthcdr(return_value_index,kind_list);
	M_CAR(temp) = kind;
    }
  end_shared_gsi_set_rpc_remote_return_v_k:;
}

static Object string_constant_5;   /* "gsi_set_rpc_remote_return_v_k" */

/* GSI-SET-RPC-REMOTE-RETURN-V-K */
DLLEXPORT void gsi_set_rpc_remote_return_v_k(local_handle,
	    return_value_index,kind)
    Object local_handle, kind;
    SI_Long return_value_index;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,17);
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
	    g2int_shared_gsi_set_rpc_remote_return_v_k(G2int_gsi_wide_api_p,
		    local_handle,return_value_index,kind);
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
		    g2int_shared_gsi_set_rpc_remote_return_v_k(G2int_gsi_wide_api_p,
			    local_handle,return_value_index,kind);
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

static Object Qg2int_gsi_set_rpc_remote_return_e_u_a;  /* |gsi_set_rpc_remote_return_e_u_a| */

/* SHARED-GSI-SET-RPC-REMOTE-RETURN-E-U-A */
void g2int_shared_gsi_set_rpc_remote_return_e_u_a(local_handle,
	    gsi_fc_outer_attrs)
    Object local_handle, gsi_fc_outer_attrs;
{
    Object attrs, magic_number, exclude_user_attrs, item, type, value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(50,18);
    if ( !TRUEP(gsi_fc_outer_attrs))
	attrs = Nil;
    else {
	magic_number = inline_gsi_get_magic_header(gsi_fc_outer_attrs);
	if (IFIX(magic_number) == (SI_Long)5472500L)
	    attrs = inline_get_array_from_c(gsi_fc_outer_attrs,
		    G2int_gsi_magic_offset);
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_bad_magic_number,
		    Nil,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_e_u_a,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_return_e_u_a;
	}
    }
    exclude_user_attrs = Nil;
    if (attrs) {
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(g2int_gsi_managed_array_length(attrs));
	item = Nil;
	type = Nil;
	value = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	item = ISVREF(attrs,i);
	type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	value = ISVREF(item,(SI_Long)2L);
	if (FIXNUM_EQ(type,G2int_gsi_symbol_type_tag))
	    exclude_user_attrs = g2int_gensym_cons_1(value,exclude_user_attrs);
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_incompatible_type,
		    type,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_e_u_a,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_return_e_u_a;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    SVREF(local_handle,FIX((SI_Long)9L)) = exclude_user_attrs;
  end_shared_gsi_set_rpc_remote_return_e_u_a:;
}

static Object string_constant_6;   /* "gsi_set_rpc_remote_return_e_u_a" */

/* GSI-SET-RPC-REMOTE-RETURN-E-U-A */
DLLEXPORT void gsi_set_rpc_remote_return_e_u_a(local_handle,attrs)
    Object local_handle, attrs;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,19);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_6);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_set_rpc_remote_return_e_u_a(local_handle,attrs);
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
		    g2int_shared_gsi_set_rpc_remote_return_e_u_a(local_handle,
			    attrs);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_6);
}

static Object Qg2int_gsi_set_rpc_remote_return_i_s_a;  /* |gsi_set_rpc_remote_return_i_s_a| */

/* SHARED-GSI-SET-RPC-REMOTE-RETURN-I-S-A */
void g2int_shared_gsi_set_rpc_remote_return_i_s_a(local_handle,
	    gsi_fc_outer_attrs)
    Object local_handle, gsi_fc_outer_attrs;
{
    Object attrs, magic_number, include_system_attrs, item, type, value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(50,20);
    if ( !TRUEP(gsi_fc_outer_attrs))
	attrs = Nil;
    else {
	magic_number = inline_gsi_get_magic_header(gsi_fc_outer_attrs);
	if (IFIX(magic_number) == (SI_Long)5472500L)
	    attrs = inline_get_array_from_c(gsi_fc_outer_attrs,
		    G2int_gsi_magic_offset);
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_bad_magic_number,
		    Nil,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_i_s_a,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_return_i_s_a;
	}
    }
    include_system_attrs = Nil;
    if (attrs) {
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(g2int_gsi_managed_array_length(attrs));
	item = Nil;
	type = Nil;
	value = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	item = ISVREF(attrs,i);
	type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	value = ISVREF(item,(SI_Long)2L);
	if (FIXNUM_EQ(type,G2int_gsi_symbol_type_tag))
	    include_system_attrs = g2int_gensym_cons_1(value,
		    include_system_attrs);
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_incompatible_type,
		    type,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_return_i_s_a,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_return_i_s_a;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    SVREF(local_handle,FIX((SI_Long)10L)) = include_system_attrs;
  end_shared_gsi_set_rpc_remote_return_i_s_a:;
}

static Object string_constant_7;   /* "gsi_set_rpc_remote_return_i_s_a" */

/* GSI-SET-RPC-REMOTE-RETURN-I-S-A */
DLLEXPORT void gsi_set_rpc_remote_return_i_s_a(local_handle,attrs)
    Object local_handle, attrs;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,21);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_7);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_set_rpc_remote_return_i_s_a(local_handle,attrs);
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
		    g2int_shared_gsi_set_rpc_remote_return_i_s_a(local_handle,
			    attrs);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_7);
}

static Object Qg2int_gsi_set_rpc_remote_r_i_a_s_a_e;  /* |gsi_set_rpc_remote_r_i_a_s_a_e| */

/* SHARED-GSI-SET-RPC-REMOTE-R-I-A-S-A-E */
void g2int_shared_gsi_set_rpc_remote_r_i_a_s_a_e(local_handle,
	    gsi_fc_outer_attrs)
    Object local_handle, gsi_fc_outer_attrs;
{
    Object attrs, magic_number, include_system_attrs_except;
    Object include_system_attrs, item, type, value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(50,22);
    if ( !TRUEP(gsi_fc_outer_attrs))
	attrs = Nil;
    else {
	magic_number = inline_gsi_get_magic_header(gsi_fc_outer_attrs);
	if (IFIX(magic_number) == (SI_Long)5472500L)
	    attrs = inline_get_array_from_c(gsi_fc_outer_attrs,
		    G2int_gsi_magic_offset);
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_bad_magic_number,
		    Nil,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_r_i_a_s_a_e,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_r_i_a_s_a_e;
	}
    }
    include_system_attrs_except = Nil;
    include_system_attrs = Nil;
    if (attrs) {
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(g2int_gsi_managed_array_length(attrs));
	item = Nil;
	type = Nil;
	value = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	item = ISVREF(attrs,i);
	type = FIX(IFIX(ISVREF(item,(SI_Long)1L)) >>  -  - (SI_Long)3L);
	value = ISVREF(item,(SI_Long)2L);
	if (FIXNUM_EQ(type,G2int_gsi_symbol_type_tag)) {
	    include_system_attrs_except = g2int_gensym_cons_1(value,
		    include_system_attrs_except);
	    include_system_attrs = g2int_gensym_cons_1(value,
		    include_system_attrs);
	}
	else {
	    g2int_set_gsi_error_message_1(Nil,G2int_gsi_incompatible_type,
		    type,Nil,Nil,Nil,Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_set_rpc_remote_r_i_a_s_a_e,
		    Qerror,T);
	    goto end_shared_gsi_set_rpc_remote_r_i_a_s_a_e;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    SVREF(local_handle,FIX((SI_Long)12L)) = include_system_attrs_except;
    SVREF(local_handle,FIX((SI_Long)11L)) = include_system_attrs;
  end_shared_gsi_set_rpc_remote_r_i_a_s_a_e:;
}

static Object string_constant_8;   /* "gsi_set_rpc_remote_r_i_a_s_a_e" */

/* GSI-SET-RPC-REMOTE-R-I-A-S-A-E */
DLLEXPORT void gsi_set_rpc_remote_r_i_a_s_a_e(local_handle,attrs)
    Object local_handle, attrs;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,23);
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
	    g2int_shared_gsi_set_rpc_remote_r_i_a_s_a_e(local_handle,attrs);
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
		    g2int_shared_gsi_set_rpc_remote_r_i_a_s_a_e(local_handle,
			    attrs);
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

static Object Qg2int_send_icp_resumable_rpc_start;  /* send-icp-resumable-rpc-start */

/* GSI-RPC-START-INTERNAL */
Object g2int_gsi_rpc_start_internal(local_handle,argument_array,context)
    Object local_handle, argument_array, context;
{
    Object remote_procedure_name, derived_socket, temp, temp_1;
    Object current_icp_port, current_icp_socket, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    Object use_new_message_group_for_send_icp_enlarge_index_space_p;
    double gensymed_symbol_1;
    Declare_special(13);

    x_note_fn_call(50,24);
    remote_procedure_name = ISVREF(local_handle,(SI_Long)2L);
    if (remote_procedure_name);
    else
	remote_procedure_name = 
		g2int_gsi_define_new_remote_procedure(local_handle);
    derived_socket = g2int_get_icp_socket_from_context(context,T);
    temp = ISVREF(derived_socket,(SI_Long)21L);
    temp_1 = ISVREF(derived_socket,(SI_Long)22L);
    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L)
	g2int_send_or_enqueue_icp_write_task(ISVREF(derived_socket,
		(SI_Long)4L),G2int_resumable_priority_of_gsi_rpc_service,
		SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_start),
		g2int_gensym_list_2(remote_procedure_name,argument_array),
		Nil,Nil);
    else {
	current_icp_port = ISVREF(derived_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,12);
	  current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,11);
	    temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		    (SI_Long)53L) : Nil;
	    if (temp);
	    else
		temp = Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,10);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      9);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			8);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			  7);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			    6);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      5);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				4);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				  3);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    2);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(G2int_writing_icp_message_group);
			      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				      1);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					&&  
					!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					    {
				    use_new_message_group_for_send_icp_enlarge_index_space_p 
					    = Nil;
				    PUSH_SPECIAL(G2int_use_new_message_group_for_send_icp_enlarge_index_space_p,use_new_message_group_for_send_icp_enlarge_index_space_p,
					    0);
				      g2int_establish_new_object_indices_as_required(argument_array);
				      g2int_send_icp_rpc_start(remote_procedure_name,
					      argument_array);
				    POP_SPECIAL();
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
	g2int_flush_outgoing_item_list(derived_socket);
    }
    g2int_gsi_flush_internal_1(derived_socket,Nil);
    return VALUES_1(Nil);
}

/* BUILD-PROCEDURE-IDENTIFIER-ICP-LIST */
Object g2int_build_procedure_identifier_icp_list(list_1,varargs_p)
    Object list_1, varargs_p;
{
    Object result_1;

    x_note_fn_call(50,25);
    result_1 = list_1 ? g2int_copy_tree_using_gensym_conses_1(list_1) : Nil;
    if (varargs_p || CONSP(list_1))
	return g2int_gensym_cons_1(result_1,Nil);
    else
	return VALUES_1(result_1);
}

static Object Qg2int_send_icp_resumable_rpc_call;  /* send-icp-resumable-rpc-call */

/* GSI-RPC-CALL-INTERNAL */
Object g2int_gsi_rpc_call_internal(local_handle,argument_array,context,
	    user_data,user_data_p)
    Object local_handle, argument_array, context, user_data, user_data_p;
{
    Object remote_procedure_name, kind_list, incl, excl, incl_sys;
    Object incl_all_sys, incl_all_sys_except, remote_procedure_identifier;
    Object derived_socket, temp, temp_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    Object use_new_message_group_for_send_icp_enlarge_index_space_p;
    char varargs_p;
    double gensymed_symbol_1;
    Declare_special(13);

    x_note_fn_call(50,26);
    remote_procedure_name = ISVREF(local_handle,(SI_Long)2L);
    if (remote_procedure_name);
    else
	remote_procedure_name = 
		g2int_gsi_define_new_remote_procedure(local_handle);
    kind_list = ISVREF(local_handle,(SI_Long)8L);
    varargs_p = IFIX(ISVREF(local_handle,(SI_Long)7L)) == (SI_Long)-1L;
    incl = varargs_p ? g2int_gensym_cons_1(Nil,Nil) : Nil;
    excl = g2int_build_procedure_identifier_icp_list(ISVREF(local_handle,
	    (SI_Long)9L),varargs_p ? T : Nil);
    incl_sys = 
	    g2int_build_procedure_identifier_icp_list(ISVREF(local_handle,
	    (SI_Long)10L),varargs_p ? T : Nil);
    incl_all_sys = 
	    g2int_build_procedure_identifier_icp_list(ISVREF(local_handle,
	    (SI_Long)11L),varargs_p ? T : Nil);
    incl_all_sys_except = 
	    g2int_build_procedure_identifier_icp_list(ISVREF(local_handle,
	    (SI_Long)12L),varargs_p ? T : Nil);
    remote_procedure_identifier = 
	    g2int_make_outgoing_remote_procedure_identifier_with_info(incl,
	    excl,incl_sys,incl_all_sys,incl_all_sys_except,kind_list,
	    varargs_p ? T : Nil);
    derived_socket = g2int_get_icp_socket_from_context(context,T);
    user_data = user_data_p ? user_data : 
	    inline_get_long_from_fixnum(ISVREF(remote_procedure_identifier,
	    (SI_Long)1L));
    if (incl)
	g2int_reclaim_gensym_tree_1(incl);
    if (excl)
	g2int_reclaim_gensym_tree_1(excl);
    if (incl_sys)
	g2int_reclaim_gensym_tree_1(incl_sys);
    if (incl_all_sys)
	g2int_reclaim_gensym_tree_1(incl_all_sys);
    if (incl_all_sys_except)
	g2int_reclaim_gensym_tree_1(incl_all_sys_except);
    SVREF(remote_procedure_identifier,FIX((SI_Long)3L)) = local_handle;
    SVREF(remote_procedure_identifier,FIX((SI_Long)7L)) = user_data;
    temp = ISVREF(derived_socket,(SI_Long)21L);
    temp_1 = ISVREF(derived_socket,(SI_Long)22L);
    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L)
	g2int_send_or_enqueue_icp_write_task(ISVREF(derived_socket,
		(SI_Long)4L),G2int_resumable_priority_of_gsi_rpc_service,
		SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_call),
		g2int_gensym_list_3(remote_procedure_name,
		remote_procedure_identifier,argument_array),Nil,Nil);
    else {
	current_icp_port = ISVREF(derived_socket,(SI_Long)4L);
	PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,12);
	  current_icp_socket = ISVREF(G2int_current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,11);
	    temp = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(G2int_current_icp_socket,
		    (SI_Long)53L) : Nil;
	    if (temp);
	    else
		temp = Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,10);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      9);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
			8);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
			  7);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
			    6);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      5);
			current_icp_buffer = Nil;
			PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
				4);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
				  3);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    2);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(G2int_writing_icp_message_group);
			      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
				      1);
				gensymed_symbol = Nil;
				gensymed_symbol_1 = 0.0;
				gensymed_symbol_1 = 0.0;
				if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					&&  
					!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					    {
				    use_new_message_group_for_send_icp_enlarge_index_space_p 
					    = Nil;
				    PUSH_SPECIAL(G2int_use_new_message_group_for_send_icp_enlarge_index_space_p,use_new_message_group_for_send_icp_enlarge_index_space_p,
					    0);
				      g2int_establish_new_object_indices_as_required(argument_array);
				      g2int_send_icp_rpc_call(remote_procedure_name,
					      remote_procedure_identifier,
					      argument_array);
				    POP_SPECIAL();
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
	g2int_flush_outgoing_item_list(derived_socket);
    }
    g2int_gsi_flush_internal_1(derived_socket,Nil);
    return VALUES_1(user_data);
}

static Object Qg2int_gsi_rpc_start;  /* |gsi_rpc_start| */

/* SHARED-GSI-RPC-START */
void g2int_shared_gsi_rpc_start(local_handle,gsi_fc_outer_argument_array,
	    gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array;
    SI_Long gsi_fc_outer_context;
{
    Object context, argument_array, code;
    SI_Long value;

    x_note_fn_call(50,27);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start,Qerror,T);
	goto end_shared_gsi_rpc_start;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start,Qerror,T);
	goto end_shared_gsi_rpc_start;
    }
    context = LONG_TO_FIXNUM(value);
    if (gsi_fc_outer_argument_array) {
	if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) 
		    {
	    g2int_set_gsi_error_message_1(Nil,
		    G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,
		    Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start,Qerror,T);
	    goto end_shared_gsi_rpc_start;
	}
	argument_array = 
		g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
		ISVREF(local_handle,(SI_Long)6L));
    }
    else
	argument_array = Nil;
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_start;
    }
    g2int_gsi_rpc_start_internal(local_handle,argument_array,context);
    g2int_gsi_reclaim_displaced_array(argument_array);
  end_shared_gsi_rpc_start:;
}

static Object string_constant_9;   /* "gsi_rpc_start" */

/* GSI-RPC-START */
DLLEXPORT void gsi_rpc_start(local_handle,argument_array,context)
    Object local_handle, argument_array;
    SI_Long context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,28);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_9);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_rpc_start(local_handle,argument_array,context);
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
		    g2int_shared_gsi_rpc_start(local_handle,argument_array,
			    context);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_9);
}

static Object Qg2int_gsi_rpc_start_with_count;  /* |gsi_rpc_start_with_count| */

/* SHARED-GSI-RPC-START-WITH-COUNT */
void g2int_shared_gsi_rpc_start_with_count(local_handle,
	    gsi_fc_outer_argument_array,gsi_fc_outer_count,
	    gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array;
    SI_Long gsi_fc_outer_count, gsi_fc_outer_context;
{
    Object count_1, context, argument_array, code;
    SI_Long value;

    x_note_fn_call(50,29);
    value = gsi_fc_outer_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	goto end_shared_gsi_rpc_start_with_count;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	goto end_shared_gsi_rpc_start_with_count;
    }
    count_1 = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	goto end_shared_gsi_rpc_start_with_count;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	goto end_shared_gsi_rpc_start_with_count;
    }
    context = LONG_TO_FIXNUM(value);
    argument_array = gsi_fc_outer_argument_array ? 
	    g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
	    count_1) : Nil;
    if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,Nil,
		Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_start_with_count;
    }
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_start_with_count,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_start_with_count;
    }
    g2int_gsi_rpc_start_internal(local_handle,argument_array,context);
    g2int_gsi_reclaim_displaced_array(argument_array);
  end_shared_gsi_rpc_start_with_count:;
}

static Object string_constant_10;  /* "gsi_rpc_start_with_count" */

/* GSI-RPC-START-WITH-COUNT */
DLLEXPORT void gsi_rpc_start_with_count(local_handle,argument_array,
	    count_1,context)
    Object local_handle, argument_array;
    SI_Long count_1, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,30);
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
	    g2int_shared_gsi_rpc_start_with_count(local_handle,
		    argument_array,count_1,context);
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
		    g2int_shared_gsi_rpc_start_with_count(local_handle,
			    argument_array,count_1,context);
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

static Object Qg2int_gsi_rpc_call;  /* |gsi_rpc_call| */

/* SHARED-GSI-RPC-CALL */
Object g2int_shared_gsi_rpc_call(local_handle,gsi_fc_outer_argument_array,
	    gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array;
    SI_Long gsi_fc_outer_context;
{
    Object result_1, context, argument_array, code, gsi_fc_result;
    SI_Long value;

    x_note_fn_call(50,31);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call;
    }
    context = LONG_TO_FIXNUM(value);
    if (gsi_fc_outer_argument_array) {
	if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) 
		    {
	    g2int_set_gsi_error_message_1(Nil,
		    G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,
		    Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call,Qerror,T);
	    result_1 = Qnil;
	    goto end_shared_gsi_rpc_call;
	}
	argument_array = 
		g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
		ISVREF(local_handle,(SI_Long)6L));
    }
    else
	argument_array = Nil;
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call;
    }
    gsi_fc_result = g2int_gsi_rpc_call_internal(local_handle,
	    argument_array,context,Nil,Nil);
    g2int_gsi_reclaim_displaced_array(argument_array);
    result_1 = gsi_fc_result;
  end_shared_gsi_rpc_call:;
    return result_1;
}

static Object string_constant_11;  /* "gsi_rpc_call" */

/* GSI-RPC-CALL */
DLLEXPORT Object gsi_rpc_call(local_handle,argument_array,context)
    Object local_handle, argument_array;
    SI_Long context;
{
    volatile Object result_1;
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Object result_2;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,32);
    result_1 = Nil;
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_11);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    result_1 = g2int_shared_gsi_rpc_call(local_handle,
		    argument_array,context);
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
		    result_1 = g2int_shared_gsi_rpc_call(local_handle,
			    argument_array,context);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_11);
    result_2 = result_1;
    return result_2;
}

static Object Qg2int_gsi_rpc_call_with_count;  /* |gsi_rpc_call_with_count| */

/* SHARED-GSI-RPC-CALL-WITH-COUNT */
Object g2int_shared_gsi_rpc_call_with_count(local_handle,
	    gsi_fc_outer_argument_array,gsi_fc_outer_count,
	    gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array;
    SI_Long gsi_fc_outer_count, gsi_fc_outer_context;
{
    Object result_1, count_1, context, argument_array, code, gsi_fc_result;
    SI_Long value;

    x_note_fn_call(50,33);
    value = gsi_fc_outer_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    count_1 = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    context = LONG_TO_FIXNUM(value);
    argument_array = gsi_fc_outer_argument_array ? 
	    g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
	    count_1) : Nil;
    if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,Nil,
		Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count;
    }
    gsi_fc_result = g2int_gsi_rpc_call_internal(local_handle,
	    argument_array,context,Nil,Nil);
    g2int_gsi_reclaim_displaced_array(argument_array);
    result_1 = gsi_fc_result;
  end_shared_gsi_rpc_call_with_count:;
    return result_1;
}

static Object string_constant_12;  /* "gsi_rpc_call_with_count" */

/* GSI-RPC-CALL-WITH-COUNT */
DLLEXPORT Object gsi_rpc_call_with_count(local_handle,argument_array,
	    count_1,context)
    Object local_handle, argument_array;
    SI_Long count_1, context;
{
    volatile Object result_1;
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Object result_2;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,34);
    result_1 = Nil;
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
	    result_1 = g2int_shared_gsi_rpc_call_with_count(local_handle,
		    argument_array,count_1,context);
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
		    result_1 = 
			    g2int_shared_gsi_rpc_call_with_count(local_handle,
			    argument_array,count_1,context);
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
    result_2 = result_1;
    return result_2;
}

static Object Qg2int_gsi_rpc_call_with_u_d;  /* |gsi_rpc_call_with_u_d| */

/* SHARED-GSI-RPC-CALL-WITH-U-D */
Object g2int_shared_gsi_rpc_call_with_u_d(local_handle,
	    gsi_fc_outer_argument_array,user_data,gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array, user_data;
    SI_Long gsi_fc_outer_context;
{
    Object result_1, context, argument_array, code, gsi_fc_result;
    SI_Long value;

    x_note_fn_call(50,35);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_u_d;
    }
    context = LONG_TO_FIXNUM(value);
    if (gsi_fc_outer_argument_array) {
	if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) 
		    {
	    g2int_set_gsi_error_message_1(Nil,
		    G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,
		    Nil,Nil);
	    g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_u_d,Qerror,T);
	    result_1 = Qnil;
	    goto end_shared_gsi_rpc_call_with_u_d;
	}
	argument_array = 
		g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
		ISVREF(local_handle,(SI_Long)6L));
    }
    else
	argument_array = Nil;
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_u_d,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_u_d;
    }
    gsi_fc_result = g2int_gsi_rpc_call_internal(local_handle,
	    argument_array,context,user_data,T);
    g2int_gsi_reclaim_displaced_array(argument_array);
    result_1 = gsi_fc_result;
  end_shared_gsi_rpc_call_with_u_d:;
    return result_1;
}

static Object string_constant_13;  /* "gsi_rpc_call_with_u_d" */

/* GSI-RPC-CALL-WITH-U-D */
DLLEXPORT Object gsi_rpc_call_with_u_d(local_handle,argument_array,
	    user_data,context)
    Object local_handle, argument_array, user_data;
    SI_Long context;
{
    volatile Object result_1;
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Object result_2;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,36);
    result_1 = Nil;
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
	    result_1 = g2int_shared_gsi_rpc_call_with_u_d(local_handle,
		    argument_array,user_data,context);
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
		    result_1 = 
			    g2int_shared_gsi_rpc_call_with_u_d(local_handle,
			    argument_array,user_data,context);
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
    result_2 = result_1;
    return result_2;
}

static Object Qg2int_gsi_rpc_call_with_count_u_d;  /* |gsi_rpc_call_with_count_u_d| */

/* SHARED-GSI-RPC-CALL-WITH-COUNT-U-D */
Object g2int_shared_gsi_rpc_call_with_count_u_d(local_handle,
	    gsi_fc_outer_argument_array,gsi_fc_outer_count,user_data,
	    gsi_fc_outer_context)
    Object local_handle, gsi_fc_outer_argument_array, user_data;
    SI_Long gsi_fc_outer_count, gsi_fc_outer_context;
{
    Object result_1, count_1, context, argument_array, code, gsi_fc_result;
    SI_Long value;

    x_note_fn_call(50,37);
    value = gsi_fc_outer_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    count_1 = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    context = LONG_TO_FIXNUM(value);
    argument_array = gsi_fc_outer_argument_array ? 
	    g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
	    count_1) : Nil;
    if ( !(SIMPLE_VECTOR_P(local_handle) && EQ(ISVREF(local_handle,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct))) {
	g2int_set_gsi_error_message_1(Nil,
		G2int_gsi_remote_declaration_not_found,Nil,Nil,Nil,Nil,Nil,
		Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_call_with_count_u_d,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	result_1 = Qnil;
	goto end_shared_gsi_rpc_call_with_count_u_d;
    }
    gsi_fc_result = g2int_gsi_rpc_call_internal(local_handle,
	    argument_array,context,user_data,T);
    g2int_gsi_reclaim_displaced_array(argument_array);
    result_1 = gsi_fc_result;
  end_shared_gsi_rpc_call_with_count_u_d:;
    return result_1;
}

static Object string_constant_14;  /* "gsi_rpc_call_with_count_u_d" */

/* GSI-RPC-CALL-WITH-COUNT-U-D */
DLLEXPORT Object gsi_rpc_call_with_count_u_d(local_handle,argument_array,
	    count_1,user_data,context)
    Object local_handle, argument_array, user_data;
    SI_Long count_1, context;
{
    volatile Object result_1;
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Object result_2;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,38);
    result_1 = Nil;
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
	    result_1 = 
		    g2int_shared_gsi_rpc_call_with_count_u_d(local_handle,
		    argument_array,count_1,user_data,context);
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
		    result_1 = 
			    g2int_shared_gsi_rpc_call_with_count_u_d(local_handle,
			    argument_array,count_1,user_data,context);
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
    result_2 = result_1;
    return result_2;
}

static Object Qab_g2int_gsi_rpc_return_values_internal;  /* gsi_rpc_return_values_internal */

static Object Qg2int_error_description;  /* error-description */

static Object Qg2int_outstanding;  /* outstanding */

static Object Qg2int_send_icp_resumable_rpc_error_to_caller;  /* send-icp-resumable-rpc-error-to-caller */

static Object Qg2int_reclaim_if_text_string_function;  /* reclaim-if-text-string-function */

static Object Qg2int_send_icp_resumable_rpc_return_values;  /* send-icp-resumable-rpc-return-values */

static Object Qg2int_returned;     /* returned */

static Object Qg2int_async_abort;  /* async-abort */

/* GSI-RPC-RETURN-VALUES-INTERNAL */
Object g2int_gsi_rpc_return_values_internal(argument_array,
	    remote_procedure_identifier,context,errorp)
    Object argument_array, remote_procedure_identifier, context, errorp;
{
    Object rpid_tag, derived_socket, output_port, error_name, error_level;
    Object error_message, error_message_for_reclaim, error_in_arguments;
    Object gsi_instance_extension, temp, temp_1, gensymed_symbol;
    Object gensymed_symbol_1, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object use_new_message_group_for_send_icp_enlarge_index_space_p;
    double gensymed_symbol_2;
    Declare_special(13);

    x_note_fn_call(50,39);
    rpid_tag = remote_procedure_identifier ? 
	    ISVREF(remote_procedure_identifier,(SI_Long)1L) : FIX((SI_Long)0L);
    derived_socket = g2int_get_icp_socket_from_context(context,T);
    output_port = ISVREF(derived_socket,(SI_Long)4L);
    error_name = Nil;
    error_level = Nil;
    error_message = Nil;
    error_message_for_reclaim = Nil;
    if (errorp) {
	error_in_arguments = 
		g2int_check_gsi_error_argument_list(argument_array);
	if (error_in_arguments)
	    g2int_gsi_error(3,Qab_g2int_gsi_rpc_return_values_internal,
		    G2int_gsi_illegal_error_arguments,error_in_arguments);
	error_level = FIX((SI_Long)1L);
	if ((SI_Long)2L == 
		IFIX(FIXNUM_SUB1(g2int_gsi_managed_array_length(argument_array)))) 
		    {
	    error_name = ISVREF(ISVREF(argument_array,(SI_Long)1L),
		    (SI_Long)2L);
	    error_message = ISVREF(ISVREF(argument_array,(SI_Long)2L),
		    (SI_Long)2L);
	}
	else {
	    gsi_instance_extension = ISVREF(ISVREF(argument_array,
		    (SI_Long)1L),(SI_Long)3L);
	    error_name = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
	    error_message = 
		    ISVREF(g2int_gsi_get_item_of_attribute_named(ISVREF(argument_array,
		    (SI_Long)1L),Qg2int_error_description),(SI_Long)2L);
	}
	if ( !TRUEP(g2int_text_string_p(error_message))) {
	    error_message = g2int_convert_gsi_value_to_value(error_message);
	    error_message_for_reclaim = error_message;
	}
    }
    temp = remote_procedure_identifier ? 
	    ISVREF(remote_procedure_identifier,(SI_Long)6L) : errorp ? 
	    Qg2int_outstanding : Nil;
    if (EQ(temp,Qg2int_outstanding)) {
	if (errorp) {
	    temp = ISVREF(derived_socket,(SI_Long)21L);
	    temp_1 = ISVREF(derived_socket,(SI_Long)22L);
	    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L) {
		temp = G2int_resumable_priority_of_gsi_rpc_service;
		gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)6L));
		gensymed_symbol_1 = gensymed_symbol;
		M_CAR(gensymed_symbol_1) = rpid_tag;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = error_name;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = error_level;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = error_message;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		M_CAR(gensymed_symbol_1) = argument_array;
		g2int_send_or_enqueue_icp_write_task(output_port,temp,
			SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_error_to_caller),
			gensymed_symbol,
			SYMBOL_FUNCTION(Qg2int_reclaim_if_text_string_function),
			g2int_gensym_cons_1(error_message_for_reclaim,Nil));
	    }
	    else {
		current_icp_port = output_port;
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
					gensymed_symbol_2 = 0.0;
					gensymed_symbol_2 = 0.0;
					if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
						&&  
						!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						    {
					    if ((SI_Long)0L < IFIX(rpid_tag))
						g2int_send_icp_rpc_error_to_caller(rpid_tag,
							Nil,error_name,
							error_level,
							error_message,Nil);
					    else
						g2int_send_icp_rpc_error(error_name,
							error_level,
							error_message,Nil);
					    g2int_reclaim_if_text_string_function(error_message_for_reclaim);
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
	else {
	    temp = ISVREF(derived_socket,(SI_Long)21L);
	    temp_1 = ISVREF(derived_socket,(SI_Long)22L);
	    if (IFIX(FIXNUM_MIN(temp,temp_1)) >= (SI_Long)8L)
		g2int_send_or_enqueue_icp_write_task(output_port,
			G2int_resumable_priority_of_gsi_rpc_service,
			SYMBOL_FUNCTION(Qg2int_send_icp_resumable_rpc_return_values),
			g2int_gensym_list_2(rpid_tag,argument_array),Nil,Nil);
	    else {
		current_icp_port = output_port;
		PUSH_SPECIAL(G2int_current_icp_port,current_icp_port,12);
		  current_icp_socket = ISVREF(G2int_current_icp_port,
			  (SI_Long)2L);
		  PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,11);
		    temp = IFIX(ISVREF(G2int_current_icp_socket,
			    (SI_Long)22L)) >= (SI_Long)17L ? 
			    ISVREF(G2int_current_icp_socket,(SI_Long)53L) :
			     Nil;
		    if (temp);
		    else
			temp = Nil;
		    disable_resumability = temp;
		    PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			    10);
		      number_of_icp_bytes_for_message_series = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL(G2int_number_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
			      9);
			icp_buffers_for_message_group = Nil;
			PUSH_SPECIAL(G2int_icp_buffers_for_message_group,icp_buffers_for_message_group,
				8);
			  icp_buffer_of_start_of_message_series_qm = Nil;
			  PUSH_SPECIAL(G2int_icp_buffer_of_start_of_message_seriesqm,icp_buffer_of_start_of_message_series_qm,
				  7);
			    icp_byte_position_of_start_of_message_series_qm 
				    = Nil;
			    PUSH_SPECIAL(G2int_icp_byte_position_of_start_of_message_seriesqm,icp_byte_position_of_start_of_message_series_qm,
				    6);
			      number_of_icp_bytes_to_fill_buffer = 
				      FIX((SI_Long)0L);
			      PUSH_SPECIAL(G2int_number_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
				      5);
				current_icp_buffer = Nil;
				PUSH_SPECIAL(G2int_current_icp_buffer,current_icp_buffer,
					4);
				  current_write_icp_byte_position = Nil;
				  PUSH_SPECIAL(G2int_current_write_icp_byte_position,current_write_icp_byte_position,
					  3);
				    number_of_icp_bytes_in_message_group = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL(G2int_number_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
					    2);
				      writing_icp_message_group = 
					      FIXNUM_ADD1(G2int_writing_icp_message_group);
				      PUSH_SPECIAL(G2int_writing_icp_message_group,writing_icp_message_group,
					      1);
					gensymed_symbol = Nil;
					gensymed_symbol_2 = 0.0;
					gensymed_symbol_2 = 0.0;
					if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
						&&  
						!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
						    {
					    use_new_message_group_for_send_icp_enlarge_index_space_p 
						    = Nil;
					    PUSH_SPECIAL(G2int_use_new_message_group_for_send_icp_enlarge_index_space_p,use_new_message_group_for_send_icp_enlarge_index_space_p,
						    0);
					      g2int_establish_new_object_indices_as_required(argument_array);
					      g2int_send_icp_rpc_return_values(rpid_tag,
						      argument_array);
					    POP_SPECIAL();
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
		g2int_flush_outgoing_item_list(derived_socket);
	    }
	}
	g2int_gsi_flush_internal_1(derived_socket,Nil);
	if (remote_procedure_identifier)
	    SVREF(remote_procedure_identifier,FIX((SI_Long)6L)) = 
		    Qg2int_returned;
    }
    else if (EQ(temp,Qg2int_async_abort)) {
	current_icp_port = output_port;
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
				gensymed_symbol_2 = 0.0;
				gensymed_symbol_2 = 0.0;
				if (g2int_icp_connection_open_p(G2int_current_icp_socket) 
					&&  
					!TRUEP(g2int_icp_connection_being_shutdownqm(G2int_current_icp_socket))) 
					    {
				    g2int_send_icp_rpc_acknowledge_abort(rpid_tag);
				    g2int_gsi_flush_internal_1(derived_socket,
					    Nil);
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
    else
	g2int_gsi_error(2,Qab_g2int_gsi_rpc_return_values_internal,
		G2int_gsi_bad_rpc_state);
    return VALUES_1(Nil);
}

static Object Qg2int_gsi_rpc_return_values;  /* |gsi_rpc_return_values| */

static Object Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-identifier-g2-struct */

/* SHARED-GSI-RPC-RETURN-VALUES */
void g2int_shared_gsi_rpc_return_values(gsi_fc_outer_argument_array,
	    gsi_fc_outer_count,call_handle,gsi_fc_outer_context)
    Object gsi_fc_outer_argument_array, call_handle;
    SI_Long gsi_fc_outer_count, gsi_fc_outer_context;
{
    Object count_1, context, argument_array, code;
    SI_Long value;

    x_note_fn_call(50,40);
    value = gsi_fc_outer_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	goto end_shared_gsi_rpc_return_values;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	goto end_shared_gsi_rpc_return_values;
    }
    count_1 = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	goto end_shared_gsi_rpc_return_values;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	goto end_shared_gsi_rpc_return_values;
    }
    context = LONG_TO_FIXNUM(value);
    argument_array = gsi_fc_outer_argument_array ? 
	    g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
	    count_1) : Nil;
    if ( !(SIMPLE_VECTOR_P(call_handle) && EQ(ISVREF(call_handle,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct))) 
		{
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_invalid_call_handle,
		Nil,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_return_values;
    }
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_values,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_return_values;
    }
    g2int_gsi_rpc_return_values_internal(argument_array,call_handle,
	    context,Nil);
    g2int_gsi_reclaim_displaced_array(argument_array);
  end_shared_gsi_rpc_return_values:;
}

static Object string_constant_15;  /* "gsi_rpc_return_values" */

/* GSI-RPC-RETURN-VALUES */
DLLEXPORT void gsi_rpc_return_values(argument_array,count_1,call_handle,
	    context)
    Object argument_array, call_handle;
    SI_Long count_1, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,41);
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
	    g2int_shared_gsi_rpc_return_values(argument_array,count_1,
		    call_handle,context);
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
		    g2int_shared_gsi_rpc_return_values(argument_array,
			    count_1,call_handle,context);
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

static Object Qg2int_gsi_rpc_return_error_values;  /* |gsi_rpc_return_error_values| */

/* SHARED-GSI-RPC-RETURN-ERROR-VALUES */
void g2int_shared_gsi_rpc_return_error_values(gsi_fc_outer_argument_array,
	    gsi_fc_outer_count,call_handle,gsi_fc_outer_context)
    Object gsi_fc_outer_argument_array, call_handle;
    SI_Long gsi_fc_outer_count, gsi_fc_outer_context;
{
    Object count_1, context, argument_array, code;
    SI_Long value;

    x_note_fn_call(50,42);
    value = gsi_fc_outer_count;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	goto end_shared_gsi_rpc_return_error_values;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	goto end_shared_gsi_rpc_return_error_values;
    }
    count_1 = LONG_TO_FIXNUM(value);
    value = gsi_fc_outer_context;
    if (IFIX(Most_positive_fixnum) < value) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_large,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	goto end_shared_gsi_rpc_return_error_values;
    }
    if (value < IFIX(Most_negative_fixnum)) {
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_integer_too_small,Nil,
		Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	goto end_shared_gsi_rpc_return_error_values;
    }
    context = LONG_TO_FIXNUM(value);
    argument_array = gsi_fc_outer_argument_array ? 
	    g2int_gsi_displaced_array_from_c_contents(gsi_fc_outer_argument_array,
	    count_1) : Nil;
    if ( !( !TRUEP(call_handle) || SIMPLE_VECTOR_P(call_handle) && 
	    EQ(ISVREF(call_handle,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct))) 
		{
	g2int_set_gsi_error_message_1(Nil,G2int_gsi_invalid_call_handle,
		Nil,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_return_error_values;
    }
    code = g2int_invalid_gsi_context_p(context,T);
    if (code) {
	g2int_set_gsi_error_message_1(Nil,code,context,Nil,Nil,Nil,Nil,Nil);
	g2int_gsi_handle_error_1(Qg2int_gsi_rpc_return_error_values,Qerror,T);
	g2int_gsi_reclaim_displaced_array(argument_array);
	goto end_shared_gsi_rpc_return_error_values;
    }
    g2int_gsi_rpc_return_values_internal(argument_array,call_handle,context,T);
    g2int_gsi_reclaim_displaced_array(argument_array);
  end_shared_gsi_rpc_return_error_values:;
}

static Object string_constant_16;  /* "gsi_rpc_return_error_values" */

/* GSI-RPC-RETURN-ERROR-VALUES */
DLLEXPORT void gsi_rpc_return_error_values(argument_array,count_1,
	    call_handle,context)
    Object argument_array, call_handle;
    SI_Long count_1, context;
{
    Object in_recursive_gsi_context, in_unprotected_gsi_api_call_p;
    Object shutdown_catch_tag, top_level_error_catcher_tag, abort_level_0_tag;
    Declare_catch(1);
    Declare_special(4);

    x_note_fn_call(50,43);
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_entering_gsi,
	    G2int_gsi_run_state_type_api,string_constant_16);
    in_recursive_gsi_context =  ! 
	    !TRUEP(G2int_top_level_error_catcher_tag) ? T : Nil;
    PUSH_SPECIAL(G2int_in_recursive_gsi_context,in_recursive_gsi_context,3);
      if ( !TRUEP(g2int_protect_gsi_api_call_p())) {
	  in_unprotected_gsi_api_call_p = T;
	  PUSH_SPECIAL(G2int_in_unprotected_gsi_api_call_p,in_unprotected_gsi_api_call_p,
		  0);
	    g2int_shared_gsi_rpc_return_error_values(argument_array,
		    count_1,call_handle,context);
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
		    g2int_shared_gsi_rpc_return_error_values(argument_array,
			    count_1,call_handle,context);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  POP_CATCH(0);
      }
    POP_SPECIAL();
    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
	    G2int_gsi_run_state_direction_leaving_gsi,
	    G2int_gsi_run_state_type_api,string_constant_16);
}

static Object Qg2int_start;        /* start */

static Object Qg2int_call;         /* call */

static Object Qg2int_error_return;  /* error-return */

static Object list_constant;       /* # */

static Object Qg2int_rpc_error_handler_2;  /* rpc_error_handler_2 */

static Object string_constant_17;  /* "rpc_start" */

static Object string_constant_18;  /* "rpc_call" */

static Object string_constant_19;  /* "rpc_return" */

static Object string_constant_20;  /* "rpc_error_return" */

static Object Qg2int_rpc_callback;  /* rpc-callback */

static Object Qg2int_twrite_gsi_rpc_backtrace_info;  /* twrite-gsi-rpc-backtrace-info */

/* GSI-START-OR-CALL-LOCAL-FUNCTION-OR-HANDLE-RETURN-VALUES */
Object g2int_gsi_start_or_call_local_function_or_handle_return_values(invocation_type,
	    remote_procedure_name,remote_procedure_identifier,
	    rpc_argument_list)
    Object invocation_type, remote_procedure_name, remote_procedure_identifier;
    Object rpc_argument_list;
{
    Object current_remote_procedure_identifier, argument_list_length;
    Object local_function, function, remote_procedure_name_symbol, temp;
    Object temp_1, gsi_instance_extension, error_name, error_message;
    Object user_data, info_string, index_of_top_of_backtrace_stack;
    Object old_top_of_stack, elements_to_push_qm, temp_2;
    Object stored_elements_to_push, index_1, elements_to_push_qm_old_value;
    Object info_symbol, twrite_function_qm, number_of_args, svref_arg_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(50,44);
    if (EQ(invocation_type,Qg2int_start))
	G2int_current_invocation_remotely_started_p = T;
    else if (EQ(invocation_type,Qg2int_call))
	G2int_current_invocation_remotely_started_p = Nil;
    current_remote_procedure_identifier = EQ(invocation_type,Qg2int_call) ?
	     remote_procedure_identifier : Nil;
    PUSH_SPECIAL(G2int_current_remote_procedure_identifier,current_remote_procedure_identifier,
	    1);
      argument_list_length = 
	      FIXNUM_SUB1(g2int_gsi_managed_array_length(rpc_argument_list));
      if (EQ(invocation_type,Qg2int_start) || EQ(invocation_type,
		  Qg2int_call)) {
	  local_function = ISVREF(remote_procedure_name,(SI_Long)3L);
	  if (local_function);
	  else
	      local_function = 
		      g2int_gsi_handle_define_remote_procedure_name(remote_procedure_name);
      }
      else if (EQ(invocation_type,Qreturn))
	  local_function = ISVREF(remote_procedure_identifier,(SI_Long)3L);
      else if (EQ(invocation_type,Qg2int_error_return))
	  local_function = ISVREF(remote_procedure_identifier,(SI_Long)3L);
      else
	  local_function = Qnil;
      if (local_function) {
	  if (EQ(invocation_type,Qg2int_start) || EQ(invocation_type,
		  Qg2int_call))
	      function = ISVREF(local_function,(SI_Long)1L);
	  else if (EQ(invocation_type,Qreturn))
	      function = ISVREF(local_function,(SI_Long)3L);
	  else if (EQ(invocation_type,Qg2int_error_return))
	      function = ISVREF(local_function,(SI_Long)4L);
	  else
	      function = Qnil;
      }
      else
	  function = Nil;
      remote_procedure_name_symbol = ISVREF(remote_procedure_name,(SI_Long)1L);
      if (g2int_memq_function(invocation_type,list_constant) && 
	      local_function && remote_procedure_identifier)
	  SVREF(remote_procedure_identifier,FIX((SI_Long)3L)) = local_function;
      if ( !TRUEP(function)) {
	  if (EQ(invocation_type,Qg2int_error_return)) {
	      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),argument_list_length) 
		      && FIXNUM_LE(argument_list_length,FIX((SI_Long)127L))))
		  result = VALUES_1(Nil);
	      else
		  switch (INTEGER_TO_CHAR(argument_list_length)) {
		    case 2:
		      temp = ISVREF(ISVREF(rpc_argument_list,(SI_Long)1L),
			      (SI_Long)2L);
		      temp_1 = ISVREF(ISVREF(rpc_argument_list,
			      (SI_Long)2L),(SI_Long)2L);
		      result = VALUES_2(temp,temp_1);
		      break;
		    case 1:
		      gsi_instance_extension = 
			      ISVREF(ISVREF(rpc_argument_list,(SI_Long)1L),
			      (SI_Long)3L);
		      temp = gsi_instance_extension ? 
			      ISVREF(gsi_instance_extension,(SI_Long)2L) : Nil;
		      temp_1 = 
			      ISVREF(g2int_gsi_get_item_of_attribute_named(ISVREF(rpc_argument_list,
			      (SI_Long)1L),Qg2int_error_description),
			      (SI_Long)2L);
		      result = VALUES_2(temp,temp_1);
		      break;
		    default:
		      result = VALUES_1(Nil);
		      break;
		  }
	      MVS_2(result,error_name,error_message);
	      g2int_gsi_warning(5,Qg2int_rpc_error_handler_2,
		      G2int_gsi_rpc_error_from_g2_procedure,
		      remote_procedure_name_symbol,error_name,error_message);
	  }
      }
      else {
	  if (EQ(invocation_type,Qg2int_start) || EQ(invocation_type,
		  Qg2int_call))
	      user_data = ISVREF(local_function,(SI_Long)2L);
	  else if (EQ(invocation_type,Qreturn) || EQ(invocation_type,
		  Qg2int_error_return))
	      user_data = ISVREF(local_function,(SI_Long)5L);
	  else
	      user_data = Qnil;
	  if (EQ(invocation_type,Qg2int_start))
	      info_string = string_constant_17;
	  else if (EQ(invocation_type,Qg2int_call))
	      info_string = string_constant_18;
	  else if (EQ(invocation_type,Qreturn))
	      info_string = string_constant_19;
	  else if (EQ(invocation_type,Qg2int_error_return))
	      info_string = string_constant_20;
	  else
	      info_string = Qnil;
	  index_of_top_of_backtrace_stack = 
		  G2int_index_of_top_of_backtrace_stack;
	  PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		  0);
	    if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
		    G2int_size_of_basic_backtrace_information),
		    G2int_maximum_index_in_backtrace_stack_for_internal_error)) 
			{
		old_top_of_stack = G2int_index_of_top_of_backtrace_stack;
		elements_to_push_qm = Nil;
		temp_2 = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		G2int_index_of_top_of_backtrace_stack = temp_2;
		elements_to_push_qm = 
			g2int_gensym_cons_1(remote_procedure_name_symbol,
			elements_to_push_qm);
		if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
			G2int_size_of_basic_backtrace_information),
			G2int_maximum_index_in_backtrace_stack_for_internal_error)) 
			    {
		    stored_elements_to_push = elements_to_push_qm;
		    index_1 = G2int_index_of_top_of_backtrace_stack;
		  next_loop:
		    if ( !TRUEP(elements_to_push_qm))
			goto end_loop;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    elements_to_push_qm_old_value = elements_to_push_qm;
		    temp_1 = FIRST(elements_to_push_qm_old_value);
		    elements_to_push_qm = REST(elements_to_push_qm_old_value);
		    SVREF(temp_2,index_1) = temp_1;
		    index_1 = FIXNUM_SUB1(index_1);
		    goto next_loop;
		  end_loop:;
		    g2int_reclaim_gensym_list_1(stored_elements_to_push);
		    info_symbol = Qg2int_rpc_callback;
		    twrite_function_qm = Qg2int_twrite_gsi_rpc_backtrace_info;
		    number_of_args = 
			    FIXNUM_MINUS(G2int_index_of_top_of_backtrace_stack,
			    old_top_of_stack);
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = number_of_args;
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = twrite_function_qm;
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = info_symbol;
		}
		else {
		    G2int_index_of_top_of_backtrace_stack = old_top_of_stack;
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = FIX((SI_Long)0L);
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = Nil;
		    temp_2 = 
			    FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
		    G2int_index_of_top_of_backtrace_stack = temp_2;
		    temp_2 = G2int_backtrace_stack_for_internal_error;
		    svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
		    SVREF(temp_2,svref_arg_2) = Qg2int_rpc_callback;
		}
	    }
	    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
		    G2int_gsi_run_state_direction_leaving_gsi,
		    G2int_gsi_run_state_type_callback,info_string);
	    if (EQ(invocation_type,Qg2int_start) || EQ(invocation_type,
		    Qg2int_call)) {
		if (g2int_gsi_option_is_set_p(G2int_gsi_user_data_for_callbacks))
		    inline_c_function_call_user_data(function,user_data,
			    inline_extract_c_array(rpc_argument_list,
			    G2int_gsi_magic_offset),
			    FIXNUM_TO_LONG(argument_list_length),
			    remote_procedure_identifier);
		else
		    inline_c_function_call(function,
			    inline_extract_c_array(rpc_argument_list,
			    G2int_gsi_magic_offset),
			    FIXNUM_TO_LONG(argument_list_length),
			    remote_procedure_identifier);
	    }
	    else if (EQ(invocation_type,Qreturn) || EQ(invocation_type,
		    Qg2int_error_return)) {
		if (g2int_gsi_option_is_set_p(G2int_gsi_user_data_for_callbacks)) 
			    {
		    temp_1 = inline_extract_c_array(rpc_argument_list,
			    G2int_gsi_magic_offset);
		    inline_c_return_function_call_with_index_and_user_data(function,
			    user_data,temp_1,
			    FIXNUM_TO_LONG(argument_list_length),
			    ISVREF(remote_procedure_identifier,(SI_Long)7L));
		}
		else {
		    temp_1 = inline_extract_c_array(rpc_argument_list,
			    G2int_gsi_magic_offset);
		    inline_c_return_function_call_with_index(function,
			    temp_1,FIXNUM_TO_LONG(argument_list_length),
			    ISVREF(remote_procedure_identifier,(SI_Long)7L));
		}
	    }
	    g2int_call_gsi_callback(4,G2int_gsi_run_state_change,
		    G2int_gsi_run_state_direction_entering_gsi,
		    G2int_gsi_run_state_type_callback,info_string);
	  POP_SPECIAL();
      }
      if (EQ(invocation_type,Qreturn) || EQ(invocation_type,
	      Qg2int_error_return)) {
	  G2int_gsi_most_recent_error_remote_procedure_identifier = Nil;
	  g2int_reclaim_outgoing_remote_procedure_identifier_and_index(remote_procedure_identifier);
      }
    POP_SPECIAL();
    return VALUES_1(Nil);
}

void gsi_rpc1_INIT()
{
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package;

    x_note_fn_call(50,45);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_handle_icp_define_remote_proc = 
	    STATIC_SYMBOL("HANDLE_ICP_DEFINE_REMOTE_PROC",AB_package);
    string_constant = STATIC_STRING("gsi_rpc_declare_local_plain");
    Qg2int_gsi_catch = STATIC_SYMBOL("GSI-CATCH",AB_package);
    string_constant_1 = STATIC_STRING("gsi_rpc_declare_local_w_u_d");
    Qg2int_gsi_rpc_declare_remote_plain = 
	    STATIC_SYMBOL("gsi_rpc_declare_remote_plain",AB_package);
    string_constant_2 = STATIC_STRING("gsi_rpc_declare_remote_plain");
    Qg2int_gsi_rpc_declare_remote_w_u_d = 
	    STATIC_SYMBOL("gsi_rpc_declare_remote_w_u_d",AB_package);
    string_constant_3 = STATIC_STRING("gsi_rpc_declare_remote_w_u_d");
    Qg2int_gsi_rpc_declare_remote_w_e_u_d = 
	    STATIC_SYMBOL("gsi_rpc_declare_remote_w_e_u_d",AB_package);
    string_constant_4 = STATIC_STRING("gsi_rpc_declare_remote_w_e_u_d");
    Qg2int_gsi_set_rpc_remote_return_v_k = 
	    STATIC_SYMBOL("gsi_set_rpc_remote_return_v_k",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_by_copy_with_handle = STATIC_SYMBOL("BY-COPY-WITH-HANDLE",
	    AB_package);
    Qg2int_handle = STATIC_SYMBOL("HANDLE",AB_package);
    Qg2int_reference = STATIC_SYMBOL("REFERENCE",AB_package);
    Qg2int_copy = STATIC_SYMBOL("COPY",AB_package);
    Qg2int_value = STATIC_SYMBOL("VALUE",AB_package);
    string_constant_5 = STATIC_STRING("gsi_set_rpc_remote_return_v_k");
    Qg2int_gsi_set_rpc_remote_return_e_u_a = 
	    STATIC_SYMBOL("gsi_set_rpc_remote_return_e_u_a",AB_package);
    string_constant_6 = STATIC_STRING("gsi_set_rpc_remote_return_e_u_a");
    Qg2int_gsi_set_rpc_remote_return_i_s_a = 
	    STATIC_SYMBOL("gsi_set_rpc_remote_return_i_s_a",AB_package);
    string_constant_7 = STATIC_STRING("gsi_set_rpc_remote_return_i_s_a");
    Qg2int_gsi_set_rpc_remote_r_i_a_s_a_e = 
	    STATIC_SYMBOL("gsi_set_rpc_remote_r_i_a_s_a_e",AB_package);
    string_constant_8 = STATIC_STRING("gsi_set_rpc_remote_r_i_a_s_a_e");
    Qg2int_send_icp_resumable_rpc_start = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-START",AB_package);
    Qg2int_send_icp_resumable_rpc_call = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-CALL",AB_package);
    Qg2int_gsi_rpc_start = STATIC_SYMBOL("gsi_rpc_start",AB_package);
    string_constant_9 = STATIC_STRING("gsi_rpc_start");
    Qg2int_gsi_rpc_start_with_count = 
	    STATIC_SYMBOL("gsi_rpc_start_with_count",AB_package);
    string_constant_10 = STATIC_STRING("gsi_rpc_start_with_count");
    Qg2int_gsi_rpc_call = STATIC_SYMBOL("gsi_rpc_call",AB_package);
    string_constant_11 = STATIC_STRING("gsi_rpc_call");
    Qg2int_gsi_rpc_call_with_count = 
	    STATIC_SYMBOL("gsi_rpc_call_with_count",AB_package);
    string_constant_12 = STATIC_STRING("gsi_rpc_call_with_count");
    Qg2int_gsi_rpc_call_with_u_d = STATIC_SYMBOL("gsi_rpc_call_with_u_d",
	    AB_package);
    string_constant_13 = STATIC_STRING("gsi_rpc_call_with_u_d");
    Qg2int_gsi_rpc_call_with_count_u_d = 
	    STATIC_SYMBOL("gsi_rpc_call_with_count_u_d",AB_package);
    string_constant_14 = STATIC_STRING("gsi_rpc_call_with_count_u_d");
    Qab_g2int_gsi_rpc_return_values_internal = 
	    STATIC_SYMBOL("GSI_RPC_RETURN_VALUES_INTERNAL",AB_package);
    Qg2int_error_description = STATIC_SYMBOL("ERROR-DESCRIPTION",AB_package);
    Qg2int_outstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qg2int_send_icp_resumable_rpc_error_to_caller = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-ERROR-TO-CALLER",AB_package);
    Qg2int_reclaim_if_text_string_function = 
	    STATIC_SYMBOL("RECLAIM-IF-TEXT-STRING-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_if_text_string_function,
	    STATIC_FUNCTION(g2int_reclaim_if_text_string_function,NIL,
	    FALSE,1,1));
    Qg2int_send_icp_resumable_rpc_return_values = 
	    STATIC_SYMBOL("SEND-ICP-RESUMABLE-RPC-RETURN-VALUES",AB_package);
    Qg2int_returned = STATIC_SYMBOL("RETURNED",AB_package);
    Qg2int_async_abort = STATIC_SYMBOL("ASYNC-ABORT",AB_package);
    Qg2int_gsi_rpc_return_values = STATIC_SYMBOL("gsi_rpc_return_values",
	    AB_package);
    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_15 = STATIC_STRING("gsi_rpc_return_values");
    Qg2int_gsi_rpc_return_error_values = 
	    STATIC_SYMBOL("gsi_rpc_return_error_values",AB_package);
    string_constant_16 = STATIC_STRING("gsi_rpc_return_error_values");
    Qg2int_start = STATIC_SYMBOL("START",AB_package);
    Qg2int_call = STATIC_SYMBOL("CALL",AB_package);
    Qg2int_error_return = STATIC_SYMBOL("ERROR-RETURN",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qg2int_start,Qg2int_call);
    Qg2int_rpc_error_handler_2 = STATIC_SYMBOL("RPC_ERROR_HANDLER_2",
	    AB_package);
    string_constant_17 = STATIC_STRING("rpc_start");
    string_constant_18 = STATIC_STRING("rpc_call");
    string_constant_19 = STATIC_STRING("rpc_return");
    string_constant_20 = STATIC_STRING("rpc_error_return");
    Qg2int_rpc_callback = STATIC_SYMBOL("RPC-CALLBACK",AB_package);
    Qg2int_twrite_gsi_rpc_backtrace_info = 
	    STATIC_SYMBOL("TWRITE-GSI-RPC-BACKTRACE-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_twrite_gsi_rpc_backtrace_info,
	    STATIC_FUNCTION(g2int_twrite_gsi_rpc_backtrace_info,NIL,FALSE,
	    0,0));
}
