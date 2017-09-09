/* schdle.c
 * Input file:  schedule.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "schdle.h"


Object The_type_description_of_schedule_task = UNBOUND;

Object Chain_of_available_schedule_tasks = UNBOUND;

Object Schedule_task_count = UNBOUND;

/* SCHEDULE-TASK-STRUCTURE-MEMORY-USAGE */
Object schedule_task_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(44,0);
    temp = Schedule_task_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)15L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SCHEDULE-TASK-COUNT */
Object outstanding_schedule_task_count()
{
    Object def_structure_schedule_task_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(44,1);
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
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(44,2);
    inline_note_reclaim_cons(schedule_task,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = schedule_task;
    reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
    SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_schedule_tasks;
    SVREF(schedule_task,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_schedule_tasks = schedule_task;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SCHEDULE-TASK */
Object reclaim_structure_for_schedule_task(schedule_task)
    Object schedule_task;
{
    x_note_fn_call(44,3);
    return reclaim_schedule_task_1(schedule_task);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* MAKE-PERMANENT-SCHEDULE-TASK-STRUCTURE-INTERNAL */
Object make_permanent_schedule_task_structure_internal()
{
    Object def_structure_schedule_task_variable;
    Object defstruct_g2_schedule_task_variable, the_array, svref_new_value;
    SI_Long schedule_task_count_new_value, gensymed_symbol, gensymed_symbol_1;
    SI_Long i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,4);
    def_structure_schedule_task_variable = Nil;
    schedule_task_count_new_value = IFIX(Schedule_task_count) + (SI_Long)50L;
    Schedule_task_count = FIX(schedule_task_count_new_value);
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_schedule_task_variable = Nil;
	gensymed_symbol_1 = (SI_Long)15L;
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
	svref_new_value = 
		allocate_managed_simple_float_array(FIX((SI_Long)2L));
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)1L)) = 
		svref_new_value;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	svref_new_value = Chain_of_available_schedule_tasks;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		svref_new_value;
	Chain_of_available_schedule_tasks = 
		def_structure_schedule_task_variable;
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
    Object def_structure_schedule_task_variable;

    x_note_fn_call(44,5);
    def_structure_schedule_task_variable = Chain_of_available_schedule_tasks;
    if (def_structure_schedule_task_variable) {
	Chain_of_available_schedule_tasks = 
		ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
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
    Object f, gensym_pop_store, cons_1, next_cons, temp;
    SI_Long i, svref_arg_2;

    x_note_fn_call(44,6);
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
	    temp = Available_gensym_conses;
	    M_CDR(cons_1) = temp;
	    Available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	reclaimers = next_cons;
	f = gensym_pop_store;
	if (f) {
	    FUNCALL_1(f,ISVREF(Structure_being_reclaimed,i + 
		    IFIX(Schedule_task_arg_offset)));
	    temp = Structure_being_reclaimed;
	    svref_arg_2 = i + IFIX(Schedule_task_arg_offset);
	    ISVREF(temp,svref_arg_2) = Nil;
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

    x_note_fn_call(44,7);
    dot_object_dot = schedule_task;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)2L,stream,"TASK (");
    format((SI_Long)3L,stream,"~S",ISVREF(schedule_task,(SI_Long)7L));
    ab_loop_bind_ = IFIX(ISVREF(schedule_task,(SI_Long)10L));
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
    x_note_fn_call(44,8);
    return VALUES_1(Nil);
}

Object Immediate_task_queue = UNBOUND;

Object Current_task_queue_vector = UNBOUND;

Object Deferred_task_queue_vector = UNBOUND;

Object Future_real_time_tasks = UNBOUND;

Object Future_g2_time_tasks = UNBOUND;

Object The_type_description_of_future_task_queue_holder = UNBOUND;

Object Chain_of_available_future_task_queue_holders = UNBOUND;

Object Future_task_queue_holder_count = UNBOUND;

/* FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-MEMORY-USAGE */
Object future_task_queue_holder_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(44,9);
    temp = Future_task_queue_holder_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FUTURE-TASK-QUEUE-HOLDER-COUNT */
Object outstanding_future_task_queue_holder_count()
{
    Object def_structure_future_task_queue_holder_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(44,10);
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
    Object svref_new_value;

    x_note_fn_call(44,11);
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    svref_new_value = Chain_of_available_future_task_queue_holders;
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_future_task_queue_holders = future_task_queue_holder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FUTURE-TASK-QUEUE-HOLDER */
Object reclaim_structure_for_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    x_note_fn_call(44,12);
    return reclaim_future_task_queue_holder_1_1(future_task_queue_holder);
}

/* MAKE-PERMANENT-FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-INTERNAL */
Object make_permanent_future_task_queue_holder_structure_internal()
{
    Object def_structure_future_task_queue_holder_variable, the_array;
    Object defstruct_g2_future_task_queue_holder_variable, svref_new_value;
    SI_Long future_task_queue_holder_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(44,13);
    def_structure_future_task_queue_holder_variable = Nil;
    future_task_queue_holder_count_new_value = 
	    IFIX(Future_task_queue_holder_count) + (SI_Long)50L;
    Future_task_queue_holder_count = 
	    FIX(future_task_queue_holder_count_new_value);
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)4L;
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
	svref_new_value = allocate_managed_float_box();
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)1L)) = svref_new_value;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	svref_new_value = Chain_of_available_future_task_queue_holders;
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_future_task_queue_holders = 
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
    Object def_structure_future_task_queue_holder_variable;

    x_note_fn_call(44,14);
    def_structure_future_task_queue_holder_variable = 
	    Chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	Chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    return VALUES_1(def_structure_future_task_queue_holder_variable);
}

/* RECLAIM-FUTURE-TASK-QUEUE-HOLDER */
Object reclaim_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    Object svref_new_value;

    x_note_fn_call(44,15);
    reclaim_constant_queue(ISVREF(future_task_queue_holder,(SI_Long)3L));
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    svref_new_value = Chain_of_available_future_task_queue_holders;
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_future_task_queue_holders = future_task_queue_holder;
    return VALUES_1(Nil);
}

Object System_has_aborted = UNBOUND;

static Object Qabort_g2;           /* abort */

static Object Qrunning;            /* running */

static Object Qpaused;             /* paused */

static Object Qreset;              /* reset */

/* CURRENT-G2-RUN-STATE */
Object current_g2_run_state()
{
    x_note_fn_call(44,16);
    if (System_has_aborted)
	return VALUES_1(Qabort_g2);
    else if (System_is_running)
	return VALUES_1(Qrunning);
    else if (System_has_paused)
	return VALUES_1(Qpaused);
    else
	return VALUES_1(Qreset);
}

Object Current_schedule_task = UNBOUND;

Object Priority_of_current_task = UNBOUND;

Object Priority_of_next_task = UNBOUND;

Object Future_task_queue_marker = UNBOUND;

