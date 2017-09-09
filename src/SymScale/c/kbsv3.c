/* kbsv3.c
 * Input file:  kb-save3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "kbsv3.h"


/* RUN-PROGRAM-WITH-STRING-OUTPUT */
Object run_program_with_string_output(full_command,directory_1,
	    initial_timeout_qm,callback_qm)
    Object full_command, directory_1, initial_timeout_qm, callback_qm;
{
    Object unix_command_callback_function, buffer, temp, temp_1;
    Object number_of_characters;
    SI_Long length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(135,0);
    unix_command_callback_function = callback_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Unix_command_callback_function,Qunix_command_callback_function,unix_command_callback_function,
	    0);
      length_1 = (SI_Long)2048L;
      buffer = obtain_simple_gensym_string(FIX(length_1));
      temp = Gensym_environment_variable_success;
      temp_1 = initial_timeout_qm;
      if (temp_1);
      else
	  temp_1 = Most_positive_fixnum;
      temp_1 = c_run_program_with_string_output_and_timeout(full_command,
	      directory_1,buffer,temp_1,FIX(length_1));
      number_of_characters = EQL(temp,temp_1) ? 
	      length_of_null_terminated_string(buffer) : FIX((SI_Long)0L);
      reclaim_text_or_gensym_string(full_command);
      result = VALUES_2(buffer,number_of_characters);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_cvs_command, Qcurrent_cvs_command);

DEFINE_VARIABLE_WITH_SYMBOL(Cvs_command_initial_timeout, Qcvs_command_initial_timeout);

DEFINE_VARIABLE_WITH_SYMBOL(Permit_cvs_timeout_dialog_p, Qpermit_cvs_timeout_dialog_p);

DEFINE_VARIABLE_WITH_SYMBOL(Cvs_command_timed_out_p, Qcvs_command_timed_out_p);

DEFINE_VARIABLE_WITH_SYMBOL(Source_code_control_is_enabled_by_default, Qsource_code_control_is_enabled_by_default);

/* GET-ENABLE-SOURCE-CODE-CONTROL-FROM-ENVIRONMENT-OR-COMMAND-LINE */
Object get_enable_source_code_control_from_environment_or_command_line()
{
    x_note_fn_call(135,1);
    Source_code_control_support_enabled_p = Nil;
    return VALUES_1(Source_code_control_support_enabled_p);
}

DEFINE_VARIABLE_WITH_SYMBOL(Ms_to_wait_for_cvs, Qms_to_wait_for_cvs);

/* WAIT-FOR-CVS */
Object wait_for_cvs(ms_to_wait)
    Object ms_to_wait;
{
    x_note_fn_call(135,2);
    Ms_to_wait_for_cvs = ms_to_wait;
    return VALUES_1(Ms_to_wait_for_cvs);
}

static Object Qsource_code_control_support_is_enabled;  /* source-code-control-support-is-enabled */

/* DISABLE-CVS-SUPPORT-AND-RETURN-0 */
Object disable_cvs_support_and_return_0()
{
    x_note_fn_call(135,3);
    change_slot_value(3,Server_parameters,
	    Qsource_code_control_support_is_enabled,Nil);
    Cvs_command_timed_out_p = T;
    Ms_to_wait_for_cvs = FIX((SI_Long)0L);
    return VALUES_1(Ms_to_wait_for_cvs);
}

DEFINE_VARIABLE_WITH_SYMBOL(Workstations_with_their_stacks_for_timeout_of_source_code_control, Qworkstations_with_their_stacks_for_timeout_of_source_code_control);

DEFINE_VARIABLE_WITH_SYMBOL(Ui_client_interfaces_for_timeout_of_source_code_control, Qui_client_interfaces_for_timeout_of_source_code_control);

/* MAYBE-PUT-UP-SCC-TIMEOUT-DIALOG-FOR-WORKSTATION */
Object maybe_put_up_scc_timeout_dialog_for_workstation(workstation)
    Object workstation;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(135,4);
    SAVE_STACK();
    if ( !TRUEP(assq_function(workstation,
	    Workstations_with_their_stacks_for_timeout_of_source_code_control))) 
		{
	Workstations_with_their_stacks_for_timeout_of_source_code_control 
		= gensym_cons_1(gensym_cons_1(workstation,
		ISVREF(workstation,(SI_Long)17L)),
		Workstations_with_their_stacks_for_timeout_of_source_code_control);
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    SAVE_VALUES(maybe_put_up_scc_timeout_dialog_for_workstation_1());
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
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object string_constant;     /* "Waiting for the command:~a~%~
				    *          This probably means someone else is currently committing files, ~
				    *          or that the cvs server is unreachable."
				    */

static Object array_constant;      /* # */

static Object Qnone;               /* none */

static Object Qdisable_cvs_support_and_return_0;  /* disable-cvs-support-and-return-0 */

/* MAYBE-PUT-UP-SCC-TIMEOUT-DIALOG-FOR-WORKSTATION-1 */
Object maybe_put_up_scc_timeout_dialog_for_workstation_1()
{
    Object temp;

    x_note_fn_call(135,5);
    temp = tformat_text_string(2,string_constant,Current_cvs_command);
    return enter_dialog(16,temp,
	    copy_constant_wide_string_given_length(array_constant,
	    FIX((SI_Long)39L)),Qnone,Qdisable_cvs_support_and_return_0,Nil,
	    Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,T,Nil);
}

static Object Qtext;               /* text */

static Object Qscc_timeout_message;  /* scc-timeout-message */

static Object Qscc_timeout;        /* scc-timeout */

static Object Qbutton;             /* button */

static Object Qcancel_and_disable_scc;  /* cancel-and-disable-scc */

static Object Qcontinuation_for_scc_timeout_dialog_for_ui_client_interface;  /* continuation-for-scc-timeout-dialog-for-ui-client-interface */

/* MAYBE-PUT-UP-SCC-TIMEOUT-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object maybe_put_up_scc_timeout_dialog_for_ui_client_interface(ui_client_interface)
    Object ui_client_interface;
{
    Object temp;

    x_note_fn_call(135,6);
    if ( !TRUEP(assq_function(ui_client_interface,
	    Ui_client_interfaces_for_timeout_of_source_code_control))) {
	temp = eval_list_3(Qtext,tformat_text_string(2,string_constant,
		Current_cvs_command),Qscc_timeout_message);
	temp = gensym_cons_1(ui_client_interface,enter_dialog_for_t2(5,
		Qscc_timeout,eval_list_2(temp,eval_list_3(Qbutton,
		copy_text_string(array_constant),Qcancel_and_disable_scc)),
		Qcontinuation_for_scc_timeout_dialog_for_ui_client_interface,
		ui_client_interface,Nil));
	Ui_client_interfaces_for_timeout_of_source_code_control = 
		gensym_cons_1(temp,
		Ui_client_interfaces_for_timeout_of_source_code_control);
	return VALUES_1(Ui_client_interfaces_for_timeout_of_source_code_control);
    }
    else
	return VALUES_1(Nil);
}

/* CONTINUATION-FOR-SCC-TIMEOUT-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object continuation_for_scc_timeout_dialog_for_ui_client_interface(dialog_sequence_number,
	    client_item)
    Object dialog_sequence_number, client_item;
{
    x_note_fn_call(135,7);
    leave_dialog_for_t2(dialog_sequence_number);
    remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
	    ISVREF(client_item,(SI_Long)26L));
    return disable_cvs_support_and_return_0();
}

/* LEAVE-SCC-TIMEOUT-DIALOG-FOR-WORKSTATION */
Object leave_scc_timeout_dialog_for_workstation(workstation)
    Object workstation;
{
    Object a, stack, current_stack, ab_loop_it_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(135,8);
    SAVE_STACK();
    a = assq_function(workstation,
	    Workstations_with_their_stacks_for_timeout_of_source_code_control);
    if (a) {
	Workstations_with_their_stacks_for_timeout_of_source_code_control 
		= delete_gensym_element_1(a,
		Workstations_with_their_stacks_for_timeout_of_source_code_control);
	stack = CDR(a);
	reclaim_gensym_cons_1(a);
	current_stack = ISVREF(workstation,(SI_Long)17L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(current_stack))
	    goto end_loop;
	ab_loop_it_ = EQUAL(stack,current_stack) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	current_stack = M_CDR(current_stack);
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	if (temp) {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = workstation;
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			11);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  10);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    9);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      8);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				7);
			  temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  6);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    5);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
				      (SI_Long)2L);
			      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				      4);
				current_workstation_detail_pane = 
					detail_pane(Current_workstation_window);
				PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					3);
				  current_g2_user_mode_qm = 
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  2);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    1);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      0);
				      next_loop_1:
					temp_1 = ISVREF(workstation,
						(SI_Long)17L);
					if ( !TRUEP(CDR(temp_1)))
					    goto end_loop_1;
					if (EQ(stack,ISVREF(workstation,
						(SI_Long)17L)))
					    goto end_loop_1;
					abort_current_workstation_context(Type_of_current_workstation_context);
					goto next_loop_1;
				      end_loop_1:
					SAVE_VALUES(VALUES_1(Qnil));
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
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* LEAVE-SCC-TIMEOUT-DIALOG-FOR-UI-CLIENT-INTERFACE */
Object leave_scc_timeout_dialog_for_ui_client_interface(ui_client_interface)
    Object ui_client_interface;
{
    Object a, sequence_number;

    x_note_fn_call(135,9);
    a = assq_function(ui_client_interface,
	    Ui_client_interfaces_for_timeout_of_source_code_control);
    if (a) {
	Ui_client_interfaces_for_timeout_of_source_code_control = 
		delete_gensym_element_1(a,
		Ui_client_interfaces_for_timeout_of_source_code_control);
	sequence_number = CDR(a);
	reclaim_gensym_cons_1(a);
	return leave_dialog_for_t2(sequence_number);
    }
    else
	return VALUES_1(Nil);
}

/* LEAVE-ALL-SCC-TIMEOUT-DIALOGS */
Object leave_all_scc_timeout_dialogs()
{
    Object temp;

    x_note_fn_call(135,10);
  next_loop:
    if ( 
	    !TRUEP(Workstations_with_their_stacks_for_timeout_of_source_code_control))
	goto end_loop;
    temp = 
	    FIRST(Workstations_with_their_stacks_for_timeout_of_source_code_control);
    leave_scc_timeout_dialog_for_workstation(CAR(temp));
    goto next_loop;
  end_loop:
  next_loop_1:
    if ( !TRUEP(Ui_client_interfaces_for_timeout_of_source_code_control))
	goto end_loop_1;
    temp = FIRST(Ui_client_interfaces_for_timeout_of_source_code_control);
    leave_scc_timeout_dialog_for_ui_client_interface(CAR(temp));
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object Qicp;                /* icp */

static Object Qx11_window;         /* x11-window */

static Object Qtop_level;          /* top-level */

/* CURRENT-WORKSTATION-IF-USABLE-FOR-DIALOG */
Object current_workstation_if_usable_for_dialog(dialog_is_modal_p)
    Object dialog_is_modal_p;
{
    Object workstation_qm, window;
    char temp;

    x_note_fn_call(135,11);
    workstation_qm = Servicing_workstation_qm ? Current_workstation : Nil;
    if (workstation_qm) {
	window = ISVREF(workstation_qm,(SI_Long)1L);
	temp = EQ(ISVREF(window,(SI_Long)1L),Qicp) ? TRUEP(ISVREF(window,
		(SI_Long)12L)) : TRUEP(Qnil);
	if (temp);
	else
	    temp = EQ(ISVREF(window,(SI_Long)1L),Qx11_window) ? 
		    TRUEP(ISVREF(window,(SI_Long)17L)) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? dialog_is_modal_p || EQ(Type_of_current_workstation_context,
	    Qtop_level) : TRUEP(Nil))
	return VALUES_1(workstation_qm);
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qui_client_interface;  /* ui-client-interface */

/* GET-CURRENT-UI-CLIENT-INTERFACE */
Object get_current_ui_client_interface()
{
    Object icp_socket_qm, interface_qm, gensymed_symbol, x, y, xa, ya;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(135,12);
    icp_socket_qm = Current_system_rpc_icp_socket_qm;
    if (icp_socket_qm);
    else
	icp_socket_qm = Current_icp_socket;
    interface_qm = icp_socket_qm ? ISVREF(icp_socket_qm,(SI_Long)5L) : Qnil;
    if (interface_qm) {
	gensymed_symbol = ISVREF(interface_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(interface_qm) ? EQ(ISVREF(interface_qm,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(icp_socket_qm,(SI_Long)6L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qui_client_interface,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(interface_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(interface_qm);
    else
	return VALUES_1(Nil);
}

/* GET-CURRENT-WORKSTATION-OR-UI-CLIENT-INTERFACE-IF-ANY */
Object get_current_workstation_or_ui_client_interface_if_any()
{
    Object temp;

    x_note_fn_call(135,13);
    temp = current_workstation_if_usable_for_dialog(Nil);
    if (temp)
	return VALUES_1(temp);
    else
	return get_current_ui_client_interface();
}

DEFINE_VARIABLE_WITH_SYMBOL(Return_to_waiting_for_cvs_p, Qreturn_to_waiting_for_cvs_p);

/* CVS-COMMAND-TIMEOUT-CALLBACK */
Object cvs_command_timeout_callback()
{
    Object workstation_qm, ui_client_interface_qm, ms_to_wait_for_cvs;
    Object workstation, ab_loop_list_, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, ui_client_interface;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(135,14);
    if ( !TRUEP(Permit_cvs_timeout_dialog_p)) {
	Cvs_command_timed_out_p = T;
	return VALUES_1(FIX((SI_Long)0L));
    }
    workstation_qm = Nil;
    ui_client_interface_qm = Nil;
    workstation_qm = current_workstation_if_usable_for_dialog(T);
    if (workstation_qm) {
	maybe_put_up_scc_timeout_dialog_for_workstation(workstation_qm);
	ms_to_wait_for_cvs = FIX((SI_Long)100L);
	PUSH_SPECIAL_WITH_SYMBOL(Ms_to_wait_for_cvs,Qms_to_wait_for_cvs,ms_to_wait_for_cvs,
		0);
	  do_some_workstation_processing(workstation_qm);
	  result = VALUES_1(Ms_to_wait_for_cvs);
	POP_SPECIAL();
	return result;
    }
    else {
	ui_client_interface_qm = get_current_ui_client_interface();
	if (ui_client_interface_qm) {
	    maybe_put_up_scc_timeout_dialog_for_ui_client_interface(ui_client_interface_qm);
	    ms_to_wait_for_cvs = FIX((SI_Long)100L);
	    PUSH_SPECIAL_WITH_SYMBOL(Ms_to_wait_for_cvs,Qms_to_wait_for_cvs,ms_to_wait_for_cvs,
		    0);
	      do_some_workstation_processing(workstation_qm);
	      result = VALUES_1(Ms_to_wait_for_cvs);
	    POP_SPECIAL();
	    return result;
	}
	else {
	    workstation = Nil;
	    ab_loop_list_ = Workstations_in_service;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    workstation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    maybe_put_up_scc_timeout_dialog_for_workstation(workstation);
	    goto next_loop;
	  end_loop:;
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ui_client_interface = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qui_client_interface);
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_2:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_1;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_1;
		  goto next_loop_2;
		end_loop_1:
		  temp =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  goto end_loop_2;
	      ui_client_interface = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      maybe_put_up_scc_timeout_dialog_for_ui_client_interface(ui_client_interface);
	      goto next_loop_1;
	    end_loop_2:;
	    POP_SPECIAL();
	    ms_to_wait_for_cvs = FIX((SI_Long)100L);
	    PUSH_SPECIAL_WITH_SYMBOL(Ms_to_wait_for_cvs,Qms_to_wait_for_cvs,ms_to_wait_for_cvs,
		    0);
	      do_some_workstation_processing(Nil);
	      result = VALUES_1(Ms_to_wait_for_cvs);
	    POP_SPECIAL();
	    return result;
	}
    }
}

/* DO-SOME-WORKSTATION-PROCESSING */
Object do_some_workstation_processing(workstation_or_workstation_alist_qm)
    Object workstation_or_workstation_alist_qm;
{
    Object handle_ui_client_interface_messages_immediately_p, workstation;
    Object ab_loop_list_;
    Declare_special(1);

    x_note_fn_call(135,15);
    handle_ui_client_interface_messages_immediately_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Handle_ui_client_interface_messages_immediately_p,Qhandle_ui_client_interface_messages_immediately_p,handle_ui_client_interface_messages_immediately_p,
	    0);
      do_some_icp_processing();
    POP_SPECIAL();
    propagate_all_workspace_changes_to_image_planes();
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    service_workstation(workstation);
    goto next_loop;
  end_loop:;
    return flush_icp_output_ports();
}

static Object Qvms;                /* vms */

static Object Qnamestring_as_gensym_string;  /* namestring-as-gensym-string */

static Object Qg2_defstruct_structure_name_gensym_pathname_g2_struct;  /* g2-defstruct-structure-name::gensym-pathname-g2-struct */

static Object string_constant_1;   /* "" */

static Object string_constant_2;   /* "cvs ~a ~a ~a ~a" */

static Object string_constant_3;   /* "cvs ~a ~a ~a" */

static Object string_constant_4;   /* "cvs ~a ~a" */

static Object string_constant_5;   /* "~a" */

static Object Qcvs_command_timeout_callback;  /* cvs-command-timeout-callback */

/* RUN-CVS-COMMAND-WITH-STRING-OUTPUT */
Object run_cvs_command_with_string_output varargs_1(int, n)
{
    Object command, pathname_1;
    Object no_string_p, arg1, arg2;
    Object internal_status_of_most_recent_file_operation;
    Object pathname_directory_namestring;
    Object pathname_directory_namestring_as_gensym_string, namestring_1;
    Object current_cvs_command;
    Object workstations_with_their_stacks_for_timeout_of_source_code_control;
    Object cvs_command_timed_out_p, buffer, number_of_characters;
    Declare_varargs_nonrelocating;
    Declare_special(4);
    Object result;

    x_note_fn_call(135,16);
    INIT_ARGS_nonrelocating();
    command = REQUIRED_ARG_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    no_string_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(G2_operating_system,Qvms) ||  
	    !TRUEP(Source_code_control_support_enabled_p)) {
	if (no_string_p)
	    return VALUES_1(Nil);
	else
	    return VALUES_2(Nil,FIX((SI_Long)0L));
    }
    internal_status_of_most_recent_file_operation = 
	    File_operation_succeeded_code;
    PUSH_SPECIAL_WITH_SYMBOL(Internal_status_of_most_recent_file_operation,Qinternal_status_of_most_recent_file_operation,internal_status_of_most_recent_file_operation,
	    3);
      if (pathname_1)
	  pathname_directory_namestring = 
		  gensym_directory_and_above_namestring(1,pathname_1);
      else {
	  internal_status_of_most_recent_file_operation = 
		  File_operation_succeeded_code;
	  PUSH_SPECIAL_WITH_SYMBOL(Internal_status_of_most_recent_file_operation,Qinternal_status_of_most_recent_file_operation,internal_status_of_most_recent_file_operation,
		  0);
	    pathname_directory_namestring = g2_stream_get_default_directory();
	  POP_SPECIAL();
      }
      pathname_directory_namestring_as_gensym_string = 
	      export_text_string(2,pathname_directory_namestring,
	      Qnamestring_as_gensym_string);
      namestring_1 = SIMPLE_VECTOR_P(pathname_1) && EQ(ISVREF(pathname_1,
	      (SI_Long)0L),
	      Qg2_defstruct_structure_name_gensym_pathname_g2_struct) ? 
	      gensym_file_namestring(1,pathname_1) : 
	      copy_text_string(string_constant_1);
      if (arg2)
	  current_cvs_command = tformat_gensym_string(5,string_constant_2,
		  command,arg1,arg2,namestring_1);
      else if (arg1)
	  current_cvs_command = tformat_gensym_string(4,string_constant_3,
		  command,arg1,namestring_1);
      else
	  current_cvs_command = tformat_gensym_string(3,string_constant_4,
		  command,namestring_1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_cvs_command,Qcurrent_cvs_command,current_cvs_command,
	      2);
	workstations_with_their_stacks_for_timeout_of_source_code_control 
		= Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Workstations_with_their_stacks_for_timeout_of_source_code_control,Qworkstations_with_their_stacks_for_timeout_of_source_code_control,workstations_with_their_stacks_for_timeout_of_source_code_control,
		1);
	  cvs_command_timed_out_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Cvs_command_timed_out_p,Qcvs_command_timed_out_p,cvs_command_timed_out_p,
		  0);
	    reclaim_text_string(namestring_1);
	    reclaim_text_string(pathname_directory_namestring);
	    if (Send_logbook_messages_to_console_p)
		notify_user_at_console(2,string_constant_5,
			Current_cvs_command);
	    result = run_program_with_string_output(Current_cvs_command,
		    pathname_directory_namestring_as_gensym_string,
		    Cvs_command_initial_timeout,
		    SYMBOL_FUNCTION(Qcvs_command_timeout_callback));
	    MVS_2(result,buffer,number_of_characters);
	    reclaim_gensym_string(pathname_directory_namestring_as_gensym_string);
	    leave_all_scc_timeout_dialogs();
	    if (no_string_p) {
		reclaim_simple_gensym_string(buffer);
		result = VALUES_1( !TRUEP(Cvs_command_timed_out_p) ? T : Nil);
	    }
	    else
		result = VALUES_3(buffer,number_of_characters, 
			!TRUEP(Cvs_command_timed_out_p) ? T : Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qtext_string;        /* text-string */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* GET-SUBSTRING-FROM-BUFFER */
Object get_substring_from_buffer(buffer,number_of_characters,start_string,
	    end_string,result_type,require_version_p)
    Object buffer, number_of_characters, start_string, end_string, result_type;
    Object require_version_p;
{
    Object start_pos, untrimmed_value_start, char_1, value_start;
    Object untrimmed_value_end, value_end, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object thing, temp, schar_arg_2, schar_new_value;
    SI_Long i, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,17);
    start_pos = search(4,start_string,buffer,Kend2,number_of_characters);
    untrimmed_value_start = start_pos ? FIXNUM_ADD(start_pos,
	    length(start_string)) : Nil;
    if (untrimmed_value_start) {
	i = IFIX(untrimmed_value_start);
	ab_loop_bind_ = IFIX(number_of_characters);
	char_1 = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	char_1 = CHR(ICHAR(buffer,i));
	if ( !(CHAR_EQ(char_1,CHR(' ')) || CHAR_EQ(char_1,CHR('\t')))) {
	    value_start = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	value_start = Qnil;
      end_1:;
    }
    else
	value_start = Nil;
    if (value_start) {
	if (CHARACTERP(end_string)) {
	    if (CHAR_EQ(end_string,CHR(' '))) {
		i = IFIX(FIXNUM_ADD1(value_start));
		ab_loop_bind_ = IFIX(number_of_characters);
		char_1 = Nil;
	      next_loop_1:
		if (i >= ab_loop_bind_)
		    goto end_loop_1;
		char_1 = CHR(ICHAR(buffer,i));
		if (CHAR_EQ(char_1,CHR(' ')) || CHAR_EQ(char_1,CHR('\t')) 
			|| CHAR_EQ(char_1,CHR('\n'))) {
		    untrimmed_value_end = FIX(i);
		    goto end_2;
		}
		i = i + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		untrimmed_value_end = Qnil;
	      end_2:;
	    }
	    else
		untrimmed_value_end = position(6,end_string,buffer,Kstart,
			FIXNUM_ADD1(value_start),Kend,number_of_characters);
	}
	else
	    untrimmed_value_end = search(6,end_string,buffer,Kstart2,
		    FIXNUM_ADD1(value_start),Kend2,number_of_characters);
    }
    else
	untrimmed_value_end = Nil;
    if (untrimmed_value_end) {
	i = IFIX(FIXNUM_SUB1(untrimmed_value_end));
	ab_loop_bind_ = IFIX(value_start);
	char_1 = Nil;
      next_loop_2:
	if (i <= ab_loop_bind_)
	    goto end_loop_2;
	char_1 = CHR(ICHAR(buffer,i));
	if ( !(CHAR_EQ(char_1,CHR(' ')) || CHAR_EQ(char_1,CHR('\t')) || 
		CHAR_EQ(char_1,CHR('\r')))) {
	    value_end = FIX(i + (SI_Long)1L);
	    goto end_3;
	}
	i = i - (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	value_end = Qnil;
      end_3:;
    }
    else
	value_end = Nil;
    if (value_end) {
	if ( !(require_version_p &&  !TRUEP(digit_char_p(CHAR(buffer,
		value_start),_)))) {
	    if (EQ(result_type,Qsymbol))
		return intern_gensym_string(1,
			gensym_string_substring(buffer,value_start,value_end));
	    else if (EQ(result_type,Qtext_string)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
		  bv16_length = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		  UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			  aref_new_value);
		  UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			  (SI_Long)0L);
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
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  i = IFIX(value_start);
			  ab_loop_bind_ = IFIX(value_end);
			  char_1 = Nil;
			next_loop_3:
			  if (i >= ab_loop_bind_)
			      goto end_loop_3;
			  char_1 = CHR(ICHAR(buffer,i));
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = char_1;
			      twrite_wide_character(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = char_1;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing) ? 
				      CHAR_CODE(thing) : thing);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
			  i = i + (SI_Long)1L;
			  goto next_loop_3;
			end_loop_3:;
			  result = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Local_source_code_control_buffer, Qlocal_source_code_control_buffer);

DEFINE_VARIABLE_WITH_SYMBOL(Local_source_code_control_number_of_characters, Qlocal_source_code_control_number_of_characters);

DEFINE_VARIABLE_WITH_SYMBOL(In_local_source_code_control_scope_p, Qin_local_source_code_control_scope_p);

static Object string_constant_6;   /* "status" */

static Object Qstatus;             /* status */

static Object string_constant_7;   /* "Status:" */

static Object Qchecked_out_version;  /* checked-out-version */

static Object string_constant_8;   /* "Working revision:" */

static Object Qnewest_version;     /* newest-version */

static Object string_constant_9;   /* "Repository revision:" */

static Object Qbranch;             /* branch */

static Object string_constant_10;  /* "Sticky Tag:" */

static Object string_constant_11;  /* "Error while running \"cvs status ~NP\": " */

/* GET-CVS-STATUS */
Object get_cvs_status varargs_1(int, n)
{
    Object pathname_1, field;
    Object symbolp_1, buffer, number_of_characters, temp, temp_1, temp_2;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object char_1, thing, temp_3, schar_arg_2, schar_new_value, substring;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,18);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    field = REQUIRED_ARG_nonrelocating();
    symbolp_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (In_local_source_code_control_scope_p && 
	    Local_source_code_control_buffer)
	result = VALUES_2(Local_source_code_control_buffer,
		Local_source_code_control_number_of_characters);
    else
	result = run_cvs_command_with_string_output(2,string_constant_6,
		pathname_1);
    MVS_2(result,buffer,number_of_characters);
    if (In_local_source_code_control_scope_p &&  
	    !TRUEP(Local_source_code_control_buffer)) {
	Local_source_code_control_buffer = buffer;
	Local_source_code_control_number_of_characters = number_of_characters;
    }
    if ((SI_Long)0L < IFIX(number_of_characters)) {
	if (CHAR_EQ(CHAR(buffer,FIX((SI_Long)0L)),CHR('='))) {
	    if (EQ(field,Qstatus))
		temp = string_constant_7;
	    else if (EQ(field,Qchecked_out_version))
		temp = string_constant_8;
	    else if (EQ(field,Qnewest_version))
		temp = string_constant_9;
	    else if (EQ(field,Qbranch))
		temp = string_constant_10;
	    else
		temp = Qnil;
	    temp_1 = EQ(field,Qstatus) ? CHR('\n') : CHR(' ');
	    temp_2 = EQ(field,Qchecked_out_version) ? T : Nil;
	    if (temp_2);
	    else
		temp_2 = EQ(field,Qnewest_version) ? T : Nil;
	    temp_2 = get_substring_from_buffer(buffer,number_of_characters,
		    temp,temp_1,symbolp_1 ? Qsymbol : Qtext_string,temp_2);
	}
	else {
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
		      ab_loop_bind_ = IFIX(number_of_characters);
		      char_1 = Nil;
		    next_loop:
		      if (i >= ab_loop_bind_)
			  goto end_loop;
		      char_1 = CHR(ICHAR(buffer,i));
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = char_1;
			  twrite_wide_character(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_3 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = char_1;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing) ? 
				  CHAR_CODE(thing) : thing);
			  SET_SCHAR(temp_3,schar_arg_2,schar_new_value);
			  temp_3 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_3;
		      }
		      i = i + (SI_Long)1L;
		      goto next_loop;
		    end_loop:;
		      substring = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user(3,string_constant_11,pathname_1,substring);
	    reclaim_text_string(substring);
	    temp_2 = Nil;
	}
    }
    else
	temp_2 = Nil;
    if ( !(In_local_source_code_control_scope_p ||  !TRUEP(buffer)))
	reclaim_simple_gensym_string(buffer);
    return VALUES_1(temp_2);
}

static Object string_constant_12;  /* "-v" */

static Object string_constant_13;  /* "1." */

/* GET-CVS-VERSION */
Object get_cvs_version()
{
    Object buffer, number_of_characters, temp, version_string_start_qm, d1_qm;
    Object d2_qm;
    Object result;

    x_note_fn_call(135,19);
    result = run_cvs_command_with_string_output(2,string_constant_12,Nil);
    MVS_2(result,buffer,number_of_characters);
    temp = FIX((SI_Long)0L);
    if (NUM_LT(temp,number_of_characters)) {
	version_string_start_qm = search(4,string_constant_13,buffer,Kend2,
		number_of_characters);
	d1_qm = version_string_start_qm ? digit_char_p(CHR(ICHAR(buffer,
		IFIX(version_string_start_qm) + (SI_Long)2L)),_) : Nil;
	d2_qm = version_string_start_qm ? digit_char_p(CHR(ICHAR(buffer,
		IFIX(version_string_start_qm) + (SI_Long)3L)),_) : Nil;
	temp = d1_qm ? (d2_qm ? FIX(IFIX(d1_qm) * (SI_Long)10L + 
		IFIX(d2_qm)) : d1_qm) : Nil;
    }
    else
	temp = Nil;
    reclaim_simple_gensym_string(buffer);
    return VALUES_1(temp);
}

static Object string_constant_14;  /* "editors" */

/* GET-CVS-EDITORS */
Object get_cvs_editors(pathname_1)
    Object pathname_1;
{
    Object buffer, number_of_characters, start_pos, tab_pos, name_start;
    Object name_end, name, date_start, date_end, host_start, host_end;
    Object directory_start, line_end, directory_end, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;
    Object result;

    x_note_fn_call(135,20);
    result = run_cvs_command_with_string_output(2,string_constant_14,
	    pathname_1);
    MVS_2(result,buffer,number_of_characters);
    if ((SI_Long)0L < IFIX(number_of_characters)) {
	start_pos = FIX((SI_Long)0L);
	tab_pos = Nil;
	name_start = Nil;
	name_end = Nil;
	name = Nil;
	date_start = Nil;
	date_end = Nil;
	host_start = Nil;
	host_end = Nil;
	directory_start = Nil;
	line_end = Nil;
	directory_end = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(start_pos))
	    goto end_loop;
	tab_pos = position(6,CHR('\t'),buffer,Kstart,start_pos,Kend,
		number_of_characters);
	name_start = tab_pos ? FIXNUM_ADD1(tab_pos) : Nil;
	name_end = name_start ? position(6,CHR('\t'),buffer,Kstart,
		name_start,Kend,number_of_characters) : Nil;
	name = name_end ? intern_gensym_string(1,
		gensym_string_substring(buffer,name_start,name_end)) : Nil;
	date_start = name_end ? FIXNUM_ADD1(name_end) : Nil;
	date_end = name_end ? position(6,CHR('\t'),buffer,Kstart,
		date_start,Kend,number_of_characters) : Nil;
	host_start = date_end ? FIXNUM_ADD1(date_end) : Nil;
	host_end = date_end ? position(6,CHR('\t'),buffer,Kstart,
		host_start,Kend,number_of_characters) : Nil;
	directory_start = host_end ? FIXNUM_ADD1(host_end) : Nil;
	line_end = host_end ? position(6,CHR('\n'),buffer,Kstart,
		directory_start,Kend,number_of_characters) : Nil;
	directory_end = line_end ? (CHAR_EQ(SCHAR(buffer,
		FIXNUM_SUB1(line_end)),CHR('\r')) ? FIXNUM_SUB1(line_end) :
		 line_end) : Nil;
	if (name) {
	    temp = name;
	    ab_loopvar__2 = gensym_cons_1(gensym_list_2(temp,
		    gensym_string_substring(buffer,FIXNUM_ADD1(host_end),
		    directory_end)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	start_pos = line_end;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    if (buffer)
	reclaim_simple_gensym_string(buffer);
    return VALUES_1(temp);
}

/* RECLAIM-CVS-EDITORS */
Object reclaim_cvs_editors(editors)
    Object editors;
{
    Object editor, ab_loop_list_, user, directory_1, ab_loop_list__1;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(135,21);
    editor = Nil;
    ab_loop_list_ = editors;
    user = Nil;
    directory_1 = Nil;
    ab_loop_list__1 = editor;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    editor = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
    user = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    directory_1 = CAR(temp);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    reclaim_simple_gensym_string(directory_1);
    reclaim_gensym_list_1(editor);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(editors);
}

static Object list_constant;       /* # */

static Object Qcvs;                /* cvs */

/* FILE-IS-IN-SOURCE-CODE-CONTROL-P */
Object file_is_in_source_code_control_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,22);
    if ( !TRUEP(memq_function(get_cvs_status(3,pathname_1,Qstatus,T),
	    list_constant)))
	return VALUES_1(Qcvs);
    else
	return VALUES_1(Nil);
}

/* STATUS-OF-CURRENTLY-CHECKED-OUT-FILE */
Object status_of_currently_checked_out_file(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,23);
    return get_cvs_status(2,pathname_1,Qstatus);
}

static Object QUp_to_date;         /* |Up-to-date| */

/* CURRENTLY-CHECKED-OUT-FILE-IS-UP-TO-DATE-P */
Object currently_checked_out_file_is_up_to_date_p(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,24);
    return VALUES_1(EQ(get_cvs_status(3,pathname_1,Qstatus,T),QUp_to_date) 
	    ? T : Nil);
}

/* VERSION-OF-CURRENTLY-CHECKED-OUT-FILE */
Object version_of_currently_checked_out_file(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,25);
    return get_cvs_status(2,pathname_1,Qchecked_out_version);
}

/* NEWEST-VERSION-OF-CHECKED-OUT-FILE */
Object newest_version_of_checked_out_file(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,26);
    return get_cvs_status(2,pathname_1,Qnewest_version);
}

