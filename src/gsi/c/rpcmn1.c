/* rpcmn1.c
 * Input file:  rpc-common1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rpcmn1.h"


Object G2int_the_type_description_of_gsi_local_function = UNBOUND;

Object G2int_chain_of_available_gsi_local_functions = UNBOUND;

Object G2int_gsi_local_function_count = UNBOUND;

/* RECLAIM-GSI-LOCAL-FUNCTION-1 */
Object g2int_reclaim_gsi_local_function_1(gsi_local_function)
    Object gsi_local_function;
{
    Object svref_new_value;

    x_note_fn_call(44,0);
    inline_note_reclaim_cons(gsi_local_function,Nil);
    svref_new_value = G2int_chain_of_available_gsi_local_functions;
    SVREF(gsi_local_function,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_local_functions = gsi_local_function;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-LOCAL-FUNCTION */
Object g2int_reclaim_structure_for_gsi_local_function(gsi_local_function)
    Object gsi_local_function;
{
    x_note_fn_call(44,1);
    return g2int_reclaim_gsi_local_function_1(gsi_local_function);
}

static Object Qg2_defstruct_structure_name_gsi_local_function_g2_struct;  /* g2-defstruct-structure-name::gsi-local-function-g2-struct */

/* MAKE-PERMANENT-GSI-LOCAL-FUNCTION-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_local_function_structure_internal()
{
    Object def_structure_gsi_local_function_variable;
    Object gsi_local_function_count_new_value;
    Object defstruct_g2_gsi_local_function_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,2);
    def_structure_gsi_local_function_variable = Nil;
    gsi_local_function_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_local_function_count);
    G2int_gsi_local_function_count = gsi_local_function_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_local_function_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_gsi_local_function_variable = the_array;
	SVREF(defstruct_g2_gsi_local_function_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_local_function_g2_struct;
	def_structure_gsi_local_function_variable = 
		defstruct_g2_gsi_local_function_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_local_function_variable);
}

/* MAKE-GSI-LOCAL-FUNCTION-1 */
Object g2int_make_gsi_local_function_1()
{
    Object def_structure_gsi_local_function_variable;

    x_note_fn_call(44,3);
    def_structure_gsi_local_function_variable = 
	    G2int_chain_of_available_gsi_local_functions;
    if (def_structure_gsi_local_function_variable) {
	G2int_chain_of_available_gsi_local_functions = 
		ISVREF(def_structure_gsi_local_function_variable,(SI_Long)0L);
	SVREF(def_structure_gsi_local_function_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_local_function_g2_struct;
    }
    else
	def_structure_gsi_local_function_variable = 
		g2int_make_permanent_gsi_local_function_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_local_function_variable,Nil);
    SVREF(def_structure_gsi_local_function_variable,FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_gsi_local_function_variable);
}

Object G2int_the_type_description_of_gsi_remote_procedure = UNBOUND;

Object G2int_chain_of_available_gsi_remote_procedures = UNBOUND;

Object G2int_gsi_remote_procedure_count = UNBOUND;

/* RECLAIM-GSI-REMOTE-PROCEDURE-INTERNAL-1 */
Object g2int_reclaim_gsi_remote_procedure_internal_1(gsi_remote_procedure)
    Object gsi_remote_procedure;
{
    Object svref_new_value;

    x_note_fn_call(44,4);
    inline_note_reclaim_cons(gsi_remote_procedure,Nil);
    svref_new_value = G2int_chain_of_available_gsi_remote_procedures;
    SVREF(gsi_remote_procedure,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_gsi_remote_procedures = gsi_remote_procedure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GSI-REMOTE-PROCEDURE */
Object g2int_reclaim_structure_for_gsi_remote_procedure(gsi_remote_procedure)
    Object gsi_remote_procedure;
{
    x_note_fn_call(44,5);
    return g2int_reclaim_gsi_remote_procedure_internal_1(gsi_remote_procedure);
}

static Object Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;  /* g2-defstruct-structure-name::gsi-remote-procedure-g2-struct */

/* MAKE-PERMANENT-GSI-REMOTE-PROCEDURE-STRUCTURE-INTERNAL */
Object g2int_make_permanent_gsi_remote_procedure_structure_internal()
{
    Object def_structure_gsi_remote_procedure_variable;
    Object gsi_remote_procedure_count_new_value;
    Object defstruct_g2_gsi_remote_procedure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,6);
    def_structure_gsi_remote_procedure_variable = Nil;
    gsi_remote_procedure_count_new_value = 
	    FIXNUM_ADD1(G2int_gsi_remote_procedure_count);
    G2int_gsi_remote_procedure_count = gsi_remote_procedure_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gsi_remote_procedure_variable = Nil;
	gensymed_symbol = (SI_Long)13L;
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
	defstruct_g2_gsi_remote_procedure_variable = the_array;
	SVREF(defstruct_g2_gsi_remote_procedure_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;
	def_structure_gsi_remote_procedure_variable = 
		defstruct_g2_gsi_remote_procedure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gsi_remote_procedure_variable);
}

/* MAKE-GSI-REMOTE-PROCEDURE-1 */
Object g2int_make_gsi_remote_procedure_1()
{
    Object def_structure_gsi_remote_procedure_variable;

    x_note_fn_call(44,7);
    def_structure_gsi_remote_procedure_variable = 
	    G2int_chain_of_available_gsi_remote_procedures;
    if (def_structure_gsi_remote_procedure_variable) {
	G2int_chain_of_available_gsi_remote_procedures = 
		ISVREF(def_structure_gsi_remote_procedure_variable,
		(SI_Long)0L);
	SVREF(def_structure_gsi_remote_procedure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct;
    }
    else
	def_structure_gsi_remote_procedure_variable = 
		g2int_make_permanent_gsi_remote_procedure_structure_internal();
    inline_note_allocate_cons(def_structure_gsi_remote_procedure_variable,Nil);
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_gsi_remote_procedure_variable,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_gsi_remote_procedure_variable);
}

/* RECLAIM-GSI-REMOTE-PROCEDURE */
Object g2int_reclaim_gsi_remote_procedure(remote_procedure)
    Object remote_procedure;
{
    Object remote_procedure_name_structure;

    x_note_fn_call(44,8);
    remote_procedure_name_structure = ISVREF(remote_procedure,(SI_Long)2L);
    if (remote_procedure_name_structure) {
	g2int_reclaim_remote_procedure_name(remote_procedure_name_structure);
	SVREF(remote_procedure,FIX((SI_Long)2L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)8L)) {
	g2int_reclaim_gensym_list_1(ISVREF(remote_procedure,(SI_Long)8L));
	SVREF(remote_procedure,FIX((SI_Long)8L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)9L)) {
	g2int_reclaim_gensym_tree_1(ISVREF(remote_procedure,(SI_Long)9L));
	SVREF(remote_procedure,FIX((SI_Long)9L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)10L)) {
	g2int_reclaim_gensym_tree_1(ISVREF(remote_procedure,(SI_Long)10L));
	SVREF(remote_procedure,FIX((SI_Long)10L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)11L)) {
	g2int_reclaim_gensym_tree_1(ISVREF(remote_procedure,(SI_Long)11L));
	SVREF(remote_procedure,FIX((SI_Long)11L)) = Nil;
    }
    if (ISVREF(remote_procedure,(SI_Long)12L)) {
	g2int_reclaim_gensym_tree_1(ISVREF(remote_procedure,(SI_Long)12L));
	SVREF(remote_procedure,FIX((SI_Long)12L)) = Nil;
    }
    return g2int_reclaim_gsi_remote_procedure_internal_1(remote_procedure);
}

Object G2int_current_remote_procedure_identifier = UNBOUND;

Object G2int_current_invocation_remotely_started_p = UNBOUND;

Object G2int_rpc_argument_count_overrideqm = UNBOUND;

Object G2int_the_type_description_of_remote_procedure_name = UNBOUND;

Object G2int_chain_of_available_remote_procedure_names = UNBOUND;

Object G2int_remote_procedure_name_count = UNBOUND;

/* RECLAIM-REMOTE-PROCEDURE-NAME-INTERNAL-1 */
Object g2int_reclaim_remote_procedure_name_internal_1(remote_procedure_name)
    Object remote_procedure_name;
{
    Object svref_new_value;

    x_note_fn_call(44,9);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    svref_new_value = G2int_chain_of_available_remote_procedure_names;
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_remote_procedure_names = remote_procedure_name;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_reclaim_structure_for_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    x_note_fn_call(44,10);
    return g2int_reclaim_remote_procedure_name_internal_1(remote_procedure_name);
}

static Object Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-name-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-NAME-STRUCTURE-INTERNAL */
Object g2int_make_permanent_remote_procedure_name_structure_internal()
{
    Object def_structure_remote_procedure_name_variable;
    Object remote_procedure_name_count_new_value;
    Object defstruct_g2_remote_procedure_name_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,11);
    def_structure_remote_procedure_name_variable = Nil;
    remote_procedure_name_count_new_value = 
	    FIXNUM_ADD1(G2int_remote_procedure_name_count);
    G2int_remote_procedure_name_count = remote_procedure_name_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_name_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_remote_procedure_name_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_name_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;
	def_structure_remote_procedure_name_variable = 
		defstruct_g2_remote_procedure_name_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_name_variable);
}

/* MAKE-REMOTE-PROCEDURE-NAME-1 */
Object g2int_make_remote_procedure_name_1(remote_procedure_name_symbol)
    Object remote_procedure_name_symbol;
{
    Object def_structure_remote_procedure_name_variable;

    x_note_fn_call(44,12);
    def_structure_remote_procedure_name_variable = 
	    G2int_chain_of_available_remote_procedure_names;
    if (def_structure_remote_procedure_name_variable) {
	G2int_chain_of_available_remote_procedure_names = 
		ISVREF(def_structure_remote_procedure_name_variable,
		(SI_Long)0L);
	SVREF(def_structure_remote_procedure_name_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_name_g2_struct;
    }
    else
	def_structure_remote_procedure_name_variable = 
		g2int_make_permanent_remote_procedure_name_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_name_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)1L)) = 
	    remote_procedure_name_symbol;
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_remote_procedure_name_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_remote_procedure_name_variable);
}

/* MAKE-REMOTE-PROCEDURE-NAME-FUNCTION */
Object g2int_make_remote_procedure_name_function(remote_procedure_name_symbol)
    Object remote_procedure_name_symbol;
{
    Object temp;

    x_note_fn_call(44,13);
    temp = g2int_make_remote_procedure_name_1(remote_procedure_name_symbol);
    return VALUES_1(temp);
}

/* RECLAIM-REMOTE-PROCEDURE-NAME */
Object g2int_reclaim_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object svref_new_value;

    x_note_fn_call(44,14);
    g2int_reclaim_icp_object_map_for_remote_procedure_name(remote_procedure_name);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    svref_new_value = G2int_chain_of_available_remote_procedure_names;
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_remote_procedure_names = remote_procedure_name;
    return VALUES_1(Nil);
}

/* RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE */
Object g2int_reclaim_remote_procedure_name_structure(remote_procedure_name)
    Object remote_procedure_name;
{
    Object svref_new_value;

    x_note_fn_call(44,15);
    inline_note_reclaim_cons(remote_procedure_name,Nil);
    svref_new_value = G2int_chain_of_available_remote_procedure_names;
    SVREF(remote_procedure_name,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_remote_procedure_names = remote_procedure_name;
    return VALUES_1(Nil);
}

static Object Qg2int_input;        /* input */

/* RECLAIM-REMOTE-PROCEDURE-NAME-FOR-CONNECTION-LOSS */
Object g2int_reclaim_remote_procedure_name_for_connection_loss(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(44,16);
    if (EQ(ISVREF(icp_port,(SI_Long)3L),Qg2int_input))
	return g2int_reclaim_remote_procedure_name(remote_procedure_name);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_standard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qg2int_establish_new_object_index_for_remote_procedure_name;  /* establish-new-object-index-for-remote-procedure-name */

static Object string_constant;     /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_establish_new_object_index_for_remote_procedure_name varargs_1(int, n)
{
    Object remote_procedure_name, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(44,17);
    INIT_ARGS_nonrelocating();
    remote_procedure_name = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (G2int_disable_resumability) {
	result = g2int_assign_corresponding_icp_object_index(remote_procedure_name,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_name,(SI_Long)2L)));
	SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_establish_new_object_index_for_remote_procedure_name,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_establish_new_object_index_for_remote_procedure_name,
			top,Nil);
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	icp_port = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : send_enlarge_message_p;
	result = g2int_assign_corresponding_icp_object_index(remote_procedure_name,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_name,(SI_Long)2L)));
	SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qg2int_make_corresponding_icp_remote_procedure_name;  /* make-corresponding-icp-remote-procedure-name */

/* MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-NAME */
Object g2int_make_corresponding_icp_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,18);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_assign_corresponding_icp_object_index(remote_procedure_name,
		  Qg2int_standard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		  g2int_gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(remote_procedure_name,(SI_Long)2L)));
	  SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making))
	      g2int_send_icp_define_remote_procedure_name(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)1L));
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_make_corresponding_icp_remote_procedure_name,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_make_corresponding_icp_remote_procedure_name,
			top,Nil);
	}
	remote_procedure_name = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = g2int_resumable_icp_pop();
	  else {
	      result = g2int_assign_corresponding_icp_object_index(remote_procedure_name,
		      Qg2int_standard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		      g2int_gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)2L)));
	      SVREF(remote_procedure_name,FIX((SI_Long)2L)) = svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      if (EQ(icp_suspend_1,
		      g2int_send_icp_define_remote_procedure_name(corresponding_icp_object_index,
		      ISVREF(remote_procedure_name,(SI_Long)1L)))) {
		  g2int_resumable_icp_push(corresponding_icp_object_index);
		  g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_block;
	      }
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(remote_procedure_name);
	    g2int_resumable_icp_push(Qg2int_make_corresponding_icp_remote_procedure_name);
	    return VALUES_1(G2int_icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_get_icp_object_index_for_remote_procedure_name(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(44,19);
    return g2int_getfq_function_no_default(ISVREF(remote_procedure_name,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_set_icp_object_index_for_remote_procedure_name(remote_procedure_name,
	    corresponding_icp_object_index,icp_port)
    Object remote_procedure_name, corresponding_icp_object_index, icp_port;
{
    Object svref_new_value;

    x_note_fn_call(44,20);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(remote_procedure_name,(SI_Long)2L)));
    return VALUES_1(SVREF(remote_procedure_name,FIX((SI_Long)2L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_reclaim_icp_object_map_for_remote_procedure_name(remote_procedure_name)
    Object remote_procedure_name;
{
    Object icp_object_map;

    x_note_fn_call(44,21);
    icp_object_map = ISVREF(remote_procedure_name,(SI_Long)2L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(remote_procedure_name,
		icp_object_map,Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_remote_procedure_name;  /* set-access-form-for-remote-procedure-name */

/* RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_reclaim_icp_port_entry_for_remote_procedure_name(remote_procedure_name,
	    icp_port)
    Object remote_procedure_name, icp_port;
{
    x_note_fn_call(44,22);
    return g2int_reclaim_icp_port_entry(icp_port,remote_procedure_name,
	    ISVREF(remote_procedure_name,(SI_Long)2L),
	    Qg2int_set_access_form_for_remote_procedure_name);
}

/* SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-NAME */
Object g2int_set_access_form_for_remote_procedure_name(remote_procedure_name,
	    new_value)
    Object remote_procedure_name, new_value;
{
    x_note_fn_call(44,23);
    return VALUES_1(SVREF(remote_procedure_name,FIX((SI_Long)2L)) = new_value);
}

static Object Qg2int_send_icp_define_remote_procedure_name;  /* send-icp-define-remote-procedure-name */

static Object Qg2int_corresponding_icp_object_map_for_symbol;  /* corresponding-icp-object-map-for-symbol */

/* SEND-ICP-DEFINE-REMOTE-PROCEDURE-NAME */
Object g2int_send_icp_define_remote_procedure_name(corresponding_icp_object_index,
	    remote_procedure_name_symbol)
    Object corresponding_icp_object_index, remote_procedure_name_symbol;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,24);
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
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_remote_procedure_name;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(remote_procedure_name_symbol),
		  Qg2int_corresponding_icp_object_map_for_symbol);
	  temp_1 = g2int_getfq_function_no_default(temp_1,
		  G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_symbol(remote_procedure_name_symbol);
	  remote_procedure_name_symbol = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)221L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_corresponding_object_index(remote_procedure_name_symbol);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_define_remote_procedure_name,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_define_remote_procedure_name,top,Nil);
		goto end_send_icp_define_remote_procedure_name;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	remote_procedure_name_symbol = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_name_symbol;
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
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_remote_procedure_name;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      value = g2int_resumable_icp_pop();
	  else {
	      temp_1 = 
		      g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(remote_procedure_name_symbol),
		      Qg2int_corresponding_icp_object_map_for_symbol);
	      value = g2int_getfq_function_no_default(temp_1,
		      G2int_current_icp_port);
	  }
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      remote_procedure_name_symbol = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_symbol(remote_procedure_name_symbol);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      remote_procedure_name_symbol = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)221L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(remote_procedure_name_symbol))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(remote_procedure_name_symbol);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_define_remote_procedure_name);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_remote_procedure_name;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_remote_procedure_name:
    return result;
}

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME--BODY */
Object g2int_handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
	    remote_procedure_name_symbol)
    Object corresponding_icp_object_index, remote_procedure_name_symbol;
{
    Object new_remote_procedure_name;

    x_note_fn_call(44,25);
    new_remote_procedure_name = 
	    g2int_make_remote_procedure_name_1(remote_procedure_name_symbol);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    new_remote_procedure_name);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_remote_procedure_name;  /* handle-icp-define-remote-procedure-name */

static Object Qg2int_resumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME */
Object g2int_handle_icp_define_remote_procedure_name()
{
    Object corresponding_icp_object_index, index_1, index_space;
    Object remote_procedure_name_symbol, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(44,26);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    remote_procedure_name_symbol = 
		    ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
		    IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) & 
		    (SI_Long)1023L);
	}
	else
	    remote_procedure_name_symbol = Nil;
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
		  remote_procedure_name_symbol);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_define_remote_procedure_name,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_define_remote_procedure_name,top,
			Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_name);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_name_symbol = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(corresponding_icp_object_index);
		    g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_name);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		remote_procedure_name_symbol = 
			ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),
			IFIX(index_1) >>  -  - (SI_Long)10L),IFIX(index_1) 
			& (SI_Long)1023L);
	    }
	    else
		remote_procedure_name_symbol = Nil;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_remote_procedure_name__body(corresponding_icp_object_index,
		  remote_procedure_name_symbol);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_remote_procedure_identifier = UNBOUND;

Object G2int_chain_of_available_remote_procedure_identifiers = UNBOUND;

Object G2int_remote_procedure_identifier_count = UNBOUND;

/* RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-1 */
Object g2int_reclaim_remote_procedure_identifier_1(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(44,27);
    inline_note_reclaim_cons(remote_procedure_identifier,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = remote_procedure_identifier;
    g2int_reclaim_gensym_list_1(ISVREF(remote_procedure_identifier,
	    (SI_Long)5L));
    SVREF(remote_procedure_identifier,FIX((SI_Long)5L)) = Nil;
    g2int_reclaim_remote_procedure_item_passing_info(ISVREF(remote_procedure_identifier,
	    (SI_Long)8L));
    SVREF(remote_procedure_identifier,FIX((SI_Long)8L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_remote_procedure_identifiers;
    SVREF(remote_procedure_identifier,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_remote_procedure_identifiers = 
	    remote_procedure_identifier;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_structure_for_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    x_note_fn_call(44,28);
    return g2int_reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
}

static Object Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-identifier-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-IDENTIFIER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_remote_procedure_identifier_structure_internal()
{
    Object def_structure_remote_procedure_identifier_variable;
    Object remote_procedure_identifier_count_new_value;
    Object defstruct_g2_remote_procedure_identifier_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,29);
    def_structure_remote_procedure_identifier_variable = Nil;
    remote_procedure_identifier_count_new_value = 
	    FIXNUM_ADD1(G2int_remote_procedure_identifier_count);
    G2int_remote_procedure_identifier_count = 
	    remote_procedure_identifier_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_identifier_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_remote_procedure_identifier_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_identifier_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;
	def_structure_remote_procedure_identifier_variable = 
		defstruct_g2_remote_procedure_identifier_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_identifier_variable);
}

static Object Qg2int_outstanding;  /* outstanding */

/* MAKE-REMOTE-PROCEDURE-IDENTIFIER-1 */
Object g2int_make_remote_procedure_identifier_1(remote_procedure_identifier_tag,
	    remote_procedure_item_passing_info)
    Object remote_procedure_identifier_tag, remote_procedure_item_passing_info;
{
    Object def_structure_remote_procedure_identifier_variable;

    x_note_fn_call(44,30);
    def_structure_remote_procedure_identifier_variable = 
	    G2int_chain_of_available_remote_procedure_identifiers;
    if (def_structure_remote_procedure_identifier_variable) {
	G2int_chain_of_available_remote_procedure_identifiers = 
		ISVREF(def_structure_remote_procedure_identifier_variable,
		(SI_Long)0L);
	SVREF(def_structure_remote_procedure_identifier_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct;
    }
    else
	def_structure_remote_procedure_identifier_variable = 
		g2int_make_permanent_remote_procedure_identifier_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_identifier_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)1L)) = remote_procedure_identifier_tag;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)8L)) = remote_procedure_item_passing_info;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)6L)) = Qg2int_outstanding;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_remote_procedure_identifier_variable,
	    FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_remote_procedure_identifier_variable);
}

/* MAKE-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_make_outgoing_remote_procedure_identifier(tag,info)
    Object tag, info;
{
    Object temp;

    x_note_fn_call(44,31);
    temp = g2int_make_remote_procedure_identifier_1(tag,info);
    return VALUES_1(temp);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_outgoing_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object temp;

    x_note_fn_call(44,32);
    SVREF(remote_procedure_identifier,FIX((SI_Long)9L)) = Nil;
    temp = 
	    g2int_reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
    return VALUES_1(temp);
}

/* MAKE-INCOMING-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_make_incoming_remote_procedure_identifier(tag,info)
    Object tag, info;
{
    Object temp;

    x_note_fn_call(44,33);
    temp = g2int_make_remote_procedure_identifier_1(tag,info);
    return VALUES_1(temp);
}

/* RECLAIM-INCOMING-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_incoming_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object temp;

    x_note_fn_call(44,34);
    SVREF(remote_procedure_identifier,FIX((SI_Long)9L)) = Nil;
    temp = 
	    g2int_reclaim_remote_procedure_identifier_1(remote_procedure_identifier);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-INFO */
Object g2int_make_remote_procedure_item_info(included_attributes,
	    excluded_attributes,included_system_attributes,
	    include_all_system_attributes,
	    include_all_system_attributes_except,kind)
    Object included_attributes, excluded_attributes;
    Object included_system_attributes, include_all_system_attributes;
    Object include_all_system_attributes_except, kind;
{
    Object gensymed_symbol, gensymed_symbol_1, list_1, temp;

    x_note_fn_call(44,35);
    gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = included_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = excluded_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = included_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes_except;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = kind;
    list_1 = gensymed_symbol;
    temp = g2int_intern_list(list_1);
    g2int_reclaim_gensym_list_1(list_1);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-INFO-OLD */
Object g2int_make_remote_procedure_item_info_old(included_attributes,
	    excluded_attributes,included_system_attributes,
	    include_all_system_attributes,kind)
    Object included_attributes, excluded_attributes;
    Object included_system_attributes, include_all_system_attributes, kind;
{
    Object gensymed_symbol, gensymed_symbol_1, list_1, temp;

    x_note_fn_call(44,36);
    gensymed_symbol = g2int_make_gensym_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = included_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = excluded_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = included_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = include_all_system_attributes;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = kind;
    list_1 = gensymed_symbol;
    temp = g2int_intern_list(list_1);
    g2int_reclaim_gensym_list_1(list_1);
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDED-ATTRIBUTES */
Object g2int_remote_procedure_item_info_included_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,37);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = FIRST(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-EXCLUDED-ATTRIBUTES */
Object g2int_remote_procedure_item_info_excluded_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,38);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = SECOND(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDED-SYSTEM-ATTRIBUTES */
Object g2int_remote_procedure_item_info_included_system_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,39);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = THIRD(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDE-ALL-SYSTEM-ATTRIBUTES */
Object g2int_remote_procedure_item_info_include_all_system_attributes(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,40);
    if (x) {
	temp = ISVREF(x,(SI_Long)1L);
	temp = FOURTH(temp);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-INCLUDE-ALL-SYSTEM-ATTRIBUTES-EXCEPT */
Object g2int_remote_procedure_item_info_include_all_system_attributes_except(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,41);
    temp = x ? FIFTH(ISVREF(x,(SI_Long)1L)) : Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-KIND */
Object g2int_remote_procedure_item_info_kind(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,42);
    temp = x ? SIXTH(ISVREF(x,(SI_Long)1L)) : Nil;
    return VALUES_1(temp);
}

/* REMOTE-PROCEDURE-ITEM-INFO-KIND-FUNCTION */
Object g2int_remote_procedure_item_info_kind_function(x)
    Object x;
{
    Object temp;

    x_note_fn_call(44,43);
    temp = g2int_remote_procedure_item_info_kind(x);
    return VALUES_1(temp);
}

Object G2int_the_type_description_of_remote_procedure_item_passing_info = UNBOUND;

Object G2int_chain_of_available_remote_procedure_item_passing_infos = UNBOUND;

Object G2int_remote_procedure_item_passing_info_count = UNBOUND;

/* RECLAIM-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object g2int_reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    Object svref_new_value;

    x_note_fn_call(44,44);
    inline_note_reclaim_cons(remote_procedure_item_passing_info,Nil);
    svref_new_value = 
	    G2int_chain_of_available_remote_procedure_item_passing_infos;
    SVREF(remote_procedure_item_passing_info,FIX((SI_Long)0L)) = 
	    svref_new_value;
    G2int_chain_of_available_remote_procedure_item_passing_infos = 
	    remote_procedure_item_passing_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object g2int_reclaim_structure_for_remote_procedure_item_passing_info(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    x_note_fn_call(44,45);
    return g2int_reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info);
}

static Object Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-item-passing-info-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-INTERNAL */
Object g2int_make_permanent_remote_procedure_item_passing_info_structure_internal()
{
    Object def_structure_remote_procedure_item_passing_info_variable;
    Object remote_procedure_item_passing_info_count_new_value;
    Object defstruct_g2_remote_procedure_item_passing_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,46);
    def_structure_remote_procedure_item_passing_info_variable = Nil;
    remote_procedure_item_passing_info_count_new_value = 
	    FIXNUM_ADD1(G2int_remote_procedure_item_passing_info_count);
    G2int_remote_procedure_item_passing_info_count = 
	    remote_procedure_item_passing_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_remote_procedure_item_passing_info_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_remote_procedure_item_passing_info_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;
	def_structure_remote_procedure_item_passing_info_variable = 
		defstruct_g2_remote_procedure_item_passing_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_item_passing_info_variable);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object g2int_make_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list)
    Object remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
{
    Object def_structure_remote_procedure_item_passing_info_variable;

    x_note_fn_call(44,47);
    def_structure_remote_procedure_item_passing_info_variable = 
	    G2int_chain_of_available_remote_procedure_item_passing_infos;
    if (def_structure_remote_procedure_item_passing_info_variable) {
	G2int_chain_of_available_remote_procedure_item_passing_infos = 
		ISVREF(def_structure_remote_procedure_item_passing_info_variable,
		(SI_Long)0L);
	SVREF(def_structure_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct;
    }
    else
	def_structure_remote_procedure_item_passing_info_variable = 
		g2int_make_permanent_remote_procedure_item_passing_info_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_item_passing_info_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_item_passing_info_variable,
	    FIX((SI_Long)1L)) = 
	    remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
    return VALUES_1(def_structure_remote_procedure_item_passing_info_variable);
}

