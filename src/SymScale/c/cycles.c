/* cycles.c
 * Input file:  cycles.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cycles.h"


static Object Qreal_time;          /* real-time */

static Object Qsimulated_time;     /* simulated-time */

static Object float_constant;      /* 0.0 */

/* RESYNCHRONIZE-GENSYM-TIME-AND-ACTUAL-TIME */
Object resynchronize_gensym_time_and_actual_time()
{
    Object current_fixnum_time, old_gensym_time, scheduler_mode;
    Object gensymed_symbol, aref_arg_1, gensymed_symbol_3;
    Object millisecond_minimum_scheduling_interval_qm;
    SI_Long gensymed_symbol_2;
    SI_Long gensymed_symbol_6;
    char temp;
    double current_unix_time, floored_unix_time, gensymed_symbol_1, arg, arg_1;
    double temp_1, aref_new_value, float_minimum_scheduling_interval;
    double gensymed_symbol_4, gensymed_symbol_5;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(183,0);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	current_fixnum_time = c_native_clock_ticks_or_cache(T,Nil);
	current_unix_time = g2ext_unix_time_as_float();
	floored_unix_time = inline_ffloor_1(current_unix_time);
	old_gensym_time = Gensym_time;
	scheduler_mode = scheduler_mode_function(Timing_parameters);
	if (Warmbooting_qm) {
	    if (EQ(scheduler_mode,Qreal_time) &&  
		    !TRUEP(Warmbooting_with_catch_up_qm)) {
	      next_loop:
		gensymed_symbol = Gensym_time;
		gensymed_symbol_1 = floored_unix_time - 
			DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L) + 
			(double)IFIX(Gensym_time_at_start);
		arg = gensymed_symbol_1;
		arg_1 = DOUBLE_FLOAT_TO_DOUBLE(Most_positive_fixnum_as_float);
		temp = arg > arg_1 &&  !inline_nanp_for_comparison(arg) ?  
			!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		if (temp);
		else {
		    arg = gensymed_symbol_1;
		    arg_1 = 
			    DOUBLE_FLOAT_TO_DOUBLE(Most_negative_fixnum_as_float);
		    temp = arg < arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		gensymed_symbol_2 = temp ? IFIX(Most_negative_fixnum) : 
			inline_floor_1(gensymed_symbol_1);
		if (CAS_SYMBOL(Qgensym_time,gensymed_symbol,
			FIX(gensymed_symbol_2)))
		    goto end_1;
		goto next_loop;
	      end_loop:
	      end_1:
		aref_arg_1 = Current_g2_time;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_unix_time);
		aref_arg_1 = Most_recent_g2_time;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_unix_time);
		aref_arg_1 = Real_time_of_last_g2_tick;
		DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_unix_time);
	      next_loop_1:
		gensymed_symbol = Fixnum_time_of_last_g2_tick;
		gensymed_symbol_3 = current_fixnum_time;
		if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,
			gensymed_symbol,gensymed_symbol_3))
		    goto end_2;
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	}
	else {
	  next_loop_2:
	    gensymed_symbol = Gensym_time_at_start;
	    gensymed_symbol_3 = Gensym_time;
	    if (CAS_SYMBOL(Qgensym_time_at_start,gensymed_symbol,
		    gensymed_symbol_3))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	    aref_arg_1 = Gensym_base_time_as_managed_float;
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    aref_new_value = floored_unix_time + temp_1 - 
		    (double)IFIX(Gensym_time);
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,aref_new_value);
	    aref_arg_1 = Current_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_unix_time);
	    aref_arg_1 = Most_recent_g2_time;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_unix_time);
	    aref_arg_1 = Real_time_of_last_g2_tick;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,current_unix_time);
	  next_loop_3:
	    gensymed_symbol = Fixnum_time_of_last_g2_tick;
	    gensymed_symbol_3 = current_fixnum_time;
	    if (CAS_SYMBOL(Qfixnum_time_of_last_g2_tick,gensymed_symbol,
		    gensymed_symbol_3))
		goto end_4;
	    goto next_loop_3;
	  end_loop_3:
	  end_4:
	    aref_arg_1 = G2_time_at_start;
	    DFLOAT_ISASET_1(aref_arg_1,(SI_Long)0L,floored_unix_time);
	}
	millisecond_minimum_scheduling_interval_qm = 
		minimum_scheduling_interval_function(Timing_parameters);
	if (EQ(scheduler_mode,Qreal_time) || EQ(scheduler_mode,
		Qsimulated_time)) {
	    if (millisecond_minimum_scheduling_interval_qm) {
		float_minimum_scheduling_interval = 
			millisecond_minimum_scheduling_interval_qm ? 
			(double)IFIX(millisecond_minimum_scheduling_interval_qm) 
			/ 1000.0 : 0.0;
	      next_loop_4:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_1 = (double)IFIX(Fixnum_time_units_per_second);
		gensymed_symbol_3 = float_constant;
		gensymed_symbol_4 = EQ(scheduler_mode,Qreal_time) ? 
			DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) : 
			current_unix_time;
		gensymed_symbol_5 = float_minimum_scheduling_interval;
		gensymed_symbol_4 = gensymed_symbol_4 + gensymed_symbol_5;
		gensymed_symbol_5 = current_unix_time;
		gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(gensymed_symbol_3);
		gensymed_symbol_4 = MAX(temp_1,gensymed_symbol_4);
		gensymed_symbol_6 = inline_floor_1(gensymed_symbol_1 * 
			gensymed_symbol_4);
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,LONG_TO_FIXNUM(gensymed_symbol_6)))
		    goto end_5;
		goto next_loop_4;
	      end_loop_4:
	      end_5:
	      next_loop_5:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_3 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_3))
		    goto end_6;
		goto next_loop_5;
	      end_loop_5:
	      end_6:;
	    }
	    else {
	      next_loop_6:
		gensymed_symbol = Fixnum_time_until_g2_time_tick;
		gensymed_symbol_2 = (SI_Long)0L;
		if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,
			gensymed_symbol,FIX(gensymed_symbol_2)))
		    goto end_7;
		goto next_loop_6;
	      end_loop_6:
	      end_7:
	      next_loop_7:
		gensymed_symbol = G2_time_to_tick_p_base;
		gensymed_symbol_3 = current_fixnum_time;
		if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
			gensymed_symbol_3))
		    goto end_8;
		goto next_loop_7;
	      end_loop_7:
	      end_8:;
	    }
	}
	else {
	  next_loop_8:
	    gensymed_symbol = Fixnum_time_until_g2_time_tick;
	    gensymed_symbol_2 = (SI_Long)0L;
	    if (CAS_SYMBOL(Qfixnum_time_until_g2_time_tick,gensymed_symbol,
		    FIX(gensymed_symbol_2)))
		goto end_9;
	    goto next_loop_8;
	  end_loop_8:
	  end_9:
	  next_loop_9:
	    gensymed_symbol = G2_time_to_tick_p_base;
	    gensymed_symbol_3 = current_fixnum_time;
	    if (CAS_SYMBOL(Qg2_time_to_tick_p_base,gensymed_symbol,
		    gensymed_symbol_3))
		goto end_10;
	    goto next_loop_9;
	  end_loop_9:
	  end_10:;
	}
	unpack_future_tasks_into_current_task_queues(T);
	if (Warmbooting_qm && FIXNUM_NE(old_gensym_time,Gensym_time))
	    take_actions_at_start_of_clock_tick(FIX((SI_Long)0L));
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object Qpause;              /* pause */

/* SYSTEM-PAUSE */
Object system_pause varargs_1(int, n)
{
    Object abort_p, abort_1, gensymed_symbol, gensymed_symbol_1, server;
    Object ab_loop_list_, pause_function_qm;
    Declare_varargs;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(183,1);
    SAVE_STACK();
    INIT_ARGS();
    SAVE_ARGS();
    abort_p = KEYWORD_ARG_P(Kabort);
    abort_1 = abort_p ? KEYWORD_ARG(abort_p) : Nil;
  next_loop:
    gensymed_symbol = System_is_running;
    gensymed_symbol_1 = Nil;
    if (CAS_SYMBOL(Qsystem_is_running,gensymed_symbol,gensymed_symbol_1))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
  next_loop_1:
    gensymed_symbol = System_has_paused;
    gensymed_symbol_1 = T;
    if (CAS_SYMBOL(Qsystem_has_paused,gensymed_symbol,gensymed_symbol_1))
	goto end_2;
    goto next_loop_1;
  end_loop_1:
  end_2:
    if (abort_1) {
      next_loop_2:
	gensymed_symbol = System_has_aborted;
	gensymed_symbol_1 = T;
	if (CAS_SYMBOL(Qsystem_has_aborted,gensymed_symbol,gensymed_symbol_1))
	    goto end_3;
	goto next_loop_2;
      end_loop_2:
      end_3:;
    }
    defer_current_g2_running_tasks();
    update_g2_run_state();
    complete_save_after_running_if_necessary();
    server = Nil;
    ab_loop_list_ = List_of_all_data_servers;
    pause_function_qm = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    server = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pause_function_qm = ISVREF(server,(SI_Long)11L);
    if (pause_function_qm)
	FUNCALL_0(SYMBOL_FUNCTION(pause_function_qm));
    goto next_loop_3;
  end_loop_3:;
    result = run_state_change_hook(Qpause);
    RESTORE_STACK();
    return result;
}

static Object Qsystem_start;       /* system-start */

static Object Qsystem_frame;       /* system-frame */

static Object Qg2_extension;       /* g2-extension */

static Object Qkb_workspace;       /* kb-workspace */

static Object Qmessage_board;      /* message-board */

static Object Qstart;              /* start */

