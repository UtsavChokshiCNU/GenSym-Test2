/* fnctns.c
 * Input file:  functions.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "fnctns.h"


Object No_inlining_qm = UNBOUND;

static Object Qop;                 /* \( */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qfunction_definition_byte_code_body;  /* function-definition-byte-code-body */

static Object Qfunction_definition_parse_result;  /* function-definition-parse-result */

static Object Qbad;                /* bad */

/* COMPILE-FUNCTION-DEFINITION-FOR-SLOT */
Object compile_function_definition_for_slot varargs_1(int, n)
{
    Object translation, function_definition, gensymed_symbol;
    Object name, temp, old_definition_qm, old_name_qm, var_list, raw_body;
    Object current_computation_frame, compilation_status, compiled_body_qm;
    Object byte_code_body_qm, result_1, current_flag_state_qm;
    Object slot_description, new_cons, temp_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, stack_of_slot_value_changes, gensymed_symbol_2;
    Object gensymed_symbol_3, frame_and_slot_or_atom, ab_loop_list_;
    Object ab_loop_it_, stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(154,0);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    function_definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    name = FIRST(translation);
    temp = ISVREF(function_definition,(SI_Long)16L);
    old_definition_qm = CAR(temp);
    old_name_qm = old_definition_qm &&  !EQ(old_definition_qm,No_value) ? 
	    FIRST(old_definition_qm) : Nil;
    temp = SECOND(translation);
    var_list =  !EQ(CAR(temp),Qop) ? SECOND(translation) : Nil;
    raw_body = THIRD(translation);
    current_computation_frame = function_definition;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    1);
      compilation_status = Nil;
      compiled_body_qm = compile_expression(raw_body,Nil,
	      copy_list_using_gensym_conses_1(var_list));
      byte_code_body_qm = Nil;
      if (compiled_body_qm) {
	  if (old_name_qm &&  !EQ(old_name_qm,name))
	      mutate_global_or_kb_specific_property_value(old_name_qm,Nil,
		      Argument_range_gkbprop);
	  mutate_global_or_kb_specific_property_value(name,
		  length(var_list),Argument_range_gkbprop);
	  result_1 = Nil;
	  current_flag_state_qm = Nil;
	  slot_description = 
		  get_slot_description_of_class_description_function(Qframe_status_and_notes,
		  ISVREF(function_definition,(SI_Long)1L),Nil);
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
	      gensymed_symbol_1 = 
		      nconc2(stack_change_list_2(function_definition,
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
	      M_CAR(gensymed_symbol_1) = function_definition;
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
	    current_flag_state_qm = (SI_Long)0L != 
		    (IFIX(ISVREF(function_definition,(SI_Long)5L)) & 
		    (SI_Long)16777216L) ? T : Nil;
	    if ( !TRUEP(current_flag_state_qm)) {
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(function_definition,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = function_definition;
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = T;
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		svref_new_value_1 = IFIX(ISVREF(function_definition,
			(SI_Long)5L)) | (SI_Long)16777216L;
		ISVREF(function_definition,(SI_Long)5L) = 
			FIX(svref_new_value_1);
	    }
	    change_slot_value(3,function_definition,
		    Qname_or_names_for_frame,name);
	    byte_code_body_qm = compile_function_definition_for_stack(name,
		    function_definition,compiled_body_qm,var_list);
	    result_1 = change_slot_value(3,function_definition,
		    Qfunction_definition_byte_code_body,byte_code_body_qm);
	    if ( !TRUEP(current_flag_state_qm)) {
		svref_new_value_1 = IFIX(ISVREF(function_definition,
			(SI_Long)5L)) &  ~(SI_Long)16777216L;
		ISVREF(function_definition,(SI_Long)5L) = 
			FIX(svref_new_value_1);
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(function_definition,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		gensymed_symbol_1 = function_definition;
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
		ab_loop_it_ = temp_2 ? (EQ(function_definition,
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
		update_all_representations_of_slot(function_definition,
			slot_description,Nil,Nil);
	    if (ISVREF(slot_description,(SI_Long)14L))
		update_frame_name_references(function_definition);
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
	  if (byte_code_body_qm) {
	      if ( !TRUEP(No_inlining_qm))
		  change_slot_value(3,function_definition,
			  Qfunction_definition_parse_result,
			  copy_for_slot_value(translation));
	  }
	  else
	      compilation_status = Qbad;
	  update_frame_status(function_definition,compilation_status,Nil);
	  analyze_compiled_items_for_consistency(name);
	  result = phrase_list_3(name,var_list,compiled_body_qm);
      }
      else {
	  change_slot_value(3,function_definition,
		  Qfunction_definition_byte_code_body,Nil);
	  update_frame_status(function_definition,Qbad,Nil);
	  result = phrase_list_2(name,var_list);
      }
    POP_SPECIAL();
    return result;
}

static Object Qincomplete;         /* incomplete */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-FUNCTION-DEFINITION */
Object put_box_translation_and_text_slot_value_for_function_definition(function_definition,
	    box_translation_and_text,initializing_qm)
    Object function_definition, box_translation_and_text, initializing_qm;
{
    Object car_new_value, temp, old_definition_qm, old_name_qm, raw_definition;
    Object parsed_definition_qm, name, arglist;

    x_note_fn_call(154,1);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(function_definition)) && 
	    Loading_kb_p) {
	reclaim_slot_value(CAR(box_translation_and_text));
	car_new_value = No_value;
	M_CAR(box_translation_and_text) = car_new_value;
	note_frame_with_compilation_removed(function_definition);
	update_frame_status(function_definition,Qincomplete,initializing_qm);
    }
    if ( !TRUEP(initializing_qm)) {
	temp = ISVREF(function_definition,(SI_Long)16L);
	old_definition_qm = CAR(temp);
    }
    else
	old_definition_qm = Nil;
    old_name_qm = old_definition_qm &&  !EQ(old_definition_qm,No_value) ? 
	    FIRST(old_definition_qm) : Nil;
    raw_definition = CAR(box_translation_and_text);
    parsed_definition_qm =  !EQ(raw_definition,No_value) ? raw_definition :
	     Nil;
    name = FIRST(parsed_definition_qm);
    arglist = SECOND(parsed_definition_qm);
    if (initializing_qm && Loading_kb_p) {
	if (compiler_errors_qm(function_definition))
	    update_frame_status(function_definition,Qbad,initializing_qm);
    }
    if ( !TRUEP(initializing_qm))
	change_slot_value(3,function_definition,Qname_or_names_for_frame,name);
    if (old_name_qm &&  !EQ(old_name_qm,name))
	mutate_global_or_kb_specific_property_value(old_name_qm,Nil,
		Argument_range_gkbprop);
    if (parsed_definition_qm)
	mutate_global_or_kb_specific_property_value(name,length(arglist),
		Argument_range_gkbprop);
    else
	change_slot_value(3,function_definition,
		Qfunction_definition_byte_code_body,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(function_definition,Qbox_translation_and_text);
    SVREF(function_definition,FIX((SI_Long)16L)) = box_translation_and_text;
    return VALUES_2(box_translation_and_text,Nil);
}

/* PUT-FUNCTION-DEFINITION-BYTE-CODE-BODY */
Object put_function_definition_byte_code_body(function_definition,
	    new_byte_code_body,initializing_qm)
    Object function_definition, new_byte_code_body, initializing_qm;
{
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_, temp_2;
    Object stack_change_pop_store, cons_1, next_cons;
    SI_Long svref_new_value_1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(154,2);
    if (initializing_qm &&  
	    !TRUEP(compilations_up_to_date_p(function_definition)) && 
	    Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(function_definition);
    }
    result_1 = Nil;
    current_flag_state_qm = Nil;
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(function_definition,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(function_definition,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = function_definition;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    0);
      current_flag_state_qm = (SI_Long)0L != 
	      (IFIX(ISVREF(function_definition,(SI_Long)5L)) & 
	      (SI_Long)16777216L) ? T : Nil;
      if ( !TRUEP(current_flag_state_qm)) {
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(function_definition,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = function_definition;
	  gensymed_symbol_2 = Nil;
	  gensymed_symbol_3 = T;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
	  svref_new_value_1 = IFIX(ISVREF(function_definition,
		  (SI_Long)5L)) | (SI_Long)16777216L;
	  ISVREF(function_definition,(SI_Long)5L) = FIX(svref_new_value_1);
      }
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(function_definition,
		  Qfunction_definition_byte_code_body);
      result_1 = SVREF(function_definition,FIX((SI_Long)20L)) = 
	      new_byte_code_body;
      if ( !TRUEP(current_flag_state_qm)) {
	  svref_new_value_1 = IFIX(ISVREF(function_definition,
		  (SI_Long)5L)) &  ~(SI_Long)16777216L;
	  ISVREF(function_definition,(SI_Long)5L) = FIX(svref_new_value_1);
	  gensymed_symbol = 
		  ISVREF(ISVREF(ISVREF(ISVREF(function_definition,
		  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	  gensymed_symbol_1 = function_definition;
	  gensymed_symbol_2 = T;
	  gensymed_symbol_3 = Nil;
	  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_2,gensymed_symbol_3);
      }
      temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_1);
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
	  temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_1);
	  else {
	      temp_2 = M_CDR(frame_and_slot_or_atom);
	      temp_1 = CONSP(temp_2) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_1 ? (EQ(function_definition,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_1 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if ( !temp_1)
	  update_all_representations_of_slot(function_definition,
		  slot_description,Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(function_definition);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_2 = M_CAR(Stack_of_slot_value_changes);
	  temp_1 = ATOM(temp_2);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    return VALUES_1(new_byte_code_body);
}

static Object Qfunction_definition;  /* function-definition */

/* CLEANUP-FOR-FUNCTION-DEFINITION */
Object cleanup_for_function_definition(function_definition)
    Object function_definition;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(154,3);
    frame = function_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qfunction_definition)) {
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
    change_slot_value(3,function_definition,Qbox_translation_and_text,Nil);
    return change_slot_value(3,function_definition,
	    Qfunction_definition_byte_code_body,Nil);
}

static Object Qcm;                 /* \, */

/* COMPILE-UNITS-DECLARATION-FOR-SLOT */
Object compile_units_declaration_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Object temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(154,4);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    temp = CAR(translation);
    if (CONSP(temp) && EQ(CAAR(translation),Qcm))
	return VALUES_1(CDAR(translation));
    else
	return VALUES_1(translation);
}

/* PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-UNITS-OF-MEASURE-DECLARATION */
Object put_box_translation_and_text_slot_value_for_units_of_measure_declaration(units_of_measure_declaration,
	    box_translation_and_text,initial_qm)
    Object units_of_measure_declaration, box_translation_and_text, initial_qm;
{
    Object translation_qm;

    x_note_fn_call(154,5);
    translation_qm =  !EQ(CAR(box_translation_and_text),No_value) ? 
	    CAR(box_translation_and_text) : Nil;
    if (translation_qm) {
	add_units_of_measure(translation_qm);
	update_frame_status(units_of_measure_declaration,Nil,Nil);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(units_of_measure_declaration,
		Qbox_translation_and_text);
    return VALUES_1(SVREF(units_of_measure_declaration,FIX((SI_Long)16L)) 
	    = box_translation_and_text);
}

static Object Qcolumn_of_args;     /* column-of-args */

/* PUT-COLUMN-OF-ARGS */
Object put_column_of_args(tabular_function_of_1_arg,
	    slot_value_list_of_values,gensymed_symbol)
    Object tabular_function_of_1_arg, slot_value_list_of_values;
    Object gensymed_symbol;
{
    Object series_of_values;

    x_note_fn_call(154,6);
    series_of_values = 
	    convert_list_to_series_of_values(slot_value_list_of_values);
    reclaim_series_of_values_and_values(ISVREF(tabular_function_of_1_arg,
	    (SI_Long)24L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,Qcolumn_of_args);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)24L)) = series_of_values;
    reclaim_slot_value_list_1(slot_value_list_of_values);
    return VALUES_2(series_of_values,T);
}

static Object Qcolumn_of_values;   /* column-of-values */

/* PUT-COLUMN-OF-VALUES */
Object put_column_of_values(tabular_function_of_1_arg,
	    slot_value_list_of_values,gensymed_symbol)
    Object tabular_function_of_1_arg, slot_value_list_of_values;
    Object gensymed_symbol;
{
    Object series_of_values;

    x_note_fn_call(154,7);
    series_of_values = 
	    convert_list_to_series_of_values(slot_value_list_of_values);
    reclaim_series_of_values_and_values(ISVREF(tabular_function_of_1_arg,
	    (SI_Long)25L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,Qcolumn_of_values);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)25L)) = series_of_values;
    reclaim_slot_value_list_1(slot_value_list_of_values);
    return VALUES_2(series_of_values,T);
}

/* RECLAIM-COLUMN-OF-ARGS-VALUE */
Object reclaim_column_of_args_value(column_of_args,gensymed_symbol)
    Object column_of_args, gensymed_symbol;
{
    x_note_fn_call(154,8);
    reclaim_series_of_values_and_values(column_of_args);
    return VALUES_1(Nil);
}

/* RECLAIM-COLUMN-OF-VALUES-VALUE */
Object reclaim_column_of_values_value(column_of_values,gensymed_symbol)
    Object column_of_values, gensymed_symbol;
{
    x_note_fn_call(154,9);
    reclaim_series_of_values_and_values(column_of_values);
    return VALUES_1(Nil);
}

static Object Qtabular_function_of_1_arg;  /* tabular-function-of-1-arg */

/* INITIALIZE-AFTER-READING-FOR-TABULAR-FUNCTION-OF-1-ARG */
Object initialize_after_reading_for_tabular_function_of_1_arg(tabular_function_of_1_arg)
    Object tabular_function_of_1_arg;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(154,10);
    frame = tabular_function_of_1_arg;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qtabular_function_of_1_arg)) {
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
    if ( !FIXNUM_GE(Kb_flags,G2_version_6_general_kb_flags))
	return sort_tabular_function_if_necessary(tabular_function_of_1_arg);
    else
	return VALUES_1(Nil);
}

/* TABULAR-FUNCTION-DATUM-EQUAL */
Object tabular_function_datum_equal(datum1,datum2)
    Object datum1, datum2;
{
    Object temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,11);
    temp = EQ(datum1,datum2) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (FIXNUMP(datum1) && FIXNUMP(datum2))
	return VALUES_1(FIXNUM_EQ(datum1,datum2) ? T : Nil);
    else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L && 
	    INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L) {
	temp_1 = aref1(datum1,FIX((SI_Long)0L));
	temp = aref1(datum2,FIX((SI_Long)0L));
	return VALUES_1(NUM_EQ(temp_1,temp) ? T : Nil);
    }
    else if (slot_value_number_p(datum1)) {
	if (slot_value_number_p(datum2)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum1,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp = aref1(datum1,FIX((SI_Long)0L));
		else
		    temp = datum1;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum2,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp_1 = aref1(datum2,FIX((SI_Long)0L));
		else
		    temp_1 = datum2;
		result = VALUES_1(NUM_EQ(temp,temp_1) ? T : Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else if (slot_value_number_p(datum2))
	return VALUES_1(Nil);
    else {
	temp = stringw(datum1);
	return string_equalw(temp,stringw(datum2));
    }
}

/* TABULAR-FUNCTION-PHRASE-DATUM-EQUAL */
Object tabular_function_phrase_datum_equal(phrase,datum)
    Object phrase, datum;
{
    Object temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,12);
    temp = EQ(phrase,datum) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (FIXNUMP(phrase) && FIXNUMP(datum))
	return VALUES_1(FIXNUM_EQ(phrase,datum) ? T : Nil);
    else if (INLINE_LONG_VECTOR_P(phrase) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase)) == (SI_Long)1L && 
	    INLINE_LONG_VECTOR_P(datum) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L) {
	temp_1 = aref1(phrase,FIX((SI_Long)0L));
	temp = aref1(datum,FIX((SI_Long)0L));
	return VALUES_1(NUM_EQ(temp_1,temp) ? T : Nil);
    }
    else if (phrase_number_p(phrase)) {
	if (slot_value_number_p(datum)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase)) == (SI_Long)1L)
		    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(phrase) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase)) == (SI_Long)1L)
		    temp = aref1(phrase,FIX((SI_Long)0L));
		else
		    temp = phrase;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L)
		    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L)
		    temp_1 = aref1(datum,FIX((SI_Long)0L));
		else
		    temp_1 = datum;
		result = VALUES_1(NUM_EQ(temp,temp_1) ? T : Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else if (slot_value_number_p(datum))
	return VALUES_1(Nil);
    else {
	temp = stringw(phrase);
	return string_equalw(temp,stringw(datum));
    }
}

