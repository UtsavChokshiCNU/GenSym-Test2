/* rules.c
 * Input file:  rules.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "rules.h"


/* BACKWARD-CHAINING-PRECEDENCE-FUNCTION */
Object backward_chaining_precedence_function(rule)
    Object rule;
{
    Object temp;

    x_note_fn_call(151,0);
    temp = ISVREF(rule,(SI_Long)28L);
    return VALUES_1(temp);
}

/* RULE-CHAINING-LINKS-FUNCTION */
Object rule_chaining_links_function(rule)
    Object rule;
{
    Object temp;

    x_note_fn_call(151,1);
    temp = ISVREF(rule,(SI_Long)30L);
    return VALUES_1(temp);
}

/* RULE-BYTE-CODE-BODY-FUNCTION */
Object rule_byte_code_body_function(rule)
    Object rule;
{
    Object temp;

    x_note_fn_call(151,2);
    temp = ISVREF(rule,(SI_Long)31L);
    return VALUES_1(temp);
}

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

/* EQUAL-RULE-CONTEXT */
Object equal_rule_context(rule_context_1,rule_context_2)
    Object rule_context_1, rule_context_2;
{
    Object temp, context_vector_1, context_vector_2, value1, value2;
    Object gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash;
    SI_Long index_1, ab_loop_bind_, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind__1;
    char temp_1;
    Object result;

    x_note_fn_call(151,3);
    temp = EQ(rule_context_1,rule_context_2) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (FIXNUM_EQ(M_CAR(M_CDR(rule_context_1)),
	    M_CAR(M_CDR(rule_context_2)))) {
	context_vector_1 = M_CDR(M_CDR(rule_context_1));
	context_vector_2 = M_CDR(M_CDR(rule_context_2));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(M_CAR(M_CDR(rule_context_1)));
	value1 = Nil;
	value2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value1 = ISVREF(context_vector_1,index_1);
	value2 = ISVREF(context_vector_2,index_1);
	if (EQ(value1,value2) && value1) {
	    gensymed_symbol = value1;
	    temp_1 = FIXNUMP(gensymed_symbol);
	    if (temp_1);
	    else
		temp_1 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
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
		    ab_loop_bind__1 = bottom_level;
		  next_loop_1:
		    if (level < ab_loop_bind__1)
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_2:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_3:
		    if ( !TRUEP(marked))
			goto end_loop_2;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_3;
		  end_loop_2:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 =  !temp_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1)
	    return VALUES_1(Nil);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* HANDLE-RULE-CATEGORY-COMPLETION-NOTIFICATION */
Object handle_rule_category_completion_notification(rule_instance)
    Object rule_instance;
{
    Object completion_notification_collection_qm, car_new_value;
    Object code_body_invocation_qm_1;

    x_note_fn_call(151,4);
    completion_notification_collection_qm = ISVREF(rule_instance,(SI_Long)26L);
    if (completion_notification_collection_qm) {
	SVREF(rule_instance,FIX((SI_Long)26L)) = Nil;
	car_new_value = delete_eval_element_1(rule_instance,
		CAR(completion_notification_collection_qm));
	if ( !TRUEP(M_CAR(completion_notification_collection_qm) = 
		car_new_value)) {
	    code_body_invocation_qm_1 = 
		    CADR(completion_notification_collection_qm);
	    if (code_body_invocation_qm_1) {
		clean_up_ri_completion_notification_collection_back_pointer(code_body_invocation_qm_1);
		wake_up_code_body_invocation(code_body_invocation_qm_1);
	    }
	    reclaim_eval_list_1(completion_notification_collection_qm);
	}
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Backward_chaining_displays, Qbackward_chaining_displays);

static Object Qinitializing;       /* initializing */

/* DISMISS-RULE-INSTANCE */
Object dismiss_rule_instance(rule_instance)
    Object rule_instance;
{
    Object purposes, purpose, ab_loop_list_, temp, svref_arg_2, last_1;
    Object next_qm, interesting_variables, variable, pruned_interest_list;
    Object variable_list_qm, gensymed_symbol, structure_being_reclaimed;
    Declare_special(1);

    x_note_fn_call(151,5);
    SVREF(rule_instance,FIX((SI_Long)10L)) = Nil;
    SVREF(rule_instance,FIX((SI_Long)2L)) = Nil;
    purposes = ISVREF(rule_instance,(SI_Long)16L);
    if (purposes) {
	SVREF(rule_instance,FIX((SI_Long)16L)) = Nil;
	purpose = Nil;
	ab_loop_list_ = purposes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	purpose = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(purpose)) {
	    rule_instance_completed(M_CDR(purpose),rule_instance);
	    inline_note_reclaim_cons(purpose,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = purpose;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = purpose;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = purpose;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = purpose;
	    }
	    M_CDR(purpose) = Nil;
	}
	else if (EQ(purpose,Qinitializing))
	    handle_completion_of_initial_rule(rule_instance);
	goto next_loop;
      end_loop:;
	if (purposes) {
	    last_1 = purposes;
	    next_qm = Nil;
	  next_loop_1:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_1;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop_1;
	  end_loop_1:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = purposes;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = purposes;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    interesting_variables = ISVREF(rule_instance,(SI_Long)17L);
    if (interesting_variables) {
	SVREF(rule_instance,FIX((SI_Long)17L)) = Nil;
	variable = Nil;
	ab_loop_list_ = interesting_variables;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	variable = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	pruned_interest_list = delete_eval_element_1(rule_instance,
		ISVREF(variable,(SI_Long)36L));
	ISVREF(variable,(SI_Long)36L) = pruned_interest_list;
	if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable,
		(SI_Long)38L)))
	    withdraw_backward_chaining(variable);
	goto next_loop_2;
      end_loop_2:;
	if (interesting_variables) {
	    last_1 = interesting_variables;
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
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = interesting_variables;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = interesting_variables;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    if (Backward_chaining_displays)
	update_backward_chaining_displays_function(rule_instance);
    remove_rule_instance_from_dynamic_rule_displays(rule_instance);
    remove_rule_instance_from_generic_rule_displays(rule_instance);
    variable_list_qm = ISVREF(rule_instance,(SI_Long)21L);
    if (variable_list_qm) {
	reclaim_evaluation_variables_list(variable_list_qm);
	SVREF(rule_instance,FIX((SI_Long)21L)) = Nil;
    }
    gensymed_symbol = Nil;
  next_loop_4:
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
    goto next_loop_4;
  end_loop_4:
  end_1:;
    gensymed_symbol = Nil;
  next_loop_5:
    gensymed_symbol = ISVREF(rule_instance,(SI_Long)7L);
    if (CAS_SVREF(rule_instance,(SI_Long)7L,gensymed_symbol,Nil)) {
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
	goto end_2;
    }
    goto next_loop_5;
  end_loop_5:
  end_2:;
    handle_rule_category_completion_notification(rule_instance);
    return reclaim_rule_instance_1(rule_instance);
}

/* RECLAIM-RULE-CONTEXT */
Object reclaim_rule_context(rule_context)
    Object rule_context;
{
    Object second_cons, vector_qm, context_length, environment_length;
    Object eval_cons, temp, svref_arg_2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,6);
    second_cons = M_CDR(rule_context);
    vector_qm = M_CDR(second_cons);
    context_length = M_CAR(second_cons);
    if (vector_qm) {
	environment_length = SIMPLE_ARRAY_ANY_1_LENGTH(vector_qm);
	index_1 = IFIX(context_length);
	ab_loop_bind_ = IFIX(environment_length);
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(vector_qm,index_1) = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	reclaim_environment_vector(vector_qm);
    }
    if (rule_context &&  !((SI_Long)0L == inline_debugging_consing())) {
	eval_cons = rule_context;
      next_loop_1:
	inline_note_reclaim_cons(eval_cons,Qeval);
	if (EQ(eval_cons,second_cons))
	    goto end_1;
	else if ( !TRUEP(eval_cons))
	    goto end_1;
	else
	    eval_cons = CDR(eval_cons);
	goto next_loop_1;
      end_loop_1:
      end_1:;
    }
    if (ISVREF(Available_eval_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = rule_context;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = second_cons;
    }
    else {
	temp = Available_eval_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = rule_context;
	temp = Available_eval_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = second_cons;
    }
    M_CDR(second_cons) = Nil;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_hashed_rule_instance_hash_vector_43_vectors, Qavailable_hashed_rule_instance_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_hashed_rule_instance_hash_vector_43_vectors, Qcount_of_hashed_rule_instance_hash_vector_43_vectors);

Object Available_hashed_rule_instance_hash_vector_43_vectors_vector = UNBOUND;

/* HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object hashed_rule_instance_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(151,7);
    temp = Count_of_hashed_rule_instance_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTORS */
Object out_hashed_rule_instance_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(151,8);
    temp = 
	    FIXNUM_MINUS(Count_of_hashed_rule_instance_hash_vector_43_vectors,
	    length(Available_hashed_rule_instance_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_hashed_rule_instance_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(151,9);
    atomic_incff_symval(Qcount_of_hashed_rule_instance_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-HASHED-RULE-INSTANCE-HASH-VECTOR */
Object make_hashed_rule_instance_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(151,10);
    if (ISVREF(Available_hashed_rule_instance_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_hashed_rule_instance_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_hashed_rule_instance_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_hashed_rule_instance_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_hashed_rule_instance_hash_vector_43_vectors_vector,
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
		make_permanent_hashed_rule_instance_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-HASHED-RULE-INSTANCE-HASH-VECTOR */
Object reclaim_hashed_rule_instance_hash_vector(hashed_rule_instance_hash_vector_43_vector)
    Object hashed_rule_instance_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(151,11);
    svref_arg_1 = Available_hashed_rule_instance_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = hashed_rule_instance_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_hashed_rule_instance_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-HASHED-RULE-INSTANCE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_hashed_rule_instance_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(151,12);
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

/* MUTATE-HASHED-RULE-INSTANCE-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_hashed_rule_instance_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(151,13);
    reclaim_rule_context(ISVREF(node,(SI_Long)2L));
    dismiss_rule_instance(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_hashed_rule_instance_tree_for_hash_skip_list_entry = UNBOUND;

static Object Qequal_rule_context;  /* equal-rule-context */

/* CLEAR-HASHED-RULE-INSTANCE-TREE */
Object clear_hashed_rule_instance_tree(hashed_rule_instance_tree_for_hash_skip_list)
    Object hashed_rule_instance_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, old_key, old_entry;
    Object result;

    x_note_fn_call(151,14);
    head = M_CAR(M_CDR(hashed_rule_instance_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(hashed_rule_instance_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
	    key_qm,hashed_rule_instance_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),M_CAR(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_rule_context(old_key);
    if (old_entry)
	dismiss_rule_instance(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(hashed_rule_instance_tree_for_hash_skip_list);
}

static Object Qhashed_rule_instance_tree_for_hash;  /* hashed-rule-instance-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-HASHED-RULE-INSTANCE */
Object make_hashed_rule_instance()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(151,15);
    new_vector = make_hashed_rule_instance_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_hashed_rule_instance_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_hashed_rule_instance_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qhashed_rule_instance_tree_for_hash;
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

/* FLATTEN-HASHED-RULE-INSTANCE */
Object flatten_hashed_rule_instance(hashed_rule_instance_hash_table)
    Object hashed_rule_instance_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(151,16);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(hashed_rule_instance_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-HASHED-RULE-INSTANCE */
Object clear_hashed_rule_instance(hashed_rule_instance_hash_table)
    Object hashed_rule_instance_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(151,17);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_hashed_rule_instance_tree(ISVREF(hashed_rule_instance_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-HASHED-RULE-INSTANCE */
Object reclaim_hashed_rule_instance(hashed_rule_instance_hash_table)
    Object hashed_rule_instance_hash_table;
{
    Object hashed_rule_instance_tree_for_hash_skip_list, head, tail;
    Object element_qm, key_qm, old_key, old_entry, last_1, next_qm, temp;
    Object svref_arg_2, temp_1;
    SI_Long index_1;
    Object result;

    x_note_fn_call(151,18);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    hashed_rule_instance_tree_for_hash_skip_list = 
	    ISVREF(hashed_rule_instance_hash_table,index_1);
    head = M_CAR(M_CDR(hashed_rule_instance_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(hashed_rule_instance_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequal_rule_context),
	    key_qm,hashed_rule_instance_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),M_CAR(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_rule_context(old_key);
    if (old_entry)
	dismiss_rule_instance(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(hashed_rule_instance_tree_for_hash_skip_list) = Nil;
    M_CADR(hashed_rule_instance_tree_for_hash_skip_list) = Nil;
    M_CAR(hashed_rule_instance_tree_for_hash_skip_list) = Nil;
    if (hashed_rule_instance_tree_for_hash_skip_list) {
	last_1 = hashed_rule_instance_tree_for_hash_skip_list;
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
	    M_CDR(temp) = hashed_rule_instance_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    hashed_rule_instance_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(hashed_rule_instance_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_hashed_rule_instance_hash_vector(hashed_rule_instance_hash_table);
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Within_activate_for_kb_workspace, Qwithin_activate_for_kb_workspace);

static Object Qrule;               /* rule */

static Object Qactivate;           /* activate */

/* ACTIVATE-FOR-RULE */
Object activate_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,19);
    if ( !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)5L)) & (SI_Long)1L))) {
	frame = rule;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)6L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
	if ( !TRUEP(In_suspend_resume_p))
	    return startup_rule_execution_if_appropriate(rule,Qactivate);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-FOR-RULE */
Object deactivate_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,20);
    if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)5L)) & (SI_Long)1L)) {
	frame = rule;
	sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		(SI_Long)11L),(SI_Long)7L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
		(SI_Long)3L;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
	if ( !TRUEP(In_suspend_resume_p))
	    return startup_rule_execution_if_appropriate(rule,Qactivate);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qedit;               /* edit */

/* MANUALLY-ENABLE-FOR-RULE */
Object manually_enable_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,21);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)48L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    return startup_rule_execution_if_appropriate(rule,Qedit);
}

/* MANUALLY-DISABLE-FOR-RULE */
Object manually_disable_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,22);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)47L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    return shutdown_rule_execution_if_appropriate(rule,Nil);
}

/* NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-RULE */
Object note_runs_while_inactive_change_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,23);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)18L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16777216L))
	return startup_rule_execution_if_appropriate(rule,Qedit);
    else
	return shutdown_rule_execution_if_appropriate(rule,Qedit);
}

static Object Qinitialize;         /* initialize */

/* INITIALIZE-FOR-RULE */
Object initialize_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,24);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    if (ISVREF(rule,(SI_Long)27L))
	reclaim_hashed_rule_instance(ISVREF(rule,(SI_Long)27L));
    svref_new_value = make_hashed_rule_instance();
    ISVREF(rule,(SI_Long)27L) = svref_new_value;
    return startup_rule_execution_if_appropriate(rule,Qinitialize);
}

static Object Qframe_representations;  /* frame-representations */

