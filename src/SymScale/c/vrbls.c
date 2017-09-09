/* vrbls.c
 * Input file:  variables.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "vrbls.h"


DEFINE_VARIABLE_WITH_SYMBOL(Stack_eval_qm, Qstack_eval_qm);

Object Formulas_for_this_role_kbprop = UNBOUND;

/* PUT-GENERIC-FORMULA-BYTE-CODE-BODY-WHERE-SLOT-IS-ABSENT */
Object put_generic_formula_byte_code_body_where_slot_is_absent(generic_formula,
	    byte_code_body)
    Object generic_formula, byte_code_body;
{
    x_note_fn_call(147,0);
    reclaim_slot_value(byte_code_body);
    return VALUES_1(Nil);
}

static Object Qgeneric_formula;    /* generic-formula */

static Object Qcell_array;         /* cell-array */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qg2_cell_array;      /* g2-cell-array */

/* INITIALIZE-FOR-GENERIC-FORMULA */
Object initialize_for_generic_formula(generic_formula)
    Object generic_formula;
{
    Object frame, sub_vector_qm, method_function_qm, x, x2, gensymed_symbol;
    Object sub_class_bit_vector, current_block_of_dependent_frame;
    Object new_cell_array;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,1);
    frame = generic_formula;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgeneric_formula)) {
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
    x = get_lookup_slot_value_given_default(generic_formula,Qcell_array,Nil);
    if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(x,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_cell_array_class_description,(SI_Long)18L));
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
    if ( !temp) {
	current_block_of_dependent_frame = generic_formula;
	PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		0);
	  new_cell_array = make_frame(Qg2_cell_array);
	  change_slot_value(3,generic_formula,Qcell_array,new_cell_array);
	  result = make_empty_expression_cell(new_cell_array);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* CLEANUP-FOR-GENERIC-FORMULA */
Object cleanup_for_generic_formula(generic_formula)
    Object generic_formula;
{
    Object frame, sub_vector_qm, method_function_qm, temp, old_role_name;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Object svref_arg_2, result_1, current_flag_state_qm, slot_description;
    Object new_cons, svref_new_value, stack_of_slot_value_changes;
    Object gensymed_symbol_3, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, stack_change_pop_store, cons_1, next_cons;
    SI_Long index_1, ab_loop_bind_, svref_new_value_1;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(147,2);
    frame = generic_formula;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qgeneric_formula)) {
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
    temp = ISVREF(generic_formula,(SI_Long)16L);
    temp = CAR(temp);
    old_role_name = FIRST(temp);
    if (old_role_name) {
	gensymed_symbol = generic_formula;
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = 
		lookup_kb_specific_property_value(old_role_name,
		Formulas_for_this_role_kbprop);
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_1;
	if (EQ(CAR(gensymed_symbol_2),gensymed_symbol)) {
	    if (gensymed_symbol_1) {
		temp_1 = CDR(gensymed_symbol_2);
		M_CDR(gensymed_symbol_1) = temp_1;
	    }
	    else
		mutate_kb_specific_property_value(old_role_name,
			CDR(gensymed_symbol_2),Formulas_for_this_role_kbprop);
	    inline_note_reclaim_cons(gensymed_symbol_2,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_2;
	    }
	    M_CDR(gensymed_symbol_2) = Nil;
	    goto end_2;
	}
	gensymed_symbol_1 = gensymed_symbol_2;
	gensymed_symbol_2 = CDR(gensymed_symbol_2);
	goto next_loop_1;
      end_loop_1:
      end_2:;
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(generic_formula,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(generic_formula,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = generic_formula;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp_1 = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp_1;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    0);
      current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(generic_formula,
	      (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(generic_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_formula;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(generic_formula,(SI_Long)5L)) | 
		  (SI_Long)16777216L;
	  ISVREF(generic_formula,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      result_1 = change_slot_value(3,generic_formula,Qcell_array,Nil);
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(generic_formula,(SI_Long)5L)) &  
		  ~(SI_Long)16777216L;
	  ISVREF(generic_formula,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(generic_formula,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = generic_formula;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_2;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(generic_formula,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_3;
	  }
	  goto next_loop_2;
	end_loop_2:
	  temp_2 = TRUEP(Qnil);
	end_3:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(generic_formula,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(generic_formula);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp_1 = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp_1) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp_1,svref_arg_2) = cons_1;
	  }
	  else {
	      temp_1 = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp_1,svref_arg_2) = cons_1;
	      temp_1 = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp_1,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return change_slot_value(3,generic_formula,Qbox_translation_and_text,Nil);
}

/* RECLAIM-G2-INTERNAL-CACHED-EXPLANATION-VALUE */
Object reclaim_g2_internal_cached_explanation_value(cached_explanation,
	    gensymed_symbol)
    Object cached_explanation, gensymed_symbol;
{
    x_note_fn_call(147,3);
    if (cached_explanation)
	reclaim_cached_explanation(cached_explanation);
    return VALUES_1(Nil);
}

/* DATA-TYPE-OF-VARIABLE-OR-PARAMETER-FUNCTION */
Object data_type_of_variable_or_parameter_function(variable_or_parameter)
    Object variable_or_parameter;
{
    x_note_fn_call(147,4);
    return VALUES_1(ISVREF(variable_or_parameter,(SI_Long)20L));
}

DEFINE_VARIABLE_WITH_SYMBOL(Generic_simulation_formulas_used_p, Qgeneric_simulation_formulas_used_p);

static Object Qvariable_or_parameter;  /* variable-or-parameter */

/* INITIALIZE-AFTER-READING-FOR-VARIABLE-OR-PARAMETER */
Object initialize_after_reading_for_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object frame, sub_vector_qm, method_function_qm, sub_class_bit_vector;
    Object initial_value, svref_new_value, store_managed_number_or_value_arg_1;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;
    double store_managed_number_or_value_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(147,5);
    frame = variable_or_parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qvariable_or_parameter)) {
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
    fix_up_initial_value_of_variable_or_parameter(2,variable_or_parameter,T);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
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
	initial_value = ISVREF(variable_or_parameter,(SI_Long)22L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value)) == 
		    (SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		store_managed_number_or_value_arg = 
			DFLOAT_ISAREF_1(initial_value,(SI_Long)0L);
		svref_new_value = 
			store_managed_number_or_value_function(ISVREF(variable_or_parameter,
			(SI_Long)23L),
			DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
		ISVREF(variable_or_parameter,(SI_Long)23L) = svref_new_value;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else {
	    store_managed_number_or_value_arg_1 = initial_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(variable_or_parameter,
		    (SI_Long)23L),store_managed_number_or_value_arg_1);
	    ISVREF(variable_or_parameter,(SI_Long)23L) = svref_new_value;
	}
    }
    update_representations_of_variable_or_parameter_value(variable_or_parameter);
    if (Generic_simulation_formulas_used_p)
	return update_generic_simulation_formula_for_variable_or_parameter(variable_or_parameter);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Attribute_nesting_depth, Qattribute_nesting_depth);

/* INITIALIZE-FOR-VARIABLE-OR-PARAMETER */
Object initialize_for_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(147,6);
    frame = variable_or_parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qvariable_or_parameter)) {
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
    if (Generic_simulation_formulas_used_p && 
	    IFIX(Attribute_nesting_depth) == (SI_Long)1L)
	return update_generic_simulation_formula_for_variable_or_parameter(variable_or_parameter);
    else
	return VALUES_1(Nil);
}

/* PUT-SIMULATION-CATEGORY?-WHERE-SLOT-IS-ABSENT */
Object put_simulation_category_qm_where_slot_is_absent(variable_or_parameter,
	    value)
    Object variable_or_parameter, value;
{
    x_note_fn_call(147,7);
    return VALUES_1(Nil);
}

/* PUT-INITIAL-SIMULATED-VALUE?-WHERE-SLOT-IS-ABSENT */
Object put_initial_simulated_value_qm_where_slot_is_absent(variable_or_parameter,
	    value)
    Object variable_or_parameter, value;
{
    x_note_fn_call(147,8);
    return VALUES_1(Nil);
}

/* PUT-FORMULA-SPECIFIED-TIME-INCREMENT-FOR-UPDATE?-WHERE-SLOT-IS-ABSENT */
Object put_formula_specified_time_increment_for_update_qm_where_slot_is_absent(variable_or_parameter,
	    value)
    Object variable_or_parameter, value;
{
    x_note_fn_call(147,9);
    return VALUES_1(Nil);
}

static Object Qdata_type_of_variable_or_parameter;  /* data-type-of-variable-or-parameter */

/* PUT-DATA-TYPE-OF-VARIABLE-OR-PARAMETER */
Object put_data_type_of_variable_or_parameter(variable,new_data_type,
	    gensymed_symbol)
    Object variable, new_data_type, gensymed_symbol;
{
    x_note_fn_call(147,10);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qdata_type_of_variable_or_parameter);
    SVREF(variable,FIX((SI_Long)20L)) = new_data_type;
    handle_update_to_sensor_data_type(variable);
    return VALUES_1(new_data_type);
}

/* PUT-DATA-TYPE-OF-VARIABLE-WHERE-SLOT-IS-ABSENT */
Object put_data_type_of_variable_where_slot_is_absent(variable,value)
    Object variable, value;
{
    x_note_fn_call(147,11);
    change_slot_value(3,variable,Qdata_type_of_variable_or_parameter,value);
    return VALUES_1(Nil);
}

static Object Qvariable_or_parameter_history_specification_qm;  /* variable-or-parameter-history-specification? */

/* PUT-VARIABLE-STORED-HISTORY-SPECIFICATION?-WHERE-SLOT-IS-ABSENT */
Object put_variable_stored_history_specification_qm_where_slot_is_absent(variable,
	    value)
    Object variable, value;
{
    x_note_fn_call(147,12);
    change_slot_value(3,variable,
	    Qvariable_or_parameter_history_specification_qm,value);
    return VALUES_1(Nil);
}

static Object Qsimulation_details;  /* simulation-details */

/* PUT-SIMULATION-FRAME?-WHERE-SLOT-IS-ABSENT */
Object put_simulation_frame_qm_where_slot_is_absent(variable,value)
    Object variable, value;
{
    x_note_fn_call(147,13);
    change_slot_value(3,variable,Qsimulation_details,value);
    return VALUES_1(Nil);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

/* CLEANUP-FOR-VARIABLE */
Object cleanup_for_variable(variable)
    Object variable;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(147,14);
    frame = variable;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qvariable)) {
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
    delete_dynamic_rule_displays_for_rule_or_object(variable);
    delete_backward_chaining_display_if_any_for_variable(variable);
    change_slot_value(3,variable,
	    Qvariable_or_parameter_history_specification_qm,Nil);
    return change_slot_value(3,variable,Qsimulation_info_qm,Nil);
}

static Object Qparameter;          /* parameter */

/* CLEANUP-FOR-PARAMETER */
Object cleanup_for_parameter(parameter)
    Object parameter;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(147,15);
    frame = parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qparameter)) {
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
    delete_dynamic_rule_displays_for_rule_or_object(parameter);
    change_slot_value(3,parameter,
	    Qvariable_or_parameter_history_specification_qm,Nil);
    return change_slot_value(3,parameter,Qsimulation_info_qm,Nil);
}

static Object Qobject;             /* object */

/* CLEANUP-FOR-OBJECT */
Object cleanup_for_object(object)
    Object object;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(147,16);
    frame = object;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qobject)) {
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
    return delete_dynamic_rule_displays_for_rule_or_object(object);
}

/* PUT-RULE-TO-INVOKE-WHEN-VALUE-ARRIVES?-WHERE-SLOT-IS-ABSENT */
Object put_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent(sensor,
	    old_rule_to_invoke_value)
    Object sensor, old_rule_to_invoke_value;
{
    x_note_fn_call(147,17);
    return VALUES_1(Nil);
}

/* PUT-RULE-TO-INVOKE-WHEN-SENSOR-FAILS?-WHERE-SLOT-IS-ABSENT */
Object put_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent(sensor,
	    old_rule_to_invoke_value)
    Object sensor, old_rule_to_invoke_value;
{
    x_note_fn_call(147,18);
    return VALUES_1(Nil);
}

static Object Qformula_qm;         /* formula? */

/* PUT-FORMULA? */
Object put_formula_qm(variable,new_formula_qm,initializing_qm)
    Object variable, new_formula_qm, initializing_qm;
{
    Object car_new_value;

    x_note_fn_call(147,19);
    if (CONSP(new_formula_qm) && initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(variable)) && Loading_kb_p) {
	reclaim_slot_value(CAR(new_formula_qm));
	car_new_value = No_value;
	M_CAR(new_formula_qm) = car_new_value;
	note_frame_with_compilation_removed(variable);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable,Qformula_qm);
    return VALUES_1(SVREF(variable,FIX((SI_Long)28L)) = new_formula_qm);
}

static Object Qtruth_value;        /* truth-value */

/* VALID-INITIAL-VALUE-P */
Object valid_initial_value_p(variable_or_parameter)
    Object variable_or_parameter;
{
    Object managed_value, sub_class_bit_vector, required_type;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(147,20);
    managed_value = ISVREF(variable_or_parameter,(SI_Long)22L);
    if ( !TRUEP(managed_value)) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	required_type = 
		get_data_type_of_variable_or_parameter_from_frame(1,
		variable_or_parameter);
	if (lookup_global_or_kb_specific_property_value(required_type,
		Numeric_data_type_gkbprop))
	    required_type = Qnumber;
	if (EQ(required_type,Qtruth_value)) {
	    if (FIXNUMP(managed_value)) {
		if (FIXNUM_LE(Falsity,managed_value))
		    return VALUES_1(FIXNUM_LE(managed_value,Truth) ? T : Nil);
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return symbolic_type_specification_subtype_p(evaluation_value_type(managed_value),
		    required_type);
    }
}

static Object Qinitial_value_of_variable_or_parameter;  /* initial-value-of-variable-or-parameter */

/* FIX-UP-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER */
Object fix_up_initial_value_of_variable_or_parameter varargs_1(int, n)
{
    Object variable_or_parameter;
    Object report_if_bad_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(147,21);
    INIT_ARGS_nonrelocating();
    variable_or_parameter = REQUIRED_ARG_nonrelocating();
    report_if_bad_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ( !TRUEP(valid_initial_value_p(variable_or_parameter))) {
	if (report_if_bad_qm)
	    report_bad_initial_value_of_variable_or_parameter(variable_or_parameter);
	return change_slot_value(3,variable_or_parameter,
		Qinitial_value_of_variable_or_parameter,
		get_slot_init_form(2,ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)1L),
		Qinitial_value_of_variable_or_parameter));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "The initial-value (~NV) of ~NF is not of the valid type (~NT) for this ~
				    *        class.  Changing value to ~NV, the default for class ~A."
				    */

/* REPORT-BAD-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER */
Object report_bad_initial_value_of_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object value, evaluation_value_qm, type, class_1, init_form;
    Object init_form_evaluation_value_qm;
    char logical_qm;

    x_note_fn_call(147,22);
    value = ISVREF(variable_or_parameter,(SI_Long)22L);
    if (value) {
	if (Nil) {
	    if (FIXNUM_EQ(value,Truth))
		evaluation_value_qm = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		evaluation_value_qm = Evaluation_false_value;
	    else
		evaluation_value_qm = eval_cons_1(value,Qtruth_value);
	}
	else
	    evaluation_value_qm = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) 
		    != (SI_Long)0L ? copy_wide_string(value) : 
		    FIXNUMP(value) || SYMBOLP(value) ? value : 
		    copy_evaluation_value_1(value);
    }
    else
	evaluation_value_qm = Nil;
    type = get_data_type_of_variable_or_parameter_from_frame(1,
	    variable_or_parameter);
    class_1 = ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),(SI_Long)1L);
    init_form = get_slot_init_form(2,class_1,
	    Qinitial_value_of_variable_or_parameter);
    if (init_form) {
	logical_qm = EQ(type,Qtruth_value);
	value = init_form;
	if (logical_qm) {
	    if (FIXNUM_EQ(value,Truth))
		init_form_evaluation_value_qm = Evaluation_true_value;
	    else if (FIXNUM_EQ(value,Falsity))
		init_form_evaluation_value_qm = Evaluation_false_value;
	    else
		init_form_evaluation_value_qm = eval_cons_1(value,
			Qtruth_value);
	}
	else
	    init_form_evaluation_value_qm = 
		    INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != (SI_Long)0L 
		    ? copy_wide_string(value) : FIXNUMP(value) || 
		    SYMBOLP(value) ? value : copy_evaluation_value_1(value);
    }
    else
	init_form_evaluation_value_qm = Nil;
    notify_user_at_console_and_on_logbook(6,string_constant,
	    evaluation_value_qm,variable_or_parameter,type,
	    init_form_evaluation_value_qm,class_1);
    if (evaluation_value_qm)
	reclaim_evaluation_value(evaluation_value_qm);
    if (init_form_evaluation_value_qm)
	return reclaim_evaluation_value(init_form_evaluation_value_qm);
    else
	return VALUES_1(Nil);
}

/* PUT-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER */
Object put_initial_value_of_variable_or_parameter(variable_or_parameter,
	    new_value,initialize_qm)
    Object variable_or_parameter, new_value, initialize_qm;
{
    Object default_value, sub_class_bit_vector;
    Object store_managed_number_or_value_arg, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(147,23);
    default_value = get_slot_init_form(2,
	    ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),(SI_Long)1L),
	    Qinitial_value_of_variable_or_parameter);
    if ( !EQ(new_value,default_value) && EQ(variable_or_parameter,new_value)) {
	if (text_string_p(new_value) && text_string_p(default_value) && 
		string_eq_w(new_value,default_value)) {
	    reclaim_slot_value(new_value);
	    new_value = default_value;
	}
	else if ((FLOATP(new_value) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == (SI_Long)1L) 
		&& (FLOATP(default_value) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(default_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(default_value)) == 
		(SI_Long)1L)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != (SI_Long)0L 
			&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == 
			(SI_Long)1L)
		    arg = DFLOAT_ISAREF_1(new_value,(SI_Long)0L);
		else
		    arg = DOUBLE_FLOAT_TO_DOUBLE(new_value);
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(default_value) != 
			(SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(default_value)) == 
			(SI_Long)1L)
		    arg_1 = DFLOAT_ISAREF_1(default_value,(SI_Long)0L);
		else
		    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(default_value);
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == 
			    (SI_Long)1L)
			reclaim_slot_value(new_value);
		    new_value = default_value;
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(variable_or_parameter,
		Qinitial_value_of_variable_or_parameter);
    SVREF(variable_or_parameter,FIX((SI_Long)22L)) = new_value;
    if ( !(System_is_running || System_has_paused || initialize_qm)) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    store_managed_number_or_value_arg = 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(new_value) != (SI_Long)0L 
		    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value)) == 
		    (SI_Long)1L ? 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_value,
		    (SI_Long)0L)) : new_value;
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(variable_or_parameter,
		    (SI_Long)23L),store_managed_number_or_value_arg);
	    ISVREF(variable_or_parameter,(SI_Long)23L) = svref_new_value;
	}
	POP_LOCAL_ALLOCATION(0,0);
	update_representations_of_variable_or_parameter_value(variable_or_parameter);
    }
    return VALUES_1(new_value);
}

/* INITIALIZE-FOR-PARAMETER */
Object initialize_for_parameter(parameter)
    Object parameter;
{
    Object frame, sub_vector_qm, method_function_qm, initial_qm;
    Object svref_new_value, store_managed_number_or_value_arg_1;
    SI_Long index_1, ab_loop_bind_;
    double store_managed_number_or_value_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(147,24);
    frame = parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qparameter)) {
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
    initial_qm = ISVREF(parameter,(SI_Long)22L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_qm)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    store_managed_number_or_value_arg = DFLOAT_ISAREF_1(initial_qm,
		    (SI_Long)0L);
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(parameter,
		    (SI_Long)23L),
		    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	    ISVREF(parameter,(SI_Long)23L) = svref_new_value;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	store_managed_number_or_value_arg_1 = initial_qm;
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(parameter,
		(SI_Long)23L),store_managed_number_or_value_arg_1);
	ISVREF(parameter,(SI_Long)23L) = svref_new_value;
    }
    return VALUES_1(Nil);
}

static Object Qdatum;              /* datum */

static Object Qlong;               /* long */

/* TYPE-SPECIFICATION-OF-VARIABLE-OR-PARAMETER-VALUE */
Object type_specification_of_variable_or_parameter_value(variable_or_parameter)
    Object variable_or_parameter;
{
    Object stored_data_type, temp;

    x_note_fn_call(147,25);
    stored_data_type = ISVREF(variable_or_parameter,(SI_Long)20L);
    if (symbolic_type_specification_subtype_p(stored_data_type,Qdatum))
	temp = stored_data_type;
    else if (EQ(stored_data_type,Qnumber) || EQ(stored_data_type,Qinteger) 
	    || EQ(stored_data_type,Qfloat) || EQ(stored_data_type,Qlong) 
	    || 
	    lookup_global_or_kb_specific_property_value(stored_data_type,
	    Numeric_data_type_gkbprop))
	temp = Qnumber;
    else
	temp = Qdatum;
    return VALUES_1(temp);
}

static Object Qcurrent_value_of_variable_or_parameter;  /* current-value-of-variable-or-parameter */

static Object Qparent_frame;       /* parent-frame */

/* UPDATE-REPRESENTATIONS-OF-VARIABLE-OR-PARAMETER-VALUE */
Object update_representations_of_variable_or_parameter_value(variable_or_parameter)
    Object variable_or_parameter;
{
    Object temp, class_description, parent_frame, slot_name;
    Object class_qualifier_qm;
    Object result;

    x_note_fn_call(147,26);
    if (ISVREF(variable_or_parameter,(SI_Long)9L)) {
	temp = 
		get_slot_description_of_class_description_function(Qcurrent_value_of_variable_or_parameter,
		ISVREF(variable_or_parameter,(SI_Long)1L),Nil);
	if (temp);
	else {
	    class_description = 
		    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(variable_or_parameter,
		    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	    temp = get_slot_description(3,
		    Qcurrent_value_of_variable_or_parameter,
		    ISVREF(class_description,(SI_Long)6L),Nil);
	}
	change_slot_description_value_function(variable_or_parameter,temp,
		Just_update_representations_of_slot_value,Nil,Nil);
    }
    if (get_lookup_slot_value_given_default(variable_or_parameter,
	    Qparent_frame,Nil) && 
	    ISVREF(get_lookup_slot_value_given_default(variable_or_parameter,
	    Qparent_frame,Nil),(SI_Long)9L)) {
	result = get_kb_parent_information(variable_or_parameter);
	MVS_3(result,parent_frame,slot_name,class_qualifier_qm);
	temp = 
		get_slot_description_of_class_description_function(slot_name,
		ISVREF(parent_frame,(SI_Long)1L),class_qualifier_qm);
	if (temp);
	else {
	    class_description = 
		    lookup_global_or_kb_specific_property_value(ISVREF(ISVREF(parent_frame,
		    (SI_Long)1L),(SI_Long)1L),Class_description_gkbprop);
	    temp = get_slot_description(3,slot_name,
		    ISVREF(class_description,(SI_Long)6L),class_qualifier_qm);
	}
	change_slot_description_value_function(parent_frame,temp,
		Just_update_representations_of_slot_value,Nil,Nil);
    }
    return update_subscriptions_from_variable_change(variable_or_parameter);
}

Object Priority_of_expiration_update_task = UNBOUND;

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qpropagate_variable_value_expiration;  /* propagate-variable-value-expiration */

/* SCHEDULE-UPDATE-FOR-VARIABLE-EXPIRATION */
Object schedule_update_for_variable_expiration(variable)
    Object variable;
{
    Object task, task_1, temp_1, structure_being_reclaimed, svref_arg_2, old;
    Object new_1, def_structure_schedule_task_variable, svref_new_value;
    SI_Long expiration, task_time, reschedule_task_arg;
    char temp, svref_new_value_1;
    double gensymed_symbol, arg, arg_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(147,27);
    expiration = IFIX(ISVREF(variable,(SI_Long)26L));
    task_time = expiration + (SI_Long)1L;
    task = ISVREF(variable,(SI_Long)39L);
    if (task && (ISVREF(task,(SI_Long)6L) || EQ(task,Current_schedule_task))) {
	gensymed_symbol = DFLOAT_ISAREF_1(ISVREF(task,(SI_Long)1L),
		(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
		(SI_Long)0L) + (double)IFIX(Gensym_time_at_start);
	arg = gensymed_symbol;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp);
	else {
	    arg = gensymed_symbol;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	    temp = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	if ((temp ? IFIX(Most_negative_fixnum) : 
		inline_floor_1(gensymed_symbol)) != task_time) {
	    reschedule_task_arg = task_time - IFIX(Gensym_time);
	    task_1 = ISVREF(variable,(SI_Long)39L);
	    if (task_1 && (ISVREF(task_1,(SI_Long)6L) || EQ(task_1,
		    Current_schedule_task))) {
		if (ISVREF(task_1,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(task_1);
		if (EQ(task_1,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (FIXNUM_EQ(ISVREF(task_1,(SI_Long)4L),
			Higher_than_any_priority))
		    SVREF(task_1,FIX((SI_Long)4L)) = Highest_system_priority;
		temp_1 = ISVREF(task_1,(SI_Long)1L);
		aref_new_value = DFLOAT_ISAREF_1(ISVREF(task_1,
			(SI_Long)3L) ? Current_g2_time : Current_real_time,
			(SI_Long)0L) + (double)reschedule_task_arg;
		DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
		future_task_schedule_2(task_1);
		task_1;
	    }
	    else {
		if (task_1) {
		    if (EQ(task_1,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(task_1,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(task_1);
		    inline_note_reclaim_cons(task_1,Nil);
		    structure_being_reclaimed = task_1;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(task_1,(SI_Long)9L));
		      SVREF(task_1,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp_1 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(task_1,FIX((SI_Long)0L)) = temp_1;
		    temp_1 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = task_1;
		}
		task_1 = Nil;
	    }
	    return VALUES_1(ISVREF(variable,(SI_Long)39L) = task_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = ISVREF(variable,(SI_Long)39L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task_1 = def_structure_schedule_task_variable;
	temp_1 = ISVREF(task_1,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 
		(double)(task_time - IFIX(Gensym_time));
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	temp_1 = ISVREF(task_1,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	svref_new_value_1 =  !TRUEP(Nil);
	SVREF(task_1,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	temp_1 = Priority_of_expiration_update_task;
	SVREF(task_1,FIX((SI_Long)4L)) = temp_1;
	SVREF(task_1,FIX((SI_Long)5L)) = Nil;
	SVREF(task_1,FIX((SI_Long)9L)) = Nil;
	SVREF(task_1,FIX((SI_Long)10L)) = Nil;
	SVREF(task_1,FIX((SI_Long)7L)) = Qpropagate_variable_value_expiration;
	temp_1 = SYMBOL_FUNCTION(Qpropagate_variable_value_expiration);
	SVREF(task_1,FIX((SI_Long)8L)) = temp_1;
	ISVREF(task_1,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task_1,FIX((SI_Long)13L)) = variable;
	new_1 = task_1;
	if (CAS_SVREF(variable,(SI_Long)39L,old,new_1)) {
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
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(old,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = old;
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = new_1;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* PROPAGATE-VARIABLE-VALUE-EXPIRATION */
Object propagate_variable_value_expiration(variable)
    Object variable;
{
    Object x2, star_current_computation_frame_star_previously_bound_qm;
    Object managed_number_or_value, old_value;

    x_note_fn_call(147,28);
    update_representations_of_variable_or_parameter_value(variable);
    if (SIMPLE_VECTOR_P(Current_computation_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_computation_frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(Current_computation_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(Current_computation_frame,(SI_Long)1L);
	star_current_computation_frame_star_previously_bound_qm = 
		SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	star_current_computation_frame_star_previously_bound_qm = Nil;
    managed_number_or_value = ISVREF(variable,(SI_Long)23L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	old_value = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		(SI_Long)0L));
    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) == 
	    (SI_Long)1L)
	old_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
    else
	old_value = managed_number_or_value;
    if ( !TRUEP(star_current_computation_frame_star_previously_bound_qm))
	Current_computation_frame = variable;
    invoke_update_functions_for_expired_value(variable,old_value);
    if ( !TRUEP(star_current_computation_frame_star_previously_bound_qm))
	Current_computation_frame = Nil;
    return VALUES_1(Nil);
}

/* PARENT-VARIABLE-FUNCTION */
Object parent_variable_function(simulation_subtable)
    Object simulation_subtable;
{
    x_note_fn_call(147,29);
    return VALUES_1(ISVREF(simulation_subtable,(SI_Long)22L));
}

/* PUT-SIMULATION-CLASS-WHERE-SLOT-IS-ABSENT */
Object put_simulation_class_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,30);
    return VALUES_1(Nil);
}

/* PUT-INITIAL-VALUE-FOR-SIMULATION?-WHERE-SLOT-IS-ABSENT */
Object put_initial_value_for_simulation_qm_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,31);
    return VALUES_1(Nil);
}

/* PUT-SIMULATION-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_simulation_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,32);
    return VALUES_1(Nil);
}

/* PUT-SIMULATION-VALUE-TIME-WHERE-SLOT-IS-ABSENT */
Object put_simulation_value_time_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,33);
    return VALUES_1(Nil);
}

/* PUT-NEW-SIMULATION-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_new_simulation_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,34);
    return VALUES_1(Nil);
}

/* PUT-NEW-SIMULATION-VALUE-TIME-WHERE-SLOT-IS-ABSENT */
Object put_new_simulation_value_time_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,35);
    return VALUES_1(Nil);
}

/* PUT-NEW-SIMULATION-VALUE-STEP-WHERE-SLOT-IS-ABSENT */
Object put_new_simulation_value_step_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,36);
    return VALUES_1(Nil);
}

/* PUT-K1-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_k1_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,37);
    return VALUES_1(Nil);
}

/* PUT-K2-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_k2_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,38);
    return VALUES_1(Nil);
}

/* PUT-K3-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_k3_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,39);
    return VALUES_1(Nil);
}

/* PUT-K4-VALUE-WHERE-SLOT-IS-ABSENT */
Object put_k4_value_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,40);
    return VALUES_1(Nil);
}

/* PUT-TIME-OF-NEXT-UPDATE-WHERE-SLOT-IS-ABSENT */
Object put_time_of_next_update_where_slot_is_absent(simulation_subtable,value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,41);
    return VALUES_1(Nil);
}

/* PUT-INTERVAL-AT-WHICH-TO-SEND-VALUE-TO-INFERENCE-ENGINE-WHERE-SLOT-IS-ABSENT */
Object put_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,42);
    return VALUES_1(Nil);
}

/* PUT-LAST-TIME-VALUE-SENT-TO-INFERENCE-ENGINE-WHERE-SLOT-IS-ABSENT */
Object put_last_time_value_sent_to_inference_engine_where_slot_is_absent(simulation_subtable,
	    value)
    Object simulation_subtable, value;
{
    x_note_fn_call(147,43);
    return VALUES_1(Nil);
}

Object The_type_description_of_simulation_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_simulation_infos, Qchain_of_available_simulation_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Simulation_info_count, Qsimulation_info_count);

Object Chain_of_available_simulation_infos_vector = UNBOUND;

/* SIMULATION-INFO-STRUCTURE-MEMORY-USAGE */
Object simulation_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(147,44);
    temp = Simulation_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SIMULATION-INFO-COUNT */
Object outstanding_simulation_info_count()
{
    Object def_structure_simulation_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(147,45);
    gensymed_symbol = IFIX(Simulation_info_count);
    def_structure_simulation_info_variable = 
	    Chain_of_available_simulation_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_simulation_info_variable))
	goto end_loop;
    def_structure_simulation_info_variable = 
	    ISVREF(def_structure_simulation_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SIMULATION-INFO-1 */
Object reclaim_simulation_info_1(simulation_info)
    Object simulation_info;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(147,46);
    inline_note_reclaim_cons(simulation_info,Nil);
    structure_being_reclaimed = simulation_info;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value(ISVREF(simulation_info,(SI_Long)3L));
      SVREF(simulation_info,FIX((SI_Long)3L)) = Nil;
      reclaim_slot_value(ISVREF(simulation_info,(SI_Long)4L));
      SVREF(simulation_info,FIX((SI_Long)4L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_simulation_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(simulation_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_simulation_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = simulation_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SIMULATION-INFO */
Object reclaim_structure_for_simulation_info(simulation_info)
    Object simulation_info;
{
    x_note_fn_call(147,47);
    return reclaim_simulation_info_1(simulation_info);
}

static Object Qg2_defstruct_structure_name_simulation_info_g2_struct;  /* g2-defstruct-structure-name::simulation-info-g2-struct */

/* MAKE-PERMANENT-SIMULATION-INFO-STRUCTURE-INTERNAL */
Object make_permanent_simulation_info_structure_internal()
{
    Object def_structure_simulation_info_variable;
    Object defstruct_g2_simulation_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(147,48);
    def_structure_simulation_info_variable = Nil;
    atomic_incff_symval(Qsimulation_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_simulation_info_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_simulation_info_variable = the_array;
	SVREF(defstruct_g2_simulation_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_simulation_info_g2_struct;
	def_structure_simulation_info_variable = 
		defstruct_g2_simulation_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_simulation_info_variable);
}

/* MAKE-SIMULATION-INFO-1 */
Object make_simulation_info_1()
{
    Object def_structure_simulation_info_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(147,49);
    def_structure_simulation_info_variable = 
	    ISVREF(Chain_of_available_simulation_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_simulation_info_variable) {
	svref_arg_1 = Chain_of_available_simulation_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_simulation_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_simulation_info_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_simulation_info_g2_struct;
    }
    else
	def_structure_simulation_info_variable = 
		make_permanent_simulation_info_structure_internal();
    inline_note_allocate_cons(def_structure_simulation_info_variable,Nil);
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_simulation_info_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_simulation_info_variable);
}

Object The_type_description_of_variable_simulation_runtime_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_variable_simulation_runtime_structures, Qchain_of_available_variable_simulation_runtime_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Variable_simulation_runtime_structure_count, Qvariable_simulation_runtime_structure_count);

Object Chain_of_available_variable_simulation_runtime_structures_vector = UNBOUND;

/* VARIABLE-SIMULATION-RUNTIME-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object variable_simulation_runtime_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(147,50);
    temp = Variable_simulation_runtime_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)26L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-COUNT */
Object outstanding_variable_simulation_runtime_structure_count()
{
    Object def_structure_variable_simulation_runtime_structure_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(147,51);
    gensymed_symbol = IFIX(Variable_simulation_runtime_structure_count);
    def_structure_variable_simulation_runtime_structure_variable = 
	    Chain_of_available_variable_simulation_runtime_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_variable_simulation_runtime_structure_variable))
	goto end_loop;
    def_structure_variable_simulation_runtime_structure_variable = 
	    ISVREF(def_structure_variable_simulation_runtime_structure_variable,
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

/* RECLAIM-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-INTERNAL-1 */
Object reclaim_variable_simulation_runtime_structure_internal_1(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(147,52);
    inline_note_reclaim_cons(variable_simulation_runtime_structure,Nil);
    structure_being_reclaimed = variable_simulation_runtime_structure;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)1L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)1L)) = temp;
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)1L)) = Nil;
      temp = 
	      reclaim_managed_number_or_value_function(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)2L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)2L)) = temp;
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)2L)) = Nil;
      reclaim_possible_managed_float(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)15L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)15L)) = Nil;
      reclaim_eval_list_1(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)18L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)18L)) = Nil;
      reclaim_simulation_runtime_cache(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)20L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)20L)) = Nil;
      reclaim_simulation_runtime_cache(ISVREF(variable_simulation_runtime_structure,
	      (SI_Long)22L));
      SVREF(variable_simulation_runtime_structure,FIX((SI_Long)22L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_variable_simulation_runtime_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(variable_simulation_runtime_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_variable_simulation_runtime_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = variable_simulation_runtime_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-VARIABLE-SIMULATION-RUNTIME-STRUCTURE */
Object reclaim_structure_for_variable_simulation_runtime_structure(variable_simulation_runtime_structure)
    Object variable_simulation_runtime_structure;
{
    x_note_fn_call(147,53);
    return reclaim_variable_simulation_runtime_structure_internal_1(variable_simulation_runtime_structure);
}

static Object Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct;  /* g2-defstruct-structure-name::variable-simulation-runtime-structure-g2-struct */

/* MAKE-PERMANENT-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_variable_simulation_runtime_structure_structure_internal()
{
    Object def_structure_variable_simulation_runtime_structure_variable;
    Object defstruct_g2_variable_simulation_runtime_structure_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(147,54);
    def_structure_variable_simulation_runtime_structure_variable = Nil;
    atomic_incff_symval(Qvariable_simulation_runtime_structure_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_variable_simulation_runtime_structure_variable = Nil;
	gensymed_symbol = (SI_Long)26L;
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
	defstruct_g2_variable_simulation_runtime_structure_variable = 
		the_array;
	SVREF(defstruct_g2_variable_simulation_runtime_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct;
	def_structure_variable_simulation_runtime_structure_variable = 
		defstruct_g2_variable_simulation_runtime_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_variable_simulation_runtime_structure_variable);
}

/* MAKE-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-1 */
Object make_variable_simulation_runtime_structure_1()
{
    Object def_structure_variable_simulation_runtime_structure_variable;
    Object svref_arg_1, svref_arg_2, svref_new_value;

    x_note_fn_call(147,55);
    def_structure_variable_simulation_runtime_structure_variable = 
	    ISVREF(Chain_of_available_variable_simulation_runtime_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_variable_simulation_runtime_structure_variable) {
	svref_arg_1 = 
		Chain_of_available_variable_simulation_runtime_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_variable_simulation_runtime_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_variable_simulation_runtime_structure_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct;
    }
    else
	def_structure_variable_simulation_runtime_structure_variable = 
		make_permanent_variable_simulation_runtime_structure_structure_internal();
    inline_note_allocate_cons(def_structure_variable_simulation_runtime_structure_variable,
	    Nil);
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)16L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)22L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_variable_simulation_runtime_structure_variable,
	    FIX((SI_Long)25L)) = Nil;
    return VALUES_1(def_structure_variable_simulation_runtime_structure_variable);
}

static Object Qfloat_array;        /* float-array */

/* SET-LAST-TIME-VALUE-SENT-TO-INFERENCE-ENGINE */
Object set_last_time_value_sent_to_inference_engine(variable,new_value)
    Object variable, new_value;
{
    Object old_value, amf_available_array_cons_qm, amf_array, temp, temp_1;
    Object amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(147,56);
    old_value = ISVREF(variable,(SI_Long)15L);
    if (FLOATP(new_value)) {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L) {
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(old_value,(SI_Long)0L,aref_new_value);
	    return VALUES_1(Nil);
	}
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(new_value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    return VALUES_1(SVREF(variable,FIX((SI_Long)15L)) = new_float);
	}
    }
    else {
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_value)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(old_value);
	return VALUES_1(SVREF(variable,FIX((SI_Long)15L)) = new_value);
    }
}

/* GET-OR-MAKE-SIMULATION-RUNTIME-CACHE */
Object get_or_make_simulation_runtime_cache(simulation_environment_vector_length,
	    runtime_structure,environment_for_initial_value_qm)
    Object simulation_environment_vector_length, runtime_structure;
    Object environment_for_initial_value_qm;
{
    Object existing_simulation_environment_vector_qm;

    x_note_fn_call(147,57);
    existing_simulation_environment_vector_qm = 
	    environment_for_initial_value_qm ? ISVREF(runtime_structure,
	    (SI_Long)22L) : ISVREF(runtime_structure,(SI_Long)20L);
    if ( !TRUEP(existing_simulation_environment_vector_qm))
	return set_simulation_environment_vector(runtime_structure,
		simulation_environment_vector_length,
		environment_for_initial_value_qm);
    else if (FIXNUM_EQ(length(existing_simulation_environment_vector_qm),
	    simulation_environment_vector_length))
	return VALUES_1(existing_simulation_environment_vector_qm);
    else {
	reclaim_simulation_runtime_cache(existing_simulation_environment_vector_qm);
	return set_simulation_environment_vector(runtime_structure,
		simulation_environment_vector_length,
		environment_for_initial_value_qm);
    }
}

/* SET-SIMULATION-ENVIRONMENT-VECTOR */
Object set_simulation_environment_vector(runtime_structure,length_1,
	    environment_for_initial_value_qm)
    Object runtime_structure, length_1, environment_for_initial_value_qm;
{
    Object new_vector;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(147,58);
    if (environment_for_initial_value_qm) {
	new_vector = 
		allocate_managed_simple_vector(buffer_size_for_partial_buffer(length_1,
		Environment_allocation_schemes));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_vector));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(new_vector,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	return VALUES_1(SVREF(runtime_structure,FIX((SI_Long)22L)) = 
		new_vector);
    }
    else {
	new_vector = 
		allocate_managed_simple_vector(buffer_size_for_partial_buffer(length_1,
		Environment_allocation_schemes));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_vector));
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(new_vector,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	return VALUES_1(SVREF(runtime_structure,FIX((SI_Long)20L)) = 
		new_vector);
    }
}

/* RECLAIM-SIMULATION-RUNTIME-CACHE */
Object reclaim_simulation_runtime_cache(simulation_runtime_cache_qm)
    Object simulation_runtime_cache_qm;
{
    x_note_fn_call(147,59);
    if (simulation_runtime_cache_qm)
	return reclaim_environment_vector(simulation_runtime_cache_qm);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_list_of_all_data_servers, Qglobal_list_of_all_data_servers);

Object Data_server_kbprop = UNBOUND;

Object Data_server_or_alias_qm_kbprop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(List_of_all_data_servers, Qlist_of_all_data_servers);

Object The_type_description_of_data_server = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_data_servers, Qchain_of_available_data_servers);

DEFINE_VARIABLE_WITH_SYMBOL(Data_server_count, Qdata_server_count);

Object Chain_of_available_data_servers_vector = UNBOUND;

/* DATA-SERVER-STRUCTURE-MEMORY-USAGE */
Object data_server_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(147,60);
    temp = Data_server_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)17L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-DATA-SERVER-COUNT */
Object outstanding_data_server_count()
{
    Object def_structure_data_server_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(147,61);
    gensymed_symbol = IFIX(Data_server_count);
    def_structure_data_server_variable = Chain_of_available_data_servers;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_data_server_variable))
	goto end_loop;
    def_structure_data_server_variable = 
	    ISVREF(def_structure_data_server_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-DATA-SERVER-1 */
Object reclaim_data_server_1(data_server)
    Object data_server;
{
    Object temp, svref_arg_2;

    x_note_fn_call(147,62);
    inline_note_reclaim_cons(data_server,Nil);
    temp = ISVREF(Chain_of_available_data_servers_vector,
	    IFIX(Current_thread_index));
    SVREF(data_server,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_data_servers_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = data_server;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-DATA-SERVER */
Object reclaim_structure_for_data_server(data_server)
    Object data_server;
{
    x_note_fn_call(147,63);
    return reclaim_data_server_1(data_server);
}

static Object Qg2_defstruct_structure_name_data_server_g2_struct;  /* g2-defstruct-structure-name::data-server-g2-struct */

/* MAKE-PERMANENT-DATA-SERVER-STRUCTURE-INTERNAL */
Object make_permanent_data_server_structure_internal()
{
    Object def_structure_data_server_variable;
    Object defstruct_g2_data_server_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(147,64);
    def_structure_data_server_variable = Nil;
    atomic_incff_symval(Qdata_server_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_data_server_variable = Nil;
	gensymed_symbol = (SI_Long)17L;
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
	defstruct_g2_data_server_variable = the_array;
	SVREF(defstruct_g2_data_server_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_data_server_g2_struct;
	def_structure_data_server_variable = defstruct_g2_data_server_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_data_server_variable);
}

/* MAKE-DATA-SERVER-1 */
Object make_data_server_1(name_of_data_server,
	    function_to_collect_one_shot_data,
	    function_to_begin_collecting_data,
	    function_to_stop_collecting_data,function_to_accept_data,
	    server_is_in_use,function_to_initialize_data_server,
	    function_to_set_external_variable,
	    function_to_shut_down_data_server_qm,
	    function_to_deliver_messages,function_to_pause_data_server_qm,
	    function_to_resume_data_server_qm,
	    function_to_request_accept_data_qm,
	    function_to_start_data_server_qm,function_to_reset_data_server_qm)
    Object name_of_data_server, function_to_collect_one_shot_data;
    Object function_to_begin_collecting_data, function_to_stop_collecting_data;
    Object function_to_accept_data, server_is_in_use;
    Object function_to_initialize_data_server;
    Object function_to_set_external_variable;
    Object function_to_shut_down_data_server_qm, function_to_deliver_messages;
    Object function_to_pause_data_server_qm, function_to_resume_data_server_qm;
    Object function_to_request_accept_data_qm;
    Object function_to_start_data_server_qm, function_to_reset_data_server_qm;
{
    Object def_structure_data_server_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(147,65);
    def_structure_data_server_variable = 
	    ISVREF(Chain_of_available_data_servers_vector,
	    IFIX(Current_thread_index));
    if (def_structure_data_server_variable) {
	svref_arg_1 = Chain_of_available_data_servers_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_data_server_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_data_server_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_data_server_g2_struct;
    }
    else
	def_structure_data_server_variable = 
		make_permanent_data_server_structure_internal();
    inline_note_allocate_cons(def_structure_data_server_variable,Nil);
    SVREF(def_structure_data_server_variable,FIX((SI_Long)1L)) = 
	    name_of_data_server;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)2L)) = 
	    function_to_collect_one_shot_data;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)3L)) = 
	    function_to_begin_collecting_data;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)4L)) = 
	    function_to_stop_collecting_data;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)5L)) = 
	    function_to_accept_data;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)6L)) = 
	    server_is_in_use;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)7L)) = 
	    function_to_initialize_data_server;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)8L)) = 
	    function_to_set_external_variable;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)9L)) = 
	    function_to_shut_down_data_server_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)10L)) = 
	    function_to_deliver_messages;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)11L)) = 
	    function_to_pause_data_server_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)12L)) = 
	    function_to_resume_data_server_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)14L)) = 
	    function_to_request_accept_data_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)15L)) = 
	    function_to_start_data_server_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)16L)) = 
	    function_to_reset_data_server_qm;
    SVREF(def_structure_data_server_variable,FIX((SI_Long)13L)) = Nil;
    return VALUES_1(def_structure_data_server_variable);
}

static Object Qcomputation;        /* computation */

/* INITIALIZE-DATA-SERVER-PROPERTIES */
Object initialize_data_server_properties()
{
    Object data_server, ab_loop_list_, name;

    x_note_fn_call(147,66);
    mutate_kb_specific_property_value(Qcomputation,Qcomputation,
	    Data_server_kbprop);
    mutate_kb_specific_property_value(Qcomputation,Qcomputation,
	    Data_server_or_alias_qm_kbprop);
    data_server = Nil;
    ab_loop_list_ = List_of_all_data_servers;
    name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    data_server = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    name = ISVREF(data_server,(SI_Long)1L);
    mutate_kb_specific_property_value(name,data_server,Data_server_kbprop);
    mutate_kb_specific_property_value(name,data_server,
	    Data_server_or_alias_qm_kbprop);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COPY-DATA-SERVERS-FOR-PROCESS */
Object copy_data_servers_for_process()
{
    Object data_server, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(147,67);
    data_server = Nil;
    ab_loop_list_ = Global_list_of_all_data_servers;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    data_server = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(copy_data_server(data_server),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* DEF-DATA-SERVER */
Object def_data_server varargs_1(int, n)
{
    Object name_of_data_server, function_to_collect_one_shot_data;
    Object function_to_begin_collecting_data, function_to_stop_collecting_data;
    Object function_to_accept_data, server_is_in_use;
    Object function_to_initialize_data_server;
    Object function_to_set_external_variable;
    Object function_to_shut_down_data_server_qm, function_to_deliver_messages;
    Object function_to_pause_data_server_qm, function_to_resume_data_server_qm;
    Object function_to_request_accept_data_qm;
    Object function_to_start_data_server_qm, function_to_reset_data_server_qm;
    Object new_server, data_server_cons, push_arg;
    Object global_list_of_all_data_servers_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(147,68);
    INIT_ARGS_nonrelocating();
    name_of_data_server = REQUIRED_ARG_nonrelocating();
    function_to_collect_one_shot_data = REQUIRED_ARG_nonrelocating();
    function_to_begin_collecting_data = REQUIRED_ARG_nonrelocating();
    function_to_stop_collecting_data = REQUIRED_ARG_nonrelocating();
    function_to_accept_data = REQUIRED_ARG_nonrelocating();
    server_is_in_use = REQUIRED_ARG_nonrelocating();
    function_to_initialize_data_server = REQUIRED_ARG_nonrelocating();
    function_to_set_external_variable = REQUIRED_ARG_nonrelocating();
    function_to_shut_down_data_server_qm = REQUIRED_ARG_nonrelocating();
    function_to_deliver_messages = REQUIRED_ARG_nonrelocating();
    function_to_pause_data_server_qm = REQUIRED_ARG_nonrelocating();
    function_to_resume_data_server_qm = REQUIRED_ARG_nonrelocating();
    function_to_request_accept_data_qm = REQUIRED_ARG_nonrelocating();
    function_to_start_data_server_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    function_to_reset_data_server_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    new_server = make_data_server_1(name_of_data_server,
	    function_to_collect_one_shot_data,
	    function_to_begin_collecting_data,
	    function_to_stop_collecting_data,function_to_accept_data,
	    server_is_in_use,function_to_initialize_data_server,
	    function_to_set_external_variable,
	    function_to_shut_down_data_server_qm,
	    function_to_deliver_messages,function_to_pause_data_server_qm,
	    function_to_resume_data_server_qm,
	    function_to_request_accept_data_qm,
	    function_to_start_data_server_qm,function_to_reset_data_server_qm);
    data_server_cons = Global_list_of_all_data_servers;
  next_loop:
    if ( !TRUEP(data_server_cons))
	goto end_loop;
    if (EQ(ISVREF(CAR(data_server_cons),(SI_Long)1L),name_of_data_server)) {
	M_CAR(data_server_cons) = new_server;
	return VALUES_1(Nil);
    }
    data_server_cons = M_CDR(data_server_cons);
    goto next_loop;
  end_loop:
    push_arg = new_server;
    global_list_of_all_data_servers_new_value = CONS(push_arg,
	    Global_list_of_all_data_servers);
    Global_list_of_all_data_servers = 
	    global_list_of_all_data_servers_new_value;
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_server_pretty_name_alist, Qdata_server_pretty_name_alist);

/* DEF-DATA-SERVER-PRETTY-PRINTER */
Object def_data_server_pretty_printer(data_server_symbol_name,
	    data_server_pretty_string_name)
    Object data_server_symbol_name, data_server_pretty_string_name;
{
    Object pretty_name_entry, temp;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(147,69);
    pretty_name_entry = assq_function(data_server_symbol_name,
	    Data_server_pretty_name_alist);
    if (pretty_name_entry)
	return VALUES_1(M_CDR(pretty_name_entry) = 
		data_server_pretty_string_name);
    else {
	if (PUSH_AREA(Dynamic_area,0)) {
	    temp = CONS(data_server_symbol_name,
		    data_server_pretty_string_name);
	    Data_server_pretty_name_alist = CONS(temp,
		    Data_server_pretty_name_alist);
	    result = VALUES_1(Data_server_pretty_name_alist);
	}
	POP_AREA(0);
	return result;
    }
}

/* COPY-DATA-SERVER */
Object copy_data_server(data_server)
    Object data_server;
{
    x_note_fn_call(147,70);
    return make_data_server_1(ISVREF(data_server,(SI_Long)1L),
	    ISVREF(data_server,(SI_Long)2L),ISVREF(data_server,
	    (SI_Long)3L),ISVREF(data_server,(SI_Long)4L),
	    ISVREF(data_server,(SI_Long)5L),ISVREF(data_server,
	    (SI_Long)6L),ISVREF(data_server,(SI_Long)7L),
	    ISVREF(data_server,(SI_Long)8L),ISVREF(data_server,
	    (SI_Long)9L),ISVREF(data_server,(SI_Long)10L),
	    ISVREF(data_server,(SI_Long)11L),ISVREF(data_server,
	    (SI_Long)12L),ISVREF(data_server,(SI_Long)14L),
	    ISVREF(data_server,(SI_Long)15L),ISVREF(data_server,(SI_Long)16L));
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_1;   /* "The data server specified for ~NF is " */

static Object string_constant_2;   /* ", which is not a defined data server or data server alias." */

/* WARN-OF-UNDEFINED-DATA-SERVER */
Object warn_of_undefined_data_server(variable,data_server_map)
    Object variable, data_server_map;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(147,71);
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
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
		      tformat(2,string_constant_1,variable);
		      write_data_server_map_from_slot(data_server_map,Nil);
		      twrite(string_constant_2);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user_1(temp);
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* NOTIFY-DATA-SERVER-OF-START-OR-RESET */
Object notify_data_server_of_start_or_reset(start_p)
    Object start_p;
{
    Object server, ab_loop_list_, function_qm;

    x_note_fn_call(147,72);
    server = Nil;
    ab_loop_list_ = List_of_all_data_servers;
    function_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    server = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    function_qm = start_p ? ISVREF(server,(SI_Long)15L) : ISVREF(server,
	    (SI_Long)16L);
    if (function_qm)
	FUNCALL_0(SYMBOL_FUNCTION(function_qm));
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qdata_server_map;    /* data-server-map */

/* PUT-DATA-SERVER-MAP */
Object put_data_server_map(variable,new_data_server_map,gensymed_symbol)
    Object variable, new_data_server_map, gensymed_symbol;
{
    Object source_or_map, server_qm, old_data_server_qm, temp, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store, cons_1, next_cons, collection_interval_qm;
    Object new_data_server_qm;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(147,73);
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & (SI_Long)1L)) {
	source_or_map = ISVREF(variable,(SI_Long)31L);
	server_qm = ATOM(source_or_map) ? 
		lookup_kb_specific_property_value(source_or_map,
		Data_server_or_alias_qm_kbprop) : Nil;
	old_data_server_qm = server_qm ? server_qm : 
		warn_of_undefined_data_server(variable,source_or_map);
	if (SIMPLE_VECTOR_P(old_data_server_qm) && 
		EQ(ISVREF(old_data_server_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct)) {
	    temp = SYMBOL_FUNCTION(ISVREF(old_data_server_qm,(SI_Long)4L));
	    FUNCALL_1(temp,variable);
	}
	else if (EQ(old_data_server_qm,Qcomputation))
	    stop_collecting_data_for_inference_engine(variable);
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(variable,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(variable,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = variable;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp_1 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = variable;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(variable,Qdata_server_map);
	  result_1 = SVREF(variable,FIX((SI_Long)31L)) = new_data_server_map;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = variable;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_2);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop;
	      temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(variable,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_2 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop:
	      temp_2 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2)
	      update_all_representations_of_slot(variable,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(variable);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	collection_interval_qm = ISVREF(variable,(SI_Long)32L);
	if (collection_interval_qm) {
	    source_or_map = ISVREF(variable,(SI_Long)31L);
	    server_qm = ATOM(source_or_map) ? 
		    lookup_kb_specific_property_value(source_or_map,
		    Data_server_or_alias_qm_kbprop) : Nil;
	    new_data_server_qm = server_qm ? server_qm : 
		    warn_of_undefined_data_server(variable,source_or_map);
	    if (SIMPLE_VECTOR_P(new_data_server_qm) && 
		    EQ(ISVREF(new_data_server_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_data_server_g2_struct)) {
		temp = SYMBOL_FUNCTION(ISVREF(new_data_server_qm,(SI_Long)3L));
		FUNCALL_2(temp,variable,collection_interval_qm);
	    }
	    else if (EQ(new_data_server_qm,Qcomputation))
		begin_collecting_data_for_inference_engine(variable,
			collection_interval_qm);
	}
	return VALUES_1(new_data_server_map);
    }
    else {
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(variable,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_1 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_1 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_1 = nconc2(stack_change_list_2(variable,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_1 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_1 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_1) = variable;
	    M_CDR(gensymed_symbol_1) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	temp_1 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_1;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = variable;
	      gensymed_symbol_2 = Nil;
	      gensymed_symbol_3 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	      svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
	  }
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(variable,Qdata_server_map);
	  result_1 = SVREF(variable,FIX((SI_Long)31L)) = new_data_server_map;
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value_1 = IFIX(ISVREF(variable,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value_1);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(variable,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_1 = variable;
	      gensymed_symbol_2 = T;
	      gensymed_symbol_3 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2,gensymed_symbol_3);
	  }
	  temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_2);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_1;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop_1;
	      temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_2);
	      else {
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_2 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_2 ? (EQ(variable,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_2 = TRUEP(ab_loop_it_);
		  goto end_2;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      temp_2 = TRUEP(Qnil);
	    end_2:;
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if ( !temp_2)
	      update_all_representations_of_slot(variable,slot_description,
		      Nil,Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(variable);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_2 = ATOM(temp);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	return VALUES_1(result_1);
    }
}

/* DATA-SERVER-REQUESTS-ACCEPT-DATA-CALLS */
Object data_server_requests_accept_data_calls(data_server)
    Object data_server;
{
    Object function_qm, temp;

    x_note_fn_call(147,74);
    function_qm = ISVREF(data_server,(SI_Long)14L);
    if ( !TRUEP(function_qm))
	temp = Nil;
    else if (EQ(function_qm,T))
	temp = T;
    else
	temp = FUNCALL_0(SYMBOL_FUNCTION(function_qm));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Data_server_parameters, Qdata_server_parameters);

static Object Qpriority_of_data_service;  /* priority-of-data-service */

/* PUT-PRIORITY-OF-CONTINUED-DATA-SERVICE-WHERE-SLOT-IS-ABSENT */
Object put_priority_of_continued_data_service_where_slot_is_absent(data_server_parameters_table,
	    new_priority)
    Object data_server_parameters_table, new_priority;
{
    x_note_fn_call(147,75);
    change_slot_value(3,data_server_parameters_table,
	    Qpriority_of_data_service,new_priority);
    return VALUES_1(Nil);
}

/* G2-PRIORITY-OF-DATA-SERVICE-FUNCTION */
Object g2_priority_of_data_service_function()
{
    Object temp;

    x_note_fn_call(147,76);
    temp = ISVREF(Data_server_parameters,(SI_Long)22L);
    return VALUES_1(temp);
}

static Object Qg2_meter_data_service_on_qm;  /* g2-meter-data-service-on? */

static Object Qdata_server_aliases;  /* data-server-aliases */

/* INSTALL-SYSTEM-TABLE-FOR-DATA-SERVER-PARAMETERS */
Object install_system_table_for_data_server_parameters(data_server_parameters)
    Object data_server_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(147,77);
    PUSH_SPECIAL_WITH_SYMBOL(Data_server_parameters,Qdata_server_parameters,data_server_parameters,
	    0);
      initialize_or_shut_down_g2_meter_data_server(get_lookup_slot_value_given_default(Data_server_parameters,
	      Qg2_meter_data_service_on_qm,Nil));
      result = absorb_data_server_aliases(Nil,
	      get_lookup_slot_value_given_default(Data_server_parameters,
	      Qdata_server_aliases,Nil));
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-DATA-SERVER-PARAMETERS */
Object deinstall_system_table_for_data_server_parameters(data_server_parameters)
    Object data_server_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(147,78);
    PUSH_SPECIAL_WITH_SYMBOL(Data_server_parameters,Qdata_server_parameters,data_server_parameters,
	    0);
      result = absorb_data_server_aliases(get_lookup_slot_value_given_default(Data_server_parameters,
	      Qdata_server_aliases,Nil),Nil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_meter_data_server;  /* g2-meter-data-server */

/* INITIALIZE-OR-SHUT-DOWN-G2-METER-DATA-SERVER */
Object initialize_or_shut_down_g2_meter_data_server(install_case_qm)
    Object install_case_qm;
{
    Object data_server_qm, function_to_shut_down_data_server_qm;

    x_note_fn_call(147,79);
    data_server_qm = 
	    lookup_kb_specific_property_value(Qg2_meter_data_server,
	    Data_server_kbprop);
    if (data_server_qm) {
	if (install_case_qm) {
	    if (System_is_running || System_has_paused)
		return FUNCALL_0(SYMBOL_FUNCTION(ISVREF(lookup_kb_specific_property_value(Qg2_meter_data_server,
			Data_server_kbprop),(SI_Long)7L)));
	    else
		return VALUES_1(Nil);
	}
	else {
	    function_to_shut_down_data_server_qm = 
		    ISVREF(lookup_kb_specific_property_value(Qg2_meter_data_server,
		    Data_server_kbprop),(SI_Long)9L);
	    if (function_to_shut_down_data_server_qm)
		return FUNCALL_0(SYMBOL_FUNCTION(function_to_shut_down_data_server_qm));
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* PUT-G2-METER-DATA-SERVICE-ON? */
Object put_g2_meter_data_service_on_qm(data_server_parameters_instance,
	    new_value,gensymed_symbol)
    Object data_server_parameters_instance, new_value, gensymed_symbol;
{
    x_note_fn_call(147,80);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(data_server_parameters_instance,
		Qg2_meter_data_service_on_qm);
    set_lookup_slot_value_1(data_server_parameters_instance,
	    Qg2_meter_data_service_on_qm,new_value);
    Record_fixnum_time_units_of_sleep_this_clock_tick_qm = new_value;
    g2ext_set_record_waits(new_value ? (SI_Long)1L : (SI_Long)0L);
    if (system_table_installed_p(data_server_parameters_instance))
	initialize_or_shut_down_g2_meter_data_server(new_value);
    return VALUES_1(new_value);
}

static Object Qnone;               /* none */

static Object string_constant_3;   /* "the name ~(~a~) may not be given two alias mappings" */

/* COMPILE-DATA-SERVER-ALIASES-FOR-SLOT */
Object compile_data_server_aliases_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object alias_cons, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(147,81);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else if (EQ(CAR(parse_result),Qand)) {
	alias_cons = CDR(parse_result);
      next_loop:
	if ( !TRUEP(alias_cons))
	    goto end_loop;
	if (assq_function(CAAR(alias_cons),CDR(alias_cons))) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_3,CAAR(alias_cons));
	    return VALUES_2(temp,temp_1);
	}
	alias_cons = M_CDR(alias_cons);
	goto next_loop;
      end_loop:
	return VALUES_1(parse_result);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(parse_result);
}

static Object string_constant_4;   /* "none" */

static Object string_constant_5;   /* " implies service through " */

static Object string_constant_6;   /* ", " */

/* WRITE-DATA-SERVER-ALIASES-FROM-SLOT */
Object write_data_server_aliases_from_slot(data_server_aliases,gensymed_symbol)
    Object data_server_aliases, gensymed_symbol;
{
    Object alias_cons, alias;

    x_note_fn_call(147,82);
    if ( !TRUEP(data_server_aliases))
	return twrite(string_constant_4);
    else if (EQ(CAR(data_server_aliases),Qand)) {
	alias_cons = CDR(data_server_aliases);
	alias = Nil;
      next_loop:
	if ( !TRUEP(alias_cons))
	    goto end_loop;
	alias = CAR(alias_cons);
	write_data_server_map_from_slot(FIRST(alias),Nil);
	twrite(string_constant_5);
	write_data_server_map_from_slot(SECOND(alias),Nil);
	if (CDR(alias_cons))
	    twrite(string_constant_6);
	alias_cons = M_CDR(alias_cons);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	write_data_server_map_from_slot(FIRST(data_server_aliases),Nil);
	twrite(string_constant_5);
	return write_data_server_map_from_slot(SECOND(data_server_aliases),
		Nil);
    }
}

/* PUT-DATA-SERVER-ALIASES */
Object put_data_server_aliases(data_server_parameters_instance,new_aliases,
	    initializing_qm)
    Object data_server_parameters_instance, new_aliases, initializing_qm;
{
    x_note_fn_call(147,83);
    if (system_table_installed_p(data_server_parameters_instance))
	absorb_data_server_aliases( !TRUEP(initializing_qm) ? 
		get_lookup_slot_value_given_default(data_server_parameters_instance,
		Qdata_server_aliases,Nil) : Nil,new_aliases);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(data_server_parameters_instance,
		Qdata_server_aliases);
    return set_lookup_slot_value_1(data_server_parameters_instance,
	    Qdata_server_aliases,new_aliases);
}

static Object string_constant_7;   /* "Within the data server aliases just defined, note that" */

static Object string_constant_8;   /* " " */

static Object string_constant_9;   /* "," */

static Object string_constant_10;  /* " and" */

static Object string_constant_11;  /* "are not defined data servers." */

static Object string_constant_12;  /* "Within the data server aliases just defined, note that " */

static Object string_constant_13;  /* " is not a defined data server." */

/* ABSORB-DATA-SERVER-ALIASES */
Object absorb_data_server_aliases(old_aliases,new_aliases)
    Object old_aliases, new_aliases;
{
    Object old_alias_list, new_alias_list, undefined_data_server_names;
    Object data_server_structure, notification_text_string, aliases_to_remove;
    Object aliases_to_add, affected_variables, old_alias_spec, ab_loop_list_;
    Object new_spec_qm, scope_conses, ab_loopvar_, ab_loopvar__1, variable;
    Object server_map, temp_1, source_or_map, server_qm, old_alias;
    Object ab_loop_desetq_, alias, affected_entry, old_data_server_qm;
    Object new_data_server_qm, temp_2, svref_arg_2, interval_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object name_cons, name, last_1, next_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(147,84);
    if ( !TRUEP(old_aliases))
	old_alias_list = Nil;
    else if (EQ(CAR(old_aliases),Qand))
	old_alias_list = copy_list_using_eval_conses_1(CDR(old_aliases));
    else
	old_alias_list = eval_cons_1(old_aliases,Nil);
    if ( !TRUEP(new_aliases))
	new_alias_list = Nil;
    else if (EQ(CAR(new_aliases),Qand))
	new_alias_list = copy_list_using_eval_conses_1(CDR(new_aliases));
    else
	new_alias_list = eval_cons_1(new_aliases,Nil);
    undefined_data_server_names = Nil;
    data_server_structure = Nil;
    notification_text_string = Nil;
    aliases_to_remove = Nil;
    aliases_to_add = copy_list_using_eval_conses_1(new_alias_list);
    affected_variables = Nil;
    old_alias_spec = Nil;
    ab_loop_list_ = old_alias_list;
    new_spec_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    old_alias_spec = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_spec_qm = assq_function(CAR(old_alias_spec),aliases_to_add);
    if ( !TRUEP(new_spec_qm))
	aliases_to_remove = eval_cons_1(old_alias_spec,aliases_to_remove);
    else if (EQ(SECOND(old_alias_spec),SECOND(new_spec_qm)))
	aliases_to_add = delete_eval_element_1(new_spec_qm,aliases_to_add);
    goto next_loop;
  end_loop:;
    if (System_is_running || System_has_paused) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	variable = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qvariable);
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
	  variable = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & 
		  (SI_Long)1L)) {
	      server_map = ISVREF(variable,(SI_Long)31L);
	      if (assq_function(server_map,aliases_to_add) || 
		      assq_function(server_map,aliases_to_remove)) {
		  temp_1 = variable;
		  source_or_map = ISVREF(variable,(SI_Long)31L);
		  server_qm = ATOM(source_or_map) ? 
			  lookup_kb_specific_property_value(source_or_map,
			  Data_server_or_alias_qm_kbprop) : Nil;
		  temp_1 = eval_cons_1(temp_1,server_qm ? server_qm : 
			  warn_of_undefined_data_server(variable,
			  source_or_map));
		  affected_variables = eval_cons_1(temp_1,affected_variables);
	      }
	  }
	  goto next_loop_1;
	end_loop_2:;
	POP_SPECIAL();
    }
    old_alias = Nil;
    ab_loop_list_ = aliases_to_remove;
    ab_loop_desetq_ = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    old_alias = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_kb_specific_property_value(old_alias,
	    lookup_kb_specific_property_value(old_alias,
	    Data_server_kbprop),Data_server_or_alias_qm_kbprop);
    goto next_loop_3;
  end_loop_3:;
    alias = Nil;
    ab_loop_list_ = aliases_to_add;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    alias = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    data_server_structure = 
	    lookup_kb_specific_property_value(SECOND(alias),
	    Data_server_kbprop);
    if ( !TRUEP(data_server_structure))
	undefined_data_server_names = gensym_cons_1(SECOND(alias),
		undefined_data_server_names);
    mutate_kb_specific_property_value(FIRST(alias),data_server_structure,
	    Data_server_or_alias_qm_kbprop);
    goto next_loop_4;
  end_loop_4:;
    affected_entry = Nil;
    ab_loop_list_ = affected_variables;
    variable = Nil;
    old_data_server_qm = Nil;
    new_data_server_qm = Nil;
  next_loop_5:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_5;
    affected_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    variable = CAR(affected_entry);
    old_data_server_qm = CDR(affected_entry);
    source_or_map = ISVREF(variable,(SI_Long)31L);
    server_qm = ATOM(source_or_map) ? 
	    lookup_kb_specific_property_value(source_or_map,
	    Data_server_or_alias_qm_kbprop) : Nil;
    new_data_server_qm = server_qm ? server_qm : 
	    warn_of_undefined_data_server(variable,source_or_map);
    inline_note_reclaim_cons(affected_entry,Qeval);
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp_2 = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp_2) = affected_entry;
	temp_2 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = affected_entry;
    }
    else {
	temp_2 = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = affected_entry;
	temp_2 = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp_2,svref_arg_2) = affected_entry;
    }
    M_CDR(affected_entry) = Nil;
    if ( !EQ(old_data_server_qm,new_data_server_qm)) {
	if (old_data_server_qm) {
	    if (EQ(old_data_server_qm,Qcomputation))
		withdraw_backward_chaining(variable);
	    else {
		temp_1 = SYMBOL_FUNCTION(ISVREF(old_data_server_qm,
			(SI_Long)4L));
		FUNCALL_1(temp_1,variable);
	    }
	}
	interval_qm = ISVREF(variable,(SI_Long)32L);
	if (interval_qm) {
	    if (SIMPLE_VECTOR_P(new_data_server_qm) && 
		    EQ(ISVREF(new_data_server_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_data_server_g2_struct)) {
		temp_1 = SYMBOL_FUNCTION(ISVREF(new_data_server_qm,
			(SI_Long)3L));
		FUNCALL_2(temp_1,variable,interval_qm);
	    }
	    else if (EQ(new_data_server_qm,Qcomputation))
		begin_collecting_data_for_inference_engine(variable,
			interval_qm);
	}
	else if (ISVREF(variable,(SI_Long)36L) && 
		SIMPLE_VECTOR_P(new_data_server_qm) && 
		EQ(ISVREF(new_data_server_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct)) {
	    temp_1 = SYMBOL_FUNCTION(ISVREF(new_data_server_qm,(SI_Long)2L));
	    FUNCALL_1(temp_1,variable);
	}
    }
    goto next_loop_5;
  end_loop_5:;
    if (undefined_data_server_names && CDR(undefined_data_server_names)) {
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
		  twrite(string_constant_7);
		  name_cons = undefined_data_server_names;
		  name = Nil;
		next_loop_6:
		  if ( !TRUEP(name_cons))
		      goto end_loop_6;
		  name = CAR(name_cons);
		  twrite(string_constant_8);
		  write_data_server_map_from_slot(name,Nil);
		  if (CDR(name_cons)) {
		      if (IFIX(length(undefined_data_server_names)) != 
			      (SI_Long)2L)
			  twrite(string_constant_9);
		      if ( !TRUEP(CDDR(name_cons)))
			  twrite(string_constant_10);
		      else
			  twrite(string_constant_8);
		  }
		  name_cons = M_CDR(name_cons);
		  goto next_loop_6;
		end_loop_6:;
		  twrite(string_constant_11);
		  notification_text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_engineer(1,notification_text_string);
	reclaim_text_string(notification_text_string);
	reclaim_gensym_list_1(undefined_data_server_names);
    }
    else if (undefined_data_server_names) {
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
		  twrite(string_constant_12);
		  write_data_server_map_from_slot(CAR(undefined_data_server_names),
			  Nil);
		  twrite(string_constant_13);
		  notification_text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	notify_engineer(1,notification_text_string);
	reclaim_text_string(notification_text_string);
	reclaim_gensym_cons_1(undefined_data_server_names);
    }
    if (old_alias_list) {
	last_1 = old_alias_list;
	next_qm = Nil;
      next_loop_7:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_7;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_7;
      end_loop_7:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = old_alias_list;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = old_alias_list;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (new_alias_list) {
	last_1 = new_alias_list;
	next_qm = Nil;
      next_loop_8:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_8;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_8;
      end_loop_8:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = new_alias_list;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = new_alias_list;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (aliases_to_add) {
	last_1 = aliases_to_add;
	next_qm = Nil;
      next_loop_9:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_9;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_9;
      end_loop_9:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = aliases_to_add;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = aliases_to_add;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (aliases_to_remove) {
	last_1 = aliases_to_remove;
	next_qm = Nil;
      next_loop_10:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_10;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_10;
      end_loop_10:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = aliases_to_remove;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = aliases_to_remove;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    if (affected_variables) {
	last_1 = affected_variables;
	next_qm = Nil;
      next_loop_11:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_11;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_11;
      end_loop_11:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = affected_variables;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = affected_variables;
	    temp_2 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-WAKE-UPS-POSTPONING-CLEAN-UP */
Object remove_wake_ups_postponing_clean_up(requestor,wake_ups)
    Object requestor, wake_ups;
{
    Object variable, ab_loop_list_, svref_new_value;

    x_note_fn_call(147,85);
    variable = Nil;
    ab_loop_list_ = wake_ups;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    svref_new_value = delete_eval_element_1(requestor,ISVREF(variable,
	    (SI_Long)36L));
    ISVREF(variable,(SI_Long)36L) = svref_new_value;
    if ( !TRUEP(ISVREF(variable,(SI_Long)38L)))
	ISVREF(variable,(SI_Long)38L) = requestor;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PERFORM-POSTPONED-CLEAN-UPS */
Object perform_postponed_clean_ups(requestor,wake_ups)
    Object requestor, wake_ups;
{
    Object variable_cons, variable, cdr_of_cons, eval_cons, temp, svref_arg_2;

    x_note_fn_call(147,86);
    if (wake_ups) {
	variable_cons = wake_ups;
	variable = Nil;
	cdr_of_cons = Nil;
      next_loop:
	variable = M_CAR(variable_cons);
	cdr_of_cons = M_CDR(variable_cons);
	if (EQ(ISVREF(variable,(SI_Long)38L),requestor)) {
	    ISVREF(variable,(SI_Long)38L) = Nil;
	    if ( !TRUEP(ISVREF(variable,(SI_Long)36L)))
		withdraw_backward_chaining(variable);
	}
	if ( !TRUEP(cdr_of_cons))
	    goto end_loop;
	variable_cons = cdr_of_cons;
	goto next_loop;
      end_loop:
	if (wake_ups &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = wake_ups;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,variable_cons))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_cons;
	}
	M_CDR(variable_cons) = Nil;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qvalue_request_pending;  /* value-request-pending */

/* SET-PENDING-WAKE-UPS */
Object set_pending_wake_ups(requestor,wake_ups)
    Object requestor, wake_ups;
{
    Object variable, ab_loop_list_, list_spot, gensymed_symbol;

    x_note_fn_call(147,87);
    variable = Nil;
    ab_loop_list_ = wake_ups;
    list_spot = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(variable,(SI_Long)36L);
  next_loop_1:
    if ( !TRUEP(gensymed_symbol))
	goto end_loop_1;
    if (EQ(M_CAR(gensymed_symbol),Qvalue_request_pending)) {
	list_spot = gensymed_symbol;
	goto end_1;
    }
    gensymed_symbol = M_CDR(gensymed_symbol);
    goto next_loop_1;
  end_loop_1:
    list_spot = Qnil;
  end_1:;
    if (list_spot)
	M_CAR(list_spot) = requestor;
    else
	write_wake_up_list_lossage_warning();
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CLEAR-PENDING-WAKE-UPS */
Object clear_pending_wake_ups()
{
    Object wake_ups, variable_cons, variable, cdr_of_cons;
    Object pruned_interest_list, eval_cons, temp, svref_arg_2;

    x_note_fn_call(147,88);
    wake_ups = Variables_that_did_not_have_values;
    if (wake_ups) {
	Variables_that_did_not_have_values = Nil;
	variable_cons = wake_ups;
	variable = Nil;
	cdr_of_cons = Nil;
      next_loop:
	variable = M_CAR(variable_cons);
	cdr_of_cons = M_CDR(variable_cons);
	pruned_interest_list = 
		delete_eval_element_1(Qvalue_request_pending,
		ISVREF(variable,(SI_Long)36L));
	ISVREF(variable,(SI_Long)36L) = pruned_interest_list;
	if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable,
		(SI_Long)38L)))
	    withdraw_backward_chaining(variable);
	if ( !TRUEP(cdr_of_cons))
	    goto end_loop;
	variable_cons = cdr_of_cons;
	goto next_loop;
      end_loop:
	if (wake_ups &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = wake_ups;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,variable_cons))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = variable_cons;
	}
	M_CDR(variable_cons) = Nil;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* WRITE-WAKE-UP-LIST-LOSSAGE-WARNING */
Object write_wake_up_list_lossage_warning()
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(147,89);
    SAVE_STACK();
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      twrite_beginning_of_wide_string(array_constant,
			      FIX((SI_Long)59L));
		      twrite_beginning_of_wide_string(array_constant_1,
			      FIX((SI_Long)58L));
		      twrite_beginning_of_wide_string(array_constant_2,
			      FIX((SI_Long)51L));
		      twrite_beginning_of_wide_string(array_constant_3,
			      FIX((SI_Long)42L));
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	    result = RESTORE_VALUES();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Explanation_variables, Qexplanation_variables);

/* RECLAIM-EXPLANATION-VARIABLES */
Object reclaim_explanation_variables()
{
    Object var, ab_loop_list_;

    x_note_fn_call(147,90);
    var = Nil;
    ab_loop_list_ = Explanation_variables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(CDR(var));
    reclaim_eval_tree_1(CAR(var));
    goto next_loop;
  end_loop:;
    reclaim_eval_list_1(Explanation_variables);
    Explanation_variables = Nil;
    return VALUES_1(Nil);
}

/* COPY-EXPLANATION-VARIABLES */
Object copy_explanation_variables(vars)
    Object vars;
{
    Object var, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(147,91);
    var = Nil;
    ab_loop_list_ = vars;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = copy_tree_using_eval_conses_1(CAR(var));
    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,
	    copy_frame_serial_number(CDR(var))),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object The_type_description_of_formula_invocation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_formula_invocations, Qchain_of_available_formula_invocations);

DEFINE_VARIABLE_WITH_SYMBOL(Formula_invocation_count, Qformula_invocation_count);

Object Chain_of_available_formula_invocations_vector = UNBOUND;

/* FORMULA-INVOCATION-STRUCTURE-MEMORY-USAGE */
Object formula_invocation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(147,92);
    temp = Formula_invocation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FORMULA-INVOCATION-COUNT */
Object outstanding_formula_invocation_count()
{
    Object def_structure_formula_invocation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(147,93);
    gensymed_symbol = IFIX(Formula_invocation_count);
    def_structure_formula_invocation_variable = 
	    Chain_of_available_formula_invocations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_formula_invocation_variable))
	goto end_loop;
    def_structure_formula_invocation_variable = 
	    ISVREF(def_structure_formula_invocation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FORMULA-INVOCATION-1 */
Object reclaim_formula_invocation_1(formula_invocation)
    Object formula_invocation;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(147,94);
    inline_note_reclaim_cons(formula_invocation,Nil);
    structure_being_reclaimed = formula_invocation;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(formula_invocation,(SI_Long)7L);
      if (CAS_SVREF(formula_invocation,(SI_Long)7L,gensymed_symbol,Nil)) {
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
      goto next_loop;
    end_loop:
    end_1:;
      SVREF(formula_invocation,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(formula_invocation,(SI_Long)10L));
      SVREF(formula_invocation,FIX((SI_Long)10L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_formula_invocations_vector,
	    IFIX(Current_thread_index));
    SVREF(formula_invocation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_formula_invocations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = formula_invocation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FORMULA-INVOCATION */
Object reclaim_structure_for_formula_invocation(formula_invocation)
    Object formula_invocation;
{
    x_note_fn_call(147,95);
    return reclaim_formula_invocation_1(formula_invocation);
}

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

/* MAKE-PERMANENT-FORMULA-INVOCATION-STRUCTURE-INTERNAL */
Object make_permanent_formula_invocation_structure_internal()
{
    Object def_structure_formula_invocation_variable;
    Object defstruct_g2_formula_invocation_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(147,96);
    def_structure_formula_invocation_variable = Nil;
    atomic_incff_symval(Qformula_invocation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_formula_invocation_variable = Nil;
	gensymed_symbol_1 = (SI_Long)13L;
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
	defstruct_g2_formula_invocation_variable = the_array;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_formula_invocation_g2_struct;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_formula_invocation_variable,FIX((SI_Long)7L)) = Nil;
	def_structure_formula_invocation_variable = 
		defstruct_g2_formula_invocation_variable;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)5L)) 
		= Nil;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)6L)) 
		= Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_formula_invocations_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)0L)) 
		= temp;
	temp = Chain_of_available_formula_invocations_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_formula_invocation_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_formula_invocation_variable);
}

/* MAKE-FORMULA-INVOCATION-1 */
Object make_formula_invocation_1(formula_invocation_variable,
	    formula_invocation_generic_formula_qm,
	    formula_invocation_frame_serial_number_qm)
    Object formula_invocation_variable, formula_invocation_generic_formula_qm;
    Object formula_invocation_frame_serial_number_qm;
{
    Object def_structure_formula_invocation_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(147,97);
    def_structure_formula_invocation_variable = 
	    ISVREF(Chain_of_available_formula_invocations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_formula_invocation_variable) {
	svref_arg_1 = Chain_of_available_formula_invocations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_formula_invocation_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_formula_invocation_g2_struct;
    }
    else
	def_structure_formula_invocation_variable = 
		make_permanent_formula_invocation_structure_internal();
    inline_note_allocate_cons(def_structure_formula_invocation_variable,Nil);
    SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)8L)) = 
	    formula_invocation_variable;
    SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)9L)) = 
	    formula_invocation_generic_formula_qm;
    SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)10L)) = 
	    formula_invocation_frame_serial_number_qm;
    SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_formula_invocation_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_formula_invocation_variable);
}

static Object string_constant_14;  /* "Requesting a value for ~NF from a data server." */

/* WRITE-MAJOR-TRACE-MESSAGE-FOR-SENSOR-DATA-SEEK */
Object write_major_trace_message_for_sensor_data_seek(variable)
    Object variable;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(147,98);
    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
	    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
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
		  tformat(2,string_constant_14,variable);
		  gensymed_symbol = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return write_major_trace_message_function(gensymed_symbol);
    }
    else
	return VALUES_1(Nil);
}

static Object Qnever;              /* never */

/* OBTAIN-NEWER-VALUE */
Object obtain_newer_value(variable,wake_up_qm)
    Object variable, wake_up_qm;
{
    Object source_or_map, server_qm, data_server, current_computation_frame;
    Object current_computation_instance, expiration_time_of_current_value;
    Object temp;
    Declare_special(2);

    x_note_fn_call(147,99);
    source_or_map = ISVREF(variable,(SI_Long)31L);
    server_qm = ATOM(source_or_map) ? 
	    lookup_kb_specific_property_value(source_or_map,
	    Data_server_or_alias_qm_kbprop) : Nil;
    data_server = server_qm ? server_qm : 
	    warn_of_undefined_data_server(variable,source_or_map);
    current_computation_frame = variable;
    current_computation_instance = variable;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      0);
	if ( !TRUEP(data_server)) {
	    expiration_time_of_current_value = ISVREF(variable,(SI_Long)26L);
	    if ( !(EQ(expiration_time_of_current_value,Qnever) || 
		    FIXNUM_GE(expiration_time_of_current_value,Gensym_time)))
		task_to_detect_failure(variable);
	}
	else if (EQ(data_server,Qcomputation))
	    compute_newer_value_of_variable(Current_computation_frame,
		    wake_up_qm);
	else {
	    if ((IFIX(Tracing_message_level) > (SI_Long)1L || 
		    IFIX(Breakpoint_level) > (SI_Long)1L) &&  
		    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
		    (SI_Long)22L))
		write_major_trace_message_for_sensor_data_seek(Current_computation_frame);
	    temp = SYMBOL_FUNCTION(ISVREF(data_server,(SI_Long)2L));
	    FUNCALL_1(temp,Current_computation_frame);
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* WAKE-UP-VARIABLE */
Object wake_up_variable(variable)
    Object variable;
{
    x_note_fn_call(147,100);
    return compute_newer_value_of_variable(variable,T);
}

static Object Qtext;               /* text */

static Object Qab_structure;       /* structure */

/* GET-CURRENT-VALUE */
Object get_current_value(variable_or_parameter,wake_up_qm)
    Object variable_or_parameter, wake_up_qm;
{
    Object old_stack_expiration, result_1, new_expiration, type, value;

    x_note_fn_call(147,101);
    old_stack_expiration = Stack_expiration;
    Stack_expiration = Qnever;
    result_1 = get_current_evaluation_value(variable_or_parameter,wake_up_qm);
    new_expiration = Stack_expiration;
    Stack_expiration = old_stack_expiration;
    if ( !TRUEP(new_expiration) ||  !TRUEP(result_1))
	return VALUES_3(Nil,Nil,Nil);
    else {
	type = evaluation_value_type(result_1);
	value = evaluation_value_value(result_1);
	if (EQ(type,Qtext));
	else if (EQ(type,Qlist) || EQ(type,Qab_structure))
	    reclaim_eval_cons_1(result_1);
	else
	    reclaim_evaluation_value(result_1);
	return VALUES_3(value,new_expiration,type);
    }
}

static Object string_constant_15;  /* "~NF is not active, its value was requested in ~NF." */

static Object Qtask_to_detect_failure;  /* task-to-detect-failure */

/* GET-CURRENT-EVALUATION-VALUE */
Object get_current_evaluation_value(variable_or_parameter,wake_up_qm)
    Object variable_or_parameter, wake_up_qm;
{
    Object result_1, expiration, sub_class_bit_vector, value;
    Object expiration_time_of_current_value, temp_1, current_qm, temp_2;
    Object timeout_qm, old, new_1, def_structure_schedule_task_variable;
    Object svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp, logical_qm, svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(147,102);
    result_1 = Nil;
    expiration = Qnever;
    if ( !((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)5L)) 
	    & (SI_Long)1L))) {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)1L),string_constant_15,
		    variable_or_parameter,Current_computation_frame);
	expiration = Nil;
	result_1 = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	    logical_qm = EQ(ISVREF(variable_or_parameter,(SI_Long)20L),
		    Qtruth_value);
	    value = ISVREF(variable_or_parameter,(SI_Long)23L);
	    if (logical_qm) {
		if (FIXNUM_EQ(value,Truth))
		    result_1 = Evaluation_true_value;
		else if (FIXNUM_EQ(value,Falsity))
		    result_1 = Evaluation_false_value;
		else
		    result_1 = eval_cons_1(value,Qtruth_value);
	    }
	    else
		result_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			(SI_Long)0L ? copy_wide_string(value) : 
			FIXNUMP(value) || SYMBOLP(value) ? value : 
			copy_evaluation_value_1(value);
	}
	else if ((IFIX(Current_computation_flags) & (SI_Long)256L) != 
		(SI_Long)0L || (SI_Long)0L != 
		(IFIX(ISVREF(variable_or_parameter,(SI_Long)4L)) & 
		(SI_Long)16L)) {
	    expiration_time_of_current_value = 
		    ISVREF(variable_or_parameter,(SI_Long)26L);
	    if (EQ(expiration_time_of_current_value,Qnever) || 
		    FIXNUM_GE(expiration_time_of_current_value,Gensym_time)) {
		expiration = ISVREF(variable_or_parameter,(SI_Long)26L);
		logical_qm = EQ(ISVREF(variable_or_parameter,(SI_Long)20L),
			Qtruth_value);
		value = ISVREF(variable_or_parameter,(SI_Long)23L);
		if (logical_qm) {
		    if (FIXNUM_EQ(value,Truth))
			result_1 = Evaluation_true_value;
		    else if (FIXNUM_EQ(value,Falsity))
			result_1 = Evaluation_false_value;
		    else
			result_1 = eval_cons_1(value,Qtruth_value);
		}
		else
		    result_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L ? copy_wide_string(value) : 
			    FIXNUMP(value) || SYMBOLP(value) ? value : 
			    copy_evaluation_value_1(value);
	    }
	    else {
		if ( !((IFIX(Current_computation_flags) & (SI_Long)256L) 
			!= (SI_Long)0L)) {
		    Variables_that_did_not_have_values = 
			    eval_cons_1(variable_or_parameter,
			    Variables_that_did_not_have_values);
		    temp_1 = eval_cons_1(Qvalue_request_pending,
			    ISVREF(variable_or_parameter,(SI_Long)36L));
		    ISVREF(variable_or_parameter,(SI_Long)36L) = temp_1;
		}
		expiration = Nil;
	    }
	}
	else {
	    expiration_time_of_current_value = 
		    ISVREF(variable_or_parameter,(SI_Long)26L);
	    current_qm = EQ(expiration_time_of_current_value,Qnever) ? T : Nil;
	    if (current_qm);
	    else
		current_qm = FIXNUM_GE(expiration_time_of_current_value,
			Gensym_time) ? T : Nil;
	    if (current_qm &&  !((IFIX(Current_computation_flags) & 
		    (SI_Long)4L) != (SI_Long)0L)) {
		expiration = ISVREF(variable_or_parameter,(SI_Long)26L);
		logical_qm = EQ(ISVREF(variable_or_parameter,(SI_Long)20L),
			Qtruth_value);
		value = ISVREF(variable_or_parameter,(SI_Long)23L);
		if (logical_qm) {
		    if (FIXNUM_EQ(value,Truth))
			result_1 = Evaluation_true_value;
		    else if (FIXNUM_EQ(value,Falsity))
			result_1 = Evaluation_false_value;
		    else
			result_1 = eval_cons_1(value,Qtruth_value);
		}
		else
		    result_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			    (SI_Long)0L ? copy_wide_string(value) : 
			    FIXNUMP(value) || SYMBOLP(value) ? value : 
			    copy_evaluation_value_1(value);
	    }
	    else {
		obtain_newer_value(variable_or_parameter,wake_up_qm);
		expiration_time_of_current_value = 
			ISVREF(variable_or_parameter,(SI_Long)26L);
		temp_2 = EQ(expiration_time_of_current_value,Qnever) ? T : Nil;
		if (temp_2);
		else
		    temp_2 = FIXNUM_GE(expiration_time_of_current_value,
			    Gensym_time) ? T : Nil;
		current_qm = temp_2;
		if (current_qm) {
		    expiration = ISVREF(variable_or_parameter,(SI_Long)26L);
		    logical_qm = EQ(ISVREF(variable_or_parameter,
			    (SI_Long)20L),Qtruth_value);
		    value = ISVREF(variable_or_parameter,(SI_Long)23L);
		    if (logical_qm) {
			if (FIXNUM_EQ(value,Truth))
			    result_1 = Evaluation_true_value;
			else if (FIXNUM_EQ(value,Falsity))
			    result_1 = Evaluation_false_value;
			else
			    result_1 = eval_cons_1(value,Qtruth_value);
		    }
		    else
			result_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) 
				!= (SI_Long)0L ? copy_wide_string(value) : 
				FIXNUMP(value) || SYMBOLP(value) ? value : 
				copy_evaluation_value_1(value);
		}
		else {
		    Variables_that_did_not_have_values = 
			    eval_cons_1(variable_or_parameter,
			    Variables_that_did_not_have_values);
		    temp_1 = eval_cons_1(Qvalue_request_pending,
			    ISVREF(variable_or_parameter,(SI_Long)36L));
		    ISVREF(variable_or_parameter,(SI_Long)36L) = temp_1;
		    if ((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,
			    (SI_Long)5L)) & (SI_Long)32L))
			task_to_detect_failure(variable_or_parameter);
		    else if ( !TRUEP(ISVREF(variable_or_parameter,
			    (SI_Long)29L))) {
			temp_1 = Gensym_time;
			ISVREF(variable_or_parameter,(SI_Long)29L) = temp_1;
			timeout_qm = ISVREF(Inference_engine_parameters,
				(SI_Long)23L);
			if (timeout_qm) {
			    old = Nil;
			    new_1 = Nil;
			  next_loop:
			    old = ISVREF(variable_or_parameter,(SI_Long)30L);
			    def_structure_schedule_task_variable = 
				    ISVREF(Chain_of_available_schedule_tasks_vector,
				    IFIX(Current_thread_index));
			    if (def_structure_schedule_task_variable) {
				temp_1 = 
					Chain_of_available_schedule_tasks_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = 
					ISVREF(def_structure_schedule_task_variable,
					(SI_Long)0L);
				SVREF(temp_1,svref_arg_2) = svref_new_value;
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
			    temp_1 = ISVREF(task,(SI_Long)1L);
			    aref_new_value = 
				    DFLOAT_ISAREF_1(Current_g2_time,
				    (SI_Long)0L) + (double)IFIX(timeout_qm);
			    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
			    temp_1 = ISVREF(task,(SI_Long)1L);
			    aref_new_value = -1.0;
			    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
			    svref_new_value_1 =  !TRUEP(Nil);
			    SVREF(task,FIX((SI_Long)3L)) = 
				    svref_new_value_1 ? T : Nil;
			    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)8L);
			    SVREF(task,FIX((SI_Long)5L)) = Nil;
			    SVREF(task,FIX((SI_Long)9L)) = Nil;
			    SVREF(task,FIX((SI_Long)10L)) = Nil;
			    SVREF(task,FIX((SI_Long)7L)) = 
				    Qtask_to_detect_failure;
			    temp_1 = SYMBOL_FUNCTION(Qtask_to_detect_failure);
			    SVREF(task,FIX((SI_Long)8L)) = temp_1;
			    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
			    SVREF(task,FIX((SI_Long)13L)) = 
				    variable_or_parameter;
			    new_1 = task;
			    if (CAS_SVREF(variable_or_parameter,
				    (SI_Long)30L,old,new_1)) {
				if (old) {
				    if (EQ(old,Current_schedule_task))
					Current_schedule_task = Nil;
				    if (ISVREF(old,(SI_Long)6L))
					cancel_and_reclaim_scheduled_queue_element_1(old);
				    inline_note_reclaim_cons(old,Nil);
				    structure_being_reclaimed = old;
				    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
					    0);
				      reclaim_schedule_task_args(ISVREF(old,
					      (SI_Long)9L));
				      SVREF(old,FIX((SI_Long)9L)) = Nil;
				    POP_SPECIAL();
				    temp_1 = 
					    ISVREF(Chain_of_available_schedule_tasks_vector,
					    IFIX(Current_thread_index));
				    SVREF(old,FIX((SI_Long)0L)) = temp_1;
				    temp_1 = 
					    Chain_of_available_schedule_tasks_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_1,svref_arg_2) = old;
				}
				future_task_schedule_2(new_1);
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
				temp_1 = 
					ISVREF(Chain_of_available_schedule_tasks_vector,
					IFIX(Current_thread_index));
				SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
				temp_1 = 
					Chain_of_available_schedule_tasks_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_1,svref_arg_2) = new_1;
			    }
			    goto next_loop;
			  end_loop:
			  end_1:;
			}
		    }
		    expiration = Nil;
		}
	    }
	}
    }
    if ((IFIX(Current_computation_flags) & (SI_Long)1L) != (SI_Long)0L && 
	    expiration && result_1)
	cache_explanation_variables(variable_or_parameter);
    if (EQ(Stack_expiration,Qnever))
	Stack_expiration = expiration;
    else if (EQ(expiration,Qnever));
    else if ( !TRUEP(Stack_expiration) ||  !TRUEP(expiration))
	Stack_expiration = Nil;
    else
	Stack_expiration = FIXNUM_MIN(Stack_expiration,expiration);
    return VALUES_1(result_1);
}

static Object Qtask_to_probe_failed_variable;  /* task-to-probe-failed-variable */

/* TASK-TO-DETECT-FAILURE */
Object task_to_detect_failure(variable)
    Object variable;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object failed_sensor_probing_interval_qm, schedule_task_qm, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value_1, task;
    Object ctask, p, v, q;
    SI_Long svref_new_value;
    char temp_1, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(147,103);
    if ( !((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & 
		(SI_Long)32L))) {
	svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) | (SI_Long)32L;
	ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
	invoke_rules_for_failure_chaining(variable);
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(variable,(SI_Long)30L);
	if (CAS_SVREF(variable,(SI_Long)30L,gensymed_symbol,Nil)) {
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
	goto next_loop;
      end_loop:
      end_1:;
    }
    failed_sensor_probing_interval_qm = ISVREF(Inference_engine_parameters,
	    (SI_Long)25L);
    if (failed_sensor_probing_interval_qm) {
	schedule_task_qm = ISVREF(variable,(SI_Long)30L);
	temp_1 =  !(schedule_task_qm && (ISVREF(schedule_task_qm,
		(SI_Long)6L) || EQ(schedule_task_qm,Current_schedule_task)));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	old = Nil;
	new_1 = Nil;
      next_loop_1:
	old = ISVREF(variable,(SI_Long)30L);
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value_1 = 
		    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value_1;
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
	aref_new_value = (double)IFIX(failed_sensor_probing_interval_qm);
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	ISVREF(task,(SI_Long)4L) = FIX((SI_Long)8L);
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qtask_to_probe_failed_variable;
	temp = SYMBOL_FUNCTION(Qtask_to_probe_failed_variable);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(task,FIX((SI_Long)13L)) = variable;
	new_1 = task;
	if (CAS_SVREF(variable,(SI_Long)30L,old,new_1)) {
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
	    goto end_2;
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
      end_2:;
    }
    return VALUES_1(Nil);
}

/* TASK-TO-PROBE-FAILED-VARIABLE */
Object task_to_probe_failed_variable(variable)
    Object variable;
{
    x_note_fn_call(147,104);
    attempt_new_variable_value_collection(variable,Nil,Nil);
    return VALUES_1(Nil);
}

/* FIND-GENERIC-FORMULA */
Object find_generic_formula(parent_entity_qm,slot_designator)
    Object parent_entity_qm, slot_designator;
{
    Object pretty_name, generic_formulas, class_1, class_description;
    Object ab_loop_list_, gensymed_symbol, defining_class;
    Object defining_description, description, formula, ab_loop_list__1;
    Object formula_qualifier_description, temp;
    char temp_1;

    x_note_fn_call(147,105);
    if (parent_entity_qm) {
	pretty_name = CONSP(slot_designator) ? M_CAR(slot_designator) : 
		slot_designator;
	generic_formulas = lookup_kb_specific_property_value(pretty_name,
		Formulas_for_this_role_kbprop);
	class_1 = Nil;
	class_description = ISVREF(parent_entity_qm,(SI_Long)1L);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	gensymed_symbol = slot_designator;
	defining_class = CONSP(gensymed_symbol) ? M_CDR(gensymed_symbol) : Nil;
	defining_description = defining_class ? 
		lookup_global_or_kb_specific_property_value(defining_class,
		Class_description_gkbprop) : ISVREF(parent_entity_qm,
		(SI_Long)1L);
	description = 
		get_slot_description_of_class_description_function(pretty_name,
		defining_description,Nil);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	formula = Nil;
	ab_loop_list__1 = generic_formulas;
	formula_qualifier_description = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	formula = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = ISVREF(formula,(SI_Long)16L);
	if (IFIX(length(CAR(temp))) > (SI_Long)2L) {
	    temp = ISVREF(formula,(SI_Long)16L);
	    temp = CAR(temp);
	    temp_1 = TRUEP(THIRD(temp));
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = ISVREF(formula,(SI_Long)16L);
	    if (IFIX(length(CAR(temp))) > (SI_Long)2L) {
		temp = ISVREF(formula,(SI_Long)16L);
		temp = CAR(temp);
		temp = THIRD(temp);
	    }
	    else
		temp = Nil;
	    formula_qualifier_description = 
		    lookup_global_or_kb_specific_property_value(temp,
		    Class_description_gkbprop);
	}
	else
	    formula_qualifier_description = ISVREF(parent_entity_qm,
		    (SI_Long)1L);
	temp = ISVREF(formula,(SI_Long)16L);
	temp = CAR(temp);
	if (EQ(class_1,SECOND(temp))) {
	    temp = ISVREF(formula,(SI_Long)8L);
	    temp_1 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != 
		    (IFIX(ISVREF(formula,(SI_Long)5L)) & (SI_Long)1L) ||  
		    !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		    (IFIX(ISVREF(formula,(SI_Long)4L)) & 
		    (SI_Long)16777216L) &&  !((SI_Long)0L != 
		    (IFIX(ISVREF(formula,(SI_Long)4L)) & (SI_Long)8192L)) :
		     TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ? EQ(description,
		get_slot_description_of_class_description_function(pretty_name,
		formula_qualifier_description,Nil)) : TRUEP(Nil))
	    return VALUES_1(formula);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-CURRENTLY-EVALUATING-FORMULA-AFTER-BOMBOUT */
Object clear_currently_evaluating_formula_after_bombout()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, variable;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,106);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    variable = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qvariable);
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
      variable = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) &  ~(SI_Long)128L;
      ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

/* MAXIMIZE-PRIORITY-OF-VARIABLE */
Object maximize_priority_of_variable(variable,priority)
    Object variable, priority;
{
    Object old_priority_qm, schedule_task_qm, change_priority_of_task_arg;
    Object priority_1, temp, structure_being_reclaimed, svref_arg_2, thing;
    Object ab_loop_list_, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(147,107);
    old_priority_qm = ISVREF(variable,(SI_Long)42L);
    if (old_priority_qm && FIXNUM_LT(priority,old_priority_qm)) {
	ISVREF(variable,(SI_Long)42L) = priority;
	schedule_task_qm = ISVREF(variable,(SI_Long)37L);
	if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
		EQ(schedule_task_qm,Current_schedule_task))) {
	    change_priority_of_task_arg = priority;
	    schedule_task_qm = ISVREF(variable,(SI_Long)37L);
	    priority_1 = change_priority_of_task_arg;
	    if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) 
		    || EQ(schedule_task_qm,Current_schedule_task))) {
		if ( !FIXNUM_EQ(ISVREF(schedule_task_qm,(SI_Long)4L),
			priority_1)) {
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    if (EQ(schedule_task_qm,Current_schedule_task))
			Current_schedule_task = Nil;
		    SVREF(schedule_task_qm,FIX((SI_Long)4L)) = priority_1;
		    future_task_schedule_2(schedule_task_qm);
		}
		temp = schedule_task_qm;
	    }
	    else {
		if (schedule_task_qm) {
		    if (EQ(schedule_task_qm,Current_schedule_task))
			Current_schedule_task = Nil;
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    inline_note_reclaim_cons(schedule_task_qm,Nil);
		    structure_being_reclaimed = schedule_task_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			    0);
		      reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			      (SI_Long)9L));
		      SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		    POP_SPECIAL();
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = schedule_task_qm;
		}
		temp = Nil;
	    }
	    ISVREF(variable,(SI_Long)37L) = temp;
	}
	if (ISVREF(variable,(SI_Long)34L))
	    schedule_computation_instance_execution(ISVREF(variable,
		    (SI_Long)34L),priority,variable);
	thing = Nil;
	ab_loop_list_ = ISVREF(variable,(SI_Long)35L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct))
	    maximize_priority_of_rule_instance(thing,priority);
	else {
	    if (SIMPLE_VECTOR_P(thing) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(thing,(SI_Long)1L);
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
			IFIX(ISVREF(Variable_class_description,(SI_Long)18L));
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
	    if (temp_1)
		maximize_priority_of_variable(thing,priority);
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Within_backward_chaining_task, Qwithin_backward_chaining_task);

/* CIRCULAR-VARIABLE-INTERESTS-1 */
Object circular_variable_interests_1(variable_to_search,original_variable)
    Object variable_to_search, original_variable;
{
    Object loop_result, interesting_thing, ab_loop_list_;
    SI_Long svref_new_value, gensymed_symbol;

    x_note_fn_call(147,108);
    loop_result = Nil;
    svref_new_value = IFIX(ISVREF(variable_to_search,(SI_Long)5L)) | 
	    (SI_Long)128L;
    ISVREF(variable_to_search,(SI_Long)5L) = FIX(svref_new_value);
    interesting_thing = Nil;
    ab_loop_list_ = ISVREF(variable_to_search,(SI_Long)35L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    interesting_thing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !(SIMPLE_VECTOR_P(interesting_thing) && 
	    EQ(ISVREF(interesting_thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))) {
	if (EQ(interesting_thing,original_variable))
	    loop_result = eval_cons_1(interesting_thing,Nil);
	else {
	    gensymed_symbol = IFIX(ISVREF(interesting_thing,(SI_Long)5L)) 
		    & (SI_Long)128L;
	    if ( !((SI_Long)0L != gensymed_symbol)) {
		loop_result = 
			circular_variable_interests_1(interesting_thing,
			original_variable);
		if (loop_result)
		    loop_result = eval_cons_1(interesting_thing,loop_result);
	    }
	}
    }
    if (loop_result)
	goto end_loop;
    goto next_loop;
  end_loop:;
    svref_new_value = IFIX(ISVREF(variable_to_search,(SI_Long)5L)) &  
	    ~(SI_Long)128L;
    ISVREF(variable_to_search,(SI_Long)5L) = FIX(svref_new_value);
    return VALUES_1(loop_result);
}

static Object string_constant_16;  /* "The formula computing the value of ~NF refers directly to ~
				    *            itself, and so cannot be evaluated."
				    */

static Object string_constant_17;  /* "Formulas computing the value of ~NF refer indirectly to ~
				    *              itself, and so cannot be evaluated.  The variables in the ~
				    *              loop are the following: "
				    */

static Object string_constant_18;  /* "and" */

/* WRITE-CIRCULAR-PATH-WARNING */
Object write_circular_path_warning(variable,path)
    Object variable, path;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    Declare_special(7);

    x_note_fn_call(147,109);
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      if ( !TRUEP(CDR(path)) && EQ(variable,CAR(path)))
			  tformat(2,string_constant_16,variable);
		      else {
			  tformat(2,string_constant_17,variable);
			  write_list_in_chicago_style(3,path,
				  string_constant_18,T);
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = (SI_Long)46L;
			      twrite_wide_character(CHARACTERP(FIX(thing)) 
				      ? CHAR_CODE(FIX(thing)) : FIX(thing));
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = (SI_Long)46L;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(FIX(thing)) ? 
				      CHAR_CODE(FIX(thing)) : FIX(thing));
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
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
    }
    return reclaim_eval_list_1(path);
}

static Object Qparent_attribute_name;  /* parent-attribute-name */

/* COMPUTE-NEWER-VALUE-OF-VARIABLE */
Object compute_newer_value_of_variable(variable,wake_up_qm)
    Object variable, wake_up_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object temp_1, specific_formula_qm, parent_entity_qm, slot_name;
    Object generic_formula_qm;
    Declare_special(1);

    x_note_fn_call(147,110);
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)32768L))
	return VALUES_1(Nil);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(variable,(SI_Long)37L);
    if (CAS_SVREF(variable,(SI_Long)37L,gensymed_symbol,Nil)) {
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
    temp_1 = ISVREF(variable,(SI_Long)28L);
    specific_formula_qm = CAR(temp_1);
    if (specific_formula_qm)
	return schedule_formula_for_backward_chaining(variable,Nil);
    else {
	parent_entity_qm = get_lookup_slot_value_given_default(variable,
		Qparent_frame,Nil);
	slot_name = get_lookup_slot_value_given_default(variable,
		Qparent_attribute_name,Nil);
	generic_formula_qm = find_generic_formula(parent_entity_qm,slot_name);
	if (generic_formula_qm)
	    return schedule_formula_for_backward_chaining(variable,
		    generic_formula_qm);
	else
	    return invoke_rules_for_backward_chaining(variable);
    }
}

/* IS-A-FORMULA-INVOCATION? */
Object is_a_formula_invocation_qm(a_potential_formula_invocation)
    Object a_potential_formula_invocation;
{
    Object temp;

    x_note_fn_call(147,111);
    temp = SIMPLE_VECTOR_P(a_potential_formula_invocation) ? 
	    (EQ(ISVREF(a_potential_formula_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct) ? T 
	    : Nil) : Qnil;
    return VALUES_1(temp);
}

/* ITEM-TO-PROFILE-OF-FORMULA-INVOCATION */
Object item_to_profile_of_formula_invocation(a_formula_invocation)
    Object a_formula_invocation;
{
    Object the_item;

    x_note_fn_call(147,112);
    the_item = Nil;
    the_item = ISVREF(a_formula_invocation,(SI_Long)9L);
    if ( !TRUEP(the_item))
	the_item = ISVREF(a_formula_invocation,(SI_Long)8L);
    return VALUES_1(the_item);
}

/* SCHEDULE-FORMULA-FOR-BACKWARD-CHAINING */
Object schedule_formula_for_backward_chaining(variable,generic_formula_qm)
    Object variable, generic_formula_qm;
{
    Object old_priority_qm, priority_to_propagate, priority_of_task;
    Object formula_invocation, item_to_profile;

    x_note_fn_call(147,113);
    if (ISVREF(variable,(SI_Long)34L))
	maximize_priority_of_variable(variable,Priority_of_current_task);
    else {
	old_priority_qm = ISVREF(variable,(SI_Long)42L);
	priority_to_propagate = FIXNUMP(Priority_of_current_task) && 
		IFIX(Priority_of_current_task) > (SI_Long)0L && 
		FIXNUM_LE(Priority_of_current_task,How_many_priorities_qm) 
		? Priority_of_current_task : FIX((SI_Long)1L);
	priority_of_task = old_priority_qm ? FIXNUM_MIN(old_priority_qm,
		priority_to_propagate) : priority_to_propagate;
	formula_invocation = make_formula_invocation_1(variable,
		generic_formula_qm,generic_formula_qm ? 
		copy_frame_serial_number(ISVREF(generic_formula_qm,
		(SI_Long)3L)) : Nil);
	remove_rule_instances_from_variable_interests(variable);
	ISVREF(variable,(SI_Long)34L) = formula_invocation;
	if (Profiling_enabled_qm) {
	    item_to_profile = 
		    item_to_profile_of_formula_invocation(formula_invocation);
	    increment_profiling_calls(item_to_profile);
	}
	schedule_computation_instance_execution(formula_invocation,
		priority_of_task,variable);
	if (old_priority_qm && FIXNUM_LT(priority_to_propagate,
		old_priority_qm))
	    maximize_priority_of_variable(variable,priority_to_propagate);
    }
    return VALUES_1(Nil);
}

/* REMOVE-RULE-INSTANCES-FROM-VARIABLE-INTERESTS */
Object remove_rule_instances_from_variable_interests(variable)
    Object variable;
{
    Object list_1, previous_cons, current_cons, interesting_thing, next_cons;

    x_note_fn_call(147,114);
    list_1 = ISVREF(variable,(SI_Long)35L);
    previous_cons = Nil;
    current_cons = list_1;
    interesting_thing = Nil;
    next_cons = Nil;
    previous_cons = Nil;
  next_loop:
    if ( !TRUEP(current_cons))
	goto end_loop;
    interesting_thing = CAR(current_cons);
    next_cons = CDR(current_cons);
    if ( !(SIMPLE_VECTOR_P(interesting_thing) && 
	    EQ(ISVREF(interesting_thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)))
	previous_cons = current_cons;
    else {
	remove_request_for_rule_instance_invocation(interesting_thing,
		variable);
	if (previous_cons)
	    M_CDR(previous_cons) = next_cons;
	else
	    list_1 = next_cons;
	reclaim_eval_cons_1(current_cons);
    }
    previous_cons = Nil;
    current_cons = next_cons;
    goto next_loop;
  end_loop:
    ISVREF(variable,(SI_Long)35L) = list_1;
    return VALUES_1(Qnil);
}

/* CANCEL-FORMULA-FOR-BACKWARD-CHAINING */
Object cancel_formula_for_backward_chaining(variable)
    Object variable;
{
    Object formula_invocation_qm, gensymed_symbol, structure_being_reclaimed;
    Object temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(147,115);
    formula_invocation_qm = ISVREF(variable,(SI_Long)34L);
    if (formula_invocation_qm) {
	ISVREF(variable,(SI_Long)34L) = Nil;
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(formula_invocation_qm,(SI_Long)7L);
	if (CAS_SVREF(formula_invocation_qm,(SI_Long)7L,gensymed_symbol,Nil)) {
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
	goto next_loop;
      end_loop:
      end_1:;
	if ( !EQ(formula_invocation_qm,Current_computation_instance))
	    reclaim_formula_invocation_1(formula_invocation_qm);
    }
    return VALUES_1(Nil);
}

static Object string_constant_19;  /* "~nw~%Exiting execution of this formula.  No value was computed for ~NF" */

/* HANDLE-FORMULA-INVOCATION-ERROR */
Object handle_formula_invocation_error(formula_invocation,error_1,
	    error_level,error_text_string,current_program_counter,
	    local_stack,top_of_stack,computation_frame,
	    computation_component_particulars,byte_code_body,
	    constant_vector,local_var_vector)
    Object formula_invocation, error_1, error_level, error_text_string;
    Object current_program_counter, local_stack, top_of_stack;
    Object computation_frame, computation_component_particulars;
    Object byte_code_body, constant_vector, local_var_vector;
{
    Object standard_message;

    x_note_fn_call(147,116);
    standard_message = generate_standard_error_message(error_1,
	    error_text_string,computation_frame,
	    computation_component_particulars,formula_invocation,
	    byte_code_body,constant_vector,current_program_counter,
	    local_stack,top_of_stack,local_var_vector);
    if (registered_and_active_default_error_handler_p() && 
	    invoke_user_defined_default_error_handler(error_1,
	    standard_message));
    else {
	Suppress_warning_message_header_qm = T;
	if (FIXNUM_LE(error_level,Warning_message_level))
	    give_warning_1(4,error_level,string_constant_19,
		    standard_message,ISVREF(formula_invocation,(SI_Long)8L));
	Suppress_warning_message_header_qm = Nil;
	reclaim_error_text(standard_message);
    }
    reclaim_error_text(error_text_string);
    exit_computation_context_for_variable_formula(formula_invocation);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(New_value_computed_in_formula_qm, Qnew_value_computed_in_formula_qm);

/* EXPRESSION-CELL-UPDATED-FOR-VARIABLE */
Object expression_cell_updated_for_variable(variable,g2_cell_array,index_1,
	    old_cache_qm,new_cache_qm)
    Object variable, g2_cell_array, index_1, old_cache_qm, new_cache_qm;
{
    x_note_fn_call(147,117);
    if (new_cache_qm) {
	New_value_computed_in_formula_qm = T;
	return put_current_value(5,variable,
		evaluation_value_value(new_cache_qm),
		evaluation_value_type(new_cache_qm),Stack_expiration,Nil);
    }
    else
	return VALUES_1(Nil);
}

/* EXPRESSION-CELL-UPDATED-FOR-GENERIC-FORMULA */
Object expression_cell_updated_for_generic_formula(generic_formula,
	    g2_cell_array,index_1,old_cache_qm,new_cache_qm)
    Object generic_formula, g2_cell_array, index_1, old_cache_qm, new_cache_qm;
{
    x_note_fn_call(147,118);
    if (new_cache_qm) {
	New_value_computed_in_formula_qm = T;
	return put_current_value(5,Current_computation_instance,
		evaluation_value_value(new_cache_qm),
		evaluation_value_type(new_cache_qm),Stack_expiration,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_4;    /* # */

static Object string_constant_20;  /* " of " */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-VARIABLE */
Object denote_cell_array_element_for_variable(variable,
	    component_particulars,include_block_denotation_qm)
    Object variable, component_particulars, include_block_denotation_qm;
{
    x_note_fn_call(147,119);
    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)11L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_20);
}

static Object array_constant_5;    /* # */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-GENERIC-FORMULA */
Object denote_cell_array_element_for_generic_formula(generic_formula,
	    component_particulars,include_block_denotation_qm)
    Object generic_formula, component_particulars, include_block_denotation_qm;
{
    x_note_fn_call(147,120);
    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)8L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_20);
}

/* VALIDATE-ALL-GENERIC-FORMULA-INVOCATIONS */
Object validate_all_generic_formula_invocations()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, variable;
    Object formula_invocation_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(147,121);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    variable = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      formula_invocation_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qvariable);
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
      variable = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      formula_invocation_qm = ISVREF(variable,(SI_Long)34L);
      if (formula_invocation_qm)
	  validate_generic_formula_invocation_environment(formula_invocation_qm,
		  variable,T);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* VALIDATE-GENERIC-FORMULA-INVOCATION-ENVIRONMENT */
Object validate_generic_formula_invocation_environment(formula_invocation,
	    variable,also_validate_item_classes_qm)
    Object formula_invocation, variable, also_validate_item_classes_qm;
{
    Object generic_formula_qm, frame_serial_number, gensymed_symbol, xa, ya;
    Object expression_cell_parent, g2_cell_array, temp_1, expression_cell;
    Object byte_code_body, environment_description, environment_length;
    Object local_var_vector, value_qm, svref_new_value, item_type_qm, x2;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(147,122);
    generic_formula_qm = ISVREF(formula_invocation,(SI_Long)9L);
    frame_serial_number = ISVREF(formula_invocation,(SI_Long)10L);
    if (generic_formula_qm) {
	gensymed_symbol = ISVREF(generic_formula_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(generic_formula_qm) ? 
		EQ(ISVREF(generic_formula_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    expression_cell_parent = temp ? generic_formula_qm : variable;
    g2_cell_array = 
	    get_lookup_slot_value_given_default(expression_cell_parent,
	    Qcell_array,Nil);
    if (g2_cell_array) {
	if (FIXNUM_LE(ISVREF(g2_cell_array_managed_array_function(g2_cell_array),
		(SI_Long)1L),Maximum_in_place_array_size)) {
	    temp_1 = g2_cell_array_managed_array_function(g2_cell_array);
	    expression_cell = ISVREF(temp_1,(SI_Long)0L + 
		    IFIX(Managed_array_index_offset));
	}
	else
	    expression_cell = 
		    ISVREF(ISVREF(g2_cell_array_managed_array_function(g2_cell_array),
		    (SI_Long)2L),(SI_Long)0L);
    }
    else
	expression_cell = Nil;
    byte_code_body = expression_cell ? 
	    g2_expression_cell_byte_code_body_function(expression_cell) : Nil;
    environment_description = byte_code_body ? ISVREF(byte_code_body,
	    (SI_Long)4L) : Nil;
    environment_length = var_count(environment_description);
    local_var_vector = ISVREF(formula_invocation,(SI_Long)2L);
    if (generic_formula_qm) {
	if ( !TRUEP(also_validate_item_classes_qm)) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(environment_length);
	    value_qm = Nil;
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    value_qm = ISVREF(local_var_vector,index_1);
	    if (value_qm) {
		svref_new_value = 
			validate_item_or_evaluation_value(value_qm,
			frame_serial_number,Nil);
		ISVREF(local_var_vector,index_1) = svref_new_value;
	    }
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	else {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(environment_length);
	    value_qm = Nil;
	    item_type_qm = Nil;
	  next_loop_1:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop_1;
	    value_qm = ISVREF(local_var_vector,index_1);
	    if (SIMPLE_VECTOR_P(value_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(value_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(value_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    item_type_qm = temp ? 
		    var_type_from_index_function(environment_description,
		    FIX(index_1)) : Nil;
	    if (value_qm) {
		svref_new_value = 
			validate_item_or_evaluation_value(value_qm,
			frame_serial_number,item_type_qm);
		ISVREF(local_var_vector,index_1) = svref_new_value;
	    }
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Put_current_value_called_from_simulator_p, Qput_current_value_called_from_simulator_p);

static Object string_constant_21;  /* "~a" */

/* PUT-CURRENT-VALUE */
Object put_current_value varargs_1(int, n)
{
    Object variable_or_parameter, value, data_type, expiration_time_qm;
    Object collection_time_qm;
    Object override_validity_interval_qm, evaluation_value;
    Object problem_description_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(147,123);
    INIT_ARGS_nonrelocating();
    variable_or_parameter = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    data_type = REQUIRED_ARG_nonrelocating();
    expiration_time_qm = REQUIRED_ARG_nonrelocating();
    collection_time_qm = REQUIRED_ARG_nonrelocating();
    override_validity_interval_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    evaluation_value = make_evaluation_value_1(value,data_type);
    problem_description_qm = 
	    put_current_evaluation_value(variable_or_parameter,
	    evaluation_value,expiration_time_qm,collection_time_qm,
	    override_validity_interval_qm);
    if ( !TRUEP(problem_description_qm)) {
	temp = expiration_time_qm;
	if (temp);
	else
	    temp = Gensym_time;
	return VALUES_3(value,temp,data_type);
    }
    else {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_21,
		    problem_description_qm);
	reclaim_evaluation_value(evaluation_value);
	reclaim_text_string(problem_description_qm);
	return VALUES_3(Nil,Nil,Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Put_current_evaluation_value_old_value_qm, Qput_current_evaluation_value_old_value_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Put_current_evaluation_value_return_value, Qput_current_evaluation_value_return_value);

static Object string_constant_22;  /* "An attempt was made to store a value into ~NF which failed, ~
				    *          because it was not active."
				    */

static Object string_constant_23;  /* "An attempt to store the value ~NV of type ~NT into ~NF failed ~
				    *            because of type mismatch.  ~NF requires values of type ~NT."
				    */

static Object float_constant;      /* 0.0 */

static Object Qsupplied;           /* supplied */

static Object string_constant_24;  /* "The variable ~NF, which has a validity ~
				    *                         interval of SUPPLIED, received a value ~
				    *                         with no supplied expiration time."
				    */

static Object Qindefinite;         /* indefinite */

static Object string_constant_25;  /* "The variable ~NF has an invalid validity ~
				    *                      interval.  This is a G2 internal error, please ~
				    *                      notify Gensym software support."
				    */

/* PUT-CURRENT-EVALUATION-VALUE */
Object put_current_evaluation_value(variable_or_parameter,evaluation_value,
	    supplied_expiration_time_qm,supplied_collection_time_qm,
	    override_validity_interval_qm)
    Object variable_or_parameter, evaluation_value;
    Object supplied_expiration_time_qm, supplied_collection_time_qm;
    Object override_validity_interval_qm;
{
    Object sub_class_bit_vector, variable_qm, history_spec_qm;
    Object type_specification, unix_supplied_collection_time_qm;
    Object old_collection_time, amf_available_array_cons_qm, amf_array, temp;
    Object temp_1, amf_result, new_float, new_value, temp_2;
    Object validity_interval_of_variable_qm;
    Object expiration_time_of_new_current_value, truth_value_p, new_value_type;
    Object value, new_managed_value, old_managed_value, old_expiration;
    Object gensymed_symbol_4, structure_being_reclaimed, temp_5;
    Object interested_list_qm, thing_cons, cdr_of_cons_qm, thing, eval_cons;
    Object value_changed_p, value_or_expiration_changed_qm;
    Object evaluation_value_for_simulator;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp_3;
    double aref_new_value, arg, arg_1, collection_time_of_new_current_value;
    double gensymed_symbol_3, temp_4;
    Declare_special(1);

    x_note_fn_call(147,124);
    if (Noting_changes_to_kb_p)
	note_change_to_runtime_data_for_block_1(variable_or_parameter);
    if ( !((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)5L)) 
	    & (SI_Long)1L)))
	return tformat_text_string(2,string_constant_22,variable_or_parameter);
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
	variable_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	variable_qm = Nil;
    history_spec_qm = ISVREF(variable_or_parameter,(SI_Long)25L);
    type_specification = 
	    type_specification_of_variable_or_parameter_value(variable_or_parameter);
    if (supplied_collection_time_qm) {
	if (FIXNUMP(supplied_collection_time_qm))
	    unix_supplied_collection_time_qm = 
		    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(FIXNUM_MINUS(supplied_collection_time_qm,
		    Gensym_time_at_start)) + 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L));
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(supplied_collection_time_qm) 
		!= (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(supplied_collection_time_qm)) 
		== (SI_Long)1L)
	    unix_supplied_collection_time_qm = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(supplied_collection_time_qm,
		    (SI_Long)0L));
	else
	    unix_supplied_collection_time_qm = supplied_collection_time_qm;
    }
    else
	unix_supplied_collection_time_qm = Nil;
    old_collection_time = ISVREF(variable_or_parameter,(SI_Long)21L);
    if (FIXNUMP(evaluation_value) && EQ(type_specification,Qfloat)) {
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
	aref_new_value = (double)IFIX(evaluation_value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	new_value = new_float;
	evaluation_value = new_value;
    }
    else if (INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L && EQ(type_specification,Qfloat)) {
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
	temp_2 = normalize_to_gensym_float(evaluation_value);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	new_value = new_float;
	reclaim_managed_simple_long_array_of_length_1(evaluation_value);
	evaluation_value = new_value;
    }
    if ( !(EQ(type_specification,Qnumber) && (FIXNUMP(evaluation_value) || 
	    INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
	    (SI_Long)1L) || evaluation_value_of_type_p(evaluation_value,
	    type_specification)))
	return tformat_text_string(6,string_constant_23,evaluation_value,
		evaluation_value_type(evaluation_value),
		variable_or_parameter,variable_or_parameter,
		type_specification);
    if (unix_supplied_collection_time_qm) {
	arg = DOUBLE_FLOAT_TO_DOUBLE(unix_supplied_collection_time_qm);
	if (FIXNUMP(old_collection_time)) {
	    temp_2 = lfloat(old_collection_time,float_constant);
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	}
	else
	    arg_1 = DFLOAT_ISAREF_1(old_collection_time,(SI_Long)0L);
	temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	if (history_spec_qm) {
	    temp_2 = get_or_make_history_buffer(variable_or_parameter,
		    history_spec_qm);
	    store_history_value(temp_2,history_spec_qm,
		    evaluation_value_value(evaluation_value),
		    unix_supplied_collection_time_qm,Nil);
	}
	reclaim_evaluation_value(evaluation_value);
	return VALUES_1(Nil);
    }
    validity_interval_of_variable_qm = variable_qm ? 
	    ISVREF(variable_or_parameter,(SI_Long)27L) : Nil;
    temp_2 = unix_supplied_collection_time_qm;
    if (temp_2);
    else
	temp_2 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L));
    collection_time_of_new_current_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
    if ( !TRUEP(variable_qm))
	expiration_time_of_new_current_value = Nil;
    else if (override_validity_interval_qm || 
	    EQ(validity_interval_of_variable_qm,Qsupplied)) {
	if (supplied_expiration_time_qm) {
	    if (FIXNUMP(supplied_expiration_time_qm))
		expiration_time_of_new_current_value = 
			supplied_expiration_time_qm;
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(supplied_expiration_time_qm) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(supplied_expiration_time_qm)) 
		    == (SI_Long)1L) {
		gensymed_symbol_3 = 
			DFLOAT_ISAREF_1(supplied_expiration_time_qm,
			(SI_Long)0L) - DFLOAT_ISAREF_1(G2_time_at_start,
			(SI_Long)0L) + (double)IFIX(Gensym_time_at_start);
		arg = gensymed_symbol_3;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp_3);
		else {
		    arg = gensymed_symbol_3;
		    arg_1 = 
			    DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		    temp_3 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		expiration_time_of_new_current_value = temp_3 ? 
			Most_negative_fixnum : 
			LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_3));
	    }
	    else if (FLOATP(supplied_expiration_time_qm)) {
		temp_4 = DOUBLE_FLOAT_TO_DOUBLE(supplied_expiration_time_qm);
		gensymed_symbol_3 = temp_4 - 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
			(double)IFIX(Gensym_time_at_start);
		arg = gensymed_symbol_3;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
			  !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp_3);
		else {
		    arg = gensymed_symbol_3;
		    arg_1 = 
			    DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		    temp_3 = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		expiration_time_of_new_current_value = temp_3 ? 
			Most_negative_fixnum : 
			LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol_3));
	    }
	    else
		expiration_time_of_new_current_value = 
			supplied_expiration_time_qm;
	}
	else
	    return tformat_text_string(2,string_constant_24,
		    variable_or_parameter);
    }
    else if (EQ(validity_interval_of_variable_qm,Qindefinite))
	expiration_time_of_new_current_value = Qnever;
    else if (FIXNUMP(validity_interval_of_variable_qm)) {
	gensymed_symbol = IFIX(validity_interval_of_variable_qm);
	gensymed_symbol_3 = collection_time_of_new_current_value - 
		DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
		(double)IFIX(Gensym_time_at_start);
	arg = gensymed_symbol_3;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
	temp_3 = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	if (temp_3);
	else {
	    arg = gensymed_symbol_3;
	    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
	    temp_3 = arg < arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	gensymed_symbol_1 = temp_3 ? IFIX(Most_negative_fixnum) : 
		inline_floor_1(gensymed_symbol_3);
	expiration_time_of_new_current_value = FIX(gensymed_symbol + 
		gensymed_symbol_1);
    }
    else
	return tformat_text_string(2,string_constant_25,variable_or_parameter);
    truth_value_p = CONSP(evaluation_value) ? (EQ(M_CDR(evaluation_value),
	    Qtruth_value) ? T : Nil) : Qnil;
    new_value_type = evaluation_value_type(evaluation_value);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qtruth_value)) {
	value = M_CAR(evaluation_value);
	if ( !(EQ(evaluation_value,Evaluation_true_value) || 
		EQ(evaluation_value,Evaluation_false_value)))
	    reclaim_eval_cons_1(evaluation_value);
	new_managed_value = value;
    }
    else
	new_managed_value = evaluation_value;
    old_managed_value = ISVREF(variable_or_parameter,(SI_Long)23L);
    old_expiration = variable_qm ? ISVREF(variable_or_parameter,
	    (SI_Long)26L) : Nil;
    if (Put_current_evaluation_value_old_value_qm) {
	Put_current_evaluation_value_return_value = 
		CAS_SVREF(variable_or_parameter,(SI_Long)23L,
		Put_current_evaluation_value_old_value_qm,new_managed_value);
	if ( !TRUEP(Put_current_evaluation_value_return_value))
	    return VALUES_1(Nil);
    }
    else
	ISVREF(variable_or_parameter,(SI_Long)23L) = new_managed_value;
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(old_collection_time) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(old_collection_time)) == 
	    (SI_Long)1L)
	DFLOAT_ISASET_1(old_collection_time,(SI_Long)0L,
		collection_time_of_new_current_value);
    else {
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,
		collection_time_of_new_current_value);
	ISVREF(variable_or_parameter,(SI_Long)21L) = new_float;
    }
    if (variable_qm) {
	svref_new_value = IFIX(ISVREF(variable_or_parameter,(SI_Long)5L)) 
		&  ~(SI_Long)32L;
	ISVREF(variable_or_parameter,(SI_Long)5L) = FIX(svref_new_value);
	gensymed_symbol_4 = Nil;
      next_loop:
	gensymed_symbol_4 = ISVREF(variable_or_parameter,(SI_Long)30L);
	if (CAS_SVREF(variable_or_parameter,(SI_Long)30L,gensymed_symbol_4,
		Nil)) {
	    if (gensymed_symbol_4) {
		if (EQ(gensymed_symbol_4,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol_4,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol_4);
		inline_note_reclaim_cons(gensymed_symbol_4,Nil);
		structure_being_reclaimed = gensymed_symbol_4;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol_4,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol_4,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol_4,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = gensymed_symbol_4;
	    }
	    goto end_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
	ISVREF(variable_or_parameter,(SI_Long)26L) = 
		expiration_time_of_new_current_value;
	ISVREF(variable_or_parameter,(SI_Long)29L) = Nil;
    }
    if (history_spec_qm) {
	temp_2 = get_or_make_history_buffer(variable_or_parameter,
		history_spec_qm);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(new_managed_value) != (SI_Long)0L 
		&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_managed_value)) == 
		(SI_Long)1L)
	    temp_5 = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(new_managed_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(new_managed_value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_managed_value)) == 
		(SI_Long)1L)
	    temp_5 = aref1(new_managed_value,FIX((SI_Long)0L));
	else
	    temp_5 = new_managed_value;
	store_history_value(temp_2,history_spec_qm,temp_5,
		DOUBLE_TO_DOUBLE_FLOAT(collection_time_of_new_current_value),
		Nil);
    }
    if (variable_qm) {
	interested_list_qm = ISVREF(variable_or_parameter,(SI_Long)36L);
	if (interested_list_qm) {
	    ISVREF(variable_or_parameter,(SI_Long)36L) = Nil;
	    thing_cons = interested_list_qm;
	    cdr_of_cons_qm = Nil;
	    thing = Nil;
	  next_loop_1:
	    cdr_of_cons_qm = M_CDR(thing_cons);
	    thing = M_CAR(thing_cons);
	    variable_has_received_a_value(thing,variable_or_parameter);
	    if ( !TRUEP(cdr_of_cons_qm))
		goto end_loop_1;
	    thing_cons = cdr_of_cons_qm;
	    goto next_loop_1;
	  end_loop_1:
	    if (interested_list_qm &&  !((SI_Long)0L == 
		    inline_debugging_consing())) {
		eval_cons = interested_list_qm;
	      next_loop_2:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,thing_cons))
		    goto end_2;
		else if ( !TRUEP(eval_cons))
		    goto end_2;
		else
		    eval_cons = CDR(eval_cons);
		goto next_loop_2;
	      end_loop_2:
	      end_2:;
	    }
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = interested_list_qm;
		temp = Available_eval_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = thing_cons;
	    }
	    else {
		temp = Available_eval_conses_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = interested_list_qm;
		temp = Available_eval_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = thing_cons;
	    }
	    M_CDR(thing_cons) = Nil;
	}
    }
    value_changed_p = FIXNUMP(new_managed_value) && 
	    FIXNUMP(old_managed_value) ? (FIXNUM_NE(old_managed_value,
	    new_managed_value) ? T : Nil) : Qnil;
    if (value_changed_p);
    else
	value_changed_p =  !TRUEP(evaluation_value_eql(2,new_managed_value,
		old_managed_value)) ? T : Nil;
    value_or_expiration_changed_qm = value_changed_p;
    if (value_or_expiration_changed_qm);
    else
	value_or_expiration_changed_qm = variable_qm ? ( 
		!(FIXNUMP(expiration_time_of_new_current_value) && 
		FIXNUMP(old_expiration) && 
		FIXNUM_EQ(expiration_time_of_new_current_value,
		old_expiration) || EQ(expiration_time_of_new_current_value,
		old_expiration)) ? T : Nil) : Qnil;
    if ((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)4L)) & 
	    (SI_Long)2L) &&  !((IFIX(Current_computation_flags) & 
	    (SI_Long)512L) != (SI_Long)0L)) {
	temp_2 = (SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,
		(SI_Long)4L)) & (SI_Long)32L) ? T : Nil;
	if (temp_2);
	else
	    temp_2 = value_or_expiration_changed_qm;
    }
    else
	temp_2 = Nil;
    invoke_rules_for_forward_chaining(variable_or_parameter,
	    new_managed_value,new_value_type,temp_2,old_managed_value);
    if (value_or_expiration_changed_qm) {
	update_representations_of_variable_or_parameter_value(variable_or_parameter);
	if ( !TRUEP(variable_qm) &&  
		!TRUEP(Put_current_value_called_from_simulator_p)) {
	    if (truth_value_p) {
		if (FIXNUM_EQ(new_managed_value,Truth))
		    evaluation_value_for_simulator = Evaluation_true_value;
		else if (FIXNUM_EQ(new_managed_value,Falsity))
		    evaluation_value_for_simulator = Evaluation_false_value;
		else
		    evaluation_value_for_simulator = 
			    eval_cons_1(new_managed_value,Qtruth_value);
	    }
	    else
		evaluation_value_for_simulator = 
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(new_managed_value) 
			!= (SI_Long)0L ? 
			copy_wide_string(new_managed_value) : 
			FIXNUMP(new_managed_value) || 
			SYMBOLP(new_managed_value) ? new_managed_value : 
			copy_evaluation_value_1(new_managed_value);
	    set_external_variable_for_simulator(3,variable_or_parameter,
		    evaluation_value_for_simulator,truth_value_p ? 
		    Qtruth_value : Nil);
	    reclaim_evaluation_value(evaluation_value_for_simulator);
	}
    }
    if (variable_qm)
	withdraw_backward_chaining(variable_or_parameter);
    if ( !FIXNUMP(old_managed_value))
	old_managed_value = 
		reclaim_managed_number_or_value_function(old_managed_value);
    if ((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)4L)) & 
	    (SI_Long)1048576L))
	cache_explanation(variable_or_parameter);
    return VALUES_1(Nil);
}

static Object string_constant_26;  /* "In ~NF, an attempt was made to conclude that the variable ~NF has no ~
				    *           current value.  The attempt failed, because the variable was not ~
				    *           active."
				    */

/* PUT-HAS-NO-CURRENT-VALUE */
Object put_has_no_current_value(variable)
    Object variable;
{
    Object expiration_time_of_current_value, managed_number_or_value;
    Object old_value, svref_new_value;

    x_note_fn_call(147,125);
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & (SI_Long)1L)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(variable);
	expiration_time_of_current_value = ISVREF(variable,(SI_Long)26L);
	if (EQ(expiration_time_of_current_value,Qnever) || 
		FIXNUM_GE(expiration_time_of_current_value,Gensym_time)) {
	    managed_number_or_value = ISVREF(variable,(SI_Long)23L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		old_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		old_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else
		old_value = managed_number_or_value;
	    svref_new_value = FIXNUM_SUB1(Gensym_time);
	    ISVREF(variable,(SI_Long)26L) = svref_new_value;
	    invoke_update_functions_for_put_has_no_current_value(variable,
		    old_value);
	    update_representations_of_variable_or_parameter_value(variable);
	    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & 
		    (SI_Long)1048576L))
		cache_explanation(variable);
	}
    }
    else if ((SI_Long)3L <= IFIX(Warning_message_level))
	give_warning_1(4,FIX((SI_Long)3L),string_constant_26,
		Current_computation_frame,variable);
    return VALUES_3(Nil,Nil,Nil);
}

static Object string_constant_27;  /* "In ~NF, an attempt was made to conclude that the variable ~NF has no ~
				    *          value.  The attempt failed, because the variable was not ~
				    *          active."
				    */

/* PUT-HAS-NO-VALUE */
Object put_has_no_value(variable)
    Object variable;
{
    Object expiration, managed_number_or_value, old_value, svref_new_value;
    Object thing, managed_float;

    x_note_fn_call(147,126);
    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)5L)) & (SI_Long)1L)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_runtime_data_for_block_1(variable);
	expiration = ISVREF(variable,(SI_Long)26L);
	if (EQ(expiration,Qnever) || FIXNUM_NE(expiration,Some_time_ago)) {
	    managed_number_or_value = ISVREF(variable,(SI_Long)23L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		old_value = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		old_value = aref1(managed_number_or_value,FIX((SI_Long)0L));
	    else
		old_value = managed_number_or_value;
	    svref_new_value = Some_time_ago;
	    ISVREF(variable,(SI_Long)26L) = svref_new_value;
	    thing = ISVREF(variable,(SI_Long)21L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
		managed_float = ISVREF(variable,(SI_Long)21L);
		reclaim_managed_simple_float_array_of_length_1(managed_float);
	    }
	    svref_new_value = Some_time_ago;
	    ISVREF(variable,(SI_Long)21L) = svref_new_value;
	    invoke_update_functions_for_put_has_no_current_value(variable,
		    old_value);
	    update_representations_of_variable_or_parameter_value(variable);
	    if ((SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & 
		    (SI_Long)1048576L))
		cache_explanation(variable);
	}
    }
    else {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)3L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)3L),string_constant_27,
		    Current_computation_frame,variable);
	Suppress_warning_message_header_qm = Nil;
    }
    return VALUES_3(Nil,Nil,Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-ITEMS-NEEDING-INITIALIZATION-SKIP-LIST-SENTINEL */
Object make_items_needing_initialization_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(147,127);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* MUTATE-ITEMS-NEEDING-INITIALIZATION-SKIP-LIST-ENTRY */
Object mutate_items_needing_initialization_skip_list_entry(node,new_key,
	    new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(147,128);
    reclaim_frame_serial_number(ISVREF(node,(SI_Long)2L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_items_needing_initialization_skip_list_entry = UNBOUND;

static Object Qframe_serial_number_equal_function;  /* frame-serial-number-equal-function */

/* CLEAR-ITEMS-NEEDING-INITIALIZATION-TREE */
Object clear_items_needing_initialization_tree(items_needing_initialization_skip_list)
    Object items_needing_initialization_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, fsn, old_key;

    x_note_fn_call(147,129);
    head = M_CAR(M_CDR(items_needing_initialization_skip_list));
    tail = M_CDR(M_CDR(items_needing_initialization_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    fsn = key_qm;
    temp = 
	    delete_skip_list_entry(SYMBOL_FUNCTION(Qframe_serial_number_equal_function),
	    temp,items_needing_initialization_skip_list,FIX((SI_Long)31L),
	    FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
    old_key = temp;
    if (old_key)
	reclaim_frame_serial_number(old_key);
    goto next_loop;
  end_loop:;
    return VALUES_1(items_needing_initialization_skip_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Items_needing_initialization_tree, Qitems_needing_initialization_tree);

/* NOTE-ITEM-NEEDING-INITIALIZATION-FUNCTION */
Object note_item_needing_initialization_function(item)
    Object item;
{
    Object gensymed_symbol, temp, temp_1, fsn;

    x_note_fn_call(147,130);
    gensymed_symbol = copy_frame_serial_number(ISVREF(item,(SI_Long)3L));
    temp = Items_needing_initialization_tree;
    temp_1 = Fp_mutate_items_needing_initialization_skip_list_entry;
    fsn = gensymed_symbol;
    return set_skip_list_entry(temp,FIX((SI_Long)31L),
	    Qframe_serial_number_equal_function,temp_1,T,gensymed_symbol,
	    FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)),item);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-VARIABLE */
Object activate_subclass_of_entity_for_variable(variable)
    Object variable;
{
    x_note_fn_call(147,131);
    if (ISVREF(variable,(SI_Long)32L) || ISVREF(variable,(SI_Long)22L))
	return note_item_needing_initialization_function(variable);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_inference_background_collection = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_inference_background_collections, Qchain_of_available_inference_background_collections);

DEFINE_VARIABLE_WITH_SYMBOL(Inference_background_collection_count, Qinference_background_collection_count);

Object Chain_of_available_inference_background_collections_vector = UNBOUND;

/* INFERENCE-BACKGROUND-COLLECTION-STRUCTURE-MEMORY-USAGE */
Object inference_background_collection_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(147,132);
    temp = Inference_background_collection_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)7L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INFERENCE-BACKGROUND-COLLECTION-COUNT */
Object outstanding_inference_background_collection_count()
{
    Object def_structure_inference_background_collection_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(147,133);
    gensymed_symbol = IFIX(Inference_background_collection_count);
    def_structure_inference_background_collection_variable = 
	    Chain_of_available_inference_background_collections;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_inference_background_collection_variable))
	goto end_loop;
    def_structure_inference_background_collection_variable = 
	    ISVREF(def_structure_inference_background_collection_variable,
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

/* RECLAIM-INFERENCE-BACKGROUND-COLLECTION-1 */
Object reclaim_inference_background_collection_1(inference_background_collection)
    Object inference_background_collection;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(147,134);
    inline_note_reclaim_cons(inference_background_collection,Nil);
    structure_being_reclaimed = inference_background_collection;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(inference_background_collection,(SI_Long)3L);
      if (CAS_SVREF(inference_background_collection,(SI_Long)3L,
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
      goto next_loop;
    end_loop:
    end_1:;
      SVREF(inference_background_collection,FIX((SI_Long)3L)) = Nil;
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = ISVREF(inference_background_collection,(SI_Long)5L);
      if (CAS_SVREF(inference_background_collection,(SI_Long)5L,
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
	  goto end_2;
      }
      goto next_loop_1;
    end_loop_1:
    end_2:;
      SVREF(inference_background_collection,FIX((SI_Long)5L)) = Nil;
    POP_SPECIAL();
    temp = 
	    ISVREF(Chain_of_available_inference_background_collections_vector,
	    IFIX(Current_thread_index));
    SVREF(inference_background_collection,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_inference_background_collections_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = inference_background_collection;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INFERENCE-BACKGROUND-COLLECTION */
Object reclaim_structure_for_inference_background_collection(inference_background_collection)
    Object inference_background_collection;
{
    x_note_fn_call(147,135);
    return reclaim_inference_background_collection_1(inference_background_collection);
}

static Object Qg2_defstruct_structure_name_inference_background_collection_g2_struct;  /* g2-defstruct-structure-name::inference-background-collection-g2-struct */

/* MAKE-PERMANENT-INFERENCE-BACKGROUND-COLLECTION-STRUCTURE-INTERNAL */
Object make_permanent_inference_background_collection_structure_internal()
{
    Object def_structure_inference_background_collection_variable;
    Object defstruct_g2_inference_background_collection_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(147,136);
    def_structure_inference_background_collection_variable = Nil;
    atomic_incff_symval(Qinference_background_collection_count,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_inference_background_collection_variable = Nil;
	gensymed_symbol = (SI_Long)7L;
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
	defstruct_g2_inference_background_collection_variable = the_array;
	SVREF(defstruct_g2_inference_background_collection_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct;
	def_structure_inference_background_collection_variable = 
		defstruct_g2_inference_background_collection_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_inference_background_collection_variable);
}

/* MAKE-INFERENCE-BACKGROUND-COLLECTION-1 */
Object make_inference_background_collection_1(inference_background_collection_variable)
    Object inference_background_collection_variable;
{
    Object def_structure_inference_background_collection_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(147,137);
    def_structure_inference_background_collection_variable = 
	    ISVREF(Chain_of_available_inference_background_collections_vector,
	    IFIX(Current_thread_index));
    if (def_structure_inference_background_collection_variable) {
	svref_arg_1 = 
		Chain_of_available_inference_background_collections_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_inference_background_collection_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_inference_background_collection_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct;
    }
    else
	def_structure_inference_background_collection_variable = 
		make_permanent_inference_background_collection_structure_internal();
    inline_note_allocate_cons(def_structure_inference_background_collection_variable,
	    Nil);
    SVREF(def_structure_inference_background_collection_variable,
	    FIX((SI_Long)1L)) = inference_background_collection_variable;
    ISVREF(def_structure_inference_background_collection_variable,
	    (SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(def_structure_inference_background_collection_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_inference_background_collection_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_inference_background_collection_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_inference_background_collection_variable,
	    FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_inference_background_collection_variable);
}

static Object Qperform_background_collection_for_inference_engine;  /* perform-background-collection-for-inference-engine */

/* BEGIN-COLLECTING-DATA-FOR-INFERENCE-ENGINE */
Object begin_collecting_data_for_inference_engine(variable,interval)
    Object variable, interval;
{
    Object collection_structure, frame_serial_number_setf_arg, old, new_1;
    Object temp, old_1, new_2, def_structure_schedule_task_variable;
    Object svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(147,138);
    collection_structure = ISVREF(variable,(SI_Long)33L);
    if ( !TRUEP(collection_structure)) {
	collection_structure = 
		make_inference_background_collection_1(variable);
	frame_serial_number_setf_arg = ISVREF(variable,(SI_Long)3L);
	old = ISVREF(collection_structure,(SI_Long)2L);
	new_1 = frame_serial_number_setf_arg;
	temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(collection_structure,FIX((SI_Long)2L)) = temp;
	ISVREF(variable,(SI_Long)33L) = collection_structure;
    }
    old_1 = Nil;
    new_2 = Nil;
  next_loop:
    old_1 = ISVREF(collection_structure,(SI_Long)3L);
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
    aref_new_value = FIXNUMP(interval) ? (double)IFIX(interval) : 
	    DFLOAT_ISAREF_1(interval,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)4L);
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = Nil;
    g2_p =  !TRUEP(Nil);
    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
	    Current_real_time,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    SVREF(task,FIX((SI_Long)7L)) = 
	    Qperform_background_collection_for_inference_engine;
    temp = 
	    SYMBOL_FUNCTION(Qperform_background_collection_for_inference_engine);
    SVREF(task,FIX((SI_Long)8L)) = temp;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
    SVREF(task,FIX((SI_Long)13L)) = collection_structure;
    SVREF(task,FIX((SI_Long)14L)) = T;
    new_2 = task;
    if (CAS_SVREF(collection_structure,(SI_Long)3L,old_1,new_2)) {
	task = new_2;
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
	inline_note_reclaim_cons(new_2,Nil);
	structure_being_reclaimed = new_2;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(new_2,(SI_Long)9L));
	  SVREF(new_2,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(new_2,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = new_2;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ATTEMPT-NEW-VARIABLE-VALUE-COLLECTION */
Object attempt_new_variable_value_collection(variable,priority_qm,force_qm)
    Object variable, priority_qm, force_qm;
{
    Object collection_structure, frame_serial_number_setf_arg, old, new_1;
    Object temp, old_1, new_2, def_structure_schedule_task_variable;
    Object svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(147,139);
    collection_structure = ISVREF(variable,(SI_Long)33L);
    if ( !TRUEP(collection_structure)) {
	collection_structure = 
		make_inference_background_collection_1(variable);
	frame_serial_number_setf_arg = ISVREF(variable,(SI_Long)3L);
	old = ISVREF(collection_structure,(SI_Long)2L);
	new_1 = frame_serial_number_setf_arg;
	temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(collection_structure,FIX((SI_Long)2L)) = temp;
	ISVREF(variable,(SI_Long)33L) = collection_structure;
    }
    if (priority_qm) {
	old_1 = Nil;
	new_2 = Nil;
      next_loop:
	old_1 = ISVREF(collection_structure,(SI_Long)5L);
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
	SVREF(task,FIX((SI_Long)4L)) = priority_qm;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = 
		Qperform_background_collection_for_inference_engine;
	temp = 
		SYMBOL_FUNCTION(Qperform_background_collection_for_inference_engine);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	SVREF(task,FIX((SI_Long)13L)) = collection_structure;
	SVREF(task,FIX((SI_Long)14L)) = force_qm;
	new_2 = task;
	if (CAS_SVREF(collection_structure,(SI_Long)5L,old_1,new_2)) {
	    task = new_2;
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
	    goto end_1;
	}
	else {
	    inline_note_reclaim_cons(new_2,Nil);
	    structure_being_reclaimed = new_2;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(new_2,(SI_Long)9L));
	      SVREF(new_2,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(new_2,FIX((SI_Long)0L)) = temp;
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = new_2;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    else
	perform_background_collection_for_inference_engine(collection_structure,
		force_qm);
    return VALUES_1(Nil);
}

/* WAKE-UP-INFERENCE-BACKGROUND-COLLECTION */
Object wake_up_inference_background_collection(collection_structure)
    Object collection_structure;
{
    Object variable, gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(147,140);
    variable = ISVREF(collection_structure,(SI_Long)1L);
    gensymed_symbol = ISVREF(variable,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(variable) ? EQ(ISVREF(variable,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(collection_structure,(SI_Long)2L);
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
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if (temp);
    else
	temp = TRUEP(ISVREF(variable,(SI_Long)32L));
    if ( !temp)
	stop_collecting_data_for_inference_engine(variable);
    return VALUES_1(Nil);
}

/* PERFORM-BACKGROUND-COLLECTION-FOR-INFERENCE-ENGINE */
Object perform_background_collection_for_inference_engine(collection_structure,
	    force_qm)
    Object collection_structure, force_qm;
{
    Object variable, gensymed_symbol, x, y, xa, ya, current_computation_frame;
    Object current_computation_instance, current_computation_flags;
    Object variables_that_did_not_have_values, structure_being_reclaimed;
    Object temp_1, svref_arg_2, thing;
    char temp;
    Declare_special(5);

    x_note_fn_call(147,141);
    variable = ISVREF(collection_structure,(SI_Long)1L);
    gensymed_symbol = ISVREF(variable,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(variable) ? EQ(ISVREF(variable,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(collection_structure,(SI_Long)2L);
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
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp) {
	current_computation_frame = variable;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		4);
	  current_computation_instance = collection_structure;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
		  3);
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		    2);
	      variables_that_did_not_have_values = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Variables_that_did_not_have_values,Qvariables_that_did_not_have_values,variables_that_did_not_have_values,
		      1);
		if (force_qm)
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) | (SI_Long)4L);
		else
		    Current_computation_flags = 
			    FIX(IFIX(Current_computation_flags) &  
			    ~(SI_Long)4L);
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)256L);
		gensymed_symbol = Nil;
	      next_loop:
		gensymed_symbol = ISVREF(collection_structure,(SI_Long)5L);
		if (CAS_SVREF(collection_structure,(SI_Long)5L,
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
			temp_1 = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
			temp_1 = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_1,svref_arg_2) = gensymed_symbol;
		    }
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
	      end_1:;
		open_wake_up_collection_function(Nil);
		thing = get_current_evaluation_value(variable,Nil);
		if ( !(FIXNUMP(thing) || SYMBOLP(thing) || 
			SIMPLE_VECTOR_P(thing)))
		    reclaim_if_evaluation_value_1(thing);
		set_wake_ups_function(Nil);
		clean_up_wake_ups_state_if_any();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* STOP-COLLECTING-DATA-FOR-INFERENCE-ENGINE */
Object stop_collecting_data_for_inference_engine(variable)
    Object variable;
{
    Object collection_structure, variable_1, ab_loop_list_;
    Object pruned_interest_list;

    x_note_fn_call(147,142);
    collection_structure = ISVREF(variable,(SI_Long)33L);
    if (collection_structure) {
	variable_1 = Nil;
	ab_loop_list_ = ISVREF(collection_structure,(SI_Long)4L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	variable_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	pruned_interest_list = delete_eval_element_1(collection_structure,
		ISVREF(variable_1,(SI_Long)36L));
	ISVREF(variable_1,(SI_Long)36L) = pruned_interest_list;
	if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable_1,
		(SI_Long)38L)))
	    withdraw_backward_chaining(variable_1);
	goto next_loop;
      end_loop:;
	reclaim_eval_list_1(ISVREF(collection_structure,(SI_Long)4L));
	SVREF(collection_structure,FIX((SI_Long)4L)) = Nil;
	reclaim_inference_background_collection_1(collection_structure);
	ISVREF(variable,(SI_Long)33L) = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qg2_internal_cached_explanation;  /* g2-internal-cached-explanation */

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-VARIABLE */
Object deactivate_subclass_of_entity_for_variable(variable)
    Object variable;
{
    Object source_or_map, server_qm, data_server_qm, temp, gensymed_symbol;
    Object structure_being_reclaimed, temp_1, svref_arg_2, thing;
    Object managed_float, cached_explanation, interested_list, ab_loop_list_;
    Object last_1, next_qm;
    SI_Long svref_new_value;
    Declare_special(1);

    x_note_fn_call(147,143);
    source_or_map = ISVREF(variable,(SI_Long)31L);
    server_qm = ATOM(source_or_map) ? 
	    lookup_kb_specific_property_value(source_or_map,
	    Data_server_or_alias_qm_kbprop) : Nil;
    data_server_qm = server_qm ? server_qm : 
	    warn_of_undefined_data_server(variable,source_or_map);
    if (data_server_qm) {
	if (SIMPLE_VECTOR_P(data_server_qm) && EQ(ISVREF(data_server_qm,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct)) {
	    temp = SYMBOL_FUNCTION(ISVREF(data_server_qm,(SI_Long)4L));
	    FUNCALL_1(temp,variable);
	}
	stop_collecting_data_for_inference_engine(variable);
    }
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(variable,(SI_Long)30L);
    if (CAS_SVREF(variable,(SI_Long)30L,gensymed_symbol,Nil)) {
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = gensymed_symbol;
	}
	goto end_1;
    }
    goto next_loop;
  end_loop:
  end_1:;
    ISVREF(variable,(SI_Long)29L) = Nil;
    temp_1 = Some_time_ago;
    ISVREF(variable,(SI_Long)26L) = temp_1;
    thing = ISVREF(variable,(SI_Long)21L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L) {
	managed_float = ISVREF(variable,(SI_Long)21L);
	reclaim_managed_simple_float_array_of_length_1(managed_float);
    }
    temp_1 = Some_time_ago;
    ISVREF(variable,(SI_Long)21L) = temp_1;
    cached_explanation = get_lookup_slot_value_given_default(variable,
	    Qg2_internal_cached_explanation,Nil);
    if (cached_explanation) {
	reclaim_cached_explanation(cached_explanation);
	set_non_savable_lookup_slot_value(variable,
		Qg2_internal_cached_explanation,Nil);
    }
    update_representations_of_variable_or_parameter_value(variable);
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = ISVREF(variable,(SI_Long)39L);
    if (CAS_SVREF(variable,(SI_Long)39L,gensymed_symbol,Nil)) {
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = gensymed_symbol;
	}
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    svref_new_value = IFIX(ISVREF(variable,(SI_Long)5L)) &  ~(SI_Long)32L;
    ISVREF(variable,(SI_Long)5L) = FIX(svref_new_value);
    interested_list = ISVREF(variable,(SI_Long)36L);
    thing = Nil;
    ab_loop_list_ = interested_list;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    thing = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    variable_is_no_longer_available(thing,variable);
    goto next_loop_2;
  end_loop_2:;
    if (interested_list) {
	last_1 = interested_list;
	next_qm = Nil;
      next_loop_3:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_3;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_3;
      end_loop_3:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = interested_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = interested_list;
	    temp_1 = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(variable,(SI_Long)36L) = Nil;
    withdraw_backward_chaining(variable);
    return clear_histories(variable);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-PARAMETER */
Object activate_subclass_of_entity_for_parameter(parameter)
    Object parameter;
{
    x_note_fn_call(147,144);
    note_item_needing_initialization_function(parameter);
    return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-PARAMETER */
Object deactivate_subclass_of_entity_for_parameter(parameter)
    Object parameter;
{
    Object initial_value, svref_new_value, store_managed_number_or_value_arg_1;
    double store_managed_number_or_value_arg;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(147,145);
    initial_value = ISVREF(parameter,(SI_Long)22L);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(initial_value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value)) == (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    store_managed_number_or_value_arg = 
		    DFLOAT_ISAREF_1(initial_value,(SI_Long)0L);
	    svref_new_value = 
		    store_managed_number_or_value_function(ISVREF(parameter,
		    (SI_Long)23L),
		    DOUBLE_TO_DOUBLE_FLOAT(store_managed_number_or_value_arg));
	    ISVREF(parameter,(SI_Long)23L) = svref_new_value;
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else {
	store_managed_number_or_value_arg_1 = initial_value;
	svref_new_value = 
		store_managed_number_or_value_function(ISVREF(parameter,
		(SI_Long)23L),store_managed_number_or_value_arg_1);
	ISVREF(parameter,(SI_Long)23L) = svref_new_value;
    }
    clear_histories(parameter);
    update_representations_of_variable_or_parameter_value(parameter);
    return VALUES_1(Nil);
}

Object Indexed_attribute_hash_table_kbprop = UNBOUND;

Object Indexed_attribute_classes_kbprop = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Indexed_attributes, Qindexed_attributes);

/* MAKE-INDEXED-ATTRIBUTE-DEFINING-CLASSES-SKIP-LIST-SENTINEL */
Object make_indexed_attribute_defining_classes_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(147,146);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

static Object Qab_gensym;          /* gensym */

/* MUTATE-INDEXED-ATTRIBUTE-DEFINING-CLASSES-SKIP-LIST-ENTRY */
Object mutate_indexed_attribute_defining_classes_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    Object gensym_list, last_1, next_qm, temp, svref_arg_2;

    x_note_fn_call(147,147);
    gensym_list = ISVREF(node,(SI_Long)3L);
    if (gensym_list) {
	last_1 = gensym_list;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	if (ISVREF(Available_gensym_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensym_list;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_gensym_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensym_list;
	    temp = Available_gensym_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_indexed_attribute_defining_classes_skip_list_entry = UNBOUND;

/* CLEAR-INDEXED-ATTRIBUTE-DEFINING-CLASSES-SKIP-LIST */
Object clear_indexed_attribute_defining_classes_skip_list(indexed_attribute_defining_classes_skip_list)
    Object indexed_attribute_defining_classes_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_entry, last_1, next_qm;
    Object temp_1, svref_arg_2;
    Object result;

    x_note_fn_call(147,148);
    head = M_CAR(M_CDR(indexed_attribute_defining_classes_skip_list));
    tail = M_CDR(M_CDR(indexed_attribute_defining_classes_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    indexed_attribute_defining_classes_skip_list,FIX((SI_Long)31L),
	    frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry) {
	if (old_entry) {
	    last_1 = old_entry;
	    next_qm = Nil;
	  next_loop_1:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_1;
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    last_1 = next_qm;
	    goto next_loop_1;
	  end_loop_1:
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = old_entry;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = old_entry;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(indexed_attribute_defining_classes_skip_list);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_indexed_attribute_parent_objects_hash_vector_43_vectors, Qavailable_indexed_attribute_parent_objects_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors, Qcount_of_indexed_attribute_parent_objects_hash_vector_43_vectors);

Object Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector = UNBOUND;

/* INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object indexed_attribute_parent_objects_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(147,149);
    temp = Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTORS */
Object out_indexed_attribute_parent_objects_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(147,150);
    temp = 
	    FIXNUM_MINUS(Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    length(Available_indexed_attribute_parent_objects_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_indexed_attribute_parent_objects_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(147,151);
    atomic_incff_symval(Qcount_of_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR */
Object make_indexed_attribute_parent_objects_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(147,152);
    if (ISVREF(Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index));
	inline_note_reclaim_cons(vector_pool_cons,Qvector_pool);
	if (ISVREF(Available_vector_pool_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_vector_pool_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	else {
	    temp_2 = Available_vector_pool_conses_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	    temp_2 = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2_1) = vector_pool_cons;
	}
	M_CDR(vector_pool_cons) = Nil;
	SVREF(svref_arg_1,svref_arg_2) = temp_1;
    }
    else
	temp = 
		make_permanent_indexed_attribute_parent_objects_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR */
Object reclaim_indexed_attribute_parent_objects_hash_vector(indexed_attribute_parent_objects_hash_vector_43_vector)
    Object indexed_attribute_parent_objects_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(147,153);
    svref_arg_1 = 
	    Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector;
    svref_arg_2 = Current_thread_index;
    new_cons = ISVREF(Available_vector_pool_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_vector_pool_conses_vector;
	svref_arg_2_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_vector_pool_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_vector_pool_conses_tail_vector;
	    svref_arg_2_1 = Current_thread_index;
	    SVREF(temp,svref_arg_2_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_vector_pool_cons_pool();
    M_CAR(gensymed_symbol) = 
	    indexed_attribute_parent_objects_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

/* MAKE-INDEXED-ATTRIBUTE-PARENT-OBJECTS-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_indexed_attribute_parent_objects_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(147,154);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)31L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)32L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)31L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

static Object Qlookup;             /* lookup */

/* MUTATE-INDEXED-ATTRIBUTE-PARENT-OBJECTS-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    Object indexed_attribute_defining_classes_skip_list, head, tail;
    Object element_qm, key_qm, temp, old_entry, last_1, next_qm, temp_1;
    Object svref_arg_2;
    Object result;

    x_note_fn_call(147,155);
    reclaim_evaluation_value(ISVREF(node,(SI_Long)2L));
    indexed_attribute_defining_classes_skip_list = ISVREF(node,(SI_Long)3L);
    head = M_CAR(M_CDR(indexed_attribute_defining_classes_skip_list));
    tail = M_CDR(M_CDR(indexed_attribute_defining_classes_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    indexed_attribute_defining_classes_skip_list,FIX((SI_Long)31L),
	    frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry) {
	if (old_entry) {
	    last_1 = old_entry;
	    next_qm = Nil;
	  next_loop_1:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_1;
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    last_1 = next_qm;
	    goto next_loop_1;
	  end_loop_1:
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = old_entry;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = old_entry;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    goto next_loop;
  end_loop:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(indexed_attribute_defining_classes_skip_list) = Nil;
    M_CADR(indexed_attribute_defining_classes_skip_list) = Nil;
    M_CAR(indexed_attribute_defining_classes_skip_list) = Nil;
    if (indexed_attribute_defining_classes_skip_list) {
	last_1 = indexed_attribute_defining_classes_skip_list;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = indexed_attribute_defining_classes_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    indexed_attribute_defining_classes_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry = UNBOUND;

static Object Qevaluation_value_equal_p;  /* evaluation-value-equal-p */

/* CLEAR-INDEXED-ATTRIBUTE-PARENT-OBJECTS-TREE */
Object clear_indexed_attribute_parent_objects_tree(indexed_attribute_parent_objects_tree_for_hash_skip_list)
    Object indexed_attribute_parent_objects_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, temp_1, old_key, old_entry;
    Object head_1, tail_1, old_entry_1, last_1, next_qm, temp_2, svref_arg_2;
    Object result;

    x_note_fn_call(147,156);
    head = 
	    M_CAR(M_CDR(indexed_attribute_parent_objects_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(indexed_attribute_parent_objects_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    if (FIXNUMP(key_qm))
	temp_1 = FIXNUM_ABS(key_qm);
    else if (SYMBOLP(key_qm))
	temp_1 = FIX(SXHASH_SYMBOL_1(key_qm) & IFIX(Most_positive_fixnum));
    else if (text_string_p(key_qm))
	temp_1 = compute_text_hash_code(key_qm);
    else
	temp_1 = FIX((SI_Long)0L);
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qevaluation_value_equal_p),
	    temp,indexed_attribute_parent_objects_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),temp_1);
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_evaluation_value(old_key);
    if (old_entry) {
	head_1 = M_CAR(M_CDR(old_entry));
	tail_1 = M_CDR(M_CDR(old_entry));
	element_qm = Nil;
	key_qm = Nil;
      next_loop_1:
	element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head_1,(SI_Long)0L),
		(SI_Long)0L));
	key_qm = ISVREF(element_qm,(SI_Long)2L);
	if ( ! !EQ(element_qm,tail_1))
	    goto end_loop_1;
	temp = key_qm;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
		old_entry,FIX((SI_Long)31L),frame_hash_function(key_qm));
	old_entry_1 = NTH_VALUE((SI_Long)1L, result);
	if (old_entry_1) {
	    if (old_entry_1) {
		last_1 = old_entry_1;
		next_qm = Nil;
	      next_loop_2:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_2;
		inline_note_reclaim_cons(last_1,Qab_gensym);
		last_1 = next_qm;
		goto next_loop_2;
	      end_loop_2:
		inline_note_reclaim_cons(last_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = old_entry_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		else {
		    temp_2 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = old_entry_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	}
	goto next_loop_1;
      end_loop_1:
	reclaim_skip_list_element(head_1);
	reclaim_skip_list_element(tail_1);
	M_CDDR(old_entry) = Nil;
	M_CADR(old_entry) = Nil;
	M_CAR(old_entry) = Nil;
	if (old_entry) {
	    last_1 = old_entry;
	    next_qm = Nil;
	  next_loop_3:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_3;
	    inline_note_reclaim_cons(last_1,Qlookup);
	    last_1 = next_qm;
	    goto next_loop_3;
	  end_loop_3:
	    inline_note_reclaim_cons(last_1,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = old_entry;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    else {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = old_entry;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(indexed_attribute_parent_objects_tree_for_hash_skip_list);
}

static Object Qindexed_attribute_parent_objects_tree_for_hash;  /* indexed-attribute-parent-objects-tree-for-hash */

/* MAKE-INDEXED-ATTRIBUTE-PARENT-OBJECTS */
Object make_indexed_attribute_parent_objects()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(147,157);
    new_vector = make_indexed_attribute_parent_objects_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_indexed_attribute_parent_objects_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_indexed_attribute_parent_objects_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
	    tail);
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol) = Qindexed_attribute_parent_objects_tree_for_hash;
    new_cons = ISVREF(Available_lookup_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	svref_arg_1 = Available_lookup_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index)))) {
	    svref_arg_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(svref_arg_1,svref_arg_2) = Nil;
	}
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_lookup_cons_pool();
    M_CAR(gensymed_symbol_1) = head;
    M_CDR(gensymed_symbol_1) = tail;
    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
    M_CDR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-INDEXED-ATTRIBUTE-PARENT-OBJECTS */
Object flatten_indexed_attribute_parent_objects(indexed_attribute_parent_objects_hash_table)
    Object indexed_attribute_parent_objects_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(147,158);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(indexed_attribute_parent_objects_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-INDEXED-ATTRIBUTE-PARENT-OBJECTS */
Object clear_indexed_attribute_parent_objects(indexed_attribute_parent_objects_hash_table)
    Object indexed_attribute_parent_objects_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(147,159);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_indexed_attribute_parent_objects_tree(ISVREF(indexed_attribute_parent_objects_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-INDEXED-ATTRIBUTE-PARENT-OBJECTS */
Object reclaim_indexed_attribute_parent_objects(indexed_attribute_parent_objects_hash_table)
    Object indexed_attribute_parent_objects_hash_table;
{
    Object indexed_attribute_parent_objects_tree_for_hash_skip_list, head;
    Object tail, element_qm, key_qm, temp, temp_1, old_key, old_entry, head_1;
    Object tail_1, old_entry_1, last_1, next_qm, temp_2, svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(147,160);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    indexed_attribute_parent_objects_tree_for_hash_skip_list = 
	    ISVREF(indexed_attribute_parent_objects_hash_table,index_1);
    head = 
	    M_CAR(M_CDR(indexed_attribute_parent_objects_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(indexed_attribute_parent_objects_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    if (FIXNUMP(key_qm))
	temp_1 = FIXNUM_ABS(key_qm);
    else if (SYMBOLP(key_qm))
	temp_1 = FIX(SXHASH_SYMBOL_1(key_qm) & IFIX(Most_positive_fixnum));
    else if (text_string_p(key_qm))
	temp_1 = compute_text_hash_code(key_qm);
    else
	temp_1 = FIX((SI_Long)0L);
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qevaluation_value_equal_p),
	    temp,indexed_attribute_parent_objects_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),temp_1);
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_evaluation_value(old_key);
    if (old_entry) {
	head_1 = M_CAR(M_CDR(old_entry));
	tail_1 = M_CDR(M_CDR(old_entry));
	element_qm = Nil;
	key_qm = Nil;
      next_loop_2:
	element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head_1,(SI_Long)0L),
		(SI_Long)0L));
	key_qm = ISVREF(element_qm,(SI_Long)2L);
	if ( ! !EQ(element_qm,tail_1))
	    goto end_loop_2;
	temp = key_qm;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
		old_entry,FIX((SI_Long)31L),frame_hash_function(key_qm));
	old_entry_1 = NTH_VALUE((SI_Long)1L, result);
	if (old_entry_1) {
	    if (old_entry_1) {
		last_1 = old_entry_1;
		next_qm = Nil;
	      next_loop_3:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_3;
		inline_note_reclaim_cons(last_1,Qab_gensym);
		last_1 = next_qm;
		goto next_loop_3;
	      end_loop_3:
		inline_note_reclaim_cons(last_1,Qab_gensym);
		if (ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = old_entry_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		else {
		    temp_2 = Available_gensym_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = old_entry_1;
		    temp_2 = Available_gensym_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	}
	goto next_loop_2;
      end_loop_2:
	reclaim_skip_list_element(head_1);
	reclaim_skip_list_element(tail_1);
	M_CDDR(old_entry) = Nil;
	M_CADR(old_entry) = Nil;
	M_CAR(old_entry) = Nil;
	if (old_entry) {
	    last_1 = old_entry;
	    next_qm = Nil;
	  next_loop_4:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_4;
	    inline_note_reclaim_cons(last_1,Qlookup);
	    last_1 = next_qm;
	    goto next_loop_4;
	  end_loop_4:
	    inline_note_reclaim_cons(last_1,Qlookup);
	    if (ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = old_entry;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    else {
		temp_2 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = old_entry;
		temp_2 = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(indexed_attribute_parent_objects_tree_for_hash_skip_list) = Nil;
    M_CADR(indexed_attribute_parent_objects_tree_for_hash_skip_list) = Nil;
    M_CAR(indexed_attribute_parent_objects_tree_for_hash_skip_list) = Nil;
    if (indexed_attribute_parent_objects_tree_for_hash_skip_list) {
	last_1 = indexed_attribute_parent_objects_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_5:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_5;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_5;
      end_loop_5:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_2 = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_2) = 
		    indexed_attribute_parent_objects_tree_for_hash_skip_list;
	    temp_2 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	else {
	    temp_2 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = 
		    indexed_attribute_parent_objects_tree_for_hash_skip_list;
	    temp_2 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_2,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(indexed_attribute_parent_objects_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_indexed_attribute_parent_objects_hash_vector(indexed_attribute_parent_objects_hash_table);
    return VALUES_1(temp);
}

/* MAKE-INDEXED-ATTRIBUTE-HASH-TABLE */
Object make_indexed_attribute_hash_table(attribute_name)
    Object attribute_name;
{
    Object temp;

    x_note_fn_call(147,161);
    temp = make_indexed_attribute_parent_objects();
    return mutate_kb_specific_property_value(attribute_name,temp,
	    Indexed_attribute_hash_table_kbprop);
}

/* RECLAIM-INDEXED-ATTRIBUTE-HASH-TABLE */
Object reclaim_indexed_attribute_hash_table(attribute_name)
    Object attribute_name;
{
    Object hash_table_qm;

    x_note_fn_call(147,162);
    hash_table_qm = lookup_kb_specific_property_value(attribute_name,
	    Indexed_attribute_hash_table_kbprop);
    if (hash_table_qm) {
	reclaim_indexed_attribute_parent_objects(hash_table_qm);
	return mutate_kb_specific_property_value(attribute_name,Nil,
		Indexed_attribute_hash_table_kbprop);
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-INDEXED-ATTRIBUTE-HASH-TABLE */
Object clear_indexed_attribute_hash_table(attribute_name)
    Object attribute_name;
{
    Object hash_table_qm;

    x_note_fn_call(147,163);
    hash_table_qm = lookup_kb_specific_property_value(attribute_name,
	    Indexed_attribute_hash_table_kbprop);
    if (hash_table_qm)
	return clear_indexed_attribute_parent_objects(hash_table_qm);
    else
	return VALUES_1(Nil);
}

/* MAKE-ALL-INDEXED-ATTRIBUTE-HASH-TABLES */
Object make_all_indexed_attribute_hash_tables()
{
    Object attribute, ab_loop_list_;

    x_note_fn_call(147,164);
    attribute = Nil;
    ab_loop_list_ = Indexed_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    make_indexed_attribute_hash_table(attribute);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RECLAIM-ALL-INDEXED-ATTRIBUTE-HASH-TABLES */
Object reclaim_all_indexed_attribute_hash_tables()
{
    Object attribute, ab_loop_list_;

    x_note_fn_call(147,165);
    attribute = Nil;
    ab_loop_list_ = Indexed_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_indexed_attribute_hash_table(attribute);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qindexed_attribute_defining_classes;  /* indexed-attribute-defining-classes */

/* PUT-INDEXED-ATTRIBUTE-PARENT */
Object put_indexed_attribute_parent(attribute,defining_attribute_class,
	    attribute_value,attribute_parent_object)
    Object attribute, defining_attribute_class, attribute_value;
    Object attribute_parent_object;
{
    Object indexed_attribute_hash_table_qm, tail, head, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object new_attribute_value_tree, attribute_evaluation_value;
    Object stored_attribute_value_tree, temp_2, temp_3, head_1, tail_1;
    Object element_qm, key_qm, old_entry, last_1, next_qm, new_class_list, fsn;
    Object stored_class_list;
    SI_Long gensymed_symbol_2, temp_1;
    Object result;

    x_note_fn_call(147,166);
    indexed_attribute_hash_table_qm = 
	    lookup_kb_specific_property_value(attribute,
	    Indexed_attribute_hash_table_kbprop);
    if (indexed_attribute_hash_table_qm) {
	tail = 
		make_indexed_attribute_defining_classes_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_indexed_attribute_defining_classes_skip_list_sentinel(Most_negative_fixnum,
		tail);
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol) = Qindexed_attribute_defining_classes;
	new_cons = ISVREF(Available_lookup_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_lookup_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = head;
	M_CDR(gensymed_symbol_1) = tail;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	M_CDR(gensymed_symbol) = gensymed_symbol_1;
	inline_note_allocate_cons(gensymed_symbol,Qlookup);
	new_attribute_value_tree = gensymed_symbol;
	attribute_evaluation_value = FIXNUMP(attribute_value) || 
		attribute_value && SYMBOLP(attribute_value) ? 
		attribute_value : copy_evaluation_value_1(attribute_value);
	if (FIXNUMP(attribute_evaluation_value))
	    gensymed_symbol_2 = IFIX(FIXNUM_ABS(attribute_evaluation_value));
	else if (SYMBOLP(attribute_evaluation_value))
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(attribute_evaluation_value) & 
		    IFIX(Most_positive_fixnum);
	else if (text_string_p(attribute_evaluation_value))
	    gensymed_symbol_2 = 
		    IFIX(compute_text_hash_code(attribute_evaluation_value));
	else
	    gensymed_symbol_2 = (SI_Long)0L;
	temp_1 = gensymed_symbol_2 % (SI_Long)43L;
	stored_attribute_value_tree = 
		set_skip_list_entry(SVREF(indexed_attribute_hash_table_qm,
		FIX(temp_1)),FIX((SI_Long)31L),Qevaluation_value_equal_p,
		Nil,Nil,attribute_evaluation_value,FIX(gensymed_symbol_2),
		new_attribute_value_tree);
	if (EQ(stored_attribute_value_tree,new_attribute_value_tree)) {
	    gensymed_symbol = attribute_parent_object;
	    temp_2 = 
		    Fp_mutate_indexed_attribute_defining_classes_skip_list_entry;
	    temp_3 = frame_hash_function(gensymed_symbol);
	    temp_3 = set_skip_list_entry(new_attribute_value_tree,
		    FIX((SI_Long)31L),Qeq,temp_2,T,gensymed_symbol,temp_3,
		    gensym_cons_1(defining_attribute_class,Nil));
	}
	else {
	    reclaim_evaluation_value(attribute_evaluation_value);
	    head_1 = M_CAR(M_CDR(new_attribute_value_tree));
	    tail_1 = M_CDR(M_CDR(new_attribute_value_tree));
	    element_qm = Nil;
	    key_qm = Nil;
	  next_loop:
	    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head_1,
		    (SI_Long)0L),(SI_Long)0L));
	    key_qm = ISVREF(element_qm,(SI_Long)2L);
	    if ( ! !EQ(element_qm,tail_1))
		goto end_loop;
	    temp_3 = key_qm;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_3,
		    new_attribute_value_tree,FIX((SI_Long)31L),
		    frame_hash_function(key_qm));
	    old_entry = NTH_VALUE((SI_Long)1L, result);
	    if (old_entry) {
		if (old_entry) {
		    last_1 = old_entry;
		    next_qm = Nil;
		  next_loop_1:
		    next_qm = M_CDR(last_1);
		    if ( !TRUEP(next_qm))
			goto end_loop_1;
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    last_1 = next_qm;
		    goto next_loop_1;
		  end_loop_1:
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    if (ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = ISVREF(Available_gensym_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = old_entry;
			temp = Available_gensym_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = last_1;
		    }
		    else {
			temp = Available_gensym_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = old_entry;
			temp = Available_gensym_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = last_1;
		    }
		    M_CDR(last_1) = Nil;
		}
	    }
	    goto next_loop;
	  end_loop:
	    reclaim_skip_list_element(head_1);
	    reclaim_skip_list_element(tail_1);
	    M_CDDR(new_attribute_value_tree) = Nil;
	    M_CADR(new_attribute_value_tree) = Nil;
	    M_CAR(new_attribute_value_tree) = Nil;
	    if (new_attribute_value_tree) {
		last_1 = new_attribute_value_tree;
		next_qm = Nil;
	      next_loop_2:
		next_qm = M_CDR(last_1);
		if ( !TRUEP(next_qm))
		    goto end_loop_2;
		inline_note_reclaim_cons(last_1,Qlookup);
		last_1 = next_qm;
		goto next_loop_2;
	      end_loop_2:
		inline_note_reclaim_cons(last_1,Qlookup);
		if (ISVREF(Available_lookup_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_lookup_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = new_attribute_value_tree;
		    temp = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = last_1;
		}
		else {
		    temp = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = new_attribute_value_tree;
		    temp = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = last_1;
		}
		M_CDR(last_1) = Nil;
	    }
	    new_class_list = gensym_cons_1(defining_attribute_class,Nil);
	    fsn = ISVREF(attribute_parent_object,(SI_Long)3L);
	    stored_class_list = 
		    set_skip_list_entry(stored_attribute_value_tree,
		    FIX((SI_Long)31L),Qeq,Nil,Nil,attribute_parent_object,
		    FIXNUMP(fsn) ? fsn : FIXNUM_LOGXOR(M_CAR(fsn),
		    M_CDR(fsn)),new_class_list);
	    if ( !EQ(stored_class_list,new_class_list)) {
		if (memq_function(defining_attribute_class,stored_class_list))
		    temp_3 = reclaim_gensym_cons_1(new_class_list);
		else {
		    temp = M_CDR(stored_class_list);
		    M_CDR(new_class_list) = temp;
		    temp_3 = M_CDR(stored_class_list) = new_class_list;
		}
	    }
	    else
		temp_3 = Nil;
	}
    }
    else
	temp_3 = Nil;
    return VALUES_1(temp_3);
}

/* REMOVE-INDEXED-ATTRIBUTE-PARENT */
Object remove_indexed_attribute_parent(attribute,attribute_defining_class,
	    attribute_value,attribute_parent_object)
    Object attribute, attribute_defining_class, attribute_value;
    Object attribute_parent_object;
{
    Object hash_table_qm, temp_1, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash, defining_classes_tree_qm;
    Object classes_list_qm, old_entry, last_1, next_qm, temp_3, svref_arg_2;
    Object gensymed_symbol_1, old_key, head, tail, element_qm, key_qm;
    Object old_entry_1, remaining_classes;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp_4;
    Object result;

    x_note_fn_call(147,167);
    hash_table_qm = lookup_kb_specific_property_value(attribute,
	    Indexed_attribute_hash_table_kbprop);
    if (hash_table_qm) {
	if (FIXNUMP(attribute_value))
	    gensymed_symbol = IFIX(FIXNUM_ABS(attribute_value));
	else if (SYMBOLP(attribute_value))
	    gensymed_symbol = SXHASH_SYMBOL_1(attribute_value) & 
		    IFIX(Most_positive_fixnum);
	else if (text_string_p(attribute_value))
	    gensymed_symbol = IFIX(compute_text_hash_code(attribute_value));
	else
	    gensymed_symbol = (SI_Long)0L;
	temp = gensymed_symbol % (SI_Long)43L;
	temp_1 = SVREF(hash_table_qm,FIX(temp));
	skip_list = CDR(temp_1);
	key_value = attribute_value;
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  
		!TRUEP(evaluation_value_equal_p(key_value,ISVREF(curr,
		(SI_Long)2L)))) {
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
	defining_classes_tree_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (evaluation_value_equal_p(key_value,
		ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
		Nil) : Nil;
    }
    else
	defining_classes_tree_qm = Nil;
    if (defining_classes_tree_qm) {
	skip_list = CDR(defining_classes_tree_qm);
	key_value = attribute_parent_object;
	key_hash_value = IFIX(frame_hash_function(attribute_parent_object));
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	classes_list_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
    }
    else
	classes_list_qm = Nil;
    if (memq_function(attribute_defining_class,classes_list_qm)) {
	if ( !EQ(M_CAR(classes_list_qm),attribute_defining_class))
	    temp_1 = delete_gensym_element_1(attribute_defining_class,
		    classes_list_qm);
	else if ( !TRUEP(M_CDR(classes_list_qm))) {
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
		    attribute_parent_object,defining_classes_tree_qm,
		    FIX((SI_Long)31L),
		    frame_hash_function(attribute_parent_object));
	    old_entry = NTH_VALUE((SI_Long)1L, result);
	    if (old_entry) {
		if (old_entry) {
		    last_1 = old_entry;
		    next_qm = Nil;
		  next_loop_6:
		    next_qm = M_CDR(last_1);
		    if ( !TRUEP(next_qm))
			goto end_loop_6;
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    last_1 = next_qm;
		    goto next_loop_6;
		  end_loop_6:
		    inline_note_reclaim_cons(last_1,Qab_gensym);
		    if (ISVREF(Available_gensym_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_3 = 
				ISVREF(Available_gensym_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_3) = old_entry;
			temp_3 = Available_gensym_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = last_1;
		    }
		    else {
			temp_3 = Available_gensym_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = old_entry;
			temp_3 = Available_gensym_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = last_1;
		    }
		    M_CDR(last_1) = Nil;
		}
	    }
	    gensymed_symbol_1 = CDR(defining_classes_tree_qm);
	    if (CONSP(gensymed_symbol_1)) {
		temp_1 = M_CAR(gensymed_symbol_1);
		temp_4 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    if (temp_4) {
		temp_1 = M_CDR(gensymed_symbol_1);
		temp_4 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_4 = TRUEP(Nil);
	    if (temp_4) {
		gensymed_symbol_1 = M_CDR(defining_classes_tree_qm);
		temp_1 = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(gensymed_symbol_1),
			(SI_Long)0L),(SI_Long)0L));
		temp_4 = EQ(temp_1,M_CDR(gensymed_symbol_1));
	    }
	    else
		temp_4 =  !TRUEP(M_CDR(defining_classes_tree_qm));
	    if (temp_4) {
		if (FIXNUMP(attribute_value))
		    gensymed_symbol = IFIX(FIXNUM_ABS(attribute_value));
		else if (SYMBOLP(attribute_value))
		    gensymed_symbol = SXHASH_SYMBOL_1(attribute_value) & 
			    IFIX(Most_positive_fixnum);
		else if (text_string_p(attribute_value))
		    gensymed_symbol = 
			    IFIX(compute_text_hash_code(attribute_value));
		else
		    gensymed_symbol = (SI_Long)0L;
		temp = gensymed_symbol % (SI_Long)43L;
		result = delete_skip_list_entry(SYMBOL_FUNCTION(Qevaluation_value_equal_p),
			attribute_value,SVREF(hash_table_qm,FIX(temp)),
			FIX((SI_Long)31L),FIX(gensymed_symbol));
		MVS_2(result,old_key,old_entry);
		if (old_key)
		    reclaim_evaluation_value(old_key);
		if (old_entry) {
		    head = M_CAR(M_CDR(old_entry));
		    tail = M_CDR(M_CDR(old_entry));
		    element_qm = Nil;
		    key_qm = Nil;
		  next_loop_7:
		    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,
			    (SI_Long)0L),(SI_Long)0L));
		    key_qm = ISVREF(element_qm,(SI_Long)2L);
		    if ( ! !EQ(element_qm,tail))
			goto end_loop_7;
		    temp_1 = key_qm;
		    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
			    temp_1,old_entry,FIX((SI_Long)31L),
			    frame_hash_function(key_qm));
		    old_entry_1 = NTH_VALUE((SI_Long)1L, result);
		    if (old_entry_1) {
			if (old_entry_1) {
			    last_1 = old_entry_1;
			    next_qm = Nil;
			  next_loop_8:
			    next_qm = M_CDR(last_1);
			    if ( !TRUEP(next_qm))
				goto end_loop_8;
			    inline_note_reclaim_cons(last_1,Qab_gensym);
			    last_1 = next_qm;
			    goto next_loop_8;
			  end_loop_8:
			    inline_note_reclaim_cons(last_1,Qab_gensym);
			    if (ISVREF(Available_gensym_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_3 = 
					ISVREF(Available_gensym_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_3) = old_entry_1;
				temp_3 = Available_gensym_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = last_1;
			    }
			    else {
				temp_3 = Available_gensym_conses_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = old_entry_1;
				temp_3 = Available_gensym_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(temp_3,svref_arg_2) = last_1;
			    }
			    M_CDR(last_1) = Nil;
			}
		    }
		    goto next_loop_7;
		  end_loop_7:
		    reclaim_skip_list_element(head);
		    reclaim_skip_list_element(tail);
		    M_CDDR(old_entry) = Nil;
		    M_CADR(old_entry) = Nil;
		    M_CAR(old_entry) = Nil;
		    if (old_entry) {
			last_1 = old_entry;
			next_qm = Nil;
		      next_loop_9:
			next_qm = M_CDR(last_1);
			if ( !TRUEP(next_qm))
			    goto end_loop_9;
			inline_note_reclaim_cons(last_1,Qlookup);
			last_1 = next_qm;
			goto next_loop_9;
		      end_loop_9:
			inline_note_reclaim_cons(last_1,Qlookup);
			if (ISVREF(Available_lookup_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_3 = 
				    ISVREF(Available_lookup_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_3) = old_entry;
			    temp_3 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_3,svref_arg_2) = last_1;
			}
			else {
			    temp_3 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_3,svref_arg_2) = old_entry;
			    temp_3 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_3,svref_arg_2) = last_1;
			}
			M_CDR(last_1) = Nil;
		    }
		}
		temp_1 = Nil;
	    }
	    else
		temp_1 = Nil;
	}
	else {
	    remaining_classes = M_CDR(classes_list_qm);
	    M_CDR(classes_list_qm) = Nil;
	    gensymed_symbol_1 = attribute_parent_object;
	    temp_1 = 
		    Fp_mutate_indexed_attribute_defining_classes_skip_list_entry;
	    temp_1 = set_skip_list_entry(defining_classes_tree_qm,
		    FIX((SI_Long)31L),Qeq,temp_1,T,gensymed_symbol_1,
		    frame_hash_function(gensymed_symbol_1),remaining_classes);
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* VALID-INDEXED-ATTRIBUTE-VALUE-P */
Object valid_indexed_attribute_value_p(attribute_value)
    Object attribute_value;
{
    Object temp;

    x_note_fn_call(147,168);
    temp = FIXNUMP(attribute_value) ? T : Nil;
    if (temp);
    else
	temp = SYMBOLP(attribute_value) ? T : Nil;
    if (temp);
    else
	temp = text_string_p(attribute_value);
    return VALUES_1(temp);
}

/* OF-VALID-INDEXED-ATTRIBUTE-CLASS-P */
Object of_valid_indexed_attribute_class_p(attribute_object)
    Object attribute_object;
{
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(147,169);
    sub_class_bit_vector = ISVREF(ISVREF(attribute_object,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
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
	sub_class_bit_vector = ISVREF(ISVREF(attribute_object,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Logical_parameter_class_description,(SI_Long)18L));
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
	temp_1 =  !temp ? T : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* INDEXED-ATTRIBUTE-OR-INHERITED-ATTRIBUTE-P */
Object indexed_attribute_or_inherited_attribute_p(attribute_name,class_1,
	    parent_object)
    Object attribute_name, class_1, parent_object;
{
    Object gensymed_symbol, sub_class_bit_vector, class_description;
    Object indexed_class, ab_loop_list_, ab_loop_it_, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(147,170);
    if ((SI_Long)0L != (IFIX(ISVREF(parent_object,(SI_Long)5L)) & 
	    (SI_Long)64L)) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(parent_object,
		    (SI_Long)1L),(SI_Long)19L);
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
    if (temp) {
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	if (class_description) {
	    indexed_class = Nil;
	    ab_loop_list_ = 
		    lookup_kb_specific_property_value(attribute_name,
		    Indexed_attribute_classes_kbprop);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    indexed_class = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(indexed_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,
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
		    ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
		}
		else
		    ab_loop_it_ = Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	    if (ab_loop_it_) {
		temp_1 = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp_1 = Qnil;
	  end_1:;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qhas_indexed_attributes;  /* has-indexed-attributes */

/* INDEXED-ATTRIBUTE-OR-INHERITED-ATTRIBUTE-FOR-CLASS-P */
Object indexed_attribute_or_inherited_attribute_for_class_p(attribute_name,
	    class_1)
    Object attribute_name, class_1;
{
    Object class_description_qm, indexed_class, ab_loop_list_, ab_loop_it_;
    Object gensymed_symbol, temp, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(147,171);
    if (get_class_feature_if_any(class_1,Qhas_indexed_attributes)) {
	class_description_qm = Nil;
	indexed_class = Nil;
	ab_loop_list_ = lookup_kb_specific_property_value(attribute_name,
		Indexed_attribute_classes_kbprop);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	indexed_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(indexed_class,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    temp = class_description_qm;
	    if (temp);
	    else {
		class_description_qm = 
			lookup_global_or_kb_specific_property_value(class_1,
			Class_description_gkbprop);
		temp = class_description_qm;
	    }
	    sub_class_bit_vector = ISVREF(temp,(SI_Long)19L);
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
		ab_loop_it_ = (SI_Long)0L < gensymed_symbol_1 ? T : Nil;
	    }
	    else
		ab_loop_it_ = Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

/* GET-AND-VALIDATE-INDEXED-ATTRIBUTE-VALUE */
Object get_and_validate_indexed_attribute_value(attribute_value_qm)
    Object attribute_value_qm;
{
    Object x2, managed_number_or_value, attribute_datum_qm, car_1, cdr_1;
    Object temp_1;
    char temp;

    x_note_fn_call(147,172);
    if (SIMPLE_VECTOR_P(attribute_value_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_value_qm)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(attribute_value_qm,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(attribute_value_qm,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (of_valid_indexed_attribute_class_p(attribute_value_qm)) {
	    managed_number_or_value = ISVREF(attribute_value_qm,(SI_Long)23L);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		attribute_datum_qm = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		    == (SI_Long)1L)
		attribute_datum_qm = aref1(managed_number_or_value,
			FIX((SI_Long)0L));
	    else
		attribute_datum_qm = managed_number_or_value;
	}
	else
	    attribute_datum_qm = Nil;
    }
    else if (SIMPLE_VECTOR_P(attribute_value_qm) && 
	    EQ(ISVREF(attribute_value_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	managed_number_or_value = ISVREF(attribute_value_qm,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    attribute_datum_qm = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    attribute_datum_qm = aref1(managed_number_or_value,
		    FIX((SI_Long)0L));
	else
	    attribute_datum_qm = managed_number_or_value;
    }
    else {
	if (CONSP(attribute_value_qm)) {
	    car_1 = M_CAR(attribute_value_qm);
	    cdr_1 = M_CDR(attribute_value_qm);
	    if (CONSP(cdr_1)) {
		temp_1 = M_CAR(cdr_1);
		temp = SYMBOLP(temp_1);
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ? slot_value_number_p(car_1) || 
		    text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    attribute_datum_qm = M_CAR(attribute_value_qm);
	else
	    attribute_datum_qm = attribute_value_qm;
    }
    if (attribute_datum_qm && 
	    valid_indexed_attribute_value_p(attribute_datum_qm))
	return VALUES_1(attribute_datum_qm);
    else
	return VALUES_1(Nil);
}

/* PUT-PARENT-IF-INDEXED-ATTRIBUTE */
Object put_parent_if_indexed_attribute(attribute_name,
	    attribute_defining_class,attribute_value,
	    old_attribute_value_qm,attribute_parent_object)
    Object attribute_name, attribute_defining_class, attribute_value;
    Object old_attribute_value_qm, attribute_parent_object;
{
    Object valid_old_attribute_value_qm, valid_attribute_value_qm;

    x_note_fn_call(147,173);
    valid_old_attribute_value_qm = Nil;
    valid_attribute_value_qm = Nil;
    if ( !EQUAL(attribute_value,old_attribute_value_qm) && 
	    indexed_attribute_or_inherited_attribute_p(attribute_name,
	    attribute_defining_class,attribute_parent_object)) {
	if (old_attribute_value_qm) {
	    valid_old_attribute_value_qm = 
		    get_and_validate_indexed_attribute_value(old_attribute_value_qm);
	    if (valid_old_attribute_value_qm)
		remove_indexed_attribute_parent(attribute_name,
			attribute_defining_class,
			valid_old_attribute_value_qm,attribute_parent_object);
	}
	valid_attribute_value_qm = 
		get_and_validate_indexed_attribute_value(attribute_value);
	if (valid_attribute_value_qm)
	    return put_indexed_attribute_parent(attribute_name,
		    attribute_defining_class,valid_attribute_value_qm,
		    attribute_parent_object);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

/* PUT-PARENT-FOR-ITS-INDEXED-ATTRIBUTES */
Object put_parent_for_its_indexed_attributes varargs_1(int, n)
{
    Object attribute_parent_object;
    Object do_frames_qm, indexed_attribute_alist, indexed_attribute;
    Object defining_class, ab_loop_list_, slot_description_from_class_qm;
    Object attribute_value_qm, ab_loop_desetq_, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(147,174);
    INIT_ARGS_nonrelocating();
    attribute_parent_object = REQUIRED_ARG_nonrelocating();
    do_frames_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if ((SI_Long)0L != (IFIX(ISVREF(attribute_parent_object,(SI_Long)5L)) 
	    & (SI_Long)64L)) {
	indexed_attribute_alist = 
		collect_all_indexed_attributes_for_object(attribute_parent_object);
	indexed_attribute = Nil;
	defining_class = Nil;
	ab_loop_list_ = indexed_attribute_alist;
	slot_description_from_class_qm = Nil;
	attribute_value_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	indexed_attribute = CAR(ab_loop_desetq_);
	defining_class = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	skip_list = CDR(Symbol_properties_table);
	key_value = defining_class;
	key_hash_value = SXHASH_SYMBOL_1(defining_class) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_1:
	if (level < ab_loop_bind_)
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_2:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_1;
	goto next_loop_2;
      end_loop_3:
      end_1:
	level = level - (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = defining_class;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		    tail);
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	    new_cons = ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_lookup_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_lookup_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_4:
	if (level < ab_loop_bind_)
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_5:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_5;
      end_loop_6:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_8;
	  end_loop_9:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_7;
	  end_loop_7:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_10:
	    if (level < ab_loop_bind_)
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_11;
	  end_loop_12:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_10;
	  end_loop_10:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	slot_description_from_class_qm = 
		get_slot_description_of_class_description_function(indexed_attribute,
		gensymed_symbol,defining_class);
	attribute_value_qm = 
		get_slot_value_if_any_function(attribute_parent_object,
		indexed_attribute,defining_class);
	if (slot_description_from_class_qm && EQ(defining_class,
		ISVREF(slot_description_from_class_qm,(SI_Long)3L))) {
	    temp_2 = TRUEP(do_frames_qm);
	    if (temp_2);
	    else {
		if (SIMPLE_VECTOR_P(attribute_value_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(attribute_value_qm)) 
			> (SI_Long)2L &&  !EQ(ISVREF(attribute_value_qm,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(attribute_value_qm,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_2 =  !temp_2;
	    }
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    put_parent_if_indexed_attribute(indexed_attribute,
		    defining_class,attribute_value_qm,Nil,
		    attribute_parent_object);
	goto next_loop;
      end_loop:
	reclaim_gensym_tree_1(indexed_attribute_alist);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-PARENT-IF-INDEXED-ATTRIBUTE */
Object remove_parent_if_indexed_attribute(attribute_name,
	    attribute_defining_class,attribute_value,attribute_parent_object)
    Object attribute_name, attribute_defining_class, attribute_value;
    Object attribute_parent_object;
{
    Object valid_attribute_value_qm;

    x_note_fn_call(147,175);
    if (indexed_attribute_or_inherited_attribute_p(attribute_name,
	    attribute_defining_class,attribute_parent_object)) {
	valid_attribute_value_qm = 
		get_and_validate_indexed_attribute_value(attribute_value);
	if (valid_attribute_value_qm)
	    return remove_indexed_attribute_parent(attribute_name,
		    attribute_defining_class,valid_attribute_value_qm,
		    attribute_parent_object);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-PARENT-FOR-ITS-INDEXED-ATTRIBUTES */
Object remove_parent_for_its_indexed_attributes(attribute_parent_object)
    Object attribute_parent_object;
{
    Object indexed_attribute_alist, indexed_attribute, class_1, ab_loop_list_;
    Object attribute_value_qm, ab_loop_desetq_;

    x_note_fn_call(147,176);
    if ((SI_Long)0L != (IFIX(ISVREF(attribute_parent_object,(SI_Long)5L)) 
	    & (SI_Long)64L)) {
	indexed_attribute_alist = 
		collect_all_indexed_attributes_for_object(attribute_parent_object);
	indexed_attribute = Nil;
	class_1 = Nil;
	ab_loop_list_ = indexed_attribute_alist;
	attribute_value_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	indexed_attribute = CAR(ab_loop_desetq_);
	class_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_value_qm = 
		get_slot_value_if_any_function(attribute_parent_object,
		indexed_attribute,class_1);
	if (attribute_value_qm)
	    remove_parent_if_indexed_attribute(indexed_attribute,class_1,
		    attribute_value_qm,attribute_parent_object);
	goto next_loop;
      end_loop:
	reclaim_gensym_tree_1(indexed_attribute_alist);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-ALL-INDEXED-ATTRIBUTES-FOR-OBJECT */
Object collect_all_indexed_attributes_for_object(object)
    Object object;
{
    x_note_fn_call(147,177);
    return collect_all_indexed_attributes_for_class(ISVREF(ISVREF(object,
	    (SI_Long)1L),(SI_Long)1L));
}

static Object Qindexed_attributes_for_definition;  /* indexed-attributes-for-definition */

/* COLLECT-ALL-INDEXED-ATTRIBUTES-FOR-CLASS */
Object collect_all_indexed_attributes_for_class(class_1)
    Object class_1;
{
    Object inherited_class, class_description, ab_loop_list_;
    Object inherited_class_def, indexed_attribute_list_qm, indexed_attribute;
    Object ab_loop_list__1, new_indexed_attribute_list;

    x_note_fn_call(147,178);
    if (get_class_feature_if_any(class_1,Qhas_indexed_attributes)) {
	inherited_class = Nil;
	class_description = 
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	inherited_class_def = Nil;
	indexed_attribute_list_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	inherited_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	inherited_class_def = 
		lookup_global_or_kb_specific_property_value(inherited_class,
		Class_definition_gkbprop);
	if ( !LISTP(inherited_class_def)) {
	    indexed_attribute = Nil;
	    ab_loop_list__1 = 
		    get_lookup_slot_value_given_default(inherited_class_def,
		    Qindexed_attributes_for_definition,Nil);
	    new_indexed_attribute_list = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    indexed_attribute = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    new_indexed_attribute_list = 
		    gensym_cons_1(gensym_cons_1(indexed_attribute,
		    inherited_class),Nil);
	    if ( !TRUEP(indexed_attribute_list_qm))
		indexed_attribute_list_qm = new_indexed_attribute_list;
	    else
		indexed_attribute_list_qm = 
			nconc2(indexed_attribute_list_qm,
			new_indexed_attribute_list);
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(indexed_attribute_list_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-INDEXED-ATTRIBUTE-HASH-TABLE */
Object update_indexed_attribute_hash_table(indexed_attribute)
    Object indexed_attribute;
{
    Object indexed_classes_qm, indexed_class, ab_loop_list_, scope_conses;
    Object ab_loopvar_, class_1, slot_description, temp, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_1, entry_hash;
    Object gensymed_symbol, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, ab_loopvar__1, indexed_item, slot_value_qm;
    Object indexed_attribute_value_qm;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,179);
    indexed_classes_qm = 
	    lookup_kb_specific_property_value(indexed_attribute,
	    Indexed_attribute_classes_kbprop);
    indexed_class = Nil;
    ab_loop_list_ = indexed_classes_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    indexed_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = indexed_class;
    class_1 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      slot_description = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop_1:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop_1;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      class_1 = temp;
      skip_list = CDR(Symbol_properties_table);
      key_value = class_1;
      key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
      bottom_level = (SI_Long)0L;
      marked = Nil;
      pred = M_CAR(skip_list);
      curr = Nil;
      succ = Nil;
      level = (SI_Long)31L;
      ab_loop_bind_ = bottom_level;
    next_loop_2:
      if (level < ab_loop_bind_)
	  goto end_loop_2;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_3:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_4:
      if ( !TRUEP(marked))
	  goto end_loop_3;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_4;
    end_loop_3:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	  pred = curr;
	  curr = succ;
      }
      else
	  goto end_1;
      goto next_loop_3;
    end_loop_4:
    end_1:
      level = level - (SI_Long)1L;
      goto next_loop_2;
    end_loop_2:;
      gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if ( !TRUEP(gensymed_symbol)) {
	  gensymed_symbol = class_1;
	  temp_1 = Symbol_properties_table;
	  temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		  IFIX(Most_positive_fixnum));
	  tail = 
		  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		  Nil);
	  head = 
		  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
		  tail);
	  new_cons = ISVREF(Available_lookup_conses_vector,
		  IFIX(Current_thread_index));
	  if (new_cons) {
	      svref_arg_1 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  svref_arg_1 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(svref_arg_1,svref_arg_2) = Nil;
	      }
	      gensymed_symbol_1 = new_cons;
	  }
	  else
	      gensymed_symbol_1 = Nil;
	  if ( !TRUEP(gensymed_symbol_1))
	      gensymed_symbol_1 = replenish_lookup_cons_pool();
	  M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
	  new_cons = ISVREF(Available_lookup_conses_vector,
		  IFIX(Current_thread_index));
	  if (new_cons) {
	      svref_arg_1 = Available_lookup_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      svref_new_value = M_CDR(new_cons);
	      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	      if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		      IFIX(Current_thread_index)))) {
		  svref_arg_1 = Available_lookup_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(svref_arg_1,svref_arg_2) = Nil;
	      }
	      gensymed_symbol_2 = new_cons;
	  }
	  else
	      gensymed_symbol_2 = Nil;
	  if ( !TRUEP(gensymed_symbol_2))
	      gensymed_symbol_2 = replenish_lookup_cons_pool();
	  M_CAR(gensymed_symbol_2) = head;
	  M_CDR(gensymed_symbol_2) = tail;
	  inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	  M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	  inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	  gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		  Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
      }
      global_properties = gensymed_symbol;
      skip_list = CDR(global_properties);
      key_value = Current_kb_specific_property_list_property_name;
      key_hash_value = 
	      SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	      & IFIX(Most_positive_fixnum);
      bottom_level = (SI_Long)0L;
      marked = Nil;
      pred = M_CAR(skip_list);
      curr = Nil;
      succ = Nil;
      level = (SI_Long)31L;
      ab_loop_bind_ = bottom_level;
    next_loop_5:
      if (level < ab_loop_bind_)
	  goto end_loop_5;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    next_loop_6:
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
    next_loop_7:
      if ( !TRUEP(marked))
	  goto end_loop_6;
      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
      temp_1 = ATOMIC_REF_OBJECT(reference);
      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
      result = VALUES_2(temp_1,temp);
      MVS_2(result,succ,marked);
      goto next_loop_7;
    end_loop_6:
      entry_hash = ISVREF(curr,(SI_Long)1L);
      if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	      key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	  pred = curr;
	  curr = succ;
      }
      else
	  goto end_2;
      goto next_loop_6;
    end_loop_7:
    end_2:
      level = level - (SI_Long)1L;
      goto next_loop_5;
    end_loop_5:;
      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	      (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	      (SI_Long)3L) : Nil) : Nil;
      if (kb_properties);
      else
	  kb_properties = Nil;
      if (kb_properties) {
	  skip_list = CDR(kb_properties);
	  key_value = Class_description_gkbprop;
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_8:
	  if (level < ab_loop_bind_)
	      goto end_loop_8;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_9:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_10:
	  if ( !TRUEP(marked))
	      goto end_loop_9;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_10;
	end_loop_9:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_3;
	  goto next_loop_9;
	end_loop_10:
	end_3:
	  level = level - (SI_Long)1L;
	  goto next_loop_8;
	end_loop_8:;
	  kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if (kb_specific_value);
	  else
	      kb_specific_value = No_specific_property_value;
      }
      else
	  kb_specific_value = No_specific_property_value;
      if ( !EQ(kb_specific_value,No_specific_property_value))
	  resulting_value = kb_specific_value;
      else {
	  skip_list = CDR(global_properties);
	  key_value = Class_description_gkbprop;
	  key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		  IFIX(Most_positive_fixnum);
	  bottom_level = (SI_Long)0L;
	  marked = Nil;
	  pred = M_CAR(skip_list);
	  curr = Nil;
	  succ = Nil;
	  level = (SI_Long)31L;
	  ab_loop_bind_ = bottom_level;
	next_loop_11:
	  if (level < ab_loop_bind_)
	      goto end_loop_11;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	next_loop_12:
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	next_loop_13:
	  if ( !TRUEP(marked))
	      goto end_loop_12;
	  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	  temp_1 = ATOMIC_REF_OBJECT(reference);
	  temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	  result = VALUES_2(temp_1,temp);
	  MVS_2(result,succ,marked);
	  goto next_loop_13;
	end_loop_12:
	  entry_hash = ISVREF(curr,(SI_Long)1L);
	  if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		  key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	      pred = curr;
	      curr = succ;
	  }
	  else
	      goto end_4;
	  goto next_loop_12;
	end_loop_13:
	end_4:
	  level = level - (SI_Long)1L;
	  goto next_loop_11;
	end_loop_11:;
	  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		  key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) 
		  ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	  if (resulting_value);
	  else
	      resulting_value = Nil;
      }
      gensymed_symbol = resulting_value;
      slot_description = 
	      get_slot_description_of_class_description_function(indexed_attribute,
	      gensymed_symbol,indexed_class);
      ab_loopvar__1 = lookup_kb_specific_property_value(class_1,
	      Instances_specific_to_this_class_kbprop);
      indexed_item = Nil;
    next_loop_14:
      if ( !TRUEP(ab_loopvar__1))
	  goto end_loop_14;
      indexed_item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(indexed_item,(SI_Long)5L)) & 
	      (SI_Long)1L)) {
	  slot_value_qm = get_slot_description_value(indexed_item,
		  slot_description);
	  indexed_attribute_value_qm = slot_value_qm ? 
		  get_and_validate_indexed_attribute_value(slot_value_qm) :
		   Nil;
	  if (indexed_attribute_value_qm)
	      put_indexed_attribute_parent(indexed_attribute,indexed_class,
		      indexed_attribute_value_qm,indexed_item);
      }
      goto next_loop_14;
    end_loop_14:;
      goto next_loop_1;
    end_loop_1:;
    POP_SPECIAL();
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* UPDATE-ALL-INDEXED-ATTRIBUTE-HASH-TABLES */
Object update_all_indexed_attribute_hash_tables()
{
    Object attribute, ab_loop_list_;

    x_note_fn_call(147,180);
    attribute = Nil;
    ab_loop_list_ = Indexed_attributes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    update_indexed_attribute_hash_table(attribute);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qthere_exists_literal;  /* there-exists-literal */

static Object Qab_or;              /* or */

static Object Qis;                 /* is */

static Object Qclass_qualified_name;  /* class-qualified-name */

/* EXPRESSION-MAY-USE-INDEXED-ATTRIBUTE-P */
Object expression_may_use_indexed_attribute_p(expression)
    Object expression;
{
    Object operator_qm, gensymed_symbol, gensymed_symbol_1, role;
    Object var_spot_or_symbol, domain_qm, logical_expression;
    Object logical_expression_list_qm, possible_equality_expression_qm;
    Object indexed_attribute_expression_found_qm, temp, form, op;
    Object attribute_quantifier, attribute_role, attribute_domain_qm;
    Object expression_qm;
    char temp_1;

    x_note_fn_call(147,181);
    operator_qm = CONSP(expression) ? FIRST(expression) : Nil;
    if (EQ(operator_qm,Qthere_exists_literal) || EQ(operator_qm,Qcount)) {
	gensymed_symbol = expression;
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol_1);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	var_spot_or_symbol = CAR(gensymed_symbol_1);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	domain_qm = CAR(gensymed_symbol_1);
	logical_expression = CAR(gensymed_symbol);
	if (CONSP(logical_expression)) {
	    logical_expression_list_qm = EQ(FIRST(logical_expression),
		    Qand) ? CDR(logical_expression) : Nil;
	    if (logical_expression_list_qm)
		possible_equality_expression_qm = 
			CAR(logical_expression_list_qm);
	    else if (EQ(FIRST(logical_expression),Qab_or))
		possible_equality_expression_qm = Nil;
	    else
		possible_equality_expression_qm = logical_expression;
	    indexed_attribute_expression_found_qm = Nil;
	  next_loop:
	    if ( !TRUEP(possible_equality_expression_qm))
		goto end_loop;
	    if (CONSP(possible_equality_expression_qm)) {
		temp = SECOND(possible_equality_expression_qm);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		form = SECOND(possible_equality_expression_qm);
		temp_1 = ATOM(form) ? form && SYMBOLP(form) : 
			TRUEP(designation_operator_or_giver_of_value_p(CAR(form)));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		gensymed_symbol = possible_equality_expression_qm;
		op = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		gensymed_symbol_1 = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		attribute_quantifier = CAR(gensymed_symbol_1);
		gensymed_symbol_1 = CDR(gensymed_symbol_1);
		attribute_role = CAR(gensymed_symbol_1);
		gensymed_symbol_1 = CDR(gensymed_symbol_1);
		attribute_domain_qm = CAR(gensymed_symbol_1);
		expression_qm = gensymed_symbol;
		if ((EQ(op,Qnum_eq) || EQ(op,Qis)) && 
			EQ(attribute_quantifier,Qthe) && 
			(SYMBOLP(attribute_role) || CONSP(attribute_role) 
			&& EQ(M_CAR(attribute_role),
			Qclass_qualified_name)) &&  !TRUEP(domain_qm)) {
		    if (SYMBOLP(role)) {
			temp_1 = EQ(attribute_domain_qm,role);
			if (temp_1);
			else
			    temp_1 = EQ(attribute_domain_qm,
				    var_spot_or_symbol);
			if (temp_1);
			else
			    temp_1 = CONSP(attribute_domain_qm) && 
				    EQ(CAR(attribute_domain_qm),Qthe) && 
				    CDR(attribute_domain_qm) &&  
				    !TRUEP(CDDR(attribute_domain_qm)) ? 
				    EQ(SECOND(attribute_domain_qm),role) : 
				    TRUEP(Qnil);
		    }
		    else {
			if (CONSP(role)) {
			    temp = simple_role_of_role(role);
			    temp_1 = SYMBOLP(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1) {
			    temp = CDR(role);
			    temp_1 = ATOM(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
			temp_1 = temp_1 ? EQ(attribute_domain_qm,
				CAR(role)) || EQ(attribute_domain_qm,
				CDR(role)) || CONSP(attribute_domain_qm) 
				&& EQ(CAR(attribute_domain_qm),Qthe) && 
				CDR(attribute_domain_qm) &&  
				!TRUEP(CDDR(attribute_domain_qm)) && 
				EQ(SECOND(attribute_domain_qm),CAR(role)) :
				 TRUEP(Nil);
		    }
		}
		else
		    temp_1 = TRUEP(Nil);
		if ((temp_1 ?  ! !TRUEP(expression_qm) : TRUEP(Nil)) ? 
			TRUEP(attribute_role) : TRUEP(Nil))
		    indexed_attribute_expression_found_qm = T;
	    }
	    logical_expression_list_qm = CDR(logical_expression_list_qm);
	    if (indexed_attribute_expression_found_qm)
		goto end_loop;
	    possible_equality_expression_qm = logical_expression_list_qm ? 
		    CAR(logical_expression_list_qm) : Nil;
	    goto next_loop;
	  end_loop:
	    if (indexed_attribute_expression_found_qm)
		return VALUES_1(possible_equality_expression_qm);
	    else
		return VALUES_1(Nil);
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-INDEXED-ATTRIBUTE-PROPERTIES */
Object update_indexed_attribute_properties(definition,
	    remove_old_indexed_attributes_if_necessary_qm,
	    old_indexed_attributes_if_different_qm,
	    old_class_name_if_different_qm)
    Object definition, remove_old_indexed_attributes_if_necessary_qm;
    Object old_indexed_attributes_if_different_qm;
    Object old_class_name_if_different_qm;
{
    Object current_class_name_qm, current_indexed_attributes_qm;
    Object old_class_name_qm, old_indexed_attributes_qm;
    Object test_if_old_indexed_attribute_is_still_defined_qm;
    Object any_class_instances_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp, temp_1, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, thing;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,182);
    current_class_name_qm = ISVREF(definition,(SI_Long)20L);
    current_indexed_attributes_qm = 
	    get_lookup_slot_value_given_default(definition,
	    Qindexed_attributes_for_definition,Nil);
    old_class_name_qm = old_class_name_if_different_qm;
    if (old_class_name_qm);
    else
	old_class_name_qm = current_class_name_qm;
    old_indexed_attributes_qm = old_indexed_attributes_if_different_qm;
    if (old_indexed_attributes_qm);
    else
	old_indexed_attributes_qm = current_indexed_attributes_qm;
    test_if_old_indexed_attribute_is_still_defined_qm = 
	    remove_old_indexed_attributes_if_necessary_qm && 
	    current_class_name_qm && current_indexed_attributes_qm ? 
	    (EQ(old_class_name_qm,current_class_name_qm) ? T : Nil) : Qnil;
    any_class_instances_qm = Nil;
    if (current_class_name_qm) {
	if (SYMBOLP(current_class_name_qm)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = current_class_name_qm;
	    key_hash_value = SXHASH_SYMBOL_1(current_class_name_qm) & 
		    IFIX(Most_positive_fixnum);
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
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = current_class_name_qm;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_5;
	  end_loop_4:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_4;
	  end_loop_5:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_7;
	      end_loop_8:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_10;
	      end_loop_11:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_9;
	      end_loop_9:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	thing = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(current_class_name_qm);
	next_loop_12:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_13:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_12;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_12;
	      goto next_loop_13;
	    end_loop_12:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_13;
	  thing = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  any_class_instances_qm = T;
	  if (any_class_instances_qm)
	      goto end_loop_13;
	  goto next_loop_12;
	end_loop_13:;
	POP_SPECIAL();
    }
    if ( !TRUEP(any_class_instances_qm) && old_class_name_qm) {
	if (SYMBOLP(old_class_name_qm)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = old_class_name_qm;
	    key_hash_value = SXHASH_SYMBOL_1(old_class_name_qm) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_14:
	    if (level < ab_loop_bind_)
		goto end_loop_14;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_15:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_16:
	    if ( !TRUEP(marked))
		goto end_loop_15;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_16;
	  end_loop_15:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_15;
	  end_loop_16:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_14;
	  end_loop_14:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = old_class_name_qm;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    svref_arg_1 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			svref_arg_1 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(svref_arg_1,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_17:
	    if (level < ab_loop_bind_)
		goto end_loop_17;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_18:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_19:
	    if ( !TRUEP(marked))
		goto end_loop_18;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_19;
	  end_loop_18:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_18;
	  end_loop_19:
	  end_6:
	    level = level - (SI_Long)1L;
	    goto next_loop_17;
	  end_loop_17:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_20:
		if (level < ab_loop_bind_)
		    goto end_loop_20;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_21:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_22:
		if ( !TRUEP(marked))
		    goto end_loop_21;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_22;
	      end_loop_21:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_21;
	      end_loop_22:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_20;
	      end_loop_20:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_23:
		if (level < ab_loop_bind_)
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_24:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_25:
		if ( !TRUEP(marked))
		    goto end_loop_24;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_25;
	      end_loop_24:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_24;
	      end_loop_25:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_23;
	      end_loop_23:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	thing = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(old_class_name_qm);
	next_loop_26:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_27:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_26;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_26;
	      goto next_loop_27;
	    end_loop_26:
	      temp_2 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_2 = TRUEP(Nil);
	  if (temp_2)
	      goto end_loop_27;
	  thing = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  any_class_instances_qm = T;
	  if (any_class_instances_qm)
	      goto end_loop_27;
	  goto next_loop_26;
	end_loop_27:;
	POP_SPECIAL();
    }
    if (remove_old_indexed_attributes_if_necessary_qm && 
	    old_indexed_attributes_qm && old_class_name_qm)
	remove_indexed_attribute_properties(old_indexed_attributes_qm,
		old_class_name_qm,
		test_if_old_indexed_attribute_is_still_defined_qm ? 
		current_indexed_attributes_qm : Nil,Loading_kb_p || 
		Currently_automatically_resolving_class_name_conflicts_qm ?
		 Nil : any_class_instances_qm);
    if (current_class_name_qm && current_indexed_attributes_qm)
	add_indexed_attribute_properties(current_indexed_attributes_qm,
		current_class_name_qm,Loading_kb_p || 
		Currently_automatically_resolving_class_name_conflicts_qm ?
		 Nil : any_class_instances_qm,T);
    return VALUES_1(Nil);
}

static Object Qany;                /* any */

static Object Qhandle_update_to_indexed_attribute;  /* handle-update-to-indexed-attribute */

/* REMOVE-INDEXED-ATTRIBUTE-PROPERTIES */
Object remove_indexed_attribute_properties(indexed_attribute_to_remove,
	    class_name,indexed_attributes_to_keep_qm,
	    update_hash_table_if_necessary_qm)
    Object indexed_attribute_to_remove, class_name;
    Object indexed_attributes_to_keep_qm, update_hash_table_if_necessary_qm;
{
    Object indexed_attribute, ab_loop_list_, indexed_attribute_classes_qm;
    Object update_designation;

    x_note_fn_call(147,183);
    indexed_attribute = Nil;
    ab_loop_list_ = indexed_attribute_to_remove;
    indexed_attribute_classes_qm = Nil;
    update_designation = gensym_list_3(Qthe,Nil,gensym_list_2(Qany,
	    class_name));
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    indexed_attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    indexed_attribute_classes_qm = 
	    lookup_kb_specific_property_value(indexed_attribute,
	    Indexed_attribute_classes_kbprop);
    if (memq_function(class_name,indexed_attribute_classes_qm) && ( 
	    !TRUEP(indexed_attributes_to_keep_qm) ||  
	    !TRUEP(memq_function(indexed_attribute,
	    indexed_attributes_to_keep_qm)))) {
	M_SECOND(update_designation) = indexed_attribute;
	install_true_value_update(Qhandle_update_to_indexed_attribute,Nil,
		Nil,update_designation,Nil);
	indexed_attribute_classes_qm = delete_gensym_element_1(class_name,
		indexed_attribute_classes_qm);
	mutate_kb_specific_property_value(indexed_attribute,
		indexed_attribute_classes_qm,Indexed_attribute_classes_kbprop);
	if ( !TRUEP(indexed_attribute_classes_qm))
	    Indexed_attributes = delete_gensym_element_1(indexed_attribute,
		    Indexed_attributes);
	if (update_hash_table_if_necessary_qm && 
		lookup_kb_specific_property_value(indexed_attribute,
		Indexed_attribute_hash_table_kbprop)) {
	    reclaim_indexed_attribute_hash_table(indexed_attribute);
	    if (indexed_attribute_classes_qm) {
		make_indexed_attribute_hash_table(indexed_attribute);
		update_indexed_attribute_hash_table(indexed_attribute);
	    }
	}
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_tree_1(update_designation);
    return VALUES_1(Nil);
}

/* ADD-INDEXED-ATTRIBUTE-PROPERTIES */
Object add_indexed_attribute_properties(indexed_attributes_to_add,
	    class_name,update_hash_table_if_necessary_qm,
	    updates_apply_to_existing_attributes_also_qm)
    Object indexed_attributes_to_add, class_name;
    Object update_hash_table_if_necessary_qm;
    Object updates_apply_to_existing_attributes_also_qm;
{
    Object indexed_attribute, ab_loop_list_, indexed_attribute_classes_qm;
    Object attribute_added_p_qm, update_designation;

    x_note_fn_call(147,184);
    indexed_attribute = Nil;
    ab_loop_list_ = indexed_attributes_to_add;
    indexed_attribute_classes_qm = Nil;
    attribute_added_p_qm = Nil;
    update_designation = gensym_list_3(Qthe,Nil,gensym_list_2(Qany,
	    class_name));
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    indexed_attribute = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    indexed_attribute_classes_qm = 
	    lookup_kb_specific_property_value(indexed_attribute,
	    Indexed_attribute_classes_kbprop);
    attribute_added_p_qm = Nil;
    if ( !TRUEP(memq_function(class_name,indexed_attribute_classes_qm))) {
	attribute_added_p_qm = T;
	M_SECOND(update_designation) = indexed_attribute;
	install_true_value_update(Qhandle_update_to_indexed_attribute,Nil,
		Nil,Nil,update_designation);
	indexed_attribute_classes_qm = gensym_cons_1(class_name,
		indexed_attribute_classes_qm);
	mutate_kb_specific_property_value(indexed_attribute,
		indexed_attribute_classes_qm,Indexed_attribute_classes_kbprop);
	if ( !TRUEP(memq_function(indexed_attribute,Indexed_attributes)))
	    Indexed_attributes = gensym_cons_1(indexed_attribute,
		    Indexed_attributes);
    }
    if ((attribute_added_p_qm || 
	    updates_apply_to_existing_attributes_also_qm) && 
	    (System_has_paused || System_is_running)) {
	if (update_hash_table_if_necessary_qm) {
	    if (lookup_kb_specific_property_value(indexed_attribute,
		    Indexed_attribute_hash_table_kbprop))
		reclaim_indexed_attribute_hash_table(indexed_attribute);
	    make_indexed_attribute_hash_table(indexed_attribute);
	    update_indexed_attribute_hash_table(indexed_attribute);
	}
	else if ( 
		!TRUEP(lookup_kb_specific_property_value(indexed_attribute,
		Indexed_attribute_hash_table_kbprop)))
	    make_indexed_attribute_hash_table(indexed_attribute);
	else;
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_tree_1(update_designation);
    return VALUES_1(Nil);
}

/* HANDLE-UPDATE-TO-INDEXED-ATTRIBUTE */
Object handle_update_to_indexed_attribute(ignored_frame,
	    ignored_extra_argument,changed_frame,attribute_name_qm,
	    old_value,defining_class_if_attribute_name_is_provided)
    Object ignored_frame, ignored_extra_argument, changed_frame;
    Object attribute_name_qm, old_value;
    Object defining_class_if_attribute_name_is_provided;
{
    Object item, temp, temp_1;

    x_note_fn_call(147,185);
    if ( !TRUEP(attribute_name_qm)) {
	item = get_lookup_slot_value_given_default(changed_frame,
		Qparent_frame,Nil);
	if ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & (SI_Long)64L)) {
	    temp = 
		    get_pretty_slot_name_for_parent_attribute_if_any(changed_frame);
	    temp_1 = 
		    get_defining_class_for_parent_attribute_if_any(changed_frame);
	    return put_parent_if_indexed_attribute(temp,temp_1,
		    changed_frame,old_value,
		    get_lookup_slot_value_given_default(changed_frame,
		    Qparent_frame,Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else if ((SI_Long)0L != (IFIX(ISVREF(changed_frame,(SI_Long)5L)) & 
	    (SI_Long)64L))
	return put_parent_if_indexed_attribute(attribute_name_qm,
		defining_class_if_attribute_name_is_provided,
		get_slot_value_function(changed_frame,attribute_name_qm,
		defining_class_if_attribute_name_is_provided),old_value,
		changed_frame);
    else
	return VALUES_1(Nil);
}

static Object Quuid;               /* uuid */

static Object Qunique_identification;  /* unique-identification */

static Object string_constant_28;  /* "The attribute ~a and value ~NV are not indexed for the class ~
				    *           ~a.  No items will be added to the item-list ~NF."
				    */

/* INSERT-INDEXED-ATTRIBUTE-ITEMS-IN-LIST */
Object insert_indexed_attribute_items_in_list(indexed_item_list,class_name,
	    attribute_name,attribute_value)
    Object indexed_item_list, class_name, attribute_name, attribute_value;
{
    Object class_1, class_description, attribute, attribute_value_value;
    Object indexed_attribute_value_qm, indexed_attribute_table_qm, temp_1;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp_2;
    Object entry_hash, parent_and_class_tree_qm, empty_list_p_qm, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol_1, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object item, class_list, ab_less_than_branch_qm_, defining_class;
    Object ab_loop_list_, sub_class_bit_vector, slot_description_qm;
    Object defining_class_of_attribute_qm, item_or_item_list, top_of_stack;
    Object message_1;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,186);
    class_1 = class_name;
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    attribute = attribute_name;
    attribute_value_value = evaluation_value_value(attribute_value);
    indexed_attribute_value_qm = 
	    indexed_attribute_or_inherited_attribute_for_class_p(attribute,
	    class_1) ? 
	    get_and_validate_indexed_attribute_value(attribute_value_value) 
	    : Qnil;
    indexed_attribute_table_qm = 
	    lookup_kb_specific_property_value(attribute,
	    Indexed_attribute_hash_table_kbprop);
    if (indexed_attribute_value_qm && indexed_attribute_table_qm) {
	if (FIXNUMP(indexed_attribute_value_qm))
	    gensymed_symbol = IFIX(FIXNUM_ABS(indexed_attribute_value_qm));
	else if (SYMBOLP(indexed_attribute_value_qm))
	    gensymed_symbol = SXHASH_SYMBOL_1(indexed_attribute_value_qm) 
		    & IFIX(Most_positive_fixnum);
	else if (text_string_p(indexed_attribute_value_qm))
	    gensymed_symbol = 
		    IFIX(compute_text_hash_code(indexed_attribute_value_qm));
	else
	    gensymed_symbol = (SI_Long)0L;
	temp = gensymed_symbol % (SI_Long)43L;
	temp_1 = SVREF(indexed_attribute_table_qm,FIX(temp));
	skip_list = CDR(temp_1);
	key_value = indexed_attribute_value_qm;
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  
		!TRUEP(evaluation_value_equal_p(key_value,ISVREF(curr,
		(SI_Long)2L)))) {
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
	parent_and_class_tree_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (evaluation_value_equal_p(key_value,
		ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
		Nil) : Nil;
	empty_list_p_qm = g2_list_empty_p(indexed_item_list);
	if (parent_and_class_tree_qm && class_description) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = parent_and_class_tree_qm;
	    ab_binary_tree_form_ = parent_and_class_tree_qm;
	    gensymed_symbol_1 = CDR(parent_and_class_tree_qm);
	    if (CONSP(gensymed_symbol_1)) {
		temp_1 = M_CAR(gensymed_symbol_1);
		temp_3 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		temp_1 = M_CDR(gensymed_symbol_1);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    class_list = Nil;
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
	    next_loop_3:
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
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
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
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      item = CAR(ab_entry_cons_);
	      class_list = CDR(ab_entry_cons_);
	      defining_class = Nil;
	      ab_loop_list_ = class_list;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_5;
	      defining_class = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_1 = ISVREF(item,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		  temp_3 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3) {
		  slot_description_qm = 
			  get_slot_description_of_class_description_function(attribute_name,
			  ISVREF(item,(SI_Long)1L),Nil);
		  defining_class_of_attribute_qm = slot_description_qm ? 
			  ISVREF(slot_description_qm,(SI_Long)3L) : Nil;
		  if (EQ(defining_class_of_attribute_qm,defining_class))
		      g2_list_insert_at_end(3,item,indexed_item_list,
			      empty_list_p_qm);
	      }
	      goto next_loop_5;
	    end_loop_5:;
	      goto next_loop_3;
	    end_loop_4:;
	    POP_SPECIAL();
	}
    }
    else {
	if (EQ(attribute,Quuid) && class_description) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qunique_identification,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3 ? TRUEP(text_string_p(attribute_value)) : TRUEP(Nil)) {
	    item_or_item_list = 
		    get_item_or_item_list_for_uuid(attribute_value);
	    empty_list_p_qm = g2_list_empty_p(indexed_item_list);
	    if ( !TRUEP(item_or_item_list));
	    else if (ATOM(item_or_item_list)) {
		gensymed_symbol_1 = ISVREF(item_or_item_list,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3)
		    g2_list_insert_at_end(3,item_or_item_list,
			    indexed_item_list,empty_list_p_qm);
	    }
	    else {
		item = Nil;
		ab_loop_list_ = item_or_item_list;
	      next_loop_6:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_6;
		item = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol_1 = ISVREF(item,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3)
		    g2_list_insert_at_end(3,item,indexed_item_list,
			    empty_list_p_qm);
		goto next_loop_6;
	      end_loop_6:;
	    }
	}
	else {
	    reclaim_evaluation_value(attribute_value);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(5,
		    string_constant_28,attribute,attribute_value,class_1,
		    indexed_item_list);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    return reclaim_evaluation_value(attribute_value);
}

static Object string_constant_29;  /* "The system procedure p-get-item-of-class-by-attribute-value is only available in G2 Enterprise" */

static Object Qitem_not_found;     /* item-not-found */

static Object string_constant_30;  /* "The attribute ~a and value ~NV are not indexed for the class ~
				    *           ~a.  No items will be found."
				    */

/* P-GET-ITEM-OF-CLASS-BY-ATTRIBUTE-VALUE */
Object p_get_item_of_class_by_attribute_value(class_name,attribute_name,
	    attribute_value)
    Object class_name, attribute_name, attribute_value;
{
    Object top_of_stack, message_1, class_1, class_description, attribute;
    Object attribute_value_value, indexed_attribute_value_qm;
    Object indexed_attribute_table_qm, item_or_not_found, temp_1, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object parent_and_class_tree_qm, scope_conses, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_binary_tree_form_;
    Object gensymed_symbol_1, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, item, class_list;
    Object ab_less_than_branch_qm_, defining_class, ab_loop_list_;
    Object sub_class_bit_vector, slot_description_qm;
    Object defining_class_of_attribute_qm, item_or_item_list;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_3;
    Declare_special(1);
    Object result;

    x_note_fn_call(147,187);
    if ( !TRUEP(g2_enterprise_p())) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_29);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    class_1 = class_name;
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    attribute = attribute_name;
    attribute_value_value = evaluation_value_value(attribute_value);
    indexed_attribute_value_qm = 
	    indexed_attribute_or_inherited_attribute_for_class_p(attribute,
	    class_1) ? 
	    get_and_validate_indexed_attribute_value(attribute_value_value) 
	    : Qnil;
    indexed_attribute_table_qm = 
	    lookup_kb_specific_property_value(attribute,
	    Indexed_attribute_hash_table_kbprop);
    item_or_not_found = Qitem_not_found;
    if (indexed_attribute_value_qm && indexed_attribute_table_qm) {
	if (FIXNUMP(indexed_attribute_value_qm))
	    gensymed_symbol = IFIX(FIXNUM_ABS(indexed_attribute_value_qm));
	else if (SYMBOLP(indexed_attribute_value_qm))
	    gensymed_symbol = SXHASH_SYMBOL_1(indexed_attribute_value_qm) 
		    & IFIX(Most_positive_fixnum);
	else if (text_string_p(indexed_attribute_value_qm))
	    gensymed_symbol = 
		    IFIX(compute_text_hash_code(indexed_attribute_value_qm));
	else
	    gensymed_symbol = (SI_Long)0L;
	temp = gensymed_symbol % (SI_Long)43L;
	temp_1 = SVREF(indexed_attribute_table_qm,FIX(temp));
	skip_list = CDR(temp_1);
	key_value = indexed_attribute_value_qm;
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
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  
		!TRUEP(evaluation_value_equal_p(key_value,ISVREF(curr,
		(SI_Long)2L)))) {
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
	parent_and_class_tree_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (evaluation_value_equal_p(key_value,
		ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
		Nil) : Nil;
	if (parent_and_class_tree_qm && class_description) {
	    scope_conses = Scope_conses;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_skip_list_form_ = parent_and_class_tree_qm;
	    ab_binary_tree_form_ = parent_and_class_tree_qm;
	    gensymed_symbol_1 = CDR(parent_and_class_tree_qm);
	    if (CONSP(gensymed_symbol_1)) {
		temp_1 = M_CAR(gensymed_symbol_1);
		temp_3 = SIMPLE_VECTOR_P(temp_1);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		temp_1 = M_CDR(gensymed_symbol_1);
		ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	    }
	    else
		ab_skip_list_p_ = Nil;
	    ab_next_node_ = Nil;
	    ab_tail_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    item = Nil;
	    class_list = Nil;
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
	    next_loop_3:
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
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
		  }
		  else
		      ab_current_node_ = Nil;
	      }
	      else {
		  if (ab_next_node_) {
		      ab_current_node_ = ab_next_node_;
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_4:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_3;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_4;
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
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_4;
	      item = CAR(ab_entry_cons_);
	      class_list = CDR(ab_entry_cons_);
	      defining_class = Nil;
	      ab_loop_list_ = class_list;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_5;
	      defining_class = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol_1 = ISVREF(item,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		  temp_3 = (SI_Long)0L < gensymed_symbol;
	      }
	      else
		  temp_3 = TRUEP(Nil);
	      if (temp_3) {
		  slot_description_qm = 
			  get_slot_description_of_class_description_function(attribute_name,
			  ISVREF(item,(SI_Long)1L),Nil);
		  defining_class_of_attribute_qm = slot_description_qm ? 
			  ISVREF(slot_description_qm,(SI_Long)3L) : Nil;
		  if (EQ(defining_class_of_attribute_qm,defining_class)) {
		      item_or_not_found = item;
		      goto end_loop_5;
		  }
	      }
	      goto next_loop_5;
	    end_loop_5:;
	      if ( !EQ(item_or_not_found,Qitem_not_found))
		  goto end_loop_4;
	      goto next_loop_3;
	    end_loop_4:;
	    POP_SPECIAL();
	}
    }
    else {
	if (EQ(attribute,Quuid) && class_description) {
	    gensymed_symbol_1 = 
		    lookup_global_or_kb_specific_property_value(Qunique_identification,
		    Class_description_gkbprop);
	    if (gensymed_symbol_1) {
		sub_class_bit_vector = ISVREF(class_description,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3 ? TRUEP(text_string_p(attribute_value)) : TRUEP(Nil)) {
	    item_or_item_list = 
		    get_item_or_item_list_for_uuid(attribute_value);
	    if ( !TRUEP(item_or_item_list));
	    else if (ATOM(item_or_item_list)) {
		gensymed_symbol_1 = ISVREF(item_or_item_list,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3)
		    item_or_not_found = item_or_item_list;
	    }
	    else {
		item = Nil;
		ab_loop_list_ = item_or_item_list;
	      next_loop_6:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_6;
		item = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		gensymed_symbol_1 = ISVREF(item,(SI_Long)1L);
		sub_class_bit_vector = ISVREF(gensymed_symbol_1,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_2 = (SI_Long)1L;
		    gensymed_symbol_3 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_2;
		    temp_3 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3) {
		    item_or_not_found = item;
		    goto end_loop_6;
		}
		goto next_loop_6;
	      end_loop_6:;
	    }
	}
	else {
	    reclaim_evaluation_value(attribute_value);
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_30,attribute,attribute_value,class_1);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    reclaim_evaluation_value(attribute_value);
    return VALUES_1(item_or_not_found);
}

void variables_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_simulation_info_1;
    Object reclaim_structure_for_variable_simulation_runtime_structure_1;
    Object reclaim_structure_for_data_server_1;
    Object reclaim_structure_for_formula_invocation_1;
    Object reclaim_structure_for_inference_background_collection_1;
    Object gensymed_symbol;
    Object Qp_get_item_of_class_by_attribute_value, AB_package;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qinsert_indexed_attribute_items_in_list;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qmutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry;
    Object Qout_indexed_attribute_parent_objects_hash_vector_43_vectors;
    Object Qindexed_attribute_parent_objects_hash_vector_43_vector_memory_usage;
    Object string_constant_241, Qutilities2;
    Object Qmutate_indexed_attribute_defining_classes_skip_list_entry;
    Object Qvariables, Qindexed_attribute_classes;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qindexed_attribute_hash_table, Qclasses_which_define;
    Object Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_parameter;
    Object Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_parameter;
    Object Qdeactivate_subclass_of_entity_for_variable;
    Object Qinference_background_collection, Qreclaim_structure;
    Object Qoutstanding_inference_background_collection_count;
    Object Qinference_background_collection_structure_memory_usage;
    Object string_constant_240, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_239, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object Qactivate_subclass_of_entity_for_variable;
    Object Qmutate_items_needing_initialization_skip_list_entry;
    Object Qdenote_cell_array_element;
    Object Qdenote_cell_array_element_for_generic_formula, list_constant_11;
    Object Qdenote_cell_array_element_for_variable, Qexpression_cell_updated;
    Object Qexpression_cell_updated_for_generic_formula;
    Object Qexpression_cell_updated_for_variable;
    Object Qclear_currently_evaluating_formula_after_bombout;
    Object Qformula_invocation, Qoutstanding_formula_invocation_count;
    Object Qformula_invocation_structure_memory_usage, string_constant_238;
    Object string_constant_237, Qslot_putter, Qput_data_server_aliases;
    Object Qslot_value_writer, Qwrite_data_server_aliases_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_data_server_aliases_for_slot;
    Object Qput_g2_meter_data_service_on_qm, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_data_server_parameters;
    Object Qinstall_system_table;
    Object Qinstall_system_table_for_data_server_parameters;
    Object string_constant_236, string_constant_235;
    Object Qsimplify_associative_operation, Qg2_meter_data_service_on;
    Object Qgsi_data_server_filters_text, Qgsi_data_server_filters_text_qm;
    Object Qabsent_slot_putter;
    Object Qput_priority_of_continued_data_service_where_slot_is_absent;
    Object Qpriority_of_continued_data_service, Ksystem_frame;
    Object string_constant_234, list_constant_10, string_constant_233;
    Object string_constant_232, string_constant_231, Qsystem_table;
    Object Qput_data_server_map, Qcopy_data_servers_for_process, Qdata_server;
    Object Qoutstanding_data_server_count, Qdata_server_structure_memory_usage;
    Object string_constant_230, string_constant_229, string_constant_228;
    Object list_constant_9, Kfuncall, Qdata_server_or_alias_qm;
    Object Qvariable_simulation_runtime_structure;
    Object Qoutstanding_variable_simulation_runtime_structure_count;
    Object Qvariable_simulation_runtime_structure_structure_memory_usage;
    Object string_constant_227, string_constant_226, Qsimulation_info;
    Object Qoutstanding_simulation_info_count;
    Object Qsimulation_info_structure_memory_usage, string_constant_225;
    Object string_constant_224;
    Object Qput_last_time_value_sent_to_inference_engine_where_slot_is_absent;
    Object Qlast_time_value_sent_to_inference_engine;
    Object Qput_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent;
    Object Qinterval_at_which_to_send_value_to_inference_engine;
    Object Qput_time_of_next_update_where_slot_is_absent, Qtime_of_next_update;
    Object Qput_k4_value_where_slot_is_absent, Qk4_value;
    Object Qput_k3_value_where_slot_is_absent, Qk3_value;
    Object Qput_k2_value_where_slot_is_absent, Qk2_value;
    Object Qput_k1_value_where_slot_is_absent, Qk1_value;
    Object Qput_new_simulation_value_step_where_slot_is_absent;
    Object Qnew_simulation_value_step;
    Object Qput_new_simulation_value_time_where_slot_is_absent;
    Object Qnew_simulation_value_time;
    Object Qput_new_simulation_value_where_slot_is_absent;
    Object Qnew_simulation_value;
    Object Qput_simulation_value_time_where_slot_is_absent;
    Object Qsimulation_value_time, Qput_simulation_value_where_slot_is_absent;
    Object Qsimulation_value;
    Object Qput_initial_value_for_simulation_qm_where_slot_is_absent;
    Object Qinitial_value_for_simulation_qm;
    Object Qput_simulation_class_where_slot_is_absent, Qsimulation_class;
    Object Qsimulation_subtable, string_constant_223, string_constant_222;
    Object list_constant_8, string_constant_221, string_constant_220;
    Object string_constant_219, string_constant_218, string_constant_217;
    Object string_constant_216, string_constant_215, Qitem;
    Object Qsubstitute_class_and_kb_flags, Qsimulation_frame, Qtext_parameter;
    Object string_constant_214, string_constant_213, string_constant_212;
    Object string_constant_211, list_constant_6, Qcreate_icon_description;
    Object string_constant_210, string_constant_209, string_constant_208;
    Object string_constant_207, string_constant_206, string_constant_205;
    Object string_constant_155, string_constant_204, string_constant_203;
    Object Qsymbolic_parameter, string_constant_202, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_198;
    Object string_constant_197, string_constant_196, string_constant_195;
    Object string_constant_194, Qfloat_parameter, string_constant_193;
    Object string_constant_192, string_constant_191, list_constant_7;
    Object string_constant_190, string_constant_189, string_constant_188;
    Object string_constant_187, array_constant_6, string_constant_186;
    Object Qlong_parameter, Qint64_parameter, string_constant_185;
    Object string_constant_184, string_constant_160, string_constant_183;
    Object string_constant_182, string_constant_181, string_constant_180;
    Object Qinteger_parameter, string_constant_179, string_constant_178;
    Object string_constant_177, string_constant_176, string_constant_175;
    Object string_constant_174, string_constant_173, Qquantitative_parameter;
    Object string_constant_172, string_constant_171, string_constant_170;
    Object string_constant_169, string_constant_168, string_constant_167;
    Object string_constant_166, string_constant_165, string_constant_164;
    Object Qlogical_parameter, string_constant_163, string_constant_162;
    Object string_constant_161, string_constant_159, string_constant_158;
    Object string_constant_157, string_constant_156, string_constant_154;
    Object string_constant_153, Qinitialize, Qinitialize_for_parameter;
    Object Qput_initial_value_of_variable_or_parameter, string_constant_152;
    Object list_constant_2, string_constant_151, string_constant_79;
    Object string_constant_150, string_constant_149, Qput_formula_qm;
    Object Qput_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent;
    Object Qrule_to_invoke_when_sensor_fails_qm;
    Object Qput_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent;
    Object Qrule_to_invoke_when_value_arrives_qm, string_constant_148;
    Object string_constant_147, list_constant_3, Qsensor, string_constant_146;
    Object string_constant_145, string_constant_144, string_constant_143;
    Object string_constant_142, Qtext_variable, string_constant_141;
    Object string_constant_140, string_constant_139, string_constant_138;
    Object list_constant_4, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object Qsymbolic_variable, string_constant_129, string_constant_128;
    Object string_constant_127, string_constant_126, string_constant_125;
    Object string_constant_124, string_constant_123, string_constant_122;
    Object string_constant_121, Qlong_variable, Qint64_variable;
    Object string_constant_120, string_constant_119, list_constant_5;
    Object string_constant_118, string_constant_117, string_constant_116;
    Object string_constant_115, string_constant_114, string_constant_113;
    Object Qinteger_variable, string_constant_112, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object Qfloat_variable, string_constant_104, string_constant_103;
    Object string_constant_102, string_constant_101, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, Qquantitative_variable, string_constant_95;
    Object string_constant_94, string_constant_93, string_constant_92;
    Object string_constant_91, string_constant_90, string_constant_89;
    Object string_constant_88, Qlogical_variable, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_78, string_constant_77;
    Object Qg2_variable, string_constant_76, string_constant_75;
    Object string_constant_74, Qcleanup, Qcleanup_for_object;
    Object Qcleanup_for_parameter, Qcleanup_for_variable;
    Object Qhistory_keeping_spec_for_simulation_subtables;
    Object Qhistory_specification_for_simulation_subtables_qm;
    Object Qput_simulation_frame_qm_where_slot_is_absent, Qsimulation_frame_qm;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, Qinitial_value;
    Object Qput_variable_stored_history_specification_qm_where_slot_is_absent;
    Object Qvariable_stored_history_specification_qm;
    Object Qput_data_type_of_variable_where_slot_is_absent;
    Object Qdata_type_of_variable, Qput_data_type_of_variable_or_parameter;
    Object Qput_formula_specified_time_increment_for_update_qm_where_slot_is_absent;
    Object Qformula_specified_time_increment_for_update_qm;
    Object Qput_initial_simulated_value_qm_where_slot_is_absent;
    Object Qinitial_simulated_value_qm;
    Object Qput_simulation_category_qm_where_slot_is_absent;
    Object Qsimulation_category_qm, Qinitialize_for_variable_or_parameter;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_variable_or_parameter;
    Object Qslot_value_reclaimer;
    Object Qreclaim_g2_internal_cached_explanation_value, string_constant_57;
    Object string_constant_56, string_constant_55, list_constant_1;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, Qgeneric_simulation_formula, string_constant_47;
    Object string_constant_37, string_constant_46, list_constant;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_33;
    Object string_constant_40, string_constant_39;
    Object Qcleanup_for_generic_formula, Qinitialize_for_generic_formula;
    Object Qput_generic_formula_byte_code_body_where_slot_is_absent;
    Object Qgeneric_formula_byte_code_body, string_constant_38;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_32, string_constant_31, Qstatement;
    Object Qsimulation_formula_for_attribute, Qformula_for_attribute;
    Object Qformula_statement, Qformulas_for_this_role;

    x_note_fn_call(147,188);
    SET_PACKAGE("AB");
    if (Stack_eval_qm == UNBOUND)
	Stack_eval_qm = T;
    AB_package = STATIC_PACKAGE("AB");
    Qformulas_for_this_role = STATIC_SYMBOL("FORMULAS-FOR-THIS-ROLE",
	    AB_package);
    Kb_specific_property_names = CONS(Qformulas_for_this_role,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qformulas_for_this_role,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Formulas_for_this_role_kbprop = Qformulas_for_this_role;
    Qformula_statement = STATIC_SYMBOL("FORMULA-STATEMENT",AB_package);
    Qgeneric_formula = STATIC_SYMBOL("GENERIC-FORMULA",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qformula_statement,CONS(Qgeneric_formula,temp),
	    Qsubstitute_class_and_kb_flags);
    Qformula_for_attribute = STATIC_SYMBOL("FORMULA-FOR-ATTRIBUTE",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qformula_for_attribute,CONS(Qgeneric_formula,
	    temp),Qsubstitute_class_and_kb_flags);
    Qsimulation_formula_for_attribute = 
	    STATIC_SYMBOL("SIMULATION-FORMULA-FOR-ATTRIBUTE",AB_package);
    Qgeneric_simulation_formula = 
	    STATIC_SYMBOL("GENERIC-SIMULATION-FORMULA",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qsimulation_formula_for_attribute,
	    CONS(Qgeneric_simulation_formula,temp),
	    Qsubstitute_class_and_kb_flags);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qgeneric_formula,list_constant);
    string_constant_31 = STATIC_STRING("1m1m8v836wy1l8t");
    string_constant_32 = 
	    STATIC_STRING("1n4z8r83--y83--y836wy836wy00001p1l8l1m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date. ");
    string_constant_33 = 
	    STATIC_STRING("~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n1l83Ey1l83Uy00");
    string_constant_34 = 
	    STATIC_STRING("0004z8r83-0y83-0y836wy836wy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_35 = 
	    STATIC_STRING("ion is available at this time)000004z8r83ry83ry836wy836wy00001p1n8p836wy83Gy1l8o1l8l1l83-5y1l83-3y00000");
    string_constant_36 = 
	    STATIC_STRING("1p8q1o836wy1l83*ry1m8v836wy8t1o83--y01m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date.");
    string_constant_37 = 
	    STATIC_STRING(" ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n1n83-0y01m8p8");
    string_constant_38 = STATIC_STRING("3-0y1q83ry01n8p836wy83Gy8o8l83-5y");
    temp = regenerate_optimized_constant(string_constant_31);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_32,
	    string_constant_33,string_constant_34,string_constant_35));
    add_class_to_environment(9,Qgeneric_formula,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,
	    regenerate_optimized_constant(LIST_3(string_constant_36,
	    string_constant_37,string_constant_38)),Nil);
    Generic_formula_class_description = 
	    lookup_global_or_kb_specific_property_value(Qgeneric_formula,
	    Class_description_gkbprop);
    Qgeneric_formula_byte_code_body = 
	    STATIC_SYMBOL("GENERIC-FORMULA-BYTE-CODE-BODY",AB_package);
    Qput_generic_formula_byte_code_body_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-GENERIC-FORMULA-BYTE-CODE-BODY-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_generic_formula_byte_code_body_where_slot_is_absent,
	    STATIC_FUNCTION(put_generic_formula_byte_code_body_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qgeneric_formula_byte_code_body,
	    SYMBOL_FUNCTION(Qput_generic_formula_byte_code_body_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qinitialize_for_generic_formula = 
	    STATIC_SYMBOL("INITIALIZE-FOR-GENERIC-FORMULA",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_generic_formula,
	    STATIC_FUNCTION(initialize_for_generic_formula,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_generic_formula);
    set_get(Qgeneric_formula,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_formula,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qcleanup_for_generic_formula = 
	    STATIC_SYMBOL("CLEANUP-FOR-GENERIC-FORMULA",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_generic_formula,
	    STATIC_FUNCTION(cleanup_for_generic_formula,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_generic_formula);
    set_get(Qgeneric_formula,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_formula,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    check_if_superior_classes_are_defined(Qgeneric_simulation_formula,
	    list_constant);
    string_constant_39 = STATIC_STRING("1m1m8v835Ty1l8t");
    string_constant_40 = 
	    STATIC_STRING("1q4z8r83--y83--y835Ty835Ty00001p1l8l1m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date. ");
    string_constant_41 = 
	    STATIC_STRING("0004z8r83-0y83-0y835Ty835Ty00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_42 = 
	    STATIC_STRING("ion is available at this time)000004z8r83ry83ry835Ty835Ty00001p1n8p835Ty83Gy1l8o1l8l1l83-5y1l83-3y000004z8r83-py83-py835Ty835Ty0");
    string_constant_43 = 
	    STATIC_STRING("0001q1l8l1l83Ey1l83Cy1m8p83-py1l8z1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or ");
    string_constant_44 = 
	    STATIC_STRING("default &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]000004z8r83Q=y83Q=y835Ty835Ty00001n1l8l1l8o1l83Cy0000");
    string_constant_45 = 
	    STATIC_STRING("04z8r83Q0y83Q0y835Ty835Ty00001n1l8l1l8o1l83Cy00000");
    string_constant_46 = 
	    STATIC_STRING("1s8q1o835Ty1l83*ry1m8v835Ty8t1o83--y01m8p83-*y1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date.");
    string_constant_47 = 
	    STATIC_STRING("3-0y1q83ry01n8p835Ty83Gy8o8l83-5y1q83-py08l83Ey83Cy1m8p83-py1o83Q=y08o83Cy1o83Q0y08o83Cy");
    temp = regenerate_optimized_constant(string_constant_39);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_40,
	    string_constant_33,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45));
    add_class_to_environment(9,Qgeneric_simulation_formula,list_constant,
	    Nil,temp,Nil,temp_1,list_constant,
	    regenerate_optimized_constant(LIST_3(string_constant_46,
	    string_constant_37,string_constant_47)),Nil);
    Generic_simulation_formula_class_description = 
	    lookup_global_or_kb_specific_property_value(Qgeneric_simulation_formula,
	    Class_description_gkbprop);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_1 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qvariable_or_parameter,
	    list_constant_1);
    string_constant_48 = STATIC_STRING("1p1m8v830Cy1l8t1l83-8y1l83Iy1l83Ly");
    string_constant_49 = 
	    STATIC_STRING("1t4z8r83-Iy83-Iy830Cy830Cy00001n1l8o1l8l1m8p831ry000004z8r83-py83-py830Cy830Cy00001q1l8l1l8z1l83Ey1l83Cy1m8p83-py1m83Dy53*Qy[war");
    string_constant_50 = 
	    STATIC_STRING("ning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;), ~\nbreakpoint-level: (or");
    string_constant_51 = 
	    STATIC_STRING(" default &lt;integer&gt;)]000004z8r83c1y83c1y830Cy830Cy03RtKe+z001n1l8o1l8l1m83Dy5rExport\?000004z8r83-Ky83-Ky830Cy830Cy00001p1l8");
    string_constant_52 = 
	    STATIC_STRING("o1l8z1l8l1l83Cy1m83Dy5qExport000004z8r83J0y83J0y830Cy830Cy00001p1l8o1l8l1m8p83b9y1l83Fy1l83Hy000004z8r83doy83doy830Cy830Cy00001n");
    string_constant_53 = 
	    STATIC_STRING("1l8o1l8l1m83Dy5yExport: Struct000004z8r83Fqy83Fqy830Cy830Cy00001p1m8p830hy1l8o1l8z1l8l1m83Dy5yExport: Struct000004z8r83aAy83aAy8");
    string_constant_54 = 
	    STATIC_STRING("30Cy830Cy00001n1l83Ey1l8l1m83Dy53CyPossible export.000004z8r83N*y83N*y830Cy830Cy00001o1l83Ey1l8l1l83Hy1m83Dy5tInternal.00000");
    string_constant_55 = 
	    STATIC_STRING("1v8q1r830Cy1l83-Oy1m8v830Cy8t83-8y83Iy83Ly1p83-Iy08o8l1m8p831ry1r83-py08l8z83Ey83Cy1m8p83-py1p83c1y3RtKe+z8o8l1m83Dy5rExport\?1r8");
    string_constant_56 = 
	    STATIC_STRING("3-Ky08o8z8l83Cy1m83Dy5qExport1r83J0y08o8l1m8p83b9y83Fy83Hy1p83doy08o8l1m83Dy5yExport: Struct1r83Fqy01m8p830hy8o8z8l1m83Dy5yExpor");
    string_constant_57 = 
	    STATIC_STRING("t: Struct1p83aAy083Ey8l1m83Dy53CyPossible export.1q83N*y083Ey8l83Hy1m83Dy5tInternal.");
    temp = regenerate_optimized_constant(string_constant_48);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_49,
	    string_constant_50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54));
    add_class_to_environment(9,Qvariable_or_parameter,list_constant_1,Nil,
	    temp,Nil,temp_1,list_constant_1,
	    regenerate_optimized_constant(LIST_3(string_constant_55,
	    string_constant_56,string_constant_57)),Nil);
    Variable_or_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qvariable_or_parameter,
	    Class_description_gkbprop);
    Qg2_internal_cached_explanation = 
	    STATIC_SYMBOL("G2-INTERNAL-CACHED-EXPLANATION",AB_package);
    Qreclaim_g2_internal_cached_explanation_value = 
	    STATIC_SYMBOL("RECLAIM-G2-INTERNAL-CACHED-EXPLANATION-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_internal_cached_explanation_value,
	    STATIC_FUNCTION(reclaim_g2_internal_cached_explanation_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qg2_internal_cached_explanation,
	    SYMBOL_FUNCTION(Qreclaim_g2_internal_cached_explanation_value),
	    Qslot_value_reclaimer);
    Qinitialize_after_reading_for_variable_or_parameter = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_variable_or_parameter,
	    STATIC_FUNCTION(initialize_after_reading_for_variable_or_parameter,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_variable_or_parameter);
    set_get(Qvariable_or_parameter,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable_or_parameter,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qinitialize_for_variable_or_parameter = 
	    STATIC_SYMBOL("INITIALIZE-FOR-VARIABLE-OR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_variable_or_parameter,
	    STATIC_FUNCTION(initialize_for_variable_or_parameter,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_variable_or_parameter);
    set_get(Qvariable_or_parameter,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable_or_parameter,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qsimulation_category_qm = STATIC_SYMBOL("SIMULATION-CATEGORY\?",
	    AB_package);
    Qput_simulation_category_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-CATEGORY\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_category_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_category_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_category_qm,
	    SYMBOL_FUNCTION(Qput_simulation_category_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitial_simulated_value_qm = 
	    STATIC_SYMBOL("INITIAL-SIMULATED-VALUE\?",AB_package);
    Qput_initial_simulated_value_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-INITIAL-SIMULATED-VALUE\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_initial_simulated_value_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_initial_simulated_value_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinitial_simulated_value_qm,
	    SYMBOL_FUNCTION(Qput_initial_simulated_value_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qformula_specified_time_increment_for_update_qm = 
	    STATIC_SYMBOL("FORMULA-SPECIFIED-TIME-INCREMENT-FOR-UPDATE\?",
	    AB_package);
    Qput_formula_specified_time_increment_for_update_qm_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-FORMULA-SPECIFIED-TIME-INCREMENT-FOR-UPDATE\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_formula_specified_time_increment_for_update_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_formula_specified_time_increment_for_update_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qformula_specified_time_increment_for_update_qm,
	    SYMBOL_FUNCTION(Qput_formula_specified_time_increment_for_update_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qdata_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qput_data_type_of_variable_or_parameter = 
	    STATIC_SYMBOL("PUT-DATA-TYPE-OF-VARIABLE-OR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_type_of_variable_or_parameter,
	    STATIC_FUNCTION(put_data_type_of_variable_or_parameter,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qdata_type_of_variable_or_parameter,
	    SYMBOL_FUNCTION(Qput_data_type_of_variable_or_parameter),
	    Qslot_putter);
    Qdata_type_of_variable = STATIC_SYMBOL("DATA-TYPE-OF-VARIABLE",AB_package);
    Qput_data_type_of_variable_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-DATA-TYPE-OF-VARIABLE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_type_of_variable_where_slot_is_absent,
	    STATIC_FUNCTION(put_data_type_of_variable_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdata_type_of_variable,
	    SYMBOL_FUNCTION(Qput_data_type_of_variable_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qvariable_or_parameter_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-OR-PARAMETER-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qvariable_stored_history_specification_qm = 
	    STATIC_SYMBOL("VARIABLE-STORED-HISTORY-SPECIFICATION\?",
	    AB_package);
    Qput_variable_stored_history_specification_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-VARIABLE-STORED-HISTORY-SPECIFICATION\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_variable_stored_history_specification_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_variable_stored_history_specification_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qvariable_stored_history_specification_qm,
	    SYMBOL_FUNCTION(Qput_variable_stored_history_specification_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    alias_slot_name(3,Qinitial_value_of_variable_or_parameter,
	    Qinitial_value,Qnil);
    list_constant_2 = STATIC_CONS(Qvariable_or_parameter,Qnil);
    check_if_superior_classes_are_defined(Qvariable,list_constant_2);
    string_constant_58 = 
	    STATIC_STRING("1q1l8t1l83-8y1l83Iy1l83Ly1m8v83*dy1m83-Cy53hyExport computation style and history info, etc.");
    string_constant_59 = 
	    STATIC_STRING("13Hy4z8r83-Ey83-Ey83*dy83*dy0k001r1l8l1l8o1l8z1m8p83*Ey1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I ");
    string_constant_60 = 
	    STATIC_STRING("think individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be su");
    string_constant_61 = 
	    STATIC_STRING("pported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83Kqy83Kqy83*dy83*dy03RtKe+z001");
    string_constant_62 = 
	    STATIC_STRING("m1l8o1l8l000004z8r830uy830uy83*dy83*dy00001o1l8o1l8l1l8z1m8p830uy000004z8r831xy831xy83*dy83*dy00001o1l8o1l8l1n8p83D-y83Gy1l83-5y");
    string_constant_63 = 
	    STATIC_STRING("000004z8r83c3y83c3y83*dy83*dy00001m1l8o1l8l000004z8r83bXy83bXy83*dy83*dy00001m1l8o1l8l000004z8r837Py837Py83*dy83*dy00001q1l83Ey1");
    string_constant_64 = 
	    STATIC_STRING("l8l1l8z1m8p83a9y1l83Fy1m83=dy832Ly000004z8r83Cfy83Cfy83*dy83*dy00001p1l83Ey1l8l1l8z1m8p830hy1l83Ny000004z8r83WWy83WWy83*dy83*dy0");
    string_constant_65 = 
	    STATIC_STRING("0001n1m8p83E1y1l83Ey1l8l000004z8r83*My83*My83*dy83*dy083BLy001o1l8o1l8l1l8z1m8p83*My000004z8r83Auy83Auy83*dy83*dy00001o1l8o1l8l1");
    string_constant_66 = 
	    STATIC_STRING("l8z1m8p832gy000004z8r83b+y83b+y83*dy83*dy00001m1l8o1l8l000004z8r83M+y83M+y83*dy83*dy00001m1l8o1l8l000004z8r83boy83boy83*dy83*dy0");
    string_constant_67 = 
	    STATIC_STRING("0001m1l8o1l8l000004z8r83bmy83bmy83*dy83*dy00001m1l8o1l8l000004z8r83bRy83bRy83*dy83*dy00001m1l8o1l8l000004z8r83bly83bly83*dy83*dy");
    string_constant_68 = 
	    STATIC_STRING("00001m1l8o1l8l000004z8r83bPy83bPy83*dy83*dy00001m1l8o1l8l000004z8r83bQy83bQy83*dy83*dy00001m1l8o1l8l000004z8r83H=y83H=y83*dy83*d");
    string_constant_69 = 
	    STATIC_STRING("y00001m1l8l1l8o000004z8r83H0y83H0y83*dy83*dy00001m1l8l1l8o00000");
    string_constant_70 = 
	    STATIC_STRING("13Jy8q1s83*dy1l830Cy8t83-8y83Iy83Ly1m8v83*dy1m83-Cy53hyExport computation style and history info, etc.1q83-Eyk8l8o8z1m8p83*Ey1o8");
    string_constant_71 = 
	    STATIC_STRING("3Kqy3RtKe+z8o8l1q830uy08o8l8z1m8p830uy1q831xy08o8l1n8p83D-y83Gy83-5y1o83c3y08o8l1o83bXy08o8l1s837Py083Ey8l8z1m8p83a9y83Fy1m83=dy");
    string_constant_72 = 
	    STATIC_STRING("832Ly1r83Cfy083Ey8l8z1m8p830hy83Ny1p83WWy01m8p83E1y83Ey8l1q83*My83BLy8o8l8z1m8p83*My1q83Auy08o8l8z1m8p832gy1o83b+y08o8l1o83M+y08");
    string_constant_73 = 
	    STATIC_STRING("o8l1o83boy08o8l1o83bmy08o8l1o83bRy08o8l1o83bly08o8l1o83bPy08o8l1o83bQy08o8l1o83H=y08l8o1o83H0y08l8o");
    temp = regenerate_optimized_constant(string_constant_58);
    temp_1 = regenerate_optimized_constant(list(11,string_constant_59,
	    string_constant_60,string_constant_61,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69));
    add_class_to_environment(9,Qvariable,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(LIST_4(string_constant_70,
	    string_constant_71,string_constant_72,string_constant_73)),Nil);
    Variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qvariable,
	    Class_description_gkbprop);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qsimulation_frame_qm = STATIC_SYMBOL("SIMULATION-FRAME\?",AB_package);
    Qput_simulation_frame_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-FRAME\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_frame_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_frame_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_frame_qm,
	    SYMBOL_FUNCTION(Qput_simulation_frame_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qdata_server_map = STATIC_SYMBOL("DATA-SERVER-MAP",AB_package);
    Qdata_server = STATIC_SYMBOL("DATA-SERVER",AB_package);
    alias_slot_name(3,Qdata_server_map,Qdata_server,Qnil);
    Qhistory_specification_for_simulation_subtables_qm = 
	    STATIC_SYMBOL("HISTORY-SPECIFICATION-FOR-SIMULATION-SUBTABLES\?",
	    AB_package);
    Qhistory_keeping_spec_for_simulation_subtables = 
	    STATIC_SYMBOL("HISTORY-KEEPING-SPEC-FOR-SIMULATION-SUBTABLES",
	    AB_package);
    alias_slot_name(3,Qhistory_specification_for_simulation_subtables_qm,
	    Qhistory_keeping_spec_for_simulation_subtables,Qnil);
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qcleanup_for_variable = STATIC_SYMBOL("CLEANUP-FOR-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_variable,
	    STATIC_FUNCTION(cleanup_for_variable,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_variable);
    set_get(Qvariable,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    Qcleanup_for_parameter = STATIC_SYMBOL("CLEANUP-FOR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_parameter,
	    STATIC_FUNCTION(cleanup_for_parameter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_parameter);
    set_get(Qparameter,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qparameter,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qcleanup_for_object = STATIC_SYMBOL("CLEANUP-FOR-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_object,
	    STATIC_FUNCTION(cleanup_for_object,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_object);
    set_get(Qobject,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qobject,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qg2_variable = STATIC_SYMBOL("G2-VARIABLE",AB_package);
    list_constant_3 = STATIC_CONS(Qvariable,Qnil);
    check_if_superior_classes_are_defined(Qg2_variable,list_constant_3);
    string_constant_74 = STATIC_STRING("1o1m8v831Hy1l8t1l83-8y1l83Iy");
    string_constant_75 = 
	    STATIC_STRING("1l4z8r830uy830uy831Hy831Hy083A3y001o1l8o1l8l1m8p830uy1l8z00000");
    string_constant_76 = 
	    STATIC_STRING("1n8q1q831Hy1l83*dy1m8v831Hy8t83-8y83Iy1p830uy83A3y8o8l1m8p830uy");
    temp = regenerate_optimized_constant(string_constant_74);
    temp_1 = regenerate_optimized_constant(string_constant_75);
    add_class_to_environment(9,Qg2_variable,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_76),Nil);
    Qlogical_variable = STATIC_SYMBOL("LOGICAL-VARIABLE",AB_package);
    list_constant_4 = STATIC_CONS(Qg2_variable,Qnil);
    check_if_superior_classes_are_defined(Qlogical_variable,list_constant_4);
    string_constant_77 = STATIC_STRING("1m1m8v834Ky1l8t");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_78 = 
	    STATIC_STRING("1p4z8r83-Ey83-Ey834Ky834Ky0m001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_79 = 
	    STATIC_STRING("ink individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be supp");
    string_constant_80 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834Ky834Ky083-hy001o1l8");
    string_constant_81 = 
	    STATIC_STRING("o1l8l1m8p8364y1l83Fy000004z8r83-Ky83-Ky834Ky834Ky00001q1l8o1l8l1m8p836Ny1l8z1l83Cy1m83Dy5qExport000004z8r831xy831xy834Ky834Ky000");
    string_constant_82 = 
	    STATIC_STRING("01o1l8o1l8l1n8p83DXy83Gy1l83-5y000004z8r8u8u834Ky834Ky01p8w9k3uy3uy1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1x83Jy1m3Dyt1m3dyt1m3dy3Ty1m3");
    string_constant_83 = 
	    STATIC_STRING("Ty3Ty1m3Ty3cy1m3Ny3cy1m3Ny3Ny1m3Wy3Ny1m3Wyz1m3Kyz1m3Ky3Hy1m3Dy3Hy1p83Jy1m3Ny3iy1m3Ty3iy1m3Ty3oy1m3Ny3oy001o1l8l1l8o1l8z1m83Dy53Y");
    string_constant_84 = 
	    STATIC_STRING("ySee comment on ENTITY class definition00000");
    string_constant_85 = 
	    STATIC_STRING("1r8q1o834Ky1l831Hy1m8v834Ky8t1p83-Eym8l8o1m8p83*Ey1q83-Iy83-hy8o8l1m8p8364y83Fy1p83-Ky08o8l1m8p836Ny1q831xy08o8l1n8p83DXy83Gy83-");
    string_constant_86 = 
	    STATIC_STRING("5y1m8u1p8w9k3uy3uy1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1x83Jy1m3Dyt1m3dyt1m3dy3Ty1m3Ty3Ty1m3Ty3cy1m3Ny3cy1m3Ny3Ny1m3Wy3Ny1m3Wyz1m3Kyz");
    string_constant_87 = 
	    STATIC_STRING("1m3Ky3Hy1m3Dy3Hy1p83Jy1m3Ny3iy1m3Ty3iy1m3Ty3oy1m3Ny3oy");
    temp = regenerate_optimized_constant(string_constant_77);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_78,
	    string_constant_79,string_constant_80,string_constant_81,
	    string_constant_82,string_constant_83,string_constant_84));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qlogical_variable,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_3(string_constant_85,
	    string_constant_86,string_constant_87)),Nil);
    Logical_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qlogical_variable,
	    Class_description_gkbprop);
    Qquantitative_variable = STATIC_SYMBOL("QUANTITATIVE-VARIABLE",AB_package);
    check_if_superior_classes_are_defined(Qquantitative_variable,
	    list_constant_4);
    string_constant_88 = STATIC_STRING("1m1m8v8315y1l8t");
    string_constant_89 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey8315y8315y0k001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_90 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy8315y8315y083-Hy001o1l8");
    string_constant_91 = 
	    STATIC_STRING("o1l8l1m8p832Fy1l8z000004z8r83-Ky83-Ky8315y8315y00001q1l8o1l8l1m8p837Iy1l8z1l83Cy1m83Dy5qExport000004z8r8u8u8315y8315y01p8w9k3uy3");
    string_constant_92 = 
	    STATIC_STRING("uy1o1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1o83Oy1mk3Qy1m83*Hy1mzz1m3Qy3Qy1o83Oy1m3Qy3Qy1m83*Hy1m3fy3fy1m3uy3Qy001o1l");
    string_constant_93 = 
	    STATIC_STRING("8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_94 = 
	    STATIC_STRING("1q8q1o8315y1l831Hy1m8v8315y8t1p83-Eyk8l8o1m8p83*Ey1q83-Iy83-Hy8o8l1m8p832Fy8z1p83-Ky08o8l1m8p837Iy1m8u1p8w9k3uy3uy1o1p83Jy1mkk1m");
    string_constant_95 = 
	    STATIC_STRING("3uyk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1o83Oy1mk3Qy1m83*Hy1mzz1m3Qy3Qy1o83Oy1m3Qy3Qy1m83*Hy1m3fy3fy1m3uy3Qy");
    temp = regenerate_optimized_constant(string_constant_88);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_89,
	    string_constant_79,string_constant_90,string_constant_91,
	    string_constant_92,string_constant_93));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qquantitative_variable,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_2(string_constant_94,
	    string_constant_95)),Nil);
    Quantitative_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qquantitative_variable,
	    Class_description_gkbprop);
    Qfloat_variable = STATIC_SYMBOL("FLOAT-VARIABLE",AB_package);
    list_constant_5 = STATIC_CONS(Qquantitative_variable,Qnil);
    check_if_superior_classes_are_defined(Qfloat_variable,list_constant_5);
    string_constant_96 = STATIC_STRING("1m1m8v834-y1l8t");
    string_constant_97 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834-y834-y0k001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_98 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834-y834-y09k001o1l8o1l");
    string_constant_99 = 
	    STATIC_STRING("8l1m8p833xy1l8z000004z8r83-Ky83-Ky834-y834-y00001q1l8o1l8l1m8p8370y1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834-y834-y01p8w9l3uy3uy1");
    string_constant_100 = 
	    STATIC_STRING("n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1u83Oy1mm3Qy1m83*Hy1mt3Jy1m3Cy3Qy1m83*Hy1m3Jy3Xy1m3Qy3Qy1m83*Hy1m3Xy3Jy1m3ey3");
    string_constant_101 = 
	    STATIC_STRING("Qy1m83*Hy1m3ly3Xy1m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_102 = 
	    STATIC_STRING("1q8q1o834-y1l8315y1m8v834-y8t1p83-Eyk8l8o1m8p83*Ey1p83-Iy9k8o8l1m8p833xy1p83-Ky08o8l1m8p8370y1m8u1p8w9l3uy3uy1n1p83Jy1mkk1m3uyk1");
    string_constant_103 = 
	    STATIC_STRING("m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1u83Oy1mm3Qy1m83*Hy1mt3Jy1m3Cy3Qy1m83*Hy1m3Jy3Xy1m3Qy3Qy1m83*Hy1m3Xy3Jy1m3ey3Qy1m83*Hy1m3ly3Xy1");
    string_constant_104 = STATIC_STRING("m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_96);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_97,
	    string_constant_79,string_constant_98,string_constant_99,
	    string_constant_100,string_constant_101));
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qfloat_variable,list_constant_5,Nil,temp,
	    Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_3(string_constant_102,
	    string_constant_103,string_constant_104)),Nil);
    Float_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qfloat_variable,
	    Class_description_gkbprop);
    Qinteger_variable = STATIC_SYMBOL("INTEGER-VARIABLE",AB_package);
    check_if_superior_classes_are_defined(Qinteger_variable,list_constant_5);
    string_constant_105 = STATIC_STRING("1m1m8v834Ey1l8t");
    string_constant_106 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834Ey834Ey0k001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_107 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834Ey834Ey083Sy001o1l8o");
    string_constant_108 = 
	    STATIC_STRING("1l8l1m8p834Cy1l8z000004z8r83-Ky83-Ky834Ey834Ey00001q1l8o1l8l1m8p8372y1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834Ey834Ey01p8w9k3uy3u");
    string_constant_109 = 
	    STATIC_STRING("y1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1");
    string_constant_110 = 
	    STATIC_STRING("m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_111 = 
	    STATIC_STRING("1q8q1o834Ey1l8315y1m8v834Ey8t1p83-Eyk8l8o1m8p83*Ey1p83-Iy83Sy8o8l1m8p834Cy1p83-Ky08o8l1m8p8372y1m8u1p8w9k3uy3uy1n1p83Jy1mkk1m3uy");
    string_constant_112 = 
	    STATIC_STRING("k1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_105);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_106,
	    string_constant_79,string_constant_107,string_constant_108,
	    string_constant_109,string_constant_110));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qinteger_variable,list_constant_5,Nil,temp,
	    Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_111,
	    string_constant_112)),Nil);
    Integer_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinteger_variable,
	    Class_description_gkbprop);
    Qlong_variable = STATIC_SYMBOL("LONG-VARIABLE",AB_package);
    check_if_superior_classes_are_defined(Qlong_variable,list_constant_5);
    string_constant_113 = STATIC_STRING("1m1m8v835iy1l8t");
    string_constant_114 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey835iy835iy0k001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_115 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy835iy835iy083=By001o1l8");
    string_constant_116 = 
	    STATIC_STRING("o1l8l1m8p834Ly1l8z000004z8r83-Ky83-Ky835iy835iy00001q1l8o1l8l1m8p8374y1l8z1l83Cy1m83Dy5qExport000004z8r8u8u835iy835iy01p8w9k3uy3");
    string_constant_117 = 
	    STATIC_STRING("uy1n1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy");
    string_constant_118 = 
	    STATIC_STRING("1m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_119 = 
	    STATIC_STRING("1q8q1o835iy1l8315y1m8v835iy8t1p83-Eyk8l8o1m8p83*Ey1p83-Iy83=By8o8l1m8p834Ly1p83-Ky08o8l1m8p8374y1m8u1p8w9k3uy3uy1n1p83Jy1mkk1m3u");
    string_constant_120 = 
	    STATIC_STRING("yk1m3uy3uy1mk3uy1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_113);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_114,
	    string_constant_79,string_constant_115,string_constant_116,
	    string_constant_117,string_constant_118));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qlong_variable,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_119,
	    string_constant_120)),Nil);
    Long_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qlong_variable,
	    Class_description_gkbprop);
    Qint64_variable = STATIC_SYMBOL("INT64-VARIABLE",AB_package);
    temp = add1(G2_version_2011_kb_flags);
    mutate_global_property(Qint64_variable,CONS(Qlong_variable,temp),
	    Qsubstitute_class_and_kb_flags);
    Qsymbolic_variable = STATIC_SYMBOL("SYMBOLIC-VARIABLE",AB_package);
    check_if_superior_classes_are_defined(Qsymbolic_variable,list_constant_4);
    string_constant_121 = STATIC_STRING("1m1m8v834fy1l8t");
    string_constant_122 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834fy834fy0m001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_123 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834fy834fy083-2y001o1l8");
    string_constant_124 = 
	    STATIC_STRING("o1l8l1m8p8362y1l83Fy000004z8r83-Ky83-Ky834fy834fy00001q1l8o1l8l1m8p837Sy1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834fy834fy01p8w9k3u");
    string_constant_125 = 
	    STATIC_STRING("y3uy1o1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1p83Jy1m3Kyq1m3Wyq1m3Wy3Ey1m3Ky3Ey1p83Jy1m3Ky3Ky1m3Wy3Ky1m3Wy3Wy1m3Ky3Wy1p83Jy1m3Ky3cy1m3Wy3");
    string_constant_126 = 
	    STATIC_STRING("cy1m3Wy3oy1m3Ky3oy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_127 = 
	    STATIC_STRING("1q8q1o834fy1l831Hy1m8v834fy8t1p83-Eym8l8o1m8p83*Ey1q83-Iy83-2y8o8l1m8p8362y83Fy1p83-Ky08o8l1m8p837Sy1m8u1p8w9k3uy3uy1o1p83Jy1mkk");
    string_constant_128 = 
	    STATIC_STRING("1m3uyk1m3uy3uy1mk3uy1p83Jy1m3Kyq1m3Wyq1m3Wy3Ey1m3Ky3Ey1p83Jy1m3Ky3Ky1m3Wy3Ky1m3Wy3Wy1m3Ky3Wy1p83Jy1m3Ky3cy1m3Wy3cy1m3Wy3oy1m3Ky3");
    string_constant_129 = STATIC_STRING("oy");
    temp = regenerate_optimized_constant(string_constant_121);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_122,
	    string_constant_79,string_constant_123,string_constant_124,
	    string_constant_125,string_constant_126));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qsymbolic_variable,list_constant_4,Nil,temp,
	    Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_3(string_constant_127,
	    string_constant_128,string_constant_129)),Nil);
    Symbolic_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsymbolic_variable,
	    Class_description_gkbprop);
    Qtext_variable = STATIC_SYMBOL("TEXT-VARIABLE",AB_package);
    check_if_superior_classes_are_defined(Qtext_variable,list_constant_4);
    string_constant_130 = STATIC_STRING("1m1m8v834jy1l8t");
    string_constant_131 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834jy834jy0k001r1l8l1l8o1m8p83*Ey1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_132 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834jy834jy083Gy001o1l8o");
    string_constant_133 = 
	    STATIC_STRING("1l8l1m8p8363y1l83Fy000004z8r83-Ky83-Ky834jy834jy00001q1l8o1l8l1m8p83-xy1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834jy834jy01p8w9k3uy");
    string_constant_134 = 
	    STATIC_STRING("3uy1v1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mr3Qy1mr3Vy1n83Oy1mu3Qy1mu3Vy1n83Oy1m3jy3Qy1m3jy3Vy1n83Oy1m3my3Vy1m3my3Qy1p83Oy1m3Cy3a");
    string_constant_135 = 
	    STATIC_STRING("y1m3Cy3by1m3Dy3by1m3Dy3ay1p83Oy1m3Iy3ay1m3Iy3by1m3Jy3by1m3Jy3ay1p83Oy1m3Oy3ay1m3Oy3by1m3Py3by1m3Py3ay1p83Oy1m3Uy3ay1m3Uy3by1m3Vy");
    string_constant_136 = 
	    STATIC_STRING("3by1m3Vy3ay1p83Oy1m3ay3ay1m3ay3by1m3by3by1m3by3ay1p83Oy1m3gy3ay1m3gy3by1m3hy3by1m3hy3ay001o1l8l1l8o1l8z1m83Dy53YySee comment on ");
    string_constant_137 = STATIC_STRING("ENTITY class definition00000");
    string_constant_138 = 
	    STATIC_STRING("1q8q1o834jy1l831Hy1m8v834jy8t1p83-Eyk8l8o1m8p83*Ey1q83-Iy83Gy8o8l1m8p8363y83Fy1p83-Ky08o8l1m8p83-xy1m8u1p8w9k3uy3uy1v1p83Jy1mkk1");
    string_constant_139 = 
	    STATIC_STRING("m3uyk1m3uy3uy1mk3uy1n83Oy1mr3Qy1mr3Vy1n83Oy1mu3Qy1mu3Vy1n83Oy1m3jy3Qy1m3jy3Vy1n83Oy1m3my3Vy1m3my3Qy1p83Oy1m3Cy3ay1m3Cy3by1m3Dy3b");
    string_constant_140 = 
	    STATIC_STRING("y1m3Dy3ay1p83Oy1m3Iy3ay1m3Iy3by1m3Jy3by1m3Jy3ay1p83Oy1m3Oy3ay1m3Oy3by1m3Py3by1m3Py3ay1p83Oy1m3Uy3ay1m3Uy3by1m3Vy3by1m3Vy3ay1p83O");
    string_constant_141 = 
	    STATIC_STRING("y1m3ay3ay1m3ay3by1m3by3by1m3by3ay1p83Oy1m3gy3ay1m3gy3by1m3hy3by1m3hy3ay");
    temp = regenerate_optimized_constant(string_constant_130);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_131,
	    string_constant_79,string_constant_132,string_constant_133,
	    string_constant_134,string_constant_135,string_constant_136,
	    string_constant_137));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qtext_variable,list_constant_4,Nil,temp,Nil,
	    temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_4(string_constant_138,
	    string_constant_139,string_constant_140,string_constant_141)),Nil);
    Text_variable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtext_variable,
	    Class_description_gkbprop);
    Qsensor = STATIC_SYMBOL("SENSOR",AB_package);
    check_if_superior_classes_are_defined(Qsensor,list_constant_3);
    string_constant_142 = STATIC_STRING("1o1m8v834ay1l8t1l83Iy1l83Ly");
    string_constant_143 = 
	    STATIC_STRING("1q4z8r83-Iy83-Iy834ay834ay083-Hy001o1l8o1l8l1l8z1m8p831ry000004z8r83-Ky83-Ky834ay834ay00001q1l8o1l8l1m8p835Vy1l8z1l83Cy1m83Dy5qE");
    string_constant_144 = 
	    STATIC_STRING("xport000004z8r831xy831xy834ay834ay00001o1l8o1l8l1m8p01l83-5y000004z8r830uy830uy834ay834ay0832by001o1l8o1l8l1m8p834by1l8z000004z8");
    string_constant_145 = 
	    STATIC_STRING("r83*My83*My834ay834ay083F5y001o1l8o1l8l1m8p83*My1l8z000004z8r8u8u834ay834ay01p8w9k3Gy3Gy1m1o83*fy1mku1muk1m3Gyu1o83Oy1mro1mrz1mx");
    string_constant_146 = 
	    STATIC_STRING("z001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_147 = 
	    STATIC_STRING("1s8q1q834ay1l83*dy1m8v834ay8t83Iy83Ly1q83-Iy83-Hy8o8l8z1m8p831ry1p83-Ky08o8l1m8p835Vy1p831xy08o8l1m8p01p830uy832by8o8l1m8p834by1");
    string_constant_148 = 
	    STATIC_STRING("p83*My83F5y8o8l1m8p83*My1m8u1p8w9k3Gy3Gy1m1o83*fy1mku1muk1m3Gyu1o83Oy1mro1mrz1mxz");
    temp = regenerate_optimized_constant(string_constant_142);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_143,
	    string_constant_144,string_constant_145,string_constant_146));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qsensor,list_constant_3,Nil,temp,Nil,temp_1,
	    list_constant_3,
	    regenerate_optimized_constant(LIST_2(string_constant_147,
	    string_constant_148)),Nil);
    Qrule_to_invoke_when_value_arrives_qm = 
	    STATIC_SYMBOL("RULE-TO-INVOKE-WHEN-VALUE-ARRIVES\?",AB_package);
    Qput_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-RULE-TO-INVOKE-WHEN-VALUE-ARRIVES\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qrule_to_invoke_when_value_arrives_qm,
	    SYMBOL_FUNCTION(Qput_rule_to_invoke_when_value_arrives_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qrule_to_invoke_when_sensor_fails_qm = 
	    STATIC_SYMBOL("RULE-TO-INVOKE-WHEN-SENSOR-FAILS\?",AB_package);
    Qput_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-RULE-TO-INVOKE-WHEN-SENSOR-FAILS\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qrule_to_invoke_when_sensor_fails_qm,
	    SYMBOL_FUNCTION(Qput_rule_to_invoke_when_sensor_fails_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qformula_qm = STATIC_SYMBOL("FORMULA\?",AB_package);
    Qput_formula_qm = STATIC_SYMBOL("PUT-FORMULA\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_formula_qm,STATIC_FUNCTION(put_formula_qm,NIL,
	    FALSE,3,3));
    mutate_global_property(Qformula_qm,SYMBOL_FUNCTION(Qput_formula_qm),
	    Qslot_putter);
    check_if_superior_classes_are_defined(Qparameter,list_constant_2);
    string_constant_149 = STATIC_STRING("1o1m8v83=vy1l8t1l83-8y1l83Iy");
    string_constant_150 = 
	    STATIC_STRING("1l4z8r83-Ey83-Ey83=vy83=vy0k001r1l8l1l8o1l8z1m8p83=Cy1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I th");
    string_constant_151 = 
	    STATIC_STRING("orted. This\ncomment should show up on options, despite it being placed on frame-flags.00000");
    string_constant_152 = 
	    STATIC_STRING("1n8q1q83=vy1l830Cy1m8v83=vy8t83-8y83Iy1q83-Eyk8l8o8z1m8p83=Cy");
    temp = regenerate_optimized_constant(string_constant_149);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_150,
	    string_constant_79,string_constant_151));
    add_class_to_environment(9,Qparameter,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_152),Nil);
    Parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qparameter,
	    Class_description_gkbprop);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    string_constant = 
	    STATIC_STRING("The initial-value (~NV) of ~NF is not of the valid type (~NT) for this ~\n       class.  Changing value to ~NV, the default for class ~A.");
    Qput_initial_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("PUT-INITIAL-VALUE-OF-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_initial_value_of_variable_or_parameter,
	    STATIC_FUNCTION(put_initial_value_of_variable_or_parameter,NIL,
	    FALSE,3,3));
    mutate_global_property(Qinitial_value_of_variable_or_parameter,
	    SYMBOL_FUNCTION(Qput_initial_value_of_variable_or_parameter),
	    Qslot_putter);
    Qinitialize_for_parameter = STATIC_SYMBOL("INITIALIZE-FOR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_parameter,
	    STATIC_FUNCTION(initialize_for_parameter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_parameter);
    set_get(Qparameter,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qparameter,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qlogical_parameter = STATIC_SYMBOL("LOGICAL-PARAMETER",AB_package);
    list_constant_6 = STATIC_CONS(Qparameter,Qnil);
    check_if_superior_classes_are_defined(Qlogical_parameter,list_constant_6);
    string_constant_153 = STATIC_STRING("1m1m8v834Jy1l8t");
    string_constant_154 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834Jy834Jy034+Ey001r1l8l1l8o1m8p83=Cy1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. ");
    string_constant_155 = 
	    STATIC_STRING("I think individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be ");
    string_constant_156 = 
	    STATIC_STRING("supported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834Jy834Jy083-hy001");
    string_constant_157 = 
	    STATIC_STRING("o1l8o1l8l1m8p8364y1l83Fy000004z8r83-Ky83-Ky834Jy834Jy03Baz001q1l8o1l8l1m8p83-hy1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834Jy834Jy01");
    string_constant_158 = 
	    STATIC_STRING("p8w9k3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1x83Jy1m3Dyt1m3dyt1m3dy3Ty1m3Ty3Ty1m3Ty3cy1m3Ny3cy1m3Ny3Ny1m3");
    string_constant_159 = 
	    STATIC_STRING("Wy3Ny1m3Wyz1m3Kyz1m3Ky3Hy1m3Dy3Hy1p83Jy1m3Ny3iy1m3Ty3iy1m3Ty3oy1m3Ny3oy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class def");
    string_constant_160 = STATIC_STRING("inition00000");
    string_constant_161 = 
	    STATIC_STRING("1q8q1o834Jy1l83=vy1m8v834Jy8t1p83-Ey34+Ey8l8o1m8p83=Cy1q83-Iy83-hy8o8l1m8p8364y83Fy1p83-Ky3Baz8o8l1m8p83-hy1m8u1p8w9k3uy3uy1n1t8");
    string_constant_162 = 
	    STATIC_STRING("3Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1x83Jy1m3Dyt1m3dyt1m3dy3Ty1m3Ty3Ty1m3Ty3cy1m3Ny3cy1m3Ny3Ny1m3Wy3Ny1m3Wyz1m3Ky");
    string_constant_163 = 
	    STATIC_STRING("z1m3Ky3Hy1m3Dy3Hy1p83Jy1m3Ny3iy1m3Ty3iy1m3Ty3oy1m3Ny3oy");
    temp = regenerate_optimized_constant(string_constant_153);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_154,
	    string_constant_155,string_constant_156,string_constant_157,
	    string_constant_158,string_constant_159,string_constant_160));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qlogical_parameter,list_constant_6,Nil,temp,
	    Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_3(string_constant_161,
	    string_constant_162,string_constant_163)),Nil);
    Logical_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qlogical_parameter,
	    Class_description_gkbprop);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    check_if_superior_classes_are_defined(Qquantitative_parameter,
	    list_constant_6);
    string_constant_164 = STATIC_STRING("1m1m8v8314y1l8t");
    array_constant_6 = STATIC_ARRAY(Qdouble_float,(SI_Long)1L,
	    FIX((SI_Long)1L));
    DFLOAT_ISASET_1(array_constant_6,(SI_Long)0L,0.0);
    string_constant_165 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey8314y8314y034+Cy001r1l8l1l8o1m8p83=Cy1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. ");
    string_constant_166 = 
	    STATIC_STRING("supported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy8314y8314y083-Hy001");
    string_constant_167 = 
	    STATIC_STRING("o1l8o1l8l1m8p832Fy1l8z000004z8r83-Ky83-Ky8314y8314y09k001q1l8o1l8l1m8p830my1l8z1l83Cy1m83Dy5qExport000004z8r8u8u8314y8314y01p8w9");
    string_constant_168 = 
	    STATIC_STRING("l3uy3uy1o1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1o83Oy1mk3Qy1m83*Hy1mzz1m3Qy3Qy1o83Oy1m3Qy3Qy");
    string_constant_169 = 
	    STATIC_STRING("1m83*Hy1m3fy3fy1m3uy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    float_constant = STATIC_FLOAT(0.0);
    string_constant_170 = 
	    STATIC_STRING("1q8q1o8314y1l83=vy1m8v8314y8t1p83-Ey34+Cy8l8o1m8p83=Cy1q83-Iy83-Hy8o8l1m8p832Fy8z1p83-Ky9k8o8l1m8p830my1m8u1p8w9l3uy3uy1o1t83Jy1");
    string_constant_171 = 
	    STATIC_STRING("mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1o83Oy1mk3Qy1m83*Hy1mzz1m3Qy3Qy1o83Oy1m3Qy3Qy1m83*Hy1m3fy3fy1");
    string_constant_172 = STATIC_STRING("m3uy3Qy");
    temp = regenerate_optimized_constant(string_constant_164);
    clear_optimized_constants();
    push_optimized_constant(array_constant_6);
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_165,
	    string_constant_155,string_constant_166,string_constant_167,
	    string_constant_168,string_constant_169));
    clear_optimized_constants();
    push_optimized_constant(float_constant);
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qquantitative_parameter,list_constant_6,Nil,
	    temp,Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_3(string_constant_170,
	    string_constant_171,string_constant_172)),Nil);
    Quantitative_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qquantitative_parameter,
	    Class_description_gkbprop);
    Qinteger_parameter = STATIC_SYMBOL("INTEGER-PARAMETER",AB_package);
    list_constant_7 = STATIC_CONS(Qquantitative_parameter,Qnil);
    check_if_superior_classes_are_defined(Qinteger_parameter,list_constant_7);
    string_constant_173 = STATIC_STRING("1m1m8v834Dy1l8t");
    string_constant_174 = 
	    STATIC_STRING("1n4z8r83-Iy83-Iy834Dy834Dy083Sy001o1l8o1l8l1m8p834Cy1l8z000004z8r83-Ky83-Ky834Dy834Dy0k001q1l8o1l8l1m8p8371y1l8z1l83Cy1m83Dy5qEx");
    string_constant_175 = 
	    STATIC_STRING("port000004z8r8u8u834Dy834Dy01p8w9k3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy");
    string_constant_176 = 
	    STATIC_STRING("1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class defi");
    string_constant_177 = STATIC_STRING("nition00000");
    string_constant_178 = 
	    STATIC_STRING("1p8q1o834Dy1l8314y1m8v834Dy8t1p83-Iy83Sy8o8l1m8p834Cy1p83-Kyk8o8l1m8p8371y1m8u1p8w9k3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3");
    string_constant_179 = 
	    STATIC_STRING("uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_173);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_174,
	    string_constant_175,string_constant_176,string_constant_177));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qinteger_parameter,list_constant_7,Nil,temp,
	    Nil,temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_2(string_constant_178,
	    string_constant_179)),Nil);
    Integer_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinteger_parameter,
	    Class_description_gkbprop);
    Qlong_parameter = STATIC_SYMBOL("LONG-PARAMETER",AB_package);
    check_if_superior_classes_are_defined(Qlong_parameter,list_constant_7);
    string_constant_180 = STATIC_STRING("1m1m8v835hy1l8t");
    string_constant_181 = 
	    STATIC_STRING("1n4z8r83-Iy83-Iy835hy835hy083=By001o1l8o1l8l1m8p834Ly1l8z000004z8r83-Ky83-Ky835hy835hy0k001q1l8o1l8l1m8p8373y1l8z1l83Cy1m83Dy5qE");
    string_constant_182 = 
	    STATIC_STRING("xport000004z8r8u8u835hy835hy01p8w9k3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Q");
    string_constant_183 = 
	    STATIC_STRING("y1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class def");
    string_constant_184 = 
	    STATIC_STRING("1p8q1o835hy1l8314y1m8v835hy8t1p83-Iy83=By8o8l1m8p834Ly1p83-Kyk8o8l1m8p8373y1m8u1p8w9k3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy");
    string_constant_185 = 
	    STATIC_STRING("3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1v83Oy1mm3Qy1mm3Jy1m3Cy3Jy1m3Cy3Xy1m3Qy3Xy1m3Qy3Jy1m3ey3Jy1m3ey3Xy1m3sy3Xy1m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_180);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_181,
	    string_constant_182,string_constant_183,string_constant_160));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qlong_parameter,list_constant_7,Nil,temp,
	    Nil,temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_2(string_constant_184,
	    string_constant_185)),Nil);
    Qint64_parameter = STATIC_SYMBOL("INT64-PARAMETER",AB_package);
    temp = add1(G2_version_2011_kb_flags);
    mutate_global_property(Qint64_parameter,CONS(Qlong_parameter,temp),
	    Qsubstitute_class_and_kb_flags);
    Qfloat_parameter = STATIC_SYMBOL("FLOAT-PARAMETER",AB_package);
    check_if_superior_classes_are_defined(Qfloat_parameter,list_constant_7);
    string_constant_186 = STATIC_STRING("1m1m8v834+y1l8t");
    string_constant_187 = 
	    STATIC_STRING("1n4z8r83-Iy83-Iy834+y834+y09k001o1l8o1l8l1m8p833xy1l8z000004z8r83-Ky83-Ky834+y834+y09l001q1l8o1l8l1m8p837=y1l8z1l83Cy1m83Dy5qExp");
    string_constant_188 = 
	    STATIC_STRING("ort000004z8r8u8u834+y834+y01p8w9m3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1u83Oy1mm3Qy1");
    string_constant_189 = 
	    STATIC_STRING("m83*Hy1mt3Jy1m3Cy3Qy1m83*Hy1m3Jy3Xy1m3Qy3Qy1m83*Hy1m3Xy3Jy1m3ey3Qy1m83*Hy1m3ly3Xy1m3sy3Qy001o1l8l1l8o1l8z1m83Dy53YySee comment o");
    string_constant_190 = STATIC_STRING("n ENTITY class definition00000");
    string_constant_191 = 
	    STATIC_STRING("1p8q1o834+y1l8314y1m8v834+y8t1p83-Iy9k8o8l1m8p833xy1p83-Ky9l8o8l1m8p837=y1m8u1p8w9m3uy3uy1n1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3u");
    string_constant_192 = 
	    STATIC_STRING("y1mw3uy1mk3iy1mkw1n83Oy1mk3Qy1m3uy3Qy1u83Oy1mm3Qy1m83*Hy1mt3Jy1m3Cy3Qy1m83*Hy1m3Jy3Xy1m3Qy3Qy1m83*Hy1m3Xy3Jy1m3ey3Qy1m83*Hy1m3ly");
    string_constant_193 = STATIC_STRING("3Xy1m3sy3Qy");
    temp = regenerate_optimized_constant(string_constant_186);
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(array_constant_6);
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_187,
	    string_constant_188,string_constant_189,string_constant_190));
    clear_optimized_constants();
    push_optimized_constant(Qfloat);
    push_optimized_constant(float_constant);
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qfloat_parameter,list_constant_7,Nil,temp,
	    Nil,temp_1,list_constant_7,
	    regenerate_optimized_constant(LIST_3(string_constant_191,
	    string_constant_192,string_constant_193)),Nil);
    Float_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qfloat_parameter,
	    Class_description_gkbprop);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
    check_if_superior_classes_are_defined(Qsymbolic_parameter,list_constant_6);
    string_constant_194 = STATIC_STRING("1m1m8v834ey1l8t");
    string_constant_195 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834ey834ey034+Ey001r1l8l1l8o1m8p83=Cy1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. ");
    string_constant_196 = 
	    STATIC_STRING("supported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834ey834ey083-2y001");
    string_constant_197 = 
	    STATIC_STRING("o1l8o1l8l1m8p8362y1l83Fy000004z8r83-Ky83-Ky834ey834ey0830Jy001q1l8o1l8l1m8p830Ty1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834ey834ey0");
    string_constant_198 = 
	    STATIC_STRING("1p8w9k3uy3uy1o1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1p83Jy1m3Kyq1m3Wyq1m3Wy3Ey1m3Ky3Ey1p83Jy1m3Ky3Ky1m3Wy3Ky1m3W");
    string_constant_199 = 
	    STATIC_STRING("y3Wy1m3Ky3Wy1p83Jy1m3Ky3cy1m3Wy3cy1m3Wy3oy1m3Ky3oy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_200 = 
	    STATIC_STRING("1q8q1o834ey1l83=vy1m8v834ey8t1p83-Ey34+Ey8l8o1m8p83=Cy1q83-Iy83-2y8o8l1m8p8362y83Fy1p83-Ky830Jy8o8l1m8p830Ty1m8u1p8w9k3uy3uy1o1t");
    string_constant_201 = 
	    STATIC_STRING("83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1p83Jy1m3Kyq1m3Wyq1m3Wy3Ey1m3Ky3Ey1p83Jy1m3Ky3Ky1m3Wy3Ky1m3Wy3Wy1m3Ky3Wy1p83");
    string_constant_202 = STATIC_STRING("Jy1m3Ky3cy1m3Wy3cy1m3Wy3oy1m3Ky3oy");
    temp = regenerate_optimized_constant(string_constant_194);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_195,
	    string_constant_155,string_constant_196,string_constant_197,
	    string_constant_198,string_constant_199));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qsymbolic_parameter,list_constant_6,Nil,
	    temp,Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_3(string_constant_200,
	    string_constant_201,string_constant_202)),Nil);
    Symbolic_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsymbolic_parameter,
	    Class_description_gkbprop);
    Qtext_parameter = STATIC_SYMBOL("TEXT-PARAMETER",AB_package);
    check_if_superior_classes_are_defined(Qtext_parameter,list_constant_6);
    string_constant_203 = STATIC_STRING("1m1m8v834iy1l8t");
    string_constant_204 = 
	    STATIC_STRING("1o4z8r83-Ey83-Ey834iy834iy034+Cy001r1l8l1l8o1m8p83=Cy1l8z1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. ");
    string_constant_205 = 
	    STATIC_STRING("supported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83-Iy83-Iy834iy834iy083Gy001o");
    string_constant_206 = 
	    STATIC_STRING("1l8o1l8l1m8p8363y1l83Fy000004z8r83-Ky83-Ky834iy834iy0+skkkkkkk3A++y001q1l8o1l8l1m8p83-Uy1l8z1l83Cy1m83Dy5qExport000004z8r8u8u834");
    string_constant_207 = 
	    STATIC_STRING("iy834iy01p8w9k3uy3uy1v1t83Jy1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mr3Qy1mr3Vy1n83Oy1mu3Qy1mu3Vy1n83Oy1m3jy3Qy1m");
    string_constant_208 = 
	    STATIC_STRING("3jy3Vy1n83Oy1m3my3Vy1m3my3Qy1p83Oy1m3Cy3ay1m3Cy3by1m3Dy3by1m3Dy3ay1p83Oy1m3Iy3ay1m3Iy3by1m3Jy3by1m3Jy3ay1p83Oy1m3Oy3ay1m3Oy3by1m");
    string_constant_209 = 
	    STATIC_STRING("3Py3by1m3Py3ay1p83Oy1m3Uy3ay1m3Uy3by1m3Vy3by1m3Vy3ay1p83Oy1m3ay3ay1m3ay3by1m3by3by1m3by3ay1p83Oy1m3gy3ay1m3gy3by1m3hy3by1m3hy3ay");
    string_constant_210 = 
	    STATIC_STRING("001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_211 = 
	    STATIC_STRING("1q8q1o834iy1l83=vy1m8v834iy8t1p83-Ey34+Cy8l8o1m8p83=Cy1q83-Iy83Gy8o8l1m8p8363y83Fy1p83-Ky5k8o8l1m8p83-Uy1m8u1p8w9k3uy3uy1v1t83Jy");
    string_constant_212 = 
	    STATIC_STRING("1mwk1m3iyk1m3uyw1m3uy3iy1m3iy3uy1mw3uy1mk3iy1mkw1n83Oy1mr3Qy1mr3Vy1n83Oy1mu3Qy1mu3Vy1n83Oy1m3jy3Qy1m3jy3Vy1n83Oy1m3my3Vy1m3my3Qy");
    string_constant_213 = 
	    STATIC_STRING("1p83Oy1m3Cy3ay1m3Cy3by1m3Dy3by1m3Dy3ay1p83Oy1m3Iy3ay1m3Iy3by1m3Jy3by1m3Jy3ay1p83Oy1m3Oy3ay1m3Oy3by1m3Py3by1m3Py3ay1p83Oy1m3Uy3ay");
    string_constant_214 = 
	    STATIC_STRING("1m3Uy3by1m3Vy3by1m3Vy3ay1p83Oy1m3ay3ay1m3ay3by1m3by3by1m3by3ay1p83Oy1m3gy3ay1m3gy3by1m3hy3by1m3hy3ay");
    temp = regenerate_optimized_constant(string_constant_203);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(8,string_constant_204,
	    string_constant_155,string_constant_205,string_constant_206,
	    string_constant_207,string_constant_208,string_constant_209,
	    string_constant_210));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qtext_parameter,list_constant_6,Nil,temp,
	    Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_4(string_constant_211,
	    string_constant_212,string_constant_213,string_constant_214)),Nil);
    Text_parameter_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtext_parameter,
	    Class_description_gkbprop);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qcurrent_value_of_variable_or_parameter = 
	    STATIC_SYMBOL("CURRENT-VALUE-OF-VARIABLE-OR-PARAMETER",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Priority_of_expiration_update_task = FIX((SI_Long)2L);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpropagate_variable_value_expiration = 
	    STATIC_SYMBOL("PROPAGATE-VARIABLE-VALUE-EXPIRATION",AB_package);
    SET_SYMBOL_FUNCTION(Qpropagate_variable_value_expiration,
	    STATIC_FUNCTION(propagate_variable_value_expiration,NIL,FALSE,
	    1,1));
    Qsimulation_frame = STATIC_SYMBOL("SIMULATION-FRAME",AB_package);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qsimulation_frame,CONS(Qsimulation_subtable,
	    temp),Qsubstitute_class_and_kb_flags);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qitem,Qblock);
    check_if_superior_classes_are_defined(Qsimulation_subtable,
	    list_constant_8);
    string_constant_215 = STATIC_STRING("1n1m8v832Ly1l8t1l83ey");
    string_constant_216 = 
	    STATIC_STRING("1u4z8r83-py83-py832Ly832Ly00001q1l8l1l83Ey1l83Cy1l8z1m8p83-py1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\n");
    string_constant_217 = 
	    STATIC_STRING("tracing-message-level: (or default &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]000004z8r83FNy83FNy832Ly83");
    string_constant_218 = 
	    STATIC_STRING("2Ly00001p1m8p83A+y1l8o1l8l1l8z1l83Cy000004z8r83a8y83a8y832Ly832Ly00001n1n8p83F7y83Gy1l8o1l8l000004z8r83Kmy83Kmy832Ly832Ly00001m1");
    string_constant_219 = 
	    STATIC_STRING("l8o1l8l000004z8r83JVy83JVy832Ly832Ly0k001m1l8o1l8l000004z8r83aDy83aDy832Ly832Ly00001m1l8o1l8l000004z8r83aEy83aEy832Ly832Ly00001o");
    string_constant_220 = 
	    STATIC_STRING("1m8p830hy1l8o1l8l1l8z000004z8r83Xcy83Xcy832Ly832Ly00001o1l8o1l8l1l83Cy1l83Uy000004z8r83aFy83aFy832Ly832Ly00001n1l8l1l8o1l83Cy000");
    string_constant_221 = 
	    STATIC_STRING("004z8r83aGy83aGy832Ly832Ly00001n1l8l1l8o1l83Cy00000");
    string_constant_222 = 
	    STATIC_STRING("1w8q1p832Ly1m83Ry9k1m8v832Ly8t83ey1r83-py08l83Ey83Cy8z1m8p83-py1r83FNy01m8p83A+y8o8l8z83Cy1p83a8y01n8p83F7y83Gy8o8l1o83Kmy08o8l1");
    string_constant_223 = 
	    STATIC_STRING("o83JVyk8o8l1o83aDy08o8l1q83aEy01m8p830hy8o8l8z1q83Xcy08o8l83Cy83Uy1o83aFy08o83Cy1o83aGy08o83Cy");
    temp = regenerate_optimized_constant(string_constant_215);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_216,
	    string_constant_217,string_constant_218,string_constant_219,
	    string_constant_220,string_constant_221));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qsimulation_subtable,list_constant_8,Nil,
	    temp,Nil,temp_1,list_constant_8,
	    regenerate_optimized_constant(LIST_2(string_constant_222,
	    string_constant_223)),Nil);
    Simulation_subtable_class_description = 
	    lookup_global_or_kb_specific_property_value(Qsimulation_subtable,
	    Class_description_gkbprop);
    Qsimulation_class = STATIC_SYMBOL("SIMULATION-CLASS",AB_package);
    Qput_simulation_class_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-CLASS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_class_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_class_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsimulation_class,
	    SYMBOL_FUNCTION(Qput_simulation_class_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinitial_value_for_simulation_qm = 
	    STATIC_SYMBOL("INITIAL-VALUE-FOR-SIMULATION\?",AB_package);
    Qput_initial_value_for_simulation_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-INITIAL-VALUE-FOR-SIMULATION\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_initial_value_for_simulation_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_initial_value_for_simulation_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinitial_value_for_simulation_qm,
	    SYMBOL_FUNCTION(Qput_initial_value_for_simulation_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qsimulation_value = STATIC_SYMBOL("SIMULATION-VALUE",AB_package);
    Qput_simulation_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-VALUE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_value_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsimulation_value,
	    SYMBOL_FUNCTION(Qput_simulation_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qsimulation_value_time = STATIC_SYMBOL("SIMULATION-VALUE-TIME",AB_package);
    Qput_simulation_value_time_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SIMULATION-VALUE-TIME-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_simulation_value_time_where_slot_is_absent,
	    STATIC_FUNCTION(put_simulation_value_time_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qsimulation_value_time,
	    SYMBOL_FUNCTION(Qput_simulation_value_time_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnew_simulation_value = STATIC_SYMBOL("NEW-SIMULATION-VALUE",AB_package);
    Qput_new_simulation_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NEW-SIMULATION-VALUE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_new_simulation_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_new_simulation_value_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnew_simulation_value,
	    SYMBOL_FUNCTION(Qput_new_simulation_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnew_simulation_value_time = STATIC_SYMBOL("NEW-SIMULATION-VALUE-TIME",
	    AB_package);
    Qput_new_simulation_value_time_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NEW-SIMULATION-VALUE-TIME-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_new_simulation_value_time_where_slot_is_absent,
	    STATIC_FUNCTION(put_new_simulation_value_time_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnew_simulation_value_time,
	    SYMBOL_FUNCTION(Qput_new_simulation_value_time_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qnew_simulation_value_step = STATIC_SYMBOL("NEW-SIMULATION-VALUE-STEP",
	    AB_package);
    Qput_new_simulation_value_step_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-NEW-SIMULATION-VALUE-STEP-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_new_simulation_value_step_where_slot_is_absent,
	    STATIC_FUNCTION(put_new_simulation_value_step_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qnew_simulation_value_step,
	    SYMBOL_FUNCTION(Qput_new_simulation_value_step_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qk1_value = STATIC_SYMBOL("K1-VALUE",AB_package);
    Qput_k1_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-K1-VALUE-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_k1_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_k1_value_where_slot_is_absent,NIL,FALSE,2,2));
    mutate_global_property(Qk1_value,
	    SYMBOL_FUNCTION(Qput_k1_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qk2_value = STATIC_SYMBOL("K2-VALUE",AB_package);
    Qput_k2_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-K2-VALUE-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_k2_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_k2_value_where_slot_is_absent,NIL,FALSE,2,2));
    mutate_global_property(Qk2_value,
	    SYMBOL_FUNCTION(Qput_k2_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qk3_value = STATIC_SYMBOL("K3-VALUE",AB_package);
    Qput_k3_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-K3-VALUE-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_k3_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_k3_value_where_slot_is_absent,NIL,FALSE,2,2));
    mutate_global_property(Qk3_value,
	    SYMBOL_FUNCTION(Qput_k3_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qk4_value = STATIC_SYMBOL("K4-VALUE",AB_package);
    Qput_k4_value_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-K4-VALUE-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_k4_value_where_slot_is_absent,
	    STATIC_FUNCTION(put_k4_value_where_slot_is_absent,NIL,FALSE,2,2));
    mutate_global_property(Qk4_value,
	    SYMBOL_FUNCTION(Qput_k4_value_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtime_of_next_update = STATIC_SYMBOL("TIME-OF-NEXT-UPDATE",AB_package);
    Qput_time_of_next_update_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TIME-OF-NEXT-UPDATE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_time_of_next_update_where_slot_is_absent,
	    STATIC_FUNCTION(put_time_of_next_update_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtime_of_next_update,
	    SYMBOL_FUNCTION(Qput_time_of_next_update_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinterval_at_which_to_send_value_to_inference_engine = 
	    STATIC_SYMBOL("INTERVAL-AT-WHICH-TO-SEND-VALUE-TO-INFERENCE-ENGINE",
	    AB_package);
    Qput_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-INTERVAL-AT-WHICH-TO-SEND-VALUE-TO-INFERENCE-ENGINE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent,
	    STATIC_FUNCTION(put_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qinterval_at_which_to_send_value_to_inference_engine,
	    SYMBOL_FUNCTION(Qput_interval_at_which_to_send_value_to_inference_engine_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qlast_time_value_sent_to_inference_engine = 
	    STATIC_SYMBOL("LAST-TIME-VALUE-SENT-TO-INFERENCE-ENGINE",
	    AB_package);
    Qput_last_time_value_sent_to_inference_engine_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-LAST-TIME-VALUE-SENT-TO-INFERENCE-ENGINE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_last_time_value_sent_to_inference_engine_where_slot_is_absent,
	    STATIC_FUNCTION(put_last_time_value_sent_to_inference_engine_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qlast_time_value_sent_to_inference_engine,
	    SYMBOL_FUNCTION(Qput_last_time_value_sent_to_inference_engine_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qg2_defstruct_structure_name_simulation_info_g2_struct = 
	    STATIC_SYMBOL("SIMULATION-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsimulation_info = STATIC_SYMBOL("SIMULATION-INFO",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_simulation_info_g2_struct,
	    Qsimulation_info,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qsimulation_info,
	    Qg2_defstruct_structure_name_simulation_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_simulation_info == UNBOUND)
	The_type_description_of_simulation_info = Nil;
    string_constant_224 = 
	    STATIC_STRING("43Dy8m83n7y1n83n7y8n8k1l8n0000000k3Cyk0k0");
    temp = The_type_description_of_simulation_info;
    The_type_description_of_simulation_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_224));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_simulation_info_g2_struct,
	    The_type_description_of_simulation_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qsimulation_info,
	    The_type_description_of_simulation_info,Qtype_description_of_type);
    Qoutstanding_simulation_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-SIMULATION-INFO-COUNT",AB_package);
    Qsimulation_info_structure_memory_usage = 
	    STATIC_SYMBOL("SIMULATION-INFO-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_225 = STATIC_STRING("1q83n7y8s83-phy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_simulation_info_count);
    push_optimized_constant(Qsimulation_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_225));
    Qchain_of_available_simulation_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SIMULATION-INFOS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_simulation_infos,
	    Chain_of_available_simulation_infos);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_simulation_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsimulation_info_count = STATIC_SYMBOL("SIMULATION-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsimulation_info_count,Simulation_info_count);
    record_system_variable(Qsimulation_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_simulation_infos_vector == UNBOUND)
	Chain_of_available_simulation_infos_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsimulation_info_structure_memory_usage,
	    STATIC_FUNCTION(simulation_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_simulation_info_count,
	    STATIC_FUNCTION(outstanding_simulation_info_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_simulation_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_simulation_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsimulation_info,
	    reclaim_structure_for_simulation_info_1);
    Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct 
	    = 
	    STATIC_SYMBOL("VARIABLE-SIMULATION-RUNTIME-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qvariable_simulation_runtime_structure = 
	    STATIC_SYMBOL("VARIABLE-SIMULATION-RUNTIME-STRUCTURE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct,
	    Qvariable_simulation_runtime_structure,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qvariable_simulation_runtime_structure,
	    Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_variable_simulation_runtime_structure == 
	    UNBOUND)
	The_type_description_of_variable_simulation_runtime_structure = Nil;
    string_constant_226 = 
	    STATIC_STRING("43Dy8m83oSy1n83oSy8n8k1l8n0000001l1m83My83-BGyk3Myk0k0");
    temp = The_type_description_of_variable_simulation_runtime_structure;
    The_type_description_of_variable_simulation_runtime_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_226));
    mutate_global_property(Qg2_defstruct_structure_name_variable_simulation_runtime_structure_g2_struct,
	    The_type_description_of_variable_simulation_runtime_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qvariable_simulation_runtime_structure,
	    The_type_description_of_variable_simulation_runtime_structure,
	    Qtype_description_of_type);
    Qoutstanding_variable_simulation_runtime_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-VARIABLE-SIMULATION-RUNTIME-STRUCTURE-COUNT",
	    AB_package);
    Qvariable_simulation_runtime_structure_structure_memory_usage = 
	    STATIC_SYMBOL("VARIABLE-SIMULATION-RUNTIME-STRUCTURE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_227 = STATIC_STRING("1q83oSy8s83-wHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_variable_simulation_runtime_structure_count);
    push_optimized_constant(Qvariable_simulation_runtime_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_227));
    Qchain_of_available_variable_simulation_runtime_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-VARIABLE-SIMULATION-RUNTIME-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_variable_simulation_runtime_structures,
	    Chain_of_available_variable_simulation_runtime_structures);
    record_system_variable(Qchain_of_available_variable_simulation_runtime_structures,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qvariable_simulation_runtime_structure_count = 
	    STATIC_SYMBOL("VARIABLE-SIMULATION-RUNTIME-STRUCTURE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qvariable_simulation_runtime_structure_count,
	    Variable_simulation_runtime_structure_count);
    record_system_variable(Qvariable_simulation_runtime_structure_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_variable_simulation_runtime_structures_vector 
	    == UNBOUND)
	Chain_of_available_variable_simulation_runtime_structures_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qvariable_simulation_runtime_structure_structure_memory_usage,
	    STATIC_FUNCTION(variable_simulation_runtime_structure_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_variable_simulation_runtime_structure_count,
	    STATIC_FUNCTION(outstanding_variable_simulation_runtime_structure_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_variable_simulation_runtime_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_variable_simulation_runtime_structure,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qvariable_simulation_runtime_structure,
	    reclaim_structure_for_variable_simulation_runtime_structure_1);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    if (Global_list_of_all_data_servers == UNBOUND)
	Global_list_of_all_data_servers = Nil;
    Kb_specific_property_names = CONS(Qdata_server,Kb_specific_property_names);
    mutate_global_property(Qdata_server,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Data_server_kbprop = Qdata_server;
    Qdata_server_or_alias_qm = STATIC_SYMBOL("DATA-SERVER-OR-ALIAS\?",
	    AB_package);
    Kb_specific_property_names = CONS(Qdata_server_or_alias_qm,
	    Kb_specific_property_names);
    mutate_global_property(Qdata_server_or_alias_qm,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Data_server_or_alias_qm_kbprop = Qdata_server_or_alias_qm;
    Qlist_of_all_data_servers = STATIC_SYMBOL("LIST-OF-ALL-DATA-SERVERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_all_data_servers,
	    List_of_all_data_servers);
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qcopy_data_servers_for_process = 
	    STATIC_SYMBOL("COPY-DATA-SERVERS-FOR-PROCESS",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qcopy_data_servers_for_process);
    record_system_variable(Qlist_of_all_data_servers,Qvariables,
	    list_constant_9,Qt,Qnil,Qnil,Qnil);
    Qg2_defstruct_structure_name_data_server_g2_struct = 
	    STATIC_SYMBOL("DATA-SERVER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_data_server_g2_struct,
	    Qdata_server,Qab_name_of_unique_structure_type);
    mutate_global_property(Qdata_server,
	    Qg2_defstruct_structure_name_data_server_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_data_server == UNBOUND)
	The_type_description_of_data_server = Nil;
    string_constant_228 = 
	    STATIC_STRING("43Dy8m83BVy1n83BVy8n8k1l8n0000001l1n8y83-3My1z83-7By83xAy83x9y83xKy83x8y83-Ccy83xCy83xHy83xIy83xBy83xDy83xGy83xEy83xJy83xFyk3Dyk");
    string_constant_229 = STATIC_STRING("0k0");
    temp = The_type_description_of_data_server;
    The_type_description_of_data_server = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(LIST_2(string_constant_228,
	    string_constant_229)));
    mutate_global_property(Qg2_defstruct_structure_name_data_server_g2_struct,
	    The_type_description_of_data_server,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qdata_server,
	    The_type_description_of_data_server,Qtype_description_of_type);
    Qoutstanding_data_server_count = 
	    STATIC_SYMBOL("OUTSTANDING-DATA-SERVER-COUNT",AB_package);
    Qdata_server_structure_memory_usage = 
	    STATIC_SYMBOL("DATA-SERVER-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_230 = STATIC_STRING("1q83BVy8s83-Psy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_data_server_count);
    push_optimized_constant(Qdata_server_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_230));
    Qchain_of_available_data_servers = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-DATA-SERVERS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_data_servers,
	    Chain_of_available_data_servers);
    record_system_variable(Qchain_of_available_data_servers,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qdata_server_count = STATIC_SYMBOL("DATA-SERVER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_server_count,Data_server_count);
    record_system_variable(Qdata_server_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_data_servers_vector == UNBOUND)
	Chain_of_available_data_servers_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qdata_server_structure_memory_usage,
	    STATIC_FUNCTION(data_server_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_data_server_count,
	    STATIC_FUNCTION(outstanding_data_server_count,NIL,FALSE,0,0));
    reclaim_structure_for_data_server_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_data_server,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qdata_server,
	    reclaim_structure_for_data_server_1);
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_data_servers_for_process,
	    STATIC_FUNCTION(copy_data_servers_for_process,NIL,FALSE,0,0));
    if (Data_server_pretty_name_alist == UNBOUND)
	Data_server_pretty_name_alist = Nil;
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_1 = STATIC_STRING("The data server specified for ~NF is ");
    string_constant_2 = 
	    STATIC_STRING(", which is not a defined data server or data server alias.");
    Qput_data_server_map = STATIC_SYMBOL("PUT-DATA-SERVER-MAP",AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_server_map,
	    STATIC_FUNCTION(put_data_server_map,NIL,FALSE,3,3));
    mutate_global_property(Qdata_server_map,
	    SYMBOL_FUNCTION(Qput_data_server_map),Qslot_putter);
    Qdata_server_parameters = STATIC_SYMBOL("DATA-SERVER-PARAMETERS",
	    AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_10 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qdata_server_parameters,
	    list_constant_10);
    string_constant_231 = STATIC_STRING("1l1l83ey");
    string_constant_232 = 
	    STATIC_STRING("1o4z8r83BWy83BWy83J6y83J6y00001o1l8l1l83Ey1l83Cy1m8p83BWy000004z8r83Y8y83Y8y83J6y83J6y0o001o1l8l1l8o1l83Cy1m8p83-Yy000004z8r83NG");
    string_constant_233 = 
	    STATIC_STRING("y83NGy83J6y83J6y00001o1l8l1l83Ey1l83Cy1m8p83Ky000004z8r83R2y83R2y83J6y83J6y00001n1l8l1l83Ey1l83Cy00000");
    string_constant_234 = 
	    STATIC_STRING("1q8q1n83J6y1l83-sy83ey1q83BWy08l83Ey83Cy1m8p83BWy1q83Y8yo8l8o83Cy1m8p83-Yy1q83NGy08l83Ey83Cy1m8p83Ky1p83R2y08l83Ey83Cy");
    temp = regenerate_optimized_constant(string_constant_231);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_232,
	    string_constant_233));
    add_class_to_environment(9,Qdata_server_parameters,list_constant_10,
	    Nil,temp,Nil,temp_1,list_constant_10,
	    regenerate_optimized_constant(string_constant_234),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qdata_server_parameters,Data_server_parameters);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qdata_server_parameters,Qvariables,
	    Ksystem_frame,Qnil,Qnil,Qnil,Qt);
    Qpriority_of_data_service = STATIC_SYMBOL("PRIORITY-OF-DATA-SERVICE",
	    AB_package);
    Qpriority_of_continued_data_service = 
	    STATIC_SYMBOL("PRIORITY-OF-CONTINUED-DATA-SERVICE",AB_package);
    Qput_priority_of_continued_data_service_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PRIORITY-OF-CONTINUED-DATA-SERVICE-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_priority_of_continued_data_service_where_slot_is_absent,
	    STATIC_FUNCTION(put_priority_of_continued_data_service_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qpriority_of_continued_data_service,
	    SYMBOL_FUNCTION(Qput_priority_of_continued_data_service_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qgsi_data_server_filters_text_qm = 
	    STATIC_SYMBOL("GSI-DATA-SERVER-FILTERS-TEXT\?",AB_package);
    Qgsi_data_server_filters_text = 
	    STATIC_SYMBOL("GSI-DATA-SERVER-FILTERS-TEXT",AB_package);
    alias_slot_name(3,Qgsi_data_server_filters_text_qm,
	    Qgsi_data_server_filters_text,Qnil);
    Qg2_meter_data_service_on_qm = 
	    STATIC_SYMBOL("G2-METER-DATA-SERVICE-ON\?",AB_package);
    Qg2_meter_data_service_on = STATIC_SYMBOL("G2-METER-DATA-SERVICE-ON",
	    AB_package);
    alias_slot_name(3,Qg2_meter_data_service_on_qm,
	    Qg2_meter_data_service_on,Qnil);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_235 = 
	    STATIC_STRING("1p1m83BWy1m9k83Zy1m83BWy83-cry1m83-cry83-Pry1o83-cry1n83-Pry1m9k83vy83-cry1n83-tyln9l1n83-Pry1p83*My1m9k83Cpy1m9k83-Cdy1m9k83-ss");
    string_constant_236 = STATIC_STRING("y83BXy1mlp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_235,
	    string_constant_236)));
    Qdata_server_aliases = STATIC_SYMBOL("DATA-SERVER-ALIASES",AB_package);
    Qinstall_system_table_for_data_server_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-DATA-SERVER-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_data_server_parameters,
	    STATIC_FUNCTION(install_system_table_for_data_server_parameters,
	    NIL,FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_data_server_parameters);
    set_get(Qdata_server_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qdata_server_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_data_server_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-DATA-SERVER-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_data_server_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_data_server_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qdeinstall_system_table_for_data_server_parameters);
    set_get(Qdata_server_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qdata_server_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qg2_meter_data_server = STATIC_SYMBOL("G2-METER-DATA-SERVER",AB_package);
    Qput_g2_meter_data_service_on_qm = 
	    STATIC_SYMBOL("PUT-G2-METER-DATA-SERVICE-ON\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_meter_data_service_on_qm,
	    STATIC_FUNCTION(put_g2_meter_data_service_on_qm,NIL,FALSE,3,3));
    mutate_global_property(Qg2_meter_data_service_on_qm,
	    SYMBOL_FUNCTION(Qput_g2_meter_data_service_on_qm),Qslot_putter);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    string_constant_3 = 
	    STATIC_STRING("the name ~(~a~) may not be given two alias mappings");
    Qcompile_data_server_aliases_for_slot = 
	    STATIC_SYMBOL("COMPILE-DATA-SERVER-ALIASES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_data_server_aliases_for_slot,
	    STATIC_FUNCTION(compile_data_server_aliases_for_slot,NIL,TRUE,
	    3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qdata_server_aliases,
	    SYMBOL_FUNCTION(Qcompile_data_server_aliases_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qdata_server_aliases,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_4 = STATIC_STRING("none");
    string_constant_5 = STATIC_STRING(" implies service through ");
    string_constant_6 = STATIC_STRING(", ");
    Qwrite_data_server_aliases_from_slot = 
	    STATIC_SYMBOL("WRITE-DATA-SERVER-ALIASES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_data_server_aliases_from_slot,
	    STATIC_FUNCTION(write_data_server_aliases_from_slot,NIL,FALSE,
	    2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qdata_server_aliases,
	    SYMBOL_FUNCTION(Qwrite_data_server_aliases_from_slot),
	    Qslot_value_writer);
    Qput_data_server_aliases = STATIC_SYMBOL("PUT-DATA-SERVER-ALIASES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_data_server_aliases,
	    STATIC_FUNCTION(put_data_server_aliases,NIL,FALSE,3,3));
    mutate_global_property(Qdata_server_aliases,
	    SYMBOL_FUNCTION(Qput_data_server_aliases),Qslot_putter);
    string_constant_7 = 
	    STATIC_STRING("Within the data server aliases just defined, note that");
    string_constant_8 = STATIC_STRING(" ");
    string_constant_9 = STATIC_STRING(",");
    string_constant_10 = STATIC_STRING(" and");
    string_constant_11 = STATIC_STRING("are not defined data servers.");
    string_constant_12 = 
	    STATIC_STRING("Within the data server aliases just defined, note that ");
    string_constant_13 = STATIC_STRING(" is not a defined data server.");
    Qvalue_request_pending = STATIC_SYMBOL("VALUE-REQUEST-PENDING",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)33L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)34L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)36L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)41L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)42L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)43L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)44L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)46L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)47L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)51L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)54L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)55L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)56L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)57L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)58L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)62L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)63L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)45L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)48L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)49L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)50L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)51L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)52L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)53L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)54L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)55L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)56L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)57L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)62L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)63L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)34L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)40L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)43L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)44L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)46L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)47L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)48L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)49L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)54L,(SI_Long)51L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)55L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)35L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)36L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)37L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)40L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)41L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)46L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)47L,(SI_Long)57344L);
    if (Explanation_variables == UNBOUND)
	Explanation_variables = Nil;
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qformula_invocation = STATIC_SYMBOL("FORMULA-INVOCATION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_formula_invocation_g2_struct,
	    Qformula_invocation,Qab_name_of_unique_structure_type);
    mutate_global_property(Qformula_invocation,
	    Qg2_defstruct_structure_name_formula_invocation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_formula_invocation == UNBOUND)
	The_type_description_of_formula_invocation = Nil;
    string_constant_237 = 
	    STATIC_STRING("43Dy8m83hQy1o83hQy830Ey8n8k1l830Ey0000001m1m8x830Ey1n8y83-3hy1n83wmy83wly83wjykxk0k0");
    temp = The_type_description_of_formula_invocation;
    The_type_description_of_formula_invocation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_237));
    mutate_global_property(Qg2_defstruct_structure_name_formula_invocation_g2_struct,
	    The_type_description_of_formula_invocation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qformula_invocation,
	    The_type_description_of_formula_invocation,
	    Qtype_description_of_type);
    Qoutstanding_formula_invocation_count = 
	    STATIC_SYMBOL("OUTSTANDING-FORMULA-INVOCATION-COUNT",AB_package);
    Qformula_invocation_structure_memory_usage = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_238 = STATIC_STRING("1q83hQy8s83-Upy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_formula_invocation_count);
    push_optimized_constant(Qformula_invocation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_238));
    Qchain_of_available_formula_invocations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FORMULA-INVOCATIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_formula_invocations,
	    Chain_of_available_formula_invocations);
    record_system_variable(Qchain_of_available_formula_invocations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qformula_invocation_count = STATIC_SYMBOL("FORMULA-INVOCATION-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qformula_invocation_count,
	    Formula_invocation_count);
    record_system_variable(Qformula_invocation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_formula_invocations_vector == UNBOUND)
	Chain_of_available_formula_invocations_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qformula_invocation_structure_memory_usage,
	    STATIC_FUNCTION(formula_invocation_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_formula_invocation_count,
	    STATIC_FUNCTION(outstanding_formula_invocation_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_formula_invocation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_formula_invocation,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qformula_invocation,
	    reclaim_structure_for_formula_invocation_1);
    string_constant_14 = 
	    STATIC_STRING("Requesting a value for ~NF from a data server.");
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    string_constant_15 = 
	    STATIC_STRING("~NF is not active, its value was requested in ~NF.");
    Qtask_to_detect_failure = STATIC_SYMBOL("TASK-TO-DETECT-FAILURE",
	    AB_package);
    Qtask_to_probe_failed_variable = 
	    STATIC_SYMBOL("TASK-TO-PROBE-FAILED-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qtask_to_detect_failure,
	    STATIC_FUNCTION(task_to_detect_failure,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qtask_to_probe_failed_variable,
	    STATIC_FUNCTION(task_to_probe_failed_variable,NIL,FALSE,1,1));
    Qclear_currently_evaluating_formula_after_bombout = 
	    STATIC_SYMBOL("CLEAR-CURRENTLY-EVALUATING-FORMULA-AFTER-BOMBOUT",
	    AB_package);
    def_bombout_clean_up_function(Qclear_currently_evaluating_formula_after_bombout);
    SET_SYMBOL_FUNCTION(Qclear_currently_evaluating_formula_after_bombout,
	    STATIC_FUNCTION(clear_currently_evaluating_formula_after_bombout,
	    NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Within_backward_chaining_task == UNBOUND)
	Within_backward_chaining_task = Nil;
    string_constant_16 = 
	    STATIC_STRING("The formula computing the value of ~NF refers directly to ~\n           itself, and so cannot be evaluated.");
    string_constant_17 = 
	    STATIC_STRING("Formulas computing the value of ~NF refer indirectly to ~\n             itself, and so cannot be evaluated.  The variables in the ~\n             loop are the following: ");
    string_constant_18 = STATIC_STRING("and");
    Qparent_attribute_name = STATIC_SYMBOL("PARENT-ATTRIBUTE-NAME",AB_package);
    string_constant_19 = 
	    STATIC_STRING("~nw~%Exiting execution of this formula.  No value was computed for ~NF");
    if (New_value_computed_in_formula_qm == UNBOUND)
	New_value_computed_in_formula_qm = Nil;
    Qexpression_cell_updated_for_variable = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_variable,
	    STATIC_FUNCTION(expression_cell_updated_for_variable,NIL,FALSE,
	    5,5));
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_variable);
    set_get(Qvariable,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    Qexpression_cell_updated_for_generic_formula = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-GENERIC-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_generic_formula,
	    STATIC_FUNCTION(expression_cell_updated_for_generic_formula,
	    NIL,FALSE,5,5));
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_generic_formula);
    set_get(Qgeneric_formula,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_formula,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    array_constant_4 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_20 = STATIC_STRING(" of ");
    Qdenote_cell_array_element_for_variable = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_variable,
	    STATIC_FUNCTION(denote_cell_array_element_for_variable,NIL,
	    FALSE,3,3));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_variable);
    set_get(Qvariable,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    array_constant_5 = STATIC_ARRAY(list_constant_11,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qdenote_cell_array_element_for_generic_formula = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-GENERIC-FORMULA",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_generic_formula,
	    STATIC_FUNCTION(denote_cell_array_element_for_generic_formula,
	    NIL,FALSE,3,3));
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_generic_formula);
    set_get(Qgeneric_formula,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qgeneric_formula,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qput_current_value_called_from_simulator_p = 
	    STATIC_SYMBOL("PUT-CURRENT-VALUE-CALLED-FROM-SIMULATOR-P",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qput_current_value_called_from_simulator_p,
	    Put_current_value_called_from_simulator_p);
    record_system_variable(Qput_current_value_called_from_simulator_p,
	    Qvariables,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_21 = STATIC_STRING("~a");
    if (Put_current_evaluation_value_old_value_qm == UNBOUND)
	Put_current_evaluation_value_old_value_qm = Nil;
    if (Put_current_evaluation_value_return_value == UNBOUND)
	Put_current_evaluation_value_return_value = Nil;
    string_constant_22 = 
	    STATIC_STRING("An attempt was made to store a value into ~NF which failed, ~\n         because it was not active.");
    string_constant_23 = 
	    STATIC_STRING("An attempt to store the value ~NV of type ~NT into ~NF failed ~\n           because of type mismatch.  ~NF requires values of type ~NT.");
    Qsupplied = STATIC_SYMBOL("SUPPLIED",AB_package);
    string_constant_24 = 
	    STATIC_STRING("The variable ~NF, which has a validity ~\n                        interval of SUPPLIED, received a value ~\n                        with no supplied expiration time.");
    Qindefinite = STATIC_SYMBOL("INDEFINITE",AB_package);
    string_constant_25 = 
	    STATIC_STRING("The variable ~NF has an invalid validity ~\n                     interval.  This is a G2 internal error, please ~\n                     notify Gensym software support.");
    string_constant_26 = 
	    STATIC_STRING("In ~NF, an attempt was made to conclude that the variable ~NF has no ~\n          current value.  The attempt failed, because the variable was not ~\n          active.");
    string_constant_27 = 
	    STATIC_STRING("In ~NF, an attempt was made to conclude that the variable ~NF has no ~\n         value.  The attempt failed, because the variable was not ~\n         active.");
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_items_needing_initialization_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-ITEMS-NEEDING-INITIALIZATION-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_items_needing_initialization_skip_list_entry,
	    STATIC_FUNCTION(mutate_items_needing_initialization_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_items_needing_initialization_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_items_needing_initialization_skip_list_entry);
    Qframe_serial_number_equal_function = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-EQUAL-FUNCTION",AB_package);
    Qactivate_subclass_of_entity_for_variable = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-VARIABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_variable,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_variable,NIL,
	    FALSE,1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_variable);
    set_get(Qvariable,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qg2_defstruct_structure_name_inference_background_collection_g2_struct 
	    = STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinference_background_collection = 
	    STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_inference_background_collection_g2_struct,
	    Qinference_background_collection,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qinference_background_collection,
	    Qg2_defstruct_structure_name_inference_background_collection_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_inference_background_collection == UNBOUND)
	The_type_description_of_inference_background_collection = Nil;
    string_constant_239 = 
	    STATIC_STRING("43Dy8m83j*y1n83j*y8n8k1l8n0000001l1n8y83-4by1l83-=Tykrk0k0");
    temp = The_type_description_of_inference_background_collection;
    The_type_description_of_inference_background_collection = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_239));
    mutate_global_property(Qg2_defstruct_structure_name_inference_background_collection_g2_struct,
	    The_type_description_of_inference_background_collection,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qinference_background_collection,
	    The_type_description_of_inference_background_collection,
	    Qtype_description_of_type);
    Qoutstanding_inference_background_collection_count = 
	    STATIC_SYMBOL("OUTSTANDING-INFERENCE-BACKGROUND-COLLECTION-COUNT",
	    AB_package);
    Qinference_background_collection_structure_memory_usage = 
	    STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_240 = STATIC_STRING("1q83j*y8s83-Zoy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_inference_background_collection_count);
    push_optimized_constant(Qinference_background_collection_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_240));
    Qchain_of_available_inference_background_collections = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INFERENCE-BACKGROUND-COLLECTIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_inference_background_collections,
	    Chain_of_available_inference_background_collections);
    record_system_variable(Qchain_of_available_inference_background_collections,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qinference_background_collection_count = 
	    STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinference_background_collection_count,
	    Inference_background_collection_count);
    record_system_variable(Qinference_background_collection_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_inference_background_collections_vector == UNBOUND)
	Chain_of_available_inference_background_collections_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qinference_background_collection_structure_memory_usage,
	    STATIC_FUNCTION(inference_background_collection_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_inference_background_collection_count,
	    STATIC_FUNCTION(outstanding_inference_background_collection_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_inference_background_collection_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_inference_background_collection,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qinference_background_collection,
	    reclaim_structure_for_inference_background_collection_1);
    Qperform_background_collection_for_inference_engine = 
	    STATIC_SYMBOL("PERFORM-BACKGROUND-COLLECTION-FOR-INFERENCE-ENGINE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qperform_background_collection_for_inference_engine,
	    STATIC_FUNCTION(perform_background_collection_for_inference_engine,
	    NIL,FALSE,2,2));
    Qdeactivate_subclass_of_entity_for_variable = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-VARIABLE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_variable,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_variable,NIL,
	    FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_variable);
    set_get(Qvariable,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qactivate_subclass_of_entity_for_parameter = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_parameter,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_parameter,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_parameter);
    set_get(Qparameter,Qactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qparameter,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_parameter = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_parameter,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_parameter,
	    NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_parameter);
    set_get(Qparameter,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qparameter,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qindexed_attribute_hash_table = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTE-HASH-TABLE",AB_package);
    Kb_specific_property_names = CONS(Qindexed_attribute_hash_table,
	    Kb_specific_property_names);
    mutate_global_property(Qindexed_attribute_hash_table,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Indexed_attribute_hash_table_kbprop = Qindexed_attribute_hash_table;
    Qindexed_attribute_classes = STATIC_SYMBOL("INDEXED-ATTRIBUTE-CLASSES",
	    AB_package);
    Kb_specific_property_names = CONS(Qindexed_attribute_classes,
	    Kb_specific_property_names);
    mutate_global_property(Qindexed_attribute_classes,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Indexed_attribute_classes_kbprop = Qindexed_attribute_classes;
    Qindexed_attributes = STATIC_SYMBOL("*INDEXED-ATTRIBUTES*",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qindexed_attributes,Indexed_attributes);
    record_system_variable(Qindexed_attributes,Qvariables,Nil,Qnil,Qnil,
	    Qnil,Qt);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qmutate_indexed_attribute_defining_classes_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-INDEXED-ATTRIBUTE-DEFINING-CLASSES-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_indexed_attribute_defining_classes_skip_list_entry,
	    STATIC_FUNCTION(mutate_indexed_attribute_defining_classes_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_indexed_attribute_defining_classes_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_indexed_attribute_defining_classes_skip_list_entry);
    Qavailable_indexed_attribute_parent_objects_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    Available_indexed_attribute_parent_objects_hash_vector_43_vectors);
    record_system_variable(Qavailable_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_indexed_attribute_parent_objects_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    Count_of_indexed_attribute_parent_objects_hash_vector_43_vectors);
    record_system_variable(Qcount_of_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_indexed_attribute_parent_objects_hash_vector_43_vectors_vector 
		= make_thread_array(Nil);
    Qout_indexed_attribute_parent_objects_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qindexed_attribute_parent_objects_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTE-PARENT-OBJECTS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_241 = STATIC_STRING("1q83-Zhy83*9y83-Owy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_indexed_attribute_parent_objects_hash_vector_43_vectors);
    push_optimized_constant(Qindexed_attribute_parent_objects_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_241));
    SET_SYMBOL_FUNCTION(Qindexed_attribute_parent_objects_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(indexed_attribute_parent_objects_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_indexed_attribute_parent_objects_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qmutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry 
	    = 
	    STATIC_SYMBOL("MUTATE-INDEXED-ATTRIBUTE-PARENT-OBJECTS-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry 
	    = 
	    SYMBOL_FUNCTION(Qmutate_indexed_attribute_parent_objects_tree_for_hash_skip_list_entry);
    Qevaluation_value_equal_p = STATIC_SYMBOL("EVALUATION-VALUE-EQUAL-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_value_equal_p,
	    STATIC_FUNCTION(evaluation_value_equal_p,NIL,FALSE,2,2));
    Qindexed_attribute_parent_objects_tree_for_hash = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTE-PARENT-OBJECTS-TREE-FOR-HASH",
	    AB_package);
    Qindexed_attribute_defining_classes = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTE-DEFINING-CLASSES",AB_package);
    Qhas_indexed_attributes = STATIC_SYMBOL("HAS-INDEXED-ATTRIBUTES",
	    AB_package);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qindexed_attributes_for_definition = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTES-FOR-DEFINITION",AB_package);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qis = STATIC_SYMBOL("IS",AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qhandle_update_to_indexed_attribute = 
	    STATIC_SYMBOL("HANDLE-UPDATE-TO-INDEXED-ATTRIBUTE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_update_to_indexed_attribute,
	    STATIC_FUNCTION(handle_update_to_indexed_attribute,NIL,FALSE,6,6));
    Qinsert_indexed_attribute_items_in_list = 
	    STATIC_SYMBOL("INSERT-INDEXED-ATTRIBUTE-ITEMS-IN-LIST",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qinsert_indexed_attribute_items_in_list,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Quuid = STATIC_SYMBOL("UUID",AB_package);
    Qunique_identification = STATIC_SYMBOL("UNIQUE-IDENTIFICATION",AB_package);
    string_constant_28 = 
	    STATIC_STRING("The attribute ~a and value ~NV are not indexed for the class ~\n          ~a.  No items will be added to the item-list ~NF.");
    SET_SYMBOL_FUNCTION(Qinsert_indexed_attribute_items_in_list,
	    STATIC_FUNCTION(insert_indexed_attribute_items_in_list,NIL,
	    FALSE,4,4));
    Qp_get_item_of_class_by_attribute_value = 
	    STATIC_SYMBOL("P-GET-ITEM-OF-CLASS-BY-ATTRIBUTE-VALUE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qp_get_item_of_class_by_attribute_value,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_29 = 
	    STATIC_STRING("The system procedure p-get-item-of-class-by-attribute-value is only available in G2 Enterprise");
    Qitem_not_found = STATIC_SYMBOL("ITEM-NOT-FOUND",AB_package);
    string_constant_30 = 
	    STATIC_STRING("The attribute ~a and value ~NV are not indexed for the class ~\n          ~a.  No items will be found.");
    SET_SYMBOL_FUNCTION(Qp_get_item_of_class_by_attribute_value,
	    STATIC_FUNCTION(p_get_item_of_class_by_attribute_value,NIL,
	    FALSE,3,3));
}
