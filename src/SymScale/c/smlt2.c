/* smlt2.c
 * Input file:  simulate2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "smlt2.h"


static Object Qno_work_done_yet_for_this_cycle;  /* no-work-done-yet-for-this-cycle */

static Object Qnew_values_computed;  /* new-values-computed */

static Object Qcalculate_new_values_for_variables;  /* calculate-new-values-for-variables */

/* SIMULATE-ONE-CYCLE */
Object simulate_one_cycle(objects,other_args,resumption_qm)
    Object objects, other_args, resumption_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, macro_time_1;
    Object micro_time_1, macro_time_2, micro_time_2, temp;
    Object simulating_externally_p_1, procedure_name_qm;

    x_note_fn_call(185,0);
    if ( !TRUEP(resumption_qm)) {
	gensymed_symbol = ISVREF(Current_model_runtime_info_qm,(SI_Long)6L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
	gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)8L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (IFIX(micro_time_2) != (SI_Long)0L) {
	    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	    if (FIXNUM_GE(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time)) {
		temp = FIXNUM_MINUS(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp;
		macro_time_1 = FIXNUM_ADD1(macro_time_1);
	    }
	    else
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	}
	else {
	    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	}
	temp = FIXNUM_ADD(macro_time_1,macro_time_2);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = temp;
	if (simulating_externally_p()) {
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)16L)) = Qno_work_done_yet_for_this_cycle;
	}
	determine_variable_groups_to_be_updated();
	return VALUES_4(Qnew_values_computed,
		Qcalculate_new_values_for_variables,Nil,Nil);
    }
    else if (EQ(objects,Qnew_values_computed)) {
	update_variables();
	simulating_externally_p_1 = simulating_externally_p();
	procedure_name_qm = current_simulation_procedure();
	if (simulating_externally_p_1) {
	    if (current_send_all_values_at_beginning_of_cycle_qm())
		send_all_input_values_to_external_simulator();
	    else
		work_on_external_simulator_tasks();
	}
	if (procedure_name_qm)
	    invoke_simulation_procedure(procedure_name_qm);
	if ( !(simulating_externally_p_1 ||  
		!TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)13L))))
	    end_simulation_cycle();
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* END-SIMULATION-CYCLE */
Object end_simulation_cycle()
{
    Object gensymed_symbol, gensymed_symbol_1, svref_new_value;
    Object variable_group_update_structure, ab_loop_list_;

    x_note_fn_call(185,1);
    if (increment_simulation_time_for_current_model_qm()) {
	gensymed_symbol = ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
	gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)6L);
	svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	variable_group_update_structure = Nil;
	ab_loop_list_ = ISVREF(Current_model_runtime_info_qm,(SI_Long)23L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	variable_group_update_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(variable_group_update_structure,(SI_Long)3L);
	gensymed_symbol_1 = ISVREF(variable_group_update_structure,
		(SI_Long)5L);
	svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qcontinue_data_server_data_acceptance;  /* continue-data-server-data-acceptance */

static Object Qsimulator_data_server;  /* simulator-data-server */

/* END-SIMULATION-PROCEDURE-OR-EXTERNAL-SIMULATION-CYCLE */
Object end_simulation_procedure_or_external_simulation_cycle()
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(185,2);
    if (simulation_procedure_and_external_simulation_finished_qm()) {
	Inhibit_non_real_time_clock_ticks_qm = Nil;
	end_simulation_cycle();
	if (Nil) {
	    if (EQ(Nil,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(Nil,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(Nil);
	    inline_note_reclaim_cons(Nil,Nil);
	    structure_being_reclaimed = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
	      SVREF(Nil,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(Nil,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
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
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qcontinue_data_server_data_acceptance;
	temp = SYMBOL_FUNCTION(Qcontinue_data_server_data_acceptance);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	temp = lookup_kb_specific_property_value(Qsimulator_data_server,
		Data_server_kbprop);
	SVREF(task,FIX((SI_Long)13L)) = temp;
	temp = Current_g2_time;
	SVREF(task,FIX((SI_Long)14L)) = temp;
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
    }
    return VALUES_1(Nil);
}

static Object Qwork_completed_for_this_cycle;  /* work-completed-for-this-cycle */

/* SIMULATION-PROCEDURE-AND-EXTERNAL-SIMULATION-FINISHED? */
Object simulation_procedure_and_external_simulation_finished_qm()
{
    Object temp;

    x_note_fn_call(185,3);
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)13L)) {
	temp =  !TRUEP(simulating_externally_p()) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1(EQ(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)16L),Qwork_completed_for_this_cycle) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* END-EXTERNAL-SIMULATION-CYCLE */
Object end_external_simulation_cycle()
{
    x_note_fn_call(185,4);
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)15L))
	return end_simulation_procedure_or_external_simulation_cycle();
    else
	return VALUES_1(Nil);
}

/* DETERMINE-VARIABLE-GROUPS-TO-BE-UPDATED */
Object determine_variable_groups_to_be_updated()
{
    Object variable_group_update_structure, ab_loop_list_, gensymed_symbol;
    Object gensymed_symbol_1, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, gensymed_symbol_2, svref_new_value;
    char temp;

    x_note_fn_call(185,5);
    variable_group_update_structure = Nil;
    ab_loop_list_ = ISVREF(Current_model_runtime_info_qm,(SI_Long)23L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable_group_update_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(variable_group_update_structure,(SI_Long)3L);
    gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
    macro_time_1 = ISVREF(gensymed_symbol,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    if (FIXNUM_LT(macro_time_1,macro_time_2))
	temp = TRUEP(T);
    else if (FIXNUM_EQ(macro_time_1,macro_time_2))
	temp = FIXNUM_LE(micro_time_1,micro_time_2);
    else
	temp = TRUEP(Qnil);
    if (temp);
    else
	temp =  !TRUEP(increment_simulation_time_for_current_model_qm());
    if (temp) {
	SVREF(variable_group_update_structure,FIX((SI_Long)4L)) = T;
	gensymed_symbol = ISVREF(variable_group_update_structure,(SI_Long)5L);
	gensymed_symbol_1 = ISVREF(variable_group_update_structure,
		(SI_Long)3L);
	gensymed_symbol_2 = ISVREF(variable_group_update_structure,
		(SI_Long)2L);
	macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
	micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	if (IFIX(micro_time_2) != (SI_Long)0L) {
	    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	    if (FIXNUM_GE(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time)) {
		svref_new_value = FIXNUM_MINUS(micro_time_1,
			Fraction_modulus_of_compound_fixnum_simulation_time);
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
		macro_time_1 = FIXNUM_ADD1(macro_time_1);
	    }
	    else
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	}
	else {
	    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
	}
	svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
    }
    else
	SVREF(variable_group_update_structure,FIX((SI_Long)4L)) = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_procedure_completion_form, Qsimulation_procedure_completion_form);

static Object string_constant;     /* "~a is given as the simulation procedure in the simulation-parameters ~
				    *           system table, but no procedure with that name exists."
				    */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_1;   /* "~a is given as the simulation procedure in the simulation-parameters ~
				    *           system table, but this names the constant value ~NC."
				    */

static Object string_constant_2;   /* "~a is given as the simulation procedure in the simulation-parameters ~
				    *           system table, but this names a ~a, not a procedure."
				    */

static Object string_constant_3;   /* "~a is given as the simulation procedure in the simulation-parameters ~
				    *           system table, but this procedure is either inactive, is not enabled ~
				    *           for running while inactive, or has a status other than OK."
				    */

static Object string_constant_4;   /* "Error starting simulation procedure ~NF: ~a" */

/* INVOKE-SIMULATION-PROCEDURE */
Object invoke_simulation_procedure(procedure_name)
    Object procedure_name;
{
    Object temp, current_computation_frame, procedure;
    Object current_computation_component_particulars, managed_number_or_value;
    Object sub_class_bit_vector, argument_error_qm;
    Object current_model_definition_or_t, temp_2, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(185,6);
    temp = Current_model_definition_qm;
    if (temp);
    else
	temp = Simulation_parameters;
    current_computation_frame = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      procedure = evaluate_designation(procedure_name,Nil);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      0);
	if ( !TRUEP(procedure)) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		result = give_warning_1(3,FIX((SI_Long)1L),string_constant,
			procedure_name);
	    else
		result = VALUES_1(Nil);
	}
	else if (SIMPLE_VECTOR_P(procedure) && EQ(ISVREF(procedure,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level)) {
		managed_number_or_value = ISVREF(procedure,(SI_Long)1L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else
		    temp = managed_number_or_value;
		give_warning_1(5,FIX((SI_Long)1L),string_constant_1,
			procedure_name,temp,ISVREF(procedure,(SI_Long)2L));
	    }
	    result = reclaim_temporary_constant_1(procedure);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    result = give_warning_1(4,FIX((SI_Long)1L),
			    string_constant_2,procedure_name,
			    ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)1L));
		else
		    result = VALUES_1(Nil);
	    }
	    else {
		temp = ISVREF(procedure,(SI_Long)8L);
		if ( !( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
			(IFIX(ISVREF(procedure,(SI_Long)5L)) & 
			(SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) && 
			(SI_Long)0L != (IFIX(ISVREF(procedure,
			(SI_Long)4L)) & (SI_Long)16777216L) &&  
			!((SI_Long)0L != (IFIX(ISVREF(procedure,
			(SI_Long)4L)) & (SI_Long)8192L))))) {
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			result = give_warning_1(3,FIX((SI_Long)1L),
				string_constant_3,procedure_name);
		    else
			result = VALUES_1(Nil);
		}
		else {
		    argument_error_qm = 
			    get_procedure_argument_list_error_if_any(procedure,
			    Nil,Nil);
		    if (argument_error_qm) {
			if ((SI_Long)1L <= IFIX(Warning_message_level))
			    give_warning_1(4,FIX((SI_Long)1L),
				    string_constant_4,procedure,
				    argument_error_qm);
			result = reclaim_text_string(argument_error_qm);
		    }
		    else {
			current_model_definition_or_t = 
				Current_model_definition_qm;
			if (current_model_definition_or_t);
			else
			    current_model_definition_or_t = T;
			temp_2 = Current_model_runtime_info_qm;
			SVREF(temp_2,FIX((SI_Long)13L)) = Nil;
			temp_2 = Simulation_procedure_completion_form;
			M_SECOND(temp_2) = current_model_definition_or_t;
			temp_2 = Current_model_runtime_info_qm;
			svref_new_value = 
				ISVREF(start_procedure_invocation_in_place(procedure,
				Nil,Nil,Nil,FIX((SI_Long)0L),
				FIX((SI_Long)0L),
				current_model_definition_or_t,
				Simulation_procedure_completion_form,Nil,
				Nil,Nil),(SI_Long)11L);
			result = VALUES_1(SVREF(temp_2,FIX((SI_Long)12L)) 
				= svref_new_value);
		    }
		}
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qeuler;              /* euler */

static Object Qrk4;                /* rk4 */

/* CALCULATE-NEW-VALUES-FOR-VARIABLES */
Object calculate_new_values_for_variables(objects,other_args,resumption_qm)
    Object objects, other_args, resumption_qm;
{
    Object temp;

    x_note_fn_call(185,7);
    temp = current_integration_algorithm();
    if (EQ(temp,Qeuler))
	return calculate_new_values_using_euler(objects,other_args,
		resumption_qm);
    else if (EQ(temp,Qrk4))
	return calculate_new_values_using_rk4(objects,other_args,
		resumption_qm);
    else
	return VALUES_1(Qnil);
}

static Object Qcalculating_state_variables;  /* calculating-state-variables */

static Object Qcontinuous_state_done;  /* continuous-state-done */

static Object Qcalculate_new_values_for_continuous_state_variables;  /* calculate-new-values-for-continuous-state-variables */

static Object Qdiscrete_state_done;  /* discrete-state-done */

static Object Qcalculate_new_values_for_discrete_state_variables;  /* calculate-new-values-for-discrete-state-variables */

static Object Qcalculating_dependent_variables;  /* calculating-dependent-variables */

static Object Qdependent_done;     /* dependent-done */

static Object Qcalculate_new_values_for_dependent_variables;  /* calculate-new-values-for-dependent-variables */

/* CALCULATE-NEW-VALUES-USING-EULER */
Object calculate_new_values_using_euler(objects,other_args,resumption_qm)
    Object objects, other_args, resumption_qm;
{
    Object svref_arg_1, temp;

    x_note_fn_call(185,8);
    if ( !TRUEP(resumption_qm)) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_state_variables;
	temp = ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)19L),
		(SI_Long)9L);
	return VALUES_4(Qcontinuous_state_done,
		Qcalculate_new_values_for_continuous_state_variables,temp,Nil);
    }
    else if (EQ(objects,Qcontinuous_state_done)) {
	temp = ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)20L),
		(SI_Long)9L);
	return VALUES_4(Qdiscrete_state_done,
		Qcalculate_new_values_for_discrete_state_variables,temp,Nil);
    }
    else if (EQ(objects,Qdiscrete_state_done)) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_dependent_variables;
	temp = ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)21L),
		(SI_Long)9L);
	return VALUES_4(Qdependent_done,
		Qcalculate_new_values_for_dependent_variables,temp,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CALCULATE-NEW-VALUES-USING-RK4 */
Object calculate_new_values_using_rk4(objects,other_args,resumption_qm)
    Object objects, other_args, resumption_qm;
{
    Object svref_arg_1, temp;
    SI_Long svref_new_value;

    x_note_fn_call(185,9);
    if ( !TRUEP(resumption_qm)) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_state_variables;
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
	temp = ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)20L),
		(SI_Long)9L);
	return VALUES_4(Qdiscrete_state_done,
		Qcalculate_new_values_for_discrete_state_variables,temp,Nil);
    }
    else if (EQ(objects,Qdiscrete_state_done) || EQ(objects,Qdependent_done)) {
	if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L) && 
		IFIX(ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) == 
		(SI_Long)4L)
	    return VALUES_1(Nil);
	else {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_state_variables;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    svref_new_value =  !TRUEP(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)3L)) ? (SI_Long)1L : 
		    IFIX(FIXNUM_ADD1(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)3L)));
	    ISVREF(svref_arg_1,(SI_Long)3L) = FIX(svref_new_value);
	    temp = ISVREF(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)19L),(SI_Long)9L);
	    return VALUES_4(Qcontinuous_state_done,
		    Qcalculate_new_values_for_continuous_state_variables,
		    temp,Nil);
	}
    }
    else {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_dependent_variables;
	temp = ISVREF(ISVREF(Current_model_runtime_info_qm,(SI_Long)21L),
		(SI_Long)9L);
	return VALUES_4(Qdependent_done,
		Qcalculate_new_values_for_dependent_variables,temp,Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Set_of_variables_to_simulation_evaluate, Qset_of_variables_to_simulation_evaluate);

DEFINE_VARIABLE_WITH_SYMBOL(Current_simulation_category, Qcurrent_simulation_category);

DEFINE_VARIABLE_WITH_SYMBOL(Working_on_variables_that_need_simulated_values_stack_qm, Qworking_on_variables_that_need_simulated_values_stack_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Variable_is_at_bottom_of_stack_qm, Qvariable_is_at_bottom_of_stack_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Dont_proceed_to_next_variable_qm, Qdont_proceed_to_next_variable_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Within_simulator_for_stack_error_qm, Qwithin_simulator_for_stack_error_qm);

static Object Qsimulator;          /* simulator */

static Object Qnever;              /* never */

/* PROCESS-N-VARIABLES-IN-STACK-EVAL */
Object process_n_variables_in_stack_eval(rest_of_set,simulation_category)
    Object rest_of_set, simulation_category;
{
    Object current_computation_flags, current_computation_activity;
    Object current_computation_component_particulars;
    Object current_computation_frame, current_computation_instance;
    Object current_computation_style, current_environment;
    Object evaluating_simulator_procedure_qm, explanation_variables;
    Object stack_expiration, variables_that_did_not_have_values;
    Object set_of_variables_to_simulation_evaluate;
    Object current_simulation_category, current_simulation_runtime_structure;
    Object dont_backward_chain_in_sim_eval_qm;
    Object dont_proceed_to_next_variable_qm;
    Object working_on_variables_that_need_simulated_values_stack_qm;
    Object variable_is_at_bottom_of_stack_qm;
    Object within_simulator_for_stack_error_qm, saved_warning_level;
    Object saved_tracing_level, saved_breakpoint_level;
    Object saved_source_stepping_level, simulation_environment_vector, formula;
    Object byte_code_body, temp;
    Declare_special(24);
    Object result;

    x_note_fn_call(185,10);
  next_loop:
    if ( !TRUEP(rest_of_set))
	goto end_loop;
    current_computation_flags = FIX((SI_Long)18L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    23);
      current_computation_activity = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_activity,Qcurrent_computation_activity,current_computation_activity,
	      22);
	current_computation_component_particulars = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		21);
	  current_computation_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  20);
	    current_computation_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    19);
	      current_computation_style = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		      18);
		current_environment = Qsimulator;
		PUSH_SPECIAL_WITH_SYMBOL(Current_environment,Qcurrent_environment,current_environment,
			17);
		  evaluating_simulator_procedure_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Evaluating_simulator_procedure_qm,Qevaluating_simulator_procedure_qm,evaluating_simulator_procedure_qm,
			  16);
		    explanation_variables = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Explanation_variables,Qexplanation_variables,explanation_variables,
			    15);
		      stack_expiration = Qnever;
		      PUSH_SPECIAL_WITH_SYMBOL(Stack_expiration,Qstack_expiration,stack_expiration,
			      14);
			variables_that_did_not_have_values = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
				13);
			  set_of_variables_to_simulation_evaluate = 
				  rest_of_set;
			  PUSH_SPECIAL_WITH_SYMBOL(Set_of_variables_to_simulation_evaluate,Qset_of_variables_to_simulation_evaluate,set_of_variables_to_simulation_evaluate,
				  12);
			    current_simulation_category = simulation_category;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_category,Qcurrent_simulation_category,current_simulation_category,
				    11);
			      current_simulation_runtime_structure = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
				      10);
				dont_backward_chain_in_sim_eval_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
					9);
				  dont_proceed_to_next_variable_qm = Nil;
				  PUSH_SPECIAL_WITH_SYMBOL(Dont_proceed_to_next_variable_qm,Qdont_proceed_to_next_variable_qm,dont_proceed_to_next_variable_qm,
					  8);
				    working_on_variables_that_need_simulated_values_stack_qm 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Working_on_variables_that_need_simulated_values_stack_qm,Qworking_on_variables_that_need_simulated_values_stack_qm,working_on_variables_that_need_simulated_values_stack_qm,
					    7);
				      variable_is_at_bottom_of_stack_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Variable_is_at_bottom_of_stack_qm,Qvariable_is_at_bottom_of_stack_qm,variable_is_at_bottom_of_stack_qm,
					      6);
					within_simulator_for_stack_error_qm 
						= T;
					PUSH_SPECIAL_WITH_SYMBOL(Within_simulator_for_stack_error_qm,Qwithin_simulator_for_stack_error_qm,within_simulator_for_stack_error_qm,
						5);
					  saved_warning_level = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Saved_warning_level,Qsaved_warning_level,saved_warning_level,
						  4);
					    saved_tracing_level = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Saved_tracing_level,Qsaved_tracing_level,saved_tracing_level,
						    3);
					      saved_breakpoint_level = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Saved_breakpoint_level,Qsaved_breakpoint_level,saved_breakpoint_level,
						      2);
						saved_source_stepping_level 
							= Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Saved_source_stepping_level,Qsaved_source_stepping_level,saved_source_stepping_level,
							1);
						  enter_next_simulation_variable_context();
						  if ( 
							  !TRUEP(Current_computation_instance)) 
							      {
						      result = VALUES_1(Nil);
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
						      goto end_process_n_variables_in_stack_eval;
						  }
						  simulation_environment_vector 
							  = 
							  ISVREF(Current_simulation_runtime_structure,
							  (SI_Long)20L);
						  if (Profiling_enabled_qm) {
						      formula = 
							      ISVREF(Current_simulation_runtime_structure,
							      (SI_Long)21L);
						      increment_profiling_calls(formula);
						      posit_profiling_structure(formula);
						  }
						  byte_code_body = 
							  ISVREF(Current_simulation_runtime_structure,
							  (SI_Long)17L);
						  temp = 
							  ISVREF(byte_code_body,
							  (SI_Long)3L);
						  stack_eval(byte_code_body,
							  temp,
							  simulation_environment_vector,
							  c_native_clock_ticks_or_cache(Nil,
							  Nil),Nil,
							  FIX((SI_Long)0L));
						  if (ISVREF(Current_model_runtime_info_qm,
							  (SI_Long)11L))
						      signal_simulation_error_after_stack_eval();
						  if (Current_computation_instance) 
							      {
						      dont_backward_chain_in_sim_eval_qm 
							      = T;
						      PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
							      0);
							exit_last_simulation_variable_context(Nil,
								simulation_environment_vector);
						      POP_SPECIAL();
						  }
						  if ( 
							  !TRUEP(Initializing_simulator_qm) 
							  && 
							  Ran_out_of_time_qm) {
						      result = VALUES_2(Set_of_variables_to_simulation_evaluate,
							      Nil);
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
						      goto end_process_n_variables_in_stack_eval;
						  }
						  rest_of_set = 
							  Set_of_variables_to_simulation_evaluate;
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
    goto next_loop;
  end_loop:
    result = VALUES_1(Qnil);
  end_process_n_variables_in_stack_eval:
    return result;
}