/* GET-OR-CREATE-FUTURE-TASK-QUEUE-FOR-TASK */
Object get_or_create_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object priority, g2_running_task_qm, holder_trailer, queue_holder;
    Object holder_priority, insert_new_qm, temp;
    Object def_structure_future_task_queue_holder_variable, new_holder;
    Object new_queue, aref_arg_1, new_holder_1;
    double task_time, holder_task_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,17);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	priority = ISVREF(schedule_task,(SI_Long)4L);
	task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	holder_trailer = g2_running_task_qm ? Future_g2_time_tasks : 
		Future_real_time_tasks;
	queue_holder = ISVREF(holder_trailer,(SI_Long)0L);
      next_loop:
	if (queue_holder) {
	    holder_task_time = DFLOAT_ISAREF_1(ISVREF(queue_holder,
		    (SI_Long)1L),(SI_Long)0L);
	    holder_priority = ISVREF(queue_holder,(SI_Long)2L);
	    insert_new_qm = Nil;
	    arg = holder_task_time;
	    arg_1 = task_time;
	    if ( !(arg < arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))) {
		arg = task_time;
		arg_1 = holder_task_time;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    if (FIXNUM_EQ(holder_priority,priority)) {
			temp = ISVREF(queue_holder,(SI_Long)3L);
			goto end_1;
		    }
		    else if (FIXNUM_GT(priority,holder_priority))
			insert_new_qm = T;
		}
		else
		    insert_new_qm = T;
		if (insert_new_qm) {
		    def_structure_future_task_queue_holder_variable = 
			    Chain_of_available_future_task_queue_holders;
		    if (def_structure_future_task_queue_holder_variable)
			Chain_of_available_future_task_queue_holders = 
				ISVREF(def_structure_future_task_queue_holder_variable,
				(SI_Long)0L);
		    else
			def_structure_future_task_queue_holder_variable = 
				make_permanent_future_task_queue_holder_structure_internal();
		    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
			    Nil);
		    new_holder = 
			    def_structure_future_task_queue_holder_variable;
		    new_queue = make_empty_constant_queue();
		    SVREF(new_queue,FIX((SI_Long)2L)) = 
			    Future_task_queue_marker;
		    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
		    aref_arg_1 = ISVREF(new_holder,(SI_Long)1L);
		    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,task_time);
		    SVREF(new_holder,FIX((SI_Long)2L)) = priority;
		    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
		    new_holder_1 = new_holder;
		    SVREF(new_holder_1,FIX((SI_Long)0L)) = queue_holder;
		    SVREF(holder_trailer,FIX((SI_Long)0L)) = new_holder_1;
		    temp = ISVREF(new_holder_1,(SI_Long)3L);
		    goto end_1;
		}
	    }
	}
	else {
	    def_structure_future_task_queue_holder_variable = 
		    Chain_of_available_future_task_queue_holders;
	    if (def_structure_future_task_queue_holder_variable)
		Chain_of_available_future_task_queue_holders = 
			ISVREF(def_structure_future_task_queue_holder_variable,
			(SI_Long)0L);
	    else
		def_structure_future_task_queue_holder_variable = 
			make_permanent_future_task_queue_holder_structure_internal();
	    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
		    Nil);
	    new_holder = def_structure_future_task_queue_holder_variable;
	    new_queue = make_empty_constant_queue();
	    SVREF(new_queue,FIX((SI_Long)2L)) = Future_task_queue_marker;
	    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
	    aref_arg_1 = ISVREF(new_holder,(SI_Long)1L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,task_time);
	    SVREF(new_holder,FIX((SI_Long)2L)) = priority;
	    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
	    new_holder_1 = new_holder;
	    SVREF(new_holder_1,FIX((SI_Long)0L)) = Nil;
	    SVREF(holder_trailer,FIX((SI_Long)0L)) = new_holder_1;
	    temp = ISVREF(new_holder_1,(SI_Long)3L);
	    goto end_1;
	}
	holder_trailer = queue_holder;
	queue_holder = ISVREF(queue_holder,(SI_Long)0L);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* DELETE-FUTURE-TASK-QUEUE-FOR-TASK */
Object delete_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object priority, g2_running_task_qm, holder_trailer, queue_holder;
    Object svref_new_value;
    char temp;
    double task_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,18);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	priority = ISVREF(schedule_task,(SI_Long)4L);
	task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	holder_trailer = g2_running_task_qm ? Future_g2_time_tasks : 
		Future_real_time_tasks;
	queue_holder = ISVREF(holder_trailer,(SI_Long)0L);
      next_loop:
	if ( !TRUEP(queue_holder))
	    goto end_loop;
	if (FIXNUM_EQ(priority,ISVREF(queue_holder,(SI_Long)2L))) {
	    arg = task_time;
	    arg_1 = DFLOAT_ISAREF_1(ISVREF(queue_holder,(SI_Long)1L),
		    (SI_Long)0L);
	    temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    svref_new_value = ISVREF(queue_holder,(SI_Long)0L);
	    SVREF(holder_trailer,FIX((SI_Long)0L)) = svref_new_value;
	    reclaim_future_task_queue_holder(queue_holder);
	    goto end_find_queue;
	}
	holder_trailer = queue_holder;
	queue_holder = ISVREF(queue_holder,(SI_Long)0L);
	goto next_loop;
      end_loop:
      end_find_queue:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

Object Current_real_time = UNBOUND;

Object Current_g2_time = UNBOUND;

Object Timing_parameters = UNBOUND;

static Object Qreal_time;          /* real-time */