static Object string_constant;     /* "Types of args and values cannot be changed once the table has rows." */

/* COMPILE-TABULAR-FUNCTION-DATA-TYPE-FOR-SLOT */
Object compile_tabular_function_data_type_for_slot varargs_1(int, n)
{
    Object parse_result, tabular_function_of_1_arg, gensymed_symbol;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(154,13);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    tabular_function_of_1_arg = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (IFIX(ISVREF(tabular_function_of_1_arg,(SI_Long)26L)) == (SI_Long)0L)
	return VALUES_1(parse_result);
    else {
	temp = Bad_phrase;
	temp_1 = copy_text_string(string_constant);
	return VALUES_2(temp,temp_1);
    }
}

static Object Qab_no;              /* no */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object string_constant_1;   /* "The sort specification cannot be changed because ~
				    *                 there is an instance of this class with table rows."
				    */

static Object string_constant_2;   /* "The sort specification cannot be so changed once the table has rows." */

/* COMPILE-KEEP-TABULAR-FUNCTION-SORTED?-FOR-SLOT */
Object compile_keep_tabular_function_sorted_qm_for_slot varargs_1(int, n)
{
    Object parse_result, tabular_function_or_class_definition, gensymed_symbol;
    Object sub_class_bit_vector, class_name_qm, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, temp_2, entry_hash, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, scope_conses;
    Object ab_loopvar_, ab_loopvar__1, instance, ab_loop_it_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(154,14);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    tabular_function_or_class_definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qab_no))
	return VALUES_1(Nil);
    else {
	sub_class_bit_vector = 
		ISVREF(ISVREF(tabular_function_or_class_definition,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	if (temp) {
	    class_name_qm = ISVREF(tabular_function_or_class_definition,
		    (SI_Long)20L);
	    if (SYMBOLP(class_name_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_name_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_name_qm) & 
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    gensymed_symbol = class_name_qm;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_2,gensymed_symbol_4);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp = TRUEP(resulting_value);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		instance = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loop_it_ = Nil;
		  ab_loopvar_ = collect_subclasses(class_name_qm);
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
		      temp =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      goto end_loop_13;
		  instance = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  ab_loop_it_ =  !(EQ(ISVREF(instance,(SI_Long)22L),
			  parse_result) || IFIX(ISVREF(instance,
			  (SI_Long)26L)) == (SI_Long)0L) ? T : Nil;
		  if (ab_loop_it_) {
		      temp = TRUEP(ab_loop_it_);
		      goto end_5;
		  }
		  goto next_loop_12;
		end_loop_13:
		  temp = TRUEP(Qnil);
		end_5:;
		POP_SPECIAL();
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = Bad_phrase;
		temp_2 = tformat_text_string(1,string_constant_1);
		return VALUES_2(temp_1,temp_2);
	    }
	    else
		return VALUES_1(parse_result);
	}
	else if (EQ(ISVREF(tabular_function_or_class_definition,
		(SI_Long)22L),parse_result) || 
		IFIX(ISVREF(tabular_function_or_class_definition,
		(SI_Long)26L)) == (SI_Long)0L)
	    return VALUES_1(parse_result);
	else {
	    temp_1 = Bad_phrase;
	    temp_2 = copy_text_string(string_constant_2);
	    return VALUES_2(temp_1,temp_2);
	}
    }
}

static Object string_constant_3;   /* "no" */

static Object Qargs;               /* args */

static Object string_constant_4;   /* "by args" */

static Object string_constant_5;   /* "by values" */

/* WRITE-KEEP-TABULAR-FUNCTION-SORTED?-FROM-SLOT */
Object write_keep_tabular_function_sorted_qm_from_slot(keep_tabular_function_sorted_qm,
	    gensymed_symbol)
    Object keep_tabular_function_sorted_qm, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(154,15);
    if ( !TRUEP(keep_tabular_function_sorted_qm))
	temp = string_constant_3;
    else if (EQ(keep_tabular_function_sorted_qm,Qargs))
	temp = string_constant_4;
    else if (EQ(keep_tabular_function_sorted_qm,Qvalues))
	temp = string_constant_5;
    else
	temp = Qnil;
    return twrite_general_string(temp);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* KEEP-TABULAR-FUNCTION-SORTED?-EVALUATION-SETTER */
Object keep_tabular_function_sorted_qm_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(154,16);
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
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_keep_tabular_function_sorted_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_keep_tabular_function_sorted_qm_evaluation_setter:
    return result;
}

/* KEEP-TABULAR-FUNCTION-SORTED?-EVALUATION-GETTER */
Object keep_tabular_function_sorted_qm_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(154,17);
    temp = slot_value;
    if (temp);
    else
	temp = Qab_no;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object array_constant;      /* # */

/* WRITE-ADD-OR-DELETE-ROWS-FROM-SLOT */
Object write_add_or_delete_rows_from_slot(add_or_delete_rows,gensymed_symbol)
    Object add_or_delete_rows, gensymed_symbol;
{
    x_note_fn_call(154,18);
    return twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)18L));
}

/* TABULAR-FUNCTION-CAR-TESTER */
Object tabular_function_car_tester(pair1,pair2)
    Object pair1, pair2;
{
    Object datum1, datum2, temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,19);
    datum1 = CAR(pair1);
    datum2 = CAR(pair2);
    if (FIXNUMP(datum1) && FIXNUMP(datum2))
	return VALUES_1(FIXNUM_LT(datum1,datum2) ? T : Nil);
    else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L && 
	    INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L) {
	temp = aref1(datum1,FIX((SI_Long)0L));
	temp_1 = aref1(datum2,FIX((SI_Long)0L));
	return VALUES_1(NUM_LT(temp,temp_1) ? T : Nil);
    }
    else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L && 
	    FIXNUMP(datum2)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_1 = aref1(datum1,FIX((SI_Long)0L));
	    result = VALUES_1(NUM_LT(temp_1,datum2) ? T : Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (FIXNUMP(datum1) && INLINE_LONG_VECTOR_P(datum2) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == 
	    (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_1 = aref1(datum2,FIX((SI_Long)0L));
	    result = VALUES_1(NUM_LT(datum1,temp_1) ? T : Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (slot_value_number_p(datum1)) {
	temp_1 =  !TRUEP(slot_value_number_p(datum2)) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum1,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp_1 = aref1(datum1,FIX((SI_Long)0L));
		else
		    temp_1 = datum1;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum2,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp = aref1(datum2,FIX((SI_Long)0L));
		else
		    temp = datum2;
		result = VALUES_1(NUM_LT(temp_1,temp) ? T : Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
    }
    else if (slot_value_number_p(datum2))
	return VALUES_1(Nil);
    else {
	temp_1 = stringw(datum1);
	return string_lesspw(temp_1,stringw(datum2));
    }
}

/* TABULAR-FUNCTION-CDR-TESTER */
Object tabular_function_cdr_tester(pair1,pair2)
    Object pair1, pair2;
{
    Object datum1, datum2, temp, temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,20);
    datum1 = CDR(pair1);
    datum2 = CDR(pair2);
    if (FIXNUMP(datum1) && FIXNUMP(datum2))
	return VALUES_1(FIXNUM_LT(datum1,datum2) ? T : Nil);
    else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L && 
	    INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L) {
	temp = aref1(datum1,FIX((SI_Long)0L));
	temp_1 = aref1(datum2,FIX((SI_Long)0L));
	return VALUES_1(NUM_LT(temp,temp_1) ? T : Nil);
    }
    else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L && 
	    FIXNUMP(datum2)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_1 = aref1(datum1,FIX((SI_Long)0L));
	    result = VALUES_1(NUM_LT(temp_1,datum2) ? T : Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (FIXNUMP(datum1) && INLINE_LONG_VECTOR_P(datum2) != 
	    (SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == 
	    (SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_1 = aref1(datum2,FIX((SI_Long)0L));
	    result = VALUES_1(NUM_LT(datum1,temp_1) ? T : Nil);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (slot_value_number_p(datum1)) {
	temp_1 =  !TRUEP(slot_value_number_p(datum2)) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum1,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum1) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum1)) == (SI_Long)1L)
		    temp_1 = aref1(datum1,FIX((SI_Long)0L));
		else
		    temp_1 = datum1;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(datum2,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(datum2) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum2)) == (SI_Long)1L)
		    temp = aref1(datum2,FIX((SI_Long)0L));
		else
		    temp = datum2;
		result = VALUES_1(NUM_LT(temp_1,temp) ? T : Nil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    return result;
	}
    }
    else if (slot_value_number_p(datum2))
	return VALUES_1(Nil);
    else {
	temp_1 = stringw(datum1);
	return string_lesspw(temp_1,stringw(datum2));
    }
}

/* INITIAL-VALUES-FOR-TABLE-OF-VALUES */
Object initial_values_for_table_of_values(class_1)
    Object class_1;
{
    x_note_fn_call(154,21);
    return VALUES_1(Nil);
}

static Object Qx;                  /* x */

static Object Qf_of_x;             /* f-of-x */

