/* gspan.c
 * Input file:  gspan.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gspan.h"


DEFINE_VARIABLE_WITH_SYMBOL(Proceed_with_edit, Qproceed_with_edit);

Object External_simulation_definitions_for_attribute_kbprop = UNBOUND;

Object External_simulation_definition_for_class_kbprop = UNBOUND;

static Object string_constant;     /* "An external-simulation-definition may not be edited while the system is running or paused.  Please reset before editing an external-simulation-definition." */

/* OK-TO-EDIT-EXTERNAL-SIMULATION-DEFINITION? */
Object ok_to_edit_external_simulation_definition_qm()
{
    x_note_fn_call(219,0);
    if (System_is_running || System_has_paused) {
	if ( !TRUEP(Proceed_with_edit)) {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)2L <= IFIX(Warning_message_level))
		give_warning_1(2,FIX((SI_Long)2L),string_constant);
	    Suppress_warning_message_header_qm = Nil;
	}
	return VALUES_1(Proceed_with_edit);
    }
    else
	return VALUES_1(T);
}

static Object Qclass_of_object_computed_by_this;  /* class-of-object-computed-by-this */

/* PUT-CLASS-OF-OBJECT-COMPUTED-BY-THIS */
Object put_class_of_object_computed_by_this(external_simulation_definition,
	    class_1,initializing_qm)
    Object external_simulation_definition, class_1, initializing_qm;
{
    Object old_slot_value;

    x_note_fn_call(219,1);
    if (ok_to_edit_external_simulation_definition_qm()) {
	old_slot_value =  !TRUEP(initializing_qm) ? 
		ISVREF(external_simulation_definition,(SI_Long)20L) : Nil;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_simulation_definition,
		    Qclass_of_object_computed_by_this);
	SVREF(external_simulation_definition,FIX((SI_Long)20L)) = class_1;
	if (class_1)
	    return mutate_kb_specific_property_value(class_1,
		    external_simulation_definition,
		    External_simulation_definition_for_class_kbprop);
	else
	    return mutate_kb_specific_property_value(old_slot_value,Nil,
		    External_simulation_definition_for_class_kbprop);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinput_vector_to_external_simulator;  /* input-vector-to-external-simulator */

/* PUT-INPUT-VECTOR-TO-EXTERNAL-SIMULATOR */
Object put_input_vector_to_external_simulator(external_simulation_definition,
	    input_vector,gensymed_symbol)
    Object external_simulation_definition, input_vector, gensymed_symbol;
{
    x_note_fn_call(219,2);
    if (ok_to_edit_external_simulation_definition_qm()) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_simulation_definition,
		    Qinput_vector_to_external_simulator);
	return VALUES_1(SVREF(external_simulation_definition,
		FIX((SI_Long)22L)) = input_vector);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmessage_keywords;   /* message-keywords */

/* PUT-MESSAGE-KEYWORDS */
Object put_message_keywords(external_simulation_definition,
	    message_keywords,gensymed_symbol)
    Object external_simulation_definition, message_keywords, gensymed_symbol;
{
    x_note_fn_call(219,3);
    if (ok_to_edit_external_simulation_definition_qm()) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_simulation_definition,
		    Qmessage_keywords);
	return VALUES_1(SVREF(external_simulation_definition,
		FIX((SI_Long)21L)) = message_keywords);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinitialization_vector_for_external_simulator;  /* initialization-vector-for-external-simulator */

/* PUT-INITIALIZATION-VECTOR-FOR-EXTERNAL-SIMULATOR */
Object put_initialization_vector_for_external_simulator(external_simulation_definition,
	    initialization_vector,gensymed_symbol)
    Object external_simulation_definition, initialization_vector;
    Object gensymed_symbol;
{
    x_note_fn_call(219,4);
    if (ok_to_edit_external_simulation_definition_qm()) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_simulation_definition,
		    Qinitialization_vector_for_external_simulator);
	return VALUES_1(SVREF(external_simulation_definition,
		FIX((SI_Long)24L)) = initialization_vector);
    }
    else
	return VALUES_1(Nil);
}

static Object Qoutput_vector_from_external_simulator;  /* output-vector-from-external-simulator */

static Object Qincomplete;         /* incomplete */

/* PUT-OUTPUT-VECTOR-FROM-EXTERNAL-SIMULATOR */
Object put_output_vector_from_external_simulator(external_simulation_definition,
	    output_vector,initializing_qm)
    Object external_simulation_definition, output_vector, initializing_qm;
{
    Object old_frame_status_ok_qm, new_frame_status_ok_qm, old_slot_value;
    Object class_of_object, designations_to_remove, designations_to_add, temp;

    x_note_fn_call(219,5);
    if (ok_to_edit_external_simulation_definition_qm()) {
	old_frame_status_ok_qm = Nil;
	new_frame_status_ok_qm = Nil;
	old_slot_value = Nil;
	class_of_object = ISVREF(external_simulation_definition,(SI_Long)20L);
	designations_to_remove = Nil;
	designations_to_add = Nil;
	if ( !TRUEP(initializing_qm)) {
	    temp = ISVREF(external_simulation_definition,(SI_Long)8L);
	    old_frame_status_ok_qm =  !TRUEP(CAR(temp)) ? T : Nil;
	    old_slot_value = ISVREF(external_simulation_definition,
		    (SI_Long)23L);
	}
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(external_simulation_definition,
		    Qoutput_vector_from_external_simulator);
	SVREF(external_simulation_definition,FIX((SI_Long)23L)) = 
		output_vector;
	if ( !TRUEP(initializing_qm)) {
	    if (output_vector) {
		if (ISVREF(external_simulation_definition,(SI_Long)20L))
		    update_frame_status(external_simulation_definition,Nil,
			    Nil);
	    }
	    else
		update_frame_status(external_simulation_definition,
			Qincomplete,Nil);
	    temp = ISVREF(external_simulation_definition,(SI_Long)8L);
	    new_frame_status_ok_qm =  !TRUEP(CAR(temp)) ? ( !((SI_Long)0L 
		    != (IFIX(ISVREF(external_simulation_definition,
		    (SI_Long)5L)) & (SI_Long)512L)) ? T : Nil) : Nil;
	    if (old_frame_status_ok_qm && new_frame_status_ok_qm) {
		designations_to_remove = 
			get_missing_designations(CAR(old_slot_value),
			CAR(output_vector));
		designations_to_add = 
			get_missing_designations(CAR(output_vector),
			CAR(old_slot_value));
		if (designations_to_remove)
		    forward_external_simulation_install(external_simulation_definition,
			    class_of_object,designations_to_remove,T,T);
		if (designations_to_add)
		    forward_external_simulation_install(external_simulation_definition,
			    class_of_object,designations_to_add,Nil,T);
	    }
	    else if (old_frame_status_ok_qm) {
		designations_to_remove = 
			get_attribute_designations(CAR(old_slot_value));
		forward_external_simulation_install(external_simulation_definition,
			class_of_object,designations_to_remove,T,Nil);
	    }
	    else if (new_frame_status_ok_qm) {
		designations_to_add = 
			get_attribute_designations(CAR(output_vector));
		forward_external_simulation_install(external_simulation_definition,
			class_of_object,designations_to_add,Nil,Nil);
	    }
	    reclaim_simulate_list_1(designations_to_remove);
	    return reclaim_simulate_list_1(designations_to_add);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qexternal_simulation_definition;  /* external-simulation-definition */

/* INITIALIZE-FOR-EXTERNAL-SIMULATION-DEFINITION */
Object initialize_for_external_simulation_definition(external_simulation_definition)
    Object external_simulation_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(219,6);
    frame = external_simulation_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexternal_simulation_definition)) {
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
    update_frame_status(external_simulation_definition,
	    ISVREF(external_simulation_definition,(SI_Long)23L) && 
	    ISVREF(external_simulation_definition,(SI_Long)20L) ? Nil : 
	    Qincomplete,Nil);
    return install_new_external_simulation_definition(external_simulation_definition);
}

/* CLEANUP-FOR-EXTERNAL-SIMULATION-DEFINITION */
Object cleanup_for_external_simulation_definition(external_simulation_definition)
    Object external_simulation_definition;
{
    Object frame, sub_vector_qm, method_function_qm, proceed_with_edit;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(219,7);
    frame = external_simulation_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qexternal_simulation_definition)) {
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
    proceed_with_edit = T;
    PUSH_SPECIAL_WITH_SYMBOL(Proceed_with_edit,Qproceed_with_edit,proceed_with_edit,
	    0);
      change_slot_value(3,external_simulation_definition,
	      Qoutput_vector_from_external_simulator,Nil);
      result = change_slot_value(3,external_simulation_definition,
	      Qclass_of_object_computed_by_this,Nil);
    POP_SPECIAL();
    return result;
}

/* INSTALL-EXTERNAL-SIMULATION-1 */
Object install_external_simulation_1()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, definition;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(219,8);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qexternal_simulation_definition);
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
      definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      install_new_external_simulation_definition(definition);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* INSTALL-NEW-EXTERNAL-SIMULATION-DEFINITION */
Object install_new_external_simulation_definition(new_external_simulation_definition)
    Object new_external_simulation_definition;
{
    Object temp, designations_to_add;
    Object class_for_new_external_simulation_definition;

    x_note_fn_call(219,9);
    temp = ISVREF(new_external_simulation_definition,(SI_Long)8L);
    if ( !TRUEP(CAR(temp))) {
	temp = ISVREF(new_external_simulation_definition,(SI_Long)23L);
	designations_to_add = get_attribute_designations(CAR(temp));
	class_for_new_external_simulation_definition = 
		ISVREF(new_external_simulation_definition,(SI_Long)20L);
	if (class_for_new_external_simulation_definition)
	    forward_external_simulation_install(new_external_simulation_definition,
		    class_for_new_external_simulation_definition,
		    designations_to_add,Nil,Nil);
	return reclaim_simulate_list_1(designations_to_add);
    }
    else
	return VALUES_1(Nil);
}

/* INSTALL-EXTERNALLY-SIMULATED-ENTITY */
Object install_externally_simulated_entity varargs_1(int, n)
{
    Object entity;
    Object external_simulation_definition_being_edited_qm, designations_qm;
    Object deinstall_qm, incremental_qm, class_1, class_description;
    Object ab_loop_list_, external_simulation_definition_qm, temp;
    Object designations;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(219,10);
    INIT_ARGS_nonrelocating();
    entity = REQUIRED_ARG_nonrelocating();
    external_simulation_definition_being_edited_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    designations_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    deinstall_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    incremental_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    class_1 = Nil;
    class_description = ISVREF(entity,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
    external_simulation_definition_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    external_simulation_definition_qm = 
	    lookup_kb_specific_property_value(class_1,
	    External_simulation_definition_for_class_kbprop);
    if (external_simulation_definition_qm) {
	temp = ISVREF(external_simulation_definition_qm,(SI_Long)8L);
	temp_1 =  !TRUEP(CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !((SI_Long)0L != 
	    (IFIX(ISVREF(external_simulation_definition_qm,(SI_Long)5L)) & 
	    (SI_Long)512L)) : TRUEP(Nil)) {
	if (external_simulation_definition_being_edited_qm) {
	    if (EQ(external_simulation_definition_being_edited_qm,
		    external_simulation_definition_qm))
		install_externally_simulated_entity_1(entity,
			external_simulation_definition_qm,class_1,
			designations_qm,deinstall_qm,incremental_qm);
	}
	else {
	    temp = ISVREF(external_simulation_definition_qm,(SI_Long)23L);
	    designations = get_attribute_designations(CAR(temp));
	    install_externally_simulated_entity_1(entity,
		    external_simulation_definition_qm,class_1,designations,
		    deinstall_qm,incremental_qm);
	    reclaim_simulate_list_1(designations);
	}
	return VALUES_0();
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qexternal_simulation;  /* external-simulation */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qexternal_simulation_definition_for_entity;  /* external-simulation-definition-for-entity */

static Object string_constant_1;   /* "The object ~NF does not have an external simulation capability.  If this is ~
				    *         desired, add the external-simulation capability to the capabilities-and-~
				    *         restrictions attribute of ~a, the object definition for this object's class."
				    */

/* INSTALL-EXTERNALLY-SIMULATED-ENTITY-1 */
Object install_externally_simulated_entity_1(entity,
	    external_simulation_definition,class_1,designations,
	    deinstall_qm,incremental_qm)
    Object entity, external_simulation_definition, class_1, designations;
    Object deinstall_qm, incremental_qm;
{
    Object alist, current_computation_frame, current_computation_flags;
    Object designation, ab_loop_list_, output_variable_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector, current_model_runtime_info_qm;
    Object current_model_definition_qm, model_definition_for_item_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,11);
    if (get_property_value_in_object_configuration(entity,
	    Qexternal_simulation,Nil)) {
	alist = simulate_cons_1(simulate_cons_1(class_1,entity),Nil);
	current_computation_frame = external_simulation_definition;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		1);
	  current_computation_flags = Current_computation_flags;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    designation = Nil;
	    ab_loop_list_ = designations;
	    output_variable_qm = Nil;
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    output_variable_qm = evaluate_designation(designation,alist);
	    if (SIMPLE_VECTOR_P(output_variable_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_variable_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(output_variable_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(output_variable_qm,(SI_Long)1L);
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
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		install_externally_simulated_variable_1(output_variable_qm,
			external_simulation_definition,deinstall_qm);
	    goto next_loop;
	  end_loop:
	    reclaim_simulate_tree_1(alist);
	  POP_SPECIAL();
	POP_SPECIAL();
	if ( !TRUEP(incremental_qm)) {
	    if (deinstall_qm) {
		set_slot_value_function(entity,
			Qexternal_simulation_definition_for_entity,Nil,Nil);
		current_model_runtime_info_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
			1);
		  current_model_definition_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
			  0);
		    model_definition_for_item_qm = 
			    get_model_to_which_item_belongs(entity,T);
		    if (model_definition_for_item_qm) {
			Current_model_definition_qm = 
				model_definition_for_item_qm;
			Current_model_runtime_info_qm = 
				ISVREF(model_definition_for_item_qm,
				(SI_Long)20L);
		    }
		    else {
			Current_model_definition_qm = Nil;
			Current_model_runtime_info_qm = 
				Main_model_runtime_info;
		    }
		    result = remove_externally_simulated_entity_from_simulation_model(entity);
		  POP_SPECIAL();
		POP_SPECIAL();
		return result;
	    }
	    else {
		set_slot_value_function(entity,
			Qexternal_simulation_definition_for_entity,
			external_simulation_definition,Nil);
		make_external_set_pointers_if_necessary(entity);
		current_model_runtime_info_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
			1);
		  current_model_definition_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
			  0);
		    model_definition_for_item_qm = 
			    get_model_to_which_item_belongs(entity,T);
		    if (model_definition_for_item_qm) {
			Current_model_definition_qm = 
				model_definition_for_item_qm;
			Current_model_runtime_info_qm = 
				ISVREF(model_definition_for_item_qm,
				(SI_Long)20L);
		    }
		    else {
			Current_model_definition_qm = Nil;
			Current_model_runtime_info_qm = 
				Main_model_runtime_info;
		    }
		    result = add_externally_simulated_entity_to_simulation_model(entity);
		  POP_SPECIAL();
		POP_SPECIAL();
		return result;
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)2L),string_constant_1,entity,
		    ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L));
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
}

static Object Qsimulate;           /* simulate */

