/* schdle.c
 * Input file:  schedule.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "schdle.h"


Object The_type_description_of_schedule_task = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_schedule_tasks, Qchain_of_available_schedule_tasks);

DEFINE_VARIABLE_WITH_SYMBOL(Schedule_task_count, Qschedule_task_count);

Object Chain_of_available_schedule_tasks_vector = UNBOUND;

/* SCHEDULE-TASK-STRUCTURE-MEMORY-USAGE */
Object schedule_task_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(43,0);
    temp = Schedule_task_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)17L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SCHEDULE-TASK-COUNT */
Object outstanding_schedule_task_count()
{
    Object def_structure_schedule_task_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(43,1);
    gensymed_symbol = IFIX(Schedule_task_count);
    def_structure_schedule_task_variable = Chain_of_available_schedule_tasks;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_schedule_task_variable))
	goto end_loop;
    def_structure_schedule_task_variable = 
	    ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SCHEDULE-TASK-1 */
Object reclaim_schedule_task_1(schedule_task)
    Object schedule_task;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(43,2);
    inline_note_reclaim_cons(schedule_task,Nil);
    structure_being_reclaimed = schedule_task;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
      SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
	    IFIX(Current_thread_index));
    SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_schedule_tasks_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = schedule_task;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SCHEDULE-TASK */
Object reclaim_structure_for_schedule_task(schedule_task)
    Object schedule_task;
{
    x_note_fn_call(43,3);
    return reclaim_schedule_task_1(schedule_task);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* MAKE-PERMANENT-SCHEDULE-TASK-STRUCTURE-INTERNAL */
Object make_permanent_schedule_task_structure_internal()
{
    Object def_structure_schedule_task_variable;
    Object defstruct_g2_schedule_task_variable, the_array, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,4);
    def_structure_schedule_task_variable = Nil;
    atomic_incff_symval(Qschedule_task_count,FIX((SI_Long)50L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_schedule_task_variable = Nil;
	gensymed_symbol_1 = (SI_Long)17L;
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
	defstruct_g2_schedule_task_variable = the_array;
	SVREF(defstruct_g2_schedule_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_schedule_task_g2_struct;
	def_structure_schedule_task_variable = 
		defstruct_g2_schedule_task_variable;
	temp = allocate_managed_simple_float_array(FIX((SI_Long)2L));
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)1L)) = temp;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_schedule_task_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_schedule_task_variable);
}

/* MAKE-SCHEDULE-TASK-1 */
Object make_schedule_task_1(schedule_task_reclaimable_by_scheduler_p)
    Object schedule_task_reclaimable_by_scheduler_p;
{
    Object def_structure_schedule_task_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(43,5);
    def_structure_schedule_task_variable = 
	    ISVREF(Chain_of_available_schedule_tasks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_schedule_task_variable) {
	svref_arg_1 = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_schedule_task_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_schedule_task_g2_struct;
    }
    else
	def_structure_schedule_task_variable = 
		make_permanent_schedule_task_structure_internal();
    inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = 
	    schedule_task_reclaimable_by_scheduler_p;
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_schedule_task_variable);
}

static Object Qab_gensym;          /* gensym */

/* RECLAIM-SCHEDULE-TASK-ARGS */
Object reclaim_schedule_task_args(reclaimers)
    Object reclaimers;
{
    Object f, gensym_pop_store, cons_1, next_cons, temp, svref_arg_2;
    SI_Long i, svref_arg_2_1;

    x_note_fn_call(43,6);
    if (reclaimers) {
	f = Nil;
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(Schedule_task_arg_limit))
	    goto end_loop;
	gensym_pop_store = Nil;
	cons_1 = reclaimers;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	reclaimers = next_cons;
	f = gensym_pop_store;
	if (f) {
	    FUNCALL_1(f,ISVREF(Structure_being_reclaimed,i + 
		    IFIX(Schedule_task_arg_offset)));
	    temp = Structure_being_reclaimed;
	    svref_arg_2_1 = i + IFIX(Schedule_task_arg_offset);
	    ISVREF(temp,svref_arg_2_1) = Nil;
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* PRINT-SCHEDULE-TASK */
Object print_schedule_task(schedule_task,stream,depth)
    Object schedule_task, stream, depth;
{
    Object dot_object_dot, dot_stream_dot;
    SI_Long ab_loop_bind_, i;

    x_note_fn_call(43,7);
    dot_object_dot = schedule_task;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)2L,stream,"TASK (");
    format((SI_Long)3L,stream,"~S",ISVREF(schedule_task,(SI_Long)7L));
    ab_loop_bind_ = IFIX(ISVREF(schedule_task,(SI_Long)12L));
    i = (SI_Long)0L;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    format((SI_Long)3L,stream," ~S",ISVREF(schedule_task,i + 
	    IFIX(Schedule_task_arg_offset)));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    format((SI_Long)2L,stream,")");
    print_random_object_suffix(dot_object_dot,dot_stream_dot);
    return VALUES_1(schedule_task);
}

/* NOTE-SCHEDULING-TASK-1 */
Object note_scheduling_task_1(function_name,task)
    Object function_name, task;
{
    x_note_fn_call(43,8);
    return VALUES_1(Nil);
}

Object Immediate_task_queue = UNBOUND;

Object Immediate_task_queue_vector = UNBOUND;

Object Current_task_queue_vector = UNBOUND;

Object Deferred_task_queue_vector = UNBOUND;

Object Future_real_time_tasks = UNBOUND;

Object Future_g2_time_tasks = UNBOUND;

Object The_type_description_of_future_task_queue_holder = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_future_task_queue_holders, Qchain_of_available_future_task_queue_holders);

DEFINE_VARIABLE_WITH_SYMBOL(Future_task_queue_holder_count, Qfuture_task_queue_holder_count);

Object Chain_of_available_future_task_queue_holders_vector = UNBOUND;

/* FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-MEMORY-USAGE */
Object future_task_queue_holder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(43,9);
    temp = Future_task_queue_holder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FUTURE-TASK-QUEUE-HOLDER-COUNT */
Object outstanding_future_task_queue_holder_count()
{
    Object def_structure_future_task_queue_holder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(43,10);
    gensymed_symbol = IFIX(Future_task_queue_holder_count);
    def_structure_future_task_queue_holder_variable = 
	    Chain_of_available_future_task_queue_holders;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_future_task_queue_holder_variable))
	goto end_loop;
    def_structure_future_task_queue_holder_variable = 
	    ISVREF(def_structure_future_task_queue_holder_variable,
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

/* RECLAIM-FUTURE-TASK-QUEUE-HOLDER-1-1 */
Object reclaim_future_task_queue_holder_1_1(future_task_queue_holder)
    Object future_task_queue_holder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(43,11);
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    temp = ISVREF(Chain_of_available_future_task_queue_holders_vector,
	    IFIX(Current_thread_index));
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_future_task_queue_holders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = future_task_queue_holder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FUTURE-TASK-QUEUE-HOLDER */
Object reclaim_structure_for_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    x_note_fn_call(43,12);
    return reclaim_future_task_queue_holder_1_1(future_task_queue_holder);
}

/* MAKE-PERMANENT-FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-INTERNAL */
Object make_permanent_future_task_queue_holder_structure_internal()
{
    Object def_structure_future_task_queue_holder_variable, the_array;
    Object defstruct_g2_future_task_queue_holder_variable, temp, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(43,13);
    def_structure_future_task_queue_holder_variable = Nil;
    atomic_incff_symval(Qfuture_task_queue_holder_count,FIX((SI_Long)50L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)5L;
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
	defstruct_g2_future_task_queue_holder_variable = the_array;
	def_structure_future_task_queue_holder_variable = 
		defstruct_g2_future_task_queue_holder_variable;
	temp = allocate_managed_float_box();
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)1L)) = temp;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_future_task_queue_holders_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_future_task_queue_holders_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = 
		def_structure_future_task_queue_holder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_future_task_queue_holder_variable);
}

/* MAKE-FUTURE-TASK-QUEUE-HOLDER-1-1 */
Object make_future_task_queue_holder_1_1()
{
    Object def_structure_future_task_queue_holder_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(43,14);
    def_structure_future_task_queue_holder_variable = 
	    ISVREF(Chain_of_available_future_task_queue_holders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_future_task_queue_holder_variable) {
	svref_arg_1 = Chain_of_available_future_task_queue_holders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_future_task_queue_holder_variable = 
		make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    return VALUES_1(def_structure_future_task_queue_holder_variable);
}

/* MAKE-FUTURE-TASK-QUEUE-HOLDER-SENTINEL */
Object make_future_task_queue_holder_sentinel(task_time,tail)
    Object task_time, tail;
{
    Object def_structure_future_task_queue_holder_variable, temp, svref_arg_2;
    Object svref_new_value, node, next;
    SI_Long i;
    double aref_new_value;

    x_note_fn_call(43,15);
    def_structure_future_task_queue_holder_variable = 
	    ISVREF(Chain_of_available_future_task_queue_holders_vector,
	    IFIX(Current_thread_index));
    if (def_structure_future_task_queue_holder_variable) {
	temp = Chain_of_available_future_task_queue_holders_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_future_task_queue_holder_variable = 
		make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    node = def_structure_future_task_queue_holder_variable;
    next = 
	    allocate_managed_simple_vector_for_skip_list(FIXNUM_ADD1(Future_task_queue_max_level));
    temp = ISVREF(node,(SI_Long)1L);
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(task_time);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    ISVREF(node,(SI_Long)2L) = FIX((SI_Long)0L);
    i = (SI_Long)0L;
  next_loop:
    if (i > IFIX(Future_task_queue_max_level))
	goto end_loop;
    temp = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = temp;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

static Object Qlookup;             /* lookup */

/* MAKE-FUTURE-TASK-PRIORITY-QUEUE */
Object make_future_task_priority_queue()
{
    Object tail, head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol;

    x_note_fn_call(43,16);
    tail = 
	    make_future_task_queue_holder_sentinel(Most_positive_double_float,
	    Nil);
    head = 
	    make_future_task_queue_holder_sentinel(Most_negative_double_float,
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
    M_CAR(gensymed_symbol) = head;
    M_CDR(gensymed_symbol) = tail;
    inline_note_allocate_cons(gensymed_symbol,Qlookup);
    return VALUES_1(gensymed_symbol);
}

/* RECLAIM-FUTURE-TASK-QUEUE-HOLDER */
Object reclaim_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    Object temp, svref_arg_2;

    x_note_fn_call(43,17);
    reclaim_constant_queue(ISVREF(future_task_queue_holder,(SI_Long)3L));
    reclaim_managed_simple_vector_for_skip_list(ISVREF(future_task_queue_holder,
	    (SI_Long)0L));
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = Nil;
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    temp = ISVREF(Chain_of_available_future_task_queue_holders_vector,
	    IFIX(Current_thread_index));
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_future_task_queue_holders_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = future_task_queue_holder;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(System_has_aborted, Qsystem_has_aborted);

static Object Qabort_g2;           /* abort */

static Object Qrunning;            /* running */

static Object Qpaused;             /* paused */

static Object Qreset;              /* reset */

/* CURRENT-G2-RUN-STATE */
Object current_g2_run_state()
{
    x_note_fn_call(43,18);
    if (System_has_aborted)
	return VALUES_1(Qabort_g2);
    else if (System_is_running)
	return VALUES_1(Qrunning);
    else if (System_has_paused)
	return VALUES_1(Qpaused);
    else
	return VALUES_1(Qreset);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_schedule_task, Qcurrent_schedule_task);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_of_current_task, Qpriority_of_current_task);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_of_next_task, Qpriority_of_next_task);

Object Future_task_queue_marker = UNBOUND;

/* FUTURE-TASK-QUEUE-FIND */
Object future_task_queue_find(queue_holder,task_time,priority,preds,succs)
    Object queue_holder, task_time, priority, preds, succs;
{
    Object marked, snip, pred, curr, succ, reference, temp, temp_1;
    Object node_priority;
    SI_Long bottom_level, level, ab_loop_bind_;
    double node_time, arg, arg_1;
    int temp_2;
    Object result;

    x_note_fn_call(43,19);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    snip = Nil;
    pred = Nil;
    curr = Nil;
    succ = Nil;
  retry:
  next_loop:
    pred = queue_holder;
    level = IFIX(Future_task_queue_max_level);
    ab_loop_bind_ = bottom_level;
  next_loop_1:
    if (level < ab_loop_bind_)
	goto end_loop;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_2:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_3:
    if ( !TRUEP(marked))
	goto end_loop_1;
    temp = ISVREF(pred,(SI_Long)0L);
    temp_2 = level;
    temp_1 = MAKE_ATOMIC_REF(curr,(SI_Long)0L);
    snip = CAS_SVREF(temp,temp_2,temp_1,MAKE_ATOMIC_REF(succ,(SI_Long)0L));
    if ( !TRUEP(snip))
	goto retry;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_3;
  end_loop_1:
    node_time = DFLOAT_ISAREF_1(ISVREF(curr,(SI_Long)1L),(SI_Long)0L);
    node_priority = ISVREF(curr,(SI_Long)2L);
    arg = node_time;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(task_time);
    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1))
	temp_1 = T;
    else {
	arg = node_time;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(task_time);
	if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1))
	    temp_1 = FIXNUM_GT(node_priority,priority) ? T : Nil;
	else
	    temp_1 = Nil;
    }
    if (temp_1) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_1;
    goto next_loop_2;
  end_loop_2:
  end_1:
    ISVREF(preds,level) = pred;
    ISVREF(succs,level) = curr;
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    node_time = DFLOAT_ISAREF_1(ISVREF(curr,(SI_Long)1L),(SI_Long)0L);
    node_priority = ISVREF(curr,(SI_Long)2L);
    arg = node_time;
    arg_1 = DOUBLE_FLOAT_TO_DOUBLE(task_time);
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1) ? FIXNUM_EQ(node_priority,
	    priority) : TRUEP(Nil))
	return VALUES_1(curr);
    else
	return VALUES_1(Nil);
    goto next_loop;
  end_loop_3:;
    return VALUES_1(Qnil);
}

static Object Qget_or_create_future_task_queue_for_task;  /* get-or-create-future-task-queue-for-task */