/* INITIALIZE-AFTER-READING-FOR-RULE */
Object initialize_after_reading_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(151,25);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    if ( !TRUEP(New_saved_kb_format_p) && get_kb_parent_information(rule) 
	    && ISVREF(rule,(SI_Long)9L)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_representations);
	SVREF(rule,FIX((SI_Long)9L)) = Nil;
    }
    if (ISVREF(rule,(SI_Long)27L))
	reclaim_hashed_rule_instance(ISVREF(rule,(SI_Long)27L));
    svref_new_value = make_hashed_rule_instance();
    ISVREF(rule,(SI_Long)27L) = svref_new_value;
    return startup_rule_execution_if_appropriate(rule,Qinitialize);
}

static Object Qrule_chaining_links;  /* rule-chaining-links */

/* CLEANUP-FOR-RULE */
Object cleanup_for_rule(rule)
    Object rule;
{
    Object frame, sub_vector_qm, method_function_qm, gensymed_symbol;
    Object structure_being_reclaimed, temp, svref_arg_2;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(151,26);
    frame = rule;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qrule)) {
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
    delete_dynamic_rule_displays_for_rule_or_object(rule);
    gensymed_symbol = Nil;
  next_loop_1:
    gensymed_symbol = ISVREF(rule,(SI_Long)21L);
    if (CAS_SVREF(rule,(SI_Long)21L,gensymed_symbol,Nil)) {
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
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
  end_2:;
    if (ISVREF(rule,(SI_Long)27L)) {
	reclaim_hashed_rule_instance(ISVREF(rule,(SI_Long)27L));
	ISVREF(rule,(SI_Long)27L) = Nil;
    }
    return change_slot_value(3,rule,Qrule_chaining_links,Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qinvoke_rule_universally;  /* invoke-rule-universally */

/* STARTUP-RULE-EXECUTION-IF-APPROPRIATE */
Object startup_rule_execution_if_appropriate(rule,event)
    Object rule, event;
{
    Object scan_interval, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    Object temp_1;
    char runs_while_inactive_qm, svref_new_value_1, temp_2;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(151,27);
    runs_while_inactive_qm = (SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)16777216L);
    if ( !runs_while_inactive_qm && EQ(event,Qactivate) &&  
	    !TRUEP(Within_activate_for_kb_workspace) || 
	    runs_while_inactive_qm &&  !EQ(event,Qactivate)) {
	scan_interval = ISVREF(rule,(SI_Long)20L);
	if (scan_interval) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(rule,(SI_Long)21L);
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp,svref_arg_2) = svref_new_value;
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
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
		    + 1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = FIXNUMP(scan_interval) ? 
		    (double)IFIX(scan_interval) : 
		    DFLOAT_ISAREF_1(scan_interval,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !runs_while_inactive_qm;
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    temp = ISVREF(rule,(SI_Long)26L);
	    SVREF(task,FIX((SI_Long)4L)) = temp;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = Qinvoke_rule_universally;
	    temp = SYMBOL_FUNCTION(Qinvoke_rule_universally);
	    SVREF(task,FIX((SI_Long)8L)) = temp;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = rule;
	    new_1 = task;
	    if (CAS_SVREF(rule,(SI_Long)21L,old,new_1)) {
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
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = old;
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
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = new_1;
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
    }
    if (runs_while_inactive_qm && EQ(event,Qinitialize) && (SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)2048L)) {
	temp_1 = ISVREF(rule,(SI_Long)8L);
	temp_2 =  !TRUEP(CAR(temp_1)) ? (SI_Long)0L != (IFIX(ISVREF(rule,
		(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)16777216L) &&  
		!((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		(SI_Long)8192L)) : TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	generate_and_schedule_rule_instances(rule,Nil,Nil,Nil,
		Qinitializing,Nil,ISVREF(rule,(SI_Long)26L),Nil);
    return VALUES_1(Nil);
}

/* SHUTDOWN-RULE-EXECUTION-IF-APPROPRIATE */
Object shutdown_rule_execution_if_appropriate(rule,deactivating_qm)
    Object rule, deactivating_qm;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Object old_qm, new_1;
    Declare_special(1);

    x_note_fn_call(151,28);
    if ( !(deactivating_qm && (SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)16777216L))) {
	gensymed_symbol = Nil;
      next_loop:
	gensymed_symbol = ISVREF(rule,(SI_Long)21L);
	if (CAS_SVREF(rule,(SI_Long)21L,gensymed_symbol,Nil)) {
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
	old_qm = ISVREF(rule,(SI_Long)27L);
	new_1 = old_qm ? make_hashed_rule_instance() : Nil;
	if (old_qm) {
	    if (CAS_SVREF(rule,(SI_Long)27L,old_qm,new_1))
		reclaim_hashed_rule_instance(old_qm);
	    else
		reclaim_hashed_rule_instance(new_1);
	}
    }
    return VALUES_1(Nil);
}

static Object Qfor;                /* for */

/* RULE-TRANSLATION-KEYWORD */
Object rule_translation_keyword(translation)
    Object translation;
{
    Object body;

    x_note_fn_call(151,29);
    body = translation;
  next_loop:
    if ( !EQ(CAR(body),Qfor))
	goto end_loop;
    body = THIRD(body);
    goto next_loop;
  end_loop:
    return VALUES_1(CAR(body));
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

static Object Qrule_scan_interval;  /* rule-scan-interval */

/* PUT-RULE-SCAN-INTERVAL */
Object put_rule_scan_interval(rule,new_value,gensymed_symbol)
    Object rule, new_value, gensymed_symbol;
{
    Object old_value, rule_keyword, temp, structure_being_reclaimed, temp_1;
    Object svref_arg_2, old, new_1, def_structure_schedule_task_variable;
    Object svref_new_value, task;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(151,30);
    old_value = ISVREF(rule,(SI_Long)20L);
    rule_keyword = ISVREF(rule,(SI_Long)32L);
    if (memq_function(rule_keyword,list_constant) || (SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)2048L)) {
	reclaim_slot_value(new_value);
	new_value = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_scan_interval);
    SVREF(rule,FIX((SI_Long)20L)) = new_value;
    temp = ISVREF(rule,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)8192L))) &&  
	    !TRUEP(equal_scan_intervals(old_value,new_value))) {
	if (old_value) {
	    gensymed_symbol = Nil;
	  next_loop:
	    gensymed_symbol = ISVREF(rule,(SI_Long)21L);
	    if (CAS_SVREF(rule,(SI_Long)21L,gensymed_symbol,Nil)) {
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
	}
	if (new_value) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop_1:
	    old = ISVREF(rule,(SI_Long)21L);
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_1 = Chain_of_available_schedule_tasks_vector;
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
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp_1 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
		    + 1.0;
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    temp_1 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = FIXNUMP(new_value) ? (double)IFIX(new_value) :
		     DFLOAT_ISAREF_1(new_value,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !((SI_Long)0L != (IFIX(ISVREF(rule,
		    (SI_Long)4L)) & (SI_Long)16777216L));
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    temp_1 = ISVREF(rule,(SI_Long)26L);
	    SVREF(task,FIX((SI_Long)4L)) = temp_1;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = Qinvoke_rule_universally;
	    temp_1 = SYMBOL_FUNCTION(Qinvoke_rule_universally);
	    SVREF(task,FIX((SI_Long)8L)) = temp_1;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = rule;
	    new_1 = task;
	    if (CAS_SVREF(rule,(SI_Long)21L,old,new_1)) {
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
		    temp_1 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp_1;
		    temp_1 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = old;
		}
		future_task_schedule_2(new_1);
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
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = new_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	  end_2:;
	}
    }
    return VALUES_1(new_value);
}

/* EQUAL-SCAN-INTERVALS */
Object equal_scan_intervals(value1,value2)
    Object value1, value2;
{
    Object temp;
    double arg, arg_1;

    x_note_fn_call(151,31);
    temp = EQ(value1,value2) ? T : Nil;
    if (temp);
    else
	temp = FIXNUMP(value1) && FIXNUMP(value2) ? (FIXNUM_EQ(value1,
		value2) ? T : Nil) : Qnil;
    if (temp);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value1)) == (SI_Long)1L && 
	    INLINE_DOUBLE_FLOAT_VECTOR_P(value2) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value2)) == (SI_Long)1L) {
	arg = DFLOAT_ISAREF_1(value1,(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(value2,(SI_Long)0L);
	temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? ( 
		!inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* WALK-RULE */
Object walk_rule(rule_parse_to_walk,walker)
    Object rule_parse_to_walk, walker;
{
    x_note_fn_call(151,32);
    return walk_rule_without_copying(copy_for_phrase(rule_parse_to_walk),
	    walker);
}

/* WALK-RULE-WITHOUT-COPYING */
Object walk_rule_without_copying(rule,walker)
    Object rule, walker;
{
    Object temp;

    x_note_fn_call(151,33);
    if (EQ(CAR(rule),Qfor)) {
	temp = walk_designation(SECOND(rule),walker);
	M_SECOND(rule) = temp;
	temp = walk_rule_without_copying(THIRD(rule),walker);
	M_THIRD(rule) = temp;
    }
    else {
	temp = walk_expression(SECOND(rule),walker);
	M_SECOND(rule) = temp;
	temp = walk_rule_actions(THIRD(rule),walker);
	M_THIRD(rule) = temp;
    }
    return VALUES_1(rule);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object list_constant_3;     /* # */

/* WALK-RULE-ACTIONS */
Object walk_rule_actions(action,walker)
    Object action, walker;
{
    Object subaction_cons, temp, temp_1, temp_2;

    x_note_fn_call(151,34);
    if (memq_function(CAR(action),list_constant_1)) {
	subaction_cons = CDR(action);
      next_loop:
	if ( !TRUEP(subaction_cons))
	    goto end_loop;
	temp = walk_rule_actions(CAR(subaction_cons),walker);
	M_CAR(subaction_cons) = temp;
	subaction_cons = M_CDR(subaction_cons);
	goto next_loop;
      end_loop:
	return VALUES_1(action);
	return VALUES_1(Qnil);
    }
    else {
	temp_1 = CDR(action);
	temp_2 = assq_function(CAR(action),list_constant_2);
	temp_2 = CDR(temp_2);
	if (temp_2);
	else {
	    temp_2 = lookup_action_template(CAR(action));
	    temp_2 = CDR(temp_2);
	}
	if (temp_2);
	else
	    temp_2 = list_constant_3;
	temp = walk_action_body_given_template(temp_1,temp_2,walker);
	M_CDR(action) = temp;
	return VALUES_1(action);
    }
}

static Object Qexpression;         /* expression */

static Object Qmessage_text;       /* message-text */

static Object Qdesignation;        /* designation */

static Object Qplace_reference_expression;  /* place-reference-expression */

static Object Qany;                /* any */

static Object Qexpression_list;    /* expression-list */

static Object Qdesignation_list;   /* designation-list */

static Object Qmessage_designation;  /* message-designation */

static Object list_constant_4;     /* # */

static Object Qoperator;           /* operator */

static Object Qinform_option;      /* inform-option */

static Object Qduration;           /* duration */

static Object Qshow_or_hide_argument_list;  /* show-or-hide-argument-list */

static Object Qcolor_changes;      /* color-changes */

static Object Qcreate_connection_spec;  /* create-connection-spec */

static Object Qother;              /* other */

/* WALK-ACTION-BODY-GIVEN-TEMPLATE */
Object walk_action_body_given_template(given_body,template_1,walker)
    Object given_body, template_1, walker;
{
    Object body, body_trailer, temp, final_body, gensymed_symbol, domain_cons;
    Object expression_cons, designation_cons, expr_qm_cons;
    char temp_1;

    x_note_fn_call(151,35);
    body = given_body;
    body_trailer = Nil;
  next_loop:
    if ( !(CONSP(template_1) && CONSP(body)))
	goto end_loop;
    temp = walk_action_body_given_template(M_CAR(body),M_CAR(template_1),
	    walker);
    M_CAR(body) = temp;
    template_1 = M_CDR(template_1);
    body_trailer = body;
    body = M_CDR(body);
    goto next_loop;
  end_loop:
    if (SYMBOLP(template_1)) {
	if (EQ(template_1,Qexpression) || EQ(template_1,Qmessage_text))
	    final_body = walk_expression(body,walker);
	else if (EQ(template_1,Qdesignation))
	    final_body = walk_designation(body,walker);
	else if (EQ(template_1,Qplace_reference_expression)) {
	    if (CONSP(body)) {
		gensymed_symbol = M_CAR(body);
		temp_1 = EQ(gensymed_symbol,Qany);
		if (temp_1);
		else
		    temp_1 = EQ(gensymed_symbol,Qthe);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		domain_cons = CDDR(body);
	      next_loop_1:
		if ( !TRUEP(domain_cons))
		    goto end_loop_1;
		temp = walk_expression(M_CAR(domain_cons),walker);
		M_CAR(domain_cons) = temp;
		domain_cons = M_CDR(domain_cons);
		goto next_loop_1;
	      end_loop_1:;
	    }
	    final_body = body;
	}
	else if (EQ(template_1,Qexpression_list)) {
	    expression_cons = body;
	  next_loop_2:
	    if ( !TRUEP(expression_cons))
		goto end_loop_2;
	    temp = walk_expression(M_CAR(expression_cons),walker);
	    M_CAR(expression_cons) = temp;
	    expression_cons = M_CDR(expression_cons);
	    goto next_loop_2;
	  end_loop_2:;
	    final_body = body;
	}
	else if (EQ(template_1,Qdesignation_list)) {
	    designation_cons = body;
	  next_loop_3:
	    if ( !TRUEP(designation_cons))
		goto end_loop_3;
	    temp = walk_designation(M_CAR(designation_cons),walker);
	    M_CAR(designation_cons) = temp;
	    designation_cons = M_CDR(designation_cons);
	    goto next_loop_3;
	  end_loop_3:;
	    final_body = body;
	}
	else if (EQ(template_1,Qmessage_designation))
	    final_body = EQUAL(body,list_constant_4) || EQ(body,Qoperator) 
		    ? body : walk_designation(body,walker);
	else if (EQ(template_1,Qinform_option)) {
	    temp = EQ(CAR(body),Qduration) ? walk_expression(SECOND(body),
		    walker) : walk_designation(SECOND(body),walker);
	    M_SECOND(body) = temp;
	    final_body = body;
	}
	else if (EQ(template_1,Qshow_or_hide_argument_list)) {
	    expr_qm_cons = body;
	  next_loop_4:
	    if ( !TRUEP(expr_qm_cons))
		goto end_loop_4;
	    if (CAR(expr_qm_cons)) {
		temp = walk_expression(CAR(expr_qm_cons),walker);
		M_CAR(expr_qm_cons) = temp;
	    }
	    expr_qm_cons = M_CDR(expr_qm_cons);
	    goto next_loop_4;
	  end_loop_4:;
	    final_body = body;
	}
	else if (EQ(template_1,Qcolor_changes))
	    final_body = body;
	else if (EQ(template_1,Qcreate_connection_spec))
	    final_body = body;
	else if (EQ(template_1,Qother) || EQ(template_1,Qnil))
	    final_body = body;
	else
	    final_body = body;
    }
    else
	final_body = body;
    if (body_trailer) {
	M_CDR(body_trailer) = final_body;
	return VALUES_1(given_body);
    }
    else
	return VALUES_1(final_body);
    return VALUES_1(Qnil);
}

/* WALK-EXPRESSION */
Object walk_expression(expression,walker)
    Object expression, walker;
{
    Object operator_1, function_template, sub_expr_cons, car_new_value;

    x_note_fn_call(151,36);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(expression) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(expression)) == (SI_Long)1L)
	return FUNCALL_1(walker,expression);
    else if (CONSP(expression) && EQ(M_CDR(expression),
	    Phrase_sequence_marker) || CONSP(expression) && 
	    EQ(M_CDR(expression),Phrase_structure_marker) || 
	    truth_value_phrase_p(expression))
	return FUNCALL_1(walker,expression);
    else if (CONSP(expression)) {
	operator_1 = CAR(expression);
	if (ATOM(expression) ? expression && SYMBOLP(expression) : 
		TRUEP(designation_operator_or_giver_of_value_p(CAR(expression))))
	    return walk_designation(expression,walker);
	else if (SYMBOLP(operator_1)) {
	    function_template = lookup_function_template(operator_1);
	    if (function_template)
		return walk_expression_given_template(expression,
			function_template,walker);
	    else {
		sub_expr_cons = M_CDR(expression);
	      next_loop:
		if ( !TRUEP(sub_expr_cons))
		    goto end_loop;
		car_new_value = walk_expression(CAR(sub_expr_cons),walker);
		M_CAR(sub_expr_cons) = car_new_value;
		sub_expr_cons = M_CDR(sub_expr_cons);
		goto next_loop;
	      end_loop:;
		return FUNCALL_1(walker,expression);
	    }
	}
	else if (NUMBERP(operator_1) || 
		INLINE_DOUBLE_FLOAT_VECTOR_P(operator_1) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(operator_1)) == (SI_Long)1L)
	    return FUNCALL_1(walker,operator_1);
	else
	    return VALUES_1(expression);
    }
    else if (SYMBOLP(expression))
	return walk_designation(expression,walker);
    else
	return FUNCALL_1(walker,expression);
}

static Object Qscope;              /* scope */

/* WALK-EXPRESSION-GIVEN-TEMPLATE */
Object walk_expression_given_template(expression,template_1,walker)
    Object expression, template_1, walker;
{
    Object expr_arg_cons, expr_arg, template_type, ab_loop_list_;
    Object car_new_value, new_designation, temp;

    x_note_fn_call(151,37);
    expr_arg_cons = CDR(expression);
    expr_arg = Nil;
    template_type = Nil;
    ab_loop_list_ = CDR(template_1);
  next_loop:
    if ( !TRUEP(expr_arg_cons))
	goto end_loop;
    expr_arg = M_CAR(expr_arg_cons);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    template_type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(template_type,Qexpression)) {
	car_new_value = walk_expression(expr_arg,walker);
	M_CAR(expr_arg_cons) = car_new_value;
    }
    else if (EQ(template_type,Qdesignation)) {
	car_new_value = walk_designation(expr_arg,walker);
	M_CAR(expr_arg_cons) = car_new_value;
    }
    else if (EQ(template_type,Qscope)) {
	new_designation = gensym_cons_1(Qany,expr_arg);
	temp = walk_designation(new_designation,walker);
	car_new_value = CDR(temp);
	M_CAR(expr_arg_cons) = car_new_value;
	reclaim_gensym_cons_1(new_designation);
    }
    else if (EQ(template_type,Qother));
    else;
    expr_arg_cons = M_CDR(expr_arg_cons);
    goto next_loop;
  end_loop:;
    return FUNCALL_1(walker,expression);
}

/* WALK-DESIGNATION */
Object walk_designation(designation,walker)
    Object designation, walker;
{
    Object domain_cons, car_new_value;

    x_note_fn_call(151,38);
    if (CONSP(designation)) {
	domain_cons = CDDR(designation);
      next_loop:
	if ( !TRUEP(domain_cons))
	    goto end_loop;
	car_new_value = walk_expression(M_CAR(domain_cons),walker);
	M_CAR(domain_cons) = car_new_value;
	domain_cons = M_CDR(domain_cons);
	goto next_loop;
      end_loop:;
    }
    return FUNCALL_1(walker,designation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Rule_local_name_references, Qrule_local_name_references);

DEFINE_VARIABLE_WITH_SYMBOL(Current_rule_local_name_reference_info, Qcurrent_rule_local_name_reference_info);

/* GET-RULE-LOCAL-NAME-REFERENCE-INFO */
Object get_rule_local_name_reference_info(implicit_local_name)
    Object implicit_local_name;
{
    Object temp, new_info;

    x_note_fn_call(151,39);
    temp = assq_function(implicit_local_name,Rule_local_name_references);
    if (temp)
	return VALUES_1(temp);
    else {
	new_info = phrase_list_4(implicit_local_name,FIX((SI_Long)0L),Nil,
		FIX((SI_Long)0L));
	Rule_local_name_references = phrase_cons(new_info,
		Rule_local_name_references);
	return VALUES_1(new_info);
    }
}

/* COLLECT-LOCAL-NAME-REFERENCE-INFO */
Object collect_local_name_reference_info(expr)
    Object expr;
{
    Object role, implicit_local_name, reference_info, temp;
    Object implicit_reference_qm, explicit_local_name_qm, temp_2;
    Object modify_macro_for_phrase_push_arg;
    char temp_1;

    x_note_fn_call(151,40);
    if (CONSP(expr) &&  !(CONSP(expr) && EQ(M_CDR(expr),
	    Phrase_sequence_marker)) &&  !(CONSP(expr) && EQ(M_CDR(expr),
	    Phrase_structure_marker)) &&  
	    !TRUEP(truth_value_phrase_p(expr)) && (EQ(M_CAR(expr),Qthe) || 
	    EQ(M_CAR(expr),Qany)) &&  
	    !TRUEP(ignore_role_in_walk_p(simple_role_of_role(SECOND(expr))))) {
	role = SECOND(expr);
	implicit_local_name = atomic_naming_element_of_role(role);
	reference_info = 
		get_rule_local_name_reference_info(implicit_local_name);
	if (EQ(M_CAR(expr),Qthe)) {
	    temp = M_CAR(M_CDR(expr));
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	implicit_reference_qm = temp_1 ? ( !TRUEP(M_CDR(M_CDR(expr))) ? T :
		 Nil) : Nil;
	explicit_local_name_qm = 
		get_explicitly_specified_local_name_of_role_if_any(role);
	if (implicit_reference_qm) {
	    temp_2 = FIXNUM_ADD1(FOURTH(reference_info));
	    M_FOURTH(reference_info) = temp_2;
	}
	else {
	    temp_2 = FIXNUM_ADD1(SECOND(reference_info));
	    M_SECOND(reference_info) = temp_2;
	}
	if ( !TRUEP(implicit_reference_qm) && explicit_local_name_qm) {
	    modify_macro_for_phrase_push_arg = explicit_local_name_qm;
	    temp_2 = phrase_cons_with_args_reversed(THIRD(reference_info),
		    modify_macro_for_phrase_push_arg);
	    M_THIRD(reference_info) = temp_2;
	}
    }
    return VALUES_1(expr);
}

static Object Qrole_server;        /* role-server */

static Object Qname;               /* name */

static Object Qnamed_by_debugging_name;  /* named-by-debugging-name */

static Object Qicon_color;         /* icon-color */

static Object Qitem_color;         /* item-color */

static Object Qitem_x_position;    /* item-x-position */

static Object Qitem_y_position;    /* item-y-position */

static Object Qicon_heading;       /* icon-heading */

static Object Qitem_width;         /* item-width */

static Object Qitem_height;        /* item-height */

static Object Qsystem_attribute_as_text;  /* system-attribute-as-text */

static Object Qtext_of_attribute;  /* text-of-attribute */

static Object Qthis_workspace;     /* this-workspace */

static Object Qthis_window;        /* this-window */

static Object Qthis_rule;          /* this-rule */

static Object Qthis_procedure;     /* this-procedure */

static Object Qthis_procedure_invocation;  /* this-procedure-invocation */

static Object Qnth_element;        /* nth-element */

static Object Qindexed_attribute;  /* indexed-attribute */

static Object Qattribute_frame_or_place_reference;  /* attribute-frame-or-place-reference */

static Object Qelement_frame_or_place_reference;  /* element-frame-or-place-reference */

static Object Qclass_qualified_name_frame_or_place_reference;  /* class-qualified-name-frame-or-place-reference */

static Object Qclass_qualified_method;  /* class-qualified-method */

static Object Qnext_procedure_method;  /* next-procedure-method */

/* IGNORE-ROLE-IN-WALK-P */
Object ignore_role_in_walk_p(simple_role)
    Object simple_role;
{
    Object role_symbol, temp;

    x_note_fn_call(151,41);
    role_symbol = CONSP(simple_role) ? M_CAR(simple_role) : simple_role;
    temp = EQ(role_symbol,Qrole_server) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qname) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qnamed_by_debugging_name) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qicon_color) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qitem_color) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qitem_x_position) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qitem_y_position) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qicon_heading) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qitem_width) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qitem_height) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qsystem_attribute_as_text) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qtext_of_attribute) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qthis_workspace) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qthis_window) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qthis_rule) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qthis_procedure) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qthis_procedure_invocation) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qnth_element) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qindexed_attribute) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qattribute_frame_or_place_reference) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qelement_frame_or_place_reference) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,
		Qclass_qualified_name_frame_or_place_reference) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qclass_qualified_method) ? T : Nil;
    if (temp);
    else
	temp = EQ(role_symbol,Qnext_procedure_method) ? T : Nil;
    return VALUES_1(temp);
}