/* FORWARD-EXTERNAL-SIMULATION-INSTALL */
Object forward_external_simulation_install(external_simulation_definition,
	    class_1,designations,deinstall_qm,incremental_qm)
    Object external_simulation_definition, class_1, designations, deinstall_qm;
    Object incremental_qm;
{
    Object designation, ab_loop_list_, attribute, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, temp, svref_arg_2, temp_1;
    Object new_cons, svref_new_value, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object entity, super_class, class_description;
    Object external_simulation_definition_qm, super_class_designations;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(219,12);
    designation = Nil;
    ab_loop_list_ = designations;
    attribute = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute = get_attribute_of_attribute_designation(designation);
    if (deinstall_qm) {
	gensymed_symbol = external_simulation_definition;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = lookup_kb_specific_property_value(attribute,
		External_simulation_definitions_for_attribute_kbprop);
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_1;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp;
	    }
	    else
		mutate_kb_specific_property_value(attribute,
			CDR(gensymed_symbol_2),
			External_simulation_definitions_for_attribute_kbprop);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qsimulate);
	    if (ISVREF(Available_simulate_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_simulate_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp = Available_simulate_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
		temp = Available_simulate_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    goto end_1;
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    else {
	gensymed_symbol = lookup_kb_specific_property_value(attribute,
		External_simulation_definitions_for_attribute_kbprop);
	gensymed_symbol_1 = external_simulation_definition;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp_1 = attribute;
	    new_cons = ISVREF(Available_simulate_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp = Available_simulate_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_simulate_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp = Available_simulate_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_simulate_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qsimulate);
	    mutate_kb_specific_property_value(temp_1,gensymed_symbol_2,
		    External_simulation_definitions_for_attribute_kbprop);
	}
    }
    goto next_loop;
  end_loop:;
    if (incremental_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	entity = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(class_1);
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
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_3;
	  entity = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  install_externally_simulated_entity(5,entity,
		  external_simulation_definition,designations,deinstall_qm,
		  incremental_qm);
	  goto next_loop_2;
	end_loop_3:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else if (deinstall_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	entity = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(class_1);
	next_loop_4:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_5:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_4;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_4;
	      goto next_loop_5;
	    end_loop_4:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_5;
	  entity = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  install_externally_simulated_entity_1(entity,
		  external_simulation_definition,class_1,designations,
		  deinstall_qm,incremental_qm);
	  install_externally_simulated_entity(1,entity);
	  goto next_loop_4;
	end_loop_5:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else {
	mutate_kb_specific_property_value(class_1,Nil,
		External_simulation_definition_for_class_kbprop);
	super_class = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	temp_1 = ISVREF(class_description,(SI_Long)2L);
	ab_loop_list_ = CDR(temp_1);
	external_simulation_definition_qm = Nil;
      next_loop_6:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_6;
	super_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	external_simulation_definition_qm = 
		lookup_kb_specific_property_value(super_class,
		External_simulation_definition_for_class_kbprop);
	if (external_simulation_definition_qm) {
	    temp_1 = ISVREF(external_simulation_definition_qm,(SI_Long)8L);
	    temp_2 =  !TRUEP(CAR(temp_1));
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2) {
	    temp_1 = ISVREF(external_simulation_definition_qm,(SI_Long)23L);
	    super_class_designations = get_attribute_designations(CAR(temp_1));
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    entity = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(class_1);
	    next_loop_7:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_8:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_7;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_7;
		  goto next_loop_8;
		end_loop_7:
		  temp_2 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2)
		  goto end_loop_8;
	      entity = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      install_externally_simulated_entity(5,entity,
		      external_simulation_definition_qm,
		      super_class_designations,T,Nil);
	      goto next_loop_7;
	    end_loop_8:;
	    POP_SPECIAL();
	    reclaim_simulate_list_1(super_class_designations);
	    goto end_2;
	}
	goto next_loop_6;
      end_loop_6:
      end_2:;
	mutate_kb_specific_property_value(class_1,
		external_simulation_definition,
		External_simulation_definition_for_class_kbprop);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	entity = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(class_1);
	next_loop_9:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_10:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_9;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_9;
	      goto next_loop_10;
	    end_loop_9:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_10;
	  entity = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  install_externally_simulated_entity(5,entity,
		  external_simulation_definition,designations,deinstall_qm,
		  incremental_qm);
	  goto next_loop_9;
	end_loop_10:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
}

/* GET-CLASS-OF-ATTRIBUTE-DESIGNATION */
Object get_class_of_attribute_designation(attribute_designation)
    Object attribute_designation;
{
    x_note_fn_call(219,13);
    if ( !TRUEP(THIRD(attribute_designation)))
	return VALUES_1(SECOND(attribute_designation));
    else
	return get_class_of_attribute_designation(THIRD(attribute_designation));
}

/* GET-ATTRIBUTE-OF-ATTRIBUTE-DESIGNATION */
Object get_attribute_of_attribute_designation(attribute_designation)
    Object attribute_designation;
{
    x_note_fn_call(219,14);
    return VALUES_1(SECOND(attribute_designation));
}

/* GET-MISSING-DESIGNATIONS */
Object get_missing_designations(first_designation_or_designations,
	    second_designation_or_designations)
    Object first_designation_or_designations;
    Object second_designation_or_designations;
{
    Object missing_designations, designation, ab_loop_list_;

    x_note_fn_call(219,15);
    missing_designations = Nil;
    if (more_than_one_designation_in_vector_p(first_designation_or_designations)) 
		{
	designation = Nil;
	ab_loop_list_ = CDR(first_designation_or_designations);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (more_than_one_designation_in_vector_p(second_designation_or_designations)) 
		    {
	    if ( !TRUEP(member_equal(designation,
		    second_designation_or_designations)))
		missing_designations = simulate_cons_1(designation,
			missing_designations);
	}
	else if (at_least_one_designation_in_vector_p(second_designation_or_designations)) 
		    {
	    if ( !EQUAL(designation,second_designation_or_designations))
		missing_designations = simulate_cons_1(designation,
			missing_designations);
	}
	else
	    missing_designations = simulate_cons_1(designation,
		    missing_designations);
	goto next_loop;
      end_loop:;
    }
    else if (at_least_one_designation_in_vector_p(first_designation_or_designations)) 
		{
	if (more_than_one_designation_in_vector_p(second_designation_or_designations)) 
		    {
	    if ( !TRUEP(member_equal(first_designation_or_designations,
		    second_designation_or_designations)))
		missing_designations = 
			simulate_cons_1(first_designation_or_designations,
			missing_designations);
	}
	else if (at_least_one_designation_in_vector_p(second_designation_or_designations)) 
		    {
	    if ( !EQUAL(first_designation_or_designations,
		    second_designation_or_designations))
		missing_designations = 
			simulate_cons_1(first_designation_or_designations,
			missing_designations);
	}
	else
	    missing_designations = 
		    simulate_cons_1(first_designation_or_designations,
		    missing_designations);
    }
    return VALUES_1(missing_designations);
}

/* GET-ATTRIBUTE-DESIGNATIONS */
Object get_attribute_designations(designation_or_designations)
    Object designation_or_designations;
{
    x_note_fn_call(219,16);
    if (more_than_one_designation_in_vector_p(designation_or_designations))
	return copy_list_using_simulate_conses_1(CDR(designation_or_designations));
    else if (at_least_one_designation_in_vector_p(designation_or_designations))
	return simulate_cons_1(designation_or_designations,Nil);
    else
	return VALUES_1(Qnil);
}

/* INSTALL-EXTERNALLY-SIMULATED-VARIABLE */
Object install_externally_simulated_variable(variable)
    Object variable;
{
    Object external_simulation_definitions_for_variable_qm, definition;
    Object ab_loop_list_;

    x_note_fn_call(219,17);
    external_simulation_definitions_for_variable_qm = 
	    find_external_simulation_definitions_for_variable_if_any(variable);
    if (external_simulation_definitions_for_variable_qm) {
	definition = Nil;
	ab_loop_list_ = external_simulation_definitions_for_variable_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	definition = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	install_externally_simulated_variable_1(variable,definition,Nil);
	goto next_loop;
      end_loop:
	reclaim_simulate_list_1(external_simulation_definitions_for_variable_qm);
	return VALUES_1(Qnil);
    }
    else
	return install_externally_simulated_variable_1(variable,Nil,Nil);
}

/* FIND-EXTERNAL-SIMULATION-DEFINITIONS-FOR-VARIABLE-IF-ANY */
Object find_external_simulation_definitions_for_variable_if_any(variable)
    Object variable;
{
    Object parent_entity_qm, parent_attribute_qm;
    Object result;

    x_note_fn_call(219,18);
    result = get_kb_parent_information(variable);
    MVS_2(result,parent_entity_qm,parent_attribute_qm);
    if (parent_entity_qm)
	return find_external_simulation_definitions_for_variable_1(variable,
		parent_attribute_qm,parent_entity_qm,Nil);
    else
	return VALUES_1(Nil);
}

/* FIND-EXTERNAL-SIMULATION-DEFINITIONS-FOR-VARIABLE-1 */
Object find_external_simulation_definitions_for_variable_1(variable,
	    attribute,entity,external_simulation_definitions_so_far)
    Object variable, attribute, entity, external_simulation_definitions_so_far;
{
    Object external_simulation_definition_for_entity, temp, parent_entity_qm;

    x_note_fn_call(219,19);
    if (get_property_value_in_object_configuration(entity,
	    Qexternal_simulation,Nil)) {
	external_simulation_definition_for_entity = 
		get_slot_value_function(entity,
		Qexternal_simulation_definition_for_entity,Nil);
	if (memq_function(external_simulation_definition_for_entity,
		lookup_kb_specific_property_value(attribute,
		External_simulation_definitions_for_attribute_kbprop)) && 
		variable_simulated_by_external_simulation_definition_qm(variable,
		entity,external_simulation_definition_for_entity))
	    external_simulation_definitions_so_far = 
		    simulate_cons_1(external_simulation_definition_for_entity,
		    external_simulation_definitions_so_far);
    }
    temp = get_kb_parent_information(entity);
    parent_entity_qm = temp;
    if (parent_entity_qm)
	return find_external_simulation_definitions_for_variable_1(variable,
		attribute,parent_entity_qm,
		external_simulation_definitions_so_far);
    else
	return VALUES_1(external_simulation_definitions_so_far);
}

/* VARIABLE-SIMULATED-BY-EXTERNAL-SIMULATION-DEFINITION? */
Object variable_simulated_by_external_simulation_definition_qm(variable,
	    entity,external_simulation_definition)
    Object variable, entity, external_simulation_definition;
{
    Object temp, designations, designation, ab_loop_list_;

    x_note_fn_call(219,20);
    temp = ISVREF(external_simulation_definition,(SI_Long)8L);
    if ( !TRUEP(CAR(temp))) {
	temp = ISVREF(external_simulation_definition,(SI_Long)23L);
	designations = get_attribute_designations(CAR(temp));
	designation = Nil;
	ab_loop_list_ = designations;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (variable_designated_by_designation_qm(variable,designation,
		entity,external_simulation_definition)) {
	    reclaim_simulate_list_1(designations);
	    return VALUES_1(designation);
	}
	goto next_loop;
      end_loop:
	reclaim_simulate_list_1(designations);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* VARIABLE-DESIGNATED-BY-DESIGNATION? */
Object variable_designated_by_designation_qm(variable,designation,entity,
	    external_simulation_definition)
    Object variable, designation, entity, external_simulation_definition;
{
    Object alist, current_computation_frame, current_computation_flags;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,21);
    alist = 
	    simulate_cons_1(simulate_cons_1(ISVREF(external_simulation_definition,
	    (SI_Long)20L),entity),Nil);
    current_computation_frame = external_simulation_definition;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      current_computation_flags = Current_computation_flags;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	      0);
	Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
		(SI_Long)16L);
	result = VALUES_1(EQ(variable,evaluate_designation(designation,
		alist)) ? T : Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INSTALL-EXTERNALLY-SIMULATED-VARIABLE-1 */
Object install_externally_simulated_variable_1(variable,
	    external_simulation_definition_qm,deinstall_qm)
    Object variable, external_simulation_definition_qm, deinstall_qm;
{
    x_note_fn_call(219,22);
    if (external_simulation_definition_qm &&  !TRUEP(deinstall_qm))
	return put_external_simulation_formula_into_variable_or_parameter(variable,
		external_simulation_definition_qm);
    else
	return put_external_simulation_formula_into_variable_or_parameter(variable,
		Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Output_vector_for_object, Qoutput_vector_for_object);

Object The_type_description_of_external_simulation_object = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_external_simulation_objects, Qchain_of_available_external_simulation_objects);

DEFINE_VARIABLE_WITH_SYMBOL(External_simulation_object_count, Qexternal_simulation_object_count);

Object Chain_of_available_external_simulation_objects_vector = UNBOUND;

/* EXTERNAL-SIMULATION-OBJECT-STRUCTURE-MEMORY-USAGE */
Object external_simulation_object_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(219,23);
    temp = External_simulation_object_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXTERNAL-SIMULATION-OBJECT-COUNT */
Object outstanding_external_simulation_object_count()
{
    Object def_structure_external_simulation_object_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(219,24);
    gensymed_symbol = IFIX(External_simulation_object_count);
    def_structure_external_simulation_object_variable = 
	    Chain_of_available_external_simulation_objects;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_external_simulation_object_variable))
	goto end_loop;
    def_structure_external_simulation_object_variable = 
	    ISVREF(def_structure_external_simulation_object_variable,
	    (SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXTERNAL-SIMULATION-OBJECT-1 */
Object reclaim_external_simulation_object_1(external_simulation_object)
    Object external_simulation_object;
{
    Object temp, svref_arg_2;

    x_note_fn_call(219,25);
    inline_note_reclaim_cons(external_simulation_object,Nil);
    temp = ISVREF(Chain_of_available_external_simulation_objects_vector,
	    IFIX(Current_thread_index));
    SVREF(external_simulation_object,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_external_simulation_objects_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = external_simulation_object;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXTERNAL-SIMULATION-OBJECT */
Object reclaim_structure_for_external_simulation_object(external_simulation_object)
    Object external_simulation_object;
{
    x_note_fn_call(219,26);
    return reclaim_external_simulation_object_1(external_simulation_object);
}

static Object Qg2_defstruct_structure_name_external_simulation_object_g2_struct;  /* g2-defstruct-structure-name::external-simulation-object-g2-struct */

/* MAKE-PERMANENT-EXTERNAL-SIMULATION-OBJECT-STRUCTURE-INTERNAL */
Object make_permanent_external_simulation_object_structure_internal()
{
    Object def_structure_external_simulation_object_variable;
    Object defstruct_g2_external_simulation_object_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(219,27);
    def_structure_external_simulation_object_variable = Nil;
    atomic_incff_symval(Qexternal_simulation_object_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_external_simulation_object_variable = Nil;
	gensymed_symbol = (SI_Long)3L;
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
	defstruct_g2_external_simulation_object_variable = the_array;
	SVREF(defstruct_g2_external_simulation_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_external_simulation_object_g2_struct;
	def_structure_external_simulation_object_variable = 
		defstruct_g2_external_simulation_object_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_external_simulation_object_variable);
}

/* MAKE-EXTERNAL-SIMULATION-OBJECT-1 */
Object make_external_simulation_object_1()
{
    Object def_structure_external_simulation_object_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(219,28);
    def_structure_external_simulation_object_variable = 
	    ISVREF(Chain_of_available_external_simulation_objects_vector,
	    IFIX(Current_thread_index));
    if (def_structure_external_simulation_object_variable) {
	svref_arg_1 = Chain_of_available_external_simulation_objects_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_external_simulation_object_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_external_simulation_object_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_external_simulation_object_g2_struct;
    }
    else
	def_structure_external_simulation_object_variable = 
		make_permanent_external_simulation_object_structure_internal();
    inline_note_allocate_cons(def_structure_external_simulation_object_variable,
	    Nil);
    SVREF(def_structure_external_simulation_object_variable,
	    FIX((SI_Long)2L)) = Nil;
    return VALUES_1(def_structure_external_simulation_object_variable);
}

static Object Qstandard_icp_object_index_space;  /* standard-icp-object-index-space */

static Object Qestablish_new_object_index_for_external_simulation_object;  /* establish-new-object-index-for-external-simulation-object */

static Object string_constant_2;   /* "resumable icp synch error: ~S expected, ~S found" */

/* ESTABLISH-NEW-OBJECT-INDEX-FOR-EXTERNAL-SIMULATION-OBJECT */
Object establish_new_object_index_for_external_simulation_object varargs_1(int, n)
{
    Object external_simulation_object, icp_port;
    Object send_enlarge_message_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(219,29);
    INIT_ARGS_nonrelocating();
    external_simulation_object = REQUIRED_ARG_nonrelocating();
    icp_port = REQUIRED_ARG_nonrelocating();
    send_enlarge_message_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    if (Disable_resumability) {
	result = assign_corresponding_icp_object_index(external_simulation_object,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(external_simulation_object,(SI_Long)2L)));
	SVREF(external_simulation_object,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( 
		    !EQ(Qestablish_new_object_index_for_external_simulation_object,
		    top))
		return icp_error_internal(Qerror,string_constant_2,
			Qestablish_new_object_index_for_external_simulation_object,
			top,Nil);
	}
	external_simulation_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : external_simulation_object;
	icp_port = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_port;
	send_enlarge_message_p = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : send_enlarge_message_p;
	result = assign_corresponding_icp_object_index(external_simulation_object,
		Qstandard_icp_object_index_space,send_enlarge_message_p);
	MVS_2(result,corresponding_icp_object_index,
		new_index_limit_plus_one_qm);
	svref_new_value = gensym_cons_1(icp_port,
		gensym_cons_1(corresponding_icp_object_index,
		ISVREF(external_simulation_object,(SI_Long)2L)));
	SVREF(external_simulation_object,FIX((SI_Long)2L)) = svref_new_value;
	if (send_enlarge_message_p)
	    return VALUES_1(corresponding_icp_object_index);
	else
	    return VALUES_2(corresponding_icp_object_index,
		    new_index_limit_plus_one_qm);
    }
}

static Object Qmake_corresponding_icp_external_simulation_object;  /* make-corresponding-icp-external-simulation-object */

/* MAKE-CORRESPONDING-ICP-EXTERNAL-SIMULATION-OBJECT */
Object make_corresponding_icp_external_simulation_object(external_simulation_object)
    Object external_simulation_object;
{
    Object writing_resumable_icp_messages_p, corresponding_icp_object_index;
    Object new_index_limit_plus_one_qm, svref_new_value, temp, g2_object;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);
    Object result;

    x_note_fn_call(219,30);
    if (Disable_resumability) {
	write_icp_maybe_suspend();
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(external_simulation_object,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(external_simulation_object,(SI_Long)2L)));
	  SVREF(external_simulation_object,FIX((SI_Long)2L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      g2_object = ISVREF(external_simulation_object,(SI_Long)1L);
	      define_external_simulation_object(g2_object,
		      corresponding_icp_object_index);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qmake_corresponding_icp_external_simulation_object,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qmake_corresponding_icp_external_simulation_object,
			top,Nil);
	}
	external_simulation_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : external_simulation_object;
	if (EQ(icp_suspend_1,write_icp_maybe_suspend())) {
	    resumable_icp_push(external_simulation_object);
	    resumable_icp_push(Qmake_corresponding_icp_external_simulation_object);
	    return VALUES_1(Icp_suspend);
	}
	writing_resumable_icp_messages_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Writing_resumable_icp_messages_p,Qwriting_resumable_icp_messages_p,writing_resumable_icp_messages_p,
		0);
	  result = assign_corresponding_icp_object_index(external_simulation_object,
		  Qstandard_icp_object_index_space,T);
	  MVS_2(result,corresponding_icp_object_index,
		  new_index_limit_plus_one_qm);
	  svref_new_value = gensym_cons_1(Current_icp_port,
		  gensym_cons_1(corresponding_icp_object_index,
		  ISVREF(external_simulation_object,(SI_Long)2L)));
	  SVREF(external_simulation_object,FIX((SI_Long)2L)) = svref_new_value;
	  if (T);
	  else {
	      temp = corresponding_icp_object_index;
	      corresponding_icp_object_index = temp;
	  }
	  if ( !TRUEP(Inhibit_corresponding_icp_object_making)) {
	      g2_object = ISVREF(external_simulation_object,(SI_Long)1L);
	      define_external_simulation_object(g2_object,
		      corresponding_icp_object_index);
	  }
	  result = VALUES_1(corresponding_icp_object_index);
	POP_SPECIAL();
	return result;
    }
}

/* GET-ICP-OBJECT-INDEX-FOR-EXTERNAL-SIMULATION-OBJECT */
Object get_icp_object_index_for_external_simulation_object(external_simulation_object,
	    icp_port)
    Object external_simulation_object, icp_port;
{
    x_note_fn_call(219,31);
    return getfq_function_no_default(ISVREF(external_simulation_object,
	    (SI_Long)2L),icp_port);
}

/* SET-ICP-OBJECT-INDEX-FOR-EXTERNAL-SIMULATION-OBJECT */
Object set_icp_object_index_for_external_simulation_object(external_simulation_object,
	    corresponding_icp_object_index,icp_port)
    Object external_simulation_object, corresponding_icp_object_index;
    Object icp_port;
{
    Object svref_new_value;

    x_note_fn_call(219,32);
    svref_new_value = gensym_cons_1(icp_port,
	    gensym_cons_1(corresponding_icp_object_index,
	    ISVREF(external_simulation_object,(SI_Long)2L)));
    return VALUES_1(SVREF(external_simulation_object,FIX((SI_Long)2L)) = 
	    svref_new_value);
}

/* RECLAIM-ICP-OBJECT-MAP-FOR-EXTERNAL-SIMULATION-OBJECT */
Object reclaim_icp_object_map_for_external_simulation_object(external_simulation_object)
    Object external_simulation_object;
{
    Object icp_object_map;

    x_note_fn_call(219,33);
    icp_object_map = ISVREF(external_simulation_object,(SI_Long)2L);
    if (icp_object_map)
	return reclaim_icp_object_map(external_simulation_object,
		icp_object_map,Qstandard_icp_object_index_space);
    else
	return VALUES_1(Nil);
}

static Object Qset_access_form_for_external_simulation_object;  /* set-access-form-for-external-simulation-object */

/* RECLAIM-ICP-PORT-ENTRY-FOR-EXTERNAL-SIMULATION-OBJECT */
Object reclaim_icp_port_entry_for_external_simulation_object(external_simulation_object,
	    icp_port)
    Object external_simulation_object, icp_port;
{
    x_note_fn_call(219,34);
    return reclaim_icp_port_entry(icp_port,external_simulation_object,
	    ISVREF(external_simulation_object,(SI_Long)2L),
	    Qset_access_form_for_external_simulation_object);
}

/* SET-ACCESS-FORM-FOR-EXTERNAL-SIMULATION-OBJECT */
Object set_access_form_for_external_simulation_object(external_simulation_object,
	    new_value)
    Object external_simulation_object, new_value;
{
    x_note_fn_call(219,35);
    return VALUES_1(SVREF(external_simulation_object,FIX((SI_Long)2L)) = 
	    new_value);
}

static Object Qsend_icp_new_externally_simulated_object;  /* send-icp-new-externally-simulated-object */

static Object Qnew_externally_simulated_object;  /* new-externally-simulated-object */

static Object string_constant_3;   /* "[message]" */

static Object Qmessage;            /* message */

static Object Qexternal_simulation_object;  /* external-simulation-object */

static Object string_constant_4;   /* "[object arg]" */

static Object Qargument;           /* argument */

/* SEND-ICP-NEW-EXTERNALLY-SIMULATED-OBJECT */
Object send_icp_new_externally_simulated_object(external_simulation_object)
    Object external_simulation_object;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,36);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_new_externally_simulated_object;
	  }
	  temp_1 = 
		  getfq_function_no_default(ISVREF(external_simulation_object,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_external_simulation_object(external_simulation_object);
	  external_simulation_object = temp_1;
	  start_writing_icp_message(FIX((SI_Long)120L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnew_externally_simulated_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(external_simulation_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(external_simulation_object);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnew_externally_simulated_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object,string_constant_4,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_corresponding_object_index(external_simulation_object);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_corresponding_object_index(external_simulation_object);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_new_externally_simulated_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_new_externally_simulated_object,top,Nil);
		goto end_send_icp_new_externally_simulated_object;
	    }
	}
	external_simulation_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : external_simulation_object;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_new_externally_simulated_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(external_simulation_object,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      external_simulation_object = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_external_simulation_object(external_simulation_object);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      external_simulation_object = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)120L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qnew_externally_simulated_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(external_simulation_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(external_simulation_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qnew_externally_simulated_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object,string_constant_4,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(external_simulation_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_corresponding_object_index(external_simulation_object))) 
		      {
	      resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(external_simulation_object);
	      resumable_icp_push(Qsend_icp_new_externally_simulated_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_new_externally_simulated_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_new_externally_simulated_object:
    return result;
}

static Object Qsend_icp_define_external_simulation_object;  /* send-icp-define-external-simulation-object */

static Object Qdefine_external_simulation_object;  /* define-external-simulation-object */

static Object Qicp_object_index;   /* icp-object-index */

static Object string_constant_5;   /* "[value arg]" */

static Object Qobject_class;       /* object-class */

/* SEND-ICP-DEFINE-EXTERNAL-SIMULATION-OBJECT */
Object send_icp_define_external_simulation_object(icp_object_index,
	    object_class)
    Object icp_object_index, object_class;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,37);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_external_simulation_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)121L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_external_simulation_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qicp_object_index,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_integer(icp_object_index);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qicp_object_index,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_integer(icp_object_index);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qobject_class,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_text_string(object_class);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qobject_class,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_text_string(object_class);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_external_simulation_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qicp_object_index,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_integer(icp_object_index);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qicp_object_index,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_integer(icp_object_index);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qobject_class,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = write_icp_text_string(object_class);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qobject_class,string_constant_5,Qargument,
				Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(object_class);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_define_external_simulation_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_define_external_simulation_object,top,Nil);
		goto end_send_icp_define_external_simulation_object;
	    }
	}
	icp_object_index = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : icp_object_index;
	object_class = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : object_class;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_define_external_simulation_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)121L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qdefine_external_simulation_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qicp_object_index,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_integer(icp_object_index))) {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qicp_object_index,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			    write_icp_integer(icp_object_index))) {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qobject_class,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(object_class))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qobject_class,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			    write_icp_text_string(object_class))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qdefine_external_simulation_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
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
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qicp_object_index,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
				write_icp_integer(icp_object_index))) {
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qicp_object_index,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_integer(icp_object_index))) {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qobject_class,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
				write_icp_text_string(object_class))) {
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qobject_class,string_constant_5,Qargument,
				Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,write_icp_text_string(object_class))) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(object_class);
	      resumable_icp_push(icp_object_index);
	      resumable_icp_push(Qsend_icp_define_external_simulation_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_define_external_simulation_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_define_external_simulation_object:
    return result;
}

static Object Qsend_icp_simulation_initialization_value;  /* send-icp-simulation-initialization-value */

static Object Qsimulation_initialization_value;  /* simulation-initialization-value */

static Object Qinitialization_value;  /* initialization-value */

/* SEND-ICP-SIMULATION-INITIALIZATION-VALUE */
Object send_icp_simulation_initialization_value(initialization_value)
    Object initialization_value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,38);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_simulation_initialization_value;
	  }
	  start_writing_icp_message(FIX((SI_Long)122L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qsimulation_initialization_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qinitialization_value,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_float(initialization_value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinitialization_value,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_float(initialization_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_initialization_value,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinitialization_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_float(initialization_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinitialization_value,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_float(initialization_value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_simulation_initialization_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_simulation_initialization_value,top,Nil);
		goto end_send_icp_simulation_initialization_value;
	    }
	}
	initialization_value = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : initialization_value;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_simulation_initialization_value;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)122L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qsimulation_initialization_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qinitialization_value,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_float(initialization_value))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinitialization_value,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_float(initialization_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_initialization_value,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinitialization_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_float(initialization_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinitialization_value,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_float(initialization_value))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(initialization_value);
	      resumable_icp_push(Qsend_icp_simulation_initialization_value);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_simulation_initialization_value;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_simulation_initialization_value:
    return result;
}

static Object Qsend_icp_end_simulation_initialization_vector_for_object;  /* send-icp-end-simulation-initialization-vector-for-object */

static Object Qend_simulation_initialization_vector_for_object;  /* end-simulation-initialization-vector-for-object */

/* SEND-ICP-END-SIMULATION-INITIALIZATION-VECTOR-FOR-OBJECT */
Object send_icp_end_simulation_initialization_vector_for_object()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,39);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_initialization_vector_for_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)123L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_initialization_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_initialization_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( 
		    !EQ(Qsend_icp_end_simulation_initialization_vector_for_object,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_end_simulation_initialization_vector_for_object,
			top,Nil);
		goto end_send_icp_end_simulation_initialization_vector_for_object;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_initialization_vector_for_object;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)123L)))) {
	      resumable_icp_push(Qsend_icp_end_simulation_initialization_vector_for_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_simulation_initialization_vector_for_object;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_initialization_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_initialization_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_simulation_initialization_vector_for_object:
    return result;
}

static Object Qsend_icp_begin_simulation_input_vector_for_object;  /* send-icp-begin-simulation-input-vector-for-object */

static Object Qbegin_simulation_input_vector_for_object;  /* begin-simulation-input-vector-for-object */

/* SEND-ICP-BEGIN-SIMULATION-INPUT-VECTOR-FOR-OBJECT */
Object send_icp_begin_simulation_input_vector_for_object(external_simulation_object)
    Object external_simulation_object;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,40);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_begin_simulation_input_vector_for_object;
	  }
	  temp_1 = 
		  getfq_function_no_default(ISVREF(external_simulation_object,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_external_simulation_object(external_simulation_object);
	  external_simulation_object = temp_1;
	  start_writing_icp_message(FIX((SI_Long)124L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_simulation_input_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(external_simulation_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_corresponding_object_index(external_simulation_object);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_simulation_input_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object,string_constant_4,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_corresponding_object_index(external_simulation_object);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_corresponding_object_index(external_simulation_object);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_begin_simulation_input_vector_for_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_begin_simulation_input_vector_for_object,
			top,Nil);
		goto end_send_icp_begin_simulation_input_vector_for_object;
	    }
	}
	external_simulation_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : external_simulation_object;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_begin_simulation_input_vector_for_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(external_simulation_object,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      external_simulation_object = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_external_simulation_object(external_simulation_object);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      external_simulation_object = value_1;
	  }
	l2:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)124L)))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l3:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_simulation_input_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(external_simulation_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(external_simulation_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_simulation_input_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object,string_constant_4,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(external_simulation_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object,string_constant_4,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_corresponding_object_index(external_simulation_object))) 
		      {
	      resumable_icp_push(FIX((SI_Long)3L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(external_simulation_object);
	      resumable_icp_push(Qsend_icp_begin_simulation_input_vector_for_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_begin_simulation_input_vector_for_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_begin_simulation_input_vector_for_object:
    return result;
}

static Object Qsend_icp_simulation_keyword;  /* send-icp-simulation-keyword */

static Object Qsimulation_keyword;  /* simulation-keyword */

/* SEND-ICP-SIMULATION-KEYWORD */
Object send_icp_simulation_keyword(keyword)
    Object keyword;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,41);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_keyword;
	  }
	  start_writing_icp_message(FIX((SI_Long)125L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_keyword,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qkeyword,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_text_string(keyword);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qkeyword,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_text_string(keyword);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_keyword,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qkeyword,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_text_string(keyword);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qkeyword,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_text_string(keyword);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_simulation_keyword,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_simulation_keyword,top,Nil);
		goto end_send_icp_simulation_keyword;
	    }
	}
	keyword = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : keyword;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_keyword;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)125L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_keyword,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qkeyword,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_text_string(keyword))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qkeyword,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_text_string(keyword))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_keyword,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qkeyword,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_text_string(keyword))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qkeyword,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_text_string(keyword))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(keyword);
	      resumable_icp_push(Qsend_icp_simulation_keyword);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_simulation_keyword;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_simulation_keyword:
    return result;
}

static Object Qsend_icp_simulation_input_value;  /* send-icp-simulation-input-value */

static Object Qsimulation_input_value;  /* simulation-input-value */

static Object Qinput_value;        /* input-value */

/* SEND-ICP-SIMULATION-INPUT-VALUE */
Object send_icp_simulation_input_value(input_value)
    Object input_value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,42);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_input_value;
	  }
	  start_writing_icp_message(FIX((SI_Long)126L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_input_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qinput_value,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_float(input_value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_value,string_constant_5,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_float(input_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_input_value,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinput_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_float(input_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinput_value,string_constant_5,Qargument,Nil,
			    Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_float(input_value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_simulation_input_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_simulation_input_value,top,Nil);
		goto end_send_icp_simulation_input_value;
	    }
	}
	input_value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) :
		 TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : input_value;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_input_value;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)126L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_input_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qinput_value,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_float(input_value))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_value,string_constant_5,Qargument,
				  Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_float(input_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_input_value,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinput_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_float(input_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinput_value,string_constant_5,Qargument,Nil,
			    Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_float(input_value))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(input_value);
	      resumable_icp_push(Qsend_icp_simulation_input_value);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_simulation_input_value;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_simulation_input_value:
    return result;
}

static Object Qsend_icp_end_simulation_input_vector_for_object;  /* send-icp-end-simulation-input-vector-for-object */

static Object Qend_simulation_input_vector_for_object;  /* end-simulation-input-vector-for-object */

/* SEND-ICP-END-SIMULATION-INPUT-VECTOR-FOR-OBJECT */
Object send_icp_end_simulation_input_vector_for_object()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,43);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_input_vector_for_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)127L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_input_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_input_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( !EQ(Qsend_icp_end_simulation_input_vector_for_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_end_simulation_input_vector_for_object,
			top,Nil);
		goto end_send_icp_end_simulation_input_vector_for_object;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_input_vector_for_object;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)127L)))) {
	      resumable_icp_push(Qsend_icp_end_simulation_input_vector_for_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_simulation_input_vector_for_object;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_input_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_input_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_simulation_input_vector_for_object:
    return result;
}

static Object Qsend_icp_begin_simulation_output_vector_for_object;  /* send-icp-begin-simulation-output-vector-for-object */

static Object Qbegin_simulation_output_vector_for_object;  /* begin-simulation-output-vector-for-object */

static Object Qexternal_simulation_object_qm;  /* external-simulation-object? */

/* SEND-ICP-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT */
Object send_icp_begin_simulation_output_vector_for_object(external_simulation_object_qm)
    Object external_simulation_object_qm;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,44);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_begin_simulation_output_vector_for_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)131L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object_qm,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_returned_external_simulation_object(external_simulation_object_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object_qm,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_returned_external_simulation_object(external_simulation_object_qm);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_simulation_output_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object_qm,string_constant_5,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_returned_external_simulation_object(external_simulation_object_qm);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object_qm,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_returned_external_simulation_object(external_simulation_object_qm);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_begin_simulation_output_vector_for_object,
			top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_begin_simulation_output_vector_for_object,
			top,Nil);
		goto end_send_icp_begin_simulation_output_vector_for_object;
	    }
	}
	external_simulation_object_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : external_simulation_object_qm;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_begin_simulation_output_vector_for_object;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)131L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qbegin_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternal_simulation_object_qm,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_returned_external_simulation_object(external_simulation_object_qm))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternal_simulation_object_qm,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_returned_external_simulation_object(external_simulation_object_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qbegin_simulation_output_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qexternal_simulation_object_qm,string_constant_5,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_returned_external_simulation_object(external_simulation_object_qm))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qexternal_simulation_object_qm,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_returned_external_simulation_object(external_simulation_object_qm))) 
		      {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(external_simulation_object_qm);
	      resumable_icp_push(Qsend_icp_begin_simulation_output_vector_for_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_begin_simulation_output_vector_for_object;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_begin_simulation_output_vector_for_object:
    return result;
}

static Object string_constant_6;   /* "Unable to retrieve external simulation object" */

/* HANDLE-ICP-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT--BODY */
Object handle_icp_begin_simulation_output_vector_for_object__body(external_simulation_object_qm)
    Object external_simulation_object_qm;
{
    Object g2_object;

    x_note_fn_call(219,45);
    if (external_simulation_object_qm) {
	g2_object = ISVREF(external_simulation_object_qm,(SI_Long)1L);
	Output_vector_for_object = simulate_cons_1(g2_object,Nil);
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(2,FIX((SI_Long)1L),string_constant_6);
	Suppress_warning_message_header_qm = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qhandle_icp_begin_simulation_output_vector_for_object;  /* handle-icp-begin-simulation-output-vector-for-object */

static Object Qresumable_icp_list_end;  /* resumable-icp-list-end */

/* HANDLE-ICP-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT */
Object handle_icp_begin_simulation_output_vector_for_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, external_simulation_object_qm;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,46);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qbegin_simulation_output_vector_for_object,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qexternal_simulation_object_qm,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = 
			    read_icp_returned_external_simulation_object();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qexternal_simulation_object_qm,
				string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    external_simulation_object_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  external_simulation_object_qm = 
			  read_icp_returned_external_simulation_object();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_begin_simulation_output_vector_for_object__body(external_simulation_object_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qbegin_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qexternal_simulation_object_qm,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = 
			  read_icp_returned_external_simulation_object();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qexternal_simulation_object_qm,
			      string_constant_5,Qargument,T,result_of_read,
			      Nil,Nil);
		  external_simulation_object_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else
		external_simulation_object_qm = 
			read_icp_returned_external_simulation_object();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_begin_simulation_output_vector_for_object__body(external_simulation_object_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_begin_simulation_output_vector_for_object,
		    top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_begin_simulation_output_vector_for_object,
			top,Nil);
		goto end_handle_icp_begin_simulation_output_vector_for_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qbegin_simulation_output_vector_for_object,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  external_simulation_object_qm = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qexternal_simulation_object_qm,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_returned_external_simulation_object();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_begin_simulation_output_vector_for_object);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_begin_simulation_output_vector_for_object;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qexternal_simulation_object_qm,
				string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    external_simulation_object_qm = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_returned_external_simulation_object();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_begin_simulation_output_vector_for_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_simulation_output_vector_for_object;
		  }
		  external_simulation_object_qm = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_begin_simulation_output_vector_for_object__body(external_simulation_object_qm);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qbegin_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		external_simulation_object_qm = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qexternal_simulation_object_qm,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_returned_external_simulation_object();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_begin_simulation_output_vector_for_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_begin_simulation_output_vector_for_object;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qexternal_simulation_object_qm,
			      string_constant_5,Qargument,T,result_of_read,
			      Nil,Nil);
		  external_simulation_object_qm = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_returned_external_simulation_object();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_begin_simulation_output_vector_for_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_begin_simulation_output_vector_for_object;
		}
		external_simulation_object_qm = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_begin_simulation_output_vector_for_object__body(external_simulation_object_qm);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_begin_simulation_output_vector_for_object:
    return result;
}