/* GET-OR-CREATE-FUTURE-TASK-QUEUE-FOR-TASK */
Object get_or_create_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object tag_temp, priority, g2_running_task_qm, future_holder, head, preds;
    Object succs, queue_holder, top_level;
    Object def_structure_future_task_queue_holder_variable, temp, temp_1;
    Object svref_new_value, new_holder, new_queue, new_holder_1, pred, succ;
    Object temp_2, temp_3;
    SI_Long bottom_level, level, ab_loop_bind_;
    double task_time;
    int temp_4;
    Declare_catch(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(43,20);
    tag_temp = UNIQUE_TAG(Qget_or_create_future_task_queue_for_task);
    if (PUSH_CATCH(tag_temp,0)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    priority = ISVREF(schedule_task,(SI_Long)4L);
	    task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		    (SI_Long)0L);
	    g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	    future_holder = g2_running_task_qm ? Future_g2_time_tasks : 
		    Future_real_time_tasks;
	    head = M_CAR(future_holder);
	    preds = Skip_list_find_preds;
	    succs = Skip_list_find_succs;
	    bottom_level = (SI_Long)0L;
	    queue_holder = Nil;
	  next_loop:
	    queue_holder = future_task_queue_find(head,
		    DOUBLE_TO_DOUBLE_FLOAT(task_time),priority,preds,succs);
	    if (queue_holder) {
		result = VALUES_1(ISVREF(queue_holder,(SI_Long)3L));
		THROW(tag_temp,result);
	    }
	    else {
		top_level = random_level(Future_task_queue_max_level);
		def_structure_future_task_queue_holder_variable = 
			ISVREF(Chain_of_available_future_task_queue_holders_vector,
			IFIX(Current_thread_index));
		if (def_structure_future_task_queue_holder_variable) {
		    temp = Chain_of_available_future_task_queue_holders_vector;
		    temp_1 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_future_task_queue_holder_variable,
			    (SI_Long)0L);
		    SVREF(temp,temp_1) = svref_new_value;
		}
		else
		    def_structure_future_task_queue_holder_variable = 
			    make_permanent_future_task_queue_holder_structure_internal();
		inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
			Nil);
		new_holder = def_structure_future_task_queue_holder_variable;
		new_queue = make_empty_constant_queue();
		SVREF(new_queue,FIX((SI_Long)4L)) = Future_task_queue_marker;
		SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
		temp = ISVREF(new_holder,(SI_Long)1L);
		DFLOAT_ISASET_1(temp,(SI_Long)0L,task_time);
		SVREF(new_holder,FIX((SI_Long)2L)) = priority;
		temp = 
			allocate_managed_simple_vector_for_skip_list(FIXNUM_ADD1(top_level));
		SVREF(new_holder,FIX((SI_Long)0L)) = temp;
		SVREF(new_holder,FIX((SI_Long)4L)) = top_level;
		new_holder_1 = new_holder;
		level = bottom_level;
		ab_loop_bind_ = IFIX(top_level);
	      next_loop_1:
		if (level > ab_loop_bind_)
		    goto end_loop;
		temp = ISVREF(new_holder_1,(SI_Long)0L);
		temp_1 = MAKE_ATOMIC_REF(ISVREF(succs,level),(SI_Long)0L);
		ISVREF(temp,level) = temp_1;
		level = level + (SI_Long)1L;
		goto next_loop_1;
	      end_loop:;
		pred = ISVREF(preds,bottom_level);
		succ = ISVREF(succs,bottom_level);
		temp_2 = ISVREF(pred,(SI_Long)0L);
		temp_3 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
		if (CAS_SVREF(temp_2,bottom_level,temp_3,
			MAKE_ATOMIC_REF(new_holder_1,(SI_Long)0L))) {
		    level = bottom_level + (SI_Long)1L;
		    ab_loop_bind_ = IFIX(top_level);
		  next_loop_2:
		    if (level > ab_loop_bind_)
			goto end_loop_1;
		  next_loop_3:
		    pred = ISVREF(preds,level);
		    succ = ISVREF(succs,level);
		    temp_2 = ISVREF(pred,(SI_Long)0L);
		    temp_4 = level;
		    temp_3 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
		    if (CAS_SVREF(temp_2,temp_4,temp_3,
			    MAKE_ATOMIC_REF(new_holder_1,(SI_Long)0L)))
			goto end_1;
		    future_task_queue_find(head,
			    DOUBLE_TO_DOUBLE_FLOAT(task_time),priority,
			    preds,succs);
		    goto next_loop_3;
		  end_loop_2:
		  end_1:
		    level = level + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_1:;
		    result = VALUES_1(ISVREF(new_holder_1,(SI_Long)3L));
		    THROW(tag_temp,result);
		}
	    }
	    goto next_loop;
	  end_loop_3:
	    temp_2 = Qnil;
	}
	POP_LOCAL_ALLOCATION(0,0);
	result = VALUES_1(temp_2);
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    return result;
}

/* DELETE-FUTURE-TASK-QUEUE-FOR-TASK */
Object delete_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object priority, g2_running_task_qm, future_holder;
    double task_time;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,21);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	priority = ISVREF(schedule_task,(SI_Long)4L);
	task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	future_holder = g2_running_task_qm ? Future_g2_time_tasks : 
		Future_real_time_tasks;
	delete_future_task_queue_for_task_inner(future_holder,
		DOUBLE_TO_DOUBLE_FLOAT(task_time),priority);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DELETE-FUTURE-TASK-QUEUE-FOR-TASK-INNER */