static Object string_constant;     /* "COMPILER-~A-1" */

static Object string_constant_1;   /* "COMPILER-~A-~A" */

/* ADD-LOCAL-NAMES-FOR-CURRENT-REFERENCE-INFO */
Object add_local_names_for_current_reference_info(expr)
    Object expr;
{
    Object temp, current_implicit_local_name, role, implicit_local_name;
    Object new_local_name, name_reference, ab_loop_list_, ab_loop_it_, temp_2;
    SI_Long current_name_count;
    char temp_1;

    x_note_fn_call(151,42);
    if (CONSP(expr) &&  !(CONSP(expr) && EQ(M_CDR(expr),
	    Phrase_sequence_marker)) &&  !(CONSP(expr) && EQ(M_CDR(expr),
	    Phrase_structure_marker)) &&  
	    !TRUEP(truth_value_phrase_p(expr)) && (EQ(M_CAR(expr),Qthe) || 
	    EQ(M_CAR(expr),Qany))) {
	temp = CAR(Current_rule_local_name_reference_info);
	current_implicit_local_name = CAR(temp);
	role = M_CAR(M_CDR(expr));
	implicit_local_name = atomic_naming_element_of_role(role);
	if (EQ(current_implicit_local_name,implicit_local_name) &&  
		!TRUEP(get_explicitly_specified_local_name_of_role_if_any(role)) 
		&&  
		!TRUEP(ignore_role_in_walk_p(simple_role_of_role(role))) 
		&& invertible_designation_p(expr)) {
	    if (EQ(M_CAR(expr),Qthe) && SYMBOLP(role) &&  
		    !TRUEP(M_CDR(M_CDR(expr))))
		expr = intern_text_string(1,tformat_text_string(2,
			string_constant,current_implicit_local_name));
	    else {
		current_name_count = 
			IFIX(FIXNUM_ADD1(CDR(Current_rule_local_name_reference_info)));
		new_local_name = Nil;
	      next_loop:
		new_local_name = intern_text_string(1,
			tformat_text_string(3,string_constant_1,
			current_implicit_local_name,FIX(current_name_count)));
		name_reference = Nil;
		ab_loop_list_ = Rule_local_name_references;
		ab_loop_it_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		name_reference = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		ab_loop_it_ = memq_function(new_local_name,
			THIRD(name_reference));
		if (ab_loop_it_) {
		    temp_1 = TRUEP(ab_loop_it_);
		    goto end_1;
		}
		goto next_loop_1;
	      end_loop:
		temp_1 = TRUEP(Qnil);
	      end_1:;
		if ( !temp_1)
		    goto end_loop_1;
		current_name_count = current_name_count + (SI_Long)1L;
		goto next_loop;
	      end_loop_1:
		temp_2 = phrase_cons(role,new_local_name);
		M_SECOND(expr) = temp_2;
		temp_2 = Current_rule_local_name_reference_info;
		M_CDR(temp_2) = FIX(current_name_count);
	    }
	}
    }
    return VALUES_1(expr);
}

static Object Qcollect_local_name_reference_info;  /* collect-local-name-reference-info */

static Object Qadd_local_names_for_current_reference_info;  /* add-local-names-for-current-reference-info */