static Object Qsend_icp_simulation_output_value;  /* send-icp-simulation-output-value */

static Object Qsimulation_output_value;  /* simulation-output-value */

static Object Qoutput_value;       /* output-value */

/* SEND-ICP-SIMULATION-OUTPUT-VALUE */
Object send_icp_simulation_output_value(output_value)
    Object output_value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,47);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_output_value;
	  }
	  start_writing_icp_message(FIX((SI_Long)132L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_output_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qoutput_value,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_float(output_value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qoutput_value,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_float(output_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_output_value,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qoutput_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_float(output_value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qoutput_value,string_constant_5,Qargument,Nil,
			    Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_float(output_value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_simulation_output_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_simulation_output_value,top,Nil);
		goto end_send_icp_simulation_output_value;
	    }
	}
	output_value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) 
		: TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : output_value;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_simulation_output_value;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)132L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qsimulation_output_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qoutput_value,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_float(output_value))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qoutput_value,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_float(output_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qsimulation_output_value,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qoutput_value,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_float(output_value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qoutput_value,string_constant_5,Qargument,Nil,
			    Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_float(output_value))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(output_value);
	      resumable_icp_push(Qsend_icp_simulation_output_value);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_simulation_output_value;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_simulation_output_value:
    return result;
}

/* HANDLE-ICP-SIMULATION-OUTPUT-VALUE--BODY */
Object handle_icp_simulation_output_value__body(output_value)
    Object output_value;
{
    x_note_fn_call(219,48);
    Output_vector_for_object = nconc2(Output_vector_for_object,
	    simulate_cons_1(output_value,Nil));
    return VALUES_1(Nil);
}

static Object Qhandle_icp_simulation_output_value;  /* handle-icp-simulation-output-value */

/* HANDLE-ICP-SIMULATION-OUTPUT-VALUE */
Object handle_icp_simulation_output_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, output_value;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,49);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qsimulation_output_value,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qoutput_value,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_float();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qoutput_value,string_constant_5,Qargument,
				T,result_of_read,Nil,Nil);
		    output_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  output_value = read_icp_float();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_simulation_output_value__body(output_value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsimulation_output_value,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qoutput_value,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_float();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qoutput_value,string_constant_5,Qargument,T,
			      result_of_read,Nil,Nil);
		  output_value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		output_value = read_icp_float();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_simulation_output_value__body(output_value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_simulation_output_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_simulation_output_value,top,Nil);
		goto end_handle_icp_simulation_output_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qsimulation_output_value,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  output_value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qoutput_value,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_float();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_simulation_output_value);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_simulation_output_value;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qoutput_value,string_constant_5,Qargument,
				T,result_of_read,Nil,Nil);
		    output_value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_float();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_simulation_output_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_simulation_output_value;
		  }
		  output_value = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = 
			handle_icp_simulation_output_value__body(output_value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qsimulation_output_value,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		output_value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qoutput_value,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_float();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_simulation_output_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_simulation_output_value;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qoutput_value,string_constant_5,Qargument,T,
			      result_of_read,Nil,Nil);
		  output_value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_float();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_simulation_output_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_simulation_output_value;
		}
		output_value = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_simulation_output_value__body(output_value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_simulation_output_value:
    return result;
}

static Object Qsend_icp_end_simulation_output_vector_for_object;  /* send-icp-end-simulation-output-vector-for-object */

static Object Qend_simulation_output_vector_for_object;  /* end-simulation-output-vector-for-object */

/* SEND-ICP-END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT */
Object send_icp_end_simulation_output_vector_for_object()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,50);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_output_vector_for_object;
	  }
	  start_writing_icp_message(FIX((SI_Long)133L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_output_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( !EQ(Qsend_icp_end_simulation_output_vector_for_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_end_simulation_output_vector_for_object,
			top,Nil);
		goto end_send_icp_end_simulation_output_vector_for_object;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_output_vector_for_object;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)133L)))) {
	      resumable_icp_push(Qsend_icp_end_simulation_output_vector_for_object);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_simulation_output_vector_for_object;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_output_vector_for_object,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_simulation_output_vector_for_object:
    return result;
}

static Object Qsimulation_info_qm;  /* simulation-info? */

static Object Qlong;               /* long */

static Object Qtext;               /* text */

static Object Qtruth_value;        /* truth-value */

static Object Qboolean;            /* boolean */

static Object string_constant_7;   /* "Problem encountered simulating the designation ~a for the entity ~NF externally." */

static Object string_constant_8;   /* "Problem encountered simulating the entity ~NF externally due to 
				    * mismatch in number of designations specified in \"output vector from external 
				    * simulator\" slot of external simulation definition and number of values returned
				    * by the external simulator."
				    */

/* HANDLE-ICP-END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT--BODY */
Object handle_icp_end_simulation_output_vector_for_object__body()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, g2_object;
    Object external_simulation_definition, alist, current_computation_frame;
    Object current_computation_flags, temp, designations;
    Object variable_simulation_runtime_structure, designation, ab_loop_list_;
    Object output_value, ab_loop_list__1, output_variable_qm, x2;
    Object gensymed_symbol, sub_class_bit_vector, simulation_info_qm;
    Object gensymed_symbol_4, gensymed_symbol_5, type_specification, temp_2;
    Object store_managed_number_or_value_arg_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    double store_managed_number_or_value_arg;
    Declare_special(4);
    Object result;

    x_note_fn_call(219,51);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    3);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      2);
	if (Current_model_runtime_info_qm) {
	    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)17L))) {
		g2_object = CAR(Output_vector_for_object);
		external_simulation_definition = 
			get_slot_value_function(g2_object,
			Qexternal_simulation_definition_for_entity,Nil);
		alist = 
			simulate_cons_1(simulate_cons_1(ISVREF(external_simulation_definition,
			(SI_Long)20L),g2_object),Nil);
		current_computation_frame = external_simulation_definition;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			1);
		  current_computation_flags = Current_computation_flags;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  0);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)16L);
		    temp = ISVREF(external_simulation_definition,(SI_Long)23L);
		    designations = get_attribute_designations(CAR(temp));
		    if (FIXNUM_EQ(length(designations),
			    length(CDR(Output_vector_for_object)))) {
			variable_simulation_runtime_structure = Nil;
			designation = Nil;
			ab_loop_list_ = designations;
			output_value = Nil;
			ab_loop_list__1 = CDR(Output_vector_for_object);
			output_variable_qm = Nil;
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			designation = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop;
			output_value = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			output_variable_qm = 
				evaluate_designation(designation,alist);
			if (output_variable_qm) {
			    if (SIMPLE_VECTOR_P(output_variable_qm) && 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_variable_qm)) 
				    > (SI_Long)2L &&  
				    !EQ(ISVREF(output_variable_qm,
				    (SI_Long)1L),Qavailable_frame_vector)) {
				x2 = ISVREF(output_variable_qm,(SI_Long)1L);
				gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					EQ(ISVREF(x2,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					? x2 : Qnil;
			    }
			    else
				gensymed_symbol = Nil;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Variable_or_parameter_class_description,
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
			    }
			    else
				temp_1 = TRUEP(Nil);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1 ? 
				TRUEP(externally_simulated_variable_p(output_variable_qm)) 
				: TRUEP(Nil)) {
			    temp = ISVREF(output_variable_qm,(SI_Long)8L);
			    temp_1 =  !TRUEP(CAR(temp));
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    simulation_info_qm = 
				    get_lookup_slot_value_given_default(output_variable_qm,
				    Qsimulation_info_qm,Nil);
			    variable_simulation_runtime_structure = 
				    simulation_info_qm ? 
				    ISVREF(simulation_info_qm,(SI_Long)1L) 
				    : Nil;
			    gensymed_symbol = 
				    variable_simulation_runtime_structure;
			    gensymed_symbol_4 = ISVREF(gensymed_symbol,
				    (SI_Long)16L);
			    gensymed_symbol_5 = output_value;
			    type_specification = 
				    type_specification_of_variable_or_parameter_value(gensymed_symbol_4);
			    if (EQ(type_specification,Qfloat) && 
				    FIXNUMP(gensymed_symbol_5)) {
				store_managed_number_or_value_arg = 
					(double)IFIX(gensymed_symbol_5);
				temp_2 = 
					store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					(SI_Long)2L),
					DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
				SVREF(gensymed_symbol,FIX((SI_Long)2L)) = 
					temp_2;
			    }
			    else {
				if (EQ(type_specification,Qinteger))
				    temp = FIXNUMP(gensymed_symbol_5) ? T :
					     Nil;
				else if (EQ(type_specification,Qlong))
				    temp = 
					    INLINE_LONG_P(gensymed_symbol_5) 
					    != (SI_Long)0L ? T : Nil;
				else if (EQ(type_specification,Qfloat))
				    temp = FLOATP(gensymed_symbol_5) ? T : Nil;
				else if (EQ(type_specification,Qsymbol))
				    temp = gensymed_symbol_5 ? 
					    (SYMBOLP(gensymed_symbol_5) ? 
					    T : Nil) : Qnil;
				else if (EQ(type_specification,Qtext))
				    temp = text_string_p(gensymed_symbol_5);
				else if (EQ(type_specification,Qtruth_value))
				    temp = FIXNUMP(gensymed_symbol_5) && 
					    FIXNUM_LE(Falsity,
					    gensymed_symbol_5) ? 
					    (FIXNUM_LE(gensymed_symbol_5,
					    Truth) ? T : Nil) : Qnil;
				else if (EQ(type_specification,Qboolean)) {
				    if (FIXNUMP(gensymed_symbol_5)) {
					temp = FIXNUM_EQ(gensymed_symbol_5,
						Falsity) ? T : Nil;
					if (temp);
					else
					    temp = 
						    FIXNUM_EQ(gensymed_symbol_5,
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
				    temp = FLOATP(gensymed_symbol_5) ? T : Nil;
				    if (temp);
				    else
					temp = FIXNUMP(gensymed_symbol_5) ?
						 T : Nil;
				}
				else
				    temp = Nil;
				if (temp) {
				    store_managed_number_or_value_arg_1 = 
					    gensymed_symbol_5;
				    temp_2 = 
					    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
					    (SI_Long)2L),
					    store_managed_number_or_value_arg_1);
				    SVREF(gensymed_symbol,
					    FIX((SI_Long)2L)) = temp_2;
				}
				else
				    simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_4,
					    gensymed_symbol_5);
			    }
			    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
			    update_variable(output_variable_qm);
			}
			else {
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)2L <= IFIX(Warning_message_level))
				give_warning_1(4,FIX((SI_Long)2L),
					string_constant_7,designation,
					g2_object);
			    Suppress_warning_message_header_qm = Nil;
			}
			goto next_loop;
		      end_loop:;
		    }
		    else {
			Suppress_warning_message_header_qm = T;
			if ((SI_Long)2L <= IFIX(Warning_message_level))
			    give_warning_1(3,FIX((SI_Long)2L),
				    string_constant_8,g2_object);
			Suppress_warning_message_header_qm = Nil;
		    }
		    reclaim_simulate_tree_1(alist);
		    reclaim_simulate_list_1(designations);
		    reclaim_simulate_list_1(Output_vector_for_object);
		    Output_vector_for_object = Nil;
		  POP_SPECIAL();
		POP_SPECIAL();
		if ( 
			!TRUEP(current_send_all_values_at_beginning_of_cycle_qm()))
		    work_on_next_externally_simulated_entity(0);
	    }
	    else {
		reclaim_simulate_list_1(Output_vector_for_object);
		Output_vector_for_object = Nil;
		temp_2 = Current_model_runtime_info_qm;
		SVREF(temp_2,FIX((SI_Long)17L)) = Nil;
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_end_simulation_output_vector_for_object;  /* handle-icp-end-simulation-output-vector-for-object */

/* HANDLE-ICP-END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT */
Object handle_icp_end_simulation_output_vector_for_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(219,52);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qend_simulation_output_vector_for_object,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = 
			handle_icp_end_simulation_output_vector_for_object__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_simulation_output_vector_for_object__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_end_simulation_output_vector_for_object,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_end_simulation_output_vector_for_object,
			top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qend_simulation_output_vector_for_object,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = 
			handle_icp_end_simulation_output_vector_for_object__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_simulation_output_vector_for_object,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_simulation_output_vector_for_object__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_initialize_external_simulator;  /* send-icp-initialize-external-simulator */

static Object Qinitialize_external_simulator;  /* initialize-external-simulator */

/* SEND-ICP-INITIALIZE-EXTERNAL-SIMULATOR */
Object send_icp_initialize_external_simulator()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,53);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_initialize_external_simulator;
	  }
	  start_writing_icp_message(FIX((SI_Long)134L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qinitialize_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qinitialize_external_simulator,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( !EQ(Qsend_icp_initialize_external_simulator,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_initialize_external_simulator,top,Nil);
		goto end_send_icp_initialize_external_simulator;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_initialize_external_simulator;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)134L)))) {
	      resumable_icp_push(Qsend_icp_initialize_external_simulator);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_initialize_external_simulator;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qinitialize_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qinitialize_external_simulator,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_initialize_external_simulator:
    return result;
}

/* HANDLE-ICP-INITIALIZE-EXTERNAL-SIMULATOR */
Object handle_icp_initialize_external_simulator()
{
    x_note_fn_call(219,54);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qinitialize_external_simulator,FIX((SI_Long)134L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_shutdown_external_simulator;  /* send-icp-shutdown-external-simulator */

static Object Qshutdown_external_simulator;  /* shutdown-external-simulator */

/* SEND-ICP-SHUTDOWN-EXTERNAL-SIMULATOR */
Object send_icp_shutdown_external_simulator()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,55);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_shutdown_external_simulator;
	  }
	  start_writing_icp_message(FIX((SI_Long)128L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qshutdown_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qshutdown_external_simulator,string_constant_3,
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
	    if ( !EQ(Qsend_icp_shutdown_external_simulator,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_shutdown_external_simulator,top,Nil);
		goto end_send_icp_shutdown_external_simulator;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_shutdown_external_simulator;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)128L)))) {
	      resumable_icp_push(Qsend_icp_shutdown_external_simulator);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_shutdown_external_simulator;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qshutdown_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qshutdown_external_simulator,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_shutdown_external_simulator:
    return result;
}

/* HANDLE-ICP-SHUTDOWN-EXTERNAL-SIMULATOR */
Object handle_icp_shutdown_external_simulator()
{
    x_note_fn_call(219,56);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qshutdown_external_simulator,FIX((SI_Long)128L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_pause_external_simulator;  /* send-icp-pause-external-simulator */

static Object Qpause_external_simulator;  /* pause-external-simulator */

/* SEND-ICP-PAUSE-EXTERNAL-SIMULATOR */
Object send_icp_pause_external_simulator()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,57);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_pause_external_simulator;
	  }
	  start_writing_icp_message(FIX((SI_Long)129L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qpause_external_simulator,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qpause_external_simulator,string_constant_3,
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
	    if ( !EQ(Qsend_icp_pause_external_simulator,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_pause_external_simulator,top,Nil);
		goto end_send_icp_pause_external_simulator;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_pause_external_simulator;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)129L)))) {
	      resumable_icp_push(Qsend_icp_pause_external_simulator);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_pause_external_simulator;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qpause_external_simulator,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qpause_external_simulator,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_pause_external_simulator:
    return result;
}

/* HANDLE-ICP-PAUSE-EXTERNAL-SIMULATOR */
Object handle_icp_pause_external_simulator()
{
    x_note_fn_call(219,58);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qpause_external_simulator,FIX((SI_Long)129L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_resume_external_simulator;  /* send-icp-resume-external-simulator */

static Object Qresume_external_simulator;  /* resume-external-simulator */

/* SEND-ICP-RESUME-EXTERNAL-SIMULATOR */
Object send_icp_resume_external_simulator()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,59);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_resume_external_simulator;
	  }
	  start_writing_icp_message(FIX((SI_Long)130L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qresume_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qresume_external_simulator,string_constant_3,
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
	    if ( !EQ(Qsend_icp_resume_external_simulator,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_resume_external_simulator,top,Nil);
		goto end_send_icp_resume_external_simulator;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_resume_external_simulator;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)130L)))) {
	      resumable_icp_push(Qsend_icp_resume_external_simulator);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_resume_external_simulator;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qresume_external_simulator,string_constant_3,
			  Qmessage,Nil,Nil,Nil,Nil);
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
			    Qresume_external_simulator,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_resume_external_simulator:
    return result;
}

/* HANDLE-ICP-RESUME-EXTERNAL-SIMULATOR */
Object handle_icp_resume_external_simulator()
{
    x_note_fn_call(219,60);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qresume_external_simulator,FIX((SI_Long)130L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_end_simulation_input_for_cycle;  /* send-icp-end-simulation-input-for-cycle */

static Object Qend_simulation_input_for_cycle;  /* end-simulation-input-for-cycle */

/* SEND-ICP-END-SIMULATION-INPUT-FOR-CYCLE */
Object send_icp_end_simulation_input_for_cycle()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,61);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_input_for_cycle;
	  }
	  start_writing_icp_message(FIX((SI_Long)135L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_input_for_cycle,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_input_for_cycle,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( !EQ(Qsend_icp_end_simulation_input_for_cycle,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_end_simulation_input_for_cycle,top,Nil);
		goto end_send_icp_end_simulation_input_for_cycle;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_input_for_cycle;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)135L)))) {
	      resumable_icp_push(Qsend_icp_end_simulation_input_for_cycle);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_simulation_input_for_cycle;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_input_for_cycle,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_input_for_cycle,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_simulation_input_for_cycle:
    return result;
}

/* HANDLE-ICP-END-SIMULATION-INPUT-FOR-CYCLE */
Object handle_icp_end_simulation_input_for_cycle()
{
    x_note_fn_call(219,62);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qend_simulation_input_for_cycle,FIX((SI_Long)135L));
    return VALUES_1(Nil);
}

static Object Qsend_icp_end_simulation_output_for_cycle;  /* send-icp-end-simulation-output-for-cycle */

static Object Qend_simulation_output_for_cycle;  /* end-simulation-output-for-cycle */

/* SEND-ICP-END-SIMULATION-OUTPUT-FOR-CYCLE */
Object send_icp_end_simulation_output_for_cycle()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,63);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_output_for_cycle;
	  }
	  start_writing_icp_message(FIX((SI_Long)136L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_output_for_cycle,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_output_for_cycle,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
	    if ( !EQ(Qsend_icp_end_simulation_output_for_cycle,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_end_simulation_output_for_cycle,top,Nil);
		goto end_send_icp_end_simulation_output_for_cycle;
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_end_simulation_output_for_cycle;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)136L)))) {
	      resumable_icp_push(Qsend_icp_end_simulation_output_for_cycle);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_end_simulation_output_for_cycle;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qend_simulation_output_for_cycle,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qend_simulation_output_for_cycle,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_end_simulation_output_for_cycle:
    return result;
}

/* HANDLE-ICP-END-SIMULATION-OUTPUT-FOR-CYCLE--BODY */
Object handle_icp_end_simulation_output_for_cycle__body()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,64);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm)
	    end_external_work_for_cycle();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_end_simulation_output_for_cycle;  /* handle-icp-end-simulation-output-for-cycle */

/* HANDLE-ICP-END-SIMULATION-OUTPUT-FOR-CYCLE */
Object handle_icp_end_simulation_output_for_cycle()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(219,65);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qend_simulation_output_for_cycle,string_constant_3,
			Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = 
			handle_icp_end_simulation_output_for_cycle__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_simulation_output_for_cycle,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_simulation_output_for_cycle__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_end_simulation_output_for_cycle,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_end_simulation_output_for_cycle,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qend_simulation_output_for_cycle,string_constant_3,
			Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = 
			handle_icp_end_simulation_output_for_cycle__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qend_simulation_output_for_cycle,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_end_simulation_output_for_cycle__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_connection_info;  /* send-icp-connection-info */

static Object Qconnection_info;    /* connection-info */

static Object Qinput_end_object;   /* input-end-object */

static Object Qoutput_end_object;  /* output-end-object */

static Object Qdirectional_qm;     /* directional? */

static Object Qport_name_for_input_end_object;  /* port-name-for-input-end-object */

static Object Qport_name_for_output_end_object;  /* port-name-for-output-end-object */

static Object Qexternally_simulated_connection;  /* externally-simulated-connection */

static Object Qnumber_of_connections_left_in_path;  /* number-of-connections-left-in-path */