/* BRANCH-OF-CHECKED-OUT-FILE */
Object branch_of_checked_out_file(pathname_1)
    Object pathname_1;
{
    x_note_fn_call(135,27);
    return get_cvs_status(2,pathname_1,Qbranch);
}

static Object QNeeds_sp_Patch;     /* |Needs Patch| */

static Object QNeeds_sp_Checkout;  /* |Needs Checkout| */

static Object string_constant_15;  /* "update" */

static Object string_constant_16;  /* "-kb" */

static Object string_constant_17;  /* "Updated ~NP" */

static Object string_constant_18;  /* "Timed out updating ~NP" */

static Object QLocally_sp_Modified;  /* |Locally Modified| */

static Object string_constant_19;  /* "Deleted ~NP" */

static Object QNeeds_sp_Merge;     /* |Needs Merge| */

static Object string_constant_20;  /* "Can't update ~NP because it has been edited locally, ~
				    *               and a newer revision has been committed. ~
				    *               Note that it will not be possible to commit ~NP from within G2."
				    */

static Object QUnknown;            /* |Unknown| */

static Object string_constant_21;  /* "Can't update ~NP because \"cvs status\" is failing." */

static Object string_constant_22;  /* "Can't update ~NP, ~
				    *                                  because cvs is not installed or not in the PATH environment variable"
				    */

/* TRY-TO-GET-NEWEST-VERSION-OF-FILE-1 */
Object try_to_get_newest_version_of_file_1 varargs_1(int, n)
{
    Object pathname_1;
    Object discard_current_version_if_necessary_p, binary_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,28);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    discard_current_version_if_necessary_p = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    binary_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = get_cvs_status(3,pathname_1,Qstatus,T);
    if (EQ(temp,QNeeds_sp_Patch) || EQ(temp,QNeeds_sp_Checkout)) {
	if (run_cvs_command_with_string_output(4,string_constant_15,
		pathname_1,T,binary_p ? string_constant_16 : Nil)) {
	    notify_user(2,string_constant_17,pathname_1);
	    return VALUES_1(Nil);
	}
	else
	    return tformat_text_string(2,string_constant_18,pathname_1);
    }
    else if (EQ(temp,QLocally_sp_Modified)) {
	if (discard_current_version_if_necessary_p) {
	    gensym_delete_file(pathname_1);
	    notify_user(2,string_constant_19,pathname_1);
	    return try_to_get_newest_version_of_file_1(1,pathname_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(temp,QNeeds_sp_Merge)) {
	if (discard_current_version_if_necessary_p) {
	    gensym_delete_file(pathname_1);
	    notify_user(2,string_constant_19,pathname_1);
	    return try_to_get_newest_version_of_file_1(1,pathname_1);
	}
	else
	    return tformat_text_string(3,string_constant_20,pathname_1,
		    pathname_1);
    }
    else if (EQ(temp,QUnknown))
	return try_to_put_file_in_source_code_control(4,pathname_1,
		binary_p,string_constant_15,T);
    else if (EQ(temp,Qnil)) {
	if (Source_code_control_support_enabled_p) {
	    if (get_cvs_version()) {
		temp = try_to_put_file_in_source_code_control(4,pathname_1,
			binary_p,string_constant_15,T);
		if (temp)
		    return VALUES_1(temp);
		else
		    return tformat_text_string(2,string_constant_21,
			    pathname_1);
	    }
	    else
		return tformat_text_string(2,string_constant_22,pathname_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* TRY-TO-GET-NEWEST-VERSION-OF-FILE */
Object try_to_get_newest_version_of_file varargs_1(int, n)
{
    Object pathname_1;
    Object discard_current_version_if_necessary_p, binary_p, message_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,29);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    discard_current_version_if_necessary_p = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    binary_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    message_qm = try_to_get_newest_version_of_file_1(3,pathname_1,
	    discard_current_version_if_necessary_p,binary_p);
    if (message_qm)
	return notify_user_1(message_qm);
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* "The source code control features of G2 will not be usable, ~
				    *                            because cvs is not installed or not in the PATH environment variable"
				    */

static Object string_constant_24;  /* "The source code control features of G2 work best with CVS version 1.10 ~
				    *                            or higher, but version 1.~d was found"
				    */

/* ENABLE-SCC-CHECK */
Object enable_scc_check()
{
    Object version_qm;

    x_note_fn_call(135,30);
    if (Source_code_control_support_enabled_p) {
	version_qm = get_cvs_version();
	if ( !TRUEP(version_qm)) {
	    notify_user(1,string_constant_23);
	    return VALUES_1(T);
	}
	else if (IFIX(version_qm) < (SI_Long)10L) {
	    notify_user(2,string_constant_24,version_qm);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_25;  /* "The source code control features of G2 will not be usable, ~
				    *                because cvs is not installed or not in the PATH environment variable"
				    */

static Object string_constant_26;  /* "use source code control for" */

static Object string_constant_27;  /* "Note that a newer revision is available for ~NP. ~
				    *                        You might want to load it again using UPDATE BEFORE LOADING"
				    */

static Object string_constant_28;  /* "Note that there is now a newer revision for ~NP, ~
				    *                        but it will not be possible to merge it with ~NP"
				    */

static Object string_constant_29;  /* "Note that it will not be possible to check out ~NP ~
				    *                            for editing because ~A"
				    */

static Object string_constant_30;  /* "Note that this file is under source code control. ~
				    *                    If cvs is installed on your machine, you might want ~
				    *                    to turn on source code control support, in the ~
				    *                    server-parameters system table."
				    */

/* NON-UPDATE-KB-CHECK-1 */
Object non_update_kb_check_1(pathname_1,top_level_p)
    Object pathname_1, top_level_p;
{
    Object error_qm, temp, reason_qm;

    x_note_fn_call(135,31);
    if (Source_code_control_support_enabled_p) {
	if (top_level_p &&  !TRUEP(get_cvs_version()))
	    return tformat_text_string(1,string_constant_25);
	error_qm = try_to_put_file_in_source_code_control(4,pathname_1,T,
		string_constant_26,T);
	if (error_qm)
	    return VALUES_1(error_qm);
	else {
	    temp = get_cvs_status(3,pathname_1,Qstatus,T);
	    if (EQ(temp,QNeeds_sp_Patch) || EQ(temp,QNeeds_sp_Checkout))
		return tformat_text_string(2,string_constant_27,pathname_1);
	    else if (EQ(temp,QNeeds_sp_Merge))
		return tformat_text_string(3,string_constant_28,pathname_1,
			pathname_1);
	    else if (EQ(temp,QUp_to_date) || EQ(temp,QLocally_sp_Modified)) {
		reason_qm = 
			reason_that_the_current_user_is_not_the_only_editor(pathname_1,
			T);
		if (reason_qm)
		    return tformat_text_string(3,string_constant_29,
			    pathname_1,reason_qm);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else if (top_level_p) {
	error_qm = try_to_put_file_in_source_code_control(4,pathname_1,T,
		string_constant_1,T);
	if (error_qm) {
	    reclaim_text_string(error_qm);
	    return VALUES_1(Nil);
	}
	else
	    return tformat_text_string(1,string_constant_30);
    }
    else
	return VALUES_1(Qnil);
}

/* NON-UPDATE-KB-CHECK */
Object non_update_kb_check(pathname_1,top_level_p)
    Object pathname_1, top_level_p;
{
    Object warning_qm;

    x_note_fn_call(135,32);
    warning_qm = non_update_kb_check_1(pathname_1,top_level_p);
    if (warning_qm)
	return notify_user_1(warning_qm);
    else
	return VALUES_1(Nil);
}

Object Status_codes_causing_source_code_control_problems_if_saved_p = UNBOUND;

/* WILL-CAUSE-SOURCE-CODE-CONTROL-PROBLEMS-IF-SAVED-P */
Object will_cause_source_code_control_problems_if_saved_p(pathname_1)
    Object pathname_1;
{
    Object temp;

    x_note_fn_call(135,33);
    temp = get_cvs_status(3,pathname_1,Qstatus,T);
    return VALUES_1( ! !TRUEP(memq_function(temp,
	    Status_codes_causing_source_code_control_problems_if_saved_p)) 
	    ? T : Nil);
}

static Object string_constant_31;  /* "Can't ~A ~NP because its directory is at top level" */

static Object Krelative;           /* :relative */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant_3;    /* # */

static Object string_constant_32;  /* "Can't ~A ~NP because its directory is not ~
				    *                       under source code control. ~
				    *                       Use \"cvs checkout\" on its directory first."
				    */

static Object string_constant_33;  /* "Can't ~A ~NP because its CVS repository directory, ~A, ~
				    *                       specified by the CVS file ~NP, does not exist."
				    */

static Object string_constant_34;  /* "add" */

/* TRY-TO-PUT-FILE-IN-SOURCE-CODE-CONTROL */
Object try_to_put_file_in_source_code_control varargs_1(int, n)
{
    Object pathname_1;
    Object binary_p, operation, no_add_p, directory_1;
    Object internal_status_of_most_recent_file_operation, cvs_directory;
    Object cvs_root_pathname, namestring_for_root;
    volatile Object pathname_used_p;
    volatile Object namestring_1;
    volatile Object input_stream_qm;
    Object temp, root_qm, root_is_local_p, root_is_local_and_exists_p;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(135,34);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    binary_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    operation = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    no_add_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    directory_1 = ISVREF(pathname_1,(SI_Long)3L);
    if ( !LISTP(directory_1)) {
	result = tformat_text_string(3,string_constant_31,operation,
		pathname_1);
	RESTORE_STACK();
	return result;
    }
    internal_status_of_most_recent_file_operation = 
	    File_operation_succeeded_code;
    PUSH_SPECIAL_WITH_SYMBOL(Internal_status_of_most_recent_file_operation,Qinternal_status_of_most_recent_file_operation,internal_status_of_most_recent_file_operation,
	    0);
      cvs_directory = nconc2(directory_1 ? 
	      copy_list_using_gensym_conses_1(directory_1) : 
	      gensym_cons_1(Krelative,Nil),gensym_cons_1(array_constant_1,
	      Nil));
      cvs_root_pathname = gensym_make_pathname_with_copied_components(Nil,
	      ISVREF(pathname_1,(SI_Long)2L),cvs_directory,
	      array_constant_2,Nil,Nil,Nil);
      namestring_for_root = gensym_namestring(1,cvs_root_pathname);
      if (g2_stream_file_is_readable_p(namestring_for_root)) {
	  pathname_used_p = Qunbound_in_protected_let;
	  namestring_1 = Qunbound_in_protected_let;
	  input_stream_qm = Qunbound_in_protected_let;
	  if (PUSH_UNWIND_PROTECT(0)) {
	      pathname_used_p = SIMPLE_VECTOR_P(namestring_for_root) ? 
		      (EQ(ISVREF(namestring_for_root,(SI_Long)0L),
		      Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		      ? T : Nil) : Qnil;
	      namestring_1 = SIMPLE_VECTOR_P(namestring_for_root) && 
		      EQ(ISVREF(namestring_for_root,(SI_Long)0L),
		      Qg2_defstruct_structure_name_gensym_pathname_g2_struct) 
		      ? gensym_namestring(1,namestring_for_root) : 
		      namestring_for_root;
	      input_stream_qm = g2_stream_open_for_input(namestring_1);
	      temp = input_stream_qm ? 
		      g2_stream_read_line(input_stream_qm) : Nil;
	      SAVE_VALUES(VALUES_1(temp));
	  }
	  POP_UNWIND_PROTECT(0);
	  if (input_stream_qm) {
	      if ( !EQ(input_stream_qm,Qunbound_in_protected_let))
		  g2_stream_close(input_stream_qm);
	  }
	  if (namestring_1) {
	      if ( !EQ(namestring_1,Qunbound_in_protected_let)) {
		  if (pathname_used_p)
		      reclaim_text_string(namestring_1);
	      }
	  }
	  CONTINUE_UNWINDING(0);
	  result = RESTORE_VALUES();
	  root_qm = result;
      }
      else
	  root_qm = Nil;
      if (root_qm) {
	  root_is_local_p =  
		  !TRUEP(position_in_text_string(FIX((SI_Long)58L),
		  root_qm)) ? T : Nil;
	  if (root_is_local_p);
	  else
	      root_is_local_p = (SI_Long)7L < IFIX(lengthw(root_qm)) ? 
		      text_string_equal_given_indices(array_constant_3,
		      root_qm,FIX((SI_Long)0L),FIX((SI_Long)7L),
		      FIX((SI_Long)0L),FIX((SI_Long)7L)) : Qnil;
      }
      else
	  root_is_local_p = Nil;
      root_is_local_and_exists_p = root_is_local_p ? 
	      g2_stream_file_is_readable_p(root_qm) : Qnil;
      reclaim_gensym_list_1(cvs_directory);
      reclaim_text_string(namestring_for_root);
      if ( !TRUEP(root_qm)) {
	  temp = tformat_text_string(3,string_constant_32,operation,
		  pathname_1);
	  reclaim_gensym_pathname(cvs_root_pathname);
	  result = VALUES_1(temp);
      }
      else if (root_is_local_p &&  !TRUEP(root_is_local_and_exists_p)) {
	  temp = tformat_text_string(5,string_constant_33,operation,
		  pathname_1,root_qm,cvs_root_pathname);
	  reclaim_text_string(root_qm);
	  reclaim_gensym_pathname(cvs_root_pathname);
	  result = VALUES_1(temp);
      }
      else {
	  reclaim_text_string(root_qm);
	  reclaim_gensym_pathname(cvs_root_pathname);
	  if ( !TRUEP(no_add_p))
	      run_cvs_command_with_string_output(4,string_constant_34,
		      pathname_1,T,binary_p ? string_constant_16 : Nil);
	  result = VALUES_1(Nil);
      }
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object string_constant_35;  /* "Can't commit ~NP because source code control does not run on VMS" */

static Object string_constant_36;  /* "Can't commit ~NP because source code control is not enabled" */

static Object string_constant_37;  /* "commit" */

static Object string_constant_38;  /* "Can't commit ~NP because \"cvs status\" is failing." */

static Object string_constant_39;  /* "Can't commit ~NP because ~
				    *                      cvs is not installed or not in the PATH environment variable"
				    */

static Object string_constant_40;  /* "Can't commit ~NP because someone else has committed a different version" */

static Object string_constant_41;  /* "g2_commit_log" */

static Object string_constant_42;  /* "-F" */

static Object string_constant_43;  /* "Committed ~NP." */

static Object string_constant_44;  /* "unedit" */

static Object string_constant_45;  /* "Timed out committing ~NP" */

/* TRY-TO-COMMIT-FILE-1 */
Object try_to_commit_file_1 varargs_1(int, n)
{
    Object pathname_1, message_1;
    Object binary_p, status, version_qm, error_qm, temporary_file;
    Object did_not_time_out_p, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,35);
    INIT_ARGS_nonrelocating();
    pathname_1 = REQUIRED_ARG_nonrelocating();
    message_1 = REQUIRED_ARG_nonrelocating();
    binary_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(G2_operating_system,Qvms))
	return tformat_text_string(2,string_constant_35,pathname_1);
    if ( !TRUEP(Source_code_control_support_enabled_p))
	return tformat_text_string(2,string_constant_36,pathname_1);
    status = get_cvs_status(3,pathname_1,Qstatus,T);
    if ( !TRUEP(status)) {
	version_qm = get_cvs_version();
	if (version_qm) {
	    temp = try_to_put_file_in_source_code_control(3,pathname_1,
		    binary_p,string_constant_37);
	    if (temp)
		return VALUES_1(temp);
	    else
		return tformat_text_string(2,string_constant_38,pathname_1);
	}
	else
	    return tformat_text_string(2,string_constant_39,pathname_1);
    }
    else if (EQ(status,QUnknown)) {
	error_qm = try_to_put_file_in_source_code_control(3,pathname_1,
		binary_p,string_constant_37);
	if (error_qm)
	    return VALUES_1(error_qm);
    }
    else if (memq_function(status,
	    Status_codes_causing_source_code_control_problems_if_saved_p))
	return tformat_text_string(2,string_constant_40,pathname_1);
    temporary_file = write_string_to_temporary_file(string_constant_41,
	    message_1);
    did_not_time_out_p = run_cvs_command_with_string_output(5,
	    string_constant_37,pathname_1,T,string_constant_42,temporary_file);
    gensym_delete_file(temporary_file);
    if (did_not_time_out_p) {
	notify_user(2,string_constant_43,pathname_1);
	run_cvs_command_with_string_output(3,string_constant_44,pathname_1,T);
	return VALUES_1(Nil);
    }
    else
	return tformat_text_string(2,string_constant_45,pathname_1);
}

/* TRY-TO-COMMIT-FILE */
Object try_to_commit_file(pathname_1,message_1)
    Object pathname_1, message_1;
{
    Object message_qm;

    x_note_fn_call(135,36);
    message_qm = try_to_commit_file_1(3,pathname_1,message_1,T);
    if (message_qm)
	return notify_user_1(message_qm);
    else
	return VALUES_1(Nil);
}

/* DIRECTORY-CONTAINS-PATHNAME-P */
Object directory_contains_pathname_p(directory_1,pathname_1)
    Object directory_1, pathname_1;
{
    Object directory_of_pathname, temp;

    x_note_fn_call(135,37);
    directory_of_pathname = gensym_directory_and_above_namestring(1,
	    pathname_1);
    temp =  !((SI_Long)0L == 
	    IFIX(c_directory_contains_directory(directory_1,
	    directory_of_pathname))) ? T : Nil;
    reclaim_text_string(directory_of_pathname);
    return VALUES_1(temp);
}

/* GET-USERS-EDITING-MODULE-FILE */
Object get_users_editing_module_file(pathname_1)
    Object pathname_1;
{
    Object editors, current_user, current_user_in_correct_directory_found_p;
    Object current_user_but_in_another_directory_found_p, user, directory_1;
    Object ab_loop_list_, current_user_editing_from_another_directory_p;
    Object current_user_editing_from_correct_directory_p, others, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_desetq_, temp;

    x_note_fn_call(135,38);
    editors = get_cvs_editors(pathname_1);
    current_user = get_current_user_name();
    current_user_in_correct_directory_found_p = Nil;
    current_user_but_in_another_directory_found_p = Nil;
    user = Nil;
    directory_1 = Nil;
    ab_loop_list_ = editors;
    current_user_editing_from_another_directory_p = Nil;
    current_user_editing_from_correct_directory_p = Nil;
    others = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    user = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    directory_1 = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_user_editing_from_another_directory_p = EQ(user,current_user) ?
	     ( !TRUEP(directory_contains_pathname_p(directory_1,
	    pathname_1)) ? T : Nil) : Qnil;
    current_user_editing_from_correct_directory_p = EQ(user,current_user) ?
	     ( !TRUEP(current_user_editing_from_another_directory_p) ? T : 
	    Nil) : Qnil;
    if (current_user_editing_from_correct_directory_p)
	current_user_in_correct_directory_found_p = T;
    if (current_user_editing_from_another_directory_p)
	current_user_but_in_another_directory_found_p = T;
    if ( !(current_user_editing_from_correct_directory_p || 
	    current_user_but_in_another_directory_found_p)) {
	ab_loopvar__1 = slot_value_cons_1(user,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    others = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_cvs_editors(editors);
    return VALUES_3(others,current_user_editing_from_correct_directory_p,
	    current_user_but_in_another_directory_found_p);
    return VALUES_1(Qnil);
}

static Object string_constant_46;  /* "~A is already being edited by ~L,&" */

static Object string_constant_47;  /* "~A is already being edited in a different directory" */

static Object string_constant_48;  /* "edit" */

static Object string_constant_49;  /* "~A does not want to make edits to ~NP" */

/* REASON-THAT-THE-CURRENT-USER-IS-NOT-THE-ONLY-EDITOR */
Object reason_that_the_current_user_is_not_the_only_editor(pathname_1,
	    force_check_p)
    Object pathname_1, force_check_p;
{
    Object others, current_user_editing_from_correct_directory_p;
    Object current_user_but_in_another_directory_found_p, namestring_1, temp;
    Object result;

    x_note_fn_call(135,39);
    result = get_users_editing_module_file(pathname_1);
    MVS_3(result,others,current_user_editing_from_correct_directory_p,
	    current_user_but_in_another_directory_found_p);
    if (others) {
	namestring_1 = gensym_file_namestring(1,pathname_1);
	temp = tformat_text_string(3,string_constant_46,namestring_1,others);
	reclaim_text_string(namestring_1);
    }
    else if (current_user_but_in_another_directory_found_p) {
	namestring_1 = gensym_file_namestring(1,pathname_1);
	temp = tformat_text_string(2,string_constant_47,namestring_1);
	reclaim_text_string(namestring_1);
    }
    else if (current_user_editing_from_correct_directory_p)
	temp = Nil;
    else if ( !TRUEP(force_check_p)) {
	if (ask_user_about_checking_pathname_out_for_editing(pathname_1)) {
	    run_cvs_command_with_string_output(3,string_constant_48,
		    pathname_1,T);
	    temp = Nil;
	}
	else
	    temp = tformat_text_string(3,string_constant_49,
		    symbol_name_text_string(get_current_user_name()),
		    pathname_1);
    }
    else
	temp = Nil;
    reclaim_gensym_list_1(others);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Result_of_ask_user_about_checking_pathname_out_for_editing, Qresult_of_ask_user_about_checking_pathname_out_for_editing);

DEFINE_VARIABLE_WITH_SYMBOL(Return_from_ask_user_about_checking_pathname_out_for_editing_p, Qreturn_from_ask_user_about_checking_pathname_out_for_editing_p);

DEFINE_VARIABLE_WITH_SYMBOL(Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing, Qworkstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);

DEFINE_VARIABLE_WITH_SYMBOL(Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing, Qui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);

/* ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING-FOR-WORKSTATION */
Object ask_user_about_checking_pathname_out_for_editing_for_workstation(workstation,
	    question)
    Object workstation, question;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(135,40);
    SAVE_STACK();
    if ( !TRUEP(assq_function(workstation,
	    Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing))) 
		{
	Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing 
		= gensym_cons_1(gensym_cons_1(workstation,
		ISVREF(workstation,(SI_Long)17L)),
		Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    SAVE_VALUES(ask_user_about_checking_pathname_out_for_editing_for_workstation_1(question));
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
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object array_constant_4;    /* # */

static Object array_constant_5;    /* # */

static Object Qexit_from_ask_user_about_checking_pathname_out_for_editing;  /* exit-from-ask-user-about-checking-pathname-out-for-editing */

/* ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING-FOR-WORKSTATION-1 */
Object ask_user_about_checking_pathname_out_for_editing_for_workstation_1(question)
    Object question;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(135,41);
    temp = copy_text_string(question);
    temp_1 = copy_constant_wide_string_given_length(array_constant_4,
	    FIX((SI_Long)3L));
    temp_2 = copy_constant_wide_string_given_length(array_constant_5,
	    FIX((SI_Long)2L));
    return enter_dialog(15,temp,temp_1,temp_2,
	    Qexit_from_ask_user_about_checking_pathname_out_for_editing,
	    slot_value_cons_1(T,Nil),
	    Qexit_from_ask_user_about_checking_pathname_out_for_editing,
	    slot_value_cons_1(Nil,Nil),ISVREF(ISVREF(Current_workstation,
	    (SI_Long)11L),(SI_Long)2L),ISVREF(ISVREF(Current_workstation,
	    (SI_Long)11L),(SI_Long)3L),Nil,Nil,Nil,Nil,Nil,T);
}

static Object Qcheck_out_for_editing_question;  /* check-out-for-editing-question */

static Object Qyes;                /* yes */

static Object Qask_user_about_checking_out_a_file;  /* ask-user-about-checking-out-a-file */

static Object Qab_no;              /* no */

static Object Qt2_continuation_for_ask_user_about_checking_pathname_out_for_editing;  /* t2-continuation-for-ask-user-about-checking-pathname-out-for-editing */

/* ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING-FOR-UI-CLIENT-INTERFACE */
Object ask_user_about_checking_pathname_out_for_editing_for_ui_client_interface(ui_client_interface,
	    question)
    Object ui_client_interface, question;
{
    Object temp, temp_1;

    x_note_fn_call(135,42);
    if ( !TRUEP(assq_function(ui_client_interface,
	    Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing))) 
		{
	temp = eval_list_3(Qtext,copy_text_string(question),
		Qcheck_out_for_editing_question);
	temp_1 = eval_list_3(Qbutton,copy_text_string(array_constant_4),Qyes);
	temp_1 = gensym_cons_1(ui_client_interface,enter_dialog_for_t2(5,
		Qask_user_about_checking_out_a_file,eval_list_3(temp,
		temp_1,eval_list_3(Qbutton,
		copy_text_string(array_constant_5),Qab_no)),
		Qt2_continuation_for_ask_user_about_checking_pathname_out_for_editing,
		ui_client_interface,Nil));
	Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing 
		= gensym_cons_1(temp_1,
		Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);
	return VALUES_1(Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);
    }
    else
	return VALUES_1(Nil);
}

/* STOP-ASKING-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING-FOR-WORKSTATION */
Object stop_asking_user_about_checking_pathname_out_for_editing_for_workstation(workstation)
    Object workstation;
{
    Object a, stack, current_stack, ab_loop_it_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(135,43);
    SAVE_STACK();
    a = assq_function(workstation,
	    Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);
    if (a) {
	Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing 
		= delete_gensym_element_1(a,
		Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);
	stack = CDR(a);
	reclaim_gensym_cons_1(a);
	current_stack = ISVREF(workstation,(SI_Long)17L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(current_stack))
	    goto end_loop;
	ab_loop_it_ = EQUAL(stack,current_stack) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	current_stack = M_CDR(current_stack);
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end_1:;
	if (temp) {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = workstation;
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			11);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  10);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    9);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      8);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				7);
			  temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  6);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    5);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
				      (SI_Long)2L);
			      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				      4);
				current_workstation_detail_pane = 
					detail_pane(Current_workstation_window);
				PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					3);
				  current_g2_user_mode_qm = 
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  2);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    1);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      0);
				      next_loop_1:
					temp_1 = ISVREF(workstation,
						(SI_Long)17L);
					if ( !TRUEP(CDR(temp_1)))
					    goto end_loop_1;
					if (EQ(stack,ISVREF(workstation,
						(SI_Long)17L)))
					    goto end_loop_1;
					abort_current_workstation_context(Type_of_current_workstation_context);
					goto next_loop_1;
				      end_loop_1:
					SAVE_VALUES(VALUES_1(Qnil));
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
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* STOP-ASKING-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING-FOR-UI-CLIENT-INTERFACE */
Object stop_asking_user_about_checking_pathname_out_for_editing_for_ui_client_interface(ui_client_interface)
    Object ui_client_interface;
{
    Object a, sequence_number;

    x_note_fn_call(135,44);
    a = assq_function(ui_client_interface,
	    Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);
    if (a) {
	Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing 
		= delete_gensym_element_1(a,
		Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);
	sequence_number = CDR(a);
	reclaim_gensym_cons_1(a);
	return leave_dialog_for_t2(sequence_number);
    }
    else
	return VALUES_1(Nil);
}

/* STOP-ASKING-USERS-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING */
Object stop_asking_users_about_checking_pathname_out_for_editing()
{
    Object temp;

    x_note_fn_call(135,45);
  next_loop:
    if ( 
	    !TRUEP(Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing))
	goto end_loop;
    temp = 
	    FIRST(Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);
    stop_asking_user_about_checking_pathname_out_for_editing_for_workstation(CAR(temp));
    goto next_loop;
  end_loop:
  next_loop_1:
    if ( 
	    !TRUEP(Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing))
	goto end_loop_1;
    temp = 
	    FIRST(Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing);
    stop_asking_user_about_checking_pathname_out_for_editing_for_ui_client_interface(CAR(temp));
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object string_constant_50;  /* "Do you want to check out ~NP for editing?" */

/* ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING */
Object ask_user_about_checking_pathname_out_for_editing(pathname_1)
    Object pathname_1;
{
    Object result_of_ask_user_about_checking_pathname_out_for_editing;
    Object return_from_ask_user_about_checking_pathname_out_for_editing_p;
    Object question, workstation_qm, ui_client_interface_qm, workstation;
    Object ab_loop_list_, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object ui_client_interface, temp_1;
    char temp;
    Declare_special(3);

    x_note_fn_call(135,46);
    result_of_ask_user_about_checking_pathname_out_for_editing = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Result_of_ask_user_about_checking_pathname_out_for_editing,Qresult_of_ask_user_about_checking_pathname_out_for_editing,result_of_ask_user_about_checking_pathname_out_for_editing,
	    2);
      return_from_ask_user_about_checking_pathname_out_for_editing_p = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Return_from_ask_user_about_checking_pathname_out_for_editing_p,Qreturn_from_ask_user_about_checking_pathname_out_for_editing_p,return_from_ask_user_about_checking_pathname_out_for_editing_p,
	      1);
	question = tformat_text_string(2,string_constant_50,pathname_1);
      next_loop:
	if (Return_from_ask_user_about_checking_pathname_out_for_editing_p)
	    goto end_loop;
	workstation_qm = Nil;
	ui_client_interface_qm = Nil;
	workstation_qm = current_workstation_if_usable_for_dialog(T);
	if (workstation_qm)
	    ask_user_about_checking_pathname_out_for_editing_for_workstation(workstation_qm,
		    question);
	else {
	    ui_client_interface_qm = get_current_ui_client_interface();
	    if (ui_client_interface_qm)
		ask_user_about_checking_pathname_out_for_editing_for_ui_client_interface(ui_client_interface_qm,
			question);
	    else {
		workstation = Nil;
		ab_loop_list_ = Workstations_in_service;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_1;
		workstation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ask_user_about_checking_pathname_out_for_editing_for_workstation(workstation,
			question);
		goto next_loop_1;
	      end_loop_1:;
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ui_client_interface = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(Qui_client_interface);
		next_loop_2:
		  if ( !TRUEP(ab_loopvar__1)) {
		    next_loop_3:
		      if ( !TRUEP(ab_loopvar_))
			  goto end_loop_2;
		      ab_loopvar__1 = 
			      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			      Instances_specific_to_this_class_kbprop);
		      ab_loopvar_ = M_CDR(ab_loopvar_);
		      if (ab_loopvar__1)
			  goto end_loop_2;
		      goto next_loop_3;
		    end_loop_2:
		      temp =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      goto end_loop_3;
		  ui_client_interface = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  ask_user_about_checking_pathname_out_for_editing_for_ui_client_interface(ui_client_interface,
			  question);
		  goto next_loop_2;
		end_loop_3:;
		POP_SPECIAL();
	    }
	}
	do_some_workstation_processing(Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing);
	g2ext_sys_sleep((SI_Long)50L);
	goto next_loop;
      end_loop:
	reclaim_text_string(question);
	stop_asking_users_about_checking_pathname_out_for_editing();
	temp_1 = Result_of_ask_user_about_checking_pathname_out_for_editing;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* T2-CONTINUATION-FOR-ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING */
Object t2_continuation_for_ask_user_about_checking_pathname_out_for_editing(sequence_number,
	    client_item)
    Object sequence_number, client_item;
{
    Object button, temp;

    x_note_fn_call(135,47);
    button = leave_dialog_for_t2(sequence_number);
    remove_dialog_info_from_ui_client_interface_dialog_list(sequence_number,
	    ISVREF(client_item,(SI_Long)26L));
    if (EQ(button,Qyes))
	temp = T;
    else if (EQ(button,Qab_no))
	temp = Nil;
    else
	temp = Qnil;
    return exit_from_ask_user_about_checking_pathname_out_for_editing(temp);
}

/* EXIT-FROM-ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING */
Object exit_from_ask_user_about_checking_pathname_out_for_editing(value)
    Object value;
{
    x_note_fn_call(135,48);
    Result_of_ask_user_about_checking_pathname_out_for_editing = value;
    Return_from_ask_user_about_checking_pathname_out_for_editing_p = T;
    return VALUES_1(Return_from_ask_user_about_checking_pathname_out_for_editing_p);
}

static Object Qscc_update;         /* scc-update */

static Object Qscc_edit;           /* scc-edit */

static Object Qscc_unedit;         /* scc-unedit */

static Object Qscc_revert;         /* scc-revert */

static Object string_constant_51;  /* "revert" */

static Object Qscc_commit;         /* scc-commit */

static Object string_constant_52;  /* "Can't ~a ~NP because source code control does not run on VMS" */

static Object string_constant_53;  /* "Can't perform the source code control operation ~a on ~NP ~
				    *                 because it is not under source code control"
				    */

static Object string_constant_54;  /* "Can't perform the source control operation ~a on ~NP ~
				    *                 because source code control is not enabled"
				    */

/* DO-SCC-COMMAND-1 */
Object do_scc_command_1 varargs_1(int, n)
{
    Object command_symbol, default_pathname_qm;
    Object log_message_for_commit_after_saving_qm, operation_name, scc_type_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,49);
    INIT_ARGS_nonrelocating();
    command_symbol = REQUIRED_ARG_nonrelocating();
    default_pathname_qm = REQUIRED_ARG_nonrelocating();
    log_message_for_commit_after_saving_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (EQ(command_symbol,Qscc_update))
	operation_name = string_constant_15;
    else if (EQ(command_symbol,Qscc_edit))
	operation_name = string_constant_48;
    else if (EQ(command_symbol,Qscc_unedit))
	operation_name = string_constant_44;
    else if (EQ(command_symbol,Qscc_revert))
	operation_name = string_constant_51;
    else if (EQ(command_symbol,Qscc_commit))
	operation_name = string_constant_37;
    else
	operation_name = Qnil;
    if (EQ(G2_operating_system,Qvms))
	return tformat_text_string(3,string_constant_52,operation_name,
		default_pathname_qm);
    scc_type_qm = Source_code_control_support_enabled_p ? 
	    file_is_in_source_code_control_p(default_pathname_qm) : Qnil;
    if ( !TRUEP(scc_type_qm)) {
	if (Source_code_control_support_enabled_p)
	    return tformat_text_string(3,string_constant_53,operation_name,
		    default_pathname_qm);
	else
	    return tformat_text_string(3,string_constant_54,operation_name,
		    default_pathname_qm);
    }
    if (EQ(command_symbol,Qscc_update))
	return try_to_get_newest_version_of_file_1(2,default_pathname_qm,Nil);
    else if (EQ(command_symbol,Qscc_edit)) {
	if (EQ(scc_type_qm,Qcvs)) {
	    run_cvs_command_with_string_output(3,string_constant_48,
		    default_pathname_qm,T);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_symbol,Qscc_unedit)) {
	if (EQ(scc_type_qm,Qcvs)) {
	    run_cvs_command_with_string_output(3,string_constant_44,
		    default_pathname_qm,T);
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_symbol,Qscc_revert))
	return try_to_get_newest_version_of_file_1(2,default_pathname_qm,T);
    else if (EQ(command_symbol,Qscc_commit))
	return try_to_commit_file_1(2,default_pathname_qm,
		log_message_for_commit_after_saving_qm);
    else
	return VALUES_1(Qnil);
}

/* DO-SCC-COMMAND */
Object do_scc_command varargs_1(int, n)
{
    Object command_symbol, default_pathname_qm;
    Object log_message_for_commit_after_saving_qm, error_message_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,50);
    INIT_ARGS_nonrelocating();
    command_symbol = REQUIRED_ARG_nonrelocating();
    default_pathname_qm = REQUIRED_ARG_nonrelocating();
    log_message_for_commit_after_saving_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    error_message_qm = do_scc_command_1(3,command_symbol,
	    default_pathname_qm,log_message_for_commit_after_saving_qm);
    if (error_message_qm) {
	notify_user_1(error_message_qm);
	return VALUES_1(Nil);
    }
    else {
	recompute_editability_of_modules();
	update_saving_parameters_status_attributes(1,Qstar);
	return VALUES_1(T);
    }
}

static Object Qcurrent_file_for_module;  /* current-file-for-module */

static Object Qreason_module_is_not_editable;  /* reason-module-is-not-editable */

static Object Qmodule_file_is_read_only;  /* module-file-is-read-only */

static Object Qsource_code_control_for_module_file;  /* source-code-control-for-module-file */

static Object Qmodule_file_is_checked_out_for_writing_by_current_user;  /* module-file-is-checked-out-for-writing-by-current-user */

static Object Qusers_currently_having_module_file_checked_out;  /* users-currently-having-module-file-checked-out */

static Object Qsource_code_control_status_for_module_file;  /* source-code-control-status-for-module-file */

static Object Qversion_of_checked_out_module_file;  /* version-of-checked-out-module-file */

static Object Qnewest_version_of_module_file;  /* newest-version-of-module-file */

static Object Qbranch_of_checked_out_module_file;  /* branch-of-checked-out-module-file */

/* UPDATE-SAVING-PARAMETERS-STATUS-ATTRIBUTES */
Object update_saving_parameters_status_attributes varargs_1(int, n)
{
    Object module_qm, suite, ab_loop_list_, module_information_instance;
    Object module_name, saving_parameters;
    Object internal_status_of_most_recent_file_operation, pathname_qm;
    Object namestring_qm, local_source_code_control_buffer;
    Object local_source_code_control_number_of_characters;
    Object in_local_source_code_control_scope_p, temp, others;
    Object current_user_editing_from_correct_directory_p;
    Object current_user_but_in_another_directory_found_p;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,51);
    INIT_ARGS_nonrelocating();
    module_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(module_qm,Qstar)) {
	suite = Nil;
	ab_loop_list_ = Modules_and_system_tables_a_list;
	module_information_instance = Nil;
	module_name = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	suite = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	module_information_instance = FIRST(suite);
	module_name = ISVREF(module_information_instance,(SI_Long)23L);
	if (module_name)
	    update_saving_parameters_status_attributes(1,module_name);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	saving_parameters = get_saving_parameters(module_qm);
	PUSH_SPECIAL_WITH_SYMBOL(Saving_parameters,Qsaving_parameters,saving_parameters,
		4);
	  if (Saving_parameters) {
	      internal_status_of_most_recent_file_operation = 
		      File_operation_succeeded_code;
	      PUSH_SPECIAL_WITH_SYMBOL(Internal_status_of_most_recent_file_operation,Qinternal_status_of_most_recent_file_operation,internal_status_of_most_recent_file_operation,
		      3);
		pathname_qm = get_true_pathname_of_module_if_any(module_qm);
		namestring_qm = pathname_qm ? gensym_namestring(1,
			pathname_qm) : Nil;
		local_source_code_control_buffer = Nil;
		local_source_code_control_number_of_characters = Nil;
		in_local_source_code_control_scope_p = T;
		PUSH_SPECIAL_WITH_SYMBOL(In_local_source_code_control_scope_p,Qin_local_source_code_control_scope_p,in_local_source_code_control_scope_p,
			2);
		  PUSH_SPECIAL_WITH_SYMBOL(Local_source_code_control_number_of_characters,Qlocal_source_code_control_number_of_characters,local_source_code_control_number_of_characters,
			  1);
		    PUSH_SPECIAL_WITH_SYMBOL(Local_source_code_control_buffer,Qlocal_source_code_control_buffer,local_source_code_control_buffer,
			    0);
		      change_slot_value(3,Saving_parameters,
			      Qcurrent_file_for_module,namestring_qm);
		      temp = Saving_parameters;
		      change_slot_value(3,temp,
			      Qreason_module_is_not_editable,
			      copy_for_slot_value(get_reason_module_is_not_editable(2,
			      module_qm,T)));
		      change_slot_value(3,Saving_parameters,
			      Qmodule_file_is_read_only, 
			      !TRUEP(lookup_kb_specific_property_value(module_qm,
			      Module_is_writable_p_kbprop)) ? T : Nil);
		      temp = Saving_parameters;
		      change_slot_value(3,temp,
			      Qsource_code_control_for_module_file,
			      namestring_qm ? 
			      file_is_in_source_code_control_p(pathname_qm) 
			      : Nil);
		      if (pathname_qm)
			  result = get_users_editing_module_file(pathname_qm);
		      else
			  result = VALUES_1(Nil);
		      MVS_3(result,others,
			      current_user_editing_from_correct_directory_p,
			      current_user_but_in_another_directory_found_p);
		      if (current_user_but_in_another_directory_found_p) {
			  temp = get_current_user_name();
			  others = slot_value_cons_1(temp,others);
		      }
		      change_slot_value(3,Saving_parameters,
			      Qmodule_file_is_checked_out_for_writing_by_current_user,
			      current_user_editing_from_correct_directory_p);
		      change_slot_value(3,Saving_parameters,
			      Qusers_currently_having_module_file_checked_out,
			      others);
		      temp = Saving_parameters;
		      change_slot_value(3,temp,
			      Qsource_code_control_status_for_module_file,
			      pathname_qm ? 
			      status_of_currently_checked_out_file(pathname_qm) 
			      : Nil);
		      temp = Saving_parameters;
		      change_slot_value(3,temp,
			      Qversion_of_checked_out_module_file,
			      pathname_qm ? 
			      version_of_currently_checked_out_file(pathname_qm) 
			      : Nil);
		      temp = Saving_parameters;
		      change_slot_value(3,temp,
			      Qnewest_version_of_module_file,pathname_qm ? 
			      newest_version_of_checked_out_file(pathname_qm) 
			      : Nil);
		      temp = Saving_parameters;
		      temp = change_slot_value(3,temp,
			      Qbranch_of_checked_out_module_file,
			      pathname_qm ? 
			      branch_of_checked_out_file(pathname_qm) : Nil);
		      if (Local_source_code_control_buffer)
			  reclaim_simple_gensym_string(Local_source_code_control_buffer);
		      result = VALUES_1(temp);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
}

/* G2-UPDATE-SAVING-PARAMETERS-STATUS-ATTRIBUTES */
Object g2_update_saving_parameters_status_attributes()
{
    x_note_fn_call(135,52);
    return update_saving_parameters_status_attributes(1,Qstar);
}

static Object array_constant_6;    /* # */

/* WRITE-STATUS-TEXT-OR-NONE-FROM-SLOT */
Object write_status_text_or_none_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(135,53);
    temp = value;
    if (temp);
    else
	temp = array_constant_6;
    return twrite(temp);
}

/* STATUS-TEXT-OR-NONE-EVALUATION-GETTER */
Object status_text_or_none_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,54);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-SOURCE-CODE-CONTROL-NAME-FROM-SLOT */
Object write_source_code_control_name_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(135,55);
    temp = value;
    if (temp);
    else
	temp = array_constant_6;
    return twrite(temp);
}

