/* schdle.c
 * Input file:  schedule.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "schdle.h"


Object G2int_the_type_description_of_schedule_task = UNBOUND;

Object G2int_chain_of_available_schedule_tasks = UNBOUND;

Object G2int_schedule_task_count = UNBOUND;

/* RECLAIM-SCHEDULE-TASK-1 */
Object g2int_reclaim_schedule_task_1(schedule_task)
    Object schedule_task;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(33,0);
    inline_note_reclaim_cons(schedule_task,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = schedule_task;
    g2int_reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
    SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_schedule_tasks;
    SVREF(schedule_task,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_schedule_tasks = schedule_task;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SCHEDULE-TASK */
Object g2int_reclaim_structure_for_schedule_task(schedule_task)
    Object schedule_task;
{
    x_note_fn_call(33,1);
    return g2int_reclaim_schedule_task_1(schedule_task);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* MAKE-PERMANENT-SCHEDULE-TASK-STRUCTURE-INTERNAL */
Object g2int_make_permanent_schedule_task_structure_internal()
{
    Object def_structure_schedule_task_variable;
    Object defstruct_g2_schedule_task_variable, the_array, svref_new_value;
    SI_Long schedule_task_count_new_value, gensymed_symbol, gensymed_symbol_1;
    SI_Long i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,2);
    def_structure_schedule_task_variable = Nil;
    schedule_task_count_new_value = IFIX(G2int_schedule_task_count) + 
	    (SI_Long)50L;
    G2int_schedule_task_count = FIX(schedule_task_count_new_value);
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
		g2int_allocate_managed_simple_float_array(FIX((SI_Long)2L));
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)1L)) = 
		svref_new_value;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		svref_new_value;
	G2int_chain_of_available_schedule_tasks = 
		def_structure_schedule_task_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_schedule_task_variable);
}

/* MAKE-SCHEDULE-TASK-1 */
Object g2int_make_schedule_task_1(schedule_task_reclaimable_by_scheduler_p)
    Object schedule_task_reclaimable_by_scheduler_p;
{
    Object def_structure_schedule_task_variable;

    x_note_fn_call(33,3);
    def_structure_schedule_task_variable = 
	    G2int_chain_of_available_schedule_tasks;
    if (def_structure_schedule_task_variable) {
	G2int_chain_of_available_schedule_tasks = 
		ISVREF(def_structure_schedule_task_variable,(SI_Long)0L);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_schedule_task_g2_struct;
    }
    else
	def_structure_schedule_task_variable = 
		g2int_make_permanent_schedule_task_structure_internal();
    inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = 
	    schedule_task_reclaimable_by_scheduler_p;
    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
    return VALUES_1(def_structure_schedule_task_variable);
}

static Object Qg2int_gensym;       /* gensym */

/* RECLAIM-SCHEDULE-TASK-ARGS */
Object g2int_reclaim_schedule_task_args(reclaimers)
    Object reclaimers;
{
    Object f, gensym_pop_store, cons_1, next_cons, temp;
    SI_Long i, svref_arg_2;

    x_note_fn_call(33,4);
    if (reclaimers) {
	f = Nil;
	i = (SI_Long)0L;
      next_loop:
	if (i >= IFIX(G2int_schedule_task_arg_limit))
	    goto end_loop;
	gensym_pop_store = Nil;
	cons_1 = reclaimers;
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qg2int_gensym);
	    temp = G2int_available_gensym_conses;
	    M_CDR(cons_1) = temp;
	    G2int_available_gensym_conses = cons_1;
	}
	else
	    next_cons = Nil;
	reclaimers = next_cons;
	f = gensym_pop_store;
	if (f) {
	    FUNCALL_1(f,ISVREF(G2int_structure_being_reclaimed,i + 
		    IFIX(G2int_schedule_task_arg_offset)));
	    temp = G2int_structure_being_reclaimed;
	    svref_arg_2 = i + IFIX(G2int_schedule_task_arg_offset);
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
Object g2int_print_schedule_task(schedule_task,stream,depth)
    Object schedule_task, stream, depth;
{
    x_note_fn_call(33,5);
    return VALUES_1(schedule_task);
}

/* NOTE-SCHEDULING-TASK-1 */
Object g2int_note_scheduling_task_1(function_name,task)
    Object function_name, task;
{
    x_note_fn_call(33,6);
    return VALUES_1(Nil);
}

Object G2int_immediate_task_queue = UNBOUND;

Object G2int_current_task_queue_vector = UNBOUND;

Object G2int_deferred_task_queue_vector = UNBOUND;

Object G2int_future_real_time_tasks = UNBOUND;

Object G2int_future_g2_time_tasks = UNBOUND;

Object G2int_the_type_description_of_future_task_queue_holder = UNBOUND;

Object G2int_chain_of_available_future_task_queue_holders = UNBOUND;

Object G2int_future_task_queue_holder_count = UNBOUND;

/* RECLAIM-FUTURE-TASK-QUEUE-HOLDER-1-1 */
Object g2int_reclaim_future_task_queue_holder_1_1(future_task_queue_holder)
    Object future_task_queue_holder;
{
    Object svref_new_value;

    x_note_fn_call(33,7);
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    svref_new_value = G2int_chain_of_available_future_task_queue_holders;
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_future_task_queue_holders = 
	    future_task_queue_holder;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FUTURE-TASK-QUEUE-HOLDER */
Object g2int_reclaim_structure_for_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    x_note_fn_call(33,8);
    return g2int_reclaim_future_task_queue_holder_1_1(future_task_queue_holder);
}

/* MAKE-PERMANENT-FUTURE-TASK-QUEUE-HOLDER-STRUCTURE-INTERNAL */
Object g2int_make_permanent_future_task_queue_holder_structure_internal()
{
    Object def_structure_future_task_queue_holder_variable, the_array;
    Object defstruct_g2_future_task_queue_holder_variable, svref_new_value;
    SI_Long future_task_queue_holder_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(33,9);
    def_structure_future_task_queue_holder_variable = Nil;
    future_task_queue_holder_count_new_value = 
	    IFIX(G2int_future_task_queue_holder_count) + (SI_Long)50L;
    G2int_future_task_queue_holder_count = 
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
	svref_new_value = g2int_allocate_managed_float_box();
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)1L)) = svref_new_value;
	if (gensymed_symbol >= (SI_Long)50L)
	    goto end_loop_1;
	svref_new_value = G2int_chain_of_available_future_task_queue_holders;
	SVREF(def_structure_future_task_queue_holder_variable,
		FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_future_task_queue_holders = 
		def_structure_future_task_queue_holder_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_future_task_queue_holder_variable);
}

/* MAKE-FUTURE-TASK-QUEUE-HOLDER-1-1 */
Object g2int_make_future_task_queue_holder_1_1()
{
    Object def_structure_future_task_queue_holder_variable;

    x_note_fn_call(33,10);
    def_structure_future_task_queue_holder_variable = 
	    G2int_chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	G2int_chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		g2int_make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    return VALUES_1(def_structure_future_task_queue_holder_variable);
}