Object delete_future_task_queue_for_task_inner(future_holder,
	    task_time_init,priority)
    Object future_holder, task_time_init, priority;
{
    Object head, preds, succs, queue_holder, node_to_remove, succ, marked;
    Object reference, temp, temp_1, i_marked_it;
    SI_Long bottom_level, level, ab_loop_bind_;
    double task_time;
    int temp_2;
    Object result;

    x_note_fn_call(43,22);
    task_time = DOUBLE_FLOAT_TO_DOUBLE(task_time_init);
    head = M_CAR(future_holder);
    preds = Skip_list_find_preds;
    succs = Skip_list_find_succs;
    bottom_level = (SI_Long)0L;
    queue_holder = Nil;
  next_loop:
    queue_holder = future_task_queue_find(head,
	    DOUBLE_TO_DOUBLE_FLOAT(task_time),priority,preds,succs);
    if ( !TRUEP(queue_holder))
	return VALUES_1(Nil);
    node_to_remove = ISVREF(succs,bottom_level);
    succ = Nil;
    marked = Nil;
    level = IFIX(ISVREF(node_to_remove,(SI_Long)4L));
    ab_loop_bind_ = bottom_level + (SI_Long)1L;
  next_loop_1:
    if (level < ab_loop_bind_)
	goto end_loop;
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( ! !TRUEP(marked))
	goto end_loop_1;
    temp_1 = ISVREF(node_to_remove,(SI_Long)0L);
    temp_2 = level;
    temp = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
    CAS_SVREF(temp_1,temp_2,temp,MAKE_ATOMIC_REF(succ,(SI_Long)355L));
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    level = level - (SI_Long)1L;
    goto next_loop_1;
  end_loop:;
    reference = ISVREF(ISVREF(node_to_remove,(SI_Long)0L),bottom_level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    i_marked_it = Nil;
  next_loop_3:
    temp = ISVREF(node_to_remove,(SI_Long)0L);
    temp_1 = MAKE_ATOMIC_REF(succ,(SI_Long)0L);
    i_marked_it = CAS_SVREF(temp,bottom_level,temp_1,MAKE_ATOMIC_REF(succ,
	    (SI_Long)355L));
    reference = ISVREF(ISVREF(ISVREF(succs,bottom_level),(SI_Long)0L),
	    bottom_level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    if (i_marked_it) {
	future_task_queue_find(head,DOUBLE_TO_DOUBLE_FLOAT(task_time),
		priority,preds,succs);
	return VALUES_1(T);
    }
    else if (marked)
	return VALUES_1(Nil);
    goto next_loop_3;
  end_loop_2:;
    goto next_loop;
  end_loop_3:;
    return VALUES_1(Qnil);
}

/* MERGE-CONSTANT-QUEUES */
Object merge_constant_queues(queue_to_fill,queue_to_empty)
    Object queue_to_fill, queue_to_empty;
{
    Object element;

    x_note_fn_call(43,23);
    element = Nil;
  next_loop:
    if ( !TRUEP(constant_queue_next(ISVREF(queue_to_empty,(SI_Long)2L),
	    queue_to_empty)))
	goto end_loop;
    element = constant_queue_pop_left(2,queue_to_empty,Nil);
    SVREF(element,FIX((SI_Long)11L)) = queue_to_fill;
    constant_queue_push_right(queue_to_fill,element);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* UNPACK-ONE-FUTURE-TASK-QUEUE */
Object unpack_one_future_task_queue(future_queue)
    Object future_queue;
{
    Object head, tail, marked, curr, succ, reference, temp, temp_1;
    Object queue_holder, priority;
    SI_Long level;
    double task_time;
    Object result;

    x_note_fn_call(43,24);
    head = M_CAR(future_queue);
    tail = M_CDR(future_queue);
    marked = Nil;
    level = (SI_Long)0L;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),level));
    succ = Nil;
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop:
    if ( !TRUEP(marked))
	goto end_loop;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(curr,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop;
  end_loop:
    queue_holder = curr;
    priority = ISVREF(queue_holder,(SI_Long)2L);
    if (EQ(queue_holder,tail))
	return VALUES_1(Nil);
    merge_constant_queues(ISVREF(Current_task_queue_vector,IFIX(priority)),
	    ISVREF(queue_holder,(SI_Long)3L));
    if (FIXNUM_LT(priority,Priority_of_next_task))
	Priority_of_next_task = priority;
    task_time = DFLOAT_ISAREF_1(ISVREF(queue_holder,(SI_Long)1L),(SI_Long)0L);
    delete_future_task_queue_for_task_inner(future_queue,
	    DOUBLE_TO_DOUBLE_FLOAT(task_time),priority);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_real_time, Qcurrent_real_time);

DEFINE_VARIABLE_WITH_SYMBOL(Current_g2_time, Qcurrent_g2_time);

DEFINE_VARIABLE_WITH_SYMBOL(Timing_parameters, Qtiming_parameters);

static Object Qreal_time;          /* real-time */

/* UNPACK-FUTURE-TASKS-INTO-CURRENT-TASK-QUEUES */
Object unpack_future_tasks_into_current_task_queues(g2_clock_ticked_qm)
    Object g2_clock_ticked_qm;
{
    Object g2_running_qm, scheduler_mode, future_queue, next_future_task;
    Object next_queue, future_real_time_tasks_qm, future_g2_time_tasks_qm;
    char temp;
    double real_time, g2_time, latest_dequeue_time, arg, arg_1;
    double next_real_task_time, next_g2_task_time;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,25);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	real_time = DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L);
	g2_time = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
	g2_running_qm = System_is_running;
	scheduler_mode = scheduler_mode_function(Timing_parameters);
	if ( !TRUEP(g2_running_qm) ||  !TRUEP(g2_clock_ticked_qm)) {
	    future_queue = Future_real_time_tasks;
	    latest_dequeue_time = real_time;
	    next_future_task = Nil;
	  next_loop:
	    next_queue = ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(future_queue),
		    (SI_Long)0L),(SI_Long)0L));
	    next_future_task = EQ(next_queue,CDR(future_queue)) ? Nil : 
		    next_queue;
	    if (next_future_task) {
		arg = DFLOAT_ISAREF_1(ISVREF(next_future_task,(SI_Long)1L),
			(SI_Long)0L);
		arg_1 = latest_dequeue_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop;
	    unpack_one_future_task_queue(future_queue);
	    goto next_loop;
	  end_loop:;
	}
	else if ( !EQ(scheduler_mode,Qreal_time)) {
	    future_queue = Future_real_time_tasks;
	    latest_dequeue_time = real_time;
	    next_future_task = Nil;
	  next_loop_1:
	    next_queue = ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(future_queue),
		    (SI_Long)0L),(SI_Long)0L));
	    next_future_task = EQ(next_queue,CDR(future_queue)) ? Nil : 
		    next_queue;
	    if (next_future_task) {
		arg = DFLOAT_ISAREF_1(ISVREF(next_future_task,(SI_Long)1L),
			(SI_Long)0L);
		arg_1 = latest_dequeue_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop_1;
	    unpack_one_future_task_queue(future_queue);
	    goto next_loop_1;
	  end_loop_1:;
	    future_queue = Future_g2_time_tasks;
	    latest_dequeue_time = g2_time;
	    next_future_task = Nil;
	  next_loop_2:
	    next_queue = ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(future_queue),
		    (SI_Long)0L),(SI_Long)0L));
	    next_future_task = EQ(next_queue,CDR(future_queue)) ? Nil : 
		    next_queue;
	    if (next_future_task) {
		arg = DFLOAT_ISAREF_1(ISVREF(next_future_task,(SI_Long)1L),
			(SI_Long)0L);
		arg_1 = latest_dequeue_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop_2;
	    unpack_one_future_task_queue(future_queue);
	    goto next_loop_2;
	  end_loop_2:;
	}
	else {
	    next_queue = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_real_time_tasks),
		    (SI_Long)0L),(SI_Long)0L));
	    future_real_time_tasks_qm = EQ(next_queue,
		    CDR(Future_real_time_tasks)) ? Nil : next_queue;
	    next_real_task_time = future_real_time_tasks_qm ? 
		    DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
		    (SI_Long)1L),(SI_Long)0L) : 0.0;
	    next_queue = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
		    (SI_Long)0L),(SI_Long)0L));
	    future_g2_time_tasks_qm = EQ(next_queue,
		    CDR(Future_g2_time_tasks)) ? Nil : next_queue;
	    next_g2_task_time = future_g2_time_tasks_qm ? 
		    DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
		    (SI_Long)1L),(SI_Long)0L) : 0.0;
	  next_loop_3:
	    if (future_g2_time_tasks_qm && future_real_time_tasks_qm) {
		arg = next_g2_task_time;
		arg_1 = g2_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		arg = next_real_task_time;
		arg_1 = real_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop_3;
	    arg = next_g2_task_time;
	    arg_1 = next_real_task_time;
	    if (arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1)) {
		unpack_one_future_task_queue(Future_g2_time_tasks);
		next_queue = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
			(SI_Long)0L),(SI_Long)0L));
		future_g2_time_tasks_qm = EQ(next_queue,
			CDR(Future_g2_time_tasks)) ? Nil : next_queue;
		if (future_g2_time_tasks_qm)
		    next_g2_task_time = 
			    DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
			    (SI_Long)1L),(SI_Long)0L);
	    }
	    else {
		unpack_one_future_task_queue(Future_real_time_tasks);
		next_queue = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_real_time_tasks),
			(SI_Long)0L),(SI_Long)0L));
		future_real_time_tasks_qm = EQ(next_queue,
			CDR(Future_real_time_tasks)) ? Nil : next_queue;
		if (future_real_time_tasks_qm)
		    next_real_task_time = 
			    DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
			    (SI_Long)1L),(SI_Long)0L);
	    }
	    goto next_loop_3;
	  end_loop_3:
	    future_queue = Future_real_time_tasks;
	    latest_dequeue_time = real_time;
	    next_future_task = Nil;
	  next_loop_4:
	    next_queue = ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(future_queue),
		    (SI_Long)0L),(SI_Long)0L));
	    next_future_task = EQ(next_queue,CDR(future_queue)) ? Nil : 
		    next_queue;
	    if (next_future_task) {
		arg = DFLOAT_ISAREF_1(ISVREF(next_future_task,(SI_Long)1L),
			(SI_Long)0L);
		arg_1 = latest_dequeue_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop_4;
	    unpack_one_future_task_queue(future_queue);
	    goto next_loop_4;
	  end_loop_4:;
	    future_queue = Future_g2_time_tasks;
	    latest_dequeue_time = g2_time;
	    next_future_task = Nil;
	  next_loop_5:
	    next_queue = ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(future_queue),
		    (SI_Long)0L),(SI_Long)0L));
	    next_future_task = EQ(next_queue,CDR(future_queue)) ? Nil : 
		    next_queue;
	    if (next_future_task) {
		arg = DFLOAT_ISAREF_1(ISVREF(next_future_task,(SI_Long)1L),
			(SI_Long)0L);
		arg_1 = latest_dequeue_time;
		temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		goto end_loop_5;
	    unpack_one_future_task_queue(future_queue);
	    goto next_loop_5;
	  end_loop_5:;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DEFER-CURRENT-G2-RUNNING-TASKS */
Object defer_current_g2_running_tasks()
{
    Object current_task_queue, deferred_task_queue, head, queue_element;
    Object next_queue_element, schedule_task;
    SI_Long priority;

    x_note_fn_call(43,26);
    priority = IFIX(Highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(Current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(Deferred_task_queue_vector,priority);
    if ( ! !TRUEP(constant_queue_next(ISVREF(current_task_queue,
	    (SI_Long)2L),current_task_queue))) {
	head = ISVREF(current_task_queue,(SI_Long)2L);
	queue_element = constant_queue_next(head,current_task_queue);
	next_queue_element = Nil;
	schedule_task = Nil;
      next_loop_1:
	if ( !TRUEP(queue_element))
	    goto end_loop_1;
	next_queue_element = constant_queue_next(queue_element,
		current_task_queue);
	schedule_task = ISVREF(queue_element,(SI_Long)4L);
	if (ISVREF(schedule_task,(SI_Long)3L)) {
	    SVREF(schedule_task,FIX((SI_Long)11L)) = deferred_task_queue;
	    requeue_queue_element(deferred_task_queue,queue_element,
		    current_task_queue);
	}
	queue_element = next_queue_element;
	goto next_loop_1;
      end_loop_1:;
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* REQUEUE-DEFERRED-RUNNING-TASKS */
Object requeue_deferred_running_tasks()
{
    Object current_task_queue, deferred_task_queue;
    SI_Long priority;

    x_note_fn_call(43,27);
    priority = IFIX(Highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(Current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(Deferred_task_queue_vector,priority);
    if ( ! !TRUEP(constant_queue_next(ISVREF(deferred_task_queue,
	    (SI_Long)2L),deferred_task_queue))) {
	merge_constant_queues(current_task_queue,deferred_task_queue);
	if (priority < IFIX(Priority_of_next_task))
	    Priority_of_next_task = FIX(priority);
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Scheduler_has_been_initialized_p, Qscheduler_has_been_initialized_p);

/* INITIALIZE-SCHEDULER */
Object initialize_scheduler()
{
    Object temp, svref_new_value, number_of_priorities, new_vector;
    Object gensymed_symbol, gensymed_symbol_1;
    SI_Long i, ab_loop_bind_, index_1;

    x_note_fn_call(43,28);
    Immediate_task_queue_vector = make_thread_array(Nil);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Number_of_all_threads);
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    temp = Immediate_task_queue_vector;
    svref_new_value = make_empty_constant_queue();
    ISVREF(temp,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    Immediate_task_queue = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
    number_of_priorities = FIXNUM_ADD1(FIXNUM_MINUS(Lowest_system_priority,
	    Highest_system_priority));
    new_vector = make_array(1,number_of_priorities);
    index_1 = IFIX(Highest_system_priority);
  next_loop_1:
    if (index_1 > IFIX(Lowest_system_priority))
	goto end_loop_1;
    temp = make_empty_constant_queue();
    ISVREF(new_vector,index_1) = temp;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    Current_task_queue_vector = new_vector;
    Priority_of_next_task = Lower_than_any_priority;
    new_vector = make_array(1,number_of_priorities);
    index_1 = IFIX(Highest_system_priority);
  next_loop_2:
    if (index_1 > IFIX(Lowest_system_priority))
	goto end_loop_2;
    temp = make_empty_constant_queue();
    ISVREF(new_vector,index_1) = temp;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_2;
  end_loop_2:
    Deferred_task_queue_vector = new_vector;
    Future_real_time_tasks = make_future_task_priority_queue();
    Future_g2_time_tasks = make_future_task_priority_queue();
  next_loop_3:
    gensymed_symbol = Scheduler_has_been_initialized_p;
    gensymed_symbol_1 = T;
    if (CAS_SYMBOL(Qscheduler_has_been_initialized_p,gensymed_symbol,
	    gensymed_symbol_1))
	goto end_1;
    goto next_loop_3;
  end_loop_3:
  end_1:;
    return VALUES_1(Nil);
}

/* CANCEL-G2-RUNNING-TASKS */
Object cancel_g2_running_tasks()
{
    x_note_fn_call(43,29);
    error((SI_Long)1L,
	    "Cancel-g2-running-tasks not implementented yet.  -jra 2/20/94");
    return VALUES_1(Nil);
}

/* CANCEL-AND-RECLAIM-SCHEDULED-QUEUE-ELEMENT-1 */
Object cancel_and_reclaim_scheduled_queue_element_1(schedule_task)
    Object schedule_task;
{
    Object queue_element, queue, next_queue_element, previous_queue_element;

    x_note_fn_call(43,30);
    queue_element = ISVREF(schedule_task,(SI_Long)6L);
    queue = ISVREF(schedule_task,(SI_Long)11L);
    if (queue_element) {
	SVREF(schedule_task,FIX((SI_Long)6L)) = Nil;
	SVREF(schedule_task,FIX((SI_Long)11L)) = Nil;
	next_queue_element = ATOMIC_REF_OBJECT(ISVREF(queue_element,
		(SI_Long)2L));
	previous_queue_element = ATOMIC_REF_OBJECT(ISVREF(queue_element,
		(SI_Long)3L));
	constant_queue_delete(2,queue_element,queue);
	if (EQ(ISVREF(next_queue_element,(SI_Long)4L),
		Constant_queue_tail_marker) && 
		EQ(ISVREF(previous_queue_element,(SI_Long)4L),
		Constant_queue_head_marker))
	    delete_future_task_queue_for_task(schedule_task);
    }
    return VALUES_1(Nil);
}

/* FUTURE-TASK-SCHEDULE-2 */
Object future_task_schedule_2(schedule_task)
    Object schedule_task;
{
    Object g2_task_qm, millisecond_minimum_scheduling_interval_qm;
    Object minimum_in_milliseconds, temp, future_task_qm, current_task_qm;
    Object priority, queue;
    double new_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,31);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	if (g2_task_qm) {
	    millisecond_minimum_scheduling_interval_qm = 
		    minimum_scheduling_interval_function(Timing_parameters);
	    if (millisecond_minimum_scheduling_interval_qm) {
		float_minimum_scheduling_interval = 
			(double)IFIX(millisecond_minimum_scheduling_interval_qm) 
			/ 1000.0;
		time_1 = new_task_time;
		minimum_in_milliseconds = 
			millisecond_minimum_scheduling_interval_qm;
		minimum_float = float_minimum_scheduling_interval;
		if (minimum_in_milliseconds) {
		    if (IFIX(minimum_in_milliseconds) < (SI_Long)1000L) {
			floored_tick_time = inline_ffloor_1(time_1);
			new_task_time = floored_tick_time + 
				inline_fceiling_1((time_1 - 
				floored_tick_time - 1.0E-6) / 
				minimum_float) * minimum_float;
		    }
		    else
			new_task_time = inline_fceiling_1(time_1 / 
				minimum_float) * minimum_float;
		}
		else
		    new_task_time = time_1;
		temp = ISVREF(schedule_task,(SI_Long)1L);
		DFLOAT_ISASET_1(temp,(SI_Long)0L,new_task_time);
	    }
	}
	arg = new_task_time;
	arg_1 = DFLOAT_ISAREF_1(g2_task_qm ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	future_task_qm = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
		 ( !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	if ( !TRUEP(future_task_qm)) {
	    current_task_qm =  !TRUEP(g2_task_qm) ? T : Nil;
	    if (current_task_qm);
	    else
		current_task_qm = System_is_running;
	}
	else
	    current_task_qm = Nil;
	priority = ISVREF(schedule_task,(SI_Long)4L);
	queue = future_task_qm ? 
		get_or_create_future_task_queue_for_task(schedule_task) : 
		ISVREF(current_task_qm ? Current_task_queue_vector : 
		Deferred_task_queue_vector,IFIX(priority));
	SVREF(schedule_task,FIX((SI_Long)11L)) = queue;
	temp = constant_queue_push_right(queue,schedule_task);
	SVREF(schedule_task,FIX((SI_Long)6L)) = temp;
	if (current_task_qm && FIXNUM_LT(priority,Priority_of_next_task))
	    Priority_of_next_task = priority;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DEQUEUE-NEXT-TASK */
Object dequeue_next_task()
{
    Object current_task_qm;
    SI_Long priority;

    x_note_fn_call(43,32);
    priority = IFIX(Priority_of_next_task);
    current_task_qm = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    current_task_qm = constant_queue_pop_left(2,
	    ISVREF(Current_task_queue_vector,priority),Nil);
    if (current_task_qm) {
	Priority_of_next_task = FIX(priority);
	Priority_of_current_task = FIX(priority);
	SVREF(current_task_qm,FIX((SI_Long)6L)) = Nil;
	SVREF(current_task_qm,FIX((SI_Long)11L)) = Nil;
	Current_schedule_task = current_task_qm;
	goto end_1;
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:
    Priority_of_next_task = Lower_than_any_priority;
  end_1:;
    return VALUES_1(Nil);
}

Object Scheduler_task = UNBOUND;

Object Scheduler_task_priority = UNBOUND;

Object Scheduler_task_time = UNBOUND;

Object Multicore_p = UNBOUND;

Object Scheduler_event_lock = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Time_slice_start_time, Qtime_slice_start_time);

Object Scheduler_event_ready = UNBOUND;

static Object Qfloat_array;        /* float-array */

static Object Qworkstation;        /* workstation */

/* DEQUEUE-AND-EXECUTE-NEXT-TASK */
Object dequeue_and_execute_next_task()
{
    Object priority_to_use, local_immediate_queue, immediate_task_qm;
    Object reclaim_task_qm, function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, current_time, structure_being_reclaimed, current_task;
    Object task_function_name, task_thread;
    char temp_3;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(43,33);
    SAVE_STACK();
    if (Current_schedule_task) {
	if (ISVREF(Current_schedule_task,(SI_Long)2L))
	    reclaim_schedule_task_1(Current_schedule_task);
	Current_schedule_task = Nil;
    }
    priority_to_use = FIXNUMP(Priority_of_current_task) && 
	    FIXNUM_GE(Priority_of_current_task,Highest_system_priority) && 
	    FIXNUM_LE(Priority_of_current_task,Lowest_system_priority) ? 
	    Priority_of_current_task : Highest_system_priority;
    local_immediate_queue = ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index));
    immediate_task_qm = Nil;
  next_loop:
    immediate_task_qm = constant_queue_pop_left(2,local_immediate_queue,Nil);
    if ( !TRUEP(immediate_task_qm))
	goto end_loop;
    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
    SVREF(immediate_task_qm,FIX((SI_Long)11L)) = Nil;
    Priority_of_current_task = priority_to_use;
    Current_schedule_task = immediate_task_qm;
    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(immediate_task_qm);
    function = ISVREF(immediate_task_qm,(SI_Long)8L);
    temp = ISVREF(immediate_task_qm,(SI_Long)12L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)16L);
	    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    break;
	  default:
	    break;
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
	exit_current_profiling_context(current_time);
	reclaim_managed_simple_float_array_of_length_1(current_time);
    }
    if (reclaim_task_qm && EQ(immediate_task_qm,Current_schedule_task)) {
	inline_note_reclaim_cons(immediate_task_qm,Nil);
	structure_being_reclaimed = immediate_task_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(immediate_task_qm,(SI_Long)9L));
	  SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	temp_1 = Chain_of_available_schedule_tasks_vector;
	temp_2 = Current_thread_index;
	SVREF(temp_1,temp_2) = immediate_task_qm;
    }
    goto next_loop;
  end_loop:;
    Priority_of_current_task = Higher_than_any_priority;
    Current_schedule_task = Nil;
    if (Time_to_check_network_events) {
	temp_3 = TRUEP(g2_event_ready_p());
	if (temp_3);
	else {
	    Time_to_check_network_events = Nil;
	    temp_3 = TRUEP(Time_to_check_network_events);
	}
    }
    else
	temp_3 = TRUEP(Nil);
    if (temp_3) {
	Time_to_check_network_events = Nil;
	get_pending_network_events();
    }
    dequeue_next_task();
    if ( !TRUEP(Current_schedule_task) && (get_pending_network_events() || 
	    tick_the_clock(Nil)))
	dequeue_next_task();
    if (Current_schedule_task) {
	current_task = Current_schedule_task;
	task_function_name = ISVREF(current_task,(SI_Long)7L);
	task_thread = ISVREF(current_task,(SI_Long)10L);
	if (Multicore_p) {
	    if (EQ(task_thread,Qworkstation))
		execute_task_and_reschedule(current_task);
	    else if (EQ(task_thread,Qt)) {
		LOCK(Scheduler_event_lock);
		if (PUSH_UNWIND_PROTECT(0)) {
		    Scheduler_task = Current_schedule_task;
		    Scheduler_task_priority = Priority_of_current_task;
		    Scheduler_task_time = Time_slice_start_time;
		    condition_variable_broadcast(Scheduler_event_ready);
		  next_loop_1:
		    if ( !TRUEP(Scheduler_task))
			goto end_loop_1;
		    condition_variable_wait_with_timeout(Scheduler_event_ready,
			    Scheduler_worker_loop_interval);
		    goto next_loop_1;
		  end_loop_1:
		    condition_variable_broadcast(Scheduler_event_ready);
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Scheduler_event_lock);
		CONTINUE_UNWINDING(0);
	    }
	    else
		execute_task_and_reschedule(current_task);
	}
	else
	    execute_task_and_reschedule(current_task);
	Current_schedule_task = Nil;
	local_immediate_queue = ISVREF(Immediate_task_queue_vector,
		IFIX(Current_thread_index));
	immediate_task_qm = Nil;
      next_loop_2:
	immediate_task_qm = constant_queue_pop_left(2,
		local_immediate_queue,Nil);
	if ( !TRUEP(immediate_task_qm))
	    goto end_loop_2;
	SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	SVREF(immediate_task_qm,FIX((SI_Long)11L)) = Nil;
	Current_schedule_task = immediate_task_qm;
	reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
	if (Profiling_enabled_qm)
	    posit_profiling_structure(immediate_task_qm);
	function = ISVREF(immediate_task_qm,(SI_Long)8L);
	temp = ISVREF(immediate_task_qm,(SI_Long)12L);
	if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		inline_funcall_0(function);
		break;
	      case 1:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		break;
	      case 2:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
		break;
	      case 3:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		break;
	      case 4:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
		gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)16L);
		inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
		break;
	      default:
		break;
	    }
	if (Profiling_enabled_qm) {
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
	    reclaim_managed_simple_float_array_of_length_1(current_time);
	}
	if (reclaim_task_qm && EQ(immediate_task_qm,Current_schedule_task)) {
	    inline_note_reclaim_cons(immediate_task_qm,Nil);
	    structure_being_reclaimed = immediate_task_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(immediate_task_qm,
		      (SI_Long)9L));
	      SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = immediate_task_qm;
	}
	goto next_loop_2;
      end_loop_2:;
	Priority_of_current_task = Higher_than_any_priority;
	Current_schedule_task = Nil;
	Priority_of_current_task = Higher_than_any_priority;
	temp = task_function_name;
    }
    else
	temp = Nil;
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

/* EXECUTE-TASK-AND-RESCHEDULE */
Object execute_task_and_reschedule(current_task)
    Object current_task;
{
    Object reclaim_task_qm, function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, current_time, g2_running_qm, structure_being_reclaimed;
    double aref_new_value, interval, arg, arg_1, current_time_1, old_task_time;
    double new_time;
    Declare_special(1);

    x_note_fn_call(43,34);
    reclaim_task_qm = ISVREF(current_task,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(current_task);
    function = ISVREF(current_task,(SI_Long)8L);
    temp = ISVREF(current_task,(SI_Long)12L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)13L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)14L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(current_task,(SI_Long)15L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(current_task,(SI_Long)15L);
	    gensymed_symbol_4 = ISVREF(current_task,(SI_Long)16L);
	    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    break;
	  default:
	    break;
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
	exit_current_profiling_context(current_time);
	reclaim_managed_simple_float_array_of_length_1(current_time);
    }
    if (EQ(Current_schedule_task,current_task)) {
	interval = DFLOAT_ISAREF_1(ISVREF(current_task,(SI_Long)1L),
		(SI_Long)1L);
	arg = interval;
	arg_1 = 0.0;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    g2_running_qm = ISVREF(current_task,(SI_Long)3L);
	    current_time_1 = g2_running_qm ? 
		    DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) : 
		    DFLOAT_ISAREF_1(Current_real_time,(SI_Long)0L);
	    old_task_time = DFLOAT_ISAREF_1(ISVREF(current_task,
		    (SI_Long)1L),(SI_Long)0L);
	    new_time = interval + current_time_1;
	    if (ISVREF(current_task,(SI_Long)5L)) {
		new_time = old_task_time + interval;
		arg = new_time;
		arg_1 = current_time_1;
		if ( !(arg > arg_1 &&  !inline_nanp_for_comparison(arg) && 
			 !inline_nanp_for_comparison(arg_1)))
		    new_time = old_task_time + interval * 
			    inline_fceiling_1((current_time_1 - 
			    old_task_time) / interval);
	    }
	    temp_1 = ISVREF(current_task,(SI_Long)1L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,new_time);
	    future_task_schedule_2(current_task);
	    Current_schedule_task = Nil;
	}
    }
    if (reclaim_task_qm && EQ(current_task,Current_schedule_task)) {
	inline_note_reclaim_cons(current_task,Nil);
	structure_being_reclaimed = current_task;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(current_task,(SI_Long)9L));
	  SVREF(current_task,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(current_task,FIX((SI_Long)0L)) = temp_1;
	temp_1 = Chain_of_available_schedule_tasks_vector;
	temp_2 = Current_thread_index;
	SVREF(temp_1,temp_2) = current_task;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TASKS-ENQUEUED-FOR-CURRENT-EXECUTION? */
Object tasks_enqueued_for_current_execution_qm()
{
    Object constant_queue, temp, ab_loop_it_;
    SI_Long priority;

    x_note_fn_call(43,35);
    constant_queue = ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index));
    temp =  ! !TRUEP(constant_queue_next(ISVREF(constant_queue,
	    (SI_Long)2L),constant_queue)) ? T : Nil;
    if (temp);
    else {
	priority = IFIX(Highest_system_priority);
	ab_loop_it_ = Nil;
      next_loop:
	if (priority > IFIX(Lowest_system_priority))
	    goto end_loop;
	constant_queue = ISVREF(Current_task_queue_vector,priority);
	ab_loop_it_ =  ! !TRUEP(constant_queue_next(ISVREF(constant_queue,
		(SI_Long)2L),constant_queue)) ? T : Nil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	priority = priority + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* TASKS-DEFERRED-UNTIL-RESUMPTION? */
Object tasks_deferred_until_resumption_qm()
{
    Object ab_loop_it_, constant_queue, temp;
    SI_Long priority;

    x_note_fn_call(43,36);
    priority = IFIX(Highest_system_priority);
    ab_loop_it_ = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    constant_queue = ISVREF(Deferred_task_queue_vector,priority);
    ab_loop_it_ =  ! !TRUEP(constant_queue_next(ISVREF(constant_queue,
	    (SI_Long)2L),constant_queue)) ? T : Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end_1;
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* NEXT-SCHEDULED-TASK-FOR-FUNCTION */
Object next_scheduled_task_for_function(function_name,priority)
    Object function_name, priority;
{
    Object queue, head, first_1, immediate_task_qm;

    x_note_fn_call(43,37);
    queue = ISVREF(Immediate_task_queue_vector,IFIX(Current_thread_index));
    head = ISVREF(queue,(SI_Long)2L);
    first_1 = constant_queue_next(head,queue);
    immediate_task_qm = first_1 ? constant_queue_read(2,first_1,queue) : Nil;
    return VALUES_1(immediate_task_qm ? (EQ(ISVREF(immediate_task_qm,
	    (SI_Long)7L),function_name) ? immediate_task_qm : Nil) : Nil);
}

/* EXECUTE-TASK-OUT-OF-ORDER-1 */
Object execute_task_out_of_order_1(schedule_task)
    Object schedule_task;
{
    Object temp, priority_of_current_task, current_schedule_task;
    Object reclaim_task_qm, function, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, current_time, structure_being_reclaimed;
    Object local_immediate_queue, immediate_task_qm;
    double aref_new_value;
    Declare_special(3);

    x_note_fn_call(43,38);
    if (schedule_task) {
	if (ISVREF(schedule_task,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	if (EQ(schedule_task,Current_schedule_task))
	    Current_schedule_task = Nil;
	temp = ISVREF(schedule_task,(SI_Long)4L);
	priority_of_current_task = FIXNUM_MAX(temp,Highest_system_priority);
	current_schedule_task = schedule_task;
	reclaim_task_qm = ISVREF(schedule_task,(SI_Long)2L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_schedule_task,Qcurrent_schedule_task,current_schedule_task,
		2);
	  PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		  1);
	    if (Profiling_enabled_qm)
		posit_profiling_structure(schedule_task);
	    function = ISVREF(schedule_task,(SI_Long)8L);
	    temp = ISVREF(schedule_task,(SI_Long)12L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    inline_funcall_0(function);
		    break;
		  case 1:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)13L);
		    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		    break;
		  case 2:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)14L);
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    break;
		  case 3:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)14L);
		    gensymed_symbol_3 = ISVREF(schedule_task,(SI_Long)15L);
		    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3);
		    break;
		  case 4:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)14L);
		    gensymed_symbol_3 = ISVREF(schedule_task,(SI_Long)15L);
		    gensymed_symbol_4 = ISVREF(schedule_task,(SI_Long)16L);
		    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4);
		    break;
		  default:
		    break;
		}
	    if (Profiling_enabled_qm) {
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
		reclaim_managed_simple_float_array_of_length_1(current_time);
	    }
	    if (reclaim_task_qm) {
		inline_note_reclaim_cons(schedule_task,Nil);
		structure_being_reclaimed = schedule_task;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(schedule_task,
			  (SI_Long)9L));
		  SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(schedule_task,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = schedule_task;
	    }
	    local_immediate_queue = ISVREF(Immediate_task_queue_vector,
		    IFIX(Current_thread_index));
	    immediate_task_qm = Nil;
	  next_loop:
	    immediate_task_qm = constant_queue_pop_left(2,
		    local_immediate_queue,Nil);
	    if ( !TRUEP(immediate_task_qm))
		goto end_loop;
	    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	    SVREF(immediate_task_qm,FIX((SI_Long)11L)) = Nil;
	    Priority_of_current_task = Highest_system_priority;
	    Current_schedule_task = immediate_task_qm;
	    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
	    if (Profiling_enabled_qm)
		posit_profiling_structure(immediate_task_qm);
	    function = ISVREF(immediate_task_qm,(SI_Long)8L);
	    temp = ISVREF(immediate_task_qm,(SI_Long)12L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    inline_funcall_0(function);
		    break;
		  case 1:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		    break;
		  case 2:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    break;
		  case 3:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
		    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3);
		    break;
		  case 4:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
		    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
		    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)16L);
		    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3,
			    gensymed_symbol_4);
		    break;
		  default:
		    break;
		}
	    if (Profiling_enabled_qm) {
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
		reclaim_managed_simple_float_array_of_length_1(current_time);
	    }
	    if (reclaim_task_qm && EQ(immediate_task_qm,
			Current_schedule_task)) {
		inline_note_reclaim_cons(immediate_task_qm,Nil);
		structure_being_reclaimed = immediate_task_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(immediate_task_qm,
			  (SI_Long)9L));
		  SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = immediate_task_qm;
	    }
	    goto next_loop;
	  end_loop:;
	    Priority_of_current_task = Higher_than_any_priority;
	    Current_schedule_task = Nil;
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qclear_g2_schedule;  /* clear-g2-schedule */