static Object Qsimulation_info_qm;  /* simulation-info? */

/* SIM-EVAL-FOR-STACK-UNTIL-VALUE-FOUND */
Object sim_eval_for_stack_until_value_found(variable)
    Object variable;
{
    Object current_computation_flags, current_computation_activity;
    Object current_computation_component_particulars;
    Object current_computation_frame, current_computation_instance;
    Object current_computation_style, current_environment;
    Object evaluating_simulator_procedure_qm, explanation_variables;
    Object stack_expiration, variables_that_did_not_have_values;
    Object set_of_variables_to_simulation_evaluate, simulation_info_qm;
    Object current_simulation_category, current_simulation_runtime_structure;
    Object dont_backward_chain_in_sim_eval_qm;
    Object dont_proceed_to_next_variable_qm;
    Object working_on_variables_that_need_simulated_values_stack_qm;
    Object variable_is_at_bottom_of_stack_qm;
    Object within_simulator_for_stack_error_qm, saved_warning_level;
    Object saved_tracing_level, saved_breakpoint_level;
    Object saved_source_stepping_level;
    Declare_special(23);
    Object result;

    x_note_fn_call(185,11);
    current_computation_flags = FIX((SI_Long)18L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    22);
      current_computation_activity = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_activity,Qcurrent_computation_activity,current_computation_activity,
	      21);
	current_computation_component_particulars = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		20);
	  current_computation_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  19);
	    current_computation_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    18);
	      current_computation_style = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		      17);
		current_environment = Qsimulator;
		PUSH_SPECIAL_WITH_SYMBOL(Current_environment,Qcurrent_environment,current_environment,
			16);
		  evaluating_simulator_procedure_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Evaluating_simulator_procedure_qm,Qevaluating_simulator_procedure_qm,evaluating_simulator_procedure_qm,
			  15);
		    explanation_variables = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Explanation_variables,Qexplanation_variables,explanation_variables,
			    14);
		      stack_expiration = Qnever;
		      PUSH_SPECIAL_WITH_SYMBOL(Stack_expiration,Qstack_expiration,stack_expiration,
			      13);
			variables_that_did_not_have_values = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
				12);
			  set_of_variables_to_simulation_evaluate = 
				  get_lookup_slot_value_given_default(variable,
				  Qsimulation_info_qm,Nil);
			  PUSH_SPECIAL_WITH_SYMBOL(Set_of_variables_to_simulation_evaluate,Qset_of_variables_to_simulation_evaluate,set_of_variables_to_simulation_evaluate,
				  11);
			    simulation_info_qm = 
				    get_lookup_slot_value_given_default(variable,
				    Qsimulation_info_qm,Nil);
			    current_simulation_category = 
				    simulation_info_qm ? 
				    ISVREF(simulation_info_qm,(SI_Long)2L) 
				    : Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_category,Qcurrent_simulation_category,current_simulation_category,
				    10);
			      current_simulation_runtime_structure = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
				      9);
				dont_backward_chain_in_sim_eval_qm = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
					8);
				  dont_proceed_to_next_variable_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Dont_proceed_to_next_variable_qm,Qdont_proceed_to_next_variable_qm,dont_proceed_to_next_variable_qm,
					  7);
				    working_on_variables_that_need_simulated_values_stack_qm 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Working_on_variables_that_need_simulated_values_stack_qm,Qworking_on_variables_that_need_simulated_values_stack_qm,working_on_variables_that_need_simulated_values_stack_qm,
					    6);
				      variable_is_at_bottom_of_stack_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Variable_is_at_bottom_of_stack_qm,Qvariable_is_at_bottom_of_stack_qm,variable_is_at_bottom_of_stack_qm,
					      5);
					within_simulator_for_stack_error_qm 
						= T;
					PUSH_SPECIAL_WITH_SYMBOL(Within_simulator_for_stack_error_qm,Qwithin_simulator_for_stack_error_qm,within_simulator_for_stack_error_qm,
						4);
					  saved_warning_level = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Saved_warning_level,Qsaved_warning_level,saved_warning_level,
						  3);
					    saved_tracing_level = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Saved_tracing_level,Qsaved_tracing_level,saved_tracing_level,
						    2);
					      saved_breakpoint_level = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Saved_breakpoint_level,Qsaved_breakpoint_level,saved_breakpoint_level,
						      1);
						saved_source_stepping_level 
							= Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Saved_source_stepping_level,Qsaved_source_stepping_level,saved_source_stepping_level,
							0);
						next_loop:
						  sim_eval_for_stack();
						  if ( 
							  !TRUEP(ISVREF(Current_model_runtime_info_qm,
							  (SI_Long)30L)))
						      goto end_loop;
						  goto next_loop;
						end_loop:
						  result = VALUES_1(Qnil);
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
    return result;
}

/* SIM-EVAL-FOR-STACK-WITHOUT-CHAINING */
Object sim_eval_for_stack_without_chaining(variable)
    Object variable;
{
    Object current_computation_flags, current_computation_activity;
    Object current_computation_component_particulars;
    Object current_computation_frame, current_computation_instance;
    Object current_computation_style, current_environment;
    Object evaluating_simulator_procedure_qm, explanation_variables;
    Object stack_expiration, variables_that_did_not_have_values;
    Object set_of_variables_to_simulation_evaluate, simulation_info_qm;
    Object current_simulation_category, current_simulation_runtime_structure;
    Object dont_backward_chain_in_sim_eval_qm;
    Object dont_proceed_to_next_variable_qm;
    Object working_on_variables_that_need_simulated_values_stack_qm;
    Object variable_is_at_bottom_of_stack_qm;
    Object within_simulator_for_stack_error_qm, saved_warning_level;
    Object saved_tracing_level, saved_breakpoint_level;
    Object saved_source_stepping_level;
    Declare_special(23);
    Object result;

    x_note_fn_call(185,12);
    current_computation_flags = FIX((SI_Long)18L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    22);
      current_computation_activity = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_activity,Qcurrent_computation_activity,current_computation_activity,
	      21);
	current_computation_component_particulars = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		20);
	  current_computation_frame = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		  19);
	    current_computation_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		    18);
	      current_computation_style = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		      17);
		current_environment = Qsimulator;
		PUSH_SPECIAL_WITH_SYMBOL(Current_environment,Qcurrent_environment,current_environment,
			16);
		  evaluating_simulator_procedure_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Evaluating_simulator_procedure_qm,Qevaluating_simulator_procedure_qm,evaluating_simulator_procedure_qm,
			  15);
		    explanation_variables = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Explanation_variables,Qexplanation_variables,explanation_variables,
			    14);
		      stack_expiration = Qnever;
		      PUSH_SPECIAL_WITH_SYMBOL(Stack_expiration,Qstack_expiration,stack_expiration,
			      13);
			variables_that_did_not_have_values = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
				12);
			  set_of_variables_to_simulation_evaluate = 
				  get_lookup_slot_value_given_default(variable,
				  Qsimulation_info_qm,Nil);
			  PUSH_SPECIAL_WITH_SYMBOL(Set_of_variables_to_simulation_evaluate,Qset_of_variables_to_simulation_evaluate,set_of_variables_to_simulation_evaluate,
				  11);
			    simulation_info_qm = 
				    get_lookup_slot_value_given_default(variable,
				    Qsimulation_info_qm,Nil);
			    current_simulation_category = 
				    simulation_info_qm ? 
				    ISVREF(simulation_info_qm,(SI_Long)2L) 
				    : Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_category,Qcurrent_simulation_category,current_simulation_category,
				    10);
			      current_simulation_runtime_structure = Nil;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
				      9);
				dont_backward_chain_in_sim_eval_qm = T;
				PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
					8);
				  dont_proceed_to_next_variable_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Dont_proceed_to_next_variable_qm,Qdont_proceed_to_next_variable_qm,dont_proceed_to_next_variable_qm,
					  7);
				    working_on_variables_that_need_simulated_values_stack_qm 
					    = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Working_on_variables_that_need_simulated_values_stack_qm,Qworking_on_variables_that_need_simulated_values_stack_qm,working_on_variables_that_need_simulated_values_stack_qm,
					    6);
				      variable_is_at_bottom_of_stack_qm = Nil;
				      PUSH_SPECIAL_WITH_SYMBOL(Variable_is_at_bottom_of_stack_qm,Qvariable_is_at_bottom_of_stack_qm,variable_is_at_bottom_of_stack_qm,
					      5);
					within_simulator_for_stack_error_qm 
						= T;
					PUSH_SPECIAL_WITH_SYMBOL(Within_simulator_for_stack_error_qm,Qwithin_simulator_for_stack_error_qm,within_simulator_for_stack_error_qm,
						4);
					  saved_warning_level = Nil;
					  PUSH_SPECIAL_WITH_SYMBOL(Saved_warning_level,Qsaved_warning_level,saved_warning_level,
						  3);
					    saved_tracing_level = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Saved_tracing_level,Qsaved_tracing_level,saved_tracing_level,
						    2);
					      saved_breakpoint_level = Nil;
					      PUSH_SPECIAL_WITH_SYMBOL(Saved_breakpoint_level,Qsaved_breakpoint_level,saved_breakpoint_level,
						      1);
						saved_source_stepping_level 
							= Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Saved_source_stepping_level,Qsaved_source_stepping_level,saved_source_stepping_level,
							0);
						  result = sim_eval_for_stack();
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
    return result;
}