/* GET-VALUES-FOR-TABLE-OF-VALUES */
Object get_values_for_table_of_values(tabular_function_of_1_arg)
    Object tabular_function_of_1_arg;
{
    Object length_1, tabular_args, tabular_values, arg, ab_loop_list_, value;
    Object ab_loop_list__1, tabular_function_eval_list, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(154,22);
    length_1 = ISVREF(tabular_function_of_1_arg,(SI_Long)26L);
    tabular_args = convert_series_of_values_to_list(2,
	    ISVREF(tabular_function_of_1_arg,(SI_Long)24L),length_1);
    tabular_values = convert_series_of_values_to_list(2,
	    ISVREF(tabular_function_of_1_arg,(SI_Long)25L),length_1);
    arg = Nil;
    ab_loop_list_ = tabular_args;
    value = Nil;
    ab_loop_list__1 = tabular_values;
    tabular_function_eval_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    value = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = arg ? (FIXNUMP(arg) || arg && SYMBOLP(arg) ? arg : 
	    copy_evaluation_value_1(arg)) : Qnil;
    ab_loopvar__1 = 
	    eval_cons_1(allocate_evaluation_structure(eval_list_4(Qx,temp,
	    Qf_of_x,value ? (FIXNUMP(value) || value && SYMBOLP(value) ? 
	    value : copy_evaluation_value_1(value)) : Qnil)),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	tabular_function_eval_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    reclaim_slot_value_list_1(tabular_args);
    reclaim_slot_value_list_1(tabular_values);
    temp = allocate_evaluation_sequence(tabular_function_eval_list);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Qnumber_of_rows_in_table;  /* number-of-rows-in-table */

/* SET-VALUES-FOR-TABLE-OF-VALUES */
Object set_values_for_table_of_values(tabular_function_of_1_arg,new_value)
    Object tabular_function_of_1_arg, new_value;
{
    Object current_length, delete_current_value_phrase, gensymed_symbol;
    Object held_vector, arg_value_struct, x_arg, x_of_f_value, new_args;
    Object ab_loopvar_, ab_loopvar__1, new_values, ab_loopvar__2, elt_1;
    Object validated_elt, new_length, sorted_args, sorted_values;
    Object svref_new_value;
    SI_Long next_index, length_1;
    Object result;

    x_note_fn_call(154,23);
    current_length = ISVREF(tabular_function_of_1_arg,(SI_Long)26L);
    delete_current_value_phrase = gensym_list_2(Qdelete,current_length);
    compile_add_or_delete_rows_for_slot(3,delete_current_value_phrase,
	    tabular_function_of_1_arg,T);
    reclaim_gensym_list_1(delete_current_value_phrase);
    gensymed_symbol = new_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    arg_value_struct = Nil;
    x_arg = Nil;
    x_of_f_value = Nil;
    new_args = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    new_values = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    arg_value_struct = validated_elt;
    x_arg = estructure_slot(arg_value_struct,Qx,Nil);
    x_of_f_value = estructure_slot(arg_value_struct,Qf_of_x,Nil);
    ab_loopvar__1 = gensym_cons_1(copy_for_slot_value(x_arg),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	new_args = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    ab_loopvar__1 = gensym_cons_1(copy_for_slot_value(x_of_f_value),Nil);
    if (ab_loopvar__2)
	M_CDR(ab_loopvar__2) = ab_loopvar__1;
    else
	new_values = ab_loopvar__1;
    ab_loopvar__2 = ab_loopvar__1;
    goto next_loop;
  end_loop:
    new_length = length(new_args);
    if (new_args) {
	result = sort_args_or_values_for_tabular_function_if_necessary(tabular_function_of_1_arg,
		new_args,new_values);
	MVS_2(result,sorted_args,sorted_values);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(tabular_function_of_1_arg,Qcolumn_of_args);
	svref_new_value = convert_list_to_series_of_values(sorted_args);
	SVREF(tabular_function_of_1_arg,FIX((SI_Long)24L)) = svref_new_value;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(tabular_function_of_1_arg,
		    Qcolumn_of_values);
	svref_new_value = convert_list_to_series_of_values(sorted_values);
	SVREF(tabular_function_of_1_arg,FIX((SI_Long)25L)) = svref_new_value;
	reclaim_gensym_list_1(sorted_args);
	reclaim_gensym_list_1(sorted_values);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,
		Qnumber_of_rows_in_table);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)26L)) = new_length;
    return VALUES_1(Qnil);
}

static Object Qtabular_function_car_tester;  /* tabular-function-car-tester */

static Object Qtabular_function_cdr_tester;  /* tabular-function-cdr-tester */

/* SORT-ARGS-OR-VALUES-FOR-TABULAR-FUNCTION-IF-NECESSARY */
Object sort_args_or_values_for_tabular_function_if_necessary(tabular_function_of_1_arg,
	    args,values_1)
    Object tabular_function_of_1_arg, args, values_1;
{
    Object l, m, next_m_qm, ab_loop_iter_flag_, temp, temp_1, temp_2;
    Object last_m_qm;

    x_note_fn_call(154,24);
    if (ISVREF(tabular_function_of_1_arg,(SI_Long)22L)) {
	l = values_1;
	m = args;
	next_m_qm = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(l))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    m = next_m_qm;
	next_m_qm = CDR(m);
	temp = CAR(l);
	M_CDR(m) = temp;
	M_CAR(l) = m;
	ab_loop_iter_flag_ = Nil;
	l = M_CDR(l);
	goto next_loop;
      end_loop:;
	temp_1 = values_1;
	temp_2 = ISVREF(tabular_function_of_1_arg,(SI_Long)22L);
	if (EQ(temp_2,Qargs))
	    temp_2 = SYMBOL_FUNCTION(Qtabular_function_car_tester);
	else if (EQ(temp_2,Qvalues))
	    temp_2 = SYMBOL_FUNCTION(Qtabular_function_cdr_tester);
	else
	    temp_2 = Qnil;
	values_1 = sort_list(temp_1,temp_2,Nil);
	args = CAR(values_1);
	last_m_qm = Nil;
	l = values_1;
      next_loop_1:
	if ( !TRUEP(l))
	    goto end_loop_1;
	if (last_m_qm) {
	    temp = CAR(l);
	    M_CDR(last_m_qm) = temp;
	}
	last_m_qm = CAR(l);
	temp = CDR(last_m_qm);
	M_CAR(l) = temp;
	M_CDR(last_m_qm) = Nil;
	l = M_CDR(l);
	goto next_loop_1;
      end_loop_1:;
    }
    return VALUES_2(args,values_1);
}

/* SORT-TABULAR-FUNCTION-IF-NECESSARY */
Object sort_tabular_function_if_necessary(tabular_function_of_1_arg)
    Object tabular_function_of_1_arg;
{
    Object length_1, args, values_1, sorted_args, sorted_values;
    Object result;

    x_note_fn_call(154,25);
    if (ISVREF(tabular_function_of_1_arg,(SI_Long)22L)) {
	length_1 = ISVREF(tabular_function_of_1_arg,(SI_Long)26L);
	args = convert_series_of_values_to_list(3,
		ISVREF(tabular_function_of_1_arg,(SI_Long)24L),length_1,T);
	values_1 = convert_series_of_values_to_list(3,
		ISVREF(tabular_function_of_1_arg,(SI_Long)25L),length_1,T);
	result = sort_args_or_values_for_tabular_function_if_necessary(tabular_function_of_1_arg,
		args,values_1);
	MVS_2(result,sorted_args,sorted_values);
	change_slot_value(3,tabular_function_of_1_arg,Qcolumn_of_args,
		sorted_args);
	return change_slot_value(3,tabular_function_of_1_arg,
		Qcolumn_of_values,sorted_values);
    }
    else
	return VALUES_1(Nil);
}

static Object Qunfinished;         /* unfinished */

static Object Qbeginning;          /* beginning */

static Object list_constant_2;     /* # */

static Object Qafter;              /* after */

static Object Qbefore;             /* before */

static Object Qtabular_function_phrase_datum_equal;  /* tabular-function-phrase-datum-equal */

static Object Qetc_dot;            /* etc. */

static Object Qfloat_array;        /* float-array */

static Object Qtable_of_values;    /* table-of-values */

