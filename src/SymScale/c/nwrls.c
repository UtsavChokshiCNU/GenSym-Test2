/* nwrls.c
 * Input file:  new-rules.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "nwrls.h"


/* RECLAIM-EVALUATION-ACTION-CACHE */
Object reclaim_evaluation_action_cache(action_cache)
    Object action_cache;
{
    Object first_cons, trailer, current_cons, element_cons, temp, svref_arg_2;
    Object eval_cons;

    x_note_fn_call(152,0);
    first_cons = M_CAR(action_cache);
    if (first_cons) {
	trailer = Nil;
	current_cons = first_cons;
	element_cons = Nil;
      next_loop:
	if ( !TRUEP(current_cons))
	    goto end_loop;
	element_cons = M_CAR(current_cons);
	if (IFIX(M_CAR(element_cons)) != (SI_Long)0L)
	    reclaim_environment_vector(M_CDR(element_cons));
	inline_note_reclaim_cons(element_cons,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = element_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = element_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = element_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = element_cons;
	}
	M_CDR(element_cons) = Nil;
	trailer = current_cons;
	current_cons = M_CDR(current_cons);
	goto next_loop;
      end_loop:
	if (first_cons &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = first_cons;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,trailer))
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
	    M_CDR(temp) = first_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = first_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	M_CDR(trailer) = Nil;
    }
    if (action_cache) {
	inline_note_reclaim_cons(action_cache,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = action_cache;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = action_cache;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = action_cache;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = action_cache;
	}
	M_CDR(action_cache) = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qaction_cache;       /* action-cache */

/* COPY-EVALUATION-ACTION-CACHE */
Object copy_evaluation_action_cache(action_cache)
    Object action_cache;
{
    Object element_cons, ab_loop_list_, count_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(152,1);
    element_cons = Nil;
    ab_loop_list_ = M_CAR(action_cache);
    count_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element_cons = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    count_1 = M_CAR(element_cons);
    temp = count_1;
    ab_loopvar__2 = eval_cons_1(eval_cons_1(temp,IFIX(count_1) != 
	    (SI_Long)0L ? copy_environment_vector(M_CDR(element_cons)) : 
	    Nil),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    temp = eval_cons_1(temp,Qaction_cache);
    return VALUES_1(temp);
}

/* EVALUATION-ACTION-CACHE-EQL */
Object evaluation_action_cache_eql(action_cache_1,action_cache_2)
    Object action_cache_1, action_cache_2;
{
    x_note_fn_call(152,2);
    return VALUES_1(Nil);
}

static Object string_constant;     /* "~a cached action argument~a" */

static Object string_constant_1;   /* "" */

static Object string_constant_2;   /* "s" */

/* WRITE-EVALUATION-ACTION-CACHE */
Object write_evaluation_action_cache(action_cache)
    Object action_cache;
{
    Object count_1;

    x_note_fn_call(152,3);
    count_1 = length(M_CAR(action_cache));
    tformat(3,string_constant,count_1,IFIX(count_1) == (SI_Long)1L ? 
	    string_constant_1 : string_constant_2);
    return VALUES_1(Nil);
}

/* VALIDATE-EVALUATION-ACTION-CACHE */
Object validate_evaluation_action_cache(action_cache,frame_serial_number)
    Object action_cache, frame_serial_number;
{
    Object cache_cons, ab_loop_list_, count_1, vector_qm, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(152,4);
    cache_cons = Nil;
    ab_loop_list_ = M_CAR(action_cache);
    count_1 = Nil;
    vector_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cache_cons = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    count_1 = M_CAR(cache_cons);
    vector_qm = M_CDR(cache_cons);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(count_1);
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    svref_new_value = validate_item_or_evaluation_value(ISVREF(vector_qm,
	    index_1),frame_serial_number,Nil);
    ISVREF(vector_qm,index_1) = svref_new_value;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    return VALUES_1(action_cache);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* VALID-RULE-CONTEXT-VECTOR-P */
Object valid_rule_context_vector_p(context_vector,environment_length,
	    frame_serial_number,rule,also_validate_item_classes_qm)
    Object context_vector, environment_length, frame_serial_number, rule;
    Object also_validate_item_classes_qm;
{
    Object current_computation_flags, value_qm, temp, rule_byte_code_body;
    Object descriptions, item_type_qm, ab_loop_iter_flag_, x2;
    SI_Long index_1, ab_loop_bind_, description_index, ab_loop_bind__1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(152,5);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)33554432L))
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)16L);
      else
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  &  ~(SI_Long)16L);
      if ( !TRUEP(also_validate_item_classes_qm)) {
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(environment_length);
	  value_qm = Nil;
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  value_qm = ISVREF(context_vector,index_1);
	  if ( !( !TRUEP(value_qm) || 
		  valid_item_or_evaluation_value_p(value_qm,
		  frame_serial_number,Nil))) {
	      temp = Nil;
	      goto end_1;
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  temp = T;
	  goto end_1;
	  temp = Qnil;
	end_1:;
      }
      else {
	  rule_byte_code_body = ISVREF(rule,(SI_Long)31L);
	  descriptions = ISVREF(rule_byte_code_body,(SI_Long)4L);
	  description_index = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(var_count(descriptions));
	  index_1 = (SI_Long)0L;
	  ab_loop_bind__1 = IFIX(environment_length);
	  value_qm = Nil;
	  item_type_qm = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop_1:
	  if (description_index >= ab_loop_bind_)
	      goto end_loop_1;
	  if ( !TRUEP(ab_loop_iter_flag_))
	      index_1 = index_1 + (SI_Long)1L;
	  if (index_1 >= ab_loop_bind__1)
	      goto end_loop_1;
	  value_qm = ISVREF(context_vector,index_1);
	  if (SIMPLE_VECTOR_P(value_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) > (SI_Long)2L 
		  &&  !EQ(ISVREF(value_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(value_qm,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  item_type_qm = temp_1 ? 
		  var_type_from_index_function(descriptions,
		  FIX(description_index)) : Nil;
	  if ( !( !TRUEP(value_qm) || 
		  valid_item_or_evaluation_value_p(value_qm,
		  frame_serial_number,item_type_qm))) {
	      temp = Nil;
	      goto end_2;
	  }
	  ab_loop_iter_flag_ = Nil;
	  description_index = description_index + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:
	  temp = T;
	  goto end_2;
	  temp = Qnil;
	end_2:;
      }
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* VALIDATE-RULE-CONTEXT-VECTOR */
Object validate_rule_context_vector(context_vector,environment_length,
	    frame_serial_number,rule,also_validate_item_classes_qm)
    Object context_vector, environment_length, frame_serial_number, rule;
    Object also_validate_item_classes_qm;
{
    Object current_computation_flags, value_qm, svref_new_value, temp;
    Object rule_byte_code_body, descriptions, item_type_qm, ab_loop_iter_flag_;
    Object x2;
    SI_Long index_1, ab_loop_bind_, description_index, ab_loop_bind__1;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(152,6);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)33554432L))
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)16L);
      else
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  &  ~(SI_Long)16L);
      if ( !TRUEP(also_validate_item_classes_qm)) {
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(environment_length);
	  value_qm = Nil;
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  value_qm = ISVREF(context_vector,index_1);
	  if (value_qm) {
	      svref_new_value = validate_item_or_evaluation_value(value_qm,
		      frame_serial_number,Nil);
	      ISVREF(context_vector,index_1) = svref_new_value;
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  temp = Qnil;
      }
      else {
	  rule_byte_code_body = ISVREF(rule,(SI_Long)31L);
	  descriptions = ISVREF(rule_byte_code_body,(SI_Long)4L);
	  description_index = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(var_count(descriptions));
	  index_1 = (SI_Long)0L;
	  ab_loop_bind__1 = IFIX(environment_length);
	  value_qm = Nil;
	  item_type_qm = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop_1:
	  if (description_index >= ab_loop_bind_)
	      goto end_loop_1;
	  if ( !TRUEP(ab_loop_iter_flag_))
	      index_1 = index_1 + (SI_Long)1L;
	  if (index_1 >= ab_loop_bind__1)
	      goto end_loop_1;
	  value_qm = ISVREF(context_vector,index_1);
	  if (SIMPLE_VECTOR_P(value_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) > (SI_Long)2L 
		  &&  !EQ(ISVREF(value_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(value_qm,(SI_Long)1L);
	      temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  item_type_qm = temp_1 ? 
		  var_type_from_index_function(descriptions,
		  FIX(description_index)) : Nil;
	  if (value_qm) {
	      svref_new_value = validate_item_or_evaluation_value(value_qm,
		      frame_serial_number,item_type_qm);
	      ISVREF(context_vector,index_1) = svref_new_value;
	  }
	  ab_loop_iter_flag_ = Nil;
	  description_index = description_index + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:
	  temp = Qnil;
      }
    POP_SPECIAL();
    return VALUES_1(temp);
}

static Object Qrule;               /* rule */

static Object Qequal_rule_context;  /* equal-rule-context */

/* VALIDATE-ALL-RULE-INSTANCES */
Object validate_all_rule_instances()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, rule;
    Object rule_instance_hash_table_qm, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, rule_instance, rule_instance_state;
    Object context_vector, environment_length, frame_serial_number;
    Object rule_instances_to_dismiss_qm, ab_less_than_branch_qm_;
    Object gensymed_symbol, temp_1, ab_loop_list_, old_key, old_entry;
    SI_Long ab_table_length_, ab_index_, gensymed_symbol_1, temp_2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(152,7);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    rule = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,1);
      rule_instance_hash_table_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qrule);
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
      rule = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      rule_instance_hash_table_qm = ISVREF(rule,(SI_Long)27L);
      if (rule_instance_hash_table_qm) {
	  scope_conses = Scope_conses;
	  ab_hash_table_ = rule_instance_hash_table_qm;
	  ab_table_length_ = (SI_Long)0L;
	  ab_index_ = (SI_Long)0L;
	  ab_tree_form_ = Nil;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  ab_skip_list_p_ = Nil;
	  ab_tail_node_ = Nil;
	  rule_instance = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    rule_instance_state = Nil;
	    context_vector = Nil;
	    environment_length = Nil;
	    frame_serial_number = Nil;
	    rule_instances_to_dismiss_qm = Nil;
	    ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_current_node_ && ab_skip_list_p_) {
		ab_current_node_ = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			(SI_Long)0L),(SI_Long)0L));
		if (EQ(ab_current_node_,ab_tail_node_))
		    ab_current_node_ = Nil;
		else
		    ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			    (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	    }
	    else if (ab_current_node_) {
		ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		if (ab_current_node_) {
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack_) {
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		if (ab_current_node_) {
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_)) {
	      next_loop_4:
		if ( !(ab_index_ < ab_table_length_))
		    goto end_loop_3;
		ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		if (ab_index_ == (SI_Long)0L) {
		    gensymed_symbol = CDR(ab_tree_form_);
		    if (CONSP(gensymed_symbol)) {
			temp_1 = M_CAR(gensymed_symbol);
			temp = SIMPLE_VECTOR_P(temp_1);
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			temp_1 = M_CDR(gensymed_symbol);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		}
		ab_index_ = ab_index_ + (SI_Long)1L;
		if (ab_skip_list_p_) {
		    ab_current_node_ = 
			    ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_tree_form_)),
			    (SI_Long)0L),(SI_Long)0L));
		    ab_tail_node_ = M_CDR(M_CDR(ab_tree_form_));
		    if (EQ(ab_current_node_,ab_tail_node_))
			ab_current_node_ = Nil;
		    else {
			ab_entry_cons_ = 
				scope_cons(ISVREF(ab_current_node_,
				(SI_Long)2L),ISVREF(ab_current_node_,
				(SI_Long)3L));
			goto end_loop_3;
		    }
		}
		else {
		    ab_current_node_ = CDR(ab_tree_form_);
		    if (ab_current_node_) {
			ab_less_than_branch_qm_ = Nil;
		      next_loop_5:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_4;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_5;
		      end_loop_4:;
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
			goto end_loop_3;
		    }
		}
		goto next_loop_4;
	      end_loop_3:;
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_5;
	    rule_instance = M_CDR(ab_entry_cons_);
	    rule_instance_state = ISVREF(rule_instance,(SI_Long)19L);
	    context_vector = ISVREF(rule_instance,(SI_Long)2L);
	    environment_length = ISVREF(rule,(SI_Long)34L);
	    frame_serial_number = 
		    copy_frame_serial_number(ISVREF(rule_instance,
		    (SI_Long)11L));
	    if (IFIX(rule_instance_state) == (SI_Long)0L) {
		if ( !TRUEP(valid_rule_context_vector_p(context_vector,
			environment_length,frame_serial_number,rule,T)))
		    rule_instances_to_dismiss_qm =  
			    !TRUEP(rule_instances_to_dismiss_qm) ? 
			    gensym_cons_1(rule_instance,Nil) : 
			    gensym_cons_1(rule_instance,
			    rule_instances_to_dismiss_qm);
	    }
	    else
		validate_rule_context_vector(context_vector,
			environment_length,frame_serial_number,rule,T);
	    goto next_loop_2;
	  end_loop_5:
	    reclaim_frame_serial_number(frame_serial_number);
	    rule_instance = Nil;
	    ab_loop_list_ = rule_instances_to_dismiss_qm;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_6;
	    rule_instance = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(rule_instance,(SI_Long)10L);
	    gensymed_symbol_1 = IFIX(M_CAR(gensymed_symbol));
	    temp_1 = rule_instance_hash_table_qm;
	    temp_2 = gensymed_symbol_1 % (SI_Long)43L;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
		    gensymed_symbol,SVREF(temp_1,FIX(temp_2)),
		    FIX((SI_Long)31L),FIX(gensymed_symbol_1));
	    MVS_2(result,old_key,old_entry);
	    if (old_key)
		reclaim_rule_context(old_key);
	    if (old_entry)
		dismiss_rule_instance(old_entry);
	    goto next_loop_6;
	  end_loop_6:
	    if (rule_instances_to_dismiss_qm)
		reclaim_gensym_list_1(rule_instances_to_dismiss_qm);
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_style, Qcurrent_computation_style);