/* MAYBE-ADD-MORE-LOCAL-NAMES */
Object maybe_add_more_local_names(original_rule_parse)
    Object original_rule_parse;
{
    Object rule_local_name_references, rule_parse, copying_done_qm;
    Object reference_info, ab_loop_list_;
    Object current_rule_local_name_reference_info;
    Declare_special(2);
    Object result;

    x_note_fn_call(151,43);
    rule_local_name_references = Nil;
    rule_parse = original_rule_parse;
    PUSH_SPECIAL_WITH_SYMBOL(Rule_local_name_references,Qrule_local_name_references,rule_local_name_references,
	    1);
      walk_rule_without_copying(rule_parse,
	      SYMBOL_FUNCTION(Qcollect_local_name_reference_info));
      copying_done_qm = Nil;
      reference_info = Nil;
      ab_loop_list_ = Rule_local_name_references;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      reference_info = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (IFIX(SECOND(reference_info)) > (SI_Long)1L && 
	      FIXNUM_LT(length(THIRD(reference_info)),
	      SECOND(reference_info)) && (IFIX(FOURTH(reference_info)) == 
	      (SI_Long)0L || FIXNUM_EQ(length(THIRD(reference_info)),
	      FIXNUM_SUB1(SECOND(reference_info))))) {
	  current_rule_local_name_reference_info = 
		  phrase_cons(reference_info,FIX((SI_Long)0L));
	  PUSH_SPECIAL_WITH_SYMBOL(Current_rule_local_name_reference_info,Qcurrent_rule_local_name_reference_info,current_rule_local_name_reference_info,
		  0);
	    rule_parse = copying_done_qm ? 
		    walk_rule_without_copying(rule_parse,
		    SYMBOL_FUNCTION(Qadd_local_names_for_current_reference_info)) 
		    : walk_rule(rule_parse,
		    SYMBOL_FUNCTION(Qadd_local_names_for_current_reference_info));
	    copying_done_qm = T;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop:;
      result = VALUES_1(rule_parse);
    POP_SPECIAL();
    return result;
}

static Object Qusing;              /* using */

/* EXTRACT-ASSIGNMENTS-SECTION-FROM-FOR-RULE */
Object extract_assignments_section_from_for_rule(rule_translation)
    Object rule_translation;
{
    Object assignments_section, rule_text, result_1, temp, rule_element;
    Object ab_loop_list_, temp_1;
    char temp_2;

    x_note_fn_call(151,44);
    assignments_section = Nil;
    rule_text = Nil;
    result_1 = Nil;
    temp = Nil;
    rule_element = Nil;
    ab_loop_list_ = rule_translation;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    rule_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (LISTP(rule_element)) {
	temp_1 = CAR(rule_element);
	temp_2 = LISTP(temp_1);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2 ? EQ(CAAR(rule_element),Qusing) : TRUEP(Nil)) {
	assignments_section = CAR(rule_element);
	rule_text = nconc2(rule_text,CDR(rule_element));
    }
    else if ( ! !TRUEP(rule_element) && LISTP(rule_element)) {
	if ( !EQ(CAR(rule_element),Qfor))
	    rule_text = nconc2(rule_text,phrase_cons(rule_element,Nil));
	else {
	    temp = extract_assignments_section_from_for_rule(rule_element);
	    assignments_section = FIRST(temp);
	    rule_text = nconc2(rule_text,phrase_cons(SECOND(temp),Nil));
	}
    }
    else
	rule_text = phrase_cons(rule_element,Nil);
    goto next_loop;
  end_loop:;
    result_1 = phrase_list_2(assignments_section,rule_text);
    return VALUES_1(result_1);
}

/* EXTRACT-ASSIGNMENTS-SECTION-IF-ANY */
Object extract_assignments_section_if_any(rule_translation)
    Object rule_translation;
{
    Object assignments_section, rt, result_1, temp, temp_1;

    x_note_fn_call(151,45);
    assignments_section = Nil;
    rt = Nil;
    result_1 = Nil;
    temp = Nil;
    temp_1 = CAR(rule_translation);
    if (LISTP(temp_1)) {
	if (EQ(CAAR(rule_translation),Qusing)) {
	    assignments_section = CAR(rule_translation);
	    rt = SECOND(rule_translation);
	}
    }
    else if (EQ(CAR(rule_translation),Qfor)) {
	temp = extract_assignments_section_from_for_rule(rule_translation);
	assignments_section = FIRST(temp);
	rt = SECOND(temp);
    }
    result_1 = phrase_list_2(assignments_section,rt);
    return VALUES_1(result_1);
}

static Object Qnupec_extra_actions;  /* nupec-extra-actions */

static Object Qrule_keyword;       /* rule-keyword */

static Object Qinitially;          /* initially */

static Object Qframe_flags;        /* frame-flags */

static Object Qab_if;              /* if */

static Object Qwhenever;           /* whenever */

static Object Quniversal_compilation;  /* universal-compilation */

static Object Qfocus_class_compilation_failed;  /* focus-class-compilation-failed */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

static Object Qrule_byte_code_body;  /* rule-byte-code-body */

static Object Qbad;                /* bad */

/* COMPILE-RULE-FOR-SLOT */
Object compile_rule_for_slot varargs_1(int, n)
{
    Object translation, rule, gensymed_symbol;
    Object rule_data, old_qm, new_1, code, temp, nupec_extra_actions_qm;
    Object nupec_extra_actions_copy, rule_translation_list;
    Object translation_action_list_qm, rule_keyword;
    Object needs_to_be_reactivated_qm, original_compile;
    Object current_computation_frame;
    Object current_computation_component_particulars, focal_classes;
    Object general_compilation, chaining_links, general_compilation_context;
    Object collected_roles, link_1, ab_loop_list_, focus_role_qm;
    Object second_focus_role_qm, ab_loop_desetq_, sub_class_bit_vector;
    Object chaining_roles, focus_compilations, name, focus_compilation;
    Object result_1, current_flag_state_qm, slot_description, new_cons, temp_2;
    Object svref_arg_2, svref_new_value_1, gensymed_symbol_4;
    Object stack_of_slot_value_changes, gensymed_symbol_5, gensymed_symbol_6;
    Object frame_and_slot_or_atom, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    SI_Long svref_new_value, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(3);
    Object result;

    x_note_fn_call(151,46);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    rule_data = extract_assignments_section_if_any(translation);
    old_qm = ISVREF(rule,(SI_Long)27L);
    new_1 = old_qm ? make_hashed_rule_instance() : Nil;
    if (old_qm) {
	if (CAS_SVREF(rule,(SI_Long)27L,old_qm,new_1))
	    reclaim_hashed_rule_instance(old_qm);
	else
	    reclaim_hashed_rule_instance(new_1);
    }
    code = M_CAR(M_CDR(Journal_shutout_scan_p));
    if (FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != (SI_Long)0L ? 
	    TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) : TRUEP(Nil)) {
	temp = get_lookup_slot_value_given_default(rule,
		Qnupec_extra_actions,Nil);
	nupec_extra_actions_qm = CAR(temp);
	if (nupec_extra_actions_qm) {
	    nupec_extra_actions_copy = copy_for_phrase(nupec_extra_actions_qm);
	    rule_translation_list = translation;
	  next_loop:
	    if ( !TRUEP(rule_translation_list))
		goto end_loop;
	    if (CONSP(rule_translation_list) && 
		    EQ(FIRST(rule_translation_list),Qfor))
		rule_translation_list = THIRD(rule_translation_list);
	    else {
		translation_action_list_qm = THIRD(rule_translation_list);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    translation_action_list_qm = Qnil;
	  end_1:;
	    if (translation_action_list_qm)
		nconc2(translation_action_list_qm,nupec_extra_actions_copy);
	}
    }
    rule_keyword = rule_translation_keyword(translation);
    needs_to_be_reactivated_qm = (SI_Long)0L != (IFIX(ISVREF(rule,
	    (SI_Long)4L)) & (SI_Long)2048L) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)5L)) & (SI_Long)1L)) ? ( 
	    !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16777216L)) ? T : Nil) : Qnil;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_keyword);
    SVREF(rule,FIX((SI_Long)32L)) = rule_keyword;
    if (EQ(rule_keyword,Qinitially)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) | (SI_Long)2048L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	needs_to_be_reactivated_qm = Nil;
	if (EQ(SECOND(translation),Qfor))
	    translation = CDR(translation);
	else
	    M_CAR(translation) = Qab_if;
    }
    else if (EQ(rule_keyword,Qwhen) || EQ(rule_keyword,Qwhenever)) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) &  ~(SI_Long)2048L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) &  ~(SI_Long)2L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) &  ~(SI_Long)8L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	update_representations_of_slot_value(2,rule,Qframe_flags);
    }
    else {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(rule,Qframe_flags);
	svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) &  ~(SI_Long)2048L;
	ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
    }
    if ((EQ(rule_keyword,Qinitially) || EQ(rule_keyword,Qwhenever)) && 
	    ISVREF(rule,(SI_Long)20L))
	set_slot_value_and_update_representations(3,rule,
		Qrule_scan_interval,Nil);
    translation = maybe_add_more_local_names(translation);
    original_compile = Nil;
    current_computation_frame = rule;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    2);
      current_computation_component_particulars = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
	      1);
	focal_classes = ISVREF(rule,(SI_Long)22L);
	general_compilation = compile_rule(translation,Nil,Nil,CAR(rule_data));
	chaining_links = general_compilation ? 
		generate_forward_and_backward_chaining_links(rule,
		translation) : Nil;
	general_compilation_context = SECOND(general_compilation);
	collected_roles = Nil;
	link_1 = Nil;
	ab_loop_list_ = chaining_links;
	focus_role_qm = Nil;
	second_focus_role_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	link_1 = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Forward_chaining_link_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    focus_role_qm = ISVREF(link_1,(SI_Long)4L);
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Backward_chaining_link_class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		focus_role_qm = ISVREF(link_1,(SI_Long)4L);
	    else
		focus_role_qm = Qnil;
	}
	sub_class_bit_vector = ISVREF(ISVREF(link_1,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Forward_chaining_link_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
	second_focus_role_qm = temp_1 ? ISVREF(link_1,(SI_Long)9L) : Nil;
	if (focus_role_qm &&  !TRUEP(memq_function(focus_role_qm,
		collected_roles)))
	    collected_roles = phrase_cons(focus_role_qm,collected_roles);
	if (second_focus_role_qm &&  
		!TRUEP(memq_function(second_focus_role_qm,collected_roles)))
	    collected_roles = phrase_cons(second_focus_role_qm,
		    collected_roles);
	goto next_loop_1;
      end_loop_1:
	chaining_roles = collected_roles;
	goto end_2;
	chaining_roles = Qnil;
      end_2:;
	focus_compilations = Nil;
	change_slot_value(3,rule,Qrule_chaining_links,chaining_links);
	if (general_compilation) {
	    name = Nil;
	    ab_loop_list_ = focal_classes;
	    focus_compilation = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    focus_compilation = compile_rule(translation,name,
		    general_compilation_context,CAR(rule_data));
	    if (CONSP(focus_compilation)) {
		temp = M_CAR(focus_compilation);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(M_CDR(M_CAR(focus_compilation)),
		    Quniversal_compilation) : TRUEP(Nil))
		add_to_frame_note_particulars_list_if_necessary(name,
			Qfocus_class_compilation_failed,rule);
	    else
		focus_compilations = nconc2(focus_compilations,
			focus_compilation);
	    goto next_loop_2;
	  end_loop_2:;
	    name = Nil;
	    ab_loop_list_ = chaining_roles;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    name = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp = focus_compilations;
	    focus_compilations = nconc2(temp,compile_rule(translation,name,
		    general_compilation_context,CAR(rule_data)));
	    goto next_loop_3;
	  end_loop_3:;
	    temp = translation;
	    original_compile = phrase_cons(temp,nconc2(general_compilation,
		    focus_compilations));
	}
	result_1 = Nil;
	current_flag_state_qm = Nil;
	slot_description = 
		get_slot_description_of_class_description_function(Qframe_status_and_notes,
		ISVREF(rule,(SI_Long)1L),Nil);
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_2 = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value_1 = M_CDR(new_cons);
	    SVREF(temp_2,svref_arg_2) = svref_new_value_1;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_2,svref_arg_2) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_stack_change_cons_pool();
	if (Nil)
	    gensymed_symbol_4 = nconc2(stack_change_list_2(rule,
		    slot_description),stack_change_cons_1(Nil,Nil));
	else {
	    new_cons = ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_2 = Available_stack_change_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value_1 = M_CDR(new_cons);
		SVREF(temp_2,svref_arg_2) = svref_new_value_1;
		if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_stack_change_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = Nil;
		}
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_stack_change_cons_pool();
	    M_CAR(gensymed_symbol_4) = rule;
	    M_CDR(gensymed_symbol_4) = slot_description;
	    inline_note_allocate_cons(gensymed_symbol_4,Qstack_change);
	}
	M_CAR(gensymed_symbol) = gensymed_symbol_4;
	temp_2 = Stack_of_slot_value_changes;
	M_CDR(gensymed_symbol) = temp_2;
	inline_note_allocate_cons(gensymed_symbol,Qstack_change);
	stack_of_slot_value_changes = gensymed_symbol;
	PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
		0);
	  current_flag_state_qm = (SI_Long)0L != (IFIX(ISVREF(rule,
		  (SI_Long)5L)) & (SI_Long)16777216L) ? T : Nil;
	  if ( !TRUEP(current_flag_state_qm)) {
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(rule,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_4 = rule;
	      gensymed_symbol_5 = Nil;
	      gensymed_symbol_6 = T;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6);
	      svref_new_value = IFIX(ISVREF(rule,(SI_Long)5L)) | 
		      (SI_Long)16777216L;
	      ISVREF(rule,(SI_Long)5L) = FIX(svref_new_value);
	  }
	  if ( !TRUEP(bad_status_compiler_frame_notes_qm(1,rule))) {
	      original_compile = compile_rule_for_stack(rule,original_compile);
	      result_1 = original_compile;
	  }
	  else {
	      remove_compiler_error_and_warning_frame_notes();
	      result_1 = change_slot_value(3,rule,Qrule_byte_code_body,Nil);
	  }
	  if ( !TRUEP(current_flag_state_qm)) {
	      svref_new_value = IFIX(ISVREF(rule,(SI_Long)5L)) &  
		      ~(SI_Long)16777216L;
	      ISVREF(rule,(SI_Long)5L) = FIX(svref_new_value);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(rule,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)3L),(SI_Long)1L);
	      gensymed_symbol_4 = rule;
	      gensymed_symbol_5 = T;
	      gensymed_symbol_6 = Nil;
	      inline_funcall_3(gensymed_symbol,gensymed_symbol_4,
		      gensymed_symbol_5,gensymed_symbol_6);
	  }
	  temp_1 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
	  if (temp_1);
	  else if (M_CDR(Stack_of_slot_value_changes)) {
	      frame_and_slot_or_atom = Nil;
	      ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	      ab_loop_it_ = Nil;
	    next_loop_4:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_4;
	      frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (ATOM(frame_and_slot_or_atom))
		  goto end_loop_4;
	      temp_1 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	      if (temp_1);
	      else {
		  temp = M_CDR(frame_and_slot_or_atom);
		  temp_1 = CONSP(temp) ? EQ(slot_description,
			  SECOND(frame_and_slot_or_atom)) && EQ(Nil,
			  THIRD(frame_and_slot_or_atom)) && EQ(Nil,
			  CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	      }
	      ab_loop_it_ = temp_1 ? (EQ(rule,
		      M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_3;
	      }
	      goto next_loop_4;
	    end_loop_4:
	      temp_1 = TRUEP(Qnil);
	    end_3:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if ( !temp_1)
	      update_all_representations_of_slot(rule,slot_description,Nil,
		      Nil);
	  if (ISVREF(slot_description,(SI_Long)14L))
	      update_frame_name_references(rule);
	  stack_change_pop_store = Nil;
	  cons_1 = Stack_of_slot_value_changes;
	  if (cons_1) {
	      stack_change_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qstack_change);
	      if (ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_2 = 
			  ISVREF(Available_stack_change_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_2) = cons_1;
		  temp_2 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_2 = Available_stack_change_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = cons_1;
		  temp_2 = Available_stack_change_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_2,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Stack_of_slot_value_changes = next_cons;
	  reclaim_stack_change_tree_1(stack_change_pop_store);
	  if (Stack_of_slot_value_changes) {
	      temp = M_CAR(Stack_of_slot_value_changes);
	      temp_1 = ATOM(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1 ?  
		  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) : 
		  TRUEP(Nil))
	      do_deferred_updates_to_representations_in_tables();
	POP_SPECIAL();
	if (Current_computation_component_particulars)
	    temp_1 = 
		    TRUEP(get_particulars_of_frame_note_from_component_particulars(Qcompiler_errors,
		    rule,Current_computation_component_particulars));
	else {
	    temp = ISVREF(rule,(SI_Long)8L);
	    temp_1 = TRUEP(getfq_function_no_default(CDR(temp),
		    Qcompiler_errors));
	}
	if (temp_1);
	else
	    temp_1 = TRUEP(bad_status_compiler_frame_notes_qm(1,rule));
	update_frame_status(rule,temp_1 ? Qbad : Nil,Nil);
	if (needs_to_be_reactivated_qm) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(rule,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	    gensymed_symbol_4 = rule;
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_4);
	}
	result = VALUES_1(original_compile);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qnone;               /* none */

/* COMPILE-NUPEC-EXTRA-ACTION-LIST-FOR-SLOT */
Object compile_nupec_extra_action_list_for_slot varargs_1(int, n)
{
    Object nupec_extra_action_list_qm, rule, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(151,47);
    INIT_ARGS_nonrelocating();
    nupec_extra_action_list_qm = REQUIRED_ARG_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if ( !TRUEP(nupec_extra_action_list_qm))
	return VALUES_1(Nil);
    else if (EQ(nupec_extra_action_list_qm,Qnone))
	return VALUES_1(Nil);
    else if (EQ(CAR(nupec_extra_action_list_qm),Qand))
	return VALUES_1(CDR(nupec_extra_action_list_qm));
    else
	return phrase_cons(nupec_extra_action_list_qm,Nil);
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* PUT-NUPEC-EXTRA-ACTIONS */
Object put_nupec_extra_actions(rule,nupec_extra_actions,initializing_qm)
    Object rule, nupec_extra_actions, initializing_qm;
{
    Object temp, temp_1, rule_text_qm;

    x_note_fn_call(151,48);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qnupec_extra_actions);
    temp = set_lookup_slot_value_1(rule,Qnupec_extra_actions,
	    nupec_extra_actions);
    if ( !TRUEP(initializing_qm)) {
	temp_1 = ISVREF(rule,(SI_Long)16L);
	rule_text_qm = CDR(temp_1);
	if (rule_text_qm) {
	    temp_1 = copy_text(rule_text_qm);
	    parse_text_for_slot(3,temp_1,rule,
		    get_slot_description_of_class_description_function(Qbox_translation_and_text,
		    ISVREF(rule,(SI_Long)1L),Nil));
	}
    }
    return VALUES_1(temp);
}

/* COMPILE-FOCAL-CLASSES-FOR-SLOT */
Object compile_focal_classes_for_slot varargs_1(int, n)
{
    Object translation, gensymed_symbol, gensymed_symbol_1;
    Object compiled_focal_classes;
    Declare_varargs_nonrelocating;

    x_note_fn_call(151,49);
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
    if (EQ(translation,Qnone))
	compiled_focal_classes = Nil;
    else if (SYMBOLP(translation))
	compiled_focal_classes = phrase_cons(translation,Nil);
    else
	compiled_focal_classes = CDR(translation);
    return VALUES_1(compiled_focal_classes);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_2;   /* "~NT " */

static Object string_constant_3;   /* "~NV must be one of the following types: ~a" */

/* FOCAL-CLASSES-EVALUATION-SETTER */
Object focal_classes_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object rule_category, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(151,50);
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
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_focal_classes_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_7))
	result = VALUES_1(Qnone);
    else if (type_specification_type_p(gensymed_symbol,list_constant_8)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	rule_category = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_1)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	rule_category = validated_elt;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = rule_category;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
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
	result = phrase_cons(Qand,temp_1);
    }
    else {
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
	      length_2 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_2 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_2,list_constant_7);
		  tformat(2,string_constant_2,list_constant_8);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_3,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_focal_classes_evaluation_setter:
    return result;
}