/* COMPILE-ADD-OR-DELETE-ROWS-FOR-SLOT */
Object compile_add_or_delete_rows_for_slot varargs_1(int, n)
{
    Object parse_result, tabular_function_of_1_arg;
    Object called_from_values_for_table_of_values_virtual_attribute_qm;
    Object length_1, args, values_1, number_of_rows_qm, row_position_qm;
    Object row_position_relation_qm, row_data_qm, arg_data_qm;
    Object arg_data_is_atomic_qm, value_data_qm, position_for_change, x;
    Object arg_or_arg_list, y, ab_loop_list_, temp_1, temp_2;
    Object number_left_to_delete, arg_qm, value_qm, ab_loop_list__1;
    Object delete_this_qm, new_args, ab_loopvar_, ab_loopvar__1, new_values;
    Object ab_loopvar__2, arg_cons_to_insert_after_qm, rest_of_arg_data_qm;
    Object previous_arg_qm, previous_arg_difference_qm;
    Object value_cons_to_insert_after_qm, rest_of_value_data_qm;
    Object previous_value_qm, previous_value_difference_qm;
    Object amf_available_array_cons_qm, amf_array, temp_3, temp_4, amf_result;
    Object new_float, phrase_number, rest_of_arg_data_qm_old_value, new_arg;
    Object rest_of_value_data_qm_old_value, new_value, sorted_args;
    Object sorted_values, tables, table, workspace_qm, image_plane;
    SI_Long i, ab_loop_bind_;
    char delete_case_qm, unfinished_case_qm, temp;
    double aref_new_value;
    Declare_varargs_nonrelocating;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,26);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    tabular_function_of_1_arg = REQUIRED_ARG_nonrelocating();
    called_from_values_for_table_of_values_virtual_attribute_qm = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    length_1 = ISVREF(tabular_function_of_1_arg,(SI_Long)26L);
    args = convert_series_of_values_to_list(2,
	    ISVREF(tabular_function_of_1_arg,(SI_Long)24L),length_1);
    values_1 = convert_series_of_values_to_list(2,
	    ISVREF(tabular_function_of_1_arg,(SI_Long)25L),length_1);
    delete_case_qm = EQ(FIRST(parse_result),Qdelete);
    unfinished_case_qm = EQ(SECOND(parse_result),Qunfinished);
    number_of_rows_qm =  !unfinished_case_qm ? SECOND(parse_result) : Nil;
    row_position_qm = THIRD(parse_result);
    row_position_relation_qm = CONSP(row_position_qm) ? 
	    FIRST(row_position_qm) : Nil;
    row_data_qm = FOURTH(parse_result);
    arg_data_qm = SECOND(row_data_qm);
    arg_data_is_atomic_qm = atomic_phrase_p(arg_data_qm);
    value_data_qm = THIRD(row_data_qm);
    if (EQ(row_position_qm,Qbeginning))
	position_for_change = FIX((SI_Long)0L);
    else if (memq_function(row_position_relation_qm,list_constant_2) || 
	    row_data_qm) {
	if (row_position_relation_qm)
	    x = SECOND(row_position_qm);
	else {
	    arg_or_arg_list = SECOND(row_data_qm);
	    x = atomic_phrase_p(arg_or_arg_list) ? arg_or_arg_list : 
		    SECOND(arg_or_arg_list);
	}
	i = (SI_Long)0L;
	y = Nil;
	ab_loop_list_ = args;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	y = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = TRUEP(tabular_function_datum_equal(x,y));
	if (temp);
	else if (slot_value_number_p(x) && slot_value_number_p(y)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L)
		    temp_1 = aref1(x,FIX((SI_Long)0L));
		else
		    temp_1 = x;
		if (INLINE_DOUBLE_FLOAT_VECTOR_P(y) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
		    temp_2 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(y,
			    (SI_Long)0L));
		else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == (SI_Long)1L)
		    temp_2 = aref1(y,FIX((SI_Long)0L));
		else
		    temp_2 = y;
		temp = NUM_LT(temp_1,temp_2);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if (EQ(row_position_relation_qm,Qafter)) {
		temp =  !TRUEP(slot_value_number_p(x));
		if (temp);
		else
		    temp =  !TRUEP(slot_value_number_p(y));
		if (temp);
		else {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L 
				&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == 
				(SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(x,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == 
				(SI_Long)1L)
			    temp_1 = aref1(x,FIX((SI_Long)0L));
			else
			    temp_1 = x;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(y) != (SI_Long)0L 
				&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == 
				(SI_Long)1L)
			    temp_2 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(y,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(y) != (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(y)) == 
				(SI_Long)1L)
			    temp_2 = aref1(y,FIX((SI_Long)0L));
			else
			    temp_2 = y;
			temp = NUM_EQ(temp_1,temp_2);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if ( !TRUEP(number_of_rows_qm))
		    number_of_rows_qm = FIX((SI_Long)1L);
		position_for_change = FIX(i + (SI_Long)1L);
	    }
	    else if (EQ(row_position_relation_qm,Qbefore) && delete_case_qm) {
		if (unfinished_case_qm ||  !TRUEP(number_of_rows_qm)) {
		    number_of_rows_qm = FIX((SI_Long)1L);
		    position_for_change = FIX(i - (SI_Long)1L);
		}
		else
		    position_for_change = FIX(i - IFIX(number_of_rows_qm));
	    }
	    else
		position_for_change = FIX(i);
	    goto end_1;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	position_for_change = length_1;
	goto end_1;
	position_for_change = Qnil;
      end_1:;
    }
    else
	position_for_change = delete_case_qm ? (unfinished_case_qm ||  
		!TRUEP(number_of_rows_qm) ? FIX((SI_Long)0L) : 
		FIXNUM_MINUS(length_1,number_of_rows_qm)) : length_1;
    if (delete_case_qm) {
	number_left_to_delete = number_of_rows_qm;
	if (number_left_to_delete);
	else
	    number_left_to_delete = unfinished_case_qm || row_position_qm ?
		     length_1 : FIX((SI_Long)1L);
	i = (SI_Long)0L;
	arg_qm = Nil;
	ab_loop_list_ = args;
	value_qm = Nil;
	ab_loop_list__1 = values_1;
	delete_this_qm = Nil;
	new_args = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	new_values = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__1 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	arg_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	value_qm = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (IFIX(number_left_to_delete) > (SI_Long)0L && i >= 
		IFIX(position_for_change) && ( !unfinished_case_qm ||  
		!TRUEP(arg_qm) ||  !TRUEP(value_qm))) {
	    temp_1 =  !TRUEP(row_data_qm) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 = arg_data_is_atomic_qm ? 
			tabular_function_phrase_datum_equal(arg_qm,
			arg_data_qm) : member(4,arg_qm,arg_data_qm,Ktest,
			SYMBOL_FUNCTION(Qtabular_function_phrase_datum_equal));
	    delete_this_qm = temp_1;
	}
	else
	    delete_this_qm = Nil;
	if ( !TRUEP(delete_this_qm)) {
	    ab_loopvar__1 = slot_value_cons_1(arg_qm,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		new_args = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	if ( !TRUEP(delete_this_qm)) {
	    ab_loopvar__1 = slot_value_cons_1(value_qm,Nil);
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__1;
	    else
		new_values = ab_loopvar__1;
	    ab_loopvar__2 = ab_loopvar__1;
	}
	if (delete_this_qm) {
	    number_left_to_delete = FIXNUM_SUB1(number_left_to_delete);
	    reclaim_slot_value(arg_qm);
	    reclaim_slot_value(value_qm);
	}
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	reclaim_slot_value_list_1(args);
	args = new_args;
	reclaim_slot_value_list_1(values_1);
	values_1 = new_values;
    }
    else {
	arg_cons_to_insert_after_qm =  !(IFIX(position_for_change) == 
		(SI_Long)0L) ? nthcdr(FIXNUM_SUB1(position_for_change),
		args) : Nil;
	rest_of_arg_data_qm =  !TRUEP(arg_data_is_atomic_qm) ? 
		CDR(arg_data_qm) : Nil;
	previous_arg_qm = Nil;
	previous_arg_difference_qm = Nil;
	value_cons_to_insert_after_qm = arg_cons_to_insert_after_qm ? 
		nthcdr(FIXNUM_SUB1(position_for_change),values_1) : Nil;
	rest_of_value_data_qm =  !TRUEP(atomic_phrase_p(value_data_qm)) ? 
		CDR(value_data_qm) : Nil;
	previous_value_qm = Nil;
	previous_value_difference_qm = Nil;
	i = (SI_Long)1L;
	temp_1 = number_of_rows_qm;
	if (temp_1);
	else
	    temp_1 =  !TRUEP(arg_data_is_atomic_qm) ? 
		    length(CDR(arg_data_qm)) : Nil;
	if (temp_1);
	else
	    temp_1 = FIX((SI_Long)1L);
	ab_loop_bind_ = IFIX(temp_1);
	new_args = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	new_values = Nil;
	ab_loopvar__2 = Nil;
	ab_loopvar__1 = Nil;
      next_loop_2:
	if (i > ab_loop_bind_)
	    goto end_loop_2;
	if (arg_data_is_atomic_qm)
	    previous_arg_qm = arg_data_qm;
	else if (EQ(CAR(rest_of_arg_data_qm),Qetc_dot)) {
	    if (previous_arg_difference_qm) {
		if (FIXNUMP(previous_arg_qm) && 
			FIXNUMP(previous_arg_difference_qm))
		    previous_arg_qm = FIXNUM_ADD(previous_arg_qm,
			    previous_arg_difference_qm);
		else {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_3 = Vector_of_simple_float_array_pools;
			    temp_4 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_3 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_3) = amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_3 = Available_float_array_conses_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_arg_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_qm)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_arg_qm,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(previous_arg_qm) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_qm)) 
				== (SI_Long)1L)
			    temp_1 = aref1(previous_arg_qm,FIX((SI_Long)0L));
			else
			    temp_1 = previous_arg_qm;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_arg_difference_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_difference_qm)) 
				== (SI_Long)1L)
			    temp_2 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_arg_difference_qm,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(previous_arg_difference_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_difference_qm)) 
				== (SI_Long)1L)
			    temp_2 = aref1(previous_arg_difference_qm,
				    FIX((SI_Long)0L));
			else
			    temp_2 = previous_arg_difference_qm;
			temp_1 = add(temp_1,temp_2);
			aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			previous_arg_qm = 
				note_use_of_managed_float_in_phrase(new_float);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
	    }
	}
	else {
	    if (FIXNUMP(CAR(rest_of_arg_data_qm)) && FIXNUMP(previous_arg_qm))
		previous_arg_difference_qm = 
			FIXNUM_MINUS(CAR(rest_of_arg_data_qm),previous_arg_qm);
	    else if (phrase_number_p(CAR(rest_of_arg_data_qm)) && 
		    phrase_number_p(previous_arg_qm)) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_3 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_3 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_3) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_3 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		    phrase_number = CAR(rest_of_arg_data_qm);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = aref1(phrase_number,FIX((SI_Long)0L));
		    else
			temp_1 = phrase_number;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_arg_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_qm)) 
			    == (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_arg_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(previous_arg_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_arg_qm)) 
			    == (SI_Long)1L)
			temp_2 = aref1(previous_arg_qm,FIX((SI_Long)0L));
		    else
			temp_2 = previous_arg_qm;
		    temp_1 = minus(temp_1,temp_2);
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    previous_arg_difference_qm = 
			    note_use_of_managed_float_in_phrase(new_float);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else
		previous_arg_difference_qm = Qnil;
	    rest_of_arg_data_qm_old_value = rest_of_arg_data_qm;
	    temp_1 = FIRST(rest_of_arg_data_qm_old_value);
	    rest_of_arg_data_qm = REST(rest_of_arg_data_qm_old_value);
	    previous_arg_qm = temp_1;
	}
	new_arg = previous_arg_qm;
	ab_loopvar__1 = slot_value_cons_1(copy_for_slot_value(new_arg),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    new_args = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	if (atomic_phrase_p(value_data_qm))
	    previous_value_qm = value_data_qm;
	else if (EQ(CAR(rest_of_value_data_qm),Qetc_dot)) {
	    if (previous_value_difference_qm) {
		if (FIXNUMP(previous_value_qm) && 
			FIXNUMP(previous_value_difference_qm))
		    previous_value_qm = FIXNUM_ADD(previous_value_qm,
			    previous_value_difference_qm);
		else {
		    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			amf_available_array_cons_qm = 
				ISVREF(Vector_of_simple_float_array_pools,
				(SI_Long)1L);
			if (amf_available_array_cons_qm) {
			    amf_array = M_CAR(amf_available_array_cons_qm);
			    temp_3 = Vector_of_simple_float_array_pools;
			    temp_4 = M_CDR(amf_available_array_cons_qm);
			    SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			    inline_note_reclaim_cons(amf_available_array_cons_qm,
				    Qfloat_array);
			    if (ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index))) {
				temp_3 = 
					ISVREF(Available_float_array_conses_tail_vector,
					IFIX(Current_thread_index));
				M_CDR(temp_3) = amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
			    }
			    else {
				temp_3 = Available_float_array_conses_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
				temp_3 = 
					Available_float_array_conses_tail_vector;
				temp_4 = Current_thread_index;
				SVREF(temp_3,temp_4) = 
					amf_available_array_cons_qm;
			    }
			    M_CDR(amf_available_array_cons_qm) = Nil;
			    amf_result = amf_array;
			}
			else {
			    atomic_incff_symval(Qcreated_simple_float_array_pool_arrays,
				    FIX((SI_Long)1L));
			    atomic_incff_symval(Qsimple_float_array_pool_memory_usage,
				    bytes_per_double_float_simple_array(FIX((SI_Long)1L)));
			    amf_result = 
				    generate_float_vector(FIX((SI_Long)1L));
			}
			new_float = amf_result;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_value_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_qm)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_value_qm,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(previous_value_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_qm)) 
				== (SI_Long)1L)
			    temp_1 = aref1(previous_value_qm,FIX((SI_Long)0L));
			else
			    temp_1 = previous_value_qm;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_value_difference_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_difference_qm)) 
				== (SI_Long)1L)
			    temp_2 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_value_difference_qm,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(previous_value_difference_qm) 
				!= (SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_difference_qm)) 
				== (SI_Long)1L)
			    temp_2 = aref1(previous_value_difference_qm,
				    FIX((SI_Long)0L));
			else
			    temp_2 = previous_value_difference_qm;
			temp_1 = add(temp_1,temp_2);
			aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
			DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
			previous_value_qm = 
				note_use_of_managed_float_in_phrase(new_float);
		    }
		    POP_LOCAL_ALLOCATION(0,0);
		}
	    }
	}
	else {
	    if (FIXNUMP(CAR(rest_of_value_data_qm)) && 
		    FIXNUMP(previous_value_qm))
		previous_value_difference_qm = 
			FIXNUM_MINUS(CAR(rest_of_value_data_qm),
			previous_value_qm);
	    else if (phrase_number_p(CAR(rest_of_value_data_qm)) && 
		    phrase_number_p(previous_value_qm)) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_3 = Vector_of_simple_float_array_pools;
			temp_4 = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qfloat_array);
			if (ISVREF(Available_float_array_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp_3 = 
				    ISVREF(Available_float_array_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp_3) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			}
			else {
			    temp_3 = Available_float_array_conses_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
			    temp_3 = Available_float_array_conses_tail_vector;
			    temp_4 = Current_thread_index;
			    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
		    phrase_number = CAR(rest_of_value_data_qm);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = aref1(phrase_number,FIX((SI_Long)0L));
		    else
			temp_1 = phrase_number;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(previous_value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_qm)) 
			    == (SI_Long)1L)
			temp_2 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(previous_value_qm,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(previous_value_qm) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(previous_value_qm)) 
			    == (SI_Long)1L)
			temp_2 = aref1(previous_value_qm,FIX((SI_Long)0L));
		    else
			temp_2 = previous_value_qm;
		    temp_1 = minus(temp_1,temp_2);
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    previous_value_difference_qm = 
			    note_use_of_managed_float_in_phrase(new_float);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else
		previous_value_difference_qm = Qnil;
	    rest_of_value_data_qm_old_value = rest_of_value_data_qm;
	    temp_1 = FIRST(rest_of_value_data_qm_old_value);
	    rest_of_value_data_qm = REST(rest_of_value_data_qm_old_value);
	    previous_value_qm = temp_1;
	}
	new_value = previous_value_qm;
	ab_loopvar__1 = slot_value_cons_1(copy_for_slot_value(new_value),Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__1;
	else
	    new_values = ab_loopvar__1;
	ab_loopvar__2 = ab_loopvar__1;
	i = i + (SI_Long)1L;
	goto next_loop_2;
      end_loop_2:
	if (arg_cons_to_insert_after_qm) {
	    temp_3 = nconc2(new_args,CDR(arg_cons_to_insert_after_qm));
	    M_CDR(arg_cons_to_insert_after_qm) = temp_3;
	}
	else
	    args = nconc2(new_args,args);
	if (value_cons_to_insert_after_qm) {
	    temp_3 = nconc2(new_values,CDR(value_cons_to_insert_after_qm));
	    M_CDR(value_cons_to_insert_after_qm) = temp_3;
	}
	else
	    values_1 = nconc2(new_values,values_1);
	result = sort_args_or_values_for_tabular_function_if_necessary(tabular_function_of_1_arg,
		args,values_1);
	MVS_2(result,sorted_args,sorted_values);
	args = sorted_args;
	values_1 = sorted_values;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,
		Qnumber_of_rows_in_table);
    temp_3 = length(args);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)26L)) = temp_3;
    reclaim_series_of_values(ISVREF(tabular_function_of_1_arg,(SI_Long)24L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,Qcolumn_of_args);
    temp_3 = convert_list_to_series_of_values(args);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)24L)) = temp_3;
    reclaim_slot_value_list_1(args);
    reclaim_series_of_values(ISVREF(tabular_function_of_1_arg,(SI_Long)25L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(tabular_function_of_1_arg,Qcolumn_of_values);
    temp_3 = convert_list_to_series_of_values(values_1);
    SVREF(tabular_function_of_1_arg,FIX((SI_Long)25L)) = temp_3;
    reclaim_slot_value_list_1(values_1);
    tables = copy_for_slot_value(ISVREF(tabular_function_of_1_arg,
	    (SI_Long)9L));
    table = Nil;
    ab_loop_list_ = tables;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    table = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(ISVREF(table,(SI_Long)1L),(SI_Long)1L),Qtable_of_values)) {
	workspace_qm = get_workspace_if_any(table);
	image_plane = Nil;
	ab_loop_list__1 = workspace_qm ? ISVREF(workspace_qm,(SI_Long)16L) 
		: Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_4;
	image_plane = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( 
		!TRUEP(called_from_values_for_table_of_values_virtual_attribute_qm))
	    put_up_table_of_values(tabular_function_of_1_arg,
		    FIX(IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)19L),
		    ISVREF(image_plane,(SI_Long)21L))) >>  -  - 
		    (SI_Long)1L),ISVREF(image_plane,(SI_Long)20L));
	goto next_loop_4;
      end_loop_4:;
	delete_frame(table);
    }
    goto next_loop_3;
  end_loop_3:
    reclaim_slot_value_list_1(tables);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