/* SYSTEM-START */
Object system_start()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, expiration_qm;
    Object authorized_package_list, today, existing_package, ab_loop_list_;
    Object package_name_1, start_date_qm, end_date_qm, ab_loop_desetq_, temp_2;
    Object window_instigating_this_rule_instance_qm, gensymed_symbol;
    Object gensymed_symbol_1, server, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object frame, g2_extension, block, message_board_qm, sub_class_bit_vector;
    Object collecting_updates_to_sensor_attributes_p;
    Object collected_updates_to_sensor_attributes;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(4);
    Object result;

    x_note_fn_call(183,2);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    3);
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
	  SVREF(temp,svref_arg_2) = Qsystem_start;
      }
      if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	  expiration_qm = FOURTH(End_of_recovery_list);
	  temp_1 = expiration_qm && FIXNUMP(expiration_qm) ? 
		  FIXNUM_GE(expiration_qm,get_universal_date()) : TRUEP(T);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  authorized_package_list = THIRD(Local_recovery_list);
	  today = get_universal_date();
	  existing_package = Nil;
	  ab_loop_list_ = Control_sequence_record;
	  package_name_1 = Nil;
	  start_date_qm = Nil;
	  end_date_qm = Nil;
	  ab_loop_desetq_ = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  ab_loop_desetq_ = M_CAR(ab_loop_list_);
	  existing_package = CAR(ab_loop_desetq_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loop_desetq_ = assq_function(existing_package,
		  authorized_package_list);
	  package_name_1 = CAR(ab_loop_desetq_);
	  temp_2 = CDR(ab_loop_desetq_);
	  temp_2 = CDR(temp_2);
	  temp_2 = CDR(temp_2);
	  temp_2 = CDR(temp_2);
	  start_date_qm = CAR(temp_2);
	  temp_2 = CDR(ab_loop_desetq_);
	  temp_2 = CDR(temp_2);
	  temp_2 = CDR(temp_2);
	  temp_2 = CDR(temp_2);
	  temp_2 = CDR(temp_2);
	  end_date_qm = CAR(temp_2);
	  if ( !(package_name_1 && (start_date_qm ? 
		  FIXNUM_LE(start_date_qm,today) && FIXNUM_LE(today,
		  end_date_qm) : TRUEP(T)))) {
	      temp_1 = TRUEP(Nil);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  temp_1 = TRUEP(T);
	  goto end_1;
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp_2 = BOUNDP(Qcurrent_workstation_window) ? 
		  Current_workstation_window : Qnil;
	  if (temp_2);
	  else
	      temp_2 = System_window;
	  window_instigating_this_rule_instance_qm = temp_2;
	  PUSH_SPECIAL_WITH_SYMBOL(Window_instigating_this_rule_instance_qm,Qwindow_instigating_this_rule_instance_qm,window_instigating_this_rule_instance_qm,
		  2);
	    reset_g2_random_state( 
		    !TRUEP(repeat_random_function_on_reset_qm_function(Miscellaneous_parameters)) 
		    ? T : Nil);
	    make_all_indexed_attribute_hash_tables();
	    Debugging_reset = Nil;
	    Inhibit_non_real_time_clock_ticks_qm = Nil;
	  next_loop_1:
	    gensymed_symbol = System_is_running;
	    gensymed_symbol_1 = T;
	    if (CAS_SYMBOL(Qsystem_is_running,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_2;
	    goto next_loop_1;
	  end_loop_1:
	  end_2:
	  next_loop_2:
	    gensymed_symbol = System_has_paused;
	    gensymed_symbol_1 = Nil;
	    if (CAS_SYMBOL(Qsystem_has_paused,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_3;
	    goto next_loop_2;
	  end_loop_2:
	  end_3:
	  next_loop_3:
	    gensymed_symbol = System_has_aborted;
	    gensymed_symbol_1 = Nil;
	    if (CAS_SYMBOL(Qsystem_has_aborted,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_4;
	    goto next_loop_3;
	  end_loop_3:
	  end_4:
	    update_g2_run_state();
	    preset_gensym_time_for_initialization();
	  next_loop_4:
	    gensymed_symbol = Items_needing_initialization;
	    gensymed_symbol_1 = Nil;
	    if (CAS_SYMBOL(Qitems_needing_initialization,gensymed_symbol,
		    gensymed_symbol_1))
		goto end_5;
	    goto next_loop_4;
	  end_loop_4:
	  end_5:
	    server = Nil;
	    ab_loop_list_ = List_of_all_data_servers;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    server = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    FUNCALL_0(SYMBOL_FUNCTION(ISVREF(server,(SI_Long)7L)));
	    goto next_loop_5;
	  end_loop_5:;
	    schedule_immediate_data_server_accept_data_calls();
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    frame = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qsystem_frame);
	    next_loop_6:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_7:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_6;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_6;
		  goto next_loop_7;
		end_loop_6:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_7;
	      frame = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	      goto next_loop_6;
	    end_loop_7:;
	    POP_SPECIAL();
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    g2_extension = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qg2_extension);
	    next_loop_8:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_9:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_8;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_8;
		  goto next_loop_9;
		end_loop_8:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_9;
	      g2_extension = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(g2_extension,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      if (gensymed_symbol) {
		  temp_2 = ISVREF(g2_extension,(SI_Long)8L);
		  temp_1 =  !TRUEP(CAR(temp_2));
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if ( !temp_1) {
		  gensymed_symbol = 
			  ISVREF(ISVREF(ISVREF(ISVREF(g2_extension,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
			  (SI_Long)1L);
		  gensymed_symbol_1 = g2_extension;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	      }
	      goto next_loop_8;
	    end_loop_9:;
	    POP_SPECIAL();
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    block = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qkb_workspace);
	    next_loop_10:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_11:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_10;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_10;
		  goto next_loop_11;
		end_loop_10:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_11;
	      block = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	      gensymed_symbol = gensymed_symbol ? 
		      ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	      if ( !TRUEP(gensymed_symbol) ?  !TRUEP(ISVREF(block,
		      (SI_Long)18L)) : TRUEP(Nil)) {
		  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			  (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
			  (SI_Long)1L);
		  gensymed_symbol_1 = block;
		  inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	      }
	      goto next_loop_10;
	    end_loop_11:;
	    POP_SPECIAL();
	    message_board_qm = 
		    get_instance_with_name_if_any(Qmessage_board,
		    Qmessage_board);
	    if (message_board_qm) {
		gensymed_symbol = 
			ISVREF(ISVREF(ISVREF(ISVREF(message_board_qm,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
		gensymed_symbol_1 = message_board_qm;
		inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	    }
	    if (Warmbooting_qm) {
		scope_conses = Scope_conses;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		block = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
		  ab_loopvar_ = collect_subclasses(Qblock);
		next_loop_12:
		  if ( !TRUEP(ab_loopvar__1)) {
		    next_loop_13:
		      if ( !TRUEP(ab_loopvar_))
			  goto end_loop_12;
		      ab_loopvar__1 = 
			      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			      Instances_specific_to_this_class_kbprop);
		      ab_loopvar_ = M_CDR(ab_loopvar_);
		      if (ab_loopvar__1)
			  goto end_loop_12;
		      goto next_loop_13;
		    end_loop_12:
		      temp_1 =  !TRUEP(ab_loopvar__1);
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1)
		      goto end_loop_13;
		  block = ab_loopvar__1;
		  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
		  if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			  (SI_Long)262144L) &&  
			      !TRUEP(superior_frame(block))) {
		      sub_class_bit_vector = ISVREF(ISVREF(block,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Connection_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol_2 = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_3 = (SI_Long)1L;
			  gensymed_symbol_4 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_3 = gensymed_symbol_3 << 
				  gensymed_symbol_4;
			  gensymed_symbol_2 = gensymed_symbol_2 & 
				  gensymed_symbol_3;
			  temp_1 = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      temp_1 =  !temp_1;
		      if (temp_1);
		      else
			  temp_1 =  
				  !TRUEP(get_superblock_of_connection_frame(block));
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			      (SI_Long)1L),(SI_Long)11L),(SI_Long)30L),
			      (SI_Long)1L);
		      gensymed_symbol_1 = block;
		      inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
		  }
		  goto next_loop_12;
		end_loop_13:;
		POP_SPECIAL();
	    }
	    G2_has_been_started_qm = T;
	    collecting_updates_to_sensor_attributes_p = T;
	    collected_updates_to_sensor_attributes = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Collected_updates_to_sensor_attributes,Qcollected_updates_to_sensor_attributes,collected_updates_to_sensor_attributes,
		    1);
	      PUSH_SPECIAL_WITH_SYMBOL(Collecting_updates_to_sensor_attributes_p,Qcollecting_updates_to_sensor_attributes_p,collecting_updates_to_sensor_attributes_p,
		      0);
		initialize_items_needing_initialization();
		handle_collected_updates_to_sensor_attributes();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    resynchronize_gensym_time_and_actual_time();
	    notify_data_server_of_start_or_reset(T);
	    inline_network_io_trace_note("Starting G2");
	    run_state_change_hook(Qstart);
	    result = VALUES_1(Nil);
	  POP_SPECIAL();
      }
      else
	  result = warn_upon_start_or_resume();
    POP_SPECIAL();
    return result;
}

static Object Qsystem_reset;       /* system-reset */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qreset;              /* reset */

/* SYSTEM-RESET */
Object system_reset()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object system_has_paused, system_is_running;
    Object frame_serial_number_prior_to_reset, scope_conses, ab_loopvar_;
    Object ab_loopvar__1, block, ab_loopvar__2, ab_loopvar__3, ab_loopvar__4;
    Object blocks_needing_representations_of_status_refreshed, gensymed_symbol;
    Object gensymed_symbol_1, items_to_delete;
    Object delete_connections_without_leaving_stubs_qm, connections_to_delete;
    Object item;
    Object inhibit_updating_module_related_frame_notes_for_all_workspaces_qm;
    Object serial_number, ab_loop_list_, xa, ya, superior_qm, ab_node_stack_;
    Object ab_current_node_, ab_skip_list_form_, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_connection_, ab_connection_item_, connection, temp_2;
    Object ab_less_than_branch_qm_, g2_extension, gensymed_symbol_2;
    Object message_board_qm;
    Object safe_to_access_attribute_display_update_interval_p, server;
    Object shut_down_function_qm, frame;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(4);
    Object result;

    x_note_fn_call(183,3);
    SAVE_STACK();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    3);
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
	  SVREF(temp,svref_arg_2) = Qsystem_reset;
      }
      if (System_has_paused || System_is_running) {
	  cancel_all_field_edits_in_session();
	  system_has_paused = Nil;
	  system_is_running = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(System_is_running,Qsystem_is_running,system_is_running,
		  1);
	    PUSH_SPECIAL_WITH_SYMBOL(System_has_paused,Qsystem_has_paused,system_has_paused,
		    0);
	      complete_save_after_running_if_necessary();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  frame_serial_number_prior_to_reset = 
		  copy_frame_serial_number(Current_frame_serial_number);
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar__2 = Nil;
	    ab_loopvar__3 = Nil;
	    ab_loopvar__4 = Nil;
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
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_1;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    if (ISVREF(block,(SI_Long)9L) && 
		    frame_status_and_notes_reflects_flags_of_frame_p(block)) {
		ab_loopvar__4 = gensym_cons_1(block,Nil);
		if (ab_loopvar__3)
		    M_CDR(ab_loopvar__3) = ab_loopvar__4;
		else
		    ab_loopvar__2 = ab_loopvar__4;
		ab_loopvar__3 = ab_loopvar__4;
	    }
	    goto next_loop;
	  end_loop_1:
	    blocks_needing_representations_of_status_refreshed = ab_loopvar__2;
	    goto end_1;
	    blocks_needing_representations_of_status_refreshed = Qnil;
	  end_1:;
	  POP_SPECIAL();
	next_loop_2:
	  gensymed_symbol = System_has_paused;
	  gensymed_symbol_1 = Nil;
	  if (CAS_SYMBOL(Qsystem_has_paused,gensymed_symbol,gensymed_symbol_1))
	      goto end_2;
	  goto next_loop_2;
	end_loop_2:
	end_2:
	next_loop_3:
	  gensymed_symbol = System_is_running;
	  gensymed_symbol_1 = Nil;
	  if (CAS_SYMBOL(Qsystem_is_running,gensymed_symbol,gensymed_symbol_1))
	      goto end_3;
	  goto next_loop_3;
	end_loop_3:
	end_3:
	  update_g2_run_state();
	  terminate_kb_save_or_backup_if_error_occurs();
	  Inhibit_non_real_time_clock_ticks_qm = Nil;
	  LOCK(Procedure_invocations_lock);
	  if (PUSH_UNWIND_PROTECT(0))
	      clear_procedure_invocations_1();
	  POP_UNWIND_PROTECT(0);
	  UNLOCK(Procedure_invocations_lock);
	  CONTINUE_UNWINDING(0);
	  kill_all_instances_of_all_g2gl_processes();
	  disable_and_clear_system_profiling();
	  reclaim_all_indexed_attribute_hash_tables();
	  Global_table_of_attributes_pane = Nil;
	  Global_table_of_hidden_attributes_pane = Nil;
	  notify_sockets_of_g2_reset();
	  notify_http_servers_of_g2_reset();
	  items_to_delete = Nil;
	  delete_connections_without_leaving_stubs_qm = T;
	  connections_to_delete = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Delete_connections_without_leaving_stubs_qm,Qdelete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
		  2);
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    item = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qkb_workspace);
	    next_loop_4:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_5:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_4;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_4;
		  goto next_loop_5;
		end_loop_4:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_5;
	      item = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      if ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		      (SI_Long)262144L) &&  !TRUEP(ISVREF(item,(SI_Long)18L)))
		  items_to_delete = gensym_cons_1(item,items_to_delete);
	      goto next_loop_4;
	    end_loop_5:;
	    POP_SPECIAL();
	    inhibit_updating_module_related_frame_notes_for_all_workspaces_qm 
		    = T;
	    PUSH_SPECIAL_WITH_SYMBOL(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,Qinhibit_updating_module_related_frame_notes_for_all_workspaces_qm,inhibit_updating_module_related_frame_notes_for_all_workspaces_qm,
		    0);
	      serial_number = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      item = Nil;
	      ab_loop_list_ = items_to_delete;
	    next_loop_6:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_6;
	      item = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      gensymed_symbol = ISVREF(item,(SI_Long)3L);
	      temp_1 = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		      Qavailable_frame_vector) : TRUEP(Qnil);
	      if (temp_1);
	      else
		  temp_1 = FIXNUMP(gensymed_symbol) ? 
			  IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
	      if (temp_1);
	      else if (FIXNUMP(serial_number))
		  temp_1 = FIXNUMP(gensymed_symbol) ? 
			  FIXNUM_LT(serial_number,gensymed_symbol) : TRUEP(T);
	      else if (FIXNUMP(gensymed_symbol))
		  temp_1 = TRUEP(Nil);
	      else {
		  xa = M_CAR(serial_number);
		  ya = M_CAR(gensymed_symbol);
		  temp_1 = FIXNUM_LT(xa,ya);
		  if (temp_1);
		  else
		      temp_1 = FIXNUM_EQ(xa,ya) ? 
			      FIXNUM_LT(M_CDR(serial_number),
			      M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	      }
	      if ( !temp_1)
		  delete_frame(item);
	      goto next_loop_6;
	    end_loop_6:
	      reclaim_frame_serial_number(serial_number);
	    POP_SPECIAL();
	    if ( 
		    !TRUEP(Inhibit_updating_module_related_frame_notes_for_all_workspaces_qm))
		update_module_related_frame_notes_for_all_workspaces(0);
	    reclaim_gensym_list_1(items_to_delete);
	    items_to_delete = Nil;
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    block = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    1);
	      superior_qm = Nil;
	      ab_loopvar_ = collect_subclasses(Qblock);
	    next_loop_7:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_8:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_7;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_7;
		  goto next_loop_8;
		end_loop_7:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_8;
	      block = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      superior_qm = superior_frame(block);
	      if (ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)16L)) {
		  if ((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
			  (SI_Long)262144L) && ( !TRUEP(superior_qm) ||  
			  !((SI_Long)0L != (IFIX(ISVREF(superior_qm,
			  (SI_Long)5L)) & (SI_Long)262144L))))
		      items_to_delete = gensym_cons_1(block,items_to_delete);
		  remove_transient_relation_instances(block,T);
	      }
	      if ( !EQ(CAR(items_to_delete),block)) {
		  scope_conses = Scope_conses;
		  ab_node_stack_ = Nil;
		  ab_current_node_ = Nil;
		  gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
		  gensymed_symbol = gensymed_symbol ? 
			  ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) 
			  : Nil;
		  ab_skip_list_form_ = gensymed_symbol;
		  ab_skip_list_p_ = Nil;
		  ab_next_node_ = Nil;
		  ab_tail_node_ = Nil;
		  ab_current_alist_ = Nil;
		  ab_entry_cons_ = Nil;
		  ab_connection_ = Nil;
		  ab_connection_item_ = Nil;
		  connection = Nil;
		  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			  0);
		    gensymed_symbol = CDR(ab_skip_list_form_);
		    if (CONSP(gensymed_symbol)) {
			temp_2 = M_CAR(gensymed_symbol);
			temp_1 = SIMPLE_VECTOR_P(temp_2);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			temp_2 = M_CDR(gensymed_symbol);
			ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_2) ? T : Nil;
		    }
		    else
			ab_skip_list_p_ = Nil;
		    if (ab_skip_list_p_) {
			ab_next_node_ = 
				ATOMIC_REF_OBJECT(ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
				(SI_Long)0L),(SI_Long)0L));
			ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
			if (EQ(ab_next_node_,ab_tail_node_))
			    ab_next_node_ = Nil;
		    }
		    else
			ab_next_node_ = CDR(ab_skip_list_form_);
		  next_loop_9:
		  next_loop_10:
		    if (ab_current_alist_) {
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_connection_ = M_CAR(ab_entry_cons_);
			ab_connection_item_ = M_CDR(ab_entry_cons_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
		    }
		    else if (ab_skip_list_p_) {
			if (ab_next_node_) {
			    ab_current_node_ = ab_next_node_;
			    ab_next_node_ = 
				    ATOMIC_REF_OBJECT(ISVREF(ISVREF(ab_current_node_,
				    (SI_Long)0L),(SI_Long)0L));
			    if (EQ(ab_next_node_,ab_tail_node_))
				ab_next_node_ = Nil;
			    ab_connection_ = ISVREF(ab_current_node_,
				    (SI_Long)2L);
			    ab_connection_item_ = ISVREF(ab_current_node_,
				    (SI_Long)3L);
			}
			else
			    ab_current_node_ = Nil;
		    }
		    else {
			if (ab_next_node_) {
			    ab_current_node_ = ab_next_node_;
			    ab_less_than_branch_qm_ = Nil;
			  next_loop_11:
			    ab_less_than_branch_qm_ = 
				    ISVREF(ab_current_node_,(SI_Long)1L);
			    if ( !TRUEP(ab_less_than_branch_qm_))
				goto end_loop_9;
			    ab_node_stack_ = scope_cons(ab_current_node_,
				    ab_node_stack_);
			    ab_current_node_ = ab_less_than_branch_qm_;
			    goto next_loop_11;
			  end_loop_9:;
			}
			else if (ab_node_stack_) {
			    ab_next_node_ = ab_node_stack_;
			    ab_current_node_ = M_CAR(ab_node_stack_);
			    ab_node_stack_ = M_CDR(ab_node_stack_);
			}
			else
			    ab_current_node_ = Nil;
			if (ab_current_node_) {
			    ab_next_node_ = ISVREF(ab_current_node_,
				    (SI_Long)2L);
			    ab_current_alist_ = ISVREF(ab_current_node_,
				    (SI_Long)3L);
			    ab_entry_cons_ = M_CAR(ab_current_alist_);
			    ab_connection_ = M_CAR(ab_entry_cons_);
			    ab_connection_item_ = M_CDR(ab_entry_cons_);
			    ab_current_alist_ = M_CDR(ab_current_alist_);
			}
		    }
		    if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
			    ab_connection_ && EQ(ISVREF(ab_connection_,
			    (SI_Long)3L),block))
			goto end_4;
		    goto next_loop_10;
		  end_loop_10:
		  end_4:
		    if ( !TRUEP(ab_current_node_))
			goto end_loop_11;
		    connection = ab_connection_;
		    if ((SI_Long)0L != (IFIX(ISVREF(connection,
			    (SI_Long)7L)) & (SI_Long)64L)) {
			temp_2 = ISVREF(connection,(SI_Long)1L);
			temp_1 = SYMBOLP(temp_2);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1)
			connections_to_delete = gensym_cons_1(connection,
				connections_to_delete);
		    goto next_loop_9;
		  end_loop_11:;
		  POP_SPECIAL();
	      }
	      goto next_loop_7;
	    end_loop_8:;
	    POP_SPECIAL();
	    serial_number = 
		    copy_frame_serial_number(Current_frame_serial_number);
	    item = Nil;
	    ab_loop_list_ = items_to_delete;
	  next_loop_12:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_12;
	    item = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(item,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(item) ? EQ(ISVREF(item,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(serial_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(serial_number,gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(serial_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1)
		delete_item(item);
	    goto next_loop_12;
	  end_loop_12:
	    reclaim_frame_serial_number(serial_number);
	    reclaim_gensym_list_1(items_to_delete);
	    serial_number = 
		    copy_frame_serial_number(Current_frame_serial_number);
	    connection = Nil;
	    ab_loop_list_ = connections_to_delete;
	  next_loop_13:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_13;
	    connection = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(connection,(SI_Long)10L);
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(serial_number))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(serial_number,gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(serial_number);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(serial_number),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1)
		delete_connection_leaving_stubs_if_appropriate(connection);
	    goto next_loop_13;
	  end_loop_13:
	    reclaim_frame_serial_number(serial_number);
	    reclaim_gensym_list_1(connections_to_delete);
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  g2_extension = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qg2_extension);
	  next_loop_14:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_15:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_14;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_14;
		goto next_loop_15;
	      end_loop_14:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_15;
	    g2_extension = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(g2_extension,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    if (gensymed_symbol) {
		temp_2 = ISVREF(g2_extension,(SI_Long)8L);
		temp_1 =  !TRUEP(CAR(temp_2));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ( !temp_1) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(g2_extension,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
		gensymed_symbol_1 = g2_extension;
		gensymed_symbol_2 = Nil;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    goto next_loop_14;
	  end_loop_15:;
	  POP_SPECIAL();
	  scope_conses = Scope_conses;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  block = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	    ab_loopvar_ = collect_subclasses(Qkb_workspace);
	  next_loop_16:
	    if ( !TRUEP(ab_loopvar__1)) {
	      next_loop_17:
		if ( !TRUEP(ab_loopvar_))
		    goto end_loop_16;
		ab_loopvar__1 = 
			lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			Instances_specific_to_this_class_kbprop);
		ab_loopvar_ = M_CDR(ab_loopvar_);
		if (ab_loopvar__1)
		    goto end_loop_16;
		goto next_loop_17;
	      end_loop_16:
		temp_1 =  !TRUEP(ab_loopvar__1);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		goto end_loop_17;
	    block = ab_loopvar__1;
	    ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(block,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)5L)) : Nil;
	    if ( !TRUEP(gensymed_symbol) ?  !TRUEP(ISVREF(block,
		    (SI_Long)18L)) : TRUEP(Nil)) {
		gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,
			(SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
		gensymed_symbol_1 = block;
		gensymed_symbol_2 = Nil;
		inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2);
	    }
	    goto next_loop_16;
	  end_loop_17:;
	  POP_SPECIAL();
	  message_board_qm = get_instance_with_name_if_any(Qmessage_board,
		  Qmessage_board);
	  if (message_board_qm) {
	      gensymed_symbol = 
		      ISVREF(ISVREF(ISVREF(ISVREF(message_board_qm,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	      gensymed_symbol_1 = message_board_qm;
	      gensymed_symbol_2 = Nil;
	      inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2);
	  }
	  finish_all_table_updates();
	  safe_to_access_attribute_display_update_interval_p = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Safe_to_access_attribute_display_update_interval_p,Qsafe_to_access_attribute_display_update_interval_p,safe_to_access_attribute_display_update_interval_p,
		  1);
	    clear_g2_schedule();
	    undo_kb_state_changes();
	    clear_inform_messages();
	    notify_data_server_of_start_or_reset(Nil);
	    server = Nil;
	    ab_loop_list_ = List_of_all_data_servers;
	    shut_down_function_qm = Nil;
	  next_loop_18:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_18;
	    server = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    shut_down_function_qm = ISVREF(server,(SI_Long)9L);
	    if (shut_down_function_qm)
		FUNCALL_0(SYMBOL_FUNCTION(shut_down_function_qm));
	    goto next_loop_18;
	  end_loop_18:;
	    cancel_data_server_accept_data_calls();
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    frame = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      ab_loopvar_ = collect_subclasses(Qsystem_frame);
	    next_loop_19:
	      if ( !TRUEP(ab_loopvar__1)) {
		next_loop_20:
		  if ( !TRUEP(ab_loopvar_))
		      goto end_loop_19;
		  ab_loopvar__1 = 
			  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
			  Instances_specific_to_this_class_kbprop);
		  ab_loopvar_ = M_CDR(ab_loopvar_);
		  if (ab_loopvar__1)
		      goto end_loop_19;
		  goto next_loop_20;
		end_loop_19:
		  temp_1 =  !TRUEP(ab_loopvar__1);
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1)
		  goto end_loop_20;
	      frame = ab_loopvar__1;
	      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(frame,
		      (SI_Long)1L),(SI_Long)11L),(SI_Long)31L),(SI_Long)1L);
	      gensymed_symbol_1 = frame;
	      gensymed_symbol_2 = Nil;
	      inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		      gensymed_symbol_2);
	      goto next_loop_19;
	    end_loop_20:;
	    POP_SPECIAL();
	    block = Nil;
	    ab_loop_list_ = blocks_needing_representations_of_status_refreshed;
	  next_loop_21:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_21;
	    block = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ISVREF(block,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(block) ? EQ(ISVREF(block,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(frame_serial_number_prior_to_reset))
		temp_1 = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number_prior_to_reset,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number_prior_to_reset);
		ya = M_CAR(gensymed_symbol);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number_prior_to_reset),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp_1)
		update_representations_of_slot_value(2,block,
			Qframe_status_and_notes);
	    goto next_loop_21;
	  end_loop_21:;
	    reclaim_gensym_list_1(blocks_needing_representations_of_status_refreshed);
	    Gensym_time_at_start = Gensym_time;
	    reclaim_frame_serial_number(frame_serial_number_prior_to_reset);
	    result = run_state_change_hook(Qreset);
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qresume;             /* resume */