/* UNPACK-FUTURE-TASKS-INTO-CURRENT-TASK-QUEUES */
Object unpack_future_tasks_into_current_task_queues(g2_clock_ticked_qm)
    Object g2_clock_ticked_qm;
{
    Object g2_running_qm, scheduler_mode, future_queue, next_future_task;
    Object queue_holder, next_queue_holder, priority, queue_to_fill;
    Object queue_to_empty, head, tail, old_tail, future_real_time_tasks_qm;
    Object future_g2_time_tasks_qm, svref_arg_1;
    char temp;
    double real_time, g2_time, latest_dequeue_time, arg, arg_1;
    double next_real_task_time, next_g2_task_time;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,19);
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
	    next_future_task = ISVREF(future_queue,(SI_Long)0L);
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
	    queue_holder = ISVREF(future_queue,(SI_Long)0L);
	    next_queue_holder = queue_holder ? ISVREF(queue_holder,
		    (SI_Long)0L) : Qnil;
	    priority = ISVREF(queue_holder,(SI_Long)2L);
	    queue_to_fill = ISVREF(Current_task_queue_vector,IFIX(priority));
	    queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
	    if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		head = ISVREF(queue_to_empty,(SI_Long)0L);
		tail = ISVREF(queue_to_empty,(SI_Long)1L);
		SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
		    SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
		else {
		    old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
		    SVREF(old_tail,FIX((SI_Long)0L)) = head;
		    SVREF(head,FIX((SI_Long)1L)) = old_tail;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
	    }
	    reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,Priority_of_next_task))
		Priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop;
	  end_loop:;
	}
	else if ( !EQ(scheduler_mode,Qreal_time)) {
	    future_queue = Future_real_time_tasks;
	    latest_dequeue_time = real_time;
	    next_future_task = Nil;
	  next_loop_1:
	    next_future_task = ISVREF(future_queue,(SI_Long)0L);
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
	    queue_holder = ISVREF(future_queue,(SI_Long)0L);
	    next_queue_holder = queue_holder ? ISVREF(queue_holder,
		    (SI_Long)0L) : Qnil;
	    priority = ISVREF(queue_holder,(SI_Long)2L);
	    queue_to_fill = ISVREF(Current_task_queue_vector,IFIX(priority));
	    queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
	    if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		head = ISVREF(queue_to_empty,(SI_Long)0L);
		tail = ISVREF(queue_to_empty,(SI_Long)1L);
		SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
		    SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
		else {
		    old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
		    SVREF(old_tail,FIX((SI_Long)0L)) = head;
		    SVREF(head,FIX((SI_Long)1L)) = old_tail;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
	    }
	    reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,Priority_of_next_task))
		Priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_1;
	  end_loop_1:;
	    future_queue = Future_g2_time_tasks;
	    latest_dequeue_time = g2_time;
	    next_future_task = Nil;
	  next_loop_2:
	    next_future_task = ISVREF(future_queue,(SI_Long)0L);
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
	    queue_holder = ISVREF(future_queue,(SI_Long)0L);
	    next_queue_holder = queue_holder ? ISVREF(queue_holder,
		    (SI_Long)0L) : Qnil;
	    priority = ISVREF(queue_holder,(SI_Long)2L);
	    queue_to_fill = ISVREF(Current_task_queue_vector,IFIX(priority));
	    queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
	    if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		head = ISVREF(queue_to_empty,(SI_Long)0L);
		tail = ISVREF(queue_to_empty,(SI_Long)1L);
		SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
		    SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
		else {
		    old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
		    SVREF(old_tail,FIX((SI_Long)0L)) = head;
		    SVREF(head,FIX((SI_Long)1L)) = old_tail;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
	    }
	    reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,Priority_of_next_task))
		Priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_2;
	  end_loop_2:;
	}
	else {
	    future_real_time_tasks_qm = ISVREF(Future_real_time_tasks,
		    (SI_Long)0L);
	    next_real_task_time = future_real_time_tasks_qm ? 
		    DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
		    (SI_Long)1L),(SI_Long)0L) : 0.0;
	    future_g2_time_tasks_qm = ISVREF(Future_g2_time_tasks,(SI_Long)0L);
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
		queue_holder = ISVREF(Future_g2_time_tasks,(SI_Long)0L);
		next_queue_holder = queue_holder ? ISVREF(queue_holder,
			(SI_Long)0L) : Qnil;
		priority = ISVREF(queue_holder,(SI_Long)2L);
		queue_to_fill = ISVREF(Current_task_queue_vector,
			IFIX(priority));
		queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
		if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		    head = ISVREF(queue_to_empty,(SI_Long)0L);
		    tail = ISVREF(queue_to_empty,(SI_Long)1L);
		    SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		    SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		    if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
			SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
			SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
			SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
			SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		    }
		    else {
			old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
			SVREF(old_tail,FIX((SI_Long)0L)) = head;
			SVREF(head,FIX((SI_Long)1L)) = old_tail;
			SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
			SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		    }
		}
		reclaim_future_task_queue_holder(queue_holder);
		if (FIXNUM_LT(priority,Priority_of_next_task))
		    Priority_of_next_task = priority;
		svref_arg_1 = Future_g2_time_tasks;
		SVREF(svref_arg_1,FIX((SI_Long)0L)) = next_queue_holder;
		future_g2_time_tasks_qm = ISVREF(Future_g2_time_tasks,
			(SI_Long)0L);
		if (future_g2_time_tasks_qm)
		    next_g2_task_time = 
			    DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
			    (SI_Long)1L),(SI_Long)0L);
	    }
	    else {
		queue_holder = ISVREF(Future_real_time_tasks,(SI_Long)0L);
		next_queue_holder = queue_holder ? ISVREF(queue_holder,
			(SI_Long)0L) : Qnil;
		priority = ISVREF(queue_holder,(SI_Long)2L);
		queue_to_fill = ISVREF(Current_task_queue_vector,
			IFIX(priority));
		queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
		if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		    head = ISVREF(queue_to_empty,(SI_Long)0L);
		    tail = ISVREF(queue_to_empty,(SI_Long)1L);
		    SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		    SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		    if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
			SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
			SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
			SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
			SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		    }
		    else {
			old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
			SVREF(old_tail,FIX((SI_Long)0L)) = head;
			SVREF(head,FIX((SI_Long)1L)) = old_tail;
			SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
			SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		    }
		}
		reclaim_future_task_queue_holder(queue_holder);
		if (FIXNUM_LT(priority,Priority_of_next_task))
		    Priority_of_next_task = priority;
		svref_arg_1 = Future_real_time_tasks;
		SVREF(svref_arg_1,FIX((SI_Long)0L)) = next_queue_holder;
		future_real_time_tasks_qm = ISVREF(Future_real_time_tasks,
			(SI_Long)0L);
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
	    next_future_task = ISVREF(future_queue,(SI_Long)0L);
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
	    queue_holder = ISVREF(future_queue,(SI_Long)0L);
	    next_queue_holder = queue_holder ? ISVREF(queue_holder,
		    (SI_Long)0L) : Qnil;
	    priority = ISVREF(queue_holder,(SI_Long)2L);
	    queue_to_fill = ISVREF(Current_task_queue_vector,IFIX(priority));
	    queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
	    if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		head = ISVREF(queue_to_empty,(SI_Long)0L);
		tail = ISVREF(queue_to_empty,(SI_Long)1L);
		SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
		    SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
		else {
		    old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
		    SVREF(old_tail,FIX((SI_Long)0L)) = head;
		    SVREF(head,FIX((SI_Long)1L)) = old_tail;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
	    }
	    reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,Priority_of_next_task))
		Priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_4;
	  end_loop_4:;
	    future_queue = Future_g2_time_tasks;
	    latest_dequeue_time = g2_time;
	    next_future_task = Nil;
	  next_loop_5:
	    next_future_task = ISVREF(future_queue,(SI_Long)0L);
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
	    queue_holder = ISVREF(future_queue,(SI_Long)0L);
	    next_queue_holder = queue_holder ? ISVREF(queue_holder,
		    (SI_Long)0L) : Qnil;
	    priority = ISVREF(queue_holder,(SI_Long)2L);
	    queue_to_fill = ISVREF(Current_task_queue_vector,IFIX(priority));
	    queue_to_empty = ISVREF(queue_holder,(SI_Long)3L);
	    if ( !EQ(ISVREF(queue_to_empty,(SI_Long)0L),queue_to_empty)) {
		head = ISVREF(queue_to_empty,(SI_Long)0L);
		tail = ISVREF(queue_to_empty,(SI_Long)1L);
		SVREF(queue_to_empty,FIX((SI_Long)0L)) = queue_to_empty;
		SVREF(queue_to_empty,FIX((SI_Long)1L)) = queue_to_empty;
		if (EQ(ISVREF(queue_to_fill,(SI_Long)0L),queue_to_fill)) {
		    SVREF(queue_to_fill,FIX((SI_Long)0L)) = head;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(head,FIX((SI_Long)1L)) = queue_to_fill;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
		else {
		    old_tail = ISVREF(queue_to_fill,(SI_Long)1L);
		    SVREF(old_tail,FIX((SI_Long)0L)) = head;
		    SVREF(head,FIX((SI_Long)1L)) = old_tail;
		    SVREF(queue_to_fill,FIX((SI_Long)1L)) = tail;
		    SVREF(tail,FIX((SI_Long)0L)) = queue_to_fill;
		}
	    }
	    reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,Priority_of_next_task))
		Priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
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
    Object current_task_queue, deferred_task_queue, queue, next_queue_element;
    Object schedule_task, queue_element, old_next_element;
    Object old_previous_element, old_tail;
    SI_Long priority;

    x_note_fn_call(44,20);
    priority = IFIX(Highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(Current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(Deferred_task_queue_vector,priority);
    if ( !EQ(ISVREF(current_task_queue,(SI_Long)0L),current_task_queue)) {
	queue = current_task_queue;
	next_queue_element = Nil;
	schedule_task = Nil;
	next_queue_element = ISVREF(queue,(SI_Long)0L);
      next_loop_1:
	if (EQ(next_queue_element,queue))
	    goto end_loop_1;
	schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
	next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
	if (ISVREF(schedule_task,(SI_Long)3L)) {
	    queue_element = ISVREF(schedule_task,(SI_Long)6L);
	    old_next_element = ISVREF(queue_element,(SI_Long)0L);
	    old_previous_element = ISVREF(queue_element,(SI_Long)1L);
	    SVREF(old_next_element,FIX((SI_Long)1L)) = old_previous_element;
	    SVREF(old_previous_element,FIX((SI_Long)0L)) = old_next_element;
	    old_tail = ISVREF(deferred_task_queue,(SI_Long)1L);
	    SVREF(queue_element,FIX((SI_Long)0L)) = deferred_task_queue;
	    SVREF(queue_element,FIX((SI_Long)1L)) = old_tail;
	    SVREF(old_tail,FIX((SI_Long)0L)) = queue_element;
	    SVREF(deferred_task_queue,FIX((SI_Long)1L)) = queue_element;
	}
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
    Object current_task_queue, deferred_task_queue, head, tail, old_tail;
    SI_Long priority;

    x_note_fn_call(44,21);
    priority = IFIX(Highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(Current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(Deferred_task_queue_vector,priority);
    if ( !EQ(ISVREF(deferred_task_queue,(SI_Long)0L),deferred_task_queue)) {
	if ( !EQ(ISVREF(deferred_task_queue,(SI_Long)0L),
		    deferred_task_queue)) {
	    head = ISVREF(deferred_task_queue,(SI_Long)0L);
	    tail = ISVREF(deferred_task_queue,(SI_Long)1L);
	    SVREF(deferred_task_queue,FIX((SI_Long)0L)) = deferred_task_queue;
	    SVREF(deferred_task_queue,FIX((SI_Long)1L)) = deferred_task_queue;
	    if (EQ(ISVREF(current_task_queue,(SI_Long)0L),
			current_task_queue)) {
		SVREF(current_task_queue,FIX((SI_Long)0L)) = head;
		SVREF(current_task_queue,FIX((SI_Long)1L)) = tail;
		SVREF(head,FIX((SI_Long)1L)) = current_task_queue;
		SVREF(tail,FIX((SI_Long)0L)) = current_task_queue;
	    }
	    else {
		old_tail = ISVREF(current_task_queue,(SI_Long)1L);
		SVREF(old_tail,FIX((SI_Long)0L)) = head;
		SVREF(head,FIX((SI_Long)1L)) = old_tail;
		SVREF(current_task_queue,FIX((SI_Long)1L)) = tail;
		SVREF(tail,FIX((SI_Long)0L)) = current_task_queue;
	    }
	}
	if (priority < IFIX(Priority_of_next_task))
	    Priority_of_next_task = FIX(priority);
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

Object Scheduler_has_been_initialized_p = UNBOUND;

/* INITIALIZE-SCHEDULER */
Object initialize_scheduler()
{
    Object number_of_priorities, new_vector, temp;
    Object def_structure_future_task_queue_holder_variable, new_holder;
    Object new_queue;
    SI_Long index_1;

    x_note_fn_call(44,22);
    Immediate_task_queue = make_empty_constant_queue();
    number_of_priorities = FIXNUM_ADD1(FIXNUM_MINUS(Lowest_system_priority,
	    Highest_system_priority));
    new_vector = make_array(1,number_of_priorities);
    index_1 = IFIX(Highest_system_priority);
  next_loop:
    if (index_1 > IFIX(Lowest_system_priority))
	goto end_loop;
    temp = make_empty_constant_queue();
    ISVREF(new_vector,index_1) = temp;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    Current_task_queue_vector = new_vector;
    Priority_of_next_task = Lower_than_any_priority;
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
    Deferred_task_queue_vector = new_vector;
    def_structure_future_task_queue_holder_variable = 
	    Chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	Chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    new_holder = def_structure_future_task_queue_holder_variable;
    new_queue = make_empty_constant_queue();
    SVREF(new_queue,FIX((SI_Long)2L)) = Future_task_queue_marker;
    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
    temp = ISVREF(new_holder,(SI_Long)1L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,0.0);
    ISVREF(new_holder,(SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
    Future_real_time_tasks = new_holder;
    def_structure_future_task_queue_holder_variable = 
	    Chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	Chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    new_holder = def_structure_future_task_queue_holder_variable;
    new_queue = make_empty_constant_queue();
    SVREF(new_queue,FIX((SI_Long)2L)) = Future_task_queue_marker;
    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
    temp = ISVREF(new_holder,(SI_Long)1L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,0.0);
    ISVREF(new_holder,(SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
    Future_g2_time_tasks = new_holder;
    Scheduler_has_been_initialized_p = T;
    return VALUES_1(Nil);
}

/* CANCEL-G2-RUNNING-TASKS */
Object cancel_g2_running_tasks()
{
    x_note_fn_call(44,23);
    error((SI_Long)1L,
	    "Cancel-g2-running-tasks not implementented yet.  -jra 2/20/94");
    return VALUES_1(Nil);
}

/* CANCEL-AND-RECLAIM-SCHEDULED-QUEUE-ELEMENT-1 */
Object cancel_and_reclaim_scheduled_queue_element_1(schedule_task)
    Object schedule_task;
{
    Object queue_element, next_queue_element, gensymed_symbol;
    Object gensymed_symbol_1, svref_new_value;
    char temp;

    x_note_fn_call(44,24);
    queue_element = ISVREF(schedule_task,(SI_Long)6L);
    if (queue_element) {
	SVREF(schedule_task,FIX((SI_Long)6L)) = Nil;
	next_queue_element = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol_1 = ISVREF(queue_element,(SI_Long)1L);
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = gensymed_symbol;
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	inline_note_reclaim_cons(queue_element,Nil);
	svref_new_value = Chain_of_available_queue_elements;
	SVREF(queue_element,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_queue_elements = queue_element;
	if (EQ(ISVREF(next_queue_element,(SI_Long)2L),
		Future_task_queue_marker)) {
	    gensymed_symbol = ISVREF(next_queue_element,(SI_Long)0L);
	    temp =  !( !EQ(gensymed_symbol,next_queue_element) ? 
		    TRUEP(ISVREF(gensymed_symbol,(SI_Long)2L)) : TRUEP(Nil));
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    delete_future_task_queue_for_task(schedule_task);
    }
    return VALUES_1(Nil);
}

/* FUTURE-TASK-SCHEDULE-2 */
Object future_task_schedule_2(schedule_task)
    Object schedule_task;
{
    Object g2_task_qm, millisecond_minimum_scheduling_interval_qm;
    Object minimum_in_milliseconds, aref_arg_1, future_task_qm;
    Object current_task_qm, priority, queue, gensymed_symbol;
    Object def_structure_queue_element_variable, gensymed_symbol_1;
    double new_task_time, float_minimum_scheduling_interval, time_1;
    double minimum_float, floored_tick_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,25);
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
		aref_arg_1 = ISVREF(schedule_task,(SI_Long)1L);
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,new_task_time);
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
	gensymed_symbol = ISVREF(queue,(SI_Long)1L);
	def_structure_queue_element_variable = 
		Chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    Chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    make_permanent_queue_element_structure_internal();
	inline_note_allocate_cons(def_structure_queue_element_variable,Nil);
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)0L)) = queue;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)1L)) = 
		gensymed_symbol;
	SVREF(def_structure_queue_element_variable,FIX((SI_Long)2L)) = 
		schedule_task;
	gensymed_symbol_1 = def_structure_queue_element_variable;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_1;
	SVREF(queue,FIX((SI_Long)1L)) = gensymed_symbol_1;
	SVREF(schedule_task,FIX((SI_Long)6L)) = gensymed_symbol_1;
	if (current_task_qm && FIXNUM_LT(priority,Priority_of_next_task))
	    Priority_of_next_task = priority;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DEQUEUE-NEXT-TASK */
Object dequeue_next_task()
{
    Object current_task_qm, gensymed_symbol, gensymed_symbol_1, temp;
    Object gensymed_symbol_2, gensymed_symbol_3, svref_new_value;
    SI_Long priority;

    x_note_fn_call(44,26);
    priority = IFIX(Priority_of_next_task);
    current_task_qm = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    gensymed_symbol = ISVREF(Current_task_queue_vector,priority);
    gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)0L);
    if (EQ(gensymed_symbol_1,gensymed_symbol)) {
	temp = Nil;
	current_task_qm = temp;
    }
    else {
	gensymed_symbol_2 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	gensymed_symbol_3 = ISVREF(gensymed_symbol_1,(SI_Long)0L);
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = gensymed_symbol_3;
	SVREF(gensymed_symbol_3,FIX((SI_Long)1L)) = gensymed_symbol;
	inline_note_reclaim_cons(gensymed_symbol_1,Nil);
	svref_new_value = Chain_of_available_queue_elements;
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_queue_elements = gensymed_symbol_1;
	temp = gensymed_symbol_2;
	current_task_qm = temp;
    }
    if (current_task_qm) {
	Priority_of_next_task = FIX(priority);
	Priority_of_current_task = FIX(priority);
	SVREF(current_task_qm,FIX((SI_Long)6L)) = Nil;
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

static Object Qab;                 /* ab */

/* DEQUEUE-AND-EXECUTE-NEXT-TASK */
Object dequeue_and_execute_next_task()
{
    Object priority_to_use, local_immediate_queue, immediate_task_qm;
    Object gensymed_symbol, temp, gensymed_symbol_1, gensymed_symbol_2, temp_1;
    Object reclaim_task_qm, function, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, svref_new_value, amf_result;
    Object incff_1_arg, new_float, current_time, old_structure_being_reclaimed;
    Object current_task, task_function_name;
    char temp_2;
    double aref_new_value;

    x_note_fn_call(44,27);
    if (Current_schedule_task) {
	if (ISVREF(Current_schedule_task,(SI_Long)2L))
	    reclaim_schedule_task_1(Current_schedule_task);
	Current_schedule_task = Nil;
    }
    priority_to_use = FIXNUMP(Priority_of_current_task) && 
	    FIXNUM_GE(Priority_of_current_task,Highest_system_priority) && 
	    FIXNUM_LE(Priority_of_current_task,Lowest_system_priority) ? 
	    Priority_of_current_task : Highest_system_priority;
    local_immediate_queue = Immediate_task_queue;
    immediate_task_qm = Nil;
  next_loop:
    gensymed_symbol = ISVREF(local_immediate_queue,(SI_Long)0L);
    if (EQ(gensymed_symbol,local_immediate_queue)) {
	temp = Nil;
	immediate_task_qm = temp;
    }
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_2 = ISVREF(gensymed_symbol,(SI_Long)0L);
	SVREF(local_immediate_queue,FIX((SI_Long)0L)) = gensymed_symbol_2;
	SVREF(gensymed_symbol_2,FIX((SI_Long)1L)) = local_immediate_queue;
	inline_note_reclaim_cons(gensymed_symbol,Nil);
	temp_1 = Chain_of_available_queue_elements;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
	Chain_of_available_queue_elements = gensymed_symbol;
	temp = gensymed_symbol_1;
	immediate_task_qm = temp;
    }
    if ( !TRUEP(immediate_task_qm))
	goto end_loop;
    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
    Priority_of_current_task = priority_to_use;
    Current_schedule_task = immediate_task_qm;
    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(immediate_task_qm);
    function = ISVREF(immediate_task_qm,(SI_Long)8L);
    temp = ISVREF(immediate_task_qm,(SI_Long)10L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
	    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
	    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)14L);
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
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp_1 = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp_1;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp_1 = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp_1;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp_1 = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp_1;
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
	old_structure_being_reclaimed = Structure_being_reclaimed;
	Structure_being_reclaimed = immediate_task_qm;
	reclaim_schedule_task_args(ISVREF(immediate_task_qm,(SI_Long)9L));
	SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed;
	temp_1 = Chain_of_available_schedule_tasks;
	SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	Chain_of_available_schedule_tasks = immediate_task_qm;
    }
    goto next_loop;
  end_loop:;
    Priority_of_current_task = Higher_than_any_priority;
    Current_schedule_task = Nil;
    if (Time_to_check_network_events) {
	temp_2 = TRUEP(g2_event_ready_p());
	if (temp_2);
	else {
	    Time_to_check_network_events = Nil;
	    temp_2 = TRUEP(Time_to_check_network_events);
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	Time_to_check_network_events = Nil;
	get_pending_network_events();
    }
    if (EQ(Current_system_name,Qab))
	mqtt_poll_watcher();
    dequeue_next_task();
    if ( !TRUEP(Current_schedule_task) && (get_pending_network_events() || 
	    tick_the_clock(Nil)))
	dequeue_next_task();
    if (Current_schedule_task) {
	current_task = Current_schedule_task;
	task_function_name = ISVREF(current_task,(SI_Long)7L);
	execute_task_and_reschedule(current_task);
	Current_schedule_task = Nil;
	local_immediate_queue = Immediate_task_queue;
	immediate_task_qm = Nil;
      next_loop_1:
	gensymed_symbol = ISVREF(local_immediate_queue,(SI_Long)0L);
	if (EQ(gensymed_symbol,local_immediate_queue)) {
	    temp = Nil;
	    immediate_task_qm = temp;
	}
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    gensymed_symbol_2 = ISVREF(gensymed_symbol,(SI_Long)0L);
	    SVREF(local_immediate_queue,FIX((SI_Long)0L)) = gensymed_symbol_2;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)1L)) = local_immediate_queue;
	    inline_note_reclaim_cons(gensymed_symbol,Nil);
	    temp_1 = Chain_of_available_queue_elements;
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
	    Chain_of_available_queue_elements = gensymed_symbol;
	    temp = gensymed_symbol_1;
	    immediate_task_qm = temp;
	}
	if ( !TRUEP(immediate_task_qm))
	    goto end_loop_1;
	SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	Current_schedule_task = immediate_task_qm;
	reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
	if (Profiling_enabled_qm)
	    posit_profiling_structure(immediate_task_qm);
	function = ISVREF(immediate_task_qm,(SI_Long)8L);
	temp = ISVREF(immediate_task_qm,(SI_Long)10L);
	if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		FIX((SI_Long)127L))))
	    switch (INTEGER_TO_CHAR(temp)) {
	      case 0:
		inline_funcall_0(function);
		break;
	      case 1:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		break;
	      case 2:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
		break;
	      case 3:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
		inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3);
		break;
	      case 4:
		gensymed_symbol = function;
		gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
		gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)14L);
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
		svref_new_value = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qab_gensym);
		temp_1 = Available_gensym_conses;
		M_CDR(amf_available_array_cons_qm) = temp_1;
		Available_gensym_conses = amf_available_array_cons_qm;
		amf_result = amf_array;
	    }
	    else {
		temp_1 = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
		Created_simple_float_array_pool_arrays = temp_1;
		incff_1_arg = 
			bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		temp_1 = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
			incff_1_arg);
		Simple_float_array_pool_memory_usage = temp_1;
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
	    old_structure_being_reclaimed = Structure_being_reclaimed;
	    Structure_being_reclaimed = immediate_task_qm;
	    reclaim_schedule_task_args(ISVREF(immediate_task_qm,(SI_Long)9L));
	    SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	    Structure_being_reclaimed = old_structure_being_reclaimed;
	    temp_1 = Chain_of_available_schedule_tasks;
	    SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
	    Chain_of_available_schedule_tasks = immediate_task_qm;
	}
	goto next_loop_1;
      end_loop_1:;
	Priority_of_current_task = Higher_than_any_priority;
	Current_schedule_task = Nil;
	Priority_of_current_task = Higher_than_any_priority;
	temp = task_function_name;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXECUTE-TASK-AND-RESCHEDULE */
