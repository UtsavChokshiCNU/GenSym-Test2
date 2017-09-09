/* gram3.c
 * Input file:  grammar3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram3.h"


static Object Qseconds;            /* seconds */

/* REJECT-IF-FLOAT-INTERVAL */
Object reject_if_float_interval(ago_interval)
    Object ago_interval;
{
    Object thing;
    char temp;

    x_note_fn_call(196,0);
    if (CONSP(ago_interval) && EQ(CDR(ago_interval),Qseconds)) {
	thing = CAR(ago_interval);
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(thing) != (SI_Long)0L ? 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) == (SI_Long)1L : 
		TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(ago_interval);
}

static Object Qbad;                /* bad */

/* COMPILE-UNIQUE-LOGICAL-EXPRESSION-FOR-SLOT */
Object compile_unique_logical_expression_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Object current_computation_frame, compiled_condition_qm;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(196,1);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    current_computation_frame = frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      compiled_condition_qm = compile_expression(parse_result,Nil,Nil);
      if (compiled_condition_qm)
	  update_frame_status(frame,Nil,Nil);
      else
	  update_frame_status(frame,Qbad,Nil);
      result = VALUES_1(compiled_condition_qm);
    POP_SPECIAL();
    return result;
}

static Object Qcell_array;         /* cell-array */

static Object Qnone;               /* none */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qg2_cell_array;      /* g2-cell-array */

static Object Qpart_stack;         /* part-stack */

static Object Qmark;               /* mark */

static Object Qg2_lambda;          /* g2-lambda */

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qitem;               /* item */

static Object Qg2_fake_user_menu_choice_attribute;  /* g2-fake-user-menu-choice-attribute */

static Object Qempty_expression_cell;  /* empty-expression-cell */