DEFINE_VARIABLE_WITH_SYMBOL(Evaluating_simulator_procedure_qm, Qevaluating_simulator_procedure_qm);

static Object Qinference_engine;   /* inference-engine */

static Object Qnever;              /* never */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

static Object string_constant_3;   /* "Invoking-rule ~NF." */

static Object string_constant_4;   /* "Terminating invocation of rule ~NF because either some item in ~
				    *               its invocation has been deleted or some dynamic relation among ~
				    *               these items no longer holds."
				    */

static Object Qhighlight_invoked_rules_mode;  /* highlight-invoked-rules-mode */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object Qforeground;         /* foreground */

static Object Qdefault;            /* default */

static Object Qaction_button;      /* action-button */

/* ENTER-OR-RECLAIM-RULE-INSTANCE-CONTEXT */
Object enter_or_reclaim_rule_instance_context(rule_instance,
	    dont_validate_environment)
    Object rule_instance, dont_validate_environment;
{
    Object rule, context_vector, environment_length, frame_serial_number;
    Object rule_instance_state, temp, rule_purpose, gensymed_symbol_5, old_key;
    Object old_entry, timeout, fixnum_time_limit;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, temp_1;
    Object result;

    x_note_fn_call(152,8);
    rule = ISVREF(rule_instance,(SI_Long)8L);
    context_vector = ISVREF(rule_instance,(SI_Long)2L);
    environment_length = ISVREF(rule,(SI_Long)34L);
    frame_serial_number = copy_frame_serial_number(ISVREF(rule_instance,
	    (SI_Long)11L));
    rule_instance_state = ISVREF(rule_instance,(SI_Long)19L);
    temp = ISVREF(rule_instance,(SI_Long)16L);
    if (CONSP(temp)) {
	temp = ISVREF(rule_instance,(SI_Long)16L);
	rule_purpose = CAR(temp);
    }
    else
	rule_purpose = Nil;
    gensymed_symbol = explanation_related_features_enabled_func_qm() && 
	    (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)1048576L) ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_1 = (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)33554432L) ? (SI_Long)16L : (SI_Long)0L;
    gensymed_symbol_2 =  !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) 
	    & (SI_Long)16L)) ? (SI_Long)128L : (SI_Long)0L;
    gensymed_symbol_3 =  !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) 
	    & (SI_Long)16L)) ? (SI_Long)256L : (SI_Long)0L;
    gensymed_symbol_4 =  !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) 
	    & (SI_Long)32768L)) ? (SI_Long)512L : (SI_Long)0L;
    Current_computation_flags = FIX(gensymed_symbol + gensymed_symbol_1 + 
	    gensymed_symbol_2 + gensymed_symbol_3 + gensymed_symbol_4);
    Current_computation_activity = FIX((SI_Long)0L);
    Current_computation_component_particulars = Nil;
    Current_computation_frame = rule;
    Current_computation_instance = rule_instance;
    Current_computation_style = Nil;
    Current_environment = Qinference_engine;
    Evaluating_simulator_procedure_qm = Nil;
    if (Explanation_variables)
	reclaim_explanation_variables();
    Stack_expiration = Qnever;
    Variables_that_did_not_have_values = Nil;
    gensymed_symbol_5 = get_lookup_slot_value(rule,Qtracing_and_breakpoints);
    if ((gensymed_symbol_5 || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(rule,
		gensymed_symbol_5);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L)
	    issue_tracing_and_breakpoints_entry_message(rule,
		    tformat_text_string(2,string_constant_3,rule));
    }
    if (IFIX(rule_instance_state) == (SI_Long)0L &&  
	    !TRUEP(dont_validate_environment) &&  
	    !TRUEP(valid_rule_context_vector_p(context_vector,
	    environment_length,frame_serial_number,rule,Nil))) {
	gensymed_symbol_5 = ISVREF(rule_instance,(SI_Long)10L);
	gensymed_symbol = IFIX(M_CAR(gensymed_symbol_5));
	temp = ISVREF(rule,(SI_Long)27L);
	temp_1 = gensymed_symbol % (SI_Long)43L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
		gensymed_symbol_5,SVREF(temp,FIX(temp_1)),
		FIX((SI_Long)31L),FIX(gensymed_symbol));
	MVS_2(result,old_key,old_entry);
	if (old_key)
	    reclaim_rule_context(old_key);
	if (old_entry)
	    dismiss_rule_instance(old_entry);
	if (Saved_warning_level) {
	    if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		    IFIX(Tracing_message_level) > (SI_Long)0L) && 
		    ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		    !TRUEP(in_order_p(rule)))
		issue_tracing_and_breakpoint_exit_message(rule,
			tformat_text_string(2,string_constant_4,rule));
	    Warning_message_level = Saved_warning_level;
	    Tracing_message_level = Saved_tracing_level;
	    Breakpoint_level = Saved_breakpoint_level;
	    Source_stepping_level = Saved_source_stepping_level;
	}
	clear_computation_context_variables();
    }
    else {
	if (IFIX(rule_instance_state) != (SI_Long)0L &&  
		!TRUEP(dont_validate_environment))
	    validate_rule_context_vector(context_vector,environment_length,
		    frame_serial_number,rule,Nil);
	if (get_lookup_slot_value_given_default(Debugging_parameters,
		Qhighlight_invoked_rules_mode,Nil)) {
	    SVREF(rule_instance,FIX((SI_Long)24L)) = T;
	    highlight_or_unhighlight_for_slot(5,rule,
		    Qbox_translation_and_text,Nil,Qforeground,Nil);
	    force_process_drawing();
	}
	else
	    SVREF(rule_instance,FIX((SI_Long)24L)) = Nil;
	timeout = ISVREF(rule,(SI_Long)29L);
	if (EQ(timeout,Qdefault))
	    timeout = ISVREF(Inference_engine_parameters,(SI_Long)24L);
	if (ISVREF(rule_instance,(SI_Long)15L) || timeout && 
		FIXNUM_LE(FIXNUM_ADD(ISVREF(rule_instance,(SI_Long)18L),
		timeout),Gensym_time))
	    Current_computation_flags = 
		    FIX(IFIX(Current_computation_flags) | (SI_Long)2L);
    }
    reclaim_frame_serial_number(frame_serial_number);
    if (EQ(rule_purpose,Qaction_button))
	return VALUES_1(Nil);
    fixnum_time_limit = ISVREF(rule,(SI_Long)29L);
    if (EQ(fixnum_time_limit,Qdefault))
	fixnum_time_limit = ISVREF(Inference_engine_parameters,(SI_Long)24L);
    fixnum_time_limit = FIX(IFIX(fixnum_time_limit) * (SI_Long)1000L);
    return VALUES_1(fixnum_time_limit);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qschedule_computation_instance_execution;  /* schedule-computation-instance-execution */

static Object string_constant_5;   /* "Rule ~NF did not complete and is being continued." */

static Object string_constant_6;   /* "Rule ~NF did not complete.  Its time for completion has expired." */

static Object string_constant_7;   /* "Rule ~NF has completed." */