Object execute_task_and_reschedule(current_task)
    Object current_task;
{
    Object reclaim_task_qm, function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, svref_new_value;
    Object amf_result, incff_1_arg, new_float, current_time, g2_running_qm;
    Object old_structure_being_reclaimed;
    double aref_new_value, interval, arg, arg_1, current_time_1, old_task_time;
    double new_time;

    x_note_fn_call(44,28);
    reclaim_task_qm = ISVREF(current_task,(SI_Long)2L);
    if (Profiling_enabled_qm)
	posit_profiling_structure(current_task);
    function = ISVREF(current_task,(SI_Long)8L);
    temp = ISVREF(current_task,(SI_Long)10L);
    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
	    FIX((SI_Long)127L))))
	switch (INTEGER_TO_CHAR(temp)) {
	  case 0:
	    inline_funcall_0(function);
	    break;
	  case 1:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)11L);
	    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    break;
	  case 2:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)12L);
	    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2);
	    break;
	  case 3:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)12L);
	    gensymed_symbol_3 = ISVREF(current_task,(SI_Long)13L);
	    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	    break;
	  case 4:
	    gensymed_symbol = function;
	    gensymed_symbol_1 = ISVREF(current_task,(SI_Long)11L);
	    gensymed_symbol_2 = ISVREF(current_task,(SI_Long)12L);
	    gensymed_symbol_3 = ISVREF(current_task,(SI_Long)13L);
	    gensymed_symbol_4 = ISVREF(current_task,(SI_Long)14L);
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
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp_1 = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp_1;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp_1 = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp_1;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp_1 = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp_1;
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
	old_structure_being_reclaimed = Structure_being_reclaimed;
	Structure_being_reclaimed = current_task;
	reclaim_schedule_task_args(ISVREF(current_task,(SI_Long)9L));
	SVREF(current_task,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed;
	temp_1 = Chain_of_available_schedule_tasks;
	SVREF(current_task,FIX((SI_Long)0L)) = temp_1;
	Chain_of_available_schedule_tasks = current_task;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TASKS-ENQUEUED-FOR-CURRENT-EXECUTION? */
Object tasks_enqueued_for_current_execution_qm()
{
    Object temp, ab_loop_it_, constant_queue;
    SI_Long priority;

    x_note_fn_call(44,29);
    temp =  !EQ(ISVREF(Immediate_task_queue,(SI_Long)0L),
	    Immediate_task_queue) ? T : Nil;
    if (temp);
    else {
	priority = IFIX(Highest_system_priority);
	ab_loop_it_ = Nil;
      next_loop:
	if (priority > IFIX(Lowest_system_priority))
	    goto end_loop;
	constant_queue = ISVREF(Current_task_queue_vector,priority);
	ab_loop_it_ =  !EQ(ISVREF(constant_queue,(SI_Long)0L),
		constant_queue) ? T : Nil;
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

    x_note_fn_call(44,30);
    priority = IFIX(Highest_system_priority);
    ab_loop_it_ = Nil;
  next_loop:
    if (priority > IFIX(Lowest_system_priority))
	goto end_loop;
    constant_queue = ISVREF(Deferred_task_queue_vector,priority);
    ab_loop_it_ =  !EQ(ISVREF(constant_queue,(SI_Long)0L),constant_queue) ?
	     T : Nil;
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
    Object gensymed_symbol, immediate_task_qm, temp, current_task_qm;
    Object gensymed_symbol_1;
    SI_Long priority_1, ab_loop_bind_;

    x_note_fn_call(44,31);
    gensymed_symbol = ISVREF(Immediate_task_queue,(SI_Long)0L);
    immediate_task_qm =  !EQ(gensymed_symbol,Immediate_task_queue) ? 
	    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
    if (immediate_task_qm)
	temp = EQ(ISVREF(immediate_task_qm,(SI_Long)7L),function_name) ? 
		immediate_task_qm : Nil;
    else {
	priority_1 = IFIX(Priority_of_next_task);
	ab_loop_bind_ = IFIX(priority);
	current_task_qm = Nil;
      next_loop:
	if (priority_1 > ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = ISVREF(Current_task_queue_vector,priority_1);
	gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)0L);
	current_task_qm =  !EQ(gensymed_symbol_1,gensymed_symbol) ? 
		ISVREF(gensymed_symbol_1,(SI_Long)2L) : Nil;
	if (current_task_qm) {
	    temp = EQ(ISVREF(current_task_qm,(SI_Long)7L),function_name) 
		    && IFIX(ISVREF(current_task_qm,(SI_Long)4L)) == 
		    priority_1 ? current_task_qm : Nil;
	    goto end_1;
	}
	priority_1 = priority_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* EXECUTE-TASK-OUT-OF-ORDER-1 */
Object execute_task_out_of_order_1(schedule_task)
    Object schedule_task;
{
    Object temp, priority_of_current_task, current_schedule_task;
    Object reclaim_task_qm, function, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_1, svref_new_value;
    Object amf_result, incff_1_arg, new_float, current_time;
    Object old_structure_being_reclaimed, local_immediate_queue;
    Object immediate_task_qm;
    double aref_new_value;
    Declare_special(2);

    x_note_fn_call(44,32);
    if (schedule_task) {
	if (ISVREF(schedule_task,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	if (EQ(schedule_task,Current_schedule_task))
	    Current_schedule_task = Nil;
	temp = ISVREF(schedule_task,(SI_Long)4L);
	priority_of_current_task = FIXNUM_MAX(temp,Highest_system_priority);
	current_schedule_task = schedule_task;
	reclaim_task_qm = ISVREF(schedule_task,(SI_Long)2L);
	PUSH_SPECIAL(Current_schedule_task,current_schedule_task,1);
	  PUSH_SPECIAL(Priority_of_current_task,priority_of_current_task,0);
	    if (Profiling_enabled_qm)
		posit_profiling_structure(schedule_task);
	    function = ISVREF(schedule_task,(SI_Long)8L);
	    temp = ISVREF(schedule_task,(SI_Long)10L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    inline_funcall_0(function);
		    break;
		  case 1:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)11L);
		    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		    break;
		  case 2:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)12L);
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    break;
		  case 3:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)12L);
		    gensymed_symbol_3 = ISVREF(schedule_task,(SI_Long)13L);
		    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3);
		    break;
		  case 4:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(schedule_task,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(schedule_task,(SI_Long)12L);
		    gensymed_symbol_3 = ISVREF(schedule_task,(SI_Long)13L);
		    gensymed_symbol_4 = ISVREF(schedule_task,(SI_Long)14L);
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
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qab_gensym);
		    temp_1 = Available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp_1;
		    Available_gensym_conses = amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp_1 = 
			    FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
		    Created_simple_float_array_pool_arrays = temp_1;
		    incff_1_arg = 
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp_1 = 
			    FIXNUM_ADD(Simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    Simple_float_array_pool_memory_usage = temp_1;
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
		old_structure_being_reclaimed = Structure_being_reclaimed;
		Structure_being_reclaimed = schedule_task;
		reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
		SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
		Structure_being_reclaimed = old_structure_being_reclaimed;
		temp_1 = Chain_of_available_schedule_tasks;
		SVREF(schedule_task,FIX((SI_Long)0L)) = temp_1;
		Chain_of_available_schedule_tasks = schedule_task;
	    }
	    local_immediate_queue = Immediate_task_queue;
	    immediate_task_qm = Nil;
	  next_loop:
	    gensymed_symbol = ISVREF(local_immediate_queue,(SI_Long)0L);
	    if (EQ(gensymed_symbol,local_immediate_queue)) {
		temp = Nil;
		immediate_task_qm = temp;
	    }
	    else {
		gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		gensymed_symbol_2 = ISVREF(gensymed_symbol,(SI_Long)0L);
		SVREF(local_immediate_queue,FIX((SI_Long)0L)) = 
			gensymed_symbol_2;
		SVREF(gensymed_symbol_2,FIX((SI_Long)1L)) = 
			local_immediate_queue;
		inline_note_reclaim_cons(gensymed_symbol,Nil);
		temp_1 = Chain_of_available_queue_elements;
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
		Chain_of_available_queue_elements = gensymed_symbol;
		temp = gensymed_symbol_1;
		immediate_task_qm = temp;
	    }
	    if ( !TRUEP(immediate_task_qm))
		goto end_loop;
	    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	    Priority_of_current_task = Highest_system_priority;
	    Current_schedule_task = immediate_task_qm;
	    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
	    if (Profiling_enabled_qm)
		posit_profiling_structure(immediate_task_qm);
	    function = ISVREF(immediate_task_qm,(SI_Long)8L);
	    temp = ISVREF(immediate_task_qm,(SI_Long)10L);
	    if (! !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && FIXNUM_LE(temp,
		    FIX((SI_Long)127L))))
		switch (INTEGER_TO_CHAR(temp)) {
		  case 0:
		    inline_funcall_0(function);
		    break;
		  case 1:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		    break;
		  case 2:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		    inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2);
		    break;
		  case 3:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
			    gensymed_symbol_2,gensymed_symbol_3);
		    break;
		  case 4:
		    gensymed_symbol = function;
		    gensymed_symbol_1 = ISVREF(immediate_task_qm,(SI_Long)11L);
		    gensymed_symbol_2 = ISVREF(immediate_task_qm,(SI_Long)12L);
		    gensymed_symbol_3 = ISVREF(immediate_task_qm,(SI_Long)13L);
		    gensymed_symbol_4 = ISVREF(immediate_task_qm,(SI_Long)14L);
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
		    svref_new_value = M_CDR(amf_available_array_cons_qm);
		    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
		    inline_note_reclaim_cons(amf_available_array_cons_qm,
			    Qab_gensym);
		    temp_1 = Available_gensym_conses;
		    M_CDR(amf_available_array_cons_qm) = temp_1;
		    Available_gensym_conses = amf_available_array_cons_qm;
		    amf_result = amf_array;
		}
		else {
		    temp_1 = 
			    FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
		    Created_simple_float_array_pool_arrays = temp_1;
		    incff_1_arg = 
			    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
		    temp_1 = 
			    FIXNUM_ADD(Simple_float_array_pool_memory_usage,
			    incff_1_arg);
		    Simple_float_array_pool_memory_usage = temp_1;
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
		old_structure_being_reclaimed = Structure_being_reclaimed;
		Structure_being_reclaimed = immediate_task_qm;
		reclaim_schedule_task_args(ISVREF(immediate_task_qm,
			(SI_Long)9L));
		SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
		Structure_being_reclaimed = old_structure_being_reclaimed;
		temp_1 = Chain_of_available_schedule_tasks;
		SVREF(immediate_task_qm,FIX((SI_Long)0L)) = temp_1;
		Chain_of_available_schedule_tasks = immediate_task_qm;
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
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, queue;
    Object next_queue_element, schedule_task, old_structure_being_reclaimed;
    Object queue_1, next_queue_holder, queue_holder;
    SI_Long priority;
    Declare_special(1);

    x_note_fn_call(44,33);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
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
      queue = Immediate_task_queue;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = ISVREF(queue,(SI_Long)0L);
    next_loop:
      if (EQ(next_queue_element,queue))
	  goto end_loop;
      schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
      next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
      if (ISVREF(schedule_task,(SI_Long)3L)) {
	  if (ISVREF(schedule_task,(SI_Long)6L))
	      cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      old_structure_being_reclaimed = Structure_being_reclaimed;
	      Structure_being_reclaimed = schedule_task;
	      reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	      SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      Structure_being_reclaimed = old_structure_being_reclaimed;
	      temp = Chain_of_available_schedule_tasks;
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      Chain_of_available_schedule_tasks = schedule_task;
	  }
      }
      goto next_loop;
    end_loop:;
      priority = IFIX(Highest_system_priority);
      queue_1 = Nil;
    next_loop_1:
      if (priority > IFIX(Lowest_system_priority))
	  goto end_loop_1;
      queue_1 = ISVREF(Current_task_queue_vector,priority);
      queue = queue_1;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = ISVREF(queue,(SI_Long)0L);
    next_loop_2:
      if (EQ(next_queue_element,queue))
	  goto end_loop_2;
      schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
      next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
      if (ISVREF(schedule_task,(SI_Long)3L)) {
	  if (ISVREF(schedule_task,(SI_Long)6L))
	      cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      old_structure_being_reclaimed = Structure_being_reclaimed;
	      Structure_being_reclaimed = schedule_task;
	      reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	      SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      Structure_being_reclaimed = old_structure_being_reclaimed;
	      temp = Chain_of_available_schedule_tasks;
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      Chain_of_available_schedule_tasks = schedule_task;
	  }
      }
      goto next_loop_2;
    end_loop_2:;
      priority = priority + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:;
      priority = IFIX(Highest_system_priority);
      queue_1 = Nil;
    next_loop_3:
      if (priority > IFIX(Lowest_system_priority))
	  goto end_loop_3;
      queue_1 = ISVREF(Deferred_task_queue_vector,priority);
      queue = queue_1;
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = ISVREF(queue,(SI_Long)0L);
    next_loop_4:
      if (EQ(next_queue_element,queue))
	  goto end_loop_4;
      schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
      next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
      if (ISVREF(schedule_task,(SI_Long)6L))
	  cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  old_structure_being_reclaimed = Structure_being_reclaimed;
	  Structure_being_reclaimed = schedule_task;
	  reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	  SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  Structure_being_reclaimed = old_structure_being_reclaimed;
	  temp = Chain_of_available_schedule_tasks;
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  Chain_of_available_schedule_tasks = schedule_task;
      }
      goto next_loop_4;
    end_loop_4:;
      priority = priority + (SI_Long)1L;
      goto next_loop_3;
    end_loop_3:;
      next_queue_holder = ISVREF(Future_g2_time_tasks,(SI_Long)0L);
      queue_holder = Nil;
    next_loop_5:
      if ( !TRUEP(next_queue_holder))
	  goto end_loop_5;
      queue_holder = next_queue_holder;
      next_queue_holder = ISVREF(next_queue_holder,(SI_Long)0L);
      queue = ISVREF(queue_holder,(SI_Long)3L);
      next_queue_element = Nil;
      schedule_task = Nil;
      next_queue_element = ISVREF(queue,(SI_Long)0L);
    next_loop_6:
      if (EQ(next_queue_element,queue))
	  goto end_loop_6;
      schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
      next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
      if (ISVREF(schedule_task,(SI_Long)6L))
	  cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  old_structure_being_reclaimed = Structure_being_reclaimed;
	  Structure_being_reclaimed = schedule_task;
	  reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	  SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  Structure_being_reclaimed = old_structure_being_reclaimed;
	  temp = Chain_of_available_schedule_tasks;
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  Chain_of_available_schedule_tasks = schedule_task;
      }
      goto next_loop_6;
    end_loop_6:;
      goto next_loop_5;
    end_loop_5:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* ADJUST-TASK-TIMES-AFTER-CLOCK-DISCONTINUITY */