/* FOCAL-CLASSES-EVALUATION-GETTER */
Object focal_classes_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object rule_category, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, temp;

    x_note_fn_call(151,51);
    if (slot_value) {
	rule_category = Nil;
	ab_loop_list_ = slot_value;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	rule_category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(rule_category,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* PUT-RULE-CHAINING-LINKS */
Object put_rule_chaining_links(rule,new_links,initializing_qm)
    Object rule, new_links, initializing_qm;
{
    Object old_links;

    x_note_fn_call(151,52);
    if (initializing_qm &&  !TRUEP(compilations_up_to_date_p(rule)) && 
	    Loading_kb_p) {
	reclaim_slot_value(new_links);
	new_links = Nil;
	note_frame_with_compilation_removed(rule);
    }
    old_links = ISVREF(rule,(SI_Long)30L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_chaining_links);
    SVREF(rule,FIX((SI_Long)30L)) = new_links;
    deinstall_chaining_links(old_links);
    install_chaining_links(new_links);
    return VALUES_1(new_links);
}

/* PUT-RULE-BYTE-CODE-BODY */
Object put_rule_byte_code_body(rule,new_byte_code_body,initializing_qm)
    Object rule, new_byte_code_body, initializing_qm;
{
    x_note_fn_call(151,53);
    if (initializing_qm &&  !TRUEP(compilations_up_to_date_p(rule)) && 
	    Loading_kb_p) {
	reclaim_slot_value(new_byte_code_body);
	new_byte_code_body = Nil;
	note_frame_with_compilation_removed(rule);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(rule,Qrule_byte_code_body);
    SVREF(rule,FIX((SI_Long)31L)) = new_byte_code_body;
    return VALUES_1(new_byte_code_body);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object Qbackward_chain;     /* backward-chain */

static Object Qinvocable_via_backward_chaining;  /* invocable-via-backward-chaining */

static Object Qnot_invocable_via_backward_chaining;  /* not-invocable-via-backward-chaining */

static Object Qforward_chain;      /* forward-chain */

static Object Qinvocable_via_forward_chaining;  /* invocable-via-forward-chaining */

static Object Qnot_invocable_via_forward_chaining;  /* not-invocable-via-forward-chaining */

static Object Qdata_seeking;       /* data-seeking */

static Object Qmay_cause_data_seeking;  /* may-cause-data-seeking */

static Object Qmay_not_cause_data_seeking;  /* may-not-cause-data-seeking */

static Object Qcause_forward;      /* cause-forward */

static Object Qmay_cause_forward_chaining;  /* may-cause-forward-chaining */

static Object Qmay_not_cause_forward_chaining;  /* may-not-cause-forward-chaining */

static Object Qexplanation_data;   /* explanation-data */

static Object Qcache_data_for_explanation_flag;  /* cache-data-for-explanation-flag */

/* RULE-FRAME-FLAGS-EVALUATION-SETTER */
Object rule_frame_flags_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object backward_chaining_phrase, forward_chaining_phrase;
    Object data_seeking_phrase, cause_forward_phrase, explanation_phrase;
    Object gensymed_symbol_1;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(151,54);
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
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_rule_frame_flags_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qbackward_chain,Nil);
    backward_chaining_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qbackward_chain,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qbackward_chain,Nil)),Truth) ? 
	    Qinvocable_via_backward_chaining : 
	    Qnot_invocable_via_backward_chaining;
    temp_1 = estructure_slot(gensymed_symbol,Qforward_chain,Nil);
    forward_chaining_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qforward_chain,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qforward_chain,Nil)),Truth) ? Qinvocable_via_forward_chaining :
	     Qnot_invocable_via_forward_chaining;
    temp_1 = estructure_slot(gensymed_symbol,Qdata_seeking,Nil);
    data_seeking_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qdata_seeking,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qdata_seeking,Nil)),Truth) ? Qmay_cause_data_seeking : 
	    Qmay_not_cause_data_seeking;
    temp_1 = estructure_slot(gensymed_symbol,Qcause_forward,Nil);
    cause_forward_phrase = CONSP(temp_1) && 
	    EQ(M_CDR(estructure_slot(gensymed_symbol,Qcause_forward,Nil)),
	    Qtruth_value) && EQ(M_CAR(estructure_slot(gensymed_symbol,
	    Qcause_forward,Nil)),Truth) ? Qmay_cause_forward_chaining : 
	    Qmay_not_cause_forward_chaining;
    if (explanation_related_features_enabled_func_qm()) {
	temp_1 = estructure_slot(gensymed_symbol,Qexplanation_data,Nil);
	temp_2 = CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,
		Qexplanation_data,Nil)),Qtruth_value) ? 
		EQ(M_CAR(estructure_slot(gensymed_symbol,Qexplanation_data,
		Nil)),Truth) : TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    explanation_phrase = temp_2 ? Qcache_data_for_explanation_flag : Nil;
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = backward_chaining_phrase;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = forward_chaining_phrase;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = data_seeking_phrase;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = cause_forward_phrase;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = explanation_phrase;
    result = VALUES_1(gensymed_symbol);
  end_rule_frame_flags_evaluation_setter:
    return result;
}

/* RULE-FRAME-FLAGS-EVALUATION-GETTER */
Object rule_frame_flags_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(151,55);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(gensymed_symbol,Qbackward_chain,
		(SI_Long)0L != (IFIX(slot_value) & (SI_Long)2L) ? 
		Evaluation_true_value : Evaluation_false_value);
	set_evaluation_structure_slot(gensymed_symbol,Qforward_chain,
		(SI_Long)0L != (IFIX(slot_value) & (SI_Long)8L) ? 
		Evaluation_true_value : Evaluation_false_value);
	if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)16L))
	    set_evaluation_structure_slot(gensymed_symbol,Qdata_seeking,T ?
		     Evaluation_true_value : Evaluation_false_value);
	if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)32768L))
	    set_evaluation_structure_slot(gensymed_symbol,Qcause_forward,T 
		    ? Evaluation_true_value : Evaluation_false_value);
	if ((SI_Long)0L != (IFIX(slot_value) & (SI_Long)1048576L))
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qexplanation_data,T ? Evaluation_true_value : 
		    Evaluation_false_value);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* COMPILE-RULE-FRAME-FLAGS-FOR-SLOT */
Object compile_rule_frame_flags_for_slot varargs_1(int, n)
{
    Object parse_result, rule, gensymed_symbol;
    Object flags;
    Declare_varargs_nonrelocating;

    x_note_fn_call(151,56);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    flags = ISVREF(rule,(SI_Long)4L);
    gensymed_symbol = ISVREF(rule,(SI_Long)32L);
    if (EQ(gensymed_symbol,Qwhen) || EQ(gensymed_symbol,Qwhenever)) {
	flags = FIX(IFIX(flags) &  
		~IFIX(Invocable_via_backward_chaining_flag));
	flags = FIX(IFIX(flags) &  ~IFIX(Invocable_via_forward_chaining_flag));
    }
    else {
	if (EQ(FIRST(parse_result),Qinvocable_via_backward_chaining))
	    flags = FIXNUM_LOGIOR(flags,Invocable_via_backward_chaining_flag);
	else
	    flags = FIX(IFIX(flags) &  
		    ~IFIX(Invocable_via_backward_chaining_flag));
	if (EQ(SECOND(parse_result),Qinvocable_via_forward_chaining))
	    flags = FIXNUM_LOGIOR(flags,Invocable_via_forward_chaining_flag);
	else
	    flags = FIX(IFIX(flags) &  
		    ~IFIX(Invocable_via_forward_chaining_flag));
    }
    if (CDDR(parse_result)) {
	if (memq_function(Qmay_cause_data_seeking,parse_result))
	    flags = FIXNUM_LOGIOR(flags,May_cause_data_seeking_flag);
	else
	    flags = FIX(IFIX(flags) &  ~IFIX(May_cause_data_seeking_flag));
	if (memq_function(Qmay_cause_forward_chaining,parse_result))
	    flags = FIXNUM_LOGIOR(flags,May_cause_forward_chaining_flag);
	else
	    flags = FIX(IFIX(flags) &  ~IFIX(May_cause_forward_chaining_flag));
	if (memq_function(Qcache_data_for_explanation_flag,parse_result))
	    flags = FIXNUM_LOGIOR(flags,Cache_data_for_explanation_flag);
	else
	    flags = FIX(IFIX(flags) &  ~IFIX(Cache_data_for_explanation_flag));
    }
    return VALUES_1(flags);
}

/* CLEAR-CACHED-EXPLANATIONS */
Object clear_cached_explanations(rule)
    Object rule;
{
    Object scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, rule_instance, cached_variables_qm;
    Object ab_less_than_branch_qm_, gensymed_symbol, temp;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(151,57);
    scope_conses = Scope_conses;
    ab_hash_table_ = ISVREF(rule,(SI_Long)27L);
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
      cached_variables_qm = Nil;
      ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
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
		      (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
      }
      else if (ab_current_node_) {
	  ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	  if (ab_current_node_) {
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_1:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
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
		  ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
		  goto end_loop_1;
	      }
	  }
	  else {
	      ab_current_node_ = CDR(ab_tree_form_);
	      if (ab_current_node_) {
		  ab_less_than_branch_qm_ = Nil;
		next_loop_3:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop_2;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_3;
		end_loop_2:;
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
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
      cached_variables_qm = ISVREF(rule_instance,(SI_Long)21L);
      if (cached_variables_qm) {
	  reclaim_evaluation_variables_list(cached_variables_qm);
	  SVREF(rule_instance,FIX((SI_Long)21L)) = Nil;
      }
      goto next_loop;
    end_loop_3:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "invocable via backward chaining, " */

static Object string_constant_5;   /* "not invocable via backward chaining, " */

static Object string_constant_6;   /* "invocable via forward chaining, " */

static Object string_constant_7;   /* "not invocable via forward chaining, " */

static Object string_constant_8;   /* "may cause data seeking, " */

static Object string_constant_9;   /* "may not cause data seeking, " */

static Object string_constant_10;  /* "may cause forward chaining" */

static Object string_constant_11;  /* "may not cause forward chaining" */

static Object string_constant_12;  /* ", cache data for explanation" */

static Object string_constant_13;  /* ", do not cache data for explanation" */

/* WRITE-RULE-FRAME-FLAGS-FROM-SLOT */
Object write_rule_frame_flags_from_slot(value,rule)
    Object value, rule;
{
    x_note_fn_call(151,58);
    twrite_general_string((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)2L) ? string_constant_4 : string_constant_5);
    twrite_general_string((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)8L) ? string_constant_6 : string_constant_7);
    twrite_general_string((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)16L) ? string_constant_8 : string_constant_9);
    twrite_general_string((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	    (SI_Long)32768L) ? string_constant_10 : string_constant_11);
    if (explanation_related_features_enabled_func_qm() || (SI_Long)0L != 
	    (IFIX(ISVREF(rule,(SI_Long)4L)) & (SI_Long)1048576L))
	return twrite_general_string((SI_Long)0L != (IFIX(ISVREF(rule,
		(SI_Long)4L)) & (SI_Long)1048576L) ? string_constant_12 : 
		string_constant_13);
    else
	return VALUES_1(Nil);
}