/* SEND-ICP-CONNECTION-INFO */
Object send_icp_connection_info(input_end_object,output_end_object,
	    directional_qm,port_name_for_input_end_object,
	    port_name_for_output_end_object,
	    externally_simulated_connection,number_of_connections_left_in_path)
    Object input_end_object, output_end_object, directional_qm;
    Object port_name_for_input_end_object, port_name_for_output_end_object;
    Object externally_simulated_connection, number_of_connections_left_in_path;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, resumable_icp_state_1;
    Object icp_suspend_1, top, value, value_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,66);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_info;
	  }
	  temp_1 = getfq_function_no_default(ISVREF(input_end_object,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_external_simulation_object(input_end_object);
	  input_end_object = temp_1;
	  temp_1 = getfq_function_no_default(ISVREF(output_end_object,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_external_simulation_object(output_end_object);
	  output_end_object = temp_1;
	  temp_1 = 
		  getfq_function_no_default(ISVREF(externally_simulated_connection,
		  (SI_Long)2L),Current_icp_port);
	  if (temp_1);
	  else
	      temp_1 = 
		      make_corresponding_icp_external_simulation_object(externally_simulated_connection);
	  externally_simulated_connection = temp_1;
	  start_writing_icp_message(FIX((SI_Long)137L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qconnection_info,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qinput_end_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(input_end_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_end_object,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(input_end_object);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qoutput_end_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(output_end_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qoutput_end_object,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(output_end_object);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qdirectional_qm,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(directional_qm);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qdirectional_qm,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_unsigned_integer(directional_qm);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qport_name_for_input_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(port_name_for_input_end_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qport_name_for_input_end_object,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_text_string(port_name_for_input_end_object);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qport_name_for_output_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(port_name_for_output_end_object);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qport_name_for_output_end_object,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_text_string(port_name_for_output_end_object);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternally_simulated_connection,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_corresponding_object_index(externally_simulated_connection);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternally_simulated_connection,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    write_icp_corresponding_object_index(externally_simulated_connection);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_connections_left_in_path,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_unsigned_integer(number_of_connections_left_in_path);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_connections_left_in_path,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_unsigned_integer(number_of_connections_left_in_path);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_info,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else {
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qinput_end_object,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(input_end_object);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qinput_end_object,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(input_end_object);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qoutput_end_object,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(output_end_object);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qoutput_end_object,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(output_end_object);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qdirectional_qm,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(directional_qm);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qdirectional_qm,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(directional_qm);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qport_name_for_input_end_object,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(port_name_for_input_end_object);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qport_name_for_input_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(port_name_for_input_end_object);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qport_name_for_output_end_object,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_text_string(port_name_for_output_end_object);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qport_name_for_output_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_text_string(port_name_for_output_end_object);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qexternally_simulated_connection,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_corresponding_object_index(externally_simulated_connection);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qexternally_simulated_connection,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_corresponding_object_index(externally_simulated_connection);
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qnumber_of_connections_left_in_path,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    result_of_write = 
			    write_icp_unsigned_integer(number_of_connections_left_in_path);
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnumber_of_connections_left_in_path,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else
		  write_icp_unsigned_integer(number_of_connections_left_in_path);
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_connection_info,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_connection_info,top,Nil);
		goto end_send_icp_connection_info;
	    }
	}
	input_end_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : input_end_object;
	output_end_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : output_end_object;
	directional_qm = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : directional_qm;
	port_name_for_input_end_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : port_name_for_input_end_object;
	port_name_for_output_end_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : port_name_for_output_end_object;
	externally_simulated_connection = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : externally_simulated_connection;
	number_of_connections_left_in_path = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : number_of_connections_left_in_path;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_connection_info;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		    case 4:
		      goto l4;
		      break;
		    case 5:
		      goto l5;
		      break;
		    default:
		      break;
		  }
	  }
	l1:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(input_end_object,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      input_end_object = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_external_simulation_object(input_end_object);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      input_end_object = value_1;
	  }
	l2:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(output_end_object,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      output_end_object = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_external_simulation_object(output_end_object);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      output_end_object = value_1;
	  }
	l3:
	  value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) &&  
		  !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		  resumable_icp_pop() : 
		  getfq_function_no_default(ISVREF(externally_simulated_connection,
		  (SI_Long)2L),Current_icp_port);
	  if ( !(resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		  TRUEP(Nil)) && value)
	      externally_simulated_connection = value;
	  else {
	      value_1 = 
		      make_corresponding_icp_external_simulation_object(externally_simulated_connection);
	      if (EQ(icp_suspend_1,value_1)) {
		  resumable_icp_push(value);
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      externally_simulated_connection = value_1;
	  }
	l4:
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)137L)))) {
	      resumable_icp_push(FIX((SI_Long)4L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l5:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qconnection_info,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
			TRUEP(Nil)) {
		    temp_1 = resumable_icp_pop();
		    if (! !(FIXNUMP(temp_1) && 
			    FIXNUM_LE(FIX((SI_Long)-128L),temp_1) && 
			    FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
			switch (INTEGER_TO_CHAR(temp_1)) {
			  case 1:
			    goto l1_1;
			    break;
			  case 2:
			    goto l2_1;
			    break;
			  case 3:
			    goto l3_1;
			    break;
			  case 4:
			    goto l4_1;
			    break;
			  case 5:
			    goto l5_1;
			    break;
			  case 6:
			    goto l6;
			    break;
			  case 7:
			    goto l7;
			    break;
			  default:
			    break;
			}
		}
	      l1_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qinput_end_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(input_end_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)1L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_end_object,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(input_end_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)1L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l2_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qoutput_end_object,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(output_end_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qoutput_end_object,string_constant_4,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(output_end_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l3_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qdirectional_qm,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(directional_qm))) {
			  resumable_icp_push(FIX((SI_Long)3L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qdirectional_qm,string_constant_5,
				  Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(directional_qm))) {
		    resumable_icp_push(FIX((SI_Long)3L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l4_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qport_name_for_input_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(port_name_for_input_end_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)4L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qport_name_for_input_end_object,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(port_name_for_input_end_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)4L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l5_1:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qport_name_for_output_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(port_name_for_output_end_object))) 
				  {
			  resumable_icp_push(FIX((SI_Long)5L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qport_name_for_output_end_object,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(port_name_for_output_end_object))) 
			    {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l6:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qexternally_simulated_connection,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_corresponding_object_index(externally_simulated_connection))) 
				  {
			  resumable_icp_push(FIX((SI_Long)6L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qexternally_simulated_connection,
				  string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_corresponding_object_index(externally_simulated_connection))) 
			    {
		    resumable_icp_push(FIX((SI_Long)6L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
	      l7:
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qnumber_of_connections_left_in_path,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_unsigned_integer(number_of_connections_left_in_path))) 
				  {
			  resumable_icp_push(FIX((SI_Long)7L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  goto end_block_1;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qnumber_of_connections_left_in_path,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      temp_1 = result_of_write;
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_unsigned_integer(number_of_connections_left_in_path))) 
			    {
		    resumable_icp_push(FIX((SI_Long)7L));
		    temp_1 = Icp_suspend;
		    goto end_block_1;
		}
		else
		    temp_1 = Nil;
		goto end_block_1;
	      end_block_1:
		if (EQ(icp_suspend_1,temp_1)) {
		    resumable_icp_push(FIX((SI_Long)5L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qconnection_info,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else {
	      if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
		  temp_1 = resumable_icp_pop();
		  if (! !(FIXNUMP(temp_1) && FIXNUM_LE(FIX((SI_Long)-128L),
			  temp_1) && FIXNUM_LE(temp_1,FIX((SI_Long)127L))))
		      switch (INTEGER_TO_CHAR(temp_1)) {
			case 1:
			  goto l1_2;
			  break;
			case 2:
			  goto l2_2;
			  break;
			case 3:
			  goto l3_2;
			  break;
			case 4:
			  goto l4_2;
			  break;
			case 5:
			  goto l5_2;
			  break;
			case 6:
			  goto l6_1;
			  break;
			case 7:
			  goto l7_1;
			  break;
			default:
			  break;
		      }
	      }
	    l1_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qinput_end_object,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(input_end_object))) 
				{
			resumable_icp_push(FIX((SI_Long)1L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qinput_end_object,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(input_end_object))) 
			  {
		  resumable_icp_push(FIX((SI_Long)1L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l2_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qoutput_end_object,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(output_end_object))) 
				{
			resumable_icp_push(FIX((SI_Long)2L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qoutput_end_object,string_constant_4,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(output_end_object))) 
			  {
		  resumable_icp_push(FIX((SI_Long)2L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l3_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,Qdirectional_qm,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(directional_qm))) {
			resumable_icp_push(FIX((SI_Long)3L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qdirectional_qm,string_constant_5,
				Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(directional_qm))) {
		  resumable_icp_push(FIX((SI_Long)3L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l4_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qport_name_for_input_end_object,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(port_name_for_input_end_object))) 
				{
			resumable_icp_push(FIX((SI_Long)4L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qport_name_for_input_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(port_name_for_input_end_object))) {
		  resumable_icp_push(FIX((SI_Long)4L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l5_2:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qport_name_for_output_end_object,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_text_string(port_name_for_output_end_object))) 
				{
			resumable_icp_push(FIX((SI_Long)5L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qport_name_for_output_end_object,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_text_string(port_name_for_output_end_object))) 
			  {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l6_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qexternally_simulated_connection,
			      string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_corresponding_object_index(externally_simulated_connection))) 
				{
			resumable_icp_push(FIX((SI_Long)6L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qexternally_simulated_connection,
				string_constant_4,Qargument,Nil,Nil,Nil,Nil);
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_corresponding_object_index(externally_simulated_connection))) 
			  {
		  resumable_icp_push(FIX((SI_Long)6L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	    l7_1:
	      if (Icp_write_trace_cutoff_level_qm) {
		  tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		  if (tracep);
		  else
		      tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			      (SI_Long)3L ? T : Nil;
		  if (tracep) {
		      emit_icp_write_trace(T,Nil,Nil,
			      Qnumber_of_connections_left_in_path,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before = 
			      instantaneous_icp_writer_byte_count();
		  }
		  else
		      byte_count_before = Nil;
		  current_icp_write_trace_level = 
			  FIXNUM_ADD1(Current_icp_write_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			  0);
		    if (EQ(icp_suspend_1,
			    write_icp_unsigned_integer(number_of_connections_left_in_path))) 
				{
			resumable_icp_push(FIX((SI_Long)7L));
			temp_1 = Icp_suspend;
			POP_SPECIAL();
			goto end_block_2;
		    }
		    else
			result_of_write = Nil;
		    if (tracep)
			emit_icp_write_trace(Nil,byte_count_before,
				instantaneous_icp_writer_byte_count(),
				Qnumber_of_connections_left_in_path,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    temp_1 = result_of_write;
		  POP_SPECIAL();
	      }
	      else if (EQ(icp_suspend_1,
		      write_icp_unsigned_integer(number_of_connections_left_in_path))) 
			  {
		  resumable_icp_push(FIX((SI_Long)7L));
		  temp_1 = Icp_suspend;
		  goto end_block_2;
	      }
	      else
		  temp_1 = Nil;
	      goto end_block_2;
	    end_block_2:
	      if (EQ(icp_suspend_1,temp_1)) {
		  resumable_icp_push(FIX((SI_Long)5L));
		  temp_1 = Icp_suspend;
		  goto end_block;
	      }
	      else
		  temp_1 = Nil;
	  }
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(number_of_connections_left_in_path);
	      resumable_icp_push(externally_simulated_connection);
	      resumable_icp_push(port_name_for_output_end_object);
	      resumable_icp_push(port_name_for_input_end_object);
	      resumable_icp_push(directional_qm);
	      resumable_icp_push(output_end_object);
	      resumable_icp_push(input_end_object);
	      resumable_icp_push(Qsend_icp_connection_info);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_connection_info;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_connection_info:
    return result;
}

/* HANDLE-ICP-CONNECTION-INFO */
Object handle_icp_connection_info()
{
    x_note_fn_call(219,67);
    error((SI_Long)3L,"ICP did not expect to handle message ~a, code ~a",
	    Qconnection_info,FIX((SI_Long)137L));
    return VALUES_1(Nil);
}

static Object Qtelewindows;        /* telewindows */

static Object string_constant_9;   /* "~a" */

/* DEFINE-EXTERNAL-SIMULATION-OBJECT */
Object define_external_simulation_object(g2_object,icp_object_index)
    Object g2_object, icp_object_index;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, class_string;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(219,68);
    current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)14L),(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
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
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				class_string = tformat_text_string(2,
					string_constant_9,
					ISVREF(ISVREF(g2_object,
					(SI_Long)1L),(SI_Long)1L));
				send_icp_define_external_simulation_object(icp_object_index,
					class_string);
				temp = reclaim_text_string(class_string);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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

static Object Qreturned_external_simulation_object;  /* returned-external-simulation-object */

static Object string_constant_10;  /* "[value]" */

static Object Qvalue;              /* value */

static Object Qread_icp_returned_external_simulation_object;  /* read-icp-returned-external-simulation-object */

/* READ-ICP-RETURNED-EXTERNAL-SIMULATION-OBJECT */
Object read_icp_returned_external_simulation_object()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object corresponding_icp_object_index, current_icp_port, result_of_read;
    Object temp, resumable_icp_state_1, icp_suspend_1, top, value;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,69);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreturned_external_simulation_object,
			string_constant_10,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      corresponding_icp_object_index = read_icp_unsigned_integer();
	      current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      1);
		current_icp_port = ISVREF(ISVREF(Current_icp_port,
			(SI_Long)2L),(SI_Long)4L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			0);
		  result_of_read = 
			  get_corresponding_icp_object(corresponding_icp_object_index);
		POP_SPECIAL();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreturned_external_simulation_object,
			  string_constant_10,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    corresponding_icp_object_index = read_icp_unsigned_integer();
	    current_icp_port = ISVREF(Current_icp_socket,(SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    1);
	      current_icp_port = ISVREF(ISVREF(Current_icp_port,
		      (SI_Long)2L),(SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      0);
		temp = 
			get_corresponding_icp_object(corresponding_icp_object_index);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qread_icp_returned_external_simulation_object,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qread_icp_returned_external_simulation_object,top,Nil);
		goto end_read_icp_returned_external_simulation_object;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qreturned_external_simulation_object,
			string_constant_10,Qvalue,Nil,Nil,Nil,Nil);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    2);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  corresponding_icp_object_index = resumable_icp_pop();
	      else {
		  value = read_icp_unsigned_integer();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qread_icp_returned_external_simulation_object);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_read_icp_returned_external_simulation_object;
		  }
		  corresponding_icp_object_index = value;
	      }
	      current_icp_port = (resumable_icp_state_1 ? 
		      TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		      resumable_icp_pop() : ISVREF(Current_icp_socket,
		      (SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      1);
		current_icp_port = ISVREF(ISVREF(Current_icp_port,
			(SI_Long)2L),(SI_Long)4L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			0);
		  result_of_read = 
			  get_corresponding_icp_object(corresponding_icp_object_index);
		POP_SPECIAL();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qreturned_external_simulation_object,
			  string_constant_10,Qvalue,T,result_of_read,Nil,Nil);
	      temp = result_of_read;
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		corresponding_icp_object_index = resumable_icp_pop();
	    else {
		value = read_icp_unsigned_integer();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qread_icp_returned_external_simulation_object);
		    result = VALUES_1(Icp_suspend);
		    goto end_read_icp_returned_external_simulation_object;
		}
		corresponding_icp_object_index = value;
	    }
	    current_icp_port = (resumable_icp_state_1 ? 
		    TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		    resumable_icp_pop() : ISVREF(Current_icp_socket,
		    (SI_Long)4L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		    1);
	      current_icp_port = ISVREF(ISVREF(Current_icp_port,
		      (SI_Long)2L),(SI_Long)4L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		      0);
		temp = 
			get_corresponding_icp_object(corresponding_icp_object_index);
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
    }
    result = VALUES_1(temp);
  end_read_icp_returned_external_simulation_object:
    return result;
}

static Object Qdummy_definition;   /* dummy-definition */

static Object Qwrite_icp_returned_external_simulation_object;  /* write-icp-returned-external-simulation-object */

/* WRITE-ICP-RETURNED-EXTERNAL-SIMULATION-OBJECT */
Object write_icp_returned_external_simulation_object(returned_external_simulation_object)
    Object returned_external_simulation_object;
{
    Object tracep, byte_count_before, current_icp_write_trace_level;
    Object result_of_write, temp, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(1);

    x_note_fn_call(219,70);
    if (Disable_resumability) {
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qreturned_external_simulation_object,
			string_constant_10,Qvalue,T,
			returned_external_simulation_object,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = Qdummy_definition;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qreturned_external_simulation_object,
			  string_constant_10,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = Qdummy_definition;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qwrite_icp_returned_external_simulation_object,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qwrite_icp_returned_external_simulation_object,top,
			Nil);
	}
	returned_external_simulation_object = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : returned_external_simulation_object;
	if (Icp_write_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			(SI_Long)4L ? T : Nil;
	    if (tracep) {
		emit_icp_write_trace(T,Nil,Nil,
			Qreturned_external_simulation_object,
			string_constant_10,Qvalue,T,
			returned_external_simulation_object,Nil,Nil);
		byte_count_before = instantaneous_icp_writer_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_write_trace_level = 
		    FIXNUM_ADD1(Current_icp_write_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		    0);
	      result_of_write = Qdummy_definition;
	      if (tracep)
		  emit_icp_write_trace(Nil,byte_count_before,
			  instantaneous_icp_writer_byte_count(),
			  Qreturned_external_simulation_object,
			  string_constant_10,Qvalue,Nil,Nil,Nil,Nil);
	      temp = result_of_write;
	    POP_SPECIAL();
	}
	else
	    temp = Qdummy_definition;
    }
    return VALUES_1(temp);
}

static Object Qnone;               /* none */

static Object string_constant_11;  /* "Attempting to execute GSPAN functionality.  GSPAN has been ~
				    *             discontinued as a product and its features were removed from G2 ~
				    *             as of Version 4.0."
				    */

/* INITIALIZE-EXTERNALLY-SIMULATED-PORTION-OF-MODEL */
Object initialize_externally_simulated_portion_of_model()
{
    Object external_simulator_configuration, svref_arg_1;

    x_note_fn_call(219,71);
    external_simulator_configuration = 
	    current_external_simulator_configuration();
    if (external_simulator_configuration &&  
	    !EQ(CAR(external_simulator_configuration),Qnone)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(2,FIX((SI_Long)1L),string_constant_11);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Suppress_warning_message_header_qm);
    }
    else {
	svref_arg_1 = Current_model_runtime_info_qm;
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)15L)) = T);
    }
}

/* INITIALIZE-EXTERNALLY-SIMULATED-ENTITY */
Object initialize_externally_simulated_entity(entity)
    Object entity;
{
    Object current_computation_frame, current_computation_flags;
    Object external_simulation_definition, alist, temp, designations;
    Object designation, ab_loop_list_, output_variable_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,72);
    current_computation_frame = entity;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      current_computation_flags = Current_computation_flags;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	      0);
	external_simulation_definition = get_slot_value_function(entity,
		Qexternal_simulation_definition_for_entity,Nil);
	alist = 
		simulate_cons_1(simulate_cons_1(ISVREF(external_simulation_definition,
		(SI_Long)20L),entity),Nil);
	Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
		(SI_Long)16L);
	temp = ISVREF(external_simulation_definition,(SI_Long)23L);
	designations = get_attribute_designations(CAR(temp));
	designation = Nil;
	ab_loop_list_ = designations;
	output_variable_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	output_variable_qm = evaluate_designation(designation,alist);
	if (output_variable_qm) {
	    if (SIMPLE_VECTOR_P(output_variable_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_variable_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(output_variable_qm,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(output_variable_qm,(SI_Long)1L);
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
			IFIX(ISVREF(Variable_or_parameter_class_description,
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
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? 
		TRUEP(externally_simulated_variable_p(output_variable_qm)) 
		: TRUEP(Nil)) {
	    temp = ISVREF(output_variable_qm,(SI_Long)8L);
	    temp_1 =  !TRUEP(CAR(temp));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    initialize_externally_simulated_variable(output_variable_qm);
	else {
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(4,FIX((SI_Long)1L),string_constant_7,
			designation,entity);
	    Suppress_warning_message_header_qm = Nil;
	}
	goto next_loop;
      end_loop:
	reclaim_simulate_tree_1(alist);
	reclaim_simulate_list_1(designations);
	result = VALUES_1(Qnil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-EXTERNALLY-SIMULATED-VARIABLE */
Object initialize_externally_simulated_variable(variable)
    Object variable;
{
    Object simulation_info_qm, old_runtime_structure_qm, new_runtime_structure;
    Object variable_simulation_runtime_structure, svref_new_value;

    x_note_fn_call(219,73);
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    old_runtime_structure_qm = simulation_info_qm ? 
	    ISVREF(simulation_info_qm,(SI_Long)1L) : Nil;
    new_runtime_structure = make_variable_simulation_runtime_structure_1();
    if (old_runtime_structure_qm)
	reclaim_variable_simulation_runtime_structure(old_runtime_structure_qm);
    SVREF(new_runtime_structure,FIX((SI_Long)16L)) = variable;
    simulation_info_qm = get_lookup_slot_value_given_default(variable,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm)
	SVREF(simulation_info_qm,FIX((SI_Long)1L)) = new_runtime_structure;
    variable_simulation_runtime_structure = new_runtime_structure;
    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)14L)) = Nil;
    svref_new_value = Simulation_no_value;
    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)1L)) = 
	    svref_new_value;
    svref_new_value = Simulation_no_value;
    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)2L)) = 
	    svref_new_value;
    set_up_update_timing_for_variable(variable_simulation_runtime_structure,
	    Nil);
    return VALUES_1(variable_simulation_runtime_structure);
}

static Object Qexternal_simulation_object_structure;  /* external-simulation-object-structure */

static Object Qcalculating_state_variables;  /* calculating-state-variables */

static Object Qinitialization;     /* initialization */

/* CREATE-NEW-EXTERNALLY-SIMULATED-OBJECT */
Object create_new_externally_simulated_object(external_simulation_definition,
	    entity)
    Object external_simulation_definition, entity;
{
    Object class_1, external_simulation_object, current_computation_flags;
    Object alist, current_computation_frame;
    Object current_simulation_runtime_structure, temp, designations;
    Object initializing_simulator_qm, initialization_values, svref_arg_1;
    Object designation, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    Declare_special(4);
    Object result;

    x_note_fn_call(219,74);
    class_1 = ISVREF(external_simulation_definition,(SI_Long)20L);
    external_simulation_object = make_external_simulation_object_1();
    set_slot_value_function(entity,Qexternal_simulation_object_structure,
	    external_simulation_object,Nil);
    SVREF(external_simulation_object,FIX((SI_Long)1L)) = entity;
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    3);
      Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
	      (SI_Long)16L);
      alist = simulate_cons_1(simulate_cons_1(class_1,entity),Nil);
      current_computation_frame = external_simulation_definition;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      2);
	current_simulation_runtime_structure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
		1);
	  temp = ISVREF(external_simulation_definition,(SI_Long)24L);
	  designations = get_attribute_designations(CAR(temp));
	  initializing_simulator_qm = T;
	  PUSH_SPECIAL_WITH_SYMBOL(Initializing_simulator_qm,Qinitializing_simulator_qm,initializing_simulator_qm,
		  0);
	    initialization_values = Nil;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_state_variables;
	    designation = Nil;
	    ab_loop_list_ = designations;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = 
		    simulate_cons_1(sim_eval_variable_for_designation(designation,
		    alist),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    initialization_values = ab_loopvar_;
	    goto end_1;
	    initialization_values = Qnil;
	  end_1:;
	    if (external_simulator_input_values_ok_qm(initialization_values,
		    entity,Qinitialization)) {
		send_create_new_externally_simulated_object(external_simulation_object,
			initialization_values);
		temp = T;
	    }
	    else
		temp = Nil;
	    reclaim_simulate_tree_1(alist);
	    reclaim_simulate_list_1(designations);
	    reclaim_simulate_list_1(initialization_values);
	    result = VALUES_1(temp);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qcm;                 /* \, */

/* MORE-THAN-ONE-DESIGNATION-IN-VECTOR-P */
Object more_than_one_designation_in_vector_p(designation_or_designations)
    Object designation_or_designations;
{
    x_note_fn_call(219,75);
    if (CONSP(designation_or_designations))
	return VALUES_1(EQ(CAR(designation_or_designations),Qcm) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* AT-LEAST-ONE-DESIGNATION-IN-VECTOR-P */
Object at_least_one_designation_in_vector_p(designation_or_designations)
    Object designation_or_designations;
{
    x_note_fn_call(219,76);
    if (designation_or_designations)
	return VALUES_1( !EQ(designation_or_designations,Qnone) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* SEND-CREATE-NEW-EXTERNALLY-SIMULATED-OBJECT */
Object send_create_new_externally_simulated_object(external_simulation_object,
	    initialization_values)
    Object external_simulation_object, initialization_values;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, initialization_value, ab_loop_list_;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(219,77);
    current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)14L),(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
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
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_new_externally_simulated_object(external_simulation_object);
				initialization_value = Nil;
				ab_loop_list_ = initialization_values;
			      next_loop:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop;
				initialization_value = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				send_icp_simulation_initialization_value(initialization_value);
				goto next_loop;
			      end_loop:;
				temp = 
					send_icp_end_simulation_initialization_vector_for_object();
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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

static Object string_constant_12;  /* "ICP connection to external simulator is broken." */

/* WARN-OF-LOSS-OF-CONNECTION-TO-EXTERNAL-SIMULATOR */
Object warn_of_loss_of_connection_to_external_simulator(icp_socket)
    Object icp_socket;
{
    x_note_fn_call(219,78);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)2L),string_constant_12);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

static Object Qno_work_done_yet_for_this_cycle;  /* no-work-done-yet-for-this-cycle */

static Object Qwork_completed_for_this_cycle;  /* work-completed-for-this-cycle */

/* WORK-ON-EXTERNAL-SIMULATOR-TASKS */
Object work_on_external_simulator_tasks()
{
    Object temp, svref_arg_1, svref_new_value;

    x_note_fn_call(219,79);
    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)16L);
    if (EQ(temp,Qno_work_done_yet_for_this_cycle)) {
	handle_updates_to_externally_simulated_entities();
	if ( 
		!TRUEP(external_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)26L))) && execute_external_simulation_cycle_qm()) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    svref_new_value = ISVREF(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)26L),(SI_Long)1L);
	    SVREF(svref_arg_1,FIX((SI_Long)27L)) = svref_new_value;
	    return work_on_next_externally_simulated_entity(0);
	}
	else {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)16L)) = 
		    Qwork_completed_for_this_cycle;
	    return end_external_simulation_cycle();
	}
    }
    else
	return VALUES_1(Nil);
}

/* EXECUTE-EXTERNAL-SIMULATION-CYCLE? */
Object execute_external_simulation_cycle_qm()
{
    Object variable_group_update_structure_qm;

    x_note_fn_call(219,80);
    variable_group_update_structure_qm = 
	    get_non_override_variable_group_update_structure(Current_model_runtime_info_qm);
    if (variable_group_update_structure_qm)
	return VALUES_1(ISVREF(variable_group_update_structure_qm,
		(SI_Long)4L));
    else
	return VALUES_1(Nil);
}

static Object Qwaiting_for_values;  /* waiting-for-values */

/* WORK-ON-NEXT-EXTERNALLY-SIMULATED-ENTITY */
Object work_on_next_externally_simulated_entity varargs_1(int, n)
{
    Object sending_all_at_once_qm, next_entity_set_structure_qm, next_entity;
    Object svref_arg_1, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(219,81);
    INIT_ARGS_nonrelocating();
    sending_all_at_once_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    next_entity_set_structure_qm = Nil;
    next_entity = Nil;
  next_loop:
    next_entity_set_structure_qm = ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)27L);
    if ( !TRUEP(next_entity_set_structure_qm))
	goto end_loop;
    next_entity = ISVREF(next_entity_set_structure_qm,(SI_Long)3L);
    svref_arg_1 = Current_model_runtime_info_qm;
    svref_new_value = ISVREF(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)27L),(SI_Long)1L);
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = svref_new_value;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)15L) ? 
	    TRUEP(begin_simulating_object_externally(get_slot_value_function(next_entity,
	    Qexternal_simulation_definition_for_entity,Nil),next_entity)) :
	     
	    TRUEP(create_new_externally_simulated_object(get_slot_value_function(next_entity,
	    Qexternal_simulation_definition_for_entity,Nil),next_entity))) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Qwaiting_for_values;
	return VALUES_0();
    }
    goto next_loop;
  end_loop:
    if (sending_all_at_once_qm) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)16L)) = Qwork_completed_for_this_cycle;
    }
    else
	end_external_work_for_cycle();
    return VALUES_1(Qnil);
}

/* END-EXTERNAL-WORK-FOR-CYCLE */
Object end_external_work_for_cycle()
{
    Object svref_arg_1;

    x_note_fn_call(219,82);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)16L)) = Qwork_completed_for_this_cycle;
    if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,(SI_Long)15L))) {
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)15L)) = T;
    }
    return end_external_simulation_cycle();
}