/* RECLAIM-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object g2int_reclaim_remote_procedure_item_passing_info(remote_procedure_item_passing_info)
    Object remote_procedure_item_passing_info;
{
    x_note_fn_call(44,48);
    if (SIMPLE_VECTOR_P(remote_procedure_item_passing_info) && 
	    EQ(ISVREF(remote_procedure_item_passing_info,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct))
	g2int_reclaim_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info);
    return VALUES_1(Nil);
}

Object G2int_the_type_description_of_interned_remote_procedure_item_passing_info = UNBOUND;

Object G2int_chain_of_available_interned_remote_procedure_item_passing_infos = UNBOUND;

Object G2int_interned_remote_procedure_item_passing_info_count = UNBOUND;

/* RECLAIM-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1 */
Object g2int_reclaim_interned_remote_procedure_item_passing_info_1(interned_remote_procedure_item_passing_info)
    Object interned_remote_procedure_item_passing_info;
{
    Object svref_new_value;

    x_note_fn_call(44,49);
    inline_note_reclaim_cons(interned_remote_procedure_item_passing_info,Nil);
    svref_new_value = 
	    G2int_chain_of_available_interned_remote_procedure_item_passing_infos;
    SVREF(interned_remote_procedure_item_passing_info,FIX((SI_Long)0L)) = 
	    svref_new_value;
    G2int_chain_of_available_interned_remote_procedure_item_passing_infos 
	    = interned_remote_procedure_item_passing_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO */
Object g2int_reclaim_structure_for_interned_remote_procedure_item_passing_info(interned_remote_procedure_item_passing_info)
    Object interned_remote_procedure_item_passing_info;
{
    x_note_fn_call(44,50);
    return g2int_reclaim_interned_remote_procedure_item_passing_info_1(interned_remote_procedure_item_passing_info);
}

static Object Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;  /* g2-defstruct-structure-name::interned-remote-procedure-item-passing-info-g2-struct */

/* MAKE-PERMANENT-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-STRUCTURE-INTERNAL */
Object g2int_make_permanent_interned_remote_procedure_item_passing_info_structure_internal()
{
    Object def_structure_interned_remote_procedure_item_passing_info_variable;
    Object interned_remote_procedure_item_passing_info_count_new_value;
    Object defstruct_g2_interned_remote_procedure_item_passing_info_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,51);
    def_structure_interned_remote_procedure_item_passing_info_variable = Nil;
    interned_remote_procedure_item_passing_info_count_new_value = 
	    FIXNUM_ADD1(G2int_interned_remote_procedure_item_passing_info_count);
    G2int_interned_remote_procedure_item_passing_info_count = 
	    interned_remote_procedure_item_passing_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_interned_remote_procedure_item_passing_info_variable 
		= Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_interned_remote_procedure_item_passing_info_variable 
		= the_array;
	SVREF(defstruct_g2_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;
	SVREF(defstruct_g2_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)1L)) = Nil;
	def_structure_interned_remote_procedure_item_passing_info_variable 
		= 
		defstruct_g2_interned_remote_procedure_item_passing_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_interned_remote_procedure_item_passing_info_variable);
}

/* MAKE-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-1-1 */
Object g2int_make_interned_remote_procedure_item_passing_info_1_1(remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list)
    Object remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
{
    Object def_structure_interned_remote_procedure_item_passing_info_variable;

    x_note_fn_call(44,52);
    def_structure_interned_remote_procedure_item_passing_info_variable = 
	    G2int_chain_of_available_interned_remote_procedure_item_passing_infos;
    if (def_structure_interned_remote_procedure_item_passing_info_variable) {
	G2int_chain_of_available_interned_remote_procedure_item_passing_infos 
		= 
		ISVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
		(SI_Long)0L);
	SVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct;
    }
    else
	def_structure_interned_remote_procedure_item_passing_info_variable 
		= 
		g2int_make_permanent_interned_remote_procedure_item_passing_info_structure_internal();
    inline_note_allocate_cons(def_structure_interned_remote_procedure_item_passing_info_variable,
	    Nil);
    SVREF(def_structure_interned_remote_procedure_item_passing_info_variable,
	    FIX((SI_Long)1L)) = 
	    remote_procedure_item_passing_info_interned_varargsp_plus_item_info_list;
    return VALUES_1(def_structure_interned_remote_procedure_item_passing_info_variable);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-FROM-SPECS */
Object g2int_make_remote_procedure_item_passing_info_from_specs(internedp,
	    included_attributes_spec,excluded_attributes_spec,
	    included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p)
    Object internedp, included_attributes_spec, excluded_attributes_spec;
    Object included_system_attributes_spec, include_all_system_attributes_spec;
    Object include_all_system_attributes_except_spec, kind_spec, varargs_p;
{
    Object interned_list, temp;

    x_note_fn_call(44,53);
    interned_list = 
	    g2int_make_remote_procedure_item_passing_info_from_specs_1(included_attributes_spec,
	    excluded_attributes_spec,included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p);
    temp = internedp ? 
	    g2int_make_interned_remote_procedure_item_passing_info_1_1(interned_list) 
	    : g2int_make_remote_procedure_item_passing_info_1_1(interned_list);
    return VALUES_1(temp);
}

/* MAKE-REMOTE-PROCEDURE-ITEM-PASSING-INFO-FROM-SPECS-1 */
Object g2int_make_remote_procedure_item_passing_info_from_specs_1(included_attributes_spec,
	    excluded_attributes_spec,included_system_attributes_spec,
	    include_all_system_attributes_spec,
	    include_all_system_attributes_except_spec,kind_spec,varargs_p)
    Object included_attributes_spec, excluded_attributes_spec;
    Object included_system_attributes_spec, include_all_system_attributes_spec;
    Object include_all_system_attributes_except_spec, kind_spec, varargs_p;
{
    Object incl_attr_tail, excl_attr_tail, incl_sys_attr_tail;
    Object incl_all_sys_attr_tail, incl_all_sys_attr_except_tail, kind_tail;
    Object incl_attr, excl_attr, incl_sys_attr, incl_all_sys_attr;
    Object incl_all_sys_except_attr, kind, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, list_of_interned_item_infos, list_to_intern, temp;

    x_note_fn_call(44,54);
    incl_attr_tail = included_attributes_spec;
    excl_attr_tail = excluded_attributes_spec;
    incl_sys_attr_tail = included_system_attributes_spec;
    incl_all_sys_attr_tail = include_all_system_attributes_spec;
    incl_all_sys_attr_except_tail = include_all_system_attributes_except_spec;
    kind_tail = kind_spec;
    incl_attr = Nil;
    excl_attr = Nil;
    incl_sys_attr = Nil;
    incl_all_sys_attr = Nil;
    incl_all_sys_except_attr = Nil;
    kind = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !(incl_attr_tail || excl_attr_tail || incl_sys_attr_tail || 
	    incl_all_sys_attr_tail || incl_all_sys_attr_except_tail || 
	    kind_tail))
	goto end_loop;
    incl_attr = CAR(incl_attr_tail);
    excl_attr = CAR(excl_attr_tail);
    incl_sys_attr = CAR(incl_sys_attr_tail);
    incl_all_sys_attr = CAR(incl_all_sys_attr_tail);
    incl_all_sys_except_attr = CAR(incl_all_sys_attr_except_tail);
    kind = CAR(kind_tail);
    ab_loopvar__2 = 
	    g2int_gensym_cons_1(g2int_make_remote_procedure_item_info(incl_attr,
	    excl_attr,incl_sys_attr,incl_all_sys_attr,
	    incl_all_sys_except_attr,kind),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    incl_attr_tail = CDR(incl_attr_tail);
    excl_attr_tail = CDR(excl_attr_tail);
    incl_sys_attr_tail = CDR(incl_sys_attr_tail);
    incl_all_sys_attr_tail = CDR(incl_all_sys_attr_tail);
    incl_all_sys_attr_except_tail = CDR(incl_all_sys_attr_except_tail);
    kind_tail = CDR(kind_tail);
    goto next_loop;
  end_loop:
    list_of_interned_item_infos = ab_loopvar_;
    goto end;
    list_of_interned_item_infos = Qnil;
  end:;
    list_to_intern = g2int_gensym_cons_1(varargs_p,
	    list_of_interned_item_infos);
    temp = g2int_intern_list(list_to_intern);
    g2int_reclaim_gensym_list_1(list_to_intern);
    return VALUES_1(temp);
}

/* RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-FOR-CONNECTION-LOSS */
Object g2int_reclaim_remote_procedure_identifier_for_connection_loss(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(44,55);
    if (EQ(ISVREF(icp_port,(SI_Long)3L),Qg2int_input))
	return g2int_abort_rpc_call_and_reclaim_identifier(remote_procedure_identifier);
    else
	return g2int_signal_error_to_rpc_caller_and_reclaim_identifier(remote_procedure_identifier);
}