/* SOURCE-CODE-CONTROL-NAME-EVALUATION-GETTER */
Object source_code_control_name_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,56);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

/* WRITE-USER-NAME-SEQUENCE-FROM-SLOT */
Object write_user_name_sequence_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object len, user, ab_loop_list_, firstp, lastp, ab_loop_iter_flag_, temp;
    SI_Long i;

    x_note_fn_call(135,57);
    if (CONSP(value)) {
	len = Nil;
	user = Nil;
	ab_loop_list_ = value;
	firstp = T;
	i = (SI_Long)1L;
	lastp = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	len = length(value);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	user = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_)) {
	    firstp = Nil;
	    i = i + (SI_Long)1L;
	}
	lastp = i == IFIX(len) ? T : Nil;
	if ( !TRUEP(firstp)) {
	    if (IFIX(len) == (SI_Long)2L)
		temp = array_constant_7;
	    else if (lastp)
		temp = array_constant_8;
	    else
		temp = array_constant_9;
	    twrite(temp);
	}
	twrite(stringw(user));
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return twrite(array_constant_6);
}

/* USER-NAME-SEQUENCE-EVALUATION-GETTER */
Object user_name_sequence_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,58);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object string_constant_55;  /* "yes" */

static Object string_constant_56;  /* "no" */

/* WRITE-READONLY-YES-OR-NO-FROM-SLOT */
Object write_readonly_yes_or_no_from_slot(yes_or_no,gensymed_symbol)
    Object yes_or_no, gensymed_symbol;
{
    x_note_fn_call(135,59);
    return twrite_general_string(yes_or_no ? string_constant_55 : 
	    string_constant_56);
}

/* READONLY-YES-OR-NO-EVALUATION-GETTER */
Object readonly_yes_or_no_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,60);
    GENSYM_RETURN_ONE(slot_value ? Evaluation_true_value : 
	    Evaluation_false_value);
    return VALUES_1(Nil);
}

/* PUT-ENABLE-JOURNALLING-WHERE-SLOT-IS-ABSENT */
Object put_enable_journalling_where_slot_is_absent(saving_parameters_frame,
	    value)
    Object saving_parameters_frame, value;
{
    x_note_fn_call(135,61);
    return VALUES_1(Nil);
}

/* PUT-PATHNAME-FORMAT-WHERE-SLOT-IS-ABSENT */
Object put_pathname_format_where_slot_is_absent(saving_parameters_frame,value)
    Object saving_parameters_frame, value;
{
    x_note_fn_call(135,62);
    return VALUES_1(Nil);
}

/* PUT-NUMBER-OF-BACKUP-FILES-WHERE-SLOT-IS-ABSENT */
Object put_number_of_backup_files_where_slot_is_absent(saving_parameters_frame,
	    value)
    Object saving_parameters_frame, value;
{
    x_note_fn_call(135,63);
    return VALUES_1(Nil);
}

/* PUT-JOURNALLING-STATUS-WHERE-SLOT-IS-ABSENT */
Object put_journalling_status_where_slot_is_absent(saving_parameters_frame,
	    value)
    Object saving_parameters_frame, value;
{
    x_note_fn_call(135,64);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* GET-SAVING-PARAMETERS */
Object get_saving_parameters(module_qm)
    Object module_qm;
{
    Object frame, ab_loop_list_, x2, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(135,65);
    if (module_qm) {
	frame = Nil;
	ab_loop_list_ = 
		find_system_table_suite_with_module_assignment(module_qm);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	frame = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(frame);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Saving_parameters);
}

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

/* WRITE-CLEAR-TEXT-HISTORY-FROM-SLOT */
Object write_clear_text_history_from_slot(slot_value,gensymed_symbol)
    Object slot_value, gensymed_symbol;
{
    Object differences;

    x_note_fn_call(135,66);
    if ( !FIXNUMP(slot_value) || IFIX(slot_value) == (SI_Long)0L)
	return twrite(array_constant_6);
    else if ((SI_Long)0L != IFIX(slot_value)) {
	twrite(array_constant_10);
	differences = 
		get_kb_has_been_loaded_from_clear_text_with_differences(slot_value);
	if (differences) {
	    tformat(2,array_constant_11,differences);
	    return reclaim_gensym_list_1(differences);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GET-KB-CLEAR-TEXT-HISTORY */
Object get_kb_clear_text_history(module,currentp)
    Object module, currentp;
{
    Object frame_qm, temp, bits, suite, ab_loop_list_, frame, ab_loop_list__1;
    Object x2, gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(135,67);
    if (module)
	frame_qm = get_saving_parameters(module);
    else if (currentp)
	frame_qm = Saving_parameters;
    else
	frame_qm = Nil;
    if (frame_qm) {
	temp = ISVREF(frame_qm,(SI_Long)23L);
	if (temp);
	else
	    temp = FIX((SI_Long)0L);
    }
    else
	temp = Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	bits = FIX((SI_Long)0L);
	suite = Nil;
	ab_loop_list_ = Modules_and_system_tables_a_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	suite = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	frame = Nil;
	ab_loop_list__1 = suite;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	frame = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (SIMPLE_VECTOR_P(frame) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		!EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qsaving_parameters,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_2 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_3 = (SI_Long)1L;
		    gensymed_symbol_4 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol_2 = IFIX(bits);
	    temp = ISVREF(frame,(SI_Long)23L);
	    if (temp);
	    else
		temp = FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(temp);
	    bits = FIX(gensymed_symbol_2 | gensymed_symbol_3);
	}
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	return VALUES_1(bits);
	return VALUES_1(Qnil);
    }
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* GET-KB-HAS-BEEN-LOADED-FROM-CLEAR-TEXT-WITH-DIFFERENCES */
Object get_kb_has_been_loaded_from_clear_text_with_differences(module_qm)
    Object module_qm;
{
    Object bits, mask, ab_loop_list_, name, ab_loop_list__1, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(135,68);
    bits = FIXNUMP(module_qm) ? module_qm : 
	    get_kb_clear_text_history(module_qm,Nil);
    mask = Nil;
    ab_loop_list_ = list_constant_1;
    name = Nil;
    ab_loop_list__1 = list_constant_2;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mask = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    name = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ((SI_Long)0L != IFIX(FIXNUM_LOGAND(mask,bits))) {
	ab_loopvar__2 = gensym_cons_1(name,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qclear_text_history;  /* clear-text-history */

/* NOTE-MODIFICATION-OF-MODULE-FOR-CLEAR-TEXT */
Object note_modification_of_module_for_clear_text(module1_qm,module2_qm)
    Object module1_qm, module2_qm;
{
    Object x2, debugging_parameters1, bits_from_module2, temp_1;
    SI_Long gensymed_symbol, gensymed_symbol_1, svref_new_value;
    char temp;

    x_note_fn_call(135,69);
    if (SIMPLE_VECTOR_P(module1_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(module1_qm)) > (SI_Long)2L &&  
	    !EQ(ISVREF(module1_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(module1_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	module1_qm = get_module_block_is_in(module1_qm);
    else if (SYMBOLP(module1_qm));
    else
	module1_qm = Nil;
    if (module1_qm) {
	if (SIMPLE_VECTOR_P(module2_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(module2_qm)) > (SI_Long)2L 
		&&  !EQ(ISVREF(module2_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(module2_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    module2_qm = get_module_block_is_in(module2_qm);
	else if (SYMBOLP(module2_qm));
	else
	    module2_qm = Nil;
	debugging_parameters1 = get_saving_parameters(module1_qm);
	bits_from_module2 = get_kb_clear_text_history(module2_qm,Nil);
	if (debugging_parameters1) {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(debugging_parameters1,
			Qclear_text_history);
	    temp_1 = ISVREF(debugging_parameters1,(SI_Long)23L);
	    if (temp_1);
	    else
		temp_1 = FIX((SI_Long)0L);
	    gensymed_symbol = IFIX(temp_1);
	    gensymed_symbol_1 = IFIX(bits_from_module2);
	    svref_new_value = gensymed_symbol | gensymed_symbol_1;
	    ISVREF(debugging_parameters1,(SI_Long)23L) = FIX(svref_new_value);
	    return VALUES_1(T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type;  /* type-is-sub-element-of-g2-attribute-and-value-is-attribute-of-type */

static Object string_constant_57;  /* "type is sub element of g2 attribute and value is attribute of type" */

static Object Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type;  /* type-is-sub-element-of-g2-attribute-and-value-is-contents-of-type */

static Object string_constant_58;  /* "type is sub element of g2 attribute and value is contents of type" */

static Object Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute;  /* type-is-attribute-of-g2-attribute-and-value-is-contents-of-g2-attribute */

static Object string_constant_59;  /* "type is attribute of g2 attribute and value is contents of g2 attribute" */

/* WRITE-XML-PRIMITIVE-VALUE-STYLE-FROM-SLOT */
Object write_xml_primitive_value_style_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(135,70);
    if (EQ(value,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type))
	temp = string_constant_57;
    else if (EQ(value,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type))
	temp = string_constant_58;
    else if (EQ(value,
	    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute))
	temp = string_constant_59;
    else
	temp = string_constant_1;
    return twrite(temp);
}

/* COMPILE-XML-PRIMITIVE-VALUE-STYLE-FOR-SLOT */
Object compile_xml_primitive_value_style_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,71);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(parse_result);
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

/* XML-PRIMITIVE-VALUE-STYLE-EVALUATION-SETTER */
Object xml_primitive_value_style_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,72);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_xml_primitive_value_style_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_xml_primitive_value_style_evaluation_setter:
    return result;
}

/* XML-PRIMITIVE-VALUE-STYLE-EVALUATION-GETTER */
Object xml_primitive_value_style_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,73);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qallow_changes;      /* allow-changes */

static Object string_constant_60;  /* "allow changes" */

static Object string_constant_61;  /* "do not allow changes" */

static Object string_constant_62;  /* ", " */

static Object string_constant_63;  /* "warn when edit attempted" */

static Object string_constant_64;  /* "do not warn when edit attempted" */

/* WRITE-UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-FROM-SLOT */
Object write_unsavable_change_protection_specification_from_slot(value,
	    gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(135,74);
    twrite(memq_function(Qallow_changes,value) ? string_constant_60 : 
	    string_constant_61);
    twrite(string_constant_62);
    return twrite(memq_function(Qwarn,value) ? string_constant_63 : 
	    string_constant_64);
}

static Object string_constant_65;  /* "default" */

/* WRITE-UNSAVABLE-CHANGE-PROTECTION-FROM-SLOT */
Object write_unsavable_change_protection_from_slot(value,frame)
    Object value, frame;
{
    x_note_fn_call(135,75);
    if (CONSP(value))
	return write_unsavable_change_protection_specification_from_slot(value,
		frame);
    else
	return twrite(string_constant_65);
}

/* COMPILE-UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-FOR-SLOT */
Object compile_unsavable_change_protection_specification_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,76);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(parse_result);
}

/* COMPILE-UNSAVABLE-CHANGE-PROTECTION-FOR-SLOT */
Object compile_unsavable_change_protection_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(135,77);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(parse_result);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qtruth_value;        /* truth-value */

static Object Qdo_not_allow_changes;  /* do-not-allow-changes */

static Object Qdo_not_warn;        /* do-not-warn */

/* UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-EVALUATION-SETTER */
Object unsavable_change_protection_specification_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,78);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_unsavable_change_protection_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qallow_changes,Nil);
    temp = CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,
	    Qallow_changes,Nil)),Qtruth_value) && 
	    EQ(M_CAR(estructure_slot(gensymed_symbol,Qallow_changes,Nil)),
	    Truth) ? Qallow_changes : Qdo_not_allow_changes;
    temp_1 = estructure_slot(gensymed_symbol,Qwarn,Nil);
    result = phrase_list_2(temp,CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qwarn,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qwarn,Nil)),Truth) ? Qwarn : Qdo_not_warn);
  end_unsavable_change_protection_specification_evaluation_setter:
    return result;
}

/* UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-EVALUATION-GETTER */
Object unsavable_change_protection_specification_evaluation_getter(slot_value,
	    frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol;

    x_note_fn_call(135,79);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qallow_changes,
	    memq_function(Qallow_changes,slot_value) ? 
	    Evaluation_true_value : Evaluation_false_value);
    set_evaluation_structure_slot(gensymed_symbol,Qwarn,
	    memq_function(Qdo_not_warn,slot_value) ? Evaluation_true_value 
	    : Evaluation_false_value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qunsavable_change_protection_specification;  /* unsavable-change-protection-specification */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qdefault;            /* default */

/* UNSAVABLE-CHANGE-PROTECTION-EVALUATION-SETTER */
Object unsavable_change_protection_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(135,80);
    if ( !TRUEP(gensymed_symbol)) {
	value_at_type_failure = Nil;
	type_at_type_failure = Nil;
	reason_for_type_failure = Nil;
	context_of_type_failure = Nil;
	last_slot_checked_of_type_failure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Last_slot_checked_of_type_failure,Qlast_slot_checked_of_type_failure,last_slot_checked_of_type_failure,
		4);
	  PUSH_SPECIAL_WITH_SYMBOL(Context_of_type_failure,Qcontext_of_type_failure,context_of_type_failure,
		  3);
	    PUSH_SPECIAL_WITH_SYMBOL(Reason_for_type_failure,Qreason_for_type_failure,reason_for_type_failure,
		    2);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_at_type_failure,Qtype_at_type_failure,type_at_type_failure,
		      1);
		PUSH_SPECIAL_WITH_SYMBOL(Value_at_type_failure,Qvalue_at_type_failure,value_at_type_failure,
			0);
		  if ( 
			  !TRUEP(type_specification_type_p__with_explanation(evaluation_value,
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_unsavable_change_protection_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunsavable_change_protection_specification),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
    else
	result = VALUES_1(Qdefault);
  end_safe_category_setter_calling_block:
  end_unsavable_change_protection_evaluation_setter:
    return result;
}

/* UNSAVABLE-CHANGE-PROTECTION-EVALUATION-GETTER */
Object unsavable_change_protection_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(135,81);
    if (EQ(slot_value,Qdefault))
	temp = Nil;
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunsavable_change_protection_specification),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qdefault_unsavable_change_protection;  /* default-unsavable-change-protection */

static Object Qunsavable_change_protection;  /* unsavable-change-protection */

/* GET-UNSAVABLE-CHANGE-PROTECTION */
Object get_unsavable_change_protection(module)
    Object module;
{
    Object module_saving_parameters_qm, temp, value;

    x_note_fn_call(135,82);
    module_saving_parameters_qm = get_saving_parameters(module);
    if ( !TRUEP(module_saving_parameters_qm))
	temp = get_lookup_slot_value(get_saving_parameters(Nil),
		Qdefault_unsavable_change_protection);
    else {
	value = get_lookup_slot_value(get_saving_parameters(module),
		Qunsavable_change_protection);
	temp = EQ(value,Qdefault) ? 
		get_lookup_slot_value(get_saving_parameters(Nil),
		Qdefault_unsavable_change_protection) : value;
    }
    return VALUES_1(temp);
}

/* WARN-ON-UNSAVABLE-CHANGE-P */
Object warn_on_unsavable_change_p(module)
    Object module;
{
    Object temp;

    x_note_fn_call(135,83);
    temp =  ! !TRUEP(memq_function(Qwarn,
	    get_unsavable_change_protection(module))) ? T : Nil;
    return VALUES_1(temp);
}

/* ALLOW-UNSAVABLE-CHANGE-P */
Object allow_unsavable_change_p(module)
    Object module;
{
    Object temp;

    x_note_fn_call(135,84);
    temp =  ! !TRUEP(memq_function(Qallow_changes,
	    get_unsavable_change_protection(module))) ? T : Nil;
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(All_permanently_changed_things_are_marked, Qall_permanently_changed_things_are_marked);

static Object string_constant_66;  /* "ok to write backup or journal" */

static Object string_constant_67;  /* "cannot write backup or journal until after a kb is saved" */

/* WRITE-JOURNALLING-STATUS-FROM-SLOT */
Object write_journalling_status_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(135,85);
    return twrite(All_permanently_changed_things_are_marked ? 
	    string_constant_66 : string_constant_67);
}

static Object string_constant_68;  /* "none" */

/* WRITE-BASIS-KB-FROM-SLOT */
Object write_basis_kb_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(135,86);
    temp = value;
    if (temp);
    else
	temp = string_constant_68;
    return twrite(temp);
}

/* BASIS-KB-EVALUATION-GETTER */
Object basis_kb_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,87);
    GENSYM_RETURN_ONE(slot_value ? (FIXNUMP(slot_value) || slot_value && 
	    SYMBOLP(slot_value) ? slot_value : 
	    copy_evaluation_value_1(slot_value)) : Qnone);
    return VALUES_1(Nil);
}

/* WRITE-FILENAME-OF-BASIS-KB-FROM-SLOT */
Object write_filename_of_basis_kb_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(135,88);
    temp = value;
    if (temp);
    else
	temp = string_constant_68;
    return twrite(temp);
}

/* FILE-NAME-OF-BASIS-KB-EVALUATION-GETTER */
Object file_name_of_basis_kb_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(135,89);
    GENSYM_RETURN_ONE(slot_value ? (FIXNUMP(slot_value) || slot_value && 
	    SYMBOLP(slot_value) ? slot_value : 
	    copy_evaluation_value_1(slot_value)) : Qnone);
    return VALUES_1(Nil);
}

/* CHANGE-ALL-PERMANENTLY-CHANGED-THINGS-ARE-MARKED */
Object change_all_permanently_changed_things_are_marked(logical_value)
    Object logical_value;
{
    Object modified_value;

    x_note_fn_call(135,90);
    modified_value = logical_value;
    if ( !EQ(modified_value,All_permanently_changed_things_are_marked)) {
	All_permanently_changed_things_are_marked = logical_value;
	return VALUES_1(All_permanently_changed_things_are_marked);
    }
    else
	return VALUES_1(Nil);
}

