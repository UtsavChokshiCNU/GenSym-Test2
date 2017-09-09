/* cmds1.c
 * Input file:  commands1.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cmds1.h"


static Object Qstart;              /* start */

/* COM-START */
Object com_start()
{
    x_note_fn_call(225,0);
    if ( !EQ(Unevaluated_expression,Within_side_limits) &&  
	    !(System_is_running || System_has_paused))
	return system_state_change_from_scheduler(Qstart);
    else
	return VALUES_1(Nil);
}

/* START-COMMAND-TRANSLATOR */
Object start_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,1);
    if ( !EQ(Unevaluated_expression,Within_side_limits) &&  
	    !(System_is_running || System_has_paused))
	return make_partial_command(Qstart,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qlogged_in;          /* logged-in */

static Object Qpause;              /* pause */

/* COM-PAUSE */
Object com_pause()
{
    x_note_fn_call(225,2);
    if (System_is_running &&  !TRUEP(System_has_paused) && 
	    Current_workstation && EQ(ISVREF(Current_workstation,
	    (SI_Long)28L),Qlogged_in))
	return system_state_change_from_scheduler(Qpause);
    else
	return VALUES_1(Nil);
}

/* PAUSE-COMMAND-TRANSLATOR */
Object pause_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,3);
    if (System_is_running &&  !TRUEP(System_has_paused) && 
	    Current_workstation && EQ(ISVREF(Current_workstation,
	    (SI_Long)28L),Qlogged_in))
	return make_partial_command(Qpause,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qresume;             /* resume */

/* COM-RESUME */
Object com_resume()
{
    x_note_fn_call(225,4);
    if (System_has_paused &&  !EQ(Unevaluated_expression,
	    Within_side_limits) &&  !TRUEP(Inside_breakpoint_p))
	return system_state_change_from_scheduler(Qresume);
    else
	return VALUES_1(Nil);
}

/* RESUME-COMMAND-TRANSLATOR */
Object resume_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,5);
    if (System_has_paused &&  !EQ(Unevaluated_expression,
	    Within_side_limits) &&  !TRUEP(Inside_breakpoint_p))
	return make_partial_command(Qresume,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "Continue from the point of the breakpoint." */

/* COM-CONTINUE-FROM-BREAKPOINT */
Object com_continue_from_breakpoint()
{
    x_note_fn_call(225,6);
    if (System_has_paused &&  !EQ(Unevaluated_expression,
	    Within_side_limits) && Inside_breakpoint_p) {
	notify_user(1,string_constant);
	return return_from_breakpoint(0);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcontinue_from_breakpoint;  /* continue-from-breakpoint */

/* CONTINUE-FROM-BREAKPOINT-COMMAND-TRANSLATOR */
Object continue_from_breakpoint_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,7);
    if (System_has_paused &&  !EQ(Unevaluated_expression,
	    Within_side_limits) && Inside_breakpoint_p)
	return make_partial_command(Qcontinue_from_breakpoint,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_1;   /* "Cannot ~A because G2 is in a breakpoint.  ~
				    *                 Exit the breakpoint first, with resume."
				    */

/* NOTIFY-USER-OF-BREAKPOINT */
Object notify_user_of_breakpoint(attempted_command)
    Object attempted_command;
{
    x_note_fn_call(225,8);
    notify_user(2,string_constant_1,attempted_command);
    return VALUES_1(Nil);
}

static Object Qreset;              /* reset */

/* COM-RESET */
Object com_reset()
{
    x_note_fn_call(225,9);
    if ((System_has_paused || System_is_running) &&  
	    !TRUEP(Inside_breakpoint_p))
	return system_state_change_from_scheduler(Qreset);
    else
	return VALUES_1(Nil);
}

/* RESET-COMMAND-TRANSLATOR */
Object reset_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,10);
    if ((System_has_paused || System_is_running) &&  
	    !TRUEP(Inside_breakpoint_p))
	return make_partial_command(Qreset,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qab_restart;         /* restart */

/* COM-RESTART */
Object com_restart()
{
    x_note_fn_call(225,11);
    if ((System_is_running || System_has_paused) &&  
	    !EQ(Unevaluated_expression,Within_side_limits) &&  
	    !TRUEP(Inside_breakpoint_p))
	return system_state_change_from_scheduler(Qab_restart);
    else
	return VALUES_1(Nil);
}

/* RESTART-COMMAND-TRANSLATOR */
Object restart_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,12);
    if ((System_is_running || System_has_paused) &&  
	    !EQ(Unevaluated_expression,Within_side_limits) &&  
	    !TRUEP(Inside_breakpoint_p))
	return make_partial_command(Qab_restart,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qclear_kb;           /* clear-kb */

static Object string_constant_2;   /* "Do you really want to ~(~A~) G2?" */

static Object Qsystem_state_change_from_scheduler_1;  /* system-state-change-from-scheduler-1 */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* SYSTEM-STATE-CHANGE-FROM-SCHEDULER */
Object system_state_change_from_scheduler(action)
    Object action;
{
    Object temp, structure_being_reclaimed, temp_1, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(1);

    x_note_fn_call(225,13);
    if (confirm_run_state_changes_p() &&  !EQ(action,Qclear_kb) && 
	    BOUNDP(Qcurrent_workstation)) {
	temp = tformat_text_string(2,string_constant_2,action);
	return confirm_or_cancel(3,temp,
		SYMBOL_FUNCTION(Qsystem_state_change_from_scheduler_1),
		slot_value_cons_1(action,Nil));
    }
    else {
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
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(Nil,FIX((SI_Long)0L)) = temp_1;
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = Nil;
	}
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp_1 = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp_1,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = T;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	new_task = def_structure_schedule_task_variable;
	SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	SVREF(new_task,FIX((SI_Long)7L)) = 
		Qsystem_state_change_from_scheduler_1;
	temp_1 = SYMBOL_FUNCTION(Qsystem_state_change_from_scheduler_1);
	SVREF(new_task,FIX((SI_Long)8L)) = temp_1;
	ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(new_task,FIX((SI_Long)13L)) = action;
	temp_1 = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	SVREF(new_task,FIX((SI_Long)11L)) = temp_1;
	temp_1 = 
		constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		(SI_Long)0L),new_task);
	SVREF(new_task,FIX((SI_Long)6L)) = temp_1;
	return VALUES_1(new_task);
    }
}

static Object string_constant_3;   /* "Resetting KB to beginning. You may start when ready." */

static Object string_constant_4;   /* "Resetting KB to beginning and restarting it." */

static Object string_constant_5;   /* "Resuming running of KB from where it last paused." */

static Object string_constant_6;   /* "Pause while running KB. You may resume, reset, or restart." */

static Object string_constant_7;   /* "Starting to run KB. You may pause, reset, or restart at any time." */

/* SYSTEM-STATE-CHANGE-FROM-SCHEDULER-1 */
Object system_state_change_from_scheduler_1(action)
    Object action;
{
    x_note_fn_call(225,14);
    if (EQ(action,Qreset)) {
	notify_user(1,string_constant_3);
	return system_reset();
    }
    else if (EQ(action,Qab_restart)) {
	notify_user(1,string_constant_4);
	return system_restart();
    }
    else if (EQ(action,Qresume)) {
	notify_user(1,string_constant_5);
	return system_resume();
    }
    else if (EQ(action,Qpause)) {
	notify_user(1,string_constant_6);
	return system_pause(0);
    }
    else if (EQ(action,Qstart)) {
	notify_user(1,string_constant_7);
	return system_start();
    }
    else if (EQ(action,Qclear_kb))
	return clear_kb(0);
    else
	return VALUES_1(Qnil);
}

static Object Qg2_window;          /* g2-window */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qkb_workspace_initial_width;  /* kb-workspace-initial-width */

static Object Qkb_workspace_initial_height;  /* kb-workspace-initial-height */

static Object Qmodule_this_is_part_of_qm;  /* module-this-is-part-of? */

/* COM-NEW-WORKSPACE */
Object com_new_workspace(class_1,g2_window)
    Object class_1, g2_window;
{
    Object expiration_qm, temp_1, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash, gensymed_symbol, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, temp_3, temp_4;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(225,15);
    if (of_class_p_function(g2_window,Qg2_window)) {
	if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	    expiration_qm = FOURTH(End_of_recovery_list);
	    temp = expiration_qm && FIXNUMP(expiration_qm) ? 
		    FIXNUM_GE(expiration_qm,get_universal_date()) : TRUEP(T);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (EQ(class_1,Qkb_workspace))
	    temp_1 = make_new_top_level_kb_workspace(1,Qkb_workspace);
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
		gensymed_symbol = class_1;
		temp_2 = Symbol_properties_table;
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
		gensymed_symbol = set_skip_list_entry(temp_2,
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
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp_1);
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_1);
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_2,temp_1);
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
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    ISVREF(get_slot_description_of_class_description_function(Qkb_workspace_initial_width,
		    gensymed_symbol,Nil),(SI_Long)6L);
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
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
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
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
		gensymed_symbol = class_1;
		temp_3 = Symbol_properties_table;
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
		gensymed_symbol = set_skip_list_entry(temp_3,
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
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_3 = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_3,temp_1);
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
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
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
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_3 = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_3,temp_1);
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
	    temp_1 = 
		    ISVREF(get_slot_description_of_class_description_function(Qkb_workspace_initial_height,
		    gensymed_symbol,Nil),(SI_Long)6L);
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_24:
	    if (level < ab_loop_bind_)
		goto end_loop_24;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_25:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_3);
	    MVS_2(result,succ,marked);
	  next_loop_26:
	    if ( !TRUEP(marked))
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_3);
	    MVS_2(result,succ,marked);
	    goto next_loop_26;
	  end_loop_25:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_25;
	  end_loop_26:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_24;
	  end_loop_24:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_1;
		temp_4 = Symbol_properties_table;
		temp_3 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_skip_list_entry(temp_4,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_3,
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
	  next_loop_27:
	    if (level < ab_loop_bind_)
		goto end_loop_27;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_28:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_3);
	    MVS_2(result,succ,marked);
	  next_loop_29:
	    if ( !TRUEP(marked))
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_4 = ATOMIC_REF_OBJECT(reference);
	    temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_4,temp_3);
	    MVS_2(result,succ,marked);
	    goto next_loop_29;
	  end_loop_28:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_10;
	    goto next_loop_28;
	  end_loop_29:
	  end_10:
	    level = level - (SI_Long)1L;
	    goto next_loop_27;
	  end_loop_27:;
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
	      next_loop_30:
		if (level < ab_loop_bind_)
		    goto end_loop_30;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_31:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_3);
		MVS_2(result,succ,marked);
		goto next_loop_32;
	      end_loop_31:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_31;
	      end_loop_32:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_30;
	      end_loop_30:;
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
	      next_loop_33:
		if (level < ab_loop_bind_)
		    goto end_loop_33;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_34:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_3);
		MVS_2(result,succ,marked);
	      next_loop_35:
		if ( !TRUEP(marked))
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_4 = ATOMIC_REF_OBJECT(reference);
		temp_3 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_4,temp_3);
		MVS_2(result,succ,marked);
		goto next_loop_35;
	      end_loop_34:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_12;
		goto next_loop_34;
	      end_loop_35:
	      end_12:
		level = level - (SI_Long)1L;
		goto next_loop_33;
	      end_loop_33:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_1 = make_new_top_level_kb_workspace(7,class_1,Nil,Nil,Nil,
		    temp_2,temp_1,
		    ISVREF(get_slot_description_of_class_description_function(Qmodule_this_is_part_of_qm,
		    gensymed_symbol,Nil),(SI_Long)6L));
	}
	return show_or_hide(5,temp_1,T,Nil,g2_window,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qab_class;           /* class */

static Object Qclass_of_workspace;  /* class-of-workspace */

/* NEW-WORKSPACE-COMMAND-PURSUER */
Object new_workspace_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, class_1, g2_window;

    x_note_fn_call(225,16);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    class_1 = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window = CAR(gensymed_symbol);
    class_1 = command_argument_value(class_1);
    g2_window = command_argument_value(g2_window);
    if (EQ(class_1,Plus_missing_argument_plus))
	return VALUES_3(Qab_class,Qclass_of_workspace,FIX((SI_Long)0L));
    else if (EQ(g2_window,Plus_missing_argument_plus))
	return VALUES_3(Qg2_window,Qg2_window,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qnew_workspace;      /* new-workspace */

/* NEW-WORKSPACE-COMMAND-TRANSLATOR */
Object new_workspace_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object g2_window, expiration_qm, temp_1, temp_2;
    char temp;

    x_note_fn_call(225,17);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (g2_window) {
	if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	    expiration_qm = FOURTH(End_of_recovery_list);
	    temp = expiration_qm && FIXNUMP(expiration_qm) ? 
		    FIXNUM_GE(expiration_qm,get_universal_date()) : TRUEP(T);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = snapshot_command_argument(Plus_missing_argument_plus);
	    temp_2 = g2_window;
	    if (temp_2);
	    else
		temp_2 = Plus_missing_argument_plus;
	    return make_partial_command(Qnew_workspace,
		    slot_value_list_2(temp_1,
		    snapshot_command_argument(temp_2)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-GET-WORKSPACE */
Object com_get_workspace(workspace)
    Object workspace;
{
    x_note_fn_call(225,18);
    if (named_kb_workspace_tester_function(workspace))
	return goto_frame_instance(workspace);
    else
	return VALUES_1(Nil);
}

static Object Qworkspace;          /* workspace */

static Object Qnamed_kb_workspace;  /* named-kb-workspace */

/* GET-WORKSPACE-COMMAND-PURSUER */
Object get_workspace_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, workspace;

    x_note_fn_call(225,19);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    workspace = CAR(gensymed_symbol);
    workspace = command_argument_value(workspace);
    if (EQ(workspace,Plus_missing_argument_plus))
	return VALUES_3(Qworkspace,Qnamed_kb_workspace,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qget_workspace;      /* get-workspace */

/* GET-WORKSPACE-COMMAND-TRANSLATOR */
Object get_workspace_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,20);
    if (named_workspaces_exist_p())
	return make_partial_command(Qget_workspace,
		slot_value_cons_1(snapshot_command_argument(Plus_missing_argument_plus),
		Nil));
    else
	return VALUES_1(Nil);
}

/* INSPECT-PERMITTED-P */
Object inspect_permitted_p()
{
    Object code, temp_1;
    char temp;

    x_note_fn_call(225,21);
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
    temp_1 =  !temp ? T : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(Override_limited_license_block_on_inspect_qm);
}

static Object Qinspect_command;    /* inspect-command */

/* COM-INSPECT */
Object com_inspect()
{
    x_note_fn_call(225,22);
    if (inspect_permitted_p())
	return handle_command(Qinspect_command,Nil);
    else
	return VALUES_1(Nil);
}

/* INSPECT-COMMAND-TRANSLATOR */
Object inspect_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,23);
    if (inspect_permitted_p())
	return make_partial_command(Qinspect,Nil);
    else
	return VALUES_1(Nil);
}

/* LOAD-KB-PERMITTED-P */
Object load_kb_permitted_p()
{
    x_note_fn_call(225,24);
    return VALUES_1( !(System_is_running || Inside_breakpoint_p) ? T : Nil);
}

static Object Qload_kb;            /* load-kb */

/* COM-LOAD-KB */
Object com_load_kb()
{
    x_note_fn_call(225,25);
    if (load_kb_permitted_p())
	return handle_file_related_window_menu_choice(Qload_kb);
    else
	return VALUES_1(Nil);
}

/* LOAD-KB-COMMAND-TRANSLATOR */
Object load_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,26);
    if (load_kb_permitted_p())
	return make_partial_command(Qload_kb,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qmerge_kb;           /* merge-kb */

/* COM-MERGE-KB */
Object com_merge_kb()
{
    x_note_fn_call(225,27);
    if (load_kb_permitted_p())
	return handle_file_related_window_menu_choice(Qmerge_kb);
    else
	return VALUES_1(Nil);
}

/* MERGE-KB-COMMAND-TRANSLATOR */
Object merge_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,28);
    if (load_kb_permitted_p())
	return make_partial_command(Qmerge_kb,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-LOAD-RECENT-KB */
Object com_load_recent_kb(pathname_1)
    Object pathname_1;
{
    Object default_kb_pathname_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(225,29);
    if (recent_loaded_kb_tester_function(pathname_1)) {
	default_kb_pathname_qm = pathname_1;
	PUSH_SPECIAL_WITH_SYMBOL(Default_kb_pathname_qm,Qdefault_kb_pathname_qm,default_kb_pathname_qm,
		0);
	  result = handle_file_related_window_menu_choice(Qload_kb);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qab_pathname;        /* pathname */

static Object Qrecent_loaded_kb;   /* recent-loaded-kb */

/* LOAD-RECENT-KB-COMMAND-PURSUER */
Object load_recent_kb_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, pathname_1;

    x_note_fn_call(225,30);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    pathname_1 = CAR(gensymed_symbol);
    pathname_1 = command_argument_value(pathname_1);
    if (EQ(pathname_1,Plus_missing_argument_plus))
	return VALUES_3(Qab_pathname,Qrecent_loaded_kb,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qload_recent_kb;     /* load-recent-kb */

/* LOAD-RECENT-KB-COMMAND-TRANSLATOR */
Object load_recent_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,31);
    if (recent_loaded_kb_available_p())
	return make_partial_command(Qload_recent_kb,
		slot_value_cons_1(snapshot_command_argument(Plus_missing_argument_plus),
		Nil));
    else
	return VALUES_1(Nil);
}

/* SAVE-KB-PERMITTED-P */
Object save_kb_permitted_p()
{
    Object code;
    char temp;

    x_note_fn_call(225,32);
    if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
	if (temp);
	else {
	    code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		    (SI_Long)0L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = 
			TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
	}
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsave_kb;            /* save-kb */

/* COM-SAVE-KB */
Object com_save_kb()
{
    x_note_fn_call(225,33);
    if (save_kb_permitted_p())
	return handle_file_related_window_menu_choice(Qsave_kb);
    else
	return VALUES_1(Nil);
}

/* SAVE-KB-COMMAND-TRANSLATOR */
Object save_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,34);
    if (save_kb_permitted_p())
	return make_partial_command(Qsave_kb,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qkb_save;            /* kb-save */

/* COM-SAVE-KB-WITHOUT-ASKING */
Object com_save_kb_without_asking()
{
    x_note_fn_call(225,35);
    if (save_kb_permitted_p()) {
	if (Current_kb_pathname_qm)
	    return save_kb(2,get_or_make_default_kb_pathname(0),Qkb_save);
	else
	    return handle_file_related_window_menu_choice(Qsave_kb);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsave_kb_without_asking;  /* save-kb-without-asking */

/* SAVE-KB-WITHOUT-ASKING-COMMAND-TRANSLATOR */
Object save_kb_without_asking_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,36);
    if (save_kb_permitted_p())
	return make_partial_command(Qsave_kb_without_asking,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-SHOW-SYSTEM-TABLE */
Object com_show_system_table(system_table,original_x_in_window,
	    original_y_in_window)
    Object system_table, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(225,37);
    if (system_table_tester_function(system_table) && original_x_in_window 
	    && original_y_in_window)
	return put_up_attributes_table(3,system_table,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

static Object Qsystem_table;       /* system-table */

static Object Qoriginal_x_in_window;  /* original-x-in-window */

static Object Qoriginal_y_in_window;  /* original-y-in-window */

/* SHOW-SYSTEM-TABLE-COMMAND-PURSUER */
Object show_system_table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, system_table, original_x_in_window;
    Object original_y_in_window;

    x_note_fn_call(225,38);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    system_table = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    system_table = command_argument_value(system_table);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(system_table,Plus_missing_argument_plus))
	return VALUES_3(Qsystem_table,Qsystem_table,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qshow_system_table;  /* show-system-table */

/* SHOW-SYSTEM-TABLE-COMMAND-TRANSLATOR */
Object show_system_table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object original_x_in_window, original_y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,39);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (original_x_in_window && original_y_in_window) {
	if (T) {
	    temp = snapshot_command_argument(Plus_missing_argument_plus);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qshow_system_table,
		    slot_value_list_3(temp,temp_2,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_gensym_window_g2_struct;  /* g2-defstruct-structure-name::gensym-window-g2-struct */

/* COM-PRINTER-SETUP */
Object com_printer_setup(window)
    Object window;
{
    SI_Long x;

    x_note_fn_call(225,40);
    if (SIMPLE_VECTOR_P(window) && EQ(ISVREF(window,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_window_g2_struct)) {
	x = IFIX(FIXNUM_ADD(ISVREF(window,(SI_Long)7L),ISVREF(window,
		(SI_Long)9L))) >>  -  - (SI_Long)1L;
	return put_up_attributes_table(3,Printer_setup,FIX(x),
		FIX((SI_Long)0L));
    }
    else
	return VALUES_1(Nil);
}

static Object Qwindow;             /* window */

/* PRINTER-SETUP-COMMAND-PURSUER */
Object printer_setup_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, window;

    x_note_fn_call(225,41);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    window = CAR(gensymed_symbol);
    window = command_argument_value(window);
    if (EQ(window,Plus_missing_argument_plus))
	return VALUES_3(Qwindow,Qwindow,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* PRINTER-SETUP-COMMAND-TRANSLATOR */
Object printer_setup_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object window, temp;

    x_note_fn_call(225,42);
    window = window_blackboard_function(mouse_pointer);
    if (window) {
	if (T) {
	    temp = window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qprinter_setup,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-CHANGE-MODE */
Object com_change_mode()
{
    x_note_fn_call(225,43);
    return change_mode();
}

static Object Qchange_mode;        /* change-mode */

/* CHANGE-MODE-COMMAND-TRANSLATOR */
Object change_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,44);
    if (T)
	return make_partial_command(Qchange_mode,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qalias_creation;     /* alias-creation */

/* COM-CREATE-NEW-USER-MODE-ALIAS */
Object com_create_new_user_mode_alias()
{
    x_note_fn_call(225,45);
    return enter_user_settings_editor(Qalias_creation);
}

static Object Qcreate_new_user_mode_alias;  /* create-new-user-mode-alias */

/* CREATE-NEW-USER-MODE-ALIAS-COMMAND-TRANSLATOR */
Object create_new_user_mode_alias_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,46);
    if (T)
	return make_partial_command(Qcreate_new_user_mode_alias,Nil);
    else
	return VALUES_1(Nil);
}

static Object Quser_mode_aliases;  /* user-mode-aliases */

/* COM-USER-MODE-ALIASES */
Object com_user_mode_aliases()
{
    x_note_fn_call(225,47);
    return put_up_aliases_table(get_lookup_slot_value_given_default(Kb_configuration,
	    Quser_mode_aliases,Nil));
}

/* USER-MODE-ALIASES-COMMAND-TRANSLATOR */
Object user_mode_aliases_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,48);
    if (T)
	return make_partial_command(Quser_mode_aliases,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qcontrol_e;          /* control-e */

/* COM-CHANGE-G2-USER-MODE */
Object com_change_g2_user_mode()
{
    x_note_fn_call(225,49);
    if ( !TRUEP(lookup_kb_specific_property_value(Qcontrol_e,
	    Frame_or_frames_with_this_name_kbprop)))
	return change_mode();
    else
	return VALUES_1(Nil);
}

static Object Qchange_g2_user_mode;  /* change-g2-user-mode */

/* CHANGE-G2-USER-MODE-COMMAND-TRANSLATOR */
Object change_g2_user_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,50);
    if ( !TRUEP(lookup_kb_specific_property_value(Qcontrol_e,
	    Frame_or_frames_with_this_name_kbprop)))
	return make_partial_command(Qchange_g2_user_mode,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-CHANGE-G2-USER-MODE-E */
Object com_change_g2_user_mode_e()
{
    x_note_fn_call(225,51);
    if (lookup_kb_specific_property_value(Qcontrol_e,
	    Frame_or_frames_with_this_name_kbprop))
	return change_mode();
    else
	return VALUES_1(Nil);
}

static Object Qchange_g2_user_mode_e;  /* change-g2-user-mode-e */

/* CHANGE-G2-USER-MODE-E-COMMAND-TRANSLATOR */
Object change_g2_user_mode_e_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,52);
    if (lookup_kb_specific_property_value(Qcontrol_e,
	    Frame_or_frames_with_this_name_kbprop))
	return make_partial_command(Qchange_g2_user_mode_e,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-CHANGE-PASSWORD */
Object com_change_password()
{
    x_note_fn_call(225,53);
    if (Relations_tag_list && ISVREF(Current_workstation,(SI_Long)20L) && 
	    ISVREF(Current_workstation,(SI_Long)21L) && 
	    G2passwdexe_is_executable_p)
	return enter_change_password_dialog();
    else
	return VALUES_1(Nil);
}

static Object Qchange_password;    /* change-password */

/* CHANGE-PASSWORD-COMMAND-TRANSLATOR */
Object change_password_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,54);
    if (Relations_tag_list && ISVREF(Current_workstation,(SI_Long)20L) && 
	    ISVREF(Current_workstation,(SI_Long)21L) && 
	    G2passwdexe_is_executable_p)
	return make_partial_command(Qchange_password,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-REINSTALL-AUTHORIZED-USERS */
Object com_reinstall_authorized_users()
{
    x_note_fn_call(225,55);
    if (Relations_tag_list && g2_ok_file_readable_p())
	return reinstall_authorized_users();
    else
	return VALUES_1(Nil);
}

static Object Qreinstall_authorized_users;  /* reinstall-authorized-users */

/* REINSTALL-AUTHORIZED-USERS-COMMAND-TRANSLATOR */
Object reinstall_authorized_users_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,56);
    if (Relations_tag_list && g2_ok_file_readable_p())
	return make_partial_command(Qreinstall_authorized_users,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-SHORT-MENUS */
Object com_short_menus()
{
    x_note_fn_call(225,57);
    if ( !TRUEP(Short_menus_qm)) {
	Short_menus_qm = T;
	return VALUES_1(Short_menus_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshort_menus;        /* short-menus */

/* SHORT-MENUS-COMMAND-TRANSLATOR */
Object short_menus_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,58);
    if ( !TRUEP(Short_menus_qm))
	return make_partial_command(Qshort_menus,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-LONG-MENUS */
Object com_long_menus()
{
    x_note_fn_call(225,59);
    if (Short_menus_qm) {
	Short_menus_qm = Nil;
	return VALUES_1(Short_menus_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qlong_menus;         /* long-menus */

/* LONG-MENUS-COMMAND-TRANSLATOR */
Object long_menus_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,60);
    if (Short_menus_qm)
	return make_partial_command(Qlong_menus,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-NEATLY-STACK-WINDOWS */
Object com_neatly_stack_windows(window)
    Object window;
{
    x_note_fn_call(225,61);
    if (SIMPLE_VECTOR_P(window) && EQ(ISVREF(window,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_window_g2_struct) && window)
	return neatly_stack_image_planes_in_window(window);
    else
	return VALUES_1(Nil);
}

/* NEATLY-STACK-WINDOWS-COMMAND-PURSUER */
Object neatly_stack_windows_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, window;

    x_note_fn_call(225,62);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    window = CAR(gensymed_symbol);
    window = command_argument_value(window);
    if (EQ(window,Plus_missing_argument_plus))
	return VALUES_3(Qwindow,Qwindow,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qneatly_stack_windows;  /* neatly-stack-windows */

/* NEATLY-STACK-WINDOWS-COMMAND-TRANSLATOR */
Object neatly_stack_windows_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object window, temp;

    x_note_fn_call(225,63);
    window = window_blackboard_function(mouse_pointer);
    if (window) {
	if (window) {
	    temp = window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qneatly_stack_windows,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qconnect_to_foreign_image;  /* connect-to-foreign-image */

/* COM-CONNECT-TO-FOREIGN-IMAGE */
Object com_connect_to_foreign_image()
{
    x_note_fn_call(225,64);
    if ( !TRUEP(System_is_running))
	return handle_file_related_window_menu_choice(Qconnect_to_foreign_image);
    else
	return VALUES_1(Nil);
}

/* CONNECT-TO-FOREIGN-IMAGE-COMMAND-TRANSLATOR */
Object connect_to_foreign_image_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,65);
    if ( !TRUEP(System_is_running))
	return make_partial_command(Qconnect_to_foreign_image,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qdisconnect_from_foreign_image;  /* disconnect-from-foreign-image */

/* COM-DISCONNECT-FROM-FOREIGN-IMAGE */
Object com_disconnect_from_foreign_image()
{
    x_note_fn_call(225,66);
    if ( !TRUEP(System_is_running))
	return handle_file_related_window_menu_choice(Qdisconnect_from_foreign_image);
    else
	return VALUES_1(Nil);
}

/* DISCONNECT-FROM-FOREIGN-IMAGE-COMMAND-TRANSLATOR */
Object disconnect_from_foreign_image_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,67);
    if ( !TRUEP(System_is_running))
	return make_partial_command(Qdisconnect_from_foreign_image,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qload_attribute_file;  /* load-attribute-file */

/* COM-LOAD-ATTRIBUTE-FILE */
Object com_load_attribute_file()
{
    x_note_fn_call(225,68);
    if ( !TRUEP(System_is_running))
	return handle_file_related_window_menu_choice(Qload_attribute_file);
    else
	return VALUES_1(Nil);
}

/* LOAD-ATTRIBUTE-FILE-COMMAND-TRANSLATOR */
Object load_attribute_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,69);
    if ( !TRUEP(System_is_running))
	return make_partial_command(Qload_attribute_file,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qwrite_g2_stats;     /* write-g2-stats */

/* COM-WRITE-G2-STATS */
Object com_write_g2_stats()
{
    x_note_fn_call(225,70);
    return handle_file_related_window_menu_choice(Qwrite_g2_stats);
}

/* WRITE-G2-STATS-COMMAND-TRANSLATOR */
Object write_g2_stats_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,71);
    if (T)
	return make_partial_command(Qwrite_g2_stats,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qhighlight_invoked_rules_mode;  /* highlight-invoked-rules-mode */

/* COM-HIGHLIGHT-INVOKED-RULES */
Object com_highlight_invoked_rules()
{
    x_note_fn_call(225,72);
    if ( !TRUEP(get_lookup_slot_value_given_default(Debugging_parameters,
	    Qhighlight_invoked_rules_mode,Nil)))
	return change_slot_value(3,Debugging_parameters,
		Qhighlight_invoked_rules_mode,T);
    else
	return VALUES_1(Nil);
}

static Object Qhighlight_invoked_rules;  /* highlight-invoked-rules */

/* HIGHLIGHT-INVOKED-RULES-COMMAND-TRANSLATOR */
Object highlight_invoked_rules_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,73);
    if ( !TRUEP(get_lookup_slot_value_given_default(Debugging_parameters,
	    Qhighlight_invoked_rules_mode,Nil)))
	return make_partial_command(Qhighlight_invoked_rules,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-DO-NOT-HIGHLIGHT-INVOKED-RULES */
Object com_do_not_highlight_invoked_rules()
{
    x_note_fn_call(225,74);
    if (get_lookup_slot_value_given_default(Debugging_parameters,
	    Qhighlight_invoked_rules_mode,Nil))
	return change_slot_value(3,Debugging_parameters,
		Qhighlight_invoked_rules_mode,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qdo_not_highlight_invoked_rules;  /* do-not-highlight-invoked-rules */

/* DO-NOT-HIGHLIGHT-INVOKED-RULES-COMMAND-TRANSLATOR */
Object do_not_highlight_invoked_rules_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,75);
    if (get_lookup_slot_value_given_default(Debugging_parameters,
	    Qhighlight_invoked_rules_mode,Nil))
	return make_partial_command(Qdo_not_highlight_invoked_rules,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-ENABLE-ALL-ITEMS */
Object com_enable_all_items()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, frame, gensymed_symbol;
    Object gensymed_symbol_1;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(225,76);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    frame = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qblock);
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
      frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(frame,(SI_Long)4L)) & (SI_Long)8192L)) {
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)48L),(SI_Long)1L);
	  gensymed_symbol_1 = frame;
	  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qenable_all_items;   /* enable-all-items */

/* ENABLE-ALL-ITEMS-COMMAND-TRANSLATOR */
Object enable_all_items_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,77);
    if (T)
	return make_partial_command(Qenable_all_items,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-REMOVE-TRACING-AND-BREAKPOINTS */
Object com_remove_tracing_and_breakpoints()
{
    x_note_fn_call(225,78);
    return remove_tracing_and_breakpoints();
}

static Object Qremove_tracing_and_breakpoints;  /* remove-tracing-and-breakpoints */

/* REMOVE-TRACING-AND-BREAKPOINTS-COMMAND-TRANSLATOR */
Object remove_tracing_and_breakpoints_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,79);
    if (T)
	return make_partial_command(Qremove_tracing_and_breakpoints,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsource_code_control_update_file;  /* source-code-control-update-file */

/* COM-UPDATE-FILE */
Object com_update_file()
{
    x_note_fn_call(225,80);
    return handle_file_related_window_menu_choice(Qsource_code_control_update_file);
}

static Object Qupdate_file;        /* update-file */

/* UPDATE-FILE-COMMAND-TRANSLATOR */
Object update_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,81);
    if (T)
	return make_partial_command(Qupdate_file,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsource_code_control_edit_file;  /* source-code-control-edit-file */

/* COM-EDIT-FILE */
Object com_edit_file()
{
    x_note_fn_call(225,82);
    return handle_file_related_window_menu_choice(Qsource_code_control_edit_file);
}

static Object Qedit_file;          /* edit-file */

/* EDIT-FILE-COMMAND-TRANSLATOR */
Object edit_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,83);
    if (T)
	return make_partial_command(Qedit_file,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsource_code_control_unedit_file;  /* source-code-control-unedit-file */

/* COM-UNEDIT-FILE */
Object com_unedit_file()
{
    x_note_fn_call(225,84);
    return handle_file_related_window_menu_choice(Qsource_code_control_unedit_file);
}

static Object Qunedit_file;        /* unedit-file */

/* UNEDIT-FILE-COMMAND-TRANSLATOR */
Object unedit_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,85);
    if (T)
	return make_partial_command(Qunedit_file,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsource_code_control_commit_file;  /* source-code-control-commit-file */

/* COM-COMMIT-FILE */
Object com_commit_file()
{
    x_note_fn_call(225,86);
    return handle_file_related_window_menu_choice(Qsource_code_control_commit_file);
}

static Object Qcommit_file;        /* commit-file */

/* COMMIT-FILE-COMMAND-TRANSLATOR */
Object commit_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,87);
    if (T)
	return make_partial_command(Qcommit_file,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsource_code_control_revert_file;  /* source-code-control-revert-file */

/* COM-REVERT-FILE */
Object com_revert_file()
{
    x_note_fn_call(225,88);
    return handle_file_related_window_menu_choice(Qsource_code_control_revert_file);
}

static Object Qrevert_file;        /* revert-file */

/* REVERT-FILE-COMMAND-TRANSLATOR */
Object revert_file_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,89);
    if (T)
	return make_partial_command(Qrevert_file,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-CREATE-NEW-MODULE */
Object com_create_new_module(original_x_in_window,original_y_in_window)
    Object original_x_in_window, original_y_in_window;
{
    x_note_fn_call(225,90);
    if (original_x_in_window && original_y_in_window)
	return handle_create_new_module_window_menu_choice(original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* CREATE-NEW-MODULE-COMMAND-PURSUER */
Object create_new_module_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,91);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)0L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qcreate_new_module;  /* create-new-module */

/* CREATE-NEW-MODULE-COMMAND-TRANSLATOR */
Object create_new_module_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object original_x_in_window, original_y_in_window, temp, temp_1;

    x_note_fn_call(225,92);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (original_x_in_window && original_y_in_window) {
	if (T) {
	    temp = original_x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = original_y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcreate_new_module,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_8;   /* "Delete ~amodule ~a? (Choose `All' to delete all associated workspaces as well.)" */

static Object string_constant_9;   /* "the TOP-LEVEL " */

static Object string_constant_10;  /* "" */

static Object string_constant_11;  /* "All" */

static Object Qdo_deletion_of_module_after_confirmation;  /* do-deletion-of-module-after-confirmation */

/* COM-DELETE-MODULE */
Object com_delete_module(module)
    Object module;
{
    Object system_table_suite_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(225,93);
    if (kb_has_modularity_information_p() &&  !TRUEP(Inside_breakpoint_p)) {
	system_table_suite_qm = 
		get_system_table_suite_for_module_or_nil(module);
	if (system_table_suite_qm) {
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
		      tformat(3,string_constant_8,
			      system_table_installed_p(CAR(system_table_suite_qm)) 
			      ? string_constant_9 : string_constant_10,module);
		      tformat_warning_about_modules_that_require_this_if_necessary(module);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_1 = slot_value_list_2(module,Nil);
	    temp_2 = tformat_text_string(1,string_constant_11);
	    return enter_dialog(12,temp,Nil,Nil,
		    Qdo_deletion_of_module_after_confirmation,temp_1,Nil,
		    Nil,Nil,Nil,temp_2,
		    Qdo_deletion_of_module_after_confirmation,
		    slot_value_list_2(module,T));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmodule;             /* module */

static Object Qdeletable_module;   /* deletable-module */

/* DELETE-MODULE-COMMAND-PURSUER */
Object delete_module_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, module;

    x_note_fn_call(225,94);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    module = CAR(gensymed_symbol);
    module = command_argument_value(module);
    if (EQ(module,Plus_missing_argument_plus))
	return VALUES_3(Qmodule,Qdeletable_module,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qdelete_module;      /* delete-module */

/* DELETE-MODULE-COMMAND-TRANSLATOR */
Object delete_module_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,95);
    if (kb_has_modularity_information_p() &&  !TRUEP(Inside_breakpoint_p))
	return make_partial_command(Qdelete_module,
		slot_value_cons_1(snapshot_command_argument(Plus_missing_argument_plus),
		Nil));
    else
	return VALUES_1(Nil);
}

/* COM-NEW-TITLE-BLOCK */
Object com_new_title_block()
{
    x_note_fn_call(225,96);
    return display_credits(1,Current_workstation);
}

static Object Qnew_title_block;    /* new-title-block */

/* NEW-TITLE-BLOCK-COMMAND-TRANSLATOR */
Object new_title_block_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,97);
    if (T)
	return make_partial_command(Qnew_title_block,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_12;  /* "Completely shut down G2?" */

static Object Qcompletely_shut_down_g2;  /* completely-shut-down-g2 */

static Object Qrequested;          /* requested */

/* COM-SHUT-DOWN-G2 */
Object com_shut_down_g2()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(225,98);
    if ( !TRUEP(System_is_running) || System_has_paused) {
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
		  twrite_changed_modules_note();
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return confirm_or_cancel(3,temp,
		SYMBOL_FUNCTION(Qcompletely_shut_down_g2),
		slot_value_cons_1(Qrequested,Nil));
    }
    else
	return VALUES_1(Nil);
}

static Object Qshut_down_g2;       /* shut-down-g2 */

/* SHUT-DOWN-G2-COMMAND-TRANSLATOR */
Object shut_down_g2_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,99);
    if ( !TRUEP(System_is_running) || System_has_paused)
	return make_partial_command(Qshut_down_g2,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_13;  /* "Shutdown!" */

/* COMPLETELY-SHUT-DOWN-G2 */
Object completely_shut_down_g2 varargs_1(int, n)
{
    Object status;
    Declare_varargs_nonrelocating;

    x_note_fn_call(225,100);
    INIT_ARGS_nonrelocating();
    status = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    notify_user(1,string_constant_13);
    return shut_down_ab_process(1,status);
}

static Object string_constant_14;  /* "Clear KB? (Are you sure you want to delete every item in ~
				    *            the current KB and reinitialize system tables?)"
				    */

static Object Qsystem_state_change_from_scheduler;  /* system-state-change-from-scheduler */

/* COM-CLEAR-KB */
Object com_clear_kb()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(225,101);
    if (( !TRUEP(System_is_running) || System_has_paused) &&  
	    !TRUEP(Inside_breakpoint_p)) {
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
		  twrite_changed_modules_note();
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return confirm_or_cancel(3,temp,
		Qsystem_state_change_from_scheduler,
		slot_value_cons_1(Qclear_kb,Nil));
    }
    else
	return VALUES_1(Nil);
}

/* CLEAR-KB-COMMAND-TRANSLATOR */
Object clear_kb_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,102);
    if (( !TRUEP(System_is_running) || System_has_paused) &&  
	    !TRUEP(Inside_breakpoint_p))
	return make_partial_command(Qclear_kb,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qexplanation_related_features_enabled_qm;  /* explanation-related-features-enabled? */

/* COM-TURN-ON-ALL-EXPLANATION-CACHING */
Object com_turn_on_all_explanation_caching()
{
    x_note_fn_call(225,103);
    if (get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qexplanation_related_features_enabled_qm,Nil))
	return turn_on_explanation_caching_for_all();
    else
	return VALUES_1(Nil);
}

static Object Qturn_on_all_explanation_caching;  /* turn-on-all-explanation-caching */

/* TURN-ON-ALL-EXPLANATION-CACHING-COMMAND-TRANSLATOR */
Object turn_on_all_explanation_caching_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,104);
    if (get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qexplanation_related_features_enabled_qm,Nil))
	return make_partial_command(Qturn_on_all_explanation_caching,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-TURN-OFF-ALL-EXPLANATION-CACHING */
Object com_turn_off_all_explanation_caching()
{
    x_note_fn_call(225,105);
    if (get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qexplanation_related_features_enabled_qm,Nil))
	return turn_off_explanation_caching_for_all();
    else
	return VALUES_1(Nil);
}

static Object Qturn_off_all_explanation_caching;  /* turn-off-all-explanation-caching */

/* TURN-OFF-ALL-EXPLANATION-CACHING-COMMAND-TRANSLATOR */
Object turn_off_all_explanation_caching_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,106);
    if (get_lookup_slot_value_given_default(Miscellaneous_parameters,
	    Qexplanation_related_features_enabled_qm,Nil))
	return make_partial_command(Qturn_off_all_explanation_caching,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-NETWORK-INFO */
Object com_network_info()
{
    x_note_fn_call(225,107);
    return put_up_table_of_network_info();
}

static Object Qnetwork_info;       /* network-info */

/* NETWORK-INFO-COMMAND-TRANSLATOR */
Object network_info_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,108);
    if (T)
	return make_partial_command(Qnetwork_info,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qicp;                /* icp */

static Object string_constant_15;  /* "Close this Telewindows connection to G2?" */

static Object Qclose_telewindows_connection_1;  /* close-telewindows-connection-1 */

/* COM-CLOSE-TELEWINDOWS-CONNECTION */
Object com_close_telewindows_connection()
{
    Object temp;

    x_note_fn_call(225,109);
    if (EQ(ISVREF(Current_workstation_window,(SI_Long)1L),Qicp)) {
	temp = copy_text_string(string_constant_15);
	return confirm_or_cancel(3,temp,
		SYMBOL_FUNCTION(Qclose_telewindows_connection_1),
		slot_value_cons_1(Current_workstation_window,Nil));
    }
    else
	return VALUES_1(Nil);
}

static Object Qclose_telewindows_connection;  /* close-telewindows-connection */

/* CLOSE-TELEWINDOWS-CONNECTION-COMMAND-TRANSLATOR */
Object close_telewindows_connection_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,110);
    if (EQ(ISVREF(Current_workstation_window,(SI_Long)1L),Qicp))
	return make_partial_command(Qclose_telewindows_connection,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_16;  /* "Closing Telewindows connection!" */

/* CLOSE-TELEWINDOWS-CONNECTION-1 */
Object close_telewindows_connection_1(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(225,111);
    notify_user(1,string_constant_16);
    return close_telewindows_connection(gensym_window);
}

static Object string_constant_17;  /* "Log out? (Are you sure?)" */

static Object Qlog_out_workstation;  /* log-out-workstation */

/* COM-LOG-OUT */
Object com_log_out()
{
    Object temp;

    x_note_fn_call(225,112);
    if (Relations_tag_list) {
	temp = copy_text_string(string_constant_17);
	return confirm_or_cancel(3,temp,
		SYMBOL_FUNCTION(Qlog_out_workstation),
		slot_value_cons_1(Current_workstation,Nil));
    }
    else
	return VALUES_1(Nil);
}

static Object Qlog_out;            /* log-out */

/* LOG-OUT-COMMAND-TRANSLATOR */
Object log_out_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,113);
    if (Relations_tag_list)
	return make_partial_command(Qlog_out,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-DETECT-DEADLOCKS-FOR-UI */
Object com_detect_deadlocks_for_ui()
{
    x_note_fn_call(225,114);
    return detect_deadlocks_for_ui();
}

static Object Qdetect_deadlocks_for_ui;  /* detect-deadlocks-for-ui */

/* DETECT-DEADLOCKS-FOR-UI-COMMAND-TRANSLATOR */
Object detect_deadlocks_for_ui_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,115);
    if (T)
	return make_partial_command(Qdetect_deadlocks_for_ui,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-DETECT-AND-BREAK-DEADLOCKS-FOR-UI */
Object com_detect_and_break_deadlocks_for_ui()
{
    x_note_fn_call(225,116);
    return detect_and_break_deadlocks_for_ui();
}

static Object Qdetect_and_break_deadlocks_for_ui;  /* detect-and-break-deadlocks-for-ui */

/* DETECT-AND-BREAK-DEADLOCKS-FOR-UI-COMMAND-TRANSLATOR */
Object detect_and_break_deadlocks_for_ui_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,117);
    if (T)
	return make_partial_command(Qdetect_and_break_deadlocks_for_ui,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_18;  /* "Enter Package Preparation mode?  (This will add options to menus ~
				    *          that allow for potentially dangerous and irreversible changes to the ~
				    *          KB.)"
				    */

static Object Qenter_package_preparation_mode;  /* enter-package-preparation-mode */

/* COM-ENTER-PACKAGE-PREPARATION-MODE */
Object com_enter_package_preparation_mode()
{
    x_note_fn_call(225,118);
    if ( !TRUEP(Package_preparation_mode))
	return confirm_or_cancel(2,tformat_text_string(1,
		string_constant_18),Qenter_package_preparation_mode);
    else
	return VALUES_1(Nil);
}

/* ENTER-PACKAGE-PREPARATION-MODE-COMMAND-TRANSLATOR */
Object enter_package_preparation_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,119);
    if ( !TRUEP(Package_preparation_mode))
	return make_partial_command(Qenter_package_preparation_mode,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-LEAVE-PACKAGE-PREPARATION-MODE */
Object com_leave_package_preparation_mode()
{
    x_note_fn_call(225,120);
    if (Package_preparation_mode)
	return leave_package_preparation_mode();
    else
	return VALUES_1(Nil);
}

static Object Qleave_package_preparation_mode;  /* leave-package-preparation-mode */

/* LEAVE-PACKAGE-PREPARATION-MODE-COMMAND-TRANSLATOR */
Object leave_package_preparation_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,121);
    if (Package_preparation_mode)
	return make_partial_command(Qleave_package_preparation_mode,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_19;  /* "Strip texts now?  (This will permanently remove most of the text ~
				    *          associated with all items that have been marked to be stripped of ~
				    *          their text.  These changes will be irreversible.)"
				    */

static Object Qstrip_all_texts;    /* strip-all-texts */

/* COM-STRIP-TEXTS-NOW */
Object com_strip_texts_now()
{
    x_note_fn_call(225,122);
    if (Package_preparation_mode &&  !TRUEP(System_is_running))
	return confirm_or_cancel(2,tformat_text_string(1,
		string_constant_19),Qstrip_all_texts);
    else
	return VALUES_1(Nil);
}

static Object Qstrip_texts_now;    /* strip-texts-now */

/* STRIP-TEXTS-NOW-COMMAND-TRANSLATOR */
Object strip_texts_now_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,123);
    if (Package_preparation_mode &&  !TRUEP(System_is_running))
	return make_partial_command(Qstrip_texts_now,Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_20;  /* "Make workspaces in this KB proprietary now?  (This will cause workspaces ~
				    *          that have been given a potential proprietary package to become permanently ~
				    *          proprietary to those packages and thus severely restricted in their use.  ~
				    *          Once that has been done, this KB, or any KB that has merged in those workspaces, ~
				    *          will only be allowed to execute with special authorization codes obtained ~
				    *          through Gensym Corporation.  These changes will be irreversible.)"
				    */

static Object Qmake_proprietary_now;  /* make-proprietary-now */

/* COM-MAKE-WORKSPACES-PROPRIETARY-NOW */
Object com_make_workspaces_proprietary_now()
{
    x_note_fn_call(225,124);
    if (Package_preparation_mode &&  !TRUEP(System_is_running))
	return confirm_or_cancel(2,tformat_text_string(1,
		string_constant_20),Qmake_proprietary_now);
    else
	return VALUES_1(Nil);
}

static Object Qmake_workspaces_proprietary_now;  /* make-workspaces-proprietary-now */

/* MAKE-WORKSPACES-PROPRIETARY-NOW-COMMAND-TRANSLATOR */
Object make_workspaces_proprietary_now_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,125);
    if (Package_preparation_mode &&  !TRUEP(System_is_running))
	return make_partial_command(Qmake_workspaces_proprietary_now,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qsimulate_proprietary_mode_changed;  /* simulate-proprietary-mode-changed */

/* SET-SIMULATE-PROPRIETARY-MODE */
Object set_simulate_proprietary_mode(new_state)
    Object new_state;
{
    Object temp;

    x_note_fn_call(225,126);
    Simulate_proprietary_qm = new_state;
    temp = 
	    inform_ui_client_interfaces_of_general_update(Qsimulate_proprietary_mode_changed,
	    new_state ? Evaluation_true_value : Evaluation_false_value);
    return VALUES_1(temp);
}

/* COM-ENTER-SIMULATE-PROPRIETARY-MODE */
Object com_enter_simulate_proprietary_mode()
{
    x_note_fn_call(225,127);
    if ( !TRUEP(Simulate_proprietary_qm))
	return set_simulate_proprietary_mode(T);
    else
	return VALUES_1(Nil);
}

static Object Qenter_simulate_proprietary_mode;  /* enter-simulate-proprietary-mode */

/* ENTER-SIMULATE-PROPRIETARY-MODE-COMMAND-TRANSLATOR */
Object enter_simulate_proprietary_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,128);
    if ( !TRUEP(Simulate_proprietary_qm))
	return make_partial_command(Qenter_simulate_proprietary_mode,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-LEAVE-SIMULATE-PROPRIETARY-MODE */
Object com_leave_simulate_proprietary_mode()
{
    x_note_fn_call(225,129);
    if (Simulate_proprietary_qm)
	return set_simulate_proprietary_mode(Nil);
    else
	return VALUES_1(Nil);
}

static Object Qleave_simulate_proprietary_mode;  /* leave-simulate-proprietary-mode */

/* LEAVE-SIMULATE-PROPRIETARY-MODE-COMMAND-TRANSLATOR */
Object leave_simulate_proprietary_mode_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,130);
    if (Simulate_proprietary_qm)
	return make_partial_command(Qleave_simulate_proprietary_mode,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-ABORT */
Object com_abort()
{
    Object temp;
    char at_the_top_qm;

    x_note_fn_call(225,131);
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)18L))) {
	temp = ISVREF(Current_workstation,(SI_Long)17L);
	at_the_top_qm =  !TRUEP(CDR(temp));
	abort_current_workstation_context(Type_of_current_workstation_context);
	if (at_the_top_qm)
	    return refresh_window(Current_workstation_window);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qabort_g2;           /* abort */

/* ABORT-COMMAND-TRANSLATOR */
Object abort_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,132);
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)18L)))
	return make_partial_command(Qabort_g2,Nil);
    else
	return VALUES_1(Nil);
}

/* COM-REFRESH */
Object com_refresh(window)
    Object window;
{
    x_note_fn_call(225,133);
    if (SIMPLE_VECTOR_P(window) && EQ(ISVREF(window,(SI_Long)0L),
	    Qg2_defstruct_structure_name_gensym_window_g2_struct)) {
	if (mdi_frame_p(window))
	    return mega_refresh(window);
	else
	    return refresh_window(window);
    }
    else
	return VALUES_1(Nil);
}

/* REFRESH-COMMAND-PURSUER */
Object refresh_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, window;

    x_note_fn_call(225,134);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    window = CAR(gensymed_symbol);
    window = command_argument_value(window);
    if (EQ(window,Plus_missing_argument_plus))
	return VALUES_3(Qwindow,Qwindow,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qrefresh;            /* refresh */

/* REFRESH-COMMAND-TRANSLATOR */
Object refresh_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object window, temp;

    x_note_fn_call(225,135);
    window = window_blackboard_function(mouse_pointer);
    if (window) {
	if (T) {
	    temp = window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qrefresh,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TOGGLE-VISIBLE-GRID */
Object com_toggle_visible_grid(image_plane)
    Object image_plane;
{
    x_note_fn_call(225,136);
    if (valid_image_plane_p(image_plane) && 
	    visible_grid_permitted_p(image_plane))
	return toggle_visible_grid(image_plane);
    else
	return VALUES_1(Nil);
}

static Object Qimage_plane;        /* image-plane */

/* TOGGLE-VISIBLE-GRID-COMMAND-PURSUER */
Object toggle_visible_grid_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane;

    x_note_fn_call(225,137);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qtoggle_visible_grid;  /* toggle-visible-grid */

/* TOGGLE-VISIBLE-GRID-COMMAND-TRANSLATOR */
Object toggle_visible_grid_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, temp;

    x_note_fn_call(225,138);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (image_plane) {
	if (visible_grid_permitted_p(image_plane)) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtoggle_visible_grid,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qediting;            /* editing */

static Object Qspecial_character_entry;  /* special-character-entry */

static Object Qinsertion_of_symbol;  /* insertion-of-symbol */

static Object Qcenter;             /* center */

/* COM-HELP */
Object com_help varargs_1(int, n)
{
    Object frame_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(225,139);
    INIT_ARGS_nonrelocating();
    frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(ISVREF(Current_workstation_context,(SI_Long)1L),Qediting) && 
	    EQ(ISVREF(Specific_structure_for_current_workstation_context,
	    (SI_Long)22L),Qspecial_character_entry))
	return put_up_special_character_help_workspace();
    else if (EQ(ISVREF(Current_workstation_context,(SI_Long)1L),Qediting) 
	    && 
	    EQ(ISVREF(Specific_structure_for_current_workstation_context,
	    (SI_Long)22L),Qinsertion_of_symbol))
	return put_up_special_character_help_workspace();
    else {
	temp = make_help_workspace(frame_qm);
	return put_workspace_on_pane_function(temp,
		Current_workstation_detail_pane,Qcenter,Qcenter,Nil,
		FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
}

static Object Qframe_qm;           /* frame? */

static Object Qframe;              /* frame */

/* HELP-COMMAND-PURSUER */
Object help_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame_qm;

    x_note_fn_call(225,140);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame_qm = CAR(gensymed_symbol);
    frame_qm = command_argument_value(frame_qm);
    if (EQ(frame_qm,Plus_missing_argument_plus))
	return VALUES_3(Qframe_qm,Qframe,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qhelp;               /* help */

/* HELP-COMMAND-TRANSLATOR */
Object help_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame_qm;

    x_note_fn_call(225,141);
    frame_qm = frame_blackboard_function(mouse_pointer);
    if (T)
	return make_partial_command(Qhelp,
		slot_value_cons_1(snapshot_command_argument(frame_qm),Nil));
    else
	return VALUES_1(Nil);
}

static Object Qg2_launch_online_help;  /* g2-launch-online-help */

static Object Qprocedure;          /* procedure */

static Object string_constant_21;  /* "The ~(~a~) procedure ~a does not exist." */

static Object string_constant_22;  /* "The launch-online-help procedure ~NF must be an ordinary procedure, not a ~(~A~)." */

static Object string_constant_23;  /* "The launch-online-help procedure ~NF ~
				    *           is either inactive or has a status other than OK."
				    */

static Object list_constant;       /* # */

static Object string_constant_24;  /* "The launch-online-help procedure ~NF's ~
				    *           argument list is not (<window> :class g2-window)"
				    */

/* GET-VALIDATED-LAUNCH-HELP-PROCEDURE? */
Object get_validated_launch_help_procedure_qm()
{
    Object procedure_name, procedure, temp;

    x_note_fn_call(225,142);
    procedure_name = Qg2_launch_online_help;
    procedure = get_instance_with_name_if_any(Qprocedure,procedure_name);
    if ( !TRUEP(procedure)) {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_21,
		    procedure_name);
	temp = Nil;
    }
    else if ( !EQ(ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)1L),
	    Qprocedure)) {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(4,FIX((SI_Long)1L),string_constant_22,procedure,
		    ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)1L));
	temp = Nil;
    }
    else {
	temp = ISVREF(procedure,(SI_Long)8L);
	if ( !( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
		(IFIX(ISVREF(procedure,(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(procedure,(SI_Long)4L)) & (SI_Long)16777216L) 
		&&  !((SI_Long)0L != (IFIX(ISVREF(procedure,(SI_Long)4L)) 
		& (SI_Long)8192L))))) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_23,
			procedure);
	    temp = Nil;
	}
	else if ( 
		!TRUEP(argument_list_description_matches_template_p(ISVREF(procedure,
		(SI_Long)24L),list_constant))) {
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(3,FIX((SI_Long)1L),string_constant_24,
			procedure);
	    temp = Nil;
	}
	else
	    temp = procedure;
    }
    return VALUES_1(temp);
}

/* COM-LAUNCH-ONLINE-HELP */
Object com_launch_online_help(workstation)
    Object workstation;
{
    Object g2_window_qm, procedure_qm_1, arg_vector;

    x_note_fn_call(225,143);
    if (workstation && get_instance_with_name_if_any(Qprocedure,
	    Qg2_launch_online_help)) {
	g2_window_qm = ISVREF(workstation,(SI_Long)25L);
	procedure_qm_1 = get_validated_launch_help_procedure_qm();
	arg_vector = allocate_managed_simple_vector(FIX((SI_Long)1L));
	if (g2_window_qm && procedure_qm_1) {
	    SVREF(arg_vector,FIX((SI_Long)0L)) = g2_window_qm;
	    start_procedure_invocation_in_place(procedure_qm_1,
		    FIX((SI_Long)6L),FIX((SI_Long)0L),arg_vector,
		    FIX((SI_Long)0L),FIX((SI_Long)1L),Nil,Nil,Nil,Nil,Nil);
	}
	return reclaim_managed_simple_vector(arg_vector);
    }
    else
	return VALUES_1(Nil);
}

static Object Qworkstation;        /* workstation */

/* LAUNCH-ONLINE-HELP-COMMAND-PURSUER */
Object launch_online_help_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, workstation;

    x_note_fn_call(225,144);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    workstation = CAR(gensymed_symbol);
    workstation = command_argument_value(workstation);
    if (EQ(workstation,Plus_missing_argument_plus))
	return VALUES_3(Qworkstation,Qworkstation,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qlaunch_online_help;  /* launch-online-help */

/* LAUNCH-ONLINE-HELP-COMMAND-TRANSLATOR */
Object launch_online_help_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object workstation, temp;

    x_note_fn_call(225,145);
    workstation = workstation_blackboard_function(mouse_pointer);
    if (workstation) {
	if (get_instance_with_name_if_any(Qprocedure,Qg2_launch_online_help)) {
	    temp = workstation;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qlaunch_online_help,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-CIRCULATE-UP */
Object com_circulate_up(pane)
    Object pane;
{
    x_note_fn_call(225,146);
    if (pane)
	return circulate_up(pane);
    else
	return VALUES_1(Nil);
}

static Object Qpane;               /* pane */

/* CIRCULATE-UP-COMMAND-PURSUER */
Object circulate_up_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, pane;

    x_note_fn_call(225,147);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    pane = CAR(gensymed_symbol);
    pane = command_argument_value(pane);
    if (EQ(pane,Plus_missing_argument_plus))
	return VALUES_3(Qpane,Qpane,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qcirculate_up;       /* circulate-up */

/* CIRCULATE-UP-COMMAND-TRANSLATOR */
Object circulate_up_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object pane, temp;

    x_note_fn_call(225,148);
    pane = pane_blackboard_function(mouse_pointer);
    if (pane) {
	if (T) {
	    temp = pane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcirculate_up,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-CIRCULATE-DOWN */
Object com_circulate_down(pane)
    Object pane;
{
    x_note_fn_call(225,149);
    if (pane)
	return circulate_down(pane);
    else
	return VALUES_1(Nil);
}

/* CIRCULATE-DOWN-COMMAND-PURSUER */
Object circulate_down_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, pane;

    x_note_fn_call(225,150);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    pane = CAR(gensymed_symbol);
    pane = command_argument_value(pane);
    if (EQ(pane,Plus_missing_argument_plus))
	return VALUES_3(Qpane,Qpane,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qcirculate_down;     /* circulate-down */

/* CIRCULATE-DOWN-COMMAND-TRANSLATOR */
Object circulate_down_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object pane, temp;

    x_note_fn_call(225,151);
    pane = pane_blackboard_function(mouse_pointer);
    if (pane) {
	if (T) {
	    temp = pane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcirculate_down,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-LIFT-TO-TOP */
Object com_lift_to_top(image_plane)
    Object image_plane;
{
    x_note_fn_call(225,152);
    if (valid_image_plane_p(image_plane))
	return raise_image_plane_to_top(1,image_plane);
    else
	return VALUES_1(Nil);
}

/* LIFT-TO-TOP-COMMAND-PURSUER */
Object lift_to_top_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane;

    x_note_fn_call(225,153);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qlift_to_top;        /* lift-to-top */

/* LIFT-TO-TOP-COMMAND-TRANSLATOR */
Object lift_to_top_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, temp;

    x_note_fn_call(225,154);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (image_plane) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qlift_to_top,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-DROP-TO-BOTTOM */
Object com_drop_to_bottom(image_plane)
    Object image_plane;
{
    x_note_fn_call(225,155);
    if (valid_image_plane_p(image_plane))
	return lower_image_plane_to_bottom(image_plane);
    else
	return VALUES_1(Nil);
}

/* DROP-TO-BOTTOM-COMMAND-PURSUER */
Object drop_to_bottom_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane;

    x_note_fn_call(225,156);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qdrop_to_bottom;     /* drop-to-bottom */

/* DROP-TO-BOTTOM-COMMAND-TRANSLATOR */
Object drop_to_bottom_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, temp;

    x_note_fn_call(225,157);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (image_plane) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qdrop_to_bottom,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtrend_chart;        /* trend-chart */

static Object Qfreeform_table;     /* freeform-table */

static Object Qfree_text;          /* free-text */

static Object Qborderless_free_text;  /* borderless-free-text */

/* ENTITY-LIKE-P */
Object entity_like_p(block)
    Object block;
{
    Object sub_class_bit_vector, temp, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(225,158);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Entity_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Chart_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qtrend_chart,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Graph_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Readout_table_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qfreeform_table,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qfree_text,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	gensymed_symbol_3 = 
		lookup_global_or_kb_specific_property_value(Qborderless_free_text,
		Class_description_gkbprop);
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_3,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_1 = (SI_Long)1L;
		gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	    }
	    else
		temp = Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Statement_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Message_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Scrap_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_1 = (SI_Long)1L;
	    gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	    return VALUES_1((SI_Long)0L < gensymed_symbol ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* BLOCK-IS-UPON-KB-WORKSPACE? */
Object block_is_upon_kb_workspace_qm(block)
    Object block;
{
    Object gensymed_symbol, workspace_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(225,159);
    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)5L)) : Nil;
    workspace_qm = gensymed_symbol;
    if (workspace_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	    return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? T : Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-LIFT-ITEM-TO-TOP */
Object com_lift_item_to_top(frame)
    Object frame;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,160);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	temp = (temp ? TRUEP(entity_like_p(frame)) : TRUEP(Nil)) ? 
		TRUEP(block_is_upon_kb_workspace_qm(frame)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return raise_block_to_top(frame);
    else
	return VALUES_1(Nil);
}

static Object Qframe_for_selection;  /* frame-for-selection */

/* LIFT-ITEM-TO-TOP-COMMAND-PURSUER */
Object lift_item_to_top_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame;

    x_note_fn_call(225,161);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qframe_for_selection,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qlift_item_to_top;   /* lift-item-to-top */

/* LIFT-ITEM-TO-TOP-COMMAND-TRANSLATOR */
Object lift_item_to_top_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,162);
    frame = frame_for_selection_blackboard_function(mouse_pointer);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ((temp ? TRUEP(entity_like_p(frame)) : TRUEP(Nil)) ? 
		TRUEP(block_is_upon_kb_workspace_qm(frame)) : TRUEP(Nil)) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qlift_item_to_top,
		    slot_value_cons_1(snapshot_command_argument(temp_1),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-DROP-ITEM-TO-BOTTOM */
Object com_drop_item_to_bottom(frame)
    Object frame;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,163);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	temp = (temp ? TRUEP(entity_like_p(frame)) : TRUEP(Nil)) ? 
		TRUEP(block_is_upon_kb_workspace_qm(frame)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return lower_block_to_bottom(frame);
    else
	return VALUES_1(Nil);
}

/* DROP-ITEM-TO-BOTTOM-COMMAND-PURSUER */
Object drop_item_to_bottom_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame;

    x_note_fn_call(225,164);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qframe_for_selection,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qdrop_item_to_bottom;  /* drop-item-to-bottom */

/* DROP-ITEM-TO-BOTTOM-COMMAND-TRANSLATOR */
Object drop_item_to_bottom_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,165);
    frame = frame_for_selection_blackboard_function(mouse_pointer);
    if (frame) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ((temp ? TRUEP(entity_like_p(frame)) : TRUEP(Nil)) ? 
		TRUEP(block_is_upon_kb_workspace_qm(frame)) : TRUEP(Nil)) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qdrop_item_to_bottom,
		    slot_value_cons_1(snapshot_command_argument(temp_1),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-LIFT-ITEM-TO-TOP */
Object g2_lift_item_to_top(block)
    Object block;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,166);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
    if (temp)
	return VALUES_1(Nil);
    else
	return raise_block_to_top(block);
}

static Object Kstack_error;        /* :stack-error */

/* G2-LIFT-ITEM-TO-TOP-SYSTEM-RPC-INTERNAL */
Object g2_lift_item_to_top_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(225,167);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_lift_item_to_top(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DROP-ITEM-TO-BOTTOM */
Object g2_drop_item_to_bottom(block)
    Object block;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,168);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
    if (temp)
	return VALUES_1(Nil);
    else
	return lower_block_to_bottom(block);
}

/* G2-DROP-ITEM-TO-BOTTOM-SYSTEM-RPC-INTERNAL */
Object g2_drop_item_to_bottom_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(225,169);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_drop_item_to_bottom(item);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-LIFT-ITEM-TO-FRONT */
Object g2_lift_item_to_front(block_1,block_2)
    Object block_1, block_2;
{
    x_note_fn_call(225,170);
    return order_blocks(block_1,block_2,Nil);
}

/* G2-LIFT-ITEM-IN-FRONT-OF-SYSTEM-RPC-INTERNAL */
Object g2_lift_item_in_front_of_system_rpc_internal(gensymed_symbol,item_1,
	    item_2)
    Object gensymed_symbol, item_1, item_2;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(225,171);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_drop_item_to_back(item_1,item_2);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-DROP-ITEM-TO-BACK */
Object g2_drop_item_to_back(block_1,block_2)
    Object block_1, block_2;
{
    x_note_fn_call(225,172);
    return order_blocks(block_1,block_2,T);
}

/* G2-DROP-ITEM-BEHIND-SYSTEM-RPC-INTERNAL */
Object g2_drop_item_behind_system_rpc_internal(gensymed_symbol,item_1,item_2)
    Object gensymed_symbol, item_1, item_2;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(225,173);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_drop_item_to_back(item_1,item_2);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-GET-ITEM-LAYER-POSITION */
Object g2_get_item_layer_position(item_as_evaluation_value)
    Object item_as_evaluation_value;
{
    Object item, value_1;

    x_note_fn_call(225,174);
    item = IDENTITY(item_as_evaluation_value);
    value_1 = Nil;
    value_1 = compute_user_visible_layer_position_of_item(item);
    IDENTITY(item_as_evaluation_value);
    return VALUES_1(value_1);
}

/* G2-GET-ITEM-LAYER-POSITION-SYSTEM-RPC-INTERNAL */
Object g2_get_item_layer_position_system_rpc_internal(gensymed_symbol,item)
    Object gensymed_symbol, item;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(225,175);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL_WITH_SYMBOL(Current_system_rpc_icp_socket_qm,Qcurrent_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		  0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_get_item_layer_position(item);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = eval_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

static Object Qg2_last_input_event;  /* g2-last-input-event */

static Object Qunknown;            /* unknown */

/* G2-LAST-INPUT-EVENT */
Object g2_last_input_event(g2_window_as_evaluation_value)
    Object g2_window_as_evaluation_value;
{
    Object g2_window, value_1, workstation_qm, mouse_pointer, key_code, temp;

    x_note_fn_call(225,176);
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    value_1 = Nil;
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    if ( !TRUEP(workstation_qm))
	value_1 = ui_stack_error_for_non_connected_window(Qg2_window,
		Qg2_last_input_event);
    else {
	mouse_pointer = ISVREF(workstation_qm,(SI_Long)54L);
	key_code = ISVREF(mouse_pointer,(SI_Long)8L);
	if (FIXNUM_EQ(Illegal_key_code,key_code))
	    value_1 = Qunknown;
	else {
	    temp = parseable_symbol_from_key_code(key_code);
	    if (temp);
	    else
		temp = Qunknown;
	    value_1 = temp;
	}
    }
    IDENTITY(g2_window_as_evaluation_value);
    return VALUES_1(value_1);
}

/* GENSYM-WINDOW-POINT-TO-USER-WINDOW-POINT */
Object gensym_window_point_to_user_window_point(gensym_window,x_in_window,
	    y_in_window)
    Object gensym_window, x_in_window, y_in_window;
{
    Object temp, image_plane, temp_1;

    x_note_fn_call(225,177);
    temp = ISVREF(detail_pane(gensym_window),(SI_Long)5L);
    image_plane = CAR(temp);
    temp_1 = FIX(IFIX(x_in_window) - (IFIX(FIXNUM_ADD(ISVREF(image_plane,
	    (SI_Long)6L),ISVREF(image_plane,(SI_Long)8L))) >>  -  - 
	    (SI_Long)1L));
    temp = FIX( - (IFIX(y_in_window) - (IFIX(FIXNUM_ADD(ISVREF(image_plane,
	    (SI_Long)7L),ISVREF(image_plane,(SI_Long)9L))) >>  -  - 
	    (SI_Long)1L)));
    return VALUES_2(temp_1,temp);
}

static Object Qg2_last_input_event_info;  /* g2-last-input-event-info */

static Object Qnone;               /* none */

static Object Qtruth_value;        /* truth-value */

/* G2-LAST-INPUT-EVENT-INFO */
Object g2_last_input_event_info(g2_window_as_evaluation_value)
    Object g2_window_as_evaluation_value;
{
    Object g2_window, value_1, value_2, value_3, value_4, value_5, value_6;
    Object value_7, value_8, workstation_qm, mouse_pointer, key_code, unicode;
    Object gensymed_symbol, mouse_button, last_event_symbol, x_in_window;
    Object y_in_window, timestamp, image_plane_qm, user_window_x;
    Object user_window_y, scale, value, temp_1, temp_3;
    SI_Long arg, arg_1, arg_2, temp_2, gensymed_symbol_1;
    char temp;
    Object result;

    x_note_fn_call(225,178);
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    value_1 = Nil;
    value_2 = Nil;
    value_3 = Nil;
    value_4 = Nil;
    value_5 = Nil;
    value_6 = Nil;
    value_7 = Nil;
    value_8 = Nil;
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    if ( !TRUEP(workstation_qm))
	result = ui_stack_error_for_non_connected_window(Qg2_window,
		Qg2_last_input_event_info);
    else {
	mouse_pointer = ISVREF(workstation_qm,(SI_Long)54L);
	key_code = ISVREF(mouse_pointer,(SI_Long)8L);
	arg = (SI_Long)769L;
	if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
	    unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
	    arg_1 = num_len(3,FIX((SI_Long)0L),unicode,FIX((SI_Long)127L)) 
		    ? IFIX(unicode) : IFIX(Illegal_key_index);
	}
	else
	    arg_1 = IFIX(FIXNUM_LOGAND(Key_index_bits,key_code));
	arg_2 = (SI_Long)779L;
	temp = arg <= arg_1 ? arg_1 <= arg_2 : TRUEP(Qnil);
	if (temp);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp = IFIX(gensymed_symbol) == (SI_Long)779L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)812L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)813L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)814L;
	}
	if (temp);
	else {
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		gensymed_symbol = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		gensymed_symbol = FIXNUM_LOGAND(Key_index_bits,key_code);
	    temp = IFIX(gensymed_symbol) == (SI_Long)778L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)815L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)816L;
	    if (temp);
	    else
		temp = IFIX(gensymed_symbol) == (SI_Long)817L;
	}
	mouse_button = temp ? ISVREF(workstation_qm,(SI_Long)10L) : Qnone;
	last_event_symbol =  !FIXNUM_EQ(Illegal_key_code,key_code) ? 
		parseable_symbol_from_key_code(key_code) : Nil;
	if (last_event_symbol);
	else
	    last_event_symbol = Qunknown;
	x_in_window = x_in_window_blackboard_function(mouse_pointer);
	y_in_window = y_in_window_blackboard_function(mouse_pointer);
	timestamp = timestamp_blackboard_function(mouse_pointer);
	image_plane_qm = image_plane_blackboard_function(mouse_pointer);
	if (x_in_window && y_in_window && timestamp) {
	    result = gensym_window_point_to_user_window_point(ISVREF(workstation_qm,
		    (SI_Long)1L),x_in_window,y_in_window);
	    MVS_2(result,user_window_x,user_window_y);
	    if (image_plane_qm) {
		scale = ISVREF(image_plane_qm,(SI_Long)11L);
		value = FIXNUM_MINUS(x_in_window,ISVREF(image_plane_qm,
			(SI_Long)13L));
		if (IFIX(scale) == (SI_Long)4096L)
		    temp_1 = value;
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    temp_1 = inverse_scalef_function(scale,value);
		else if (IFIX(value) >= (SI_Long)0L)
		    temp_1 = FIX(((IFIX(value) << (SI_Long)12L) + 
			    (IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale));
		else {
		    temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp_1 = FIXNUM_NEGATE(FIX(temp_2));
		}
	    }
	    else
		temp_1 = FIX((SI_Long)0L);
	    if (image_plane_qm) {
		scale = ISVREF(image_plane_qm,(SI_Long)12L);
		value = FIXNUM_MINUS(y_in_window,ISVREF(image_plane_qm,
			(SI_Long)14L));
		if (IFIX(scale) == (SI_Long)4096L)
		    gensymed_symbol_1 = IFIX(value);
		else if ( 
			!(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)))
		    gensymed_symbol_1 = IFIX(inverse_scalef_function(scale,
			    value));
		else if (IFIX(value) >= (SI_Long)0L) {
		    temp_2 = ((IFIX(value) << (SI_Long)12L) + (IFIX(scale) 
			    >>  -  - (SI_Long)1L)) / IFIX(scale);
		    gensymed_symbol_1 = temp_2;
		}
		else {
		    temp_2 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) 
			    + (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			    IFIX(scale);
		    temp_2 = IFIX(FIXNUM_NEGATE(FIX(temp_2)));
		    gensymed_symbol_1 = temp_2;
		}
		temp_3 = FIX( - gensymed_symbol_1);
	    }
	    else
		temp_3 = FIX((SI_Long)0L);
	    result = VALUES_8(last_event_symbol,image_plane_qm ? Truth : 
		    Falsity,user_window_x,user_window_y,timestamp,temp_1,
		    temp_3,mouse_button);
	}
	else
	    result = VALUES_1(Nil);
    }
    MVS_8(result,value_1,value_2,value_3,value_4,value_5,value_6,value_7,
	    value_8);
    IDENTITY(g2_window_as_evaluation_value);
    temp_3 = value_1;
    if (FIXNUM_EQ(value_2,Truth))
	temp_1 = Evaluation_true_value;
    else if (FIXNUM_EQ(value_2,Falsity))
	temp_1 = Evaluation_false_value;
    else
	temp_1 = eval_cons_1(value_2,Qtruth_value);
    return VALUES_8(temp_3,temp_1,value_3,value_4,value_5,value_6,value_7,
	    value_8);
}

/* G2-REFRESH-IMAGE-DEFINITION */
Object g2_refresh_image_definition(image_definition_as_evaluation_value)
    Object image_definition_as_evaluation_value;
{
    Object image_definition;

    x_note_fn_call(225,179);
    image_definition = IDENTITY(image_definition_as_evaluation_value);
    refresh_image_definition_from_file(image_definition);
    IDENTITY(image_definition_as_evaluation_value);
    return VALUES_0();
}

/* TRANSFER-ITEMS-TO-MOUSE-OF-WINDOW */
Object transfer_items_to_mouse_of_window varargs_1(int, n)
{
    Object item_or_items, g2_window;
    Object image_plane_if_move_case_qm, workstation_qm, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, block_or_blocks;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(225,180);
    INIT_ARGS_nonrelocating();
    item_or_items = REQUIRED_ARG_nonrelocating();
    g2_window = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    image_plane_if_move_case_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workstation_qm = ISVREF(g2_window,(SI_Long)20L);
    if (workstation_qm) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation_qm;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    11);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      10);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			9);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  8);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    7);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      6);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				5);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  4);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    3);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      2);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					1);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  0);
				    block_or_blocks = ATOM(item_or_items) ?
					     item_or_items : 
					    copy_list_using_dragging_conses_1(item_or_items);
				    if (image_plane_if_move_case_qm)
					SAVE_VALUES(enter_move_dragging_context(4,
						block_or_blocks,
						FIX((SI_Long)0L),
						FIX((SI_Long)0L),
						image_plane_if_move_case_qm));
				    else
					SAVE_VALUES(enter_transfer_dragging_context(1,
						block_or_blocks));
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
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

/* TRANSFER-ITEM-TO-MOUSE-OF-WINDOW */
Object transfer_item_to_mouse_of_window(item,g2_window)
    Object item, g2_window;
{
    x_note_fn_call(225,181);
    return transfer_items_to_mouse_of_window(2,item,g2_window);
}

/* MOVE-ITEMS-TO-MOUSE-OF-WINDOW */
Object move_items_to_mouse_of_window(item_or_items,g2_window,image_plane)
    Object item_or_items, g2_window, image_plane;
{
    x_note_fn_call(225,182);
    return transfer_items_to_mouse_of_window(3,item_or_items,g2_window,
	    image_plane);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object string_constant_25;  /* "The ~a" */

static Object string_constant_26;  /* " argument of ~a is declared to take values of class ~
				    *        ~a, but instead it received "
				    */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant_27;  /* "~NF, an instance of the class ~a." */

/* SYSTEM-PROCEDURE-ARGUMENT-LIST-ERROR */
Object system_procedure_argument_list_error(argument_name,procedure_name,
	    class_1,supplied_value)
    Object argument_name, procedure_name, class_1, supplied_value;
{
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(7);

    x_note_fn_call(225,183);
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
		  tformat(2,string_constant_25,argument_name);
		  tformat(3,string_constant_26,procedure_name,class_1);
		  if (SIMPLE_VECTOR_P(supplied_value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(supplied_value)) 
			  > (SI_Long)2L &&  !EQ(ISVREF(supplied_value,
			  (SI_Long)1L),Qavailable_frame_vector)) {
		      x2 = ISVREF(supplied_value,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      tformat(3,string_constant_27,supplied_value,
			      ISVREF(ISVREF(supplied_value,(SI_Long)1L),
			      (SI_Long)1L));
		  else {
		      write_stored_value(supplied_value);
		      twrite_character(FIX((SI_Long)46L));
		  }
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

static Object string_constant_28;  /* "The ~a argument of ~a must be a connected window." */

/* UI-STACK-ERROR-FOR-NON-CONNECTED-WINDOW */
Object ui_stack_error_for_non_connected_window(argument_name,procedure_name)
    Object argument_name, procedure_name;
{
    Object top_of_stack, message_1;

    x_note_fn_call(225,184);
    top_of_stack = Cached_top_of_stack;
    message_1 = tformat_stack_error_text_string(3,string_constant_28,
	    argument_name,procedure_name);
    return raw_stack_error_named_error(top_of_stack,message_1);
}

Object Launch_editor_options_type = UNBOUND;

static Object string_constant_29;  /* "The attribute named ~a was not found." */

static Object Qcompound_slot_descriptor;  /* compound-slot-descriptor */

static Object string_constant_30;  /* "Component attributes of a ~a, such as ~a, ~
				    *                                     may not be edited programmatically."
				    */

static Object string_constant_31;  /* "The editing of attribute ~a of ~NF is restricted." */

static Object string_constant_32;  /* "The attribute ~a of ~NF may not be edited." */

/* SLOT-DENOTATION-OF-EDITABLE-SLOT-OR-STACK-ERROR */
Object slot_denotation_of_editable_slot_or_stack_error(item,attribute_name,
	    workstation)
    Object item, attribute_name, workstation;
{
    Object current_g2_user_mode_qm, slot_denotation_qm, top_of_stack;
    Object message_1, gensymed_symbol, pretty_slot_name, class_or_frame_qm;
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(225,185);
    current_g2_user_mode_qm = ISVREF(workstation,(SI_Long)19L);
    slot_denotation_qm = 
	    unmangle_slot_component_alias(parse_slot_name_denotation(attribute_name,
	    item));
    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
	    0);
      if ( !TRUEP(slot_denotation_qm) ||  
	      !TRUEP(get_slot_description_of_class_description_function(CONSP(slot_denotation_qm) 
	      ? M_CAR(M_CDR(M_CDR(slot_denotation_qm))) : 
	      slot_denotation_qm,ISVREF(item,(SI_Long)1L),
	      CONSP(slot_denotation_qm) ? M_CAR(M_CDR(slot_denotation_qm)) 
	      : Nil))) {
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(2,string_constant_29,
		  attribute_name);
	  result = raw_stack_error_named_error(top_of_stack,message_1);
      }
      else {
	  gensymed_symbol = CONSP(slot_denotation_qm) ? 
		  M_CAR(M_CDR(M_CDR(slot_denotation_qm))) : slot_denotation_qm;
	  if (getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		  Qcompound_slot_descriptor)) {
	      top_of_stack = Cached_top_of_stack;
	      message_1 = tformat_stack_error_text_string(3,
		      string_constant_30,ISVREF(ISVREF(item,(SI_Long)1L),
		      (SI_Long)1L),attribute_name);
	      result = raw_stack_error_named_error(top_of_stack,message_1);
	  }
	  else {
	      pretty_slot_name = CONSP(slot_denotation_qm) ? 
		      M_CAR(M_CDR(M_CDR(slot_denotation_qm))) : 
		      slot_denotation_qm;
	      class_or_frame_qm = CONSP(slot_denotation_qm) ? 
		      M_CAR(M_CDR(slot_denotation_qm)) : Nil;
	      temp = get_alias_for_slot_name_if_any(pretty_slot_name,
		      class_or_frame_qm);
	      if (temp);
	      else
		  temp = pretty_slot_name;
	      if ( !TRUEP(get_slot_description_if_editable_attribute(item,
		      temp,CONSP(slot_denotation_qm) ? 
		      M_CAR(M_CDR(slot_denotation_qm)) : Nil))) {
		  top_of_stack = Cached_top_of_stack;
		  message_1 = tformat_stack_error_text_string(3,
			  string_constant_31,attribute_name,item);
		  result = raw_stack_error_named_error(top_of_stack,message_1);
	      }
	      else if ( !TRUEP(editable_slot_p(item,
		      CONSP(slot_denotation_qm) ? 
		      M_CAR(M_CDR(M_CDR(slot_denotation_qm))) : 
		      slot_denotation_qm,CONSP(slot_denotation_qm) ? 
		      M_CAR(M_CDR(slot_denotation_qm)) : Nil,Nil))) {
		  top_of_stack = Cached_top_of_stack;
		  message_1 = tformat_stack_error_text_string(3,
			  string_constant_32,attribute_name,item);
		  result = raw_stack_error_named_error(top_of_stack,message_1);
	      }
	      else
		  result = VALUES_1(slot_denotation_qm);
	  }
      }
    POP_SPECIAL();
    return result;
}

static Object Qreturn_from_field_edit;  /* return-from-field-edit */

static Object Qreclaim_list_and_record_abort_in_edit_status_parameter;  /* reclaim-list-and-record-abort-in-edit-status-parameter */

/* LAUNCH-EDITOR-1 */
Object launch_editor_1 varargs_1(int, n)
{
    Object item, slot_denotation, workstation;
    Object line_qm, character_qm, type_of_slot_qm, symbolic_parameter_qm;
    Object modal, size_x, size_y, pos_x, pos_y, workspace_qm, image_plane_qm;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(225,186);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    slot_denotation = REQUIRED_ARG_nonrelocating();
    workstation = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    line_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    character_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    type_of_slot_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    symbolic_parameter_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    modal = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    size_x = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    size_y = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    pos_x = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    pos_y = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    workspace_qm = get_workspace_if_any(item);
    image_plane_qm = workspace_qm ? 
	    image_plane_of_workspace_on_workstation(workstation,
	    workspace_qm) : Qnil;
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				if (symbolic_parameter_qm) {
				    establish_next_workstation_context_continuation(Nil,
					    Qreturn_from_field_edit,
					    slot_value_list_2(symbolic_parameter_qm,
					    copy_frame_serial_number(ISVREF(symbolic_parameter_qm,
					    (SI_Long)3L))),
					    Qreclaim_list_and_record_abort_in_edit_status_parameter);
				    SAVE_VALUES(launch_editor_2(item,
					    slot_denotation,image_plane_qm,
					    line_qm,character_qm,
					    type_of_slot_qm,modal,size_x,
					    size_y,pos_x,pos_y));
				}
				else
				    SAVE_VALUES(launch_editor_2(item,
					    slot_denotation,image_plane_qm,
					    line_qm,character_qm,
					    type_of_slot_qm,modal,size_x,
					    size_y,pos_x,pos_y));
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qbox_translation_and_text;  /* box-translation-and-text */

/* LAUNCH-EDITOR-2 */
Object launch_editor_2(item,slot_denotation,image_plane_qm,line_qm,
	    character_qm,type_of_slot_qm,modal,size_x,size_y,pos_x,pos_y)
    Object item, slot_denotation, image_plane_qm, line_qm, character_qm;
    Object type_of_slot_qm, modal, size_x, size_y, pos_x, pos_y;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,187);
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
    if ((temp ? EQ(CONSP(slot_denotation) ? 
	    M_CAR(M_CDR(M_CDR(slot_denotation))) : slot_denotation,
	    Qbox_translation_and_text) : TRUEP(Nil)) ? 
	    TRUEP(image_plane_qm) : TRUEP(Nil))
	return enter_editing_context_on_text_box(7,item,image_plane_qm,Nil,
		Nil,line_qm,character_qm,type_of_slot_qm);
    else
	return enter_editing_context(29,item,slot_denotation,Nil,Nil,Nil,
		Nil,line_qm,character_qm,Nil,Nil,Nil,Nil,Nil,Nil,
		type_of_slot_qm,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil,modal,
		size_x,size_y,pos_x,pos_y);
}

static Object Qtoolbar_id;         /* toolbar-id */

static Object Qtoolbar_text;       /* toolbar-text */

/* PROCESSED-EDITOR-TOOLBAR */
Object processed_editor_toolbar(toolbar_buttons)
    Object toolbar_buttons;
{
    Object gensymed_symbol, held_vector, button, elt_1, validated_elt;
    Object toolbar_component_id, toolbar_component_text;
    SI_Long next_index, length_1;

    x_note_fn_call(225,188);
    gensymed_symbol = toolbar_buttons;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    button = Nil;
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
    button = validated_elt;
    toolbar_component_id = estructure_slot(button,Qtoolbar_id,Nil);
    toolbar_component_text = estructure_slot(button,Qtoolbar_text,Nil);
    manage_native_editor(4,Editor_window_handle,Editor_add_toolbar_button,
	    toolbar_component_text,toolbar_component_id);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Editor_toolbar_user_callback, Qeditor_toolbar_user_callback);

static Object string_constant_33;  /* "There is no editor open on ~NF." */

/* G2-UI-CLOSE-CURRENT-EDITOR */
Object g2_ui_close_current_editor(apply_changes_qm,g2_window)
    Object apply_changes_qm, g2_window;
{
    Object apply_changes_p, gensym_window, workstation, edit_state;
    Object top_of_stack, message_1, native_window_qm, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, current_edit_state;
    Object current_edit_workspace, svref_arg_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(225,189);
    SAVE_STACK();
    apply_changes_p = evaluation_truth_value_is_true_p(apply_changes_qm);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    edit_state = find_current_edit_state(workstation);
    if (edit_state);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_33,
		g2_window);
	edit_state = raw_stack_error_named_error(top_of_stack,message_1);
    }
    native_window_qm = native_editor_p(gensym_window) ? 
	    native_editor_window(edit_state) : Nil;
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		13);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  12);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    11);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      10);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			9);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  8);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    7);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      6);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				5);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  4);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    3);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      2);
				current_edit_state = edit_state;
				PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
					1);
				  current_edit_workspace = 
					  ISVREF(Current_edit_state,
					  (SI_Long)12L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
					  0);
				    svref_arg_1 = Current_edit_state;
				    SVREF(svref_arg_1,FIX((SI_Long)102L)) = T;
				    if (native_window_qm) {
					if (apply_changes_p)
					    SAVE_VALUES(manage_native_editor(2,
						    native_window_qm,
						    Editor_exit_new));
					else
					    SAVE_VALUES(manage_native_editor(2,
						    native_window_qm,
						    Editor_cancel));
				    }
				    else if (apply_changes_p)
					SAVE_VALUES(end_editing());
				    else if ( !TRUEP(end_editing())) {
					svref_arg_1 = Current_edit_state;
					SVREF(svref_arg_1,
						FIX((SI_Long)76L)) = T;
					SAVE_VALUES(cancel_editing());
				    }
				    else
					SAVE_VALUES(VALUES_1(Nil));
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qg2_ui_launch_editor;  /* g2-ui-launch-editor */

static Object Qtoolbar;            /* toolbar */

static Object Qtoolbar_callback_function;  /* toolbar-callback-function */

static Object Qattribute;          /* attribute */

static Object Qtext;               /* text */

static Object Qgrammar;            /* grammar */

static Object Qsemaphore;          /* semaphore */

static Object Qline;               /* line */

static Object Qexclude;            /* exclude */

static Object Qpreferred_editor;   /* preferred-editor */

static Object Qtitle;              /* title */

/* G2-UI-LAUNCH-EDITOR-EXTENDED */
Object g2_ui_launch_editor_extended(item_as_evaluation_value,
	    options_as_evaluation_value,modal_as_evaluation_value,
	    size_x_as_evaluation_value,size_y_as_evaluation_value,
	    pos_x_as_evaluation_value,pos_y_as_evaluation_value,
	    g2_window_as_evaluation_value)
    Object item_as_evaluation_value, options_as_evaluation_value;
    Object modal_as_evaluation_value, size_x_as_evaluation_value;
    Object size_y_as_evaluation_value, pos_x_as_evaluation_value;
    Object pos_y_as_evaluation_value, g2_window_as_evaluation_value;
{
    Object item, options, modal, size_x, size_y, pos_x, pos_y, g2_window;
    Object workstation, toolbar_buttons, toolbar_callback, attribute;
    Object slot_denotation, type_of_slot_qm, symbolic_parameter_qm, line_qm;
    Object column_qm, editor_prompt_filter_qm, override_preferred_editor;
    Object editor_caption_text_override_qm;
    Declare_special(3);

    x_note_fn_call(225,190);
    item = IDENTITY(item_as_evaluation_value);
    options = IDENTITY(options_as_evaluation_value);
    modal = M_CAR(modal_as_evaluation_value);
    size_x = size_x_as_evaluation_value;
    size_y = size_y_as_evaluation_value;
    pos_x = pos_x_as_evaluation_value;
    pos_y = pos_y_as_evaluation_value;
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    if ( !TRUEP(ISVREF(g2_window,(SI_Long)20L)))
	ui_stack_error_for_non_connected_window(Qg2_window,
		Qg2_ui_launch_editor);
    if (EQ(modal,Truth))
	modal = T;
    else if (EQ(modal,Falsity))
	modal = Nil;
    check_type_or_stack_error(2,options,Launch_editor_options_type);
    workstation = ISVREF(g2_window,(SI_Long)20L);
    toolbar_buttons = estructure_slot(options,Qtoolbar,Nil);
    toolbar_callback = estructure_slot(options,Qtoolbar_callback_function,Nil);
    attribute = estructure_slot(options,Qattribute,Qtext);
    slot_denotation = slot_denotation_of_editable_slot_or_stack_error(item,
	    attribute,workstation);
    type_of_slot_qm = 
	    compute_type_of_slot_or_stack_error(estructure_slot(options,
	    Qgrammar,Nil));
    symbolic_parameter_qm = estructure_slot(options,Qsemaphore,Nil);
    line_qm = estructure_slot(options,Qline,FIX((SI_Long)1L));
    column_qm = estructure_slot(options,Qcolumn,FIX((SI_Long)0L));
    editor_prompt_filter_qm = 
	    parse_editor_prompt_filter(estructure_slot(options,Qexclude,Nil));
    PUSH_SPECIAL_WITH_SYMBOL(Editor_prompt_filter_qm,Qeditor_prompt_filter_qm,editor_prompt_filter_qm,
	    2);
      override_preferred_editor = estructure_slot(options,
	      Qpreferred_editor,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Override_preferred_editor,Qoverride_preferred_editor,override_preferred_editor,
	      1);
	editor_caption_text_override_qm = estructure_slot(options,Qtitle,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Editor_caption_text_override_qm,Qeditor_caption_text_override_qm,editor_caption_text_override_qm,
		0);
	  launch_editor_1(12,item,slot_denotation,workstation,line_qm,
		  column_qm,type_of_slot_qm,symbolic_parameter_qm,modal,
		  size_x,size_y,pos_x,pos_y);
	  if (CONSP(toolbar_buttons) && EQ(M_CDR(toolbar_buttons),
		  Qsequence) &&  
		  !(IFIX(FIXNUM_SUB1(ISVREF(M_CAR(toolbar_buttons),
		  (SI_Long)1L))) == (SI_Long)0L))
	      processed_editor_toolbar(toolbar_buttons);
	  if (toolbar_callback)
	      Editor_toolbar_user_callback = 
		      stored_callback_procedure(toolbar_callback);
	  reclaim_evaluation_structure(options);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    IDENTITY(item_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    if ( !(EQ(modal_as_evaluation_value,Evaluation_true_value) || 
	    EQ(modal_as_evaluation_value,Evaluation_false_value)))
	reclaim_eval_cons_1(modal_as_evaluation_value);
    IDENTITY(g2_window_as_evaluation_value);
    return VALUES_0();
}

/* G2-UI-LAUNCH-EDITOR */
Object g2_ui_launch_editor(item_as_evaluation_value,
	    options_as_evaluation_value,g2_window_as_evaluation_value)
    Object item_as_evaluation_value, options_as_evaluation_value;
    Object g2_window_as_evaluation_value;
{
    Object item, options, g2_window, workstation, attribute, slot_denotation;
    Object type_of_slot_qm, symbolic_parameter_qm, line_qm, column_qm;
    Object editor_prompt_filter_qm, override_preferred_editor;
    Object editor_caption_text_override_qm;
    Declare_special(3);

    x_note_fn_call(225,191);
    item = IDENTITY(item_as_evaluation_value);
    options = IDENTITY(options_as_evaluation_value);
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    if ( !TRUEP(ISVREF(g2_window,(SI_Long)20L)))
	ui_stack_error_for_non_connected_window(Qg2_window,
		Qg2_ui_launch_editor);
    check_type_or_stack_error(2,options,Launch_editor_options_type);
    workstation = ISVREF(g2_window,(SI_Long)20L);
    attribute = estructure_slot(options,Qattribute,Qtext);
    slot_denotation = slot_denotation_of_editable_slot_or_stack_error(item,
	    attribute,workstation);
    type_of_slot_qm = 
	    compute_type_of_slot_or_stack_error(estructure_slot(options,
	    Qgrammar,Nil));
    symbolic_parameter_qm = estructure_slot(options,Qsemaphore,Nil);
    line_qm = estructure_slot(options,Qline,FIX((SI_Long)1L));
    column_qm = estructure_slot(options,Qcolumn,FIX((SI_Long)0L));
    editor_prompt_filter_qm = 
	    parse_editor_prompt_filter(estructure_slot(options,Qexclude,Nil));
    PUSH_SPECIAL_WITH_SYMBOL(Editor_prompt_filter_qm,Qeditor_prompt_filter_qm,editor_prompt_filter_qm,
	    2);
      override_preferred_editor = estructure_slot(options,
	      Qpreferred_editor,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Override_preferred_editor,Qoverride_preferred_editor,override_preferred_editor,
	      1);
	editor_caption_text_override_qm = estructure_slot(options,Qtitle,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Editor_caption_text_override_qm,Qeditor_caption_text_override_qm,editor_caption_text_override_qm,
		0);
	  launch_editor_1(7,item,slot_denotation,workstation,line_qm,
		  column_qm,type_of_slot_qm,symbolic_parameter_qm);
	  reclaim_evaluation_structure(options);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    IDENTITY(item_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    IDENTITY(g2_window_as_evaluation_value);
    return VALUES_0();
}

DEFINE_VARIABLE_WITH_SYMBOL(Edit_states, Qedit_states);

DEFINE_VARIABLE_WITH_SYMBOL(Highest_state_index, Qhighest_state_index);

/* G2-UI-LAUNCH-EDITOR-RETURNING-HANDLE */
Object g2_ui_launch_editor_returning_handle(item_as_evaluation_value,
	    options_as_evaluation_value,g2_window_as_evaluation_value)
    Object item_as_evaluation_value, options_as_evaluation_value;
    Object g2_window_as_evaluation_value;
{
    Object item, options, g2_window, value_1, workstation, attribute;
    Object slot_denotation, type_of_slot_qm, symbolic_parameter_qm, line_qm;
    Object column_qm, editor_prompt_filter_qm, override_preferred_editor;
    Object editor_caption_text_override_qm, new_edit_state, temp, svref_arg_2;
    SI_Long i, ab_loop_bind_;
    Declare_special(3);

    x_note_fn_call(225,192);
    item = IDENTITY(item_as_evaluation_value);
    options = IDENTITY(options_as_evaluation_value);
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    value_1 = Nil;
    if ( !TRUEP(ISVREF(g2_window,(SI_Long)20L)))
	ui_stack_error_for_non_connected_window(Qg2_window,
		Qg2_ui_launch_editor);
    check_type_or_stack_error(2,options,Launch_editor_options_type);
    workstation = ISVREF(g2_window,(SI_Long)20L);
    attribute = estructure_slot(options,Qattribute,Qtext);
    slot_denotation = slot_denotation_of_editable_slot_or_stack_error(item,
	    attribute,workstation);
    type_of_slot_qm = 
	    compute_type_of_slot_or_stack_error(estructure_slot(options,
	    Qgrammar,Nil));
    symbolic_parameter_qm = estructure_slot(options,Qsemaphore,Nil);
    line_qm = estructure_slot(options,Qline,FIX((SI_Long)1L));
    column_qm = estructure_slot(options,Qcolumn,FIX((SI_Long)0L));
    editor_prompt_filter_qm = 
	    parse_editor_prompt_filter(estructure_slot(options,Qexclude,Nil));
    PUSH_SPECIAL_WITH_SYMBOL(Editor_prompt_filter_qm,Qeditor_prompt_filter_qm,editor_prompt_filter_qm,
	    2);
      override_preferred_editor = estructure_slot(options,
	      Qpreferred_editor,Nil);
      PUSH_SPECIAL_WITH_SYMBOL(Override_preferred_editor,Qoverride_preferred_editor,override_preferred_editor,
	      1);
	editor_caption_text_override_qm = estructure_slot(options,Qtitle,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Editor_caption_text_override_qm,Qeditor_caption_text_override_qm,editor_caption_text_override_qm,
		0);
	  new_edit_state = Nil;
	  new_edit_state = launch_editor_1(7,item,slot_denotation,
		  workstation,line_qm,column_qm,type_of_slot_qm,
		  symbolic_parameter_qm);
	  reclaim_evaluation_structure(options);
	  if ( !TRUEP(Edit_states)) {
	      Edit_states = 
		      allocate_managed_simple_vector(Maximum_open_editors);
	      i = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(FIXNUM_SUB1(Maximum_open_editors));
	    next_loop:
	      if (i > ab_loop_bind_)
		  goto end_loop;
	      if (Edit_states) {
		  temp = Edit_states;
		  ISVREF(temp,i) = Nil;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	  }
	  if (FIXNUM_GE(Highest_state_index,Maximum_open_editors))
	      Highest_state_index = FIX((SI_Long)0L);
	  else {
	    next_loop_1:
	      if ( !TRUEP(ISVREF(Edit_states,IFIX(Highest_state_index))))
		  goto end_loop_1;
	      temp = FIXNUM_ADD1(Highest_state_index);
	      Highest_state_index = temp;
	      if (FIXNUM_GE(Highest_state_index,
		      FIXNUM_SUB1(Maximum_open_editors)))
		  Highest_state_index = FIX((SI_Long)0L);
	      goto next_loop_1;
	    end_loop_1:;
	  }
	  temp = Edit_states;
	  svref_arg_2 = Highest_state_index;
	  SVREF(temp,svref_arg_2) = new_edit_state;
	  value_1 = Highest_state_index;
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    IDENTITY(item_as_evaluation_value);
    IDENTITY(options_as_evaluation_value);
    IDENTITY(g2_window_as_evaluation_value);
    return VALUES_1(value_1);
}

static Object Qend;                /* end */

/* G2-UI-FINISH-EDITING-SESSION */
Object g2_ui_finish_editing_session(editor_handle_as_evaluation_value,
	    g2_window_as_evaluation_value)
    Object editor_handle_as_evaluation_value, g2_window_as_evaluation_value;
{
    Object editor_handle, g2_window, value_1, ws, es;
    volatile Object retval;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, current_edit_state;
    Object current_edit_workspace, svref_arg_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(225,193);
    SAVE_STACK();
    editor_handle = editor_handle_as_evaluation_value;
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    value_1 = Nil;
    ws = ISVREF(g2_window,(SI_Long)20L);
    es = Nil;
    retval = Nil;
    if (FIXNUM_GT(Maximum_open_editors,editor_handle) && 
	    IFIX(editor_handle) >= (SI_Long)0L)
	es = ISVREF(Edit_states,IFIX(editor_handle));
    if ( ! !TRUEP(es)) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = ws;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		    13);
	      current_workstation_window = ISVREF(Current_workstation,
		      (SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		      12);
		current_g2_window_for_this_workstation_qm = 
			ISVREF(Current_workstation,(SI_Long)25L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			11);
		  type_of_current_workstation_window = 
			  ISVREF(Current_workstation_window,(SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			  10);
		    current_workstation_native_window_qm = 
			    ISVREF(Current_workstation_window,(SI_Long)17L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			    9);
		      temp = ISVREF(Current_workstation,(SI_Long)17L);
		      current_workstation_context = CAR(temp);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			      8);
			type_of_current_workstation_context = 
				ISVREF(Current_workstation_context,
				(SI_Long)1L);
			PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				7);
			  specific_structure_for_current_workstation_context 
				  = ISVREF(Current_workstation_context,
				  (SI_Long)2L);
			  PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				  6);
			    current_workstation_detail_pane = 
				    detail_pane(Current_workstation_window);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				    5);
			      current_g2_user_mode_qm = 
				      ISVREF(Current_workstation,(SI_Long)19L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				      4);
				new_g2_classic_ui_p = 
					get_value_for_current_workstation_new_g2_classic_ui_p();
				PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					3);
				  servicing_workstation_qm = T;
				  PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					  2);
				    current_edit_state = es;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
					    1);
				      current_edit_workspace = 
					      ISVREF(Current_edit_state,
					      (SI_Long)12L);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
					      0);
					retval = 
						extend_parsing_as_appropriate(1,
						Qend);
					if (retval) {
					    svref_arg_1 = Edit_states;
					    SVREF(svref_arg_1,
						    editor_handle) = Nil;
					}
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
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(For_workstation);
	CONTINUE_UNWINDING(0);
    }
    value_1 = retval;
    IDENTITY(g2_window_as_evaluation_value);
    if (FIXNUM_EQ(value_1,Truth))
	temp = Evaluation_true_value;
    else if (FIXNUM_EQ(value_1,Falsity))
	temp = Evaluation_false_value;
    else
	temp = eval_cons_1(value_1,Qtruth_value);
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object Qab_structure;       /* structure */

static Object Qdefining_class;     /* defining-class */

static Object string_constant_34;  /* "The grammar specification ~NV in invalid" */

static Object string_constant_35;  /* " because ~A is not a known class" */

static Object string_constant_36;  /* " because ~A is not an attribute of ~A" */

static Object string_constant_37;  /* "." */

/* COMPUTE-TYPE-OF-SLOT-OR-STACK-ERROR */
Object compute_type_of_slot_or_stack_error(grammar)
    Object grammar;
{
    Object temp, temp_1, temp_2, class_qm, attribute_qm, defining_class_qm;
    Object top_of_stack, text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);
    Object result;

    x_note_fn_call(225,194);
    if (grammar && SYMBOLP(grammar))
	result = VALUES_3(grammar,Qtext,Nil);
    else if (CONSP(grammar) && EQ(M_CDR(grammar),Qab_structure)) {
	temp = estructure_slot(grammar,Qab_class,Nil);
	temp_1 = estructure_slot(grammar,Qattribute,Qtext);
	temp_2 = estructure_slot(grammar,Qdefining_class,Nil);
	result = VALUES_3(temp,temp_1,temp_2);
    }
    else
	result = VALUES_1(Qnil);
    MVS_3(result,class_qm,attribute_qm,defining_class_qm);
    if (class_qm) {
	temp_2 = get_type_of_slot_for_user_edit(class_qm,attribute_qm,
		defining_class_qm);
	if (temp_2);
	else {
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
			  tformat(2,string_constant_34,grammar);
			  if ( 
				  !TRUEP(lookup_global_or_kb_specific_property_value(class_qm,
				  Class_description_gkbprop)))
			      tformat(2,string_constant_35,class_qm);
			  else if ( 
				  !TRUEP(get_slot_description_of_class_description_function(attribute_qm,
				  lookup_global_or_kb_specific_property_value(class_qm,
				  Class_description_gkbprop),Nil)))
			      tformat(3,string_constant_36,attribute_qm,
				      class_qm);
			  tformat(1,string_constant_37);
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
	    temp_2 = raw_stack_error_named_error(top_of_stack,message_1);
	}
	return coerce_to_free_text_type_of_slot(temp_2);
    }
    else
	return VALUES_1(Nil);
}

/* PARSE-EDITOR-PROMPT-FILTER */
Object parse_editor_prompt_filter(filter)
    Object filter;
{
    Object gensymed_symbol, held_vector, element, result_qm, ab_loop_it_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(225,195);
    if (CONSP(filter) && EQ(M_CDR(filter),Qsequence)) {
	gensymed_symbol = filter;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	element = Nil;
	result_qm = Nil;
	ab_loop_it_ = Nil;
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
	element = validated_elt;
	if (element && SYMBOLP(element))
	    result_qm = gensym_cons_1(element,Nil);
	else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(element) != (SI_Long)0L)
	    result_qm = read_symbol_list_from_text_string(element);
	else
	    result_qm = Qnil;
	ab_loop_it_ = result_qm;
	if (ab_loop_it_) {
	    ab_loopvar__2 = gensym_cons_1(ab_loop_it_,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant_1;     /* # */

/* READ-SYMBOL-LIST-FROM-TEXT-STRING */
Object read_symbol_list_from_text_string(text_string)
    Object text_string;
{
    Object token_qm, type_of_token_qm, next_qm, start_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, token_value;
    Object token_type_or_partial_types, character_index_after_token;
    Object result;

    x_note_fn_call(225,196);
    token_qm = Nil;
    type_of_token_qm = Nil;
    next_qm = Nil;
    start_qm = FIX((SI_Long)0L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    result = token_from_text_string(text_string,start_qm,Nil);
    MVS_3(result,token_value,token_type_or_partial_types,
	    character_index_after_token);
    if (CONSP(token_type_or_partial_types) || 
	    memq_function(token_type_or_partial_types,list_constant_1))
	result = VALUES_3(Nil,Nil,Nil);
    else
	result = VALUES_3(token_value,token_type_or_partial_types,
		character_index_after_token);
    MVS_3(result,token_qm,type_of_token_qm,next_qm);
    if ( !TRUEP(token_qm))
	goto end_loop;
    if (SYMBOLP(token_qm)) {
	ab_loopvar__2 = gensym_cons_1(token_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else
	reclaim_slot_value(token_qm);
    start_qm = next_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object string_constant_38;  /* "There is no edit in progress on ~NF ~NF." */

/* G2-UI-GET-TEXT-FROM-CURRENT-EDITOR */
Object g2_ui_get_text_from_current_editor(g2_window)
    Object g2_window;
{
    Object gensym_window, workstation, edit_state, top_of_stack, message_1;
    Object edit_text;

    x_note_fn_call(225,197);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    edit_state = find_current_edit_state(workstation);
    if (edit_state);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_38,
		g2_window,workstation);
	edit_state = raw_stack_error_named_error(top_of_stack,message_1);
    }
    edit_text = ISVREF(edit_state,(SI_Long)15L);
    return convert_text_to_text_string(1,edit_text);
}

static Object string_constant_39;  /* "There is no edit in progress on ~NF." */

/* G2-UI-INSERT-TEXT-INTO-CURRENT-EDITOR */
Object g2_ui_insert_text_into_current_editor(text,options,g2_window)
    Object text, options, g2_window;
{
    Object gensym_window, workstation, edit_state, top_of_stack, message_1;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, current_edit_state;
    Object current_edit_workspace;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(225,198);
    SAVE_STACK();
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    workstation = ISVREF(gensym_window,(SI_Long)2L);
    edit_state = find_current_edit_state(workstation);
    if (edit_state);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_39,
		g2_window);
	edit_state = raw_stack_error_named_error(top_of_stack,message_1);
    }
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		13);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  12);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    11);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      10);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			9);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  8);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    7);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      6);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				5);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  4);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    3);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      2);
				current_edit_state = edit_state;
				PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
					1);
				  current_edit_workspace = 
					  ISVREF(Current_edit_state,
					  (SI_Long)12L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
					  0);
				    insert_text_string_at_cursor(3,text,
					    Nil,Nil);
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    reclaim_text_string(text);
    result = reclaim_evaluation_value(options);
    RESTORE_STACK();
    return result;
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

static Object Qg2_defstruct_structure_name_edit_state_g2_struct;  /* g2-defstruct-structure-name::edit-state-g2-struct */

/* FIND-CURRENT-EDIT-STATE */
Object find_current_edit_state(workstation)
    Object workstation;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, ws, ab_loop_list_;
    Object state_1, gensymed_symbol, gensymed_symbol_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(225,199);
    SAVE_STACK();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				ws = Nil;
				ab_loop_list_ = ISVREF(workstation,
					(SI_Long)17L);
				state_1 = Nil;
			      next_loop:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop;
				ws = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				state_1 = ISVREF(ws,(SI_Long)2L);
				gensymed_symbol = ISVREF(state_1,(SI_Long)0L);
				gensymed_symbol = 
					ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
					Qtype_description_of_unique_type_name_of_gensym_structure),
					(SI_Long)9L),(SI_Long)4L);
				gensymed_symbol_1 = state_1;
				if (inline_funcall_1(gensymed_symbol,
					gensymed_symbol_1) ? 
					SIMPLE_VECTOR_P(state_1) && 
					EQ(ISVREF(state_1,(SI_Long)0L),
					Qg2_defstruct_structure_name_edit_state_g2_struct) 
					: TRUEP(Nil)) {
				    SAVE_VALUES(VALUES_1(state_1));
				    goto end_1;
				}
				goto next_loop;
			      end_loop:
				SAVE_VALUES(VALUES_1(Qnil));
			      end_1:;
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qui_client_session;  /* ui-client-session */

static Object string_constant_40;  /* "The use of a ui-client-session in g2-system-command is not yet supported" */

static Object Qg2_system_command;  /* g2-system-command */

static Object Qg2_user_mode;       /* g2-user-mode */

static Object Qadministrator;      /* administrator */

/* G2-SYSTEM-COMMAND */
Object g2_system_command(command_name_as_evaluation_value,
	    g2_window_as_evaluation_value,item_as_evaluation_value,
	    attribute_name_as_evaluation_value)
    Object command_name_as_evaluation_value, g2_window_as_evaluation_value;
    Object item_as_evaluation_value, attribute_name_as_evaluation_value;
{
    Object command_name, g2_window, item, attribute_name, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, top_of_stack, message_1;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp_1;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(13);
    Object result;

    x_note_fn_call(225,200);
    SAVE_STACK();
    command_name = command_name_as_evaluation_value;
    g2_window = IDENTITY(g2_window_as_evaluation_value);
    item = IDENTITY(item_as_evaluation_value);
    attribute_name = attribute_name_as_evaluation_value;
    if (SIMPLE_VECTOR_P(g2_window) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L &&  
	    !EQ(ISVREF(g2_window,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(g2_window,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	gensymed_symbol_1 = 
		lookup_global_or_kb_specific_property_value(Qui_client_session,
		Class_description_gkbprop);
	if (gensymed_symbol_1) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
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
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_40);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    else {
	if (SIMPLE_VECTOR_P(g2_window) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(g2_window)) > (SI_Long)2L 
		&&  !EQ(ISVREF(g2_window,(SI_Long)1L),
		    Qavailable_frame_vector)) {
	    x2 = ISVREF(g2_window,(SI_Long)1L);
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
		    IFIX(ISVREF(G2_window_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp)
	    system_procedure_argument_list_error(Qwindow,
		    Qg2_system_command,Qg2_window,g2_window);
	else if ( !TRUEP(ISVREF(g2_window,(SI_Long)20L)))
	    ui_stack_error_for_non_connected_window(Qg2_window,
		    Qg2_system_command);
	else {
	    LOCK(For_workstation);
	    if (PUSH_UNWIND_PROTECT(0)) {
		current_workstation_1 = ISVREF(g2_window,(SI_Long)20L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
			12);
		  current_workstation_window = ISVREF(Current_workstation,
			  (SI_Long)1L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
			  11);
		    current_g2_window_for_this_workstation_qm = 
			    ISVREF(Current_workstation,(SI_Long)25L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
			    10);
		      type_of_current_workstation_window = 
			      ISVREF(Current_workstation_window,(SI_Long)1L);
		      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
			      9);
			current_workstation_native_window_qm = 
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
				8);
			  temp_1 = ISVREF(Current_workstation,(SI_Long)17L);
			  current_workstation_context = CAR(temp_1);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
				  7);
			    type_of_current_workstation_context = 
				    ISVREF(Current_workstation_context,
				    (SI_Long)1L);
			    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
				    6);
			      specific_structure_for_current_workstation_context 
				      = ISVREF(Current_workstation_context,
				      (SI_Long)2L);
			      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
				      5);
				current_workstation_detail_pane = 
					detail_pane(Current_workstation_window);
				PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
					4);
				  current_g2_user_mode_qm = 
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  3);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    2);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      1);
					temp_1 = 
						get_lookup_slot_value_given_default(g2_window,
						Qg2_user_mode,Nil);
					if (temp_1);
					else
					    temp_1 = Qadministrator;
					current_g2_user_mode_qm = temp_1;
					PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
						0);
					  g2_system_command_1(command_name,
						  g2_window,item,
						  attribute_name);
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
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	}
    }
    IDENTITY(g2_window_as_evaluation_value);
    IDENTITY(item_as_evaluation_value);
    result = VALUES_0();
    RESTORE_STACK();
    return result;
}

static Object Qui_command_named;   /* ui-command-named */

static Object list_constant_2;     /* # */

static Object Qabort_user_mouse_tracking;  /* abort-user-mouse-tracking */

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Qchange_size;        /* change-size */

static Object Qtransfer;           /* transfer */

static Object string_constant_41;  /* "The item ~NF is not transferrable, cannot do ~a command." */

static Object Qclone;              /* clone */

static Object string_constant_42;  /* "The item ~NF is not clonable, cannot do ~a command." */

static Object list_constant_6;     /* # */

static Object string_constant_43;  /* "The item ~NF is not showing, cannot do ~a command." */

static Object string_constant_44;  /* "The item ~NF is not be deleteable, cannot do ~a command." */

static Object Qredo_layout;        /* redo-layout */

static Object Qredo_layout_of_g2gl_body;  /* redo-layout-of-g2gl-body */

static Object string_constant_45;  /* "The item ~NF is not a G2GL body workspace, cannot do ~a command." */

static Object Qrestore_to_normal_size;  /* restore-to-normal-size */

static Object Qedit_icon;          /* edit-icon */

static Object Qitem;               /* item */

static Object string_constant_46;  /* "the EDIT-ICON case of G2-SYSTEM-COMMAND" */

static Object Qclass_definition;   /* class-definition */

static Object Qedit;               /* edit */

static Object string_constant_47;  /* "The ~a argument of ~a received ~a, which does not name a system command." */

static Object Qcommand_name;       /* command-name */

/* G2-SYSTEM-COMMAND-1 */
Object g2_system_command_1(command_name,g2_window,item,attribute_name)
    Object command_name, g2_window, item, attribute_name;
{
    Object workspace_qm, gensym_window, image_plane_qm, gensymed_symbol;
    Object image_plane, scale, x_in_window_qm, y_in_window_qm, ui_command;
    Object temp, x2, top_of_stack, message_1, top_plane, sub_class_bit_vector;
    Object workstation, slot_denotation;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, x_in_workspace, value;
    SI_Long unshifted_result, y_in_workspace, x, y, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(225,201);
    workspace_qm = get_workspace_if_any(item);
    gensym_window = get_gensym_window_for_g2_window(g2_window);
    image_plane_qm = workspace_qm ? image_plane_of_workspace(workspace_qm) 
	    : Qnil;
    if (image_plane_qm) {
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	x_in_workspace = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	image_plane = image_plane_qm;
	gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
	scale = ISVREF(image_plane,(SI_Long)11L);
	value = x_in_workspace;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
	x_in_window_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    else
	x_in_window_qm = Nil;
    if (image_plane_qm) {
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(item,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)1L;
	y_in_workspace = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	image_plane = image_plane_qm;
	gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
	scale = ISVREF(image_plane,(SI_Long)12L);
	value = y_in_workspace;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,FIX(value)));
	y_in_window_qm = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    else
	y_in_window_qm = Nil;
    if (EQ(command_name,Qrefresh)) {
	if (global_keyboard_command_permitted_p(command_name)) {
	    ui_command = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
		    Qui_command_named);
	    if (ui_command) {
		gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		temp = SYMBOLP(gensymed_symbol) ? 
			SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
		return FUNCALL_1(temp,Current_workstation_window);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qclose_telewindows_connection)) {
	if (main_menu_command_permitted_p(command_name)) {
	    if (EQ(Type_of_current_workstation_window,Qicp))
		return close_telewindows_connection(Current_workstation_window);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qlog_out)) {
	if (main_menu_command_permitted_p(command_name)) {
	    if (Relations_tag_list)
		return log_out_workstation(Current_workstation);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qhelp)) {
	if (global_keyboard_command_permitted_p(command_name)) {
	    ui_command = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
		    Qui_command_named);
	    if (ui_command) {
		gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		return FUNCALL_0(SYMBOLP(gensymed_symbol) ? 
			SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (member_eql(command_name,list_constant_2)) {
	if (main_menu_command_permitted_p(command_name)) {
	    ui_command = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
		    Qui_command_named);
	    if (ui_command) {
		gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		return FUNCALL_0(SYMBOLP(gensymed_symbol) ? 
			SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qabort_user_mouse_tracking))
	return abort_user_mouse_tracking_on_current_workstation();
    else if (member_eql(command_name,list_constant_3)) {
	if (image_plane_qm)
	    return handle_image_plane_event(command_name,image_plane_qm,
		    x_in_window_qm,y_in_window_qm);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qlift_to_top) || EQ(command_name,
	    Qdrop_to_bottom) || EQ(command_name,Qtoggle_visible_grid)) {
	if (image_plane_qm && 
		global_keyboard_command_permitted_p(command_name)) {
	    if (EQ(command_name,Qlift_to_top))
		return raise_image_plane_to_top(1,image_plane_qm);
	    else if (EQ(command_name,Qdrop_to_bottom))
		return lower_image_plane_to_bottom(image_plane_qm);
	    else if (EQ(command_name,Qtoggle_visible_grid))
		return toggle_visible_grid(image_plane_qm);
	    else
		return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qcirculate_up) || EQ(command_name,
	    Qcirculate_down)) {
	if (global_keyboard_command_permitted_p(command_name)) {
	    if (EQ(command_name,Qcirculate_up))
		return circulate_up(Current_workstation_detail_pane);
	    else
		return circulate_down(Current_workstation_detail_pane);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (member_eql(command_name,list_constant_4)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if (gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L) ? 
		TRUEP(item_menu_command_permitted_p(command_name,item)) : 
		TRUEP(Nil)) {
	    if (member_eql(command_name,list_constant_5)) {
		if (image_plane_qm) {
		    if (EQ(command_name,Qchange_size)) {
			ui_command = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
				Qui_command_named);
			if (ui_command) {
			    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			    temp = SYMBOLP(gensymed_symbol) ? 
				    SYMBOL_FUNCTION(gensymed_symbol) : 
				    gensymed_symbol;
			    return FUNCALL_5(temp,item,image_plane_qm,
				    x_in_window_qm,y_in_window_qm,
				    gensym_window);
			}
			else
			    return VALUES_1(Nil);
		    }
		    else if (EQ(command_name,Qtransfer)) {
			if (block_transferable_via_ui_command_p(item)) {
			    ui_command = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
				    Qui_command_named);
			    if (ui_command) {
				gensymed_symbol = ISVREF(ui_command,
					(SI_Long)4L);
				temp = SYMBOLP(gensymed_symbol) ? 
					SYMBOL_FUNCTION(gensymed_symbol) : 
					gensymed_symbol;
				return FUNCALL_4(temp,item,x_in_window_qm,
					y_in_window_qm,image_plane_qm);
			    }
			    else
				return VALUES_1(Nil);
			}
			else {
			    top_of_stack = Cached_top_of_stack;
			    message_1 = tformat_stack_error_text_string(3,
				    string_constant_41,item,command_name);
			    return raw_stack_error_named_error(top_of_stack,
				    message_1);
			}
		    }
		    else if (EQ(command_name,Qclone)) {
			if (block_clonable_via_ui_command_p(item)) {
			    ui_command = 
				    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
				    Qui_command_named);
			    if (ui_command) {
				gensymed_symbol = ISVREF(ui_command,
					(SI_Long)4L);
				temp = SYMBOLP(gensymed_symbol) ? 
					SYMBOL_FUNCTION(gensymed_symbol) : 
					gensymed_symbol;
				return FUNCALL_4(temp,item,x_in_window_qm,
					y_in_window_qm,image_plane_qm);
			    }
			    else
				return VALUES_1(Nil);
			}
			else {
			    top_of_stack = Cached_top_of_stack;
			    message_1 = tformat_stack_error_text_string(3,
				    string_constant_42,item,command_name);
			    return raw_stack_error_named_error(top_of_stack,
				    message_1);
			}
		    }
		    else {
			ui_command = 
				getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
				Qui_command_named);
			if (ui_command) {
			    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			    temp = SYMBOLP(gensymed_symbol) ? 
				    SYMBOL_FUNCTION(gensymed_symbol) : 
				    gensymed_symbol;
			    return FUNCALL_3(temp,item,x_in_window_qm,
				    y_in_window_qm);
			}
			else
			    return VALUES_1(Nil);
		    }
		}
		else if (memq_function(command_name,list_constant_6)) {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_43,item,command_name);
		    return raw_stack_error_named_error(top_of_stack,message_1);
		}
		else {
		    temp = ISVREF(Current_workstation_detail_pane,(SI_Long)5L);
		    top_plane = FIRST(temp);
		    x = IFIX(FIXNUM_ADD(ISVREF(top_plane,(SI_Long)6L),
			    ISVREF(top_plane,(SI_Long)8L))) >>  -  - 
			    (SI_Long)1L;
		    y = IFIX(FIXNUM_ADD(ISVREF(top_plane,(SI_Long)7L),
			    ISVREF(top_plane,(SI_Long)9L))) >>  -  - 
			    (SI_Long)1L;
		    ui_command = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
			    Qui_command_named);
		    if (ui_command) {
			gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			temp = SYMBOLP(gensymed_symbol) ? 
				SYMBOL_FUNCTION(gensymed_symbol) : 
				gensymed_symbol;
			return FUNCALL_3(temp,item,FIX(x),FIX(y));
		    }
		    else
			return VALUES_1(Nil);
		}
	    }
	    else if (EQ(command_name,Qdelete)) {
		if (item_may_be_deleted_by_user(item)) {
		    ui_command = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
			    Qui_command_named);
		    if (ui_command) {
			gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			temp = SYMBOLP(gensymed_symbol) ? 
				SYMBOL_FUNCTION(gensymed_symbol) : 
				gensymed_symbol;
			return FUNCALL_1(temp,item);
		    }
		    else
			return VALUES_1(Nil);
		}
		else {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_44,item,command_name);
		    return raw_stack_error_named_error(top_of_stack,message_1);
		}
	    }
	    else if (EQ(command_name,Qredo_layout)) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Kb_workspace_class_description,
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
		    temp_1 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1 ? 
			TRUEP(get_g2gl_process_parent_of_workspace_if_any(1,
			item)) : TRUEP(Nil)) {
		    ui_command = 
			    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qredo_layout_of_g2gl_body),
			    Qui_command_named);
		    if (ui_command) {
			gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
			temp = SYMBOLP(gensymed_symbol) ? 
				SYMBOL_FUNCTION(gensymed_symbol) : 
				gensymed_symbol;
			return FUNCALL_1(temp,item);
		    }
		    else
			return VALUES_1(Nil);
		}
		else {
		    top_of_stack = Cached_top_of_stack;
		    message_1 = tformat_stack_error_text_string(3,
			    string_constant_45,item,command_name);
		    return raw_stack_error_named_error(top_of_stack,message_1);
		}
	    }
	    else if (EQ(command_name,Qrestore_to_normal_size)) {
		ui_command = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
			Qui_command_named);
		if (ui_command) {
		    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		    temp = SYMBOLP(gensymed_symbol) ? 
			    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
		    return FUNCALL_2(temp,item,gensym_window);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else {
		ui_command = 
			getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
			Qui_command_named);
		if (ui_command) {
		    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		    temp = SYMBOLP(gensymed_symbol) ? 
			    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
		    return FUNCALL_1(temp,item);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command_name,Qedit_icon)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
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
		    IFIX(ISVREF(Class_definition_class_description,
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
	}
	else
	    temp_1 = TRUEP(Nil);
	if ( !temp_1)
	    return system_procedure_argument_list_error(Qitem,
		    string_constant_46,Qclass_definition,g2_window);
	else if (item_menu_command_permitted_p(command_name,item)) {
	    ui_command = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(command_name),
		    Qui_command_named);
	    if (ui_command) {
		gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
		temp = SYMBOLP(gensymed_symbol) ? 
			SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
		return FUNCALL_1(temp,item);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Qnil);
    }
    else if (EQ(command_name,Qedit)) {
	if (SIMPLE_VECTOR_P(item) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item)) 
		> (SI_Long)2L &&  !EQ(ISVREF(item,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	if ((gensymed_symbol && ISVREF(gensymed_symbol,(SI_Long)16L) ? 
		TRUEP(attribute_name) : TRUEP(Nil)) ? 
		SYMBOLP(attribute_name) : TRUEP(Nil)) {
	    workstation = ISVREF(g2_window,(SI_Long)20L);
	    slot_denotation = 
		    slot_denotation_of_editable_slot_or_stack_error(item,
		    attribute_name,workstation);
	    return launch_editor_1(3,item,slot_denotation,workstation);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(4,string_constant_47,
		Qcommand_name,Qg2_system_command,command_name);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object list_constant_7;     /* # */

/* G2-COMMAND-IS-ENABLED */
Object g2_command_is_enabled(command,item,g2_window)
    Object command, item, g2_window;
{
    Object gensym_window;

    x_note_fn_call(225,202);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    check_type_or_stack_error(2,command,list_constant_7);
    if (command_enabled_for_ui_p(3,command,ISVREF(gensym_window,
	    (SI_Long)2L),item))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* COMMAND-ENABLED-FOR-UI-P */
Object command_enabled_for_ui_p varargs_1(int, n)
{
    Object command, workstation;
    Object item_qm, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(225,203);
    INIT_ARGS_nonrelocating();
    command = REQUIRED_ARG_nonrelocating();
    workstation = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    item_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = workstation;
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      0);
				if (SIMPLE_VECTOR_P(command) && 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(command)) 
					> (SI_Long)2L &&  
					!EQ(ISVREF(command,(SI_Long)1L),
					Qavailable_frame_vector)) {
				    x2 = ISVREF(command,(SI_Long)1L);
				    gensymed_symbol = SIMPLE_VECTOR_P(x2) 
					    && EQ(ISVREF(x2,(SI_Long)0L),
					    Qg2_defstruct_structure_name_class_description_g2_struct) 
					    ? x2 : Qnil;
				}
				else
				    gensymed_symbol = Nil;
				if (gensymed_symbol) {
				    sub_class_bit_vector = 
					    ISVREF(gensymed_symbol,
					    (SI_Long)19L);
				    superior_class_bit_number = 
					    IFIX(ISVREF(User_menu_choice_class_description,
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
					temp_1 = (SI_Long)0L < 
						gensymed_symbol_1;
				    }
				    else
					temp_1 = TRUEP(Nil);
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1) {
				    if (item_qm && 
					    user_menu_choice_runnable_p(command,
					    item_qm))
					SAVE_VALUES(item_menu_command_permitted_p(ISVREF(command,
						(SI_Long)20L),item_qm));
				    else
					SAVE_VALUES(VALUES_1(Nil));
				}
				else if ( !SYMBOLP(command))
				    SAVE_VALUES(VALUES_1(Nil));
				else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(command),
					Qui_command_named)) {
				    if (command_applicable_p(2,command,
					    item_qm))
					SAVE_VALUES(command_unrestricted_p(2,
						command,item_qm));
				    else
					SAVE_VALUES(VALUES_1(Nil));
				}
				else
				    SAVE_VALUES(command_unrestricted_p(2,
					    command,item_qm));
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* COMMAND-APPLICABLE-P */
Object command_applicable_p varargs_1(int, n)
{
    Object command;
    Object item_qm, mouse_pointer, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(225,204);
    INIT_ARGS_nonrelocating();
    command = REQUIRED_ARG_nonrelocating();
    item_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    mouse_pointer = synthesize_mouse_pointer(3,Current_workstation,item_qm,
	    FIX((SI_Long)768L));
    temp = command_available_p(command,mouse_pointer);
    release_mouse_pointer_if_any(mouse_pointer);
    return VALUES_1(temp);
}

/* COMMAND-UNRESTRICTED-P */
Object command_unrestricted_p varargs_1(int, n)
{
    Object command;
    Object item_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(225,205);
    INIT_ARGS_nonrelocating();
    command = REQUIRED_ARG_nonrelocating();
    item_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (memq_function(command,Main_menu_choices))
	return main_menu_command_permitted_p(command);
    else if (memq_function(command,Global_keyboard_command_choices))
	return global_keyboard_command_permitted_p(command);
    else if (memq_function(command,Non_menu_choices))
	return non_menu_choice_permitted_p(command,item_qm);
    else if (item_qm)
	return item_menu_command_permitted_p(command,item_qm);
    else
	return VALUES_1(Qnil);
}

static Object Qplot_names;         /* plot-names */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object list_constant_8;     /* # */

/* UNMANGLE-SLOT-COMPONENT-ALIAS */
Object unmangle_slot_component_alias(slot_denotation)
    Object slot_denotation;
{
    x_note_fn_call(225,206);
    if (EQ(slot_denotation,Qplot_names))
	slot_denotation = Qname_or_names_for_frame;
    else if (EQUAL(slot_denotation,list_constant_8))
	M_THIRD(slot_denotation) = Qname_or_names_for_frame;
    return VALUES_1(slot_denotation);
}

static Object Qoperate_on_area;    /* operate-on-area */

/* G2-LAUNCH-OPERATE-ON-AREA */
Object g2_launch_operate_on_area(kb_workspace,g2_window,x_in_workspace,
	    y_in_workspace)
    Object kb_workspace, g2_window, x_in_workspace, y_in_workspace;
{
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, image_plane_qm;
    Object x_in_window, y_in_window, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, scale;
    Object ui_command, gensymed_symbol_2;
    SI_Long initial_half_extent_of_bounding_box, gensymed_symbol, value;
    SI_Long gensymed_symbol_1, unshifted_result;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(17);
    Object result;

    x_note_fn_call(225,207);
    SAVE_STACK();
    LOCK(For_workstation);
    if (PUSH_UNWIND_PROTECT(0)) {
	current_workstation_1 = ISVREF(g2_window,(SI_Long)20L);
	PUSH_SPECIAL_WITH_SYMBOL(Current_workstation,Qcurrent_workstation,current_workstation_1,
		16);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_window,Qcurrent_workstation_window,current_workstation_window,
		  15);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_g2_window_for_this_workstation_qm,Qcurrent_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    14);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_window,Qtype_of_current_workstation_window,type_of_current_workstation_window,
		      13);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_native_window_qm,Qcurrent_workstation_native_window_qm,current_workstation_native_window_qm,
			12);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_context,Qcurrent_workstation_context,current_workstation_context,
			  11);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_workstation_context,Qtype_of_current_workstation_context,type_of_current_workstation_context,
			    10);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Specific_structure_for_current_workstation_context,Qspecific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      9);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL_WITH_SYMBOL(Current_workstation_detail_pane,Qcurrent_workstation_detail_pane,current_workstation_detail_pane,
				8);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
				  7);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
				    6);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
				      5);
				image_plane_qm = 
					image_plane_of_workspace_on_window(ISVREF(Current_workstation,
					(SI_Long)1L),kb_workspace);
				initial_half_extent_of_bounding_box = 
					(SI_Long)50L;
				x_in_window = Nil;
				y_in_window = Nil;
				current_frame_transform_qm = Nil;
				current_image_x_scale = 
					ISVREF(image_plane_qm,(SI_Long)11L);
				current_image_y_scale = 
					ISVREF(image_plane_qm,(SI_Long)12L);
				current_x_origin_of_drawing = 
					ISVREF(image_plane_qm,(SI_Long)13L);
				current_y_origin_of_drawing = 
					ISVREF(image_plane_qm,(SI_Long)14L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
					4);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
					  3);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
					    2);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
					      1);
					PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
						0);
					  gensymed_symbol = 
						  IFIX(Current_x_origin_of_drawing);
					  scale = Current_image_x_scale;
					  value = IFIX(x_in_workspace) - 
						  initial_half_extent_of_bounding_box;
					  if (IFIX(scale) == (SI_Long)4096L)
					      gensymed_symbol_1 = value;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  scale) && 
						  FIXNUM_LT(scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < value && value < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(scale) * value 
						      + (SI_Long)2048L;
					      gensymed_symbol_1 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_1 = 
						      IFIX(scalef_function(scale,
						      FIX(value)));
					  x_in_window = 
						  FIX(gensymed_symbol + 
						  gensymed_symbol_1);
					  gensymed_symbol = 
						  IFIX(Current_y_origin_of_drawing);
					  scale = Current_image_y_scale;
					  value = 
						  IFIX(FIXNUM_NEGATE(y_in_workspace)) 
						  - 
						  initial_half_extent_of_bounding_box;
					  if (IFIX(scale) == (SI_Long)4096L)
					      gensymed_symbol_1 = value;
					  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						  scale) && 
						  FIXNUM_LT(scale,
						  Isqrt_of_most_positive_fixnum) 
						  && 
						  IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						  < value && value < 
						  IFIX(Isqrt_of_most_positive_fixnum)) 
						      {
					      unshifted_result = 
						      IFIX(scale) * value 
						      + (SI_Long)2048L;
					      gensymed_symbol_1 = 
						      unshifted_result >>  
						      -  - (SI_Long)12L;
					  }
					  else
					      gensymed_symbol_1 = 
						      IFIX(scalef_function(scale,
						      FIX(value)));
					  y_in_window = 
						  FIX(gensymed_symbol + 
						  gensymed_symbol_1);
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				ui_command = 
					getfq_function_no_default(INLINE_SYMBOL_PLIST(Qoperate_on_area),
					Qui_command_named);
				if (ui_command) {
				    gensymed_symbol_2 = ISVREF(ui_command,
					    (SI_Long)4L);
				    temp = SYMBOLP(gensymed_symbol_2) ? 
					    SYMBOL_FUNCTION(gensymed_symbol_2) 
					    : gensymed_symbol_2;
				    SAVE_VALUES(FUNCALL_4(temp,
					    kb_workspace,image_plane_qm,
					    x_in_window,y_in_window));
				}
				else
				    SAVE_VALUES(VALUES_1(Nil));
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
    }
    POP_UNWIND_PROTECT(0);
    UNLOCK(For_workstation);
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* COM-DO-SCROLLING */
Object com_do_scrolling(stepper_of_scroll_bar_spot,block,image_plane)
    Object stepper_of_scroll_bar_spot, block, image_plane;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4;

    x_note_fn_call(225,208);
    if (stepper_of_scroll_bar_spot && of_class_p_function(block,Qblock) && 
	    valid_image_plane_p(image_plane)) {
	if (block_is_allowed_to_have_frame_p(block)) {
	    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)24L),(SI_Long)1L);
	    gensymed_symbol_1 = block;
	    gensymed_symbol_2 = image_plane;
	    gensymed_symbol_3 = ISVREF(stepper_of_scroll_bar_spot,
		    (SI_Long)11L);
	    gensymed_symbol_4 = ISVREF(stepper_of_scroll_bar_spot,
		    (SI_Long)10L);
	    return inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qstepper_of_scroll_bar_spot;  /* stepper-of-scroll-bar-spot */

static Object Qspot;               /* spot */

/* DO-SCROLLING-COMMAND-PURSUER */
Object do_scrolling_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, stepper_of_scroll_bar_spot, block, image_plane;

    x_note_fn_call(225,209);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    stepper_of_scroll_bar_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    block = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    image_plane = CAR(gensymed_symbol);
    stepper_of_scroll_bar_spot = 
	    command_argument_value(stepper_of_scroll_bar_spot);
    block = command_argument_value(block);
    image_plane = command_argument_value(image_plane);
    if (EQ(stepper_of_scroll_bar_spot,Plus_missing_argument_plus))
	return VALUES_3(Qstepper_of_scroll_bar_spot,Qspot,FIX((SI_Long)0L));
    else if (EQ(block,Plus_missing_argument_plus))
	return VALUES_3(Qblock,Qblock,FIX((SI_Long)1L));
    else if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qdo_scrolling;       /* do-scrolling */

/* DO-SCROLLING-COMMAND-TRANSLATOR */
Object do_scrolling_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object stepper_of_scroll_bar_spot, block, image_plane, temp, temp_1;
    Object temp_2;

    x_note_fn_call(225,210);
    stepper_of_scroll_bar_spot = spot_blackboard_function(mouse_pointer);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    if (stepper_of_scroll_bar_spot && block && image_plane) {
	if (T) {
	    temp = stepper_of_scroll_bar_spot;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = block;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qdo_scrolling,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfull_scale;         /* full-scale */

/* COM-FULL-SCALE */
Object com_full_scale(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,211);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qfull_scale,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

static Object Qx_in_window;        /* x-in-window */

static Object Qy_in_window;        /* y-in-window */

/* FULL-SCALE-COMMAND-PURSUER */
Object full_scale_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,212);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* FULL-SCALE-COMMAND-TRANSLATOR */
Object full_scale_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,213);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qfull_scale,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qnormalized_full_scale;  /* normalized-full-scale */

/* COM-NORMALIZED-FULL-SCALE */
Object com_normalized_full_scale(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,214);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qnormalized_full_scale,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* NORMALIZED-FULL-SCALE-COMMAND-PURSUER */
Object normalized_full_scale_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,215);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* NORMALIZED-FULL-SCALE-COMMAND-TRANSLATOR */
Object normalized_full_scale_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,216);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qnormalized_full_scale,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qscale_to_fit;       /* scale-to-fit */

/* COM-SCALE-TO-FIT */
Object com_scale_to_fit(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,217);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qscale_to_fit,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SCALE-TO-FIT-COMMAND-PURSUER */
Object scale_to_fit_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,218);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SCALE-TO-FIT-COMMAND-TRANSLATOR */
Object scale_to_fit_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,219);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qscale_to_fit,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmaximum_scale_to_fit;  /* maximum-scale-to-fit */

/* COM-MAXIMUM-SCALE-TO-FIT */
Object com_maximum_scale_to_fit(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,220);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qmaximum_scale_to_fit,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* MAXIMUM-SCALE-TO-FIT-COMMAND-PURSUER */
Object maximum_scale_to_fit_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,221);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* MAXIMUM-SCALE-TO-FIT-COMMAND-TRANSLATOR */
Object maximum_scale_to_fit_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,222);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmaximum_scale_to_fit,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qone_quarter_the_scale;  /* one-quarter-the-scale */

/* COM-ONE-QUARTER-THE-SCALE */
Object com_one_quarter_the_scale(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,223);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qone_quarter_the_scale,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* ONE-QUARTER-THE-SCALE-COMMAND-PURSUER */
Object one_quarter_the_scale_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,224);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* ONE-QUARTER-THE-SCALE-COMMAND-TRANSLATOR */
Object one_quarter_the_scale_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,225);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qone_quarter_the_scale,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfour_times_the_scale;  /* four-times-the-scale */

/* COM-FOUR-TIMES-THE-SCALE */
Object com_four_times_the_scale(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,226);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qfour_times_the_scale,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* FOUR-TIMES-THE-SCALE-COMMAND-PURSUER */
Object four_times_the_scale_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,227);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* FOUR-TIMES-THE-SCALE-COMMAND-TRANSLATOR */
Object four_times_the_scale_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,228);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qfour_times_the_scale,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtwenty_percent_smaller;  /* twenty-percent-smaller */

/* COM-TWENTY-PERCENT-SMALLER */
Object com_twenty_percent_smaller(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,229);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qtwenty_percent_smaller,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* TWENTY-PERCENT-SMALLER-COMMAND-PURSUER */
Object twenty_percent_smaller_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,230);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* TWENTY-PERCENT-SMALLER-COMMAND-TRANSLATOR */
Object twenty_percent_smaller_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,231);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtwenty_percent_smaller,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtwenty_percent_bigger;  /* twenty-percent-bigger */

/* COM-TWENTY-PERCENT-BIGGER */
Object com_twenty_percent_bigger(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,232);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qtwenty_percent_bigger,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* TWENTY-PERCENT-BIGGER-COMMAND-PURSUER */
Object twenty_percent_bigger_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,233);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* TWENTY-PERCENT-BIGGER-COMMAND-TRANSLATOR */
Object twenty_percent_bigger_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,234);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtwenty_percent_bigger,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtwenty_percent_narrower;  /* twenty-percent-narrower */

/* COM-TWENTY-PERCENT-NARROWER */
Object com_twenty_percent_narrower(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,235);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qtwenty_percent_narrower,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* TWENTY-PERCENT-NARROWER-COMMAND-PURSUER */
Object twenty_percent_narrower_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,236);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* TWENTY-PERCENT-NARROWER-COMMAND-TRANSLATOR */
Object twenty_percent_narrower_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,237);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtwenty_percent_narrower,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtwenty_percent_wider;  /* twenty-percent-wider */

/* COM-TWENTY-PERCENT-WIDER */
Object com_twenty_percent_wider(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,238);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qtwenty_percent_wider,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* TWENTY-PERCENT-WIDER-COMMAND-PURSUER */
Object twenty_percent_wider_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,239);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* TWENTY-PERCENT-WIDER-COMMAND-TRANSLATOR */
Object twenty_percent_wider_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,240);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtwenty_percent_wider,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qcenter_origin;      /* center-origin */

/* COM-CENTER-ORIGIN */
Object com_center_origin(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,241);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qcenter_origin,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* CENTER-ORIGIN-COMMAND-PURSUER */
Object center_origin_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,242);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* CENTER-ORIGIN-COMMAND-TRANSLATOR */
Object center_origin_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,243);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcenter_origin,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_left_ten_percent;  /* shift-left-ten-percent */

/* COM-SHIFT-LEFT-TEN-PERCENT */
Object com_shift_left_ten_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,244);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_left_ten_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-LEFT-TEN-PERCENT-COMMAND-PURSUER */
Object shift_left_ten_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,245);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-LEFT-TEN-PERCENT-COMMAND-TRANSLATOR */
Object shift_left_ten_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,246);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_left_ten_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_right_ten_percent;  /* shift-right-ten-percent */

/* COM-SHIFT-RIGHT-TEN-PERCENT */
Object com_shift_right_ten_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,247);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_right_ten_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-RIGHT-TEN-PERCENT-COMMAND-PURSUER */
Object shift_right_ten_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,248);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-RIGHT-TEN-PERCENT-COMMAND-TRANSLATOR */
Object shift_right_ten_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,249);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_right_ten_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_left_one_percent;  /* shift-left-one-percent */

/* COM-SHIFT-LEFT-ONE-PERCENT */
Object com_shift_left_one_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,250);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_left_one_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-LEFT-ONE-PERCENT-COMMAND-PURSUER */
Object shift_left_one_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,251);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-LEFT-ONE-PERCENT-COMMAND-TRANSLATOR */
Object shift_left_one_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,252);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_left_one_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_right_one_percent;  /* shift-right-one-percent */

/* COM-SHIFT-RIGHT-ONE-PERCENT */
Object com_shift_right_one_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,253);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_right_one_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-RIGHT-ONE-PERCENT-COMMAND-PURSUER */
Object shift_right_one_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,254);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-RIGHT-ONE-PERCENT-COMMAND-TRANSLATOR */
Object shift_right_one_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,255);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_right_one_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_up_ten_percent;  /* shift-up-ten-percent */

/* COM-SHIFT-UP-TEN-PERCENT */
Object com_shift_up_ten_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,256);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_up_ten_percent,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-UP-TEN-PERCENT-COMMAND-PURSUER */
Object shift_up_ten_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,257);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-UP-TEN-PERCENT-COMMAND-TRANSLATOR */
Object shift_up_ten_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,258);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_up_ten_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_down_ten_percent;  /* shift-down-ten-percent */

/* COM-SHIFT-DOWN-TEN-PERCENT */
Object com_shift_down_ten_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,259);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_down_ten_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-DOWN-TEN-PERCENT-COMMAND-PURSUER */
Object shift_down_ten_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,260);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-DOWN-TEN-PERCENT-COMMAND-TRANSLATOR */
Object shift_down_ten_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,261);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_down_ten_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_up_one_percent;  /* shift-up-one-percent */

/* COM-SHIFT-UP-ONE-PERCENT */
Object com_shift_up_one_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,262);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_up_one_percent,image_plane,
		x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-UP-ONE-PERCENT-COMMAND-PURSUER */
Object shift_up_one_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,263);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-UP-ONE-PERCENT-COMMAND-TRANSLATOR */
Object shift_up_one_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,264);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_up_one_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshift_down_one_percent;  /* shift-down-one-percent */

/* COM-SHIFT-DOWN-ONE-PERCENT */
Object com_shift_down_one_percent(image_plane,x_in_window,y_in_window)
    Object image_plane, x_in_window, y_in_window;
{
    x_note_fn_call(225,265);
    if (valid_image_plane_p(image_plane) && x_in_window && y_in_window)
	return handle_image_plane_event(Qshift_down_one_percent,
		image_plane,x_in_window,y_in_window);
    else
	return VALUES_1(Nil);
}

/* SHIFT-DOWN-ONE-PERCENT-COMMAND-PURSUER */
Object shift_down_one_percent_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, image_plane, x_in_window, y_in_window;

    x_note_fn_call(225,266);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    image_plane = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y_in_window = CAR(gensymed_symbol);
    image_plane = command_argument_value(image_plane);
    x_in_window = command_argument_value(x_in_window);
    y_in_window = command_argument_value(y_in_window);
    if (EQ(image_plane,Plus_missing_argument_plus))
	return VALUES_3(Qimage_plane,Qimage_plane,FIX((SI_Long)0L));
    else if (EQ(x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qx_in_window,Qx_in_window,FIX((SI_Long)1L));
    else if (EQ(y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qy_in_window,Qy_in_window,FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

/* SHIFT-DOWN-ONE-PERCENT-COMMAND-TRANSLATOR */
Object shift_down_one_percent_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, temp, temp_1, temp_2;

    x_note_fn_call(225,267);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window) {
	if (T) {
	    temp = image_plane;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshift_down_one_percent,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinspect_history;    /* inspect-history */

static Object Qtable_item;         /* table-item */

/* ALLOW-TABLE-COMMAND-P */
Object allow_table_command_p(frame)
    Object frame;
{
    Object sub_class_bit_vector, temp_1, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,268);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Workspace_class_description,
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
    if (temp)
	temp_1 = user_workspace_p(frame);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Inspect_command_class_description,
		    (SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qinspect_history,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp);
	    else
		temp = TRUEP(frame_acts_like_arrow_button_p(frame));
	    if (temp);
	    else {
		gensymed_symbol_3 = 
			lookup_global_or_kb_specific_property_value(Qtable_item,
			Class_description_gkbprop);
		if (gensymed_symbol_3) {
		    sub_class_bit_vector = ISVREF(ISVREF(frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_3,(SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    if (temp);
	    else
		temp = TRUEP(block_of_edit_workspace_p(frame));
	    temp_1 =  !temp ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

/* COM-TABLE-OF-ATTRIBUTES-PANE */
Object com_table_of_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    x_note_fn_call(225,269);
    if (frame && of_class_p_function(g2_window,Qg2_window) && 
	    allow_table_command_p(frame))
	return create_or_destroy_table_of_attributes_pane(frame,g2_window);
    else
	return VALUES_1(Nil);
}

static Object Qmost_interesting_frame;  /* most-interesting-frame */

/* TABLE-OF-ATTRIBUTES-PANE-COMMAND-PURSUER */
Object table_of_attributes_pane_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, g2_window;

    x_note_fn_call(225,270);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    g2_window = command_argument_value(g2_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(g2_window,Plus_missing_argument_plus))
	return VALUES_3(Qg2_window,Qg2_window,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_attributes_pane;  /* table-of-attributes-pane */

/* TABLE-OF-ATTRIBUTES-PANE-COMMAND-TRANSLATOR */
Object table_of_attributes_pane_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, g2_window, temp, temp_1;

    x_note_fn_call(225,271);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (frame && g2_window) {
	if (allow_table_command_p(frame)) {
	    temp = frame;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = g2_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_attributes_pane,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TABLE-OF-HIDDEN-ATTRIBUTES-PANE */
Object com_table_of_hidden_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,272);
    if (frame && of_class_p_function(g2_window,Qg2_window)) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return create_or_destroy_table_of_hidden_attributes_pane(frame,
		g2_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-OF-HIDDEN-ATTRIBUTES-PANE-COMMAND-PURSUER */
Object table_of_hidden_attributes_pane_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, g2_window;

    x_note_fn_call(225,273);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    g2_window = command_argument_value(g2_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(g2_window,Plus_missing_argument_plus))
	return VALUES_3(Qg2_window,Qg2_window,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_hidden_attributes_pane;  /* table-of-hidden-attributes-pane */

/* TABLE-OF-HIDDEN-ATTRIBUTES-PANE-COMMAND-TRANSLATOR */
Object table_of_hidden_attributes_pane_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, g2_window, sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,274);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (frame && g2_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = g2_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_hidden_attributes_pane,
		    slot_value_list_2(temp_2,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qupdate_table_of_attributes_pane;  /* update-table-of-attributes-pane */

static Object Qupdate_table_of_hidden_attributes_pane;  /* update-table-of-hidden-attributes-pane */

/* UPDATE-ATT-TABLES */
Object update_att_tables(frame,g2_window)
    Object frame, g2_window;
{
    Object x2, ui_command, gensymed_symbol, temp_1;
    char temp;

    x_note_fn_call(225,275);
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(g2_window) : TRUEP(Nil)) {
	ui_command = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_table_of_attributes_pane),
		Qui_command_named);
	if (ui_command) {
	    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
	    temp_1 = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    FUNCALL_2(temp_1,frame,g2_window);
	}
	ui_command = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qupdate_table_of_hidden_attributes_pane),
		Qui_command_named);
	if (ui_command) {
	    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
	    temp_1 = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    return FUNCALL_2(temp_1,frame,g2_window);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_property_grid;   /* g2-property-grid */

static Object Qdestroy;            /* destroy */

static Object Qcontents;           /* contents */

static Object Quser_data;          /* user-data */

static Object Qproperty_user_callback_func;  /* property-user-callback-func */

static Object array_constant;      /* # */

/* CREATE-OR-DESTROY-TABLE-OF-ATTRIBUTES-PANE */
Object create_or_destroy_table_of_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(225,276);
    temp = map_to_gensym_window_or_stack_error(g2_window);
    if ( !TRUEP(find_native_window(3,temp,Global_table_of_attributes_pane,
	    Qg2_property_grid))) {
	Global_table_of_attributes_pane = Nil;
	Global_table_of_attributes_pane_pointer = Nil;
    }
    if ( !EQ(Global_table_of_attributes_pane,Nil)) {
	g2_ui_manage_property_grid(Qdestroy,
		Global_table_of_attributes_pane,Nil,g2_window);
	Global_table_of_attributes_pane = Nil;
	return VALUES_1(Global_table_of_attributes_pane);
    }
    else if (EQ(Global_table_of_attributes_pane,Nil)) {
	if (frame) {
	    temp = make_class_header_string(frame);
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qcontents;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qcontents;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = get_attribute_texts_of_item_for_pane(frame);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = get_attribute_texts_of_item_for_pane(frame);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Quser_data;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Quser_data;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = package_internal_data_property(frame,
			g2_window,Qupdate_table_of_attributes_pane,Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = package_internal_data_property(frame,
			g2_window,Qupdate_table_of_attributes_pane,Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsort;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)5L)) = Qsort;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnone;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qnone;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    Global_table_of_attributes_pane = g2_ui_create_property_grid(5,
		    temp,Nil,eval_cons_1(gensymed_symbol,Qab_structure),
		    g2_window,Qproperty_user_callback_func);
	}
	else {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
		ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  
			- (SI_Long)10L) + (SI_Long)2L);
		svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
		ISVREF(temp_1,svref_arg_2) = FIX((SI_Long)1L);
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qcontents;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)1L)) = Qcontents;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = allocate_evaluation_sequence(Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = allocate_evaluation_sequence(Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Quser_data;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)3L)) = Quser_data;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = package_internal_data_property(Nil,
			g2_window,Qupdate_table_of_attributes_pane,Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = package_internal_data_property(Nil,
			g2_window,Qupdate_table_of_attributes_pane,Nil);
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size))
		SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsort;
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp_1,FIX((SI_Long)5L)) = Qsort;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = Qnone;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
			item_or_value;
		SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	    }
	    else {
		temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = Qnone;
		if (SIMPLE_VECTOR_P(item_or_value) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
			(SI_Long)2L &&  !EQ(ISVREF(item_or_value,
			(SI_Long)1L),Qavailable_frame_vector)) {
		    x2 = ISVREF(item_or_value,(SI_Long)1L);
		    temp_2 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp_2 = TRUEP(Nil);
		svref_new_value = temp_2 ? 
			get_reference_to_item(item_or_value) : item_or_value;
		SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	    }
	    Global_table_of_attributes_pane = g2_ui_create_property_grid(5,
		    array_constant,Nil,eval_cons_1(gensymed_symbol,
		    Qab_structure),g2_window,Qproperty_user_callback_func);
	}
	Global_nmsci_id_for_attributes_pane = Global_nms_menu_choiced_item_id;
	temp = map_to_gensym_window_or_stack_error(g2_window);
	Global_table_of_attributes_pane_pointer = 
		find_native_view_or_stack_error(3,temp,
		Global_table_of_attributes_pane,Qg2_property_grid);
	return VALUES_1(Global_table_of_attributes_pane_pointer);
    }
    else
	return VALUES_1(Qnil);
}

/* CREATE-OR-DESTROY-TABLE-OF-HIDDEN-ATTRIBUTES-PANE */
Object create_or_destroy_table_of_hidden_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object temp, gensymed_symbol, temp_1, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_2;

    x_note_fn_call(225,277);
    temp = map_to_gensym_window_or_stack_error(g2_window);
    if ( !TRUEP(find_native_window(3,temp,
	    Global_table_of_hidden_attributes_pane,Qg2_property_grid))) {
	Global_table_of_hidden_attributes_pane = Nil;
	Global_table_of_hidden_attributes_pane_pointer = Nil;
    }
    if ( !EQ(Global_table_of_hidden_attributes_pane,Nil)) {
	g2_ui_manage_property_grid(Qdestroy,
		Global_table_of_hidden_attributes_pane,Nil,g2_window);
	Global_table_of_hidden_attributes_pane = Nil;
	return VALUES_1(Global_table_of_hidden_attributes_pane);
    }
    else if (EQ(Global_table_of_hidden_attributes_pane,Nil)) {
	temp = make_virtual_attribute_class_header_string(frame);
	gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + 
		(SI_Long)1L));
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
	    SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qcontents;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)1L)) = Qcontents;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = get_hidden_attribute_texts_of_item_for_pane(frame);
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
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = get_hidden_attribute_texts_of_item_for_pane(frame);
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
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Quser_data;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)3L)) = Quser_data;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = package_internal_data_property(frame,g2_window,
		    Qupdate_table_of_hidden_attributes_pane,Nil);
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
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = package_internal_data_property(frame,g2_window,
		    Qupdate_table_of_hidden_attributes_pane,Nil);
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
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)4L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qsort;
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    SVREF(temp_1,FIX((SI_Long)5L)) = Qsort;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = Qnone;
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
	    temp_1 = temp_2 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp_1;
	}
	else {
	    temp_1 = ISVREF(gensymed_symbol,(SI_Long)2L);
	    item_or_value = Qnone;
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
	    svref_new_value = temp_2 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_1,FIX((SI_Long)6L)) = svref_new_value;
	}
	Global_table_of_hidden_attributes_pane = 
		g2_ui_create_property_grid(5,temp,Nil,
		eval_cons_1(gensymed_symbol,Qab_structure),g2_window,
		Qproperty_user_callback_func);
	Global_nmsci_id_for_hidden_attributes_pane = 
		Global_nms_menu_choiced_item_id;
	temp = map_to_gensym_window_or_stack_error(g2_window);
	Global_table_of_hidden_attributes_pane_pointer = 
		find_native_view_or_stack_error(3,temp,
		Global_table_of_hidden_attributes_pane,Qg2_property_grid);
	return VALUES_1(Global_table_of_hidden_attributes_pane_pointer);
    }
    else
	return VALUES_1(Qnil);
}

/* COM-UPDATE-TABLE-OF-ATTRIBUTES-PANE */
Object com_update_table_of_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    x_note_fn_call(225,278);
    if (frame && of_class_p_function(g2_window,Qg2_window) && 
	    allow_table_command_p(frame))
	return update_table_of_attributes_pane(frame,g2_window);
    else
	return VALUES_1(Nil);
}

/* UPDATE-TABLE-OF-ATTRIBUTES-PANE-COMMAND-PURSUER */
Object update_table_of_attributes_pane_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, g2_window;

    x_note_fn_call(225,279);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    g2_window = command_argument_value(g2_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(g2_window,Plus_missing_argument_plus))
	return VALUES_3(Qg2_window,Qg2_window,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

/* UPDATE-TABLE-OF-ATTRIBUTES-PANE-COMMAND-TRANSLATOR */
Object update_table_of_attributes_pane_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, g2_window, temp, temp_1;

    x_note_fn_call(225,280);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (frame && g2_window) {
	if (allow_table_command_p(frame)) {
	    temp = frame;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = g2_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qupdate_table_of_attributes_pane,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-UPDATE-TABLE-OF-HIDDEN-ATTRIBUTES-PANE */
Object com_update_table_of_hidden_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,281);
    if (frame && of_class_p_function(g2_window,Qg2_window)) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return update_table_of_hidden_attributes_pane(frame,g2_window);
    else
	return VALUES_1(Nil);
}

/* UPDATE-TABLE-OF-HIDDEN-ATTRIBUTES-PANE-COMMAND-PURSUER */
Object update_table_of_hidden_attributes_pane_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, g2_window;

    x_note_fn_call(225,282);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    g2_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    g2_window = command_argument_value(g2_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(g2_window,Plus_missing_argument_plus))
	return VALUES_3(Qg2_window,Qg2_window,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

/* UPDATE-TABLE-OF-HIDDEN-ATTRIBUTES-PANE-COMMAND-TRANSLATOR */
Object update_table_of_hidden_attributes_pane_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, g2_window, sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,283);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (frame && g2_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = g2_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qupdate_table_of_hidden_attributes_pane,
		    slot_value_list_2(temp_2,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-PROPERTY-GRID-ALL */
Object update_property_grid_all(frame)
    Object frame;
{
    x_note_fn_call(225,284);
    update_property_pane_after_edit(Global_table_of_attributes_pane_pointer);
    return update_property_pane_after_edit(Global_table_of_hidden_attributes_pane_pointer);
}

static Object Qpopulate;           /* populate */

/* UPDATE-TABLE-OF-ATTRIBUTES-PANE */
Object update_table_of_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object temp;
    char temp_1;

    x_note_fn_call(225,285);
    if ( !EQ(Global_table_of_attributes_pane,Nil)) {
	temp = map_to_gensym_window_or_stack_error(g2_window);
	temp_1 = TRUEP(find_native_window(3,temp,
		Global_table_of_attributes_pane,Qg2_property_grid));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = Global_table_of_attributes_pane;
	g2_ui_manage_property_grid(Qpopulate,temp,
		get_attribute_texts_of_item_for_pane(frame),g2_window);
	temp = map_to_gensym_window_or_stack_error(g2_window);
	temp = find_native_view_or_stack_error(3,temp,
		Global_table_of_attributes_pane,Qg2_property_grid);
	caption_native_window(temp,make_class_header_string(frame));
	return g2_ui_manage_property_grid(Qsort,
		Global_table_of_attributes_pane,Qnone,g2_window);
    }
    else
	return VALUES_1(Nil);
}

/* UPDATE-TABLE-OF-HIDDEN-ATTRIBUTES-PANE */
Object update_table_of_hidden_attributes_pane(frame,g2_window)
    Object frame, g2_window;
{
    Object temp;
    char temp_1;

    x_note_fn_call(225,286);
    if ( !EQ(Global_table_of_hidden_attributes_pane,Nil)) {
	temp = map_to_gensym_window_or_stack_error(g2_window);
	temp_1 = TRUEP(find_native_window(3,temp,
		Global_table_of_hidden_attributes_pane,Qg2_property_grid));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = Global_table_of_hidden_attributes_pane;
	g2_ui_manage_property_grid(Qpopulate,temp,
		get_hidden_attribute_texts_of_item_for_pane(frame),g2_window);
	temp = map_to_gensym_window_or_stack_error(g2_window);
	temp = find_native_view_or_stack_error(3,temp,
		Global_table_of_hidden_attributes_pane,Qg2_property_grid);
	caption_native_window(temp,
		make_virtual_attribute_class_header_string(frame));
	return g2_ui_manage_property_grid(Qsort,
		Global_table_of_hidden_attributes_pane,Qnone,g2_window);
    }
    else
	return VALUES_1(Nil);
}

/* GET-ATTRIBUTE-TEXTS-OF-ITEM-FOR-PANE */
Object get_attribute_texts_of_item_for_pane(frame)
    Object frame;
{
    Object class_description, name_and_description_alist, name;
    Object slot_description_or_virtual_attribute, ab_loop_list_;
    Object all_attributes_p, want_attribute_p, attribute_text_value_qm;
    Object slot_name_qm, attribute_names_and_values, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_desetq_;

    x_note_fn_call(225,287);
    class_description = ISVREF(frame,(SI_Long)1L);
    name_and_description_alist = 
	    get_list_of_all_user_visible_attributes_for_pane(class_description,
	    Nil);
    name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = name_and_description_alist;
    all_attributes_p = T;
    want_attribute_p = Nil;
    attribute_text_value_qm = Nil;
    slot_name_qm = Nil;
    attribute_names_and_values = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    want_attribute_p = all_attributes_p;
    attribute_text_value_qm = want_attribute_p ? 
	    serve_text_of_attribute(frame,name,Nil) : Qnil;
    slot_name_qm = ISVREF(slot_description_or_virtual_attribute,(SI_Long)2L);
    if (attribute_text_value_qm) {
	ab_loopvar__1 = 
		eval_cons_1(create_node_for_table_of_attributes_pane(frame,
		name,attribute_text_value_qm,slot_name_qm,Nil,T),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    return allocate_evaluation_sequence(attribute_names_and_values);
    return VALUES_1(Qnil);
}

/* GET-HIDDEN-ATTRIBUTE-TEXTS-OF-ITEM-FOR-PANE */
Object get_hidden_attribute_texts_of_item_for_pane(frame)
    Object frame;
{
    Object class_description, name_and_description_alist, attr_name;
    Object slot_description_or_virtual_attribute, ab_loop_list_;
    Object all_attributes_p, want_attribute_p, attribute_value_qm;
    Object slot_name_qm, attribute_names_and_values, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_desetq_, temp, temp_1;

    x_note_fn_call(225,288);
    class_description = ISVREF(frame,(SI_Long)1L);
    name_and_description_alist = 
	    get_list_of_all_virtual_attributes_for_pane(class_description,Nil);
    attr_name = Nil;
    slot_description_or_virtual_attribute = Nil;
    ab_loop_list_ = name_and_description_alist;
    all_attributes_p = T;
    want_attribute_p = Nil;
    attribute_value_qm = Nil;
    slot_name_qm = Nil;
    attribute_names_and_values = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    attr_name = CAR(ab_loop_desetq_);
    slot_description_or_virtual_attribute = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    want_attribute_p = all_attributes_p;
    attribute_value_qm = want_attribute_p ? 
	    get_attribute_description_evaluation_value(frame,
	    slot_description_or_virtual_attribute) : Qnil;
    slot_name_qm = ISVREF(slot_description_or_virtual_attribute,(SI_Long)2L);
    if (text_string_for_item_or_value(attribute_value_qm)) {
	temp = attr_name;
	temp_1 = text_string_for_item_or_value(attribute_value_qm);
	ab_loopvar__1 = 
		eval_cons_1(create_node_for_table_of_hidden_attributes_pane(frame,
		temp,temp_1,attr_name,T,T),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    attribute_names_and_values = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    reclaim_eval_alist(name_and_description_alist);
    return allocate_evaluation_sequence(attribute_names_and_values);
    return VALUES_1(Qnil);
}

static Object Qfunc;               /* func */

static Object Qflag;               /* flag */

/* PACKAGE-INTERNAL-DATA-PROPERTY */
Object package_internal_data_property(frame,g2_window,function,flag)
    Object frame, g2_window, function, flag;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(225,289);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qframe;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qframe;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = frame;
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
	item_or_value = frame;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qwindow;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qwindow;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = g2_window;
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
	item_or_value = g2_window;
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
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qfunc;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qfunc;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = function;
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
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = function;
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
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qflag;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qflag;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = flag;
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
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = flag;
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
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    temp_2 = eval_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(temp_2);
}

static Object Qproperty;           /* property */

static Object Qcurrent_value;      /* current-value */

static Object Qedit_in_place;      /* edit-in-place */

/* CREATE-NODE-FOR-TABLE-OF-ATTRIBUTES-PANE */
Object create_node_for_table_of_attributes_pane(frame,attribute_text_name,
	    attribute_text_value,slot_name,virtual_1,editable)
    Object frame, attribute_text_name, attribute_text_value, slot_name;
    Object virtual_1, editable;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(225,290);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qproperty;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qproperty;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = attribute_text_name;
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
	item_or_value = attribute_text_name;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcurrent_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qcurrent_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = attribute_text_value;
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
	item_or_value = attribute_text_value;
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
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Quser_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Quser_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = package_internal_data_with_slot(frame,slot_name,
		virtual_1,editable);
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
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = package_internal_data_with_slot(frame,slot_name,
		virtual_1,editable);
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
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qedit_in_place;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qedit_in_place;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Evaluation_false_value;
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
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qslot_name;          /* slot-name */

static Object Qcommand;            /* command */

static Object Qexecute;            /* execute */

static Object Qvirtual;            /* virtual */

static Object Qeditable;           /* editable */

/* PACKAGE-INTERNAL-DATA-WITH-SLOT */
Object package_internal_data_with_slot(frame,slot_name,virtual_1,editable)
    Object frame, slot_name, virtual_1, editable;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(225,291);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)10L + 
	    (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qframe;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qframe;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = frame;
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
	item_or_value = frame;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qslot_name;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qslot_name;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = slot_name;
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
	item_or_value = slot_name;
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
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qcommand;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qcommand;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qexecute;
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
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qexecute;
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
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qvirtual;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qvirtual;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = virtual_1;
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
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = virtual_1;
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
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)11L)) = Qeditable;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)9L)) = Qeditable;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = editable;
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
	SVREF(gensymed_symbol,FIX((SI_Long)12L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = editable;
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
	SVREF(temp,FIX((SI_Long)10L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* CREATE-NODE-FOR-TABLE-OF-HIDDEN-ATTRIBUTES-PANE */
Object create_node_for_table_of_hidden_attributes_pane(frame,
	    attribute_text_name,attribute_text_value,slot_name,virtual_1,edit)
    Object frame, attribute_text_name, attribute_text_value, slot_name;
    Object virtual_1, edit;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(225,292);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)8L + (SI_Long)1L));
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
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qproperty;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qproperty;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = attribute_text_name;
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
	item_or_value = attribute_text_name;
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
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qcurrent_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qcurrent_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = attribute_text_value;
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
	item_or_value = attribute_text_value;
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
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Quser_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Quser_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = package_internal_data_with_slot(frame,slot_name,
		virtual_1,edit);
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
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = package_internal_data_with_slot(frame,slot_name,
		virtual_1,edit);
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
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)9L)) = Qedit_in_place;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)7L)) = Qedit_in_place;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Evaluation_false_value;
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
	SVREF(gensymed_symbol,FIX((SI_Long)10L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Evaluation_false_value;
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
	SVREF(temp,FIX((SI_Long)8L)) = svref_new_value;
    }
    return eval_cons_1(gensymed_symbol,Qab_structure);
}

/* COM-TABLE */
Object com_table(frame,original_x_in_window,original_y_in_window)
    Object frame, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(225,293);
    if (frame && original_x_in_window && original_y_in_window && 
	    allow_table_command_p(frame))
	return put_up_attributes_table(3,frame,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-COMMAND-PURSUER */
Object table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,294);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable;              /* table */

/* TABLE-COMMAND-TRANSLATOR */
Object table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, original_x_in_window, original_y_in_window, temp, temp_1;
    Object temp_2;

    x_note_fn_call(225,295);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (frame && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(frame)) {
	    temp = frame;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = original_x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = original_y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtable,slot_value_list_3(temp_1,
		    temp_2,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TABLE-OF-ITEM */
Object com_table_of_item(frame,original_x_in_window,original_y_in_window)
    Object frame, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,296);
    if (frame && original_x_in_window && original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	temp =  !temp ? TRUEP(allow_table_command_p(frame)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_attributes_table(3,frame,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-OF-ITEM-COMMAND-PURSUER */
Object table_of_item_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,297);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_item;      /* table-of-item */

/* TABLE-OF-ITEM-COMMAND-TRANSLATOR */
Object table_of_item_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,298);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (frame && original_x_in_window && original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ( !temp ? TRUEP(allow_table_command_p(frame)) : TRUEP(Nil)) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_item,
		    slot_value_list_3(temp_2,temp_3,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TABLE-OF-WORKSPACE */
Object com_table_of_workspace(workspace,original_x_in_window,
	    original_y_in_window)
    Object workspace, original_x_in_window, original_y_in_window;
{
    x_note_fn_call(225,299);
    if (of_class_p_function(workspace,Qworkspace) && original_x_in_window 
	    && original_y_in_window && allow_table_command_p(workspace))
	return put_up_attributes_table(3,workspace,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-OF-WORKSPACE-COMMAND-PURSUER */
Object table_of_workspace_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, workspace, original_x_in_window;
    Object original_y_in_window;

    x_note_fn_call(225,300);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    workspace = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    workspace = command_argument_value(workspace);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(workspace,Plus_missing_argument_plus))
	return VALUES_3(Qworkspace,Qworkspace,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_workspace;  /* table-of-workspace */

/* TABLE-OF-WORKSPACE-COMMAND-TRANSLATOR */
Object table_of_workspace_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object workspace, original_x_in_window, original_y_in_window, temp, temp_1;
    Object temp_2;

    x_note_fn_call(225,301);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (workspace && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(workspace)) {
	    temp = workspace;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = original_x_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp);
	    temp = original_y_in_window;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_workspace,
		    slot_value_list_3(temp_1,temp_2,
		    snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TABLE-OF-HIDDEN-ATTRIBUTES */
Object com_table_of_hidden_attributes(frame,original_x_in_window,
	    original_y_in_window)
    Object frame, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,302);
    if (frame && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_virtual_attributes_table(frame,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-OF-HIDDEN-ATTRIBUTES-COMMAND-PURSUER */
Object table_of_hidden_attributes_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,303);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_hidden_attributes;  /* table-of-hidden-attributes */

/* TABLE-OF-HIDDEN-ATTRIBUTES-COMMAND-TRANSLATOR */
Object table_of_hidden_attributes_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,304);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (frame && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_hidden_attributes,
		    slot_value_list_3(temp_2,temp_3,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-TABLE-OF-HIDDEN-ATTRIBUTES-OF-ITEM */
Object com_table_of_hidden_attributes_of_item(frame,original_x_in_window,
	    original_y_in_window)
    Object frame, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,305);
    if (frame && original_x_in_window && original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ( !temp ? TRUEP(allow_table_command_p(frame)) : TRUEP(Nil)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_virtual_attributes_table(frame,original_x_in_window,
		original_y_in_window);
    else
	return VALUES_1(Nil);
}

/* TABLE-OF-HIDDEN-ATTRIBUTES-OF-ITEM-COMMAND-PURSUER */
Object table_of_hidden_attributes_of_item_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,306);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qtable_of_hidden_attributes_of_item;  /* table-of-hidden-attributes-of-item */

/* TABLE-OF-HIDDEN-ATTRIBUTES-OF-ITEM-COMMAND-TRANSLATOR */
Object table_of_hidden_attributes_of_item_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,307);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (frame && original_x_in_window && original_y_in_window) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ( !temp ? TRUEP(allow_table_command_p(frame)) : TRUEP(Nil)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qtable_of_hidden_attributes_of_item,
		    slot_value_list_3(temp_2,temp_3,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qattributes_permamently_changed;  /* attributes-permamently-changed */

/* COM-SHOW-UNSAVED-ATTRIBUTES */
Object com_show_unsaved_attributes(frame,original_x_in_window,
	    original_y_in_window)
    Object frame, original_x_in_window, original_y_in_window;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,308);
    if (frame && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	temp = temp ? 
		TRUEP(item_has_unsaved_changes_visible_in_tables_p(frame)) 
		: TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return put_up_attributes_table(7,frame,original_x_in_window,
		original_y_in_window,Nil,Nil,Nil,(SI_Long)0L != 
		(IFIX(ISVREF(frame,(SI_Long)5L)) & (SI_Long)16L) ? 
		get_lookup_slot_value_given_default(frame,
		Qattributes_permamently_changed,Nil) : T);
    else
	return VALUES_1(Nil);
}

/* SHOW-UNSAVED-ATTRIBUTES-COMMAND-PURSUER */
Object show_unsaved_attributes_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, frame, original_x_in_window, original_y_in_window;

    x_note_fn_call(225,309);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    frame = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_x_in_window = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    original_y_in_window = CAR(gensymed_symbol);
    frame = command_argument_value(frame);
    original_x_in_window = command_argument_value(original_x_in_window);
    original_y_in_window = command_argument_value(original_y_in_window);
    if (EQ(frame,Plus_missing_argument_plus))
	return VALUES_3(Qframe,Qmost_interesting_frame,FIX((SI_Long)0L));
    else if (EQ(original_x_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_x_in_window,Qoriginal_x_in_window,
		FIX((SI_Long)1L));
    else if (EQ(original_y_in_window,Plus_missing_argument_plus))
	return VALUES_3(Qoriginal_y_in_window,Qoriginal_y_in_window,
		FIX((SI_Long)2L));
    else
	return VALUES_1(Qnil);
}

static Object Qshow_unsaved_attributes;  /* show-unsaved-attributes */

/* SHOW-UNSAVED-ATTRIBUTES-COMMAND-TRANSLATOR */
Object show_unsaved_attributes_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object frame, original_x_in_window, original_y_in_window;
    Object sub_class_bit_vector, temp_1, temp_2, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,310);
    frame = most_interesting_frame_blackboard_function(mouse_pointer);
    original_x_in_window = 
	    original_x_in_window_blackboard_function(mouse_pointer);
    original_y_in_window = 
	    original_y_in_window_blackboard_function(mouse_pointer);
    if (frame && original_x_in_window && original_y_in_window) {
	if (allow_table_command_p(frame)) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
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
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? 
		TRUEP(item_has_unsaved_changes_visible_in_tables_p(frame)) 
		: TRUEP(Nil)) {
	    temp_1 = frame;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_2 = snapshot_command_argument(temp_1);
	    temp_1 = original_x_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    temp_3 = snapshot_command_argument(temp_1);
	    temp_1 = original_y_in_window;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qshow_unsaved_attributes,
		    slot_value_list_3(temp_2,temp_3,
		    snapshot_command_argument(temp_1)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-SHRINK-WRAP */
Object com_shrink_wrap(workspace)
    Object workspace;
{
    x_note_fn_call(225,311);
    if (of_class_p_function(workspace,Qworkspace))
	return shrink_wrap_workspace(workspace);
    else
	return VALUES_1(Nil);
}

/* SHRINK-WRAP-COMMAND-PURSUER */
Object shrink_wrap_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, workspace;

    x_note_fn_call(225,312);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    workspace = CAR(gensymed_symbol);
    workspace = command_argument_value(workspace);
    if (EQ(workspace,Plus_missing_argument_plus))
	return VALUES_3(Qworkspace,Qworkspace,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qshrink_wrap;        /* shrink-wrap */

/* SHRINK-WRAP-COMMAND-TRANSLATOR */
Object shrink_wrap_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object workspace, temp;

    x_note_fn_call(225,313);
    workspace = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qworkspace);
    if (workspace) {
	if (T) {
	    temp = workspace;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qshrink_wrap,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* NAME-BLOCK-PERMITTED-P */
Object name_block_permitted_p(block)
    Object block;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,314);
    if (type_of_slot_if_editable(2,ISVREF(ISVREF(block,(SI_Long)1L),
	    (SI_Long)1L),Qname_or_names_for_frame)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return item_is_either_not_permanent_or_from_an_editable_module_p(block);
    else
	return VALUES_1(Nil);
}

/* EDIT-NAME-OF-BLOCK */
Object edit_name_of_block(block)
    Object block;
{
    x_note_fn_call(225,315);
    return enter_editing_context(3,block,Qname_or_names_for_frame,
	    make_text_representation_for_slot_value(2,block,
	    Qname_or_names_for_frame));
}

/* COM-NAME */
Object com_name(block)
    Object block;
{
    x_note_fn_call(225,316);
    if (of_class_p_function(block,Qblock) && name_block_permitted_p(block))
	return edit_name_of_block(block);
    else
	return VALUES_1(Nil);
}

/* NAME-COMMAND-PURSUER */
Object name_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, block;

    x_note_fn_call(225,317);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    block = CAR(gensymed_symbol);
    block = command_argument_value(block);
    if (EQ(block,Plus_missing_argument_plus))
	return VALUES_3(Qblock,Qblock,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qname;               /* name */

/* NAME-COMMAND-TRANSLATOR */
Object name_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object block, temp;

    x_note_fn_call(225,318);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    if (block) {
	if (name_block_permitted_p(block)) {
	    temp = block;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qname,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-NAME-ITEM */
Object com_name_item(block)
    Object block;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,319);
    if (of_class_p_function(block,Qblock)) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	temp =  !temp ? TRUEP(name_block_permitted_p(block)) : TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return edit_name_of_block(block);
    else
	return VALUES_1(Nil);
}

/* NAME-ITEM-COMMAND-PURSUER */
Object name_item_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, block;

    x_note_fn_call(225,320);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    block = CAR(gensymed_symbol);
    block = command_argument_value(block);
    if (EQ(block,Plus_missing_argument_plus))
	return VALUES_3(Qblock,Qblock,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qname_item;          /* name-item */

/* NAME-ITEM-COMMAND-TRANSLATOR */
Object name_item_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object block, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(225,321);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qblock);
    if (block) {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
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
	if ( !temp ? TRUEP(name_block_permitted_p(block)) : TRUEP(Nil)) {
	    temp_1 = block;
	    if (temp_1);
	    else
		temp_1 = Plus_missing_argument_plus;
	    return make_partial_command(Qname_item,
		    slot_value_cons_1(snapshot_command_argument(temp_1),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmark_to_strip_text;  /* mark-to-strip-text */

/* COM-MARK-TO-STRIP-TEXT */
Object com_mark_to_strip_text(item)
    Object item;
{
    x_note_fn_call(225,322);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qmark_to_strip_text))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)1L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-TO-STRIP-TEXT-COMMAND-PURSUER */
Object mark_to_strip_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,323);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-TO-STRIP-TEXT-COMMAND-TRANSLATOR */
Object mark_to_strip_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,324);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qmark_to_strip_text)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmark_to_strip_text,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmark_to_strip_text_star;  /* mark-to-strip-text-* */

/* COM-MARK-TO-STRIP-TEXT-* */
Object com_mark_to_strip_text_star(item)
    Object item;
{
    x_note_fn_call(225,325);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qmark_to_strip_text_star))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)1L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-TO-STRIP-TEXT-*-COMMAND-PURSUER */
Object mark_to_strip_text_star_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,326);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-TO-STRIP-TEXT-*-COMMAND-TRANSLATOR */
Object mark_to_strip_text_star_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,327);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qmark_to_strip_text_star)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmark_to_strip_text_star,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qremove_strip_text_mark;  /* remove-strip-text-mark */

/* COM-REMOVE-STRIP-TEXT-MARK */
Object com_remove_strip_text_mark(item)
    Object item;
{
    x_note_fn_call(225,328);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qremove_strip_text_mark))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-STRIP-TEXT-MARK-COMMAND-PURSUER */
Object remove_strip_text_mark_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,329);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-STRIP-TEXT-MARK-COMMAND-TRANSLATOR */
Object remove_strip_text_mark_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,330);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qremove_strip_text_mark)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qremove_strip_text_mark,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qremove_strip_text_mark_star;  /* remove-strip-text-mark-* */

/* COM-REMOVE-STRIP-TEXT-MARK-* */
Object com_remove_strip_text_mark_star(item)
    Object item;
{
    x_note_fn_call(225,331);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qremove_strip_text_mark_star))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-STRIP-TEXT-MARK-*-COMMAND-PURSUER */
Object remove_strip_text_mark_star_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,332);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-STRIP-TEXT-MARK-*-COMMAND-TRANSLATOR */
Object remove_strip_text_mark_star_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,333);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qremove_strip_text_mark_star)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qremove_strip_text_mark_star,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmark_not_to_strip_text_star;  /* mark-not-to-strip-text-* */

/* COM-MARK-NOT-TO-STRIP-TEXT-* */
Object com_mark_not_to_strip_text_star(item)
    Object item;
{
    x_note_fn_call(225,334);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qmark_not_to_strip_text_star))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* MARK-NOT-TO-STRIP-TEXT-*-COMMAND-PURSUER */
Object mark_not_to_strip_text_star_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,335);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-NOT-TO-STRIP-TEXT-*-COMMAND-TRANSLATOR */
Object mark_not_to_strip_text_star_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,336);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qmark_not_to_strip_text_star)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmark_not_to_strip_text_star,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmark_not_to_strip_text;  /* mark-not-to-strip-text */

/* COM-MARK-NOT-TO-STRIP-TEXT */
Object com_mark_not_to_strip_text(item)
    Object item;
{
    x_note_fn_call(225,337);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qmark_not_to_strip_text))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)1L));
    else
	return VALUES_1(Nil);
}

/* MARK-NOT-TO-STRIP-TEXT-COMMAND-PURSUER */
Object mark_not_to_strip_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,338);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MARK-NOT-TO-STRIP-TEXT-COMMAND-TRANSLATOR */
Object mark_not_to_strip_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,339);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qmark_not_to_strip_text)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmark_not_to_strip_text,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qremove_do_not_strip_text_mark_star;  /* remove-do-not-strip-text-mark-* */

/* COM-REMOVE-DO-NOT-STRIP-TEXT-MARK-* */
Object com_remove_do_not_strip_text_mark_star(item)
    Object item;
{
    x_note_fn_call(225,340);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qremove_do_not_strip_text_mark_star))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-DO-NOT-STRIP-TEXT-MARK-*-COMMAND-PURSUER */
Object remove_do_not_strip_text_mark_star_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,341);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-DO-NOT-STRIP-TEXT-MARK-*-COMMAND-TRANSLATOR */
Object remove_do_not_strip_text_mark_star_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,342);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qremove_do_not_strip_text_mark_star)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qremove_do_not_strip_text_mark_star,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qremove_do_not_strip_text_mark;  /* remove-do-not-strip-text-mark */

/* COM-REMOVE-DO-NOT-STRIP-TEXT-MARK */
Object com_remove_do_not_strip_text_mark(item)
    Object item;
{
    x_note_fn_call(225,343);
    if (of_class_p_function(item,Qitem) && strip_choice_obtains_p(item,
	    Qremove_do_not_strip_text_mark))
	return set_stripping_flags_as_specified(item,FIX((SI_Long)0L),
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-DO-NOT-STRIP-TEXT-MARK-COMMAND-PURSUER */
Object remove_do_not_strip_text_mark_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, item;

    x_note_fn_call(225,344);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    item = CAR(gensymed_symbol);
    item = command_argument_value(item);
    if (EQ(item,Plus_missing_argument_plus))
	return VALUES_3(Qitem,Qitem,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* REMOVE-DO-NOT-STRIP-TEXT-MARK-COMMAND-TRANSLATOR */
Object remove_do_not_strip_text_mark_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object item, temp;

    x_note_fn_call(225,345);
    item = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qitem);
    if (item) {
	if (strip_choice_obtains_p(item,Qremove_do_not_strip_text_mark)) {
	    temp = item;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qremove_do_not_strip_text_mark,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qreadout_table;      /* readout-table */

static Object Qexpressions_to_display;  /* expressions-to-display */

/* COM-EDIT-EXPRESSION-OF-READOUT-TABLE */
Object com_edit_expression_of_readout_table(readout_table,slot_name)
    Object readout_table, slot_name;
{
    x_note_fn_call(225,346);
    if (of_class_p_function(readout_table,Qreadout_table) && slot_name && 
	    EQ(slot_name,Qexpressions_to_display) && 
	    item_is_either_not_permanent_or_from_an_editable_module_p(readout_table))
	return enter_editing_context(2,readout_table,Qexpressions_to_display);
    else
	return VALUES_1(Nil);
}

/* EDIT-EXPRESSION-OF-READOUT-TABLE-COMMAND-PURSUER */
Object edit_expression_of_readout_table_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, readout_table, slot_name;

    x_note_fn_call(225,347);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    readout_table = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    slot_name = CAR(gensymed_symbol);
    readout_table = command_argument_value(readout_table);
    slot_name = command_argument_value(slot_name);
    if (EQ(readout_table,Plus_missing_argument_plus))
	return VALUES_3(Qreadout_table,Qreadout_table,FIX((SI_Long)0L));
    else if (EQ(slot_name,Plus_missing_argument_plus))
	return VALUES_3(Qslot_name,Qslot_name,FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qedit_expression_of_readout_table;  /* edit-expression-of-readout-table */

/* EDIT-EXPRESSION-OF-READOUT-TABLE-COMMAND-TRANSLATOR */
Object edit_expression_of_readout_table_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object readout_table, slot_name, temp, temp_1;

    x_note_fn_call(225,348);
    readout_table = find_frame_of_class_in_mouse_pointer(mouse_pointer,
	    Qreadout_table);
    slot_name = slot_name_blackboard_function(mouse_pointer);
    if (readout_table && slot_name) {
	if (EQ(slot_name,Qexpressions_to_display) && 
		item_is_either_not_permanent_or_from_an_editable_module_p(readout_table)) 
		    {
	    temp = readout_table;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = slot_name;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qedit_expression_of_readout_table,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qname_box;           /* name-box */

/* COM-HIDE-NAME */
Object com_hide_name(block)
    Object block;
{
    Object ui_command, gensymed_symbol, temp;

    x_note_fn_call(225,349);
    if (of_class_p_function(block,Qname_box)) {
	ui_command = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdelete),
		Qui_command_named);
	if (ui_command) {
	    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
	    temp = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    return FUNCALL_1(temp,block);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* HIDE-NAME-COMMAND-PURSUER */
Object hide_name_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, block;

    x_note_fn_call(225,350);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    block = CAR(gensymed_symbol);
    block = command_argument_value(block);
    if (EQ(block,Plus_missing_argument_plus))
	return VALUES_3(Qblock,Qname_box,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qhide_name;          /* hide-name */

/* HIDE-NAME-COMMAND-TRANSLATOR */
Object hide_name_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object block, temp;

    x_note_fn_call(225,351);
    block = find_frame_of_class_in_mouse_pointer(mouse_pointer,Qname_box);
    if (block) {
	if (T) {
	    temp = block;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qhide_name,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshort_main_menu;    /* short-main-menu */

static Object Qmain_menu;          /* main-menu */

/* COM-MAIN-MENU */
Object com_main_menu()
{
    x_note_fn_call(225,352);
    return post_menu_named_function(Short_menus_qm ? Qshort_main_menu : 
	    Qmain_menu,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

/* MAIN-MENU-COMMAND-TRANSLATOR */
Object main_menu_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,353);
    if (T)
	return make_partial_command(Qmain_menu,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qload_merge_save;    /* load-merge-save */

/* COM-LOAD-MERGE-SAVE */
Object com_load_merge_save()
{
    x_note_fn_call(225,354);
    return post_menu_named_function(Qload_merge_save,Nil,Nil,Nil,Nil,Nil,
	    Nil,Nil);
}

/* LOAD-MERGE-SAVE-COMMAND-TRANSLATOR */
Object load_merge_save_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,355);
    if (T)
	return make_partial_command(Qload_merge_save,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qrun_options;        /* run-options */

/* COM-RUN-OPTIONS */
Object com_run_options()
{
    x_note_fn_call(225,356);
    return post_menu_named_function(Qrun_options,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

/* RUN-OPTIONS-COMMAND-TRANSLATOR */
Object run_options_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,357);
    if (T)
	return make_partial_command(Qrun_options,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qworkspace_menu;     /* workspace-menu */

static Object Qworkspace_miscellany;  /* workspace-miscellany */

static Object Qshort_miscellany_menu;  /* short-miscellany-menu */

static Object Qmiscellany_menu;    /* miscellany-menu */

/* COM-MISCELLANY */
Object com_miscellany(mouse_pointer)
    Object mouse_pointer;
{
    Object menu_name;

    x_note_fn_call(225,358);
    if (mouse_pointer) {
	if (menu_obtains_p(Qworkspace_menu,mouse_pointer))
	    menu_name = Qworkspace_miscellany;
	else if (Short_menus_qm)
	    menu_name = Qshort_miscellany_menu;
	else
	    menu_name = Qmiscellany_menu;
	return post_menu_named_function(menu_name,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qmouse_pointer;      /* mouse-pointer */

/* MISCELLANY-COMMAND-PURSUER */
Object miscellany_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, mouse_pointer;

    x_note_fn_call(225,359);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    mouse_pointer = CAR(gensymed_symbol);
    mouse_pointer = command_argument_value(mouse_pointer);
    if (EQ(mouse_pointer,Plus_missing_argument_plus))
	return VALUES_3(Qmouse_pointer,Qmouse_pointer,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

static Object Qmiscellany;         /* miscellany */

/* MISCELLANY-COMMAND-TRANSLATOR */
Object miscellany_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, temp;

    x_note_fn_call(225,360);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (mouse_pointer_1) {
	if (T) {
	    temp = mouse_pointer_1;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmiscellany,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qother_edits;        /* other-edits */

/* COM-OTHER-EDITS */
Object com_other_edits(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(225,361);
    if (mouse_pointer && menu_obtains_p(Qfreeform_table,mouse_pointer))
	return post_menu_named_function(Qother_edits,Nil,Nil,Nil,Nil,Nil,
		Nil,Nil);
    else
	return VALUES_1(Nil);
}

/* OTHER-EDITS-COMMAND-PURSUER */
Object other_edits_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, mouse_pointer;

    x_note_fn_call(225,362);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    mouse_pointer = CAR(gensymed_symbol);
    mouse_pointer = command_argument_value(mouse_pointer);
    if (EQ(mouse_pointer,Plus_missing_argument_plus))
	return VALUES_3(Qmouse_pointer,Qmouse_pointer,FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* OTHER-EDITS-COMMAND-TRANSLATOR */
Object other_edits_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, temp;

    x_note_fn_call(225,363);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (mouse_pointer_1) {
	if (menu_obtains_p(Qfreeform_table,mouse_pointer_1)) {
	    temp = mouse_pointer_1;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qother_edits,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-CUT-SELECTED-TEXT */
Object com_cut_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,364);
    if (text_region && edit_context) {
	if (empty_text_region_p(text_region))
	    return delete_frame(text_region);
	else {
	    current_edit_state = edit_context;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		    1);
	      current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		      0);
		result = do_cut_within_editor(0);
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext_region;        /* text-region */

static Object Qblock_of_selection_focus;  /* block-of-selection-focus */

static Object Qedit_context;       /* edit-context */

static Object Qworkstation_context_specifics;  /* workstation-context-specifics */

/* CUT-SELECTED-TEXT-COMMAND-PURSUER */
Object cut_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,365);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qcut_selected_text;  /* cut-selected-text */

/* CUT-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object cut_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,366);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcut_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-COPY-SELECTED-TEXT */
Object com_copy_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,367);
    if (text_region && edit_context) {
	current_edit_state = edit_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		  0);
	    if ( !TRUEP(empty_text_region_p(text_region)))
		coerce_text_region_to_scrap(text_region);
	    result = delete_frame(text_region);
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* COPY-SELECTED-TEXT-COMMAND-PURSUER */
Object copy_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,368);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qcopy_selected_text;  /* copy-selected-text */

/* COPY-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object copy_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,369);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcopy_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qpaste;              /* paste */

static Object Qpending_delete_type_in;  /* pending-delete-type-in */

/* COM-PASTE-OVER-SELECTED-TEXT */
Object com_paste_over_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object ui_command, gensymed_symbol, temp;

    x_note_fn_call(225,370);
    if (text_region && edit_context && 
	    text_can_be_pasted_in_current_workstation_p()) {
	ui_command = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpaste),
		Qui_command_named);
	if (ui_command) {
	    gensymed_symbol = ISVREF(ui_command,(SI_Long)4L);
	    temp = SYMBOLP(gensymed_symbol) ? 
		    SYMBOL_FUNCTION(gensymed_symbol) : gensymed_symbol;
	    FUNCALL_1(temp,edit_context);
	}
	return return_from_current_workstation_context(2,
		Type_of_current_workstation_context,Qpending_delete_type_in);
    }
    else
	return VALUES_1(Nil);
}

/* PASTE-OVER-SELECTED-TEXT-COMMAND-PURSUER */
Object paste_over_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,371);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qpaste_over_selected_text;  /* paste-over-selected-text */

/* PASTE-OVER-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object paste_over_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,372);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (text_can_be_pasted_in_current_workstation_p()) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qpaste_over_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-DELETE-SELECTED-TEXT */
Object com_delete_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,373);
    if (text_region && edit_context) {
	current_edit_state = edit_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		  0);
	    result = do_delete_within_editor();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-SELECTED-TEXT-COMMAND-PURSUER */
Object delete_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,374);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qdelete_selected_text;  /* delete-selected-text */

/* DELETE-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object delete_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,375);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qdelete_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-INSERT-SELECTED-TEXT */
Object com_insert_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,376);
    if (text_region && edit_context) {
	if (empty_text_region_p(text_region))
	    return delete_frame(text_region);
	else {
	    current_edit_state = edit_context;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		    1);
	      current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		      0);
		result = do_insert_within_editor();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

/* INSERT-SELECTED-TEXT-COMMAND-PURSUER */
Object insert_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,377);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qinsert_selected_text;  /* insert-selected-text */

/* INSERT-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object insert_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,378);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qinsert_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-COPY-AND-INSERT-SELECTED-TEXT */
Object com_copy_and_insert_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,379);
    if (text_region && edit_context) {
	if (empty_text_region_p(text_region))
	    return delete_frame(text_region);
	else {
	    current_edit_state = edit_context;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		    1);
	      current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		      0);
		result = do_copy_and_insert_within_editor();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

/* COPY-AND-INSERT-SELECTED-TEXT-COMMAND-PURSUER */
Object copy_and_insert_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,380);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qcopy_and_insert_selected_text;  /* copy-and-insert-selected-text */

/* COPY-AND-INSERT-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object copy_and_insert_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,381);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcopy_and_insert_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-MOVE-SELECTED-TEXT */
Object com_move_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,382);
    if (text_region && edit_context) {
	current_edit_state = edit_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		  0);
	    if (empty_text_region_p(text_region))
		result = delete_frame(text_region);
	    else
		result = do_move_within_editor();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* MOVE-SELECTED-TEXT-COMMAND-PURSUER */
Object move_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,383);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qmove_selected_text;  /* move-selected-text */

/* MOVE-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object move_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,384);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qmove_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-CUT-AND-INSERT-SELECTED-TEXT */
Object com_cut_and_insert_selected_text(text_region,edit_context)
    Object text_region, edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,385);
    if (text_region && edit_context) {
	if (empty_text_region_p(text_region))
	    return delete_frame(text_region);
	else {
	    current_edit_state = edit_context;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		    1);
	      current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	      PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		      0);
		result = do_cut_and_insert_within_editor();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
    }
    else
	return VALUES_1(Nil);
}

/* CUT-AND-INSERT-SELECTED-TEXT-COMMAND-PURSUER */
Object cut_and_insert_selected_text_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, text_region, edit_context;

    x_note_fn_call(225,386);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    text_region = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    edit_context = CAR(gensymed_symbol);
    text_region = command_argument_value(text_region);
    edit_context = command_argument_value(edit_context);
    if (EQ(text_region,Plus_missing_argument_plus))
	return VALUES_3(Qtext_region,Qblock_of_selection_focus,
		FIX((SI_Long)0L));
    else if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)1L));
    else
	return VALUES_1(Qnil);
}

static Object Qcut_and_insert_selected_text;  /* cut-and-insert-selected-text */

/* CUT-AND-INSERT-SELECTED-TEXT-COMMAND-TRANSLATOR */
Object cut_and_insert_selected_text_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object text_region, edit_context, temp, temp_1;

    x_note_fn_call(225,387);
    text_region = block_of_selection_focus_blackboard_function(mouse_pointer);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (text_region && edit_context) {
	if (T) {
	    temp = text_region;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    temp_1 = snapshot_command_argument(temp);
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qcut_and_insert_selected_text,
		    slot_value_list_2(temp_1,snapshot_command_argument(temp)));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COM-PASTE */
Object com_paste(edit_context)
    Object edit_context;
{
    Object current_edit_state, current_edit_workspace;
    Declare_special(2);
    Object result;

    x_note_fn_call(225,388);
    if (edit_context) {
	current_edit_state = edit_context;
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_edit_workspace,Qcurrent_edit_workspace,current_edit_workspace,
		  0);
	    result = do_paste_within_editor();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PASTE-COMMAND-PURSUER */
Object paste_command_pursuer(partial_command)
    Object partial_command;
{
    Object gensymed_symbol, edit_context;

    x_note_fn_call(225,389);
    gensymed_symbol = ISVREF(partial_command,(SI_Long)2L);
    edit_context = CAR(gensymed_symbol);
    edit_context = command_argument_value(edit_context);
    if (EQ(edit_context,Plus_missing_argument_plus))
	return VALUES_3(Qedit_context,Qworkstation_context_specifics,
		FIX((SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* PASTE-COMMAND-TRANSLATOR */
Object paste_command_translator(mouse_pointer)
    Object mouse_pointer;
{
    Object edit_context, temp;

    x_note_fn_call(225,390);
    edit_context = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    if (edit_context) {
	if (T) {
	    temp = edit_context;
	    if (temp);
	    else
		temp = Plus_missing_argument_plus;
	    return make_partial_command(Qpaste,
		    slot_value_cons_1(snapshot_command_argument(temp),Nil));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTE-CATEGORY-MEMBERS */
Object compute_category_members(category_name)
    Object category_name;
{
    Object category_qm;

    x_note_fn_call(225,391);
    category_qm = get(category_name,
	    Current_indicator_for_category_of_this_name,_);
    if (category_qm)
	return compute_category_members_1(category_qm);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_category_for_token_g2_struct;  /* g2-defstruct-structure-name::category-for-token-g2-struct */

/* COMPUTE-CATEGORY-MEMBERS-1 */
Object compute_category_members_1(category)
    Object category;
{
    Object result_1, symbol, ab_loop_list_;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_, category_1;
    Object ab_loop_list__2, symbols;
    char temp;

    x_note_fn_call(225,392);
    if (SIMPLE_VECTOR_P(category) && EQ(ISVREF(category,(SI_Long)0L),
	    Qg2_defstruct_structure_name_category_for_token_g2_struct))
	return gensym_cons_1(ISVREF(category,(SI_Long)7L),Nil);
    else {
	result_1 = Nil;
	symbol = Nil;
	ab_loop_list_ = ISVREF(category,(SI_Long)9L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	symbol = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensym_modify_macro_using_test_arg_1 = symbol;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = result_1;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__1 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	x_element = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_1:;
	result_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	goto next_loop;
      end_loop:;
	category_1 = Nil;
	ab_loop_list_ = ISVREF(category,(SI_Long)10L);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	category_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	symbol = Nil;
	ab_loop_list__1 = compute_category_members_1(category_1);
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	symbol = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	gensym_modify_macro_using_test_arg_1 = symbol;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = result_1;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__2 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_4;
	x_element = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	goto next_loop_4;
      end_loop_4:
	temp = TRUEP(Qnil);
      end_2:;
	result_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	goto next_loop_3;
      end_loop_3:;
	goto next_loop_2;
      end_loop_2:;
	if (get_directory_contents(ISVREF(category,(SI_Long)7L))) {
	    symbols = 
		    flatten_gensym_tree(get_directory_contents(ISVREF(category,
		    (SI_Long)7L)));
	    symbol = Nil;
	    ab_loop_list_ = symbols;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensym_modify_macro_using_test_arg_1 = symbol;
	    car_1 = gensym_modify_macro_using_test_arg_1;
	    cdr_1 = result_1;
	    key_result = car_1;
	    x_element = Nil;
	    ab_loop_list__1 = cdr_1;
	    ab_loop_it_ = Nil;
	  next_loop_6:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_6;
	    x_element = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_3;
	    }
	    goto next_loop_6;
	  end_loop_6:
	    temp = TRUEP(Qnil);
	  end_3:;
	    result_1 = temp ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	    goto next_loop_5;
	  end_loop_5:;
	    reclaim_gensym_list_1(symbols);
	}
	return nreverse(result_1);
    }
}

/* FLATTEN-GENSYM-TREE */
Object flatten_gensym_tree(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(225,393);
    if ( !TRUEP(tree))
	return VALUES_1(Nil);
    else if (ATOM(tree))
	return gensym_cons_1(tree,Nil);
    else if (CONSP(tree)) {
	temp = flatten_gensym_tree(CAR(tree));
	return VALUES_1(nconc2(temp,flatten_gensym_tree(CDR(tree))));
    }
    else
	return VALUES_1(Qnil);
}

static Object Qslot_value_writer;  /* slot-value-writer */

/* SLOT-VALUE-AS-STRING */
Object slot_value_as_string(frame,slot_name)
    Object frame, slot_name;
{
    Object slot_description, slot_value, type_of_slot_qm;
    Object grammar_category_symbol, slot_value_writer_qm;
    Object write_symbols_in_lower_case_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(225,394);
    slot_description = 
	    get_slot_description_of_class_description_function(slot_name,
	    ISVREF(frame,(SI_Long)1L),Nil);
    slot_value = get_slot_description_value(frame,slot_description);
    type_of_slot_qm = get_type_of_slot_if_any(2,frame,slot_name);
    grammar_category_symbol = SECOND(type_of_slot_qm);
    slot_value_writer_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_symbol),
	    Qslot_value_writer);
    write_symbols_in_lower_case_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
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
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
		    (SI_Long)16L));
	    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		    1);
	      current_twriting_output_type = Qwide_string;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		      0);
		if (slot_value_writer_qm)
		    inline_funcall_2(slot_value_writer_qm,slot_value,frame);
		result = copy_out_current_wide_string();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qslot_value_compiler;  /* slot-value-compiler */

/* PUT-SYMBOL-VALUED-SLOT */
Object put_symbol_valued_slot(frame,slot,string_qm)
    Object frame, slot, string_qm;
{
    Object type_qm, category_qm, compiler_qm, parse, compiled_value, error_qm;
    Object result;

    x_note_fn_call(225,395);
    type_qm = get_type_of_slot_if_any(2,frame,slot);
    category_qm = SECOND(type_qm);
    compiler_qm = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_qm),
	    Qslot_value_compiler);
    if (string_qm) {
	if (IFIX(lengthw(string_qm)) == (SI_Long)0L)
	    parse = Nil;
	else {
	    upcase_text_string_in_place(string_qm);
	    parse = intern_wide_string_no_reclaim(1,string_qm);
	}
	if (compiler_qm)
	    result = FUNCALL_3(compiler_qm,parse,frame,slot);
	else
	    result = VALUES_1(parse);
	MVS_2(result,compiled_value,error_qm);
	if ( !TRUEP(error_qm))
	    return change_slot_value(3,frame,slot,compiled_value);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Alternate_symbols_for_translation, Qalternate_symbols_for_translation);

/* MAKE-DIALOG-SPEC */
Object make_dialog_spec(dialog_spec_type,dialog_spec_caption,dialog_spec_x,
	    dialog_spec_y,dialog_spec_width,dialog_spec_height,
	    dialog_spec_style,dialog_spec_exstyle,dialog_spec_flags,
	    dialog_spec_font,dialog_spec_font_size,dialog_spec_controls)
    Object dialog_spec_type, dialog_spec_caption, dialog_spec_x, dialog_spec_y;
    Object dialog_spec_width, dialog_spec_height, dialog_spec_style;
    Object dialog_spec_exstyle, dialog_spec_flags, dialog_spec_font;
    Object dialog_spec_font_size, dialog_spec_controls;
{
    Object temp;

    x_note_fn_call(225,396);
    temp = CONS(dialog_spec_controls,Nil);
    temp = CONS(dialog_spec_font_size,temp);
    temp = CONS(dialog_spec_font,temp);
    temp = CONS(dialog_spec_flags,temp);
    temp = CONS(dialog_spec_exstyle,temp);
    temp = CONS(dialog_spec_style,temp);
    temp = CONS(dialog_spec_height,temp);
    temp = CONS(dialog_spec_width,temp);
    temp = CONS(dialog_spec_y,temp);
    temp = CONS(dialog_spec_x,temp);
    temp = CONS(dialog_spec_caption,temp);
    return VALUES_1(CONS(dialog_spec_type,temp));
}

/* MAKE-DIALOG-CONTROL */
Object make_dialog_control(dialog_control_class,dialog_control_id,
	    dialog_control_caption,dialog_control_x,dialog_control_y,
	    dialog_control_width,dialog_control_height,
	    dialog_control_style,dialog_control_exstyle,
	    dialog_control_flags,dialog_control_data)
    Object dialog_control_class, dialog_control_id, dialog_control_caption;
    Object dialog_control_x, dialog_control_y, dialog_control_width;
    Object dialog_control_height, dialog_control_style, dialog_control_exstyle;
    Object dialog_control_flags, dialog_control_data;
{
    Object temp;

    x_note_fn_call(225,397);
    temp = CONS(dialog_control_data,Nil);
    temp = CONS(dialog_control_flags,temp);
    temp = CONS(dialog_control_exstyle,temp);
    temp = CONS(dialog_control_style,temp);
    temp = CONS(dialog_control_height,temp);
    temp = CONS(dialog_control_width,temp);
    temp = CONS(dialog_control_y,temp);
    temp = CONS(dialog_control_x,temp);
    temp = CONS(dialog_control_caption,temp);
    temp = CONS(dialog_control_id,temp);
    return VALUES_1(CONS(dialog_control_class,temp));
}

/* FIND-CONTROL-IN-DIALOG-SPEC */
Object find_control_in_dialog_spec(id,spec)
    Object id, spec;
{
    Object control, temp, ab_loop_list_;

    x_note_fn_call(225,398);
    control = Nil;
    temp = CDDDDR(spec);
    temp = CDDDDR(temp);
    temp = CDDDR(temp);
    ab_loop_list_ = CAR(temp);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    control = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDR(control);
    temp = CAR(temp);
    if (EQL(id,temp))
	return VALUES_1(control);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* TRANSLATE-LABEL-FOR-DIALOG */
Object translate_label_for_dialog(label)
    Object label;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object element, ab_loop_list_, string_qm, symbol, temp, alt_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(225,399);
    if ( !TRUEP(label))
	return VALUES_1(Nil);
    else if (STRINGP(label))
	return copy_as_wide_string(label);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(label) != (SI_Long)0L)
	return copy_wide_string(label);
    else if (LISTP(label)) {
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
		  element = Nil;
		  ab_loop_list_ = label;
		  string_qm = Nil;
		next_loop:
		  if ( !TRUEP(ab_loop_list_))
		      goto end_loop;
		  element = M_CAR(ab_loop_list_);
		  ab_loop_list_ = M_CDR(ab_loop_list_);
		  string_qm = translate_label_for_dialog(element);
		  if (string_qm)
		      twrite_general_string(string_qm);
		  goto next_loop;
		end_loop:;
		  result = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else if (SYMBOLP(label)) {
	symbol = translation_for_symbol_qm(1,label) ? label : Nil;
	if (symbol);
	else {
	    temp = assq_function(label,Alternate_symbols_for_translation);
	    alt_qm = CDR(temp);
	    symbol = alt_qm && translation_for_symbol_qm(1,alt_qm) ? 
		    alt_qm : Nil;
	}
	if (symbol);
	else
	    symbol = label;
	return translated_string_for_symbol(3,symbol,T,T);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qws_visible;         /* ws-visible */

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

/* TRANSLATE-STYLE-FOR-DIALOG */
Object translate_style_for_dialog(style)
    Object style;
{
    Object temp, ab_loop_destructure_, high, low, e, ab_loop_list_, sym;
    Object not_qm, hi, lo, ab_loop_desetq_;

    x_note_fn_call(225,400);
    temp = assoc_eql(Qws_visible,N_32bit_constants);
    ab_loop_destructure_ = CDR(temp);
    high = Nil;
    low = Nil;
    high = CAR(ab_loop_destructure_);
    low = CDR(ab_loop_destructure_);
    e = Nil;
    ab_loop_list_ = style;
    sym = Nil;
    not_qm = Nil;
    hi = Nil;
    lo = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    e = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    sym = CONSP(e) ? CADR(e) : e;
    not_qm = CONSP(e) ? (EQ(CAR(e),Qnot) ? T : Nil) : Qnil;
    temp = assoc_eql(sym,N_32bit_constants);
    temp = CDR(temp);
    if (temp);
    else {
	temp = assq_function(sym,list_constant_9);
	temp = CDR(temp);
    }
    if (temp);
    else
	temp = list_constant_10;
    ab_loop_desetq_ = temp;
    hi = CAR(ab_loop_desetq_);
    lo = CDR(ab_loop_desetq_);
    if (not_qm) {
	high = FIX(IFIX(high) &  ~IFIX(hi));
	low = FIX(IFIX(low) &  ~IFIX(lo));
    }
    else {
	high = FIXNUM_LOGIOR(high,hi);
	low = FIXNUM_LOGIOR(low,lo);
    }
    goto next_loop;
  end_loop:
    return make_32bit_integer(high,low);
    return VALUES_1(Qnil);
}

static Object Qidok;               /* idok */

static Object Qidcancel;           /* idcancel */

static Object Qidabort;            /* idabort */

static Object Qidretry;            /* idretry */

static Object Qidignore;           /* idignore */

static Object Qidyes;              /* idyes */

static Object Qidno;               /* idno */

/* TRANSLATE-CONTROL-ID-FOR-DIALOG */
Object translate_control_id_for_dialog(id)
    Object id;
{
    x_note_fn_call(225,401);
    if (EQ(id,Qidok))
	return VALUES_1(FIX((SI_Long)1L));
    else if (EQ(id,Qidcancel))
	return VALUES_1(FIX((SI_Long)2L));
    else if (EQ(id,Qidabort))
	return VALUES_1(FIX((SI_Long)3L));
    else if (EQ(id,Qidretry))
	return VALUES_1(FIX((SI_Long)4L));
    else if (EQ(id,Qidignore))
	return VALUES_1(FIX((SI_Long)5L));
    else if (EQ(id,Qidyes))
	return VALUES_1(FIX((SI_Long)6L));
    else if (EQ(id,Qidno))
	return VALUES_1(FIX((SI_Long)7L));
    else
	return VALUES_1(id);
}

static Object Qstatic;             /* static */

static Object Qanchor_top;         /* anchor-top */

static Object Qanchor_bottom;      /* anchor-bottom */

static Object Qanchor_left;        /* anchor-left */

static Object Qanchor_right;       /* anchor-right */

static Object Qresizeable;         /* resizeable */

/* TRANSLATE-FLAGS-FOR-DIALOG */
Object translate_flags_for_dialog(class_1,flags)
    Object class_1, flags;
{
    Object result_1, flag, ab_loop_list_, value;

    x_note_fn_call(225,402);
    result_1 = EQ(class_1,Qstatic) ? FIX((SI_Long)32L) : FIX((SI_Long)0L);
    flag = Nil;
    ab_loop_list_ = flags;
    value = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    flag = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(flag,Qanchor_top))
	value = FIX((SI_Long)1L);
    else if (EQ(flag,Qanchor_bottom))
	value = FIX((SI_Long)2L);
    else if (EQ(flag,Qanchor_left))
	value = FIX((SI_Long)4L);
    else if (EQ(flag,Qanchor_right))
	value = FIX((SI_Long)8L);
    else if (EQ(flag,Qresizeable))
	value = FIX((SI_Long)16L);
    else if (EQ(flag,Qignore))
	value = FIX((SI_Long)32L);
    else
	value = FIX((SI_Long)0L);
    result_1 = FIXNUM_LOGIOR(result_1,flag);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object Qdialog;             /* dialog */

/* TRANSLATE-DIALOG-SPEC */
Object translate_dialog_spec(spec)
    Object spec;
{
    Object gensymed_symbol, type, caption, x, y, width, height, style, exstyle;
    Object flags, font, font_size, controls, gensymed_symbol_1, car_new_value;
    Object class_1, id, data_qm, ab_loop_list_, control, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;
    Object gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(225,403);
    gensymed_symbol = spec;
    type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    caption = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    x = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    y = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    width = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    height = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    style = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    exstyle = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    flags = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    font = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    font_size = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    controls = CAR(gensymed_symbol);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)12L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = type;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = translate_label_for_dialog(caption);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = x;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = y;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = width;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = height;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = translate_style_for_dialog(style);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = translate_style_for_dialog(exstyle);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = translate_flags_for_dialog(Qdialog,flags);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = copy_as_wide_string(font);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = font_size;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    class_1 = Nil;
    id = Nil;
    caption = Nil;
    x = Nil;
    y = Nil;
    width = Nil;
    height = Nil;
    style = Nil;
    exstyle = Nil;
    flags = Nil;
    data_qm = Nil;
    ab_loop_list_ = controls;
    control = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    class_1 = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    id = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    caption = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    x = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    y = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    width = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    height = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    style = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    exstyle = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    flags = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    temp = CDR(temp);
    data_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol_2 = make_gensym_list_1(FIX((SI_Long)10L));
    gensymed_symbol_3 = gensymed_symbol_2;
    M_CAR(gensymed_symbol_3) = class_1;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = translate_control_id_for_dialog(id);
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = translate_label_for_dialog(caption);
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = x;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = y;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = width;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    M_CAR(gensymed_symbol_3) = height;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = translate_style_for_dialog(style);
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = translate_style_for_dialog(exstyle);
    M_CAR(gensymed_symbol_3) = car_new_value;
    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
    car_new_value = translate_flags_for_dialog(class_1,flags);
    M_CAR(gensymed_symbol_3) = car_new_value;
    control = nconc2(gensymed_symbol_2,data_qm ? 
	    gensym_cons_1(copy_gensym_tree_with_text_strings(data_qm),Nil) 
	    : Nil);
    ab_loopvar__2 = gensym_cons_1(control,Nil);
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
    M_CAR(gensymed_symbol_1) = ab_loopvar_;
    return VALUES_1(gensymed_symbol);
}

static Object Qdisable;            /* disable */

static Object Qhide;               /* hide */

/* MODIFY-CONTROL-IN-DIALOG-SPEC */
Object modify_control_in_dialog_spec(how,id,spec)
    Object how, id, spec;
{
    Object control_qm, temp, old_style, new_style, car_arg;
    SI_Long temp_1;

    x_note_fn_call(225,404);
    control_qm = 
	    find_control_in_dialog_spec(translate_control_id_for_dialog(id),
	    spec);
    if (control_qm) {
	temp = CDDDDR(control_qm);
	temp = CDDDR(temp);
	old_style = CAR(temp);
	if (EQ(how,Qdisable))
	    temp = FIX(IFIX(n_32bit_integer_high_part(old_style)) | 
		    (SI_Long)2048L);
	else if (EQ(how,Qhide)) {
	    temp_1 = IFIX(n_32bit_integer_high_part(old_style));
	    temp = FIX(temp_1 &  ~(SI_Long)4096L);
	}
	else
	    temp = n_32bit_integer_high_part(old_style);
	new_style = make_32bit_integer(temp,
		n_32bit_integer_low_part(old_style));
	temp = CDDDDR(control_qm);
	car_arg = CDDDR(temp);
	M_CAR(car_arg) = new_style;
	return reclaim_32bit_integer(old_style);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_login_dialog, Qnative_login_dialog);

Object Alternate_translations_for_login_dialogs = UNBOUND;

static Object Qcombobox;           /* combobox */

/* RESIZE-NATIVE-LOGIN-DIALOG */
Object resize_native_login_dialog(spec)
    Object spec;
{
    Object control, temp, ab_loop_list_, need, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_maxmin_fl_, delta, width, car_arg, incff_1_arg;
    Object car_new_value, temp_1;
    SI_Long temp_2;

    x_note_fn_call(225,405);
    control = Nil;
    temp = CDDDDR(spec);
    temp = CDDDDR(temp);
    temp = CDDDR(temp);
    ab_loop_list_ = CAR(temp);
    need = Nil;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loopvar__1 = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    control = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDDR(control);
    need = FIX((SI_Long)8L + (SI_Long)3L * IFIX(lengthw(stringw(CAR(temp)))));
    temp = CDR(control);
    if ( !TRUEP(CAR(temp)) && EQ(CAR(control),Qstatic)) {
	temp = CDDDDR(control);
	temp = CDR(temp);
	ab_loopvar__1 = FIXNUM_MINUS(need,CAR(temp));
	if (ab_loop_maxmin_fl_) {
	    ab_loop_maxmin_fl_ = Nil;
	    ab_loopvar_ = ab_loopvar__1;
	}
	else
	    ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
    }
    goto next_loop;
  end_loop:
    delta = ab_loopvar_;
    goto end_1;
    delta = Qnil;
  end_1:;
    temp = CDDDDR(spec);
    width = CAR(temp);
    if (IFIX(delta) > (SI_Long)0L) {
	control = Nil;
	temp = CDDDDR(spec);
	temp = CDDDDR(temp);
	temp = CDDDR(temp);
	ab_loop_list_ = CAR(temp);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	control = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = CAR(control);
	if (EQ(temp,Qstatic)) {
	    temp = CDR(control);
	    if ( !TRUEP(CAR(temp))) {
		temp = CDDDDR(control);
		car_arg = CDR(temp);
		incff_1_arg = delta;
		car_new_value = FIXNUM_ADD(CAR(car_arg),incff_1_arg);
		M_CAR(car_arg) = car_new_value;
	    }
	}
	else if (EQ(temp,Qedit) || EQ(temp,Qcombobox)) {
	    car_arg = CDDDR(control);
	    incff_1_arg = delta;
	    car_new_value = FIXNUM_ADD(CAR(car_arg),incff_1_arg);
	    M_CAR(car_arg) = car_new_value;
	    temp_1 = CDDDR(control);
	    temp = CDDDDR(control);
	    temp = CDR(temp);
	    temp_2 = IFIX(FIXNUM_ADD(CAR(temp_1),CAR(temp))) + (SI_Long)2L;
	    width = FIX(MAX(IFIX(width),temp_2));
	}
	goto next_loop_1;
      end_loop_1:;
    }
    car_arg = CDDDDR(spec);
    M_CAR(car_arg) = width;
    return VALUES_1(spec);
}

/* NATIVE-LOGIN-DIALOG-P */
Object native_login_dialog_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(225,406);
    if (ISVREF(Miscellaneous_parameters,(SI_Long)28L) && 
	    FIXNUM_LT(Icp_window_protocol_supports_manage_dialog,
	    ISVREF(gensym_window,(SI_Long)11L)) && EQ(ISVREF(gensym_window,
	    (SI_Long)1L),Qicp))
	return VALUES_1( !TRUEP(classic_ui_p(gensym_window)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Native_alias_creation_dialog, Qnative_alias_creation_dialog);

static Object Qg2_login_user_name_qm;  /* g2-login-user-name? */

static Object Qg2_login_user_mode;  /* g2-login-user-mode */

static Object Qg2_login_specific_language_for_this_g2_window_qm;  /* g2-login-specific-language-for-this-g2-window? */

static Object Qg2_user_mode_for_login;  /* g2-user-mode-for-login */

static Object Qlanguage_qm;        /* language? */

static Object Qg2_login_comments;  /* g2-login-comments */

static Object Quser;               /* user */

static Object Qmode;               /* mode */

static Object Qlang;               /* lang */

static Object Qspec;               /* spec */

static Object Qdata;               /* data */

static Object Qbeep;               /* beep */

static Object array_constant_1;    /* # */

static Object list_constant_11;    /* # */

/* POST-NATIVE-LOGIN-DIALOG */
Object post_native_login_dialog varargs_1(int, n)
{
    Object g2_login_state;
    Object beep_qm, gensym_window, g2_login, how_entered, user, mode, language;
    Object all_modes, all_mode_aliases, result_1, ab_loop_list_, is_alias;
    Object alias, ab_loop_list__1, modes, languages, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_qm, alternate_symbols_for_translation, spec, data;
    Object gensymed_symbol, gensymed_symbol_1, temp, arg, new_caption, thing;
    Object car_arg;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, handle;
    Declare_varargs_nonrelocating;
    Declare_special(6);
    Object result;

    x_note_fn_call(225,407);
    INIT_ARGS_nonrelocating();
    g2_login_state = REQUIRED_ARG_nonrelocating();
    beep_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensym_window = Current_workstation_window;
    g2_login = ISVREF(g2_login_state,(SI_Long)3L);
    how_entered = ISVREF(g2_login,(SI_Long)25L);
    user = slot_value_as_string(g2_login,Qg2_login_user_name_qm);
    mode = slot_value_as_string(g2_login,Qg2_login_user_mode);
    language = slot_value_as_string(g2_login,
	    Qg2_login_specific_language_for_this_g2_window_qm);
    all_modes = compute_category_members(Qg2_user_mode_for_login);
    all_mode_aliases = 
	    get_lookup_slot_value_given_default(Kb_configuration,
	    Quser_mode_aliases,Nil);
    if (EQ(how_entered,Qalias_creation)) {
	result_1 = Nil;
	mode = Nil;
	ab_loop_list_ = all_modes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	mode = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	is_alias = Nil;
	alias = Nil;
	ab_loop_list__1 = all_mode_aliases;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	alias = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(mode,ISVREF(alias,(SI_Long)1L))) {
	    is_alias = T;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_1:;
	if ( !TRUEP(is_alias))
	    result_1 = gensym_cons_1(mode,result_1);
	goto next_loop;
      end_loop:;
	modes = gensym_cons_1(CAR(result_1),result_1);
    }
    else
	modes = gensym_cons_1(mode,all_modes);
    languages = gensym_cons_1(language,compute_category_members(Qlanguage_qm));
    if (get_lookup_slot_value_given_default(g2_login,Qg2_login_comments,Nil)) {
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
		  twrite_login_failure_translation_symbol(get_lookup_slot_value_given_default(g2_login,
			  Qg2_login_comments,Nil));
		  message_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    else
	message_qm = Nil;
    alternate_symbols_for_translation = 
	    Alternate_translations_for_login_dialogs;
    PUSH_SPECIAL_WITH_SYMBOL(Alternate_symbols_for_translation,Qalternate_symbols_for_translation,alternate_symbols_for_translation,
	    5);
      spec = EQ(how_entered,Qalias_creation) ? 
	      resize_native_login_dialog(translate_dialog_spec(Native_alias_creation_dialog)) 
	      : 
	      resize_native_login_dialog(translate_dialog_spec(Native_login_dialog));
      if (EQ(how_entered,Qalias_creation))
	  data = gensym_list_4(Quser,Nil,Qmode,modes);
      else {
	  gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
	  gensymed_symbol_1 = gensymed_symbol;
	  M_CAR(gensymed_symbol_1) = Quser;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = user;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = Qmode;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = modes;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = Qlang;
	  gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	  M_CAR(gensymed_symbol_1) = languages;
	  data = gensymed_symbol;
      }
      temp = gensym_list_4(Qspec,spec,Qdata,data);
      arg = nconc2(temp,FIXNUMP(beep_qm) ? gensym_list_2(Qbeep,beep_qm) : Nil);
      handle = (SI_Long)123L;
      if (message_qm) {
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
		    temp = CDR(spec);
		    twrite(CAR(temp));
		    twrite_beginning_of_wide_string(array_constant_1,
			    FIX((SI_Long)3L));
		    twrite_general_string(message_qm);
		    new_caption = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  reclaim_text_string(message_qm);
	  temp = CDR(spec);
	  thing = CAR(temp);
	  if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	      reclaim_wide_string(thing);
	  car_arg = CDR(spec);
	  M_CAR(car_arg) = new_caption;
      }
      if (EQ(ISVREF(gensym_window,(SI_Long)1L),Qicp) &&  
	      !TRUEP(memq_function(how_entered,list_constant_11)))
	  modify_control_in_dialog_spec(Qdisable,Qidcancel,spec);
      else
	  modify_control_in_dialog_spec(Qdisable,Qidabort,spec);
      manage_dialog(gensym_window,FIX((SI_Long)1L),FIX(handle),arg);
      result = reclaim_gensym_tree_with_text_strings(arg);
    POP_SPECIAL();
    return result;
}

/* CANCEL-NATIVE-LOGIN-DIALOG */
Object cancel_native_login_dialog(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(225,408);
    if (native_login_dialog_p(gensym_window))
	return manage_dialog(Current_workstation_window,FIX((SI_Long)2L),
		FIX((SI_Long)123L),Nil);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_g2_login_state_g2_struct;  /* g2-defstruct-structure-name::g2-login-state-g2-struct */

static Object Qg2pvt_choice;       /* g2pvt-choice */

static Object Qpass;               /* pass */

static Object Qg2_login_user_password_qm;  /* g2-login-user-password? */

static Object Qok;                 /* ok */

static Object Qdisconnect;         /* disconnect */

static Object Qcancel;             /* cancel */

/* HANDLE-LOGIN-DIALOG-MESSAGE */
Object handle_login_dialog_message(mouse_pointer)
    Object mouse_pointer;
{
    Object gensym_window, context, event_plist, g2_login, frame_reference;
    Object choice_qm, user_mode_qm, symbolized_user_mode, gensymed_symbol, xa;
    Object ya;
    char temp;

    x_note_fn_call(225,409);
    gensym_window = window_blackboard_function(mouse_pointer);
    context = workstation_context_specifics_blackboard_function(mouse_pointer);
    event_plist = event_plist_blackboard_function(mouse_pointer);
    if (gensym_window && context && event_plist) {
	if (SIMPLE_VECTOR_P(context) && EQ(ISVREF(context,(SI_Long)0L),
		Qg2_defstruct_structure_name_g2_login_state_g2_struct)) {
	    g2_login = ISVREF(context,(SI_Long)3L);
	    frame_reference = Current_frame_serial_number;
	    choice_qm = getf(event_plist,Qg2pvt_choice,_);
	    user_mode_qm = getf(event_plist,Qmode,_);
	    symbolized_user_mode = symbolize(user_mode_qm);
	    if (is_in_ldap_mode_p())
		check_user_ldap(ISVREF(Current_workstation,(SI_Long)20L),
			getf(event_plist,Quser,_),getf(event_plist,Qpass,_));
	    put_symbol_valued_slot(g2_login,Qg2_login_user_name_qm,
		    getf(event_plist,Quser,_));
	    put_symbol_valued_slot(g2_login,Qg2_login_user_password_qm,
		    getf(event_plist,Qpass,_));
	    put_symbol_valued_slot(g2_login,
		    Qg2_login_specific_language_for_this_g2_window_qm,
		    getf(event_plist,Qlang,_));
	    change_slot_value(3,g2_login,Qg2_login_user_mode,
		    symbolized_user_mode);
	    if (EQ(choice_qm,Qok))
		do_g2_login_button(Qend);
	    else if (EQ(choice_qm,Qabort_g2))
		do_g2_login_button(Qdisconnect);
	    else
		do_g2_login_button(Qcancel);
	    gensymed_symbol = ISVREF(g2_login,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(g2_login) ? EQ(ISVREF(g2_login,
		    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(frame_reference))
		temp = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_reference,gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_reference);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_reference),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp)
		return post_native_login_dialog(2,context,FIX((SI_Long)48L));
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Kall;                /* :all */

/* SYMBOLIZE */
Object symbolize(thing)
    Object thing;
{
    x_note_fn_call(225,410);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	return intern_wide_string(1,
		copy_wide_string_with_case_conversion(thing,Kall));
    else if (SYMBOLP(thing))
	return VALUES_1(thing);
    else
	return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_selection_handle_spot_g2_struct;  /* g2-defstruct-structure-name::selection-handle-spot-g2-struct */

static Object Qdefault;            /* default */

static Object Qcircle_slash;       /* circle-slash */

static Object Qmouse_cursor;       /* mouse-cursor */

/* UPDATE-MOUSE-CURSOR */
Object update_mouse_cursor(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, gensym_window, temp;

    x_note_fn_call(225,411);
    spot = spot_blackboard_function(mouse_pointer);
    gensym_window = window_blackboard_function(mouse_pointer);
    if (spot && gensym_window) {
	if ( !(SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
		Qg2_defstruct_structure_name_selection_handle_spot_g2_struct)))
	    temp = Qdefault;
	else if (drag_selection_handle_permitted_p(spot))
	    temp = selection_handle_mouse_cursor(spot);
	else
	    temp = Qcircle_slash;
	return change_ui_property(gensym_window,Qmouse_cursor,temp);
    }
    else
	return VALUES_1(Nil);
}

static Object Qvertex;             /* vertex */

static Object Qresize;             /* resize */

/* DRAG-SELECTION-HANDLE-PERMITTED-P */
Object drag_selection_handle_permitted_p(selection_handle_spot)
    Object selection_handle_spot;
{
    Object temp;

    x_note_fn_call(225,412);
    temp = ISVREF(selection_handle_spot,(SI_Long)6L);
    if (EQ(temp,Qvertex))
	return drag_connection_vertex_permitted_p(ISVREF(selection_handle_spot,
		(SI_Long)4L));
    else if (EQ(temp,Qresize))
	return resize_block_permitted_p(ISVREF(selection_handle_spot,
		(SI_Long)4L));
    else
	return VALUES_1(Nil);
}

/* DRAG-SELECTION-HANDLE */
Object drag_selection_handle(mouse_pointer)
    Object mouse_pointer;
{
    Object spot, mouse_pointer_1, image_plane, x_in_workspace, y_in_workspace;
    Object temp, item_or_items;

    x_note_fn_call(225,413);
    spot = spot_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    if (spot && mouse_pointer_1 && image_plane && x_in_workspace && 
	    y_in_workspace) {
	if (SIMPLE_VECTOR_P(spot) && EQ(ISVREF(spot,(SI_Long)0L),
		Qg2_defstruct_structure_name_selection_handle_spot_g2_struct)) 
		    {
	    temp = ISVREF(spot,(SI_Long)6L);
	    if (EQ(temp,Qvertex))
		item_or_items = ISVREF(spot,(SI_Long)4L);
	    else if (EQ(temp,Qresize))
		item_or_items = 
			compute_blocks_to_resize_from_selection(ISVREF(spot,
			(SI_Long)4L),ISVREF(image_plane,(SI_Long)40L));
	    else
		item_or_items = Qnil;
	    if (item_or_items) {
		requeue_mouse_motion_event(mouse_pointer_1);
		return begin_dragging_selection_handle(image_plane,
			mouse_pointer_1,item_or_items,ISVREF(spot,
			(SI_Long)6L),ISVREF(spot,(SI_Long)7L),
			x_in_workspace,y_in_workspace);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qresize_block_permitted_p;  /* resize-block-permitted-p */

/* COMPUTE-BLOCKS-TO-RESIZE-FROM-SELECTION */
Object compute_blocks_to_resize_from_selection(lead_item,selection)
    Object lead_item, selection;
{
    Object blocks, sublist, car_new_value;

    x_note_fn_call(225,414);
    blocks = compute_filtered_blocks_from_selection(selection,
	    SYMBOL_FUNCTION(Qresize_block_permitted_p));
    sublist = memq_function(lead_item,blocks);
    if (sublist &&  !EQ(lead_item,FIRST(blocks))) {
	car_new_value = FIRST(blocks);
	M_CAR(sublist) = car_new_value;
	M_FIRST(blocks) = lead_item;
    }
    return VALUES_1(blocks);
}

static Object Qmove_object;        /* move-object */

/* RESIZE-BLOCK-PERMITTED-P */
Object resize_block_permitted_p(block)
    Object block;
{
    x_note_fn_call(225,415);
    if (change_size_permitted_p(block))
	return non_menu_choice_permitted_p(Qmove_object,block);
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* DRAW-SELECTION-HANDLES-FOR-CURRENT-IMAGE-PLANE */
Object draw_selection_handles_for_current_image_plane(left,top,right,bottom)
    Object left, top, right, bottom;
{
    Object selection_qm, state_1, thing, color, x2;
    char temp;

    x_note_fn_call(225,416);
    selection_qm = ISVREF(Current_image_plane,(SI_Long)40L);
    if (selection_qm) {
	state_1 = T;
      next_loop:
	if ( !TRUEP(state_1))
	    goto end_loop;
	thing = EQ(state_1,T) ? ISVREF(selection_qm,(SI_Long)2L) : 
		CAR(state_1);
	state_1 = EQ(state_1,T) ? ISVREF(selection_qm,(SI_Long)3L) : 
		CDR(state_1);
	if (thing) {
	    if ( !TRUEP(render_thing_in_xor_overlay_p(thing))) {
		color = EQ(thing,ISVREF(selection_qm,(SI_Long)2L)) ? 
			primary_selection_color(Current_image_plane) : 
			secondary_selection_color(Current_image_plane);
		if (SIMPLE_VECTOR_P(thing) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing)) > 
			(SI_Long)2L &&  !EQ(ISVREF(thing,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(thing,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    draw_selection_handles_for_block(thing,color);
		else if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_connection_g2_struct))
		    draw_selection_handles_for_connection(thing,color);
		else if (text_cell_p(thing))
		    draw_selection_handles_for_text_cell(thing,color);
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_48;  /* "Passed window is not a TWNG window: ~NF" */

/* G2-REGISTER-CALLBACK-ON-TWNG-EXIT */
Object g2_register_callback_on_twng_exit(g2_window,callback)
    Object g2_window, callback;
{
    Object gensym_window, top_of_stack, message_1;

    x_note_fn_call(225,417);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    if (twng_window_p(gensym_window))
	return add_twng_disconnect_callback(gensym_window,callback);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_48,
		g2_window);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* G2-UNREGISTER-CALLBACK-ON-TWNG-EXIT */
Object g2_unregister_callback_on_twng_exit(g2_window,callback)
    Object g2_window, callback;
{
    Object gensym_window, top_of_stack, message_1;

    x_note_fn_call(225,418);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    if (twng_window_p(gensym_window))
	return remove_twng_disconnect_callback(gensym_window,callback);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_48,
		g2_window);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

/* CLEAR-ALL-TWNG-DISCONNECT-CALLBACKS */
Object clear_all_twng_disconnect_callbacks()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_window;
    Object gensym_window_qm, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(225,419);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_window = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      gensym_window_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qg2_window);
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
      g2_window = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      gensym_window_qm = map_g2_window_to_gensym_window(g2_window);
      if (gensym_window_qm && twng_window_p(gensym_window_qm))
	  clear_twng_disconnect_callbacks(gensym_window_qm);
      goto next_loop;
    end_loop_1:
      temp_1 = Qnil;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

static Object string_constant_49;  /* "twng-disconnect-callback" */

/* CALL-TWNG-DISCONNECT-CALLBACKS */
Object call_twng_disconnect_callbacks(gensym_window)
    Object gensym_window;
{
    Object g2_window, callback, ab_loop_list_, callback_proc_qm;

    x_note_fn_call(225,420);
    g2_window = g2_window_for_gensym_window_qm(gensym_window);
    callback = Nil;
    ab_loop_list_ = ISVREF(gensym_window,(SI_Long)69L);
    callback_proc_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    callback = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    callback_proc_qm = get_callback_procedure(6,callback,
	    string_constant_49,list_constant,T,Nil,T);
    if (callback_proc_qm)
	apply_kb_procedure(callback_proc_qm,gensym_cons_1(g2_window,Nil));
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

void commands1_INIT()
{
    Object com_start_1, start_command_translator_1, com_pause_1;
    Object pause_command_translator_1, com_resume_1;
    Object resume_command_translator_1, com_continue_from_breakpoint_1;
    Object continue_from_breakpoint_command_translator_1, com_reset_1;
    Object reset_command_translator_1, com_restart_1;
    Object restart_command_translator_1, com_new_workspace_1;
    Object new_workspace_command_pursuer_1, new_workspace_command_translator_1;
    Object com_get_workspace_1, get_workspace_command_pursuer_1;
    Object get_workspace_command_translator_1, com_inspect_1;
    Object inspect_command_translator_1, com_load_kb_1;
    Object load_kb_command_translator_1, com_merge_kb_1;
    Object merge_kb_command_translator_1, com_load_recent_kb_1;
    Object load_recent_kb_command_pursuer_1;
    Object load_recent_kb_command_translator_1, com_save_kb_1;
    Object save_kb_command_translator_1, com_save_kb_without_asking_1;
    Object save_kb_without_asking_command_translator_1;
    Object com_show_system_table_1, show_system_table_command_pursuer_1;
    Object show_system_table_command_translator_1, com_printer_setup_1;
    Object printer_setup_command_pursuer_1, printer_setup_command_translator_1;
    Object com_change_mode_1, change_mode_command_translator_1;
    Object com_create_new_user_mode_alias_1;
    Object create_new_user_mode_alias_command_translator_1;
    Object com_user_mode_aliases_1, user_mode_aliases_command_translator_1;
    Object com_change_g2_user_mode_1, change_g2_user_mode_command_translator_1;
    Object com_change_g2_user_mode_e_1;
    Object change_g2_user_mode_e_command_translator_1, com_change_password_1;
    Object change_password_command_translator_1;
    Object com_reinstall_authorized_users_1;
    Object reinstall_authorized_users_command_translator_1, com_short_menus_1;
    Object short_menus_command_translator_1, com_long_menus_1;
    Object long_menus_command_translator_1, com_neatly_stack_windows_1;
    Object neatly_stack_windows_command_pursuer_1;
    Object neatly_stack_windows_command_translator_1;
    Object com_connect_to_foreign_image_1;
    Object connect_to_foreign_image_command_translator_1;
    Object com_disconnect_from_foreign_image_1;
    Object disconnect_from_foreign_image_command_translator_1;
    Object com_load_attribute_file_1, load_attribute_file_command_translator_1;
    Object com_write_g2_stats_1, write_g2_stats_command_translator_1;
    Object com_highlight_invoked_rules_1;
    Object highlight_invoked_rules_command_translator_1;
    Object com_do_not_highlight_invoked_rules_1;
    Object do_not_highlight_invoked_rules_command_translator_1;
    Object com_enable_all_items_1, enable_all_items_command_translator_1;
    Object com_remove_tracing_and_breakpoints_1;
    Object remove_tracing_and_breakpoints_command_translator_1;
    Object com_update_file_1, update_file_command_translator_1;
    Object com_edit_file_1, edit_file_command_translator_1, com_unedit_file_1;
    Object unedit_file_command_translator_1, com_commit_file_1;
    Object commit_file_command_translator_1, com_revert_file_1;
    Object revert_file_command_translator_1, com_create_new_module_1;
    Object create_new_module_command_pursuer_1;
    Object create_new_module_command_translator_1, com_delete_module_1;
    Object delete_module_command_pursuer_1, delete_module_command_translator_1;
    Object com_new_title_block_1, new_title_block_command_translator_1;
    Object com_shut_down_g2_1, shut_down_g2_command_translator_1;
    Object com_clear_kb_1, clear_kb_command_translator_1;
    Object com_turn_on_all_explanation_caching_1;
    Object turn_on_all_explanation_caching_command_translator_1;
    Object com_turn_off_all_explanation_caching_1;
    Object turn_off_all_explanation_caching_command_translator_1;
    Object com_network_info_1, network_info_command_translator_1;
    Object com_close_telewindows_connection_1;
    Object close_telewindows_connection_command_translator_1, com_log_out_1;
    Object log_out_command_translator_1, com_detect_deadlocks_for_ui_1;
    Object detect_deadlocks_for_ui_command_translator_1;
    Object com_detect_and_break_deadlocks_for_ui_1;
    Object detect_and_break_deadlocks_for_ui_command_translator_1;
    Object com_enter_package_preparation_mode_1;
    Object enter_package_preparation_mode_command_translator_1;
    Object com_leave_package_preparation_mode_1;
    Object leave_package_preparation_mode_command_translator_1;
    Object com_strip_texts_now_1, strip_texts_now_command_translator_1;
    Object com_make_workspaces_proprietary_now_1;
    Object make_workspaces_proprietary_now_command_translator_1;
    Object com_enter_simulate_proprietary_mode_1;
    Object enter_simulate_proprietary_mode_command_translator_1;
    Object com_leave_simulate_proprietary_mode_1;
    Object leave_simulate_proprietary_mode_command_translator_1, com_abort_1;
    Object abort_command_translator_1, com_refresh_1;
    Object refresh_command_pursuer_1, refresh_command_translator_1;
    Object com_toggle_visible_grid_1, toggle_visible_grid_command_pursuer_1;
    Object toggle_visible_grid_command_translator_1, com_help_1;
    Object help_command_pursuer_1, help_command_translator_1;
    Object com_launch_online_help_1, launch_online_help_command_pursuer_1;
    Object launch_online_help_command_translator_1, com_circulate_up_1;
    Object circulate_up_command_pursuer_1, circulate_up_command_translator_1;
    Object com_circulate_down_1, circulate_down_command_pursuer_1;
    Object circulate_down_command_translator_1, com_lift_to_top_1;
    Object lift_to_top_command_pursuer_1, lift_to_top_command_translator_1;
    Object com_drop_to_bottom_1, drop_to_bottom_command_pursuer_1;
    Object drop_to_bottom_command_translator_1, com_lift_item_to_top_1;
    Object lift_item_to_top_command_pursuer_1;
    Object lift_item_to_top_command_translator_1, com_drop_item_to_bottom_1;
    Object drop_item_to_bottom_command_pursuer_1;
    Object drop_item_to_bottom_command_translator_1, gensymed_symbol;
    Object system_defined_rpcs_new_value, com_do_scrolling_1;
    Object do_scrolling_command_pursuer_1, do_scrolling_command_translator_1;
    Object com_full_scale_1, full_scale_command_pursuer_1;
    Object full_scale_command_translator_1, com_normalized_full_scale_1;
    Object normalized_full_scale_command_pursuer_1;
    Object normalized_full_scale_command_translator_1, com_scale_to_fit_1;
    Object scale_to_fit_command_pursuer_1, scale_to_fit_command_translator_1;
    Object com_maximum_scale_to_fit_1, maximum_scale_to_fit_command_pursuer_1;
    Object maximum_scale_to_fit_command_translator_1;
    Object com_one_quarter_the_scale_1;
    Object one_quarter_the_scale_command_pursuer_1;
    Object one_quarter_the_scale_command_translator_1;
    Object com_four_times_the_scale_1, four_times_the_scale_command_pursuer_1;
    Object four_times_the_scale_command_translator_1;
    Object com_twenty_percent_smaller_1;
    Object twenty_percent_smaller_command_pursuer_1;
    Object twenty_percent_smaller_command_translator_1;
    Object com_twenty_percent_bigger_1;
    Object twenty_percent_bigger_command_pursuer_1;
    Object twenty_percent_bigger_command_translator_1;
    Object com_twenty_percent_narrower_1;
    Object twenty_percent_narrower_command_pursuer_1;
    Object twenty_percent_narrower_command_translator_1;
    Object com_twenty_percent_wider_1, twenty_percent_wider_command_pursuer_1;
    Object twenty_percent_wider_command_translator_1, com_center_origin_1;
    Object center_origin_command_pursuer_1, center_origin_command_translator_1;
    Object com_shift_left_ten_percent_1;
    Object shift_left_ten_percent_command_pursuer_1;
    Object shift_left_ten_percent_command_translator_1;
    Object com_shift_right_ten_percent_1;
    Object shift_right_ten_percent_command_pursuer_1;
    Object shift_right_ten_percent_command_translator_1;
    Object com_shift_left_one_percent_1;
    Object shift_left_one_percent_command_pursuer_1;
    Object shift_left_one_percent_command_translator_1;
    Object com_shift_right_one_percent_1;
    Object shift_right_one_percent_command_pursuer_1;
    Object shift_right_one_percent_command_translator_1;
    Object com_shift_up_ten_percent_1, shift_up_ten_percent_command_pursuer_1;
    Object shift_up_ten_percent_command_translator_1;
    Object com_shift_down_ten_percent_1;
    Object shift_down_ten_percent_command_pursuer_1;
    Object shift_down_ten_percent_command_translator_1;
    Object com_shift_up_one_percent_1, shift_up_one_percent_command_pursuer_1;
    Object shift_up_one_percent_command_translator_1;
    Object com_shift_down_one_percent_1;
    Object shift_down_one_percent_command_pursuer_1;
    Object shift_down_one_percent_command_translator_1;
    Object com_table_of_attributes_pane_1;
    Object table_of_attributes_pane_command_pursuer_1;
    Object table_of_attributes_pane_command_translator_1;
    Object com_table_of_hidden_attributes_pane_1;
    Object table_of_hidden_attributes_pane_command_pursuer_1;
    Object table_of_hidden_attributes_pane_command_translator_1;
    Object com_update_table_of_attributes_pane_1;
    Object update_table_of_attributes_pane_command_pursuer_1;
    Object update_table_of_attributes_pane_command_translator_1;
    Object com_update_table_of_hidden_attributes_pane_1;
    Object update_table_of_hidden_attributes_pane_command_pursuer_1;
    Object update_table_of_hidden_attributes_pane_command_translator_1;
    Object com_table_1, table_command_pursuer_1, table_command_translator_1;
    Object com_table_of_item_1, table_of_item_command_pursuer_1;
    Object table_of_item_command_translator_1, com_table_of_workspace_1;
    Object table_of_workspace_command_pursuer_1;
    Object table_of_workspace_command_translator_1;
    Object com_table_of_hidden_attributes_1;
    Object table_of_hidden_attributes_command_pursuer_1;
    Object table_of_hidden_attributes_command_translator_1;
    Object com_table_of_hidden_attributes_of_item_1;
    Object table_of_hidden_attributes_of_item_command_pursuer_1;
    Object table_of_hidden_attributes_of_item_command_translator_1;
    Object com_show_unsaved_attributes_1;
    Object show_unsaved_attributes_command_pursuer_1;
    Object show_unsaved_attributes_command_translator_1, com_shrink_wrap_1;
    Object shrink_wrap_command_pursuer_1, shrink_wrap_command_translator_1;
    Object com_name_1, name_command_pursuer_1, name_command_translator_1;
    Object com_name_item_1, name_item_command_pursuer_1;
    Object name_item_command_translator_1, com_mark_to_strip_text_1;
    Object mark_to_strip_text_command_pursuer_1;
    Object mark_to_strip_text_command_translator_1;
    Object com_mark_to_strip_text_star_1;
    Object mark_to_strip_text_star_command_pursuer_1;
    Object mark_to_strip_text_star_command_translator_1;
    Object com_remove_strip_text_mark_1;
    Object remove_strip_text_mark_command_pursuer_1;
    Object remove_strip_text_mark_command_translator_1;
    Object com_remove_strip_text_mark_star_1;
    Object remove_strip_text_mark_star_command_pursuer_1;
    Object remove_strip_text_mark_star_command_translator_1;
    Object com_mark_not_to_strip_text_star_1;
    Object mark_not_to_strip_text_star_command_pursuer_1;
    Object mark_not_to_strip_text_star_command_translator_1;
    Object com_mark_not_to_strip_text_1;
    Object mark_not_to_strip_text_command_pursuer_1;
    Object mark_not_to_strip_text_command_translator_1;
    Object com_remove_do_not_strip_text_mark_star_1;
    Object remove_do_not_strip_text_mark_star_command_pursuer_1;
    Object remove_do_not_strip_text_mark_star_command_translator_1;
    Object com_remove_do_not_strip_text_mark_1;
    Object remove_do_not_strip_text_mark_command_pursuer_1;
    Object remove_do_not_strip_text_mark_command_translator_1;
    Object com_edit_expression_of_readout_table_1;
    Object edit_expression_of_readout_table_command_pursuer_1;
    Object edit_expression_of_readout_table_command_translator_1;
    Object com_hide_name_1, hide_name_command_pursuer_1;
    Object hide_name_command_translator_1, com_main_menu_1;
    Object main_menu_command_translator_1, com_load_merge_save_1;
    Object load_merge_save_command_translator_1, com_run_options_1;
    Object run_options_command_translator_1, com_miscellany_1;
    Object miscellany_command_pursuer_1, miscellany_command_translator_1;
    Object com_other_edits_1, other_edits_command_pursuer_1;
    Object other_edits_command_translator_1, com_cut_selected_text_1;
    Object cut_selected_text_command_pursuer_1;
    Object cut_selected_text_command_translator_1, com_copy_selected_text_1;
    Object copy_selected_text_command_pursuer_1;
    Object copy_selected_text_command_translator_1;
    Object com_paste_over_selected_text_1;
    Object paste_over_selected_text_command_pursuer_1;
    Object paste_over_selected_text_command_translator_1;
    Object com_delete_selected_text_1, delete_selected_text_command_pursuer_1;
    Object delete_selected_text_command_translator_1;
    Object com_insert_selected_text_1, insert_selected_text_command_pursuer_1;
    Object insert_selected_text_command_translator_1;
    Object com_copy_and_insert_selected_text_1;
    Object copy_and_insert_selected_text_command_pursuer_1;
    Object copy_and_insert_selected_text_command_translator_1;
    Object com_move_selected_text_1, move_selected_text_command_pursuer_1;
    Object move_selected_text_command_translator_1;
    Object com_cut_and_insert_selected_text_1;
    Object cut_and_insert_selected_text_command_pursuer_1;
    Object cut_and_insert_selected_text_command_translator_1, com_paste_1;
    Object paste_command_pursuer_1, paste_command_translator_1;
    Object Qg2_unregister_callback_on_twng_exit;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_register_callback_on_twng_exit;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qdrag_selection_handle;
    Object Qnew_style_event_handler, Qupdate_mouse_cursor;
    Object Qhandle_login_dialog_message, Qpassword_change, Qchanging_mode;
    Object list_constant_16, list_constant_148, list_constant_147;
    Object array_constant_21, list_constant_125, Quser_mode_alias_creation;
    Object list_constant_146, list_constant_145, list_constant_144;
    Object list_constant_143, list_constant_142, list_constant_141;
    Object list_constant_140, Qbutton, list_constant_102, list_constant_139;
    Object list_constant_112, list_constant_138, list_constant_109;
    Object list_constant_135, list_constant_137, list_constant_99;
    Object Qexisting_user_mode_for_this_alias, list_constant_136;
    Object list_constant_105, list_constant_104, list_constant_134;
    Object list_constant_133, Quser_mode_alias, list_constant_132;
    Object list_constant_131, list_constant_130, list_constant_129;
    Object list_constant_128, Qg2_window_specific_language, Qlanguage;
    Object Qg2_window_name_or_class, Quser_mode, list_constant_127;
    Object list_constant_126, Qchange_user_settings, list_constant_124;
    Object list_constant_123, list_constant_122, list_constant_121;
    Object list_constant_120, list_constant_119, list_constant_118;
    Object list_constant_117, list_constant_116, list_constant_115;
    Object list_constant_114, list_constant_113, Qbs_defpushbutton;
    Object list_constant_110, list_constant_101, list_constant_111;
    Object Qws_vscroll, Qcbs_dropdown, list_constant_108, list_constant_107;
    Object Qes_password, list_constant_106, Qpassword, list_constant_103;
    Object Qws_ex_clientedge, Qes_autohscroll, Qws_tabstop, list_constant_100;
    Object Quser_name, string_constant_94, Qws_sysmenu, Qws_caption;
    Object Qws_clipchildren, Qds_modalframe, Qmb_iconasterisk;
    Object Qmb_iconexclamation, Qmb_iconquestion, Qmb_iconhand;
    Object list_constant_98, list_constant_97, list_constant_96;
    Object list_constant_95, list_constant_94, list_constant_93, Qds_sysmodal;
    Object Qds_setforeground, Qds_setfont, Qds_noidlemsg, Qds_nofailcreate;
    Object Qmenu_string, array_constant_20, string_constant_93, Qcommand_menu;
    Object Qeditor_text_marking_menu, array_constant_19, string_constant_92;
    Object list_constant_92, list_constant_90, array_constant_18;
    Object Qcut_and_insert, string_constant_91, list_constant_91, Qmove;
    Object string_constant_90, array_constant_17, Qcopy_and_insert;
    Object string_constant_89, Qinsert, string_constant_88, string_constant_87;
    Object string_constant_86, Qcopy, string_constant_85, Qcut;
    Object string_constant_84, list_constant_89, list_constant_88;
    Object Qempty_command_pursuer, list_constant_87, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_82, string_constant_83, list_constant_81;
    Object string_constant_82, list_constant_80, string_constant_81;
    Object list_constant_78, string_constant_80, list_constant_79;
    Object list_constant_21, string_constant_79, list_constant_76;
    Object list_constant_77, array_constant_16, string_constant_78;
    Object array_constant_15, string_constant_77, list_constant_27;
    Object list_constant_75, Qrefreshes_image_plane_p, list_constant_74;
    Object list_constant_73, list_constant_72, list_constant_71;
    Object list_constant_24, Qg2_launch_operate_on_area, Qclass_qualified_name;
    Object Qg2_command_is_enabled, list_constant_70, Qab_or, Quser_menu_choice;
    Object list_constant_69, Qenable, Qdynamic_rule_invocation_display;
    Object Qdynamic_generic_rule_display, Qdescribe_chaining;
    Object Qdynamic_backward_chaining, Qdescribe_configuration, Qab_describe;
    Object Qg2_ui_insert_text_into_current_editor;
    Object Qg2_ui_get_text_from_current_editor, Qsingle_line_comment, Qcomment;
    Object Qellipsis, Qquoted_character, Qg2_ui_finish_editing_session;
    Object Qg2_ui_launch_editor_returning_handle, Qmaximum_open_editors;
    Object Qg2_ui_launch_editor_extended, Qg2_ui_close_current_editor;
    Object list_constant_68, list_constant_67, list_constant_66;
    Object list_constant_65, list_constant_64, list_constant_63;
    Object list_constant_62, list_constant_61, list_constant_60;
    Object list_constant_59, list_constant_58, list_constant_47;
    Object list_constant_57, Qsymbolic_parameter, list_constant_42;
    Object list_constant_41, list_constant_56, list_constant_55;
    Object list_constant_54, list_constant_53, list_constant_52;
    Object list_constant_40, list_constant_51, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_46;
    Object list_constant_45, Qnative, Qclassic, list_constant_44;
    Object list_constant_43, Qg2_refresh_image_definition;
    Object Qg2_get_item_layer_position_system_rpc_internal;
    Object Qg2_get_item_layer_position, Qsystem_defined_rpc, list_constant_35;
    Object Qg2_drop_item_behind_system_rpc_internal, Qg2_drop_item_behind;
    Object list_constant_39, Qg2_drop_item_to_back;
    Object Qg2_lift_item_in_front_of_system_rpc_internal;
    Object Qg2_lift_item_in_front_of, list_constant_38, list_constant_37;
    Object list_constant_36, Qitem_2, Qitem_1, list_constant_33;
    Object Qg2_lift_item_to_front, Qg2_drop_item_to_bottom_system_rpc_internal;
    Object Qg2_drop_item_to_bottom, Qg2_lift_item_to_top_system_rpc_internal;
    Object Qg2_lift_item_to_top, list_constant_34, list_constant_32;
    Object list_constant_31, array_constant_14, array_constant_13;
    Object list_constant_30, array_constant_12, list_constant_29;
    Object list_constant_28, string_constant_76, list_constant_26;
    Object list_constant_25, list_constant_20, array_constant_11;
    Object array_constant_10, string_constant_75, array_constant_9;
    Object string_constant_74, list_constant_23, list_constant_22;
    Object array_constant_8, Qchoose_a_module_to_delete, string_constant_73;
    Object Qui_command_command_posts_dialog_p, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_64;
    Object string_constant_66, string_constant_65, array_constant_7;
    Object string_constant_63, Qsystem_tables, string_constant_62;
    Object list_constant_19, array_constant_6, array_constant_5;
    Object string_constant_61, array_constant_4, string_constant_60;
    Object list_constant_18, list_constant_17, array_constant_3;
    Object string_constant_59, array_constant_2, string_constant_58;
    Object string_constant_57, string_constant_56, list_constant_15;
    Object list_constant_14, string_constant_55, list_constant_13;
    Object list_constant_12, string_constant_52, string_constant_54;
    Object string_constant_53, string_constant_51, string_constant_50;

    x_note_fn_call(225,421);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qstart = STATIC_SYMBOL("START",AB_package);
    string_constant_50 = STATIC_STRING("Start running the knowledge base");
    make_ui_command(5,Qstart,Qnil,string_constant_50,Qstart,Qnil);
    com_start_1 = STATIC_FUNCTION(com_start,NIL,FALSE,0,0);
    set_ui_command_function(Qstart,com_start_1);
    Qempty_command_pursuer = STATIC_SYMBOL("EMPTY-COMMAND-PURSUER",AB_package);
    set_ui_command_pursuer(Qstart,Qempty_command_pursuer);
    start_command_translator_1 = STATIC_FUNCTION(start_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qstart,start_command_translator_1);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    string_constant_51 = 
	    STATIC_STRING("Stop running the knowledge base, while allowing it to be resumed later.");
    make_ui_command(5,Qpause,Qnil,string_constant_51,Qpause,Qnil);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    com_pause_1 = STATIC_FUNCTION(com_pause,NIL,FALSE,0,0);
    set_ui_command_function(Qpause,com_pause_1);
    set_ui_command_pursuer(Qpause,Qempty_command_pursuer);
    pause_command_translator_1 = STATIC_FUNCTION(pause_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qpause,pause_command_translator_1);
    Qresume = STATIC_SYMBOL("RESUME",AB_package);
    string_constant_52 = 
	    STATIC_STRING("Continue running the KB from where it was paused.");
    make_ui_command(5,Qresume,Qnil,string_constant_52,Qresume,Qnil);
    com_resume_1 = STATIC_FUNCTION(com_resume,NIL,FALSE,0,0);
    set_ui_command_function(Qresume,com_resume_1);
    set_ui_command_pursuer(Qresume,Qempty_command_pursuer);
    resume_command_translator_1 = 
	    STATIC_FUNCTION(resume_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qresume,resume_command_translator_1);
    Qcontinue_from_breakpoint = STATIC_SYMBOL("CONTINUE-FROM-BREAKPOINT",
	    AB_package);
    string_constant_53 = 
	    STATIC_STRING("Continue running the KB from the point of the breakpoint.");
    make_ui_command(5,Qcontinue_from_breakpoint,Qnil,string_constant_53,
	    Qcontinue_from_breakpoint,Qnil);
    string_constant = 
	    STATIC_STRING("Continue from the point of the breakpoint.");
    com_continue_from_breakpoint_1 = 
	    STATIC_FUNCTION(com_continue_from_breakpoint,NIL,FALSE,0,0);
    set_ui_command_function(Qcontinue_from_breakpoint,
	    com_continue_from_breakpoint_1);
    set_ui_command_pursuer(Qcontinue_from_breakpoint,Qempty_command_pursuer);
    continue_from_breakpoint_command_translator_1 = 
	    STATIC_FUNCTION(continue_from_breakpoint_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qcontinue_from_breakpoint,
	    continue_from_breakpoint_command_translator_1);
    string_constant_1 = 
	    STATIC_STRING("Cannot ~A because G2 is in a breakpoint.  ~\n                Exit the breakpoint first, with resume.");
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    string_constant_54 = 
	    STATIC_STRING("Stop running the knowledge base and reset all variables, parameters, etc.");
    make_ui_command(5,Qreset,Qnil,string_constant_54,Qreset,Qnil);
    com_reset_1 = STATIC_FUNCTION(com_reset,NIL,FALSE,0,0);
    set_ui_command_function(Qreset,com_reset_1);
    set_ui_command_pursuer(Qreset,Qempty_command_pursuer);
    reset_command_translator_1 = STATIC_FUNCTION(reset_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qreset,reset_command_translator_1);
    Qab_restart = STATIC_SYMBOL("RESTART",AB_package);
    make_ui_command(5,Qab_restart,Qnil,string_constant_52,Qab_restart,Qnil);
    com_restart_1 = STATIC_FUNCTION(com_restart,NIL,FALSE,0,0);
    set_ui_command_function(Qab_restart,com_restart_1);
    set_ui_command_pursuer(Qab_restart,Qempty_command_pursuer);
    restart_command_translator_1 = 
	    STATIC_FUNCTION(restart_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qab_restart,restart_command_translator_1);
    Qclear_kb = STATIC_SYMBOL("CLEAR-KB",AB_package);
    Qcurrent_workstation = STATIC_SYMBOL("CURRENT-WORKSTATION",AB_package);
    string_constant_2 = STATIC_STRING("Do you really want to ~(~A~) G2\?");
    Qsystem_state_change_from_scheduler_1 = 
	    STATIC_SYMBOL("SYSTEM-STATE-CHANGE-FROM-SCHEDULER-1",AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_3 = 
	    STATIC_STRING("Resetting KB to beginning. You may start when ready.");
    string_constant_4 = 
	    STATIC_STRING("Resetting KB to beginning and restarting it.");
    string_constant_5 = 
	    STATIC_STRING("Resuming running of KB from where it last paused.");
    string_constant_6 = 
	    STATIC_STRING("Pause while running KB. You may resume, reset, or restart.");
    string_constant_7 = 
	    STATIC_STRING("Starting to run KB. You may pause, reset, or restart at any time.");
    SET_SYMBOL_FUNCTION(Qsystem_state_change_from_scheduler_1,
	    STATIC_FUNCTION(system_state_change_from_scheduler_1,NIL,FALSE,
	    1,1));
    Qnew_workspace = STATIC_SYMBOL("NEW-WORKSPACE",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qclass_of_workspace = STATIC_SYMBOL("CLASS-OF-WORKSPACE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qab_class,Qclass_of_workspace);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,list_constant_12,Qg2_window);
    string_constant_55 = STATIC_STRING("Create a new, top-level KB workspace");
    make_ui_command(5,Qnew_workspace,list_constant_13,string_constant_55,
	    Qnew_workspace,Qnil);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qkb_workspace_initial_width = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-WIDTH",AB_package);
    Qkb_workspace_initial_height = 
	    STATIC_SYMBOL("KB-WORKSPACE-INITIAL-HEIGHT",AB_package);
    Qmodule_this_is_part_of_qm = STATIC_SYMBOL("MODULE-THIS-IS-PART-OF\?",
	    AB_package);
    com_new_workspace_1 = STATIC_FUNCTION(com_new_workspace,NIL,FALSE,2,2);
    set_ui_command_function(Qnew_workspace,com_new_workspace_1);
    new_workspace_command_pursuer_1 = 
	    STATIC_FUNCTION(new_workspace_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qnew_workspace,new_workspace_command_pursuer_1);
    new_workspace_command_translator_1 = 
	    STATIC_FUNCTION(new_workspace_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qnew_workspace,
	    new_workspace_command_translator_1);
    Qget_workspace = STATIC_SYMBOL("GET-WORKSPACE",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qnamed_kb_workspace = STATIC_SYMBOL("NAMED-KB-WORKSPACE",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qworkspace,Qnamed_kb_workspace);
    list_constant_15 = STATIC_CONS(list_constant_14,Qnil);
    string_constant_56 = 
	    STATIC_STRING("Choose an existing workspace and bring it to the top");
    make_ui_command(5,Qget_workspace,list_constant_15,string_constant_56,
	    Qget_workspace,Qnil);
    com_get_workspace_1 = STATIC_FUNCTION(com_get_workspace,NIL,FALSE,1,1);
    set_ui_command_function(Qget_workspace,com_get_workspace_1);
    get_workspace_command_pursuer_1 = 
	    STATIC_FUNCTION(get_workspace_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qget_workspace,get_workspace_command_pursuer_1);
    get_workspace_command_translator_1 = 
	    STATIC_FUNCTION(get_workspace_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qget_workspace,
	    get_workspace_command_translator_1);
    string_constant_57 = STATIC_STRING("Bring up the inspector window");
    make_ui_command(5,Qinspect,Qnil,string_constant_57,Qinspect,Qnil);
    Qui_command_command_posts_dialog_p = 
	    STATIC_SYMBOL("UI-COMMAND-COMMAND-POSTS-DIALOG-P",AB_package);
    mutate_global_property(Qinspect,Qt,Qui_command_command_posts_dialog_p);
    Qinspect_command = STATIC_SYMBOL("INSPECT-COMMAND",AB_package);
    com_inspect_1 = STATIC_FUNCTION(com_inspect,NIL,FALSE,0,0);
    set_ui_command_function(Qinspect,com_inspect_1);
    set_ui_command_pursuer(Qinspect,Qempty_command_pursuer);
    inspect_command_translator_1 = 
	    STATIC_FUNCTION(inspect_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qinspect,inspect_command_translator_1);
    Qload_kb = STATIC_SYMBOL("LOAD-KB",AB_package);
    string_constant_58 = STATIC_STRING("Load a KB");
    make_ui_command(5,Qload_kb,Qnil,string_constant_58,Qload_kb,Qnil);
    mutate_global_property(Qload_kb,Qt,Qui_command_command_posts_dialog_p);
    com_load_kb_1 = STATIC_FUNCTION(com_load_kb,NIL,FALSE,0,0);
    set_ui_command_function(Qload_kb,com_load_kb_1);
    set_ui_command_pursuer(Qload_kb,Qempty_command_pursuer);
    load_kb_command_translator_1 = 
	    STATIC_FUNCTION(load_kb_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qload_kb,load_kb_command_translator_1);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant_2 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    Qmenu_string = STATIC_SYMBOL("MENU-STRING",AB_package);
    mutate_global_property(Qload_kb,array_constant_2,Qmenu_string);
    Qmerge_kb = STATIC_SYMBOL("MERGE-KB",AB_package);
    string_constant_59 = STATIC_STRING("Merge a KB");
    make_ui_command(5,Qmerge_kb,Qnil,string_constant_59,Qmerge_kb,Qnil);
    mutate_global_property(Qmerge_kb,Qt,Qui_command_command_posts_dialog_p);
    com_merge_kb_1 = STATIC_FUNCTION(com_merge_kb,NIL,FALSE,0,0);
    set_ui_command_function(Qmerge_kb,com_merge_kb_1);
    set_ui_command_pursuer(Qmerge_kb,Qempty_command_pursuer);
    merge_kb_command_translator_1 = 
	    STATIC_FUNCTION(merge_kb_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qmerge_kb,merge_kb_command_translator_1);
    array_constant_3 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qmerge_kb,array_constant_3,Qmenu_string);
    Qload_recent_kb = STATIC_SYMBOL("LOAD-RECENT-KB",AB_package);
    Qab_pathname = STATIC_SYMBOL("PATHNAME",AB_package);
    Qrecent_loaded_kb = STATIC_SYMBOL("RECENT-LOADED-KB",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qab_pathname,Qrecent_loaded_kb);
    list_constant_18 = STATIC_CONS(list_constant_17,Qnil);
    string_constant_60 = STATIC_STRING("Load a recent KB");
    make_ui_command(5,Qload_recent_kb,list_constant_18,string_constant_60,
	    Qload_recent_kb,Qnil);
    mutate_global_property(Qload_recent_kb,Qt,
	    Qui_command_command_posts_dialog_p);
    com_load_recent_kb_1 = STATIC_FUNCTION(com_load_recent_kb,NIL,FALSE,1,1);
    set_ui_command_function(Qload_recent_kb,com_load_recent_kb_1);
    load_recent_kb_command_pursuer_1 = 
	    STATIC_FUNCTION(load_recent_kb_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qload_recent_kb,load_recent_kb_command_pursuer_1);
    load_recent_kb_command_translator_1 = 
	    STATIC_FUNCTION(load_recent_kb_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qload_recent_kb,
	    load_recent_kb_command_translator_1);
    array_constant_4 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)70L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qload_recent_kb,array_constant_4,Qmenu_string);
    Qsave_kb = STATIC_SYMBOL("SAVE-KB",AB_package);
    string_constant_61 = STATIC_STRING("Save the current KB");
    make_ui_command(5,Qsave_kb,Qnil,string_constant_61,Qsave_kb,Qnil);
    mutate_global_property(Qsave_kb,Qt,Qui_command_command_posts_dialog_p);
    com_save_kb_1 = STATIC_FUNCTION(com_save_kb,NIL,FALSE,0,0);
    set_ui_command_function(Qsave_kb,com_save_kb_1);
    set_ui_command_pursuer(Qsave_kb,Qempty_command_pursuer);
    save_kb_command_translator_1 = 
	    STATIC_FUNCTION(save_kb_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qsave_kb,save_kb_command_translator_1);
    array_constant_5 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qsave_kb,array_constant_5,Qmenu_string);
    Qsave_kb_without_asking = STATIC_SYMBOL("SAVE-KB-WITHOUT-ASKING",
	    AB_package);
    make_ui_command(5,Qsave_kb_without_asking,Qnil,Qnil,
	    Qsave_kb_without_asking,Qnil);
    Qkb_save = STATIC_SYMBOL("KB-SAVE",AB_package);
    com_save_kb_without_asking_1 = 
	    STATIC_FUNCTION(com_save_kb_without_asking,NIL,FALSE,0,0);
    set_ui_command_function(Qsave_kb_without_asking,
	    com_save_kb_without_asking_1);
    set_ui_command_pursuer(Qsave_kb_without_asking,Qempty_command_pursuer);
    save_kb_without_asking_command_translator_1 = 
	    STATIC_FUNCTION(save_kb_without_asking_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qsave_kb_without_asking,
	    save_kb_without_asking_command_translator_1);
    array_constant_6 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qsave_kb_without_asking,array_constant_6,
	    Qmenu_string);
    Qshow_system_table = STATIC_SYMBOL("SHOW-SYSTEM-TABLE",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    Qoriginal_x_in_window = STATIC_SYMBOL("ORIGINAL-X-IN-WINDOW",AB_package);
    Qoriginal_y_in_window = STATIC_SYMBOL("ORIGINAL-Y-IN-WINDOW",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qsystem_table,
	    Qoriginal_x_in_window,Qoriginal_y_in_window);
    string_constant_62 = STATIC_STRING("Put up a chosen system table");
    Qsystem_tables = STATIC_SYMBOL("SYSTEM-TABLES",AB_package);
    make_ui_command(5,Qshow_system_table,list_constant_19,
	    string_constant_62,Qsystem_tables,Qnil);
    com_show_system_table_1 = STATIC_FUNCTION(com_show_system_table,NIL,
	    FALSE,3,3);
    set_ui_command_function(Qshow_system_table,com_show_system_table_1);
    show_system_table_command_pursuer_1 = 
	    STATIC_FUNCTION(show_system_table_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qshow_system_table,
	    show_system_table_command_pursuer_1);
    show_system_table_command_translator_1 = 
	    STATIC_FUNCTION(show_system_table_command_translator,NIL,FALSE,
	    1,1);
    set_ui_command_translator(Qshow_system_table,
	    show_system_table_command_translator_1);
    Qprinter_setup = STATIC_SYMBOL("PRINTER-SETUP",AB_package);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    list_constant_20 = STATIC_CONS(Qwindow,Qnil);
    string_constant_63 = STATIC_STRING("Put up the printer-setup table");
    make_ui_command(5,Qprinter_setup,list_constant_20,string_constant_63,
	    Qprinter_setup,Qnil);
    Qg2_defstruct_structure_name_gensym_window_g2_struct = 
	    STATIC_SYMBOL("GENSYM-WINDOW-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    com_printer_setup_1 = STATIC_FUNCTION(com_printer_setup,NIL,FALSE,1,1);
    set_ui_command_function(Qprinter_setup,com_printer_setup_1);
    printer_setup_command_pursuer_1 = 
	    STATIC_FUNCTION(printer_setup_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qprinter_setup,printer_setup_command_pursuer_1);
    printer_setup_command_translator_1 = 
	    STATIC_FUNCTION(printer_setup_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qprinter_setup,
	    printer_setup_command_translator_1);
    array_constant_7 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)38L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qprinter_setup,array_constant_7,Qmenu_string);
    Qchange_mode = STATIC_SYMBOL("CHANGE-MODE",AB_package);
    string_constant_64 = STATIC_STRING("Change the user mode of this window");
    make_ui_command(5,Qchange_mode,Qnil,string_constant_64,Qchange_mode,Qnil);
    mutate_global_property(Qchange_mode,Qt,Qui_command_command_posts_dialog_p);
    com_change_mode_1 = STATIC_FUNCTION(com_change_mode,NIL,FALSE,0,0);
    set_ui_command_function(Qchange_mode,com_change_mode_1);
    set_ui_command_pursuer(Qchange_mode,Qempty_command_pursuer);
    change_mode_command_translator_1 = 
	    STATIC_FUNCTION(change_mode_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qchange_mode,change_mode_command_translator_1);
    Qcreate_new_user_mode_alias = 
	    STATIC_SYMBOL("CREATE-NEW-USER-MODE-ALIAS",AB_package);
    string_constant_65 = 
	    STATIC_STRING("Create the new alias for the user mode");
    make_ui_command(5,Qcreate_new_user_mode_alias,Qnil,string_constant_65,
	    Qcreate_new_user_mode_alias,Qnil);
    mutate_global_property(Qcreate_new_user_mode_alias,Qt,
	    Qui_command_command_posts_dialog_p);
    Qalias_creation = STATIC_SYMBOL("ALIAS-CREATION",AB_package);
    com_create_new_user_mode_alias_1 = 
	    STATIC_FUNCTION(com_create_new_user_mode_alias,NIL,FALSE,0,0);
    set_ui_command_function(Qcreate_new_user_mode_alias,
	    com_create_new_user_mode_alias_1);
    set_ui_command_pursuer(Qcreate_new_user_mode_alias,Qempty_command_pursuer);
    create_new_user_mode_alias_command_translator_1 = 
	    STATIC_FUNCTION(create_new_user_mode_alias_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qcreate_new_user_mode_alias,
	    create_new_user_mode_alias_command_translator_1);
    Quser_mode_aliases = STATIC_SYMBOL("USER-MODE-ALIASES",AB_package);
    string_constant_66 = STATIC_STRING("Show dialog with aliases table.");
    make_ui_command(5,Quser_mode_aliases,Qnil,string_constant_66,
	    Quser_mode_aliases,Qnil);
    com_user_mode_aliases_1 = STATIC_FUNCTION(com_user_mode_aliases,NIL,
	    FALSE,0,0);
    set_ui_command_function(Quser_mode_aliases,com_user_mode_aliases_1);
    set_ui_command_pursuer(Quser_mode_aliases,Qempty_command_pursuer);
    user_mode_aliases_command_translator_1 = 
	    STATIC_FUNCTION(user_mode_aliases_command_translator,NIL,FALSE,
	    1,1);
    set_ui_command_translator(Quser_mode_aliases,
	    user_mode_aliases_command_translator_1);
    Qchange_g2_user_mode = STATIC_SYMBOL("CHANGE-G2-USER-MODE",AB_package);
    make_ui_command(5,Qchange_g2_user_mode,Qnil,string_constant_64,
	    Qchange_g2_user_mode,Qnil);
    Qcontrol_e = STATIC_SYMBOL("CONTROL-E",AB_package);
    com_change_g2_user_mode_1 = STATIC_FUNCTION(com_change_g2_user_mode,
	    NIL,FALSE,0,0);
    set_ui_command_function(Qchange_g2_user_mode,com_change_g2_user_mode_1);
    set_ui_command_pursuer(Qchange_g2_user_mode,Qempty_command_pursuer);
    change_g2_user_mode_command_translator_1 = 
	    STATIC_FUNCTION(change_g2_user_mode_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qchange_g2_user_mode,
	    change_g2_user_mode_command_translator_1);
    Qchange_g2_user_mode_e = STATIC_SYMBOL("CHANGE-G2-USER-MODE-E",AB_package);
    make_ui_command(5,Qchange_g2_user_mode_e,Qnil,string_constant_64,
	    Qchange_g2_user_mode_e,Qnil);
    com_change_g2_user_mode_e_1 = 
	    STATIC_FUNCTION(com_change_g2_user_mode_e,NIL,FALSE,0,0);
    set_ui_command_function(Qchange_g2_user_mode_e,
	    com_change_g2_user_mode_e_1);
    set_ui_command_pursuer(Qchange_g2_user_mode_e,Qempty_command_pursuer);
    change_g2_user_mode_e_command_translator_1 = 
	    STATIC_FUNCTION(change_g2_user_mode_e_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qchange_g2_user_mode_e,
	    change_g2_user_mode_e_command_translator_1);
    Qchange_password = STATIC_SYMBOL("CHANGE-PASSWORD",AB_package);
    string_constant_67 = 
	    STATIC_STRING("Change the password for the current user in a secure G2 site.");
    make_ui_command(5,Qchange_password,Qnil,string_constant_67,
	    Qchange_password,Qnil);
    com_change_password_1 = STATIC_FUNCTION(com_change_password,NIL,FALSE,0,0);
    set_ui_command_function(Qchange_password,com_change_password_1);
    set_ui_command_pursuer(Qchange_password,Qempty_command_pursuer);
    change_password_command_translator_1 = 
	    STATIC_FUNCTION(change_password_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qchange_password,
	    change_password_command_translator_1);
    Qreinstall_authorized_users = 
	    STATIC_SYMBOL("REINSTALL-AUTHORIZED-USERS",AB_package);
    string_constant_68 = 
	    STATIC_STRING("Read in fresh copy of the G2 ok file, using it to define the current set of users and their passwords.");
    make_ui_command(5,Qreinstall_authorized_users,Qnil,string_constant_68,
	    Qreinstall_authorized_users,Qnil);
    com_reinstall_authorized_users_1 = 
	    STATIC_FUNCTION(com_reinstall_authorized_users,NIL,FALSE,0,0);
    set_ui_command_function(Qreinstall_authorized_users,
	    com_reinstall_authorized_users_1);
    set_ui_command_pursuer(Qreinstall_authorized_users,Qempty_command_pursuer);
    reinstall_authorized_users_command_translator_1 = 
	    STATIC_FUNCTION(reinstall_authorized_users_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qreinstall_authorized_users,
	    reinstall_authorized_users_command_translator_1);
    Qshort_menus = STATIC_SYMBOL("SHORT-MENUS",AB_package);
    make_ui_command(5,Qshort_menus,Qnil,Qnil,Qshort_menus,Qnil);
    com_short_menus_1 = STATIC_FUNCTION(com_short_menus,NIL,FALSE,0,0);
    set_ui_command_function(Qshort_menus,com_short_menus_1);
    set_ui_command_pursuer(Qshort_menus,Qempty_command_pursuer);
    short_menus_command_translator_1 = 
	    STATIC_FUNCTION(short_menus_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qshort_menus,short_menus_command_translator_1);
    Qlong_menus = STATIC_SYMBOL("LONG-MENUS",AB_package);
    make_ui_command(5,Qlong_menus,Qnil,Qnil,Qlong_menus,Qnil);
    com_long_menus_1 = STATIC_FUNCTION(com_long_menus,NIL,FALSE,0,0);
    set_ui_command_function(Qlong_menus,com_long_menus_1);
    set_ui_command_pursuer(Qlong_menus,Qempty_command_pursuer);
    long_menus_command_translator_1 = 
	    STATIC_FUNCTION(long_menus_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qlong_menus,long_menus_command_translator_1);
    Qneatly_stack_windows = STATIC_SYMBOL("NEATLY-STACK-WINDOWS",AB_package);
    make_ui_command(5,Qneatly_stack_windows,list_constant_20,Qnil,
	    Qneatly_stack_windows,Qnil);
    com_neatly_stack_windows_1 = STATIC_FUNCTION(com_neatly_stack_windows,
	    NIL,FALSE,1,1);
    set_ui_command_function(Qneatly_stack_windows,com_neatly_stack_windows_1);
    neatly_stack_windows_command_pursuer_1 = 
	    STATIC_FUNCTION(neatly_stack_windows_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qneatly_stack_windows,
	    neatly_stack_windows_command_pursuer_1);
    neatly_stack_windows_command_translator_1 = 
	    STATIC_FUNCTION(neatly_stack_windows_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qneatly_stack_windows,
	    neatly_stack_windows_command_translator_1);
    Qconnect_to_foreign_image = STATIC_SYMBOL("CONNECT-TO-FOREIGN-IMAGE",
	    AB_package);
    string_constant_69 = 
	    STATIC_STRING("Connect G2 an external C or C++ program.");
    make_ui_command(5,Qconnect_to_foreign_image,Qnil,string_constant_69,
	    Qconnect_to_foreign_image,Qnil);
    mutate_global_property(Qconnect_to_foreign_image,Qt,
	    Qui_command_command_posts_dialog_p);
    com_connect_to_foreign_image_1 = 
	    STATIC_FUNCTION(com_connect_to_foreign_image,NIL,FALSE,0,0);
    set_ui_command_function(Qconnect_to_foreign_image,
	    com_connect_to_foreign_image_1);
    set_ui_command_pursuer(Qconnect_to_foreign_image,Qempty_command_pursuer);
    connect_to_foreign_image_command_translator_1 = 
	    STATIC_FUNCTION(connect_to_foreign_image_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qconnect_to_foreign_image,
	    connect_to_foreign_image_command_translator_1);
    Qdisconnect_from_foreign_image = 
	    STATIC_SYMBOL("DISCONNECT-FROM-FOREIGN-IMAGE",AB_package);
    string_constant_70 = 
	    STATIC_STRING("Disconnect G2 from an external C or C++ program.");
    make_ui_command(5,Qdisconnect_from_foreign_image,Qnil,
	    string_constant_70,Qdisconnect_from_foreign_image,Qnil);
    mutate_global_property(Qdisconnect_from_foreign_image,Qt,
	    Qui_command_command_posts_dialog_p);
    com_disconnect_from_foreign_image_1 = 
	    STATIC_FUNCTION(com_disconnect_from_foreign_image,NIL,FALSE,0,0);
    set_ui_command_function(Qdisconnect_from_foreign_image,
	    com_disconnect_from_foreign_image_1);
    set_ui_command_pursuer(Qdisconnect_from_foreign_image,
	    Qempty_command_pursuer);
    disconnect_from_foreign_image_command_translator_1 = 
	    STATIC_FUNCTION(disconnect_from_foreign_image_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qdisconnect_from_foreign_image,
	    disconnect_from_foreign_image_command_translator_1);
    Qload_attribute_file = STATIC_SYMBOL("LOAD-ATTRIBUTE-FILE",AB_package);
    string_constant_71 = 
	    STATIC_STRING("Loads a file that populates the attributes of existing items in the current KB, a superseded practice.");
    make_ui_command(5,Qload_attribute_file,Qnil,string_constant_71,
	    Qload_attribute_file,Qnil);
    mutate_global_property(Qload_attribute_file,Qt,
	    Qui_command_command_posts_dialog_p);
    com_load_attribute_file_1 = STATIC_FUNCTION(com_load_attribute_file,
	    NIL,FALSE,0,0);
    set_ui_command_function(Qload_attribute_file,com_load_attribute_file_1);
    set_ui_command_pursuer(Qload_attribute_file,Qempty_command_pursuer);
    load_attribute_file_command_translator_1 = 
	    STATIC_FUNCTION(load_attribute_file_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qload_attribute_file,
	    load_attribute_file_command_translator_1);
    Qwrite_g2_stats = STATIC_SYMBOL("WRITE-G2-STATS",AB_package);
    string_constant_72 = STATIC_STRING("Write G2 memory usage statistics");
    make_ui_command(5,Qwrite_g2_stats,Qnil,string_constant_72,
	    Qwrite_g2_stats,Qnil);
    mutate_global_property(Qwrite_g2_stats,Qt,
	    Qui_command_command_posts_dialog_p);
    com_write_g2_stats_1 = STATIC_FUNCTION(com_write_g2_stats,NIL,FALSE,0,0);
    set_ui_command_function(Qwrite_g2_stats,com_write_g2_stats_1);
    set_ui_command_pursuer(Qwrite_g2_stats,Qempty_command_pursuer);
    write_g2_stats_command_translator_1 = 
	    STATIC_FUNCTION(write_g2_stats_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qwrite_g2_stats,
	    write_g2_stats_command_translator_1);
    Qhighlight_invoked_rules = STATIC_SYMBOL("HIGHLIGHT-INVOKED-RULES",
	    AB_package);
    string_constant_73 = 
	    STATIC_STRING("Highlight rules when they are invoked");
    make_ui_command(5,Qhighlight_invoked_rules,Qnil,string_constant_73,
	    Qhighlight_invoked_rules,Qnil);
    Qhighlight_invoked_rules_mode = 
	    STATIC_SYMBOL("HIGHLIGHT-INVOKED-RULES-MODE",AB_package);
    com_highlight_invoked_rules_1 = 
	    STATIC_FUNCTION(com_highlight_invoked_rules,NIL,FALSE,0,0);
    set_ui_command_function(Qhighlight_invoked_rules,
	    com_highlight_invoked_rules_1);
    set_ui_command_pursuer(Qhighlight_invoked_rules,Qempty_command_pursuer);
    highlight_invoked_rules_command_translator_1 = 
	    STATIC_FUNCTION(highlight_invoked_rules_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qhighlight_invoked_rules,
	    highlight_invoked_rules_command_translator_1);
    Qdo_not_highlight_invoked_rules = 
	    STATIC_SYMBOL("DO-NOT-HIGHLIGHT-INVOKED-RULES",AB_package);
    make_ui_command(5,Qdo_not_highlight_invoked_rules,Qnil,Qnil,
	    Qdo_not_highlight_invoked_rules,Qnil);
    com_do_not_highlight_invoked_rules_1 = 
	    STATIC_FUNCTION(com_do_not_highlight_invoked_rules,NIL,FALSE,0,0);
    set_ui_command_function(Qdo_not_highlight_invoked_rules,
	    com_do_not_highlight_invoked_rules_1);
    set_ui_command_pursuer(Qdo_not_highlight_invoked_rules,
	    Qempty_command_pursuer);
    do_not_highlight_invoked_rules_command_translator_1 = 
	    STATIC_FUNCTION(do_not_highlight_invoked_rules_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qdo_not_highlight_invoked_rules,
	    do_not_highlight_invoked_rules_command_translator_1);
    Qenable_all_items = STATIC_SYMBOL("ENABLE-ALL-ITEMS",AB_package);
    make_ui_command(5,Qenable_all_items,Qnil,Qnil,Qenable_all_items,Qnil);
    com_enable_all_items_1 = STATIC_FUNCTION(com_enable_all_items,NIL,
	    FALSE,0,0);
    set_ui_command_function(Qenable_all_items,com_enable_all_items_1);
    set_ui_command_pursuer(Qenable_all_items,Qempty_command_pursuer);
    enable_all_items_command_translator_1 = 
	    STATIC_FUNCTION(enable_all_items_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qenable_all_items,
	    enable_all_items_command_translator_1);
    Qremove_tracing_and_breakpoints = 
	    STATIC_SYMBOL("REMOVE-TRACING-AND-BREAKPOINTS",AB_package);
    make_ui_command(5,Qremove_tracing_and_breakpoints,Qnil,Qnil,
	    Qremove_tracing_and_breakpoints,Qnil);
    com_remove_tracing_and_breakpoints_1 = 
	    STATIC_FUNCTION(com_remove_tracing_and_breakpoints,NIL,FALSE,0,0);
    set_ui_command_function(Qremove_tracing_and_breakpoints,
	    com_remove_tracing_and_breakpoints_1);
    set_ui_command_pursuer(Qremove_tracing_and_breakpoints,
	    Qempty_command_pursuer);
    remove_tracing_and_breakpoints_command_translator_1 = 
	    STATIC_FUNCTION(remove_tracing_and_breakpoints_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qremove_tracing_and_breakpoints,
	    remove_tracing_and_breakpoints_command_translator_1);
    Qupdate_file = STATIC_SYMBOL("UPDATE-FILE",AB_package);
    make_ui_command(5,Qupdate_file,Qnil,Qnil,Qupdate_file,Qnil);
    Qsource_code_control_update_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-UPDATE-FILE",AB_package);
    com_update_file_1 = STATIC_FUNCTION(com_update_file,NIL,FALSE,0,0);
    set_ui_command_function(Qupdate_file,com_update_file_1);
    set_ui_command_pursuer(Qupdate_file,Qempty_command_pursuer);
    update_file_command_translator_1 = 
	    STATIC_FUNCTION(update_file_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qupdate_file,update_file_command_translator_1);
    Qedit_file = STATIC_SYMBOL("EDIT-FILE",AB_package);
    make_ui_command(5,Qedit_file,Qnil,Qnil,Qedit_file,Qnil);
    Qsource_code_control_edit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-EDIT-FILE",AB_package);
    com_edit_file_1 = STATIC_FUNCTION(com_edit_file,NIL,FALSE,0,0);
    set_ui_command_function(Qedit_file,com_edit_file_1);
    set_ui_command_pursuer(Qedit_file,Qempty_command_pursuer);
    edit_file_command_translator_1 = 
	    STATIC_FUNCTION(edit_file_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qedit_file,edit_file_command_translator_1);
    Qunedit_file = STATIC_SYMBOL("UNEDIT-FILE",AB_package);
    make_ui_command(5,Qunedit_file,Qnil,Qnil,Qunedit_file,Qnil);
    Qsource_code_control_unedit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-UNEDIT-FILE",AB_package);
    com_unedit_file_1 = STATIC_FUNCTION(com_unedit_file,NIL,FALSE,0,0);
    set_ui_command_function(Qunedit_file,com_unedit_file_1);
    set_ui_command_pursuer(Qunedit_file,Qempty_command_pursuer);
    unedit_file_command_translator_1 = 
	    STATIC_FUNCTION(unedit_file_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qunedit_file,unedit_file_command_translator_1);
    Qcommit_file = STATIC_SYMBOL("COMMIT-FILE",AB_package);
    make_ui_command(5,Qcommit_file,Qnil,Qnil,Qcommit_file,Qnil);
    Qsource_code_control_commit_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-COMMIT-FILE",AB_package);
    com_commit_file_1 = STATIC_FUNCTION(com_commit_file,NIL,FALSE,0,0);
    set_ui_command_function(Qcommit_file,com_commit_file_1);
    set_ui_command_pursuer(Qcommit_file,Qempty_command_pursuer);
    commit_file_command_translator_1 = 
	    STATIC_FUNCTION(commit_file_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qcommit_file,commit_file_command_translator_1);
    Qrevert_file = STATIC_SYMBOL("REVERT-FILE",AB_package);
    make_ui_command(5,Qrevert_file,Qnil,Qnil,Qrevert_file,Qnil);
    Qsource_code_control_revert_file = 
	    STATIC_SYMBOL("SOURCE-CODE-CONTROL-REVERT-FILE",AB_package);
    com_revert_file_1 = STATIC_FUNCTION(com_revert_file,NIL,FALSE,0,0);
    set_ui_command_function(Qrevert_file,com_revert_file_1);
    set_ui_command_pursuer(Qrevert_file,Qempty_command_pursuer);
    revert_file_command_translator_1 = 
	    STATIC_FUNCTION(revert_file_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qrevert_file,revert_file_command_translator_1);
    Qcreate_new_module = STATIC_SYMBOL("CREATE-NEW-MODULE",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qoriginal_x_in_window,
	    Qoriginal_y_in_window);
    make_ui_command(5,Qcreate_new_module,list_constant_21,Qnil,
	    Qcreate_new_module,Qnil);
    com_create_new_module_1 = STATIC_FUNCTION(com_create_new_module,NIL,
	    FALSE,2,2);
    set_ui_command_function(Qcreate_new_module,com_create_new_module_1);
    create_new_module_command_pursuer_1 = 
	    STATIC_FUNCTION(create_new_module_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcreate_new_module,
	    create_new_module_command_pursuer_1);
    create_new_module_command_translator_1 = 
	    STATIC_FUNCTION(create_new_module_command_translator,NIL,FALSE,
	    1,1);
    set_ui_command_translator(Qcreate_new_module,
	    create_new_module_command_translator_1);
    Qchoose_a_module_to_delete = STATIC_SYMBOL("CHOOSE-A-MODULE-TO-DELETE",
	    AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)9L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)12L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)16L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)19L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)31L,(SI_Long)57344L);
    mutate_global_property(Qchoose_a_module_to_delete,array_constant_8,
	    Qmenu_string);
    Qdelete_module = STATIC_SYMBOL("DELETE-MODULE",AB_package);
    Qmodule = STATIC_SYMBOL("MODULE",AB_package);
    Qdeletable_module = STATIC_SYMBOL("DELETABLE-MODULE",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qmodule,Qdeletable_module);
    list_constant_23 = STATIC_CONS(list_constant_22,Qnil);
    make_ui_command(5,Qdelete_module,list_constant_23,Qnil,Qdelete_module,
	    Qnil);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_8 = 
	    STATIC_STRING("Delete ~amodule ~a\? (Choose `All\' to delete all associated workspaces as well.)");
    string_constant_9 = STATIC_STRING("the TOP-LEVEL ");
    string_constant_10 = STATIC_STRING("");
    string_constant_11 = STATIC_STRING("All");
    Qdo_deletion_of_module_after_confirmation = 
	    STATIC_SYMBOL("DO-DELETION-OF-MODULE-AFTER-CONFIRMATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdo_deletion_of_module_after_confirmation,
	    STATIC_FUNCTION(do_deletion_of_module_after_confirmation,NIL,
	    FALSE,2,2));
    com_delete_module_1 = STATIC_FUNCTION(com_delete_module,NIL,FALSE,1,1);
    set_ui_command_function(Qdelete_module,com_delete_module_1);
    delete_module_command_pursuer_1 = 
	    STATIC_FUNCTION(delete_module_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qdelete_module,delete_module_command_pursuer_1);
    delete_module_command_translator_1 = 
	    STATIC_FUNCTION(delete_module_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qdelete_module,
	    delete_module_command_translator_1);
    Qnew_title_block = STATIC_SYMBOL("NEW-TITLE-BLOCK",AB_package);
    make_ui_command(5,Qnew_title_block,Qnil,Qnil,Qnew_title_block,Qnil);
    com_new_title_block_1 = STATIC_FUNCTION(com_new_title_block,NIL,FALSE,0,0);
    set_ui_command_function(Qnew_title_block,com_new_title_block_1);
    set_ui_command_pursuer(Qnew_title_block,Qempty_command_pursuer);
    new_title_block_command_translator_1 = 
	    STATIC_FUNCTION(new_title_block_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qnew_title_block,
	    new_title_block_command_translator_1);
    Qshut_down_g2 = STATIC_SYMBOL("SHUT-DOWN-G2",AB_package);
    make_ui_command(5,Qshut_down_g2,Qnil,Qnil,Qshut_down_g2,Qnil);
    string_constant_12 = STATIC_STRING("Completely shut down G2\?");
    Qcompletely_shut_down_g2 = STATIC_SYMBOL("COMPLETELY-SHUT-DOWN-G2",
	    AB_package);
    Qrequested = STATIC_SYMBOL("REQUESTED",AB_package);
    com_shut_down_g2_1 = STATIC_FUNCTION(com_shut_down_g2,NIL,FALSE,0,0);
    set_ui_command_function(Qshut_down_g2,com_shut_down_g2_1);
    set_ui_command_pursuer(Qshut_down_g2,Qempty_command_pursuer);
    shut_down_g2_command_translator_1 = 
	    STATIC_FUNCTION(shut_down_g2_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qshut_down_g2,shut_down_g2_command_translator_1);
    string_constant_13 = STATIC_STRING("Shutdown!");
    SET_SYMBOL_FUNCTION(Qcompletely_shut_down_g2,
	    STATIC_FUNCTION(completely_shut_down_g2,NIL,TRUE,0,1));
    string_constant_74 = STATIC_STRING("Clear the current knowledge base");
    make_ui_command(5,Qclear_kb,Qnil,string_constant_74,Qclear_kb,Qnil);
    string_constant_14 = 
	    STATIC_STRING("Clear KB\? (Are you sure you want to delete every item in ~\n           the current KB and reinitialize system tables\?)");
    Qsystem_state_change_from_scheduler = 
	    STATIC_SYMBOL("SYSTEM-STATE-CHANGE-FROM-SCHEDULER",AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_state_change_from_scheduler,
	    STATIC_FUNCTION(system_state_change_from_scheduler,NIL,FALSE,1,1));
    com_clear_kb_1 = STATIC_FUNCTION(com_clear_kb,NIL,FALSE,0,0);
    set_ui_command_function(Qclear_kb,com_clear_kb_1);
    set_ui_command_pursuer(Qclear_kb,Qempty_command_pursuer);
    clear_kb_command_translator_1 = 
	    STATIC_FUNCTION(clear_kb_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qclear_kb,clear_kb_command_translator_1);
    array_constant_9 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qclear_kb,array_constant_9,Qmenu_string);
    Qturn_on_all_explanation_caching = 
	    STATIC_SYMBOL("TURN-ON-ALL-EXPLANATION-CACHING",AB_package);
    make_ui_command(5,Qturn_on_all_explanation_caching,Qnil,Qnil,
	    Qturn_on_all_explanation_caching,Qnil);
    Qexplanation_related_features_enabled_qm = 
	    STATIC_SYMBOL("EXPLANATION-RELATED-FEATURES-ENABLED\?",AB_package);
    com_turn_on_all_explanation_caching_1 = 
	    STATIC_FUNCTION(com_turn_on_all_explanation_caching,NIL,FALSE,0,0);
    set_ui_command_function(Qturn_on_all_explanation_caching,
	    com_turn_on_all_explanation_caching_1);
    set_ui_command_pursuer(Qturn_on_all_explanation_caching,
	    Qempty_command_pursuer);
    turn_on_all_explanation_caching_command_translator_1 = 
	    STATIC_FUNCTION(turn_on_all_explanation_caching_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qturn_on_all_explanation_caching,
	    turn_on_all_explanation_caching_command_translator_1);
    Qturn_off_all_explanation_caching = 
	    STATIC_SYMBOL("TURN-OFF-ALL-EXPLANATION-CACHING",AB_package);
    make_ui_command(5,Qturn_off_all_explanation_caching,Qnil,Qnil,
	    Qturn_off_all_explanation_caching,Qnil);
    com_turn_off_all_explanation_caching_1 = 
	    STATIC_FUNCTION(com_turn_off_all_explanation_caching,NIL,FALSE,
	    0,0);
    set_ui_command_function(Qturn_off_all_explanation_caching,
	    com_turn_off_all_explanation_caching_1);
    set_ui_command_pursuer(Qturn_off_all_explanation_caching,
	    Qempty_command_pursuer);
    turn_off_all_explanation_caching_command_translator_1 = 
	    STATIC_FUNCTION(turn_off_all_explanation_caching_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qturn_off_all_explanation_caching,
	    turn_off_all_explanation_caching_command_translator_1);
    Qnetwork_info = STATIC_SYMBOL("NETWORK-INFO",AB_package);
    make_ui_command(5,Qnetwork_info,Qnil,Qnil,Qnetwork_info,Qnil);
    com_network_info_1 = STATIC_FUNCTION(com_network_info,NIL,FALSE,0,0);
    set_ui_command_function(Qnetwork_info,com_network_info_1);
    set_ui_command_pursuer(Qnetwork_info,Qempty_command_pursuer);
    network_info_command_translator_1 = 
	    STATIC_FUNCTION(network_info_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qnetwork_info,network_info_command_translator_1);
    Qclose_telewindows_connection = 
	    STATIC_SYMBOL("CLOSE-TELEWINDOWS-CONNECTION",AB_package);
    make_ui_command(5,Qclose_telewindows_connection,Qnil,Qnil,
	    Qclose_telewindows_connection,Qnil);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    string_constant_15 = 
	    STATIC_STRING("Close this Telewindows connection to G2\?");
    Qclose_telewindows_connection_1 = 
	    STATIC_SYMBOL("CLOSE-TELEWINDOWS-CONNECTION-1",AB_package);
    com_close_telewindows_connection_1 = 
	    STATIC_FUNCTION(com_close_telewindows_connection,NIL,FALSE,0,0);
    set_ui_command_function(Qclose_telewindows_connection,
	    com_close_telewindows_connection_1);
    set_ui_command_pursuer(Qclose_telewindows_connection,
	    Qempty_command_pursuer);
    close_telewindows_connection_command_translator_1 = 
	    STATIC_FUNCTION(close_telewindows_connection_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qclose_telewindows_connection,
	    close_telewindows_connection_command_translator_1);
    string_constant_16 = STATIC_STRING("Closing Telewindows connection!");
    SET_SYMBOL_FUNCTION(Qclose_telewindows_connection_1,
	    STATIC_FUNCTION(close_telewindows_connection_1,NIL,FALSE,1,1));
    Qlog_out = STATIC_SYMBOL("LOG-OUT",AB_package);
    string_constant_75 = STATIC_STRING("Log-out of G2.");
    make_ui_command(5,Qlog_out,Qnil,string_constant_75,Qlog_out,Qnil);
    string_constant_17 = STATIC_STRING("Log out\? (Are you sure\?)");
    Qlog_out_workstation = STATIC_SYMBOL("LOG-OUT-WORKSTATION",AB_package);
    com_log_out_1 = STATIC_FUNCTION(com_log_out,NIL,FALSE,0,0);
    set_ui_command_function(Qlog_out,com_log_out_1);
    set_ui_command_pursuer(Qlog_out,Qempty_command_pursuer);
    log_out_command_translator_1 = 
	    STATIC_FUNCTION(log_out_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qlog_out,log_out_command_translator_1);
    Qdetect_deadlocks_for_ui = STATIC_SYMBOL("DETECT-DEADLOCKS-FOR-UI",
	    AB_package);
    make_ui_command(5,Qdetect_deadlocks_for_ui,Qnil,Qnil,
	    Qdetect_deadlocks_for_ui,Qnil);
    com_detect_deadlocks_for_ui_1 = 
	    STATIC_FUNCTION(com_detect_deadlocks_for_ui,NIL,FALSE,0,0);
    set_ui_command_function(Qdetect_deadlocks_for_ui,
	    com_detect_deadlocks_for_ui_1);
    set_ui_command_pursuer(Qdetect_deadlocks_for_ui,Qempty_command_pursuer);
    detect_deadlocks_for_ui_command_translator_1 = 
	    STATIC_FUNCTION(detect_deadlocks_for_ui_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qdetect_deadlocks_for_ui,
	    detect_deadlocks_for_ui_command_translator_1);
    array_constant_10 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qdetect_deadlocks_for_ui,array_constant_10,
	    Qmenu_string);
    Qdetect_and_break_deadlocks_for_ui = 
	    STATIC_SYMBOL("DETECT-AND-BREAK-DEADLOCKS-FOR-UI",AB_package);
    make_ui_command(5,Qdetect_and_break_deadlocks_for_ui,Qnil,Qnil,
	    Qdetect_and_break_deadlocks_for_ui,Qnil);
    com_detect_and_break_deadlocks_for_ui_1 = 
	    STATIC_FUNCTION(com_detect_and_break_deadlocks_for_ui,NIL,
	    FALSE,0,0);
    set_ui_command_function(Qdetect_and_break_deadlocks_for_ui,
	    com_detect_and_break_deadlocks_for_ui_1);
    set_ui_command_pursuer(Qdetect_and_break_deadlocks_for_ui,
	    Qempty_command_pursuer);
    detect_and_break_deadlocks_for_ui_command_translator_1 = 
	    STATIC_FUNCTION(detect_and_break_deadlocks_for_ui_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qdetect_and_break_deadlocks_for_ui,
	    detect_and_break_deadlocks_for_ui_command_translator_1);
    array_constant_11 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)57344L);
    mutate_global_property(Qdetect_and_break_deadlocks_for_ui,
	    array_constant_11,Qmenu_string);
    Qenter_package_preparation_mode = 
	    STATIC_SYMBOL("ENTER-PACKAGE-PREPARATION-MODE",AB_package);
    make_ui_command(5,Qenter_package_preparation_mode,Qnil,Qnil,
	    Qenter_package_preparation_mode,Qnil);
    string_constant_18 = 
	    STATIC_STRING("Enter Package Preparation mode\?  (This will add options to menus ~\n         that allow for potentially dangerous and irreversible changes to the ~\n         KB.)");
    com_enter_package_preparation_mode_1 = 
	    STATIC_FUNCTION(com_enter_package_preparation_mode,NIL,FALSE,0,0);
    set_ui_command_function(Qenter_package_preparation_mode,
	    com_enter_package_preparation_mode_1);
    set_ui_command_pursuer(Qenter_package_preparation_mode,
	    Qempty_command_pursuer);
    enter_package_preparation_mode_command_translator_1 = 
	    STATIC_FUNCTION(enter_package_preparation_mode_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qenter_package_preparation_mode,
	    enter_package_preparation_mode_command_translator_1);
    Qleave_package_preparation_mode = 
	    STATIC_SYMBOL("LEAVE-PACKAGE-PREPARATION-MODE",AB_package);
    make_ui_command(5,Qleave_package_preparation_mode,Qnil,Qnil,
	    Qleave_package_preparation_mode,Qnil);
    com_leave_package_preparation_mode_1 = 
	    STATIC_FUNCTION(com_leave_package_preparation_mode,NIL,FALSE,0,0);
    set_ui_command_function(Qleave_package_preparation_mode,
	    com_leave_package_preparation_mode_1);
    set_ui_command_pursuer(Qleave_package_preparation_mode,
	    Qempty_command_pursuer);
    leave_package_preparation_mode_command_translator_1 = 
	    STATIC_FUNCTION(leave_package_preparation_mode_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qleave_package_preparation_mode,
	    leave_package_preparation_mode_command_translator_1);
    Qstrip_texts_now = STATIC_SYMBOL("STRIP-TEXTS-NOW",AB_package);
    make_ui_command(5,Qstrip_texts_now,Qnil,Qnil,Qstrip_texts_now,Qnil);
    string_constant_19 = 
	    string_append2(STATIC_STRING("Strip texts now\?  (This will permanently remove most of the text ~\n         associated with all items that have been marked to be stripped of ~\n         their text.  These cha"),
	    STATIC_STRING("nges will be irreversible.)"));
    Qstrip_all_texts = STATIC_SYMBOL("STRIP-ALL-TEXTS",AB_package);
    SET_SYMBOL_FUNCTION(Qstrip_all_texts,STATIC_FUNCTION(strip_all_texts,
	    NIL,FALSE,0,0));
    com_strip_texts_now_1 = STATIC_FUNCTION(com_strip_texts_now,NIL,FALSE,0,0);
    set_ui_command_function(Qstrip_texts_now,com_strip_texts_now_1);
    set_ui_command_pursuer(Qstrip_texts_now,Qempty_command_pursuer);
    strip_texts_now_command_translator_1 = 
	    STATIC_FUNCTION(strip_texts_now_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qstrip_texts_now,
	    strip_texts_now_command_translator_1);
    Qmake_workspaces_proprietary_now = 
	    STATIC_SYMBOL("MAKE-WORKSPACES-PROPRIETARY-NOW",AB_package);
    make_ui_command(5,Qmake_workspaces_proprietary_now,Qnil,Qnil,
	    Qmake_workspaces_proprietary_now,Qnil);
    string_constant_20 = string_appendn(3,
	    STATIC_STRING("Make workspaces in this KB proprietary now\?  (This will cause workspaces ~\n         that have been given a potential proprietary package to become permanently ~\n         propr"),
	    STATIC_STRING("ietary to those packages and thus severely restricted in their use.  ~\n         Once that has been done, this KB, or any KB that has merged in those workspaces, ~\n         wil"),
	    STATIC_STRING("l only be allowed to execute with special authorization codes obtained ~\n         through Gensym Corporation.  These changes will be irreversible.)"));
    Qmake_proprietary_now = STATIC_SYMBOL("MAKE-PROPRIETARY-NOW",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_proprietary_now,
	    STATIC_FUNCTION(make_proprietary_now,NIL,FALSE,0,0));
    com_make_workspaces_proprietary_now_1 = 
	    STATIC_FUNCTION(com_make_workspaces_proprietary_now,NIL,FALSE,0,0);
    set_ui_command_function(Qmake_workspaces_proprietary_now,
	    com_make_workspaces_proprietary_now_1);
    set_ui_command_pursuer(Qmake_workspaces_proprietary_now,
	    Qempty_command_pursuer);
    make_workspaces_proprietary_now_command_translator_1 = 
	    STATIC_FUNCTION(make_workspaces_proprietary_now_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qmake_workspaces_proprietary_now,
	    make_workspaces_proprietary_now_command_translator_1);
    Qsimulate_proprietary_mode_changed = 
	    STATIC_SYMBOL("SIMULATE-PROPRIETARY-MODE-CHANGED",AB_package);
    Qenter_simulate_proprietary_mode = 
	    STATIC_SYMBOL("ENTER-SIMULATE-PROPRIETARY-MODE",AB_package);
    make_ui_command(5,Qenter_simulate_proprietary_mode,Qnil,Qnil,
	    Qenter_simulate_proprietary_mode,Qnil);
    com_enter_simulate_proprietary_mode_1 = 
	    STATIC_FUNCTION(com_enter_simulate_proprietary_mode,NIL,FALSE,0,0);
    set_ui_command_function(Qenter_simulate_proprietary_mode,
	    com_enter_simulate_proprietary_mode_1);
    set_ui_command_pursuer(Qenter_simulate_proprietary_mode,
	    Qempty_command_pursuer);
    enter_simulate_proprietary_mode_command_translator_1 = 
	    STATIC_FUNCTION(enter_simulate_proprietary_mode_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qenter_simulate_proprietary_mode,
	    enter_simulate_proprietary_mode_command_translator_1);
    Qleave_simulate_proprietary_mode = 
	    STATIC_SYMBOL("LEAVE-SIMULATE-PROPRIETARY-MODE",AB_package);
    make_ui_command(5,Qleave_simulate_proprietary_mode,Qnil,Qnil,
	    Qleave_simulate_proprietary_mode,Qnil);
    com_leave_simulate_proprietary_mode_1 = 
	    STATIC_FUNCTION(com_leave_simulate_proprietary_mode,NIL,FALSE,0,0);
    set_ui_command_function(Qleave_simulate_proprietary_mode,
	    com_leave_simulate_proprietary_mode_1);
    set_ui_command_pursuer(Qleave_simulate_proprietary_mode,
	    Qempty_command_pursuer);
    leave_simulate_proprietary_mode_command_translator_1 = 
	    STATIC_FUNCTION(leave_simulate_proprietary_mode_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qleave_simulate_proprietary_mode,
	    leave_simulate_proprietary_mode_command_translator_1);
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    make_ui_command(5,Qabort_g2,Qnil,Qnil,Qabort_g2,Qnil);
    com_abort_1 = STATIC_FUNCTION(com_abort,NIL,FALSE,0,0);
    set_ui_command_function(Qabort_g2,com_abort_1);
    set_ui_command_pursuer(Qabort_g2,Qempty_command_pursuer);
    abort_command_translator_1 = STATIC_FUNCTION(abort_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qabort_g2,abort_command_translator_1);
    Qrefresh = STATIC_SYMBOL("REFRESH",AB_package);
    make_ui_command(5,Qrefresh,list_constant_20,Qnil,Qrefresh,Qnil);
    com_refresh_1 = STATIC_FUNCTION(com_refresh,NIL,FALSE,1,1);
    set_ui_command_function(Qrefresh,com_refresh_1);
    refresh_command_pursuer_1 = STATIC_FUNCTION(refresh_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qrefresh,refresh_command_pursuer_1);
    refresh_command_translator_1 = 
	    STATIC_FUNCTION(refresh_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qrefresh,refresh_command_translator_1);
    Qtoggle_visible_grid = STATIC_SYMBOL("TOGGLE-VISIBLE-GRID",AB_package);
    Qimage_plane = STATIC_SYMBOL("IMAGE-PLANE",AB_package);
    list_constant_24 = STATIC_CONS(Qimage_plane,Qnil);
    make_ui_command(5,Qtoggle_visible_grid,list_constant_24,Qnil,
	    Qtoggle_visible_grid,Qnil);
    com_toggle_visible_grid_1 = STATIC_FUNCTION(com_toggle_visible_grid,
	    NIL,FALSE,1,1);
    set_ui_command_function(Qtoggle_visible_grid,com_toggle_visible_grid_1);
    toggle_visible_grid_command_pursuer_1 = 
	    STATIC_FUNCTION(toggle_visible_grid_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qtoggle_visible_grid,
	    toggle_visible_grid_command_pursuer_1);
    toggle_visible_grid_command_translator_1 = 
	    STATIC_FUNCTION(toggle_visible_grid_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtoggle_visible_grid,
	    toggle_visible_grid_command_translator_1);
    Qhelp = STATIC_SYMBOL("HELP",AB_package);
    Qframe_qm = STATIC_SYMBOL("FRAME\?",AB_package);
    Qframe = STATIC_SYMBOL("FRAME",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qframe_qm,Qframe);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qand_optional,list_constant_25);
    string_constant_76 = 
	    STATIC_STRING("Display a table of all keyboard commands, subject to the item-configuration\n   relevant to the item under the mouse.");
    make_ui_command(5,Qhelp,list_constant_26,string_constant_76,Qhelp,Qnil);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    Qspecial_character_entry = STATIC_SYMBOL("SPECIAL-CHARACTER-ENTRY",
	    AB_package);
    Qinsertion_of_symbol = STATIC_SYMBOL("INSERTION-OF-SYMBOL",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    com_help_1 = STATIC_FUNCTION(com_help,NIL,TRUE,0,1);
    set_ui_command_function(Qhelp,com_help_1);
    help_command_pursuer_1 = STATIC_FUNCTION(help_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qhelp,help_command_pursuer_1);
    help_command_translator_1 = STATIC_FUNCTION(help_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qhelp,help_command_translator_1);
    Qg2_launch_online_help = STATIC_SYMBOL("G2-LAUNCH-ONLINE-HELP",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    string_constant_21 = 
	    STATIC_STRING("The ~(~a~) procedure ~a does not exist.");
    string_constant_22 = 
	    STATIC_STRING("The launch-online-help procedure ~NF must be an ordinary procedure, not a ~(~A~).");
    string_constant_23 = 
	    STATIC_STRING("The launch-online-help procedure ~NF ~\n          is either inactive or has a status other than OK.");
    list_constant_27 = STATIC_CONS(Qg2_window,Qnil);
    list_constant_28 = STATIC_CONS(Qab_class,list_constant_27);
    list_constant = STATIC_CONS(list_constant_28,Qnil);
    string_constant_24 = 
	    STATIC_STRING("The launch-online-help procedure ~NF\'s ~\n          argument list is not (<window> :class g2-window)");
    Qlaunch_online_help = STATIC_SYMBOL("LAUNCH-ONLINE-HELP",AB_package);
    Qworkstation = STATIC_SYMBOL("WORKSTATION",AB_package);
    list_constant_29 = STATIC_CONS(Qworkstation,Qnil);
    make_ui_command(5,Qlaunch_online_help,list_constant_29,Qnil,
	    Qlaunch_online_help,Qnil);
    com_launch_online_help_1 = STATIC_FUNCTION(com_launch_online_help,NIL,
	    FALSE,1,1);
    set_ui_command_function(Qlaunch_online_help,com_launch_online_help_1);
    launch_online_help_command_pursuer_1 = 
	    STATIC_FUNCTION(launch_online_help_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qlaunch_online_help,
	    launch_online_help_command_pursuer_1);
    launch_online_help_command_translator_1 = 
	    STATIC_FUNCTION(launch_online_help_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qlaunch_online_help,
	    launch_online_help_command_translator_1);
    array_constant_12 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qlaunch_online_help,array_constant_12,Qmenu_string);
    Qcirculate_up = STATIC_SYMBOL("CIRCULATE-UP",AB_package);
    Qpane = STATIC_SYMBOL("PANE",AB_package);
    list_constant_30 = STATIC_CONS(Qpane,Qnil);
    make_ui_command(5,Qcirculate_up,list_constant_30,Qnil,Qcirculate_up,Qnil);
    com_circulate_up_1 = STATIC_FUNCTION(com_circulate_up,NIL,FALSE,1,1);
    set_ui_command_function(Qcirculate_up,com_circulate_up_1);
    circulate_up_command_pursuer_1 = 
	    STATIC_FUNCTION(circulate_up_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcirculate_up,circulate_up_command_pursuer_1);
    circulate_up_command_translator_1 = 
	    STATIC_FUNCTION(circulate_up_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qcirculate_up,circulate_up_command_translator_1);
    Qcirculate_down = STATIC_SYMBOL("CIRCULATE-DOWN",AB_package);
    make_ui_command(5,Qcirculate_down,list_constant_30,Qnil,
	    Qcirculate_down,Qnil);
    com_circulate_down_1 = STATIC_FUNCTION(com_circulate_down,NIL,FALSE,1,1);
    set_ui_command_function(Qcirculate_down,com_circulate_down_1);
    circulate_down_command_pursuer_1 = 
	    STATIC_FUNCTION(circulate_down_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcirculate_down,circulate_down_command_pursuer_1);
    circulate_down_command_translator_1 = 
	    STATIC_FUNCTION(circulate_down_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qcirculate_down,
	    circulate_down_command_translator_1);
    Qlift_to_top = STATIC_SYMBOL("LIFT-TO-TOP",AB_package);
    make_ui_command(5,Qlift_to_top,list_constant_24,Qnil,Qlift_to_top,Qnil);
    com_lift_to_top_1 = STATIC_FUNCTION(com_lift_to_top,NIL,FALSE,1,1);
    set_ui_command_function(Qlift_to_top,com_lift_to_top_1);
    lift_to_top_command_pursuer_1 = 
	    STATIC_FUNCTION(lift_to_top_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qlift_to_top,lift_to_top_command_pursuer_1);
    lift_to_top_command_translator_1 = 
	    STATIC_FUNCTION(lift_to_top_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qlift_to_top,lift_to_top_command_translator_1);
    array_constant_13 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    mutate_global_property(Qlift_to_top,array_constant_13,Qmenu_string);
    Qdrop_to_bottom = STATIC_SYMBOL("DROP-TO-BOTTOM",AB_package);
    make_ui_command(5,Qdrop_to_bottom,list_constant_24,Qnil,
	    Qdrop_to_bottom,Qnil);
    com_drop_to_bottom_1 = STATIC_FUNCTION(com_drop_to_bottom,NIL,FALSE,1,1);
    set_ui_command_function(Qdrop_to_bottom,com_drop_to_bottom_1);
    drop_to_bottom_command_pursuer_1 = 
	    STATIC_FUNCTION(drop_to_bottom_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qdrop_to_bottom,drop_to_bottom_command_pursuer_1);
    drop_to_bottom_command_translator_1 = 
	    STATIC_FUNCTION(drop_to_bottom_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qdrop_to_bottom,
	    drop_to_bottom_command_translator_1);
    array_constant_14 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qdrop_to_bottom,array_constant_14,Qmenu_string);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qfreeform_table = STATIC_SYMBOL("FREEFORM-TABLE",AB_package);
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qborderless_free_text = STATIC_SYMBOL("BORDERLESS-FREE-TEXT",AB_package);
    Qlift_item_to_top = STATIC_SYMBOL("LIFT-ITEM-TO-TOP",AB_package);
    Qframe_for_selection = STATIC_SYMBOL("FRAME-FOR-SELECTION",AB_package);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Qframe,Qframe_for_selection);
    list_constant_32 = STATIC_CONS(list_constant_31,Qnil);
    make_ui_command(5,Qlift_item_to_top,list_constant_32,Qnil,Qlift_to_top,
	    Qnil);
    com_lift_item_to_top_1 = STATIC_FUNCTION(com_lift_item_to_top,NIL,
	    FALSE,1,1);
    set_ui_command_function(Qlift_item_to_top,com_lift_item_to_top_1);
    lift_item_to_top_command_pursuer_1 = 
	    STATIC_FUNCTION(lift_item_to_top_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qlift_item_to_top,
	    lift_item_to_top_command_pursuer_1);
    lift_item_to_top_command_translator_1 = 
	    STATIC_FUNCTION(lift_item_to_top_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qlift_item_to_top,
	    lift_item_to_top_command_translator_1);
    Qdrop_item_to_bottom = STATIC_SYMBOL("DROP-ITEM-TO-BOTTOM",AB_package);
    make_ui_command(5,Qdrop_item_to_bottom,list_constant_32,Qnil,
	    Qdrop_to_bottom,Qnil);
    com_drop_item_to_bottom_1 = STATIC_FUNCTION(com_drop_item_to_bottom,
	    NIL,FALSE,1,1);
    set_ui_command_function(Qdrop_item_to_bottom,com_drop_item_to_bottom_1);
    drop_item_to_bottom_command_pursuer_1 = 
	    STATIC_FUNCTION(drop_item_to_bottom_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qdrop_item_to_bottom,
	    drop_item_to_bottom_command_pursuer_1);
    drop_item_to_bottom_command_translator_1 = 
	    STATIC_FUNCTION(drop_item_to_bottom_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qdrop_item_to_bottom,
	    drop_item_to_bottom_command_translator_1);
    Qg2_lift_item_to_top = STATIC_SYMBOL("G2-LIFT-ITEM-TO-TOP",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lift_item_to_top,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lift_item_to_top,
	    STATIC_FUNCTION(g2_lift_item_to_top,NIL,FALSE,1,1));
    Qg2_lift_item_to_top_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LIFT-ITEM-TO-TOP-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qitem,Ktype,list_constant_33);
    list_constant_35 = STATIC_CONS(list_constant_34,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_lift_item_to_top,
	    make_system_rpc_1(Qg2_lift_item_to_top_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_35,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,Qg2_lift_item_to_top,
	    System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_lift_item_to_top_system_rpc_internal,
	    STATIC_FUNCTION(g2_lift_item_to_top_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_drop_item_to_bottom = STATIC_SYMBOL("G2-DROP-ITEM-TO-BOTTOM",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_drop_item_to_bottom,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_drop_item_to_bottom,
	    STATIC_FUNCTION(g2_drop_item_to_bottom,NIL,FALSE,1,1));
    Qg2_drop_item_to_bottom_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DROP-ITEM-TO-BOTTOM-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_drop_item_to_bottom,
	    make_system_rpc_1(Qg2_drop_item_to_bottom_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_35,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,Qg2_drop_item_to_bottom,
	    System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_drop_item_to_bottom_system_rpc_internal,
	    STATIC_FUNCTION(g2_drop_item_to_bottom_system_rpc_internal,NIL,
	    FALSE,2,2));
    Qg2_lift_item_to_front = STATIC_SYMBOL("G2-LIFT-ITEM-TO-FRONT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_lift_item_to_front,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_lift_item_to_front,
	    STATIC_FUNCTION(g2_lift_item_to_front,NIL,FALSE,2,2));
    Qg2_lift_item_in_front_of = STATIC_SYMBOL("G2-LIFT-ITEM-IN-FRONT-OF",
	    AB_package);
    Qg2_lift_item_in_front_of_system_rpc_internal = 
	    STATIC_SYMBOL("G2-LIFT-ITEM-IN-FRONT-OF-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qitem_1 = STATIC_SYMBOL("ITEM-1",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Ktype,list_constant_33);
    list_constant_37 = STATIC_CONS(Qitem_1,list_constant_36);
    Qitem_2 = STATIC_SYMBOL("ITEM-2",AB_package);
    list_constant_38 = STATIC_CONS(Qitem_2,list_constant_36);
    list_constant_39 = STATIC_LIST((SI_Long)2L,list_constant_37,
	    list_constant_38);
    mutate_global_property(Qg2_lift_item_in_front_of,
	    make_system_rpc_1(Qg2_lift_item_in_front_of_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_39,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,Qg2_lift_item_in_front_of,
	    System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_lift_item_in_front_of_system_rpc_internal,
	    STATIC_FUNCTION(g2_lift_item_in_front_of_system_rpc_internal,
	    NIL,FALSE,3,3));
    Qg2_drop_item_to_back = STATIC_SYMBOL("G2-DROP-ITEM-TO-BACK",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_drop_item_to_back,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_drop_item_to_back,
	    STATIC_FUNCTION(g2_drop_item_to_back,NIL,FALSE,2,2));
    Qg2_drop_item_behind = STATIC_SYMBOL("G2-DROP-ITEM-BEHIND",AB_package);
    Qg2_drop_item_behind_system_rpc_internal = 
	    STATIC_SYMBOL("G2-DROP-ITEM-BEHIND-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_drop_item_behind,
	    make_system_rpc_1(Qg2_drop_item_behind_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_39,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,Qg2_drop_item_behind,
	    System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_drop_item_behind_system_rpc_internal,
	    STATIC_FUNCTION(g2_drop_item_behind_system_rpc_internal,NIL,
	    FALSE,3,3));
    Qg2_get_item_layer_position = 
	    STATIC_SYMBOL("G2-GET-ITEM-LAYER-POSITION",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_item_layer_position,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_item_layer_position,
	    STATIC_FUNCTION(g2_get_item_layer_position,NIL,FALSE,1,1));
    Qg2_get_item_layer_position_system_rpc_internal = 
	    STATIC_SYMBOL("G2-GET-ITEM-LAYER-POSITION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_40 = STATIC_CONS(Qinteger,Qnil);
    mutate_global_property(Qg2_get_item_layer_position,
	    make_system_rpc_1(Qg2_get_item_layer_position_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_35,
	    Nil,T),list_constant_40),Qsystem_defined_rpc);
    system_defined_rpcs_new_value = adjoin(2,Qg2_get_item_layer_position,
	    System_defined_rpcs);
    System_defined_rpcs = system_defined_rpcs_new_value;
    SET_SYMBOL_FUNCTION(Qg2_get_item_layer_position_system_rpc_internal,
	    STATIC_FUNCTION(g2_get_item_layer_position_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_last_input_event = STATIC_SYMBOL("G2-LAST-INPUT-EVENT",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_last_input_event,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_last_input_event,
	    STATIC_FUNCTION(g2_last_input_event,NIL,FALSE,1,1));
    Qg2_last_input_event_info = STATIC_SYMBOL("G2-LAST-INPUT-EVENT-INFO",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_last_input_event_info,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_last_input_event_info,
	    STATIC_FUNCTION(g2_last_input_event_info,NIL,FALSE,1,1));
    Qg2_refresh_image_definition = 
	    STATIC_SYMBOL("G2-REFRESH-IMAGE-DEFINITION",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_refresh_image_definition,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_refresh_image_definition,
	    STATIC_FUNCTION(g2_refresh_image_definition,NIL,FALSE,1,1));
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    string_constant_25 = STATIC_STRING("The ~a");
    string_constant_26 = 
	    STATIC_STRING(" argument of ~a is declared to take values of class ~\n       ~a, but instead it received ");
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_27 = STATIC_STRING("~NF, an instance of the class ~a.");
    string_constant_28 = 
	    STATIC_STRING("The ~a argument of ~a must be a connected window.");
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    list_constant_41 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_47 = STATIC_CONS(Qattribute,list_constant_41);
    Qline = STATIC_SYMBOL("LINE",AB_package);
    list_constant_58 = STATIC_CONS(Qline,list_constant_40);
    Qcolumn = STATIC_SYMBOL("COLUMN",AB_package);
    list_constant_59 = STATIC_CONS(Qcolumn,list_constant_40);
    Qexclude = STATIC_SYMBOL("EXCLUDE",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    list_constant_42 = STATIC_CONS(Qtext,Qnil);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_42);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_43);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qexclude,list_constant_44);
    Qpreferred_editor = STATIC_SYMBOL("PREFERRED-EDITOR",AB_package);
    Qclassic = STATIC_SYMBOL("CLASSIC",AB_package);
    Qnative = STATIC_SYMBOL("NATIVE",AB_package);
    list_constant_45 = STATIC_LIST((SI_Long)3L,Qmember,Qclassic,Qnative);
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qpreferred_editor,
	    list_constant_45);
    Qgrammar = STATIC_SYMBOL("GRAMMAR",AB_package);
    list_constant_46 = STATIC_CONS(Qab_class,list_constant_41);
    Qdefining_class = STATIC_SYMBOL("DEFINING-CLASS",AB_package);
    list_constant_48 = STATIC_CONS(Qdefining_class,list_constant_41);
    list_constant_49 = STATIC_LIST((SI_Long)3L,list_constant_46,
	    list_constant_47,list_constant_48);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_49);
    list_constant_51 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_50);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qgrammar,list_constant_51);
    Qtoolbar = STATIC_SYMBOL("TOOLBAR",AB_package);
    Qtoolbar_id = STATIC_SYMBOL("TOOLBAR-ID",AB_package);
    list_constant_52 = STATIC_CONS(Qtoolbar_id,list_constant_40);
    Qtoolbar_text = STATIC_SYMBOL("TOOLBAR-TEXT",AB_package);
    list_constant_53 = STATIC_CONS(Qtoolbar_text,list_constant_42);
    list_constant_54 = STATIC_LIST((SI_Long)2L,list_constant_52,
	    list_constant_53);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_54);
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_55);
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qtoolbar,list_constant_56);
    Qtoolbar_callback_function = STATIC_SYMBOL("TOOLBAR-CALLBACK-FUNCTION",
	    AB_package);
    list_constant_64 = STATIC_CONS(Qtoolbar_callback_function,
	    list_constant_41);
    Qtitle = STATIC_SYMBOL("TITLE",AB_package);
    list_constant_65 = STATIC_CONS(Qtitle,list_constant_42);
    Qsemaphore = STATIC_SYMBOL("SEMAPHORE",AB_package);
    Qsymbolic_parameter = STATIC_SYMBOL("SYMBOLIC-PARAMETER",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qab_class,Qsymbolic_parameter);
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qsemaphore,list_constant_57);
    list_constant_67 = STATIC_LIST((SI_Long)10L,list_constant_47,
	    list_constant_58,list_constant_59,list_constant_60,
	    list_constant_61,list_constant_62,list_constant_63,
	    list_constant_64,list_constant_65,list_constant_66);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_67);
    Launch_editor_options_type = list_constant_68;
    string_constant_29 = 
	    STATIC_STRING("The attribute named ~a was not found.");
    Qcompound_slot_descriptor = STATIC_SYMBOL("COMPOUND-SLOT-DESCRIPTOR",
	    AB_package);
    string_constant_30 = 
	    STATIC_STRING("Component attributes of a ~a, such as ~a, ~\n                                    may not be edited programmatically.");
    string_constant_31 = 
	    STATIC_STRING("The editing of attribute ~a of ~NF is restricted.");
    string_constant_32 = 
	    STATIC_STRING("The attribute ~a of ~NF may not be edited.");
    Qreturn_from_field_edit = STATIC_SYMBOL("RETURN-FROM-FIELD-EDIT",
	    AB_package);
    Qreclaim_list_and_record_abort_in_edit_status_parameter = 
	    STATIC_SYMBOL("RECLAIM-LIST-AND-RECORD-ABORT-IN-EDIT-STATUS-PARAMETER",
	    AB_package);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    if (Editor_toolbar_user_callback == UNBOUND)
	Editor_toolbar_user_callback = Nil;
    Qg2_ui_close_current_editor = 
	    STATIC_SYMBOL("G2-UI-CLOSE-CURRENT-EDITOR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_close_current_editor,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_33 = STATIC_STRING("There is no editor open on ~NF.");
    SET_SYMBOL_FUNCTION(Qg2_ui_close_current_editor,
	    STATIC_FUNCTION(g2_ui_close_current_editor,NIL,FALSE,2,2));
    Qg2_ui_launch_editor_extended = 
	    STATIC_SYMBOL("G2-UI-LAUNCH-EDITOR-EXTENDED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_launch_editor_extended,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qg2_ui_launch_editor = STATIC_SYMBOL("G2-UI-LAUNCH-EDITOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_ui_launch_editor_extended,
	    STATIC_FUNCTION(g2_ui_launch_editor_extended,NIL,FALSE,8,8));
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_launch_editor,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_ui_launch_editor,
	    STATIC_FUNCTION(g2_ui_launch_editor,NIL,FALSE,3,3));
    if (Edit_states == UNBOUND)
	Edit_states = Nil;
    if (Highest_state_index == UNBOUND)
	Highest_state_index = FIX((SI_Long)0L);
    Qmaximum_open_editors = STATIC_SYMBOL("MAXIMUM-OPEN-EDITORS",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_open_editors,FIX((SI_Long)4096L));
    Qg2_ui_launch_editor_returning_handle = 
	    STATIC_SYMBOL("G2-UI-LAUNCH-EDITOR-RETURNING-HANDLE",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_launch_editor_returning_handle,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_ui_launch_editor_returning_handle,
	    STATIC_FUNCTION(g2_ui_launch_editor_returning_handle,NIL,FALSE,
	    3,3));
    Qg2_ui_finish_editing_session = 
	    STATIC_SYMBOL("G2-UI-FINISH-EDITING-SESSION",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_finish_editing_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qend = STATIC_SYMBOL("END",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_ui_finish_editing_session,
	    STATIC_FUNCTION(g2_ui_finish_editing_session,NIL,FALSE,2,2));
    string_constant_34 = 
	    STATIC_STRING("The grammar specification ~NV in invalid");
    string_constant_35 = STATIC_STRING(" because ~A is not a known class");
    string_constant_36 = 
	    STATIC_STRING(" because ~A is not an attribute of ~A");
    string_constant_37 = STATIC_STRING(".");
    Qquoted_character = STATIC_SYMBOL("QUOTED-CHARACTER",AB_package);
    Qellipsis = STATIC_SYMBOL("ELLIPSIS",AB_package);
    Qcomment = STATIC_SYMBOL("COMMENT",AB_package);
    Qsingle_line_comment = STATIC_SYMBOL("SINGLE-LINE-COMMENT",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qquoted_character,Qellipsis,
	    Qcomment,Qsingle_line_comment);
    Qg2_ui_get_text_from_current_editor = 
	    STATIC_SYMBOL("G2-UI-GET-TEXT-FROM-CURRENT-EDITOR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_get_text_from_current_editor,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_38 = 
	    STATIC_STRING("There is no edit in progress on ~NF ~NF.");
    SET_SYMBOL_FUNCTION(Qg2_ui_get_text_from_current_editor,
	    STATIC_FUNCTION(g2_ui_get_text_from_current_editor,NIL,FALSE,1,1));
    Qg2_ui_insert_text_into_current_editor = 
	    STATIC_SYMBOL("G2-UI-INSERT-TEXT-INTO-CURRENT-EDITOR",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_insert_text_into_current_editor,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_39 = STATIC_STRING("There is no edit in progress on ~NF.");
    SET_SYMBOL_FUNCTION(Qg2_ui_insert_text_into_current_editor,
	    STATIC_FUNCTION(g2_ui_insert_text_into_current_editor,NIL,
	    FALSE,3,3));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    Qg2_defstruct_structure_name_edit_state_g2_struct = 
	    STATIC_SYMBOL("EDIT-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_system_command = STATIC_SYMBOL("G2-SYSTEM-COMMAND",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_system_command,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    string_constant_40 = 
	    STATIC_STRING("The use of a ui-client-session in g2-system-command is not yet supported");
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_system_command,
	    STATIC_FUNCTION(g2_system_command,NIL,FALSE,4,4));
    Qui_command_named = STATIC_SYMBOL("UI-COMMAND-NAMED",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)15L,Qnetwork_info,
	    Qnew_title_block,Qremove_tracing_and_breakpoints,
	    Qenable_all_items,Qdo_not_highlight_invoked_rules,
	    Qhighlight_invoked_rules,Qlong_menus,Qshort_menus,Qchange_mode,
	    Qchange_password,Qsave_kb,Qinspect,Qreinstall_authorized_users,
	    Qturn_on_all_explanation_caching,
	    Qturn_off_all_explanation_caching);
    Qabort_user_mouse_tracking = STATIC_SYMBOL("ABORT-USER-MOUSE-TRACKING",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qabort_user_mouse_tracking,
	    STATIC_FUNCTION(abort_user_mouse_tracking,NIL,FALSE,1,1));
    Qfull_scale = STATIC_SYMBOL("FULL-SCALE",AB_package);
    Qnormalized_full_scale = STATIC_SYMBOL("NORMALIZED-FULL-SCALE",AB_package);
    Qscale_to_fit = STATIC_SYMBOL("SCALE-TO-FIT",AB_package);
    Qmaximum_scale_to_fit = STATIC_SYMBOL("MAXIMUM-SCALE-TO-FIT",AB_package);
    Qone_quarter_the_scale = STATIC_SYMBOL("ONE-QUARTER-THE-SCALE",AB_package);
    Qfour_times_the_scale = STATIC_SYMBOL("FOUR-TIMES-THE-SCALE",AB_package);
    Qtwenty_percent_smaller = STATIC_SYMBOL("TWENTY-PERCENT-SMALLER",
	    AB_package);
    Qtwenty_percent_bigger = STATIC_SYMBOL("TWENTY-PERCENT-BIGGER",AB_package);
    Qtwenty_percent_narrower = STATIC_SYMBOL("TWENTY-PERCENT-NARROWER",
	    AB_package);
    Qtwenty_percent_wider = STATIC_SYMBOL("TWENTY-PERCENT-WIDER",AB_package);
    Qcenter_origin = STATIC_SYMBOL("CENTER-ORIGIN",AB_package);
    Qshift_left_ten_percent = STATIC_SYMBOL("SHIFT-LEFT-TEN-PERCENT",
	    AB_package);
    Qshift_right_ten_percent = STATIC_SYMBOL("SHIFT-RIGHT-TEN-PERCENT",
	    AB_package);
    Qshift_left_one_percent = STATIC_SYMBOL("SHIFT-LEFT-ONE-PERCENT",
	    AB_package);
    Qshift_right_one_percent = STATIC_SYMBOL("SHIFT-RIGHT-ONE-PERCENT",
	    AB_package);
    Qshift_up_ten_percent = STATIC_SYMBOL("SHIFT-UP-TEN-PERCENT",AB_package);
    Qshift_down_ten_percent = STATIC_SYMBOL("SHIFT-DOWN-TEN-PERCENT",
	    AB_package);
    Qshift_up_one_percent = STATIC_SYMBOL("SHIFT-UP-ONE-PERCENT",AB_package);
    Qshift_down_one_percent = STATIC_SYMBOL("SHIFT-DOWN-ONE-PERCENT",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)19L,Qfull_scale,
	    Qnormalized_full_scale,Qscale_to_fit,Qmaximum_scale_to_fit,
	    Qone_quarter_the_scale,Qfour_times_the_scale,
	    Qtwenty_percent_smaller,Qtwenty_percent_bigger,
	    Qtwenty_percent_narrower,Qtwenty_percent_wider,Qcenter_origin,
	    Qshift_left_ten_percent,Qshift_right_ten_percent,
	    Qshift_left_one_percent,Qshift_right_one_percent,
	    Qshift_up_ten_percent,Qshift_down_ten_percent,
	    Qshift_up_one_percent,Qshift_down_one_percent);
    Qab_describe = STATIC_SYMBOL("DESCRIBE",AB_package);
    Qdescribe_configuration = STATIC_SYMBOL("DESCRIBE-CONFIGURATION",
	    AB_package);
    Qdynamic_backward_chaining = STATIC_SYMBOL("DYNAMIC-BACKWARD-CHAINING",
	    AB_package);
    Qdescribe_chaining = STATIC_SYMBOL("DESCRIBE-CHAINING",AB_package);
    Qdynamic_generic_rule_display = 
	    STATIC_SYMBOL("DYNAMIC-GENERIC-RULE-DISPLAY",AB_package);
    Qdynamic_rule_invocation_display = 
	    STATIC_SYMBOL("DYNAMIC-RULE-INVOCATION-DISPLAY",AB_package);
    Qenable = STATIC_SYMBOL("ENABLE",AB_package);
    Qdisable = STATIC_SYMBOL("DISABLE",AB_package);
    Qredo_layout = STATIC_SYMBOL("REDO-LAYOUT",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qtable_of_hidden_attributes = 
	    STATIC_SYMBOL("TABLE-OF-HIDDEN-ATTRIBUTES",AB_package);
    Qshow_unsaved_attributes = STATIC_SYMBOL("SHOW-UNSAVED-ATTRIBUTES",
	    AB_package);
    Qchange_size = STATIC_SYMBOL("CHANGE-SIZE",AB_package);
    Qrestore_to_normal_size = STATIC_SYMBOL("RESTORE-TO-NORMAL-SIZE",
	    AB_package);
    Qtransfer = STATIC_SYMBOL("TRANSFER",AB_package);
    Qclone = STATIC_SYMBOL("CLONE",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qtransfer,Qclone);
    list_constant_4 = STATIC_LIST_STAR((SI_Long)16L,Qab_describe,
	    Qdescribe_configuration,Qdynamic_backward_chaining,
	    Qdescribe_chaining,Qdynamic_generic_rule_display,
	    Qdynamic_rule_invocation_display,Qenable,Qdisable,Qdelete,
	    Qredo_layout,Qtable,Qtable_of_hidden_attributes,
	    Qshow_unsaved_attributes,Qchange_size,Qrestore_to_normal_size,
	    list_constant_69);
    list_constant_6 = STATIC_CONS(Qchange_size,list_constant_69);
    list_constant_5 = STATIC_LIST_STAR((SI_Long)4L,Qtable,
	    Qtable_of_hidden_attributes,Qshow_unsaved_attributes,
	    list_constant_6);
    string_constant_41 = 
	    STATIC_STRING("The item ~NF is not transferrable, cannot do ~a command.");
    string_constant_42 = 
	    STATIC_STRING("The item ~NF is not clonable, cannot do ~a command.");
    string_constant_43 = 
	    STATIC_STRING("The item ~NF is not showing, cannot do ~a command.");
    string_constant_44 = 
	    STATIC_STRING("The item ~NF is not be deleteable, cannot do ~a command.");
    Qredo_layout_of_g2gl_body = STATIC_SYMBOL("REDO-LAYOUT-OF-G2GL-BODY",
	    AB_package);
    string_constant_45 = 
	    STATIC_STRING("The item ~NF is not a G2GL body workspace, cannot do ~a command.");
    Qedit_icon = STATIC_SYMBOL("EDIT-ICON",AB_package);
    string_constant_46 = 
	    STATIC_STRING("the EDIT-ICON case of G2-SYSTEM-COMMAND");
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    string_constant_47 = 
	    STATIC_STRING("The ~a argument of ~a received ~a, which does not name a system command.");
    Qcommand_name = STATIC_SYMBOL("COMMAND-NAME",AB_package);
    Qg2_command_is_enabled = STATIC_SYMBOL("G2-COMMAND-IS-ENABLED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_command_is_enabled,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Quser_menu_choice = STATIC_SYMBOL("USER-MENU-CHOICE",AB_package);
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qab_class,Quser_menu_choice);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,list_constant_70);
    SET_SYMBOL_FUNCTION(Qg2_command_is_enabled,
	    STATIC_FUNCTION(g2_command_is_enabled,NIL,FALSE,3,3));
    Qplot_names = STATIC_SYMBOL("PLOT-NAMES",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qclass_qualified_name,
	    Qtrend_chart,Qplot_names);
    Qg2_launch_operate_on_area = STATIC_SYMBOL("G2-LAUNCH-OPERATE-ON-AREA",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_launch_operate_on_area,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qoperate_on_area = STATIC_SYMBOL("OPERATE-ON-AREA",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_launch_operate_on_area,
	    STATIC_FUNCTION(g2_launch_operate_on_area,NIL,FALSE,4,4));
    Qdo_scrolling = STATIC_SYMBOL("DO-SCROLLING",AB_package);
    Qstepper_of_scroll_bar_spot = 
	    STATIC_SYMBOL("STEPPER-OF-SCROLL-BAR-SPOT",AB_package);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qstepper_of_scroll_bar_spot,
	    Qspot);
    list_constant_72 = STATIC_LIST((SI_Long)2L,Qblock,Qblock);
    list_constant_73 = STATIC_CONS(Qimage_plane,list_constant_24);
    list_constant_74 = STATIC_LIST((SI_Long)3L,list_constant_71,
	    list_constant_72,list_constant_73);
    make_ui_command(5,Qdo_scrolling,list_constant_74,Qnil,Qdo_scrolling,Qnil);
    com_do_scrolling_1 = STATIC_FUNCTION(com_do_scrolling,NIL,FALSE,3,3);
    set_ui_command_function(Qdo_scrolling,com_do_scrolling_1);
    do_scrolling_command_pursuer_1 = 
	    STATIC_FUNCTION(do_scrolling_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qdo_scrolling,do_scrolling_command_pursuer_1);
    do_scrolling_command_translator_1 = 
	    STATIC_FUNCTION(do_scrolling_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qdo_scrolling,do_scrolling_command_translator_1);
    Qrefreshes_image_plane_p = STATIC_SYMBOL("REFRESHES-IMAGE-PLANE-P",
	    AB_package);
    mutate_global_property(Qfull_scale,T,Qrefreshes_image_plane_p);
    Qx_in_window = STATIC_SYMBOL("X-IN-WINDOW",AB_package);
    Qy_in_window = STATIC_SYMBOL("Y-IN-WINDOW",AB_package);
    list_constant_75 = STATIC_LIST((SI_Long)3L,Qimage_plane,Qx_in_window,
	    Qy_in_window);
    make_ui_command(5,Qfull_scale,list_constant_75,Qnil,Qfull_scale,Qnil);
    com_full_scale_1 = STATIC_FUNCTION(com_full_scale,NIL,FALSE,3,3);
    set_ui_command_function(Qfull_scale,com_full_scale_1);
    full_scale_command_pursuer_1 = 
	    STATIC_FUNCTION(full_scale_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qfull_scale,full_scale_command_pursuer_1);
    full_scale_command_translator_1 = 
	    STATIC_FUNCTION(full_scale_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qfull_scale,full_scale_command_translator_1);
    mutate_global_property(Qnormalized_full_scale,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qnormalized_full_scale,list_constant_75,Qnil,
	    Qnormalized_full_scale,Qnil);
    com_normalized_full_scale_1 = 
	    STATIC_FUNCTION(com_normalized_full_scale,NIL,FALSE,3,3);
    set_ui_command_function(Qnormalized_full_scale,
	    com_normalized_full_scale_1);
    normalized_full_scale_command_pursuer_1 = 
	    STATIC_FUNCTION(normalized_full_scale_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qnormalized_full_scale,
	    normalized_full_scale_command_pursuer_1);
    normalized_full_scale_command_translator_1 = 
	    STATIC_FUNCTION(normalized_full_scale_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qnormalized_full_scale,
	    normalized_full_scale_command_translator_1);
    mutate_global_property(Qscale_to_fit,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qscale_to_fit,list_constant_75,Qnil,Qscale_to_fit,Qnil);
    com_scale_to_fit_1 = STATIC_FUNCTION(com_scale_to_fit,NIL,FALSE,3,3);
    set_ui_command_function(Qscale_to_fit,com_scale_to_fit_1);
    scale_to_fit_command_pursuer_1 = 
	    STATIC_FUNCTION(scale_to_fit_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qscale_to_fit,scale_to_fit_command_pursuer_1);
    scale_to_fit_command_translator_1 = 
	    STATIC_FUNCTION(scale_to_fit_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qscale_to_fit,scale_to_fit_command_translator_1);
    mutate_global_property(Qmaximum_scale_to_fit,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qmaximum_scale_to_fit,list_constant_75,Qnil,
	    Qmaximum_scale_to_fit,Qnil);
    com_maximum_scale_to_fit_1 = STATIC_FUNCTION(com_maximum_scale_to_fit,
	    NIL,FALSE,3,3);
    set_ui_command_function(Qmaximum_scale_to_fit,com_maximum_scale_to_fit_1);
    maximum_scale_to_fit_command_pursuer_1 = 
	    STATIC_FUNCTION(maximum_scale_to_fit_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qmaximum_scale_to_fit,
	    maximum_scale_to_fit_command_pursuer_1);
    maximum_scale_to_fit_command_translator_1 = 
	    STATIC_FUNCTION(maximum_scale_to_fit_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qmaximum_scale_to_fit,
	    maximum_scale_to_fit_command_translator_1);
    mutate_global_property(Qone_quarter_the_scale,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qone_quarter_the_scale,list_constant_75,Qnil,
	    Qone_quarter_the_scale,Qnil);
    com_one_quarter_the_scale_1 = 
	    STATIC_FUNCTION(com_one_quarter_the_scale,NIL,FALSE,3,3);
    set_ui_command_function(Qone_quarter_the_scale,
	    com_one_quarter_the_scale_1);
    one_quarter_the_scale_command_pursuer_1 = 
	    STATIC_FUNCTION(one_quarter_the_scale_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qone_quarter_the_scale,
	    one_quarter_the_scale_command_pursuer_1);
    one_quarter_the_scale_command_translator_1 = 
	    STATIC_FUNCTION(one_quarter_the_scale_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qone_quarter_the_scale,
	    one_quarter_the_scale_command_translator_1);
    mutate_global_property(Qfour_times_the_scale,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qfour_times_the_scale,list_constant_75,Qnil,
	    Qfour_times_the_scale,Qnil);
    com_four_times_the_scale_1 = STATIC_FUNCTION(com_four_times_the_scale,
	    NIL,FALSE,3,3);
    set_ui_command_function(Qfour_times_the_scale,com_four_times_the_scale_1);
    four_times_the_scale_command_pursuer_1 = 
	    STATIC_FUNCTION(four_times_the_scale_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qfour_times_the_scale,
	    four_times_the_scale_command_pursuer_1);
    four_times_the_scale_command_translator_1 = 
	    STATIC_FUNCTION(four_times_the_scale_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qfour_times_the_scale,
	    four_times_the_scale_command_translator_1);
    mutate_global_property(Qtwenty_percent_smaller,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qtwenty_percent_smaller,list_constant_75,Qnil,
	    Qtwenty_percent_smaller,Qnil);
    com_twenty_percent_smaller_1 = 
	    STATIC_FUNCTION(com_twenty_percent_smaller,NIL,FALSE,3,3);
    set_ui_command_function(Qtwenty_percent_smaller,
	    com_twenty_percent_smaller_1);
    twenty_percent_smaller_command_pursuer_1 = 
	    STATIC_FUNCTION(twenty_percent_smaller_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtwenty_percent_smaller,
	    twenty_percent_smaller_command_pursuer_1);
    twenty_percent_smaller_command_translator_1 = 
	    STATIC_FUNCTION(twenty_percent_smaller_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtwenty_percent_smaller,
	    twenty_percent_smaller_command_translator_1);
    mutate_global_property(Qtwenty_percent_bigger,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qtwenty_percent_bigger,list_constant_75,Qnil,
	    Qtwenty_percent_bigger,Qnil);
    com_twenty_percent_bigger_1 = 
	    STATIC_FUNCTION(com_twenty_percent_bigger,NIL,FALSE,3,3);
    set_ui_command_function(Qtwenty_percent_bigger,
	    com_twenty_percent_bigger_1);
    twenty_percent_bigger_command_pursuer_1 = 
	    STATIC_FUNCTION(twenty_percent_bigger_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtwenty_percent_bigger,
	    twenty_percent_bigger_command_pursuer_1);
    twenty_percent_bigger_command_translator_1 = 
	    STATIC_FUNCTION(twenty_percent_bigger_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtwenty_percent_bigger,
	    twenty_percent_bigger_command_translator_1);
    mutate_global_property(Qtwenty_percent_narrower,T,
	    Qrefreshes_image_plane_p);
    make_ui_command(5,Qtwenty_percent_narrower,list_constant_75,Qnil,
	    Qtwenty_percent_narrower,Qnil);
    com_twenty_percent_narrower_1 = 
	    STATIC_FUNCTION(com_twenty_percent_narrower,NIL,FALSE,3,3);
    set_ui_command_function(Qtwenty_percent_narrower,
	    com_twenty_percent_narrower_1);
    twenty_percent_narrower_command_pursuer_1 = 
	    STATIC_FUNCTION(twenty_percent_narrower_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtwenty_percent_narrower,
	    twenty_percent_narrower_command_pursuer_1);
    twenty_percent_narrower_command_translator_1 = 
	    STATIC_FUNCTION(twenty_percent_narrower_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtwenty_percent_narrower,
	    twenty_percent_narrower_command_translator_1);
    mutate_global_property(Qtwenty_percent_wider,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qtwenty_percent_wider,list_constant_75,Qnil,
	    Qtwenty_percent_wider,Qnil);
    com_twenty_percent_wider_1 = STATIC_FUNCTION(com_twenty_percent_wider,
	    NIL,FALSE,3,3);
    set_ui_command_function(Qtwenty_percent_wider,com_twenty_percent_wider_1);
    twenty_percent_wider_command_pursuer_1 = 
	    STATIC_FUNCTION(twenty_percent_wider_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qtwenty_percent_wider,
	    twenty_percent_wider_command_pursuer_1);
    twenty_percent_wider_command_translator_1 = 
	    STATIC_FUNCTION(twenty_percent_wider_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtwenty_percent_wider,
	    twenty_percent_wider_command_translator_1);
    mutate_global_property(Qcenter_origin,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qcenter_origin,list_constant_75,Qnil,Qcenter_origin,
	    Qnil);
    com_center_origin_1 = STATIC_FUNCTION(com_center_origin,NIL,FALSE,3,3);
    set_ui_command_function(Qcenter_origin,com_center_origin_1);
    center_origin_command_pursuer_1 = 
	    STATIC_FUNCTION(center_origin_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcenter_origin,center_origin_command_pursuer_1);
    center_origin_command_translator_1 = 
	    STATIC_FUNCTION(center_origin_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qcenter_origin,
	    center_origin_command_translator_1);
    mutate_global_property(Qshift_left_ten_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_left_ten_percent,list_constant_75,Qnil,
	    Qshift_left_ten_percent,Qnil);
    com_shift_left_ten_percent_1 = 
	    STATIC_FUNCTION(com_shift_left_ten_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_left_ten_percent,
	    com_shift_left_ten_percent_1);
    shift_left_ten_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_left_ten_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_left_ten_percent,
	    shift_left_ten_percent_command_pursuer_1);
    shift_left_ten_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_left_ten_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_left_ten_percent,
	    shift_left_ten_percent_command_translator_1);
    mutate_global_property(Qshift_right_ten_percent,T,
	    Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_right_ten_percent,list_constant_75,Qnil,
	    Qshift_right_ten_percent,Qnil);
    com_shift_right_ten_percent_1 = 
	    STATIC_FUNCTION(com_shift_right_ten_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_right_ten_percent,
	    com_shift_right_ten_percent_1);
    shift_right_ten_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_right_ten_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_right_ten_percent,
	    shift_right_ten_percent_command_pursuer_1);
    shift_right_ten_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_right_ten_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_right_ten_percent,
	    shift_right_ten_percent_command_translator_1);
    mutate_global_property(Qshift_left_one_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_left_one_percent,list_constant_75,Qnil,
	    Qshift_left_one_percent,Qnil);
    com_shift_left_one_percent_1 = 
	    STATIC_FUNCTION(com_shift_left_one_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_left_one_percent,
	    com_shift_left_one_percent_1);
    shift_left_one_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_left_one_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_left_one_percent,
	    shift_left_one_percent_command_pursuer_1);
    shift_left_one_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_left_one_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_left_one_percent,
	    shift_left_one_percent_command_translator_1);
    mutate_global_property(Qshift_right_one_percent,T,
	    Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_right_one_percent,list_constant_75,Qnil,
	    Qshift_right_one_percent,Qnil);
    com_shift_right_one_percent_1 = 
	    STATIC_FUNCTION(com_shift_right_one_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_right_one_percent,
	    com_shift_right_one_percent_1);
    shift_right_one_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_right_one_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_right_one_percent,
	    shift_right_one_percent_command_pursuer_1);
    shift_right_one_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_right_one_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_right_one_percent,
	    shift_right_one_percent_command_translator_1);
    mutate_global_property(Qshift_up_ten_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_up_ten_percent,list_constant_75,Qnil,
	    Qshift_up_ten_percent,Qnil);
    com_shift_up_ten_percent_1 = STATIC_FUNCTION(com_shift_up_ten_percent,
	    NIL,FALSE,3,3);
    set_ui_command_function(Qshift_up_ten_percent,com_shift_up_ten_percent_1);
    shift_up_ten_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_up_ten_percent_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qshift_up_ten_percent,
	    shift_up_ten_percent_command_pursuer_1);
    shift_up_ten_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_up_ten_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_up_ten_percent,
	    shift_up_ten_percent_command_translator_1);
    mutate_global_property(Qshift_down_ten_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_down_ten_percent,list_constant_75,Qnil,
	    Qshift_down_ten_percent,Qnil);
    com_shift_down_ten_percent_1 = 
	    STATIC_FUNCTION(com_shift_down_ten_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_down_ten_percent,
	    com_shift_down_ten_percent_1);
    shift_down_ten_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_down_ten_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_down_ten_percent,
	    shift_down_ten_percent_command_pursuer_1);
    shift_down_ten_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_down_ten_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_down_ten_percent,
	    shift_down_ten_percent_command_translator_1);
    mutate_global_property(Qshift_up_one_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_up_one_percent,list_constant_75,Qnil,
	    Qshift_up_one_percent,Qnil);
    com_shift_up_one_percent_1 = STATIC_FUNCTION(com_shift_up_one_percent,
	    NIL,FALSE,3,3);
    set_ui_command_function(Qshift_up_one_percent,com_shift_up_one_percent_1);
    shift_up_one_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_up_one_percent_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qshift_up_one_percent,
	    shift_up_one_percent_command_pursuer_1);
    shift_up_one_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_up_one_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_up_one_percent,
	    shift_up_one_percent_command_translator_1);
    mutate_global_property(Qshift_down_one_percent,T,Qrefreshes_image_plane_p);
    make_ui_command(5,Qshift_down_one_percent,list_constant_75,Qnil,
	    Qshift_down_one_percent,Qnil);
    com_shift_down_one_percent_1 = 
	    STATIC_FUNCTION(com_shift_down_one_percent,NIL,FALSE,3,3);
    set_ui_command_function(Qshift_down_one_percent,
	    com_shift_down_one_percent_1);
    shift_down_one_percent_command_pursuer_1 = 
	    STATIC_FUNCTION(shift_down_one_percent_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshift_down_one_percent,
	    shift_down_one_percent_command_pursuer_1);
    shift_down_one_percent_command_translator_1 = 
	    STATIC_FUNCTION(shift_down_one_percent_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshift_down_one_percent,
	    shift_down_one_percent_command_translator_1);
    Qinspect_history = STATIC_SYMBOL("INSPECT-HISTORY",AB_package);
    Qtable_item = STATIC_SYMBOL("TABLE-ITEM",AB_package);
    if (Global_table_of_attributes_pane == UNBOUND)
	Global_table_of_attributes_pane = Nil;
    if (Global_table_of_hidden_attributes_pane == UNBOUND)
	Global_table_of_hidden_attributes_pane = Nil;
    if (Global_table_of_attributes_pane_pointer == UNBOUND)
	Global_table_of_attributes_pane_pointer = Nil;
    if (Global_table_of_hidden_attributes_pane_pointer == UNBOUND)
	Global_table_of_hidden_attributes_pane_pointer = Nil;
    if (Global_nmsci_id_for_attributes_pane == UNBOUND)
	Global_nmsci_id_for_attributes_pane = Nil;
    if (Global_nmsci_id_for_hidden_attributes_pane == UNBOUND)
	Global_nmsci_id_for_hidden_attributes_pane = Nil;
    if (Global_nms_menu_choiced_item_id == UNBOUND)
	Global_nms_menu_choiced_item_id = Nil;
    Qtable_of_attributes_pane = STATIC_SYMBOL("TABLE-OF-ATTRIBUTES-PANE",
	    AB_package);
    Qmost_interesting_frame = STATIC_SYMBOL("MOST-INTERESTING-FRAME",
	    AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)2L,Qframe,Qmost_interesting_frame);
    list_constant_77 = STATIC_CONS(list_constant_76,list_constant_27);
    string_constant_77 = 
	    STATIC_STRING("Put up the attributes table pane for the selected item.");
    make_ui_command(5,Qtable_of_attributes_pane,list_constant_77,
	    string_constant_77,Qtable_of_attributes_pane,Qnil);
    com_table_of_attributes_pane_1 = 
	    STATIC_FUNCTION(com_table_of_attributes_pane,NIL,FALSE,2,2);
    set_ui_command_function(Qtable_of_attributes_pane,
	    com_table_of_attributes_pane_1);
    table_of_attributes_pane_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_attributes_pane_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_attributes_pane,
	    table_of_attributes_pane_command_pursuer_1);
    table_of_attributes_pane_command_translator_1 = 
	    STATIC_FUNCTION(table_of_attributes_pane_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qtable_of_attributes_pane,
	    table_of_attributes_pane_command_translator_1);
    array_constant_15 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)18L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qtable_of_attributes_pane,array_constant_15,
	    Qmenu_string);
    Qtable_of_hidden_attributes_pane = 
	    STATIC_SYMBOL("TABLE-OF-HIDDEN-ATTRIBUTES-PANE",AB_package);
    string_constant_78 = 
	    STATIC_STRING("Put up the hidden attributes table pane for the selected item.");
    make_ui_command(5,Qtable_of_hidden_attributes_pane,list_constant_77,
	    string_constant_78,Qtable_of_hidden_attributes_pane,Qnil);
    com_table_of_hidden_attributes_pane_1 = 
	    STATIC_FUNCTION(com_table_of_hidden_attributes_pane,NIL,FALSE,2,2);
    set_ui_command_function(Qtable_of_hidden_attributes_pane,
	    com_table_of_hidden_attributes_pane_1);
    table_of_hidden_attributes_pane_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_pane_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_hidden_attributes_pane,
	    table_of_hidden_attributes_pane_command_pursuer_1);
    table_of_hidden_attributes_pane_command_translator_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_pane_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qtable_of_hidden_attributes_pane,
	    table_of_hidden_attributes_pane_command_translator_1);
    array_constant_16 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)31L,(SI_Long)57344L);
    mutate_global_property(Qtable_of_hidden_attributes_pane,
	    array_constant_16,Qmenu_string);
    Qupdate_table_of_attributes_pane = 
	    STATIC_SYMBOL("UPDATE-TABLE-OF-ATTRIBUTES-PANE",AB_package);
    Qupdate_table_of_hidden_attributes_pane = 
	    STATIC_SYMBOL("UPDATE-TABLE-OF-HIDDEN-ATTRIBUTES-PANE",AB_package);
    Qg2_property_grid = STATIC_SYMBOL("G2-PROPERTY-GRID",AB_package);
    Qdestroy = STATIC_SYMBOL("DESTROY",AB_package);
    Qcontents = STATIC_SYMBOL("CONTENTS",AB_package);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    Qproperty_user_callback_func = 
	    STATIC_SYMBOL("PROPERTY-USER-CALLBACK-FUNC",AB_package);
    array_constant = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    make_ui_command(5,Qupdate_table_of_attributes_pane,list_constant_77,
	    Qnil,Qupdate_table_of_attributes_pane,Qnil);
    com_update_table_of_attributes_pane_1 = 
	    STATIC_FUNCTION(com_update_table_of_attributes_pane,NIL,FALSE,2,2);
    set_ui_command_function(Qupdate_table_of_attributes_pane,
	    com_update_table_of_attributes_pane_1);
    update_table_of_attributes_pane_command_pursuer_1 = 
	    STATIC_FUNCTION(update_table_of_attributes_pane_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qupdate_table_of_attributes_pane,
	    update_table_of_attributes_pane_command_pursuer_1);
    update_table_of_attributes_pane_command_translator_1 = 
	    STATIC_FUNCTION(update_table_of_attributes_pane_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qupdate_table_of_attributes_pane,
	    update_table_of_attributes_pane_command_translator_1);
    make_ui_command(5,Qupdate_table_of_hidden_attributes_pane,
	    list_constant_77,Qnil,Qupdate_table_of_hidden_attributes_pane,
	    Qnil);
    com_update_table_of_hidden_attributes_pane_1 = 
	    STATIC_FUNCTION(com_update_table_of_hidden_attributes_pane,NIL,
	    FALSE,2,2);
    set_ui_command_function(Qupdate_table_of_hidden_attributes_pane,
	    com_update_table_of_hidden_attributes_pane_1);
    update_table_of_hidden_attributes_pane_command_pursuer_1 = 
	    STATIC_FUNCTION(update_table_of_hidden_attributes_pane_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qupdate_table_of_hidden_attributes_pane,
	    update_table_of_hidden_attributes_pane_command_pursuer_1);
    update_table_of_hidden_attributes_pane_command_translator_1 = 
	    STATIC_FUNCTION(update_table_of_hidden_attributes_pane_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qupdate_table_of_hidden_attributes_pane,
	    update_table_of_hidden_attributes_pane_command_translator_1);
    Qpopulate = STATIC_SYMBOL("POPULATE",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_table_of_attributes_pane,
	    STATIC_FUNCTION(update_table_of_attributes_pane,NIL,FALSE,2,2));
    SET_SYMBOL_FUNCTION(Qupdate_table_of_hidden_attributes_pane,
	    STATIC_FUNCTION(update_table_of_hidden_attributes_pane,NIL,
	    FALSE,2,2));
    Qfunc = STATIC_SYMBOL("FUNC",AB_package);
    Qflag = STATIC_SYMBOL("FLAG",AB_package);
    Qproperty = STATIC_SYMBOL("PROPERTY",AB_package);
    Qcurrent_value = STATIC_SYMBOL("CURRENT-VALUE",AB_package);
    Qedit_in_place = STATIC_SYMBOL("EDIT-IN-PLACE",AB_package);
    Qslot_name = STATIC_SYMBOL("SLOT-NAME",AB_package);
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    Qexecute = STATIC_SYMBOL("EXECUTE",AB_package);
    Qvirtual = STATIC_SYMBOL("VIRTUAL",AB_package);
    Qeditable = STATIC_SYMBOL("EDITABLE",AB_package);
    list_constant_78 = STATIC_CONS(list_constant_76,list_constant_21);
    string_constant_79 = 
	    STATIC_STRING("Put up the attributes table for the selected item.");
    make_ui_command(5,Qtable,list_constant_78,string_constant_79,Qtable,Qnil);
    com_table_1 = STATIC_FUNCTION(com_table,NIL,FALSE,3,3);
    set_ui_command_function(Qtable,com_table_1);
    table_command_pursuer_1 = STATIC_FUNCTION(table_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtable,table_command_pursuer_1);
    table_command_translator_1 = STATIC_FUNCTION(table_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qtable,table_command_translator_1);
    Qtable_of_item = STATIC_SYMBOL("TABLE-OF-ITEM",AB_package);
    make_ui_command(5,Qtable_of_item,list_constant_78,string_constant_79,
	    Qtable,Qnil);
    com_table_of_item_1 = STATIC_FUNCTION(com_table_of_item,NIL,FALSE,3,3);
    set_ui_command_function(Qtable_of_item,com_table_of_item_1);
    table_of_item_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_item_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_item,table_of_item_command_pursuer_1);
    table_of_item_command_translator_1 = 
	    STATIC_FUNCTION(table_of_item_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qtable_of_item,
	    table_of_item_command_translator_1);
    Qtable_of_workspace = STATIC_SYMBOL("TABLE-OF-WORKSPACE",AB_package);
    list_constant_79 = STATIC_CONS(Qworkspace,list_constant_21);
    string_constant_80 = 
	    STATIC_STRING("Put up the attributes table for the selected workspace.");
    make_ui_command(5,Qtable_of_workspace,list_constant_79,
	    string_constant_80,Qtable,Qnil);
    com_table_of_workspace_1 = STATIC_FUNCTION(com_table_of_workspace,NIL,
	    FALSE,3,3);
    set_ui_command_function(Qtable_of_workspace,com_table_of_workspace_1);
    table_of_workspace_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_workspace_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_workspace,
	    table_of_workspace_command_pursuer_1);
    table_of_workspace_command_translator_1 = 
	    STATIC_FUNCTION(table_of_workspace_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qtable_of_workspace,
	    table_of_workspace_command_translator_1);
    make_ui_command(5,Qtable_of_hidden_attributes,list_constant_78,Qnil,
	    Qtable_of_hidden_attributes,Qnil);
    com_table_of_hidden_attributes_1 = 
	    STATIC_FUNCTION(com_table_of_hidden_attributes,NIL,FALSE,3,3);
    set_ui_command_function(Qtable_of_hidden_attributes,
	    com_table_of_hidden_attributes_1);
    table_of_hidden_attributes_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_hidden_attributes,
	    table_of_hidden_attributes_command_pursuer_1);
    table_of_hidden_attributes_command_translator_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qtable_of_hidden_attributes,
	    table_of_hidden_attributes_command_translator_1);
    Qtable_of_hidden_attributes_of_item = 
	    STATIC_SYMBOL("TABLE-OF-HIDDEN-ATTRIBUTES-OF-ITEM",AB_package);
    make_ui_command(5,Qtable_of_hidden_attributes_of_item,list_constant_78,
	    Qnil,Qtable_of_hidden_attributes,Qnil);
    com_table_of_hidden_attributes_of_item_1 = 
	    STATIC_FUNCTION(com_table_of_hidden_attributes_of_item,NIL,
	    FALSE,3,3);
    set_ui_command_function(Qtable_of_hidden_attributes_of_item,
	    com_table_of_hidden_attributes_of_item_1);
    table_of_hidden_attributes_of_item_command_pursuer_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_of_item_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qtable_of_hidden_attributes_of_item,
	    table_of_hidden_attributes_of_item_command_pursuer_1);
    table_of_hidden_attributes_of_item_command_translator_1 = 
	    STATIC_FUNCTION(table_of_hidden_attributes_of_item_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qtable_of_hidden_attributes_of_item,
	    table_of_hidden_attributes_of_item_command_translator_1);
    string_constant_81 = 
	    STATIC_STRING("Shows the attributes that have changed since the last save of an permanent G2 item.");
    make_ui_command(5,Qshow_unsaved_attributes,list_constant_78,
	    string_constant_81,Qshow_unsaved_attributes,Qnil);
    Qattributes_permamently_changed = 
	    STATIC_SYMBOL("ATTRIBUTES-PERMAMENTLY-CHANGED",AB_package);
    com_show_unsaved_attributes_1 = 
	    STATIC_FUNCTION(com_show_unsaved_attributes,NIL,FALSE,3,3);
    set_ui_command_function(Qshow_unsaved_attributes,
	    com_show_unsaved_attributes_1);
    show_unsaved_attributes_command_pursuer_1 = 
	    STATIC_FUNCTION(show_unsaved_attributes_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qshow_unsaved_attributes,
	    show_unsaved_attributes_command_pursuer_1);
    show_unsaved_attributes_command_translator_1 = 
	    STATIC_FUNCTION(show_unsaved_attributes_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qshow_unsaved_attributes,
	    show_unsaved_attributes_command_translator_1);
    Qshrink_wrap = STATIC_SYMBOL("SHRINK-WRAP",AB_package);
    list_constant_80 = STATIC_CONS(Qworkspace,Qnil);
    string_constant_82 = 
	    STATIC_STRING("Shrink this workspace until just large enough to enclose all of its subblocks.");
    make_ui_command(5,Qshrink_wrap,list_constant_80,string_constant_82,
	    Qshrink_wrap,Qnil);
    com_shrink_wrap_1 = STATIC_FUNCTION(com_shrink_wrap,NIL,FALSE,1,1);
    set_ui_command_function(Qshrink_wrap,com_shrink_wrap_1);
    shrink_wrap_command_pursuer_1 = 
	    STATIC_FUNCTION(shrink_wrap_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qshrink_wrap,shrink_wrap_command_pursuer_1);
    shrink_wrap_command_translator_1 = 
	    STATIC_FUNCTION(shrink_wrap_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qshrink_wrap,shrink_wrap_command_translator_1);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    list_constant_81 = STATIC_CONS(Qblock,Qnil);
    string_constant_83 = 
	    STATIC_STRING("Edit the name of this object, if it allows one.");
    make_ui_command(5,Qname,list_constant_81,string_constant_83,Qname,Qnil);
    com_name_1 = STATIC_FUNCTION(com_name,NIL,FALSE,1,1);
    set_ui_command_function(Qname,com_name_1);
    name_command_pursuer_1 = STATIC_FUNCTION(name_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qname,name_command_pursuer_1);
    name_command_translator_1 = STATIC_FUNCTION(name_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qname,name_command_translator_1);
    Qname_item = STATIC_SYMBOL("NAME-ITEM",AB_package);
    make_ui_command(5,Qname_item,list_constant_81,string_constant_83,Qname,
	    Qnil);
    com_name_item_1 = STATIC_FUNCTION(com_name_item,NIL,FALSE,1,1);
    set_ui_command_function(Qname_item,com_name_item_1);
    name_item_command_pursuer_1 = 
	    STATIC_FUNCTION(name_item_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qname_item,name_item_command_pursuer_1);
    name_item_command_translator_1 = 
	    STATIC_FUNCTION(name_item_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qname_item,name_item_command_translator_1);
    Qmark_to_strip_text = STATIC_SYMBOL("MARK-TO-STRIP-TEXT",AB_package);
    list_constant_82 = STATIC_CONS(Qitem,Qnil);
    make_ui_command(5,Qmark_to_strip_text,list_constant_82,Qnil,
	    Qmark_to_strip_text,Qnil);
    com_mark_to_strip_text_1 = STATIC_FUNCTION(com_mark_to_strip_text,NIL,
	    FALSE,1,1);
    set_ui_command_function(Qmark_to_strip_text,com_mark_to_strip_text_1);
    mark_to_strip_text_command_pursuer_1 = 
	    STATIC_FUNCTION(mark_to_strip_text_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qmark_to_strip_text,
	    mark_to_strip_text_command_pursuer_1);
    mark_to_strip_text_command_translator_1 = 
	    STATIC_FUNCTION(mark_to_strip_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qmark_to_strip_text,
	    mark_to_strip_text_command_translator_1);
    Qmark_to_strip_text_star = STATIC_SYMBOL("MARK-TO-STRIP-TEXT-*",
	    AB_package);
    make_ui_command(5,Qmark_to_strip_text_star,list_constant_82,Qnil,
	    Qmark_to_strip_text_star,Qnil);
    com_mark_to_strip_text_star_1 = 
	    STATIC_FUNCTION(com_mark_to_strip_text_star,NIL,FALSE,1,1);
    set_ui_command_function(Qmark_to_strip_text_star,
	    com_mark_to_strip_text_star_1);
    mark_to_strip_text_star_command_pursuer_1 = 
	    STATIC_FUNCTION(mark_to_strip_text_star_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qmark_to_strip_text_star,
	    mark_to_strip_text_star_command_pursuer_1);
    mark_to_strip_text_star_command_translator_1 = 
	    STATIC_FUNCTION(mark_to_strip_text_star_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qmark_to_strip_text_star,
	    mark_to_strip_text_star_command_translator_1);
    Qremove_strip_text_mark = STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK",
	    AB_package);
    make_ui_command(5,Qremove_strip_text_mark,list_constant_82,Qnil,
	    Qremove_strip_text_mark,Qnil);
    com_remove_strip_text_mark_1 = 
	    STATIC_FUNCTION(com_remove_strip_text_mark,NIL,FALSE,1,1);
    set_ui_command_function(Qremove_strip_text_mark,
	    com_remove_strip_text_mark_1);
    remove_strip_text_mark_command_pursuer_1 = 
	    STATIC_FUNCTION(remove_strip_text_mark_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qremove_strip_text_mark,
	    remove_strip_text_mark_command_pursuer_1);
    remove_strip_text_mark_command_translator_1 = 
	    STATIC_FUNCTION(remove_strip_text_mark_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qremove_strip_text_mark,
	    remove_strip_text_mark_command_translator_1);
    Qremove_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-STRIP-TEXT-MARK-*",AB_package);
    make_ui_command(5,Qremove_strip_text_mark_star,list_constant_82,Qnil,
	    Qremove_strip_text_mark_star,Qnil);
    com_remove_strip_text_mark_star_1 = 
	    STATIC_FUNCTION(com_remove_strip_text_mark_star,NIL,FALSE,1,1);
    set_ui_command_function(Qremove_strip_text_mark_star,
	    com_remove_strip_text_mark_star_1);
    remove_strip_text_mark_star_command_pursuer_1 = 
	    STATIC_FUNCTION(remove_strip_text_mark_star_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qremove_strip_text_mark_star,
	    remove_strip_text_mark_star_command_pursuer_1);
    remove_strip_text_mark_star_command_translator_1 = 
	    STATIC_FUNCTION(remove_strip_text_mark_star_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qremove_strip_text_mark_star,
	    remove_strip_text_mark_star_command_translator_1);
    Qmark_not_to_strip_text_star = 
	    STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT-*",AB_package);
    make_ui_command(5,Qmark_not_to_strip_text_star,list_constant_82,Qnil,
	    Qmark_not_to_strip_text_star,Qnil);
    com_mark_not_to_strip_text_star_1 = 
	    STATIC_FUNCTION(com_mark_not_to_strip_text_star,NIL,FALSE,1,1);
    set_ui_command_function(Qmark_not_to_strip_text_star,
	    com_mark_not_to_strip_text_star_1);
    mark_not_to_strip_text_star_command_pursuer_1 = 
	    STATIC_FUNCTION(mark_not_to_strip_text_star_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qmark_not_to_strip_text_star,
	    mark_not_to_strip_text_star_command_pursuer_1);
    mark_not_to_strip_text_star_command_translator_1 = 
	    STATIC_FUNCTION(mark_not_to_strip_text_star_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qmark_not_to_strip_text_star,
	    mark_not_to_strip_text_star_command_translator_1);
    Qmark_not_to_strip_text = STATIC_SYMBOL("MARK-NOT-TO-STRIP-TEXT",
	    AB_package);
    make_ui_command(5,Qmark_not_to_strip_text,list_constant_82,Qnil,
	    Qmark_not_to_strip_text,Qnil);
    com_mark_not_to_strip_text_1 = 
	    STATIC_FUNCTION(com_mark_not_to_strip_text,NIL,FALSE,1,1);
    set_ui_command_function(Qmark_not_to_strip_text,
	    com_mark_not_to_strip_text_1);
    mark_not_to_strip_text_command_pursuer_1 = 
	    STATIC_FUNCTION(mark_not_to_strip_text_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qmark_not_to_strip_text,
	    mark_not_to_strip_text_command_pursuer_1);
    mark_not_to_strip_text_command_translator_1 = 
	    STATIC_FUNCTION(mark_not_to_strip_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qmark_not_to_strip_text,
	    mark_not_to_strip_text_command_translator_1);
    Qremove_do_not_strip_text_mark_star = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK-*",AB_package);
    make_ui_command(5,Qremove_do_not_strip_text_mark_star,list_constant_82,
	    Qnil,Qremove_do_not_strip_text_mark_star,Qnil);
    com_remove_do_not_strip_text_mark_star_1 = 
	    STATIC_FUNCTION(com_remove_do_not_strip_text_mark_star,NIL,
	    FALSE,1,1);
    set_ui_command_function(Qremove_do_not_strip_text_mark_star,
	    com_remove_do_not_strip_text_mark_star_1);
    remove_do_not_strip_text_mark_star_command_pursuer_1 = 
	    STATIC_FUNCTION(remove_do_not_strip_text_mark_star_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qremove_do_not_strip_text_mark_star,
	    remove_do_not_strip_text_mark_star_command_pursuer_1);
    remove_do_not_strip_text_mark_star_command_translator_1 = 
	    STATIC_FUNCTION(remove_do_not_strip_text_mark_star_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qremove_do_not_strip_text_mark_star,
	    remove_do_not_strip_text_mark_star_command_translator_1);
    Qremove_do_not_strip_text_mark = 
	    STATIC_SYMBOL("REMOVE-DO-NOT-STRIP-TEXT-MARK",AB_package);
    make_ui_command(5,Qremove_do_not_strip_text_mark,list_constant_82,Qnil,
	    Qremove_do_not_strip_text_mark,Qnil);
    com_remove_do_not_strip_text_mark_1 = 
	    STATIC_FUNCTION(com_remove_do_not_strip_text_mark,NIL,FALSE,1,1);
    set_ui_command_function(Qremove_do_not_strip_text_mark,
	    com_remove_do_not_strip_text_mark_1);
    remove_do_not_strip_text_mark_command_pursuer_1 = 
	    STATIC_FUNCTION(remove_do_not_strip_text_mark_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qremove_do_not_strip_text_mark,
	    remove_do_not_strip_text_mark_command_pursuer_1);
    remove_do_not_strip_text_mark_command_translator_1 = 
	    STATIC_FUNCTION(remove_do_not_strip_text_mark_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qremove_do_not_strip_text_mark,
	    remove_do_not_strip_text_mark_command_translator_1);
    Qedit_expression_of_readout_table = 
	    STATIC_SYMBOL("EDIT-EXPRESSION-OF-READOUT-TABLE",AB_package);
    Qreadout_table = STATIC_SYMBOL("READOUT-TABLE",AB_package);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qreadout_table,Qreadout_table);
    list_constant_84 = STATIC_LIST((SI_Long)2L,Qslot_name,Qslot_name);
    list_constant_85 = STATIC_LIST((SI_Long)2L,list_constant_83,
	    list_constant_84);
    make_ui_command(5,Qedit_expression_of_readout_table,list_constant_85,
	    Qnil,Qedit,Qnil);
    Qexpressions_to_display = STATIC_SYMBOL("EXPRESSIONS-TO-DISPLAY",
	    AB_package);
    com_edit_expression_of_readout_table_1 = 
	    STATIC_FUNCTION(com_edit_expression_of_readout_table,NIL,FALSE,
	    2,2);
    set_ui_command_function(Qedit_expression_of_readout_table,
	    com_edit_expression_of_readout_table_1);
    edit_expression_of_readout_table_command_pursuer_1 = 
	    STATIC_FUNCTION(edit_expression_of_readout_table_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qedit_expression_of_readout_table,
	    edit_expression_of_readout_table_command_pursuer_1);
    edit_expression_of_readout_table_command_translator_1 = 
	    STATIC_FUNCTION(edit_expression_of_readout_table_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qedit_expression_of_readout_table,
	    edit_expression_of_readout_table_command_translator_1);
    Qhide_name = STATIC_SYMBOL("HIDE-NAME",AB_package);
    Qname_box = STATIC_SYMBOL("NAME-BOX",AB_package);
    list_constant_86 = STATIC_LIST((SI_Long)2L,Qblock,Qname_box);
    list_constant_87 = STATIC_CONS(list_constant_86,Qnil);
    make_ui_command(5,Qhide_name,list_constant_87,Qnil,Qhide_name,Qnil);
    com_hide_name_1 = STATIC_FUNCTION(com_hide_name,NIL,FALSE,1,1);
    set_ui_command_function(Qhide_name,com_hide_name_1);
    hide_name_command_pursuer_1 = 
	    STATIC_FUNCTION(hide_name_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qhide_name,hide_name_command_pursuer_1);
    hide_name_command_translator_1 = 
	    STATIC_FUNCTION(hide_name_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qhide_name,hide_name_command_translator_1);
    Qmain_menu = STATIC_SYMBOL("MAIN-MENU",AB_package);
    make_ui_command(5,Qmain_menu,Qnil,Qnil,Qmain_menu,Qnil);
    Qshort_main_menu = STATIC_SYMBOL("SHORT-MAIN-MENU",AB_package);
    com_main_menu_1 = STATIC_FUNCTION(com_main_menu,NIL,FALSE,0,0);
    set_ui_command_function(Qmain_menu,com_main_menu_1);
    set_ui_command_pursuer(Qmain_menu,Qempty_command_pursuer);
    main_menu_command_translator_1 = 
	    STATIC_FUNCTION(main_menu_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qmain_menu,main_menu_command_translator_1);
    Qload_merge_save = STATIC_SYMBOL("LOAD-MERGE-SAVE",AB_package);
    make_ui_command(5,Qload_merge_save,Qnil,Qnil,Qload_merge_save,Qnil);
    com_load_merge_save_1 = STATIC_FUNCTION(com_load_merge_save,NIL,FALSE,0,0);
    set_ui_command_function(Qload_merge_save,com_load_merge_save_1);
    set_ui_command_pursuer(Qload_merge_save,Qempty_command_pursuer);
    load_merge_save_command_translator_1 = 
	    STATIC_FUNCTION(load_merge_save_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qload_merge_save,
	    load_merge_save_command_translator_1);
    Qrun_options = STATIC_SYMBOL("RUN-OPTIONS",AB_package);
    make_ui_command(5,Qrun_options,Qnil,Qnil,Qrun_options,Qnil);
    com_run_options_1 = STATIC_FUNCTION(com_run_options,NIL,FALSE,0,0);
    set_ui_command_function(Qrun_options,com_run_options_1);
    set_ui_command_pursuer(Qrun_options,Qempty_command_pursuer);
    run_options_command_translator_1 = 
	    STATIC_FUNCTION(run_options_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qrun_options,run_options_command_translator_1);
    Qmiscellany = STATIC_SYMBOL("MISCELLANY",AB_package);
    Qmouse_pointer = STATIC_SYMBOL("MOUSE-POINTER",AB_package);
    list_constant_88 = STATIC_CONS(Qmouse_pointer,Qnil);
    make_ui_command(5,Qmiscellany,list_constant_88,Qnil,Qmiscellany,Qnil);
    Qworkspace_menu = STATIC_SYMBOL("WORKSPACE-MENU",AB_package);
    Qworkspace_miscellany = STATIC_SYMBOL("WORKSPACE-MISCELLANY",AB_package);
    Qshort_miscellany_menu = STATIC_SYMBOL("SHORT-MISCELLANY-MENU",AB_package);
    Qmiscellany_menu = STATIC_SYMBOL("MISCELLANY-MENU",AB_package);
    com_miscellany_1 = STATIC_FUNCTION(com_miscellany,NIL,FALSE,1,1);
    set_ui_command_function(Qmiscellany,com_miscellany_1);
    miscellany_command_pursuer_1 = 
	    STATIC_FUNCTION(miscellany_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qmiscellany,miscellany_command_pursuer_1);
    miscellany_command_translator_1 = 
	    STATIC_FUNCTION(miscellany_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qmiscellany,miscellany_command_translator_1);
    Qother_edits = STATIC_SYMBOL("OTHER-EDITS",AB_package);
    make_ui_command(5,Qother_edits,list_constant_88,Qnil,Qother_edits,Qnil);
    com_other_edits_1 = STATIC_FUNCTION(com_other_edits,NIL,FALSE,1,1);
    set_ui_command_function(Qother_edits,com_other_edits_1);
    other_edits_command_pursuer_1 = 
	    STATIC_FUNCTION(other_edits_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qother_edits,other_edits_command_pursuer_1);
    other_edits_command_translator_1 = 
	    STATIC_FUNCTION(other_edits_command_translator,NIL,FALSE,1,1);
    set_ui_command_translator(Qother_edits,other_edits_command_translator_1);
    Qcut_selected_text = STATIC_SYMBOL("CUT-SELECTED-TEXT",AB_package);
    Qtext_region = STATIC_SYMBOL("TEXT-REGION",AB_package);
    Qblock_of_selection_focus = STATIC_SYMBOL("BLOCK-OF-SELECTION-FOCUS",
	    AB_package);
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qtext_region,
	    Qblock_of_selection_focus);
    Qedit_context = STATIC_SYMBOL("EDIT-CONTEXT",AB_package);
    Qworkstation_context_specifics = 
	    STATIC_SYMBOL("WORKSTATION-CONTEXT-SPECIFICS",AB_package);
    list_constant_90 = STATIC_LIST((SI_Long)2L,Qedit_context,
	    Qworkstation_context_specifics);
    list_constant_91 = STATIC_LIST((SI_Long)2L,list_constant_89,
	    list_constant_90);
    string_constant_84 = 
	    STATIC_STRING("Cut the selected text and place it on the clipboard.");
    Qcut = STATIC_SYMBOL("CUT",AB_package);
    make_ui_command(5,Qcut_selected_text,list_constant_91,
	    string_constant_84,Qcut,Qnil);
    com_cut_selected_text_1 = STATIC_FUNCTION(com_cut_selected_text,NIL,
	    FALSE,2,2);
    set_ui_command_function(Qcut_selected_text,com_cut_selected_text_1);
    cut_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(cut_selected_text_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcut_selected_text,
	    cut_selected_text_command_pursuer_1);
    cut_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(cut_selected_text_command_translator,NIL,FALSE,
	    1,1);
    set_ui_command_translator(Qcut_selected_text,
	    cut_selected_text_command_translator_1);
    Qcopy_selected_text = STATIC_SYMBOL("COPY-SELECTED-TEXT",AB_package);
    string_constant_85 = 
	    STATIC_STRING("Copy the selected text to the clipboard.");
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    make_ui_command(5,Qcopy_selected_text,list_constant_91,
	    string_constant_85,Qcopy,Qnil);
    com_copy_selected_text_1 = STATIC_FUNCTION(com_copy_selected_text,NIL,
	    FALSE,2,2);
    set_ui_command_function(Qcopy_selected_text,com_copy_selected_text_1);
    copy_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(copy_selected_text_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcopy_selected_text,
	    copy_selected_text_command_pursuer_1);
    copy_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(copy_selected_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qcopy_selected_text,
	    copy_selected_text_command_translator_1);
    Qpaste_over_selected_text = STATIC_SYMBOL("PASTE-OVER-SELECTED-TEXT",
	    AB_package);
    string_constant_86 = 
	    STATIC_STRING("Paste the clipboard, replacing and discarding the selected text.");
    Qpaste = STATIC_SYMBOL("PASTE",AB_package);
    make_ui_command(5,Qpaste_over_selected_text,list_constant_91,
	    string_constant_86,Qpaste,Qnil);
    Qpending_delete_type_in = STATIC_SYMBOL("PENDING-DELETE-TYPE-IN",
	    AB_package);
    com_paste_over_selected_text_1 = 
	    STATIC_FUNCTION(com_paste_over_selected_text,NIL,FALSE,2,2);
    set_ui_command_function(Qpaste_over_selected_text,
	    com_paste_over_selected_text_1);
    paste_over_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(paste_over_selected_text_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qpaste_over_selected_text,
	    paste_over_selected_text_command_pursuer_1);
    paste_over_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(paste_over_selected_text_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qpaste_over_selected_text,
	    paste_over_selected_text_command_translator_1);
    Qdelete_selected_text = STATIC_SYMBOL("DELETE-SELECTED-TEXT",AB_package);
    string_constant_87 = 
	    STATIC_STRING("Delete the selected text, and discard it.");
    make_ui_command(5,Qdelete_selected_text,list_constant_91,
	    string_constant_87,Qdelete,Qnil);
    com_delete_selected_text_1 = STATIC_FUNCTION(com_delete_selected_text,
	    NIL,FALSE,2,2);
    set_ui_command_function(Qdelete_selected_text,com_delete_selected_text_1);
    delete_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(delete_selected_text_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qdelete_selected_text,
	    delete_selected_text_command_pursuer_1);
    delete_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(delete_selected_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qdelete_selected_text,
	    delete_selected_text_command_translator_1);
    Qinsert_selected_text = STATIC_SYMBOL("INSERT-SELECTED-TEXT",AB_package);
    string_constant_88 = 
	    STATIC_STRING("Insert the selected text at the cursor location.");
    Qinsert = STATIC_SYMBOL("INSERT",AB_package);
    make_ui_command(5,Qinsert_selected_text,list_constant_91,
	    string_constant_88,Qinsert,Qnil);
    com_insert_selected_text_1 = STATIC_FUNCTION(com_insert_selected_text,
	    NIL,FALSE,2,2);
    set_ui_command_function(Qinsert_selected_text,com_insert_selected_text_1);
    insert_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(insert_selected_text_command_pursuer,NIL,FALSE,
	    1,1);
    set_ui_command_pursuer(Qinsert_selected_text,
	    insert_selected_text_command_pursuer_1);
    insert_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(insert_selected_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qinsert_selected_text,
	    insert_selected_text_command_translator_1);
    Qcopy_and_insert_selected_text = 
	    STATIC_SYMBOL("COPY-AND-INSERT-SELECTED-TEXT",AB_package);
    string_constant_89 = 
	    STATIC_STRING("Copy the selected text and insert it at the cursor location.");
    Qcopy_and_insert = STATIC_SYMBOL("COPY-AND-INSERT",AB_package);
    make_ui_command(5,Qcopy_and_insert_selected_text,list_constant_91,
	    string_constant_89,Qcopy_and_insert,Qnil);
    com_copy_and_insert_selected_text_1 = 
	    STATIC_FUNCTION(com_copy_and_insert_selected_text,NIL,FALSE,2,2);
    set_ui_command_function(Qcopy_and_insert_selected_text,
	    com_copy_and_insert_selected_text_1);
    copy_and_insert_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(copy_and_insert_selected_text_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcopy_and_insert_selected_text,
	    copy_and_insert_selected_text_command_pursuer_1);
    copy_and_insert_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(copy_and_insert_selected_text_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qcopy_and_insert_selected_text,
	    copy_and_insert_selected_text_command_translator_1);
    array_constant_17 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qcopy_and_insert,array_constant_17,Qmenu_string);
    Qmove_selected_text = STATIC_SYMBOL("MOVE-SELECTED-TEXT",AB_package);
    string_constant_90 = 
	    STATIC_STRING("Move the selected text to the cursor location.");
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    make_ui_command(5,Qmove_selected_text,list_constant_91,
	    string_constant_90,Qmove,Qnil);
    com_move_selected_text_1 = STATIC_FUNCTION(com_move_selected_text,NIL,
	    FALSE,2,2);
    set_ui_command_function(Qmove_selected_text,com_move_selected_text_1);
    move_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(move_selected_text_command_pursuer,NIL,FALSE,1,1);
    set_ui_command_pursuer(Qmove_selected_text,
	    move_selected_text_command_pursuer_1);
    move_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(move_selected_text_command_translator,NIL,
	    FALSE,1,1);
    set_ui_command_translator(Qmove_selected_text,
	    move_selected_text_command_translator_1);
    Qcut_and_insert_selected_text = 
	    STATIC_SYMBOL("CUT-AND-INSERT-SELECTED-TEXT",AB_package);
    string_constant_91 = 
	    STATIC_STRING("Cut the selected text, place it on the clipboard, and insert it at the cursor.");
    Qcut_and_insert = STATIC_SYMBOL("CUT-AND-INSERT",AB_package);
    make_ui_command(5,Qcut_and_insert_selected_text,list_constant_91,
	    string_constant_91,Qcut_and_insert,Qnil);
    com_cut_and_insert_selected_text_1 = 
	    STATIC_FUNCTION(com_cut_and_insert_selected_text,NIL,FALSE,2,2);
    set_ui_command_function(Qcut_and_insert_selected_text,
	    com_cut_and_insert_selected_text_1);
    cut_and_insert_selected_text_command_pursuer_1 = 
	    STATIC_FUNCTION(cut_and_insert_selected_text_command_pursuer,
	    NIL,FALSE,1,1);
    set_ui_command_pursuer(Qcut_and_insert_selected_text,
	    cut_and_insert_selected_text_command_pursuer_1);
    cut_and_insert_selected_text_command_translator_1 = 
	    STATIC_FUNCTION(cut_and_insert_selected_text_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qcut_and_insert_selected_text,
	    cut_and_insert_selected_text_command_translator_1);
    array_constant_18 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qcut_and_insert,array_constant_18,Qmenu_string);
    list_constant_92 = STATIC_CONS(list_constant_90,Qnil);
    string_constant_92 = 
	    STATIC_STRING("Paste the clipboard contents at the cursor location.");
    make_ui_command(5,Qpaste,list_constant_92,string_constant_92,Qpaste,Qnil);
    com_paste_1 = STATIC_FUNCTION(com_paste,NIL,FALSE,1,1);
    set_ui_command_function(Qpaste,com_paste_1);
    paste_command_pursuer_1 = STATIC_FUNCTION(paste_command_pursuer,NIL,
	    FALSE,1,1);
    set_ui_command_pursuer(Qpaste,paste_command_pursuer_1);
    paste_command_translator_1 = STATIC_FUNCTION(paste_command_translator,
	    NIL,FALSE,1,1);
    set_ui_command_translator(Qpaste,paste_command_translator_1);
    Qeditor_text_marking_menu = STATIC_SYMBOL("EDITOR-TEXT-MARKING-MENU",
	    AB_package);
    array_constant_19 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    mutate_global_property(Qeditor_text_marking_menu,array_constant_19,
	    Qmenu_string);
    Qcommand_menu = STATIC_SYMBOL("COMMAND-MENU",AB_package);
    string_constant_93 = 
	    STATIC_STRING("1r83-Pdy83-Ohy83-iYy83-Qny83-a8y83-foy83-Pcy");
    make_menu_description(Qeditor_text_marking_menu,Qnil,Qnil,
	    Qeditor_text_marking_menu,Qnil,Qnil,Qt,Qnil,Qt,Nil,Nil,Qnil,
	    Qnil,Qnil,Qcommand_menu,
	    regenerate_optimized_constant(string_constant_93));
    Qg2_defstruct_structure_name_category_for_token_g2_struct = 
	    STATIC_SYMBOL("CATEGORY-FOR-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    if (Alternate_symbols_for_translation == UNBOUND)
	Alternate_symbols_for_translation = Nil;
    Qok = STATIC_SYMBOL("OK",AB_package);
    array_constant_20 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    mutate_global_property(Qok,array_constant_20,Qmenu_string);
    Qws_visible = STATIC_SYMBOL("WS-VISIBLE",AB_package);
    Qds_modalframe = STATIC_SYMBOL("DS-MODALFRAME",AB_package);
    list_constant_93 = STATIC_LIST_STAR((SI_Long)3L,Qds_modalframe,
	    FIX((SI_Long)0L),FIX((SI_Long)128L));
    Qds_nofailcreate = STATIC_SYMBOL("DS-NOFAILCREATE",AB_package);
    list_constant_94 = STATIC_LIST_STAR((SI_Long)3L,Qds_nofailcreate,
	    FIX((SI_Long)0L),FIX((SI_Long)16L));
    Qds_noidlemsg = STATIC_SYMBOL("DS-NOIDLEMSG",AB_package);
    list_constant_95 = STATIC_LIST_STAR((SI_Long)3L,Qds_noidlemsg,
	    FIX((SI_Long)0L),FIX((SI_Long)256L));
    Qds_setfont = STATIC_SYMBOL("DS-SETFONT",AB_package);
    list_constant_96 = STATIC_LIST_STAR((SI_Long)3L,Qds_setfont,
	    FIX((SI_Long)0L),FIX((SI_Long)64L));
    Qds_setforeground = STATIC_SYMBOL("DS-SETFOREGROUND",AB_package);
    list_constant_97 = STATIC_LIST_STAR((SI_Long)3L,Qds_setforeground,
	    FIX((SI_Long)0L),FIX((SI_Long)512L));
    Qds_sysmodal = STATIC_SYMBOL("DS-SYSMODAL",AB_package);
    list_constant_98 = STATIC_LIST_STAR((SI_Long)3L,Qds_sysmodal,
	    FIX((SI_Long)0L),FIX((SI_Long)2L));
    list_constant_9 = STATIC_LIST((SI_Long)6L,list_constant_93,
	    list_constant_94,list_constant_95,list_constant_96,
	    list_constant_97,list_constant_98);
    list_constant_10 = STATIC_CONS(FIX((SI_Long)0L),FIX((SI_Long)0L));
    Qidok = STATIC_SYMBOL("IDOK",AB_package);
    Qidcancel = STATIC_SYMBOL("IDCANCEL",AB_package);
    Qidabort = STATIC_SYMBOL("IDABORT",AB_package);
    Qidretry = STATIC_SYMBOL("IDRETRY",AB_package);
    Qidignore = STATIC_SYMBOL("IDIGNORE",AB_package);
    Qidyes = STATIC_SYMBOL("IDYES",AB_package);
    Qidno = STATIC_SYMBOL("IDNO",AB_package);
    Qstatic = STATIC_SYMBOL("STATIC",AB_package);
    Qanchor_top = STATIC_SYMBOL("ANCHOR-TOP",AB_package);
    Qanchor_bottom = STATIC_SYMBOL("ANCHOR-BOTTOM",AB_package);
    Qanchor_left = STATIC_SYMBOL("ANCHOR-LEFT",AB_package);
    Qanchor_right = STATIC_SYMBOL("ANCHOR-RIGHT",AB_package);
    Qresizeable = STATIC_SYMBOL("RESIZEABLE",AB_package);
    Qdialog = STATIC_SYMBOL("DIALOG",AB_package);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qmb_iconhand = STATIC_SYMBOL("MB-ICONHAND",AB_package);
    SET_SYMBOL_VALUE(Qmb_iconhand,FIX((SI_Long)16L));
    Qmb_iconquestion = STATIC_SYMBOL("MB-ICONQUESTION",AB_package);
    SET_SYMBOL_VALUE(Qmb_iconquestion,FIX((SI_Long)32L));
    Qmb_iconexclamation = STATIC_SYMBOL("MB-ICONEXCLAMATION",AB_package);
    SET_SYMBOL_VALUE(Qmb_iconexclamation,FIX((SI_Long)48L));
    Qmb_iconasterisk = STATIC_SYMBOL("MB-ICONASTERISK",AB_package);
    SET_SYMBOL_VALUE(Qmb_iconasterisk,FIX((SI_Long)64L));
    Qchange_user_settings = STATIC_SYMBOL("CHANGE-USER-SETTINGS",AB_package);
    Qws_clipchildren = STATIC_SYMBOL("WS-CLIPCHILDREN",AB_package);
    Qws_caption = STATIC_SYMBOL("WS-CAPTION",AB_package);
    Qws_sysmenu = STATIC_SYMBOL("WS-SYSMENU",AB_package);
    list_constant_125 = STATIC_LIST((SI_Long)4L,Qds_modalframe,
	    Qws_clipchildren,Qws_caption,Qws_sysmenu);
    array_constant_21 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    Quser_name = STATIC_SYMBOL("USER-NAME",AB_package);
    string_constant_94 = STATIC_STRING(":");
    list_constant_99 = STATIC_CONS(string_constant_94,Qnil);
    list_constant_100 = STATIC_CONS(Quser_name,list_constant_99);
    list_constant_101 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)49L),
	    FIX((SI_Long)8L));
    list_constant_114 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_100,FIX((SI_Long)6L),FIX((SI_Long)10L),
	    list_constant_101);
    Quser = STATIC_SYMBOL("USER",AB_package);
    Qes_autohscroll = STATIC_SYMBOL("ES-AUTOHSCROLL",AB_package);
    Qws_tabstop = STATIC_SYMBOL("WS-TABSTOP",AB_package);
    list_constant_102 = STATIC_CONS(Qws_tabstop,Qnil);
    list_constant_104 = STATIC_CONS(Qes_autohscroll,list_constant_102);
    Qws_ex_clientedge = STATIC_SYMBOL("WS-EX-CLIENTEDGE",AB_package);
    list_constant_103 = STATIC_CONS(Qws_ex_clientedge,Qnil);
    list_constant_105 = STATIC_CONS(list_constant_103,Qnil);
    list_constant_115 = STATIC_LIST_STAR((SI_Long)9L,Qedit,Quser,Qnil,
	    FIX((SI_Long)60L),FIX((SI_Long)8L),FIX((SI_Long)162L),
	    FIX((SI_Long)12L),list_constant_104,list_constant_105);
    Qpassword = STATIC_SYMBOL("PASSWORD",AB_package);
    list_constant_106 = STATIC_CONS(Qpassword,list_constant_99);
    list_constant_116 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_106,FIX((SI_Long)6L),FIX((SI_Long)27L),
	    list_constant_101);
    Qpass = STATIC_SYMBOL("PASS",AB_package);
    Qes_password = STATIC_SYMBOL("ES-PASSWORD",AB_package);
    list_constant_107 = STATIC_CONS(Qes_password,list_constant_104);
    list_constant_117 = STATIC_LIST_STAR((SI_Long)9L,Qedit,Qpass,Qnil,
	    FIX((SI_Long)60L),FIX((SI_Long)25L),FIX((SI_Long)162L),
	    FIX((SI_Long)12L),list_constant_107,list_constant_105);
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    list_constant_108 = STATIC_CONS(Quser_mode,list_constant_99);
    list_constant_118 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_108,FIX((SI_Long)6L),FIX((SI_Long)44L),
	    list_constant_101);
    Qcombobox = STATIC_SYMBOL("COMBOBOX",AB_package);
    Qmode = STATIC_SYMBOL("MODE",AB_package);
    Qcbs_dropdown = STATIC_SYMBOL("CBS-DROPDOWN",AB_package);
    Qws_vscroll = STATIC_SYMBOL("WS-VSCROLL",AB_package);
    list_constant_109 = STATIC_LIST_STAR((SI_Long)3L,Qcbs_dropdown,
	    Qws_vscroll,list_constant_102);
    list_constant_110 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)162L),
	    FIX((SI_Long)144L),list_constant_109);
    list_constant_119 = STATIC_LIST_STAR((SI_Long)6L,Qcombobox,Qmode,Qnil,
	    FIX((SI_Long)60L),FIX((SI_Long)42L),list_constant_110);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    list_constant_111 = STATIC_CONS(Qlanguage,list_constant_99);
    list_constant_120 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_111,FIX((SI_Long)6L),FIX((SI_Long)63L),
	    list_constant_101);
    Qlang = STATIC_SYMBOL("LANG",AB_package);
    list_constant_121 = STATIC_LIST_STAR((SI_Long)6L,Qcombobox,Qlang,Qnil,
	    FIX((SI_Long)60L),FIX((SI_Long)61L),list_constant_110);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    Qbs_defpushbutton = STATIC_SYMBOL("BS-DEFPUSHBUTTON",AB_package);
    list_constant_112 = STATIC_CONS(Qbs_defpushbutton,list_constant_102);
    list_constant_122 = STATIC_LIST((SI_Long)8L,Qbutton,Qidok,Qok,
	    FIX((SI_Long)61L),FIX((SI_Long)87L),FIX((SI_Long)50L),
	    FIX((SI_Long)14L),list_constant_112);
    Qcancel = STATIC_SYMBOL("CANCEL",AB_package);
    list_constant_113 = STATIC_LIST((SI_Long)4L,FIX((SI_Long)87L),
	    FIX((SI_Long)50L),FIX((SI_Long)14L),list_constant_102);
    list_constant_123 = STATIC_LIST_STAR((SI_Long)5L,Qbutton,Qidcancel,
	    Qcancel,FIX((SI_Long)127L),list_constant_113);
    Qdisconnect = STATIC_SYMBOL("DISCONNECT",AB_package);
    list_constant_124 = STATIC_LIST_STAR((SI_Long)5L,Qbutton,Qidabort,
	    Qdisconnect,FIX((SI_Long)193L),list_constant_113);
    list_constant_126 = STATIC_LIST((SI_Long)11L,list_constant_114,
	    list_constant_115,list_constant_116,list_constant_117,
	    list_constant_118,list_constant_119,list_constant_120,
	    list_constant_121,list_constant_122,list_constant_123,
	    list_constant_124);
    list_constant_127 = STATIC_LIST((SI_Long)12L,Qdialog,
	    Qchange_user_settings,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    FIX((SI_Long)265L),FIX((SI_Long)110L),list_constant_125,Qnil,
	    Qnil,array_constant_21,FIX((SI_Long)8L),list_constant_126);
    Native_login_dialog = list_constant_127;
    list_constant_128 = STATIC_CONS(Quser_mode,Qg2_user_mode);
    Qg2_window_name_or_class = STATIC_SYMBOL("G2-WINDOW-NAME-OR-CLASS",
	    AB_package);
    list_constant_129 = STATIC_CONS(Qwindow,Qg2_window_name_or_class);
    Qg2_window_specific_language = 
	    STATIC_SYMBOL("G2-WINDOW-SPECIFIC-LANGUAGE",AB_package);
    list_constant_130 = STATIC_CONS(Qlanguage,Qg2_window_specific_language);
    list_constant_131 = STATIC_CONS(Qok,Qend);
    list_constant_132 = STATIC_LIST((SI_Long)4L,list_constant_128,
	    list_constant_129,list_constant_130,list_constant_131);
    Alternate_translations_for_login_dialogs = list_constant_132;
    Quser_mode_alias_creation = STATIC_SYMBOL("USER-MODE-ALIAS-CREATION",
	    AB_package);
    Quser_mode_alias = STATIC_SYMBOL("USER-MODE-ALIAS",AB_package);
    list_constant_134 = STATIC_CONS(Quser_mode_alias,list_constant_99);
    list_constant_133 = STATIC_CONS(FIX((SI_Long)8L),Qnil);
    list_constant_135 = STATIC_CONS(FIX((SI_Long)60L),list_constant_133);
    list_constant_141 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_134,FIX((SI_Long)6L),FIX((SI_Long)10L),
	    list_constant_135);
    list_constant_136 = STATIC_LIST_STAR((SI_Long)3L,FIX((SI_Long)12L),
	    list_constant_104,list_constant_105);
    list_constant_142 = STATIC_LIST_STAR((SI_Long)7L,Qedit,Quser,Qnil,
	    FIX((SI_Long)75L),FIX((SI_Long)8L),FIX((SI_Long)140L),
	    list_constant_136);
    Qexisting_user_mode_for_this_alias = 
	    STATIC_SYMBOL("EXISTING-USER-MODE-FOR-THIS-ALIAS",AB_package);
    list_constant_137 = STATIC_CONS(Qexisting_user_mode_for_this_alias,
	    list_constant_99);
    list_constant_143 = STATIC_LIST_STAR((SI_Long)6L,Qstatic,Qnil,
	    list_constant_137,FIX((SI_Long)6L),FIX((SI_Long)27L),
	    list_constant_135);
    list_constant_138 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)144L),
	    list_constant_109);
    list_constant_144 = STATIC_LIST_STAR((SI_Long)7L,Qcombobox,Qmode,Qnil,
	    FIX((SI_Long)75L),FIX((SI_Long)25L),FIX((SI_Long)140L),
	    list_constant_138);
    list_constant_139 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)50L),
	    FIX((SI_Long)14L),list_constant_112);
    list_constant_145 = STATIC_LIST_STAR((SI_Long)6L,Qbutton,Qidok,Qok,
	    FIX((SI_Long)81L),FIX((SI_Long)55L),list_constant_139);
    list_constant_140 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)50L),
	    FIX((SI_Long)14L),list_constant_102);
    list_constant_146 = STATIC_LIST_STAR((SI_Long)6L,Qbutton,Qidcancel,
	    Qcancel,FIX((SI_Long)147L),FIX((SI_Long)55L),list_constant_140);
    list_constant_147 = STATIC_LIST((SI_Long)6L,list_constant_141,
	    list_constant_142,list_constant_143,list_constant_144,
	    list_constant_145,list_constant_146);
    list_constant_148 = STATIC_LIST((SI_Long)12L,Qdialog,
	    Quser_mode_alias_creation,FIX((SI_Long)0L),FIX((SI_Long)0L),
	    FIX((SI_Long)265L),FIX((SI_Long)80L),list_constant_125,Qnil,
	    Qnil,array_constant_21,FIX((SI_Long)8L),list_constant_147);
    Native_alias_creation_dialog = list_constant_148;
    Qg2_login_user_name_qm = STATIC_SYMBOL("G2-LOGIN-USER-NAME\?",AB_package);
    Qg2_login_user_mode = STATIC_SYMBOL("G2-LOGIN-USER-MODE",AB_package);
    Qg2_login_specific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("G2-LOGIN-SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",
	    AB_package);
    Qg2_user_mode_for_login = STATIC_SYMBOL("G2-USER-MODE-FOR-LOGIN",
	    AB_package);
    Qlanguage_qm = STATIC_SYMBOL("LANGUAGE\?",AB_package);
    Qg2_login_comments = STATIC_SYMBOL("G2-LOGIN-COMMENTS",AB_package);
    Qspec = STATIC_SYMBOL("SPEC",AB_package);
    Qdata = STATIC_SYMBOL("DATA",AB_package);
    Qbeep = STATIC_SYMBOL("BEEP",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    Qchanging_mode = STATIC_SYMBOL("CHANGING-MODE",AB_package);
    Qpassword_change = STATIC_SYMBOL("PASSWORD-CHANGE",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)3L,Qchanging_mode,
	    Qpassword_change,Qalias_creation);
    Qhandle_login_dialog_message = 
	    STATIC_SYMBOL("HANDLE-LOGIN-DIALOG-MESSAGE",AB_package);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qhandle_login_dialog_message,
	    Qhandle_login_dialog_message,Qnew_style_event_handler);
    Qg2_defstruct_structure_name_g2_login_state_g2_struct = 
	    STATIC_SYMBOL("G2-LOGIN-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2pvt_choice = STATIC_SYMBOL("G2PVT-CHOICE",AB_package);
    Qg2_login_user_password_qm = STATIC_SYMBOL("G2-LOGIN-USER-PASSWORD\?",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_login_dialog_message,
	    STATIC_FUNCTION(handle_login_dialog_message,NIL,FALSE,1,1));
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qupdate_mouse_cursor = STATIC_SYMBOL("UPDATE-MOUSE-CURSOR",AB_package);
    mutate_global_property(Qupdate_mouse_cursor,Qupdate_mouse_cursor,
	    Qnew_style_event_handler);
    Qg2_defstruct_structure_name_selection_handle_spot_g2_struct = 
	    STATIC_SYMBOL("SELECTION-HANDLE-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qcircle_slash = STATIC_SYMBOL("CIRCLE-SLASH",AB_package);
    Qmouse_cursor = STATIC_SYMBOL("MOUSE-CURSOR",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_mouse_cursor,
	    STATIC_FUNCTION(update_mouse_cursor,NIL,FALSE,1,1));
    Qvertex = STATIC_SYMBOL("VERTEX",AB_package);
    Qresize = STATIC_SYMBOL("RESIZE",AB_package);
    Qdrag_selection_handle = STATIC_SYMBOL("DRAG-SELECTION-HANDLE",AB_package);
    mutate_global_property(Qdrag_selection_handle,Qdrag_selection_handle,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qdrag_selection_handle,
	    STATIC_FUNCTION(drag_selection_handle,NIL,FALSE,1,1));
    Qresize_block_permitted_p = STATIC_SYMBOL("RESIZE-BLOCK-PERMITTED-P",
	    AB_package);
    Qmove_object = STATIC_SYMBOL("MOVE-OBJECT",AB_package);
    SET_SYMBOL_FUNCTION(Qresize_block_permitted_p,
	    STATIC_FUNCTION(resize_block_permitted_p,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_register_callback_on_twng_exit = 
	    STATIC_SYMBOL("G2-REGISTER-CALLBACK-ON-TWNG-EXIT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_register_callback_on_twng_exit,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_48 = 
	    STATIC_STRING("Passed window is not a TWNG window: ~NF");
    SET_SYMBOL_FUNCTION(Qg2_register_callback_on_twng_exit,
	    STATIC_FUNCTION(g2_register_callback_on_twng_exit,NIL,FALSE,2,2));
    Qg2_unregister_callback_on_twng_exit = 
	    STATIC_SYMBOL("G2-UNREGISTER-CALLBACK-ON-TWNG-EXIT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_unregister_callback_on_twng_exit,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_unregister_callback_on_twng_exit,
	    STATIC_FUNCTION(g2_unregister_callback_on_twng_exit,NIL,FALSE,
	    2,2));
    string_constant_49 = STATIC_STRING("twng-disconnect-callback");
}