/* SIM-EVAL-FOR-STACK */
Object sim_eval_for_stack()
{
    Object sub_class_bit_vector, temp_1, temp_2, byte_code_body;
    Object simulation_environment_vector, dont_backward_chain_in_sim_eval_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(185,13);
    enter_next_simulation_variable_context();
    if (Current_computation_instance) {
	if (state_variable_p(Current_computation_instance) && 
		Initializing_state_variables_qm) {
	    if (need_to_stack_eval_to_get_initial_value_for_state_variable_qm(Current_computation_instance,
		    Current_simulation_runtime_structure)) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(Current_computation_frame,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_simulation_formula_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    temp_1 = ISVREF(Current_computation_frame,(SI_Long)21L);
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(Current_computation_frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Simulation_subtable_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			temp_1 = ISVREF(Current_computation_frame,
				(SI_Long)24L);
		    else
			temp_1 = Qnil;
		}
		temp_2 = ISVREF(Current_simulation_runtime_structure,
			(SI_Long)22L);
		result = VALUES_2(temp_1,temp_2);
	    }
	    else
		result = VALUES_2(Nil,Nil);
	}
	else {
	    temp_1 = ISVREF(Current_simulation_runtime_structure,(SI_Long)17L);
	    temp_2 = ISVREF(Current_simulation_runtime_structure,(SI_Long)20L);
	    result = VALUES_2(temp_1,temp_2);
	}
	MVS_2(result,byte_code_body,simulation_environment_vector);
	if ( !TRUEP(byte_code_body))
	    Current_computation_instance = Nil;
	if (byte_code_body) {
	    if (Profiling_enabled_qm) {
		increment_profiling_calls(Current_computation_instance);
		posit_profiling_structure(Current_computation_instance);
	    }
	    temp_2 = ISVREF(byte_code_body,(SI_Long)3L);
	    stack_eval(byte_code_body,temp_2,simulation_environment_vector,
		    c_native_clock_ticks_or_cache(Nil,Nil),Nil,
		    FIX((SI_Long)0L));
	    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)11L))
		signal_simulation_error_after_stack_eval();
	    if (Current_computation_instance) {
		dont_backward_chain_in_sim_eval_qm = T;
		PUSH_SPECIAL_WITH_SYMBOL(Dont_backward_chain_in_sim_eval_qm,Qdont_backward_chain_in_sim_eval_qm,dont_backward_chain_in_sim_eval_qm,
			0);
		  result = exit_last_simulation_variable_context(Nil,
			  simulation_environment_vector);
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdependent;          /* dependent */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

/* ENTER-NEXT-SIMULATION-VARIABLE-CONTEXT */
Object enter_next_simulation_variable_context()
{
    Object temp, variable, temp_list, simulation_info_qm, runtime_info_qm;
    Object svref_arg_1, svref_new_value, next_variable_to_compute;
    Object gensymed_symbol;

    x_note_fn_call(185,14);
    if (Dont_backward_chain_in_sim_eval_qm)
	set_info_for_evaluation_only(Set_of_variables_to_simulation_evaluate);
    else {
	Current_computation_instance = Nil;
      next_loop:
	if ( !TRUEP(Set_of_variables_to_simulation_evaluate))
	    goto end_loop;
	if (EQ(Current_simulation_category,Qdependent) || 
		Initializing_state_variables_qm) {
	    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)30L)))
		set_info_for_next_variable_to_simulate_1(Set_of_variables_to_simulation_evaluate);
	    else {
		temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)30L);
		variable = CAR(temp);
		temp_list = ISVREF(Current_model_runtime_info_qm,(SI_Long)30L);
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		runtime_info_qm = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		svref_arg_1 = Current_model_runtime_info_qm;
		temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)30L);
		svref_new_value = CDR(temp);
		SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
		if (temp_list)
		    reclaim_simulate_cons_1(temp_list);
		if (runtime_info_qm)
		    SVREF(runtime_info_qm,FIX((SI_Long)23L)) = Nil;
		next_variable_to_compute = variable;
		Working_on_variables_that_need_simulated_values_stack_qm = T;
		Variable_is_at_bottom_of_stack_qm =  
			!TRUEP(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)30L)) ? T : Nil;
		set_info_for_next_variable_to_simulate_1(get_lookup_slot_value_given_default(next_variable_to_compute,
			Qsimulation_info_qm,Nil));
	    }
	}
	else
	    set_info_for_next_variable_to_simulate_1(Set_of_variables_to_simulation_evaluate);
	if (Current_computation_instance || Dont_proceed_to_next_variable_qm)
	    goto end_loop;
	Set_of_variables_to_simulation_evaluate = 
		ISVREF(Set_of_variables_to_simulation_evaluate,(SI_Long)9L);
	goto next_loop;
      end_loop:
	if ( !TRUEP(Current_computation_instance))
	    return VALUES_1(Nil);
	Number_of_simulated_variables_processed = 
		FIXNUM_ADD1(Number_of_simulated_variables_processed);
    }
    Stack_expiration = Qnever;
    gensymed_symbol = get_lookup_slot_value(Current_computation_frame,
	    Qtracing_and_breakpoints);
    if ((gensymed_symbol || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(Current_computation_frame,
		gensymed_symbol);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) {
	    temp = Current_computation_frame;
	    return issue_tracing_and_breakpoints_entry_message(temp,
		    simulation_enter_tracing_context_message());
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

/* SIMULATION-ENTER-TRACING-CONTEXT-MESSAGE */
Object simulation_enter_tracing_context_message()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(185,15);
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
	      twrite_beginning_of_wide_string(array_constant,
		      FIX((SI_Long)10L));
	      write_simulation_formula_trace_entry(Current_computation_frame);
	      twrite_character(FIX((SI_Long)46L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object float_constant;      /* 0.0 */

static Object Qcontinuous_state;   /* continuous-state */

static Object Qlong;               /* long */

static Object Qtext;               /* text */

static Object Qtruth_value;        /* truth-value */

static Object Qboolean;            /* boolean */

static Object string_constant_5;   /* "Error while integrating ~NF.  The equation for the derivative did ~
				    * not evaluate to a number."
				    */

static Object string_constant_6;   /* "Error while integrating ~NF.  The equation for the derivative did ~
				    *         not evaluate to a number."
				    */

static Object Qdiscrete_state;     /* discrete-state */

/* EXIT-LAST-SIMULATION-VARIABLE-CONTEXT */
Object exit_last_simulation_variable_context(value_known_qm,
	    simulation_environment_vector)
    Object value_known_qm, simulation_environment_vector;
{
    Object temp, new_evaluation_value, gensymed_symbol;
    Object store_managed_number_or_value_arg, temp_1, gensymed_symbol_1;
    Object gensymed_symbol_2, type_specification;
    Object simulate_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    Object simulation_info_qm, k_value, runtime_structure;
    Object managed_number_or_value, previous_value, integer_portion;
    Object micro_time, h, managed_number, current_value, new_value;
    Object top_of_stack, message_1;
    double aref_new_value, temp_2, temp_3, store_managed_number_or_value_arg_1;
    double gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double gensymed_symbol_6, gensymed_symbol_7;

    x_note_fn_call(185,16);
    if (Current_computation_frame) {
	if (Saved_warning_level) {
	    if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		    IFIX(Tracing_message_level) > (SI_Long)0L) && 
		    ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		    !TRUEP(in_order_p(Current_computation_frame))) {
		temp = Current_computation_frame;
		issue_tracing_and_breakpoint_exit_message(temp,
			simulation_formula_trace_exit_message(Current_computation_frame));
	    }
	    Warning_message_level = Saved_warning_level;
	    Tracing_message_level = Saved_tracing_level;
	    Breakpoint_level = Saved_breakpoint_level;
	    Source_stepping_level = Saved_source_stepping_level;
	}
	if ( !TRUEP(Dont_backward_chain_in_sim_eval_qm)) {
	    new_evaluation_value = value_known_qm ? 
		    ISVREF(simulation_environment_vector,(SI_Long)1L) : 
		    Simulation_no_value;
	    if (EQ(Current_simulation_category,Qdependent) || 
		    Initializing_state_variables_qm) {
		if ( !TRUEP(ISVREF(Current_simulation_runtime_structure,
			(SI_Long)23L))) {
		    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
			temp = ISVREF(Current_model_runtime_info_qm,
				(SI_Long)3L);
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				gensymed_symbol = 
					Current_simulation_runtime_structure;
				store_managed_number_or_value_arg = 
					evaluation_value_value(new_evaluation_value);
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)7L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)1L);
				break;
			      case 2:
				gensymed_symbol = 
					Current_simulation_runtime_structure;
				store_managed_number_or_value_arg = 
					evaluation_value_value(new_evaluation_value);
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)8L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)8L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)2L);
				break;
			      case 3:
				gensymed_symbol = 
					Current_simulation_runtime_structure;
				store_managed_number_or_value_arg = 
					evaluation_value_value(new_evaluation_value);
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)9L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)9L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)3L);
				break;
			      case 4:
				gensymed_symbol = 
					Current_simulation_runtime_structure;
				store_managed_number_or_value_arg = 
					evaluation_value_value(new_evaluation_value);
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)10L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)10L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)4L);
				gensymed_symbol = 
					Current_simulation_runtime_structure;
				gensymed_symbol_1 = ISVREF(gensymed_symbol,
					(SI_Long)16L);
				gensymed_symbol_2 = new_evaluation_value;
				type_specification = 
					type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
				if (EQ(type_specification,Qfloat) && 
					FIXNUMP(gensymed_symbol_2)) {
				    store_managed_number_or_value_arg = 
					    lfloat(gensymed_symbol_2,
					    float_constant);
				    temp_1 = 
					    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					    (SI_Long)2L),
					    store_managed_number_or_value_arg);
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_1;
				}
				else if (type_specification_type_p(gensymed_symbol_2,
					type_specification)) {
				    temp_1 = 
					    reclaim_managed_number_or_value_function(ISVREF(gensymed_symbol,
					    (SI_Long)2L));
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_1;
				    temp_1 = FIXNUMP(gensymed_symbol_2) || 
					    SYMBOLP(gensymed_symbol_2) ? 
					    gensymed_symbol_2 : 
					    copy_evaluation_value_1(gensymed_symbol_2);
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_1;
				}
				else
				    simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
					    evaluation_value_value(gensymed_symbol_2));
				SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
				break;
			      default:
				break;
			    }
		    }
		    else {
			gensymed_symbol = Current_simulation_runtime_structure;
			gensymed_symbol_1 = ISVREF(gensymed_symbol,
				(SI_Long)16L);
			gensymed_symbol_2 = new_evaluation_value;
			type_specification = 
				type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
			if (EQ(type_specification,Qfloat) && 
				FIXNUMP(gensymed_symbol_2)) {
			    store_managed_number_or_value_arg = 
				    lfloat(gensymed_symbol_2,float_constant);
			    temp_1 = 
				    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
				    (SI_Long)2L),
				    store_managed_number_or_value_arg);
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
			}
			else if (type_specification_type_p(gensymed_symbol_2,
				type_specification)) {
			    temp_1 = 
				    reclaim_managed_number_or_value_function(ISVREF(gensymed_symbol,
				    (SI_Long)2L));
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
			    temp_1 = FIXNUMP(gensymed_symbol_2) || 
				    SYMBOLP(gensymed_symbol_2) ? 
				    gensymed_symbol_2 : 
				    copy_evaluation_value_1(gensymed_symbol_2);
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
			}
			else
			    simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
				    evaluation_value_value(gensymed_symbol_2));
			SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
		    }
		}
		if (Working_on_variables_that_need_simulated_values_stack_qm) {
		    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)31L) 
			    &&  !TRUEP(Variable_is_at_bottom_of_stack_qm) 
			    &&  
			    !TRUEP(ISVREF(Current_simulation_runtime_structure,
			    (SI_Long)24L))) {
			temp_1 = Current_model_runtime_info_qm;
			simulate_push_modify_macro_arg = 
				Current_computation_instance;
			car_1 = simulate_push_modify_macro_arg;
			cdr_1 = ISVREF(temp_1,(SI_Long)32L);
			svref_new_value = simulate_cons_1(car_1,cdr_1);
			SVREF(temp_1,FIX((SI_Long)32L)) = svref_new_value;
			simulation_info_qm = 
				get_lookup_slot_value_given_default(Current_computation_instance,
				Qsimulation_info_qm,Nil);
			temp_1 = simulation_info_qm ? 
				ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
			SVREF(temp_1,FIX((SI_Long)24L)) = T;
		    }
		    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,
			    (SI_Long)30L)))
			clear_tainted_variables(1,T);
		    Working_on_variables_that_need_simulated_values_stack_qm 
			    = Nil;
		    Variable_is_at_bottom_of_stack_qm = Nil;
		}
		if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)30L)) &&  
			!TRUEP(Dont_proceed_to_next_variable_qm))
		    Set_of_variables_to_simulation_evaluate = 
			    ISVREF(Set_of_variables_to_simulation_evaluate,
			    (SI_Long)9L);
	    }
	    else if (EQ(Current_simulation_category,Qcontinuous_state)) {
		if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    k_value = evaluation_value_value(new_evaluation_value);
		    runtime_structure = Current_simulation_runtime_structure;
		    managed_number_or_value = ISVREF(runtime_structure,
			    (SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp = copy_text_string(managed_number_or_value);
		    else
			temp = managed_number_or_value;
		    previous_value = lfloat(temp,float_constant);
		    gensymed_symbol = 
			    ISVREF(ISVREF(ISVREF(runtime_structure,
			    (SI_Long)11L),(SI_Long)1L),(SI_Long)2L);
		    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
		    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
		    if (IFIX(micro_time) == (SI_Long)0L) {
			temp_1 = Simulation_time_managed_float;
			aref_new_value = (double)IFIX(integer_portion);
			DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		    }
		    else {
			temp_1 = Simulation_time_managed_float;
			aref_new_value = (double)IFIX(integer_portion) + 
				(double)IFIX(micro_time) / 100000.0;
			DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		    }
		    h = Simulation_time_managed_float;
		    if (NUMBERP(k_value)) {
			k_value = lfloat(k_value,float_constant);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
			k_value = DOUBLE_TO_DOUBLE_FLOAT(temp_2 * 
				DFLOAT_ISAREF_1(h,(SI_Long)0L));
			temp = ISVREF(Current_model_runtime_info_qm,
				(SI_Long)3L);
			if (! !(FIXNUMP(temp) && 
				FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				FIXNUM_LE(temp,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp)) {
			      case 1:
				gensymed_symbol = runtime_structure;
				temp_3 = 
					DOUBLE_FLOAT_TO_DOUBLE(previous_value);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
				store_managed_number_or_value_arg_1 = 
					temp_3 + temp_2 / 2.0;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)7L),
					DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
				SVREF(gensymed_symbol,FIX((SI_Long)7L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)1L);
				store_managed_number_or_value_arg = k_value;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)3L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)3L)) = 
					temp_1;
				break;
			      case 2:
				gensymed_symbol = runtime_structure;
				temp_3 = 
					DOUBLE_FLOAT_TO_DOUBLE(previous_value);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
				store_managed_number_or_value_arg_1 = 
					temp_3 + temp_2 / 2.0;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)8L),
					DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
				SVREF(gensymed_symbol,FIX((SI_Long)8L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)2L);
				store_managed_number_or_value_arg = k_value;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)4L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)4L)) = 
					temp_1;
				break;
			      case 3:
				gensymed_symbol = runtime_structure;
				temp_3 = 
					DOUBLE_FLOAT_TO_DOUBLE(previous_value);
				temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
				store_managed_number_or_value_arg_1 = 
					temp_3 + temp_2;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)9L),
					DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
				SVREF(gensymed_symbol,FIX((SI_Long)9L)) = 
					temp_1;
				ISVREF(gensymed_symbol,(SI_Long)12L) = 
					FIX((SI_Long)3L);
				store_managed_number_or_value_arg = k_value;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)5L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)5L)) = 
					temp_1;
				break;
			      case 4:
				gensymed_symbol = runtime_structure;
				store_managed_number_or_value_arg = k_value;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)6L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)6L)) = 
					temp_1;
				k_value = Nil;
				gensymed_symbol_3 = 1.0 / 6.0;
				managed_number = ISVREF(runtime_structure,
					(SI_Long)3L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L)
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(managed_number,
					    (SI_Long)0L);
				else if (INLINE_LONG_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L) {
				    temp = aref1(managed_number,
					    FIX((SI_Long)0L));
				    gensymed_symbol_4 = 
					    DOUBLE_FLOAT_TO_DOUBLE(temp);
				}
				else
				    gensymed_symbol_4 = 
					    DOUBLE_FLOAT_TO_DOUBLE(managed_number);
				gensymed_symbol_5 = 2.0;
				managed_number = ISVREF(runtime_structure,
					(SI_Long)4L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L)
				    gensymed_symbol_6 = 
					    DFLOAT_ISAREF_1(managed_number,
					    (SI_Long)0L);
				else if (INLINE_LONG_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L) {
				    temp = aref1(managed_number,
					    FIX((SI_Long)0L));
				    gensymed_symbol_6 = 
					    DOUBLE_FLOAT_TO_DOUBLE(temp);
				}
				else
				    gensymed_symbol_6 = 
					    DOUBLE_FLOAT_TO_DOUBLE(managed_number);
				gensymed_symbol_5 = gensymed_symbol_5 * 
					gensymed_symbol_6;
				gensymed_symbol_6 = 2.0;
				managed_number = ISVREF(runtime_structure,
					(SI_Long)5L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L)
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(managed_number,
					    (SI_Long)0L);
				else if (INLINE_LONG_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L) {
				    temp = aref1(managed_number,
					    FIX((SI_Long)0L));
				    gensymed_symbol_7 = 
					    DOUBLE_FLOAT_TO_DOUBLE(temp);
				}
				else
				    gensymed_symbol_7 = 
					    DOUBLE_FLOAT_TO_DOUBLE(managed_number);
				gensymed_symbol_6 = gensymed_symbol_6 * 
					gensymed_symbol_7;
				managed_number = ISVREF(runtime_structure,
					(SI_Long)6L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L)
				    gensymed_symbol_7 = 
					    DFLOAT_ISAREF_1(managed_number,
					    (SI_Long)0L);
				else if (INLINE_LONG_VECTOR_P(managed_number) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
					== (SI_Long)1L) {
				    temp = aref1(managed_number,
					    FIX((SI_Long)0L));
				    gensymed_symbol_7 = 
					    DOUBLE_FLOAT_TO_DOUBLE(temp);
				}
				else
				    gensymed_symbol_7 = 
					    DOUBLE_FLOAT_TO_DOUBLE(managed_number);
				gensymed_symbol_4 = gensymed_symbol_4 + 
					gensymed_symbol_5 + 
					gensymed_symbol_6 + gensymed_symbol_7;
				k_value = 
					DOUBLE_TO_DOUBLE_FLOAT(gensymed_symbol_3 
					* gensymed_symbol_4);
				managed_number_or_value = 
					ISVREF(runtime_structure,(SI_Long)1L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    current_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    current_value = 
					    aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    current_value = 
					    copy_text_string(managed_number_or_value);
				else
				    current_value = managed_number_or_value;
				if (NUMBERP(current_value)) {
				    temp = lfloat(current_value,
					    float_constant);
				    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
				    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
				    new_value = 
					    DOUBLE_TO_DOUBLE_FLOAT(temp_3 
					    + temp_2);
				}
				else
				    new_value = Simulation_no_value;
				gensymed_symbol = runtime_structure;
				gensymed_symbol_1 = ISVREF(gensymed_symbol,
					(SI_Long)16L);
				gensymed_symbol_2 = new_value;
				type_specification = 
					type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
				if (EQ(type_specification,Qfloat) && 
					FIXNUMP(gensymed_symbol_2)) {
				    store_managed_number_or_value_arg_1 = 
					    (double)IFIX(gensymed_symbol_2);
				    temp_1 = 
					    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					    (SI_Long)2L),
					    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_1;
				}
				else {
				    if (EQ(type_specification,Qinteger))
					temp = FIXNUMP(gensymed_symbol_2) ?
						 T : Nil;
				    else if (EQ(type_specification,Qlong))
					temp = 
						INLINE_LONG_P(gensymed_symbol_2) 
						!= (SI_Long)0L ? T : Nil;
				    else if (EQ(type_specification,Qfloat))
					temp = FLOATP(gensymed_symbol_2) ? 
						T : Nil;
				    else if (EQ(type_specification,Qsymbol))
					temp = gensymed_symbol_2 ? 
						(SYMBOLP(gensymed_symbol_2) 
						? T : Nil) : Qnil;
				    else if (EQ(type_specification,Qtext))
					temp = 
						text_string_p(gensymed_symbol_2);
				    else if (EQ(type_specification,
					    Qtruth_value))
					temp = FIXNUMP(gensymed_symbol_2) 
						&& FIXNUM_LE(Falsity,
						gensymed_symbol_2) ? 
						(FIXNUM_LE(gensymed_symbol_2,
						Truth) ? T : Nil) : Qnil;
				    else if (EQ(type_specification,Qboolean)) {
					if (FIXNUMP(gensymed_symbol_2)) {
					    temp = 
						    FIXNUM_EQ(gensymed_symbol_2,
						    Falsity) ? T : Nil;
					    if (temp);
					    else
						temp = 
							FIXNUM_EQ(gensymed_symbol_2,
							Truth) ? T : Nil;
					}
					else
					    temp = Nil;
				    }
				    else if (EQ(type_specification,
					    Qnumber) || 
					    EQ(type_specification,
					    Qinteger) || 
					    EQ(type_specification,Qfloat) 
					    || EQ(type_specification,
					    Qlong) || 
					    lookup_global_or_kb_specific_property_value(type_specification,
					    Numeric_data_type_gkbprop)) {
					temp = FLOATP(gensymed_symbol_2) ? 
						T : Nil;
					if (temp);
					else
					    temp = 
						    FIXNUMP(gensymed_symbol_2) 
						    ? T : Nil;
				    }
				    else
					temp = Nil;
				    if (temp) {
					store_managed_number_or_value_arg 
						= gensymed_symbol_2;
					temp_1 = 
						store_managed_number_or_value_function(ISVREF(gensymed_symbol,
						(SI_Long)2L),
						store_managed_number_or_value_arg);
					SVREF(gensymed_symbol,
						FIX((SI_Long)2L)) = temp_1;
				    }
				    else
					simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
						gensymed_symbol_2);
				}
				SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
				break;
			      default:
				break;
			    }
		    }
		    else {
			top_of_stack = Cached_top_of_stack;
			message_1 = tformat_stack_error_text_string(2,
				string_constant_5,Current_computation_frame);
			raw_stack_error_named_error(top_of_stack,message_1);
		    }
		}
		else {
		    k_value = evaluation_value_value(new_evaluation_value);
		    runtime_structure = Current_simulation_runtime_structure;
		    if (NUMBERP(k_value)) {
			gensymed_symbol = 
				ISVREF(ISVREF(ISVREF(runtime_structure,
				(SI_Long)11L),(SI_Long)1L),(SI_Long)2L);
			integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
			micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
			if (IFIX(micro_time) == (SI_Long)0L) {
			    temp_1 = Simulation_time_managed_float;
			    aref_new_value = (double)IFIX(integer_portion);
			    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
			}
			else {
			    temp_1 = Simulation_time_managed_float;
			    aref_new_value = (double)IFIX(integer_portion) 
				    + (double)IFIX(micro_time) / 100000.0;
			    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
			}
			h = Simulation_time_managed_float;
			temp = lfloat(k_value,float_constant);
			temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			k_value = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(h,
				(SI_Long)0L) * temp_2);
			managed_number_or_value = ISVREF(runtime_structure,
				(SI_Long)1L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    current_value = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    current_value = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    current_value = 
				    copy_text_string(managed_number_or_value);
			else
			    current_value = managed_number_or_value;
			if (NUMBERP(current_value)) {
			    temp = lfloat(current_value,float_constant);
			    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp);
			    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(k_value);
			    new_value = DOUBLE_TO_DOUBLE_FLOAT(temp_3 + 
				    temp_2);
			}
			else
			    new_value = Simulation_no_value;
			gensymed_symbol = runtime_structure;
			gensymed_symbol_1 = ISVREF(gensymed_symbol,
				(SI_Long)16L);
			gensymed_symbol_2 = new_value;
			type_specification = 
				type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
			if (EQ(type_specification,Qfloat) && 
				FIXNUMP(gensymed_symbol_2)) {
			    store_managed_number_or_value_arg_1 = 
				    (double)IFIX(gensymed_symbol_2);
			    temp_1 = 
				    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
				    (SI_Long)2L),
				    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg_1));
			    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
			}
			else {
			    if (EQ(type_specification,Qinteger))
				temp = FIXNUMP(gensymed_symbol_2) ? T : Nil;
			    else if (EQ(type_specification,Qlong))
				temp = INLINE_LONG_P(gensymed_symbol_2) != 
					(SI_Long)0L ? T : Nil;
			    else if (EQ(type_specification,Qfloat))
				temp = FLOATP(gensymed_symbol_2) ? T : Nil;
			    else if (EQ(type_specification,Qsymbol))
				temp = gensymed_symbol_2 ? 
					(SYMBOLP(gensymed_symbol_2) ? T : 
					Nil) : Qnil;
			    else if (EQ(type_specification,Qtext))
				temp = text_string_p(gensymed_symbol_2);
			    else if (EQ(type_specification,Qtruth_value))
				temp = FIXNUMP(gensymed_symbol_2) && 
					FIXNUM_LE(Falsity,
					gensymed_symbol_2) ? 
					(FIXNUM_LE(gensymed_symbol_2,
					Truth) ? T : Nil) : Qnil;
			    else if (EQ(type_specification,Qboolean)) {
				if (FIXNUMP(gensymed_symbol_2)) {
				    temp = FIXNUM_EQ(gensymed_symbol_2,
					    Falsity) ? T : Nil;
				    if (temp);
				    else
					temp = FIXNUM_EQ(gensymed_symbol_2,
						Truth) ? T : Nil;
				}
				else
				    temp = Nil;
			    }
			    else if (EQ(type_specification,Qnumber) || 
				    EQ(type_specification,Qinteger) || 
				    EQ(type_specification,Qfloat) || 
				    EQ(type_specification,Qlong) || 
				    lookup_global_or_kb_specific_property_value(type_specification,
				    Numeric_data_type_gkbprop)) {
				temp = FLOATP(gensymed_symbol_2) ? T : Nil;
				if (temp);
				else
				    temp = FIXNUMP(gensymed_symbol_2) ? T :
					     Nil;
			    }
			    else
				temp = Nil;
			    if (temp) {
				store_managed_number_or_value_arg = 
					gensymed_symbol_2;
				temp_1 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)2L),
					store_managed_number_or_value_arg);
				SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
					temp_1;
			    }
			    else
				simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
					gensymed_symbol_2);
			}
			SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
		    }
		    else {
			top_of_stack = Cached_top_of_stack;
			message_1 = tformat_stack_error_text_string(2,
				string_constant_6,Current_computation_frame);
			raw_stack_error_named_error(top_of_stack,message_1);
		    }
		}
		if ( !TRUEP(Dont_proceed_to_next_variable_qm))
		    Set_of_variables_to_simulation_evaluate = 
			    ISVREF(Set_of_variables_to_simulation_evaluate,
			    (SI_Long)9L);
	    }
	    else if (EQ(Current_simulation_category,Qdiscrete_state)) {
		gensymed_symbol = Current_simulation_runtime_structure;
		gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)16L);
		gensymed_symbol_2 = new_evaluation_value;
		type_specification = 
			type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
		if (EQ(type_specification,Qfloat) && 
			FIXNUMP(gensymed_symbol_2)) {
		    store_managed_number_or_value_arg = 
			    lfloat(gensymed_symbol_2,float_constant);
		    temp_1 = 
			    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
			    (SI_Long)2L),store_managed_number_or_value_arg);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
		}
		else if (type_specification_type_p(gensymed_symbol_2,
			type_specification)) {
		    temp_1 = 
			    reclaim_managed_number_or_value_function(ISVREF(gensymed_symbol,
			    (SI_Long)2L));
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
		    temp_1 = FIXNUMP(gensymed_symbol_2) || 
			    SYMBOLP(gensymed_symbol_2) ? gensymed_symbol_2 
			    : copy_evaluation_value_1(gensymed_symbol_2);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
		}
		else
		    simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
			    evaluation_value_value(gensymed_symbol_2));
		SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
		if ( !TRUEP(Dont_proceed_to_next_variable_qm))
		    Set_of_variables_to_simulation_evaluate = 
			    ISVREF(Set_of_variables_to_simulation_evaluate,
			    (SI_Long)9L);
	    }
	}
    }
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* "~NF" */