/* INSTALL-SYSTEM-TABLE-FOR-SAVING-PARAMETERS */
Object install_system_table_for_saving_parameters(saving_parameters)
    Object saving_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(135,91);
    PUSH_SPECIAL_WITH_SYMBOL(Saving_parameters,Qsaving_parameters,saving_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-SAVING-PARAMETERS */
Object deinstall_system_table_for_saving_parameters(saving_parameters)
    Object saving_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(135,92);
    PUSH_SPECIAL_WITH_SYMBOL(Saving_parameters,Qsaving_parameters,saving_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* RESTORE-BACKUP-JOURNALING-PARAMETERS-TO-DEFAULT-VALUES */
Object restore_backup_journaling_parameters_to_default_values()
{
    x_note_fn_call(135,93);
    Noting_changes_to_kb_p = Nil;
    All_permanently_changed_things_are_marked = Nil;
    return VALUES_1(All_permanently_changed_things_are_marked);
}

static Object Qprogress_through_file;  /* progress-through-file */

static Object Qstatus_of_file_progress_qm;  /* status-of-file-progress? */

/* UPDATE-FILE-PROGRESS-DISPLAY-STATUS */
Object update_file_progress_display_status(status)
    Object status;
{
    Object display_qm, svref_new_value;

    x_note_fn_call(135,94);
    display_qm = ISVREF(Current_kb_save,(SI_Long)13L);
    if (display_qm) {
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	ISVREF(display_qm,(SI_Long)24L) = svref_new_value;
	change_slot_value(3,display_qm,Qprogress_through_file,
		ISVREF(Current_kb_save,(SI_Long)30L));
	change_slot_value(3,display_qm,Qstatus_of_file_progress_qm,status);
	note_update_to_file_progress(1,display_qm);
	if ( !TRUEP(Stack_of_slot_value_changes))
	    force_process_drawing();
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Clear_text_saving_problems_were_encountered_p, Qclear_text_saving_problems_were_encountered_p);

DEFINE_VARIABLE_WITH_SYMBOL(Return_from_save_to_caller_for_continuation_qm, Qreturn_from_save_to_caller_for_continuation_qm);

static Object Qsave_kb_internal;   /* save-kb-internal */

static Object Qkb_save;            /* kb-save */

static Object Qok_kb_save;         /* ok-kb-save */

static Object Qbackup;             /* backup */

/* SAVE-KB */
Object save_kb varargs_1(int, n)
{
    Object pathname_or_module_saving_schedule;
    Object type_of_kb_save_qm, emit_c_code_qm;
    Object log_message_for_commit_after_saving_qm;
    Object index_of_top_of_backtrace_stack, temp, temp_1;
    Object enable_saving_compiled_kbs_p, type_of_kb_save;
    Object ok_file_saving_mode_qm, number_of_streams_to_open_initially;
    Object current_saving_context, current_computation_flags;
    Object write_xml_object_items_collected, total_items_in_file;
    Object current_kb_save, ab_loop_list_, temp_3;
    char saving_modules_p, temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(9);
    Object result;

    x_note_fn_call(135,95);
    INIT_ARGS_nonrelocating();
    pathname_or_module_saving_schedule = REQUIRED_ARG_nonrelocating();
    type_of_kb_save_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    emit_c_code_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    log_message_for_commit_after_saving_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    8);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Qsave_kb_internal;
      }
      enable_saving_compiled_kbs_p = emit_c_code_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
	      7);
	type_of_kb_save = type_of_kb_save_qm;
	if (type_of_kb_save);
	else
	    type_of_kb_save = Qkb_save;
	ok_file_saving_mode_qm = EQ(type_of_kb_save,Qok_kb_save) ? T : Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Ok_file_saving_mode_qm,Qok_file_saving_mode_qm,ok_file_saving_mode_qm,
		6);
	  saving_modules_p = LISTP(pathname_or_module_saving_schedule);
	  if ( !(reject_save_kb_if_run_time_only(type_of_kb_save) || 
		  reject_save_kb_if_save_or_backup_in_progress() || 
		  reject_save_kb_if_not_authorized() || 
		  reject_save_kb_if_not_savable() || 
		  reject_save_kb_if_filename_problems(pathname_or_module_saving_schedule) 
		  || (saving_modules_p ? 
		  TRUEP(reject_save_kb_if_saving_modules_without_consistency()) 
		  : TRUEP(Nil)))) {
	      if (Clear_text_saving_problems_were_encountered_p) {
		  reclaim_gensym_list_1(Clear_text_saving_problems_were_encountered_p);
		  Clear_text_saving_problems_were_encountered_p = Nil;
	      }
	      prepare_image_definitions_for_saving();
	      prepare_blocks_and_connections_for_saving(saving_modules_p ? 
		      T : Nil);
	      Current_saving_context_qm = 
		      make_saving_context(type_of_kb_save,
		      pathname_or_module_saving_schedule,emit_c_code_qm,
		      log_message_for_commit_after_saving_qm);
	      Noting_changes_to_kb_p = T;
	      Kb_save_termination_reason_qm = Nil;
	      if ( !EQ(type_of_kb_save,Qbackup))
		  Basis_kb_frame_serial_number = Current_frame_serial_number;
	      if (EQ(type_of_kb_save,Qbackup)) {
		  temp = Current_saving_context;
		  temp_1 = Items_deleted_since_load_or_save;
		  SVREF(temp,FIX((SI_Long)6L)) = temp_1;
		  temp = Current_saving_context;
		  temp_1 = Items_deleted_since_load_or_save_tail;
		  SVREF(temp,FIX((SI_Long)7L)) = temp_1;
	      }
	      else
		  reclaim_items_deleted_since_load_or_save();
	      number_of_streams_to_open_initially = FIX((SI_Long)1L);
	      current_saving_context = Current_saving_context_qm;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
		      5);
		enable_saving_compiled_kbs_p = 
			ISVREF(Current_saving_context,(SI_Long)10L);
		PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
			4);
		  current_computation_flags = Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  3);
		    write_xml_object_items_collected = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
			    2);
		      total_items_in_file = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
			      1);
			Current_computation_flags = 
				FIX(IFIX(Current_computation_flags) &  
				~(SI_Long)2048L);
			Current_computation_flags = 
				FIX(IFIX(Current_computation_flags) &  
				~(SI_Long)4096L);
			current_kb_save = Nil;
			ab_loop_list_ = ISVREF(Current_saving_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
				0);
			next_loop:
			  if ( !TRUEP(ab_loop_list_))
			      goto end_loop;
			  Current_kb_save = M_CAR(ab_loop_list_);
			  ab_loop_list_ = M_CDR(ab_loop_list_);
			  if (IFIX(number_of_streams_to_open_initially) == 
				  (SI_Long)0L) {
			      temp_2 = TRUEP(T);
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      goto end_initial_stream_opening;
			  }
			  if ( !TRUEP(open_kb_save_or_backup_stream())) {
			      temp_2 = TRUEP(Nil);
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      POP_SPECIAL();
			      goto end_initial_stream_opening;
			  }
			  number_of_streams_to_open_initially = 
				  FIXNUM_SUB1(number_of_streams_to_open_initially);
			  goto next_loop;
			end_loop:;
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      temp_2 = TRUEP(T);
	    end_initial_stream_opening:;
	      if (temp_2) {
		  current_saving_context = Current_saving_context_qm;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
			  5);
		    enable_saving_compiled_kbs_p = 
			    ISVREF(Current_saving_context,(SI_Long)10L);
		    PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
			    4);
		      current_computation_flags = Current_computation_flags;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			      3);
			write_xml_object_items_collected = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
				2);
			  total_items_in_file = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
				  1);
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) &  
				    ~(SI_Long)2048L);
			    Current_computation_flags = 
				    FIX(IFIX(Current_computation_flags) &  
				    ~(SI_Long)4096L);
			    current_kb_save = Nil;
			    ab_loop_list_ = ISVREF(Current_saving_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
				    0);
			    next_loop_1:
			      if ( !TRUEP(ab_loop_list_))
				  goto end_loop_1;
			      Current_kb_save = M_CAR(ab_loop_list_);
			      ab_loop_list_ = M_CDR(ab_loop_list_);
			      write_initial_sections_of_kb_to_first_checkpoint();
			      temp = Current_kb_save;
			      SVREF(temp,FIX((SI_Long)49L)) = T;
			      goto next_loop_1;
			    end_loop_1:;
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  temp = Current_saving_context_qm;
		  SVREF(temp,FIX((SI_Long)9L)) = Nil;
		  temp_3 = Return_from_save_to_caller_for_continuation_qm;
		  if (temp_3)
		      result = VALUES_1(temp_3);
		  else
		      result = continue_current_kb_save_or_backup(Current_saving_context_qm);
	      }
	      else
		  result = VALUES_1(Nil);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Save_kb_state_for_system_procedure_save, Qsave_kb_state_for_system_procedure_save);

static Object Qab_continue;        /* continue */

static Object Qfinish;             /* finish */

/* COMPLETE-SAVE-AFTER-RUNNING-IF-NECESSARY */
Object complete_save_after_running_if_necessary()
{
    Object continuation_task_for_current_backup_new_value;

    x_note_fn_call(135,96);
    continuation_task_for_current_backup_new_value = 
	    execute_task_out_of_order_1(Continuation_task_for_current_backup);
    Continuation_task_for_current_backup = 
	    continuation_task_for_current_backup_new_value;
    if (EQ(Save_kb_state_for_system_procedure_save,Qab_continue))
	return continue_current_kb_save_or_backup(Current_saving_context_qm);
    else if (EQ(Save_kb_state_for_system_procedure_save,Qfinish))
	return finish_current_kb_save_or_backup(Current_saving_context_qm);
    else
	return VALUES_1(Qnil);
}

static Object string_constant_69;  /* "G2 could not open the file ~s:  ~a." */

static Object string_constant_70;  /* "Problem associating stream with file \"~a\"." */

/* OPEN-SAVE-KB-STREAM-OR-REJECT-SAVE-KB */
Object open_save_kb_stream_or_reject_save_kb(compiled_source_p)
    Object compiled_source_p;
{
    Object pathname_1;
    volatile Object namestring_1;
    volatile Object namestring_for_user;
    volatile Object probe_pathname_qm;
    Object save_kb_stream_qm;
    volatile Object truename_of_save_kb_stream_qm;
    Object message_string_if_error_qm, error_text, temp, svref_arg_1;
    Object new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(135,97);
    SAVE_STACK();
    pathname_1 = Qunbound_in_protected_let;
    namestring_1 = Qunbound_in_protected_let;
    namestring_for_user = Qunbound_in_protected_let;
    probe_pathname_qm = Qunbound_in_protected_let;
    save_kb_stream_qm = Qunbound_in_protected_let;
    truename_of_save_kb_stream_qm = Qunbound_in_protected_let;
    message_string_if_error_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	pathname_1 = compiled_source_p ? ISVREF(Current_kb_save,
		(SI_Long)16L) : ISVREF(Current_kb_save,(SI_Long)5L);
	namestring_1 = gensym_namestring(1,pathname_1);
	namestring_for_user = copy_text_string(namestring_1);
	probe_pathname_qm = gensym_probe_file_for_write(pathname_1);
	save_kb_stream_qm = probe_pathname_qm ? (T ? 
		find_and_open_temp_file(pathname_1) : Nil) : Qnil;
	truename_of_save_kb_stream_qm = save_kb_stream_qm ? 
		gensym_probe_file(save_kb_stream_qm) : Nil;
	if ( !TRUEP(save_kb_stream_qm)) {
	    error_text = most_recent_file_operation_status_as_text();
	    temp = tformat_text_string(3,string_constant_69,
		    namestring_for_user,error_text);
	    reclaim_text_string(error_text);
	    message_string_if_error_qm = temp;
	}
	else if ( !TRUEP(truename_of_save_kb_stream_qm))
	    message_string_if_error_qm = tformat_text_string(2,
		    string_constant_70,namestring_for_user);
	else
	    message_string_if_error_qm = Qnil;
	if (message_string_if_error_qm) {
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)27L)) = message_string_if_error_qm;
	    SAVE_VALUES(VALUES_1(Nil));
	}
	else {
	    if ( !TRUEP(compiled_source_p)) {
		if (ISVREF(Current_kb_save,(SI_Long)37L))
		    set_true_pathname_of_module(ISVREF(Current_kb_save,
			    (SI_Long)37L),pathname_1,Current_kb_pathname_qm);
		if ( !(ISVREF(Current_kb_save,(SI_Long)37L) &&  
			!EQ(ISVREF(Current_kb_save,(SI_Long)37L),
			ISVREF(Module_information,(SI_Long)23L)))) {
		    new_value = copy_gensym_pathname(pathname_1);
		    reclaim_pathname_or_string(Current_kb_pathname_qm);
		    if (text_string_p(new_value)) {
			temp = gensym_pathname(new_value);
			reclaim_text_string(new_value);
			Current_kb_pathname_qm = temp;
		    }
		    else
			Current_kb_pathname_qm = new_value;
		    add_recent_loaded_kb(Current_kb_pathname_qm);
		}
	    }
	    SAVE_VALUES(VALUES_1(save_kb_stream_qm));
	}
    }
    POP_UNWIND_PROTECT(0);
    if (truename_of_save_kb_stream_qm) {
	if ( !EQ(truename_of_save_kb_stream_qm,Qunbound_in_protected_let)) {
	    if (truename_of_save_kb_stream_qm)
		reclaim_gensym_pathname(truename_of_save_kb_stream_qm);
	}
    }
    if (probe_pathname_qm) {
	if ( !EQ(probe_pathname_qm,Qunbound_in_protected_let)) {
	    if (probe_pathname_qm)
		reclaim_gensym_pathname(probe_pathname_qm);
	}
    }
    if (namestring_for_user) {
	if ( !EQ(namestring_for_user,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_for_user);
    }
    if (namestring_1) {
	if ( !EQ(namestring_1,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_1);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qkb_save_with_runtime_data;  /* kb-save-with-runtime-data */

static Object Qruntime_data_only;  /* runtime-data-only */

static Object list_constant_9;     /* # */

static Object array_constant_12;   /* # */

static Object Qmodule_uses_crlf_p;  /* module-uses-crlf-p */

static Object Qwin32;              /* win32 */

static Object Qoutput;             /* output */

static Object Qread_only;          /* read-only */

static Object Qunopened;           /* unopened */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

static Object Qdialog_workspace_frame_style;  /* dialog-workspace-frame-style */

static Object Qdefault_workspace_frame_style;  /* default-workspace-frame-style */

/* MAKE-SAVING-CONTEXT */
Object make_saving_context(type_of_kb_save,
	    pathname_or_module_saving_schedule,saving_compiled_kbs_p,
	    log_message_for_commit_after_saving_qm)
    Object type_of_kb_save, pathname_or_module_saving_schedule;
    Object saving_compiled_kbs_p, log_message_for_commit_after_saving_qm;
{
    Object save_permanent_data_qm, save_runtime_data_qm, serial_number;
    Object saving_context_kb_file_progress_displays, display_progress_qm;
    Object existing_table_rows, existing_slots, module_qm, pathname_qm;
    Object read_only_qm, ab_loop_list_, pathname_1, clear_text_p, use_crlf_qm;
    Object pathname_copy, kb_transfer_user_namestring_as_text_string;
    Object kb_save_qm, file_progress, result_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, temp, temp_1, temp_2, table, workspace;
    Object workstation, window, list_of_saves;
    Object result;

    x_note_fn_call(135,98);
    save_permanent_data_qm = EQ(type_of_kb_save,Qkb_save) ? T : Nil;
    if (save_permanent_data_qm);
    else
	save_permanent_data_qm = EQ(type_of_kb_save,
		Qkb_save_with_runtime_data) ? T : Nil;
    save_runtime_data_qm = EQ(type_of_kb_save,Qruntime_data_only) ? T : Nil;
    if (save_runtime_data_qm);
    else
	save_runtime_data_qm = EQ(type_of_kb_save,
		Qkb_save_with_runtime_data) ? T : Nil;
    serial_number = Current_frame_serial_number;
    saving_context_kb_file_progress_displays = Nil;
    display_progress_qm = save_permanent_data_qm ? ( 
	    !TRUEP(Suppress_notification_for_kb_save_qm) ? T : Nil) : Qnil;
    existing_table_rows = Nil;
    existing_slots = Nil;
    module_qm = Nil;
    pathname_qm = Nil;
    read_only_qm = Nil;
    ab_loop_list_ = ATOM(pathname_or_module_saving_schedule) ? 
	    list_constant_9 : pathname_or_module_saving_schedule;
    pathname_1 = Nil;
    clear_text_p = Nil;
    use_crlf_qm = Nil;
    pathname_copy = Nil;
    kb_transfer_user_namestring_as_text_string = Nil;
    kb_save_qm = Nil;
    file_progress = Nil;
    result_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    module_qm = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    pathname_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    read_only_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = pathname_qm;
    if (temp);
    else
	temp = pathname_or_module_saving_schedule;
    pathname_1 = temp;
    clear_text_p = pathname_1 ? string_equalw(array_constant_12,
	    ISVREF(pathname_1,(SI_Long)5L)) : Qnil;
    use_crlf_qm = module_qm && 
	    file_is_in_source_code_control_p(pathname_qm) ? 
	    lookup_kb_specific_property_value_with_default(module_qm,
	    Qmodule_uses_crlf_p,Qdefault) : Qdefault;
    pathname_copy = copy_gensym_pathname(pathname_1);
    kb_transfer_user_namestring_as_text_string = 
	    gensym_namestring_as_text_string(1,pathname_copy);
    if ( !TRUEP(read_only_qm)) {
	temp_1 = pathname_copy;
	temp_2 = module_qm;
	temp = get_pane_description_for_saving_if_any(save_runtime_data_qm,
		module_qm);
	kb_save_qm = make_kb_save(temp_1,serial_number,temp_2,temp,
		clear_text_p,log_message_for_commit_after_saving_qm,
		EQ(use_crlf_qm,Qdefault) ? (EQ(G2_operating_system,Qwin32) 
		? T : Nil) : use_crlf_qm);
    }
    else
	kb_save_qm = Nil;
    file_progress = make_or_revise_file_progress(6,Nil,Nil,
	    kb_transfer_user_namestring_as_text_string,Qoutput,
	    read_only_qm ? Qread_only : Qunopened,module_qm);
    if (read_only_qm)
	give_read_only_warning_message(pathname_copy,module_qm);
    if (display_progress_qm && kb_save_qm)
	SVREF(kb_save_qm,FIX((SI_Long)13L)) = file_progress;
    saving_context_kb_file_progress_displays = gensym_cons_1(file_progress,
	    saving_context_kb_file_progress_displays);
    if (display_progress_qm) {
	temp_2 = file_progress;
	temp = select_subset_of_file_progress_attributes_to_show(3,T,
		module_qm,T);
	result = merge_frame_into_multiframe_table_rows(4,temp_2,temp,
		existing_table_rows,existing_slots);
	MVS_2(result,existing_table_rows,existing_slots);
    }
    if (kb_save_qm) {
	ab_loopvar__1 = journal_cons_1(kb_save_qm,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(log_message_for_commit_after_saving_qm) 
	    != (SI_Long)0L)
	reclaim_wide_string(log_message_for_commit_after_saving_qm);
    if (display_progress_qm) {
	reclaim_slot_value(existing_slots);
	table = finish_making_multiframe_table(2,existing_table_rows,Nil);
	workspace = make_workspace(4,Qtemporary_workspace,Nil,table,
		FIX((SI_Long)2L));
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
	window = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	window = ISVREF(workstation,(SI_Long)1L);
	temp = detail_pane(window);
	put_workspace_on_pane_function(workspace,temp,Qleft,Qtop,T,
		FIX((SI_Long)11L),Nil,
		lookup_frame_description_reference_of_frame_style(Qdialog_workspace_frame_style,
		Qdefault_workspace_frame_style),Nil,Nil,Nil,Nil,Nil);
	goto next_loop_1;
      end_loop_1:;
    }
    list_of_saves = result_1;
    goto end_1;
    list_of_saves = Qnil;
  end_1:;
    return make_saving_context_internal_1(list_of_saves,type_of_kb_save,
	    save_permanent_data_qm,save_runtime_data_qm,
	    saving_context_kb_file_progress_displays,saving_compiled_kbs_p);
}

static Object string_constant_71;  /* "Warning: Cannot save ~a~a as ~s because it is ~
				    *        read-only.  It is being skipped."
				    */

static Object string_constant_72;  /* "module " */

static Object string_constant_73;  /* "this KB " */

/* GIVE-READ-ONLY-WARNING-MESSAGE */
Object give_read_only_warning_message(gensym_pathname_1,module_qm)
    Object gensym_pathname_1, module_qm;
{
    volatile Object name_text_string;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(135,99);
    SAVE_STACK();
    name_text_string = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	name_text_string = gensym_namestring_as_text_string(1,
		gensym_pathname_1);
	temp = module_qm;
	if (temp);
	else
	    temp = string_constant_1;
	SAVE_VALUES(notify_user(4,string_constant_71,module_qm ? 
		string_constant_72 : string_constant_73,temp,
		name_text_string));
    }
    POP_UNWIND_PROTECT(0);
    if (name_text_string) {
	if ( !EQ(name_text_string,Qunbound_in_protected_let))
	    reclaim_text_string(name_text_string);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* GET-PANE-DESCRIPTION-FOR-SAVING-IF-ANY */
Object get_pane_description_for_saving_if_any(include_transient_kb_workspaces_qm,
	    module_qm)
    Object include_transient_kb_workspaces_qm, module_qm;
{
    Object g2_window_qm, workstation_qm, window_for_workstation_qm;
    Object detail_pane_qm, workspace_qm, info, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, x2, gensymed_symbol;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(135,100);
    g2_window_qm = Servicing_workstation_qm ? ISVREF(Current_workstation,
	    (SI_Long)25L) : G2_window_for_save_via_system_procedure_qm;
    workstation_qm = g2_window_qm ? 
	    workstation_for_g2_window_qm_function(g2_window_qm) : Nil;
    window_for_workstation_qm = workstation_qm ? ISVREF(workstation_qm,
	    (SI_Long)1L) : Nil;
    detail_pane_qm = window_for_workstation_qm ? 
	    detail_pane(window_for_workstation_qm) : Nil;
    if (detail_pane_qm)
	return modify_pane_description(make_pane_description(detail_pane_qm,
		include_transient_kb_workspaces_qm,Nil,module_qm));
    else if ( !TRUEP(g2_window_qm)) {
	workspace_qm = Nil;
	info = Nil;
	ab_loop_list_ = Saved_detail_pane_description;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	workspace_qm = CAR(ab_loop_desetq_);
	info = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(workspace_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(workspace_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(workspace_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(workspace_qm,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_1 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_2 = (SI_Long)1L;
		gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		temp = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ((temp ? include_transient_kb_workspaces_qm || (SI_Long)0L != 
		(IFIX(ISVREF(workspace_qm,(SI_Long)4L)) & (SI_Long)1L) : 
		TRUEP(Nil)) ?  !TRUEP(module_qm) || 
		EQ(get_module_block_is_in(workspace_qm),module_qm) : 
		TRUEP(Nil)) {
	    ab_loopvar__2 = 
		    slot_value_cons_1(slot_value_cons_1(workspace_qm,
		    copy_for_slot_value(info)),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	temp_1 = ab_loopvar_;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
	return modify_pane_description(temp_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfuncall_to_write_to_kb_save_stream;  /* funcall-to-write-to-kb-save-stream */

static Object list_constant_10;    /* # */

static Object Qerror_writing_file;  /* error-writing-file */

/* FUNCALL-TO-WRITE-TO-KB-SAVE-STREAM */
Object funcall_to_write_to_kb_save_stream varargs_1(int, n)
{
    Object function, location_symbol;
    Object error_token_qm, tag_temp;
    volatile Object stream_error_string_qm;
    volatile Object protected_form_completed_p;
    Object temp, svref_arg_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(135,101);
    INIT_ARGS_nonrelocating();
    function = REQUIRED_ARG_nonrelocating();
    location_symbol = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    error_token_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    tag_temp = UNIQUE_TAG(Qfuncall_to_write_to_kb_save_stream);
    if (PUSH_CATCH(tag_temp,1)) {
	stream_error_string_qm = Nil;
	protected_form_completed_p = Nil;
	Internal_status_of_most_recent_file_operation = 
		File_operation_succeeded_code;
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = FUNCALL_0(function);
	    SAVE_VALUES(VALUES_1(temp));
	    if (ISVREF(Current_kb_save,(SI_Long)27L)) {
		stream_error_string_qm = ISVREF(Current_kb_save,(SI_Long)27L);
		svref_arg_1 = Current_kb_save;
		SVREF(svref_arg_1,FIX((SI_Long)27L)) = Nil;
	    }
	    else if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code))
		stream_error_string_qm = 
			most_recent_file_operation_status_as_text();
	    protected_form_completed_p = T;
	}
	POP_UNWIND_PROTECT(0);
	if ( !TRUEP(protected_form_completed_p) || stream_error_string_qm) {
	    defer_terminate_kb_save_or_backup(Current_saving_context,
		    getf(list_constant_10,location_symbol,
		    Qerror_writing_file),stream_error_string_qm);
	    result = VALUES_1(error_token_qm);
	    THROW(tag_temp,result);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object Qopen_kb_save_or_backup_stream;  /* open-kb-save-or-backup-stream */

static Object Qaborted;            /* aborted */

/* OPEN-KB-SAVE-OR-BACKUP-STREAM */
Object open_kb_save_or_backup_stream()
{
    Object tag_temp;
    volatile Object stream_error_string_qm;
    volatile Object protected_form_completed_p;
    Object save_kb_stream_qm, temp, svref_arg_1, save_compiled_kb_stream_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(135,102);
    SAVE_STACK();
    tag_temp = UNIQUE_TAG(Qopen_kb_save_or_backup_stream);
    if (PUSH_CATCH(tag_temp,1)) {
	stream_error_string_qm = Nil;
	protected_form_completed_p = Nil;
	Internal_status_of_most_recent_file_operation = 
		File_operation_succeeded_code;
	if (PUSH_UNWIND_PROTECT(0)) {
	    save_kb_stream_qm = open_save_kb_stream_or_reject_save_kb(Nil);
	    update_file_progress_display_status(save_kb_stream_qm ? Qopen :
		     Qaborted);
	    if ( !TRUEP(save_kb_stream_qm))
		temp = Nil;
	    else {
		svref_arg_1 = Current_kb_save;
		SVREF(svref_arg_1,FIX((SI_Long)4L)) = save_kb_stream_qm;
		svref_arg_1 = Current_kb_save;
		SVREF(svref_arg_1,FIX((SI_Long)14L)) = T;
		if ( !TRUEP(Enable_saving_compiled_kbs_p))
		    temp = T;
		else {
		    save_compiled_kb_stream_qm = 
			    open_save_kb_stream_or_reject_save_kb(T);
		    if ( !TRUEP(save_compiled_kb_stream_qm))
			temp = Nil;
		    else {
			svref_arg_1 = Current_kb_save;
			SVREF(svref_arg_1,FIX((SI_Long)15L)) = 
				save_compiled_kb_stream_qm;
			svref_arg_1 = Current_kb_save;
			SVREF(svref_arg_1,FIX((SI_Long)17L)) = T;
			temp = T;
		    }
		}
	    }
	    SAVE_VALUES(VALUES_1(temp));
	    if (ISVREF(Current_kb_save,(SI_Long)27L)) {
		stream_error_string_qm = ISVREF(Current_kb_save,(SI_Long)27L);
		svref_arg_1 = Current_kb_save;
		SVREF(svref_arg_1,FIX((SI_Long)27L)) = Nil;
	    }
	    else if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code))
		stream_error_string_qm = 
			most_recent_file_operation_status_as_text();
	    protected_form_completed_p = T;
	}
	POP_UNWIND_PROTECT(0);
	if ( !TRUEP(protected_form_completed_p) || stream_error_string_qm) {
	    defer_terminate_kb_save_or_backup(Current_saving_context,
		    getf(list_constant_10,Qopen_kb_save_or_backup_stream,
		    Qerror_writing_file),stream_error_string_qm);
	    result = VALUES_1(Nil);
	    THROW(tag_temp,result);
	}
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(1);
    RESTORE_STACK();
    return result;
}

static Object string_constant_74;  /* "#include \"bytecode.h\"" */

static Object string_constant_75;  /* "static Object *byte_code_constants;" */

static Object string_constant_76;  /* "static Object **byte_code_variables;" */

static Object string_constant_77;  /* "static fn_type *byte_code_functions;" */

static Object string_constant_78;  /* "static fn_type *byte_code_run_time_functions;" */

/* WRITE-INITIAL-SECTIONS-OF-COMPILED-KB-TO-FIRST-CHECKPOINT */
Object write_initial_sections_of_compiled_kb_to_first_checkpoint()
{
    x_note_fn_call(135,103);
    if (T) {
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_74);
	write_char_for_compiled_kb(CHR('\n'));
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_75);
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_76);
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_77);
	write_char_for_compiled_kb(CHR('\n'));
	write_gensym_string_for_compiled_kb(string_constant_78);
	write_char_for_compiled_kb(CHR('\n'));
	write_char_for_compiled_kb(CHR('\n'));
    }
    return VALUES_1(Nil);
}

static Object Qnormal;             /* normal */

static Object Qclear_text;         /* clear-text */

/* WRITE-INITIAL-SECTIONS-OF-KB-TO-FIRST-CHECKPOINT */
Object write_initial_sections_of_kb_to_first_checkpoint()
{
    Object noting_changes_to_kb_p, kb_name, instance_qm, temp, svref_arg_1;
    Object fsn, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(135,104);
    noting_changes_to_kb_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Noting_changes_to_kb_p,Qnoting_changes_to_kb_p,noting_changes_to_kb_p,
	    0);
      kb_name = make_kb_name(ISVREF(Current_kb_save,(SI_Long)5L));
      instance_qm = ISVREF(Current_kb_save,(SI_Long)37L) ? 
	      get_system_table_of_class_for_module_or_nil(ISVREF(Current_kb_save,
	      (SI_Long)37L),Qsaving_parameters) : Saving_parameters;
      if (instance_qm)
	  increment_version_for_change_logging_if_appropriate(instance_qm);
      make_or_clear_complete_kb_name(3,kb_name,Nil,ISVREF(Current_kb_save,
	      (SI_Long)37L));
      reclaim_text_string(kb_name);
      temp = ISVREF(Current_kb_save,(SI_Long)38L);
      if (EQ(temp,Qnormal)) {
	  write_initial_plist(Complete_kb_name_qm);
	  svref_arg_1 = Current_kb_save;
	  fsn = Current_frame_serial_number;
	  svref_new_value = chestnut_modf_function(FIXNUMP(fsn) ? fsn : 
		  FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)),Base_modulus);
	  SVREF(svref_arg_1,FIX((SI_Long)9L)) = svref_new_value;
	  if (ISVREF(Current_kb_save,(SI_Long)37L))
	      write_ghost_definitions(ISVREF(Current_kb_save,(SI_Long)37L));
      }
      else if (EQ(temp,Qclear_text));
      if (Enable_saving_compiled_kbs_p)
	  result = write_initial_sections_of_compiled_kb_to_first_checkpoint();
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qcontinue_current_kb_save_or_backup;  /* continue-current-kb-save-or-backup */

static Object Qterminate_kb_save_or_backup;  /* terminate-kb-save-or-backup */

/* CONTINUE-CURRENT-KB-SAVE-OR-BACKUP */
Object continue_current_kb_save_or_backup(saving_context)
    Object saving_context;
{
    Object current_saving_context, enable_saving_compiled_kbs_p;
    Object current_computation_flags, write_xml_object_items_collected;
    Object total_items_in_file, current_kb_save, ab_loop_list_, temp, old;
    Object new_1, def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char temp_1, g2_p;
    double aref_new_value;
    Declare_special(6);
    Object result;

    x_note_fn_call(135,105);
    current_saving_context = saving_context;
    PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
	    5);
      enable_saving_compiled_kbs_p = ISVREF(Current_saving_context,
	      (SI_Long)10L);
      PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
	      4);
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		3);
	  write_xml_object_items_collected = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
		  2);
	    total_items_in_file = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
		    1);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)2048L);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)4096L);
	      current_kb_save = Nil;
	      ab_loop_list_ = ISVREF(Current_saving_context,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
		      0);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		Current_kb_save = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (ISVREF(Current_saving_context,(SI_Long)6L) || 
			ISVREF(Current_kb_save,(SI_Long)39L))
		    continue_current_kb_save(Nil);
		if ( !TRUEP(Current_saving_context_qm)) {
		    result = VALUES_1(Nil);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_continue_current_kb_save_or_backup;
		}
		if (System_is_running && time_slice_expired_p()) {
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_timeout;
		}
		goto next_loop;
	      end_loop:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
  end_timeout:
    if ( !TRUEP(System_is_running))
	temp = terminate_kb_save_or_backup(saving_context,Nil,Nil);
    else {
	temp = Return_from_save_to_caller_for_continuation_qm;
	if (temp);
	else {
	    temp = ISVREF(saving_context,(SI_Long)9L);
	    if (temp);
	    else {
		current_saving_context = saving_context;
		PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
			5);
		  enable_saving_compiled_kbs_p = 
			  ISVREF(Current_saving_context,(SI_Long)10L);
		  PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
			  4);
		    current_computation_flags = Current_computation_flags;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			    3);
		      write_xml_object_items_collected = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
			      2);
			total_items_in_file = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
				1);
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) &  
				  ~(SI_Long)2048L);
			  Current_computation_flags = 
				  FIX(IFIX(Current_computation_flags) &  
				  ~(SI_Long)4096L);
			  current_kb_save = Nil;
			  ab_loop_list_ = ISVREF(Current_saving_context,
				  (SI_Long)1L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
				  0);
			  next_loop_1:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_1;
			    Current_kb_save = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    if (ISVREF(Current_saving_context,(SI_Long)6L) 
				    || ISVREF(Current_kb_save,(SI_Long)39L)) {
				temp_1 = TRUEP(T);
				POP_SPECIAL();
				POP_SPECIAL();
				POP_SPECIAL();
				POP_SPECIAL();
				POP_SPECIAL();
				POP_SPECIAL();
				goto end_over;
			    }
			    goto next_loop_1;
			  end_loop_1:;
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		temp_1 = TRUEP(Nil);
	      end_over:
		if (temp_1) {
		    old = Nil;
		    new_1 = Nil;
		  next_loop_2:
		    old = Continuation_task_for_current_backup;
		    def_structure_schedule_task_variable = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    if (def_structure_schedule_task_variable) {
			temp_2 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = 
				ISVREF(def_structure_schedule_task_variable,
				(SI_Long)0L);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
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
		    temp_2 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = -1.0;
		    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
		    temp_2 = ISVREF(Saving_parameters,(SI_Long)22L);
		    SVREF(task,FIX((SI_Long)4L)) = temp_2;
		    SVREF(task,FIX((SI_Long)5L)) = Nil;
		    SVREF(task,FIX((SI_Long)9L)) = Nil;
		    SVREF(task,FIX((SI_Long)10L)) = Nil;
		    g2_p =  !TRUEP(Nil);
		    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		    temp_2 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
			    Current_g2_time : Current_real_time,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
		    SVREF(task,FIX((SI_Long)7L)) = 
			    Qcontinue_current_kb_save_or_backup;
		    temp_2 = 
			    SYMBOL_FUNCTION(Qcontinue_current_kb_save_or_backup);
		    SVREF(task,FIX((SI_Long)8L)) = temp_2;
		    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		    SVREF(task,FIX((SI_Long)13L)) = saving_context;
		    new_1 = task;
		    if (CAS_SYMBOL(Qcontinuation_task_for_current_backup,
			    old,new_1)) {
			task = new_1;
			ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
			if (ctask);
			else
			    ctask = System_is_running;
			p = ISVREF(task,(SI_Long)4L);
			v = ctask ? Current_task_queue_vector : 
				Deferred_task_queue_vector;
			q = ISVREF(v,IFIX(p));
			SVREF(task,FIX((SI_Long)11L)) = q;
			temp_2 = constant_queue_push_right(q,task);
			SVREF(task,FIX((SI_Long)6L)) = temp_2;
			if (ctask && FIXNUM_LT(p,Priority_of_next_task))
			    Priority_of_next_task = p;
			temp = task;
			goto end_1;
		    }
		    else {
			inline_note_reclaim_cons(new_1,Nil);
			structure_being_reclaimed = new_1;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(new_1,
				  (SI_Long)9L));
			  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_2 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
			temp_2 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = new_1;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp = Qnil;
		  end_1:;
		}
		else {
		    old = Nil;
		    new_1 = Nil;
		  next_loop_3:
		    old = Continuation_task_for_current_backup;
		    def_structure_schedule_task_variable = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    if (def_structure_schedule_task_variable) {
			temp_2 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = 
				ISVREF(def_structure_schedule_task_variable,
				(SI_Long)0L);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
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
		    temp_2 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = -1.0;
		    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
		    temp_2 = ISVREF(Saving_parameters,(SI_Long)22L);
		    SVREF(task,FIX((SI_Long)4L)) = temp_2;
		    SVREF(task,FIX((SI_Long)5L)) = Nil;
		    SVREF(task,FIX((SI_Long)9L)) = Nil;
		    SVREF(task,FIX((SI_Long)10L)) = Nil;
		    g2_p =  !TRUEP(Nil);
		    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
		    temp_2 = ISVREF(task,(SI_Long)1L);
		    aref_new_value = DFLOAT_ISAREF_1(g2_p ? 
			    Current_g2_time : Current_real_time,(SI_Long)0L);
		    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
		    SVREF(task,FIX((SI_Long)7L)) = 
			    Qterminate_kb_save_or_backup;
		    temp_2 = SYMBOL_FUNCTION(Qterminate_kb_save_or_backup);
		    SVREF(task,FIX((SI_Long)8L)) = temp_2;
		    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
		    SVREF(task,FIX((SI_Long)13L)) = saving_context;
		    SVREF(task,FIX((SI_Long)14L)) = Nil;
		    SVREF(task,FIX((SI_Long)15L)) = Nil;
		    new_1 = task;
		    if (CAS_SYMBOL(Qcontinuation_task_for_current_backup,
			    old,new_1)) {
			task = new_1;
			ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
			if (ctask);
			else
			    ctask = System_is_running;
			p = ISVREF(task,(SI_Long)4L);
			v = ctask ? Current_task_queue_vector : 
				Deferred_task_queue_vector;
			q = ISVREF(v,IFIX(p));
			SVREF(task,FIX((SI_Long)11L)) = q;
			temp_2 = constant_queue_push_right(q,task);
			SVREF(task,FIX((SI_Long)6L)) = temp_2;
			if (ctask && FIXNUM_LT(p,Priority_of_next_task))
			    Priority_of_next_task = p;
			temp = task;
			goto end_2;
		    }
		    else {
			inline_note_reclaim_cons(new_1,Nil);
			structure_being_reclaimed = new_1;
			PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
				0);
			  reclaim_schedule_task_args(ISVREF(new_1,
				  (SI_Long)9L));
			  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
			POP_SPECIAL();
			temp_2 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
			temp_2 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = new_1;
		    }
		    goto next_loop_3;
		  end_loop_3:
		    temp = Qnil;
		  end_2:;
		}
	    }
	}
    }
    result = VALUES_1(temp);
  end_continue_current_kb_save_or_backup:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Save_only_if_interrupting_qm, Qsave_only_if_interrupting_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Use_minimal_time_slice_for_continue_current_kb_save_p, Quse_minimal_time_slice_for_continue_current_kb_save_p);