/* SEND-ALL-INPUT-VALUES-TO-EXTERNAL-SIMULATOR */
Object send_all_input_values_to_external_simulator()
{
    Object temp, temp_1, svref_new_value, current_icp_port, current_icp_socket;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(219,83);
    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)16L);
    if (EQ(temp,Qno_work_done_yet_for_this_cycle)) {
	handle_updates_to_externally_simulated_entities();
	if (execute_external_simulation_cycle_qm()) {
	    if ( 
		    !TRUEP(external_set_empty_qm(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)26L)))) {
		temp_1 = Current_model_runtime_info_qm;
		svref_new_value = 
			ISVREF(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)26L),(SI_Long)1L);
		SVREF(temp_1,FIX((SI_Long)27L)) = svref_new_value;
	      next_loop:
		if ( ! !EQ(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)16L),Qwork_completed_for_this_cycle))
		    goto end_loop;
		work_on_next_externally_simulated_entity(1,T);
		goto next_loop;
	      end_loop:
		temp_1 = Current_model_runtime_info_qm;
		SVREF(temp_1,FIX((SI_Long)16L)) = Qwaiting_for_values;
		if ( !TRUEP(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)15L)))
		    send_connection_information_to_external_simulator();
		current_icp_port = 
			ISVREF(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)14L),(SI_Long)4L);
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
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp = 
						    send_icp_end_simulation_input_for_cycle();
					    end_icp_message_group();
					}
					else
					    temp = Nil;
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    aref_new_value);
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    aref_new_value);
					}
					result = VALUES_1(temp);
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
	    else {
		temp_1 = Current_model_runtime_info_qm;
		SVREF(temp_1,FIX((SI_Long)16L)) = Qwaiting_for_values;
		send_speedup_input();
		current_icp_port = 
			ISVREF(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)14L),(SI_Long)4L);
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
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp = 
						    send_icp_end_simulation_input_for_cycle();
					    end_icp_message_group();
					}
					else
					    temp = Nil;
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    aref_new_value);
					    temp_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(temp_1,
						    (SI_Long)0L,
						    aref_new_value);
					}
					result = VALUES_1(temp);
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
	}
	else {
	    temp_1 = Current_model_runtime_info_qm;
	    SVREF(temp_1,FIX((SI_Long)16L)) = Qwork_completed_for_this_cycle;
	    return end_external_simulation_cycle();
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qsend_connection_information_to_external_simulator_1;  /* send-connection-information-to-external-simulator-1 */

/* SEND-CONNECTION-INFORMATION-TO-EXTERNAL-SIMULATOR */
Object send_connection_information_to_external_simulator()
{
    x_note_fn_call(219,84);
    return for_each_element_in_external_set(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)26L),
	    Qsend_connection_information_to_external_simulator_1);
}

/* SEND-CONNECTION-INFORMATION-TO-EXTERNAL-SIMULATOR-1 */
Object send_connection_information_to_external_simulator_1(externally_simulated_entity)
    Object externally_simulated_entity;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(219,85);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(externally_simulated_entity,
	    (SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
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
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)3L),
	      externally_simulated_entity))
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      connection = ab_connection_;
      get_and_send_info_for_connection(connection,
	      externally_simulated_entity,T);
      goto next_loop;
    end_loop_2:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(externally_simulated_entity,
	    (SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)6L)) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    connection = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = 
		  ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L));
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop_3:
    next_loop_4:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
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
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_5:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop_3;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_5;
	    end_loop_3:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_ 
	      && EQ(ISVREF(ab_connection_,(SI_Long)2L),
	      externally_simulated_entity))
	  goto end_2;
      goto next_loop_4;
    end_loop_4:
    end_2:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_5;
      connection = ab_connection_;
      get_and_send_info_for_connection(connection,
	      externally_simulated_entity,Nil);
      goto next_loop_3;
    end_loop_5:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object string_constant_13;  /* "" */

/* GET-AND-SEND-INFO-FOR-CONNECTION */
Object get_and_send_info_for_connection(connection,
	    externally_simulated_entity,output_connection_qm)
    Object connection, externally_simulated_entity, output_connection_qm;
{
    Object opposite_end_info_triples, connection_paths, local_port_name_string;
    Object opposite_end_entity_to_send, opposite_end_port_name_string;
    Object opposite_end_entity, port_name_list, ab_loop_list_, connection_path;
    Object ab_loop_list__1, opposite_end_entity_externally_simulated_qm;
    Object ab_loop_desetq_, temp;
    SI_Long directionality;
    Object result;

    x_note_fn_call(219,86);
    opposite_end_info_triples = Nil;
    connection_paths = Nil;
    local_port_name_string = tformat_text_string(2,string_constant_9,
	    get_port_name_given_block_and_connection(2,
	    externally_simulated_entity,connection));
    directionality = (SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)7L)) 
	    & (SI_Long)1L) ? (SI_Long)0L : (SI_Long)1L;
    result = get_info_for_connection_and_entity(connection,
	    externally_simulated_entity);
    MVS_2(result,opposite_end_info_triples,connection_paths);
    opposite_end_entity_to_send = Nil;
    opposite_end_port_name_string = Nil;
    opposite_end_entity = Nil;
    port_name_list = Nil;
    ab_loop_list_ = opposite_end_info_triples;
    connection_path = Nil;
    ab_loop_list__1 = connection_paths;
    opposite_end_entity_externally_simulated_qm = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    opposite_end_entity = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    port_name_list = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    connection_path = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    opposite_end_entity_externally_simulated_qm = 
	    get_property_value_in_object_configuration(opposite_end_entity,
	    Qexternal_simulation,Nil);
    if (output_connection_qm ||  
	    !TRUEP(opposite_end_entity_externally_simulated_qm)) {
	if (opposite_end_entity_externally_simulated_qm) {
	    opposite_end_entity_to_send = opposite_end_entity;
	    temp = CAR(port_name_list);
	    if (temp);
	    else
		temp = Qnone;
	    opposite_end_port_name_string = tformat_text_string(2,
		    string_constant_9,temp);
	}
	else {
	    opposite_end_entity_to_send = externally_simulated_entity;
	    opposite_end_port_name_string = tformat_text_string(1,
		    string_constant_13);
	}
	send_info_for_this_connection_path(output_connection_qm,
		FIX(directionality),externally_simulated_entity,
		local_port_name_string,opposite_end_entity_to_send,
		opposite_end_port_name_string,connection_path);
	reclaim_text_string(opposite_end_port_name_string);
    }
    goto next_loop;
  end_loop:;
    reclaim_text_string(local_port_name_string);
    reclaim_eval_tree_1(opposite_end_info_triples);
    return reclaim_eval_tree_1(connection_paths);
}

static Object Qobject;             /* object */

static Object Qboth;               /* both */

static Object Qsave_path;          /* save-path */

/* GET-INFO-FOR-CONNECTION-AND-ENTITY */
Object get_info_for_connection_and_entity(connection,entity)
    Object connection, entity;
{
    Object entities, connections, current_connection_path;
    Object connections_in_connection_paths, connections_to_be_excluded_qm;
    Object entities_to_be_excluded_qm, entities_or_triples_found_in_search;
    Declare_special(5);
    Object result;

    x_note_fn_call(219,87);
    entities = Nil;
    connections = Nil;
    current_connection_path = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_connection_path,Qcurrent_connection_path,current_connection_path,
	    4);
      connections_in_connection_paths = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Connections_in_connection_paths,Qconnections_in_connection_paths,connections_in_connection_paths,
	      3);
	connections_to_be_excluded_qm = Nil;
	entities_to_be_excluded_qm = Nil;
	entities_or_triples_found_in_search = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Entities_or_triples_found_in_search,Qentities_or_triples_found_in_search,entities_or_triples_found_in_search,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Entities_to_be_excluded_qm,Qentities_to_be_excluded_qm,entities_to_be_excluded_qm,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(Connections_to_be_excluded_qm,Qconnections_to_be_excluded_qm,connections_to_be_excluded_qm,
		    0);
	      search_for_directly_connected_entities_for_connection(entity,
		      Qobject,connection,Nil,Qboth,Nil,Nil,Qsave_path);
	      entities = Entities_or_triples_found_in_search;
	      connections = Connections_in_connection_paths;
	      clear_connections_to_be_excluded(Connections_to_be_excluded_qm);
	      clear_entities_to_be_excluded(Entities_to_be_excluded_qm);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(entities,connections);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SEND-INFO-FOR-THIS-CONNECTION-PATH */
Object send_info_for_this_connection_path(output_connection_qm,
	    directionality,externally_simulated_entity,
	    local_port_name_string,opposite_end_entity,
	    opposite_end_port_name_string,connection_path)
    Object output_connection_qm, directionality, externally_simulated_entity;
    Object local_port_name_string, opposite_end_entity;
    Object opposite_end_port_name_string, connection_path;
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
    Object result;

    x_note_fn_call(219,88);
    current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)14L),(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
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
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				temp = output_connection_qm ? 
					send_info_for_each_connection_in_path(get_slot_value_if_any_function(externally_simulated_entity,
					Qexternal_simulation_object_structure,
					Nil),
					get_slot_value_if_any_function(opposite_end_entity,
					Qexternal_simulation_object_structure,
					Nil),directionality,
					local_port_name_string,
					opposite_end_port_name_string,
					connection_path) : 
					send_info_for_each_connection_in_path(get_slot_value_if_any_function(opposite_end_entity,
					Qexternal_simulation_object_structure,
					Nil),
					get_slot_value_if_any_function(externally_simulated_entity,
					Qexternal_simulation_object_structure,
					Nil),directionality,
					opposite_end_port_name_string,
					local_port_name_string,
					connection_path);
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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

/* SEND-INFO-FOR-EACH-CONNECTION-IN-PATH */
Object send_info_for_each_connection_in_path(input_end_object,
	    output_end_object,directional_qm,
	    port_name_for_input_end_object,port_name_for_output_end_object,
	    connection_path)
    Object input_end_object, output_end_object, directional_qm;
    Object port_name_for_input_end_object, port_name_for_output_end_object;
    Object connection_path;
{
    Object connection, ab_loop_list_;
    Object external_simulation_object_for_connection_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    Object externally_simulated_connections_in_connection_path;
    Object externally_simulated_connection;
    SI_Long number_left_in_path;

    x_note_fn_call(219,89);
    connection = Nil;
    ab_loop_list_ = connection_path;
    external_simulation_object_for_connection_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    external_simulation_object_for_connection_qm = 
	    get_slot_value_if_any_function(connection,
	    Qexternal_simulation_object_structure,Nil);
    ab_loopvar__2 = external_simulation_object_for_connection_qm ? 
	    eval_cons_1(external_simulation_object_for_connection_qm,Nil) :
	     Nil;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    externally_simulated_connections_in_connection_path = ab_loopvar_;
    goto end_1;
    externally_simulated_connections_in_connection_path = Qnil;
  end_1:;
    if (externally_simulated_connections_in_connection_path) {
	number_left_in_path = 
		IFIX(FIXNUM_SUB1(length(externally_simulated_connections_in_connection_path)));
	externally_simulated_connection = Nil;
	ab_loop_list_ = externally_simulated_connections_in_connection_path;
      next_loop_1:
	if (number_left_in_path < (SI_Long)0L)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	externally_simulated_connection = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	send_icp_connection_info(input_end_object,output_end_object,
		directional_qm,port_name_for_input_end_object,
		port_name_for_output_end_object,
		externally_simulated_connection,FIX(number_left_in_path));
	number_left_in_path = number_left_in_path - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
    }
    else
	send_icp_connection_info(input_end_object,output_end_object,
		directional_qm,port_name_for_input_end_object,
		port_name_for_output_end_object,input_end_object,
		FIX((SI_Long)-1L));
    return reclaim_eval_list_1(externally_simulated_connections_in_connection_path);
}

/* HANDLE-UPDATES-TO-EXTERNALLY-SIMULATED-ENTITIES */
Object handle_updates_to_externally_simulated_entities()
{
    x_note_fn_call(219,90);
    return VALUES_1(Nil);
}

static Object Qinput;              /* input */

/* BEGIN-SIMULATING-OBJECT-EXTERNALLY */
Object begin_simulating_object_externally(external_simulation_definition,
	    object)
    Object external_simulation_definition, object;
{
    Object current_computation_flags, alist, current_computation_frame;
    Object current_simulation_runtime_structure, temp;
    Object input_value_designations, message_keywords, input_values;
    Object svref_arg_1, designation, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,91);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    2);
      Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
	      (SI_Long)16L);
      alist = 
	      simulate_cons_1(simulate_cons_1(ISVREF(external_simulation_definition,
	      (SI_Long)20L),object),Nil);
      current_computation_frame = external_simulation_definition;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      1);
	current_simulation_runtime_structure = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
		0);
	  temp = ISVREF(external_simulation_definition,(SI_Long)22L);
	  input_value_designations = get_attribute_designations(CAR(temp));
	  temp = ISVREF(external_simulation_definition,(SI_Long)21L);
	  message_keywords = get_attribute_designations(CAR(temp));
	  input_values = Nil;
	  svref_arg_1 = Current_model_runtime_info_qm;
	  SVREF(svref_arg_1,FIX((SI_Long)2L)) = Qcalculating_state_variables;
	  designation = Nil;
	  ab_loop_list_ = input_value_designations;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  designation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loopvar__2 = 
		  simulate_cons_1(sim_eval_variable_for_designation(designation,
		  alist),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop:
	  input_values = ab_loopvar_;
	  goto end_1;
	  input_values = Qnil;
	end_1:;
	  if (external_simulator_input_values_ok_qm(input_values,object,
		  Qinput)) {
	      send_input_vector_for_object_simulated_externally(get_slot_value_if_any_function(object,
		      Qexternal_simulation_object_structure,Nil),
		      message_keywords,input_values);
	      temp = T;
	  }
	  else
	      temp = Nil;
	  reclaim_simulate_tree_1(alist);
	  reclaim_simulate_list_1(input_value_designations);
	  reclaim_simulate_list_1(input_values);
	  reclaim_simulate_list_1(message_keywords);
	  result = VALUES_1(temp);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_14;  /* "Problem encountered simulating the entity ~NF externally.  The ~a
				    * value ~a is not a number."
				    */

/* EXTERNAL-SIMULATOR-INPUT-VALUES-OK? */
Object external_simulator_input_values_ok_qm(input_values,entity,
	    input_or_initialization)
    Object input_values, entity, input_or_initialization;
{
    Object input_value, ab_loop_list_;

    x_note_fn_call(219,92);
    input_value = Nil;
    ab_loop_list_ = input_values;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    input_value = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !NUMBERP(input_value)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(5,FIX((SI_Long)2L),string_constant_14,entity,
		    input_or_initialization,input_value);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* SEND-INPUT-VECTOR-FOR-OBJECT-SIMULATED-EXTERNALLY */
Object send_input_vector_for_object_simulated_externally(external_simulation_object,
	    keywords,input_values)
    Object external_simulation_object, keywords, input_values;
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, keyword, ab_loop_list_, keyword_string;
    Object input_value;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);
    Object result;

    x_note_fn_call(219,93);
    current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
	    (SI_Long)14L),(SI_Long)4L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
	    11);
      current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
	      10);
	temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		(SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
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
				gensymed_symbol_2 = g2ext_unix_time_as_float();
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					gensymed_symbol_2);
			    }
			    if (icp_connection_open_p(Current_icp_socket) 
				    &&  
				    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					{
				send_icp_begin_simulation_input_vector_for_object(external_simulation_object);
				keyword = Nil;
				ab_loop_list_ = keywords;
				keyword_string = Nil;
			      next_loop:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop;
				keyword = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				keyword_string = tformat_text_string(2,
					string_constant_9,keyword);
				send_icp_simulation_keyword(keyword_string);
				reclaim_text_string(keyword_string);
				goto next_loop;
			      end_loop:;
				input_value = Nil;
				ab_loop_list_ = input_values;
			      next_loop_1:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop_1;
				input_value = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				send_icp_simulation_input_value(input_value);
				goto next_loop_1;
			      end_loop_1:;
				temp = 
					send_icp_end_simulation_input_vector_for_object();
				end_icp_message_group();
			    }
			    else
				temp = Nil;
			    if (Profiling_enabled_qm) {
				gensymed_symbol_3 = g2ext_unix_time_as_float();
				gensymed_symbol_4 = 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)2L),(SI_Long)0L);
				gensymed_symbol_5 = gensymed_symbol_3 - 
					gensymed_symbol_4;
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)6L);
				aref_new_value = gensymed_symbol_5 + 
					DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					(SI_Long)6L),(SI_Long)0L);
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
				aref_arg_1 = ISVREF(Profiling_enabled_qm,
					(SI_Long)2L);
				aref_new_value = gensymed_symbol ? 
					gensymed_symbol_1 + 
					gensymed_symbol_5 + 
					(gensymed_symbol_4 - 
					gensymed_symbol_2) : gensymed_symbol_3;
				DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,
					aref_new_value);
			    }
			    result = VALUES_1(temp);
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

/* SHUTDOWN-EXTERNALLY-SIMULATED-PORTION-OF-MODEL */
Object shutdown_externally_simulated_portion_of_model()
{
    Object temp, current_icp_port, current_icp_socket, temp_1;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(219,94);
    temp = Current_model_runtime_info_qm;
    SVREF(temp,FIX((SI_Long)27L)) = Nil;
    shutdown_speedup_simulation();
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)14L)) {
	current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)14L),(SI_Long)4L);
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
				    send_icp_shutdown_external_simulator();
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
	shutdown_icp_socket_connection(1,
		ISVREF(Current_model_runtime_info_qm,(SI_Long)14L));
	temp = Current_model_runtime_info_qm;
	return VALUES_1(SVREF(temp,FIX((SI_Long)14L)) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsend_icp_speedup_begin_tagnames;  /* send-icp-speedup-begin-tagnames */

static Object Qspeedup_begin_tagnames;  /* speedup-begin-tagnames */

/* SEND-ICP-SPEEDUP-BEGIN-TAGNAMES */
Object send_icp_speedup_begin_tagnames()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,95);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_begin_tagnames;
	  }
	  start_writing_icp_message(FIX((SI_Long)251L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_begin_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_begin_tagnames,string_constant_3,
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
	    if ( !EQ(Qsend_icp_speedup_begin_tagnames,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_begin_tagnames,top,Nil);
		goto end_send_icp_speedup_begin_tagnames;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_begin_tagnames;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)251L)))) {
	      resumable_icp_push(Qsend_icp_speedup_begin_tagnames);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_begin_tagnames;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_begin_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_begin_tagnames,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_begin_tagnames:
    return result;
}

/* HANDLE-ICP-SPEEDUP-BEGIN-TAGNAMES--BODY */
Object handle_icp_speedup_begin_tagnames__body()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, svref_arg_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,96);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)34L)) = Nil;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)35L)) = Nil;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_begin_tagnames;  /* handle-icp-speedup-begin-tagnames */

/* HANDLE-ICP-SPEEDUP-BEGIN-TAGNAMES */
Object handle_icp_speedup_begin_tagnames()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(219,97);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_begin_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_begin_tagnames__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_begin_tagnames,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_begin_tagnames__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_begin_tagnames,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_begin_tagnames,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_begin_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_begin_tagnames__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_begin_tagnames,string_constant_3,
			  Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_begin_tagnames__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_speedup_input_or_output_tagnames;  /* send-icp-speedup-input-or-output-tagnames */

static Object Qspeedup_input_or_output_tagnames;  /* speedup-input-or-output-tagnames */

static Object Qinput_or_output_tagnames;  /* input-or-output-tagnames */

/* SEND-ICP-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES */
Object send_icp_speedup_input_or_output_tagnames(input_or_output_tagnames)
    Object input_or_output_tagnames;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,98);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_speedup_input_or_output_tagnames;
	  }
	  start_writing_icp_message(FIX((SI_Long)252L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qspeedup_input_or_output_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qinput_or_output_tagnames,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = 
			      write_icp_text_string(input_or_output_tagnames);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_or_output_tagnames,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = 
			    write_icp_text_string(input_or_output_tagnames);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_input_or_output_tagnames,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinput_or_output_tagnames,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = 
			write_icp_text_string(input_or_output_tagnames);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinput_or_output_tagnames,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_text_string(input_or_output_tagnames);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_speedup_input_or_output_tagnames,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_input_or_output_tagnames,top,Nil);
		goto end_send_icp_speedup_input_or_output_tagnames;
	    }
	}
	input_or_output_tagnames = (resumable_icp_state_1 ? 
		TRUEP(Resumable_icp_state) : TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : input_or_output_tagnames;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = 
		      Qsend_icp_speedup_input_or_output_tagnames;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)252L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,
			  Qspeedup_input_or_output_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,
				Qinput_or_output_tagnames,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,
			      write_icp_text_string(input_or_output_tagnames))) 
				  {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qinput_or_output_tagnames,
				  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,
			write_icp_text_string(input_or_output_tagnames))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_input_or_output_tagnames,
			    string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qinput_or_output_tagnames,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,
			write_icp_text_string(input_or_output_tagnames))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qinput_or_output_tagnames,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,
		  write_icp_text_string(input_or_output_tagnames))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(input_or_output_tagnames);
	      resumable_icp_push(Qsend_icp_speedup_input_or_output_tagnames);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_input_or_output_tagnames;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_input_or_output_tagnames:
    return result;
}

static Object array_constant;      /* # */

/* HANDLE-ICP-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES--BODY */
Object handle_icp_speedup_input_or_output_tagnames__body(input_or_output_tagnames)
    Object input_or_output_tagnames;
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, svref_arg_1, svref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,99);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    svref_new_value = string_equalw(input_or_output_tagnames,
		    array_constant);
	    SVREF(svref_arg_1,FIX((SI_Long)36L)) = svref_new_value;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_input_or_output_tagnames;  /* handle-icp-speedup-input-or-output-tagnames */

/* HANDLE-ICP-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES */
Object handle_icp_speedup_input_or_output_tagnames()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, input_or_output_tagnames;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,100);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qspeedup_input_or_output_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qinput_or_output_tagnames,string_constant_5,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qinput_or_output_tagnames,
				string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    input_or_output_tagnames = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  input_or_output_tagnames = read_icp_text_string();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_speedup_input_or_output_tagnames__body(input_or_output_tagnames);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(input_or_output_tagnames);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_input_or_output_tagnames,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qinput_or_output_tagnames,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qinput_or_output_tagnames,string_constant_5,
			      Qargument,T,result_of_read,Nil,Nil);
		  input_or_output_tagnames = result_of_read;
		POP_SPECIAL();
	    }
	    else
		input_or_output_tagnames = read_icp_text_string();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_input_or_output_tagnames__body(input_or_output_tagnames);
	    POP_SPECIAL();
	    reclaim_text_string(input_or_output_tagnames);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_input_or_output_tagnames,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_input_or_output_tagnames,top,Nil);
		goto end_handle_icp_speedup_input_or_output_tagnames;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,
			Qspeedup_input_or_output_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  input_or_output_tagnames = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,
			      Qinput_or_output_tagnames,string_constant_5,
			      Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_speedup_input_or_output_tagnames);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_speedup_input_or_output_tagnames;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qinput_or_output_tagnames,
				string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    input_or_output_tagnames = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_input_or_output_tagnames);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_input_or_output_tagnames;
		  }
		  input_or_output_tagnames = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_speedup_input_or_output_tagnames__body(input_or_output_tagnames);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(input_or_output_tagnames);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_input_or_output_tagnames,
			  string_constant_3,Qmessage,Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		input_or_output_tagnames = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,
			    Qinput_or_output_tagnames,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_input_or_output_tagnames);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_input_or_output_tagnames;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qinput_or_output_tagnames,string_constant_5,
			      Qargument,T,result_of_read,Nil,Nil);
		  input_or_output_tagnames = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_speedup_input_or_output_tagnames);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_speedup_input_or_output_tagnames;
		}
		input_or_output_tagnames = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_input_or_output_tagnames__body(input_or_output_tagnames);
	    POP_SPECIAL();
	    reclaim_text_string(input_or_output_tagnames);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_speedup_input_or_output_tagnames:
    return result;
}

static Object Qsend_icp_speedup_tagname;  /* send-icp-speedup-tagname */

static Object Qspeedup_tagname;    /* speedup-tagname */

static Object Qtagname;            /* tagname */

/* SEND-ICP-SPEEDUP-TAGNAME */
Object send_icp_speedup_tagname(tagname)
    Object tagname;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,101);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_tagname;
	  }
	  start_writing_icp_message(FIX((SI_Long)253L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_tagname,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qtagname,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_text_string(tagname);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qtagname,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_text_string(tagname);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_tagname,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qtagname,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_text_string(tagname);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qtagname,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_text_string(tagname);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_speedup_tagname,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_tagname,top,Nil);
		goto end_send_icp_speedup_tagname;
	    }
	}
	tagname = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : tagname;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_tagname;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)253L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_tagname,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qtagname,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_text_string(tagname))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qtagname,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_text_string(tagname))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_tagname,string_constant_3,Qmessage,
			    Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qtagname,
			  string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_text_string(tagname))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qtagname,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_text_string(tagname))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(tagname);
	      resumable_icp_push(Qsend_icp_speedup_tagname);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_tagname;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_tagname:
    return result;
}

/* HANDLE-ICP-SPEEDUP-TAGNAME--BODY */
Object handle_icp_speedup_tagname__body(tagname)
    Object tagname;
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, temp, temp_1, temp_2;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,102);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)35L)) {
		temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)35L);
		temp_1 = 
			slot_value_cons_1(convert_speedup_tagname_to_designation(tagname),
			Nil);
		M_CDR(temp) = temp_1;
		temp = Current_model_runtime_info_qm;
		temp_2 = ISVREF(Current_model_runtime_info_qm,(SI_Long)35L);
		temp_1 = CDR(temp_2);
		SVREF(temp,FIX((SI_Long)35L)) = temp_1;
	    }
	    else {
		temp = Current_model_runtime_info_qm;
		temp_1 = 
			slot_value_cons_1(convert_speedup_tagname_to_designation(tagname),
			Nil);
		SVREF(temp,FIX((SI_Long)34L)) = temp_1;
		temp = Current_model_runtime_info_qm;
		temp_1 = ISVREF(Current_model_runtime_info_qm,(SI_Long)34L);
		SVREF(temp,FIX((SI_Long)35L)) = temp_1;
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_tagname;  /* handle-icp-speedup-tagname */

/* HANDLE-ICP-SPEEDUP-TAGNAME */
Object handle_icp_speedup_tagname()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, tagname;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,103);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_tagname,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtagname,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_text_string();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtagname,string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    tagname = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  tagname = read_icp_text_string();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_speedup_tagname__body(tagname);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(tagname);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_tagname,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtagname,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_text_string();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtagname,string_constant_5,Qargument,T,
			      result_of_read,Nil,Nil);
		  tagname = result_of_read;
		POP_SPECIAL();
	    }
	    else
		tagname = read_icp_text_string();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_tagname__body(tagname);
	    POP_SPECIAL();
	    reclaim_text_string(tagname);
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_tagname,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_tagname,top,Nil);
		goto end_handle_icp_speedup_tagname;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_tagname,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  tagname = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qtagname,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value = read_icp_text_string();
		    if (EQ(icp_suspend_1,value)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_speedup_tagname);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_speedup_tagname;
		    }
		    result_of_read = value;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qtagname,string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    tagname = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_tagname);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_tagname;
		  }
		  tagname = value;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		handle_icp_speedup_tagname__body(tagname);
	      POP_SPECIAL();
	      result_of_read = reclaim_text_string(tagname);
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_tagname,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		tagname = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qtagname,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value = read_icp_text_string();
		  if (EQ(icp_suspend_1,value)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_tagname);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_tagname;
		  }
		  result_of_read = value;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),
			      Qtagname,string_constant_5,Qargument,T,
			      result_of_read,Nil,Nil);
		  tagname = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value = read_icp_text_string();
		if (EQ(icp_suspend_1,value)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_speedup_tagname);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_speedup_tagname;
		}
		tagname = value;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_tagname__body(tagname);
	    POP_SPECIAL();
	    reclaim_text_string(tagname);
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_speedup_tagname:
    return result;
}