/* SYSTEM-RESUME */
Object system_resume()
{
    Object expiration_qm, authorized_package_list, today, existing_package;
    Object ab_loop_list_, package_name_1, start_date_qm, end_date_qm;
    Object ab_loop_desetq_, temp_1, gensymed_symbol, gensymed_symbol_1, server;
    Object resume_function_qm;
    char temp;

    x_note_fn_call(183,4);
    if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	expiration_qm = FOURTH(End_of_recovery_list);
	temp = expiration_qm && FIXNUMP(expiration_qm) ? 
		FIXNUM_GE(expiration_qm,get_universal_date()) : TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	authorized_package_list = THIRD(Local_recovery_list);
	today = get_universal_date();
	existing_package = Nil;
	ab_loop_list_ = Control_sequence_record;
	package_name_1 = Nil;
	start_date_qm = Nil;
	end_date_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	existing_package = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_desetq_ = assq_function(existing_package,
		authorized_package_list);
	package_name_1 = CAR(ab_loop_desetq_);
	temp_1 = CDR(ab_loop_desetq_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	start_date_qm = CAR(temp_1);
	temp_1 = CDR(ab_loop_desetq_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	end_date_qm = CAR(temp_1);
	if ( !(package_name_1 && (start_date_qm ? FIXNUM_LE(start_date_qm,
		today) && FIXNUM_LE(today,end_date_qm) : TRUEP(T)))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	Debugging_reset = Nil;
      next_loop_1:
	gensymed_symbol = System_has_paused;
	gensymed_symbol_1 = Nil;
	if (CAS_SYMBOL(Qsystem_has_paused,gensymed_symbol,gensymed_symbol_1))
	    goto end_2;
	goto next_loop_1;
      end_loop_1:
      end_2:
      next_loop_2:
	gensymed_symbol = System_has_aborted;
	gensymed_symbol_1 = Nil;
	if (CAS_SYMBOL(Qsystem_has_aborted,gensymed_symbol,gensymed_symbol_1))
	    goto end_3;
	goto next_loop_2;
      end_loop_2:
      end_3:
      next_loop_3:
	gensymed_symbol = System_is_running;
	gensymed_symbol_1 = T;
	if (CAS_SYMBOL(Qsystem_is_running,gensymed_symbol,gensymed_symbol_1))
	    goto end_4;
	goto next_loop_3;
      end_loop_3:
      end_4:
	requeue_deferred_running_tasks();
	update_g2_run_state();
	server = Nil;
	ab_loop_list_ = List_of_all_data_servers;
	resume_function_qm = Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	server = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	resume_function_qm = ISVREF(server,(SI_Long)12L);
	if (resume_function_qm)
	    FUNCALL_0(SYMBOL_FUNCTION(resume_function_qm));
	goto next_loop_4;
      end_loop_4:;
	return run_state_change_hook(Qresume);
    }
    else
	return warn_upon_start_or_resume();
}

/* SYSTEM-RESTART */
Object system_restart()
{
    Object expiration_qm, authorized_package_list, today, existing_package;
    Object ab_loop_list_, package_name_1, start_date_qm, end_date_qm;
    Object ab_loop_desetq_, temp_1;
    char temp;

    x_note_fn_call(183,5);
    if ( !EQ(Unevaluated_expression,Within_side_limits)) {
	expiration_qm = FOURTH(End_of_recovery_list);
	temp = expiration_qm && FIXNUMP(expiration_qm) ? 
		FIXNUM_GE(expiration_qm,get_universal_date()) : TRUEP(T);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	authorized_package_list = THIRD(Local_recovery_list);
	today = get_universal_date();
	existing_package = Nil;
	ab_loop_list_ = Control_sequence_record;
	package_name_1 = Nil;
	start_date_qm = Nil;
	end_date_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	existing_package = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_desetq_ = assq_function(existing_package,
		authorized_package_list);
	package_name_1 = CAR(ab_loop_desetq_);
	temp_1 = CDR(ab_loop_desetq_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	start_date_qm = CAR(temp_1);
	temp_1 = CDR(ab_loop_desetq_);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	temp_1 = CDR(temp_1);
	end_date_qm = CAR(temp_1);
	if ( !(package_name_1 && (start_date_qm ? FIXNUM_LE(start_date_qm,
		today) && FIXNUM_LE(today,end_date_qm) : TRUEP(T)))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	system_reset();
	return system_start();
    }
    else
	return warn_upon_start_or_resume();
}

/* G2-REPEAT-RANDOM-FUNCTION */
Object g2_repeat_random_function()
{
    x_note_fn_call(183,6);
    return reset_g2_random_state(Nil);
}

/* G2-GET-RANDOM-SEED */
Object g2_get_random_seed()
{
    x_note_fn_call(183,7);
    return VALUES_1(Random_variation);
}

static Object string_constant;     /* "The argument ~a to g2-set-random-seed must be a non-negative integer." */

/* G2-SET-RANDOM-SEED */
Object g2_set_random_seed(seed)
    Object seed;
{
    Object top_of_stack, message_1, user_random_seed_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(183,8);
    if (IFIX(seed) < (SI_Long)0L) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant,seed);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    user_random_seed_qm = seed;
    PUSH_SPECIAL_WITH_SYMBOL(User_random_seed_qm,Quser_random_seed_qm,user_random_seed_qm,
	    0);
      result = reset_g2_random_state(T);
    POP_SPECIAL();
    return result;
}

/* G2-GENERATE-NEW-RANDOM-SEED */
Object g2_generate_new_random_seed()
{
    x_note_fn_call(183,9);
    return c_native_clock_ticks_or_cache(Nil,Nil);
}

static Object string_constant_1;   /* "real time" */

static Object string_constant_2;   /* "simulated time" */

static Object Qfast_time;          /* fast-time */

static Object string_constant_3;   /* "as fast as possible" */

static Object Qnupec_catch_up;     /* nupec-catch-up */

static Object string_constant_4;   /* "NUPEC catch up mode" */

static Object string_constant_5;   /* "unknown" */

/* WRITE-TIMING-SCHEDULER-MODE-FROM-SLOT */
Object write_timing_scheduler_mode_from_slot(mode,gensymed_symbol)
    Object mode, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(183,10);
    if (EQ(mode,Qreal_time))
	temp = string_constant_1;
    else if (EQ(mode,Qsimulated_time))
	temp = string_constant_2;
    else if (EQ(mode,Qfast_time))
	temp = string_constant_3;
    else if (EQ(mode,Qnupec_catch_up))
	temp = string_constant_4;
    else
	temp = string_constant_5;
    return twrite_general_string(temp);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

static Object Qas_fast_as_possible;  /* as-fast-as-possible */

/* TIMING-SCHEDULER-MODE-EVALUATION-SETTER */
Object timing_scheduler_mode_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, mode;
    Declare_special(5);
    Object result;

    x_note_fn_call(183,11);
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
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_timing_scheduler_mode_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    mode = evaluation_value;
    if (EQ(mode,Qas_fast_as_possible))
	result = VALUES_1(Qfast_time);
    else
	result = VALUES_1(mode);
  end_timing_scheduler_mode_evaluation_setter:
    return result;
}

/* TIMING-SCHEDULER-MODE-EVALUATION-GETTER */
Object timing_scheduler_mode_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(183,12);
    GENSYM_RETURN_ONE(EQ(slot_value,Qfast_time) ? Qas_fast_as_possible : 
	    slot_value);
    return VALUES_1(Nil);
}

static Object Qscheduler_mode;     /* scheduler-mode */

/* PUT-SCHEDULER-MODE */
Object put_scheduler_mode(timing_parameters_instance,new_mode,gensymed_symbol)
    Object timing_parameters_instance, new_mode, gensymed_symbol;
{
    Object gensymed_symbol_1;

    x_note_fn_call(183,13);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(timing_parameters_instance,Qscheduler_mode);
    SVREF(timing_parameters_instance,FIX((SI_Long)22L)) = new_mode;
    if (system_table_installed_p(timing_parameters_instance)) {
      next_loop:
	gensymed_symbol = Force_clock_tick;
	gensymed_symbol_1 = T;
	if (CAS_SYMBOL(Qforce_clock_tick,gensymed_symbol,gensymed_symbol_1))
	    goto end_1;
	goto next_loop;
      end_loop:
      end_1:
	update_g2_time_to_tick_after_scheduling_change();
    }
    return VALUES_1(new_mode);
}

/* INSTALL-SYSTEM-TABLE-FOR-TIMING-PARAMETERS */
Object install_system_table_for_timing_parameters(timing_parameters)
    Object timing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(183,14);
    PUSH_SPECIAL_WITH_SYMBOL(Timing_parameters,Qtiming_parameters,timing_parameters,
	    0);
      Global_daylight_saving_time_adjustment = ISVREF(Timing_parameters,
	      (SI_Long)26L);
      result = update_g2_time_to_tick_after_scheduling_change();
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-TIMING-PARAMETERS */
Object deinstall_system_table_for_timing_parameters(timing_parameters)
    Object timing_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(183,15);
    PUSH_SPECIAL_WITH_SYMBOL(Timing_parameters,Qtiming_parameters,timing_parameters,
	    0);
      Global_daylight_saving_time_adjustment = FIX((SI_Long)0L);
      result = update_g2_time_to_tick_after_scheduling_change();
    POP_SPECIAL();
    return result;
}

static Object Qalways_service_interface_first;  /* always-service-interface-first */

static Object string_constant_6;   /* "always service interface first" */

static Object Qtime_slice_dependant;  /* time-slice-dependant */

static Object string_constant_7;   /* "interruptible interface service" */

static Object string_constant_8;   /* "unknown value" */

/* WRITE-INTERFACE-MODE-FROM-SLOT */
Object write_interface_mode_from_slot(mode,gensymed_symbol)
    Object mode, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(183,16);
    if (EQ(mode,Qalways_service_interface_first))
	temp = string_constant_6;
    else if (EQ(mode,Qtime_slice_dependant))
	temp = string_constant_7;
    else
	temp = string_constant_8;
    return twrite(temp);
}

Object Scheduled_tasks_time_limit = UNBOUND;

Object Icp_socket_processing_time_limit = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Countdown_for_checking, Qcountdown_for_checking);

Object Legacy_multisecond_heartbeat_adjustment_priority = UNBOUND;

Object Legacy_multisecond_heartbeat_adjustment_interval = UNBOUND;

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_9;   /* "The license to use G2 on this machine expires on " */

static Object string_constant_10;  /* ".~%G2 will not run after this date.~%~%" */

static Object string_constant_11;  /* "The following application packages are not authorized:~%" */

static Object string_constant_12;  /* "The following application packages have expired authorizations:~%" */

static Object string_constant_13;  /* "The following application packages have authorizations with future start dates:~%" */

static Object string_constant_14;  /* "The following application packages have authorizations that will expire within a week:~%" */

