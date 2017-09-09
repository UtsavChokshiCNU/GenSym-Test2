/* gram3.c
 * Input file:  grammar3.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
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

    x_note_fn_call(197,0);
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

    x_note_fn_call(197,1);
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
    PUSH_SPECIAL(Current_computation_frame,current_computation_frame,0);
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

static Object Qab_gensym;          /* gensym */

static Object Qg2_cell_array;      /* g2-cell-array */

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
    Object current_flag_state_qm, slot_description, new_cons;
    Object gensymed_symbol_1, temp, stack_of_slot_value_changes;
    Object gensymed_symbol_2, gensymed_symbol_3, temp_1;
    Object old_current_part_description, part_feature_index;
    Object exit_feature_handler, gensym_pop_store, cons_1, next_cons;
    Object frame_and_slot_or_atom, ab_loop_list_, ab_loop_it_;
    SI_Long svref_new_value;
    char temp_2;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(197,2);
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
    PUSH_SPECIAL(Current_computation_frame,current_computation_frame,4);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL(Current_computation_component_particulars,current_computation_component_particulars,
	      3);
	current_computation_style = The_only_dynamic_computation_style;
	PUSH_SPECIAL(Current_computation_style,current_computation_style,2);
	  current_block_of_dependent_frame = user_menu_choice;
	  PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
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
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_gensym_cons_pool();
	    if (Nil)
		gensymed_symbol_1 = nconc2(gensym_list_2(user_menu_choice,
			slot_description),gensym_cons_1(Nil,Nil));
	    else {
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = user_menu_choice;
		M_CDR(gensymed_symbol_1) = slot_description;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    }
	    M_CAR(gensymed_symbol) = gensymed_symbol_1;
	    temp = Stack_of_slot_value_changes;
	    M_CDR(gensymed_symbol) = temp;
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	    stack_of_slot_value_changes = gensymed_symbol;
	    PUSH_SPECIAL(Stack_of_slot_value_changes,stack_of_slot_value_changes,
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
		  svref_new_value = IFIX(ISVREF(user_menu_choice,
			  (SI_Long)5L)) | (SI_Long)16777216L;
		  ISVREF(user_menu_choice,(SI_Long)5L) = FIX(svref_new_value);
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
		      new_cons = Available_gensym_conses;
		      if (new_cons) {
			  Available_gensym_conses = M_CDR(new_cons);
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_gensym_cons_pool();
		      temp = Current_part_description;
		      M_CAR(gensymed_symbol) = temp;
		      temp = Stack_of_current_part_descriptions;
		      M_CDR(gensymed_symbol) = temp;
		      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		      Stack_of_current_part_descriptions = gensymed_symbol;
		  }
		  new_cons = Available_gensym_conses;
		  if (new_cons) {
		      Available_gensym_conses = M_CDR(new_cons);
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_gensym_cons_pool();
		  M_CAR(gensymed_symbol) = Qmark;
		  temp = Part_feature_recall_stack;
		  M_CDR(gensymed_symbol) = temp;
		  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
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
		  gensym_pop_store = Nil;
		  cons_1 = Part_feature_recall_stack;
		  if (cons_1) {
		      gensym_pop_store = M_CAR(cons_1);
		      next_cons = M_CDR(cons_1);
		      inline_note_reclaim_cons(cons_1,Qab_gensym);
		      temp = Available_gensym_conses;
		      M_CDR(cons_1) = temp;
		      Available_gensym_conses = cons_1;
		  }
		  else
		      next_cons = Nil;
		  Part_feature_recall_stack = next_cons;
		  part_feature_index = gensym_pop_store;
		  if (EQ(part_feature_index,Qmark))
		      goto end_loop;
		  exit_feature_handler = ISVREF(Part_feature_exit_methods,
			  IFIX(part_feature_index));
		  inline_funcall_0(exit_feature_handler);
		  goto next_loop;
		end_loop:;
		  Current_part_description = old_current_part_description;
		  if (Maintain_stack_of_current_part_descriptions_p) {
		      gensym_pop_store = Nil;
		      cons_1 = Stack_of_current_part_descriptions;
		      if (cons_1) {
			  gensym_pop_store = M_CAR(cons_1);
			  next_cons = M_CDR(cons_1);
			  inline_note_reclaim_cons(cons_1,Qab_gensym);
			  temp = Available_gensym_conses;
			  M_CDR(cons_1) = temp;
			  Available_gensym_conses = cons_1;
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
		  svref_new_value = IFIX(ISVREF(user_menu_choice,
			  (SI_Long)5L)) &  ~(SI_Long)16777216L;
		  ISVREF(user_menu_choice,(SI_Long)5L) = FIX(svref_new_value);
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
	      gensym_pop_store = Nil;
	      cons_1 = Stack_of_slot_value_changes;
	      if (cons_1) {
		  gensym_pop_store = M_CAR(cons_1);
		  next_cons = M_CDR(cons_1);
		  inline_note_reclaim_cons(cons_1,Qab_gensym);
		  temp = Available_gensym_conses;
		  M_CDR(cons_1) = temp;
		  Available_gensym_conses = cons_1;
	      }
	      else
		  next_cons = Nil;
	      Stack_of_slot_value_changes = next_cons;
	      reclaim_gensym_tree_1(gensym_pop_store);
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

    x_note_fn_call(197,3);
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

    x_note_fn_call(197,4);
    cddr_new_value = phrase_cons(T,CDDR(parse));
    M_CDDR(parse) = cddr_new_value;
    return VALUES_1(parse);
}

static Object string_constant;     /* "1m1n83vry1p833*y1m9k831by83=Zy83-6y1m9k83vly1o83-Vhyl1m9ko1m83=by83Ry1n83vry1q833*y1m9k831by83=Zy83-6y1m9k83vly83*Zy1o83-Vhyl1m9" */

static Object string_constant_1;   /* "ko1m83=by2l83Ryq" */

/* ADD-GENERIC-RULE-GRAMMAR */
Object add_generic_rule_grammar()
{
    XDeclare_area(1);
    Object result;

    x_note_fn_call(197,5);
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

static Object string_constant_2;   /* "1m1n836Yy1m1m9k836Gy1m9k83-1my1l83-pFy1n836Yy1m1m9k83Z8y1m9k83-1my1l83-ldy" */

/* EXTEND-ACTION-GRAMMAR */
Object extend_action_grammar()
{
    XDeclare_area(1);

    x_note_fn_call(197,6);
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
    Object Qfake_attribute, string_constant_46, Kfuncall;
    Object Qunique_logical_expression;
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

    x_note_fn_call(197,7);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qreject_if_float_interval = STATIC_SYMBOL("REJECT-IF-FLOAT-INTERVAL",
	    AB_package);
    Qconvert_history_interval = STATIC_SYMBOL("CONVERT-HISTORY-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qconvert_history_interval,
	    STATIC_FUNCTION(convert_history_interval,NIL,FALSE,1,1));
    string_constant_3 = 
	    STATIC_STRING("13Ky1m83nBy83-Hy1m83-Cwy836Ey1n83-Cwy1q1m9k8312y83aFy1m9k832Sy836Ey1m9k8332y83-Cwy1o8348ymoq1n83-Cwy1o1m9k8312y83aFy1m9k832Sy836");
    string_constant_4 = 
	    STATIC_STRING("Ey1n8348ymo1m83f7y83-oy1o83f7y83=xyl9l1o83f7y1m83=xy83ldy1mlm9m1m83-1sy83-oy1o83-1sy1m83=xy83ldy1mlm9m1m83lly83=xy1m83-Fay83-oy1");
    string_constant_5 = 
	    STATIC_STRING("o83-Fay83=xyl9l1o83-Fay1m83=xy83ldy1mlm9m1m83-Fgy83-oy1o83-Fgy1m83=xy83ldy1mlm9m1m83-Fky83=xy1m83-Cuy83-oy1o83-Cuy836Eyl9l1o83-C");
    string_constant_6 = 
	    STATIC_STRING("uy1m836Ey83ldy1mlm9m1m83-Cxy83-oy1o83-Cxy1m836Ey83ldy1mlm9m1m83-oPy836Ey1m83gYy1m9k83-Ppy1m83gYy1m9k83ucy");
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
	    STATIC_STRING("13cy1m83UTy83-RLy1o83UTy1n83-Fey1m9k83=Uy831Py1n83=Uyln9l1n83-8ly1n1m9k83-9y83UTy1m9k83-Aym1n83-8ly1o1m9k9m1m9k83-9y831Py1m9k83-");
    string_constant_8 = 
	    STATIC_STRING("Ay1m9mn1m83-RLy83-Nny1o83-RLy1n83-Nny1m9k83-ty83-RLy1n83-tyln9l1m83-Nny83kcy1n83kcy1n1m9k83-9y83UTy1m9k83-Aym1n83kcy1o1m9k9m1m9k");
    string_constant_9 = 
	    STATIC_STRING("83-9y831Py1m9k83-Ay1m9mn1p83kcy1n832ay1m9k83-9y83Ecy1ll9n9o1p83kcy1m832ay836ay2llm9n9o1n83kcy1n83=py838Ry83=py1nmln1n83kcy1n83-Q");
    string_constant_10 = 
	    STATIC_STRING("iy83xQy83-Qiy1nmln1n83kcy1n83=py1m9k9p83=py1nmln1n83kcy1n83=py1m9k9q83=py1nmln1o83kcy1m833*y83-jYy2llm9r1n83kcy1o83-hKy1m9k831by");
    string_constant_11 = 
	    STATIC_STRING("1m9k83=Yy1m9k83*ly1m83RJyl1n83kcy1p83-hKy1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iTyl1n83kcy1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C");
    string_constant_12 = 
	    STATIC_STRING("4y83C-y1m9k83*ly83oJy2l83LZys1n83kcy1s1m9k83-9y1m9k8312y831Py1m9k832Sy831Py1m9k8332y831Py1m9k83-Ay1o8348ynpr1n83kcy1q1m9k83-9y1m");
    string_constant_13 = 
	    STATIC_STRING("9k8312y831Py1m9k832Sy831Py1m9k83-Ay1n8348ynp1m83-Qiy833*y1n83-Qiy1n1m9k83-9y83UTy1m9k83-Aym1n83-jYy1n1m9k831by1m9k83=Yy1m9k83*ly");
    string_constant_14 = 
	    STATIC_STRING("1m83RJy83hPy1n83-jYy1n1m9k831by1m9k83=Ty1m9k83*ly1m83RLy83hPy1n83-jYy1o1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iTy83hPy1n83-jYy1");
    string_constant_15 = 
	    STATIC_STRING("o1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iUy83hPy1n83-hKy1n1m9k83-9y83=py1m9k83-Aym1n83-hKy1n1m9k83-9y83UTy1m9k83-Aym1n83-hKy1o1");
    string_constant_16 = 
	    STATIC_STRING("m9k9m1m9k83-9y831Py1m9k83-Ay1m9mn1n83-2ay1n1m9k83-9y83UTy1m9k83-Ay1lm1n83-2ay1o1m9k83-9y83UTy1m9k83vy83-cLy2lmo1n83-cLy1m83UTy1m");
    string_constant_17 = 
	    STATIC_STRING("9k83-Ay1ll1n83-cLy1n83UTy1m9k83vy83-cLy2lln1n833*y1s1m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83*my1m9k83-Ty833*y1n83CVy2lmn1npqs1n833*y1u1");
    string_constant_18 = 
	    STATIC_STRING("m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83-Gy1m9k83=my83*my1m9k83-Ty833*y1n83CVy2lmn1np1n830=yqsu1m83xQy1m9k9u1m83xQy1m9k9v1n83xQy1o1m9k83");
    string_constant_19 = 
	    STATIC_STRING("*Iy1m9k83-eby1m9k83=Oy1m9k83-r1y83-a-y1n83xQy1p1m9k83*Iy1m9k9m1m9k83-eby1m9k83=Oy1m9k83-r1y83-a3y1n83xQy1o1m9k83*Iy1m9k83-bdy1m9");
    string_constant_20 = 
	    STATIC_STRING("k83=Oy1m9k83-r1y83-a+y1n83xQy1p1m9k83*Iy1m9k9m1m9k83-bdy1m9k83=Oy1m9k83-r1y83-a2y");
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
	    STATIC_STRING("13Sy1m83aFy83-oFy1o83aFy1n83-oFy1m9k83=Uy83aFy1n83=Uyln9l1m83-oFy83-oEy1o83-oFy1n83-oEy1m9k83-ty83-oFy1n83-tyln9l1m83-oEy83nDy1n");
    string_constant_22 = 
	    STATIC_STRING("83nDy1n1m9k83-9y83aFy1m9k83-Aym1n83nDy1o1m9k9m1m9k83-9y83aFy1m9k83-Ay1m9mn1p83nDy1n832ay1m9k83-9y83Ecy1ll9n9o1p83nDy1m832ay836ay");
    string_constant_23 = 
	    STATIC_STRING("2llm9n9o1n83nDy1n836Ey838Ry836Ey1nmln1n83nDy1n836Ey1m9k9p836Ey1nmln1n83nDy1n836Ey1m9k9q836Ey1nmln1o83nDy1m83F2y83-oQy2llm9r1n83n");
    string_constant_24 = 
	    STATIC_STRING("Dy1o83-oNy1m9k831by1m9k83=Yy1m9k83*ly1m83RJyl1n83nDy1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C4y83C-y1m9k83*ly83-oKy2l83LZys1n83nDy1s1");
    string_constant_25 = 
	    STATIC_STRING("m9k83-9y1m9k8312y83aFy1m9k832Sy83aFy1m9k8332y83aFy1m9k83-Ay1o8348ynpr1n83nDy1q1m9k83-9y1m9k8312y83aFy1m9k832Sy83aFy1m9k83-Ay1n83");
    string_constant_26 = 
	    STATIC_STRING("48ynp1n83nDy1o83F2y1m9k83*Iy834Uy83F2y1o83-=uy1m9knlo1n83nDy1p83F2y1m9k83*Iy1m9k9m834Uy83F2y1o83-=sy1m9kolp1m83nDy83F2y1n83-oQy1");
    string_constant_27 = 
	    STATIC_STRING("n1m9k831by1m9k83=Yy1m9k83*ly1m83RJy83hPy1n83-oQy1n1m9k831by1m9k83=Ty1m9k83*ly1m83RLy83hPy1n83-oNy1n1m9k83-9y836Ey1m9k83-Aym1n83-");
    string_constant_28 = 
	    STATIC_STRING("oNy1n1m9k83-9y83aFy1m9k83-Aym1n83-oNy1o1m9k9m1m9k83-9y83aFy1m9k83-Ay1m9mn1n83-oKy1n1m9k83-9y83aFy1m9k83-Ay1lm1n83-oKy1o1m9k83-9y");
    string_constant_29 = 
	    STATIC_STRING("83aFy1m9k83vy83-oLy2lmo1n83-oLy1m83aFy1m9k83-Ay1ll1n83-oLy1n83aFy1m9k83vy83-oLy2lln1n83F2y1s1m9k9s83-Gy83*Zy1m9k83CWy1m9k9s83*my");
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
	    STATIC_STRING("13Ly1m831Py83-Fey1o831Py1n83-Fey1m9k83=Uy831Py1n83=Uyln9l1n83-Fiy1n1m9k83-9y831Py1m9k83-Aym1n83-Fiy1o1m9k9m1m9k83-9y831Py1m9k83-");
    string_constant_33 = 
	    STATIC_STRING("Ay1m9mn1m83-Fey83-tJy1o83-Fey1n83-tJy1m9k83-ty83-Fey1n83-tyln9l1m83-tJy83dTy1n83dTy1n83-Fdy83xQy83-Fdy1nmln1m83dTy830By1n83dTy1n");
    string_constant_34 = 
	    STATIC_STRING("1m9k83-9y831Py1m9k83-Aym1n83dTy1o1m9k9m1m9k83-9y831Py1m9k83-Ay1m9mn1p83dTy1n832ay1m9k83-9y83Ecy1ll9n9o1p83dTy1m832ay836ay2llm9n9");
    string_constant_35 = 
	    STATIC_STRING("o1n83dTy1n83=xy838Ry83=xy1nmln1n83dTy1n83=xy1m9k9p83=xy1nmln1n83dTy1n83=xy1m9k9q83=xy1nmln1o83dTy1m830By83-Fly2llm9r1n83dTy1o83-");
    string_constant_36 = 
	    STATIC_STRING("Fhy1m9k831by1m9k83=Yy1m9k83*ly1m83RJyl1n83dTy1p83-Fhy1m9k831by1m9k83=Yy1m9k831Sy1m9k83*ly1m83iTyl1n83dTy1o83-Fhy1m9k831by1m9k83=");
    string_constant_37 = 
	    STATIC_STRING("Ty1m9k83*ly1m83RLyl1n83dTy1p83-Fhy1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iUyl1n83dTy1s1m9k9s1m9k9t1m9k83-Ty1m9k9s1m9k83C4y83C-y");
    string_constant_38 = 
	    STATIC_STRING("1m9k83*ly83oJy2l83LZys1n83dTy1s1m9k83-9y1m9k8312y831Py1m9k832Sy831Py1m9k8332y831Py1m9k83-Ay1o8348ynpr1o83dTy1q1m9k83-9y1m9k8312y");
    string_constant_39 = 
	    STATIC_STRING("831Py1m9k832Sy831Py1m9k83-Ay1n8348ynp1n9u83=Vy83gFy1m83dTy830By");
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
	    STATIC_STRING("13Ey1n83-Fly1n1m9k831by1m9k83=Yy1m9k83*ly1m83RJy83hPy1n83-Fly1n1m9k831by1m9k83=Ty1m9k83*ly1m83RLy83hPy1n83-Fly1o1m9k831by1m9k83=");
    string_constant_41 = 
	    STATIC_STRING("Yy1m9k831Sy1m9k83*ly1m83iTy83hPy1n83-Fly1o1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83iUy83hPy1n83-Fhy1n1m9k83-9y83=xy1m9k83-Aym1n83");
    string_constant_42 = 
	    STATIC_STRING("-Fhy1n1m9k83-9y831Py1m9k83-Aym1n83-Fhy1o1m9k9l1m9k83-9y831Py1m9k83-Ay1m9ln1n83oJy1n1m9k83-9y831Py1m9k83-Ay1lm1n83oJy1o1m9k83-9y8");
    string_constant_43 = 
	    STATIC_STRING("31Py1m9k83vy83-tQy2lmo1n83-tQy1m831Py1m9k83-Ay1ll1n83-tQy1n831Py1m9k83vy83-tQy2lln1n830By1s1m9k9m83-Gy83*Zy1m9k83CWy1m9k9m83*my1");
    string_constant_44 = 
	    STATIC_STRING("m9k83-Ty830By1n83CVy2lmn1npqs1n830By1u1m9k9m83-Gy83*Zy1m9k83CWy1m9k9m83-Gy1m9k83=my83*my1m9k83-Ty830By1n83CVy2lmn1np1n830=yqsu1m");
    string_constant_45 = 
	    STATIC_STRING("83-Fdy830By1n83-Fdy1n1m9k83-9y831Py1m9k83-Aym1m83APy831Py1m83APy1m9k83Zy1m83-u1y83APy");
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
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
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
	    STATIC_STRING("13=6y1n833*y1n1m9k83=by83-Gy83*Zy1ml2lmn1m838Ry1m9k9l1m838Ry1m9k9m1m838Ry1m9k9n1m838Ry1m9k9o1m83-NLy1m9k9l1m83-NLy1m9k9m1m83-NLy");
    string_constant_48 = 
	    STATIC_STRING("1m9k9n1m83-NLy1m9k9p1m83-NLy1m9k9o1m83-NLy1m9k9q1m83vmy83-Suy1o83vmy1o83-Suy1m9k83-ty1m9k837ey83UTy1n83-tylo9r1m83-Suy83-Sty1o83");
    string_constant_49 = 
	    STATIC_STRING("-Suy1n83-Sty1m9k83=Uy83-Suy1n83=Uyln9r1m83-Sty83vry1n83vry1o833*y1m9k83-A3y1m9k83=Yy1m9k83*ly1m83-A4yl1n83vry1q833*y1m9k83-TVy1m");
    string_constant_50 = 
	    STATIC_STRING("9k83=3y1m9k839ry1m9k83=Yy1m9k83*ly1m83-TWyl1n83vry1n833*y1m9k83*Iy1m9k83-exy1m83-a*yl1n83vry1q833*y1m9k83*Iy1m9k83-exy1m9k83*uy1");
    string_constant_51 = 
	    STATIC_STRING("m9k9s1m9k83oNy1m83-a0yl1n83vry1p833*y1m9k83*Iy1m9k83-exy1m9k83*uy1m9k830Jy1m83-a=yl1n83vry1q833*y1m9k83*Iy1m9k83-l8y1m9k83*uy1m9");
    string_constant_52 = 
	    STATIC_STRING("k9s1m9k83oNy1m83-a4yl1n83vry1o833*y1m9k83-Kfy834Uy833*y1o83-Kgy1m9knlo1n83vry1q833*y1m9k83-Lky1m9k83=3y1m9k83-Key834Uy833*y1o83-");
    string_constant_53 = 
	    STATIC_STRING("Lly1m9kplq1n83vry1n833*y1m9k83*Iy1m9k83GSy1m83-Zsyl1n83vry1n833*y1m9k83*Iy1m9k83-QLy1m83-Zvyl1n83vry1n833*y1m9k83*Iy1m9k83h6y1m8");
    string_constant_54 = 
	    STATIC_STRING("3-Zxyl1n83vry1n833*y1m9k83*Iy1m9k83vGy1m83-Zwyl1n83vry1o833*y1m9k83-cOy1m9k83-aRy1m9k83*ly1m83-cPyl1n83vry1q1m9k83=by1m9k831Ly1m");
    string_constant_55 = 
	    STATIC_STRING("9k83-Ty83-Gy1m9k83*Iy1m9k83-PHy1m83-Zuy1m83=byo1n83vry1r1m9k83=by1m9k831Ly1m9k83-Ty83-Gy83*Zy1m9k83*Iy1m9k83-PHy1m83-Zuy1m83=by2");
    string_constant_56 = 
	    STATIC_STRING("lop1n83vry1p833*y1m9k83-Kfy1m9k83-BYy1m9k83=3y833*y1n83-Vcylp1n83vry1r833*y1m9k83-Lky1m9k83=3y1m9k83-Key1m9k83-BYy1m9k83=3y833*y");
    string_constant_57 = 
	    STATIC_STRING("1n83-Veylr1n83vry1q83-Sry1m9k83*Iy1m9k83-REy1m9k83Igy1m9k83=3y833*y1o83-Vfyl1m9k83-fpyq1n83vry1r83-Sry1m9k83*Iy1m9k83-REy1m9k83I");
    string_constant_58 = 
	    STATIC_STRING("gy1m9k83=3y83-O3y833*y1o83-Vfy1m83=by83=+y1m9kqr1n83vry1r1m9k83=Yy1m9k83=+y1m9k83*Iy1m9k83-REy1m9k83-RJy1m9k832+y833*y1n83-Vgy1m");
    string_constant_59 = 
	    STATIC_STRING("9k83-fpyr1n83vry1s1m9k83=Yy1m9k83=+y1m9k83*Iy1m9k83-REy1m9k83-RJy1m9k832+y83-O3y833*y1n83-Vgy1m9krs1n83vry1s1m9k83=Yy1m9k83=+y83");
    string_constant_60 = 
	    STATIC_STRING("-o1y1m9k83*Iy1m9k83-REy1m9k83Igy1m9k83=3y833*y1o83-RFy1m83=byn1m9k83-fpys1n83vry1t1m9k83=Yy1m9k83=+y83-o1y1m9k83*Iy1m9k83-REy1m9");
    string_constant_61 = 
	    STATIC_STRING("k83Igy1m9k83=3y83-O3y833*y1o83-RFy1m83=byn1m9kst1n83vry1s1m9k83=Yy1m9k83=+y83-o1y1m9k83*Iy1m9k83-REy1m9k83-RJy1m9k832+y833*y1o83");
    string_constant_62 = 
	    STATIC_STRING("-RGy1m9kn1m9k83-fpys1n83vry1t1m9k83=Yy1m9k83=+y83-o1y1m9k83*Iy1m9k83-REy1m9k83-RJy1m9k832+y83-O3y833*y1o83-RGy1m9kn1m9kst1n83vry");
    string_constant_63 = 
	    STATIC_STRING("1t1m9k83=Yy1m9k83=+y83*Zy83-o1y1m9k83*Iy1m9k83-REy1m9k83Igy1m9k83=3y833*y1o83-RFy1m83=by2lon1m9k83-fpyt1n83vry1u1m9k83=Yy1m9k83=");
    string_constant_64 = 
	    STATIC_STRING("+y83*Zy83-o1y1m9k83*Iy1m9k83-REy1m9k83Igy1m9k83=3y83-O3y833*y1o83-RFy1m83=by2lon1m9ktu1n83-Sry1m1m9k83=Yy1m9k83=+y1m83=bym1n83-S");
    string_constant_65 = 
	    STATIC_STRING("ry1n1m9k83=Yy1m9k83=+y83*Zy1m83=by2lmn1n83-o1y1n1m9k83-Ty1m9k83-Gy83BOyn1n83-O3y1m839jy1m9k83-Tyl1n83-O3y1n1m9k83=ay1m9k83dy1m9k");
    string_constant_66 = 
	    STATIC_STRING("83=3y83fDy1n83-O3y1n1m9k83=ay1m9k83py1m9k83-Ty83fEy1n83vry1p833*y1m9k83*Iy1m9k83Igy1m9k83=3y833*y1n83-Z-ylp1n83vry1p833*y1m9k83*");
    string_constant_67 = 
	    STATIC_STRING("Iy1m9k83-RJy1m9k832+y833*y1n83-Z*ylp1m83lxy1m9k9s1m83lxy1m9k83=by1m83-Fmy1m9k9s1m83-D+y1m9k9s1m832ay1m9k83fKy1m832ay1m9k833Oy1m8");
    string_constant_68 = 
	    STATIC_STRING("32ay1m9k833Ty1m832ay1m9k9t1m832ay1m9k83-2y1m832ay83-6y1o83pSy1n836Yy1m9k83-ty83pTy1n83-tyln9r1m83pSy836Yy1o83pTy1n836Yy1m9k83-ty");
    string_constant_69 = 
	    STATIC_STRING("83pTy1n83-tyln9r1m83pTy836Yy1n83pSy1n1m9k83*Xy1m9k83-gvy836Yy1m83-YVyn1o83pSy1n1m9k83*Xy1m9k83-gvy83-J7y1m83-YVyn9u1o83-J7y1n836");
    string_constant_70 = 
	    STATIC_STRING("Yy1m9k83-ty83-J8y1n83-tyln9r1o83-J8y1n836Yy1m9k83-ty83-J8y1n83-tyln9r1m83-J8y836Yy1n83-Ngy1n1m9k83=Fy1m9k83vwy83=xy1on0001n83-Ng");
    string_constant_71 = 
	    STATIC_STRING("y1o1m9k83=Fy1m9k83g2y1m9k831Ay83=xy1o0o001n83-Ngy1r1m9k83=Fy1m9k83vwy83=xy1m9k83=Fy1m9k83g2y1m9k831Ay83=xy1onr001n83-Ngy1r1m9k83");
    string_constant_72 = 
	    STATIC_STRING("=Fy1m9k83g2y1m9k831Ay83=xy1m9k83=Fy1m9k83vwy83=xy1oro001n83-Ngy1m1m9k83-NMy83=xy1o00m01n83-Ngy1o1m9k83-NMy83=xy1m9k83-lIy83*Zy1o");
    string_constant_73 = 
	    STATIC_STRING("00mo1n836Yy1r1m9k83gEy1m9k8319y8330y1m9k831by1m9k83=Ty1m9k831Sy1m9k83*ly1m83-Ndyn1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k831by1m9k83");
    string_constant_74 = 
	    STATIC_STRING("=Ty1m9k83*ly1m83-Neyn1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k838By1m9k9v1m9k83vuy1m83-Neyn1n836Yy1n1m9k83gEy1m9k8319y8330y1r83gEyn00");
    string_constant_75 = 
	    STATIC_STRING("0001n836Yy1o1m9k83gEy1m9k8319y1m9k9v8330y1q83-Nfyo00001n836Yy1p1m9k83gEy1m9k8319y8330y1m9k83*Iy1m9k832Zy1q83-Nfyn00001n836Yy1p1m");
    string_constant_76 = 
	    STATIC_STRING("9k83gEy1m9k8319y8330y1m9k83*Iy1m9k83=Oy1r83gEyn000001n836Yy1p1m9k83gEy1m9k8319y8330y1m9k9l83=xy1r83gEynp00001n836Yy1p1m9k83gEy1m");
    string_constant_77 = 
	    STATIC_STRING("9k8319y8330y1m9k9l83dTy1r83gEynp00001o836Yy1p1m9k83gEy1m9k8319y8330y1m9k83*Iy830Ty1r83gEyn1m9kp00009w1n836Yy1o1m9k83gEy1m9k8319y");
    string_constant_78 = 
	    STATIC_STRING("8330y83-Ngy2n83gEyn0o1n836Yy1p1m9k83gEy1m9k8319y1m9k9v8330y83-Ngy2m83-Nfyop1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k83*Iy1m9k832Zy83-");
    string_constant_79 = 
	    STATIC_STRING("Ngy2m83-Nfynq1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k83*Iy1m9k83=Oy83-Ngy2n83gEyn0q1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k9l83=xy83-Ngy");
    string_constant_80 = 
	    STATIC_STRING("2n83gEynpq1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k9l83dTy83-Ngy2n83gEynpq1o836Yy1q1m9k83gEy1m9k8319y8330y1m9k83*Iy83-2y83-Ngy2n83gEy");
    string_constant_81 = 
	    STATIC_STRING("n1m9kpq9w1n836Yy1n1m9k83-U3y1m9k830Py8330y1n83-U3yn01o836Yy1n1m9k83D8y83-Lfy83-Eny1o83D8ym009x1o836Yy1p1m9k83D8y83-Lfy83-Eny1m9k");
    string_constant_82 = 
	    STATIC_STRING("83=Iy8330y1o83D8ymp09x1o83-9Py1q1m9k83D8y83-Lfy83-Eny1m9k83vy1m9k83-KKy1m9k83-NSy1o83D8ym08k9x1o83-9Py1s1m9k83D8y83-Lfy83-Eny1m9");
    string_constant_83 = 
	    STATIC_STRING("k83=Iy8330y1m9k83vy1m9k83-KKy1m9k83-NSy1o83D8ymp8k9x1n83-9Py1q1m9k83-U3y1m9k830Py8330y1m9k83vy1m9k83-KKy1m9k83-NSy1n83-U3yn8k1n8");
    string_constant_84 = 
	    STATIC_STRING("36Yy1r1m9k83-Wwy1m9k83=Fy83-Uy1m9k8312y1m9k83fXy1m9k83poy1m9k83h6y1m83-Wwyn1n836Yy1p1m9k83-Wwy1m9k8312y1m9k83fXy1m9k83poy1m9k83h");
    string_constant_85 = 
	    STATIC_STRING("6y1l83-Wwy1n836Yy1o1m9k83-=Zy8330y1m9k8319y83-day1n83-=Zymo1n836Yy1p1m9k83-=Zy8330y83-Z2y1m9k8319y83-day2n83-=Zympn1n836Yy1p1m9k");
    string_constant_86 = 
	    STATIC_STRING("83-=Zy1m9k9s1m9k83-gry1m9k8319y83-day1n83-=Zy1m9s83-gryp1n836Yy1m1m9k83-9Ay83-day1n83-=Zy1m9s83-grym1n836Yy1n1m9k83-9Ay83-Z1y83-");
    string_constant_87 = 
	    STATIC_STRING("day2n83-=Zy1m9s83-grynm1n836Yy1q1m9k83-=Zy1m9k9s1m9k83-gry83-Z2y1m9k8319y83-day2n83-=Zy1m9s83-gryqo1m83-Z2y83-Z6y1o83-Z2y1m83-Z6");
    string_constant_88 = 
	    STATIC_STRING("y83-Z3y2llm9y1m83-Z2y83-Z3y1m83-Z3y83-Z5y1m83-Z3y83-Z1y1o83-Z3y1m83-Z5y83-Z1y1mlm9z1o83-Z1y1o1m9k83=Iy1m9k9s1m9k837Fy83-oy1l1m83");
    string_constant_89 = 
	    STATIC_STRING("-Rryo93Cy1n83-Z6y1m1m9k830Py830By1l1m830Pym1n83-Z5y1m83-Kky830By1l1mlm1m83-Kky1m9k83HCy1m83-Kky1m9k83GOy1n836Yy1o1m9k93Dy8330y1m");
    string_constant_90 = 
	    STATIC_STRING("9k83=3y83=xy1n93Dymo1n836Yy1p1m9k83-JAy1m9k9s1m9k83b9y1m9k83-Ty8330y1mlp1n836Yy1p1m9k83-QKy1m9k9s1m9k83b9y1m9k83-Ty8330y1mlp1n83");
    string_constant_91 = 
	    STATIC_STRING("6Yy1m1m9k83n2y8330y1m83-nQym1n836Yy1n1m9k83n2y8330y83-YYy1n83-nQymn1n836Yy1o1m9k83n2y8330y83-YYy83-mJy1o83-nQymno1o836Yy1r1m9k83");
    string_constant_92 = 
	    STATIC_STRING("n2y8330y83-YYy83-mJy1m9k83lky1m9k83*ry1m9k83-bNy1o83-nQymno93Ey1n836Yy1o1m9k83n2y8330y83-YYy83-iJy2n83-nQymno1o836Yy1r1m9k83n2y8");
    string_constant_93 = 
	    STATIC_STRING("330y83-YYy83-iJy1m9k83lky1m9k83*ry1m9k83-bNy2n83-nQymno93Ey1n836Yy1p1m9k83n2y8330y83-YYy83-mJy83-iJy2o83-nQymnop1o836Yy1s1m9k83n");
    string_constant_94 = 
	    STATIC_STRING("2y8330y83-YYy83-mJy83-iJy1m9k83lky1m9k83*ry1m9k83-bNy2o83-nQymnop93Ey1n836Yy1n1m9k83n2y8330y83-mJy1n83-nQymn1o836Yy1q1m9k83n2y83");
    string_constant_95 = 
	    STATIC_STRING("30y83-mJy1m9k83lky1m9k83*ry1m9k83-bNy1n83-nQymn93Ey1n836Yy1o1m9k83n2y8330y83-mJy83-iJy2n83-nQymno1o836Yy1r1m9k83n2y8330y83-mJy83");
    string_constant_96 = 
	    STATIC_STRING("-iJy1m9k83lky1m9k83*ry1m9k83-bNy2n83-nQymno93Ey1n836Yy1n1m9k83n2y8330y83-iJy2m83-nQymn1o836Yy1q1m9k83n2y8330y83-iJy1m9k83lky1m9k");
    string_constant_97 = 
	    STATIC_STRING("83*ry1m9k83-bNy2m83-nQymn93Ey1m836Yy1m1m9k83-XIy8330y1m836Yy1n1m9k83-XIy8330y83-YYy1n836Yy1q1m9k83gEy1m9k8319y8330y1m9k83*Iy834U");
    string_constant_98 = 
	    STATIC_STRING("y8330y1o83-JHypnq1n836Yy1r1m9k83gEy1m9k8319y8330y1m9k83*Iy1m9k9v834Uy8330y1o83-kvyqnr1n836Yy1r1m9k83gEy1m9k8319y8330y1m9k83*Iy1m");
    string_constant_99 = 
	    STATIC_STRING("9k83-g6y834Uy8330y1p83-JHyqnr83-g6y1n836Yy1m1m9k93Fy8330y1mlm1n836Yy1n1m9k83-nsy1m9k838Cy1m9k830Jy1l83n7y1n836Yy1m1m9k834Wy1m9k8");
    string_constant_100 = 
	    STATIC_STRING("3-1my1l83-l6y1n836Yy1m1m9k831iy1m9k83-1my1l83-hcy1m836Yy1m1m9k93Gy8330y1n83-YYy1m1m9k830Py83-vOy1m83*Xym1m83-vOy8330y1n83-iJy83-");
    string_constant_101 = 
	    STATIC_STRING("mUy1ll1n83-iJy1m83-vky83-mUy1mlm1n83-vky1s1m9k83=Fy1m9k83wYy1m9k835xy1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1m83-vjy1mpr1n83-mUy1t1");
    string_constant_102 = 
	    STATIC_STRING("m9k83=Gy1m9k83-9y83=xy1m9k83vy83=xy1m9k83-Ay1m9k83*Xy1m9k9s1m9k83-mSy1m83-mTy1n83=Gynp1n83-mJy83-mKy1m83-mAyl1n83-mKy1n1m9k83=Gy");
    string_constant_103 = 
	    STATIC_STRING("83-mCy1m9k83-mAym1m83-mCy1m9k83-ghy1m83-mCy1m9k83-Wvy1m83-mCy1m9k83-rGy1m83-mCy1m9k83-Uly1n83-mKy1n1m9k83-CMy1m9k83*uy83-mBy2l83");
    string_constant_104 = 
	    STATIC_STRING("-Ulyn1n83-mKy1r1m9k83-CMy1m9k83*uy1m9k83-aRy1m9k831Sy1m9k83-mAy1m9k83-rjy83-mBy2l831Syr1n83-mBy83=xy1ll1n83-mBy1p1m9k83-9y83=xy1");
    string_constant_105 = 
	    STATIC_STRING("m9k83vy83=xy1m9k83-Ay1mmo1n83-mUy1q83-cHy1m9k9s83-kAy1m9k83-Ty1m9k9s1m9k83-mSy1n83-mTyln1m83-kAy1m9k83-dy1m83-kAy1m83-Lny1m9k83-");
    string_constant_106 = 
	    STATIC_STRING("dy1n83-kAy1m83-Ofy1m9k83-Oeyl1m83-X+y1m9k83*hy1m83-X+y1m9k83-cy1m83-rwy1m9k83hy1m83-rwy1m9k83gy1m83-Lny83-X+y1m83-Lny83-rwy1m83-");
    string_constant_107 = 
	    STATIC_STRING("Ofy1m83-rwy83-X+y1m83-cHy1m9k83=Gy1m83-cHy83-gVy1n83-gVy1m83-gWy83-XXy1mml1n83-gVy1m83-gWy83-umy1mml1n83-gVy1p83-gWy83-XXy1m9k83");
    string_constant_108 = 
	    STATIC_STRING("-ty83-gWy83-umy1omlpo1n83-gWy1m83=xy1m9k83Fgyl1m83-umy1m9k83GOy1m83-umy1m9k83HCy1n83-XXy1o1m9k83=3y1m9k9s83-X+y1m9k83-Tyn1n83-vk");
    string_constant_109 = 
	    STATIC_STRING("y1n1m9k83=Fy1m9k83-aRy83-kAy1m83-vjyn1m83-day83-Uy1o83-day1m83Try83-gly1n83-tylm9r1o83-gly1m83-dVy83ZFy1n83-tylm9r1o83-gly1m83-d");
    string_constant_110 = 
	    STATIC_STRING("Vy83-dby1n83-tylm9r1o83-dby1m83VXy83-gly1n83-tylm9r1m83-dVy83=xy1n83-dVy1p83=xy1m9k83*5y83=Zy1m9k831Ay1m9k83A*y1n838Pyl1m9k832ny");
    string_constant_111 = 
	    STATIC_STRING("1n83-dVy1o83=xy1m9k83*5y83=Zy1m9k83-oy1n838Pyl1m9k832Ky1o83-dVy1n83=xy1m9k83*5y83J9y1n83J9yln93Hy1o83-mqy1n83-Uy1m9k83vy83-mqy1n");
    string_constant_112 = 
	    STATIC_STRING("83-tyln9r1m83J9y83-6y1m83-R1y83-6y1n83-R1y1m1m9k9s83-6ym1m83-Lfy83mcy1n83-Lfy1n83mcy1m9k83-ty83mcy1n83-tyln1o83-Lfy1n83mcy1m9k83");
    string_constant_113 = 
	    STATIC_STRING("vy83-Lgy1n83-tyln9r1n83-Lgy1o83mcy1m9k83vy1m9k83-ty83mcy1n83-tylo1o83-Lgy1n83mcy1m9k83vy83-Lgy1n83-tyln9r1m83mcy83-6y1m839jy83-6");
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
	    STATIC_STRING("1m1n83vry1p833*y1m9k831by83=Zy83-6y1m9k83vly1o83-Vhyl1m9ko1m83=by83Ry1n83vry1q833*y1m9k831by83=Zy83-6y1m9k83vly83*Zy1o83-Vhyl1m9");
    string_constant_1 = STATIC_STRING("ko1m83=by2l83Ryq");
    SET_SYMBOL_FUNCTION(Qadd_generic_rule_grammar,
	    STATIC_FUNCTION(add_generic_rule_grammar,NIL,FALSE,0,0));
    Qextend_action_grammar = STATIC_SYMBOL("EXTEND-ACTION-GRAMMAR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qextend_action_grammar,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_2 = 
	    STATIC_STRING("1m1n836Yy1m1m9k836Gy1m9k83-1my1l83-pFy1n836Yy1m1m9k83Z8y1m9k83-1my1l83-ldy");
    SET_SYMBOL_FUNCTION(Qextend_action_grammar,
	    STATIC_FUNCTION(extend_action_grammar,NIL,FALSE,0,0));
}
