/* smrtsgnlxtnsn.c
 * Input file:  smartsignalextension.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "smrtsgnlxtnsn.h"


static Object Qlong;               /* long */

static Object string_constant;     /* "The history function ~a, which requires numeric data, ~
				    *                tried to use the history of the variable ~NF, which has a ~
				    *               non-numeric data type."
				    */

static Object Qlisp_g2nke_count_history_matching_op;  /* lisp-g2nke-count-history-matching-op */

static Object Qsimulation_details;  /* simulation-details */

/* LISP-G2NKE-COUNT-HISTORY-MATCHING-OP */
Object lisp_g2nke_count_history_matching_op(variable,
	    value_requested_by_simulator_qm,arg_n,arg_nstart,
	    arg_fellow_val,arg_requiredgoodsize,arg_compareoperator)
    Object variable, value_requested_by_simulator_qm, arg_n, arg_nstart;
    Object arg_fellow_val, arg_requiredgoodsize, arg_compareoperator;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(239,0);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant,
		Qlisp_g2nke_count_history_matching_op,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    return VALUES_1(g2nke_count_history_datapoints_matching_op(variable,
		    value_history_cascaded_ring_buffer,
		    value_history_ring_buffer_or_cascade,
		    value_requested_by_simulator_qm,
		    referencing_simulation_history_qm,arg_n,arg_nstart,
		    arg_fellow_val,arg_requiredgoodsize,arg_compareoperator));
	}
    }
}

static Object Qfloat_array;        /* float-array */

/* KB-G2NKE-COUNT-HISTORY-MATCHING-OP */
Object kb_g2nke_count_history_matching_op(arg_subj,arg_n,arg_nstart,
	    arg_fellow_val,arg_requiredgoodsize,arg_compareoperator)
    Object arg_subj, arg_n, arg_nstart, arg_fellow_val, arg_requiredgoodsize;
    Object arg_compareoperator;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double aref_new_value;

    x_note_fn_call(239,1);
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
    if (g2_enterprise_p()) {
	temp_2 = lisp_g2nke_count_history_matching_op(arg_subj,Nil,arg_n,
		arg_nstart,arg_fellow_val,arg_requiredgoodsize,
		arg_compareoperator);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    }
    else
	aref_new_value = 0.0;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* KB-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG */
Object kb_g2nke_count_history_matching_op_and_eventflag(arg_subj,arg_n,
	    arg_nstart,arg_fellow_val,arg_eventflag,arg_event_bit,
	    arg_requiredgoodsize,arg_compareoperator)
    Object arg_subj, arg_n, arg_nstart, arg_fellow_val, arg_eventflag;
    Object arg_event_bit, arg_requiredgoodsize, arg_compareoperator;
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;
    double aref_new_value;

    x_note_fn_call(239,2);
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
    if (g2_enterprise_p()) {
	temp_2 = 
		g2nke_count_history_datapoints_matching_op_and_eventflag(arg_subj,
		arg_n,arg_nstart,arg_fellow_val,arg_eventflag,
		arg_event_bit,arg_requiredgoodsize,arg_compareoperator);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    }
    else
	aref_new_value = 0.0;
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* C2-GET-TOTAL-LENGTH-OF-RING-BUFFER-OR-CASCADE */
Object c2_get_total_length_of_ring_buffer_or_cascade(ring_buffer_or_cascade)
    Object ring_buffer_or_cascade;
{
    Object ring_buffer, index_1, oldest_active_element_index_for_ring_buffer;

    x_note_fn_call(239,3);
    if (ISVREF(ring_buffer_or_cascade,(SI_Long)3L))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	ring_buffer = ring_buffer_or_cascade;
	index_1 = ISVREF(ring_buffer_or_cascade,(SI_Long)1L);
	oldest_active_element_index_for_ring_buffer = ISVREF(ring_buffer,
		(SI_Long)2L);
	if (FIXNUM_GE(index_1,oldest_active_element_index_for_ring_buffer))
	    return VALUES_1(FIXNUM_ADD1(FIXNUM_MINUS(index_1,
		    oldest_active_element_index_for_ring_buffer)));
	else
	    return VALUES_1(FIXNUM_ADD1(FIXNUM_MINUS(FIXNUM_ADD(index_1,
		    ISVREF(ring_buffer,(SI_Long)4L)),
		    oldest_active_element_index_for_ring_buffer)));
    }
}

static Object Qc2_get_history_spec;  /* c2-get-history-spec */