DEFINE_VARIABLE_WITH_SYMBOL(Dont_cerror_for_slot_changes_while_on_window_qm, Qdont_cerror_for_slot_changes_while_on_window_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Continue_current_kb_save_failure, Qcontinue_current_kb_save_failure);

static Object Qcontinue_current_kb_save;  /* continue-current-kb-save */

static Object Qwrite_clear_text_kb;  /* write-clear-text-kb */

static Object Qwrite_kb_per_traversal_state_a_little;  /* write-kb-per-traversal-state-a-little */

static Object Qwrite_deletions_for_saving_a_little;  /* write-deletions-for-saving-a-little */

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* CONTINUE-CURRENT-KB-SAVE */
Object continue_current_kb_save(node_to_write_if_interrupting_qm)
    Object node_to_write_if_interrupting_qm;
{
    Object index_of_top_of_backtrace_stack, temp, temp_1, write_ok_p, temp_2;
    Object display_to_restore_qm, node_to_insert_qm;
    Object write_xml_object_items_collected, write_result;
    Object journal_push_modify_macro_arg, car_1, cdr_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(135,106);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    1);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  temp_1 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,temp_1) = Qcontinue_current_kb_save;
      }
      if (System_is_running && Save_only_if_interrupting_qm &&  
	      !TRUEP(node_to_write_if_interrupting_qm)) {
	  result = VALUES_1(Nil);
	  POP_SPECIAL();
	  goto end_continue_current_kb_save;
      }
      if ( !TRUEP(ISVREF(Current_kb_save,(SI_Long)4L))) {
	  if ( !TRUEP(open_kb_save_or_backup_stream())) {
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      goto end_continue_current_kb_save;
	  }
      }
      write_ok_p = T;
      if (node_to_write_if_interrupting_qm) {
	  temp_2 = ISVREF(Current_kb_save,(SI_Long)13L);
	  temp = Current_kb_save;
	  SVREF(temp,FIX((SI_Long)13L)) = Nil;
	  display_to_restore_qm = temp_2;
      }
      else
	  display_to_restore_qm = Nil;
      node_to_insert_qm = node_to_write_if_interrupting_qm;
      write_xml_object_items_collected = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
	      0);
	temp_2 = ISVREF(Current_kb_save,(SI_Long)38L);
	if (EQ(temp_2,Qclear_text)) {
	    temp_2 = funcall_to_write_to_kb_save_stream(3,
		    SYMBOL_FUNCTION(Qwrite_clear_text_kb),
		    Qcontinue_current_kb_save,
		    Continue_current_kb_save_failure);
	    if (EQ(temp_2,Continue_current_kb_save_failure))
		write_ok_p = Nil;
	}
	else if (EQ(temp_2,Qnormal)) {
	    write_result = Nil;
	  next_loop:
	    if (ISVREF(Current_kb_save,(SI_Long)31L))
		goto end_loop;
	    write_result = funcall_to_write_to_kb_save_stream(3,
		    SYMBOL_FUNCTION(Qwrite_kb_per_traversal_state_a_little),
		    Qcontinue_current_kb_save,
		    Continue_current_kb_save_failure);
	    if (EQ(write_result,Continue_current_kb_save_failure)) {
		write_ok_p = Nil;
		goto end_loop;
	    }
	    goto next_loop;
	  end_loop:;
	    if (write_ok_p) {
		write_result = Nil;
	      next_loop_1:
		if ( !(ISVREF(Current_saving_context,(SI_Long)6L) || 
			ISVREF(Current_kb_save,(SI_Long)39L)))
		    goto end_loop_1;
		if (ISVREF(Current_saving_context,(SI_Long)6L))
		    write_result = funcall_to_write_to_kb_save_stream(3,
			    SYMBOL_FUNCTION(Qwrite_deletions_for_saving_a_little),
			    Qcontinue_current_kb_save,
			    Continue_current_kb_save_failure);
		else {
		    if (node_to_insert_qm) {
			temp = Current_kb_save;
			temp_2 = 
				copy_frame_serial_number(Current_frame_serial_number);
			journal_push_modify_macro_arg = 
				journal_cons_1(temp_2,
				journal_cons_1(node_to_insert_qm,Nil));
			car_1 = journal_push_modify_macro_arg;
			cdr_1 = ISVREF(temp,(SI_Long)39L);
			temp_1 = journal_cons_1(car_1,cdr_1);
			SVREF(temp,FIX((SI_Long)39L)) = temp_1;
			node_to_insert_qm = Nil;
		    }
		    write_result = funcall_to_write_to_kb_save_stream(3,
			    SYMBOL_FUNCTION(Qwrite_kb_per_traversal_state_a_little),
			    Qcontinue_current_kb_save,
			    Continue_current_kb_save_failure);
		}
		if (EQ(write_result,Continue_current_kb_save_failure)) {
		    write_ok_p = Nil;
		    goto end_loop_1;
		}
		if (System_is_running &&  !TRUEP(node_to_insert_qm) && ( 
			!TRUEP(node_to_write_if_interrupting_qm) || 
			(SIMPLE_VECTOR_P(node_to_write_if_interrupting_qm) 
			&& EQ(ISVREF(node_to_write_if_interrupting_qm,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct) 
			? (SI_Long)0L != 
			(IFIX(ISVREF(node_to_write_if_interrupting_qm,
			(SI_Long)7L)) & (SI_Long)4L) : 
			TRUEP(block_written_in_current_save_p(node_to_write_if_interrupting_qm)))) 
			&& 
			(Use_minimal_time_slice_for_continue_current_kb_save_p 
			|| time_slice_expired_p()))
		    goto end_loop_1;
		goto next_loop_1;
	      end_loop_1:;
	    }
	}
	if (write_ok_p) {
	    if ( !(ISVREF(Current_saving_context,(SI_Long)6L) || 
		    ISVREF(Current_kb_save,(SI_Long)39L)))
		finish_current_kb_save();
	    if (display_to_restore_qm) {
		temp = Current_kb_save;
		temp_2 = SVREF(temp,FIX((SI_Long)13L)) = display_to_restore_qm;
	    }
	    else
		temp_2 = Nil;
	}
	else
	    temp_2 = Nil;
      POP_SPECIAL();
    POP_SPECIAL();
    result = VALUES_1(temp_2);
  end_continue_current_kb_save:
    return result;
}

/* WRITE-DELETIONS-FOR-SAVING-A-LITTLE */
Object write_deletions_for_saving_a_little()
{
    Object temp, svref_arg_1, svref_new_value;
    SI_Long ab_loop_repeat_;

    x_note_fn_call(135,107);
    ab_loop_repeat_ = (SI_Long)10L;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    if ( !TRUEP(ISVREF(Current_saving_context,(SI_Long)6L)))
	goto end_loop;
    write_char_for_kb(CHR('D'));
    temp = ISVREF(Current_saving_context,(SI_Long)6L);
    write_frame_serial_number_for_kb(FIRST(temp));
    svref_arg_1 = Current_saving_context;
    if (EQ(ISVREF(Current_saving_context,(SI_Long)6L),
	    ISVREF(Current_saving_context,(SI_Long)7L)))
	svref_new_value = Nil;
    else {
	temp = ISVREF(Current_saving_context,(SI_Long)6L);
	svref_new_value = CDR(temp);
    }
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = svref_new_value;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qjournal;            /* journal */

/* WRITE-KB-PER-TRAVERSAL-STATE-A-LITTLE */
Object write_kb_per_traversal_state_a_little()
{
    Object temp, journal_pop_store, temp_1, cons_1, next_cons, temp_2;
    Object svref_arg_2, new_nodes, journal_push_modify_macro_arg, car_1, cdr_1;

    x_note_fn_call(135,108);
    temp = ISVREF(Current_kb_save,(SI_Long)39L);
    temp = CAAR(temp);
    journal_pop_store = Nil;
    temp_1 = ISVREF(Current_kb_save,(SI_Long)39L);
    cons_1 = CDAR(temp_1);
    if (cons_1) {
	journal_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qjournal);
	if (ISVREF(Available_journal_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_journal_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = cons_1;
	    temp_2 = Available_journal_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	else {
	    temp_2 = Available_journal_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	    temp_2 = Available_journal_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    M_CDAR(temp_1) = next_cons;
    new_nodes = write_kb_traversal_state_node(temp,journal_pop_store);
    temp = ISVREF(Current_kb_save,(SI_Long)39L);
    if ( !TRUEP(CDAR(temp))) {
	temp = ISVREF(Current_kb_save,(SI_Long)39L);
	reclaim_frame_serial_number(CAAR(temp));
	journal_pop_store = Nil;
	temp_1 = Current_kb_save;
	cons_1 = ISVREF(temp_1,(SI_Long)39L);
	if (cons_1) {
	    journal_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qjournal);
	    if (ISVREF(Available_journal_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_journal_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = cons_1;
		temp_2 = Available_journal_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
	    }
	    else {
		temp_2 = Available_journal_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
		temp_2 = Available_journal_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	SVREF(temp_1,FIX((SI_Long)39L)) = next_cons;
	reclaim_journal_cons_1(journal_pop_store);
    }
    if (new_nodes) {
	temp_1 = Current_kb_save;
	journal_push_modify_macro_arg = 
		journal_cons_1(copy_frame_serial_number(Current_frame_serial_number),
		new_nodes);
	car_1 = journal_push_modify_macro_arg;
	cdr_1 = ISVREF(temp_1,(SI_Long)39L);
	temp_2 = journal_cons_1(car_1,cdr_1);
	SVREF(temp_1,FIX((SI_Long)39L)) = temp_2;
    }
    return VALUES_1(Nil);
}

static Object Ktop_level_workspaces;  /* :top-level-workspaces */

static Object Qclass_definition;   /* class-definition */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qwrite_kb_traversal_state_node;  /* write-kb-traversal-state-node */

/* WRITE-KB-TRAVERSAL-STATE-NODE */
Object write_kb_traversal_state_node(serial_number,node)
    Object serial_number, node;
{
    Object svref_arg_1, temp, gensymed_symbol, xa, ya, x2;
    Object sub_class_bit_vector, class_test, dont_save_for_this_backup_qm;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char saving_backup_qm, temp_1;

    x_note_fn_call(135,109);
    saving_backup_qm = EQ(ISVREF(Current_saving_context,(SI_Long)2L),Qbackup);
    if (SYMBOLP(node)) {
	if (EQ(node,Ktop_level_workspaces)) {
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)31L)) = T;
	}
	temp = traverse_kb_for_saving(node);
    }
    else if (SIMPLE_VECTOR_P(node) && EQ(ISVREF(node,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	gensymed_symbol = ISVREF(node,(SI_Long)10L);
	temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else if (FIXNUMP(serial_number))
	    temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if (temp_1);
	else
	    temp_1 = (SI_Long)0L != (IFIX(ISVREF(node,(SI_Long)7L)) & 
		    (SI_Long)4L);
	if ( !temp_1) {
	    svref_new_value = IFIX(ISVREF(node,(SI_Long)7L)) | (SI_Long)4L;
	    ISVREF(node,(SI_Long)7L) = FIX(svref_new_value);
	    if ( !(saving_backup_qm &&  !((SI_Long)0L != (IFIX(ISVREF(node,
		    (SI_Long)7L)) & (SI_Long)2L)))) {
		write_connection_for_kb(node);
		if ( !saving_backup_qm) {
		    svref_new_value = IFIX(ISVREF(node,(SI_Long)7L)) &  
			    ~(SI_Long)2L;
		    ISVREF(node,(SI_Long)7L) = FIX(svref_new_value);
		}
	    }
	    temp = traverse_kb_for_saving(node);
	}
	else
	    temp = Nil;
    }
    else {
	if (SIMPLE_VECTOR_P(node) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(node)) 
		> (SI_Long)2L &&  !EQ(ISVREF(node,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(node,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(node,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(node) ? EQ(ISVREF(node,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(serial_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(serial_number,gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(serial_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if (temp_1);
	    else
		temp_1 = TRUEP(block_written_in_current_save_p(node));
	    if ( !temp_1) {
		gensymed_symbol = ISVREF(node,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Class_definition_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_1 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    class_test = Qclass_definition;
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Kb_workspace_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp_1 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			class_test = Qkb_workspace;
		    else
			class_test = Qnil;
		}
		dont_save_for_this_backup_qm = saving_backup_qm ? ( 
			!((SI_Long)0L != (IFIX(ISVREF(node,(SI_Long)5L)) & 
			(SI_Long)4L)) ? T : Nil) : Qnil;
		if (EQ(class_test,Qclass_definition)) {
		    if (ISVREF(Current_kb_save,(SI_Long)31L)) {
			set_block_written_in_current_save(node,T);
			if ( !TRUEP(dont_save_for_this_backup_qm)) {
			    if (ISVREF(Current_saving_context,(SI_Long)3L)) {
				if ( 
					!TRUEP(relation_instances_empty_p(ISVREF(node,
					(SI_Long)12L))))
				    write_runtime_data_frame_modification(node);
			    }
			    else {
				sub_class_bit_vector = ISVREF(ISVREF(node,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Definition_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_1 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp_1 = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1)
				    write_entangled_slots_of_definition_as_frame_modification(node);
			    }
			    if ( !saving_backup_qm)
				note_saving_frame(node);
			}
			temp = traverse_kb_for_saving(node);
		    }
		    else {
			if ( !TRUEP(dont_save_for_this_backup_qm)) {
			    if ( 
				    !TRUEP(block_referenced_in_current_save_p(node))) 
					{
				set_block_referenced_in_current_save(node,T);
				increment_frame_reference_balance(node,
					Qwrite_kb_traversal_state_node);
			    }
			    write_frame_for_kb(2,node,T);
			}
			temp = Nil;
		    }
		}
		else {
		    set_block_written_in_current_save(node,T);
		    if (EQ(class_test,Qkb_workspace))
			normalize_kb_workspace(node,T);
		    if ( !TRUEP(dont_save_for_this_backup_qm)) {
			write_frame_for_kb(2,node,T);
			if ( !saving_backup_qm)
			    note_saving_frame(node);
		    }
		    temp = traverse_kb_for_saving(node);
		}
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

static Object string_constant_79;  /* "DLLEXPORT void do_initialize_compiled_kb_" */

static Object string_constant_80;  /* "(args)" */

static Object string_constant_81;  /* "  void **args;" */

static Object string_constant_82;  /* "  byte_code_constants = (Object *)(args[0]);" */

static Object string_constant_83;  /* "  byte_code_variables = (Object **)(args[1]);" */

static Object string_constant_84;  /* "  byte_code_functions = (fn_type *)(args[2]);" */

static Object string_constant_85;  /* "  byte_code_run_time_functions = (fn_type *)(args[3]);" */

static Object string_constant_86;  /* "  add_compiled_function(fn" */

static Object string_constant_87;  /* ");" */

/* WRITE-COMPILED-KB-FILE-SPECIFIC-INITIALIZATION-FUNCTION */
Object write_compiled_kb_file_specific_initialization_function()
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(135,110);
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_79);
    write_fixnum_for_compiled_kb(ISVREF(Current_kb_save,(SI_Long)46L));
    write_gensym_string_for_compiled_kb(string_constant_80);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_81);
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('{'));
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_82);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_83);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_84);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_85);
    write_char_for_compiled_kb(CHR('\n'));
    i = IFIX(FIXNUM_ADD1(ISVREF(Current_kb_save,(SI_Long)45L)));
    ab_loop_bind_ = IFIX(ISVREF(Current_kb_save,(SI_Long)44L));
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    write_gensym_string_for_compiled_kb(string_constant_86);
    write_fixnum_for_compiled_kb(FIX(i));
    write_gensym_string_for_compiled_kb(string_constant_87);
    write_char_for_compiled_kb(CHR('\n'));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    write_char_for_compiled_kb(CHR('}'));
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('\n'));
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Finish_current_kb_save_failure, Qfinish_current_kb_save_failure);

static Object Qclosing_compiled;   /* closing-compiled */

static Object Qclose_current_compiled_kb_save_stream;  /* close-current-compiled-kb-save-stream */

static Object Qfinish_current_kb_save;  /* finish-current-kb-save */

static Object Qclosed_compiled;    /* closed-compiled */

/* CLOSE-AND-RENAME-CURRENT-COMPILED-KB-STREAM */
Object close_and_rename_current_compiled_kb_stream()
{
    Object stream, temp_file_truename, termination_description, temp;
    Object svref_arg_1, new_pathname_qm, old_truename_qm, new_truename_qm;
    Object result;

    x_note_fn_call(135,111);
    stream = ISVREF(Current_kb_save,(SI_Long)15L);
    temp_file_truename = T ? gensym_truename(stream) : Nil;
    termination_description = Nil;
    update_file_progress_display_status(Qclosing_compiled);
    temp = funcall_to_write_to_kb_save_stream(3,
	    SYMBOL_FUNCTION(Qclose_current_compiled_kb_save_stream),
	    Qfinish_current_kb_save,Finish_current_kb_save_failure);
    temp = EQ(temp,Finish_current_kb_save_failure) ? T : Nil;
    svref_arg_1 = Current_kb_save;
    SVREF(svref_arg_1,FIX((SI_Long)15L)) = Nil;
    if ( !TRUEP(temp)) {
	if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		File_operation_succeeded_code)) {
	    gensym_delete_file(temp_file_truename);
	    termination_description = 
		    most_recent_file_operation_status_as_text();
	}
	else {
	    checkpoint_file_if_necessary(ISVREF(Current_kb_save,(SI_Long)16L));
	    result = gensym_rename_file(temp_file_truename,
		    ISVREF(Current_kb_save,(SI_Long)16L));
	    MVS_3(result,new_pathname_qm,old_truename_qm,new_truename_qm);
	    if (new_pathname_qm)
		reclaim_gensym_pathname(new_pathname_qm);
	    if (old_truename_qm)
		reclaim_gensym_pathname(old_truename_qm);
	    if (new_truename_qm)
		reclaim_gensym_pathname(new_truename_qm);
	    if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code)) {
		gensym_delete_file(temp_file_truename);
		termination_description = 
			most_recent_file_operation_status_as_text();
	    }
	}
	update_file_progress_display_status(Qclosed_compiled);
	if (T)
	    return reclaim_gensym_pathname(temp_file_truename);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* INCREMENT-COMPILED-KB-FILE */
Object increment_compiled_kb_file()
{
    Object svref_arg_1, svref_new_value, save_compiled_kb_stream_qm;

    x_note_fn_call(135,112);
    write_compiled_kb_file_specific_initialization_function();
    flush_compiled_kb_write_buffer();
    svref_arg_1 = Current_kb_save;
    ISVREF(svref_arg_1,(SI_Long)42L) = FIX((SI_Long)0L);
    svref_arg_1 = Current_kb_save;
    svref_new_value = ISVREF(Current_kb_save,(SI_Long)44L);
    SVREF(svref_arg_1,FIX((SI_Long)45L)) = svref_new_value;
    svref_arg_1 = Current_kb_save;
    svref_new_value = FIXNUM_ADD1(ISVREF(svref_arg_1,(SI_Long)46L));
    SVREF(svref_arg_1,FIX((SI_Long)46L)) = svref_new_value;
    close_and_rename_current_compiled_kb_stream();
    save_compiled_kb_stream_qm = open_save_kb_stream_or_reject_save_kb(T);
    if (save_compiled_kb_stream_qm) {
	svref_arg_1 = Current_kb_save;
	SVREF(svref_arg_1,FIX((SI_Long)15L)) = save_compiled_kb_stream_qm;
	svref_arg_1 = Current_kb_save;
	SVREF(svref_arg_1,FIX((SI_Long)17L)) = T;
	set_compiled_kb_file_pathname(Current_kb_save,
		ISVREF(Current_kb_save,(SI_Long)5L),ISVREF(Current_kb_save,
		(SI_Long)46L));
	write_initial_sections_of_compiled_kb_to_first_checkpoint();
    }
    return VALUES_1(Nil);
}

/* COMPILE-FILES-INTO-SHARED-OBJECT */
Object compile_files_into_shared_object(kb_save)
    Object kb_save;
{
    Object temp, kb_filename, dll_name;

    x_note_fn_call(135,113);
    temp = ISVREF(ISVREF(kb_save,(SI_Long)5L),(SI_Long)10L);
    kb_filename = FUNCALL_1(temp,ISVREF(kb_save,(SI_Long)5L));
    dll_name = kb_name_gt_shared_object_filename(kb_filename);
    temp = ISVREF(kb_save,(SI_Long)46L);
    c_produce_shared_object(kb_filename,temp,
	    get_object_file_suffix_for_this_os(),dll_name);
    reclaim_text_string(dll_name);
    return VALUES_1(Nil);
}

/* FINISH-CURRENT-KB-SAVE-OR-BACKUP */
Object finish_current_kb_save_or_backup(saving_context)
    Object saving_context;
{
    Object current_saving_context, enable_saving_compiled_kbs_p;
    Object current_computation_flags, write_xml_object_items_collected;
    Object total_items_in_file, current_kb_save, ab_loop_list_, temp;
    Declare_special(6);
    Object result;

    x_note_fn_call(135,114);
    current_saving_context = saving_context;
    PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
	    5);
      enable_saving_compiled_kbs_p = ISVREF(Current_saving_context,
	      (SI_Long)10L);
      PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
	      4);
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		3);
	  write_xml_object_items_collected = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
		  2);
	    total_items_in_file = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
		    1);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)2048L);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)4096L);
	      current_kb_save = Nil;
	      ab_loop_list_ = ISVREF(Current_saving_context,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
		      0);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		Current_kb_save = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		finish_current_kb_save();
		if ( !TRUEP(Current_saving_context_qm)) {
		    result = VALUES_1(Nil);
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    POP_SPECIAL();
		    goto end_finish_current_kb_save_or_backup;
		}
		goto next_loop;
	      end_loop:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = terminate_kb_save_or_backup(saving_context,Nil,Nil);
    result = VALUES_1(temp);
  end_finish_current_kb_save_or_backup:
    return result;
}

static Object Qfinish_current_kb_save_1;  /* finish-current-kb-save-1 */

/* FINISH-CURRENT-KB-SAVE */
Object finish_current_kb_save()
{
    x_note_fn_call(135,115);
    return funcall_to_write_to_kb_save_stream(2,
	    SYMBOL_FUNCTION(Qfinish_current_kb_save_1),
	    Qfinish_current_kb_save);
}

Object Current_compiled_byte_code_version = UNBOUND;

static Object string_constant_88;  /* "DLLEXPORT long initialize_compiled_kb(args)" */

static Object string_constant_89;  /* "  if (!check_version(" */

static Object string_constant_90;  /* ")) return 0;" */

static Object string_constant_91;  /* "  do_initialize_compiled_kb_" */

static Object string_constant_92;  /* "(args);" */

static Object string_constant_93;  /* "  return 1;" */

/* WRITE-COMPILED-KB-BOOTSTRAP-FUNCTION */
Object write_compiled_kb_bootstrap_function()
{
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(135,116);
    write_gensym_string_for_compiled_kb(string_constant_88);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_81);
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('{'));
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_89);
    write_fixnum_for_compiled_kb(Current_compiled_byte_code_version);
    write_gensym_string_for_compiled_kb(string_constant_90);
    write_char_for_compiled_kb(CHR('\n'));
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(ISVREF(Current_kb_save,(SI_Long)46L));
  next_loop:
    if (i > ab_loop_bind_)
	goto end_loop;
    write_gensym_string_for_compiled_kb(string_constant_91);
    write_fixnum_for_compiled_kb(FIX(i));
    write_gensym_string_for_compiled_kb(string_constant_92);
    write_char_for_compiled_kb(CHR('\n'));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    write_gensym_string_for_compiled_kb(string_constant_93);
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('}'));
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('\n'));
    return VALUES_1(Nil);
}

static Object string_constant_94;  /* "void dummy () {" */

static Object string_constant_95;  /* "  printf(\"Don't know why, but if this isn't here, dlopen bombs out on the sun4\");" */

/* WRITE-COMPILED-KB-DUMMY-FUNCTION */
Object write_compiled_kb_dummy_function()
{
    x_note_fn_call(135,117);
    write_gensym_string_for_compiled_kb(string_constant_94);
    write_char_for_compiled_kb(CHR('\n'));
    write_gensym_string_for_compiled_kb(string_constant_95);
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('}'));
    write_char_for_compiled_kb(CHR('\n'));
    write_char_for_compiled_kb(CHR('\n'));
    return VALUES_1(Nil);
}

/* WRITE-FINAL-PLIST-FOR-CURRENT-KB-SAVE */
Object write_final_plist_for_current_kb_save()
{
    x_note_fn_call(135,118);
    if (Enable_saving_compiled_kbs_p) {
	if (T) {
	    write_compiled_kb_file_specific_initialization_function();
	    write_compiled_kb_bootstrap_function();
	}
    }
    return write_final_plist(ISVREF(Current_kb_save,(SI_Long)12L),
	    ISVREF(Current_saving_context,(SI_Long)5L));
}

/* CLOSE-CURRENT-KB-SAVE-STREAM */
Object close_current_kb_save_stream()
{
    x_note_fn_call(135,119);
    return g2_stream_close(ISVREF(Current_kb_save,(SI_Long)4L));
}

/* CLOSE-CURRENT-COMPILED-KB-SAVE-STREAM */
Object close_current_compiled_kb_save_stream()
{
    x_note_fn_call(135,120);
    if (T)
	g2_stream_close(ISVREF(Current_kb_save,(SI_Long)15L));
    return VALUES_1(Nil);
}

static Object Qclosing;            /* closing */

static Object Qclose_current_kb_save_stream;  /* close-current-kb-save-stream */

static Object Qclose_failed;       /* close-failed */

static Object Qrename_failed;      /* rename-failed */

static Object Qclosed;             /* closed */

static Object Qunknown;            /* unknown */

/* CLOSE-AND-RENAME-KB-STREAM */
Object close_and_rename_kb_stream(stream,compiled_p,log_message_for_commit_qm)
    Object stream, compiled_p, log_message_for_commit_qm;
{
    Object temp_file_truename, termination_reason_qm, termination_description;
    Object temp, svref_arg_1, new_pathname_qm, old_truename_qm;
    Object new_truename_qm, old_namestring_for_user_qm, svref_new_value;
    Object module_qm;
    Object result;

    x_note_fn_call(135,121);
    if (stream) {
	temp_file_truename = T ? gensym_truename(stream) : Nil;
	termination_reason_qm = Nil;
	termination_description = Nil;
	update_file_progress_display_status(compiled_p ? Qclosing_compiled 
		: Qclosing);
	temp = funcall_to_write_to_kb_save_stream(3,compiled_p ? 
		SYMBOL_FUNCTION(Qclose_current_compiled_kb_save_stream) : 
		SYMBOL_FUNCTION(Qclose_current_kb_save_stream),
		Qfinish_current_kb_save,Finish_current_kb_save_failure);
	temp = EQ(temp,Finish_current_kb_save_failure) ? T : Nil;
	if (compiled_p) {
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)15L)) = Nil;
	}
	else {
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)4L)) = Nil;
	}
	if ( !TRUEP(temp)) {
	    if (termination_reason_qm)
		gensym_delete_file(temp_file_truename);
	    else if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
		    File_operation_succeeded_code)) {
		gensym_delete_file(temp_file_truename);
		termination_reason_qm = Qclose_failed;
		termination_description = 
			most_recent_file_operation_status_as_text();
	    }
	    else {
		checkpoint_file_if_necessary(compiled_p ? 
			ISVREF(Current_kb_save,(SI_Long)16L) : 
			ISVREF(Current_kb_save,(SI_Long)5L));
		result = gensym_rename_file(temp_file_truename,compiled_p ?
			 ISVREF(Current_kb_save,(SI_Long)16L) : 
			ISVREF(Current_kb_save,(SI_Long)5L));
		MVS_3(result,new_pathname_qm,old_truename_qm,new_truename_qm);
		if (new_pathname_qm && old_truename_qm && new_truename_qm) {
		    if (!compiled_p) {
			if (log_message_for_commit_qm)
			    try_to_commit_file(new_pathname_qm,
				    log_message_for_commit_qm);
			old_namestring_for_user_qm = 
				ISVREF(Current_kb_save,(SI_Long)7L);
			if (text_string_p(old_namestring_for_user_qm))
			    reclaim_text_string(old_namestring_for_user_qm);
			svref_arg_1 = Current_kb_save;
			svref_new_value = 
				gensym_namestring_as_text_string(1,
				new_truename_qm);
			SVREF(svref_arg_1,FIX((SI_Long)7L)) = svref_new_value;
		    }
		}
		if (new_pathname_qm)
		    reclaim_gensym_pathname(new_pathname_qm);
		if (old_truename_qm)
		    reclaim_gensym_pathname(old_truename_qm);
		if (new_truename_qm)
		    reclaim_gensym_pathname(new_truename_qm);
		if (FIXNUM_NE(Internal_status_of_most_recent_file_operation,
			File_operation_succeeded_code)) {
		    gensym_delete_file(temp_file_truename);
		    termination_reason_qm = Qrename_failed;
		    termination_description = 
			    most_recent_file_operation_status_as_text();
		}
	    }
	    update_file_progress_display_status(Qclosed);
	    if (termination_reason_qm)
		terminate_kb_save_or_backup(Current_saving_context,
			termination_reason_qm,termination_description);
	    else if ( !TRUEP(compiled_p) &&  !TRUEP(ISVREF(Current_kb_save,
		    (SI_Long)15L))) {
		module_qm = ISVREF(Current_kb_save,(SI_Long)37L);
		if (module_qm) {
		    mutate_kb_specific_property_value(module_qm,T,
			    Module_is_writable_p_kbprop);
		    set_reason_module_is_not_editable(module_qm,
			    file_is_in_source_code_control_p(ISVREF(Current_kb_save,
			    (SI_Long)5L)) ? Qunknown : Nil);
		}
		temp = 
			make_description_text_line_for_kb_save(Current_saving_context,
			Current_kb_save);
		notify_user_of_save_termination(temp,Nil,Nil,
			memq_function(ISVREF(Current_kb_save,(SI_Long)37L),
			Clear_text_saving_problems_were_encountered_p));
	    }
	    if (T)
		return reclaim_gensym_pathname(temp_file_truename);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfailed_to_write_items;  /* failed-to-write-items */