static Object Qg2int_establish_new_object_index_for_remote_procedure_identifier;  /* establish-new-object-index-for-remote-procedure-identifier */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_establish_new_object_index_for_remote_procedure_identifier varargs_1(int, n)
{
    Object remote_procedure_identifier, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(44,56);
    INIT_ARGS_nonrelocating();
    remote_procedure_identifier = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (G2int_disable_resumability) {
	result = g2int_assign_corresponding_icp_object_index(remote_procedure_identifier,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_establish_new_object_index_for_remote_procedure_identifier,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_establish_new_object_index_for_remote_procedure_identifier,
			top,Nil);
	}
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_identifier;
	icp_port = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : send_enlarge_message_p;
	result = g2int_assign_corresponding_icp_object_index(remote_procedure_identifier,
		Qg2int_standard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = g2int_gensym_cons_1(icp_port,
		g2int_gensym_cons_1(corresponding_icp_object_index,
		ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qg2int_make_corresponding_icp_remote_procedure_identifier;  /* make-corresponding-icp-remote-procedure-identifier */

/* MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_make_corresponding_icp_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp;
    Object item_passing_info, varargsp, item_info, ab_loop_list_;
    Object included_attributes_spec, ab_loopvar_, ab_loopvar__1;
    Object excluded_attributes_spec, ab_loopvar__2;
    Object included_system_attributes_spec, ab_loopvar__3;
    Object include_all_system_attributes_spec, ab_loopvar__4;
    Object include_all_system_attributes_except_spec, ab_loopvar__5, kind_spec;
    Object ab_loopvar__6, resumable_icp_state_1, icp_suspend_1, top;
    Object ab_loopvar__7, ab_loopvar__8, ab_loopvar__9, ab_loopvar__10;
    Object ab_loopvar__11, gensymed_symbol, value, v1, v2, v3;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,57);
    if (G2int_disable_resumability) {
	g2int_write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = g2int_assign_corresponding_icp_object_index(remote_procedure_identifier,
		  Qg2int_standard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		  g2int_gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	  SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
		  svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      item_passing_info = ISVREF(remote_procedure_identifier,
		      (SI_Long)8L);
	      temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),(SI_Long)1L);
	      varargsp = CAR(temp);
	      item_info = Nil;
	      temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),(SI_Long)1L);
	      ab_loop_list_ = CDR(temp);
	      included_attributes_spec = Nil;
	      ab_loopvar_ = Nil;
	      ab_loopvar__1 = Nil;
	      excluded_attributes_spec = Nil;
	      ab_loopvar__2 = Nil;
	      ab_loopvar__1 = Nil;
	      included_system_attributes_spec = Nil;
	      ab_loopvar__3 = Nil;
	      ab_loopvar__1 = Nil;
	      include_all_system_attributes_spec = Nil;
	      ab_loopvar__4 = Nil;
	      ab_loopvar__1 = Nil;
	      include_all_system_attributes_except_spec = Nil;
	      ab_loopvar__5 = Nil;
	      ab_loopvar__1 = Nil;
	      kind_spec = Nil;
	      ab_loopvar__6 = Nil;
	      ab_loopvar__1 = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      item_info = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_attributes(item_info),
		      Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  included_attributes_spec = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_excluded_attributes(item_info),
		      Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__1;
	      else
		  excluded_attributes_spec = ab_loopvar__1;
	      ab_loopvar__2 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__1;
	      else
		  included_system_attributes_spec = ab_loopvar__1;
	      ab_loopvar__3 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__4)
		  M_CDR(ab_loopvar__4) = ab_loopvar__1;
	      else
		  include_all_system_attributes_spec = ab_loopvar__1;
	      ab_loopvar__4 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes_except(item_info),
		      Nil);
	      if (ab_loopvar__5)
		  M_CDR(ab_loopvar__5) = ab_loopvar__1;
	      else
		  include_all_system_attributes_except_spec = ab_loopvar__1;
	      ab_loopvar__5 = ab_loopvar__1;
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_kind(item_info),
		      Nil);
	      if (ab_loopvar__6)
		  M_CDR(ab_loopvar__6) = ab_loopvar__1;
	      else
		  kind_spec = ab_loopvar__1;
	      ab_loopvar__6 = ab_loopvar__1;
	      goto next_loop;
	    end_loop:
	      g2int_send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
		      ISVREF(remote_procedure_identifier,(SI_Long)1L),
		      included_attributes_spec,excluded_attributes_spec,
		      included_system_attributes_spec,
		      include_all_system_attributes_spec,
		      include_all_system_attributes_except_spec,kind_spec,
		      varargsp);
	      g2int_reclaim_gensym_list_1(included_attributes_spec);
	      g2int_reclaim_gensym_list_1(excluded_attributes_spec);
	      g2int_reclaim_gensym_list_1(included_system_attributes_spec);
	      g2int_reclaim_gensym_list_1(include_all_system_attributes_spec);
	      g2int_reclaim_gensym_list_1(include_all_system_attributes_except_spec);
	      g2int_reclaim_gensym_list_1(kind_spec);
	      goto end;
	    end:;
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( 
		    !EQ(Qg2int_make_corresponding_icp_remote_procedure_identifier,
		    top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_make_corresponding_icp_remote_procedure_identifier,
			top,Nil);
	}
	remote_procedure_identifier = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_identifier;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,g2int_write_icp_maybe_suspend())) {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	writing_resumable_icp_messages_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      corresponding_icp_object_index = g2int_resumable_icp_pop();
	  else {
	      result = g2int_assign_corresponding_icp_object_index(remote_procedure_identifier,
		      Qg2int_standard_icp_object_index_space,T);
	      MVS_2(result,corresponding_icp_object_index,
		      new_index_limit_plus_one_qm);
	      svref_new_value = g2int_gensym_cons_1(G2int_current_icp_port,
		      g2int_gensym_cons_1(corresponding_icp_object_index,
		      ISVREF(remote_procedure_identifier,(SI_Long)2L)));
	      SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
		      svref_new_value;
	      if (T);
	      else {
		  temp = corresponding_icp_object_index;
		  corresponding_icp_object_index = temp;
	      }
	  }
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  ||  !TRUEP(G2int_inhibit_corresponding_icp_object_making)) {
	      item_passing_info = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      ISVREF(remote_procedure_identifier,(SI_Long)8L);
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  varargsp = g2int_resumable_icp_pop();
	      else {
		  temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  varargsp = CAR(temp);
	      }
	      item_info = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  ab_loop_list_ = g2int_resumable_icp_pop();
	      else {
		  temp = ISVREF(ISVREF(item_passing_info,(SI_Long)1L),
			  (SI_Long)1L);
		  ab_loop_list_ = CDR(temp);
	      }
	      included_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__1 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      excluded_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__2 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__3 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      included_system_attributes_spec = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__4 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__5 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      include_all_system_attributes_spec = (resumable_icp_state_1 ?
		       TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__6 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__7 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      include_all_system_attributes_except_spec = 
		      (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__8 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__9 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      kind_spec = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__10 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__11 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      item_info = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loopvar__1 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_attributes(item_info),
		      Nil);
	      if (ab_loopvar_)
		  M_CDR(ab_loopvar_) = ab_loopvar__1;
	      else
		  included_attributes_spec = ab_loopvar__1;
	      ab_loopvar_ = ab_loopvar__1;
	      ab_loopvar__3 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_excluded_attributes(item_info),
		      Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__3;
	      else
		  excluded_attributes_spec = ab_loopvar__3;
	      ab_loopvar__2 = ab_loopvar__3;
	      ab_loopvar__5 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_included_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__4)
		  M_CDR(ab_loopvar__4) = ab_loopvar__5;
	      else
		  included_system_attributes_spec = ab_loopvar__5;
	      ab_loopvar__4 = ab_loopvar__5;
	      ab_loopvar__7 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes(item_info),
		      Nil);
	      if (ab_loopvar__6)
		  M_CDR(ab_loopvar__6) = ab_loopvar__7;
	      else
		  include_all_system_attributes_spec = ab_loopvar__7;
	      ab_loopvar__6 = ab_loopvar__7;
	      ab_loopvar__9 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_include_all_system_attributes_except(item_info),
		      Nil);
	      if (ab_loopvar__8)
		  M_CDR(ab_loopvar__8) = ab_loopvar__9;
	      else
		  include_all_system_attributes_except_spec = ab_loopvar__9;
	      ab_loopvar__8 = ab_loopvar__9;
	      ab_loopvar__11 = 
		      g2int_gensym_cons_1(g2int_remote_procedure_item_info_kind(item_info),
		      Nil);
	      if (ab_loopvar__10)
		  M_CDR(ab_loopvar__10) = ab_loopvar__11;
	      else
		  kind_spec = ab_loopvar__11;
	      ab_loopvar__10 = ab_loopvar__11;
	      goto next_loop_1;
	    end_loop_1:
	    resume:
	      if ((resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		  gensymed_symbol = g2int_resumable_icp_pop();
	      else {
		  value = 
			  g2int_send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
			  ISVREF(remote_procedure_identifier,(SI_Long)1L),
			  included_attributes_spec,
			  excluded_attributes_spec,
			  included_system_attributes_spec,
			  include_all_system_attributes_spec,
			  include_all_system_attributes_except_spec,
			  kind_spec,varargsp);
		  if (EQ(icp_suspend_1,value)) {
		      g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		      g2int_resumable_icp_push(ab_loopvar__11);
		      g2int_resumable_icp_push(ab_loopvar__10);
		      g2int_resumable_icp_push(kind_spec);
		      g2int_resumable_icp_push(ab_loopvar__9);
		      g2int_resumable_icp_push(ab_loopvar__8);
		      g2int_resumable_icp_push(include_all_system_attributes_except_spec);
		      g2int_resumable_icp_push(ab_loopvar__7);
		      g2int_resumable_icp_push(ab_loopvar__6);
		      g2int_resumable_icp_push(include_all_system_attributes_spec);
		      g2int_resumable_icp_push(ab_loopvar__5);
		      g2int_resumable_icp_push(ab_loopvar__4);
		      g2int_resumable_icp_push(included_system_attributes_spec);
		      g2int_resumable_icp_push(ab_loopvar__3);
		      g2int_resumable_icp_push(ab_loopvar__2);
		      g2int_resumable_icp_push(excluded_attributes_spec);
		      g2int_resumable_icp_push(ab_loopvar__1);
		      g2int_resumable_icp_push(ab_loopvar_);
		      g2int_resumable_icp_push(included_attributes_spec);
		      g2int_resumable_icp_push(ab_loop_list_);
		      g2int_resumable_icp_push(item_info);
		      g2int_resumable_icp_push(varargsp);
		      g2int_resumable_icp_push(item_passing_info);
		      g2int_resumable_icp_push(corresponding_icp_object_index);
		      g2int_resumable_icp_push(G2int_writing_resumable_icp_messages_p);
		      g2int_resumable_icp_push(FIX((SI_Long)2L));
		      result = VALUES_1(G2int_icp_suspend);
		      POP_SPECIAL();
		      goto end_block;
		  }
		  gensymed_symbol = value;
	      }
	      g2int_reclaim_gensym_list_1(included_attributes_spec);
	      g2int_reclaim_gensym_list_1(excluded_attributes_spec);
	      g2int_reclaim_gensym_list_1(included_system_attributes_spec);
	      g2int_reclaim_gensym_list_1(include_all_system_attributes_spec);
	      g2int_reclaim_gensym_list_1(include_all_system_attributes_except_spec);
	      g2int_reclaim_gensym_list_1(kind_spec);
	      goto end_1;
	    end_1:;
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(remote_procedure_identifier);
	    g2int_resumable_icp_push(Qg2int_make_corresponding_icp_remote_procedure_identifier);
	    return VALUES_1(G2int_icp_suspend);
	}
	return VALUES_3(v1,v2,v3);
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_get_icp_object_index_for_remote_procedure_identifier(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(44,58);
    return g2int_getfq_function_no_default(ISVREF(remote_procedure_identifier,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_set_icp_object_index_for_remote_procedure_identifier(remote_procedure_identifier,
	    corresponding_icp_object_index,icp_port)
    Object remote_procedure_identifier, corresponding_icp_object_index;
    Object icp_port;
{
    Object svref_new_value;

    x_note_fn_call(44,59);
    svref_new_value = g2int_gensym_cons_1(icp_port,
	    g2int_gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(remote_procedure_identifier,(SI_Long)2L)));
    return VALUES_1(SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_icp_object_map_for_remote_procedure_identifier(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object icp_object_map;

    x_note_fn_call(44,60);
    icp_object_map = ISVREF(remote_procedure_identifier,(SI_Long)2L);
    if (icp_object_map)
	return g2int_reclaim_icp_object_map(remote_procedure_identifier,
		icp_object_map,Qg2int_standard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qg2int_set_access_form_for_remote_procedure_identifier;  /* set-access-form-for-remote-procedure-identifier */

/* RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_reclaim_icp_port_entry_for_remote_procedure_identifier(remote_procedure_identifier,
	    icp_port)
    Object remote_procedure_identifier, icp_port;
{
    x_note_fn_call(44,61);
    return g2int_reclaim_icp_port_entry(icp_port,
	    remote_procedure_identifier,ISVREF(remote_procedure_identifier,
	    (SI_Long)2L),
	    Qg2int_set_access_form_for_remote_procedure_identifier);
}

/* SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_set_access_form_for_remote_procedure_identifier(remote_procedure_identifier,
	    new_value)
    Object remote_procedure_identifier, new_value;
{
    x_note_fn_call(44,62);
    return VALUES_1(SVREF(remote_procedure_identifier,FIX((SI_Long)2L)) = 
	    new_value);
}

static Object Qg2int_send_icp_define_remote_procedure_identifier;  /* send-icp-define-remote-procedure-identifier */

/* SEND-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_send_icp_define_remote_procedure_identifier(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,63);
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
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_remote_procedure_identifier;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)222L));
	  g2int_write_icp_unsigned_integer(corresponding_icp_object_index);
	  g2int_write_icp_unsigned_integer(remote_procedure_identifier_tag);
	  g2int_write_icp_list_of_included_return_attributes(list_of_included_return_attributes);
	  g2int_write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes);
	  g2int_write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes);
	  g2int_write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes);
	  g2int_write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except);
	  g2int_write_icp_list_of_return_kinds(list_of_return_kinds);
	  g2int_write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_define_remote_procedure_identifier,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_define_remote_procedure_identifier,
			top,Nil);
		goto end_send_icp_define_remote_procedure_identifier;
	    }
	}
	corresponding_icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : corresponding_icp_object_index;
	remote_procedure_identifier_tag = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_identifier_tag;
	list_of_included_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_included_return_attributes;
	list_of_excluded_return_attributes = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_excluded_return_attributes;
	list_of_included_return_system_attributes = (resumable_icp_state_1 
		? TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		&&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_included_return_system_attributes;
	list_of_include_all_return_system_attributes = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_include_all_return_system_attributes;
	list_of_include_all_return_system_attributes_except = 
		(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : 
		list_of_include_all_return_system_attributes_except;
	list_of_return_kinds = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_of_return_kinds;
	remote_procedure_varargs_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_procedure_varargs_p;
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
	      SVREF(temp,svref_arg_2) = 
		      Qg2int_send_icp_define_remote_procedure_identifier;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)222L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1_1;
		      break;
		    case 2:
		      goto l2_1;
		      break;
		    case 3:
		      goto l3;
		      break;
		    case 4:
		      goto l4;
		      break;
		    case 5:
		      goto l5;
		      break;
		    case 6:
		      goto l6;
		      break;
		    case 7:
		      goto l7;
		      break;
		    case 8:
		      goto l8;
		      break;
		    case 9:
		      goto l9;
		      break;
		    default:
		      break;
		  }
	  }
	l1_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(corresponding_icp_object_index))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l2_1:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(remote_procedure_identifier_tag))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_included_return_attributes(list_of_included_return_attributes))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_excluded_return_attributes(list_of_excluded_return_attributes))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l5:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_included_return_system_attributes(list_of_included_return_system_attributes))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)5L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l6:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_include_all_return_system_attributes(list_of_include_all_return_system_attributes))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)6L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l7:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_include_all_return_system_attributes_except(list_of_include_all_return_system_attributes_except))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)7L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l8:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_list_of_return_kinds(list_of_return_kinds))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)8L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	l9:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_remote_procedure_varargs_p(remote_procedure_varargs_p))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)9L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block_1;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block_1;
	end_block_1:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(remote_procedure_varargs_p);
	      g2int_resumable_icp_push(list_of_return_kinds);
	      g2int_resumable_icp_push(list_of_include_all_return_system_attributes_except);
	      g2int_resumable_icp_push(list_of_include_all_return_system_attributes);
	      g2int_resumable_icp_push(list_of_included_return_system_attributes);
	      g2int_resumable_icp_push(list_of_excluded_return_attributes);
	      g2int_resumable_icp_push(list_of_included_return_attributes);
	      g2int_resumable_icp_push(remote_procedure_identifier_tag);
	      g2int_resumable_icp_push(corresponding_icp_object_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_define_remote_procedure_identifier);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_remote_procedure_identifier;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_remote_procedure_identifier:
    return result;
}

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER--BODY */
Object g2int_handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
	    remote_procedure_identifier_tag,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p)
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
{
    Object new_remote_procedure_identifier;

    x_note_fn_call(44,64);
    new_remote_procedure_identifier = 
	    g2int_make_incoming_remote_procedure_identifier(remote_procedure_identifier_tag,
	    g2int_make_remote_procedure_item_passing_info_from_specs(Nil,
	    list_of_included_return_attributes,
	    list_of_excluded_return_attributes,
	    list_of_included_return_system_attributes,
	    list_of_include_all_return_system_attributes,
	    list_of_include_all_return_system_attributes_except,
	    list_of_return_kinds,remote_procedure_varargs_p));
    g2int_reclaim_gensym_tree_1(list_of_included_return_attributes);
    g2int_reclaim_gensym_tree_1(list_of_excluded_return_attributes);
    g2int_reclaim_gensym_tree_1(list_of_included_return_system_attributes);
    g2int_reclaim_gensym_tree_1(list_of_include_all_return_system_attributes);
    g2int_reclaim_gensym_tree_1(list_of_include_all_return_system_attributes_except);
    g2int_reclaim_gensym_tree_1(list_of_return_kinds);
    g2int_store_corresponding_icp_object(corresponding_icp_object_index,
	    new_remote_procedure_identifier);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_define_remote_procedure_identifier;  /* handle-icp-define-remote-procedure-identifier */

/* HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER */
Object g2int_handle_icp_define_remote_procedure_identifier()
{
    Object corresponding_icp_object_index, remote_procedure_identifier_tag;
    Object list_of_included_return_attributes;
    Object list_of_excluded_return_attributes;
    Object list_of_included_return_system_attributes;
    Object list_of_include_all_return_system_attributes;
    Object list_of_include_all_return_system_attributes_except;
    Object list_of_return_kinds, remote_procedure_varargs_p;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(44,65);
    if (G2int_disable_resumability) {
	corresponding_icp_object_index = g2int_read_icp_unsigned_integer();
	remote_procedure_identifier_tag = g2int_read_icp_unsigned_integer();
	list_of_included_return_attributes = 
		g2int_read_icp_list_of_included_return_attributes();
	list_of_excluded_return_attributes = 
		g2int_read_icp_list_of_excluded_return_attributes();
	list_of_included_return_system_attributes = 
		g2int_read_icp_list_of_included_return_system_attributes();
	list_of_include_all_return_system_attributes = 
		g2int_read_icp_list_of_include_all_return_system_attributes();
	list_of_include_all_return_system_attributes_except = 
		g2int_read_icp_list_of_include_all_return_system_attributes_except();
	list_of_return_kinds = g2int_read_icp_list_of_return_kinds();
	remote_procedure_varargs_p = 
		g2int_read_icp_remote_procedure_varargs_p();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
		  remote_procedure_identifier_tag,
		  list_of_included_return_attributes,
		  list_of_excluded_return_attributes,
		  list_of_included_return_system_attributes,
		  list_of_include_all_return_system_attributes,
		  list_of_include_all_return_system_attributes_except,
		  list_of_return_kinds,remote_procedure_varargs_p);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_define_remote_procedure_identifier,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_define_remote_procedure_identifier,
			top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    corresponding_icp_object_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    corresponding_icp_object_index = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_identifier_tag = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_procedure_identifier_tag = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_included_return_attributes = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_of_included_return_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_included_return_attributes = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_excluded_return_attributes = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_of_excluded_return_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_excluded_return_attributes = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_included_return_system_attributes = 
		    g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_of_included_return_system_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_included_return_system_attributes = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_include_all_return_system_attributes = 
		    g2int_resumable_icp_pop();
	else {
	    value = 
		    g2int_read_icp_list_of_include_all_return_system_attributes();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_included_return_system_attributes);
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_include_all_return_system_attributes = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_include_all_return_system_attributes_except = 
		    g2int_resumable_icp_pop();
	else {
	    value = 
		    g2int_read_icp_list_of_include_all_return_system_attributes_except();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes);
		g2int_resumable_icp_push(list_of_included_return_system_attributes);
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_include_all_return_system_attributes_except = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    list_of_return_kinds = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_list_of_return_kinds();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes_except);
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes);
		g2int_resumable_icp_push(list_of_included_return_system_attributes);
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    list_of_return_kinds = value;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    remote_procedure_varargs_p = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_remote_procedure_varargs_p();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(list_of_return_kinds);
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes_except);
		g2int_resumable_icp_push(list_of_include_all_return_system_attributes);
		g2int_resumable_icp_push(list_of_included_return_system_attributes);
		g2int_resumable_icp_push(list_of_excluded_return_attributes);
		g2int_resumable_icp_push(list_of_included_return_attributes);
		g2int_resumable_icp_push(remote_procedure_identifier_tag);
		g2int_resumable_icp_push(corresponding_icp_object_index);
		g2int_resumable_icp_push(Qg2int_handle_icp_define_remote_procedure_identifier);
		return VALUES_1(G2int_icp_suspend);
	    }
	    remote_procedure_varargs_p = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_define_remote_procedure_identifier__body(corresponding_icp_object_index,
		  remote_procedure_identifier_tag,
		  list_of_included_return_attributes,
		  list_of_excluded_return_attributes,
		  list_of_included_return_system_attributes,
		  list_of_include_all_return_system_attributes,
		  list_of_include_all_return_system_attributes_except,
		  list_of_return_kinds,remote_procedure_varargs_p);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* RECLAIM-RPC-ARGUMENT-LIST */
Object g2int_reclaim_rpc_argument_list(list_1,do_not_reclaim_arguments)
    Object list_1, do_not_reclaim_arguments;
{
    x_note_fn_call(44,66);
    if (list_1)
	g2int_gsi_reclaim_managed_array(list_1);
    return VALUES_1(Nil);
}

/* RECLAIM-TRANSFORMED-RPC-ARGUMENT-LIST */
Object g2int_reclaim_transformed_rpc_argument_list(list_1,
	    do_not_reclaim_arguments)
    Object list_1, do_not_reclaim_arguments;
{
    x_note_fn_call(44,67);
    if (list_1)
	g2int_gsi_reclaim_managed_array(list_1);
    return VALUES_1(Nil);
}

/* RECLAIM-UNPROCESSED-RPC-ARGUMENT-LIST */
Object g2int_reclaim_unprocessed_rpc_argument_list varargs_1(int, n)
{
    Object list_1, initial_rpc_frame_serial_number;
    Object nargs_to_skip_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(44,68);
    INIT_ARGS_nonrelocating();
    list_1 = REQUIRED_ARG_nonrelocating();
    initial_rpc_frame_serial_number = REQUIRED_ARG_nonrelocating();
    nargs_to_skip_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    return VALUES_1(Nil);
}

Object G2int_write_remote_value_items_kind = UNBOUND;

Object G2int_gsi_remote_value_creates_instance_p = UNBOUND;

Object G2int_gsi_remote_value_conses_logical_p = UNBOUND;

Object G2int_remote_value_is_binary_p = UNBOUND;

Object G2int_remote_value_known_typetag = UNBOUND;

static Object Qg2_defstruct_structure_name_gsi_instance_g2_struct;  /* g2-defstruct-structure-name::gsi-instance-g2-struct */

static Object Qg2int_item;         /* item */

static Object Qg2int_truth_value;  /* truth-value */

static Object Qg2int_write_icp_remote_value_1;  /* write-icp-remote-value-1 */

static Object Qg2int_true;         /* true */

static Object Qg2int_false;        /* false */

/* WRITE-ICP-REMOTE-VALUE-1 */
Object g2int_write_icp_remote_value_1(remote_value_1)
    Object remote_value_1;
{
    Object typecode, cdr_1, value, result_1, temp_1, temp_2;
    Object resumable_icp_state_1, icp_suspend_1, top, gensymed_symbol, arg1;
    Object arg2, test, value_1;
    SI_Long type, length_1;
    char temp;

    x_note_fn_call(44,69);
    if (G2int_disable_resumability) {
	typecode = G2int_remote_value_known_typetag;
	if (typecode);
	else if (SIMPLE_VECTOR_P(remote_value_1) && 
		EQ(ISVREF(remote_value_1,(SI_Long)0L),
		Qg2_defstruct_structure_name_gsi_instance_g2_struct)) {
	    if ( !(G2int_write_value_of_gsi_item_p || 
		    g2int_gsi_item_is_value_p(remote_value_1)))
		typecode = Qg2int_item;
	    else {
		type = IFIX(ISVREF(remote_value_1,(SI_Long)1L)) >>  -  - 
			(SI_Long)3L;
		typecode = EQ(FIX((SI_Long)50L),FIX(type)) || 
			EQ(FIX((SI_Long)49L),FIX(type)) || 
			g2int_element_type_for_gsi_type(FIX(type)) || 
			ISVREF(remote_value_1,(SI_Long)2L) ? FIX(type) : 
			FIX((SI_Long)0L);
	    }
	}
	else if ( !TRUEP(remote_value_1))
	    typecode = FIX((SI_Long)0L);
	else if (SYMBOLP(remote_value_1))
	    typecode = FIX((SI_Long)3L);
	else if (FIXNUMP(remote_value_1))
	    typecode = FIX((SI_Long)1L);
	else if (INLINE_LONG_P(remote_value_1) != (SI_Long)0L)
	    typecode = FIX((SI_Long)51L);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(remote_value_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == (SI_Long)1L)
	    typecode = FIX((SI_Long)6L);
	else {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) != 
		    (SI_Long)0L) {
		length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1));
		temp = (SI_Long)1L == UBYTE_16_ISAREF_1(remote_value_1,
			UBYTE_16_ISAREF_1(remote_value_1,length_1 - 
			(SI_Long)2L) + ((UBYTE_16_ISAREF_1(remote_value_1,
			length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			(SI_Long)16L));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		typecode = FIX((SI_Long)11L);
	    else if (g2int_text_string_p(remote_value_1) || 
		    STRINGP(remote_value_1))
		typecode = FIX((SI_Long)4L);
	    else if (CONSP(remote_value_1)) {
		cdr_1 = M_CDR(remote_value_1);
		typecode = EQ(cdr_1,Qg2int_truth_value) ? FIX((SI_Long)5L) 
			: FIX((SI_Long)0L);
	    }
	    else
		typecode = FIX((SI_Long)0L);
	}
	if (EQ(typecode,FIX((SI_Long)0L))) {
	    value = Nil;
	    result_1 = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		    >= (SI_Long)8L ? ( 
		    !TRUEP(G2int_remote_value_known_typetag) ? 
		    g2int_write_icp_byte(FIX((SI_Long)0L)) : Nil) : 
		    g2int_write_icp_byte(FIX((SI_Long)0L));
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)1L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L) {
		if ( !TRUEP(G2int_remote_value_known_typetag))
		    g2int_write_icp_byte(FIX((SI_Long)1L));
	    }
	    else
		g2int_write_icp_byte(FIX((SI_Long)1L));
	    result_1 = g2int_write_icp_integer(value);
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)51L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    temp_1 = ISVREF(G2int_current_icp_socket,(SI_Long)21L);
	    temp_2 = ISVREF(G2int_current_icp_socket,(SI_Long)22L);
	    if (IFIX(FIXNUM_MIN(temp_1,temp_2)) >= (SI_Long)30L) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(G2int_remote_value_known_typetag))
			g2int_write_icp_byte(FIX((SI_Long)51L));
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)51L));
		result_1 = g2int_write_icp_managed_long(value);
	    }
	    else
		result_1 = Nil;
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)5L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L) {
		if ( !TRUEP(G2int_remote_value_known_typetag))
		    g2int_write_icp_byte(FIX((SI_Long)5L));
	    }
	    else
		g2int_write_icp_byte(FIX((SI_Long)5L));
	    result_1 = g2int_write_icp_integer(value);
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)6L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)2L) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(G2int_remote_value_known_typetag))
			g2int_write_icp_byte(FIX((SI_Long)6L));
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)6L));
		result_1 = g2int_write_icp_managed_double_float(value);
	    }
	    else {
		g2int_write_icp_byte(FIX((SI_Long)2L));
		result_1 = g2int_write_icp_float(value);
	    }
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)3L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    result_1 = g2int_write_icp_symbol_as_value_type(value);
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)4L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		temp_1 = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		temp_1 = M_CAR(remote_value_1);
	    else
		temp_1 = remote_value_1;
	    value = g2int_convert_gsi_value_to_value(temp_1);
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L) {
		if ( !TRUEP(G2int_remote_value_known_typetag))
		    g2int_write_icp_byte(FIX((SI_Long)4L));
	    }
	    else
		g2int_write_icp_byte(FIX((SI_Long)4L));
	    result_1 = g2int_write_icp_text_string(value);
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		temp_1 = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		temp_1 = M_CAR(remote_value_1);
	    else
		temp_1 = remote_value_1;
	    if (STRINGP(temp_1))
		g2int_reclaim_wide_string(value);
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)11L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)14L) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(G2int_remote_value_known_typetag))
			g2int_write_icp_byte(FIX((SI_Long)11L));
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)11L));
		result_1 = g2int_write_icp_wide_string(value);
	    }
	    else {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(G2int_remote_value_known_typetag))
			g2int_write_icp_byte(FIX((SI_Long)4L));
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)4L));
		result_1 = g2int_write_icp_text_string(value);
	    }
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)9L))) {
	    if (SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		value = ISVREF(remote_value_1,(SI_Long)2L);
	    else if (CONSP(remote_value_1))
		value = M_CAR(remote_value_1);
	    else
		value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L) {
		if ( !TRUEP(G2int_remote_value_known_typetag))
		    g2int_write_icp_byte(FIX((SI_Long)8L));
	    }
	    else
		g2int_write_icp_byte(FIX((SI_Long)8L));
	    result_1 = g2int_write_icp_fixnum(value);
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)50L))) {
	    value = remote_value_1;
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)8L) {
		if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) >= 
			(SI_Long)8L) {
		    if ( !TRUEP(G2int_remote_value_known_typetag))
			g2int_write_icp_byte(FIX((SI_Long)50L));
		}
		else
		    g2int_write_icp_byte(FIX((SI_Long)50L));
		result_1 = g2int_write_icp_evaluation_structure(value);
	    }
	    else
		result_1 = g2int_write_icp_byte(FIX((SI_Long)0L));
	    temp_1 = result_1;
	}
	else if (EQ(typecode,FIX((SI_Long)49L))) {
	    value = remote_value_1;
	    result_1 = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		    >= (SI_Long)8L ? 
		    g2int_write_icp_evaluation_sequence(value) : 
		    g2int_write_icp_byte(FIX((SI_Long)0L));
	    temp_1 = result_1;
	}
	else if (EQ(typecode,Qg2int_item)) {
	    value = remote_value_1;
	    result_1 = IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)22L)) 
		    >= (SI_Long)8L ? g2int_write_icp_item(value) : 
		    g2int_write_icp_byte(FIX((SI_Long)0L));
	    temp_1 = result_1;
	}
	else
	    temp_1 = g2int_write_icp_byte(FIX((SI_Long)0L));
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_remote_value_1,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_remote_value_1,top,Nil);
	}
	remote_value_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_value_1;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    typecode = g2int_resumable_icp_pop();
	else {
	    gensymed_symbol = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : 
		    G2int_remote_value_known_typetag;
	    if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    && gensymed_symbol)
		typecode = gensymed_symbol;
	    else if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    && SIMPLE_VECTOR_P(remote_value_1) && 
		    EQ(ISVREF(remote_value_1,(SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct)) {
		if ( !(G2int_write_value_of_gsi_item_p || 
			g2int_gsi_item_is_value_p(remote_value_1)))
		    typecode = Qg2int_item;
		else {
		    type = IFIX(ISVREF(remote_value_1,(SI_Long)1L)) >>  -  
			    - (SI_Long)3L;
		    typecode = EQ(FIX((SI_Long)50L),FIX(type)) || 
			    EQ(FIX((SI_Long)49L),FIX(type)) || 
			    g2int_element_type_for_gsi_type(FIX(type)) || 
			    ISVREF(remote_value_1,(SI_Long)2L) ? FIX(type) 
			    : FIX((SI_Long)0L);
		}
	    }
	    else if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(remote_value_1))
		typecode = FIX((SI_Long)0L);
	    else if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    && SYMBOLP(remote_value_1))
		typecode = FIX((SI_Long)3L);
	    else if ( !(resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    && FIXNUMP(remote_value_1))
		typecode = FIX((SI_Long)1L);
	    else {
		arg1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : 
			FIX(INLINE_LONG_P(remote_value_1));
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : FIX((SI_Long)0L);
		if (FIXNUM_NE(arg1,arg2))
		    typecode = FIX((SI_Long)51L);
		else if (INLINE_DOUBLE_FLOAT_VECTOR_P(remote_value_1) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1)) == 
			(SI_Long)1L)
		    typecode = FIX((SI_Long)6L);
		else {
		    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(remote_value_1) 
			    != (SI_Long)0L) {
			length_1 = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(remote_value_1));
			temp = (SI_Long)1L == 
				UBYTE_16_ISAREF_1(remote_value_1,
				UBYTE_16_ISAREF_1(remote_value_1,length_1 
				- (SI_Long)2L) + 
				((UBYTE_16_ISAREF_1(remote_value_1,
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			typecode = FIX((SI_Long)11L);
		    else if (g2int_text_string_p(remote_value_1) || 
			    STRINGP(remote_value_1))
			typecode = FIX((SI_Long)4L);
		    else if (CONSP(remote_value_1)) {
			cdr_1 = M_CDR(remote_value_1);
			typecode = EQ(cdr_1,Qg2int_truth_value) ? 
				FIX((SI_Long)5L) : FIX((SI_Long)0L);
		    }
		    else
			typecode = FIX((SI_Long)0L);
		}
	    }
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp = TRUEP(test);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? EQ(test,Qg2int_true) : EQ(typecode,FIX((SI_Long)0L))) {
	    value = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		result_1 = g2int_resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp = TRUEP(test);
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? EQ(test,Qg2int_true) : 
			IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)22L)) >= (SI_Long)8L) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) ||  
			    !TRUEP(G2int_remote_value_known_typetag)) {
			value_1 = g2int_write_icp_byte(FIX((SI_Long)0L));
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(typecode);
			    g2int_resumable_icp_push(remote_value_1);
			    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			result_1 = value_1;
		    }
		    else
			result_1 = Nil;
		}
		else {
		    value_1 = g2int_write_icp_byte(FIX((SI_Long)0L));
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(typecode);
			g2int_resumable_icp_push(remote_value_1);
			g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    result_1 = value_1;
		}
	    }
	    temp_1 = result_1;
	}
	else {
	    test = Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		test = g2int_resumable_icp_pop();
		temp = TRUEP(test);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? EQ(test,Qg2int_true) : EQ(typecode,FIX((SI_Long)1L))) {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    value = g2int_resumable_icp_pop();
		else if (SIMPLE_VECTOR_P(remote_value_1) && 
			EQ(ISVREF(remote_value_1,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    value = ISVREF(remote_value_1,(SI_Long)2L);
		else if (CONSP(remote_value_1))
		    value = M_CAR(remote_value_1);
		else
		    value = remote_value_1;
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    result_1 = g2int_resumable_icp_pop();
		else {
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			temp_1 = g2int_resumable_icp_pop();
			if (! !(FIXNUMP(temp_1) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				goto l1;
				break;
			      case 2:
				goto l2;
				break;
			      default:
				break;
			    }
		    }
		  l1:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp = TRUEP(test);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp ? EQ(test,Qg2int_true) : 
			    IFIX(ISVREF(G2int_current_icp_socket,
			    (SI_Long)22L)) >= (SI_Long)8L) {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) ||  
				!TRUEP(G2int_remote_value_known_typetag)) {
			    if (EQ(icp_suspend_1,
				    g2int_write_icp_byte(FIX((SI_Long)1L)))) {
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(FIX((SI_Long)1L));
				value_1 = G2int_icp_suspend;
				goto end_block;
			    }
			}
		    }
		    else if (EQ(icp_suspend_1,
			    g2int_write_icp_byte(FIX((SI_Long)1L)))) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(FIX((SI_Long)1L));
			value_1 = G2int_icp_suspend;
			goto end_block;
		    }
		  l2:
		    value_1 = g2int_write_icp_integer(value);
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(FIX((SI_Long)2L));
			value_1 = G2int_icp_suspend;
			goto end_block;
		    }
		    goto end_block;
		  end_block:
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(typecode);
			g2int_resumable_icp_push(remote_value_1);
			g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    result_1 = value_1;
		}
		temp_1 = result_1;
	    }
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp = TRUEP(test);
		}
		else
		    temp = TRUEP(Nil);
		if (temp ? EQ(test,Qg2int_true) : EQ(typecode,
			FIX((SI_Long)51L))) {
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			value = g2int_resumable_icp_pop();
		    else if (SIMPLE_VECTOR_P(remote_value_1) && 
			    EQ(ISVREF(remote_value_1,(SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			value = ISVREF(remote_value_1,(SI_Long)2L);
		    else if (CONSP(remote_value_1))
			value = M_CAR(remote_value_1);
		    else
			value = remote_value_1;
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			result_1 = g2int_resumable_icp_pop();
		    else {
			temp = resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil);
			if (temp);
			else {
			    temp_2 = ISVREF(G2int_current_icp_socket,
				    (SI_Long)21L);
			    temp_1 = ISVREF(G2int_current_icp_socket,
				    (SI_Long)22L);
			    temp = IFIX(FIXNUM_MIN(temp_2,temp_1)) >= 
				    (SI_Long)30L;
			}
			if (temp) {
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				temp_1 = g2int_resumable_icp_pop();
				if (! !(FIXNUMP(temp_1) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp_1) && FIXNUM_LE(temp_1,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp_1)) {
				      case 1:
					goto l1_1;
					break;
				      case 2:
					goto l2_1;
					break;
				      default:
					break;
				    }
			    }
			  l1_1:
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				test = g2int_resumable_icp_pop();
				temp = TRUEP(test);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp ? EQ(test,Qg2int_true) : 
				    IFIX(ISVREF(G2int_current_icp_socket,
				    (SI_Long)22L)) >= (SI_Long)8L) {
				if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) ||  
					!TRUEP(G2int_remote_value_known_typetag)) 
					    {
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(FIX((SI_Long)51L)))) 
						{
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					value_1 = G2int_icp_suspend;
					goto end_block_1;
				    }
				}
			    }
			    else if (EQ(icp_suspend_1,
				    g2int_write_icp_byte(FIX((SI_Long)51L)))) {
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(FIX((SI_Long)1L));
				value_1 = G2int_icp_suspend;
				goto end_block_1;
			    }
			  l2_1:
			    value_1 = g2int_write_icp_managed_long(value);
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(FIX((SI_Long)2L));
				value_1 = G2int_icp_suspend;
				goto end_block_1;
			    }
			    goto end_block_1;
			  end_block_1:
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(typecode);
				g2int_resumable_icp_push(remote_value_1);
				g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    result_1 = value_1;
			}
			else
			    result_1 = Nil;
		    }
		    temp_1 = result_1;
		}
		else {
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp = TRUEP(test);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp ? EQ(test,Qg2int_true) : EQ(typecode,
			    FIX((SI_Long)5L))) {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    value = g2int_resumable_icp_pop();
			else if (SIMPLE_VECTOR_P(remote_value_1) && 
				EQ(ISVREF(remote_value_1,(SI_Long)0L),
				Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			    value = ISVREF(remote_value_1,(SI_Long)2L);
			else if (CONSP(remote_value_1))
			    value = M_CAR(remote_value_1);
			else
			    value = remote_value_1;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    result_1 = g2int_resumable_icp_pop();
			else {
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				temp_1 = g2int_resumable_icp_pop();
				if (! !(FIXNUMP(temp_1) && 
					FIXNUM_LE(FIX((SI_Long)-128L),
					temp_1) && FIXNUM_LE(temp_1,
					FIX((SI_Long)127L))))
				    switch (INTEGER_TO_CHAR(temp_1)) {
				      case 1:
					goto l1_2;
					break;
				      case 2:
					goto l2_2;
					break;
				      default:
					break;
				    }
			    }
			  l1_2:
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				test = g2int_resumable_icp_pop();
				temp = TRUEP(test);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp ? EQ(test,Qg2int_true) : 
				    IFIX(ISVREF(G2int_current_icp_socket,
				    (SI_Long)22L)) >= (SI_Long)8L) {
				if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) ||  
					!TRUEP(G2int_remote_value_known_typetag)) 
					    {
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(FIX((SI_Long)5L)))) 
						{
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					value_1 = G2int_icp_suspend;
					goto end_block_2;
				    }
				}
			    }
			    else if (EQ(icp_suspend_1,
				    g2int_write_icp_byte(FIX((SI_Long)5L)))) {
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(FIX((SI_Long)1L));
				value_1 = G2int_icp_suspend;
				goto end_block_2;
			    }
			  l2_2:
			    value_1 = g2int_write_icp_integer(value);
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(FIX((SI_Long)2L));
				value_1 = G2int_icp_suspend;
				goto end_block_2;
			    }
			    goto end_block_2;
			  end_block_2:
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(typecode);
				g2int_resumable_icp_push(remote_value_1);
				g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    result_1 = value_1;
			}
			temp_1 = result_1;
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    test = g2int_resumable_icp_pop();
			    temp = TRUEP(test);
			}
			else
			    temp = TRUEP(Nil);
			if (temp ? EQ(test,Qg2int_true) : EQ(typecode,
				FIX((SI_Long)6L))) {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				value = g2int_resumable_icp_pop();
			    else if (SIMPLE_VECTOR_P(remote_value_1) && 
				    EQ(ISVREF(remote_value_1,(SI_Long)0L),
				    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
				value = ISVREF(remote_value_1,(SI_Long)2L);
			    else if (CONSP(remote_value_1))
				value = M_CAR(remote_value_1);
			    else
				value = remote_value_1;
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				result_1 = g2int_resumable_icp_pop();
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    test = g2int_resumable_icp_pop();
				    temp = TRUEP(test);
				}
				else
				    temp = TRUEP(Nil);
				if (temp ? EQ(test,Qg2int_true) : 
					IFIX(ISVREF(G2int_current_icp_socket,
					(SI_Long)22L)) >= (SI_Long)2L) {
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					temp_1 = g2int_resumable_icp_pop();
					if (! !(FIXNUMP(temp_1) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp_1) && 
						FIXNUM_LE(temp_1,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp_1)) {
					      case 1:
						goto l1_3;
						break;
					      case 2:
						goto l2_3;
						break;
					      default:
						break;
					    }
				    }
				  l1_3:
				    test = Nil;
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					test = g2int_resumable_icp_pop();
					temp = TRUEP(test);
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp ? EQ(test,Qg2int_true) : 
					    IFIX(ISVREF(G2int_current_icp_socket,
					    (SI_Long)22L)) >= (SI_Long)8L) {
					if ((resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) ||  
						!TRUEP(G2int_remote_value_known_typetag)) 
						    {
					    if (EQ(icp_suspend_1,
						    g2int_write_icp_byte(FIX((SI_Long)6L)))) 
							{
						g2int_resumable_icp_push(Qg2int_true);
						g2int_resumable_icp_push(FIX((SI_Long)1L));
						value_1 = G2int_icp_suspend;
						goto end_block_3;
					    }
					}
				    }
				    else if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(FIX((SI_Long)6L)))) 
						{
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					value_1 = G2int_icp_suspend;
					goto end_block_3;
				    }
				  l2_3:
				    value_1 = 
					    g2int_write_icp_managed_double_float(value);
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(FIX((SI_Long)2L));
					value_1 = G2int_icp_suspend;
					goto end_block_3;
				    }
				    goto end_block_3;
				  end_block_3:
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(value);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(typecode);
					g2int_resumable_icp_push(remote_value_1);
					g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
					return VALUES_1(G2int_icp_suspend);
				    }
				    result_1 = value_1;
				}
				else {
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					temp_1 = g2int_resumable_icp_pop();
					if (! !(FIXNUMP(temp_1) && 
						FIXNUM_LE(FIX((SI_Long)-128L),
						temp_1) && 
						FIXNUM_LE(temp_1,
						FIX((SI_Long)127L))))
					    switch (INTEGER_TO_CHAR(temp_1)) {
					      case 1:
						goto l1_4;
						break;
					      case 2:
						goto l2_4;
						break;
					      default:
						break;
					    }
				    }
				  l1_4:
				    if (EQ(icp_suspend_1,
					    g2int_write_icp_byte(FIX((SI_Long)2L)))) 
						{
					g2int_resumable_icp_push(FIX((SI_Long)1L));
					value_1 = G2int_icp_suspend;
					goto end_block_4;
				    }
				  l2_4:
				    value_1 = g2int_write_icp_float(value);
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(FIX((SI_Long)2L));
					value_1 = G2int_icp_suspend;
					goto end_block_4;
				    }
				    goto end_block_4;
				  end_block_4:
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(value);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(typecode);
					g2int_resumable_icp_push(remote_value_1);
					g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
					return VALUES_1(G2int_icp_suspend);
				    }
				    result_1 = value_1;
				}
			    }
			    temp_1 = result_1;
			}
			else {
			    test = Nil;
			    if (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) {
				test = g2int_resumable_icp_pop();
				temp = TRUEP(test);
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp ? EQ(test,Qg2int_true) : EQ(typecode,
				    FIX((SI_Long)3L))) {
				if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				    value = g2int_resumable_icp_pop();
				else if (SIMPLE_VECTOR_P(remote_value_1) 
					&& EQ(ISVREF(remote_value_1,
					(SI_Long)0L),
					Qg2_defstruct_structure_name_gsi_instance_g2_struct))
				    value = ISVREF(remote_value_1,(SI_Long)2L);
				else if (CONSP(remote_value_1))
				    value = M_CAR(remote_value_1);
				else
				    value = remote_value_1;
				if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				    result_1 = g2int_resumable_icp_pop();
				else {
				    value_1 = 
					    g2int_write_icp_symbol_as_value_type(value);
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(value);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(Qg2int_false);
					g2int_resumable_icp_push(typecode);
					g2int_resumable_icp_push(remote_value_1);
					g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
					return VALUES_1(G2int_icp_suspend);
				    }
				    result_1 = value_1;
				}
				temp_1 = result_1;
			    }
			    else {
				test = Nil;
				if (resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) {
				    test = g2int_resumable_icp_pop();
				    temp = TRUEP(test);
				}
				else
				    temp = TRUEP(Nil);
				if (temp ? EQ(test,Qg2int_true) : 
					EQ(typecode,FIX((SI_Long)4L))) {
				    if ((resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) &&  
					    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
					value = g2int_resumable_icp_pop();
				    else {
					if (SIMPLE_VECTOR_P(remote_value_1) 
						&& 
						EQ(ISVREF(remote_value_1,
						(SI_Long)0L),
						Qg2_defstruct_structure_name_gsi_instance_g2_struct))
					    temp_1 = ISVREF(remote_value_1,
						    (SI_Long)2L);
					else if (CONSP(remote_value_1))
					    temp_1 = M_CAR(remote_value_1);
					else
					    temp_1 = remote_value_1;
					value = 
						g2int_convert_gsi_value_to_value(temp_1);
				    }
				    if ((resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) &&  
					    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
					result_1 = g2int_resumable_icp_pop();
				    else {
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    temp_1 = g2int_resumable_icp_pop();
					    if (! !(FIXNUMP(temp_1) && 
						    FIXNUM_LE(FIX((SI_Long)-128L),
						    temp_1) && 
						    FIXNUM_LE(temp_1,
						    FIX((SI_Long)127L))))
						switch (INTEGER_TO_CHAR(temp_1)) 
							    {
						  case 1:
						    goto l1_5;
						    break;
						  case 2:
						    goto l2_5;
						    break;
						  default:
						    break;
						}
					}
				      l1_5:
					test = Nil;
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    test = g2int_resumable_icp_pop();
					    temp = TRUEP(test);
					}
					else
					    temp = TRUEP(Nil);
					if (temp ? EQ(test,Qg2int_true) : 
						IFIX(ISVREF(G2int_current_icp_socket,
						(SI_Long)22L)) >= 
						    (SI_Long)8L) {
					    if ((resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) ||  
						    !TRUEP(G2int_remote_value_known_typetag)) 
							{
						if (EQ(icp_suspend_1,
							g2int_write_icp_byte(FIX((SI_Long)4L)))) 
							    {
						    g2int_resumable_icp_push(Qg2int_true);
						    g2int_resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_5;
						}
					    }
					}
					else if (EQ(icp_suspend_1,
						g2int_write_icp_byte(FIX((SI_Long)4L)))) 
						    {
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(FIX((SI_Long)1L));
					    value_1 = G2int_icp_suspend;
					    goto end_block_5;
					}
				      l2_5:
					value_1 = 
						g2int_write_icp_text_string(value);
					if (EQ(icp_suspend_1,value_1)) {
					    g2int_resumable_icp_push(FIX((SI_Long)2L));
					    value_1 = G2int_icp_suspend;
					    goto end_block_5;
					}
					goto end_block_5;
				      end_block_5:
					if (EQ(icp_suspend_1,value_1)) {
					    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					    g2int_resumable_icp_push(value);
					    g2int_resumable_icp_push(Qg2int_true);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(Qg2int_false);
					    g2int_resumable_icp_push(typecode);
					    g2int_resumable_icp_push(remote_value_1);
					    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
					    return VALUES_1(G2int_icp_suspend);
					}
					result_1 = value_1;
				    }
				    if (SIMPLE_VECTOR_P(remote_value_1) && 
					    EQ(ISVREF(remote_value_1,
					    (SI_Long)0L),
					    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
					temp_1 = ISVREF(remote_value_1,
						(SI_Long)2L);
				    else if (CONSP(remote_value_1))
					temp_1 = M_CAR(remote_value_1);
				    else
					temp_1 = remote_value_1;
				    if (STRINGP(temp_1))
					g2int_reclaim_wide_string(value);
				    temp_1 = result_1;
				}
				else {
				    test = Nil;
				    if (resumable_icp_state_1 ? 
					    TRUEP(G2int_starresumable_icp_statestar) 
					    : TRUEP(Nil)) {
					test = g2int_resumable_icp_pop();
					temp = TRUEP(test);
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp ? EQ(test,Qg2int_true) : 
					    EQ(typecode,FIX((SI_Long)11L))) {
					if ((resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) &&  
						!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
					    value = g2int_resumable_icp_pop();
					else if (SIMPLE_VECTOR_P(remote_value_1) 
						&& 
						EQ(ISVREF(remote_value_1,
						(SI_Long)0L),
						Qg2_defstruct_structure_name_gsi_instance_g2_struct))
					    value = ISVREF(remote_value_1,
						    (SI_Long)2L);
					else if (CONSP(remote_value_1))
					    value = M_CAR(remote_value_1);
					else
					    value = remote_value_1;
					if ((resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) &&  
						!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
					    result_1 = 
						    g2int_resumable_icp_pop();
					else {
					    test = Nil;
					    if (resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) {
						test = 
							g2int_resumable_icp_pop();
						temp = TRUEP(test);
					    }
					    else
						temp = TRUEP(Nil);
					    if (temp ? EQ(test,
						    Qg2int_true) : 
						    IFIX(ISVREF(G2int_current_icp_socket,
						    (SI_Long)22L)) >= 
						    (SI_Long)14L) {
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    temp_1 = 
							    g2int_resumable_icp_pop();
						    if (! 
							    !(FIXNUMP(temp_1) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp_1) && 
							    FIXNUM_LE(temp_1,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp_1)) 
								    {
							  case 1:
							    goto l1_6;
							    break;
							  case 2:
							    goto l2_6;
							    break;
							  default:
							    break;
							}
						}
					      l1_6:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    test = 
							    g2int_resumable_icp_pop();
						    temp = TRUEP(test);
						}
						else
						    temp = TRUEP(Nil);
						if (temp ? EQ(test,
							Qg2int_true) : 
							IFIX(ISVREF(G2int_current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(G2int_remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								g2int_write_icp_byte(FIX((SI_Long)11L)))) 
								    {
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    G2int_icp_suspend;
							    goto end_block_6;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							g2int_write_icp_byte(FIX((SI_Long)11L)))) 
							    {
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_6;
						}
					      l2_6:
						value_1 = 
							g2int_write_icp_wide_string(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_6;
						}
						goto end_block_6;
					      end_block_6:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(Qg2int_true);
						    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
						    g2int_resumable_icp_push(value);
						    g2int_resumable_icp_push(Qg2int_true);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(typecode);
						    g2int_resumable_icp_push(remote_value_1);
						    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
						    return VALUES_1(G2int_icp_suspend);
						}
						result_1 = value_1;
					    }
					    else {
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    temp_1 = 
							    g2int_resumable_icp_pop();
						    if (! 
							    !(FIXNUMP(temp_1) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp_1) && 
							    FIXNUM_LE(temp_1,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp_1)) 
								    {
							  case 1:
							    goto l1_7;
							    break;
							  case 2:
							    goto l2_7;
							    break;
							  default:
							    break;
							}
						}
					      l1_7:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    test = 
							    g2int_resumable_icp_pop();
						    temp = TRUEP(test);
						}
						else
						    temp = TRUEP(Nil);
						if (temp ? EQ(test,
							Qg2int_true) : 
							IFIX(ISVREF(G2int_current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(G2int_remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								g2int_write_icp_byte(FIX((SI_Long)4L)))) 
								    {
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    G2int_icp_suspend;
							    goto end_block_7;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							g2int_write_icp_byte(FIX((SI_Long)4L)))) 
							    {
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_7;
						}
					      l2_7:
						value_1 = 
							g2int_write_icp_text_string(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_7;
						}
						goto end_block_7;
					      end_block_7:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
						    g2int_resumable_icp_push(value);
						    g2int_resumable_icp_push(Qg2int_true);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(typecode);
						    g2int_resumable_icp_push(remote_value_1);
						    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
						    return VALUES_1(G2int_icp_suspend);
						}
						result_1 = value_1;
					    }
					}
					temp_1 = result_1;
				    }
				    else {
					test = Nil;
					if (resumable_icp_state_1 ? 
						TRUEP(G2int_starresumable_icp_statestar) 
						: TRUEP(Nil)) {
					    test = g2int_resumable_icp_pop();
					    temp = TRUEP(test);
					}
					else
					    temp = TRUEP(Nil);
					if (temp ? EQ(test,Qg2int_true) : 
						EQ(typecode,
						    FIX((SI_Long)9L))) {
					    if ((resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) &&  
						    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
						value = 
							g2int_resumable_icp_pop();
					    else if (SIMPLE_VECTOR_P(remote_value_1) 
						    && 
						    EQ(ISVREF(remote_value_1,
						    (SI_Long)0L),
						    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
						value = 
							ISVREF(remote_value_1,
							(SI_Long)2L);
					    else if (CONSP(remote_value_1))
						value = M_CAR(remote_value_1);
					    else
						value = remote_value_1;
					    if ((resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) &&  
						    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
						result_1 = 
							g2int_resumable_icp_pop();
					    else {
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    temp_1 = 
							    g2int_resumable_icp_pop();
						    if (! 
							    !(FIXNUMP(temp_1) 
							    && 
							    FIXNUM_LE(FIX((SI_Long)-128L),
							    temp_1) && 
							    FIXNUM_LE(temp_1,
							    FIX((SI_Long)127L))))
							switch (INTEGER_TO_CHAR(temp_1)) 
								    {
							  case 1:
							    goto l1_8;
							    break;
							  case 2:
							    goto l2_8;
							    break;
							  default:
							    break;
							}
						}
					      l1_8:
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    test = 
							    g2int_resumable_icp_pop();
						    temp = TRUEP(test);
						}
						else
						    temp = TRUEP(Nil);
						if (temp ? EQ(test,
							Qg2int_true) : 
							IFIX(ISVREF(G2int_current_icp_socket,
							(SI_Long)22L)) >= 
							(SI_Long)8L) {
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
							    ||  
							    !TRUEP(G2int_remote_value_known_typetag)) 
								{
							if (EQ(icp_suspend_1,
								g2int_write_icp_byte(FIX((SI_Long)8L)))) 
								    {
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    G2int_icp_suspend;
							    goto end_block_8;
							}
						    }
						}
						else if (EQ(icp_suspend_1,
							g2int_write_icp_byte(FIX((SI_Long)8L)))) 
							    {
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(FIX((SI_Long)1L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_8;
						}
					      l2_8:
						value_1 = 
							g2int_write_icp_fixnum(value);
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(FIX((SI_Long)2L));
						    value_1 = 
							    G2int_icp_suspend;
						    goto end_block_8;
						}
						goto end_block_8;
					      end_block_8:
						if (EQ(icp_suspend_1,
							    value_1)) {
						    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
						    g2int_resumable_icp_push(value);
						    g2int_resumable_icp_push(Qg2int_true);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(Qg2int_false);
						    g2int_resumable_icp_push(typecode);
						    g2int_resumable_icp_push(remote_value_1);
						    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
						    return VALUES_1(G2int_icp_suspend);
						}
						result_1 = value_1;
					    }
					    temp_1 = result_1;
					}
					else {
					    test = Nil;
					    if (resumable_icp_state_1 ? 
						    TRUEP(G2int_starresumable_icp_statestar) 
						    : TRUEP(Nil)) {
						test = 
							g2int_resumable_icp_pop();
						temp = TRUEP(test);
					    }
					    else
						temp = TRUEP(Nil);
					    if (temp ? EQ(test,
						    Qg2int_true) : 
						    EQ(typecode,
						    FIX((SI_Long)50L))) {
						value = 
							(resumable_icp_state_1 
							? 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) &&  
							!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
							? 
							g2int_resumable_icp_pop() 
							: remote_value_1;
						if ((resumable_icp_state_1 
							? 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) &&  
							!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
						    result_1 = 
							    g2int_resumable_icp_pop();
						else {
						    test = Nil;
						    if (resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) {
							test = 
								g2int_resumable_icp_pop();
							temp = TRUEP(test);
						    }
						    else
							temp = TRUEP(Nil);
						    if (temp ? EQ(test,
							    Qg2int_true) : 
							    IFIX(ISVREF(G2int_current_icp_socket,
							    (SI_Long)22L)) 
							    >= (SI_Long)8L) {
							if (resumable_icp_state_1 
								? 
								TRUEP(G2int_starresumable_icp_statestar) 
								: TRUEP(Nil)) {
							    temp_1 = 
								    g2int_resumable_icp_pop();
							    if (! 
								    !(FIXNUMP(temp_1) 
								    && 
								    FIXNUM_LE(FIX((SI_Long)-128L),
								    temp_1) 
								    && 
								    FIXNUM_LE(temp_1,
								    FIX((SI_Long)127L))))
								switch (INTEGER_TO_CHAR(temp_1)) 
									    {
								  case 1:
								    goto l1_9;
								    break;
								  case 2:
								    goto l2_9;
								    break;
								  default:
								    break;
								}
							}
						      l1_9:
							test = Nil;
							if (resumable_icp_state_1 
								? 
								TRUEP(G2int_starresumable_icp_statestar) 
								: TRUEP(Nil)) {
							    test = 
								    g2int_resumable_icp_pop();
							    temp = TRUEP(test);
							}
							else
							    temp = TRUEP(Nil);
							if (temp ? EQ(test,
								Qg2int_true) 
								: 
								IFIX(ISVREF(G2int_current_icp_socket,
								(SI_Long)22L)) 
								>= 
								    (SI_Long)8L) {
							    if ((resumable_icp_state_1 
								    ? 
								    TRUEP(G2int_starresumable_icp_statestar) 
								    : 
								    TRUEP(Nil)) 
								    ||  
								    !TRUEP(G2int_remote_value_known_typetag)) 
									{
								if (EQ(icp_suspend_1,
									g2int_write_icp_byte(FIX((SI_Long)50L)))) 
									    {
								    g2int_resumable_icp_push(Qg2int_true);
								    g2int_resumable_icp_push(FIX((SI_Long)1L));
								    value_1 
									    = 
									    G2int_icp_suspend;
								    goto end_block_9;
								}
							    }
							}
							else if (EQ(icp_suspend_1,
								g2int_write_icp_byte(FIX((SI_Long)50L)))) 
								    {
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(FIX((SI_Long)1L));
							    value_1 = 
								    G2int_icp_suspend;
							    goto end_block_9;
							}
						      l2_9:
							value_1 = 
								g2int_write_icp_evaluation_structure(value);
							if (EQ(icp_suspend_1,
								value_1)) {
							    g2int_resumable_icp_push(FIX((SI_Long)2L));
							    value_1 = 
								    G2int_icp_suspend;
							    goto end_block_9;
							}
							goto end_block_9;
						      end_block_9:
							if (EQ(icp_suspend_1,
								value_1)) {
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
							    g2int_resumable_icp_push(value);
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(typecode);
							    g2int_resumable_icp_push(remote_value_1);
							    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
							    return VALUES_1(G2int_icp_suspend);
							}
							result_1 = value_1;
						    }
						    else {
							value_1 = 
								g2int_write_icp_byte(FIX((SI_Long)0L));
							if (EQ(icp_suspend_1,
								value_1)) {
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
							    g2int_resumable_icp_push(value);
							    g2int_resumable_icp_push(Qg2int_true);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(typecode);
							    g2int_resumable_icp_push(remote_value_1);
							    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
							    return VALUES_1(G2int_icp_suspend);
							}
							result_1 = value_1;
						    }
						}
						temp_1 = result_1;
					    }
					    else {
						test = Nil;
						if (resumable_icp_state_1 ?
							 
							TRUEP(G2int_starresumable_icp_statestar) 
							: TRUEP(Nil)) {
						    test = 
							    g2int_resumable_icp_pop();
						    temp = TRUEP(test);
						}
						else
						    temp = TRUEP(Nil);
						if (temp ? EQ(test,
							Qg2int_true) : 
							EQ(typecode,
							FIX((SI_Long)49L))) {
						    value = 
							    (resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
							    &&  
							    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
							    ? 
							    g2int_resumable_icp_pop() 
							    : remote_value_1;
						    if ((resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
							    &&  
							    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
							result_1 = 
								g2int_resumable_icp_pop();
						    else {
							test = Nil;
							if (resumable_icp_state_1 
								? 
								TRUEP(G2int_starresumable_icp_statestar) 
								: TRUEP(Nil)) {
							    test = 
								    g2int_resumable_icp_pop();
							    temp = TRUEP(test);
							}
							else
							    temp = TRUEP(Nil);
							if (temp ? EQ(test,
								Qg2int_true) 
								: 
								IFIX(ISVREF(G2int_current_icp_socket,
								(SI_Long)22L)) 
								>= 
								    (SI_Long)8L) {
							    value_1 = 
								    g2int_write_icp_evaluation_sequence(value);
							    if (EQ(icp_suspend_1,
								    value_1)) {
								g2int_resumable_icp_push(Qg2int_true);
								g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
								g2int_resumable_icp_push(value);
								g2int_resumable_icp_push(Qg2int_true);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(typecode);
								g2int_resumable_icp_push(remote_value_1);
								g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
								return VALUES_1(G2int_icp_suspend);
							    }
							    result_1 = value_1;
							}
							else {
							    value_1 = 
								    g2int_write_icp_byte(FIX((SI_Long)0L));
							    if (EQ(icp_suspend_1,
								    value_1)) {
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
								g2int_resumable_icp_push(value);
								g2int_resumable_icp_push(Qg2int_true);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(Qg2int_false);
								g2int_resumable_icp_push(typecode);
								g2int_resumable_icp_push(remote_value_1);
								g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
								return VALUES_1(G2int_icp_suspend);
							    }
							    result_1 = value_1;
							}
						    }
						    temp_1 = result_1;
						}
						else {
						    test = Nil;
						    if (resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) {
							test = 
								g2int_resumable_icp_pop();
							temp = TRUEP(test);
						    }
						    else
							temp = TRUEP(Nil);
						    if (temp ? EQ(test,
							    Qg2int_true) : 
							    EQ(typecode,
							    Qg2int_item)) {
							value = 
								(resumable_icp_state_1 
								? 
								TRUEP(G2int_starresumable_icp_statestar) 
								: 
								TRUEP(Nil)) 
								&&  
								!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
								? 
								g2int_resumable_icp_pop() 
								: 
								remote_value_1;
							if ((resumable_icp_state_1 
								? 
								TRUEP(G2int_starresumable_icp_statestar) 
								: 
								TRUEP(Nil)) 
								&&  
								!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
							    result_1 = 
								    g2int_resumable_icp_pop();
							else {
							    test = Nil;
							    if (resumable_icp_state_1 
								    ? 
								    TRUEP(G2int_starresumable_icp_statestar) 
								    : 
								    TRUEP(Nil)) 
									{
								test = 
									g2int_resumable_icp_pop();
								temp = 
									TRUEP(test);
							    }
							    else
								temp = 
									TRUEP(Nil);
							    if (temp ? 
								    EQ(test,
								    Qg2int_true) 
								    : 
								    IFIX(ISVREF(G2int_current_icp_socket,
								    (SI_Long)22L)) 
								    >= 
								    (SI_Long)8L) 
									{
								value_1 = 
									g2int_write_icp_item(value);
								if (EQ(icp_suspend_1,
									value_1)) 
									    {
								    g2int_resumable_icp_push(Qg2int_true);
								    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
								    g2int_resumable_icp_push(value);
								    g2int_resumable_icp_push(Qg2int_true);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(typecode);
								    g2int_resumable_icp_push(remote_value_1);
								    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
								    return VALUES_1(G2int_icp_suspend);
								}
								result_1 = 
									value_1;
							    }
							    else {
								value_1 = 
									g2int_write_icp_byte(FIX((SI_Long)0L));
								if (EQ(icp_suspend_1,
									value_1)) 
									    {
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
								    g2int_resumable_icp_push(value);
								    g2int_resumable_icp_push(Qg2int_true);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(Qg2int_false);
								    g2int_resumable_icp_push(typecode);
								    g2int_resumable_icp_push(remote_value_1);
								    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
								    return VALUES_1(G2int_icp_suspend);
								}
								result_1 = 
									value_1;
							    }
							}
							temp_1 = result_1;
						    }
						    else if ((resumable_icp_state_1 
							    ? 
							    TRUEP(G2int_starresumable_icp_statestar) 
							    : TRUEP(Nil)) 
								|| T) {
							value_1 = 
								g2int_write_icp_byte(FIX((SI_Long)0L));
							if (EQ(icp_suspend_1,
								value_1)) {
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(Qg2int_false);
							    g2int_resumable_icp_push(typecode);
							    g2int_resumable_icp_push(remote_value_1);
							    g2int_resumable_icp_push(Qg2int_write_icp_remote_value_1);
							    return VALUES_1(G2int_icp_suspend);
							}
							temp_1 = value_1;
						    }
						    else
							temp_1 = Qnil;
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp_1);
}

Object G2int_identifying_attribute_count_for_item_new_copy = UNBOUND;

static Object Qg2int_context;      /* context */

static Object string_constant_1;   /* "Unknown type tag ~a in READ-ICP-REMOTE-VALUE" */

static Object Qg2int_read_icp_remote_value_1;  /* read-icp-remote-value-1 */

/* READ-ICP-REMOTE-VALUE-1 */
Object g2int_read_icp_remote_value_1()
{
    Object value_p, temp, value, symbol, type_tag, string_1;
    Object resumable_icp_state_1, icp_suspend_1, top, key, test, value_1;
    Object value_2, arg1, arg2, arg3, arg4, arg5, arg6, arg1_1;
    char temp_1;

    x_note_fn_call(44,70);
    if (G2int_disable_resumability) {
	value_p = Nil;
	if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)8L) {
	    temp = G2int_remote_value_known_typetag;
	    if (temp);
	    else
		temp = g2int_peek_icp_byte();
	}
	else
	    temp = g2int_peek_icp_byte();
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    value = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 60:
	      case 61:
	      case 74:
	      case 62:
	      case 64:
	      case 65:
	      case 66:
	      case 63:
		value_p = T;
		value = g2int_read_icp_item();
		break;
	      case 70:
	      case 73:
	      case 71:
	      case 72:
	      case 75:
	      case 3:
		symbol = g2int_read_icp_symbol_as_value_type();
		value = G2int_gsi_remote_value_creates_instance_p ? 
			g2int_make_gsi_instance(6,
			G2int_gsi_symbol_type_tag,symbol,Nil,Nil,Nil,
			G2int_identifying_attribute_count_for_item_new_copy 
			? Qg2int_context : 
			g2int_default_owner_for_gsi_objects()) : symbol;
		break;
	      case 49:
	      case 67:
		value = g2int_read_icp_evaluation_sequence();
		break;
	      default:
		value = Nil;
		break;
	    }
	if (value || value_p)
	    temp = value;
	else {
	    if (IFIX(ISVREF(G2int_current_icp_socket,(SI_Long)21L)) >= 
		    (SI_Long)8L) {
		type_tag = G2int_remote_value_known_typetag;
		if (type_tag);
		else
		    type_tag = g2int_read_icp_byte();
	    }
	    else
		type_tag = g2int_read_icp_byte();
	    temp = type_tag;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		temp = g2int_icp_error_internal(Qerror,string_constant_1,
			type_tag,Nil,Nil);
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = G2int_gsi_remote_value_creates_instance_p ? 
			    g2int_make_gsi_instance(6,Nil,Nil,Nil,Nil,Nil,
			    G2int_identifying_attribute_count_for_item_new_copy 
			    ? Qg2int_context : 
			    g2int_default_owner_for_gsi_objects()) : Nil;
		    break;
		  case 5:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_integer();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_logical_type_tag,temp,Nil,Nil,
				Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = G2int_gsi_remote_value_conses_logical_p ? 
				g2int_gensym_cons_1(g2int_read_icp_integer(),
				Qg2int_truth_value) : g2int_read_icp_integer();
		    break;
		  case 1:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_fixnum();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_integer_type_tag,temp,Nil,Nil,
				Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_fixnum();
		    break;
		  case 51:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_managed_long();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_long_type_tag,temp,Nil,Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_managed_long();
		    break;
		  case 6:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_managed_double_float();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_64bit_float_type_tag,temp,Nil,
				Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_managed_double_float();
		    break;
		  case 2:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_float();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_64bit_float_type_tag,temp,Nil,
				Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_float();
		    break;
		  case 4:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = 
				g2int_convert_value_to_gsi_value(g2int_read_icp_text_string());
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_string_type_tag,temp,Nil,Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = 
				g2int_convert_value_to_gsi_value(g2int_read_icp_text_string());
		    break;
		  case 68:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			string_1 = g2int_read_icp_gensym_string();
			temp = g2int_gensym_string_to_wide_string(string_1);
			g2int_reclaim_gensym_string(string_1);
			temp = g2int_convert_value_to_gsi_value(temp);
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_string_type_tag,temp,Nil,Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else {
			string_1 = g2int_read_icp_gensym_string();
			temp = g2int_gensym_string_to_wide_string(string_1);
			g2int_reclaim_gensym_string(string_1);
			temp = g2int_convert_value_to_gsi_value(temp);
		    }
		    break;
		  case 69:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = 
				g2int_convert_value_to_gsi_value(g2int_read_icp_wide_string());
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_string_type_tag,temp,Nil,Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = 
				g2int_convert_value_to_gsi_value(g2int_read_icp_wide_string());
		    break;
		  case 11:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_wide_string();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_unsigned_short_vector_type_tag,
				temp,Nil,Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_wide_string();
		    break;
		  case 50:
		    temp = g2int_read_icp_evaluation_structure();
		    break;
		  case 8:
		    if (G2int_gsi_remote_value_creates_instance_p) {
			temp = g2int_read_icp_fixnum();
			temp = g2int_make_gsi_instance(6,
				G2int_gsi_item_handle_type_tag,temp,Nil,
				Nil,Nil,
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects());
		    }
		    else
			temp = g2int_read_icp_fixnum();
		    break;
		  default:
		    temp = g2int_icp_error_internal(Qerror,
			    string_constant_1,type_tag,Nil,Nil);
		    break;
		}
	}
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_remote_value_1,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_remote_value_1,top,Nil);
	}
	value_p = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    value = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		key = g2int_resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)21L)) >= (SI_Long)8L) {
		    value_1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : 
			    G2int_remote_value_known_typetag;
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && value_1)
			key = value_1;
		    else {
			value_2 = g2int_peek_icp_byte();
			if (EQ(icp_suspend_1,value_2)) {
			    g2int_resumable_icp_push(value_1);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			key = value_2;
		    }
		}
		else {
		    value_1 = g2int_peek_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    key = value_1;
		}
	    }
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		value = Nil;
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 60:
		  case 61:
		  case 74:
		  case 62:
		  case 64:
		  case 65:
		  case 66:
		  case 63:
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)))
			value_p = T;
		    value_1 = g2int_read_icp_item();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    value = value_1;
		    break;
		  case 70:
		  case 73:
		  case 71:
		  case 72:
		  case 75:
		  case 3:
		    if ((resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			symbol = g2int_resumable_icp_pop();
		    else {
			value_1 = g2int_read_icp_symbol_as_value_type();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			symbol = value_1;
		    }
		    value = G2int_gsi_remote_value_creates_instance_p ? 
			    g2int_make_gsi_instance(6,
			    G2int_gsi_symbol_type_tag,symbol,Nil,Nil,Nil,
			    G2int_identifying_attribute_count_for_item_new_copy 
			    ? Qg2int_context : 
			    g2int_default_owner_for_gsi_objects()) : symbol;
		    break;
		  case 49:
		  case 67:
		    value_1 = g2int_read_icp_evaluation_sequence();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    value = value_1;
		    break;
		  default:
		    value = Nil;
		    break;
		}
	}
	if ( !(resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) && 
		(value || value_p))
	    temp = value;
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		type_tag = g2int_resumable_icp_pop();
	    else {
		test = Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
		    test = g2int_resumable_icp_pop();
		    temp_1 = TRUEP(test);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? EQ(test,Qg2int_true) : 
			IFIX(ISVREF(G2int_current_icp_socket,
			(SI_Long)21L)) >= (SI_Long)8L) {
		    value_1 = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : 
			    G2int_remote_value_known_typetag;
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && value_1)
			type_tag = value_1;
		    else {
			value_2 = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value_2)) {
			    g2int_resumable_icp_push(value_1);
			    g2int_resumable_icp_push(Qg2int_true);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			type_tag = value_2;
		    }
		}
		else {
		    value_1 = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_false);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    type_tag = value_1;
		}
	    }
	    key = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : type_tag;
	    temp = key;
	    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L)))) {
		value_1 = g2int_icp_error_internal(Qerror,
			string_constant_1,type_tag,Nil,Nil);
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(key);
		    g2int_resumable_icp_push(type_tag);
		    g2int_resumable_icp_push(value);
		    g2int_resumable_icp_push(value_p);
		    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
		    return VALUES_1(G2int_icp_suspend);
		}
		temp = value_1;
	    }
	    else
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    temp = G2int_gsi_remote_value_creates_instance_p ? 
			    g2int_make_gsi_instance(6,Nil,Nil,Nil,Nil,Nil,
			    G2int_identifying_attribute_count_for_item_new_copy 
			    ? Qg2int_context : 
			    g2int_default_owner_for_gsi_objects()) : Nil;
		    break;
		  case 5:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_logical_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_integer();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			test = Nil;
			if (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) {
			    test = g2int_resumable_icp_pop();
			    temp_1 = TRUEP(test);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? EQ(test,Qg2int_true) : 
				TRUEP(G2int_gsi_remote_value_conses_logical_p)) 
				    {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				arg1 = g2int_resumable_icp_pop();
			    else {
				value_1 = g2int_read_icp_integer();
				if (EQ(icp_suspend_1,value_1)) {
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(key);
				    g2int_resumable_icp_push(type_tag);
				    g2int_resumable_icp_push(value);
				    g2int_resumable_icp_push(value_p);
				    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				    return VALUES_1(G2int_icp_suspend);
				}
				arg1 = value_1;
			    }
			    arg2 = (resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				    ? g2int_resumable_icp_pop() : 
				    Qg2int_truth_value;
			    temp = g2int_gensym_cons_1(arg1,arg2);
			}
			else {
			    value_1 = g2int_read_icp_integer();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    temp = value_1;
			}
		    }
		    break;
		  case 1:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_integer_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_fixnum();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_fixnum();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  case 51:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_long_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_managed_long();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_managed_long();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  case 6:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_64bit_float_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_managed_double_float();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_managed_double_float();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  case 2:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_64bit_float_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_float();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_float();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  case 4:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_string_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				arg1_1 = g2int_resumable_icp_pop();
			    else {
				value_1 = g2int_read_icp_text_string();
				if (EQ(icp_suspend_1,value_1)) {
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(arg1);
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(key);
				    g2int_resumable_icp_push(type_tag);
				    g2int_resumable_icp_push(value);
				    g2int_resumable_icp_push(value_p);
				    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				    return VALUES_1(G2int_icp_suspend);
				}
				arg1_1 = value_1;
			    }
			    arg2 = g2int_convert_value_to_gsi_value(arg1_1);
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg1 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_text_string();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg1 = value_1;
			}
			temp = g2int_convert_value_to_gsi_value(arg1);
		    }
		    break;
		  case 68:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_string_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				arg1_1 = g2int_resumable_icp_pop();
			    else {
				if ((resumable_icp_state_1 ? 
					TRUEP(G2int_starresumable_icp_statestar) 
					: TRUEP(Nil)) &&  
					!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				    string_1 = g2int_resumable_icp_pop();
				else {
				    value_1 = g2int_read_icp_gensym_string();
				    if (EQ(icp_suspend_1,value_1)) {
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
					g2int_resumable_icp_push(arg1);
					g2int_resumable_icp_push(Qg2int_true);
					g2int_resumable_icp_push(key);
					g2int_resumable_icp_push(type_tag);
					g2int_resumable_icp_push(value);
					g2int_resumable_icp_push(value_p);
					g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
					return VALUES_1(G2int_icp_suspend);
				    }
				    string_1 = value_1;
				}
				temp = 
					g2int_gensym_string_to_wide_string(string_1);
				g2int_reclaim_gensym_string(string_1);
				arg1_1 = temp;
			    }
			    arg2 = g2int_convert_value_to_gsi_value(arg1_1);
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg1 = g2int_resumable_icp_pop();
			else {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				string_1 = g2int_resumable_icp_pop();
			    else {
				value_1 = g2int_read_icp_gensym_string();
				if (EQ(icp_suspend_1,value_1)) {
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(Qg2int_false);
				    g2int_resumable_icp_push(key);
				    g2int_resumable_icp_push(type_tag);
				    g2int_resumable_icp_push(value);
				    g2int_resumable_icp_push(value_p);
				    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				    return VALUES_1(G2int_icp_suspend);
				}
				string_1 = value_1;
			    }
			    temp = 
				    g2int_gensym_string_to_wide_string(string_1);
			    g2int_reclaim_gensym_string(string_1);
			    arg1 = temp;
			}
			temp = g2int_convert_value_to_gsi_value(arg1);
		    }
		    break;
		  case 69:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_string_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    if ((resumable_icp_state_1 ? 
				    TRUEP(G2int_starresumable_icp_statestar) 
				    : TRUEP(Nil)) &&  
				    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
				arg1_1 = g2int_resumable_icp_pop();
			    else {
				value_1 = g2int_read_icp_wide_string();
				if (EQ(icp_suspend_1,value_1)) {
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				    g2int_resumable_icp_push(arg1);
				    g2int_resumable_icp_push(Qg2int_true);
				    g2int_resumable_icp_push(key);
				    g2int_resumable_icp_push(type_tag);
				    g2int_resumable_icp_push(value);
				    g2int_resumable_icp_push(value_p);
				    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				    return VALUES_1(G2int_icp_suspend);
				}
				arg1_1 = value_1;
			    }
			    arg2 = g2int_convert_value_to_gsi_value(arg1_1);
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg1 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_wide_string();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(Qg2int_false);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg1 = value_1;
			}
			temp = g2int_convert_value_to_gsi_value(arg1);
		    }
		    break;
		  case 11:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_unsigned_short_vector_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_wide_string();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_wide_string();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  case 50:
		    value_1 = g2int_read_icp_evaluation_structure();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(type_tag);
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value_1;
		    break;
		  case 8:
		    test = Nil;
		    if (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) {
			test = g2int_resumable_icp_pop();
			temp_1 = TRUEP(test);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1 ? EQ(test,Qg2int_true) : 
			    TRUEP(G2int_gsi_remote_value_creates_instance_p)) {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_gsi_item_handle_type_tag;
			if ((resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
			    arg2 = g2int_resumable_icp_pop();
			else {
			    value_1 = g2int_read_icp_fixnum();
			    if (EQ(icp_suspend_1,value_1)) {
				g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
				g2int_resumable_icp_push(arg1);
				g2int_resumable_icp_push(Qg2int_true);
				g2int_resumable_icp_push(key);
				g2int_resumable_icp_push(type_tag);
				g2int_resumable_icp_push(value);
				g2int_resumable_icp_push(value_p);
				g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
				return VALUES_1(G2int_icp_suspend);
			    }
			    arg2 = value_1;
			}
			arg3 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg4 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg5 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : Nil;
			arg6 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				G2int_identifying_attribute_count_for_item_new_copy 
				? Qg2int_context : 
				g2int_default_owner_for_gsi_objects();
			temp = g2int_make_gsi_instance(6,arg1,arg2,arg3,
				arg4,arg5,arg6);
		    }
		    else {
			value_1 = g2int_read_icp_fixnum();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(Qg2int_false);
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(type_tag);
			    g2int_resumable_icp_push(value);
			    g2int_resumable_icp_push(value_p);
			    g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			    return VALUES_1(G2int_icp_suspend);
			}
			temp = value_1;
		    }
		    break;
		  default:
		    value_1 = g2int_icp_error_internal(Qerror,
			    string_constant_1,type_tag,Nil,Nil);
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(key);
			g2int_resumable_icp_push(type_tag);
			g2int_resumable_icp_push(value);
			g2int_resumable_icp_push(value_p);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value_1);
			return VALUES_1(G2int_icp_suspend);
		    }
		    temp = value_1;
		    break;
		}
	}
    }
    return VALUES_1(temp);
}