Object adjust_task_times_after_clock_discontinuity(managed_float_offset,
	    future_task_queue_set)
    Object managed_float_offset, future_task_queue_set;
{
    Object next_queue_holder, task_queue_holder, holder_time, queue, queue_1;
    Object next_queue_element, schedule_task, aref_arg_1;
    double offset, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,34);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	offset = DFLOAT_ISAREF_1(managed_float_offset,(SI_Long)0L);
	next_queue_holder = ISVREF(future_task_queue_set,(SI_Long)0L);
	task_queue_holder = Nil;
	holder_time = Nil;
	queue = Nil;
      next_loop:
	if ( !TRUEP(next_queue_holder))
	    goto end_loop;
	task_queue_holder = next_queue_holder;
	next_queue_holder = ISVREF(next_queue_holder,(SI_Long)0L);
	holder_time = ISVREF(task_queue_holder,(SI_Long)1L);
	queue = ISVREF(task_queue_holder,(SI_Long)3L);
	aref_new_value = DFLOAT_ISAREF_1(holder_time,(SI_Long)0L) + offset;
	DFLOAT_ISASET_1(holder_time,(SI_Long)0L,aref_new_value);
	queue_1 = queue;
	next_queue_element = Nil;
	schedule_task = Nil;
	next_queue_element = ISVREF(queue_1,(SI_Long)0L);
      next_loop_1:
	if (EQ(next_queue_element,queue_1))
	    goto end_loop_1;
	schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
	next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
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