/* COMPILE-USER-MENU-CHOICE-EXPRESSION-FOR-SLOT */
Object compile_user_menu_choice_expression_for_slot varargs_1(int, n)
{
    Object parse_result, user_menu_choice, gensymed_symbol;
    Object current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_style, current_block_of_dependent_frame;
    Object cell_array_qm, expression_cell_qm, expression_qm, result_1;
    Object current_flag_state_qm, slot_description, new_cons, temp;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object stack_of_slot_value_changes, gensymed_symbol_2, gensymed_symbol_3;
    Object temp_1, old_current_part_description, part_feature_index;
    Object exit_feature_handler, part_stack_pop_store, cons_1, next_cons;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    Object stack_change_pop_store;
    SI_Long svref_new_value_1;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(196,2);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    user_menu_choice = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    current_computation_frame = user_menu_choice;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    4);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      3);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
		2);
	  current_block_of_dependent_frame = user_menu_choice;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
		  1);
	    cell_array_qm = 
		    get_lookup_slot_value_given_default(user_menu_choice,
		    Qcell_array,Nil);
	    expression_cell_qm = cell_array_qm ? 
		    (FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)1L),Maximum_in_place_array_size) ? 
		    ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),(SI_Long)0L + 
		    IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
		    (SI_Long)2L),(SI_Long)0L)) : Nil;
	    expression_qm = EQ(parse_result,Qnone) ? Nil : parse_result;
	    result_1 = Nil;
	    current_flag_state_qm = Nil;
	    slot_description = 
		    get_slot_description_of_class_description_function(Qframe_status_and_notes,
		    ISVREF(user_menu_choice,(SI_Long)1L),Nil);
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
		gensymed_symbol_1 = 
			nconc2(stack_change_list_2(user_menu_choice,
			slot_description),stack_change_cons_1(Nil,Nil));
	    else {
		new_cons = ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp = Available_stack_change_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp,svref_arg_2) = svref_new_value;
		    if ( 
			    !TRUEP(ISVREF(Available_stack_change_conses_vector,
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
		M_CAR(gensymed_symbol_1) = user_menu_choice;
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
		      (IFIX(ISVREF(user_menu_choice,(SI_Long)5L)) & 
		      (SI_Long)16777216L) ? T : Nil;
	      if ( !TRUEP(current_flag_state_qm)) {
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(user_menu_choice,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = user_menu_choice;
		  gensymed_symbol_2 = Nil;
		  gensymed_symbol_3 = T;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
		  svref_new_value_1 = IFIX(ISVREF(user_menu_choice,
			  (SI_Long)5L)) | (SI_Long)16777216L;
		  ISVREF(user_menu_choice,(SI_Long)5L) = 
			  FIX(svref_new_value_1);
	      }
	      if (expression_qm) {
		  if ( !(cell_array_qm && expression_cell_qm)) {
		      cell_array_qm = make_frame(Qg2_cell_array);
		      change_slot_value(3,user_menu_choice,Qcell_array,
			      cell_array_qm);
		      make_empty_expression_cell(cell_array_qm);
		      expression_cell_qm = 
			      FIXNUM_LE(ISVREF(ISVREF(cell_array_qm,
			      (SI_Long)3L),(SI_Long)1L),
			      Maximum_in_place_array_size) ? 
			      ISVREF(ISVREF(cell_array_qm,(SI_Long)3L),
			      (SI_Long)0L + 
			      IFIX(Managed_array_index_offset)) : 
			      ISVREF(ISVREF(ISVREF(cell_array_qm,
			      (SI_Long)3L),(SI_Long)2L),(SI_Long)0L);
		      temp_1 = ISVREF(user_menu_choice,(SI_Long)8L);
		      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(user_menu_choice,(SI_Long)5L)) 
			      & (SI_Long)1L) ||  
			      !TRUEP(Inside_breakpoint_p) && (SI_Long)0L 
			      != (IFIX(ISVREF(user_menu_choice,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != 
			      (IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) 
			      & (SI_Long)8192L))))
			  activate_g2_cell_array(cell_array_qm);
		  }
		  old_current_part_description = Current_part_description;
		  Current_part_description = 
			  get_default_computation_style_of_class();
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      new_cons = ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index));
		      if (new_cons) {
			  temp = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  svref_new_value = M_CDR(new_cons);
			  SVREF(temp,svref_arg_2) = svref_new_value;
			  if ( 
				  !TRUEP(ISVREF(Available_part_stack_conses_vector,
				  IFIX(Current_thread_index)))) {
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = Nil;
			  }
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_part_stack_cons_pool();
		      temp = Current_part_description;
		      M_CAR(gensymed_symbol) = temp;
		      temp = Stack_of_current_part_descriptions;
		      M_CDR(gensymed_symbol) = temp;
		      inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		      Stack_of_current_part_descriptions = gensymed_symbol;
		  }
		  new_cons = ISVREF(Available_part_stack_conses_vector,
			  IFIX(Current_thread_index));
		  if (new_cons) {
		      temp = Available_part_stack_conses_vector;
		      svref_arg_2 = Current_thread_index;
		      svref_new_value = M_CDR(new_cons);
		      SVREF(temp,svref_arg_2) = svref_new_value;
		      if ( 
			      !TRUEP(ISVREF(Available_part_stack_conses_vector,
			      IFIX(Current_thread_index)))) {
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = Nil;
		      }
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_part_stack_cons_pool();
		  M_CAR(gensymed_symbol) = Qmark;
		  temp = Part_feature_recall_stack;
		  M_CDR(gensymed_symbol) = temp;
		  inline_note_allocate_cons(gensymed_symbol,Qpart_stack);
		  Part_feature_recall_stack = gensymed_symbol;
		  enter_part_description(Current_part_description);
		  register_expression_cell_during_compilation(7,
			  cell_array_qm,FIX((SI_Long)0L),T,
			  phrase_list_3(Qg2_lambda,list_constant,
			  expression_qm),list_constant_1,Qitem,
			  Qg2_fake_user_menu_choice_attribute);
		  if ( !EQ(ISVREF(expression_cell_qm,(SI_Long)2L),
			  Qempty_expression_cell)) {
		      update_frame_status(user_menu_choice,
			      button_frame_status(user_menu_choice),Nil);
		      temp_1 = T;
		  }
		  else {
		      update_frame_status(user_menu_choice,Qbad,Nil);
		      temp_1 = Qbad;
		  }
		  part_feature_index = Nil;
		  exit_feature_handler = Nil;
		next_loop:
		  part_stack_pop_store = Nil;
		  cons_1 = Part_feature_recall_stack;
		  if (cons_1) {
		      part_stack_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qpart_stack);
		      if (ISVREF(Available_part_stack_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp = 
				  ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index));
			  M_CDR(temp) = cons_1;
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
		      }
		      else {
			  temp = Available_part_stack_conses_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
			  temp = Available_part_stack_conses_tail_vector;
			  svref_arg_2 = Current_thread_index;
			  SVREF(temp,svref_arg_2) = cons_1;
		      }
		      M_CDR(cons_1) = Nil;
		  }
		  else
		      next_cons = Nil;
		  Part_feature_recall_stack = next_cons;
		  part_feature_index = part_stack_pop_store;
		  if (EQ(part_feature_index,Qmark))
		      goto end_loop;
		  exit_feature_handler = ISVREF(Part_feature_exit_methods,
			  IFIX(part_feature_index));
		  inline_funcall_0(exit_feature_handler);
		  goto next_loop;
		end_loop:;
		  Current_part_description = old_current_part_description;
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      part_stack_pop_store = Nil;
		      cons_1 = Stack_of_current_part_descriptions;
		      if (cons_1) {
			  part_stack_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qpart_stack);
			  if (ISVREF(Available_part_stack_conses_tail_vector,
				  IFIX(Current_thread_index))) {
			      temp = 
				      ISVREF(Available_part_stack_conses_tail_vector,
				      IFIX(Current_thread_index));
			      M_CDR(temp) = cons_1;
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  else {
			      temp = Available_part_stack_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			      temp = Available_part_stack_conses_tail_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp,svref_arg_2) = cons_1;
			  }
			  M_CDR(cons_1) = Nil;
		      }
		      else
			  next_cons = Nil;
		      Stack_of_current_part_descriptions = next_cons;
		  }
		  result_1 = temp_1;
	      }
	      else {
		  if (cell_array_qm) {
		      temp_1 = ISVREF(user_menu_choice,(SI_Long)8L);
		      if ( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
			      (IFIX(ISVREF(user_menu_choice,(SI_Long)5L)) 
			      & (SI_Long)1L) ||  
			      !TRUEP(Inside_breakpoint_p) && (SI_Long)0L 
			      != (IFIX(ISVREF(user_menu_choice,
			      (SI_Long)4L)) & (SI_Long)16777216L) &&  
			      !((SI_Long)0L != 
			      (IFIX(ISVREF(user_menu_choice,(SI_Long)4L)) 
			      & (SI_Long)8192L))))
			  deactivate_g2_cell_array(cell_array_qm);
		      change_slot_value(3,user_menu_choice,Qcell_array,Nil);
		  }
		  update_frame_status(user_menu_choice,
			  button_frame_status(user_menu_choice),Nil);
		  result_1 = Nil;
	      }
	      if ( !TRUEP(current_flag_state_qm)) {
		  svref_new_value_1 = IFIX(ISVREF(user_menu_choice,
			  (SI_Long)5L)) &  ~(SI_Long)16777216L;
		  ISVREF(user_menu_choice,(SI_Long)5L) = 
			  FIX(svref_new_value_1);
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(user_menu_choice,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
		  gensymed_symbol_1 = user_menu_choice;
		  gensymed_symbol_2 = T;
		  gensymed_symbol_3 = Nil;
		  inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			  gensymed_symbol_2,gensymed_symbol_3);
	      }
	      temp_2 = 
		      TRUEP(Suppress_updating_of_slot_value_representations_qm);
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
		      temp_1 = M_CDR(frame_and_slot_or_atom);
		      temp_2 = CONSP(temp_1) ? EQ(slot_description,
			      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
		  }
		  ab_loop_it_ = temp_2 ? (EQ(user_menu_choice,
			  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
		  if (ab_loop_it_) {
		      temp_2 = TRUEP(ab_loop_it_);
		      goto end_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp_2 = TRUEP(Qnil);
		end_1:;
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if ( !temp_2)
		  update_all_representations_of_slot(user_menu_choice,
			  slot_description,Nil,Nil);
	      if (ISVREF(slot_description,(SI_Long)14L))
		  update_frame_name_references(user_menu_choice);
	      stack_change_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  stack_change_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qstack_change);
		  if (ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index))) {
		      temp = 
			      ISVREF(Available_stack_change_conses_tail_vector,
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
		  temp_1 = M_CAR(Stack_of_slot_value_changes);
		  temp_2 = ATOM(temp_1);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      if (temp_2 ?  
		      !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) 
		      : TRUEP(Nil))
		  do_deferred_updates_to_representations_in_tables();
	    POP_SPECIAL();
	    result = VALUES_1(result_1);
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMPILE-USER-MENU-CHOICE-EXPRESSION-INITIALIZATION-FOR-SLOT */
Object compile_user_menu_choice_expression_initialization_for_slot varargs_1(int, n)
{
    Object parse_result, user_menu_choice, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(196,3);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    user_menu_choice = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return VALUES_1(parse_result);
}

/* ADD-LAYERING-PRESERVATION-TO-SHOW-DETAILS */
Object add_layering_preservation_to_show_details(parse)
    Object parse;
{
    Object cddr_new_value;

    x_note_fn_call(196,4);
    cddr_new_value = phrase_cons(T,CDDR(parse));
    M_CDDR(parse) = cddr_new_value;
    return VALUES_1(parse);
}

static Object string_constant;     /* "1m1n83vmy1p833*y1m9k831by83=Zy83-6y1m9k83vgy1o83-W9yl1m9ko1m83=by83Ry1n83vmy1q833*y1m9k831by83=Zy83-6y1m9k83vgy83*Zy1o83-W9yl1m9" */

static Object string_constant_1;   /* "ko1m83=by2l83Ryq" */

/* ADD-GENERIC-RULE-GRAMMAR */
Object add_generic_rule_grammar()
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(196,5);
    if (PUSH_AREA(Dynamic_area,0)) {
	clear_optimized_constants();
	push_optimized_constant(Qquote);
	add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant,
		string_constant_1)));
	result = VALUES_1(Evaluation_true_value);
    }
    POP_AREA(0);
    return result;
}

static Object string_constant_2;   /* "1m1n836Yy1m1m9k836Gy1m9k83-1jy1l83-qky1n836Yy1m1m9k83Z4y1m9k83-1jy1l83-mvy" */

/* EXTEND-ACTION-GRAMMAR */
Object extend_action_grammar()
{
    XDeclare_area(1);

    x_note_fn_call(196,6);
    if (PUSH_AREA(Dynamic_area,0)) {
	clear_optimized_constants();
	push_optimized_constant(Qquote);
	add_grammar_rules_function(regenerate_optimized_constant(string_constant_2));
    }
    POP_AREA(0);
    return VALUES_1(Evaluation_true_value);
}