Object G2int_item_copy_index_space = UNBOUND;

static Object Qg2int_unbound;      /* unbound */

static Object Qg2int_write_icp_remote_value;  /* write-icp-remote-value */

/* WRITE-ICP-REMOTE-VALUE */
Object g2int_write_icp_remote_value(remote_value)
    Object remote_value;
{
    Object item_copy_index_space, current_computation_flags, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, gensymed_symbol;
    Object value;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(44,71);
    if (G2int_disable_resumability) {
	if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = G2int_current_computation_flags;
	    PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      0);
		temp = g2int_write_icp_remote_value_1(remote_value);
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = g2int_write_icp_remote_value_1(remote_value);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_remote_value,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_remote_value,top,Nil);
		goto end_write_icp_remote_value;
	    }
	}
	remote_value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : remote_value;
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		G2int_item_copy_index_space)) {
	    item_copy_index_space = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,1);
	      current_computation_flags = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      0);
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    gensymed_symbol = g2int_resumable_icp_pop();
		else {
		    value = g2int_write_icp_remote_value_1(remote_value);
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(G2int_current_computation_flags);
			g2int_resumable_icp_push(G2int_item_copy_index_space);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(remote_value);
			g2int_resumable_icp_push(Qg2int_write_icp_remote_value);
			result = VALUES_1(G2int_icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_write_icp_remote_value;
		    }
		    gensymed_symbol = value;
		}
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		temp = gensymed_symbol;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    value = g2int_write_icp_remote_value_1(remote_value);
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(remote_value);
		g2int_resumable_icp_push(Qg2int_write_icp_remote_value);
		result = VALUES_1(G2int_icp_suspend);
		goto end_write_icp_remote_value;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_write_icp_remote_value:
    return result;
}