/* DO-LEGACY-MULTISECOND-HEARTBEAT-ADJUSTMENTS */
Object do_legacy_multisecond_heartbeat_adjustments()
{
    Object expiration_qm, license_expiration_qm, gensymed_symbol, hour;
    Object this_hour, today, days_left, expired, will_expire, post_dated;
    Object not_authorized, post_message_qm, authorized_package_list;
    Object existing_package, ab_loop_list_, package_name_1, start_date_qm;
    Object end_date_qm, ab_loop_desetq_, temp, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object day, month, year;
    SI_Long start_date, end_date, hours_left, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, arg, arg_1, arg_2;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(183,17);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	expiration_qm = FOURTH(End_of_recovery_list);
	if ( !TRUEP(expiration_qm))
	    license_expiration_qm = Nil;
	else if (expiration_qm && IFIX(expiration_qm) >= (SI_Long)8388608L) {
	    start_date = IFIX(Reference_date_for_interval_encoding) + 
		    (IFIX(expiration_qm) & (SI_Long)4095L);
	    end_date = start_date + (IFIX(expiration_qm) >>  -  - 
		    (SI_Long)12L & (SI_Long)2047L);
	    result = VALUES_2(FIX(start_date),FIX(end_date));
	    gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
	    license_expiration_qm = gensymed_symbol;
	}
	else
	    license_expiration_qm = expiration_qm;
	result = get_decoded_real_time();
	hour = NTH_VALUE((SI_Long)2L, result);
	this_hour = hour;
	today = get_universal_date();
	days_left = license_expiration_qm && 
		FIXNUMP(license_expiration_qm) ? 
		FIXNUM_MINUS(license_expiration_qm,get_universal_date()) : 
		FIX((SI_Long)100000L);
	expired = Nil;
	will_expire = Nil;
	post_dated = Nil;
	not_authorized = Nil;
	post_message_qm = Nil;
	authorized_package_list = THIRD(Local_recovery_list);
	existing_package = Nil;
	ab_loop_list_ = Control_sequence_record;
	package_name_1 = Nil;
	start_date_qm = Nil;
	end_date_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	existing_package = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_desetq_ = assq_function(existing_package,
		authorized_package_list);
	package_name_1 = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	start_date_qm = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	end_date_qm = CAR(temp);
	if ( !TRUEP(package_name_1))
	    not_authorized = gensym_cons_1(existing_package,not_authorized);
	else if ( !TRUEP(start_date_qm));
	else if (FIXNUM_LT(end_date_qm,today))
	    expired = gensym_cons_1(existing_package,expired);
	else if (FIXNUM_LT(today,start_date_qm))
	    post_dated = gensym_cons_1(existing_package,post_dated);
	else if (end_date_qm && IFIX(end_date_qm) < IFIX(today) + 
		    (SI_Long)7L) {
	    will_expire = gensym_cons_1(existing_package,will_expire);
	    temp = FIXNUM_MINUS(end_date_qm,today);
	    days_left = FIXNUM_MIN(days_left,temp);
	}
	goto next_loop;
      end_loop:
	if ((not_authorized || expired || post_dated || 
		IFIX(Daily_countdown) <= (SI_Long)0L && 
		IFIX(Hourly_countdown) <= (SI_Long)0L) && 
		FIXNUM_NE(this_hour,Hour_of_last_message)) {
	    Hour_of_last_message = this_hour;
	    post_message_qm = T;
	}
	else if (IFIX(Daily_countdown) <= (SI_Long)0L && 
		IFIX(Hourly_countdown) > (SI_Long)0L) {
	    hours_left = (SI_Long)23L - IFIX(this_hour);
	    if (IFIX(Hourly_countdown) > hours_left) {
		Hourly_countdown = FIX(hours_left);
		post_message_qm = T;
	    }
	}
	else if (FIXNUM_GT(Daily_countdown,days_left)) {
	    Daily_countdown = days_left;
	    post_message_qm = T;
	}
	if (post_message_qm) {
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
		      if (license_expiration_qm) {
			  if (FIXNUM_LT(license_expiration_qm,today))
			      tformat(1,
				      license_on_this_machine_has_expired_ok_message());
			  if (FIXNUM_EQ(license_expiration_qm,today))
			      tformat(1,
				      licence_on_this_machine_expires_today_ok_message());
			  arg = IFIX(today);
			  arg_1 = IFIX(license_expiration_qm);
			  arg_2 = IFIX(today) + (SI_Long)7L;
			  if (arg < arg_1 && arg_1 < arg_2) {
			      twrite(string_constant_9);
			      result = decode_universal_date(license_expiration_qm);
			      MVS_3(result,day,month,year);
			      print_decoded_date(day,month,year);
			      tformat(1,string_constant_10);
			  }
		      }
		      if (not_authorized) {
			  tformat(1,string_constant_11);
			  print_list_without_message(not_authorized);
		      }
		      if (expired) {
			  tformat(1,string_constant_12);
			  print_list_without_message(expired);
		      }
		      if (post_dated) {
			  tformat(1,string_constant_13);
			  print_list_without_message(post_dated);
		      }
		      if (will_expire) {
			  print_list_without_message(will_expire);
			  tformat(1,string_constant_14);
		      }
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    post_prominent_notification(1,temp);
	}
	reclaim_gensym_list_1(not_authorized);
	reclaim_gensym_list_1(expired);
	reclaim_gensym_list_1(post_dated);
	reclaim_gensym_list_1(will_expire);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qdo_legacy_multisecond_heartbeat_adjustments;  /* do-legacy-multisecond-heartbeat-adjustments */

/* SCHEDULE-G2-LEGACY-HEARTBEAT-TASKS-IF-NECESSARY */
Object schedule_g2_legacy_heartbeat_tasks_if_necessary()
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, temp_1, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,18);
    schedule_tw_modernization_tasks_if_necessary();
    schedule_task_qm = Countdown_for_checking;
    if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
	    EQ(schedule_task_qm,Current_schedule_task)))) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = Countdown_for_checking;
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,temp_1) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp_1 = ISVREF(task,(SI_Long)1L);
	temp = Legacy_multisecond_heartbeat_adjustment_interval;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp);
	DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	temp = Legacy_multisecond_heartbeat_adjustment_priority;
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(T);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = 
		Qdo_legacy_multisecond_heartbeat_adjustments;
	temp = SYMBOL_FUNCTION(Qdo_legacy_multisecond_heartbeat_adjustments);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SYMBOL(Qcountdown_for_checking,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = new_1;
	}
	goto next_loop;
      end_loop:
      end_1:;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Place_for_for_telewindows_modernization, Qplace_for_for_telewindows_modernization);

Object Priority_for_telewindows_modernization = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Interval_for_telewindows_modernization, Qinterval_for_telewindows_modernization);

/* INITIALIZE-INTERVAL-FOR-TELEWINDOWS-MODERNIZATION */
Object initialize_interval_for_telewindows_modernization()
{
    Object temp;

    x_note_fn_call(183,19);
    temp = FIX((SI_Long)14L + IFIX(l_random(FIX((SI_Long)5L),_)));
    return VALUES_1(temp);
}

/* DO-LEGACY-SUBSECOND-HEARTBEAT-ADJUSTMENTS */
Object do_legacy_subsecond_heartbeat_adjustments()
{
    x_note_fn_call(183,20);
    optimize_telewindows_z_layer_model();
    start_adaptive_font_fallback();
    invoke_interlace_abstraction_if_offered();
    return VALUES_1(Nil);
}

static Object Qdo_legacy_subsecond_heartbeat_adjustments;  /* do-legacy-subsecond-heartbeat-adjustments */

/* SCHEDULE-TW-MODERNIZATION-TASKS-IF-NECESSARY */
Object schedule_tw_modernization_tasks_if_necessary()
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp, svref_arg_2, svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,21);
    if (scheduler_enabled_p()) {
	schedule_task_qm = Place_for_for_telewindows_modernization;
	if ( !(schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) 
		|| EQ(schedule_task_qm,Current_schedule_task)))) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = Place_for_for_telewindows_modernization;
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
		    + (double)IFIX(Interval_for_telewindows_modernization);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !TRUEP(T);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    temp = Priority_for_telewindows_modernization;
	    SVREF(task,FIX((SI_Long)4L)) = temp;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qdo_legacy_subsecond_heartbeat_adjustments;
	    temp = SYMBOL_FUNCTION(Qdo_legacy_subsecond_heartbeat_adjustments);
	    SVREF(task,FIX((SI_Long)8L)) = temp;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	    new_1 = task;
	    if (CAS_SYMBOL(Qplace_for_for_telewindows_modernization,old,
			new_1)) {
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
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Multiplicative_counter_for_evaluation, Qmultiplicative_counter_for_evaluation);

Object Modulus_counter_for_evaluation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Previous_modulus_counter_for_evaluation, Qprevious_modulus_counter_for_evaluation);

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object Qtask_fragmentation_map_1;  /* task-fragmentation-map-1 */

static Object Qtask_fragmentation_map_2;  /* task-fragmentation-map-2 */

static Object Qtask_fragmentation_map_3;  /* task-fragmentation-map-3 */

static Object Qtask_fragmentation_map_4;  /* task-fragmentation-map-4 */

static Object Qtask_fragmentation_map_5;  /* task-fragmentation-map-5 */

static Object string_constant_15;  /* "~a-~a-~a" */

static Object Qab_format;          /* format */