static Object string_constant_6;   /* "~s" */

/* WRITE-TABULAR-FUNCTION-DATA-TYPE-FROM-SLOT */
Object write_tabular_function_data_type_from_slot(tabular_function_data_type,
	    gensymed_symbol)
    Object tabular_function_data_type, gensymed_symbol;
{
    Object temp;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(154,27);
    if ( !TRUEP(tabular_function_data_type))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)4L));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tabular_function_data_type) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tabular_function_data_type)) == 
	    (SI_Long)1L || FLOATP(tabular_function_data_type)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(tabular_function_data_type) 
		    != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tabular_function_data_type)) 
		    == (SI_Long)1L)
		temp = 
			DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(tabular_function_data_type,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(tabular_function_data_type) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tabular_function_data_type)) 
		    == (SI_Long)1L)
		temp = aref1(tabular_function_data_type,FIX((SI_Long)0L));
	    else
		temp = tabular_function_data_type;
	    result = write_floating_point_number_simple_c_format(1,temp);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else if (INLINE_LONG_VECTOR_P(tabular_function_data_type) != 
	    (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tabular_function_data_type)) == 
	    (SI_Long)1L)
	return write_evaluation_value(1,tabular_function_data_type);
    else if (SYMBOLP(tabular_function_data_type))
	return twrite_symbol(1,tabular_function_data_type);
    else if (text_string_p(tabular_function_data_type))
	return tformat(2,string_constant_6,tabular_function_data_type);
    else
	return twrite(tabular_function_data_type);
}

static Object Qclass_format;       /* class-format */

static Object Qfont_for_attribute_tables;  /* font-for-attribute-tables */

static Object Qattribute_value_format;  /* attribute-value-format */

static Object list_constant_3;     /* # */

static Object array_constant_2;    /* # */

static Object Qadd_or_delete_rows;  /* add-or-delete-rows */

static Object array_constant_3;    /* # */

static Object Qf;                  /* f */

static Object string_constant_7;   /* " ~(~A~) (x)" */

static Object Qattributes_table_format;  /* attributes-table-format */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qstretch_new_image_planes_for_caption_p;  /* stretch-new-image-planes-for-caption-p */

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qwide_string;        /* wide-string */

static Object string_constant_8;   /* "Table of values" */

static Object Qab_slot_value;      /* slot-value */

/* PUT-UP-TABLE-OF-VALUES */
Object put_up_table_of_values(tabular_function_of_1_arg,x_in_window,
	    y_in_window)
    Object tabular_function_of_1_arg, x_in_window, y_in_window;
{
    Object class_format, attribute_value_format, column_of_args;
    Object column_of_values, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object text_cell, text_cell_1, table_rows, temp, temp_1, temp_2, temp_3;
    Object table_of_values, workspace, wide_string_bv16, new_wide_string;
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_4, temp_5, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, new_cons, svref_new_value, gensymed_symbol;
    Object short_string;
    SI_Long i, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_special(5);

    x_note_fn_call(154,28);
    class_format = choose_font_format_per_fonts_table(Qclass_format,
	    Qfont_for_attribute_tables);
    attribute_value_format = 
	    choose_font_format_per_fonts_table(Qattribute_value_format,
	    Qfont_for_attribute_tables);
    column_of_args = ISVREF(tabular_function_of_1_arg,(SI_Long)24L);
    column_of_values = ISVREF(tabular_function_of_1_arg,(SI_Long)25L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(tabular_function_of_1_arg,(SI_Long)26L));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    text_cell = make_text_cell(2,
	    make_text_representation_for_slot_value_itself(tabular_function_of_1_arg,
	    ISVREF(nth(ash(FIX(i),FIX((SI_Long)-6L)),column_of_args),i & 
	    (SI_Long)63L),list_constant_3),attribute_value_format);
    note_slot_represented_by_text_cell(text_cell,tabular_function_of_1_arg,
	    FIX( - i - (SI_Long)1L),Nil);
    text_cell_1 = make_text_cell(2,
	    make_text_representation_for_slot_value_itself(tabular_function_of_1_arg,
	    ISVREF(nth(ash(FIX(i),FIX((SI_Long)-6L)),column_of_values),i & 
	    (SI_Long)63L),list_constant_3),attribute_value_format);
    note_slot_represented_by_text_cell(text_cell_1,
	    tabular_function_of_1_arg,FIX(i),Nil);
    ab_loopvar__2 = slot_value_cons_1(slot_value_list_2(text_cell,
	    text_cell_1),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    table_rows = ab_loopvar_;
    goto end_1;
    table_rows = Qnil;
  end_1:;
    temp =  !TRUEP(New_g2_classic_ui_p) ? 
	    slot_value_cons_1(slot_value_list_2(Nil,make_text_cell(2,
	    slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_2,
	    FIX((SI_Long)15L)),Nil),class_format)),Nil) : Nil;
    temp_1 = slot_value_list_2(Nil,make_text_cell_for_slot(5,
	    tabular_function_of_1_arg,Qadd_or_delete_rows,Nil,
	    get_type_of_slot_if_any(3,tabular_function_of_1_arg,
	    Qadd_or_delete_rows,Nil),attribute_value_format));
    temp_2 = make_text_cell(2,
	    slot_value_cons_1(copy_constant_wide_string_given_length(array_constant_3,
	    FIX((SI_Long)3L)),Nil),attribute_value_format);
    temp_3 = get_primary_name_for_frame_if_any(tabular_function_of_1_arg);
    if (temp_3);
    else
	temp_3 = Qf;
    temp_3 = nconc2(temp,nconc2(slot_value_list_2(temp_1,
	    slot_value_list_2(temp_2,make_text_cell(2,
	    slot_value_cons_1(tformat_text_string(2,string_constant_7,
	    temp_3),Nil),attribute_value_format))),table_rows));
    table_of_values = make_or_reformat_table(5,temp_3,New_g2_classic_ui_p ?
	     get_ui_parameter(1,Qattributes_table_format) : 
	    Qattributes_table_format,Nil,Qtable_of_values,T);
    add_frame_representation_if_necessary(table_of_values,
	    tabular_function_of_1_arg);
    workspace = make_workspace(4,Qtemporary_workspace,Nil,table_of_values,
	    FIX((SI_Long)2L));
    if (New_g2_classic_ui_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,
		    Qstretch_new_image_planes_for_caption_p);
	set_lookup_slot_value_1(workspace,
		Qstretch_new_image_planes_for_caption_p,T);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(workspace,Qtitle_bar_caption_text);
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  current_wide_string = new_wide_string;
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
		  tformat(1,string_constant_8);
		  temp_4 = Current_wide_string;
		  temp_5 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_4));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(temp_5) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp_4,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(temp_5) >>  -  - 
			  (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp_4,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp_4,IFIX(temp_5),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list_ = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	string_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_4 = Available_slot_value_conses_vector;
	    temp_5 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_4,temp_5) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_4 = Available_slot_value_conses_tail_vector;
		temp_5 = Current_thread_index;
		SVREF(temp_4,temp_5) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp_4 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol) = temp_4;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_4 = Available_slot_value_conses_vector;
	    temp_5 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_4,temp_5) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_4 = Available_slot_value_conses_tail_vector;
		temp_5 = Current_thread_index;
		SVREF(temp_4,temp_5) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp_4 = short_string;
	}
	else
	    temp_4 = string_1;
	M_CAR(gensymed_symbol) = temp_4;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp_3 = ab_loopvar_;
	goto end_2;
	temp_3 = Qnil;
      end_2:;
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
	set_lookup_slot_value_1(workspace,Qtitle_bar_caption_text,temp_3);
    }
    return post_workspace_in_pane_function(workspace,
	    Current_workstation_detail_pane,x_in_window,y_in_window,Nil,
	    Nil,Nil,Nil,Nil,Nil);
}

static Object float_constant;      /* 0.0 */