/* WRITE-SIMULATION-FORMULA-TRACE-ENTRY */
Object write_simulation_formula_trace_entry(simulation_formula)
    Object simulation_formula;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(185,17);
    sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Generic_simulation_formula_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
    }
    if (temp)
	return tformat(2,string_constant_7,simulation_formula);
    else
	return VALUES_1(Nil);
}

static Object string_constant_8;   /* "Exiting execution of ~NF." */

/* SIMULATION-FORMULA-TRACE-EXIT-MESSAGE */
Object simulation_formula_trace_exit_message(simulation_formula)
    Object simulation_formula;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(185,18);
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
	      sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,
		      (SI_Long)1L),(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Generic_simulation_formula_class_description,
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
	      if (temp);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(simulation_formula,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Simulation_subtable_class_description,
			  (SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
		  if (sub_class_vector_index < 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			      {
		      gensymed_symbol = 
			      UBYTE_8_ISAREF_1(sub_class_bit_vector,
			      sub_class_vector_index);
		      gensymed_symbol_1 = (SI_Long)1L;
		      gensymed_symbol_2 = superior_class_bit_number & 
			      (SI_Long)7L;
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
	      }
	      if (temp)
		  tformat(2,string_constant_8,simulation_formula);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qsuppress_first_update;  /* suppress-first-update */

static Object list_constant;       /* # */

/* SET-INFO-FOR-NEXT-VARIABLE-TO-SIMULATE-1 */
Object set_info_for_next_variable_to_simulate_1(rest_of_structures)
    Object rest_of_structures;
{
    Object runtime_structure_qm, variable, gensymed_symbol, gensymed_symbol_1;
    Object value_computed_qm, temp_1;
    char temp;

    x_note_fn_call(185,19);
    runtime_structure_qm = ISVREF(rest_of_structures,(SI_Long)1L);
    variable = Nil;
    if (runtime_structure_qm) {
	variable = ISVREF(runtime_structure_qm,(SI_Long)16L);
	gensymed_symbol = runtime_structure_qm;
	gensymed_symbol_1 = ISVREF(ISVREF(gensymed_symbol,(SI_Long)11L),
		(SI_Long)1L);
	if (gensymed_symbol_1 && ISVREF(gensymed_symbol_1,(SI_Long)4L) ? 
		(EQ(ISVREF(gensymed_symbol,(SI_Long)13L),
		Qsuppress_first_update) ? TRUEP(Nil) : TRUEP(T)) : 
		    TRUEP(Nil)) {
	    SVREF(runtime_structure_qm,FIX((SI_Long)13L)) = T;
	    temp =  !EQ(Current_simulation_category,Qdependent);
	    if (temp);
	    else {
		value_computed_qm = ISVREF(runtime_structure_qm,(SI_Long)12L);
		if (value_computed_qm && NUMBERP(value_computed_qm) && 
			ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)3L);
		    if ( !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			temp = TRUEP(Nil);
		    else
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    temp = IFIX(value_computed_qm) == (SI_Long)1L;
			    break;
			  case 2:
			    temp = IFIX(value_computed_qm) == (SI_Long)2L;
			    break;
			  case 3:
			    temp = IFIX(value_computed_qm) == (SI_Long)3L;
			    break;
			  case 4:
			    temp = IFIX(value_computed_qm) == (SI_Long)4L;
			    break;
			  default:
			    temp = TRUEP(Nil);
			    break;
			}
		}
		else
		    temp = TRUEP(value_computed_qm);
		temp =  !temp;
	    }
	    if (temp) {
		Current_simulation_runtime_structure = runtime_structure_qm;
		Current_computation_instance = variable;
		Current_computation_component_particulars = Nil;
		Current_computation_frame = ISVREF(runtime_structure_qm,
			(SI_Long)21L);
		temp_1 = Current_computation_frame;
	    }
	    else {
		Current_computation_instance = Nil;
		temp_1 = Current_computation_instance;
	    }
	}
	else if (ISVREF(runtime_structure_qm,(SI_Long)25L)) {
	    SVREF(runtime_structure_qm,FIX((SI_Long)13L)) = T;
	    Current_simulation_runtime_structure = runtime_structure_qm;
	    Current_computation_instance = variable;
	    Current_computation_component_particulars = list_constant;
	    Current_computation_frame = ISVREF(runtime_structure_qm,
		    (SI_Long)21L);
	    temp_1 = Current_computation_frame;
	}
	else {
	    if (state_variable_p(variable)) {
		if ( !EQ(ISVREF(runtime_structure_qm,(SI_Long)13L),
			Qsuppress_first_update))
		    SVREF(runtime_structure_qm,FIX((SI_Long)13L)) = Nil;
	    }
	    else
		SVREF(runtime_structure_qm,FIX((SI_Long)13L)) = Nil;
	    Current_computation_instance = Nil;
	    temp_1 = Current_computation_instance;
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* SET-INFO-FOR-EVALUATION-ONLY */
Object set_info_for_evaluation_only(rest_of_structures)
    Object rest_of_structures;
{
    Object runtime_structure, variable;

    x_note_fn_call(185,20);
    runtime_structure = ISVREF(rest_of_structures,(SI_Long)1L);
    variable = ISVREF(runtime_structure,(SI_Long)16L);
    Current_simulation_runtime_structure = runtime_structure;
    Current_computation_instance = variable;
    Current_computation_frame = ISVREF(runtime_structure,(SI_Long)21L);
    return VALUES_1(Current_computation_frame);
}

/* CALCULATE-NEW-VALUES-FOR-CONTINUOUS-STATE-VARIABLES */
Object calculate_new_values_for_continuous_state_variables(set_of_continuous_state_variables,
	    other_args,resumption_qm)
    Object set_of_continuous_state_variables, other_args, resumption_qm;
{
    x_note_fn_call(185,21);
    return process_n_variables_in_stack_eval(set_of_continuous_state_variables,
	    Qcontinuous_state);
}

/* CALCULATE-NEW-VALUES-FOR-DISCRETE-STATE-VARIABLES */
Object calculate_new_values_for_discrete_state_variables(set_of_discrete_state_variables,
	    other_args,resumption_qm)
    Object set_of_discrete_state_variables, other_args, resumption_qm;
{
    x_note_fn_call(185,22);
    return process_n_variables_in_stack_eval(set_of_discrete_state_variables,
	    Qdiscrete_state);
}

/* CALCULATE-NEW-VALUES-FOR-DEPENDENT-VARIABLES */
Object calculate_new_values_for_dependent_variables(set_of_dependent_variables,
	    other_args,resumption_qm)
    Object set_of_dependent_variables, other_args, resumption_qm;
{
    x_note_fn_call(185,23);
    return process_n_variables_in_stack_eval(set_of_dependent_variables,
	    Qdependent);
}

/* SIM-EVAL-GET-VALUE-OF-VARIABLE */
Object sim_eval_get_value_of_variable(variable)
    Object variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure_qm;
    Object loop_encountered_qm, svref_arg_1, managed_number_or_value, temp_1;
    Object gensymed_symbol, gensymed_symbol_1, value_computed_qm, result_1;
    char temp;

    x_note_fn_call(185,24);
    if (variable) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	variable_simulation_runtime_structure_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    }
    else
	variable_simulation_runtime_structure_qm = Nil;
    if (variable_simulation_runtime_structure_qm) {
	if ( !TRUEP(Do_not_update_simulated_value_qm) &&  
		!EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)2L),
		Qcalculating_state_variables)) {
	    loop_encountered_qm = 
		    ISVREF(variable_simulation_runtime_structure_qm,
		    (SI_Long)23L);
	    if (loop_encountered_qm);
	    else
		loop_encountered_qm = Current_simulation_runtime_structure 
			? (EQ(variable_simulation_runtime_structure_qm,
			Current_simulation_runtime_structure) ? T : Nil) : 
			Qnil;
	    if (loop_encountered_qm) {
		svref_arg_1 = Current_model_runtime_info_qm;
		SVREF(svref_arg_1,FIX((SI_Long)31L)) = T;
	    }
	    temp = TRUEP(loop_encountered_qm);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (externally_simulated_variable_p(variable)) {
	    managed_number_or_value = 
		    ISVREF(variable_simulation_runtime_structure_qm,
		    (SI_Long)1L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_1 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp_1 = copy_text_string(managed_number_or_value);
	    else
		temp_1 = managed_number_or_value;
	}
	else {
	    gensymed_symbol = variable_simulation_runtime_structure_qm;
	    temp = TRUEP(Do_not_update_simulated_value_qm);
	    if (temp);
	    else {
		gensymed_symbol_1 = ISVREF(ISVREF(gensymed_symbol,
			(SI_Long)11L),(SI_Long)1L);
		temp =  !(gensymed_symbol_1 && ISVREF(gensymed_symbol_1,
			(SI_Long)4L) ? (EQ(ISVREF(gensymed_symbol,
			(SI_Long)13L),Qsuppress_first_update) ? TRUEP(Nil) 
			: TRUEP(T)) : TRUEP(Nil));
	    }
	    if (temp) {
		managed_number_or_value = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			!= (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			== (SI_Long)1L)
		    temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
		else if (text_string_p(managed_number_or_value))
		    temp_1 = copy_text_string(managed_number_or_value);
		else
		    temp_1 = managed_number_or_value;
	    }
	    else if (EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)2L),
		    Qcalculating_state_variables)) {
		if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    if (discrete_state_variable_p(ISVREF(gensymed_symbol,
			    (SI_Long)16L))) {
			managed_number_or_value = ISVREF(gensymed_symbol,
				(SI_Long)1L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp_1 = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp_1 = copy_text_string(managed_number_or_value);
			else
			    temp_1 = managed_number_or_value;
		    }
		    else {
			temp_1 = ISVREF(Current_model_runtime_info_qm,
				(SI_Long)3L);
			if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    temp_1 = Nil;
			else
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				managed_number_or_value = 
					ISVREF(gensymed_symbol,(SI_Long)1L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp_1 = 
					    copy_text_string(managed_number_or_value);
				else
				    temp_1 = managed_number_or_value;
				break;
			      case 2:
				managed_number_or_value = 
					ISVREF(gensymed_symbol,(SI_Long)7L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp_1 = 
					    copy_text_string(managed_number_or_value);
				else
				    temp_1 = managed_number_or_value;
				break;
			      case 3:
				managed_number_or_value = 
					ISVREF(gensymed_symbol,(SI_Long)8L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp_1 = 
					    copy_text_string(managed_number_or_value);
				else
				    temp_1 = managed_number_or_value;
				break;
			      case 4:
				managed_number_or_value = 
					ISVREF(gensymed_symbol,(SI_Long)9L);
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					!= (SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					== (SI_Long)1L)
				    temp_1 = aref1(managed_number_or_value,
					    FIX((SI_Long)0L));
				else if (text_string_p(managed_number_or_value))
				    temp_1 = 
					    copy_text_string(managed_number_or_value);
				else
				    temp_1 = managed_number_or_value;
				break;
			      default:
				temp_1 = Nil;
				break;
			    }
		    }
		}
		else {
		    managed_number_or_value = ISVREF(gensymed_symbol,
			    (SI_Long)1L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			temp_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			temp_1 = copy_text_string(managed_number_or_value);
		    else
			temp_1 = managed_number_or_value;
		}
	    }
	    else {
		value_computed_qm = ISVREF(gensymed_symbol,(SI_Long)12L);
		if (value_computed_qm && NUMBERP(value_computed_qm) && 
			ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)3L);
		    if ( !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			temp = TRUEP(Nil);
		    else
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    temp = IFIX(value_computed_qm) == (SI_Long)1L;
			    break;
			  case 2:
			    temp = IFIX(value_computed_qm) == (SI_Long)2L;
			    break;
			  case 3:
			    temp = IFIX(value_computed_qm) == (SI_Long)3L;
			    break;
			  case 4:
			    temp = IFIX(value_computed_qm) == (SI_Long)4L;
			    break;
			  default:
			    temp = TRUEP(Nil);
			    break;
			}
		}
		else
		    temp = TRUEP(value_computed_qm);
		if (temp) {
		    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
			if (discrete_state_variable_p(ISVREF(gensymed_symbol,
				(SI_Long)16L))) {
			    managed_number_or_value = 
				    ISVREF(gensymed_symbol,(SI_Long)2L);
			    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				temp_1 = 
					DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					(SI_Long)0L));
			    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				    != (SI_Long)0L && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				    == (SI_Long)1L)
				temp_1 = aref1(managed_number_or_value,
					FIX((SI_Long)0L));
			    else if (text_string_p(managed_number_or_value))
				temp_1 = 
					copy_text_string(managed_number_or_value);
			    else
				temp_1 = managed_number_or_value;
			}
			else {
			    result_1 = Nil;
			    temp_1 = ISVREF(Current_model_runtime_info_qm,
				    (SI_Long)3L);
			    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) 
				    && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp_1)) {
				  case 4:
				    managed_number_or_value = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					result_1 = 
						copy_text_string(managed_number_or_value);
				    else
					result_1 = managed_number_or_value;
				    break;
				  case 1:
				    managed_number_or_value = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)7L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					result_1 = 
						copy_text_string(managed_number_or_value);
				    else
					result_1 = managed_number_or_value;
				    break;
				  case 2:
				    managed_number_or_value = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)8L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					result_1 = 
						copy_text_string(managed_number_or_value);
				    else
					result_1 = managed_number_or_value;
				    break;
				  case 3:
				    managed_number_or_value = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)9L);
				    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
						(SI_Long)0L));
				    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
					    != (SI_Long)0L && 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
					    == (SI_Long)1L)
					result_1 = 
						aref1(managed_number_or_value,
						FIX((SI_Long)0L));
				    else if (text_string_p(managed_number_or_value))
					result_1 = 
						copy_text_string(managed_number_or_value);
				    else
					result_1 = managed_number_or_value;
				    break;
				  default:
				    break;
				}
			    temp_1 = result_1;
			}
		    }
		    else {
			managed_number_or_value = ISVREF(gensymed_symbol,
				(SI_Long)2L);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				== (SI_Long)1L)
			    temp_1 = aref1(managed_number_or_value,
				    FIX((SI_Long)0L));
			else if (text_string_p(managed_number_or_value))
			    temp_1 = copy_text_string(managed_number_or_value);
			else
			    temp_1 = managed_number_or_value;
		    }
		}
		else
		    temp_1 = 
			    sim_eval_calculate_new_value_for_variable(gensymed_symbol);
	    }
	}
    }
    else
	temp_1 = Simulation_no_value;
    return VALUES_1(temp_1);
}