/* ADJUST-COUNTERS-FOR-EVALUATION */
Object adjust_counters_for_evaluation(do_task_1_p,do_task_2_p)
    Object do_task_1_p, do_task_2_p;
{
    Object new_guardian_2, old_guardian_1_qm, old_guardian_2_qm;
    Object clock_setback_time, setback_remaining;
    volatile Object timestamp;
    volatile Object raw_field_list;
    Object timestamp_1, fix_time, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_iter_flag_, gensymed_symbol, gensymed_symbol_1;
    Object circularity_point, temp_1, raw_field, ab_loop_list_;
    Object timestamp_field, temp_3, timestamp_cons, encrypted_timestamp_field;
    Object rotator_list, rotator, ab_loop_list__1, logrotate_in_place_arg_1;
    Object svref_new_value, last_setback_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol_3;
    SI_Long new_guardian_1;
    SI_Long total_setback_time, ab_loop_repeat_, index_1, shift_amount, temp_2;
    SI_Long offset, logrotate_in_place_arg_2, bv16_length, aref_new_value;
    SI_Long length_1, gensymed_symbol_2, ab_loop_bind_;
    char temp_4;
    double time_1, temp;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(183,22);
    SAVE_STACK();
    if (do_task_1_p) {
	if (Separate_imminent_actions_p) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		time_1 = g2ext_unix_time_as_float();
		new_guardian_1 = inline_floor_1(539303.90625 + 
			g2ext_unix_time_as_float() / 4096.0);
		temp = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		new_guardian_2 = 
			logand(lfloor(DOUBLE_TO_DOUBLE_FLOAT(time_1 + 
			temp),_),FIX((SI_Long)4095L));
		old_guardian_1_qm = ISVREF(Debugging_parameters,(SI_Long)28L);
		old_guardian_2_qm = ISVREF(Debugging_parameters,(SI_Long)29L);
		if (old_guardian_1_qm && old_guardian_2_qm && 
			(new_guardian_1 < IFIX(old_guardian_1_qm) || 
			new_guardian_1 == IFIX(old_guardian_1_qm) && 
			NUM_LT(new_guardian_2,old_guardian_2_qm))) {
		    clock_setback_time = add(FIX(IFIX(old_guardian_1_qm) - 
			    new_guardian_1 << (SI_Long)12L),
			    minus(old_guardian_2_qm,new_guardian_2));
		    setback_remaining = FIXNUM_MINUS(Most_positive_fixnum,
			    Current_inner_procedure_loop_cache_index);
		    total_setback_time = FIXNUM_GT(clock_setback_time,
			    setback_remaining) ? 
			    IFIX(Most_positive_fixnum) : 
			    IFIX(FIXNUM_ADD(clock_setback_time,
			    Current_inner_procedure_loop_cache_index));
		    if (total_setback_time > (SI_Long)86400L) {
			Engage_context_pipelining_p = T;
			Current_inner_procedure_loop_cache_index = 
				FIX(total_setback_time);
			timestamp = Qunbound_in_protected_let;
			if (PUSH_UNWIND_PROTECT(2)) {
			    raw_field_list = Qunbound_in_protected_let;
			    timestamp_1 = Qunbound_in_protected_let;
			    if (PUSH_UNWIND_PROTECT(1)) {
				ab_loop_repeat_ = (SI_Long)5L;
				temp = 
					DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
				fix_time = 
					lfloor(DOUBLE_TO_DOUBLE_FLOAT(time_1 
					+ temp),_);
				index_1 = (SI_Long)4L;
				shift_amount = (SI_Long)-28L;
				ab_loopvar_ = Nil;
				ab_loopvar__1 = Nil;
				ab_loopvar__2 = Nil;
				ab_loop_iter_flag_ = T;
			      next_loop:
				if ( !((SI_Long)0L < ab_loop_repeat_))
				    goto end_loop;
				ab_loop_repeat_ = ab_loop_repeat_ - 
					(SI_Long)1L;
				if ( !TRUEP(ab_loop_iter_flag_)) {
				    index_1 = index_1 - (SI_Long)1L;
				    shift_amount = shift_amount + (SI_Long)7L;
				}
				ab_loopvar__2 = 
					timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
					index_1),fix_time),
					FIX(shift_amount)),Nil);
				if (ab_loopvar__1)
				    M_CDR(ab_loopvar__1) = ab_loopvar__2;
				else
				    ab_loopvar_ = ab_loopvar__2;
				ab_loopvar__1 = ab_loopvar__2;
				ab_loop_iter_flag_ = Nil;
				goto next_loop;
			      end_loop:
				raw_field_list = ab_loopvar_;
				goto end_1;
				raw_field_list = Qnil;
			      end_1:;
				gensymed_symbol = 
					make_timestamp_list_1(FIX((SI_Long)5L));
				gensymed_symbol_1 = gensymed_symbol;
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				timestamp_1 = gensymed_symbol;
				circularity_point = 
					FIXNUM_SUB1(length(timestamp_1));
				temp_1 = nthcdr(circularity_point,timestamp_1);
				M_CDR(temp_1) = timestamp_1;
				if (PUSH_UNWIND_PROTECT(0)) {
				    raw_field = Nil;
				    ab_loop_list_ = raw_field_list;
				  next_loop_1:
				    if ( !TRUEP(ab_loop_list_))
					goto end_loop_1;
				    raw_field = M_CAR(ab_loop_list_);
				    ab_loop_list_ = M_CDR(ab_loop_list_);
				    ab_loop_repeat_ = (SI_Long)7L;
				  next_loop_2:
				    if ( !((SI_Long)0L < ab_loop_repeat_))
					goto end_loop_2;
				    ab_loop_repeat_ = ab_loop_repeat_ - 
					    (SI_Long)1L;
				    timestamp_field = CAR(timestamp_1);
				    temp_2 = oddp(raw_field) ? 
					    IFIX(ash(timestamp_field,
					    FIX((SI_Long)1L))) | 
					    (SI_Long)1L : 
					    IFIX(timestamp_field) << 
					    (SI_Long)1L;
				    M_CAR(timestamp_1) = FIX(temp_2);
				    timestamp_1 = CDR(timestamp_1);
				    raw_field = FIX(IFIX(raw_field) >>  -  
					    - (SI_Long)1L);
				    goto next_loop_2;
				  end_loop_2:;
				    goto next_loop_1;
				  end_loop_1:
				    temp_3 = timestamp_1;
				    goto end_2;
				    temp_3 = Qnil;
				  end_2:;
				    SAVE_VALUES(VALUES_1(temp_3));
				}
				POP_UNWIND_PROTECT(0);
				temp_1 = nthcdr(circularity_point,timestamp_1);
				M_CDR(temp_1) = Nil;
				CONTINUE_UNWINDING(0);
				result = RESTORE_VALUES();
				SAVE_VALUES(VALUES_1(result));
			    }
			    POP_UNWIND_PROTECT(1);
			    if (raw_field_list) {
				if ( !EQ(raw_field_list,
					Qunbound_in_protected_let))
				    reclaim_timestamp_list_1(raw_field_list);
			    }
			    CONTINUE_UNWINDING(1);
			    result = RESTORE_VALUES();
			    timestamp_1 = result;
			    timestamp_field = Nil;
			    ab_loop_list_ = timestamp_1;
			    timestamp_cons = timestamp_1;
			    ab_loop_iter_flag_ = T;
			  next_loop_3:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_3;
			    timestamp_field = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    if ( !TRUEP(ab_loop_iter_flag_))
				timestamp_cons = M_CDR(timestamp_cons);
			    if ( !TRUEP(timestamp_cons))
				goto end_loop_3;
			    encrypted_timestamp_field = logiorn(3,
				    ash(timestamp_field,FIX((SI_Long)0L)),
				    ash(timestamp_field,FIX((SI_Long)7L)),
				    ash(timestamp_field,FIX((SI_Long)14L)));
			    gensymed_symbol = 
				    make_timestamp_list_1(FIX((SI_Long)7L));
			    gensymed_symbol_1 = gensymed_symbol;
			    temp_1 = THIRD(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SIXTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SEVENTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SECOND(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FIRST(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FIFTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FOURTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    rotator_list = gensymed_symbol;
			    rotator = Nil;
			    ab_loop_list__1 = rotator_list;
			    offset = (SI_Long)0L;
			    ab_loop_iter_flag_ = T;
			  next_loop_4:
			    if ( !TRUEP(ab_loop_list__1))
				goto end_loop_4;
			    rotator = M_CAR(ab_loop_list__1);
			    ab_loop_list__1 = M_CDR(ab_loop_list__1);
			    if ( !TRUEP(ab_loop_iter_flag_))
				offset = offset + (SI_Long)3L;
			    logrotate_in_place_arg_1 = rotator;
			    logrotate_in_place_arg_2 = offset;
			    encrypted_timestamp_field = 
				    assemble_uncached_compound_method_flags(encrypted_timestamp_field,
				    logrotate_in_place_arg_1,
				    FIX(logrotate_in_place_arg_2),
				    FIX((SI_Long)3L));
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop_4;
			  end_loop_4:;
			    reclaim_timestamp_list_1(rotator_list);
			    M_CAR(timestamp_cons) = encrypted_timestamp_field;
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop_3;
			  end_loop_3:
			    timestamp = timestamp_1;
			    goto end_3;
			    timestamp = Qnil;
			  end_3:;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FIRST(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_1);
			    SVREF(temp_1,FIX((SI_Long)23L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = SECOND(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_2);
			    SVREF(temp_1,FIX((SI_Long)24L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = THIRD(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_3);
			    SVREF(temp_1,FIX((SI_Long)25L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FOURTH(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_4);
			    SVREF(temp_1,FIX((SI_Long)26L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FIFTH(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_5);
			    SVREF(temp_1,FIX((SI_Long)27L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    ISVREF(temp_1,(SI_Long)28L) = 
				    LONG_TO_FIXNUM(new_guardian_1);
			    temp_1 = Debugging_parameters;
			    ISVREF(temp_1,(SI_Long)29L) = new_guardian_2;
			}
			POP_UNWIND_PROTECT(2);
			if (timestamp) {
			    if ( !EQ(timestamp,Qunbound_in_protected_let))
				reclaim_timestamp_list_1(timestamp);
			}
			CONTINUE_UNWINDING(2);
		    }
		    else {
			Current_inner_procedure_loop_cache_index = 
				FIX(total_setback_time);
			timestamp = Qunbound_in_protected_let;
			if (PUSH_UNWIND_PROTECT(2)) {
			    raw_field_list = Qunbound_in_protected_let;
			    timestamp_1 = Qunbound_in_protected_let;
			    if (PUSH_UNWIND_PROTECT(1)) {
				ab_loop_repeat_ = (SI_Long)5L;
				temp = 
					DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
				fix_time = 
					lfloor(DOUBLE_TO_DOUBLE_FLOAT(time_1 
					+ temp),_);
				index_1 = (SI_Long)4L;
				shift_amount = (SI_Long)-28L;
				ab_loopvar_ = Nil;
				ab_loopvar__1 = Nil;
				ab_loopvar__2 = Nil;
				ab_loop_iter_flag_ = T;
			      next_loop_5:
				if ( !((SI_Long)0L < ab_loop_repeat_))
				    goto end_loop_5;
				ab_loop_repeat_ = ab_loop_repeat_ - 
					(SI_Long)1L;
				if ( !TRUEP(ab_loop_iter_flag_)) {
				    index_1 = index_1 - (SI_Long)1L;
				    shift_amount = shift_amount + (SI_Long)7L;
				}
				ab_loopvar__2 = 
					timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
					index_1),fix_time),
					FIX(shift_amount)),Nil);
				if (ab_loopvar__1)
				    M_CDR(ab_loopvar__1) = ab_loopvar__2;
				else
				    ab_loopvar_ = ab_loopvar__2;
				ab_loopvar__1 = ab_loopvar__2;
				ab_loop_iter_flag_ = Nil;
				goto next_loop_5;
			      end_loop_5:
				raw_field_list = ab_loopvar_;
				goto end_4;
				raw_field_list = Qnil;
			      end_4:;
				gensymed_symbol = 
					make_timestamp_list_1(FIX((SI_Long)5L));
				gensymed_symbol_1 = gensymed_symbol;
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
				M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
				timestamp_1 = gensymed_symbol;
				circularity_point = 
					FIXNUM_SUB1(length(timestamp_1));
				temp_1 = nthcdr(circularity_point,timestamp_1);
				M_CDR(temp_1) = timestamp_1;
				if (PUSH_UNWIND_PROTECT(0)) {
				    raw_field = Nil;
				    ab_loop_list_ = raw_field_list;
				  next_loop_6:
				    if ( !TRUEP(ab_loop_list_))
					goto end_loop_6;
				    raw_field = M_CAR(ab_loop_list_);
				    ab_loop_list_ = M_CDR(ab_loop_list_);
				    ab_loop_repeat_ = (SI_Long)7L;
				  next_loop_7:
				    if ( !((SI_Long)0L < ab_loop_repeat_))
					goto end_loop_7;
				    ab_loop_repeat_ = ab_loop_repeat_ - 
					    (SI_Long)1L;
				    timestamp_field = CAR(timestamp_1);
				    temp_2 = oddp(raw_field) ? 
					    IFIX(ash(timestamp_field,
					    FIX((SI_Long)1L))) | 
					    (SI_Long)1L : 
					    IFIX(timestamp_field) << 
					    (SI_Long)1L;
				    M_CAR(timestamp_1) = FIX(temp_2);
				    timestamp_1 = CDR(timestamp_1);
				    raw_field = FIX(IFIX(raw_field) >>  -  
					    - (SI_Long)1L);
				    goto next_loop_7;
				  end_loop_7:;
				    goto next_loop_6;
				  end_loop_6:
				    temp_3 = timestamp_1;
				    goto end_5;
				    temp_3 = Qnil;
				  end_5:;
				    SAVE_VALUES(VALUES_1(temp_3));
				}
				POP_UNWIND_PROTECT(0);
				temp_1 = nthcdr(circularity_point,timestamp_1);
				M_CDR(temp_1) = Nil;
				CONTINUE_UNWINDING(0);
				result = RESTORE_VALUES();
				SAVE_VALUES(VALUES_1(result));
			    }
			    POP_UNWIND_PROTECT(1);
			    if (raw_field_list) {
				if ( !EQ(raw_field_list,
					Qunbound_in_protected_let))
				    reclaim_timestamp_list_1(raw_field_list);
			    }
			    CONTINUE_UNWINDING(1);
			    result = RESTORE_VALUES();
			    timestamp_1 = result;
			    timestamp_field = Nil;
			    ab_loop_list_ = timestamp_1;
			    timestamp_cons = timestamp_1;
			    ab_loop_iter_flag_ = T;
			  next_loop_8:
			    if ( !TRUEP(ab_loop_list_))
				goto end_loop_8;
			    timestamp_field = M_CAR(ab_loop_list_);
			    ab_loop_list_ = M_CDR(ab_loop_list_);
			    if ( !TRUEP(ab_loop_iter_flag_))
				timestamp_cons = M_CDR(timestamp_cons);
			    if ( !TRUEP(timestamp_cons))
				goto end_loop_8;
			    encrypted_timestamp_field = logiorn(3,
				    ash(timestamp_field,FIX((SI_Long)0L)),
				    ash(timestamp_field,FIX((SI_Long)7L)),
				    ash(timestamp_field,FIX((SI_Long)14L)));
			    gensymed_symbol = 
				    make_timestamp_list_1(FIX((SI_Long)7L));
			    gensymed_symbol_1 = gensymed_symbol;
			    temp_1 = THIRD(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SIXTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SEVENTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = SECOND(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FIRST(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FIFTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    temp_1 = FOURTH(Embedded_fuzzy_conditionals_list);
			    M_CAR(gensymed_symbol_1) = temp_1;
			    rotator_list = gensymed_symbol;
			    rotator = Nil;
			    ab_loop_list__1 = rotator_list;
			    offset = (SI_Long)0L;
			    ab_loop_iter_flag_ = T;
			  next_loop_9:
			    if ( !TRUEP(ab_loop_list__1))
				goto end_loop_9;
			    rotator = M_CAR(ab_loop_list__1);
			    ab_loop_list__1 = M_CDR(ab_loop_list__1);
			    if ( !TRUEP(ab_loop_iter_flag_))
				offset = offset + (SI_Long)3L;
			    logrotate_in_place_arg_1 = rotator;
			    logrotate_in_place_arg_2 = offset;
			    encrypted_timestamp_field = 
				    assemble_uncached_compound_method_flags(encrypted_timestamp_field,
				    logrotate_in_place_arg_1,
				    FIX(logrotate_in_place_arg_2),
				    FIX((SI_Long)3L));
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop_9;
			  end_loop_9:;
			    reclaim_timestamp_list_1(rotator_list);
			    M_CAR(timestamp_cons) = encrypted_timestamp_field;
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop_8;
			  end_loop_8:
			    timestamp = timestamp_1;
			    goto end_6;
			    timestamp = Qnil;
			  end_6:;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FIRST(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_1);
			    SVREF(temp_1,FIX((SI_Long)23L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = SECOND(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_2);
			    SVREF(temp_1,FIX((SI_Long)24L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = THIRD(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_3);
			    SVREF(temp_1,FIX((SI_Long)25L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FOURTH(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_4);
			    SVREF(temp_1,FIX((SI_Long)26L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    svref_new_value = FIFTH(timestamp);
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(temp_1,
					Qtask_fragmentation_map_5);
			    SVREF(temp_1,FIX((SI_Long)27L)) = svref_new_value;
			    temp_1 = Debugging_parameters;
			    ISVREF(temp_1,(SI_Long)28L) = 
				    LONG_TO_FIXNUM(new_guardian_1);
			    temp_1 = Debugging_parameters;
			    ISVREF(temp_1,(SI_Long)29L) = new_guardian_2;
			}
			POP_UNWIND_PROTECT(2);
			if (timestamp) {
			    if ( !EQ(timestamp,Qunbound_in_protected_let))
				reclaim_timestamp_list_1(timestamp);
			}
			CONTINUE_UNWINDING(2);
			last_setback_qm = ISVREF(Debugging_parameters,
				(SI_Long)30L);
			if ( !TRUEP(last_setback_qm) || new_guardian_1 - 
				IFIX(last_setback_qm) >= (SI_Long)7698L) {
			    if (last_setback_qm && 
				    IFIX(Current_inner_procedure_loop_cache_index) 
				    >= (SI_Long)3600L) {
				temp_2 = 
					IFIX(Current_inner_procedure_loop_cache_index) 
					- (SI_Long)3600L;
				Current_inner_procedure_loop_cache_index = 
					FIX(temp_2);
			    }
			    temp_1 = Debugging_parameters;
			    ISVREF(temp_1,(SI_Long)30L) = 
				    LONG_TO_FIXNUM(new_guardian_1);
			}
		    }
		}
		else {
		    timestamp = Qunbound_in_protected_let;
		    if (PUSH_UNWIND_PROTECT(2)) {
			raw_field_list = Qunbound_in_protected_let;
			timestamp_1 = Qunbound_in_protected_let;
			if (PUSH_UNWIND_PROTECT(1)) {
			    ab_loop_repeat_ = (SI_Long)5L;
			    temp = 
				    DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
			    fix_time = 
				    lfloor(DOUBLE_TO_DOUBLE_FLOAT(time_1 + 
				    temp),_);
			    index_1 = (SI_Long)4L;
			    shift_amount = (SI_Long)-28L;
			    ab_loopvar_ = Nil;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			    ab_loop_iter_flag_ = T;
			  next_loop_10:
			    if ( !((SI_Long)0L < ab_loop_repeat_))
				goto end_loop_10;
			    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			    if ( !TRUEP(ab_loop_iter_flag_)) {
				index_1 = index_1 - (SI_Long)1L;
				shift_amount = shift_amount + (SI_Long)7L;
			    }
			    ab_loopvar__2 = 
				    timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
				    index_1),fix_time),FIX(shift_amount)),Nil);
			    if (ab_loopvar__1)
				M_CDR(ab_loopvar__1) = ab_loopvar__2;
			    else
				ab_loopvar_ = ab_loopvar__2;
			    ab_loopvar__1 = ab_loopvar__2;
			    ab_loop_iter_flag_ = Nil;
			    goto next_loop_10;
			  end_loop_10:
			    raw_field_list = ab_loopvar_;
			    goto end_7;
			    raw_field_list = Qnil;
			  end_7:;
			    gensymed_symbol = 
				    make_timestamp_list_1(FIX((SI_Long)5L));
			    gensymed_symbol_1 = gensymed_symbol;
			    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
			    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			    M_CAR(gensymed_symbol_1) = FIX((SI_Long)0L);
			    timestamp_1 = gensymed_symbol;
			    circularity_point = 
				    FIXNUM_SUB1(length(timestamp_1));
			    temp_1 = nthcdr(circularity_point,timestamp_1);
			    M_CDR(temp_1) = timestamp_1;
			    if (PUSH_UNWIND_PROTECT(0)) {
				raw_field = Nil;
				ab_loop_list_ = raw_field_list;
			      next_loop_11:
				if ( !TRUEP(ab_loop_list_))
				    goto end_loop_11;
				raw_field = M_CAR(ab_loop_list_);
				ab_loop_list_ = M_CDR(ab_loop_list_);
				ab_loop_repeat_ = (SI_Long)7L;
			      next_loop_12:
				if ( !((SI_Long)0L < ab_loop_repeat_))
				    goto end_loop_12;
				ab_loop_repeat_ = ab_loop_repeat_ - 
					(SI_Long)1L;
				timestamp_field = CAR(timestamp_1);
				temp_2 = oddp(raw_field) ? 
					IFIX(ash(timestamp_field,
					FIX((SI_Long)1L))) | (SI_Long)1L : 
					IFIX(timestamp_field) << (SI_Long)1L;
				M_CAR(timestamp_1) = FIX(temp_2);
				timestamp_1 = CDR(timestamp_1);
				raw_field = FIX(IFIX(raw_field) >>  -  - 
					(SI_Long)1L);
				goto next_loop_12;
			      end_loop_12:;
				goto next_loop_11;
			      end_loop_11:
				temp_3 = timestamp_1;
				goto end_8;
				temp_3 = Qnil;
			      end_8:;
				SAVE_VALUES(VALUES_1(temp_3));
			    }
			    POP_UNWIND_PROTECT(0);
			    temp_1 = nthcdr(circularity_point,timestamp_1);
			    M_CDR(temp_1) = Nil;
			    CONTINUE_UNWINDING(0);
			    result = RESTORE_VALUES();
			    SAVE_VALUES(VALUES_1(result));
			}
			POP_UNWIND_PROTECT(1);
			if (raw_field_list) {
			    if ( !EQ(raw_field_list,Qunbound_in_protected_let))
				reclaim_timestamp_list_1(raw_field_list);
			}
			CONTINUE_UNWINDING(1);
			result = RESTORE_VALUES();
			timestamp_1 = result;
			timestamp_field = Nil;
			ab_loop_list_ = timestamp_1;
			timestamp_cons = timestamp_1;
			ab_loop_iter_flag_ = T;
		      next_loop_13:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_13;
			timestamp_field = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if ( !TRUEP(ab_loop_iter_flag_))
			    timestamp_cons = M_CDR(timestamp_cons);
			if ( !TRUEP(timestamp_cons))
			    goto end_loop_13;
			encrypted_timestamp_field = logiorn(3,
				ash(timestamp_field,FIX((SI_Long)0L)),
				ash(timestamp_field,FIX((SI_Long)7L)),
				ash(timestamp_field,FIX((SI_Long)14L)));
			gensymed_symbol = 
				make_timestamp_list_1(FIX((SI_Long)7L));
			gensymed_symbol_1 = gensymed_symbol;
			temp_1 = THIRD(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = SIXTH(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = SEVENTH(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = SECOND(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = FIRST(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = FIFTH(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			temp_1 = FOURTH(Embedded_fuzzy_conditionals_list);
			M_CAR(gensymed_symbol_1) = temp_1;
			rotator_list = gensymed_symbol;
			rotator = Nil;
			ab_loop_list__1 = rotator_list;
			offset = (SI_Long)0L;
			ab_loop_iter_flag_ = T;
		      next_loop_14:
			if ( !TRUEP(ab_loop_list__1))
			    goto end_loop_14;
			rotator = M_CAR(ab_loop_list__1);
			ab_loop_list__1 = M_CDR(ab_loop_list__1);
			if ( !TRUEP(ab_loop_iter_flag_))
			    offset = offset + (SI_Long)3L;
			logrotate_in_place_arg_1 = rotator;
			logrotate_in_place_arg_2 = offset;
			encrypted_timestamp_field = 
				assemble_uncached_compound_method_flags(encrypted_timestamp_field,
				logrotate_in_place_arg_1,
				FIX(logrotate_in_place_arg_2),
				FIX((SI_Long)3L));
			ab_loop_iter_flag_ = Nil;
			goto next_loop_14;
		      end_loop_14:;
			reclaim_timestamp_list_1(rotator_list);
			M_CAR(timestamp_cons) = encrypted_timestamp_field;
			ab_loop_iter_flag_ = Nil;
			goto next_loop_13;
		      end_loop_13:
			timestamp = timestamp_1;
			goto end_9;
			timestamp = Qnil;
		      end_9:;
			temp_1 = Debugging_parameters;
			svref_new_value = FIRST(timestamp);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(temp_1,
				    Qtask_fragmentation_map_1);
			SVREF(temp_1,FIX((SI_Long)23L)) = svref_new_value;
			temp_1 = Debugging_parameters;
			svref_new_value = SECOND(timestamp);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(temp_1,
				    Qtask_fragmentation_map_2);
			SVREF(temp_1,FIX((SI_Long)24L)) = svref_new_value;
			temp_1 = Debugging_parameters;
			svref_new_value = THIRD(timestamp);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(temp_1,
				    Qtask_fragmentation_map_3);
			SVREF(temp_1,FIX((SI_Long)25L)) = svref_new_value;
			temp_1 = Debugging_parameters;
			svref_new_value = FOURTH(timestamp);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(temp_1,
				    Qtask_fragmentation_map_4);
			SVREF(temp_1,FIX((SI_Long)26L)) = svref_new_value;
			temp_1 = Debugging_parameters;
			svref_new_value = FIFTH(timestamp);
			if (Noting_changes_to_kb_p)
			    note_change_to_block_1(temp_1,
				    Qtask_fragmentation_map_5);
			SVREF(temp_1,FIX((SI_Long)27L)) = svref_new_value;
			temp_1 = Debugging_parameters;
			ISVREF(temp_1,(SI_Long)28L) = 
				LONG_TO_FIXNUM(new_guardian_1);
			temp_1 = Debugging_parameters;
			ISVREF(temp_1,(SI_Long)29L) = new_guardian_2;
		    }
		    POP_UNWIND_PROTECT(2);
		    if (timestamp) {
			if ( !EQ(timestamp,Qunbound_in_protected_let))
			    reclaim_timestamp_list_1(timestamp);
		    }
		    CONTINUE_UNWINDING(2);
		}
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	temp_1 = 
		chestnut_modf_function(Counter_for_sleep_management_adjustment,
		FIX((SI_Long)1000L));
	Counter_for_sleep_management_adjustment = temp_1;
    }
    if (do_task_2_p) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L + 
		  (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp_2 = bv16_length - (SI_Long)2L;
	  aref_new_value = (SI_Long)2048L & (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
	  temp_2 = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp_2,aref_new_value);
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
		  tformat(4,string_constant_15,Qab_format,
			  CAR(Format_redefinition_list),
			  SECOND(Format_redefinition_list));
		  temp_3 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	gensymed_symbol = SYMBOL_VALUE(intern_text_string(1,temp_3));
	ab_loop_repeat_ = (SI_Long)15L;
	gensymed_symbol_1 = gensymed_symbol;
	ab_loop_iter_flag_ = T;
      next_loop_15:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_15;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	if ( !TRUEP(ab_loop_iter_flag_))
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	if (ATOM(gensymed_symbol_1)) {
	    temp_4 = TRUEP(Nil);
	    goto end_10;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop_15;
      end_loop_15:
	temp_4 = TRUEP(T);
	goto end_10;
	temp_4 = TRUEP(Qnil);
      end_10:;
	if (temp_4) {
	    gensymed_symbol_1 = FOURTH(gensymed_symbol);
	    gensymed_symbol = SECOND(gensymed_symbol);
	    temp_4 =  !SIMPLE_VECTOR_P(gensymed_symbol_1);
	    if (temp_4);
	    else
		temp_4 =  !(IFIX(length(gensymed_symbol_1)) >= (SI_Long)8L);
	    if (temp_4);
	    else {
		gensymed_symbol_2 = (SI_Long)0L;
		ab_loop_bind_ = IFIX(length(gensymed_symbol_1));
		gensymed_symbol_3 = Nil;
	      next_loop_16:
		if (gensymed_symbol_2 >= ab_loop_bind_)
		    goto end_loop_16;
		gensymed_symbol_3 = ISVREF(gensymed_symbol_1,
			gensymed_symbol_2);
		if ( !(FIXNUMP(gensymed_symbol_3) && (SI_Long)0L <= 
			IFIX(gensymed_symbol_3) && IFIX(gensymed_symbol_3) 
			<= (SI_Long)255L)) {
		    temp_4 = TRUEP(Nil);
		    goto end_11;
		}
		gensymed_symbol_2 = gensymed_symbol_2 + (SI_Long)1L;
		goto next_loop_16;
	      end_loop_16:
		temp_4 = TRUEP(T);
		goto end_11;
		temp_4 = TRUEP(Qnil);
	      end_11:;
		temp_4 =  !temp_4;
	    }
	    if (temp_4);
	    else
		temp_4 =  
			!TRUEP(match_machine_id_for_this_machine_online(gensymed_symbol,
			gensymed_symbol_1));
	    temp_3 = temp_4 ? Nil : T;
	    gensymed_symbol = Nil;
	    gensymed_symbol_1 = Nil;
	    gensymed_symbol = Nil;
	    temp_4 = TRUEP(temp_3);
	}
	else
	    temp_4 = TRUEP(Nil);
	if ( !temp_4) {
	    temp_1 = Default_format_structure;
	    M_THIRD(temp_1) = T;
	}
	temp_1 = 
		chestnut_modf_function(Multiplicative_counter_for_evaluation,
		FIX((SI_Long)10000L));
	Multiplicative_counter_for_evaluation = temp_1;
	RESTORE_STACK();
	return VALUES_1(Multiplicative_counter_for_evaluation);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object string_constant_16;  /* "This knowledge base was written within a NUPEC specialized ~
				    *                   version of G2.  The scheduler mode was NUPEC catch up, but ~
				    *                   since this is not  a NUPEC version of G2, it has been changed ~
				    *                   to real time."
				    */

static Object Qupdate_memory_limits;  /* update-memory-limits */

/* TICK-THE-CLOCK */
Object tick_the_clock(disable_caching_fixnum_time_qm)
    Object disable_caching_fixnum_time_qm;
{
    Object local_fixnum_time, time_at_start_of_previous_clock_tick, temp;
    Object real_time_ticked_qm, g2_time_ticked_qm, code;
    Object index_of_top_of_backtrace_stack, temp_3, svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    SI_Long fixnum_time_length_of_previous_tick, incff_1_arg, temp_1;
    char do_task_1_p, do_task_2_p, temp_2;
    double current_time, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(183,23);
    local_fixnum_time = c_native_clock_ticks_or_cache(T,
	    disable_caching_fixnum_time_qm);
    time_at_start_of_previous_clock_tick = Fixnum_time_of_last_g2_tick;
    if (FIXNUM_GE(local_fixnum_time,Real_time_to_tick_p_base))
	temp = FIXNUM_MINUS(local_fixnum_time,Real_time_to_tick_p_base);
    else {
	gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
		Real_time_to_tick_p_base));
	gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	temp = FIX(gensymed_symbol + (SI_Long)1L);
    }
    if (FIXNUM_GE(temp,Fixnum_time_until_real_time_tick)) {
	gensymed_symbol = IFIX(local_fixnum_time);
	gensymed_symbol_1 = IFIX(Previous_modulus_counter_for_evaluation);
	if (gensymed_symbol >= gensymed_symbol_1)
	    fixnum_time_length_of_previous_tick = gensymed_symbol - 
		    gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    fixnum_time_length_of_previous_tick = gensymed_symbol + 
		    (SI_Long)1L;
	}
	incff_1_arg = fixnum_time_length_of_previous_tick;
	temp_1 = IFIX(Counter_for_sleep_management_adjustment) + incff_1_arg;
	Counter_for_sleep_management_adjustment = FIX(temp_1);
	do_task_1_p = FIXNUM_GT(Counter_for_sleep_management_adjustment,
		Legacy_subsecond_heartbeat_adjustment_interval);
	incff_1_arg = fixnum_time_length_of_previous_tick;
	temp_1 = IFIX(Multiplicative_counter_for_evaluation) + incff_1_arg;
	Multiplicative_counter_for_evaluation = FIX(temp_1);
	do_task_2_p = FIXNUM_GT(Multiplicative_counter_for_evaluation,
		Modulus_counter_for_evaluation);
	if (do_task_1_p || do_task_2_p)
	    adjust_counters_for_evaluation(do_task_1_p ? T : Nil,
		    do_task_2_p ? T : Nil);
	Previous_modulus_counter_for_evaluation = local_fixnum_time;
	real_time_ticked_qm = tick_the_real_time_clock(local_fixnum_time);
    }
    else
	real_time_ticked_qm = Nil;
    g2_time_ticked_qm = Nil;
    temp = ISVREF(Timing_parameters,(SI_Long)22L);
    if (EQ(temp,Qreal_time)) {
	if (System_is_running) {
	    if (FIXNUM_GE(local_fixnum_time,G2_time_to_tick_p_base))
		temp = FIXNUM_MINUS(local_fixnum_time,G2_time_to_tick_p_base);
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			G2_time_to_tick_p_base));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    temp_2 = FIXNUM_GE(temp,Fixnum_time_until_g2_time_tick);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? TRUEP(tick_the_g2_real_time_clock(local_fixnum_time)) 
		: TRUEP(Nil)) {
	    if (FIXNUM_GE(local_fixnum_time,
		    time_at_start_of_previous_clock_tick))
		temp = FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick);
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    take_actions_at_start_of_clock_tick(temp);
	    g2_time_ticked_qm = T;
	}
    }
    else if (EQ(temp,Qfast_time)) {
	if (System_is_running &&  
		!TRUEP(tasks_enqueued_for_current_execution_qm()) &&  
		!TRUEP(Inhibit_non_real_time_clock_ticks_qm) && 
		tick_the_g2_fast_time_clock(local_fixnum_time)) {
	    if (FIXNUM_GE(local_fixnum_time,
		    time_at_start_of_previous_clock_tick))
		temp = FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick);
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    take_actions_at_start_of_clock_tick(temp);
	    g2_time_ticked_qm = T;
	}
    }
    else if (EQ(temp,Qsimulated_time)) {
	if (System_is_running &&  
		!TRUEP(tasks_enqueued_for_current_execution_qm()) &&  
		!TRUEP(Inhibit_non_real_time_clock_ticks_qm)) {
	    if (FIXNUM_GE(local_fixnum_time,G2_time_to_tick_p_base))
		temp = FIXNUM_MINUS(local_fixnum_time,G2_time_to_tick_p_base);
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			G2_time_to_tick_p_base));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    temp_2 = FIXNUM_GE(temp,Fixnum_time_until_g2_time_tick);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ? 
		TRUEP(tick_the_g2_simulated_time_clock(local_fixnum_time)) 
		: TRUEP(Nil)) {
	    if (FIXNUM_GE(local_fixnum_time,
		    time_at_start_of_previous_clock_tick))
		temp = FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick);
	    else {
		gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			time_at_start_of_previous_clock_tick));
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    take_actions_at_start_of_clock_tick(temp);
	    g2_time_ticked_qm = T;
	}
    }
    else if (EQ(temp,Qnupec_catch_up)) {
	code = M_CAR(M_CDR(Journal_shutout_scan_p));
	if (FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != (SI_Long)0L ? 
		TRUEP(M_CAR(M_CDR(Cache_nupec_semantics_graph))) : 
		    TRUEP(Nil)) {
	    if (System_is_running) {
		if (Nupec_catch_up_mode_caught_up_qm) {
		    if (FIXNUM_GE(local_fixnum_time,G2_time_to_tick_p_base))
			temp = FIXNUM_MINUS(local_fixnum_time,
				G2_time_to_tick_p_base);
		    else {
			gensymed_symbol = 
				IFIX(FIXNUM_MINUS(local_fixnum_time,
				G2_time_to_tick_p_base));
			gensymed_symbol = gensymed_symbol + 
				IFIX(Most_positive_fixnum);
			temp = FIX(gensymed_symbol + (SI_Long)1L);
		    }
		    temp_2 = FIXNUM_GE(temp,Fixnum_time_until_g2_time_tick);
		}
		else
		    temp_2 =  
			    !TRUEP(tasks_enqueued_for_current_execution_qm()) 
			    ?  
			    !TRUEP(Inhibit_non_real_time_clock_ticks_qm) : 
			    TRUEP(Qnil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ? 
		    TRUEP(tick_the_nupec_catch_up_clock(local_fixnum_time)) 
		    : TRUEP(Nil)) {
		if (FIXNUM_GE(local_fixnum_time,
			time_at_start_of_previous_clock_tick))
		    temp = FIXNUM_MINUS(local_fixnum_time,
			    time_at_start_of_previous_clock_tick);
		else {
		    gensymed_symbol = IFIX(FIXNUM_MINUS(local_fixnum_time,
			    time_at_start_of_previous_clock_tick));
		    gensymed_symbol = gensymed_symbol + 
			    IFIX(Most_positive_fixnum);
		    temp = FIX(gensymed_symbol + (SI_Long)1L);
		}
		take_actions_at_start_of_clock_tick(temp);
		g2_time_ticked_qm = T;
	    }
	}
	else {
	    change_slot_value(3,Timing_parameters,Qscheduler_mode,Qreal_time);
	    Suppress_warning_message_header_qm = T;
	    if ((SI_Long)1L <= IFIX(Warning_message_level))
		give_warning_1(2,FIX((SI_Long)1L),string_constant_16);
	    Suppress_warning_message_header_qm = Nil;
	}
    }
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	if (real_time_ticked_qm &&  !TRUEP(g2_time_ticked_qm))
	    unpack_future_tasks_into_current_task_queues(Nil);
    }
    POP_LOCAL_ALLOCATION(0,0);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    0);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp_3 = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp_3;
	  temp_3 = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp_3,svref_arg_2) = FIX((SI_Long)0L);
	  temp_3 = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp_3;
	  temp_3 = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp_3,svref_arg_2) = Nil;
	  temp_3 = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp_3;
	  temp_3 = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp_3,svref_arg_2) = Qupdate_memory_limits;
      }
      update_memory_limits(local_fixnum_time);
    POP_SPECIAL();
    if (Profiling_enabled_qm) {
	current_time = g2ext_unix_time_as_float();
	temp_3 = ISVREF(Profiling_enabled_qm,(SI_Long)4L);
	aref_new_value = current_time - 
		DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)2L),
		(SI_Long)0L) + DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
		(SI_Long)4L),(SI_Long)0L);
	DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value);
	temp_3 = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	DFLOAT_ISASET_1(temp_3,(SI_Long)0L,current_time);
	temp = Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qtask_execution;     /* task-execution */

/* RUN-ONE-SCHEDULER-CYCLE */
Object run_one_scheduler_cycle()
{
    Object temp, time_slice_start_time, index_of_top_of_backtrace_stack;
    Object svref_arg_2, task_scheduling_start_time;
    Object executed_task_function_name, temp_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;
    char temp_2;
    double current_time, aref_new_value;
    Declare_special(2);
    Object result;

    x_note_fn_call(183,24);
    if (Profiling_enabled_qm) {
	current_time = g2ext_unix_time_as_float();
	temp = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,current_time);
    }
    tick_the_clock(Nil);
    time_slice_start_time = FIX((SI_Long)0L);
    PUSH_SPECIAL_WITH_SYMBOL(Time_slice_start_time,Qtime_slice_start_time,time_slice_start_time,
	    1);
      index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
      PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
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
	    SVREF(temp,svref_arg_2) = Qtask_execution;
	}
	task_scheduling_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	executed_task_function_name = Nil;
	Time_slice_start_time = task_scheduling_start_time;
      next_loop:
	temp_1 = dequeue_and_execute_next_task();
	executed_task_function_name = temp_1;
	temp_2 =  !TRUEP(executed_task_function_name);
	if (temp_2);
	else {
	    Time_slice_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	    gensymed_symbol = IFIX(Time_slice_start_time);
	    gensymed_symbol_1 = IFIX(task_scheduling_start_time);
	    if (gensymed_symbol >= gensymed_symbol_1)
		temp_1 = FIX(gensymed_symbol - gensymed_symbol_1);
	    else {
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
		temp_1 = FIX(gensymed_symbol + (SI_Long)1L);
	    }
	    temp_2 = FIXNUM_GE(temp_1,Scheduled_tasks_time_limit);
	}
	if (temp_2)
	    goto end_loop;
	goto next_loop;
      end_loop:;
      POP_SPECIAL();
      if (Profiling_enabled_qm) {
	  current_time = g2ext_unix_time_as_float();
	  temp = ISVREF(Profiling_enabled_qm,(SI_Long)4L);
	  aref_new_value = current_time - 
		  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)2L),
		  (SI_Long)0L) + 
		  DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,(SI_Long)4L),
		  (SI_Long)0L);
	  DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	  temp = ISVREF(Profiling_enabled_qm,(SI_Long)2L);
	  DFLOAT_ISASET_1(temp,(SI_Long)0L,current_time);
      }
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object G2_meters_scheduler_time_lag_variable_names_format = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Priority_1_last_gensym_time, Qpriority_1_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_2_last_gensym_time, Qpriority_2_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_3_last_gensym_time, Qpriority_3_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_4_last_gensym_time, Qpriority_4_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_5_last_gensym_time, Qpriority_5_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_6_last_gensym_time, Qpriority_6_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_7_last_gensym_time, Qpriority_7_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_8_last_gensym_time, Qpriority_8_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_9_last_gensym_time, Qpriority_9_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Priority_10_last_gensym_time, Qpriority_10_last_gensym_time);