/* RECLAIM-FUTURE-TASK-QUEUE-HOLDER */
Object g2int_reclaim_future_task_queue_holder(future_task_queue_holder)
    Object future_task_queue_holder;
{
    Object svref_new_value;

    x_note_fn_call(33,11);
    g2int_reclaim_constant_queue(ISVREF(future_task_queue_holder,(SI_Long)3L));
    inline_note_reclaim_cons(future_task_queue_holder,Nil);
    svref_new_value = G2int_chain_of_available_future_task_queue_holders;
    SVREF(future_task_queue_holder,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_future_task_queue_holders = 
	    future_task_queue_holder;
    return VALUES_1(Nil);
}

Object G2int_system_is_running = UNBOUND;

Object G2int_system_has_paused = UNBOUND;

Object G2int_system_has_aborted = UNBOUND;

static Object Qg2int_abort;        /* abort */

static Object Qg2int_running;      /* running */

static Object Qg2int_paused;       /* paused */

static Object Qg2int_reset;        /* reset */

/* CURRENT-G2-RUN-STATE */
Object g2int_current_g2_run_state()
{
    x_note_fn_call(33,12);
    if (G2int_system_has_aborted)
	return VALUES_1(Qg2int_abort);
    else if (G2int_system_is_running)
	return VALUES_1(Qg2int_running);
    else if (G2int_system_has_paused)
	return VALUES_1(Qg2int_paused);
    else
	return VALUES_1(Qg2int_reset);
}

Object G2int_current_schedule_task = UNBOUND;

Object G2int_priority_of_current_task = UNBOUND;

Object G2int_priority_of_next_task = UNBOUND;

Object G2int_future_task_queue_marker = UNBOUND;

/* GET-OR-CREATE-FUTURE-TASK-QUEUE-FOR-TASK */
Object g2int_get_or_create_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object priority, g2_running_task_qm, holder_trailer, queue_holder;
    Object holder_priority, insert_new_qm, temp;
    Object def_structure_future_task_queue_holder_variable, new_holder;
    Object new_queue, aref_arg_1, new_holder_1;
    double task_time, holder_task_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(33,13);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	priority = ISVREF(schedule_task,(SI_Long)4L);
	task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	holder_trailer = g2_running_task_qm ? G2int_future_g2_time_tasks : 
		G2int_future_real_time_tasks;
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
			goto end;
		    }
		    else if (FIXNUM_GT(priority,holder_priority))
			insert_new_qm = T;
		}
		else
		    insert_new_qm = T;
		if (insert_new_qm) {
		    def_structure_future_task_queue_holder_variable = 
			    G2int_chain_of_available_future_task_queue_holders;
		    if (def_structure_future_task_queue_holder_variable)
			G2int_chain_of_available_future_task_queue_holders 
				= 
				ISVREF(def_structure_future_task_queue_holder_variable,
				(SI_Long)0L);
		    else
			def_structure_future_task_queue_holder_variable = 
				g2int_make_permanent_future_task_queue_holder_structure_internal();
		    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
			    Nil);
		    new_holder = 
			    def_structure_future_task_queue_holder_variable;
		    new_queue = g2int_make_empty_constant_queue();
		    SVREF(new_queue,FIX((SI_Long)2L)) = 
			    G2int_future_task_queue_marker;
		    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
		    aref_arg_1 = ISVREF(new_holder,(SI_Long)1L);
		    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,task_time);
		    SVREF(new_holder,FIX((SI_Long)2L)) = priority;
		    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
		    new_holder_1 = new_holder;
		    SVREF(new_holder_1,FIX((SI_Long)0L)) = queue_holder;
		    SVREF(holder_trailer,FIX((SI_Long)0L)) = new_holder_1;
		    temp = ISVREF(new_holder_1,(SI_Long)3L);
		    goto end;
		}
	    }
	}
	else {
	    def_structure_future_task_queue_holder_variable = 
		    G2int_chain_of_available_future_task_queue_holders;
	    if (def_structure_future_task_queue_holder_variable)
		G2int_chain_of_available_future_task_queue_holders = 
			ISVREF(def_structure_future_task_queue_holder_variable,
			(SI_Long)0L);
	    else
		def_structure_future_task_queue_holder_variable = 
			g2int_make_permanent_future_task_queue_holder_structure_internal();
	    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
		    Nil);
	    new_holder = def_structure_future_task_queue_holder_variable;
	    new_queue = g2int_make_empty_constant_queue();
	    SVREF(new_queue,FIX((SI_Long)2L)) = G2int_future_task_queue_marker;
	    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
	    aref_arg_1 = ISVREF(new_holder,(SI_Long)1L);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,task_time);
	    SVREF(new_holder,FIX((SI_Long)2L)) = priority;
	    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
	    new_holder_1 = new_holder;
	    SVREF(new_holder_1,FIX((SI_Long)0L)) = Nil;
	    SVREF(holder_trailer,FIX((SI_Long)0L)) = new_holder_1;
	    temp = ISVREF(new_holder_1,(SI_Long)3L);
	    goto end;
	}
	holder_trailer = queue_holder;
	queue_holder = ISVREF(queue_holder,(SI_Long)0L);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(temp);
}