static Object Qsend_icp_speedup_end_tagnames;  /* send-icp-speedup-end-tagnames */

static Object Qspeedup_end_tagnames;  /* speedup-end-tagnames */

/* SEND-ICP-SPEEDUP-END-TAGNAMES */
Object send_icp_speedup_end_tagnames()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,104);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_end_tagnames;
	  }
	  start_writing_icp_message(FIX((SI_Long)254L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_end_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_end_tagnames,string_constant_3,
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
	    if ( !EQ(Qsend_icp_speedup_end_tagnames,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_end_tagnames,top,Nil);
		goto end_send_icp_speedup_end_tagnames;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_end_tagnames;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)254L)))) {
	      resumable_icp_push(Qsend_icp_speedup_end_tagnames);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_end_tagnames;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_end_tagnames,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_end_tagnames,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_end_tagnames:
    return result;
}

/* HANDLE-ICP-SPEEDUP-END-TAGNAMES--BODY */
Object handle_icp_speedup_end_tagnames__body()
{
    x_note_fn_call(219,105);
    define_speedup_end_tagnames();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_end_tagnames;  /* handle-icp-speedup-end-tagnames */

/* HANDLE-ICP-SPEEDUP-END-TAGNAMES */
Object handle_icp_speedup_end_tagnames()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(219,106);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_end_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_end_tagnames__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_end_tagnames,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_end_tagnames__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_end_tagnames,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_end_tagnames,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_end_tagnames,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_end_tagnames__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_end_tagnames,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_end_tagnames__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

/* DEFINE-SPEEDUP-END-TAGNAMES */
Object define_speedup_end_tagnames()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, temp, current_icp_port;
    Object current_icp_socket, temp_1, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, current_computation_flags;
    Object current_computation_frame, designation, ab_loop_list_;
    Object variable_or_parameter_qm, sub_class_bit_vector, simulation_info_qm;
    Object new_variable_simulation_runtime_structure, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_6, gensymed_symbol_7, gensymed_symbol_8;
    char temp_2;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(14);
    Object result;

    x_note_fn_call(219,107);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    13);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      12);
	if (Current_model_runtime_info_qm) {
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)37L)) = Nil;
	    temp = Current_model_runtime_info_qm;
	    SVREF(temp,FIX((SI_Long)38L)) = Nil;
	    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)36L))
		change_vector_to_external_simulator(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)34L));
	    else
		change_vector_from_external_simulator(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)34L));
	    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)36L)) {
		send_speedup_input();
		current_icp_port = 
			ISVREF(ISVREF(Current_model_runtime_info_qm,
			(SI_Long)14L),(SI_Long)4L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp_1 = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp_1);
		    else
			temp_1 = EQ(ISVREF(Current_icp_socket,
				(SI_Long)25L),Qtelewindows) ? T : Nil;
		    disable_resumability = temp_1;
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
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp_1 = 
						    send_icp_end_simulation_input_for_cycle();
					    end_icp_message_group();
					}
					else
					    temp_1 = Nil;
					if (Profiling_enabled_qm) {
					    gensymed_symbol_3 = 
						    g2ext_unix_time_as_float();
					    gensymed_symbol_4 = 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L),(SI_Long)0L);
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					    temp = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(temp,
						    (SI_Long)0L,
						    aref_new_value);
					}
					result = VALUES_1(temp_1);
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
	    else {
		current_computation_flags = Current_computation_flags;
		current_computation_frame = Simulation_parameters;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
			1);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			  0);
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | 
			    (SI_Long)16L);
		    designation = Nil;
		    ab_loop_list_ = current_vector_from_external_simulator();
		    variable_or_parameter_qm = Nil;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    designation = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    variable_or_parameter_qm = 
			    evaluate_designation(designation,Nil);
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(variable_or_parameter_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_6 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_7 = (SI_Long)1L;
			gensymed_symbol_8 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_7 = gensymed_symbol_7 << 
				gensymed_symbol_8;
			gensymed_symbol_6 = gensymed_symbol_6 & 
				gensymed_symbol_7;
			temp_2 = (SI_Long)0L < gensymed_symbol_6;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if ( !temp_2)
			speedup_tagname_not_variable(designation,
				variable_or_parameter_qm);
		    else {
			simulation_info_qm = 
				get_lookup_slot_value_given_default(variable_or_parameter_qm,
				Qsimulation_info_qm,Nil);
			if ((simulation_info_qm ? 
				TRUEP(ISVREF(simulation_info_qm,
				(SI_Long)1L)) : TRUEP(Nil)) ?  
				!TRUEP(externally_simulated_variable_p(variable_or_parameter_qm)) 
				: TRUEP(Nil))
			    speedup_simulation_conflict(designation,
				    variable_or_parameter_qm);
			else {
			    make_simulation_info_for_speedup_variable(variable_or_parameter_qm);
			    new_variable_simulation_runtime_structure = 
				    make_and_initialize_variable_simulation_runtime_structure(variable_or_parameter_qm);
			    if (ISVREF(Current_model_runtime_info_qm,
				    (SI_Long)38L)) {
				temp = 
					ISVREF(Current_model_runtime_info_qm,
					(SI_Long)38L);
				temp_3 = 
					simulate_cons_1(new_variable_simulation_runtime_structure,
					Nil);
				M_CDR(temp) = temp_3;
				temp = Current_model_runtime_info_qm;
				temp_1 = 
					ISVREF(Current_model_runtime_info_qm,
					(SI_Long)38L);
				temp_3 = CDR(temp_1);
				SVREF(temp,FIX((SI_Long)38L)) = temp_3;
			    }
			    else {
				temp = Current_model_runtime_info_qm;
				temp_3 = 
					simulate_cons_1(new_variable_simulation_runtime_structure,
					Nil);
				SVREF(temp,FIX((SI_Long)37L)) = temp_3;
				temp = Current_model_runtime_info_qm;
				temp_3 = 
					ISVREF(Current_model_runtime_info_qm,
					(SI_Long)37L);
				SVREF(temp,FIX((SI_Long)38L)) = temp_3;
			    }
			    begin_collecting_data_for_simulated_variable_if_appropriate(variable_or_parameter_qm);
			}
		    }
		    goto next_loop;
		  end_loop:
		    result = VALUES_1(Qnil);
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qexternal;           /* external */

/* MAKE-SIMULATION-INFO-FOR-SPEEDUP-VARIABLE */
Object make_simulation_info_for_speedup_variable(variable_or_parameter)
    Object variable_or_parameter;
{
    Object simulation_info_qm;

    x_note_fn_call(219,108);
    simulation_info_qm = get_or_make_simulation_info(variable_or_parameter,T);
    set_non_savable_lookup_slot_value(variable_or_parameter,
	    Qsimulation_info_qm,simulation_info_qm);
    return VALUES_1(SVREF(simulation_info_qm,FIX((SI_Long)2L)) = Qexternal);
}

static Object Qsend_icp_speedup_begin_values;  /* send-icp-speedup-begin-values */

static Object Qspeedup_begin_values;  /* speedup-begin-values */

/* SEND-ICP-SPEEDUP-BEGIN-VALUES */
Object send_icp_speedup_begin_values()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, result_of_write;
    Object temp_1, resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,109);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_begin_values;
	  }
	  start_writing_icp_message(FIX((SI_Long)255L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_begin_values,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_begin_values,string_constant_3,
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
	    if ( !EQ(Qsend_icp_speedup_begin_values,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_begin_values,top,Nil);
		goto end_send_icp_speedup_begin_values;
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_begin_values;
	  }
	  if (EQ(icp_suspend_1,
		      start_writing_icp_message(FIX((SI_Long)255L)))) {
	      resumable_icp_push(Qsend_icp_speedup_begin_values);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_begin_values;
	  }
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_begin_values,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
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
			    Qspeedup_begin_values,string_constant_3,
			    Qmessage,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_begin_values:
    return result;
}

/* HANDLE-ICP-SPEEDUP-BEGIN-VALUES--BODY */
Object handle_icp_speedup_begin_values__body()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, svref_arg_1, svref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,110);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    svref_arg_1 = Current_model_runtime_info_qm;
	    svref_new_value = ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)37L);
	    SVREF(svref_arg_1,FIX((SI_Long)38L)) = svref_new_value;
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_begin_values;  /* handle-icp-speedup-begin-values */

/* HANDLE-ICP-SPEEDUP-BEGIN-VALUES */
Object handle_icp_speedup_begin_values()
{
    Object tracep, byte_count_before, current_icp_read_trace_level;
    Object abort_for_icp_catcher_qm, result_of_read, temp;
    Object resumable_icp_state_1, icp_suspend_1, top;
    Declare_special(2);

    x_note_fn_call(219,111);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_begin_values,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_begin_values__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_begin_values,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_begin_values__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_begin_values,top))
		return icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_begin_values,top,Nil);
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_begin_values,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
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
		result_of_read = handle_icp_speedup_begin_values__body();
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_begin_values,string_constant_3,Qmessage,
			  Nil,result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_begin_values__body();
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    return VALUES_1(temp);
}

static Object Qsend_icp_speedup_value;  /* send-icp-speedup-value */

static Object Qspeedup_value;      /* speedup-value */

/* SEND-ICP-SPEEDUP-VALUE */
Object send_icp_speedup_value(value)
    Object value;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, tracep;
    Object byte_count_before, current_icp_write_trace_level, tracep_1;
    Object byte_count_before_1, result_of_write, temp_1, resumable_icp_state_1;
    Object icp_suspend_1, top;
    Declare_special(3);
    Object result;

    x_note_fn_call(219,112);
    if (Disable_resumability) {
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_value;
	  }
	  start_writing_icp_message(FIX((SI_Long)256L));
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qvalue,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      result_of_write = write_icp_float(value);
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qvalue,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else
		    result_of_write = write_icp_float(value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_value,string_constant_3,Qmessage,Nil,
			    Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qvalue,string_constant_5,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		result_of_write = write_icp_float(value);
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qvalue,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
	      POP_SPECIAL();
	  }
	  else
	      write_icp_float(value);
	POP_SPECIAL();
	temp_1 = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qsend_icp_speedup_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qsend_icp_speedup_value,top,Nil);
		goto end_send_icp_speedup_value;
	    }
	}
	value = (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		TRUEP(Nil)) &&  
		!TRUEP(resumable_icp_pop_list_if_end_marker()) ? 
		resumable_icp_pop() : value;
	index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
	PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
		2);
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
	      SVREF(temp,svref_arg_2) = Qsend_icp_speedup_value;
	  }
	  if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) {
	      temp_1 = resumable_icp_pop();
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
		      start_writing_icp_message(FIX((SI_Long)256L)))) {
	      resumable_icp_push(FIX((SI_Long)1L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	l2:
	  if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)2L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qspeedup_value,
			  string_constant_3,Qmessage,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      1);
		if (Icp_write_trace_cutoff_level_qm) {
		    tracep_1 = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep_1);
		    else
			tracep_1 = IFIX(Icp_write_trace_cutoff_level_qm) 
				>= (SI_Long)3L ? T : Nil;
		    if (tracep_1) {
			emit_icp_write_trace(T,Nil,Nil,Qvalue,
				string_constant_5,Qargument,Nil,Nil,Nil,Nil);
			byte_count_before_1 = 
				instantaneous_icp_writer_byte_count();
		    }
		    else
			byte_count_before_1 = Nil;
		    current_icp_write_trace_level = 
			    FIXNUM_ADD1(Current_icp_write_trace_level);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
			    0);
		      if (EQ(icp_suspend_1,write_icp_float(value))) {
			  resumable_icp_push(FIX((SI_Long)2L));
			  temp_1 = Icp_suspend;
			  POP_SPECIAL();
			  POP_SPECIAL();
			  goto end_block;
		      }
		      else
			  result_of_write = Nil;
		      if (tracep_1)
			  emit_icp_write_trace(Nil,byte_count_before_1,
				  instantaneous_icp_writer_byte_count(),
				  Qvalue,string_constant_5,Qargument,Nil,
				  Nil,Nil,Nil);
		    POP_SPECIAL();
		}
		else if (EQ(icp_suspend_1,write_icp_float(value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),
			    Qspeedup_value,string_constant_3,Qmessage,Nil,
			    Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (Icp_write_trace_cutoff_level_qm) {
	      tracep = EQ(Icp_write_trace_cutoff_level_qm,T) ? T : Nil;
	      if (tracep);
	      else
		  tracep = IFIX(Icp_write_trace_cutoff_level_qm) >= 
			  (SI_Long)3L ? T : Nil;
	      if (tracep) {
		  emit_icp_write_trace(T,Nil,Nil,Qvalue,string_constant_5,
			  Qargument,Nil,Nil,Nil,Nil);
		  byte_count_before = instantaneous_icp_writer_byte_count();
	      }
	      else
		  byte_count_before = Nil;
	      current_icp_write_trace_level = 
		      FIXNUM_ADD1(Current_icp_write_trace_level);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_write_trace_level,Qcurrent_icp_write_trace_level,current_icp_write_trace_level,
		      0);
		if (EQ(icp_suspend_1,write_icp_float(value))) {
		    resumable_icp_push(FIX((SI_Long)2L));
		    temp_1 = Icp_suspend;
		    POP_SPECIAL();
		    goto end_block;
		}
		else
		    result_of_write = Nil;
		if (tracep)
		    emit_icp_write_trace(Nil,byte_count_before,
			    instantaneous_icp_writer_byte_count(),Qvalue,
			    string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		temp_1 = result_of_write;
	      POP_SPECIAL();
	  }
	  else if (EQ(icp_suspend_1,write_icp_float(value))) {
	      resumable_icp_push(FIX((SI_Long)2L));
	      temp_1 = Icp_suspend;
	      goto end_block;
	  }
	  else
	      temp_1 = Nil;
	  goto end_block;
	end_block:
	  if (EQ(icp_suspend_1,temp_1)) {
	      resumable_icp_push(value);
	      resumable_icp_push(Qsend_icp_speedup_value);
	      result = VALUES_1(Icp_suspend);
	      POP_SPECIAL();
	      goto end_send_icp_speedup_value;
	  }
	POP_SPECIAL();
	temp_1 = Nil;
    }
    result = VALUES_1(temp_1);
  end_send_icp_speedup_value:
    return result;
}

/* HANDLE-ICP-SPEEDUP-VALUE--BODY */
Object handle_icp_speedup_value__body(value)
    Object value;
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, temp, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, type_specification, temp_1;
    Object store_managed_number_or_value_arg_1, svref_new_value;
    double store_managed_number_or_value_arg;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,113);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)38L);
	    gensymed_symbol = CAR(temp);
	    gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)16L);
	    gensymed_symbol_2 = value;
	    type_specification = 
		    type_specification_of_variable_or_parameter_value(gensymed_symbol_1);
	    if (EQ(type_specification,Qfloat) && FIXNUMP(gensymed_symbol_2)) {
		store_managed_number_or_value_arg = 
			(double)IFIX(gensymed_symbol_2);
		temp_1 = 
			store_managed_number_or_value_function(ISVREF(gensymed_symbol,
			(SI_Long)2L),
			DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
		SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
	    }
	    else {
		if (EQ(type_specification,Qinteger))
		    temp = FIXNUMP(gensymed_symbol_2) ? T : Nil;
		else if (EQ(type_specification,Qlong))
		    temp = INLINE_LONG_P(gensymed_symbol_2) != (SI_Long)0L 
			    ? T : Nil;
		else if (EQ(type_specification,Qfloat))
		    temp = FLOATP(gensymed_symbol_2) ? T : Nil;
		else if (EQ(type_specification,Qsymbol))
		    temp = gensymed_symbol_2 ? (SYMBOLP(gensymed_symbol_2) 
			    ? T : Nil) : Qnil;
		else if (EQ(type_specification,Qtext))
		    temp = text_string_p(gensymed_symbol_2);
		else if (EQ(type_specification,Qtruth_value))
		    temp = FIXNUMP(gensymed_symbol_2) && FIXNUM_LE(Falsity,
			    gensymed_symbol_2) ? 
			    (FIXNUM_LE(gensymed_symbol_2,Truth) ? T : Nil) 
			    : Qnil;
		else if (EQ(type_specification,Qboolean)) {
		    if (FIXNUMP(gensymed_symbol_2)) {
			temp = FIXNUM_EQ(gensymed_symbol_2,Falsity) ? T : Nil;
			if (temp);
			else
			    temp = FIXNUM_EQ(gensymed_symbol_2,Truth) ? T :
				     Nil;
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
			temp = FIXNUMP(gensymed_symbol_2) ? T : Nil;
		}
		else
		    temp = Nil;
		if (temp) {
		    store_managed_number_or_value_arg_1 = gensymed_symbol_2;
		    temp_1 = 
			    store_managed_number_or_value_function(ISVREF(gensymed_symbol,
			    (SI_Long)2L),store_managed_number_or_value_arg_1);
		    SVREF(gensymed_symbol,FIX((SI_Long)2L)) = temp_1;
		}
		else
		    simulation_type_error_from_within_or_without_stack_eval(gensymed_symbol_1,
			    gensymed_symbol_2);
	    }
	    SVREF(gensymed_symbol,FIX((SI_Long)12L)) = T;
	    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)38L);
	    update_variable(ISVREF(CAR(temp),(SI_Long)16L));
	    temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)38L);
	    if (CDR(temp)) {
		temp_1 = Current_model_runtime_info_qm;
		temp = ISVREF(Current_model_runtime_info_qm,(SI_Long)38L);
		svref_new_value = CDR(temp);
		SVREF(temp_1,FIX((SI_Long)38L)) = svref_new_value;
	    }
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qhandle_icp_speedup_value;  /* handle-icp-speedup-value */

/* HANDLE-ICP-SPEEDUP-VALUE */
Object handle_icp_speedup_value()
{
    Object tracep, byte_count_before, current_icp_read_trace_level, tracep_1;
    Object byte_count_before_1, result_of_read, value;
    Object abort_for_icp_catcher_qm, temp, resumable_icp_state_1;
    Object icp_suspend_1, top, value_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,114);
    if (Disable_resumability) {
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_value,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qvalue,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    result_of_read = read_icp_float();
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qvalue,string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    value = result_of_read;
		  POP_SPECIAL();
	      }
	      else
		  value = read_icp_float();
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_speedup_value__body(value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_value,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qvalue,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  result_of_read = read_icp_float();
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qvalue,
			      string_constant_5,Qargument,T,result_of_read,
			      Nil,Nil);
		  value = result_of_read;
		POP_SPECIAL();
	    }
	    else
		value = read_icp_float();
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_value__body(value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    else {
	resumable_icp_state_1 = Resumable_icp_state;
	icp_suspend_1 = Icp_suspend;
	if (resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : TRUEP(Nil)) {
	    top = resumable_icp_pop();
	    if ( !EQ(Qhandle_icp_speedup_value,top)) {
		result = icp_error_internal(Qerror,string_constant_2,
			Qhandle_icp_speedup_value,top,Nil);
		goto end_handle_icp_speedup_value;
	    }
	}
	if (Icp_read_trace_cutoff_level_qm) {
	    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
	    if (tracep);
	    else
		tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
			(SI_Long)2L ? T : Nil;
	    if (tracep) {
		emit_icp_read_trace(T,Nil,Nil,Qspeedup_value,
			string_constant_3,Qmessage,Nil,Nil,Nil,T);
		byte_count_before = instantaneous_icp_reader_byte_count();
	    }
	    else
		byte_count_before = Nil;
	    current_icp_read_trace_level = 
		    FIXNUM_ADD1(Current_icp_read_trace_level);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
		    1);
	      if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		      TRUEP(Nil)) &&  
		      !TRUEP(resumable_icp_pop_list_if_end_marker()))
		  value = resumable_icp_pop();
	      else if (Icp_read_trace_cutoff_level_qm) {
		  if (Icp_read_trace_cutoff_level_qm) {
		      tracep_1 = EQ(Icp_read_trace_cutoff_level_qm,T) ? T :
			       Nil;
		      if (tracep_1);
		      else
			  tracep_1 = IFIX(Icp_read_trace_cutoff_level_qm) 
				  >= (SI_Long)3L ? T : Nil;
		  }
		  else
		      tracep_1 = Nil;
		  if (tracep_1) {
		      emit_icp_read_trace(T,Nil,Nil,Qvalue,
			      string_constant_5,Qargument,Nil,Nil,Nil,Nil);
		      byte_count_before_1 = 
			      instantaneous_icp_reader_byte_count();
		  }
		  else
		      byte_count_before_1 = Nil;
		  current_icp_read_trace_level = 
			  FIXNUM_ADD1(Current_icp_read_trace_level);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			  0);
		    value_1 = read_icp_float();
		    if (EQ(icp_suspend_1,value_1)) {
			resumable_icp_push(Qresumable_icp_list_end);
			resumable_icp_push(Qhandle_icp_speedup_value);
			result = VALUES_1(Icp_suspend);
			POP_SPECIAL();
			POP_SPECIAL();
			goto end_handle_icp_speedup_value;
		    }
		    result_of_read = value_1;
		    if (tracep_1)
			emit_icp_read_trace(Nil,byte_count_before_1,
				instantaneous_icp_reader_byte_count(),
				Qvalue,string_constant_5,Qargument,T,
				result_of_read,Nil,Nil);
		    value = result_of_read;
		  POP_SPECIAL();
	      }
	      else {
		  value_1 = read_icp_float();
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_value;
		  }
		  value = value_1;
	      }
	      abort_for_icp_catcher_qm = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		      0);
		result_of_read = handle_icp_speedup_value__body(value);
	      POP_SPECIAL();
	      if (tracep)
		  emit_icp_read_trace(Nil,byte_count_before,
			  instantaneous_icp_reader_byte_count(),
			  Qspeedup_value,string_constant_3,Qmessage,Nil,
			  result_of_read,Nil,T);
	    POP_SPECIAL();
	}
	else {
	    if ((resumable_icp_state_1 ? TRUEP(Resumable_icp_state) : 
		    TRUEP(Nil)) &&  
		    !TRUEP(resumable_icp_pop_list_if_end_marker()))
		value = resumable_icp_pop();
	    else if (Icp_read_trace_cutoff_level_qm) {
		if (Icp_read_trace_cutoff_level_qm) {
		    tracep = EQ(Icp_read_trace_cutoff_level_qm,T) ? T : Nil;
		    if (tracep);
		    else
			tracep = IFIX(Icp_read_trace_cutoff_level_qm) >= 
				(SI_Long)3L ? T : Nil;
		}
		else
		    tracep = Nil;
		if (tracep) {
		    emit_icp_read_trace(T,Nil,Nil,Qvalue,string_constant_5,
			    Qargument,Nil,Nil,Nil,Nil);
		    byte_count_before = instantaneous_icp_reader_byte_count();
		}
		else
		    byte_count_before = Nil;
		current_icp_read_trace_level = 
			FIXNUM_ADD1(Current_icp_read_trace_level);
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_read_trace_level,Qcurrent_icp_read_trace_level,current_icp_read_trace_level,
			0);
		  value_1 = read_icp_float();
		  if (EQ(icp_suspend_1,value_1)) {
		      resumable_icp_push(Qresumable_icp_list_end);
		      resumable_icp_push(Qhandle_icp_speedup_value);
		      result = VALUES_1(Icp_suspend);
		      POP_SPECIAL();
		      goto end_handle_icp_speedup_value;
		  }
		  result_of_read = value_1;
		  if (tracep)
		      emit_icp_read_trace(Nil,byte_count_before,
			      instantaneous_icp_reader_byte_count(),Qvalue,
			      string_constant_5,Qargument,T,result_of_read,
			      Nil,Nil);
		  value = result_of_read;
		POP_SPECIAL();
	    }
	    else {
		value_1 = read_icp_float();
		if (EQ(icp_suspend_1,value_1)) {
		    resumable_icp_push(Qresumable_icp_list_end);
		    resumable_icp_push(Qhandle_icp_speedup_value);
		    result = VALUES_1(Icp_suspend);
		    goto end_handle_icp_speedup_value;
		}
		value = value_1;
	    }
	    abort_for_icp_catcher_qm = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Abort_for_icp_catcher_qm,Qabort_for_icp_catcher_qm,abort_for_icp_catcher_qm,
		    0);
	      handle_icp_speedup_value__body(value);
	    POP_SPECIAL();
	}
	temp = Nil;
    }
    result = VALUES_1(temp);
  end_handle_icp_speedup_value:
    return result;
}