/* CLEAR-G2-SCHEDULE */
Object clear_g2_schedule()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, queue, queue_1;
    Object next_queue_element, schedule_task, structure_being_reclaimed, head;
    Object tail, next_queue_holder, queue_holder;
    SI_Long i, ab_loop_bind_, priority;
    Declare_special(2);

    x_note_fn_call(43,39);
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
	  SVREF(temp,svref_arg_2) = Qclear_g2_schedule;
      }
      i = (SI_Long)0L;
      ab_loop_bind_ = IFIX(Number_of_all_threads);
      queue = Nil;
    next_loop:
      if (i >= ab_loop_bind_)
	  goto end_loop;
      queue = ISVREF(Immediate_task_queue_vector,i);
      queue_1 = queue;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = constant_queue_next(ISVREF(queue_1,(SI_Long)2L),
	      queue_1);
    next_loop_1:
      if ( !TRUEP(next_queue_element))
	  goto end_loop_1;
      schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
      next_queue_element = constant_queue_next(next_queue_element,queue_1);
      if (ISVREF(schedule_task,(SI_Long)3L)) {
	  if (ISVREF(schedule_task,(SI_Long)6L))
	      cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      structure_being_reclaimed = schedule_task;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
		SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = schedule_task;
	  }
      }
      goto next_loop_1;
    end_loop_1:;
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:;
      priority = IFIX(Highest_system_priority);
      queue = Nil;
    next_loop_2:
      if (priority > IFIX(Lowest_system_priority))
	  goto end_loop_2;
      queue = ISVREF(Current_task_queue_vector,priority);
      queue_1 = queue;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = constant_queue_next(ISVREF(queue_1,(SI_Long)2L),
	      queue_1);
    next_loop_3:
      if ( !TRUEP(next_queue_element))
	  goto end_loop_3;
      schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
      next_queue_element = constant_queue_next(next_queue_element,queue_1);
      if (ISVREF(schedule_task,(SI_Long)3L)) {
	  if (ISVREF(schedule_task,(SI_Long)6L))
	      cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      structure_being_reclaimed = schedule_task;
	      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		      0);
		reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
		SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      POP_SPECIAL();
	      temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		      IFIX(Current_thread_index));
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      temp = Chain_of_available_schedule_tasks_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = schedule_task;
	  }
      }
      goto next_loop_3;
    end_loop_3:;
      priority = priority + (SI_Long)1L;
      goto next_loop_2;
    end_loop_2:;
      priority = IFIX(Highest_system_priority);
      queue = Nil;
    next_loop_4:
      if (priority > IFIX(Lowest_system_priority))
	  goto end_loop_4;
      queue = ISVREF(Deferred_task_queue_vector,priority);
      queue_1 = queue;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = constant_queue_next(ISVREF(queue_1,(SI_Long)2L),
	      queue_1);
    next_loop_5:
      if ( !TRUEP(next_queue_element))
	  goto end_loop_5;
      schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
      next_queue_element = constant_queue_next(next_queue_element,queue_1);
      if (ISVREF(schedule_task,(SI_Long)6L))
	  cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  structure_being_reclaimed = schedule_task;
	  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		  0);
	    reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	    SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  POP_SPECIAL();
	  temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		  IFIX(Current_thread_index));
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  temp = Chain_of_available_schedule_tasks_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = schedule_task;
      }
      goto next_loop_5;
    end_loop_5:;
      priority = priority + (SI_Long)1L;
      goto next_loop_4;
    end_loop_4:;
      head = CAR(Future_g2_time_tasks);
      tail = CDR(Future_g2_time_tasks);
      next_queue_holder = Nil;
      queue_holder = Nil;
      next_queue_holder = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,
	      (SI_Long)0L),(SI_Long)0L));
    next_loop_6:
      if (EQ(next_queue_holder,tail))
	  goto end_loop_6;
      queue_holder = next_queue_holder;
      next_queue_holder = 
	      ATOMIC_REF_OBJECT(ISVREF(ISVREF(next_queue_holder,
	      (SI_Long)0L),(SI_Long)0L));
      queue_1 = ISVREF(queue_holder,(SI_Long)3L);
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = constant_queue_next(ISVREF(queue_1,(SI_Long)2L),
	      queue_1);
    next_loop_7:
      if ( !TRUEP(next_queue_element))
	  goto end_loop_7;
      schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
      next_queue_element = constant_queue_next(next_queue_element,queue_1);
      if (ISVREF(schedule_task,(SI_Long)6L))
	  cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  structure_being_reclaimed = schedule_task;
	  PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		  0);
	    reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	    SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  POP_SPECIAL();
	  temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		  IFIX(Current_thread_index));
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  temp = Chain_of_available_schedule_tasks_vector;
	  svref_arg_2 = Current_thread_index;
	  SVREF(temp,svref_arg_2) = schedule_task;
      }
      goto next_loop_7;
    end_loop_7:;
      goto next_loop_6;
    end_loop_6:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* ADJUST-TASK-TIMES-AFTER-CLOCK-DISCONTINUITY */
Object adjust_task_times_after_clock_discontinuity(managed_float_offset,
	    future_task_queue_set)
    Object managed_float_offset, future_task_queue_set;
{
    Object head, tail, next_queue_holder, task_queue_holder, holder_time;
    Object queue, queue_1, next_queue_element, schedule_task, aref_arg_1;
    double offset, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,40);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	offset = DFLOAT_ISAREF_1(managed_float_offset,(SI_Long)0L);
	head = CAR(future_task_queue_set);
	tail = CDR(future_task_queue_set);
	next_queue_holder = Nil;
	task_queue_holder = Nil;
	holder_time = Nil;
	queue = Nil;
	next_queue_holder = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,
		(SI_Long)0L),(SI_Long)0L));
      next_loop:
	if (EQ(next_queue_holder,tail))
	    goto end_loop;
	task_queue_holder = next_queue_holder;
	next_queue_holder = 
		ATOMIC_REF_OBJECT(ISVREF(ISVREF(next_queue_holder,
		(SI_Long)0L),(SI_Long)0L));
	holder_time = ISVREF(task_queue_holder,(SI_Long)1L);
	queue = ISVREF(task_queue_holder,(SI_Long)3L);
	aref_new_value = DFLOAT_ISAREF_1(holder_time,(SI_Long)0L) + offset;
	DFLOAT_ISASET_1(holder_time,(SI_Long)0L,aref_new_value);
	queue_1 = queue;
	next_queue_element = Nil;
	schedule_task = Nil;
	next_queue_element = constant_queue_next(ISVREF(queue_1,
		(SI_Long)2L),queue_1);
      next_loop_1:
	if ( !TRUEP(next_queue_element))
	    goto end_loop_1;
	schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
	next_queue_element = constant_queue_next(next_queue_element,queue_1);
	aref_arg_1 = ISVREF(schedule_task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L) + offset;
	DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Maximum_time_slice_size, Qmaximum_time_slice_size);

