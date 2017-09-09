/* smlt5.c
 * Input file:  simulate5.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "smlt5.h"


static Object Qintegration_algorithm_for_model;  /* integration-algorithm-for-model */

static Object Qrk4;                /* rk4 */

/* PUT-INTEGRATION-ALGORITHM-FOR-MODEL */
Object put_integration_algorithm_for_model(frame,new_value,gensymed_symbol)
    Object frame, new_value, gensymed_symbol;
{
    Object svref_arg_1;

    x_note_fn_call(187,0);
    if (EQ(get_lookup_slot_value(frame,Qintegration_algorithm_for_model),
	    Qrk4) &&  !EQ(new_value,Qrk4) && ISVREF(frame,(SI_Long)20L)) {
	svref_arg_1 = ISVREF(frame,(SI_Long)20L);
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qintegration_algorithm_for_model);
    return set_lookup_slot_value_1(frame,Qintegration_algorithm_for_model,
	    new_value);
}

/* MODEL-RUNTIME-INFO-FUNCTION? */
Object model_runtime_info_function_qm(frame)
    Object frame;
{
    x_note_fn_call(187,1);
    return VALUES_1(ISVREF(frame,(SI_Long)20L));
}

static Object Qfloat_array;        /* float-array */

/* INITIALIZE-DEFAULT-SIMULATION-TIME-INCREMENT-FOR-MODEL */
Object initialize_default_simulation_time_increment_for_model()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(187,2);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.5);
    return VALUES_1(new_float);
}

static Object Qsynchronously;      /* synchronously */

/* INITIALIZE-SIMULATION-CONTROL-SPECIFICATIONS */
Object initialize_simulation_control_specifications()
{
    x_note_fn_call(187,3);
    return slot_value_cons_1(Qsynchronously,Nil);
}

static Object Qmodel_simulation_status;  /* model-simulation-status */

static Object Qpaused;             /* paused */

/* MODEL-PAUSED? */
Object model_paused_qm(model)
    Object model;
{
    Object model_definition_qm;

    x_note_fn_call(187,4);
    model_definition_qm = ISVREF(model,(SI_Long)28L);
    if (model_definition_qm)
	return VALUES_1(EQ(get_lookup_slot_value(model_definition_qm,
		Qmodel_simulation_status),Qpaused) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qmodel_definition;   /* model-definition */

static Object Qitems_belonging_to_this_model;  /* items-belonging-to-this-model */

/* CLEANUP-FOR-MODEL-DEFINITION */
Object cleanup_for_model_definition(model_definition)
    Object model_definition;
{
    Object frame, sub_vector_qm, method_function_qm, model_runtime_info_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(187,5);
    frame = model_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmodel_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    change_slot_value(3,model_definition,Qitems_belonging_to_this_model,Nil);
    model_runtime_info_qm = ISVREF(model_definition,(SI_Long)20L);
    if (memq_function(model_runtime_info_qm,
	    ISVREF(get_model_queue_for_model(model_runtime_info_qm),
	    (SI_Long)1L)))
	return shutdown_simulator(2,model_runtime_info_qm,model_definition);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-MODEL-RUNTIME-INFO?-VALUE */
Object reclaim_model_runtime_info_qm_value(model_runtime_info_qm,
	    gensymed_symbol)
    Object model_runtime_info_qm, gensymed_symbol;
{
    Object current_model_runtime_info_qm;
    Declare_special(1);

    x_note_fn_call(187,6);
    if (model_runtime_info_qm) {
	current_model_runtime_info_qm = model_runtime_info_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		0);
	  reclaim_model_runtime_info_1(model_runtime_info_qm);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qsimulation_control_specifications;  /* simulation-control-specifications */

/* DONT-WAIT-FOR-MODEL-TO-FINISH-FUNCTION? */
Object dont_wait_for_model_to_finish_function_qm(model_runtime_info)
    Object model_runtime_info;
{
    Object model_definition_qm, temp;

    x_note_fn_call(187,7);
    model_definition_qm = ISVREF(model_runtime_info,(SI_Long)28L);
    if (model_definition_qm) {
	temp = get_lookup_slot_value(model_definition_qm,
		Qsimulation_control_specifications);
	return VALUES_1(THIRD(temp));
    }
    else
	return VALUES_1(Nil);
}

/* INCREMENT-SIMULATION-TIME-FOR-CURRENT-MODEL? */
Object increment_simulation_time_for_current_model_qm()
{
    Object model_definition_qm, temp;

    x_note_fn_call(187,8);
    model_definition_qm = ISVREF(Current_model_runtime_info_qm,(SI_Long)28L);
    temp =  !TRUEP(model_definition_qm) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = get_lookup_slot_value(model_definition_qm,
		Qsimulation_control_specifications);
	return VALUES_1( !TRUEP(SECOND(temp)) ? T : Nil);
    }
}

/* CURRENT-MODEL-IS-PAUSED? */
Object current_model_is_paused_qm()
{
    Object model_definition_qm;

    x_note_fn_call(187,9);
    model_definition_qm = ISVREF(Current_model_runtime_info_qm,(SI_Long)28L);
    if (model_definition_qm)
	return VALUES_1(EQ(get_lookup_slot_value(model_definition_qm,
		Qmodel_simulation_status),Qpaused) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qas_fast_as_possible;  /* as-fast-as-possible */

/* GET-MODEL-QUEUE-FOR-MODEL */
Object get_model_queue_for_model(model_runtime_info_qm)
    Object model_runtime_info_qm;
{
    Object model_definition_qm, key_for_queue_to_use, temp;

    x_note_fn_call(187,10);
    model_definition_qm = model_runtime_info_qm ? 
	    ISVREF(model_runtime_info_qm,(SI_Long)28L) : 
	    Current_model_definition_qm;
    key_for_queue_to_use = Nil;
    if (model_definition_qm) {
	temp = get_lookup_slot_value(model_definition_qm,
		Qsimulation_control_specifications);
	key_for_queue_to_use = FIRST(temp);
	if (EQ(key_for_queue_to_use,Qas_fast_as_possible))
	    return VALUES_1(As_fast_as_possible_model_queue);
	else
	    return VALUES_1(Synchronous_model_queue);
    }
    else
	return VALUES_1(Synchronous_model_queue);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

/* GET-MODEL-RUNTIME-INFO-FOR-VARIABLE */
Object get_model_runtime_info_for_variable(variable_or_parameter)
    Object variable_or_parameter;
{
    Object simulation_info_qm, model_definition_qm;

    x_note_fn_call(187,11);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    model_definition_qm = simulation_info_qm ? ISVREF(simulation_info_qm,
	    (SI_Long)8L) : Nil;
    if (model_definition_qm)
	return VALUES_1(ISVREF(model_definition_qm,(SI_Long)20L));
    else
	return VALUES_1(Main_model_runtime_info);
}

static Object Qdefault_simulation_time_increment_for_model;  /* default-simulation-time-increment-for-model */

/* CURRENT-DEFAULT-SIMULATION-TIME-INCREMENT */
Object current_default_simulation_time_increment()
{
    Object slot_value_number;

    x_note_fn_call(187,12);
    slot_value_number = Current_model_definition_qm ? 
	    get_lookup_slot_value(Current_model_definition_qm,
	    Qdefault_simulation_time_increment_for_model) : 
	    ISVREF(Simulation_parameters,(SI_Long)22L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
		(SI_Long)0L)));
    else if (INLINE_LONG_VECTOR_P(slot_value_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) == (SI_Long)1L)
	return aref1(slot_value_number,FIX((SI_Long)0L));
    else
	return VALUES_1(slot_value_number);
}

/* CURRENT-INTEGRATION-ALGORITHM */
Object current_integration_algorithm()
{
    x_note_fn_call(187,13);
    if (Current_model_definition_qm)
	return get_lookup_slot_value(Current_model_definition_qm,
		Qintegration_algorithm_for_model);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)23L));
}

static Object Qexternal_simulator_configuration_for_model;  /* external-simulator-configuration-for-model */

/* CURRENT-EXTERNAL-SIMULATOR-CONFIGURATION */
Object current_external_simulator_configuration()
{
    x_note_fn_call(187,14);
    if (Current_model_definition_qm)
	return get_lookup_slot_value_given_default(Current_model_definition_qm,
		Qexternal_simulator_configuration_for_model,Nil);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)26L));
}

static Object Qsimulation_procedure_for_model;  /* simulation-procedure-for-model */

/* CURRENT-SIMULATION-PROCEDURE */
Object current_simulation_procedure()
{
    x_note_fn_call(187,15);
    if (Current_model_definition_qm)
	return get_lookup_slot_value(Current_model_definition_qm,
		Qsimulation_procedure_for_model);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)27L));
}

static Object Qsend_all_values_at_beginning_of_cycle_for_model_qm;  /* send-all-values-at-beginning-of-cycle-for-model? */

/* CURRENT-SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE? */
Object current_send_all_values_at_beginning_of_cycle_qm()
{
    x_note_fn_call(187,16);
    if (Current_model_definition_qm)
	return get_lookup_slot_value(Current_model_definition_qm,
		Qsend_all_values_at_beginning_of_cycle_for_model_qm);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)28L));
}

static Object Qvector_from_external_simulator_for_model;  /* vector-from-external-simulator-for-model */

/* CURRENT-VECTOR-FROM-EXTERNAL-SIMULATOR */
Object current_vector_from_external_simulator()
{
    x_note_fn_call(187,17);
    if (Current_model_definition_qm)
	return get_lookup_slot_value_given_default(Current_model_definition_qm,
		Qvector_from_external_simulator_for_model,Nil);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)29L));
}

static Object Qvector_to_external_simulator_for_model;  /* vector-to-external-simulator-for-model */

/* CURRENT-VECTOR-TO-EXTERNAL-SIMULATOR */
Object current_vector_to_external_simulator()
{
    x_note_fn_call(187,18);
    if (Current_model_definition_qm)
	return get_lookup_slot_value_given_default(Current_model_definition_qm,
		Qvector_to_external_simulator_for_model,Nil);
    else
	return VALUES_1(ISVREF(Simulation_parameters,(SI_Long)30L));
}

static Object Qvector_from_external_simulator;  /* vector-from-external-simulator */

/* CHANGE-VECTOR-FROM-EXTERNAL-SIMULATOR */
Object change_vector_from_external_simulator(vector_1)
    Object vector_1;
{
    x_note_fn_call(187,19);
    if (Current_model_definition_qm)
	return change_slot_value(3,Current_model_definition_qm,
		Qvector_from_external_simulator_for_model,vector_1);
    else
	return change_slot_value(3,Simulation_parameters,
		Qvector_from_external_simulator,vector_1);
}

static Object Qvector_to_external_simulator;  /* vector-to-external-simulator */

/* CHANGE-VECTOR-TO-EXTERNAL-SIMULATOR */
Object change_vector_to_external_simulator(vector_1)
    Object vector_1;
{
    x_note_fn_call(187,20);
    if (Current_model_definition_qm)
	return change_slot_value(3,Current_model_definition_qm,
		Qvector_to_external_simulator_for_model,vector_1);
    else
	return change_slot_value(3,Simulation_parameters,
		Qvector_to_external_simulator,vector_1);
}

/* RESTART-SIMULATOR-AFTER-PROCEDURE */
Object restart_simulator_after_procedure(completion_form)
    Object completion_form;
{
    x_note_fn_call(187,21);
    return restart_simulator_after_procedure_1(SECOND(completion_form));
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* RESTART-SIMULATOR-AFTER-PROCEDURE-1 */
Object restart_simulator_after_procedure_1(model_definition_or_t)
    Object model_definition_or_t;
{
    Object current_model_runtime_info_qm, current_model_definition_qm, x2;
    Object svref_arg_1;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,22);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (SIMPLE_VECTOR_P(model_definition_or_t) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(model_definition_or_t)) > 
		(SI_Long)2L &&  !EQ(ISVREF(model_definition_or_t,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(model_definition_or_t,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    Current_model_definition_qm = model_definition_or_t;
	    Current_model_runtime_info_qm = ISVREF(model_definition_or_t,
		    (SI_Long)20L);
	}
	else {
	    Current_model_definition_qm = Nil;
	    Current_model_runtime_info_qm = Main_model_runtime_info;
	}
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)13L)) = T;
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
	if (System_is_running || System_has_paused)
	    result = end_simulation_procedure_or_external_simulation_cycle();
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-MODEL-RUNTIME-INFO-GIVEN-ICP-SOCKET */
Object get_model_runtime_info_given_icp_socket(icp_socket)
    Object icp_socket;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, md, model_runtime_info_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,23);
    if (Main_model_runtime_info && EQ(ISVREF(Main_model_runtime_info,
	    (SI_Long)14L),icp_socket))
	return VALUES_2(Main_model_runtime_info,Nil);
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	md = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  model_runtime_info_qm = Nil;
	  ab_loopvar_ = collect_subclasses(Qmodel_definition);
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
	  md = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  model_runtime_info_qm = ISVREF(md,(SI_Long)20L);
	  if (EQ(ISVREF(model_runtime_info_qm,(SI_Long)14L),icp_socket)) {
	      result = VALUES_2(model_runtime_info_qm,md);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

/* MAKE-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-WITH-MODEL */
Object make_variable_simulation_runtime_structure_with_model(variable)
    Object variable;
{
    Object current_model_runtime_info_qm, current_model_definition_qm;
    Object simulation_info_qm, model_definition_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,24);
    current_model_runtime_info_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	    1);
      current_model_definition_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	      0);
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	model_definition_qm = Nil;
	if (simulation_info_qm) {
	    model_definition_qm = ISVREF(simulation_info_qm,(SI_Long)8L);
	    if (model_definition_qm) {
		Current_model_definition_qm = model_definition_qm;
		Current_model_runtime_info_qm = ISVREF(model_definition_qm,
			(SI_Long)20L);
	    }
	    else {
		Current_model_definition_qm = Nil;
		Current_model_runtime_info_qm = Main_model_runtime_info;
	    }
	    result = make_and_initialize_variable_simulation_runtime_structure(variable);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qparent_frame;       /* parent-frame */

/* ADD-VARIABLE-TO-SIMULATION */
Object add_variable_to_simulation(variable)
    Object variable;
{
    Object current_model_runtime_info_qm, current_model_definition_qm;
    Object simulation_info_qm, model_definition_qm, parent_frame_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,25);
    current_model_runtime_info_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	    1);
      current_model_definition_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	      0);
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	model_definition_qm = Nil;
	if (simulation_info_qm) {
	    model_definition_qm = ISVREF(simulation_info_qm,(SI_Long)8L);
	    if (model_definition_qm) {
		Current_model_definition_qm = model_definition_qm;
		Current_model_runtime_info_qm = ISVREF(model_definition_qm,
			(SI_Long)20L);
	    }
	    else {
		Current_model_definition_qm = Nil;
		Current_model_runtime_info_qm = Main_model_runtime_info;
	    }
	    add_variable_to_simulation_model(variable);
	    if (ISVREF(Synchronous_model_queue,(SI_Long)1L)) {
		add_to_variables_to_be_rederived(variable);
		parent_frame_qm = 
			get_lookup_slot_value_given_default(variable,
			Qparent_frame,Nil);
		if (parent_frame_qm)
		    update_runtime_structures_according_to_edit(2,
			    parent_frame_qm,T);
		result = update_runtime_structures_according_to_edit(2,
			variable,T);
	    }
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* REMOVE-VARIABLE-FROM-SIMULATION */
Object remove_variable_from_simulation(variable)
    Object variable;
{
    Object current_model_runtime_info_qm, current_model_definition_qm;
    Object simulation_info_qm, model_definition_qm;
    Object variable_simulation_runtime_structure_qm, svref_arg_1;
    Object parent_frame_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,26);
    current_model_runtime_info_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	    1);
      current_model_definition_qm = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	      0);
	simulation_info_qm = get_lookup_slot_value_given_default(variable,
		Qsimulation_info_qm,Nil);
	model_definition_qm = Nil;
	if (simulation_info_qm) {
	    model_definition_qm = ISVREF(simulation_info_qm,(SI_Long)8L);
	    if (model_definition_qm) {
		Current_model_definition_qm = model_definition_qm;
		Current_model_runtime_info_qm = ISVREF(model_definition_qm,
			(SI_Long)20L);
	    }
	    else {
		Current_model_definition_qm = Nil;
		Current_model_runtime_info_qm = Main_model_runtime_info;
	    }
	    remove_variable_from_simulation_model(variable);
	    remove_from_variables_to_be_rederived(variable);
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    variable_simulation_runtime_structure_qm = simulation_info_qm ?
		     ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
	    if (ISVREF(Synchronous_model_queue,(SI_Long)1L)) {
		svref_arg_1 = Current_model_runtime_info_qm;
		SVREF(svref_arg_1,FIX((SI_Long)25L)) = T;
		if (variable_simulation_runtime_structure_qm) {
		    parent_frame_qm = 
			    get_lookup_slot_value_given_default(variable,
			    Qparent_frame,Nil);
		    if (parent_frame_qm)
			update_runtime_structures_according_to_edit(2,
				parent_frame_qm,T);
		    update_runtime_structures_according_to_edit(2,variable,T);
		    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) 
			    & (SI_Long)512L))
			delete_from_external_simulation_runtime_structures(variable_simulation_runtime_structure_qm);
		}
	    }
	    if (variable_simulation_runtime_structure_qm)
		result = reclaim_variable_simulation_runtime_structure(variable_simulation_runtime_structure_qm);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* ADD-TO-VARIABLES-TO-BE-REDERIVED */
Object add_to_variables_to_be_rederived(variable)
    Object variable;
{
    Object simulation_info_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, model_definition_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,27);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	current_model_runtime_info_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		1);
	  current_model_definition_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
		  0);
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    model_definition_qm = Nil;
	    if (simulation_info_qm) {
		model_definition_qm = ISVREF(simulation_info_qm,(SI_Long)8L);
		if (model_definition_qm) {
		    Current_model_definition_qm = model_definition_qm;
		    Current_model_runtime_info_qm = 
			    ISVREF(model_definition_qm,(SI_Long)20L);
		}
		else {
		    Current_model_definition_qm = Nil;
		    Current_model_runtime_info_qm = Main_model_runtime_info;
		}
		result = add_to_rederive_set(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)24L),variable);
	    }
	    else
		result = VALUES_1(Nil);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulate;           /* simulate */

/* REMOVE-FROM-VARIABLES-TO-BE-REDERIVED */
Object remove_from_variables_to_be_rederived(variable)
    Object variable;
{
    Object simulation_info_qm, runtime_structure_qm, temp_1, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, temp_2, temp_3;
    char temp;

    x_note_fn_call(187,28);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    runtime_structure_qm = Nil;
    if (simulation_info_qm) {
	runtime_structure_qm = ISVREF(simulation_info_qm,(SI_Long)1L);
	if (runtime_structure_qm) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    temp = simulation_info_qm ? TRUEP(ISVREF(simulation_info_qm,
		    (SI_Long)1L)) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    temp_1 = simulation_info_qm ? ISVREF(simulation_info_qm,
		    (SI_Long)1L) : Nil;
	    SVREF(temp_1,FIX((SI_Long)23L)) = Nil;
	    simulation_info_qm = 
		    get_lookup_slot_value_given_default(variable,
		    Qsimulation_info_qm,Nil);
	    temp_1 = simulation_info_qm ? ISVREF(simulation_info_qm,
		    (SI_Long)1L) : Nil;
	    SVREF(temp_1,FIX((SI_Long)24L)) = Nil;
	}
	delete_from_rederive_set(variable);
	gensymed_symbol = Qsimulate;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)30L);
      next_loop:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp_1 = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp_1;
	    }
	    else {
		temp_1 = Current_model_runtime_info_qm;
		temp_2 = CDR(gensymed_symbol_2);
		SVREF(temp_1,FIX((SI_Long)30L)) = temp_2;
	    }
	    inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    goto end_1;
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop;
      end_loop:
      end_1:;
	gensymed_symbol = Qsimulate;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)32L);
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_1;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp_1 = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp_1;
	    }
	    else {
		temp_1 = Current_model_runtime_info_qm;
		temp_2 = CDR(gensymed_symbol_2);
		SVREF(temp_1,FIX((SI_Long)32L)) = temp_2;
	    }
	    temp_3 = CAR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    return VALUES_1(temp_3);
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcm;                 /* \, */

/* COMPILE-ITEM-DESIGNATIONS-FOR-MODEL-FOR-SLOT */
Object compile_item_designations_for_model_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(187,29);
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
    if (CONSP(parse_result) && EQ(CAR(parse_result),Qcm))
	return VALUES_1(CDR(parse_result));
    else
	return phrase_cons(parse_result,Nil);
}

static Object Qincomplete;         /* incomplete */

/* INITIALIZE-MODEL-DEFINITION */
Object initialize_model_definition(model_definition)
    Object model_definition;
{
    Object temp;

    x_note_fn_call(187,30);
    initialize_model_runtime_info_if_necessary(model_definition);
    if (get_lookup_slot_value_given_default(model_definition,
	    Qitems_belonging_to_this_model,Nil))
	update_frame_status(model_definition,Nil,Nil);
    else
	update_frame_status(model_definition,Qincomplete,Nil);
    temp = get_lookup_slot_value_given_default(model_definition,
	    Qitems_belonging_to_this_model,Nil);
    forward_model_install(model_definition,CAR(temp),Nil);
    return update_anything_to_simulate_in_model_qm(ISVREF(model_definition,
	    (SI_Long)20L));
}