DEFINE_VARIABLE_WITH_SYMBOL(Meter_lag_time_variables, Qmeter_lag_time_variables);

DEFINE_VARIABLE_WITH_SYMBOL(G2_meter_task_count, Qg2_meter_task_count);

/* UPDATE-SCHEDULER-TIME-LAG */
Object update_scheduler_time_lag(lag_meter,schedule_time)
    Object lag_meter, schedule_time;
{
    Object g2_meter_task_count_new_value;

    x_note_fn_call(183,25);
    g2_meter_task_count_new_value = FIXNUM_SUB1(G2_meter_task_count);
    G2_meter_task_count = g2_meter_task_count_new_value;
    return set(lag_meter,schedule_time);
}

/* RESET-ALL-SCHEDULER-LAG-TIME-VARIABLES */
Object reset_all_scheduler_lag_time_variables()
{
    Object variable, ab_loop_list_, symbol_value_new_value;

    x_note_fn_call(183,26);
    variable = Nil;
    ab_loop_list_ = Meter_lag_time_variables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    symbol_value_new_value = Gensym_time;
    set(variable,symbol_value_new_value);
    goto next_loop;
  end_loop:;
    G2_meter_task_count = FIX((SI_Long)0L);
    return VALUES_1(G2_meter_task_count);
}