/* SIM-EVAL-GET-EVALUATION-VALUE-OF-VARIABLE */
Object sim_eval_get_evaluation_value_of_variable(variable)
    Object variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure_qm;
    Object loop_encountered_qm, svref_arg_1, simulation_value;
    Object runtime_structure, temp_1, value, gensymed_symbol;
    Object gensymed_symbol_1, managed_value, value_computed_qm;
    char temp, logical_qm;

    x_note_fn_call(185,25);
    if (variable) {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	variable_simulation_runtime_structure_qm = simulation_info_qm ? 
		ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    }
    else
	variable_simulation_runtime_structure_qm = Nil;
    if (variable_simulation_runtime_structure_qm) {
	if ( !TRUEP(Do_not_update_simulated_value_qm) &&  
		!EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)2L),
		Qcalculating_state_variables)) {
	    loop_encountered_qm = 
		    ISVREF(variable_simulation_runtime_structure_qm,
		    (SI_Long)23L);
	    if (loop_encountered_qm);
	    else
		loop_encountered_qm = Current_simulation_runtime_structure 
			? (EQ(variable_simulation_runtime_structure_qm,
			Current_simulation_runtime_structure) ? T : Nil) : 
			Qnil;
	    if (loop_encountered_qm) {
		svref_arg_1 = Current_model_runtime_info_qm;
		SVREF(svref_arg_1,FIX((SI_Long)31L)) = T;
	    }
	    temp = TRUEP(loop_encountered_qm);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (externally_simulated_variable_p(variable)) {
	    simulation_value = 
		    ISVREF(variable_simulation_runtime_structure_qm,
		    (SI_Long)1L);
	    runtime_structure = variable_simulation_runtime_structure_qm;
	    if (CONSP(simulation_value) && EQ(M_CDR(simulation_value),
		    Qtruth_value))
		temp_1 = FIXNUMP(simulation_value) || 
			SYMBOLP(simulation_value) ? simulation_value : 
			copy_evaluation_value_1(simulation_value);
	    else {
		logical_qm = EQ(ISVREF(ISVREF(runtime_structure,
			(SI_Long)16L),(SI_Long)20L),Qtruth_value);
		value = simulation_value;
		if (logical_qm) {
		    if (FIXNUM_EQ(value,Truth))
			temp_1 = Evaluation_true_value;
		    else if (FIXNUM_EQ(value,Falsity))
			temp_1 = Evaluation_false_value;
		    else
			temp_1 = eval_cons_1(value,Qtruth_value);
		}
		else
		    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L ? copy_wide_string(value) : 
			    FIXNUMP(value) || SYMBOLP(value) ? value : 
			    copy_evaluation_value_1(value);
	    }
	}
	else {
	    gensymed_symbol = variable_simulation_runtime_structure_qm;
	    temp = TRUEP(Do_not_update_simulated_value_qm);
	    if (temp);
	    else {
		gensymed_symbol_1 = ISVREF(ISVREF(gensymed_symbol,
			(SI_Long)11L),(SI_Long)1L);
		temp =  !(gensymed_symbol_1 && ISVREF(gensymed_symbol_1,
			(SI_Long)4L) ? (EQ(ISVREF(gensymed_symbol,
			(SI_Long)13L),Qsuppress_first_update) ? TRUEP(Nil) 
			: TRUEP(T)) : TRUEP(Nil));
	    }
	    if (temp) {
		simulation_value = ISVREF(gensymed_symbol,(SI_Long)1L);
		runtime_structure = gensymed_symbol;
		if (CONSP(simulation_value) && EQ(M_CDR(simulation_value),
			Qtruth_value))
		    temp_1 = FIXNUMP(simulation_value) || 
			    SYMBOLP(simulation_value) ? simulation_value : 
			    copy_evaluation_value_1(simulation_value);
		else {
		    logical_qm = EQ(ISVREF(ISVREF(runtime_structure,
			    (SI_Long)16L),(SI_Long)20L),Qtruth_value);
		    value = simulation_value;
		    if (logical_qm) {
			if (FIXNUM_EQ(value,Truth))
			    temp_1 = Evaluation_true_value;
			else if (FIXNUM_EQ(value,Falsity))
			    temp_1 = Evaluation_false_value;
			else
			    temp_1 = eval_cons_1(value,Qtruth_value);
		    }
		    else
			temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) 
				!= (SI_Long)0L ? copy_wide_string(value) : 
				FIXNUMP(value) || SYMBOLP(value) ? value : 
				copy_evaluation_value_1(value);
		}
	    }
	    else if (EQ(ISVREF(Current_model_runtime_info_qm,(SI_Long)2L),
		    Qcalculating_state_variables)) {
		managed_value = Nil;
		if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    if (discrete_state_variable_p(ISVREF(gensymed_symbol,
			    (SI_Long)16L)))
			managed_value = ISVREF(gensymed_symbol,(SI_Long)1L);
		    else {
			temp_1 = ISVREF(Current_model_runtime_info_qm,
				(SI_Long)3L);
			if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
				FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			    switch (INTEGER_TO_CHAR(temp_1)) {
			      case 1:
				managed_value = ISVREF(gensymed_symbol,
					(SI_Long)1L);
				break;
			      case 2:
				managed_value = ISVREF(gensymed_symbol,
					(SI_Long)7L);
				break;
			      case 3:
				managed_value = ISVREF(gensymed_symbol,
					(SI_Long)8L);
				break;
			      case 4:
				managed_value = ISVREF(gensymed_symbol,
					(SI_Long)9L);
				break;
			      default:
				break;
			    }
		    }
		}
		else
		    managed_value = ISVREF(gensymed_symbol,(SI_Long)1L);
		if (CONSP(managed_value) && EQ(M_CDR(managed_value),
			Qtruth_value))
		    temp_1 = FIXNUMP(managed_value) || 
			    SYMBOLP(managed_value) ? managed_value : 
			    copy_evaluation_value_1(managed_value);
		else {
		    logical_qm = EQ(ISVREF(ISVREF(gensymed_symbol,
			    (SI_Long)16L),(SI_Long)20L),Qtruth_value);
		    value = managed_value;
		    if (logical_qm) {
			if (FIXNUM_EQ(value,Truth))
			    temp_1 = Evaluation_true_value;
			else if (FIXNUM_EQ(value,Falsity))
			    temp_1 = Evaluation_false_value;
			else
			    temp_1 = eval_cons_1(value,Qtruth_value);
		    }
		    else
			temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) 
				!= (SI_Long)0L ? copy_wide_string(value) : 
				FIXNUMP(value) || SYMBOLP(value) ? value : 
				copy_evaluation_value_1(value);
		}
	    }
	    else {
		value_computed_qm = ISVREF(gensymed_symbol,(SI_Long)12L);
		if (value_computed_qm && NUMBERP(value_computed_qm) && 
			ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
		    temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)3L);
		    if ( !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			temp = TRUEP(Nil);
		    else
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    temp = IFIX(value_computed_qm) == (SI_Long)1L;
			    break;
			  case 2:
			    temp = IFIX(value_computed_qm) == (SI_Long)2L;
			    break;
			  case 3:
			    temp = IFIX(value_computed_qm) == (SI_Long)3L;
			    break;
			  case 4:
			    temp = IFIX(value_computed_qm) == (SI_Long)4L;
			    break;
			  default:
			    temp = TRUEP(Nil);
			    break;
			}
		}
		else
		    temp = TRUEP(value_computed_qm);
		if (temp) {
		    managed_value = Nil;
		    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
			if (discrete_state_variable_p(ISVREF(gensymed_symbol,
				(SI_Long)16L)))
			    managed_value = ISVREF(gensymed_symbol,
				    (SI_Long)2L);
			else {
			    temp_1 = ISVREF(Current_model_runtime_info_qm,
				    (SI_Long)3L);
			    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp_1) 
				    && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
				switch (INTEGER_TO_CHAR(temp_1)) {
				  case 4:
				    managed_value = ISVREF(gensymed_symbol,
					    (SI_Long)2L);
				    break;
				  case 1:
				    managed_value = ISVREF(gensymed_symbol,
					    (SI_Long)7L);
				    break;
				  case 2:
				    managed_value = ISVREF(gensymed_symbol,
					    (SI_Long)8L);
				    break;
				  case 3:
				    managed_value = ISVREF(gensymed_symbol,
					    (SI_Long)9L);
				    break;
				  default:
				    break;
				}
			}
		    }
		    else
			managed_value = ISVREF(gensymed_symbol,(SI_Long)2L);
		    if (CONSP(managed_value) && EQ(M_CDR(managed_value),
			    Qtruth_value))
			temp_1 = FIXNUMP(managed_value) || 
				SYMBOLP(managed_value) ? managed_value : 
				copy_evaluation_value_1(managed_value);
		    else {
			logical_qm = EQ(ISVREF(ISVREF(gensymed_symbol,
				(SI_Long)16L),(SI_Long)20L),Qtruth_value);
			value = managed_value;
			if (logical_qm) {
			    if (FIXNUM_EQ(value,Truth))
				temp_1 = Evaluation_true_value;
			    else if (FIXNUM_EQ(value,Falsity))
				temp_1 = Evaluation_false_value;
			    else
				temp_1 = eval_cons_1(value,Qtruth_value);
			}
			else
			    temp_1 = 
				    INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) 
				    != (SI_Long)0L ? 
				    copy_wide_string(value) : 
				    FIXNUMP(value) || SYMBOLP(value) ? 
				    value : copy_evaluation_value_1(value);
		    }
		}
		else
		    temp_1 = 
			    sim_eval_calculate_new_evaluation_value_for_variable(gensymed_symbol);
	    }
	}
    }
    else
	temp_1 = Simulation_no_value;
    return VALUES_1(temp_1);
}