/* TIME-SLICE-EXPIRED-P */
Object time_slice_expired_p()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, elapsed_time;

    x_note_fn_call(43,41);
    temp = FIXNUM_LT(Priority_of_next_task,Priority_of_current_task) ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(Time_slice_start_time);
	if (gensymed_symbol >= gensymed_symbol_1)
	    elapsed_time = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    elapsed_time = gensymed_symbol + (SI_Long)1L;
	}
	temp = elapsed_time >= IFIX(Maximum_time_slice_size) ? T : Nil;
    }
    if (temp);
    else if (FIXNUM_NE(Priority_of_next_task,Most_positive_fixnum)) {
	if (Time_to_check_network_events) {
	    temp = g2_event_ready_p();
	    if (temp);
	    else {
		Time_to_check_network_events = Nil;
		temp = Time_to_check_network_events;
	    }
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TIME-SLICE-EXPIRED-P-GIVEN-TIME */
Object time_slice_expired_p_given_time(given_fixnum_time)
    Object given_fixnum_time;
{
    Object temp;
    SI_Long elapsed_time, gensymed_symbol;

    x_note_fn_call(43,42);
    temp = FIXNUM_LT(Priority_of_next_task,Priority_of_current_task) ? T : Nil;
    if (temp);
    else {
	if (FIXNUM_GE(given_fixnum_time,Time_slice_start_time))
	    elapsed_time = IFIX(FIXNUM_MINUS(given_fixnum_time,
		    Time_slice_start_time));
	else {
	    gensymed_symbol = IFIX(FIXNUM_MINUS(given_fixnum_time,
		    Time_slice_start_time));
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    elapsed_time = gensymed_symbol + (SI_Long)1L;
	}
	temp = elapsed_time >= IFIX(Maximum_time_slice_size) ? T : Nil;
    }
    return VALUES_1(temp);
}

static Object float_constant;      /* 0.0 */

/* SCHEDULER-TIME-LAG */
Object scheduler_time_lag(priority)
    Object priority;
{
    Object queue, next_queue_element, task, temp;

    x_note_fn_call(43,43);
    queue = ISVREF(Current_task_queue_vector,IFIX(priority));
    next_queue_element = Nil;
    task = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    task = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
    if (ISVREF(task,(SI_Long)3L)) {
	temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
		(SI_Long)0L) - DFLOAT_ISAREF_1(ISVREF(task,(SI_Long)1L),
		(SI_Long)0L));
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = float_constant;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

static Object string_constant;     /* "Time Cyclic G2-Running? Priority Function-and-Args" */

/* TWRITE-SCHEDULE-TASK-HEADER */
Object twrite_schedule_task_header()
{
    x_note_fn_call(43,44);
    tformat(1,string_constant);
    return VALUES_1(Nil);
}

static Object Qab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

/* TYPE-NAME-OF-NAMED-SIMPLE-VECTOR */
Object type_name_of_named_simple_vector(arg)
    Object arg;
{
    Object type, temp;

    x_note_fn_call(43,45);
    if (allocated_named_gensym_structure_p(arg)) {
	type = ISVREF(arg,(SI_Long)0L);
	temp = SYMBOL_PACKAGE(type);
	temp = EQ(temp,The_g2_defstruct_package) ? 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
		Qab_name_of_unique_structure_type) : type;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object string_constant_1;   /* " <~a>" */

static Object string_constant_2;   /* " ~a" */

/* TWRITE-DEBUG-OBJECT */
Object twrite_debug_object(arg)
    Object arg;
{
    x_note_fn_call(43,46);
    if (allocated_named_gensym_structure_p(arg))
	tformat(2,string_constant_1,type_name_of_named_simple_vector(arg));
    else
	tformat(2,string_constant_2,arg);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* " [~a]" */

static Object string_constant_4;   /* " [~a ~a]" */

/* TWRITE-DEBUG-COMPUTATION-INSTANCE-OR-OBJECT */
Object twrite_debug_computation_instance_or_object(arg)
    Object arg;
{
    Object name_qm, class_qm;
    Object result;

    x_note_fn_call(43,47);
    result = name_and_class_for_computation_instance(arg);
    MVS_2(result,name_qm,class_qm);
    if ( !TRUEP(class_qm))
	twrite_debug_object(arg);
    else if ( !TRUEP(name_qm))
	tformat(2,string_constant_3,class_qm);
    else
	tformat(3,string_constant_4,class_qm,name_qm);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_time, Qgensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_base_time_as_managed_float, Qgensym_base_time_as_managed_float);

static Object Qwide_string;        /* wide-string */

static Object Qdo_not_use;         /* do-not-use */

static Object string_constant_5;   /* "T    " */

static Object string_constant_6;   /* "NIL  " */

static Object string_constant_7;   /* "~a~a   " */

static Object string_constant_8;   /* " " */

static Object string_constant_9;   /* "" */

/* TWRITE-SCHEDULE-TASK */
Object twrite_schedule_task(schedule_task)
    Object schedule_task;
{
    Object temp_1, schar_arg_2, schar_new_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object interval_string, args, name;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_repeat_;
    char thing;
    double temp;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,48);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	write_floating_point_number(10,
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(schedule_task,
		(SI_Long)1L),(SI_Long)0L) - ((double)IFIX(Gensym_time) + 
		(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
		(SI_Long)0L) - temp))),FIX((SI_Long)9L),FIX((SI_Long)3L),
		FIX((SI_Long)0L),Nil,Nil,Nil,Nil,FIX((SI_Long)13L),CHR('#'));
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = ' ';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = ' ';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
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
		  write_floating_point_number(10,
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(schedule_task,
			  (SI_Long)1L),(SI_Long)1L)),FIX((SI_Long)4L),
			  FIX((SI_Long)3L),FIX((SI_Long)0L),T,Nil,Nil,Nil,
			  FIX((SI_Long)8L),CHR('#'));
		  interval_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	twrite_general_string(interval_string);
	ab_loop_repeat_ = (SI_Long)8L - 
		IFIX(text_string_length(interval_string));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = ' ';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = ' ';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
	goto next_loop;
      end_loop:;
	reclaim_text_string(interval_string);
	twrite_general_string(ISVREF(schedule_task,(SI_Long)3L) ? 
		string_constant_5 : string_constant_6);
	tformat(3,string_constant_7,ISVREF(schedule_task,(SI_Long)4L),
		IFIX(ISVREF(schedule_task,(SI_Long)4L)) < (SI_Long)10L ? 
		string_constant_8 : string_constant_9);
	args = ISVREF(schedule_task,(SI_Long)12L);
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = '(';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = '(';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
	name = get_name_for_function(ISVREF(schedule_task,(SI_Long)7L));
	twrite_general_string(name);
	reclaim_simple_gensym_string(name);
	if (IFIX(args) > (SI_Long)0L) {
	    twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
		    (SI_Long)13L));
	    if (IFIX(args) > (SI_Long)1L) {
		twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
			(SI_Long)14L));
		if (IFIX(args) > (SI_Long)2L) {
		    twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
			    (SI_Long)15L));
		    if (IFIX(args) > (SI_Long)3L)
			twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
				(SI_Long)16L));
		}
	    }
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = ')';
	    twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp_1 = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = ')';
	    schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		    CHAR_CODE(CHR(thing)) : CHR(thing));
	    SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
	    temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp_1;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* TASK-QUEUE-DESCRIPTIONS */
Object task_queue_descriptions(constant_queue)
    Object constant_queue;
{
    Object queue, next_queue_element, schedule_task, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(43,49);
    queue = constant_queue;
    next_queue_element = Nil;
    schedule_task = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    next_queue_element = constant_queue_next(ISVREF(queue,(SI_Long)2L),queue);
  next_loop:
    if ( !TRUEP(next_queue_element))
	goto end_loop;
    schedule_task = ISVREF(next_queue_element,(SI_Long)4L);
    next_queue_element = constant_queue_next(next_queue_element,queue);
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
	      twrite_schedule_task(schedule_task);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
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

static Object string_constant_10;  /* "System-is-running = ~a, System-has-paused = ~a" */

static Object string_constant_11;  /* "Scheduler-mode = ~a, Minimum-scheduling-interval = ~a" */

static Object array_constant;      /* # */

static Object string_constant_12;  /* "Current-real-time = " */

static Object string_constant_13;  /* "Current-g2-time   = " */

static Object string_constant_14;  /* "Gensym-time       = " */

static Object string_constant_15;  /* " (Gensym-time = ~a, gensym-base-time-as-managed-float = ~a)" */

static Object string_constant_16;  /* "Priority-of-next-task = ~a, current-tasks-enqueued? = ~a" */

static Object string_constant_17;  /* "Immediate-task-queue" */

static Object string_constant_18;  /* "Current-task-queue-vector" */

static Object string_constant_19;  /* "Deferred-task-queue-vector" */

static Object string_constant_20;  /* "Future-real-time-tasks" */

static Object string_constant_21;  /* "Future-g2-time-tasks" */

/* PRINT-SCHEDULE-TO-STRING-LIST */
Object print_schedule_to_string_list(current_only_p)
    Object current_only_p;
{
    Object gensymed_symbol, gensymed_symbol_1, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object car_new_value, temp, temp_2, temp_3, temp_4, temp_5, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp_6, next_queue, temp_7, head;
    Object tail, next_queue_holder, queue_holder, temp_8;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, priority;
    double temp_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(43,50);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
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
		  tformat(3,string_constant_10,System_is_running,
			  System_has_paused);
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  temp = scheduler_mode_function(Timing_parameters);
		  tformat(3,string_constant_11,temp,
			  minimum_scheduling_interval_function(Timing_parameters));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  twrite_beginning_of_wide_string(array_constant,
			  FIX((SI_Long)20L));
		  write_floating_point_number(10,
			  DOUBLE_TO_DOUBLE_FLOAT(g2ext_unix_time_as_float()),
			  FIX((SI_Long)9L),FIX((SI_Long)3L),
			  FIX((SI_Long)0L),Nil,Nil,Nil,Nil,
			  FIX((SI_Long)13L),CHR('#'));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  tformat(1,string_constant_12);
		  write_floating_point_number(10,
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_real_time,
			  (SI_Long)0L)),FIX((SI_Long)9L),FIX((SI_Long)3L),
			  FIX((SI_Long)0L),Nil,Nil,Nil,Nil,
			  FIX((SI_Long)13L),CHR('#'));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  tformat(1,string_constant_13);
		  write_floating_point_number(10,
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Current_g2_time,
			  (SI_Long)0L)),FIX((SI_Long)9L),FIX((SI_Long)3L),
			  FIX((SI_Long)0L),Nil,Nil,Nil,Nil,
			  FIX((SI_Long)13L),CHR('#'));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  tformat(1,string_constant_14);
		  temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		  write_floating_point_number(10,
			  DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(Gensym_time) 
			  + 
			  (DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			  (SI_Long)0L) - temp_1)),FIX((SI_Long)9L),
			  FIX((SI_Long)3L),FIX((SI_Long)0L),Nil,Nil,Nil,
			  Nil,FIX((SI_Long)13L),CHR('#'));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  tformat(3,string_constant_15,Gensym_time,
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(Gensym_base_time_as_managed_float,
			  (SI_Long)0L)));
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
		  temp = Priority_of_next_task;
		  tformat(3,string_constant_16,temp,
			  tasks_enqueued_for_current_execution_qm());
		  car_new_value = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	M_CAR(gensymed_symbol_1) = car_new_value;
	if ( ! !TRUEP(constant_queue_next(ISVREF(Immediate_task_queue,
		(SI_Long)2L),Immediate_task_queue))) {
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
		      tformat(1,string_constant_9);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      tformat(1,string_constant_17);
		      temp_2 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      twrite_schedule_task_header();
		      temp_3 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_2 = gensym_cons_1(temp,gensym_cons_1(temp_2,
		    gensym_cons_1(temp_3,
		    task_queue_descriptions(Immediate_task_queue))));
	}
	else
	    temp_2 = Nil;
	if (tasks_enqueued_for_current_execution_qm()) {
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
		      tformat(1,string_constant_9);
		      temp_3 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      tformat(1,string_constant_18);
		      temp_4 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
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
		      twrite_schedule_task_header();
		      temp_5 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    priority = IFIX(Highest_system_priority);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if (priority > IFIX(Lowest_system_priority))
		goto end_loop;
	    ab_loopvar__2 = 
		    task_queue_descriptions(ISVREF(Current_task_queue_vector,
		    priority));
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    priority = priority + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	    temp_3 = gensym_cons_1(temp_3,gensym_cons_1(temp_4,
		    gensym_cons_1(temp_5,temp)));
	}
	else
	    temp_3 = Nil;
	if ( !TRUEP(current_only_p)) {
	    if (tasks_deferred_until_resumption_qm()) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_4 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_19);
			  temp_5 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_schedule_task_header();
			  temp_6 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		priority = IFIX(Highest_system_priority);
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_1:
		if (priority > IFIX(Lowest_system_priority))
		    goto end_loop_1;
		ab_loopvar__2 = 
			task_queue_descriptions(ISVREF(Deferred_task_queue_vector,
			priority));
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		priority = priority + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:
		temp = ab_loopvar_;
		goto end_2;
		temp = Qnil;
	      end_2:;
		temp_4 = gensym_cons_1(temp_4,gensym_cons_1(temp_5,
			gensym_cons_1(temp_6,temp)));
	    }
	    else
		temp_4 = Nil;
	    next_queue = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_real_time_tasks),
		    (SI_Long)0L),(SI_Long)0L));
	    if (EQ(next_queue,CDR(Future_real_time_tasks)) ? TRUEP(Nil) : 
		    TRUEP(next_queue)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_5 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_20);
			  temp_6 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_schedule_task_header();
			  temp_7 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		head = CAR(Future_real_time_tasks);
		tail = CDR(Future_real_time_tasks);
		next_queue_holder = Nil;
		queue_holder = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		next_queue_holder = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,
			(SI_Long)0L),(SI_Long)0L));
	      next_loop_2:
		if (EQ(next_queue_holder,tail))
		    goto end_loop_2;
		queue_holder = next_queue_holder;
		next_queue_holder = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(next_queue_holder,
			(SI_Long)0L),(SI_Long)0L));
		ab_loopvar__2 = 
			task_queue_descriptions(ISVREF(queue_holder,
			(SI_Long)3L));
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		goto next_loop_2;
	      end_loop_2:
		temp = ab_loopvar_;
		goto end_3;
		temp = Qnil;
	      end_3:;
		temp_5 = gensym_cons_1(temp_5,gensym_cons_1(temp_6,
			gensym_cons_1(temp_7,temp)));
	    }
	    else
		temp_5 = Nil;
	    next_queue = 
		    ATOMIC_REF_OBJECT(ISVREF(ISVREF(CAR(Future_g2_time_tasks),
		    (SI_Long)0L),(SI_Long)0L));
	    if (EQ(next_queue,CDR(Future_g2_time_tasks)) ? TRUEP(Nil) : 
		    TRUEP(next_queue)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_6 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_21);
			  temp_7 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
			4);
		  wide_string_bv16 = 
			  allocate_byte_vector_16(FIX((SI_Long)2048L + 
			  (SI_Long)3L));
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
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_schedule_task_header();
			  temp_8 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		head = CAR(Future_g2_time_tasks);
		tail = CDR(Future_g2_time_tasks);
		next_queue_holder = Nil;
		queue_holder = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		next_queue_holder = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,
			(SI_Long)0L),(SI_Long)0L));
	      next_loop_3:
		if (EQ(next_queue_holder,tail))
		    goto end_loop_3;
		queue_holder = next_queue_holder;
		next_queue_holder = 
			ATOMIC_REF_OBJECT(ISVREF(ISVREF(next_queue_holder,
			(SI_Long)0L),(SI_Long)0L));
		ab_loopvar__2 = 
			task_queue_descriptions(ISVREF(queue_holder,
			(SI_Long)3L));
		if (ab_loopvar__2) {
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = last(ab_loopvar__2,_);
		}
		goto next_loop_3;
	      end_loop_3:
		temp = ab_loopvar_;
		goto end_4;
		temp = Qnil;
	      end_4:;
		temp = gensym_cons_1(temp_6,gensym_cons_1(temp_7,
			gensym_cons_1(temp_8,temp)));
	    }
	    else
		temp = Nil;
	    temp = nconc2(temp_4,nconc2(temp_5,temp));
	}
	else
	    temp = Nil;
	temp = nconc2(gensymed_symbol,nconc2(temp_2,nconc2(temp_3,temp)));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Gsi_maximum_idle_interval, Qgsi_maximum_idle_interval);