static Object Qg2int_read_icp_remote_value;  /* read-icp-remote-value */

/* READ-ICP-REMOTE-VALUE */
Object g2int_read_icp_remote_value()
{
    Object item_copy_index_space, current_computation_flags, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, test, gensymed_symbol;
    Object value;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(44,72);
    if (G2int_disable_resumability) {
	if (EQ(Qg2int_unbound,G2int_item_copy_index_space)) {
	    item_copy_index_space = Nil;
	    current_computation_flags = G2int_current_computation_flags;
	    PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		    1);
	      PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,
		      0);
		temp = g2int_read_icp_remote_value_1();
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp = g2int_read_icp_remote_value_1();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_remote_value,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_remote_value,top,Nil);
		goto end_read_icp_remote_value;
	    }
	}
	test = Nil;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    test = g2int_resumable_icp_pop();
	    temp_1 = TRUEP(test);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(test,Qg2int_true) : EQ(Qg2int_unbound,
		G2int_item_copy_index_space)) {
	    item_copy_index_space = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    PUSH_SPECIAL(G2int_item_copy_index_space,item_copy_index_space,1);
	      current_computation_flags = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : 
		      G2int_current_computation_flags;
	      PUSH_SPECIAL(G2int_current_computation_flags,current_computation_flags,
		      0);
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    gensymed_symbol = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_remote_value_1();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(G2int_current_computation_flags);
			g2int_resumable_icp_push(G2int_item_copy_index_space);
			g2int_resumable_icp_push(Qg2int_true);
			g2int_resumable_icp_push(Qg2int_read_icp_remote_value);
			result = VALUES_1(G2int_icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_read_icp_remote_value;
		    }
		    gensymed_symbol = value;
		}
		if (G2int_item_copy_index_space)
		    g2int_reclaim_index_space_1(G2int_item_copy_index_space);
		temp = gensymed_symbol;
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else {
	    value = g2int_read_icp_remote_value_1();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_false);
		g2int_resumable_icp_push(Qg2int_read_icp_remote_value);
		result = VALUES_1(G2int_icp_suspend);
		goto end_read_icp_remote_value;
	    }
	    temp = value;
	}
    }
    result = VALUES_1(temp);
  end_read_icp_remote_value:
    return result;
}

static Object Qg2int_read_icp_gsi_permanent_remote_value;  /* read-icp-gsi-permanent-remote-value */

/* READ-ICP-GSI-PERMANENT-REMOTE-VALUE */
Object g2int_read_icp_gsi_permanent_remote_value()
{
    Object gsi_reclaim_list_qm, temp, resumable_icp_state_1, icp_suspend_1;
    Object top, gensymed_symbol, value;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,73);
    if (G2int_disable_resumability) {
	gsi_reclaim_list_qm = Nil;
	PUSH_SPECIAL(G2int_gsi_reclaim_listqm,gsi_reclaim_list_qm,0);
	  temp = g2int_read_icp_remote_value();
	  g2int_reclaim_gensym_list_1(G2int_gsi_reclaim_listqm);
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_gsi_permanent_remote_value,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_gsi_permanent_remote_value,top,Nil);
		goto end_read_icp_gsi_permanent_remote_value;
	    }
	}
	gsi_reclaim_list_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	PUSH_SPECIAL(G2int_gsi_reclaim_listqm,gsi_reclaim_list_qm,0);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	      gensymed_symbol = g2int_resumable_icp_pop();
	  else {
	      value = g2int_read_icp_remote_value();
	      if (EQ(icp_suspend_1,value)) {
		  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		  g2int_resumable_icp_push(G2int_gsi_reclaim_listqm);
		  g2int_resumable_icp_push(Qg2int_read_icp_gsi_permanent_remote_value);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_gsi_permanent_remote_value;
	      }
	      gensymed_symbol = value;
	  }
	  g2int_reclaim_gensym_list_1(G2int_gsi_reclaim_listqm);
	  temp = gensymed_symbol;
	POP_SPECIAL();
    }
    result = VALUES_1(temp);
  end_read_icp_gsi_permanent_remote_value:
    return result;
}

static Object Qg2int_write_icp_gsi_permanent_remote_value;  /* write-icp-gsi-permanent-remote-value */

/* WRITE-ICP-GSI-PERMANENT-REMOTE-VALUE */
Object g2int_write_icp_gsi_permanent_remote_value(gsi_permanent_remote_value)
    Object gsi_permanent_remote_value;
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;

    x_note_fn_call(44,74);
    if (G2int_disable_resumability)
	temp = g2int_write_icp_remote_value(gsi_permanent_remote_value);
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_gsi_permanent_remote_value,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_gsi_permanent_remote_value,top,Nil);
	}
	gsi_permanent_remote_value = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : gsi_permanent_remote_value;
	value = g2int_write_icp_remote_value(gsi_permanent_remote_value);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(gsi_permanent_remote_value);
	    g2int_resumable_icp_push(Qg2int_write_icp_gsi_permanent_remote_value);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

static Object Qg2int_gsi;          /* gsi */

/* RECLAIM-REMOTE-VALUE */
Object g2int_reclaim_remote_value(remote_value)
    Object remote_value;
{
    x_note_fn_call(44,75);
    if (EQ(Qg2int_gsi,g2int_default_owner_for_gsi_objects()))
	g2int_reclaim_gsi_instance(remote_value,Qg2int_gsi);
    return VALUES_1(Nil);
}

static Object Qg2int_read_icp_evaluation_sequence;  /* read-icp-evaluation-sequence */

/* READ-ICP-EVALUATION-SEQUENCE */
Object g2int_read_icp_evaluation_sequence()
{
    Object temp, typetag, length_1, remote_value_known_typetag, value;
    Object converted_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object resumable_icp_state_1, icp_suspend_1, top, arg1, key, value_1;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,76);
    if (G2int_disable_resumability) {
	temp = g2int_read_icp_byte();
	if ( !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
		FIXNUM_LE(temp,FIX((SI_Long)127L))))
	    typetag = Nil;
	else
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 67:
		typetag = g2int_read_icp_byte();
		break;
	      case 49:
		typetag = FIX((SI_Long)8L);
		break;
	      default:
		typetag = Nil;
		break;
	    }
	length_1 = g2int_read_icp_fixnum();
	remote_value_known_typetag = IFIX(typetag) == (SI_Long)8L ? Nil : 
		typetag;
	PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		0);
	  i = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(length_1);
	  value = Nil;
	  converted_value = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if (i >= ab_loop_bind_)
	      goto end_loop;
	  value = g2int_read_icp_remote_value();
	  converted_value = value;
	  ab_loopvar__2 = g2int_gensym_cons_1(converted_value,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  i = i + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  temp = ab_loopvar_;
	  goto end;
	  temp = Qnil;
	end:;
	POP_SPECIAL();
	temp = g2int_make_gsi_sequence(temp);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_evaluation_sequence,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_evaluation_sequence,top,Nil);
		goto end_read_icp_evaluation_sequence;
	    }
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		typetag = g2int_resumable_icp_pop();
	    else {
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    key = g2int_resumable_icp_pop();
		else {
		    value_1 = g2int_read_icp_byte();
		    if (EQ(icp_suspend_1,value_1)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_read_icp_evaluation_sequence);
			result = VALUES_1(G2int_icp_suspend);
			goto end_read_icp_evaluation_sequence;
		    }
		    key = value_1;
		}
		if ( !(FIXNUMP(key) && FIXNUM_LE(FIX((SI_Long)-128L),key) 
			&& FIXNUM_LE(key,FIX((SI_Long)127L))))
		    typetag = Nil;
		else
		    switch (INTEGER_TO_CHAR(key)) {
		      case 67:
			value_1 = g2int_read_icp_byte();
			if (EQ(icp_suspend_1,value_1)) {
			    g2int_resumable_icp_push(key);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			    g2int_resumable_icp_push(Qg2int_read_icp_evaluation_sequence);
			    result = VALUES_1(G2int_icp_suspend);
			    goto end_read_icp_evaluation_sequence;
			}
			typetag = value_1;
			break;
		      case 49:
			typetag = FIX((SI_Long)8L);
			break;
		      default:
			typetag = Nil;
			break;
		    }
	    }
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		length_1 = g2int_resumable_icp_pop();
	    else {
		value_1 = g2int_read_icp_fixnum();
		if (EQ(icp_suspend_1,value_1)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(typetag);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_read_icp_evaluation_sequence);
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_read_icp_evaluation_sequence;
		}
		length_1 = value_1;
	    }
	    remote_value_known_typetag = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : IFIX(typetag) == 
		    (SI_Long)8L ? Nil : typetag;
	    PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		    0);
	      i = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
	      value = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      converted_value = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__1 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loopvar__2 = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume;
	    next_loop_1:
	      if (i >= ab_loop_bind_)
		  goto end_loop_1;
	    resume:
	      value_1 = g2int_read_icp_remote_value();
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(ab_loopvar__2);
		  g2int_resumable_icp_push(ab_loopvar__1);
		  g2int_resumable_icp_push(ab_loopvar_);
		  g2int_resumable_icp_push(converted_value);
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX(ab_loop_bind_));
		  g2int_resumable_icp_push(FIX(i));
		  g2int_resumable_icp_push(G2int_remote_value_known_typetag);
		  g2int_resumable_icp_push(length_1);
		  g2int_resumable_icp_push(typetag);
		  g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		  g2int_resumable_icp_push(Qg2int_read_icp_evaluation_sequence);
		  result = VALUES_1(G2int_icp_suspend);
		  POP_SPECIAL();
		  goto end_read_icp_evaluation_sequence;
	      }
	      value = value_1;
	      converted_value = value;
	      ab_loopvar__2 = g2int_gensym_cons_1(converted_value,Nil);
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = ab_loopvar__2;
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      arg1 = ab_loopvar_;
	      goto end_1;
	      arg1 = Qnil;
	    end_1:;
	    POP_SPECIAL();
	}
	temp = g2int_make_gsi_sequence(arg1);
    }
    result = VALUES_1(temp);
  end_read_icp_evaluation_sequence:
    return result;
}

static Object Qg2int_text;         /* text */

static Object Qg2int_unsigned_short_vector;  /* unsigned-short-vector */

static Object Qg2int_long;         /* long */

static Object Qg2int_write_icp_evaluation_sequence;  /* write-icp-evaluation-sequence */