/* EXIT-LAST-RULE-INSTANCE-CONTEXT */
Object exit_last_rule_instance_context(stack_program_counter)
    Object stack_program_counter;
{
    Object rule_instance, rule, temp_1, schedule_task_qm, timeout_qm, old;
    Object new_1, def_structure_schedule_task_variable, temp_2, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed, variable_list;
    Object frame_serial_number_setf_arg, old_1, new_2, gensymed_symbol, temp_3;
    Object old_key, old_entry, cached_variables;
    SI_Long gensymed_symbol_1, temp_4;
    char temp, continue_rule_qm, svref_new_value_1;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(152,9);
    rule_instance = Current_computation_instance;
    rule = ISVREF(rule_instance,(SI_Long)8L);
    temp = (IFIX(Current_computation_flags) & (SI_Long)2L) != (SI_Long)0L;
    if (temp);
    else {
	temp_1 = ISVREF(rule_instance,(SI_Long)19L);
	temp = SYMBOLP(temp_1);
    }
    if (temp);
    else
	temp =  !TRUEP(ISVREF(rule_instance,(SI_Long)17L));
    if (temp);
    else
	temp =  !TRUEP(ISVREF(rule_instance,(SI_Long)16L));
    continue_rule_qm =  !temp;
    if (continue_rule_qm) {
	schedule_task_qm = ISVREF(rule_instance,(SI_Long)13L);
	temp =  !(schedule_task_qm && (ISVREF(schedule_task_qm,
		(SI_Long)6L) || EQ(schedule_task_qm,Current_schedule_task)));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	timeout_qm = ISVREF(rule,(SI_Long)29L);
	if (EQ(timeout_qm,Qdefault))
	    timeout_qm = ISVREF(Inference_engine_parameters,(SI_Long)24L);
	if (timeout_qm) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(rule_instance,(SI_Long)13L);
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
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
		    + 
		    (double)IFIX(FIXNUM_MINUS(FIXNUM_ADD(ISVREF(rule_instance,
		    (SI_Long)18L),timeout_qm),Gensym_time));
	    DFLOAT_ISASET_1(temp_2,(SI_Long)0L,aref_new_value);
	    temp_2 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp_2,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !TRUEP(Nil);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    temp_2 = ISVREF(rule_instance,(SI_Long)14L);
	    SVREF(task,FIX((SI_Long)4L)) = temp_2;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qschedule_computation_instance_execution;
	    temp_2 = SYMBOL_FUNCTION(Qschedule_computation_instance_execution);
	    SVREF(task,FIX((SI_Long)8L)) = temp_2;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
	    SVREF(task,FIX((SI_Long)13L)) = rule_instance;
	    temp_2 = ISVREF(rule_instance,(SI_Long)14L);
	    SVREF(task,FIX((SI_Long)14L)) = temp_2;
	    SVREF(task,FIX((SI_Long)15L)) = rule;
	    new_1 = task;
	    if (CAS_SVREF(rule_instance,(SI_Long)13L,old,new_1)) {
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
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = old;
		}
		future_task_schedule_2(new_1);
		goto end_1;
	    }
	    else {
		inline_note_reclaim_cons(new_1,Nil);
		structure_being_reclaimed = new_1;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
		  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_2 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_2;
		temp_2 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = new_1;
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
    }
    if (ISVREF(rule_instance,(SI_Long)15L)) {
	if ( !continue_rule_qm) {
	    schedule_computation_instance_execution(rule_instance,
		    ISVREF(rule_instance,(SI_Long)15L),rule);
	    SVREF(rule_instance,FIX((SI_Long)15L)) = Nil;
	    variable_list = ISVREF(rule_instance,(SI_Long)21L);
	    if (variable_list) {
		reclaim_evaluation_variables_list(variable_list);
		SVREF(rule_instance,FIX((SI_Long)21L)) = Nil;
	    }
	    if (Backward_chaining_displays)
		update_backward_chaining_displays_function(rule_instance);
	    ISVREF(rule_instance,(SI_Long)19L) = FIX((SI_Long)0L);
	    if (Profiling_enabled_qm)
		increment_profiling_calls(ISVREF(rule_instance,(SI_Long)8L));
	    frame_serial_number_setf_arg = Current_frame_serial_number;
	    old_1 = ISVREF(rule_instance,(SI_Long)11L);
	    new_2 = frame_serial_number_setf_arg;
	    temp_2 = (FIXNUMP(old_1) ||  !TRUEP(old_1)) && (FIXNUMP(new_2) 
		    ||  !TRUEP(new_2)) ? new_2 : 
		    frame_serial_number_setf_helper_1(old_1,new_2);
	    SVREF(rule_instance,FIX((SI_Long)11L)) = temp_2;
	    ISVREF(rule_instance,(SI_Long)3L) = FIX((SI_Long)0L);
	    temp_2 = Gensym_time;
	    SVREF(rule_instance,FIX((SI_Long)18L)) = temp_2;
	    gensymed_symbol = Nil;
	  next_loop_1:
	    gensymed_symbol = ISVREF(rule_instance,(SI_Long)13L);
	    if (CAS_SVREF(rule_instance,(SI_Long)13L,gensymed_symbol,Nil)) {
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
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = gensymed_symbol;
		}
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	  end_2:;
	}
	else {
	    frame_serial_number_setf_arg = Current_frame_serial_number;
	    old_1 = ISVREF(rule_instance,(SI_Long)11L);
	    new_2 = frame_serial_number_setf_arg;
	    temp_2 = (FIXNUMP(old_1) ||  !TRUEP(old_1)) && (FIXNUMP(new_2) 
		    ||  !TRUEP(new_2)) ? new_2 : 
		    frame_serial_number_setf_helper_1(old_1,new_2);
	    SVREF(rule_instance,FIX((SI_Long)11L)) = temp_2;
	    SVREF(rule_instance,FIX((SI_Long)3L)) = stack_program_counter;
	    if (Backward_chaining_displays)
		update_backward_chaining_displays_function(rule_instance);
	    temp_1 = ISVREF(rule_instance,(SI_Long)15L);
	    temp_3 = ISVREF(rule_instance,(SI_Long)14L);
	    schedule_computation_instance_execution(rule_instance,
		    FIXNUM_MIN(temp_1,temp_3),rule);
	}
    }
    else if ( !continue_rule_qm) {
	gensymed_symbol = ISVREF(rule_instance,(SI_Long)10L);
	gensymed_symbol_1 = IFIX(M_CAR(gensymed_symbol));
	temp_1 = ISVREF(rule,(SI_Long)27L);
	temp_4 = gensymed_symbol_1 % (SI_Long)43L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
		gensymed_symbol,SVREF(temp_1,FIX(temp_4)),
		FIX((SI_Long)31L),FIX(gensymed_symbol_1));
	MVS_2(result,old_key,old_entry);
	if (old_key)
	    reclaim_rule_context(old_key);
	if (old_entry)
	    dismiss_rule_instance(old_entry);
    }
    else {
	frame_serial_number_setf_arg = Current_frame_serial_number;
	old_1 = ISVREF(rule_instance,(SI_Long)11L);
	new_2 = frame_serial_number_setf_arg;
	temp_2 = (FIXNUMP(old_1) ||  !TRUEP(old_1)) && (FIXNUMP(new_2) ||  
		!TRUEP(new_2)) ? new_2 : 
		frame_serial_number_setf_helper_1(old_1,new_2);
	SVREF(rule_instance,FIX((SI_Long)11L)) = temp_2;
	SVREF(rule_instance,FIX((SI_Long)3L)) = stack_program_counter;
	if (Backward_chaining_displays)
	    update_backward_chaining_displays_function(rule_instance);
    }
    if (ISVREF(rule_instance,(SI_Long)24L)) {
	g2ext_sys_sleep((SI_Long)50L);
	highlight_or_unhighlight_for_slot(5,rule,Qbox_translation_and_text,
		Nil,Qforeground,T);
	force_process_drawing();
	SVREF(rule_instance,FIX((SI_Long)24L)) = Nil;
    }
    if (continue_rule_qm && IFIX(ISVREF(rule_instance,(SI_Long)19L)) == 
	    (SI_Long)0L && explanation_related_features_enabled_func_qm()) {
	cached_variables = ISVREF(rule_instance,(SI_Long)21L);
	if (cached_variables) {
	    reclaim_evaluation_variables_list(cached_variables);
	    SVREF(rule_instance,FIX((SI_Long)21L)) = Nil;
	}
    }
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(rule))) {
	    if (continue_rule_qm)
		temp_1 = string_constant_5;
	    else if ((IFIX(Current_computation_flags) & (SI_Long)2L) != 
		    (SI_Long)0L)
		temp_1 = string_constant_6;
	    else
		temp_1 = string_constant_7;
	    issue_tracing_and_breakpoint_exit_message(rule,
		    tformat_text_string(2,temp_1,rule));
	}
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    clear_computation_context_variables();
    return VALUES_1(Nil);
}

static Object Qnone;               /* none */

static Object string_constant_8;   /* "The rule ~NF was invoked via the focal role ~a, which was ~
				    *                    not in its list of focal roles."
				    */

static Object string_constant_9;   /* "The rule ~NF was invoked via the focal role ~a, which ~
				    *                     was not in its list of focal roles."
				    */

/* GENERATE-RULE-CONTEXT-VECTORS */
Object generate_rule_context_vectors(rule,focal_role_qm,local_name_qm,
	    focal_entity_qm,constraint_alist)
    Object rule, focal_role_qm, local_name_qm, focal_entity_qm;
    Object constraint_alist;
{
    Object prefix, focal_specifier, role_for_prefix, index_for_prefix;
    Object environment_length, new_vector, initial_environment_qm;
    Object definition_qm, rule_contexts, current_computation_frame;
    Object current_computation_component_particulars;
    Object current_computation_flags, temp, pair, ab_loop_list_;
    Object prefixes_found_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(3);
    Object result;

    x_note_fn_call(152,10);
    prefix = Qnone;
    focal_specifier = Nil;
    role_for_prefix = Nil;
    index_for_prefix = Nil;
    environment_length = ISVREF(rule,(SI_Long)34L);
    if (IFIX(environment_length) > (SI_Long)0L) {
	new_vector = 
		allocate_managed_simple_vector(buffer_size_for_partial_buffer(environment_length,
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
	initial_environment_qm = new_vector;
    }
    else
	initial_environment_qm = Nil;
    definition_qm = M_CAR(ISVREF(rule,(SI_Long)16L));
    rule_contexts =  !EQ(definition_qm,No_value) ? 
	    M_CDR(M_CDR(definition_qm)) : Nil;
    current_computation_frame = rule;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    2);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      1);
	current_computation_flags = Current_computation_flags;
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		0);
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  | (SI_Long)8L);
	  if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		  (SI_Long)33554432L))
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	  else
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	  List_of_generated_contexts = Nil;
	  List_of_generated_contexts_tail = Nil;
	  temp = ISVREF(rule,(SI_Long)8L);
	  if ( !( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
		  (SI_Long)5L)) & (SI_Long)1L) ||  
		  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		  (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16777216L) && 
		   !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		  (SI_Long)8192L))) &&  ! !TRUEP(rule_contexts) && ( 
		  !TRUEP(focal_entity_qm) || serve_item_p(focal_entity_qm)))) {
	      if (initial_environment_qm)
		  reclaim_managed_simple_vector(initial_environment_qm);
	      result = VALUES_1(Nil);
	      POP_SPECIAL();
	      POP_SPECIAL();
	      POP_SPECIAL();
	      goto end_generate_rule_context_vectors;
	  }
	  if (local_name_qm ||  !TRUEP(focal_role_qm) ||  !((SI_Long)0L != 
		  (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16384L))) {
	      if (local_name_qm) {
		  pair = Nil;
		  ab_loop_list_ = rule_contexts;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  pair = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  focal_specifier = M_CAR(pair);
		  if (CONSP(focal_specifier) && EQ(local_name_qm,
			  M_CAR(M_CDR(focal_specifier)))) {
		      index_for_prefix = M_CAR(M_CDR(M_CDR(focal_specifier)));
		      prefix = M_CDR(pair);
		      goto end_1;
		  }
		  goto next_loop_1;
		end_loop_1:
		end_1:;
	      }
	      else {
		  pair = Nil;
		  temp = ISVREF(rule,(SI_Long)16L);
		  ab_loop_list_ = CDDAR(temp);
		next_loop_2:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_2;
		  pair = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  focal_specifier = M_CAR(pair);
		  if (SYMBOLP(focal_specifier)) {
		      if (EQ(focal_specifier,focal_role_qm)) {
			  role_for_prefix = focal_specifier;
			  index_for_prefix = FIX((SI_Long)0L);
			  prefix = M_CDR(pair);
			  goto end_2;
		      }
		  }
		  else {
		      role_for_prefix = M_CAR(focal_specifier);
		      if (EQ(role_for_prefix,focal_role_qm)) {
			  index_for_prefix = 
				  M_CAR(M_CDR(M_CDR(focal_specifier)));
			  prefix = M_CDR(pair);
			  goto end_2;
		      }
		  }
		  goto next_loop_2;
		end_loop_2:
		end_2:;
	      }
	      if (EQ(prefix,Qnone)) {
		  Suppress_warning_message_header_qm = T;
		  if ((SI_Long)3L <= IFIX(Warning_message_level))
		      give_warning_1(4,FIX((SI_Long)3L),string_constant_8,
			      rule,focal_role_qm);
		  Suppress_warning_message_header_qm = Nil;
	      }
	      else {
		  if (focal_role_qm)
		      SVREF(initial_environment_qm,index_for_prefix) = 
			      focal_entity_qm;
		  generate_rule_context_vectors_1(rule,prefix,
			  initial_environment_qm,constraint_alist);
	      }
	  }
	  else {
	      prefixes_found_qm = Nil;
	      pair = Nil;
	      ab_loop_list_ = CDR(rule_contexts);
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      pair = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      focal_specifier = M_CAR(pair);
	      if (SYMBOLP(focal_specifier)) {
		  role_for_prefix = focal_specifier;
		  index_for_prefix = FIX((SI_Long)0L);
	      }
	      else {
		  role_for_prefix = M_CAR(focal_specifier);
		  index_for_prefix = M_CAR(M_CDR(M_CDR(focal_specifier)));
	      }
	      if (EQ(role_for_prefix,focal_role_qm)) {
		  prefix = M_CDR(pair);
		  SVREF(initial_environment_qm,index_for_prefix) = 
			  focal_entity_qm;
		  generate_rule_context_vectors_1(rule,prefix,
			  initial_environment_qm,constraint_alist);
		  prefixes_found_qm = T;
	      }
	      goto next_loop_3;
	    end_loop_3:
	      if ( !TRUEP(prefixes_found_qm)) {
		  Suppress_warning_message_header_qm = T;
		  if ((SI_Long)3L <= IFIX(Warning_message_level))
		      give_warning_1(4,FIX((SI_Long)3L),string_constant_9,
			      rule,focal_role_qm);
		  Suppress_warning_message_header_qm = Nil;
	      }
	  }
	  if (initial_environment_qm)
	      reclaim_managed_simple_vector(initial_environment_qm);
	  result = VALUES_1(List_of_generated_contexts);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
  end_generate_rule_context_vectors:
    return result;
}

/* COPY-ENVIRONMENT-TO-GENERATED-LIST */
Object copy_environment_to_generated_list(rule,environment_qm)
    Object rule, environment_qm;
{
    Object new_cons, temp, svref_arg_2, svref_new_value, gensymed_symbol;
    Object new_environment, value;
    SI_Long context_length, environment_length, index_1, ab_loop_bind_;

    x_note_fn_call(152,11);
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
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
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    if (environment_qm) {
	context_length = IFIX(ISVREF(rule,(SI_Long)33L));
	environment_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(environment_qm));
	new_environment = 
		allocate_managed_simple_vector(FIX(environment_length));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = context_length;
	value = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value = ISVREF(environment_qm,index_1);
	temp = FIXNUMP(value) || value && SYMBOLP(value) || 
		SIMPLE_VECTOR_P(value) ? value : 
		copy_if_evaluation_value_1(value);
	ISVREF(new_environment,index_1) = temp;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	index_1 = context_length;
	ab_loop_bind_ = environment_length;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	ISVREF(new_environment,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	temp = new_environment;
    }
    else
	temp = Nil;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    new_environment = gensymed_symbol;
    if (List_of_generated_contexts_tail) {
	temp = List_of_generated_contexts_tail;
	M_CDR(temp) = new_environment;
	List_of_generated_contexts_tail = new_environment;
    }
    else {
	List_of_generated_contexts = new_environment;
	List_of_generated_contexts_tail = new_environment;
    }
    return VALUES_1(Nil);
}

static Object Qany;                /* any */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

static Object Qany_inverse;        /* any-inverse */

static Object Qthe_inverse;        /* the-inverse */

static Object Qthe_inverse_no_bind;  /* the-inverse-no-bind */