/* SEND-SPEEDUP-INPUT */
Object send_speedup_input()
{
    Object current_icp_port, current_icp_socket, temp, disable_resumability;
    Object number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, temp_1, current_computation_flags;
    Object current_computation_frame, current_simulation_runtime_structure;
    Object do_not_update_simulated_value_qm, designation, ab_loop_list_;
    Object input_value;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(16);
    Object result;

    x_note_fn_call(219,115);
    if (current_vector_to_external_simulator()) {
	current_icp_port = ISVREF(ISVREF(Current_model_runtime_info_qm,
		(SI_Long)14L),(SI_Long)4L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
		15);
	  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
		  14);
	    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) >= 
		    (SI_Long)17L ? ISVREF(Current_icp_socket,(SI_Long)53L) 
		    : Nil;
	    if (temp);
	    else
		temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
			Qtelewindows) ? T : Nil;
	    disable_resumability = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Disable_resumability,Qdisable_resumability,disable_resumability,
		    13);
	      number_of_icp_bytes_for_message_series = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_for_message_series,Qnumber_of_icp_bytes_for_message_series,number_of_icp_bytes_for_message_series,
		      12);
		icp_buffers_for_message_group = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Icp_buffers_for_message_group,Qicp_buffers_for_message_group,icp_buffers_for_message_group,
			11);
		  icp_buffer_of_start_of_message_series_qm = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Icp_buffer_of_start_of_message_series_qm,Qicp_buffer_of_start_of_message_series_qm,icp_buffer_of_start_of_message_series_qm,
			  10);
		    icp_byte_position_of_start_of_message_series_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Icp_byte_position_of_start_of_message_series_qm,Qicp_byte_position_of_start_of_message_series_qm,icp_byte_position_of_start_of_message_series_qm,
			    9);
		      number_of_icp_bytes_to_fill_buffer = FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_to_fill_buffer,Qnumber_of_icp_bytes_to_fill_buffer,number_of_icp_bytes_to_fill_buffer,
			      8);
			current_icp_buffer = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_icp_buffer,Qcurrent_icp_buffer,current_icp_buffer,
				7);
			  current_write_icp_byte_position = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_write_icp_byte_position,Qcurrent_write_icp_byte_position,current_write_icp_byte_position,
				  6);
			    number_of_icp_bytes_in_message_group = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Number_of_icp_bytes_in_message_group,Qnumber_of_icp_bytes_in_message_group,number_of_icp_bytes_in_message_group,
				    5);
			      writing_icp_message_group = 
				      FIXNUM_ADD1(Writing_icp_message_group);
			      PUSH_SPECIAL_WITH_SYMBOL(Writing_icp_message_group,Qwriting_icp_message_group,writing_icp_message_group,
				      4);
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
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    gensymed_symbol_2);
				}
				if (icp_connection_open_p(Current_icp_socket) 
					&&  
					!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
					    {
				    send_icp_speedup_begin_values();
				    current_computation_flags = 
					    Current_computation_flags;
				    current_computation_frame = 
					    Simulation_parameters;
				    current_simulation_runtime_structure = Nil;
				    do_not_update_simulated_value_qm = T;
				    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_simulated_value_qm,Qdo_not_update_simulated_value_qm,do_not_update_simulated_value_qm,
					    3);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_simulation_runtime_structure,Qcurrent_simulation_runtime_structure,current_simulation_runtime_structure,
					      2);
					PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
						1);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
						  0);
					    Current_computation_flags = 
						    FIX(IFIX(Current_computation_flags) 
						    | (SI_Long)16L);
					    temp_1 = 
						    Current_model_runtime_info_qm;
					    SVREF(temp_1,FIX((SI_Long)2L)) 
						    = 
						    Qcalculating_state_variables;
					    designation = Nil;
					    ab_loop_list_ = 
						    current_vector_to_external_simulator();
					    input_value = Nil;
					  next_loop:
					    if ( !TRUEP(ab_loop_list_))
						goto end_loop;
					    designation = M_CAR(ab_loop_list_);
					    ab_loop_list_ = 
						    M_CDR(ab_loop_list_);
					    input_value = 
						    sim_eval_variable_for_designation(designation,
						    Nil);
					    if (NUMBERP(input_value))
						send_icp_speedup_value(input_value);
					    else
						speedup_input_value_not_a_number(designation,
							input_value);
					    goto next_loop;
					  end_loop:
					    temp = Qnil;
					  POP_SPECIAL();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				    end_icp_message_group();
				}
				else
				    temp = Nil;
				if (Profiling_enabled_qm) {
				    gensymed_symbol_3 = 
					    g2ext_unix_time_as_float();
				    gensymed_symbol_4 = 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L),(SI_Long)0L);
				    gensymed_symbol_5 = gensymed_symbol_3 
					    - gensymed_symbol_4;
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L);
				    aref_new_value = gensymed_symbol_5 + 
					    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
					    (SI_Long)6L),(SI_Long)0L);
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
				    temp_1 = ISVREF(Profiling_enabled_qm,
					    (SI_Long)2L);
				    aref_new_value = gensymed_symbol ? 
					    gensymed_symbol_1 + 
					    gensymed_symbol_5 + 
					    (gensymed_symbol_4 - 
					    gensymed_symbol_2) : 
					    gensymed_symbol_3;
				    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,
					    aref_new_value);
				}
				result = VALUES_1(temp);
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
    else
	return VALUES_1(Nil);
}

/* SHUTDOWN-SPEEDUP-SIMULATION */
Object shutdown_speedup_simulation()
{
    Object current_model_runtime_info_lexical_qm;
    Object current_model_definition_lexical_qm, current_model_runtime_info_qm;
    Object current_model_definition_qm, svref_arg_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,116);
    result = get_model_runtime_info_given_icp_socket(Current_icp_socket);
    MVS_2(result,current_model_runtime_info_lexical_qm,
	    current_model_definition_lexical_qm);
    current_model_runtime_info_qm = current_model_runtime_info_lexical_qm;
    current_model_definition_qm = current_model_definition_lexical_qm;
    PUSH_SPECIAL_WITH_SYMBOL(Current_model_definition_qm,Qcurrent_model_definition_qm,current_model_definition_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_model_runtime_info_qm,Qcurrent_model_runtime_info_qm,current_model_runtime_info_qm,
	      0);
	if (Current_model_runtime_info_qm) {
	    reclaim_simulate_list_1(ISVREF(Current_model_runtime_info_qm,
		    (SI_Long)37L));
	    svref_arg_1 = Current_model_runtime_info_qm;
	    SVREF(svref_arg_1,FIX((SI_Long)37L)) = Nil;
	    svref_arg_1 = Current_model_runtime_info_qm;
	    result = VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)38L)) = Nil);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Speedup_tagname_string_index, Qspeedup_tagname_string_index);

DEFINE_VARIABLE_WITH_SYMBOL(Speedup_tagname_string, Qspeedup_tagname_string);

/* CONVERT-SPEEDUP-TAGNAME-TO-DESIGNATION */
Object convert_speedup_tagname_to_designation(speedup_tagname_string)
    Object speedup_tagname_string;
{
    Object speedup_tagname_string_index;
    Declare_special(2);
    Object result;

    x_note_fn_call(219,117);
    PUSH_SPECIAL_WITH_SYMBOL(Speedup_tagname_string,Qspeedup_tagname_string,speedup_tagname_string,
	    1);
      speedup_tagname_string_index = FIX((SI_Long)0L);
      PUSH_SPECIAL_WITH_SYMBOL(Speedup_tagname_string_index,Qspeedup_tagname_string_index,speedup_tagname_string_index,
	      0);
	result = parse_first_symbol_for_speedup_tagname();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* PARSE-FIRST-SYMBOL-FOR-SPEEDUP-TAGNAME */
Object parse_first_symbol_for_speedup_tagname()
{
    Object first_symbol;

    x_note_fn_call(219,118);
    first_symbol = get_next_speedup_tagname_symbol();
    if ( !TRUEP(first_symbol))
	return incorrect_format_for_speedup_tagname(Speedup_tagname_string);
    else if (EQ(first_symbol,Qthe))
	return parse_attribute_name_for_speedup_tagname();
    else
	return VALUES_1(first_symbol);
}

static Object list_constant;       /* # */

/* PARSE-ATTRIBUTE-NAME-FOR-SPEEDUP-TAGNAME */
Object parse_attribute_name_for_speedup_tagname()
{
    Object attribute_name;

    x_note_fn_call(219,119);
    attribute_name = get_next_speedup_tagname_symbol();
    if ( !TRUEP(attribute_name) || memq_function(attribute_name,list_constant))
	return incorrect_format_for_speedup_tagname(Speedup_tagname_string);
    else
	return slot_value_cons_1(Qthe,slot_value_cons_1(attribute_name,
		parse_after_attribute_for_speedup_tagname()));
}

static Object Qof;                 /* of */

/* PARSE-AFTER-ATTRIBUTE-FOR-SPEEDUP-TAGNAME */
Object parse_after_attribute_for_speedup_tagname()
{
    Object name_or_attribute_designation;

    x_note_fn_call(219,120);
    if ( !EQ(get_next_speedup_tagname_symbol(),Qof))
	incorrect_format_for_speedup_tagname(Speedup_tagname_string);
    name_or_attribute_designation = get_next_speedup_tagname_symbol();
    if ( !TRUEP(name_or_attribute_designation) || 
	    EQ(name_or_attribute_designation,Qof))
	return incorrect_format_for_speedup_tagname(Speedup_tagname_string);
    else if (EQ(name_or_attribute_designation,Qthe))
	return parse_attribute_name_for_speedup_tagname();
    else
	return slot_value_cons_1(name_or_attribute_designation,Nil);
}

/* GET-NEXT-SPEEDUP-TAGNAME-SYMBOL */
Object get_next_speedup_tagname_symbol()
{
    Object next_symbol_qm, next_string_index;
    Object result;

    x_note_fn_call(219,121);
    result = read_symbol_from_text_string(2,Speedup_tagname_string,
	    Speedup_tagname_string_index);
    MVS_2(result,next_symbol_qm,next_string_index);
    if (next_symbol_qm) {
	Speedup_tagname_string_index = next_string_index;
	return VALUES_1(next_symbol_qm);
    }
    else {
	non_symbol_in_speedup_tagname(Speedup_tagname_string_index,
		Speedup_tagname_string);
	return VALUES_1(Nil);
    }
}

static Object Qnon_symbol_in_speedup_tagname;  /* non-symbol-in-speedup-tagname */

static Object string_constant_15;  /* "Unable to read a symbol beginning with character ~d in the SPEEDUP tagname ~s." */

static Object Qsimulation_error_catch;  /* simulation-error-catch */

/* NON-SYMBOL-IN-SPEEDUP-TAGNAME */
Object non_symbol_in_speedup_tagname(start_index,tagname_string)
    Object start_index, tagname_string;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,122);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qnon_symbol_in_speedup_tagname;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)1L),string_constant_15,start_index,
		tagname_string);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qincorrect_format_for_speedup_tagname;  /* incorrect-format-for-speedup-tagname */

static Object string_constant_16;  /* "The SPEEDUP tagname ~a does not have the correct format." */

/* INCORRECT-FORMAT-FOR-SPEEDUP-TAGNAME */
Object incorrect_format_for_speedup_tagname(tagname_string)
    Object tagname_string;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,123);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = 
	    Qincorrect_format_for_speedup_tagname;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(3,FIX((SI_Long)1L),string_constant_16,tagname_string);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qspeedup_tagname_not_variable;  /* speedup-tagname-not-variable */

static Object string_constant_17;  /* "The SPEEDUP output designation ~s refers to ~s, which is not a variable or parameter." */

/* SPEEDUP-TAGNAME-NOT-VARIABLE */
Object speedup_tagname_not_variable(designation,variable_or_parameter_qm)
    Object designation, variable_or_parameter_qm;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,124);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qspeedup_tagname_not_variable;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)1L),string_constant_17,designation,
		variable_or_parameter_qm);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qspeedup_simulation_conflict;  /* speedup-simulation-conflict */

static Object string_constant_18;  /* "The SPEEDUP output designation ~s refers to ~s which is already being simulated. ~
				    *     Please check if this variable is designated more than once by SPEEDUP tagnames, or ~
				    *     if it is being simulated by G2."
				    */

/* SPEEDUP-SIMULATION-CONFLICT */
Object speedup_simulation_conflict(designation,variable_or_parameter_qm)
    Object designation, variable_or_parameter_qm;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,125);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qspeedup_simulation_conflict;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)1L),string_constant_18,designation,
		variable_or_parameter_qm);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qspeedup_output_variable_deleted;  /* speedup-output-variable-deleted */

static Object string_constant_19;  /* "A variable simulated by SPEEDUP has been deleted." */

/* SPEEDUP-OUTPUT-VARIABLE-DELETED */
Object speedup_output_variable_deleted()
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,126);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qspeedup_output_variable_deleted;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(2,FIX((SI_Long)1L),string_constant_19);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qspeedup_input_value_not_a_number;  /* speedup-input-value-not-a-number */

static Object string_constant_20;  /* "The SPEEDUP input designation ~s evaluates to ~s, which is not a number." */