/* SIM-EVAL-GET-VALUE-OF-PARAMETER */
Object sim_eval_get_value_of_parameter(parameter)
    Object parameter;
{
    Object simulated_value, managed_number_or_value;

    x_note_fn_call(185,26);
    simulated_value = sim_eval_get_value_of_variable(parameter);
    if ( !EQ(simulated_value,Simulation_no_value))
	return VALUES_1(simulated_value);
    else {
	managed_number_or_value = ISVREF(parameter,(SI_Long)23L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L)));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    return aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    return copy_text_string(managed_number_or_value);
	else
	    return VALUES_1(managed_number_or_value);
    }
}

/* SIM-EVAL-GET-EVALUATION-VALUE-OF-PARAMETER */
Object sim_eval_get_evaluation_value_of_parameter(parameter)
    Object parameter;
{
    Object simulated_value, temp, value;
    char logical_qm;

    x_note_fn_call(185,27);
    simulated_value = sim_eval_get_evaluation_value_of_variable(parameter);
    if ( !EQ(simulated_value,Simulation_no_value))
	temp = simulated_value;
    else {
	logical_qm = EQ(ISVREF(parameter,(SI_Long)20L),Qtruth_value);
	value = ISVREF(parameter,(SI_Long)23L);
	if (logical_qm) {
	    if (FIXNUM_EQ(value,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(value,Qtruth_value);
	}
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L ?
		     copy_wide_string(value) : FIXNUMP(value) || 
		    SYMBOLP(value) ? value : copy_evaluation_value_1(value);
    }
    return VALUES_1(temp);
}

static Object Qunknown_encountered;  /* unknown-encountered */

static Object string_constant_9;   /* "" */

/* SIM-EVAL-CALCULATE-NEW-VALUE-FOR-VARIABLE */
Object sim_eval_calculate_new_value_for_variable(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    Object variable, simulation_info_qm, simulation_runtime_information_qm;
    Object svref_arg_1, simulate_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value, top_of_stack, message_1, temp;

    x_note_fn_call(185,28);
    variable = ISVREF(variable_simulation_runtime_structure,(SI_Long)16L);
    if (dependent_variable_p(variable) || Initializing_state_variables_qm) {
	if (EQ(Current_environment,Qsimulator)) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(Current_computation_instance,
		    Qsimulation_info_qm,Nil);
	    simulation_runtime_information_qm = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    if ( !TRUEP(ISVREF(simulation_runtime_information_qm,
		    (SI_Long)23L))) {
		svref_arg_1 = Current_model_runtime_info_qm;
		simulate_push_modify_macro_arg = Current_computation_instance;
		car_1 = simulate_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)30L);
		svref_new_value = simulate_cons_1(car_1,cdr_1);
		SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
		simulation_info_qm = 
			get_lookup_slot_value_given_default(Current_computation_instance,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		SVREF(svref_arg_1,FIX((SI_Long)23L)) = T;
	    }
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    simulation_runtime_information_qm = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    if ( !TRUEP(ISVREF(simulation_runtime_information_qm,
		    (SI_Long)23L))) {
		svref_arg_1 = Current_model_runtime_info_qm;
		simulate_push_modify_macro_arg = variable;
		car_1 = simulate_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)30L);
		svref_new_value = simulate_cons_1(car_1,cdr_1);
		SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		SVREF(svref_arg_1,FIX((SI_Long)23L)) = T;
	    }
	    Stack_expiration = Nil;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qunknown_encountered;
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_9);
	    temp = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    Stack_expiration = Nil;
	    temp = Stack_expiration;
	}
    }
    else if (state_variable_p(variable))
	temp = sim_eval_calculate_new_value_for_state_variable(variable);
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* SIM-EVAL-CALCULATE-NEW-EVALUATION-VALUE-FOR-VARIABLE */
Object sim_eval_calculate_new_evaluation_value_for_variable(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    Object variable, simulation_info_qm, simulation_runtime_information_qm;
    Object svref_arg_1, simulate_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value, top_of_stack, message_1, temp;

    x_note_fn_call(185,29);
    variable = ISVREF(variable_simulation_runtime_structure,(SI_Long)16L);
    if (dependent_variable_p(variable) || Initializing_state_variables_qm) {
	if (EQ(Current_environment,Qsimulator)) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(Current_computation_instance,
		    Qsimulation_info_qm,Nil);
	    simulation_runtime_information_qm = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    if ( !TRUEP(ISVREF(simulation_runtime_information_qm,
		    (SI_Long)23L))) {
		svref_arg_1 = Current_model_runtime_info_qm;
		simulate_push_modify_macro_arg = Current_computation_instance;
		car_1 = simulate_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)30L);
		svref_new_value = simulate_cons_1(car_1,cdr_1);
		SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
		simulation_info_qm = 
			get_lookup_slot_value_given_default(Current_computation_instance,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		SVREF(svref_arg_1,FIX((SI_Long)23L)) = T;
	    }
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    simulation_runtime_information_qm = simulation_info_qm ? 
		    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    if ( !TRUEP(ISVREF(simulation_runtime_information_qm,
		    (SI_Long)23L))) {
		svref_arg_1 = Current_model_runtime_info_qm;
		simulate_push_modify_macro_arg = variable;
		car_1 = simulate_push_modify_macro_arg;
		cdr_1 = ISVREF(svref_arg_1,(SI_Long)30L);
		svref_new_value = simulate_cons_1(car_1,cdr_1);
		SVREF(svref_arg_1,FIX((SI_Long)30L)) = svref_new_value;
		simulation_info_qm = 
			get_lookup_slot_value_given_default(variable,
			Qsimulation_info_qm,Nil);
		svref_arg_1 = simulation_info_qm ? 
			ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
		SVREF(svref_arg_1,FIX((SI_Long)23L)) = T;
	    }
	    Stack_expiration = Nil;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qunknown_encountered;
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_9);
	    temp = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    Stack_expiration = Nil;
	    temp = Stack_expiration;
	}
    }
    else if (state_variable_p(variable))
	temp = 
		sim_eval_calculate_new_evaluation_value_for_state_variable(variable);
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* SIM-EVAL-CALCULATE-NEW-VALUE-FOR-STATE-VARIABLE */
Object sim_eval_calculate_new_value_for_state_variable(state_variable)
    Object state_variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure;
    Object managed_number_or_value, temp, result_1;

    x_note_fn_call(185,30);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(state_variable,
	    Qsimulation_info_qm,Nil);
    variable_simulation_runtime_structure = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
	if (discrete_state_variable_p(ISVREF(variable_simulation_runtime_structure,
		(SI_Long)16L))) {
	    managed_number_or_value = 
		    ISVREF(variable_simulation_runtime_structure,(SI_Long)2L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else if (text_string_p(managed_number_or_value))
		temp = copy_text_string(managed_number_or_value);
	    else
		temp = managed_number_or_value;
	}
	else {
	    result_1 = Nil;
	    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)3L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 4:
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)2L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			result_1 = copy_text_string(managed_number_or_value);
		    else
			result_1 = managed_number_or_value;
		    break;
		  case 1:
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)7L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			result_1 = copy_text_string(managed_number_or_value);
		    else
			result_1 = managed_number_or_value;
		    break;
		  case 2:
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)8L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			result_1 = copy_text_string(managed_number_or_value);
		    else
			result_1 = managed_number_or_value;
		    break;
		  case 3:
		    managed_number_or_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)9L);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			    == (SI_Long)1L)
			result_1 = aref1(managed_number_or_value,
				FIX((SI_Long)0L));
		    else if (text_string_p(managed_number_or_value))
			result_1 = copy_text_string(managed_number_or_value);
		    else
			result_1 = managed_number_or_value;
		    break;
		  default:
		    break;
		}
	    temp = result_1;
	}
    }
    else {
	managed_number_or_value = 
		ISVREF(variable_simulation_runtime_structure,(SI_Long)2L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else if (text_string_p(managed_number_or_value))
	    temp = copy_text_string(managed_number_or_value);
	else
	    temp = managed_number_or_value;
    }
    return VALUES_1(temp);
}