/* MILLISECONDS-TO-NEXT-SCHEDULER-EVENT */
Object milliseconds_to_next_scheduler_event()
{
    Object temp_1, milliseconds_to_next_task_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp;

    x_note_fn_call(43,51);
    temp = TRUEP(tasks_enqueued_for_current_execution_qm());
    if (temp);
    else {
	tick_the_clock(T);
	temp = TRUEP(tasks_enqueued_for_current_execution_qm());
    }
    if (temp)
	temp_1 = Nil;
    else {
	milliseconds_to_next_task_1 = milliseconds_to_next_task();
	if (milliseconds_to_next_task_1 && (SI_Long)0L >= 
		IFIX(milliseconds_to_next_task_1))
	    temp_1 = Nil;
	else {
	    temp_1 = milliseconds_to_next_task_1;
	    if (temp_1);
	    else
		temp_1 = Most_positive_fixnum;
	    gensymed_symbol = IFIX(temp_1);
	    gensymed_symbol_1 = (SI_Long)3600000L;
	    temp_1 = FIX(MIN(gensymed_symbol,gensymed_symbol_1));
	}
    }
    return VALUES_1(temp_1);
}

/* ENQUEUE-SCHEDULER-EVENTS-IF-NECESSARY */
Object enqueue_scheduler_events_if_necessary(force_scheduler_event_qm)
    Object force_scheduler_event_qm;
{
    Object milliseconds_to_sleep_qm;

    x_note_fn_call(43,52);
    milliseconds_to_sleep_qm =  !TRUEP(force_scheduler_event_qm) ? 
	    milliseconds_to_next_scheduler_event() : Nil;
    if (milliseconds_to_sleep_qm)
	ne_set_next_timer_event(IFIX(milliseconds_to_sleep_qm));
    else
	ne_enqueue_scheduler_event();
    return VALUES_1(milliseconds_to_sleep_qm);
}

Object Number_of_scheduler_workers = UNBOUND;

Object Scheduler_event_done = UNBOUND;

/* COMMAND-LINE-PROCESS-LEGACY */
Object command_line_process_legacy(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(43,53);
    return VALUES_1(arg_qm);
}

static Object array_constant_1;    /* # */

static Object Qlegacy;             /* legacy */

static Object Qcommand_line_argument_processor;  /* command-line-argument-processor */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LEGACY */
Object get_command_line_plist_element_for_legacy()
{
    Object arg_qm, temp;

    x_note_fn_call(43,54);
    arg_qm = get_command_line_flag_argument(2,array_constant_1,T);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlegacy),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

/* COMMAND-LINE-PROCESS-THREADS */
Object command_line_process_threads(arg_qm)
    Object arg_qm;
{
    x_note_fn_call(43,55);
    return VALUES_1(arg_qm);
}

static Object array_constant_2;    /* # */

static Object Qthreads;            /* threads */

/* GET-COMMAND-LINE-PLIST-ELEMENT-FOR-THREADS */
Object get_command_line_plist_element_for_threads()
{
    Object arg_qm, temp;

    x_note_fn_call(43,56);
    arg_qm = get_command_line_keyword_argument(1,array_constant_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qthreads),
	    Qcommand_line_argument_processor);
    return FUNCALL_1(temp,arg_qm);
}

static Object array_constant_3;    /* # */

/* GET-WORKERS-FROM-COMMAND-LINE */
Object get_workers_from_command_line()
{
    Object n_1, temp;

    x_note_fn_call(43,57);
    n_1 = get_command_line_keyword_argument_as_integer(1,array_constant_3);
    temp = n_1;
    if (temp);
    else
	temp = Max_number_of_cores;
    return VALUES_1(temp);
}

static Object array_constant_4;    /* # */

/* LEGACY-MODE-P */
Object legacy_mode_p()
{
    Object temp;

    x_note_fn_call(43,58);
    temp = get_command_line_flag_argument(1,array_constant_4);
    return VALUES_1(temp);
}

Object G2_main_thread = UNBOUND;

static Object Qscheduler_worker_function;  /* scheduler-worker-function */

/* START-SCHEDULER-WORKERS */
Object start_scheduler_workers()
{
    Object temp, temp_1, new_vector, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(43,59);
    Legacy_mode_p = legacy_mode_p();
    Multicore_p =  !TRUEP(Legacy_mode_p) ? T : Nil;
    if (Legacy_mode_p)
	return VALUES_1(Nil);
    temp = get_workers_from_command_line();
    temp_1 = FIXNUM_SUB1(G2_max_threads);
    Number_of_scheduler_workers = FIXNUM_MIN(temp,temp_1);
    Number_of_all_threads = FIXNUM_ADD1(Number_of_scheduler_workers);
    new_vector = make_thread_array(Nil);
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(Number_of_all_threads);
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    temp_1 = format((SI_Long)3L,Nil,"G2 scheduler worker ~D",FIX(index_1));
    svref_new_value = spawn_thread(3,temp_1,
	    SYMBOL_FUNCTION(Qscheduler_worker_function),FIX(index_1));
    ISVREF(new_vector,index_1) = svref_new_value;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    svref_new_value = G2_main_thread;
    SVREF(new_vector,FIX((SI_Long)0L)) = svref_new_value;
    Scheduler_worker_vector = new_vector;
    temp_1 = thread_yield();
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_transform_constituent_array, Qcurrent_transform_constituent_array);

DEFINE_VARIABLE_WITH_SYMBOL(Current_transform_constituent_count, Qcurrent_transform_constituent_count);

DEFINE_VARIABLE_WITH_SYMBOL(Current_saving_context_qm, Qcurrent_saving_context_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Global_table_of_attributes_pane, Qglobal_table_of_attributes_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Global_table_of_hidden_attributes_pane, Qglobal_table_of_hidden_attributes_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Global_table_of_attributes_pane_pointer, Qglobal_table_of_attributes_pane_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Global_table_of_hidden_attributes_pane_pointer, Qglobal_table_of_hidden_attributes_pane_pointer);

DEFINE_VARIABLE_WITH_SYMBOL(Global_nmsci_id_for_attributes_pane, Qglobal_nmsci_id_for_attributes_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Global_nmsci_id_for_hidden_attributes_pane, Qglobal_nmsci_id_for_hidden_attributes_pane);

DEFINE_VARIABLE_WITH_SYMBOL(Global_nms_menu_choiced_item_id, Qglobal_nms_menu_choiced_item_id);

DEFINE_VARIABLE_WITH_SYMBOL(Available_workstation_contexts, Qavailable_workstation_contexts);

DEFINE_VARIABLE_WITH_SYMBOL(Next_continuation_function_qm, Qnext_continuation_function_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Next_old_style_return_function_qm, Qnext_old_style_return_function_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Next_info, Qnext_info);

DEFINE_VARIABLE_WITH_SYMBOL(Next_info_reclaimer_qm, Qnext_info_reclaimer_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Inside_breakpoint_p, Qinside_breakpoint_p);

DEFINE_VARIABLE_WITH_SYMBOL(Return_from_breakpoint_task, Qreturn_from_breakpoint_task);

DEFINE_VARIABLE_WITH_SYMBOL(Duplicates_check_hash, Qduplicates_check_hash);

DEFINE_VARIABLE_WITH_SYMBOL(Things_that_affect_this_formula, Qthings_that_affect_this_formula);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_untransformed_width, Qcurrent_icon_untransformed_width);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_untransformed_height, Qcurrent_icon_untransformed_height);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_variables_plist, Qcurrent_icon_variables_plist);

DEFINE_VARIABLE_WITH_SYMBOL(Current_icon_variables_override_plist, Qcurrent_icon_variables_override_plist);

DEFINE_VARIABLE_WITH_SYMBOL(Stack_of_slot_value_changes, Qstack_of_slot_value_changes);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_generated_contexts, Qlist_of_generated_contexts);

DEFINE_VARIABLE_WITH_SYMBOL(List_of_generated_contexts_tail, Qlist_of_generated_contexts_tail);