void grammar3_INIT()
{
    Object gensymed_symbol;
    Object Qextend_action_grammar;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qadd_generic_rule_grammar, Qregistered_directory_of_names_p;
    Object Qrule_category_name, Qddd_dot_dddd_format, string_constant_114;
    Object string_constant_113, string_constant_112, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, Qcheck_ddd_dddd_format, Qabort_g2;
    Object Qadd_layering_preservation_to_show_details, Qcar_2_1, Qunlist_1_2;
    Object Qunlist_1, Qcategory_hack, Qsymbol_cannot_be_true_false_or_not;
    Object Qfix_in_order_action_list, Qsimplify_associative_operation;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Quser_menu_choice_expression_initialization, Qslot_value_compiler;
    Object Qcompile_user_menu_choice_expression_initialization_for_slot;
    Object Quser_menu_choice_expression;
    Object Qcompile_user_menu_choice_expression_for_slot, list_constant_5;
    Object Qtruth_value, Qab_or, Qunknown_datum, list_constant_4;
    Object list_constant_3, Qab_class, list_constant_2, Qgrammar3;
    Object string_constant_46, Kfuncall, Qunique_logical_expression;
    Object Qcompile_unique_logical_expression_for_slot, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, Qrestrict_if_slot_edit_feature;
    Object Qput_designation_in_qualifier, Qreject_if_sequence_constant;
    Object Qcheck_number_of_args, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;
    Object string_constant_11, string_constant_10, string_constant_9;
    Object string_constant_8, string_constant_7, Qreject_if_float_interval;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, Qconvert_history_interval;

    x_note_fn_call(196,7);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qreject_if_float_interval = STATIC_SYMBOL("REJECT-IF-FLOAT-INTERVAL",
	    AB_package);
    Qconvert_history_interval = STATIC_SYMBOL("CONVERT-HISTORY-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_history_interval,
	    STATIC_FUNCTION(convert_history_interval,NIL,FALSE,1,1));
    string_constant_3 = 
	    STATIC_STRING("13Ky1m83n6y83-Hy1m83-Cty836Ey1n83-Cty1q1m9k8312y83aBy1m9k832Sy836Ey1m9k8332y83-Cty1o8348ymoq1n83-Cty1o1m9k8312y83aBy1m9k832Sy836");
    string_constant_4 = 
	    STATIC_STRING("Ey1n8348ymo1m83f2y83-oy1o83f2y83=xyl9l1o83f2y1m83=xy83lYy1mlm9m1m83-1py83-oy1o83-1py1m83=xy83lYy1mlm9m1m83lgy83=xy1m83-FXy83-oy1");
    string_constant_5 = 
	    STATIC_STRING("o83-FXy83=xyl9l1o83-FXy1m83=xy83lYy1mlm9m1m83-Fdy83-oy1o83-Fdy1m83=xy83lYy1mlm9m1m83-Fhy83=xy1m83-Cry83-oy1o83-Cry836Eyl9l1o83-C");
    string_constant_6 = 
	    STATIC_STRING("ry1m836Ey83lYy1mlm9m1m83-Cuy83-oy1o83-Cuy1m836Ey83lYy1mlm9m1m83-poy836Ey1m83gTy1m9k83-Pxy1m83gTy1m9k83uXy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qreject_if_float_interval);
    push_optimized_constant(Qconvert_history_interval);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_3,
	    string_constant_4,string_constant_5,string_constant_6)));
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_if_float_interval,
	    STATIC_FUNCTION(reject_if_float_interval,NIL,FALSE,1,1));
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qcheck_number_of_args = STATIC_SYMBOL("CHECK-NUMBER-OF-ARGS",AB_package);
    Qreject_if_sequence_constant = 
	    STATIC_SYMBOL("REJECT-IF-SEQUENCE-CONSTANT",AB_package);
    Qput_designation_in_qualifier = 
	    STATIC_SYMBOL("PUT-DESIGNATION-IN-QUALIFIER",AB_package);
    string_constant_7 = 
	    STATIC_STRING("13cy1m83UQy83-RTy1o83UQy1n83-Fby1m9k83=Uy831Py1n83=Uyln9l1n83-8iy1n1m9k83-9y83UQy1m9k83-Aym1n83-8iy1o1m9k9m1m9k83-9y831Py1m9k83-");
    string_constant_8 = 
	    STATIC_STRING("Ay1m9mn1m83-RTy83-Nqy1o83-RTy1n83-Nqy1m9k83-ty83-RTy1n83-tyln9l1m83-Nqy83kXy1n83kXy1n1m9k83-9y83UQy1m9k83-Aym1n83kXy1o1m9k9m1m9k");
    string_constant_9 = 
	    STATIC_STRING("83-9y831Py1m9k83-Ay1m9mn1p83kXy1n832ay1m9k83-9y83Ecy1ll9n9o1p83kXy1m832ay836ay2llm9n9o1n83kXy1n83=py838Ry83=py1nmln1n83kXy1n83-Q");
    string_constant_10 = 
	    STATIC_STRING("qy83xLy83-Qqy1nmln1n83kXy1n83=py1m9k9p83=py1nmln1n83kXy1n83=py1m9k9q83=py1nmln1o83kXy1m833*y83-kky2llm9r1n83kXy1o83-iKy1m9k831by");
    string_constant_11 = 
	    STATIC_STRING("1m9k83=Yy1m9k83*ly1m83RGyl1n83kXy1p83-iKy1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iOyl1n83kXy1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C");
    string_constant_12 = 
	    STATIC_STRING("4y83C-y1m9k83*ly83oEy2l83LWys1n83kXy1s1m9k83-9y1m9k8312y831Py1m9k832Sy831Py1m9k8332y831Py1m9k83-Ay1o8348ynpr1n83kXy1q1m9k83-9y1m");
    string_constant_13 = 
	    STATIC_STRING("9k8312y831Py1m9k832Sy831Py1m9k83-Ay1n8348ynp1m83-Qqy833*y1n83-Qqy1n1m9k83-9y83UQy1m9k83-Aym1n83-kky1n1m9k831by1m9k83=Yy1m9k83*ly");
    string_constant_14 = 
	    STATIC_STRING("1m83RGy83hKy1n83-kky1n1m9k831by1m9k83=Ty1m9k83*ly1m83RIy83hKy1n83-kky1o1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iOy83hKy1n83-kky1");
    string_constant_15 = 
	    STATIC_STRING("o1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iPy83hKy1n83-iKy1n1m9k83-9y83=py1m9k83-Aym1n83-iKy1n1m9k83-9y83UQy1m9k83-Aym1n83-iKy1o1");
    string_constant_16 = 
	    STATIC_STRING("m9k9m1m9k83-9y831Py1m9k83-Ay1m9mn1n83-2Xy1n1m9k83-9y83UQy1m9k83-Ay1lm1n83-2Xy1o1m9k83-9y83UQy1m9k83vy83-dFy2lmo1n83-dFy1m83UQy1m");
    string_constant_17 = 
	    STATIC_STRING("9k83-Ay1ll1n83-dFy1n83UQy1m9k83vy83-dFy2lln1n833*y1s1m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83*my1m9k83-Ty833*y1n83CVy2lmn1npqs1n833*y1u1");
    string_constant_18 = 
	    STATIC_STRING("m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83-Gy1m9k83=my83*my1m9k83-Ty833*y1n83CVy2lmn1np1n830=yqsu1m83xLy1m9k9u1m83xLy1m9k9v1n83xLy1o1m9k83");
    string_constant_19 = 
	    STATIC_STRING("*Iy1m9k83-fZy1m9k83=Oy1m9k83-scy83-any1n83xLy1p1m9k83*Iy1m9k9m1m9k83-fZy1m9k83=Oy1m9k83-scy83-aty1n83xLy1o1m9k83*Iy1m9k83-cXy1m9");
    string_constant_20 = 
	    STATIC_STRING("k83=Oy1m9k83-scy83-amy1n83xLy1p1m9k83*Iy1m9k9m1m9k83-cXy1m9k83=Oy1m9k83-scy83-asy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qcheck_number_of_args);
    push_optimized_constant(Qreject_if_sequence_constant);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qnum_ge);
    push_optimized_constant(Qput_designation_in_qualifier);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qnum_ne);
    add_grammar_rules_function(regenerate_optimized_constant(list(14,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20)));
    string_constant_21 = 
	    STATIC_STRING("13Sy1m83aBy83-pey1o83aBy1n83-pey1m9k83=Uy83aBy1n83=Uyln9l1m83-pey83-pdy1o83-pey1n83-pdy1m9k83-ty83-pey1n83-tyln9l1m83-pdy83n8y1n");
    string_constant_22 = 
	    STATIC_STRING("83n8y1n1m9k83-9y83aBy1m9k83-Aym1n83n8y1o1m9k9m1m9k83-9y83aBy1m9k83-Ay1m9mn1p83n8y1n832ay1m9k83-9y83Ecy1ll9n9o1p83n8y1m832ay836ay");
    string_constant_23 = 
	    STATIC_STRING("2llm9n9o1n83n8y1n836Ey838Ry836Ey1nmln1n83n8y1n836Ey1m9k9p836Ey1nmln1n83n8y1n836Ey1m9k9q836Ey1nmln1o83n8y1m83F2y83-ppy2llm9r1n83n");
    string_constant_24 = 
	    STATIC_STRING("8y1o83-pmy1m9k831by1m9k83=Yy1m9k83*ly1m83RGyl1n83n8y1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C4y83C-y1m9k83*ly83-pjy2l83LWys1n83n8y1s1");
    string_constant_25 = 
	    STATIC_STRING("m9k83-9y1m9k8312y83aBy1m9k832Sy83aBy1m9k8332y83aBy1m9k83-Ay1o8348ynpr1n83n8y1q1m9k83-9y1m9k8312y83aBy1m9k832Sy83aBy1m9k83-Ay1n83");
    string_constant_26 = 
	    STATIC_STRING("48ynp1n83n8y1o83F2y1m9k83*Iy834Uy83F2y1o83-=ry1m9knlo1n83n8y1p83F2y1m9k83*Iy1m9k9m834Uy83F2y1o83-=py1m9kolp1m83n8y83F2y1n83-ppy1");
    string_constant_27 = 
	    STATIC_STRING("n1m9k831by1m9k83=Yy1m9k83*ly1m83RGy83hKy1n83-ppy1n1m9k831by1m9k83=Ty1m9k83*ly1m83RIy83hKy1n83-pmy1n1m9k83-9y836Ey1m9k83-Aym1n83-");
    string_constant_28 = 
	    STATIC_STRING("pmy1n1m9k83-9y83aBy1m9k83-Aym1n83-pmy1o1m9k9m1m9k83-9y83aBy1m9k83-Ay1m9mn1n83-pjy1n1m9k83-9y83aBy1m9k83-Ay1lm1n83-pjy1o1m9k83-9y");
    string_constant_29 = 
	    STATIC_STRING("83aBy1m9k83vy83-pky2lmo1n83-pky1m83aBy1m9k83-Ay1ll1n83-pky1n83aBy1m9k83vy83-pky2lln1n83F2y1s1m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83*my");
    string_constant_30 = 
	    STATIC_STRING("1m9k83-Ty83F2y1n83CVy2lmn1npqs1n83F2y1u1m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83-Gy1m9k83=my83*my1m9k83-Ty83F2y1n83CVy2lmn1np1n830=yqsu1");
    string_constant_31 = STATIC_STRING("n83F2y1n1m9k9s1m9k83-2y83-2y1m9kn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qcheck_number_of_args);
    push_optimized_constant(Qreject_if_sequence_constant);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qnum_ge);
    push_optimized_constant(Qput_designation_in_qualifier);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfirst);
    add_grammar_rules_function(regenerate_optimized_constant(list(11,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31)));
    Qrestrict_if_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-SLOT-EDIT-FEATURE",AB_package);
    string_constant_32 = 
	    STATIC_STRING("13Ly1m831Py83-Fby1o831Py1n83-Fby1m9k83=Uy831Py1n83=Uyln9l1n83-Ffy1n1m9k83-9y831Py1m9k83-Aym1n83-Ffy1o1m9k9m1m9k83-9y831Py1m9k83-");
    string_constant_33 = 
	    STATIC_STRING("Ay1m9mn1m83-Fby83-v0y1o83-Fby1n83-v0y1m9k83-ty83-Fby1n83-tyln9l1m83-v0y83dPy1n83dPy1n83-Fay83xLy83-Fay1nmln1m83dPy830By1n83dPy1n");
    string_constant_34 = 
	    STATIC_STRING("1m9k83-9y831Py1m9k83-Aym1n83dPy1o1m9k9m1m9k83-9y831Py1m9k83-Ay1m9mn1p83dPy1n832ay1m9k83-9y83Ecy1ll9n9o1p83dPy1m832ay836ay2llm9n9");
    string_constant_35 = 
	    STATIC_STRING("o1n83dPy1n83=xy838Ry83=xy1nmln1n83dPy1n83=xy1m9k9p83=xy1nmln1n83dPy1n83=xy1m9k9q83=xy1nmln1o83dPy1m830By83-Fiy2llm9r1n83dPy1o83-");
    string_constant_36 = 
	    STATIC_STRING("Fey1m9k831by1m9k83=Yy1m9k83*ly1m83RGyl1n83dPy1p83-Fey1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iOyl1n83dPy1o83-Fey1m9k831by1m9k83=");
    string_constant_37 = 
	    STATIC_STRING("Ty1m9k83*ly1m83RIyl1n83dPy1p83-Fey1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iPyl1n83dPy1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C4y83C-y");
    string_constant_38 = 
	    STATIC_STRING("1m9k83*ly83oEy2l83LWys1n83dPy1s1m9k83-9y1m9k8312y831Py1m9k832Sy831Py1m9k8332y831Py1m9k83-Ay1o8348ynpr1o83dPy1q1m9k83-9y1m9k8312y");
    string_constant_39 = 
	    STATIC_STRING("831Py1m9k832Sy831Py1m9k83-Ay1n8348ynp1n9u83=Vy83gAy1m83dPy830By");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qcheck_number_of_args);
    push_optimized_constant(Qreject_if_sequence_constant);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qnum_ge);
    push_optimized_constant(Qput_designation_in_qualifier);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qrestrict_if_slot_edit_feature);
    add_grammar_rules_function(regenerate_optimized_constant(list(8,
	    string_constant_32,string_constant_33,string_constant_34,
	    string_constant_35,string_constant_36,string_constant_37,
	    string_constant_38,string_constant_39)));
    string_constant_40 = 
	    STATIC_STRING("13Ey1n83-Fiy1n1m9k831by1m9k83=Yy1m9k83*ly1m83RGy83hKy1n83-Fiy1n1m9k831by1m9k83=Ty1m9k83*ly1m83RIy83hKy1n83-Fiy1o1m9k831by1m9k83=");
    string_constant_41 = 
	    STATIC_STRING("Yy1m9k831Sy1m9k83*ly1m83iOy83hKy1n83-Fiy1o1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iPy83hKy1n83-Fey1n1m9k83-9y83=xy1m9k83-Aym1n83");
    string_constant_42 = 
	    STATIC_STRING("-Fey1n1m9k83-9y831Py1m9k83-Aym1n83-Fey1o1m9k9l1m9k83-9y831Py1m9k83-Ay1m9ln1n83oEy1n1m9k83-9y831Py1m9k83-Ay1lm1n83oEy1o1m9k83-9y8");
    string_constant_43 = 
	    STATIC_STRING("31Py1m9k83vy83-v7y2lmo1n83-v7y1m831Py1m9k83-Ay1ll1n83-v7y1n831Py1m9k83vy83-v7y2lln1n830By1s1m9k9m83-Gy83*Zy1m9k83CWy1m9k9m83*my1");
    string_constant_44 = 
	    STATIC_STRING("m9k83-Ty830By1n83CVy2lmn1npqs1n830By1u1m9k9m83-Gy83*Zy1m9k83CWy1m9k9m83-Gy1m9k83=my83*my1m9k83-Ty830By1n83CVy2lmn1np1n830=yqsu1m");
    string_constant_45 = 
	    STATIC_STRING("83-Fay830By1n83-Fay1n1m9k83-9y831Py1m9k83-Aym1m83APy831Py1m83APy1m9k83Zy1m83-vky83APy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45)));
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qunique_logical_expression = STATIC_SYMBOL("UNIQUE-LOGICAL-EXPRESSION",
	    AB_package);
    Qcompile_unique_logical_expression_for_slot = 
	    STATIC_SYMBOL("COMPILE-UNIQUE-LOGICAL-EXPRESSION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_unique_logical_expression_for_slot,
	    STATIC_FUNCTION(compile_unique_logical_expression_for_slot,NIL,
	    TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qunique_logical_expression,
	    SYMBOL_FUNCTION(Qcompile_unique_logical_expression_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qunique_logical_expression,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qfake_attribute = STATIC_SYMBOL("FAKE-ATTRIBUTE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfake_attribute,Fake_attribute);
    Qgrammar3 = STATIC_SYMBOL("GRAMMAR3",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    string_constant_46 = STATIC_STRING("fake-attribute");
    list_constant_2 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_46);
    record_system_variable(Qfake_attribute,Qgrammar3,list_constant_2,Qnil,
	    Qnil,Qnil,Qnil);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qpart_stack = STATIC_SYMBOL("PART-STACK",AB_package);
    Qmark = STATIC_SYMBOL("MARK",AB_package);
    Qg2_lambda = STATIC_SYMBOL("G2-LAMBDA",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qitem,list_constant_3);
    list_constant = STATIC_CONS(list_constant_4,Qnil);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_5 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant_5);
    Qg2_fake_user_menu_choice_attribute = 
	    STATIC_SYMBOL("G2-FAKE-USER-MENU-CHOICE-ATTRIBUTE",AB_package);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    Quser_menu_choice_expression = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION",AB_package);
    Qcompile_user_menu_choice_expression_for_slot = 
	    STATIC_SYMBOL("COMPILE-USER-MENU-CHOICE-EXPRESSION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_user_menu_choice_expression_for_slot,
	    STATIC_FUNCTION(compile_user_menu_choice_expression_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Quser_menu_choice_expression,
	    SYMBOL_FUNCTION(Qcompile_user_menu_choice_expression_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Quser_menu_choice_expression,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Quser_menu_choice_expression_initialization = 
	    STATIC_SYMBOL("USER-MENU-CHOICE-EXPRESSION-INITIALIZATION",
	    AB_package);
    Qcompile_user_menu_choice_expression_initialization_for_slot = 
	    STATIC_SYMBOL("COMPILE-USER-MENU-CHOICE-EXPRESSION-INITIALIZATION-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_user_menu_choice_expression_initialization_for_slot,
	    STATIC_FUNCTION(compile_user_menu_choice_expression_initialization_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Quser_menu_choice_expression_initialization,
	    SYMBOL_FUNCTION(Qcompile_user_menu_choice_expression_initialization_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Quser_menu_choice_expression_initialization,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qfix_in_order_action_list = STATIC_SYMBOL("FIX-IN-ORDER-ACTION-LIST",
	    AB_package);
    Qsymbol_cannot_be_true_false_or_not = 
	    STATIC_SYMBOL("SYMBOL-CANNOT-BE-TRUE-FALSE-OR-NOT",AB_package);
    Qcategory_hack = STATIC_SYMBOL("CATEGORY-HACK",AB_package);
    Qunlist_1 = STATIC_SYMBOL("UNLIST-1",AB_package);
    Qunlist_1_2 = STATIC_SYMBOL("UNLIST-1-2",AB_package);
    Qcar_2_1 = STATIC_SYMBOL("CAR-2-1",AB_package);
    Qadd_layering_preservation_to_show_details = 
	    STATIC_SYMBOL("ADD-LAYERING-PRESERVATION-TO-SHOW-DETAILS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_layering_preservation_to_show_details,
	    STATIC_FUNCTION(add_layering_preservation_to_show_details,NIL,
	    FALSE,1,1));
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    Qcheck_ddd_dddd_format = STATIC_SYMBOL("CHECK-DDD-DDDD-FORMAT",AB_package);
    string_constant_47 = 
	    STATIC_STRING("13=6y1n833*y1n1m9k83=by83-Gy83*Zy1ml2lmn1m838Ry1m9k9l1m838Ry1m9k9m1m838Ry1m9k9n1m838Ry1m9k9o1m83-NMy1m9k9l1m83-NMy1m9k9m1m83-NMy");
    string_constant_48 = 
	    STATIC_STRING("1m9k9n1m83-NMy1m9k9p1m83-NMy1m9k9o1m83-NMy1m9k9q1m83vhy83-T6y1o83vhy1o83-T6y1m9k83-ty1m9k837ey83UQy1n83-tylo9r1m83-T6y83-T5y1o83");
    string_constant_49 = 
	    STATIC_STRING("-T6y1n83-T5y1m9k83=Uy83-T6y1n83=Uyln9r1m83-T5y83vmy1n83vmy1o833*y1m9k83-A0y1m9k83=Yy1m9k83*ly1m83-A1yl1n83vmy1q833*y1m9k83-Tjy1m");
    string_constant_50 = 
	    STATIC_STRING("9k83=3y1m9k839ry1m9k83=Yy1m9k83*ly1m83-Tkyl1n83vmy1n833*y1m9k83*Iy1m9k83-fvy1m83-aoyl1n83vmy1q833*y1m9k83*Iy1m9k83-fvy1m9k83*ty1");
    string_constant_51 = 
	    STATIC_STRING("m9k9s1m9k83oIy1m83-aqyl1n83vmy1p833*y1m9k83*Iy1m9k83-fvy1m9k83*ty1m9k830Jy1m83-apyl1n83vmy1q833*y1m9k83*Iy1m9k83-mQy1m9k83*ty1m9");
    string_constant_52 = 
	    STATIC_STRING("k9s1m9k83oIy1m83-auyl1n83vmy1o833*y1m9k83-Key834Uy833*y1o83-Kfy1m9knlo1n83vmy1q833*y1m9k83-Lly1m9k83=3y1m9k83-Kdy834Uy833*y1o83-");
    string_constant_53 = 
	    STATIC_STRING("Lmy1m9kplq1n83vmy1n833*y1m9k83*Iy1m9k83GSy1m83-agyl1n83vmy1n833*y1m9k83*Iy1m9k83-QTy1m83-ajyl1n83vmy1n833*y1m9k83*Iy1m9k83h1y1m8");
    string_constant_54 = 
	    STATIC_STRING("3-alyl1n83vmy1n833*y1m9k83*Iy1m9k83vBy1m83-akyl1n83vmy1o833*y1m9k83-dMy1m9k83-bFy1m9k83*ly1m83-dNyl1n83vmy1q1m9k83=by1m9k831Ly1m");
    string_constant_55 = 
	    STATIC_STRING("9k83-Ty83-Gy1m9k83*Iy1m9k83-PNy1m83-aiy1m83=byo1n83vmy1r1m9k83=by1m9k831Ly1m9k83-Ty83-Gy83*Zy1m9k83*Iy1m9k83-PNy1m83-aiy1m83=by2");
    string_constant_56 = 
	    STATIC_STRING("lop1n83vmy1p833*y1m9k83-Key1m9k83-BVy1m9k83=3y833*y1n83-W4ylp1n83vmy1r833*y1m9k83-Lly1m9k83=3y1m9k83-Kdy1m9k83-BVy1m9k83=3y833*y");
    string_constant_57 = 
	    STATIC_STRING("1n83-W6ylr1n83vmy1q83-T3y1m9k83*Iy1m9k83-RMy1m9k83Igy1m9k83=3y833*y1o83-W7yl1m9k83-gnyq1n83vmy1r83-T3y1m9k83*Iy1m9k83-RMy1m9k83I");
    string_constant_58 = 
	    STATIC_STRING("gy1m9k83=3y83-O8y833*y1o83-W7y1m83=by83=+y1m9kqr1n83vmy1r1m9k83=Yy1m9k83=+y1m9k83*Iy1m9k83-RMy1m9k83-RRy1m9k832+y833*y1n83-W8y1m");
    string_constant_59 = 
	    STATIC_STRING("9k83-gnyr1n83vmy1s1m9k83=Yy1m9k83=+y1m9k83*Iy1m9k83-RMy1m9k83-RRy1m9k832+y83-O8y833*y1n83-W8y1m9krs1n83vmy1s1m9k83=Yy1m9k83=+y83");
    string_constant_60 = 
	    STATIC_STRING("-pOy1m9k83*Iy1m9k83-RMy1m9k83Igy1m9k83=3y833*y1o83-RNy1m83=byn1m9k83-gnys1n83vmy1t1m9k83=Yy1m9k83=+y83-pOy1m9k83*Iy1m9k83-RMy1m9");
    string_constant_61 = 
	    STATIC_STRING("k83Igy1m9k83=3y83-O8y833*y1o83-RNy1m83=byn1m9kst1n83vmy1s1m9k83=Yy1m9k83=+y83-pOy1m9k83*Iy1m9k83-RMy1m9k83-RRy1m9k832+y833*y1o83");
    string_constant_62 = 
	    STATIC_STRING("-ROy1m9kn1m9k83-gnys1n83vmy1t1m9k83=Yy1m9k83=+y83-pOy1m9k83*Iy1m9k83-RMy1m9k83-RRy1m9k832+y83-O8y833*y1o83-ROy1m9kn1m9kst1n83vmy");
    string_constant_63 = 
	    STATIC_STRING("1t1m9k83=Yy1m9k83=+y83*Zy83-pOy1m9k83*Iy1m9k83-RMy1m9k83Igy1m9k83=3y833*y1o83-RNy1m83=by2lon1m9k83-gnyt1n83vmy1u1m9k83=Yy1m9k83=");
    string_constant_64 = 
	    STATIC_STRING("+y83*Zy83-pOy1m9k83*Iy1m9k83-RMy1m9k83Igy1m9k83=3y83-O8y833*y1o83-RNy1m83=by2lon1m9ktu1n83-T3y1m1m9k83=Yy1m9k83=+y1m83=bym1n83-T");
    string_constant_65 = 
	    STATIC_STRING("3y1n1m9k83=Yy1m9k83=+y83*Zy1m83=by2lmn1n83-pOy1n1m9k83-Ty1m9k83-Gy83BOyn1n83-O8y1m839jy1m9k83-Tyl1n83-O8y1n1m9k83=ay1m9k83dy1m9k");
    string_constant_66 = 
	    STATIC_STRING("83=3y83f8y1n83-O8y1n1m9k83=ay1m9k83py1m9k83-Ty83f9y1n83vmy1p833*y1m9k83*Iy1m9k83Igy1m9k83=3y833*y1n83-Zlylp1n83vmy1p833*y1m9k83*");
    string_constant_67 = 
	    STATIC_STRING("Iy1m9k83-RRy1m9k832+y833*y1n83-Zmylp1m83lsy1m9k9s1m83lsy1m9k83=by1m83-Fjy1m9k9s1m83-Cvy1m9k9s1m832ay1m9k83fFy1m832ay1m9k833Oy1m8");
    string_constant_68 = 
	    STATIC_STRING("32ay1m9k833Ty1m832ay1m9k9t1m832ay1m9k83-2y1m832ay83-6y1o83pNy1n836Yy1m9k83-ty83pOy1n83-tyln9r1m83pNy836Yy1o83pOy1n836Yy1m9k83-ty");
    string_constant_69 = 
	    STATIC_STRING("83pOy1n83-tyln9r1m83pOy836Yy1n83pNy1n1m9k83*Xy1m9k83-hvy836Yy1m83-ZHyn1o83pNy1n1m9k83*Xy1m9k83-hvy83-J4y1m83-ZHyn9u1o83-J4y1n836");
    string_constant_70 = 
	    STATIC_STRING("Yy1m9k83-ty83-J5y1n83-tyln9r1o83-J5y1n836Yy1m9k83-ty83-J5y1n83-tyln9r1m83-J5y836Yy1n83-Njy1n1m9k83=Fy1m9k83vry83=xy1on0001n83-Nj");
    string_constant_71 = 
	    STATIC_STRING("y1o1m9k83=Fy1m9k83g-y1m9k831Ay83=xy1o0o001n83-Njy1r1m9k83=Fy1m9k83vry83=xy1m9k83=Fy1m9k83g-y1m9k831Ay83=xy1onr001n83-Njy1r1m9k83");
    string_constant_72 = 
	    STATIC_STRING("=Fy1m9k83g-y1m9k831Ay83=xy1m9k83=Fy1m9k83vry83=xy1oro001n83-Njy1m1m9k83-NNy83=xy1o00m01n83-Njy1o1m9k83-NNy83=xy1m9k83-may83*Zy1o");
    string_constant_73 = 
	    STATIC_STRING("00mo1n836Yy1r1m9k83g9y1m9k8319y8330y1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83-Ngyn1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k831by1m9k83");
    string_constant_74 = 
	    STATIC_STRING("=Ty1m9k83*ly1m83-Nhyn1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k838By1m9k9v1m9k83vpy1m83-Nhyn1n836Yy1n1m9k83g9y1m9k8319y8330y1r83g9yn00");
    string_constant_75 = 
	    STATIC_STRING("0001n836Yy1o1m9k83g9y1m9k8319y1m9k9v8330y1q83-Niyo00001n836Yy1p1m9k83g9y1m9k8319y8330y1m9k83*Iy1m9k832Zy1q83-Niyn00001n836Yy1p1m");
    string_constant_76 = 
	    STATIC_STRING("9k83g9y1m9k8319y8330y1m9k83*Iy1m9k83=Oy1r83g9yn000001n836Yy1p1m9k83g9y1m9k8319y8330y1m9k9l83=xy1r83g9ynp00001n836Yy1p1m9k83g9y1m");
    string_constant_77 = 
	    STATIC_STRING("9k8319y8330y1m9k9l83dPy1r83g9ynp00001o836Yy1p1m9k83g9y1m9k8319y8330y1m9k83*Iy830Ty1r83g9yn1m9kp00009w1n836Yy1o1m9k83g9y1m9k8319y");
    string_constant_78 = 
	    STATIC_STRING("8330y83-Njy2n83g9yn0o1n836Yy1p1m9k83g9y1m9k8319y1m9k9v8330y83-Njy2m83-Niyop1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k83*Iy1m9k832Zy83-");
    string_constant_79 = 
	    STATIC_STRING("Njy2m83-Niynq1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k83*Iy1m9k83=Oy83-Njy2n83g9yn0q1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k9l83=xy83-Njy");
    string_constant_80 = 
	    STATIC_STRING("2n83g9ynpq1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k9l83dPy83-Njy2n83g9ynpq1o836Yy1q1m9k83g9y1m9k8319y8330y1m9k83*Iy83-2y83-Njy2n83g9y");
    string_constant_81 = 
	    STATIC_STRING("n1m9kpq9w1n836Yy1n1m9k83-ULy1m9k830Py8330y1n83-ULyn01o836Yy1n1m9k83D8y83-Lgy83-Eky1o83D8ym009x1o836Yy1p1m9k83D8y83-Lgy83-Eky1m9k");
    string_constant_82 = 
	    STATIC_STRING("83=Iy8330y1o83D8ymp09x1o83-9My1q1m9k83D8y83-Lgy83-Eky1m9k83vy1m9k83-KHy1m9k83-NVy1o83D8ym08k9x1o83-9My1s1m9k83D8y83-Lgy83-Eky1m9");
    string_constant_83 = 
	    STATIC_STRING("k83=Iy8330y1m9k83vy1m9k83-KHy1m9k83-NVy1o83D8ymp8k9x1n83-9My1q1m9k83-ULy1m9k830Py8330y1m9k83vy1m9k83-KHy1m9k83-NVy1n83-ULyn8k1n8");
    string_constant_84 = 
	    STATIC_STRING("36Yy1r1m9k83-Xay1m9k83=Fy83-Uy1m9k8312y1m9k83fSy1m9k83pjy1m9k83h1y1m83-Xayn1n836Yy1p1m9k83-Xay1m9k8312y1m9k83fSy1m9k83pjy1m9k83h");
    string_constant_85 = 
	    STATIC_STRING("1y1l83-Xay1n836Yy1o1m9k83-=Wy8330y1m9k8319y83-eYy1n83-=Wymo1n836Yy1p1m9k83-=Wy8330y83-Zqy1m9k8319y83-eYy2n83-=Wympn1n836Yy1p1m9k");
    string_constant_86 = 
	    STATIC_STRING("83-=Wy1m9k9s1m9k83-hry1m9k8319y83-eYy1n83-=Wy1m9s83-hryp1n836Yy1m1m9k83-97y83-eYy1n83-=Wy1m9s83-hrym1n836Yy1n1m9k83-97y83-Zpy83-");
    string_constant_87 = 
	    STATIC_STRING("eYy2n83-=Wy1m9s83-hrynm1n836Yy1q1m9k83-=Wy1m9k9s1m9k83-hry83-Zqy1m9k8319y83-eYy2n83-=Wy1m9s83-hryqo1m83-Zqy83-Zuy1o83-Zqy1m83-Zu");
    string_constant_88 = 
	    STATIC_STRING("y83-Zry2llm9y1m83-Zqy83-Zry1m83-Zry83-Zty1m83-Zry83-Zpy1o83-Zry1m83-Zty83-Zpy1mlm9z1o83-Zpy1o1m9k83=Iy1m9k9s1m9k837Fy83-oy1l1m83");
    string_constant_89 = 
	    STATIC_STRING("-S=yo93Cy1n83-Zuy1m1m9k830Py830By1l1m830Pym1n83-Zty1m83-Kjy830By1l1mlm1m83-Kjy1m9k83HCy1m83-Kjy1m9k83GOy1n836Yy1o1m9k93Dy8330y1m");
    string_constant_90 = 
	    STATIC_STRING("9k83=3y83=xy1n93Dymo1n836Yy1p1m9k83-J7y1m9k9s1m9k83b5y1m9k83-Ty8330y1mlp1n836Yy1p1m9k83-QSy1m9k9s1m9k83b5y1m9k83-Ty8330y1mlp1n83");
    string_constant_91 = 
	    STATIC_STRING("6Yy1m1m9k83n-y8330y1m83-onym1n836Yy1n1m9k83n-y8330y83-ZKy1n83-onymn1n836Yy1o1m9k83n-y8330y83-ZKy83-ndy1o83-onymno1o836Yy1r1m9k83");
    string_constant_92 = 
	    STATIC_STRING("n-y8330y83-ZKy83-ndy1m9k83lfy1m9k83*qy1m9k83-cHy1o83-onymno93Ey1n836Yy1o1m9k83n-y8330y83-ZKy83-jRy2n83-onymno1o836Yy1r1m9k83n-y8");
    string_constant_93 = 
	    STATIC_STRING("330y83-ZKy83-jRy1m9k83lfy1m9k83*qy1m9k83-cHy2n83-onymno93Ey1n836Yy1p1m9k83n-y8330y83-ZKy83-ndy83-jRy2o83-onymnop1o836Yy1s1m9k83n");
    string_constant_94 = 
	    STATIC_STRING("-y8330y83-ZKy83-ndy83-jRy1m9k83lfy1m9k83*qy1m9k83-cHy2o83-onymnop93Ey1n836Yy1n1m9k83n-y8330y83-ndy1n83-onymn1o836Yy1q1m9k83n-y83");
    string_constant_95 = 
	    STATIC_STRING("30y83-ndy1m9k83lfy1m9k83*qy1m9k83-cHy1n83-onymn93Ey1n836Yy1o1m9k83n-y8330y83-ndy83-jRy2n83-onymno1o836Yy1r1m9k83n-y8330y83-ndy83");
    string_constant_96 = 
	    STATIC_STRING("-jRy1m9k83lfy1m9k83*qy1m9k83-cHy2n83-onymno93Ey1n836Yy1n1m9k83n-y8330y83-jRy2m83-onymn1o836Yy1q1m9k83n-y8330y83-jRy1m9k83lfy1m9k");
    string_constant_97 = 
	    STATIC_STRING("83*qy1m9k83-cHy2m83-onymn93Ey1m836Yy1m1m9k83-Y+y8330y1m836Yy1n1m9k83-Y+y8330y83-ZKy1n836Yy1q1m9k83g9y1m9k8319y8330y1m9k83*Iy834U");
    string_constant_98 = 
	    STATIC_STRING("y8330y1o83-JEypnq1n836Yy1r1m9k83g9y1m9k8319y8330y1m9k83*Iy1m9k9v834Uy8330y1o83-mByqnr1n836Yy1r1m9k83g9y1m9k8319y8330y1m9k83*Iy1m");
    string_constant_99 = 
	    STATIC_STRING("9k83-h4y834Uy8330y1p83-JEyqnr83-h4y1n836Yy1m1m9k93Fy8330y1mlm1n836Yy1n1m9k83-pDy1m9k838Cy1m9k830Jy1l83n2y1n836Yy1m1m9k834Wy1m9k8");
    string_constant_100 = 
	    STATIC_STRING("3-1jy1l83-mOy1n836Yy1m1m9k831iy1m9k83-1jy1l83-igy1m836Yy1m1m9k93Gy8330y1n83-ZKy1m1m9k830Py83-x9y1m83*Xym1m83-x9y8330y1n83-jRy83-");
    string_constant_101 = 
	    STATIC_STRING("noy1ll1n83-jRy1m83-xVy83-noy1mlm1n83-xVy1s1m9k83=Fy1m9k83wTy1m9k835xy1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1m83-xUy1mpr1n83-noy1t1");
    string_constant_102 = 
	    STATIC_STRING("m9k83=Gy1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1m9k83*Xy1m9k9s1m9k83-nmy1m83-nny1n83=Gynp1n83-ndy83-ney1m83-nUyl1n83-ney1n1m9k83=Gy");
    string_constant_103 = 
	    STATIC_STRING("83-nWy1m9k83-nUym1m83-nWy1m9k83-hhy1m83-nWy1m9k83-XZy1m83-nWy1m9k83-sry1m83-nWy1m9k83-V9y1n83-ney1n1m9k83-CJy1m9k83*ty83-nVy2l83");
    string_constant_104 = 
	    STATIC_STRING("-V9yn1n83-ney1r1m9k83-CJy1m9k83*ty1m9k83-bFy1m9k831Sy1m9k83-nUy1m9k83-tIy83-nVy2l831Syr1n83-nVy83=xy1ll1n83-nVy1p1m9k83-9y83=xy1");
    string_constant_105 = 
	    STATIC_STRING("m9k83vy83=xy1m9k83-Ay1mmo1n83-noy1q83-dBy1m9k9s83-lOy1m9k83-Ty1m9k9s1m9k83-nmy1n83-nnyln1m83-lOy1m9k83-cy1m83-lOy1m83-Loy1m9k83-");
    string_constant_106 = 
	    STATIC_STRING("cy1n83-lOy1m83-Oky1m9k83-Ojyl1m83-Xcy1m9k83*hy1m83-Xcy1m9k83-by1m83-tby1m9k83hy1m83-tby1m9k83gy1m83-Loy83-Xcy1m83-Loy83-tby1m83-");
    string_constant_107 = 
	    STATIC_STRING("Oky1m83-tby83-Xcy1m83-dBy1m9k83=Gy1m83-dBy83-hTy1n83-hTy1m83-hUy83-YDy1mml1n83-hTy1m83-hUy83-wVy1mml1n83-hTy1p83-hUy83-YDy1m9k83");
    string_constant_108 = 
	    STATIC_STRING("-ty83-hUy83-wVy1omlpo1n83-hUy1m83=xy1m9k83Fgyl1m83-wVy1m9k83GOy1m83-wVy1m9k83HCy1n83-YDy1o1m9k83=3y1m9k9s83-Xcy1m9k83-Tyn1n83-xV");
    string_constant_109 = 
	    STATIC_STRING("y1n1m9k83=Fy1m9k83-bFy83-lOy1m83-xUyn1m83-eYy83-Uy1o83-eYy1m83Toy83-hly1n83-tylm9r1o83-hly1m83-eTy83ZBy1n83-tylm9r1o83-hly1m83-e");
    string_constant_110 = 
	    STATIC_STRING("Ty83-eZy1n83-tylm9r1o83-eZy1m83VUy83-hly1n83-tylm9r1m83-eTy83=xy1n83-eTy1p83=xy1m9k83*5y83=Zy1m9k831Ay1m9k83A*y1n838Pyl1m9k832ny");
    string_constant_111 = 
	    STATIC_STRING("1n83-eTy1o83=xy1m9k83*5y83=Zy1m9k83-oy1n838Pyl1m9k832Ky1o83-eTy1n83=xy1m9k83*5y83J9y1n83J9yln93Hy1o83-o8y1n83-Uy1m9k83vy83-o8y1n");
    string_constant_112 = 
	    STATIC_STRING("83-tyln9r1m83J9y83-6y1m83-R9y83-6y1n83-R9y1m1m9k9s83-6ym1m83-Lgy83mXy1n83-Lgy1n83mXy1m9k83-ty83mXy1n83-tyln1o83-Lgy1n83mXy1m9k83");
    string_constant_113 = 
	    STATIC_STRING("vy83-Lhy1n83-tyln9r1n83-Lhy1o83mXy1m9k83vy1m9k83-ty83mXy1n83-tylo1o83-Lhy1n83mXy1m9k83vy83-Lhy1n83-tyln9r1m83mXy83-6y1m839jy83-6");
    string_constant_114 = STATIC_STRING("y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qnum_ne);
    push_optimized_constant(Qnum_lt);
    push_optimized_constant(Qnum_gt);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qnum_ge);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qfix_in_order_action_list);
    push_optimized_constant(Qnot);
    push_optimized_constant(Qsymbol_cannot_be_true_false_or_not);
    push_optimized_constant(Qcategory_hack);
    push_optimized_constant(Qunlist_1);
    push_optimized_constant(Qunlist_1_2);
    push_optimized_constant(Qcar_2_1);
    push_optimized_constant(Qset);
    push_optimized_constant(Qadd_layering_preservation_to_show_details);
    push_optimized_constant(Qabort_g2);
    push_optimized_constant(Qprint);
    push_optimized_constant(Qcheck_ddd_dddd_format);
    add_grammar_rules_function(regenerate_optimized_constant(nconc2(list(50,
	    string_constant_47,string_constant_48,string_constant_49,
	    string_constant_50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67,
	    string_constant_68,string_constant_69,string_constant_70,
	    string_constant_71,string_constant_72,string_constant_73,
	    string_constant_74,string_constant_75,string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79,
	    string_constant_80,string_constant_81,string_constant_82,
	    string_constant_83,string_constant_84,string_constant_85,
	    string_constant_86,string_constant_87,string_constant_88,
	    string_constant_89,string_constant_90,string_constant_91,
	    string_constant_92,string_constant_93,string_constant_94,
	    string_constant_95,string_constant_96),list(18,
	    string_constant_97,string_constant_98,string_constant_99,
	    string_constant_100,string_constant_101,string_constant_102,
	    string_constant_103,string_constant_104,string_constant_105,
	    string_constant_106,string_constant_107,string_constant_108,
	    string_constant_109,string_constant_110,string_constant_111,
	    string_constant_112,string_constant_113,string_constant_114))));
    Qddd_dot_dddd_format = STATIC_SYMBOL("DDD.DDDD-FORMAT",AB_package);
    Qregistered_directory_of_names_p = 
	    STATIC_SYMBOL("REGISTERED-DIRECTORY-OF-NAMES-P",AB_package);
    mutate_global_property(Qddd_dot_dddd_format,T,
	    Qregistered_directory_of_names_p);
    Qrule_category_name = STATIC_SYMBOL("RULE-CATEGORY-NAME",AB_package);
    mutate_global_property(Qrule_category_name,T,
	    Qregistered_directory_of_names_p);
    Qadd_generic_rule_grammar = STATIC_SYMBOL("ADD-GENERIC-RULE-GRAMMAR",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qadd_generic_rule_grammar,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant = 
	    STATIC_STRING("1m1n83vmy1p833*y1m9k831by83=Zy83-6y1m9k83vgy1o83-W9yl1m9ko1m83=by83Ry1n83vmy1q833*y1m9k831by83=Zy83-6y1m9k83vgy83*Zy1o83-W9yl1m9");
    string_constant_1 = STATIC_STRING("ko1m83=by2l83Ryq");
    SET_SYMBOL_FUNCTION(Qadd_generic_rule_grammar,
	    STATIC_FUNCTION(add_generic_rule_grammar,NIL,FALSE,0,0));
    Qextend_action_grammar = STATIC_SYMBOL("EXTEND-ACTION-GRAMMAR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qextend_action_grammar,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_2 = 
	    STATIC_STRING("1m1n836Yy1m1m9k836Gy1m9k83-1jy1l83-qky1n836Yy1m1m9k83Z4y1m9k83-1jy1l83-mvy");
    SET_SYMBOL_FUNCTION(Qextend_action_grammar,
	    STATIC_FUNCTION(extend_action_grammar,NIL,FALSE,0,0));
}