/* SCHEDULE-TASKS-FOR-UPDATING-G2-METERS-LAST-GENSYM-TIMES */
Object schedule_tasks_for_updating_g2_meters_last_gensym_times()
{
    x_note_fn_call(183,27);
    return VALUES_1(Nil);
}

Object Recursive_attribute_nesting_has_occurred_qm = UNBOUND;

static Object Qunload_scheduler_into_current_queue;  /* unload-scheduler-into-current-queue */

static Object Qg2_meter_data_service_on_qm;  /* g2-meter-data-service-on? */

/* TAKE-ACTIONS-AT-START-OF-CLOCK-TICK */
Object take_actions_at_start_of_clock_tick(fixnum_time_length_of_previous_tick)
    Object fixnum_time_length_of_previous_tick;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(183,28);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
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
	  SVREF(temp,svref_arg_2) = Qunload_scheduler_into_current_queue;
      }
      unpack_future_tasks_into_current_task_queues(T);
    POP_SPECIAL();
    if (get_lookup_slot_value_given_default(Data_server_parameters,
	    Qg2_meter_data_service_on_qm,Nil)) {
	update_meter_values(fixnum_time_length_of_previous_tick);
	schedule_tasks_for_updating_g2_meters_last_gensym_times();
    }
    reset_debugging_parameters();
    Recursive_attribute_nesting_has_occurred_qm = Nil;
    return VALUES_1(Recursive_attribute_nesting_has_occurred_qm);
}

Object Data_server_accept_data_task = UNBOUND;

static Object Qcall_data_server_accept_data_functions;  /* call-data-server-accept-data-functions */

static Object Qdata_server_accept_data_task;  /* data-server-accept-data-task */

/* SCHEDULE-DATA-SERVER-ACCEPT-DATA-CALLS */
Object schedule_data_server_accept_data_calls()
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    char svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,29);
    if (System_is_running || System_has_paused) {
	if ( !(Data_server_accept_data_task && 
		(ISVREF(Data_server_accept_data_task,(SI_Long)6L) || 
		EQ(Data_server_accept_data_task,Current_schedule_task))) 
		|| Data_server_accept_data_task && 
		EQ(Data_server_accept_data_task,Current_schedule_task)) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = Data_server_accept_data_task;
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
	    aref_new_value = 
		    inline_ffloor_1(DFLOAT_ISAREF_1(Current_g2_time,
		    (SI_Long)0L)) + 1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !TRUEP(Nil);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	    SVREF(task,FIX((SI_Long)4L)) = temp;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qcall_data_server_accept_data_functions;
	    temp = SYMBOL_FUNCTION(Qcall_data_server_accept_data_functions);
	    SVREF(task,FIX((SI_Long)8L)) = temp;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	    new_1 = task;
	    if (CAS_SYMBOL(Qdata_server_accept_data_task,old,new_1)) {
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
    return VALUES_1(Nil);
}

/* SCHEDULE-IMMEDIATE-DATA-SERVER-ACCEPT-DATA-CALLS */
Object schedule_immediate_data_server_accept_data_calls()
{
    Object old, new_1, def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,30);
    if (System_is_running || System_has_paused) {
	old = Nil;
	new_1 = Nil;
      next_loop:
	old = Data_server_accept_data_task;
	def_structure_schedule_task_variable = 
		ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	if (def_structure_schedule_task_variable) {
	    temp = Chain_of_available_schedule_tasks_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = ISVREF(def_structure_schedule_task_variable,
		    (SI_Long)0L);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)0L)) = 
		    Qg2_defstruct_structure_name_schedule_task_g2_struct;
	}
	else
	    def_structure_schedule_task_variable = 
		    make_permanent_schedule_task_structure_internal();
	inline_note_allocate_cons(def_structure_schedule_task_variable,Nil);
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	task = def_structure_schedule_task_variable;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = -1.0;
	DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	SVREF(task,FIX((SI_Long)4L)) = temp;
	SVREF(task,FIX((SI_Long)5L)) = Nil;
	SVREF(task,FIX((SI_Long)9L)) = Nil;
	SVREF(task,FIX((SI_Long)10L)) = Nil;
	g2_p =  !TRUEP(Nil);
	SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	temp = ISVREF(task,(SI_Long)1L);
	aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		Current_real_time,(SI_Long)0L);
	DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	SVREF(task,FIX((SI_Long)7L)) = Qcall_data_server_accept_data_functions;
	temp = SYMBOL_FUNCTION(Qcall_data_server_accept_data_functions);
	SVREF(task,FIX((SI_Long)8L)) = temp;
	ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	new_1 = task;
	if (CAS_SYMBOL(Qdata_server_accept_data_task,old,new_1)) {
	    task = new_1;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
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
    return VALUES_1(Nil);
}

/* CANCEL-DATA-SERVER-ACCEPT-DATA-CALLS */
Object cancel_data_server_accept_data_calls()
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(183,31);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = Data_server_accept_data_task;
    if (CAS_SYMBOL(Qdata_server_accept_data_task,gensymed_symbol,Nil)) {
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
    goto next_loop;
  end_loop:
  end_1:;
    return VALUES_1(Nil);
}

static Object Qhandle_all_data_servers;  /* handle-all-data-servers */

/* CALL-DATA-SERVER-ACCEPT-DATA-FUNCTIONS */
Object call_data_server_accept_data_functions()
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object continue_accept_data_calls_qm, data_server, ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(183,32);
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
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
	  SVREF(temp,svref_arg_2) = Qhandle_all_data_servers;
      }
      continue_accept_data_calls_qm = Nil;
      data_server = Nil;
      ab_loop_list_ = List_of_all_data_servers;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      data_server = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (data_server_requests_accept_data_calls(data_server)) {
	  continue_accept_data_calls_qm = T;
	  if (ISVREF(data_server,(SI_Long)6L))
	      schedule_task_to_accept_data(data_server);
      }
      goto next_loop;
    end_loop:
      if (continue_accept_data_calls_qm)
	  schedule_data_server_accept_data_calls();
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

static Object Qaccept_data_and_reschedule_if_necessary;  /* accept-data-and-reschedule-if-necessary */

/* SCHEDULE-TASK-TO-ACCEPT-DATA */
Object schedule_task_to_accept_data(data_server)
    Object data_server;
{
    Object schedule_task_qm, old, new_1, def_structure_schedule_task_variable;
    Object temp_1, svref_arg_2, svref_new_value, task, ctask, p, v, q;
    Object structure_being_reclaimed;
    char temp, g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,33);
    if (ISVREF(data_server,(SI_Long)6L)) {
	schedule_task_qm = ISVREF(data_server,(SI_Long)13L);
	if (schedule_task_qm && (ISVREF(schedule_task_qm,(SI_Long)6L) || 
		EQ(schedule_task_qm,Current_schedule_task))) {
	    schedule_task_qm = ISVREF(data_server,(SI_Long)13L);
	    temp =  !(schedule_task_qm && EQ(schedule_task_qm,
		    Current_schedule_task));
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(data_server,(SI_Long)13L);
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
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp_1,(SI_Long)1L,aref_new_value);
	    temp_1 = ISVREF(Data_server_parameters,(SI_Long)22L);
	    SVREF(task,FIX((SI_Long)4L)) = temp_1;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    g2_p =  !TRUEP(Nil);
	    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	    temp_1 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		    Current_real_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qaccept_data_and_reschedule_if_necessary;
	    temp_1 = SYMBOL_FUNCTION(Qaccept_data_and_reschedule_if_necessary);
	    SVREF(task,FIX((SI_Long)8L)) = temp_1;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)13L)) = data_server;
	    new_1 = task;
	    if (CAS_SVREF(data_server,(SI_Long)13L,old,new_1)) {
		task = new_1;
		ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
		if (ctask);
		else
		    ctask = System_is_running;
		p = ISVREF(task,(SI_Long)4L);
		v = ctask ? Current_task_queue_vector : 
			Deferred_task_queue_vector;
		q = ISVREF(v,IFIX(p));
		SVREF(task,FIX((SI_Long)11L)) = q;
		temp_1 = constant_queue_push_right(q,task);
		SVREF(task,FIX((SI_Long)6L)) = temp_1;
		if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		    Priority_of_next_task = p;
		return VALUES_1(task);
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
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ACCEPT-DATA-AND-RESCHEDULE-IF-NECESSARY */
Object accept_data_and_reschedule_if_necessary(data_server)
    Object data_server;
{
    Object temp;

    x_note_fn_call(183,34);
    if (ISVREF(data_server,(SI_Long)6L)) {
	Time_slice_start_time = c_native_clock_ticks_or_cache(Nil,Nil);
	temp =  !TRUEP(FUNCALL_0(SYMBOL_FUNCTION(ISVREF(data_server,
		(SI_Long)5L)))) ? 
		schedule_task_to_accept_data(data_server) : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qcontinue_data_server_data_acceptance;  /* continue-data-server-data-acceptance */

/* CONTINUE-DATA-SERVER-DATA-ACCEPTANCE */
Object continue_data_server_data_acceptance(data_server,continuation_time)
    Object data_server, continuation_time;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, task, ctask;
    Object p, v, q;
    char g2_p;
    double arg, arg_1, aref_new_value;
    Declare_special(1);

    x_note_fn_call(183,35);
    arg = DFLOAT_ISAREF_1(continuation_time,(SI_Long)0L);
    arg_1 = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L);
    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
	    !inline_nanp_for_comparison(arg_1) ? TRUEP(ISVREF(data_server,
	    (SI_Long)6L)) : TRUEP(Nil)) {
	if ( !TRUEP(FUNCALL_0(SYMBOL_FUNCTION(ISVREF(data_server,
		(SI_Long)5L))))) {
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
	    task = def_structure_schedule_task_variable;
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    temp = ISVREF(Data_server_parameters,(SI_Long)22L);
	    SVREF(task,FIX((SI_Long)4L)) = temp;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    g2_p =  !TRUEP(Nil);
	    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		    Current_real_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
	    SVREF(task,FIX((SI_Long)7L)) = 
		    Qcontinue_data_server_data_acceptance;
	    temp = SYMBOL_FUNCTION(Qcontinue_data_server_data_acceptance);
	    SVREF(task,FIX((SI_Long)8L)) = temp;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)2L);
	    SVREF(task,FIX((SI_Long)13L)) = data_server;
	    SVREF(task,FIX((SI_Long)14L)) = continuation_time;
	    ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	    if (ctask);
	    else
		ctask = System_is_running;
	    p = ISVREF(task,(SI_Long)4L);
	    v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	    q = ISVREF(v,IFIX(p));
	    SVREF(task,FIX((SI_Long)11L)) = q;
	    temp = constant_queue_push_right(q,task);
	    SVREF(task,FIX((SI_Long)6L)) = temp;
	    if (ctask && FIXNUM_LT(p,Priority_of_next_task))
		Priority_of_next_task = p;
	}
    }
    return VALUES_1(Nil);
}