/* SCHEDULER-WORKER-FUNCTION */
Object scheduler_worker_function(index_1)
    Object index_1;
{
    Object current_thread_index, current_schedule_task;
    Object priority_of_current_task, time_slice_start_time;
    Object optimized_constant_vector, optimized_constant_vector_index;
    Object optimized_constant_pc, optimized_constant_op_codes;
    Object current_transform_constituent_array;
    Object current_transform_constituent_count, current_saving_context_qm;
    Object scope_conses, vector_of_simple_vector_pools;
    Object vector_of_oversized_simple_vector_pools;
    Object vector_of_simple_float_array_pools;
    Object vector_of_oversized_simple_float_array_pools;
    Object short_simple_gensym_strings, long_simple_gensym_strings;
    Object adjustable_gensym_strings, short_simple_gensym_string_counts;
    Object long_simple_gensym_string_counts, adjustable_gensym_string_counts;
    Object structure_being_reclaimed, skip_list_find_preds;
    Object skip_list_find_succs, package, string_for_returning_floats;
    Object partition_float_union, partition_long_union, gensym_time_array;
    Object global_table_of_attributes_pane;
    Object global_table_of_hidden_attributes_pane;
    Object global_table_of_attributes_pane_pointer;
    Object global_table_of_hidden_attributes_pane_pointer;
    Object global_nmsci_id_for_attributes_pane;
    Object global_nmsci_id_for_hidden_attributes_pane;
    Object global_nms_menu_choiced_item_id, available_workstation_contexts;
    Object specific_structure_for_current_workstation_context;
    Object next_continuation_function_qm, next_old_style_return_function_qm;
    Object next_info, next_info_reclaimer_qm, byte_vector_16_pools;
    Object byte_vector_16_pool_counts, byte_vector_16_pool_number_to_malloc;
    Object inside_breakpoint_p, return_from_breakpoint_task;
    Object duplicates_check_hash, things_that_affect_this_formula;
    Object current_icon_untransformed_width, current_icon_untransformed_height;
    Object current_icon_variables_plist, current_icon_variables_override_plist;
    Object stack_of_slot_value_changes, list_of_generated_contexts;
    Object list_of_generated_contexts_tail;
    Declare_special(57);

    x_note_fn_call(43,60);
    current_thread_index = index_1;
    PUSH_SPECIAL_WITH_SYMBOL(Current_thread_index,Qcurrent_thread_index,current_thread_index,
	    56);
      current_schedule_task = Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Current_schedule_task,Qcurrent_schedule_task,current_schedule_task,
	      55);
	priority_of_current_task = Higher_than_any_priority;
	PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
		54);
	  time_slice_start_time = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Time_slice_start_time,Qtime_slice_start_time,time_slice_start_time,
		  53);
	    optimized_constant_vector = make_array(1,
		    Optimized_constant_vector_length);
	    PUSH_SPECIAL_WITH_SYMBOL(Optimized_constant_vector,Qoptimized_constant_vector,optimized_constant_vector,
		    52);
	      optimized_constant_vector_index = FIX((SI_Long)0L);
	      PUSH_SPECIAL_WITH_SYMBOL(Optimized_constant_vector_index,Qoptimized_constant_vector_index,optimized_constant_vector_index,
		      51);
		optimized_constant_pc = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Optimized_constant_pc,Qoptimized_constant_pc,optimized_constant_pc,
			50);
		  optimized_constant_op_codes = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Optimized_constant_op_codes,Qoptimized_constant_op_codes,optimized_constant_op_codes,
			  49);
		    current_transform_constituent_array = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_transform_constituent_array,Qcurrent_transform_constituent_array,current_transform_constituent_array,
			    48);
		      current_transform_constituent_count = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_transform_constituent_count,Qcurrent_transform_constituent_count,current_transform_constituent_count,
			      47);
			current_saving_context_qm = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Current_saving_context_qm,Qcurrent_saving_context_qm,current_saving_context_qm,
				46);
			  scope_conses = LIST_1(LIST_1(Nil));
			  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				  45);
			    vector_of_simple_vector_pools = 
				    allocate_initial_managed_simple_vector_pool_array(Nil);
			    PUSH_SPECIAL_WITH_SYMBOL(Vector_of_simple_vector_pools,Qvector_of_simple_vector_pools,vector_of_simple_vector_pools,
				    44);
			      vector_of_oversized_simple_vector_pools = 
				      allocate_initial_managed_simple_vector_pool_array(Nil);
			      PUSH_SPECIAL_WITH_SYMBOL(Vector_of_oversized_simple_vector_pools,Qvector_of_oversized_simple_vector_pools,vector_of_oversized_simple_vector_pools,
				      43);
				vector_of_simple_float_array_pools = 
					allocate_initial_vector_of_simple_float_array_pools();
				PUSH_SPECIAL_WITH_SYMBOL(Vector_of_simple_float_array_pools,Qvector_of_simple_float_array_pools,vector_of_simple_float_array_pools,
					42);
				  vector_of_oversized_simple_float_array_pools 
					  = 
					  allocate_initial_vector_of_simple_float_array_pools();
				  PUSH_SPECIAL_WITH_SYMBOL(Vector_of_oversized_simple_float_array_pools,Qvector_of_oversized_simple_float_array_pools,vector_of_oversized_simple_float_array_pools,
					  41);
				    short_simple_gensym_strings = 
					    new_short_simple_gensym_string_vector(Nil);
				    PUSH_SPECIAL_WITH_SYMBOL(Short_simple_gensym_strings,Qshort_simple_gensym_strings,short_simple_gensym_strings,
					    40);
				      long_simple_gensym_strings = 
					      new_partial_buffer_gensym_string_vector(Nil);
				      PUSH_SPECIAL_WITH_SYMBOL(Long_simple_gensym_strings,Qlong_simple_gensym_strings,long_simple_gensym_strings,
					      39);
					adjustable_gensym_strings = 
						new_partial_buffer_gensym_string_vector(Nil);
					PUSH_SPECIAL_WITH_SYMBOL(Adjustable_gensym_strings,Qadjustable_gensym_strings,adjustable_gensym_strings,
						38);
					  short_simple_gensym_string_counts 
						  = 
						  new_short_simple_gensym_string_vector(FIX((SI_Long)0L));
					  PUSH_SPECIAL_WITH_SYMBOL(Short_simple_gensym_string_counts,Qshort_simple_gensym_string_counts,short_simple_gensym_string_counts,
						  37);
					    long_simple_gensym_string_counts 
						    = 
						    new_partial_buffer_gensym_string_vector(FIX((SI_Long)0L));
					    PUSH_SPECIAL_WITH_SYMBOL(Long_simple_gensym_string_counts,Qlong_simple_gensym_string_counts,long_simple_gensym_string_counts,
						    36);
					      adjustable_gensym_string_counts 
						      = 
						      new_partial_buffer_gensym_string_vector(FIX((SI_Long)0L));
					      PUSH_SPECIAL_WITH_SYMBOL(Adjustable_gensym_string_counts,Qadjustable_gensym_string_counts,adjustable_gensym_string_counts,
						      35);
						structure_being_reclaimed 
							= Nil;
						PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
							34);
						  skip_list_find_preds = 
							  make_array(1,
							  Skip_list_global_max_level);
						  PUSH_SPECIAL_WITH_SYMBOL(Skip_list_find_preds,Qskip_list_find_preds,skip_list_find_preds,
							  33);
						    skip_list_find_succs = 
							    make_array(1,
							    Skip_list_global_max_level);
						    PUSH_SPECIAL_WITH_SYMBOL(Skip_list_find_succs,Qskip_list_find_succs,skip_list_find_succs,
							    32);
						      package = Package;
						      PUSH_SPECIAL_WITH_SYMBOL(Package,Qpackage_variable,package,
							      31);
							string_for_returning_floats 
								= 
								make_string(1,
								Size_of_string_for_returning_floats);
							PUSH_SPECIAL_WITH_SYMBOL(String_for_returning_floats,Qstring_for_returning_floats,string_for_returning_floats,
								30);
							  partition_float_union 
								  = 
								  make_partition_float_or_long_union();
							  PUSH_SPECIAL_WITH_SYMBOL(Partition_float_union,Qpartition_float_union,partition_float_union,
								  29);
							    partition_long_union 
								    = 
								    make_partition_float_or_long_union();
							    PUSH_SPECIAL_WITH_SYMBOL(Partition_long_union,Qpartition_long_union,partition_long_union,
								    28);
							      gensym_time_array 
								      = 
								      make_gensym_time_array();
							      PUSH_SPECIAL_WITH_SYMBOL(Gensym_time_array,Qgensym_time_array,gensym_time_array,
								      27);
								global_table_of_attributes_pane 
									= Nil;
								PUSH_SPECIAL_WITH_SYMBOL(Global_table_of_attributes_pane,Qglobal_table_of_attributes_pane,global_table_of_attributes_pane,
									26);
								  global_table_of_hidden_attributes_pane 
									  = 
									  Nil;
								  PUSH_SPECIAL_WITH_SYMBOL(Global_table_of_hidden_attributes_pane,Qglobal_table_of_hidden_attributes_pane,global_table_of_hidden_attributes_pane,
									  25);
								    global_table_of_attributes_pane_pointer 
									    = 
									    Nil;
								    PUSH_SPECIAL_WITH_SYMBOL(Global_table_of_attributes_pane_pointer,Qglobal_table_of_attributes_pane_pointer,global_table_of_attributes_pane_pointer,
									    24);
								      global_table_of_hidden_attributes_pane_pointer 
									      = 
									      Nil;
								      PUSH_SPECIAL_WITH_SYMBOL(Global_table_of_hidden_attributes_pane_pointer,Qglobal_table_of_hidden_attributes_pane_pointer,global_table_of_hidden_attributes_pane_pointer,
									      23);
									global_nmsci_id_for_attributes_pane 
										= 
										Nil;
									PUSH_SPECIAL_WITH_SYMBOL(Global_nmsci_id_for_attributes_pane,Qglobal_nmsci_id_for_attributes_pane,global_nmsci_id_for_attributes_pane,
										22);
									  global_nmsci_id_for_hidden_attributes_pane 
										  = 
										  Nil;
									  PUSH_SPECIAL_WITH_SYMBOL(Global_nmsci_id_for_hidden_attributes_pane,Qglobal_nmsci_id_for_hidden_attributes_pane,global_nmsci_id_for_hidden_attributes_pane,
										  21);
									    global_nms_menu_choiced_item_id 
										    = 
										    Nil;
									    PUSH_SPECIAL_WITH_SYMBOL(Global_nms_menu_choiced_item_id,Qglobal_nms_menu_choiced_item_id,global_nms_menu_choiced_item_id,
										    20);
									      available_workstation_contexts 
										      = 
										      Nil;
									      PUSH_SPECIAL_WITH_SYMBOL(Available_workstation_contexts,Qavailable_workstation_contexts,available_workstation_contexts,
										      19);
										specific_structure_for_current_workstation_context 
											= 
											Nil;
										PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
											18);
										  next_continuation_function_qm 
											  = 
											  Nil;
										  PUSH_SPECIAL_WITH_SYMBOL(Next_continuation_function_qm,Qnext_continuation_function_qm,next_continuation_function_qm,
											  17);
										    next_old_style_return_function_qm 
											    = 
											    Nil;
										    PUSH_SPECIAL_WITH_SYMBOL(Next_old_style_return_function_qm,Qnext_old_style_return_function_qm,next_old_style_return_function_qm,
											    16);
										      next_info 
											      = 
											      Nil;
										      PUSH_SPECIAL_WITH_SYMBOL(Next_info,Qnext_info,next_info,
											      15);
											next_info_reclaimer_qm 
												= 
												Nil;
											PUSH_SPECIAL_WITH_SYMBOL(Next_info_reclaimer_qm,Qnext_info_reclaimer_qm,next_info_reclaimer_qm,
												14);
											  byte_vector_16_pools 
												  = 
												  make_byte_vector_16_pools(Nil);
											  PUSH_SPECIAL_WITH_SYMBOL(Byte_vector_16_pools,Qbyte_vector_16_pools,byte_vector_16_pools,
												  13);
											    byte_vector_16_pool_counts 
												    = 
												    make_byte_vector_16_pools(FIX((SI_Long)0L));
											    PUSH_SPECIAL_WITH_SYMBOL(Byte_vector_16_pool_counts,Qbyte_vector_16_pool_counts,byte_vector_16_pool_counts,
												    12);
											      byte_vector_16_pool_number_to_malloc 
												      = 
												      FIX((SI_Long)-1L);
											      PUSH_SPECIAL_WITH_SYMBOL(Byte_vector_16_pool_number_to_malloc,Qbyte_vector_16_pool_number_to_malloc,byte_vector_16_pool_number_to_malloc,
												      11);
												inside_breakpoint_p 
													= 
													Nil;
												PUSH_SPECIAL_WITH_SYMBOL(Inside_breakpoint_p,Qinside_breakpoint_p,inside_breakpoint_p,
													10);
												  return_from_breakpoint_task 
													  = 
													  Nil;
												  PUSH_SPECIAL_WITH_SYMBOL(Return_from_breakpoint_task,Qreturn_from_breakpoint_task,return_from_breakpoint_task,
													  9);
												    duplicates_check_hash 
													    = 
													    make_duplicates_check_hash_table();
												    PUSH_SPECIAL_WITH_SYMBOL(Duplicates_check_hash,Qduplicates_check_hash,duplicates_check_hash,
													    8);
												      things_that_affect_this_formula 
													      = 
													      Nil;
												      PUSH_SPECIAL_WITH_SYMBOL(Things_that_affect_this_formula,Qthings_that_affect_this_formula,things_that_affect_this_formula,
													      7);
													current_icon_untransformed_width 
														= 
														Nil;
													PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
														6);
													  current_icon_untransformed_height 
														  = 
														  Nil;
													  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
														  5);
													    current_icon_variables_plist 
														    = 
														    Nil;
													    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
														    4);
													      current_icon_variables_override_plist 
														      = 
														      Nil;
													      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
														      3);
														stack_of_slot_value_changes 
															= 
															Nil;
														PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
															2);
														  list_of_generated_contexts 
															  = 
															  Nil;
														  PUSH_SPECIAL_WITH_SYMBOL(List_of_generated_contexts,Qlist_of_generated_contexts,list_of_generated_contexts,
															  1);
														    list_of_generated_contexts_tail 
															    = 
															    Nil;
														    PUSH_SPECIAL_WITH_SYMBOL(List_of_generated_contexts_tail,Qlist_of_generated_contexts_tail,list_of_generated_contexts_tail,
															    0);
														      g2_worker_loop();
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
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* SCHEDULER-WORKER-LOOP */
Object scheduler_worker_loop()
{
    Object priority_to_use, local_immediate_queue, immediate_task_qm;
    Object reclaim_task_qm, function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, temp_2, amf_result;
    Object new_float, current_time, structure_being_reclaimed;
    Object current_schedule_task_old_value;
    double aref_new_value;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(43,61);
    SAVE_STACK();
    if (Current_schedule_task) {
	if (ISVREF(Current_schedule_task,(SI_Long)2L))
	    reclaim_schedule_task_1(Current_schedule_task);
	Current_schedule_task = Nil;
    }
    priority_to_use = FIXNUMP(Priority_of_current_task) && 
	    FIXNUM_GE(Priority_of_current_task,Highest_system_priority) && 
	    FIXNUM_LE(Priority_of_current_task,Lowest_system_priority) ? 
	    Priority_of_current_task : Highest_system_priority;
    local_immediate_queue = ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index));
    immediate_task_qm = Nil;
  next_loop:
    immediate_task_qm = constant_queue_pop_left(2,local_immediate_queue,Nil);
    if ( !TRUEP(immediate_task_qm))
	goto end_loop;
    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
    SVREF(immediate_task_qm,FIX((SI_Long)11L)) = Nil;
    Priority_of_current_task = priority_to_use;
    Current_schedule_task = immediate_task_qm;
    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(immediate_task_qm);
    function = ISVREF(immediate_task_qm,(SI_Long)8L);
    temp = ISVREF(immediate_task_qm,(SI_Long)12L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)16L);
	    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    break;
	  default:
	    break;
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
	exit_current_profiling_context(current_time);
	reclaim_managed_simple_float_array_of_length_1(current_time);
    }
    if (reclaim_task_qm && EQ(immediate_task_qm,Current_schedule_task)) {
	inline_note_reclaim_cons(immediate_task_qm,Nil);
	structure_being_reclaimed = immediate_task_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(immediate_task_qm,(SI_Long)9L));
	  SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	temp_1 = Chain_of_available_schedule_tasks_vector;
	temp_2 = Current_thread_index;
	SVREF(temp_1,temp_2) = immediate_task_qm;
    }
    goto next_loop;
  end_loop:;
    Priority_of_current_task = Higher_than_any_priority;
    Current_schedule_task = Nil;
    LOCK(Scheduler_event_lock);
    if (PUSH_UNWIND_PROTECT(0)) {
      next_loop_1:
	if ( ! !TRUEP(Scheduler_task))
	    goto end_loop_1;
	condition_variable_wait_with_timeout(Scheduler_event_ready,
		Scheduler_worker_loop_interval);
	goto next_loop_1;
      end_loop_1:
	current_schedule_task_old_value = Current_schedule_task;
	temp_1 = Scheduler_task;
	Current_schedule_task = temp_1;
	Scheduler_task = Nil;
	Priority_of_current_task = Scheduler_task_priority;
	Time_slice_start_time = Scheduler_task_time;
	condition_variable_broadcast(Scheduler_event_ready);
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(Scheduler_event_lock);
    CONTINUE_UNWINDING(0);
    execute_task_and_reschedule(Current_schedule_task);
    local_immediate_queue = ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index));
    immediate_task_qm = Nil;
  next_loop_2:
    immediate_task_qm = constant_queue_pop_left(2,local_immediate_queue,Nil);
    if ( !TRUEP(immediate_task_qm))
	goto end_loop_2;
    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
    SVREF(immediate_task_qm,FIX((SI_Long)11L)) = Nil;
    Current_schedule_task = immediate_task_qm;
    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(immediate_task_qm);
    function = ISVREF(immediate_task_qm,(SI_Long)8L);
    temp = ISVREF(immediate_task_qm,(SI_Long)12L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)14L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)15L);
	    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)16L);
	    inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    break;
	  default:
	    break;
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
	exit_current_profiling_context(current_time);
	reclaim_managed_simple_float_array_of_length_1(current_time);
    }
    if (reclaim_task_qm && EQ(immediate_task_qm,Current_schedule_task)) {
	inline_note_reclaim_cons(immediate_task_qm,Nil);
	structure_being_reclaimed = immediate_task_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(immediate_task_qm,(SI_Long)9L));
	  SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	temp_1 = Chain_of_available_schedule_tasks_vector;
	temp_2 = Current_thread_index;
	SVREF(temp_1,temp_2) = immediate_task_qm;
    }
    goto next_loop_2;
  end_loop_2:;
    Priority_of_current_task = Higher_than_any_priority;
    Current_schedule_task = Nil;
    Priority_of_current_task = Higher_than_any_priority;
    RESTORE_STACK();
    return VALUES_1(Nil);
}