static Object Qwrite_final_plist_for_current_kb_save;  /* write-final-plist-for-current-kb-save */

static Object Qflush_kb_write_buffer;  /* flush-kb-write-buffer */

static Object Qflush_compiled_kb_write_buffer;  /* flush-compiled-kb-write-buffer */

/* FINISH-CURRENT-KB-SAVE-1 */
Object finish_current_kb_save_1()
{
    Object reason_if_bad_qm, temp, svref_arg_1, module_qm;
    char temp_1;

    x_note_fn_call(135,122);
    reason_if_bad_qm = EQ(ISVREF(Current_kb_save,(SI_Long)38L),Qnormal) ? 
	    check_frame_reference_balance_for_completed_save() : Qnil;
    if (reason_if_bad_qm)
	return terminate_kb_save_or_backup(Current_saving_context,
		Qfailed_to_write_items,reason_if_bad_qm);
    else {
	if (EQ(ISVREF(Current_kb_save,(SI_Long)38L),Qnormal)) {
	    temp = funcall_to_write_to_kb_save_stream(3,
		    SYMBOL_FUNCTION(Qwrite_final_plist_for_current_kb_save),
		    Qfinish_current_kb_save,Finish_current_kb_save_failure);
	    temp_1 = EQ(temp,Finish_current_kb_save_failure);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else {
	    temp = funcall_to_write_to_kb_save_stream(3,
		    SYMBOL_FUNCTION(Qflush_kb_write_buffer),
		    Qfinish_current_kb_save,Finish_current_kb_save_failure);
	    temp_1 = EQ(temp,Finish_current_kb_save_failure);
	}
	if (temp_1);
	else {
	    temp = funcall_to_write_to_kb_save_stream(3,
		    SYMBOL_FUNCTION(Qflush_compiled_kb_write_buffer),
		    Qfinish_current_kb_save,Finish_current_kb_save_failure);
	    temp_1 = EQ(temp,Finish_current_kb_save_failure);
	}
	if ( !temp_1) {
	    maybe_write_clear_text_diffs();
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)14L)) = Nil;
	    close_and_rename_kb_stream(ISVREF(Current_kb_save,(SI_Long)4L),
		    Nil,ISVREF(Current_kb_save,(SI_Long)48L));
	    svref_arg_1 = Current_kb_save;
	    SVREF(svref_arg_1,FIX((SI_Long)17L)) = Nil;
	    close_and_rename_kb_stream(ISVREF(Current_kb_save,
		    (SI_Long)15L),T,Nil);
	    module_qm = ISVREF(Current_kb_save,(SI_Long)37L);
	    if (module_qm)
		return update_saving_parameters_status_attributes(1,module_qm);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

static Object array_constant_15;   /* # */

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object string_constant_96;  /* "~a \"~a\"" */

/* MAKE-DESCRIPTION-TEXT-LINE-FOR-KB-SAVE */
Object make_description_text_line_for_kb_save(saving_context,
	    kb_save_if_known_qm)
    Object saving_context, kb_save_if_known_qm;
{
    Object temp;

    x_note_fn_call(135,123);
    temp = ISVREF(saving_context,(SI_Long)2L);
    if (EQ(temp,Qkb_save))
	temp = kb_save_if_known_qm ? 
		(string_equalw(ISVREF(ISVREF(kb_save_if_known_qm,
		(SI_Long)5L),(SI_Long)5L),array_constant_13) ? 
		array_constant_14 : array_constant_15) : array_constant_16;
    else if (EQ(temp,Qkb_save_with_runtime_data))
	temp = array_constant_17;
    else if (EQ(temp,Qruntime_data_only))
	temp = array_constant_18;
    else if (EQ(temp,Qok_kb_save))
	temp = array_constant_19;
    else
	temp = array_constant_20;
    return tformat_text_string(3,kb_save_if_known_qm ? string_constant_96 :
	     string_constant_5,temp,kb_save_if_known_qm ? 
	    ISVREF(kb_save_if_known_qm,(SI_Long)7L) : Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_97;  /* "Warning: THIS KB WAS NOT SAVED CORRECTLY! ~
				    *                         Please notify Gensym Customer Support of this internal ~
				    *                         software problem: this save failed to write ~d items: "
				    */

static Object string_constant_98;  /* "~NF (class: ~a, calling by: ~a)" */

static Object string_constant_99;  /* "Referenced items: " */

static Object string_constant_100;  /* "~NF (~a)" */

static Object string_constant_101;  /* "failed to write ~d items." */

/* CHECK-FRAME-REFERENCE-BALANCE-FOR-COMPLETED-SAVE */
Object check_frame_reference_balance_for_completed_save()
{
    Object balance, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object referenced_blocks, ab_loopvar__2, ab_loopvar__3;
    Object sub_class_bit_vector, gensymed_symbol_3;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object first_1, ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, temp_1, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, calling_function;
    Object ab_less_than_branch_qm_, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp;
    Declare_special(9);
    Object result;

    x_note_fn_call(135,124);
    balance = ISVREF(Current_kb_save,(SI_Long)32L);
    if ((SI_Long)0L != IFIX(balance)) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	block = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,8);
	  referenced_blocks = Nil;
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar_ = collect_subclasses(Qblock);
	next_loop:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_1:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop;
	      goto next_loop_1;
	    end_loop:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_1;
	  block = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if (block_referenced_in_current_save_p(block) &&  
		  !TRUEP(block_written_in_current_save_p(block))) {
	      sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Class_definition_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_1 = (SI_Long)1L;
		  gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		  gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		  temp = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp = TRUEP(Nil);
	      temp =  !temp;
	      if (temp);
	      else {
		  gensymed_symbol_3 = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		  gensymed_symbol_3 = gensymed_symbol_3 ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol_3,
			  (SI_Long)5L)) : Nil;
		  temp = TRUEP(gensymed_symbol_3);
	      }
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      ab_loopvar__3 = gensym_cons_1(block,Nil);
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__3;
	      else
		  referenced_blocks = ab_loopvar__3;
	      ab_loopvar__2 = ab_loopvar__3;
	  }
	  goto next_loop;
	end_loop_1:
	  snapshots_of_related_blocks = Nil;
	  note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	  PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		  7);
	    PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		    6);
	      current_wide_string_list = Qdo_not_use;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		      5);
		wide_string_bv16 = 
			allocate_byte_vector_16(FIX((SI_Long)2048L + 
			(SI_Long)3L));
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
		aref_arg_2 = bv16_length - (SI_Long)2L;
		aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
		UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
		aref_arg_2 = bv16_length - (SI_Long)1L;
		aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
		UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,(SI_Long)0L);
		current_wide_string = wide_string_bv16;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			4);
		  fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			  3);
		    length_1 = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		    total_length_of_current_wide_string = 
			    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)2L) + 
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    2);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      1);
			tformat(2,string_constant_97,balance);
			first_1 = T;
			scope_conses = Scope_conses;
			ab_node_stack_ = Nil;
			ab_current_node_ = Nil;
			ab_skip_list_form_ = ISVREF(Current_kb_save,
				(SI_Long)33L);
			ab_binary_tree_form_ = ISVREF(Current_kb_save,
				(SI_Long)33L);
			temp_1 = ISVREF(Current_kb_save,(SI_Long)33L);
			gensymed_symbol_3 = CDR(temp_1);
			if (CONSP(gensymed_symbol_3)) {
			    temp_1 = M_CAR(gensymed_symbol_3);
			    temp = SIMPLE_VECTOR_P(temp_1);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    temp_1 = M_CDR(gensymed_symbol_3);
			    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T :
				     Nil;
			}
			else
			    ab_skip_list_p_ = Nil;
			ab_next_node_ = Nil;
			ab_tail_node_ = Nil;
			ab_current_alist_ = Nil;
			ab_entry_cons_ = Nil;
			block = Nil;
			calling_function = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				0);
			  if (ab_skip_list_p_) {
			      ab_next_node_ = 
				      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
				      (SI_Long)0L),(SI_Long)0L));
			      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
			      if (EQ(ab_next_node_,ab_tail_node_))
				  ab_next_node_ = Nil;
			  }
			  else
			      ab_next_node_ = M_CDR(ab_binary_tree_form_);
			next_loop_2:
			  if (ab_current_alist_) {
			      ab_entry_cons_ = M_CAR(ab_current_alist_);
			      ab_current_alist_ = M_CDR(ab_current_alist_);
			  }
			  else if (ab_skip_list_p_) {
			      if (ab_next_node_) {
				  ab_current_node_ = ab_next_node_;
				  ab_next_node_ = 
					  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
					  (SI_Long)0L),(SI_Long)0L));
				  if (EQ(ab_next_node_,ab_tail_node_))
				      ab_next_node_ = Nil;
				  ab_entry_cons_ = 
					  scope_cons(ISVREF(ab_current_node_,
					  (SI_Long)2L),
					  ISVREF(ab_current_node_,
					  (SI_Long)3L));
			      }
			      else
				  ab_current_node_ = Nil;
			  }
			  else {
			      if (ab_next_node_) {
				  ab_current_node_ = ab_next_node_;
				  ab_less_than_branch_qm_ = Nil;
				next_loop_3:
				  ab_less_than_branch_qm_ = 
					  ISVREF(ab_current_node_,(SI_Long)1L);
				  if ( !TRUEP(ab_less_than_branch_qm_))
				      goto end_loop_2;
				  ab_node_stack_ = 
					  scope_cons(ab_current_node_,
					  ab_node_stack_);
				  ab_current_node_ = ab_less_than_branch_qm_;
				  goto next_loop_3;
				end_loop_2:;
			      }
			      else if (ab_node_stack_) {
				  ab_next_node_ = ab_node_stack_;
				  ab_current_node_ = M_CAR(ab_node_stack_);
				  ab_node_stack_ = M_CDR(ab_node_stack_);
			      }
			      else
				  ab_current_node_ = Nil;
			      if (ab_current_node_) {
				  ab_next_node_ = ISVREF(ab_current_node_,
					  (SI_Long)2L);
				  ab_current_alist_ = 
					  ISVREF(ab_current_node_,(SI_Long)3L);
				  ab_entry_cons_ = M_CAR(ab_current_alist_);
				  ab_current_alist_ = M_CDR(ab_current_alist_);
			      }
			  }
			  if ( !TRUEP(ab_current_node_))
			      goto end_loop_3;
			  block = CAR(ab_entry_cons_);
			  calling_function = CDR(ab_entry_cons_);
			  if ( !TRUEP(first_1))
			      tformat(1,string_constant_62);
			  tformat(4,string_constant_98,block,
				  ISVREF(ISVREF(block,(SI_Long)1L),
				  (SI_Long)1L),calling_function);
			  first_1 = Nil;
			  goto next_loop_2;
			end_loop_3:;
			POP_SPECIAL();
			tformat(1,string_constant_99);
			if ( !TRUEP(referenced_blocks))
			    tformat(1,string_constant_68);
			else {
			    first_1 = T;
			    block = Nil;
			    ab_loop_list_ = referenced_blocks;
			  next_loop_4:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_4;
			    block = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    if ( !TRUEP(first_1))
				tformat(1,string_constant_62);
			    tformat(3,string_constant_100,block,
				    ISVREF(ISVREF(block,(SI_Long)1L),
				    (SI_Long)1L));
			    first_1 = Nil;
			    goto next_loop_4;
			  end_loop_4:;
			}
			temp_1 = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      notify_user_1(temp_1);
	      if (Snapshots_of_related_blocks) {
		  reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		  Snapshots_of_related_blocks = Nil;
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	  reclaim_gensym_list_1(referenced_blocks);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
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
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
		    3);
	      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		      2);
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(2,string_constant_101,balance);
		    result = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DEFER-TERMINATE-KB-SAVE-OR-BACKUP */
Object defer_terminate_kb_save_or_backup(saving_context,
	    termination_reason_qm,stream_error_message_qm)
    Object saving_context, termination_reason_qm, stream_error_message_qm;
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(135,125);
    if ( !TRUEP(System_is_running))
	return terminate_kb_save_or_backup(saving_context,
		termination_reason_qm,stream_error_message_qm);
    else if (Return_from_save_to_caller_for_continuation_qm) {
	Current_saving_context_qm = saving_context;
	Kb_save_termination_reason_qm = termination_reason_qm;
	return update_terminate_kb_save_stream_error_message(stream_error_message_qm);
    }
    else {
	SVREF(saving_context,FIX((SI_Long)9L)) = T;
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = Continuation_task_for_current_backup;
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
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qterminate_kb_save_or_backup;
	temp = SYMBOL_FUNCTION(Qterminate_kb_save_or_backup);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
	SVREF(task,FIX((SI_Long)13L)) = saving_context;
	SVREF(task,FIX((SI_Long)14L)) = termination_reason_qm;
	SVREF(task,FIX((SI_Long)15L)) = stream_error_message_qm;
	new_1 = task;
	if (CAS_SYMBOL(Qcontinuation_task_for_current_backup,old,new_1)) {
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
}

static Object string_constant_102;  /* "WARNING: There were problems saving some attributes in clear text ~
				     *                     in the module~A ~(~L,A~).  These problems may prevent the kb ~
				     *                     from being correctly loaded.  Please fix these problems now, ~
				     *                     and save again."
				     */

static Object string_constant_103;  /* "s" */

/* TERMINATE-KB-SAVE-OR-BACKUP */
Object terminate_kb_save_or_backup(saving_context,termination_reason_qm,
	    stream_error_message_qm)
    Object saving_context, termination_reason_qm, stream_error_message_qm;
{
    Object display, ab_loop_list_, current_saving_context;
    Object enable_saving_compiled_kbs_p, current_computation_flags;
    Object write_xml_object_items_collected, total_items_in_file;
    Object current_kb_save, kb_object_index_property_name, display_qm, temp;
    Object file_is_open_qm, stream_qm, compiled_file_is_open_qm;
    Object compiled_stream_qm, gensymed_symbol, structure_being_reclaimed;
    Object svref_arg_2, temp_1;
    Declare_special(6);

    x_note_fn_call(135,126);
    if (Current_saving_context_qm) {
	if (termination_reason_qm || stream_error_message_qm)
	    notify_user_of_save_termination(make_description_text_line_for_kb_save(saving_context,
		    Nil),termination_reason_qm,stream_error_message_qm,Nil);
	if (Clear_text_saving_problems_were_encountered_p) {
	    notify_user(3,string_constant_102,
		    CDR(Clear_text_saving_problems_were_encountered_p) ? 
		    string_constant_103 : string_constant_1,
		    Clear_text_saving_problems_were_encountered_p);
	    reclaim_gensym_list_1(Clear_text_saving_problems_were_encountered_p);
	    Clear_text_saving_problems_were_encountered_p = Nil;
	}
	display = Nil;
	ab_loop_list_ = ISVREF(saving_context,(SI_Long)8L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	note_update_to_file_progress(2,display,Qdelete);
	delete_frame(display);
	goto next_loop;
      end_loop:;
	current_saving_context = saving_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
		5);
	  enable_saving_compiled_kbs_p = ISVREF(Current_saving_context,
		  (SI_Long)10L);
	  PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
		  4);
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    3);
	      write_xml_object_items_collected = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
		      2);
		total_items_in_file = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
			1);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) &  
			  ~(SI_Long)2048L);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) &  
			  ~(SI_Long)4096L);
		  current_kb_save = Nil;
		  ab_loop_list_ = ISVREF(Current_saving_context,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
			  0);
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    Current_kb_save = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    kb_object_index_property_name = ISVREF(Current_kb_save,
			    (SI_Long)22L);
		    delete_kb_object_index_property_names(kb_object_index_property_name,
			    ISVREF(Current_kb_save,(SI_Long)28L));
		    Kb_object_index_property_name_pool = 
			    gensym_cons_1(kb_object_index_property_name,
			    Kb_object_index_property_name_pool);
		    display_qm = ISVREF(Current_kb_save,(SI_Long)13L);
		    if (display_qm) {
			temp = Current_kb_save;
			SVREF(temp,FIX((SI_Long)13L)) = Nil;
		    }
		    file_is_open_qm = ISVREF(Current_kb_save,(SI_Long)14L);
		    stream_qm = ISVREF(Current_kb_save,(SI_Long)4L);
		    compiled_file_is_open_qm = ISVREF(Current_kb_save,
			    (SI_Long)17L);
		    compiled_stream_qm = ISVREF(Current_kb_save,(SI_Long)15L);
		    reclaim_kb_save_1(Current_kb_save);
		    if (file_is_open_qm && stream_qm)
			gensym_close_and_delete_file(stream_qm);
		    if ((compiled_file_is_open_qm || 
			    Delete_compiled_kb_source_p) && 
				compiled_stream_qm) {
			if (T)
			    gensym_delete_file(compiled_stream_qm);
		    }
		    goto next_loop_1;
		  end_loop_1:;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	Save_kb_state_for_system_procedure_save = Nil;
	gensymed_symbol = Nil;
      next_loop_2:
	gensymed_symbol = Continuation_task_for_current_backup;
	if (CAS_SYMBOL(Qcontinuation_task_for_current_backup,
		gensymed_symbol,Nil)) {
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
	goto next_loop_2;
      end_loop_2:
      end_1:;
	Current_saving_context_qm = Nil;
	Noting_changes_to_kb_p = Nil;
	if (ISVREF(saving_context,(SI_Long)4L))
	    change_all_permanently_changed_things_are_marked(termination_reason_qm 
		    ? Nil : T);
	if (Return_from_save_to_caller_for_continuation_qm) {
	    Kb_save_termination_reason_qm = termination_reason_qm;
	    Return_from_save_to_caller_for_continuation_qm = Nil;
	}
	temp_1 = reclaim_saving_context_1(saving_context);
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object string_constant_104;  /* "WARNING: ~a did not complete. Problem: ~a" */

static Object string_constant_105;  /* "~a completed successfully, but there were problems saving some attributes" */

static Object string_constant_106;  /* "~a completed successfully" */

/* NOTIFY-USER-OF-SAVE-TERMINATION */
Object notify_user_of_save_termination(save_description_text_line,
	    termination_reason_qm,stream_error_message_qm,
	    clear_text_problems_p)
    Object save_description_text_line, termination_reason_qm;
    Object stream_error_message_qm, clear_text_problems_p;
{
    Object temp, error_text_string_qm;

    x_note_fn_call(135,127);
    if (termination_reason_qm) {
	temp = stream_error_message_qm;
	if (temp);
	else
	    temp = termination_reason_qm;
	error_text_string_qm = tformat_text_string(2,string_constant_5,temp);
    }
    else
	error_text_string_qm = Nil;
    if (termination_reason_qm) {
	if ( !TRUEP(Suppress_notification_for_kb_save_qm))
	    notify_user(3,string_constant_104,save_description_text_line,
		    error_text_string_qm);
    }
    else
	notify_user(2,clear_text_problems_p ? string_constant_105 : 
		string_constant_106,save_description_text_line);
    reclaim_text_string(save_description_text_line);
    return update_terminate_kb_save_stream_error_message(error_text_string_qm);
}

DEFINE_VARIABLE_WITH_SYMBOL(Terminate_kb_save_stream_error_message_qm, Qterminate_kb_save_stream_error_message_qm);

/* UPDATE-TERMINATE-KB-SAVE-STREAM-ERROR-MESSAGE */
Object update_terminate_kb_save_stream_error_message(stream_error_message_qm)
    Object stream_error_message_qm;
{
    x_note_fn_call(135,128);
    if (Terminate_kb_save_stream_error_message_qm &&  
	    !EQ(stream_error_message_qm,
	    Terminate_kb_save_stream_error_message_qm))
	reclaim_text_string(Terminate_kb_save_stream_error_message_qm);
    Terminate_kb_save_stream_error_message_qm = stream_error_message_qm;
    return VALUES_1(Terminate_kb_save_stream_error_message_qm);
}

/* TERMINATE-KB-SAVE-OR-BACKUP-IF-ERROR-OCCURS */
Object terminate_kb_save_or_backup_if_error_occurs()
{
    x_note_fn_call(135,129);
    if (Current_saving_context_qm)
	return terminate_kb_save_or_backup(Current_saving_context_qm,
		Qerror_writing_file,Nil);
    else {
	Return_from_save_to_caller_for_continuation_qm = Nil;
	Kb_save_termination_reason_qm = Nil;
	Suppress_notification_for_kb_save_qm = Nil;
	Terminate_kb_save_stream_error_message_qm = Nil;
	Save_kb_state_for_system_procedure_save = Nil;
	return VALUES_1(Save_kb_state_for_system_procedure_save);
    }
}

/* CLEANUP-KB-SAVE-OR-BACKUP-IF-NECESSARY */
Object cleanup_kb_save_or_backup_if_necessary(x)
    Object x;
{
    x_note_fn_call(135,130);
    return terminate_kb_save_or_backup_if_error_occurs();
}

/* HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-BLOCK */
Object handle_change_or_deletion_fanout_for_block(block,
	    slot_name_or_t_in_change_case_qm)
    Object block, slot_name_or_t_in_change_case_qm;
{
    x_note_fn_call(135,131);
    if (ISVREF(Current_kb_save,(SI_Long)37L) &&  
	    !TRUEP(slot_name_or_t_in_change_case_qm))
	return remove_block_from_module(block);
    else
	return VALUES_1(Nil);
}

static Object Qworkspace;          /* workspace */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-WORKSPACE */
Object handle_change_or_deletion_fanout_for_workspace(workspace,
	    slot_name_or_t_in_change_case_qm)
    Object workspace, slot_name_or_t_in_change_case_qm;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(135,132);
    frame = workspace;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)49L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qworkspace)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_2(method_function_qm,frame,
		slot_name_or_t_in_change_case_qm);
    if (ISVREF(Current_kb_save,(SI_Long)37L) && 
	    EQ(slot_name_or_t_in_change_case_qm,Qmodule_this_is_part_of_qm))
	return remove_block_from_module(workspace);
    else
	return VALUES_1(Nil);
}

static Object Qtop_level_kb_module_qm;  /* top-level-kb-module? */

/* HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-MODULE-INFORMATION */
Object handle_change_or_deletion_fanout_for_module_information(module_information,
	    slot_name_or_t_in_change_case_qm)
    Object module_information, slot_name_or_t_in_change_case_qm;
{
    Object frame, sub_vector_qm, method_function_qm, module, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, block;
    SI_Long index_1, ab_loop_bind_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(135,133);
    PUSH_SPECIAL_WITH_SYMBOL(Module_information,Qmodule_information,module_information,
	    1);
      frame = Module_information;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)49L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qmodule_information)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_1;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop;
    end_loop:
      method_function_qm = Qnil;
    end_1:;
      if (method_function_qm)
	  inline_funcall_2(method_function_qm,frame,
		  slot_name_or_t_in_change_case_qm);
      if (EQ(slot_name_or_t_in_change_case_qm,Qtop_level_kb_module_qm) && 
	      ISVREF(Current_kb_save,(SI_Long)37L)) {
	  module = ISVREF(Current_kb_save,(SI_Long)37L);
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qblock);
	  next_loop_1:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_2:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_1;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_1;
		goto next_loop_2;
	      end_loop_1:
		temp =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		goto end_loop_2;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (EQ(get_module_block_is_in(block),module))
		note_change_or_deletion(block,T);
	    goto next_loop_1;
	  end_loop_2:
	    result = VALUES_1(Qnil);
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qrelation;           /* relation */

/* HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-RELATION */
Object handle_change_or_deletion_fanout_for_relation(relation,
	    slot_name_or_t_in_change_case_qm)
    Object relation, slot_name_or_t_in_change_case_qm;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(135,134);
    frame = relation;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)49L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrelation)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_2(method_function_qm,frame,
		slot_name_or_t_in_change_case_qm);
    if (ISVREF(Current_saving_context,(SI_Long)3L))
	return note_change_to_all_related_items(relation);
    else
	return VALUES_1(Nil);
}

static Object Qruntime_data;       /* runtime-data */

/* NOTE-CHANGE-TO-RUNTIME-DATA-FOR-BLOCK-1 */
Object note_change_to_runtime_data_for_block_1(block)
    Object block;
{
    Object temp;

    x_note_fn_call(135,135);
    temp = Current_saving_context_qm && ISVREF(Current_saving_context_qm,
	    (SI_Long)3L) ? note_change_to_block_2(block,Qruntime_data) : Nil;
    return VALUES_1(temp);
}