/* INITIALIZE-MODEL-RUNTIME-INFO-IF-NECESSARY */
Object initialize_model_runtime_info_if_necessary(model_definition)
    Object model_definition;
{
    Object svref_new_value;

    x_note_fn_call(187,31);
    if ( !TRUEP(ISVREF(model_definition,(SI_Long)20L))) {
	svref_new_value = initialize_model_runtime_info(1,model_definition);
	return VALUES_1(ISVREF(model_definition,(SI_Long)20L) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* INITIALIZE-FOR-MODEL-DEFINITION */
Object initialize_for_model_definition(model_definition)
    Object model_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(187,32);
    frame = model_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmodel_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return initialize_model_definition(model_definition);
}

/* INITIALIZE-AFTER-READING-FOR-MODEL-DEFINITION */
Object initialize_after_reading_for_model_definition(model_definition)
    Object model_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(187,33);
    frame = model_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmodel_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	inline_funcall_1(method_function_qm,frame);
    return initialize_model_definition(model_definition);
}

Object Model_definitions_for_item_or_class_kbprop = UNBOUND;

/* PUT-ITEMS-BELONGING-TO-THIS-MODEL */
Object put_items_belonging_to_this_model(model_definition,
	    items_belonging_to_this_model,initializing_qm)
    Object model_definition, items_belonging_to_this_model, initializing_qm;
{
    Object old_slot_value, temp;

    x_note_fn_call(187,34);
    old_slot_value = get_lookup_slot_value_given_default(model_definition,
	    Qitems_belonging_to_this_model,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(model_definition,
		Qitems_belonging_to_this_model);
    temp = set_lookup_slot_value_1(model_definition,
	    Qitems_belonging_to_this_model,items_belonging_to_this_model);
    if ( !TRUEP(initializing_qm)) {
	initialize_model_runtime_info_if_necessary(model_definition);
	if (get_lookup_slot_value_given_default(model_definition,
		Qitems_belonging_to_this_model,Nil))
	    update_frame_status(model_definition,Nil,Nil);
	else
	    update_frame_status(model_definition,Qincomplete,Nil);
	forward_model_install(model_definition,
		CAR(items_belonging_to_this_model),CAR(old_slot_value));
    }
    update_models_used_p();
    return VALUES_1(temp);
}

/* FORWARD-MODEL-INSTALL */
Object forward_model_install(model_definition,designations,
	    deinstall_designations)
    Object model_definition, designations, deinstall_designations;
{
    Object designation, ab_loop_list_, designation2, ab_loop_list__1;
    char temp;

    x_note_fn_call(187,35);
    designation = Nil;
    ab_loop_list_ = deinstall_designations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation2 = Nil;
    ab_loop_list__1 = designations;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    designation2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (model_item_designations_eq(designation,designation2)) {
	temp = TRUEP(Nil);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp = TRUEP(T);
    goto end_1;
    temp = TRUEP(Qnil);
  end_1:;
    if (temp)
	forward_model_install_1(model_definition,designation,T);
    goto next_loop;
  end_loop:;
    designation = Nil;
    ab_loop_list_ = designations;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation2 = Nil;
    ab_loop_list__1 = deinstall_designations;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    designation2 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (model_item_designations_eq(designation,designation2)) {
	temp = TRUEP(Nil);
	goto end_2;
    }
    goto next_loop_3;
  end_loop_3:
    temp = TRUEP(T);
    goto end_2;
    temp = TRUEP(Qnil);
  end_2:;
    if (temp)
	forward_model_install_1(model_definition,designation,Nil);
    goto next_loop_2;
  end_loop_2:
    return VALUES_1(Qnil);
}

static Object Qab_class;           /* class */

static Object Qthis_workspace;     /* this-workspace */

static Object Qitem;               /* item */

/* FORWARD-MODEL-INSTALL-1 */
Object forward_model_install_1(model_definition,designation,
	    deinstall_instead_qm)
    Object model_definition, designation, deinstall_instead_qm;
{
    Object temp, designated_class, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object designated_item, gensymed_symbol, workspace_qm, designated_item_qm;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,36);
    if (CONSP(designation)) {
	if (EQ(CAR(designation),Qab_class)) {
	    temp = CDR(designation);
	    designated_class = SYMBOLP(temp) ? CDR(designation) : 
		    SECOND(designation);
	    update_model_definitions_for_item_or_class(model_definition,
		    designated_class,deinstall_instead_qm);
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    designated_item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(designated_class);
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
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_1;
	      designated_item = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      if (deinstall_instead_qm)
		  install_item_in_model_if_appropriate(designated_item,Nil,T);
	      else
		  install_item_in_model_if_appropriate(designated_item,
			  model_definition,T);
	      goto next_loop;
	    end_loop_1:
	      result = VALUES_1(Qnil);
	    POP_SPECIAL();
	    return result;
	}
	else if (EQ(CAR(designation),Qthis_workspace)) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(model_definition,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    workspace_qm = gensymed_symbol;
	    if (workspace_qm) {
		if (deinstall_instead_qm)
		    return install_item_in_model_if_appropriate(workspace_qm,
			    Nil,T);
		else
		    return install_item_in_model_if_appropriate(workspace_qm,
			    model_definition,T);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else {
	update_model_definitions_for_item_or_class(model_definition,
		designation,deinstall_instead_qm);
	designated_item_qm = get_instance_with_name_if_any(Qitem,designation);
	if (designated_item_qm) {
	    if (deinstall_instead_qm)
		return install_item_in_model_if_appropriate(designated_item_qm,
			Nil,T);
	    else
		return install_item_in_model_if_appropriate(designated_item_qm,
			model_definition,T);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* UPDATE-MODEL-DEFINITIONS-FOR-ITEM-OR-CLASS */
Object update_model_definitions_for_item_or_class(model_definition,
	    item_or_class,deinstall_instead_qm)
    Object model_definition, item_or_class, deinstall_instead_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp, temp_1;
    Object svref_arg_2, new_cons, svref_new_value;

    x_note_fn_call(187,37);
    if (deinstall_instead_qm) {
	gensymed_symbol = model_definition;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = 
		lookup_kb_specific_property_value(item_or_class,
		Model_definitions_for_item_or_class_kbprop);
      next_loop:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else
		mutate_kb_specific_property_value(item_or_class,
			CDR(gensymed_symbol_2),
			Model_definitions_for_item_or_class_kbprop);
	    temp_1 = CAR(gensymed_symbol_2);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    return VALUES_1(temp_1);
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	gensymed_symbol = lookup_kb_specific_property_value(item_or_class,
		Model_definitions_for_item_or_class_kbprop);
	gensymed_symbol_1 = model_definition;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = gensymed_symbol_1;
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_eval_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qeval);
	    mutate_kb_specific_property_value(item_or_class,
		    gensymed_symbol_2,
		    Model_definitions_for_item_or_class_kbprop);
	    return VALUES_1(temp_1);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* MODEL-ITEM-DESIGNATIONS-EQ */
Object model_item_designations_eq(designation1,designation2)
    Object designation1, designation2;
{
    x_note_fn_call(187,38);
    if (CONSP(designation1) && EQ(CAR(designation1),Qab_class)) {
	if (CONSP(designation2) && EQ(CAR(designation2),Qab_class))
	    return VALUES_1(EQ(CDR(designation1),CDR(designation2)) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(EQ(designation1,designation2) ? T : Nil);
}

/* UPDATE-MODELS-USED-P */
Object update_models_used_p()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, md, ab_loop_it_;
    char temp;
    Declare_special(1);

    x_note_fn_call(187,39);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    md = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qmodel_definition);
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
      md = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      ab_loop_it_ = get_lookup_slot_value_given_default(md,
	      Qitems_belonging_to_this_model,Nil);
      if (ab_loop_it_) {
	  temp = TRUEP(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if (temp) {
	Models_used_p = T;
	return VALUES_1(Models_used_p);
    }
    else {
	Models_used_p = Nil;
	return VALUES_1(Models_used_p);
    }
}

/* INSTALL-ITEMS-OF-CLASS-IN-MODEL */
Object install_items_of_class_in_model(class_1)
    Object class_1;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,40);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(class_1);
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
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      install_item_in_model_if_models_used(item);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* INSTALL-ITEM-IN-MODEL-IF-MODELS-USED */
Object install_item_in_model_if_models_used(item)
    Object item;
{
    Object sub_class_bit_vector, inhibit_model_install_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(187,41);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
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
    if (temp) {
	inhibit_model_install_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Inhibit_model_install_qm,Qinhibit_model_install_qm,inhibit_model_install_qm,
		0);
	  update_generic_simulation_formula_for_variable_or_parameter(item);
	POP_SPECIAL();
    }
    if (Models_used_p)
	return install_item_in_model_if_appropriate(item,Nil,T);
    else
	return VALUES_1(Nil);
}

/* INSTALL-SUPERBLOCK-IN-MODEL-IF-APPROPRIATE */
Object install_superblock_in_model_if_appropriate(block,superblock)
    Object block, superblock;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(187,42);
    if (Models_used_p) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Model_definition_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(superblock,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if (temp)
	return install_item_in_model_if_appropriate(superblock,Nil,T);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Install_item_in_model_if_appropriate, Qinstall_item_in_model_if_appropriate);

/* INSTALL-ITEM-IN-MODEL-IF-APPROPRIATE */
Object install_item_in_model_if_appropriate(item,
	    model_definition_for_superior_item_qm,check_superior_items_qm)
    Object item, model_definition_for_superior_item_qm;
    Object check_superior_items_qm;
{
    Object model_definition_for_item_qm, model_definition_to_pass_on_qm;
    Object sub_class_bit_vector, subworkspace, ab_loop_list_;
    Object gensymed_symbol_3, ab_queue_form_, ab_next_queue_element_, subblock;
    Object x2, gensymed_symbol_4, gensymed_symbol_5, slot_description;
    Object class_description, vector_slot_index_qm, slot_value;
    Object user_vector_slot_index_qm, slot_name, lookup_structure_qm;
    Object slot_index_qm, gensymed_symbol_6;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, max_i, i, ab_loop_bind_;
    char temp;

    x_note_fn_call(187,43);
    model_definition_for_item_qm = get_model_to_which_item_belongs(item,
	    check_superior_items_qm);
    model_definition_to_pass_on_qm = model_definition_for_item_qm;
    if (model_definition_to_pass_on_qm);
    else
	model_definition_to_pass_on_qm = model_definition_for_superior_item_qm;
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Variable_or_parameter_class_description,(SI_Long)18L));
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
    if (temp)
	mark_variable_as_belonging_to_model(item,
		model_definition_to_pass_on_qm);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
    if (temp) {
	mark_entity_as_belonging_to_model_if_appropriate(item,
		model_definition_to_pass_on_qm);
	subworkspace = Nil;
	ab_loop_list_ = ISVREF(item,(SI_Long)18L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	subworkspace = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	install_item_in_model_if_appropriate(subworkspace,
		model_definition_to_pass_on_qm,Nil);
	goto next_loop;
      end_loop:;
    }
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Kb_workspace_class_description,
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
    if (temp) {
	gensymed_symbol_3 = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	gensymed_symbol_3 = gensymed_symbol_3 ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol_3;
	ab_next_queue_element_ = Nil;
	subblock = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop_1:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop_1;
	subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	if (SIMPLE_VECTOR_P(subblock) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(subblock)) > (SI_Long)2L && 
		 !EQ(ISVREF(subblock,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(subblock,(SI_Long)1L);
	    gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_3 = Nil;
	if (gensymed_symbol_3 && ISVREF(gensymed_symbol_3,(SI_Long)16L))
	    install_item_in_model_if_appropriate(subblock,
		    model_definition_to_pass_on_qm,Nil);
	goto next_loop_1;
      end_loop_1:;
    }
    gensymed_symbol_3 = item;
    gensymed_symbol_4 = model_definition_for_item_qm;
    if (gensymed_symbol_4);
    else
	gensymed_symbol_4 = model_definition_for_superior_item_qm;
    gensymed_symbol_5 = Nil;
    slot_description = Nil;
    class_description = ISVREF(gensymed_symbol_3,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)6L);
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(slot_description,(SI_Long)8L)) {
	vector_slot_index_qm = ISVREF(slot_description,(SI_Long)7L);
	if (vector_slot_index_qm)
	    slot_value = ISVREF(gensymed_symbol_3,IFIX(vector_slot_index_qm));
	else {
	    user_vector_slot_index_qm = ISVREF(slot_description,(SI_Long)8L);
	    if (user_vector_slot_index_qm)
		slot_value = ISVREF(ISVREF(gensymed_symbol_3,(SI_Long)0L),
			IFIX(user_vector_slot_index_qm));
	    else {
		slot_name = ISVREF(slot_description,(SI_Long)1L);
		lookup_structure_qm = ISVREF(gensymed_symbol_3,(SI_Long)0L);
		if (lookup_structure_qm) {
		    max_i = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(lookup_structure_qm));
		    max_i = max_i - (SI_Long)1L;
		    i = IFIX(ISVREF(ISVREF(gensymed_symbol_3,(SI_Long)1L),
			    (SI_Long)15L));
		    ab_loop_bind_ = max_i;
		  next_loop_3:
		    if (i >= ab_loop_bind_)
			goto end_loop_3;
		    if (EQ(ISVREF(lookup_structure_qm,i),slot_name)) {
			slot_index_qm = FIX(i + (SI_Long)1L);
			goto end_1;
		    }
		    i = i + (SI_Long)2L;
		    goto next_loop_3;
		  end_loop_3:
		    slot_index_qm = Qnil;
		  end_1:;
		    slot_value = slot_index_qm ? 
			    ISVREF(lookup_structure_qm,
			    IFIX(slot_index_qm)) : ISVREF(slot_description,
			    (SI_Long)6L);
		}
		else
		    slot_value = ISVREF(slot_description,(SI_Long)6L);
	    }
	}
	if (SIMPLE_VECTOR_P(slot_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(slot_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(slot_value,(SI_Long)1L);
	    gensymed_symbol_6 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_6 = Nil;
	if (gensymed_symbol_6 && ISVREF(gensymed_symbol_6,(SI_Long)16L))
	    inline_funcall_3(Install_item_in_model_if_appropriate,
		    slot_value,gensymed_symbol_4,gensymed_symbol_5);
    }
    goto next_loop_2;
  end_loop_2:;
    return VALUES_1(Qnil);
}

/* MARK-VARIABLE-AS-BELONGING-TO-MODEL */
Object mark_variable_as_belonging_to_model(variable_or_parameter,
	    model_definition_qm)
    Object variable_or_parameter, model_definition_qm;
{
    Object simulation_info_qm, current_model_runtime_info_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,44);
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	SVREF(simulation_info_qm,FIX((SI_Long)8L)) = model_definition_qm;
	current_model_runtime_info_qm = model_definition_qm ? 
		ISVREF(model_definition_qm,(SI_Long)20L) : 
		Main_model_runtime_info;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		0);
	  result = add_variable_to_simulation(variable_or_parameter);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qexternal_simulation_definition_for_entity;  /* external-simulation-definition-for-entity */

/* MARK-ENTITY-AS-BELONGING-TO-MODEL-IF-APPROPRIATE */
Object mark_entity_as_belonging_to_model_if_appropriate(entity,
	    model_definition_qm)
    Object entity, model_definition_qm;
{
    Object current_model_runtime_info_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,45);
    if (get_slot_value_if_any_function(entity,
	    Qexternal_simulation_definition_for_entity,Nil)) {
	current_model_runtime_info_qm = model_definition_qm ? 
		ISVREF(model_definition_qm,(SI_Long)20L) : 
		Main_model_runtime_info;
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
		0);
	  result = add_externally_simulated_entity_to_simulation_model(entity);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* GET-MODEL-TO-WHICH-ITEM-BELONGS */
Object get_model_to_which_item_belongs(item,check_superior_items_qm)
    Object item, check_superior_items_qm;
{
    Object item_to_check_qm, model_definition_qm;

    x_note_fn_call(187,46);
    if (check_superior_items_qm) {
	item_to_check_qm = item;
	model_definition_qm = Nil;
      next_loop:
	if ( !TRUEP(item_to_check_qm))
	    goto end_loop;
	model_definition_qm = 
		get_model_which_designates_item(item_to_check_qm);
	if (model_definition_qm)
	    return VALUES_1(model_definition_qm);
	item_to_check_qm = superior_frame(item_to_check_qm);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return get_model_which_designates_item(item);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* GET-MODEL-WHICH-DESIGNATES-ITEM */
Object get_model_which_designates_item(item)
    Object item;
{
    Object name_or_names, name, ab_loop_list_, model_definition_qm, temp;
    Object sub_class_bit_vector, gensymed_symbol_3, ab_queue_form_;
    Object ab_next_queue_element_, block, designation, class_1;
    Object class_description;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(187,47);
    name_or_names = get_lookup_slot_value_given_default(item,
	    Qname_or_names_for_frame,Nil);
    if (name_or_names) {
	if (CONSP(name_or_names)) {
	    name = Nil;
	    ab_loop_list_ = name_or_names;
	    model_definition_qm = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = lookup_kb_specific_property_value(name,
		    Model_definitions_for_item_or_class_kbprop);
	    model_definition_qm = CAR(temp);
	    if (model_definition_qm) {
		temp = model_definition_qm;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	else {
	    temp = lookup_kb_specific_property_value(name_or_names,
		    Model_definitions_for_item_or_class_kbprop);
	    temp = CAR(temp);
	}
    }
    else
	temp = Nil;
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp_1 ?  !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)512L)) : TRUEP(Nil)) {
	    gensymed_symbol_3 = ACCESS_ONCE(ISVREF(item,(SI_Long)14L));
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol_3;
	    ab_next_queue_element_ = Nil;
	    block = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_1;
	    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Model_definition_class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		designation = Nil;
		temp = get_lookup_slot_value_given_default(block,
			Qitems_belonging_to_this_model,Nil);
		ab_loop_list_ = CAR(temp);
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		designation = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (CONSP(designation) && EQ(CAR(designation),Qthis_workspace))
		    return VALUES_1(block);
		goto next_loop_2;
	      end_loop_2:;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	}
	else
	    temp = Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Object_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
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
	}
	if (temp_1) {
	    class_1 = Nil;
	    class_description = ISVREF(item,(SI_Long)1L);
	    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	    model_definition_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(class_1,Qitem))
		goto end_loop_3;
	    model_definition_qm = 
		    get_appropriate_model_definition_for_class(item,
		    class_1,lookup_kb_specific_property_value(class_1,
		    Model_definitions_for_item_or_class_kbprop));
	    if (model_definition_qm)
		return VALUES_1(model_definition_qm);
	    goto next_loop_3;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* GET-APPROPRIATE-MODEL-DEFINITION-FOR-CLASS */
Object get_appropriate_model_definition_for_class(item,class_1,
	    model_definitions_for_class)
    Object item, class_1, model_definitions_for_class;
{
    Object model_definition_for_entire_class_qm, item_to_check_qm;
    Object any_model_definitions_specifying_items_qm, model_definition;
    Object ab_loop_list_, designation, temp, ab_loop_list__1;

    x_note_fn_call(187,48);
    model_definition_for_entire_class_qm = Nil;
    item_to_check_qm = item;
  next_loop:
    if ( !TRUEP(item_to_check_qm))
	goto end_loop;
    any_model_definitions_specifying_items_qm = Nil;
    model_definition = Nil;
    ab_loop_list_ = model_definitions_for_class;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    model_definition = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    designation = Nil;
    temp = get_lookup_slot_value_given_default(model_definition,
	    Qitems_belonging_to_this_model,Nil);
    ab_loop_list__1 = CAR(temp);
  next_loop_2:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_2;
    designation = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (CONSP(designation) && EQ(CAR(designation),Qab_class)) {
	temp = CDR(designation);
	if (SYMBOLP(temp)) {
	    if ( !TRUEP(model_definition_for_entire_class_qm) && 
		    EQ(CDR(designation),class_1))
		model_definition_for_entire_class_qm = model_definition;
	}
	else {
	    any_model_definitions_specifying_items_qm = T;
	    if (EQ(SECOND(designation),class_1) && 
		    item_matches_one_in_designation(item_to_check_qm,
		    THIRD(designation),model_definition))
		return VALUES_1(model_definition);
	}
    }
    goto next_loop_2;
  end_loop_2:;
    goto next_loop_1;
  end_loop_1:
    if ( !TRUEP(any_model_definitions_specifying_items_qm))
	return VALUES_1(model_definition_for_entire_class_qm);
    item_to_check_qm = superior_frame(item_to_check_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(model_definition_for_entire_class_qm);
    return VALUES_1(Qnil);
}

/* ITEM-MATCHES-ONE-IN-DESIGNATION */
Object item_matches_one_in_designation(item,model_item_designation,
	    model_definition)
    Object item, model_item_designation, model_definition;
{
    Object name_or_names, gensymed_symbol;

    x_note_fn_call(187,49);
    if (SYMBOLP(model_item_designation)) {
	name_or_names = get_lookup_slot_value_given_default(item,
		Qname_or_names_for_frame,Nil);
	if (CONSP(name_or_names))
	    return memq_function(model_item_designation,name_or_names);
	else
	    return VALUES_1(EQ(model_item_designation,name_or_names) ? T : 
		    Nil);
    }
    else if (CONSP(model_item_designation) && 
	    EQ(CAR(model_item_designation),Qthis_workspace)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(model_definition,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	return VALUES_1(EQ(gensymed_symbol,item) ? T : Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* PUT-SIMULATION-PROCEDURE-FOR-MODEL */
Object put_simulation_procedure_for_model(model_definition,
	    simulation_procedure_for_model,initializing_qm)
    Object model_definition, simulation_procedure_for_model, initializing_qm;
{
    Object temp;

    x_note_fn_call(187,50);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(model_definition,
		Qsimulation_procedure_for_model);
    temp = set_lookup_slot_value_1(model_definition,
	    Qsimulation_procedure_for_model,simulation_procedure_for_model);
    if ( !TRUEP(initializing_qm)) {
	initialize_model_runtime_info_if_necessary(model_definition);
	update_anything_to_simulate_in_model_qm(ISVREF(model_definition,
		(SI_Long)20L));
    }
    return VALUES_1(temp);
}

/* PUT-EXTERNAL-SIMULATOR-CONFIGURATION-FOR-MODEL */
Object put_external_simulator_configuration_for_model(model_definition,
	    external_simulator_configuration_for_model,initializing_qm)
    Object model_definition, external_simulator_configuration_for_model;
    Object initializing_qm;
{
    Object temp;

    x_note_fn_call(187,51);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(model_definition,
		Qexternal_simulator_configuration_for_model);
    temp = set_lookup_slot_value_1(model_definition,
	    Qexternal_simulator_configuration_for_model,
	    external_simulator_configuration_for_model);
    if ( !TRUEP(initializing_qm)) {
	initialize_model_runtime_info_if_necessary(model_definition);
	update_anything_to_simulate_in_model_qm(ISVREF(model_definition,
		(SI_Long)20L));
    }
    return VALUES_1(temp);
}

/* INSTALL-SYSTEM-TABLE-FOR-SIMULATION-PARAMETERS */
Object install_system_table_for_simulation_parameters(simulation_parameters)
    Object simulation_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(187,52);
    PUSH_SPECIAL_WITH_SYMBOL(Simulation_parameters,Qsimulation_parameters,simulation_parameters,
	    0);
      warn_of_simulation_license_restrictions_if_necessary();
      if (ISVREF(Simulation_parameters,(SI_Long)27L) || 
	      ISVREF(Simulation_parameters,(SI_Long)26L))
	  result = update_anything_to_simulate_in_model_qm(Main_model_runtime_info);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-SIMULATION-PARAMETERS */
Object deinstall_system_table_for_simulation_parameters(simulation_parameters)
    Object simulation_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(187,53);
    PUSH_SPECIAL_WITH_SYMBOL(Simulation_parameters,Qsimulation_parameters,simulation_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant;     /* "Ignoring the request to turn on the simulator found in the simulation-parameters.  The current G2 license does not include this feature." */

/* WARN-OF-SIMULATION-LICENSE-RESTRICTIONS-IF-NECESSARY */
Object warn_of_simulation_license_restrictions_if_necessary()
{
    Object code;
    char temp;

    x_note_fn_call(187,54);
    if (ISVREF(Simulation_parameters,(SI_Long)24L)) {
	code = M_CAR(M_CDR(Edit_type_alias_mapping));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)4096L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_g1_semantics_graph)));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return notify_user(1,string_constant);
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_procedure;  /* simulation-procedure */

/* PUT-SIMULATION-PROCEDURE */
Object put_simulation_procedure(simulation_parameters_instance,
	    simulation_procedure,initializing_qm)
    Object simulation_parameters_instance, simulation_procedure;
    Object initializing_qm;
{
    Object temp;

    x_note_fn_call(187,55);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_parameters_instance,
		Qsimulation_procedure);
    temp = SVREF(simulation_parameters_instance,FIX((SI_Long)27L)) = 
	    simulation_procedure;
    if ( !TRUEP(initializing_qm)) {
	if (system_table_installed_p(simulation_parameters_instance))
	    update_anything_to_simulate_in_model_qm(Main_model_runtime_info);
    }
    return VALUES_1(temp);
}

static Object Qsimulator_on_qm;    /* simulator-on? */

/* PUT-SIMULATOR-ON? */
Object put_simulator_on_qm(simulation_parameters_instance,simulator_on_qm,
	    initializing_qm)
    Object simulation_parameters_instance, simulator_on_qm, initializing_qm;
{
    Object temp;

    x_note_fn_call(187,56);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_parameters_instance,
		Qsimulator_on_qm);
    temp = SVREF(simulation_parameters_instance,FIX((SI_Long)24L)) = 
	    simulator_on_qm;
    if ( !TRUEP(initializing_qm)) {
	warn_of_simulation_license_restrictions_if_necessary();
	if (system_table_installed_p(simulation_parameters_instance)) {
	    if (simulator_on_qm)
		schedule_data_server_accept_data_calls();
	    update_anything_to_simulate_in_model_qm(Main_model_runtime_info);
	}
    }
    return VALUES_1(temp);
}

static Object Qexternal_simulator_configuration;  /* external-simulator-configuration */

/* PUT-EXTERNAL-SIMULATOR-CONFIGURATION */
Object put_external_simulator_configuration(simulation_parameters_instance,
	    external_simulator_configuration,initializing_qm)
    Object simulation_parameters_instance, external_simulator_configuration;
    Object initializing_qm;
{
    Object temp;

    x_note_fn_call(187,57);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(simulation_parameters_instance,
		Qexternal_simulator_configuration);
    temp = SVREF(simulation_parameters_instance,FIX((SI_Long)26L)) = 
	    external_simulator_configuration;
    if ( !TRUEP(initializing_qm)) {
	if (system_table_installed_p(simulation_parameters_instance))
	    update_anything_to_simulate_in_model_qm(Main_model_runtime_info);
    }
    return VALUES_1(temp);
}

static Object Qnone;               /* none */

/* UPDATE-ANYTHING-TO-SIMULATE-IN-MODEL? */
Object update_anything_to_simulate_in_model_qm(model_runtime_info)
    Object model_runtime_info;
{
    Object external_configuration_qm, model_definition;
    char temp;

    x_note_fn_call(187,58);
    temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
	    (SI_Long)21L)));
    if (temp);
    else
	temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
		(SI_Long)20L)));
    if (temp);
    else
	temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
		(SI_Long)19L)));
    if (temp);
    else if (EQ(model_runtime_info,Main_model_runtime_info)) {
	if ( !TRUEP(Releasing_kb_qm)) {
	    temp = TRUEP(ISVREF(Simulation_parameters,(SI_Long)27L));
	    if (temp);
	    else {
		external_configuration_qm = ISVREF(Simulation_parameters,
			(SI_Long)26L);
		temp = external_configuration_qm ?  
			!EQ(CAR(external_configuration_qm),Qnone) : 
			TRUEP(Qnil);
	    }
	}
	else
	    temp = TRUEP(Nil);
    }
    else {
	model_definition = ISVREF(model_runtime_info,(SI_Long)28L);
	temp = TRUEP(get_lookup_slot_value(model_definition,
		Qsimulation_procedure_for_model));
	if (temp);
	else {
	    external_configuration_qm = 
		    get_lookup_slot_value_given_default(model_definition,
		    Qexternal_simulator_configuration_for_model,Nil);
	    temp = external_configuration_qm ?  
		    !EQ(CAR(external_configuration_qm),Qnone) : TRUEP(Qnil);
	}
    }
    if (temp)
	return add_model_which_has_something_to_simulate(model_runtime_info);
    else
	return remove_model_which_has_nothing_to_simulate(model_runtime_info);
}

/* ANYTHING-TO-SIMULATE? */
Object anything_to_simulate_qm(model_runtime_info)
    Object model_runtime_info;
{
    Object temp, external_configuration_qm, model_definition;

    x_note_fn_call(187,59);
    temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
	    (SI_Long)21L))) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
		(SI_Long)20L))) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(installation_set_empty_qm(ISVREF(model_runtime_info,
		(SI_Long)19L))) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (EQ(model_runtime_info,Main_model_runtime_info)) {
	if ( !TRUEP(Releasing_kb_qm)) {
	    temp = ISVREF(Simulation_parameters,(SI_Long)27L);
	    if (temp)
		return VALUES_1(temp);
	    else {
		external_configuration_qm = ISVREF(Simulation_parameters,
			(SI_Long)26L);
		if (external_configuration_qm)
		    return VALUES_1( !EQ(CAR(external_configuration_qm),
			    Qnone) ? T : Nil);
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	model_definition = ISVREF(model_runtime_info,(SI_Long)28L);
	temp = get_lookup_slot_value(model_definition,
		Qsimulation_procedure_for_model);
	if (temp)
	    return VALUES_1(temp);
	else {
	    external_configuration_qm = 
		    get_lookup_slot_value_given_default(model_definition,
		    Qexternal_simulator_configuration_for_model,Nil);
	    if (external_configuration_qm)
		return VALUES_1( !EQ(CAR(external_configuration_qm),Qnone) 
			? T : Nil);
	    else
		return VALUES_1(Nil);
	}
    }
}

static Object Qnothing_to_simulate;  /* nothing-to-simulate */

static Object Qrunning;            /* running */

static Object Qneeds_to_be_shutdown;  /* needs-to-be-shutdown */

static Object Qneeds_to_be_initialized;  /* needs-to-be-initialized */

/* ADD-MODEL-WHICH-HAS-SOMETHING-TO-SIMULATE */
Object add_model_which_has_something_to_simulate(model_runtime_info)
    Object model_runtime_info;
{
    Object model_definition_qm, code, current_model_queue_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,60);
    model_definition_qm = ISVREF(model_runtime_info,(SI_Long)28L);
    if ( !TRUEP(model_definition_qm)) {
	temp = TRUEP(System_is_running);
	if (temp);
	else
	    temp = TRUEP(System_has_paused);
    }
    else if (model_running_or_paused_qm(model_definition_qm))
	temp = TRUEP(T);
    else if (EQ(get_lookup_slot_value(model_definition_qm,
	    Qmodel_simulation_status),Qnothing_to_simulate)) {
	change_slot_value(3,model_definition_qm,Qmodel_simulation_status,
		Qrunning);
	temp = TRUEP(T);
    }
    else
	temp = TRUEP(Qnil);
    if (temp) {
	if (EQ(ISVREF(model_runtime_info,(SI_Long)29L),Qneeds_to_be_shutdown))
	    return VALUES_1(SVREF(model_runtime_info,FIX((SI_Long)29L)) = 
		    Qrunning);
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
	    if (temp ?  !TRUEP(ISVREF(model_runtime_info,(SI_Long)29L)) : 
		    TRUEP(Nil)) {
		SVREF(model_runtime_info,FIX((SI_Long)29L)) = 
			Qneeds_to_be_initialized;
		current_model_queue_qm = 
			get_model_queue_for_model(model_runtime_info);
		PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
			0);
		  result = add_model_to_simulation(model_runtime_info);
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-MODEL-WHICH-HAS-NOTHING-TO-SIMULATE */
Object remove_model_which_has_nothing_to_simulate(model_runtime_info)
    Object model_runtime_info;
{
    Object current_model_queue_qm, model_definition_qm;
    Declare_special(1);

    x_note_fn_call(187,61);
    if (EQ(ISVREF(model_runtime_info,(SI_Long)29L),Qneeds_to_be_initialized)) {
	current_model_queue_qm = get_model_queue_for_model(model_runtime_info);
	PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		0);
	  remove_model_from_simulation(model_runtime_info);
	POP_SPECIAL();
    }
    else if (ISVREF(Synchronous_model_queue,(SI_Long)1L) && 
	    ISVREF(model_runtime_info,(SI_Long)29L))
	SVREF(model_runtime_info,FIX((SI_Long)29L)) = Qneeds_to_be_shutdown;
    model_definition_qm = ISVREF(model_runtime_info,(SI_Long)28L);
    if (model_definition_qm && model_running_or_paused_qm(model_definition_qm))
	return change_slot_value(3,model_definition_qm,
		Qmodel_simulation_status,Qnothing_to_simulate);
    else
	return VALUES_1(Nil);
}

static Object Qclear_simulation_history_at_runtime;  /* clear-simulation-history-at-runtime */

/* CLEAR-SIMULATION-HISTORY-OF-MODEL-VARIABLES */
Object clear_simulation_history_of_model_variables(model_definition)
    Object model_definition;
{
    Object model_runtime_info_qm;

    x_note_fn_call(187,62);
    model_runtime_info_qm = ISVREF(model_definition,(SI_Long)20L);
    for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
	    (SI_Long)19L),Qclear_simulation_history_at_runtime);
    for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
	    (SI_Long)20L),Qclear_simulation_history_at_runtime);
    return for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
	    (SI_Long)21L),Qclear_simulation_history_at_runtime);
}

static Object Qadjust_simulation_history_at_runtime_if_necessary;  /* adjust-simulation-history-at-runtime-if-necessary */

/* ADJUST-SIMULATION-HISTORY-OF-MODEL-VARIABLES-IF-NECESSARY */
Object adjust_simulation_history_of_model_variables_if_necessary(model_definition)
    Object model_definition;
{
    Object model_runtime_info_qm, time_used_to_adjust_histories_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,63);
    model_runtime_info_qm = ISVREF(model_definition,(SI_Long)20L);
    time_used_to_adjust_histories_qm = 
	    get_model_simulation_time(model_definition);
    PUSH_SPECIAL_WITH_SYMBOL(Time_used_to_adjust_histories_qm,Qtime_used_to_adjust_histories_qm,time_used_to_adjust_histories_qm,
	    0);
      if (Time_used_to_adjust_histories_qm) {
	  for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
		  (SI_Long)19L),
		  Qadjust_simulation_history_at_runtime_if_necessary);
	  for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
		  (SI_Long)20L),
		  Qadjust_simulation_history_at_runtime_if_necessary);
	  for_each_element_in_installation_set(ISVREF(model_runtime_info_qm,
		  (SI_Long)21L),
		  Qadjust_simulation_history_at_runtime_if_necessary);
	  reclaim_managed_simple_float_array_of_length_1(Time_used_to_adjust_histories_qm);
	  result = VALUES_1(Nil);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* START-MODEL */
Object start_model(model_definition)
    Object model_definition;
{
    Object model_runtime_info;

    x_note_fn_call(187,64);
    model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
    if (anything_to_simulate_qm(model_runtime_info)) {
	change_slot_value(3,model_definition,Qmodel_simulation_status,
		Qrunning);
	initialize_simulator(2,model_runtime_info,model_definition);
	clear_simulation_history_of_model_variables(model_definition);
	if (ISVREF(Simulation_parameters,(SI_Long)24L))
	    return schedule_data_server_accept_data_calls();
	else
	    return VALUES_1(Nil);
    }
    else
	return change_slot_value(3,model_definition,
		Qmodel_simulation_status,Qnothing_to_simulate);
}

static Object Qnot_running;        /* not-running */

/* RESET-MODEL */
Object reset_model(model_definition)
    Object model_definition;
{
    x_note_fn_call(187,65);
    if (model_running_or_paused_qm(model_definition))
	shutdown_simulator(2,ISVREF(model_definition,(SI_Long)20L),
		model_definition);
    return change_slot_value(3,model_definition,Qmodel_simulation_status,
	    Qnot_running);
}

/* PAUSE-MODEL */
Object pause_model(model_definition)
    Object model_definition;
{
    x_note_fn_call(187,66);
    if (EQ(get_lookup_slot_value(model_definition,
	    Qmodel_simulation_status),Qrunning))
	return change_slot_value(3,model_definition,
		Qmodel_simulation_status,Qpaused);
    else
	return VALUES_1(Nil);
}

/* RESUME-MODEL */
Object resume_model(model_definition)
    Object model_definition;
{
    x_note_fn_call(187,67);
    if (EQ(get_lookup_slot_value(model_definition,
	    Qmodel_simulation_status),Qpaused)) {
	adjust_model_simulation_time_to_skip_paused_period(model_definition);
	return change_slot_value(3,model_definition,
		Qmodel_simulation_status,Qrunning);
    }
    else
	return VALUES_1(Nil);
}

/* ADJUST-MODEL-SIMULATION-TIME-TO-SKIP-PAUSED-PERIOD */
Object adjust_model_simulation_time_to_skip_paused_period(model_definition)
    Object model_definition;
{
    Object model_runtime_info, as_fast_as_possible_model_qm;
    Object current_simulation_time, base_simulation_time, gensymed_symbol;
    Object integer_portion, fraction_portion, svref_new_value;
    SI_Long current_gensym_time;
    SI_Long gensymed_symbol_1;
    double temp;
    Object result;

    x_note_fn_call(187,68);
    model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
    as_fast_as_possible_model_qm = memq_function(Qas_fast_as_possible,
	    get_lookup_slot_value(model_definition,
	    Qsimulation_control_specifications));
    temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
    current_gensym_time = inline_floor_1(DFLOAT_ISAREF_1(Current_g2_time,
	    (SI_Long)0L) - 
	    (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
	    (SI_Long)0L) - temp));
    current_simulation_time = ISVREF(ISVREF(model_runtime_info,
	    (SI_Long)5L),(SI_Long)1L);
    base_simulation_time = ISVREF(ISVREF(model_runtime_info,(SI_Long)7L),
	    (SI_Long)1L);
    if (as_fast_as_possible_model_qm) {
	if (NUM_GT(LONG_TO_FIXNUM(current_gensym_time),
		current_simulation_time)) {
	    gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)5L);
	    gensymed_symbol_1 = current_gensym_time - 
		    IFIX(base_simulation_time);
	    if (INTEGERP(FIX(gensymed_symbol_1))) {
		ISVREF(gensymed_symbol,(SI_Long)1L) = FIX(gensymed_symbol_1);
		return VALUES_1(ISVREF(gensymed_symbol,(SI_Long)2L) = 
			FIX((SI_Long)0L));
	    }
	    else {
		result = ltruncate(DOUBLE_TO_DOUBLE_FLOAT((double)gensymed_symbol_1),
			_);
		MVS_2(result,integer_portion,fraction_portion);
		SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
		svref_new_value = l_round(ltimes(fraction_portion,
			Fraction_modulus_of_compound_fixnum_simulation_time),
			_);
		return VALUES_1(SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
			svref_new_value);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)5L);
	gensymed_symbol_1 = current_gensym_time - IFIX(base_simulation_time);
	if (INTEGERP(FIX(gensymed_symbol_1))) {
	    ISVREF(gensymed_symbol,(SI_Long)1L) = FIX(gensymed_symbol_1);
	    return VALUES_1(ISVREF(gensymed_symbol,(SI_Long)2L) = 
		    FIX((SI_Long)0L));
	}
	else {
	    result = ltruncate(DOUBLE_TO_DOUBLE_FLOAT((double)gensymed_symbol_1),
		    _);
	    MVS_2(result,integer_portion,fraction_portion);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
	    svref_new_value = l_round(ltimes(fraction_portion,
		    Fraction_modulus_of_compound_fixnum_simulation_time),_);
	    return VALUES_1(SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
		    svref_new_value);
	}
    }
}

/* MODEL-RUNNING-OR-PAUSED? */
Object model_running_or_paused_qm(model_definition)
    Object model_definition;
{
    Object status, temp;

    x_note_fn_call(187,69);
    status = get_lookup_slot_value(model_definition,Qmodel_simulation_status);
    temp = EQ(status,Qrunning) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(EQ(status,Qpaused) ? T : Nil);
}

static Object float_constant;      /* 0.0 */

/* SET-MODEL-SIMULATION-TIME */
Object set_model_simulation_time(model_definition,time_1)
    Object model_definition, time_1;
{
    Object model_runtime_info, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, svref_new_value, integer_portion, fraction_portion;
    Object result_negative_p, micro_time_1_temp, macro_time_1_temp;
    Object variable_group_update_structure, ab_loop_list_;
    SI_Long svref_new_value_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,70);
    model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
    gensymed_symbol = Simulation_time_accumulator;
    gensymed_symbol_1 = ISVREF(model_runtime_info,(SI_Long)5L);
    gensymed_symbol_2 = ISVREF(model_runtime_info,(SI_Long)7L);
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
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)5L);
	gensymed_symbol_1 = evaluation_value_value(time_1);
	if (INTEGERP(gensymed_symbol_1)) {
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	    ISVREF(gensymed_symbol,(SI_Long)2L) = FIX((SI_Long)0L);
	}
	else {
	    result = ltruncate(lfloat(gensymed_symbol_1,float_constant),_);
	    MVS_2(result,integer_portion,fraction_portion);
	    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = integer_portion;
	    svref_new_value = l_round(ltimes(fraction_portion,
		    Fraction_modulus_of_compound_fixnum_simulation_time),_);
	    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    reclaim_evaluation_value(time_1);
    gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)7L);
    gensymed_symbol_1 = Simulation_time_accumulator;
    gensymed_symbol_2 = ISVREF(model_runtime_info,(SI_Long)5L);
    macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
    micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
    result_negative_p = Nil;
    if (FIXNUM_GT(macro_time_2,macro_time_1) || FIXNUM_EQ(macro_time_1,
	    macro_time_2) && FIXNUM_GT(micro_time_2,micro_time_1)) {
	micro_time_1_temp = micro_time_2;
	macro_time_1_temp = macro_time_2;
	micro_time_2 = micro_time_1;
	micro_time_1 = micro_time_1_temp;
	macro_time_2 = macro_time_1;
	macro_time_1 = macro_time_1_temp;
	result_negative_p = T;
    }
    if (IFIX(micro_time_2) != (SI_Long)0L) {
	if (FIXNUM_GT(micro_time_2,micro_time_1)) {
	    macro_time_1 = FIXNUM_SUB1(macro_time_1);
	    micro_time_1 = FIXNUM_MINUS(FIXNUM_ADD(micro_time_1,
		    Fraction_modulus_of_compound_fixnum_simulation_time),
		    micro_time_2);
	}
	else
	    micro_time_1 = FIXNUM_MINUS(micro_time_1,micro_time_2);
    }
    macro_time_1 = FIXNUM_MINUS(macro_time_1,macro_time_2);
    if (result_negative_p) {
	svref_new_value_1 = IFIX(micro_time_1) * (SI_Long)-1L;
	ISVREF(gensymed_symbol,(SI_Long)2L) = FIX(svref_new_value_1);
	svref_new_value_1 = IFIX(macro_time_1) * (SI_Long)-1L;
	ISVREF(gensymed_symbol,(SI_Long)1L) = FIX(svref_new_value_1);
    }
    else {
	SVREF(gensymed_symbol,FIX((SI_Long)2L)) = micro_time_1;
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = macro_time_1;
    }
    variable_group_update_structure = Nil;
    ab_loop_list_ = ISVREF(model_runtime_info,(SI_Long)23L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable_group_update_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(variable_group_update_structure,(SI_Long)3L);
    gensymed_symbol_1 = ISVREF(model_runtime_info,(SI_Long)5L);
    svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    SVREF(gensymed_symbol,FIX((SI_Long)1L)) = svref_new_value;
    goto next_loop;
  end_loop:;
    SVREF(model_runtime_info,FIX((SI_Long)25L)) = T;
    return adjust_simulation_history_of_model_variables_if_necessary(model_definition);
}

/* GET-MODEL-SIMULATION-TIME */
Object get_model_simulation_time(model_definition)
    Object model_definition;
{
    Object model_runtime_info, gensymed_symbol, integer_portion, micro_time;
    Object aref_arg_1, time_as_quantity;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,71);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
	gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)5L);
	integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	if (IFIX(micro_time) == (SI_Long)0L) {
	    aref_arg_1 = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	}
	else {
	    aref_arg_1 = Simulation_time_managed_float;
	    aref_new_value = (double)IFIX(integer_portion) + 
		    (double)IFIX(micro_time) / 100000.0;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	}
	time_as_quantity = Simulation_time_managed_float;
	result = copy_managed_float(time_as_quantity);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* SET-MODEL-SIMULATION-TIME-INCREMENT */
Object set_model_simulation_time_increment(model_definition,time_increment)
    Object model_definition, time_increment;
{
    Object model_runtime_info, variable_group_update_structure_qm;
    Object current_model_runtime_info_qm, current_model_definition_qm, code;
    Object current_model_queue_qm, gensymed_symbol, gensymed_symbol_1;
    Object integer_portion, fraction_portion, svref_new_value;
    Object gensymed_symbol_2, macro_time_1, micro_time_1, macro_time_2;
    Object micro_time_2, temp_1;
    char temp;
    Declare_special(3);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,72);
    model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
    variable_group_update_structure_qm = 
	    get_non_override_variable_group_update_structure(model_runtime_info);
    current_model_runtime_info_qm = Nil;
    current_model_definition_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      1);
	if (model_runtime_info) {
	    Current_model_runtime_info_qm = model_runtime_info;
	    Current_model_definition_qm = model_definition;
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
	    current_model_queue_qm = 
		    get_model_queue_for_model(Current_model_runtime_info_qm);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_model_queue_qm,Qcurrent_model_queue_qm,current_model_queue_qm,
		    0);
	      if (variable_group_update_structure_qm) {
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      gensymed_symbol = 
			      ISVREF(variable_group_update_structure_qm,
			      (SI_Long)2L);
		      gensymed_symbol_1 = 
			      evaluation_value_value(time_increment);
		      if (INTEGERP(gensymed_symbol_1)) {
			  SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
				  gensymed_symbol_1;
			  ISVREF(gensymed_symbol,(SI_Long)2L) = 
				  FIX((SI_Long)0L);
		      }
		      else {
			  result = ltruncate(lfloat(gensymed_symbol_1,
				  float_constant),_);
			  MVS_2(result,integer_portion,fraction_portion);
			  SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
				  integer_portion;
			  svref_new_value = 
				  l_round(ltimes(fraction_portion,
				  Fraction_modulus_of_compound_fixnum_simulation_time),
				  _);
			  SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
				  svref_new_value;
		      }
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  reclaim_evaluation_value(time_increment);
		  if (IFIX(ISVREF(ISVREF(model_runtime_info,(SI_Long)33L),
			  (SI_Long)1L)) < (SI_Long)0L) {
		      gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)8L);
		      gensymed_symbol_1 = 
			      ISVREF(variable_group_update_structure_qm,
			      (SI_Long)2L);
		      svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		      SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
			      svref_new_value;
		      svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		      SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
			      svref_new_value;
		  }
		  else {
		      gensymed_symbol = ISVREF(model_runtime_info,(SI_Long)8L);
		      gensymed_symbol_1 = ISVREF(model_runtime_info,
			      (SI_Long)33L);
		      gensymed_symbol_2 = 
			      ISVREF(variable_group_update_structure_qm,
			      (SI_Long)2L);
		      macro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		      micro_time_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		      macro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		      micro_time_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		      if (FIXNUM_LT(macro_time_1,macro_time_2))
			  temp_1 = T;
		      else if (FIXNUM_EQ(macro_time_1,macro_time_2))
			  temp_1 = FIXNUM_LT(micro_time_1,micro_time_2) ? 
				  T : Nil;
		      else
			  temp_1 = Qnil;
		      gensymed_symbol_1 = temp_1 ? gensymed_symbol_1 : 
			      gensymed_symbol_2;
		      svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)2L);
		      SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
			      svref_new_value;
		      svref_new_value = ISVREF(gensymed_symbol_1,(SI_Long)1L);
		      SVREF(gensymed_symbol,FIX((SI_Long)1L)) = 
			      svref_new_value;
		  }
	      }
	      update_shortest_simulation_time_increment_for_all_models();
	      result = VALUES_1(SVREF(model_runtime_info,
		      FIX((SI_Long)25L)) = T);
	    POP_SPECIAL();
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_1;   /* "The model ~NF has no variables whose time increments are the one ~
				    *             specified in the model definition."
				    */

