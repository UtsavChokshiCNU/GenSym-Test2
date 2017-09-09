/* sets.c
 * Input file:  sets.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "sets.h"


DEFINE_VARIABLE_WITH_SYMBOL(Stack_expiration, Qstack_expiration);

DEFINE_VARIABLE_WITH_SYMBOL(Multiplier_for_turning_off_data_collection, Qmultiplier_for_turning_off_data_collection);

DEFINE_VARIABLE_WITH_SYMBOL(Message_completion_interval, Qmessage_completion_interval);

DEFINE_VARIABLE_WITH_SYMBOL(Inference_engine_parameters, Qinference_engine_parameters);

/* PUT-SET-OF-ALL-COMPUTATION-STYLES-WHERE-SLOT-IS-ABSENT */
Object put_set_of_all_computation_styles_where_slot_is_absent(inference_engine_parameters,
	    value)
    Object inference_engine_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(142,0);
    PUSH_SPECIAL_WITH_SYMBOL(Inference_engine_parameters,Qinference_engine_parameters,inference_engine_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* PUT-USE-OLD-RULE-COMPILER?-WHERE-SLOT-IS-ABSENT */
Object put_use_old_rule_compiler_qm_where_slot_is_absent(inference_engine_parameters,
	    value)
    Object inference_engine_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(142,1);
    PUSH_SPECIAL_WITH_SYMBOL(Inference_engine_parameters,Qinference_engine_parameters,inference_engine_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qtruth_threshold;    /* truth-threshold */

/* PUT-TRUTH-THRESHHOLD-WHERE-SLOT-IS-ABSENT */
Object put_truth_threshhold_where_slot_is_absent(inference_engine_parameters,
	    value)
    Object inference_engine_parameters, value;
{
    Object svref_arg_1, svref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(142,2);
    PUSH_SPECIAL_WITH_SYMBOL(Inference_engine_parameters,Qinference_engine_parameters,inference_engine_parameters,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_block_1(Inference_engine_parameters,Qtruth_threshold);
      svref_arg_1 = Inference_engine_parameters;
      SVREF(svref_arg_1,FIX((SI_Long)26L)) = value;
      svref_arg_1 = Inference_engine_parameters;
      svref_new_value = FIXNUM_NEGATE(value);
      ISVREF(svref_arg_1,(SI_Long)27L) = svref_new_value;
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* PUT-TRUTH-THRESHOLD */
Object put_truth_threshold(inference_engine_parameters_instance,value,
	    gensymed_symbol)
    Object inference_engine_parameters_instance, value, gensymed_symbol;
{
    Object svref_new_value;

    x_note_fn_call(142,3);
    value = FIXNUM_ABS(value);
    svref_new_value = FIXNUM_NEGATE(value);
    ISVREF(inference_engine_parameters_instance,(SI_Long)27L) = 
	    svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(inference_engine_parameters_instance,
		Qtruth_threshold);
    return VALUES_1(SVREF(inference_engine_parameters_instance,
	    FIX((SI_Long)26L)) = value);
}

/* PUT-DEFAULT-DEBUGGING-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT */
Object put_default_debugging_message_level_where_slot_is_absent(inference_engine_parameters,
	    value)
    Object inference_engine_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(142,4);
    PUSH_SPECIAL_WITH_SYMBOL(Inference_engine_parameters,Qinference_engine_parameters,inference_engine_parameters,
	    0);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qtimeout_for_wakeups;  /* timeout-for-wakeups */

/* PUT-TIMEOUT-FOR-WAKE-UPS-WHERE-SLOT-IS-ABSENT */
Object put_timeout_for_wake_ups_where_slot_is_absent(inference_engine_parameters,
	    value)
    Object inference_engine_parameters, value;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(142,5);
    PUSH_SPECIAL_WITH_SYMBOL(Inference_engine_parameters,Qinference_engine_parameters,inference_engine_parameters,
	    0);
      change_slot_value(3,Inference_engine_parameters,Qtimeout_for_wakeups,
	      value);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Recursive_depth, Qrecursive_depth);

/* TRUTH-THRESHOLD-PARAMETER-FUNCTION */
Object truth_threshold_parameter_function()
{
    x_note_fn_call(142,6);
    return VALUES_1(ISVREF(Inference_engine_parameters,(SI_Long)26L));
}

static Object array_constant;      /* # */

static Object Qseconds;            /* seconds */

/* WRITE-INTERVAL-FOR-RETRY-FROM-SLOT */
Object write_interval_for_retry_from_slot(interval_qm,gensymed_symbol)
    Object interval_qm, gensymed_symbol;
{
    x_note_fn_call(142,7);
    if ( !TRUEP(interval_qm))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)12L));
    else
	return print_constant(2,interval_qm,Qseconds);
}

/* COMPILE-INTERVAL-FOR-RETRY-FOR-SLOT */
Object compile_interval_for_retry_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(142,8);
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
    if (CONSP(parse_result)) {
	if (EQ(CAR(parse_result),Qdo))
	    return VALUES_1(Nil);
	else {
	    temp = CAR(parse_result);
	    if (NUMBERP(temp))
		return VALUES_1(CAR(parse_result));
	    else
		return VALUES_1(Nil);
	}
    }
    else if (NUMBERP(parse_result))
	return VALUES_1(parse_result);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_environment, Qcurrent_environment);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_top_of_stack, Qcached_top_of_stack);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_stack_program_counter, Qcached_stack_program_counter);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_fixnum_start_time, Qcached_fixnum_start_time);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_byte_code_body, Qcached_byte_code_body);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_fixnum_time_limit_qm, Qcached_fixnum_time_limit_qm);

Object The_type_description_of_rule_instance = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_rule_instances, Qchain_of_available_rule_instances);

DEFINE_VARIABLE_WITH_SYMBOL(Rule_instance_count, Qrule_instance_count);

Object Chain_of_available_rule_instances_vector = UNBOUND;

/* RULE-INSTANCE-STRUCTURE-MEMORY-USAGE */
Object rule_instance_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(142,9);
    temp = Rule_instance_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)29L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-RULE-INSTANCE-COUNT */
Object outstanding_rule_instance_count()
{
    Object def_structure_rule_instance_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(142,10);
    gensymed_symbol = IFIX(Rule_instance_count);
    def_structure_rule_instance_variable = Chain_of_available_rule_instances;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_rule_instance_variable))
	goto end_loop;
    def_structure_rule_instance_variable = 
	    ISVREF(def_structure_rule_instance_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-RULE-INSTANCE-1 */
Object reclaim_rule_instance_1(rule_instance)
    Object rule_instance;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(142,11);
    inline_note_reclaim_cons(rule_instance,Nil);
    structure_being_reclaimed = rule_instance;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
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
      SVREF(rule_instance,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(rule_instance,(SI_Long)11L));
      SVREF(rule_instance,FIX((SI_Long)11L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_rule_instances_vector,
	    IFIX(Current_thread_index));
    SVREF(rule_instance,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_rule_instances_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = rule_instance;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RULE-INSTANCE */
Object reclaim_structure_for_rule_instance(rule_instance)
    Object rule_instance;
{
    x_note_fn_call(142,12);
    return reclaim_rule_instance_1(rule_instance);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

/* MAKE-PERMANENT-RULE-INSTANCE-STRUCTURE-INTERNAL */
Object make_permanent_rule_instance_structure_internal()
{
    Object def_structure_rule_instance_variable;
    Object defstruct_g2_rule_instance_variable, the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(142,13);
    def_structure_rule_instance_variable = Nil;
    atomic_incff_symval(Qrule_instance_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_rule_instance_variable = Nil;
	gensymed_symbol_1 = (SI_Long)29L;
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
	defstruct_g2_rule_instance_variable = the_array;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rule_instance_g2_struct;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_rule_instance_variable,FIX((SI_Long)7L)) = Nil;
	def_structure_rule_instance_variable = 
		defstruct_g2_rule_instance_variable;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)6L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_rule_instances_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_rule_instances_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_rule_instance_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_rule_instance_variable);
}

/* MAKE-RULE-INSTANCE-1 */
Object make_rule_instance_1()
{
    Object def_structure_rule_instance_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(142,14);
    def_structure_rule_instance_variable = 
	    ISVREF(Chain_of_available_rule_instances_vector,
	    IFIX(Current_thread_index));
    if (def_structure_rule_instance_variable) {
	svref_arg_1 = Chain_of_available_rule_instances_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_rule_instance_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_rule_instance_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rule_instance_g2_struct;
    }
    else
	def_structure_rule_instance_variable = 
		make_permanent_rule_instance_structure_internal();
    inline_note_allocate_cons(def_structure_rule_instance_variable,Nil);
    SVREF(def_structure_rule_instance_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_rule_instance_variable,FIX((SI_Long)11L)) = Nil;
    return VALUES_1(def_structure_rule_instance_variable);
}

/* RECLAIM-EVALUATION-VARIABLES-LIST */
Object reclaim_evaluation_variables_list(variables)
    Object variables;
{
    Object var, ab_loop_list_;

    x_note_fn_call(142,15);
    var = Nil;
    ab_loop_list_ = variables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(CDR(var));
    reclaim_eval_cons_1(var);
    goto next_loop;
  end_loop:;
    return reclaim_eval_list_1(variables);
}

/* COPY-VARIABLES-LIST */
Object copy_variables_list(variables)
    Object variables;
{
    Object var, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(142,16);
    var = Nil;
    ab_loop_list_ = variables;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CAR(var);
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

DEFINE_VARIABLE_WITH_SYMBOL(Current_ri_completion_notification_collection_qm, Qcurrent_ri_completion_notification_collection_qm);

/* READ-EVALUATION-VALUE-FOR-KB */
Object read_evaluation_value_for_kb()
{
    Object temp;

    x_note_fn_call(142,17);
    temp = read_element_for_kb(Nil);
    return VALUES_1(temp);
}

static Object Qtruth_value;        /* truth-value */

/* READ-TRUTH-VALUE-FOR-KB */
Object read_truth_value_for_kb()
{
    Object value, temp;

    x_note_fn_call(142,18);
    value = read_element_for_kb(Nil);
    if ( !FIXNUMP(value))
	temp = abort_on_bad_kb(0);
    else if (FIXNUM_EQ(value,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value,Qtruth_value);
    return VALUES_1(temp);
}

/* READ-PAST-TRUTH-VALUE-FOR-KB */
Object read_past_truth_value_for_kb(print_qm)
    Object print_qm;
{
    x_note_fn_call(142,19);
    read_past_element_for_kb(print_qm);
    return VALUES_1(Nil);
}

/* WRITE-EVALUATION-VALUE-FOR-KB */
Object write_evaluation_value_for_kb(evaluation_value)
    Object evaluation_value;
{
    x_note_fn_call(142,20);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qtruth_value))
	write_truth_value_for_kb(evaluation_value);
    else
	write_element_for_kb(evaluation_value);
    return VALUES_1(Nil);
}

/* WRITE-TRUTH-VALUE-FOR-KB */
Object write_truth_value_for_kb(evaluation_truth_value)
    Object evaluation_truth_value;
{
    x_note_fn_call(142,21);
    write_char_for_kb(CHR('U'));
    write_element_for_kb(M_CAR(evaluation_truth_value));
    return VALUES_1(Nil);
}

static Object Qlong;               /* long */

static Object Qtext;               /* text */

static Object Qboolean;            /* boolean */

static Object Qdatum;              /* datum */

static Object Qiteration_state;    /* iteration-state */

/* EVALUATION-VALUE-OF-TYPE-P */
Object evaluation_value_of_type_p(evaluation_value,type)
    Object evaluation_value, type;
{
    Object temp, value, gensymed_symbol, possible_type_name, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, entry_hash;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(142,22);
    if (EQ(type,Qinteger))
	temp = FIXNUMP(evaluation_value) ? T : Nil;
    else if (EQ(type,Qlong))
	temp = INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    else if (EQ(type,Qfloat))
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != 
		(SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    else if (EQ(type,Qnumber)) {
	temp = FIXNUMP(evaluation_value) ? T : Nil;
	if (temp);
	else
	    temp = INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != 
		    (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		    (SI_Long)1L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = INLINE_LONG_VECTOR_P(evaluation_value) != (SI_Long)0L ? 
		    (IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) == 
		    (SI_Long)1L ? T : Nil) : Qnil;
    }
    else if (EQ(type,Qsymbol))
	temp = evaluation_value ? (SYMBOLP(evaluation_value) ? T : Nil) : Qnil;
    else if (EQ(type,Qtext))
	temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(evaluation_value) != 
		(SI_Long)0L ? T : Nil;
    else if (EQ(type,Qboolean)) {
	if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qtruth_value)) {
	    value = M_CAR(evaluation_value);
	    temp = EQ(value,Truth) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(value,Falsity) ? T : Nil;
	}
	else
	    temp = Nil;
    }
    else if (EQ(type,Qtruth_value))
	temp = CONSP(evaluation_value) ? (EQ(M_CDR(evaluation_value),
		Qtruth_value) ? T : Nil) : Qnil;
    else if (EQ(type,Qdatum)) {
	gensymed_symbol = evaluation_value;
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
		temp = memq_function(gensymed_symbol,
			Defined_evaluation_datum_types);
	}
	else
	    temp = Nil;
    }
    else {
	temp = iteration_state_type_specification_p(type) ? 
		(CONSP(evaluation_value) ? (EQ(M_CDR(evaluation_value),
		Qiteration_state) ? T : Nil) : Qnil) : Qnil;
	if (temp);
	else if (SYMBOLP(type) && (EQ(type,Qnumber) || EQ(type,Qinteger) 
		|| EQ(type,Qfloat) || EQ(type,Qlong) || 
		lookup_global_or_kb_specific_property_value(type,
		Numeric_data_type_gkbprop))) {
	    temp = FIXNUMP(evaluation_value) ? T : Nil;
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(evaluation_value) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(evaluation_value) != 
			(SI_Long)0L ? 
			(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(evaluation_value)) 
			== (SI_Long)1L ? T : Nil) : Qnil;
	}
	else
	    temp = Nil;
	if (temp);
	else {
	    if (CONSP(type)) {
		possible_type_name = M_CAR(type);
		if (SYMBOLP(possible_type_name)) {
		    skip_list = CDR(Defined_evaluation_value_types);
		    key_value = possible_type_name;
		    key_hash_value = SXHASH_SYMBOL_1(possible_type_name) & 
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
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_2;
		  end_loop_1:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		    temp_2 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp = (temp_2 ? CONSP(evaluation_value) : TRUEP(Nil)) ? 
		    (EQ(M_CAR(type),M_CDR(evaluation_value)) ? T : Nil) : Nil;
	}
    }
    return VALUES_1(temp);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* WRITE-EVALUATION-VALUE-TO-TEXT-STRING */
Object write_evaluation_value_to_text_string(evaluation_value)
    Object evaluation_value;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(142,23);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      write_evaluation_value(1,evaluation_value);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* WRITE-EVALUATION-OBSOLETE-DATUM */
Object write_evaluation_obsolete_datum(obsolete_datum)
    Object obsolete_datum;
{
    Object temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(142,24);
    write_evaluation_value(1,M_CAR(obsolete_datum));
    if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = (SI_Long)42L;
	twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = (SI_Long)42L;
	schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		CHAR_CODE(FIX(thing)) : FIX(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    return VALUES_1(Nil);
}

static Object Qab_or;              /* or */

/* MAKE-TYPE-SPECIFICATION-UNION */
Object make_type_specification_union(type1,type2)
    Object type1, type2;
{
    Object temp, collected_types, union_type, ab_loop_list_;

    x_note_fn_call(142,25);
    if (type_specification_subtype_p(type1,type2))
	temp = type2;
    else if (type_specification_subtype_p(type2,type1))
	temp = type1;
    else {
	collected_types = Nil;
	if (union_type_specification_p(type1)) {
	    union_type = Nil;
	    ab_loop_list_ = CDR(type1);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    union_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    collected_types = possibly_add_type_to_union_list(union_type,
		    collected_types);
	    goto next_loop;
	  end_loop:;
	}
	else
	    collected_types = possibly_add_type_to_union_list(type1,
		    collected_types);
	if (union_type_specification_p(type2)) {
	    union_type = Nil;
	    ab_loop_list_ = CDR(type2);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    union_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    collected_types = possibly_add_type_to_union_list(union_type,
		    collected_types);
	    goto next_loop_1;
	  end_loop_1:;
	}
	else
	    collected_types = possibly_add_type_to_union_list(type2,
		    collected_types);
	temp = phrase_cons(Qab_or,collected_types);
    }
    return VALUES_1(temp);
}

/* POSSIBLY-ADD-TYPE-TO-UNION-LIST */
Object possibly_add_type_to_union_list(type_to_add,union_list)
    Object type_to_add, union_list;
{
    Object type_cons, type, temp;

    x_note_fn_call(142,26);
    type_cons = union_list;
    type = Nil;
  next_loop:
    if ( !TRUEP(type_cons))
	goto end_loop;
    type = M_CAR(type_cons);
    if (type_specification_subtype_p(type_to_add,type)) {
	temp = union_list;
	goto end_1;
    }
    else if (type_specification_subtype_p(type,type_to_add)) {
	M_CAR(type_cons) = type_to_add;
	temp = union_list;
	goto end_1;
    }
    type_cons = M_CDR(type_cons);
    goto next_loop;
  end_loop:
    temp = nconc2(union_list,phrase_cons(type_to_add,Nil));
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

/* MAKE-TYPE-SPECIFICATION-INTERSECTION */
Object make_type_specification_intersection(type1,type2)
    Object type1, type2;
{
    Object unknown_allowed_qm, no_item_allowed_qm;
    Object no_item_implies_unknown_allowed_qm, primary_type1, primary_type2;
    Object temp;

    x_note_fn_call(142,27);
    unknown_allowed_qm = type_specification_subtype_p(list_constant,type1) 
	    ? type_specification_subtype_p(list_constant,type2) : Qnil;
    no_item_allowed_qm = type_specification_subtype_p(list_constant_1,
	    type1) ? type_specification_subtype_p(list_constant_1,type2) : 
	    Qnil;
    no_item_implies_unknown_allowed_qm = 
	    type_specification_subtype_p(list_constant_2,type1) ? 
	    type_specification_subtype_p(list_constant_2,type2) : Qnil;
    primary_type1 = primary_type_of_type_specification(type1);
    primary_type2 = primary_type_of_type_specification(type2);
    if (type_specification_subtype_p(primary_type1,primary_type2))
	temp = primary_type1;
    else if (type_specification_subtype_p(primary_type2,primary_type1))
	temp = primary_type2;
    else
	temp = phrase_list_3(Qand,primary_type1,primary_type2);
    temp = 
	    maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(temp,
	    unknown_allowed_qm),no_item_allowed_qm),
	    no_item_implies_unknown_allowed_qm);
    return VALUES_1(temp);
}

/* MAKE-TYPE-SPECIFICATION-NEGATION */
Object make_type_specification_negation(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(142,28);
    temp = phrase_list_2(Qnot,type_specification);
    return VALUES_1(temp);
}

/* MAKE-TYPE-SPECIFICATION-FILTERED */
Object make_type_specification_filtered(function_name_symbol)
    Object function_name_symbol;
{
    Object temp;

    x_note_fn_call(142,29);
    temp = phrase_list_2(Qsatisfies,function_name_symbol);
    return VALUES_1(temp);
}

static Object Qquantity;           /* quantity */

static Object Qvalue;              /* value */

static Object Qitem_or_value;      /* item-or-value */

static Object Qitem_or_datum;      /* item-or-datum */

static Object list_constant_3;     /* # */

static Object Qstruct;             /* struct */

static Object Qab_structure;       /* structure */

static Object list_constant_4;     /* # */

/* TYPE-SPECIFICATION-FOR-USER-TYPE */
Object type_specification_for_user_type(symbol)
    Object symbol;
{
    Object temp;

    x_note_fn_call(142,30);
    if (EQ(symbol,Qquantity))
	temp = Qnumber;
    else if (EQ(symbol,Qvalue))
	temp = Qdatum;
    else if (EQ(symbol,Qitem_or_value))
	temp = Qitem_or_datum;
    else if (EQ(symbol,Qsequence))
	temp = list_constant_3;
    else if (EQ(symbol,Qstruct) || EQ(symbol,Qab_structure))
	temp = list_constant_4;
    else
	temp =  !EQ(symbol,Qdatum) && 
		valid_datum_type_specification_p(symbol) ? symbol : Nil;
    return VALUES_1(temp);
}

/* USER-TYPE-FOR-TYPE-SPECIFICATION */
Object user_type_for_type_specification(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(142,31);
    if (symbolic_type_specification_p(type_specification)) {
	if (EQ(type_specification,Qnumber))
	    temp = Qquantity;
	else if (EQ(type_specification,Qfloat))
	    temp = Qfloat;
	else if (EQ(type_specification,Qinteger))
	    temp = Qinteger;
	else if (EQ(type_specification,Qlong))
	    temp = Qlong;
	else if (EQ(type_specification,Qitem_or_datum))
	    temp = Qitem_or_value;
	else if (EQ(type_specification,Qdatum))
	    temp = Qvalue;
	else if (EQ(type_specification,Qsymbol))
	    temp = Qsymbol;
	else if (EQ(type_specification,Qtext))
	    temp = Qtext;
	else if (EQ(type_specification,Qtruth_value))
	    temp = Qtruth_value;
	else
	    temp = Qnil;
    }
    else if (class_type_specification_p(type_specification))
	temp = M_CAR(M_CDR(type_specification));
    else if (aggregate_value_type_specification_p(type_specification))
	temp = M_CAR(type_specification);
    else
	temp = Qitem_or_value;
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-FOR-USER-OR-DATUM-TYPE */
Object type_specification_for_user_or_datum_type(symbol_or_type_spec)
    Object symbol_or_type_spec;
{
    Object temp;

    x_note_fn_call(142,32);
    if (SYMBOLP(symbol_or_type_spec)) {
	if (EQ(symbol_or_type_spec,Qquantity))
	    temp = Qnumber;
	else if (EQ(symbol_or_type_spec,Qvalue))
	    temp = Qdatum;
	else if (EQ(symbol_or_type_spec,Qitem_or_value))
	    temp = Qitem_or_datum;
	else if (EQ(symbol_or_type_spec,Qitem_or_datum))
	    temp = Qitem_or_datum;
	else if (EQ(symbol_or_type_spec,Qsequence))
	    temp = list_constant_3;
	else if (EQ(symbol_or_type_spec,Qstruct) || EQ(symbol_or_type_spec,
		Qab_structure))
	    temp = list_constant_4;
	else
	    temp = valid_datum_type_specification_p(symbol_or_type_spec) ? 
		    symbol_or_type_spec : Nil;
    }
    else if (valid_type_specification_p(symbol_or_type_spec))
	temp = symbol_or_type_spec;
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* PRINT-USER-OR-DATUM-TYPE */
Object print_user_or_datum_type(symbol_or_type_spec)
    Object symbol_or_type_spec;
{
    Object type_spec_qm;

    x_note_fn_call(142,33);
    type_spec_qm = 
	    type_specification_for_user_or_datum_type(symbol_or_type_spec);
    if (type_spec_qm)
	write_type_specification(type_spec_qm);
    else if (SYMBOLP(symbol_or_type_spec))
	twrite_symbol(1,symbol_or_type_spec);
    else
	twrite(symbol_or_type_spec);
    return VALUES_1(Nil);
}

/* MAYBE-ADD-UNKNOWN */
Object maybe_add_unknown(type,add_unknown_datum_qm)
    Object type, add_unknown_datum_qm;
{
    Object temp;

    x_note_fn_call(142,34);
    temp = add_unknown_datum_qm ? make_type_specification_union(type,
	    list_constant) : type;
    return VALUES_1(temp);
}

/* MAYBE-ADD-NO-ITEM */
Object maybe_add_no_item(type,add_no_item_qm)
    Object type, add_no_item_qm;
{
    Object temp;

    x_note_fn_call(142,35);
    temp = add_no_item_qm ? make_type_specification_union(type,
	    list_constant_1) : type;
    return VALUES_1(temp);
}

/* MAYBE-ADD-NO-ITEM-IMPLIES-UNKNOWN */
Object maybe_add_no_item_implies_unknown(type,add_no_item_implies_unknown_qm)
    Object type, add_no_item_implies_unknown_qm;
{
    Object temp;

    x_note_fn_call(142,36);
    temp = add_no_item_implies_unknown_qm ? 
	    make_type_specification_union(type,list_constant_2) : type;
    return VALUES_1(temp);
}

/* DIFFERENCE-TYPE-SPECIFICATION-P */
Object difference_type_specification_p(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(142,37);
    temp = CONSP(type_specification) && EQ(M_CAR(type_specification),Qand) 
	    && valid_type_specification_list_p(M_CDR(type_specification)) 
	    && IFIX(length(type_specification)) == (SI_Long)3L && 
	    negation_type_specification_p(M_CAR(M_CDR(M_CDR(type_specification)))) 
	    ? 
	    type_specification_subtype_p(M_CAR(M_CDR(M_CAR(M_CDR(M_CDR(type_specification))))),
	    M_CAR(M_CDR(type_specification))) : Qnil;
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-UNION-MINUS-TYPE */
Object type_specification_union_minus_type(union_1,type_to_remove)
    Object union_1, type_to_remove;
{
    Object temp, type, ab_loop_list_, result_types, ab_loopvar_, ab_loopvar__1;

    x_note_fn_call(142,38);
    if (IFIX(length(union_1)) == (SI_Long)3L)
	temp = type_specification_subtype_p(THIRD(union_1),type_to_remove) 
		? SECOND(union_1) : 
		type_specification_subtype_p(SECOND(union_1),
		type_to_remove) ? THIRD(union_1) : union_1;
    else {
	type = Nil;
	ab_loop_list_ = CDR(union_1);
	result_types = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(type_specification_subtype_p(type,type_to_remove))) {
	    ab_loopvar__1 = phrase_cons(type,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		result_types = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	goto next_loop;
      end_loop:
	if ( !TRUEP(result_types)) {
	    temp = Nil;
	    goto end_1;
	}
	else if ( !TRUEP(CDR(result_types))) {
	    temp = CAR(result_types);
	    goto end_1;
	}
	else {
	    temp = phrase_cons(Qab_or,result_types);
	    goto end_1;
	}
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-MINUS-TYPE */
Object type_specification_minus_type(type,type_to_remove)
    Object type, type_to_remove;
{
    Object temp;

    x_note_fn_call(142,39);
    temp = union_type_specification_p(type) && 
	    type_specification_subtype_p(type_to_remove,type) ? 
	    type_specification_union_minus_type(type,type_to_remove) : type;
    return VALUES_1(temp);
}

/* PRIMARY-TYPE-OF-TYPE-SPECIFICATION */
Object primary_type_of_type_specification(type_specification)
    Object type_specification;
{
    Object temp;

    x_note_fn_call(142,40);
    temp = 
	    type_specification_minus_type(type_specification_minus_type(type_specification_minus_type(type_specification,
	    list_constant_2),list_constant_1),list_constant);
    return VALUES_1(temp);
}

/* ADD-SECONDARY-TYPE-SPECIFICATIONS */
Object add_secondary_type_specifications(to_type,from_type)
    Object to_type, from_type;
{
    Object temp;

    x_note_fn_call(142,41);
    temp = 
	    maybe_add_no_item_implies_unknown(maybe_add_no_item(maybe_add_unknown(to_type,
	    type_specification_subtype_p(list_constant,from_type)),
	    type_specification_subtype_p(list_constant_1,from_type)),
	    type_specification_subtype_p(list_constant_2,from_type));
    return VALUES_1(temp);
}

static Object list_constant_5;     /* # */

/* SEQUENCE-TYPE-SPECIFICATION-SUBTYPE-P */
Object sequence_type_specification_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object superior_low_bound_qm, superior_high_bound_qm, low_bound_qm, temp_1;
    Object high_bound_qm;
    char temp;

    x_note_fn_call(142,42);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant_5;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant_5;
	if (type_specification_subtype_p(CADR(type),CADR(superior_type))) {
	    superior_low_bound_qm = CADDR(superior_type);
	    superior_high_bound_qm = CADDDR(superior_type);
	    temp =  !TRUEP(superior_low_bound_qm);
	    if (temp);
	    else {
		low_bound_qm = CADDR(type);
		temp =  !TRUEP(low_bound_qm) ? IFIX(superior_low_bound_qm) 
			== (SI_Long)0L : FIXNUM_GE(low_bound_qm,
			superior_low_bound_qm);
	    }
	    if (temp) {
		temp_1 =  !TRUEP(superior_high_bound_qm) ? T : Nil;
		if (temp_1);
		else {
		    high_bound_qm = CADDDR(type);
		    temp_1 =  !TRUEP(high_bound_qm) ? 
			    (FIXNUM_EQ(superior_high_bound_qm,
			    Most_positive_fixnum) ? T : Nil) : 
			    FIXNUM_LE(high_bound_qm,
			    superior_high_bound_qm) ? T : Nil;
		}
	    }
	    else
		temp_1 = Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

/* SEQUENCE-TYPE-SPECIFICATIONS-COULD-INTERSECT-P */
Object sequence_type_specifications_could_intersect_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p, superior_low_bound;
    Object superior_high_bound, low_bound, high_bound, temp;

    x_note_fn_call(142,43);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant_5;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant_5;
	if (type_specifications_could_intersect_p(CADR(type),
		CADR(superior_type))) {
	    superior_low_bound = CADDR(superior_type);
	    if (superior_low_bound);
	    else
		superior_low_bound = FIX((SI_Long)0L);
	    superior_high_bound = CADDDR(superior_type);
	    if (superior_high_bound);
	    else
		superior_high_bound = Most_positive_fixnum;
	    low_bound = CADDR(type);
	    if (low_bound);
	    else
		low_bound = FIX((SI_Long)0L);
	    high_bound = CADDDR(type);
	    if (high_bound);
	    else
		high_bound = Most_positive_fixnum;
	    temp = FIXNUM_LE(superior_low_bound,high_bound) ? 
		    (FIXNUM_LE(high_bound,superior_high_bound) ? T : Nil) :
		     Qnil;
	    if (temp);
	    else
		temp = FIXNUM_LE(superior_low_bound,low_bound) ? 
			(FIXNUM_LE(low_bound,superior_high_bound) ? T : 
			Nil) : Qnil;
	}
	else
	    temp = Nil;
    }
    else
	temp = T;
    return VALUES_1(temp);
}

/* SEQUENCE-TYPE-SPECIFICATION-NOT-SUBTYPE-P */
Object sequence_type_specification_not_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p, temp;
    Object superior_low_bound, superior_high_bound, low_bound, high_bound;

    x_note_fn_call(142,44);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p || superior_type_has_details_p) {
	if ( !TRUEP(type_has_details_p))
	    type = list_constant_5;
	if ( !TRUEP(superior_type_has_details_p))
	    superior_type = list_constant_5;
	temp = type_specification_not_subtype_p(CADR(type),
		CADR(superior_type));
	if (temp);
	else {
	    superior_low_bound = CADDR(superior_type);
	    if (superior_low_bound);
	    else
		superior_low_bound = FIX((SI_Long)0L);
	    superior_high_bound = CADDDR(superior_type);
	    if (superior_high_bound);
	    else
		superior_high_bound = Most_positive_fixnum;
	    low_bound = CADDR(type);
	    if (low_bound);
	    else
		low_bound = FIX((SI_Long)0L);
	    high_bound = CADDDR(type);
	    if (high_bound);
	    else
		high_bound = Most_positive_fixnum;
	    temp =  !(FIXNUM_LE(superior_low_bound,low_bound) && 
		    FIXNUM_LE(low_bound,high_bound) && 
		    FIXNUM_LE(high_bound,superior_high_bound)) ? T : Nil;
	}
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* STRUCTURE-TYPE-SPECIFICATION-SUBTYPE-P */
Object structure_type_specification_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, ok_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, temp_1, type_spec_of_slot;
    Object type_spec_of_slot_in_superior_qm, new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp;

    x_note_fn_call(142,45);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (superior_type_has_details_p) {
	if (type_has_details_p) {
	    minimum_contents_of_superior = CADDR(superior_type);
	    slot_list_of_type = M_CAR(M_CDR(type));
	    slot_list_of_superior_type = M_CAR(M_CDR(superior_type));
	    slot_type_cache = Nil;
	    ok_p = T;
	    type_specification = type;
	    slot_list = M_CAR(M_CDR(type_specification));
	    minimum_contents = CADDR(type_specification);
	    len = IFIX(length(slot_list));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = (SI_Long)1L << len;
	    tuple = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    j = (SI_Long)0L;
	    ab_loop_bind__1 = len;
	    slot_name = Nil;
	    ab_loop_list_ = slot_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if (j > ab_loop_bind__1)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    slot_name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
		ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    j = j + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    tuple = ab_loopvar_;
	    goto end_1;
	    tuple = Qnil;
	  end_1:;
	    if ( !TRUEP(minimum_contents) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		    tuple)) {
		if ( !TRUEP(minimum_contents_of_superior) || 
			slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
			tuple)) {
		    name = Nil;
		    ab_loop_list_ = tuple;
		    cache_entry_qm = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    name = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    cache_entry_qm = assq_function(name,slot_type_cache);
		    if (cache_entry_qm)
			temp = TRUEP(CDR(cache_entry_qm));
		    else {
			temp_1 = assq_function(name,slot_list_of_type);
			type_spec_of_slot = CADR(temp_1);
			temp_1 = assq_function(name,
				slot_list_of_superior_type);
			type_spec_of_slot_in_superior_qm = CADR(temp_1);
			new_cached_type_test =  
				!TRUEP(type_spec_of_slot_in_superior_qm) ? 
				T : Nil;
			if (new_cached_type_test);
			else
			    new_cached_type_test = 
				    type_specification_subtype_p(type_spec_of_slot,
				    type_spec_of_slot_in_superior_qm);
			slot_type_cache = gensym_cons_1(gensym_cons_1(name,
				new_cached_type_test),slot_type_cache);
			temp = TRUEP(new_cached_type_test);
		    }
		    if ( !temp) {
			temp = TRUEP(Nil);
			goto end_2;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp = TRUEP(T);
		    goto end_2;
		    temp = TRUEP(Qnil);
		  end_2:;
		}
		else
		    temp = TRUEP(Nil);
		if ( !temp) {
		    ok_p = Nil;
		    goto end_test_loop;
		}
	    }
	    reclaim_gensym_list_1(tuple);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	  end_test_loop:
	    temp_1 = ok_p;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

/* STRUCTURE-TYPE-SPECIFICATIONS-COULD-INTERSECT-P */
Object structure_type_specifications_could_intersect_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, augmented_type;
    Object augmented_superior_type, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, ok_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, temp_1, type_spec_of_slot;
    Object type_spec_of_slot_in_superior, new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp;

    x_note_fn_call(142,46);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p && superior_type_has_details_p) {
	minimum_contents_of_superior = CADDR(superior_type);
	augmented_type = make_augmented_structure_type_specification(type,
		superior_type);
	augmented_superior_type = 
		make_augmented_structure_type_specification(superior_type,
		type);
	slot_list_of_type = M_CAR(M_CDR(augmented_type));
	slot_list_of_superior_type = M_CAR(M_CDR(augmented_superior_type));
	slot_type_cache = Nil;
	ok_p = Nil;
	type_specification = augmented_type;
	slot_list = M_CAR(M_CDR(type_specification));
	minimum_contents = CADDR(type_specification);
	len = IFIX(length(slot_list));
	i = (SI_Long)0L;
	ab_loop_bind_ = (SI_Long)1L << len;
	tuple = Nil;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	j = (SI_Long)0L;
	ab_loop_bind__1 = len;
	slot_name = Nil;
	ab_loop_list_ = slot_list;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if (j > ab_loop_bind__1)
	    goto end_loop_1;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	slot_name = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
	    ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	j = j + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	tuple = ab_loopvar_;
	goto end_1;
	tuple = Qnil;
      end_1:;
	if ( !TRUEP(minimum_contents) || 
		slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		tuple)) {
	    if ( !TRUEP(minimum_contents_of_superior) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
		    tuple)) {
		name = Nil;
		ab_loop_list_ = tuple;
		cache_entry_qm = Nil;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		name = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		cache_entry_qm = assq_function(name,slot_type_cache);
		if (cache_entry_qm)
		    temp = TRUEP(CDR(cache_entry_qm));
		else {
		    temp_1 = assq_function(name,slot_list_of_type);
		    type_spec_of_slot = CADR(temp_1);
		    temp_1 = assq_function(name,slot_list_of_superior_type);
		    type_spec_of_slot_in_superior = CADR(temp_1);
		    new_cached_type_test = 
			    type_specifications_could_intersect_p(type_spec_of_slot,
			    type_spec_of_slot_in_superior);
		    slot_type_cache = gensym_cons_1(gensym_cons_1(name,
			    new_cached_type_test),slot_type_cache);
		    temp = TRUEP(new_cached_type_test);
		}
		if ( !temp) {
		    temp = TRUEP(Nil);
		    goto end_2;
		}
		goto next_loop_2;
	      end_loop_2:
		temp = TRUEP(T);
		goto end_2;
		temp = TRUEP(Qnil);
	      end_2:;
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		ok_p = T;
		goto end_test_loop;
	    }
	}
	reclaim_gensym_list_1(tuple);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
      end_test_loop:
	reclaim_gensym_tree_1(augmented_type);
	reclaim_gensym_tree_1(augmented_superior_type);
	temp_1 = ok_p;
    }
    else
	temp_1 = T;
    return VALUES_1(temp_1);
}

/* STRUCTURE-TYPE-SPECIFICATION-NOT-SUBTYPE-P */
Object structure_type_specification_not_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object type_has_details_p, superior_type_has_details_p;
    Object minimum_contents_of_superior, slot_list_of_type;
    Object slot_list_of_superior_type, slot_type_cache, not_subtype_p;
    Object type_specification, slot_list, minimum_contents, tuple, slot_name;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, name, cache_entry_qm, ab_loop_it_, temp;
    Object type_spec_of_slot, type_spec_of_slot_in_superior_qm;
    Object new_cached_type_test;
    SI_Long len, i, ab_loop_bind_, j, ab_loop_bind__1;
    char temp_1;

    x_note_fn_call(142,47);
    type_has_details_p = M_CDR(type);
    superior_type_has_details_p = M_CDR(superior_type);
    if (type_has_details_p) {
	if (superior_type_has_details_p) {
	    minimum_contents_of_superior = CADDR(superior_type);
	    slot_list_of_type = M_CAR(M_CDR(type));
	    slot_list_of_superior_type = M_CAR(M_CDR(superior_type));
	    slot_type_cache = Nil;
	    not_subtype_p = Nil;
	    type_specification = type;
	    slot_list = M_CAR(M_CDR(type_specification));
	    minimum_contents = CADDR(type_specification);
	    len = IFIX(length(slot_list));
	    i = (SI_Long)0L;
	    ab_loop_bind_ = (SI_Long)1L << len;
	    tuple = Nil;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    j = (SI_Long)0L;
	    ab_loop_bind__1 = len;
	    slot_name = Nil;
	    ab_loop_list_ = slot_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if (j > ab_loop_bind__1)
		goto end_loop_1;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    slot_name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ((SI_Long)0L != ((SI_Long)1L << j & i)) {
		ab_loopvar__2 = gensym_cons_1(slot_name,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    j = j + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    tuple = ab_loopvar_;
	    goto end_1;
	    tuple = Qnil;
	  end_1:;
	    if ( !TRUEP(minimum_contents) || 
		    slot_name_list_meets_minimum_structure_requirements_p(minimum_contents,
		    tuple)) {
		if ( !TRUEP(minimum_contents_of_superior) || 
			slot_name_list_meets_minimum_structure_requirements_p(minimum_contents_of_superior,
			tuple)) {
		    name = Nil;
		    ab_loop_list_ = tuple;
		    cache_entry_qm = Nil;
		    ab_loop_it_ = Nil;
		  next_loop_2:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_2;
		    name = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    cache_entry_qm = assq_function(name,slot_type_cache);
		    if (cache_entry_qm)
			ab_loop_it_ = CDR(cache_entry_qm);
		    else {
			temp = assq_function(name,slot_list_of_type);
			type_spec_of_slot = CADR(temp);
			temp = assq_function(name,slot_list_of_superior_type);
			type_spec_of_slot_in_superior_qm = CADR(temp);
			new_cached_type_test = 
				type_spec_of_slot_in_superior_qm ? 
				type_specification_not_subtype_p(type_spec_of_slot,
				type_spec_of_slot_in_superior_qm) : Qnil;
			slot_type_cache = gensym_cons_1(gensym_cons_1(name,
				new_cached_type_test),slot_type_cache);
			ab_loop_it_ = new_cached_type_test;
		    }
		    if (ab_loop_it_) {
			temp_1 = TRUEP(ab_loop_it_);
			goto end_2;
		    }
		    goto next_loop_2;
		  end_loop_2:
		    temp_1 = TRUEP(Qnil);
		  end_2:;
		    temp_1 = temp_1 ? TRUEP(T) : TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(T);
		if (temp_1) {
		    not_subtype_p = T;
		    goto end_test_loop;
		}
	    }
	    reclaim_gensym_list_1(tuple);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	  end_test_loop:
	    temp = not_subtype_p;
	}
	else
	    temp = Nil;
    }
    else if (superior_type_has_details_p)
	temp = T;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object list_constant_6;     /* # */

static Object list_constant_7;     /* # */

static Object Qevaluation_value;   /* evaluation-value */

static Object Qitem;               /* item */

static Object Qstable_subclass;    /* stable-subclass */

static Object Qstable_not_subclass;  /* stable-not-subclass */

/* TYPE-SPECIFICATION-SUBTYPE-P */
Object type_specification_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object temp, subtype, ab_loop_list_, intersection_type, ab_loop_it_;
    Object superior_class, class_1, gensymed_symbol, union_type;
    char temp_1;

    x_note_fn_call(142,48);
    if (EQUAL(type,list_constant_6) && EQUAL(superior_type,list_constant_7))
	temp = Nil;
    else {
	temp = EQUAL(type,superior_type) ? T : Nil;
	if (temp);
	else if (union_type_specification_p(type)) {
	    subtype = Nil;
	    ab_loop_list_ = CDR(type);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_subtype_p(subtype,superior_type))) {
		temp = Nil;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = T;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	else if (difference_type_specification_p(type))
	    temp = type_specification_subtype_p(M_CAR(M_CDR(type)),
		    superior_type);
	else if (intersection_type_specification_p(type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(type);
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_subtype_p(intersection_type,
		    superior_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_2:;
	}
	else if (negation_type_specification_p(type))
	    temp = negation_type_specification_p(superior_type) ? 
		    type_specification_subtype_p(SECOND(superior_type),
		    SECOND(type)) : Qnil;
	else
	    temp = Qnil;
	if (temp);
	else if (SYMBOLP(superior_type)) {
	    temp = SYMBOLP(type) ? 
		    symbolic_type_specification_subtype_p(type,
		    superior_type) : Qnil;
	    if (temp);
	    else
		temp = member_type_specification_p(type) ? 
			member_type_specification_subtype_of_symbolic_type_p(type,
			superior_type) : Qnil;
	    if (temp);
	    else if (EQ(superior_type,Qitem_or_datum)) {
		temp = class_type_specification_p(type);
		if (temp);
		else
		    temp = aggregate_value_type_specification_p(type);
	    }
	    else
		temp = Nil;
	    if (temp);
	    else
		temp = EQ(superior_type,Qdatum) ? 
			aggregate_value_type_specification_p(type) : Qnil;
	    if (temp);
	    else
		temp = EQ(superior_type,Qevaluation_value) && CONSP(type) ?
			 evaluation_value_type_specification_p(type) : Qnil;
	}
	else if (aggregate_value_type_specification_p(superior_type)) {
	    if (aggregate_value_type_specification_p(type)) {
		temp = CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
			CONSP(superior_type) && EQ(M_CAR(superior_type),
			Qab_structure) ? 
			structure_type_specification_subtype_p(type,
			superior_type) : Qnil;
		if (temp);
		else
		    temp = fast_sequence_type_specification_p(type) && 
			    fast_sequence_type_specification_p(superior_type) 
			    ? sequence_type_specification_subtype_p(type,
			    superior_type) : Qnil;
	    }
	    else
		temp = Nil;
	}
	else if (member_type_specification_p(superior_type))
	    temp = member_type_specification_p(type) ? 
		    member_type_specification_subtype_p(type,
		    superior_type) : Qnil;
	else if (class_type_specification_p(superior_type)) {
	    superior_class = M_CAR(M_CDR(superior_type));
	    if (class_type_specification_p(type)) {
		class_1 = M_CAR(M_CDR(type));
		temp = EQ(superior_class,Qitem) ? T : Nil;
		if (temp);
		else
		    temp = EQ(superior_class,class_1) ? T : Nil;
		if (temp);
		else {
		    if (lookup_global_or_kb_specific_property_value(superior_class,
			    Class_description_gkbprop)) {
			temp = 
				lookup_global_or_kb_specific_property_value(superior_class,
				Class_definition_gkbprop);
			temp_1 = CONSP(temp);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			if (lookup_global_or_kb_specific_property_value(class_1,
				Class_description_gkbprop)) {
			    temp = 
				    lookup_global_or_kb_specific_property_value(class_1,
				    Class_definition_gkbprop);
			    temp_1 = CONSP(temp);
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(class_1,
				Class_description_gkbprop);
			temp =  ! !(gensymed_symbol ? 
				TRUEP(memq_function(superior_class,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil)) ? T : Nil;
		    }
		    else if (dependent_compilation_p(0) && 
			    stable_class_p(1,superior_class) && 
			    stable_class_p(1,class_1)) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(class_1,
				Class_description_gkbprop);
			if (gensymed_symbol ? 
				TRUEP(memq_function(superior_class,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil)) {
			    record_free_reference(Qstable_subclass,
				    phrase_cons(superior_class,class_1));
			    temp = T;
			}
			else {
			    record_free_reference(Qstable_not_subclass,
				    phrase_cons(superior_class,class_1));
			    temp = Nil;
			}
		    }
		    else
			temp = Nil;
		}
	    }
	    else
		temp = Nil;
	}
	else if (union_type_specification_p(superior_type)) {
	    union_type = Nil;
	    ab_loop_list_ = CDR(superior_type);
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    union_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_subtype_p(type,union_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = Qnil;
	  end_3:;
	}
	else if (intersection_type_specification_p(superior_type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(superior_type);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_subtype_p(type,
			intersection_type))) {
		temp = Nil;
		goto end_4;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = T;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
	else if (negation_type_specification_p(superior_type))
	    temp =  !TRUEP(type_specifications_could_intersect_p(type,
		    SECOND(superior_type))) ? T : Nil;
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-NOT-SUBTYPE-P */
Object type_specification_not_subtype_p(type,superior_type)
    Object type, superior_type;
{
    Object intersection_type, ab_loop_list_, ab_loop_it_, temp, subtype;

    x_note_fn_call(142,49);
    if ( !EQUAL(type,superior_type)) {
	if (intersection_type_specification_p(superior_type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(superior_type);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specification_not_subtype_p(type,
		    intersection_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	else if (union_type_specification_p(superior_type)) {
	    subtype = Nil;
	    ab_loop_list_ = CDR(superior_type);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_not_subtype_p(type,subtype))) {
		temp = Nil;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = T;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
	else if (negation_type_specification_p(superior_type)) {
	    temp = type_specification_subtype_p(type,SECOND(superior_type));
	    if (temp);
	    else
		temp = type_specification_subtype_p(SECOND(superior_type),
			type);
	}
	else
	    temp = Qnil;
	if (temp);
	else if (difference_type_specification_p(type))
	    temp = type_specification_not_subtype_p(M_CAR(M_CDR(type)),
		    superior_type);
	else if (intersection_type_specification_p(type)) {
	    intersection_type = Nil;
	    ab_loop_list_ = CDR(type);
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    intersection_type = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    type_specification_not_subtype_p(intersection_type,
		    superior_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = Qnil;
	  end_3:;
	}
	else if (union_type_specification_p(type)) {
	    subtype = Nil;
	    ab_loop_list_ = CDR(type);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specification_not_subtype_p(subtype,
		    superior_type))) {
		temp = Nil;
		goto end_4;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = T;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
	else if (negation_type_specification_p(type)) {
	    temp = type_specification_subtype_p(SECOND(type),superior_type);
	    if (temp);
	    else
		temp = type_specification_subtype_p(superior_type,
			SECOND(type));
	}
	else
	    temp = Qnil;
	if (temp);
	else if (filtered_type_specification_p(superior_type) || 
		filtered_type_specification_p(type) || 
		intersection_type_specification_p(type) || 
		union_type_specification_p(type) || 
		negation_type_specification_p(type))
	    temp = Nil;
	else if (SYMBOLP(superior_type)) {
	    if (SYMBOLP(type))
		temp =  !TRUEP(symbolic_type_specification_subtype_p(type,
			superior_type)) ? T : Nil;
	    else if (aggregate_value_type_specification_p(type))
		temp =  !(EQ(superior_type,Qdatum) || EQ(superior_type,
			Qitem_or_datum) || EQ(superior_type,
			Qevaluation_value)) ? T : Nil;
	    else if (member_type_specification_p(type))
		temp = 
			member_type_specification_not_subtype_of_symbolic_type_p(type,
			superior_type);
	    else {
		temp =  !TRUEP(class_type_specification_p(type)) ? T : Nil;
		if (temp);
		else
		    temp = EQ(superior_type,Qevaluation_value) ? ( 
			    !TRUEP(type_specification_subtype_p(type,
			    superior_type)) ? T : Nil) :  
			    !EQ(superior_type,Qitem_or_datum) ? T : Nil;
	    }
	}
	else if (member_type_specification_p(superior_type))
	    temp = member_type_specification_p(type) ? 
		    member_type_specification_not_subtype_p(type,
		    superior_type) : T;
	else if (aggregate_value_type_specification_p(superior_type)) {
	    if (aggregate_value_type_specification_p(type)) {
		if (CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
			CONSP(superior_type) && EQ(M_CAR(superior_type),
			Qab_structure))
		    temp = structure_type_specification_not_subtype_p(type,
			    superior_type);
		else if (fast_sequence_type_specification_p(type) && 
			fast_sequence_type_specification_p(superior_type))
		    temp = sequence_type_specification_not_subtype_p(type,
			    superior_type);
		else
		    temp = T;
	    }
	    else
		temp = T;
	}
	else if (evaluation_value_type_specification_p(superior_type) || 
		unknown_type_specification_p(superior_type) || 
		no_item_type_specification_p(superior_type) || 
		no_item_implies_unknown_type_specification_p(superior_type))
	    temp =  !TRUEP(type_specification_subtype_p(type,
		    superior_type)) ? T : Nil;
	else if (class_type_specification_p(superior_type)) {
	    temp =  !TRUEP(class_type_specification_p(type)) ? T : Nil;
	    if (temp);
	    else
		temp = 
			class_type_specification_not_subtype_p(M_CAR(M_CDR(type)),
			M_CAR(M_CDR(superior_type)));
	}
	else
	    temp = Qnil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* CLASS-TYPE-SPECIFICATION-NOT-SUBTYPE-P */
Object class_type_specification_not_subtype_p(inferior_class,superior_class)
    Object inferior_class, superior_class;
{
    Object temp, gensymed_symbol;
    char temp_1;

    x_note_fn_call(142,50);
    if (EQ(inferior_class,superior_class))
	temp = Nil;
    else {
	if (lookup_global_or_kb_specific_property_value(superior_class,
		Class_description_gkbprop)) {
	    temp = 
		    lookup_global_or_kb_specific_property_value(superior_class,
		    Class_definition_gkbprop);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (lookup_global_or_kb_specific_property_value(inferior_class,
		    Class_description_gkbprop)) {
		temp = 
			lookup_global_or_kb_specific_property_value(inferior_class,
			Class_definition_gkbprop);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(inferior_class,
		    Class_description_gkbprop);
	    temp =  !(gensymed_symbol ? TRUEP(memq_function(superior_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) ? 
		    T : Nil;
	}
	else if ( !TRUEP(dependent_compilation_p(0)) ||  
		!TRUEP(stable_class_p(1,superior_class)) ||  
		!TRUEP(stable_class_p(1,inferior_class)))
	    temp = Nil;
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(inferior_class,
		    Class_description_gkbprop);
	    if (gensymed_symbol ? TRUEP(memq_function(superior_class,
		    ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil)) {
		record_free_reference(Qstable_subclass,
			phrase_cons(superior_class,inferior_class));
		temp = Nil;
	    }
	    else {
		record_free_reference(Qstable_not_subclass,
			phrase_cons(superior_class,inferior_class));
		temp = T;
	    }
	}
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATIONS-COULD-INTERSECT-P */
Object type_specifications_could_intersect_p(type,superior_type)
    Object type, superior_type;
{
    Object temp;

    x_note_fn_call(142,51);
    temp = type_specifications_could_intersect_p_1(type,superior_type);
    return VALUES_1(temp);
}

static Object Qab_class;           /* class */

/* TYPE-SPECIFICATIONS-COULD-INTERSECT-P-1 */
Object type_specifications_could_intersect_p_1(type,superior_type)
    Object type, superior_type;
{
    Object temp, subtype, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(142,52);
    temp = EQUAL(type,superior_type) ? T : Nil;
    if (temp);
    else if (ATOM(superior_type)) {
	if (SYMBOLP(type)) {
	    temp = symbolic_type_specification_subtype_p(type,superior_type);
	    if (temp);
	    else
		temp = symbolic_type_specification_subtype_p(superior_type,
			type);
	}
	else
	    temp = Nil;
	if (temp);
	else if (EQ(superior_type,Qitem_or_datum)) {
	    temp = class_type_specification_p(type);
	    if (temp);
	    else
		temp = aggregate_value_type_specification_p(type);
	}
	else
	    temp = Nil;
	if (temp);
	else
	    temp = EQ(superior_type,Qdatum) ? 
		    aggregate_value_type_specification_p(type) : Qnil;
	if (temp);
	else
	    temp = EQ(superior_type,Qevaluation_value) && CONSP(type) ? 
		    evaluation_value_type_specification_p(type) : Qnil;
    }
    else {
	temp = CAR(superior_type);
	if (EQ(temp,Qab_or)) {
	    subtype = Nil;
	    ab_loop_list_ = M_CDR(superior_type);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specifications_could_intersect_p_1(type,
		    subtype);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = Qnil;
	  end_1:;
	}
	else if (EQ(temp,Qand)) {
	    subtype = Nil;
	    ab_loop_list_ = M_CDR(superior_type);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specifications_could_intersect_p_1(type,
			subtype))) {
		temp = Nil;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = T;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
	else if (EQ(temp,Qnot))
	    temp =  !TRUEP(type_specification_subtype_p(type,
		    M_CAR(M_CDR(superior_type)))) ? T : Nil;
	else if (EQ(temp,Qab_class))
	    temp = class_type_specification_p(type) ? 
		    class_type_specifications_could_intersect_p(superior_type,
		    type) : Qnil;
	else if (EQ(temp,Qsequence) || EQ(temp,Qab_structure)) {
	    temp = EQ(type,Qdatum) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(type,Qitem_or_datum) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(type,Qevaluation_value) ? T : Nil;
	    if (temp);
	    else
		temp = CONSP(type) && EQ(M_CAR(type),Qab_structure) && 
			CONSP(superior_type) && EQ(M_CAR(superior_type),
			Qab_structure) ? 
			structure_type_specifications_could_intersect_p(type,
			superior_type) : Qnil;
	    if (temp);
	    else
		temp = fast_sequence_type_specification_p(type) && 
			fast_sequence_type_specification_p(superior_type) ?
			 
			sequence_type_specifications_could_intersect_p(type,
			superior_type) : Qnil;
	}
	else if (EQ(temp,Qmember)) {
	    temp = EQ(type,Qitem_or_datum) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(type,Qevaluation_value) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(type,Qdatum) ? T : Nil;
	    if (temp);
	    else
		temp = member_type_specification_p(type) ? 
			member_type_specifications_could_intersect_p(superior_type,
			type) : Qnil;
	    if (temp);
	    else
		temp = type_specification_subtype_in_kb_p(type,Qdatum) ? 
			member_type_specification_intersects_datum_type_p(superior_type,
			type) : Qnil;
	}
	else
	    temp = Qnil;
    }
    if (temp);
    else if (ATOM(type)) {
	temp = EQ(type,Qitem_or_datum) ? 
		class_type_specification_p(superior_type) : Qnil;
	if (temp);
	else
	    temp = EQ(type,Qevaluation_value) && CONSP(superior_type) ? 
		    evaluation_value_type_specification_p(superior_type) : 
		    Qnil;
    }
    else {
	temp = M_CAR(type);
	if (EQ(temp,Qab_or)) {
	    subtype = Nil;
	    ab_loop_list_ = M_CDR(type);
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = type_specifications_could_intersect_p_1(subtype,
		    superior_type);
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_3;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = Qnil;
	  end_3:;
	}
	else if (EQ(temp,Qand)) {
	    subtype = Nil;
	    ab_loop_list_ = M_CDR(type);
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    subtype = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(type_specifications_could_intersect_p_1(subtype,
		    superior_type))) {
		temp = Nil;
		goto end_4;
	    }
	    goto next_loop_3;
	  end_loop_3:
	    temp = T;
	    goto end_4;
	    temp = Qnil;
	  end_4:;
	}
	else if (EQ(temp,Qnot))
	    temp =  !TRUEP(type_specification_subtype_p(superior_type,
		    M_CAR(M_CDR(type)))) ? T : Nil;
	else if (EQ(temp,Qmember)) {
	    temp = EQ(superior_type,Qitem_or_datum) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(superior_type,Qevaluation_value) ? T : Nil;
	    if (temp);
	    else
		temp = EQ(superior_type,Qdatum) ? T : Nil;
	    if (temp);
	    else
		temp = member_type_specification_p(superior_type) ? 
			member_type_specifications_could_intersect_p(superior_type,
			type) : Qnil;
	    if (temp);
	    else
		temp = type_specification_subtype_in_kb_p(type,Qdatum) ? 
			member_type_specification_intersects_datum_type_p(type,
			superior_type) : Qnil;
	}
	else
	    temp = Qnil;
    }
    return VALUES_1(temp);
}

/* CLASS-TYPE-SPECIFICATIONS-COULD-INTERSECT-P */
Object class_type_specifications_could_intersect_p(class_spec1,class_spec2)
    Object class_spec1, class_spec2;
{
    Object class1, class2, temp, class_description2, class_description1;
    Object foundation1_qm, foundation2_qm, gensymed_symbol;

    x_note_fn_call(142,53);
    class1 = M_CAR(M_CDR(class_spec1));
    class2 = M_CAR(M_CDR(class_spec2));
    temp = EQ(class1,class2) ? T : Nil;
    if (temp);
    else if (EQ(class1,Qitem)) {
	class_description2 = 
		lookup_global_or_kb_specific_property_value(class2,
		Class_description_gkbprop);
	temp = class_description2 ? ISVREF(class_description2,
		(SI_Long)16L) : Qnil;
    }
    else
	temp = Nil;
    if (temp);
    else if (EQ(class2,Qitem)) {
	class_description1 = 
		lookup_global_or_kb_specific_property_value(class1,
		Class_description_gkbprop);
	temp = class_description1 ? ISVREF(class_description1,
		(SI_Long)16L) : Qnil;
    }
    else
	temp = Nil;
    if (temp);
    else
	temp =  !TRUEP(class_type_specification_not_subtype_p(class1,
		class2)) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(class_type_specification_not_subtype_p(class1,
		class2)) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(stable_class_p(1,class1)) ? T : Nil;
    if (temp);
    else
	temp =  !TRUEP(stable_class_p(1,class2)) ? T : Nil;
    if (temp);
    else {
	foundation1_qm = get_foundation_class_for_class(class1);
	foundation2_qm = get_foundation_class_for_class(class2);
	if (foundation1_qm && foundation2_qm) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(foundation1_qm,
		    Class_description_gkbprop);
	    temp = gensymed_symbol ? memq_function(foundation2_qm,
		    ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
	    if (temp);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(foundation2_qm,
			Class_description_gkbprop);
		temp = gensymed_symbol ? memq_function(foundation1_qm,
			ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
	    }
	}
	else
	    temp = T;
    }
    return VALUES_1(temp);
}

/* TYPE-SPECIFICATION-OF-ROLE-RESULT */
Object type_specification_of_role_result(non_atomic_role)
    Object non_atomic_role;
{
    Object type_qm, temp;

    x_note_fn_call(142,54);
    type_qm = type_of_role(non_atomic_role);
    temp = type_qm ? (valid_datum_type_specification_p(type_qm) ? type_qm :
	     make_class_type_specification(type_qm)) : Nil;
    return VALUES_1(temp);
}

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

static Object list_constant_14;    /* # */

/* TYPE-SPECIFICATION-RETURNING-DATUM-TYPE-OR-UNKNOWN */
Object type_specification_returning_datum_type_or_unknown varargs_1(int, n)
{
    Object datum_subtype;
    Object allow_coercions_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(142,55);
    INIT_ARGS_nonrelocating();
    datum_subtype = REQUIRED_ARG_nonrelocating();
    allow_coercions_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (type_specification_subtype_p(datum_subtype,Qtext))
	return VALUES_1(list_constant_8);
    else if (type_specification_subtype_p(datum_subtype,Qsymbol))
	return VALUES_1(list_constant_9);
    else if (type_specification_subtype_p(datum_subtype,Qtruth_value))
	return VALUES_1(list_constant_10);
    else if (type_specification_subtype_p(datum_subtype,Qinteger))
	return VALUES_1(list_constant_11);
    else if (type_specification_subtype_p(datum_subtype,Qfloat)) {
	if (allow_coercions_qm)
	    return VALUES_1(list_constant_12);
	else
	    return VALUES_1(list_constant_13);
    }
    else if (type_specification_subtype_p(datum_subtype,Qnumber))
	return VALUES_1(list_constant_12);
    else
	return VALUES_1(list_constant_14);
}

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

/* TYPE-SPECIFICATION-RETURNING-DATUM-TYPE */
Object type_specification_returning_datum_type varargs_1(int, n)
{
    Object datum_subtype;
    Object allow_coercions_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(142,56);
    INIT_ARGS_nonrelocating();
    datum_subtype = REQUIRED_ARG_nonrelocating();
    allow_coercions_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (type_specification_subtype_p(datum_subtype,Qtext))
	return VALUES_1(list_constant_15);
    else if (type_specification_subtype_p(datum_subtype,Qsymbol))
	return VALUES_1(list_constant_16);
    else if (type_specification_subtype_p(datum_subtype,Qtruth_value))
	return VALUES_1(list_constant_17);
    else if (type_specification_subtype_p(datum_subtype,Qinteger))
	return VALUES_1(list_constant_18);
    else if (type_specification_subtype_p(datum_subtype,Qfloat)) {
	if (allow_coercions_qm)
	    return VALUES_1(list_constant_19);
	else
	    return VALUES_1(list_constant_20);
    }
    else if (type_specification_subtype_p(datum_subtype,Qnumber))
	return VALUES_1(list_constant_19);
    else
	return VALUES_1(list_constant_21);
}

static Object list_constant_22;    /* # */

static Object list_constant_23;    /* # */

static Object list_constant_24;    /* # */

static Object list_constant_25;    /* # */

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

/* TYPE-SPECIFICATION-HELD-IN-VARIABLE-OR-PARAMETER */
Object type_specification_held_in_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,57);
    gensymed_symbol = ISVREF(variable_or_parameter,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Integer_parameter_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp)
	temp_1 = Qinteger;
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Float_parameter_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = Qfloat;
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantitative_parameter_class_description,
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
	    if (temp)
		temp_1 = Qnumber;
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Symbolic_parameter_class_description,
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
		if (temp)
		    temp_1 = Qsymbol;
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Text_parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp)
			temp_1 = Qtext;
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Logical_parameter_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp = TRUEP(Nil);
			if (temp)
			    temp_1 = Qtruth_value;
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Parameter_class_description,
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
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp = TRUEP(Nil);
			    if (temp)
				temp_1 = Qdatum;
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Integer_variable_class_description,
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
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
				if (temp)
				    temp_1 = list_constant_22;
				else {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(Float_variable_class_description,
					    (SI_Long)18L));
				    sub_class_vector_index = 
					    superior_class_bit_number >>  
					    -  - (SI_Long)3L;
				    if (sub_class_vector_index < 
					    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						{
					gensymed_symbol_1 = 
						UBYTE_8_ISAREF_1(sub_class_bit_vector,
						sub_class_vector_index);
					gensymed_symbol_2 = (SI_Long)1L;
					gensymed_symbol_3 = 
						superior_class_bit_number 
						& (SI_Long)7L;
					gensymed_symbol_2 = 
						gensymed_symbol_2 << 
						gensymed_symbol_3;
					gensymed_symbol_1 = 
						gensymed_symbol_1 & 
						gensymed_symbol_2;
					temp = (SI_Long)0L < gensymed_symbol_1;
				    }
				    else
					temp = TRUEP(Nil);
				    if (temp)
					temp_1 = list_constant_23;
				    else {
					sub_class_bit_vector = 
						ISVREF(gensymed_symbol,
						(SI_Long)19L);
					superior_class_bit_number = 
						IFIX(ISVREF(Quantitative_variable_class_description,
						(SI_Long)18L));
					sub_class_vector_index = 
						superior_class_bit_number 
						>>  -  - (SI_Long)3L;
					if (sub_class_vector_index < 
						IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						    {
					    gensymed_symbol_1 = 
						    UBYTE_8_ISAREF_1(sub_class_bit_vector,
						    sub_class_vector_index);
					    gensymed_symbol_2 = (SI_Long)1L;
					    gensymed_symbol_3 = 
						    superior_class_bit_number 
						    & (SI_Long)7L;
					    gensymed_symbol_2 = 
						    gensymed_symbol_2 << 
						    gensymed_symbol_3;
					    gensymed_symbol_1 = 
						    gensymed_symbol_1 & 
						    gensymed_symbol_2;
					    temp = (SI_Long)0L < 
						    gensymed_symbol_1;
					}
					else
					    temp = TRUEP(Nil);
					if (temp)
					    temp_1 = list_constant_24;
					else {
					    sub_class_bit_vector = 
						    ISVREF(gensymed_symbol,
						    (SI_Long)19L);
					    superior_class_bit_number = 
						    IFIX(ISVREF(Symbolic_variable_class_description,
						    (SI_Long)18L));
					    sub_class_vector_index = 
						    superior_class_bit_number 
						    >>  -  - (SI_Long)3L;
					    if (sub_class_vector_index < 
						    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							{
						gensymed_symbol_1 = 
							UBYTE_8_ISAREF_1(sub_class_bit_vector,
							sub_class_vector_index);
						gensymed_symbol_2 = 
							(SI_Long)1L;
						gensymed_symbol_3 = 
							superior_class_bit_number 
							& (SI_Long)7L;
						gensymed_symbol_2 = 
							gensymed_symbol_2 
							<< gensymed_symbol_3;
						gensymed_symbol_1 = 
							gensymed_symbol_1 
							& gensymed_symbol_2;
						temp = (SI_Long)0L < 
							gensymed_symbol_1;
					    }
					    else
						temp = TRUEP(Nil);
					    if (temp)
						temp_1 = list_constant_25;
					    else {
						sub_class_bit_vector = 
							ISVREF(gensymed_symbol,
							(SI_Long)19L);
						superior_class_bit_number 
							= 
							IFIX(ISVREF(Text_variable_class_description,
							(SI_Long)18L));
						sub_class_vector_index = 
							superior_class_bit_number 
							>>  -  - (SI_Long)3L;
						if (sub_class_vector_index 
							< 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							    {
						    gensymed_symbol_1 = 
							    UBYTE_8_ISAREF_1(sub_class_bit_vector,
							    sub_class_vector_index);
						    gensymed_symbol_2 = 
							    (SI_Long)1L;
						    gensymed_symbol_3 = 
							    superior_class_bit_number 
							    & (SI_Long)7L;
						    gensymed_symbol_2 = 
							    gensymed_symbol_2 
							    << 
							    gensymed_symbol_3;
						    gensymed_symbol_1 = 
							    gensymed_symbol_1 
							    & 
							    gensymed_symbol_2;
						    temp = (SI_Long)0L < 
							    gensymed_symbol_1;
						}
						else
						    temp = TRUEP(Nil);
						if (temp)
						    temp_1 = list_constant_26;
						else {
						    sub_class_bit_vector = 
							    ISVREF(gensymed_symbol,
							    (SI_Long)19L);
						    superior_class_bit_number 
							    = 
							    IFIX(ISVREF(Logical_variable_class_description,
							    (SI_Long)18L));
						    sub_class_vector_index 
							    = 
							    superior_class_bit_number 
							    >>  -  - 
							    (SI_Long)3L;
						    if (sub_class_vector_index 
							    < 
							    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								{
							gensymed_symbol_1 
								= 
								UBYTE_8_ISAREF_1(sub_class_bit_vector,
								sub_class_vector_index);
							gensymed_symbol_2 
								= (SI_Long)1L;
							gensymed_symbol_3 
								= 
								superior_class_bit_number 
								& (SI_Long)7L;
							gensymed_symbol_2 
								= 
								gensymed_symbol_2 
								<< 
								gensymed_symbol_3;
							gensymed_symbol_1 
								= 
								gensymed_symbol_1 
								& 
								gensymed_symbol_2;
							temp = (SI_Long)0L 
								< 
								gensymed_symbol_1;
						    }
						    else
							temp = TRUEP(Nil);
						    if (temp)
							temp_1 = 
								list_constant_7;
						    else {
							sub_class_bit_vector 
								= 
								ISVREF(gensymed_symbol,
								(SI_Long)19L);
							superior_class_bit_number 
								= 
								IFIX(ISVREF(Variable_class_description,
								(SI_Long)18L));
							sub_class_vector_index 
								= 
								superior_class_bit_number 
								>>  -  - 
								(SI_Long)3L;
							if (sub_class_vector_index 
								< 
								IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								    {
							    gensymed_symbol_1 
								    = 
								    UBYTE_8_ISAREF_1(sub_class_bit_vector,
								    sub_class_vector_index);
							    gensymed_symbol_2 
								    = 
								    (SI_Long)1L;
							    gensymed_symbol_3 
								    = 
								    superior_class_bit_number 
								    & 
								    (SI_Long)7L;
							    gensymed_symbol_2 
								    = 
								    gensymed_symbol_2 
								    << 
								    gensymed_symbol_3;
							    gensymed_symbol_1 
								    = 
								    gensymed_symbol_1 
								    & 
								    gensymed_symbol_2;
							    temp = 
								    (SI_Long)0L 
								    < 
								    gensymed_symbol_1;
							}
							else
							    temp = TRUEP(Nil);
							if (temp)
							    temp_1 = 
								    list_constant_27;
							else
							    temp_1 = Qnil;
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    return VALUES_1(temp_1);
}

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

/* TYPE-SPECIFICATION-HELD-IN-TYPE */
Object type_specification_held_in_type(type_specification)
    Object type_specification;
{
    Object temp, type, ab_loop_list_;

    x_note_fn_call(142,58);
    temp = type_specification_subtype_p(type_specification,
	    list_constant_28) ? list_constant_27 : Qnil;
    if (temp);
    else {
	type = Nil;
	ab_loop_list_ = list_constant_29;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (type_specification_subtype_p(type_specification,
		type_specification_returning_datum_type(1,type))) {
	    temp = type;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    if (temp);
    else {
	type = Nil;
	ab_loop_list_ = list_constant_29;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	type = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (type_specification_subtype_p(type_specification,
		type_specification_returning_datum_type_or_unknown(1,type))) {
	    temp = make_type_specification_union(type,list_constant);
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_2:;
    }
    return VALUES_1(temp);
}

/* DEF-NUMERIC-SUBTYPE */
Object def_numeric_subtype varargs_1(int, n)
{
    Object type;
    Object plural_of_type, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(142,59);
    INIT_ARGS_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    plural_of_type = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = plural_of_type;
    if (temp);
    else
	temp = type;
    return mutate_global_or_kb_specific_property_value(type,temp,
	    Numeric_data_type_gkbprop);
}

/* DATA-TYPE-OF-NON-LOGICAL-DATUM */
Object data_type_of_non_logical_datum(datum)
    Object datum;
{
    Object temp;

    x_note_fn_call(142,60);
    if (SYMBOLP(datum))
	temp = Qsymbol;
    else if (text_string_p(datum))
	temp = Qtext;
    else if (FIXNUMP(datum))
	temp = Qinteger;
    else if (FLOATP(datum))
	temp = Qfloat;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(datum) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L)
	temp = Qfloat;
    else if (INLINE_LONG_P(datum) != (SI_Long)0L)
	temp = Qlong;
    else if (INLINE_LONG_VECTOR_P(datum) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(datum)) == (SI_Long)1L)
	temp = Qlong;
    else if (NUMBERP(datum))
	temp = Qnumber;
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant;     /* "Fetching a value of type ~a, an unrecognized type or unit of ~
				    *        measure."
				    */

/* WARN-ABOUT-UNRECOGNIZED-TYPE */
Object warn_about_unrecognized_type(unit_of_measure_or_type)
    Object unit_of_measure_or_type;
{
    x_note_fn_call(142,61);
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)1L),string_constant,
		unit_of_measure_or_type);
    else
	return VALUES_1(Nil);
}

/* DATA-TYPE-OF-VARIABLE-OR-PARAMETER-DATUM */
Object data_type_of_variable_or_parameter_datum(datum,variable_or_parameter)
    Object datum, variable_or_parameter;
{
    Object type_spec, temp;

    x_note_fn_call(142,62);
    type_spec = 
	    type_specification_of_variable_or_parameter_value(variable_or_parameter);
    if ( !EQ(type_spec,Qtruth_value) &&  !EQ(type_spec,Qboolean))
	temp = data_type_of_non_logical_datum(datum);
    else {
	if (EQ(Qtruth_value,Qinteger))
	    temp = FIXNUMP(datum) ? T : Nil;
	else if (EQ(Qtruth_value,Qlong))
	    temp = INLINE_LONG_P(datum) != (SI_Long)0L ? T : Nil;
	else if (EQ(Qtruth_value,Qfloat))
	    temp = FLOATP(datum) ? T : Nil;
	else if (EQ(Qtruth_value,Qsymbol))
	    temp = datum ? (SYMBOLP(datum) ? T : Nil) : Qnil;
	else if (EQ(Qtruth_value,Qtext))
	    temp = text_string_p(datum);
	else if (EQ(Qtruth_value,Qtruth_value))
	    temp = FIXNUMP(datum) && FIXNUM_LE(Falsity,datum) ? 
		    (FIXNUM_LE(datum,Truth) ? T : Nil) : Qnil;
	else if (EQ(Qtruth_value,Qboolean)) {
	    if (FIXNUMP(datum)) {
		temp = FIXNUM_EQ(datum,Falsity) ? T : Nil;
		if (temp);
		else
		    temp = FIXNUM_EQ(datum,Truth) ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else if (EQ(Qtruth_value,Qnumber) || EQ(Qtruth_value,Qinteger) || 
		EQ(Qtruth_value,Qfloat) || EQ(Qtruth_value,Qlong) || 
		lookup_global_or_kb_specific_property_value(Qtruth_value,
		Numeric_data_type_gkbprop)) {
	    temp = FLOATP(datum) ? T : Nil;
	    if (temp);
	    else
		temp = FIXNUMP(datum) ? T : Nil;
	}
	else
	    temp = Nil;
	if (temp)
	    temp = Qtruth_value;
	else
	    temp = data_type_of_non_logical_datum(datum);
    }
    return VALUES_1(temp);
}

/* ANALYZE-BYTE-CODE-BODY-FOR-FREE-REFERENCE-CONSISTENCY */
Object analyze_byte_code_body_for_free_reference_consistency(byte_code_body)
    Object byte_code_body;
{
    Object free_reference_vector_qm, type, reference;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,63);
    free_reference_vector_qm = ISVREF(byte_code_body,(SI_Long)7L);
    if (free_reference_vector_qm) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(free_reference_vector_qm));
	type = Nil;
	reference = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	type = ISVREF(free_reference_vector_qm,index_1);
	reference = ISVREF(free_reference_vector_qm,index_1 + (SI_Long)1L);
	analyze_single_free_reference_for_consistency(type,reference);
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_1;   /* "~%  " */

static Object string_constant_2;   /* "~%  None" */

/* WRITE-BYTE-CODE-BODY-FREE-REFERENCES */
Object write_byte_code_body_free_references(byte_code_body)
    Object byte_code_body;
{
    Object free_reference_vector_qm, type, reference;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,64);
    free_reference_vector_qm = ISVREF(byte_code_body,(SI_Long)7L);
    if (free_reference_vector_qm) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(free_reference_vector_qm));
	type = Nil;
	reference = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	type = ISVREF(free_reference_vector_qm,index_1);
	reference = ISVREF(free_reference_vector_qm,index_1 + (SI_Long)1L);
	tformat(1,string_constant_1);
	twrite_single_free_reference_for_consistency(type,reference);
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return tformat(1,string_constant_2);
}

Object Environment_allocation_schemes = UNBOUND;

Object Maximum_environment_vector_length = UNBOUND;

/* RECLAIM-ENVIRONMENT-VECTOR */
Object reclaim_environment_vector(environment_vector)
    Object environment_vector;
{
    Object length_1, value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,65);
    length_1 = SIMPLE_ARRAY_ANY_1_LENGTH(environment_vector);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    value = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    value = ISVREF(environment_vector,index_1);
    if ( !(FIXNUMP(value) || SYMBOLP(value) || SIMPLE_VECTOR_P(value)))
	reclaim_if_evaluation_value_1(value);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    reclaim_managed_simple_vector(environment_vector);
    return VALUES_1(Nil);
}

/* COPY-ENVIRONMENT-VECTOR */
Object copy_environment_vector(environment_vector)
    Object environment_vector;
{
    Object length_1, new_vector, value, svref_new_value, temp;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,66);
    length_1 = SIMPLE_ARRAY_ANY_1_LENGTH(environment_vector);
    new_vector = allocate_managed_simple_vector(length_1);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length_1);
    value = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    value = ISVREF(environment_vector,index_1);
    svref_new_value = FIXNUMP(value) || value && SYMBOLP(value) || 
	    SIMPLE_VECTOR_P(value) ? value : copy_if_evaluation_value_1(value);
    ISVREF(new_vector,index_1) = svref_new_value;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object Kstack_error;        /* :stack-error */

/* RAW-STACK-ERROR */
Object raw_stack_error(top_of_stack,error_name,error_text)
    Object top_of_stack, error_name, error_text;
{
    Object result;

    x_note_fn_call(142,67);
    result = VALUES_4(top_of_stack,error_name,error_text,Nil);
    THROW(Kstack_error,result);
    return VALUES_1(Nil);
}

/* RAW-STACK-ERROR-NAMED-ERROR */
Object raw_stack_error_named_error(top_of_stack,error_text)
    Object top_of_stack, error_text;
{
    Object result;

    x_note_fn_call(142,68);
    result = VALUES_4(top_of_stack,Qerror,error_text,Nil);
    THROW(Kstack_error,result);
    return VALUES_1(Nil);
}

/* RAW-STACK-ERROR-1 */
Object raw_stack_error_1(top_of_stack,error_name,error_text)
    Object top_of_stack, error_name, error_text;
{
    Object result;

    x_note_fn_call(142,69);
    result = VALUES_4(top_of_stack,error_name,error_text,T);
    THROW(Kstack_error,result);
    return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

/* TFORMAT-STACK-ERROR-TEXT-STRING */
Object tformat_stack_error_text_string varargs_1(int, n)
{
    Object control_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(7);

    x_note_fn_call(142,70);
    INIT_ARGS_nonrelocating();
    control_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
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
		  tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,
			  arg7,arg8,arg9);
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
    return make_error_text(text_string,snapshots);
}

static Object string_constant_3;   /* "Error explicitly triggered from the C debugger." */

/* CAUSE-STACK-ERROR */
Object cause_stack_error()
{
    Object top_of_stack, message_1;

    x_note_fn_call(142,71);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(1,string_constant_3);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_internal_procedure_environment_printing_qm, Qallow_internal_procedure_environment_printing_qm);

/* G2-ENABLE-DISASSEMBLER */
Object g2_enable_disassembler()
{
    x_note_fn_call(142,72);
    Disassemble_enabled_qm = T;
    Allow_internal_procedure_environment_printing_qm = T;
    return VALUES_1(Allow_internal_procedure_environment_printing_qm);
}

/* G2-DISABLE-DISASSEMBLER */
Object g2_disable_disassembler()
{
    x_note_fn_call(142,73);
    Disassemble_enabled_qm = Nil;
    Allow_internal_procedure_environment_printing_qm = Nil;
    return VALUES_1(Allow_internal_procedure_environment_printing_qm);
}

static Object string_constant_4;   /* "A floating point exception has occurred.  Floating point exceptions are ~
				    *      arithmetic errors such as dividing by zero, or overflowing or ~
				    *      underflowing floating point number representations."
				    */

/* SIGNAL-FLOATING-POINT-EXCEPTION-STACK-ERROR */
Object signal_floating_point_exception_stack_error()
{
    Object top_of_stack, message_1;

    x_note_fn_call(142,74);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(1,string_constant_4);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

static Object Qerror_description;  /* error-description */

/* PUT-ERROR-DESCRIPTION */
Object put_error_description(error_1,error_text,initializing_p)
    Object error_1, error_text, initializing_p;
{
    x_note_fn_call(142,75);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(error_1,Qerror_description);
    return set_lookup_slot_value_1(error_1,Qerror_description,
	    error_text_p(error_text) ? 
	    convert_text_string_to_text(CONSP(error_text) ? 
	    FIRST(error_text) : error_text) : error_text);
}

/* INITIAL-ERROR-SOURCE-TRACE */
Object initial_error_source_trace(class_1)
    Object class_1;
{
    x_note_fn_call(142,76);
    return VALUES_1(Nil);
}

static Object Qerror_trace;        /* error-trace */

static Object Qerror_trace_description;  /* error-trace-description */

static Object array_constant_1;    /* # */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object Qerror_trace_source_item;  /* error-trace-source-item */

static Object Qerror_trace_source_line;  /* error-trace-source-line */

static Object Qerror_trace_source_column;  /* error-trace-source-column */

/* GET-ERROR-SOURCE-TRACE */
Object get_error_source_trace(error_1)
    Object error_1;
{
    Object error_text_qm, error_source_item, error_source_line;
    Object error_source_column, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, temp, gensymed_symbol, temp_1;
    Object item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(142,77);
    error_text_qm = Nil;
    error_source_item = Nil;
    error_source_line = Nil;
    error_source_column = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(error_1,
	    Qerror_trace,Nil);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    error_text_qm = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    error_source_item = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    error_source_line = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    error_source_column = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qerror_trace_description;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)1L)) = Qerror_trace_description;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = error_text_qm ? convert_text_to_text_string(1,
		error_text_qm) : copy_as_wide_string(array_constant_1);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = error_text_qm ? convert_text_to_text_string(1,
		error_text_qm) : copy_as_wide_string(array_constant_1);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qerror_trace_source_item;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)3L)) = Qerror_trace_source_item;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = error_source_item;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = error_source_item;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qerror_trace_source_line;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)5L)) = Qerror_trace_source_line;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = error_source_line;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = error_source_line;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qerror_trace_source_column;
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp_1,FIX((SI_Long)7L)) = Qerror_trace_source_column;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = error_source_column;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	temp_1 = temp_2 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp_1;
    }
    else {
	temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = error_source_column;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_2 = TRUEP(Nil);
	svref_new_value = temp_2 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp_1,FIX((SI_Long)8L)) = svref_new_value;
    }
    ab_loopvar__2 = eval_cons_1(eval_cons_1(gensymed_symbol,Qab_structure),
	    Nil);
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
    temp = allocate_evaluation_sequence(temp);
    return VALUES_1(temp);
}

static Object Qg2_error;           /* g2-error */

static Object Qrpc_error;          /* rpc-error */

static Object Qg2_rpc_error;       /* g2-rpc-error */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qdefault_error;      /* default-error */

/* MAP-ERROR-SYMBOL-TO-CLASS-NAME */
Object map_error_symbol_to_class_name(error_symbol)
    Object error_symbol;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(142,78);
    if (EQ(Qerror,error_symbol))
	return VALUES_1(Qg2_error);
    else if (EQ(Qrpc_error,error_symbol))
	return VALUES_1(Qg2_rpc_error);
    else {
	if (SYMBOLP(error_symbol)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = error_symbol;
	    key_hash_value = SXHASH_SYMBOL_1(error_symbol) & 
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
		gensymed_symbol = error_symbol;
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
	if (temp_2) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = error_symbol;
	    key_hash_value = SXHASH_SYMBOL_1(error_symbol) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_14;
	  end_loop_13:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_13;
	  end_loop_14:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_12;
	  end_loop_12:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = error_symbol;
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
	  next_loop_15:
	    if (level < ab_loop_bind_)
		goto end_loop_15;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_16:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_17;
	  end_loop_16:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_16;
	  end_loop_17:
	  end_6:
	    level = level - (SI_Long)1L;
	    goto next_loop_15;
	  end_loop_15:;
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
	      next_loop_18:
		if (level < ab_loop_bind_)
		    goto end_loop_18;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_19:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_20;
	      end_loop_19:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_19;
	      end_loop_20:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_18;
	      end_loop_18:;
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
	      next_loop_21:
		if (level < ab_loop_bind_)
		    goto end_loop_21;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_22:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_23;
	      end_loop_22:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_22;
	      end_loop_23:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_21;
	      end_loop_21:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		gensymed_symbol_1 = 
			lookup_global_or_kb_specific_property_value(Qerror,
			Class_description_gkbprop);
		if (gensymed_symbol_1) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_2 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_2 = TRUEP(Nil);
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    return VALUES_1(error_symbol);
	else
	    return VALUES_1(Qdefault_error);
    }
}

static Object Qerror_source_item;  /* error-source-item */

static Object Qerror_source_line;  /* error-source-line */

static Object Qerror_source_column;  /* error-source-column */

/* ADD-SOURCE-INFO-TO-ERROR-TRACE */
Object add_source_info_to_error_trace(error_object)
    Object error_object;
{
    Object temp, temp_1, temp_2, slot_value_push_modify_macro_arg, car_1;
    Object cdr_1, error_trace_new_value;

    x_note_fn_call(142,79);
    temp = copy_text(get_lookup_slot_value(error_object,Qerror_description));
    temp_1 = get_lookup_slot_value(error_object,Qerror_source_item);
    temp_2 = get_lookup_slot_value(error_object,Qerror_source_line);
    slot_value_push_modify_macro_arg = slot_value_list_4(temp,temp_1,
	    temp_2,get_lookup_slot_value(error_object,Qerror_source_column));
    car_1 = slot_value_push_modify_macro_arg;
    cdr_1 = get_lookup_slot_value_given_default(error_object,Qerror_trace,Nil);
    error_trace_new_value = slot_value_cons_1(car_1,cdr_1);
    set_non_savable_lookup_slot_value(error_object,Qerror_trace,
	    error_trace_new_value);
    return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* SETUP-SOURCE-INFO-FOR-ERROR-OBJECT */
Object setup_source_info_for_error_object(error_object)
    Object error_object;
{
    Object program_counter_qm, code_body, line_number_qm, temp;
    Object non_wrapped_line_index, non_wrapped_user_column_position;
    Declare_special(1);
    Object result;

    x_note_fn_call(142,80);
    if (Current_computation_instance && 
	    ok_to_get_source_code_lookup_info_p(Current_computation_instance)) 
		{
	program_counter_qm = ISVREF(Current_computation_instance,(SI_Long)3L);
	code_body = 
		code_body_of_invocation_function(Current_computation_instance);
	PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
	  if (program_counter_qm) {
	      result = get_annotation_for_address_if_any(program_counter_qm,
		      Code_body);
	      MVS_5(result,line_number_qm,temp,non_wrapped_line_index,temp,
		      non_wrapped_user_column_position);
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(error_object,Qerror_source_item);
	      set_lookup_slot_value_1(error_object,Qerror_source_item,
		      get_lookup_slot_value_given_default(procedure_definition_of_code_body_function(Code_body),
		      Qname_or_names_for_frame,Nil));
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(error_object,Qerror_source_line);
	      set_lookup_slot_value_1(error_object,Qerror_source_line,
		      line_number_qm ? non_wrapped_line_index : 
		      Default_error_source_line);
	      if (Noting_changes_to_kb_p)
		  note_change_to_block_1(error_object,Qerror_source_column);
	      set_lookup_slot_value_1(error_object,Qerror_source_column,
		      line_number_qm ? non_wrapped_user_column_position : 
		      Default_error_source_column);
	      add_source_info_to_error_trace(error_object);
	  }
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* CONVERT-SYMBOL-TEXT-TO-ERROR-OBJECT */
Object convert_symbol_text_to_error_object(error_1,error_text)
    Object error_1, error_text;
{
    Object class_to_create, error_object;

    x_note_fn_call(142,81);
    class_to_create = map_error_symbol_to_class_name(error_1);
    error_object = make_transient_item(class_to_create);
    put_error_description(error_object,error_text,Nil);
    setup_source_info_for_error_object(error_object);
    return VALUES_1(error_object);
}

/* CONVERT-ERROR-OBJECT-TO-SYMBOL-TEXT */
Object convert_error_object_to_symbol_text(error_1)
    Object error_1;
{
    Object class_of_error, error_text, text_to_return, wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(142,82);
    class_of_error = ISVREF(ISVREF(error_1,(SI_Long)1L),(SI_Long)1L);
    error_text = get_lookup_slot_value(error_1,Qerror_description);
    if (error_text)
	text_to_return = convert_text_to_text_string(1,error_text);
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	text_to_return = wide_string_bv16;
    }
    return VALUES_2(class_of_error,text_to_return);
}

/* MAP-BETWEEN-ERROR-STYLES */
Object map_between_error_styles(error_name_or_error_object,error_message,
	    new_style_error_qm,new_style_handler_qm)
    Object error_name_or_error_object, error_message, new_style_error_qm;
    Object new_style_handler_qm;
{
    x_note_fn_call(142,83);
    if (new_style_error_qm &&  !TRUEP(new_style_handler_qm))
	return convert_error_object_to_symbol_text(error_name_or_error_object);
    else if ( !TRUEP(new_style_error_qm) && new_style_handler_qm)
	return convert_symbol_text_to_error_object(error_name_or_error_object,
		error_message);
    else
	return VALUES_2(error_name_or_error_object,error_message);
}

/* RAW-STACK-ERROR-THROW-OBJECT-FUNCTION */
Object raw_stack_error_throw_object_function(top_of_stack,error_object)
    Object top_of_stack, error_object;
{
    Object error_description_qm, temp, wide_string_bv16;
    SI_Long bv16_length, aref_arg_2, aref_new_value;

    x_note_fn_call(142,84);
    error_description_qm = get_lookup_slot_value(error_object,
	    Qerror_description);
    if (error_description_qm)
	temp = convert_text_to_text_string(1,error_description_qm);
    else {
	wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)0L + 
		(SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = (SI_Long)0L & (SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)0L,(SI_Long)0L);
	temp = wide_string_bv16;
    }
    return raw_stack_error_1(top_of_stack,error_object,temp);
}

static Object string_constant_5;   /* "~A" */

/* CHECK-TYPE-OR-STACK-ERROR */
Object check_type_or_stack_error varargs_1(int, n)
{
    Object value, type;
    Object allow_other_keys, error_message_qm, top_of_stack, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(7);

    x_note_fn_call(142,85);
    INIT_ARGS_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    type = REQUIRED_ARG_nonrelocating();
    allow_other_keys = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    error_message_qm = check_type_error_message(3,value,type,allow_other_keys);
    if (error_message_qm) {
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
		      tformat(2,string_constant_5,error_message_qm);
		      reclaim_text_string(error_message_qm);
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
    else
	return VALUES_1(Nil);
}

/* CLEAR-BASIC-PROFILING-STRUCTURE */
Object clear_basic_profiling_structure(s)
    Object s;
{
    Object aref_arg_1, count_array;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(142,86);
    aref_arg_1 = ISVREF(s,(SI_Long)4L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    ISVREF(s,(SI_Long)5L) = FIX((SI_Long)0L);
    count_array = ISVREF(s,(SI_Long)6L);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(count_array));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    ISVREF(count_array,i) = FIX((SI_Long)0L);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MAKE-BASIC-PROFILING-STRUCTURE */
Object make_basic_profiling_structure()
{
    Object new_structure;

    x_note_fn_call(142,87);
    new_structure = make_basic_profiling_structure1_1();
    clear_basic_profiling_structure(new_structure);
    return VALUES_1(new_structure);
}

/* CLEAR-GLOBAL-PROFILING-STRUCTURE */
Object clear_global_profiling_structure(s)
    Object s;
{
    Object restart_profiling_qm, aref_arg_1;

    x_note_fn_call(142,88);
    restart_profiling_qm = Nil;
    if (Profiling_enabled_qm) {
	g2_toggle_system_profiling();
	restart_profiling_qm = T;
    }
    aref_arg_1 = ISVREF(s,(SI_Long)8L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)7L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)2L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)3L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)4L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)5L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    aref_arg_1 = ISVREF(s,(SI_Long)6L);
    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,0.0);
    clear_call_hash(ISVREF(s,(SI_Long)1L));
    if (restart_profiling_qm)
	g2_toggle_system_profiling();
    return VALUES_1(Nil);
}

static Object Qg2_list;            /* g2-list */

static Object string_constant_6;   /* "~a" */

static Object Qfloat_array;        /* float-array */

/* ADD-PROFILING-STRUCTURE-TO-G2-LIST */
Object add_profiling_structure_to_g2_list(s,call_list)
    Object s, call_list;
{
    Object item_list, temp, calls, registration_count, call_data;
    Object ab_loop_iter_flag_, temp_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float;
    SI_Long index_1, ab_loop_bind_, potential_registrations, bv16_length;
    SI_Long aref_arg_2, aref_new_value, length_1;
    double float_time_units_per_second, aref_new_value_1;
    Declare_special(5);

    x_note_fn_call(142,89);
    item_list = make_transient_item(Qg2_list);
    float_time_units_per_second = (double)IFIX(Fixnum_time_units_per_second);
    temp = ISVREF(s,(SI_Long)5L);
    if (NUMBERP(temp)) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(Registered_activities_array));
	potential_registrations = (SI_Long)1L;
	calls = ISVREF(s,(SI_Long)6L);
	registration_count = FIX((SI_Long)0L);
	call_data = Nil;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    potential_registrations = potential_registrations + (SI_Long)1L;
	temp = ISVREF(calls,index_1);
	temp_1 = FIX((SI_Long)0L);
	if (NUM_GT(temp,temp_1)) {
	    call_data = make_transient_item(Qg2_list);
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
		      tformat(2,string_constant_6,
			      ISVREF(Registered_activities_array,index_1));
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    g2_list_insert_at_beginning(temp,call_data);
	    g2_list_insert_at_end(2,ISVREF(calls,index_1),call_data);
	    g2_list_insert_at_end(2,call_data,item_list);
	    registration_count = add1(registration_count);
	}
	ab_loop_iter_flag_ = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	g2_list_insert_at_beginning(FIX(potential_registrations),item_list);
	g2_list_insert_at_beginning(registration_count,item_list);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	aref_new_value_1 = FIXNUM_EQ(ISVREF(s,(SI_Long)5L),
		FIX((SI_Long)0L)) ? 0.0 : DFLOAT_ISAREF_1(ISVREF(s,
		(SI_Long)4L),(SI_Long)0L) / 
		(double)IFIX(FIXNUM_TIMES(ISVREF(s,(SI_Long)5L),
		DOUBLE_TO_DOUBLE_FLOAT(float_time_units_per_second)));
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	g2_list_insert_at_beginning(new_float,item_list);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_2 = Vector_of_simple_float_array_pools;
	    temp_3 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
	    }
	    else {
		temp_2 = Available_float_array_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
		temp_2 = Available_float_array_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = amf_available_array_cons_qm;
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
	aref_new_value_1 = DFLOAT_ISAREF_1(ISVREF(s,(SI_Long)4L),
		(SI_Long)0L) / float_time_units_per_second;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	g2_list_insert_at_beginning(new_float,item_list);
	g2_list_insert_at_beginning(ISVREF(s,(SI_Long)5L),item_list);
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
		  tformat(2,string_constant_6,ISVREF(s,(SI_Long)1L));
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	g2_list_insert_at_beginning(temp,item_list);
	g2_list_insert_at_beginning(item_list,call_list);
    }
    return VALUES_1(Nil);
}

static Object string_constant_7;   /* "No Profiling Information~a" */

static Object string_constant_8;   /* " " */

static Object string_constant_9;   /* " ~a Items profiled" */

/* G2-PROFILED-CALL-INFORMATION */
Object g2_profiled_call_information()
{
    Object call_data, profiler, verbose, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, x, ab_less_than_branch_qm_;
    Object gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long ab_table_length_, ab_index_, profile_count;
    char temp_1;
    Declare_special(6);

    x_note_fn_call(142,90);
    call_data = make_transient_item(Qg2_list);
    profiler = Profiling_structure;
    verbose = Nil;
    if ( !TRUEP(profiler)) {
	if (verbose)
	    format((SI_Long)2L,T,"~% no profiling structure");
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
		  tformat(2,string_constant_7,string_constant_8);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	g2_list_insert_at_end(2,temp,call_data);
    }
    else {
	scope_conses = Scope_conses;
	ab_hash_table_ = ISVREF(profiler,(SI_Long)1L);
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	x = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,5);
	  profile_count = (SI_Long)0L;
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
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
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
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
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
	  x = M_CDR(ab_entry_cons_);
	  if (verbose)
	      format((SI_Long)3L,T,"~%Adding profile ~a",FIX(profile_count));
	  add_profiling_structure_to_g2_list(x,call_data);
	  profile_count = profile_count + (SI_Long)1L;
	  goto next_loop;
	end_loop_3:
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(2,string_constant_9,FIX(profile_count));
		    temp = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  g2_list_insert_at_beginning(temp,call_data);
	POP_SPECIAL();
    }
    return VALUES_1(call_data);
}

Object Display_profiling_names = UNBOUND;

Object Scheduling_profiling_names = UNBOUND;

Object Data_service_profiling_names = UNBOUND;

Object Kb_io_profiling_names = UNBOUND;

Object Icp_profiling_names = UNBOUND;

Object Workstation_profiling_names = UNBOUND;

Object Overhead_kb_profiling_names = UNBOUND;

Object G2gl_profiling_lists = UNBOUND;

/* DISABLE-AND-CLEAR-SYSTEM-PROFILING */
Object disable_and_clear_system_profiling()
{
    x_note_fn_call(142,91);
    if (Profiling_enabled_qm)
	g2_disable_system_profiling();
    g2_clear_profiling_inner();
    return VALUES_1(Nil);
}

static Object Qquantity_list;      /* quantity-list */

static Object float_constant;      /* 0.0 */

static Object Qcontinue_current_kb_save_or_backup;  /* continue-current-kb-save-or-backup */

static Object Qterminate_kb_save_or_backup;  /* terminate-kb-save-or-backup */

static Object Qsys_proc_read_kb;   /* sys-proc-read-kb */

/* G2-SYSTEM-PROFILE */
Object g2_system_profile()
{
    Object system_data, profiler, restart_qm, scope_conses, ab_hash_table_;
    Object ab_tree_form_, ab_node_stack_, ab_current_node_, ab_current_alist_;
    Object ab_entry_cons_, ab_skip_list_p_, ab_tail_node_, x, scheduling_time;
    Object data_service_time, kb_io_time, overhead_time, workstation_time;
    Object display_time, icp_time, system_time, name, duration;
    Object ab_less_than_branch_qm_, gensymed_symbol, temp_3;
    Object amf_available_array_cons_qm, amf_array, temp_5, temp_6, amf_result;
    Object new_float;
    SI_Long item_count, ab_table_length_, ab_index_, i, ab_loop_bind_;
    char temp_4;
    double idle_time, clock_tick_time, total_time, temp, temp_1, temp_2;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(142,92);
    system_data = make_transient_item(Qquantity_list);
    profiler = Profiling_structure;
    restart_qm = Nil;
    item_count = (SI_Long)11L;
    if (Profiling_enabled_qm) {
	g2_disable_system_profiling();
	restart_qm = T;
    }
    if (profiler) {
	scope_conses = Scope_conses;
	ab_hash_table_ = ISVREF(profiler,(SI_Long)1L);
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	x = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  scheduling_time = float_constant;
	  data_service_time = float_constant;
	  kb_io_time = float_constant;
	  overhead_time = float_constant;
	  workstation_time = float_constant;
	  display_time = 
		  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(profiler,
		  (SI_Long)5L),(SI_Long)0L));
	  icp_time = 
		  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(profiler,
		  (SI_Long)6L),(SI_Long)0L));
	  idle_time = DFLOAT_ISAREF_1(ISVREF(profiler,(SI_Long)3L),
		  (SI_Long)0L);
	  clock_tick_time = DFLOAT_ISAREF_1(ISVREF(profiler,(SI_Long)4L),
		  (SI_Long)0L);
	  total_time = DFLOAT_ISAREF_1(ISVREF(profiler,(SI_Long)8L),
		  (SI_Long)0L);
	  temp = DOUBLE_FLOAT_TO_DOUBLE(display_time);
	  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(icp_time);
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(workstation_time);
	  system_time = DOUBLE_TO_DOUBLE_FLOAT(temp + temp_1 + temp_2 + 
		  idle_time + clock_tick_time);
	  name = Nil;
	  duration = Nil;
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
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
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
		      temp_3 = M_CAR(gensymed_symbol);
		      temp_4 = SIMPLE_VECTOR_P(temp_3);
		  }
		  else
		      temp_4 = TRUEP(Nil);
		  if (temp_4) {
		      temp_3 = M_CDR(gensymed_symbol);
		      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_3) ? T : Nil;
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
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
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
	  x = M_CDR(ab_entry_cons_);
	  name = ISVREF(x,(SI_Long)1L);
	  duration = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(x,
		  (SI_Long)4L),(SI_Long)0L));
	  if ( !NUMBERP(name)) {
	      temp_1 = DOUBLE_FLOAT_TO_DOUBLE(system_time);
	      temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
	      system_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      if (member_eql(name,Display_profiling_names)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(display_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  display_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else if (member_eql(name,Scheduling_profiling_names)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(scheduling_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  scheduling_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else if (member_eql(name,Data_service_profiling_names)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(data_service_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  data_service_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else if (EQ(name,Qcontinuation_task_for_current_backup) || 
		      EQ(name,Qcontinue_current_kb_save_or_backup) || 
		      EQ(name,Qterminate_kb_save_or_backup) || EQ(name,
		      Qsys_proc_read_kb)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(kb_io_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  kb_io_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else if (member_eql(name,Icp_profiling_names)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(icp_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  icp_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else if (member_eql(name,Workstation_profiling_names)) {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(workstation_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  workstation_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	      else {
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(overhead_time);
		  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(duration);
		  overhead_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	      }
	  }
	  goto next_loop;
	end_loop_3:
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,idle_time);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,clock_tick_time);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(icp_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(workstation_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(display_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(scheduling_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(data_service_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(kb_io_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(overhead_time);
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  temp_2 = DOUBLE_FLOAT_TO_DOUBLE(system_time);
	  aref_new_value = total_time - temp_2;
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	  g2_list_insert_at_end(2,new_float,system_data);
	  amf_available_array_cons_qm = 
		  ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	  if (amf_available_array_cons_qm) {
	      amf_array = M_CAR(amf_available_array_cons_qm);
	      temp_5 = Vector_of_simple_float_array_pools;
	      temp_6 = M_CDR(amf_available_array_cons_qm);
	      SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	      inline_note_reclaim_cons(amf_available_array_cons_qm,
		      Qfloat_array);
	      if (ISVREF(Available_float_array_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_5) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	      }
	      else {
		  temp_5 = Available_float_array_conses_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		  temp_5 = Available_float_array_conses_tail_vector;
		  temp_6 = Current_thread_index;
		  SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	  DFLOAT_ISASET_1(new_float,(SI_Long)0L,total_time);
	  g2_list_insert_at_end(2,new_float,system_data);
	POP_SPECIAL();
    }
    else {
	i = (SI_Long)0L;
	ab_loop_bind_ = item_count;
	g2_list_insert_at_end(2,FIX((SI_Long)0L),system_data);
      next_loop_4:
	if (i > ab_loop_bind_)
	    goto end_loop_4;
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_5 = Vector_of_simple_float_array_pools;
	    temp_6 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_5,FIX((SI_Long)1L)) = temp_6;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_5 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_5) = amf_available_array_cons_qm;
		temp_5 = Available_float_array_conses_tail_vector;
		temp_6 = Current_thread_index;
		SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
	    }
	    else {
		temp_5 = Available_float_array_conses_vector;
		temp_6 = Current_thread_index;
		SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
		temp_5 = Available_float_array_conses_tail_vector;
		temp_6 = Current_thread_index;
		SVREF(temp_5,temp_6) = amf_available_array_cons_qm;
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
	g2_list_insert_at_end(2,new_float,system_data);
	i = i + (SI_Long)1L;
	goto next_loop_4;
      end_loop_4:;
    }
    if (restart_qm)
	g2_enable_system_profiling();
    return VALUES_1(system_data);
}

/* G2-PROCEDURE-DETAIL */
Object g2_procedure_detail(item)
    Object item;
{
    Object procedure_data, profiler, profiled_data;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double execution_time, aref_new_value;

    x_note_fn_call(142,93);
    procedure_data = make_transient_item(Qquantity_list);
    profiler = Profiling_structure;
    profiled_data = Nil;
    execution_time = 0.0;
    if (profiler)
	profiled_data = find_profiled_data_given_item(item);
    if (profiler && profiled_data) {
	execution_time = DFLOAT_ISAREF_1(ISVREF(profiled_data,(SI_Long)4L),
		(SI_Long)0L);
	g2_list_insert_at_end(2,ISVREF(profiled_data,(SI_Long)5L),
		procedure_data);
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,execution_time);
	g2_list_insert_at_end(2,new_float,procedure_data);
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
	aref_new_value = FIXNUM_EQ(ISVREF(profiled_data,(SI_Long)5L),
		FIX((SI_Long)0L)) ? 0.0 : execution_time / 
		(double)IFIX(ISVREF(profiled_data,(SI_Long)5L));
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	g2_list_insert_at_end(2,new_float,procedure_data);
    }
    else {
	g2_list_insert_at_end(2,FIX((SI_Long)0L),procedure_data);
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
	g2_list_insert_at_end(2,new_float,procedure_data);
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
	g2_list_insert_at_end(2,new_float,procedure_data);
    }
    return VALUES_1(procedure_data);
}

DEFINE_VARIABLE_WITH_SYMBOL(Registered_activities_symbol_array, Qregistered_activities_symbol_array);

/* CREATE-REGISTERED-ACTIVITIES-SYMBOL-ARRAY */
Object create_registered_activities_symbol_array()
{
    Object svref_arg_1, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,94);
    Registered_activities_symbol_array = make_array(1,
	    length(Registered_activities_array));
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Registered_activities_array));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    svref_arg_1 = Registered_activities_symbol_array;
    svref_new_value = intern(nstring_upcase(1,substitute(3,CHR('-'),
	    CHR(' '),aref1(Registered_activities_array,FIX(index_1)))),_);
    ISVREF(svref_arg_1,index_1) = svref_new_value;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* ACTIVITY-INDEX-GIVEN-SYMBOL */
Object activity_index_given_symbol(activity_symbol)
    Object activity_symbol;
{
    Object matched_index;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,95);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(Registered_activities_symbol_array));
    matched_index = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (matched_index)
	goto end_loop;
    if (EQ(activity_symbol,ISVREF(Registered_activities_symbol_array,index_1)))
	matched_index = FIX(index_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(matched_index);
    return VALUES_1(Qnil);
}

/* FIND-PROFILED-DATA-GIVEN-ITEM */
Object find_profiled_data_given_item(item)
    Object item;
{
    Object profiled_data, scope_conses, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, x, ab_less_than_branch_qm_;
    Object gensymed_symbol, temp, gensymed_symbol_1;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(142,96);
    profiled_data = Nil;
    scope_conses = Scope_conses;
    ab_hash_table_ = ISVREF(Profiling_structure,(SI_Long)1L);
    ab_table_length_ = (SI_Long)0L;
    ab_index_ = (SI_Long)0L;
    ab_tree_form_ = Nil;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_skip_list_p_ = Nil;
    ab_tail_node_ = Nil;
    x = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      x = M_CDR(ab_entry_cons_);
      if (profiled_data)
	  goto end_loop_3;
      if (EQ(ISVREF(x,(SI_Long)2L),item)) {
	  gensymed_symbol = ISVREF(x,(SI_Long)3L);
	  gensymed_symbol_1 = ISVREF(item,(SI_Long)3L);
	  temp_1 = FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ?
		   FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
		  TRUEP(Nil)) : FIXNUMP(gensymed_symbol_1) ? TRUEP(Nil) : 
		  FIXNUM_EQ(M_CAR(gensymed_symbol),
		  M_CAR(gensymed_symbol_1)) && 
		  FIXNUM_EQ(M_CDR(gensymed_symbol),M_CDR(gensymed_symbol_1));
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  profiled_data = x;
      goto next_loop;
    end_loop_3:;
    POP_SPECIAL();
    return VALUES_1(profiled_data);
}

static Object Qsymbol_list;        /* symbol-list */

/* G2-PROCEDURE-ACTIVITY-LIST */
Object g2_procedure_activity_list(item)
    Object item;
{
    Object procedure_activities, profiler, profiled_data, calls, temp, temp_1;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(142,97);
    procedure_activities = make_transient_item(Qsymbol_list);
    profiler = Profiling_structure;
    profiled_data = Nil;
    if (profiler) {
	profiled_data = find_profiled_data_given_item(item);
	if (profiled_data) {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length(Registered_activities_array));
	    calls = ISVREF(profiled_data,(SI_Long)6L);
	  next_loop:
	    if (index_1 >= ab_loop_bind_)
		goto end_loop;
	    temp = ISVREF(calls,index_1);
	    temp_1 = FIX((SI_Long)0L);
	    if (NUM_GT(temp,temp_1))
		g2_list_insert_at_end(2,
			ISVREF(Registered_activities_symbol_array,index_1),
			procedure_activities);
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
    }
    return VALUES_1(procedure_activities);
}

DEFINE_VARIABLE_WITH_SYMBOL(Limit_profiling_based_on_licence_level_p, Qlimit_profiling_based_on_licence_level_p);

/* G2-ALLOW-PROFILING-REGARDLESS-OF-LICENSE */
Object g2_allow_profiling_regardless_of_license()
{
    x_note_fn_call(142,98);
    Limit_profiling_based_on_licence_level_p = Nil;
    return VALUES_1(Limit_profiling_based_on_licence_level_p);
}

/* G2-USER-NAME-FOR-FRAME */
Object g2_user_name_for_frame(a_frame)
    Object a_frame;
{
    Object designation, name_for_user;

    x_note_fn_call(142,99);
    designation = Nil;
    name_for_user = Nil;
    designation = get_or_make_up_designation_for_block(a_frame);
    if (SYMBOLP(designation))
	name_for_user = designation;
    else
	name_for_user = copy_as_wide_string(designation);
    return VALUES_1(name_for_user);
}

static Object string_constant_10;  /* "Attempt to invoke unlicensed system procedure." */

/* G2-PROCEDURE-ACTIVITY-CALLS */
Object g2_procedure_activity_calls(item,activity_symbol)
    Object item, activity_symbol;
{
    Object code, top_of_stack, message_1, profiler, activity_calls;
    Object profiled_data, index_1, calls, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float;
    char temp;
    double aref_new_value;

    x_note_fn_call(142,100);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp ? TRUEP(Limit_profiling_based_on_licence_level_p) : TRUEP(Nil)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    profiler = Profiling_structure;
    activity_calls = make_transient_item(Qquantity_list);
    profiled_data = Nil;
    index_1 = Nil;
    calls = Nil;
    if (profiler) {
	profiled_data = find_profiled_data_given_item(item);
	if (profiled_data)
	    index_1 = activity_index_given_symbol(activity_symbol);
	if (index_1) {
	    calls = lfloat(ISVREF(ISVREF(profiled_data,(SI_Long)6L),
		    IFIX(index_1)),_);
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
	    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(calls);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    g2_list_insert_at_end(2,new_float,activity_calls);
	}
    }
    if ( !TRUEP(calls)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	g2_list_insert_at_end(2,new_float,activity_calls);
    }
    return VALUES_1(activity_calls);
}

/* G2-SYSTEM-PROFILED-ITEMS */
Object g2_system_profiled_items()
{
    Object code, top_of_stack, message_1, system_data, profiler, table;
    Object scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, x, name, ab_less_than_branch_qm_;
    Object gensymed_symbol, temp_1, gensymed_symbol_1, old_entry;
    SI_Long ab_table_length_, ab_index_, gensymed_symbol_2, temp_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(142,101);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp ? TRUEP(Limit_profiling_based_on_licence_level_p) : TRUEP(Nil)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    system_data = make_transient_item(Qg2_list);
    profiler = Profiling_structure;
    table = Nil;
    if (profiler) {
	table = ISVREF(profiler,(SI_Long)1L);
	scope_conses = Scope_conses;
	ab_hash_table_ = table;
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	x = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  name = Nil;
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
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
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
		      ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
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
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
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
	  x = M_CDR(ab_entry_cons_);
	  name = ISVREF(x,(SI_Long)1L);
	  if ( !SYMBOLP(name) && IFIX(ISVREF(x,(SI_Long)5L)) > (SI_Long)0L) {
	      gensymed_symbol = ISVREF(ISVREF(x,(SI_Long)2L),(SI_Long)3L);
	      gensymed_symbol_1 = ISVREF(x,(SI_Long)3L);
	      if (FIXNUMP(gensymed_symbol) ? (FIXNUMP(gensymed_symbol_1) ? 
		      FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
		      TRUEP(Nil)) : FIXNUMP(gensymed_symbol_1) ? 
		      TRUEP(Nil) : FIXNUM_EQ(M_CAR(gensymed_symbol),
		      M_CAR(gensymed_symbol_1)) && 
		      FIXNUM_EQ(M_CDR(gensymed_symbol),
		      M_CDR(gensymed_symbol_1)))
		  g2_list_insert_at_end(2,ISVREF(x,(SI_Long)2L),system_data);
	      else {
		  gensymed_symbol = ISVREF(x,(SI_Long)2L);
		  gensymed_symbol_2 = SYMBOLP(gensymed_symbol) ? 
			  SXHASH_SYMBOL_1(gensymed_symbol) & 
			  IFIX(Most_positive_fixnum) : 
			  IFIX(frame_hash_function(gensymed_symbol));
		  temp_1 = table;
		  temp_2 = gensymed_symbol_2 % (SI_Long)43L;
		  result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),
			  gensymed_symbol,SVREF(temp_1,FIX(temp_2)),
			  FIX((SI_Long)31L),FIX(gensymed_symbol_2));
		  old_entry = NTH_VALUE((SI_Long)1L, result);
		  if (old_entry)
		      reclaim_basic_profiling_structure(old_entry);
	      }
	  }
	  goto next_loop;
	end_loop_3:;
	POP_SPECIAL();
    }
    return VALUES_1(system_data);
}

/* G2-ENABLE-SYSTEM-PROFILING */
Object g2_enable_system_profiling()
{
    Object code, top_of_stack, message_1, aref_arg_1;
    char temp;
    double current_time;

    x_note_fn_call(142,102);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp ? TRUEP(Limit_profiling_based_on_licence_level_p) : TRUEP(Nil)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !TRUEP(Profiling_enabled_qm)) {
	current_time = g2ext_unix_time_as_float();
	if ( !TRUEP(Profiling_structure))
	    Profiling_structure = make_global_profiling_structure_1();
	aref_arg_1 = ISVREF(Profiling_structure,(SI_Long)7L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	aref_arg_1 = ISVREF(Profiling_structure,(SI_Long)2L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_time);
	Profiling_enabled_qm = Profiling_structure;
	return VALUES_1(Profiling_enabled_qm);
    }
    else
	return VALUES_1(Nil);
}

/* EXIT-CURRENT-PROFILING-CONTEXT */
Object exit_current_profiling_context(current_time)
    Object current_time;
{
    Object aref_arg_1;
    double incf_arg, aref_new_value;

    x_note_fn_call(142,103);
    if (Profiling_enabled_qm && Current_profile_structure_qm) {
	aref_arg_1 = ISVREF(Current_profile_structure_qm,(SI_Long)4L);
	incf_arg = DFLOAT_ISAREF_1(current_time,(SI_Long)0L) - 
		DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)2L),
		(SI_Long)0L);
	aref_new_value = DFLOAT_ISAREF_1(aref_arg_1,(SI_Long)0L) + incf_arg;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	aref_arg_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	aref_new_value = DFLOAT_ISAREF_1(current_time,(SI_Long)0L);
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	Current_profile_structure_qm = Nil;
    }
    return VALUES_1(Nil);
}

/* G2-DISABLE-SYSTEM-PROFILING */
Object g2_disable_system_profiling()
{
    Object code, top_of_stack, message_1, amf_available_array_cons_qm;
    Object amf_array, temp_1, temp_2, amf_result, new_float, current_time;
    char temp;
    double aref_new_value;

    x_note_fn_call(142,104);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp ? TRUEP(Limit_profiling_based_on_licence_level_p) : TRUEP(Nil)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (Profiling_enabled_qm) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	aref_new_value = g2ext_unix_time_as_float();
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	current_time = new_float;
	temp_1 = ISVREF(Profiling_structure,(SI_Long)8L);
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(Profiling_structure,
		(SI_Long)8L),(SI_Long)0L) + (DFLOAT_ISAREF_1(current_time,
		(SI_Long)0L) - DFLOAT_ISAREF_1(ISVREF(Profiling_structure,
		(SI_Long)7L),(SI_Long)0L));
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	exit_current_profiling_context(current_time);
	temp_1 = ISVREF(Profiling_structure,(SI_Long)7L);
	DFLOAT_ISASET_1(temp_1,(SI_Long)0L,0.0);
	Profiling_enabled_qm = Nil;
	reclaim_managed_simple_float_array_of_length_1(current_time);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-TOGGLE-SYSTEM-PROFILING */
Object g2_toggle_system_profiling()
{
    x_note_fn_call(142,105);
    if (Profiling_enabled_qm)
	return g2_disable_system_profiling();
    else
	return g2_enable_system_profiling();
}

/* G2-CLEAR-PROFILING */
Object g2_clear_profiling()
{
    Object code, top_of_stack, message_1;
    char temp;

    x_note_fn_call(142,106);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp ? TRUEP(Limit_profiling_based_on_licence_level_p) : TRUEP(Nil)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_10);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return g2_clear_profiling_inner();
}

/* G2-CLEAR-PROFILING-INNER */
Object g2_clear_profiling_inner()
{
    x_note_fn_call(142,107);
    if (Profiling_structure)
	return clear_global_profiling_structure(Profiling_structure);
    else
	return VALUES_1(Nil);
}

/* FIND-OR-CREATE-PROFILING-STRUCTURE */
Object find_or_create_profiling_structure(thing_to_profile,hash_table)
    Object thing_to_profile, hash_table;
{
    Object temp_1, skip_list, key_value, marked, pred, curr, succ, reference;
    Object temp_2, entry_hash, profiling_structure_qm, gensymed_symbol_1;
    Object gensymed_symbol_2, old_entry, frame_serial_number_setf_arg, old;
    Object new_1, svref_new_value;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    char temp_3;
    Object result;

    x_note_fn_call(142,108);
    gensymed_symbol = SYMBOLP(thing_to_profile) ? 
	    SXHASH_SYMBOL_1(thing_to_profile) & IFIX(Most_positive_fixnum) 
	    : IFIX(frame_hash_function(thing_to_profile));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(hash_table,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = thing_to_profile;
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    profiling_structure_qm = IFIX(ISVREF(curr,(SI_Long)1L)) == 
	    key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
	    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
    if (profiling_structure_qm &&  !SYMBOLP(thing_to_profile)) {
	gensymed_symbol_1 = ISVREF(thing_to_profile,(SI_Long)3L);
	gensymed_symbol_2 = ISVREF(profiling_structure_qm,(SI_Long)3L);
	temp_3 =  !(FIXNUMP(gensymed_symbol_1) ? 
		(FIXNUMP(gensymed_symbol_2) ? FIXNUM_EQ(gensymed_symbol_1,
		gensymed_symbol_2) : TRUEP(Nil)) : 
		FIXNUMP(gensymed_symbol_2) ? TRUEP(Nil) : 
		FIXNUM_EQ(M_CAR(gensymed_symbol_1),
		M_CAR(gensymed_symbol_2)) && 
		FIXNUM_EQ(M_CDR(gensymed_symbol_1),M_CDR(gensymed_symbol_2)));
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	gensymed_symbol = SYMBOLP(profiling_structure_qm) ? 
		SXHASH_SYMBOL_1(profiling_structure_qm) & 
		IFIX(Most_positive_fixnum) : 
		IFIX(frame_hash_function(profiling_structure_qm));
	temp_1 = profiling_structure_qm;
	temp = gensymed_symbol % (SI_Long)43L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp_1,
		SVREF(hash_table,FIX(temp)),FIX((SI_Long)31L),
		FIX(gensymed_symbol));
	old_entry = NTH_VALUE((SI_Long)1L, result);
	if (old_entry)
	    reclaim_basic_profiling_structure(old_entry);
	profiling_structure_qm = Nil;
    }
    if ( !TRUEP(profiling_structure_qm)) {
	profiling_structure_qm = make_basic_profiling_structure();
	if ( !SYMBOLP(thing_to_profile)) {
	    frame_serial_number_setf_arg = ISVREF(thing_to_profile,
		    (SI_Long)3L);
	    old = ISVREF(profiling_structure_qm,(SI_Long)3L);
	    new_1 = frame_serial_number_setf_arg;
	    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		    (FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		    frame_serial_number_setf_helper_1(old,new_1);
	    SVREF(profiling_structure_qm,FIX((SI_Long)3L)) = svref_new_value;
	}
	svref_new_value = SYMBOLP(thing_to_profile) ? thing_to_profile : 
		copy_frame_serial_number(ISVREF(thing_to_profile,(SI_Long)3L));
	SVREF(profiling_structure_qm,FIX((SI_Long)1L)) = svref_new_value;
	SVREF(profiling_structure_qm,FIX((SI_Long)2L)) = thing_to_profile;
	gensymed_symbol = SYMBOLP(thing_to_profile) ? 
		SXHASH_SYMBOL_1(thing_to_profile) & 
		IFIX(Most_positive_fixnum) : 
		IFIX(frame_hash_function(thing_to_profile));
	temp = gensymed_symbol % (SI_Long)43L;
	set_skip_list_entry(SVREF(hash_table,FIX(temp)),FIX((SI_Long)31L),
		Qeq,Fp_mutate_call_hash_tree_for_hash_skip_list_entry,T,
		thing_to_profile,FIX(gensymed_symbol),profiling_structure_qm);
    }
    return VALUES_1(profiling_structure_qm);
}

/* INCREMENT-PROFILING-CALLS */
Object increment_profiling_calls(item_to_profile)
    Object item_to_profile;
{
    Object call_hash_table, profiling_structure, svref_arg_1, svref_new_value;
    Declare_special(1);

    x_note_fn_call(142,109);
    call_hash_table = ISVREF(Profiling_enabled_qm,(SI_Long)1L);
    profiling_structure = 
	    find_or_create_profiling_structure(item_to_profile,
	    call_hash_table);
    PUSH_SPECIAL_WITH_SYMBOL(Profiling_structure,Qprofiling_structure,profiling_structure,
	    0);
      svref_arg_1 = Profiling_structure;
      svref_new_value = FIXNUM_ADD1(ISVREF(Profiling_structure,(SI_Long)5L));
      SVREF(svref_arg_1,FIX((SI_Long)5L)) = svref_new_value;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* NOTE-POSSIBLY-PROFILED-ITEM-DELETION */
Object note_possibly_profiled_item_deletion(item)
    Object item;
{
    Object call_hash, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, old_entry;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(142,110);
    call_hash = ISVREF(Profiling_structure,(SI_Long)1L);
    gensymed_symbol = SYMBOLP(item) ? SXHASH_SYMBOL_1(item) & 
	    IFIX(Most_positive_fixnum) : IFIX(frame_hash_function(item));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(call_hash,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = item;
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    if (IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? (EQ(key_value,
	    ISVREF(curr,(SI_Long)2L)) ? TRUEP(ISVREF(curr,(SI_Long)3L)) : 
	    TRUEP(Nil)) : TRUEP(Nil)) {
	gensymed_symbol = SYMBOLP(item) ? SXHASH_SYMBOL_1(item) & 
		IFIX(Most_positive_fixnum) : IFIX(frame_hash_function(item));
	temp = gensymed_symbol % (SI_Long)43L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),item,
		SVREF(call_hash,FIX(temp)),FIX((SI_Long)31L),
		FIX(gensymed_symbol));
	old_entry = NTH_VALUE((SI_Long)1L, result);
	if (old_entry)
	    reclaim_basic_profiling_structure(old_entry);
    }
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* POSIT-PROFILING-STRUCTURE */
Object posit_profiling_structure(item)
    Object item;
{
    Object thing_to_profile, x2, gensymed_symbol, sub_class_bit_vector;
    Object call_hash_table, amf_available_array_cons_qm, amf_array, temp_1;
    Object temp_2, amf_result, new_float, current_time;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    double aref_new_value;

    x_note_fn_call(142,111);
    if (item &&  !TRUEP(code_body_invocation_qm(item))) {
	if (SYMBOLP(item))
	    thing_to_profile = item;
	else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_schedule_task_g2_struct))
	    thing_to_profile = ISVREF(item,(SI_Long)7L);
	else if (is_a_formula_invocation_qm(item))
	    thing_to_profile = item_to_profile_of_formula_invocation(item);
	else if (SIMPLE_VECTOR_P(item) && EQ(ISVREF(item,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct))
	    thing_to_profile = ISVREF(item,(SI_Long)8L);
	else {
	    if (SIMPLE_VECTOR_P(item) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) > (SI_Long)2L && 
		     !EQ(ISVREF(item,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(item,(SI_Long)1L);
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
			IFIX(ISVREF(Block_class_description,(SI_Long)18L));
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
		thing_to_profile = item;
	    else
		thing_to_profile = Qnil;
	}
	if (thing_to_profile) {
	    call_hash_table = ISVREF(Profiling_enabled_qm,(SI_Long)1L);
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
	    aref_new_value = g2ext_unix_time_as_float();
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    current_time = new_float;
	    exit_current_profiling_context(current_time);
	    Current_profile_structure_qm = 
		    find_or_create_profiling_structure(thing_to_profile,
		    call_hash_table);
	    temp_1 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	    aref_new_value = DFLOAT_ISAREF_1(current_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    reclaim_managed_simple_float_array_of_length_1(current_time);
	}
    }
    return VALUES_1(Nil);
}

static Object string_constant_11;  /* "Save is already in progress." */

static Object array_constant_2;    /* # */

static Object Qin_progress;        /* in-progress */

static Object list_constant_30;    /* # */

static Object Qfile_progress_display;  /* file-progress-display */

static Object Qinclude_required_modules;  /* include-required-modules */

static Object Qusing_clear_text;   /* using-clear-text */

static Object Qemitting_c_code;    /* emitting-c-code */

static Object Qlog_message_for_commit_after_saving;  /* log-message-for-commit-after-saving */

static Object Qfile_command;       /* file-command */

static Object Qincluding_all_required_modules;  /* including-all-required-modules */

static Object Qcommit_after_saving;  /* commit-after-saving */

static Object Qsave_module;        /* save-module */

static Object Qfailed;             /* failed */

static Object Qread_only;          /* read-only */

static Object string_constant_12;  /* "Terminating save" */

static Object Qnever_opened;       /* never-opened */

static Object Qab_continue;        /* continue */

static Object Qok;                 /* ok */

/* G2-SAVE-MODULE-EXTENDED */
Object g2_save_module_extended(pathname_string,module_name,g2_window_qm,
	    options)
    Object pathname_string, module_name, g2_window_qm, options;
{
    Object temp, evaluation_value, display_qm, include_required_qm;
    Object using_clear_text_qm, emitting_c_code_qm, thing;
    Object log_message_for_commit_after_saving_qm, file_command;
    Object attempting_save_via_system_procedure_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector, g2_window_for_save_via_system_procedure_qm;
    Object evaluation_error_text_string, gensymed_symbol_4, option_list;
    Object read_only_modules_qm, car_arg, car_new_value, file_progress;
    Object ab_loop_list_, ab_loop_it_, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(142,112);
    if (Current_saving_context_qm) {
	notify_user(1,string_constant_11);
	temp = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)28L));
	return VALUES_2(Qin_progress,temp);
    }
    if (Current_computation_instance)
	install_procedure_invocation_completion_form_function(procedure_invocation_of_code_body_function(Current_computation_instance),
		list_constant_30);
    evaluation_value = estructure_slot(options,Qfile_progress_display,Nil);
    display_qm = CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value) ? (EQ(M_CAR(estructure_slot(options,
	    Qfile_progress_display,Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qinclude_required_modules,Nil);
    include_required_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qinclude_required_modules,
	    Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qusing_clear_text,Nil);
    using_clear_text_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qusing_clear_text,Nil)),
	    Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qemitting_c_code,Nil);
    emitting_c_code_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qemitting_c_code,Nil)),
	    Truth) ? T : Nil) : Nil;
    thing = estructure_slot(options,Qlog_message_for_commit_after_saving,Nil);
    log_message_for_commit_after_saving_qm = 
	    INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
	    copy_text_string(thing) : thing;
    Return_from_save_to_caller_for_continuation_qm = T;
    Kb_save_termination_reason_qm = Nil;
    Suppress_notification_for_kb_save_qm =  !TRUEP(display_qm) ? T : Nil;
    update_terminate_kb_save_stream_error_message(Nil);
    file_command = make_command_frame(1,Qfile_command);
    attempting_save_via_system_procedure_qm = T;
    if (SIMPLE_VECTOR_P(g2_window_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window_qm)) > (SI_Long)2L && 
	     !EQ(ISVREF(g2_window_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window_qm,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    }
    else
	temp_1 = TRUEP(Nil);
    g2_window_for_save_via_system_procedure_qm = temp_1 ? g2_window_qm : Nil;
    evaluation_error_text_string = Nil;
    gensymed_symbol = make_slot_value_list_1(FIX((SI_Long)8L));
    gensymed_symbol_4 = gensymed_symbol;
    M_CAR(gensymed_symbol_4) = Qincluding_all_required_modules;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = include_required_qm;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = Qusing_clear_text;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = using_clear_text_qm;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = Qemitting_c_code;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = emitting_c_code_qm;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = Qcommit_after_saving;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = log_message_for_commit_after_saving_qm;
    option_list = gensymed_symbol;
    read_only_modules_qm = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2_window_for_save_via_system_procedure_qm,Qg2_window_for_save_via_system_procedure_qm,g2_window_for_save_via_system_procedure_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Attempting_save_via_system_procedure_qm,Qattempting_save_via_system_procedure_qm,attempting_save_via_system_procedure_qm,
	      0);
	car_arg = ISVREF(file_command,(SI_Long)16L);
	car_new_value = slot_value_list_3(slot_value_list_2(Qsave_module,
		module_name),pathname_string,option_list);
	M_CAR(car_arg) = car_new_value;
	Kb_save_termination_reason_qm = Qfailed;
	execute_file_command(file_command);
	delete_frame(file_command);
	if (Current_saving_context_qm) {
	    file_progress = Nil;
	    ab_loop_list_ = ISVREF(Current_saving_context_qm,(SI_Long)8L);
	    ab_loop_it_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    file_progress = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQ(ISVREF(file_progress,(SI_Long)26L),
		    Qread_only) ? T : Nil;
	    if (ab_loop_it_) {
		read_only_modules_qm = ab_loop_it_;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    read_only_modules_qm = Qnil;
	  end_1:;
	}
	else
	    read_only_modules_qm = Nil;
	if (Current_saving_context_qm && 
		EQ(ISVREF(Current_saving_context_qm,(SI_Long)9L),T)) {
	    notify_user_at_console(1,string_constant_12);
	    temp = Current_saving_context_qm;
	    temp_2 = Kb_save_termination_reason_qm;
	    terminate_kb_save_or_backup(temp,temp_2,
		    copy_text_string(Terminate_kb_save_stream_error_message_qm));
	}
	if (Current_saving_context_qm &&  
		!EQ(ISVREF(Current_saving_context_qm,(SI_Long)9L),
		Qnever_opened))
	    Save_kb_state_for_system_procedure_save = Qab_continue;
	temp = Terminate_kb_save_stream_error_message_qm;
	if (temp);
	else
	    temp = copy_constant_wide_string_given_length(array_constant_1,
		    FIX((SI_Long)0L));
	evaluation_error_text_string = temp;
	Terminate_kb_save_stream_error_message_qm = Nil;
	temp = Kb_save_termination_reason_qm;
	if (temp);
	else
	    temp = read_only_modules_qm ? Qread_only : Qnil;
	if (temp);
	else
	    temp = Qok;
	result = VALUES_2(temp,evaluation_error_text_string);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(G2_save_module_flag, Qg2_save_module_flag);

/* SET-G2-SAVE-MODULE-FLAG */
Object set_g2_save_module_flag()
{
    x_note_fn_call(142,113);
    G2_save_module_flag = T;
    return VALUES_1(G2_save_module_flag);
}

/* RESET-G2-SAVE-MODULE-FLAG */
Object reset_g2_save_module_flag()
{
    x_note_fn_call(142,114);
    G2_save_module_flag = Nil;
    return VALUES_1(G2_save_module_flag);
}

/* IS-G2-SAVE-MODULE-FLAG-SET */
Object is_g2_save_module_flag_set()
{
    x_note_fn_call(142,115);
    return VALUES_1(G2_save_module_flag);
}

/* G2-SAVE-MODULE */
Object g2_save_module(pathname_string,file_progress_display_qm,
	    g2_window_qm,module_name,include_required_modules_qm)
    Object pathname_string, file_progress_display_qm, g2_window_qm;
    Object module_name, include_required_modules_qm;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, options;
    Object status_symbol, error_text_qm;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;
    Object result;

    x_note_fn_call(142,116);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)4L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qfile_progress_display;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qfile_progress_display;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = file_progress_display_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = file_progress_display_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qinclude_required_modules;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qinclude_required_modules;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = include_required_modules_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = include_required_modules_qm;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    options = eval_cons_1(gensymed_symbol,Qab_structure);
    result = g2_save_module_extended(pathname_string,module_name,
	    g2_window_qm,options);
    MVS_2(result,status_symbol,error_text_qm);
    reclaim_evaluation_value(options);
    return VALUES_2(status_symbol,error_text_qm);
}

/* IS-EMPTY-PAGE */
Object is_empty_page(page)
    Object page;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,117);
    gensymed_symbol = ACCESS_ONCE(ISVREF(page,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
    if (temp)
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:;
    return VALUES_1(T);
}

/* G2-RECLAIM-SAVE-MODULE-MEMORY */
Object g2_reclaim_save_module_memory()
{
    Object id, ab_loop_list_, page, ab_loop_list__1, gensymed_symbol;
    Object ab_queue_form_, ab_next_queue_element_, block, sub_class_bit_vector;
    Object temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,118);
    provide_current_logbook();
    id = Nil;
    ab_loop_list_ = G2_save_module_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    id = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    page = Nil;
    ab_loop_list__1 = ISVREF(Current_logbook_qm,(SI_Long)20L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    page = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    gensymed_symbol = ACCESS_ONCE(ISVREF(page,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop_2:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop_2;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
	    (SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
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
	temp_1 = ISVREF(block,(SI_Long)20L);
	temp = EQL(temp_1,id);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	delete_frame(block);
    goto next_loop_2;
  end_loop_2:;
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    page = Nil;
    ab_loop_list_ = ISVREF(Current_logbook_qm,(SI_Long)20L);
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    page = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (is_empty_page(page))
	delete_frame(page);
    goto next_loop_3;
  end_loop_3:;
    reclaim_gensym_list_1(G2_save_module_list);
    G2_save_module_list = Nil;
    return VALUES_1(G2_save_module_list);
}

static Object Qsave_kb;            /* save-kb */

static Object Qkb_save;            /* kb-save */

static Object Qsave_kb_with_runtime_data;  /* save-kb-with-runtime-data */

static Object Qkb_save_with_runtime_data;  /* kb-save-with-runtime-data */

static Object string_constant_13;  /* "The symbol ~a is not a valid argument for SAVE-KB." */

/* G2-SAVE-KB */
Object g2_save_kb(pathname_string,type_of_file,file_progress_display_qm,
	    g2_window_qm)
    Object pathname_string, type_of_file, file_progress_display_qm;
    Object g2_window_qm;
{
    Object temp, display_qm, file_command;
    Object attempting_save_via_system_procedure_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector, g2_window_for_save_via_system_procedure_qm;
    Object evaluation_error_text_string, car_arg, car_new_value, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(2);
    Object result;

    x_note_fn_call(142,119);
    if (Current_saving_context_qm) {
	notify_user(1,string_constant_11);
	temp = copy_constant_wide_string_given_length(array_constant_2,
		FIX((SI_Long)28L));
	return VALUES_2(Qin_progress,temp);
    }
    if (EQ(type_of_file,Qsave_kb))
	type_of_file = Qkb_save;
    else if (EQ(type_of_file,Qsave_kb_with_runtime_data))
	type_of_file = Qkb_save_with_runtime_data;
    else {
	temp = tformat_text_string(2,string_constant_13,type_of_file);
	return VALUES_2(Qfailed,temp);
    }
    if (Current_computation_instance)
	install_procedure_invocation_completion_form_function(procedure_invocation_of_code_body_function(Current_computation_instance),
		list_constant_30);
    display_qm = CONSP(file_progress_display_qm) && 
	    EQ(M_CDR(file_progress_display_qm),Qtruth_value) ? 
	    (EQ(M_CAR(file_progress_display_qm),Truth) ? T : Nil) : Qnil;
    if ( !(EQ(file_progress_display_qm,Evaluation_true_value) || 
	    EQ(file_progress_display_qm,Evaluation_false_value)))
	reclaim_eval_cons_1(file_progress_display_qm);
    Return_from_save_to_caller_for_continuation_qm = T;
    Kb_save_termination_reason_qm = Nil;
    Suppress_notification_for_kb_save_qm =  !TRUEP(display_qm) ? T : Nil;
    update_terminate_kb_save_stream_error_message(Nil);
    file_command = make_command_frame(1,Qfile_command);
    attempting_save_via_system_procedure_qm = T;
    if (SIMPLE_VECTOR_P(g2_window_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window_qm)) > (SI_Long)2L && 
	     !EQ(ISVREF(g2_window_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window_qm,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    }
    else
	temp_1 = TRUEP(Nil);
    g2_window_for_save_via_system_procedure_qm = temp_1 ? g2_window_qm : Nil;
    evaluation_error_text_string = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(G2_window_for_save_via_system_procedure_qm,Qg2_window_for_save_via_system_procedure_qm,g2_window_for_save_via_system_procedure_qm,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Attempting_save_via_system_procedure_qm,Qattempting_save_via_system_procedure_qm,attempting_save_via_system_procedure_qm,
	      0);
	car_arg = ISVREF(file_command,(SI_Long)16L);
	car_new_value = slot_value_list_2(type_of_file,pathname_string);
	M_CAR(car_arg) = car_new_value;
	Kb_save_termination_reason_qm = Qfailed;
	execute_file_command(file_command);
	delete_frame(file_command);
	if (Current_saving_context_qm && 
		EQ(ISVREF(Current_saving_context_qm,(SI_Long)9L),T)) {
	    temp = Current_saving_context_qm;
	    temp_2 = Kb_save_termination_reason_qm;
	    terminate_kb_save_or_backup(temp,temp_2,
		    copy_text_string(Terminate_kb_save_stream_error_message_qm));
	}
	if (Current_saving_context_qm &&  
		!EQ(ISVREF(Current_saving_context_qm,(SI_Long)9L),
		Qnever_opened))
	    Save_kb_state_for_system_procedure_save = Qab_continue;
	temp = Terminate_kb_save_stream_error_message_qm;
	if (temp);
	else
	    temp = copy_constant_wide_string_given_length(array_constant_1,
		    FIX((SI_Long)0L));
	evaluation_error_text_string = temp;
	Terminate_kb_save_stream_error_message_qm = Nil;
	temp = Kb_save_termination_reason_qm;
	if (temp);
	else
	    temp = Qok;
	result = VALUES_2(temp,evaluation_error_text_string);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qfinish;             /* finish */

static Object Qfinished;           /* finished */

/* G2-CONTINUE-SAVE-KB */
Object g2_continue_save_kb(file_progress_display_qm)
    Object file_progress_display_qm;
{
    Object finish_qm, evaluation_error_text_string, temp, temp_1;
    Object current_saving_context, enable_saving_compiled_kbs_p;
    Object current_computation_flags, write_xml_object_items_collected;
    Object total_items_in_file, current_kb_save, ab_loop_list_;
    char temp_2;
    Declare_special(6);

    x_note_fn_call(142,120);
    if ( !(EQ(file_progress_display_qm,Evaluation_true_value) || 
	    EQ(file_progress_display_qm,Evaluation_false_value)))
	reclaim_eval_cons_1(file_progress_display_qm);
    finish_qm = T;
    evaluation_error_text_string = Nil;
    if (Current_saving_context_qm) {
	continue_current_kb_save_or_backup(Current_saving_context_qm);
	if (Current_saving_context_qm && ISVREF(Current_saving_context_qm,
		(SI_Long)9L)) {
	    temp = Current_saving_context_qm;
	    temp_1 = Kb_save_termination_reason_qm;
	    terminate_kb_save_or_backup(temp,temp_1,
		    copy_text_string(Terminate_kb_save_stream_error_message_qm));
	}
	temp = Kb_save_termination_reason_qm;
	if (temp);
	else
	    temp =  !TRUEP(Current_saving_context_qm) ? T : Nil;
	if (temp);
	else {
	    current_saving_context = Current_saving_context_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context,Qcurrent_saving_context,current_saving_context,
		    5);
	      enable_saving_compiled_kbs_p = ISVREF(Current_saving_context,
		      (SI_Long)10L);
	      PUSH_SPECIAL_WITH_SYMBOL(Enable_saving_compiled_kbs_p,Qenable_saving_compiled_kbs_p,enable_saving_compiled_kbs_p,
		      4);
		current_computation_flags = Current_computation_flags;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
			3);
		  write_xml_object_items_collected = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Write_xml_object_items_collected,Qwrite_xml_object_items_collected,write_xml_object_items_collected,
			  2);
		    total_items_in_file = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Total_items_in_file,Qtotal_items_in_file,total_items_in_file,
			    1);
		      Current_computation_flags = 
			      FIX(IFIX(Current_computation_flags) &  
			      ~(SI_Long)2048L);
		      Current_computation_flags = 
			      FIX(IFIX(Current_computation_flags) &  
			      ~(SI_Long)4096L);
		      current_kb_save = Nil;
		      ab_loop_list_ = ISVREF(Current_saving_context,
			      (SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_kb_save,Qcurrent_kb_save,current_kb_save,
			      0);
		      next_loop:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop;
			Current_kb_save = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if (ISVREF(Current_saving_context,(SI_Long)6L) || 
				ISVREF(Current_kb_save,(SI_Long)39L)) {
			    temp_2 = TRUEP(T);
			    POP_SPECIAL();
			    POP_SPECIAL();
			    POP_SPECIAL();
			    POP_SPECIAL();
			    POP_SPECIAL();
			    POP_SPECIAL();
			    goto end_over;
			}
			goto next_loop;
		      end_loop:;
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_2 = TRUEP(Nil);
	  end_over:
	    temp =  !temp_2 ? T : Nil;
	}
	finish_qm = temp;
	Save_kb_state_for_system_procedure_save = finish_qm ? Qfinish : 
		Qab_continue;
    }
    temp = Terminate_kb_save_stream_error_message_qm;
    if (temp);
    else
	temp = copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)0L));
    evaluation_error_text_string = temp;
    Terminate_kb_save_stream_error_message_qm = Nil;
    if (Kb_save_termination_reason_qm)
	temp = Kb_save_termination_reason_qm;
    else if (finish_qm)
	temp = Qfinished;
    else
	temp = Qab_continue;
    return VALUES_2(temp,evaluation_error_text_string);
}

/* G2-FINISH-SAVE-KB */
Object g2_finish_save_kb(file_progress_display_qm)
    Object file_progress_display_qm;
{
    Object evaluation_error_text_string, temp, temp_1;

    x_note_fn_call(142,121);
    if ( !(EQ(file_progress_display_qm,Evaluation_true_value) || 
	    EQ(file_progress_display_qm,Evaluation_false_value)))
	reclaim_eval_cons_1(file_progress_display_qm);
    evaluation_error_text_string = Nil;
    if (Current_saving_context_qm) {
	finish_current_kb_save_or_backup(Current_saving_context_qm);
	if (Current_saving_context_qm && ISVREF(Current_saving_context_qm,
		(SI_Long)9L)) {
	    temp = Current_saving_context_qm;
	    temp_1 = Kb_save_termination_reason_qm;
	    terminate_kb_save_or_backup(temp,temp_1,
		    copy_text_string(Terminate_kb_save_stream_error_message_qm));
	}
	Save_kb_state_for_system_procedure_save = Nil;
    }
    temp = Terminate_kb_save_stream_error_message_qm;
    if (temp);
    else
	temp = copy_constant_wide_string_given_length(array_constant_1,
		FIX((SI_Long)0L));
    evaluation_error_text_string = temp;
    Terminate_kb_save_stream_error_message_qm = Nil;
    temp = Kb_save_termination_reason_qm;
    if (temp);
    else
	temp = Qok;
    return VALUES_2(temp,evaluation_error_text_string);
}

/* G2-SAVE-KB-WITHOUT-OTHER-PROCESSING */
Object g2_save_kb_without_other_processing(pathname_string,type_of_file,
	    file_progress_display_qm,g2_window_qm)
    Object pathname_string, type_of_file, file_progress_display_qm;
    Object g2_window_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(142,122);
    result = g2_save_kb(pathname_string,type_of_file,
	    file_progress_display_qm,g2_window_qm);
    MVS_2(result,gensymed_symbol,gensymed_symbol_1);
    if ( !EQ(gensymed_symbol,Qok))
	return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    else {
	system_pause(0);
	result = g2_continue_save_kb(Evaluation_true_value);
	MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	system_resume();
	if (EQ(gensymed_symbol,Qfinished))
	    return g2_finish_save_kb(Evaluation_true_value);
	else
	    return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    }
}

/* G2-SAVE-MODULE-EXTENDED-WITHOUT-OTHER-PROCESSING */
Object g2_save_module_extended_without_other_processing(pathname_string,
	    module_name,g2_window_qm,options)
    Object pathname_string, module_name, g2_window_qm, options;
{
    Object gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(142,123);
    result = g2_save_module_extended(pathname_string,module_name,
	    g2_window_qm,options);
    MVS_2(result,gensymed_symbol,gensymed_symbol_1);
    if ( !EQ(gensymed_symbol,Qok))
	return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    else {
	system_pause(0);
	result = g2_continue_save_kb(Evaluation_true_value);
	MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	system_resume();
	if (EQ(gensymed_symbol,Qfinished))
	    return g2_finish_save_kb(Evaluation_true_value);
	else
	    return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    }
}

/* G2-SAVE-MODULE-WITHOUT-OTHER-PROCESSING */
Object g2_save_module_without_other_processing(pathname_string,
	    file_progress_display_qm,g2_window_qm,module_name,
	    include_required_modules_qm)
    Object pathname_string, file_progress_display_qm, g2_window_qm;
    Object module_name, include_required_modules_qm;
{
    Object gensymed_symbol, gensymed_symbol_1;
    Object result;

    x_note_fn_call(142,124);
    result = g2_save_module(pathname_string,file_progress_display_qm,
	    g2_window_qm,module_name,include_required_modules_qm);
    MVS_2(result,gensymed_symbol,gensymed_symbol_1);
    if ( !EQ(gensymed_symbol,Qok))
	return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    else {
	system_pause(0);
	result = g2_continue_save_kb(Evaluation_true_value);
	MVS_2(result,gensymed_symbol,gensymed_symbol_1);
	system_resume();
	if (EQ(gensymed_symbol,Qfinished))
	    return g2_finish_save_kb(Evaluation_true_value);
	else
	    return VALUES_2(gensymed_symbol,gensymed_symbol_1);
    }
}

static Object Quilroot;            /* uilroot */

static Object string_constant_14;  /* "The system procedure g2-delete-module cannot be called with ~
				    *          the module set to UILROOT and delete-associated-workspaces? ~
				    *          set to TRUE because g2-delete-module will also be deleted. ~
				    *          The call should be successful when delete-associated-workspaces? ~
				    *          is set to FALSE."
				    */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

static Object string_constant_15;  /* "The system procedure g2-delete-module cannot be called to delete a module which contains the calling procedure." */

static Object Qprocedure;          /* procedure */

static Object Qg2_delete_module;   /* g2-delete-module */

static Object string_constant_16;  /* "The system procedure g2-delete-module cannot be called with ~
				    *                the module set to ~A and delete-associated-workspaces? ~
				    *                set to TRUE because g2-delete-module will also be deleted. ~
				    *                The call should be successful when delete-associated-workspaces? ~
				    *                is set to FALSE."
				    */

static Object string_constant_17;  /* "Cannot call g2-delete-module to delete module ~a with ~
				    *                delete-associated-workspaces? set to TRUE because ~
				    *                a procedure in the calling chain, ~a, is in ~a. ~
				    *                The call should be successful when ~
				    *                delete-associated-workspaces? is set to FALSE."
				    */

/* G2-DELETE-MODULE */
Object g2_delete_module(module_as_evaluation_value,
	    also_delete_associated_workspaces_qm_boolean_as_evaluation_value)
    Object module_as_evaluation_value;
    Object also_delete_associated_workspaces_qm_boolean_as_evaluation_value;
{
    Object module, also_delete_associated_workspaces_qm_boolean;
    Object deleting_associated_workspaces_qm, top_of_stack, message_1;
    Object procedure_of_invocation_qm, gensymed_symbol;
    Object g2_delete_module_procedure;
    Object procedure_on_calling_stack_to_be_deleted_qm;
    char also_delete_associated_workspaces_qm, temp;

    x_note_fn_call(142,125);
    module = module_as_evaluation_value;
    also_delete_associated_workspaces_qm_boolean = 
	    M_CAR(also_delete_associated_workspaces_qm_boolean_as_evaluation_value);
    also_delete_associated_workspaces_qm = 
	    FIXNUM_EQ(also_delete_associated_workspaces_qm_boolean,Truth);
    deleting_associated_workspaces_qm = 
	    also_delete_associated_workspaces_qm ? T : Nil;
    if (EQ(module,Quilroot) && deleting_associated_workspaces_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_14);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    procedure_of_invocation_qm = 
	    find_procedure_invocation_in_module(Current_computation_instance,
	    module);
    if (deleting_associated_workspaces_qm && Current_computation_instance 
	    && code_body_invocation_qm(Current_computation_instance) && 
	    procedure_of_invocation_qm) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(procedure_of_invocation_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	temp = EQ(module,get_lookup_slot_value(gensymed_symbol,
		Qmodule_this_is_part_of_qm));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_15);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    g2_delete_module_procedure = get_instance_with_name_if_any(Qprocedure,
	    Qg2_delete_module);
    procedure_on_calling_stack_to_be_deleted_qm = 
	    find_calling_procedure_invocation_in_module(g2_delete_module_procedure,
	    module);
    if (procedure_on_calling_stack_to_be_deleted_qm) {
	if (EQ(procedure_on_calling_stack_to_be_deleted_qm,
		g2_delete_module_procedure)) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_16,module);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(4,
		    string_constant_17,module,
		    procedure_on_calling_stack_to_be_deleted_qm,module);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    do_deletion_of_module_after_confirmation(module,
	    deleting_associated_workspaces_qm);
    if ( 
	    !(EQ(also_delete_associated_workspaces_qm_boolean_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(also_delete_associated_workspaces_qm_boolean_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(also_delete_associated_workspaces_qm_boolean_as_evaluation_value);
    return VALUES_0();
}

static Object Qmodule_name_in_use;  /* module-name-in-use */

static Object string_constant_18;  /* "the name is already in use." */

static Object Qmodule_name_is_reserved_word;  /* module-name-is-reserved-word */

static Object string_constant_19;  /* "the name is a reserved word." */

static Object Qmodule_name_unspecified;  /* module-name-unspecified */

static Object string_constant_20;  /* "a module's name cannot be unspecified unless it's the top-level module" */

static Object string_constant_21;  /* "reason unknown." */

static Object string_constant_22;  /* "Creation of module with name ~a failed; ~a" */

/* G2-CREATE-MODULE */
Object g2_create_module(module_as_evaluation_value)
    Object module_as_evaluation_value;
{
    Object module, result_1, top_of_stack, temp, message_1;

    x_note_fn_call(142,126);
    module = module_as_evaluation_value;
    result_1 = create_new_module(module);
    if (SYMBOLP(result_1)) {
	top_of_stack = Cached_top_of_stack;
	if (EQ(result_1,Qmodule_name_in_use))
	    temp = string_constant_18;
	else if (EQ(result_1,Qmodule_name_is_reserved_word))
	    temp = string_constant_19;
	else if (EQ(result_1,Qmodule_name_unspecified))
	    temp = string_constant_20;
	else
	    temp = string_constant_21;
	message_1 = tformat_stack_error_text_string(3,string_constant_22,
		module,temp);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_0();
}

/* G2-MODULES-WITH-UNSAVED-CHANGES */
Object g2_modules_with_unsaved_changes()
{
    Object value_1, list_1, temp;

    x_note_fn_call(142,127);
    value_1 = Nil;
    list_1 = modules_with_unsaved_changes();
    temp = copy_list_using_eval_conses_1(list_1);
    reclaim_gensym_list_1(list_1);
    value_1 = allocate_evaluation_sequence(temp);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

static Object Qresolve_conflicts_automatically;  /* resolve-conflicts-automatically */

static Object Qbring_formats_up_to_date;  /* bring-formats-up-to-date */

static Object Qupdate_before_loading;  /* update-before-loading */

/* G2-LOAD-KB-EXTENDED */
Object g2_load_kb_extended(pathname_string_as_evaluation_value,
	    options_as_evaluation_value)
    Object pathname_string_as_evaluation_value, options_as_evaluation_value;
{
    Object pathname_string, options, value_1, evaluation_value;
    Object auto_merge_case_qm, reformat_as_appropriate_qm;
    Object update_before_loading_qm, temp;
    Declare_special(1);

    x_note_fn_call(142,128);
    pathname_string = pathname_string_as_evaluation_value;
    options = IDENTITY(options_as_evaluation_value);
    value_1 = Nil;
    evaluation_value = estructure_slot(options,
	    Qresolve_conflicts_automatically,Nil);
    auto_merge_case_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,
	    Qresolve_conflicts_automatically,Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qbring_formats_up_to_date,Nil);
    reformat_as_appropriate_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qbring_formats_up_to_date,
	    Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qupdate_before_loading,Nil);
    update_before_loading_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qupdate_before_loading,Nil)),
	    Truth) ? T : Nil) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    0);
      value_1 = start_read_kb_for_system_procedure(pathname_string,T,T,
	      Reformat_as_appropriate_qm,auto_merge_case_qm,Nil,
	      update_before_loading_qm);
    POP_SPECIAL();
    reclaim_text_string(pathname_string_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* G2-LOAD-KB */
Object g2_load_kb(pathname_string_as_evaluation_value,
	    auto_merge_case_qm_truth_value_as_evaluation_value,
	    reformat_as_appropriate_qm_truth_value_as_evaluation_value)
    Object pathname_string_as_evaluation_value;
    Object auto_merge_case_qm_truth_value_as_evaluation_value;
    Object reformat_as_appropriate_qm_truth_value_as_evaluation_value;
{
    Object pathname_string, auto_merge_case_qm_truth_value;
    Object reformat_as_appropriate_qm_truth_value, value_1;
    Object reformat_as_appropriate_qm, temp;
    char auto_merge_case_qm;
    Declare_special(1);

    x_note_fn_call(142,129);
    pathname_string = pathname_string_as_evaluation_value;
    auto_merge_case_qm_truth_value = 
	    M_CAR(auto_merge_case_qm_truth_value_as_evaluation_value);
    reformat_as_appropriate_qm_truth_value = 
	    M_CAR(reformat_as_appropriate_qm_truth_value_as_evaluation_value);
    value_1 = Nil;
    auto_merge_case_qm = FIXNUM_EQ(auto_merge_case_qm_truth_value,Truth);
    reformat_as_appropriate_qm = 
	    FIXNUM_EQ(reformat_as_appropriate_qm_truth_value,Truth) ? T : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    0);
      value_1 = start_read_kb_for_system_procedure(pathname_string,T,T,
	      Reformat_as_appropriate_qm,auto_merge_case_qm ? T : Nil,Nil,Nil);
    POP_SPECIAL();
    reclaim_text_string(pathname_string_as_evaluation_value);
    if ( !(EQ(auto_merge_case_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(auto_merge_case_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(auto_merge_case_qm_truth_value_as_evaluation_value);
    if ( !(EQ(reformat_as_appropriate_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(reformat_as_appropriate_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(reformat_as_appropriate_qm_truth_value_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

Object Merge_kb_ex_options_type = UNBOUND;

/* GET-EV-BOOL */
Object get_ev_bool varargs_1(int, n)
{
    Object ev_structure, name;
    Object default_1, evaluation_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(142,130);
    INIT_ARGS_nonrelocating();
    ev_structure = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    default_1 = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    evaluation_value = estructure_slot(ev_structure,name,default_1 ? 
	    Evaluation_true_value : Evaluation_false_value);
    if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),Qtruth_value))
	return VALUES_1(EQ(M_CAR(estructure_slot(ev_structure,name,
		default_1 ? Evaluation_true_value : 
		Evaluation_false_value)),Truth) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qmerge_kb;           /* merge-kb */

static Object Qinstall_system_tables;  /* install-system-tables */

static Object Qrestore_workspaces;  /* restore-workspaces */

static Object Qpost_logbook_messages;  /* post-logbook-messages */

static Object Qshow_conflicts;     /* show-conflicts */

static Object Qdisable_ui_during_load;  /* disable-ui-during-load */

/* G2-MERGE-KB-EX */
Object g2_merge_kb_ex(pathname_string_as_evaluation_value,
	    options_as_evaluation_value)
    Object pathname_string_as_evaluation_value, options_as_evaluation_value;
{
    Object pathname_string, options, value_1, auto_merge_case_qm;
    Object reformat_as_appropriate_qm, install_system_tables_qm;
    Object do_not_update_file_progress_display_qm;
    Object do_not_restore_image_planes_qm;
    Object do_not_notify_user_during_kb_load_qm;
    Object do_not_show_conflicts_during_kb_load_qm;
    Object do_not_allow_user_interactions_during_kb_load_qm, temp;
    char clear_kb_qm;
    Declare_special(6);

    x_note_fn_call(142,131);
    pathname_string = pathname_string_as_evaluation_value;
    options = IDENTITY(options_as_evaluation_value);
    value_1 = Nil;
    check_type_or_stack_error(2,options,Merge_kb_ex_options_type);
    auto_merge_case_qm = get_ev_bool(3,options,
	    Qresolve_conflicts_automatically,T);
    reformat_as_appropriate_qm = get_ev_bool(2,options,
	    Qbring_formats_up_to_date);
    clear_kb_qm =  !TRUEP(get_ev_bool(3,options,Qmerge_kb,T));
    install_system_tables_qm = get_ev_bool(2,options,Qinstall_system_tables);
    do_not_update_file_progress_display_qm =  !TRUEP(get_ev_bool(3,options,
	    Qfile_progress_display,T)) ? T : Nil;
    do_not_restore_image_planes_qm =  !TRUEP(get_ev_bool(3,options,
	    Qrestore_workspaces,T)) ? T : Nil;
    do_not_notify_user_during_kb_load_qm =  !TRUEP(get_ev_bool(3,options,
	    Qpost_logbook_messages,T)) ? T : Nil;
    do_not_show_conflicts_during_kb_load_qm =  !TRUEP(get_ev_bool(3,
	    options,Qshow_conflicts,T)) ? T : Nil;
    do_not_allow_user_interactions_during_kb_load_qm = get_ev_bool(3,
	    options,Qdisable_ui_during_load,T);
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_allow_user_interactions_during_kb_load_qm,Qdo_not_allow_user_interactions_during_kb_load_qm,do_not_allow_user_interactions_during_kb_load_qm,
	    5);
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_show_conflicts_during_kb_load_qm,Qdo_not_show_conflicts_during_kb_load_qm,do_not_show_conflicts_during_kb_load_qm,
	      4);
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_notify_user_during_kb_load_qm,Qdo_not_notify_user_during_kb_load_qm,do_not_notify_user_during_kb_load_qm,
		3);
	  PUSH_SPECIAL_WITH_SYMBOL(Do_not_restore_image_planes_qm,Qdo_not_restore_image_planes_qm,do_not_restore_image_planes_qm,
		  2);
	    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_file_progress_display_qm,Qdo_not_update_file_progress_display_qm,do_not_update_file_progress_display_qm,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
		      0);
		value_1 = 
			start_read_kb_for_system_procedure(pathname_string,
			clear_kb_qm ? T : Nil,install_system_tables_qm,
			Reformat_as_appropriate_qm,auto_merge_case_qm,Nil,Nil);
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_text_string(pathname_string_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* G2-MERGE-KB-EXTENDED */
Object g2_merge_kb_extended(pathname_string_as_evaluation_value,
	    options_as_evaluation_value)
    Object pathname_string_as_evaluation_value, options_as_evaluation_value;
{
    Object pathname_string, options, value_1, evaluation_value;
    Object auto_merge_case_qm, reformat_as_appropriate_qm;
    Object install_system_tables_qm, update_before_loading_qm, temp;
    char clear_kb_qm;
    Declare_special(1);

    x_note_fn_call(142,132);
    pathname_string = pathname_string_as_evaluation_value;
    options = IDENTITY(options_as_evaluation_value);
    value_1 = Nil;
    evaluation_value = estructure_slot(options,
	    Qresolve_conflicts_automatically,Nil);
    auto_merge_case_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,
	    Qresolve_conflicts_automatically,Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qbring_formats_up_to_date,Nil);
    reformat_as_appropriate_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qbring_formats_up_to_date,
	    Nil)),Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qmerge_kb,Nil);
    clear_kb_qm =  !(CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qtruth_value) ? EQ(M_CAR(estructure_slot(options,Qmerge_kb,
	    Nil)),Truth) : TRUEP(Nil));
    evaluation_value = estructure_slot(options,Qinstall_system_tables,Nil);
    install_system_tables_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qinstall_system_tables,Nil)),
	    Truth) ? T : Nil) : Nil;
    evaluation_value = estructure_slot(options,Qupdate_before_loading,Nil);
    update_before_loading_qm = CONSP(evaluation_value) && 
	    EQ(M_CDR(evaluation_value),Qtruth_value) ? 
	    (EQ(M_CAR(estructure_slot(options,Qupdate_before_loading,Nil)),
	    Truth) ? T : Nil) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    0);
      value_1 = start_read_kb_for_system_procedure(pathname_string,
	      clear_kb_qm ? T : Nil,install_system_tables_qm,
	      Reformat_as_appropriate_qm,auto_merge_case_qm,Nil,
	      update_before_loading_qm);
    POP_SPECIAL();
    reclaim_text_string(pathname_string_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* G2-MERGE-KB */
Object g2_merge_kb(pathname_string_as_evaluation_value,
	    auto_merge_case_qm_truth_value_as_evaluation_value,
	    reformat_as_appropriate_qm_truth_value_as_evaluation_value,
	    clear_kb_qm_truth_value_as_evaluation_value,
	    install_system_tables_qm_truth_value_as_evaluation_value)
    Object pathname_string_as_evaluation_value;
    Object auto_merge_case_qm_truth_value_as_evaluation_value;
    Object reformat_as_appropriate_qm_truth_value_as_evaluation_value;
    Object clear_kb_qm_truth_value_as_evaluation_value;
    Object install_system_tables_qm_truth_value_as_evaluation_value;
{
    Object pathname_string, auto_merge_case_qm_truth_value;
    Object reformat_as_appropriate_qm_truth_value, clear_kb_qm_truth_value;
    Object install_system_tables_qm_truth_value, value_1;
    Object reformat_as_appropriate_qm, temp;
    char auto_merge_case_qm, clear_kb_qm, install_system_tables_qm;
    Declare_special(1);

    x_note_fn_call(142,133);
    pathname_string = pathname_string_as_evaluation_value;
    auto_merge_case_qm_truth_value = 
	    M_CAR(auto_merge_case_qm_truth_value_as_evaluation_value);
    reformat_as_appropriate_qm_truth_value = 
	    M_CAR(reformat_as_appropriate_qm_truth_value_as_evaluation_value);
    clear_kb_qm_truth_value = 
	    M_CAR(clear_kb_qm_truth_value_as_evaluation_value);
    install_system_tables_qm_truth_value = 
	    M_CAR(install_system_tables_qm_truth_value_as_evaluation_value);
    value_1 = Nil;
    auto_merge_case_qm = FIXNUM_EQ(auto_merge_case_qm_truth_value,Truth);
    reformat_as_appropriate_qm = 
	    FIXNUM_EQ(reformat_as_appropriate_qm_truth_value,Truth) ? T : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Reformat_as_appropriate_qm,Qreformat_as_appropriate_qm,reformat_as_appropriate_qm,
	    0);
      clear_kb_qm = FIXNUM_EQ(clear_kb_qm_truth_value,Truth);
      install_system_tables_qm = 
	      FIXNUM_EQ(install_system_tables_qm_truth_value,Truth);
      value_1 = start_read_kb_for_system_procedure(pathname_string,
	      clear_kb_qm ? T : Nil,install_system_tables_qm ? T : Nil,
	      Reformat_as_appropriate_qm,auto_merge_case_qm ? T : Nil,Nil,Nil);
    POP_SPECIAL();
    reclaim_text_string(pathname_string_as_evaluation_value);
    if ( !(EQ(auto_merge_case_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(auto_merge_case_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(auto_merge_case_qm_truth_value_as_evaluation_value);
    if ( !(EQ(reformat_as_appropriate_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(reformat_as_appropriate_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(reformat_as_appropriate_qm_truth_value_as_evaluation_value);
    if ( !(EQ(clear_kb_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(clear_kb_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(clear_kb_qm_truth_value_as_evaluation_value);
    if ( !(EQ(install_system_tables_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(install_system_tables_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(install_system_tables_qm_truth_value_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

static Object Qwarmboot_afterwards_with_catch_up;  /* warmboot-afterwards-with-catch-up */

static Object Qwarmboot_afterwards;  /* warmboot-afterwards */

/* G2-WARMBOOT-KB */
Object g2_warmboot_kb(pathname_string_as_evaluation_value,
	    catch_up_qm_truth_value_as_evaluation_value)
    Object pathname_string_as_evaluation_value;
    Object catch_up_qm_truth_value_as_evaluation_value;
{
    Object pathname_string, catch_up_qm_truth_value, value_1, temp;
    char catch_up_qm;

    x_note_fn_call(142,134);
    pathname_string = pathname_string_as_evaluation_value;
    catch_up_qm_truth_value = 
	    M_CAR(catch_up_qm_truth_value_as_evaluation_value);
    value_1 = Nil;
    catch_up_qm = FIXNUM_EQ(catch_up_qm_truth_value,Truth);
    value_1 = start_read_kb_for_system_procedure(pathname_string,T,T,Nil,
	    Nil,catch_up_qm ? Qwarmboot_afterwards_with_catch_up : 
	    Qwarmboot_afterwards,Nil);
    reclaim_text_string(pathname_string_as_evaluation_value);
    if ( !(EQ(catch_up_qm_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(catch_up_qm_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(catch_up_qm_truth_value_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* G2-LOAD-RUNTIME-DATA */
Object g2_load_runtime_data(pathname_string_as_evaluation_value,
	    option_as_evaluation_value)
    Object pathname_string_as_evaluation_value, option_as_evaluation_value;
{
    Object pathname_string, option, value_1, temp;

    x_note_fn_call(142,135);
    pathname_string = pathname_string_as_evaluation_value;
    option = IDENTITY(option_as_evaluation_value);
    value_1 = Nil;
    value_1 = start_read_kb_for_system_procedure(pathname_string,T,T,Nil,
	    Nil,Qwarmboot_afterwards,Nil);
    reclaim_text_string(pathname_string_as_evaluation_value);
    IDENTITY(option_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* START-READ-KB-FOR-SYSTEM-PROCEDURE */
Object start_read_kb_for_system_procedure(pathname_string,clear_kb_qm,
	    install_system_tables_qm,bring_formats_up_to_date_qm,
	    resolve_conflicts_automatically_qm,
	    what_to_do_after_loading_kb_qm,update_before_loading_qm)
    Object pathname_string, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object what_to_do_after_loading_kb_qm, update_before_loading_qm;
{
    Object truename_qm, client_qm, structure_being_reclaimed, temp;
    Object svref_arg_2, def_structure_schedule_task_variable, svref_new_value;
    Object new_task, gensymed_symbol, gensymed_symbol_1, kb_serial_number;
    Object temp_1;
    Declare_special(1);

    x_note_fn_call(142,136);
    truename_qm = probe_for_kb_named_by_text_string(pathname_string);
    client_qm = get_current_workstation_or_ui_client_interface_if_any();
    if (truename_qm) {
	if (clear_kb_qm) {
	    if (Nil) {
		if (EQ(Nil,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(Nil,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(Nil);
		inline_note_reclaim_cons(Nil,Nil);
		structure_being_reclaimed = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(Nil,(SI_Long)9L));
		  SVREF(Nil,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(Nil,FIX((SI_Long)0L)) = temp;
		temp = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
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
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    new_task = def_structure_schedule_task_variable;
	    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	    SVREF(new_task,FIX((SI_Long)7L)) = Qsys_proc_read_kb;
	    temp = SYMBOL_FUNCTION(Qsys_proc_read_kb);
	    SVREF(new_task,FIX((SI_Long)8L)) = temp;
	    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)2L);
	    SVREF(new_task,FIX((SI_Long)13L)) = truename_qm;
	    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)12L));
	    gensymed_symbol_1 = gensymed_symbol;
	    M_CAR(gensymed_symbol_1) = clear_kb_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = install_system_tables_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = bring_formats_up_to_date_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = resolve_conflicts_automatically_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = what_to_do_after_loading_kb_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = update_before_loading_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    M_CAR(gensymed_symbol_1) = client_qm;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = Do_not_update_file_progress_display_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = Do_not_restore_image_planes_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = Do_not_notify_user_during_kb_load_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = Do_not_show_conflicts_during_kb_load_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    temp = Do_not_allow_user_interactions_during_kb_load_qm;
	    M_CAR(gensymed_symbol_1) = temp;
	    SVREF(new_task,FIX((SI_Long)14L)) = gensymed_symbol;
	    temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	    SVREF(new_task,FIX((SI_Long)11L)) = temp;
	    temp = 
		    constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		    (SI_Long)0L),new_task);
	    SVREF(new_task,FIX((SI_Long)6L)) = temp;
	    system_pause(0);
	    return VALUES_1(Truth);
	}
	else {
	    system_pause(0);
	    kb_serial_number = Current_kb_serial_number;
	    temp_1 = read_kb_or_group_thereof(truename_qm,clear_kb_qm,
		    install_system_tables_qm,bring_formats_up_to_date_qm,
		    resolve_conflicts_automatically_qm,
		    what_to_do_after_loading_kb_qm,
		    update_before_loading_qm,client_qm) ? Truth : Falsity;
	    reclaim_gensym_pathname(truename_qm);
	    if ( !FIXNUM_GT(Current_kb_serial_number,kb_serial_number))
		system_resume();
	    return VALUES_1(temp_1);
	}
    }
    else
	return VALUES_1(Falsity);
}

/* SYS-PROC-READ-KB */
Object sys_proc_read_kb(gensym_pathname_1,gensym_list_of_read_kb_args)
    Object gensym_pathname_1, gensym_list_of_read_kb_args;
{
    Object gensymed_symbol, clear_kb_qm, install_system_tables_qm;
    Object bring_formats_up_to_date_qm, resolve_conflicts_automatically_qm;
    Object what_to_do_after_loading_kb_qm, update_before_loading_qm, client_qm;
    Object do_not_update_file_progress_display_qm;
    Object do_not_restore_image_planes_qm;
    Object do_not_notify_user_during_kb_load_qm;
    Object do_not_show_conflicts_during_kb_load_qm;
    Object do_not_allow_user_interactions_during_kb_load_qm, temp;
    Declare_special(5);

    x_note_fn_call(142,137);
    gensymed_symbol = gensym_list_of_read_kb_args;
    clear_kb_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    install_system_tables_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    bring_formats_up_to_date_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    resolve_conflicts_automatically_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    what_to_do_after_loading_kb_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    update_before_loading_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    client_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    do_not_update_file_progress_display_qm = CAR(gensymed_symbol);
    PUSH_SPECIAL_WITH_SYMBOL(Do_not_update_file_progress_display_qm,Qdo_not_update_file_progress_display_qm,do_not_update_file_progress_display_qm,
	    4);
      gensymed_symbol = CDR(gensymed_symbol);
      do_not_restore_image_planes_qm = CAR(gensymed_symbol);
      PUSH_SPECIAL_WITH_SYMBOL(Do_not_restore_image_planes_qm,Qdo_not_restore_image_planes_qm,do_not_restore_image_planes_qm,
	      3);
	gensymed_symbol = CDR(gensymed_symbol);
	do_not_notify_user_during_kb_load_qm = CAR(gensymed_symbol);
	PUSH_SPECIAL_WITH_SYMBOL(Do_not_notify_user_during_kb_load_qm,Qdo_not_notify_user_during_kb_load_qm,do_not_notify_user_during_kb_load_qm,
		2);
	  gensymed_symbol = CDR(gensymed_symbol);
	  do_not_show_conflicts_during_kb_load_qm = CAR(gensymed_symbol);
	  PUSH_SPECIAL_WITH_SYMBOL(Do_not_show_conflicts_during_kb_load_qm,Qdo_not_show_conflicts_during_kb_load_qm,do_not_show_conflicts_during_kb_load_qm,
		  1);
	    gensymed_symbol = CDR(gensymed_symbol);
	    do_not_allow_user_interactions_during_kb_load_qm = 
		    CAR(gensymed_symbol);
	    PUSH_SPECIAL_WITH_SYMBOL(Do_not_allow_user_interactions_during_kb_load_qm,Qdo_not_allow_user_interactions_during_kb_load_qm,do_not_allow_user_interactions_during_kb_load_qm,
		    0);
	      temp = read_kb_or_group_thereof(gensym_pathname_1,
		      clear_kb_qm,install_system_tables_qm,
		      bring_formats_up_to_date_qm,
		      resolve_conflicts_automatically_qm,
		      what_to_do_after_loading_kb_qm,
		      update_before_loading_qm,client_qm);
	      reclaim_gensym_pathname(gensym_pathname_1);
	      reclaim_gensym_list_1(gensym_list_of_read_kb_args);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(temp);
}

/* G2-GET-CONNECTION-VERTICES */
Object g2_get_connection_vertices(item,connection,integer_list)
    Object item, connection, integer_list;
{
    x_note_fn_call(142,138);
    check_args_for_get_connection_vertices(item,connection,
	    Cached_top_of_stack);
    if (get_connection_vertices_backward_compatibility_p())
	return get_connection_vertices_original(item,connection,integer_list);
    else
	return get_connection_vertices_accurately(connection,integer_list);
}

/* GET-CONNECTION-VERTICES-ORIGINAL */
Object get_connection_vertices_original(item,connection,integer_list)
    Object item, connection, integer_list;
{
    Object connection_structure, dont_include_offset_for_end_position_qm;
    Object connection_deltas;
    char from_output_item_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(142,139);
    connection_structure = ISVREF(connection,(SI_Long)21L);
    dont_include_offset_for_end_position_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Dont_include_offset_for_end_position_qm,Qdont_include_offset_for_end_position_qm,dont_include_offset_for_end_position_qm,
	    0);
      connection_deltas = 
	      add_missing_deltas_to_connection(connection_structure);
      from_output_item_qm = EQ(ISVREF(connection_structure,(SI_Long)2L),item);
      put_connection_deltas_into_integer_list(connection_structure,
	      connection_deltas,integer_list,from_output_item_qm ? T : Nil);
      remove_redundant_deltas_from_connection(connection_structure);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qloose_end;          /* loose-end */

/* GET-CONNECTION-VERTICES-ACCURATELY */
Object get_connection_vertices_accurately(connection,integer_list)
    Object connection, integer_list;
{
    Object connection_structure, connection_deltas, deltas_added_qm, frame;
    Object symbol, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,140);
    connection_structure = ISVREF(connection,(SI_Long)21L);
    connection_deltas = ISVREF(connection_structure,(SI_Long)6L);
    deltas_added_qm = Nil;
    if ( !TRUEP(connection_deltas)) {
	frame = ISVREF(connection_structure,(SI_Long)2L);
	symbol = Qloose_end;
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(symbol,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
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
	if (temp);
	else {
	    frame = ISVREF(connection_structure,(SI_Long)3L);
	    symbol = Qloose_end;
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(symbol,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
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
		    temp = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	add_missing_deltas_to_connection(connection_structure);
	deltas_added_qm = T;
    }
    else if ( ! !TRUEP(connection_deltas) && ATOM(connection_deltas)) {
	add_missing_deltas_to_connection(connection_structure);
	remove_last_delta_from_connection(connection_structure);
	deltas_added_qm = T;
    }
    connection_deltas = ISVREF(connection_structure,(SI_Long)6L);
    integer_list = 
	    put_connection_deltas_into_integer_list(connection_structure,
	    connection_deltas,integer_list,Nil);
    if (deltas_added_qm)
	remove_last_delta_from_connection(connection_structure);
    if (LISTP(integer_list))
	return VALUES_1(integer_list);
    else
	return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object Qleft;               /* left */

static Object Qright;              /* right */

static Object Qtop;                /* top */

static Object Qbottom;             /* bottom */

/* PUT-CONNECTION-DELTAS-INTO-INTEGER-LIST */
Object put_connection_deltas_into_integer_list(connection,
	    connection_deltas,integer_list,starting_at_output_qm)
    Object connection, connection_deltas, integer_list, starting_at_output_qm;
{
    Object reclaim_deltas_on_exit_qm, gensymed_symbol, input_end_object;
    Object input_end_position, input_end_side, gensymed_symbol_1;
    Object output_end_object, output_end_position, output_end_side, delta;
    Object ab_loop_list_, delta_count, delta_count_minus_1, value_to_insert;
    Object a_delta, ab_loop_list__1, last_value, next_to_last_value;
    Object ab_loop_iter_flag_, omit_last_two_values_qm, direction_multiplier;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, item_count, count_1;

    x_note_fn_call(142,141);
    if ( !LISTP(integer_list))
	clear_g2_list(integer_list);
    if (connection_deltas) {
	reclaim_deltas_on_exit_qm = Nil;
	if (ATOM(connection_deltas)) {
	    connection_deltas = slot_value_cons_1(connection_deltas,Nil);
	    reclaim_deltas_on_exit_qm = T;
	}
	gensymed_symbol = connection;
	input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
	input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
	input_end_side = ISVREF(array_constant_3,IFIX(input_end_position) 
		& (SI_Long)3L);
	input_end_position_on_side = IFIX(input_end_position) >>  -  - 
		(SI_Long)2L;
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	if (EQ(input_end_side,Qleft))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(input_end_side,Qright)) {
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = input_end_position_on_side;
	input_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	if (EQ(input_end_side,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(input_end_side,Qbottom)) {
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = input_end_position_on_side;
	input_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
	output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
	output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
	output_end_side = ISVREF(array_constant_3,
		IFIX(output_end_position) & (SI_Long)3L);
	output_end_position_on_side = IFIX(output_end_position) >>  -  - 
		(SI_Long)2L;
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	if (EQ(output_end_side,Qleft))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(output_end_side,Qright)) {
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)2L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = output_end_position_on_side;
	output_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	if (EQ(output_end_side,Qtop))
	    gensymed_symbol_3 = (SI_Long)0L;
	else if (EQ(output_end_side,Qbottom)) {
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_4 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	    gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		    (SI_Long)0L : (SI_Long)1L;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	}
	else
	    gensymed_symbol_3 = output_end_position_on_side;
	output_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
	if (starting_at_output_qm) {
	    delta = Nil;
	    ab_loop_list_ = connection_deltas;
	    item_count = (SI_Long)1L;
	    delta_count = length(connection_deltas);
	    delta_count_minus_1 = FIXNUM_SUB1(delta_count);
	    value_to_insert = Nil;
	    if (FIXNUM_GT(delta_count,FIX((SI_Long)1L))) {
		a_delta = Nil;
		ab_loop_list__1 = connection_deltas;
		count_1 = (SI_Long)1L;
		last_value = Nil;
		next_to_last_value = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop;
		a_delta = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    count_1 = count_1 + (SI_Long)1L;
		if (count_1 == IFIX(delta_count_minus_1))
		    next_to_last_value = a_delta;
		else if (count_1 == IFIX(delta_count))
		    last_value = a_delta;
		ab_loop_iter_flag_ = Nil;
		goto next_loop;
	      end_loop:
		omit_last_two_values_qm = IFIX(next_to_last_value) == 
			(SI_Long)0L ? (IFIX(last_value) == (SI_Long)0L ? T 
			: Nil) : Qnil;
		goto end_1;
		omit_last_two_values_qm = Qnil;
	      end_1:;
	    }
	    else
		omit_last_two_values_qm = Nil;
	    direction_multiplier = EQ(input_end_side,Qleft) || 
		    EQ(input_end_side,Qright) ? FIX((SI_Long)1L) : 
		    FIX((SI_Long)-1L);
	    ab_loop_iter_flag_ = T;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    delta = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		item_count = item_count + (SI_Long)1L;
		direction_multiplier = FIX(IFIX(direction_multiplier) * 
			(SI_Long)-1L);
	    }
	    if ( !(omit_last_two_values_qm && (item_count == 
		    IFIX(delta_count_minus_1) || item_count == 
		    IFIX(delta_count)))) {
		value_to_insert = FIXNUM_TIMES(FIXNUM_NEGATE(delta),
			direction_multiplier);
		if (LISTP(integer_list))
		    integer_list = eval_cons_1(value_to_insert,integer_list);
		else
		    g2_list_insert_at_beginning(value_to_insert,integer_list);
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_1;
	  end_loop_1:;
	}
	else {
	    delta = Nil;
	    ab_loop_list_ = connection_deltas;
	    item_count = (SI_Long)1L;
	    delta_count = length(connection_deltas);
	    delta_count_minus_1 = FIXNUM_SUB1(delta_count);
	    if (FIXNUM_GT(delta_count,FIX((SI_Long)1L))) {
		a_delta = Nil;
		ab_loop_list__1 = connection_deltas;
		count_1 = (SI_Long)1L;
		last_value = Nil;
		next_to_last_value = Nil;
		ab_loop_iter_flag_ = T;
	      next_loop_2:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_2;
		a_delta = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    count_1 = count_1 + (SI_Long)1L;
		if (count_1 == IFIX(delta_count_minus_1))
		    next_to_last_value = a_delta;
		else if (count_1 == IFIX(delta_count))
		    last_value = a_delta;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_2;
	      end_loop_2:
		omit_last_two_values_qm = IFIX(next_to_last_value) == 
			(SI_Long)0L ? (IFIX(last_value) == (SI_Long)0L ? T 
			: Nil) : Qnil;
		goto end_2;
		omit_last_two_values_qm = Qnil;
	      end_2:;
	    }
	    else
		omit_last_two_values_qm = Nil;
	    direction_multiplier = EQ(input_end_side,Qleft) || 
		    EQ(input_end_side,Qright) ? FIX((SI_Long)1L) : 
		    FIX((SI_Long)-1L);
	    ab_loop_iter_flag_ = T;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    delta = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_iter_flag_)) {
		item_count = item_count + (SI_Long)1L;
		direction_multiplier = FIX(IFIX(direction_multiplier) * 
			(SI_Long)-1L);
	    }
	    if ( !(omit_last_two_values_qm && (item_count == 
		    IFIX(delta_count_minus_1) || item_count == 
		    IFIX(delta_count)))) {
		last_value = FIXNUM_TIMES(delta,direction_multiplier);
		if (LISTP(integer_list))
		    integer_list = nconc2(integer_list,
			    eval_cons_1(last_value,Nil));
		else
		    g2_list_insert_at_end(2,last_value,integer_list);
	    }
	    ab_loop_iter_flag_ = Nil;
	    goto next_loop_3;
	  end_loop_3:;
	}
	if (reclaim_deltas_on_exit_qm)
	    reclaim_slot_value_list_1(connection_deltas);
    }
    return VALUES_1(integer_list);
}

static Object string_constant_23;  /* "GET-CONNECTION-VERTICES" */

/* CHECK-ARGS-FOR-GET-CONNECTION-VERTICES */
Object check_args_for_get_connection_vertices(item,connection,top_of_stack)
    Object item, connection, top_of_stack;
{
    x_note_fn_call(142,142);
    return check_args_for_connection_evaluator(item,connection,
	    string_constant_23,top_of_stack);
}

static Object string_constant_24;  /* "Could not reference the ~a connected to ~NF at ~a.  ~a is not a ~a" */

static Object string_constant_25;  /* "class that can have connections." */

static Object string_constant_26;  /* "defined class." */

static Object Qinput;              /* input */

static Object Qoutput;             /* output */

/* G2-GET-ITEMS-CONNECTED-TO-PORT */
Object g2_get_items_connected_to_port(connected_item,connected_class_name,
	    port_name,connected_items_item_list)
    Object connected_item, connected_class_name, port_name;
    Object connected_items_item_list;
{
    Object class_1, class_description_qm, port, direction_qm, top_of_stack;
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, message_1, connected_items_qm;
    Object connected_item_at_port, ab_loop_list_, sub_class_bit_vector;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(142,143);
    class_1 = connected_class_name;
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    port = port_name;
    direction_qm = Nil;
    if ( !TRUEP(class_description_qm) ||  
	    !TRUEP(ISVREF(class_description_qm,(SI_Long)16L))) {
	top_of_stack = Cached_top_of_stack;
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
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
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	gensymed_symbol = resulting_value;
	message_1 = tformat_stack_error_text_string(6,string_constant_24,
		class_1,connected_item,port,class_1,gensymed_symbol && 
		ISVREF(gensymed_symbol,(SI_Long)16L) ? string_constant_25 :
		 string_constant_26);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	connected_items_qm = 
		search_for_directly_connected_entities(connected_item,
		class_1,port,Nil,Nil,Nil,Nil,Nil);
	connected_item_at_port = Nil;
	ab_loop_list_ = connected_items_qm;
      next_loop_12:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_12;
	connected_item_at_port = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(connected_item_at_port,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_2 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? TRUEP(serve_item_p(connected_item_at_port)) : 
		    TRUEP(Nil)) {
	    if (EQ(direction_qm,Nil)) {
		if (EQ(ISVREF(ISVREF(connected_item_at_port,(SI_Long)21L),
			(SI_Long)2L),connected_item))
		    direction_qm = Qinput;
		else
		    direction_qm = Qoutput;
	    }
	    g2_get_items_connected_to_port_1(connected_item_at_port,
		    class_1,port,direction_qm,connected_items_item_list);
	}
	else if (serve_item_p(connected_item_at_port))
	    g2_list_insert_at_end(2,connected_item_at_port,
		    connected_items_item_list);
	goto next_loop_12;
      end_loop_12:;
	if (connected_items_qm)
	    reclaim_eval_list_1(connected_items_qm);
    }
    return VALUES_1(Nil);
}

/* G2-GET-ITEMS-CONNECTED-TO-PORT-1 */
Object g2_get_items_connected_to_port_1(connected_item,class_1,port,
	    direction_qm,connected_items_item_list)
    Object connected_item, class_1, port, direction_qm;
    Object connected_items_item_list;
{
    Object temp_list, connected_item_at_port, ab_loop_list_;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(142,144);
    temp_list = search_for_directly_connected_entities(connected_item,
	    class_1,port,direction_qm,direction_qm,Nil,Nil,Nil);
    connected_item_at_port = Nil;
    ab_loop_list_ = temp_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connected_item_at_port = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sub_class_bit_vector = ISVREF(ISVREF(connected_item_at_port,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
    if (temp ? TRUEP(serve_item_p(connected_item_at_port)) : TRUEP(Nil))
	g2_get_items_connected_to_port_1(connected_item_at_port,class_1,
		port,direction_qm,connected_items_item_list);
    else if (serve_item_p(connected_item_at_port))
	g2_list_insert_at_end(2,connected_item_at_port,
		connected_items_item_list);
    goto next_loop;
  end_loop:
    reclaim_eval_list_1(temp_list);
    return VALUES_1(Qnil);
}

static Object Qshowing;            /* showing */

static Object Qexposed;            /* exposed */

static Object Qtransient;          /* transient */

static Object Qpermanent;          /* permanent */

/* SYSTEM-PREDICATE */
Object system_predicate(item,symbol)
    Object item, symbol;
{
    Object temp;

    x_note_fn_call(142,145);
    if (EQ(symbol,Qshowing) || EQ(symbol,Qexposed))
	temp = showing_p(item,Nil);
    else if (EQ(symbol,Qtransient))
	temp = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		(SI_Long)262144L) ? T : Nil;
    else if (EQ(symbol,Qpermanent))
	temp = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) & 
		(SI_Long)1L) ? T : Nil;
    else
	temp = Nil;
    if (temp)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

static Object string_constant_27;  /* "~a is not a valid class name." */

static Object Qobject;             /* object */

static Object Qnone;               /* none */

static Object Kfuncall;            /* :funcall */

static Object string_constant_28;  /* "Inconsistency Found. Non-simple and non-funcalled attribute initialization in user-defined attribute slot [~a] of class ~a." */

static Object Qg2_array_length;    /* g2-array-length */

static Object Qmanaged_g2_array;   /* managed-g2-array */

static Object Qab_slot_value;      /* slot-value */

/* G2-GET-ATTRIBUTES-FOR-CLASS */
Object g2_get_attributes_for_class(class_name,array_frame,
	    specific_attributes_flag)
    Object class_name, array_frame, specific_attributes_flag;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons, temp_2;
    Object temp_3, temp_4, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, top_of_stack, message_1, array_length;
    Object managed_array, attr_info_list, ab_loopvar_, attribute_name;
    Object class_or_frame, ab_loopvar__1, slot_description, defining_class;
    Object attribute_type_specification_1, slot_init_form;
    Object tail_of_slot_descriptions, ab_loopvar__2, attribute_type_generic;
    Object attribute_type_specific, empty_allowed_p, car_1, cdr_1, slot_value;
    Object slot_units, initial_type, initial_value_or_class, x, ab_loop_list_;
    Object ab_loop_iter_flag_, slot_value_pop_store, cons_1, next_cons;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_, index_1;
    SI_Long svref_arg_2;
    char temp_5, all_attributes_p;
    Object result;

    x_note_fn_call(142,146);
    if (SYMBOLP(class_name)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_name;
	key_hash_value = SXHASH_SYMBOL_1(class_name) & 
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_name;
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
		temp_2 = Available_lookup_conses_vector;
		temp_3 = Current_thread_index;
		temp_4 = M_CDR(new_cons);
		SVREF(temp_2,temp_3) = temp_4;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = Nil;
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
		temp_2 = Available_lookup_conses_vector;
		temp_3 = Current_thread_index;
		temp_4 = M_CDR(new_cons);
		SVREF(temp_2,temp_3) = temp_4;
		if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_2 = Available_lookup_conses_tail_vector;
		    temp_3 = Current_thread_index;
		    SVREF(temp_2,temp_3) = Nil;
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
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	temp_5 = TRUEP(resulting_value);
    }
    else
	temp_5 = TRUEP(Nil);
    if ( !temp_5) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_27,
		class_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    array_length = Nil;
    managed_array = Nil;
    attr_info_list = Qnil;
    all_attributes_p =  
	    !TRUEP(evaluation_truth_value_is_true_p(specific_attributes_flag));
    ab_loopvar_ = Nil;
    attribute_name = Nil;
    class_or_frame = class_name;
    ab_loopvar__1 = SYMBOLP(class_or_frame) ? 
	    lookup_global_or_kb_specific_property_value(class_or_frame,
	    Class_description_gkbprop) : ISVREF(class_or_frame,(SI_Long)1L);
    slot_description = Nil;
    defining_class = Nil;
    attribute_type_specification_1 = Nil;
    slot_init_form = Nil;
    tail_of_slot_descriptions = ISVREF(ab_loopvar__1,(SI_Long)6L);
  next_loop_12:
    if ( !TRUEP(tail_of_slot_descriptions))
	goto end_loop_12;
    if (ISVREF(M_CAR(tail_of_slot_descriptions),(SI_Long)8L))
	goto end_loop_12;
    tail_of_slot_descriptions = M_CDR(tail_of_slot_descriptions);
    goto next_loop_12;
  end_loop_12:
    ab_loopvar_ = tail_of_slot_descriptions;
  next_loop_13:
    if ( !TRUEP(ab_loopvar_))
	goto end_loop_13;
    ab_loopvar__2 = M_CAR(ab_loopvar_);
    if ( ! !TRUEP(ISVREF(ab_loopvar__2,(SI_Long)8L))) {
	temp_1 = ISVREF(ab_loopvar__2,(SI_Long)3L);
	temp_5 =  !EQ(temp_1,
		ISVREF(get_slot_description_of_class_description_function(ISVREF(ab_loopvar__2,
		(SI_Long)2L),ab_loopvar__1,Nil),(SI_Long)3L));
    }
    else
	temp_5 = TRUEP(Nil);
    attribute_name = temp_5 ? ISVREF(ab_loopvar__2,(SI_Long)1L) : 
	    ISVREF(ab_loopvar__2,(SI_Long)2L);
    ab_loopvar_ = CDR(ab_loopvar_);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_name;
    key_hash_value = SXHASH_SYMBOL_1(class_name) & IFIX(Most_positive_fixnum);
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_name;
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
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    temp_4 = M_CDR(new_cons);
	    SVREF(temp_2,temp_3) = temp_4;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
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
	    temp_2 = Available_lookup_conses_vector;
	    temp_3 = Current_thread_index;
	    temp_4 = M_CDR(new_cons);
	    SVREF(temp_2,temp_3) = temp_4;
	    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_2 = Available_lookup_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = Nil;
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
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
      next_loop_20:
	if (level < ab_loop_bind_)
	    goto end_loop_20;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_21:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_22:
	if ( !TRUEP(marked))
	    goto end_loop_21;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_22;
      end_loop_21:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
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
      next_loop_23:
	if (level < ab_loop_bind_)
	    goto end_loop_23;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_24:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_25:
	if ( !TRUEP(marked))
	    goto end_loop_24;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_25;
      end_loop_24:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    slot_description = 
	    get_slot_description_of_class_description_function(attribute_name,
	    gensymed_symbol,Nil);
    defining_class = ISVREF(slot_description,(SI_Long)3L);
    attribute_type_specification_1 = ISVREF(slot_description,(SI_Long)5L);
    slot_init_form = ISVREF(slot_description,(SI_Long)6L);
    if (all_attributes_p || EQ(defining_class,class_name)) {
	attr_info_list = slot_value_cons_1(attribute_name,attr_info_list);
	attr_info_list = slot_value_cons_1(ISVREF(slot_description,
		(SI_Long)3L),attr_info_list);
	if (symbolic_type_specification_p(attribute_type_specification_1)) {
	    temp_1 = 
		    user_type_for_symbolic_type_specification(attribute_type_specification_1);
	    result = VALUES_3(Qvalue,temp_1,Evaluation_false_value);
	}
	else if (class_type_specification_p(attribute_type_specification_1))
	    result = VALUES_3(Qobject,
		    M_CAR(M_CDR(attribute_type_specification_1)),
		    Evaluation_false_value);
	else
	    result = VALUES_3(Qitem_or_value,Qnone,Evaluation_true_value);
	MVS_3(result,attribute_type_generic,attribute_type_specific,
		empty_allowed_p);
	attr_info_list = slot_value_cons_1(attribute_type_generic,
		attr_info_list);
	attr_info_list = slot_value_cons_1(attribute_type_specific,
		attr_info_list);
	attr_info_list = slot_value_cons_1(empty_allowed_p,attr_info_list);
	if ( !TRUEP(slot_init_form))
	    result = VALUES_2(Qnone,Qnone);
	else if (SYMBOLP(slot_init_form))
	    result = VALUES_2(Qvalue,slot_init_form);
	else {
	    if (CONSP(slot_init_form)) {
		car_1 = M_CAR(slot_init_form);
		cdr_1 = M_CDR(slot_init_form);
		if (CONSP(cdr_1)) {
		    temp_1 = M_CAR(cdr_1);
		    temp_5 = SYMBOLP(temp_1);
		}
		else
		    temp_5 = TRUEP(Nil);
		temp_5 = temp_5 ? slot_value_number_p(car_1) || 
			text_string_p(car_1) || STRINGP(car_1) : TRUEP(Nil);
	    }
	    else
		temp_5 = TRUEP(Nil);
	    if (temp_5) {
		slot_value = M_CAR(slot_init_form);
		slot_units = M_CAR(M_CDR(slot_init_form));
		if (EQ(slot_units,Qnumber)) {
		    if (FIXNUMP(slot_value))
			result = VALUES_2(Qvalue,slot_value);
		    else {
			temp_1 = copy_managed_float(slot_value);
			result = VALUES_2(Qvalue,temp_1);
		    }
		}
		else if (EQ(slot_units,Qtruth_value)) {
		    if (FIXNUM_EQ(slot_value,Truth))
			temp_1 = Evaluation_true_value;
		    else if (FIXNUM_EQ(slot_value,Falsity))
			temp_1 = Evaluation_false_value;
		    else
			temp_1 = eval_cons_1(slot_value,Qtruth_value);
		    result = VALUES_2(Qvalue,temp_1);
		}
		else if (EQ(slot_units,Qtext)) {
		    temp_1 = copy_as_wide_string(slot_value);
		    result = VALUES_2(Qvalue,temp_1);
		}
		else {
		    temp_1 = FIXNUMP(slot_value) ? slot_value : 
			    copy_managed_float(slot_value);
		    result = VALUES_2(slot_units,temp_1);
		}
	    }
	    else {
		gensymed_symbol = slot_init_form;
		temp_5 = FIXNUMP(gensymed_symbol);
		if (temp_5);
		else
		    temp_5 = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_5);
		else
		    temp_5 = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_5);
		else
		    temp_5 = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			    TRUEP(Qnil);
		if (temp_5);
		else
		    temp_5 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			    != (SI_Long)0L;
		if (temp_5);
		else if (CONSP(gensymed_symbol)) {
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    temp_5 = EQ(gensymed_symbol,Qtruth_value);
		    if (temp_5);
		    else
			temp_5 = EQ(gensymed_symbol,Qiteration_state);
		    if (temp_5);
		    else if (SYMBOLP(gensymed_symbol)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol;
			key_hash_value = SXHASH_SYMBOL_1(gensymed_symbol) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_26:
			if (level < ab_loop_bind_)
			    goto end_loop_26;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_27:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_28:
			if ( !TRUEP(marked))
			    goto end_loop_27;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_28;
		      end_loop_27:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_9;
			goto next_loop_27;
		      end_loop_28:
		      end_9:
			level = level - (SI_Long)1L;
			goto next_loop_26;
		      end_loop_26:;
			temp_5 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_5 = TRUEP(Nil);
		}
		else
		    temp_5 = TRUEP(Nil);
		if (temp_5) {
		    temp_1 = FIXNUMP(slot_init_form) || slot_init_form && 
			    SYMBOLP(slot_init_form) ? slot_init_form : 
			    copy_evaluation_value_1(slot_init_form);
		    result = VALUES_2(Qvalue,temp_1);
		}
		else if ( !EQ(CAR(slot_init_form),Kfuncall)) {
		    reclaim_slot_value_list_1(attr_info_list);
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_28,attribute_name,class_name);
		    result = raw_stack_error_named_error(top_of_stack,
			    message_1);
		}
		else
		    result = VALUES_2(Qobject,CADDR(slot_init_form));
	    }
	}
	MVS_2(result,initial_type,initial_value_or_class);
	attr_info_list = slot_value_cons_1(initial_type,attr_info_list);
	attr_info_list = slot_value_cons_1(initial_value_or_class,
		attr_info_list);
	attr_info_list = slot_value_cons_1(ISVREF(slot_description,
		(SI_Long)4L),attr_info_list);
    }
    goto next_loop_13;
  end_loop_13:;
    array_length = length(attr_info_list);
    change_slot_value(3,array_frame,Qg2_array_length,array_length);
    managed_array = get_slot_value_function(array_frame,Qmanaged_g2_array,Nil);
    x = Nil;
    ab_loop_list_ = attr_info_list;
    index_1 = IFIX(FIXNUM_SUB1(array_length));
    ab_loop_iter_flag_ = T;
  next_loop_29:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_29;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 - (SI_Long)1L;
    if (index_1 < (SI_Long)0L)
	goto end_loop_29;
    temp_3 = 
	    reclaim_managed_number_or_value_function(FIXNUM_LE(ISVREF(managed_array,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(managed_array,index_1 + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
	    (SI_Long)2L),index_1 & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(managed_array,svref_arg_2) = temp_3;
    }
    else {
	temp_2 = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(temp_2,svref_arg_2) = temp_3;
    }
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	slot_value_pop_store = Nil;
	cons_1 = attr_info_list;
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_2 = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_2) = cons_1;
		temp_2 = Available_slot_value_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = cons_1;
	    }
	    else {
		temp_2 = Available_slot_value_conses_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = cons_1;
		temp_2 = Available_slot_value_conses_tail_vector;
		temp_3 = Current_thread_index;
		SVREF(temp_2,temp_3) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	attr_info_list = next_cons;
	ISVREF(managed_array,svref_arg_2) = slot_value_pop_store;
    }
    else {
	temp_2 = ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	slot_value_pop_store = Nil;
	cons_1 = attr_info_list;
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_3 = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_3) = cons_1;
		temp_3 = Available_slot_value_conses_tail_vector;
		temp_4 = Current_thread_index;
		SVREF(temp_3,temp_4) = cons_1;
	    }
	    else {
		temp_3 = Available_slot_value_conses_vector;
		temp_4 = Current_thread_index;
		SVREF(temp_3,temp_4) = cons_1;
		temp_3 = Available_slot_value_conses_tail_vector;
		temp_4 = Current_thread_index;
		SVREF(temp_3,temp_4) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	attr_info_list = next_cons;
	ISVREF(temp_2,svref_arg_2) = slot_value_pop_store;
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_29;
  end_loop_29:;
    return reclaim_slot_value_list_1(attr_info_list);
}

/* G2-GET-ENUMERATIONS-FOR-SYMBOLIC-ATTRIBUTE */
Object g2_get_enumerations_for_symbolic_attribute(class_name,
	    pretty_slot_name,symbol_list)
    Object class_name, pretty_slot_name, symbol_list;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, top_of_stack, message_1;
    Object defining_class, class_specific_attributes_of_defining_class;
    Object enumerations, attribute_description, ab_loop_list_, attribute_name;
    Object allowed_symbol;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(142,147);
    if (SYMBOLP(class_name)) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_name;
	key_hash_value = SXHASH_SYMBOL_1(class_name) & 
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
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_name;
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
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
    if ( !temp_2) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_27,
		class_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    defining_class = 
	    ISVREF(get_slot_description_of_class_description_function(pretty_slot_name,
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop),Nil),(SI_Long)3L);
    class_specific_attributes_of_defining_class = 
	    ISVREF(lookup_global_or_kb_specific_property_value(defining_class,
	    Class_definition_gkbprop),(SI_Long)22L);
    enumerations = Nil;
    attribute_description = Nil;
    ab_loop_list_ = class_specific_attributes_of_defining_class;
    attribute_name = Nil;
  next_loop_12:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_12;
    attribute_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_name = CAR(attribute_description);
    if (EQ(attribute_name,pretty_slot_name))
	goto end_loop_12;
    goto next_loop_12;
  end_loop_12:
    enumerations = CDDDDR(attribute_description);
    if (enumerations) {
	allowed_symbol = Nil;
	ab_loop_list_ = enumerations;
      next_loop_13:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_13;
	allowed_symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	g2_list_insert_at_end(2,allowed_symbol,symbol_list);
	goto next_loop_13;
      end_loop_13:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* USER-TYPE-FOR-SYMBOLIC-TYPE-SPECIFICATION */
Object user_type_for_symbolic_type_specification(symbol)
    Object symbol;
{
    x_note_fn_call(142,148);
    if (EQ(symbol,Qnumber))
	return VALUES_1(Qquantity);
    else if (EQ(symbol,Qdatum))
	return VALUES_1(Qvalue);
    else if (EQ(symbol,Qboolean))
	return VALUES_1(Qtruth_value);
    else
	return VALUES_1(symbol);
}

/* G2-FLOAT-TO-TEXT-USING-DECIMAL-FORMAT */
Object g2_float_to_text_using_decimal_format(float_arg_as_evaluation_value,
	    max_integral_size_as_evaluation_value,
	    max_fraction_size_as_evaluation_value,
	    always_format_as_exponent_p_truth_value_as_evaluation_value,
	    suppress_trailing_zeros_p_truth_value_as_evaluation_value)
    Object float_arg_as_evaluation_value;
    Object max_integral_size_as_evaluation_value;
    Object max_fraction_size_as_evaluation_value;
    Object always_format_as_exponent_p_truth_value_as_evaluation_value;
    Object suppress_trailing_zeros_p_truth_value_as_evaluation_value;
{
    Object max_integral_size, max_fraction_size;
    Object always_format_as_exponent_p_truth_value;
    Object suppress_trailing_zeros_p_truth_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object value_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char always_format_as_exponent_p, suppress_trailing_zeros_p;
    double float_arg;
    Declare_special(5);

    x_note_fn_call(142,149);
    float_arg = DFLOAT_ISAREF_1(float_arg_as_evaluation_value,(SI_Long)0L);
    max_integral_size = max_integral_size_as_evaluation_value;
    max_fraction_size = max_fraction_size_as_evaluation_value;
    always_format_as_exponent_p_truth_value = 
	    M_CAR(always_format_as_exponent_p_truth_value_as_evaluation_value);
    suppress_trailing_zeros_p_truth_value = 
	    M_CAR(suppress_trailing_zeros_p_truth_value_as_evaluation_value);
    always_format_as_exponent_p = 
	    FIXNUM_EQ(always_format_as_exponent_p_truth_value,Truth);
    suppress_trailing_zeros_p = 
	    FIXNUM_EQ(suppress_trailing_zeros_p_truth_value,Truth);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      write_floating_point_number(8,
		      DOUBLE_TO_DOUBLE_FLOAT(float_arg),max_integral_size,
		      max_fraction_size,FIX((SI_Long)16L),
		      suppress_trailing_zeros_p ? T : Nil,
		      always_format_as_exponent_p ? T : Nil,Nil,Nil);
	      value_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_managed_simple_float_array_of_length_1(float_arg_as_evaluation_value);
    if ( !(EQ(always_format_as_exponent_p_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(always_format_as_exponent_p_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(always_format_as_exponent_p_truth_value_as_evaluation_value);
    if ( !(EQ(suppress_trailing_zeros_p_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(suppress_trailing_zeros_p_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(suppress_trailing_zeros_p_truth_value_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-FLOAT-TO-TEXT */
Object g2_float_to_text(float_arg_as_evaluation_value,
	    minimum_width_as_evaluation_value,
	    precision_as_evaluation_value,
	    output_format_as_evaluation_value,
	    suppress_trailing_zeros_p_truth_value_as_evaluation_value)
    Object float_arg_as_evaluation_value, minimum_width_as_evaluation_value;
    Object precision_as_evaluation_value, output_format_as_evaluation_value;
    Object suppress_trailing_zeros_p_truth_value_as_evaluation_value;
{
    Object minimum_width, precision, output_format;
    Object suppress_trailing_zeros_p_truth_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object value_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char suppress_trailing_zeros_p;
    double float_arg;
    Declare_special(5);

    x_note_fn_call(142,150);
    float_arg = DFLOAT_ISAREF_1(float_arg_as_evaluation_value,(SI_Long)0L);
    minimum_width = minimum_width_as_evaluation_value;
    precision = precision_as_evaluation_value;
    output_format = output_format_as_evaluation_value;
    suppress_trailing_zeros_p_truth_value = 
	    M_CAR(suppress_trailing_zeros_p_truth_value_as_evaluation_value);
    suppress_trailing_zeros_p = 
	    FIXNUM_EQ(suppress_trailing_zeros_p_truth_value,Truth);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      write_floating_point_number_simple_c_format(5,
		      DOUBLE_TO_DOUBLE_FLOAT(float_arg),precision,
		      output_format,minimum_width,
		      suppress_trailing_zeros_p ? T : Nil);
	      value_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_managed_simple_float_array_of_length_1(float_arg_as_evaluation_value);
    if ( !(EQ(suppress_trailing_zeros_p_truth_value_as_evaluation_value,
	    Evaluation_true_value) || 
	    EQ(suppress_trailing_zeros_p_truth_value_as_evaluation_value,
	    Evaluation_false_value)))
	reclaim_eval_cons_1(suppress_trailing_zeros_p_truth_value_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-RUN-TRACE */
Object g2_run_trace(text_arg_as_evaluation_value)
    Object text_arg_as_evaluation_value;
{
    Object text_arg, value_1, temp;

    x_note_fn_call(142,151);
    text_arg = text_arg_as_evaluation_value;
    value_1 = Nil;
    value_1 = run_trace(text_arg) ? Truth : Falsity;
    reclaim_text_string(text_arg_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tracked_items_call_depth, Qtracked_items_call_depth);

DEFINE_VARIABLE_WITH_SYMBOL(Available_tracked_items_call_vector_table_hash_vector_43_vectors, Qavailable_tracked_items_call_vector_table_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_tracked_items_call_vector_table_hash_vector_43_vectors, Qcount_of_tracked_items_call_vector_table_hash_vector_43_vectors);

Object Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector = UNBOUND;

/* TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object tracked_items_call_vector_table_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(142,152);
    temp = Count_of_tracked_items_call_vector_table_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTORS */
Object out_tracked_items_call_vector_table_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(142,153);
    temp = 
	    FIXNUM_MINUS(Count_of_tracked_items_call_vector_table_hash_vector_43_vectors,
	    length(Available_tracked_items_call_vector_table_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_tracked_items_call_vector_table_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(142,154);
    atomic_incff_symval(Qcount_of_tracked_items_call_vector_table_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR */
Object make_tracked_items_call_vector_table_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(142,155);
    if (ISVREF(Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector,
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
		make_permanent_tracked_items_call_vector_table_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR */
Object reclaim_tracked_items_call_vector_table_hash_vector(tracked_items_call_vector_table_hash_vector_43_vector)
    Object tracked_items_call_vector_table_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(142,156);
    svref_arg_1 = 
	    Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector;
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
	    tracked_items_call_vector_table_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-TRACKED-ITEMS-CALL-VECTOR-TABLE-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_tracked_items_call_vector_table_tree_for_hash_skip_list_sentinel(hash,
	    tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(142,157);
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

/* MUTATE-TRACKED-ITEMS-CALL-VECTOR-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry(node,
	    new_key,new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(142,158);
    reclaim_if_evaluation_value_function(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry = UNBOUND;

/* CLEAR-TRACKED-ITEMS-CALL-VECTOR-TABLE-TREE */
Object clear_tracked_items_call_vector_table_tree(tracked_items_call_vector_table_tree_for_hash_skip_list)
    Object tracked_items_call_vector_table_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_entry;
    Object result;

    x_note_fn_call(142,159);
    head = 
	    M_CAR(M_CDR(tracked_items_call_vector_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(tracked_items_call_vector_table_tree_for_hash_skip_list));
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
	    tracked_items_call_vector_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_if_evaluation_value_function(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(tracked_items_call_vector_table_tree_for_hash_skip_list);
}

static Object Qtracked_items_call_vector_table_tree_for_hash;  /* tracked-items-call-vector-table-tree-for-hash */

/* MAKE-TRACKED-ITEMS-CALL-VECTOR-TABLE */
Object make_tracked_items_call_vector_table()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(142,160);
    new_vector = make_tracked_items_call_vector_table_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_tracked_items_call_vector_table_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_tracked_items_call_vector_table_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qtracked_items_call_vector_table_tree_for_hash;
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

/* FLATTEN-TRACKED-ITEMS-CALL-VECTOR-TABLE */
Object flatten_tracked_items_call_vector_table(tracked_items_call_vector_table_hash_table)
    Object tracked_items_call_vector_table_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(142,161);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(tracked_items_call_vector_table_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-TRACKED-ITEMS-CALL-VECTOR-TABLE */
Object clear_tracked_items_call_vector_table(tracked_items_call_vector_table_hash_table)
    Object tracked_items_call_vector_table_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(142,162);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_tracked_items_call_vector_table_tree(ISVREF(tracked_items_call_vector_table_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-TRACKED-ITEMS-CALL-VECTOR-TABLE */
Object reclaim_tracked_items_call_vector_table(tracked_items_call_vector_table_hash_table)
    Object tracked_items_call_vector_table_hash_table;
{
    Object tracked_items_call_vector_table_tree_for_hash_skip_list, head, tail;
    Object element_qm, key_qm, temp, old_entry, last_1, next_qm, temp_1;
    Object svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(142,163);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tracked_items_call_vector_table_tree_for_hash_skip_list = 
	    ISVREF(tracked_items_call_vector_table_hash_table,index_1);
    head = 
	    M_CAR(M_CDR(tracked_items_call_vector_table_tree_for_hash_skip_list));
    tail = 
	    M_CDR(M_CDR(tracked_items_call_vector_table_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),temp,
	    tracked_items_call_vector_table_tree_for_hash_skip_list,
	    FIX((SI_Long)31L),frame_hash_function(key_qm));
    old_entry = NTH_VALUE((SI_Long)1L, result);
    if (old_entry)
	reclaim_if_evaluation_value_function(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(tracked_items_call_vector_table_tree_for_hash_skip_list) = Nil;
    M_CADR(tracked_items_call_vector_table_tree_for_hash_skip_list) = Nil;
    M_CAR(tracked_items_call_vector_table_tree_for_hash_skip_list) = Nil;
    if (tracked_items_call_vector_table_tree_for_hash_skip_list) {
	last_1 = tracked_items_call_vector_table_tree_for_hash_skip_list;
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
	    M_CDR(temp_1) = 
		    tracked_items_call_vector_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    tracked_items_call_vector_table_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(tracked_items_call_vector_table_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_tracked_items_call_vector_table_hash_vector(tracked_items_call_vector_table_hash_table);
    return VALUES_1(temp);
}

/* NOTE-TRACKED-ITEM-CREATION */
Object note_tracked_item_creation(item)
    Object item;
{
    Object temp, temp_2;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(142,164);
    if ((SI_Long)0L < IFIX(Tracked_items_call_depth)) {
	if ( !TRUEP(Tracked_items_call_vector_table))
	    Tracked_items_call_vector_table = 
		    make_tracked_items_call_vector_table();
	if (Current_computation_frame && Current_computation_instance && 
		Cached_stack_frame_base) {
	    gensymed_symbol = IFIX(frame_hash_function(item));
	    temp = Tracked_items_call_vector_table;
	    temp_1 = gensymed_symbol % (SI_Long)43L;
	    temp = SVREF(temp,FIX(temp_1));
	    temp_2 = 
		    Fp_mutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry;
	    set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,temp_2,T,item,
		    FIX(gensymed_symbol),
		    get_call_sequence(Tracked_items_call_depth,
		    Current_computation_frame,Current_computation_instance,
		    Cached_stack_frame_base));
	}
    }
    return VALUES_1(Nil);
}

/* NOTE-POSSIBLY-TRACKED-ITEM-DELETION */
Object note_possibly_tracked_item_deletion(item)
    Object item;
{
    Object temp, old_entry;
    SI_Long gensymed_symbol, temp_1;
    Object result;

    x_note_fn_call(142,165);
    if (Tracked_items_call_vector_table) {
	gensymed_symbol = IFIX(frame_hash_function(item));
	temp = Tracked_items_call_vector_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	result = delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),item,
		SVREF(temp,FIX(temp_1)),FIX((SI_Long)31L),
		FIX(gensymed_symbol));
	old_entry = NTH_VALUE((SI_Long)1L, result);
	if (old_entry)
	    reclaim_if_evaluation_value_function(old_entry);
    }
    return VALUES_1(Nil);
}

/* G2-GET-TRACKED-ITEM-CALL-SEQUENCE */
Object g2_get_tracked_item_call_sequence(item_as_evaluation_value)
    Object item_as_evaluation_value;
{
    Object item, value_1, temp, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, thing;
    SI_Long gensymed_symbol, temp_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(142,166);
    item = IDENTITY(item_as_evaluation_value);
    value_1 = Nil;
    if (Tracked_items_call_vector_table) {
	gensymed_symbol = IFIX(frame_hash_function(item));
	temp = Tracked_items_call_vector_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	skip_list = CDR(temp);
	key_value = item;
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
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_2 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_2,temp);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	thing = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	temp = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
		SIMPLE_VECTOR_P(thing) ? thing : 
		copy_if_evaluation_value_1(thing);
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = allocate_evaluation_sequence(Nil);
    value_1 = temp;
    IDENTITY(item_as_evaluation_value);
    temp = IDENTITY(value_1);
    return VALUES_1(temp);
}

/* G2-GET-TRACKED-ITEMS-CALL-DEPTH */
Object g2_get_tracked_items_call_depth()
{
    Object value_1;

    x_note_fn_call(142,167);
    value_1 = Nil;
    value_1 = Tracked_items_call_depth;
    return VALUES_1(value_1);
}

/* G2-SET-TRACKED-ITEMS-CALL-DEPTH */
Object g2_set_tracked_items_call_depth(max_depth_as_evaluation_value)
    Object max_depth_as_evaluation_value;
{
    Object max_depth, value_1, temp;
    char temp_1;

    x_note_fn_call(142,168);
    max_depth = max_depth_as_evaluation_value;
    value_1 = Nil;
    if ((SI_Long)0L <= IFIX(max_depth)) {
	temp = FIX((SI_Long)100L);
	temp_1 = NUM_LE(max_depth,temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	Tracked_items_call_depth = max_depth;
    value_1 = Tracked_items_call_depth;
    return VALUES_1(value_1);
}

/* G2-START-TRACKING-ITEMS */
Object g2_start_tracking_items()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(142,169);
    Tracking_items_p = T;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
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
      svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) | (SI_Long)67108864L;
      ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tracking_items_grammar_installed_p, Qtracking_items_grammar_installed_p);

static Object string_constant_29;  /* "1l1n83m+y1p1m9k83*Xy1m9k9l1m9k83-thy1m9k83Ry1m9k9m1m83-ZJy83f7y" */

/* G2-STOP-TRACKING-ITEMS */
Object g2_stop_tracking_items()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);
    XDeclare_area(1);

    x_note_fn_call(142,170);
    Tracking_items_p = Nil;
    if ( !TRUEP(Tracking_items_grammar_installed_p)) {
	Tracking_items_grammar_installed_p = T;
	if (PUSH_AREA(Dynamic_area,0)) {
	    clear_optimized_constants();
	    push_optimized_constant(Qquote);
	    push_optimized_constant(Qthe);
	    push_optimized_constant(Qset);
	    add_grammar_rules_function(regenerate_optimized_constant(string_constant_29));
	}
	POP_AREA(0);
    }
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
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
      if ( !((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
	      (SI_Long)67108864L))) {
	  svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) | 
		  (SI_Long)67108864L;
	  ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
	  svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) | 
		  (SI_Long)134217728L;
	  ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* G2-CLEAR-TRACKED-ITEMS */
Object g2_clear_tracked_items()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(142,171);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
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
      svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) &  ~(SI_Long)67108864L;
      ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
      svref_new_value = IFIX(ISVREF(item,(SI_Long)5L)) &  ~(SI_Long)134217728L;
      ISVREF(item,(SI_Long)5L) = FIX(svref_new_value);
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    if (Tracked_items_call_vector_table)
	clear_tracked_items_call_vector_table(Tracked_items_call_vector_table);
    return VALUES_1(Nil);
}

/* G2-TEXT-TO-SYMBOL-TEST */
Object g2_text_to_symbol_test(text_arg_as_evaluation_value)
    Object text_arg_as_evaluation_value;
{
    Object text_arg, value_1, temp;

    x_note_fn_call(142,172);
    text_arg = text_arg_as_evaluation_value;
    value_1 = Nil;
    value_1 = read_symbol_from_text_string(1,text_arg) ? Truth : Falsity;
    reclaim_text_string(text_arg_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* G2-LIST-OF-USER-VISIBLE-ATTRIBUTES */
Object g2_list_of_user_visible_attributes(class_name)
    Object class_name;
{
    Object new_g2_list_class, g2_list, class_description, slot_descriptions;
    Object slot_description, ab_loop_list_, slot_name, defining_class_var_qm;
    Object slot_features, type_of_slot, temp;
    char temp_1;

    x_note_fn_call(142,173);
    new_g2_list_class = g2_list_or_array_class_for_element_type(Qsymbol,Nil);
    g2_list = make_transient_item(new_g2_list_class);
    class_description = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    slot_descriptions = ISVREF(class_description,(SI_Long)6L);
    slot_description = Nil;
    ab_loop_list_ = slot_descriptions;
    slot_name = Nil;
    defining_class_var_qm = Nil;
    slot_features = Nil;
    type_of_slot = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    slot_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_name = ISVREF(slot_description,(SI_Long)2L);
    if ( !EQ(slot_name,Qab_class)) {
	if ( ! !TRUEP(ISVREF(slot_description,(SI_Long)8L))) {
	    temp = ISVREF(slot_description,(SI_Long)3L);
	    temp_1 =  !EQ(temp,
		    ISVREF(get_slot_description_of_class_description_function(ISVREF(slot_description,
		    (SI_Long)2L),class_description,Nil),(SI_Long)3L));
	}
	else
	    temp_1 = TRUEP(Nil);
	defining_class_var_qm = temp_1 ? ISVREF(slot_description,
		(SI_Long)3L) : Nil;
    }
    else
	defining_class_var_qm = Nil;
    slot_features = ISVREF(slot_description,(SI_Long)9L);
    type_of_slot = assq_function(Qtype,slot_features);
    if (type_of_slot &&  !TRUEP(do_not_put_slot_in_attribute_tables_p(2,
	    slot_description,Nil)) && SECOND(type_of_slot))
	g2_list_insert_at_end(2,slot_name,g2_list);
    goto next_loop;
  end_loop:;
    return VALUES_1(g2_list);
}

/* G2-GET-METHODS */
Object g2_get_methods(class_name)
    Object class_name;
{
    Object new_g2_list_class, g2_list, name, method, ab_loop_list_;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(142,174);
    new_g2_list_class = g2_list_or_array_class_for_element_type(Qsymbol,Nil);
    g2_list = make_transient_item(new_g2_list_class);
    name = Nil;
    method = Nil;
    ab_loop_list_ = get_procedure_methods_of_class(class_name);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    method = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_list_insert_at_end(2,method,g2_list);
    goto next_loop;
  end_loop:;
    return VALUES_1(g2_list);
}

static Object Qquantitative_variable;  /* quantitative-variable */

static Object Qvalidity_interval;  /* validity-interval */

static Object string_constant_30;  /* "G2 could not parse interval: ~a" */

/* G2-TEXT-TIME-INTERVAL-TO-UNIX-TIME */
Object g2_text_time_interval_to_unix_time(text_interval)
    Object text_interval;
{
    Object frame_type, slot_name, the_frame, the_value, temp, error_string_qm;
    Object top_of_stack, message_1, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(142,175);
    frame_type = Qquantitative_variable;
    slot_name = Qvalidity_interval;
    the_frame = make_frame(frame_type);
    the_value = Nil;
    temp = convert_text_string_to_text(text_interval);
    result = parse_text_for_slot(8,temp,the_frame,
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(the_frame,(SI_Long)1L),Nil),Nil,Nil,Nil,Nil,T);
    error_string_qm = NTH_VALUE((SI_Long)1L, result);
    the_value = get_slot_value_function(the_frame,slot_name,Nil);
    delete_frame(the_frame);
    if ( !NUMBERP(the_value)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_30,
		error_string_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	temp = lfloat(the_value,float_constant);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	result = VALUES_1(new_float);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object Qframe_author_or_authors;  /* frame-author-or-authors */

static Object string_constant_31;  /* "timestamp (~a)" */

static Object string_constant_32;  /* "G2 could not parse timestamp: ~a" */

/* G2-TEXT-TIME-STAMP-TO-UNIX-TIME */
Object g2_text_time_stamp_to_unix_time(text_timestamp)
    Object text_timestamp;
{
    Object frame_type, slot_name, the_frame, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object new_text, the_text, the_value, time_of_frame_edit_base_time;
    Object text_time_stamp_seconds, error_string_qm, temp, top_of_stack;
    Object message_1, amf_available_array_cons_qm, amf_array, temp_1, temp_2;
    Object amf_result, new_float;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    double the_value_as_float, temp_3, aref_new_value_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(142,176);
    frame_type = Qprocedure;
    slot_name = Qframe_author_or_authors;
    the_frame = make_frame(frame_type);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(2,string_constant_31,text_timestamp);
	      new_text = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    the_text = convert_text_string_to_text(new_text);
    the_value = Nil;
    the_value_as_float = 0.0;
    time_of_frame_edit_base_time = float_constant;
    PUSH_SPECIAL_WITH_SYMBOL(Time_of_frame_edit_base_time,Qtime_of_frame_edit_base_time,time_of_frame_edit_base_time,
	    1);
      text_time_stamp_seconds = float_constant;
      PUSH_SPECIAL_WITH_SYMBOL(Text_time_stamp_seconds,Qtext_time_stamp_seconds,text_time_stamp_seconds,
	      0);
	result = parse_text_for_slot(8,the_text,the_frame,
		get_slot_description_of_class_description_function(slot_name,
		ISVREF(the_frame,(SI_Long)1L),Nil),Nil,Nil,Nil,Nil,T);
	error_string_qm = NTH_VALUE((SI_Long)1L, result);
	temp = get_slot_value_function(the_frame,slot_name,Nil);
	the_value = CDR(temp);
	delete_frame(the_frame);
	reclaim_text_string(text_timestamp);
	if (FIXNUMP(the_value)) {
	    temp = lfloat(the_value,float_constant);
	    the_value_as_float = DOUBLE_FLOAT_TO_DOUBLE(temp);
	}
	else if (FLOATP(the_value))
	    the_value_as_float = DOUBLE_FLOAT_TO_DOUBLE(the_value);
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_32,error_string_qm);
	    raw_stack_error_named_error(top_of_stack,message_1);
	}
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
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
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(Text_time_stamp_seconds);
	aref_new_value_1 = 60.0 * the_value_as_float + temp_3;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value_1);
	result = VALUES_1(new_float);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* G2-CLEAR-HISTORY */
Object g2_clear_history(var_or_param_with_history)
    Object var_or_param_with_history;
{
    x_note_fn_call(142,177);
    return clear_histories(var_or_param_with_history);
}

static Object Qui_client_session;  /* ui-client-session */

static Object string_constant_33;  /* "~NF is not a g2-window or ui-client-session" */

/* G2-FLOATING-LICENSES-REMAINING */
Object g2_floating_licenses_remaining(ui_client_item)
    Object ui_client_item;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object gensymed_symbol_4, top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,178);
    if (SIMPLE_VECTOR_P(ui_client_item) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ui_client_item)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(ui_client_item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(ui_client_item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    if (temp)
	temp_1 = T;
    else {
	if (SIMPLE_VECTOR_P(ui_client_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ui_client_item)) > 
		(SI_Long)2L &&  !EQ(ISVREF(ui_client_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(ui_client_item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qui_client_session,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    temp_1 = Nil;
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_33,ui_client_item);
	    temp_1 = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    if (temp_1)
	return count_available_floating_telewindows();
    else
	return count_available_floating_tw2s();
}

static Object string_constant_34;  /* "~NF is not a valid ui-client-session." */

static Object string_constant_35;  /* "~NF is not a g2-window or ui-client-session." */

static Object string_constant_36;  /* "~NF is unauthorized." */

/* G2-FLOATING-CLIENT-P */
Object g2_floating_client_p(ui_client_item)
    Object ui_client_item;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, level, gensymed_symbol_4;
    Object top_of_stack, message_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(142,179);
    if (SIMPLE_VECTOR_P(ui_client_item) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ui_client_item)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(ui_client_item,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(ui_client_item,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
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
    if (temp)
	level = ISVREF(map_to_gensym_window_or_stack_error(ui_client_item),
		(SI_Long)16L);
    else {
	if (SIMPLE_VECTOR_P(ui_client_item) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ui_client_item)) > 
		(SI_Long)2L &&  !EQ(ISVREF(ui_client_item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(ui_client_item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol) {
	    gensymed_symbol_4 = 
		    lookup_global_or_kb_specific_property_value(Qui_client_session,
		    Class_description_gkbprop);
	    if (gensymed_symbol_4) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_4,
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    if ( !TRUEP(ui_client_session_valid_p(ui_client_item))) {
		top_of_stack = Cached_top_of_stack;
		message_1 = tformat_stack_error_text_string(2,
			string_constant_34,ui_client_item);
		raw_stack_error_named_error(top_of_stack,message_1);
	    }
	    level = 
		    ui_client_session_license_level_qm_function(ui_client_item);
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_35,ui_client_item);
	    level = raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    if (IFIX(level) == (SI_Long)-2L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_36,
		ui_client_item);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if (IFIX(level) == (SI_Long)-1L)
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* G2-SET-USER-PASSWORD */
Object g2_set_user_password(user_name,clear_old_password,clear_new_password)
    Object user_name, clear_old_password, clear_new_password;
{
    Object success_qm, error_symbol_qm;
    Object result;

    x_note_fn_call(142,180);
    result = set_user_password(user_name,clear_old_password,
	    clear_new_password);
    MVS_2(result,success_qm,error_symbol_qm);
    if (success_qm)
	return VALUES_1(Qok);
    else
	return VALUES_1(error_symbol_qm);
}

/* G2-VALIDATE-USER-AND-PASSWORD */
Object g2_validate_user_and_password(user_name_as_evaluation_value,
	    clear_password_as_evaluation_value)
    Object user_name_as_evaluation_value, clear_password_as_evaluation_value;
{
    Object user_name, clear_password, value_1, error_symbol_qm, temp;

    x_note_fn_call(142,181);
    user_name = user_name_as_evaluation_value;
    clear_password = clear_password_as_evaluation_value;
    value_1 = Nil;
    error_symbol_qm = valid_user_and_password_p(user_name,clear_password);
    temp = error_symbol_qm;
    if (temp);
    else
	temp = Qok;
    value_1 = temp;
    reclaim_text_string(clear_password_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-AUTHORIZED-MODES-FOR-USER */
Object g2_authorized_modes_for_user(user_name)
    Object user_name;
{
    Object modes_qm;

    x_note_fn_call(142,182);
    modes_qm = authorized_modes_for_user(user_name);
    if (modes_qm)
	return allocate_evaluation_sequence(copy_list_using_eval_conses_1(modes_qm));
    else
	return allocate_evaluation_sequence(Nil);
}

/* INVALID-USER-NAME-P */
Object invalid_user_name_p(user_name_string)
    Object user_name_string;
{
    Object temp_1;
    SI_Long wchar, gensymed_symbol, i, length_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(142,183);
    wchar = UBYTE_16_ISAREF_1(user_name_string,(SI_Long)0L);
    gensymed_symbol = wchar;
    if ( !((SI_Long)97L <= gensymed_symbol && gensymed_symbol <= 
	    (SI_Long)122L || (SI_Long)65L <= gensymed_symbol && 
	    gensymed_symbol <= (SI_Long)90L))
	return VALUES_1(T);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(user_name_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(user_name_string,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(user_name_string,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    wchar = UBYTE_16_ISAREF_1(user_name_string,i);
    gensymed_symbol = wchar;
    temp = (SI_Long)97L <= gensymed_symbol ? gensymed_symbol <= 
	    (SI_Long)122L : TRUEP(Qnil);
    if (temp);
    else
	temp = (SI_Long)65L <= gensymed_symbol ? gensymed_symbol <= 
		(SI_Long)90L : TRUEP(Qnil);
    if (temp);
    else {
	gensymed_symbol = wchar;
	temp = (SI_Long)48L <= gensymed_symbol && gensymed_symbol <= 
		(SI_Long)57L ? TRUEP(FIX(gensymed_symbol - (SI_Long)48L)) :
		 TRUEP(Nil);
    }
    if (temp);
    else
	temp = IFIX(Pct_) == wchar;
    if (temp);
    else
	temp = IFIX(ab_Pct_) == wchar;
    if (temp);
    else
	temp = IFIX(Pct_dot) == wchar;
    if (temp);
    else
	temp = IFIX(Pct_qm) == wchar;
    if ( !temp) {
	temp_1 = T;
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = Nil;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    return VALUES_1(temp_1);
}

static Object string_constant_37;  /* "The user ~a already exists." */

static Object string_constant_38;  /* "The password-expiration-date ~NV should ~
				    *                                be a sequence of three integers."
				    */

static Object string_constant_39;  /* "~a is not a valid user mode because ~a" */

static Object string_constant_40;  /* "Problem: ~a" */

/* G2-ADD-USER */
Object g2_add_user(user_name_as_evaluation_value,
	    clear_password_as_evaluation_value,modes_as_evaluation_value,
	    password_expiration_date_as_evaluation_value)
    Object user_name_as_evaluation_value, clear_password_as_evaluation_value;
    Object modes_as_evaluation_value;
    Object password_expiration_date_as_evaluation_value;
{
    Object user_name, clear_password, modes, password_expiration_date;
    Object top_of_stack, message_1, scope_conses, gensymed_symbol, held_vector;
    Object number, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, date_list, date, ab_loop_list_, text_string;
    Object snapshots, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object mode, list_of_modes, error_symbol_qm;
    SI_Long next_index, length_1, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_2;
    char temp;
    Declare_special(8);

    x_note_fn_call(142,184);
    user_name = user_name_as_evaluation_value;
    clear_password = clear_password_as_evaluation_value;
    modes = IDENTITY(modes_as_evaluation_value);
    password_expiration_date = 
	    IDENTITY(password_expiration_date_as_evaluation_value);
    if (authorized_modes_for_user(user_name)) {
	reclaim_evaluation_sequence(modes);
	reclaim_evaluation_sequence(password_expiration_date);
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_37,
		user_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	scope_conses = Scope_conses;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,7);
	  gensymed_symbol = password_expiration_date;
	  held_vector = Nil;
	  next_index = (SI_Long)1L;
	  length_1 = (SI_Long)0L;
	  number = Nil;
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
	  number = validated_elt;
	  ab_loopvar__2 = scope_cons(number,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop:
	  date_list = ab_loopvar_;
	  goto end_1;
	  date_list = Qnil;
	end_1:;
	  if (IFIX(length(date_list)) == (SI_Long)1L && 
		  EQ(FIRST(date_list),FIX((SI_Long)0L)))
	      date_list = FIX((SI_Long)0L);
	  else {
	      temp = IFIX(length(date_list)) != (SI_Long)3L;
	      if (temp);
	      else {
		  date = Nil;
		  ab_loop_list_ = date_list;
		next_loop_1:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop_1;
		  date = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  if ( !INTEGERP(date)) {
		      temp = TRUEP(T);
		      goto end_2;
		  }
		  goto next_loop_1;
		end_loop_1:
		  temp = TRUEP(Qnil);
		end_2:;
	      }
	      if (temp) {
		  reclaim_evaluation_sequence(modes);
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
			  fill_pointer_for_current_wide_string = 
				  FIX((SI_Long)0L);
			  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				  2);
			    length_2 = 
				    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			    total_length_of_current_wide_string = 
				    FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				    length_2 - (SI_Long)2L) + 
				    ((UBYTE_16_ISAREF_1(Current_wide_string,
				    length_2 - (SI_Long)1L) & 
				    (SI_Long)8191L) << (SI_Long)16L));
			    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				    1);
			      current_twriting_output_type = Qwide_string;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				      0);
				tformat(2,string_constant_38,
					password_expiration_date);
				reclaim_evaluation_sequence(password_expiration_date);
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
	      else
		  date_list = 
			  check_that_pswd_decay_date_is_in_the_future(FIRST(date_list),
			  SECOND(date_list),THIRD(date_list));
	  }
	  gensymed_symbol = modes;
	  held_vector = Nil;
	  next_index = (SI_Long)1L;
	  length_1 = (SI_Long)0L;
	  mode = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	  held_vector = M_CAR(gensymed_symbol);
	  length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	next_loop_2:
	  if (next_index >= length_1)
	      goto end_loop_2;
	  elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(held_vector,
		  next_index + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	  validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		  Nil,Nil) : Nil;
	  next_index = next_index + (SI_Long)1L;
	  mode = validated_elt;
	  ab_loopvar__2 = gensym_cons_1(mode,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_2;
	end_loop_2:
	  list_of_modes = ab_loopvar_;
	  goto end_3;
	  list_of_modes = Qnil;
	end_3:;
	  error_symbol_qm = Nil;
	  mode = Nil;
	  ab_loop_list_ = list_of_modes;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  mode = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  error_symbol_qm = validate_as_possible_user_mode(mode);
	  if (error_symbol_qm) {
	      reclaim_gensym_list_1(list_of_modes);
	      reclaim_evaluation_sequence(modes);
	      reclaim_evaluation_sequence(password_expiration_date);
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(3,
		      string_constant_39,mode,error_symbol_qm);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  goto next_loop_3;
	end_loop_3:;
	  error_symbol_qm = add_new_user_encoding_as_needed(user_name,
		  clear_password,list_of_modes,date_list);
	  if (error_symbol_qm) {
	      reclaim_gensym_list_1(list_of_modes);
	      reclaim_evaluation_sequence(modes);
	      reclaim_evaluation_sequence(password_expiration_date);
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(2,
		      string_constant_40,error_symbol_qm);
	      raw_stack_error_named_error(top_of_stack,message_1);
	  }
	POP_SPECIAL();
    }
    reclaim_evaluation_sequence(modes);
    reclaim_evaluation_sequence(password_expiration_date);
    reclaim_text_string(clear_password_as_evaluation_value);
    IDENTITY(modes_as_evaluation_value);
    IDENTITY(password_expiration_date_as_evaluation_value);
    return VALUES_0();
}

static Object string_constant_41;  /* "There is no user with the name ~a" */

/* G2-DELETE-USER */
Object g2_delete_user(user_name_as_evaluation_value)
    Object user_name_as_evaluation_value;
{
    Object user_name, top_of_stack, message_1, error_symbol_qm;

    x_note_fn_call(142,185);
    user_name = user_name_as_evaluation_value;
    if ( !TRUEP(authorized_modes_for_user(user_name))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_41,
		user_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    error_symbol_qm = delete_user(user_name);
    if (error_symbol_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_40,
		error_symbol_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_0();
}

static Object string_constant_42;  /* "The date provided for when the password should ~
				    *                expire, ~a/~a/~a, is in the past"
				    */

/* CHECK-THAT-PSWD-DECAY-DATE-IS-IN-THE-FUTURE */
Object check_that_pswd_decay_date_is_in_the_future(day,month,year)
    Object day, month, year;
{
    Object today, expiration_date, top_of_stack, message_1;

    x_note_fn_call(142,186);
    today = get_universal_date();
    expiration_date = encode_universal_date(day,month,year);
    if ( !FIXNUM_GE(expiration_date,today)) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_42,
		month,day,year);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(expiration_date);
}

/* G2-CHANGE-PASSWORD-EXPIRATION-DATE */
Object g2_change_password_expiration_date(user_name_as_evaluation_value,
	    day_as_evaluation_value,month_as_evaluation_value,
	    year_as_evaluation_value)
    Object user_name_as_evaluation_value, day_as_evaluation_value;
    Object month_as_evaluation_value, year_as_evaluation_value;
{
    Object user_name, day, month, year, top_of_stack, message_1;
    Object universal_date, error_symbol_qm;

    x_note_fn_call(142,187);
    user_name = user_name_as_evaluation_value;
    day = day_as_evaluation_value;
    month = month_as_evaluation_value;
    year = year_as_evaluation_value;
    if ( !TRUEP(authorized_modes_for_user(user_name))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_41,
		user_name);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    universal_date = check_that_pswd_decay_date_is_in_the_future(day,month,
	    year);
    error_symbol_qm = change_users_password_decay_date(user_name,
	    universal_date);
    if (error_symbol_qm) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_40,
		error_symbol_qm);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_0();
}

/* G2-UPDATE-LICENSE */
Object g2_update_license()
{
    Object value_1, unevaluated_expression, temp;
    Declare_special(1);

    x_note_fn_call(142,188);
    value_1 = Nil;
    Cached_machine_id_qm = Nil;
    Cached_matching_machine_id_qm = Nil;
    unevaluated_expression = Within_side_limits;
    PUSH_SPECIAL_WITH_SYMBOL(Unevaluated_expression,Qunevaluated_expression,unevaluated_expression,
	    0);
      value_1 = authorize_ab() ? Truth : Falsity;
    POP_SPECIAL();
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    return VALUES_1(temp);
}

/* FREE-MALLOCED-ARRAYS-ON-RECLAIM */
Object free_malloced_arrays_on_reclaim()
{
    x_note_fn_call(142,189);
    Free_malloced_arrays = T;
    free_malloced_byte_vector_16s();
    free_malloced_strings();
    return VALUES_0();
}

/* FREE-MALLOCED-ARRAYS-ON-REQUEST */
Object free_malloced_arrays_on_request()
{
    x_note_fn_call(142,190);
    Free_malloced_arrays = Nil;
    return VALUES_0();
}

/* FREE-ALL-MALLOCED-ARRAYS */
Object free_all_malloced_arrays()
{
    x_note_fn_call(142,191);
    free_malloced_byte_vector_16s();
    free_malloced_strings();
    return VALUES_0();
}

void sets_INIT()
{
    Object temp, temp_1, reclaim_structure_for_rule_instance_1, temp_2, temp_3;
    Object temp_4, gensymed_symbol, temp_5;
    Object Qfree_all_malloced_arrays;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qfree_malloced_arrays_on_request, Qfree_malloced_arrays_on_reclaim;
    Object Qg2_update_license, Qg2_change_password_expiration_date;
    Object Qg2_delete_user, Qg2_add_user, Qg2_authorized_modes_for_user;
    Object Qg2_validate_user_and_password, Qg2_set_user_password;
    Object Qg2_floating_client_p, Qg2_floating_licenses_remaining;
    Object Qg2_clear_history, Qg2_text_time_stamp_to_unix_time;
    Object Qg2_text_time_interval_to_unix_time, Qg2_get_methods;
    Object Qg2_list_of_user_visible_attributes, Qg2_text_to_symbol_test;
    Object Qg2_clear_tracked_items, Qg2_stop_tracking_items;
    Object Qg2_start_tracking_items, Qg2_set_tracked_items_call_depth;
    Object Qg2_get_tracked_items_call_depth;
    Object Qg2_get_tracked_item_call_sequence;
    Object Qmutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry;
    Object Qout_tracked_items_call_vector_table_hash_vector_43_vectors;
    Object Qtracked_items_call_vector_table_hash_vector_43_vector_memory_usage;
    Object string_constant_63, Qutilities2, Qg2_run_trace, Qg2_float_to_text;
    Object Qg2_float_to_text_using_decimal_format;
    Object Qg2_get_enumerations_for_symbolic_attribute;
    Object Qg2_get_attributes_for_class, Qsystem_predicate;
    Object Qg2_get_items_connected_to_port, Qg2_get_connection_vertices;
    Object Qg2_load_runtime_data, Qg2_warmboot_kb, Qg2_merge_kb;
    Object Qg2_merge_kb_extended, Qg2_merge_kb_ex, list_constant_79;
    Object list_constant_78, list_constant_77, list_constant_76;
    Object list_constant_75, list_constant_74, list_constant_73;
    Object list_constant_72, list_constant_71, list_constant_70;
    Object list_constant_69, list_constant_68, Qg2_load_kb;
    Object Qg2_load_kb_extended, Qg2_modules_with_unsaved_changes;
    Object Qg2_create_module, Qg2_save_module_without_other_processing;
    Object Qg2_save_module_extended_without_other_processing;
    Object Qg2_save_kb_without_other_processing, Qg2_finish_save_kb;
    Object Qg2_continue_save_kb, Qg2_save_kb, Qg2_reclaim_save_module_memory;
    Object Qg2_save_module, Qis_g2_save_module_flag_set;
    Object Qreset_g2_save_module_flag, Qset_g2_save_module_flag;
    Object Qg2_save_module_extended, Qcleanup_kb_save_or_backup_if_necessary;
    Object list_constant_39, Qsets, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qg2_clear_profiling, Qg2_toggle_system_profiling;
    Object Qg2_disable_system_profiling, Qg2_enable_system_profiling;
    Object Qg2_system_profiled_items, Qg2_procedure_activity_calls;
    Object Qg2_user_name_for_frame, Qg2_allow_profiling_regardless_of_license;
    Object Qg2_procedure_activity_list, Qg2_procedure_detail;
    Object Qg2_system_profile, list_constant_67, Qg2gl_profiling_lists;
    Object Qcontinue_scheduled_process_invocation;
    Object Qcontinue_execution_of_thread, list_constant_66;
    Object Qoverhead_kb_profiling_names, Qdetect_and_break_deadlocks;
    Object Qsystem_state_change_from_scheduler_1, Qwarn_about_editing_item;
    Object Qservice_background_processes, Qnative_window_heartbeat;
    Object Qinitialize_for_asian_languages;
    Object Qdo_legacy_subsecond_heartbeat_adjustments;
    Object Qdo_legacy_multisecond_heartbeat_adjustments;
    Object Qcall_post_prominent_notification;
    Object Qwarn_user_of_previously_aborted_g2, Qcompletely_shut_down_g2;
    Object list_constant_65, Qworkstation_profiling_names;
    Object Qservice_workstation, Qservice_workstations_final;
    Object Qrun_workspace_callbacks, Qrun_area_selected_callbacks;
    Object Qrun_selection_callbacks, Qpropagate_allow_scheduled_drawing_1;
    Object Qpropagate_all_workspace_changes_to_image_planes, list_constant_64;
    Object Qicp_profiling_names, Qsocket_close_cleanups;
    Object Qsend_new_trend_chart_data_task;
    Object Qsend_queued_reclaim_index_space_messages;
    Object Qtry_to_transmit_resumable_object;
    Object Qtry_to_preflight_resumable_object, Qicp_connection_timeout_task_2;
    Object Qicp_connection_timeout_task_1, Qtime_out_icp_socket;
    Object Qresumable_icp_write_callback;
    Object Qhandle_unclogged_connection_if_necessary, Qsend_i_am_alive_message;
    Object Qhandle_close_event, Qhandle_write_event_function;
    Object Qhandle_read_event_function, Qhandle_queued_icp_messages_task;
    Object list_constant_63, Qkb_io_profiling_names, list_constant_62;
    Object Qdata_service_profiling_names, Qtask_to_probe_failed_variable;
    Object Qtask_to_detect_failure, Qreturn_values_to_g2ds_client_task;
    Object Qprocess_requests_for_gsi_interfaces, Qprocess_gsi_sensor_values;
    Object Qprocess_g2ds_variable_values;
    Object Qperform_background_collection_for_inference_engine;
    Object Qkill_foreign_image_process_unconditionally;
    Object Qinitiate_inter_g2_data_service_request;
    Object Qinitiate_inter_g2_set_value_request, Qg2ds_collect_one_shot_data;
    Object Qg2ds_begin_collecting_data, Qenqueue_gsi_request_for_sensor;
    Object Qcontinue_data_server_data_acceptance;
    Object Qcollect_one_shot_data_for_gfi_data_service;
    Object Qcollect_one_shot_data_for_g2_meters;
    Object Qcall_data_server_accept_data_functions;
    Object Qaccept_data_and_reschedule_if_necessary, list_constant_61;
    Object Qscheduling_profiling_names, Qreceive_nupec_synchronize_task;
    Object Qreceive_start_or_call_remote_procedure_1;
    Object Qexecute_scheduled_remote_procedure_start;
    Object Qimmediately_return_from_breakpoint;
    Object Qsafe_invoke_rules_for_existential_chaining;
    Object Qpropagate_variable_value_expiration;
    Object Qgfi_output_spreadsheet_values_periodically_task;
    Object Qgfi_output_event_log_values_periodically_task;
    Object Qcomplete_initial_rules, Qwake_up_code_body_invocation;
    Object Qschedule_initial_rules_from_activated_kb_workspace;
    Object Qschedule_computation_instance_execution, Qinvoke_rule_universally;
    Object Qexecute_computation_instance, Qexecute_backward_chaining_for_rules;
    Object Qattempt_expression_cell_execution, list_constant_60;
    Object Qdisplay_profiling_names, Qresume_search_task_in_workstation;
    Object Qwork_on_schedule_of_table_updates_a_little;
    Object Qverify_and_set_variable_per_non_action_button;
    Object Qupdate_trend_chart_task, Qupdate_display_for_graph;
    Object Qupdate_display_for_digital_clock, Qscrolling_heartbeat;
    Object Qscheduled_update_button, Qupdate_display_if_not_reprocessed;
    Object Qupdate_chart, Qunhighlight_recent_message;
    Object Qscheduled_display_update, Qrefresh_window;
    Object Qredraw_solid_rectangles_without_overlap;
    Object Qexecute_message_removal_task, Qg2_profiled_call_information;
    Object string_constant_62, list_constant_59, Qg2_deadlock_error;
    Object string_constant_58, string_constant_57, string_constant_61;
    Object string_constant_60, list_constant_58, string_constant_59;
    Object Qget_error_source_trace, Qinitial_error_source_trace;
    Object list_constant_57, Qerror_source_trace;
    Object Qvirtual_attributes_local_to_class, Qslot_putter;
    Object Qput_error_description, string_constant_56, string_constant_55;
    Object list_constant_56, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, Qg2_disable_disassembler;
    Object Qg2_enable_disassembler, list_constant_55, Qparameter;
    Object Qvariable_or_parameter, list_constant_41, list_constant_54;
    Object list_constant_53, list_constant_52, Qinteger_parameter;
    Object list_constant_51, list_constant_45, list_constant_50;
    Object Qinteger_variable, list_constant_49, list_constant_48;
    Object list_constant_47, Qfloat_parameter, Qquantitative_parameter;
    Object list_constant_46, list_constant_44, Qfloat_variable;
    Object list_constant_43, Qlogical_variable, Qlogical_parameter;
    Object list_constant_42, Qsymbolic_variable, Qsymbolic_parameter;
    Object list_constant_40, Qsensor, Qtext_variable, Qtext_parameter;
    Object Qobsolete_datum, Qno_item_implies_unknown, Qno_item, Qunknown_datum;
    Object Qwrite_evaluation_obsolete_datum, Qdefined_evaluation_type_writer;
    Object Qrule_instance, Qreclaim_structure;
    Object Qoutstanding_rule_instance_count;
    Object Qrule_instance_structure_memory_usage, string_constant_50;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_49, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qutilities0;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qinterval_for_retry, Qslot_value_compiler;
    Object Qcompile_interval_for_retry_for_slot, Qslot_value_writer;
    Object Qwrite_interval_for_retry_from_slot, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35;
    Object list_constant_34, list_constant_33, list_constant_32, Qretry;
    Object Qinterval, Qretry_interval_after_timeout;
    Object Qretry_interval_after_sensor_timeout, Qabsent_slot_putter;
    Object Qput_timeout_for_wake_ups_where_slot_is_absent;
    Object Qtimeout_for_wake_ups;
    Object Qput_default_debugging_message_level_where_slot_is_absent;
    Object Qdefault_debugging_message_level, Qput_truth_threshold;
    Object Qtimeout_for_inference_completion, Quse_old_rule_compiler;
    Object Quse_old_rule_compiler_qm;
    Object Qput_truth_threshhold_where_slot_is_absent, Qtruth_threshhold;
    Object Qput_use_old_rule_compiler_qm_where_slot_is_absent;
    Object Qput_set_of_all_computation_styles_where_slot_is_absent;
    Object Qset_of_all_computation_styles, Ksystem_frame, string_constant_48;
    Object string_constant_47, list_constant_31, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object Qsystem_table;

    x_note_fn_call(142,192);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qstack_expiration = STATIC_SYMBOL("STACK-EXPIRATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstack_expiration,Stack_expiration);
    Qsets = STATIC_SYMBOL("SETS",AB_package);
    record_system_variable(Qstack_expiration,Qsets,Nil,Qnil,Qnil,Qnil,Qnil);
    Qmultiplier_for_turning_off_data_collection = 
	    STATIC_SYMBOL("MULTIPLIER-FOR-TURNING-OFF-DATA-COLLECTION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmultiplier_for_turning_off_data_collection,
	    Multiplier_for_turning_off_data_collection);
    record_system_variable(Qmultiplier_for_turning_off_data_collection,
	    Qsets,FIX((SI_Long)5L),Qnil,Qnil,Qnil,Qnil);
    Qmessage_completion_interval = 
	    STATIC_SYMBOL("MESSAGE-COMPLETION-INTERVAL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmessage_completion_interval,
	    Message_completion_interval);
    record_system_variable(Qmessage_completion_interval,Qsets,
	    FIX((SI_Long)15L),Qnil,Qnil,Qnil,Qnil);
    Qinference_engine_parameters = 
	    STATIC_SYMBOL("INFERENCE-ENGINE-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_31 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qinference_engine_parameters,
	    list_constant_31);
    string_constant_43 = STATIC_STRING("1l1l83ey");
    string_constant_44 = 
	    STATIC_STRING("1q4z8r83Yhy83Yhy8395y8395y03ky001n1l8o1l8l1m8p83Sy000004z8r83c5y83c5y8395y8395y03Qy001n1l8o1l8l1m8p8376y000004z8r83c6y83c6y8395y");
    string_constant_45 = 
	    STATIC_STRING("8395y03Qy001n1l8o1l8l1m8p8376y000004z8r83Z6y83Z6y8395y8395y03uy001n1l8o1l8l1m8p83D6y000004z8r83coy83coy8395y8395y038Sy001n1l8o1l");
    string_constant_46 = 
	    STATIC_STRING("8l1m8p83-hy000004z8r83LAy83LAy8395y8395y038Sz001m1l8o1l8l00000");
    string_constant_47 = 
	    STATIC_STRING("1s8q1n8395y1l83-sy83ey1p83Yhy3ky8o8l1m8p83Sy1p83c5y3Qy8o8l1m8p8376y1p83c6y3Qy8o8l1m8p8376y1p83Z6y3uy8o8l1m8p83D6y1p83coy38Sy8o8l");
    string_constant_48 = STATIC_STRING("1m8p83-hy1o83LAy38Sz8o8l");
    temp = regenerate_optimized_constant(string_constant_43);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_44,
	    string_constant_45,string_constant_46));
    add_class_to_environment(9,Qinference_engine_parameters,
	    list_constant_31,Nil,temp,Nil,temp_1,list_constant_31,
	    regenerate_optimized_constant(LIST_2(string_constant_47,
	    string_constant_48)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qinference_engine_parameters,
	    Inference_engine_parameters);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qinference_engine_parameters,Qsets,
	    Ksystem_frame,Qnil,Qnil,Qnil,Qt);
    Qset_of_all_computation_styles = 
	    STATIC_SYMBOL("SET-OF-ALL-COMPUTATION-STYLES",AB_package);
    Qput_set_of_all_computation_styles_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-SET-OF-ALL-COMPUTATION-STYLES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_set_of_all_computation_styles_where_slot_is_absent,
	    STATIC_FUNCTION(put_set_of_all_computation_styles_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qset_of_all_computation_styles,
	    SYMBOL_FUNCTION(Qput_set_of_all_computation_styles_where_slot_is_absent),
	    Qabsent_slot_putter);
    Quse_old_rule_compiler_qm = STATIC_SYMBOL("USE-OLD-RULE-COMPILER\?",
	    AB_package);
    Qput_use_old_rule_compiler_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-USE-OLD-RULE-COMPILER\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_use_old_rule_compiler_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_use_old_rule_compiler_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Quse_old_rule_compiler_qm,
	    SYMBOL_FUNCTION(Qput_use_old_rule_compiler_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtruth_threshold = STATIC_SYMBOL("TRUTH-THRESHOLD",AB_package);
    Qtruth_threshhold = STATIC_SYMBOL("TRUTH-THRESHHOLD",AB_package);
    Qput_truth_threshhold_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TRUTH-THRESHHOLD-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_truth_threshhold_where_slot_is_absent,
	    STATIC_FUNCTION(put_truth_threshhold_where_slot_is_absent,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtruth_threshhold,
	    SYMBOL_FUNCTION(Qput_truth_threshhold_where_slot_is_absent),
	    Qabsent_slot_putter);
    Quse_old_rule_compiler = STATIC_SYMBOL("USE-OLD-RULE-COMPILER",AB_package);
    alias_slot_name(3,Quse_old_rule_compiler_qm,Quse_old_rule_compiler,Qnil);
    Qtimeout_for_wakeups = STATIC_SYMBOL("TIMEOUT-FOR-WAKEUPS",AB_package);
    Qtimeout_for_inference_completion = 
	    STATIC_SYMBOL("TIMEOUT-FOR-INFERENCE-COMPLETION",AB_package);
    alias_slot_name(3,Qtimeout_for_wakeups,
	    Qtimeout_for_inference_completion,Qnil);
    Qput_truth_threshold = STATIC_SYMBOL("PUT-TRUTH-THRESHOLD",AB_package);
    SET_SYMBOL_FUNCTION(Qput_truth_threshold,
	    STATIC_FUNCTION(put_truth_threshold,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qtruth_threshold,
	    SYMBOL_FUNCTION(Qput_truth_threshold),Qslot_putter);
    Qdefault_debugging_message_level = 
	    STATIC_SYMBOL("DEFAULT-DEBUGGING-MESSAGE-LEVEL",AB_package);
    Qput_default_debugging_message_level_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-DEFAULT-DEBUGGING-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_debugging_message_level_where_slot_is_absent,
	    STATIC_FUNCTION(put_default_debugging_message_level_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qdefault_debugging_message_level,
	    SYMBOL_FUNCTION(Qput_default_debugging_message_level_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtimeout_for_wake_ups = STATIC_SYMBOL("TIMEOUT-FOR-WAKE-UPS",AB_package);
    Qput_timeout_for_wake_ups_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TIMEOUT-FOR-WAKE-UPS-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_timeout_for_wake_ups_where_slot_is_absent,
	    STATIC_FUNCTION(put_timeout_for_wake_ups_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtimeout_for_wake_ups,
	    SYMBOL_FUNCTION(Qput_timeout_for_wake_ups_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qretry_interval_after_sensor_timeout = 
	    STATIC_SYMBOL("RETRY-INTERVAL-AFTER-SENSOR-TIMEOUT",AB_package);
    Qretry_interval_after_timeout = 
	    STATIC_SYMBOL("RETRY-INTERVAL-AFTER-TIMEOUT",AB_package);
    alias_slot_name(3,Qretry_interval_after_sensor_timeout,
	    Qretry_interval_after_timeout,Qnil);
    Qrecursive_depth = STATIC_SYMBOL("RECURSIVE-DEPTH",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecursive_depth,Recursive_depth);
    record_system_variable(Qrecursive_depth,Qsets,FIX((SI_Long)0L),Qnil,
	    Qnil,Qnil,Qnil);
    Qinterval_for_retry = STATIC_SYMBOL("INTERVAL-FOR-RETRY",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qinterval_for_retry,Qinterval);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qquote,Qdo);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qquote,Qnot);
    Qretry = STATIC_SYMBOL("RETRY",AB_package);
    list_constant_34 = STATIC_LIST((SI_Long)2L,Qquote,Qretry);
    list_constant_35 = STATIC_LIST((SI_Long)3L,list_constant_32,
	    list_constant_33,list_constant_34);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qinterval_for_retry,
	    list_constant_35);
    list_constant_38 = STATIC_LIST((SI_Long)2L,list_constant_36,
	    list_constant_37);
    add_grammar_rules_function(list_constant_38);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_39,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qwrite_interval_for_retry_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERVAL-FOR-RETRY-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interval_for_retry_from_slot,
	    STATIC_FUNCTION(write_interval_for_retry_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qinterval_for_retry,
	    SYMBOL_FUNCTION(Qwrite_interval_for_retry_from_slot),
	    Qslot_value_writer);
    Qcompile_interval_for_retry_for_slot = 
	    STATIC_SYMBOL("COMPILE-INTERVAL-FOR-RETRY-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_interval_for_retry_for_slot,
	    STATIC_FUNCTION(compile_interval_for_retry_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qinterval_for_retry,
	    SYMBOL_FUNCTION(Qcompile_interval_for_retry_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qinterval_for_retry,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcurrent_environment = STATIC_SYMBOL("CURRENT-ENVIRONMENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_environment,Current_environment);
    Qutilities0 = STATIC_SYMBOL("UTILITIES0",AB_package);
    record_system_variable(Qcurrent_environment,Qutilities0,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qcached_top_of_stack = STATIC_SYMBOL("CACHED-TOP-OF-STACK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_top_of_stack,Cached_top_of_stack);
    record_system_variable(Qcached_top_of_stack,Qsets,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcached_stack_program_counter = 
	    STATIC_SYMBOL("CACHED-STACK-PROGRAM-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_stack_program_counter,
	    Cached_stack_program_counter);
    record_system_variable(Qcached_stack_program_counter,Qsets,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qcached_fixnum_start_time = STATIC_SYMBOL("CACHED-FIXNUM-START-TIME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_fixnum_start_time,
	    Cached_fixnum_start_time);
    record_system_variable(Qcached_fixnum_start_time,Qsets,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qcached_stack_frame_base = STATIC_SYMBOL("CACHED-STACK-FRAME-BASE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_stack_frame_base,
	    Cached_stack_frame_base);
    record_system_variable(Qcached_stack_frame_base,Qsets,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qcached_byte_code_body = STATIC_SYMBOL("CACHED-BYTE-CODE-BODY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_byte_code_body,Cached_byte_code_body);
    record_system_variable(Qcached_byte_code_body,Qsets,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qcached_fixnum_time_limit_qm = 
	    STATIC_SYMBOL("CACHED-FIXNUM-TIME-LIMIT\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_fixnum_time_limit_qm,
	    Cached_fixnum_time_limit_qm);
    record_system_variable(Qcached_fixnum_time_limit_qm,Qsets,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qrule_instance = STATIC_SYMBOL("RULE-INSTANCE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_rule_instance_g2_struct,
	    Qrule_instance,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qrule_instance,
	    Qg2_defstruct_structure_name_rule_instance_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_rule_instance == UNBOUND)
	The_type_description_of_rule_instance = Nil;
    string_constant_49 = 
	    STATIC_STRING("43Dy8m83mYy1o83mYy830Ey8n8k1l830Ey0000001m1m8x830Ey1m8y83-5dyk3Pyk0k0");
    temp = The_type_description_of_rule_instance;
    The_type_description_of_rule_instance = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_49));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_rule_instance_g2_struct,
	    The_type_description_of_rule_instance,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qrule_instance,
	    The_type_description_of_rule_instance,Qtype_description_of_type);
    Qoutstanding_rule_instance_count = 
	    STATIC_SYMBOL("OUTSTANDING-RULE-INSTANCE-COUNT",AB_package);
    Qrule_instance_structure_memory_usage = 
	    STATIC_SYMBOL("RULE-INSTANCE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_50 = STATIC_STRING("1q83mYy8s83-nLy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_rule_instance_count);
    push_optimized_constant(Qrule_instance_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_50));
    Qchain_of_available_rule_instances = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RULE-INSTANCES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_rule_instances,
	    Chain_of_available_rule_instances);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_rule_instances,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qrule_instance_count = STATIC_SYMBOL("RULE-INSTANCE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrule_instance_count,Rule_instance_count);
    record_system_variable(Qrule_instance_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_rule_instances_vector == UNBOUND)
	Chain_of_available_rule_instances_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qrule_instance_structure_memory_usage,
	    STATIC_FUNCTION(rule_instance_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_rule_instance_count,
	    STATIC_FUNCTION(outstanding_rule_instance_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_rule_instance_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_rule_instance,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qrule_instance,
	    reclaim_structure_for_rule_instance_1);
    if (Current_ri_completion_notification_collection_qm == UNBOUND)
	Current_ri_completion_notification_collection_qm = Nil;
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qboolean = STATIC_SYMBOL("BOOLEAN",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    Qdefined_evaluation_type_writer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-WRITER",AB_package);
    Qwrite_evaluation_obsolete_datum = 
	    STATIC_SYMBOL("WRITE-EVALUATION-OBSOLETE-DATUM",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_obsolete_datum,
	    STATIC_FUNCTION(write_evaluation_obsolete_datum,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qobsolete_datum),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_obsolete_datum));
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant = STATIC_CONS(Qunknown_datum,Qnil);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_1 = STATIC_CONS(Qno_item,Qnil);
    Qno_item_implies_unknown = STATIC_SYMBOL("NO-ITEM-IMPLIES-UNKNOWN",
	    AB_package);
    list_constant_2 = STATIC_CONS(Qno_item_implies_unknown,Qnil);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_3 = STATIC_CONS(Qsequence,Qnil);
    Qstruct = STATIC_SYMBOL("STRUCT",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_4 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qsequence,Qitem_or_datum);
    list_constant_6 = STATIC_CONS(Qobsolete_datum,Qnil);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant);
    Qevaluation_value = STATIC_SYMBOL("EVALUATION-VALUE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qstable_subclass = STATIC_SYMBOL("STABLE-SUBCLASS",AB_package);
    Qstable_not_subclass = STATIC_SYMBOL("STABLE-NOT-SUBCLASS",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qtext_parameter = STATIC_SYMBOL("TEXT-PARAMETER",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_parameter);
    Qtext_variable = STATIC_SYMBOL("TEXT-VARIABLE",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qab_class,Qtext_variable);
    Qsensor = STATIC_SYMBOL("SENSOR",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qab_class,Qsensor);
    list_constant_41 = STATIC_CONS(list_constant_28,Qnil);
    list_constant_8 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,list_constant_15,
	    list_constant_40,list_constant_41);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qab_class,Qsymbolic_parameter);
    Qsymbolic_variable = STATIC_SYMBOL("SYMBOLIC-VARIABLE",AB_package);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qab_class,Qsymbolic_variable);
    list_constant_9 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,list_constant_16,
	    list_constant_42,list_constant_41);
    Qlogical_parameter = STATIC_SYMBOL("LOGICAL-PARAMETER",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qab_class,Qlogical_parameter);
    Qlogical_variable = STATIC_SYMBOL("LOGICAL-VARIABLE",AB_package);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qab_class,Qlogical_variable);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_17,list_constant_43,list_constant_41);
    Qquantitative_variable = STATIC_SYMBOL("QUANTITATIVE-VARIABLE",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qquantitative_variable);
    Qfloat_variable = STATIC_SYMBOL("FLOAT-VARIABLE",AB_package);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qab_class,Qfloat_variable);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_44);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qand,list_constant_45,
	    list_constant_46);
    Qquantitative_parameter = STATIC_SYMBOL("QUANTITATIVE-PARAMETER",
	    AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qquantitative_parameter);
    Qfloat_parameter = STATIC_SYMBOL("FLOAT-PARAMETER",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qab_class,Qfloat_parameter);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_47);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qand,list_constant_19,
	    list_constant_48);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_49,list_constant_18,list_constant_41);
    list_constant_12 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_45,list_constant_19,list_constant_41);
    Qinteger_variable = STATIC_SYMBOL("INTEGER-VARIABLE",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qab_class,Qinteger_variable);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_50);
    list_constant_54 = STATIC_LIST((SI_Long)3L,Qand,list_constant_45,
	    list_constant_51);
    Qinteger_parameter = STATIC_SYMBOL("INTEGER-PARAMETER",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qab_class,Qinteger_parameter);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qnot,list_constant_52);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qand,list_constant_19,
	    list_constant_53);
    list_constant_13 = STATIC_LIST_STAR((SI_Long)4L,Qab_or,
	    list_constant_54,list_constant_20,list_constant_41);
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qab_class,
	    Qvariable_or_parameter);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qab_class,Qparameter);
    list_constant_55 = STATIC_CONS(list_constant,Qnil);
    list_constant_22 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_55);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qfloat,
	    list_constant_55);
    list_constant_24 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_55);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_55);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qtext,
	    list_constant_55);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qdatum,
	    list_constant_55);
    list_constant_29 = STATIC_LIST((SI_Long)7L,Qtext,Qsymbol,Qtruth_value,
	    Qinteger,Qfloat,Qnumber,Qdatum);
    def_numeric_subtype(1,Qquantity);
    string_constant = 
	    STATIC_STRING("Fetching a value of type ~a, an unrecognized type or unit of ~\n       measure.");
    string_constant_1 = STATIC_STRING("~%  ");
    string_constant_2 = STATIC_STRING("~%  None");
    temp_2 = make_partial_buffer_info(FIX((SI_Long)64L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)3L));
    temp_3 = make_partial_buffer_info(FIX((SI_Long)128L),FIX((SI_Long)32L),
	    FIX((SI_Long)0L),FIX((SI_Long)5L));
    temp_4 = make_partial_buffer_info(FIX((SI_Long)256L),FIX((SI_Long)64L),
	    FIX((SI_Long)3L),FIX((SI_Long)6L));
    temp_1 = make_partial_buffer_info(FIX((SI_Long)512L),
	    FIX((SI_Long)128L),FIX((SI_Long)5L),FIX((SI_Long)7L));
    temp = make_partial_buffer_info(FIX((SI_Long)1024L),FIX((SI_Long)256L),
	    FIX((SI_Long)7L),FIX((SI_Long)8L));
    Environment_allocation_schemes = list(6,temp_2,temp_3,temp_4,temp_1,
	    temp,make_partial_buffer_info(FIX((SI_Long)2048L),
	    FIX((SI_Long)512L),FIX((SI_Long)9L),FIX((SI_Long)9L)));
    Maximum_environment_vector_length = FIX((SI_Long)1024L);
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_3 = 
	    STATIC_STRING("Error explicitly triggered from the C debugger.");
    if (Disassemble_enabled_qm == UNBOUND)
	Disassemble_enabled_qm = Nil;
    Qg2_enable_disassembler = STATIC_SYMBOL("G2-ENABLE-DISASSEMBLER",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_enable_disassembler,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_enable_disassembler,
	    STATIC_FUNCTION(g2_enable_disassembler,NIL,FALSE,0,0));
    Qg2_disable_disassembler = STATIC_SYMBOL("G2-DISABLE-DISASSEMBLER",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_disable_disassembler,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_disable_disassembler,
	    STATIC_FUNCTION(g2_disable_disassembler,NIL,FALSE,0,0));
    string_constant_4 = 
	    string_append2(STATIC_STRING("A floating point exception has occurred.  Floating point exceptions are ~\n     arithmetic errors such as dividing by zero, or overflowing or ~\n     underflowing floating point"),
	    STATIC_STRING(" number representations."));
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_56 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qerror,list_constant_56);
    string_constant_51 = STATIC_STRING("1n1m8v9k1l8t1l83Ly");
    string_constant_52 = 
	    STATIC_STRING("1p4z8r83Kdy83Kdy9k9k00001n1n8p83-dy83Gy1l8l1l8z000004z8r83Khy83Khy9k9k00001o1m8p83YZy1l8l1l8z1l83Fy000004z8r83Kiy83Kiy9k9k083JFy");
    string_constant_53 = 
	    STATIC_STRING("001o1m8p83Sy1l8l1l8z1l83Fy000004z8r83Kgy83Kgy9k9k083JEy001o1m8p83Sy1l8l1l8z1l83Fy000004z8r83Kjy83Kjy9k9k00001n1m8p01l8l1l83Hy000");
    string_constant_54 = STATIC_STRING("00");
    string_constant_55 = 
	    STATIC_STRING("1r8q1p9k1l83-Oy1m8v9k8t83Ly1p83Kdy01n8p83-dy83Gy8l8z1q83Khy01m8p83YZy8l8z83Fy1q83Kiy83JFy1m8p83Sy8l8z83Fy1q83Kgy83JEy1m8p83Sy8l8");
    string_constant_56 = STATIC_STRING("z83Fy1p83Kjy01m8p08l83Hy");
    clear_optimized_constants();
    push_optimized_constant(Qerror);
    temp = regenerate_optimized_constant(string_constant_51);
    clear_optimized_constants();
    push_optimized_constant(Qerror);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_52,
	    string_constant_53,string_constant_54));
    clear_optimized_constants();
    push_optimized_constant(Qerror);
    add_class_to_environment(9,Qerror,list_constant_56,Nil,temp,Nil,temp_1,
	    list_constant_56,
	    regenerate_optimized_constant(LIST_2(string_constant_55,
	    string_constant_56)),Nil);
    Qerror_description = STATIC_SYMBOL("ERROR-DESCRIPTION",AB_package);
    Qput_error_description = STATIC_SYMBOL("PUT-ERROR-DESCRIPTION",AB_package);
    SET_SYMBOL_FUNCTION(Qput_error_description,
	    STATIC_FUNCTION(put_error_description,NIL,FALSE,3,3));
    mutate_global_property(Qerror_description,
	    SYMBOL_FUNCTION(Qput_error_description),Qslot_putter);
    Qerror_source_trace = STATIC_SYMBOL("ERROR-SOURCE-TRACE",AB_package);
    temp_5 = CONS(Qerror_source_trace,All_virtual_attributes);
    All_virtual_attributes = temp_5;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qerror),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_5 = CONS(Qerror_source_trace,temp);
    set_property_value_function(get_symbol_properties_function(Qerror),
	    Qvirtual_attributes_local_to_class,temp_5);
    Qerror_trace = STATIC_SYMBOL("ERROR-TRACE",AB_package);
    Qerror_trace_description = STATIC_SYMBOL("ERROR-TRACE-DESCRIPTION",
	    AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_39,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qerror_trace_source_item = STATIC_SYMBOL("ERROR-TRACE-SOURCE-ITEM",
	    AB_package);
    Qerror_trace_source_line = STATIC_SYMBOL("ERROR-TRACE-SOURCE-LINE",
	    AB_package);
    Qerror_trace_source_column = STATIC_SYMBOL("ERROR-TRACE-SOURCE-COLUMN",
	    AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qab_class,Qerror);
    Qinitial_error_source_trace = 
	    STATIC_SYMBOL("INITIAL-ERROR-SOURCE-TRACE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_error_source_trace,
	    STATIC_FUNCTION(initial_error_source_trace,NIL,FALSE,1,1));
    Qget_error_source_trace = STATIC_SYMBOL("GET-ERROR-SOURCE-TRACE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_error_source_trace,
	    STATIC_FUNCTION(get_error_source_trace,NIL,FALSE,1,1));
    add_virtual_attribute(Qerror_source_trace,list_constant_57,
	    list_constant_3,Qnil,
	    SYMBOL_FUNCTION(Qinitial_error_source_trace),
	    SYMBOL_FUNCTION(Qget_error_source_trace),Nil);
    Qdefault_error = STATIC_SYMBOL("DEFAULT-ERROR",AB_package);
    list_constant_58 = STATIC_CONS(Qerror,Qnil);
    check_if_superior_classes_are_defined(Qdefault_error,list_constant_58);
    string_constant_57 = STATIC_STRING("1n1l8t1l83Iy1l83Ly");
    string_constant_58 = STATIC_STRING("0");
    string_constant_59 = STATIC_STRING("1m8q1p83upy1l9k8t83Iy83Ly");
    temp = regenerate_optimized_constant(string_constant_57);
    temp_1 = regenerate_optimized_constant(string_constant_58);
    clear_optimized_constants();
    push_optimized_constant(Qerror);
    add_class_to_environment(9,Qdefault_error,list_constant_58,Nil,temp,
	    Nil,temp_1,list_constant_58,
	    regenerate_optimized_constant(string_constant_59),Nil);
    Qg2_error = STATIC_SYMBOL("G2-ERROR",AB_package);
    check_if_superior_classes_are_defined(Qg2_error,list_constant_58);
    string_constant_60 = STATIC_STRING("1m8q1p835Gy1l9k8t83Iy83Ly");
    temp = regenerate_optimized_constant(string_constant_57);
    temp_1 = regenerate_optimized_constant(string_constant_58);
    clear_optimized_constants();
    push_optimized_constant(Qerror);
    add_class_to_environment(9,Qg2_error,list_constant_58,Nil,temp,Nil,
	    temp_1,list_constant_58,
	    regenerate_optimized_constant(string_constant_60),Nil);
    Qg2_rpc_error = STATIC_SYMBOL("G2-RPC-ERROR",AB_package);
    list_constant_59 = STATIC_CONS(Qg2_error,Qnil);
    check_if_superior_classes_are_defined(Qg2_rpc_error,list_constant_59);
    string_constant_61 = STATIC_STRING("1m8q1p83xey1l835Gy8t83Iy83Ly");
    temp = regenerate_optimized_constant(string_constant_57);
    temp_1 = regenerate_optimized_constant(string_constant_58);
    add_class_to_environment(9,Qg2_rpc_error,list_constant_59,Nil,temp,Nil,
	    temp_1,list_constant_59,
	    regenerate_optimized_constant(string_constant_61),Nil);
    Qg2_deadlock_error = STATIC_SYMBOL("G2-DEADLOCK-ERROR",AB_package);
    check_if_superior_classes_are_defined(Qg2_deadlock_error,list_constant_59);
    string_constant_62 = STATIC_STRING("1m8q1p83xRy1l835Gy8t83Iy83Ly");
    temp = regenerate_optimized_constant(string_constant_57);
    temp_1 = regenerate_optimized_constant(string_constant_58);
    add_class_to_environment(9,Qg2_deadlock_error,list_constant_59,Nil,
	    temp,Nil,temp_1,list_constant_59,
	    regenerate_optimized_constant(string_constant_62),Nil);
    Qrpc_error = STATIC_SYMBOL("RPC-ERROR",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qerror_source_item = STATIC_SYMBOL("ERROR-SOURCE-ITEM",AB_package);
    Qerror_source_line = STATIC_SYMBOL("ERROR-SOURCE-LINE",AB_package);
    Qerror_source_column = STATIC_SYMBOL("ERROR-SOURCE-COLUMN",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    string_constant_5 = STATIC_STRING("~A");
    Qcurrent_profile_structure_qm = 
	    STATIC_SYMBOL("CURRENT-PROFILE-STRUCTURE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_profile_structure_qm,
	    Current_profile_structure_qm);
    record_system_variable(Qcurrent_profile_structure_qm,Qsets,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    string_constant_6 = STATIC_STRING("~a");
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qprofiling_structure = STATIC_SYMBOL("PROFILING-STRUCTURE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprofiling_structure,Profiling_structure);
    record_system_variable(Qprofiling_structure,Qsets,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_7 = STATIC_STRING("No Profiling Information~a");
    string_constant_8 = STATIC_STRING(" ");
    string_constant_9 = STATIC_STRING(" ~a Items profiled");
    Qg2_profiled_call_information = 
	    STATIC_SYMBOL("G2-PROFILED-CALL-INFORMATION",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_profiled_call_information,
	    STATIC_FUNCTION(g2_profiled_call_information,NIL,FALSE,0,0));
    Qdisplay_profiling_names = STATIC_SYMBOL("DISPLAY-PROFILING-NAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdisplay_profiling_names,
	    Display_profiling_names);
    Qexecute_message_removal_task = 
	    STATIC_SYMBOL("EXECUTE-MESSAGE-REMOVAL-TASK",AB_package);
    Qredraw_solid_rectangles_without_overlap = 
	    STATIC_SYMBOL("REDRAW-SOLID-RECTANGLES-WITHOUT-OVERLAP",
	    AB_package);
    Qrefresh_window = STATIC_SYMBOL("REFRESH-WINDOW",AB_package);
    Qscheduled_display_update = STATIC_SYMBOL("SCHEDULED-DISPLAY-UPDATE",
	    AB_package);
    Qunhighlight_recent_message = 
	    STATIC_SYMBOL("UNHIGHLIGHT-RECENT-MESSAGE",AB_package);
    Qupdate_chart = STATIC_SYMBOL("UPDATE-CHART",AB_package);
    Qupdate_display_if_not_reprocessed = 
	    STATIC_SYMBOL("UPDATE-DISPLAY-IF-NOT-REPROCESSED",AB_package);
    Qscheduled_update_button = STATIC_SYMBOL("SCHEDULED-UPDATE-BUTTON",
	    AB_package);
    Qscrolling_heartbeat = STATIC_SYMBOL("SCROLLING-HEARTBEAT",AB_package);
    Qupdate_display_for_digital_clock = 
	    STATIC_SYMBOL("UPDATE-DISPLAY-FOR-DIGITAL-CLOCK",AB_package);
    Qupdate_display_for_graph = STATIC_SYMBOL("UPDATE-DISPLAY-FOR-GRAPH",
	    AB_package);
    Qupdate_trend_chart_task = STATIC_SYMBOL("UPDATE-TREND-CHART-TASK",
	    AB_package);
    Qverify_and_set_variable_per_non_action_button = 
	    STATIC_SYMBOL("VERIFY-AND-SET-VARIABLE-PER-NON-ACTION-BUTTON",
	    AB_package);
    Qwork_on_schedule_of_table_updates_a_little = 
	    STATIC_SYMBOL("WORK-ON-SCHEDULE-OF-TABLE-UPDATES-A-LITTLE",
	    AB_package);
    Qresume_search_task_in_workstation = 
	    STATIC_SYMBOL("RESUME-SEARCH-TASK-IN-WORKSTATION",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)15L,
	    Qexecute_message_removal_task,
	    Qredraw_solid_rectangles_without_overlap,Qrefresh_window,
	    Qscheduled_display_update,Qunhighlight_recent_message,
	    Qupdate_chart,Qupdate_display_if_not_reprocessed,
	    Qscheduled_update_button,Qscrolling_heartbeat,
	    Qupdate_display_for_digital_clock,Qupdate_display_for_graph,
	    Qupdate_trend_chart_task,
	    Qverify_and_set_variable_per_non_action_button,
	    Qwork_on_schedule_of_table_updates_a_little,
	    Qresume_search_task_in_workstation);
    SET_SYMBOL_VALUE(Qdisplay_profiling_names,list_constant_60);
    Qscheduling_profiling_names = 
	    STATIC_SYMBOL("SCHEDULING-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscheduling_profiling_names,
	    Scheduling_profiling_names);
    Qattempt_expression_cell_execution = 
	    STATIC_SYMBOL("ATTEMPT-EXPRESSION-CELL-EXECUTION",AB_package);
    Qexecute_backward_chaining_for_rules = 
	    STATIC_SYMBOL("EXECUTE-BACKWARD-CHAINING-FOR-RULES",AB_package);
    Qexecute_computation_instance = 
	    STATIC_SYMBOL("EXECUTE-COMPUTATION-INSTANCE",AB_package);
    Qinvoke_rule_universally = STATIC_SYMBOL("INVOKE-RULE-UNIVERSALLY",
	    AB_package);
    Qschedule_computation_instance_execution = 
	    STATIC_SYMBOL("SCHEDULE-COMPUTATION-INSTANCE-EXECUTION",
	    AB_package);
    Qschedule_initial_rules_from_activated_kb_workspace = 
	    STATIC_SYMBOL("SCHEDULE-INITIAL-RULES-FROM-ACTIVATED-KB-WORKSPACE",
	    AB_package);
    Qwake_up_code_body_invocation = 
	    STATIC_SYMBOL("WAKE-UP-CODE-BODY-INVOCATION",AB_package);
    Qcomplete_initial_rules = STATIC_SYMBOL("COMPLETE-INITIAL-RULES",
	    AB_package);
    Qgfi_output_event_log_values_periodically_task = 
	    STATIC_SYMBOL("GFI-OUTPUT-EVENT-LOG-VALUES-PERIODICALLY-TASK",
	    AB_package);
    Qgfi_output_spreadsheet_values_periodically_task = 
	    STATIC_SYMBOL("GFI-OUTPUT-SPREADSHEET-VALUES-PERIODICALLY-TASK",
	    AB_package);
    Qpropagate_variable_value_expiration = 
	    STATIC_SYMBOL("PROPAGATE-VARIABLE-VALUE-EXPIRATION",AB_package);
    Qsafe_invoke_rules_for_existential_chaining = 
	    STATIC_SYMBOL("SAFE-INVOKE-RULES-FOR-EXISTENTIAL-CHAINING",
	    AB_package);
    Qimmediately_return_from_breakpoint = 
	    STATIC_SYMBOL("IMMEDIATELY-RETURN-FROM-BREAKPOINT",AB_package);
    Qexecute_scheduled_remote_procedure_start = 
	    STATIC_SYMBOL("EXECUTE-SCHEDULED-REMOTE-PROCEDURE-START",
	    AB_package);
    Qreceive_start_or_call_remote_procedure_1 = 
	    STATIC_SYMBOL("RECEIVE-START-OR-CALL-REMOTE-PROCEDURE-1",
	    AB_package);
    Qreceive_nupec_synchronize_task = 
	    STATIC_SYMBOL("RECEIVE-NUPEC-SYNCHRONIZE-TASK",AB_package);
    list_constant_61 = STATIC_LIST((SI_Long)16L,
	    Qattempt_expression_cell_execution,
	    Qexecute_backward_chaining_for_rules,
	    Qexecute_computation_instance,Qinvoke_rule_universally,
	    Qschedule_computation_instance_execution,
	    Qschedule_initial_rules_from_activated_kb_workspace,
	    Qwake_up_code_body_invocation,Qcomplete_initial_rules,
	    Qgfi_output_event_log_values_periodically_task,
	    Qgfi_output_spreadsheet_values_periodically_task,
	    Qpropagate_variable_value_expiration,
	    Qsafe_invoke_rules_for_existential_chaining,
	    Qimmediately_return_from_breakpoint,
	    Qexecute_scheduled_remote_procedure_start,
	    Qreceive_start_or_call_remote_procedure_1,
	    Qreceive_nupec_synchronize_task);
    SET_SYMBOL_VALUE(Qscheduling_profiling_names,list_constant_61);
    Qdata_service_profiling_names = 
	    STATIC_SYMBOL("DATA-SERVICE-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_service_profiling_names,
	    Data_service_profiling_names);
    Qaccept_data_and_reschedule_if_necessary = 
	    STATIC_SYMBOL("ACCEPT-DATA-AND-RESCHEDULE-IF-NECESSARY",
	    AB_package);
    Qcall_data_server_accept_data_functions = 
	    STATIC_SYMBOL("CALL-DATA-SERVER-ACCEPT-DATA-FUNCTIONS",AB_package);
    Qcollect_one_shot_data_for_g2_meters = 
	    STATIC_SYMBOL("COLLECT-ONE-SHOT-DATA-FOR-G2-METERS",AB_package);
    Qcollect_one_shot_data_for_gfi_data_service = 
	    STATIC_SYMBOL("COLLECT-ONE-SHOT-DATA-FOR-GFI-DATA-SERVICE",
	    AB_package);
    Qcontinue_data_server_data_acceptance = 
	    STATIC_SYMBOL("CONTINUE-DATA-SERVER-DATA-ACCEPTANCE",AB_package);
    Qenqueue_gsi_request_for_sensor = 
	    STATIC_SYMBOL("ENQUEUE-GSI-REQUEST-FOR-SENSOR",AB_package);
    Qg2ds_begin_collecting_data = 
	    STATIC_SYMBOL("G2DS-BEGIN-COLLECTING-DATA",AB_package);
    Qg2ds_collect_one_shot_data = 
	    STATIC_SYMBOL("G2DS-COLLECT-ONE-SHOT-DATA",AB_package);
    Qinitiate_inter_g2_set_value_request = 
	    STATIC_SYMBOL("INITIATE-INTER-G2-SET-VALUE-REQUEST",AB_package);
    Qinitiate_inter_g2_data_service_request = 
	    STATIC_SYMBOL("INITIATE-INTER-G2-DATA-SERVICE-REQUEST",AB_package);
    Qkill_foreign_image_process_unconditionally = 
	    STATIC_SYMBOL("KILL-FOREIGN-IMAGE-PROCESS-UNCONDITIONALLY",
	    AB_package);
    Qperform_background_collection_for_inference_engine = 
	    STATIC_SYMBOL("PERFORM-BACKGROUND-COLLECTION-FOR-INFERENCE-ENGINE",
	    AB_package);
    Qprocess_g2ds_variable_values = 
	    STATIC_SYMBOL("PROCESS-G2DS-VARIABLE-VALUES",AB_package);
    Qprocess_gsi_sensor_values = STATIC_SYMBOL("PROCESS-GSI-SENSOR-VALUES",
	    AB_package);
    Qprocess_requests_for_gsi_interfaces = 
	    STATIC_SYMBOL("PROCESS-REQUESTS-FOR-GSI-INTERFACES",AB_package);
    Qreturn_values_to_g2ds_client_task = 
	    STATIC_SYMBOL("RETURN-VALUES-TO-G2DS-CLIENT-TASK",AB_package);
    Qtask_to_detect_failure = STATIC_SYMBOL("TASK-TO-DETECT-FAILURE",
	    AB_package);
    Qtask_to_probe_failed_variable = 
	    STATIC_SYMBOL("TASK-TO-PROBE-FAILED-VARIABLE",AB_package);
    list_constant_62 = STATIC_LIST((SI_Long)18L,
	    Qaccept_data_and_reschedule_if_necessary,
	    Qcall_data_server_accept_data_functions,
	    Qcollect_one_shot_data_for_g2_meters,
	    Qcollect_one_shot_data_for_gfi_data_service,
	    Qcontinue_data_server_data_acceptance,
	    Qenqueue_gsi_request_for_sensor,Qg2ds_begin_collecting_data,
	    Qg2ds_collect_one_shot_data,
	    Qinitiate_inter_g2_set_value_request,
	    Qinitiate_inter_g2_data_service_request,
	    Qkill_foreign_image_process_unconditionally,
	    Qperform_background_collection_for_inference_engine,
	    Qprocess_g2ds_variable_values,Qprocess_gsi_sensor_values,
	    Qprocess_requests_for_gsi_interfaces,
	    Qreturn_values_to_g2ds_client_task,Qtask_to_detect_failure,
	    Qtask_to_probe_failed_variable);
    SET_SYMBOL_VALUE(Qdata_service_profiling_names,list_constant_62);
    Qkb_io_profiling_names = STATIC_SYMBOL("KB-IO-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_io_profiling_names,Kb_io_profiling_names);
    Qcontinuation_task_for_current_backup = 
	    STATIC_SYMBOL("CONTINUATION-TASK-FOR-CURRENT-BACKUP",AB_package);
    Qcontinue_current_kb_save_or_backup = 
	    STATIC_SYMBOL("CONTINUE-CURRENT-KB-SAVE-OR-BACKUP",AB_package);
    Qterminate_kb_save_or_backup = 
	    STATIC_SYMBOL("TERMINATE-KB-SAVE-OR-BACKUP",AB_package);
    Qsys_proc_read_kb = STATIC_SYMBOL("SYS-PROC-READ-KB",AB_package);
    list_constant_63 = STATIC_LIST((SI_Long)4L,
	    Qcontinuation_task_for_current_backup,
	    Qcontinue_current_kb_save_or_backup,
	    Qterminate_kb_save_or_backup,Qsys_proc_read_kb);
    SET_SYMBOL_VALUE(Qkb_io_profiling_names,list_constant_63);
    Qicp_profiling_names = STATIC_SYMBOL("ICP-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qicp_profiling_names,Icp_profiling_names);
    Qhandle_queued_icp_messages_task = 
	    STATIC_SYMBOL("HANDLE-QUEUED-ICP-MESSAGES-TASK",AB_package);
    Qhandle_read_event_function = 
	    STATIC_SYMBOL("HANDLE-READ-EVENT-FUNCTION",AB_package);
    Qhandle_write_event_function = 
	    STATIC_SYMBOL("HANDLE-WRITE-EVENT-FUNCTION",AB_package);
    Qhandle_close_event = STATIC_SYMBOL("HANDLE-CLOSE-EVENT",AB_package);
    Qsend_i_am_alive_message = STATIC_SYMBOL("SEND-I-AM-ALIVE-MESSAGE",
	    AB_package);
    Qhandle_unclogged_connection_if_necessary = 
	    STATIC_SYMBOL("HANDLE-UNCLOGGED-CONNECTION-IF-NECESSARY",
	    AB_package);
    Qresumable_icp_write_callback = 
	    STATIC_SYMBOL("RESUMABLE-ICP-WRITE-CALLBACK",AB_package);
    Qtime_out_icp_socket = STATIC_SYMBOL("TIME-OUT-ICP-SOCKET",AB_package);
    Qicp_connection_timeout_task_1 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-1",AB_package);
    Qicp_connection_timeout_task_2 = 
	    STATIC_SYMBOL("ICP-CONNECTION-TIMEOUT-TASK-2",AB_package);
    Qtry_to_preflight_resumable_object = 
	    STATIC_SYMBOL("TRY-TO-PREFLIGHT-RESUMABLE-OBJECT",AB_package);
    Qtry_to_transmit_resumable_object = 
	    STATIC_SYMBOL("TRY-TO-TRANSMIT-RESUMABLE-OBJECT",AB_package);
    Qsend_queued_reclaim_index_space_messages = 
	    STATIC_SYMBOL("SEND-QUEUED-RECLAIM-INDEX-SPACE-MESSAGES",
	    AB_package);
    Qsend_new_trend_chart_data_task = 
	    STATIC_SYMBOL("SEND-NEW-TREND-CHART-DATA-TASK",AB_package);
    Qsocket_close_cleanups = STATIC_SYMBOL("SOCKET-CLOSE-CLEANUPS",AB_package);
    list_constant_64 = STATIC_LIST((SI_Long)15L,
	    Qhandle_queued_icp_messages_task,Qhandle_read_event_function,
	    Qhandle_write_event_function,Qhandle_close_event,
	    Qsend_i_am_alive_message,
	    Qhandle_unclogged_connection_if_necessary,
	    Qresumable_icp_write_callback,Qtime_out_icp_socket,
	    Qicp_connection_timeout_task_1,Qicp_connection_timeout_task_2,
	    Qtry_to_preflight_resumable_object,
	    Qtry_to_transmit_resumable_object,
	    Qsend_queued_reclaim_index_space_messages,
	    Qsend_new_trend_chart_data_task,Qsocket_close_cleanups);
    SET_SYMBOL_VALUE(Qicp_profiling_names,list_constant_64);
    Qworkstation_profiling_names = 
	    STATIC_SYMBOL("WORKSTATION-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qworkstation_profiling_names,
	    Workstation_profiling_names);
    Qpropagate_all_workspace_changes_to_image_planes = 
	    STATIC_SYMBOL("PROPAGATE-ALL-WORKSPACE-CHANGES-TO-IMAGE-PLANES",
	    AB_package);
    Qpropagate_allow_scheduled_drawing_1 = 
	    STATIC_SYMBOL("PROPAGATE-ALLOW-SCHEDULED-DRAWING-1",AB_package);
    Qrun_selection_callbacks = STATIC_SYMBOL("RUN-SELECTION-CALLBACKS",
	    AB_package);
    Qrun_area_selected_callbacks = 
	    STATIC_SYMBOL("RUN-AREA-SELECTED-CALLBACKS",AB_package);
    Qrun_workspace_callbacks = STATIC_SYMBOL("RUN-WORKSPACE-CALLBACKS",
	    AB_package);
    Qservice_workstations_final = 
	    STATIC_SYMBOL("SERVICE-WORKSTATIONS-FINAL",AB_package);
    Qservice_workstation = STATIC_SYMBOL("SERVICE-WORKSTATION",AB_package);
    list_constant_65 = STATIC_LIST((SI_Long)7L,
	    Qpropagate_all_workspace_changes_to_image_planes,
	    Qpropagate_allow_scheduled_drawing_1,Qrun_selection_callbacks,
	    Qrun_area_selected_callbacks,Qrun_workspace_callbacks,
	    Qservice_workstations_final,Qservice_workstation);
    SET_SYMBOL_VALUE(Qworkstation_profiling_names,list_constant_65);
    Qoverhead_kb_profiling_names = 
	    STATIC_SYMBOL("OVERHEAD-KB-PROFILING-NAMES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qoverhead_kb_profiling_names,
	    Overhead_kb_profiling_names);
    Qcompletely_shut_down_g2 = STATIC_SYMBOL("COMPLETELY-SHUT-DOWN-G2",
	    AB_package);
    Qwarn_user_of_previously_aborted_g2 = 
	    STATIC_SYMBOL("WARN-USER-OF-PREVIOUSLY-ABORTED-G2",AB_package);
    Qcall_post_prominent_notification = 
	    STATIC_SYMBOL("CALL-POST-PROMINENT-NOTIFICATION",AB_package);
    Qdo_legacy_multisecond_heartbeat_adjustments = 
	    STATIC_SYMBOL("DO-LEGACY-MULTISECOND-HEARTBEAT-ADJUSTMENTS",
	    AB_package);
    Qdo_legacy_subsecond_heartbeat_adjustments = 
	    STATIC_SYMBOL("DO-LEGACY-SUBSECOND-HEARTBEAT-ADJUSTMENTS",
	    AB_package);
    Qinitialize_for_asian_languages = 
	    STATIC_SYMBOL("INITIALIZE-FOR-ASIAN-LANGUAGES",AB_package);
    Qnative_window_heartbeat = STATIC_SYMBOL("NATIVE-WINDOW-HEARTBEAT",
	    AB_package);
    Qservice_background_processes = 
	    STATIC_SYMBOL("SERVICE-BACKGROUND-PROCESSES",AB_package);
    Qwarn_about_editing_item = STATIC_SYMBOL("WARN-ABOUT-EDITING-ITEM",
	    AB_package);
    Qsystem_state_change_from_scheduler_1 = 
	    STATIC_SYMBOL("SYSTEM-STATE-CHANGE-FROM-SCHEDULER-1",AB_package);
    Qdetect_and_break_deadlocks = 
	    STATIC_SYMBOL("DETECT-AND-BREAK-DEADLOCKS",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)11L,Qcompletely_shut_down_g2,
	    Qwarn_user_of_previously_aborted_g2,
	    Qcall_post_prominent_notification,
	    Qdo_legacy_multisecond_heartbeat_adjustments,
	    Qdo_legacy_subsecond_heartbeat_adjustments,
	    Qinitialize_for_asian_languages,Qnative_window_heartbeat,
	    Qservice_background_processes,Qwarn_about_editing_item,
	    Qsystem_state_change_from_scheduler_1,Qdetect_and_break_deadlocks);
    SET_SYMBOL_VALUE(Qoverhead_kb_profiling_names,list_constant_66);
    Qg2gl_profiling_lists = STATIC_SYMBOL("G2GL-PROFILING-LISTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2gl_profiling_lists,G2gl_profiling_lists);
    Qcontinue_execution_of_thread = 
	    STATIC_SYMBOL("CONTINUE-EXECUTION-OF-THREAD",AB_package);
    Qcontinue_scheduled_process_invocation = 
	    STATIC_SYMBOL("CONTINUE-SCHEDULED-PROCESS-INVOCATION",AB_package);
    list_constant_67 = STATIC_LIST((SI_Long)2L,
	    Qcontinue_execution_of_thread,
	    Qcontinue_scheduled_process_invocation);
    SET_SYMBOL_VALUE(Qg2gl_profiling_lists,list_constant_67);
    Qg2_system_profile = STATIC_SYMBOL("G2-SYSTEM-PROFILE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_system_profile,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qquantity_list = STATIC_SYMBOL("QUANTITY-LIST",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    SET_SYMBOL_FUNCTION(Qg2_system_profile,
	    STATIC_FUNCTION(g2_system_profile,NIL,FALSE,0,0));
    Qg2_procedure_detail = STATIC_SYMBOL("G2-PROCEDURE-DETAIL",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_procedure_detail,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_procedure_detail,
	    STATIC_FUNCTION(g2_procedure_detail,NIL,FALSE,1,1));
    if (Registered_activities_symbol_array == UNBOUND)
	Registered_activities_symbol_array = Nil;
    create_registered_activities_symbol_array();
    Qg2_procedure_activity_list = 
	    STATIC_SYMBOL("G2-PROCEDURE-ACTIVITY-LIST",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_procedure_activity_list,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsymbol_list = STATIC_SYMBOL("SYMBOL-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_procedure_activity_list,
	    STATIC_FUNCTION(g2_procedure_activity_list,NIL,FALSE,1,1));
    if (Limit_profiling_based_on_licence_level_p == UNBOUND)
	Limit_profiling_based_on_licence_level_p = T;
    Qg2_allow_profiling_regardless_of_license = 
	    STATIC_SYMBOL("G2-ALLOW-PROFILING-REGARDLESS-OF-LICENSE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_allow_profiling_regardless_of_license,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_allow_profiling_regardless_of_license,
	    STATIC_FUNCTION(g2_allow_profiling_regardless_of_license,NIL,
	    FALSE,0,0));
    Qg2_user_name_for_frame = STATIC_SYMBOL("G2-USER-NAME-FOR-FRAME",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_user_name_for_frame,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_user_name_for_frame,
	    STATIC_FUNCTION(g2_user_name_for_frame,NIL,FALSE,1,1));
    Qg2_procedure_activity_calls = 
	    STATIC_SYMBOL("G2-PROCEDURE-ACTIVITY-CALLS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_procedure_activity_calls,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_10 = 
	    STATIC_STRING("Attempt to invoke unlicensed system procedure.");
    SET_SYMBOL_FUNCTION(Qg2_procedure_activity_calls,
	    STATIC_FUNCTION(g2_procedure_activity_calls,NIL,FALSE,2,2));
    Qg2_system_profiled_items = STATIC_SYMBOL("G2-SYSTEM-PROFILED-ITEMS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_system_profiled_items,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_system_profiled_items,
	    STATIC_FUNCTION(g2_system_profiled_items,NIL,FALSE,0,0));
    Qg2_enable_system_profiling = 
	    STATIC_SYMBOL("G2-ENABLE-SYSTEM-PROFILING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_enable_system_profiling,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_enable_system_profiling,
	    STATIC_FUNCTION(g2_enable_system_profiling,NIL,FALSE,0,0));
    Qg2_disable_system_profiling = 
	    STATIC_SYMBOL("G2-DISABLE-SYSTEM-PROFILING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_disable_system_profiling,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_disable_system_profiling,
	    STATIC_FUNCTION(g2_disable_system_profiling,NIL,FALSE,0,0));
    Qg2_toggle_system_profiling = 
	    STATIC_SYMBOL("G2-TOGGLE-SYSTEM-PROFILING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_toggle_system_profiling,
	    STATIC_FUNCTION(g2_toggle_system_profiling,NIL,FALSE,0,0));
    Qg2_clear_profiling = STATIC_SYMBOL("G2-CLEAR-PROFILING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_clear_profiling,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clear_profiling,
	    STATIC_FUNCTION(g2_clear_profiling,NIL,FALSE,0,0));
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qreturn_from_save_to_caller_for_continuation_qm = 
	    STATIC_SYMBOL("RETURN-FROM-SAVE-TO-CALLER-FOR-CONTINUATION\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreturn_from_save_to_caller_for_continuation_qm,
	    Return_from_save_to_caller_for_continuation_qm);
    record_system_variable(Qreturn_from_save_to_caller_for_continuation_qm,
	    Qsets,Nil,Qnil,Qnil,Qnil,Qnil);
    Qkb_save_termination_reason_qm = 
	    STATIC_SYMBOL("KB-SAVE-TERMINATION-REASON\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_save_termination_reason_qm,
	    Kb_save_termination_reason_qm);
    record_system_variable(Qkb_save_termination_reason_qm,Qsets,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qsuppress_notification_for_kb_save_qm = 
	    STATIC_SYMBOL("SUPPRESS-NOTIFICATION-FOR-KB-SAVE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsuppress_notification_for_kb_save_qm,
	    Suppress_notification_for_kb_save_qm);
    record_system_variable(Qsuppress_notification_for_kb_save_qm,Qsets,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qterminate_kb_save_stream_error_message_qm = 
	    STATIC_SYMBOL("TERMINATE-KB-SAVE-STREAM-ERROR-MESSAGE\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qterminate_kb_save_stream_error_message_qm,
	    Terminate_kb_save_stream_error_message_qm);
    record_system_variable(Qterminate_kb_save_stream_error_message_qm,
	    Qsets,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsave_kb_state_for_system_procedure_save = 
	    STATIC_SYMBOL("SAVE-KB-STATE-FOR-SYSTEM-PROCEDURE-SAVE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsave_kb_state_for_system_procedure_save,
	    Save_kb_state_for_system_procedure_save);
    record_system_variable(Qsave_kb_state_for_system_procedure_save,Qsets,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2_save_module_extended = STATIC_SYMBOL("G2-SAVE-MODULE-EXTENDED",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_module_extended,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_11 = STATIC_STRING("Save is already in progress.");
    array_constant_2 = STATIC_ARRAY(list_constant_39,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)31L,(SI_Long)57344L);
    Qin_progress = STATIC_SYMBOL("IN-PROGRESS",AB_package);
    Qcleanup_kb_save_or_backup_if_necessary = 
	    STATIC_SYMBOL("CLEANUP-KB-SAVE-OR-BACKUP-IF-NECESSARY",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_kb_save_or_backup_if_necessary,
	    STATIC_FUNCTION(cleanup_kb_save_or_backup_if_necessary,NIL,
	    FALSE,1,1));
    list_constant_30 = STATIC_CONS(Qcleanup_kb_save_or_backup_if_necessary,
	    Qnil);
    Qfile_progress_display = STATIC_SYMBOL("FILE-PROGRESS-DISPLAY",AB_package);
    Qinclude_required_modules = STATIC_SYMBOL("INCLUDE-REQUIRED-MODULES",
	    AB_package);
    Qusing_clear_text = STATIC_SYMBOL("USING-CLEAR-TEXT",AB_package);
    Qemitting_c_code = STATIC_SYMBOL("EMITTING-C-CODE",AB_package);
    Qlog_message_for_commit_after_saving = 
	    STATIC_SYMBOL("LOG-MESSAGE-FOR-COMMIT-AFTER-SAVING",AB_package);
    Qfile_command = STATIC_SYMBOL("FILE-COMMAND",AB_package);
    Qincluding_all_required_modules = 
	    STATIC_SYMBOL("INCLUDING-ALL-REQUIRED-MODULES",AB_package);
    Qcommit_after_saving = STATIC_SYMBOL("COMMIT-AFTER-SAVING",AB_package);
    Qsave_module = STATIC_SYMBOL("SAVE-MODULE",AB_package);
    Qfailed = STATIC_SYMBOL("FAILED",AB_package);
    Qread_only = STATIC_SYMBOL("READ-ONLY",AB_package);
    string_constant_12 = STATIC_STRING("Terminating save");
    Qnever_opened = STATIC_SYMBOL("NEVER-OPENED",AB_package);
    Qab_continue = STATIC_SYMBOL("CONTINUE",AB_package);
    Qok = STATIC_SYMBOL("OK",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_save_module_extended,
	    STATIC_FUNCTION(g2_save_module_extended,NIL,FALSE,4,4));
    if (G2_save_module_list == UNBOUND)
	G2_save_module_list = Nil;
    if (G2_save_module_flag == UNBOUND)
	G2_save_module_flag = Nil;
    Qset_g2_save_module_flag = STATIC_SYMBOL("SET-G2-SAVE-MODULE-FLAG",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qset_g2_save_module_flag,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qset_g2_save_module_flag,
	    STATIC_FUNCTION(set_g2_save_module_flag,NIL,FALSE,0,0));
    Qreset_g2_save_module_flag = STATIC_SYMBOL("RESET-G2-SAVE-MODULE-FLAG",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qreset_g2_save_module_flag,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qreset_g2_save_module_flag,
	    STATIC_FUNCTION(reset_g2_save_module_flag,NIL,FALSE,0,0));
    Qis_g2_save_module_flag_set = 
	    STATIC_SYMBOL("IS-G2-SAVE-MODULE-FLAG-SET",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qis_g2_save_module_flag_set,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qis_g2_save_module_flag_set,
	    STATIC_FUNCTION(is_g2_save_module_flag_set,NIL,FALSE,0,0));
    Qg2_save_module = STATIC_SYMBOL("G2-SAVE-MODULE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_save_module,STATIC_FUNCTION(g2_save_module,NIL,
	    FALSE,5,5));
    Qg2_reclaim_save_module_memory = 
	    STATIC_SYMBOL("G2-RECLAIM-SAVE-MODULE-MEMORY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_reclaim_save_module_memory,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_reclaim_save_module_memory,
	    STATIC_FUNCTION(g2_reclaim_save_module_memory,NIL,FALSE,0,0));
    Qg2_save_kb = STATIC_SYMBOL("G2-SAVE-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    Qsave_kb_with_runtime_data = STATIC_SYMBOL("SAVE-KB-WITH-RUNTIME-DATA",
	    AB_package);
    Qkb_save_with_runtime_data = STATIC_SYMBOL("KB-SAVE-WITH-RUNTIME-DATA",
	    AB_package);
    string_constant_13 = 
	    STATIC_STRING("The symbol ~a is not a valid argument for SAVE-KB.");
    SET_SYMBOL_FUNCTION(Qg2_save_kb,STATIC_FUNCTION(g2_save_kb,NIL,FALSE,4,4));
    Qg2_continue_save_kb = STATIC_SYMBOL("G2-CONTINUE-SAVE-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_continue_save_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qfinish = STATIC_SYMBOL("FINISH",AB_package);
    Qfinished = STATIC_SYMBOL("FINISHED",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_continue_save_kb,
	    STATIC_FUNCTION(g2_continue_save_kb,NIL,FALSE,1,1));
    Qg2_finish_save_kb = STATIC_SYMBOL("G2-FINISH-SAVE-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_finish_save_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_finish_save_kb,
	    STATIC_FUNCTION(g2_finish_save_kb,NIL,FALSE,1,1));
    Qg2_save_kb_without_other_processing = 
	    STATIC_SYMBOL("G2-SAVE-KB-WITHOUT-OTHER-PROCESSING",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_kb_without_other_processing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_save_kb_without_other_processing,
	    STATIC_FUNCTION(g2_save_kb_without_other_processing,NIL,FALSE,
	    4,4));
    Qg2_save_module_extended_without_other_processing = 
	    STATIC_SYMBOL("G2-SAVE-MODULE-EXTENDED-WITHOUT-OTHER-PROCESSING",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_module_extended_without_other_processing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_save_module_extended_without_other_processing,
	    STATIC_FUNCTION(g2_save_module_extended_without_other_processing,
	    NIL,FALSE,4,4));
    Qg2_save_module_without_other_processing = 
	    STATIC_SYMBOL("G2-SAVE-MODULE-WITHOUT-OTHER-PROCESSING",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_save_module_without_other_processing,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_save_module_without_other_processing,
	    STATIC_FUNCTION(g2_save_module_without_other_processing,NIL,
	    FALSE,5,5));
    Qg2_delete_module = STATIC_SYMBOL("G2-DELETE-MODULE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Quilroot = STATIC_SYMBOL("UILROOT",AB_package);
    string_constant_14 = 
	    string_append2(STATIC_STRING("The system procedure g2-delete-module cannot be called with ~\n         the module set to UILROOT and delete-associated-workspaces\? ~\n         set to TRUE because g2-delete-mod"),
	    STATIC_STRING("ule will also be deleted. ~\n         The call should be successful when delete-associated-workspaces\? ~\n         is set to FALSE."));
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    string_constant_15 = 
	    STATIC_STRING("The system procedure g2-delete-module cannot be called to delete a module which contains the calling procedure.");
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    string_constant_16 = 
	    string_append2(STATIC_STRING("The system procedure g2-delete-module cannot be called with ~\n               the module set to ~A and delete-associated-workspaces\? ~\n               set to TRUE because g2-del"),
	    STATIC_STRING("ete-module will also be deleted. ~\n               The call should be successful when delete-associated-workspaces\? ~\n               is set to FALSE."));
    string_constant_17 = 
	    string_append2(STATIC_STRING("Cannot call g2-delete-module to delete module ~a with ~\n               delete-associated-workspaces\? set to TRUE because ~\n               a procedure in the calling chain, ~a,"),
	    STATIC_STRING(" is in ~a. ~\n               The call should be successful when ~\n               delete-associated-workspaces\? is set to FALSE."));
    SET_SYMBOL_FUNCTION(Qg2_delete_module,STATIC_FUNCTION(g2_delete_module,
	    NIL,FALSE,2,2));
    Qg2_create_module = STATIC_SYMBOL("G2-CREATE-MODULE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_create_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_create_module,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qmodule_name_in_use = STATIC_SYMBOL("MODULE-NAME-IN-USE",AB_package);
    string_constant_18 = STATIC_STRING("the name is already in use.");
    Qmodule_name_is_reserved_word = 
	    STATIC_SYMBOL("MODULE-NAME-IS-RESERVED-WORD",AB_package);
    string_constant_19 = STATIC_STRING("the name is a reserved word.");
    Qmodule_name_unspecified = STATIC_SYMBOL("MODULE-NAME-UNSPECIFIED",
	    AB_package);
    string_constant_20 = 
	    STATIC_STRING("a module\'s name cannot be unspecified unless it\'s the top-level module");
    string_constant_21 = STATIC_STRING("reason unknown.");
    string_constant_22 = 
	    STATIC_STRING("Creation of module with name ~a failed; ~a");
    SET_SYMBOL_FUNCTION(Qg2_create_module,STATIC_FUNCTION(g2_create_module,
	    NIL,FALSE,1,1));
    Qg2_modules_with_unsaved_changes = 
	    STATIC_SYMBOL("G2-MODULES-WITH-UNSAVED-CHANGES",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_modules_with_unsaved_changes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_modules_with_unsaved_changes,
	    STATIC_FUNCTION(g2_modules_with_unsaved_changes,NIL,FALSE,0,0));
    Qg2_load_kb_extended = STATIC_SYMBOL("G2-LOAD-KB-EXTENDED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_load_kb_extended,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qresolve_conflicts_automatically = 
	    STATIC_SYMBOL("RESOLVE-CONFLICTS-AUTOMATICALLY",AB_package);
    Qbring_formats_up_to_date = STATIC_SYMBOL("BRING-FORMATS-UP-TO-DATE",
	    AB_package);
    Qupdate_before_loading = STATIC_SYMBOL("UPDATE-BEFORE-LOADING",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_load_kb_extended,
	    STATIC_FUNCTION(g2_load_kb_extended,NIL,FALSE,2,2));
    Qg2_load_kb = STATIC_SYMBOL("G2-LOAD-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_load_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_load_kb,STATIC_FUNCTION(g2_load_kb,NIL,FALSE,3,3));
    list_constant_68 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_69 = STATIC_CONS(Qresolve_conflicts_automatically,
	    list_constant_68);
    list_constant_70 = STATIC_CONS(Qbring_formats_up_to_date,list_constant_68);
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    list_constant_71 = STATIC_CONS(Qmerge_kb,list_constant_68);
    Qinstall_system_tables = STATIC_SYMBOL("INSTALL-SYSTEM-TABLES",AB_package);
    list_constant_72 = STATIC_CONS(Qinstall_system_tables,list_constant_68);
    list_constant_73 = STATIC_CONS(Qfile_progress_display,list_constant_68);
    Qrestore_workspaces = STATIC_SYMBOL("RESTORE-WORKSPACES",AB_package);
    list_constant_74 = STATIC_CONS(Qrestore_workspaces,list_constant_68);
    Qpost_logbook_messages = STATIC_SYMBOL("POST-LOGBOOK-MESSAGES",AB_package);
    list_constant_75 = STATIC_CONS(Qpost_logbook_messages,list_constant_68);
    Qshow_conflicts = STATIC_SYMBOL("SHOW-CONFLICTS",AB_package);
    list_constant_76 = STATIC_CONS(Qshow_conflicts,list_constant_68);
    Qdisable_ui_during_load = STATIC_SYMBOL("DISABLE-UI-DURING-LOAD",
	    AB_package);
    list_constant_77 = STATIC_CONS(Qdisable_ui_during_load,list_constant_68);
    list_constant_78 = STATIC_LIST((SI_Long)9L,list_constant_69,
	    list_constant_70,list_constant_71,list_constant_72,
	    list_constant_73,list_constant_74,list_constant_75,
	    list_constant_76,list_constant_77);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_78);
    Merge_kb_ex_options_type = list_constant_79;
    Qg2_merge_kb_ex = STATIC_SYMBOL("G2-MERGE-KB-EX",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_merge_kb_ex,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_merge_kb_ex,STATIC_FUNCTION(g2_merge_kb_ex,NIL,
	    FALSE,2,2));
    Qg2_merge_kb_extended = STATIC_SYMBOL("G2-MERGE-KB-EXTENDED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_merge_kb_extended,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_merge_kb_extended,
	    STATIC_FUNCTION(g2_merge_kb_extended,NIL,FALSE,2,2));
    Qg2_merge_kb = STATIC_SYMBOL("G2-MERGE-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_merge_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_merge_kb,STATIC_FUNCTION(g2_merge_kb,NIL,FALSE,
	    5,5));
    Qg2_warmboot_kb = STATIC_SYMBOL("G2-WARMBOOT-KB",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_warmboot_kb,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qwarmboot_afterwards_with_catch_up = 
	    STATIC_SYMBOL("WARMBOOT-AFTERWARDS-WITH-CATCH-UP",AB_package);
    Qwarmboot_afterwards = STATIC_SYMBOL("WARMBOOT-AFTERWARDS",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_warmboot_kb,STATIC_FUNCTION(g2_warmboot_kb,NIL,
	    FALSE,2,2));
    Qg2_load_runtime_data = STATIC_SYMBOL("G2-LOAD-RUNTIME-DATA",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_load_runtime_data,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_load_runtime_data,
	    STATIC_FUNCTION(g2_load_runtime_data,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qsys_proc_read_kb,STATIC_FUNCTION(sys_proc_read_kb,
	    NIL,FALSE,2,2));
    Qg2_get_connection_vertices = 
	    STATIC_SYMBOL("G2-GET-CONNECTION-VERTICES",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_connection_vertices,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_connection_vertices,
	    STATIC_FUNCTION(g2_get_connection_vertices,NIL,FALSE,3,3));
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    array_constant_3 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant_3,(SI_Long)0L,Qtop);
    ISASET_1(array_constant_3,(SI_Long)1L,Qleft);
    ISASET_1(array_constant_3,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant_3,(SI_Long)3L,Qright);
    string_constant_23 = STATIC_STRING("GET-CONNECTION-VERTICES");
    Qg2_get_items_connected_to_port = 
	    STATIC_SYMBOL("G2-GET-ITEMS-CONNECTED-TO-PORT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_items_connected_to_port,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_24 = 
	    STATIC_STRING("Could not reference the ~a connected to ~NF at ~a.  ~a is not a ~a");
    string_constant_25 = STATIC_STRING("class that can have connections.");
    string_constant_26 = STATIC_STRING("defined class.");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_items_connected_to_port,
	    STATIC_FUNCTION(g2_get_items_connected_to_port,NIL,FALSE,4,4));
    Qsystem_predicate = STATIC_SYMBOL("SYSTEM-PREDICATE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qsystem_predicate,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qshowing = STATIC_SYMBOL("SHOWING",AB_package);
    Qexposed = STATIC_SYMBOL("EXPOSED",AB_package);
    Qtransient = STATIC_SYMBOL("TRANSIENT",AB_package);
    Qpermanent = STATIC_SYMBOL("PERMANENT",AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_predicate,STATIC_FUNCTION(system_predicate,
	    NIL,FALSE,2,2));
    Qg2_get_attributes_for_class = 
	    STATIC_SYMBOL("G2-GET-ATTRIBUTES-FOR-CLASS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_attributes_for_class,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_27 = STATIC_STRING("~a is not a valid class name.");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    string_constant_28 = 
	    STATIC_STRING("Inconsistency Found. Non-simple and non-funcalled attribute initialization in user-defined attribute slot [~a] of class ~a.");
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qmanaged_g2_array = STATIC_SYMBOL("MANAGED-G2-ARRAY",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_get_attributes_for_class,
	    STATIC_FUNCTION(g2_get_attributes_for_class,NIL,FALSE,3,3));
    Qg2_get_enumerations_for_symbolic_attribute = 
	    STATIC_SYMBOL("G2-GET-ENUMERATIONS-FOR-SYMBOLIC-ATTRIBUTE",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_enumerations_for_symbolic_attribute,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_enumerations_for_symbolic_attribute,
	    STATIC_FUNCTION(g2_get_enumerations_for_symbolic_attribute,NIL,
	    FALSE,3,3));
    Qg2_float_to_text_using_decimal_format = 
	    STATIC_SYMBOL("G2-FLOAT-TO-TEXT-USING-DECIMAL-FORMAT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_float_to_text_using_decimal_format,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_float_to_text_using_decimal_format,
	    STATIC_FUNCTION(g2_float_to_text_using_decimal_format,NIL,
	    FALSE,5,5));
    Qg2_float_to_text = STATIC_SYMBOL("G2-FLOAT-TO-TEXT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_float_to_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_float_to_text,STATIC_FUNCTION(g2_float_to_text,
	    NIL,FALSE,5,5));
    Qg2_run_trace = STATIC_SYMBOL("G2-RUN-TRACE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_run_trace,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_run_trace,STATIC_FUNCTION(g2_run_trace,NIL,
	    FALSE,1,1));
    Qg2_start_tracking_items = STATIC_SYMBOL("G2-START-TRACKING-ITEMS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_start_tracking_items,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_stop_tracking_items = STATIC_SYMBOL("G2-STOP-TRACKING-ITEMS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_stop_tracking_items,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_clear_tracked_items = STATIC_SYMBOL("G2-CLEAR-TRACKED-ITEMS",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_clear_tracked_items,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    if (Tracked_items_call_depth == UNBOUND)
	Tracked_items_call_depth = FIX((SI_Long)0L);
    if (Tracking_items_p == UNBOUND)
	Tracking_items_p = Nil;
    Qavailable_tracked_items_call_vector_table_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_tracked_items_call_vector_table_hash_vector_43_vectors,
	    Available_tracked_items_call_vector_table_hash_vector_43_vectors);
    record_system_variable(Qavailable_tracked_items_call_vector_table_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_tracked_items_call_vector_table_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_tracked_items_call_vector_table_hash_vector_43_vectors,
	    Count_of_tracked_items_call_vector_table_hash_vector_43_vectors);
    record_system_variable(Qcount_of_tracked_items_call_vector_table_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector 
	    == UNBOUND)
	Available_tracked_items_call_vector_table_hash_vector_43_vectors_vector 
		= make_thread_array(Nil);
    Qout_tracked_items_call_vector_table_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qtracked_items_call_vector_table_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("TRACKED-ITEMS-CALL-VECTOR-TABLE-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_63 = STATIC_STRING("1q83-tiy83*9y83-PEy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_tracked_items_call_vector_table_hash_vector_43_vectors);
    push_optimized_constant(Qtracked_items_call_vector_table_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_63));
    SET_SYMBOL_FUNCTION(Qtracked_items_call_vector_table_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(tracked_items_call_vector_table_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_tracked_items_call_vector_table_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_tracked_items_call_vector_table_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry 
	    = 
	    STATIC_SYMBOL("MUTATE-TRACKED-ITEMS-CALL-VECTOR-TABLE-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry 
	    = 
	    SYMBOL_FUNCTION(Qmutate_tracked_items_call_vector_table_tree_for_hash_skip_list_entry);
    Qtracked_items_call_vector_table_tree_for_hash = 
	    STATIC_SYMBOL("TRACKED-ITEMS-CALL-VECTOR-TABLE-TREE-FOR-HASH",
	    AB_package);
    if (Tracked_items_call_vector_table == UNBOUND)
	Tracked_items_call_vector_table = Nil;
    Qg2_get_tracked_item_call_sequence = 
	    STATIC_SYMBOL("G2-GET-TRACKED-ITEM-CALL-SEQUENCE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_tracked_item_call_sequence,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_tracked_item_call_sequence,
	    STATIC_FUNCTION(g2_get_tracked_item_call_sequence,NIL,FALSE,1,1));
    Qg2_get_tracked_items_call_depth = 
	    STATIC_SYMBOL("G2-GET-TRACKED-ITEMS-CALL-DEPTH",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_tracked_items_call_depth,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_tracked_items_call_depth,
	    STATIC_FUNCTION(g2_get_tracked_items_call_depth,NIL,FALSE,0,0));
    Qg2_set_tracked_items_call_depth = 
	    STATIC_SYMBOL("G2-SET-TRACKED-ITEMS-CALL-DEPTH",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_tracked_items_call_depth,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_tracked_items_call_depth,
	    STATIC_FUNCTION(g2_set_tracked_items_call_depth,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_start_tracking_items,
	    STATIC_FUNCTION(g2_start_tracking_items,NIL,FALSE,0,0));
    if (Tracking_items_grammar_installed_p == UNBOUND)
	Tracking_items_grammar_installed_p = Nil;
    string_constant_29 = 
	    STATIC_STRING("1l1n83m+y1p1m9k83*Xy1m9k9l1m9k83-thy1m9k83Ry1m9k9m1m83-ZJy83f7y");
    SET_SYMBOL_FUNCTION(Qg2_stop_tracking_items,
	    STATIC_FUNCTION(g2_stop_tracking_items,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qg2_clear_tracked_items,
	    STATIC_FUNCTION(g2_clear_tracked_items,NIL,FALSE,0,0));
    Qg2_text_to_symbol_test = STATIC_SYMBOL("G2-TEXT-TO-SYMBOL-TEST",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_text_to_symbol_test,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_text_to_symbol_test,
	    STATIC_FUNCTION(g2_text_to_symbol_test,NIL,FALSE,1,1));
    Qg2_list_of_user_visible_attributes = 
	    STATIC_SYMBOL("G2-LIST-OF-USER-VISIBLE-ATTRIBUTES",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_list_of_user_visible_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_list_of_user_visible_attributes,
	    STATIC_FUNCTION(g2_list_of_user_visible_attributes,NIL,FALSE,1,1));
    Qg2_get_methods = STATIC_SYMBOL("G2-GET-METHODS",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_methods,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_methods,STATIC_FUNCTION(g2_get_methods,NIL,
	    FALSE,1,1));
    Qg2_text_time_interval_to_unix_time = 
	    STATIC_SYMBOL("G2-TEXT-TIME-INTERVAL-TO-UNIX-TIME",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_text_time_interval_to_unix_time,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    string_constant_30 = STATIC_STRING("G2 could not parse interval: ~a");
    SET_SYMBOL_FUNCTION(Qg2_text_time_interval_to_unix_time,
	    STATIC_FUNCTION(g2_text_time_interval_to_unix_time,NIL,FALSE,1,1));
    Qg2_text_time_stamp_to_unix_time = 
	    STATIC_SYMBOL("G2-TEXT-TIME-STAMP-TO-UNIX-TIME",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_text_time_stamp_to_unix_time,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Qframe_author_or_authors = STATIC_SYMBOL("FRAME-AUTHOR-OR-AUTHORS",
	    AB_package);
    string_constant_31 = STATIC_STRING("timestamp (~a)");
    string_constant_32 = STATIC_STRING("G2 could not parse timestamp: ~a");
    SET_SYMBOL_FUNCTION(Qg2_text_time_stamp_to_unix_time,
	    STATIC_FUNCTION(g2_text_time_stamp_to_unix_time,NIL,FALSE,1,1));
    Qg2_clear_history = STATIC_SYMBOL("G2-CLEAR-HISTORY",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_clear_history,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_clear_history,STATIC_FUNCTION(g2_clear_history,
	    NIL,FALSE,1,1));
    Qg2_floating_licenses_remaining = 
	    STATIC_SYMBOL("G2-FLOATING-LICENSES-REMAINING",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_floating_licenses_remaining,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    string_constant_33 = 
	    STATIC_STRING("~NF is not a g2-window or ui-client-session");
    SET_SYMBOL_FUNCTION(Qg2_floating_licenses_remaining,
	    STATIC_FUNCTION(g2_floating_licenses_remaining,NIL,FALSE,1,1));
    Qg2_floating_client_p = STATIC_SYMBOL("G2-FLOATING-CLIENT-P",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_floating_client_p,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_34 = 
	    STATIC_STRING("~NF is not a valid ui-client-session.");
    string_constant_35 = 
	    STATIC_STRING("~NF is not a g2-window or ui-client-session.");
    string_constant_36 = STATIC_STRING("~NF is unauthorized.");
    SET_SYMBOL_FUNCTION(Qg2_floating_client_p,
	    STATIC_FUNCTION(g2_floating_client_p,NIL,FALSE,1,1));
    Qg2_set_user_password = STATIC_SYMBOL("G2-SET-USER-PASSWORD",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_user_password,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_user_password,
	    STATIC_FUNCTION(g2_set_user_password,NIL,FALSE,3,3));
    Qg2_validate_user_and_password = 
	    STATIC_SYMBOL("G2-VALIDATE-USER-AND-PASSWORD",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_validate_user_and_password,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_validate_user_and_password,
	    STATIC_FUNCTION(g2_validate_user_and_password,NIL,FALSE,2,2));
    Qg2_authorized_modes_for_user = 
	    STATIC_SYMBOL("G2-AUTHORIZED-MODES-FOR-USER",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_authorized_modes_for_user,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_authorized_modes_for_user,
	    STATIC_FUNCTION(g2_authorized_modes_for_user,NIL,FALSE,1,1));
    Qg2_add_user = STATIC_SYMBOL("G2-ADD-USER",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_add_user,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_37 = STATIC_STRING("The user ~a already exists.");
    string_constant_38 = 
	    STATIC_STRING("The password-expiration-date ~NV should ~\n                               be a sequence of three integers.");
    string_constant_39 = 
	    STATIC_STRING("~a is not a valid user mode because ~a");
    string_constant_40 = STATIC_STRING("Problem: ~a");
    SET_SYMBOL_FUNCTION(Qg2_add_user,STATIC_FUNCTION(g2_add_user,NIL,FALSE,
	    4,4));
    Qg2_delete_user = STATIC_SYMBOL("G2-DELETE-USER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_user,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_41 = STATIC_STRING("There is no user with the name ~a");
    SET_SYMBOL_FUNCTION(Qg2_delete_user,STATIC_FUNCTION(g2_delete_user,NIL,
	    FALSE,1,1));
    string_constant_42 = 
	    STATIC_STRING("The date provided for when the password should ~\n               expire, ~a/~a/~a, is in the past");
    Qg2_change_password_expiration_date = 
	    STATIC_SYMBOL("G2-CHANGE-PASSWORD-EXPIRATION-DATE",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_change_password_expiration_date,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_change_password_expiration_date,
	    STATIC_FUNCTION(g2_change_password_expiration_date,NIL,FALSE,4,4));
    Qg2_update_license = STATIC_SYMBOL("G2-UPDATE-LICENSE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_update_license,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_update_license,
	    STATIC_FUNCTION(g2_update_license,NIL,FALSE,0,0));
    Qfree_malloced_arrays_on_reclaim = 
	    STATIC_SYMBOL("FREE-MALLOCED-ARRAYS-ON-RECLAIM",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qfree_malloced_arrays_on_reclaim,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfree_malloced_arrays_on_reclaim,
	    STATIC_FUNCTION(free_malloced_arrays_on_reclaim,NIL,FALSE,0,0));
    Qfree_malloced_arrays_on_request = 
	    STATIC_SYMBOL("FREE-MALLOCED-ARRAYS-ON-REQUEST",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qfree_malloced_arrays_on_request,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfree_malloced_arrays_on_request,
	    STATIC_FUNCTION(free_malloced_arrays_on_request,NIL,FALSE,0,0));
    Qfree_all_malloced_arrays = STATIC_SYMBOL("FREE-ALL-MALLOCED-ARRAYS",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qfree_all_malloced_arrays,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qfree_all_malloced_arrays,
	    STATIC_FUNCTION(free_all_malloced_arrays,NIL,FALSE,0,0));
}