void schedule_INIT()
{
    Object temp, reclaim_structure_for_schedule_task_1;
    Object reclaim_structure_for_future_task_queue_holder_1;
    Object all_known_command_line_plist_elements_new_value;
    Object AB_package, list_constant_2, list_constant_4;
    Object Qcommand_line_plist_element_getter;
    Object Qget_command_line_plist_element_for_threads;
    Object Qcommand_line_process_threads, list_constant_3;
    Object Qget_command_line_plist_element_for_legacy;
    Object Qcommand_line_process_legacy, string_constant_26, list_constant_1;
    Object Qclocks, Qfixnum_time_interval, Kfuncall;
    Object Qscheduler_worker_loop_interval, Qschedule, list_constant;
    Object Qfuture_task_queue_marker, Qfuture_task_queue_max_level;
    Object Qfuture_task_queue_holder, Qreclaim_structure;
    Object Qoutstanding_future_task_queue_holder_count;
    Object Qfuture_task_queue_holder_structure_memory_usage, Qutilities2;
    Object string_constant_25, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_24;
    Object Qfuture_g2_time_tasks, Qfuture_real_time_tasks;
    Object Qdeferred_task_queue_vector, Qcurrent_task_queue_vector;
    Object Qimmediate_task_queue_vector, Qimmediate_task_queue;
    Object Qschedule_task_arg_limit, Qschedule_task;
    Object Qoutstanding_schedule_task_count;
    Object Qschedule_task_structure_memory_usage, string_constant_23;
    Object string_constant_22, Qunique_structure_type_of_ab_name_qm;
    Object Qschedule_task_arg_offset, Qlower_than_any_priority;
    Object Qhigher_than_any_priority, Qlowest_system_priority;
    Object Qhighest_system_priority, Qhighest_user_priority;
    Object Qhow_many_priorities_qm;

    x_note_fn_call(43,62);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhow_many_priorities_qm = STATIC_SYMBOL("HOW-MANY-PRIORITIES\?",
	    AB_package);
    SET_SYMBOL_VALUE(Qhow_many_priorities_qm,FIX((SI_Long)10L));
    Qhighest_user_priority = STATIC_SYMBOL("HIGHEST-USER-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qhighest_user_priority,FIX((SI_Long)1L));
    Qhighest_system_priority = STATIC_SYMBOL("HIGHEST-SYSTEM-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qhighest_system_priority,FIX((SI_Long)0L));
    Qlowest_system_priority = STATIC_SYMBOL("LOWEST-SYSTEM-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qlowest_system_priority,FIX((SI_Long)11L));
    Qhigher_than_any_priority = STATIC_SYMBOL("HIGHER-THAN-ANY-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qhigher_than_any_priority,FIX((SI_Long)-1L));
    Qlower_than_any_priority = STATIC_SYMBOL("LOWER-THAN-ANY-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qlower_than_any_priority,FIX((SI_Long)12L));
    Qschedule_task_arg_offset = STATIC_SYMBOL("SCHEDULE-TASK-ARG-OFFSET",
	    AB_package);
    SET_SYMBOL_VALUE(Qschedule_task_arg_offset,FIX((SI_Long)13L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qschedule_task = STATIC_SYMBOL("SCHEDULE-TASK",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    Qschedule_task,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qschedule_task,
	    Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_schedule_task == UNBOUND)
	The_type_description_of_schedule_task = Nil;
    string_constant_22 = 
	    STATIC_STRING("43Dy8m83mey1n83mey8n8k1l8n0000001n1m83=ey3ky1n8y83-5gy1l83-CQy1m83-DFy1m83-COy83-CPyk3Dyk0k0");
    temp = The_type_description_of_schedule_task;
    The_type_description_of_schedule_task = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_22));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    The_type_description_of_schedule_task,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qschedule_task,
	    The_type_description_of_schedule_task,Qtype_description_of_type);
    Qoutstanding_schedule_task_count = 
	    STATIC_SYMBOL("OUTSTANDING-SCHEDULE-TASK-COUNT",AB_package);
    Qschedule_task_structure_memory_usage = 
	    STATIC_SYMBOL("SCHEDULE-TASK-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_23 = STATIC_STRING("1q83mey8s83-nky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_schedule_task_count);
    push_optimized_constant(Qschedule_task_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    Qchain_of_available_schedule_tasks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SCHEDULE-TASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_schedule_tasks,
	    Chain_of_available_schedule_tasks);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_schedule_tasks,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qschedule_task_count = STATIC_SYMBOL("SCHEDULE-TASK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qschedule_task_count,Schedule_task_count);
    record_system_variable(Qschedule_task_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_schedule_tasks_vector == UNBOUND)
	Chain_of_available_schedule_tasks_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qschedule_task_structure_memory_usage,
	    STATIC_FUNCTION(schedule_task_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_schedule_task_count,
	    STATIC_FUNCTION(outstanding_schedule_task_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_schedule_task_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_schedule_task,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qschedule_task,
	    reclaim_structure_for_schedule_task_1);
    Qschedule_task_arg_limit = STATIC_SYMBOL("SCHEDULE-TASK-ARG-LIMIT",
	    AB_package);
    SET_SYMBOL_VALUE(Qschedule_task_arg_limit,FIX((SI_Long)4L));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qimmediate_task_queue = STATIC_SYMBOL("IMMEDIATE-TASK-QUEUE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qimmediate_task_queue,Immediate_task_queue);
    Qschedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    record_system_variable(Qimmediate_task_queue,Qschedule,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qimmediate_task_queue_vector = 
	    STATIC_SYMBOL("IMMEDIATE-TASK-QUEUE-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qimmediate_task_queue_vector,
	    Immediate_task_queue_vector);
    record_system_variable(Qimmediate_task_queue_vector,Qschedule,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcurrent_task_queue_vector = STATIC_SYMBOL("CURRENT-TASK-QUEUE-VECTOR",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_task_queue_vector,
	    Current_task_queue_vector);
    record_system_variable(Qcurrent_task_queue_vector,Qschedule,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qdeferred_task_queue_vector = 
	    STATIC_SYMBOL("DEFERRED-TASK-QUEUE-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdeferred_task_queue_vector,
	    Deferred_task_queue_vector);
    record_system_variable(Qdeferred_task_queue_vector,Qschedule,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qfuture_real_time_tasks = STATIC_SYMBOL("FUTURE-REAL-TIME-TASKS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfuture_real_time_tasks,Future_real_time_tasks);
    record_system_variable(Qfuture_real_time_tasks,Qschedule,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qfuture_g2_time_tasks = STATIC_SYMBOL("FUTURE-G2-TIME-TASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfuture_g2_time_tasks,Future_g2_time_tasks);
    record_system_variable(Qfuture_g2_time_tasks,Qschedule,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    if (The_type_description_of_future_task_queue_holder == UNBOUND)
	The_type_description_of_future_task_queue_holder = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83hZy1m83hZy8k1l8k0000001o1m83*gy9k1m83=ey3ky1n8y83-3my01m83My83-AHykpk0k0");
    temp = The_type_description_of_future_task_queue_holder;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_future_task_queue_holder = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct,
	    The_type_description_of_future_task_queue_holder,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qfuture_task_queue_holder = STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER",
	    AB_package);
    mutate_global_property(Qfuture_task_queue_holder,
	    The_type_description_of_future_task_queue_holder,
	    Qtype_description_of_type);
    Qoutstanding_future_task_queue_holder_count = 
	    STATIC_SYMBOL("OUTSTANDING-FUTURE-TASK-QUEUE-HOLDER-COUNT",
	    AB_package);
    Qfuture_task_queue_holder_structure_memory_usage = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_25 = STATIC_STRING("1q83hZy8s83-VDy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_future_task_queue_holder_count);
    push_optimized_constant(Qfuture_task_queue_holder_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_future_task_queue_holders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FUTURE-TASK-QUEUE-HOLDERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_future_task_queue_holders,
	    Chain_of_available_future_task_queue_holders);
    record_system_variable(Qchain_of_available_future_task_queue_holders,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qfuture_task_queue_holder_count = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfuture_task_queue_holder_count,
	    Future_task_queue_holder_count);
    record_system_variable(Qfuture_task_queue_holder_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_future_task_queue_holders_vector == UNBOUND)
	Chain_of_available_future_task_queue_holders_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qfuture_task_queue_holder_structure_memory_usage,
	    STATIC_FUNCTION(future_task_queue_holder_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_future_task_queue_holder_count,
	    STATIC_FUNCTION(outstanding_future_task_queue_holder_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_future_task_queue_holder_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_future_task_queue_holder,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qfuture_task_queue_holder,
	    reclaim_structure_for_future_task_queue_holder_1);
    Qfuture_task_queue_max_level = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-MAX-LEVEL",AB_package);
    SET_SYMBOL_VALUE(Qfuture_task_queue_max_level,FIX((SI_Long)15L));
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qsystem_is_running = STATIC_SYMBOL("SYSTEM-IS-RUNNING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_is_running,System_is_running);
    record_system_variable(Qsystem_is_running,Qschedule,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qsystem_has_paused = STATIC_SYMBOL("SYSTEM-HAS-PAUSED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_has_paused,System_has_paused);
    record_system_variable(Qsystem_has_paused,Qschedule,Nil,Qnil,Qnil,Qnil,
	    Qnil);
    Qsystem_has_aborted = STATIC_SYMBOL("SYSTEM-HAS-ABORTED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_has_aborted,System_has_aborted);
    record_system_variable(Qsystem_has_aborted,Qschedule,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    Qcurrent_schedule_task = STATIC_SYMBOL("CURRENT-SCHEDULE-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_schedule_task,Current_schedule_task);
    record_system_variable(Qcurrent_schedule_task,Qschedule,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qpriority_of_current_task = STATIC_SYMBOL("PRIORITY-OF-CURRENT-TASK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_of_current_task,
	    Priority_of_current_task);
    Qclocks = STATIC_SYMBOL("CLOCKS",AB_package);
    record_system_variable(Qpriority_of_current_task,Qclocks,
	    FIX((SI_Long)-1L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_of_next_task = STATIC_SYMBOL("PRIORITY-OF-NEXT-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_of_next_task,Priority_of_next_task);
    record_system_variable(Qpriority_of_next_task,Qclocks,
	    Qmost_positive_fixnum,Qnil,Qnil,Qnil,Qnil);
    Qfuture_task_queue_marker = STATIC_SYMBOL("FUTURE-TASK-QUEUE-MARKER",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfuture_task_queue_marker,
	    Future_task_queue_marker);
    list_constant = STATIC_CONS(Qfuture_task_queue_marker,Qnil);
    SET_SYMBOL_VALUE(Qfuture_task_queue_marker,list_constant);
    Qget_or_create_future_task_queue_for_task = 
	    STATIC_SYMBOL("GET-OR-CREATE-FUTURE-TASK-QUEUE-FOR-TASK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_or_create_future_task_queue_for_task,
	    STATIC_FUNCTION(get_or_create_future_task_queue_for_task,NIL,
	    FALSE,1,1));
    Qreal_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    Qscheduler_has_been_initialized_p = 
	    STATIC_SYMBOL("SCHEDULER-HAS-BEEN-INITIALIZED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscheduler_has_been_initialized_p,
	    Scheduler_has_been_initialized_p);
    record_system_variable(Qscheduler_has_been_initialized_p,Qschedule,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    if (Scheduler_task == UNBOUND)
	Scheduler_task = Nil;
    if (Scheduler_task_time == UNBOUND)
	Scheduler_task_time = FIX((SI_Long)0L);
    if (Multicore_p == UNBOUND)
	Multicore_p = Nil;
    Qscheduler_worker_loop_interval = 
	    STATIC_SYMBOL("SCHEDULER-WORKER-LOOP-INTERVAL",AB_package);
    SET_SYMBOL_VALUE(Qscheduler_worker_loop_interval,FIX((SI_Long)1L));
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    Qclear_g2_schedule = STATIC_SYMBOL("CLEAR-G2-SCHEDULE",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_g2_schedule,
	    STATIC_FUNCTION(clear_g2_schedule,NIL,FALSE,0,0));
    if (Time_slice_start_time == UNBOUND)
	Time_slice_start_time = FIX((SI_Long)0L);
    Qmaximum_time_slice_size = STATIC_SYMBOL("MAXIMUM-TIME-SLICE-SIZE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmaximum_time_slice_size,
	    Maximum_time_slice_size);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qfixnum_time_interval = STATIC_SYMBOL("FIXNUM-TIME-INTERVAL",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qfixnum_time_interval,FIX((SI_Long)50L));
    record_system_variable(Qmaximum_time_slice_size,Qclocks,
	    list_constant_1,Qnil,Qnil,Qnil,Qnil);
    float_constant = STATIC_FLOAT(0.0);
    string_constant = 
	    STATIC_STRING("Time Cyclic G2-Running\? Priority Function-and-Args");
    string_constant_1 = STATIC_STRING(" <~a>");
    string_constant_2 = STATIC_STRING(" ~a");
    string_constant_3 = STATIC_STRING(" [~a]");
    string_constant_4 = STATIC_STRING(" [~a ~a]");
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    string_constant_5 = STATIC_STRING("T    ");
    string_constant_6 = STATIC_STRING("NIL  ");
    string_constant_7 = STATIC_STRING("~a~a   ");
    string_constant_8 = STATIC_STRING(" ");
    string_constant_9 = STATIC_STRING("");
    string_constant_10 = 
	    STATIC_STRING("System-is-running = ~a, System-has-paused = ~a");
    string_constant_11 = 
	    STATIC_STRING("Scheduler-mode = ~a, Minimum-scheduling-interval = ~a");
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    string_constant_12 = STATIC_STRING("Current-real-time = ");
    string_constant_13 = STATIC_STRING("Current-g2-time   = ");
    string_constant_14 = STATIC_STRING("Gensym-time       = ");
    string_constant_15 = 
	    STATIC_STRING(" (Gensym-time = ~a, gensym-base-time-as-managed-float = ~a)");
    string_constant_16 = 
	    STATIC_STRING("Priority-of-next-task = ~a, current-tasks-enqueued\? = ~a");
    string_constant_17 = STATIC_STRING("Immediate-task-queue");
    string_constant_18 = STATIC_STRING("Current-task-queue-vector");
    string_constant_19 = STATIC_STRING("Deferred-task-queue-vector");
    string_constant_20 = STATIC_STRING("Future-real-time-tasks");
    string_constant_21 = STATIC_STRING("Future-g2-time-tasks");
    if (Gsi_maximum_idle_interval == UNBOUND)
	Gsi_maximum_idle_interval = FIX((SI_Long)1000L);
    if (Number_of_scheduler_workers == UNBOUND)
	Number_of_scheduler_workers = Nil;
    if (Scheduler_worker_vector == UNBOUND)
	Scheduler_worker_vector = Nil;
    if (Legacy_mode_p == UNBOUND)
	Legacy_mode_p = Nil;
    string_constant_26 = STATIC_STRING("SCHEDULER-EVENT-LOCK");
    if (Scheduler_event_lock == UNBOUND)
	Scheduler_event_lock = make_lock(2,Kname,string_constant_26);
    if (Scheduler_event_ready == UNBOUND)
	Scheduler_event_ready = make_condition_variable(2,Klock,
		Scheduler_event_lock);
    if (Scheduler_event_done == UNBOUND)
	Scheduler_event_done = make_condition_variable(2,Klock,
		Scheduler_event_lock);
    Qcommand_line_process_legacy = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-LEGACY",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_legacy,
	    STATIC_FUNCTION(command_line_process_legacy,NIL,FALSE,1,1));
    Qlegacy = STATIC_SYMBOL("LEGACY",AB_package);
    Qcommand_line_argument_processor = 
	    STATIC_SYMBOL("COMMAND-LINE-ARGUMENT-PROCESSOR",AB_package);
    mutate_global_property(Qlegacy,Qcommand_line_process_legacy,
	    Qcommand_line_argument_processor);
    array_constant_1 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_legacy = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-LEGACY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_legacy,
	    STATIC_FUNCTION(get_command_line_plist_element_for_legacy,NIL,
	    FALSE,0,0));
    Qcommand_line_plist_element_getter = 
	    STATIC_SYMBOL("COMMAND-LINE-PLIST-ELEMENT-GETTER",AB_package);
    mutate_global_property(Qlegacy,
	    Qget_command_line_plist_element_for_legacy,
	    Qcommand_line_plist_element_getter);
    list_constant_3 = STATIC_CONS(Qlegacy,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_3,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    Qcommand_line_process_threads = 
	    STATIC_SYMBOL("COMMAND-LINE-PROCESS-THREADS",AB_package);
    SET_SYMBOL_FUNCTION(Qcommand_line_process_threads,
	    STATIC_FUNCTION(command_line_process_threads,NIL,FALSE,1,1));
    Qthreads = STATIC_SYMBOL("THREADS",AB_package);
    mutate_global_property(Qthreads,Qcommand_line_process_threads,
	    Qcommand_line_argument_processor);
    array_constant_2 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qget_command_line_plist_element_for_threads = 
	    STATIC_SYMBOL("GET-COMMAND-LINE-PLIST-ELEMENT-FOR-THREADS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_command_line_plist_element_for_threads,
	    STATIC_FUNCTION(get_command_line_plist_element_for_threads,NIL,
	    FALSE,0,0));
    mutate_global_property(Qthreads,
	    Qget_command_line_plist_element_for_threads,
	    Qcommand_line_plist_element_getter);
    list_constant_4 = STATIC_CONS(Qthreads,FIX((SI_Long)0L));
    all_known_command_line_plist_elements_new_value = adjoin(2,
	    list_constant_4,All_known_command_line_plist_elements);
    All_known_command_line_plist_elements = 
	    all_known_command_line_plist_elements_new_value;
    array_constant_3 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    G2_main_thread = current_thread();
    Qscheduler_worker_function = STATIC_SYMBOL("SCHEDULER-WORKER-FUNCTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qscheduler_worker_function,
	    STATIC_FUNCTION(scheduler_worker_function,NIL,FALSE,1,1));
}