/* SIM-EVAL-CALCULATE-NEW-EVALUATION-VALUE-FOR-STATE-VARIABLE */
Object sim_eval_calculate_new_evaluation_value_for_state_variable(state_variable)
    Object state_variable;
{
    Object simulation_info_qm, variable_simulation_runtime_structure;
    Object managed_value, temp, value;
    char logical_qm;

    x_note_fn_call(185,31);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(state_variable,
	    Qsimulation_info_qm,Nil);
    variable_simulation_runtime_structure = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    managed_value = Nil;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)3L)) {
	if (discrete_state_variable_p(ISVREF(variable_simulation_runtime_structure,
		(SI_Long)16L)))
	    managed_value = ISVREF(variable_simulation_runtime_structure,
		    (SI_Long)2L);
	else {
	    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)3L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 4:
		    managed_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)2L);
		    break;
		  case 1:
		    managed_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)7L);
		    break;
		  case 2:
		    managed_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)8L);
		    break;
		  case 3:
		    managed_value = 
			    ISVREF(variable_simulation_runtime_structure,
			    (SI_Long)9L);
		    break;
		  default:
		    break;
		}
	}
    }
    else
	managed_value = ISVREF(variable_simulation_runtime_structure,
		(SI_Long)2L);
    if (CONSP(managed_value) && EQ(M_CDR(managed_value),Qtruth_value))
	temp = FIXNUMP(managed_value) || SYMBOLP(managed_value) ? 
		managed_value : copy_evaluation_value_1(managed_value);
    else {
	logical_qm = 
		EQ(ISVREF(ISVREF(variable_simulation_runtime_structure,
		(SI_Long)16L),(SI_Long)20L),Qtruth_value);
	value = managed_value;
	if (logical_qm) {
	    if (FIXNUM_EQ(value,Truth))
		temp = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		temp = Evaluation_false_value;
	    else
		temp = eval_cons_1(value,Qtruth_value);
	}
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L ?
		     copy_wide_string(value) : FIXNUMP(value) || 
		    SYMBOLP(value) ? value : copy_evaluation_value_1(value);
    }
    return VALUES_1(temp);
}

static Object Qupdate_state_variable;  /* update-state-variable */

static Object Qupdate_dependent_variable;  /* update-dependent-variable */

/* UPDATE-VARIABLES */
Object update_variables()
{
    Object current_computation_frame, current_computation_instance;
    Declare_special(2);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(185,32);
    current_computation_frame = Nil;
    current_computation_instance = 
	    lookup_kb_specific_property_value(Qsimulator_data_server,
	    Data_server_kbprop);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      0);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)19L),Qupdate_state_variable);
	    for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)20L),Qupdate_state_variable);
	    result = for_each_element_in_installation_set(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)21L),Qupdate_dependent_variable);
	}
	POP_LOCAL_ALLOCATION(0,0);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* UPDATE-STATE-VARIABLE */
Object update_state_variable(state_variable)
    Object state_variable;
{
    Object simulation_info_qm, runtime_structure, update_variable_qm;

    x_note_fn_call(185,33);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(state_variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    update_variable_qm = ISVREF(runtime_structure,(SI_Long)13L);
    if (update_variable_qm) {
	if (EQ(update_variable_qm,Qsuppress_first_update))
	    return VALUES_1(SVREF(runtime_structure,FIX((SI_Long)13L)) = Nil);
	else
	    return update_variable(state_variable);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-DEPENDENT-VARIABLE */
Object update_dependent_variable(dependent_variable)
    Object dependent_variable;
{
    Object simulation_info_qm, runtime_structure, update_variable_qm;

    x_note_fn_call(185,34);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(dependent_variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)1L) : Nil;
    update_variable_qm = ISVREF(runtime_structure,(SI_Long)13L);
    if (update_variable_qm)
	return update_variable(dependent_variable);
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

static Object Qsend_one_value;     /* send-one-value */

static Object Qlong_time_ago;      /* long-time-ago */

/* UPDATE-VARIABLE */
Object update_variable(variable_or_parameter)
    Object variable_or_parameter;
{
    Object simulation_info, simulation_subtable_qm;
    Object simulation_runtime_structure;
    Object simulation_stored_history_specification_qm;
    Object new_simulation_value_box, temp, sub_class_bit_vector;
    Object interval_at_which_to_send_value_to_inference_engine;
    Object last_time_value_sent_to_inference_engine, time_of_request_qm, value;
    Object temp_2, one_shot_and_interval_request_pending_qm;
    Object new_simulation_value, put_current_value_called_from_simulator_p;
    Object temp_3, gensymed_symbol_3, integer_portion, micro_time;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(185,35);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(variable_or_parameter);
    simulation_info = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    simulation_subtable_qm = ISVREF(simulation_info,(SI_Long)15L) ? 
	    get_lookup_slot_value(variable_or_parameter,
	    Qsimulation_details) : Nil;
    simulation_runtime_structure = ISVREF(simulation_info,(SI_Long)1L);
    simulation_stored_history_specification_qm = simulation_subtable_qm ? 
	    ISVREF(simulation_subtable_qm,(SI_Long)21L) : Nil;
    new_simulation_value_box = ISVREF(simulation_runtime_structure,
	    (SI_Long)2L);
    Current_computation_frame = variable_or_parameter;
    temp = 
	    reclaim_managed_number_or_value_function(ISVREF(simulation_runtime_structure,
	    (SI_Long)1L));
    SVREF(simulation_runtime_structure,FIX((SI_Long)1L)) = temp;
    temp = FIXNUMP(new_simulation_value_box) || 
	    SYMBOLP(new_simulation_value_box) ? new_simulation_value_box : 
	    copy_evaluation_value_1(new_simulation_value_box);
    SVREF(simulation_runtime_structure,FIX((SI_Long)1L)) = temp;
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	temp_1 = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	interval_at_which_to_send_value_to_inference_engine = 
		ISVREF(simulation_runtime_structure,(SI_Long)14L);
	last_time_value_sent_to_inference_engine = 
		ISVREF(simulation_runtime_structure,(SI_Long)15L);
	time_of_request_qm = Nil;
	if (interval_at_which_to_send_value_to_inference_engine) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_simulation_value_box) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		    == (SI_Long)1L)
		value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_simulation_value_box,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(new_simulation_value_box) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		    == (SI_Long)1L)
		value = aref1(new_simulation_value_box,FIX((SI_Long)0L));
	    else
		value = new_simulation_value_box;
	    temp_1 =  !EQ(value,Simulation_no_value);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (EQ(CAR(interval_at_which_to_send_value_to_inference_engine),
		    Qsend_one_value)) {
		temp_2 = 
			CDR(interval_at_which_to_send_value_to_inference_engine);
		time_of_request_qm = 
			simulator_almost_up_to_date_qm(CONSP(temp_2) ? 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CADR(interval_at_which_to_send_value_to_inference_engine),
			(SI_Long)0L)) : 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CDR(interval_at_which_to_send_value_to_inference_engine),
			(SI_Long)0L)));
	    }
	    else
		time_of_request_qm = Nil;
	    if (time_of_request_qm) {
		temp_2 = 
			CDR(interval_at_which_to_send_value_to_inference_engine);
		if (CONSP(temp_2)) {
		    temp = 
			    CDDR(interval_at_which_to_send_value_to_inference_engine);
		    SVREF(simulation_runtime_structure,FIX((SI_Long)14L)) 
			    = temp;
		    M_CDDR(interval_at_which_to_send_value_to_inference_engine) 
			    = Nil;
		    reclaim_interval_at_which_to_send_value_to_inference_engine(interval_at_which_to_send_value_to_inference_engine);
		}
		else {
		    reclaim_interval_at_which_to_send_value_to_inference_engine(interval_at_which_to_send_value_to_inference_engine);
		    SVREF(simulation_runtime_structure,FIX((SI_Long)14L)) 
			    = Nil;
		}
	    }
	    else {
		if (EQ(last_time_value_sent_to_inference_engine,
			Qlong_time_ago)) {
		    temp_2 = 
			    CDR(interval_at_which_to_send_value_to_inference_engine);
		    temp_2 = simulator_almost_up_to_date_qm(CONSP(temp_2) ?
			     
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CDDDR(interval_at_which_to_send_value_to_inference_engine),
			    (SI_Long)0L)) : 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(CDR(interval_at_which_to_send_value_to_inference_engine),
			    (SI_Long)0L)));
		}
		else
		    temp_2 = Nil;
		if (temp_2);
		else {
		    one_shot_and_interval_request_pending_qm = Nil;
		    if ( !EQ(last_time_value_sent_to_inference_engine,
			    Qlong_time_ago)) {
			temp_1 =  
				!EQ(CAR(interval_at_which_to_send_value_to_inference_engine),
				Qsend_one_value);
			if (temp_1);
			else {
			    temp_2 = 
				    CDR(interval_at_which_to_send_value_to_inference_engine);
			    one_shot_and_interval_request_pending_qm = 
				    CONSP(temp_2) ? T : Nil;
			    temp_1 = 
				    TRUEP(one_shot_and_interval_request_pending_qm);
			}
		    }
		    else
			temp_1 = TRUEP(Nil);
		    temp_2 = temp_1 ? 
			    simulator_almost_up_to_date_qm(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(one_shot_and_interval_request_pending_qm 
			    ? 
			    THIRD(interval_at_which_to_send_value_to_inference_engine) 
			    : 
			    CAR(interval_at_which_to_send_value_to_inference_engine),
			    (SI_Long)0L) + 
			    DFLOAT_ISAREF_1(last_time_value_sent_to_inference_engine,
			    (SI_Long)0L))) : Nil;
		}
		time_of_request_qm = temp_2;
	    }
	}
	if (time_of_request_qm) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_simulation_value_box) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		    == (SI_Long)1L)
		temp_2 = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_simulation_value_box,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(new_simulation_value_box) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		    == (SI_Long)1L)
		temp_2 = aref1(new_simulation_value_box,FIX((SI_Long)0L));
	    else
		temp_2 = new_simulation_value_box;
	    put_simulated_value_to_inference_engine(3,
		    variable_or_parameter,temp_2,
		    compute_g2_time_for_simulation_time(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)6L)));
	    set_last_time_value_sent_to_inference_engine(simulation_runtime_structure,
		    time_of_request_qm);
	}
    }
    else {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    new_simulation_value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_simulation_value_box,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    new_simulation_value = aref1(new_simulation_value_box,
		    FIX((SI_Long)0L));
	else
	    new_simulation_value = new_simulation_value_box;
	if ( !EQ(new_simulation_value,Simulation_no_value)) {
	    put_current_value_called_from_simulator_p = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Put_current_value_called_from_simulator_p,Qput_current_value_called_from_simulator_p,put_current_value_called_from_simulator_p,
		    0);
	      put_simulated_value_to_inference_engine(3,
		      variable_or_parameter,new_simulation_value,
		      compute_g2_time_for_simulation_time(ISVREF(Current_model_runtime_info_qm,
		      (SI_Long)6L)));
	    POP_SPECIAL();
	}
    }
    if (simulation_stored_history_specification_qm) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_simulation_value_box,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    value = aref1(new_simulation_value_box,FIX((SI_Long)0L));
	else
	    value = new_simulation_value_box;
	temp_1 =  !EQ(value,Simulation_no_value);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp_2 = get_or_make_history_buffer(simulation_subtable_qm,
		simulation_stored_history_specification_qm);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    temp_3 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_simulation_value_box,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(new_simulation_value_box) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_simulation_value_box)) 
		== (SI_Long)1L)
	    temp_3 = aref1(new_simulation_value_box,FIX((SI_Long)0L));
	else if (text_string_p(new_simulation_value_box))
	    temp_3 = copy_text_string(new_simulation_value_box);
	else
	    temp_3 = new_simulation_value_box;
	gensymed_symbol_3 = ISVREF(Current_model_runtime_info_qm,(SI_Long)6L);
	integer_portion = ISVREF(gensymed_symbol_3,(SI_Long)1L);
	micro_time = ISVREF(gensymed_symbol_3,(SI_Long)2L);
	if (IFIX(micro_time) == (SI_Long)0L) {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	else {
	    temp = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion) + 
		    (double)IFIX(micro_time) / 100000.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	}
	store_history_value(temp_2,
		simulation_stored_history_specification_qm,temp_3,
		Simulation_time_managed_float,T);
    }
    SVREF(simulation_runtime_structure,FIX((SI_Long)12L)) = Nil;
    return VALUES_1(Nil);
}