void rules_INIT()
{
    Object temp, temp_1, temp_2, focal_classes_evaluation_setter_1;
    Object focal_classes_evaluation_getter_1;
    Object rule_frame_flags_evaluation_setter_1;
    Object rule_frame_flags_evaluation_getter_1;
    Object Qslot_value_writer, Qwrite_rule_frame_flags_from_slot;
    Object Qrule_frame_flags, AB_package;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_rule_frame_flags_for_slot, Qnamed;
    Object list_constant_27, list_constant_26, Qab_structure, list_constant_25;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object Qtype_specification_simple_expansion, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object string_constant_85, Qslot_putter, Qput_rule_byte_code_body;
    Object Qput_rule_chaining_links, Qfocal_classes, list_constant_18, Qab_or;
    Object list_constant_17, list_constant_16, Qno_item;
    Object Qcompile_focal_classes_for_slot, Qput_nupec_extra_actions;
    Object Qnupec_extra_action_list, Qcompile_nupec_extra_action_list_for_slot;
    Object Qcompile_rule_for_slot, list_constant_15, list_constant_14;
    Object list_constant_13, list_constant_12, Qchange_the_text_of_attribute;
    Object Qconclude_not, Qconclude, Qsimultaneously, Qin_order;
    Object Qput_rule_scan_interval, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_rule;
    Object Qinitialize_after_reading, Qinitialize_after_reading_for_rule;
    Object Qinitialize_for_rule, Qnote_runs_while_inactive_change;
    Object Qnote_runs_while_inactive_change_for_rule, Qmanually_disable;
    Object Qmanually_disable_for_rule, Qmanually_enable;
    Object Qmanually_enable_for_rule, Qdeactivate, Qdeactivate_for_rule;
    Object Qactivate_for_rule, Qrules;
    Object Qmutate_hashed_rule_instance_tree_for_hash_skip_list_entry;
    Object Qout_hashed_rule_instance_hash_vector_43_vectors;
    Object Qhashed_rule_instance_hash_vector_43_vector_memory_usage;
    Object string_constant_84, Qutilities2, Qsubstitute_class_and_kb_flags;
    Object Qif_rule, Qdepth_first_backward_chaining_precedence;
    Object Qbackward_chaining_precedence, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, list_constant_11, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_51;
    Object string_constant_50, string_constant_49, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_30;
    Object string_constant_29, string_constant_28, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_22, string_constant_21;
    Object string_constant_20, string_constant_19, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object string_constant_14, Qstatement;

    x_note_fn_call(151,59);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    Qstatement = STATIC_SYMBOL("STATEMENT",AB_package);
    list_constant_11 = STATIC_CONS(Qstatement,Qnil);
    check_if_superior_classes_are_defined(Qrule,list_constant_11);
    string_constant_14 = 
	    STATIC_STRING("1n1m8v832Jy1l8t1m83-Cy7399y3-2y3-ky3-hy3-fy3Sy3-my3-ay3-Xy3Sy3-hy3-ky3-by3-Zy3-by3-gy3-Ty3-ey3Sy3-Wy3-hy3-Vy3-ny3-fy3-Xy3-gy3-my");
    string_constant_15 = 
	    STATIC_STRING("3Sy3-my3-ay3-Xy3Sy3-Yy3-hy3-ey3-ey3-hy3-py3-by3-gy3-Zy3Sy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3Sy3-py3-Xy3-ky3-Xy3Sy3-ly3-ay3");
    string_constant_16 = 
	    STATIC_STRING("-hy3-py3-gy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3Sy3-Yy3-ky3-hy3-fy3Sy3-ky3-ny3-ey3-Xy3sy3Sy3-ky3-Xy3-Vy3-hy3-gy3-Vy3-by3-ey3-Xy3g");
    string_constant_17 = 
	    STATIC_STRING("yu3uy3-ny3-ey3wyu3ty3Sy3-9y3-hy3-ly3-my3Sy3-hy3-Yy3Sy3-my3-ay3-Xy3-ly3-Xy3Sy3-Ty3-ky3-Xy3Sy3-Yy3-ky3-hy3-fy3Sy3-Vy3-hy3-fy3-iy3-");
    string_constant_18 = 
	    STATIC_STRING("ny3-my3-Ty3-my3-by3-hy3-gy3fy3-ly3-my3-ry3-ey3-Xy3ey3Sy3-Ty3-gy3-Wy3Sy3-ly3-ay3-hy3-ny3-ey3-Wy3Sy3-iy3-ky3-hy3-Ty3-Uy3-ey3-ry3Sy");
    string_constant_19 = 
	    STATIC_STRING("3-Uy3-Xy3Sy3-ly3-ny3-Uy3-ly3-ny3-fy3-Xy3-Wy3gyu3uy3-8y3-5y3wy3-by3-gy3-oy3-hy3-Vy3-Ty3-Uy3-ey3-Xy3fy3-oy3-by3-Ty3fy3-Uy3-Ty3-Vy3");
    string_constant_20 = 
	    STATIC_STRING("-dy3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3w");
    string_constant_21 = 
	    STATIC_STRING("y3-by3-gy3-oy3-hy3-Vy3-Ty3-Uy3-ey3-Xy3fy3-oy3-by3-Ty3fy3-Yy3-hy3-ky3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3sy3Sy3-ey");
    string_constant_22 = 
	    STATIC_STRING("3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3wy3-fy3-Ty3-ry3fy3-Vy3-Ty3-ny3-ly3-Xy3fy3-Wy3-Ty3-my3-Ty3fy3-ly3-");
    string_constant_23 = 
	    STATIC_STRING("Xy3-Xy3-dy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3wy3-fy3-Ty3-ry3fy3-Vy3-Ty3-ny3-ly");
    string_constant_24 = 
	    STATIC_STRING("3-Xy3fy3-Yy3-hy3-ky3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3");
    string_constant_25 = 
	    STATIC_STRING("eyu3uy3-8y3-5y3wy3-gy3-hy3-my3-Xy3-ly3sy3Sy3ay3Sy3-Ny3Sy3-ly3-hy3-ny3-ky3-Vy3-Xy3sy3Sy3-ly3-ry3-fy3-Uy3-hy3-ey3ey3Sy3-gy3-hy3-my");
    string_constant_26 = 
	    STATIC_STRING("3-Xy3sy3Sy3-my3-Xy3-qy3-my3Sy3-Py3Sy3cy3Sy3by3eyu3uy3-8y3-5y3wy3-Ty3-ny3-my3-ay3-hy3-ky3-ly3sy3Sy3ay3-Ny3Sy3-gy3-Ty3-fy3-Xy3sy3S");
    string_constant_27 = 
	    STATIC_STRING("y3-gy3-Ty3-fy3-Xy3ey3Sy3-Wy3-Ty3-my3-Xy3sy3Sy3-Zy3-Xy3-gy3-ly3-ry3-fy3fy3-my3-by3-fy3-Xy3Sy3-Py3Sy3cy3Sy3by3eyu3uy3-8y3-5y3wy3-m");
    string_constant_28 = 
	    STATIC_STRING("y3-Xy3-qy3-my3eyu3uy3-8y3-5y3wy3-ly3-Vy3-Ty3-gy3fy3-by3-gy3-my3-Xy3-ky3-oy3-Ty3-ey3sy3Sy3-my3-by3-fy3-Xy3fy3-by3-gy3-my3-Xy3-ky3");
    string_constant_29 = 
	    STATIC_STRING("-oy3-Ty3-ey3fy3-iy3-Ty3-ky3-my3eytt3ty3Sy3-ky3-ny3-ey3-Xy3fy3-ly3-Vy3-Ty3-gy3fy3-by3-gy3-my3-Xy3-ky3-oy3-Ty3-eyuu3uy3-ey3-by3wy3");
    string_constant_30 = 
	    STATIC_STRING("-Yy3-hy3-Vy3-Ty3-ey3fy3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3sy3Sy3ay3Sy3-Vy3-ey3-Ty3-ly3-ly3fy3-gy3-Ty3-fy3-Xy3Sy3cy3by3eyu3uy3-8y3-5y3wy");
    string_constant_31 = 
	    STATIC_STRING("3-Yy3-hy3-Vy3-Ty3-ey3fy3-hy3-Uy3-cy3-Xy3-Vy3-my3-ly3sy3Sy3eyu3uy3-8y3-5y3wy3-Vy3-Ty3-my3-Xy3-Zy3-hy3-ky3-by3-Xy3-ly3eytt3ty3Sy3-");
    string_constant_32 = 
	    STATIC_STRING("ky3-ny3-ey3-Xy3fy3-Vy3-Ty3-my3-Xy3-Zy3-hy3-ky3-by3-Xy3-ly3eyu3uy3-8y3-5y3wy3-ky3-ny3-ey3-Xy3fy3-iy3-ky3-by3-hy3-ky3-by3-my3-ry3s");
    string_constant_33 = 
	    STATIC_STRING("y3Sy3-iy3-ky3-by3-hy3-ky3-by3-my3-ry3eyu3uy3-8y3-5y3wy3-Wy3-Xy3-iy3-my3-ay3fy3-Yy3-by3-ky3-ly3-my3fy3-Uy3-Ty3-Vy3-dy3-py3-Ty3-ky");
    string_constant_34 = 
	    STATIC_STRING("3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3fy3-iy3-ky3-Xy3-Vy3-Xy3-Wy3-Xy3-gy3-Vy3-Xy3eyu3uy3-8y3-5y3wy3-my3-by3-fy3-Xy3-hy3-ny3-my");
    string_constant_35 = 
	    STATIC_STRING("3fy3-Yy3-hy3-ky3fy3-ky3-ny3-ey3-Xy3fy3-Vy3-hy3-fy3-iy3-ey3-Xy3-my3-by3-hy3-gy3eyu3uy3Ty3fy3fy3Sy3-gy3-ny3-iy3-Xy3-Vy3fy3-Xy3-qy3");
    string_constant_36 = 
	    STATIC_STRING("-my3-ky3-Ty3fy3-Ty3-Vy3-my3-by3-hy3-gy3-ly3ey3fy3fy3wyu3uy3-8y3-5y3wy3-ky3-ny3-ey3-Xy3fy3-ly3-Vy3-Ty3-gy3fy3-my3-Ty3-ly3-dy3xy3e");
    string_constant_37 = 
	    STATIC_STRING("yu3uy3-8y3-5y3wy3-Yy3-hy3-Vy3-Ty3-ey3fy3-ky3-hy3-ey3-Xy3-ly3fy3-Yy3-hy3-ky3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3eyu3uy3-8y3-5y3wy3");
    string_constant_38 = 
	    STATIC_STRING("-ky3-ny3-ey3-Xy3fy3-dy3-Xy3-ry3-py3-hy3-ky3-Wyu3uy3hy3-ny3-ey3wy");
    string_constant_39 = 
	    STATIC_STRING("13Jy4z8r83-Ey83-Ey832Jy832Jy034+My001q1l8o1l8l1m8p83Ery1l83Hy1l83*8y1m83Dy5305yCurrently frame-flags is aliased ~\nto options. I ");
    string_constant_40 = 
	    STATIC_STRING("think individual attribute-mimics should be created for ~\nparticular flags, and I don\'t know if options should continue to be su");
    string_constant_41 = 
	    STATIC_STRING("pported. This\ncomment should show up on options, despite it being placed on frame-flags.000004z8r83--y83--y832Jy832Jy00001p1l8l1");
    string_constant_42 = 
	    STATIC_STRING("m8p83-*y1l83Ey1l83Uy1m83Dy53*syWill allow 0 or more author entries. each author entry may have a date. ~\nauthors: ([ name: symbo");
    string_constant_43 = 
	    STATIC_STRING("l, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true\n000004z8r83-0y83-0y832Jy832Jy00001q1l8l");
    string_constant_44 = 
	    STATIC_STRING("1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-Fy(to replace authors attribute; however, no documentation is available at this time)000004z");
    string_constant_45 = 
	    STATIC_STRING("8r83ry83ry832Jy832Jy00001p1o8p832Jy83Gy832Jy1l8o1l8l1l83-5y1l83-3y000004z8r83X=y83X=y832Jy832Jy00001o1n8p83E5y83Gy1m83Ny83WYy1l8");
    string_constant_46 = 
	    STATIC_STRING("3Ey1l8l000004z8r83Ety83Ety832Jy832Jy00001o1l8o1l8l1l8z1m8p832gy000004z8r83ZOy83ZOy832Jy832Jy00001m1l8o1l8l000004z8r838My838My832");
    string_constant_47 = 
	    STATIC_STRING("Jy832Jy00001o1l8o1l8l1l8z1m8p838My000004z8r838Ny838Ny832Jy832Jy00001o1l8l1l8z1l8o1m8p838Ny000004z8r83Eqy83Eqy832Jy832Jy00001o1l8");
    string_constant_48 = 
	    STATIC_STRING("l1l8z1l8o1m8p837sy000004z8r83Ljy83Ljy832Jy832Jy00001n1l8l1l8o1l83Cy000004z8r83Esy83Esy832Jy832Jy0q001o1l8l1l8z1l8o1m8p83-Yy00000");
    string_constant_49 = 
	    STATIC_STRING("4z8r83-py83-py832Jy832Jy00001q1l8l1l8z1l83Ey1l83Cy1m8p83-py1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntr");
    string_constant_50 = 
	    STATIC_STRING("acing-message-level: (or default &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]000004z8r83RJy83RJy832Jy832J");
    string_constant_51 = 
	    STATIC_STRING("y00001m1l8o1l8l000004z8r83Axy83Axy832Jy832Jy0l001o1l8o1l8l1l8z1m8p83-ey000004z8r83FPy83FPy832Jy832Jy083Py001o1l8o1l8l1l8z1m8p839");
    string_constant_52 = 
	    STATIC_STRING("8y000004z8r83ZIy83ZIy832Jy832Jy00001o1l8o1l8l1l83Cy1l83Uy000004z8r83ZHy83ZHy832Jy832Jy00001o1l8o1l8l1l83Cy1l83Uy000004z8r83ZLy83");
    string_constant_53 = 
	    STATIC_STRING("ZLy832Jy832Jy00001n1l8o1l8l1l83Cy000004z8r83ZJy83ZJy832Jy832Jy0k001n1l8o1l8l1l83Cy000004z8r83ZKy83ZKy832Jy832Jy0k001n1l8o1l8l1l8");
    string_constant_54 = 
	    STATIC_STRING("3Cy000004z8r83ZNy83ZNy832Jy832Jy0k001n1l8o1l8l1l83Cy000004z8r83ZMy83ZMy832Jy832Jy0k001n1l8o1l8l1l83Cy00000");
    string_constant_55 = 
	    STATIC_STRING("13Ly8q1p832Jy1l83*ry1m8v832Jy8t1m83-Cy7399y3-2y3-ky3-hy3-fy3Sy3-my3-ay3-Xy3Sy3-hy3-ky3-by3-Zy3-by3-gy3-Ty3-ey3Sy3-Wy3-hy3-Vy3-ny");
    string_constant_56 = 
	    STATIC_STRING("3-fy3-Xy3-gy3-my3Sy3-my3-ay3-Xy3Sy3-Yy3-hy3-ey3-ey3-hy3-py3-by3-gy3-Zy3Sy3-Ty3-my3-my3-ky3-by3-Uy3-ny3-my3-Xy3-ly3Sy3-py3-Xy3-ky");
    string_constant_57 = 
	    STATIC_STRING("3-Xy3Sy3-ly3-ay3-hy3-py3-gy3Sy3-Xy3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3Sy3-Yy3-ky3-hy3-fy3Sy3-ky3-ny3-ey3-Xy3sy3Sy3-ky3-Xy3-Vy3-hy3-gy3-");
    string_constant_58 = 
	    STATIC_STRING("Vy3-by3-ey3-Xy3gyu3uy3-ny3-ey3wyu3ty3Sy3-9y3-hy3-ly3-my3Sy3-hy3-Yy3Sy3-my3-ay3-Xy3-ly3-Xy3Sy3-Ty3-ky3-Xy3Sy3-Yy3-ky3-hy3-fy3Sy3-");
    string_constant_59 = 
	    STATIC_STRING("Vy3-hy3-fy3-iy3-ny3-my3-Ty3-my3-by3-hy3-gy3fy3-ly3-my3-ry3-ey3-Xy3ey3Sy3-Ty3-gy3-Wy3Sy3-ly3-ay3-hy3-ny3-ey3-Wy3Sy3-iy3-ky3-hy3-T");
    string_constant_60 = 
	    STATIC_STRING("y3-Uy3-ey3-ry3Sy3-Uy3-Xy3Sy3-ly3-ny3-Uy3-ly3-ny3-fy3-Xy3-Wy3gyu3uy3-8y3-5y3wy3-by3-gy3-oy3-hy3-Vy3-Ty3-Uy3-ey3-Xy3fy3-oy3-by3-Ty");
    string_constant_61 = 
	    STATIC_STRING("3fy3-Uy3-Ty3-Vy3-dy3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3");
    string_constant_62 = 
	    STATIC_STRING("eyu3uy3-8y3-5y3wy3-by3-gy3-oy3-hy3-Vy3-Ty3-Uy3-ey3-Xy3fy3-oy3-by3-Ty3fy3-Yy3-hy3-ky3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-");
    string_constant_63 = 
	    STATIC_STRING("gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3wy3-fy3-Ty3-ry3fy3-Vy3-Ty3-ny3-ly3-Xy3fy3-Wy3-Ty3");
    string_constant_64 = 
	    STATIC_STRING("-my3-Ty3fy3-ly3-Xy3-Xy3-dy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3wy3-fy3-Ty3-ry3fy");
    string_constant_65 = 
	    STATIC_STRING("3-Vy3-Ty3-ny3-ly3-Xy3fy3-Yy3-hy3-ky3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3sy3Sy3-ey3-hy3-Zy3-by3-Vy3-Ty3-ey3fy3-oy3");
    string_constant_66 = 
	    STATIC_STRING("-Ty3-ey3-ny3-Xy3eyu3uy3-8y3-5y3wy3-gy3-hy3-my3-Xy3-ly3sy3Sy3ay3Sy3-Ny3Sy3-ly3-hy3-ny3-ky3-Vy3-Xy3sy3Sy3-ly3-ry3-fy3-Uy3-hy3-ey3e");
    string_constant_67 = 
	    STATIC_STRING("y3Sy3-gy3-hy3-my3-Xy3sy3Sy3-my3-Xy3-qy3-my3Sy3-Py3Sy3cy3Sy3by3eyu3uy3-8y3-5y3wy3-Ty3-ny3-my3-ay3-hy3-ky3-ly3sy3Sy3ay3-Ny3Sy3-gy3");
    string_constant_68 = 
	    STATIC_STRING("-Ty3-fy3-Xy3sy3Sy3-gy3-Ty3-fy3-Xy3ey3Sy3-Wy3-Ty3-my3-Xy3sy3Sy3-Zy3-Xy3-gy3-ly3-ry3-fy3fy3-my3-by3-fy3-Xy3Sy3-Py3Sy3cy3Sy3by3eyu3");
    string_constant_69 = 
	    STATIC_STRING("uy3-8y3-5y3wy3-my3-Xy3-qy3-my3eyu3uy3-8y3-5y3wy3-ly3-Vy3-Ty3-gy3fy3-by3-gy3-my3-Xy3-ky3-oy3-Ty3-ey3sy3Sy3-my3-by3-fy3-Xy3fy3-by3");
    string_constant_70 = 
	    STATIC_STRING("-gy3-my3-Xy3-ky3-oy3-Ty3-ey3fy3-iy3-Ty3-ky3-my3eytt3ty3Sy3-ky3-ny3-ey3-Xy3fy3-ly3-Vy3-Ty3-gy3fy3-by3-gy3-my3-Xy3-ky3-oy3-Ty3-eyu");
    string_constant_71 = 
	    STATIC_STRING("u3uy3-ey3-by3wy3-Yy3-hy3-Vy3-Ty3-ey3fy3-Vy3-ey3-Ty3-ly3-ly3-Xy3-ly3sy3Sy3ay3Sy3-Vy3-ey3-Ty3-ly3-ly3fy3-gy3-Ty3-fy3-Xy3Sy3cy3by3e");
    string_constant_72 = 
	    STATIC_STRING("yu3uy3-8y3-5y3wy3-Yy3-hy3-Vy3-Ty3-ey3fy3-hy3-Uy3-cy3-Xy3-Vy3-my3-ly3sy3Sy3eyu3uy3-8y3-5y3wy3-Vy3-Ty3-my3-Xy3-Zy3-hy3-ky3-by3-Xy3");
    string_constant_73 = 
	    STATIC_STRING("-ly3eytt3ty3Sy3-ky3-ny3-ey3-Xy3fy3-Vy3-Ty3-my3-Xy3-Zy3-hy3-ky3-by3-Xy3-ly3eyu3uy3-8y3-5y3wy3-ky3-ny3-ey3-Xy3fy3-iy3-ky3-by3-hy3-");
    string_constant_74 = 
	    STATIC_STRING("ky3-by3-my3-ry3sy3Sy3-iy3-ky3-by3-hy3-ky3-by3-my3-ry3eyu3uy3-8y3-5y3wy3-Wy3-Xy3-iy3-my3-ay3fy3-Yy3-by3-ky3-ly3-my3fy3-Uy3-Ty3-Vy");
    string_constant_75 = 
	    STATIC_STRING("3-dy3-py3-Ty3-ky3-Wy3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3fy3-iy3-ky3-Xy3-Vy3-Xy3-Wy3-Xy3-gy3-Vy3-Xy3eyu3uy3-8y3-5y3wy3-my3-by3-fy");
    string_constant_76 = 
	    STATIC_STRING("3-Xy3-hy3-ny3-my3fy3-Yy3-hy3-ky3fy3-ky3-ny3-ey3-Xy3fy3-Vy3-hy3-fy3-iy3-ey3-Xy3-my3-by3-hy3-gy3eyu3uy3Ty3fy3fy3Sy3-gy3-ny3-iy3-Xy");
    string_constant_77 = 
	    STATIC_STRING("3-Vy3fy3-Xy3-qy3-my3-ky3-Ty3fy3-Ty3-Vy3-my3-by3-hy3-gy3-ly3ey3fy3fy3wyu3uy3-8y3-5y3wy3-ky3-ny3-ey3-Xy3fy3-ly3-Vy3-Ty3-gy3fy3-my3");
    string_constant_78 = 
	    STATIC_STRING("-Ty3-ly3-dy3xy3eyu3uy3-8y3-5y3wy3-Yy3-hy3-Vy3-Ty3-ey3fy3-ky3-hy3-ey3-Xy3-ly3fy3-Yy3-hy3-ky3fy3-Vy3-ay3-Ty3-by3-gy3-by3-gy3-Zy3ey");
    string_constant_79 = 
	    STATIC_STRING("u3uy3-8y3-5y3wy3-ky3-ny3-ey3-Xy3fy3-dy3-Xy3-ry3-py3-hy3-ky3-Wyu3uy3hy3-ny3-ey3wy1p83-Ey34+My8o8l1m8p83Ery1n83--y01m8p83-*y1n83-0");
    string_constant_80 = 
	    STATIC_STRING("y01m8p83-0y1q83ry01o8p832Jy83Gy832Jy8o8l83-5y1q83X=y01n8p83E5y83Gy1m83Ny83WYy83Ey8l1q83Ety08o8l8z1m8p832gy1o83ZOy08o8l1q838My08o");
    string_constant_81 = 
	    STATIC_STRING("8l8z1m8p838My1q838Ny08l8z8o1m8p838Ny1q83Eqy08l8z8o1m8p837sy1p83Ljy08l8o83Cy1q83Esyq8l8z8o1m8p83-Yy1r83-py08l8z83Ey83Cy1m8p83-py1");
    string_constant_82 = 
	    STATIC_STRING("o83RJy08o8l1q83Axyl8o8l8z1m8p83-ey1q83FPy83Py8o8l8z1m8p8398y1q83ZIy08o8l83Cy83Uy1q83ZHy08o8l83Cy83Uy1p83ZLy08o8l83Cy1p83ZJyk8o8l");
    string_constant_83 = 
	    STATIC_STRING("83Cy1p83ZKyk8o8l83Cy1p83ZNyk8o8l83Cy1p83ZMyk8o8l83Cy");
    temp = regenerate_optimized_constant(list(25,string_constant_14,
	    string_constant_15,string_constant_16,string_constant_17,
	    string_constant_18,string_constant_19,string_constant_20,
	    string_constant_21,string_constant_22,string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33,string_constant_34,string_constant_35,
	    string_constant_36,string_constant_37,string_constant_38));
    temp_1 = regenerate_optimized_constant(list(16,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51,
	    string_constant_52,string_constant_53,string_constant_54));
    add_class_to_environment(9,Qrule,list_constant_11,Nil,temp,Nil,temp_1,
	    list_constant_11,regenerate_optimized_constant(list(29,
	    string_constant_55,string_constant_56,string_constant_57,
	    string_constant_58,string_constant_59,string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80,string_constant_81,
	    string_constant_82,string_constant_83)),Nil);
    Rule_class_description = 
	    lookup_global_or_kb_specific_property_value(Qrule,
	    Class_description_gkbprop);
    Qbackward_chaining_precedence = 
	    STATIC_SYMBOL("BACKWARD-CHAINING-PRECEDENCE",AB_package);
    Qdepth_first_backward_chaining_precedence = 
	    STATIC_SYMBOL("DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE",
	    AB_package);
    alias_slot_name(3,Qbackward_chaining_precedence,
	    Qdepth_first_backward_chaining_precedence,Qnil);
    Qif_rule = STATIC_SYMBOL("IF-RULE",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qif_rule,CONS(Qrule,temp),
	    Qsubstitute_class_and_kb_flags);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qequal_rule_context = STATIC_SYMBOL("EQUAL-RULE-CONTEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qequal_rule_context,
	    STATIC_FUNCTION(equal_rule_context,NIL,FALSE,2,2));
    Qinitializing = STATIC_SYMBOL("INITIALIZING",AB_package);
    Qavailable_hashed_rule_instance_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_hashed_rule_instance_hash_vector_43_vectors,
	    Available_hashed_rule_instance_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_hashed_rule_instance_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_hashed_rule_instance_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_hashed_rule_instance_hash_vector_43_vectors,
	    Count_of_hashed_rule_instance_hash_vector_43_vectors);
    record_system_variable(Qcount_of_hashed_rule_instance_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_hashed_rule_instance_hash_vector_43_vectors_vector == 
	    UNBOUND)
	Available_hashed_rule_instance_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_hashed_rule_instance_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qhashed_rule_instance_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("HASHED-RULE-INSTANCE-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_84 = STATIC_STRING("1q83-Xfy83*9y83-Ovy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_hashed_rule_instance_hash_vector_43_vectors);
    push_optimized_constant(Qhashed_rule_instance_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_84));
    SET_SYMBOL_FUNCTION(Qhashed_rule_instance_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(hashed_rule_instance_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_hashed_rule_instance_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_hashed_rule_instance_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_hashed_rule_instance_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-HASHED-RULE-INSTANCE-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_hashed_rule_instance_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_hashed_rule_instance_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_hashed_rule_instance_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_hashed_rule_instance_tree_for_hash_skip_list_entry);
    Qhashed_rule_instance_tree_for_hash = 
	    STATIC_SYMBOL("HASHED-RULE-INSTANCE-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qwithin_activate_for_kb_workspace = 
	    STATIC_SYMBOL("WITHIN-ACTIVATE-FOR-KB-WORKSPACE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwithin_activate_for_kb_workspace,
	    Within_activate_for_kb_workspace);
    Qrules = STATIC_SYMBOL("RULES",AB_package);
    record_system_variable(Qwithin_activate_for_kb_workspace,Qrules,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    Qactivate_for_rule = STATIC_SYMBOL("ACTIVATE-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_rule,
	    STATIC_FUNCTION(activate_for_rule,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_rule);
    set_get(Qrule,Qactivate,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qdeactivate_for_rule = STATIC_SYMBOL("DEACTIVATE-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_rule,
	    STATIC_FUNCTION(deactivate_for_rule,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_rule);
    set_get(Qrule,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    Qmanually_enable_for_rule = STATIC_SYMBOL("MANUALLY-ENABLE-FOR-RULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_enable_for_rule,
	    STATIC_FUNCTION(manually_enable_for_rule,NIL,FALSE,1,1));
    Qmanually_enable = STATIC_SYMBOL("MANUALLY-ENABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qmanually_enable_for_rule);
    set_get(Qrule,Qmanually_enable,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_enable),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qmanually_enable,temp_2,Qclasses_which_define);
    Qmanually_disable_for_rule = STATIC_SYMBOL("MANUALLY-DISABLE-FOR-RULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_disable_for_rule,
	    STATIC_FUNCTION(manually_disable_for_rule,NIL,FALSE,1,1));
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qmanually_disable_for_rule);
    set_get(Qrule,Qmanually_disable,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_disable),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qmanually_disable,temp_2,Qclasses_which_define);
    Qnote_runs_while_inactive_change_for_rule = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-RULE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_rule,
	    STATIC_FUNCTION(note_runs_while_inactive_change_for_rule,NIL,
	    FALSE,1,1));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_rule);
    set_get(Qrule,Qnote_runs_while_inactive_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_runs_while_inactive_change),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qnote_runs_while_inactive_change,temp_2,
	    Qclasses_which_define);
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    Qinitialize_for_rule = STATIC_SYMBOL("INITIALIZE-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_rule,
	    STATIC_FUNCTION(initialize_for_rule,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_rule);
    set_get(Qrule,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qframe_representations = STATIC_SYMBOL("FRAME-REPRESENTATIONS",AB_package);
    Qinitialize_after_reading_for_rule = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_rule,
	    STATIC_FUNCTION(initialize_after_reading_for_rule,NIL,FALSE,1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_rule);
    set_get(Qrule,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qrule_chaining_links = STATIC_SYMBOL("RULE-CHAINING-LINKS",AB_package);
    Qcleanup_for_rule = STATIC_SYMBOL("CLEANUP-FOR-RULE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_rule,STATIC_FUNCTION(cleanup_for_rule,
	    NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_rule);
    set_get(Qrule,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qrule,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinvoke_rule_universally = STATIC_SYMBOL("INVOKE-RULE-UNIVERSALLY",
	    AB_package);
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qwhenever = STATIC_SYMBOL("WHENEVER",AB_package);
    Qinitially = STATIC_SYMBOL("INITIALLY",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qwhenever,Qinitially);
    Qrule_scan_interval = STATIC_SYMBOL("RULE-SCAN-INTERVAL",AB_package);
    Qput_rule_scan_interval = STATIC_SYMBOL("PUT-RULE-SCAN-INTERVAL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_scan_interval,
	    STATIC_FUNCTION(put_rule_scan_interval,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qrule_scan_interval,
	    SYMBOL_FUNCTION(Qput_rule_scan_interval),Qslot_putter);
    Qin_order = STATIC_SYMBOL("IN-ORDER",AB_package);
    Qsimultaneously = STATIC_SYMBOL("SIMULTANEOUSLY",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qand,Qin_order,Qsimultaneously);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qplace_reference_expression = 
	    STATIC_SYMBOL("PLACE-REFERENCE-EXPRESSION",AB_package);
    Qexpression_list = STATIC_SYMBOL("EXPRESSION-LIST",AB_package);
    list_constant_12 = STATIC_CONS(Qplace_reference_expression,
	    Qexpression_list);
    list_constant_13 = STATIC_CONS(Qconclude,list_constant_12);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    list_constant_14 = STATIC_CONS(Qconclude_not,list_constant_12);
    Qchange_the_text_of_attribute = 
	    STATIC_SYMBOL("CHANGE-THE-TEXT-OF-ATTRIBUTE",AB_package);
    list_constant_15 = STATIC_CONS(Qchange_the_text_of_attribute,
	    list_constant_12);
    list_constant_2 = STATIC_LIST((SI_Long)3L,list_constant_13,
	    list_constant_14,list_constant_15);
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    list_constant_3 = STATIC_CONS(Qdesignation,Qexpression_list);
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qmessage_text = STATIC_SYMBOL("MESSAGE-TEXT",AB_package);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    Qdesignation_list = STATIC_SYMBOL("DESIGNATION-LIST",AB_package);
    Qmessage_designation = STATIC_SYMBOL("MESSAGE-DESIGNATION",AB_package);
    Qoperator = STATIC_SYMBOL("OPERATOR",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qthe,Qoperator);
    Qinform_option = STATIC_SYMBOL("INFORM-OPTION",AB_package);
    Qduration = STATIC_SYMBOL("DURATION",AB_package);
    Qshow_or_hide_argument_list = 
	    STATIC_SYMBOL("SHOW-OR-HIDE-ARGUMENT-LIST",AB_package);
    Qcolor_changes = STATIC_SYMBOL("COLOR-CHANGES",AB_package);
    Qcreate_connection_spec = STATIC_SYMBOL("CREATE-CONNECTION-SPEC",
	    AB_package);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    Qscope = STATIC_SYMBOL("SCOPE",AB_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    Qnamed_by_debugging_name = STATIC_SYMBOL("NAMED-BY-DEBUGGING-NAME",
	    AB_package);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qitem_color = STATIC_SYMBOL("ITEM-COLOR",AB_package);
    Qitem_x_position = STATIC_SYMBOL("ITEM-X-POSITION",AB_package);
    Qitem_y_position = STATIC_SYMBOL("ITEM-Y-POSITION",AB_package);
    Qicon_heading = STATIC_SYMBOL("ICON-HEADING",AB_package);
    Qitem_width = STATIC_SYMBOL("ITEM-WIDTH",AB_package);
    Qitem_height = STATIC_SYMBOL("ITEM-HEIGHT",AB_package);
    Qsystem_attribute_as_text = STATIC_SYMBOL("SYSTEM-ATTRIBUTE-AS-TEXT",
	    AB_package);
    Qtext_of_attribute = STATIC_SYMBOL("TEXT-OF-ATTRIBUTE",AB_package);
    Qthis_workspace = STATIC_SYMBOL("THIS-WORKSPACE",AB_package);
    Qthis_window = STATIC_SYMBOL("THIS-WINDOW",AB_package);
    Qthis_rule = STATIC_SYMBOL("THIS-RULE",AB_package);
    Qthis_procedure = STATIC_SYMBOL("THIS-PROCEDURE",AB_package);
    Qthis_procedure_invocation = STATIC_SYMBOL("THIS-PROCEDURE-INVOCATION",
	    AB_package);
    Qnth_element = STATIC_SYMBOL("NTH-ELEMENT",AB_package);
    Qindexed_attribute = STATIC_SYMBOL("INDEXED-ATTRIBUTE",AB_package);
    Qattribute_frame_or_place_reference = 
	    STATIC_SYMBOL("ATTRIBUTE-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qelement_frame_or_place_reference = 
	    STATIC_SYMBOL("ELEMENT-FRAME-OR-PLACE-REFERENCE",AB_package);
    Qclass_qualified_name_frame_or_place_reference = 
	    STATIC_SYMBOL("CLASS-QUALIFIED-NAME-FRAME-OR-PLACE-REFERENCE",
	    AB_package);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    Qnext_procedure_method = STATIC_SYMBOL("NEXT-PROCEDURE-METHOD",AB_package);
    string_constant = STATIC_STRING("COMPILER-~A-1");
    string_constant_1 = STATIC_STRING("COMPILER-~A-~A");
    Qcollect_local_name_reference_info = 
	    STATIC_SYMBOL("COLLECT-LOCAL-NAME-REFERENCE-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qcollect_local_name_reference_info,
	    STATIC_FUNCTION(collect_local_name_reference_info,NIL,FALSE,1,1));
    Qadd_local_names_for_current_reference_info = 
	    STATIC_SYMBOL("ADD-LOCAL-NAMES-FOR-CURRENT-REFERENCE-INFO",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qadd_local_names_for_current_reference_info,
	    STATIC_FUNCTION(add_local_names_for_current_reference_info,NIL,
	    FALSE,1,1));
    Qusing = STATIC_SYMBOL("USING",AB_package);
    Qnupec_extra_actions = STATIC_SYMBOL("NUPEC-EXTRA-ACTIONS",AB_package);
    Qrule_keyword = STATIC_SYMBOL("RULE-KEYWORD",AB_package);
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qab_if = STATIC_SYMBOL("IF",AB_package);
    Quniversal_compilation = STATIC_SYMBOL("UNIVERSAL-COMPILATION",AB_package);
    Qfocus_class_compilation_failed = 
	    STATIC_SYMBOL("FOCUS-CLASS-COMPILATION-FAILED",AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qrule_byte_code_body = STATIC_SYMBOL("RULE-BYTE-CODE-BODY",AB_package);
    Qcompiler_errors = STATIC_SYMBOL("COMPILER-ERRORS",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qcompile_rule_for_slot = STATIC_SYMBOL("COMPILE-RULE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_rule_for_slot,
	    STATIC_FUNCTION(compile_rule_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qrule,SYMBOL_FUNCTION(Qcompile_rule_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qrule,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qnupec_extra_action_list = STATIC_SYMBOL("NUPEC-EXTRA-ACTION-LIST",
	    AB_package);
    Qcompile_nupec_extra_action_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-NUPEC-EXTRA-ACTION-LIST-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_nupec_extra_action_list_for_slot,
	    STATIC_FUNCTION(compile_nupec_extra_action_list_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qnupec_extra_action_list,
	    SYMBOL_FUNCTION(Qcompile_nupec_extra_action_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qnupec_extra_action_list,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    Qput_nupec_extra_actions = STATIC_SYMBOL("PUT-NUPEC-EXTRA-ACTIONS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_nupec_extra_actions,
	    STATIC_FUNCTION(put_nupec_extra_actions,NIL,FALSE,3,3));
    mutate_global_property(Qnupec_extra_actions,
	    SYMBOL_FUNCTION(Qput_nupec_extra_actions),Qslot_putter);
    Qfocal_classes = STATIC_SYMBOL("FOCAL-CLASSES",AB_package);
    Qcompile_focal_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-FOCAL-CLASSES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_focal_classes_for_slot,
	    STATIC_FUNCTION(compile_focal_classes_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qfocal_classes,
	    SYMBOL_FUNCTION(Qcompile_focal_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qfocal_classes,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_7 = STATIC_CONS(Qno_item,Qnil);
    list_constant_8 = STATIC_CONS(Qsequence,Qnil);
    list_constant_16 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_8);
    set_property_value_function(get_symbol_properties_function(Qfocal_classes),
	    Qtype_specification_simple_expansion,list_constant_16);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_17,
	    FIX((SI_Long)1L));
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_18);
    define_type_specification_explicit_complex_type(Qfocal_classes,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,Qfocal_classes);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_2 = STATIC_STRING("~NT ");
    string_constant_3 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    focal_classes_evaluation_setter_1 = 
	    STATIC_FUNCTION(focal_classes_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfocal_classes,
	    focal_classes_evaluation_setter_1);
    focal_classes_evaluation_getter_1 = 
	    STATIC_FUNCTION(focal_classes_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfocal_classes,
	    focal_classes_evaluation_getter_1);
    Qput_rule_chaining_links = STATIC_SYMBOL("PUT-RULE-CHAINING-LINKS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_chaining_links,
	    STATIC_FUNCTION(put_rule_chaining_links,NIL,FALSE,3,3));
    mutate_global_property(Qrule_chaining_links,
	    SYMBOL_FUNCTION(Qput_rule_chaining_links),Qslot_putter);
    Qput_rule_byte_code_body = STATIC_SYMBOL("PUT-RULE-BYTE-CODE-BODY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_rule_byte_code_body,
	    STATIC_FUNCTION(put_rule_byte_code_body,NIL,FALSE,3,3));
    mutate_global_property(Qrule_byte_code_body,
	    SYMBOL_FUNCTION(Qput_rule_byte_code_body),Qslot_putter);
    string_constant_85 = 
	    STATIC_STRING("1v1n83Ery1n83-ady1m9k83vy83-aey1mln1n83Ery1r83-ady1m9k83vy83-aey1m9k83vy83-duy1m9k83vy83-dvy1olnpr1n83Ery1t83-ady1m9k83vy83-aey1");
    string_constant_86 = 
	    STATIC_STRING("m9k83vy83-duy1m9k83vy83-dvy1m9k83vy83rLy1plnprt1n83-ady1o1m9k83-acy1m9k83-wZy1m9k83fIy1m9k83-Lsy83-ady1n83-ady1p1m9k9l1m9k83-acy");
    string_constant_87 = 
	    STATIC_STRING("1m9k83-wZy1m9k83fIy1m9k83-Lsy83-h0y1n83-aey1o1m9k83-acy1m9k83-wZy1m9k83hRy1m9k83-Lsy83-aey1n83-aey1p1m9k9l1m9k83-acy1m9k83-wZy1m");
    string_constant_88 = 
	    STATIC_STRING("9k83hRy1m9k83-Lsy83-h1y1n83-duy1o1m9k83-6Ty1m9k83-Lky1m9k831Dy1m9k83-nvy83-duy1n83-duy1p1m9k83-6Ty1m9k9l1m9k83-Lky1m9k831Dy1m9k8");
    string_constant_89 = 
	    STATIC_STRING("3-nvy83-dwy1n83-dvy1o1m9k83-6Ty1m9k83-Lky1m9k83hRy1m9k83-Lsy83-dvy1n83-dvy1p1m9k83-6Ty1m9k9l1m9k83-Lky1m9k83hRy1m9k83-Lsy83-dxy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_85,
	    string_constant_86,string_constant_87,string_constant_88,
	    string_constant_89)));
    Qrule_frame_flags = STATIC_SYMBOL("RULE-FRAME-FLAGS",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_19 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qrule_frame_flags),
	    Qtype_specification_simple_expansion,list_constant_19);
    Qbackward_chain = STATIC_SYMBOL("BACKWARD-CHAIN",AB_package);
    list_constant_20 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_21 = STATIC_CONS(Qbackward_chain,list_constant_20);
    Qforward_chain = STATIC_SYMBOL("FORWARD-CHAIN",AB_package);
    list_constant_22 = STATIC_CONS(Qforward_chain,list_constant_20);
    Qdata_seeking = STATIC_SYMBOL("DATA-SEEKING",AB_package);
    list_constant_23 = STATIC_CONS(Qdata_seeking,list_constant_20);
    Qcause_forward = STATIC_SYMBOL("CAUSE-FORWARD",AB_package);
    list_constant_24 = STATIC_CONS(Qcause_forward,list_constant_20);
    Qexplanation_data = STATIC_SYMBOL("EXPLANATION-DATA",AB_package);
    list_constant_25 = STATIC_CONS(Qexplanation_data,list_constant_20);
    list_constant_26 = STATIC_LIST((SI_Long)5L,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_24,
	    list_constant_25);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qand,Qbackward_chain,
	    Qforward_chain);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_26,list_constant_27);
    define_type_specification_explicit_complex_type(Qrule_frame_flags,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qrule_frame_flags);
    Qinvocable_via_backward_chaining = 
	    STATIC_SYMBOL("INVOCABLE-VIA-BACKWARD-CHAINING",AB_package);
    Qnot_invocable_via_backward_chaining = 
	    STATIC_SYMBOL("NOT-INVOCABLE-VIA-BACKWARD-CHAINING",AB_package);
    Qinvocable_via_forward_chaining = 
	    STATIC_SYMBOL("INVOCABLE-VIA-FORWARD-CHAINING",AB_package);
    Qnot_invocable_via_forward_chaining = 
	    STATIC_SYMBOL("NOT-INVOCABLE-VIA-FORWARD-CHAINING",AB_package);
    Qmay_cause_data_seeking = STATIC_SYMBOL("MAY-CAUSE-DATA-SEEKING",
	    AB_package);
    Qmay_not_cause_data_seeking = 
	    STATIC_SYMBOL("MAY-NOT-CAUSE-DATA-SEEKING",AB_package);
    Qmay_cause_forward_chaining = 
	    STATIC_SYMBOL("MAY-CAUSE-FORWARD-CHAINING",AB_package);
    Qmay_not_cause_forward_chaining = 
	    STATIC_SYMBOL("MAY-NOT-CAUSE-FORWARD-CHAINING",AB_package);
    Qcache_data_for_explanation_flag = 
	    STATIC_SYMBOL("CACHE-DATA-FOR-EXPLANATION-FLAG",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcache_data_for_explanation_flag,
	    Cache_data_for_explanation_flag);
    rule_frame_flags_evaluation_setter_1 = 
	    STATIC_FUNCTION(rule_frame_flags_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qrule_frame_flags,
	    rule_frame_flags_evaluation_setter_1);
    rule_frame_flags_evaluation_getter_1 = 
	    STATIC_FUNCTION(rule_frame_flags_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qrule_frame_flags,
	    rule_frame_flags_evaluation_getter_1);
    Qcompile_rule_frame_flags_for_slot = 
	    STATIC_SYMBOL("COMPILE-RULE-FRAME-FLAGS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_rule_frame_flags_for_slot,
	    STATIC_FUNCTION(compile_rule_frame_flags_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qrule_frame_flags,
	    SYMBOL_FUNCTION(Qcompile_rule_frame_flags_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qrule_frame_flags,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_4 = STATIC_STRING("invocable via backward chaining, ");
    string_constant_5 = STATIC_STRING("not invocable via backward chaining, ");
    string_constant_6 = STATIC_STRING("invocable via forward chaining, ");
    string_constant_7 = STATIC_STRING("not invocable via forward chaining, ");
    string_constant_8 = STATIC_STRING("may cause data seeking, ");
    string_constant_9 = STATIC_STRING("may not cause data seeking, ");
    string_constant_10 = STATIC_STRING("may cause forward chaining");
    string_constant_11 = STATIC_STRING("may not cause forward chaining");
    string_constant_12 = STATIC_STRING(", cache data for explanation");
    string_constant_13 = STATIC_STRING(", do not cache data for explanation");
    Qwrite_rule_frame_flags_from_slot = 
	    STATIC_SYMBOL("WRITE-RULE-FRAME-FLAGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_rule_frame_flags_from_slot,
	    STATIC_FUNCTION(write_rule_frame_flags_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qrule_frame_flags,
	    SYMBOL_FUNCTION(Qwrite_rule_frame_flags_from_slot),
	    Qslot_value_writer);
}