void cycles_INIT()
{
    Object gensymed_symbol, timing_scheduler_mode_evaluation_setter_1;
    Object timing_scheduler_mode_evaluation_getter_1, temp, temp_1;
    Object AB_package, Qcycles, Qg2_meter_task_limit, list_constant_13;
    Object string_constant_18;
    Object Qg2_meters_scheduler_time_lag_variable_names_format;
    Object Qinitialize_interval_for_telewindows_modernization;
    Object list_constant_12, Kfuncall, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object float_constant_1, Qslot_value_writer;
    Object Qwrite_interface_mode_from_slot, Qinterface_mode, list_constant_11;
    Object list_constant_10, list_constant_9, list_constant_8, list_constant_3;
    Object list_constant_4, list_constant_7, Qinterruptible, list_constant_6;
    Object list_constant_5, list_constant_2, Qinterface, Qservice, Qalways;
    Object Qclasses_which_define, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_timing_parameters;
    Object Qinstall_system_table, Qinstall_system_table_for_timing_parameters;
    Object Qslot_putter, Qput_scheduler_mode, Qtiming_scheduler_mode, Qnamed;
    Object Qtype_specification_simple_expansion;
    Object Qwrite_timing_scheduler_mode_from_slot, string_constant_17;
    Object Qg2_generate_new_random_seed;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qg2_set_random_seed;
    Object Qg2_get_random_seed, Qg2_repeat_random_function;

    x_note_fn_call(183,36);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qreal_time = STATIC_SYMBOL("REAL-TIME",AB_package);
    Qgensym_time = STATIC_SYMBOL("GENSYM-TIME",AB_package);
    Qfixnum_time_of_last_g2_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-OF-LAST-G2-TICK",AB_package);
    Qgensym_time_at_start = STATIC_SYMBOL("GENSYM-TIME-AT-START",AB_package);
    Qsimulated_time = STATIC_SYMBOL("SIMULATED-TIME",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    Qfixnum_time_until_g2_time_tick = 
	    STATIC_SYMBOL("FIXNUM-TIME-UNTIL-G2-TIME-TICK",AB_package);
    Qg2_time_to_tick_p_base = STATIC_SYMBOL("G2-TIME-TO-TICK-P-BASE",
	    AB_package);
    Qsystem_is_running = STATIC_SYMBOL("SYSTEM-IS-RUNNING",AB_package);
    Qsystem_has_paused = STATIC_SYMBOL("SYSTEM-HAS-PAUSED",AB_package);
    Qsystem_has_aborted = STATIC_SYMBOL("SYSTEM-HAS-ABORTED",AB_package);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    Qsystem_start = STATIC_SYMBOL("SYSTEM-START",AB_package);
    Qcurrent_workstation_window = 
	    STATIC_SYMBOL("CURRENT-WORKSTATION-WINDOW",AB_package);
    Qitems_needing_initialization = 
	    STATIC_SYMBOL("ITEMS-NEEDING-INITIALIZATION",AB_package);
    Qsystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",AB_package);
    Qg2_extension = STATIC_SYMBOL("G2-EXTENSION",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    Qstart = STATIC_SYMBOL("START",AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_start,STATIC_FUNCTION(system_start,NIL,
	    FALSE,0,0));
    Qsystem_reset = STATIC_SYMBOL("SYSTEM-RESET",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    SET_SYMBOL_FUNCTION(Qsystem_reset,STATIC_FUNCTION(system_reset,NIL,
	    FALSE,0,0));
    Qresume = STATIC_SYMBOL("RESUME",AB_package);
    Qg2_repeat_random_function = STATIC_SYMBOL("G2-REPEAT-RANDOM-FUNCTION",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_repeat_random_function,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_repeat_random_function,
	    STATIC_FUNCTION(g2_repeat_random_function,NIL,FALSE,0,0));
    Qg2_get_random_seed = STATIC_SYMBOL("G2-GET-RANDOM-SEED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_get_random_seed,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_get_random_seed,
	    STATIC_FUNCTION(g2_get_random_seed,NIL,FALSE,0,0));
    Qg2_set_random_seed = STATIC_SYMBOL("G2-SET-RANDOM-SEED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_set_random_seed,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant = 
	    STATIC_STRING("The argument ~a to g2-set-random-seed must be a non-negative integer.");
    SET_SYMBOL_FUNCTION(Qg2_set_random_seed,
	    STATIC_FUNCTION(g2_set_random_seed,NIL,FALSE,1,1));
    Qg2_generate_new_random_seed = 
	    STATIC_SYMBOL("G2-GENERATE-NEW-RANDOM-SEED",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_generate_new_random_seed,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_generate_new_random_seed,
	    STATIC_FUNCTION(g2_generate_new_random_seed,NIL,FALSE,0,0));
    string_constant_17 = 
	    STATIC_STRING("1n1n83FRy1m1m9k83Yby1m9k831Ay83Edy1n83FRy1m1m9k83-Cpy1m9k831Ay83-pYy1n83FRy1o1m9k83*5y1m9k83hGy1m9k83*5y1m9k83ldy83-Tmy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_17));
    string_constant_1 = STATIC_STRING("real time");
    string_constant_2 = STATIC_STRING("simulated time");
    Qfast_time = STATIC_SYMBOL("FAST-TIME",AB_package);
    string_constant_3 = STATIC_STRING("as fast as possible");
    Qnupec_catch_up = STATIC_SYMBOL("NUPEC-CATCH-UP",AB_package);
    string_constant_4 = STATIC_STRING("NUPEC catch up mode");
    string_constant_5 = STATIC_STRING("unknown");
    Qtiming_scheduler_mode = STATIC_SYMBOL("TIMING-SCHEDULER-MODE",AB_package);
    Qwrite_timing_scheduler_mode_from_slot = 
	    STATIC_SYMBOL("WRITE-TIMING-SCHEDULER-MODE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_timing_scheduler_mode_from_slot,
	    STATIC_FUNCTION(write_timing_scheduler_mode_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qtiming_scheduler_mode,
	    SYMBOL_FUNCTION(Qwrite_timing_scheduler_mode_from_slot),
	    Qslot_value_writer);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtiming_scheduler_mode),
	    Qtype_specification_simple_expansion,Qnil);
    Qas_fast_as_possible = STATIC_SYMBOL("AS-FAST-AS-POSSIBLE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)4L,Qmember,Qreal_time,
	    Qsimulated_time,Qas_fast_as_possible);
    define_type_specification_explicit_complex_type(Qtiming_scheduler_mode,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qtiming_scheduler_mode);
    timing_scheduler_mode_evaluation_setter_1 = 
	    STATIC_FUNCTION(timing_scheduler_mode_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtiming_scheduler_mode,
	    timing_scheduler_mode_evaluation_setter_1);
    timing_scheduler_mode_evaluation_getter_1 = 
	    STATIC_FUNCTION(timing_scheduler_mode_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtiming_scheduler_mode,
	    timing_scheduler_mode_evaluation_getter_1);
    Qscheduler_mode = STATIC_SYMBOL("SCHEDULER-MODE",AB_package);
    Qforce_clock_tick = STATIC_SYMBOL("FORCE-CLOCK-TICK",AB_package);
    Qput_scheduler_mode = STATIC_SYMBOL("PUT-SCHEDULER-MODE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_scheduler_mode,
	    STATIC_FUNCTION(put_scheduler_mode,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qscheduler_mode,
	    SYMBOL_FUNCTION(Qput_scheduler_mode),Qslot_putter);
    Qinstall_system_table_for_timing_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-TIMING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_timing_parameters,
	    STATIC_FUNCTION(install_system_table_for_timing_parameters,NIL,
	    FALSE,1,1));
    Qtiming_parameters = STATIC_SYMBOL("TIMING-PARAMETERS",AB_package);
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp = SYMBOL_FUNCTION(Qinstall_system_table_for_timing_parameters);
    set_get(Qtiming_parameters,Qinstall_system_table,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp = CONS(Qtiming_parameters,temp_1);
    mutate_global_property(Qinstall_system_table,temp,Qclasses_which_define);
    Qdeinstall_system_table_for_timing_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-TIMING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_timing_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_timing_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp = SYMBOL_FUNCTION(Qdeinstall_system_table_for_timing_parameters);
    set_get(Qtiming_parameters,Qdeinstall_system_table,temp);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp = CONS(Qtiming_parameters,temp_1);
    mutate_global_property(Qdeinstall_system_table,temp,Qclasses_which_define);
    Qinterface_mode = STATIC_SYMBOL("INTERFACE-MODE",AB_package);
    Qalways = STATIC_SYMBOL("ALWAYS",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qquote,Qalways);
    Qservice = STATIC_SYMBOL("SERVICE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qquote,Qservice);
    Qinterface = STATIC_SYMBOL("INTERFACE",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qquote,Qinterface);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qquote,Qfirst);
    list_constant_6 = STATIC_LIST((SI_Long)4L,list_constant_2,
	    list_constant_3,list_constant_4,list_constant_5);
    Qalways_service_interface_first = 
	    STATIC_SYMBOL("ALWAYS-SERVICE-INTERFACE-FIRST",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qinterface_mode,
	    list_constant_6,Qalways_service_interface_first);
    Qinterruptible = STATIC_SYMBOL("INTERRUPTIBLE",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qquote,Qinterruptible);
    list_constant_8 = STATIC_LIST((SI_Long)3L,list_constant_7,
	    list_constant_4,list_constant_3);
    Qtime_slice_dependant = STATIC_SYMBOL("TIME-SLICE-DEPENDANT",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)3L,Qinterface_mode,
	    list_constant_8,Qtime_slice_dependant);
    list_constant_11 = STATIC_LIST((SI_Long)2L,list_constant_9,
	    list_constant_10);
    add_grammar_rules_function(list_constant_11);
    string_constant_6 = STATIC_STRING("always service interface first");
    string_constant_7 = STATIC_STRING("interruptible interface service");
    string_constant_8 = STATIC_STRING("unknown value");
    Qwrite_interface_mode_from_slot = 
	    STATIC_SYMBOL("WRITE-INTERFACE-MODE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_interface_mode_from_slot,
	    STATIC_FUNCTION(write_interface_mode_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qinterface_mode,
	    SYMBOL_FUNCTION(Qwrite_interface_mode_from_slot),
	    Qslot_value_writer);
    Scheduled_tasks_time_limit = fixnum_time_interval(FIX((SI_Long)200L));
    Icp_socket_processing_time_limit = fixnum_time_interval(FIX((SI_Long)50L));
    Qcountdown_for_checking = STATIC_SYMBOL("COUNTDOWN-FOR-CHECKING",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcountdown_for_checking,Countdown_for_checking);
    Qcycles = STATIC_SYMBOL("CYCLES",AB_package);
    record_system_variable(Qcountdown_for_checking,Qcycles,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Legacy_multisecond_heartbeat_adjustment_priority = FIX((SI_Long)1L);
    float_constant_1 = STATIC_FLOAT(3600.0);
    Legacy_multisecond_heartbeat_adjustment_interval = float_constant_1;
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_9 = 
	    STATIC_STRING("The license to use G2 on this machine expires on ");
    string_constant_10 = 
	    STATIC_STRING(".~%G2 will not run after this date.~%~%");
    string_constant_11 = 
	    STATIC_STRING("The following application packages are not authorized:~%");
    string_constant_12 = 
	    STATIC_STRING("The following application packages have expired authorizations:~%");
    string_constant_13 = 
	    STATIC_STRING("The following application packages have authorizations with future start dates:~%");
    string_constant_14 = 
	    STATIC_STRING("The following application packages have authorizations that will expire within a week:~%");
    Qdo_legacy_multisecond_heartbeat_adjustments = 
	    STATIC_SYMBOL("DO-LEGACY-MULTISECOND-HEARTBEAT-ADJUSTMENTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdo_legacy_multisecond_heartbeat_adjustments,
	    STATIC_FUNCTION(do_legacy_multisecond_heartbeat_adjustments,
	    NIL,FALSE,0,0));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qplace_for_for_telewindows_modernization = 
	    STATIC_SYMBOL("PLACE-FOR-FOR-TELEWINDOWS-MODERNIZATION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplace_for_for_telewindows_modernization,
	    Place_for_for_telewindows_modernization);
    record_system_variable(Qplace_for_for_telewindows_modernization,
	    Qcycles,Nil,Qnil,Qnil,Qnil,Qnil);
    Priority_for_telewindows_modernization = FIX((SI_Long)1L);
    Qinterval_for_telewindows_modernization = 
	    STATIC_SYMBOL("INTERVAL-FOR-TELEWINDOWS-MODERNIZATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinterval_for_telewindows_modernization,
	    Interval_for_telewindows_modernization);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_interval_for_telewindows_modernization = 
	    STATIC_SYMBOL("INITIALIZE-INTERVAL-FOR-TELEWINDOWS-MODERNIZATION",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_interval_for_telewindows_modernization);
    record_system_variable(Qinterval_for_telewindows_modernization,Qcycles,
	    list_constant_12,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinitialize_interval_for_telewindows_modernization,
	    STATIC_FUNCTION(initialize_interval_for_telewindows_modernization,
	    NIL,FALSE,0,0));
    Qdo_legacy_subsecond_heartbeat_adjustments = 
	    STATIC_SYMBOL("DO-LEGACY-SUBSECOND-HEARTBEAT-ADJUSTMENTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdo_legacy_subsecond_heartbeat_adjustments,
	    STATIC_FUNCTION(do_legacy_subsecond_heartbeat_adjustments,NIL,
	    FALSE,0,0));
    Qmultiplicative_counter_for_evaluation = 
	    STATIC_SYMBOL("MULTIPLICATIVE-COUNTER-FOR-EVALUATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmultiplicative_counter_for_evaluation,
	    Multiplicative_counter_for_evaluation);
    record_system_variable(Qmultiplicative_counter_for_evaluation,Qeval,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Modulus_counter_for_evaluation = FIX((SI_Long)300000L);
    Qprevious_modulus_counter_for_evaluation = 
	    STATIC_SYMBOL("PREVIOUS-MODULUS-COUNTER-FOR-EVALUATION",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprevious_modulus_counter_for_evaluation,
	    Previous_modulus_counter_for_evaluation);
    record_system_variable(Qprevious_modulus_counter_for_evaluation,Qeval,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    Qtask_fragmentation_map_1 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-1",
	    AB_package);
    Qtask_fragmentation_map_2 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-2",
	    AB_package);
    Qtask_fragmentation_map_3 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-3",
	    AB_package);
    Qtask_fragmentation_map_4 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-4",
	    AB_package);
    Qtask_fragmentation_map_5 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-5",
	    AB_package);
    string_constant_15 = STATIC_STRING("~a-~a-~a");
    Qab_format = STATIC_SYMBOL("FORMAT",AB_package);
    string_constant_16 = 
	    string_append2(STATIC_STRING("This knowledge base was written within a NUPEC specialized ~\n                  version of G2.  The scheduler mode was NUPEC catch up, but ~\n                  since this is not"),
	    STATIC_STRING("  a NUPEC version of G2, it has been changed ~\n                  to real time."));
    Qupdate_memory_limits = STATIC_SYMBOL("UPDATE-MEMORY-LIMITS",AB_package);
    SET_SYMBOL_FUNCTION(Qupdate_memory_limits,
	    STATIC_FUNCTION(update_memory_limits,NIL,FALSE,1,1));
    Qtask_execution = STATIC_SYMBOL("TASK-EXECUTION",AB_package);
    Qg2_meters_scheduler_time_lag_variable_names_format = 
	    STATIC_SYMBOL("G2-METERS-SCHEDULER-TIME-LAG-VARIABLE-NAMES-FORMAT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_meters_scheduler_time_lag_variable_names_format,
	    G2_meters_scheduler_time_lag_variable_names_format);
    string_constant_18 = STATIC_STRING("PRIORITY-~a-LAST-GENSYM-TIME");
    SET_SYMBOL_VALUE(Qg2_meters_scheduler_time_lag_variable_names_format,
	    string_constant_18);
    Qpriority_1_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-1-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_1_last_gensym_time,
	    Priority_1_last_gensym_time);
    record_system_variable(Qpriority_1_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_2_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-2-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_2_last_gensym_time,
	    Priority_2_last_gensym_time);
    record_system_variable(Qpriority_2_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_3_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-3-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_3_last_gensym_time,
	    Priority_3_last_gensym_time);
    record_system_variable(Qpriority_3_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_4_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-4-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_4_last_gensym_time,
	    Priority_4_last_gensym_time);
    record_system_variable(Qpriority_4_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_5_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-5-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_5_last_gensym_time,
	    Priority_5_last_gensym_time);
    record_system_variable(Qpriority_5_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_6_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-6-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_6_last_gensym_time,
	    Priority_6_last_gensym_time);
    record_system_variable(Qpriority_6_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_7_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-7-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_7_last_gensym_time,
	    Priority_7_last_gensym_time);
    record_system_variable(Qpriority_7_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_8_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-8-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_8_last_gensym_time,
	    Priority_8_last_gensym_time);
    record_system_variable(Qpriority_8_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_9_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-9-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_9_last_gensym_time,
	    Priority_9_last_gensym_time);
    record_system_variable(Qpriority_9_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qpriority_10_last_gensym_time = 
	    STATIC_SYMBOL("PRIORITY-10-LAST-GENSYM-TIME",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qpriority_10_last_gensym_time,
	    Priority_10_last_gensym_time);
    record_system_variable(Qpriority_10_last_gensym_time,Qcycles,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    list_constant_13 = STATIC_LIST((SI_Long)10L,
	    Qpriority_1_last_gensym_time,Qpriority_2_last_gensym_time,
	    Qpriority_3_last_gensym_time,Qpriority_4_last_gensym_time,
	    Qpriority_5_last_gensym_time,Qpriority_6_last_gensym_time,
	    Qpriority_7_last_gensym_time,Qpriority_8_last_gensym_time,
	    Qpriority_9_last_gensym_time,Qpriority_10_last_gensym_time);
    if (Meter_lag_time_variables == UNBOUND)
	Meter_lag_time_variables = list_constant_13;
    Qg2_meter_task_count = STATIC_SYMBOL("G2-METER-TASK-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_meter_task_count,G2_meter_task_count);
    record_system_variable(Qg2_meter_task_count,Qcycles,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qg2_meter_task_limit = STATIC_SYMBOL("G2-METER-TASK-LIMIT",AB_package);
    SET_SYMBOL_VALUE(Qg2_meter_task_limit,FIX((SI_Long)100L));
    Qunload_scheduler_into_current_queue = 
	    STATIC_SYMBOL("UNLOAD-SCHEDULER-INTO-CURRENT-QUEUE",AB_package);
    Qg2_meter_data_service_on_qm = 
	    STATIC_SYMBOL("G2-METER-DATA-SERVICE-ON\?",AB_package);
    Qdata_server_accept_data_task = 
	    STATIC_SYMBOL("DATA-SERVER-ACCEPT-DATA-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdata_server_accept_data_task,
	    Data_server_accept_data_task);
    record_system_variable(Qdata_server_accept_data_task,Qcycles,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qcall_data_server_accept_data_functions = 
	    STATIC_SYMBOL("CALL-DATA-SERVER-ACCEPT-DATA-FUNCTIONS",AB_package);
    Qhandle_all_data_servers = STATIC_SYMBOL("HANDLE-ALL-DATA-SERVERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcall_data_server_accept_data_functions,
	    STATIC_FUNCTION(call_data_server_accept_data_functions,NIL,
	    FALSE,0,0));
    Qaccept_data_and_reschedule_if_necessary = 
	    STATIC_SYMBOL("ACCEPT-DATA-AND-RESCHEDULE-IF-NECESSARY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qaccept_data_and_reschedule_if_necessary,
	    STATIC_FUNCTION(accept_data_and_reschedule_if_necessary,NIL,
	    FALSE,1,1));
    Qcontinue_data_server_data_acceptance = 
	    STATIC_SYMBOL("CONTINUE-DATA-SERVER-DATA-ACCEPTANCE",AB_package);
    SET_SYMBOL_FUNCTION(Qcontinue_data_server_data_acceptance,
	    STATIC_FUNCTION(continue_data_server_data_acceptance,NIL,FALSE,
	    2,2));
}
