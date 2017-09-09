/* cmpl2.c
 * Input file:  compile2.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cmpl2.h"


static Object Qcompile1_forward_reference_for_designations;  /* compile1-forward-reference-for-designations */

static Object Qg2_defstruct_structure_name_expression_for_compilation_g2_struct;  /* g2-defstruct-structure-name::expression-for-compilation-g2-struct */

/* COMPILE1-EXPRESSION-TOP */
Object compile1_expression_top(antecedent_expression,
	    consequent_expression_qm,left_side_of_formula_qm,focus_names,
	    continuation_qm)
    Object antecedent_expression, consequent_expression_qm;
    Object left_side_of_formula_qm, focus_names, continuation_qm;
{
    Object wider_focus_names_to_try_qm, chaining_category_qm;
    Object focus_local_name_qm, first_time_qm, list_of_known_names;
    Object forward_reference_compiled_left_side_of_formula_qm;
    Object compiling_antecedent_p;
    Object forward_reference_compiled_antecedent_expression;
    Object forward_reference_compiled_consequent_expression;
    Object combined_inverse_and_antecedent_reference_tree;
    Object combined_left_side_and_right_side_tree;
    Object combined_explicit_iteration_and_antecedent_reference_tree;
    Object inverse_references_for_designations, focus_local_name_entry;
    Object next_focus_local_name_entry_continuation_index_qm;
    Object next_focus_local_name_entry, temp, return_qm;
    Object root_inverse_reference_structure;
    Object wider_focus_reference_structure_qm;
    char need_to_compile_with_focus_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(141,0);
    wider_focus_names_to_try_qm = Nil;
    chaining_category_qm = Nil;
    focus_local_name_qm = Nil;
    first_time_qm = T;
  next_loop:
    List_of_known_names = Nil;
    Names_used_for_more_than_one_item = Nil;
    Focus_local_names_for_focus_role_name = Nil;
    Local_name_errors = Nil;
    Top_level_reference_tree = Nil;
    need_to_compile_with_focus_qm =  !(Compiling_expression_p &&  
	    !TRUEP(left_side_of_formula_qm));
    list_of_known_names =  !need_to_compile_with_focus_qm ? 
	    copy_list_using_phrase_conses(focus_names) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(List_of_known_names,Qlist_of_known_names,list_of_known_names,
	    1);
      if (Compiling_rule_p)
	  compile1_forward_explicit_iteration_designations();
      forward_reference_compiled_left_side_of_formula_qm = 
	      left_side_of_formula_qm ? 
	      compile1_forward_reference_for_designations(left_side_of_formula_qm) 
	      : Nil;
      compiling_antecedent_p = Compiling_rule_p;
      PUSH_SPECIAL_WITH_SYMBOL(Compiling_antecedent_p,Qcompiling_antecedent_p,compiling_antecedent_p,
	      0);
	forward_reference_compiled_antecedent_expression = 
		compile1_forward_reference_for_designations(antecedent_expression);
      POP_SPECIAL();
      forward_reference_compiled_consequent_expression = 
	      consequent_expression_qm ? 
	      compile_consequent(consequent_expression_qm,
	      Qcompile1_forward_reference_for_designations) : Nil;
      combined_inverse_and_antecedent_reference_tree = Nil;
      combined_left_side_and_right_side_tree = Nil;
      combined_explicit_iteration_and_antecedent_reference_tree = Nil;
      inverse_references_for_designations = Nil;
      if ( !TRUEP(CDR(focus_names)) && CAR(focus_names) && first_time_qm) {
	  if (Compiling_rule_p) {
	      if (continuation_qm) {
		  focus_local_name_entry = nth(continuation_qm,
			  Focus_local_names_for_focus_role_name);
		  next_focus_local_name_entry_continuation_index_qm = 
			  FIXNUM_ADD1(continuation_qm);
		  next_focus_local_name_entry = 
			  nth(next_focus_local_name_entry_continuation_index_qm,
			  Focus_local_names_for_focus_role_name);
		  focus_names = phrase_cons(CAR(focus_local_name_entry),Nil);
		  chaining_category_qm = CDR(focus_local_name_entry);
		  continuation_qm = next_focus_local_name_entry ? 
			  next_focus_local_name_entry_continuation_index_qm 
			  : Nil;
	      }
	      else {
		  focus_names = 
			  phrase_cons(CAAR(Focus_local_names_for_focus_role_name),
			  Nil);
		  chaining_category_qm = 
			  CDAR(Focus_local_names_for_focus_role_name);
		  continuation_qm = 
			  SECOND(Focus_local_names_for_focus_role_name) ? 
			  FIX((SI_Long)1L) : Nil;
	      }
	      focus_local_name_qm = CAR(focus_names);
	  }
	  else if (left_side_of_formula_qm)
	      focus_names = 
		      phrase_cons(CAAR(Focus_local_names_for_focus_role_name),
		      Nil);
      }
      if (need_to_compile_with_focus_qm && CAR(focus_names)) {
	  temp = wider_focus_names_to_try_qm;
	  if (temp);
	  else
	      temp = focus_names;
	  inverse_references_for_designations = 
		  compile1_designations_for_focus(forward_reference_compiled_left_side_of_formula_qm,
		  forward_reference_compiled_antecedent_expression,
		  forward_reference_compiled_consequent_expression,temp);
      }
      combine_references_for_expression(forward_reference_compiled_antecedent_expression);
      if ( 
	      !(SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
	      && 
	      EQ(ISVREF(forward_reference_compiled_antecedent_expression,
	      (SI_Long)0L),
	      Qg2_defstruct_structure_name_expression_for_compilation_g2_struct))) 
		  {
	  if (Designations_from_explicit_iteration_forms)
	      combined_explicit_iteration_and_antecedent_reference_tree = 
		      combine_reference_paths_for_explicit_iteration_designations();
	  if (inverse_references_for_designations)
	      combined_left_side_and_right_side_tree = 
		      combine_inverse_reference_paths_with_local_reference_paths(inverse_references_for_designations,
		      combined_left_side_and_right_side_tree);
	  combined_inverse_and_antecedent_reference_tree = 
		  combined_explicit_iteration_and_antecedent_reference_tree;
      }
      if (SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
	      && 
	      EQ(ISVREF(forward_reference_compiled_antecedent_expression,
	      (SI_Long)0L),
	      Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		  {
	  if (Designations_from_explicit_iteration_forms) {
	      temp = 
		      combine_reference_paths_for_explicit_iteration_designations();
	      combined_explicit_iteration_and_antecedent_reference_tree = 
		      combine_explicit_iteration_and_antecedent_reference_trees(temp,
		      ISVREF(forward_reference_compiled_antecedent_expression,
		      (SI_Long)3L));
	  }
	  else
	      combined_explicit_iteration_and_antecedent_reference_tree = 
		      ISVREF(forward_reference_compiled_antecedent_expression,
		      (SI_Long)3L);
	  if (forward_reference_compiled_left_side_of_formula_qm) {
	      combined_left_side_and_right_side_tree = 
		      combine_left_side_tree_with_right_side_tree(ISVREF(forward_reference_compiled_left_side_of_formula_qm,
		      (SI_Long)3L),
		      ISVREF(forward_reference_compiled_antecedent_expression,
		      (SI_Long)3L));
	      if (ISVREF(forward_reference_compiled_antecedent_expression,
		      (SI_Long)4L))
		  combined_left_side_and_right_side_tree = 
			  combine_inverse_reference_paths_with_local_reference_paths(ISVREF(forward_reference_compiled_antecedent_expression,
			  (SI_Long)4L),combined_left_side_and_right_side_tree);
	      temp = 
		      ISVREF(forward_reference_compiled_left_side_of_formula_qm,
		      (SI_Long)3L);
	      Wrapper_references_for_left_side_of_formula_qm = CAR(temp);
	  }
	  if (inverse_references_for_designations)
	      combined_inverse_and_antecedent_reference_tree = 
		      combine_inverse_reference_paths_with_local_reference_paths(inverse_references_for_designations,
		      combined_explicit_iteration_and_antecedent_reference_tree);
	  else
	      combined_inverse_and_antecedent_reference_tree = 
		      combined_explicit_iteration_and_antecedent_reference_tree;
      }
      if (consequent_expression_qm)
	  combine_references_for_actions(forward_reference_compiled_consequent_expression);
      if (Compiling_rule_p)
	  Top_level_reference_tree = 
		  combine_references_for_antecedent_and_consequent(combined_inverse_and_antecedent_reference_tree,
		  forward_reference_compiled_antecedent_expression,
		  forward_reference_compiled_consequent_expression);
      else {
	  temp = combined_left_side_and_right_side_tree;
	  if (temp);
	  else
	      temp = 
		      SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
		      && 
		      EQ(ISVREF(forward_reference_compiled_antecedent_expression,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
		      ? 
		      combined_explicit_iteration_and_antecedent_reference_tree 
		      : Nil;
	  Top_level_reference_tree = temp;
      }
      if (first_time_qm && Compiling_rule_p)
	  Pattern_checking_inverse_references = 
		  CAR(inverse_references_for_designations);
      return_qm =  !TRUEP(Compiling_rule_p) ? T : Nil;
      if (return_qm);
      else
	  return_qm =  !TRUEP(CAR(focus_names)) ? T : Nil;
      if (return_qm);
      else
	  return_qm = first_time_qm ? 
		  fatal_focus_error_qm(forward_reference_compiled_antecedent_expression,
		  forward_reference_compiled_consequent_expression) : Nil;
      if (return_qm);
      else if (too_narrow_focus_qm(forward_reference_compiled_antecedent_expression,
	      forward_reference_compiled_consequent_expression,
	      inverse_references_for_designations)) {
	  temp = ISVREF(forward_reference_compiled_antecedent_expression,
		  (SI_Long)4L);
	  root_inverse_reference_structure = CAR(temp);
	  temp = ISVREF(root_inverse_reference_structure,(SI_Long)5L);
	  wider_focus_reference_structure_qm = CAR(temp);
	  if (wider_focus_reference_structure_qm &&  
		  !TRUEP(inverse_reference_structure_is_global_end_qm(wider_focus_reference_structure_qm))) 
		      {
	      wider_focus_names_to_try_qm = 
		      phrase_cons(ISVREF(wider_focus_reference_structure_qm,
		      (SI_Long)1L),Nil);
	      return_qm = Nil;
	  }
	  else {
	      Focus_too_narrow_qm = T;
	      return_qm = Focus_too_narrow_qm;
	  }
      }
      else
	  return_qm = T;
      if (return_qm) {
	  result = VALUES_5(forward_reference_compiled_antecedent_expression,
		  forward_reference_compiled_consequent_expression,
		  chaining_category_qm,focus_local_name_qm,continuation_qm);
	  POP_SPECIAL();
	  goto end_1;
      }
    POP_SPECIAL();
    first_time_qm = Nil;
    goto next_loop;
  end_loop:
    result = VALUES_1(Qnil);
  end_1:
    return result;
}

/* FATAL-FOCUS-ERROR? */
Object fatal_focus_error_qm(forward_reference_compiled_antecedent_expression,
	    forward_reference_compiled_consequent_expression)
    Object forward_reference_compiled_antecedent_expression;
    Object forward_reference_compiled_consequent_expression;
{
    x_note_fn_call(141,1);
    return VALUES_1(Fatal_focus_error_info_qm);
}

/* TOO-NARROW-FOCUS? */
Object too_narrow_focus_qm(forward_reference_compiled_antecedent_expression,
	    forward_reference_compiled_consequent_expression,
	    inverse_references_for_designations)
    Object forward_reference_compiled_antecedent_expression;
    Object forward_reference_compiled_consequent_expression;
    Object inverse_references_for_designations;
{
    Object temp;

    x_note_fn_call(141,2);
    temp = rule_focus_inside_rule_body_qm();
    if (temp)
	return VALUES_1(temp);
    else {
	temp = 
		rule_focus_inside_every_quantifier_qm(CAR(inverse_references_for_designations));
	if (temp)
	    return VALUES_1(temp);
	else
	    return rule_focus_inside_illegal_expression_qm(forward_reference_compiled_antecedent_expression);
    }
}

static Object Qg2_defstruct_structure_name_reference_structure_g2_struct;  /* g2-defstruct-structure-name::reference-structure-g2-struct */

/* RULE-FOCUS-INSIDE-RULE-BODY? */
Object rule_focus_inside_rule_body_qm()
{
    Object focus_reference, temp, next_inverse_reference_qm;

    x_note_fn_call(141,3);
    focus_reference = CAR(Top_level_reference_tree);
    if (SIMPLE_VECTOR_P(focus_reference) && EQ(ISVREF(focus_reference,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_reference_structure_g2_struct)) {
	temp = ISVREF(focus_reference,(SI_Long)5L);
	next_inverse_reference_qm = CAR(temp);
    }
    else
	next_inverse_reference_qm = Nil;
    if (next_inverse_reference_qm && EQ(ISVREF(next_inverse_reference_qm,
	    (SI_Long)7L),Qthe) &&  
	    !TRUEP(focus_reference_provides_binding_for_iteration_qm(next_inverse_reference_qm))) 
		{
	Number_of_no_binds = FIXNUM_ADD1(Number_of_no_binds);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qevery_inverse;      /* every-inverse */

/* FOCUS-REFERENCE-PROVIDES-BINDING-FOR-ITERATION? */
Object focus_reference_provides_binding_for_iteration_qm(reference_structure)
    Object reference_structure;
{
    Object needing_reference_structure, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(141,4);
    needing_reference_structure = Nil;
    ab_loop_list_ = ISVREF(reference_structure,(SI_Long)5L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    needing_reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ =  !EQ(ISVREF(needing_reference_structure,(SI_Long)6L),
	    Qevery_inverse) ? 
	    reference_tree_has_iteration_qm(needing_reference_structure) : 
	    Qnil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RULE-FOCUS-INSIDE-EVERY-QUANTIFIER? */
Object rule_focus_inside_every_quantifier_qm(root_inverse_reference_structure)
    Object root_inverse_reference_structure;
{
    Object reference_structure, next_reference_structure, ab_loop_it_, temp;

    x_note_fn_call(141,5);
    reference_structure = root_inverse_reference_structure;
    next_reference_structure = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(reference_structure))
	goto end_loop;
    temp = ISVREF(reference_structure,(SI_Long)5L);
    next_reference_structure = CAR(temp);
    ab_loop_it_ = next_reference_structure ? 
	    (EQ(ISVREF(next_reference_structure,(SI_Long)7L),Qevery) ? T : 
	    Nil) : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    reference_structure = next_reference_structure;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* RULE-FOCUS-INSIDE-ILLEGAL-EXPRESSION? */
Object rule_focus_inside_illegal_expression_qm(expression)
    Object expression;
{
    Object compiled_specific_expression_to_investigate_qm, designation;
    Object ab_loop_list_, root_reference_structure_qm;
    Object providing_reference_structure_qm, ab_loop_it_, temp, sub_expression;

    x_note_fn_call(141,6);
    compiled_specific_expression_to_investigate_qm = 
	    SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? ISVREF(expression,(SI_Long)1L) : Nil;
    if (compiled_specific_expression_to_investigate_qm && 
	    CONSP(compiled_specific_expression_to_investigate_qm)) {
	if (operator_to_check_for_illegal_focus_p(CAR(compiled_specific_expression_to_investigate_qm))) 
		    {
	    designation = Nil;
	    ab_loop_list_ = ISVREF(expression,(SI_Long)2L);
	    root_reference_structure_qm = Nil;
	    providing_reference_structure_qm = Nil;
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    designation = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = ISVREF(designation,(SI_Long)3L);
	    root_reference_structure_qm = CAR(temp);
	    providing_reference_structure_qm = root_reference_structure_qm 
		    ? ISVREF(root_reference_structure_qm,(SI_Long)4L) : Nil;
	    ab_loop_it_ = providing_reference_structure_qm ? ( 
		    !EQ(ISVREF(providing_reference_structure_qm,
		    (SI_Long)1L),Needed_domain) ? T : Nil) : Qnil;
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else {
	    sub_expression = Nil;
	    ab_loop_list_ = 
		    CDR(compiled_specific_expression_to_investigate_qm);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    sub_expression = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    rule_focus_inside_illegal_expression_qm(sub_expression);
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* OPERATOR-TO-CHECK-FOR-ILLEGAL-FOCUS-P */
Object operator_to_check_for_illegal_focus_p(operator_1)
    Object operator_1;
{
    Object temp;

    x_note_fn_call(141,7);
    temp = EQ(operator_1,Qnot) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else
	return quantifier_or_aggregator_p(operator_1);
}

/* COMPILE1-FORWARD-EXPLICIT-ITERATION-DESIGNATIONS */
Object compile1_forward_explicit_iteration_designations()
{
    Object forward_compiled_designations, uncompiled_designation;
    Object ab_loop_list_, compiled_designation;

    x_note_fn_call(141,8);
    forward_compiled_designations = Nil;
    uncompiled_designation = Nil;
    ab_loop_list_ = Source_designations_from_explicit_iteration_forms;
    compiled_designation = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    uncompiled_designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    compiled_designation = compile1_designation(uncompiled_designation);
    forward_compiled_designations = nconc2(forward_compiled_designations,
	    phrase_cons(compiled_designation,Nil));
    goto next_loop;
  end_loop:
    Designations_from_explicit_iteration_forms = forward_compiled_designations;
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

static Object Qcall_assignment_action;  /* call-assignment-action */

static Object Qab_structure;       /* structure */

/* COMPILE1-FORWARD-REFERENCE-FOR-DESIGNATIONS */
Object compile1_forward_reference_for_designations(expression)
    Object expression;
{
    Object operator_1, operator_1_1;

    x_note_fn_call(141,9);
    if (phrase_number_p(expression))
	return VALUES_1(expression);
    else if (SYMBOLP(expression))
	return compile1_designation(expression);
    else if (text_string_p(expression))
	return copy_for_phrase(expression);
    else if (CONSP(expression) && EQ(M_CDR(expression),Phrase_sequence_marker))
	return VALUES_1(expression);
    else if (CONSP(expression) && EQ(M_CDR(expression),
	    Phrase_structure_marker))
	return VALUES_1(expression);
    else if (CONSP(expression)) {
	operator_1 = CAR(expression);
	operator_1_1 = CDR(expression);
	if (EQ(operator_1,Qquote))
	    return VALUES_1(expression);
	else if (phrase_number_p(operator_1))
	    return VALUES_1(expression);
	else if (designation_operator_or_giver_of_value_p(operator_1))
	    return compile1_designation(expression);
	else if (quantifier_or_aggregator_p(operator_1))
	    return compile1_quantifier_or_aggregator(expression);
	else if (memq_function(operator_1,list_constant))
	    return compile1_create_action(expression);
	else if (EQ(operator_1,Qcall_assignment_action))
	    return compile1_call_assignment_action(expression);
	else if (EQ(operator_1_1,Qsequence))
	    return VALUES_1(expression);
	else if (EQ(operator_1_1,Qab_structure))
	    return VALUES_1(expression);
	else
	    return compile1_expression_according_to_template(expression);
    }
    else
	return VALUES_1(Qnil);
}

static Object list_constant_1;     /* # */

/* COMPILE1-EXPRESSION-ACCORDING-TO-TEMPLATE */
Object compile1_expression_according_to_template(expression)
    Object expression;
{
    Object expression_for_compilation, operator_1, template_qm, temp;
    Object svref_new_value;

    x_note_fn_call(141,10);
    expression_for_compilation = 
	    make_compilation_reclaimable_expression_for_compilation();
    operator_1 = CAR(expression);
    template_qm = lookup_function_template(operator_1);
    if (template_qm);
    else
	template_qm = lookup_action_template(operator_1);
    temp = operator_1 ? operator_1 :  !(template_qm && 
	    memq_function(template_qm,list_constant_1)) ? Nil_indicator : Nil;
    svref_new_value = phrase_cons(temp,
	    compile1_sub_expressions_according_to_template(expression,
	    template_qm,expression_for_compilation));
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(expression_for_compilation);
}

static Object Qexpression;         /* expression */

static Object Qother;              /* other */

static Object Qexpression_list;    /* expression-list */

static Object Qdesignation_list;   /* designation-list */

static Object Qcolor_changes;      /* color-changes */

static Object Qcreate_connection_spec;  /* create-connection-spec */

static Object Qshow_or_hide_argument_list;  /* show-or-hide-argument-list */

/* COMPILE1-SUB-EXPRESSIONS-ACCORDING-TO-TEMPLATE */
Object compile1_sub_expressions_according_to_template(expression,
	    template_qm,expression_for_compilation)
    Object expression, template_qm, expression_for_compilation;
{
    Object rest_of_template, template_symbol, compiled_sub_expression;
    Object rest_of_sub_expressions, sub_expression, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(141,11);
    rest_of_template = CDR(template_qm);
    template_symbol = template_qm ? CAR(rest_of_template) : Qexpression;
    compiled_sub_expression = Nil;
    rest_of_sub_expressions = CDR(expression);
    sub_expression = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    sub_expression = CAR(rest_of_sub_expressions);
    if ( !TRUEP(rest_of_sub_expressions))
	goto end_loop;
    if (EQ(template_symbol,Qother))
	compiled_sub_expression =  !TRUEP(sub_expression) ? Nil_indicator :
		 sub_expression;
    else if (EQ(template_symbol,Qexpression_list) || EQ(template_symbol,
	    Qdesignation_list))
	compiled_sub_expression = 
		compile1_forward_reference_for_designations(phrase_cons(Expression_list_indicator,
		sub_expression));
    else if (EQ(template_symbol,Qcolor_changes)) {
	temp = compile1_color_changes(rest_of_sub_expressions);
	rest_of_sub_expressions = Nil;
	compiled_sub_expression = temp;
    }
    else if (EQ(template_symbol,Qcreate_connection_spec))
	compiled_sub_expression = 
		compile1_create_connection_spec(sub_expression);
    else if (EQ(template_symbol,Qshow_or_hide_argument_list))
	compiled_sub_expression = 
		compile1_show_or_hide_argument(sub_expression);
    else
	compiled_sub_expression =  !TRUEP(sub_expression) ? Nil_indicator :
		 compile1_forward_reference_for_designations(sub_expression);
    nconc_designations_from_sub_expression(compiled_sub_expression,
	    expression_for_compilation);
    if (template_qm) {
	temp = CDR(rest_of_template);
	if (SYMBOLP(temp))
	    template_symbol = CDR(rest_of_template);
	else {
	    rest_of_template = CDR(rest_of_template);
	    template_symbol = CAR(rest_of_template);
	}
    }
    rest_of_sub_expressions = CDR(rest_of_sub_expressions);
    ab_loopvar__2 = phrase_cons(compiled_sub_expression,Nil);
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

/* COMPILE1-COLOR-CHANGES */
Object compile1_color_changes(color_changes)
    Object color_changes;
{
    Object region_expression, color_expression, ab_loop_list_;
    Object modified_color_changes, ab_loopvar_, ab_loopvar__1, ab_loop_desetq_;

    x_note_fn_call(141,12);
    region_expression = Nil;
    color_expression = Nil;
    ab_loop_list_ = color_changes;
    modified_color_changes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    region_expression = CAR(ab_loop_desetq_);
    color_expression = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__1 = phrase_cons(phrase_list_3(Color_change_indicator,
	    region_expression,color_expression),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	modified_color_changes = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    return compile1_forward_reference_for_designations(phrase_cons(Color_changes_indicator,
	    modified_color_changes));
    return VALUES_1(Qnil);
}

static Object Qin;                 /* in */

/* COMPILE1-SHOW-OR-HIDE-ARGUMENT */
Object compile1_show_or_hide_argument(expression)
    Object expression;
{
    Object operator_1;

    x_note_fn_call(141,13);
    operator_1 = CAR(expression);
    if (EQ(operator_1,Qin))
	return compile1_forward_reference_for_designations(expression);
    else
	return VALUES_1(expression);
}

/* SUBSTITUTE-NIL-INDICATOR */
Object substitute_nil_indicator(clause)
    Object clause;
{
    Object tail, car_new_value;

    x_note_fn_call(141,14);
    if (clause && LISTP(clause)) {
	tail = clause;
      next_loop:
	if ( !TRUEP(tail))
	    goto end_loop;
	if ( !TRUEP(CAR(tail))) {
	    car_new_value = Nil_indicator;
	    M_CAR(tail) = car_new_value;
	}
	tail = M_CDR(tail);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

static Object list_constant_2;     /* # */

static Object Qconnected_to;       /* connected-to */

/* COMPILE1-CREATE-CONNECTION-SPEC */
Object compile1_create_connection_spec(connection_spec)
    Object connection_spec;
{
    Object new_connection_spec, gensymed_symbol, creation_specifier;
    Object gensymed_symbol_1, end_position_specifier, rest_of_clauses;
    Object vertices_qm;

    x_note_fn_call(141,15);
    new_connection_spec = copy_tree_using_phrase_conses(connection_spec);
    if (new_connection_spec && memq_function(FIRST(new_connection_spec),
	    list_constant_2)) {
	gensymed_symbol = new_connection_spec;
	creation_specifier = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	end_position_specifier = CAR(gensymed_symbol_1);
	rest_of_clauses = gensymed_symbol;
	substitute_nil_indicator(end_position_specifier);
	if (EQ(creation_specifier,Qconnected_to))
	    substitute_nil_indicator(FIRST(rest_of_clauses));
	else {
	    gensymed_symbol = rest_of_clauses;
	    gensymed_symbol_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    end_position_specifier = CAR(gensymed_symbol_1);
	    vertices_qm = gensymed_symbol;
	    substitute_nil_indicator(end_position_specifier);
	    substitute_nil_indicator(FIRST(vertices_qm));
	}
    }
    return VALUES_1(new_connection_spec);
}

/* NCONC-DESIGNATIONS-FROM-SUB-EXPRESSION */
Object nconc_designations_from_sub_expression(compiled_sub_expression,
	    expression_for_compilation)
    Object compiled_sub_expression, expression_for_compilation;
{
    Object temp, svref_new_value;

    x_note_fn_call(141,16);
    if (SIMPLE_VECTOR_P(compiled_sub_expression) && 
	    EQ(ISVREF(compiled_sub_expression,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	temp = ISVREF(expression_for_compilation,(SI_Long)2L);
	svref_new_value = nconc2(temp,
		copy_list_using_phrase_conses(ISVREF(compiled_sub_expression,
		(SI_Long)2L)));
	return VALUES_1(SVREF(expression_for_compilation,FIX((SI_Long)2L)) 
		= svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qquantifier;         /* quantifier */

static Object Qthere_exists_literal;  /* there-exists-literal */

/* COMPILE1-QUANTIFIER-OR-AGGREGATOR */
Object compile1_quantifier_or_aggregator(expression)
    Object expression;
{
    Object expression_for_compilation, operator_1, aggregator_scope;
    Object aggregator_expression, modified_aggregator_scope, local_name;
    Object compiled_aggregator_scope, compiled_aggregator_expression;
    Object svref_new_value;

    x_note_fn_call(141,17);
    expression_for_compilation = 
	    make_compilation_reclaimable_expression_for_compilation();
    operator_1 = FIRST(expression);
    aggregator_scope = SECOND(expression);
    aggregator_expression = THIRD(expression);
    modified_aggregator_scope = phrase_cons(Qquantifier,aggregator_scope);
    local_name = get_name_provided_by_role(SECOND(modified_aggregator_scope));
    compiled_aggregator_scope = 
	    compile1_designation(modified_aggregator_scope);
    compiled_aggregator_expression = 
	    compile1_forward_reference_for_designations(aggregator_expression);
    nconc_designations_from_sub_expression(compiled_aggregator_scope,
	    expression_for_compilation);
    nconc_designations_from_sub_expression(compiled_aggregator_expression,
	    expression_for_compilation);
    svref_new_value = phrase_list_3(operator_1,compiled_aggregator_scope,
	    compiled_aggregator_expression);
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = svref_new_value;
    if (EQ(operator_1,Qthere_exists_literal) && local_name)
	add_to_local_names_not_associated_with_roles(local_name);
    return VALUES_1(expression_for_compilation);
}

static Object list_constant_3;     /* # */

/* COMPILE1-CREATE-ACTION */
Object compile1_create_action(expression)
    Object expression;
{
    Object temp, local_name_for_create_action_qm;

    x_note_fn_call(141,18);
    temp = compile1_expression_according_to_template(expression);
    local_name_for_create_action_qm = memq_function(CAR(expression),
	    list_constant_3) ? FOURTH(expression) : THIRD(expression);
    if (local_name_for_create_action_qm)
	add_to_local_names_not_associated_with_roles(local_name_for_create_action_qm);
    return VALUES_1(temp);
}

/* ADD-TO-LOCAL-NAMES-NOT-ASSOCIATED-WITH-ROLES */
Object add_to_local_names_not_associated_with_roles(local_name)
    Object local_name;
{
    x_note_fn_call(141,19);
    Local_names_not_associated_with_roles = phrase_cons(local_name,
	    Local_names_not_associated_with_roles);
    return VALUES_1(Local_names_not_associated_with_roles);
}

/* COMPILE1-CALL-ASSIGNMENT-ACTION */
Object compile1_call_assignment_action(expression)
    Object expression;
{
    Object temp, local_name, ab_loop_list_;

    x_note_fn_call(141,20);
    temp = compile1_expression_according_to_template(expression);
    local_name = Nil;
    ab_loop_list_ = SECOND(expression);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    local_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_to_local_names_not_associated_with_roles(local_name);
    goto next_loop;
  end_loop:;
    return VALUES_1(temp);
}

/* COMPILE1-DESIGNATION */
Object compile1_designation(expression)
    Object expression;
{
    Object expression_for_compilation, local_reference_path;
    Object modify_macro_for_phrase_push_arg, svref_new_value;

    x_note_fn_call(141,21);
    expression_for_compilation = 
	    make_compilation_reclaimable_expression_for_compilation();
    local_reference_path = SYMBOLP(expression) ? 
	    compile_forward_reference_path_for_symbol(expression) : 
	    compile_forward_reference_path(expression,Nil);
    modify_macro_for_phrase_push_arg = local_reference_path;
    svref_new_value = 
	    phrase_cons_with_args_reversed(ISVREF(expression_for_compilation,
	    (SI_Long)3L),modify_macro_for_phrase_push_arg);
    SVREF(expression_for_compilation,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = SYMBOLP(expression) ? expression : 
	    find_target_name_of_reference_path(local_reference_path);
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = phrase_cons(expression_for_compilation,Nil);
    SVREF(expression_for_compilation,FIX((SI_Long)2L)) = svref_new_value;
    return combine_designation_with_embedded_expression_if_appropriate(expression_for_compilation,
	    local_reference_path);
}

/* COMBINE-DESIGNATION-WITH-EMBEDDED-EXPRESSION-IF-APPROPRIATE */
Object combine_designation_with_embedded_expression_if_appropriate(expression_for_compilation,
	    local_reference_path)
    Object expression_for_compilation, local_reference_path;
{
    Object next_rs_qm, embedded_expression_qm, temp;

    x_note_fn_call(141,22);
    next_rs_qm = local_reference_path;
    embedded_expression_qm = Nil;
  next_loop:
    if ( !TRUEP(next_rs_qm))
	goto end_loop;
    embedded_expression_qm = ISVREF(next_rs_qm,(SI_Long)11L);
    if (embedded_expression_qm)
	nconc_designations_from_sub_expression(embedded_expression_qm,
		expression_for_compilation);
    temp = ISVREF(next_rs_qm,(SI_Long)5L);
    next_rs_qm = CAR(temp);
    goto next_loop;
  end_loop:;
    return VALUES_1(expression_for_compilation);
}

/* FIND-TARGET-NAME-OF-REFERENCE-PATH */
Object find_target_name_of_reference_path(reference_structure)
    Object reference_structure;
{
    Object temp;

    x_note_fn_call(141,23);
    if ( !TRUEP(ISVREF(reference_structure,(SI_Long)5L)))
	return VALUES_1(ISVREF(reference_structure,(SI_Long)2L));
    else {
	temp = ISVREF(reference_structure,(SI_Long)5L);
	return find_target_name_of_reference_path(CAR(temp));
    }
}

/* EXPRESSION-FOR-COMPILATION-DESIGNATION-P */
Object expression_for_compilation_designation_p(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp;

    x_note_fn_call(141,24);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    return VALUES_1(SYMBOLP(temp) ? T : Nil);
}

static Object Qexplicitly_specified_local_name_refers_to_more_than_one_item;  /* explicitly-specified-local-name-refers-to-more-than-one-item */

static Object Qforward;            /* forward */

static Object Qbackward;           /* backward */

static Object Qboth;               /* both */

/* COMPILE-FORWARD-REFERENCE-PATH */
Object compile_forward_reference_path(expression,needing_reference_structure)
    Object expression, needing_reference_structure;
{
    Object providing_reference_structure, role, simple_role_of_role_1;
    Object role_name, explicitly_specified_local_name_qm;
    Object source_specified_local_name_provided;
    Object compiler_specified_local_name_provided;
    Object entry_in_names_used_for_more_than_one_item_qm;
    Object previously_declared_local_name_for_this_item_qm;
    Object entry_in_focus_local_names_for_focus_role_name_qm;
    Object extra_reference_structure, modify_macro_for_phrase_push_arg;
    Object svref_new_value, temp, local_name_or_name_of_object;
    char temp_1;

    x_note_fn_call(141,25);
    providing_reference_structure = 
	    make_compilation_reclaimable_reference_structure();
    role = SECOND(expression);
    simple_role_of_role_1 = simple_role_of_role(role);
    role_name = atomic_naming_element_of_role(role);
    explicitly_specified_local_name_qm = 
	    get_explicitly_specified_local_name_of_role_if_any(role);
    source_specified_local_name_provided = explicitly_specified_local_name_qm;
    if (source_specified_local_name_provided);
    else
	source_specified_local_name_provided = role_name;
    compiler_specified_local_name_provided = Nil;
    if (SYMBOLP(simple_role_of_role_1) && 
	    unauthorized_system_slot_p(simple_role_of_role_1))
	Attribute_name_errors = nconc2(Attribute_name_errors,
		phrase_cons(simple_role_of_role_1,Nil));
    if (explicitly_specified_local_name_qm)
	add_local_name_and_role_name_to_alist(explicitly_specified_local_name_qm,
		role_name);
    if (memq_function(source_specified_local_name_provided,
	    List_of_known_names) || 
	    designation_requires_previous_reference_p(expression) && 
	    assq_function(source_specified_local_name_provided,
	    Role_names_and_local_names_for_runtime_items)) {
	if ( !TRUEP(designation_requires_previous_reference_p(expression))) {
	    if (explicitly_specified_local_name_qm)
		Local_name_errors = nconc2(Local_name_errors,
			phrase_cons(phrase_cons(Qexplicitly_specified_local_name_refers_to_more_than_one_item,
			explicitly_specified_local_name_qm),Nil));
	    else {
		compiler_specified_local_name_provided = 
			interned_compilation_local_name_symbol();
		add_local_name_and_role_name_to_alist(compiler_specified_local_name_provided,
			role_name);
		add_role_name_and_local_name_to_alist_of_runtime_instances(role_name,
			role_name);
		if (Focus_name_for_rule_or_formula_compilation && 
			EQ(Focus_name_for_rule_or_formula_compilation,
			role_name))
		    Focus_local_names_for_focus_role_name = 
			    nconc2(Focus_local_names_for_focus_role_name,
			    phrase_cons(phrase_cons(compiler_specified_local_name_provided,
			    Compiling_antecedent_p ? Qforward : Qbackward),
			    Nil));
		entry_in_names_used_for_more_than_one_item_qm = 
			assq_function(source_specified_local_name_provided,
			Names_used_for_more_than_one_item);
		if (entry_in_names_used_for_more_than_one_item_qm)
		    nconc2(entry_in_names_used_for_more_than_one_item_qm,
			    phrase_cons(compiler_specified_local_name_provided,
			    Nil));
		else
		    Names_used_for_more_than_one_item = 
			    nconc2(Names_used_for_more_than_one_item,
			    phrase_cons(phrase_list_2(source_specified_local_name_provided,
			    compiler_specified_local_name_provided),Nil));
	    }
	}
	else {
	    check_for_ambiguous_reference(source_specified_local_name_provided);
	    check_if_role_name_is_same_as_previous_local_name(source_specified_local_name_provided);
	    previously_declared_local_name_for_this_item_qm = 
		    role_name_refers_to_item_declared_using_local_name_qm(source_specified_local_name_provided);
	    if (previously_declared_local_name_for_this_item_qm) {
		source_specified_local_name_provided = 
			previously_declared_local_name_for_this_item_qm;
		expression = source_specified_local_name_provided;
	    }
	    entry_in_focus_local_names_for_focus_role_name_qm = 
		    assq_function(source_specified_local_name_provided,
		    Focus_local_names_for_focus_role_name);
	    if (entry_in_focus_local_names_for_focus_role_name_qm &&  
		    !TRUEP(Compiling_antecedent_p) && 
		    EQ(CDR(entry_in_focus_local_names_for_focus_role_name_qm),
		    Qforward))
		M_CDR(entry_in_focus_local_names_for_focus_role_name_qm) = 
			Qboth;
	    compiler_specified_local_name_provided = 
		    source_specified_local_name_provided;
	}
    }
    else {
	compiler_specified_local_name_provided = 
		source_specified_local_name_provided;
	add_role_name_and_local_name_to_alist_of_runtime_instances(role_name,
		compiler_specified_local_name_provided);
	if (Focus_name_for_rule_or_formula_compilation && 
		EQ(Focus_name_for_rule_or_formula_compilation,role_name))
	    Focus_local_names_for_focus_role_name = 
		    nconc2(Focus_local_names_for_focus_role_name,
		    phrase_cons(phrase_cons(source_specified_local_name_provided,
		    Compiling_antecedent_p ? Qforward : Qbackward),Nil));
    }
    if ( !TRUEP(memq_function(compiler_specified_local_name_provided,
	    List_of_known_names)))
	List_of_known_names = nconc2(List_of_known_names,
		phrase_cons(compiler_specified_local_name_provided,Nil));
    if (SYMBOLP(expression)) {
	extra_reference_structure = 
		compile_forward_reference_path_for_symbol(expression);
	if (needing_reference_structure) {
	    modify_macro_for_phrase_push_arg = needing_reference_structure;
	    svref_new_value = 
		    phrase_cons_with_args_reversed(ISVREF(extra_reference_structure,
		    (SI_Long)5L),modify_macro_for_phrase_push_arg);
	    SVREF(extra_reference_structure,FIX((SI_Long)5L)) = 
		    svref_new_value;
	    SVREF(needing_reference_structure,FIX((SI_Long)4L)) = 
		    extra_reference_structure;
	    svref_new_value = ISVREF(extra_reference_structure,(SI_Long)2L);
	    SVREF(needing_reference_structure,FIX((SI_Long)1L)) = 
		    svref_new_value;
	}
	return VALUES_1(extra_reference_structure);
    }
    else {
	svref_new_value = FIRST(expression);
	SVREF(providing_reference_structure,FIX((SI_Long)6L)) = 
		svref_new_value;
	svref_new_value = SECOND(expression);
	SVREF(providing_reference_structure,FIX((SI_Long)3L)) = 
		svref_new_value;
	SVREF(providing_reference_structure,FIX((SI_Long)2L)) = 
		compiler_specified_local_name_provided;
	if (needing_reference_structure) {
	    modify_macro_for_phrase_push_arg = needing_reference_structure;
	    svref_new_value = 
		    phrase_cons_with_args_reversed(ISVREF(providing_reference_structure,
		    (SI_Long)5L),modify_macro_for_phrase_push_arg);
	    SVREF(providing_reference_structure,FIX((SI_Long)5L)) = 
		    svref_new_value;
	    SVREF(needing_reference_structure,FIX((SI_Long)4L)) = 
		    providing_reference_structure;
	    svref_new_value = ISVREF(providing_reference_structure,
		    (SI_Long)2L);
	    SVREF(needing_reference_structure,FIX((SI_Long)1L)) = 
		    svref_new_value;
	}
	if ( !TRUEP(CDDR(expression))) {
	    if (designation_requires_previous_reference_p(expression)) {
		svref_new_value = Needed_domain;
		SVREF(providing_reference_structure,FIX((SI_Long)1L)) = 
			svref_new_value;
	    }
	    else {
		svref_new_value = Global_domain;
		SVREF(providing_reference_structure,FIX((SI_Long)1L)) = 
			svref_new_value;
	    }
	    return VALUES_1(providing_reference_structure);
	}
	else {
	    if ( !TRUEP(CDDDDR(expression))) {
		temp = THIRD(expression);
		temp_1 = SYMBOLP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		local_name_or_name_of_object = THIRD(expression);
		SVREF(providing_reference_structure,FIX((SI_Long)1L)) = 
			local_name_or_name_of_object;
		extra_reference_structure = 
			symbol_used_as_local_name_p(local_name_or_name_of_object) 
			? 
			make_needing_reference_structure_for_symbol(local_name_or_name_of_object) 
			: 
			make_global_reference_structure_for_symbol(local_name_or_name_of_object);
		modify_macro_for_phrase_push_arg = 
			providing_reference_structure;
		svref_new_value = 
			phrase_cons_with_args_reversed(ISVREF(extra_reference_structure,
			(SI_Long)5L),modify_macro_for_phrase_push_arg);
		SVREF(extra_reference_structure,FIX((SI_Long)5L)) = 
			svref_new_value;
		SVREF(providing_reference_structure,FIX((SI_Long)4L)) = 
			extra_reference_structure;
		return compile1_embedded_expression_if_appropriate(extra_reference_structure,
			FOURTH(expression),providing_reference_structure);
	    }
	    else {
		temp = compile_forward_reference_path(THIRD(expression),
			providing_reference_structure);
		return compile1_embedded_expression_if_appropriate(temp,
			FOURTH(expression),providing_reference_structure);
	    }
	}
    }
}

/* COMPILE1-EMBEDDED-EXPRESSION-IF-APPROPRIATE */
Object compile1_embedded_expression_if_appropriate(reference_structure_to_return,
	    embedded_expression_qm,
	    reference_structure_to_hold_embedded_expression)
    Object reference_structure_to_return, embedded_expression_qm;
    Object reference_structure_to_hold_embedded_expression;
{
    Object svref_new_value;

    x_note_fn_call(141,26);
    if (embedded_expression_qm) {
	svref_new_value = 
		compile1_forward_reference_for_designations(embedded_expression_qm);
	SVREF(reference_structure_to_hold_embedded_expression,
		FIX((SI_Long)11L)) = svref_new_value;
	svref_new_value = 
		copy_tree_using_phrase_conses(embedded_expression_qm);
	SVREF(reference_structure_to_hold_embedded_expression,
		FIX((SI_Long)12L)) = svref_new_value;
    }
    return VALUES_1(reference_structure_to_return);
}

/* COMPILE-FORWARD-REFERENCE-PATH-FOR-SYMBOL */
Object compile_forward_reference_path_for_symbol(symbol)
    Object symbol;
{
    x_note_fn_call(141,27);
    if (symbol_used_as_local_name_p(symbol))
	return make_needing_reference_structure_for_symbol(symbol);
    else
	return make_global_reference_structure_for_symbol(symbol);
}

/* MAKE-NEEDING-REFERENCE-STRUCTURE-FOR-SYMBOL */
Object make_needing_reference_structure_for_symbol(symbol)
    Object symbol;
{
    x_note_fn_call(141,28);
    return make_extra_reference_structure(symbol,Needed_domain);
}

/* MAKE-GLOBAL-REFERENCE-STRUCTURE-FOR-SYMBOL */
Object make_global_reference_structure_for_symbol(symbol)
    Object symbol;
{
    x_note_fn_call(141,29);
    return make_extra_reference_structure(symbol,Global_domain);
}

/* MAKE-EXTRA-REFERENCE-STRUCTURE */
Object make_extra_reference_structure(symbol,domain)
    Object symbol, domain;
{
    Object extra_reference_structure;

    x_note_fn_call(141,30);
    extra_reference_structure = 
	    make_compilation_reclaimable_reference_structure();
    SVREF(extra_reference_structure,FIX((SI_Long)6L)) = Qthe;
    SVREF(extra_reference_structure,FIX((SI_Long)3L)) = symbol;
    SVREF(extra_reference_structure,FIX((SI_Long)2L)) = symbol;
    SVREF(extra_reference_structure,FIX((SI_Long)1L)) = domain;
    return VALUES_1(extra_reference_structure);
}

/* SYMBOL-USED-AS-LOCAL-NAME-P */
Object symbol_used_as_local_name_p(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(141,31);
    temp = assq_function(symbol,Alist_of_local_names_and_role_names);
    if (temp)
	return VALUES_1(temp);
    else
	return memq_function(symbol,Local_names_not_associated_with_roles);
}

/* ADD-LOCAL-NAME-AND-ROLE-NAME-TO-ALIST */
Object add_local_name_and_role_name_to_alist(local_name,role_name)
    Object local_name, role_name;
{
    x_note_fn_call(141,32);
    Alist_of_local_names_and_role_names = 
	    nconc2(Alist_of_local_names_and_role_names,
	    phrase_cons(phrase_cons(local_name,role_name),Nil));
    return VALUES_1(Alist_of_local_names_and_role_names);
}

/* ADD-ROLE-NAME-AND-LOCAL-NAME-TO-ALIST-OF-RUNTIME-INSTANCES */
Object add_role_name_and_local_name_to_alist_of_runtime_instances(role_name,
	    local_name)
    Object role_name, local_name;
{
    x_note_fn_call(141,33);
    Role_names_and_local_names_for_runtime_items = 
	    nconc2(Role_names_and_local_names_for_runtime_items,
	    phrase_cons(phrase_cons(role_name,local_name),Nil));
    return VALUES_1(Role_names_and_local_names_for_runtime_items);
}

static Object Qroot_reference_role_name_same_as_previously_specified_local_name;  /* root-reference-role-name-same-as-previously-specified-local-name */

/* CHECK-IF-ROLE-NAME-IS-SAME-AS-PREVIOUS-LOCAL-NAME */
Object check_if_role_name_is_same_as_previous_local_name(role_name)
    Object role_name;
{
    x_note_fn_call(141,34);
    if (assq_function(role_name,Alist_of_local_names_and_role_names)) {
	Local_name_errors = nconc2(Local_name_errors,
		phrase_cons(phrase_cons(Qroot_reference_role_name_same_as_previously_specified_local_name,
		role_name),Nil));
	return VALUES_1(Local_name_errors);
    }
    else
	return VALUES_1(Nil);
}

static Object Qambiguous_reference;  /* ambiguous-reference */

/* CHECK-FOR-AMBIGUOUS-REFERENCE */
Object check_for_ambiguous_reference(role_name)
    Object role_name;
{
    Object runtime_item_entries, entry, ab_loop_list_;
    Object first_instance_not_declared_using_local_name;

    x_note_fn_call(141,35);
    runtime_item_entries = Nil;
    entry = Nil;
    ab_loop_list_ = Role_names_and_local_names_for_runtime_items;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(role_name,CAR(entry)))
	runtime_item_entries = nconc2(runtime_item_entries,
		phrase_cons(entry,Nil));
    goto next_loop;
  end_loop:
    if (CDR(runtime_item_entries)) {
	first_instance_not_declared_using_local_name = Nil;
	entry = Nil;
	ab_loop_list_ = runtime_item_entries;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	entry = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(CAR(entry),CDR(entry))) {
	    if (first_instance_not_declared_using_local_name) {
		Local_name_errors = nconc2(Local_name_errors,
			phrase_cons(phrase_cons(Qambiguous_reference,
			role_name),Nil));
		goto end_1;
	    }
	    else
		first_instance_not_declared_using_local_name = entry;
	}
	goto next_loop_1;
      end_loop_1:
	if ( !TRUEP(first_instance_not_declared_using_local_name))
	    Local_name_errors = nconc2(Local_name_errors,
		    phrase_cons(phrase_cons(Qambiguous_reference,
		    role_name),Nil));
      end_1:;
    }
    return VALUES_1(Qnil);
}

/* ROLE-NAME-REFERS-TO-ITEM-DECLARED-USING-LOCAL-NAME? */
Object role_name_refers_to_item_declared_using_local_name_qm(role_name)
    Object role_name;
{
    Object runtime_item_entries, entry, ab_loop_list_, temp, temp_1;
    char temp_2;

    x_note_fn_call(141,36);
    runtime_item_entries = Nil;
    entry = Nil;
    ab_loop_list_ = Role_names_and_local_names_for_runtime_items;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(role_name,CAR(entry)))
	runtime_item_entries = nconc2(runtime_item_entries,
		phrase_cons(entry,Nil));
    goto next_loop;
  end_loop:
    if ( !TRUEP(CDR(runtime_item_entries))) {
	temp = CAR(runtime_item_entries);
	temp_1 = CAR(runtime_item_entries);
	temp_2 =  !EQ(CAR(temp),CDR(temp_1));
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	temp_1 = CAR(runtime_item_entries);
	return VALUES_1(CDR(temp_1));
    }
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Forward_compiled_antecedent, Qforward_compiled_antecedent);

DEFINE_VARIABLE_WITH_SYMBOL(Forward_compiled_consequent_qm, Qforward_compiled_consequent_qm);

/* COMPILE1-DESIGNATIONS-FOR-FOCUS */
Object compile1_designations_for_focus(forward_reference_compiled_left_side_of_formula_qm,
	    forward_reference_compiled_antecedent_expression,
	    forward_reference_compiled_consequent_expression_qm,focus_names)
    Object forward_reference_compiled_left_side_of_formula_qm;
    Object forward_reference_compiled_antecedent_expression;
    Object forward_reference_compiled_consequent_expression_qm, focus_names;
{
    Object designations, forward_compiled_antecedent;
    Object forward_compiled_consequent_qm, inverse_references_for_designations;
    Object focus_name, ab_loop_list_, focus_reference_structure;
    Object svref_new_value, designation;
    Object designation_found_to_have_inverse_reference_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(141,37);
    designations = forward_reference_compiled_left_side_of_formula_qm ? 
	    get_copy_of_designations_for_expression(forward_reference_compiled_left_side_of_formula_qm,
	    forward_reference_compiled_antecedent_expression) : 
	    forward_reference_compiled_consequent_expression_qm ? 
	    get_copy_of_designations_for_rule(forward_reference_compiled_antecedent_expression,
	    forward_reference_compiled_consequent_expression_qm) : 
	    SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
	    && EQ(ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)2L) : Nil;
    forward_compiled_antecedent = 
	    forward_reference_compiled_antecedent_expression;
    PUSH_SPECIAL_WITH_SYMBOL(Forward_compiled_antecedent,Qforward_compiled_antecedent,forward_compiled_antecedent,
	    1);
      forward_compiled_consequent_qm = 
	      forward_reference_compiled_consequent_expression_qm;
      PUSH_SPECIAL_WITH_SYMBOL(Forward_compiled_consequent_qm,Qforward_compiled_consequent_qm,forward_compiled_consequent_qm,
	      0);
	inverse_references_for_designations = Nil;
	focus_name = Nil;
	ab_loop_list_ = focus_names;
	focus_reference_structure = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	focus_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	focus_reference_structure = 
		make_compilation_reclaimable_reference_structure();
	SVREF(focus_reference_structure,FIX((SI_Long)1L)) = focus_name;
	svref_new_value = Focus_range;
	SVREF(focus_reference_structure,FIX((SI_Long)2L)) = svref_new_value;
	svref_new_value = Focus_range;
	SVREF(focus_reference_structure,FIX((SI_Long)3L)) = svref_new_value;
	SVREF(focus_reference_structure,FIX((SI_Long)6L)) = Qevery_inverse;
	inverse_references_for_designations = 
		phrase_cons(focus_reference_structure,
		inverse_references_for_designations);
	goto next_loop;
      end_loop:;
      next_loop_1:
	designation = Nil;
	ab_loop_list_ = designations;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	designation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (check_for_inverse_references(designation,
		inverse_references_for_designations)) {
	    designation_found_to_have_inverse_reference_qm = designation;
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_1:
	designation_found_to_have_inverse_reference_qm = Qnil;
      end_1:;
	if (designation_found_to_have_inverse_reference_qm)
	    designations = ldelete(6,
		    designation_found_to_have_inverse_reference_qm,
		    designations,Ktest,SYMBOL_FUNCTION(Qeq),Kcount,
		    FIX((SI_Long)1L));
	else
	    goto end_2;
	goto next_loop_1;
      end_loop_2:
      end_2:
	if (SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
		&& 
		EQ(ISVREF(forward_reference_compiled_antecedent_expression,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_expression_for_compilation_g2_struct))
	    SVREF(forward_reference_compiled_antecedent_expression,
		    FIX((SI_Long)4L)) = inverse_references_for_designations;
	if (forward_reference_compiled_consequent_expression_qm)
	    set_inverse_references_for_actions(forward_reference_compiled_consequent_expression_qm,
		    inverse_references_for_designations);
	result = VALUES_1(inverse_references_for_designations);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* GET-COPY-OF-DESIGNATIONS-FOR-RULE */
Object get_copy_of_designations_for_rule(forward_reference_compiled_antecedent_expression,
	    forward_reference_compiled_consequent_expression)
    Object forward_reference_compiled_antecedent_expression;
    Object forward_reference_compiled_consequent_expression;
{
    Object temp, temp_1;

    x_note_fn_call(141,38);
    temp = 
	    copy_list_using_phrase_conses(Designations_from_explicit_iteration_forms);
    temp_1 = 
	    SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
	    && EQ(ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? 
	    copy_list_using_phrase_conses(ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)2L)) : Nil;
    return VALUES_1(nconc2(temp,nconc2(temp_1,
	    get_copy_of_designations_for_actions(forward_reference_compiled_consequent_expression))));
}

/* GET-COPY-OF-DESIGNATIONS-FOR-EXPRESSION */
Object get_copy_of_designations_for_expression(forward_reference_compiled_left_side_of_formula_qm,
	    forward_reference_compiled_antecedent_expression)
    Object forward_reference_compiled_left_side_of_formula_qm;
    Object forward_reference_compiled_antecedent_expression;
{
    Object temp;

    x_note_fn_call(141,39);
    temp = 
	    copy_list_using_phrase_conses(ISVREF(forward_reference_compiled_left_side_of_formula_qm,
	    (SI_Long)2L));
    return VALUES_1(nconc2(temp,
	    SIMPLE_VECTOR_P(forward_reference_compiled_antecedent_expression) 
	    && EQ(ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
	    ? 
	    copy_list_using_phrase_conses(ISVREF(forward_reference_compiled_antecedent_expression,
	    (SI_Long)2L)) : Nil));
}

/* GET-COPY-OF-DESIGNATIONS-FOR-ACTIONS */
Object get_copy_of_designations_for_actions(action_or_actions)
    Object action_or_actions;
{
    Object expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(141,40);
    expression = Nil;
    ab_loop_list_ = CDR(action_or_actions);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = copy_list_using_phrase_conses(ISVREF(expression,
	    (SI_Long)2L));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* SET-INVERSE-REFERENCES-FOR-ACTIONS */
Object set_inverse_references_for_actions(action_or_actions,
	    inverse_references_for_designations)
    Object action_or_actions, inverse_references_for_designations;
{
    Object expression, ab_loop_list_;

    x_note_fn_call(141,41);
    expression = Nil;
    ab_loop_list_ = CDR(action_or_actions);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    SVREF(expression,FIX((SI_Long)4L)) = inverse_references_for_designations;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CHECK-FOR-INVERSE-REFERENCES */
Object check_for_inverse_references(designation,
	    inverse_references_for_designations)
    Object designation, inverse_references_for_designations;
{
    Object temp, reference_structure;

    x_note_fn_call(141,42);
    temp = ISVREF(designation,(SI_Long)3L);
    reference_structure = CAR(temp);
    if (reference_structure && 
	    check_for_inverse_references_rec(designation,
	    reference_structure,inverse_references_for_designations))
	return VALUES_1(designation);
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-INVERSE-REFERENCES-REC */
Object check_for_inverse_references_rec(designation,reference_structure,
	    inverse_references_for_designations)
    Object designation, reference_structure;
    Object inverse_references_for_designations;
{
    Object needing_reference_structure, ab_loop_list_;

    x_note_fn_call(141,43);
    if ( !EQ(ISVREF(reference_structure,(SI_Long)2L),Focus_range)) {
	if (better_reference_provided_by_inverse_reference_qm(designation,
		reference_structure,inverse_references_for_designations))
	    return VALUES_1(T);
	else {
	    needing_reference_structure = Nil;
	    ab_loop_list_ = ISVREF(reference_structure,(SI_Long)5L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    needing_reference_structure = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (check_for_inverse_references_rec(designation,
		    needing_reference_structure,
		    inverse_references_for_designations))
		return VALUES_1(T);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* BETTER-REFERENCE-PROVIDED-BY-INVERSE-REFERENCE? */
Object better_reference_provided_by_inverse_reference_qm(designation,
	    reference_structure,inverse_references_for_designations)
    Object designation, reference_structure;
    Object inverse_references_for_designations;
{
    Object inverse_reference, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(141,44);
    inverse_reference = Nil;
    ab_loop_list_ = inverse_references_for_designations;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    inverse_reference = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = 
	    better_reference_provided_by_inverse_reference_rec_qm(designation,
	    reference_structure,inverse_reference);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* END-REFERENCE-STRUCTURE-P */
Object end_reference_structure_p(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(141,45);
    return VALUES_1( !TRUEP(ISVREF(reference_structure,(SI_Long)5L)) ? T : 
	    Nil);
}

/* BETTER-REFERENCE-PROVIDED-BY-INVERSE-REFERENCE-REC? */
Object better_reference_provided_by_inverse_reference_rec_qm(designation,
	    reference_structure,inverse_reference)
    Object designation, reference_structure, inverse_reference;
{
    Object providing_reference_structure_qm, svref_new_value;
    Object needing_inverse_reference, ab_loop_list_;
    char temp;

    x_note_fn_call(141,46);
    if ( 
		!TRUEP(reference_structure_for_global_symbol_p(reference_structure))) {
	if (EQ(ISVREF(inverse_reference,(SI_Long)1L),
		ISVREF(reference_structure,(SI_Long)1L))) {
	    providing_reference_structure_qm = ISVREF(reference_structure,
		    (SI_Long)4L);
	    temp = providing_reference_structure_qm ?  
		    !TRUEP(reference_structure_for_global_symbol_p(providing_reference_structure_qm)) 
		    : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else if (end_reference_structure_p(reference_structure) && 
		EQ(ISVREF(inverse_reference,(SI_Long)1L),
		ISVREF(reference_structure,(SI_Long)2L)))
	    temp = TRUEP(SVREF(reference_structure,FIX((SI_Long)8L)) = T);
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	check_for_illegal_focus(designation,reference_structure);
	add_new_inverse_references(reference_structure,inverse_reference);
	svref_new_value = 
		phrase_cons(build_inverse_reference_path_for_designation(reference_structure,
		inverse_reference),Nil);
	SVREF(designation,FIX((SI_Long)3L)) = svref_new_value;
	return VALUES_1(T);
    }
    else {
	needing_inverse_reference = Nil;
	ab_loop_list_ = ISVREF(inverse_reference,(SI_Long)5L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	needing_inverse_reference = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (better_reference_provided_by_inverse_reference_rec_qm(designation,
		reference_structure,needing_inverse_reference))
	    return VALUES_1(T);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* CHECK-FOR-ILLEGAL-FOCUS */
Object check_for_illegal_focus(designation,reference_structure)
    Object designation, reference_structure;
{
    Object providing_reference_structure_qm;
    char temp;

    x_note_fn_call(141,47);
    if (ISVREF(reference_structure,(SI_Long)8L))
	temp =  !( !TRUEP(ISVREF(reference_structure,(SI_Long)4L)) && 
		EQ(ISVREF(reference_structure,(SI_Long)1L),Needed_domain));
    else {
	providing_reference_structure_qm = ISVREF(reference_structure,
		(SI_Long)4L);
	temp = providing_reference_structure_qm ?  !( 
		!TRUEP(ISVREF(providing_reference_structure_qm,
		(SI_Long)4L)) && 
		EQ(ISVREF(providing_reference_structure_qm,(SI_Long)1L),
		Needed_domain)) : TRUEP(Nil);
    }
    if (temp)
	return check_for_illegal_focus_in_rule_consequent(designation);
    else
	return VALUES_1(Nil);
}

/* CHECK-FOR-ILLEGAL-FOCUS-IN-RULE-CONSEQUENT */
Object check_for_illegal_focus_in_rule_consequent(designation)
    Object designation;
{
    Object consequent_action, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(141,48);
    if (Forward_compiled_consequent_qm) {
	consequent_action = Nil;
	ab_loop_list_ = CDR(Forward_compiled_consequent_qm);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	consequent_action = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = illegal_focus_in_action_qm(consequent_action,
		designation);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_4;     /* # */

/* ILLEGAL-FOCUS-IN-ACTION? */
Object illegal_focus_in_action_qm(action,focus_designation)
    Object action, focus_designation;
{
    Object compiled_specific_expression, temp, conclude_expression_qm;
    char temp_1;

    x_note_fn_call(141,49);
    if (SIMPLE_VECTOR_P(action) && EQ(ISVREF(action,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	compiled_specific_expression = ISVREF(action,(SI_Long)1L);
	temp = CAR(compiled_specific_expression);
	if (member_eql(temp,list_constant_4)) {
	    conclude_expression_qm = THIRD(compiled_specific_expression);
	    temp_1 = conclude_expression_qm && 
		    SIMPLE_VECTOR_P(conclude_expression_qm) && 
		    EQ(ISVREF(conclude_expression_qm,(SI_Long)0L),
		    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct) 
		    ? TRUEP(memq_function(focus_designation,
		    ISVREF(conclude_expression_qm,(SI_Long)2L))) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(memq_function(focus_designation,ISVREF(action,
		    (SI_Long)2L)));
	if (temp_1) {
	    Fatal_focus_error_info_qm = CAR(compiled_specific_expression);
	    return VALUES_1(Fatal_focus_error_info_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* BUILD-INVERSE-REFERENCE-PATH-FOR-DESIGNATION */
Object build_inverse_reference_path_for_designation(forward_reference_structure,
	    inverse_reference_structure)
    Object forward_reference_structure, inverse_reference_structure;
{
    Object svref_new_value;

    x_note_fn_call(141,50);
    if (EQ(ISVREF(inverse_reference_structure,(SI_Long)1L),
	    ISVREF(forward_reference_structure,(SI_Long)2L))) {
	svref_new_value = Needed_domain;
	SVREF(forward_reference_structure,FIX((SI_Long)1L)) = svref_new_value;
    }
    return VALUES_1(forward_reference_structure);
}

/* ADD-NEW-INVERSE-REFERENCES */
Object add_new_inverse_references(reference_structure,
	    providing_inverse_reference_structure)
    Object reference_structure, providing_inverse_reference_structure;
{
    Object new_inverse_reference_structure, modify_macro_for_phrase_push_arg;
    Object svref_new_value;

    x_note_fn_call(141,51);
    if ( !EQ(ISVREF(reference_structure,(SI_Long)1L),Needed_domain)) {
	new_inverse_reference_structure = 
		build_inverse_reference_path(reference_structure,
		providing_inverse_reference_structure);
	if (new_inverse_reference_structure) {
	    modify_macro_for_phrase_push_arg = new_inverse_reference_structure;
	    svref_new_value = 
		    phrase_cons_with_args_reversed(ISVREF(providing_inverse_reference_structure,
		    (SI_Long)5L),modify_macro_for_phrase_push_arg);
	    SVREF(providing_inverse_reference_structure,FIX((SI_Long)5L)) 
		    = svref_new_value;
	    return VALUES_1(SVREF(new_inverse_reference_structure,
		    FIX((SI_Long)4L)) = providing_inverse_reference_structure);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* BUILD-INVERSE-REFERENCE-PATH */
Object build_inverse_reference_path(reference_structure,
	    inverse_reference_structure)
    Object reference_structure, inverse_reference_structure;
{
    Object new_inverse_reference_structure, old_providing_reference_structure;
    Object svref_new_value;

    x_note_fn_call(141,52);
    new_inverse_reference_structure = 
	    make_compilation_reclaimable_reference_structure();
    old_providing_reference_structure =  !TRUEP(ISVREF(reference_structure,
	    (SI_Long)5L)) && EQ(ISVREF(inverse_reference_structure,
	    (SI_Long)1L),ISVREF(reference_structure,(SI_Long)2L)) ? 
	    reference_structure : ISVREF(reference_structure,(SI_Long)4L);
    if ( !EQ(ISVREF(old_providing_reference_structure,(SI_Long)1L),
	    Needed_domain)) {
	SVREF(new_inverse_reference_structure,FIX((SI_Long)6L)) = 
		Qevery_inverse;
	svref_new_value = ISVREF(old_providing_reference_structure,
		(SI_Long)6L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)7L)) = 
		svref_new_value;
	svref_new_value = ISVREF(old_providing_reference_structure,
		(SI_Long)1L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)1L)) = 
		svref_new_value;
	svref_new_value = ISVREF(old_providing_reference_structure,
		(SI_Long)2L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)2L)) = 
		svref_new_value;
	svref_new_value = ISVREF(old_providing_reference_structure,
		(SI_Long)3L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)3L)) = 
		svref_new_value;
	svref_new_value = ISVREF(old_providing_reference_structure,
		(SI_Long)12L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)12L)) = 
		svref_new_value;
	build_inverse_reference_path_rec(new_inverse_reference_structure,
		ISVREF(old_providing_reference_structure,(SI_Long)4L));
	return VALUES_1(new_inverse_reference_structure);
    }
    else
	return VALUES_1(Nil);
}

/* BUILD-INVERSE-REFERENCE-PATH-REC */
Object build_inverse_reference_path_rec(previous_reference_structure,
	    reference_structure)
    Object previous_reference_structure, reference_structure;
{
    Object new_inverse_reference_structure, svref_new_value;
    Object modify_macro_for_phrase_push_arg;

    x_note_fn_call(141,53);
    if (reference_structure &&  !EQ(ISVREF(reference_structure,
	    (SI_Long)1L),Needed_domain)) {
	new_inverse_reference_structure = 
		make_compilation_reclaimable_reference_structure();
	SVREF(new_inverse_reference_structure,FIX((SI_Long)6L)) = 
		Qevery_inverse;
	svref_new_value = ISVREF(reference_structure,(SI_Long)6L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)7L)) = 
		svref_new_value;
	svref_new_value = ISVREF(reference_structure,(SI_Long)1L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)1L)) = 
		svref_new_value;
	svref_new_value = ISVREF(reference_structure,(SI_Long)2L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)2L)) = 
		svref_new_value;
	svref_new_value = ISVREF(reference_structure,(SI_Long)3L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)3L)) = 
		svref_new_value;
	svref_new_value = ISVREF(reference_structure,(SI_Long)12L);
	SVREF(new_inverse_reference_structure,FIX((SI_Long)12L)) = 
		svref_new_value;
	modify_macro_for_phrase_push_arg = new_inverse_reference_structure;
	svref_new_value = 
		phrase_cons_with_args_reversed(ISVREF(previous_reference_structure,
		(SI_Long)5L),modify_macro_for_phrase_push_arg);
	SVREF(previous_reference_structure,FIX((SI_Long)5L)) = svref_new_value;
	SVREF(new_inverse_reference_structure,FIX((SI_Long)4L)) = 
		previous_reference_structure;
	return build_inverse_reference_path_rec(new_inverse_reference_structure,
		ISVREF(reference_structure,(SI_Long)4L));
    }
    else
	return VALUES_1(Nil);
}

/* COMBINE-REFERENCES-FOR-EXPRESSION */
Object combine_references_for_expression(expression)
    Object expression;
{
    Object temp_1, operator_1, designation_p, reference_paths_for_expression;
    Object sub_expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, reference_paths;
    char temp;

    x_note_fn_call(141,54);
    if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	temp = TRUEP(expression_for_compilation_designation_p(expression));
	if (temp);
	else {
	    temp_1 = ISVREF(expression,(SI_Long)1L);
	    temp =  !LISTP(temp_1);
	}
	if (temp)
	    operator_1 = Qplus;
	else {
	    temp_1 = ISVREF(expression,(SI_Long)1L);
	    operator_1 = CAR(temp_1);
	}
	if ( !TRUEP(operator_does_not_require_references_p(operator_1))) {
	    designation_p = 
		    expression_for_compilation_designation_p(expression);
	    if (designation_p)
		reference_paths_for_expression = 
			combine_references_for_designation(expression);
	    else {
		sub_expression = Nil;
		temp_1 = ISVREF(expression,(SI_Long)1L);
		ab_loop_list_ = CDR(temp_1);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		sub_expression = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loopvar__2 = 
			combine_and_copy_references_for_expression(sub_expression);
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		goto next_loop;
	      end_loop:
		reference_paths = ab_loopvar_;
		goto end_1;
		reference_paths = Qnil;
	      end_1:;
		reference_paths_for_expression = 
			combine_reference_finding_paths(reference_paths);
	    }
	    if ( !TRUEP(designation_p))
		SVREF(expression,FIX((SI_Long)3L)) = 
			reference_paths_for_expression;
	    return VALUES_1(reference_paths_for_expression);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COMBINE-REFERENCES-FOR-DESIGNATION */
Object combine_references_for_designation(designation_expression_for_compilation)
    Object designation_expression_for_compilation;
{
    Object copied_local_reference_path, next_rs_qm, embedded_expression_qm;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object paths_for_embedded_expressions_qm;

    x_note_fn_call(141,55);
    copied_local_reference_path = 
	    copy_list_using_phrase_conses(ISVREF(designation_expression_for_compilation,
	    (SI_Long)3L));
    next_rs_qm = CAR(copied_local_reference_path);
    embedded_expression_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(next_rs_qm))
	goto end_loop;
    embedded_expression_qm = ISVREF(next_rs_qm,(SI_Long)11L);
    ab_loopvar__2 = embedded_expression_qm ? 
	    combine_and_copy_references_for_expression(embedded_expression_qm) 
	    : Nil;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    temp = ISVREF(next_rs_qm,(SI_Long)5L);
    next_rs_qm = CAR(temp);
    goto next_loop;
  end_loop:
    paths_for_embedded_expressions_qm = ab_loopvar_;
    goto end_1;
    paths_for_embedded_expressions_qm = Qnil;
  end_1:;
    if ( !TRUEP(paths_for_embedded_expressions_qm))
	return VALUES_1(copied_local_reference_path);
    else
	return combine_reference_finding_paths(nconc2(copied_local_reference_path,
		paths_for_embedded_expressions_qm));
}

/* COMBINE-AND-COPY-REFERENCES-FOR-EXPRESSION */
Object combine_and_copy_references_for_expression(expression)
    Object expression;
{
    x_note_fn_call(141,56);
    return copy_list_using_phrase_conses(combine_references_for_expression(expression));
}

/* COMBINE-REFERENCE-PATHS-FOR-EXPLICIT-ITERATION-DESIGNATIONS */
Object combine_reference_paths_for_explicit_iteration_designations()
{
    Object designation, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, reference_paths;

    x_note_fn_call(141,57);
    designation = Nil;
    ab_loop_list_ = Designations_from_explicit_iteration_forms;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = copy_list_using_phrase_conses(ISVREF(designation,
	    (SI_Long)3L));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    reference_paths = ab_loopvar_;
    goto end_1;
    reference_paths = Qnil;
  end_1:;
    return combine_reference_finding_paths(reference_paths);
}

/* COMBINE-REFERENCES-FOR-ACTIONS */
Object combine_references_for_actions(action_or_actions)
    Object action_or_actions;
{
    Object expression, ab_loop_list_;

    x_note_fn_call(141,58);
    expression = Nil;
    ab_loop_list_ = CDR(action_or_actions);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    combine_references_for_expression(expression);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* COMBINE-REFERENCES-FOR-ANTECEDENT-AND-CONSEQUENT */
Object combine_references_for_antecedent_and_consequent(combined_inverse_and_antecedent_reference_tree,
	    antecedent,consequent)
    Object combined_inverse_and_antecedent_reference_tree, antecedent;
    Object consequent;
{
    Object expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, reference_paths_for_consequent, reference_paths;

    x_note_fn_call(141,59);
    expression = Nil;
    ab_loop_list_ = CDR(consequent);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = copy_list_using_phrase_conses(ISVREF(expression,
	    (SI_Long)3L));
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    reference_paths_for_consequent = ab_loopvar_;
    goto end_1;
    reference_paths_for_consequent = Qnil;
  end_1:;
    reference_paths = 
	    nconc2(copy_list_using_phrase_conses(combined_inverse_and_antecedent_reference_tree),
	    reference_paths_for_consequent);
    return combine_reference_finding_paths(reference_paths);
}

/* COMBINE-INVERSE-REFERENCE-PATHS-WITH-LOCAL-REFERENCE-PATHS */
Object combine_inverse_reference_paths_with_local_reference_paths(inverse_references,
	    local_references)
    Object inverse_references, local_references;
{
    Object combined_reference_paths, reference_structure, ab_loop_list_;

    x_note_fn_call(141,60);
    combined_reference_paths = phrase_cons(copy_reference_structure(1,
	    CAR(inverse_references)),Nil);
    reference_structure = Nil;
    ab_loop_list_ = local_references;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    combined_reference_paths = 
	    combine_reference_finding_paths_1(combined_reference_paths,
	    reference_structure);
    goto next_loop;
  end_loop:
    return VALUES_1(combined_reference_paths);
    return VALUES_1(Qnil);
}

/* COMBINE-EXPLICIT-ITERATION-AND-ANTECEDENT-REFERENCE-TREES */
Object combine_explicit_iteration_and_antecedent_reference_trees(explicit_iteration_references,
	    local_references)
    Object explicit_iteration_references, local_references;
{
    x_note_fn_call(141,61);
    return combine_reference_finding_paths(nconc2(explicit_iteration_references,
	    copy_list_using_phrase_conses(local_references)));
}

/* COMBINE-LEFT-SIDE-TREE-WITH-RIGHT-SIDE-TREE */
Object combine_left_side_tree_with_right_side_tree(left_side_local_references,
	    right_side_local_references)
    Object left_side_local_references, right_side_local_references;
{
    Object combined_reference_paths, reference_structure, ab_loop_list_;

    x_note_fn_call(141,62);
    combined_reference_paths = phrase_cons(copy_reference_structure(1,
	    CAR(left_side_local_references)),Nil);
    reference_structure = Nil;
    ab_loop_list_ = right_side_local_references;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    combined_reference_paths = 
	    combine_reference_finding_paths_1(combined_reference_paths,
	    reference_structure);
    goto next_loop;
  end_loop:
    return VALUES_1(combined_reference_paths);
    return VALUES_1(Qnil);
}

/* COMBINE-REFERENCE-FINDING-PATHS */
Object combine_reference_finding_paths(reference_paths)
    Object reference_paths;
{
    Object combined_reference_paths, reference_structure, ab_loop_list_;

    x_note_fn_call(141,63);
    combined_reference_paths = Nil;
    reference_structure = Nil;
    ab_loop_list_ = reference_paths;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    combined_reference_paths = 
	    combine_reference_finding_paths_1(combined_reference_paths,
	    reference_structure);
    goto next_loop;
  end_loop:
    return VALUES_1(combined_reference_paths);
    return VALUES_1(Qnil);
}

/* COMBINE-REFERENCE-FINDING-PATHS-1 */
Object combine_reference_finding_paths_1(reference_structure_list_1,
	    reference_structure_2)
    Object reference_structure_list_1, reference_structure_2;
{
    Object copy_of_reference_structure_2, reference_structure, ab_loop_list_;

    x_note_fn_call(141,64);
    if ( !TRUEP(reference_structure_2))
	return VALUES_1(reference_structure_list_1);
    else if ( !TRUEP(reference_structure_list_1))
	return phrase_cons(copy_reference_structure(1,
		reference_structure_2),Nil);
    else {
	copy_of_reference_structure_2 = copy_reference_structure(1,
		reference_structure_2);
	reference_structure = Nil;
	ab_loop_list_ = reference_structure_list_1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(combining_needing_roots_p(reference_structure,
		copy_of_reference_structure_2)) && 
		combine_reference_finding_paths_rec(reference_structure,
		copy_of_reference_structure_2))
	    return VALUES_1(reference_structure_list_1);
	goto next_loop;
      end_loop:
	return VALUES_1(nconc2(reference_structure_list_1,
		phrase_cons(copy_of_reference_structure_2,Nil)));
	return VALUES_1(Qnil);
    }
}

/* IMPLICIT-ITERATOR-IN-REFERENCE-STRUCTURE */
Object implicit_iterator_in_reference_structure(test_reference_structure)
    Object test_reference_structure;
{
    Object result_qm, use, ab_loop_list_;

    x_note_fn_call(141,65);
    result_qm = Nil;
    result_qm = implicit_iterator_p(ISVREF(test_reference_structure,
	    (SI_Long)6L));
    use = Nil;
    ab_loop_list_ = ISVREF(test_reference_structure,(SI_Long)5L);
  next_loop:
    if (result_qm)
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    use = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result_qm = implicit_iterator_p(ISVREF(use,(SI_Long)6L));
    goto next_loop;
  end_loop:;
    return VALUES_1(result_qm);
}

/* COMBINING-NEEDING-ROOTS-P */
Object combining_needing_roots_p(reference_structure_to_try,
	    reference_structure_2)
    Object reference_structure_to_try, reference_structure_2;
{
    Object temp;

    x_note_fn_call(141,66);
    temp = EQ(ISVREF(reference_structure_to_try,(SI_Long)1L),
	    Needed_domain) && EQ(ISVREF(reference_structure_2,(SI_Long)1L),
	    Needed_domain) ? (EQ(ISVREF(reference_structure_to_try,
	    (SI_Long)2L),ISVREF(reference_structure_2,(SI_Long)2L)) ? T : 
	    Nil) : Qnil;
    if (temp);
    else
	temp = EQ(ISVREF(reference_structure_to_try,(SI_Long)6L),
		Qquantifier) && 
		implicit_iterator_in_reference_structure(reference_structure_2) 
		? T : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (EQ(ISVREF(reference_structure_2,(SI_Long)6L),Qquantifier) && 
	    implicit_iterator_in_reference_structure(reference_structure_to_try))
	return VALUES_1(T);
    else
	return VALUES_1(Nil);
}

/* COMBINE-REFERENCE-FINDING-PATHS-REC */
Object combine_reference_finding_paths_rec(reference_structure_to_try,
	    reference_structure_2)
    Object reference_structure_to_try, reference_structure_2;
{
    Object modify_macro_for_phrase_push_arg, svref_new_value;
    Object reference_structure, ab_loop_list_;

    x_note_fn_call(141,67);
    if (EQ(ISVREF(reference_structure_2,(SI_Long)1L),Global_domain))
	return VALUES_1(Nil);
    else if (EQ(ISVREF(reference_structure_2,(SI_Long)1L),Needed_domain) 
	    && EQ(ISVREF(reference_structure_2,(SI_Long)2L),
	    ISVREF(reference_structure_to_try,(SI_Long)2L)) || 
	    EQ(ISVREF(reference_structure_2,(SI_Long)1L),
	    ISVREF(reference_structure_to_try,(SI_Long)2L))) {
	modify_macro_for_phrase_push_arg = reference_structure_2;
	svref_new_value = 
		phrase_cons_with_args_reversed(ISVREF(reference_structure_to_try,
		(SI_Long)5L),modify_macro_for_phrase_push_arg);
	SVREF(reference_structure_to_try,FIX((SI_Long)5L)) = svref_new_value;
	SVREF(reference_structure_2,FIX((SI_Long)4L)) = 
		reference_structure_to_try;
	return VALUES_1(reference_structure_to_try);
    }
    else {
	reference_structure = Nil;
	ab_loop_list_ = ISVREF(reference_structure_to_try,(SI_Long)5L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (combine_reference_finding_paths_rec(reference_structure,
		reference_structure_2))
	    return VALUES_1(reference_structure_to_try);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* COPY-REFERENCE-STRUCTURE */
Object copy_reference_structure varargs_1(int, n)
{
    Object reference_structure;
    Object providing_reference_structure, copied_reference_structure;
    Object svref_new_value, needing_reference_structure, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(141,68);
    INIT_ARGS_nonrelocating();
    reference_structure = REQUIRED_ARG_nonrelocating();
    providing_reference_structure = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    copied_reference_structure = 
	    make_compilation_reclaimable_reference_structure();
    svref_new_value = ISVREF(reference_structure,(SI_Long)1L);
    SVREF(copied_reference_structure,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = ISVREF(reference_structure,(SI_Long)2L);
    SVREF(copied_reference_structure,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = ISVREF(reference_structure,(SI_Long)3L);
    SVREF(copied_reference_structure,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = ISVREF(reference_structure,(SI_Long)6L);
    SVREF(copied_reference_structure,FIX((SI_Long)6L)) = svref_new_value;
    svref_new_value = ISVREF(reference_structure,(SI_Long)12L);
    SVREF(copied_reference_structure,FIX((SI_Long)12L)) = svref_new_value;
    svref_new_value = ISVREF(reference_structure,(SI_Long)7L);
    SVREF(copied_reference_structure,FIX((SI_Long)7L)) = svref_new_value;
    SVREF(reference_structure,FIX((SI_Long)9L)) = copied_reference_structure;
    SVREF(copied_reference_structure,FIX((SI_Long)10L)) = reference_structure;
    needing_reference_structure = Nil;
    ab_loop_list_ = ISVREF(reference_structure,(SI_Long)5L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    needing_reference_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(copy_reference_structure(2,
	    needing_reference_structure,copied_reference_structure),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    goto end_1;
    ab_loopvar_ = Qnil;
  end_1:;
    SVREF(copied_reference_structure,FIX((SI_Long)5L)) = ab_loopvar_;
    if (providing_reference_structure)
	SVREF(copied_reference_structure,FIX((SI_Long)4L)) = 
		providing_reference_structure;
    return VALUES_1(copied_reference_structure);
}

/* GET-COPY-OF-REFERENCE-STRUCTURE-IN-HIGHEST-LEVEL-REFERENCE-TREE */
Object get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(141,69);
    return change_reference_structures_at_all_higher_levels(reference_structure,
	    Nil,Nil);
}

/* CHANGE-REFERENCE-STRUCTURES-AT-ALL-HIGHER-LEVELS */
Object change_reference_structures_at_all_higher_levels(reference_structure,
	    change_function_qm,change_arg_qm)
    Object reference_structure, change_function_qm, change_arg_qm;
{
    Object higher_level_reference_structure;

    x_note_fn_call(141,70);
    higher_level_reference_structure = ISVREF(reference_structure,(SI_Long)9L);
  next_loop:
    if (change_function_qm)
	FUNCALL_2(change_function_qm,reference_structure,change_arg_qm);
    if ( !TRUEP(higher_level_reference_structure))
	return VALUES_1(reference_structure);
    else {
	reference_structure = higher_level_reference_structure;
	higher_level_reference_structure = ISVREF(reference_structure,
		(SI_Long)9L);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(In_non_top_level_context_qm, Qin_non_top_level_context_qm);

/* COMPILE2-EXPRESSION-TOP */
Object compile2_expression_top(expression)
    Object expression;
{
    x_note_fn_call(141,71);
    if (phrase_number_p(expression))
	return VALUES_1(expression);
    else if (SYMBOLP(expression))
	return VALUES_1(expression);
    else if (text_string_p(expression))
	return VALUES_1(expression);
    else if (CONSP(expression) && (EQ(CAR(expression),Qquote) || 
	    phrase_number_p(CAR(expression))))
	return VALUES_1(expression);
    else if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct))
	return compile2_expression_1_top(expression);
    else
	return VALUES_1(Qnil);
}

/* COMPILE2-EXPRESSION */
Object compile2_expression(expression)
    Object expression;
{
    Object temp, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, expression_for_insertion, temp_1, sub_expression;
    Object return_expression, iteration_forms, insertion_location;
    Object result;

    x_note_fn_call(141,72);
    if (phrase_number_p(expression))
	return VALUES_3(Nil,expression,Nil);
    else if (SYMBOLP(expression))
	return VALUES_3(Nil,expression,Nil);
    else if (text_string_p(expression))
	return VALUES_3(Nil,expression,Nil);
    else if (CONSP(expression) && EQ(M_CDR(expression),
	    Phrase_structure_marker))
	return VALUES_3(Nil,expression,Nil);
    else if (CONSP(expression) && EQ(M_CDR(expression),Phrase_sequence_marker))
	return VALUES_3(Nil,expression,Nil);
    else if (CONSP(expression)) {
	if (EQ(CAR(expression),Qquote) || phrase_number_p(CAR(expression)))
	    return VALUES_3(Nil,expression,Nil);
	else if (EQ(M_CAR(expression),Qthe)) {
	    temp = SECOND(expression);
	    domain = Nil;
	    ab_loop_list_ = CDDR(expression);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    domain = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result = compile2_expression(domain);
	    expression_for_insertion = NTH_VALUE((SI_Long)1L, result);
	    ab_loopvar__2 = phrase_cons(expression_for_insertion,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	    temp_1 = phrase_cons(Qthe,phrase_cons(temp,temp_1));
	    return VALUES_3(Nil,temp_1,Nil);
	}
	else {
	    sub_expression = Nil;
	    ab_loop_list_ = expression;
	    return_expression = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    sub_expression = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    result = compile2_expression(sub_expression);
	    MVS_3(result,iteration_forms,expression_for_insertion,
		    insertion_location);
	    ab_loopvar__1 = phrase_cons(expression_for_insertion,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		return_expression = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_3(Nil,return_expression,Nil);
	    return VALUES_1(Qnil);
	}
    }
    else if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct))
	return compile2_expression_1(expression);
    else
	return VALUES_1(Qnil);
}

static Object Qcompile2_quantifier_or_aggregator;  /* compile2-quantifier-or-aggregator */

static Object Qcompile2_and_expression;  /* compile2-and-expression */

static Object Qab_or;              /* or */

static Object Qcompile2_or_expression;  /* compile2-or-expression */

static Object Qcompile2_not_expression;  /* compile2-not-expression */

static Object Qcompile2_if_expression;  /* compile2-if-expression */

static Object Qcompile2_comparison_operator_expression;  /* compile2-comparison-operator-expression */

static Object Qcompile2_name;      /* compile2-name */

/* COMPILE2-EXPRESSION-1-TOP */
Object compile2_expression_1_top(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, operator_1;

    x_note_fn_call(141,73);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    if (CONSP(temp)) {
	temp = ISVREF(expression_for_compilation,(SI_Long)1L);
	operator_1 = FIRST(temp);
	if (quantifier_or_aggregator_p(operator_1))
	    return compile2_top_level_expression_and_insert(expression_for_compilation,
		    Qcompile2_quantifier_or_aggregator);
	else if (logical_operator_p(operator_1)) {
	    if (EQ(operator_1,Qand))
		return compile2_top_level_expression_and_insert(expression_for_compilation,
			Qcompile2_and_expression);
	    else if (EQ(operator_1,Qab_or))
		return compile2_top_level_expression_and_insert(expression_for_compilation,
			Qcompile2_or_expression);
	    else if (EQ(operator_1,Qnot))
		return compile2_top_level_expression_and_insert(expression_for_compilation,
			Qcompile2_not_expression);
	    else
		return VALUES_1(Nil);
	}
	else if (if_operator_p(operator_1))
	    return compile2_top_level_expression_and_insert(expression_for_compilation,
		    Qcompile2_if_expression);
	else
	    return compile2_top_level_expression_and_insert(expression_for_compilation,
		    Qcompile2_comparison_operator_expression);
    }
    else
	return compile2_top_level_expression_and_insert(expression_for_compilation,
		Qcompile2_name);
}

static Object Qinform;             /* inform */

/* COMPILE2-ACTION */
Object compile2_action(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, operator_1, inside_action_iteration_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(141,74);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    operator_1 = FIRST(temp);
    inside_action_iteration_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Inside_action_iteration_p,Qinside_action_iteration_p,inside_action_iteration_p,
	    0);
      if (EQ(operator_1,Qinform))
	  result = compile2_inform(expression_for_compilation);
      else
	  result = compile2_action_according_to_template(expression_for_compilation,
		  lookup_action_template(operator_1));
    POP_SPECIAL();
    return result;
}

/* COMPILE2-TOP-LEVEL-EXPRESSION-AND-INSERT */
Object compile2_top_level_expression_and_insert(expression_for_compilation,
	    compilation_function)
    Object expression_for_compilation, compilation_function;
{
    Object temp, iteration_forms, expression_for_insertion, insertion_location;
    Object compiled_specific_expression;
    Object result;

    x_note_fn_call(141,75);
    temp = SYMBOL_FUNCTION(compilation_function);
    result = FUNCALL_1(temp,expression_for_compilation);
    MVS_3(result,iteration_forms,expression_for_insertion,insertion_location);
    compiled_specific_expression = 
	    insert_expressions_into_combined_iteration_forms(iteration_forms,
	    expression_for_insertion,insertion_location);
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = 
	    compiled_specific_expression;
    return VALUES_1(expression_for_compilation);
}

/* INSERT-EXPRESSIONS-INTO-COMBINED-ITERATION-FORMS */
Object insert_expressions_into_combined_iteration_forms(iteration_forms,
	    expression_for_insertion,insertion_location)
    Object iteration_forms, expression_for_insertion, insertion_location;
{
    x_note_fn_call(141,76);
    if (insertion_location) {
	insert_expression_into_for_structure_body(expression_for_insertion,
		insertion_location);
	return VALUES_1(iteration_forms);
    }
    else
	return VALUES_1(expression_for_insertion);
}

/* COMPILE2-IF-EXPRESSION */
Object compile2_if_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(141,77);
    return compile2_comparison_operator_expression(expression_for_compilation);
}

/* COMPILE-NON-PROVIDING-EXPRESSION */
Object compile_non_providing_expression(expression)
    Object expression;
{
    Object inside_action_iteration_p, iteration_forms;
    Object expression_for_insertion, insertion_location;
    Declare_special(1);
    Object result;

    x_note_fn_call(141,78);
    inside_action_iteration_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Inside_action_iteration_p,Qinside_action_iteration_p,inside_action_iteration_p,
	    0);
      result = compile2_expression(expression);
      MVS_3(result,iteration_forms,expression_for_insertion,
	      insertion_location);
      result = insert_expressions_into_combined_iteration_forms(iteration_forms,
	      expression_for_insertion,insertion_location);
    POP_SPECIAL();
    return result;
}

/* COMPILE2-PROVIDING-EXPRESSION-COLLECTING-ITERATION-FORMS */
Object compile2_providing_expression_collecting_iteration_forms(expression,
	    iteration_forms,insertion_locations)
    Object expression, iteration_forms, insertion_locations;
{
    Object iteration_form, expression_for_insertion, insertion_location;
    Object result;

    x_note_fn_call(141,79);
    result = compile2_expression(expression);
    MVS_3(result,iteration_form,expression_for_insertion,insertion_location);
    iteration_forms = phrase_cons(iteration_form,iteration_forms);
    insertion_locations = phrase_cons(insertion_location,insertion_locations);
    return VALUES_3(iteration_forms,expression_for_insertion,
	    insertion_locations);
}

/* NEST-LISTED-ITERATION-FORMS */
Object nest_listed_iteration_forms(iteration_forms,insertion_locations,
	    expression_to_insert)
    Object iteration_forms, insertion_locations, expression_to_insert;
{
    Object form_to_insert, iteration_form, ab_loop_list_, insertion_location;
    Object ab_loop_list__1;

    x_note_fn_call(141,80);
    form_to_insert = expression_to_insert;
    iteration_form = Nil;
    ab_loop_list_ = iteration_forms;
    insertion_location = Nil;
    ab_loop_list__1 = insertion_locations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    iteration_form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    insertion_location = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    form_to_insert = 
	    insert_expressions_into_combined_iteration_forms(iteration_form,
	    form_to_insert,insertion_location);
    goto next_loop;
  end_loop:
    return VALUES_1(form_to_insert);
    return VALUES_1(Qnil);
}

static Object Qdesignation;        /* designation */

/* COMPILE2-ACTION-ACCORDING-TO-TEMPLATE */
Object compile2_action_according_to_template(expression_for_compilation,
	    template_qm)
    Object expression_for_compilation, template_qm;
{
    Object compiled_specific_expression, iteration_forms, insertion_locations;
    Object rest_of_template, template_symbol, compiled_sub_form, sub_form;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    Object compiled_action_forms, action_to_be_inserted, svref_new_value;
    Object result;

    x_note_fn_call(141,81);
    compiled_specific_expression = ISVREF(expression_for_compilation,
	    (SI_Long)1L);
    iteration_forms = Nil;
    insertion_locations = Nil;
    rest_of_template = CDR(template_qm);
    template_symbol = template_qm ? CAR(rest_of_template) : Qdesignation;
    compiled_sub_form = Nil;
    sub_form = Nil;
    ab_loop_list_ = CDR(compiled_specific_expression);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_form = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(template_symbol,Qother))
	compiled_sub_form = sub_form;
    else if (EQ(template_symbol,Qshow_or_hide_argument_list)) {
	if (CONSP(sub_form))
	    temp = CAR(sub_form);
	else if (SIMPLE_VECTOR_P(sub_form) && EQ(ISVREF(sub_form,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		    {
	    temp = ISVREF(sub_form,(SI_Long)1L);
	    temp = CAR(temp);
	}
	else
	    temp = Qnil;
	if (EQ(temp,Qin)) {
	    result = compile2_providing_expression_collecting_iteration_forms(sub_form,
		    iteration_forms,insertion_locations);
	    MVS_3(result,iteration_forms,compiled_sub_form,
		    insertion_locations);
	}
	else
	    compiled_sub_form = sub_form;
    }
    else {
	result = compile2_providing_expression_collecting_iteration_forms(sub_form,
		iteration_forms,insertion_locations);
	MVS_3(result,iteration_forms,compiled_sub_form,insertion_locations);
    }
    if (template_qm) {
	temp = CDR(rest_of_template);
	if (SYMBOLP(temp))
	    template_symbol = CDR(rest_of_template);
	else {
	    rest_of_template = CDR(rest_of_template);
	    template_symbol = CAR(rest_of_template);
	}
    }
    else
	template_symbol = Qexpression;
    ab_loopvar__2 = phrase_cons(compiled_sub_form,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    compiled_action_forms = ab_loopvar_;
    goto end_1;
    compiled_action_forms = Qnil;
  end_1:;
    action_to_be_inserted = 
	    phrase_cons(FIRST(compiled_specific_expression),
	    compiled_action_forms);
    svref_new_value = nest_listed_iteration_forms(iteration_forms,
	    insertion_locations,action_to_be_inserted);
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = svref_new_value;
    return VALUES_1(expression_for_compilation);
}

/* COMPILE2-INFORM */
Object compile2_inform(expression_for_compilation)
    Object expression_for_compilation;
{
    Object compiled_specific_expression, designation_for_inform;
    Object expressions_for_inform, iteration_forms_for_inform_designation;
    Object expression_for_insertion_for_inform_designation;
    Object insertion_location_for_inform_designation;
    Object iteration_forms_for_inform_message;
    Object expression_for_insertion_for_inform_message;
    Object insertion_locations_for_inform_message, sub_expression;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object expression_for_insertion_for_inform_expressions;
    Object new_compiled_specific_expression;
    Object result;

    x_note_fn_call(141,82);
    compiled_specific_expression = ISVREF(expression_for_compilation,
	    (SI_Long)1L);
    designation_for_inform = SECOND(compiled_specific_expression);
    expressions_for_inform = CDDR(compiled_specific_expression);
    result = compile2_expression(designation_for_inform);
    MVS_3(result,iteration_forms_for_inform_designation,
	    expression_for_insertion_for_inform_designation,
	    insertion_location_for_inform_designation);
    result = compile2_inform_message_expression(CAR(expressions_for_inform));
    MVS_3(result,iteration_forms_for_inform_message,
	    expression_for_insertion_for_inform_message,
	    insertion_locations_for_inform_message);
    sub_expression = Nil;
    ab_loop_list_ = CDR(expressions_for_inform);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = 
	    phrase_cons(compile_non_providing_expression(sub_expression),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    expression_for_insertion_for_inform_expressions = ab_loopvar_;
    goto end_1;
    expression_for_insertion_for_inform_expressions = Qnil;
  end_1:;
    new_compiled_specific_expression = 
	    insert_expressions_into_combined_iteration_forms(iteration_forms_for_inform_designation,
	    nest_listed_iteration_forms(iteration_forms_for_inform_message,
	    insertion_locations_for_inform_message,phrase_cons(Qinform,
	    phrase_cons(expression_for_insertion_for_inform_designation,
	    phrase_cons(expression_for_insertion_for_inform_message,
	    expression_for_insertion_for_inform_expressions)))),
	    insertion_location_for_inform_designation);
    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = 
	    new_compiled_specific_expression;
    return VALUES_1(expression_for_compilation);
}

/* COMPILE2-INFORM-MESSAGE-EXPRESSION */
Object compile2_inform_message_expression(message_expression)
    Object message_expression;
{
    Object current_expression_for_insertion, iteration_forms;
    Object insertion_locations, string_or_expression, temp, ab_loop_list_;
    Object expression_for_insertion;
    Object result;

    x_note_fn_call(141,83);
    if (text_string_p(message_expression))
	return VALUES_3(Nil,message_expression,Nil);
    else {
	current_expression_for_insertion = phrase_cons(Qand,Nil);
	iteration_forms = Nil;
	insertion_locations = Nil;
	string_or_expression = Nil;
	temp = ISVREF(message_expression,(SI_Long)1L);
	ab_loop_list_ = CDR(temp);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	string_or_expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (text_string_p(string_or_expression))
	    current_expression_for_insertion = 
		    nconc2(current_expression_for_insertion,
		    phrase_cons(string_or_expression,Nil));
	else {
	    expression_for_insertion = Nil;
	    result = compile2_providing_expression_collecting_iteration_forms(string_or_expression,
		    iteration_forms,insertion_locations);
	    MVS_3(result,iteration_forms,expression_for_insertion,
		    insertion_locations);
	    current_expression_for_insertion = 
		    nconc2(current_expression_for_insertion,
		    phrase_cons(expression_for_insertion,Nil));
	}
	goto next_loop;
      end_loop:
	return VALUES_3(iteration_forms,current_expression_for_insertion,
		insertion_locations);
	return VALUES_1(Qnil);
    }
}

/* COMPILE2-EXPRESSION-1 */
Object compile2_expression_1(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, operator_1;

    x_note_fn_call(141,84);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    if (CONSP(temp)) {
	temp = ISVREF(expression_for_compilation,(SI_Long)1L);
	operator_1 = FIRST(temp);
	if (EQ(operator_1,Qquote))
	    return VALUES_1(expression_for_compilation);
	else if (quantifier_or_aggregator_p(operator_1))
	    return compile2_quantifier_or_aggregator(expression_for_compilation);
	else if (logical_operator_p(operator_1))
	    return compile2_logical_operator_expression(expression_for_compilation);
	else if (if_operator_p(operator_1))
	    return compile2_if_expression(expression_for_compilation);
	else
	    return compile2_comparison_operator_expression(expression_for_compilation);
    }
    else
	return compile2_name(expression_for_compilation);
}

/* COMPILE2-QUANTIFIER-OR-AGGREGATOR */
Object compile2_quantifier_or_aggregator(expression_for_compilation)
    Object expression_for_compilation;
{
    Object in_non_top_level_context_qm, old_compiled_specific_expression;
    Object compiled_aggregator_expression, scope;
    Object reference_structure_for_aggregator_scope;
    Object new_compiled_specific_expression;
    Declare_special(1);
    Object result;

    x_note_fn_call(141,85);
    in_non_top_level_context_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(In_non_top_level_context_qm,Qin_non_top_level_context_qm,in_non_top_level_context_qm,
	    0);
      old_compiled_specific_expression = ISVREF(expression_for_compilation,
	      (SI_Long)1L);
      compiled_aggregator_expression = 
	      compile_non_providing_expression(THIRD(old_compiled_specific_expression));
      scope = SECOND(old_compiled_specific_expression);
      reference_structure_for_aggregator_scope = 
	      get_relevent_reference_structure_for_aggregator_scope(scope);
      new_compiled_specific_expression = 
	      phrase_list_3(FIRST(old_compiled_specific_expression),scope,
	      compiled_aggregator_expression);
      if (memq_function(ISVREF(scope,(SI_Long)1L),
	      Local_names_not_associated_with_roles))
	  add_for_structure_to_non_context_binding_forms(make_for_structure_given_reference_structure(reference_structure_for_aggregator_scope));
      if (EQ(CAR(old_compiled_specific_expression),Qthere_exists_literal))
	  Reference_structures_originating_from_within_existence_predicate 
		  = phrase_cons(reference_structure_for_aggregator_scope,
		  Reference_structures_originating_from_within_existence_predicate);
      result = VALUES_3(Nil,new_compiled_specific_expression,Nil);
    POP_SPECIAL();
    return result;
}

static Object Qcombine_sub_expression_with_expression;  /* combine-sub-expression-with-expression */

/* COMPILE2-COMPARISON-OPERATOR-EXPRESSION */
Object compile2_comparison_operator_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, sub_expressions, operator_1, iteration_forms;
    Object insertion_location, new_compiled_specific_expression;
    Object sub_expression, ab_loop_list_;
    Object result;

    x_note_fn_call(141,86);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    sub_expressions = CDR(temp);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    operator_1 = CAR(temp);
    iteration_forms = Nil;
    insertion_location = Nil;
    new_compiled_specific_expression = phrase_cons(operator_1,Nil);
    sub_expression = Nil;
    ab_loop_list_ = sub_expressions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result = incorporate_iteration_forms_of_expression_and_sub_expression(iteration_forms,
	    new_compiled_specific_expression,insertion_location,
	    sub_expression,Qcombine_sub_expression_with_expression);
    MVS_3(result,iteration_forms,new_compiled_specific_expression,
	    insertion_location);
    goto next_loop;
  end_loop:;
    return VALUES_3(iteration_forms,new_compiled_specific_expression,
	    insertion_location);
}

DEFINE_VARIABLE_WITH_SYMBOL(Iteration_forms_for_embedded_expressions_qm, Qiteration_forms_for_embedded_expressions_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Insertion_location_for_embedded_expressions_qm, Qinsertion_location_for_embedded_expressions_qm);

static Object string_constant;     /* "\"any\" may only be used in a rule." */

/* COMPILE2-NAME */
Object compile2_name(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, anchor_reference_structure, iteration_forms;
    Object insertion_location, iteration_forms_for_embedded_expressions_qm;
    Object insertion_location_for_embedded_expressions_qm;
    Object previous_for_structure, for_structure;
    Object for_structure_binding_expression, for_structure_target_name;
    Object local_iteration_forms, local_insertion_location;
    Object reference_structure, reference_depends_on_existence_qm_1;
    Object in_line_optimizing_ok_qm, provides_binding_for_iteration_qm;
    Object provides_local_binding_qm, local_name_not_associated_with_role_qm;
    Object new_compiled_specific_expression, target_name;
    Declare_special(4);
    Object result;

    x_note_fn_call(141,87);
    if ( !TRUEP(ISVREF(expression_for_compilation,(SI_Long)3L))) {
	temp = ISVREF(expression_for_compilation,(SI_Long)1L);
	return VALUES_3(Nil,temp,Nil);
    }
    else {
	temp = ISVREF(expression_for_compilation,(SI_Long)3L);
	anchor_reference_structure = CAR(temp);
	iteration_forms = Nil;
	insertion_location = Nil;
	iteration_forms_for_embedded_expressions_qm = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Iteration_forms_for_embedded_expressions_qm,Qiteration_forms_for_embedded_expressions_qm,iteration_forms_for_embedded_expressions_qm,
		3);
	  insertion_location_for_embedded_expressions_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Insertion_location_for_embedded_expressions_qm,Qinsertion_location_for_embedded_expressions_qm,insertion_location_for_embedded_expressions_qm,
		  2);
	    previous_for_structure = Nil;
	    for_structure = Nil;
	    for_structure_binding_expression = Nil;
	    for_structure_target_name = Nil;
	    local_iteration_forms = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Local_iteration_forms,Qlocal_iteration_forms,local_iteration_forms,
		    1);
	      local_insertion_location = Nil;
	      PUSH_SPECIAL_WITH_SYMBOL(Local_insertion_location,Qlocal_insertion_location,local_insertion_location,
		      0);
		reference_structure = anchor_reference_structure;
		reference_depends_on_existence_qm_1 = Nil;
		in_line_optimizing_ok_qm = Nil;
		provides_binding_for_iteration_qm = Nil;
		provides_local_binding_qm = Nil;
		local_name_not_associated_with_role_qm = Nil;
	      next_loop:
		if ( !TRUEP(reference_structure))
		    goto end_loop;
		reference_depends_on_existence_qm_1 = 
			reference_depends_on_existence_qm(reference_structure);
		temp = reference_depends_on_existence_qm_1;
		if (temp);
		else
		    temp = In_non_top_level_context_qm;
		if (temp);
		else
		    temp = Allow_in_line_designations_qm;
		in_line_optimizing_ok_qm = temp;
		provides_binding_for_iteration_qm = 
			reference_structure_provides_binding_for_iteration_qm(reference_structure);
		provides_local_binding_qm =  
			!TRUEP(provides_binding_for_iteration_qm) ? 
			reference_structure_provides_local_binding_qm(reference_structure,
			in_line_optimizing_ok_qm) : Nil;
		local_name_not_associated_with_role_qm = 
			memq_function(ISVREF(reference_structure,
			(SI_Long)3L),Local_names_not_associated_with_roles);
		if ( !TRUEP(provides_binding_for_iteration_qm) &&  
			!TRUEP(provides_local_binding_qm) &&  
			!TRUEP(local_name_not_associated_with_role_qm)) {
		    result = build_optimized_reference_phrase(1,
			    reference_structure);
		    MVS_2(result,new_compiled_specific_expression,target_name);
		    if ( !TRUEP(in_line_optimizing_ok_qm) && 
			    CONSP(new_compiled_specific_expression)) {
			for_structure = 
				make_for_structure_for_optimized_path(new_compiled_specific_expression,
				target_name);
			if (previous_for_structure)
			    SVREF(previous_for_structure,FIX((SI_Long)2L)) 
				    = for_structure;
			else
			    iteration_forms = for_structure;
			insertion_location = for_structure;
			new_compiled_specific_expression = target_name;
		    }
		    SVREF(expression_for_compilation,FIX((SI_Long)1L)) = 
			    new_compiled_specific_expression;
		    result = return_values_from_compile2_name(new_compiled_specific_expression,
			    iteration_forms,insertion_location,
			    Iteration_forms_for_embedded_expressions_qm,
			    Insertion_location_for_embedded_expressions_qm);
		    goto end_1;
		}
		else if ( !(EQ(ISVREF(reference_structure,(SI_Long)1L),
			Needed_domain) || 
			reference_structure_for_global_symbol_p(reference_structure))) 
			    {
		    for_structure = 
			    make_for_structure_given_reference_structure(reference_structure);
		    if (reference_depends_on_existence_qm_1)
			add_for_structure_to_local_binding_forms(for_structure);
		    else if (local_name_not_associated_with_role_qm)
			add_for_structure_to_non_context_binding_forms(for_structure);
		    else if (compiling_action_p() || 
			    In_non_top_level_context_qm) {
			if (previous_for_structure)
			    SVREF(previous_for_structure,FIX((SI_Long)2L)) 
				    = for_structure;
			else
			    iteration_forms = for_structure;
			previous_for_structure = for_structure;
			insertion_location = for_structure;
		    }
		    else if (provides_binding_for_iteration_qm) {
			if ( !BOUNDP(Qcontext_iteration_forms))
			    compiler_error(1,string_constant);
			else
			    Context_iteration_forms = 
				    nconc2(Context_iteration_forms,
				    phrase_cons(for_structure,Nil));
		    }
		    else if ( 
			    !TRUEP(reference_structure_itself_provides_local_binding_qm(reference_structure))) 
				{
			result = add_to_for_structure_binding_expression(reference_structure,
				for_structure_binding_expression);
			MVS_2(result,for_structure_binding_expression,
				for_structure_target_name);
		    }
		    else {
			if (for_structure_binding_expression) {
			    result = add_to_for_structure_binding_expression(reference_structure,
				    for_structure_binding_expression);
			    MVS_2(result,for_structure_binding_expression,
				    for_structure_target_name);
			    for_structure = 
				    make_for_structure_for_optimized_path(for_structure_binding_expression,
				    for_structure_target_name);
			}
			if (Compiling_expression_p) {
			    if (previous_for_structure)
				SVREF(previous_for_structure,
					FIX((SI_Long)2L)) = for_structure;
			    else
				iteration_forms = for_structure;
			    previous_for_structure = for_structure;
			    insertion_location = for_structure;
			}
			else
			    add_for_structure_to_non_context_binding_forms(for_structure);
		    }
		}
		if (ISVREF(reference_structure,(SI_Long)5L)) {
		    temp = ISVREF(reference_structure,(SI_Long)5L);
		    reference_structure = CAR(temp);
		}
		else
		    reference_structure = Nil;
		goto next_loop;
	      end_loop:
		result = return_values_from_compile2_name(ISVREF(expression_for_compilation,
			(SI_Long)1L),iteration_forms,insertion_location,
			Iteration_forms_for_embedded_expressions_qm,
			Insertion_location_for_embedded_expressions_qm);
		goto end_1;
		result = VALUES_1(Qnil);
	      end_1:;
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

static Object Qsymbolic_variable;  /* symbolic-variable */

static Object Qc2;                 /* c2 */

/* REFERENCE-DEPENDS-ON-EXISTENCE? */
Object reference_depends_on_existence_qm(reference_structure)
    Object reference_structure;
{
    Object existence_origin_reference_structure, ab_loop_list_;
    Object existence_origin_reference_structure_in_top_level_tree;
    Object reference_structure_to_check;

    x_note_fn_call(141,88);
    if ( !(Nil && EQ(ISVREF(reference_structure,(SI_Long)2L),
	    Qsymbolic_variable) && EQ(ISVREF(reference_structure,
	    (SI_Long)1L),Qc2))) {
	existence_origin_reference_structure = Nil;
	ab_loop_list_ = 
		Reference_structures_originating_from_within_existence_predicate;
	existence_origin_reference_structure_in_top_level_tree = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	existence_origin_reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	existence_origin_reference_structure_in_top_level_tree = 
		get_copy_of_reference_structure_in_highest_level_reference_tree(existence_origin_reference_structure);
	reference_structure_to_check = 
		get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure);
      next_loop_1:
	if ( !TRUEP(reference_structure_to_check))
	    goto end_loop_1;
	if (EQ(reference_structure_to_check,
		existence_origin_reference_structure_in_top_level_tree))
	    return VALUES_1(T);
	reference_structure_to_check = ISVREF(reference_structure_to_check,
		(SI_Long)4L);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* COMPILE2-EMBEDDED-EXPRESSION */
Object compile2_embedded_expression(embedded_expression_qm)
    Object embedded_expression_qm;
{
    Object iteration_forms, compiled_specific_embedded_expression_qm;
    Object insertion_location;
    Object result;

    x_note_fn_call(141,89);
    if (embedded_expression_qm) {
	result = compile2_expression(embedded_expression_qm);
	MVS_3(result,iteration_forms,
		compiled_specific_embedded_expression_qm,insertion_location);
	result = combine_iteration_forms_with_those_of_sub_expression(Iteration_forms_for_embedded_expressions_qm,
		Insertion_location_for_embedded_expressions_qm,
		iteration_forms,insertion_location);
	MVS_2(result,Iteration_forms_for_embedded_expressions_qm,
		Insertion_location_for_embedded_expressions_qm);
	return VALUES_1(compiled_specific_embedded_expression_qm);
    }
    else
	return VALUES_1(Nil);
}

/* RETURN-VALUES-FROM-COMPILE2-NAME */
Object return_values_from_compile2_name(expression,iteration_forms,
	    insertion_location,iteration_forms_for_embedded_expressions_qm,
	    insertion_location_for_embedded_expressions_qm)
    Object expression, iteration_forms, insertion_location;
    Object iteration_forms_for_embedded_expressions_qm;
    Object insertion_location_for_embedded_expressions_qm;
{
    Declare_special(2);
    Object result;

    x_note_fn_call(141,90);
    PUSH_SPECIAL_WITH_SYMBOL(Insertion_location_for_embedded_expressions_qm,Qinsertion_location_for_embedded_expressions_qm,insertion_location_for_embedded_expressions_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Iteration_forms_for_embedded_expressions_qm,Qiteration_forms_for_embedded_expressions_qm,iteration_forms_for_embedded_expressions_qm,
	      0);
	expression = 
		insert_expressions_into_combined_iteration_forms(Local_iteration_forms,
		expression,Local_insertion_location);
	result = combine_iteration_forms_with_those_of_sub_expression(iteration_forms,
		insertion_location,
		Iteration_forms_for_embedded_expressions_qm,
		Insertion_location_for_embedded_expressions_qm);
	MVS_2(result,iteration_forms,insertion_location);
	result = VALUES_3(iteration_forms,expression,insertion_location);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* COMBINE-ITERATION-FORMS-WITH-THOSE-OF-SUB-EXPRESSION */
Object combine_iteration_forms_with_those_of_sub_expression(iteration_forms,
	    insertion_location,iteration_forms_for_sub_expression,
	    insertion_location_for_sub_expression)
    Object iteration_forms, insertion_location;
    Object iteration_forms_for_sub_expression;
    Object insertion_location_for_sub_expression;
{
    x_note_fn_call(141,91);
    if (iteration_forms) {
	if (iteration_forms_for_sub_expression)
	    insert_expression_into_for_structure_body(iteration_forms_for_sub_expression,
		    insertion_location);
    }
    else
	iteration_forms = iteration_forms_for_sub_expression;
    if (iteration_forms_for_sub_expression)
	insertion_location = insertion_location_for_sub_expression;
    return VALUES_2(iteration_forms,insertion_location);
}

/* INCORPORATE-ITERATION-FORMS-OF-EXPRESSION-AND-SUB-EXPRESSION */
Object incorporate_iteration_forms_of_expression_and_sub_expression(iteration_forms,
	    expression,insertion_location,sub_expression,
	    function_for_combining_specific_expression_and_sub_expression)
    Object iteration_forms, expression, insertion_location, sub_expression;
    Object function_for_combining_specific_expression_and_sub_expression;
{
    Object iteration_forms_for_sub_expression, expression_for_insertion;
    Object insertion_location_for_sub_expression;
    Object result;

    x_note_fn_call(141,92);
    if (SIMPLE_VECTOR_P(sub_expression) && EQ(ISVREF(sub_expression,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct)) 
		{
	result = compile2_expression(sub_expression);
	MVS_3(result,iteration_forms_for_sub_expression,
		expression_for_insertion,
		insertion_location_for_sub_expression);
	expression = 
		FUNCALL_2(function_for_combining_specific_expression_and_sub_expression,
		expression,expression_for_insertion);
	result = combine_iteration_forms_with_those_of_sub_expression(iteration_forms,
		insertion_location,iteration_forms_for_sub_expression,
		insertion_location_for_sub_expression);
	MVS_2(result,iteration_forms,insertion_location);
    }
    else
	expression = 
		FUNCALL_2(function_for_combining_specific_expression_and_sub_expression,
		expression,sub_expression);
    return VALUES_3(iteration_forms,expression,insertion_location);
}

/* COMBINE-SUB-EXPRESSION-WITH-EXPRESSION */
Object combine_sub_expression_with_expression(specific_expression,
	    specific_sub_expression)
    Object specific_expression, specific_sub_expression;
{
    x_note_fn_call(141,93);
    return VALUES_1(nconc2(specific_expression,
	    phrase_cons(specific_sub_expression,Nil)));
}

/* ADD-FOR-STRUCTURE-TO-LOCAL-BINDING-FORMS */
Object add_for_structure_to_local_binding_forms(for_structure)
    Object for_structure;
{
    Object temp;
    Object result;

    x_note_fn_call(141,94);
    result = combine_iteration_forms_with_those_of_sub_expression(Local_iteration_forms,
	    Local_insertion_location,for_structure,for_structure);
    temp = result;
    MVS_2(result,Local_iteration_forms,Local_insertion_location);
    return VALUES_1(temp);
}

/* ADD-FOR-STRUCTURE-TO-NON-CONTEXT-BINDING-FORMS */
Object add_for_structure_to_non_context_binding_forms(for_structure)
    Object for_structure;
{
    x_note_fn_call(141,95);
    Non_context_top_level_binding_forms = 
	    nconc2(Non_context_top_level_binding_forms,
	    phrase_cons(for_structure,Nil));
    return VALUES_1(Non_context_top_level_binding_forms);
}

/* COMPILING-ACTION-P */
Object compiling_action_p()
{
    x_note_fn_call(141,96);
    if (Compiling_rule_p)
	return VALUES_1( !TRUEP(Compiling_antecedent_p) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* COMPILE2-DESIGNATIONS-FROM-EXPLICIT-ITERATION-FORMS */
Object compile2_designations_from_explicit_iteration_forms()
{
    Object designation, ab_loop_list_, temp, anchor_reference_structure;
    Object for_structure, reference_structure;

    x_note_fn_call(141,97);
    designation = Nil;
    ab_loop_list_ = Designations_from_explicit_iteration_forms;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    designation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ISVREF(designation,(SI_Long)3L)) {
	temp = ISVREF(designation,(SI_Long)3L);
	anchor_reference_structure = CAR(temp);
	for_structure = Nil;
	reference_structure = anchor_reference_structure;
      next_loop_1:
	if ( !TRUEP(reference_structure))
	    goto end_loop_1;
	if ( !EQ(ISVREF(reference_structure,(SI_Long)1L),Needed_domain) && 
		 
		!TRUEP(reference_structure_for_global_symbol_p(reference_structure))) 
		    {
	    for_structure = 
		    make_for_structure_given_reference_structure(reference_structure);
	    if (reference_structure_provides_binding_for_iteration_qm(reference_structure))
		Context_iteration_forms = nconc2(Context_iteration_forms,
			phrase_cons(for_structure,Nil));
	    else
		add_for_structure_to_non_context_binding_forms(for_structure);
	}
	if (ISVREF(reference_structure,(SI_Long)5L)) {
	    temp = ISVREF(reference_structure,(SI_Long)5L);
	    reference_structure = CAR(temp);
	}
	else
	    reference_structure = Nil;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REFERENCE-STRUCTURE-PROVIDES-BINDING-FOR-ITERATION? */
Object reference_structure_provides_binding_for_iteration_qm(reference_structure)
    Object reference_structure;
{
    x_note_fn_call(141,98);
    return reference_tree_has_iteration_qm(get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure));
}

static Object list_constant_5;     /* # */

/* REFERENCE-TREE-HAS-ITERATION? */
Object reference_tree_has_iteration_qm(reference_structure)
    Object reference_structure;
{
    Object temp, needing_reference_structure, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(141,99);
    temp = memq_function(ISVREF(reference_structure,(SI_Long)6L),
	    list_constant_5);
    if (temp)
	return VALUES_1(temp);
    else {
	needing_reference_structure = Nil;
	ab_loop_list_ = ISVREF(reference_structure,(SI_Long)5L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	needing_reference_structure = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = 
		reference_tree_has_iteration_qm(needing_reference_structure);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* REFERENCE-STRUCTURE-PROVIDES-LOCAL-BINDING? */
Object reference_structure_provides_local_binding_qm(reference_structure,
	    in_line_optimizing_ok_qm)
    Object reference_structure, in_line_optimizing_ok_qm;
{
    Object temp, further_reference_structures_for_binding_qm;
    Object source_specified_name;

    x_note_fn_call(141,100);
    temp = 
	    reference_structure_provides_external_references_qm(reference_structure);
    if (temp);
    else
	temp =  !TRUEP(simple_role_p(ISVREF(reference_structure,
		(SI_Long)3L))) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	if (ISVREF(reference_structure,(SI_Long)5L)) {
	    temp = ISVREF(reference_structure,(SI_Long)5L);
	    further_reference_structures_for_binding_qm = 
		    reference_structure_provides_local_binding_qm(CAR(temp),
		    in_line_optimizing_ok_qm);
	}
	else
	    further_reference_structures_for_binding_qm = Nil;
	if ( !TRUEP(further_reference_structures_for_binding_qm) && 
		in_line_optimizing_ok_qm) {
	    source_specified_name = 
		    get_name_provided_by_role(ISVREF(reference_structure,
		    (SI_Long)3L));
	    if ( !EQ(ISVREF(reference_structure,(SI_Long)2L),
		    source_specified_name))
		replace_compiler_generated_local_name_with_name_from_source(reference_structure,
			source_specified_name);
	}
	return VALUES_1(further_reference_structures_for_binding_qm);
    }
}

/* REFERENCE-STRUCTURE-ITSELF-PROVIDES-LOCAL-BINDING? */
Object reference_structure_itself_provides_local_binding_qm(reference_structure)
    Object reference_structure;
{
    Object temp, needing_reference_structures_in_top;

    x_note_fn_call(141,101);
    temp =  !TRUEP(simple_role_p(ISVREF(reference_structure,(SI_Long)3L))) 
	    ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	needing_reference_structures_in_top = 
		ISVREF(get_copy_of_reference_structure_in_highest_level_reference_tree(reference_structure),
		(SI_Long)5L);
	temp = CDR(needing_reference_structures_in_top);
	if (temp)
	    return VALUES_1(temp);
	else
	    return VALUES_1( 
		    !EQ(length(needing_reference_structures_in_top),
		    length(ISVREF(reference_structure,(SI_Long)5L))) ? T : 
		    Nil);
    }
}

static Object Qreplace_compiler_generated_local_name_1;  /* replace-compiler-generated-local-name-1 */

/* REPLACE-COMPILER-GENERATED-LOCAL-NAME-WITH-NAME-FROM-SOURCE */
Object replace_compiler_generated_local_name_with_name_from_source(reference_structure,
	    source_specified_name)
    Object reference_structure, source_specified_name;
{
    x_note_fn_call(141,102);
    return change_reference_structures_at_all_higher_levels(reference_structure,
	    Qreplace_compiler_generated_local_name_1,source_specified_name);
}

/* REPLACE-COMPILER-GENERATED-LOCAL-NAME-1 */
Object replace_compiler_generated_local_name_1(reference_structure,
	    source_specified_name)
    Object reference_structure, source_specified_name;
{
    x_note_fn_call(141,103);
    return VALUES_1(SVREF(reference_structure,FIX((SI_Long)2L)) = 
	    source_specified_name);
}

/* GET-NEW-ROLE-GIVEN-ROLE-AND-LOCAL-NAME */
Object get_new_role_given_role_and_local_name(role,local_name)
    Object role, local_name;
{
    x_note_fn_call(141,104);
    if (EQ(local_name,get_name_provided_by_role(role)))
	return VALUES_1(role);
    else if (simple_role_p(role))
	return phrase_cons(role,local_name);
    else
	return phrase_cons(CAR(role),local_name);
}

/* MAKE-FOR-STRUCTURE-GIVEN-REFERENCE-STRUCTURE */
Object make_for_structure_given_reference_structure(reference_structure)
    Object reference_structure;
{
    Object for_structure, quantifier, reference_structure_role_and_local_name;
    Object for_structure_role_and_local_name, domain_name_needed;
    Object svref_new_value;

    x_note_fn_call(141,105);
    if ( !EQ(ISVREF(reference_structure,(SI_Long)3L),Focus_range)) {
	for_structure = make_compilation_reclaimable_for_structure();
	quantifier = ISVREF(reference_structure,(SI_Long)6L);
	reference_structure_role_and_local_name = 
		ISVREF(reference_structure,(SI_Long)3L);
	for_structure_role_and_local_name = 
		get_new_role_given_role_and_local_name(reference_structure_role_and_local_name,
		ISVREF(reference_structure,(SI_Long)2L));
	domain_name_needed = ISVREF(reference_structure,(SI_Long)1L);
	if (Inside_action_iteration_p)
	    SVREF(for_structure,FIX((SI_Long)3L)) = T;
	svref_new_value = 
		generate_designation_with_embedded_expression(quantifier,
		for_structure_role_and_local_name,domain_name_needed,
		reference_structure);
	SVREF(for_structure,FIX((SI_Long)1L)) = svref_new_value;
	return VALUES_1(for_structure);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-FOR-STRUCTURE-FOR-OPTIMIZED-PATH */
Object make_for_structure_for_optimized_path(optimized_path,target_name)
    Object optimized_path, target_name;
{
    Object for_structure;

    x_note_fn_call(141,106);
    for_structure = make_compilation_reclaimable_for_structure();
    if (Inside_action_iteration_p)
	SVREF(for_structure,FIX((SI_Long)3L)) = T;
    SVREF(for_structure,FIX((SI_Long)1L)) = optimized_path;
    SVREF(for_structure,FIX((SI_Long)4L)) = target_name;
    return VALUES_1(for_structure);
}

/* GENERATE-DESIGNATION-WITH-EMBEDDED-EXPRESSION */
Object generate_designation_with_embedded_expression(quantifier,role,
	    domain,reference_structure)
    Object quantifier, role, domain, reference_structure;
{
    Object compiled_embedded_expression_qm;

    x_note_fn_call(141,107);
    compiled_embedded_expression_qm = 
	    compile2_embedded_expression(ISVREF(reference_structure,
	    (SI_Long)11L));
    return phrase_cons(quantifier,phrase_cons(role,phrase_cons(domain,
	    compiled_embedded_expression_qm ? 
	    phrase_cons(compiled_embedded_expression_qm,Nil) : Nil)));
}

/* BUILD-OPTIMIZED-REFERENCE-PHRASE */
Object build_optimized_reference_phrase varargs_1(int, n)
{
    Object reference_structure;
    Object dont_check_needing_reference_structures_qm, domain_name_needed;
    Object temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(141,108);
    INIT_ARGS_nonrelocating();
    reference_structure = REQUIRED_ARG_nonrelocating();
    dont_check_needing_reference_structures_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    domain_name_needed = ISVREF(reference_structure,(SI_Long)1L);
    if ( !TRUEP(ISVREF(reference_structure,(SI_Long)5L))) {
	if ( !EQ(ISVREF(reference_structure,(SI_Long)2L),Focus_range)) {
	    if (reference_structure_for_global_symbol_p(reference_structure) 
		    || EQ(domain_name_needed,Needed_domain)) {
		temp = ISVREF(reference_structure,(SI_Long)2L);
		temp_1 = ISVREF(reference_structure,(SI_Long)2L);
		return VALUES_2(temp,temp_1);
	    }
	    else if (rs_for_two_element_designation_with_non_atomic_role_p(reference_structure)) 
			{
		temp = phrase_list_2(Qthe,ISVREF(reference_structure,
			(SI_Long)3L));
		temp_1 = ISVREF(reference_structure,(SI_Long)2L);
		return VALUES_2(temp,temp_1);
	    }
	    else {
		temp = generate_designation_with_embedded_expression(Qthe,
			ISVREF(reference_structure,(SI_Long)3L),
			domain_name_needed,reference_structure);
		temp_1 = ISVREF(reference_structure,(SI_Long)2L);
		return VALUES_2(temp,temp_1);
	    }
	}
	else
	    return VALUES_2(domain_name_needed,domain_name_needed);
    }
    else
	return build_optimized_reference_phrase_rec(reference_structure,
		Nil,dont_check_needing_reference_structures_qm);
}

/* BUILD-OPTIMIZED-REFERENCE-PHRASE-REC */
Object build_optimized_reference_phrase_rec(reference_structure,
	    phrase_so_far,dont_check_needing_reference_structures_qm)
    Object reference_structure, phrase_so_far;
    Object dont_check_needing_reference_structures_qm;
{
    Object new_role, domain_name_needed, new_phrase, temp;

    x_note_fn_call(141,109);
    new_role = ISVREF(reference_structure,(SI_Long)3L);
    domain_name_needed = ISVREF(reference_structure,(SI_Long)1L);
    if ( !TRUEP(ISVREF(reference_structure,(SI_Long)4L))) {
	if (EQ(domain_name_needed,Needed_domain))
	    new_phrase = new_role;
	else if ( !EQ(domain_name_needed,Global_domain) &&  
		!EQ(ISVREF(reference_structure,(SI_Long)2L),Focus_range))
	    new_phrase = phrase_list_3(Qthe,new_role,domain_name_needed);
	else if (rs_for_two_element_designation_with_non_atomic_role_p(reference_structure))
	    new_phrase = phrase_list_2(Qthe,new_role);
	else
	    new_phrase = Qnil;
    }
    else {
	temp = phrase_so_far;
	if (temp);
	else
	    temp = domain_name_needed;
	new_phrase = generate_designation_with_embedded_expression(Qthe,
		new_role,temp,reference_structure);
    }
    if ( !TRUEP(dont_check_needing_reference_structures_qm) && 
	    ISVREF(reference_structure,(SI_Long)5L)) {
	temp = ISVREF(reference_structure,(SI_Long)5L);
	return build_optimized_reference_phrase_rec(CAR(temp),new_phrase,
		dont_check_needing_reference_structures_qm);
    }
    else {
	temp = ISVREF(reference_structure,(SI_Long)2L);
	return VALUES_2(new_phrase,temp);
    }
}

/* ADD-TO-FOR-STRUCTURE-BINDING-EXPRESSION */
Object add_to_for_structure_binding_expression(reference_structure,
	    for_structure_binding_expression)
    Object reference_structure, for_structure_binding_expression;
{
    x_note_fn_call(141,110);
    if ( !TRUEP(for_structure_binding_expression))
	return build_optimized_reference_phrase(2,reference_structure,T);
    else
	return build_optimized_reference_phrase_rec(reference_structure,
		for_structure_binding_expression,T);
}

/* COMPILE2-LOGICAL-OPERATOR-EXPRESSION */
Object compile2_logical_operator_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    Object temp, operator_1;

    x_note_fn_call(141,111);
    temp = ISVREF(expression_for_compilation,(SI_Long)1L);
    operator_1 = FIRST(temp);
    if (EQ(operator_1,Qand))
	return compile2_and_expression(expression_for_compilation);
    else if (EQ(operator_1,Qab_or))
	return compile2_or_expression(expression_for_compilation);
    else if (EQ(operator_1,Qnot))
	return compile2_not_expression(expression_for_compilation);
    else
	return VALUES_1(Nil);
}

/* COMPILE2-AND-EXPRESSION */
Object compile2_and_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(141,112);
    return compile2_decoupled_and(expression_for_compilation);
}

/* COMPILE2-DECOUPLED-AND */
Object compile2_decoupled_and(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(141,113);
    return compile2_comparison_operator_expression(expression_for_compilation);
}

/* COMPILE2-OR-EXPRESSION */
Object compile2_or_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(141,114);
    return compile2_comparison_operator_expression(expression_for_compilation);
}

/* COMPILE2-NOT-EXPRESSION */
Object compile2_not_expression(expression_for_compilation)
    Object expression_for_compilation;
{
    x_note_fn_call(141,115);
    return compile2_comparison_operator_expression(expression_for_compilation);
}

/* INSERT-EXPRESSION-INTO-FOR-STRUCTURE-BODY */
Object insert_expression_into_for_structure_body(expression_to_be_inserted,
	    for_structure)
    Object expression_to_be_inserted, for_structure;
{
    x_note_fn_call(141,116);
    return VALUES_1(SVREF(for_structure,FIX((SI_Long)2L)) = 
	    expression_to_be_inserted);
}

static Object Qcompile3_expression;  /* compile3-expression */

/* COMPILE3-RULE */
Object compile3_rule(compiled_antecedent_2,compiled_consequent_2,
	    compiling_with_focus_qm,rule_keyword)
    Object compiled_antecedent_2, compiled_consequent_2;
    Object compiling_with_focus_qm, rule_keyword;
{
    Object inverse_context, for_structure, ab_loop_list_, compiled_iterator;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, forward_context;
    Object rule_context, compiled_antecedent_3, compiled_consequent_3;
    Object rule_body;
    Declare_special(1);
    Object result;

    x_note_fn_call(141,117);
    PUSH_SPECIAL_WITH_SYMBOL(Compiled_consequent_2,Qcompiled_consequent_2,compiled_consequent_2,
	    0);
      inverse_context = generate_inverse_context_from_inverse_reference_path();
      for_structure = Nil;
      ab_loop_list_ = Context_iteration_forms;
      compiled_iterator = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      for_structure = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      compiled_iterator = compile_forward_context_iterator(for_structure);
      ab_loopvar__2 = compiled_iterator ? phrase_cons(compiled_iterator,
	      Nil) : Nil;
      if (ab_loopvar__2) {
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = last(ab_loopvar__2,_);
      }
      goto next_loop;
    end_loop:
      forward_context = ab_loopvar_;
      goto end_1;
      forward_context = Qnil;
    end_1:;
      rule_context = nconc2(inverse_context,forward_context);
      compiled_antecedent_3 = Nil;
      compiled_consequent_3 = Nil;
      rule_body = T;
      if ( !TRUEP(compiling_with_focus_qm)) {
	  compiled_antecedent_3 = compile3_expression(compiled_antecedent_2);
	  compiled_consequent_3 = compile_consequent(Compiled_consequent_2,
		  Qcompile3_expression);
	  rule_body = phrase_list_3(rule_keyword,compiled_antecedent_3,
		  compiled_consequent_3);
	  if (Non_context_top_level_binding_forms)
	      rule_body = 
		      wrap_non_context_top_level_binding_forms(rule_body,Nil);
	  if ( ! !TRUEP(Assignment_section_forms))
	      rule_body = add_or_use_rule_let_section(rule_body);
      }
      result = VALUES_2(rule_context,rule_body);
    POP_SPECIAL();
    return result;
}

static Object Qrole_server;        /* role-server */

static Object Qthis_workspace;     /* this-workspace */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qthis_rule;          /* this-rule */

static Object Qrule;               /* rule */

/* INVERSE-REFERENCE-STRUCTURE-CONTAINS-THIS-RULE-NOR-THIS-WORKSPACE */
Object inverse_reference_structure_contains_this_rule_nor_this_workspace(reference_structure)
    Object reference_structure;
{
    Object role, temp;
    char temp_1;

    x_note_fn_call(141,118);
    role = 
	    get_new_role_given_role_and_local_name(ISVREF(reference_structure,
	    (SI_Long)3L),ISVREF(reference_structure,(SI_Long)2L));
    if (CONSP(role)) {
	temp = CDR(role);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = CDDR(role);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ? EQ(CAR(role),Qrole_server) : TRUEP(Nil)) {
	temp = EQ(CADR(role),Qthis_workspace) ? (EQ(CADDR(role),
		Qkb_workspace) ? T : Nil) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if (EQ(CADR(role),Qthis_rule))
	    return VALUES_1(EQ(CADDR(role),Qrule) ? T : Nil);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qthe_inverse_no_bind;  /* the-inverse-no-bind */

static Object Qthe_inverse;        /* the-inverse */

static Object Qany_inverse;        /* any-inverse */

/* GENERATE-INVERSE-CONTEXT-FROM-INVERSE-REFERENCE-PATH */
Object generate_inverse_context_from_inverse_reference_path()
{
    Object short_designation, domain_binding, temp, reference_structure;
    Object next_reference_structure, forward_quantifier, role, range_binding;
    Object number_left_to_not_bind, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, quantifier_for_short_designation;
    Object class_or_role_for_short_designation;
    Object local_name_provided_by_next_reference_structure, gensymed_symbol;
    Object gensymed_symbol_1, car_new_value;

    x_note_fn_call(141,119);
    short_designation = Nil;
    domain_binding = Nil;
    if (Pattern_checking_inverse_references) {
	temp = ISVREF(Pattern_checking_inverse_references,(SI_Long)5L);
	reference_structure = CAR(temp);
    }
    else
	reference_structure = Nil;
    next_reference_structure = Nil;
    forward_quantifier = Nil;
    role = Nil;
    range_binding = Nil;
    number_left_to_not_bind = Number_of_no_binds;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(reference_structure) || 
	    inverse_reference_structure_is_global_end_qm(reference_structure))
	goto end_loop;
    temp = ISVREF(reference_structure,(SI_Long)5L);
    next_reference_structure = CAR(temp);
    forward_quantifier = ISVREF(reference_structure,(SI_Long)7L);
    role = 
	    get_new_role_given_role_and_local_name(ISVREF(reference_structure,
	    (SI_Long)3L),ISVREF(reference_structure,(SI_Long)2L));
    range_binding = get_name_provided_by_role(role);
    if ( !TRUEP(ab_loop_iter_flag_))
	number_left_to_not_bind = FIXNUM_SUB1(number_left_to_not_bind);
    if ( 
	    !(inverse_reference_structure_is_global_end_qm(next_reference_structure) 
	    && 
	    inverse_reference_structure_for_global_symbol_p(next_reference_structure) 
	    &&  
	    !TRUEP(inverse_reference_structure_contains_this_rule_nor_this_workspace(next_reference_structure)))) 
		{
	quantifier_for_short_designation = ISVREF(next_reference_structure,
		(SI_Long)7L);
	class_or_role_for_short_designation = 
		rs_for_two_element_designation_with_non_atomic_role_p(next_reference_structure) 
		? simple_role_of_role(ISVREF(next_reference_structure,
		(SI_Long)3L)) : 
		atomic_naming_element_of_role(ISVREF(next_reference_structure,
		(SI_Long)3L));
	local_name_provided_by_next_reference_structure = 
		ISVREF(next_reference_structure,(SI_Long)2L);
	short_designation = phrase_list_2(quantifier_for_short_designation,
		class_or_role_for_short_designation);
	domain_binding = local_name_provided_by_next_reference_structure;
    }
    else {
	short_designation = ISVREF(reference_structure,(SI_Long)1L);
	domain_binding = short_designation;
    }
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = EQ(forward_quantifier,Qthe) ? 
	    (IFIX(number_left_to_not_bind) > (SI_Long)0L ? 
	    Qthe_inverse_no_bind : Qthe_inverse) : Qany_inverse;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = range_binding;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = simple_role_of_role(role);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = short_designation;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = domain_binding;
    ab_loopvar__2 = phrase_cons(gensymed_symbol,Nil);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    ab_loop_iter_flag_ = Nil;
    reference_structure = next_reference_structure;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qrule_let;           /* rule-let */

static Object Qcall_procedure;     /* call-procedure */

/* ADD-OR-USE-RULE-LET-SECTION */
Object add_or_use_rule_let_section(rule_body)
    Object rule_body;
{
    Object using_expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, temp_1, temp_2, new_args;

    x_note_fn_call(141,120);
    if (EQ(CAR(rule_body),Qrule_let)) {
	using_expression = Nil;
	ab_loop_list_ = Assignment_section_forms;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	using_expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = THIRD(using_expression);
	temp_1 = LISTP(temp) ? FOURTH(using_expression) : 
		THIRD(using_expression);
	temp_2 = SECOND(using_expression);
	temp = THIRD(using_expression);
	ab_loopvar__2 = phrase_list_2(temp_1,phrase_list_3(Qcall_procedure,
		temp_2,LISTP(temp) ? THIRD(using_expression) : Qnil));
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	new_args = phrase_cons(temp,Nil);
	temp = nconc2(new_args,SECOND(rule_body));
	return phrase_list_3(Qrule_let,temp,THIRD(rule_body));
    }
    else {
	using_expression = Nil;
	ab_loop_list_ = Assignment_section_forms;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	using_expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = THIRD(using_expression);
	temp_1 = LISTP(temp) ? FOURTH(using_expression) : 
		THIRD(using_expression);
	temp_2 = SECOND(using_expression);
	temp = THIRD(using_expression);
	ab_loopvar__2 = phrase_cons(phrase_list_2(temp_1,
		phrase_list_3(Qcall_procedure,temp_2,LISTP(temp) ? 
		THIRD(using_expression) : Qnil)),Nil);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_2;
	temp = Qnil;
      end_2:;
	return phrase_list_3(Qrule_let,temp,rule_body);
    }
}

static Object Qab_let;             /* let */

/* WRAP-NON-CONTEXT-TOP-LEVEL-BINDING-FORMS */
Object wrap_non_context_top_level_binding_forms(rule_or_expression_body,
	    use_let_qm)
    Object rule_or_expression_body, use_let_qm;
{
    Object for_structure, ab_loop_list_, scope, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, role, domain_list, domain, name_to_be_bound, temp;
    Object temp_1, arg_domain, ab_loop_list__1, ab_loopvar__3, ab_loopvar__4;

    x_note_fn_call(141,121);
    for_structure = Nil;
    ab_loop_list_ = Non_context_top_level_binding_forms;
    scope = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    for_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    scope = ISVREF(for_structure,(SI_Long)1L);
    if (valid_scope_p(scope)) {
	role = SECOND(scope);
	domain_list = CDDR(scope);
	domain = CAR(domain_list);
	name_to_be_bound = get_name_provided_by_role(role);
	if (memq_function(name_to_be_bound,
		Local_names_not_associated_with_roles))
	    temp = Nil;
	else if (EQ(domain,Global_domain))
	    temp = phrase_list_2(Qthe,simple_role_of_role(role));
	else {
	    temp_1 = simple_role_of_role(role);
	    arg_domain = Nil;
	    ab_loop_list__1 = domain_list;
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    arg_domain = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loopvar__4 = 
		    phrase_cons(copy_designation_dropping_local_names(arg_domain),
		    Nil);
	    if (ab_loopvar__3)
		M_CDR(ab_loopvar__3) = ab_loopvar__4;
	    else
		ab_loopvar__2 = ab_loopvar__4;
	    ab_loopvar__3 = ab_loopvar__4;
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar__2;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    temp = phrase_cons(Qthe,phrase_cons(temp_1,temp));
	}
	ab_loopvar__2 = phrase_cons(phrase_list_2(name_to_be_bound,temp),Nil);
    }
    else
	ab_loopvar__2 = Nil;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    return phrase_list_3(use_let_qm ? Qab_let : Qrule_let,temp,
	    rule_or_expression_body);
}

/* COPY-DESIGNATION-DROPPING-LOCAL-NAMES */
Object copy_designation_dropping_local_names(designation)
    Object designation;
{
    Object temp, temp_1, domain, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_2;

    x_note_fn_call(141,122);
    if (LISTP(designation) && IFIX(length(designation)) >= (SI_Long)2L) {
	temp = FIRST(designation);
	temp_1 = simple_role_of_role(SECOND(designation));
	domain = Nil;
	ab_loop_list_ = CDDR(designation);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	domain = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		phrase_cons(copy_designation_dropping_local_names(domain),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp_2 = ab_loopvar_;
	goto end_1;
	temp_2 = Qnil;
      end_1:;
	return phrase_cons(temp,phrase_cons(temp_1,temp_2));
    }
    else
	return VALUES_1(designation);
}

/* VALID-SCOPE-P */
Object valid_scope_p(scope)
    Object scope;
{
    x_note_fn_call(141,123);
    return VALUES_1( !( !TRUEP(scope) || EQ(THIRD(scope),Needed_domain) || 
	    EQ(SECOND(scope),Focus_range)) ? T : Nil);
}

static Object Qany;                /* any */

/* COMPILE-FORWARD-CONTEXT-ITERATOR */
Object compile_forward_context_iterator(for_structure)
    Object for_structure;
{
    Object scope, quantifier, role, domain, domain_qm;

    x_note_fn_call(141,124);
    scope = ISVREF(for_structure,(SI_Long)1L);
    if (valid_scope_p(scope)) {
	quantifier = FIRST(scope);
	role = SECOND(scope);
	domain = THIRD(scope);
	domain_qm =  !EQ(domain,Global_domain) ? domain : Nil;
	if (EQ(quantifier,Qthe))
	    return generate_forward_context_iterator(Qthe,role,domain_qm);
	else if (EQ(quantifier,Qany) || EQ(quantifier,Qevery))
	    return generate_forward_context_iterator(Qany,role,domain_qm);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* GENERATE-FORWARD-CONTEXT-ITERATOR */
Object generate_forward_context_iterator(operator_1,role,domain_qm)
    Object operator_1, role, domain_qm;
{
    Object temp;

    x_note_fn_call(141,125);
    temp = simple_role_of_role(role);
    temp = phrase_list_3(operator_1,temp,get_name_provided_by_role(role));
    return VALUES_1(nconc2(temp,domain_qm ? phrase_cons(domain_qm,Nil) : Nil));
}

/* COMPILE3-EXPRESSION-TOP */
Object compile3_expression_top(expression)
    Object expression;
{
    x_note_fn_call(141,126);
    if (Compiling_expression_p && 
	    Wrapper_references_for_left_side_of_formula_qm)
	insert_wrapper_references_for_left_side_of_formula(expression);
    if (Non_context_top_level_binding_forms)
	expression = wrap_non_context_top_level_binding_forms(expression,T);
    return compile3_expression(expression);
}

/* COMPILE3-QUANTIFIER-OR-AGGREGATOR-IF-OK */
Object compile3_quantifier_or_aggregator_if_ok(expression)
    Object expression;
{
    Object aggregator_scope, reference_structure;

    x_note_fn_call(141,127);
    aggregator_scope = SECOND(expression);
    reference_structure = ISVREF(aggregator_scope,(SI_Long)3L);
    if (ATOM(reference_structure))
	return VALUES_1(expression);
    else {
	reference_structure = CAR(reference_structure);
	if (SIMPLE_VECTOR_P(reference_structure) && 
		EQ(ISVREF(reference_structure,(SI_Long)0L),
		Qg2_defstruct_structure_name_reference_structure_g2_struct))
	    return compile3_quantifier_or_aggregator(expression);
	else
	    return VALUES_1(expression);
    }
}

static Object list_constant_6;     /* # */

static Object Qg2_defstruct_structure_name_for_structure_g2_struct;  /* g2-defstruct-structure-name::for-structure-g2-struct */

/* COMPILE3-EXPRESSION */
Object compile3_expression(expression)
    Object expression;
{
    Object temp, operator_1, temp_2;
    char temp_1;

    x_note_fn_call(141,128);
    if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,(SI_Long)0L),
	    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct))
	return compile3_expression(ISVREF(expression,(SI_Long)1L));
    else if (CONSP(expression) && EQ(M_CDR(expression),
	    Phrase_structure_marker) || CONSP(expression) && 
	    EQ(M_CDR(expression),Phrase_sequence_marker))
	return VALUES_1(expression);
    else if (CONSP(expression)) {
	if (CDR(expression)) {
	    temp = CDR(expression);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(expression);
	else {
	    operator_1 = CAR(expression);
	    if (EQ(operator_1,Qquote) || phrase_number_p(operator_1))
		return VALUES_1(expression);
	    else if (quantifier_or_aggregator_p(operator_1))
		return compile3_quantifier_or_aggregator_if_ok(expression);
	    else if (EQ(operator_1,Expression_list_indicator)) {
		if (CDR(expression))
		    return compile3_sub_expressions_of_listed_expression(CDR(expression));
		else
		    return VALUES_1(Nil_indicator);
	    }
	    else if (EQ(operator_1,Color_change_indicator)) {
		temp = compile3_expression(SECOND(expression));
		return phrase_cons(temp,
			compile3_expression(THIRD(expression)));
	    }
	    else if (memq_function(operator_1,list_constant_6)) {
		temp_2 = phrase_list_2(FIRST(expression),SECOND(expression));
		temp = THIRD(expression) ? 
			phrase_cons(compile3_expression(THIRD(expression)),
			Nil) : Nil;
		return VALUES_1(nconc2(temp_2,nconc2(temp,
			FOURTH(expression) ? 
			phrase_cons(compile3_expression(FOURTH(expression)),
			Nil) : Nil)));
	    }
	    else
		return compile3_sub_expressions_of_listed_expression(expression);
	}
    }
    else if (SYMBOLP(expression))
	return VALUES_1(expression);
    else if (text_string_p(expression) || phrase_number_p(expression))
	return VALUES_1(expression);
    else if (SIMPLE_VECTOR_P(expression) && EQ(ISVREF(expression,
	    (SI_Long)0L),Qg2_defstruct_structure_name_for_structure_g2_struct))
	return compile3_for_structure(expression);
    else
	return VALUES_1(Qnil);
}

/* COMPILE3-SUB-EXPRESSIONS-OF-LISTED-EXPRESSION */
Object compile3_sub_expressions_of_listed_expression(expression)
    Object expression;
{
    Object sub_expression, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, compiled_expression;

    x_note_fn_call(141,129);
    sub_expression = Nil;
    ab_loop_list_ = expression;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sub_expression = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    compiled_expression = compile3_expression(sub_expression);
    if (compiled_expression) {
	if (EQ(compiled_expression,Nil_indicator))
	    ab_loopvar__2 = phrase_cons(Nil,Nil);
	else if (CONSP(compiled_expression) && EQ(CAR(compiled_expression),
		Color_changes_indicator))
	    ab_loopvar__2 = CDR(compiled_expression);
	else
	    ab_loopvar__2 = phrase_cons(compiled_expression,Nil);
    }
    else
	ab_loopvar__2 = Nil;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* COMPILE3-QUANTIFIER-OR-AGGREGATOR */
Object compile3_quantifier_or_aggregator(expression)
    Object expression;
{
    Object reference_structure_for_aggregator_scope, new_role, domain;
    Object domain_qm, temp, new_aggregator_scope;

    x_note_fn_call(141,130);
    reference_structure_for_aggregator_scope = 
	    get_relevent_reference_structure_for_aggregator_scope(SECOND(expression));
    new_role = 
	    get_new_role_given_role_and_local_name(ISVREF(reference_structure_for_aggregator_scope,
	    (SI_Long)3L),ISVREF(reference_structure_for_aggregator_scope,
	    (SI_Long)2L));
    domain = ISVREF(reference_structure_for_aggregator_scope,(SI_Long)1L);
    domain_qm =  !EQ(domain,Global_domain) ? domain : Nil;
    temp = simple_role_of_role(new_role);
    temp = phrase_list_2(temp,get_name_provided_by_role(new_role));
    new_aggregator_scope = nconc2(temp,domain_qm ? phrase_cons(domain_qm,
	    Nil) : Nil);
    temp = FIRST(expression);
    return phrase_list_3(temp,new_aggregator_scope,
	    compile3_expression(THIRD(expression)));
}

/* GET-RELEVENT-REFERENCE-STRUCTURE-FOR-AGGREGATOR-SCOPE */
Object get_relevent_reference_structure_for_aggregator_scope(aggregator_scope)
    Object aggregator_scope;
{
    Object temp, reference_structure;

    x_note_fn_call(141,131);
    temp = ISVREF(aggregator_scope,(SI_Long)3L);
    reference_structure = CAR(temp);
    temp = ISVREF(reference_structure,(SI_Long)5L);
    temp = CAR(temp);
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(reference_structure);
}

/* COMPILE3-FOR-STRUCTURE */
Object compile3_for_structure(for_structure)
    Object for_structure;
{
    Object scope, new_scope, quantifier, binding_list;
    Object next_expression_to_compile;
    Object result;

    x_note_fn_call(141,132);
    scope = ISVREF(for_structure,(SI_Long)1L);
    if ( !TRUEP(valid_scope_p(scope)))
	return compile3_expression(ISVREF(for_structure,(SI_Long)2L));
    else {
	new_scope = EQ(THIRD(scope),Global_domain) ? 
		phrase_cons(SECOND(scope),Nil) : CDR(scope);
	quantifier = FIRST(scope);
	if (EQ(quantifier,Qnil)) {
	    result = generate_let_binding_list_from_nested_for_structures(for_structure,
		    Nil);
	    MVS_2(result,binding_list,next_expression_to_compile);
	    return phrase_cons(Qab_let,phrase_cons(binding_list,
		    phrase_cons(compile3_expression(next_expression_to_compile),
		    Nil)));
	}
	else
	    return compile3_for_structure_according_to_quantifier(for_structure,
		    quantifier,scope,new_scope);
    }
}

static Object Qlet_action;         /* let-action */

static Object Qfor_all;            /* for-all */

static Object Qthere_exists;       /* there-exists */

/* COMPILE3-FOR-STRUCTURE-ACCORDING-TO-QUANTIFIER */
Object compile3_for_structure_according_to_quantifier(for_structure,
	    quantifier,scope,new_scope)
    Object for_structure, quantifier, scope, new_scope;
{
    Object temp, binding_list, next_expression_to_compile, temp_1, role;
    Object domain_qm, temp_2;
    Object result;

    x_note_fn_call(141,133);
    if (EQ(quantifier,Qthe)) {
	if (EQ(THIRD(scope),Global_domain))
	    M_CDDR(scope) = Nil;
	temp = ISVREF(for_structure,(SI_Long)3L) ? Qlet_action : Qab_let;
	result = generate_let_binding_list_from_nested_for_structures(for_structure,
		Nil);
	MVS_2(result,binding_list,next_expression_to_compile);
	return phrase_cons(temp,phrase_cons(binding_list,
		phrase_cons(compile3_expression(next_expression_to_compile),
		Nil)));
    }
    else if (EQ(quantifier,Qevery)) {
	temp_1 = ISVREF(for_structure,(SI_Long)3L) ? Qevery : Qfor_all;
	role = FIRST(new_scope);
	domain_qm = SECOND(new_scope);
	temp_2 = simple_role_of_role(role);
	temp = get_name_provided_by_role(role);
	temp = phrase_cons(temp_2,phrase_cons(temp,domain_qm ? 
		phrase_cons(domain_qm,Nil) : Nil));
	return phrase_list_3(temp_1,temp,
		compile3_expression(ISVREF(for_structure,(SI_Long)2L)));
    }
    else if (EQ(quantifier,Qany)) {
	temp = ISVREF(for_structure,(SI_Long)3L) ? Qevery : Qthere_exists;
	return phrase_cons(temp,phrase_cons(new_scope,
		phrase_cons(compile3_expression(ISVREF(for_structure,
		(SI_Long)2L)),Nil)));
    }
    else
	return VALUES_1(Qnil);
}

/* GENERATE-LET-BINDING-LIST-FROM-NESTED-FOR-STRUCTURES */
Object generate_let_binding_list_from_nested_for_structures(for_structure,
	    binding_list_so_far)
    Object for_structure, binding_list_so_far;
{
    Object scope, quantifier, role_and_local_name_qm, name_provided, body;
    Object temp, second_new_value;

    x_note_fn_call(141,134);
    scope = ISVREF(for_structure,(SI_Long)1L);
    quantifier = FIRST(scope);
    role_and_local_name_qm = SECOND(scope);
    name_provided = ISVREF(for_structure,(SI_Long)4L);
    if (name_provided);
    else
	name_provided = get_name_provided_by_role(role_and_local_name_qm);
    body = ISVREF(for_structure,(SI_Long)2L);
    if ( !( !TRUEP(quantifier) || EQ(quantifier,Qthe)))
	return VALUES_2(binding_list_so_far,for_structure);
    else {
	if ( !TRUEP(quantifier)) {
	    temp = SECOND(scope);
	    binding_list_so_far = phrase_cons(phrase_list_2(temp,
		    compile3_expression(THIRD(scope))),Nil);
	}
	else {
	    if ( !TRUEP(simple_role_p(role_and_local_name_qm))) {
		second_new_value = CAR(role_and_local_name_qm);
		M_SECOND(scope) = second_new_value;
	    }
	    temp = binding_list_so_far;
	    binding_list_so_far = nconc2(temp,
		    phrase_cons(phrase_list_2(name_provided,
		    compile3_expression(scope)),Nil));
	}
	if (SIMPLE_VECTOR_P(body) && EQ(ISVREF(body,(SI_Long)0L),
		Qg2_defstruct_structure_name_for_structure_g2_struct))
	    return generate_let_binding_list_from_nested_for_structures(body,
		    binding_list_so_far);
	else
	    return VALUES_2(binding_list_so_far,body);
    }
}

void compile2_INIT()
{
    Object AB_package, G2_DEFSTRUCT_STRUCTURE_NAME_package, Qcompile2_action;
    Object Qcompile2, Qchange_icon_color, Qconclude_has_no_value;
    Object Qconclude_has_no_current_value, Qconclude_not, Qconclude;
    Object Qcreate_by_cloning, Qcreate_connection, Qconnected_between;
    Object Qsub_expression, Qcreate_explanation, Qcreate;

    x_note_fn_call(141,135);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qcompile1_forward_reference_for_designations = 
	    STATIC_SYMBOL("COMPILE1-FORWARD-REFERENCE-FOR-DESIGNATIONS",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_expression_for_compilation_g2_struct = 
	    STATIC_SYMBOL("EXPRESSION-FOR-COMPILATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_reference_structure_g2_struct = 
	    STATIC_SYMBOL("REFERENCE-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qevery_inverse = STATIC_SYMBOL("EVERY-INVERSE",AB_package);
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    Qcreate_by_cloning = STATIC_SYMBOL("CREATE-BY-CLONING",AB_package);
    Qcreate_connection = STATIC_SYMBOL("CREATE-CONNECTION",AB_package);
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    list_constant = STATIC_LIST((SI_Long)4L,Qcreate,Qcreate_by_cloning,
	    Qcreate_connection,Qcreate_explanation);
    Qcall_assignment_action = STATIC_SYMBOL("CALL-ASSIGNMENT-ACTION",
	    AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile1_forward_reference_for_designations,
	    STATIC_FUNCTION(compile1_forward_reference_for_designations,
	    NIL,FALSE,1,1));
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    Qsub_expression = STATIC_SYMBOL("SUB-EXPRESSION",AB_package);
    Qshow_or_hide_argument_list = 
	    STATIC_SYMBOL("SHOW-OR-HIDE-ARGUMENT-LIST",AB_package);
    Qcolor_changes = STATIC_SYMBOL("COLOR-CHANGES",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qother,Qsub_expression,
	    Qshow_or_hide_argument_list,Qcolor_changes);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qexpression_list = STATIC_SYMBOL("EXPRESSION-LIST",AB_package);
    Qdesignation_list = STATIC_SYMBOL("DESIGNATION-LIST",AB_package);
    Qcreate_connection_spec = STATIC_SYMBOL("CREATE-CONNECTION-SPEC",
	    AB_package);
    Qin = STATIC_SYMBOL("IN",AB_package);
    Qconnected_to = STATIC_SYMBOL("CONNECTED-TO",AB_package);
    Qconnected_between = STATIC_SYMBOL("CONNECTED-BETWEEN",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qconnected_to,
	    Qconnected_between);
    Qquantifier = STATIC_SYMBOL("QUANTIFIER",AB_package);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qcreate_connection,
	    Qcreate_by_cloning);
    Qexplicitly_specified_local_name_refers_to_more_than_one_item = 
	    STATIC_SYMBOL("EXPLICITLY-SPECIFIED-LOCAL-NAME-REFERS-TO-MORE-THAN-ONE-ITEM",
	    AB_package);
    Qforward = STATIC_SYMBOL("FORWARD",AB_package);
    Qbackward = STATIC_SYMBOL("BACKWARD",AB_package);
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    Qroot_reference_role_name_same_as_previously_specified_local_name = 
	    STATIC_SYMBOL("ROOT-REFERENCE-ROLE-NAME-SAME-AS-PREVIOUSLY-SPECIFIED-LOCAL-NAME",
	    AB_package);
    Qambiguous_reference = STATIC_SYMBOL("AMBIGUOUS-REFERENCE",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    Qconclude_has_no_current_value = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE",AB_package);
    Qconclude_has_no_value = STATIC_SYMBOL("CONCLUDE-HAS-NO-VALUE",AB_package);
    Qchange_icon_color = STATIC_SYMBOL("CHANGE-ICON-COLOR",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)5L,Qconclude,Qconclude_not,
	    Qconclude_has_no_current_value,Qconclude_has_no_value,
	    Qchange_icon_color);
    Qin_non_top_level_context_qm = 
	    STATIC_SYMBOL("IN-NON-TOP-LEVEL-CONTEXT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qin_non_top_level_context_qm,
	    In_non_top_level_context_qm);
    Qcompile2 = STATIC_SYMBOL("COMPILE2",AB_package);
    record_system_variable(Qin_non_top_level_context_qm,Qcompile2,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcompile2_quantifier_or_aggregator = 
	    STATIC_SYMBOL("COMPILE2-QUANTIFIER-OR-AGGREGATOR",AB_package);
    Qcompile2_and_expression = STATIC_SYMBOL("COMPILE2-AND-EXPRESSION",
	    AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qcompile2_or_expression = STATIC_SYMBOL("COMPILE2-OR-EXPRESSION",
	    AB_package);
    Qcompile2_not_expression = STATIC_SYMBOL("COMPILE2-NOT-EXPRESSION",
	    AB_package);
    Qcompile2_if_expression = STATIC_SYMBOL("COMPILE2-IF-EXPRESSION",
	    AB_package);
    Qcompile2_comparison_operator_expression = 
	    STATIC_SYMBOL("COMPILE2-COMPARISON-OPERATOR-EXPRESSION",
	    AB_package);
    Qcompile2_name = STATIC_SYMBOL("COMPILE2-NAME",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qcompile2_action = STATIC_SYMBOL("COMPILE2-ACTION",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile2_action,STATIC_FUNCTION(compile2_action,
	    NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcompile2_if_expression,
	    STATIC_FUNCTION(compile2_if_expression,NIL,FALSE,1,1));
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile2_quantifier_or_aggregator,
	    STATIC_FUNCTION(compile2_quantifier_or_aggregator,NIL,FALSE,1,1));
    Qcombine_sub_expression_with_expression = 
	    STATIC_SYMBOL("COMBINE-SUB-EXPRESSION-WITH-EXPRESSION",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile2_comparison_operator_expression,
	    STATIC_FUNCTION(compile2_comparison_operator_expression,NIL,
	    FALSE,1,1));
    Qcontext_iteration_forms = STATIC_SYMBOL("CONTEXT-ITERATION-FORMS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcontext_iteration_forms,
	    Context_iteration_forms);
    string_constant = STATIC_STRING("\"any\" may only be used in a rule.");
    SET_SYMBOL_FUNCTION(Qcompile2_name,STATIC_FUNCTION(compile2_name,NIL,
	    FALSE,1,1));
    Qsymbolic_variable = STATIC_SYMBOL("SYMBOLIC-VARIABLE",AB_package);
    Qc2 = STATIC_SYMBOL("C2",AB_package);
    SET_SYMBOL_FUNCTION(Qcombine_sub_expression_with_expression,
	    STATIC_FUNCTION(combine_sub_expression_with_expression,NIL,
	    FALSE,2,2));
    Qany = STATIC_SYMBOL("ANY",AB_package);
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qany,Qevery,Qevery_inverse);
    Qreplace_compiler_generated_local_name_1 = 
	    STATIC_SYMBOL("REPLACE-COMPILER-GENERATED-LOCAL-NAME-1",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreplace_compiler_generated_local_name_1,
	    STATIC_FUNCTION(replace_compiler_generated_local_name_1,NIL,
	    FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qcompile2_and_expression,
	    STATIC_FUNCTION(compile2_and_expression,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcompile2_or_expression,
	    STATIC_FUNCTION(compile2_or_expression,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcompile2_not_expression,
	    STATIC_FUNCTION(compile2_not_expression,NIL,FALSE,1,1));
    Qcompile3_expression = STATIC_SYMBOL("COMPILE3-EXPRESSION",AB_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qthe_inverse_no_bind = STATIC_SYMBOL("THE-INVERSE-NO-BIND",AB_package);
    Qthe_inverse = STATIC_SYMBOL("THE-INVERSE",AB_package);
    Qany_inverse = STATIC_SYMBOL("ANY-INVERSE",AB_package);
    Qrule_let = STATIC_SYMBOL("RULE-LET",AB_package);
    Qcall_procedure = STATIC_SYMBOL("CALL-PROCEDURE",AB_package);
    Qab_let = STATIC_SYMBOL("LET",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_let,Qthe);
    Qg2_defstruct_structure_name_for_structure_g2_struct = 
	    STATIC_SYMBOL("FOR-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qcompile3_expression,
	    STATIC_FUNCTION(compile3_expression,NIL,FALSE,1,1));
    Qlet_action = STATIC_SYMBOL("LET-ACTION",AB_package);
    Qfor_all = STATIC_SYMBOL("FOR-ALL",AB_package);
    Qthere_exists = STATIC_SYMBOL("THERE-EXISTS",AB_package);
}