/* GET-MODEL-SIMULATION-TIME-INCREMENT */
Object get_model_simulation_time_increment(model_definition)
    Object model_definition;
{
    Object model_runtime_info, variable_group_update_structure_qm;
    Object gensymed_symbol, integer_portion, micro_time, aref_arg_1;
    Object top_of_stack, message_1;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,73);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	model_runtime_info = ISVREF(model_definition,(SI_Long)20L);
	variable_group_update_structure_qm = 
		get_non_override_variable_group_update_structure(model_runtime_info);
	if (variable_group_update_structure_qm) {
	    gensymed_symbol = ISVREF(variable_group_update_structure_qm,
		    (SI_Long)2L);
	    integer_portion = ISVREF(gensymed_symbol,(SI_Long)1L);
	    micro_time = ISVREF(gensymed_symbol,(SI_Long)2L);
	    if (IFIX(micro_time) == (SI_Long)0L) {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    else {
		aref_arg_1 = Simulation_time_managed_float;
		aref_new_value = (double)IFIX(integer_portion) + 
			(double)IFIX(micro_time) / 100000.0;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    }
	    result = copy_managed_float(Simulation_time_managed_float);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_1,model_definition);
	    result = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_2;   /* "There is no current simulator model" */

/* GET-CURRENT-MODEL-DEFINITION */
Object get_current_model_definition()
{
    Object x2, top_of_stack, message_1;
    char temp;

    x_note_fn_call(187,74);
    if (SIMPLE_VECTOR_P(Evaluating_simulator_procedure_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Evaluating_simulator_procedure_qm)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(Evaluating_simulator_procedure_qm,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Evaluating_simulator_procedure_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Evaluating_simulator_procedure_qm);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_2);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_a_matrix, Qcurrent_a_matrix);

DEFINE_VARIABLE_WITH_SYMBOL(Current_lu_matrix, Qcurrent_lu_matrix);

DEFINE_VARIABLE_WITH_SYMBOL(Current_index_array, Qcurrent_index_array);

DEFINE_VARIABLE_WITH_SYMBOL(Current_b_vector, Qcurrent_b_vector);

DEFINE_VARIABLE_WITH_SYMBOL(Current_x_vector, Qcurrent_x_vector);

/* G2-INITIALIZE-LU-DECOMPOSE */
Object g2_initialize_lu_decompose(a,indx,lu)
    Object a, indx, lu;
{
    Object current_a_matrix, current_index_array, current_lu_matrix;
    Declare_special(3);
    Object result;

    x_note_fn_call(187,75);
    current_a_matrix = a;
    current_index_array = indx;
    current_lu_matrix = lu;
    PUSH_SPECIAL_WITH_SYMBOL(Current_lu_matrix,Qcurrent_lu_matrix,current_lu_matrix,
	    2);
      PUSH_SPECIAL_WITH_SYMBOL(Current_index_array,Qcurrent_index_array,current_index_array,
	      1);
	PUSH_SPECIAL_WITH_SYMBOL(Current_a_matrix,Qcurrent_a_matrix,current_a_matrix,
		0);
	  result = check_ludcmp_datatypes(4,ISVREF(a,(SI_Long)23L),
		  ISVREF(a,(SI_Long)20L),ISVREF(indx,(SI_Long)23L),
		  ISVREF(lu,(SI_Long)23L));
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* G2-LU-COMPUTE-SCALING */
Object g2_lu_compute_scaling(a,a_row,lu_row,vv,i)
    Object a, a_row, lu_row, vv, i;
{
    Object current_a_matrix;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,76);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_a_matrix = a;
	PUSH_SPECIAL_WITH_SYMBOL(Current_a_matrix,Qcurrent_a_matrix,current_a_matrix,
		0);
	  result = g2_lu_compute_scaling_1(a_row,lu_row,vv,i);
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_3;   /* "The MATRIX ~NF is singular and therefore cannot be lu decomposed.~
				    *                        The singularity is due to the fact that row ~a contains all zeroes."
				    */

/* G2-LU-COMPUTE-SCALING-1 */
Object g2_lu_compute_scaling_1(a_row,lu_row,vv,i)
    Object a_row, lu_row, vv, i;
{
    Object n_1, aamax_box, element_value_box, abs_value_box, row_for_a;
    Object row_for_lu, aref_arg_1, top_of_stack, message_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    char need_to_copy_qm;
    double aref_new_value, temp, arg, arg_1;

    x_note_fn_call(187,77);
    n_1 = ISVREF(a_row,(SI_Long)20L);
    need_to_copy_qm =  !EQ(a_row,lu_row);
    aamax_box = allocate_managed_float_box();
    element_value_box = allocate_managed_float_box();
    abs_value_box = allocate_managed_float_box();
    row_for_a = ISVREF(a_row,(SI_Long)23L);
    row_for_lu = ISVREF(lu_row,(SI_Long)23L);
    vv = ISVREF(vv,(SI_Long)23L);
    DFLOAT_ISASET_1(aamax_box,(SI_Long)0L,0.0);
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(row_for_a,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(element_value_box,(SI_Long)0L,aref_new_value);
    temp = DFLOAT_ISAREF_1(element_value_box,(SI_Long)0L);
    aref_new_value = ABS(temp);
    DFLOAT_ISASET_1(abs_value_box,(SI_Long)0L,aref_new_value);
    arg = DFLOAT_ISAREF_1(abs_value_box,(SI_Long)0L);
    arg_1 = DFLOAT_ISAREF_1(aamax_box,(SI_Long)0L);
    if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	aref_new_value = DFLOAT_ISAREF_1(abs_value_box,(SI_Long)0L);
	DFLOAT_ISASET_1(aamax_box,(SI_Long)0L,aref_new_value);
    }
    if (need_to_copy_qm) {
	aref_arg_1 = ISVREF(row_for_lu,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	aref_arg_2 = j & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(element_value_box,(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    arg = DFLOAT_ISAREF_1(aamax_box,(SI_Long)0L);
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_3,
		Current_a_matrix,i);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	aref_arg_1 = ISVREF(vv,(IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = IFIX(i) & (SI_Long)1023L;
	aref_new_value = 1.0 / DFLOAT_ISAREF_1(aamax_box,(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    }
    reclaim_managed_simple_float_array_of_length_1(aamax_box);
    reclaim_managed_simple_float_array_of_length_1(element_value_box);
    reclaim_managed_simple_float_array_of_length_1(abs_value_box);
    return VALUES_1(Nil);
}

/* G2-LU-CROUT */
Object g2_lu_crout(a,lu,vv,indx,j)
    Object a, lu, vv, indx, j;
{
    Object current_a_matrix;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,78);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_a_matrix = a;
	PUSH_SPECIAL_WITH_SYMBOL(Current_a_matrix,Qcurrent_a_matrix,current_a_matrix,
		0);
	  result = g2_lu_crout_1(lu,vv,indx,j);
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_4;   /* "Singularity encountered in row ~a while lu decomposing the MATRIX ~NF." */

/* G2-LU-CROUT-1 */
Object g2_lu_crout_1(lu,vv,indx,j)
    Object lu, vv, indx, j;
{
    Object aamax_box, sum_box, dum, imax, n_1, row, ab_loop_iter_flag_;
    Object managed_float_array, temp, a, svref_new_value, svref_new_value_1;
    Object svref_new_value_2, svref_new_value_3, top_of_stack, message_1;
    SI_Long two_n, two_j, i, ab_loop_bind_, i1, k, ab_loop_bind__1, k1, temp_1;
    SI_Long j_1, gensymed_symbol, managed_svref_arg_2, svref_arg_2;
    double aref_new_value, arg, arg_1;
    Declare_special(1);

    x_note_fn_call(187,79);
    aamax_box = allocate_managed_float_box();
    sum_box = allocate_managed_float_box();
    dum = allocate_managed_float_box();
    imax = Nil;
    n_1 = ISVREF(lu,(SI_Long)20L);
    two_n = (SI_Long)2L * IFIX(n_1);
    two_j = (SI_Long)2L * IFIX(j);
    lu = ISVREF(lu,(SI_Long)23L);
    indx = ISVREF(indx,(SI_Long)23L);
    vv = ISVREF(vv,(SI_Long)23L);
    i = (SI_Long)0L;
    ab_loop_bind_ = two_j;
    i1 = (SI_Long)0L;
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      ab_loop_iter_flag_ = T;
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      if ( !TRUEP(ab_loop_iter_flag_))
	  i1 = i1 + (SI_Long)1L;
      Row = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(lu,i + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(i >>  
	      -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L),
	      (SI_Long)23L);
      aref_new_value = DFLOAT_ISAREF_1(ISVREF(Row,(IFIX(j) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      k = (SI_Long)0L;
      ab_loop_bind__1 = i;
      k1 = (SI_Long)0L;
      managed_float_array = Nil;
      ab_loop_iter_flag_ = T;
    next_loop_1:
      if (k >= ab_loop_bind__1)
	  goto end_loop_1;
      if ( !TRUEP(ab_loop_iter_flag_))
	  k1 = k1 + (SI_Long)1L;
      managed_float_array = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(lu,k + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(k >>  
	      -  - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L),
	      (SI_Long)23L);
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L) - 
	      DFLOAT_ISAREF_1(ISVREF(Row,(k1 >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),k1 & (SI_Long)1023L) * 
	      DFLOAT_ISAREF_1(ISVREF(managed_float_array,(IFIX(j) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      ab_loop_iter_flag_ = Nil;
      k = k + (SI_Long)2L;
      goto next_loop_1;
    end_loop_1:
      temp = ISVREF(Row,(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L);
      temp_1 = IFIX(j) & (SI_Long)1023L;
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
      DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
      ab_loop_iter_flag_ = Nil;
      i = i + (SI_Long)2L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    DFLOAT_ISASET_1(aamax_box,(SI_Long)0L,0.0);
    i = two_j;
    ab_loop_bind_ = two_n;
    i1 = IFIX(j);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      ab_loop_iter_flag_ = T;
    next_loop_2:
      if (i >= ab_loop_bind_)
	  goto end_loop_2;
      if ( !TRUEP(ab_loop_iter_flag_))
	  i1 = i1 + (SI_Long)1L;
      Row = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(lu,i + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(i >>  
	      -  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L),
	      (SI_Long)23L);
      aref_new_value = DFLOAT_ISAREF_1(ISVREF(Row,(IFIX(j) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      k = (SI_Long)0L;
      ab_loop_bind__1 = two_j;
      k1 = (SI_Long)0L;
      managed_float_array = Nil;
      ab_loop_iter_flag_ = T;
    next_loop_3:
      if (k >= ab_loop_bind__1)
	  goto end_loop_3;
      if ( !TRUEP(ab_loop_iter_flag_))
	  k1 = k1 + (SI_Long)1L;
      managed_float_array = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(lu,k + 
	      IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(k >>  
	      -  - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L),
	      (SI_Long)23L);
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L) - 
	      DFLOAT_ISAREF_1(ISVREF(Row,(k1 >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),k1 & (SI_Long)1023L) * 
	      DFLOAT_ISAREF_1(ISVREF(managed_float_array,(IFIX(j) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      ab_loop_iter_flag_ = Nil;
      k = k + (SI_Long)2L;
      goto next_loop_3;
    end_loop_3:
      imax = g2_lu_crout_2(Row,j,sum_box,dum,vv,FIX(i1),aamax_box,imax);
      ab_loop_iter_flag_ = Nil;
      i = i + (SI_Long)2L;
      goto next_loop_2;
    end_loop_2:;
    POP_SPECIAL();
    if (FIXNUM_NE(j,imax)) {
	a = lu;
	i = two_j;
	j_1 = IFIX(imax) * (SI_Long)2L;
	svref_new_value = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,i + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  
		-  - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	svref_new_value_1 = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,j_1 + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(j_1 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),j_1 & (SI_Long)1023L);
	temp_1 = j_1 + (SI_Long)1L;
	gensymed_symbol = i + (SI_Long)1L;
	svref_new_value_2 = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L);
	managed_svref_arg_2 = i + (SI_Long)1L;
	gensymed_symbol = j_1 + (SI_Long)1L;
	svref_new_value_3 = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = j_1 + IFIX(Managed_array_index_offset);
	    ISVREF(a,svref_arg_2) = svref_new_value;
	}
	else {
	    temp = ISVREF(a,(j_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = j_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    svref_arg_2 = i + IFIX(Managed_array_index_offset);
	    ISVREF(a,svref_arg_2) = svref_new_value_1;
	}
	else {
	    temp = ISVREF(a,(i >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = i & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = svref_new_value_1;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = temp_1 + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = svref_new_value_2;
	}
	else {
	    temp = ISVREF(a,(temp_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = temp_1 & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value_2;
	}
	if (FIXNUM_LE(ISVREF(a,(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = managed_svref_arg_2 + IFIX(Managed_array_index_offset);
	    ISVREF(a,temp_1) = svref_new_value_3;
	}
	else {
	    temp = ISVREF(a,(managed_svref_arg_2 >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    temp_1 = managed_svref_arg_2 & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = svref_new_value_3;
	}
	temp = ISVREF(vv,(IFIX(imax) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = IFIX(imax) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(vv,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
    }
    if (FIXNUM_LE(ISVREF(indx,(SI_Long)1L),Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(j,Managed_array_index_offset);
	SVREF(indx,temp) = imax;
    }
    else {
	temp = ISVREF(indx,(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = IFIX(j) & (SI_Long)1023L;
	ISVREF(temp,temp_1) = imax;
    }
    arg = DFLOAT_ISAREF_1(ISVREF(ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(lu,two_j + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(two_j >> 
	     -  - (SI_Long)10L) + (SI_Long)2L),two_j & (SI_Long)1023L),
	    (SI_Long)23L),(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(j) & (SI_Long)1023L);
    arg_1 = 0.0;
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_4,j,
		Current_a_matrix);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (FIXNUM_NE(j,FIXNUM_SUB1(n_1))) {
	managed_float_array = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(lu,two_j + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,
		(two_j >>  -  - (SI_Long)10L) + (SI_Long)2L),two_j & 
		(SI_Long)1023L),(SI_Long)23L);
	aref_new_value = 1.0 / DFLOAT_ISAREF_1(ISVREF(managed_float_array,
		(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
		(SI_Long)1023L);
	DFLOAT_ISASET_1(dum,(SI_Long)0L,aref_new_value);
	i = two_j + (SI_Long)2L;
	ab_loop_bind_ = two_n;
	row = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
	next_loop_4:
	  if (i >= ab_loop_bind_)
	      goto end_loop_4;
	  Row = ISVREF(FIXNUM_LE(ISVREF(lu,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(lu,i + 
		  IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(lu,(i 
		  >>  -  - (SI_Long)10L) + (SI_Long)2L),i & 
		  (SI_Long)1023L),(SI_Long)23L);
	  temp = ISVREF(Row,(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	  temp_1 = IFIX(j) & (SI_Long)1023L;
	  aref_new_value = DFLOAT_ISAREF_1(ISVREF(Row,(IFIX(j) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L) * 
		  DFLOAT_ISAREF_1(dum,(SI_Long)0L);
	  DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	  i = i + (SI_Long)2L;
	  goto next_loop_4;
	end_loop_4:;
	POP_SPECIAL();
    }
    reclaim_managed_simple_float_array_of_length_1(aamax_box);
    reclaim_managed_simple_float_array_of_length_1(sum_box);
    reclaim_managed_simple_float_array_of_length_1(dum);
    return VALUES_1(Nil);
}

/* G2-LU-CROUT-2 */
Object g2_lu_crout_2(row,j,sum_box,dum,vv,i1,aamax_box,imax)
    Object row, j, sum_box, dum, vv, i1, aamax_box, imax;
{
    Object aref_arg_1;
    SI_Long aref_arg_2;
    double aref_new_value, temp, temp_1, arg, arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,80);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      aref_arg_1 = ISVREF(Row,(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L);
      aref_arg_2 = IFIX(j) & (SI_Long)1023L;
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
      DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
      temp = DFLOAT_ISAREF_1(ISVREF(vv,(IFIX(i1) >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),IFIX(i1) & (SI_Long)1023L);
      temp_1 = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
      aref_new_value = temp * ABS(temp_1);
      DFLOAT_ISASET_1(dum,(SI_Long)0L,aref_new_value);
      arg = DFLOAT_ISAREF_1(dum,(SI_Long)0L);
      arg_1 = DFLOAT_ISAREF_1(aamax_box,(SI_Long)0L);
      if (arg >= arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	      !inline_nanp_for_comparison(arg_1)) {
	  imax = i1;
	  aref_new_value = DFLOAT_ISAREF_1(dum,(SI_Long)0L);
	  DFLOAT_ISASET_1(aamax_box,(SI_Long)0L,aref_new_value);
      }
      result = VALUES_1(imax);
    POP_SPECIAL();
    return result;
}

/* G2-INITIALIZE-LUBKSB */
Object g2_initialize_lubksb(lu_matrix,index_1,b_vector,x_vector)
    Object lu_matrix, index_1, b_vector, x_vector;
{
    Object current_lu_matrix, current_index_array, current_b_vector;
    Object current_x_vector;
    Declare_special(4);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,81);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_lu_matrix = lu_matrix;
	current_index_array = index_1;
	current_b_vector = b_vector;
	current_x_vector = x_vector;
	PUSH_SPECIAL_WITH_SYMBOL(Current_x_vector,Qcurrent_x_vector,current_x_vector,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_b_vector,Qcurrent_b_vector,current_b_vector,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_index_array,Qcurrent_index_array,current_index_array,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_lu_matrix,Qcurrent_lu_matrix,current_lu_matrix,
		      0);
		result = g2_initialize_lubksb_1(lu_matrix,index_1,b_vector,
			x_vector);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-INITIALIZE-LUBKSB-1 */
Object g2_initialize_lubksb_1(lu_matrix,index_1,b_vector,x_vector)
    Object lu_matrix, index_1, b_vector, x_vector;
{
    Object n_1, b_managed_array, x_managed_array, aref_arg_1;
    SI_Long i, ab_loop_bind_, aref_arg_2;
    double aref_new_value;

    x_note_fn_call(187,82);
    n_1 = ISVREF(lu_matrix,(SI_Long)20L);
    b_managed_array = ISVREF(b_vector,(SI_Long)23L);
    x_managed_array = ISVREF(x_vector,(SI_Long)23L);
    check_lubksb_datatypes(ISVREF(lu_matrix,(SI_Long)23L),n_1,
	    ISVREF(index_1,(SI_Long)23L),b_managed_array,x_managed_array,T);
    if ( !EQ(b_vector,x_vector)) {
	i = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	aref_arg_1 = ISVREF(x_managed_array,(i >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	aref_arg_2 = i & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(b_managed_array,(i >>  -  
		- (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-LU-FORWARD-SUBSTITUTE-ROW */
Object g2_lu_forward_substitute_row(lu_matrix_row,index_1,x,i,ii)
    Object lu_matrix_row, index_1, x, i, ii;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,83);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = g2_lu_forward_substitute_row_1(lu_matrix_row,index_1,x,i,ii);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-LU-FORWARD-SUBSTITUTE-ROW-1 */
Object g2_lu_forward_substitute_row_1(lu_matrix_row,index_1,x,i,ii)
    Object lu_matrix_row, index_1, x, i, ii;
{
    Object ll, row, sum_box, aref_arg_1;
    SI_Long aref_arg_2, j, ab_loop_bind_;
    double aref_new_value, arg, arg_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,84);
    index_1 = ISVREF(index_1,(SI_Long)23L);
    x = ISVREF(x,(SI_Long)23L);
    ll = FIXNUM_LE(ISVREF(index_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_1,
	    IFIX(FIXNUM_ADD(i,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(index_1,(IFIX(i) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
    row = ISVREF(lu_matrix_row,(SI_Long)23L);
    sum_box = allocate_managed_float_box();
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      aref_new_value = DFLOAT_ISAREF_1(ISVREF(x,(IFIX(ll) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(ll) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      aref_arg_1 = ISVREF(x,(IFIX(ll) >>  -  - (SI_Long)10L) + (SI_Long)2L);
      aref_arg_2 = IFIX(ll) & (SI_Long)1023L;
      aref_new_value = DFLOAT_ISAREF_1(ISVREF(x,(IFIX(i) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
      DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
      if (IFIX(ii) != (SI_Long)-1L) {
	  j = IFIX(ii);
	  ab_loop_bind_ = IFIX(i);
	next_loop:
	  if (j >= ab_loop_bind_)
	      goto end_loop;
	  aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L) - 
		  DFLOAT_ISAREF_1(ISVREF(Row,(j >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),j & (SI_Long)1023L) * 
		  DFLOAT_ISAREF_1(ISVREF(x,(j >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),j & (SI_Long)1023L);
	  DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
	  j = j + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
      }
      else {
	  arg = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
	  arg_1 = 0.0;
	  if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		  !inline_nanp_for_comparison(arg_1)))
	      ii = i;
      }
      aref_arg_1 = ISVREF(x,(IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
      aref_arg_2 = IFIX(i) & (SI_Long)1023L;
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
      DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
      reclaim_managed_simple_float_array_of_length_1(sum_box);
      result = VALUES_1(ii);
    POP_SPECIAL();
    return result;
}

/* G2-LU-BACKWARD-SUBSTITUTE-ROW */
Object g2_lu_backward_substitute_row(lu_matrix_row,x,i)
    Object lu_matrix_row, x, i;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,85);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = g2_lu_backward_substitute_row_1(lu_matrix_row,x,i);
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-LU-BACKWARD-SUBSTITUTE-ROW-1 */
Object g2_lu_backward_substitute_row_1(lu_matrix_row,x,i)
    Object lu_matrix_row, x, i;
{
    Object row, sum_box, n_1, aref_arg_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,86);
    x = ISVREF(x,(SI_Long)23L);
    row = ISVREF(lu_matrix_row,(SI_Long)23L);
    sum_box = allocate_managed_float_box();
    n_1 = ISVREF(lu_matrix_row,(SI_Long)20L);
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      aref_new_value = DFLOAT_ISAREF_1(ISVREF(x,(IFIX(i) >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
      DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
      if (FIXNUM_LT(i,FIXNUM_SUB1(n_1))) {
	  j = IFIX(FIXNUM_ADD1(i));
	  ab_loop_bind_ = IFIX(n_1);
	next_loop:
	  if (j >= ab_loop_bind_)
	      goto end_loop;
	  aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L) - 
		  DFLOAT_ISAREF_1(ISVREF(Row,(j >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),j & (SI_Long)1023L) * 
		  DFLOAT_ISAREF_1(ISVREF(x,(j >>  -  - (SI_Long)10L) + 
		  (SI_Long)2L),j & (SI_Long)1023L);
	  DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
	  j = j + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
      }
      aref_arg_1 = ISVREF(x,(IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
      aref_arg_2 = IFIX(i) & (SI_Long)1023L;
      aref_new_value = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L) / 
	      DFLOAT_ISAREF_1(ISVREF(Row,(IFIX(i) >>  -  - (SI_Long)10L) + 
	      (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
      DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
      reclaim_managed_simple_float_array_of_length_1(sum_box);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_5;   /* "A row of the MATRIX ~NF was not an active float array with length >= ~a, ~
				    *          the required minimum length for the matrix operation being attempted."
				    */

/* CHECK-FLOAT-MATRIX-1 */
Object check_float_matrix_1(a,n_1)
    Object a, n_1;
{
    Object row_vector, row_vector_internal, frame_serial_number;
    Object gensymed_symbol_1, gensymed_symbol_2, top_of_stack, message_1;
    SI_Long i, ab_loop_bind_, gensymed_symbol;
    char temp;

    x_note_fn_call(187,87);
    i = (SI_Long)0L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(n_1);
    row_vector = Nil;
    row_vector_internal = Nil;
    frame_serial_number = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    row_vector = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(a,i + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,(i >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
    row_vector_internal = row_vector ? ISVREF(row_vector,(SI_Long)23L) : Nil;
    if (row_vector) {
	gensymed_symbol = i + (SI_Long)1L;
	frame_serial_number = FIXNUM_LE(ISVREF(a,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(a,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(a,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L);
    }
    else
	frame_serial_number = Nil;
    temp =  !TRUEP(row_vector);
    if (temp);
    else {
	gensymed_symbol_1 = ISVREF(row_vector,(SI_Long)3L);
	gensymed_symbol_2 = frame_serial_number;
	temp =  !(FIXNUMP(gensymed_symbol_1) ? (FIXNUMP(gensymed_symbol_2) 
		? FIXNUM_EQ(gensymed_symbol_1,gensymed_symbol_2) : 
		TRUEP(Nil)) : FIXNUMP(gensymed_symbol_2) ? TRUEP(Nil) : 
		FIXNUM_EQ(M_CAR(gensymed_symbol_1),
		M_CAR(gensymed_symbol_2)) && 
		FIXNUM_EQ(M_CDR(gensymed_symbol_1),M_CDR(gensymed_symbol_2)));
    }
    if (temp);
    else
	temp =  !((SI_Long)0L != (IFIX(ISVREF(row_vector,(SI_Long)5L)) & 
		(SI_Long)1L));
    if (temp);
    else
	temp =  !(SIMPLE_VECTOR_P(row_vector_internal) && 
		EQ(ISVREF(row_vector_internal,(SI_Long)0L),
		Managed_float_array_unique_marker));
    if (temp);
    else
	temp =  !FIXNUM_GE(ISVREF(row_vector_internal,(SI_Long)1L),n_1);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_5,
		Current_a_matrix,n_1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    i = i + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(n_1);
    return VALUES_1(Qnil);
}

static Object string_constant_6;   /* "The index array ~NF is not >= ~a, ~
				    *        the required minimum length for the matrix operation being attempted."
				    */

/* CHECK-LUDCMP-DATATYPES */
Object check_ludcmp_datatypes varargs_1(int, n)
{
    Object a, n_1, indx;
    Object lu, top_of_stack, message_1, current_a_matrix;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,88);
    INIT_ARGS_nonrelocating();
    a = REQUIRED_ARG_nonrelocating();
    n_1 = REQUIRED_ARG_nonrelocating();
    indx = REQUIRED_ARG_nonrelocating();
    lu = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !FIXNUM_GE(ISVREF(indx,(SI_Long)1L),n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_6,
		Current_index_array,n_1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    check_float_matrix_1(a,n_1);
    if (lu) {
	current_a_matrix = Current_lu_matrix;
	PUSH_SPECIAL_WITH_SYMBOL(Current_a_matrix,Qcurrent_a_matrix,current_a_matrix,
		0);
	  result = check_float_matrix_1(lu,n_1);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_7;   /* "The b vector ~NF is not >= ~a, ~
				    *         the required minimum length for the matrix operation being attempted."
				    */

static Object string_constant_8;   /* "The x vector ~NF is not >= ~a, ~
				    *         the required minimum length for the matrix operation being attempted."
				    */

/* CHECK-LUBKSB-DATATYPES */
Object check_lubksb_datatypes(lu,n_1,indx,b,x,check_lu_qm)
    Object lu, n_1, indx, b, x, check_lu_qm;
{
    Object top_of_stack, message_1;

    x_note_fn_call(187,89);
    if (check_lu_qm)
	check_ludcmp_datatypes(3,lu,n_1,indx);
    if ( !FIXNUM_GE(ISVREF(b,(SI_Long)1L),n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_7,
		Current_b_vector,n_1);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if ( !FIXNUM_GE(ISVREF(x,(SI_Long)1L),n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_8,
		Current_x_vector,n_1);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_9;   /* "The array ~NF is not the same length as the array ~NF." */

/* CHECK-ARRAY-LENGTHS-COMPATIBLE */
Object check_array_lengths_compatible varargs_1(int, n)
{
    Object array1, array2;
    Object array3, n_1, top_of_stack, message_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(187,90);
    INIT_ARGS_nonrelocating();
    array1 = REQUIRED_ARG_nonrelocating();
    array2 = REQUIRED_ARG_nonrelocating();
    array3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    n_1 = ISVREF(array1,(SI_Long)20L);
    if ( !FIXNUM_EQ(n_1,ISVREF(array2,(SI_Long)20L))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_9,
		array2,array1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (array3 &&  !FIXNUM_EQ(n_1,ISVREF(array3,(SI_Long)20L))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_9,
		array3,array1);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(n_1);
}

static Object string_constant_10;  /* "The specified index ~d is outside the range 0 to ~d." */

/* CHECK-INDEX-WITHIN-BOUNDS */
Object check_index_within_bounds(index_1,max_index)
    Object index_1, max_index;
{
    Object top_of_stack, message_1;

    x_note_fn_call(187,91);
    if (IFIX(index_1) < (SI_Long)0L || FIXNUM_GT(index_1,max_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_10,
		index_1,max_index);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_11;  /* "The array ~NF does not have the required length ~d" */

/* CHECK-ARRAY-LENGTH-COMPATIBLE */
Object check_array_length_compatible(array1,n_1)
    Object array1, n_1;
{
    Object top_of_stack, message_1;

    x_note_fn_call(187,92);
    if ( !FIXNUM_EQ(n_1,ISVREF(array1,(SI_Long)20L))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_11,
		array1,n_1);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(n_1);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_12;  /* "The range array ~NF does not have the required length 4." */

/* CHECK-RANGE-ARRAY */
Object check_range_array(range_array)
    Object range_array;
{
    Object top_of_stack, message_1;

    x_note_fn_call(187,93);
    if ( !((SI_Long)4L == IFIX(ISVREF(range_array,(SI_Long)20L)))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_12,
		range_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(ISVREF(range_array,(SI_Long)23L));
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_13;  /* "The matrix ~NF contains an empty row." */

static Object string_constant_14;  /* "The matrix ~NF contains a row which is not an item." */

static Object Qquantity;           /* quantity */

static Object string_constant_15;  /* "The array ~NF is not a subclass of quantity-array and is therefore ~
				    *        not suitable as a row of the MATRIX ~NF."
				    */

/* CHECK-MATRIX-ROW-TYPE */
Object check_matrix_row_type(matrix,array)
    Object matrix, array;
{
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1, x2, sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(7);

    x_note_fn_call(187,94);
    if ( !TRUEP(array)) {
	top_of_stack = Cached_top_of_stack;
	text_string = Nil;
	snapshots = Nil;
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		6);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  5);
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
		      tformat(2,string_constant_13,matrix);
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string,snapshots);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	if (SIMPLE_VECTOR_P(array) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array)) > (SI_Long)2L &&  
		!EQ(ISVREF(array,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(array,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    top_of_stack = Cached_top_of_stack;
	    text_string = Nil;
	    snapshots = Nil;
	    snapshots_of_related_blocks = Nil;
	    note_blocks_in_tformat = 
		    SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		    6);
	      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		      5);
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
			  tformat(2,string_constant_14,matrix);
			  text_string = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		snapshots = Snapshots_of_related_blocks;
		Snapshots_of_related_blocks = Nil;
		if (Snapshots_of_related_blocks) {
		    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		    Snapshots_of_related_blocks = Nil;
		}
	      POP_SPECIAL();
	    POP_SPECIAL();
	    message_1 = make_error_text(text_string,snapshots);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	    if (temp)
		return VALUES_1(Qinteger);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(array,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
		    return VALUES_1(Qfloat);
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(array,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
			return VALUES_1(Qquantity);
		    else {
			top_of_stack = Cached_top_of_stack;
			text_string = Nil;
			snapshots = Nil;
			snapshots_of_related_blocks = Nil;
			note_blocks_in_tformat = 
				SYMBOL_FUNCTION(Qrecord_block_for_tformat);
			PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
				6);
			  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
				  5);
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      tformat(3,string_constant_15,array,
					      matrix);
				      text_string = 
					      copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			    snapshots = Snapshots_of_related_blocks;
			    Snapshots_of_related_blocks = Nil;
			    if (Snapshots_of_related_blocks) {
				reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
				Snapshots_of_related_blocks = Nil;
			    }
			  POP_SPECIAL();
			POP_SPECIAL();
			message_1 = make_error_text(text_string,snapshots);
			return raw_stack_error_named_error(top_of_stack,
				message_1);
		    }
		}
	    }
	}
    }
}

static Object string_constant_16;  /* "The array ~NF is not of type ~a and is therefore ~
				    *          not compatible with other rows of the MATRIX ~NF."
				    */

static Object string_constant_17;  /* "The length of array ~NF is ~a which is different ~
				    *          from other rows of the MATRIX ~NF."
				    */

/* CHECK-ROW-LENGTH-AND-TYPE-COMPATIBLE */
Object check_row_length_and_type_compatible(matrix,array,length_1,type)
    Object matrix, array, length_1, type;
{
    Object row_type, top_of_stack, message_1, row_length;

    x_note_fn_call(187,95);
    row_type = check_matrix_row_type(matrix,array);
    if ( !EQ(type,row_type)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_16,
		array,row_type,matrix);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    row_length = ISVREF(array,(SI_Long)20L);
    if ( !FIXNUM_EQ(row_length,length_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_17,
		array,row_length,matrix);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return VALUES_1(Nil);
}

/* G2-INITIALIZE-MATRIX-ADD */
Object g2_initialize_matrix_add(matrix1,matrix2,matrix3)
    Object matrix1, matrix2, matrix3;
{
    x_note_fn_call(187,96);
    return check_array_lengths_compatible(3,matrix1,matrix2,matrix3);
}

DEFINE_VARIABLE_WITH_SYMBOL(Subtract_arrays_instead_qm, Qsubtract_arrays_instead_qm);

static Object string_constant_18;  /* "All arrays must be of non-zero length" */

static Object string_constant_19;  /* "a row add" */

/* G2-VECTOR-ADD */
Object g2_vector_add(vector1,vector2,vector3,add_or_subtract)
    Object vector1, vector2, vector3, add_or_subtract;
{
    Object temp, temp_1, top_of_stack, message_1, subtract_arrays_instead_qm;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;
    Declare_stack_pointer;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,97);
    SAVE_STACK();
    temp = ISVREF(vector1,(SI_Long)20L);
    temp_1 = FIX((SI_Long)0L);
    if (NUM_GT(temp,temp_1)) {
	temp_1 = ISVREF(vector2,(SI_Long)20L);
	temp = FIX((SI_Long)0L);
	temp_2 = NUM_GT(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp_1 = ISVREF(vector3,(SI_Long)20L);
	temp = FIX((SI_Long)0L);
	temp_2 = NUM_GT(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_18);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    barrier();
    subtract_arrays_instead_qm = IFIX(add_or_subtract) != (SI_Long)0L ? T :
	     Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Subtract_arrays_instead_qm,Qsubtract_arrays_instead_qm,subtract_arrays_instead_qm,
	    0);
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	      temp_2 = (SI_Long)0L < gensymed_symbol;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Integer_array_class_description,
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
		  temp_2 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2) {
	      sub_class_bit_vector = ISVREF(ISVREF(vector3,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Integer_array_class_description,
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
		  temp_2 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      result = g2_integer_vector_add(vector1,vector2,vector3);
	  else {
	      sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
		  temp_2 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  sub_class_bit_vector = ISVREF(ISVREF(vector2,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Float_array_class_description,
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
		      temp_2 = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2) {
		  sub_class_bit_vector = ISVREF(ISVREF(vector3,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Float_array_class_description,
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
		      temp_2 = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp_2 = TRUEP(Nil);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2)
		  result = g2_float_vector_add(vector1,vector2,vector3);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(vector1,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Quantity_array_class_description,
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
		      temp_2 = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2) {
		      sub_class_bit_vector = ISVREF(ISVREF(vector2,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Quantity_array_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp_2 = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2) {
		      sub_class_bit_vector = ISVREF(ISVREF(vector3,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Quantity_array_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp_2 = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(Nil);
		  if (temp_2)
		      result = g2_quantity_vector_add(vector1,vector2,vector3);
		  else
		      result = signal_invalid_vectors(gensym_list_3(vector1,
			      vector2,vector3),string_constant_19);
	      }
	  }
      }
      POP_LOCAL_ALLOCATION(0,0);
      SAVE_VALUES(result);
      barrier();
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

Object Max_number_of_array_elements_to_do = UNBOUND;

/* G2-VECTOR-ADD-NEW */
Object g2_vector_add_new(vector1,vector2,vector3)
    Object vector1, vector2, vector3;
{
    Object n_1, top_of_stack, message_1, sub_class_bit_vector, managed_array_1;
    Object managed_array_2, managed_array_3, temp_1, gensymed_symbol_3;
    Object n_minus_1, temp_3, end_value_of_j, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, ab_loop_bind_, temp_2;
    SI_Long svref_new_value, k;
    char temp;
    double aref_new_value, temp_5, temp_6;
    Declare_stack_pointer;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(187,98);
    SAVE_STACK();
    n_1 = check_array_lengths_compatible(3,vector1,vector2,vector3);
    if (IFIX(n_1) == (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_18);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector3,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    managed_array_1 = ISVREF(vector1,(SI_Long)23L);
	    managed_array_2 = ISVREF(vector2,(SI_Long)23L);
	    managed_array_3 = ISVREF(vector3,(SI_Long)23L);
	    gensymed_symbol = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(n_1);
	  next_loop:
	    if (gensymed_symbol >= ab_loop_bind_)
		goto end_loop;
	    temp_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = gensymed_symbol & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array_1,
		    (gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    gensymed_symbol & (SI_Long)1023L) + 
		    DFLOAT_ISAREF_1(ISVREF(managed_array_2,
		    (gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    gensymed_symbol & (SI_Long)1023L);
	    DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	    gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector3,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		managed_array_1 = ISVREF(vector1,(SI_Long)23L);
		managed_array_2 = ISVREF(vector2,(SI_Long)23L);
		managed_array_3 = ISVREF(vector3,(SI_Long)23L);
		gensymed_symbol = (SI_Long)0L;
		ab_loop_bind_ = IFIX(n_1);
	      next_loop_1:
		if (gensymed_symbol >= ab_loop_bind_)
		    goto end_loop_1;
		if (FIXNUM_LE(ISVREF(managed_array_3,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_2 = gensymed_symbol + 
			    IFIX(Managed_array_index_offset);
		    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_1,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_2,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
		    ISVREF(managed_array_3,temp_2) = FIX(svref_new_value);
		}
		else {
		    temp_1 = ISVREF(managed_array_3,(gensymed_symbol >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_2 = gensymed_symbol & (SI_Long)1023L;
		    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_1,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_2,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
		    ISVREF(temp_1,temp_2) = FIX(svref_new_value);
		}
		gensymed_symbol = gensymed_symbol + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		result = VALUES_1(Qnil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector2,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector3,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    managed_array_1 = ISVREF(vector1,(SI_Long)23L);
		    managed_array_2 = ISVREF(vector2,(SI_Long)23L);
		    managed_array_3 = ISVREF(vector3,(SI_Long)23L);
		    gensymed_symbol_3 = FIX((SI_Long)0L);
		  next_loop_2:
		    n_minus_1 = FIXNUM_SUB1(n_1);
		    temp_3 = FIXNUM_ADD(gensymed_symbol_3,
			    Max_number_of_array_elements_to_do);
		    end_value_of_j = FIXNUM_MIN(n_minus_1,temp_3);
		    if (FIXNUM_GT(gensymed_symbol_3,n_minus_1)) {
			result = VALUES_1(Nil);
			goto end_1;
		    }
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      next_loop_3:
			temp_3 = gensymed_symbol_3;
			temp_4 = get_quantity_element(managed_array_1,
				gensymed_symbol_3);
			temp_5 = DOUBLE_FLOAT_TO_DOUBLE(temp_4);
			temp_4 = get_quantity_element(managed_array_2,
				gensymed_symbol_3);
			temp_6 = DOUBLE_FLOAT_TO_DOUBLE(temp_4);
			set_quantity_element(managed_array_3,temp_3,
				DOUBLE_TO_DOUBLE_FLOAT(temp_5 + temp_6));
			if (FIXNUM_GE(gensymed_symbol_3,n_minus_1)) {
			    gensymed_symbol_3 = Nil;
			    goto end_2;
			}
			if (FIXNUM_EQ(gensymed_symbol_3,end_value_of_j)) {
			    gensymed_symbol_3 = end_value_of_j;
			    goto end_2;
			}
			gensymed_symbol_3 = FIXNUM_ADD1(gensymed_symbol_3);
			goto next_loop_3;
		      end_loop_2:
			gensymed_symbol_3 = Qnil;
		      end_2:;
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		    if ( !TRUEP(gensymed_symbol_3))
			goto end_loop_3;
		    goto next_loop_2;
		  end_loop_3:
		    result = VALUES_1(Qnil);
		  end_1:;
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(vector1,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Item_array_class_description,
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
		    if (temp) {
			sub_class_bit_vector = ISVREF(ISVREF(vector2,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Item_array_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = ISVREF(ISVREF(vector3,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Item_array_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			k = (SI_Long)0L;
			ab_loop_bind_ = IFIX(n_1);
		      next_loop_4:
			if (k >= ab_loop_bind_)
			    goto end_loop_4;
			temp_3 = g2_array_aref(vector1,FIX(k));
			temp_4 = g2_array_aref(vector2,FIX(k));
			g2_vector_add_new(temp_3,temp_4,
				g2_array_aref(vector3,FIX(k)));
			k = k + (SI_Long)1L;
			goto next_loop_4;
		      end_loop_4:
			result = VALUES_1(Qnil);
		    }
		    else
			result = signal_invalid_vectors(gensym_list_3(vector1,
				vector2,vector3),string_constant_19);
		}
	    }
	}
    }
    POP_LOCAL_ALLOCATION(1,1);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-VECTOR-SUBSTRACT */
Object g2_vector_substract(vector1,vector2,vector3)
    Object vector1, vector2, vector3;
{
    Object n_1, top_of_stack, message_1, sub_class_bit_vector, managed_array_1;
    Object managed_array_2, managed_array_3, temp_1, gensymed_symbol_3;
    Object n_minus_1, temp_3, end_value_of_j, temp_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, ab_loop_bind_, temp_2;
    SI_Long svref_new_value, k;
    char temp;
    double aref_new_value, temp_5, temp_6;
    Declare_stack_pointer;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(187,99);
    SAVE_STACK();
    n_1 = check_array_lengths_compatible(3,vector1,vector2,vector3);
    if (IFIX(n_1) == (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_18);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector3,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    managed_array_1 = ISVREF(vector1,(SI_Long)23L);
	    managed_array_2 = ISVREF(vector2,(SI_Long)23L);
	    managed_array_3 = ISVREF(vector3,(SI_Long)23L);
	    gensymed_symbol = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(n_1);
	  next_loop:
	    if (gensymed_symbol >= ab_loop_bind_)
		goto end_loop;
	    temp_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = gensymed_symbol & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array_1,
		    (gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    gensymed_symbol & (SI_Long)1023L) - 
		    DFLOAT_ISAREF_1(ISVREF(managed_array_2,
		    (gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    gensymed_symbol & (SI_Long)1023L);
	    DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	    gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    result = VALUES_1(Qnil);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector3,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		managed_array_1 = ISVREF(vector1,(SI_Long)23L);
		managed_array_2 = ISVREF(vector2,(SI_Long)23L);
		managed_array_3 = ISVREF(vector3,(SI_Long)23L);
		gensymed_symbol = (SI_Long)0L;
		ab_loop_bind_ = IFIX(n_1);
	      next_loop_1:
		if (gensymed_symbol >= ab_loop_bind_)
		    goto end_loop_1;
		if (FIXNUM_LE(ISVREF(managed_array_3,(SI_Long)1L),
			Maximum_in_place_array_size)) {
		    temp_2 = gensymed_symbol + 
			    IFIX(Managed_array_index_offset);
		    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_1,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_2,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
		    ISVREF(managed_array_3,temp_2) = FIX(svref_new_value);
		}
		else {
		    temp_1 = ISVREF(managed_array_3,(gensymed_symbol >>  - 
			     - (SI_Long)10L) + (SI_Long)2L);
		    temp_2 = gensymed_symbol & (SI_Long)1023L;
		    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_1,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
			    (SI_Long)1L),Maximum_in_place_array_size) ? 
			    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
			    IFIX(Managed_array_index_offset))) : 
			    IFIX(ISVREF(ISVREF(managed_array_2,
			    (gensymed_symbol >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),gensymed_symbol & (SI_Long)1023L));
		    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
		    ISVREF(temp_1,temp_2) = FIX(svref_new_value);
		}
		gensymed_symbol = gensymed_symbol + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		result = VALUES_1(Qnil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector2,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector3,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    managed_array_1 = ISVREF(vector1,(SI_Long)23L);
		    managed_array_2 = ISVREF(vector2,(SI_Long)23L);
		    managed_array_3 = ISVREF(vector3,(SI_Long)23L);
		    gensymed_symbol_3 = FIX((SI_Long)0L);
		  next_loop_2:
		    n_minus_1 = FIXNUM_SUB1(n_1);
		    temp_3 = FIXNUM_ADD(gensymed_symbol_3,
			    Max_number_of_array_elements_to_do);
		    end_value_of_j = FIXNUM_MIN(n_minus_1,temp_3);
		    if (FIXNUM_GT(gensymed_symbol_3,n_minus_1)) {
			result = VALUES_1(Nil);
			goto end_1;
		    }
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      next_loop_3:
			temp_3 = gensymed_symbol_3;
			temp_4 = get_quantity_element(managed_array_1,
				gensymed_symbol_3);
			temp_5 = DOUBLE_FLOAT_TO_DOUBLE(temp_4);
			temp_4 = get_quantity_element(managed_array_2,
				gensymed_symbol_3);
			temp_6 = DOUBLE_FLOAT_TO_DOUBLE(temp_4);
			set_quantity_element(managed_array_3,temp_3,
				DOUBLE_TO_DOUBLE_FLOAT(temp_5 - temp_6));
			if (FIXNUM_GE(gensymed_symbol_3,n_minus_1)) {
			    gensymed_symbol_3 = Nil;
			    goto end_2;
			}
			if (FIXNUM_EQ(gensymed_symbol_3,end_value_of_j)) {
			    gensymed_symbol_3 = end_value_of_j;
			    goto end_2;
			}
			gensymed_symbol_3 = FIXNUM_ADD1(gensymed_symbol_3);
			goto next_loop_3;
		      end_loop_2:
			gensymed_symbol_3 = Qnil;
		      end_2:;
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		    if ( !TRUEP(gensymed_symbol_3))
			goto end_loop_3;
		    goto next_loop_2;
		  end_loop_3:
		    result = VALUES_1(Qnil);
		  end_1:;
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(vector1,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Item_array_class_description,
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
		    if (temp) {
			sub_class_bit_vector = ISVREF(ISVREF(vector2,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Item_array_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			sub_class_bit_vector = ISVREF(ISVREF(vector3,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Item_array_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp = TRUEP(Nil);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			k = (SI_Long)0L;
			ab_loop_bind_ = IFIX(n_1);
		      next_loop_4:
			if (k >= ab_loop_bind_)
			    goto end_loop_4;
			temp_3 = g2_array_aref(vector1,FIX(k));
			temp_4 = g2_array_aref(vector2,FIX(k));
			g2_vector_substract(temp_3,temp_4,
				g2_array_aref(vector3,FIX(k)));
			k = k + (SI_Long)1L;
			goto next_loop_4;
		      end_loop_4:
			result = VALUES_1(Qnil);
		    }
		    else
			result = signal_invalid_vectors(gensym_list_3(vector1,
				vector2,vector3),string_constant_19);
		}
	    }
	}
    }
    POP_LOCAL_ALLOCATION(1,1);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_20;  /* "The elements of item-arrays given to g2-array-copy must be quantity-arrays." */

/* G2-INITIALIZE-MATRIX-COPY */
Object g2_initialize_matrix_copy(matrix1,matrix2)
    Object matrix1, matrix2;
{
    Object array_lengths_if_non_zero_and_equal, array_element, x2;
    Object sub_class_bit_vector, top_of_stack, message_1;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(187,100);
    array_lengths_if_non_zero_and_equal = check_array_lengths_compatible(2,
	    matrix1,matrix2);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(matrix1,(SI_Long)20L));
    array_element = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    array_element = g2_array_aref(matrix1,FIX(index_1));
    if (SIMPLE_VECTOR_P(array_element) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_element)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(array_element,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(array_element,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(array_element,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Quantity_array_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	temp = TRUEP(Nil);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = TRUEP(T);
    goto end_1;
    temp = TRUEP(Qnil);
  end_1:;
    if (temp) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(matrix2,(SI_Long)20L));
	array_element = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	array_element = g2_array_aref(matrix2,FIX(index_1));
	if (SIMPLE_VECTOR_P(array_element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(array_element)) > 
		(SI_Long)2L &&  !EQ(ISVREF(array_element,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(array_element,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(array_element,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantity_array_class_description,
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
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    temp = TRUEP(Nil);
	    goto end_2;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(T);
	goto end_2;
	temp = TRUEP(Qnil);
      end_2:;
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_20);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(array_lengths_if_non_zero_and_equal);
}

static Object string_constant_21;  /* "a row copy" */

/* G2-VECTOR-COPY */
Object g2_vector_copy(vector1,vector2)
    Object vector1, vector2;
{
    Object length1, length2, top_of_stack, message_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,101);
    SAVE_STACK();
    length1 = ISVREF(vector1,(SI_Long)20L);
    length2 = ISVREF(vector2,(SI_Long)20L);
    if ( !(IFIX(length1) > (SI_Long)0L && IFIX(length2) > (SI_Long)0L)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_18);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp)
	    result = g2_integer_vector_copy(vector1,vector2);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = g2_float_vector_copy(vector1,vector2);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector2,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    result = g2_quantity_vector_copy(vector1,vector2);
		else
		    result = signal_invalid_vectors(gensym_list_2(vector1,
			    vector2),string_constant_21);
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-INITIALIZE-MATRIX-EQUAL */
Object g2_initialize_matrix_equal(matrix1,matrix2)
    Object matrix1, matrix2;
{
    x_note_fn_call(187,102);
    return check_array_lengths_compatible(2,matrix1,matrix2);
}

static Object string_constant_22;  /* "an equal test" */

static Object Qtruth_value;        /* truth-value */

/* G2-VECTOR-EQUAL */
Object g2_vector_equal(vector1,vector2)
    Object vector1, vector2;
{
    Object temp, temp_1, top_of_stack, message_1, sub_class_bit_vector;
    Object equality_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_2;
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,103);
    SAVE_STACK();
    temp = ISVREF(vector1,(SI_Long)20L);
    temp_1 = FIX((SI_Long)0L);
    if (NUM_GT(temp,temp_1)) {
	temp_1 = ISVREF(vector2,(SI_Long)20L);
	temp = FIX((SI_Long)0L);
	temp_2 = NUM_GT(temp_1,temp);
    }
    else
	temp_2 = TRUEP(Nil);
    if ( !temp_2) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_18);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	    temp_2 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
		temp_2 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    equality_qm = g2_integer_vector_equal(vector1,vector2);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
		temp_2 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
		    temp_2 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		equality_qm = g2_float_vector_equal(vector1,vector2);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		    temp_2 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    sub_class_bit_vector = ISVREF(ISVREF(vector2,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
			temp_2 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2)
		    equality_qm = g2_quantity_vector_equal(vector1,vector2);
		else
		    equality_qm = 
			    signal_invalid_vectors(gensym_list_2(vector1,
			    vector2),string_constant_22);
	    }
	}
	gensymed_symbol = equality_qm ? IFIX(Truth) : IFIX(Falsity);
	if (gensymed_symbol == IFIX(Truth))
	    result = VALUES_1(Evaluation_true_value);
	else if (gensymed_symbol == IFIX(Falsity))
	    result = VALUES_1(Evaluation_false_value);
	else
	    result = eval_cons_1(FIX(gensymed_symbol),Qtruth_value);
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-INITIALIZE-MATRIX-TRANSPOSE */
Object g2_initialize_matrix_transpose(matrix1,matrix2)
    Object matrix1, matrix2;
{
    Object m, n_1, n_for_square, type;
    Object result;

    x_note_fn_call(187,104);
    result = check_matrices_compatible_for_transpose(matrix1,matrix2);
    MVS_4(result,m,n_1,n_for_square,type);
    return VALUES_4(m,n_1,n_for_square,type);
}

/* G2-TRANSPOSE-ROW */
Object g2_transpose_row(i,begin_j,end_j,type,swap_qm,matrix1,matrix2)
    Object i, begin_j, end_j, type, swap_qm, matrix1, matrix2;
{
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,105);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	type = evaluation_value_value(type);
	swap_qm = IFIX(swap_qm) == (SI_Long)1L ? T : Nil;
	result = transpose_row(i,begin_j,end_j,type,swap_qm,ISVREF(matrix1,
		(SI_Long)23L),ISVREF(matrix2,(SI_Long)23L));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-ARRAY-MULTIPLY */
Object g2_array_multiply(g2_array1,g2_array2)
    Object g2_array1, g2_array2;
{
    Object result_qm;
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,106);
    SAVE_STACK();
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result_qm = g2_vector_multiply(g2_array1,g2_array2);
	result = make_evaluation_quantity(result_qm);
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-SCALAR-MULTIPLY */
Object g2_scalar_multiply(g2_array1,g2_array2,x)
    Object g2_array1, g2_array2, x;
{
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,107);
    SAVE_STACK();
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
	result = g2_scalar_multiply_1(g2_array1,g2_array2,
		evaluation_value_value(x));
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    reclaim_evaluation_value(x);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-MATRIX-VECTOR-TO-VECTOR-MULTIPLY */
Object g2_matrix_vector_to_vector_multiply(matrix_vector,vector1,vector2,
	    index_1)
    Object matrix_vector, vector1, vector2, index_1;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,108);
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp)
	    g2_matrix_to_integer_vector_multiply(matrix_vector,vector1,
		    vector2,index_1);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp)
		g2_matrix_to_float_vector_multiply(matrix_vector,vector1,
			vector2,index_1);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		    g2_matrix_to_quantity_vector_multiply(matrix_vector,
			    vector1,vector2,index_1);
	    }
	}
	barrier();
	result = VALUES_1(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* G2-INITIALIZE-MATRIX-MULTIPLY */
Object g2_initialize_matrix_multiply(matrix1,matrix2,matrix3)
    Object matrix1, matrix2, matrix3;
{
    Object m1, m2, n2, type;
    Object result;

    x_note_fn_call(187,109);
    result = check_matrices_compatible_for_multiply(matrix1,matrix2,matrix3);
    MVS_4(result,m1,m2,n2,type);
    return VALUES_4(m1,m2,n2,type);
}

/* G2-MATRIX-TO-MATRIX-MULTIPLY */
Object g2_matrix_to_matrix_multiply(j,m2,type,matrix1_vector,matrix2,
	    matrix3_vector)
    Object j, m2, type, matrix1_vector, matrix2, matrix3_vector;
{
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,110);
    SAVE_STACK();
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	type = evaluation_value_value(type);
	result = multiply_row(j,m2,type,ISVREF(matrix1_vector,
		(SI_Long)23L),ISVREF(matrix2,(SI_Long)23L),
		ISVREF(matrix3_vector,(SI_Long)23L));
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_23;  /* "Error attempting ~a on an array which does not exist.  " */

static Object string_constant_24;  /* "Error attempting ~a on something which is not an array.  " */

static Object string_constant_25;  /* "Please check system procedure arguments, and contents of arguments." */

static Object string_constant_26;  /* "and" */

static Object string_constant_27;  /* " are not compatible for ~a." */

/* SIGNAL-INVALID-VECTORS */
Object signal_invalid_vectors(vector_list,operation)
    Object vector_list, operation;
{
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object vector_1, ab_loop_list_, x2, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(187,111);
    top_of_stack = Cached_top_of_stack;
    text_string = Nil;
    snapshots = Nil;
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
	      5);
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
		  vector_1 = Nil;
		  ab_loop_list_ = vector_list;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  vector_1 = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if (SIMPLE_VECTOR_P(vector_1) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(vector_1,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(vector_1,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if ( !temp) {
		      if ( !TRUEP(vector_1))
			  tformat(2,string_constant_23,operation);
		      else
			  tformat(2,string_constant_24,operation);
		      tformat(1,string_constant_25);
		      temp = TRUEP(T);
		      goto end_1;
		  }
		  goto next_loop;
		end_loop:
		  temp = TRUEP(Qnil);
		end_1:;
		  if ( !temp) {
		      write_list_in_chicago_style(3,vector_list,
			      string_constant_26,T);
		      reclaim_gensym_list_1(vector_list);
		      tformat(2,string_constant_27,operation);
		  }
		  text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	snapshots = Snapshots_of_related_blocks;
	Snapshots_of_related_blocks = Nil;
	if (Snapshots_of_related_blocks) {
	    reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	    Snapshots_of_related_blocks = Nil;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    message_1 = make_error_text(text_string,snapshots);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

/* GET-MATRIX-ROW */
Object get_matrix_row(matrix,i)
    Object matrix, i;
{
    SI_Long gensymed_symbol;

    x_note_fn_call(187,112);
    gensymed_symbol = (SI_Long)2L * IFIX(i);
    if (FIXNUM_LE(ISVREF(matrix,(SI_Long)1L),Maximum_in_place_array_size))
	return VALUES_1(ISVREF(matrix,gensymed_symbol + 
		IFIX(Managed_array_index_offset)));
    else
	return VALUES_1(ISVREF(ISVREF(matrix,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L));
}

/* GET-QUANTITY-ELEMENT */
Object get_quantity_element(managed_array,i)
    Object managed_array, i;
{
    Object value_of_managed_array, temp, managed_number;

    x_note_fn_call(187,113);
    value_of_managed_array = managed_array;
    if (SIMPLE_VECTOR_P(value_of_managed_array) && 
	    EQ(ISVREF(value_of_managed_array,(SI_Long)0L),
	    Managed_float_array_unique_marker))
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(value_of_managed_array,
		(IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(i) & 
		(SI_Long)1023L));
    else {
	managed_number = FIXNUM_LE(ISVREF(value_of_managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(value_of_managed_array,IFIX(FIXNUM_ADD(i,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(value_of_managed_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) == (SI_Long)1L)
	    temp = aref1(managed_number,FIX((SI_Long)0L));
	else
	    temp = managed_number;
    }
    return lfloat(temp,float_constant);
}

/* SET-QUANTITY-ELEMENT */
Object set_quantity_element(managed_array,i,value)
    Object managed_array, i, value;
{
    Object value_of_managed_array, temp, temp_2, store_managed_number_arg;
    Object svref_new_value;
    SI_Long temp_1;
    double aref_new_value;

    x_note_fn_call(187,114);
    value_of_managed_array = managed_array;
    if (SIMPLE_VECTOR_P(value_of_managed_array) && 
	    EQ(ISVREF(value_of_managed_array,(SI_Long)0L),
	    Managed_float_array_unique_marker)) {
	temp = ISVREF(value_of_managed_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_1 = IFIX(i) & (SI_Long)1023L;
	temp_2 = lfloat(value,float_constant);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	return VALUES_1(Nil);
    }
    else {
	store_managed_number_arg = value;
	svref_new_value = 
		store_managed_number_function(FIXNUM_LE(ISVREF(value_of_managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(value_of_managed_array,IFIX(FIXNUM_ADD(i,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(value_of_managed_array,(IFIX(i) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(i) & (SI_Long)1023L),
		store_managed_number_arg);
	if (FIXNUM_LE(ISVREF(value_of_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(i,Managed_array_index_offset);
	    return VALUES_1(SVREF(value_of_managed_array,temp) = 
		    svref_new_value);
	}
	else {
	    temp = ISVREF(value_of_managed_array,(IFIX(i) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(i) & (SI_Long)1023L;
	    return VALUES_1(ISVREF(temp,temp_1) = svref_new_value);
	}
    }
}

/* G2-INTEGER-VECTOR-ADD */
Object g2_integer_vector_add(vector1,vector2,vector3)
    Object vector1, vector2, vector3;
{
    Object n_1, managed_array_1, managed_array_2, managed_array_3, svref_arg_1;
    SI_Long gensymed_symbol, ab_loop_bind_, svref_arg_2, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, svref_new_value;

    x_note_fn_call(187,115);
    n_1 = check_array_lengths_compatible(3,vector1,vector2,vector3);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    managed_array_3 = ACCESS_ONCE(ISVREF(vector3,(SI_Long)23L));
    if (Subtract_arrays_instead_qm) {
	gensymed_symbol = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
      next_loop:
	if (gensymed_symbol >= ab_loop_bind_)
	    goto end_loop;
	if (FIXNUM_LE(ISVREF(managed_array_3,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_1,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_2,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
	    ISVREF(managed_array_3,svref_arg_2) = FIX(svref_new_value);
	}
	else {
	    svref_arg_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_1,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_2,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    svref_new_value = gensymed_symbol_1 - gensymed_symbol_2;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX(svref_new_value);
	}
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	gensymed_symbol = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
      next_loop_1:
	if (gensymed_symbol >= ab_loop_bind_)
	    goto end_loop_1;
	if (FIXNUM_LE(ISVREF(managed_array_3,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol + IFIX(Managed_array_index_offset);
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_1,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_2,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
	    ISVREF(managed_array_3,svref_arg_2) = FIX(svref_new_value);
	}
	else {
	    svref_arg_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_1,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_1,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(managed_array_2,gensymed_symbol + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(managed_array_2,(gensymed_symbol >> 
		     -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L));
	    svref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
	    ISVREF(svref_arg_1,svref_arg_2) = FIX(svref_new_value);
	}
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* G2-FLOAT-VECTOR-ADD */
Object g2_float_vector_add(vector1,vector2,vector3)
    Object vector1, vector2, vector3;
{
    Object n_1, managed_array_1, managed_array_2, managed_array_3, aref_arg_1;
    SI_Long gensymed_symbol, ab_loop_bind_, aref_arg_2;
    double aref_new_value;

    x_note_fn_call(187,116);
    n_1 = check_array_lengths_compatible(3,vector1,vector2,vector3);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    managed_array_3 = ACCESS_ONCE(ISVREF(vector3,(SI_Long)23L));
    if (Subtract_arrays_instead_qm) {
	gensymed_symbol = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
      next_loop:
	if (gensymed_symbol >= ab_loop_bind_)
	    goto end_loop;
	aref_arg_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array_1,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L) - 
		DFLOAT_ISAREF_1(ISVREF(managed_array_2,(gensymed_symbol >> 
		 -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	gensymed_symbol = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
      next_loop_1:
	if (gensymed_symbol >= ab_loop_bind_)
	    goto end_loop_1;
	aref_arg_1 = ISVREF(managed_array_3,(gensymed_symbol >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = gensymed_symbol & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array_1,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L) + 
		DFLOAT_ISAREF_1(ISVREF(managed_array_2,(gensymed_symbol >> 
		 -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

/* G2-QUANTITY-VECTOR-ADD */
Object g2_quantity_vector_add(vector1,vector2,vector3)
    Object vector1, vector2, vector3;
{
    Object n_1, managed_array_1, managed_array_2, managed_array_3;
    Object gensymed_symbol, n_minus_1, temp, end_value_of_j, temp_1;
    double temp_2, temp_3;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,117);
    n_1 = check_array_lengths_compatible(3,vector1,vector2,vector3);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    managed_array_3 = ACCESS_ONCE(ISVREF(vector3,(SI_Long)23L));
    if (Subtract_arrays_instead_qm) {
	gensymed_symbol = FIX((SI_Long)0L);
      next_loop:
	n_minus_1 = FIXNUM_SUB1(n_1);
	temp = FIXNUM_ADD(gensymed_symbol,Max_number_of_array_elements_to_do);
	end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
	if (FIXNUM_GT(gensymed_symbol,n_minus_1))
	    return VALUES_1(Nil);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_1:
	    temp = gensymed_symbol;
	    temp_1 = get_quantity_element(managed_array_1,gensymed_symbol);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    temp_1 = get_quantity_element(managed_array_2,gensymed_symbol);
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    set_quantity_element(managed_array_3,temp,
		    DOUBLE_TO_DOUBLE_FLOAT(temp_2 - temp_3));
	    if (FIXNUM_GE(gensymed_symbol,n_minus_1)) {
		gensymed_symbol = Nil;
		goto end_1;
	    }
	    if (FIXNUM_EQ(gensymed_symbol,end_value_of_j)) {
		gensymed_symbol = end_value_of_j;
		goto end_1;
	    }
	    gensymed_symbol = FIXNUM_ADD1(gensymed_symbol);
	    goto next_loop_1;
	  end_loop:
	    gensymed_symbol = Qnil;
	  end_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	goto next_loop;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else {
	gensymed_symbol = FIX((SI_Long)0L);
      next_loop_2:
	n_minus_1 = FIXNUM_SUB1(n_1);
	temp = FIXNUM_ADD(gensymed_symbol,Max_number_of_array_elements_to_do);
	end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
	if (FIXNUM_GT(gensymed_symbol,n_minus_1))
	    return VALUES_1(Nil);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_3:
	    temp = gensymed_symbol;
	    temp_1 = get_quantity_element(managed_array_1,gensymed_symbol);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    temp_1 = get_quantity_element(managed_array_2,gensymed_symbol);
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    set_quantity_element(managed_array_3,temp,
		    DOUBLE_TO_DOUBLE_FLOAT(temp_2 + temp_3));
	    if (FIXNUM_GE(gensymed_symbol,n_minus_1)) {
		gensymed_symbol = Nil;
		goto end_2;
	    }
	    if (FIXNUM_EQ(gensymed_symbol,end_value_of_j)) {
		gensymed_symbol = end_value_of_j;
		goto end_2;
	    }
	    gensymed_symbol = FIXNUM_ADD1(gensymed_symbol);
	    goto next_loop_3;
	  end_loop_2:
	    gensymed_symbol = Qnil;
	  end_2:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_3;
	goto next_loop_2;
      end_loop_3:
	return VALUES_1(Qnil);
    }
}

/* G2-INTEGER-VECTOR-EQUAL */
Object g2_integer_vector_equal(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2;
    SI_Long j, ab_loop_bind_;

    x_note_fn_call(187,118);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_NE(FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array_1,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array_1,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L),
	    FIXNUM_LE(ISVREF(managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array_2,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L)))
	return VALUES_1(Nil);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* G2-INTEGER-VECTOR-COPY */
Object g2_integer_vector_copy(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, temp, svref_new_value;
    SI_Long j, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(187,119);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = j + IFIX(Managed_array_index_offset);
	temp = FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array_1,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array_1,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),j & (SI_Long)1023L);
	ISVREF(managed_array_2,svref_arg_2) = temp;
    }
    else {
	temp = ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = j & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array_1,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array_1,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L),j & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-FLOAT-VECTOR-EQUAL */
Object g2_float_vector_equal(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2;
    SI_Long j, ab_loop_bind_;
    double arg, arg_1;

    x_note_fn_call(187,120);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    arg = DFLOAT_ISAREF_1(ISVREF(managed_array_1,(j >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),j & (SI_Long)1023L);
    arg_1 = DFLOAT_ISAREF_1(ISVREF(managed_array_2,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1)))
	return VALUES_1(Nil);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* G2-FLOAT-VECTOR-COPY */
Object g2_float_vector_copy(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, aref_arg_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    double aref_new_value;

    x_note_fn_call(187,121);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    aref_arg_1 = ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L);
    aref_arg_2 = j & (SI_Long)1023L;
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(managed_array_1,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-VECTOR-EQUAL */
Object g2_quantity_vector_equal(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, value_to_return, j;
    Object n_minus_1, temp, end_value_of_j;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,122);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    value_to_return = T;
    j = FIX((SI_Long)0L);
  next_loop:
    n_minus_1 = FIXNUM_SUB1(n_1);
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	temp = get_quantity_element(managed_array_1,j);
	arg = DOUBLE_FLOAT_TO_DOUBLE(temp);
	temp = get_quantity_element(managed_array_2,j);
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    value_to_return = Nil;
	    j = Nil;
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(value_to_return);
    return VALUES_1(Qnil);
}

static Object Qg2_array_copy;      /* g2-array-copy */

/* G2-QUANTITY-VECTOR-COPY */
Object g2_quantity_vector_copy(vector1,vector2)
    Object vector1, vector2;
{
    Object sub_class_bit_vector, target_is_integer_array_p, n_1;
    Object managed_array_1, managed_array_2, j, n_minus_1, temp;
    Object end_value_of_j, source_value, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,123);
    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	target_is_integer_array_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	target_is_integer_array_p = Nil;
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = FIX((SI_Long)0L);
  next_loop:
    n_minus_1 = FIXNUM_SUB1(n_1);
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	temp = j;
	source_value = get_quantity_element(managed_array_1,j);
	if (target_is_integer_array_p && FLOATP(source_value)) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(source_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_3 = truncate_evaluation_float_function(new_float,
		    Qg2_array_copy,Cached_top_of_stack);
	}
	else
	    temp_3 = source_value;
	set_quantity_element(managed_array_2,temp,temp_3);
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* CHECK-MATRICES-COMPATIBLE-FOR-TRANSPOSE */
Object check_matrices_compatible_for_transpose(matrix1,matrix2)
    Object matrix1, matrix2;
{
    Object managed_array_for_matrix_1, managed_array_for_matrix_2, m;
    Object first_row_of_matrix_1, type, n_1, row, temp;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(187,124);
    managed_array_for_matrix_1 = ISVREF(matrix1,(SI_Long)23L);
    managed_array_for_matrix_2 = ISVREF(matrix2,(SI_Long)23L);
    m = ISVREF(matrix1,(SI_Long)20L);
    first_row_of_matrix_1 = FIXNUM_LE(ISVREF(managed_array_for_matrix_1,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(managed_array_for_matrix_1,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array_for_matrix_1,(SI_Long)2L),(SI_Long)0L);
    type = check_matrix_row_type(matrix1,first_row_of_matrix_1);
    n_1 = ISVREF(first_row_of_matrix_1,(SI_Long)20L);
    i = (SI_Long)2L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(m);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      Row = FIXNUM_LE(ISVREF(managed_array_for_matrix_1,(SI_Long)1L),
	      Maximum_in_place_array_size) ? 
	      ISVREF(managed_array_for_matrix_1,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array_for_matrix_1,(i >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
      check_row_length_and_type_compatible(matrix1,Row,n_1,type);
      i = i + (SI_Long)2L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    check_array_length_compatible(matrix2,n_1);
    i = (SI_Long)0L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(n_1);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop_1:
      if (i >= ab_loop_bind_)
	  goto end_loop_1;
      Row = FIXNUM_LE(ISVREF(managed_array_for_matrix_2,(SI_Long)1L),
	      Maximum_in_place_array_size) ? 
	      ISVREF(managed_array_for_matrix_2,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array_for_matrix_2,(i >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
      check_row_length_and_type_compatible(matrix2,Row,m,type);
      i = i + (SI_Long)2L;
      goto next_loop_1;
    end_loop_1:;
    POP_SPECIAL();
    temp = FIXNUM_MIN(m,n_1);
    return VALUES_4(m,n_1,temp,type);
}

/* CHECK-MATRICES-COMPATIBLE-FOR-MULTIPLY */
Object check_matrices_compatible_for_multiply(matrix1,matrix2,matrix3)
    Object matrix1, matrix2, matrix3;
{
    Object managed_array_for_matrix_1, managed_array_for_matrix_2;
    Object managed_array_for_matrix_3, m1, m2, first_row_of_matrix_3, type, n2;
    Object row;
    SI_Long i, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(187,125);
    managed_array_for_matrix_1 = ISVREF(matrix1,(SI_Long)23L);
    managed_array_for_matrix_2 = ISVREF(matrix2,(SI_Long)23L);
    managed_array_for_matrix_3 = ISVREF(matrix3,(SI_Long)23L);
    m1 = ISVREF(matrix1,(SI_Long)20L);
    m2 = ISVREF(matrix2,(SI_Long)20L);
    first_row_of_matrix_3 = FIXNUM_LE(ISVREF(managed_array_for_matrix_3,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(managed_array_for_matrix_3,(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array_for_matrix_3,(SI_Long)2L),(SI_Long)0L);
    type = check_matrix_row_type(matrix3,first_row_of_matrix_3);
    n2 = ISVREF(first_row_of_matrix_3,(SI_Long)20L);
    i = (SI_Long)2L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(m1);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      Row = FIXNUM_LE(ISVREF(managed_array_for_matrix_1,(SI_Long)1L),
	      Maximum_in_place_array_size) ? 
	      ISVREF(managed_array_for_matrix_1,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array_for_matrix_1,(i >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
      check_row_length_and_type_compatible(matrix1,Row,m2,type);
      i = i + (SI_Long)2L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    i = (SI_Long)0L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(m2);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop_1:
      if (i >= ab_loop_bind_)
	  goto end_loop_1;
      Row = FIXNUM_LE(ISVREF(managed_array_for_matrix_2,(SI_Long)1L),
	      Maximum_in_place_array_size) ? 
	      ISVREF(managed_array_for_matrix_2,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array_for_matrix_2,(i >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
      check_row_length_and_type_compatible(matrix2,Row,n2,type);
      i = i + (SI_Long)2L;
      goto next_loop_1;
    end_loop_1:;
    POP_SPECIAL();
    check_array_length_compatible(matrix3,m1);
    i = (SI_Long)2L;
    ab_loop_bind_ = (SI_Long)2L * IFIX(m1);
    row = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop_2:
      if (i >= ab_loop_bind_)
	  goto end_loop_2;
      Row = FIXNUM_LE(ISVREF(managed_array_for_matrix_3,(SI_Long)1L),
	      Maximum_in_place_array_size) ? 
	      ISVREF(managed_array_for_matrix_3,i + 
	      IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array_for_matrix_3,(i >>  -  - 
	      (SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L);
      check_row_length_and_type_compatible(matrix3,Row,n2,type);
      i = i + (SI_Long)2L;
      goto next_loop_2;
    end_loop_2:;
    POP_SPECIAL();
    return VALUES_4(m1,m2,n2,type);
}

/* TRANSPOSE-ROW */
Object transpose_row(i,begin_j,end_j,type,swap_qm,
	    managed_array_for_matrix_1,managed_array_for_matrix_2)
    Object i, begin_j, end_j, type, swap_qm, managed_array_for_matrix_1;
    Object managed_array_for_matrix_2;
{
    Object managed_array_for_matrix_1_row, managed_array_for_matrix_2_row;
    Object managed_array_for_matrix_1_row_for_column;
    Object managed_array_for_matrix_2_row_for_column, temp, svref_new_value;
    Object temp_1, amf_available_array_cons_qm, amf_array, amf_result;
    Object new_float, temp_3, j_1, n_minus_1, temp_4, end_value_of_j;
    SI_Long j, ab_loop_bind_, temp_2;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,126);
    managed_array_for_matrix_1_row = 
	    ISVREF(get_matrix_row(managed_array_for_matrix_1,i),(SI_Long)23L);
    managed_array_for_matrix_2_row = Nil;
    if (swap_qm) {
	managed_array_for_matrix_2_row = 
		ISVREF(get_matrix_row(managed_array_for_matrix_2,i),
		(SI_Long)23L);
	if (EQ(type,Qinteger)) {
	    j = IFIX(begin_j);
	    ab_loop_bind_ = IFIX(end_j);
	    managed_array_for_matrix_1_row_for_column = Nil;
	    managed_array_for_matrix_2_row_for_column = Nil;
	  next_loop:
	    if (j >= ab_loop_bind_)
		goto end_loop;
	    managed_array_for_matrix_1_row_for_column = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_1,
		    FIX(j)),(SI_Long)23L);
	    managed_array_for_matrix_2_row_for_column = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_2,
		    FIX(j)),(SI_Long)23L);
	    temp = FIXNUM_LE(ISVREF(managed_array_for_matrix_1_row,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(managed_array_for_matrix_1_row,j + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_array_for_matrix_1_row,(j >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	    svref_new_value = 
		    FIXNUM_LE(ISVREF(managed_array_for_matrix_1_row_for_column,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(managed_array_for_matrix_1_row_for_column,
		    IFIX(FIXNUM_ADD(i,Managed_array_index_offset))) : 
		    ISVREF(ISVREF(managed_array_for_matrix_1_row_for_column,
		    (IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(i) 
		    & (SI_Long)1023L);
	    if (FIXNUM_LE(ISVREF(managed_array_for_matrix_2_row_for_column,
		    (SI_Long)1L),Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(i,Managed_array_index_offset);
		SVREF(managed_array_for_matrix_2_row_for_column,temp_1) = temp;
	    }
	    else {
		temp_1 = ISVREF(managed_array_for_matrix_2_row_for_column,
			(IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
		temp_2 = IFIX(i) & (SI_Long)1023L;
		ISVREF(temp_1,temp_2) = temp;
	    }
	    if (FIXNUM_LE(ISVREF(managed_array_for_matrix_2_row,
		    (SI_Long)1L),Maximum_in_place_array_size)) {
		temp_2 = j + IFIX(Managed_array_index_offset);
		ISVREF(managed_array_for_matrix_2_row,temp_2) = 
			svref_new_value;
	    }
	    else {
		temp_1 = ISVREF(managed_array_for_matrix_2_row,(j >>  -  - 
			(SI_Long)10L) + (SI_Long)2L);
		temp_2 = j & (SI_Long)1023L;
		ISVREF(temp_1,temp_2) = svref_new_value;
	    }
	    j = j + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (EQ(type,Qfloat)) {
	    j = IFIX(begin_j);
	    ab_loop_bind_ = IFIX(end_j);
	    managed_array_for_matrix_1_row_for_column = Nil;
	    managed_array_for_matrix_2_row_for_column = Nil;
	  next_loop_1:
	    if (j >= ab_loop_bind_)
		goto end_loop_1;
	    managed_array_for_matrix_1_row_for_column = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_1,
		    FIX(j)),(SI_Long)23L);
	    managed_array_for_matrix_2_row_for_column = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_2,
		    FIX(j)),(SI_Long)23L);
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp = Current_thread_index;
		    SVREF(temp_1,temp) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp = Current_thread_index;
		    SVREF(temp_1,temp) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp = Current_thread_index;
		    SVREF(temp_1,temp) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    aref_new_value = 
		    DFLOAT_ISAREF_1(ISVREF(managed_array_for_matrix_1_row_for_column,
		    (IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(i) 
		    & (SI_Long)1023L);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    temp_3 = new_float;
	    temp_1 = ISVREF(managed_array_for_matrix_2_row_for_column,
		    (IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(i) & (SI_Long)1023L;
	    aref_new_value = 
		    DFLOAT_ISAREF_1(ISVREF(managed_array_for_matrix_1_row,
		    (j >>  -  - (SI_Long)10L) + (SI_Long)2L),j & 
		    (SI_Long)1023L);
	    DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	    temp_1 = ISVREF(managed_array_for_matrix_2_row,(j >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = j & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(temp_3,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	    reclaim_managed_simple_float_array_of_length_1(temp_3);
	    j = j + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
	else if (EQ(type,Qquantity)) {
	    j_1 = begin_j;
	  next_loop_2:
	    n_minus_1 = FIXNUM_SUB1(end_j);
	    temp_4 = FIXNUM_ADD(j_1,Max_number_of_array_elements_to_do);
	    end_value_of_j = FIXNUM_MIN(n_minus_1,temp_4);
	    if (FIXNUM_GT(j_1,n_minus_1))
		return VALUES_1(Nil);
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	      next_loop_3:
		managed_array_for_matrix_1_row_for_column = 
			ISVREF(get_matrix_row(managed_array_for_matrix_1,
			j_1),(SI_Long)23L);
		managed_array_for_matrix_2_row_for_column = 
			ISVREF(get_matrix_row(managed_array_for_matrix_2,
			j_1),(SI_Long)23L);
		temp_3 = 
			get_quantity_element(managed_array_for_matrix_1_row_for_column,
			i);
		set_quantity_element(managed_array_for_matrix_2_row_for_column,
			i,
			get_quantity_element(managed_array_for_matrix_1_row,
			j_1));
		set_quantity_element(managed_array_for_matrix_2_row,j_1,
			temp_3);
		if (FIXNUM_GE(j_1,n_minus_1)) {
		    j_1 = Nil;
		    goto end_1;
		}
		if (FIXNUM_EQ(j_1,end_value_of_j)) {
		    j_1 = end_value_of_j;
		    goto end_1;
		}
		j_1 = FIXNUM_ADD1(j_1);
		goto next_loop_3;
	      end_loop_2:
		j_1 = Qnil;
	      end_1:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    if ( !TRUEP(j_1))
		goto end_loop_3;
	    goto next_loop_2;
	  end_loop_3:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(type,Qinteger)) {
	j = IFIX(begin_j);
	ab_loop_bind_ = IFIX(end_j);
	managed_array_for_matrix_2_row_for_column = Nil;
      next_loop_4:
	if (j >= ab_loop_bind_)
	    goto end_loop_4;
	managed_array_for_matrix_2_row_for_column = 
		ISVREF(get_matrix_row(managed_array_for_matrix_2,FIX(j)),
		(SI_Long)23L);
	if (FIXNUM_LE(ISVREF(managed_array_for_matrix_2_row_for_column,
		(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = FIXNUM_ADD(i,Managed_array_index_offset);
	    temp = FIXNUM_LE(ISVREF(managed_array_for_matrix_1_row,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(managed_array_for_matrix_1_row,j + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_array_for_matrix_1_row,(j >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	    SVREF(managed_array_for_matrix_2_row_for_column,temp_1) = temp;
	}
	else {
	    temp_1 = ISVREF(managed_array_for_matrix_2_row_for_column,
		    (IFIX(i) >>  -  - (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(i) & (SI_Long)1023L;
	    temp = FIXNUM_LE(ISVREF(managed_array_for_matrix_1_row,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(managed_array_for_matrix_1_row,j + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(managed_array_for_matrix_1_row,(j >>  -  
		    - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	    ISVREF(temp_1,temp_2) = temp;
	}
	j = j + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:
	return VALUES_1(Qnil);
    }
    else if (EQ(type,Qfloat)) {
	j = IFIX(begin_j);
	ab_loop_bind_ = IFIX(end_j);
	managed_array_for_matrix_2_row_for_column = Nil;
      next_loop_5:
	if (j >= ab_loop_bind_)
	    goto end_loop_5;
	managed_array_for_matrix_2_row_for_column = 
		ISVREF(get_matrix_row(managed_array_for_matrix_2,FIX(j)),
		(SI_Long)23L);
	temp_1 = ISVREF(managed_array_for_matrix_2_row_for_column,(IFIX(i) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(i) & (SI_Long)1023L;
	aref_new_value = 
		DFLOAT_ISAREF_1(ISVREF(managed_array_for_matrix_1_row,(j 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_5;
      end_loop_5:
	return VALUES_1(Qnil);
    }
    else if (EQ(type,Qquantity)) {
	j_1 = begin_j;
      next_loop_6:
	n_minus_1 = FIXNUM_SUB1(end_j);
	temp_4 = FIXNUM_ADD(j_1,Max_number_of_array_elements_to_do);
	end_value_of_j = FIXNUM_MIN(n_minus_1,temp_4);
	if (FIXNUM_GT(j_1,n_minus_1))
	    return VALUES_1(Nil);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_7:
	    managed_array_for_matrix_2_row_for_column = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_2,j_1),
		    (SI_Long)23L);
	    set_quantity_element(managed_array_for_matrix_2_row_for_column,
		    i,get_quantity_element(managed_array_for_matrix_1_row,
		    j_1));
	    if (FIXNUM_GE(j_1,n_minus_1)) {
		j_1 = Nil;
		goto end_2;
	    }
	    if (FIXNUM_EQ(j_1,end_value_of_j)) {
		j_1 = end_value_of_j;
		goto end_2;
	    }
	    j_1 = FIXNUM_ADD1(j_1);
	    goto next_loop_7;
	  end_loop_6:
	    j_1 = Qnil;
	  end_2:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if ( !TRUEP(j_1))
	    goto end_loop_7;
	goto next_loop_6;
      end_loop_7:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_28;  /* "a row multiply" */

/* G2-VECTOR-MULTIPLY */
Object g2_vector_multiply(vector1,vector2)
    Object vector1, vector2;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(187,127);
    SAVE_STACK();
    barrier();
    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if (temp)
	SAVE_VALUES(g2_integer_vector_multiply(vector1,vector2));
    else {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp)
	    SAVE_VALUES(g2_float_vector_multiply(vector1,vector2));
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantity_array_class_description,
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		SAVE_VALUES(g2_quantity_vector_multiply(vector1,vector2));
	    else
		SAVE_VALUES(signal_invalid_vectors(gensym_list_2(vector1,
			vector2),string_constant_28));
	}
    }
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-SCALAR-MULTIPLY-1 */
Object g2_scalar_multiply_1(vector1,vector2,x)
    Object vector1, vector2, x;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(187,128);
    SAVE_STACK();
    barrier();
    sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    else
	temp = TRUEP(Nil);
    if (temp ? FIXNUMP(x) : TRUEP(Nil))
	SAVE_VALUES(g2_integer_scalar_multiply(vector1,vector2,x));
    else {
	sub_class_bit_vector = ISVREF(ISVREF(vector1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(vector2,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp ? FLOATP(x) : TRUEP(Nil))
	    SAVE_VALUES(g2_float_scalar_multiply(vector1,vector2,x));
	else
	    SAVE_VALUES(g2_quantity_scalar_multiply(vector1,vector2,x));
    }
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-INTEGER-VECTOR-MULTIPLY */
Object g2_integer_vector_multiply(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, sum;
    SI_Long j, ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;

    x_note_fn_call(187,129);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    sum = FIX((SI_Long)0L);
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    gensymed_symbol = IFIX(sum);
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(managed_array_1,j + 
	    IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(managed_array_1,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L));
    gensymed_symbol_2 = FIXNUM_LE(ISVREF(managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(managed_array_2,j + 
	    IFIX(Managed_array_index_offset))) : 
	    IFIX(ISVREF(ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L));
    gensymed_symbol_1 = gensymed_symbol_1 * gensymed_symbol_2;
    sum = FIX(gensymed_symbol + gensymed_symbol_1);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(sum);
    return VALUES_1(Qnil);
}

/* G2-INTEGER-SCALAR-MULTIPLY */
Object g2_integer_scalar_multiply(vector1,vector2,x)
    Object vector1, vector2, x;
{
    Object n_1, managed_array_1, managed_array_2, svref_arg_1;
    SI_Long j, ab_loop_bind_, svref_arg_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long svref_new_value;

    x_note_fn_call(187,130);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    if (FIXNUM_LE(ISVREF(managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = j + IFIX(Managed_array_index_offset);
	gensymed_symbol = IFIX(x);
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? IFIX(ISVREF(managed_array_1,
		j + IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(managed_array_1,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
	svref_new_value = gensymed_symbol * gensymed_symbol_1;
	ISVREF(managed_array_2,svref_arg_2) = FIX(svref_new_value);
    }
    else {
	svref_arg_1 = ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = j & (SI_Long)1023L;
	gensymed_symbol = IFIX(x);
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(managed_array_1,(SI_Long)1L),
		Maximum_in_place_array_size) ? IFIX(ISVREF(managed_array_1,
		j + IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(managed_array_1,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
	svref_new_value = gensymed_symbol * gensymed_symbol_1;
	ISVREF(svref_arg_1,svref_arg_2) = FIX(svref_new_value);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-FLOAT-VECTOR-MULTIPLY */
Object g2_float_vector_multiply(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, managed_sum;
    SI_Long j, ab_loop_bind_;
    double aref_new_value, sum;

    x_note_fn_call(187,131);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    managed_sum = new_float;
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    aref_new_value = DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(ISVREF(managed_array_1,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L) * 
	    DFLOAT_ISAREF_1(ISVREF(managed_array_2,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(managed_sum,(SI_Long)0L,aref_new_value);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    sum = DFLOAT_ISAREF_1(managed_sum,(SI_Long)0L);
    reclaim_managed_simple_float_array_of_length_1(managed_sum);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(sum));
    return VALUES_1(Qnil);
}

/* G2-FLOAT-SCALAR-MULTIPLY */
Object g2_float_scalar_multiply(vector1,vector2,x)
    Object vector1, vector2, x;
{
    Object n_1, managed_array_1, managed_array_2, aref_arg_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    double temp, aref_new_value;

    x_note_fn_call(187,132);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    aref_arg_1 = ISVREF(managed_array_2,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L);
    aref_arg_2 = j & (SI_Long)1023L;
    temp = DOUBLE_FLOAT_TO_DOUBLE(x);
    aref_new_value = temp * DFLOAT_ISAREF_1(ISVREF(managed_array_1,(j >>  
	    -  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-VECTOR-MULTIPLY */
Object g2_quantity_vector_multiply(vector1,vector2)
    Object vector1, vector2;
{
    Object n_1, managed_array_1, managed_array_2, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, sum_box, j;
    Object n_minus_1, temp_2, end_value_of_j;
    double temp_3, temp_4, temp_5, aref_new_value, sum;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,133);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    sum_box = new_float;
    j = FIX((SI_Long)0L);
  next_loop:
    n_minus_1 = FIXNUM_SUB1(n_1);
    temp_2 = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp_2);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	temp_3 = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
	temp_2 = get_quantity_element(managed_array_1,j);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	temp_2 = get_quantity_element(managed_array_2,j);
	temp_5 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	aref_new_value = temp_3 + temp_4 * temp_5;
	DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    sum = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
    reclaim_managed_simple_float_array_of_length_1(sum_box);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(sum));
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-SCALAR-MULTIPLY */
Object g2_quantity_scalar_multiply(vector1,vector2,x)
    Object vector1, vector2, x;
{
    Object n_1, managed_array_1, managed_array_2, j, n_minus_1, temp;
    Object end_value_of_j;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,134);
    n_1 = check_array_lengths_compatible(2,vector1,vector2);
    managed_array_1 = ACCESS_ONCE(ISVREF(vector1,(SI_Long)23L));
    managed_array_2 = ACCESS_ONCE(ISVREF(vector2,(SI_Long)23L));
    j = FIX((SI_Long)0L);
  next_loop:
    n_minus_1 = FIXNUM_SUB1(n_1);
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	temp = j;
	set_quantity_element(managed_array_2,temp,ltimes(x,
		get_quantity_element(managed_array_1,j)));
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

static Object float_constant_1;    /* 0.5 */

/* G2-MATRIX-TO-INTEGER-VECTOR-MULTIPLY */
Object g2_matrix_to_integer_vector_multiply(matrix_vector,vector1,vector2,
	    index_1)
    Object matrix_vector, vector1, vector2, index_1;
{
    Object svref_arg_1, svref_arg_2, number, temp;
    SI_Long temp_1, svref_new_value;

    x_note_fn_call(187,135);
    if (FIXNUM_LE(ISVREF(ISVREF(vector2,(SI_Long)23L),(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_1 = ISVREF(vector2,(SI_Long)23L);
	svref_arg_2 = FIXNUM_ADD(index_1,Managed_array_index_offset);
	number = g2_vector_multiply(matrix_vector,vector1);
	temp = FIX((SI_Long)0L);
	temp_1 = IFIX(ltruncate(NUM_GT(number,temp) ? add(number,
		float_constant_1) : minus(number,float_constant_1),_));
	return VALUES_1(ISVREF(svref_arg_1,IFIX(svref_arg_2)) = FIX(temp_1));
    }
    else {
	svref_arg_1 = ISVREF(ISVREF(vector2,(SI_Long)23L),(IFIX(index_1) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L);
	temp_1 = IFIX(index_1) & (SI_Long)1023L;
	number = g2_vector_multiply(matrix_vector,vector1);
	temp = FIX((SI_Long)0L);
	svref_new_value = IFIX(ltruncate(NUM_GT(number,temp) ? add(number,
		float_constant_1) : minus(number,float_constant_1),_));
	return VALUES_1(ISVREF(svref_arg_1,temp_1) = FIX(svref_new_value));
    }
}

/* G2-MATRIX-TO-FLOAT-VECTOR-MULTIPLY */
Object g2_matrix_to_float_vector_multiply(matrix_vector,vector1,vector2,
	    index_1)
    Object matrix_vector, vector1, vector2, index_1;
{
    Object aref_arg_1, temp;
    SI_Long aref_arg_2;
    double aref_new_value;

    x_note_fn_call(187,136);
    aref_arg_1 = ISVREF(ISVREF(vector2,(SI_Long)23L),(IFIX(index_1) >>  -  
	    - (SI_Long)10L) + (SI_Long)2L);
    aref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
    temp = lfloat(g2_vector_multiply(matrix_vector,vector1),float_constant);
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    return VALUES_1(Nil);
}

/* G2-MATRIX-TO-QUANTITY-VECTOR-MULTIPLY */
Object g2_matrix_to_quantity_vector_multiply(matrix_vector,vector1,vector2,
	    index_1)
    Object matrix_vector, vector1, vector2, index_1;
{
    Object temp;

    x_note_fn_call(187,137);
    temp = ISVREF(vector2,(SI_Long)23L);
    return set_quantity_element(temp,index_1,
	    g2_vector_multiply(matrix_vector,vector1));
}

/* MULTIPLY-ROW */
Object multiply_row(j,n_1,type,managed_array_for_matrix_1_row,
	    managed_array_for_matrix_2,managed_array_for_matrix_3_row)
    Object j, n_1, type, managed_array_for_matrix_1_row;
    Object managed_array_for_matrix_2, managed_array_for_matrix_3_row;
{
    Object sum, managed_array_for_matrix_2_row, temp;
    Object amf_available_array_cons_qm, amf_array, temp_2, amf_result;
    Object new_float, sum_box, k_1, n_minus_1, temp_3, end_value_of_j;
    SI_Long k, ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, temp_1;
    double aref_new_value, temp_4, temp_5, temp_6;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,138);
    if (EQ(type,Qinteger)) {
	sum = FIX((SI_Long)0L);
	k = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
	managed_array_for_matrix_2_row = Nil;
      next_loop:
	if (k >= ab_loop_bind_)
	    goto end_loop;
	managed_array_for_matrix_2_row = 
		ISVREF(get_matrix_row(managed_array_for_matrix_2,FIX(k)),
		(SI_Long)23L);
	gensymed_symbol = IFIX(sum);
	gensymed_symbol_1 = 
		FIXNUM_LE(ISVREF(managed_array_for_matrix_1_row,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		IFIX(ISVREF(managed_array_for_matrix_1_row,k + 
		IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(managed_array_for_matrix_1_row,(k >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L));
	gensymed_symbol_2 = 
		FIXNUM_LE(ISVREF(managed_array_for_matrix_2_row,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		IFIX(ISVREF(managed_array_for_matrix_2_row,
		IFIX(FIXNUM_ADD(j,Managed_array_index_offset)))) : 
		IFIX(ISVREF(ISVREF(managed_array_for_matrix_2_row,(IFIX(j) 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
		(SI_Long)1023L));
	gensymed_symbol_1 = gensymed_symbol_1 * gensymed_symbol_2;
	sum = FIX(gensymed_symbol + gensymed_symbol_1);
	k = k + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (FIXNUM_LE(ISVREF(managed_array_for_matrix_3_row,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(j,Managed_array_index_offset);
	    SVREF(managed_array_for_matrix_3_row,temp) = sum;
	}
	else {
	    temp = ISVREF(managed_array_for_matrix_3_row,(IFIX(j) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_1 = IFIX(j) & (SI_Long)1023L;
	    ISVREF(temp,temp_1) = sum;
	}
	return VALUES_1(Qnil);
    }
    else if (EQ(type,Qfloat)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	sum = new_float;
	k = (SI_Long)0L;
	ab_loop_bind_ = IFIX(n_1);
	managed_array_for_matrix_2_row = Nil;
      next_loop_1:
	if (k >= ab_loop_bind_)
	    goto end_loop_1;
	managed_array_for_matrix_2_row = 
		ISVREF(get_matrix_row(managed_array_for_matrix_2,FIX(k)),
		(SI_Long)23L);
	aref_new_value = DFLOAT_ISAREF_1(sum,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(ISVREF(managed_array_for_matrix_1_row,(k 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),k & (SI_Long)1023L) 
		* DFLOAT_ISAREF_1(ISVREF(managed_array_for_matrix_2_row,
		(IFIX(j) >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
		(SI_Long)1023L);
	DFLOAT_ISASET_1(sum,(SI_Long)0L,aref_new_value);
	k = k + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	temp = ISVREF(managed_array_for_matrix_3_row,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_1 = IFIX(j) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(sum,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,temp_1,aref_new_value);
	reclaim_managed_simple_float_array_of_length_1(sum);
	return VALUES_1(Qnil);
    }
    else if (EQ(type,Qquantity)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp,temp_2) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	sum_box = new_float;
	k_1 = FIX((SI_Long)0L);
      next_loop_2:
	n_minus_1 = FIXNUM_SUB1(n_1);
	temp_3 = FIXNUM_ADD(k_1,Max_number_of_array_elements_to_do);
	end_value_of_j = FIXNUM_MIN(n_minus_1,temp_3);
	if (FIXNUM_GT(k_1,n_minus_1))
	    return VALUES_1(Nil);
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_3:
	    managed_array_for_matrix_2_row = 
		    ISVREF(get_matrix_row(managed_array_for_matrix_2,k_1),
		    (SI_Long)23L);
	    temp_4 = DFLOAT_ISAREF_1(sum_box,(SI_Long)0L);
	    temp_3 = get_quantity_element(managed_array_for_matrix_1_row,k_1);
	    temp_5 = DOUBLE_FLOAT_TO_DOUBLE(temp_3);
	    temp_3 = get_quantity_element(managed_array_for_matrix_2_row,j);
	    temp_6 = DOUBLE_FLOAT_TO_DOUBLE(temp_3);
	    aref_new_value = temp_4 + temp_5 * temp_6;
	    DFLOAT_ISASET_1(sum_box,(SI_Long)0L,aref_new_value);
	    if (FIXNUM_GE(k_1,n_minus_1)) {
		k_1 = Nil;
		goto end_1;
	    }
	    if (FIXNUM_EQ(k_1,end_value_of_j)) {
		k_1 = end_value_of_j;
		goto end_1;
	    }
	    k_1 = FIXNUM_ADD1(k_1);
	    goto next_loop_3;
	  end_loop_2:
	    k_1 = Qnil;
	  end_1:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if ( !TRUEP(k_1))
	    goto end_loop_3;
	goto next_loop_2;
      end_loop_3:
	set_quantity_element(managed_array_for_matrix_3_row,j,
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(sum_box,(SI_Long)0L)));
	reclaim_managed_simple_float_array_of_length_1(sum_box);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_29;  /* "The begin index and end index must both be integers" */

static Object string_constant_30;  /* "The value and index arrays must both be arrays" */

static Object string_constant_31;  /* "The end-index ~a must be greater than the begin-index ~a" */

/* G2-SPARSE-SCATTER */
Object g2_sparse_scatter(value_array,index_array,full_array,begin_index,
	    end_index)
    Object value_array, index_array, full_array, begin_index, end_index;
{
    Object top_of_stack, message_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,139);
    if ( !FIXNUMP(begin_index) ||  !FIXNUMP(end_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_29);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	    sub_class_bit_vector = ISVREF(ISVREF(index_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	}
	if (temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(1,string_constant_30);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    if (NUM_GE(begin_index,end_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_31,
		end_index,begin_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    check_for_incompatible_from_to_arrays(value_array,full_array);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp)
	    result = g2_integer_sparse_scatter(value_array,index_array,
		    full_array,begin_index,end_index);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(full_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = g2_float_sparse_scatter(value_array,index_array,
			full_array,begin_index,end_index);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(full_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(value_array,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    result = g2_quantity_to_integer_sparse_scatter(value_array,
			    index_array,full_array,begin_index,end_index);
		else
		    result = g2_quantity_sparse_scatter(value_array,
			    index_array,full_array,begin_index,end_index);
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_32;  /* "Values cannot be automatically converted from ~NF to ~NF" */

/* CHECK-FOR-INCOMPATIBLE-FROM-TO-ARRAYS */
Object check_for_incompatible_from_to_arrays(from_array,to_array)
    Object from_array, to_array;
{
    Object sub_class_bit_vector, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(187,140);
    sub_class_bit_vector = ISVREF(ISVREF(to_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(from_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(3,
		    string_constant_32,from_array,to_array);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_33;  /* "The value,index and full arrays must all be arrays" */

/* G2-SPARSE-GATHER */
Object g2_sparse_gather(value_array,index_array,full_array)
    Object value_array, index_array, full_array;
{
    Object sub_class_bit_vector, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,141);
    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_33);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    check_for_incompatible_from_to_arrays(full_array,value_array);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp)
	    result = g2_integer_sparse_gather(value_array,index_array,
		    full_array);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(full_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = g2_float_sparse_gather(value_array,index_array,
			full_array);
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(value_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
		if (temp) {
		    sub_class_bit_vector = ISVREF(ISVREF(full_array,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Quantity_array_class_description,
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
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    result = g2_quantity_to_integer_sparse_gather(value_array,
			    index_array,full_array);
		else
		    result = g2_quantity_sparse_gather(value_array,
			    index_array,full_array);
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* EVALUATION-TRUTH-VALUE-TRUE-P */
Object evaluation_truth_value_true_p(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(187,142);
    return VALUES_1(IFIX(M_CAR(evaluation_truth_value)) > (SI_Long)0L ? T :
	     Nil);
}

static Object string_constant_34;  /* "value-array-1, index-array-1, value-array-2, index-array-2 and full array must all be arrays" */

/* G2-SPARSE-ADD */
Object g2_sparse_add(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,alpha,range,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, alpha, range, full_array_initialized_qm;
{
    Object sub_class_bit_vector, top_of_stack, message_1, range_managed_array;
    Object begin_index_1, end_index_1, begin_index_2, end_index_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,143);
    SAVE_STACK();
    sub_class_bit_vector = ISVREF(ISVREF(value_array_1,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array_2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array_2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_34);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    range_managed_array = check_range_array(range);
    begin_index_1 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)0L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)0L);
    end_index_1 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)1L);
    begin_index_2 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)2L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)2L);
    end_index_2 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)3L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)3L);
    full_array_initialized_qm = 
	    evaluation_truth_value_true_p(full_array_initialized_qm);
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	alpha = evaluation_value_value(alpha);
	sub_class_bit_vector = ISVREF(ISVREF(value_array_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array_2,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp ? FIXNUMP(alpha) : TRUEP(Nil))
	    result = g2_integer_sparse_add(value_array_1,index_array_1,
		    value_array_2,index_array_2,full_array,alpha,
		    begin_index_1,end_index_1,begin_index_2,end_index_2,
		    full_array_initialized_qm);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array_1,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(value_array_2,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(full_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? FLOATP(alpha) : TRUEP(Nil))
		result = g2_float_sparse_add(value_array_1,index_array_1,
			value_array_2,index_array_2,full_array,alpha,
			begin_index_1,end_index_1,begin_index_2,
			end_index_2,full_array_initialized_qm);
	    else {
		if (FIXNUMP(alpha))
		    alpha = DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(alpha));
		result = g2_quantity_sparse_add(value_array_1,
			index_array_1,value_array_2,index_array_2,
			full_array,alpha,begin_index_1,end_index_1,
			begin_index_2,end_index_2,full_array_initialized_qm);
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* G2-SPARSE-MULTIPLY */
Object g2_sparse_multiply(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,range,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, range, full_array_initialized_qm;
{
    Object sub_class_bit_vector, top_of_stack, message_1, range_managed_array;
    Object begin_index_1, end_index_1, begin_index_2, end_index_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_stack_pointer;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,144);
    SAVE_STACK();
    sub_class_bit_vector = ISVREF(ISVREF(value_array_1,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array_2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array_2,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_34);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    range_managed_array = check_range_array(range);
    begin_index_1 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)0L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)0L);
    end_index_1 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    IFIX(FIXNUM_ADD1(Managed_array_index_offset))) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)1L);
    begin_index_2 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)2L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)2L);
    end_index_2 = FIXNUM_LE(ISVREF(range_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(range_managed_array,
	    (SI_Long)3L + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(range_managed_array,(SI_Long)2L),(SI_Long)3L);
    full_array_initialized_qm = 
	    evaluation_truth_value_true_p(full_array_initialized_qm);
    barrier();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array_2,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	else
	    temp = TRUEP(Nil);
	if (temp)
	    result = g2_integer_sparse_multiply(value_array_1,
		    index_array_1,value_array_2,index_array_2,full_array,
		    begin_index_1,end_index_1,begin_index_2,end_index_2,
		    full_array_initialized_qm);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array_1,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(value_array_2,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(full_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Float_array_class_description,
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
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		result = g2_float_sparse_multiply(value_array_1,
			index_array_1,value_array_2,index_array_2,
			full_array,begin_index_1,end_index_1,begin_index_2,
			end_index_2,full_array_initialized_qm);
	    else
		result = g2_quantity_sparse_multiply(value_array_1,
			index_array_1,value_array_2,index_array_2,
			full_array,begin_index_1,end_index_1,begin_index_2,
			end_index_2,full_array_initialized_qm);
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    SAVE_VALUES(result);
    barrier();
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

Object Default_min_to_extend_sparse_vector = UNBOUND;

/* EXTEND-SPARSE-VECTOR-AS-NECESSARY */
Object extend_sparse_vector_as_necessary(value_array,index_array,
	    sparse_index,value_array_length)
    Object value_array, index_array, sparse_index, value_array_length;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(187,145);
    temp = FIXNUM_MINUS(sparse_index,FIXNUM_SUB1(value_array_length));
    change_sparse_vector_length(value_array,index_array,
	    FIXNUM_ADD(value_array_length,
	    FIXNUM_MAX(Default_min_to_extend_sparse_vector,temp)));
    temp_1 = ISVREF(value_array,(SI_Long)20L);
    temp_2 = ISVREF(value_array,(SI_Long)23L);
    temp = ISVREF(index_array,(SI_Long)23L);
    return VALUES_3(temp_1,temp_2,temp);
}

/* MAKE-SPARSE-VECTOR-EXACT-SIZE */
Object make_sparse_vector_exact_size(value_array,index_array,sparse_index,
	    value_array_length)
    Object value_array, index_array, sparse_index, value_array_length;
{
    x_note_fn_call(187,146);
    if (FIXNUM_NE(sparse_index,value_array_length))
	return change_sparse_vector_length(value_array,index_array,
		sparse_index);
    else
	return VALUES_1(Nil);
}

static Object Qg2_array_length;    /* g2-array-length */

/* CHANGE-SPARSE-VECTOR-LENGTH */
Object change_sparse_vector_length(value_array,index_array,desired_length)
    Object value_array, index_array, desired_length;
{
    Object note_as_kb_state_change_qm, do_not_note_permanent_changes_p;
    Declare_special(2);
    Object result;

    x_note_fn_call(187,147);
    if ( !(INTEGERP(desired_length) && IFIX(desired_length) >= (SI_Long)0L 
	    && FIXNUM_LE(desired_length,G2_array_length_maximum)))
	bad_g2_array_length_stack_error(value_array,desired_length,
		Cached_top_of_stack);
    note_as_kb_state_change_qm = T;
    do_not_note_permanent_changes_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_note_permanent_changes_p,Qdo_not_note_permanent_changes_p,do_not_note_permanent_changes_p,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Note_as_kb_state_change_qm,Qnote_as_kb_state_change_qm,note_as_kb_state_change_qm,
	      0);
	note_kb_state_change(value_array,Qg2_array_length);
	note_kb_state_change(index_array,Qg2_array_length);
	change_slot_value(3,value_array,Qg2_array_length,desired_length);
	result = change_slot_value(3,index_array,Qg2_array_length,
		desired_length);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_35;  /* "The index ~d for the packed vector is greater than the maximum index ~d for the array ~NF." */

static Object string_constant_36;  /* "The index ~d for the packed vector is negative" */

/* G2-INTEGER-SPARSE-SCATTER */
Object g2_integer_sparse_scatter(value_array,index_array,full_array,
	    begin_index,end_index)
    Object value_array, index_array, full_array, begin_index, end_index;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, full_index, top_of_stack, message_1, temp;
    Object svref_new_value;
    SI_Long j, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(187,148);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index,max_index);
    check_index_within_bounds(end_index,max_index);
    j = IFIX(begin_index);
    ab_loop_bind_ = IFIX(end_index);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(full_index,Managed_array_index_offset);
	svref_new_value = FIXNUM_LE(ISVREF(value_managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(value_managed_array,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(value_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	SVREF(full_managed_array,temp) = svref_new_value;
    }
    else {
	temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
	svref_new_value = FIXNUM_LE(ISVREF(value_managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(value_managed_array,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(value_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	ISVREF(temp,svref_arg_2) = svref_new_value;
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_37;  /* "~a is not a valid value for an integer array " */

/* G2-QUANTITY-TO-INTEGER-SPARSE-SCATTER */
Object g2_quantity_to_integer_sparse_scatter(value_array,index_array,
	    full_array,begin_index,end_index)
    Object value_array, index_array, full_array, begin_index, end_index;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, full_index, value, top_of_stack, message_1;
    Object temp;
    SI_Long j, ab_loop_bind_, svref_arg_2;

    x_note_fn_call(187,149);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index,max_index);
    check_index_within_bounds(end_index,max_index);
    j = IFIX(begin_index);
    ab_loop_bind_ = IFIX(end_index);
    full_index = Nil;
    value = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    value = evaluation_value_value(FIXNUM_LE(ISVREF(value_managed_array,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(value_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(value_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L));
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !FIXNUMP(value)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_37,
		value);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(full_index,Managed_array_index_offset);
	SVREF(full_managed_array,temp) = value;
    }
    else {
	temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = value;
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-INTEGER-SPARSE-GATHER */
Object g2_integer_sparse_gather(value_array,index_array,full_array)
    Object value_array, index_array, full_array;
{
    Object n_1, l, value_managed_array, index_managed_array;
    Object full_managed_array, sparse_index, value_array_length, value, temp;
    SI_Long j, ab_loop_bind_, svref_arg_2;
    Object result;

    x_note_fn_call(187,150);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    sparse_index = FIX((SI_Long)0L);
    value_array_length = l;
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
    value = Nil;
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    value = FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(full_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(full_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if (IFIX(value) != (SI_Long)0L) {
	if ( !FIXNUM_LT(sparse_index,value_array_length)) {
	    result = extend_sparse_vector_as_necessary(value_array,
		    index_array,sparse_index,value_array_length);
	    MVS_3(result,value_array_length,value_managed_array,
		    index_managed_array);
	}
	if (FIXNUM_LE(ISVREF(value_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    SVREF(value_managed_array,temp) = value;
	}
	else {
	    temp = ISVREF(value_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = value;
	}
	if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    ISVREF(index_managed_array,IFIX(temp)) = FIX(j);
	}
	else {
	    temp = ISVREF(index_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX(j);
	}
	if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = j + IFIX(Managed_array_index_offset);
	    ISVREF(full_managed_array,svref_arg_2) = FIX((SI_Long)0L);
	}
	else {
	    temp = ISVREF(full_managed_array,(j >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = j & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	}
	sparse_index = FIXNUM_ADD1(sparse_index);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    make_sparse_vector_exact_size(value_array,index_array,sparse_index,
	    value_array_length);
    return VALUES_1(Qnil);
}

/* G2-INTEGER-SPARSE-ADD */
Object g2_integer_sparse_add(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,alpha,begin_index_1,end_index_1,
	    begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, alpha, begin_index_1, end_index_1, begin_index_2;
    Object end_index_2, full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value, l2, max_index_2, full_index;
    Object top_of_stack, message_1, temp, index_managed_array_2;
    Object value_managed_array_2, value_array_length, sparse_index;
    Object svref_new_value_1;
    SI_Long j, ab_loop_bind_, svref_arg_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long svref_new_value;
    Object result;

    x_note_fn_call(187,151);
    if ( !TRUEP(full_array_initialized_qm))
	g2_integer_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value = Nil;
    l2 = check_array_lengths_compatible(2,value_array_2,index_array_2);
    max_index_2 = FIXNUM_SUB1(l2);
    check_index_within_bounds(begin_index_2,max_index_2);
    check_index_within_bounds(end_index_2,max_index_2);
    j = IFIX(begin_index_1);
    ab_loop_bind_ = IFIX(end_index_1);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    value = FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(full_managed_array,
	    IFIX(FIXNUM_ADD(full_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(full_index) & (SI_Long)1023L);
    if (IFIX(value) != (SI_Long)0L) {
	if (FIXNUM_LE(ISVREF(value_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = j + IFIX(Managed_array_index_offset);
	    gensymed_symbol = FIXNUM_LE(ISVREF(value_managed_array,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(value_managed_array,j + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(value_managed_array,(j >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
	    gensymed_symbol_1 = IFIX(FIXNUM_TIMES(alpha,value));
	    svref_new_value = gensymed_symbol + gensymed_symbol_1;
	    ISVREF(value_managed_array,svref_arg_2) = FIX(svref_new_value);
	}
	else {
	    temp = ISVREF(value_managed_array,(j >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = j & (SI_Long)1023L;
	    gensymed_symbol = FIXNUM_LE(ISVREF(value_managed_array,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    IFIX(ISVREF(value_managed_array,j + 
		    IFIX(Managed_array_index_offset))) : 
		    IFIX(ISVREF(ISVREF(value_managed_array,(j >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
	    gensymed_symbol_1 = IFIX(FIXNUM_TIMES(alpha,value));
	    svref_new_value = gensymed_symbol + gensymed_symbol_1;
	    ISVREF(temp,svref_arg_2) = FIX(svref_new_value);
	}
	if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(full_index,Managed_array_index_offset);
	    ISVREF(full_managed_array,IFIX(temp)) = FIX((SI_Long)0L);
	}
	else {
	    temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	}
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
    value_managed_array_2 = ISVREF(value_array_2,(SI_Long)23L);
    value_array_length = l;
    sparse_index = value_array_length;
    j = IFIX(begin_index_2);
    ab_loop_bind_ = IFIX(end_index_2);
    full_index = Nil;
  next_loop_1:
    if (j > ab_loop_bind_)
	goto end_loop_1;
    full_index = FIXNUM_LE(ISVREF(index_managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array_2,j 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array_2,(j >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    value = FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(full_managed_array,
	    IFIX(FIXNUM_ADD(full_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(full_index) & (SI_Long)1023L);
    if (IFIX(value) != (SI_Long)0L) {
	if ( !FIXNUM_LT(sparse_index,value_array_length)) {
	    result = extend_sparse_vector_as_necessary(value_array_1,
		    index_array_1,sparse_index,value_array_length);
	    MVS_3(result,value_array_length,value_managed_array,
		    index_managed_array);
	}
	if (FIXNUM_LE(ISVREF(value_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    svref_new_value_1 = FIXNUM_TIMES(alpha,value);
	    SVREF(value_managed_array,temp) = svref_new_value_1;
	}
	else {
	    temp = ISVREF(value_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    svref_new_value_1 = FIXNUM_TIMES(alpha,value);
	    ISVREF(temp,svref_arg_2) = svref_new_value_1;
	}
	if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    SVREF(index_managed_array,temp) = full_index;
	}
	else {
	    temp = ISVREF(index_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = full_index;
	}
	if ( !TRUEP(full_array_initialized_qm)) {
	    if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp = FIXNUM_ADD(full_index,Managed_array_index_offset);
		ISVREF(full_managed_array,IFIX(temp)) = FIX((SI_Long)0L);
	    }
	    else {
		temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
		ISVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	    }
	}
	sparse_index = FIXNUM_ADD1(sparse_index);
    }
    else if (full_array_initialized_qm) {
	if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(full_index,Managed_array_index_offset);
	    svref_new_value_1 = FIXNUM_LE(ISVREF(value_managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(value_managed_array_2,j + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(value_managed_array_2,(j >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	    SVREF(full_managed_array,temp) = svref_new_value_1;
	}
	else {
	    temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
	    svref_new_value_1 = FIXNUM_LE(ISVREF(value_managed_array_2,
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(value_managed_array_2,j + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(value_managed_array_2,(j >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	    ISVREF(temp,svref_arg_2) = svref_new_value_1;
	}
    }
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    make_sparse_vector_exact_size(value_array_1,index_array_1,sparse_index,
	    value_array_length);
    return VALUES_1(Qnil);
}

/* G2-INTEGER-SPARSE-MULTIPLY */
Object g2_integer_sparse_multiply(value_array_1,index_array_1,
	    value_array_2,index_array_2,full_array,begin_index_1,
	    end_index_1,begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, begin_index_1, end_index_1, begin_index_2, end_index_2;
    Object full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value, product, full_index, top_of_stack;
    Object message_1, index_managed_array_2, gensymed_symbol_3, temp;
    SI_Long j, ab_loop_bind_, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2, svref_arg_2;

    x_note_fn_call(187,152);
    if ( !TRUEP(full_array_initialized_qm))
	g2_integer_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value = Nil;
    product = FIX((SI_Long)0L);
    j = IFIX(begin_index_1);
    ab_loop_bind_ = IFIX(end_index_1);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    value = FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(full_managed_array,
	    IFIX(FIXNUM_ADD(full_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(full_index) & (SI_Long)1023L);
    if (IFIX(value) != (SI_Long)0L) {
	gensymed_symbol = IFIX(product);
	gensymed_symbol_1 = IFIX(value);
	gensymed_symbol_2 = FIXNUM_LE(ISVREF(value_managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		IFIX(ISVREF(value_managed_array,j + 
		IFIX(Managed_array_index_offset))) : 
		IFIX(ISVREF(ISVREF(value_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L));
	gensymed_symbol_1 = gensymed_symbol_1 * gensymed_symbol_2;
	product = FIX(gensymed_symbol + gensymed_symbol_1);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !TRUEP(full_array_initialized_qm)) {
	index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
	j = IFIX(begin_index_2);
	ab_loop_bind_ = IFIX(end_index_2);
      next_loop_1:
	if (j > ab_loop_bind_)
	    goto end_loop_1;
	gensymed_symbol_3 = FIXNUM_LE(ISVREF(index_managed_array_2,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(index_managed_array_2,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(index_managed_array_2,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(gensymed_symbol_3,Managed_array_index_offset);
	    ISVREF(full_managed_array,IFIX(temp)) = FIX((SI_Long)0L);
	}
	else {
	    temp = ISVREF(full_managed_array,(IFIX(gensymed_symbol_3) >>  
		    -  - (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(gensymed_symbol_3) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	}
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_1(product);
    return VALUES_1(Qnil);
}

/* G2-FLOAT-SPARSE-SCATTER */
Object g2_float_sparse_scatter(value_array,index_array,full_array,
	    begin_index,end_index)
    Object value_array, index_array, full_array, begin_index, end_index;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, full_index, top_of_stack, message_1, aref_arg_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    double aref_new_value;

    x_note_fn_call(187,153);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index,max_index);
    check_index_within_bounds(end_index,max_index);
    j = IFIX(begin_index);
    ab_loop_bind_ = IFIX(end_index);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    aref_arg_1 = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L);
    aref_arg_2 = IFIX(full_index) & (SI_Long)1023L;
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_managed_array,(j >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    DFLOAT_ISASET_1(aref_arg_1,aref_arg_2,aref_new_value);
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-FLOAT-SPARSE-GATHER */
Object g2_float_sparse_gather(value_array,index_array,full_array)
    Object value_array, index_array, full_array;
{
    Object n_1, l, value_managed_array, index_managed_array;
    Object full_managed_array, sparse_index, value_array_length;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, boxed_zero;
    SI_Long j, ab_loop_bind_, temp_2;
    double arg, arg_1, aref_new_value;
    Object result;

    x_note_fn_call(187,154);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    sparse_index = FIX((SI_Long)0L);
    value_array_length = l;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    boxed_zero = new_float;
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    arg = DFLOAT_ISAREF_1(ISVREF(full_managed_array,(j >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
    arg_1 = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))) {
	if ( !FIXNUM_LT(sparse_index,value_array_length)) {
	    result = extend_sparse_vector_as_necessary(value_array,
		    index_array,sparse_index,value_array_length);
	    MVS_3(result,value_array_length,value_managed_array,
		    index_managed_array);
	}
	temp = ISVREF(value_managed_array,(IFIX(sparse_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(full_managed_array,(j >>  
		-  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    ISVREF(index_managed_array,IFIX(temp)) = FIX(j);
	}
	else {
	    temp = ISVREF(index_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_2) = FIX(j);
	}
	temp = ISVREF(full_managed_array,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_2 = j & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	sparse_index = FIXNUM_ADD1(sparse_index);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    make_sparse_vector_exact_size(value_array,index_array,sparse_index,
	    value_array_length);
    return VALUES_1(Qnil);
}

/* G2-FLOAT-SPARSE-ADD */
Object g2_float_sparse_add(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,alpha,begin_index_1,end_index_1,
	    begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, alpha, begin_index_1, end_index_1, begin_index_2;
    Object end_index_2, full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value_box, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, boxed_zero, l2;
    Object max_index_2, full_index, top_of_stack, message_1;
    Object index_managed_array_2, value_managed_array_2, value_array_length;
    Object sparse_index;
    SI_Long j, ab_loop_bind_, temp_2;
    double aref_new_value, arg, arg_1, temp_3, temp_4;
    Object result;

    x_note_fn_call(187,155);
    if ( !TRUEP(full_array_initialized_qm))
	g2_float_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value_box = allocate_managed_float_box();
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    boxed_zero = new_float;
    l2 = check_array_lengths_compatible(2,value_array_2,index_array_2);
    max_index_2 = FIXNUM_SUB1(l2);
    check_index_within_bounds(begin_index_2,max_index_2);
    check_index_within_bounds(end_index_2,max_index_2);
    j = IFIX(begin_index_1);
    ab_loop_bind_ = IFIX(end_index_1);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(full_managed_array,
	    (IFIX(full_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(full_index) & (SI_Long)1023L);
    DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
    arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
    arg_1 = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))) {
	temp = ISVREF(value_managed_array,(j >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	temp_2 = j & (SI_Long)1023L;
	temp_3 = DFLOAT_ISAREF_1(ISVREF(value_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(alpha);
	aref_new_value = temp_3 + temp_4 * DFLOAT_ISAREF_1(value_box,
		(SI_Long)0L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(full_index) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
    value_managed_array_2 = ISVREF(value_array_2,(SI_Long)23L);
    value_array_length = l;
    sparse_index = value_array_length;
    j = IFIX(begin_index_2);
    ab_loop_bind_ = IFIX(end_index_2);
    full_index = Nil;
  next_loop_1:
    if (j > ab_loop_bind_)
	goto end_loop_1;
    full_index = FIXNUM_LE(ISVREF(index_managed_array_2,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array_2,j 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array_2,(j >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(full_managed_array,
	    (IFIX(full_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(full_index) & (SI_Long)1023L);
    DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
    arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
    arg_1 = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))) {
	if ( !FIXNUM_LT(sparse_index,value_array_length)) {
	    result = extend_sparse_vector_as_necessary(value_array_1,
		    index_array_1,sparse_index,value_array_length);
	    MVS_3(result,value_array_length,value_managed_array,
		    index_managed_array);
	}
	temp = ISVREF(value_managed_array,(IFIX(sparse_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(alpha);
	aref_new_value = temp_4 * DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    SVREF(index_managed_array,temp) = full_index;
	}
	else {
	    temp = ISVREF(index_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,temp_2) = full_index;
	}
	if ( !TRUEP(full_array_initialized_qm)) {
	    temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    temp_2 = IFIX(full_index) & (SI_Long)1023L;
	    aref_new_value = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
	}
	sparse_index = FIXNUM_ADD1(sparse_index);
    }
    else if (full_array_initialized_qm) {
	temp = ISVREF(full_managed_array,(IFIX(full_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	temp_2 = IFIX(full_index) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_managed_array_2,(j 
		>>  -  - (SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(temp,temp_2,aref_new_value);
    }
    j = j + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    make_sparse_vector_exact_size(value_array_1,index_array_1,sparse_index,
	    value_array_length);
    reclaim_managed_simple_float_array_of_length_1(boxed_zero);
    reclaim_managed_simple_float_array_of_length_1(value_box);
    return VALUES_1(Nil);
}

/* G2-FLOAT-SPARSE-MULTIPLY */
Object g2_float_sparse_multiply(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,begin_index_1,end_index_1,
	    begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, begin_index_1, end_index_1, begin_index_2, end_index_2;
    Object full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value_box, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, product_box;
    Object boxed_zero, full_index, top_of_stack, message_1;
    Object index_managed_array_2, gensymed_symbol, gensymed_symbol_1;
    SI_Long j, ab_loop_bind_, aref_arg_2;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(187,156);
    if ( !TRUEP(full_array_initialized_qm))
	g2_float_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value_box = allocate_managed_float_box();
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    product_box = new_float;
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    boxed_zero = new_float;
    j = IFIX(begin_index_1);
    ab_loop_bind_ = IFIX(end_index_1);
    full_index = Nil;
  next_loop:
    if (j > ab_loop_bind_)
	goto end_loop;
    full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(index_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(index_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L);
    if ( !FIXNUM_LT(full_index,n_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_35,
		full_index,FIXNUM_SUB1(n_1),full_array);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else if (minusp(full_index)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		full_index);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    aref_new_value = DFLOAT_ISAREF_1(ISVREF(full_managed_array,
	    (IFIX(full_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(full_index) & (SI_Long)1023L);
    DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
    arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
    arg_1 = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
    if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))) {
	aref_new_value = DFLOAT_ISAREF_1(product_box,(SI_Long)0L) + 
		DFLOAT_ISAREF_1(value_box,(SI_Long)0L) * 
		DFLOAT_ISAREF_1(ISVREF(value_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	DFLOAT_ISASET_1(product_box,(SI_Long)0L,aref_new_value);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if ( !TRUEP(full_array_initialized_qm)) {
	index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
	j = IFIX(begin_index_2);
	ab_loop_bind_ = IFIX(end_index_2);
      next_loop_1:
	if (j > ab_loop_bind_)
	    goto end_loop_1;
	gensymed_symbol = full_managed_array;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(index_managed_array_2,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(index_managed_array_2,j + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(index_managed_array_2,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L);
	temp = ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	aref_arg_2 = IFIX(gensymed_symbol_1) & (SI_Long)1023L;
	aref_new_value = DFLOAT_ISAREF_1(boxed_zero,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,aref_arg_2,aref_new_value);
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    reclaim_managed_simple_float_array_of_length_1(value_box);
    reclaim_managed_simple_float_array_of_length_1(boxed_zero);
    return VALUES_1(product_box);
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-SPARSE-SCATTER */
Object g2_quantity_sparse_scatter(value_array,index_array,full_array,
	    begin_index,end_index)
    Object value_array, index_array, full_array, begin_index, end_index;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, j, full_index, n_minus_1, temp, end_value_of_j;
    Object top_of_stack, message_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,157);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index,max_index);
    check_index_within_bounds(end_index,max_index);
    j = begin_index;
    full_index = Nil;
  next_loop:
    n_minus_1 = FIXNUM_SUB1(FIXNUM_ADD1(end_index));
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(index_managed_array,
		IFIX(FIXNUM_ADD(j,Managed_array_index_offset))) : 
		ISVREF(ISVREF(index_managed_array,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	if ( !FIXNUM_LT(full_index,n_1)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_35,full_index,FIXNUM_SUB1(n_1),full_array);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if (minusp(full_index)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_36,full_index);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	temp = full_index;
	set_quantity_element(full_managed_array,temp,
		get_quantity_element(value_managed_array,j));
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-SPARSE-GATHER */
Object g2_quantity_sparse_gather(value_array,index_array,full_array)
    Object value_array, index_array, full_array;
{
    Object n_1, l, value_managed_array, index_managed_array;
    Object full_managed_array, sparse_index, value_array_length, value_box;
    Object sub_class_bit_vector, integer_array_qm, j, n_minus_1, temp;
    Object end_value_of_j, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    double aref_new_value, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,158);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    sparse_index = FIX((SI_Long)0L);
    value_array_length = l;
    value_box = allocate_managed_float_box();
    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	integer_array_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	integer_array_qm = Nil;
    j = FIX((SI_Long)0L);
  next_loop:
    n_minus_1 = FIXNUM_SUB1(n_1);
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	temp = get_quantity_element(full_managed_array,j);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
	arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	arg_1 = 0.0;
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    if ( !FIXNUM_LT(sparse_index,value_array_length)) {
		result = extend_sparse_vector_as_necessary(value_array,
			index_array,sparse_index,value_array_length);
		MVS_3(result,value_array_length,value_managed_array,
			index_managed_array);
	    }
	    set_quantity_element(value_managed_array,sparse_index,
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_box,
		    (SI_Long)0L)));
	    if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_1 = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
		SVREF(index_managed_array,temp_1) = j;
	    }
	    else {
		temp_1 = ISVREF(index_managed_array,(IFIX(sparse_index) >> 
			 -  - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = j;
	    }
	    if (integer_array_qm)
		set_quantity_element(full_managed_array,j,FIX((SI_Long)0L));
	    else
		set_quantity_element(full_managed_array,j,float_constant);
	    sparse_index = FIXNUM_ADD1(sparse_index);
	}
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    reclaim_managed_simple_float_array_of_length_1(value_box);
    make_sparse_vector_exact_size(value_array,index_array,sparse_index,
	    value_array_length);
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-TO-INTEGER-SPARSE-GATHER */
Object g2_quantity_to_integer_sparse_gather(value_array,index_array,full_array)
    Object value_array, index_array, full_array;
{
    Object n_1, l, value_managed_array, index_managed_array;
    Object full_managed_array, sparse_index, value_array_length, value;
    Object top_of_stack, message_1, temp;
    SI_Long j, ab_loop_bind_, svref_arg_2;
    Object result;

    x_note_fn_call(187,159);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array,index_array);
    value_managed_array = ISVREF(value_array,(SI_Long)23L);
    index_managed_array = ISVREF(index_array,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    sparse_index = FIX((SI_Long)0L);
    value_array_length = l;
    j = (SI_Long)0L;
    ab_loop_bind_ = IFIX(n_1);
    value = Nil;
  next_loop:
    if (j >= ab_loop_bind_)
	goto end_loop;
    value = evaluation_value_value(FIXNUM_LE(ISVREF(full_managed_array,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(full_managed_array,j + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(full_managed_array,(j >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),j & (SI_Long)1023L));
    if ( !FIXNUMP(value)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_37,
		value);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (IFIX(value) != (SI_Long)0L) {
	if ( !FIXNUM_LT(sparse_index,value_array_length)) {
	    result = extend_sparse_vector_as_necessary(value_array,
		    index_array,sparse_index,value_array_length);
	    MVS_3(result,value_array_length,value_managed_array,
		    index_managed_array);
	}
	if (FIXNUM_LE(ISVREF(value_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    SVREF(value_managed_array,temp) = value;
	}
	else {
	    temp = ISVREF(value_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = value;
	}
	if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
	    ISVREF(index_managed_array,IFIX(temp)) = FIX(j);
	}
	else {
	    temp = ISVREF(index_managed_array,(IFIX(sparse_index) >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX(j);
	}
	if (FIXNUM_LE(ISVREF(full_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = j + IFIX(Managed_array_index_offset);
	    ISVREF(full_managed_array,svref_arg_2) = FIX((SI_Long)0L);
	}
	else {
	    temp = ISVREF(full_managed_array,(j >>  -  - (SI_Long)10L) + 
		    (SI_Long)2L);
	    svref_arg_2 = j & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	}
	sparse_index = FIXNUM_ADD1(sparse_index);
    }
    j = j + (SI_Long)1L;
    goto next_loop;
  end_loop:
    make_sparse_vector_exact_size(value_array,index_array,sparse_index,
	    value_array_length);
    return VALUES_1(Qnil);
}

/* G2-QUANTITY-SPARSE-ADD */
Object g2_quantity_sparse_add(value_array_1,index_array_1,value_array_2,
	    index_array_2,full_array,alpha,begin_index_1,end_index_1,
	    begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, alpha, begin_index_1, end_index_1, begin_index_2;
    Object end_index_2, full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value_box, full_index, l2, max_index_2, j;
    Object n_minus_1, temp, end_value_of_j, top_of_stack, message_1, temp_1;
    Object temp_2, index_managed_array_2, value_managed_array_2;
    Object value_array_length, sparse_index, sub_class_bit_vector;
    Object integer_array_qm, temp_5;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_arg_2;
    double aref_new_value, arg, arg_1, temp_3, temp_4;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,160);
    if ( !TRUEP(full_array_initialized_qm))
	g2_quantity_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value_box = allocate_managed_float_box();
    full_index = Nil;
    l2 = check_array_lengths_compatible(2,value_array_2,index_array_2);
    max_index_2 = FIXNUM_SUB1(l2);
    check_index_within_bounds(begin_index_2,max_index_2);
    check_index_within_bounds(end_index_2,max_index_2);
    j = begin_index_1;
  next_loop:
    n_minus_1 = FIXNUM_SUB1(FIXNUM_ADD1(end_index_1));
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	goto end_1;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(index_managed_array,
		IFIX(FIXNUM_ADD(j,Managed_array_index_offset))) : 
		ISVREF(ISVREF(index_managed_array,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	if ( !FIXNUM_LT(full_index,n_1)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_35,full_index,FIXNUM_SUB1(n_1),full_array);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if (minusp(full_index)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_36,full_index);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	temp = get_quantity_element(full_managed_array,full_index);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
	arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	arg_1 = 0.0;
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    temp = value_managed_array;
	    temp_1 = j;
	    temp_2 = get_quantity_element(value_managed_array,j);
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	    temp_4 = DOUBLE_FLOAT_TO_DOUBLE(alpha);
	    set_quantity_element(temp,temp_1,DOUBLE_TO_DOUBLE_FLOAT(temp_3 
		    + temp_4 * DFLOAT_ISAREF_1(value_box,(SI_Long)0L)));
	    set_quantity_element(full_managed_array,full_index,float_constant);
	}
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_2;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_2;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_2:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
  end_1:;
    index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
    value_managed_array_2 = ISVREF(value_array_2,(SI_Long)23L);
    value_array_length = l;
    sparse_index = value_array_length;
    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	integer_array_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	integer_array_qm = Nil;
    j = begin_index_2;
  next_loop_2:
    n_minus_1 = FIXNUM_SUB1(FIXNUM_ADD1(end_index_2));
    temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
    if (FIXNUM_GT(j,n_minus_1))
	goto end_3;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_3:
	full_index = FIXNUM_LE(ISVREF(index_managed_array_2,(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(index_managed_array_2,IFIX(FIXNUM_ADD(j,
		Managed_array_index_offset))) : 
		ISVREF(ISVREF(index_managed_array_2,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	if ( !FIXNUM_LT(full_index,n_1)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_35,full_index,FIXNUM_SUB1(n_1),full_array);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if (minusp(full_index)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_36,full_index);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	temp = get_quantity_element(full_managed_array,full_index);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
	arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	arg_1 = 0.0;
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    if ( !FIXNUM_LT(sparse_index,value_array_length)) {
		result = extend_sparse_vector_as_necessary(value_array_1,
			index_array_1,sparse_index,value_array_length);
		MVS_3(result,value_array_length,value_managed_array,
			index_managed_array);
	    }
	    temp_3 = DOUBLE_FLOAT_TO_DOUBLE(alpha);
	    set_quantity_element(value_managed_array,sparse_index,
		    DOUBLE_TO_DOUBLE_FLOAT(temp_3 * 
		    DFLOAT_ISAREF_1(value_box,(SI_Long)0L)));
	    if (FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		temp_5 = FIXNUM_ADD(sparse_index,Managed_array_index_offset);
		SVREF(index_managed_array,temp_5) = full_index;
	    }
	    else {
		temp_5 = ISVREF(index_managed_array,(IFIX(sparse_index) >> 
			 -  - (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = IFIX(sparse_index) & (SI_Long)1023L;
		ISVREF(temp_5,svref_arg_2) = full_index;
	    }
	    if ( !TRUEP(full_array_initialized_qm)) {
		if (integer_array_qm)
		    set_quantity_element(full_managed_array,full_index,
			    FIX((SI_Long)0L));
		else
		    set_quantity_element(full_managed_array,full_index,
			    float_constant);
	    }
	    sparse_index = FIXNUM_ADD1(sparse_index);
	}
	else if (full_array_initialized_qm) {
	    temp = full_index;
	    set_quantity_element(full_managed_array,temp,
		    get_quantity_element(value_managed_array_2,j));
	}
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_4;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_4;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_3;
      end_loop_2:
	j = Qnil;
      end_4:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_3;
    goto next_loop_2;
  end_loop_3:
    make_sparse_vector_exact_size(value_array_1,index_array_1,sparse_index,
	    value_array_length);
  end_3:;
    reclaim_managed_simple_float_array_of_length_1(value_box);
    return VALUES_1(Nil);
}

/* G2-QUANTITY-SPARSE-MULTIPLY */
Object g2_quantity_sparse_multiply(value_array_1,index_array_1,
	    value_array_2,index_array_2,full_array,begin_index_1,
	    end_index_1,begin_index_2,end_index_2,full_array_initialized_qm)
    Object value_array_1, index_array_1, value_array_2, index_array_2;
    Object full_array, begin_index_1, end_index_1, begin_index_2, end_index_2;
    Object full_array_initialized_qm;
{
    Object n_1, l, max_index, value_managed_array, index_managed_array;
    Object full_managed_array, value_box, amf_available_array_cons_qm;
    Object amf_array, temp, temp_1, amf_result, new_float, product_box;
    Object sub_class_bit_vector, integer_array_qm, full_index, j, n_minus_1;
    Object temp_2, end_value_of_j, top_of_stack, message_1;
    Object index_managed_array_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    double aref_new_value, arg, arg_1, temp_3, temp_4, temp_5;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(187,161);
    if ( !TRUEP(full_array_initialized_qm))
	g2_quantity_sparse_scatter(value_array_2,index_array_2,full_array,
		begin_index_2,end_index_2);
    n_1 = ISVREF(full_array,(SI_Long)20L);
    l = check_array_lengths_compatible(2,value_array_1,index_array_1);
    max_index = FIXNUM_SUB1(l);
    value_managed_array = ISVREF(value_array_1,(SI_Long)23L);
    index_managed_array = ISVREF(index_array_1,(SI_Long)23L);
    full_managed_array = ISVREF(full_array,(SI_Long)23L);
    check_index_within_bounds(begin_index_1,max_index);
    check_index_within_bounds(end_index_1,max_index);
    value_box = allocate_managed_float_box();
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    product_box = new_float;
    sub_class_bit_vector = ISVREF(ISVREF(full_array,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	integer_array_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	integer_array_qm = Nil;
    full_index = Nil;
    j = begin_index_1;
  next_loop:
    n_minus_1 = FIXNUM_SUB1(FIXNUM_ADD1(end_index_1));
    temp_2 = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
    end_value_of_j = FIXNUM_MIN(n_minus_1,temp_2);
    if (FIXNUM_GT(j,n_minus_1))
	return VALUES_1(Nil);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
      next_loop_1:
	full_index = FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(index_managed_array,
		IFIX(FIXNUM_ADD(j,Managed_array_index_offset))) : 
		ISVREF(ISVREF(index_managed_array,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	if ( !FIXNUM_LT(full_index,n_1)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_35,full_index,FIXNUM_SUB1(n_1),full_array);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if (minusp(full_index)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_36,full_index);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	temp_2 = get_quantity_element(full_managed_array,full_index);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(value_box,(SI_Long)0L,aref_new_value);
	arg = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	arg_1 = 0.0;
	if ( !(arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))) {
	    temp_3 = DFLOAT_ISAREF_1(product_box,(SI_Long)0L);
	    temp_4 = DFLOAT_ISAREF_1(value_box,(SI_Long)0L);
	    temp_2 = get_quantity_element(value_managed_array,j);
	    temp_5 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	    aref_new_value = temp_3 + temp_4 * temp_5;
	    DFLOAT_ISASET_1(product_box,(SI_Long)0L,aref_new_value);
	}
	if (FIXNUM_GE(j,n_minus_1)) {
	    j = Nil;
	    goto end_1;
	}
	if (FIXNUM_EQ(j,end_value_of_j)) {
	    j = end_value_of_j;
	    goto end_1;
	}
	j = FIXNUM_ADD1(j);
	goto next_loop_1;
      end_loop:
	j = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    if ( !TRUEP(j))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    if ( !TRUEP(full_array_initialized_qm)) {
	index_managed_array_2 = ISVREF(index_array_2,(SI_Long)23L);
	j = begin_index_2;
      next_loop_2:
	n_minus_1 = FIXNUM_SUB1(FIXNUM_ADD1(end_index_2));
	temp_2 = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
	end_value_of_j = FIXNUM_MIN(n_minus_1,temp_2);
	if (FIXNUM_GT(j,n_minus_1))
	    goto end_2;
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	  next_loop_3:
	    if (integer_array_qm)
		set_quantity_element(full_managed_array,
			FIXNUM_LE(ISVREF(index_managed_array_2,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(index_managed_array_2,IFIX(FIXNUM_ADD(j,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(index_managed_array_2,(IFIX(j) >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
			(SI_Long)1023L),FIX((SI_Long)0L));
	    else
		set_quantity_element(full_managed_array,
			FIXNUM_LE(ISVREF(index_managed_array_2,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(index_managed_array_2,IFIX(FIXNUM_ADD(j,
			Managed_array_index_offset))) : 
			ISVREF(ISVREF(index_managed_array_2,(IFIX(j) >>  - 
			 - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
			(SI_Long)1023L),float_constant);
	    if (FIXNUM_GE(j,n_minus_1)) {
		j = Nil;
		goto end_3;
	    }
	    if (FIXNUM_EQ(j,end_value_of_j)) {
		j = end_value_of_j;
		goto end_3;
	    }
	    j = FIXNUM_ADD1(j);
	    goto next_loop_3;
	  end_loop_2:
	    j = Qnil;
	  end_3:;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if ( !TRUEP(j))
	    goto end_loop_3;
	goto next_loop_2;
      end_loop_3:
      end_2:;
    }
    reclaim_managed_simple_float_array_of_length_1(value_box);
    return VALUES_1(product_box);
    return VALUES_1(Qnil);
}

static Object string_constant_38;  /* "The value vector ~NF is of length 0 and is therefore not suitable for the current operation." */

/* ZERO-LENGTH-SPARSE-VECTOR-ERROR */
Object zero_length_sparse_vector_error(value_array)
    Object value_array;
{
    Object top_of_stack, message_1;

    x_note_fn_call(187,162);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(2,string_constant_38,
	    value_array);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

/* INTEGER-ACCUMULATION-FOR-SPARSE-MIN */
Object integer_accumulation_for_sparse_min(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object value;

    x_note_fn_call(187,163);
    value = FIXNUM_LE(ISVREF(value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(value_array,
	    IFIX(FIXNUM_ADD(j,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(value_array,(IFIX(j) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
    if ( !TRUEP(accumulation) || FIXNUM_LT(value,accumulation)) {
	Result_index = j;
	return VALUES_1(value);
    }
    else
	return VALUES_1(accumulation);
}

/* INTEGER-ACCUMULATION-FOR-SPARSE-MAX */
Object integer_accumulation_for_sparse_max(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object value;

    x_note_fn_call(187,164);
    value = FIXNUM_LE(ISVREF(value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(value_array,
	    IFIX(FIXNUM_ADD(j,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(value_array,(IFIX(j) >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
    if ( !TRUEP(accumulation) || FIXNUM_GT(value,accumulation)) {
	Result_index = j;
	return VALUES_1(value);
    }
    else
	return VALUES_1(accumulation);
}

/* INTEGER-ACCUMULATION-FOR-SPARSE-SUM */
Object integer_accumulation_for_sparse_sum(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(187,165);
    gensymed_symbol = IFIX(accumulation);
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(value_array,
	    IFIX(FIXNUM_ADD(j,Managed_array_index_offset)))) : 
	    IFIX(ISVREF(ISVREF(value_array,(IFIX(j) >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),IFIX(j) & (SI_Long)1023L));
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

/* INTEGER-ACCUMULATION-FOR-SPARSE-SUM-ABS */
Object integer_accumulation_for_sparse_sum_abs(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(187,166);
    gensymed_symbol = IFIX(accumulation);
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(value_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? IFIX(ISVREF(value_array,
	    IFIX(FIXNUM_ADD(j,Managed_array_index_offset)))) : 
	    IFIX(ISVREF(ISVREF(value_array,(IFIX(j) >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),IFIX(j) & (SI_Long)1023L));
    gensymed_symbol_1 = ABS(gensymed_symbol_1);
    return VALUES_1(FIX(gensymed_symbol + gensymed_symbol_1));
}

/* FLOAT-ACCUMULATION-FOR-SPARSE-MIN */
Object float_accumulation_for_sparse_min(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(187,167);
    if ( !TRUEP(accumulation)) {
	Result_index = j;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	accumulation = new_float;
    }
    else {
	arg = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	arg_1 = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    Result_index = j;
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
		    (SI_Long)1023L);
	    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
	}
    }
    return VALUES_1(accumulation);
}

/* FLOAT-ACCUMULATION-FOR-SPARSE-MAX */
Object float_accumulation_for_sparse_max(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(187,168);
    if ( !TRUEP(accumulation)) {
	Result_index = j;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	accumulation = new_float;
    }
    else {
	arg = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
	arg_1 = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    Result_index = j;
	    aref_new_value = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(j) & 
		    (SI_Long)1023L);
	    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
	}
    }
    return VALUES_1(accumulation);
}

/* FLOAT-ACCUMULATION-FOR-SPARSE-SUM */
Object float_accumulation_for_sparse_sum(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    double aref_new_value;

    x_note_fn_call(187,169);
    aref_new_value = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L) + 
	    DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
    return VALUES_1(accumulation);
}

/* FLOAT-ACCUMULATION-FOR-SPARSE-SUM-ABS */
Object float_accumulation_for_sparse_sum_abs(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    double temp, temp_1, aref_new_value;

    x_note_fn_call(187,170);
    temp = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L);
    temp_1 = DFLOAT_ISAREF_1(ISVREF(value_array,(IFIX(j) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(j) & (SI_Long)1023L);
    aref_new_value = temp + ABS(temp_1);
    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
    return VALUES_1(accumulation);
}

/* QUANTITY-ACCUMULATION-FOR-SPARSE-MIN */
Object quantity_accumulation_for_sparse_min(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object element_value, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(187,171);
    element_value = get_quantity_element(value_array,j);
    if ( !TRUEP(accumulation)) {
	Result_index = j;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	accumulation = new_float;
    }
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	arg_1 = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L);
	if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    Result_index = j;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
	}
    }
    return VALUES_1(accumulation);
}

/* QUANTITY-ACCUMULATION-FOR-SPARSE-MAX */
Object quantity_accumulation_for_sparse_max(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object element_value, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float;
    double aref_new_value, arg, arg_1;

    x_note_fn_call(187,172);
    element_value = get_quantity_element(value_array,j);
    if ( !TRUEP(accumulation)) {
	Result_index = j;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    temp_1 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    else {
		temp = Available_float_array_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
		temp = Available_float_array_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    }
	    M_CDR(amf_available_array_cons_qm) = Nil;
	    amf_result = amf_array;
	}
	else {
	    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		    FIX((SI_Long)1L));
	    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	accumulation = new_float;
    }
    else {
	arg = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	arg_1 = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L);
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    Result_index = j;
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element_value);
	    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
	}
    }
    return VALUES_1(accumulation);
}

/* QUANTITY-ACCUMULATION-FOR-SPARSE-SUM */
Object quantity_accumulation_for_sparse_sum(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object element_value;
    double temp, aref_new_value;

    x_note_fn_call(187,173);
    element_value = get_quantity_element(value_array,j);
    temp = DOUBLE_FLOAT_TO_DOUBLE(element_value);
    aref_new_value = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L) + temp;
    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
    return VALUES_1(accumulation);
}

/* QUANTITY-ACCUMULATION-FOR-SPARSE-SUM-ABS */
Object quantity_accumulation_for_sparse_sum_abs(accumulation,value_array,j)
    Object accumulation, value_array, j;
{
    Object element_value;
    double temp, aref_new_value;

    x_note_fn_call(187,174);
    element_value = get_quantity_element(value_array,j);
    temp = DOUBLE_FLOAT_TO_DOUBLE(element_value);
    aref_new_value = DFLOAT_ISAREF_1(accumulation,(SI_Long)0L) + ABS(temp);
    DFLOAT_ISASET_1(accumulation,(SI_Long)0L,aref_new_value);
    return VALUES_1(accumulation);
}

/* ACCUMULATE-SPARSE-VALUES */
Object accumulate_sparse_values(value_array,initial_value_qm,update_function)
    Object value_array, initial_value_qm, update_function;
{
    Object l, accumulation, result_index, managed_array;
    SI_Long j, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(187,175);
    l = ISVREF(value_array,(SI_Long)20L);
    if ( !(IFIX(l) > (SI_Long)0L))
	zero_length_sparse_vector_error(value_array);
    accumulation = initial_value_qm;
    result_index = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Result_index,Qresult_index,result_index,0);
      managed_array = ISVREF(value_array,(SI_Long)23L);
      j = (SI_Long)0L;
      ab_loop_bind_ = IFIX(l);
    next_loop:
      if (j >= ab_loop_bind_)
	  goto end_loop;
      accumulation = inline_funcall_3(update_function,accumulation,
	      managed_array,FIX(j));
      j = j + (SI_Long)1L;
      goto next_loop;
    end_loop:
      result = VALUES_2(accumulation,Result_index);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* ACCUMULATE-QUANTITY-SPARSE-VALUES */
Object accumulate_quantity_sparse_values(value_array,initial_value_qm,
	    update_function)
    Object value_array, initial_value_qm, update_function;
{
    Object l, accumulation, result_index, managed_array, j, n_minus_1, temp;
    Object end_value_of_j;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,176);
    l = ISVREF(value_array,(SI_Long)20L);
    if ( !(IFIX(l) > (SI_Long)0L))
	zero_length_sparse_vector_error(value_array);
    accumulation = initial_value_qm;
    result_index = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Result_index,Qresult_index,result_index,0);
      managed_array = ISVREF(value_array,(SI_Long)23L);
      j = FIX((SI_Long)0L);
    next_loop:
      n_minus_1 = FIXNUM_SUB1(l);
      temp = FIXNUM_ADD(j,Max_number_of_array_elements_to_do);
      end_value_of_j = FIXNUM_MIN(n_minus_1,temp);
      if (FIXNUM_GT(j,n_minus_1)) {
	  result = VALUES_1(Nil);
	  goto end_1;
      }
      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	next_loop_1:
	  accumulation = inline_funcall_3(update_function,accumulation,
		  managed_array,j);
	  if (FIXNUM_GE(j,n_minus_1)) {
	      j = Nil;
	      goto end_2;
	  }
	  if (FIXNUM_EQ(j,end_value_of_j)) {
	      j = end_value_of_j;
	      goto end_2;
	  }
	  j = FIXNUM_ADD1(j);
	  goto next_loop_1;
	end_loop:
	  j = Qnil;
	end_2:;
      }
      POP_LOCAL_ALLOCATION(0,0);
      if ( !TRUEP(j))
	  goto end_loop_1;
      goto next_loop;
    end_loop_1:
      result = VALUES_2(accumulation,Result_index);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qinteger_accumulation_for_sparse_min;  /* integer-accumulation-for-sparse-min */

/* G2-INTEGER-SPARSE-MIN */
Object g2_integer_sparse_min(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,177);
    result = accumulate_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_min));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qinteger_accumulation_for_sparse_max;  /* integer-accumulation-for-sparse-max */

/* G2-INTEGER-SPARSE-MAX */
Object g2_integer_sparse_max(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,178);
    result = accumulate_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_max));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qinteger_accumulation_for_sparse_sum;  /* integer-accumulation-for-sparse-sum */

/* G2-INTEGER-SPARSE-SUM */
Object g2_integer_sparse_sum(value_array)
    Object value_array;
{
    x_note_fn_call(187,179);
    return accumulate_sparse_values(value_array,FIX((SI_Long)0L),
	    SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_sum));
}

static Object Qinteger_accumulation_for_sparse_sum_abs;  /* integer-accumulation-for-sparse-sum-abs */

/* G2-INTEGER-SPARSE-SUM-ABS */
Object g2_integer_sparse_sum_abs(value_array)
    Object value_array;
{
    x_note_fn_call(187,180);
    return accumulate_sparse_values(value_array,FIX((SI_Long)0L),
	    SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_sum_abs));
}

static Object Qfloat_accumulation_for_sparse_min;  /* float-accumulation-for-sparse-min */

/* G2-FLOAT-SPARSE-MIN */
Object g2_float_sparse_min(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,181);
    result = accumulate_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_min));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qfloat_accumulation_for_sparse_max;  /* float-accumulation-for-sparse-max */

/* G2-FLOAT-SPARSE-MAX */
Object g2_float_sparse_max(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,182);
    result = accumulate_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_max));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qfloat_accumulation_for_sparse_sum;  /* float-accumulation-for-sparse-sum */

/* G2-FLOAT-SPARSE-SUM */
Object g2_float_sparse_sum(value_array)
    Object value_array;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(187,183);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    return accumulate_sparse_values(value_array,new_float,
	    SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_sum));
}

static Object Qfloat_accumulation_for_sparse_sum_abs;  /* float-accumulation-for-sparse-sum-abs */

/* G2-FLOAT-SPARSE-SUM-ABS */
Object g2_float_sparse_sum_abs(value_array)
    Object value_array;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(187,184);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    return accumulate_sparse_values(value_array,new_float,
	    SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_sum_abs));
}

static Object Qquantity_accumulation_for_sparse_min;  /* quantity-accumulation-for-sparse-min */

/* G2-QUANTITY-SPARSE-MIN */
Object g2_quantity_sparse_min(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,185);
    result = accumulate_quantity_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_min));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qquantity_accumulation_for_sparse_max;  /* quantity-accumulation-for-sparse-max */

/* G2-QUANTITY-SPARSE-MAX */
Object g2_quantity_sparse_max(value_array)
    Object value_array;
{
    Object result_1, index_1;
    Object result;

    x_note_fn_call(187,186);
    result = accumulate_quantity_sparse_values(value_array,Nil,
	    SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_max));
    MVS_2(result,result_1,index_1);
    return VALUES_2(result_1,index_1);
}

static Object Qquantity_accumulation_for_sparse_sum;  /* quantity-accumulation-for-sparse-sum */

/* G2-QUANTITY-SPARSE-SUM */
Object g2_quantity_sparse_sum(value_array)
    Object value_array;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(187,187);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    return accumulate_quantity_sparse_values(value_array,new_float,
	    SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_sum));
}

static Object Qquantity_accumulation_for_sparse_sum_abs;  /* quantity-accumulation-for-sparse-sum-abs */

/* G2-QUANTITY-SPARSE-SUM-ABS */
Object g2_quantity_sparse_sum_abs(value_array)
    Object value_array;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;

    x_note_fn_call(187,188);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	M_CDR(amf_available_array_cons_qm) = Nil;
	amf_result = amf_array;
    }
    else {
	atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
		FIX((SI_Long)1L));
	atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
		bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
	amf_result = generate_float_vector(FIX((SI_Long)1L));
    }
    new_float = amf_result;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
    return accumulate_quantity_sparse_values(value_array,new_float,
	    SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_sum_abs));
}

static Object Qg2_integer_sparse_min;  /* g2-integer-sparse-min */

static Object Qg2_float_sparse_min;  /* g2-float-sparse-min */

static Object Qg2_quantity_sparse_min;  /* g2-quantity-sparse-min */

/* G2-ARRAY-MIN */
Object g2_array_min(value_array)
    Object value_array;
{
    x_note_fn_call(187,189);
    return execute_sparse_vector_operation_according_to_type(value_array,
	    SYMBOL_FUNCTION(Qg2_integer_sparse_min),
	    SYMBOL_FUNCTION(Qg2_float_sparse_min),
	    SYMBOL_FUNCTION(Qg2_quantity_sparse_min));
}

static Object Qg2_integer_sparse_max;  /* g2-integer-sparse-max */

static Object Qg2_float_sparse_max;  /* g2-float-sparse-max */

static Object Qg2_quantity_sparse_max;  /* g2-quantity-sparse-max */

/* G2-ARRAY-MAX */
Object g2_array_max(value_array)
    Object value_array;
{
    x_note_fn_call(187,190);
    return execute_sparse_vector_operation_according_to_type(value_array,
	    SYMBOL_FUNCTION(Qg2_integer_sparse_max),
	    SYMBOL_FUNCTION(Qg2_float_sparse_max),
	    SYMBOL_FUNCTION(Qg2_quantity_sparse_max));
}

static Object Qg2_integer_sparse_sum;  /* g2-integer-sparse-sum */

static Object Qg2_float_sparse_sum;  /* g2-float-sparse-sum */

static Object Qg2_quantity_sparse_sum;  /* g2-quantity-sparse-sum */

/* G2-ARRAY-SUM */
Object g2_array_sum(value_array)
    Object value_array;
{
    x_note_fn_call(187,191);
    return execute_sparse_vector_operation_according_to_type(value_array,
	    SYMBOL_FUNCTION(Qg2_integer_sparse_sum),
	    SYMBOL_FUNCTION(Qg2_float_sparse_sum),
	    SYMBOL_FUNCTION(Qg2_quantity_sparse_sum));
}

static Object Qg2_integer_sparse_sum_abs;  /* g2-integer-sparse-sum-abs */

static Object Qg2_float_sparse_sum_abs;  /* g2-float-sparse-sum-abs */

static Object Qg2_quantity_sparse_sum_abs;  /* g2-quantity-sparse-sum-abs */

/* G2-ARRAY-SUM-ABS */
Object g2_array_sum_abs(value_array)
    Object value_array;
{
    x_note_fn_call(187,192);
    return execute_sparse_vector_operation_according_to_type(value_array,
	    SYMBOL_FUNCTION(Qg2_integer_sparse_sum_abs),
	    SYMBOL_FUNCTION(Qg2_float_sparse_sum_abs),
	    SYMBOL_FUNCTION(Qg2_quantity_sparse_sum_abs));
}

static Object string_constant_39;  /* "~a must be an integer, quantity or float array" */

/* EXECUTE-SPARSE-VECTOR-OPERATION-ACCORDING-TO-TYPE */
Object execute_sparse_vector_operation_according_to_type(value_array,
	    integer_case_function,float_case_function,quantity_case_function)
    Object value_array, integer_case_function, float_case_function;
    Object quantity_case_function;
{
    Object value, index_1, sub_class_bit_vector, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,193);
    value = Nil;
    index_1 = Nil;
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	if (temp) {
	    result = inline_funcall_1(integer_case_function,value_array);
	    MVS_2(result,value,index_1);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		result = inline_funcall_1(float_case_function,value_array);
		MVS_2(result,value,index_1);
	    }
	    else {
		sub_class_bit_vector = ISVREF(ISVREF(value_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Quantity_array_class_description,
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
		if (temp) {
		    result = inline_funcall_1(quantity_case_function,
			    value_array);
		    MVS_2(result,value,index_1);
		}
		else {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(2,
			    string_constant_39,value_array);
		    raw_stack_error_named_error(top_of_stack,message_1);
		}
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_2(value,index_1);
}

static Object string_constant_40;  /* "value-array and index-arraymust all  arrays" */

static Object string_constant_41;  /* "Index must be an integer" */

/* G2-SPARSE-GET */
Object g2_sparse_get(value_array,index_array,index_1)
    Object value_array, index_array, index_1;
{
    Object sub_class_bit_vector, top_of_stack, message_1, index_managed_array;
    Object integer_array_qm, float_array_qm, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, j, ab_loop_bind_;
    char temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,194);
    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(index_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_40);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !FIXNUMP(index_1)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_41);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	index_1 = evaluation_value_value(index_1);
	index_managed_array = ISVREF(index_array,(SI_Long)23L);
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Integer_array_class_description,(SI_Long)18L));
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
	    integer_array_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    integer_array_qm = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_array_class_description,(SI_Long)18L));
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
	    float_array_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    float_array_qm = Nil;
	j = (SI_Long)0L;
	ab_loop_bind_ = IFIX(check_array_lengths_compatible(2,value_array,
		index_array));
      next_loop:
	if (j >= ab_loop_bind_)
	    goto end_loop;
	if (FIXNUM_EQ(FIXNUM_LE(ISVREF(index_managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(index_managed_array,
		j + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(index_managed_array,(j >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),j & (SI_Long)1023L),index_1)) {
	    if (integer_array_qm) {
		if (FIXNUM_LE(ISVREF(ISVREF(value_array,(SI_Long)23L),
			(SI_Long)1L),Maximum_in_place_array_size))
		    result = VALUES_1(ISVREF(ISVREF(value_array,
			    (SI_Long)23L),j + 
			    IFIX(Managed_array_index_offset)));
		else
		    result = VALUES_1(ISVREF(ISVREF(ISVREF(value_array,
			    (SI_Long)23L),(j >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),j & (SI_Long)1023L));
		goto end_1;
	    }
	    else if (float_array_qm) {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    M_CDR(amf_available_array_cons_qm) = Nil;
		    amf_result = amf_array;
		}
		else {
		    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			    FIX((SI_Long)1L));
		    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		    amf_result = generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		aref_new_value = DFLOAT_ISAREF_1(ISVREF(ISVREF(value_array,
			(SI_Long)23L),(j >>  -  - (SI_Long)10L) + 
			(SI_Long)2L),j & (SI_Long)1023L);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		result = VALUES_1(new_float);
		goto end_1;
	    }
	    else {
		amf_available_array_cons_qm = 
			ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
		if (amf_available_array_cons_qm) {
		    amf_array = M_CAR(amf_available_array_cons_qm);
		    temp_1 = Vector_of_simple_float_array_pools;
		    temp_2 = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qfloat_array);
		    if (ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_1 = 
				ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_1) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    else {
			temp_1 = Available_float_array_conses_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
			temp_1 = Available_float_array_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    }
		    M_CDR(amf_available_array_cons_qm) = Nil;
		    amf_result = amf_array;
		}
		else {
		    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			    FIX((SI_Long)1L));
		    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		    amf_result = generate_float_vector(FIX((SI_Long)1L));
		}
		new_float = amf_result;
		temp_3 = get_quantity_element(ISVREF(value_array,
			(SI_Long)23L),FIX(j));
		aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_3);
		DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		result = VALUES_1(new_float);
		goto end_1;
	    }
	}
	j = j + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (integer_array_qm)
	    result = VALUES_1(FIX((SI_Long)0L));
	else if (float_array_qm) {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_1 = Vector_of_simple_float_array_pools;
		temp_2 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		else {
		    temp_1 = Available_float_array_conses_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		    temp_1 = Available_float_array_conses_tail_vector;
		    temp_2 = Current_thread_index;
		    SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		}
		M_CDR(amf_available_array_cons_qm) = Nil;
		amf_result = amf_array;
	    }
	    else {
		atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
			FIX((SI_Long)1L));
		atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
			bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
		amf_result = generate_float_vector(FIX((SI_Long)1L));
	    }
	    new_float = amf_result;
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	    result = VALUES_1(new_float);
	}
	else
	    result = make_evaluation_quantity(FIX((SI_Long)0L));
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object string_constant_42;  /* "g2-sparse-set requires a quantity not ~a" */

static Object string_constant_43;  /* "The provided index ~a is not a positive integer" */

static Object string_constant_44;  /* "Both the value and the index arrays must be arrays" */

static Object string_constant_45;  /* "Both the value and the index arrays must have non-zero length" */

static Object string_constant_46;  /* "Trying to put a non integer value ~a into an integer array " */

/* G2-SPARSE-SET */
Object g2_sparse_set(value_array,index_array,value,index_1)
    Object value_array, index_array, value, index_1;
{
    Object current_sparse_length, index_managed_array, value_of_value;
    Object sparse_index, index_value, top_of_stack, message_1;
    Object sub_class_bit_vector, temp_1, svref_arg_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, i, ab_loop_bind_, temp_2;
    char temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(187,195);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_sparse_length = Nil;
	index_managed_array = Nil;
	value_of_value = Nil;
	sparse_index = Nil;
	index_value = Nil;
	index_value = evaluation_value_value(index_1);
	if ( !(FIXNUMP(value) || INLINE_DOUBLE_FLOAT_VECTOR_P(value) != 
		(SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == 
		(SI_Long)1L || INLINE_LONG_VECTOR_P(value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_42,evaluation_value_value(value));
	    result = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else if ( !FIXNUMP(index_value) || minusp(index_value)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_43,index_value);
	    result = raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(value_array,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(index_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_array_class_description,(SI_Long)18L));
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
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_44);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else if (IFIX(ISVREF(value_array,(SI_Long)20L)) == (SI_Long)0L 
		    || IFIX(ISVREF(index_array,(SI_Long)20L)) == (SI_Long)0L) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(1,
			string_constant_45);
		result = raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    else {
		current_sparse_length = check_array_lengths_compatible(2,
			value_array,index_array);
		value_of_value = evaluation_value_value(value);
		index_managed_array = ISVREF(index_array,(SI_Long)23L);
		reclaim_evaluation_value(value);
		reclaim_evaluation_value(index_1);
		i = (SI_Long)0L;
		ab_loop_bind_ = IFIX(current_sparse_length);
	      next_loop:
		if (i >= ab_loop_bind_)
		    goto end_loop;
		if (FIXNUM_EQ(FIXNUM_LE(ISVREF(index_managed_array,
			(SI_Long)1L),Maximum_in_place_array_size) ? 
			ISVREF(index_managed_array,i + 
			IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(index_managed_array,(i >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),i & (SI_Long)1023L),
			index_1)) {
		    sparse_index = FIX(i);
		    goto end_1;
		}
		i = i + (SI_Long)1L;
		goto next_loop;
	      end_loop:
		sparse_index = current_sparse_length;
		change_sparse_vector_length(value_array,index_array,
			FIXNUM_ADD1(sparse_index));
		if (FIXNUM_LE(ISVREF(ISVREF(index_array,(SI_Long)23L),
			(SI_Long)1L),Maximum_in_place_array_size)) {
		    temp_1 = ISVREF(index_array,(SI_Long)23L);
		    svref_arg_2 = FIXNUM_ADD(sparse_index,
			    Managed_array_index_offset);
		    SVREF(temp_1,svref_arg_2) = index_value;
		}
		else {
		    temp_1 = ISVREF(ISVREF(index_array,(SI_Long)23L),
			    (IFIX(sparse_index) >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L);
		    temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
		    ISVREF(temp_1,temp_2) = index_value;
		}
	      end_1:;
		sub_class_bit_vector = ISVREF(ISVREF(value_array,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Integer_array_class_description,
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
		if (temp) {
		    if (FIXNUMP(value_of_value)) {
			if (FIXNUM_LE(ISVREF(ISVREF(value_array,
				(SI_Long)23L),(SI_Long)1L),
				Maximum_in_place_array_size)) {
			    temp_1 = ISVREF(value_array,(SI_Long)23L);
			    svref_arg_2 = FIXNUM_ADD(sparse_index,
				    Managed_array_index_offset);
			    result = VALUES_1(SVREF(temp_1,svref_arg_2) = 
				    value_of_value);
			}
			else {
			    temp_1 = ISVREF(ISVREF(value_array,
				    (SI_Long)23L),(IFIX(sparse_index) >>  
				    -  - (SI_Long)10L) + (SI_Long)2L);
			    temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
			    result = VALUES_1(ISVREF(temp_1,temp_2) = 
				    value_of_value);
			}
		    }
		    else {
			top_of_stack = Cached_top_of_stack;
			message_1 = tformat_stack_error_text_string(2,
				string_constant_46,value_of_value);
			result = raw_stack_error_named_error(top_of_stack,
				message_1);
		    }
		}
		else {
		    sub_class_bit_vector = ISVREF(ISVREF(value_array,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Float_array_class_description,
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
		    if (temp) {
			temp_1 = ISVREF(ISVREF(value_array,(SI_Long)23L),
				(IFIX(sparse_index) >>  -  - (SI_Long)10L) 
				+ (SI_Long)2L);
			temp_2 = IFIX(sparse_index) & (SI_Long)1023L;
			if (FIXNUMP(value_of_value)) {
			    temp_3 = lfloat(value_of_value,float_constant);
			    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_3);
			}
			else
			    aref_new_value = 
				    DOUBLE_FLOAT_TO_DOUBLE(value_of_value);
			DFLOAT_ISASET_1(temp_1,temp_2,aref_new_value);
			result = VALUES_1(Nil);
		    }
		    else
			result = set_quantity_element(ISVREF(value_array,
				(SI_Long)23L),sparse_index,value_of_value);
		}
	    }
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

void simulate5_INIT()
{
    Object temp, temp_1, temp_2, gensymed_symbol;
    Object Qg2_sparse_set, Qfunction_keeps_procedure_environment_valid_qm;
    Object AB_package, Qg2_sparse_get, Qg2_array_sum_abs, Qg2_array_sum;
    Object Qg2_array_max, Qg2_array_min, Qg2_sparse_multiply, Qg2_sparse_add;
    Object Qg2_sparse_gather, Qg2_sparse_scatter;
    Object Qg2_matrix_to_matrix_multiply, Qg2_initialize_matrix_multiply;
    Object Qg2_matrix_vector_to_vector_multiply, Qg2_scalar_multiply;
    Object Qg2_array_multiply, Qg2_transpose_row;
    Object Qg2_initialize_matrix_transpose, Qg2_vector_equal;
    Object Qg2_initialize_matrix_equal, Qg2_vector_copy;
    Object Qg2_initialize_matrix_copy, Qg2_vector_substract;
    Object Qg2_vector_add_new, Qg2_vector_add, Qsimulate5;
    Object Qg2_initialize_matrix_add, Qg2_lu_backward_substitute_row;
    Object Qg2_lu_forward_substitute_row, Qg2_initialize_lubksb, Qg2_lu_crout;
    Object Qg2_lu_compute_scaling, Qg2_initialize_lu_decompose;
    Object Qget_current_model_definition, Qget_model_simulation_time_increment;
    Object Qset_model_simulation_time_increment, Qget_model_simulation_time;
    Object Qset_model_simulation_time, Qresume_model, Qpause_model;
    Object Qreset_model, Qstart_model, Qslot_putter;
    Object Qput_external_simulator_configuration, Qput_simulator_on_qm;
    Object Qput_simulation_procedure, Qclasses_which_define;
    Object Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_simulation_parameters;
    Object Qinstall_system_table;
    Object Qinstall_system_table_for_simulation_parameters;
    Object Qput_external_simulator_configuration_for_model;
    Object Qput_simulation_procedure_for_model;
    Object Qput_items_belonging_to_this_model;
    Object Qmodel_definitions_for_item_or_class;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_model_definition, Qinitialize;
    Object Qinitialize_for_model_definition;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qitem_designations_for_model, Qslot_value_compiler;
    Object Qcompile_item_designations_for_model_for_slot, string_constant_63;
    Object string_constant_62, Qsimplify_associative_operation;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qrestart_simulator_after_procedure, Qslot_value_reclaimer;
    Object Qreclaim_model_runtime_info_qm_value, Qmodel_runtime_info_qm;
    Object Qcleanup, Qcleanup_for_model_definition;
    Object Qinitialize_simulation_control_specifications;
    Object Qinitialize_default_simulation_time_increment_for_model;
    Object Qput_integration_algorithm_for_model;
    Object Qsend_all_values_at_beginning_of_cycle, Qintegration_algorithm;
    Object Qdefault_simulation_time_increment, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object list_constant, Qinitialize_model_runtime_info;
    Object Qcreate_icon_description, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47, Qentity;

    x_note_fn_call(187,196);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qmodel_definition = STATIC_SYMBOL("MODEL-DEFINITION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qmodel_definition,list_constant);
    string_constant_47 = STATIC_STRING("1m1m8v837Dy1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    Qinitialize_model_runtime_info = 
	    STATIC_SYMBOL("INITIALIZE-MODEL-RUNTIME-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_model_runtime_info,
	    STATIC_FUNCTION(initialize_model_runtime_info,NIL,TRUE,0,1));
    Qinitialize_default_simulation_time_increment_for_model = 
	    STATIC_SYMBOL("INITIALIZE-DEFAULT-SIMULATION-TIME-INCREMENT-FOR-MODEL",
	    AB_package);
    Qinitialize_simulation_control_specifications = 
	    STATIC_SYMBOL("INITIALIZE-SIMULATION-CONTROL-SPECIFICATIONS",
	    AB_package);
    string_constant_48 = 
	    STATIC_STRING("1z4z8r83--y83--y837Dy837Dy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_49 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_50 = 
	    STATIC_STRING("0004z8r83-0y83-0y837Dy837Dy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_51 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u837Dy837Dy01p8w9k3uy3uy1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1p83Jy1mll1m3tyl1m3ty3ty1ml3ty");
    string_constant_52 = 
	    STATIC_STRING("1q83Oy1mu3ky1muu1m3Qy3ay1m3kyu1m3ky3ky001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83Voy83Voy837Dy83");
    string_constant_53 = 
	    STATIC_STRING("7Dy01m83*Ay9l001m1l8l1l8o000004z8r83T-y83T-y837Dy837Dy00001m1n8p83D9y83Gy1l8l000004z8r83Bgy83Bgy837Dy837Dy01m83*Ay9m001n1l8l1l8z");
    string_constant_54 = 
	    STATIC_STRING("1m8p832iy000004z8r83D=y83D=y837Dy837Dy0833uy001n1l8l1l8z1m8p833Py000004z8r83L4y83L4y837Dy837Dy00001m1l8l1n8p834vy83Gy000004z8r83");
    string_constant_55 = 
	    STATIC_STRING("F4y83F4y837Dy837Dy00001n1l8l1l8z1m8p8306y000004z8r83Exy83Exy837Dy837Dy00001n1l8l1l8z1m8p83Ky000004z8r83dqy83dqy837Dy837Dy00001l1");
    string_constant_56 = 
	    STATIC_STRING("l8l000004z8r83duy83duy837Dy837Dy00001l1l8l000004z8r83aHy83aHy837Dy837Dy00001m1l8l1l8o000004z8r83Vpy83Vpy837Dy837Dy083WZy001o1l8l");
    string_constant_57 = 
	    STATIC_STRING("1l83Fy1m8p83-qy1l83Hy000004z8r83F1y83F1y837Dy837Dy01m83*Ay9n001n1l8l1l8z1m8p839xy00000");
    string_constant_58 = 
	    STATIC_STRING("13Dy8q1o837Dy1m83Ry83-+y1m8v837Dy8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1m8u1p8w9k3uy3uy1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1p83Jy1mll1");
    string_constant_59 = 
	    STATIC_STRING("m3tyl1m3ty3ty1ml3ty1q83Oy1mu3ky1muu1m3Qy3ay1m3kyu1m3ky3ky1o83Voy1m83*Ay9l8l8o1o83T-y01n8p83D9y83Gy8l1p83Bgy1m83*Ay9m8l8z1m8p832i");
    string_constant_60 = 
	    STATIC_STRING("y1p83D=y833uy8l8z1m8p833Py1o83L4y08l1n8p834vy83Gy1p83F4y08l8z1m8p8306y1p83Exy08l8z1m8p83Ky1n83dqy08l1n83duy08l1o83aHy08l8o1p83Vp");
    string_constant_61 = 
	    STATIC_STRING("y83WZy83Fy1m8p83-qy83Hy1p83F1y1m83*Ay9n8l8z1m8p839xy");
    temp = regenerate_optimized_constant(string_constant_47);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qinitialize_model_runtime_info);
    push_optimized_constant(Qinitialize_default_simulation_time_increment_for_model);
    push_optimized_constant(Qinitialize_simulation_control_specifications);
    temp_1 = regenerate_optimized_constant(list(10,string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51,
	    string_constant_52,string_constant_53,string_constant_54,
	    string_constant_55,string_constant_56,string_constant_57));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    push_optimized_constant(Qinitialize_model_runtime_info);
    push_optimized_constant(Qinitialize_default_simulation_time_increment_for_model);
    push_optimized_constant(Qinitialize_simulation_control_specifications);
    add_class_to_environment(9,Qmodel_definition,list_constant,Nil,temp,
	    Nil,temp_1,list_constant,
	    regenerate_optimized_constant(LIST_4(string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61)),Nil);
    Model_definition_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmodel_definition,
	    Class_description_gkbprop);
    Qdefault_simulation_time_increment_for_model = 
	    STATIC_SYMBOL("DEFAULT-SIMULATION-TIME-INCREMENT-FOR-MODEL",
	    AB_package);
    Qdefault_simulation_time_increment = 
	    STATIC_SYMBOL("DEFAULT-SIMULATION-TIME-INCREMENT",AB_package);
    alias_slot_name(3,Qdefault_simulation_time_increment_for_model,
	    Qdefault_simulation_time_increment,Qmodel_definition);
    Qintegration_algorithm_for_model = 
	    STATIC_SYMBOL("INTEGRATION-ALGORITHM-FOR-MODEL",AB_package);
    Qintegration_algorithm = STATIC_SYMBOL("INTEGRATION-ALGORITHM",AB_package);
    alias_slot_name(3,Qintegration_algorithm_for_model,
	    Qintegration_algorithm,Qmodel_definition);
    Qexternal_simulator_configuration_for_model = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATOR-CONFIGURATION-FOR-MODEL",
	    AB_package);
    Qexternal_simulator_configuration = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATOR-CONFIGURATION",AB_package);
    alias_slot_name(3,Qexternal_simulator_configuration_for_model,
	    Qexternal_simulator_configuration,Qmodel_definition);
    Qsimulation_procedure_for_model = 
	    STATIC_SYMBOL("SIMULATION-PROCEDURE-FOR-MODEL",AB_package);
    Qsimulation_procedure = STATIC_SYMBOL("SIMULATION-PROCEDURE",AB_package);
    alias_slot_name(3,Qsimulation_procedure_for_model,
	    Qsimulation_procedure,Qmodel_definition);
    Qsend_all_values_at_beginning_of_cycle_for_model_qm = 
	    STATIC_SYMBOL("SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE-FOR-MODEL\?",
	    AB_package);
    Qsend_all_values_at_beginning_of_cycle = 
	    STATIC_SYMBOL("SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE",AB_package);
    alias_slot_name(3,Qsend_all_values_at_beginning_of_cycle_for_model_qm,
	    Qsend_all_values_at_beginning_of_cycle,Qmodel_definition);
    Qrk4 = STATIC_SYMBOL("RK4",AB_package);
    Qput_integration_algorithm_for_model = 
	    STATIC_SYMBOL("PUT-INTEGRATION-ALGORITHM-FOR-MODEL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_integration_algorithm_for_model,
	    STATIC_FUNCTION(put_integration_algorithm_for_model,NIL,FALSE,
	    3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qintegration_algorithm_for_model,
	    SYMBOL_FUNCTION(Qput_integration_algorithm_for_model),
	    Qslot_putter);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_default_simulation_time_increment_for_model,
	    STATIC_FUNCTION(initialize_default_simulation_time_increment_for_model,
	    NIL,FALSE,0,0));
    Qsynchronously = STATIC_SYMBOL("SYNCHRONOUSLY",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_simulation_control_specifications,
	    STATIC_FUNCTION(initialize_simulation_control_specifications,
	    NIL,FALSE,0,0));
    Qmodel_simulation_status = STATIC_SYMBOL("MODEL-SIMULATION-STATUS",
	    AB_package);
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    Qitems_belonging_to_this_model = 
	    STATIC_SYMBOL("ITEMS-BELONGING-TO-THIS-MODEL",AB_package);
    Qcleanup_for_model_definition = 
	    STATIC_SYMBOL("CLEANUP-FOR-MODEL-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_model_definition,
	    STATIC_FUNCTION(cleanup_for_model_definition,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_model_definition);
    set_get(Qmodel_definition,Qcleanup,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodel_definition,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qmodel_runtime_info_qm = STATIC_SYMBOL("MODEL-RUNTIME-INFO\?",AB_package);
    Qreclaim_model_runtime_info_qm_value = 
	    STATIC_SYMBOL("RECLAIM-MODEL-RUNTIME-INFO\?-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_model_runtime_info_qm_value,
	    STATIC_FUNCTION(reclaim_model_runtime_info_qm_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qmodel_runtime_info_qm,
	    SYMBOL_FUNCTION(Qreclaim_model_runtime_info_qm_value),
	    Qslot_value_reclaimer);
    Qsimulation_control_specifications = 
	    STATIC_SYMBOL("SIMULATION-CONTROL-SPECIFICATIONS",AB_package);
    Qas_fast_as_possible = STATIC_SYMBOL("AS-FAST-AS-POSSIBLE",AB_package);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qvector_from_external_simulator_for_model = 
	    STATIC_SYMBOL("VECTOR-FROM-EXTERNAL-SIMULATOR-FOR-MODEL",
	    AB_package);
    Qvector_to_external_simulator_for_model = 
	    STATIC_SYMBOL("VECTOR-TO-EXTERNAL-SIMULATOR-FOR-MODEL",AB_package);
    Qvector_from_external_simulator = 
	    STATIC_SYMBOL("VECTOR-FROM-EXTERNAL-SIMULATOR",AB_package);
    Qvector_to_external_simulator = 
	    STATIC_SYMBOL("VECTOR-TO-EXTERNAL-SIMULATOR",AB_package);
    Qrestart_simulator_after_procedure = 
	    STATIC_SYMBOL("RESTART-SIMULATOR-AFTER-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qrestart_simulator_after_procedure,
	    STATIC_FUNCTION(restart_simulator_after_procedure,NIL,FALSE,1,1));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qsimulate = STATIC_SYMBOL("SIMULATE",AB_package);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_62 = 
	    STATIC_STRING("1s1n83D9y83-b9yl1o83D9y1n83-b9y1m9k83vy83D9y1nmln9l1m83-b9y839Wy1m83-b9y83-xQy1n83-b9y1m1m9k83=by83-Gy2l83-Gym1n83-b9y1o1m9k83=b");
    string_constant_63 = 
	    STATIC_STRING("y83-Gy1m9k83-Fsy83-xQy1n83-Gymo1m83-xQy83eWy1n83-xQy1m1m9k837Zy1m9k83*qy1l83noy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_62,
	    string_constant_63)));
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qitem_designations_for_model = 
	    STATIC_SYMBOL("ITEM-DESIGNATIONS-FOR-MODEL",AB_package);
    Qcompile_item_designations_for_model_for_slot = 
	    STATIC_SYMBOL("COMPILE-ITEM-DESIGNATIONS-FOR-MODEL-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_item_designations_for_model_for_slot,
	    STATIC_FUNCTION(compile_item_designations_for_model_for_slot,
	    NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qitem_designations_for_model,
	    SYMBOL_FUNCTION(Qcompile_item_designations_for_model_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qitem_designations_for_model,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmodels_used_p = STATIC_SYMBOL("MODELS-USED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmodels_used_p,Models_used_p);
    Qsimulate5 = STATIC_SYMBOL("SIMULATE5",AB_package);
    record_system_variable(Qmodels_used_p,Qsimulate5,Nil,Qnil,Qt,Qnil,Qt);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qinitialize_for_model_definition = 
	    STATIC_SYMBOL("INITIALIZE-FOR-MODEL-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_model_definition,
	    STATIC_FUNCTION(initialize_for_model_definition,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_model_definition);
    set_get(Qmodel_definition,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodel_definition,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qinitialize_after_reading_for_model_definition = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-MODEL-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_model_definition,
	    STATIC_FUNCTION(initialize_after_reading_for_model_definition,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_model_definition);
    set_get(Qmodel_definition,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qmodel_definition,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qmodel_definitions_for_item_or_class = 
	    STATIC_SYMBOL("MODEL-DEFINITIONS-FOR-ITEM-OR-CLASS",AB_package);
    Kb_specific_property_names = CONS(Qmodel_definitions_for_item_or_class,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qmodel_definitions_for_item_or_class,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Model_definitions_for_item_or_class_kbprop = 
	    Qmodel_definitions_for_item_or_class;
    Qput_items_belonging_to_this_model = 
	    STATIC_SYMBOL("PUT-ITEMS-BELONGING-TO-THIS-MODEL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_items_belonging_to_this_model,
	    STATIC_FUNCTION(put_items_belonging_to_this_model,NIL,FALSE,3,3));
    mutate_global_property(Qitems_belonging_to_this_model,
	    SYMBOL_FUNCTION(Qput_items_belonging_to_this_model),Qslot_putter);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    if (Install_item_in_model_if_appropriate == UNBOUND)
	Install_item_in_model_if_appropriate = Nil;
    Qinstall_item_in_model_if_appropriate = 
	    STATIC_SYMBOL("INSTALL-ITEM-IN-MODEL-IF-APPROPRIATE",AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_item_in_model_if_appropriate,
	    STATIC_FUNCTION(install_item_in_model_if_appropriate,NIL,FALSE,
	    3,3));
    SET_SYMBOL_VALUE_LOCATION(Qinstall_item_in_model_if_appropriate,
	    Install_item_in_model_if_appropriate);
    Install_item_in_model_if_appropriate = 
	    SYMBOL_FUNCTION(Qinstall_item_in_model_if_appropriate);
    Qexternal_simulation_definition_for_entity = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION-FOR-ENTITY",
	    AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qput_simulation_procedure_for_model = 
	    STATIC_SYMBOL("PUT-SIMULATION-PROCEDURE-FOR-MODEL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_procedure_for_model,
	    STATIC_FUNCTION(put_simulation_procedure_for_model,NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_procedure_for_model,
	    SYMBOL_FUNCTION(Qput_simulation_procedure_for_model),Qslot_putter);
    Qput_external_simulator_configuration_for_model = 
	    STATIC_SYMBOL("PUT-EXTERNAL-SIMULATOR-CONFIGURATION-FOR-MODEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_external_simulator_configuration_for_model,
	    STATIC_FUNCTION(put_external_simulator_configuration_for_model,
	    NIL,FALSE,3,3));
    mutate_global_property(Qexternal_simulator_configuration_for_model,
	    SYMBOL_FUNCTION(Qput_external_simulator_configuration_for_model),
	    Qslot_putter);
    Qinstall_system_table_for_simulation_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-SIMULATION-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_simulation_parameters,
	    STATIC_FUNCTION(install_system_table_for_simulation_parameters,
	    NIL,FALSE,1,1));
    Qsimulation_parameters = STATIC_SYMBOL("SIMULATION-PARAMETERS",AB_package);
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_simulation_parameters);
    set_get(Qsimulation_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qsimulation_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_simulation_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-SIMULATION-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_simulation_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_simulation_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qdeinstall_system_table_for_simulation_parameters);
    set_get(Qsimulation_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qsimulation_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    string_constant = 
	    STATIC_STRING("Ignoring the request to turn on the simulator found in the simulation-parameters.  The current G2 license does not include this feature.");
    Qput_simulation_procedure = STATIC_SYMBOL("PUT-SIMULATION-PROCEDURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_procedure,
	    STATIC_FUNCTION(put_simulation_procedure,NIL,FALSE,3,3));
    mutate_global_property(Qsimulation_procedure,
	    SYMBOL_FUNCTION(Qput_simulation_procedure),Qslot_putter);
    Qsimulator_on_qm = STATIC_SYMBOL("SIMULATOR-ON\?",AB_package);
    Qput_simulator_on_qm = STATIC_SYMBOL("PUT-SIMULATOR-ON\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulator_on_qm,
	    STATIC_FUNCTION(put_simulator_on_qm,NIL,FALSE,3,3));
    mutate_global_property(Qsimulator_on_qm,
	    SYMBOL_FUNCTION(Qput_simulator_on_qm),Qslot_putter);
    Qput_external_simulator_configuration = 
	    STATIC_SYMBOL("PUT-EXTERNAL-SIMULATOR-CONFIGURATION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_external_simulator_configuration,
	    STATIC_FUNCTION(put_external_simulator_configuration,NIL,FALSE,
	    3,3));
    mutate_global_property(Qexternal_simulator_configuration,
	    SYMBOL_FUNCTION(Qput_external_simulator_configuration),
	    Qslot_putter);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qnothing_to_simulate = STATIC_SYMBOL("NOTHING-TO-SIMULATE",AB_package);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    Qneeds_to_be_shutdown = STATIC_SYMBOL("NEEDS-TO-BE-SHUTDOWN",AB_package);
    Qneeds_to_be_initialized = STATIC_SYMBOL("NEEDS-TO-BE-INITIALIZED",
	    AB_package);
    Qclear_simulation_history_at_runtime = 
	    STATIC_SYMBOL("CLEAR-SIMULATION-HISTORY-AT-RUNTIME",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_simulation_history_at_runtime,
	    STATIC_FUNCTION(clear_simulation_history_at_runtime,NIL,FALSE,
	    1,1));
    Qadjust_simulation_history_at_runtime_if_necessary = 
	    STATIC_SYMBOL("ADJUST-SIMULATION-HISTORY-AT-RUNTIME-IF-NECESSARY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadjust_simulation_history_at_runtime_if_necessary,
	    STATIC_FUNCTION(adjust_simulation_history_at_runtime_if_necessary,
	    NIL,FALSE,1,1));
    Qstart_model = STATIC_SYMBOL("START-MODEL",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qstart_model,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qstart_model,STATIC_FUNCTION(start_model,NIL,FALSE,
	    1,1));
    Qreset_model = STATIC_SYMBOL("RESET-MODEL",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qreset_model,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qnot_running = STATIC_SYMBOL("NOT-RUNNING",AB_package);
    SET_SYMBOL_FUNCTION(Qreset_model,STATIC_FUNCTION(reset_model,NIL,FALSE,
	    1,1));
    Qpause_model = STATIC_SYMBOL("PAUSE-MODEL",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qpause_model,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qpause_model,STATIC_FUNCTION(pause_model,NIL,FALSE,
	    1,1));
    Qresume_model = STATIC_SYMBOL("RESUME-MODEL",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qresume_model,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qresume_model,STATIC_FUNCTION(resume_model,NIL,
	    FALSE,1,1));
    Qset_model_simulation_time = STATIC_SYMBOL("SET-MODEL-SIMULATION-TIME",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qset_model_simulation_time,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    float_constant = STATIC_FLOAT(0.0);
    SET_SYMBOL_FUNCTION(Qset_model_simulation_time,
	    STATIC_FUNCTION(set_model_simulation_time,NIL,FALSE,2,2));
    Qget_model_simulation_time = STATIC_SYMBOL("GET-MODEL-SIMULATION-TIME",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_model_simulation_time,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qget_model_simulation_time,
	    STATIC_FUNCTION(get_model_simulation_time,NIL,FALSE,1,1));
    Qset_model_simulation_time_increment = 
	    STATIC_SYMBOL("SET-MODEL-SIMULATION-TIME-INCREMENT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qset_model_simulation_time_increment,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qset_model_simulation_time_increment,
	    STATIC_FUNCTION(set_model_simulation_time_increment,NIL,FALSE,
	    2,2));
    Qget_model_simulation_time_increment = 
	    STATIC_SYMBOL("GET-MODEL-SIMULATION-TIME-INCREMENT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_model_simulation_time_increment,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_1 = 
	    STATIC_STRING("The model ~NF has no variables whose time increments are the one ~\n            specified in the model definition.");
    SET_SYMBOL_FUNCTION(Qget_model_simulation_time_increment,
	    STATIC_FUNCTION(get_model_simulation_time_increment,NIL,FALSE,
	    1,1));
    Qget_current_model_definition = 
	    STATIC_SYMBOL("GET-CURRENT-MODEL-DEFINITION",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qget_current_model_definition,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_2 = STATIC_STRING("There is no current simulator model");
    SET_SYMBOL_FUNCTION(Qget_current_model_definition,
	    STATIC_FUNCTION(get_current_model_definition,NIL,FALSE,0,0));
    Qg2_initialize_lu_decompose = 
	    STATIC_SYMBOL("G2-INITIALIZE-LU-DECOMPOSE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_lu_decompose,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_lu_decompose,
	    STATIC_FUNCTION(g2_initialize_lu_decompose,NIL,FALSE,3,3));
    Qg2_lu_compute_scaling = STATIC_SYMBOL("G2-LU-COMPUTE-SCALING",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lu_compute_scaling,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lu_compute_scaling,
	    STATIC_FUNCTION(g2_lu_compute_scaling,NIL,FALSE,5,5));
    string_constant_3 = 
	    STATIC_STRING("The MATRIX ~NF is singular and therefore cannot be lu decomposed.~\n                       The singularity is due to the fact that row ~a contains all zeroes.");
    Qg2_lu_crout = STATIC_SYMBOL("G2-LU-CROUT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lu_crout,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lu_crout,STATIC_FUNCTION(g2_lu_crout,NIL,FALSE,
	    5,5));
    string_constant_4 = 
	    STATIC_STRING("Singularity encountered in row ~a while lu decomposing the MATRIX ~NF.");
    Qg2_initialize_lubksb = STATIC_SYMBOL("G2-INITIALIZE-LUBKSB",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_lubksb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_lubksb,
	    STATIC_FUNCTION(g2_initialize_lubksb,NIL,FALSE,4,4));
    Qg2_lu_forward_substitute_row = 
	    STATIC_SYMBOL("G2-LU-FORWARD-SUBSTITUTE-ROW",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lu_forward_substitute_row,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lu_forward_substitute_row,
	    STATIC_FUNCTION(g2_lu_forward_substitute_row,NIL,FALSE,5,5));
    Qg2_lu_backward_substitute_row = 
	    STATIC_SYMBOL("G2-LU-BACKWARD-SUBSTITUTE-ROW",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lu_backward_substitute_row,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lu_backward_substitute_row,
	    STATIC_FUNCTION(g2_lu_backward_substitute_row,NIL,FALSE,3,3));
    string_constant_5 = 
	    STATIC_STRING("A row of the MATRIX ~NF was not an active float array with length >= ~a, ~\n         the required minimum length for the matrix operation being attempted.");
    string_constant_6 = 
	    STATIC_STRING("The index array ~NF is not >= ~a, ~\n       the required minimum length for the matrix operation being attempted.");
    string_constant_7 = 
	    STATIC_STRING("The b vector ~NF is not >= ~a, ~\n        the required minimum length for the matrix operation being attempted.");
    string_constant_8 = 
	    STATIC_STRING("The x vector ~NF is not >= ~a, ~\n        the required minimum length for the matrix operation being attempted.");
    string_constant_9 = 
	    STATIC_STRING("The array ~NF is not the same length as the array ~NF.");
    string_constant_10 = 
	    STATIC_STRING("The specified index ~d is outside the range 0 to ~d.");
    string_constant_11 = 
	    STATIC_STRING("The array ~NF does not have the required length ~d");
    string_constant_12 = 
	    STATIC_STRING("The range array ~NF does not have the required length 4.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_13 = 
	    STATIC_STRING("The matrix ~NF contains an empty row.");
    string_constant_14 = 
	    STATIC_STRING("The matrix ~NF contains a row which is not an item.");
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    string_constant_15 = 
	    STATIC_STRING("The array ~NF is not a subclass of quantity-array and is therefore ~\n       not suitable as a row of the MATRIX ~NF.");
    string_constant_16 = 
	    STATIC_STRING("The array ~NF is not of type ~a and is therefore ~\n         not compatible with other rows of the MATRIX ~NF.");
    string_constant_17 = 
	    STATIC_STRING("The length of array ~NF is ~a which is different ~\n         from other rows of the MATRIX ~NF.");
    Qg2_initialize_matrix_add = STATIC_SYMBOL("G2-INITIALIZE-MATRIX-ADD",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_matrix_add,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_matrix_add,
	    STATIC_FUNCTION(g2_initialize_matrix_add,NIL,FALSE,3,3));
    Qsubtract_arrays_instead_qm = 
	    STATIC_SYMBOL("SUBTRACT-ARRAYS-INSTEAD\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsubtract_arrays_instead_qm,
	    Subtract_arrays_instead_qm);
    record_system_variable(Qsubtract_arrays_instead_qm,Qsimulate5,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qg2_vector_add = STATIC_SYMBOL("G2-VECTOR-ADD",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_vector_add,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_18 = 
	    STATIC_STRING("All arrays must be of non-zero length");
    string_constant_19 = STATIC_STRING("a row add");
    SET_SYMBOL_FUNCTION(Qg2_vector_add,STATIC_FUNCTION(g2_vector_add,NIL,
	    FALSE,4,4));
    Max_number_of_array_elements_to_do = FIX((SI_Long)500L);
    Qg2_vector_add_new = STATIC_SYMBOL("G2-VECTOR-ADD-NEW",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_vector_add_new,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_vector_add_new,
	    STATIC_FUNCTION(g2_vector_add_new,NIL,FALSE,3,3));
    Qg2_vector_substract = STATIC_SYMBOL("G2-VECTOR-SUBSTRACT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_vector_substract,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_vector_substract,
	    STATIC_FUNCTION(g2_vector_substract,NIL,FALSE,3,3));
    Qg2_initialize_matrix_copy = STATIC_SYMBOL("G2-INITIALIZE-MATRIX-COPY",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_matrix_copy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_20 = 
	    STATIC_STRING("The elements of item-arrays given to g2-array-copy must be quantity-arrays.");
    SET_SYMBOL_FUNCTION(Qg2_initialize_matrix_copy,
	    STATIC_FUNCTION(g2_initialize_matrix_copy,NIL,FALSE,2,2));
    Qg2_vector_copy = STATIC_SYMBOL("G2-VECTOR-COPY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_vector_copy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_21 = STATIC_STRING("a row copy");
    SET_SYMBOL_FUNCTION(Qg2_vector_copy,STATIC_FUNCTION(g2_vector_copy,NIL,
	    FALSE,2,2));
    Qg2_initialize_matrix_equal = 
	    STATIC_SYMBOL("G2-INITIALIZE-MATRIX-EQUAL",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_matrix_equal,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_matrix_equal,
	    STATIC_FUNCTION(g2_initialize_matrix_equal,NIL,FALSE,2,2));
    Qg2_vector_equal = STATIC_SYMBOL("G2-VECTOR-EQUAL",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_vector_equal,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_22 = STATIC_STRING("an equal test");
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_vector_equal,STATIC_FUNCTION(g2_vector_equal,
	    NIL,FALSE,2,2));
    Qg2_initialize_matrix_transpose = 
	    STATIC_SYMBOL("G2-INITIALIZE-MATRIX-TRANSPOSE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_matrix_transpose,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_matrix_transpose,
	    STATIC_FUNCTION(g2_initialize_matrix_transpose,NIL,FALSE,2,2));
    Qg2_transpose_row = STATIC_SYMBOL("G2-TRANSPOSE-ROW",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_transpose_row,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_transpose_row,STATIC_FUNCTION(g2_transpose_row,
	    NIL,FALSE,7,7));
    Qg2_array_multiply = STATIC_SYMBOL("G2-ARRAY-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_array_multiply,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_array_multiply,
	    STATIC_FUNCTION(g2_array_multiply,NIL,FALSE,2,2));
    Qg2_scalar_multiply = STATIC_SYMBOL("G2-SCALAR-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_scalar_multiply,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_scalar_multiply,
	    STATIC_FUNCTION(g2_scalar_multiply,NIL,FALSE,3,3));
    Qg2_matrix_vector_to_vector_multiply = 
	    STATIC_SYMBOL("G2-MATRIX-VECTOR-TO-VECTOR-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_matrix_vector_to_vector_multiply,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_matrix_vector_to_vector_multiply,
	    STATIC_FUNCTION(g2_matrix_vector_to_vector_multiply,NIL,FALSE,
	    4,4));
    Qg2_initialize_matrix_multiply = 
	    STATIC_SYMBOL("G2-INITIALIZE-MATRIX-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_initialize_matrix_multiply,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_initialize_matrix_multiply,
	    STATIC_FUNCTION(g2_initialize_matrix_multiply,NIL,FALSE,3,3));
    Qg2_matrix_to_matrix_multiply = 
	    STATIC_SYMBOL("G2-MATRIX-TO-MATRIX-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_matrix_to_matrix_multiply,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_matrix_to_matrix_multiply,
	    STATIC_FUNCTION(g2_matrix_to_matrix_multiply,NIL,FALSE,6,6));
    string_constant_23 = 
	    STATIC_STRING("Error attempting ~a on an array which does not exist.  ");
    string_constant_24 = 
	    STATIC_STRING("Error attempting ~a on something which is not an array.  ");
    string_constant_25 = 
	    STATIC_STRING("Please check system procedure arguments, and contents of arguments.");
    string_constant_26 = STATIC_STRING("and");
    string_constant_27 = STATIC_STRING(" are not compatible for ~a.");
    Qg2_array_copy = STATIC_SYMBOL("G2-ARRAY-COPY",AB_package);
    string_constant_28 = STATIC_STRING("a row multiply");
    float_constant_1 = STATIC_FLOAT(0.5);
    Qg2_sparse_scatter = STATIC_SYMBOL("G2-SPARSE-SCATTER",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_scatter,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_29 = 
	    STATIC_STRING("The begin index and end index must both be integers");
    string_constant_30 = 
	    STATIC_STRING("The value and index arrays must both be arrays");
    string_constant_31 = 
	    STATIC_STRING("The end-index ~a must be greater than the begin-index ~a");
    SET_SYMBOL_FUNCTION(Qg2_sparse_scatter,
	    STATIC_FUNCTION(g2_sparse_scatter,NIL,FALSE,5,5));
    Qg2_sparse_gather = STATIC_SYMBOL("G2-SPARSE-GATHER",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_gather,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_32 = 
	    STATIC_STRING("Values cannot be automatically converted from ~NF to ~NF");
    string_constant_33 = 
	    STATIC_STRING("The value,index and full arrays must all be arrays");
    SET_SYMBOL_FUNCTION(Qg2_sparse_gather,STATIC_FUNCTION(g2_sparse_gather,
	    NIL,FALSE,3,3));
    Qg2_sparse_add = STATIC_SYMBOL("G2-SPARSE-ADD",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_add,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_34 = 
	    STATIC_STRING("value-array-1, index-array-1, value-array-2, index-array-2 and full array must all be arrays");
    SET_SYMBOL_FUNCTION(Qg2_sparse_add,STATIC_FUNCTION(g2_sparse_add,NIL,
	    FALSE,8,8));
    Qg2_sparse_multiply = STATIC_SYMBOL("G2-SPARSE-MULTIPLY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_multiply,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_sparse_multiply,
	    STATIC_FUNCTION(g2_sparse_multiply,NIL,FALSE,7,7));
    Default_min_to_extend_sparse_vector = FIX((SI_Long)20L);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    string_constant_35 = 
	    STATIC_STRING("The index ~d for the packed vector is greater than the maximum index ~d for the array ~NF.");
    string_constant_36 = 
	    STATIC_STRING("The index ~d for the packed vector is negative");
    string_constant_37 = 
	    STATIC_STRING("~a is not a valid value for an integer array ");
    string_constant_38 = 
	    STATIC_STRING("The value vector ~NF is of length 0 and is therefore not suitable for the current operation.");
    Qinteger_accumulation_for_sparse_min = 
	    STATIC_SYMBOL("INTEGER-ACCUMULATION-FOR-SPARSE-MIN",AB_package);
    SET_SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_min,
	    STATIC_FUNCTION(integer_accumulation_for_sparse_min,NIL,FALSE,
	    3,3));
    Qinteger_accumulation_for_sparse_max = 
	    STATIC_SYMBOL("INTEGER-ACCUMULATION-FOR-SPARSE-MAX",AB_package);
    SET_SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_max,
	    STATIC_FUNCTION(integer_accumulation_for_sparse_max,NIL,FALSE,
	    3,3));
    Qinteger_accumulation_for_sparse_sum = 
	    STATIC_SYMBOL("INTEGER-ACCUMULATION-FOR-SPARSE-SUM",AB_package);
    SET_SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_sum,
	    STATIC_FUNCTION(integer_accumulation_for_sparse_sum,NIL,FALSE,
	    3,3));
    Qinteger_accumulation_for_sparse_sum_abs = 
	    STATIC_SYMBOL("INTEGER-ACCUMULATION-FOR-SPARSE-SUM-ABS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinteger_accumulation_for_sparse_sum_abs,
	    STATIC_FUNCTION(integer_accumulation_for_sparse_sum_abs,NIL,
	    FALSE,3,3));
    Qfloat_accumulation_for_sparse_min = 
	    STATIC_SYMBOL("FLOAT-ACCUMULATION-FOR-SPARSE-MIN",AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_min,
	    STATIC_FUNCTION(float_accumulation_for_sparse_min,NIL,FALSE,3,3));
    Qfloat_accumulation_for_sparse_max = 
	    STATIC_SYMBOL("FLOAT-ACCUMULATION-FOR-SPARSE-MAX",AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_max,
	    STATIC_FUNCTION(float_accumulation_for_sparse_max,NIL,FALSE,3,3));
    Qfloat_accumulation_for_sparse_sum = 
	    STATIC_SYMBOL("FLOAT-ACCUMULATION-FOR-SPARSE-SUM",AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_sum,
	    STATIC_FUNCTION(float_accumulation_for_sparse_sum,NIL,FALSE,3,3));
    Qfloat_accumulation_for_sparse_sum_abs = 
	    STATIC_SYMBOL("FLOAT-ACCUMULATION-FOR-SPARSE-SUM-ABS",AB_package);
    SET_SYMBOL_FUNCTION(Qfloat_accumulation_for_sparse_sum_abs,
	    STATIC_FUNCTION(float_accumulation_for_sparse_sum_abs,NIL,
	    FALSE,3,3));
    Qquantity_accumulation_for_sparse_min = 
	    STATIC_SYMBOL("QUANTITY-ACCUMULATION-FOR-SPARSE-MIN",AB_package);
    SET_SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_min,
	    STATIC_FUNCTION(quantity_accumulation_for_sparse_min,NIL,FALSE,
	    3,3));
    Qquantity_accumulation_for_sparse_max = 
	    STATIC_SYMBOL("QUANTITY-ACCUMULATION-FOR-SPARSE-MAX",AB_package);
    SET_SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_max,
	    STATIC_FUNCTION(quantity_accumulation_for_sparse_max,NIL,FALSE,
	    3,3));
    Qquantity_accumulation_for_sparse_sum = 
	    STATIC_SYMBOL("QUANTITY-ACCUMULATION-FOR-SPARSE-SUM",AB_package);
    SET_SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_sum,
	    STATIC_FUNCTION(quantity_accumulation_for_sparse_sum,NIL,FALSE,
	    3,3));
    Qquantity_accumulation_for_sparse_sum_abs = 
	    STATIC_SYMBOL("QUANTITY-ACCUMULATION-FOR-SPARSE-SUM-ABS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qquantity_accumulation_for_sparse_sum_abs,
	    STATIC_FUNCTION(quantity_accumulation_for_sparse_sum_abs,NIL,
	    FALSE,3,3));
    Qg2_array_min = STATIC_SYMBOL("G2-ARRAY-MIN",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_array_min,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_integer_sparse_min = STATIC_SYMBOL("G2-INTEGER-SPARSE-MIN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_integer_sparse_min,
	    STATIC_FUNCTION(g2_integer_sparse_min,NIL,FALSE,1,1));
    Qg2_float_sparse_min = STATIC_SYMBOL("G2-FLOAT-SPARSE-MIN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_float_sparse_min,
	    STATIC_FUNCTION(g2_float_sparse_min,NIL,FALSE,1,1));
    Qg2_quantity_sparse_min = STATIC_SYMBOL("G2-QUANTITY-SPARSE-MIN",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_quantity_sparse_min,
	    STATIC_FUNCTION(g2_quantity_sparse_min,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_array_min,STATIC_FUNCTION(g2_array_min,NIL,
	    FALSE,1,1));
    Qg2_array_max = STATIC_SYMBOL("G2-ARRAY-MAX",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_array_max,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_integer_sparse_max = STATIC_SYMBOL("G2-INTEGER-SPARSE-MAX",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_integer_sparse_max,
	    STATIC_FUNCTION(g2_integer_sparse_max,NIL,FALSE,1,1));
    Qg2_float_sparse_max = STATIC_SYMBOL("G2-FLOAT-SPARSE-MAX",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_float_sparse_max,
	    STATIC_FUNCTION(g2_float_sparse_max,NIL,FALSE,1,1));
    Qg2_quantity_sparse_max = STATIC_SYMBOL("G2-QUANTITY-SPARSE-MAX",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_quantity_sparse_max,
	    STATIC_FUNCTION(g2_quantity_sparse_max,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_array_max,STATIC_FUNCTION(g2_array_max,NIL,
	    FALSE,1,1));
    Qg2_array_sum = STATIC_SYMBOL("G2-ARRAY-SUM",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_array_sum,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_integer_sparse_sum = STATIC_SYMBOL("G2-INTEGER-SPARSE-SUM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_integer_sparse_sum,
	    STATIC_FUNCTION(g2_integer_sparse_sum,NIL,FALSE,1,1));
    Qg2_float_sparse_sum = STATIC_SYMBOL("G2-FLOAT-SPARSE-SUM",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_float_sparse_sum,
	    STATIC_FUNCTION(g2_float_sparse_sum,NIL,FALSE,1,1));
    Qg2_quantity_sparse_sum = STATIC_SYMBOL("G2-QUANTITY-SPARSE-SUM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_quantity_sparse_sum,
	    STATIC_FUNCTION(g2_quantity_sparse_sum,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_array_sum,STATIC_FUNCTION(g2_array_sum,NIL,
	    FALSE,1,1));
    Qg2_array_sum_abs = STATIC_SYMBOL("G2-ARRAY-SUM-ABS",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_array_sum_abs,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_integer_sparse_sum_abs = STATIC_SYMBOL("G2-INTEGER-SPARSE-SUM-ABS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_integer_sparse_sum_abs,
	    STATIC_FUNCTION(g2_integer_sparse_sum_abs,NIL,FALSE,1,1));
    Qg2_float_sparse_sum_abs = STATIC_SYMBOL("G2-FLOAT-SPARSE-SUM-ABS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qg2_float_sparse_sum_abs,
	    STATIC_FUNCTION(g2_float_sparse_sum_abs,NIL,FALSE,1,1));
    Qg2_quantity_sparse_sum_abs = 
	    STATIC_SYMBOL("G2-QUANTITY-SPARSE-SUM-ABS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_quantity_sparse_sum_abs,
	    STATIC_FUNCTION(g2_quantity_sparse_sum_abs,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_array_sum_abs,STATIC_FUNCTION(g2_array_sum_abs,
	    NIL,FALSE,1,1));
    string_constant_39 = 
	    STATIC_STRING("~a must be an integer, quantity or float array");
    Qg2_sparse_get = STATIC_SYMBOL("G2-SPARSE-GET",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_get,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_40 = 
	    STATIC_STRING("value-array and index-arraymust all  arrays");
    string_constant_41 = STATIC_STRING("Index must be an integer");
    SET_SYMBOL_FUNCTION(Qg2_sparse_get,STATIC_FUNCTION(g2_sparse_get,NIL,
	    FALSE,3,3));
    Qg2_sparse_set = STATIC_SYMBOL("G2-SPARSE-SET",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_sparse_set,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_42 = 
	    STATIC_STRING("g2-sparse-set requires a quantity not ~a");
    string_constant_43 = 
	    STATIC_STRING("The provided index ~a is not a positive integer");
    string_constant_44 = 
	    STATIC_STRING("Both the value and the index arrays must be arrays");
    string_constant_45 = 
	    STATIC_STRING("Both the value and the index arrays must have non-zero length");
    string_constant_46 = 
	    STATIC_STRING("Trying to put a non integer value ~a into an integer array ");
    SET_SYMBOL_FUNCTION(Qg2_sparse_set,STATIC_FUNCTION(g2_sparse_set,NIL,
	    FALSE,4,4));
}