/* SIMULATOR-ALMOST-UP-TO-DATE? */
Object simulator_almost_up_to_date_qm(time_1)
    Object time_1;
{
    Object accumulator_compound_fixnum_simulation_time, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, macro_time_1, micro_time_1;
    Object macro_time_2, micro_time_2, svref_new_value, integer_portion;
    Object micro_time;
    double current_simulation_float_time, arg, arg_1;

    x_note_fn_call(185,36);
    accumulator_compound_fixnum_simulation_time = 
	    make_compound_fixnum_simulation_time_1();
    gensymed_symbol = accumulator_compound_fixnum_simulation_time;
    gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)5L);
    gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)7L);
    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
    if (IFIX(micro_time_2) != (SI_Long)0L) {
	micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	if (FIXNUM_GE(micro_time_1,
		Fraction_modulus_of_compound_fixnum_simulation_time)) {
	    svref_new_value = FIXNUM_MINUS(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	    macro_time_1 = FIXNUM_ADD1(macro_time_1);
	}
	else
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
    }
    else {
	if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
    }
    svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
    gensymed_symbol = accumulator_compound_fixnum_simulation_time;
    gensymed_symbol_1 = accumulator_compound_fixnum_simulation_time;
    gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)8L);
    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
    if (IFIX(micro_time_2) != (SI_Long)0L) {
	micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
	if (FIXNUM_GE(micro_time_1,
		Fraction_modulus_of_compound_fixnum_simulation_time)) {
	    svref_new_value = FIXNUM_MINUS(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	    macro_time_1 = FIXNUM_ADD1(macro_time_1);
	}
	else
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
    }
    else {
	if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1);
    }
    svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
    gensymed_symbol = accumulator_compound_fixnum_simulation_time;
    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
    current_simulation_float_time = IFIX(micro_time) == (SI_Long)0L ? 
	    (double)IFIX(integer_portion) : (double)IFIX(integer_portion) 
	    + (double)IFIX(micro_time) / 100000.0;
    reclaim_compound_fixnum_simulation_time(accumulator_compound_fixnum_simulation_time);
    arg = current_simulation_float_time;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(time_1);
    if ( !(arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)))
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(current_simulation_float_time));
    else
	return VALUES_1(Nil);
}

/* SIMULATOR-TIME-LAG */
Object simulator_time_lag()
{
    Object current_model_runtime_info_qm, current_model_definition_qm, code;
    Object accumulator_compound_fixnum_simulation_time, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, macro_time_1, micro_time_1;
    Object macro_time_2, micro_time_2, svref_new_value, integer_portion;
    Object micro_time, temp_2;
    char temp;
    double temp_1, gensymed_symbol_3;
    Declare_special(2);
    Object result;

    x_note_fn_call(185,37);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Nil) {
	    Current_model_runtime_info_qm = Nil;
	    Current_model_definition_qm = Nil;
	}
	else {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		Current_model_runtime_info_qm = Main_model_runtime_info;
		Current_model_definition_qm = Nil;
	    }
	}
	if (Current_model_runtime_info_qm) {
	    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
		code = M_CAR(M_CDR(Edit_type_alias_mapping));
		temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
			(SI_Long)0L : TRUEP(Qnil);
		if (temp);
		else
		    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		accumulator_compound_fixnum_simulation_time = 
			make_compound_fixnum_simulation_time_1();
		gensymed_symbol = accumulator_compound_fixnum_simulation_time;
		gensymed_symbol_1 = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)5L);
		gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,
			(SI_Long)7L);
		macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		if (IFIX(micro_time_2) != (SI_Long)0L) {
		    micro_time_1 = FIXNUM_ADD(micro_time_1,micro_time_2);
		    if (FIXNUM_GE(micro_time_1,
			    Fraction_modulus_of_compound_fixnum_simulation_time)) 
				{
			svref_new_value = FIXNUM_MINUS(micro_time_1,
				Fraction_modulus_of_compound_fixnum_simulation_time);
			SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				svref_new_value;
			macro_time_1 = FIXNUM_ADD1(macro_time_1);
		    }
		    else
			SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
		}
		else {
		    if (SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				micro_time_1);
		}
		svref_new_value = FIXNUM_ADD(macro_time_1,macro_time_2);
		SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		temp_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) - 
			(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			(SI_Long)0L) - temp_1);
		gensymed_symbol = accumulator_compound_fixnum_simulation_time;
		integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
		micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
		gensymed_symbol_3 = temp_1 - ((IFIX(micro_time) == 
			(SI_Long)0L ? (double)IFIX(integer_portion) : 
			(double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0) + 1.0);
		gensymed_symbol = float_constant;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol);
		temp_2 = DOUBLE_TO_DOUBLE_FLOAT(MAX(gensymed_symbol_3,temp_1));
		reclaim_compound_fixnum_simulation_time(accumulator_compound_fixnum_simulation_time);
		result = VALUES_1(temp_2);
	    }
	    else
		result = VALUES_1(float_constant);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* STATE-VARIABLE-P */
Object state_variable_p(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(185,38);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)2L) :
	     Nil,Qcontinuous_state) ? T : Nil;
    if (temp);
    else {
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,
		(SI_Long)2L) : Nil,Qdiscrete_state) ? T : Nil;
    }
    return VALUES_1(temp);
}

/* CONTINUOUS-STATE-VARIABLE-P */
Object continuous_state_variable_p(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(185,39);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)2L) :
	     Nil,Qcontinuous_state) ? T : Nil;
    return VALUES_1(temp);
}

/* DISCRETE-STATE-VARIABLE-P */
Object discrete_state_variable_p(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(185,40);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)2L) :
	     Nil,Qdiscrete_state) ? T : Nil;
    return VALUES_1(temp);
}

/* DEPENDENT-VARIABLE-P */
Object dependent_variable_p(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(185,41);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)2L) :
	     Nil,Qdependent) ? T : Nil;
    return VALUES_1(temp);
}

static Object Qexternal;           /* external */

/* EXTERNALLY-SIMULATED-VARIABLE-P */
Object externally_simulated_variable_p(variable)
    Object variable;
{
    Object simulation_info_qm, temp;

    x_note_fn_call(185,42);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    temp = EQ(simulation_info_qm ? ISVREF(simulation_info_qm,(SI_Long)2L) :
	     Nil,Qexternal) ? T : Nil;
    return VALUES_1(temp);
}

void simulate2_INIT()
{
    Object AB_package, Qsimulation_initial_value, list_constant_2, Qsimulate2;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_1, Qsimulate1;
    Object Qrestart_simulator_after_procedure, Qsimulate_one_cycle;

    x_note_fn_call(185,43);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qno_work_done_yet_for_this_cycle = 
	    STATIC_SYMBOL("NO-WORK-DONE-YET-FOR-THIS-CYCLE",AB_package);
    Qnew_values_computed = STATIC_SYMBOL("NEW-VALUES-COMPUTED",AB_package);
    Qcalculate_new_values_for_variables = 
	    STATIC_SYMBOL("CALCULATE-NEW-VALUES-FOR-VARIABLES",AB_package);
    Qsimulate_one_cycle = STATIC_SYMBOL("SIMULATE-ONE-CYCLE",AB_package);
    SET_SYMBOL_FUNCTION(Qsimulate_one_cycle,
	    STATIC_FUNCTION(simulate_one_cycle,NIL,FALSE,3,3));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcontinue_data_server_data_acceptance = 
	    STATIC_SYMBOL("CONTINUE-DATA-SERVER-DATA-ACCEPTANCE",AB_package);
    Qsimulator_data_server = STATIC_SYMBOL("SIMULATOR-DATA-SERVER",AB_package);
    Qwork_completed_for_this_cycle = 
	    STATIC_SYMBOL("WORK-COMPLETED-FOR-THIS-CYCLE",AB_package);
    Qsimulation_procedure_completion_form = 
	    STATIC_SYMBOL("SIMULATION-PROCEDURE-COMPLETION-FORM",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_procedure_completion_form,
	    Simulation_procedure_completion_form);
    Qsimulate1 = STATIC_SYMBOL("SIMULATE1",AB_package);
    Qrestart_simulator_after_procedure = 
	    STATIC_SYMBOL("RESTART-SIMULATOR-AFTER-PROCEDURE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,
	    Qrestart_simulator_after_procedure,Qnil);
    record_system_variable(Qsimulation_procedure_completion_form,
	    Qsimulate1,list_constant_1,Qnil,Qnil,Qnil,Qt);
    string_constant = 
	    STATIC_STRING("~a is given as the simulation procedure in the simulation-parameters ~\n          system table, but no procedure with that name exists.");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_1 = 
	    STATIC_STRING("~a is given as the simulation procedure in the simulation-parameters ~\n          system table, but this names the constant value ~NC.");
    string_constant_2 = 
	    STATIC_STRING("~a is given as the simulation procedure in the simulation-parameters ~\n          system table, but this names a ~a, not a procedure.");
    string_constant_3 = 
	    string_append2(STATIC_STRING("~a is given as the simulation procedure in the simulation-parameters ~\n          system table, but this procedure is either inactive, is not enabled ~\n          for running wh"),
	    STATIC_STRING("ile inactive, or has a status other than OK."));
    string_constant_4 = 
	    STATIC_STRING("Error starting simulation procedure ~NF: ~a");
    Qeuler = STATIC_SYMBOL("EULER",AB_package);
    Qrk4 = STATIC_SYMBOL("RK4",AB_package);
    SET_SYMBOL_FUNCTION(Qcalculate_new_values_for_variables,
	    STATIC_FUNCTION(calculate_new_values_for_variables,NIL,FALSE,3,3));
    Qcalculating_state_variables = 
	    STATIC_SYMBOL("CALCULATING-STATE-VARIABLES",AB_package);
    Qcontinuous_state_done = STATIC_SYMBOL("CONTINUOUS-STATE-DONE",AB_package);
    Qcalculate_new_values_for_continuous_state_variables = 
	    STATIC_SYMBOL("CALCULATE-NEW-VALUES-FOR-CONTINUOUS-STATE-VARIABLES",
	    AB_package);
    Qdiscrete_state_done = STATIC_SYMBOL("DISCRETE-STATE-DONE",AB_package);
    Qcalculate_new_values_for_discrete_state_variables = 
	    STATIC_SYMBOL("CALCULATE-NEW-VALUES-FOR-DISCRETE-STATE-VARIABLES",
	    AB_package);
    Qcalculating_dependent_variables = 
	    STATIC_SYMBOL("CALCULATING-DEPENDENT-VARIABLES",AB_package);
    Qdependent_done = STATIC_SYMBOL("DEPENDENT-DONE",AB_package);
    Qcalculate_new_values_for_dependent_variables = 
	    STATIC_SYMBOL("CALCULATE-NEW-VALUES-FOR-DEPENDENT-VARIABLES",
	    AB_package);
    Qwithin_simulator_for_stack_error_qm = 
	    STATIC_SYMBOL("WITHIN-SIMULATOR-FOR-STACK-ERROR\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwithin_simulator_for_stack_error_qm,
	    Within_simulator_for_stack_error_qm);
    Qsimulate2 = STATIC_SYMBOL("SIMULATE2",AB_package);
    record_system_variable(Qwithin_simulator_for_stack_error_qm,Qsimulate2,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qdependent = STATIC_SYMBOL("DEPENDENT",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    float_constant = STATIC_FLOAT(0.0);
    Qcontinuous_state = STATIC_SYMBOL("CONTINUOUS-STATE",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    string_constant_5 = 
	    STATIC_STRING("Error while integrating ~NF.  The equation for the derivative did ~\nnot evaluate to a number.");
    string_constant_6 = 
	    STATIC_STRING("Error while integrating ~NF.  The equation for the derivative did ~\n        not evaluate to a number.");
    Qdiscrete_state = STATIC_SYMBOL("DISCRETE-STATE",AB_package);
    string_constant_7 = STATIC_STRING("~NF");
    string_constant_8 = STATIC_STRING("Exiting execution of ~NF.");
    Qsuppress_first_update = STATIC_SYMBOL("SUPPRESS-FIRST-UPDATE",AB_package);
    Qsimulation_initial_value = STATIC_SYMBOL("SIMULATION-INITIAL-VALUE",
	    AB_package);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qsimulation_initial_value,
	    Qcurrent_computation_frame);
    SET_SYMBOL_FUNCTION(Qcalculate_new_values_for_continuous_state_variables,
	    STATIC_FUNCTION(calculate_new_values_for_continuous_state_variables,
	    NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qcalculate_new_values_for_discrete_state_variables,
	    STATIC_FUNCTION(calculate_new_values_for_discrete_state_variables,
	    NIL,FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qcalculate_new_values_for_dependent_variables,
	    STATIC_FUNCTION(calculate_new_values_for_dependent_variables,
	    NIL,FALSE,3,3));
    Qunknown_encountered = STATIC_SYMBOL("UNKNOWN-ENCOUNTERED",AB_package);
    string_constant_9 = STATIC_STRING("");
    Qupdate_state_variable = STATIC_SYMBOL("UPDATE-STATE-VARIABLE",AB_package);
    Qupdate_dependent_variable = STATIC_SYMBOL("UPDATE-DEPENDENT-VARIABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_state_variable,
	    STATIC_FUNCTION(update_state_variable,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qupdate_dependent_variable,
	    STATIC_FUNCTION(update_dependent_variable,NIL,FALSE,1,1));
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qsend_one_value = STATIC_SYMBOL("SEND-ONE-VALUE",AB_package);
    Qlong_time_ago = STATIC_SYMBOL("LONG-TIME-AGO",AB_package);
    Qexternal = STATIC_SYMBOL("EXTERNAL",AB_package);
}