/* COMPUTE-VALUE-OF-TABULAR-FUNCTION-IF-ANY */
Object compute_value_of_tabular_function_if_any(tabular_function_of_1_arg,arg)
    Object tabular_function_of_1_arg, arg;
{
    Object column_of_args, i, j, k, arg_k, temp, temp_1, series_of_values;
    Object arg_j, column_of_values, value_k, value_j, arg_k_as_gensym_float;
    Object denominator_1, temp_2, temp_3;
    SI_Long k_1, ab_loop_bind_, i_1;
    char temp_4;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(154,29);
    if (IFIX(ISVREF(tabular_function_of_1_arg,(SI_Long)26L)) == (SI_Long)0L)
	return VALUES_1(Nil);
    else if (EQ(ISVREF(tabular_function_of_1_arg,(SI_Long)22L),Qargs)) {
	column_of_args = ISVREF(tabular_function_of_1_arg,(SI_Long)24L);
	i = FIX((SI_Long)0L);
	j = ISVREF(tabular_function_of_1_arg,(SI_Long)26L);
	k = Nil;
	arg_k = Nil;
      next_loop:
	k = FIX(IFIX(FIXNUM_ADD(i,j)) >>  -  - (SI_Long)1L);
	arg_k = SVREF(nth(ash(k,FIX((SI_Long)-6L)),column_of_args),
		logand(k,FIX((SI_Long)63L)));
	if (FIXNUM_EQ(k,i))
	    goto end_loop;
	if (FIXNUMP(arg) && FIXNUMP(arg_k))
	    temp = FIXNUM_LT(arg,arg_k) ? T : Nil;
	else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == (SI_Long)1L && 
		INLINE_LONG_VECTOR_P(arg_k) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == (SI_Long)1L) {
	    temp_1 = aref1(arg,FIX((SI_Long)0L));
	    temp = aref1(arg_k,FIX((SI_Long)0L));
	    temp = NUM_LT(temp_1,temp) ? T : Nil;
	}
	else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == (SI_Long)1L && 
		FIXNUMP(arg_k)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		temp = aref1(arg,FIX((SI_Long)0L));
		temp = NUM_LT(temp,arg_k) ? T : Nil;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (FIXNUMP(arg) && INLINE_LONG_VECTOR_P(arg_k) != 
		(SI_Long)0L && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
		(SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		temp = aref1(arg_k,FIX((SI_Long)0L));
		temp = NUM_LT(arg,temp) ? T : Nil;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else if (slot_value_number_p(arg)) {
	    temp =  !TRUEP(slot_value_number_p(arg_k)) ? T : Nil;
	    if (temp);
	    else {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
			    (SI_Long)1L)
			temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
			    (SI_Long)1L)
			temp = aref1(arg,FIX((SI_Long)0L));
		    else
			temp = arg;
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg_k) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg_k,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(arg_k) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L)
			temp_1 = aref1(arg_k,FIX((SI_Long)0L));
		    else
			temp_1 = arg_k;
		    temp = NUM_LT(temp,temp_1) ? T : Nil;
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	}
	else if (slot_value_number_p(arg_k))
	    temp = Nil;
	else {
	    temp = stringw(arg);
	    temp = string_lesspw(temp,stringw(arg_k));
	}
	if (temp)
	    j = k;
	else
	    i = k;
	goto next_loop;
      end_loop:
	if (tabular_function_datum_equal(arg,arg_k)) {
	    series_of_values = ISVREF(tabular_function_of_1_arg,(SI_Long)25L);
	    i = k;
	    return VALUES_1(SVREF(nth(ash(i,FIX((SI_Long)-6L)),
		    series_of_values),logand(i,FIX((SI_Long)63L))));
	}
	else {
	    if (ISVREF(tabular_function_of_1_arg,(SI_Long)23L) && 
		    slot_value_number_p(arg) && slot_value_number_p(arg_k)) {
		temp_4 = IFIX(k) > (SI_Long)0L;
		if (temp_4);
		else {
		    if (FIXNUMP(arg) && FIXNUMP(arg_k))
			temp = FIXNUM_LT(arg,arg_k) ? T : Nil;
		    else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
			    (SI_Long)1L && INLINE_LONG_VECTOR_P(arg_k) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L) {
			temp_1 = aref1(arg,FIX((SI_Long)0L));
			temp = aref1(arg_k,FIX((SI_Long)0L));
			temp = NUM_LT(temp_1,temp) ? T : Nil;
		    }
		    else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
			    (SI_Long)1L && FIXNUMP(arg_k)) {
			if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			    temp = aref1(arg,FIX((SI_Long)0L));
			    temp = NUM_LT(temp,arg_k) ? T : Nil;
			}
			POP_LOCAL_ALLOCATION(0,0);
		    }
		    else if (FIXNUMP(arg) && INLINE_LONG_VECTOR_P(arg_k) 
			    != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L) {
			if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
			    temp = aref1(arg_k,FIX((SI_Long)0L));
			    temp = NUM_LT(arg,temp) ? T : Nil;
			}
			POP_LOCAL_ALLOCATION(0,0);
		    }
		    else if (slot_value_number_p(arg)) {
			temp =  !TRUEP(slot_value_number_p(arg_k)) ? T : Nil;
			if (temp);
			else {
			    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg) != 
					(SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) 
					== (SI_Long)1L)
				    temp = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(arg) != 
					(SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) 
					== (SI_Long)1L)
				    temp = aref1(arg,FIX((SI_Long)0L));
				else
				    temp = arg;
				if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg_k) != 
					(SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) 
					== (SI_Long)1L)
				    temp_1 = 
					    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg_k,
					    (SI_Long)0L));
				else if (INLINE_LONG_VECTOR_P(arg_k) != 
					(SI_Long)0L && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) 
					== (SI_Long)1L)
				    temp_1 = aref1(arg_k,FIX((SI_Long)0L));
				else
				    temp_1 = arg_k;
				temp = NUM_LT(temp,temp_1) ? T : Nil;
			    }
			    POP_LOCAL_ALLOCATION(0,0);
			}
		    }
		    else if (slot_value_number_p(arg_k))
			temp = Nil;
		    else {
			temp = stringw(arg);
			temp = string_lesspw(temp,stringw(arg_k));
		    }
		    temp_4 =  !TRUEP(temp);
		}
	    }
	    else
		temp_4 = TRUEP(Nil);
	    if (temp_4 ? FIXNUM_LT(j,ISVREF(tabular_function_of_1_arg,
		    (SI_Long)26L)) : TRUEP(Nil)) {
		arg_j = SVREF(nth(ash(j,FIX((SI_Long)-6L)),column_of_args),
			logand(j,FIX((SI_Long)63L)));
		column_of_values = ISVREF(tabular_function_of_1_arg,
			(SI_Long)25L);
		value_k = SVREF(nth(ash(k,FIX((SI_Long)-6L)),
			column_of_values),logand(k,FIX((SI_Long)63L)));
		value_j = SVREF(nth(ash(j,FIX((SI_Long)-6L)),
			column_of_values),logand(j,FIX((SI_Long)63L)));
		if (slot_value_number_p(arg_j) && 
			slot_value_number_p(value_k) && 
			slot_value_number_p(value_j)) {
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg_k) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg_k,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(arg_k) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_k)) == 
			    (SI_Long)1L)
			temp = aref1(arg_k,FIX((SI_Long)0L));
		    else
			temp = arg_k;
		    arg_k_as_gensym_float = lfloat(temp,float_constant);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg_j) != (SI_Long)0L 
			    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_j)) == 
			    (SI_Long)1L)
			temp = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg_j,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(arg_j) != (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg_j)) == 
			    (SI_Long)1L)
			temp = aref1(arg_j,FIX((SI_Long)0L));
		    else
			temp = arg_j;
		    denominator_1 = minus(temp,arg_k_as_gensym_float);
		    temp = FIX((SI_Long)0L);
		    if ( !NUM_EQ(denominator_1,temp)) {
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_k) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_k)) 
				== (SI_Long)1L)
			    temp_1 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_k,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(value_k) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_k)) 
				== (SI_Long)1L)
			    temp_1 = aref1(value_k,FIX((SI_Long)0L));
			else
			    temp_1 = value_k;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(arg) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
				(SI_Long)1L)
			    temp = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(arg,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(arg) != (SI_Long)0L 
				&& IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) == 
				(SI_Long)1L)
			    temp = aref1(arg,FIX((SI_Long)0L));
			else
			    temp = arg;
			temp = divide(minus(temp,arg_k_as_gensym_float),
				denominator_1);
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_j) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_j)) 
				== (SI_Long)1L)
			    temp_2 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_j,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(value_j) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_j)) 
				== (SI_Long)1L)
			    temp_2 = aref1(value_j,FIX((SI_Long)0L));
			else
			    temp_2 = value_j;
			if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_k) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_k)) 
				== (SI_Long)1L)
			    temp_3 = 
				    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(value_k,
				    (SI_Long)0L));
			else if (INLINE_LONG_VECTOR_P(value_k) != 
				(SI_Long)0L && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_k)) 
				== (SI_Long)1L)
			    temp_3 = aref1(value_k,FIX((SI_Long)0L));
			else
			    temp_3 = value_k;
			return add(temp_1,ltimes(temp,minus(temp_2,
				lfloat(temp_3,float_constant))));
		    }
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
	return VALUES_1(Qnil);
    }
    else {
	column_of_args = ISVREF(tabular_function_of_1_arg,(SI_Long)24L);
	k_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(tabular_function_of_1_arg,(SI_Long)26L));
      next_loop_1:
	if (k_1 >= ab_loop_bind_)
	    goto end_loop_1;
	if (tabular_function_datum_equal(ISVREF(nth(ash(FIX(k_1),
		FIX((SI_Long)-6L)),column_of_args),k_1 & (SI_Long)63L),arg)) {
	    series_of_values = ISVREF(tabular_function_of_1_arg,(SI_Long)25L);
	    i_1 = k_1;
	    return VALUES_1(ISVREF(nth(ash(FIX(i_1),FIX((SI_Long)-6L)),
		    series_of_values),i_1 & (SI_Long)63L));
	}
	k_1 = k_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