/* C2-GET-HISTORY-SPEC */
Object c2_get_history_spec(variable,value_requested_by_simulator_qm)
    Object variable, value_requested_by_simulator_qm;
{
    Object symbol, top_of_stack, message_1, history_being_kept_qm;
    Object referencing_simulation_history_qm, sub_class_bit_vector;
    Object simulation_subtable_qm, simulation_stored_histories_qm;
    Object value_history_cascaded_ring_buffer;
    Object variable_or_parameter_stored_histories_qm;
    Object value_history_ring_buffer_or_cascade, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(239,4);
    if (Nil) {
	symbol = ISVREF(variable,(SI_Long)20L);
	temp =  !(EQ(symbol,Qnumber) || EQ(symbol,Qinteger) || EQ(symbol,
		Qfloat) || EQ(symbol,Qlong) || 
		lookup_global_or_kb_specific_property_value(symbol,
		Numeric_data_type_gkbprop));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant,
		Qc2_get_history_spec,variable);
	raw_stack_error_named_error(top_of_stack,message_1);
	return VALUES_1(Nil);
    }
    else {
	history_being_kept_qm = Nil;
	referencing_simulation_history_qm = value_requested_by_simulator_qm;
	if (value_requested_by_simulator_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(variable,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	    simulation_subtable_qm = get_lookup_slot_value(variable,
		    Qsimulation_details);
	    simulation_stored_histories_qm = simulation_subtable_qm ? 
		    ISVREF(simulation_subtable_qm,(SI_Long)20L) : Nil;
	    history_being_kept_qm =  ! !(simulation_subtable_qm && 
		    ISVREF(simulation_subtable_qm,(SI_Long)21L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(simulation_stored_histories_qm) || 
		    cascaded_ring_buffer_empty_qm(simulation_stored_histories_qm) 
		    ? Nil : simulation_stored_histories_qm;
	}
	else {
	    variable_or_parameter_stored_histories_qm = ISVREF(variable,
		    (SI_Long)24L);
	    referencing_simulation_history_qm = Nil;
	    history_being_kept_qm =  ! !TRUEP(ISVREF(variable,
		    (SI_Long)25L)) ? T : Nil;
	    value_history_cascaded_ring_buffer =  
		    !TRUEP(history_being_kept_qm) ||  
		    !TRUEP(ISVREF(variable,(SI_Long)24L)) || 
		    cascaded_ring_buffer_empty_qm(variable_or_parameter_stored_histories_qm) 
		    ? Nil : variable_or_parameter_stored_histories_qm;
	}
	value_history_ring_buffer_or_cascade = Nil;
	if ( !TRUEP(value_history_cascaded_ring_buffer) && ( 
		!TRUEP(history_being_kept_qm) || T))
	    return VALUES_1(Nil);
	else {
	    if (value_history_cascaded_ring_buffer) {
		temp_1 = ISVREF(value_history_cascaded_ring_buffer,
			(SI_Long)4L);
		value_history_ring_buffer_or_cascade = CAR(temp_1);
	    }
	    else
		value_history_ring_buffer_or_cascade = Nil;
	    temp_1 = ISVREF(value_history_ring_buffer_or_cascade,(SI_Long)5L);
	    return VALUES_5(value_history_cascaded_ring_buffer,
		    value_history_ring_buffer_or_cascade,
		    value_requested_by_simulator_qm,
		    referencing_simulation_history_qm,temp_1);
	}
    }
}

void smartsignalextension_INIT()
{
    Object gensymed_symbol;
    Object AB_package, Qkb_g2nke_count_history_matching_op_and_eventflag;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qkb_g2nke_count_history_matching_op;

    x_note_fn_call(239,5);
    AB_package = STATIC_PACKAGE("AB");
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    string_constant = 
	    STATIC_STRING("The history function ~a, which requires numeric data, ~\n               tried to use the history of the variable ~NF, which has a ~\n              non-numeric data type.");
    Qlisp_g2nke_count_history_matching_op = 
	    STATIC_SYMBOL("LISP-G2NKE-COUNT-HISTORY-MATCHING-OP",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    SET_SYMBOL_FUNCTION(Qlisp_g2nke_count_history_matching_op,
	    STATIC_FUNCTION(lisp_g2nke_count_history_matching_op,NIL,FALSE,
	    7,7));
    Qkb_g2nke_count_history_matching_op = 
	    STATIC_SYMBOL("KB-G2NKE-COUNT-HISTORY-MATCHING-OP",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2nke_count_history_matching_op,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qkb_g2nke_count_history_matching_op,
	    STATIC_FUNCTION(kb_g2nke_count_history_matching_op,NIL,FALSE,6,6));
    Qkb_g2nke_count_history_matching_op_and_eventflag = 
	    STATIC_SYMBOL("KB-G2NKE-COUNT-HISTORY-MATCHING-OP-AND-EVENTFLAG",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qkb_g2nke_count_history_matching_op_and_eventflag,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qkb_g2nke_count_history_matching_op_and_eventflag,
	    STATIC_FUNCTION(kb_g2nke_count_history_matching_op_and_eventflag,
	    NIL,FALSE,8,8));
    Qc2_get_history_spec = STATIC_SYMBOL("C2-GET-HISTORY-SPEC",AB_package);
    SET_SYMBOL_FUNCTION(Qc2_get_history_spec,
	    STATIC_FUNCTION(c2_get_history_spec,NIL,FALSE,2,2));
}