/* SPEEDUP-INPUT-VALUE-NOT-A-NUMBER */
Object speedup_input_value_not_a_number(designation,input_value)
    Object designation, input_value;
{
    Object svref_arg_1;
    Object result;

    x_note_fn_call(219,127);
    svref_arg_1 = Current_model_runtime_info_qm;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = Qspeedup_input_value_not_a_number;
    if (ISVREF(Current_model_runtime_info_qm,(SI_Long)12L)) {
	abort_procedure_invocation(1,ISVREF(Current_model_runtime_info_qm,
		(SI_Long)12L));
	svref_arg_1 = Current_model_runtime_info_qm;
	SVREF(svref_arg_1,FIX((SI_Long)12L)) = Nil;
    }
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)1L),string_constant_20,designation,
		input_value);
    if (Within_simulate_until_consistent_with_gensym_time || 
	    Initializing_simulator_qm) {
	result = VALUES_1(T);
	THROW(Qsimulation_error_catch,result);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-FROM-EXTERNAL-SIMULATION-RUNTIME-STRUCTURES */
Object delete_from_external_simulation_runtime_structures(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    x_note_fn_call(219,128);
    return VALUES_1(Nil);
}

void gspan_INIT()
{
    Object temp, temp_1, temp_2;
    Object reclaim_structure_for_external_simulation_object_1;
    Object AB_package, list_constant_3, Qhandle_icp_connection_info;
    Object Qhandle_icp_end_simulation_input_for_cycle;
    Object Qhandle_icp_resume_external_simulator;
    Object Qhandle_icp_pause_external_simulator;
    Object Qhandle_icp_shutdown_external_simulator;
    Object Qhandle_icp_initialize_external_simulator;
    Object Qreclaim_icp_port_entry_for_external_simulation_object;
    Object list_constant_2;
    Object Qexternal_simulation_object_corresponding_icp_object_map;
    Object Qreclaim_structure, Qoutstanding_external_simulation_object_count;
    Object Qexternal_simulation_object_structure_memory_usage, Qutilities2;
    Object string_constant_40, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_39, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qsimulate1;
    Object Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_external_simulation_definition, Qinitialize;
    Object Qinitialize_for_external_simulation_definition, Qslot_putter;
    Object Qput_output_vector_from_external_simulator;
    Object Qput_initialization_vector_for_external_simulator;
    Object Qput_message_keywords, Qput_input_vector_to_external_simulator;
    Object Qput_class_of_object_computed_by_this, string_constant_38;
    Object string_constant_37, Qslot_value_writer, Qwrite_symbol_from_slot;
    Object Qkeyword_strings_or_none, Qattribute_designations_or_none;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object Qsimplify_associative_operation;
    Object Qexternal_simulation_definition_for_class;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qexternal_simulation_definitions_for_attribute, Qgspan;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object list_constant_1, Qcreate_icon_description, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21, Qentity;
    Object Qitem;

    x_note_fn_call(219,129);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qexternal_simulation_definition = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qexternal_simulation_definition,
	    list_constant_1);
    string_constant_21 = STATIC_STRING("1m1m8v836oy1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_22 = 
	    STATIC_STRING("1t4z8r83--y83--y836oy836oy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_23 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_24 = 
	    STATIC_STRING("0004z8r83-0y83-0y836oy836oy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_25 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u836oy836oy01s8w9k3-Wy3-Wy1o1p83Jy1mkk1m3-Wyk1m3-Wy3-Wy1mk3-Wy1n83Oy1m3Gy3Gy1m3ky3-Cy1");
    string_constant_26 = 
	    STATIC_STRING("n83Oy1m3ky3Gy1m3Gy3-Cy1q83Oy1m3-Ey3Ly1m83*Hy1m3sy3Vy1m3-2y3ky1m83*Hy1m3-Ey3--y1m3sy3-7y03*My3*My001o1l8l1l8o1l8z1m83Dy53YySee co");
    string_constant_27 = 
	    STATIC_STRING("mment on ENTITY class definition000004z8r83-Fy83-Fy836oy836oy00001r1l8l1l83Hy1l83Ny1m8p83-ky1l83Uy1l83*-y1m83Dy53MySee comment i");
    string_constant_28 = 
	    STATIC_STRING("n class block000004z8r83BBy83BBy836oy836oy00001o1l8o1l8l1l8z1m8p833Vy000004z8r83VQy83VQy836oy836oy00001n1l8o1l8l1n8p83DNy83Gy000");
    string_constant_29 = 
	    STATIC_STRING("004z8r83SGy83SGy836oy836oy00001n1l8o1l8l1n8p83Aly83Gy000004z8r83XQy83XQy836oy836oy00001n1l8o1l8l1n8p83Aky83Gy000004z8r83SFy83SFy");
    string_constant_30 = 
	    STATIC_STRING("836oy836oy00001n1l8o1l8l1n8p83Aly83Gy00000");
    string_constant_31 = 
	    STATIC_STRING("1v8q1o836oy1m83Ry83-+y1m8v836oy8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1m8u1s8w9k3-Wy3-Wy1o1p83Jy1mkk1m3-Wyk1m3-Wy3-Wy1mk3-Wy1n83Oy1");
    string_constant_32 = 
	    STATIC_STRING("m3Gy3Gy1m3ky3-Cy1n83Oy1m3ky3Gy1m3Gy3-Cy1q83Oy1m3-Ey3Ly1m83*Hy1m3sy3Vy1m3-2y3ky1m83*Hy1m3-Ey3--y1m3sy3-7y03*My3*My1o83-Fy083Hy83N");
    string_constant_33 = 
	    STATIC_STRING("y1q83BBy08o8l8z1m8p833Vy1p83VQy08o8l1n8p83DNy83Gy1p83SGy08o8l1n8p83Aly83Gy1p83XQy08o8l1n8p83Aky83Gy1p83SFy08o8l1n8p83Aly83Gy");
    temp = regenerate_optimized_constant(string_constant_21);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(9,string_constant_22,
	    string_constant_23,string_constant_24,string_constant_25,
	    string_constant_26,string_constant_27,string_constant_28,
	    string_constant_29,string_constant_30));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qexternal_simulation_definition,
	    list_constant_1,Nil,temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(LIST_3(string_constant_31,
	    string_constant_32,string_constant_33)),Nil);
    External_simulation_definition_class_description = 
	    lookup_global_or_kb_specific_property_value(Qexternal_simulation_definition,
	    Class_description_gkbprop);
    Qproceed_with_edit = STATIC_SYMBOL("PROCEED-WITH-EDIT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qproceed_with_edit,Proceed_with_edit);
    Qgspan = STATIC_SYMBOL("GSPAN",AB_package);
    record_system_variable(Qproceed_with_edit,Qgspan,Nil,Qnil,Qnil,Qnil,Qnil);
    Qexternal_simulation_definitions_for_attribute = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITIONS-FOR-ATTRIBUTE",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qexternal_simulation_definitions_for_attribute,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qexternal_simulation_definitions_for_attribute,
	    T,Qdo_not_carry_global_property_value_into_kbs_qm);
    External_simulation_definitions_for_attribute_kbprop = 
	    Qexternal_simulation_definitions_for_attribute;
    Qexternal_simulation_definition_for_class = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION-FOR-CLASS",
	    AB_package);
    Kb_specific_property_names = 
	    CONS(Qexternal_simulation_definition_for_class,
	    Kb_specific_property_names);
    mutate_global_property(Qexternal_simulation_definition_for_class,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    External_simulation_definition_for_class_kbprop = 
	    Qexternal_simulation_definition_for_class;
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_34 = 
	    STATIC_STRING("1v1m83Aky83-K=y1o83Aky1n83-K=y1m9k83vy83Aky1nmln9l1m83Aly83Aky1m83Aly1m9k83Zy1n83-K=y1p1m9k9m83*my1m9k83-Ty1m9k9m83-Gy1nlm1mop1n");
    string_constant_35 = 
	    STATIC_STRING("83-K=y1o1m9k9m83*my1m9k83-Ty83-K=y1nlmo1m83DNy83-c0y1m83DNy1m9k83Zy1m83-c0y83-c=y1o83-c0y1n83-c=y1m9k83vy83-c=y1nmln9l1m83-c=y83");
    string_constant_36 = STATIC_STRING("-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_34,
	    string_constant_35,string_constant_36)));
    Qattribute_designations_or_none = 
	    STATIC_SYMBOL("ATTRIBUTE-DESIGNATIONS-OR-NONE",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qattribute_designations_or_none,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qkeyword_strings_or_none = STATIC_SYMBOL("KEYWORD-STRINGS-OR-NONE",
	    AB_package);
    mutate_global_property(Qkeyword_strings_or_none,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    string_constant_37 = 
	    STATIC_STRING("1s1m83-*Jy83-6y1m83-7Ly83-6y1m83-EUy83Sy1m83wHy83-Uy1m83iVy83-Uy1n834vy1p1m9k83bYy1m9k83Ray83iVy1m9k83Xvy83-EUy1n83bYynp1n834vy1");
    string_constant_38 = 
	    STATIC_STRING("o1m9k83-qPy1m9k83-wfy1m9k839ny83wHy1m83-wgyo1m834vy1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_37,
	    string_constant_38)));
    string_constant = 
	    STATIC_STRING("An external-simulation-definition may not be edited while the system is running or paused.  Please reset before editing an external-simulation-definition.");
    Qclass_of_object_computed_by_this = 
	    STATIC_SYMBOL("CLASS-OF-OBJECT-COMPUTED-BY-THIS",AB_package);
    Qput_class_of_object_computed_by_this = 
	    STATIC_SYMBOL("PUT-CLASS-OF-OBJECT-COMPUTED-BY-THIS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_class_of_object_computed_by_this,
	    STATIC_FUNCTION(put_class_of_object_computed_by_this,NIL,FALSE,
	    3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qclass_of_object_computed_by_this,
	    SYMBOL_FUNCTION(Qput_class_of_object_computed_by_this),
	    Qslot_putter);
    Qinput_vector_to_external_simulator = 
	    STATIC_SYMBOL("INPUT-VECTOR-TO-EXTERNAL-SIMULATOR",AB_package);
    Qput_input_vector_to_external_simulator = 
	    STATIC_SYMBOL("PUT-INPUT-VECTOR-TO-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qput_input_vector_to_external_simulator,
	    STATIC_FUNCTION(put_input_vector_to_external_simulator,NIL,
	    FALSE,3,3));
    mutate_global_property(Qinput_vector_to_external_simulator,
	    SYMBOL_FUNCTION(Qput_input_vector_to_external_simulator),
	    Qslot_putter);
    Qmessage_keywords = STATIC_SYMBOL("MESSAGE-KEYWORDS",AB_package);
    Qput_message_keywords = STATIC_SYMBOL("PUT-MESSAGE-KEYWORDS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_message_keywords,
	    STATIC_FUNCTION(put_message_keywords,NIL,FALSE,3,3));
    mutate_global_property(Qmessage_keywords,
	    SYMBOL_FUNCTION(Qput_message_keywords),Qslot_putter);
    Qinitialization_vector_for_external_simulator = 
	    STATIC_SYMBOL("INITIALIZATION-VECTOR-FOR-EXTERNAL-SIMULATOR",
	    AB_package);
    Qput_initialization_vector_for_external_simulator = 
	    STATIC_SYMBOL("PUT-INITIALIZATION-VECTOR-FOR-EXTERNAL-SIMULATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_initialization_vector_for_external_simulator,
	    STATIC_FUNCTION(put_initialization_vector_for_external_simulator,
	    NIL,FALSE,3,3));
    mutate_global_property(Qinitialization_vector_for_external_simulator,
	    SYMBOL_FUNCTION(Qput_initialization_vector_for_external_simulator),
	    Qslot_putter);
    Qoutput_vector_from_external_simulator = 
	    STATIC_SYMBOL("OUTPUT-VECTOR-FROM-EXTERNAL-SIMULATOR",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qput_output_vector_from_external_simulator = 
	    STATIC_SYMBOL("PUT-OUTPUT-VECTOR-FROM-EXTERNAL-SIMULATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_output_vector_from_external_simulator,
	    STATIC_FUNCTION(put_output_vector_from_external_simulator,NIL,
	    FALSE,3,3));
    mutate_global_property(Qoutput_vector_from_external_simulator,
	    SYMBOL_FUNCTION(Qput_output_vector_from_external_simulator),
	    Qslot_putter);
    Qinitialize_for_external_simulation_definition = 
	    STATIC_SYMBOL("INITIALIZE-FOR-EXTERNAL-SIMULATION-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_external_simulation_definition,
	    STATIC_FUNCTION(initialize_for_external_simulation_definition,
	    NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_external_simulation_definition);
    set_get(Qexternal_simulation_definition,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qexternal_simulation_definition,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qcleanup_for_external_simulation_definition = 
	    STATIC_SYMBOL("CLEANUP-FOR-EXTERNAL-SIMULATION-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_external_simulation_definition,
	    STATIC_FUNCTION(cleanup_for_external_simulation_definition,NIL,
	    FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_external_simulation_definition);
    set_get(Qexternal_simulation_definition,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qexternal_simulation_definition,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qexternal_simulation = STATIC_SYMBOL("EXTERNAL-SIMULATION",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexternal_simulation_definition_for_entity = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-DEFINITION-FOR-ENTITY",
	    AB_package);
    string_constant_1 = 
	    string_append2(STATIC_STRING("The object ~NF does not have an external simulation capability.  If this is ~\n        desired, add the external-simulation capability to the capabilities-and-~\n        restric"),
	    STATIC_STRING("tions attribute of ~a, the object definition for this object\'s class."));
    Qsimulate = STATIC_SYMBOL("SIMULATE",AB_package);
    Qoutput_vector_for_object = STATIC_SYMBOL("OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoutput_vector_for_object,
	    Output_vector_for_object);
    Qsimulate1 = STATIC_SYMBOL("SIMULATE1",AB_package);
    record_system_variable(Qoutput_vector_for_object,Qsimulate1,Nil,Qnil,
	    Qnil,Qnil,Qt);
    Qg2_defstruct_structure_name_external_simulation_object_g2_struct = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexternal_simulation_object = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_simulation_object_g2_struct,
	    Qexternal_simulation_object,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qexternal_simulation_object,
	    Qg2_defstruct_structure_name_external_simulation_object_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_external_simulation_object == UNBOUND)
	The_type_description_of_external_simulation_object = Nil;
    string_constant_39 = 
	    STATIC_STRING("43Dy8m83hEy1n83hEy8n8k1l8n0000000knk0k0");
    temp = The_type_description_of_external_simulation_object;
    The_type_description_of_external_simulation_object = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_39));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_simulation_object_g2_struct,
	    The_type_description_of_external_simulation_object,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qexternal_simulation_object,
	    The_type_description_of_external_simulation_object,
	    Qtype_description_of_type);
    Qoutstanding_external_simulation_object_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXTERNAL-SIMULATION-OBJECT-COUNT",
	    AB_package);
    Qexternal_simulation_object_structure_memory_usage = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_40 = STATIC_STRING("1q83hEy8s83-TZy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_external_simulation_object_count);
    push_optimized_constant(Qexternal_simulation_object_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_40));
    Qchain_of_available_external_simulation_objects = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXTERNAL-SIMULATION-OBJECTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_external_simulation_objects,
	    Chain_of_available_external_simulation_objects);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_external_simulation_objects,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qexternal_simulation_object_count = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexternal_simulation_object_count,
	    External_simulation_object_count);
    record_system_variable(Qexternal_simulation_object_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_external_simulation_objects_vector == UNBOUND)
	Chain_of_available_external_simulation_objects_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qexternal_simulation_object_structure_memory_usage,
	    STATIC_FUNCTION(external_simulation_object_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_external_simulation_object_count,
	    STATIC_FUNCTION(outstanding_external_simulation_object_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_external_simulation_object_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_external_simulation_object,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qexternal_simulation_object,
	    reclaim_structure_for_external_simulation_object_1);
    Qstandard_icp_object_index_space = 
	    STATIC_SYMBOL("STANDARD-ICP-OBJECT-INDEX-SPACE",AB_package);
    Qestablish_new_object_index_for_external_simulation_object = 
	    STATIC_SYMBOL("ESTABLISH-NEW-OBJECT-INDEX-FOR-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    string_constant_2 = 
	    STATIC_STRING("resumable icp synch error: ~S expected, ~S found");
    SET_SYMBOL_FUNCTION(Qestablish_new_object_index_for_external_simulation_object,
	    STATIC_FUNCTION(establish_new_object_index_for_external_simulation_object,
	    NIL,TRUE,2,3));
    Qmake_corresponding_icp_external_simulation_object = 
	    STATIC_SYMBOL("MAKE-CORRESPONDING-ICP-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_corresponding_icp_external_simulation_object,
	    STATIC_FUNCTION(make_corresponding_icp_external_simulation_object,
	    NIL,FALSE,1,1));
    Qset_access_form_for_external_simulation_object = 
	    STATIC_SYMBOL("SET-ACCESS-FORM-FOR-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_access_form_for_external_simulation_object,
	    STATIC_FUNCTION(set_access_form_for_external_simulation_object,
	    NIL,FALSE,2,2));
    Qexternal_simulation_object_corresponding_icp_object_map = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT-CORRESPONDING-ICP-OBJECT-MAP",
	    AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,
	    Qexternal_simulation_object_corresponding_icp_object_map,
	    Qexternal_simulation_object);
    initialize_icp_object_type_compile(Qexternal_simulation_object,
	    Qstandard_icp_object_index_space,list_constant_2);
    Qreclaim_icp_port_entry_for_external_simulation_object = 
	    STATIC_SYMBOL("RECLAIM-ICP-PORT-ENTRY-FOR-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_icp_port_entry_for_external_simulation_object,
	    STATIC_FUNCTION(reclaim_icp_port_entry_for_external_simulation_object,
	    NIL,FALSE,2,2));
    initialize_icp_object_type(Qexternal_simulation_object,Qnil,Qnil,
	    Qreclaim_icp_port_entry_for_external_simulation_object);
    Qsend_icp_new_externally_simulated_object = 
	    STATIC_SYMBOL("SEND-ICP-NEW-EXTERNALLY-SIMULATED-OBJECT",
	    AB_package);
    Qnew_externally_simulated_object = 
	    STATIC_SYMBOL("NEW-EXTERNALLY-SIMULATED-OBJECT",AB_package);
    string_constant_3 = STATIC_STRING("[message]");
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_4 = STATIC_STRING("[object arg]");
    Qargument = STATIC_SYMBOL("ARGUMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_new_externally_simulated_object,
	    STATIC_FUNCTION(send_icp_new_externally_simulated_object,NIL,
	    FALSE,1,1));
    Qsend_icp_define_external_simulation_object = 
	    STATIC_SYMBOL("SEND-ICP-DEFINE-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    Qdefine_external_simulation_object = 
	    STATIC_SYMBOL("DEFINE-EXTERNAL-SIMULATION-OBJECT",AB_package);
    Qicp_object_index = STATIC_SYMBOL("ICP-OBJECT-INDEX",AB_package);
    string_constant_5 = STATIC_STRING("[value arg]");
    Qobject_class = STATIC_SYMBOL("OBJECT-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_define_external_simulation_object,
	    STATIC_FUNCTION(send_icp_define_external_simulation_object,NIL,
	    FALSE,2,2));
    Qsend_icp_simulation_initialization_value = 
	    STATIC_SYMBOL("SEND-ICP-SIMULATION-INITIALIZATION-VALUE",
	    AB_package);
    Qsimulation_initialization_value = 
	    STATIC_SYMBOL("SIMULATION-INITIALIZATION-VALUE",AB_package);
    Qinitialization_value = STATIC_SYMBOL("INITIALIZATION-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_simulation_initialization_value,
	    STATIC_FUNCTION(send_icp_simulation_initialization_value,NIL,
	    FALSE,1,1));
    Qsend_icp_end_simulation_initialization_vector_for_object = 
	    STATIC_SYMBOL("SEND-ICP-END-SIMULATION-INITIALIZATION-VECTOR-FOR-OBJECT",
	    AB_package);
    Qend_simulation_initialization_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-INITIALIZATION-VECTOR-FOR-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_simulation_initialization_vector_for_object,
	    STATIC_FUNCTION(send_icp_end_simulation_initialization_vector_for_object,
	    NIL,FALSE,0,0));
    Qsend_icp_begin_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("SEND-ICP-BEGIN-SIMULATION-INPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qbegin_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("BEGIN-SIMULATION-INPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_begin_simulation_input_vector_for_object,
	    STATIC_FUNCTION(send_icp_begin_simulation_input_vector_for_object,
	    NIL,FALSE,1,1));
    Qsend_icp_simulation_keyword = 
	    STATIC_SYMBOL("SEND-ICP-SIMULATION-KEYWORD",AB_package);
    Qsimulation_keyword = STATIC_SYMBOL("SIMULATION-KEYWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_simulation_keyword,
	    STATIC_FUNCTION(send_icp_simulation_keyword,NIL,FALSE,1,1));
    Qsend_icp_simulation_input_value = 
	    STATIC_SYMBOL("SEND-ICP-SIMULATION-INPUT-VALUE",AB_package);
    Qsimulation_input_value = STATIC_SYMBOL("SIMULATION-INPUT-VALUE",
	    AB_package);
    Qinput_value = STATIC_SYMBOL("INPUT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_simulation_input_value,
	    STATIC_FUNCTION(send_icp_simulation_input_value,NIL,FALSE,1,1));
    Qsend_icp_end_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("SEND-ICP-END-SIMULATION-INPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qend_simulation_input_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-INPUT-VECTOR-FOR-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_simulation_input_vector_for_object,
	    STATIC_FUNCTION(send_icp_end_simulation_input_vector_for_object,
	    NIL,FALSE,0,0));
    Qsend_icp_begin_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("SEND-ICP-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qbegin_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qexternal_simulation_object_qm = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT\?",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_begin_simulation_output_vector_for_object,
	    STATIC_FUNCTION(send_icp_begin_simulation_output_vector_for_object,
	    NIL,FALSE,1,1));
    string_constant_6 = 
	    STATIC_STRING("Unable to retrieve external simulation object");
    Qhandle_icp_begin_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("HANDLE-ICP-BEGIN-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qresumable_icp_list_end = STATIC_SYMBOL("RESUMABLE-ICP-LIST-END",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_begin_simulation_output_vector_for_object,
	    STATIC_FUNCTION(handle_icp_begin_simulation_output_vector_for_object,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_begin_simulation_output_vector_for_object,
	    FIX((SI_Long)131L));
    Qsend_icp_simulation_output_value = 
	    STATIC_SYMBOL("SEND-ICP-SIMULATION-OUTPUT-VALUE",AB_package);
    Qsimulation_output_value = STATIC_SYMBOL("SIMULATION-OUTPUT-VALUE",
	    AB_package);
    Qoutput_value = STATIC_SYMBOL("OUTPUT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_simulation_output_value,
	    STATIC_FUNCTION(send_icp_simulation_output_value,NIL,FALSE,1,1));
    Qhandle_icp_simulation_output_value = 
	    STATIC_SYMBOL("HANDLE-ICP-SIMULATION-OUTPUT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_simulation_output_value,
	    STATIC_FUNCTION(handle_icp_simulation_output_value,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_simulation_output_value,
	    FIX((SI_Long)132L));
    Qsend_icp_end_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("SEND-ICP-END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    Qend_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_simulation_output_vector_for_object,
	    STATIC_FUNCTION(send_icp_end_simulation_output_vector_for_object,
	    NIL,FALSE,0,0));
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    string_constant_7 = 
	    STATIC_STRING("Problem encountered simulating the designation ~a for the entity ~NF externally.");
    string_constant_8 = 
	    string_append2(STATIC_STRING("Problem encountered simulating the entity ~NF externally due to \nmismatch in number of designations specified in \"output vector from external \nsimulator\" slot of external simu"),
	    STATIC_STRING("lation definition and number of values returned\nby the external simulator."));
    Qhandle_icp_end_simulation_output_vector_for_object = 
	    STATIC_SYMBOL("HANDLE-ICP-END-SIMULATION-OUTPUT-VECTOR-FOR-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_end_simulation_output_vector_for_object,
	    STATIC_FUNCTION(handle_icp_end_simulation_output_vector_for_object,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_end_simulation_output_vector_for_object,
	    FIX((SI_Long)133L));
    Qsend_icp_initialize_external_simulator = 
	    STATIC_SYMBOL("SEND-ICP-INITIALIZE-EXTERNAL-SIMULATOR",AB_package);
    Qinitialize_external_simulator = 
	    STATIC_SYMBOL("INITIALIZE-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_initialize_external_simulator,
	    STATIC_FUNCTION(send_icp_initialize_external_simulator,NIL,
	    FALSE,0,0));
    Qhandle_icp_initialize_external_simulator = 
	    STATIC_SYMBOL("HANDLE-ICP-INITIALIZE-EXTERNAL-SIMULATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_initialize_external_simulator,
	    STATIC_FUNCTION(handle_icp_initialize_external_simulator,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_initialize_external_simulator,
	    FIX((SI_Long)134L));
    Qsend_icp_shutdown_external_simulator = 
	    STATIC_SYMBOL("SEND-ICP-SHUTDOWN-EXTERNAL-SIMULATOR",AB_package);
    Qshutdown_external_simulator = 
	    STATIC_SYMBOL("SHUTDOWN-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_shutdown_external_simulator,
	    STATIC_FUNCTION(send_icp_shutdown_external_simulator,NIL,FALSE,
	    0,0));
    Qhandle_icp_shutdown_external_simulator = 
	    STATIC_SYMBOL("HANDLE-ICP-SHUTDOWN-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_shutdown_external_simulator,
	    STATIC_FUNCTION(handle_icp_shutdown_external_simulator,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_shutdown_external_simulator,
	    FIX((SI_Long)128L));
    Qsend_icp_pause_external_simulator = 
	    STATIC_SYMBOL("SEND-ICP-PAUSE-EXTERNAL-SIMULATOR",AB_package);
    Qpause_external_simulator = STATIC_SYMBOL("PAUSE-EXTERNAL-SIMULATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_pause_external_simulator,
	    STATIC_FUNCTION(send_icp_pause_external_simulator,NIL,FALSE,0,0));
    Qhandle_icp_pause_external_simulator = 
	    STATIC_SYMBOL("HANDLE-ICP-PAUSE-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_pause_external_simulator,
	    STATIC_FUNCTION(handle_icp_pause_external_simulator,NIL,FALSE,
	    0,0));
    add_icp_message_handler(Qhandle_icp_pause_external_simulator,
	    FIX((SI_Long)129L));
    Qsend_icp_resume_external_simulator = 
	    STATIC_SYMBOL("SEND-ICP-RESUME-EXTERNAL-SIMULATOR",AB_package);
    Qresume_external_simulator = STATIC_SYMBOL("RESUME-EXTERNAL-SIMULATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_resume_external_simulator,
	    STATIC_FUNCTION(send_icp_resume_external_simulator,NIL,FALSE,0,0));
    Qhandle_icp_resume_external_simulator = 
	    STATIC_SYMBOL("HANDLE-ICP-RESUME-EXTERNAL-SIMULATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_resume_external_simulator,
	    STATIC_FUNCTION(handle_icp_resume_external_simulator,NIL,FALSE,
	    0,0));
    add_icp_message_handler(Qhandle_icp_resume_external_simulator,
	    FIX((SI_Long)130L));
    Qsend_icp_end_simulation_input_for_cycle = 
	    STATIC_SYMBOL("SEND-ICP-END-SIMULATION-INPUT-FOR-CYCLE",
	    AB_package);
    Qend_simulation_input_for_cycle = 
	    STATIC_SYMBOL("END-SIMULATION-INPUT-FOR-CYCLE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_simulation_input_for_cycle,
	    STATIC_FUNCTION(send_icp_end_simulation_input_for_cycle,NIL,
	    FALSE,0,0));
    Qhandle_icp_end_simulation_input_for_cycle = 
	    STATIC_SYMBOL("HANDLE-ICP-END-SIMULATION-INPUT-FOR-CYCLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_end_simulation_input_for_cycle,
	    STATIC_FUNCTION(handle_icp_end_simulation_input_for_cycle,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_end_simulation_input_for_cycle,
	    FIX((SI_Long)135L));
    Qsend_icp_end_simulation_output_for_cycle = 
	    STATIC_SYMBOL("SEND-ICP-END-SIMULATION-OUTPUT-FOR-CYCLE",
	    AB_package);
    Qend_simulation_output_for_cycle = 
	    STATIC_SYMBOL("END-SIMULATION-OUTPUT-FOR-CYCLE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_end_simulation_output_for_cycle,
	    STATIC_FUNCTION(send_icp_end_simulation_output_for_cycle,NIL,
	    FALSE,0,0));
    Qhandle_icp_end_simulation_output_for_cycle = 
	    STATIC_SYMBOL("HANDLE-ICP-END-SIMULATION-OUTPUT-FOR-CYCLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_end_simulation_output_for_cycle,
	    STATIC_FUNCTION(handle_icp_end_simulation_output_for_cycle,NIL,
	    FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_end_simulation_output_for_cycle,
	    FIX((SI_Long)136L));
    Qsend_icp_connection_info = STATIC_SYMBOL("SEND-ICP-CONNECTION-INFO",
	    AB_package);
    Qconnection_info = STATIC_SYMBOL("CONNECTION-INFO",AB_package);
    Qinput_end_object = STATIC_SYMBOL("INPUT-END-OBJECT",AB_package);
    Qoutput_end_object = STATIC_SYMBOL("OUTPUT-END-OBJECT",AB_package);
    Qdirectional_qm = STATIC_SYMBOL("DIRECTIONAL\?",AB_package);
    Qport_name_for_input_end_object = 
	    STATIC_SYMBOL("PORT-NAME-FOR-INPUT-END-OBJECT",AB_package);
    Qport_name_for_output_end_object = 
	    STATIC_SYMBOL("PORT-NAME-FOR-OUTPUT-END-OBJECT",AB_package);
    Qexternally_simulated_connection = 
	    STATIC_SYMBOL("EXTERNALLY-SIMULATED-CONNECTION",AB_package);
    Qnumber_of_connections_left_in_path = 
	    STATIC_SYMBOL("NUMBER-OF-CONNECTIONS-LEFT-IN-PATH",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_connection_info,
	    STATIC_FUNCTION(send_icp_connection_info,NIL,FALSE,7,7));
    Qhandle_icp_connection_info = 
	    STATIC_SYMBOL("HANDLE-ICP-CONNECTION-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_connection_info,
	    STATIC_FUNCTION(handle_icp_connection_info,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_connection_info,FIX((SI_Long)137L));
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    string_constant_9 = STATIC_STRING("~a");
    SET_SYMBOL_FUNCTION(Qdefine_external_simulation_object,
	    STATIC_FUNCTION(define_external_simulation_object,NIL,FALSE,2,2));
    Qreturned_external_simulation_object = 
	    STATIC_SYMBOL("RETURNED-EXTERNAL-SIMULATION-OBJECT",AB_package);
    string_constant_10 = STATIC_STRING("[value]");
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qread_icp_returned_external_simulation_object = 
	    STATIC_SYMBOL("READ-ICP-RETURNED-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qread_icp_returned_external_simulation_object,
	    STATIC_FUNCTION(read_icp_returned_external_simulation_object,
	    NIL,FALSE,0,0));
    Qdummy_definition = STATIC_SYMBOL("DUMMY-DEFINITION",AB_package);
    Qwrite_icp_returned_external_simulation_object = 
	    STATIC_SYMBOL("WRITE-ICP-RETURNED-EXTERNAL-SIMULATION-OBJECT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icp_returned_external_simulation_object,
	    STATIC_FUNCTION(write_icp_returned_external_simulation_object,
	    NIL,FALSE,1,1));
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    string_constant_11 = 
	    STATIC_STRING("Attempting to execute GSPAN functionality.  GSPAN has been ~\n            discontinued as a product and its features were removed from G2 ~\n            as of Version 4.0.");
    Qexternal_simulation_object_structure = 
	    STATIC_SYMBOL("EXTERNAL-SIMULATION-OBJECT-STRUCTURE",AB_package);
    Qcalculating_state_variables = 
	    STATIC_SYMBOL("CALCULATING-STATE-VARIABLES",AB_package);
    Qinitialization = STATIC_SYMBOL("INITIALIZATION",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    string_constant_12 = 
	    STATIC_STRING("ICP connection to external simulator is broken.");
    Qno_work_done_yet_for_this_cycle = 
	    STATIC_SYMBOL("NO-WORK-DONE-YET-FOR-THIS-CYCLE",AB_package);
    Qwork_completed_for_this_cycle = 
	    STATIC_SYMBOL("WORK-COMPLETED-FOR-THIS-CYCLE",AB_package);
    Qwaiting_for_values = STATIC_SYMBOL("WAITING-FOR-VALUES",AB_package);
    Qsend_connection_information_to_external_simulator_1 = 
	    STATIC_SYMBOL("SEND-CONNECTION-INFORMATION-TO-EXTERNAL-SIMULATOR-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_connection_information_to_external_simulator_1,
	    STATIC_FUNCTION(send_connection_information_to_external_simulator_1,
	    NIL,FALSE,1,1));
    string_constant_13 = STATIC_STRING("");
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    Qsave_path = STATIC_SYMBOL("SAVE-PATH",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    string_constant_14 = 
	    STATIC_STRING("Problem encountered simulating the entity ~NF externally.  The ~a\nvalue ~a is not a number.");
    Qsend_icp_speedup_begin_tagnames = 
	    STATIC_SYMBOL("SEND-ICP-SPEEDUP-BEGIN-TAGNAMES",AB_package);
    Qspeedup_begin_tagnames = STATIC_SYMBOL("SPEEDUP-BEGIN-TAGNAMES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_begin_tagnames,
	    STATIC_FUNCTION(send_icp_speedup_begin_tagnames,NIL,FALSE,0,0));
    Qhandle_icp_speedup_begin_tagnames = 
	    STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-BEGIN-TAGNAMES",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_begin_tagnames,
	    STATIC_FUNCTION(handle_icp_speedup_begin_tagnames,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_begin_tagnames,
	    FIX((SI_Long)251L));
    Qsend_icp_speedup_input_or_output_tagnames = 
	    STATIC_SYMBOL("SEND-ICP-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES",
	    AB_package);
    Qspeedup_input_or_output_tagnames = 
	    STATIC_SYMBOL("SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES",AB_package);
    Qinput_or_output_tagnames = STATIC_SYMBOL("INPUT-OR-OUTPUT-TAGNAMES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_input_or_output_tagnames,
	    STATIC_FUNCTION(send_icp_speedup_input_or_output_tagnames,NIL,
	    FALSE,1,1));
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qhandle_icp_speedup_input_or_output_tagnames = 
	    STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-INPUT-OR-OUTPUT-TAGNAMES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_input_or_output_tagnames,
	    STATIC_FUNCTION(handle_icp_speedup_input_or_output_tagnames,
	    NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_input_or_output_tagnames,
	    FIX((SI_Long)252L));
    Qsend_icp_speedup_tagname = STATIC_SYMBOL("SEND-ICP-SPEEDUP-TAGNAME",
	    AB_package);
    Qspeedup_tagname = STATIC_SYMBOL("SPEEDUP-TAGNAME",AB_package);
    Qtagname = STATIC_SYMBOL("TAGNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_tagname,
	    STATIC_FUNCTION(send_icp_speedup_tagname,NIL,FALSE,1,1));
    Qhandle_icp_speedup_tagname = 
	    STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-TAGNAME",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_tagname,
	    STATIC_FUNCTION(handle_icp_speedup_tagname,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_tagname,FIX((SI_Long)253L));
    Qsend_icp_speedup_end_tagnames = 
	    STATIC_SYMBOL("SEND-ICP-SPEEDUP-END-TAGNAMES",AB_package);
    Qspeedup_end_tagnames = STATIC_SYMBOL("SPEEDUP-END-TAGNAMES",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_end_tagnames,
	    STATIC_FUNCTION(send_icp_speedup_end_tagnames,NIL,FALSE,0,0));
    Qhandle_icp_speedup_end_tagnames = 
	    STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-END-TAGNAMES",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_end_tagnames,
	    STATIC_FUNCTION(handle_icp_speedup_end_tagnames,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_end_tagnames,
	    FIX((SI_Long)254L));
    Qexternal = STATIC_SYMBOL("EXTERNAL",AB_package);
    Qsend_icp_speedup_begin_values = 
	    STATIC_SYMBOL("SEND-ICP-SPEEDUP-BEGIN-VALUES",AB_package);
    Qspeedup_begin_values = STATIC_SYMBOL("SPEEDUP-BEGIN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_begin_values,
	    STATIC_FUNCTION(send_icp_speedup_begin_values,NIL,FALSE,0,0));
    Qhandle_icp_speedup_begin_values = 
	    STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-BEGIN-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_begin_values,
	    STATIC_FUNCTION(handle_icp_speedup_begin_values,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_begin_values,
	    FIX((SI_Long)255L));
    Qsend_icp_speedup_value = STATIC_SYMBOL("SEND-ICP-SPEEDUP-VALUE",
	    AB_package);
    Qspeedup_value = STATIC_SYMBOL("SPEEDUP-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qsend_icp_speedup_value,
	    STATIC_FUNCTION(send_icp_speedup_value,NIL,FALSE,1,1));
    Qhandle_icp_speedup_value = STATIC_SYMBOL("HANDLE-ICP-SPEEDUP-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_icp_speedup_value,
	    STATIC_FUNCTION(handle_icp_speedup_value,NIL,FALSE,0,0));
    add_icp_message_handler(Qhandle_icp_speedup_value,FIX((SI_Long)256L));
    Qof = STATIC_SYMBOL("OF",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qof,Qthe);
    Qnon_symbol_in_speedup_tagname = 
	    STATIC_SYMBOL("NON-SYMBOL-IN-SPEEDUP-TAGNAME",AB_package);
    string_constant_15 = 
	    STATIC_STRING("Unable to read a symbol beginning with character ~d in the SPEEDUP tagname ~s.");
    Qsimulation_error_catch = STATIC_SYMBOL("SIMULATION-ERROR-CATCH",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnon_symbol_in_speedup_tagname,
	    STATIC_FUNCTION(non_symbol_in_speedup_tagname,NIL,FALSE,2,2));
    Qincorrect_format_for_speedup_tagname = 
	    STATIC_SYMBOL("INCORRECT-FORMAT-FOR-SPEEDUP-TAGNAME",AB_package);
    string_constant_16 = 
	    STATIC_STRING("The SPEEDUP tagname ~a does not have the correct format.");
    SET_SYMBOL_FUNCTION(Qincorrect_format_for_speedup_tagname,
	    STATIC_FUNCTION(incorrect_format_for_speedup_tagname,NIL,FALSE,
	    1,1));
    Qspeedup_tagname_not_variable = 
	    STATIC_SYMBOL("SPEEDUP-TAGNAME-NOT-VARIABLE",AB_package);
    string_constant_17 = 
	    STATIC_STRING("The SPEEDUP output designation ~s refers to ~s, which is not a variable or parameter.");
    SET_SYMBOL_FUNCTION(Qspeedup_tagname_not_variable,
	    STATIC_FUNCTION(speedup_tagname_not_variable,NIL,FALSE,2,2));
    Qspeedup_simulation_conflict = 
	    STATIC_SYMBOL("SPEEDUP-SIMULATION-CONFLICT",AB_package);
    string_constant_18 = 
	    string_append2(STATIC_STRING("The SPEEDUP output designation ~s refers to ~s which is already being simulated. ~\n    Please check if this variable is designated more than once by SPEEDUP tagnames, or ~\n   "),
	    STATIC_STRING(" if it is being simulated by G2."));
    SET_SYMBOL_FUNCTION(Qspeedup_simulation_conflict,
	    STATIC_FUNCTION(speedup_simulation_conflict,NIL,FALSE,2,2));
    Qspeedup_output_variable_deleted = 
	    STATIC_SYMBOL("SPEEDUP-OUTPUT-VARIABLE-DELETED",AB_package);
    string_constant_19 = 
	    STATIC_STRING("A variable simulated by SPEEDUP has been deleted.");
    SET_SYMBOL_FUNCTION(Qspeedup_output_variable_deleted,
	    STATIC_FUNCTION(speedup_output_variable_deleted,NIL,FALSE,0,0));
    Qspeedup_input_value_not_a_number = 
	    STATIC_SYMBOL("SPEEDUP-INPUT-VALUE-NOT-A-NUMBER",AB_package);
    string_constant_20 = 
	    STATIC_STRING("The SPEEDUP input designation ~s evaluates to ~s, which is not a number.");
    SET_SYMBOL_FUNCTION(Qspeedup_input_value_not_a_number,
	    STATIC_FUNCTION(speedup_input_value_not_a_number,NIL,FALSE,2,2));
}