/* WRITE-ICP-EVALUATION-SEQUENCE */
Object g2int_write_icp_evaluation_sequence(evaluation_sequence)
    Object evaluation_sequence;
{
    Object gsi_instance_extension, length_1, known_type, type, gsi_items;
    Object value, ab_loop_iter_flag_, typecode, cdr_1, internal_value;
    Object result_1, temp_1, typetag, remote_value_known_typetag;
    Object resumable_icp_state_1, icp_suspend_1, top, gensymed_symbol, arg1;
    Object arg2, test, v1, v2, v3;
    SI_Long i, ab_loop_bind_, j, type_1, length_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,77);
    if (G2int_disable_resumability) {
	gsi_instance_extension = ISVREF(evaluation_sequence,(SI_Long)3L);
	length_1 = gsi_instance_extension ? ISVREF(gsi_instance_extension,
		(SI_Long)7L) : FIX((SI_Long)0L);
	known_type = Nil;
	type = known_type;
	gsi_items = ISVREF(evaluation_sequence,(SI_Long)2L);
	if (gsi_items) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_1);
	    j = IFIX(G2int_gsi_magic_offset);
	    value = Nil;
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		j = j + (SI_Long)1L;
	    value = ISVREF(gsi_items,j);
	    typecode = G2int_remote_value_known_typetag;
	    if (typecode);
	    else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_gsi_instance_g2_struct)) {
		if ( !(G2int_write_value_of_gsi_item_p || 
			g2int_gsi_item_is_value_p(value)))
		    typecode = Qg2int_item;
		else {
		    type_1 = IFIX(ISVREF(value,(SI_Long)1L)) >>  -  - 
			    (SI_Long)3L;
		    typecode = EQ(FIX((SI_Long)50L),FIX(type_1)) || 
			    EQ(FIX((SI_Long)49L),FIX(type_1)) || 
			    g2int_element_type_for_gsi_type(FIX(type_1)) 
			    || ISVREF(value,(SI_Long)2L) ? FIX(type_1) : 
			    FIX((SI_Long)0L);
		}
	    }
	    else if ( !TRUEP(value))
		typecode = FIX((SI_Long)0L);
	    else if (SYMBOLP(value))
		typecode = FIX((SI_Long)3L);
	    else if (FIXNUMP(value))
		typecode = FIX((SI_Long)1L);
	    else if (INLINE_LONG_P(value) != (SI_Long)0L)
		typecode = FIX((SI_Long)51L);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
		typecode = FIX((SI_Long)6L);
	    else {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L) {
		    length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
		    temp = (SI_Long)1L == UBYTE_16_ISAREF_1(value,
			    UBYTE_16_ISAREF_1(value,length_2 - 
			    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(value,
			    length_2 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    typecode = FIX((SI_Long)11L);
		else if (g2int_text_string_p(value) || STRINGP(value))
		    typecode = FIX((SI_Long)4L);
		else if (CONSP(value)) {
		    cdr_1 = M_CDR(value);
		    typecode = EQ(cdr_1,Qg2int_truth_value) ? 
			    FIX((SI_Long)5L) : FIX((SI_Long)0L);
		}
		else
		    typecode = FIX((SI_Long)0L);
	    }
	    if (EQ(typecode,FIX((SI_Long)0L))) {
		internal_value = Nil;
		if ( !TRUEP(type)) {
		    type = Qnull;
		    result_1 = type;
		}
		else if ( !EQ(type,Qnull)) {
		    type = Qt;
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,FIX((SI_Long)1L))) {
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    internal_value = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    internal_value = M_CAR(value);
		else
		    internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qinteger;
		    result_1 = type;
		}
		else if ( !EQ(type,Qinteger)) {
		    type = Qt;
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,FIX((SI_Long)5L))) {
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    internal_value = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    internal_value = M_CAR(value);
		else
		    internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qg2int_truth_value;
		    result_1 = type;
		}
		else if ( !EQ(type,Qg2int_truth_value)) {
		    type = Qt;
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,FIX((SI_Long)6L))) {
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    internal_value = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    internal_value = M_CAR(value);
		else
		    internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qfloat;
		    result_1 = type;
		}
		else if ( !EQ(type,Qfloat)) {
		    type = Qt;
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
	    }
	    else if (EQ(typecode,FIX((SI_Long)4L))) {
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    temp_1 = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    temp_1 = M_CAR(value);
		else
		    temp_1 = value;
		internal_value = g2int_convert_gsi_value_to_value(temp_1);
		if ( !TRUEP(type)) {
		    type = Qg2int_text;
		    result_1 = type;
		}
		else if ( !EQ(type,Qg2int_text)) {
		    type = Qt;
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			temp_1 = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			temp_1 = M_CAR(value);
		    else
			temp_1 = value;
		    if (STRINGP(temp_1))
			g2int_reclaim_wide_string(internal_value);
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    temp_1 = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    temp_1 = M_CAR(value);
		else
		    temp_1 = value;
		if (STRINGP(temp_1))
		    g2int_reclaim_wide_string(internal_value);
	    }
	    else if (EQ(typecode,FIX((SI_Long)11L))) {
		if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,(SI_Long)0L),
			Qg2_defstruct_structure_name_gsi_instance_g2_struct))
		    internal_value = ISVREF(value,(SI_Long)2L);
		else if (CONSP(value))
		    internal_value = M_CAR(value);
		else
		    internal_value = value;
		if ( !TRUEP(type)) {
		    type = Qg2int_unsigned_short_vector;
		    result_1 = type;
		}
		else if ( !EQ(type,Qg2int_unsigned_short_vector)) {
		    type = Qt;
		    goto end_loop;
		}
		else
		    result_1 = Qnil;
	    }
	    else {
		type = Qt;
		goto end_loop;
	    }
	    ab_loop_iter_flag_ = Nil;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	if (EQ(type,Qnull))
	    typetag = FIX((SI_Long)0L);
	else if (EQ(type,Qinteger))
	    typetag = FIX((SI_Long)1L);
	else if (EQ(type,Qg2int_long))
	    typetag = FIX((SI_Long)51L);
	else if (EQ(type,Qg2int_truth_value))
	    typetag = FIX((SI_Long)5L);
	else if (EQ(type,Qfloat))
	    typetag = FIX((SI_Long)6L);
	else if (EQ(type,Qg2int_text))
	    typetag = FIX((SI_Long)4L);
	else if (EQ(type,Qg2int_unsigned_short_vector))
	    typetag = FIX((SI_Long)11L);
	else
	    typetag = Nil;
	remote_value_known_typetag = typetag;
	PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		0);
	  if (typetag) {
	      g2int_write_icp_byte(FIX((SI_Long)67L));
	      g2int_write_icp_byte(typetag);
	  }
	  else
	      g2int_write_icp_byte(FIX((SI_Long)49L));
	  g2int_write_icp_fixnum(length_1);
	  gsi_items = ISVREF(evaluation_sequence,(SI_Long)2L);
	  if (gsi_items) {
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(length_1);
	      j = IFIX(G2int_gsi_magic_offset);
	      value = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop_1:
	      if (i >= ab_loop_bind_)
		  goto end_loop_1;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  j = j + (SI_Long)1L;
	      value = ISVREF(gsi_items,j);
	      g2int_write_icp_remote_value(value);
	      ab_loop_iter_flag_ = Nil;
	      i = i + (SI_Long)1L;
	      goto next_loop_1;
	    end_loop_1:
	      temp_1 = Qnil;
	  }
	  else
	      temp_1 = Nil;
	POP_SPECIAL();
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_evaluation_sequence,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_evaluation_sequence,top,Nil);
		goto end_write_icp_evaluation_sequence;
	    }
	}
	evaluation_sequence = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : evaluation_sequence;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    length_1 = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(evaluation_sequence,(SI_Long)3L);
	    length_1 = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)7L) : 
		    FIX((SI_Long)0L);
	}
	known_type = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    typetag = g2int_resumable_icp_pop();
	else {
	    type = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : known_type;
	    gsi_items = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : ISVREF(evaluation_sequence,
		    (SI_Long)2L);
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    || gsi_items) {
		i = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
		ab_loop_bind_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
		j = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? IFIX(g2int_resumable_icp_pop()) : 
			IFIX(G2int_gsi_magic_offset);
		value = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loop_iter_flag_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : T;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
	      next_loop_2:
		if (i >= ab_loop_bind_)
		    goto end_loop_2;
		if ( !TRUEP(ab_loop_iter_flag_))
		    j = j + (SI_Long)1L;
		value = ISVREF(gsi_items,j);
	      resume:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    typecode = g2int_resumable_icp_pop();
		else {
		    gensymed_symbol = (resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  
			    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			    ? g2int_resumable_icp_pop() : 
			    G2int_remote_value_known_typetag;
		    if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && gensymed_symbol)
			typecode = gensymed_symbol;
		    else if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && SIMPLE_VECTOR_P(value) && 
			    EQ(ISVREF(value,(SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct)) 
				{
			if ( !(G2int_write_value_of_gsi_item_p || 
				g2int_gsi_item_is_value_p(value)))
			    typecode = Qg2int_item;
			else {
			    type_1 = IFIX(ISVREF(value,(SI_Long)1L)) >>  - 
				     - (SI_Long)3L;
			    typecode = EQ(FIX((SI_Long)50L),FIX(type_1)) 
				    || EQ(FIX((SI_Long)49L),FIX(type_1)) 
				    || 
				    g2int_element_type_for_gsi_type(FIX(type_1)) 
				    || ISVREF(value,(SI_Long)2L) ? 
				    FIX(type_1) : FIX((SI_Long)0L);
			}
		    }
		    else if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) &&  !TRUEP(value))
			typecode = FIX((SI_Long)0L);
		    else if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && SYMBOLP(value))
			typecode = FIX((SI_Long)3L);
		    else if ( !(resumable_icp_state_1 ? 
			    TRUEP(G2int_starresumable_icp_statestar) : 
			    TRUEP(Nil)) && FIXNUMP(value))
			typecode = FIX((SI_Long)1L);
		    else {
			arg1 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : 
				FIX(INLINE_LONG_P(value));
			arg2 = (resumable_icp_state_1 ? 
				TRUEP(G2int_starresumable_icp_statestar) : 
				TRUEP(Nil)) &&  
				!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
				? g2int_resumable_icp_pop() : FIX((SI_Long)0L);
			if (FIXNUM_NE(arg1,arg2))
			    typecode = FIX((SI_Long)51L);
			else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
				(SI_Long)1L)
			    typecode = FIX((SI_Long)6L);
			else {
			    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
				    (SI_Long)0L) {
				length_2 = 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value));
				temp = (SI_Long)1L == 
					UBYTE_16_ISAREF_1(value,
					UBYTE_16_ISAREF_1(value,length_2 - 
					(SI_Long)2L) + 
					((UBYTE_16_ISAREF_1(value,length_2 
					- (SI_Long)1L) & (SI_Long)8191L) 
					<< (SI_Long)16L));
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				typecode = FIX((SI_Long)11L);
			    else if (g2int_text_string_p(value) || 
				    STRINGP(value))
				typecode = FIX((SI_Long)4L);
			    else if (CONSP(value)) {
				cdr_1 = M_CDR(value);
				typecode = EQ(cdr_1,Qg2int_truth_value) ? 
					FIX((SI_Long)5L) : FIX((SI_Long)0L);
			    }
			    else
				typecode = FIX((SI_Long)0L);
			}
		    }
		}
		if (EQ(typecode,FIX((SI_Long)0L))) {
		    internal_value = Nil;
		    if ( !TRUEP(type)) {
			type = Qnull;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qnull)) {
			type = Qt;
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,FIX((SI_Long)1L))) {
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			internal_value = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			internal_value = M_CAR(value);
		    else
			internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qinteger;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qinteger)) {
			type = Qt;
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,FIX((SI_Long)5L))) {
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			internal_value = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			internal_value = M_CAR(value);
		    else
			internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qg2int_truth_value;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qg2int_truth_value)) {
			type = Qt;
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,FIX((SI_Long)6L))) {
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			internal_value = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			internal_value = M_CAR(value);
		    else
			internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qfloat;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qfloat)) {
			type = Qt;
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		}
		else if (EQ(typecode,FIX((SI_Long)4L))) {
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			temp_1 = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			temp_1 = M_CAR(value);
		    else
			temp_1 = value;
		    internal_value = g2int_convert_gsi_value_to_value(temp_1);
		    if ( !TRUEP(type)) {
			type = Qg2int_text;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qg2int_text)) {
			type = Qt;
			if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
				(SI_Long)0L),
				Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			    temp_1 = ISVREF(value,(SI_Long)2L);
			else if (CONSP(value))
			    temp_1 = M_CAR(value);
			else
			    temp_1 = value;
			if (STRINGP(temp_1))
			    g2int_reclaim_wide_string(internal_value);
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			temp_1 = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			temp_1 = M_CAR(value);
		    else
			temp_1 = value;
		    if (STRINGP(temp_1))
			g2int_reclaim_wide_string(internal_value);
		}
		else if (EQ(typecode,FIX((SI_Long)11L))) {
		    if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_gsi_instance_g2_struct))
			internal_value = ISVREF(value,(SI_Long)2L);
		    else if (CONSP(value))
			internal_value = M_CAR(value);
		    else
			internal_value = value;
		    if ( !TRUEP(type)) {
			type = Qg2int_unsigned_short_vector;
			result_1 = type;
		    }
		    else if ( !EQ(type,Qg2int_unsigned_short_vector)) {
			type = Qt;
			goto end_loop_2;
		    }
		    else
			result_1 = Qnil;
		}
		else {
		    type = Qt;
		    goto end_loop_2;
		}
		ab_loop_iter_flag_ = Nil;
		i = i + (SI_Long)1L;
		goto next_loop_2;
	      end_loop_2:;
	    }
	    if (EQ(type,Qnull))
		typetag = FIX((SI_Long)0L);
	    else if (EQ(type,Qinteger))
		typetag = FIX((SI_Long)1L);
	    else if (EQ(type,Qg2int_long))
		typetag = FIX((SI_Long)51L);
	    else if (EQ(type,Qg2int_truth_value))
		typetag = FIX((SI_Long)5L);
	    else if (EQ(type,Qfloat))
		typetag = FIX((SI_Long)6L);
	    else if (EQ(type,Qg2int_text))
		typetag = FIX((SI_Long)4L);
	    else if (EQ(type,Qg2int_unsigned_short_vector))
		typetag = FIX((SI_Long)11L);
	    else
		typetag = Nil;
	}
	remote_value_known_typetag = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : typetag;
	PUSH_SPECIAL(G2int_remote_value_known_typetag,remote_value_known_typetag,
		0);
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  test = Nil;
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      test = g2int_resumable_icp_pop();
	      temp = TRUEP(test);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ? EQ(test,Qg2int_true) : TRUEP(typetag)) {
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
		  temp_1 = g2int_resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_1;
			  break;
			case 2:
			  goto l2_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_1:
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)67L)))) {
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	    l2_1:
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(typetag))) {
		  g2int_resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block;
	    end_block:
	      if (EQ(icp_suspend_1,temp_1)) {
		  g2int_resumable_icp_push(Qg2int_true);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	  }
	  else if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		      || T) {
	      if (EQ(icp_suspend_1,g2int_write_icp_byte(FIX((SI_Long)49L)))) {
		  g2int_resumable_icp_push(Qg2int_false);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	  }
	l2:
	  if (EQ(icp_suspend_1,g2int_write_icp_fixnum(length_1))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      result = VALUES_1(G2int_icp_suspend);
	      goto end_block_1;
	  }
	l3:
	  gsi_items = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : ISVREF(evaluation_sequence,
		  (SI_Long)2L);
	  if ((resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  || gsi_items) {
	      i = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : (SI_Long)0L;
	      ab_loop_bind_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : IFIX(length_1);
	      j = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? IFIX(g2int_resumable_icp_pop()) : 
		      IFIX(G2int_gsi_magic_offset);
	      value = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : Nil;
	      ab_loop_iter_flag_ = (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		      ? g2int_resumable_icp_pop() : T;
	      if (resumable_icp_state_1 ? 
		      TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		  goto resume_1;
	    next_loop_3:
	      if (i >= ab_loop_bind_)
		  goto end_loop_3;
	      if ( !TRUEP(ab_loop_iter_flag_))
		  j = j + (SI_Long)1L;
	      value = ISVREF(gsi_items,j);
	    resume_1:
	      if (EQ(icp_suspend_1,g2int_write_icp_remote_value(value))) {
		  g2int_resumable_icp_push(ab_loop_iter_flag_);
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX(j));
		  g2int_resumable_icp_push(FIX(ab_loop_bind_));
		  g2int_resumable_icp_push(FIX(i));
		  g2int_resumable_icp_push(gsi_items);
		  g2int_resumable_icp_push(FIX((SI_Long)3L));
		  result = VALUES_1(G2int_icp_suspend);
		  goto end_block_1;
	      }
	      ab_loop_iter_flag_ = Nil;
	      i = i + (SI_Long)1L;
	      goto next_loop_3;
	    end_loop_3:
	      result = VALUES_1(Qnil);
	  }
	  else
	      result = VALUES_1(Nil);
	  goto end_block_1;
	end_block_1:
	  MVS_3(result,v1,v2,v3);
	  if (EQ(icp_suspend_1,v1)) {
	      g2int_resumable_icp_push(G2int_remote_value_known_typetag);
	      g2int_resumable_icp_push(typetag);
	      g2int_resumable_icp_push(known_type);
	      g2int_resumable_icp_push(length_1);
	      g2int_resumable_icp_push(evaluation_sequence);
	      g2int_resumable_icp_push(Qg2int_write_icp_evaluation_sequence);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_write_icp_evaluation_sequence;
	  }
	  temp_1 = v1;
	POP_SPECIAL();
    }
    result = VALUES_1(temp_1);
  end_write_icp_evaluation_sequence:
    return result;
}

static Object Qg2int_read_evaluation_structure_from_list;  /* read-evaluation-structure-from-list */

/* READ-EVALUATION-STRUCTURE-FROM-LIST */
Object g2int_read_evaluation_structure_from_list(so_far,list_1)
    Object so_far, list_1;
{
    Object attribute, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object plist, temp, resumable_icp_state_1, icp_suspend_1, top, arg1, value;
    Object arg2;

    x_note_fn_call(44,78);
    if (G2int_disable_resumability) {
	attribute = Nil;
	ab_loop_list_ = list_1;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	attribute = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = g2int_gensym_cons_1(attribute,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = g2int_gensym_cons_1(g2int_read_icp_remote_value(),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	plist = ab_loopvar_;
	goto end;
	plist = Qnil;
      end:;
	temp = g2int_make_gsi_structure(so_far ? nconc2(so_far,plist) : plist);
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_evaluation_structure_from_list,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_evaluation_structure_from_list,top,Nil);
	}
	so_far = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : so_far;
	list_1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : list_1;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg1 = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		plist = g2int_resumable_icp_pop();
	    else {
		attribute = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loop_list_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : list_1;
		ab_loopvar_ = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__1 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		if (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		    goto resume;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		attribute = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = g2int_gensym_cons_1(attribute,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	      resume:
		if ((resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		    arg1 = g2int_resumable_icp_pop();
		else {
		    value = g2int_read_icp_remote_value();
		    if (EQ(icp_suspend_1,value)) {
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(ab_loopvar__2);
			g2int_resumable_icp_push(ab_loopvar__1);
			g2int_resumable_icp_push(ab_loopvar_);
			g2int_resumable_icp_push(ab_loop_list_);
			g2int_resumable_icp_push(attribute);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
			g2int_resumable_icp_push(list_1);
			g2int_resumable_icp_push(so_far);
			g2int_resumable_icp_push(Qg2int_read_evaluation_structure_from_list);
			return VALUES_1(G2int_icp_suspend);
		    }
		    arg1 = value;
		}
		arg2 = (resumable_icp_state_1 ? 
			TRUEP(G2int_starresumable_icp_statestar) : 
			TRUEP(Nil)) &&  
			!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
			? g2int_resumable_icp_pop() : Nil;
		ab_loopvar__2 = g2int_gensym_cons_1(arg1,arg2);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_1;
	      end_loop_1:
		plist = ab_loopvar_;
		goto end_1;
		plist = Qnil;
	      end_1:;
	    }
	    arg1 = so_far ? nconc2(so_far,plist) : plist;
	}
	temp = g2int_make_gsi_structure(arg1);
    }
    return VALUES_1(temp);
}

static Object Qg2int_read_icp_evaluation_structure;  /* read-icp-evaluation-structure */

/* READ-ICP-EVALUATION-STRUCTURE */
Object g2int_read_icp_evaluation_structure()
{
    Object temp, resumable_icp_state_1, icp_suspend_1, top, arg1, arg2, arg1_1;
    Object value;

    x_note_fn_call(44,79);
    if (G2int_disable_resumability)
	temp = g2int_read_evaluation_structure_from_list(Nil,
		ISVREF(g2int_read_icp_interned_list_as_value_type(),
		(SI_Long)1L));
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_read_icp_evaluation_structure,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_read_icp_evaluation_structure,top,Nil);
	}
	arg1 = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : Nil;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    arg2 = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		arg1_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_interned_list_as_value_type();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(arg1);
		    g2int_resumable_icp_push(Qg2int_read_icp_evaluation_structure);
		    return VALUES_1(G2int_icp_suspend);
		}
		arg1_1 = value;
	    }
	    arg2 = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : FIX((SI_Long)1L);
	    arg2 = ISVREF(arg1_1,IFIX(arg2));
	}
	value = g2int_read_evaluation_structure_from_list(arg1,arg2);
	if (EQ(icp_suspend_1,value)) {
	    g2int_resumable_icp_push(arg2);
	    g2int_resumable_icp_push(arg1);
	    g2int_resumable_icp_push(Qg2int_read_icp_evaluation_structure);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = value;
    }
    return VALUES_1(temp);
}

/* INTERN-ATTRIBUTES-OF-STRUCTURE */
Object g2int_intern_attributes_of_structure(structure)
    Object structure;
{
    x_note_fn_call(44,80);
    return VALUES_1(Nil);
}

static Object Qg2int_attribute;    /* attribute */

static Object Qg2int_interned_list_table;  /* interned-list-table */

/* INTERN-ATTRIBUTES-OF-GSI-STRUCTURE */
Object g2int_intern_attributes_of_gsi_structure(gsi_item)
    Object gsi_item;
{
    Object accumulating_list_p, list_1, element, root, table, entry_or_table;
    Object entry, gsi_instance_extension, attribute_count;
    Object attribute_count_with_offset, attributes, attribute, attribute_name;
    Object simplified_attribute_name, temp, element_copy, e, cdr_new_value;
    Object element_count_1, root_1, attributes_1, entry_or_table_1, entry_1;
    Object result_1;
    SI_Long element_count, i, ab_loop_bind_, limit, i_1, ab_loop_bind__1;

    x_note_fn_call(44,81);
    element_count = (SI_Long)0L;
    accumulating_list_p = Nil;
    list_1 = Nil;
    element = Nil;
    root = Nil;
    table = Nil;
    entry_or_table = Nil;
    entry = Nil;
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    attribute_count = gsi_instance_extension ? 
	    ISVREF(gsi_instance_extension,(SI_Long)9L) : FIX((SI_Long)0L);
    attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
    attributes = gsi_instance_extension ? ISVREF(gsi_instance_extension,
	    (SI_Long)8L) : Nil;
    if ((SI_Long)0L < IFIX(attribute_count)) {
	i = IFIX(G2int_gsi_magic_offset);
	ab_loop_bind_ = IFIX(attribute_count_with_offset);
	attribute = Nil;
	attribute_name = Nil;
	simplified_attribute_name = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	attribute = ISVREF(attributes,i);
	attribute_name = ISVREF(attribute,(SI_Long)1L);
	simplified_attribute_name = CONSP(attribute_name) && 
		EQ(CAR(attribute_name),Qg2int_attribute) &&  
		!TRUEP(SECOND(attribute_name)) ? THIRD(attribute_name) : 
		attribute_name;
	if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
		(SI_Long)3L))))) {
	    element = simplified_attribute_name;
	    element_count = element_count + (SI_Long)1L;
	    if (element_count == (SI_Long)1L) {
		root = SYMBOLP(element) ? element : Nil;
		if (root) {
		    temp = 
			    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
			    Qg2int_interned_list_table);
		    if (temp);
		    else {
			accumulating_list_p = T;
			G2int_interned_list_symbols = 
				g2int_interned_list_cons(root,
				G2int_interned_list_symbols);
			temp = root;
			temp = g2int_mutate_global_property(temp,
				g2int_interned_list_cons(Nil,Nil),
				Qg2int_interned_list_table);
		    }
		    table = temp;
		}
		else {
		    temp = G2int_interned_list_non_symbol_root;
		    if (temp);
		    else {
			G2int_interned_list_non_symbol_root = 
				g2int_interned_list_cons(Nil,Nil);
			temp = G2int_interned_list_non_symbol_root;
		    }
		    table = temp;
		}
		if (accumulating_list_p && root)
		    list_1 = g2int_interned_list_cons(root,list_1);
		entry_or_table = table;
		entry = Nil;
	    }
	    if ( !(element_count == (SI_Long)1L && root)) {
		if (CONSP(entry_or_table))
		    table = entry_or_table;
		else {
		    table = g2int_interned_list_cons(entry_or_table,Nil);
		    M_CDR(entry) = table;
		}
		temp = SYMBOLP(element) ? g2int_assq_function(element,
			CDR(table)) : g2int_assoc_equal(element,CDR(table));
		if (temp);
		else {
		    element_copy = CONSP(element) ? 
			    g2int_copy_tree_for_interned_list(element) : 
			    element;
		    e = g2int_interned_list_cons(element_copy,Nil);
		    cdr_new_value = g2int_interned_list_cons(e,CDR(table));
		    M_CDR(table) = cdr_new_value;
		    if ( !TRUEP(accumulating_list_p)) {
			accumulating_list_p = T;
			element_count_1 = FIX((SI_Long)0L);
			element = Nil;
			root_1 = Nil;
			table = Nil;
			entry_or_table = Nil;
			entry = Nil;
			limit = element_count - (SI_Long)1L;
			gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
			attribute_count = gsi_instance_extension ? 
				ISVREF(gsi_instance_extension,(SI_Long)9L) 
				: FIX((SI_Long)0L);
			attribute_count_with_offset = 
				FIXNUM_ADD1(attribute_count);
			gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
			attributes_1 = gsi_instance_extension ? 
				ISVREF(gsi_instance_extension,(SI_Long)8L) 
				: Nil;
			if ((SI_Long)0L < IFIX(attribute_count)) {
			    i_1 = IFIX(G2int_gsi_magic_offset);
			    ab_loop_bind__1 = 
				    IFIX(attribute_count_with_offset);
			    attribute = Nil;
			    attribute_name = Nil;
			    simplified_attribute_name = Nil;
			  next_loop_1:
			    if (i_1 >= ab_loop_bind__1)
				goto end_loop_1;
			    attribute = ISVREF(attributes_1,i_1);
			    attribute_name = ISVREF(attribute,(SI_Long)1L);
			    simplified_attribute_name = 
				    CONSP(attribute_name) && 
				    EQ(CAR(attribute_name),
				    Qg2int_attribute) &&  
				    !TRUEP(SECOND(attribute_name)) ? 
				    THIRD(attribute_name) : attribute_name;
			    if ( !((SI_Long)1L == ((SI_Long)1L & 
				    IFIX(ISVREF(attribute,(SI_Long)3L))))) {
				if (limit == IFIX(element_count_1))
				    goto end_list_so_far_block;
				element = simplified_attribute_name;
				element_count_1 = FIXNUM_ADD1(element_count_1);
				if (IFIX(element_count_1) == (SI_Long)1L) {
				    root_1 = SYMBOLP(element) ? element : Nil;
				    if (root_1) {
					temp = 
						g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root_1),
						Qg2int_interned_list_table);
					if (temp);
					else
					    temp = Nil;
					table = temp;
				    }
				    else {
					temp = 
						G2int_interned_list_non_symbol_root;
					if (temp);
					else
					    temp = Nil;
					table = temp;
				    }
				    if (accumulating_list_p && root_1)
					list_1 = 
						g2int_interned_list_cons(root_1,
						list_1);
				    entry_or_table = table;
				    entry = Nil;
				}
				if ( !(IFIX(element_count_1) == 
					(SI_Long)1L && root_1)) {
				    table = CONSP(entry_or_table) ? 
					    entry_or_table : Nil;
				    temp = SYMBOLP(element) ? 
					    g2int_assq_function(element,
					    CDR(table)) : 
					    g2int_assoc_equal(element,
					    CDR(table));
				    if (temp);
				    else
					temp = Nil;
				    entry = temp;
				    if (accumulating_list_p)
					list_1 = 
						g2int_interned_list_cons(CAR(entry),
						list_1);
				    entry_or_table = CDR(entry);
				}
			    }
			    i_1 = i_1 + (SI_Long)1L;
			    goto next_loop_1;
			  end_loop_1:;
			}
		      end_list_so_far_block:;
		    }
		    temp = e;
		}
		entry = temp;
		if (accumulating_list_p)
		    list_1 = g2int_interned_list_cons(CAR(entry),list_1);
		entry_or_table = CDR(entry);
	    }
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    if ((SI_Long)0L == element_count) {
	temp = G2int_interned_list_nil;
	if (temp);
	else {
	    G2int_interned_list_nil = g2int_make_interned_list_1(Nil);
	    temp = G2int_interned_list_nil;
	}
    }
    else {
	temp = CONSP(entry_or_table) ? CAR(entry_or_table) : entry_or_table;
	if (temp);
	else {
	    if ( !TRUEP(accumulating_list_p)) {
		accumulating_list_p = T;
		element_count_1 = FIX((SI_Long)0L);
		element = Nil;
		root = Nil;
		table = Nil;
		entry_or_table_1 = Nil;
		entry_1 = Nil;
		limit = element_count;
		gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		attribute_count = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)9L) : 
			FIX((SI_Long)0L);
		attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
		gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
		attributes = gsi_instance_extension ? 
			ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
		if ((SI_Long)0L < IFIX(attribute_count)) {
		    i = IFIX(G2int_gsi_magic_offset);
		    ab_loop_bind_ = IFIX(attribute_count_with_offset);
		    attribute = Nil;
		    attribute_name = Nil;
		    simplified_attribute_name = Nil;
		  next_loop_2:
		    if (i >= ab_loop_bind_)
			goto end_loop_2;
		    attribute = ISVREF(attributes,i);
		    attribute_name = ISVREF(attribute,(SI_Long)1L);
		    simplified_attribute_name = CONSP(attribute_name) && 
			    EQ(CAR(attribute_name),Qg2int_attribute) &&  
			    !TRUEP(SECOND(attribute_name)) ? 
			    THIRD(attribute_name) : attribute_name;
		    if ( !((SI_Long)1L == ((SI_Long)1L & 
			    IFIX(ISVREF(attribute,(SI_Long)3L))))) {
			if (limit == IFIX(element_count_1))
			    goto end_list_so_far_block_1;
			element = simplified_attribute_name;
			element_count_1 = FIXNUM_ADD1(element_count_1);
			if (IFIX(element_count_1) == (SI_Long)1L) {
			    root = SYMBOLP(element) ? element : Nil;
			    if (root) {
				temp = 
					g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(root),
					Qg2int_interned_list_table);
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    else {
				temp = G2int_interned_list_non_symbol_root;
				if (temp);
				else
				    temp = Nil;
				table = temp;
			    }
			    if (accumulating_list_p && root)
				list_1 = g2int_interned_list_cons(root,list_1);
			    entry_or_table_1 = table;
			    entry_1 = Nil;
			}
			if ( !(IFIX(element_count_1) == (SI_Long)1L && root)) {
			    table = CONSP(entry_or_table_1) ? 
				    entry_or_table_1 : Nil;
			    temp = SYMBOLP(element) ? 
				    g2int_assq_function(element,
				    CDR(table)) : 
				    g2int_assoc_equal(element,CDR(table));
			    if (temp);
			    else
				temp = Nil;
			    entry_1 = temp;
			    if (accumulating_list_p)
				list_1 = 
					g2int_interned_list_cons(CAR(entry_1),
					list_1);
			    entry_or_table_1 = CDR(entry_1);
			}
		    }
		    i = i + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:;
		}
	      end_list_so_far_block_1:;
	    }
	    result_1 = g2int_make_interned_list_1(nreverse(list_1));
	    if (CONSP(entry_or_table))
		temp = M_CAR(entry_or_table) = result_1;
	    else
		temp = M_CDR(entry) = result_1;
	}
    }
    return VALUES_1(temp);
}