/* DELETE-FUTURE-TASK-QUEUE-FOR-TASK */
Object g2int_delete_future_task_queue_for_task(schedule_task)
    Object schedule_task;
{
    Object priority, g2_running_task_qm, holder_trailer, queue_holder;
    Object svref_new_value;
    char temp;
    double task_time, arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(33,14);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	priority = ISVREF(schedule_task,(SI_Long)4L);
	task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_running_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	holder_trailer = g2_running_task_qm ? G2int_future_g2_time_tasks : 
		G2int_future_real_time_tasks;
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
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

Object G2int_current_real_time = UNBOUND;

Object G2int_current_g2_time = UNBOUND;

static Object Qg2int_real_time;    /* real-time */

/* UNPACK-FUTURE-TASKS-INTO-CURRENT-TASK-QUEUES */
Object g2int_unpack_future_tasks_into_current_task_queues(g2_clock_ticked_qm)
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

    x_note_fn_call(33,15);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	real_time = DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L);
	g2_time = DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L);
	g2_running_qm = G2int_system_is_running;
	scheduler_mode = Qg2int_real_time;
	if ( !TRUEP(g2_running_qm) ||  !TRUEP(g2_clock_ticked_qm)) {
	    future_queue = G2int_future_real_time_tasks;
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
	    queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		G2int_priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop;
	  end_loop:;
	}
	else if ( !EQ(scheduler_mode,Qg2int_real_time)) {
	    future_queue = G2int_future_real_time_tasks;
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
	    queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		G2int_priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_1;
	  end_loop_1:;
	    future_queue = G2int_future_g2_time_tasks;
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
	    queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		G2int_priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_2;
	  end_loop_2:;
	}
	else {
	    future_real_time_tasks_qm = 
		    ISVREF(G2int_future_real_time_tasks,(SI_Long)0L);
	    next_real_task_time = future_real_time_tasks_qm ? 
		    DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
		    (SI_Long)1L),(SI_Long)0L) : 0.0;
	    future_g2_time_tasks_qm = ISVREF(G2int_future_g2_time_tasks,
		    (SI_Long)0L);
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
		queue_holder = ISVREF(G2int_future_g2_time_tasks,(SI_Long)0L);
		next_queue_holder = queue_holder ? ISVREF(queue_holder,
			(SI_Long)0L) : Qnil;
		priority = ISVREF(queue_holder,(SI_Long)2L);
		queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
		g2int_reclaim_future_task_queue_holder(queue_holder);
		if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		    G2int_priority_of_next_task = priority;
		svref_arg_1 = G2int_future_g2_time_tasks;
		SVREF(svref_arg_1,FIX((SI_Long)0L)) = next_queue_holder;
		future_g2_time_tasks_qm = 
			ISVREF(G2int_future_g2_time_tasks,(SI_Long)0L);
		if (future_g2_time_tasks_qm)
		    next_g2_task_time = 
			    DFLOAT_ISAREF_1(ISVREF(future_g2_time_tasks_qm,
			    (SI_Long)1L),(SI_Long)0L);
	    }
	    else {
		queue_holder = ISVREF(G2int_future_real_time_tasks,
			(SI_Long)0L);
		next_queue_holder = queue_holder ? ISVREF(queue_holder,
			(SI_Long)0L) : Qnil;
		priority = ISVREF(queue_holder,(SI_Long)2L);
		queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
		g2int_reclaim_future_task_queue_holder(queue_holder);
		if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		    G2int_priority_of_next_task = priority;
		svref_arg_1 = G2int_future_real_time_tasks;
		SVREF(svref_arg_1,FIX((SI_Long)0L)) = next_queue_holder;
		future_real_time_tasks_qm = 
			ISVREF(G2int_future_real_time_tasks,(SI_Long)0L);
		if (future_real_time_tasks_qm)
		    next_real_task_time = 
			    DFLOAT_ISAREF_1(ISVREF(future_real_time_tasks_qm,
			    (SI_Long)1L),(SI_Long)0L);
	    }
	    goto next_loop_3;
	  end_loop_3:
	    future_queue = G2int_future_real_time_tasks;
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
	    queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		G2int_priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_4;
	  end_loop_4:;
	    future_queue = G2int_future_g2_time_tasks;
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
	    queue_to_fill = ISVREF(G2int_current_task_queue_vector,
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
	    g2int_reclaim_future_task_queue_holder(queue_holder);
	    if (FIXNUM_LT(priority,G2int_priority_of_next_task))
		G2int_priority_of_next_task = priority;
	    SVREF(future_queue,FIX((SI_Long)0L)) = next_queue_holder;
	    goto next_loop_5;
	  end_loop_5:;
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DEFER-CURRENT-G2-RUNNING-TASKS */
Object g2int_defer_current_g2_running_tasks()
{
    Object current_task_queue, deferred_task_queue, queue, next_queue_element;
    Object schedule_task, queue_element, old_next_element;
    Object old_previous_element, old_tail;
    SI_Long priority;

    x_note_fn_call(33,16);
    priority = IFIX(G2int_highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(G2int_lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(G2int_current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(G2int_deferred_task_queue_vector,priority);
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
Object g2int_requeue_deferred_running_tasks()
{
    Object current_task_queue, deferred_task_queue, head, tail, old_tail;
    SI_Long priority;

    x_note_fn_call(33,17);
    priority = IFIX(G2int_highest_system_priority);
    current_task_queue = Nil;
    deferred_task_queue = Nil;
  next_loop:
    if (priority > IFIX(G2int_lowest_system_priority))
	goto end_loop;
    current_task_queue = ISVREF(G2int_current_task_queue_vector,priority);
    deferred_task_queue = ISVREF(G2int_deferred_task_queue_vector,priority);
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
	if (priority < IFIX(G2int_priority_of_next_task))
	    G2int_priority_of_next_task = FIX(priority);
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

Object G2int_scheduler_has_been_initialized_p = UNBOUND;

/* INITIALIZE-SCHEDULER */
Object g2int_initialize_scheduler()
{
    Object number_of_priorities, new_vector, temp;
    Object def_structure_future_task_queue_holder_variable, new_holder;
    Object new_queue;
    SI_Long index_1;

    x_note_fn_call(33,18);
    G2int_immediate_task_queue = g2int_make_empty_constant_queue();
    number_of_priorities = 
	    FIXNUM_ADD1(FIXNUM_MINUS(G2int_lowest_system_priority,
	    G2int_highest_system_priority));
    new_vector = make_array(1,number_of_priorities);
    index_1 = IFIX(G2int_highest_system_priority);
  next_loop:
    if (index_1 > IFIX(G2int_lowest_system_priority))
	goto end_loop;
    temp = g2int_make_empty_constant_queue();
    ISVREF(new_vector,index_1) = temp;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    G2int_current_task_queue_vector = new_vector;
    G2int_priority_of_next_task = G2int_lower_than_any_priority;
    new_vector = make_array(1,number_of_priorities);
    index_1 = IFIX(G2int_highest_system_priority);
  next_loop_1:
    if (index_1 > IFIX(G2int_lowest_system_priority))
	goto end_loop_1;
    temp = g2int_make_empty_constant_queue();
    ISVREF(new_vector,index_1) = temp;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:
    G2int_deferred_task_queue_vector = new_vector;
    def_structure_future_task_queue_holder_variable = 
	    G2int_chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	G2int_chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		g2int_make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    new_holder = def_structure_future_task_queue_holder_variable;
    new_queue = g2int_make_empty_constant_queue();
    SVREF(new_queue,FIX((SI_Long)2L)) = G2int_future_task_queue_marker;
    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
    temp = ISVREF(new_holder,(SI_Long)1L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,0.0);
    ISVREF(new_holder,(SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
    G2int_future_real_time_tasks = new_holder;
    def_structure_future_task_queue_holder_variable = 
	    G2int_chain_of_available_future_task_queue_holders;
    if (def_structure_future_task_queue_holder_variable)
	G2int_chain_of_available_future_task_queue_holders = 
		ISVREF(def_structure_future_task_queue_holder_variable,
		(SI_Long)0L);
    else
	def_structure_future_task_queue_holder_variable = 
		g2int_make_permanent_future_task_queue_holder_structure_internal();
    inline_note_allocate_cons(def_structure_future_task_queue_holder_variable,
	    Nil);
    new_holder = def_structure_future_task_queue_holder_variable;
    new_queue = g2int_make_empty_constant_queue();
    SVREF(new_queue,FIX((SI_Long)2L)) = G2int_future_task_queue_marker;
    SVREF(new_holder,FIX((SI_Long)3L)) = new_queue;
    temp = ISVREF(new_holder,(SI_Long)1L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,0.0);
    ISVREF(new_holder,(SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(new_holder,FIX((SI_Long)0L)) = Nil;
    G2int_future_g2_time_tasks = new_holder;
    G2int_scheduler_has_been_initialized_p = T;
    return VALUES_1(Nil);
}

/* CANCEL-G2-RUNNING-TASKS */
Object g2int_cancel_g2_running_tasks()
{
    x_note_fn_call(33,19);
    error((SI_Long)1L,
	    "Cancel-g2-running-tasks not implementented yet.  -jra 2/20/94");
    return VALUES_1(Nil);
}

/* CANCEL-AND-RECLAIM-SCHEDULED-QUEUE-ELEMENT-1 */
Object g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task)
    Object schedule_task;
{
    Object queue_element, next_queue_element, gensymed_symbol;
    Object gensymed_symbol_1, svref_new_value;
    char temp;

    x_note_fn_call(33,20);
    queue_element = ISVREF(schedule_task,(SI_Long)6L);
    if (queue_element) {
	SVREF(schedule_task,FIX((SI_Long)6L)) = Nil;
	next_queue_element = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol = ISVREF(queue_element,(SI_Long)0L);
	gensymed_symbol_1 = ISVREF(queue_element,(SI_Long)1L);
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = gensymed_symbol;
	SVREF(gensymed_symbol,FIX((SI_Long)1L)) = gensymed_symbol_1;
	inline_note_reclaim_cons(queue_element,Nil);
	svref_new_value = G2int_chain_of_available_queue_elements;
	SVREF(queue_element,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_queue_elements = queue_element;
	if (EQ(ISVREF(next_queue_element,(SI_Long)2L),
		G2int_future_task_queue_marker)) {
	    gensymed_symbol = ISVREF(next_queue_element,(SI_Long)0L);
	    temp =  !( !EQ(gensymed_symbol,next_queue_element) ? 
		    TRUEP(ISVREF(gensymed_symbol,(SI_Long)2L)) : TRUEP(Nil));
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    g2int_delete_future_task_queue_for_task(schedule_task);
    }
    return VALUES_1(Nil);
}

/* FUTURE-TASK-SCHEDULE-2 */
Object g2int_future_task_schedule_2(schedule_task)
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

    x_note_fn_call(33,21);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	new_task_time = DFLOAT_ISAREF_1(ISVREF(schedule_task,(SI_Long)1L),
		(SI_Long)0L);
	g2_task_qm = ISVREF(schedule_task,(SI_Long)3L);
	if (g2_task_qm) {
	    millisecond_minimum_scheduling_interval_qm = Nil;
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
	arg_1 = DFLOAT_ISAREF_1(g2_task_qm ? G2int_current_g2_time : 
		G2int_current_real_time,(SI_Long)0L);
	future_task_qm = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?
		 ( !inline_nanp_for_comparison(arg_1) ? T : Nil) : Qnil;
	if ( !TRUEP(future_task_qm)) {
	    current_task_qm =  !TRUEP(g2_task_qm) ? T : Nil;
	    if (current_task_qm);
	    else
		current_task_qm = G2int_system_is_running;
	}
	else
	    current_task_qm = Nil;
	priority = ISVREF(schedule_task,(SI_Long)4L);
	queue = future_task_qm ? 
		g2int_get_or_create_future_task_queue_for_task(schedule_task) 
		: ISVREF(current_task_qm ? G2int_current_task_queue_vector 
		: G2int_deferred_task_queue_vector,IFIX(priority));
	gensymed_symbol = ISVREF(queue,(SI_Long)1L);
	def_structure_queue_element_variable = 
		G2int_chain_of_available_queue_elements;
	if (def_structure_queue_element_variable)
	    G2int_chain_of_available_queue_elements = 
		    ISVREF(def_structure_queue_element_variable,(SI_Long)0L);
	else
	    def_structure_queue_element_variable = 
		    g2int_make_permanent_queue_element_structure_internal();
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
	if (current_task_qm && FIXNUM_LT(priority,G2int_priority_of_next_task))
	    G2int_priority_of_next_task = priority;
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

/* DEQUEUE-NEXT-TASK */
Object g2int_dequeue_next_task()
{
    Object current_task_qm, gensymed_symbol, gensymed_symbol_1, temp;
    Object gensymed_symbol_2, gensymed_symbol_3, svref_new_value;
    SI_Long priority;

    x_note_fn_call(33,22);
    priority = IFIX(G2int_priority_of_next_task);
    current_task_qm = Nil;
  next_loop:
    if (priority > IFIX(G2int_lowest_system_priority))
	goto end_loop;
    gensymed_symbol = ISVREF(G2int_current_task_queue_vector,priority);
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
	svref_new_value = G2int_chain_of_available_queue_elements;
	SVREF(gensymed_symbol_1,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_queue_elements = gensymed_symbol_1;
	temp = gensymed_symbol_2;
	current_task_qm = temp;
    }
    if (current_task_qm) {
	G2int_priority_of_next_task = FIX(priority);
	G2int_priority_of_current_task = FIX(priority);
	SVREF(current_task_qm,FIX((SI_Long)6L)) = Nil;
	G2int_current_schedule_task = current_task_qm;
	goto end;
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:
    G2int_priority_of_next_task = G2int_lower_than_any_priority;
  end:;
    return VALUES_1(Nil);
}

static Object Qg2int_ab;           /* ab */

static Object Qg2int_mqtt_poll_watcher;  /* mqtt-poll-watcher */

/* DEQUEUE-AND-EXECUTE-NEXT-TASK */
Object g2int_dequeue_and_execute_next_task()
{
    Object priority_to_use, local_immediate_queue, immediate_task_qm;
    Object gensymed_symbol, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object svref_new_value, reclaim_task_qm, function, gensymed_symbol_3;
    Object gensymed_symbol_4, old_structure_being_reclaimed, current_task;
    Object task_function_name;
    char temp_1;

    x_note_fn_call(33,23);
    if (G2int_current_schedule_task) {
	if (ISVREF(G2int_current_schedule_task,(SI_Long)2L))
	    g2int_reclaim_schedule_task_1(G2int_current_schedule_task);
	G2int_current_schedule_task = Nil;
    }
    priority_to_use = FIXNUMP(G2int_priority_of_current_task) && 
	    FIXNUM_GE(G2int_priority_of_current_task,
	    G2int_highest_system_priority) && 
	    FIXNUM_LE(G2int_priority_of_current_task,
	    G2int_lowest_system_priority) ? G2int_priority_of_current_task 
	    : G2int_highest_system_priority;
    local_immediate_queue = G2int_immediate_task_queue;
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
	svref_new_value = G2int_chain_of_available_queue_elements;
	SVREF(gensymed_symbol,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_queue_elements = gensymed_symbol;
	temp = gensymed_symbol_1;
	immediate_task_qm = temp;
    }
    if ( !TRUEP(immediate_task_qm))
	goto end_loop;
    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
    G2int_priority_of_current_task = priority_to_use;
    G2int_current_schedule_task = immediate_task_qm;
    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
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
    if (reclaim_task_qm && EQ(immediate_task_qm,G2int_current_schedule_task)) {
	inline_note_reclaim_cons(immediate_task_qm,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = immediate_task_qm;
	g2int_reclaim_schedule_task_args(ISVREF(immediate_task_qm,
		(SI_Long)9L));
	SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	svref_new_value = G2int_chain_of_available_schedule_tasks;
	SVREF(immediate_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	G2int_chain_of_available_schedule_tasks = immediate_task_qm;
    }
    goto next_loop;
  end_loop:;
    G2int_priority_of_current_task = G2int_higher_than_any_priority;
    G2int_current_schedule_task = Nil;
    if (G2int_time_to_check_network_events) {
	temp_1 = TRUEP(g2int_g2_event_ready_p());
	if (temp_1);
	else {
	    G2int_time_to_check_network_events = Nil;
	    temp_1 = TRUEP(G2int_time_to_check_network_events);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	G2int_time_to_check_network_events = Nil;
	g2int_get_pending_network_events();
    }
    if (EQ(G2int_current_system_name,Qg2int_ab))
	FUNCALL_SYMBOL_0(Qg2int_mqtt_poll_watcher);
    g2int_dequeue_next_task();
    if ( !TRUEP(G2int_current_schedule_task) && 
	    (g2int_get_pending_network_events() || 
	    g2int_tick_the_clock_for_tw_or_gsi()))
	g2int_dequeue_next_task();
    if (G2int_current_schedule_task) {
	current_task = G2int_current_schedule_task;
	task_function_name = ISVREF(current_task,(SI_Long)7L);
	g2int_execute_task_and_reschedule(current_task);
	G2int_current_schedule_task = Nil;
	local_immediate_queue = G2int_immediate_task_queue;
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
	    svref_new_value = G2int_chain_of_available_queue_elements;
	    SVREF(gensymed_symbol,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_queue_elements = gensymed_symbol;
	    temp = gensymed_symbol_1;
	    immediate_task_qm = temp;
	}
	if ( !TRUEP(immediate_task_qm))
	    goto end_loop_1;
	SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	G2int_current_schedule_task = immediate_task_qm;
	reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
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
	if (reclaim_task_qm && EQ(immediate_task_qm,
		G2int_current_schedule_task)) {
	    inline_note_reclaim_cons(immediate_task_qm,Nil);
	    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	    G2int_structure_being_reclaimed = immediate_task_qm;
	    g2int_reclaim_schedule_task_args(ISVREF(immediate_task_qm,
		    (SI_Long)9L));
	    SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
	    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	    svref_new_value = G2int_chain_of_available_schedule_tasks;
	    SVREF(immediate_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	    G2int_chain_of_available_schedule_tasks = immediate_task_qm;
	}
	goto next_loop_1;
      end_loop_1:;
	G2int_priority_of_current_task = G2int_higher_than_any_priority;
	G2int_current_schedule_task = Nil;
	G2int_priority_of_current_task = G2int_higher_than_any_priority;
	temp = task_function_name;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* EXECUTE-TASK-AND-RESCHEDULE */
Object g2int_execute_task_and_reschedule(current_task)
    Object current_task;
{
    Object reclaim_task_qm, function, temp, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object g2_running_qm, temp_1, old_structure_being_reclaimed;
    double interval, arg, arg_1, current_time, old_task_time, new_time;

    x_note_fn_call(33,24);
    reclaim_task_qm = ISVREF(current_task,(SI_Long)2L);
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
    if (EQ(G2int_current_schedule_task,current_task)) {
	interval = DFLOAT_ISAREF_1(ISVREF(current_task,(SI_Long)1L),
		(SI_Long)1L);
	arg = interval;
	arg_1 = 0.0;
	if (arg > arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1)) {
	    g2_running_qm = ISVREF(current_task,(SI_Long)3L);
	    current_time = g2_running_qm ? 
		    DFLOAT_ISAREF_1(G2int_current_g2_time,(SI_Long)0L) : 
		    DFLOAT_ISAREF_1(G2int_current_real_time,(SI_Long)0L);
	    old_task_time = DFLOAT_ISAREF_1(ISVREF(current_task,
		    (SI_Long)1L),(SI_Long)0L);
	    new_time = interval + current_time;
	    if (ISVREF(current_task,(SI_Long)5L)) {
		new_time = old_task_time + interval;
		arg = new_time;
		arg_1 = current_time;
		if ( !(arg > arg_1 &&  !inline_nanp_for_comparison(arg) && 
			 !inline_nanp_for_comparison(arg_1)))
		    new_time = old_task_time + interval * 
			    inline_fceiling_1((current_time - 
			    old_task_time) / interval);
	    }
	    temp_1 = ISVREF(current_task,(SI_Long)1L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,new_time);
	    g2int_future_task_schedule_2(current_task);
	    G2int_current_schedule_task = Nil;
	}
    }
    if (reclaim_task_qm && EQ(current_task,G2int_current_schedule_task)) {
	inline_note_reclaim_cons(current_task,Nil);
	old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	G2int_structure_being_reclaimed = current_task;
	g2int_reclaim_schedule_task_args(ISVREF(current_task,(SI_Long)9L));
	SVREF(current_task,FIX((SI_Long)9L)) = Nil;
	G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	temp_1 = G2int_chain_of_available_schedule_tasks;
	SVREF(current_task,FIX((SI_Long)0L)) = temp_1;
	G2int_chain_of_available_schedule_tasks = current_task;
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* TASKS-ENQUEUED-FOR-CURRENT-EXECUTION? */
Object g2int_tasks_enqueued_for_current_executionqm()
{
    Object temp, ab_loop_it_, constant_queue;
    SI_Long priority;

    x_note_fn_call(33,25);
    temp =  !EQ(ISVREF(G2int_immediate_task_queue,(SI_Long)0L),
	    G2int_immediate_task_queue) ? T : Nil;
    if (temp);
    else {
	priority = IFIX(G2int_highest_system_priority);
	ab_loop_it_ = Nil;
      next_loop:
	if (priority > IFIX(G2int_lowest_system_priority))
	    goto end_loop;
	constant_queue = ISVREF(G2int_current_task_queue_vector,priority);
	ab_loop_it_ =  !EQ(ISVREF(constant_queue,(SI_Long)0L),
		constant_queue) ? T : Nil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end;
	}
	priority = priority + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
    }
    return VALUES_1(temp);
}

/* TASKS-DEFERRED-UNTIL-RESUMPTION? */
Object g2int_tasks_deferred_until_resumptionqm()
{
    Object ab_loop_it_, constant_queue, temp;
    SI_Long priority;

    x_note_fn_call(33,26);
    priority = IFIX(G2int_highest_system_priority);
    ab_loop_it_ = Nil;
  next_loop:
    if (priority > IFIX(G2int_lowest_system_priority))
	goto end_loop;
    constant_queue = ISVREF(G2int_deferred_task_queue_vector,priority);
    ab_loop_it_ =  !EQ(ISVREF(constant_queue,(SI_Long)0L),constant_queue) ?
	     T : Nil;
    if (ab_loop_it_) {
	temp = ab_loop_it_;
	goto end;
    }
    priority = priority + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

/* NEXT-SCHEDULED-TASK-FOR-FUNCTION */
Object g2int_next_scheduled_task_for_function(function_name,priority)
    Object function_name, priority;
{
    Object gensymed_symbol, immediate_task_qm, temp, current_task_qm;
    Object gensymed_symbol_1;
    SI_Long priority_1, ab_loop_bind_;

    x_note_fn_call(33,27);
    gensymed_symbol = ISVREF(G2int_immediate_task_queue,(SI_Long)0L);
    immediate_task_qm =  !EQ(gensymed_symbol,G2int_immediate_task_queue) ? 
	    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
    if (immediate_task_qm)
	temp = EQ(ISVREF(immediate_task_qm,(SI_Long)7L),function_name) ? 
		immediate_task_qm : Nil;
    else {
	priority_1 = IFIX(G2int_priority_of_next_task);
	ab_loop_bind_ = IFIX(priority);
	current_task_qm = Nil;
      next_loop:
	if (priority_1 > ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = ISVREF(G2int_current_task_queue_vector,priority_1);
	gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)0L);
	current_task_qm =  !EQ(gensymed_symbol_1,gensymed_symbol) ? 
		ISVREF(gensymed_symbol_1,(SI_Long)2L) : Nil;
	if (current_task_qm) {
	    temp = EQ(ISVREF(current_task_qm,(SI_Long)7L),function_name) 
		    && IFIX(ISVREF(current_task_qm,(SI_Long)4L)) == 
		    priority_1 ? current_task_qm : Nil;
	    goto end;
	}
	priority_1 = priority_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = Qnil;
      end:;
    }
    return VALUES_1(temp);
}

/* EXECUTE-TASK-OUT-OF-ORDER-1 */
Object g2int_execute_task_out_of_order_1(schedule_task)
    Object schedule_task;
{
    Object temp, priority_of_current_task, current_schedule_task;
    Object reclaim_task_qm, function, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object old_structure_being_reclaimed, svref_new_value;
    Object local_immediate_queue, immediate_task_qm;
    Declare_special(2);

    x_note_fn_call(33,28);
    if (schedule_task) {
	if (ISVREF(schedule_task,(SI_Long)6L))
	    g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	if (EQ(schedule_task,G2int_current_schedule_task))
	    G2int_current_schedule_task = Nil;
	temp = ISVREF(schedule_task,(SI_Long)4L);
	priority_of_current_task = FIXNUM_MAX(temp,
		G2int_highest_system_priority);
	current_schedule_task = schedule_task;
	reclaim_task_qm = ISVREF(schedule_task,(SI_Long)2L);
	PUSH_SPECIAL(G2int_current_schedule_task,current_schedule_task,1);
	  PUSH_SPECIAL(G2int_priority_of_current_task,priority_of_current_task,
		  0);
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
	    if (reclaim_task_qm) {
		inline_note_reclaim_cons(schedule_task,Nil);
		old_structure_being_reclaimed = 
			G2int_structure_being_reclaimed;
		G2int_structure_being_reclaimed = schedule_task;
		g2int_reclaim_schedule_task_args(ISVREF(schedule_task,
			(SI_Long)9L));
		SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
		G2int_structure_being_reclaimed = 
			old_structure_being_reclaimed;
		svref_new_value = G2int_chain_of_available_schedule_tasks;
		SVREF(schedule_task,FIX((SI_Long)0L)) = svref_new_value;
		G2int_chain_of_available_schedule_tasks = schedule_task;
	    }
	    local_immediate_queue = G2int_immediate_task_queue;
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
		svref_new_value = G2int_chain_of_available_queue_elements;
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = svref_new_value;
		G2int_chain_of_available_queue_elements = gensymed_symbol;
		temp = gensymed_symbol_1;
		immediate_task_qm = temp;
	    }
	    if ( !TRUEP(immediate_task_qm))
		goto end_loop;
	    SVREF(immediate_task_qm,FIX((SI_Long)6L)) = Nil;
	    G2int_priority_of_current_task = G2int_highest_system_priority;
	    G2int_current_schedule_task = immediate_task_qm;
	    reclaim_task_qm = ISVREF(immediate_task_qm,(SI_Long)2L);
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
	    if (reclaim_task_qm && EQ(immediate_task_qm,
		    G2int_current_schedule_task)) {
		inline_note_reclaim_cons(immediate_task_qm,Nil);
		old_structure_being_reclaimed = 
			G2int_structure_being_reclaimed;
		G2int_structure_being_reclaimed = immediate_task_qm;
		g2int_reclaim_schedule_task_args(ISVREF(immediate_task_qm,
			(SI_Long)9L));
		SVREF(immediate_task_qm,FIX((SI_Long)9L)) = Nil;
		G2int_structure_being_reclaimed = 
			old_structure_being_reclaimed;
		svref_new_value = G2int_chain_of_available_schedule_tasks;
		SVREF(immediate_task_qm,FIX((SI_Long)0L)) = svref_new_value;
		G2int_chain_of_available_schedule_tasks = immediate_task_qm;
	    }
	    goto next_loop;
	  end_loop:;
	    G2int_priority_of_current_task = G2int_higher_than_any_priority;
	    G2int_current_schedule_task = Nil;
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qg2int_clear_g2_schedule;  /* clear-g2-schedule */

/* CLEAR-G2-SCHEDULE */
Object g2int_clear_g2_schedule()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, queue;
    Object next_queue_element, schedule_task, old_structure_being_reclaimed;
    Object queue_1, next_queue_holder, queue_holder;
    SI_Long priority;
    Declare_special(1);

    x_note_fn_call(33,29);
    index_of_top_of_backtrace_stack = G2int_index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(G2int_index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(G2int_index_of_top_of_backtrace_stack,
	      G2int_size_of_basic_backtrace_information),
	      G2int_maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(G2int_index_of_top_of_backtrace_stack);
	  G2int_index_of_top_of_backtrace_stack = temp;
	  temp = G2int_backtrace_stack_for_internal_error;
	  svref_arg_2 = G2int_index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qg2int_clear_g2_schedule;
      }
      queue = G2int_immediate_task_queue;
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
	      g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	      G2int_structure_being_reclaimed = schedule_task;
	      g2int_reclaim_schedule_task_args(ISVREF(schedule_task,
		      (SI_Long)9L));
	      SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	      temp = G2int_chain_of_available_schedule_tasks;
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      G2int_chain_of_available_schedule_tasks = schedule_task;
	  }
      }
      goto next_loop;
    end_loop:;
      priority = IFIX(G2int_highest_system_priority);
      queue_1 = Nil;
    next_loop_1:
      if (priority > IFIX(G2int_lowest_system_priority))
	  goto end_loop_1;
      queue_1 = ISVREF(G2int_current_task_queue_vector,priority);
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
	      g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
	  if (ISVREF(schedule_task,(SI_Long)2L)) {
	      inline_note_reclaim_cons(schedule_task,Nil);
	      old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	      G2int_structure_being_reclaimed = schedule_task;
	      g2int_reclaim_schedule_task_args(ISVREF(schedule_task,
		      (SI_Long)9L));
	      SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	      G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	      temp = G2int_chain_of_available_schedule_tasks;
	      SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	      G2int_chain_of_available_schedule_tasks = schedule_task;
	  }
      }
      goto next_loop_2;
    end_loop_2:;
      priority = priority + (SI_Long)1L;
      goto next_loop_1;
    end_loop_1:;
      priority = IFIX(G2int_highest_system_priority);
      queue_1 = Nil;
    next_loop_3:
      if (priority > IFIX(G2int_lowest_system_priority))
	  goto end_loop_3;
      queue_1 = ISVREF(G2int_deferred_task_queue_vector,priority);
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
	  g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	  G2int_structure_being_reclaimed = schedule_task;
	  g2int_reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	  SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	  temp = G2int_chain_of_available_schedule_tasks;
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  G2int_chain_of_available_schedule_tasks = schedule_task;
      }
      goto next_loop_4;
    end_loop_4:;
      priority = priority + (SI_Long)1L;
      goto next_loop_3;
    end_loop_3:;
      next_queue_holder = ISVREF(G2int_future_g2_time_tasks,(SI_Long)0L);
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
	  g2int_cancel_and_reclaim_scheduled_queue_element_1(schedule_task);
      if (ISVREF(schedule_task,(SI_Long)2L)) {
	  inline_note_reclaim_cons(schedule_task,Nil);
	  old_structure_being_reclaimed = G2int_structure_being_reclaimed;
	  G2int_structure_being_reclaimed = schedule_task;
	  g2int_reclaim_schedule_task_args(ISVREF(schedule_task,(SI_Long)9L));
	  SVREF(schedule_task,FIX((SI_Long)9L)) = Nil;
	  G2int_structure_being_reclaimed = old_structure_being_reclaimed;
	  temp = G2int_chain_of_available_schedule_tasks;
	  SVREF(schedule_task,FIX((SI_Long)0L)) = temp;
	  G2int_chain_of_available_schedule_tasks = schedule_task;
      }
      goto next_loop_6;
    end_loop_6:;
      goto next_loop_5;
    end_loop_5:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* ADJUST-TASK-TIMES-AFTER-CLOCK-DISCONTINUITY */
Object g2int_adjust_task_times_after_clock_discontinuity(managed_float_offset,
	    future_task_queue_set)
    Object managed_float_offset, future_task_queue_set;
{
    Object next_queue_holder, task_queue_holder, holder_time, queue, queue_1;
    Object next_queue_element, schedule_task, aref_arg_1;
    double offset, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(33,30);
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

Object G2int_time_slice_start_time = UNBOUND;

Object G2int_maximum_time_slice_size = UNBOUND;

/* TIME-SLICE-EXPIRED-P */
Object g2int_time_slice_expired_p()
{
    Object temp;
    SI_Long gensymed_symbol, gensymed_symbol_1, elapsed_time;

    x_note_fn_call(33,31);
    temp = FIXNUM_LT(G2int_priority_of_next_task,
	    G2int_priority_of_current_task) ? T : Nil;
    if (temp);
    else {
	gensymed_symbol = IFIX(g2int_c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(G2int_time_slice_start_time);
	if (gensymed_symbol >= gensymed_symbol_1)
	    elapsed_time = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    elapsed_time = gensymed_symbol + (SI_Long)1L;
	}
	temp = elapsed_time >= IFIX(G2int_maximum_time_slice_size) ? T : Nil;
    }
    if (temp);
    else if (FIXNUM_NE(G2int_priority_of_next_task,Most_positive_fixnum)) {
	if (G2int_time_to_check_network_events) {
	    temp = g2int_g2_event_ready_p();
	    if (temp);
	    else {
		G2int_time_to_check_network_events = Nil;
		temp = G2int_time_to_check_network_events;
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
Object g2int_time_slice_expired_p_given_time(given_fixnum_time)
    Object given_fixnum_time;
{
    Object temp;
    SI_Long elapsed_time, gensymed_symbol;

    x_note_fn_call(33,32);
    temp = FIXNUM_LT(G2int_priority_of_next_task,
	    G2int_priority_of_current_task) ? T : Nil;
    if (temp);
    else {
	if (FIXNUM_GE(given_fixnum_time,G2int_time_slice_start_time))
	    elapsed_time = IFIX(FIXNUM_MINUS(given_fixnum_time,
		    G2int_time_slice_start_time));
	else {
	    gensymed_symbol = IFIX(FIXNUM_MINUS(given_fixnum_time,
		    G2int_time_slice_start_time));
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    elapsed_time = gensymed_symbol + (SI_Long)1L;
	}
	temp = elapsed_time >= IFIX(G2int_maximum_time_slice_size) ? T : Nil;
    }
    return VALUES_1(temp);
}

static Object float_constant;      /* 0.0 */

/* SCHEDULER-TIME-LAG */
Object g2int_scheduler_time_lag(priority)
    Object priority;
{
    Object queue, next_queue_element, task, temp;

    x_note_fn_call(33,33);
    queue = ISVREF(G2int_current_task_queue_vector,IFIX(priority));
    next_queue_element = Nil;
    task = Nil;
    next_queue_element = ISVREF(queue,(SI_Long)0L);
  next_loop:
    if (EQ(next_queue_element,queue))
	goto end_loop;
    task = ISVREF(next_queue_element,(SI_Long)2L);
    next_queue_element = ISVREF(next_queue_element,(SI_Long)0L);
    if (ISVREF(task,(SI_Long)3L)) {
	temp = 
		DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2int_current_g2_time,
		(SI_Long)0L) - DFLOAT_ISAREF_1(ISVREF(task,(SI_Long)1L),
		(SI_Long)0L));
	goto end;
    }
    goto next_loop;
  end_loop:
    temp = float_constant;
    goto end;
    temp = Qnil;
  end:;
    return VALUES_1(temp);
}

static Object string_constant;     /* "Time Cyclic G2-Running? Priority Function-and-Args" */

/* TWRITE-SCHEDULE-TASK-HEADER */
Object g2int_twrite_schedule_task_header()
{
    x_note_fn_call(33,34);
    g2int_tformat(1,string_constant);
    return VALUES_1(Nil);
}

static Object Qg2int_ab_name_of_unique_structure_type;  /* ab-name-of-unique-structure-type */

/* TYPE-NAME-OF-NAMED-SIMPLE-VECTOR */
Object g2int_type_name_of_named_simple_vector(arg)
    Object arg;
{
    Object type, temp;

    x_note_fn_call(33,35);
    if (g2int_allocated_named_gensym_structure_p(arg)) {
	type = ISVREF(arg,(SI_Long)0L);
	temp = SYMBOL_PACKAGE(type);
	temp = EQ(temp,G2int_the_g2_defstruct_package) ? 
		g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(type),
		Qg2int_ab_name_of_unique_structure_type) : type;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object G2int_gsi_maximum_idle_interval = UNBOUND;

/* MILLISECONDS-TO-NEXT-SCHEDULER-EVENT */
Object g2int_milliseconds_to_next_scheduler_event()
{
    Object temp_1, milliseconds_to_next_task;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp;

    x_note_fn_call(33,36);
    temp = TRUEP(g2int_tasks_enqueued_for_current_executionqm());
    if (temp);
    else {
	g2int_tick_the_clock_for_tw_or_gsi();
	temp = TRUEP(g2int_tasks_enqueued_for_current_executionqm());
    }
    if (temp)
	temp_1 = Nil;
    else {
	milliseconds_to_next_task = g2int_milliseconds_to_next_task();
	if (milliseconds_to_next_task && (SI_Long)0L >= 
		IFIX(milliseconds_to_next_task))
	    temp_1 = Nil;
	else {
	    temp_1 = milliseconds_to_next_task;
	    if (temp_1);
	    else
		temp_1 = Most_positive_fixnum;
	    gensymed_symbol = IFIX(temp_1);
	    gensymed_symbol_1 = IFIX(G2int_gsi_maximum_idle_interval);
	    temp_1 = FIX(MIN(gensymed_symbol,gensymed_symbol_1));
	}
    }
    return VALUES_1(temp_1);
}

/* ENQUEUE-SCHEDULER-EVENTS-IF-NECESSARY */
Object g2int_enqueue_scheduler_events_if_necessary(force_scheduler_event_qm)
    Object force_scheduler_event_qm;
{
    Object milliseconds_to_sleep_qm;

    x_note_fn_call(33,37);
    milliseconds_to_sleep_qm =  !TRUEP(force_scheduler_event_qm) ? 
	    g2int_milliseconds_to_next_scheduler_event() : Nil;
    if (milliseconds_to_sleep_qm)
	ne_set_next_timer_event(IFIX(milliseconds_to_sleep_qm));
    else
	ne_enqueue_scheduler_event();
    return VALUES_1(milliseconds_to_sleep_qm);
}

void schedule_INIT()
{
    Object temp, reclaim_structure_for_schedule_task;
    Object reclaim_structure_for_future_task_queue_holder;
    Object list_constant_1, Qg2int_clocks, Qg2int_maximum_time_slice_size;
    Object Qg2int_fixnum_time_interval, Kfuncall, AB_package, Qg2int_schedule;
    Object Qg2int_scheduler_has_been_initialized_p, list_constant;
    Object Qg2int_future_task_queue_marker, Qg2int_priority_of_next_task;
    Object Qg2int_priority_of_current_task, Qg2int_current_schedule_task;
    Object Qg2int_system_has_aborted, Qg2int_system_has_paused;
    Object Qg2int_system_is_running, Qg2int_future_task_queue_holder;
    Object Qg2int_reclaim_structure, Qg2int_utilities2;
    Object Qg2int_future_task_queue_holder_count;
    Object Qg2int_chain_of_available_future_task_queue_holders;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_2;
    Object Qg2int_future_g2_time_tasks, Qg2int_future_real_time_tasks;
    Object Qg2int_deferred_task_queue_vector, Qg2int_current_task_queue_vector;
    Object Qg2int_immediate_task_queue, Qg2int_schedule_task_arg_limit;
    Object Qg2int_schedule_task, Qg2int_schedule_task_count;
    Object Qg2int_chain_of_available_schedule_tasks, string_constant_1;
    Object Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_schedule_task_arg_offset, Qg2int_lower_than_any_priority;
    Object Qg2int_higher_than_any_priority, Qg2int_lowest_system_priority;
    Object Qg2int_highest_system_priority, Qg2int_highest_user_priority;
    Object Qg2int_how_many_prioritiesqm;

    x_note_fn_call(33,38);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_how_many_prioritiesqm = STATIC_SYMBOL("HOW-MANY-PRIORITIES\?",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_how_many_prioritiesqm,FIX((SI_Long)10L));
    Qg2int_highest_user_priority = STATIC_SYMBOL("HIGHEST-USER-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_highest_user_priority,FIX((SI_Long)1L));
    Qg2int_highest_system_priority = 
	    STATIC_SYMBOL("HIGHEST-SYSTEM-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_highest_system_priority,FIX((SI_Long)0L));
    Qg2int_lowest_system_priority = STATIC_SYMBOL("LOWEST-SYSTEM-PRIORITY",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_lowest_system_priority,FIX((SI_Long)11L));
    Qg2int_higher_than_any_priority = 
	    STATIC_SYMBOL("HIGHER-THAN-ANY-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_higher_than_any_priority,FIX((SI_Long)-1L));
    Qg2int_lower_than_any_priority = 
	    STATIC_SYMBOL("LOWER-THAN-ANY-PRIORITY",AB_package);
    SET_SYMBOL_VALUE(Qg2int_lower_than_any_priority,FIX((SI_Long)12L));
    Qg2int_schedule_task_arg_offset = 
	    STATIC_SYMBOL("SCHEDULE-TASK-ARG-OFFSET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_schedule_task_arg_offset,FIX((SI_Long)11L));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2int_schedule_task = STATIC_SYMBOL("SCHEDULE-TASK",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    Qg2int_schedule_task,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_schedule_task,
	    Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_schedule_task == UNBOUND)
	G2int_the_type_description_of_schedule_task = Nil;
    string_constant_1 = 
	    STATIC_STRING("43Dy8l83=sy1n83=sy8m8k1l8m0000001n1m83Cy3ky1n8n83*uy1l83=vy1m8300y1m83=ty83=uykzk0k0");
    temp = G2int_the_type_description_of_schedule_task;
    G2int_the_type_description_of_schedule_task = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_1));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_schedule_task_g2_struct,
	    G2int_the_type_description_of_schedule_task,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_schedule_task,
	    G2int_the_type_description_of_schedule_task,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_schedule_tasks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SCHEDULE-TASKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_schedule_tasks,
	    G2int_chain_of_available_schedule_tasks);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_schedule_tasks,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_schedule_task_count = STATIC_SYMBOL("SCHEDULE-TASK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_schedule_task_count,
	    G2int_schedule_task_count);
    g2int_record_system_variable(Qg2int_schedule_task_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_schedule_task = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_schedule_task,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_schedule_task,reclaim_structure_for_schedule_task);
    Qg2int_schedule_task_arg_limit = 
	    STATIC_SYMBOL("SCHEDULE-TASK-ARG-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qg2int_schedule_task_arg_limit,FIX((SI_Long)4L));
    Qg2int_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qg2int_immediate_task_queue = STATIC_SYMBOL("IMMEDIATE-TASK-QUEUE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_immediate_task_queue,
	    G2int_immediate_task_queue);
    Qg2int_schedule = STATIC_SYMBOL("SCHEDULE",AB_package);
    g2int_record_system_variable(Qg2int_immediate_task_queue,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_current_task_queue_vector = 
	    STATIC_SYMBOL("CURRENT-TASK-QUEUE-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_task_queue_vector,
	    G2int_current_task_queue_vector);
    g2int_record_system_variable(Qg2int_current_task_queue_vector,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_deferred_task_queue_vector = 
	    STATIC_SYMBOL("DEFERRED-TASK-QUEUE-VECTOR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_deferred_task_queue_vector,
	    G2int_deferred_task_queue_vector);
    g2int_record_system_variable(Qg2int_deferred_task_queue_vector,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_future_real_time_tasks = STATIC_SYMBOL("FUTURE-REAL-TIME-TASKS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_future_real_time_tasks,
	    G2int_future_real_time_tasks);
    g2int_record_system_variable(Qg2int_future_real_time_tasks,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_future_g2_time_tasks = STATIC_SYMBOL("FUTURE-G2-TIME-TASKS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_future_g2_time_tasks,
	    G2int_future_g2_time_tasks);
    g2int_record_system_variable(Qg2int_future_g2_time_tasks,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    if (G2int_the_type_description_of_future_task_queue_holder == UNBOUND)
	G2int_the_type_description_of_future_task_queue_holder = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8l83py1m83py8k1l8k0000001o1m83Dy9k1m83Cy3ky1n8n83*Ty01m8p83=Uykok0k0");
    temp = G2int_the_type_description_of_future_task_queue_holder;
    g2int_clear_optimized_constants();
    g2int_push_optimized_constant(Qvector);
    G2int_the_type_description_of_future_task_queue_holder = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_2));
    Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_future_task_queue_holder_g2_struct,
	    G2int_the_type_description_of_future_task_queue_holder,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_future_task_queue_holder = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER",AB_package);
    g2int_mutate_global_property(Qg2int_future_task_queue_holder,
	    G2int_the_type_description_of_future_task_queue_holder,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_future_task_queue_holders = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FUTURE-TASK-QUEUE-HOLDERS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_future_task_queue_holders,
	    G2int_chain_of_available_future_task_queue_holders);
    g2int_record_system_variable(Qg2int_chain_of_available_future_task_queue_holders,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_future_task_queue_holder_count = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-HOLDER-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_future_task_queue_holder_count,
	    G2int_future_task_queue_holder_count);
    g2int_record_system_variable(Qg2int_future_task_queue_holder_count,
	    Qg2int_utilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    reclaim_structure_for_future_task_queue_holder = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_future_task_queue_holder,
	    NIL,FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_future_task_queue_holder,
	    reclaim_structure_for_future_task_queue_holder);
    Qg2int_system_is_running = STATIC_SYMBOL("SYSTEM-IS-RUNNING",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_system_is_running,
	    G2int_system_is_running);
    g2int_record_system_variable(Qg2int_system_is_running,Qg2int_schedule,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_system_has_paused = STATIC_SYMBOL("SYSTEM-HAS-PAUSED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_system_has_paused,
	    G2int_system_has_paused);
    g2int_record_system_variable(Qg2int_system_has_paused,Qg2int_schedule,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_system_has_aborted = STATIC_SYMBOL("SYSTEM-HAS-ABORTED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_system_has_aborted,
	    G2int_system_has_aborted);
    g2int_record_system_variable(Qg2int_system_has_aborted,Qg2int_schedule,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_abort = STATIC_SYMBOL("ABORT",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_abort,STATIC_FUNCTION(g2int_abort,NIL,TRUE,
	    0,1));
    Qg2int_running = STATIC_SYMBOL("RUNNING",AB_package);
    Qg2int_paused = STATIC_SYMBOL("PAUSED",AB_package);
    Qg2int_reset = STATIC_SYMBOL("RESET",AB_package);
    Qg2int_current_schedule_task = STATIC_SYMBOL("CURRENT-SCHEDULE-TASK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_current_schedule_task,
	    G2int_current_schedule_task);
    g2int_record_system_variable(Qg2int_current_schedule_task,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_priority_of_current_task = 
	    STATIC_SYMBOL("PRIORITY-OF-CURRENT-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_priority_of_current_task,
	    G2int_priority_of_current_task);
    Qg2int_clocks = STATIC_SYMBOL("CLOCKS",AB_package);
    g2int_record_system_variable(Qg2int_priority_of_current_task,
	    Qg2int_clocks,FIX((SI_Long)-1L),Qnil,Qnil,Qnil,Qnil);
    Qg2int_priority_of_next_task = STATIC_SYMBOL("PRIORITY-OF-NEXT-TASK",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_priority_of_next_task,
	    G2int_priority_of_next_task);
    g2int_record_system_variable(Qg2int_priority_of_next_task,
	    Qg2int_clocks,Qmost_positive_fixnum,Qnil,Qnil,Qnil,Qnil);
    Qg2int_future_task_queue_marker = 
	    STATIC_SYMBOL("FUTURE-TASK-QUEUE-MARKER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_future_task_queue_marker,
	    G2int_future_task_queue_marker);
    list_constant = STATIC_CONS(Qg2int_future_task_queue_marker,Qnil);
    SET_SYMBOL_VALUE(Qg2int_future_task_queue_marker,list_constant);
    Qg2int_real_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    Qg2int_scheduler_has_been_initialized_p = 
	    STATIC_SYMBOL("SCHEDULER-HAS-BEEN-INITIALIZED-P",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_scheduler_has_been_initialized_p,
	    G2int_scheduler_has_been_initialized_p);
    g2int_record_system_variable(Qg2int_scheduler_has_been_initialized_p,
	    Qg2int_schedule,Nil,Qnil,Qnil,Qnil,Qnil);
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_mqtt_poll_watcher = STATIC_SYMBOL("MQTT-POLL-WATCHER",AB_package);
    Qg2int_clear_g2_schedule = STATIC_SYMBOL("CLEAR-G2-SCHEDULE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2int_clear_g2_schedule,
	    STATIC_FUNCTION(g2int_clear_g2_schedule,NIL,FALSE,0,0));
    if (G2int_time_slice_start_time == UNBOUND)
	G2int_time_slice_start_time = FIX((SI_Long)0L);
    Qg2int_maximum_time_slice_size = 
	    STATIC_SYMBOL("MAXIMUM-TIME-SLICE-SIZE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_maximum_time_slice_size,
	    G2int_maximum_time_slice_size);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qg2int_fixnum_time_interval = STATIC_SYMBOL("FIXNUM-TIME-INTERVAL",
	    AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qg2int_fixnum_time_interval,FIX((SI_Long)50L));
    g2int_record_system_variable(Qg2int_maximum_time_slice_size,
	    Qg2int_clocks,list_constant_1,Qnil,Qnil,Qnil,Qnil);
    float_constant = STATIC_FLOAT(0.0);
    string_constant = 
	    STATIC_STRING("Time Cyclic G2-Running\? Priority Function-and-Args");
    if (G2int_gsi_maximum_idle_interval == UNBOUND)
	G2int_gsi_maximum_idle_interval = FIX((SI_Long)1000L);
}