void functions_INIT()
{
    Object temp, temp_1, temp_2;
    Object keep_tabular_function_sorted_qm_evaluation_setter_1;
    Object keep_tabular_function_sorted_qm_evaluation_getter_1;
    Object AB_package, list_constant_7, Qtabular_function_data_type;
    Object string_constant_53, list_constant_17, string_constant_52;
    Object string_constant_51, Qtable_item, Qslot_value_writer;
    Object Qwrite_tabular_function_data_type_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_add_or_delete_rows_for_slot;
    Object Qset_values_for_table_of_values, Qget_values_for_table_of_values;
    Object Qinitial_values_for_table_of_values, list_constant_16;
    Object list_constant_15, Qvalues_for_table_of_values, list_constant_14;
    Object list_constant_13, Qab_structure, list_constant_12, list_constant_11;
    Object list_constant_10, list_constant_9, Qtext, Qlong, list_constant_8;
    Object Qab_or, Qno_item, Qab_class, Qvirtual_attributes_local_to_class;
    Object Qwrite_add_or_delete_rows_from_slot;
    Object Qkeep_tabular_function_sorted_qm, Qnamed;
    Object Qtype_specification_simple_expansion;
    Object Qwrite_keep_tabular_function_sorted_qm_from_slot;
    Object Qcompile_keep_tabular_function_sorted_qm_for_slot;
    Object Qcompile_tabular_function_data_type_for_slot, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42;
    Object Qsimplify_associative_operation, Qend, Qclasses_which_define;
    Object Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_tabular_function_of_1_arg;
    Object Qslot_value_reclaimer, Qreclaim_column_of_values_value;
    Object Qreclaim_column_of_args_value, Qslot_putter, Qput_column_of_values;
    Object Qput_column_of_args, Qtabular_function, Qinterpolate;
    Object Qtabular_function_interpolation_qm, Qkeep_sorted, Qtype_of_value;
    Object Qtype_of_tabular_function_value, Qtype_of_arg;
    Object Qtype_of_tabular_function_arg, string_constant_41;
    Object string_constant_40, list_constant_6, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object list_constant_5, Qcreate_icon_description, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_11;
    Object string_constant_29, string_constant_28, Qentity, Qitem;
    Object Qput_box_translation_and_text_slot_value;
    Object Qunits_of_measure_declaration;
    Object Qput_box_translation_and_text_slot_value_for_units_of_measure_declaration;
    Object Qunits_declaration, Qcompile_units_declaration_for_slot;
    Object string_constant_27, string_constant_26;
    Object Qsubstitute_class_and_kb_flags, Qengineering_units_declaration;
    Object string_constant_25, list_constant_4, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object Qcleanup, Qcleanup_for_function_definition;
    Object Qput_function_definition_byte_code_body;
    Object Qput_box_translation_and_text_slot_value_for_function_definition;
    Object Qcompile_function_definition_for_slot, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_10;
    Object string_constant_9, Qstatement;

    x_note_fn_call(154,30);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qfunction_definition = STATIC_SYMBOL("FUNCTION-DEFINITION",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant_4 = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qfunction_definition,
	    list_constant_4);
    string_constant_9 = STATIC_STRING("1m1m8v836ty1l8t");
    string_constant_10 = 
	    STATIC_STRING("1s4z8r83--y83--y836ty836ty00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_11 = 
	    STATIC_STRING("ave a date. ~\nauthors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n00");
    string_constant_12 = 
	    STATIC_STRING("0004z8r83-0y83-0y836ty836ty00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_13 = 
	    STATIC_STRING("ion is available at this time)000004z8r83-Fy83-Fy836ty836ty00001p1l8l1m8p01l83Uy1l83*-y1m83Dy53MySee comment in class block00000");
    string_constant_14 = 
	    STATIC_STRING("4z8r83ry83ry836ty836ty00001p1l8l1n8p836ty83Gy1l83-5y1l8o1l83-3y000004z8r83MPy83MPy836ty836ty00001n1l8o1l8l1l83Cy000004z8r83MQy83");
    string_constant_15 = 
	    STATIC_STRING("MQy836ty836ty00001m1l8l1l83Cy000004z8r83MTy83MTy836ty836ty00001m1l8l1l83Cy000004z8r83MSy83MSy836ty836ty00001m1l8l1l83Cy00000");
    string_constant_16 = 
	    STATIC_STRING("1u8q1o836ty1l83*ry1m8v836ty8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1n83-Fy01m8p01o83ry01n8p836ty83Gy83-5y1p83MPy08o8l83Cy1o83MQy08l8");
    string_constant_17 = STATIC_STRING("3Cy1o83MTy08l83Cy1o83MSy08l83Cy");
    temp = regenerate_optimized_constant(string_constant_9);
    temp_1 = regenerate_optimized_constant(list(6,string_constant_10,
	    string_constant_11,string_constant_12,string_constant_13,
	    string_constant_14,string_constant_15));
    add_class_to_environment(9,Qfunction_definition,list_constant_4,Nil,
	    temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(LIST_2(string_constant_16,
	    string_constant_17)),Nil);
    Function_definition_class_description = 
	    lookup_global_or_kb_specific_property_value(Qfunction_definition,
	    Class_description_gkbprop);
    string_constant_18 = 
	    STATIC_STRING("1t1n836ty1o83-7Oy83-Ujy1m9k9l83=xy1nlmo1n836ty1o83-7Oy83-Ujy1m9k9l831Py1nlmo1m83-Ujy1m1m9k83-9y1m9k83-Ay1n83-Ujy1n1m9k83-9y83-Ul");
    string_constant_19 = 
	    STATIC_STRING("y1m9k83-Ay1lm1n83-Ujy1o1m9k83-9y83-Uly1m9k83vy83-Uky2lmo1n83-Uky1m83-Uly1m9k83-Ay1ll1n83-Uky1n83-Uly1m9k83vy83-Uky2lln1m83-Uly83");
    string_constant_20 = STATIC_STRING("-6y1m83-7Oy83-6y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_18,
	    string_constant_19,string_constant_20)));
    Qop = STATIC_SYMBOL("(",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qfunction_definition_byte_code_body = 
	    STATIC_SYMBOL("FUNCTION-DEFINITION-BYTE-CODE-BODY",AB_package);
    Qfunction_definition_parse_result = 
	    STATIC_SYMBOL("FUNCTION-DEFINITION-PARSE-RESULT",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qcompile_function_definition_for_slot = 
	    STATIC_SYMBOL("COMPILE-FUNCTION-DEFINITION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_function_definition_for_slot,
	    STATIC_FUNCTION(compile_function_definition_for_slot,NIL,TRUE,
	    3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qfunction_definition,
	    SYMBOL_FUNCTION(Qcompile_function_definition_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qfunction_definition,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qput_box_translation_and_text_slot_value_for_function_definition = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-FUNCTION-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_function_definition,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_function_definition,
	    NIL,FALSE,3,3));
    Qput_box_translation_and_text_slot_value = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_function_definition);
    set_get(Qfunction_definition,Qput_box_translation_and_text_slot_value,
	    temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_2 = CONS(Qfunction_definition,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_2,
	    Qclasses_which_define);
    Qput_function_definition_byte_code_body = 
	    STATIC_SYMBOL("PUT-FUNCTION-DEFINITION-BYTE-CODE-BODY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_function_definition_byte_code_body,
	    STATIC_FUNCTION(put_function_definition_byte_code_body,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qfunction_definition_byte_code_body,
	    SYMBOL_FUNCTION(Qput_function_definition_byte_code_body),
	    Qslot_putter);
    Qcleanup_for_function_definition = 
	    STATIC_SYMBOL("CLEANUP-FOR-FUNCTION-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_function_definition,
	    STATIC_FUNCTION(cleanup_for_function_definition,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_function_definition);
    set_get(Qfunction_definition,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qfunction_definition,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qunits_of_measure_declaration = 
	    STATIC_SYMBOL("UNITS-OF-MEASURE-DECLARATION",AB_package);
    check_if_superior_classes_are_defined(Qunits_of_measure_declaration,
	    list_constant_4);
    string_constant_21 = STATIC_STRING("1m1m8v83AKy1l8t");
    string_constant_22 = 
	    STATIC_STRING("1n4z8r83--y83--y83AKy83AKy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_23 = 
	    STATIC_STRING("0004z8r83-0y83-0y83AKy83AKy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_24 = 
	    STATIC_STRING("ion is available at this time)000004z8r83ry83ry83AKy83AKy00001p1l8l1n8p83Fhy83Gy1l83-5y1l8o1l83-3y00000");
    string_constant_25 = 
	    STATIC_STRING("1p8q1o83AKy1l83*ry1m8v83AKy8t1n83--y01m8p83-*y1n83-0y01m8p83-0y1o83ry01n8p83Fhy83Gy83-5y");
    temp = regenerate_optimized_constant(string_constant_21);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_22,
	    string_constant_11,string_constant_23,string_constant_24));
    add_class_to_environment(9,Qunits_of_measure_declaration,
	    list_constant_4,Nil,temp,Nil,temp_1,list_constant_4,
	    regenerate_optimized_constant(string_constant_25),Nil);
    Units_of_measure_declaration_class_description = 
	    lookup_global_or_kb_specific_property_value(Qunits_of_measure_declaration,
	    Class_description_gkbprop);
    Qengineering_units_declaration = 
	    STATIC_SYMBOL("ENGINEERING-UNITS-DECLARATION",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qengineering_units_declaration,
	    CONS(Qunits_of_measure_declaration,temp),
	    Qsubstitute_class_and_kb_flags);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_26 = 
	    STATIC_STRING("1p1n83Fhy1q1m9k83Fgy1m9k83-Ty1m9k83-e6y1m9k83pjy1m9k83-Py83-vIy1lq1m83-vIy83-vHy1o83-vIy1n83-vHy1m9k83vy83-vIy1nmln9l1m83-vHy83-");
    string_constant_27 = 
	    STATIC_STRING("6y1n83-vHy1p83-6y1m9k83-9y1m9k83-q*y83-6y1m9k83-Ay2lol");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_26,
	    string_constant_27)));
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qunits_declaration = STATIC_SYMBOL("UNITS-DECLARATION",AB_package);
    Qcompile_units_declaration_for_slot = 
	    STATIC_SYMBOL("COMPILE-UNITS-DECLARATION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_units_declaration_for_slot,
	    STATIC_FUNCTION(compile_units_declaration_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qunits_declaration,
	    SYMBOL_FUNCTION(Qcompile_units_declaration_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qunits_declaration,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qput_box_translation_and_text_slot_value_for_units_of_measure_declaration 
	    = 
	    STATIC_SYMBOL("PUT-BOX-TRANSLATION-AND-TEXT-SLOT-VALUE-FOR-UNITS-OF-MEASURE-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_units_of_measure_declaration,
	    STATIC_FUNCTION(put_box_translation_and_text_slot_value_for_units_of_measure_declaration,
	    NIL,FALSE,3,3));
    temp_2 = 
	    SYMBOL_FUNCTION(Qput_box_translation_and_text_slot_value_for_units_of_measure_declaration);
    set_get(Qunits_of_measure_declaration,
	    Qput_box_translation_and_text_slot_value,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qput_box_translation_and_text_slot_value),
	    Qclasses_which_define);
    temp_2 = CONS(Qunits_of_measure_declaration,temp);
    mutate_global_property(Qput_box_translation_and_text_slot_value,temp_2,
	    Qclasses_which_define);
    Qtabular_function = STATIC_SYMBOL("TABULAR-FUNCTION",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qtabular_function,list_constant_5);
    string_constant_28 = STATIC_STRING("1p1m8v834gy1l8t1l83-8y1l83Iy1l83Ly");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_29 = 
	    STATIC_STRING("1n4z8r83--y83--y834gy834gy00001p1l8l1m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may h");
    string_constant_30 = 
	    STATIC_STRING("0004z8r83-0y83-0y834gy834gy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentat");
    string_constant_31 = 
	    STATIC_STRING("ion is available at this time)000004z8r8u8u834gy834gy01p8w9k3uy3uy1p1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy1n83Oy1mkz1m3uyz1n83Oy1mk3Qy1m");
    string_constant_32 = 
	    STATIC_STRING("3uy3Qy1n83Oy1mk3fy1m3uy3fy1n83Oy1m3Qyk1m3Qy3uy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_33 = 
	    STATIC_STRING("1p8q1r834gy1m83Ry83-+y1m8v834gy8t83-8y83Iy83Ly1n83--y01m8p83-*y1n83-0y01m8p83-0y1m8u1p8w9k3uy3uy1p1p83Jy1mkk1m3uyk1m3uy3uy1mk3uy");
    string_constant_34 = 
	    STATIC_STRING("1n83Oy1mkz1m3uyz1n83Oy1mk3Qy1m3uy3Qy1n83Oy1mk3fy1m3uy3fy1n83Oy1m3Qyk1m3Qy3uy");
    temp = regenerate_optimized_constant(string_constant_28);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_29,
	    string_constant_11,string_constant_30,string_constant_31,
	    string_constant_32));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qtabular_function,list_constant_5,Nil,temp,
	    Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(LIST_2(string_constant_33,
	    string_constant_34)),Nil);
    Tabular_function_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtabular_function,
	    Class_description_gkbprop);
    Qtabular_function_of_1_arg = STATIC_SYMBOL("TABULAR-FUNCTION-OF-1-ARG",
	    AB_package);
    list_constant_6 = STATIC_CONS(Qtabular_function,Qnil);
    check_if_superior_classes_are_defined(Qtabular_function_of_1_arg,
	    list_constant_6);
    string_constant_35 = STATIC_STRING("1m1m8v837Uy1l8t");
    string_constant_36 = 
	    STATIC_STRING("1s4z8r83Acy83Acy837Uy837Uy00001q1m8p83Acy1l8l1l83Ey1l83Ny1l83KGy1l83Hy000004z8r83cvy83cvy837Uy837Uy083-Hy001m1l8l1l8o000004z8r83");
    string_constant_37 = 
	    STATIC_STRING("cwy83cwy837Uy837Uy083-Hy001m1l8l1l8o000004z8r839Ey839Ey837Uy837Uy083Agy001o1m8p839Ey1l8l1l8z1l8o000004z8r83FLy83FLy837Uy837Uy08k");
    string_constant_38 = 
	    STATIC_STRING("001o1m8p83Ky1l8l1l8z1l8o000004z8r83IIy83IIy837Uy837Uy00001n1l8l1l8o1l83Cy000004z8r83IJy83IJy837Uy837Uy00001n1l8l1l8o1l83Cy000004");
    string_constant_39 = 
	    STATIC_STRING("z8r83Wvy83Wvy837Uy837Uy0k001n1l8l1l8o1l83Cy00000");
    string_constant_40 = 
	    STATIC_STRING("1u8q1o837Uy1l834gy1m8v837Uy8t1s83Acy01m8p83Acy8l83Ey83Ny83KGy83Hy1o83cvy83-Hy8l8o1o83cwy83-Hy8l8o1q839Ey83Agy1m8p839Ey8l8z8o1q83");
    string_constant_41 = 
	    STATIC_STRING("FLy8k1m8p83Ky8l8z8o1p83IIy08l8o83Cy1p83IJy08l8o83Cy1p83Wvyk8l8o83Cy");
    temp = regenerate_optimized_constant(string_constant_35);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39));
    add_class_to_environment(9,Qtabular_function_of_1_arg,list_constant_6,
	    Nil,temp,Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_41)),Nil);
    Tabular_function_of_1_arg_class_description = 
	    lookup_global_or_kb_specific_property_value(Qtabular_function_of_1_arg,
	    Class_description_gkbprop);
    Qtype_of_tabular_function_arg = 
	    STATIC_SYMBOL("TYPE-OF-TABULAR-FUNCTION-ARG",AB_package);
    Qtype_of_arg = STATIC_SYMBOL("TYPE-OF-ARG",AB_package);
    alias_slot_name(3,Qtype_of_tabular_function_arg,Qtype_of_arg,
	    Qtabular_function);
    Qtype_of_tabular_function_value = 
	    STATIC_SYMBOL("TYPE-OF-TABULAR-FUNCTION-VALUE",AB_package);
    Qtype_of_value = STATIC_SYMBOL("TYPE-OF-VALUE",AB_package);
    alias_slot_name(3,Qtype_of_tabular_function_value,Qtype_of_value,
	    Qtabular_function);
    Qkeep_tabular_function_sorted_qm = 
	    STATIC_SYMBOL("KEEP-TABULAR-FUNCTION-SORTED\?",AB_package);
    Qkeep_sorted = STATIC_SYMBOL("KEEP-SORTED",AB_package);
    alias_slot_name(3,Qkeep_tabular_function_sorted_qm,Qkeep_sorted,
	    Qtabular_function);
    Qtabular_function_interpolation_qm = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-INTERPOLATION\?",AB_package);
    Qinterpolate = STATIC_SYMBOL("INTERPOLATE",AB_package);
    alias_slot_name(3,Qtabular_function_interpolation_qm,Qinterpolate,
	    Qtabular_function);
    Qcolumn_of_args = STATIC_SYMBOL("COLUMN-OF-ARGS",AB_package);
    Qput_column_of_args = STATIC_SYMBOL("PUT-COLUMN-OF-ARGS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_column_of_args,
	    STATIC_FUNCTION(put_column_of_args,NIL,FALSE,3,3));
    mutate_global_property(Qcolumn_of_args,
	    SYMBOL_FUNCTION(Qput_column_of_args),Qslot_putter);
    Qcolumn_of_values = STATIC_SYMBOL("COLUMN-OF-VALUES",AB_package);
    Qput_column_of_values = STATIC_SYMBOL("PUT-COLUMN-OF-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_column_of_values,
	    STATIC_FUNCTION(put_column_of_values,NIL,FALSE,3,3));
    mutate_global_property(Qcolumn_of_values,
	    SYMBOL_FUNCTION(Qput_column_of_values),Qslot_putter);
    Qreclaim_column_of_args_value = 
	    STATIC_SYMBOL("RECLAIM-COLUMN-OF-ARGS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_column_of_args_value,
	    STATIC_FUNCTION(reclaim_column_of_args_value,NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qcolumn_of_args,
	    SYMBOL_FUNCTION(Qreclaim_column_of_args_value),
	    Qslot_value_reclaimer);
    Qreclaim_column_of_values_value = 
	    STATIC_SYMBOL("RECLAIM-COLUMN-OF-VALUES-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_column_of_values_value,
	    STATIC_FUNCTION(reclaim_column_of_values_value,NIL,FALSE,2,2));
    mutate_global_property(Qcolumn_of_values,
	    SYMBOL_FUNCTION(Qreclaim_column_of_values_value),
	    Qslot_value_reclaimer);
    Qinitialize_after_reading_for_tabular_function_of_1_arg = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-TABULAR-FUNCTION-OF-1-ARG",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_tabular_function_of_1_arg,
	    STATIC_FUNCTION(initialize_after_reading_for_tabular_function_of_1_arg,
	    NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qinitialize_after_reading_for_tabular_function_of_1_arg);
    set_get(Qtabular_function_of_1_arg,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qtabular_function_of_1_arg,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qend = STATIC_SYMBOL("END",AB_package);
    string_constant_42 = 
	    STATIC_STRING("13Uy1n83Acy1n83-JDy83-ey83-nIy1mlm1n83Acy1o83-JDy83-ey83-nIy83-nJy1nlmo1n83Acy1o83-JDy83-ey83-nIy83-nHy1olm0o1n83Acy1p83-JDy83-e");
    string_constant_43 = 
	    STATIC_STRING("y83-nIy83-nJy83-nHy1olmop1n83Acy1n83-JDy1m9k83-umy83-nIy1mlm1n83Acy1o83-JDy1m9k83-umy83-nIy83-nJy1nlmo1n83Acy1o83-JDy1m9k83-umy8");
    string_constant_44 = 
	    STATIC_STRING("3-nIy83-nHy1olm0o1n83Acy1p83-JDy1m9k83-umy83-nIy83-nJy83-nHy1olmop1n83Acy1m83-JDy83-nIy1ll1n83Acy1n83-JDy83-nIy83-nJy1nl0n1n83Ac");
    string_constant_45 = 
	    STATIC_STRING("y1n83-JDy83-nIy83-nHy1ol00n1n83Acy1o83-JDy83-nIy83-nJy83-nHy1ol0no1m83-JDy1m9k83pRy1m83-JDy1m9k9l1n83-nJy1n1m9k83=Gy1m9k9m1m9k83");
    string_constant_46 = 
	    STATIC_STRING("HBy83HBy1n83-nJy1n1m9k83=Gy1m9k9m1m9k9n9n1n83-nJy1o1m9k83HAy1m9k83-H6y1m9k9o83-s8y1m83HAyo1n83-nJy1o1m9k835+y1m9k83-H6y1m9k9o83-");
    string_constant_47 = 
	    STATIC_STRING("s8y1m835+yo1n83-nHy1o1m9k83=Fy1m9k83-H6y1m9k9o83-s6y1m83=Fyo1n83-nHy1v1m9k83=Fy1m9k83-H6y1m9k9o83-s6y1m9k83-ty1m9k83-Tiy1m9k83-9");
    string_constant_48 = 
	    STATIC_STRING("y1m9k83-H6y1m9k83-Ay1m9k9o83-s6y1n83=Fyov1m83-nIy1m9k83-nGy1m83-nIy1m9k83-nKy1m83-s7y1m9k83-Hy1m83-s7y1m9k83-2y1m83-s7y1m9k9p1m8");
    string_constant_49 = 
	    STATIC_STRING("3-s6y83-s8y1o83-s6y1n83-s8y1m9k83vy83-s6y1n83vyln9q1n83-s6y1n83-s8y1m9k83vy1m9k83-T-y1n83vyln1m83-s8y83-Hy1m83-s8y83-2y1m83-s8y8");
    string_constant_50 = 
	    STATIC_STRING("3-Uy1m839Ey1m9k83=Ty1n839Ey1m1m9k83*ty1m9k83Agym1n839Ey1m1m9k83*ty1m9k9rm");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qdelete);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qend);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qstring);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qvalues);
    add_grammar_rules_function(regenerate_optimized_constant(list(9,
	    string_constant_42,string_constant_43,string_constant_44,
	    string_constant_45,string_constant_46,string_constant_47,
	    string_constant_48,string_constant_49,string_constant_50)));
    string_constant = 
	    STATIC_STRING("Types of args and values cannot be changed once the table has rows.");
    Qtabular_function_data_type = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-DATA-TYPE",AB_package);
    Qcompile_tabular_function_data_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-TABULAR-FUNCTION-DATA-TYPE-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_tabular_function_data_type_for_slot,
	    STATIC_FUNCTION(compile_tabular_function_data_type_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qtabular_function_data_type,
	    SYMBOL_FUNCTION(Qcompile_tabular_function_data_type_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtabular_function_data_type,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    string_constant_1 = 
	    STATIC_STRING("The sort specification cannot be changed because ~\n                there is an instance of this class with table rows.");
    string_constant_2 = 
	    STATIC_STRING("The sort specification cannot be so changed once the table has rows.");
    Qcompile_keep_tabular_function_sorted_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-KEEP-TABULAR-FUNCTION-SORTED\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_keep_tabular_function_sorted_qm_for_slot,
	    STATIC_FUNCTION(compile_keep_tabular_function_sorted_qm_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qkeep_tabular_function_sorted_qm,
	    SYMBOL_FUNCTION(Qcompile_keep_tabular_function_sorted_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qkeep_tabular_function_sorted_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_3 = STATIC_STRING("no");
    Qargs = STATIC_SYMBOL("ARGS",AB_package);
    string_constant_4 = STATIC_STRING("by args");
    string_constant_5 = STATIC_STRING("by values");
    Qwrite_keep_tabular_function_sorted_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-KEEP-TABULAR-FUNCTION-SORTED\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_keep_tabular_function_sorted_qm_from_slot,
	    STATIC_FUNCTION(write_keep_tabular_function_sorted_qm_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qkeep_tabular_function_sorted_qm,
	    SYMBOL_FUNCTION(Qwrite_keep_tabular_function_sorted_qm_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qkeep_tabular_function_sorted_qm),
	    Qtype_specification_simple_expansion,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qmember,Qab_no,Qargs,Qvalues);
    define_type_specification_explicit_complex_type(Qkeep_tabular_function_sorted_qm,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qkeep_tabular_function_sorted_qm);
    keep_tabular_function_sorted_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(keep_tabular_function_sorted_qm_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qkeep_tabular_function_sorted_qm,
	    keep_tabular_function_sorted_qm_evaluation_setter_1);
    keep_tabular_function_sorted_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(keep_tabular_function_sorted_qm_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qkeep_tabular_function_sorted_qm,
	    keep_tabular_function_sorted_qm_evaluation_getter_1);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qadd_or_delete_rows = STATIC_SYMBOL("ADD-OR-DELETE-ROWS",AB_package);
    Qwrite_add_or_delete_rows_from_slot = 
	    STATIC_SYMBOL("WRITE-ADD-OR-DELETE-ROWS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_add_or_delete_rows_from_slot,
	    STATIC_FUNCTION(write_add_or_delete_rows_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qadd_or_delete_rows,
	    SYMBOL_FUNCTION(Qwrite_add_or_delete_rows_from_slot),
	    Qslot_value_writer);
    Qvalues_for_table_of_values = 
	    STATIC_SYMBOL("VALUES-FOR-TABLE-OF-VALUES",AB_package);
    temp_2 = CONS(Qvalues_for_table_of_values,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qtabular_function_of_1_arg),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qvalues_for_table_of_values,temp);
    set_property_value_function(get_symbol_properties_function(Qtabular_function_of_1_arg),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qf_of_x = STATIC_SYMBOL("F-OF-X",AB_package);
    Qnumber_of_rows_in_table = STATIC_SYMBOL("NUMBER-OF-ROWS-IN-TABLE",
	    AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qtabular_function_of_1_arg);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_8 = STATIC_CONS(Qno_item,Qnil);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)7L,Qab_or,list_constant_8,
	    Qsymbol,Qinteger,Qlong,Qfloat,Qtext);
    list_constant_10 = STATIC_CONS(list_constant_9,Qnil);
    list_constant_11 = STATIC_CONS(Qx,list_constant_10);
    list_constant_12 = STATIC_CONS(Qf_of_x,list_constant_10);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_11,
	    list_constant_12);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_13);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_14);
    Qinitial_values_for_table_of_values = 
	    STATIC_SYMBOL("INITIAL-VALUES-FOR-TABLE-OF-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_values_for_table_of_values,
	    STATIC_FUNCTION(initial_values_for_table_of_values,NIL,FALSE,1,1));
    Qget_values_for_table_of_values = 
	    STATIC_SYMBOL("GET-VALUES-FOR-TABLE-OF-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qget_values_for_table_of_values,
	    STATIC_FUNCTION(get_values_for_table_of_values,NIL,FALSE,1,1));
    Qset_values_for_table_of_values = 
	    STATIC_SYMBOL("SET-VALUES-FOR-TABLE-OF-VALUES",AB_package);
    SET_SYMBOL_FUNCTION(Qset_values_for_table_of_values,
	    STATIC_FUNCTION(set_values_for_table_of_values,NIL,FALSE,2,2));
    add_virtual_attribute(Qvalues_for_table_of_values,list_constant_15,
	    list_constant_16,Qnil,
	    SYMBOL_FUNCTION(Qinitial_values_for_table_of_values),
	    SYMBOL_FUNCTION(Qget_values_for_table_of_values),
	    SYMBOL_FUNCTION(Qset_values_for_table_of_values));
    Qtabular_function_car_tester = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-CAR-TESTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtabular_function_car_tester,
	    STATIC_FUNCTION(tabular_function_car_tester,NIL,FALSE,2,2));
    Qtabular_function_cdr_tester = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-CDR-TESTER",AB_package);
    SET_SYMBOL_FUNCTION(Qtabular_function_cdr_tester,
	    STATIC_FUNCTION(tabular_function_cdr_tester,NIL,FALSE,2,2));
    Qunfinished = STATIC_SYMBOL("UNFINISHED",AB_package);
    Qbeginning = STATIC_SYMBOL("BEGINNING",AB_package);
    Qbefore = STATIC_SYMBOL("BEFORE",AB_package);
    Qafter = STATIC_SYMBOL("AFTER",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qbefore,Qafter);
    Qtabular_function_phrase_datum_equal = 
	    STATIC_SYMBOL("TABULAR-FUNCTION-PHRASE-DATUM-EQUAL",AB_package);
    SET_SYMBOL_FUNCTION(Qtabular_function_phrase_datum_equal,
	    STATIC_FUNCTION(tabular_function_phrase_datum_equal,NIL,FALSE,
	    2,2));
    Qetc_dot = STATIC_SYMBOL("ETC.",AB_package);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtable_of_values = STATIC_SYMBOL("TABLE-OF-VALUES",AB_package);
    Qcompile_add_or_delete_rows_for_slot = 
	    STATIC_SYMBOL("COMPILE-ADD-OR-DELETE-ROWS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_add_or_delete_rows_for_slot,
	    STATIC_FUNCTION(compile_add_or_delete_rows_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qadd_or_delete_rows,
	    SYMBOL_FUNCTION(Qcompile_add_or_delete_rows_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qadd_or_delete_rows,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_1 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_6 = STATIC_STRING("~s");
    Qwrite_tabular_function_data_type_from_slot = 
	    STATIC_SYMBOL("WRITE-TABULAR-FUNCTION-DATA-TYPE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tabular_function_data_type_from_slot,
	    STATIC_FUNCTION(write_tabular_function_data_type_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtabular_function_data_type,
	    SYMBOL_FUNCTION(Qwrite_tabular_function_data_type_from_slot),
	    Qslot_value_writer);
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    list_constant_17 = STATIC_CONS(Qtable_item,Qnil);
    check_if_superior_classes_are_defined(Qtable_of_values,list_constant_17);
    string_constant_51 = STATIC_STRING("1l1l83Iy");
    string_constant_52 = STATIC_STRING("0");
    string_constant_53 = STATIC_STRING("1m8q1n83bHy1l83A8y83Iy");
    temp = regenerate_optimized_constant(string_constant_51);
    temp_1 = regenerate_optimized_constant(string_constant_52);
    add_class_to_environment(9,Qtable_of_values,list_constant_17,Nil,temp,
	    Nil,temp_1,list_constant_17,
	    regenerate_optimized_constant(string_constant_53),Nil);
    Qclass_format = STATIC_SYMBOL("CLASS-FORMAT",AB_package);
    Qfont_for_attribute_tables = STATIC_SYMBOL("FONT-FOR-ATTRIBUTE-TABLES",
	    AB_package);
    Qattribute_value_format = STATIC_SYMBOL("ATTRIBUTE-VALUE-FORMAT",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qtype,
	    Qtabular_function_data_type);
    array_constant_2 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_7,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qf = STATIC_SYMBOL("F",AB_package);
    string_constant_7 = STATIC_STRING(" ~(~A~) (x)");
    Qattributes_table_format = STATIC_SYMBOL("ATTRIBUTES-TABLE-FORMAT",
	    AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qstretch_new_image_planes_for_caption_p = 
	    STATIC_SYMBOL("STRETCH-NEW-IMAGE-PLANES-FOR-CAPTION-P",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_8 = STATIC_STRING("Table of values");
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    float_constant = STATIC_FLOAT(0.0);
}