static Object Qg2int_write_icp_evaluation_structure;  /* write-icp-evaluation-structure */

/* WRITE-ICP-EVALUATION-STRUCTURE */
Object g2int_write_icp_evaluation_structure(evaluation_structure)
    Object evaluation_structure;
{
    Object gsi_item, gsi_instance_extension, attribute_count;
    Object attribute_count_with_offset, attributes, attribute, attribute_value;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, v1, v2, v3;
    SI_Long i, ab_loop_bind_;
    Object result;

    x_note_fn_call(44,82);
    if (G2int_disable_resumability) {
	g2int_write_icp_interned_list_as_value_type(g2int_intern_attributes_of_gsi_structure(evaluation_structure));
	gsi_item = evaluation_structure;
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	attribute_count = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)9L) : FIX((SI_Long)0L);
	attribute_count_with_offset = FIXNUM_ADD1(attribute_count);
	gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	attributes = gsi_instance_extension ? 
		ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	if ((SI_Long)0L < IFIX(attribute_count)) {
	    i = IFIX(G2int_gsi_magic_offset);
	    ab_loop_bind_ = IFIX(attribute_count_with_offset);
	    attribute = Nil;
	    attribute_value = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    attribute = ISVREF(attributes,i);
	    attribute_value = ISVREF(attribute,(SI_Long)4L);
	    if ( !((SI_Long)1L == ((SI_Long)1L & IFIX(ISVREF(attribute,
		    (SI_Long)3L)))))
		g2int_write_icp_remote_value(attribute_value);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_write_icp_evaluation_structure,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_write_icp_evaluation_structure,top,Nil);
	}
	evaluation_structure = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : evaluation_structure;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    temp = g2int_resumable_icp_pop();
	    if (! !(FIXNUMP(temp) && FIXNUM_LE(FIX((SI_Long)-128L),temp) 
		    && FIXNUM_LE(temp,FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 1:
		    goto l1;
		    break;
		  case 2:
		    goto l2;
		    break;
		  default:
		    break;
		}
	}
      l1:
	if (EQ(icp_suspend_1,
		g2int_write_icp_interned_list_as_value_type(g2int_intern_attributes_of_gsi_structure(evaluation_structure)))) 
		    {
	    g2int_resumable_icp_push(FIX((SI_Long)1L));
	    result = VALUES_1(G2int_icp_suspend);
	    goto end_block;
	}
      l2:
	gsi_item = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : evaluation_structure;
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    attribute_count = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    attribute_count = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)9L) : 
		    FIX((SI_Long)0L);
	}
	attribute_count_with_offset = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : FIXNUM_ADD1(attribute_count);
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    attributes = g2int_resumable_icp_pop();
	else {
	    gsi_instance_extension = ISVREF(gsi_item,(SI_Long)3L);
	    attributes = gsi_instance_extension ? 
		    ISVREF(gsi_instance_extension,(SI_Long)8L) : Nil;
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) || 
		(SI_Long)0L < IFIX(attribute_count)) {
	    i = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(G2int_gsi_magic_offset);
	    ab_loop_bind_ = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    IFIX(g2int_resumable_icp_pop()) : 
		    IFIX(attribute_count_with_offset);
	    attribute = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    attribute_value = (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  
		    !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		    g2int_resumable_icp_pop() : Nil;
	    if (resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil))
		goto resume;
	  next_loop_1:
	    if (i >= ab_loop_bind_)
		goto end_loop_1;
	    attribute = ISVREF(attributes,i);
	    attribute_value = ISVREF(attribute,(SI_Long)4L);
	  resume:
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    ||  !((SI_Long)1L == ((SI_Long)1L & 
		    IFIX(ISVREF(attribute,(SI_Long)3L))))) {
		if (EQ(icp_suspend_1,
			g2int_write_icp_remote_value(attribute_value))) {
		    g2int_resumable_icp_push(attribute_value);
		    g2int_resumable_icp_push(attribute);
		    g2int_resumable_icp_push(FIX(ab_loop_bind_));
		    g2int_resumable_icp_push(FIX(i));
		    g2int_resumable_icp_push(attributes);
		    g2int_resumable_icp_push(attribute_count_with_offset);
		    g2int_resumable_icp_push(attribute_count);
		    g2int_resumable_icp_push(gsi_item);
		    g2int_resumable_icp_push(FIX((SI_Long)2L));
		    result = VALUES_1(G2int_icp_suspend);
		    goto end_block;
		}
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    result = VALUES_1(Qnil);
	}
	else
	    result = VALUES_1(Nil);
	goto end_block;
      end_block:
	MVS_3(result,v1,v2,v3);
	if (EQ(icp_suspend_1,v1)) {
	    g2int_resumable_icp_push(evaluation_structure);
	    g2int_resumable_icp_push(Qg2int_write_icp_evaluation_structure);
	    return VALUES_1(G2int_icp_suspend);
	}
	temp = v1;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_asynchronous_abort;  /* send-icp-rpc-asynchronous-abort */

/* SEND-ICP-RPC-ASYNCHRONOUS-ABORT */
Object g2int_send_icp_rpc_asynchronous_abort(procedure_to_abort_qm)
    Object procedure_to_abort_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top, value, value_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,83);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_asynchronous_abort;
	  }
	  temp_1 = 
		  g2int_getfq_function_no_default(ISVREF(procedure_to_abort_qm,
		  (SI_Long)2L),G2int_current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      g2int_make_corresponding_icp_remote_procedure_identifier(procedure_to_abort_qm);
	  procedure_to_abort_qm = temp_1;
	  g2int_start_writing_icp_message(FIX((SI_Long)235L));
	  g2int_write_icp_corresponding_object_index(procedure_to_abort_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_asynchronous_abort,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_rpc_asynchronous_abort,top,Nil);
		goto end_send_icp_rpc_asynchronous_abort;
	    }
	}
	procedure_to_abort_qm = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : procedure_to_abort_qm;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_asynchronous_abort;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    case 3:
		      goto l3;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) 
		  ? g2int_resumable_icp_pop() : 
		  g2int_getfq_function_no_default(ISVREF(procedure_to_abort_qm,
		  (SI_Long)2L),G2int_current_icp_port);
	  if ( !(resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		  && value)
	      procedure_to_abort_qm = value;
	  else {
	      value_1 = 
		      g2int_make_corresponding_icp_remote_procedure_identifier(procedure_to_abort_qm);
	      if (EQ(icp_suspend_1,value_1)) {
		  g2int_resumable_icp_push(value);
		  g2int_resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = G2int_icp_suspend;
		  goto end_block;
	      }
	      procedure_to_abort_qm = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)235L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_corresponding_object_index(procedure_to_abort_qm))) 
		      {
	      g2int_resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(procedure_to_abort_qm);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_asynchronous_abort);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_asynchronous_abort;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_asynchronous_abort:
    return result;
}

static Object Qg2int_async_abort;  /* async-abort */

static Object Qg2int_rpc_asynchronous_abort;  /* rpc-asynchronous-abort */

static Object string_constant_2;   /* "<an incompletely received call>" */

static Object Qg2int_returned;     /* returned */

/* HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT--BODY */
Object g2int_handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm)
    Object procedure_to_abort_qm;
{
    Object temp, current_remote_procedure_identifier, local_function;
    Object current_icp_port, current_icp_socket, disable_resumability;
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

    x_note_fn_call(44,84);
    if (procedure_to_abort_qm) {
	temp = ISVREF(procedure_to_abort_qm,(SI_Long)6L);
	if (EQ(temp,Qg2int_outstanding)) {
	    SVREF(procedure_to_abort_qm,FIX((SI_Long)6L)) = Qg2int_async_abort;
	    current_remote_procedure_identifier = procedure_to_abort_qm;
	    PUSH_SPECIAL(G2int_current_remote_procedure_identifier,current_remote_procedure_identifier,
		    0);
	      local_function = ISVREF(procedure_to_abort_qm,(SI_Long)3L);
	      g2int_gsi_warning(3,Qg2int_rpc_asynchronous_abort,
		      G2int_gsi_rpc_async_abort,local_function ? 
		      ISVREF(local_function,(SI_Long)3L) : string_constant_2);
	    POP_SPECIAL();
	}
	else if (EQ(temp,Qg2int_returned)) {
	    current_icp_port = ISVREF(G2int_current_icp_socket,(SI_Long)4L);
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
		PUSH_SPECIAL(G2int_disable_resumability,disable_resumability,
			9);
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
					g2int_send_icp_rpc_acknowledge_abort(ISVREF(procedure_to_abort_qm,
						(SI_Long)1L));
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
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_asynchronous_abort;  /* handle-icp-rpc-asynchronous-abort */

/* HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT */
Object g2int_handle_icp_rpc_asynchronous_abort()
{
    Object index_1, index_space, procedure_to_abort_qm;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(44,85);
    if (G2int_disable_resumability) {
	index_1 = g2int_read_icp_corresponding_object_index();
	index_space = G2int_current_temporary_icp_object_index_space;
	if (index_space);
	else
	    index_space = G2int_current_standard_icp_object_index_space;
	if (FIXNUMP(index_1)) {
	    if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		g2int_enlarge_index_space(index_space,index_1);
	    procedure_to_abort_qm = ISVREF(ISVREF(ISVREF(index_space,
		    (SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
		    IFIX(index_1) & (SI_Long)1023L);
	}
	else
	    procedure_to_abort_qm = Nil;
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_asynchronous_abort,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_rpc_asynchronous_abort,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    procedure_to_abort_qm = g2int_resumable_icp_pop();
	else {
	    if ((resumable_icp_state_1 ? 
		    TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) 
		    &&  !TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
		index_1 = g2int_resumable_icp_pop();
	    else {
		value = g2int_read_icp_corresponding_object_index();
		if (EQ(icp_suspend_1,value)) {
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		    g2int_resumable_icp_push(Qg2int_handle_icp_rpc_asynchronous_abort);
		    return VALUES_1(G2int_icp_suspend);
		}
		index_1 = value;
	    }
	    index_space = G2int_current_temporary_icp_object_index_space;
	    if (index_space);
	    else
		index_space = G2int_current_standard_icp_object_index_space;
	    if (FIXNUMP(index_1)) {
		if (FIXNUM_GE(index_1,ISVREF(index_space,(SI_Long)4L)))
		    g2int_enlarge_index_space(index_space,index_1);
		procedure_to_abort_qm = ISVREF(ISVREF(ISVREF(index_space,
			(SI_Long)2L),IFIX(index_1) >>  -  - (SI_Long)10L),
			IFIX(index_1) & (SI_Long)1023L);
	    }
	    else
		procedure_to_abort_qm = Nil;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_asynchronous_abort__body(procedure_to_abort_qm);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qg2int_send_icp_rpc_acknowledge_abort;  /* send-icp-rpc-acknowledge-abort */

/* SEND-ICP-RPC-ACKNOWLEDGE-ABORT */
Object g2int_send_icp_rpc_acknowledge_abort(procedure_index)
    Object procedure_index;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(44,86);
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_acknowledge_abort;
	  }
	  g2int_start_writing_icp_message(FIX((SI_Long)240L));
	  g2int_write_icp_unsigned_integer(procedure_index);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_send_icp_rpc_acknowledge_abort,top)) {
		result = g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_send_icp_rpc_acknowledge_abort,top,Nil);
		goto end_send_icp_rpc_acknowledge_abort;
	    }
	}
	procedure_index = (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()) ? 
		g2int_resumable_icp_pop() : procedure_index;
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
	      SVREF(temp,svref_arg_2) = Qg2int_send_icp_rpc_acknowledge_abort;
	  }
	  if (resumable_icp_state_1 ? 
		  TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	      temp_1 = g2int_resumable_icp_pop();
	      if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		      temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		  switch (INTEGER_TO_CHAR(temp_1)) {
		    case 1:
		      goto l1;
		      break;
		    case 2:
		      goto l2;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  if (EQ(icp_suspend_1,
		  g2int_start_writing_icp_message(FIX((SI_Long)240L)))) {
	      g2int_resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		  g2int_write_icp_unsigned_integer(procedure_index))) {
	      g2int_resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = G2int_icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      g2int_resumable_icp_push(procedure_index);
	      g2int_resumable_icp_push(Qg2int_send_icp_rpc_acknowledge_abort);
	      result = VALUES_1(G2int_icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_rpc_acknowledge_abort;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_rpc_acknowledge_abort:
    return result;
}

/* HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT--BODY */
Object g2int_handle_icp_rpc_acknowledge_abort__body(procedure_index)
    Object procedure_index;
{
    Object identifier_qm;

    x_note_fn_call(44,87);
    identifier_qm = 
	    g2int_lookup_remote_procedure_identifier_from_index(procedure_index);
    if (identifier_qm) {
	if (ISVREF(identifier_qm,(SI_Long)9L))
	    g2int_reclaim_outgoing_remote_procedure_identifier_and_index(identifier_qm);
	else
	    g2int_rpc_acknowledge_abort_error(identifier_qm);
    }
    else
	g2int_rpc_acknowledge_abort_error(procedure_index);
    return VALUES_1(Nil);
}

static Object Qg2int_handle_icp_rpc_acknowledge_abort;  /* handle-icp-rpc-acknowledge-abort */

/* HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT */
Object g2int_handle_icp_rpc_acknowledge_abort()
{
    Object procedure_index, abort_for_icp_catcher_qm, temp;
    Object resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(1);

    x_note_fn_call(44,88);
    if (G2int_disable_resumability) {
	procedure_index = g2int_read_icp_unsigned_integer();
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_acknowledge_abort__body(procedure_index);
	POP_SPECIAL();
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = G2int_starresumable_icp_statestar;
	icp_suspend_1 = G2int_icp_suspend;
	if (resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) {
	    top = g2int_resumable_icp_pop();
	    if ( !EQ(Qg2int_handle_icp_rpc_acknowledge_abort,top))
		return g2int_icp_error_internal(Qerror,string_constant,
			Qg2int_handle_icp_rpc_acknowledge_abort,top,Nil);
	}
	if ((resumable_icp_state_1 ? 
		TRUEP(G2int_starresumable_icp_statestar) : TRUEP(Nil)) &&  
		!TRUEP(g2int_resumable_icp_pop_list_if_end_marker()))
	    procedure_index = g2int_resumable_icp_pop();
	else {
	    value = g2int_read_icp_unsigned_integer();
	    if (EQ(icp_suspend_1,value)) {
		g2int_resumable_icp_push(Qg2int_resumable_icp_list_end);
		g2int_resumable_icp_push(Qg2int_handle_icp_rpc_acknowledge_abort);
		return VALUES_1(G2int_icp_suspend);
	    }
	    procedure_index = value;
	}
	abort_for_icp_catcher_qm = Nil;
	PUSH_SPECIAL(G2int_abort_for_icp_catcherqm,abort_for_icp_catcher_qm,0);
	  g2int_handle_icp_rpc_acknowledge_abort__body(procedure_index);
	POP_SPECIAL();
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object string_constant_3;   /* "Received a rpc-acknowledge-abort message with no remote-procedure-identifier" */

static Object string_constant_4;   /* "Received an unexpected rpc-acknowledge-abort message" */

static Object string_constant_5;   /* "~%Error in rpc-acknowledge-abort, for ~NF ~A~
				    *        ~%~A: ~A~%"
				    */

/* RPC-ACKNOWLEDGE-ABORT-ERROR */
Object g2int_rpc_acknowledge_abort_error(identifier_or_index)
    Object identifier_or_index;
{
    Object description, temp, temp_1;

    x_note_fn_call(44,89);
    description = g2int_icp_socket_description(G2int_current_icp_socket);
    temp = ISVREF(G2int_current_icp_socket,(SI_Long)5L);
    temp_1 = FIXNUMP(identifier_or_index) ? string_constant_3 : 
	    string_constant_4;
    g2int_notify_user_at_console(5,string_constant_5,temp,description,
	    temp_1,FIXNUMP(identifier_or_index) ? identifier_or_index : 
	    ISVREF(identifier_or_index,(SI_Long)10L));
    g2int_reclaim_text_string(description);
    return VALUES_1(Nil);
}

Object G2int_maximum_concurrent_remote_procedure_calls = UNBOUND;

static Object Qg2int_remote_procedure_identifier_map;  /* remote-procedure-identifier-map */

/* MAKE-INITIAL-REMOTE-PROCEDURE-IDENTIFIER-ARRAY */
Object g2int_make_initial_remote_procedure_identifier_array()
{
    Object map_1;

    x_note_fn_call(44,90);
    map_1 = 
	    g2int_make_index_space_1(Qg2int_remote_procedure_identifier_map,
	    Nil);
    g2int_enlarge_index_space(map_1,FIX((SI_Long)20L));
    g2int_assign_index_in_index_space(map_1);
    return VALUES_1(map_1);
}

Object G2int_remote_procedure_identifier_array = UNBOUND;

/* MAKE-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-WITH-INFO */
Object g2int_make_outgoing_remote_procedure_identifier_with_info(return_included_attributes_spec,
	    return_excluded_attributes_spec,
	    return_included_system_attributes_spec,
	    return_include_all_system_attributes_spec,
	    return_include_all_system_attributes_except_spec,
	    return_kind_spec,return_varargs_p)
    Object return_included_attributes_spec, return_excluded_attributes_spec;
    Object return_included_system_attributes_spec;
    Object return_include_all_system_attributes_spec;
    Object return_include_all_system_attributes_except_spec, return_kind_spec;
    Object return_varargs_p;
{
    Object map_1, index_1, identifier, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(44,91);
    map_1 = G2int_remote_procedure_identifier_array;
    index_1 = g2int_assign_index_in_index_space(map_1);
    identifier = g2int_make_outgoing_remote_procedure_identifier(index_1,
	    g2int_make_remote_procedure_item_passing_info_from_specs(Nil,
	    return_included_attributes_spec,
	    return_excluded_attributes_spec,
	    return_included_system_attributes_spec,
	    return_include_all_system_attributes_spec,
	    return_include_all_system_attributes_except_spec,
	    return_kind_spec,return_varargs_p));
    if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	g2int_enlarge_index_space(map_1,index_1);
    svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = identifier;
    return VALUES_1(identifier);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-AND-INDEX */
Object g2int_reclaim_outgoing_remote_procedure_identifier_and_index(remote_procedure_identifier)
    Object remote_procedure_identifier;
{
    Object map_1, index_1, svref_arg_1;
    SI_Long svref_arg_2;

    x_note_fn_call(44,92);
    map_1 = G2int_remote_procedure_identifier_array;
    index_1 = ISVREF(remote_procedure_identifier,(SI_Long)1L);
    g2int_reclaim_icp_object_map_for_remote_procedure_identifier(remote_procedure_identifier);
    if (FIXNUM_GE(index_1,ISVREF(map_1,(SI_Long)4L)))
	g2int_enlarge_index_space(map_1,index_1);
    svref_arg_1 = ISVREF(ISVREF(map_1,(SI_Long)2L),IFIX(index_1) >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = Nil;
    g2int_deassign_index_in_index_space(index_1,map_1);
    g2int_reclaim_outgoing_remote_procedure_identifier(remote_procedure_identifier);
    return VALUES_1(Nil);
}

/* LOOKUP-REMOTE-PROCEDURE-IDENTIFIER-FROM-INDEX */
Object g2int_lookup_remote_procedure_identifier_from_index(procedure_index)
    Object procedure_index;
{
    Object vector_1, temp;
    SI_Long index_1;

    x_note_fn_call(44,93);
    vector_1 = ISVREF(G2int_remote_procedure_identifier_array,(SI_Long)2L);
    index_1 = IFIX(procedure_index) >>  -  - (SI_Long)10L;
    vector_1 = vector_1 && index_1 < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? ISVREF(vector_1,
	    index_1) : Qnil;
    index_1 = IFIX(procedure_index) & (SI_Long)1023L;
    temp = vector_1 && index_1 < IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) 
	    ? ISVREF(vector_1,index_1) : Qnil;
    return VALUES_1(temp);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-IDENTIFIER-FROM-INDEX */
Object g2int_reclaim_outgoing_remote_procedure_identifier_from_index(procedure_index)
    Object procedure_index;
{
    Object identifier_qm;

    x_note_fn_call(44,94);
    identifier_qm = 
	    g2int_lookup_remote_procedure_identifier_from_index(procedure_index);
    if (identifier_qm)
	g2int_reclaim_outgoing_remote_procedure_identifier_and_index(identifier_qm);
    return VALUES_1(Nil);
}

/* GSI-DEFINE-NEW-REMOTE-PROCEDURE */
Object g2int_gsi_define_new_remote_procedure(local_handle)
    Object local_handle;
{
    Object svref_new_value;

    x_note_fn_call(44,95);
    svref_new_value = 
	    g2int_make_remote_procedure_name_1(ISVREF(local_handle,
	    (SI_Long)1L));
    return VALUES_1(SVREF(local_handle,FIX((SI_Long)2L)) = svref_new_value);
}

static Object Qg2_defstruct_structure_name_interned_list_g2_struct;  /* g2-defstruct-structure-name::interned-list-g2-struct */

static Object Qg2int_gsi_reference_flag;  /* gsi-reference-flag */

/* WRITE-ICP-INDEX-SPACE */
Object g2int_write_icp_index_space(index_space)
    Object index_space;
{
    Object last_index, thing, index_1, writing_resumable_icp_messages_p;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(44,96);
    last_index = ISVREF(index_space,(SI_Long)3L);
    g2int_write_icp_unsigned_integer(FIXNUM_ADD1(last_index));
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(last_index);
    thing = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,FIX(i));
    thing = ISVREF(ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
	    (SI_Long)10L),i & (SI_Long)1023L);
    if (SYMBOLP(thing))
	g2int_write_icp_symbol_as_value_type(thing);
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_interned_list_g2_struct)) {
	g2int_write_icp_byte(FIX((SI_Long)90L));
	g2int_write_icp_interned_list_as_value_type(thing);
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct)) {
	index_1 = 
		g2int_get_icp_object_index_for_remote_procedure_name(thing,
		G2int_current_icp_port);
	if (index_1) {
	    g2int_write_icp_byte(FIX((SI_Long)70L));
	    g2int_write_icp_corresponding_object_index(index_1);
	}
	else {
	    g2int_write_icp_byte(FIX((SI_Long)91L));
	    g2int_write_icp_maybe_suspend();
	    writing_resumable_icp_messages_p = Nil;
	    PUSH_SPECIAL(G2int_writing_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		    0);
	      g2int_write_icp_corresponding_object_index(g2int_establish_new_object_index_for_remote_procedure_name(3,
		      thing,G2int_current_icp_port,Nil));
	      g2int_write_icp_symbol_as_value_type(ISVREF(thing,(SI_Long)1L));
	    POP_SPECIAL();
	}
    }
    else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gsi_instance_g2_struct) && 
	    g2int_get_gsi_instance_plist_value(thing,
	    Qg2int_gsi_reference_flag))
	g2int_write_icp_item_reference_1_function(thing);
    else
	g2int_write_icp_byte(FIX((SI_Long)0L));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qg2int_temporary_icp_object_index_space;  /* temporary-icp-object-index-space */

/* READ-ICP-INDEX-SPACE */
Object g2int_read_icp_index_space()
{
    Object size, last_index, index_space, thing, temp, svref_arg_1;
    SI_Long i, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(44,97);
    size = g2int_read_icp_unsigned_integer();
    last_index = FIXNUM_SUB1(size);
    index_space = 
	    g2int_make_index_space_1(Qg2int_temporary_icp_object_index_space,
	    Nil);
    SVREF(index_space,FIX((SI_Long)3L)) = last_index;
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(last_index);
    thing = Nil;
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    temp = g2int_peek_icp_byte();
    if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	thing = Nil;
    else
	switch (INTEGER_TO_CHAR(temp)) {
	  case 70:
	  case 71:
	  case 72:
	  case 75:
	  case 3:
	    thing = g2int_read_icp_symbol_as_value_type();
	    break;
	  case 91:
	    g2int_read_icp_byte();
	    temp = g2int_read_icp_corresponding_object_index();
	    thing = g2int_store_corresponding_icp_object(temp,
		    g2int_make_remote_procedure_name_1(g2int_read_icp_symbol_as_value_type()));
	    break;
	  case 90:
	    g2int_read_icp_byte();
	    thing = g2int_read_icp_interned_list_as_value_type();
	    break;
	  case 60:
	  case 61:
	  case 62:
	    thing = g2int_read_icp_item_reference();
	    break;
	  default:
	    thing = Nil;
	    break;
	}
    if (i >= IFIX(ISVREF(index_space,(SI_Long)4L)))
	g2int_enlarge_index_space(index_space,FIX(i));
    svref_arg_1 = ISVREF(ISVREF(index_space,(SI_Long)2L),i >>  -  - 
	    (SI_Long)10L);
    svref_arg_2 = i & (SI_Long)1023L;
    ISVREF(svref_arg_1,svref_arg_2) = thing;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(index_space);
}

static Object Qg2int_send_icp_define_temporary_index_space;  /* send-icp-define-temporary-index-space */

/* SEND-ICP-DEFINE-TEMPORARY-INDEX-SPACE */
Object g2int_send_icp_define_temporary_index_space(index_space)
    Object index_space;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(44,98);
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
	  SVREF(temp,svref_arg_2) = 
		  Qg2int_send_icp_define_temporary_index_space;
      }
      g2int_start_writing_icp_message(FIX((SI_Long)301L));
      g2int_write_icp_index_space(index_space);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE--BODY */
Object g2int_handle_icp_define_temporary_index_space__body(index_space)
    Object index_space;
{
    Object svref_arg_1;

    x_note_fn_call(44,99);
    svref_arg_1 = G2int_current_icp_port;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = index_space;
    G2int_current_temporary_icp_object_index_space = index_space;
    return VALUES_1(Nil);
}

/* HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE */
Object g2int_handle_icp_define_temporary_index_space()
{
    Object index_space;

    x_note_fn_call(44,100);
    index_space = g2int_read_icp_index_space();
    g2int_handle_icp_define_temporary_index_space__body(index_space);
    return VALUES_1(Nil);
}

static Object Qg2int_send_icp_release_temporary_index_space;  /* send-icp-release-temporary-index-space */

/* SEND-ICP-RELEASE-TEMPORARY-INDEX-SPACE */
Object g2int_send_icp_release_temporary_index_space()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(44,101);
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
	  SVREF(temp,svref_arg_2) = 
		  Qg2int_send_icp_release_temporary_index_space;
      }
      g2int_start_writing_icp_message(FIX((SI_Long)302L));
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE--BODY */
Object g2int_handle_icp_release_temporary_index_space__body()
{
    Object svref_arg_1;

    x_note_fn_call(44,102);
    g2int_reclaim_if_index_space(ISVREF(G2int_current_icp_port,(SI_Long)19L));
    svref_arg_1 = G2int_current_icp_port;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = Nil;
    G2int_current_temporary_icp_object_index_space = Nil;
    return VALUES_1(Nil);
}

/* HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE */
Object g2int_handle_icp_release_temporary_index_space()
{
    x_note_fn_call(44,103);
    g2int_handle_icp_release_temporary_index_space__body();
    return VALUES_1(Nil);
}

void rpc_common1_INIT()
{
    Object temp, reclaim_structure_for_gsi_local_function;
    Object reclaim_structure_for_gsi_remote_procedure;
    Object reclaim_structure_for_remote_procedure_name;
    Object reclaim_structure_for_remote_procedure_identifier;
    Object reclaim_structure_for_remote_procedure_item_passing_info;
    Object reclaim_structure_for_interned_remote_procedure_item_passing_info;
    Object Qg2int_handle_icp_release_temporary_index_space, AB_package;
    Object Qg2int_handle_icp_define_temporary_index_space;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_2;
    Object Qg2int_rpc_common1, Qg2int_remote_procedure_identifier_array;
    Object Qg2int_make_initial_remote_procedure_identifier_array, Kfuncall;
    Object Qg2int_remote_value_known_typetag, Qg2int_copy;
    Object Qg2int_reclaim_icp_port_entry_for_remote_procedure_identifier;
    Object Qg2int_reclaim_remote_procedure_identifier_for_connection_loss;
    Object Qg2int_reclaim_incoming_remote_procedure_identifier;
    Object Qg2int_remote_procedure_identifier, list_constant_1;
    Object Qg2int_icp_object_map_for_remote_procedure_identifier;
    Object Qg2int_interned_remote_procedure_item_passing_info;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_interned_remote_procedure_item_passing_info_count;
    Object Qg2int_chain_of_available_interned_remote_procedure_item_passing_infos;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_11, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object Qg2int_remote_procedure_item_passing_info;
    Object Qg2int_remote_procedure_item_passing_info_count;
    Object Qg2int_chain_of_available_remote_procedure_item_passing_infos;
    Object string_constant_10, Qg2int_remote_procedure_identifier_count;
    Object Qg2int_chain_of_available_remote_procedure_identifiers;
    Object string_constant_9;
    Object Qg2int_reclaim_icp_port_entry_for_remote_procedure_name;
    Object Qg2int_reclaim_remote_procedure_name_for_connection_loss;
    Object Qg2int_reclaim_remote_procedure_name_structure;
    Object Qg2int_remote_procedure_name, list_constant;
    Object Qg2int_icp_object_map_for_remote_procedure_name;
    Object Qg2int_remote_procedure_name_count;
    Object Qg2int_chain_of_available_remote_procedure_names, string_constant_8;
    Object Qg2int_gsi_remote_procedure, Qg2int_gsi_remote_procedure_count;
    Object Qg2int_chain_of_available_gsi_remote_procedures, string_constant_7;
    Object Qg2int_gsi_local_function, Qg2int_gsi_local_function_count;
    Object Qg2int_chain_of_available_gsi_local_functions, string_constant_6;

    x_note_fn_call(44,104);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gsi_local_function_g2_struct = 
	    STATIC_SYMBOL("GSI-LOCAL-FUNCTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_gsi_local_function = STATIC_SYMBOL("GSI-LOCAL-FUNCTION",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    Qg2int_gsi_local_function,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_local_function,
	    Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_local_function == UNBOUND)
	G2int_the_type_description_of_gsi_local_function = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8l83-Jy1n83-Jy8m8k1l8m0000000kok0k0");
    temp = G2int_the_type_description_of_gsi_local_function;
    G2int_the_type_description_of_gsi_local_function = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_6));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_local_function_g2_struct,
	    G2int_the_type_description_of_gsi_local_function,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_gsi_local_function,
	    G2int_the_type_description_of_gsi_local_function,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_local_functions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-LOCAL-FUNCTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_local_functions,
	    G2int_chain_of_available_gsi_local_functions);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_local_functions,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_local_function_count = 
	    STATIC_SYMBOL("GSI-LOCAL-FUNCTION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_local_function_count,
	    G2int_gsi_local_function_count);
    g2int_record_system_variable(Qg2int_gsi_local_function_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_gsi_local_function = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_local_function,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_local_function,
	    reclaim_structure_for_gsi_local_function);
    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_remote_procedure = STATIC_SYMBOL("GSI-REMOTE-PROCEDURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    Qg2int_gsi_remote_procedure,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_gsi_remote_procedure,
	    Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_gsi_remote_procedure == UNBOUND)
	G2int_the_type_description_of_gsi_remote_procedure = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8l83-Ky1n83-Ky8m8k1l8m0000001l1m8p83=bykxk0k0");
    temp = G2int_the_type_description_of_gsi_remote_procedure;
    G2int_the_type_description_of_gsi_remote_procedure = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_7));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_gsi_remote_procedure_g2_struct,
	    G2int_the_type_description_of_gsi_remote_procedure,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_gsi_remote_procedure,
	    G2int_the_type_description_of_gsi_remote_procedure,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_gsi_remote_procedures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GSI-REMOTE-PROCEDURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_gsi_remote_procedures,
	    G2int_chain_of_available_gsi_remote_procedures);
    g2int_record_system_variable(Qg2int_chain_of_available_gsi_remote_procedures,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_gsi_remote_procedure_count = 
	    STATIC_SYMBOL("GSI-REMOTE-PROCEDURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_gsi_remote_procedure_count,
	    G2int_gsi_remote_procedure_count);
    g2int_record_system_variable(Qg2int_gsi_remote_procedure_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_gsi_remote_procedure = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_gsi_remote_procedure,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_gsi_remote_procedure,
	    reclaim_structure_for_gsi_remote_procedure);
    if (G2int_current_remote_procedure_identifier == UNBOUND)
	G2int_current_remote_procedure_identifier = Nil;
    if (G2int_current_invocation_remotely_started_p == UNBOUND)
	G2int_current_invocation_remotely_started_p = Nil;
    if (G2int_rpc_argument_count_overrideqm == UNBOUND)
	G2int_rpc_argument_count_overrideqm = Nil;
    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_remote_procedure_name = STATIC_SYMBOL("REMOTE-PROCEDURE-NAME",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    Qg2int_remote_procedure_name,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_remote_procedure_name,
	    Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_remote_procedure_name == UNBOUND)
	G2int_the_type_description_of_remote_procedure_name = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8l83=oy1n83=oy8m8k1l8m0000001m1n8n83*ty1l83=py1m8p83=jykok0k0");
    temp = G2int_the_type_description_of_remote_procedure_name;
    G2int_the_type_description_of_remote_procedure_name = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_8));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_name_g2_struct,
	    G2int_the_type_description_of_remote_procedure_name,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_remote_procedure_name,
	    G2int_the_type_description_of_remote_procedure_name,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_remote_procedure_names = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-NAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_remote_procedure_names,
	    G2int_chain_of_available_remote_procedure_names);
    g2int_record_system_variable(Qg2int_chain_of_available_remote_procedure_names,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_remote_procedure_name_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-NAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_procedure_name_count,
	    G2int_remote_procedure_name_count);
    g2int_record_system_variable(Qg2int_remote_procedure_name_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_remote_procedure_name = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_remote_procedure_name,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_remote_procedure_name,
	    reclaim_structure_for_remote_procedure_name);
    Qg2int_input = STATIC_SYMBOL("INPUT",AB_package);
    Qg2int_standard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_establish_new_object_index_for_remote_procedure_name = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    string_constant = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qg2int_establish_new_object_index_for_remote_procedure_name,
	    STATIC_FUNCTION(g2int_establish_new_object_index_for_remote_procedure_name,
	    NIL,TRUE,2,3));
    Qg2int_make_corresponding_icp_remote_procedure_name = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_corresponding_icp_remote_procedure_name,
	    STATIC_FUNCTION(g2int_make_corresponding_icp_remote_procedure_name,
	    NIL,FALSE,1,1));
    Qg2int_set_access_form_for_remote_procedure_name = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_remote_procedure_name,
	    STATIC_FUNCTION(g2int_set_access_form_for_remote_procedure_name,
	    NIL,FALSE,2,2));
    Qg2int_icp_object_map_for_remote_procedure_name = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_remote_procedure_name,
	    Qg2int_remote_procedure_name);
    g2int_initialize_icp_object_type_compile(Qg2int_remote_procedure_name,
	    Qg2int_standard_icp_object_index_space,list_constant);
    Qg2int_reclaim_remote_procedure_name_structure = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-NAME-STRUCTURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_remote_procedure_name_structure,
	    STATIC_FUNCTION(g2int_reclaim_remote_procedure_name_structure,
	    NIL,FALSE,1,1));
    Qg2int_reclaim_remote_procedure_name_for_connection_loss = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-NAME-FOR-CONNECTION-LOSS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_remote_procedure_name_for_connection_loss,
	    STATIC_FUNCTION(g2int_reclaim_remote_procedure_name_for_connection_loss,
	    NIL,FALSE,2,2));
    Qg2int_reclaim_icp_port_entry_for_remote_procedure_name = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_remote_procedure_name,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_remote_procedure_name,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_remote_procedure_name,
	    Qg2int_reclaim_remote_procedure_name_structure,
	    Qg2int_reclaim_remote_procedure_name_for_connection_loss,
	    Qg2int_reclaim_icp_port_entry_for_remote_procedure_name);
    Qg2int_send_icp_define_remote_procedure_name = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-REMOTE-PROCEDURE-NAME",AB_package);
    Qg2int_corresponding_icp_object_map_for_symbol = 
	    STATIC_SYMBOL("CORRESPONDING-ICP-OBJECT-MAP-FOR-SYMBOL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_remote_procedure_name,
	    STATIC_FUNCTION(g2int_send_icp_define_remote_procedure_name,
	    NIL,FALSE,2,2));
    Qg2int_handle_icp_define_remote_procedure_name = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-NAME",
	    AB_package);
    Qg2int_resumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_remote_procedure_name,
	    STATIC_FUNCTION(g2int_handle_icp_define_remote_procedure_name,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_remote_procedure_name,
	    FIX((SI_Long)221L));
    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_remote_procedure_identifier = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    Qg2int_remote_procedure_identifier,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_remote_procedure_identifier,
	    Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_remote_procedure_identifier == UNBOUND)
	G2int_the_type_description_of_remote_procedure_identifier = Nil;
    string_constant_9 = 
	    STATIC_STRING("43Dy8l83=my1n83=my8m8k1l8m0000001l1n8n83*ry1m83=ny83Eykvk0k0");
    temp = G2int_the_type_description_of_remote_procedure_identifier;
    G2int_the_type_description_of_remote_procedure_identifier = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_9));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_identifier_g2_struct,
	    G2int_the_type_description_of_remote_procedure_identifier,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_remote_procedure_identifier,
	    G2int_the_type_description_of_remote_procedure_identifier,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_remote_procedure_identifiers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-IDENTIFIERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_remote_procedure_identifiers,
	    G2int_chain_of_available_remote_procedure_identifiers);
    g2int_record_system_variable(Qg2int_chain_of_available_remote_procedure_identifiers,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_remote_procedure_identifier_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_procedure_identifier_count,
	    G2int_remote_procedure_identifier_count);
    g2int_record_system_variable(Qg2int_remote_procedure_identifier_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_remote_procedure_identifier = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_remote_procedure_identifier,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_remote_procedure_identifier,
	    reclaim_structure_for_remote_procedure_identifier);
    Qg2int_outstanding = STATIC_SYMBOL("OUTSTANDING",AB_package);
    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct 
	    = STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_remote_procedure_item_passing_info = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    Qg2int_remote_procedure_item_passing_info,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_remote_procedure_item_passing_info,
	    Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_remote_procedure_item_passing_info 
	    == UNBOUND)
	G2int_the_type_description_of_remote_procedure_item_passing_info = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8l83Ey1n83Ey8m8k1l8m0000001m1n8n83*sy1l83Hy1m8p83=iykmk0k0");
    temp = G2int_the_type_description_of_remote_procedure_item_passing_info;
    G2int_the_type_description_of_remote_procedure_item_passing_info = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_10));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_item_passing_info_g2_struct,
	    G2int_the_type_description_of_remote_procedure_item_passing_info,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_remote_procedure_item_passing_info,
	    G2int_the_type_description_of_remote_procedure_item_passing_info,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_remote_procedure_item_passing_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-ITEM-PASSING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_remote_procedure_item_passing_infos,
	    G2int_chain_of_available_remote_procedure_item_passing_infos);
    g2int_record_system_variable(Qg2int_chain_of_available_remote_procedure_item_passing_infos,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_remote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_procedure_item_passing_info_count,
	    G2int_remote_procedure_item_passing_info_count);
    g2int_record_system_variable(Qg2int_remote_procedure_item_passing_info_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_remote_procedure_item_passing_info = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_remote_procedure_item_passing_info,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_remote_procedure_item_passing_info,
	    reclaim_structure_for_remote_procedure_item_passing_info);
    Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct 
	    = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_interned_remote_procedure_item_passing_info = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    Qg2int_interned_remote_procedure_item_passing_info,
	    Qg2int_ab_name_of_unique_structure_type);
    g2int_mutate_global_property(Qg2int_interned_remote_procedure_item_passing_info,
	    Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_interned_remote_procedure_item_passing_info 
	    == UNBOUND)
	G2int_the_type_description_of_interned_remote_procedure_item_passing_info 
		= Nil;
    string_constant_11 = 
	    STATIC_STRING("43Dy8l83-py1o83-py83Ey8m8k1l83Ey0000001m1m8o83Ey1n8n83*ky1l83Hykmk0k0");
    temp = 
	    G2int_the_type_description_of_interned_remote_procedure_item_passing_info;
    G2int_the_type_description_of_interned_remote_procedure_item_passing_info 
	    = g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_11));
    g2int_mutate_global_property(Qg2_defstruct_structure_name_interned_remote_procedure_item_passing_info_g2_struct,
	    G2int_the_type_description_of_interned_remote_procedure_item_passing_info,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    g2int_mutate_global_property(Qg2int_interned_remote_procedure_item_passing_info,
	    G2int_the_type_description_of_interned_remote_procedure_item_passing_info,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_interned_remote_procedure_item_passing_infos 
	    = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_interned_remote_procedure_item_passing_infos,
	    G2int_chain_of_available_interned_remote_procedure_item_passing_infos);
    g2int_record_system_variable(Qg2int_chain_of_available_interned_remote_procedure_item_passing_infos,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_interned_remote_procedure_item_passing_info_count = 
	    STATIC_SYMBOL("INTERNED-REMOTE-PROCEDURE-ITEM-PASSING-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_interned_remote_procedure_item_passing_info_count,
	    G2int_interned_remote_procedure_item_passing_info_count);
    g2int_record_system_variable(Qg2int_interned_remote_procedure_item_passing_info_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_interned_remote_procedure_item_passing_info = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_interned_remote_procedure_item_passing_info,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_interned_remote_procedure_item_passing_info,
	    reclaim_structure_for_interned_remote_procedure_item_passing_info);
    Qg2int_establish_new_object_index_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_establish_new_object_index_for_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_establish_new_object_index_for_remote_procedure_identifier,
	    NIL,TRUE,2,3));
    Qg2int_make_corresponding_icp_remote_procedure_identifier = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_corresponding_icp_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_make_corresponding_icp_remote_procedure_identifier,
	    NIL,FALSE,1,1));
    Qg2int_set_access_form_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_set_access_form_for_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_set_access_form_for_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    Qg2int_icp_object_map_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("ICP-OBJECT-MAP-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,
	    Qg2int_icp_object_map_for_remote_procedure_identifier,
	    Qg2int_remote_procedure_identifier);
    g2int_initialize_icp_object_type_compile(Qg2int_remote_procedure_identifier,
	    Qg2int_standard_icp_object_index_space,list_constant_1);
    Qg2int_reclaim_incoming_remote_procedure_identifier = 
	    STATIC_SYMBOL("RECLAIM-INCOMING-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_incoming_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_reclaim_incoming_remote_procedure_identifier,
	    NIL,FALSE,1,1));
    Qg2int_reclaim_remote_procedure_identifier_for_connection_loss = 
	    STATIC_SYMBOL("RECLAIM-REMOTE-PROCEDURE-IDENTIFIER-FOR-CONNECTION-LOSS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_remote_procedure_identifier_for_connection_loss,
	    STATIC_FUNCTION(g2int_reclaim_remote_procedure_identifier_for_connection_loss,
	    NIL,FALSE,2,2));
    Qg2int_reclaim_icp_port_entry_for_remote_procedure_identifier = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_reclaim_icp_port_entry_for_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_reclaim_icp_port_entry_for_remote_procedure_identifier,
	    NIL,FALSE,2,2));
    g2int_initialize_icp_object_type(Qg2int_remote_procedure_identifier,
	    Qg2int_reclaim_incoming_remote_procedure_identifier,
	    Qg2int_reclaim_remote_procedure_identifier_for_connection_loss,
	    Qg2int_reclaim_icp_port_entry_for_remote_procedure_identifier);
    Qg2int_send_icp_define_remote_procedure_identifier = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_send_icp_define_remote_procedure_identifier,
	    NIL,FALSE,9,9));
    Qg2int_handle_icp_define_remote_procedure_identifier = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-REMOTE-PROCEDURE-IDENTIFIER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_remote_procedure_identifier,
	    STATIC_FUNCTION(g2int_handle_icp_define_remote_procedure_identifier,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_remote_procedure_identifier,
	    FIX((SI_Long)222L));
    Qg2int_copy = STATIC_SYMBOL("COPY",AB_package);
    if (G2int_write_remote_value_items_kind == UNBOUND)
	G2int_write_remote_value_items_kind = Qg2int_copy;
    if (G2int_gsi_remote_value_creates_instance_p == UNBOUND)
	G2int_gsi_remote_value_creates_instance_p = T;
    if (G2int_gsi_remote_value_conses_logical_p == UNBOUND)
	G2int_gsi_remote_value_conses_logical_p = Nil;
    if (G2int_write_value_of_gsi_item_p == UNBOUND)
	G2int_write_value_of_gsi_item_p = Nil;
    if (G2int_remote_value_is_binary_p == UNBOUND)
	G2int_remote_value_is_binary_p = Nil;
    Qg2int_remote_value_known_typetag = 
	    STATIC_SYMBOL("REMOTE-VALUE-KNOWN-TYPETAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_value_known_typetag,
	    G2int_remote_value_known_typetag);
    Qg2int_rpc_common1 = STATIC_SYMBOL("RPC-COMMON1",AB_package);
    g2int_record_system_variable(Qg2int_remote_value_known_typetag,
	    Qg2int_rpc_common1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_gsi_instance_g2_struct = 
	    STATIC_SYMBOL("GSI-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_item = STATIC_SYMBOL("ITEM",AB_package);
    Qg2int_truth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qg2int_write_icp_remote_value_1 = 
	    STATIC_SYMBOL("WRITE-ICP-REMOTE-VALUE-1",AB_package);
    Qg2int_true = STATIC_SYMBOL("TRUE",AB_package);
    Qg2int_false = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_remote_value_1,
	    STATIC_FUNCTION(g2int_write_icp_remote_value_1,NIL,FALSE,1,1));
    Qg2int_context = STATIC_SYMBOL("CONTEXT",AB_package);
    string_constant_1 = 
	    STATIC_STRING("Unknown type tag ~a in READ-ICP-REMOTE-VALUE");
    Qg2int_read_icp_remote_value_1 = 
	    STATIC_SYMBOL("READ-ICP-REMOTE-VALUE-1",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_remote_value_1,
	    STATIC_FUNCTION(g2int_read_icp_remote_value_1,NIL,FALSE,0,0));
    Qg2int_unbound = STATIC_SYMBOL("UNBOUND",AB_package);
    if (G2int_item_copy_index_space == UNBOUND)
	G2int_item_copy_index_space = Qg2int_unbound;
    Qg2int_write_icp_remote_value = STATIC_SYMBOL("WRITE-ICP-REMOTE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_remote_value,
	    STATIC_FUNCTION(g2int_write_icp_remote_value,NIL,FALSE,1,1));
    Qg2int_read_icp_remote_value = STATIC_SYMBOL("READ-ICP-REMOTE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_remote_value,
	    STATIC_FUNCTION(g2int_read_icp_remote_value,NIL,FALSE,0,0));
    Qg2int_read_icp_gsi_permanent_remote_value = 
	    STATIC_SYMBOL("READ-ICP-GSI-PERMANENT-REMOTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_gsi_permanent_remote_value,
	    STATIC_FUNCTION(g2int_read_icp_gsi_permanent_remote_value,NIL,
	    FALSE,0,0));
    Qg2int_write_icp_gsi_permanent_remote_value = 
	    STATIC_SYMBOL("WRITE-ICP-GSI-PERMANENT-REMOTE-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_gsi_permanent_remote_value,
	    STATIC_FUNCTION(g2int_write_icp_gsi_permanent_remote_value,NIL,
	    FALSE,1,1));
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    Qg2int_read_icp_evaluation_sequence = 
	    STATIC_SYMBOL("READ-ICP-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_evaluation_sequence,
	    STATIC_FUNCTION(g2int_read_icp_evaluation_sequence,NIL,FALSE,0,0));
    Qg2int_text = STATIC_SYMBOL("TEXT",AB_package);
    Qg2int_unsigned_short_vector = STATIC_SYMBOL("UNSIGNED-SHORT-VECTOR",
	    AB_package);
    Qg2int_long = STATIC_SYMBOL("LONG",AB_package);
    Qg2int_write_icp_evaluation_sequence = 
	    STATIC_SYMBOL("WRITE-ICP-EVALUATION-SEQUENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_evaluation_sequence,
	    STATIC_FUNCTION(g2int_write_icp_evaluation_sequence,NIL,FALSE,
	    1,1));
    Qg2int_read_evaluation_structure_from_list = 
	    STATIC_SYMBOL("READ-EVALUATION-STRUCTURE-FROM-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_evaluation_structure_from_list,
	    STATIC_FUNCTION(g2int_read_evaluation_structure_from_list,NIL,
	    FALSE,2,2));
    Qg2int_read_icp_evaluation_structure = 
	    STATIC_SYMBOL("READ-ICP-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_read_icp_evaluation_structure,
	    STATIC_FUNCTION(g2int_read_icp_evaluation_structure,NIL,FALSE,
	    0,0));
    Qg2int_attribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qg2int_interned_list_table = STATIC_SYMBOL("INTERNED-LIST-TABLE",
	    AB_package);
    Qg2int_write_icp_evaluation_structure = 
	    STATIC_SYMBOL("WRITE-ICP-EVALUATION-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_write_icp_evaluation_structure,
	    STATIC_FUNCTION(g2int_write_icp_evaluation_structure,NIL,FALSE,
	    1,1));
    Qg2int_send_icp_rpc_asynchronous_abort = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ASYNCHRONOUS-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_asynchronous_abort,
	    STATIC_FUNCTION(g2int_send_icp_rpc_asynchronous_abort,NIL,
	    FALSE,1,1));
    Qg2int_async_abort = STATIC_SYMBOL("ASYNC-ABORT",AB_package);
    Qg2int_rpc_asynchronous_abort = STATIC_SYMBOL("RPC-ASYNCHRONOUS-ABORT",
	    AB_package);
    string_constant_2 = STATIC_STRING("<an incompletely received call>");
    Qg2int_returned = STATIC_SYMBOL("RETURNED",AB_package);
    Qg2int_handle_icp_rpc_asynchronous_abort = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ASYNCHRONOUS-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_asynchronous_abort,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_asynchronous_abort,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_asynchronous_abort,
	    FIX((SI_Long)235L));
    Qg2int_send_icp_rpc_acknowledge_abort = 
	    STATIC_SYMBOL("SEND-ICP-RPC-ACKNOWLEDGE-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_rpc_acknowledge_abort,
	    STATIC_FUNCTION(g2int_send_icp_rpc_acknowledge_abort,NIL,FALSE,
	    1,1));
    Qg2int_handle_icp_rpc_acknowledge_abort = 
	    STATIC_SYMBOL("HANDLE-ICP-RPC-ACKNOWLEDGE-ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_rpc_acknowledge_abort,
	    STATIC_FUNCTION(g2int_handle_icp_rpc_acknowledge_abort,NIL,
	    FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_rpc_acknowledge_abort,
	    FIX((SI_Long)240L));
    string_constant_3 = 
	    STATIC_STRING("Received a rpc-acknowledge-abort message with no remote-procedure-identifier");
    string_constant_4 = 
	    STATIC_STRING("Received an unexpected rpc-acknowledge-abort message");
    string_constant_5 = 
	    STATIC_STRING("~%Error in rpc-acknowledge-abort, for ~NF ~A~\n       ~%~A: ~A~%");
    G2int_maximum_concurrent_remote_procedure_calls = FIX((SI_Long)4096L);
    Qg2int_remote_procedure_identifier_map = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-MAP",AB_package);
    Qg2int_remote_procedure_identifier_array = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-IDENTIFIER-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_remote_procedure_identifier_array,
	    G2int_remote_procedure_identifier_array);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_make_initial_remote_procedure_identifier_array = 
	    STATIC_SYMBOL("MAKE-INITIAL-REMOTE-PROCEDURE-IDENTIFIER-ARRAY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_make_initial_remote_procedure_identifier_array,
	    STATIC_FUNCTION(g2int_make_initial_remote_procedure_identifier_array,
	    NIL,FALSE,0,0));
    list_constant_2 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qg2int_make_initial_remote_procedure_identifier_array);
    g2int_record_system_variable(Qg2int_remote_procedure_identifier_array,
	    Qg2int_rpc_common1,list_constant_2,Qnil,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_interned_list_g2_struct = 
	    STATIC_SYMBOL("INTERNED-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_gsi_reference_flag = STATIC_SYMBOL("GSI-REFERENCE-FLAG",AB_package);
    Qg2int_temporary_icp_object_index_space = 
	    STATIC_SYMBOL("TEMPORARY-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qg2int_send_icp_define_temporary_index_space = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-TEMPORARY-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_define_temporary_index_space,
	    STATIC_FUNCTION(g2int_send_icp_define_temporary_index_space,
	    NIL,FALSE,1,1));
    Qg2int_handle_icp_define_temporary_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-DEFINE-TEMPORARY-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_define_temporary_index_space,
	    STATIC_FUNCTION(g2int_handle_icp_define_temporary_index_space,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_define_temporary_index_space,
	    FIX((SI_Long)301L));
    Qg2int_send_icp_release_temporary_index_space = 
	    STATIC_SYMBOL("SEND-ICP-RELEASE-TEMPORARY-INDEX-SPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_send_icp_release_temporary_index_space,
	    STATIC_FUNCTION(g2int_send_icp_release_temporary_index_space,
	    NIL,FALSE,0,0));
    Qg2int_handle_icp_release_temporary_index_space = 
	    STATIC_SYMBOL("HANDLE-ICP-RELEASE-TEMPORARY-INDEX-SPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_handle_icp_release_temporary_index_space,
	    STATIC_FUNCTION(g2int_handle_icp_release_temporary_index_space,
	    NIL,FALSE,0,0));
    g2int_add_icp_message_handler(Qg2int_handle_icp_release_temporary_index_space,
	    FIX((SI_Long)302L));
}