/* SAVE-BLOCK-FOR-CHANGE-P */
Object save_block_for_change_p(block)
    Object block;
{
    Object temp;

    x_note_fn_call(135,136);
    if (block_should_be_written_p(block)) {
	temp = ISVREF(Current_saving_context,(SI_Long)4L);
	if (temp);
	else
	    temp = EQ(ISVREF(Current_saving_context,(SI_Long)2L),Qbackup) ?
		     ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		    (SI_Long)4L) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* BLOCK-SHOULD-BE-WRITTEN-P */
Object block_should_be_written_p(block)
    Object block;
{
    Object temp;

    x_note_fn_call(135,137);
    temp = ISVREF(Current_kb_save,(SI_Long)49L) && (SI_Long)0L != 
	    (IFIX(ISVREF(block,(SI_Long)5L)) & (SI_Long)8L) ? ( 
	    !TRUEP(block_written_in_current_save_p(block)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* SAVE-CONNECTION-FOR-CHANGE-P */
Object save_connection_for_change_p(connection_structure)
    Object connection_structure;
{
    Object temp;

    x_note_fn_call(135,138);
    if (connection_should_be_written_p(connection_structure)) {
	temp = ISVREF(Current_saving_context,(SI_Long)4L);
	if (temp);
	else
	    temp = EQ(ISVREF(Current_saving_context,(SI_Long)2L),Qbackup) ?
		     ((SI_Long)0L != (IFIX(ISVREF(connection_structure,
		    (SI_Long)7L)) & (SI_Long)2L) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CONNECTION-SHOULD-BE-WRITTEN-P */
Object connection_should_be_written_p(connection_structure)
    Object connection_structure;
{
    Object temp;

    x_note_fn_call(135,139);
    temp = ISVREF(Current_kb_save,(SI_Long)49L) && (SI_Long)0L != 
	    (IFIX(ISVREF(connection_structure,(SI_Long)7L)) & (SI_Long)8L) 
	    ? ( !((SI_Long)0L != (IFIX(ISVREF(connection_structure,
	    (SI_Long)7L)) & (SI_Long)4L)) ? T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* NOTE-CHANGE-TO-BLOCK-2 */
Object note_change_to_block_2(block,slot_name_qm)
    Object block, slot_name_qm;
{
    Object temp;

    x_note_fn_call(135,140);
    temp = slot_name_qm;
    if (temp);
    else
	temp = T;
    note_change_or_deletion(block,temp);
    return VALUES_1(Nil);
}

/* NOTE-DELETION-OF-BLOCK-2 */
Object note_deletion_of_block_2(block)
    Object block;
{
    x_note_fn_call(135,141);
    note_change_or_deletion(block,Nil);
    return VALUES_1(Nil);
}

/* NOTE-CHANGE-TO-CONNECTION-2 */
Object note_change_to_connection_2(connection_structure)
    Object connection_structure;
{
    Object temp;

    x_note_fn_call(135,142);
    note_change_or_deletion(connection_structure,T);
    temp = ISVREF(connection_structure,(SI_Long)1L);
    if ( !SYMBOLP(temp))
	note_change_or_deletion(ISVREF(connection_structure,(SI_Long)1L),T);
    return VALUES_1(Nil);
}

/* NOTE-DELETION-OF-CONNECTION-2 */
Object note_deletion_of_connection_2(connection_structure)
    Object connection_structure;
{
    x_note_fn_call(135,143);
    note_change_or_deletion(connection_structure,Nil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(The_only_dynamic_computation_style, Qthe_only_dynamic_computation_style);

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qdynamic_text_cell_format;  /* dynamic-text-cell-format */

/* NOTE-CHANGE-OR-DELETION */
Object note_change_or_deletion(block_or_connection,
	    slot_name_or_t_in_change_case_qm)
    Object block_or_connection, slot_name_or_t_in_change_case_qm;
{
    Object x2, block_case_qm, current_saving_context;
    Object enable_saving_compiled_kbs_p, current_computation_flags;
    Object write_xml_object_items_collected, total_items_in_file;
    Object current_kb_save, ab_loop_list_, block, module, frame, sub_vector_qm;
    Object function_qm, gensymed_symbol, xa, ya;
    SI_Long method_index, svref_new_value;
    char temp;
    Declare_special(6);

    x_note_fn_call(135,144);
    if (Current_saving_context_qm &&  !(EQ(block_or_connection,
	    Current_text_box_format) && 
	    EQ(get_lookup_slot_value_given_default(block_or_connection,
	    Qname_or_names_for_frame,Nil),Qdynamic_text_cell_format) || 
	    EQ(block_or_connection,The_only_dynamic_computation_style))) {
	if (SIMPLE_VECTOR_P(block_or_connection) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_connection)) > 
		(SI_Long)2L &&  !EQ(ISVREF(block_or_connection,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(block_or_connection,(SI_Long)1L);
	    block_case_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    block_case_qm = Nil;
	current_saving_context = Current_saving_context_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
		5);
	  enable_saving_compiled_kbs_p = ISVREF(Current_saving_context,
		  (SI_Long)10L);
	  PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
		  4);
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    3);
	      write_xml_object_items_collected = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
		      2);
		total_items_in_file = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
			1);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) &  
			  ~(SI_Long)2048L);
		  Current_computation_flags = 
			  FIX(IFIX(Current_computation_flags) &  
			  ~(SI_Long)4096L);
		  current_kb_save = Nil;
		  ab_loop_list_ = ISVREF(Current_saving_context,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
			  0);
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    Current_kb_save = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (EQ(ISVREF(Current_kb_save,(SI_Long)38L),Qnormal) 
			    && (block_case_qm ? (SI_Long)0L != 
			    (IFIX(ISVREF(block_or_connection,(SI_Long)4L)) 
			    & (SI_Long)1L) || 
			    ISVREF(Current_saving_context,(SI_Long)3L) && 
			    (SI_Long)0L != 
			    (IFIX(ISVREF(block_or_connection,(SI_Long)5L)) 
			    & (SI_Long)262144L) :  !((SI_Long)0L != 
			    (IFIX(ISVREF(block_or_connection,(SI_Long)7L)) 
			    & (SI_Long)64L)) || 
			    ISVREF(Current_saving_context,(SI_Long)3L))) {
			temp =  !TRUEP(ISVREF(Current_kb_save,(SI_Long)37L));
			if (temp);
			else if (block_case_qm) {
			    block = block_or_connection;
			    module = ISVREF(Current_kb_save,(SI_Long)37L);
			    temp = EQ(get_module_block_is_in(block),module);
			}
			else
			    temp = 
				    TRUEP(connection_within_module_p(block_or_connection,
				    ISVREF(Current_kb_save,(SI_Long)37L)));
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			if (block_case_qm ? 
				TRUEP(save_block_for_change_p(block_or_connection)) 
				: 
				TRUEP(save_connection_for_change_p(block_or_connection)))
			    continue_current_kb_save(block_or_connection);
			if (block_case_qm) {
			    method_index = (SI_Long)49L;
			    frame = block_or_connection;
			    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,
				    (SI_Long)1L),(SI_Long)11L),method_index);
			    function_qm = sub_vector_qm ? 
				    ISVREF(sub_vector_qm,(SI_Long)1L) : Nil;
			    if (function_qm)
				inline_funcall_2(function_qm,frame,
					slot_name_or_t_in_change_case_qm);
			}
		    }
		    goto next_loop;
		  end_loop:;
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if (slot_name_or_t_in_change_case_qm) {
	    if (block_case_qm) {
		svref_new_value = IFIX(ISVREF(block_or_connection,
			(SI_Long)5L)) | (SI_Long)4L;
		ISVREF(block_or_connection,(SI_Long)5L) = FIX(svref_new_value);
	    }
	    else {
		svref_new_value = IFIX(ISVREF(block_or_connection,
			(SI_Long)7L)) | (SI_Long)2L;
		ISVREF(block_or_connection,(SI_Long)7L) = FIX(svref_new_value);
	    }
	}
	else {
	    if (All_permanently_changed_things_are_marked) {
		if (block_case_qm) {
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)3L);
		    temp = SIMPLE_VECTOR_P(block_or_connection) ? 
			    EQ(ISVREF(block_or_connection,(SI_Long)1L),
			    Qavailable_frame_vector) : TRUEP(Qnil);
		    if (temp);
		    else
			temp = FIXNUMP(gensymed_symbol) ? 
				IFIX(gensymed_symbol) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(Basis_kb_frame_serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(Basis_kb_frame_serial_number,
				gensymed_symbol) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(Basis_kb_frame_serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(Basis_kb_frame_serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    temp =  !temp;
		}
		else {
		    gensymed_symbol = ISVREF(block_or_connection,(SI_Long)10L);
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		    if (temp);
		    else if (FIXNUMP(Basis_kb_frame_serial_number))
			temp = FIXNUMP(gensymed_symbol) ? 
				FIXNUM_LT(Basis_kb_frame_serial_number,
				gensymed_symbol) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(Basis_kb_frame_serial_number);
			ya = M_CAR(gensymed_symbol);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(Basis_kb_frame_serial_number),
				    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		    }
		    temp =  !temp;
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		add_deleted_item_to_list(block_or_connection,block_case_qm);
	}
    }
    return VALUES_1(Nil);
}

void kb_save3_INIT()
{
    Object temp, temp_1, gensymed_symbol;
    Object status_text_or_none_evaluation_getter_1;
    Object source_code_control_name_evaluation_getter_1;
    Object user_name_sequence_evaluation_getter_1;
    Object readonly_yes_or_no_evaluation_getter_1;
    Object xml_primitive_value_style_evaluation_setter_1;
    Object xml_primitive_value_style_evaluation_getter_1;
    Object unsavable_change_protection_specification_evaluation_setter_1;
    Object unsavable_change_protection_specification_evaluation_getter_1;
    Object unsavable_change_protection_evaluation_setter_1;
    Object unsavable_change_protection_evaluation_getter_1;
    Object basis_kb_evaluation_getter_1;
    Object file_name_of_basis_kb_evaluation_getter_1, temp_2;
    Object AB_package, Qclasses_which_define;
    Object Qhandle_change_or_deletion_fanout;
    Object Qhandle_change_or_deletion_fanout_for_relation;
    Object Qhandle_change_or_deletion_fanout_for_module_information;
    Object Qhandle_change_or_deletion_fanout_for_workspace;
    Object Qhandle_change_or_deletion_fanout_for_block;
    Object Qgeneric_method_lambda_list, list_constant_59;
    Object Qslot_name_or_t_in_change_case_qm;
    Object Qterminate_kb_save_or_backup_if_error_occurs, list_constant_13;
    Object list_constant_58, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_57, Qerror_writing_file_3, Qerror_writing_file_2;
    Object Qerror_writing_file_1, list_constant_56, list_constant_55, Qsave_kb;
    Object Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_saving_parameters;
    Object Qinstall_system_table, Qinstall_system_table_for_saving_parameters;
    Object Qfile_name_of_basis_kb, list_constant_54;
    Object Qtype_specification_simple_expansion, Qslot_value_writer;
    Object Qwrite_filename_of_basis_kb_from_slot, Qfilename_of_basis_kb;
    Object Qbasis_kb, list_constant_53, list_constant_15, Qab_or;
    Object Qwrite_basis_kb_from_slot, Qwrite_journalling_status_from_slot;
    Object Qjournalling_status, Qkb_save3, Qnamed, list_constant_52;
    Object list_constant_51, list_constant_50, Qab_structure, list_constant_49;
    Object list_constant_48, list_constant_47, list_constant_46;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_unsavable_change_protection_for_slot;
    Object Qcompile_unsavable_change_protection_specification_for_slot;
    Object Qwrite_unsavable_change_protection_from_slot;
    Object Qwrite_unsavable_change_protection_specification_from_slot;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object Qxml_primitive_value_style, list_constant_24, list_constant_45;
    Object list_constant_44, list_constant_43, list_constant_42;
    Object list_constant_41, list_constant_40, list_constant_39;
    Object list_constant_38, list_constant_31, list_constant_30;
    Object list_constant_25, list_constant_36, list_constant_27;
    Object list_constant_33, list_constant_32, list_constant_26;
    Object list_constant_23, list_constant_37, list_constant_34;
    Object list_constant_29, list_constant_28, Qcontents, list_constant_22;
    Object list_constant_35, Qvalue, Qattribute, Qg2, Qof, Qelement, Qsub, Qis;
    Object Qcompile_xml_primitive_value_style_for_slot;
    Object Qwrite_xml_primitive_value_style_from_slot, Quuid, Qattribute_name;
    Object list_constant_21, Qwrite_clear_text_history_from_slot;
    Object Qdefault_priority_for_runtime_saving, Qjournal_priority;
    Object Qabsent_slot_putter, Qput_journalling_status_where_slot_is_absent;
    Object Qput_number_of_backup_files_where_slot_is_absent;
    Object Qnumber_of_backup_files, Qput_pathname_format_where_slot_is_absent;
    Object Qpathname_format, Qput_enable_journalling_where_slot_is_absent;
    Object Qenable_journalling, Qsubstitute_class_and_kb_flags;
    Object Qjournal_and_backup_parameters, Qreadonly_yes_or_no;
    Object Qwrite_readonly_yes_or_no_from_slot, Quser_name_sequence;
    Object list_constant_20, list_constant_17, list_constant_19;
    Object Qwrite_user_name_sequence_from_slot, Qsource_code_control_name;
    Object list_constant_18, Qwrite_source_code_control_name_from_slot;
    Object Qstatus_text_or_none, list_constant_16, Qno_item;
    Object Qwrite_status_text_or_none_from_slot;
    Object Qg2_update_saving_parameters_status_attributes;
    Object Qfunction_keeps_procedure_environment_valid_qm, list_constant_14;
    Object Qget_enable_source_code_control_from_environment_or_command_line;
    Object list_constant_12, Kfuncall, Ksystem_frame, string_constant_123;
    Object string_constant_122, string_constant_121, string_constant_120;
    Object string_constant_119, list_constant_11, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object string_constant_111, string_constant_110, string_constant_109;
    Object string_constant_108, string_constant_107, Qsystem_table;

    x_note_fn_call(135,145);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsaving_parameters = STATIC_SYMBOL("SAVING-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_11 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qsaving_parameters,list_constant_11);
    string_constant_107 = STATIC_STRING("1l1l83ey");
    string_constant_108 = 
	    STATIC_STRING("13Iy4z8r83T8y83T8y83Zfy83Zfy0s001n1l8o1l8l1m8p83-Yy000004z8r83Rvy83Rvy83Zfy83Zfy00001o1l83Ey1l8l1l83Fy1m8p83H9y000004z8r83LSy83L");
    string_constant_109 = 
	    STATIC_STRING("Sy83Zfy83Zfy00001o1l83Ey1l8l1l83Fy1m8p83LSy000004z8r83TBy83TBy83Zfy83Zfy00001n1n8p83-dy83Gy1l83Ey1l8l000004z8r83KWy83KWy83Zfy83Z");
    string_constant_110 = 
	    STATIC_STRING("fy00001n1l83Ey1l8l1m8p83Ky000004z8r83KVy83KVy83Zfy83Zfy00001n1l83Ey1l8l1m8p83Ky000004z8r83TMy83TMy83Zfy83Zfy00001o1l83Ey1l8l1m8p");
    string_constant_111 = 
	    STATIC_STRING("83TMy1l83Fy000004z8r83Fiy83Fiy83Zfy83Zfy083Py001n1l83Ey1l8l1m8p0000004z8r83JPy83JPy83Zfy83Zfy01m83Boy9k001n1l83Ey1l8l1m8p0000004");
    string_constant_112 = 
	    STATIC_STRING("z8r83Zey83Zey83Zfy83Zfy00001n1l83Ey1l8l1m8p83Ky000004z8r83G-y83G-y83Zfy83Zfy083Fdy001n1l83Ey1l8l1m8p83G-y000004z8r83I*y83I*y83Zf");
    string_constant_113 = 
	    STATIC_STRING("y83Zfy00001p1l8o1l8l1l83Cy1m8p83I*y1l83Fy000004z8r83Iwy83Iwy83Zfy83Zfy00001p1l83Ey1l8l1m8p83LSy1l83Fy1l83Hy000004z8r83Ycy83Ycy83");
    string_constant_114 = 
	    STATIC_STRING("Zfy83Zfy00001q1l83Ey1l8l1m8p01l83Fy1l83Hy1l83-4y000004z8r83Vsy83Vsy83Zfy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83aXy83aX");
    string_constant_115 = 
	    STATIC_STRING("y83Zfy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83aYy83aYy83Zfy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83Vry83Vry83Z");
    string_constant_116 = 
	    STATIC_STRING("fy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83djy83djy83Zfy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83dwy83dwy83Zfy83");
    string_constant_117 = 
	    STATIC_STRING("Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83WTy83WTy83Zfy83Zfy00001p1l83Ey1l8l1m8p01l83Fy1l83Hy000004z8r83HKy83HKy83Zfy83Zfy0");
    string_constant_118 = 
	    STATIC_STRING("0001p1l83Ey1l8l1m8p01l83Fy1l83Hy00000");
    string_constant_119 = 
	    STATIC_STRING("13Ky8q1n83Zfy1l83-sy83ey1p83T8ys8o8l1m8p83-Yy1q83Rvy083Ey8l83Fy1m8p83H9y1q83LSy083Ey8l83Fy1m8p83LSy1p83TBy01n8p83-dy83Gy83Ey8l1p");
    string_constant_120 = 
	    STATIC_STRING("83KWy083Ey8l1m8p83Ky1p83KVy083Ey8l1m8p83Ky1q83TMy083Ey8l1m8p83TMy83Fy1p83Fiy83Py83Ey8l1m8p01p83JPy1m83Boy9k83Ey8l1m8p01p83Zey083");
    string_constant_121 = 
	    STATIC_STRING("Ey8l1m8p83Ky1p83G-y83Fdy83Ey8l1m8p83G-y1r83I*y01l8o1l8l1l83Cy1m8p83I*y83Fy1r83Iwy083Ey8l1m8p83LSy83Fy83Hy1s83Ycy083Ey8l1m8p083Fy");
    string_constant_122 = 
	    STATIC_STRING("83Hy83-4y1r83Vsy083Ey8l1m8p083Fy83Hy1r83aXy083Ey8l1m8p083Fy83Hy1r83aYy083Ey8l1m8p083Fy83Hy1r83Vry083Ey8l1m8p083Fy83Hy1r83djy083E");
    string_constant_123 = 
	    STATIC_STRING("y8l1m8p083Fy83Hy1r83dwy083Ey8l1m8p083Fy83Hy1r83WTy083Ey8l1m8p083Fy83Hy1r83HKy083Ey8l1m8p083Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_107);
    clear_optimized_constants();
    push_optimized_constant(Qwarn);
    temp_1 = regenerate_optimized_constant(list(11,string_constant_108,
	    string_constant_109,string_constant_110,string_constant_111,
	    string_constant_112,string_constant_113,string_constant_114,
	    string_constant_115,string_constant_116,string_constant_117,
	    string_constant_118));
    clear_optimized_constants();
    push_optimized_constant(Qwarn);
    add_class_to_environment(9,Qsaving_parameters,list_constant_11,Nil,
	    temp,Nil,temp_1,list_constant_11,
	    regenerate_optimized_constant(LIST_5(string_constant_119,
	    string_constant_120,string_constant_121,string_constant_122,
	    string_constant_123)),Nil);
    Qkb_save3 = STATIC_SYMBOL("KB-SAVE3",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qsaving_parameters,Qkb_save3,Ksystem_frame,Qnil,
	    Qnil,Qnil,Qt);
    if (Current_cvs_command == UNBOUND)
	Current_cvs_command = Nil;
    if (Cvs_command_initial_timeout == UNBOUND)
	Cvs_command_initial_timeout = ltimes(FIX((SI_Long)2L),
		FIX((SI_Long)1000L));
    if (Permit_cvs_timeout_dialog_p == UNBOUND)
	Permit_cvs_timeout_dialog_p = T;
    if (Cvs_command_timed_out_p == UNBOUND)
	Cvs_command_timed_out_p = Nil;
    Qsource_code_control_support_enabled_p = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-SUPPORT-ENABLED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsource_code_control_support_enabled_p,
	    Source_code_control_support_enabled_p);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qget_enable_source_code_control_from_environment_or_command_line = 
	    STATIC_SYMBOL("GET-ENABLE-SOURCE-CODE-CONTROL-FROM-ENVIRONMENT-OR-COMMAND-LINE",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_enable_source_code_control_from_environment_or_command_line);
    record_system_variable(Qsource_code_control_support_enabled_p,
	    Qkb_save3,list_constant_12,Qnil,Qnil,Qnil,Qnil);
    if (Source_code_control_is_enabled_by_default == UNBOUND)
	Source_code_control_is_enabled_by_default = Nil;
    SET_SYMBOL_FUNCTION(Qget_enable_source_code_control_from_environment_or_command_line,
	    STATIC_FUNCTION(get_enable_source_code_control_from_environment_or_command_line,
	    NIL,FALSE,0,0));
    if (Ms_to_wait_for_cvs == UNBOUND)
	Ms_to_wait_for_cvs = Nil;
    Qsource_code_control_support_is_enabled = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-SUPPORT-IS-ENABLED",AB_package);
    if (Workstations_with_their_stacks_for_timeout_of_source_code_control 
	    == UNBOUND)
	Workstations_with_their_stacks_for_timeout_of_source_code_control 
		= Nil;
    if (Ui_client_interfaces_for_timeout_of_source_code_control == UNBOUND)
	Ui_client_interfaces_for_timeout_of_source_code_control = Nil;
    string_constant = 
	    STATIC_STRING("Waiting for the command:~a~%~\n         This probably means someone else is currently committing files, ~\n         or that the cvs server is unreachable.");
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)47L,(SI_Long)57344L);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qdisable_cvs_support_and_return_0 = 
	    STATIC_SYMBOL("DISABLE-CVS-SUPPORT-AND-RETURN-0",AB_package);
    SET_SYMBOL_FUNCTION(Qdisable_cvs_support_and_return_0,
	    STATIC_FUNCTION(disable_cvs_support_and_return_0,NIL,FALSE,0,0));
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qscc_timeout_message = STATIC_SYMBOL("SCC-TIMEOUT-MESSAGE",AB_package);
    Qscc_timeout = STATIC_SYMBOL("SCC-TIMEOUT",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qcancel_and_disable_scc = STATIC_SYMBOL("CANCEL-AND-DISABLE-SCC",
	    AB_package);
    Qcontinuation_for_scc_timeout_dialog_for_ui_client_interface = 
	    STATIC_SYMBOL("CONTINUATION-FOR-SCC-TIMEOUT-DIALOG-FOR-UI-CLIENT-INTERFACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcontinuation_for_scc_timeout_dialog_for_ui_client_interface,
	    STATIC_FUNCTION(continuation_for_scc_timeout_dialog_for_ui_client_interface,
	    NIL,FALSE,2,2));
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qx11_window = STATIC_SYMBOL("X11-WINDOW",AB_package);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qui_client_interface = STATIC_SYMBOL("UI-CLIENT-INTERFACE",AB_package);
    if (Return_to_waiting_for_cvs_p == UNBOUND)
	Return_to_waiting_for_cvs_p = Nil;
    Qvms = STATIC_SYMBOL("VMS",AB_package);
    Qnamestring_as_gensym_string = 
	    STATIC_SYMBOL("NAMESTRING-AS-GENSYM-STRING",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_gensym_pathname_g2_struct = 
	    STATIC_SYMBOL("GENSYM-PATHNAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_1 = STATIC_STRING("");
    string_constant_2 = STATIC_STRING("cvs ~a ~a ~a ~a");
    string_constant_3 = STATIC_STRING("cvs ~a ~a ~a");
    string_constant_4 = STATIC_STRING("cvs ~a ~a");
    string_constant_5 = STATIC_STRING("~a");
    Qcvs_command_timeout_callback = 
	    STATIC_SYMBOL("CVS-COMMAND-TIMEOUT-CALLBACK",AB_package);
    SET_SYMBOL_FUNCTION(Qcvs_command_timeout_callback,
	    STATIC_FUNCTION(cvs_command_timeout_callback,NIL,FALSE,0,0));
    Qtext_string = STATIC_SYMBOL("TEXT-STRING",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    if (Local_source_code_control_buffer == UNBOUND)
	Local_source_code_control_buffer = Nil;
    if (Local_source_code_control_number_of_characters == UNBOUND)
	Local_source_code_control_number_of_characters = Nil;
    if (In_local_source_code_control_scope_p == UNBOUND)
	In_local_source_code_control_scope_p = Nil;
    string_constant_6 = STATIC_STRING("status");
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    string_constant_7 = STATIC_STRING("Status:");
    Qchecked_out_version = STATIC_SYMBOL("CHECKED-OUT-VERSION",AB_package);
    string_constant_8 = STATIC_STRING("Working revision:");
    Qnewest_version = STATIC_SYMBOL("NEWEST-VERSION",AB_package);
    string_constant_9 = STATIC_STRING("Repository revision:");
    Qbranch = STATIC_SYMBOL("BRANCH",AB_package);
    string_constant_10 = STATIC_STRING("Sticky Tag:");
    string_constant_11 = 
	    STATIC_STRING("Error while running \"cvs status ~NP\": ");
    string_constant_12 = STATIC_STRING("-v");
    string_constant_13 = STATIC_STRING("1.");
    string_constant_14 = STATIC_STRING("editors");
    QUnknown = STATIC_SYMBOL("Unknown",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnil,QUnknown);
    Qcvs = STATIC_SYMBOL("CVS",AB_package);
    QUp_to_date = STATIC_SYMBOL("Up-to-date",AB_package);
    QNeeds_sp_Patch = STATIC_SYMBOL("Needs Patch",AB_package);
    QNeeds_sp_Checkout = STATIC_SYMBOL("Needs Checkout",AB_package);
    string_constant_15 = STATIC_STRING("update");
    string_constant_16 = STATIC_STRING("-kb");
    string_constant_17 = STATIC_STRING("Updated ~NP");
    string_constant_18 = STATIC_STRING("Timed out updating ~NP");
    QLocally_sp_Modified = STATIC_SYMBOL("Locally Modified",AB_package);
    string_constant_19 = STATIC_STRING("Deleted ~NP");
    QNeeds_sp_Merge = STATIC_SYMBOL("Needs Merge",AB_package);
    string_constant_20 = 
	    string_append2(STATIC_STRING("Can\'t update ~NP because it has been edited locally, ~\n              and a newer revision has been committed. ~\n              Note that it will not be possible to commit ~NP f"),
	    STATIC_STRING("rom within G2."));
    string_constant_21 = 
	    STATIC_STRING("Can\'t update ~NP because \"cvs status\" is failing.");
    string_constant_22 = 
	    STATIC_STRING("Can\'t update ~NP, ~\n                                 because cvs is not installed or not in the PATH environment variable");
    string_constant_23 = 
	    STATIC_STRING("The source code control features of G2 will not be usable, ~\n                           because cvs is not installed or not in the PATH environment variable");
    string_constant_24 = 
	    STATIC_STRING("The source code control features of G2 work best with CVS version 1.10 ~\n                           or higher, but version 1.~d was found");
    string_constant_25 = 
	    STATIC_STRING("The source code control features of G2 will not be usable, ~\n               because cvs is not installed or not in the PATH environment variable");
    string_constant_26 = STATIC_STRING("use source code control for");
    string_constant_27 = 
	    STATIC_STRING("Note that a newer revision is available for ~NP. ~\n                       You might want to load it again using UPDATE BEFORE LOADING");
    string_constant_28 = 
	    STATIC_STRING("Note that there is now a newer revision for ~NP, ~\n                       but it will not be possible to merge it with ~NP");
    string_constant_29 = 
	    STATIC_STRING("Note that it will not be possible to check out ~NP ~\n                           for editing because ~A");
    string_constant_30 = 
	    string_append2(STATIC_STRING("Note that this file is under source code control. ~\n                   If cvs is installed on your machine, you might want ~\n                   to turn on source code control "),
	    STATIC_STRING("support, in the ~\n                   server-parameters system table."));
    list_constant_14 = STATIC_LIST((SI_Long)3L,QNeeds_sp_Patch,
	    QNeeds_sp_Checkout,QNeeds_sp_Merge);
    Status_codes_causing_source_code_control_problems_if_saved_p = 
	    list_constant_14;
    string_constant_31 = 
	    STATIC_STRING("Can\'t ~A ~NP because its directory is at top level");
    Krelative = STATIC_SYMBOL("RELATIVE",Pkeyword);
    array_constant_1 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    array_constant_3 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    string_constant_32 = 
	    STATIC_STRING("Can\'t ~A ~NP because its directory is not ~\n                      under source code control. ~\n                      Use \"cvs checkout\" on its directory first.");
    string_constant_33 = 
	    STATIC_STRING("Can\'t ~A ~NP because its CVS repository directory, ~A, ~\n                      specified by the CVS file ~NP, does not exist.");
    string_constant_34 = STATIC_STRING("add");
    string_constant_35 = 
	    STATIC_STRING("Can\'t commit ~NP because source code control does not run on VMS");
    string_constant_36 = 
	    STATIC_STRING("Can\'t commit ~NP because source code control is not enabled");
    string_constant_37 = STATIC_STRING("commit");
    string_constant_38 = 
	    STATIC_STRING("Can\'t commit ~NP because \"cvs status\" is failing.");
    string_constant_39 = 
	    STATIC_STRING("Can\'t commit ~NP because ~\n                     cvs is not installed or not in the PATH environment variable");
    string_constant_40 = 
	    STATIC_STRING("Can\'t commit ~NP because someone else has committed a different version");
    string_constant_41 = STATIC_STRING("g2_commit_log");
    string_constant_42 = STATIC_STRING("-F");
    string_constant_43 = STATIC_STRING("Committed ~NP.");
    string_constant_44 = STATIC_STRING("unedit");
    string_constant_45 = STATIC_STRING("Timed out committing ~NP");
    string_constant_46 = STATIC_STRING("~A is already being edited by ~L,&");
    string_constant_47 = 
	    STATIC_STRING("~A is already being edited in a different directory");
    string_constant_48 = STATIC_STRING("edit");
    string_constant_49 = 
	    STATIC_STRING("~A does not want to make edits to ~NP");
    if (Result_of_ask_user_about_checking_pathname_out_for_editing == UNBOUND)
	Result_of_ask_user_about_checking_pathname_out_for_editing = Nil;
    if (Return_from_ask_user_about_checking_pathname_out_for_editing_p == 
	    UNBOUND)
	Return_from_ask_user_about_checking_pathname_out_for_editing_p = Nil;
    if (Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing 
	    == UNBOUND)
	Workstations_with_their_stacks_for_ask_user_about_checking_pathname_out_for_editing 
		= Nil;
    if (Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing 
	    == UNBOUND)
	Ui_client_interfaces_for_ask_user_about_checking_pathname_out_for_editing 
		= Nil;
    array_constant_4 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qexit_from_ask_user_about_checking_pathname_out_for_editing = 
	    STATIC_SYMBOL("EXIT-FROM-ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING",
	    AB_package);
    Qcheck_out_for_editing_question = 
	    STATIC_SYMBOL("CHECK-OUT-FOR-EDITING-QUESTION",AB_package);
    Qyes = STATIC_SYMBOL("YES",AB_package);
    Qask_user_about_checking_out_a_file = 
	    STATIC_SYMBOL("ASK-USER-ABOUT-CHECKING-OUT-A-FILE",AB_package);
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    Qt2_continuation_for_ask_user_about_checking_pathname_out_for_editing 
	    = 
	    STATIC_SYMBOL("T2-CONTINUATION-FOR-ASK-USER-ABOUT-CHECKING-PATHNAME-OUT-FOR-EDITING",
	    AB_package);
    string_constant_50 = 
	    STATIC_STRING("Do you want to check out ~NP for editing\?");
    SET_SYMBOL_FUNCTION(Qt2_continuation_for_ask_user_about_checking_pathname_out_for_editing,
	    STATIC_FUNCTION(t2_continuation_for_ask_user_about_checking_pathname_out_for_editing,
	    NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qexit_from_ask_user_about_checking_pathname_out_for_editing,
	    STATIC_FUNCTION(exit_from_ask_user_about_checking_pathname_out_for_editing,
	    NIL,FALSE,1,1));
    Qscc_update = STATIC_SYMBOL("SCC-UPDATE",AB_package);
    Qscc_edit = STATIC_SYMBOL("SCC-EDIT",AB_package);
    Qscc_unedit = STATIC_SYMBOL("SCC-UNEDIT",AB_package);
    Qscc_revert = STATIC_SYMBOL("SCC-REVERT",AB_package);
    string_constant_51 = STATIC_STRING("revert");
    Qscc_commit = STATIC_SYMBOL("SCC-COMMIT",AB_package);
    string_constant_52 = 
	    STATIC_STRING("Can\'t ~a ~NP because source code control does not run on VMS");
    string_constant_53 = 
	    STATIC_STRING("Can\'t perform the source code control operation ~a on ~NP ~\n                because it is not under source code control");
    string_constant_54 = 
	    STATIC_STRING("Can\'t perform the source control operation ~a on ~NP ~\n                because source code control is not enabled");
    Qcurrent_file_for_module = STATIC_SYMBOL("CURRENT-FILE-FOR-MODULE",
	    AB_package);
    Qreason_module_is_not_editable = 
	    STATIC_SYMBOL("REASON-MODULE-IS-NOT-EDITABLE",AB_package);
    Qmodule_file_is_read_only = STATIC_SYMBOL("MODULE-FILE-IS-READ-ONLY",
	    AB_package);
    Qsource_code_control_for_module_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-FOR-MODULE-FILE",AB_package);
    Qmodule_file_is_checked_out_for_writing_by_current_user = 
	    STATIC_SYMBOL("MODULE-FILE-IS-CHECKED-OUT-FOR-WRITING-BY-CURRENT-USER",
	    AB_package);
    Qusers_currently_having_module_file_checked_out = 
	    STATIC_SYMBOL("USERS-CURRENTLY-HAVING-MODULE-FILE-CHECKED-OUT",
	    AB_package);
    Qsource_code_control_status_for_module_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-STATUS-FOR-MODULE-FILE",
	    AB_package);
    Qversion_of_checked_out_module_file = 
	    STATIC_SYMBOL("VERSION-OF-CHECKED-OUT-MODULE-FILE",AB_package);
    Qnewest_version_of_module_file = 
	    STATIC_SYMBOL("NEWEST-VERSION-OF-MODULE-FILE",AB_package);
    Qbranch_of_checked_out_module_file = 
	    STATIC_SYMBOL("BRANCH-OF-CHECKED-OUT-MODULE-FILE",AB_package);
    Qg2_update_saving_parameters_status_attributes = 
	    STATIC_SYMBOL("G2-UPDATE-SAVING-PARAMETERS-STATUS-ATTRIBUTES",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_update_saving_parameters_status_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_update_saving_parameters_status_attributes,
	    STATIC_FUNCTION(g2_update_saving_parameters_status_attributes,
	    NIL,FALSE,0,0));
    array_constant_6 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)57344L);
    Qstatus_text_or_none = STATIC_SYMBOL("STATUS-TEXT-OR-NONE",AB_package);
    Qwrite_status_text_or_none_from_slot = 
	    STATIC_SYMBOL("WRITE-STATUS-TEXT-OR-NONE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_status_text_or_none_from_slot,
	    STATIC_FUNCTION(write_status_text_or_none_from_slot,NIL,FALSE,
	    2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qstatus_text_or_none,
	    SYMBOL_FUNCTION(Qwrite_status_text_or_none_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_15 = STATIC_CONS(Qno_item,Qnil);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,list_constant_15);
    set_property_value_function(get_symbol_properties_function(Qstatus_text_or_none),
	    Qtype_specification_simple_expansion,list_constant_16);
    define_type_specification_explicit_complex_type(Qstatus_text_or_none,
	    list_constant_16);
    status_text_or_none_evaluation_getter_1 = 
	    STATIC_FUNCTION(status_text_or_none_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstatus_text_or_none,
	    status_text_or_none_evaluation_getter_1);
    Qsource_code_control_name = STATIC_SYMBOL("SOURCE-CODE-CONTROL-NAME",
	    AB_package);
    Qwrite_source_code_control_name_from_slot = 
	    STATIC_SYMBOL("WRITE-SOURCE-CODE-CONTROL-NAME-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_source_code_control_name_from_slot,
	    STATIC_FUNCTION(write_source_code_control_name_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsource_code_control_name,
	    SYMBOL_FUNCTION(Qwrite_source_code_control_name_from_slot),
	    Qslot_value_writer);
    list_constant_17 = STATIC_CONS(list_constant_15,Qnil);
    list_constant_18 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_17);
    set_property_value_function(get_symbol_properties_function(Qsource_code_control_name),
	    Qtype_specification_simple_expansion,list_constant_18);
    define_type_specification_explicit_complex_type(Qsource_code_control_name,
	    list_constant_18);
    source_code_control_name_evaluation_getter_1 = 
	    STATIC_FUNCTION(source_code_control_name_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsource_code_control_name,
	    source_code_control_name_evaluation_getter_1);
    array_constant_7 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Quser_name_sequence = STATIC_SYMBOL("USER-NAME-SEQUENCE",AB_package);
    Qwrite_user_name_sequence_from_slot = 
	    STATIC_SYMBOL("WRITE-USER-NAME-SEQUENCE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_user_name_sequence_from_slot,
	    STATIC_FUNCTION(write_user_name_sequence_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Quser_name_sequence,
	    SYMBOL_FUNCTION(Qwrite_user_name_sequence_from_slot),
	    Qslot_value_writer);
    list_constant_19 = STATIC_CONS(Qsequence,Qnil);
    list_constant_20 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_19,list_constant_17);
    set_property_value_function(get_symbol_properties_function(Quser_name_sequence),
	    Qtype_specification_simple_expansion,list_constant_20);
    define_type_specification_explicit_complex_type(Quser_name_sequence,
	    list_constant_20);
    user_name_sequence_evaluation_getter_1 = 
	    STATIC_FUNCTION(user_name_sequence_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Quser_name_sequence,
	    user_name_sequence_evaluation_getter_1);
    string_constant_55 = STATIC_STRING("yes");
    string_constant_56 = STATIC_STRING("no");
    Qreadonly_yes_or_no = STATIC_SYMBOL("READONLY-YES-OR-NO",AB_package);
    Qwrite_readonly_yes_or_no_from_slot = 
	    STATIC_SYMBOL("WRITE-READONLY-YES-OR-NO-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_readonly_yes_or_no_from_slot,
	    STATIC_FUNCTION(write_readonly_yes_or_no_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qreadonly_yes_or_no,
	    SYMBOL_FUNCTION(Qwrite_readonly_yes_or_no_from_slot),
	    Qslot_value_writer);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qreadonly_yes_or_no),
	    Qtype_specification_simple_expansion,Qtruth_value);
    define_type_specification_explicit_complex_type(Qreadonly_yes_or_no,
	    Qtruth_value);
    readonly_yes_or_no_evaluation_getter_1 = 
	    STATIC_FUNCTION(readonly_yes_or_no_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qreadonly_yes_or_no,
	    readonly_yes_or_no_evaluation_getter_1);
    Qjournal_and_backup_parameters = 
	    STATIC_SYMBOL("JOURNAL-AND-BACKUP-PARAMETERS",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)210L);
    mutate_global_property(Qjournal_and_backup_parameters,
	    CONS(Qsaving_parameters,temp),Qsubstitute_class_and_kb_flags);
    Qenable_journalling = STATIC_SYMBOL("ENABLE-JOURNALLING",AB_package);
    Qput_enable_journalling_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-ENABLE-JOURNALLING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_enable_journalling_where_slot_is_absent,
	    STATIC_FUNCTION(put_enable_journalling_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qenable_journalling,
	    SYMBOL_FUNCTION(Qput_enable_journalling_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qpathname_format = STATIC_SYMBOL("PATHNAME-FORMAT",AB_package);
    Qput_pathname_format_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PATHNAME-FORMAT-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_pathname_format_where_slot_is_absent,
	    STATIC_FUNCTION(put_pathname_format_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qpathname_format,
	    SYMBOL_FUNCTION(Qput_pathname_format_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnumber_of_backup_files = STATIC_SYMBOL("NUMBER-OF-BACKUP-FILES",
	    AB_package);
    Qput_number_of_backup_files_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NUMBER-OF-BACKUP-FILES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_number_of_backup_files_where_slot_is_absent,
	    STATIC_FUNCTION(put_number_of_backup_files_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnumber_of_backup_files,
	    SYMBOL_FUNCTION(Qput_number_of_backup_files_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qjournalling_status = STATIC_SYMBOL("JOURNALLING-STATUS",AB_package);
    Qput_journalling_status_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-JOURNALLING-STATUS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_journalling_status_where_slot_is_absent,
	    STATIC_FUNCTION(put_journalling_status_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qjournalling_status,
	    SYMBOL_FUNCTION(Qput_journalling_status_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qjournal_priority = STATIC_SYMBOL("JOURNAL-PRIORITY",AB_package);
    Qdefault_priority_for_runtime_saving = 
	    STATIC_SYMBOL("DEFAULT-PRIORITY-FOR-RUNTIME-SAVING",AB_package);
    alias_slot_name(3,Qjournal_priority,
	    Qdefault_priority_for_runtime_saving,Qnil);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_10 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)41L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)42L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)43L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)44L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)45L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)126L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)54L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)55L,(SI_Long)57344L);
    Qclear_text_history = STATIC_SYMBOL("CLEAR-TEXT-HISTORY",AB_package);
    Qwrite_clear_text_history_from_slot = 
	    STATIC_SYMBOL("WRITE-CLEAR-TEXT-HISTORY-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_clear_text_history_from_slot,
	    STATIC_FUNCTION(write_clear_text_history_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qclear_text_history,
	    SYMBOL_FUNCTION(Qwrite_clear_text_history_from_slot),
	    Qslot_value_writer);
    list_constant_21 = STATIC_CONS(FIX((SI_Long)16L),Qnil);
    list_constant_1 = STATIC_LIST_STAR((SI_Long)4L,FIX((SI_Long)2L),
	    FIX((SI_Long)4L),FIX((SI_Long)8L),list_constant_21);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)4L,Qattribute_name,Quuid,Qvalue,
	    Qtext);
    Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type = 
	    STATIC_SYMBOL("TYPE-IS-SUB-ELEMENT-OF-G2-ATTRIBUTE-AND-VALUE-IS-ATTRIBUTE-OF-TYPE",
	    AB_package);
    string_constant_57 = 
	    STATIC_STRING("type is sub element of g2 attribute and value is attribute of type");
    Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type = 
	    STATIC_SYMBOL("TYPE-IS-SUB-ELEMENT-OF-G2-ATTRIBUTE-AND-VALUE-IS-CONTENTS-OF-TYPE",
	    AB_package);
    string_constant_58 = 
	    STATIC_STRING("type is sub element of g2 attribute and value is contents of type");
    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute 
	    = 
	    STATIC_SYMBOL("TYPE-IS-ATTRIBUTE-OF-G2-ATTRIBUTE-AND-VALUE-IS-CONTENTS-OF-G2-ATTRIBUTE",
	    AB_package);
    string_constant_59 = 
	    STATIC_STRING("type is attribute of g2 attribute and value is contents of g2 attribute");
    Qxml_primitive_value_style = STATIC_SYMBOL("XML-PRIMITIVE-VALUE-STYLE",
	    AB_package);
    Qwrite_xml_primitive_value_style_from_slot = 
	    STATIC_SYMBOL("WRITE-XML-PRIMITIVE-VALUE-STYLE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_xml_primitive_value_style_from_slot,
	    STATIC_FUNCTION(write_xml_primitive_value_style_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qxml_primitive_value_style,
	    SYMBOL_FUNCTION(Qwrite_xml_primitive_value_style_from_slot),
	    Qslot_value_writer);
    Qcompile_xml_primitive_value_style_for_slot = 
	    STATIC_SYMBOL("COMPILE-XML-PRIMITIVE-VALUE-STYLE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_xml_primitive_value_style_for_slot,
	    STATIC_FUNCTION(compile_xml_primitive_value_style_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qxml_primitive_value_style,
	    SYMBOL_FUNCTION(Qcompile_xml_primitive_value_style_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qxml_primitive_value_style,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_22 = 
	    STATIC_CONS(Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type,
	    Qnil);
    list_constant_39 = STATIC_CONS(Qxml_primitive_value_style,
	    list_constant_22);
    list_constant_23 = 
	    STATIC_CONS(Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type,
	    Qnil);
    list_constant_40 = STATIC_CONS(Qxml_primitive_value_style,
	    list_constant_23);
    list_constant_24 = 
	    STATIC_CONS(Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute,
	    Qnil);
    list_constant_41 = STATIC_CONS(Qxml_primitive_value_style,
	    list_constant_24);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qquote,Qtype);
    Qis = STATIC_SYMBOL("IS",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qquote,Qis);
    Qsub = STATIC_SYMBOL("SUB",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qquote,Qsub);
    Qelement = STATIC_SYMBOL("ELEMENT",AB_package);
    list_constant_29 = STATIC_LIST((SI_Long)2L,Qquote,Qelement);
    Qof = STATIC_SYMBOL("OF",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qof);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qquote,Qg2);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qquote,Qattribute);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qquote,Qand);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qquote,Qvalue);
    list_constant_34 = STATIC_LIST((SI_Long)2L,list_constant_25,
	    list_constant_26);
    list_constant_35 = STATIC_LIST_STAR((SI_Long)12L,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29,
	    list_constant_25,list_constant_30,list_constant_31,
	    list_constant_32,list_constant_33,list_constant_27,
	    list_constant_31,list_constant_34);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type,
	    list_constant_35,list_constant_22);
    Qcontents = STATIC_SYMBOL("CONTENTS",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qquote,Qcontents);
    list_constant_37 = STATIC_LIST_STAR((SI_Long)12L,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29,
	    list_constant_25,list_constant_30,list_constant_31,
	    list_constant_32,list_constant_33,list_constant_27,
	    list_constant_36,list_constant_34);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type,
	    list_constant_37,list_constant_23);
    list_constant_38 = STATIC_LIST((SI_Long)13L,list_constant_26,
	    list_constant_27,list_constant_31,list_constant_25,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_33,list_constant_27,list_constant_36,
	    list_constant_25,list_constant_30,list_constant_31);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,
	    Qtype_is_attribute_of_g2_attribute_and_value_is_contents_of_g2_attribute,
	    list_constant_38,list_constant_24);
    list_constant_45 = STATIC_LIST((SI_Long)6L,list_constant_39,
	    list_constant_40,list_constant_41,list_constant_42,
	    list_constant_43,list_constant_44);
    add_grammar_rules_function(list_constant_45);
    set_property_value_function(get_symbol_properties_function(Qxml_primitive_value_style),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)4L,Qmember,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_attribute_of_type,
	    Qtype_is_sub_element_of_g2_attribute_and_value_is_contents_of_type,
	    list_constant_24);
    define_type_specification_explicit_complex_type(Qxml_primitive_value_style,
	    list_constant_4);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qxml_primitive_value_style);
    xml_primitive_value_style_evaluation_setter_1 = 
	    STATIC_FUNCTION(xml_primitive_value_style_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qxml_primitive_value_style,
	    xml_primitive_value_style_evaluation_setter_1);
    xml_primitive_value_style_evaluation_getter_1 = 
	    STATIC_FUNCTION(xml_primitive_value_style_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qxml_primitive_value_style,
	    xml_primitive_value_style_evaluation_getter_1);
    string_constant_124 = 
	    STATIC_STRING("1p1n83-Fpy1n83-vLy1m9k83vy83-vMy1mln1n83-vLy1m1m9k837gy1m9k83fiy83-JWy1n83-vLy1o1m9k830Iy1m9k9l1m9k837gy1m9k83fiy83Boy1n83-vMy1o");
    string_constant_125 = 
	    STATIC_STRING("1m9k9m1m9k837ey1m9k8331y1m9k83-K+y9m1n83-vMy1q1m9k830Iy1m9k9l1m9k9m1m9k837ey1m9k8331y1m9k83-K+y83-Rky");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qwarn);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_124,
	    string_constant_125)));
    string_constant_126 = STATIC_STRING("1m1m83Fiy1m9k83Py1m83Fiy83-Fpy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_126));
    Qallow_changes = STATIC_SYMBOL("ALLOW-CHANGES",AB_package);
    string_constant_60 = STATIC_STRING("allow changes");
    string_constant_61 = STATIC_STRING("do not allow changes");
    string_constant_62 = STATIC_STRING(", ");
    string_constant_63 = STATIC_STRING("warn when edit attempted");
    string_constant_64 = STATIC_STRING("do not warn when edit attempted");
    Qunsavable_change_protection_specification = 
	    STATIC_SYMBOL("UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION",
	    AB_package);
    Qwrite_unsavable_change_protection_specification_from_slot = 
	    STATIC_SYMBOL("WRITE-UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_unsavable_change_protection_specification_from_slot,
	    STATIC_FUNCTION(write_unsavable_change_protection_specification_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qunsavable_change_protection_specification,
	    SYMBOL_FUNCTION(Qwrite_unsavable_change_protection_specification_from_slot),
	    Qslot_value_writer);
    string_constant_65 = STATIC_STRING("default");
    Qunsavable_change_protection = 
	    STATIC_SYMBOL("UNSAVABLE-CHANGE-PROTECTION",AB_package);
    Qwrite_unsavable_change_protection_from_slot = 
	    STATIC_SYMBOL("WRITE-UNSAVABLE-CHANGE-PROTECTION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_unsavable_change_protection_from_slot,
	    STATIC_FUNCTION(write_unsavable_change_protection_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qunsavable_change_protection,
	    SYMBOL_FUNCTION(Qwrite_unsavable_change_protection_from_slot),
	    Qslot_value_writer);
    Qcompile_unsavable_change_protection_specification_for_slot = 
	    STATIC_SYMBOL("COMPILE-UNSAVABLE-CHANGE-PROTECTION-SPECIFICATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_unsavable_change_protection_specification_for_slot,
	    STATIC_FUNCTION(compile_unsavable_change_protection_specification_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qunsavable_change_protection_specification,
	    SYMBOL_FUNCTION(Qcompile_unsavable_change_protection_specification_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qunsavable_change_protection_specification,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_unsavable_change_protection_for_slot = 
	    STATIC_SYMBOL("COMPILE-UNSAVABLE-CHANGE-PROTECTION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_unsavable_change_protection_for_slot,
	    STATIC_FUNCTION(compile_unsavable_change_protection_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qunsavable_change_protection,
	    SYMBOL_FUNCTION(Qcompile_unsavable_change_protection_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qunsavable_change_protection,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_46 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qunsavable_change_protection_specification),
	    Qtype_specification_simple_expansion,list_constant_46);
    list_constant_47 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_48 = STATIC_CONS(Qallow_changes,list_constant_47);
    list_constant_49 = STATIC_CONS(Qwarn,list_constant_47);
    list_constant_50 = STATIC_LIST((SI_Long)2L,list_constant_48,
	    list_constant_49);
    list_constant_51 = STATIC_LIST((SI_Long)3L,Qand,Qallow_changes,Qwarn);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_50,list_constant_51);
    define_type_specification_explicit_complex_type(Qunsavable_change_protection_specification,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qunsavable_change_protection_specification);
    Qdo_not_allow_changes = STATIC_SYMBOL("DO-NOT-ALLOW-CHANGES",AB_package);
    Qdo_not_warn = STATIC_SYMBOL("DO-NOT-WARN",AB_package);
    unsavable_change_protection_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(unsavable_change_protection_specification_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qunsavable_change_protection_specification,
	    unsavable_change_protection_specification_evaluation_setter_1);
    unsavable_change_protection_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(unsavable_change_protection_specification_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qunsavable_change_protection_specification,
	    unsavable_change_protection_specification_evaluation_getter_1);
    list_constant_52 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_15,Qnil);
    set_property_value_function(get_symbol_properties_function(Qunsavable_change_protection),
	    Qtype_specification_simple_expansion,list_constant_52);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_15,
	    list_constant_5);
    define_type_specification_explicit_complex_type(Qunsavable_change_protection,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qunsavable_change_protection);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    unsavable_change_protection_evaluation_setter_1 = 
	    STATIC_FUNCTION(unsavable_change_protection_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qunsavable_change_protection,
	    unsavable_change_protection_evaluation_setter_1);
    unsavable_change_protection_evaluation_getter_1 = 
	    STATIC_FUNCTION(unsavable_change_protection_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qunsavable_change_protection,
	    unsavable_change_protection_evaluation_getter_1);
    Qdefault_unsavable_change_protection = 
	    STATIC_SYMBOL("DEFAULT-UNSAVABLE-CHANGE-PROTECTION",AB_package);
    Qall_permanently_changed_things_are_marked = 
	    STATIC_SYMBOL("ALL-PERMANENTLY-CHANGED-THINGS-ARE-MARKED",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_permanently_changed_things_are_marked,
	    All_permanently_changed_things_are_marked);
    record_system_variable(Qall_permanently_changed_things_are_marked,
	    Qkb_save3,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_66 = STATIC_STRING("ok to write backup or journal");
    string_constant_67 = 
	    STATIC_STRING("cannot write backup or journal until after a kb is saved");
    Qwrite_journalling_status_from_slot = 
	    STATIC_SYMBOL("WRITE-JOURNALLING-STATUS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_journalling_status_from_slot,
	    STATIC_FUNCTION(write_journalling_status_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qjournalling_status,
	    SYMBOL_FUNCTION(Qwrite_journalling_status_from_slot),
	    Qslot_value_writer);
    string_constant_68 = STATIC_STRING("none");
    Qbasis_kb = STATIC_SYMBOL("BASIS-KB",AB_package);
    Qwrite_basis_kb_from_slot = STATIC_SYMBOL("WRITE-BASIS-KB-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_basis_kb_from_slot,
	    STATIC_FUNCTION(write_basis_kb_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qbasis_kb,
	    SYMBOL_FUNCTION(Qwrite_basis_kb_from_slot),Qslot_value_writer);
    list_constant_53 = STATIC_CONS(Qtext,Qnil);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_15,list_constant_53);
    set_property_value_function(get_symbol_properties_function(Qbasis_kb),
	    Qtype_specification_simple_expansion,list_constant_54);
    define_type_specification_explicit_complex_type(Qbasis_kb,
	    list_constant_54);
    basis_kb_evaluation_getter_1 = 
	    STATIC_FUNCTION(basis_kb_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qbasis_kb,
	    basis_kb_evaluation_getter_1);
    Qfilename_of_basis_kb = STATIC_SYMBOL("FILENAME-OF-BASIS-KB",AB_package);
    Qwrite_filename_of_basis_kb_from_slot = 
	    STATIC_SYMBOL("WRITE-FILENAME-OF-BASIS-KB-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_filename_of_basis_kb_from_slot,
	    STATIC_FUNCTION(write_filename_of_basis_kb_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qfilename_of_basis_kb,
	    SYMBOL_FUNCTION(Qwrite_filename_of_basis_kb_from_slot),
	    Qslot_value_writer);
    Qfile_name_of_basis_kb = STATIC_SYMBOL("FILE-NAME-OF-BASIS-KB",AB_package);
    set_property_value_function(get_symbol_properties_function(Qfile_name_of_basis_kb),
	    Qtype_specification_simple_expansion,list_constant_54);
    define_type_specification_explicit_complex_type(Qfile_name_of_basis_kb,
	    list_constant_54);
    file_name_of_basis_kb_evaluation_getter_1 = 
	    STATIC_FUNCTION(file_name_of_basis_kb_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfile_name_of_basis_kb,
	    file_name_of_basis_kb_evaluation_getter_1);
    Qinstall_system_table_for_saving_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-SAVING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_saving_parameters,
	    STATIC_FUNCTION(install_system_table_for_saving_parameters,NIL,
	    FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_saving_parameters);
    set_get(Qsaving_parameters,Qinstall_system_table,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qsaving_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_saving_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-SAVING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_saving_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_saving_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_saving_parameters);
    set_get(Qsaving_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qsaving_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qprogress_through_file = STATIC_SYMBOL("PROGRESS-THROUGH-FILE",AB_package);
    Qstatus_of_file_progress_qm = 
	    STATIC_SYMBOL("STATUS-OF-FILE-PROGRESS\?",AB_package);
    Qsave_kb_internal = STATIC_SYMBOL("SAVE-KB-INTERNAL",AB_package);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    Qok_kb_save = STATIC_SYMBOL("OK-KB-SAVE",AB_package);
    Qbackup = STATIC_SYMBOL("BACKUP",AB_package);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    SET_SYMBOL_FUNCTION(Qsave_kb,STATIC_FUNCTION(save_kb,NIL,TRUE,1,4));
    Qab_continue = STATIC_SYMBOL("CONTINUE",AB_package);
    Qfinish = STATIC_SYMBOL("FINISH",AB_package);
    string_constant_69 = STATIC_STRING("G2 could not open the file ~s:  ~a.");
    string_constant_70 = 
	    STATIC_STRING("Problem associating stream with file \"~a\".");
    Qkb_save_with_runtime_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTIME-DATA",
	    AB_package);
    Qruntime_data_only = STATIC_SYMBOL("RUNTIME-DATA-ONLY",AB_package);
    list_constant_55 = STATIC_CONS(Qnil,Qnil);
    list_constant_56 = STATIC_LIST_STAR((SI_Long)3L,Qnil,Qnil,
	    list_constant_55);
    list_constant_9 = STATIC_CONS(list_constant_56,Qnil);
    array_constant_12 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    Qmodule_uses_crlf_p = STATIC_SYMBOL("MODULE-USES-CRLF-P",AB_package);
    Qwin32 = STATIC_SYMBOL("WIN32",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qread_only = STATIC_SYMBOL("READ-ONLY",AB_package);
    Qunopened = STATIC_SYMBOL("UNOPENED",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qdialog_workspace_frame_style = 
	    STATIC_SYMBOL("DIALOG-WORKSPACE-FRAME-STYLE",AB_package);
    Qdefault_workspace_frame_style = 
	    STATIC_SYMBOL("DEFAULT-WORKSPACE-FRAME-STYLE",AB_package);
    string_constant_71 = 
	    STATIC_STRING("Warning: Cannot save ~a~a as ~s because it is ~\n       read-only.  It is being skipped.");
    string_constant_72 = STATIC_STRING("module ");
    string_constant_73 = STATIC_STRING("this KB ");
    Qfuncall_to_write_to_kb_save_stream = 
	    STATIC_SYMBOL("FUNCALL-TO-WRITE-TO-KB-SAVE-STREAM",AB_package);
    Qopen_kb_save_or_backup_stream = 
	    STATIC_SYMBOL("OPEN-KB-SAVE-OR-BACKUP-STREAM",AB_package);
    Qerror_writing_file_1 = STATIC_SYMBOL("ERROR-WRITING-FILE-1",AB_package);
    Qcontinue_current_kb_save = STATIC_SYMBOL("CONTINUE-CURRENT-KB-SAVE",
	    AB_package);
    Qerror_writing_file_2 = STATIC_SYMBOL("ERROR-WRITING-FILE-2",AB_package);
    Qfinish_current_kb_save = STATIC_SYMBOL("FINISH-CURRENT-KB-SAVE",
	    AB_package);
    Qerror_writing_file_3 = STATIC_SYMBOL("ERROR-WRITING-FILE-3",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)6L,
	    Qopen_kb_save_or_backup_stream,Qerror_writing_file_1,
	    Qcontinue_current_kb_save,Qerror_writing_file_2,
	    Qfinish_current_kb_save,Qerror_writing_file_3);
    Qerror_writing_file = STATIC_SYMBOL("ERROR-WRITING-FILE",AB_package);
    SET_SYMBOL_FUNCTION(Qfuncall_to_write_to_kb_save_stream,
	    STATIC_FUNCTION(funcall_to_write_to_kb_save_stream,NIL,TRUE,2,3));
    Qaborted = STATIC_SYMBOL("ABORTED",AB_package);
    SET_SYMBOL_FUNCTION(Qopen_kb_save_or_backup_stream,
	    STATIC_FUNCTION(open_kb_save_or_backup_stream,NIL,FALSE,0,0));
    string_constant_74 = STATIC_STRING("#include \"bytecode.h\"");
    string_constant_75 = STATIC_STRING("static Object *byte_code_constants;");
    string_constant_76 = STATIC_STRING("static Object **byte_code_variables;");
    string_constant_77 = STATIC_STRING("static fn_type *byte_code_functions;");
    string_constant_78 = 
	    STATIC_STRING("static fn_type *byte_code_run_time_functions;");
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qclear_text = STATIC_SYMBOL("CLEAR-TEXT",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcontinue_current_kb_save_or_backup = 
	    STATIC_SYMBOL("CONTINUE-CURRENT-KB-SAVE-OR-BACKUP",AB_package);
    Qcontinuation_task_for_current_backup = 
	    STATIC_SYMBOL("CONTINUATION-TASK-FOR-CURRENT-BACKUP",AB_package);
    Qterminate_kb_save_or_backup = 
	    STATIC_SYMBOL("TERMINATE-KB-SAVE-OR-BACKUP",AB_package);
    SET_SYMBOL_FUNCTION(Qcontinue_current_kb_save_or_backup,
	    STATIC_FUNCTION(continue_current_kb_save_or_backup,NIL,FALSE,1,1));
    if (Save_only_if_interrupting_qm == UNBOUND)
	Save_only_if_interrupting_qm = Nil;
    if (Use_minimal_time_slice_for_continue_current_kb_save_p == UNBOUND)
	Use_minimal_time_slice_for_continue_current_kb_save_p = Nil;
    if (Dont_cerror_for_slot_changes_while_on_window_qm == UNBOUND)
	Dont_cerror_for_slot_changes_while_on_window_qm = Nil;
    Qcontinue_current_kb_save_failure = 
	    STATIC_SYMBOL("CONTINUE-CURRENT-KB-SAVE-FAILURE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcontinue_current_kb_save_failure,
	    Continue_current_kb_save_failure);
    list_constant_57 = STATIC_CONS(Qcontinue_current_kb_save_failure,Qnil);
    if (Continue_current_kb_save_failure == UNBOUND)
	Continue_current_kb_save_failure = list_constant_57;
    Qwrite_clear_text_kb = STATIC_SYMBOL("WRITE-CLEAR-TEXT-KB",AB_package);
    Qwrite_kb_per_traversal_state_a_little = 
	    STATIC_SYMBOL("WRITE-KB-PER-TRAVERSAL-STATE-A-LITTLE",AB_package);
    Qwrite_deletions_for_saving_a_little = 
	    STATIC_SYMBOL("WRITE-DELETIONS-FOR-SAVING-A-LITTLE",AB_package);
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qcontinue_current_kb_save,
	    STATIC_FUNCTION(continue_current_kb_save,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qwrite_deletions_for_saving_a_little,
	    STATIC_FUNCTION(write_deletions_for_saving_a_little,NIL,FALSE,
	    0,0));
    Qjournal = STATIC_SYMBOL("JOURNAL",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_kb_per_traversal_state_a_little,
	    STATIC_FUNCTION(write_kb_per_traversal_state_a_little,NIL,
	    FALSE,0,0));
    Ktop_level_workspaces = STATIC_SYMBOL("TOP-LEVEL-WORKSPACES",Pkeyword);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qwrite_kb_traversal_state_node = 
	    STATIC_SYMBOL("WRITE-KB-TRAVERSAL-STATE-NODE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_kb_traversal_state_node,
	    STATIC_FUNCTION(write_kb_traversal_state_node,NIL,FALSE,2,2));
    string_constant_79 = 
	    STATIC_STRING("DLLEXPORT void do_initialize_compiled_kb_");
    string_constant_80 = STATIC_STRING("(args)");
    string_constant_81 = STATIC_STRING("  void **args;");
    string_constant_82 = 
	    STATIC_STRING("  byte_code_constants = (Object *)(args[0]);");
    string_constant_83 = 
	    STATIC_STRING("  byte_code_variables = (Object **)(args[1]);");
    string_constant_84 = 
	    STATIC_STRING("  byte_code_functions = (fn_type *)(args[2]);");
    string_constant_85 = 
	    STATIC_STRING("  byte_code_run_time_functions = (fn_type *)(args[3]);");
    string_constant_86 = STATIC_STRING("  add_compiled_function(fn");
    string_constant_87 = STATIC_STRING(");");
    Qfinish_current_kb_save_failure = 
	    STATIC_SYMBOL("FINISH-CURRENT-KB-SAVE-FAILURE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfinish_current_kb_save_failure,
	    Finish_current_kb_save_failure);
    list_constant_58 = STATIC_CONS(Qfinish_current_kb_save_failure,Qnil);
    if (Finish_current_kb_save_failure == UNBOUND)
	Finish_current_kb_save_failure = list_constant_58;
    Qclosing_compiled = STATIC_SYMBOL("CLOSING-COMPILED",AB_package);
    Qclose_current_compiled_kb_save_stream = 
	    STATIC_SYMBOL("CLOSE-CURRENT-COMPILED-KB-SAVE-STREAM",AB_package);
    Qclosed_compiled = STATIC_SYMBOL("CLOSED-COMPILED",AB_package);
    Qfinish_current_kb_save_1 = STATIC_SYMBOL("FINISH-CURRENT-KB-SAVE-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfinish_current_kb_save,
	    STATIC_FUNCTION(finish_current_kb_save,NIL,FALSE,0,0));
    string_constant_88 = 
	    STATIC_STRING("DLLEXPORT long initialize_compiled_kb(args)");
    string_constant_89 = STATIC_STRING("  if (!check_version(");
    string_constant_90 = STATIC_STRING(")) return 0;");
    string_constant_91 = STATIC_STRING("  do_initialize_compiled_kb_");
    string_constant_92 = STATIC_STRING("(args);");
    string_constant_93 = STATIC_STRING("  return 1;");
    string_constant_94 = STATIC_STRING("void dummy () {");
    string_constant_95 = 
	    STATIC_STRING("  printf(\"Don\'t know why, but if this isn\'t here, dlopen bombs out on the sun4\");");
    SET_SYMBOL_FUNCTION(Qclose_current_compiled_kb_save_stream,
	    STATIC_FUNCTION(close_current_compiled_kb_save_stream,NIL,
	    FALSE,0,0));
    Qclosing = STATIC_SYMBOL("CLOSING",AB_package);
    Qclose_current_kb_save_stream = 
	    STATIC_SYMBOL("CLOSE-CURRENT-KB-SAVE-STREAM",AB_package);
    SET_SYMBOL_FUNCTION(Qclose_current_kb_save_stream,
	    STATIC_FUNCTION(close_current_kb_save_stream,NIL,FALSE,0,0));
    Qclose_failed = STATIC_SYMBOL("CLOSE-FAILED",AB_package);
    Qrename_failed = STATIC_SYMBOL("RENAME-FAILED",AB_package);
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qfailed_to_write_items = STATIC_SYMBOL("FAILED-TO-WRITE-ITEMS",AB_package);
    Qwrite_final_plist_for_current_kb_save = 
	    STATIC_SYMBOL("WRITE-FINAL-PLIST-FOR-CURRENT-KB-SAVE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_final_plist_for_current_kb_save,
	    STATIC_FUNCTION(write_final_plist_for_current_kb_save,NIL,
	    FALSE,0,0));
    Qflush_kb_write_buffer = STATIC_SYMBOL("FLUSH-KB-WRITE-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qflush_kb_write_buffer,
	    STATIC_FUNCTION(flush_kb_write_buffer,NIL,FALSE,0,0));
    Qflush_compiled_kb_write_buffer = 
	    STATIC_SYMBOL("FLUSH-COMPILED-KB-WRITE-BUFFER",AB_package);
    SET_SYMBOL_FUNCTION(Qflush_compiled_kb_write_buffer,
	    STATIC_FUNCTION(flush_compiled_kb_write_buffer,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qfinish_current_kb_save_1,
	    STATIC_FUNCTION(finish_current_kb_save_1,NIL,FALSE,0,0));
    array_constant_13 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)19L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)31L,(SI_Long)57344L);
    array_constant_15 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)19L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)21L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    array_constant_16 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)31L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_13,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)20L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)31L,(SI_Long)57344L);
    string_constant_96 = STATIC_STRING("~a \"~a\"");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_97 = 
	    string_append2(STATIC_STRING("Warning: THIS KB WAS NOT SAVED CORRECTLY! ~\n                        Please notify Gensym Customer Support of this internal ~\n                        software problem: this sav"),
	    STATIC_STRING("e failed to write ~d items: "));
    string_constant_98 = STATIC_STRING("~NF (class: ~a, calling by: ~a)");
    string_constant_99 = STATIC_STRING("Referenced items: ");
    string_constant_100 = STATIC_STRING("~NF (~a)");
    string_constant_101 = STATIC_STRING("failed to write ~d items.");
    string_constant_102 = 
	    string_append2(STATIC_STRING("WARNING: There were problems saving some attributes in clear text ~\n                    in the module~A ~(~L,A~).  These problems may prevent the kb ~\n                    from"),
	    STATIC_STRING(" being correctly loaded.  Please fix these problems now, ~\n                    and save again."));
    string_constant_103 = STATIC_STRING("s");
    SET_SYMBOL_FUNCTION(Qterminate_kb_save_or_backup,
	    STATIC_FUNCTION(terminate_kb_save_or_backup,NIL,FALSE,3,3));
    string_constant_104 = 
	    STATIC_STRING("WARNING: ~a did not complete. Problem: ~a");
    string_constant_105 = 
	    STATIC_STRING("~a completed successfully, but there were problems saving some attributes");
    string_constant_106 = STATIC_STRING("~a completed successfully");
    Qterminate_kb_save_or_backup_if_error_occurs = 
	    STATIC_SYMBOL("TERMINATE-KB-SAVE-OR-BACKUP-IF-ERROR-OCCURS",
	    AB_package);
    def_bombout_clean_up_function(Qterminate_kb_save_or_backup_if_error_occurs);
    SET_SYMBOL_FUNCTION(Qterminate_kb_save_or_backup_if_error_occurs,
	    STATIC_FUNCTION(terminate_kb_save_or_backup_if_error_occurs,
	    NIL,FALSE,0,0));
    Qhandle_change_or_deletion_fanout = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT",AB_package);
    Qslot_name_or_t_in_change_case_qm = 
	    STATIC_SYMBOL("SLOT-NAME-OR-T-IN-CHANGE-CASE\?",AB_package);
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qblock,
	    Qslot_name_or_t_in_change_case_qm);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qhandle_change_or_deletion_fanout,
	    list_constant_59,Qgeneric_method_lambda_list);
    Qhandle_change_or_deletion_fanout_for_block = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_block,
	    STATIC_FUNCTION(handle_change_or_deletion_fanout_for_block,NIL,
	    FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_block);
    set_get(Qblock,Qhandle_change_or_deletion_fanout,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qhandle_change_or_deletion_fanout),
	    Qclasses_which_define);
    temp_2 = CONS(Qblock,temp);
    mutate_global_property(Qhandle_change_or_deletion_fanout,temp_2,
	    Qclasses_which_define);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    Qhandle_change_or_deletion_fanout_for_workspace = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-WORKSPACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_workspace,
	    STATIC_FUNCTION(handle_change_or_deletion_fanout_for_workspace,
	    NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_workspace);
    set_get(Qworkspace,Qhandle_change_or_deletion_fanout,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qhandle_change_or_deletion_fanout),
	    Qclasses_which_define);
    temp_2 = CONS(Qworkspace,temp);
    mutate_global_property(Qhandle_change_or_deletion_fanout,temp_2,
	    Qclasses_which_define);
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    Qhandle_change_or_deletion_fanout_for_module_information = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-MODULE-INFORMATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_module_information,
	    STATIC_FUNCTION(handle_change_or_deletion_fanout_for_module_information,
	    NIL,FALSE,2,2));
    temp_2 = 
	    SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_module_information);
    set_get(Qmodule_information,Qhandle_change_or_deletion_fanout,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qhandle_change_or_deletion_fanout),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodule_information,temp);
    mutate_global_property(Qhandle_change_or_deletion_fanout,temp_2,
	    Qclasses_which_define);
    Qrelation = STATIC_SYMBOL("RELATION",AB_package);
    Qhandle_change_or_deletion_fanout_for_relation = 
	    STATIC_SYMBOL("HANDLE-CHANGE-OR-DELETION-FANOUT-FOR-RELATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_relation,
	    STATIC_FUNCTION(handle_change_or_deletion_fanout_for_relation,
	    NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qhandle_change_or_deletion_fanout_for_relation);
    set_get(Qrelation,Qhandle_change_or_deletion_fanout,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qhandle_change_or_deletion_fanout),
	    Qclasses_which_define);
    temp_2 = CONS(Qrelation,temp);
    mutate_global_property(Qhandle_change_or_deletion_fanout,temp_2,
	    Qclasses_which_define);
    Qruntime_data = STATIC_SYMBOL("RUNTIME-DATA",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qdynamic_text_cell_format = STATIC_SYMBOL("DYNAMIC-TEXT-CELL-FORMAT",
	    AB_package);
}