/* GENERATE-RULE-CONTEXT-VECTORS-1 */
Object generate_rule_context_vectors_1(rule,prefix,initial_environment_qm,
	    constraint_alist)
    Object rule, prefix, initial_environment_qm, constraint_alist;
{
    Object iterator, iteration_keyword, gensymed_symbol, role, binding;
    Object role_index, domain_index_or_name_qm, domain_value_qm;
    Object constraint_pair_qm, role_value, role_expiration, new_prefix_qm;
    Object second_cons, third_cons, fifth_cons, temp, role_continuation;
    Object reclaim_role_value_qm, new_prefix, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_2, entry_hash, gensymed_symbol_1;
    Object gensymed_symbol_2, quantifier_of_range, role_to_invert, fourth_cons;
    Object short_designation, domain_binding, sixth_cons, range_index;
    Object domain_index_or_name, range_value_qm, inverse_role_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(152,12);
    if ( !TRUEP(prefix)) {
	copy_environment_to_generated_list(rule,initial_environment_qm);
	return VALUES_1(Nil);
    }
    iterator = M_CAR(prefix);
    iteration_keyword = M_CAR(iterator);
    if (EQ(iteration_keyword,Qthe)) {
	gensymed_symbol = iterator;
	gensymed_symbol = CDR(gensymed_symbol);
	role = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	binding = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	role_index = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	domain_index_or_name_qm = CAR(gensymed_symbol);
	domain_value_qm = domain_index_or_name_qm ? 
		(FIXNUMP(domain_index_or_name_qm) ? 
		ISVREF(initial_environment_qm,
		IFIX(domain_index_or_name_qm)) : 
		evaluate_designation(domain_index_or_name_qm,Nil)) : Nil;
	constraint_pair_qm = constraint_alist ? assq_function(binding,
		constraint_alist) : Nil;
	if (domain_index_or_name_qm &&  !TRUEP(domain_value_qm))
	    return VALUES_1(Nil);
	if (constraint_pair_qm) {
	    if (value_of_role_p(M_CDR(constraint_pair_qm),Qthe,role,
		    domain_value_qm))
		result = VALUES_3(M_CDR(constraint_pair_qm),Nil,Qnever);
	    else
		result = VALUES_3(Nil,Nil,Nil);
	}
	else
	    result = serve_unique_item_or_evaluation_value_of_role(role,
		    domain_value_qm,Nil,Nil);
	MVS_2(result,role_value,role_expiration);
	if (role_expiration) {
	    SVREF(initial_environment_qm,role_index) = role_value;
	    new_prefix_qm = M_CDR(prefix);
	    if (new_prefix_qm)
		generate_rule_context_vectors_1(rule,new_prefix_qm,
			initial_environment_qm,constraint_alist);
	    else
		copy_environment_to_generated_list(rule,
			initial_environment_qm);
	    SVREF(initial_environment_qm,role_index) = Nil;
	    if ( !(FIXNUMP(role_value) || SYMBOLP(role_value) || 
		    SIMPLE_VECTOR_P(role_value)))
		return reclaim_if_evaluation_value_1(role_value);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(iteration_keyword,Qany)) {
	second_cons = M_CDR(iterator);
	role = M_CAR(second_cons);
	third_cons = M_CDR(second_cons);
	binding = M_CAR(third_cons);
	fifth_cons = M_CDR(M_CDR(third_cons));
	role_index = M_CAR(fifth_cons);
	temp = M_CDR(fifth_cons);
	domain_index_or_name_qm = CAR(temp);
	domain_value_qm = domain_index_or_name_qm ? 
		(FIXNUMP(domain_index_or_name_qm) ? 
		ISVREF(initial_environment_qm,
		IFIX(domain_index_or_name_qm)) : 
		evaluate_designation(domain_index_or_name_qm,Nil)) : Nil;
	role_value = Nil;
	role_continuation = Nil;
	role_expiration = Nil;
	reclaim_role_value_qm = Nil;
	new_prefix = M_CDR(prefix);
	constraint_pair_qm = constraint_alist ? assq_function(binding,
		constraint_alist) : Nil;
	if (domain_index_or_name_qm &&  !TRUEP(domain_value_qm))
	    return VALUES_1(Nil);
	if (constraint_pair_qm) {
	    if (value_of_role_p(M_CDR(constraint_pair_qm),Qany,role,
		    domain_value_qm))
		result = VALUES_3(CDR(constraint_pair_qm),Nil,Qnever);
	    else
		result = VALUES_3(Nil,Nil,Nil);
	}
	else
	    result = serve_first_item_or_evaluation_value_of_role(4,role,
		    domain_value_qm,Nil,Nil);
	MVS_3(result,role_value,role_continuation,role_expiration);
	if ( !TRUEP(role_expiration))
	    return VALUES_1(Nil);
	gensymed_symbol = role_value;
	temp_1 = FIXNUMP(gensymed_symbol);
	if (temp_1);
	else
	    temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ?
		     IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L;
	if (temp_1);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp_1 = EQ(gensymed_symbol,Qtruth_value);
	    if (temp_1);
	    else
		temp_1 = EQ(gensymed_symbol,Qiteration_state);
	    if (temp_1);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
		temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ?
			 (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : 
			TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    reclaim_role_value_qm = T;
	SVREF(initial_environment_qm,role_index) = role_value;
      next_loop_3:
	if (new_prefix)
	    generate_rule_context_vectors_1(rule,new_prefix,
		    initial_environment_qm,constraint_alist);
	else
	    copy_environment_to_generated_list(rule,initial_environment_qm);
	if (reclaim_role_value_qm)
	    reclaim_evaluation_value(role_value);
	if ( !TRUEP(role_continuation))
	    goto end_loop_3;
	gensymed_symbol = M_CAR(role_continuation);
	gensymed_symbol_1 = T;
	gensymed_symbol_2 = role_continuation;
	result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2);
	MVS_3(result,role_value,role_continuation,role_expiration);
	if ( !TRUEP(role_expiration))
	    goto end_loop_3;
	gensymed_symbol = role_value;
	temp = FIXNUMP(gensymed_symbol) ? T : Nil;
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = gensymed_symbol ? (SYMBOLP(gensymed_symbol) ? T : Nil) :
		     Qnil;
	if (temp);
	else
	    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L ? T : Nil;
	if (temp);
	else if (CONSP(gensymed_symbol)) {
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    temp = EQ(gensymed_symbol,Qtruth_value) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(gensymed_symbol,Qiteration_state) ? T : Nil;
	    if (temp);
	    else if (SYMBOLP(gensymed_symbol)) {
		skip_list = CDR(Defined_evaluation_value_types);
		key_value = gensymed_symbol;
		key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_5:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_6:
		if ( !TRUEP(marked))
		    goto end_loop_5;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_6;
	      end_loop_5:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		temp = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
			(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
			ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
	reclaim_role_value_qm = temp;
	SVREF(initial_environment_qm,role_index) = role_value;
	goto next_loop_3;
      end_loop_3:
	SVREF(initial_environment_qm,role_index) = Nil;
	return VALUES_1(Qnil);
    }
    else if (EQ(iteration_keyword,Qany_inverse) || EQ(iteration_keyword,
	    Qthe_inverse) || EQ(iteration_keyword,Qthe_inverse_no_bind)) {
	quantifier_of_range = EQ(iteration_keyword,Qany_inverse) ? Qany : Qthe;
	third_cons = M_CDR(M_CDR(iterator));
	role_to_invert = M_CAR(third_cons);
	fourth_cons = M_CDR(third_cons);
	short_designation = M_CAR(fourth_cons);
	fifth_cons = M_CDR(fourth_cons);
	domain_binding = M_CAR(fifth_cons);
	sixth_cons = M_CDR(fifth_cons);
	range_index = M_CAR(sixth_cons);
	domain_index_or_name = M_CAR(M_CDR(sixth_cons));
	range_value_qm = ISVREF(initial_environment_qm,IFIX(range_index));
	inverse_role_value = Nil;
	role_continuation = Nil;
	role_expiration = Nil;
	new_prefix = M_CDR(prefix);
	constraint_pair_qm = constraint_alist ? 
		assq_function(domain_binding,constraint_alist) : Nil;
	if (range_index &&  !TRUEP(range_value_qm))
	    return VALUES_1(Nil);
	if (constraint_pair_qm) {
	    if (value_of_role_p(range_value_qm,quantifier_of_range,
		    role_to_invert,M_CDR(constraint_pair_qm))) {
		inverse_role_value = M_CDR(constraint_pair_qm);
		role_continuation = Nil;
		role_expiration = Qnever;
	    }
	    else {
		inverse_role_value = Nil;
		role_continuation = Nil;
		role_expiration = Nil;
	    }
	}
	else {
	    result = serve_first_value_of_role_inverse(range_value_qm,
		    quantifier_of_range,role_to_invert,short_designation);
	    MVS_3(result,inverse_role_value,role_continuation,role_expiration);
	}
	if ( !TRUEP(role_expiration))
	    return VALUES_1(Nil);
	if (FIXNUMP(domain_index_or_name))
	    SVREF(initial_environment_qm,domain_index_or_name) = 
		    inverse_role_value;
      next_loop_7:
	if (new_prefix)
	    generate_rule_context_vectors_1(rule,new_prefix,
		    initial_environment_qm,constraint_alist);
	else
	    copy_environment_to_generated_list(rule,initial_environment_qm);
	if ( !(FIXNUMP(inverse_role_value) || SYMBOLP(inverse_role_value) 
		|| SIMPLE_VECTOR_P(inverse_role_value)))
	    reclaim_if_evaluation_value_1(inverse_role_value);
	if ( !TRUEP(role_continuation))
	    goto end_loop_7;
	gensymed_symbol = M_CAR(role_continuation);
	gensymed_symbol_1 = T;
	gensymed_symbol_2 = role_continuation;
	result = inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2);
	MVS_3(result,inverse_role_value,role_continuation,role_expiration);
	if ( !TRUEP(role_expiration))
	    goto end_loop_7;
	if (FIXNUMP(domain_index_or_name))
	    SVREF(initial_environment_qm,domain_index_or_name) = 
		    inverse_role_value;
	goto next_loop_7;
      end_loop_7:
	if (FIXNUMP(domain_index_or_name))
	    SVREF(initial_environment_qm,domain_index_or_name) = Nil;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qscanning;           /* scanning */

/* INVOKE-RULE-UNIVERSALLY */
Object invoke_rule_universally(rule)
    Object rule;
{
    Object temp;

    x_note_fn_call(152,13);
    temp = generate_and_schedule_rule_instances(rule,Nil,Nil,Nil,Qscanning,
	    Nil,Nil,Nil);
    return VALUES_1(temp);
}

Object Minus_of_logcount_most_positive_fixnum_minus_4 = UNBOUND;

Object Most_positive_fixnum_ash_minus_4 = UNBOUND;

static Object Qbackward_chaining;  /* backward-chaining */

static Object Qinitializing;       /* initializing */

/* GENERATE-AND-SCHEDULE-RULE-INSTANCES */
Object generate_and_schedule_rule_instances(rule,focal_role_qm,
	    local_name_qm,focal_object_qm,purpose,interested_party_qm,
	    priority_qm,constraint_alist)
    Object rule, focal_role_qm, local_name_qm, focal_object_qm, purpose;
    Object interested_party_qm, priority_qm, constraint_alist;
{
    Object temp, list_of_rule_context_vectors, body, maximized_priority;
    Object hash_table, rule_context_vector, ab_loop_list_, rule_context;
    Object rule_instance, existing_or_new_rule_instance, new_cons, temp_1;
    Object temp_2, svref_new_value, gensymed_symbol, vector_1, value, x2, fsn;
    Object gensymed_symbol_3, context_vector, byte_code_body;
    Object frame_serial_number_setf_arg, old, new_1;
    Object eval_push_modify_macro_arg, car_1, cdr_1, schedule_task_qm;
    Object scheduled_qm, gensymed_symbol_4, ri_priority;
    Object old_hurry_and_repeat_priority, last_1, next_qm;
    SI_Long context_length, scheduled_instance_count, hash, index_1;
    SI_Long ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2, temp_4;
    char temp_3, now_qm;

    x_note_fn_call(152,14);
    temp = ISVREF(rule,(SI_Long)8L);
    if ( !( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)8192L)))))
	return VALUES_1(FIX((SI_Long)0L));
    list_of_rule_context_vectors = generate_rule_context_vectors(rule,
	    focal_role_qm,local_name_qm,focal_object_qm,constraint_alist);
    temp = ISVREF(rule,(SI_Long)16L);
    temp = CAR(temp);
    body = SECOND(temp);
    if (priority_qm) {
	temp = ISVREF(rule,(SI_Long)26L);
	maximized_priority = FIXNUM_MIN(priority_qm,temp);
    }
    else
	maximized_priority = ISVREF(rule,(SI_Long)26L);
    hash_table = ISVREF(rule,(SI_Long)27L);
    context_length = IFIX(ISVREF(rule,(SI_Long)33L));
    scheduled_instance_count = (SI_Long)0L;
    rule_context_vector = Nil;
    ab_loop_list_ = list_of_rule_context_vectors;
    rule_context = Nil;
    rule_instance = Nil;
    existing_or_new_rule_instance = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rule_context_vector = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_eval_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_eval_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_eval_cons_pool();
    hash = (SI_Long)0L;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = context_length;
    vector_1 = rule_context_vector;
    value = Nil;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    value = ISVREF(vector_1,index_1);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(value,(SI_Long)1L);
	temp_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	hash = IFIX(ash(FIX(hash),
		Minus_of_logcount_most_positive_fixnum_minus_4)) + ((hash 
		& IFIX(Most_positive_fixnum_ash_minus_4)) << (SI_Long)3L);
	gensymed_symbol_1 = hash;
	fsn = ISVREF(value,(SI_Long)3L);
	gensymed_symbol_2 = FIXNUMP(fsn) ? IFIX(fsn) : 
		IFIX(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
	hash = gensymed_symbol_1 ^ gensymed_symbol_2;
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    temp_1 = FIX(hash);
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    M_CAR(gensymed_symbol) = temp_1;
    new_cons = ISVREF(Available_eval_conses_vector,IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_eval_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_eval_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol_3 = new_cons;
    }
    else
	gensymed_symbol_3 = Nil;
    if ( !TRUEP(gensymed_symbol_3))
	gensymed_symbol_3 = replenish_eval_cons_pool();
    M_CAR(gensymed_symbol_3) = FIX(context_length);
    M_CDR(gensymed_symbol_3) = rule_context_vector;
    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
    M_CDR(gensymed_symbol) = gensymed_symbol_3;
    inline_note_allocate_cons(gensymed_symbol,Qeval);
    rule_context = gensymed_symbol;
    rule_instance = make_rule_instance_1();
    gensymed_symbol_1 = IFIX(M_CAR(rule_context));
    temp_4 = gensymed_symbol_1 % (SI_Long)43L;
    existing_or_new_rule_instance = set_skip_list_entry(SVREF(hash_table,
	    FIX(temp_4)),FIX((SI_Long)31L),Qequal_rule_context,Nil,Nil,
	    rule_context,FIX(gensymed_symbol_1),rule_instance);
    if ( !EQ(rule_instance,existing_or_new_rule_instance)) {
	temp_3 = EQ(existing_or_new_rule_instance,
		Current_computation_instance);
	if (temp_3);
	else {
	    context_vector = ISVREF(existing_or_new_rule_instance,(SI_Long)2L);
	    temp_3 = TRUEP(valid_rule_context_vector_p(context_vector,
		    ISVREF(rule,(SI_Long)34L),
		    ISVREF(existing_or_new_rule_instance,(SI_Long)11L),
		    rule,Nil));
	}
	if ( !temp_3) {
	    existing_or_new_rule_instance = rule_instance;
	    gensymed_symbol_1 = IFIX(M_CAR(rule_context));
	    temp_4 = gensymed_symbol_1 % (SI_Long)43L;
	    set_skip_list_entry(SVREF(hash_table,FIX(temp_4)),
		    FIX((SI_Long)31L),Qequal_rule_context,
		    Fp_mutate_hashed_rule_instance_tree_for_hash_skip_list_entry,
		    T,rule_context,FIX(gensymed_symbol_1),rule_instance);
	}
    }
    if (EQ(rule_instance,existing_or_new_rule_instance)) {
	scheduled_instance_count = scheduled_instance_count + (SI_Long)1L;
	SVREF(rule_instance,FIX((SI_Long)8L)) = rule;
	gensymed_symbol = ACCESS_ONCE(ISVREF(rule,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	SVREF(rule_instance,FIX((SI_Long)25L)) = gensymed_symbol;
	byte_code_body = ISVREF(rule,(SI_Long)31L);
	SVREF(rule_instance,FIX((SI_Long)1L)) = byte_code_body;
	temp_1 = ISVREF(byte_code_body,(SI_Long)3L);
	SVREF(rule_instance,FIX((SI_Long)4L)) = temp_1;
	temp_1 = ISVREF(rule,(SI_Long)36L);
	SVREF(rule_instance,FIX((SI_Long)6L)) = temp_1;
	temp_1 = ISVREF(rule,(SI_Long)35L);
	SVREF(rule_instance,FIX((SI_Long)5L)) = temp_1;
	SVREF(rule_instance,FIX((SI_Long)9L)) = body;
	SVREF(rule_instance,FIX((SI_Long)10L)) = rule_context;
	SVREF(rule_instance,FIX((SI_Long)2L)) = rule_context_vector;
	if (explanation_related_features_enabled_func_qm()) {
	    temp_1 = M_CAR(rule_context);
	    SVREF(rule_instance,FIX((SI_Long)22L)) = temp_1;
	}
	frame_serial_number_setf_arg = Current_frame_serial_number;
	old = ISVREF(rule_instance,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	temp_1 = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(rule_instance,FIX((SI_Long)11L)) = temp_1;
	SVREF(rule_instance,FIX((SI_Long)14L)) = maximized_priority;
	if (EQ(purpose,Qbackward_chaining)) {
	    temp_1 = eval_cons_1(eval_cons_1(Qbackward_chaining,
		    interested_party_qm),Nil);
	    SVREF(rule_instance,FIX((SI_Long)16L)) = temp_1;
	    add_rule_instance_to_variable_interests(interested_party_qm,
		    rule_instance);
	}
	else {
	    temp_1 = eval_cons_1(purpose,Nil);
	    SVREF(rule_instance,FIX((SI_Long)16L)) = temp_1;
	}
	if (Profiling_enabled_qm)
	    increment_profiling_calls(ISVREF(existing_or_new_rule_instance,
		    (SI_Long)8L));
	ISVREF(rule_instance,(SI_Long)19L) = FIX((SI_Long)0L);
	ISVREF(rule_instance,(SI_Long)3L) = FIX((SI_Long)0L);
	SVREF(rule_instance,FIX((SI_Long)15L)) = Nil;
	temp_1 = Gensym_time;
	SVREF(rule_instance,FIX((SI_Long)18L)) = temp_1;
	temp_1 = Window_instigating_this_rule_instance_qm;
	SVREF(rule_instance,FIX((SI_Long)20L)) = temp_1;
	SVREF(rule_instance,FIX((SI_Long)27L)) = Nil;
	SVREF(rule_instance,FIX((SI_Long)28L)) = Nil;
	add_rule_instance_to_dynamic_rule_displays(rule_instance);
	add_rule_instance_to_generic_rule_displays(rule_instance);
	if (Current_ri_completion_notification_collection_qm) {
	    temp_1 = Current_ri_completion_notification_collection_qm;
	    eval_push_modify_macro_arg = rule_instance;
	    car_1 = eval_push_modify_macro_arg;
	    cdr_1 = M_CAR(temp_1);
	    temp_2 = eval_cons_1(car_1,cdr_1);
	    M_CAR(temp_1) = temp_2;
	    temp_1 = Current_ri_completion_notification_collection_qm;
	    SVREF(rule_instance,FIX((SI_Long)26L)) = temp_1;
	}
	schedule_computation_instance_execution(rule_instance,
		maximized_priority,rule);
    }
    else {
	reclaim_rule_context(rule_context);
	reclaim_rule_instance_1(rule_instance);
	schedule_task_qm = ISVREF(existing_or_new_rule_instance,(SI_Long)7L);
	scheduled_qm = schedule_task_qm ? ISVREF(schedule_task_qm,
		(SI_Long)6L) : Qnil;
	now_qm = EQ(existing_or_new_rule_instance,
		Current_computation_instance);
	if (EQ(purpose,Qbackward_chaining)) {
	    temp_1 = eval_cons_1(eval_cons_1(Qbackward_chaining,
		    interested_party_qm),
		    ISVREF(existing_or_new_rule_instance,(SI_Long)16L));
	    SVREF(existing_or_new_rule_instance,FIX((SI_Long)16L)) = temp_1;
	    add_rule_instance_to_variable_interests(interested_party_qm,
		    existing_or_new_rule_instance);
	}
	else {
	    if (scheduled_qm && EQ(purpose,Qinitializing))
		scheduled_instance_count = scheduled_instance_count + 
			(SI_Long)1L;
	    gensymed_symbol = ISVREF(existing_or_new_rule_instance,
		    (SI_Long)16L);
	    gensymed_symbol_3 = purpose;
	    if ( !TRUEP(memq_function(gensymed_symbol_3,gensymed_symbol))) {
		new_cons = ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_1 = Available_eval_conses_vector;
		    temp_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_1,temp_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_1 = Available_eval_conses_tail_vector;
			temp_2 = Current_thread_index;
			SVREF(temp_1,temp_2) = Nil;
		    }
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_eval_cons_pool();
		M_CAR(gensymed_symbol_4) = gensymed_symbol_3;
		M_CDR(gensymed_symbol_4) = gensymed_symbol;
		inline_note_allocate_cons(gensymed_symbol_4,Qeval);
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)16L)) = 
			gensymed_symbol_4;
	    }
	}
	if ((SI_Long)0L != IFIX(ISVREF(existing_or_new_rule_instance,
		(SI_Long)19L))) {
	    if ( !TRUEP(scheduled_qm)) {
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)15L)) = 
			maximized_priority;
		ri_priority = ISVREF(existing_or_new_rule_instance,
			(SI_Long)14L);
		if (FIXNUM_LT(maximized_priority,ri_priority)) {
		    SVREF(existing_or_new_rule_instance,FIX((SI_Long)14L)) 
			    = maximized_priority;
		    schedule_computation_instance_execution(existing_or_new_rule_instance,
			    maximized_priority,rule);
		}
		else
		    schedule_computation_instance_execution(existing_or_new_rule_instance,
			    ri_priority,rule);
	    }
	    else if (now_qm) {
		old_hurry_and_repeat_priority = 
			ISVREF(existing_or_new_rule_instance,(SI_Long)15L);
		temp_1 =  !TRUEP(old_hurry_and_repeat_priority) ? 
			maximized_priority : FIXNUM_MIN(maximized_priority,
			old_hurry_and_repeat_priority);
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)15L)) = 
			temp_1;
	    }
	    else if (FIXNUM_LT(maximized_priority,
		    ISVREF(existing_or_new_rule_instance,(SI_Long)14L))) {
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)14L)) = 
			maximized_priority;
		old_hurry_and_repeat_priority = 
			ISVREF(existing_or_new_rule_instance,(SI_Long)15L);
		temp_1 =  !TRUEP(old_hurry_and_repeat_priority) ? 
			maximized_priority : FIXNUM_MIN(maximized_priority,
			old_hurry_and_repeat_priority);
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)15L)) = 
			temp_1;
		schedule_computation_instance_execution(existing_or_new_rule_instance,
			maximized_priority,rule);
	    }
	}
	else if ( !TRUEP(scheduled_qm)) {
	    scheduled_instance_count = scheduled_instance_count + (SI_Long)1L;
	    ri_priority = ISVREF(existing_or_new_rule_instance,(SI_Long)14L);
	    if (FIXNUM_LT(maximized_priority,ri_priority)) {
		SVREF(existing_or_new_rule_instance,FIX((SI_Long)14L)) = 
			maximized_priority;
		schedule_computation_instance_execution(existing_or_new_rule_instance,
			maximized_priority,rule);
	    }
	    else
		schedule_computation_instance_execution(existing_or_new_rule_instance,
			ri_priority,rule);
	}
	else if (now_qm || FIXNUM_GE(maximized_priority,
		ISVREF(existing_or_new_rule_instance,(SI_Long)14L)));
	else {
	    SVREF(existing_or_new_rule_instance,FIX((SI_Long)14L)) = 
		    maximized_priority;
	    schedule_computation_instance_execution(existing_or_new_rule_instance,
		    maximized_priority,rule);
	}
    }
    goto next_loop;
  end_loop:
    if (list_of_rule_context_vectors) {
	last_1 = list_of_rule_context_vectors;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qeval);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp_1 = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp_1) = list_of_rule_context_vectors;
	    temp_1 = Available_eval_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = last_1;
	}
	else {
	    temp_1 = Available_eval_conses_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = list_of_rule_context_vectors;
	    temp_1 = Available_eval_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    temp = FIX(scheduled_instance_count);
    goto end_2;
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* REMOVE-REQUEST-FOR-RULE-INSTANCE-INVOCATION */
Object remove_request_for_rule_instance_invocation(rule_instance,variable)
    Object rule_instance, variable;
{
    Object trailing_cons, leading_cons, item, temp, cdr_1, gensymed_symbol;
    Object temp_1, old_key, old_entry, svref_arg_2;
    SI_Long gensymed_symbol_1, temp_2;
    Object result;

    x_note_fn_call(152,15);
    trailing_cons = Nil;
    leading_cons = ISVREF(rule_instance,(SI_Long)16L);
    item = Nil;
  next_loop:
    if ( !TRUEP(leading_cons))
	goto end_loop;
    item = M_CAR(leading_cons);
    if (CONSP(item) && EQ(M_CDR(item),variable)) {
	if (trailing_cons) {
	    temp = M_CDR(leading_cons);
	    M_CDR(trailing_cons) = temp;
	}
	else {
	    cdr_1 = M_CDR(leading_cons);
	    SVREF(rule_instance,FIX((SI_Long)16L)) = cdr_1;
	    if ( !(cdr_1 || EQ(rule_instance,Current_computation_instance))) {
		gensymed_symbol = ISVREF(rule_instance,(SI_Long)10L);
		gensymed_symbol_1 = IFIX(M_CAR(gensymed_symbol));
		temp_1 = ISVREF(ISVREF(rule_instance,(SI_Long)8L),
			(SI_Long)27L);
		temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
			gensymed_symbol,SVREF(temp_1,FIX(temp_2)),
			FIX((SI_Long)31L),FIX(gensymed_symbol_1));
		MVS_2(result,old_key,old_entry);
		if (old_key)
		    reclaim_rule_context(old_key);
		if (old_entry)
		    dismiss_rule_instance(old_entry);
	    }
	}
	inline_note_reclaim_cons(leading_cons,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = leading_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = leading_cons;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = leading_cons;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = leading_cons;
	}
	M_CDR(leading_cons) = Nil;
	inline_note_reclaim_cons(item,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = item;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = item;
	}
	M_CDR(item) = Nil;
	return VALUES_1(Nil);
    }
    trailing_cons = leading_cons;
    leading_cons = M_CDR(leading_cons);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAXIMIZE-PRIORITY-OF-RULE-INSTANCE */
Object maximize_priority_of_rule_instance(rule_instance,new_priority)
    Object rule_instance, new_priority;
{
    Object change_priority_of_task_arg, schedule_task_qm, priority, temp;
    Object structure_being_reclaimed, svref_arg_2, variable, ab_loop_list_;
    Declare_special(1);

    x_note_fn_call(152,16);
    if (FIXNUM_LT(new_priority,ISVREF(rule_instance,(SI_Long)14L))) {
	SVREF(rule_instance,FIX((SI_Long)14L)) = new_priority;
	change_priority_of_task_arg = new_priority;
	schedule_task_qm = ISVREF(rule_instance,(SI_Long)7L);
	priority = change_priority_of_task_arg;
	if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
		EQ(schedule_task_qm,Current_schedule_task))) {
	    if ( !FIXNUM_EQ(ISVREF(schedule_task_qm,(SI_Long)4L),priority)) {
		if (ISVREF(schedule_task_qm,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		if (EQ(schedule_task_qm,Current_schedule_task))
		    Current_schedule_task = Nil;
		SVREF(schedule_task_qm,FIX((SI_Long)4L)) = priority;
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
	SVREF(rule_instance,FIX((SI_Long)7L)) = temp;
	variable = Nil;
	ab_loop_list_ = ISVREF(rule_instance,(SI_Long)17L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	variable = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	maximize_priority_of_variable(variable,new_priority);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

static Object Qab_if;              /* if */

/* RULE-ANTECEDENT-PARSE */
Object rule_antecedent_parse(rule)
    Object rule;
{
    Object gensymed_symbol, if_or_rule_let, antecedent_or_bindings;
    Object consequent_or_normalized_parse;

    x_note_fn_call(152,17);
    gensymed_symbol = ISVREF(rule,(SI_Long)16L);
    gensymed_symbol = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CAR(gensymed_symbol);
    if_or_rule_let = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    antecedent_or_bindings = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    consequent_or_normalized_parse = CAR(gensymed_symbol);
    return VALUES_1(EQ(if_or_rule_let,Qab_if) ? antecedent_or_bindings : 
	    SECOND(consequent_or_normalized_parse));
}

/* RULE-CONSEQUENT-PARSE */
Object rule_consequent_parse(rule)
    Object rule;
{
    Object gensymed_symbol, if_or_rule_let, consequent_or_normalized_parse;

    x_note_fn_call(152,18);
    gensymed_symbol = ISVREF(rule,(SI_Long)16L);
    gensymed_symbol = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CAR(gensymed_symbol);
    if_or_rule_let = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    consequent_or_normalized_parse = CAR(gensymed_symbol);
    return VALUES_1(EQ(if_or_rule_let,Qab_if) ? 
	    consequent_or_normalized_parse : 
	    THIRD(consequent_or_normalized_parse));
}

/* RULE-BINDINGS-PARSE */
Object rule_bindings_parse(rule)
    Object rule;
{
    Object gensymed_symbol, bindings;

    x_note_fn_call(152,19);
    gensymed_symbol = ISVREF(rule,(SI_Long)16L);
    gensymed_symbol = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    bindings = CAR(gensymed_symbol);
    return VALUES_1(bindings);
}

/* NORMALIZE-RULE-PARSE */
Object normalize_rule_parse(rule)
    Object rule;
{
    Object temp, temp_1;

    x_note_fn_call(152,20);
    temp = rule_antecedent_parse(rule);
    temp_1 = rule_consequent_parse(rule);
    return slot_value_list_3(temp,temp_1,rule_bindings_parse(rule));
}

/* ALL-CLAUSES-CONGRUENT-P */
Object all_clauses_congruent_p(clauses1,clauses2,test)
    Object clauses1, clauses2, test;
{
    Object elt1, ab_loop_list_, elt2, ab_loop_list__1, temp_1;
    char temp;

    x_note_fn_call(152,21);
    if (LISTP(clauses1) && LISTP(clauses2)) {
	elt1 = Nil;
	ab_loop_list_ = clauses1;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	elt2 = Nil;
	ab_loop_list__1 = clauses2;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	elt2 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (FUNCALL_2(test,elt1,elt2)) {
	    temp = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	if ( !temp) {
	    temp_1 = Nil;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	temp_1 = T;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
    }
    else
	temp_1 = EQ(clauses1,clauses2) ? T : Nil;
    return VALUES_1(temp_1);
}

static Object Qslot_value_equal_p;  /* slot-value-equal-p */

/* RULE-PARSE-ANTECEDENTS-EQUIVALENT-P */
Object rule_parse_antecedents_equivalent_p(normalized_parse1,normalized_parse2)
    Object normalized_parse1, normalized_parse2;
{
    Object antecedent1, antecedent2, bindings1, bindings2, temp;

    x_note_fn_call(152,22);
    antecedent1 = FIRST(normalized_parse1);
    antecedent2 = FIRST(normalized_parse2);
    bindings1 = THIRD(normalized_parse1);
    bindings2 = THIRD(normalized_parse2);
    temp = all_clauses_congruent_p(antecedent1,antecedent2,
	    SYMBOL_FUNCTION(Qslot_value_equal_p)) && 
	    all_clauses_congruent_p(antecedent2,antecedent1,
	    SYMBOL_FUNCTION(Qslot_value_equal_p)) ? 
	    (all_clauses_congruent_p(bindings1,bindings2,
	    SYMBOL_FUNCTION(Qequal)) ? all_clauses_congruent_p(bindings2,
	    bindings1,SYMBOL_FUNCTION(Qequal)) : Qnil) : Qnil;
    return VALUES_1(temp);
}

/* RULE-PARSE-CONSEQUENTS-EQUIVALENT-P */
Object rule_parse_consequents_equivalent_p(normalized_parse1,normalized_parse2)
    Object normalized_parse1, normalized_parse2;
{
    Object temp;

    x_note_fn_call(152,23);
    temp = slot_value_equal_p(SECOND(normalized_parse1),
	    SECOND(normalized_parse2));
    return VALUES_1(temp);
}

/* RULE-PARSES-REDUNDANT-P */
Object rule_parses_redundant_p(normalized_parse1,normalized_parse2)
    Object normalized_parse1, normalized_parse2;
{
    Object temp;

    x_note_fn_call(152,24);
    temp = rule_parse_antecedents_equivalent_p(normalized_parse1,
	    normalized_parse2) ? 
	    rule_parse_consequents_equivalent_p(normalized_parse1,
	    normalized_parse2) : Qnil;
    return VALUES_1(temp);
}

/* CREATE-CLIQUES-FROM-GROUPINGS */
Object create_cliques_from_groupings(groups)
    Object groups;
{
    Object results, starter, ab_loop_list_, ab_loop_desetq_, partials, partial;
    Object ab_loop_list__1;

    x_note_fn_call(152,25);
    results = Nil;
    starter = Nil;
    ab_loop_list_ = CAR(groups);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    starter = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    partials = create_cliques_from_groupings(CDR(groups));
    if (partials) {
	partial = Nil;
	ab_loop_list__1 = partials;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	partial = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	results = eval_cons_1(eval_cons_1(starter,partial),results);
	goto next_loop_1;
      end_loop_1:
	reclaim_eval_list_1(partials);
    }
    else
	results = eval_cons_1(eval_cons_1(starter,Nil),results);
    goto next_loop;
  end_loop:;
    return VALUES_1(results);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_10;  /* "All elements of ~NV must be rules and have a ~
				    *                              status of OK.~%~%"
				    */

static Object string_constant_11;  /* "The following elements are not items: " */

static Object string_constant_12;  /* "and" */

static Object string_constant_13;  /* "~NV" */

static Object string_constant_14;  /* ".~%~%" */

static Object string_constant_15;  /* "The following elements are items but not rules: " */

static Object string_constant_16;  /* "~NF" */

static Object string_constant_17;  /* "The following elements are rules which are not OK: " */

static Object string_constant_18;  /* "." */

/* SANITY-CHECK-RULES-FOR-VALIDATION */
Object sanity_check_rules_for_validation(seq)
    Object seq;
{
    Object gensymed_symbol, held_vector, elt_1, non_frames, ab_loopvar_;
    Object ab_loopvar__1, non_rules, ab_loopvar__2, not_ok, ab_loopvar__3;
    Object elt_2, validated_elt, x2, sub_class_bit_vector, temp_1;
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long next_index, length_1, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    char temp;
    Declare_special(7);

    x_note_fn_call(152,26);
    gensymed_symbol = seq;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    elt_1 = Nil;
    non_frames = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    non_rules = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__1 = Nil;
    not_ok = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__1 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_2 ? validate_item_or_evaluation_value(elt_2,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    elt_1 = validated_elt;
    if (SIMPLE_VECTOR_P(elt_1) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(elt_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(elt_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	ab_loopvar__1 = gensym_cons_1(elt_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    non_frames = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(elt_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	if ( !temp) {
	    ab_loopvar__1 = gensym_cons_1(elt_1,Nil);
	    if (ab_loopvar__2)
		M_CDR(ab_loopvar__2) = ab_loopvar__1;
	    else
		non_rules = ab_loopvar__1;
	    ab_loopvar__2 = ab_loopvar__1;
	}
	else {
	    temp_1 = ISVREF(elt_1,(SI_Long)8L);
	    if ( ! !TRUEP(CAR(temp_1))) {
		ab_loopvar__1 = gensym_cons_1(elt_1,Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__1;
		else
		    not_ok = ab_loopvar__1;
		ab_loopvar__3 = ab_loopvar__1;
	    }
	}
    }
    goto next_loop;
  end_loop:
    if (non_frames || non_rules || not_ok) {
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
		  length_2 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_2 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_10,seq);
		      if (non_frames) {
			  tformat(1,string_constant_11);
			  write_list_in_chicago_style_given_format(non_frames,
				  string_constant_12,string_constant_13);
			  tformat(1,string_constant_14);
		      }
		      if (non_rules) {
			  tformat(1,string_constant_15);
			  write_list_in_chicago_style_given_format(non_rules,
				  string_constant_12,string_constant_16);
			  tformat(1,string_constant_14);
		      }
		      if (not_ok) {
			  tformat(1,string_constant_17);
			  write_list_in_chicago_style_given_format(not_ok,
				  string_constant_12,string_constant_16);
			  tformat(1,string_constant_18);
		      }
		      reclaim_gensym_list_1(non_frames);
		      reclaim_gensym_list_1(non_rules);
		      reclaim_gensym_list_1(not_ok);
		      reclaim_evaluation_sequence(seq);
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
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(Nil);
}

/* GATHER-NORMALIZED-RULE-PARSES-FOR-VALIDATION */
Object gather_normalized_rule_parses_for_validation(seq)
    Object seq;
{
    Object gensymed_symbol, held_vector, rule, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(152,27);
    gensymed_symbol = seq;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    rule = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
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
    rule = validated_elt;
    temp = rule;
    ab_loopvar__2 = eval_cons_1(eval_list_2(temp,
	    normalize_rule_parse(rule)),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CONTRUCT-RULE-VALIDATION-RETURN-VALUE */
Object contruct_rule_validation_return_value(clique_groups)
    Object clique_groups;
{
    Object elts, cliques, ab_loop_list_, clique, ab_loop_list__1, temp;

    x_note_fn_call(152,28);
    elts = Nil;
    cliques = Nil;
    ab_loop_list_ = clique_groups;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    cliques = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    clique = Nil;
    ab_loop_list__1 = cliques;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    clique = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = allocate_evaluation_sequence(clique);
    elts = eval_cons_1(temp,elts);
    goto next_loop_1;
  end_loop_1:
    reclaim_eval_list_1(cliques);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(clique_groups);
    temp = allocate_evaluation_sequence(elts);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-RULES-ACCORDING-TO-PARSE-CRITERIA */
Object get_rules_according_to_parse_criteria(seq,row_selector,
	    group_selector_qm)
    Object seq, row_selector, group_selector_qm;
{
    Object results, normalized_parses, rule, parse, ab_loop_list_;
    Object ab_loop_desetq_, temp, row, ab_loop_list__1;
    Object possibly_row_equivalent_parse, candidates_qm, new_row, group;
    Object candidate_rule, candidate_parse, eval_push_modify_macro_arg, car_1;
    Object cdr_1, cdr_new_value, groupings, clique_groups, ab_loopvar_;
    Object ab_loopvar__1, entry, ab_loop_list__2, rule_parse_pair;
    Object normalized_parse, temp_1;
    Declare_special(1);

    x_note_fn_call(152,29);
    sanity_check_rules_for_validation(seq);
    results = Nil;
    normalized_parses = gather_normalized_rule_parses_for_validation(seq);
    rule = Nil;
    parse = Nil;
    ab_loop_list_ = normalized_parses;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    rule = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    parse = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    row = Nil;
    ab_loop_list__1 = results;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
      possibly_row_equivalent_parse = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      Row = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      temp = CAR(Row);
      temp = CAR(temp);
      temp = CDR(temp);
      possibly_row_equivalent_parse = CAR(temp);
      if (FUNCALL_2(row_selector,parse,possibly_row_equivalent_parse)) {
	  candidates_qm = Row;
	  goto end_1;
      }
      goto next_loop_1;
    end_loop_1:
      new_row = eval_cons_1(eval_cons_1(eval_list_2(rule,parse),Nil),Nil);
      results = eval_cons_1(new_row,results);
      candidates_qm = Qnil;
    end_1:;
    POP_SPECIAL();
    if (candidates_qm) {
	if (group_selector_qm) {
	    group = Nil;
	    ab_loop_list__1 = candidates_qm;
	    candidate_rule = Nil;
	    candidate_parse = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    group = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp = CAR(group);
	    candidate_rule = CAR(temp);
	    temp = CAR(group);
	    temp = CDR(temp);
	    candidate_parse = CAR(temp);
	    if (FUNCALL_2(group_selector_qm,parse,candidate_parse)) {
		eval_push_modify_macro_arg = eval_list_2(rule,parse);
		car_1 = eval_push_modify_macro_arg;
		cdr_1 = CDR(group);
		cdr_new_value = eval_cons_1(car_1,cdr_1);
		M_CDR(group) = cdr_new_value;
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    eval_push_modify_macro_arg = eval_cons_1(eval_list_2(rule,
		    parse),Nil);
	    car_1 = eval_push_modify_macro_arg;
	    cdr_1 = CDR(candidates_qm);
	    cdr_new_value = eval_cons_1(car_1,cdr_1);
	    M_CDR(candidates_qm) = cdr_new_value;
	  end_2:;
	}
	else {
	    eval_push_modify_macro_arg = eval_cons_1(eval_list_2(rule,
		    parse),Nil);
	    car_1 = eval_push_modify_macro_arg;
	    cdr_1 = CDR(candidates_qm);
	    cdr_new_value = eval_cons_1(car_1,cdr_1);
	    M_CDR(candidates_qm) = cdr_new_value;
	}
    }
    goto next_loop;
  end_loop:
    groupings = Nil;
    ab_loop_list_ = results;
    clique_groups = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    groupings = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CDR(groupings)) {
	ab_loopvar__1 = 
		eval_cons_1(create_cliques_from_groupings(groupings),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    clique_groups = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop_3;
  end_loop_3:
    temp = contruct_rule_validation_return_value(clique_groups);
    goto end_3;
    temp = Qnil;
  end_3:;
    row = Nil;
    ab_loop_list_ = results;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop_4:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_4;
      Row = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      group = Nil;
      ab_loop_list__1 = Row;
    next_loop_5:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_5;
      group = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      entry = Nil;
      ab_loop_list__2 = group;
    next_loop_6:
      if ( !TRUEP(ab_loop_list__2))
	  goto end_loop_6;
      entry = M_CAR(ab_loop_list__2);
      ab_loop_list__2 = M_CDR(ab_loop_list__2);
      reclaim_eval_list_1(entry);
      goto next_loop_6;
    end_loop_6:
      reclaim_eval_list_1(group);
      goto next_loop_5;
    end_loop_5:
      reclaim_eval_list_1(Row);
      goto next_loop_4;
    end_loop_4:
      reclaim_eval_list_1(results);
    POP_SPECIAL();
    rule_parse_pair = Nil;
    ab_loop_list_ = normalized_parses;
    normalized_parse = Nil;
  next_loop_7:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_7;
    rule_parse_pair = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = CDR(rule_parse_pair);
    normalized_parse = CAR(temp_1);
    reclaim_eval_list_1(normalized_parse);
    reclaim_eval_list_1(rule_parse_pair);
    goto next_loop_7;
  end_loop_7:
    reclaim_eval_list_1(normalized_parses);
    goto end_4;
    temp = Qnil;
  end_4:;
    return VALUES_1(temp);
}

static Object Qrule_parse_consequents_equivalent_p;  /* rule-parse-consequents-equivalent-p */

static Object Qrule_parse_antecedents_equivalent_p;  /* rule-parse-antecedents-equivalent-p */

/* G2-GET-COLLIDING-RULES */
Object g2_get_colliding_rules(no_col_gensymed_symbol_as_evaluation_value)
    Object no_col_gensymed_symbol_as_evaluation_value;
{
    Object gensymed_symbol, value_1, temp;

    x_note_fn_call(152,30);
    gensymed_symbol = IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    value_1 = Nil;
    temp = get_rules_according_to_parse_criteria(gensymed_symbol,
	    SYMBOL_FUNCTION(Qrule_parse_consequents_equivalent_p),
	    SYMBOL_FUNCTION(Qrule_parse_antecedents_equivalent_p));
    reclaim_evaluation_sequence(gensymed_symbol);
    value_1 = temp;
    IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* G2-GET-CONFLICTING-RULES */
Object g2_get_conflicting_rules(no_col_gensymed_symbol_as_evaluation_value)
    Object no_col_gensymed_symbol_as_evaluation_value;
{
    Object gensymed_symbol, value_1, temp;

    x_note_fn_call(152,31);
    gensymed_symbol = IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    value_1 = Nil;
    temp = get_rules_according_to_parse_criteria(gensymed_symbol,
	    SYMBOL_FUNCTION(Qrule_parse_antecedents_equivalent_p),
	    SYMBOL_FUNCTION(Qrule_parse_consequents_equivalent_p));
    reclaim_evaluation_sequence(gensymed_symbol);
    value_1 = temp;
    IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

static Object Qrule_parses_redundant_p;  /* rule-parses-redundant-p */

/* G2-GET-REDUNDANT-RULES */
Object g2_get_redundant_rules(no_col_gensymed_symbol_as_evaluation_value)
    Object no_col_gensymed_symbol_as_evaluation_value;
{
    Object gensymed_symbol, value_1, temp;

    x_note_fn_call(152,32);
    gensymed_symbol = IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    value_1 = Nil;
    temp = get_rules_according_to_parse_criteria(gensymed_symbol,
	    SYMBOL_FUNCTION(Qrule_parses_redundant_p),Nil);
    reclaim_evaluation_sequence(gensymed_symbol);
    value_1 = temp;
    IDENTITY(no_col_gensymed_symbol_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

static Object Qrule_priority;      /* rule-priority */

/* PUT-RULE-PRIORITY */
Object put_rule_priority(rule,new_priority,gensymed_symbol)
    Object rule, new_priority, gensymed_symbol;
{
    Object old_priority, rule_scan_interval_qm, hash_table_qm, temp;
    Object schedule_task_qm, change_priority_of_task_arg, priority, temp_2;
    Object structure_being_reclaimed, svref_arg_2, scope_conses;
    Object ab_hash_table_, ab_tree_form_, ab_node_stack_, ab_current_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_skip_list_p_, ab_tail_node_;
    Object rule_instance, ab_less_than_branch_qm_;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(152,33);
    old_priority = ISVREF(rule,(SI_Long)26L);
    rule_scan_interval_qm = ISVREF(rule,(SI_Long)20L);
    hash_table_qm = ISVREF(rule,(SI_Long)27L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_priority);
    SVREF(rule,FIX((SI_Long)26L)) = new_priority;
    temp = ISVREF(rule,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)8192L))) && FIXNUM_NE(old_priority,
	    new_priority)) {
	if (rule_scan_interval_qm) {
	    schedule_task_qm = ISVREF(rule,(SI_Long)21L);
	    temp_1 = schedule_task_qm ? ISVREF(schedule_task_qm,
		    (SI_Long)6L) || EQ(schedule_task_qm,
		    Current_schedule_task) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    change_priority_of_task_arg = new_priority;
	    schedule_task_qm = ISVREF(rule,(SI_Long)21L);
	    priority = change_priority_of_task_arg;
	    if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) 
		    || EQ(schedule_task_qm,Current_schedule_task))) {
		if ( !FIXNUM_EQ(ISVREF(schedule_task_qm,(SI_Long)4L),
			    priority)) {
		    if (ISVREF(schedule_task_qm,(SI_Long)6L))
			cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		    if (EQ(schedule_task_qm,Current_schedule_task))
			Current_schedule_task = Nil;
		    SVREF(schedule_task_qm,FIX((SI_Long)4L)) = priority;
		    future_task_schedule_2(schedule_task_qm);
		}
		temp_2 = schedule_task_qm;
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
		    temp_2 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp_2;
		    temp_2 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = schedule_task_qm;
		}
		temp_2 = Nil;
	    }
	    ISVREF(rule,(SI_Long)21L) = temp_2;
	}
	if (hash_table_qm) {
	    scope_conses = Scope_conses;
	    ab_hash_table_ = hash_table_qm;
	    ab_table_length_ = (SI_Long)0L;
	    ab_index_ = (SI_Long)0L;
	    ab_tree_form_ = Nil;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_skip_list_p_ = Nil;
	    ab_tail_node_ = Nil;
	    rule_instance = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    1);
	      ab_table_length_ = 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	    next_loop:
	      if (ab_current_alist_) {
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	      else if (ab_current_node_ && ab_skip_list_p_) {
		  ab_current_node_ = 
			  ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L));
		  if (EQ(ab_current_node_,ab_tail_node_))
		      ab_current_node_ = Nil;
		  else
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			      (SI_Long)2L),ISVREF(ab_current_node_,
			      (SI_Long)3L));
	      }
	      else if (ab_current_node_) {
		  ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  if (ab_current_node_) {
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_1:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_1;
		    end_loop:;
		  }
		  else if (ab_node_stack_) {
		      ab_current_node_ = M_CAR(ab_node_stack_);
		      ab_node_stack_ = M_CDR(ab_node_stack_);
		  }
		  if (ab_current_node_) {
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		  }
	      }
	      if ( !TRUEP(ab_current_node_)) {
		next_loop_2:
		  if ( !(ab_index_ < ab_table_length_))
		      goto end_loop_1;
		  ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		  if (ab_index_ == (SI_Long)0L) {
		      gensymed_symbol = CDR(ab_tree_form_);
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
		  }
		  ab_index_ = ab_index_ + (SI_Long)1L;
		  if (ab_skip_list_p_) {
		      ab_current_node_ = 
			      ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_tree_form_)),
			      (SI_Long)0L),(SI_Long)0L));
		      ab_tail_node_ = M_CDR(M_CDR(ab_tree_form_));
		      if (EQ(ab_current_node_,ab_tail_node_))
			  ab_current_node_ = Nil;
		      else {
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
				  (SI_Long)2L),ISVREF(ab_current_node_,
				  (SI_Long)3L));
			  goto end_loop_1;
		      }
		  }
		  else {
		      ab_current_node_ = CDR(ab_tree_form_);
		      if (ab_current_node_) {
			  ab_less_than_branch_qm_ = Nil;
			next_loop_3:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
			  if ( !TRUEP(ab_less_than_branch_qm_))
			      goto end_loop_2;
			  ab_node_stack_ = scope_cons(ab_current_node_,
				  ab_node_stack_);
			  ab_current_node_ = ab_less_than_branch_qm_;
			  goto next_loop_3;
			end_loop_2:;
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
			  ab_entry_cons_ = M_CAR(ab_current_alist_);
			  ab_current_alist_ = M_CDR(ab_current_alist_);
			  goto end_loop_1;
		      }
		  }
		  goto next_loop_2;
		end_loop_1:;
	      }
	      if ( !TRUEP(ab_current_node_))
		  goto end_loop_3;
	      rule_instance = M_CDR(ab_entry_cons_);
	      if (FIXNUM_LT(new_priority,ISVREF(rule_instance,(SI_Long)14L))) {
		  SVREF(rule_instance,FIX((SI_Long)14L)) = new_priority;
		  schedule_computation_instance_execution(rule_instance,
			  new_priority,rule);
		  schedule_task_qm = ISVREF(rule_instance,(SI_Long)13L);
		  if (schedule_task_qm && (ISVREF(schedule_task_qm,
			  (SI_Long)6L) || EQ(schedule_task_qm,
			  Current_schedule_task))) {
		      change_priority_of_task_arg = new_priority;
		      schedule_task_qm = ISVREF(rule_instance,(SI_Long)13L);
		      priority = change_priority_of_task_arg;
		      if (schedule_task_qm && (ISVREF(schedule_task_qm,
			      (SI_Long)6L) || EQ(schedule_task_qm,
			      Current_schedule_task))) {
			  if ( !FIXNUM_EQ(ISVREF(schedule_task_qm,
				  (SI_Long)4L),priority)) {
			      if (ISVREF(schedule_task_qm,(SI_Long)6L))
				  cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
			      if (EQ(schedule_task_qm,Current_schedule_task))
				  Current_schedule_task = Nil;
			      SVREF(schedule_task_qm,FIX((SI_Long)4L)) = 
				      priority;
			      future_task_schedule_2(schedule_task_qm);
			  }
			  temp_2 = schedule_task_qm;
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
			      temp_2 = 
				      ISVREF(Chain_of_available_schedule_tasks_vector,
				      IFIX(Current_thread_index));
			      SVREF(schedule_task_qm,FIX((SI_Long)0L)) = 
				      temp_2;
			      temp_2 = 
				      Chain_of_available_schedule_tasks_vector;
			      svref_arg_2 = Current_thread_index;
			      SVREF(temp_2,svref_arg_2) = schedule_task_qm;
			  }
			  temp_2 = Nil;
		      }
		      SVREF(rule_instance,FIX((SI_Long)13L)) = temp_2;
		  }
	      }
	      goto next_loop;
	    end_loop_3:;
	    POP_SPECIAL();
	}
    }
    return VALUES_1(new_priority);
}

void new_rules_INIT()
{
    Object gensymed_symbol, temp;
    Object Qslot_putter, Qput_rule_priority, AB_package;
    Object Qg2_get_redundant_rules;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_get_conflicting_rules, Qg2_get_colliding_rules;
    Object Qinvoke_rule_universally, Qnew_rules;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qvalidate_evaluation_action_cache;
    Object Qdefined_evaluation_type_validator, Qwrite_evaluation_action_cache;
    Object Qdefined_evaluation_type_writer, Qevaluation_action_cache_eql;
    Object Qdefined_evaluation_type_comparitor, Qcopy_evaluation_action_cache;
    Object Qdefined_evaluation_type_copier, Qreclaim_evaluation_action_cache;
    Object Qdefined_evaluation_type_reclaimer, list_constant;
    Object Qtype_specification_of_defined_evaluation_type;

    x_note_fn_call(152,34);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qaction_cache = STATIC_SYMBOL("ACTION-CACHE",AB_package);
    gensymed_symbol = Qaction_cache;
    temp = Defined_evaluation_value_types;
    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qaction_cache);
    Qtype_specification_of_defined_evaluation_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-OF-DEFINED-EVALUATION-TYPE",
	    AB_package);
    list_constant = STATIC_CONS(Qaction_cache,Qnil);
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qtype_specification_of_defined_evaluation_type,list_constant);
    Qdefined_evaluation_type_reclaimer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-RECLAIMER",AB_package);
    Qreclaim_evaluation_action_cache = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-ACTION-CACHE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_action_cache,
	    STATIC_FUNCTION(reclaim_evaluation_action_cache,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_action_cache));
    Qdefined_evaluation_type_copier = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COPIER",AB_package);
    Qcopy_evaluation_action_cache = 
	    STATIC_SYMBOL("COPY-EVALUATION-ACTION-CACHE",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_action_cache,
	    STATIC_FUNCTION(copy_evaluation_action_cache,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_action_cache));
    Qdefined_evaluation_type_comparitor = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COMPARITOR",AB_package);
    Qevaluation_action_cache_eql = 
	    STATIC_SYMBOL("EVALUATION-ACTION-CACHE-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_action_cache_eql,
	    STATIC_FUNCTION(evaluation_action_cache_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_action_cache_eql));
    string_constant = STATIC_STRING("~a cached action argument~a");
    string_constant_1 = STATIC_STRING("");
    string_constant_2 = STATIC_STRING("s");
    Qdefined_evaluation_type_writer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-WRITER",AB_package);
    Qwrite_evaluation_action_cache = 
	    STATIC_SYMBOL("WRITE-EVALUATION-ACTION-CACHE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_action_cache,
	    STATIC_FUNCTION(write_evaluation_action_cache,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_action_cache));
    Qdefined_evaluation_type_validator = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-VALIDATOR",AB_package);
    Qvalidate_evaluation_action_cache = 
	    STATIC_SYMBOL("VALIDATE-EVALUATION-ACTION-CACHE",AB_package);
    SET_SYMBOL_FUNCTION(Qvalidate_evaluation_action_cache,
	    STATIC_FUNCTION(validate_evaluation_action_cache,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qaction_cache),
	    Qdefined_evaluation_type_validator,
	    SYMBOL_FUNCTION(Qvalidate_evaluation_action_cache));
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qequal_rule_context = STATIC_SYMBOL("EQUAL-RULE-CONTEXT",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    string_constant_3 = STATIC_STRING("Invoking-rule ~NF.");
    string_constant_4 = 
	    string_append2(STATIC_STRING("Terminating invocation of rule ~NF because either some item in ~\n              its invocation has been deleted or some dynamic relation among ~\n              these items no lo"),
	    STATIC_STRING("nger holds."));
    Qhighlight_invoked_rules_mode = 
	    STATIC_SYMBOL("HIGHLIGHT-INVOKED-RULES-MODE",AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qaction_button = STATIC_SYMBOL("ACTION-BUTTON",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qschedule_computation_instance_execution = 
	    STATIC_SYMBOL("SCHEDULE-COMPUTATION-INSTANCE-EXECUTION",
	    AB_package);
    string_constant_5 = 
	    STATIC_STRING("Rule ~NF did not complete and is being continued.");
    string_constant_6 = 
	    STATIC_STRING("Rule ~NF did not complete.  Its time for completion has expired.");
    string_constant_7 = STATIC_STRING("Rule ~NF has completed.");
    Qlist_of_generated_contexts = 
	    STATIC_SYMBOL("LIST-OF-GENERATED-CONTEXTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_generated_contexts,
	    List_of_generated_contexts);
    Qnew_rules = STATIC_SYMBOL("NEW-RULES",AB_package);
    record_system_variable(Qlist_of_generated_contexts,Qnew_rules,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qlist_of_generated_contexts_tail = 
	    STATIC_SYMBOL("LIST-OF-GENERATED-CONTEXTS-TAIL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_of_generated_contexts_tail,
	    List_of_generated_contexts_tail);
    record_system_variable(Qlist_of_generated_contexts_tail,Qnew_rules,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    string_constant_8 = 
	    STATIC_STRING("The rule ~NF was invoked via the focal role ~a, which was ~\n                   not in its list of focal roles.");
    string_constant_9 = 
	    STATIC_STRING("The rule ~NF was invoked via the focal role ~a, which ~\n                    was not in its list of focal roles.");
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qany_inverse = STATIC_SYMBOL("ANY-INVERSE",AB_package);
    Qthe_inverse = STATIC_SYMBOL("THE-INVERSE",AB_package);
    Qthe_inverse_no_bind = STATIC_SYMBOL("THE-INVERSE-NO-BIND",AB_package);
    Qscanning = STATIC_SYMBOL("SCANNING",AB_package);
    Qinvoke_rule_universally = STATIC_SYMBOL("INVOKE-RULE-UNIVERSALLY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinvoke_rule_universally,
	    STATIC_FUNCTION(invoke_rule_universally,NIL,FALSE,1,1));
    Minus_of_logcount_most_positive_fixnum_minus_4 = FIX( - 
	    (logcount_long(IFIX(Most_positive_fixnum)) - (SI_Long)4L));
    Most_positive_fixnum_ash_minus_4 = FIX(IFIX(Most_positive_fixnum) >>  
	    -  - (SI_Long)4L);
    Qbackward_chaining = STATIC_SYMBOL("BACKWARD-CHAINING",AB_package);
    Qinitializing = STATIC_SYMBOL("INITIALIZING",AB_package);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Qslot_value_equal_p = STATIC_SYMBOL("SLOT-VALUE-EQUAL-P",AB_package);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_10 = 
	    STATIC_STRING("All elements of ~NV must be rules and have a ~\n                             status of OK.~%~%");
    string_constant_11 = 
	    STATIC_STRING("The following elements are not items: ");
    string_constant_12 = STATIC_STRING("and");
    string_constant_13 = STATIC_STRING("~NV");
    string_constant_14 = STATIC_STRING(".~%~%");
    string_constant_15 = 
	    STATIC_STRING("The following elements are items but not rules: ");
    string_constant_16 = STATIC_STRING("~NF");
    string_constant_17 = 
	    STATIC_STRING("The following elements are rules which are not OK: ");
    string_constant_18 = STATIC_STRING(".");
    Qg2_get_colliding_rules = STATIC_SYMBOL("G2-GET-COLLIDING-RULES",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_colliding_rules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qrule_parse_consequents_equivalent_p = 
	    STATIC_SYMBOL("RULE-PARSE-CONSEQUENTS-EQUIVALENT-P",AB_package);
    SET_SYMBOL_FUNCTION(Qrule_parse_consequents_equivalent_p,
	    STATIC_FUNCTION(rule_parse_consequents_equivalent_p,NIL,FALSE,
	    2,2));
    Qrule_parse_antecedents_equivalent_p = 
	    STATIC_SYMBOL("RULE-PARSE-ANTECEDENTS-EQUIVALENT-P",AB_package);
    SET_SYMBOL_FUNCTION(Qrule_parse_antecedents_equivalent_p,
	    STATIC_FUNCTION(rule_parse_antecedents_equivalent_p,NIL,FALSE,
	    2,2));
    SET_SYMBOL_FUNCTION(Qg2_get_colliding_rules,
	    STATIC_FUNCTION(g2_get_colliding_rules,NIL,FALSE,1,1));
    Qg2_get_conflicting_rules = STATIC_SYMBOL("G2-GET-CONFLICTING-RULES",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_conflicting_rules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_conflicting_rules,
	    STATIC_FUNCTION(g2_get_conflicting_rules,NIL,FALSE,1,1));
    Qg2_get_redundant_rules = STATIC_SYMBOL("G2-GET-REDUNDANT-RULES",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_redundant_rules,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qrule_parses_redundant_p = STATIC_SYMBOL("RULE-PARSES-REDUNDANT-P",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrule_parses_redundant_p,
	    STATIC_FUNCTION(rule_parses_redundant_p,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qg2_get_redundant_rules,
	    STATIC_FUNCTION(g2_get_redundant_rules,NIL,FALSE,1,1));
    Qrule_priority = STATIC_SYMBOL("RULE-PRIORITY",AB_package);
    Qput_rule_priority = STATIC_SYMBOL("PUT-RULE-PRIORITY",AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_priority,
	    STATIC_FUNCTION(put_rule_priority,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qrule_priority,
	    SYMBOL_FUNCTION(Qput_rule_priority),Qslot_putter);
}