Object Time_slice_start_time = UNBOUND;

Object Maximum_time_slice_size = UNBOUND;

/* TIME-SLICE-EXPIRED-P */
Object time_slice_expired_p()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, elapsed_time;

    x_note_fn_call(44,35);
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

    x_note_fn_call(44,36);
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

    x_note_fn_call(44,37);
    queue = ISVREF(Current_task_queue_vector,IFIX(priority));
    next_queue_element = Nil;
    task = Nil;
    next_queue_element = ISVREF(queue,(SI_Long)0L);
  next_loop:
    if (EQ(next_queue_element,queue))
	goto end_loop;
    task = ISVREF(next_queue_element,(SI_Long)2L);
    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
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
    x_note_fn_call(44,38);
    tformat(1,string_constant);
    return VALUES_1(Nil);
}

static Object Qab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

/* TYPE-NAME-OF-NAMED-SIMPLE-VECTOR */
Object type_name_of_named_simple_vector(arg)
    Object arg;
{
    Object type, temp;

    x_note_fn_call(44,39);
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
    x_note_fn_call(44,40);
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

    x_note_fn_call(44,41);
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

Object Gensym_time = UNBOUND;

Object Gensym_base_time_as_managed_float = UNBOUND;

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

    x_note_fn_call(44,42);
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	args = ISVREF(schedule_task,(SI_Long)10L);
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
		    (SI_Long)11L));
	    if (IFIX(args) > (SI_Long)1L) {
		twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
			(SI_Long)12L));
		if (IFIX(args) > (SI_Long)2L) {
		    twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
			    (SI_Long)13L));
		    if (IFIX(args) > (SI_Long)3L)
			twrite_debug_computation_instance_or_object(ISVREF(schedule_task,
				(SI_Long)14L));
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

    x_note_fn_call(44,43);
    queue = constant_queue;
    next_queue_element = Nil;
    schedule_task = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    next_queue_element = ISVREF(queue,(SI_Long)0L);
  next_loop:
    if (EQ(next_queue_element,queue))
	goto end_loop;
    schedule_task = ISVREF(next_queue_element,(SI_Long)2L);
    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
    Object ab_loopvar__1, ab_loopvar__2, temp_6, temp_7, next_queue_holder;
    Object queue_holder, temp_8;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, priority;
    double temp_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(44,44);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	gensymed_symbol = make_gensym_list_1(FIX((SI_Long)8L));
	gensymed_symbol_1 = gensymed_symbol;
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	if ( !EQ(ISVREF(Immediate_task_queue,(SI_Long)0L),
		Immediate_task_queue)) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(1,string_constant_9);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(1,string_constant_17);
		      temp_2 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(1,string_constant_9);
		      temp_3 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(1,string_constant_18);
		      temp_4 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_4 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_19);
			  temp_5 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
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
	    if (ISVREF(Future_real_time_tasks,(SI_Long)0L)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_5 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_20);
			  temp_6 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_schedule_task_header();
			  temp_7 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		next_queue_holder = ISVREF(Future_real_time_tasks,(SI_Long)0L);
		queue_holder = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_2:
		if ( !TRUEP(next_queue_holder))
		    goto end_loop_2;
		queue_holder = next_queue_holder;
		next_queue_holder = ISVREF(next_queue_holder,(SI_Long)0L);
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
	    if (ISVREF(Future_g2_time_tasks,(SI_Long)0L)) {
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_9);
			  temp_6 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  tformat(1,string_constant_21);
			  temp_7 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		current_wide_string_list = Qdo_not_use;
		PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			    2);
		      length_1 = 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		      total_length_of_current_wide_string = 
			      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)2L) + 
			      ((UBYTE_16_ISAREF_1(Current_wide_string,
			      length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			      (SI_Long)16L));
		      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			      1);
			current_twriting_output_type = Qwide_string;
			PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				0);
			  twrite_schedule_task_header();
			  temp_8 = copy_out_current_wide_string();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		next_queue_holder = ISVREF(Future_g2_time_tasks,(SI_Long)0L);
		queue_holder = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
	      next_loop_3:
		if ( !TRUEP(next_queue_holder))
		    goto end_loop_3;
		queue_holder = next_queue_holder;
		next_queue_holder = ISVREF(next_queue_holder,(SI_Long)0L);
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

Object Gsi_maximum_idle_interval = UNBOUND;

/* MILLISECONDS-TO-NEXT-SCHEDULER-EVENT */
Object milliseconds_to_next_scheduler_event()
{
    Object temp_1, milliseconds_to_next_task_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp;

    x_note_fn_call(44,45);
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

    x_note_fn_call(44,46);
    milliseconds_to_sleep_qm =  !TRUEP(force_scheduler_event_qm) ? 
	    milliseconds_to_next_scheduler_event() : Nil;
    if (milliseconds_to_sleep_qm)
	ne_set_next_timer_event(IFIX(milliseconds_to_sleep_qm));
    else
	ne_enqueue_scheduler_event();
    return VALUES_1(milliseconds_to_sleep_qm);
}

void schedule_INIT()
{
    Object temp, reclaim_structure_for_schedule_task_1;
    Object reclaim_structure_for_future_task_queue_holder_1;
    Object list_constant_2, AB_package, list_constant_1, Qclocks;
    Object Qmaximum_time_slice_size, Qfixnum_time_interval, Kfuncall;
    Object Qschedule, Qscheduler_has_been_initialized_p, list_constant;
    Object Qfuture_task_queue_marker, Qpriority_of_next_task;
    Object Qpriority_of_current_task, Qcurrent_schedule_task;
    Object Qsystem_has_aborted, Qsystem_has_paused, Qsystem_is_running;
    Object Qfuture_task_queue_holder, Qreclaim_structure;
    Object Qoutstanding_future_task_queue_holder_count;
    Object Qfuture_task_queue_holder_structure_memory_usage, Qutilities2;
    Object Qfuture_task_queue_holder_count;
    Object Qchain_of_available_future_task_queue_holders, string_constant_25;
    Object Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_24;
    Object Qfuture_g2_time_tasks, Qfuture_real_time_tasks;
    Object Qdeferred_task_queue_vector, Qcurrent_task_queue_vector;
    Object Qimmediate_task_queue, Qschedule_task_arg_limit, Qschedule_task;
    Object Qoutstanding_schedule_task_count;
    Object Qschedule_task_structure_memory_usage, Qschedule_task_count;
    Object Qchain_of_available_schedule_tasks, string_constant_23;
    Object string_constant_22, Qunique_structure_type_of_ab_name_qm;
    Object Qschedule_task_arg_offset, Qlower_than_any_priority;
    Object Qhigher_than_any_priority, Qlowest_system_priority;
    Object Qhighest_system_priority, Qhighest_user_priority;
    Object Qhow_many_priorities_qm;

    x_note_fn_call(44,47);
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
    SET_SYMBOL_VALUE(Qschedule_task_arg_offset,FIX((SI_Long)11L));
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
	    STATIC_STRING("43Dy8m83mjy1n83mjy8n8k1l8n0000001n1m83=ey3ky1n8y83-5jy1l83-CTy1m83-DIy1m83-CRy83-CSykzk0k0");
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
    string_constant_23 = STATIC_STRING("1q83mjy8s83-mQy09k9l");
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
	    STATIC_STRING("43Dy8m83hey1m83hey8k1l8k0000001o1m83*gy9k1m83=ey3ky1n8y83-3py01m83My83-AKykok0k0");
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
    string_constant_25 = STATIC_STRING("1q83hey8s83-Upy09k9l");
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
    Qreal_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    Qscheduler_has_been_initialized_p = 
	    STATIC_SYMBOL("SCHEDULER-HAS-BEEN-INITIALIZED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qscheduler_has_been_initialized_p,
	    Scheduler_has_been_initialized_p);
    record_system_variable(Qscheduler_has_been_initialized_p,Qschedule,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qab = STATIC_SYMBOL("AB",AB_package);
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
}
