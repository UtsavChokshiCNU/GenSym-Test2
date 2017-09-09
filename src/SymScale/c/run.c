/* run.c
 * Input file:  run.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "run.h"


static Object Qab;                 /* ab */

static Object Qrun_ab;             /* run-ab */

/* RUN-AB-PROCESS-TOP-LEVEL */
Object run_ab_process_top_level(native_window)
    Object native_window;
{
    x_note_fn_call(129,0);
    return run_system_process(Qab,native_window,Qrun_ab);
}

/* LAUNCH-AB */
Object launch_ab()
{
    x_note_fn_call(129,1);
    return launch_system_process(Qab);
}

static Object Qcatcher;            /* catcher */

/* THROW-TO-CHESTNUT-CATCHER */
Object throw_to_chestnut_catcher()
{
    Object result;

    x_note_fn_call(129,2);
    result = VALUES_1(Nil);
    THROW(Qcatcher,result);
    return VALUES_1(Nil);
}

static Object Qinitial_value;      /* initial-value */

static Object Qside_effected_value;  /* side-effected-value */

/* EXHIBIT-CHESTNUT-CATCH-REVERTS-LOCALS-BUG */
Object exhibit_chestnut_catch_reverts_locals_bug()
{
    volatile Object vulnerable_local;
    Declare_catch(1);

    x_note_fn_call(129,3);
    vulnerable_local = Qinitial_value;
    if (PUSH_CATCH(Qcatcher,0)) {
	vulnerable_local = Qside_effected_value;
	throw_to_chestnut_catcher();
    }
    POP_CATCH(0);
    return VALUES_1(EQ(vulnerable_local,Qinitial_value) ? T : Nil);
}

/* VERIFY-CHESTNUT-CATCH-REVERTS-LOCALS-FIX */
Object verify_chestnut_catch_reverts_locals_fix()
{
    volatile Object vulnerable_local;
    Declare_catch(1);

    x_note_fn_call(129,4);
    vulnerable_local = Qinitial_value;
    if (PUSH_CATCH(Qcatcher,0)) {
	vulnerable_local = Qside_effected_value;
	throw_to_chestnut_catcher();
    }
    POP_CATCH(0);
    return VALUES_1(EQ(vulnerable_local,Qside_effected_value) ? T : Nil);
}

/* EXHIBIT-CHESTNUT-UNWIND-PROTECT-REVERTS-LOCALS-BUG */
Object exhibit_chestnut_unwind_protect_reverts_locals_bug()
{
    volatile Object vulnerable_local;
    volatile Object buggy_p;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(129,5);
    SAVE_STACK();
    vulnerable_local = Qinitial_value;
    buggy_p = Nil;
    if (PUSH_CATCH(Qcatcher,1)) {
	if (PUSH_UNWIND_PROTECT(0)) {
	    vulnerable_local = Qside_effected_value;
	    throw_to_chestnut_catcher();
	}
	POP_UNWIND_PROTECT(0);
	if (EQ(vulnerable_local,Qinitial_value))
	    buggy_p = T;
	else
	    buggy_p = Nil;
	CONTINUE_UNWINDING(0);
    }
    POP_CATCH(1);
    RESTORE_STACK();
    return VALUES_1(buggy_p);
}

/* NOOP-CLEANUP-FORM */
Object noop_cleanup_form()
{
    x_note_fn_call(129,6);
    return VALUES_1(Nil);
}

/* VERIFY-CHESTNUT-UNWIND-PROTECT-REVERTS-LOCALS-FIX */
Object verify_chestnut_unwind_protect_reverts_locals_fix()
{
    volatile Object vulnerable_local;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(129,7);
    SAVE_STACK();
    vulnerable_local = Qinitial_value;
    if (PUSH_CATCH(Qcatcher,1)) {
	if (PUSH_UNWIND_PROTECT(0)) {
	    vulnerable_local = Qside_effected_value;
	    throw_to_chestnut_catcher();
	}
	POP_UNWIND_PROTECT(0);
	noop_cleanup_form();
	CONTINUE_UNWINDING(0);
    }
    POP_CATCH(1);
    RESTORE_STACK();
    return VALUES_1(EQ(vulnerable_local,Qside_effected_value) ? T : Nil);
}

/* POST-SETJMP-STATUS */
Object post_setjmp_status()
{
    x_note_fn_call(129,8);
    if (exhibit_chestnut_catch_reverts_locals_bug())
	format((SI_Long)2L,T,"~&Catch noted.~%");
    else
	format((SI_Long)2L,T,"~&Catch complete.~%");
    if (verify_chestnut_catch_reverts_locals_fix())
	format((SI_Long)2L,T,"~&Throw complete.~%");
    else
	format((SI_Long)2L,T,"~&Throw noted.~%");
    if (exhibit_chestnut_unwind_protect_reverts_locals_bug())
	format((SI_Long)2L,T,"~&Unwind noted.~%");
    else
	format((SI_Long)2L,T,"~&Unwind complete.~%");
    if (verify_chestnut_unwind_protect_reverts_locals_fix())
	return format((SI_Long)2L,T,"~&Protect complete.~%");
    else
	return format((SI_Long)2L,T,"~&Protect noted.~%");
}

/* IS-IN-LDAP-MODE-P */
Object is_in_ldap_mode_p()
{
    Object ldap_mode_qm;

    x_note_fn_call(129,9);
    ldap_mode_qm = Nil;
    if (Relations_tag_list) {
	if ( !((SI_Long)0L == g2_check_ldap_mode()))
	    ldap_mode_qm = T;
    }
    return VALUES_1(ldap_mode_qm);
}

static Object Quser_name;          /* user-name */

static Object Qpassword;           /* password */

static Object Qmd5_password;       /* md5-password */

static Object array_constant;      /* # */

/* AUGMENT-WINDOW-PARAMETERS-PLIST-OF-INITIAL-GENSYM-WINDOW */
Object augment_window_parameters_plist_of_initial_gensym_window(initial_gensym_window)
    Object initial_gensym_window;
{
    Object temp, svref_new_value, window_parameters_plist, g2_user_name_qm;
    Object g2_password_qm;

    x_note_fn_call(129,10);
    temp = ISVREF(initial_gensym_window,(SI_Long)19L);
    svref_new_value = nconc2(temp,get_command_line_arguments());
    SVREF(initial_gensym_window,FIX((SI_Long)19L)) = svref_new_value;
    window_parameters_plist = ISVREF(initial_gensym_window,(SI_Long)19L);
    g2_user_name_qm = getf(window_parameters_plist,Quser_name,_);
    g2_password_qm = getf(window_parameters_plist,Qpassword,_);
    if (g2_password_qm && g2_user_name_qm) {
	svref_new_value = mutate_gensym_plist(window_parameters_plist,
		Qmd5_password,encode_password_via_md5(g2_user_name_qm,
		get_command_line_keyword_argument(1,array_constant),Nil));
	SVREF(initial_gensym_window,FIX((SI_Long)19L)) = svref_new_value;
    }
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Initial_java_class, Qinitial_java_class);

Object Debug_clear_text_checksums = UNBOUND;

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant_1;    /* # */

static Object Qtop_level_error_catcher;  /* top-level-error-catcher */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qwarn_user_of_previously_aborted_g2;  /* warn-user-of-previously-aborted-g2 */

/* RUN-AB */
Object run_ab(gensym_window_for_workstation_qm)
    Object gensym_window_for_workstation_qm;
{
    Object code, current_draw_paper_p, system_time;
    volatile Object decrypted_primeval_timestamp_qm;
    Object decrypted_primeval_time_qm, timestamp_qm, encoded_timestamp_field;
    Object ab_loop_list_, timestamp_field_qm;
    volatile Object rotator_specs;
    Object gensymed_symbol, gensymed_symbol_1, temp_3, rotator, offset;
    Object ab_loop_list__1, ab_loop_desetq_, logrotate_in_place_arg_1;
    Object logrotate_in_place_arg_2;
    volatile Object filled_timestamp_field_components;
    Object key, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_iter_flag_;
    Object component, rotator_spec, circularity_point, raw_field;
    Object timestamp_field, raw_field_list, time_1, temp_4, old_value_qm;
    Object timestamp, fix_time, temp_5, timestamp_cons;
    Object encrypted_timestamp_field, rotator_list, write_console_p;
    Object top_level_error_catcher_tag, error_occurred_p, old, new_1;
    Object def_structure_schedule_task_variable, svref_new_value, task;
    Object structure_being_reclaimed;
    SI_Long ab_loop_repeat_, index_1, shift_amount, ab_loop_repeat__1;
    SI_Long car_new_value, offset_1, logrotate_in_place_arg_2_1;
    char temp, svref_new_value_1;
    double temp_1, temp_2, aref_new_value;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(129,11);
    SAVE_STACK();
    initialize_scheduler();
    initialize_gensym_time();
    if ( !TRUEP(authorize_ab()))
	shutdown_or_exit(0);
    initialize_optional_modules();
    assign_class_bit_numbers_and_vectors_to_system_classes();
    switch_to_new_empty_kb();
    set_icp_tracing_level_from_command_line();
    if (zerop(X11_preinitialized_p)) {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	notify_user_at_console(1,Embedded_g2_with_windows_goodbye_message);
	shut_down_ab_process(0);
    }
    if (gensym_window_for_workstation_qm) {
	augment_window_parameters_plist_of_initial_gensym_window(gensym_window_for_workstation_qm);
	set_up_workstation(gensym_window_for_workstation_qm);
	lay_out_window(gensym_window_for_workstation_qm);
	make_window_visible(gensym_window_for_workstation_qm);
    }
    current_draw_paper_p = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Current_draw_paper_p,Qcurrent_draw_paper_p,current_draw_paper_p,
	    0);
      display_credits(0);
    POP_SPECIAL();
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	system_time = Qunbound_in_protected_let;
	decrypted_primeval_timestamp_qm = Qunbound_in_protected_let;
	decrypted_primeval_time_qm = Qunbound_in_protected_let;
	if (PUSH_UNWIND_PROTECT(2)) {
	    temp_1 = g2ext_unix_time_as_float();
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
	    system_time = DOUBLE_TO_DOUBLE_FLOAT(temp_1 + temp_2);
	    timestamp_qm = Nil;
	    encoded_timestamp_field = Nil;
	    ab_loop_list_ = Minimal_fragmentation_seeds;
	    timestamp_field_qm = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    encoded_timestamp_field = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    rotator_specs = Qunbound_in_protected_let;
	    if (PUSH_UNWIND_PROTECT(1)) {
		gensymed_symbol = make_timestamp_list_1(FIX((SI_Long)9L));
		gensymed_symbol_1 = gensymed_symbol;
		temp_3 = 
			timestamp_cons_1(FOURTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)0L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)3L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)6L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)9L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(THIRD(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)12L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(SIXTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)12L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(SECOND(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)15L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(FIFTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)18L));
		M_CAR(gensymed_symbol_1) = temp_3;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_3 = 
			timestamp_cons_1(SEVENTH(Embedded_fuzzy_conditionals_list),
			FIX((SI_Long)18L));
		M_CAR(gensymed_symbol_1) = temp_3;
		rotator_specs = gensymed_symbol;
		rotator = Nil;
		offset = Nil;
		ab_loop_list__1 = rotator_specs;
		ab_loop_desetq_ = Nil;
	      next_loop_1:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_1;
		ab_loop_desetq_ = M_CAR(ab_loop_list__1);
		rotator = CAR(ab_loop_desetq_);
		offset = CDR(ab_loop_desetq_);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		logrotate_in_place_arg_1 = rotator;
		logrotate_in_place_arg_2 = offset;
		encoded_timestamp_field = 
			assemble_uncached_compound_method_flags(encoded_timestamp_field,
			logrotate_in_place_arg_1,logrotate_in_place_arg_2,
			FIX((SI_Long)3L));
		goto next_loop_1;
	      end_loop_1:;
		filled_timestamp_field_components = Qunbound_in_protected_let;
		key = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(0)) {
		    ab_loop_repeat_ = (SI_Long)3L;
		    index_1 = (SI_Long)2L;
		    shift_amount = (SI_Long)-14L;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_2:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_2;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    if ( !TRUEP(ab_loop_iter_flag_)) {
			index_1 = index_1 - (SI_Long)1L;
			shift_amount = shift_amount + (SI_Long)7L;
		    }
		    ab_loopvar__2 = 
			    timestamp_cons_1(ash(logand(ISVREF(Class_instance_delta_masks,
			    index_1),encoded_timestamp_field),
			    FIX(shift_amount)),Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_2;
		  end_loop_2:
		    filled_timestamp_field_components = ab_loopvar_;
		    goto end_1;
		    filled_timestamp_field_components = Qnil;
		  end_1:;
		    key = FIRST(filled_timestamp_field_components);
		    component = Nil;
		    ab_loop_list__1 = REST(filled_timestamp_field_components);
		  next_loop_3:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_3;
		    component = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    if ( !FIXNUM_EQ(key,component)) {
			temp = TRUEP(Nil);
			goto end_2;
		    }
		    goto next_loop_3;
		  end_loop_3:
		    temp = TRUEP(T);
		    goto end_2;
		    temp = TRUEP(Qnil);
		  end_2:;
		    SAVE_VALUES(VALUES_1(temp ? key : Nil));
		}
		POP_UNWIND_PROTECT(0);
		if (filled_timestamp_field_components) {
		    if ( !EQ(filled_timestamp_field_components,
			    Qunbound_in_protected_let))
			reclaim_timestamp_list_1(filled_timestamp_field_components);
		}
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		SAVE_VALUES(VALUES_1(result));
	    }
	    POP_UNWIND_PROTECT(1);
	    if (rotator_specs) {
		if ( !EQ(rotator_specs,Qunbound_in_protected_let)) {
		    rotator_spec = Nil;
		    ab_loop_list__1 = rotator_specs;
		  next_loop_4:
		    if ( !TRUEP(ab_loop_list__1))
			goto end_loop_4;
		    rotator_spec = M_CAR(ab_loop_list__1);
		    ab_loop_list__1 = M_CDR(ab_loop_list__1);
		    reclaim_timestamp_cons_1(rotator_spec);
		    goto next_loop_4;
		  end_loop_4:
		    reclaim_timestamp_list_1(rotator_specs);
		}
	    }
	    CONTINUE_UNWINDING(1);
	    result = RESTORE_VALUES();
	    timestamp_field_qm = result;
	    timestamp_qm = timestamp_cons_1(timestamp_field_qm,timestamp_qm);
	    goto next_loop;
	  end_loop:;
	    timestamp_field_qm = Nil;
	    ab_loop_list_ = timestamp_qm;
	  next_loop_5:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_5;
	    timestamp_field_qm = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(timestamp_field_qm)) {
		if (timestamp_qm)
		    reclaim_timestamp_list_1(timestamp_qm);
		decrypted_primeval_timestamp_qm = Nil;
		goto end_3;
	    }
	    goto next_loop_5;
	  end_loop_5:
	    decrypted_primeval_timestamp_qm = nreverse(timestamp_qm);
	    goto end_3;
	    decrypted_primeval_timestamp_qm = Qnil;
	  end_3:;
	    if (decrypted_primeval_timestamp_qm) {
		circularity_point = 
			FIXNUM_SUB1(length(decrypted_primeval_timestamp_qm));
		temp_3 = nthcdr(circularity_point,
			decrypted_primeval_timestamp_qm);
		M_CDR(temp_3) = decrypted_primeval_timestamp_qm;
		if (PUSH_UNWIND_PROTECT(0)) {
		    ab_loop_repeat_ = (SI_Long)5L;
		    raw_field = Nil;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		  next_loop_6:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_6;
		    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
		    raw_field = FIX((SI_Long)0L);
		    ab_loop_repeat__1 = (SI_Long)7L;
		    timestamp_field = Nil;
		  next_loop_7:
		    if ( !((SI_Long)0L < ab_loop_repeat__1))
			goto end_loop_7;
		    ab_loop_repeat__1 = ab_loop_repeat__1 - (SI_Long)1L;
		    timestamp_field = CAR(decrypted_primeval_timestamp_qm);
		    raw_field = logtest(FIX((SI_Long)64L),timestamp_field) 
			    ? logior(ash(raw_field,FIX((SI_Long)-1L)),
			    FIX((SI_Long)64L)) : ash(raw_field,
			    FIX((SI_Long)-1L));
		    temp_3 = ash(timestamp_field,FIX((SI_Long)1L));
		    M_CAR(decrypted_primeval_timestamp_qm) = temp_3;
		    decrypted_primeval_timestamp_qm = 
			    CDR(decrypted_primeval_timestamp_qm);
		    goto next_loop_7;
		  end_loop_7:;
		    ab_loopvar__2 = timestamp_cons_1(raw_field,Nil);
		    if (ab_loopvar__1)
			M_CDR(ab_loopvar__1) = ab_loopvar__2;
		    else
			ab_loopvar_ = ab_loopvar__2;
		    ab_loopvar__1 = ab_loopvar__2;
		    goto next_loop_6;
		  end_loop_6:
		    raw_field_list = ab_loopvar_;
		    goto end_4;
		    raw_field_list = Qnil;
		  end_4:;
		    raw_field = Nil;
		    ab_loop_list_ = raw_field_list;
		    shift_amount = (SI_Long)28L;
		    time_1 = FIX((SI_Long)0L);
		    ab_loop_iter_flag_ = T;
		  next_loop_8:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_8;
		    raw_field = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if ( !TRUEP(ab_loop_iter_flag_))
			shift_amount = shift_amount + (SI_Long)-7L;
		    time_1 = logior(ash(raw_field,FIX(shift_amount)),time_1);
		    ab_loop_iter_flag_ = Nil;
		    goto next_loop_8;
		  end_loop_8:
		    reclaim_timestamp_list_1(raw_field_list);
		    temp_4 = time_1;
		    goto end_5;
		    temp_4 = Qnil;
		  end_5:;
		    SAVE_VALUES(VALUES_1(temp_4));
		}
		POP_UNWIND_PROTECT(0);
		temp_3 = nthcdr(circularity_point,
			decrypted_primeval_timestamp_qm);
		M_CDR(temp_3) = Nil;
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		decrypted_primeval_time_qm = result;
	    }
	    else
		decrypted_primeval_time_qm = Nil;
	    temp =  !TRUEP(decrypted_primeval_time_qm);
	    if (temp);
	    else {
		temp_4 = lfloat(decrypted_primeval_time_qm,_);
		temp = NUM_LT(system_time,temp_4);
	    }
	    if (temp) {
		old_value_qm = THIRD(Master_hierarchy_reconciliation_switches);
		if (old_value_qm)
		    reclaim_timestamp_list_1(old_value_qm);
		temp_3 = Master_hierarchy_reconciliation_switches;
		raw_field_list = Qunbound_in_protected_let;
		timestamp = Qunbound_in_protected_let;
		if (PUSH_UNWIND_PROTECT(1)) {
		    ab_loop_repeat_ = (SI_Long)5L;
		    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(system_time);
		    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(Seconds_from_1900_to_1970);
		    fix_time = lfloor(DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 
			    temp_2),_);
		    index_1 = (SI_Long)4L;
		    shift_amount = (SI_Long)-28L;
		    ab_loopvar_ = Nil;
		    ab_loopvar__1 = Nil;
		    ab_loopvar__2 = Nil;
		    ab_loop_iter_flag_ = T;
		  next_loop_9:
		    if ( !((SI_Long)0L < ab_loop_repeat_))
			goto end_loop_9;
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
		    goto next_loop_9;
		  end_loop_9:
		    raw_field_list = ab_loopvar_;
		    goto end_6;
		    raw_field_list = Qnil;
		  end_6:;
		    gensymed_symbol = make_timestamp_list_1(FIX((SI_Long)5L));
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
		    timestamp = gensymed_symbol;
		    circularity_point = FIXNUM_SUB1(length(timestamp));
		    temp_5 = nthcdr(circularity_point,timestamp);
		    M_CDR(temp_5) = timestamp;
		    if (PUSH_UNWIND_PROTECT(0)) {
			raw_field = Nil;
			ab_loop_list_ = raw_field_list;
		      next_loop_10:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_10;
			raw_field = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			ab_loop_repeat_ = (SI_Long)7L;
		      next_loop_11:
			if ( !((SI_Long)0L < ab_loop_repeat_))
			    goto end_loop_11;
			ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
			timestamp_field = CAR(timestamp);
			car_new_value = oddp(raw_field) ? 
				IFIX(ash(timestamp_field,
				FIX((SI_Long)1L))) | (SI_Long)1L : 
				IFIX(timestamp_field) << (SI_Long)1L;
			M_CAR(timestamp) = FIX(car_new_value);
			timestamp = CDR(timestamp);
			raw_field = FIX(IFIX(raw_field) >>  -  - (SI_Long)1L);
			goto next_loop_11;
		      end_loop_11:;
			goto next_loop_10;
		      end_loop_10:
			temp_4 = timestamp;
			goto end_7;
			temp_4 = Qnil;
		      end_7:;
			SAVE_VALUES(VALUES_1(temp_4));
		    }
		    POP_UNWIND_PROTECT(0);
		    temp_5 = nthcdr(circularity_point,timestamp);
		    M_CDR(temp_5) = Nil;
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
		timestamp = result;
		timestamp_field = Nil;
		ab_loop_list_ = timestamp;
		timestamp_cons = timestamp;
		ab_loop_iter_flag_ = T;
	      next_loop_12:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_12;
		timestamp_field = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_iter_flag_))
		    timestamp_cons = M_CDR(timestamp_cons);
		if ( !TRUEP(timestamp_cons))
		    goto end_loop_12;
		encrypted_timestamp_field = logiorn(3,ash(timestamp_field,
			FIX((SI_Long)0L)),ash(timestamp_field,
			FIX((SI_Long)7L)),ash(timestamp_field,
			FIX((SI_Long)14L)));
		gensymed_symbol = make_timestamp_list_1(FIX((SI_Long)7L));
		gensymed_symbol_1 = gensymed_symbol;
		temp_5 = THIRD(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SIXTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SEVENTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = SECOND(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FIRST(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FIFTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		temp_5 = FOURTH(Embedded_fuzzy_conditionals_list);
		M_CAR(gensymed_symbol_1) = temp_5;
		rotator_list = gensymed_symbol;
		rotator = Nil;
		ab_loop_list__1 = rotator_list;
		offset_1 = (SI_Long)0L;
		ab_loop_iter_flag_ = T;
	      next_loop_13:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_13;
		rotator = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if ( !TRUEP(ab_loop_iter_flag_))
		    offset_1 = offset_1 + (SI_Long)3L;
		logrotate_in_place_arg_1 = rotator;
		logrotate_in_place_arg_2_1 = offset_1;
		encrypted_timestamp_field = 
			assemble_uncached_compound_method_flags(encrypted_timestamp_field,
			logrotate_in_place_arg_1,
			FIX(logrotate_in_place_arg_2_1),FIX((SI_Long)3L));
		ab_loop_iter_flag_ = Nil;
		goto next_loop_13;
	      end_loop_13:;
		reclaim_timestamp_list_1(rotator_list);
		M_CAR(timestamp_cons) = encrypted_timestamp_field;
		ab_loop_iter_flag_ = Nil;
		goto next_loop_12;
	      end_loop_12:
		temp_5 = timestamp;
		goto end_8;
		temp_5 = Qnil;
	      end_8:;
		M_THIRD(temp_3) = temp_5;
	    }
	}
	POP_UNWIND_PROTECT(2);
	if (decrypted_primeval_timestamp_qm) {
	    if ( !EQ(decrypted_primeval_timestamp_qm,
		    Qunbound_in_protected_let))
		reclaim_timestamp_list_1(decrypted_primeval_timestamp_qm);
	}
	CONTINUE_UNWINDING(2);
    }
    POP_LOCAL_ALLOCATION(0,0);
    write_console_p = T;
    PUSH_SPECIAL_WITH_SYMBOL(Write_console_p,Qwrite_console_p,write_console_p,
	    0);
      report_listener_info_to_parent_window();
    POP_SPECIAL();
    if (SEVENTH(Consistency_tree_focus_shifts) && nth(FIX((SI_Long)11L),
	    Format_structure_description) && T) {
	notify_user_at_console(1,G2_system_time_too_early_goodbye_message);
	shut_down_ab_process(0);
    }
    update_system_tray_icon();
    Debug_clear_text_checksums = get_command_line_flag_argument(1,
	    array_constant_1);
    if (no_local_window_p() || running_as_noninteractive_service_p())
	set_flag_permitting_free_floating_authorization();
    do_plist_checking();
    do_plist_checking_again();
    ne_enqueue_scheduler_event();
    maybe_schedule_service_workstations(T);
    schedule_g2_legacy_heartbeat_tasks_if_necessary();
    Gc_silence = Nil;
    start_scheduler_workers();
  next_loop_14:
    if (Do_error_trapping_qm) {
	top_level_error_catcher_tag = Qtop_level_error_catcher;
	PUSH_SPECIAL_WITH_SYMBOL(Top_level_error_catcher_tag,Qtop_level_error_catcher_tag,top_level_error_catcher_tag,
		0);
	  Top_level_error_seen = Nil;
	  if (PUSH_CATCH(Top_level_error_catcher_tag,0)) {
	      register_all_signal_handlers();
	      g2_event_loop();
	      error_occurred_p = Nil;
	  }
	  else
	      error_occurred_p = CATCH_VALUES();
	  POP_CATCH(0);
	POP_SPECIAL();
	if (error_occurred_p) {
	    internal_error_given_format_info(Gensym_error_format_string,
		    Gensym_error_argument_list,
		    Gensym_error_sure_of_format_info_p);
	    Index_of_top_of_backtrace_stack = FIX((SI_Long)-1L);
	    old = Nil;
	    new_1 = Nil;
	  next_loop_15:
	    old = Task_to_warn_user_of_previously_aborted_g2;
	    def_structure_schedule_task_variable = 
		    ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    if (def_structure_schedule_task_variable) {
		temp_3 = Chain_of_available_schedule_tasks_vector;
		temp_5 = Current_thread_index;
		svref_new_value = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(temp_3,temp_5) = svref_new_value;
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
	    temp_3 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) 
		    + 30.0;
	    DFLOAT_ISASET_1(temp_3,(SI_Long)0L,aref_new_value);
	    temp_3 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = 30.0;
	    DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
	    svref_new_value_1 =  !TRUEP(T);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
	    ISVREF(task,(SI_Long)4L) = FIX((SI_Long)1L);
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    SVREF(task,FIX((SI_Long)7L)) = Qwarn_user_of_previously_aborted_g2;
	    temp_3 = SYMBOL_FUNCTION(Qwarn_user_of_previously_aborted_g2);
	    SVREF(task,FIX((SI_Long)8L)) = temp_3;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)0L);
	    new_1 = task;
	    if (CAS_SYMBOL(Qtask_to_warn_user_of_previously_aborted_g2,old,
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
		    temp_3 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(old,FIX((SI_Long)0L)) = temp_3;
		    temp_3 = Chain_of_available_schedule_tasks_vector;
		    temp_5 = Current_thread_index;
		    SVREF(temp_3,temp_5) = old;
		}
		future_task_schedule_2(new_1);
		goto end_9;
	    }
	    else {
		inline_note_reclaim_cons(new_1,Nil);
		structure_being_reclaimed = new_1;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(new_1,(SI_Long)9L));
		  SVREF(new_1,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_3 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
		temp_3 = Chain_of_available_schedule_tasks_vector;
		temp_5 = Current_thread_index;
		SVREF(temp_3,temp_5) = new_1;
	    }
	    goto next_loop_15;
	  end_loop_14:
	  end_9:;
	}
    }
    else
	g2_event_loop();
    goto next_loop_14;
  end_loop_15:
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

/* RUNNING-AS-NONINTERACTIVE-SERVICE-P */
Object running_as_noninteractive_service_p()
{
    x_note_fn_call(129,12);
    return VALUES_1(g2ext_noninteractive_service_p() == (SI_Long)1L ? T : Nil);
}

static Object Qreset;              /* reset */

static Object string_constant;     /* "reset" */

static Object Qpaused;             /* paused */

static Object string_constant_1;   /* "paused" */

static Object Qrunning;            /* running */

static Object string_constant_2;   /* "running" */

static Object Qabort_g2;           /* abort */

static Object string_constant_3;   /* "abort" */

static Object array_constant_2;    /* # */

/* UPDATE-SYSTEM-TRAY-ICON */
Object update_system_tray_icon()
{
    Object temp, icon_name_qm;

    x_note_fn_call(129,13);
    temp = current_g2_run_state();
    if (EQ(temp,Qreset))
	icon_name_qm = string_constant;
    else if (EQ(temp,Qpaused))
	icon_name_qm = string_constant_1;
    else if (EQ(temp,Qrunning))
	icon_name_qm = string_constant_2;
    else if (EQ(temp,Qabort_g2))
	icon_name_qm = string_constant_3;
    else
	icon_name_qm = Qnil;
    if (icon_name_qm)
	return c_update_system_tray(FIX((SI_Long)-1L),icon_name_qm,
		array_constant_2);
    else
	return VALUES_1(Nil);
}

/* C-UPDATE-SYSTEM-TRAY */
Object c_update_system_tray(icon,icon_name,tooltip)
    Object icon, icon_name, tooltip;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(129,14);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(icon_name);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = icon_name;
    temp = FIX(g2ext_update_system_tray(IFIX(icon),ISTRING(temp),
	    UBYTE_16_SARRAY_TO_USHORT_PTR(tooltip)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* FIND-ULTIMATE-SUPERPLANE-IN-STACK-OF-COUPLED-IMAGE-PLANES */
Object find_ultimate_superplane_in_stack_of_coupled_image_planes(image_plane)
    Object image_plane;
{
    Object ultimate_superplane_so_far, superplane_qm;

    x_note_fn_call(129,15);
    ultimate_superplane_so_far = image_plane;
    superplane_qm = Nil;
  next_loop:
    superplane_qm = ISVREF(ultimate_superplane_so_far,(SI_Long)3L);
    if ( !TRUEP(superplane_qm))
	goto end_loop;
    ultimate_superplane_so_far = superplane_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(ultimate_superplane_so_far);
    return VALUES_1(Qnil);
}

/* FIND-BASE-PLANE-IN-STACK-OF-COUPLED-IMAGE-PLANES */
Object find_base_plane_in_stack_of_coupled_image_planes(image_plane)
    Object image_plane;
{
    Object ultimate_subplane_so_far, subplane_qm_1;

    x_note_fn_call(129,16);
    ultimate_subplane_so_far = image_plane;
    subplane_qm_1 = Nil;
  next_loop:
    subplane_qm_1 = subplane_qm(ultimate_subplane_so_far);
    if ( !TRUEP(subplane_qm_1))
	goto end_loop;
    ultimate_subplane_so_far = subplane_qm_1;
    goto next_loop;
  end_loop:
    return VALUES_1(ultimate_subplane_so_far);
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

/* HANDLE-IMAGE-PLANE-EVENT */
Object handle_image_plane_event(action_name,image_plane,x_in_window,
	    y_in_window)
    Object action_name, image_plane, x_in_window, y_in_window;
{
    Object plane_with_mouse_focus, lead_plane, can_handle_qm;
    Object require_maximally_within_pane_qm, lead_plane_x_origin;
    Object lead_plane_y_origin, lead_plane_x_scale, lead_plane_y_scale;
    Object workspace;
    Object result;

    x_note_fn_call(129,17);
    plane_with_mouse_focus = image_plane;
    lead_plane = 
	    find_base_plane_in_stack_of_coupled_image_planes(plane_with_mouse_focus);
    can_handle_qm = T;
    require_maximally_within_pane_qm = Nil;
    result = test_restrictions_for_image_plane_action(action_name,lead_plane);
    MVS_2(result,can_handle_qm,require_maximally_within_pane_qm);
    if (can_handle_qm) {
	if (memq_function(action_name,list_constant)) {
	    if ( !TRUEP(embedded_image_plane_p(image_plane)))
		handle_shift_image_plane_action(image_plane,action_name,
			require_maximally_within_pane_qm);
	}
	else {
	    lead_plane_x_origin = ISVREF(lead_plane,(SI_Long)13L);
	    lead_plane_y_origin = ISVREF(lead_plane,(SI_Long)14L);
	    lead_plane_x_scale = ISVREF(lead_plane,(SI_Long)11L);
	    lead_plane_y_scale = ISVREF(lead_plane,(SI_Long)12L);
	    handle_image_plane_event_inner(action_name,lead_plane,
		    x_in_window,y_in_window,require_maximally_within_pane_qm);
	    transform_subplanes_per_lead_plane(find_ultimate_superplane_in_stack_of_coupled_image_planes(lead_plane),
		    lead_plane,lead_plane_x_origin,lead_plane_y_origin,
		    lead_plane_x_scale,lead_plane_y_scale);
	}
	workspace = ISVREF(image_plane,(SI_Long)5L);
	if (workspace)
	    return trigger_user_icon_movement_rules_for_blocks(workspace);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qriding_workspace_x_offset_qm;  /* riding-workspace-x-offset? */

static Object Qriding_workspace_y_offset_qm;  /* riding-workspace-y-offset? */

/* TRANSFORM-SUBPLANES-PER-LEAD-PLANE */
Object transform_subplanes_per_lead_plane(subplane,lead_plane,
	    old_lead_plane_x_origin,old_lead_plane_y_origin,
	    old_lead_plane_x_scale,old_lead_plane_y_scale)
    Object subplane, lead_plane, old_lead_plane_x_origin;
    Object old_lead_plane_y_origin, old_lead_plane_x_scale;
    Object old_lead_plane_y_scale;
{
    Object temp, temp_1, scale, value, scale_1, temp_2, temp_4, subplane_qm_1;
    SI_Long gensymed_symbol, temp_3, gensymed_symbol_1, unshifted_result;

    x_note_fn_call(129,18);
    if (!EQ(subplane,lead_plane)) {
	temp = ISVREF(lead_plane,(SI_Long)11L);
	temp_1 = ISVREF(lead_plane,(SI_Long)12L);
	gensymed_symbol = IFIX(ISVREF(lead_plane,(SI_Long)13L));
	scale = ISVREF(lead_plane,(SI_Long)11L);
	value = get_slot_value_if_any_function(ISVREF(subplane,
		(SI_Long)5L),Qriding_workspace_x_offset_qm,Nil);
	if (value);
	else {
	    scale_1 = old_lead_plane_x_scale;
	    value = FIXNUM_MINUS(ISVREF(subplane,(SI_Long)13L),
		    old_lead_plane_x_origin);
	    if (IFIX(scale_1) == (SI_Long)4096L);
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
		value = inverse_scalef_function(scale_1,value);
	    else if (IFIX(value) >= (SI_Long)0L) {
		temp_2 = FIX(((IFIX(value) << (SI_Long)12L) + 
			(IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1));
		value = temp_2;
	    }
	    else {
		temp_3 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			(IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1);
		temp_2 = FIXNUM_NEGATE(FIX(temp_3));
		value = temp_2;
	    }
	}
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	temp_2 = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(ISVREF(lead_plane,(SI_Long)14L));
	scale = ISVREF(lead_plane,(SI_Long)12L);
	value = get_slot_value_if_any_function(ISVREF(subplane,
		(SI_Long)5L),Qriding_workspace_y_offset_qm,Nil);
	if (value);
	else {
	    scale_1 = old_lead_plane_y_scale;
	    value = FIXNUM_MINUS(ISVREF(subplane,(SI_Long)14L),
		    old_lead_plane_y_origin);
	    if (IFIX(scale_1) == (SI_Long)4096L);
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value) && FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)))
		value = inverse_scalef_function(scale_1,value);
	    else if (IFIX(value) >= (SI_Long)0L) {
		temp_4 = FIX(((IFIX(value) << (SI_Long)12L) + 
			(IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1));
		value = temp_4;
	    }
	    else {
		temp_3 = ((IFIX(FIXNUM_NEGATE(value)) << (SI_Long)12L) + 
			(IFIX(scale_1) >>  -  - (SI_Long)1L)) / IFIX(scale_1);
		temp_4 = FIXNUM_NEGATE(FIX(temp_3));
		value = temp_4;
	    }
	}
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,value));
	transform_image(16,subplane,Nil,temp,temp_1,Nil,Nil,
		FIX((SI_Long)0L),FIX((SI_Long)0L),temp_2,
		FIX(gensymed_symbol + gensymed_symbol_1),Nil,Nil,Nil,Nil,
		Nil,Nil);
    }
    subplane_qm_1 = subplane_qm(subplane);
    if (subplane_qm_1)
	return transform_subplanes_per_lead_plane(subplane_qm_1,lead_plane,
		old_lead_plane_x_origin,old_lead_plane_y_origin,
		old_lead_plane_x_scale,old_lead_plane_y_scale);
    else
	return VALUES_1(Nil);
}

static Object Qscale_workspace;    /* scale-workspace */

static Object Qmove_workspace;     /* move-workspace */

static Object Qmove_workspaces_beyond_window_margin;  /* move-workspaces-beyond-window-margin */

static Object list_constant_1;     /* # */

/* TEST-RESTRICTIONS-FOR-IMAGE-PLANE-ACTION */
Object test_restrictions_for_image_plane_action(action_name,image_plane)
    Object action_name, image_plane;
{
    Object workspace_on_image_plane, sub_class_bit_vector, non_kb_workspace_p;
    Object scale_workspace_allowed_p, move_workspace_allowed_p, can_scale_qm;
    Object can_move_qm, require_maximally_within_pane_qm, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(129,19);
    workspace_on_image_plane = ISVREF(image_plane,(SI_Long)5L);
    sub_class_bit_vector = ISVREF(ISVREF(workspace_on_image_plane,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Non_kb_workspace_class_description,(SI_Long)18L));
    sub_class_vector_index = superior_class_bit_number >>  -  - (SI_Long)3L;
    if (sub_class_vector_index < 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	gensymed_symbol = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		sub_class_vector_index);
	gensymed_symbol_1 = (SI_Long)1L;
	gensymed_symbol_2 = superior_class_bit_number & (SI_Long)7L;
	gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
	gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
	non_kb_workspace_p = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	non_kb_workspace_p = Nil;
    scale_workspace_allowed_p = 
	    non_menu_choice_permitted_p(Qscale_workspace,
	    workspace_on_image_plane);
    move_workspace_allowed_p = non_menu_choice_permitted_p(Qmove_workspace,
	    workspace_on_image_plane);
    can_scale_qm = non_kb_workspace_p;
    if (can_scale_qm);
    else
	can_scale_qm = scale_workspace_allowed_p;
    can_move_qm = non_kb_workspace_p || move_workspace_allowed_p ? ( 
	    !TRUEP(image_plane_fixed_in_place_p(image_plane)) ? T : Nil) : 
	    Qnil;
    require_maximally_within_pane_qm =  !TRUEP(non_kb_workspace_p) ? ( 
	    !TRUEP(non_menu_choice_permitted_p(Qmove_workspaces_beyond_window_margin,
	    workspace_on_image_plane)) ? T : Nil) : Qnil;
    if (member_eql(action_name,list_constant_1)) {
	if (can_scale_qm) {
	    temp = can_move_qm;
	    if (temp);
	    else
		temp = image_plane_fixed_in_place_p(image_plane);
	}
	else
	    temp = Nil;
    }
    else if (member_eql(action_name,list_constant))
	temp = can_move_qm;
    else
	temp = Qnil;
    return VALUES_2(temp,require_maximally_within_pane_qm);
}

static Object Qcenter_origin;      /* center-origin */

/* HANDLE-SHIFT-IMAGE-PLANE-ACTION */
Object handle_shift_image_plane_action(image_plane,action_name,
	    require_maximally_within_pane_qm)
    Object image_plane, action_name, require_maximally_within_pane_qm;
{
    Object x_in_workspace_qm, y_in_workspace_qm, x_in_window_qm;
    Object y_in_window_qm, scale, value, new_mouse_x, new_mouse_y, temp;
    Object temp_1, temp_2, temp_3;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long unshifted_result, dx_in_window, dy_in_window;
    Object result;

    x_note_fn_call(129,20);
    result = decode_image_plane_shift_action(image_plane,action_name);
    MVS_4(result,x_in_workspace_qm,y_in_workspace_qm,x_in_window_qm,
	    y_in_window_qm);
    if (x_in_workspace_qm && x_in_window_qm) {
	gensymed_symbol = IFIX(x_in_window_qm);
	gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)13L));
	scale = ISVREF(image_plane,(SI_Long)11L);
	value = x_in_workspace_qm;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	dx_in_window = gensymed_symbol - gensymed_symbol_1;
    }
    else
	dx_in_window = (SI_Long)0L;
    if (y_in_workspace_qm && y_in_window_qm) {
	gensymed_symbol = IFIX(y_in_window_qm);
	gensymed_symbol_1 = IFIX(ISVREF(image_plane,(SI_Long)14L));
	scale = ISVREF(image_plane,(SI_Long)12L);
	value = y_in_workspace_qm;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_2 = IFIX(value);
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,value) && 
		FIXNUM_LT(value,Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
		    (SI_Long)2048L;
	    gensymed_symbol_2 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_2 = IFIX(scalef_function(scale,value));
	gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
	dy_in_window = gensymed_symbol - gensymed_symbol_1;
    }
    else
	dy_in_window = (SI_Long)0L;
    raise_image_plane_to_top(1,image_plane);
    move_image_plane(image_plane,FIX(dx_in_window),FIX(dy_in_window));
    require_that_image_plane_be_visible(2,image_plane,
	    require_maximally_within_pane_qm);
    new_mouse_x = EQ(action_name,Qcenter_origin) ? ISVREF(image_plane,
	    (SI_Long)13L) : FIX(IFIX(ISVREF(Current_workstation,
	    (SI_Long)5L)) + dx_in_window);
    new_mouse_y = EQ(action_name,Qcenter_origin) ? ISVREF(image_plane,
	    (SI_Long)14L) : FIX(IFIX(ISVREF(Current_workstation,
	    (SI_Long)6L)) + dy_in_window);
    temp = ISVREF(image_plane,(SI_Long)6L);
    temp_1 = FIXNUM_SUB1(ISVREF(image_plane,(SI_Long)8L));
    temp_2 = FIXNUM_MIN(temp_1,new_mouse_x);
    temp_3 = ISVREF(image_plane,(SI_Long)7L);
    temp_1 = FIXNUM_SUB1(ISVREF(image_plane,(SI_Long)9L));
    temp_1 = FIXNUM_MIN(temp_1,new_mouse_y);
    return set_cursor_position(FIXNUM_MAX(temp,temp_2),FIXNUM_MAX(temp_3,
	    temp_1));
}

static Object Qscale_to_fit;       /* scale-to-fit */

static Object Qmaximum_scale_to_fit;  /* maximum-scale-to-fit */

static Object list_constant_2;     /* # */

static Object Qfull_scale;         /* full-scale */

static Object Qnormalized_full_scale;  /* normalized-full-scale */

static Object Qone_quarter_the_scale;  /* one-quarter-the-scale */

static Object Qfour_times_the_scale;  /* four-times-the-scale */

static Object Qtwenty_percent_smaller;  /* twenty-percent-smaller */

static Object Qtwenty_percent_narrower;  /* twenty-percent-narrower */

static Object Qtwenty_percent_bigger;  /* twenty-percent-bigger */

static Object Qtwenty_percent_wider;  /* twenty-percent-wider */

/* HANDLE-IMAGE-PLANE-EVENT-INNER */
Object handle_image_plane_event_inner(action_name,image_plane,
	    cursor_x_in_window,cursor_y_in_window,
	    require_maximally_within_pane_qm)
    Object action_name, image_plane, cursor_x_in_window, cursor_y_in_window;
    Object require_maximally_within_pane_qm;
{
    Object original_x_origin_of_workspace_in_window;
    Object original_y_origin_of_workspace_in_window, workspace_on_image_plane;
    Object gensymed_symbol, transform_image_operation_hint, x_magnification_qm;
    Object old_image_x_scale, old_image_y_scale, new_image_x_scale_qm;
    Object new_image_y_scale_qm, x_scale_to_be, y_scale_to_be, single_view_p;
    Object scale, scaled_x_in_midpane_in_workspace, temp;
    Object scaled_y_in_midpane_in_workspace, image_left_border_width;
    Object image_right_border_width, image_top_border_width;
    Object image_bottom_border_width, x_in_window, y_in_window, x_in_workspace;
    Object value_1, y_in_workspace;
    SI_Long midline_x_of_pane, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long midline_x_of_workspace, midline_y_of_pane, midline_y_of_workspace;
    SI_Long value, temp_1, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long unshifted_result;
    char image_fits_widthwise_in_view_p, image_fits_heightwise_in_view_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,21);
    original_x_origin_of_workspace_in_window = ISVREF(image_plane,
	    (SI_Long)13L);
    original_y_origin_of_workspace_in_window = ISVREF(image_plane,
	    (SI_Long)14L);
    workspace_on_image_plane = ISVREF(image_plane,(SI_Long)5L);
    midline_x_of_pane = IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),
	    ISVREF(image_plane,(SI_Long)8L))) >>  -  - (SI_Long)1L;
    gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    midline_x_of_workspace = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    midline_y_of_pane = IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)7L),
	    ISVREF(image_plane,(SI_Long)9L))) >>  -  - (SI_Long)1L;
    gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)1L;
    midline_y_of_workspace = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
    if (EQ(action_name,Qscale_to_fit) || EQ(action_name,
		Qmaximum_scale_to_fit)) {
	transform_image_operation_hint = Qscale_to_fit;
	PUSH_SPECIAL_WITH_SYMBOL(Transform_image_operation_hint,Qtransform_image_operation_hint,transform_image_operation_hint,
		0);
	  transform_image(15,image_plane,Nil,Nil,Nil,EQ(action_name,
		  Qmaximum_scale_to_fit) ? FIX((SI_Long)-262L) : 
		  FIX((SI_Long)262L),Nil,FIX(midline_x_of_workspace),
		  FIX(midline_y_of_workspace),FIX(midline_x_of_pane),
		  FIX(midline_y_of_pane),Nil,Nil,Nil,Nil,T);
	  result = require_that_image_plane_be_visible(2,image_plane,
		  require_maximally_within_pane_qm);
	POP_SPECIAL();
	return result;
    }
    else if (member_eql(action_name,list_constant_2)) {
	x_magnification_qm = Nil;
	old_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
	old_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
	if (EQ(action_name,Qfull_scale))
	    new_image_x_scale_qm = get_default_image_x_scale(image_plane);
	else if (EQ(action_name,Qnormalized_full_scale))
	    new_image_x_scale_qm = FIX((SI_Long)4096L);
	else {
	    if (EQ(action_name,Qone_quarter_the_scale))
		x_magnification_qm = FIX((SI_Long)128L);
	    else if (EQ(action_name,Qfour_times_the_scale))
		x_magnification_qm = FIX((SI_Long)512L);
	    else if (EQ(action_name,Qtwenty_percent_smaller) || 
		    EQ(action_name,Qtwenty_percent_narrower))
		x_magnification_qm = FIX((SI_Long)198L);
	    else if (EQ(action_name,Qtwenty_percent_bigger) || 
		    EQ(action_name,Qtwenty_percent_wider))
		x_magnification_qm = FIX((SI_Long)331L);
	    else
		x_magnification_qm = Qnil;
	    new_image_x_scale_qm = FIX(IFIX(ltimes(old_image_x_scale,
		    x_magnification_qm)) + (SI_Long)128L >>  -  - (SI_Long)8L);
	}
	if (EQ(action_name,Qfull_scale))
	    new_image_y_scale_qm = get_default_image_y_scale(image_plane);
	else if (EQ(action_name,Qnormalized_full_scale))
	    new_image_y_scale_qm = FIX((SI_Long)4096L);
	else
	    new_image_y_scale_qm = EQ(action_name,Qone_quarter_the_scale) 
		    || EQ(action_name,Qfour_times_the_scale) || 
		    EQ(action_name,Qtwenty_percent_smaller) || 
		    EQ(action_name,Qtwenty_percent_bigger) ? 
		    FIX(IFIX(FIXNUM_TIMES(old_image_y_scale,
		    x_magnification_qm)) + (SI_Long)128L >>  -  - 
		    (SI_Long)8L) : Nil;
	x_scale_to_be = new_image_x_scale_qm;
	if (x_scale_to_be);
	else
	    x_scale_to_be = old_image_x_scale;
	y_scale_to_be = new_image_y_scale_qm;
	if (y_scale_to_be);
	else
	    y_scale_to_be = old_image_y_scale;
	single_view_p = Nil;
	scale = old_image_x_scale;
	value = midline_x_of_pane - 
		IFIX(original_x_origin_of_workspace_in_window);
	if (IFIX(scale) == (SI_Long)4096L)
	    scaled_x_in_midpane_in_workspace = FIX(value);
	else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		&& value < IFIX(Isqrt_of_most_positive_fixnum)))
	    scaled_x_in_midpane_in_workspace = 
		    inverse_scalef_function(scale,FIX(value));
	else if (value >= (SI_Long)0L) {
	    temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		    (SI_Long)1L)) / IFIX(scale));
	    scaled_x_in_midpane_in_workspace = temp;
	}
	else {
	    temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		    (SI_Long)1L)) / IFIX(scale);
	    temp = FIXNUM_NEGATE(FIX(temp_1));
	    scaled_x_in_midpane_in_workspace = temp;
	}
	scale = old_image_y_scale;
	value = midline_y_of_pane - 
		IFIX(original_y_origin_of_workspace_in_window);
	if (IFIX(scale) == (SI_Long)4096L)
	    scaled_y_in_midpane_in_workspace = FIX(value);
	else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		&& value < IFIX(Isqrt_of_most_positive_fixnum)))
	    scaled_y_in_midpane_in_workspace = 
		    inverse_scalef_function(scale,FIX(value));
	else if (value >= (SI_Long)0L) {
	    temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		    (SI_Long)1L)) / IFIX(scale));
	    scaled_y_in_midpane_in_workspace = temp;
	}
	else {
	    temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		    (SI_Long)1L)) / IFIX(scale);
	    temp = FIXNUM_NEGATE(FIX(temp_1));
	    scaled_y_in_midpane_in_workspace = temp;
	}
	image_left_border_width = FIXNUM_MINUS(ISVREF(image_plane,
		(SI_Long)19L),ISVREF(image_plane,(SI_Long)15L));
	image_right_border_width = FIXNUM_MINUS(ISVREF(image_plane,
		(SI_Long)21L),ISVREF(image_plane,(SI_Long)17L));
	image_top_border_width = FIXNUM_MINUS(ISVREF(image_plane,
		(SI_Long)20L),ISVREF(image_plane,(SI_Long)16L));
	image_bottom_border_width = FIXNUM_MINUS(ISVREF(image_plane,
		(SI_Long)22L),ISVREF(image_plane,(SI_Long)18L));
	gensymed_symbol_1 = IFIX(image_left_border_width);
	gensymed_symbol_2 = IFIX(image_right_border_width);
	scale = x_scale_to_be;
	gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	value = gensymed_symbol_3 - gensymed_symbol_4;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(scale,FIX(value)));
	image_fits_widthwise_in_view_p = FIXNUM_LT(FIX(gensymed_symbol_1 + 
		gensymed_symbol_2 + gensymed_symbol_3),
		FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		ISVREF(image_plane,(SI_Long)6L)));
	gensymed_symbol_1 = IFIX(image_top_border_width);
	gensymed_symbol_2 = IFIX(image_bottom_border_width);
	scale = y_scale_to_be;
	gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(workspace_on_image_plane,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	value = gensymed_symbol_3 - gensymed_symbol_4;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_3 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_3 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_3 = IFIX(scalef_function(scale,FIX(value)));
	image_fits_heightwise_in_view_p = FIXNUM_LE(FIX(gensymed_symbol_1 
		+ gensymed_symbol_2 + gensymed_symbol_3),
		FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		ISVREF(image_plane,(SI_Long)7L)));
	x_in_window = single_view_p ? FIX(midline_x_of_pane) : 
		cursor_x_in_window;
	y_in_window = single_view_p ? FIX(midline_y_of_pane) : 
		cursor_y_in_window;
	if (single_view_p)
	    x_in_workspace = image_fits_widthwise_in_view_p ? 
		    FIX(midline_x_of_workspace) : 
		    scaled_x_in_midpane_in_workspace;
	else {
	    scale = old_image_x_scale;
	    value_1 = FIXNUM_MINUS(x_in_window,
		    original_x_origin_of_workspace_in_window);
	    if (IFIX(scale) == (SI_Long)4096L)
		x_in_workspace = value_1;
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value_1) && FIXNUM_LT(value_1,
		    Isqrt_of_most_positive_fixnum)))
		x_in_workspace = inverse_scalef_function(scale,value_1);
	    else if (IFIX(value_1) >= (SI_Long)0L) {
		temp = FIX(((IFIX(value_1) << (SI_Long)12L) + (IFIX(scale) 
			>>  -  - (SI_Long)1L)) / IFIX(scale));
		x_in_workspace = temp;
	    }
	    else {
		temp_1 = ((IFIX(FIXNUM_NEGATE(value_1)) << (SI_Long)12L) + 
			(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		temp = FIXNUM_NEGATE(FIX(temp_1));
		x_in_workspace = temp;
	    }
	}
	if (single_view_p)
	    y_in_workspace = image_fits_heightwise_in_view_p ? 
		    FIX(midline_y_of_workspace) : 
		    scaled_y_in_midpane_in_workspace;
	else {
	    scale = old_image_y_scale;
	    value_1 = FIXNUM_MINUS(y_in_window,
		    original_y_origin_of_workspace_in_window);
	    if (IFIX(scale) == (SI_Long)4096L)
		y_in_workspace = value_1;
	    else if ( !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    value_1) && FIXNUM_LT(value_1,
		    Isqrt_of_most_positive_fixnum)))
		y_in_workspace = inverse_scalef_function(scale,value_1);
	    else if (IFIX(value_1) >= (SI_Long)0L) {
		temp = FIX(((IFIX(value_1) << (SI_Long)12L) + (IFIX(scale) 
			>>  -  - (SI_Long)1L)) / IFIX(scale));
		y_in_workspace = temp;
	    }
	    else {
		temp_1 = ((IFIX(FIXNUM_NEGATE(value_1)) << (SI_Long)12L) + 
			(IFIX(scale) >>  -  - (SI_Long)1L)) / IFIX(scale);
		temp = FIXNUM_NEGATE(FIX(temp_1));
		y_in_workspace = temp;
	    }
	}
	transform_image_operation_hint = action_name;
	PUSH_SPECIAL_WITH_SYMBOL(Transform_image_operation_hint,Qtransform_image_operation_hint,transform_image_operation_hint,
		0);
	  transform_image(10,image_plane,Nil,new_image_x_scale_qm,
		  new_image_y_scale_qm,Nil,Nil,x_in_workspace,
		  y_in_workspace,x_in_window,y_in_window);
	  if ( !TRUEP(single_view_p))
	      result = require_that_image_plane_be_visible(2,image_plane,
		      require_maximally_within_pane_qm);
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else if (member_eql(action_name,list_constant))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

static Object Qshift_left_ten_percent;  /* shift-left-ten-percent */

static Object Qshift_left_one_percent;  /* shift-left-one-percent */

static Object Qshift_right_ten_percent;  /* shift-right-ten-percent */

static Object Qshift_right_one_percent;  /* shift-right-one-percent */

static Object Qshift_up_ten_percent;  /* shift-up-ten-percent */

static Object Qshift_up_one_percent;  /* shift-up-one-percent */

static Object Qshift_down_ten_percent;  /* shift-down-ten-percent */

static Object Qshift_down_one_percent;  /* shift-down-one-percent */

/* DECODE-IMAGE-PLANE-SHIFT-ACTION */
Object decode_image_plane_shift_action(image_plane,action_name)
    Object image_plane, action_name;
{
    Object x_in_workspace, y_in_workspace, x_in_window, y_in_window, temp;
    Object temp_1, temp_2;

    x_note_fn_call(129,22);
    x_in_workspace = Nil;
    y_in_workspace = Nil;
    x_in_window = Nil;
    y_in_window = Nil;
    if (EQ(action_name,Qcenter_origin)) {
	x_in_workspace = FIX((SI_Long)0L);
	y_in_workspace = FIX((SI_Long)0L);
	x_in_window = FIX(IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)6L),
		ISVREF(image_plane,(SI_Long)8L))) >>  -  - (SI_Long)1L);
	y_in_window = FIX(IFIX(FIXNUM_ADD(ISVREF(image_plane,(SI_Long)7L),
		ISVREF(image_plane,(SI_Long)9L))) >>  -  - (SI_Long)1L);
    }
    else if (EQ(action_name,Qshift_left_ten_percent) || EQ(action_name,
	    Qshift_left_one_percent) || EQ(action_name,
	    Qshift_right_ten_percent) || EQ(action_name,
	    Qshift_right_one_percent)) {
	x_in_workspace = FIX((SI_Long)0L);
	temp = ISVREF(image_plane,(SI_Long)13L);
	temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)8L),
		ISVREF(image_plane,(SI_Long)6L));
	if (EQ(action_name,Qshift_left_ten_percent))
	    temp_2 = FIX((SI_Long)-10L);
	else if (EQ(action_name,Qshift_left_one_percent))
	    temp_2 = FIX((SI_Long)-100L);
	else if (EQ(action_name,Qshift_right_ten_percent))
	    temp_2 = FIX((SI_Long)10L);
	else
	    temp_2 = FIX((SI_Long)100L);
	x_in_window = FIXNUM_ADD(temp,l_round(temp_1,temp_2));
    }
    else if (EQ(action_name,Qshift_up_ten_percent) || EQ(action_name,
	    Qshift_up_one_percent) || EQ(action_name,
	    Qshift_down_ten_percent) || EQ(action_name,
	    Qshift_down_one_percent)) {
	y_in_workspace = FIX((SI_Long)0L);
	temp = ISVREF(image_plane,(SI_Long)14L);
	temp_1 = FIXNUM_MINUS(ISVREF(image_plane,(SI_Long)9L),
		ISVREF(image_plane,(SI_Long)7L));
	if (EQ(action_name,Qshift_up_ten_percent))
	    temp_2 = FIX((SI_Long)-10L);
	else if (EQ(action_name,Qshift_up_one_percent))
	    temp_2 = FIX((SI_Long)-100L);
	else if (EQ(action_name,Qshift_down_ten_percent))
	    temp_2 = FIX((SI_Long)10L);
	else
	    temp_2 = FIX((SI_Long)100L);
	y_in_window = FIXNUM_ADD(temp,l_round(temp_1,temp_2));
    }
    return VALUES_4(x_in_workspace,y_in_workspace,x_in_window,y_in_window);
}

static Object Qtop_level;          /* top-level */

/* RUN-TOP-LEVEL-EVENT-HANDLER */
Object run_top_level_event_handler(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, top_level_context, event_interpretation_qm;

    x_note_fn_call(129,23);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (mouse_pointer_1) {
	top_level_context = find_workstation_context(1,Qtop_level);
	event_interpretation_qm = lookup_key_in_context(top_level_context,
		ISVREF(mouse_pointer_1,(SI_Long)8L),ISVREF(mouse_pointer_1,
		(SI_Long)5L));
	if (event_interpretation_qm) {
	    run_event_handler(event_interpretation_qm,mouse_pointer_1);
	    return reclaim_event_interpretation(event_interpretation_qm);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-LEEWAY-IN-WORKSPACE */
Object mouse_leeway_in_workspace(image_x_scale)
    Object image_x_scale;
{
    Object scale, temp;
    SI_Long gensymed_symbol, unshifted_result, gensymed_symbol_1, value;
    SI_Long temp_1;

    x_note_fn_call(129,24);
    scale = image_x_scale;
    if (IFIX(image_x_scale) == (SI_Long)4096L)
	gensymed_symbol = IFIX(Constant_mouse_leeway);
    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    image_x_scale) && FIXNUM_LT(image_x_scale,
	    Isqrt_of_most_positive_fixnum) && 
	    FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
	    Constant_mouse_leeway) && FIXNUM_LT(Constant_mouse_leeway,
	    Isqrt_of_most_positive_fixnum)) {
	unshifted_result = IFIX(FIXNUM_TIMES(image_x_scale,
		Constant_mouse_leeway)) + (SI_Long)2048L;
	gensymed_symbol = unshifted_result >>  -  - (SI_Long)12L;
    }
    else
	gensymed_symbol = IFIX(scalef_function(image_x_scale,
		Constant_mouse_leeway));
    gensymed_symbol_1 = IFIX(Scalable_mouse_leeway);
    value = gensymed_symbol + gensymed_symbol_1;
    if (IFIX(scale) == (SI_Long)4096L)
	temp = FIX(value);
    else if ( !(IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
	    value < IFIX(Isqrt_of_most_positive_fixnum)))
	temp = inverse_scalef_function(scale,FIX(value));
    else if (value >= (SI_Long)0L)
	temp = FIX(((value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale));
    else {
	temp_1 = (( - value << (SI_Long)12L) + (IFIX(scale) >>  -  - 
		(SI_Long)1L)) / IFIX(scale);
	temp = FIXNUM_NEGATE(FIX(temp_1));
    }
    return VALUES_1(temp);
}

Object Minimum_x_scale_for_picking = UNBOUND;

Object Minimum_width_or_height_for_picking_in_window_units = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Finding_object_near_mouse, Qfinding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(Image_plane_for_finding_object_near_mouse, Qimage_plane_for_finding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(X_in_window_for_finding_object_near_mouse, Qx_in_window_for_finding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(Y_in_window_for_finding_object_near_mouse, Qy_in_window_for_finding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(Image_x_scale_for_finding_object_near_mouse, Qimage_x_scale_for_finding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(Image_y_scale_for_finding_object_near_mouse, Qimage_y_scale_for_finding_object_near_mouse);

DEFINE_VARIABLE_WITH_SYMBOL(Classes_of_objects_to_not_consider_qm, Qclasses_of_objects_to_not_consider_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Mouse_x_in_workspace, Qmouse_x_in_workspace);

DEFINE_VARIABLE_WITH_SYMBOL(Mouse_y_in_workspace, Qmouse_y_in_workspace);

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* FIND-OBJECT-NEAR-MOUSE */
Object find_object_near_mouse(x_in_window,y_in_window,image_plane,
	    objects_to_not_consider_qm,classes_of_objects_to_not_consider_qm)
    Object x_in_window, y_in_window, image_plane, objects_to_not_consider_qm;
    Object classes_of_objects_to_not_consider_qm;
{
    Object image_plane_for_finding_object_near_mouse;
    Object x_in_window_for_finding_object_near_mouse;
    Object y_in_window_for_finding_object_near_mouse;
    Object image_x_scale_for_finding_object_near_mouse;
    Object image_y_scale_for_finding_object_near_mouse, mouse_x_in_workspace;
    Object mouse_y_in_workspace, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing, scale;
    Object value, temp, workspace_on_image_plane, maximum_distance_to_allow;
    Object temp_2, loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, object_qm, x2;
    Object gensymed_symbol;
    SI_Long temp_1, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long value_1, unshifted_result;
    char temp_3;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(14);
    Object result;

    x_note_fn_call(129,25);
    SAVE_STACK();
    PUSH_SPECIAL_WITH_SYMBOL(Classes_of_objects_to_not_consider_qm,Qclasses_of_objects_to_not_consider_qm,classes_of_objects_to_not_consider_qm,
	    13);
      PUSH_SPECIAL_WITH_SYMBOL(Objects_to_not_consider_qm,Qobjects_to_not_consider_qm,objects_to_not_consider_qm,
	      12);
	LOCK(Finding_object_near_mouse);
	if (PUSH_UNWIND_PROTECT(0)) {
	    image_plane_for_finding_object_near_mouse = image_plane;
	    x_in_window_for_finding_object_near_mouse = x_in_window;
	    y_in_window_for_finding_object_near_mouse = y_in_window;
	    image_x_scale_for_finding_object_near_mouse = Nil;
	    image_y_scale_for_finding_object_near_mouse = Nil;
	    mouse_x_in_workspace = Nil;
	    mouse_y_in_workspace = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Mouse_y_in_workspace,Qmouse_y_in_workspace,mouse_y_in_workspace,
		    11);
	      PUSH_SPECIAL_WITH_SYMBOL(Mouse_x_in_workspace,Qmouse_x_in_workspace,mouse_x_in_workspace,
		      10);
		PUSH_SPECIAL_WITH_SYMBOL(Image_y_scale_for_finding_object_near_mouse,Qimage_y_scale_for_finding_object_near_mouse,image_y_scale_for_finding_object_near_mouse,
			9);
		  PUSH_SPECIAL_WITH_SYMBOL(Image_x_scale_for_finding_object_near_mouse,Qimage_x_scale_for_finding_object_near_mouse,image_x_scale_for_finding_object_near_mouse,
			  8);
		    PUSH_SPECIAL_WITH_SYMBOL(Y_in_window_for_finding_object_near_mouse,Qy_in_window_for_finding_object_near_mouse,y_in_window_for_finding_object_near_mouse,
			    7);
		      PUSH_SPECIAL_WITH_SYMBOL(X_in_window_for_finding_object_near_mouse,Qx_in_window_for_finding_object_near_mouse,x_in_window_for_finding_object_near_mouse,
			      6);
			PUSH_SPECIAL_WITH_SYMBOL(Image_plane_for_finding_object_near_mouse,Qimage_plane_for_finding_object_near_mouse,image_plane_for_finding_object_near_mouse,
				5);
			  current_frame_transform_qm = Nil;
			  current_image_x_scale = ISVREF(image_plane,
				  (SI_Long)11L);
			  current_image_y_scale = ISVREF(image_plane,
				  (SI_Long)12L);
			  current_x_origin_of_drawing = ISVREF(image_plane,
				  (SI_Long)13L);
			  current_y_origin_of_drawing = ISVREF(image_plane,
				  (SI_Long)14L);
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
				    Image_x_scale_for_finding_object_near_mouse 
					    = Current_image_x_scale;
				    Image_y_scale_for_finding_object_near_mouse 
					    = Current_image_y_scale;
				    scale = Current_image_x_scale;
				    value = FIXNUM_MINUS(x_in_window,
					    Current_x_origin_of_drawing);
				    if (IFIX(scale) == (SI_Long)4096L)
					Mouse_x_in_workspace = value;
				    else if ( 
					    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					    value) && FIXNUM_LT(value,
					    Isqrt_of_most_positive_fixnum)))
					Mouse_x_in_workspace = 
						inverse_scalef_function(scale,
						value);
				    else if (IFIX(value) >= (SI_Long)0L) {
					temp = FIX(((IFIX(value) << 
						(SI_Long)12L) + 
						(IFIX(scale) >>  -  - 
						(SI_Long)1L)) / IFIX(scale));
					Mouse_x_in_workspace = temp;
				    }
				    else {
					temp_1 = 
						((IFIX(FIXNUM_NEGATE(value)) 
						<< (SI_Long)12L) + 
						(IFIX(scale) >>  -  - 
						(SI_Long)1L)) / IFIX(scale);
					temp = FIXNUM_NEGATE(FIX(temp_1));
					Mouse_x_in_workspace = temp;
				    }
				    scale = Current_image_y_scale;
				    value = FIXNUM_MINUS(y_in_window,
					    Current_y_origin_of_drawing);
				    if (IFIX(scale) == (SI_Long)4096L)
					Mouse_y_in_workspace = value;
				    else if ( 
					    !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
					    value) && FIXNUM_LT(value,
					    Isqrt_of_most_positive_fixnum)))
					Mouse_y_in_workspace = 
						inverse_scalef_function(scale,
						value);
				    else if (IFIX(value) >= (SI_Long)0L) {
					temp = FIX(((IFIX(value) << 
						(SI_Long)12L) + 
						(IFIX(scale) >>  -  - 
						(SI_Long)1L)) / IFIX(scale));
					Mouse_y_in_workspace = temp;
				    }
				    else {
					temp_1 = 
						((IFIX(FIXNUM_NEGATE(value)) 
						<< (SI_Long)12L) + 
						(IFIX(scale) >>  -  - 
						(SI_Long)1L)) / IFIX(scale);
					temp = FIXNUM_NEGATE(FIX(temp_1));
					Mouse_y_in_workspace = temp;
				    }
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			  workspace_on_image_plane = ISVREF(image_plane,
				  (SI_Long)5L);
			  maximum_distance_to_allow = 
				  mouse_leeway_in_workspace(Image_x_scale_for_finding_object_near_mouse);
			  temp_2 = FIXNUM_MINUS(Mouse_x_in_workspace,
				  maximum_distance_to_allow);
			  temp = ISVREF(image_plane,(SI_Long)23L);
			  loose_left_edge_of_visible_workspace_area = 
				  FIXNUM_MAX(temp_2,temp);
			  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
				  3);
			    temp_2 = FIXNUM_MINUS(Mouse_y_in_workspace,
				    maximum_distance_to_allow);
			    temp = ISVREF(image_plane,(SI_Long)24L);
			    loose_top_edge_of_visible_workspace_area = 
				    FIXNUM_MAX(temp_2,temp);
			    PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
				    2);
			      temp_2 = FIXNUM_ADD(Mouse_x_in_workspace,
				      maximum_distance_to_allow);
			      temp = ISVREF(image_plane,(SI_Long)25L);
			      loose_right_edge_of_visible_workspace_area = 
				      FIXNUM_MIN(temp_2,temp);
			      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
				      1);
				temp_2 = FIXNUM_ADD(Mouse_y_in_workspace,
					maximum_distance_to_allow);
				temp = ISVREF(image_plane,(SI_Long)26L);
				loose_bottom_edge_of_visible_workspace_area 
					= FIXNUM_MIN(temp_2,temp);
				PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
					0);
				  object_qm = 
					  find_object_near_mouse_1(workspace_on_image_plane,
					  maximum_distance_to_allow,T);
				  if (object_qm) {
				      temp_3 =  
					      !FIXNUM_LT(Image_x_scale_for_finding_object_near_mouse,
					      Minimum_x_scale_for_picking);
				      if (temp_3);
				      else {
					  if (SIMPLE_VECTOR_P(object_qm) 
						  && 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(object_qm)) 
						  > (SI_Long)2L &&  
						  !EQ(ISVREF(object_qm,
						  (SI_Long)1L),
						  Qavailable_frame_vector)) {
					      x2 = ISVREF(object_qm,
						      (SI_Long)1L);
					      temp_3 = SIMPLE_VECTOR_P(x2) 
						      && EQ(ISVREF(x2,
						      (SI_Long)0L),
						      Qg2_defstruct_structure_name_class_description_g2_struct) 
						      ? TRUEP(x2) : 
						      TRUEP(Qnil);
					  }
					  else
					      temp_3 = TRUEP(Nil);
					  if (temp_3) {
					      scale = 
						      Image_x_scale_for_finding_object_near_mouse;
					      gensymed_symbol = 
						      ISVREF(object_qm,
						      (SI_Long)14L);
					      gensymed_symbol = 
						      gensymed_symbol ? 
						      ISVREF(gensymed_symbol,
						      (SI_Long)2L) : 
						      FIX((SI_Long)0L);
					      gensymed_symbol_1 = 
						      IFIX(gensymed_symbol);
					      gensymed_symbol = 
						      ISVREF(object_qm,
						      (SI_Long)14L);
					      gensymed_symbol = 
						      gensymed_symbol ? 
						      ISVREF(gensymed_symbol,
						      (SI_Long)0L) : 
						      FIX((SI_Long)0L);
					      gensymed_symbol_2 = 
						      IFIX(gensymed_symbol);
					      gensymed_symbol_1 = 
						      gensymed_symbol_1 - 
						      gensymed_symbol_2;
					      gensymed_symbol = 
						      ISVREF(object_qm,
						      (SI_Long)14L);
					      gensymed_symbol = 
						      gensymed_symbol ? 
						      ISVREF(gensymed_symbol,
						      (SI_Long)3L) : 
						      FIX((SI_Long)0L);
					      gensymed_symbol_2 = 
						      IFIX(gensymed_symbol);
					      gensymed_symbol = 
						      ISVREF(object_qm,
						      (SI_Long)14L);
					      gensymed_symbol = 
						      gensymed_symbol ? 
						      ISVREF(gensymed_symbol,
						      (SI_Long)1L) : 
						      FIX((SI_Long)0L);
					      gensymed_symbol_3 = 
						      IFIX(gensymed_symbol);
					      gensymed_symbol_2 = 
						      gensymed_symbol_2 - 
						      gensymed_symbol_3;
					      value_1 = 
						      MIN(gensymed_symbol_1,
						      gensymed_symbol_2);
					      if (IFIX(scale) == 
						      (SI_Long)4096L)
						  temp = FIX(value_1);
					      else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
						      scale) && 
						      FIXNUM_LT(scale,
						      Isqrt_of_most_positive_fixnum) 
						      && 
						      IFIX(Minus_of_isqrt_of_most_positive_fixnum) 
						      < value_1 && value_1 
						      < 
						      IFIX(Isqrt_of_most_positive_fixnum)) 
							  {
						  unshifted_result = 
							  IFIX(scale) * 
							  value_1 + 
							  (SI_Long)2048L;
						  temp = 
							  FIX(unshifted_result 
							  >>  -  - 
							  (SI_Long)12L);
					      }
					      else
						  temp = 
							  scalef_function(scale,
							  FIX(value_1));
					      temp_3 =  !NUM_LT(temp,
						      Minimum_width_or_height_for_picking_in_window_units);
					  }
					  else
					      temp_3 = TRUEP(Nil);
				      }
				  }
				  else
				      temp_3 = TRUEP(Nil);
				  if (temp_3)
				      SAVE_VALUES(VALUES_1(object_qm));
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
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Finding_object_near_mouse);
	CONTINUE_UNWINDING(0);
	result = RESTORE_VALUES();
      POP_SPECIAL();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qtext_box;           /* text-box */

static Object Qtable;              /* table */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qcross_section_pattern;  /* cross-section-pattern */

static Object Qconnection;         /* connection */

/* FIND-OBJECT-NEAR-MOUSE-1 */
Object find_object_near_mouse_1(block_to_search,maximum_distance_to_allow,
	    block_being_searched_is_workspace_p)
    Object block_to_search, maximum_distance_to_allow;
    Object block_being_searched_is_workspace_p;
{
    Object nearest_block_qm, nearest_connection_qm;
    Object current_maximum_distance_to_allow_for_blocks;
    Object current_maximum_distance_to_allow_for_connections, connection_qm;
    Object left_edge_of_content_and_frame, top_edge_of_content_and_frame;
    Object right_edge_of_content_and_frame, bottom_edge_of_content_and_frame;
    Object distance_if_in_range_qm, temp, d1, d2, nearest_block_distance_qm;
    Object nearest_connection_distance_qm, distance_from_point_qm;
    Object inheritance_path, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, subblocks, ab_queue_form__1;
    Object ab_next_queue_element__1, subsubblock, ab_loop_it_;
    Object class_description, class_1, ab_loop_list_, subsubblock_qm, distance;
    Object connection, connections, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_2, entry_hash, sub_class_bit_vector;
    Object connection_frame_or_class, x2, cross_section_pattern, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cross_section_stripe, width, ab_loopvar_, ab_loop_desetq_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long expansion_factor, gross_distance_from_connection;
    SI_Long effective_distance_from_connection;
    char temp_1;
    Object result;

    x_note_fn_call(129,26);
    nearest_block_qm =  !TRUEP(block_being_searched_is_workspace_p) ? 
	    block_to_search : Nil;
    nearest_connection_qm = Nil;
    current_maximum_distance_to_allow_for_blocks = maximum_distance_to_allow;
    current_maximum_distance_to_allow_for_connections = 
	    maximum_distance_to_allow;
    connection_qm = Nil;
    if ( !TRUEP(block_being_searched_is_workspace_p)) {
	result = edges_of_block_content_plus_frame(block_to_search);
	MVS_4(result,left_edge_of_content_and_frame,
		top_edge_of_content_and_frame,
		right_edge_of_content_and_frame,
		bottom_edge_of_content_and_frame);
	distance_if_in_range_qm = Nil;
	if (FIXNUM_LT(Mouse_x_in_workspace,left_edge_of_content_and_frame)) {
	    if (FIXNUM_LT(Mouse_y_in_workspace,
			top_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			left_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			top_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else if (FIXNUM_GT(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			left_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			bottom_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else
		distance_if_in_range_qm = 
			FIXNUM_MINUS(left_edge_of_content_and_frame,
			Mouse_x_in_workspace);
	}
	else if (FIXNUM_GT(Mouse_x_in_workspace,
		right_edge_of_content_and_frame)) {
	    if (FIXNUM_LT(Mouse_y_in_workspace,
			top_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			top_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else if (FIXNUM_GT(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			bottom_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else
		distance_if_in_range_qm = 
			FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
	}
	else if (FIXNUM_LT(Mouse_y_in_workspace,top_edge_of_content_and_frame))
	    distance_if_in_range_qm = 
		    FIXNUM_MINUS(top_edge_of_content_and_frame,
		    Mouse_y_in_workspace);
	else if (FIXNUM_GT(Mouse_y_in_workspace,
		bottom_edge_of_content_and_frame))
	    distance_if_in_range_qm = FIXNUM_MINUS(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame);
	else
	    distance_if_in_range_qm = FIX((SI_Long)0L);
	nearest_block_distance_qm = (distance_if_in_range_qm ? 
		FIXNUM_LT(distance_if_in_range_qm,
		current_maximum_distance_to_allow_for_blocks) : 
		TRUEP(Nil)) ? distance_if_in_range_qm : Nil;
	if (nearest_block_distance_qm);
	else {
	    nearest_block_qm = Nil;
	    nearest_block_distance_qm = nearest_block_qm;
	}
    }
    else
	nearest_block_distance_qm = Nil;
    nearest_connection_distance_qm = Nil;
    distance_from_point_qm = Nil;
    inheritance_path = Nil;
    gensymed_symbol = ACCESS_ONCE(ISVREF(block_to_search,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    temp_1 = TRUEP(quick_clipping_check_of_block_for_picking(subblock));
    if (temp_1);
    else {
	gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
		(SI_Long)2L),subblocks))) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form__1 = gensymed_symbol;
	    ab_next_queue_element__1 = Nil;
	    subsubblock = Nil;
	    ab_loop_it_ = Nil;
	    if (ab_queue_form__1)
		ab_next_queue_element__1 = 
			constant_queue_next(ISVREF(ab_queue_form__1,
			(SI_Long)2L),ab_queue_form__1);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element__1))
		goto end_loop_1;
	    subsubblock = ISVREF(ab_next_queue_element__1,(SI_Long)4L);
	    ab_next_queue_element__1 = 
		    constant_queue_next(ab_next_queue_element__1,
		    ab_queue_form__1);
	    ab_loop_it_ = 
		    quick_clipping_check_of_block_for_picking(subsubblock);
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = TRUEP(Qnil);
	  end_1:;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    if (temp_1 ?  !TRUEP(Objects_to_not_consider_qm) ||  
	    !TRUEP(memq_function(subblock,Objects_to_not_consider_qm)) : 
	    TRUEP(Nil)) {
	class_description = ISVREF(subblock,(SI_Long)1L);
	inheritance_path = ISVREF(class_description,(SI_Long)2L);
	temp_1 =  !TRUEP(Classes_of_objects_to_not_consider_qm);
	if (temp_1);
	else {
	    class_1 = Nil;
	    ab_loop_list_ = Classes_of_objects_to_not_consider_qm;
	    ab_loop_it_ = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = memq_function(class_1,inheritance_path);
	    if (ab_loop_it_) {
		temp_1 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = TRUEP(Qnil);
	  end_2:;
	    temp_1 =  !temp_1;
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if ((temp_1 ?  !TRUEP(memq_function(Qtext_box,inheritance_path)) || 
	    text_box_visible_near_mouse_p(subblock) : TRUEP(Nil)) ?  
	    !TRUEP(memq_function(Qtable,inheritance_path)) || 
	    table_visible_near_mouse_p(subblock) : TRUEP(Nil)) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(subblock,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	subblocks = gensymed_symbol;
	if (subblocks &&  ! !TRUEP(constant_queue_next(ISVREF(subblocks,
		(SI_Long)2L),subblocks)))
	    result = find_object_near_mouse_1(subblock,
		    current_maximum_distance_to_allow_for_blocks,Nil);
	else
	    result = VALUES_1(Nil);
	MVS_2(result,subsubblock_qm,distance);
	result = edges_of_block_content_plus_frame(subblock);
	MVS_4(result,left_edge_of_content_and_frame,
		top_edge_of_content_and_frame,
		right_edge_of_content_and_frame,
		bottom_edge_of_content_and_frame);
	distance_if_in_range_qm = Nil;
	if (FIXNUM_LT(Mouse_x_in_workspace,left_edge_of_content_and_frame)) {
	    if (FIXNUM_LT(Mouse_y_in_workspace,
			top_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			left_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			top_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else if (FIXNUM_GT(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			left_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			bottom_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else
		distance_if_in_range_qm = 
			FIXNUM_MINUS(left_edge_of_content_and_frame,
			Mouse_x_in_workspace);
	}
	else if (FIXNUM_GT(Mouse_x_in_workspace,
		right_edge_of_content_and_frame)) {
	    if (FIXNUM_LT(Mouse_y_in_workspace,
			top_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			top_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else if (FIXNUM_GT(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame)) {
		temp = FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
		d1 = FIXNUM_ABS(temp);
		temp = FIXNUM_MINUS(Mouse_y_in_workspace,
			bottom_edge_of_content_and_frame);
		d2 = FIXNUM_ABS(temp);
		distance_if_in_range_qm = FIXNUM_LE(d1,
			current_maximum_distance_to_allow_for_blocks) && 
			FIXNUM_LE(d2,
			current_maximum_distance_to_allow_for_blocks) ? 
			isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			FIXNUM_TIMES(d2,d2))) : Nil;
	    }
	    else
		distance_if_in_range_qm = 
			FIXNUM_MINUS(Mouse_x_in_workspace,
			right_edge_of_content_and_frame);
	}
	else if (FIXNUM_LT(Mouse_y_in_workspace,top_edge_of_content_and_frame))
	    distance_if_in_range_qm = 
		    FIXNUM_MINUS(top_edge_of_content_and_frame,
		    Mouse_y_in_workspace);
	else if (FIXNUM_GT(Mouse_y_in_workspace,
		bottom_edge_of_content_and_frame))
	    distance_if_in_range_qm = FIXNUM_MINUS(Mouse_y_in_workspace,
		    bottom_edge_of_content_and_frame);
	else
	    distance_if_in_range_qm = FIX((SI_Long)0L);
	distance_from_point_qm = (distance_if_in_range_qm ? 
		FIXNUM_LT(distance_if_in_range_qm,
		current_maximum_distance_to_allow_for_blocks) : 
		TRUEP(Nil)) ? distance_if_in_range_qm : Nil;
	if (subsubblock_qm && ( !TRUEP(distance_from_point_qm) || 
		FIXNUM_LE(distance,distance_from_point_qm)) && ( 
		!TRUEP(nearest_block_distance_qm) || FIXNUM_LE(distance,
		nearest_block_distance_qm))) {
	    nearest_block_qm = subsubblock_qm;
	    nearest_block_distance_qm = distance;
	    current_maximum_distance_to_allow_for_blocks = distance;
	}
	else if (distance_from_point_qm && ( 
		!TRUEP(nearest_block_distance_qm) || 
		FIXNUM_LE(distance_from_point_qm,nearest_block_distance_qm))) {
	    nearest_block_qm = subblock;
	    nearest_block_distance_qm = distance_from_point_qm;
	    current_maximum_distance_to_allow_for_blocks = 
		    distance_from_point_qm;
	}
    }
    if (block_being_searched_is_workspace_p) {
	result = find_vector_length_from_point_to_block_connections_if_within_limit(Mouse_x_in_workspace,
		Mouse_y_in_workspace,subblock,
		current_maximum_distance_to_allow_for_connections,
		Objects_to_not_consider_qm);
	MVS_2(result,connection_qm,distance_from_point_qm);
	temp_1 = TRUEP(connection_qm);
    }
    else
	temp_1 = TRUEP(Nil);
    if ((temp_1 ?  !TRUEP(Objects_to_not_consider_qm) ||  
	    !TRUEP(memq_function(connection_qm,
	    Objects_to_not_consider_qm)) : TRUEP(Nil)) ?  
	    !TRUEP(nearest_connection_distance_qm) || 
	    FIXNUM_LT(distance_from_point_qm,
	    nearest_connection_distance_qm) : TRUEP(Nil)) {
	nearest_connection_qm = connection_qm;
	nearest_connection_distance_qm = distance_from_point_qm;
	current_maximum_distance_to_allow_for_connections = 
		distance_from_point_qm;
    }
    goto next_loop;
  end_loop:
    if (nearest_block_qm && nearest_connection_qm) {
	connection = nearest_connection_qm;
	gensymed_symbol = ACCESS_ONCE(ISVREF(nearest_block_qm,(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)6L)) : Nil;
	connections = gensymed_symbol;
	if (connections) {
	    skip_list = CDR(connections);
	    key_value = connection;
	    key_hash_value = SXHASH_SYMBOL_1(connection) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)7L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_2 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_2,temp);
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
		goto end_3;
	    goto next_loop_4;
	  end_loop_5:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		    TRUEP(ISVREF(curr,(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	sub_class_bit_vector = ISVREF(ISVREF(nearest_block_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Loose_end_class_description,(SI_Long)18L));
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
	if (temp_1) {
	    temp = nearest_connection_qm;
	    temp_1 =  !(connection_connected_to_block_p(temp,
		    get_block_at_other_end_of_connection(nearest_connection_qm,
		    nearest_block_qm)) || 
		    connection_connected_to_block_p(nearest_connection_qm,
		    nearest_block_qm));
	}
	else
	    temp_1 = TRUEP(T);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	connection_frame_or_class = ISVREF(nearest_connection_qm,(SI_Long)1L);
	if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
		> (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    cross_section_pattern = ISVREF(connection_frame_or_class,
		    (SI_Long)20L);
	else {
	    if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		    Class_description_gkbprop)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = connection_frame_or_class;
		key_hash_value = 
			SXHASH_SYMBOL_1(connection_frame_or_class) & 
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
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
		    goto end_4;
		goto next_loop_7;
	      end_loop_8:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = connection_frame_or_class;
		    temp_2 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_4);
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
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
		    goto end_5;
		goto next_loop_10;
	      end_loop_11:
	      end_5:
		level = level - (SI_Long)1L;
		goto next_loop_9;
	      end_loop_9:;
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
		  next_loop_12:
		    if (level < ab_loop_bind_)
			goto end_loop_12;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_14;
		  end_loop_13:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_6;
		    goto next_loop_13;
		  end_loop_14:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_15:
		    if (level < ab_loop_bind_)
			goto end_loop_15;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_16:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_17:
		    if ( !TRUEP(marked))
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_17;
		  end_loop_16:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_7;
		    goto next_loop_16;
		  end_loop_17:
		  end_7:
		    level = level - (SI_Long)1L;
		    goto next_loop_15;
		  end_loop_15:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    else {
		skip_list = CDR(Symbol_properties_table);
		key_value = Qconnection;
		key_hash_value = SXHASH_SYMBOL_1(Qconnection) & 
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
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
		    goto end_8;
		goto next_loop_19;
	      end_loop_20:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_18;
	      end_loop_18:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = Qconnection;
		    temp_2 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_2,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_4);
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
	      next_loop_21:
		if (level < ab_loop_bind_)
		    goto end_loop_21;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_22:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
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
		    goto end_9;
		goto next_loop_22;
	      end_loop_23:
	      end_9:
		level = level - (SI_Long)1L;
		goto next_loop_21;
	      end_loop_21:;
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
		  next_loop_24:
		    if (level < ab_loop_bind_)
			goto end_loop_24;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_25:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_26:
		    if ( !TRUEP(marked))
			goto end_loop_25;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_26;
		  end_loop_25:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_10;
		    goto next_loop_25;
		  end_loop_26:
		  end_10:
		    level = level - (SI_Long)1L;
		    goto next_loop_24;
		  end_loop_24:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
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
		  next_loop_27:
		    if (level < ab_loop_bind_)
			goto end_loop_27;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_28:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		  next_loop_29:
		    if ( !TRUEP(marked))
			goto end_loop_28;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_2 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_2,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_29;
		  end_loop_28:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_11;
		    goto next_loop_28;
		  end_loop_29:
		  end_11:
		    level = level - (SI_Long)1L;
		    goto next_loop_27;
		  end_loop_27:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		temp = 
			get_slot_description_of_class_description_function(Qcross_section_pattern,
			gensymed_symbol,Nil);
	    }
	    cross_section_pattern = ISVREF(temp,(SI_Long)6L);
	}
	temp = CAAR(cross_section_pattern);
	cross_section_stripe = CONSP(temp) ? CDR(cross_section_pattern) : 
		cross_section_pattern;
	width = Nil;
	ab_loop_list_ = cross_section_stripe;
	ab_loopvar_ = FIX((SI_Long)0L);
	ab_loop_desetq_ = Nil;
      next_loop_30:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_30;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	width = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar_ = FIXNUM_ADD(width,ab_loopvar_);
	goto next_loop_30;
      end_loop_30:
	gensymed_symbol_1 = IFIX(ab_loopvar_);
	goto end_12;
	gensymed_symbol_1 = IFIX(Qnil);
      end_12:;
	gensymed_symbol_2 = (SI_Long)1L;
	expansion_factor = gensymed_symbol_1 >>  -  - gensymed_symbol_2;
	gross_distance_from_connection = 
		IFIX(nearest_connection_distance_qm) - expansion_factor;
	effective_distance_from_connection = 
		gross_distance_from_connection > (SI_Long)0L ? 
		gross_distance_from_connection : (SI_Long)0L;
	temp_1 = effective_distance_from_connection < 
		IFIX(nearest_block_distance_qm);
	if (temp_1);
	else if (effective_distance_from_connection == 
		IFIX(nearest_block_distance_qm)) {
	    temp = get_connection_layer_position(nearest_connection_qm);
	    temp_1 = FIXNUM_GT(temp,
		    get_block_layer_position(nearest_block_qm));
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_2(nearest_connection_qm,nearest_connection_distance_qm);
    else {
	temp_2 = nearest_block_qm;
	if (temp_2);
	else
	    temp_2 = nearest_connection_qm;
	temp = nearest_block_distance_qm;
	if (temp);
	else
	    temp = nearest_connection_distance_qm;
	return VALUES_2(temp_2,temp);
    }
    return VALUES_1(Qnil);
}

/* QUICK-CLIPPING-CHECK-OF-BLOCK-FOR-PICKING */
Object quick_clipping_check_of_block_for_picking(block)
    Object block;
{
    Object left_edge, top_edge, right_edge, bottom_edge;
    Object result;

    x_note_fn_call(129,27);
    result = edges_of_block_content_plus_frame(block);
    MVS_4(result,left_edge,top_edge,right_edge,bottom_edge);
    return VALUES_1( !(FIXNUM_GT(left_edge,
	    Loose_right_edge_of_visible_workspace_area) || 
	    FIXNUM_GT(top_edge,
	    Loose_bottom_edge_of_visible_workspace_area) || 
	    FIXNUM_LT(right_edge,
	    Loose_left_edge_of_visible_workspace_area) || 
	    FIXNUM_LT(bottom_edge,
	    Loose_top_edge_of_visible_workspace_area)) ? T : Nil);
}

/* FIND-OBJECT-NEAR-WORKSTATION-EVENT */
Object find_object_near_workstation_event varargs_1(int, n)
{
    Object workstation_event;
    Object objects_to_not_consider_qm, classes_of_objects_to_not_consider_qm;
    Object image_plane_qm, x_in_window, y_in_window, temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(129,28);
    INIT_ARGS_nonrelocating();
    workstation_event = REQUIRED_ARG_nonrelocating();
    objects_to_not_consider_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Objects_to_not_consider_qm,Qobjects_to_not_consider_qm,objects_to_not_consider_qm,
	    1);
      classes_of_objects_to_not_consider_qm = 
	      OPTIONAL_ARG_P_nonrelocating() ? 
	      OPTIONAL_ARG_nonrelocating() : Nil;
      PUSH_SPECIAL_WITH_SYMBOL(Classes_of_objects_to_not_consider_qm,Qclasses_of_objects_to_not_consider_qm,classes_of_objects_to_not_consider_qm,
	      0);
	END_ARGS_nonrelocating();
	image_plane_qm = ISVREF(workstation_event,(SI_Long)7L);
	if (image_plane_qm && ISVREF(image_plane_qm,(SI_Long)5L)) {
	    x_in_window = ISVREF(workstation_event,(SI_Long)3L);
	    y_in_window = ISVREF(workstation_event,(SI_Long)4L);
	    temp = find_object_near_mouse(ISVREF(workstation_event,
		    (SI_Long)3L),ISVREF(workstation_event,(SI_Long)4L),
		    image_plane_qm,Objects_to_not_consider_qm,
		    Classes_of_objects_to_not_consider_qm);
	    result = VALUES_4(temp,image_plane_qm,x_in_window,y_in_window);
	}
	else
	    result = VALUES_1(Nil);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Kwithout_text;       /* :without-text */

static Object Kjust_text;          /* :just-text */

static Object Ktight;              /* :tight */

/* TEXT-BOX-VISIBLE-NEAR-MOUSE-P */
Object text_box_visible_near_mouse_p(text_box)
    Object text_box;
{
    Object text_box_visibility_qm, sub_class_bit_vector, temp_1, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(129,29);
    text_box_visibility_qm = thing_selected_p(text_box,
	    Image_plane_for_finding_object_near_mouse) ? Kwithout_text : Nil;
    if (text_box_visibility_qm);
    else
	text_box_visibility_qm = text_box_visible_p(text_box,
		Image_x_scale_for_finding_object_near_mouse,
		Image_y_scale_for_finding_object_near_mouse);
    if (EQ(text_box_visibility_qm,Kjust_text)) {
	sub_class_bit_vector = ISVREF(ISVREF(text_box,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Name_box_class_description,
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
	temp_1 =  !temp ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else {
	    temp_2 = Mouse_x_in_workspace;
	    temp_1 = Mouse_y_in_workspace;
	    sub_class_bit_vector = ISVREF(ISVREF(text_box,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Name_box_class_description,(SI_Long)18L));
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
	    return find_position_in_text(11,text_box,Nil,Nil,Nil,Nil,
		    temp_2,temp_1,Nil,Nil,Nil,temp ? Ktight : T);
	}
    }
    else
	return VALUES_1(text_box_visibility_qm);
}

/* TABLE-VISIBLE-NEAR-MOUSE-P */
Object table_visible_near_mouse_p(table)
    Object table;
{
    Object temp;

    x_note_fn_call(129,30);
    temp = table_visible_in_image_plane_p(table,Nil,
	    Image_plane_for_finding_object_near_mouse);
    if (temp)
	return VALUES_1(temp);
    else
	return pick_cell_from_table(7,table,
		Image_plane_for_finding_object_near_mouse,
		X_in_window_for_finding_object_near_mouse,
		Y_in_window_for_finding_object_near_mouse,T,T,T);
}

Object Unselectable_classes_of_objects = UNBOUND;

/* FIND-BLOCK-NEAR-MOUSE-ON-WORKSPACE */
Object find_block_near_mouse_on_workspace(x_in_window,y_in_window,image_plane)
    Object x_in_window, y_in_window, image_plane;
{
    Object block_qm, valid_qm, thing_qm, x2, maybe_a_table;
    Object sub_class_bit_vector, gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Object result;

    x_note_fn_call(129,31);
    result = cached_block_near_mouse(x_in_window,y_in_window,image_plane);
    MVS_2(result,block_qm,valid_qm);
    if (valid_qm)
	return VALUES_1(block_qm);
    else {
	thing_qm = find_object_near_mouse(x_in_window,y_in_window,
		image_plane,Nil,Unselectable_classes_of_objects);
	if ( !TRUEP(thing_qm))
	    block_qm = Nil;
	else {
	    if (SIMPLE_VECTOR_P(thing_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(thing_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(thing_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(thing_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if ( !temp)
		block_qm = 
			get_or_make_connection_frame_and_activate_if_appropriate(thing_qm);
	    else {
		maybe_a_table = thing_qm;
	      next_loop:
		sub_class_bit_vector = ISVREF(ISVREF(maybe_a_table,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    block_qm = thing_qm;
		    goto end_1;
		}
		sub_class_bit_vector = ISVREF(ISVREF(maybe_a_table,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Table_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_1 = gensymed_symbol_1 << gensymed_symbol_2;
		    gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		    temp = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    block_qm = maybe_a_table;
		    goto end_1;
		}
		gensymed_symbol_3 = ACCESS_ONCE(ISVREF(maybe_a_table,
			(SI_Long)14L));
		gensymed_symbol_3 = gensymed_symbol_3 ? 
			ACCESS_ONCE(ISVREF(gensymed_symbol_3,(SI_Long)5L)) 
			: Nil;
		maybe_a_table = gensymed_symbol_3;
		goto next_loop;
	      end_loop:
		block_qm = Qnil;
	      end_1:;
	    }
	}
	cache_block_near_mouse(block_qm,x_in_window,y_in_window,image_plane);
	return VALUES_1(block_qm);
    }
}

Object The_type_description_of_block_near_mouse_cache = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_block_near_mouse_caches, Qchain_of_available_block_near_mouse_caches);

DEFINE_VARIABLE_WITH_SYMBOL(Block_near_mouse_cache_count, Qblock_near_mouse_cache_count);

Object Chain_of_available_block_near_mouse_caches_vector = UNBOUND;

/* BLOCK-NEAR-MOUSE-CACHE-STRUCTURE-MEMORY-USAGE */
Object block_near_mouse_cache_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(129,32);
    temp = Block_near_mouse_cache_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-BLOCK-NEAR-MOUSE-CACHE-COUNT */
Object outstanding_block_near_mouse_cache_count()
{
    Object def_structure_block_near_mouse_cache_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(129,33);
    gensymed_symbol = IFIX(Block_near_mouse_cache_count);
    def_structure_block_near_mouse_cache_variable = 
	    Chain_of_available_block_near_mouse_caches;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_block_near_mouse_cache_variable))
	goto end_loop;
    def_structure_block_near_mouse_cache_variable = 
	    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-BLOCK-NEAR-MOUSE-CACHE-1 */
Object reclaim_block_near_mouse_cache_1(block_near_mouse_cache)
    Object block_near_mouse_cache;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(129,34);
    inline_note_reclaim_cons(block_near_mouse_cache,Nil);
    structure_being_reclaimed = block_near_mouse_cache;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(block_near_mouse_cache,(SI_Long)12L));
      SVREF(block_near_mouse_cache,FIX((SI_Long)12L)) = Nil;
      reclaim_frame_serial_number(ISVREF(block_near_mouse_cache,(SI_Long)15L));
      SVREF(block_near_mouse_cache,FIX((SI_Long)15L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_block_near_mouse_caches_vector,
	    IFIX(Current_thread_index));
    SVREF(block_near_mouse_cache,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_block_near_mouse_caches_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = block_near_mouse_cache;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-BLOCK-NEAR-MOUSE-CACHE */
Object reclaim_structure_for_block_near_mouse_cache(block_near_mouse_cache)
    Object block_near_mouse_cache;
{
    x_note_fn_call(129,35);
    return reclaim_block_near_mouse_cache_1(block_near_mouse_cache);
}

static Object Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct;  /* g2-defstruct-structure-name::block-near-mouse-cache-g2-struct */

/* MAKE-PERMANENT-BLOCK-NEAR-MOUSE-CACHE-STRUCTURE-INTERNAL */
Object make_permanent_block_near_mouse_cache_structure_internal()
{
    Object def_structure_block_near_mouse_cache_variable;
    Object defstruct_g2_block_near_mouse_cache_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(129,36);
    def_structure_block_near_mouse_cache_variable = Nil;
    atomic_incff_symval(Qblock_near_mouse_cache_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_block_near_mouse_cache_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_block_near_mouse_cache_variable = the_array;
	SVREF(defstruct_g2_block_near_mouse_cache_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct;
	def_structure_block_near_mouse_cache_variable = 
		defstruct_g2_block_near_mouse_cache_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_block_near_mouse_cache_variable);
}

/* MAKE-BLOCK-NEAR-MOUSE-CACHE-INTERNAL-1 */
Object make_block_near_mouse_cache_internal_1()
{
    Object def_structure_block_near_mouse_cache_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(129,37);
    def_structure_block_near_mouse_cache_variable = 
	    ISVREF(Chain_of_available_block_near_mouse_caches_vector,
	    IFIX(Current_thread_index));
    if (def_structure_block_near_mouse_cache_variable) {
	temp = Chain_of_available_block_near_mouse_caches_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_block_near_mouse_cache_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_block_near_mouse_cache_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct;
    }
    else
	def_structure_block_near_mouse_cache_variable = 
		make_permanent_block_near_mouse_cache_structure_internal();
    inline_note_allocate_cons(def_structure_block_near_mouse_cache_variable,
	    Nil);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)1L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)2L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_block_near_mouse_cache_variable,FIX((SI_Long)3L)) 
	    = Nil;
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)4L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)8L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)9L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)10L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_block_near_mouse_cache_variable,FIX((SI_Long)11L)) 
	    = Nil;
    temp = frame_serial_number_0();
    SVREF(def_structure_block_near_mouse_cache_variable,FIX((SI_Long)12L)) 
	    = temp;
    ISVREF(def_structure_block_near_mouse_cache_variable,(SI_Long)13L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_block_near_mouse_cache_variable,FIX((SI_Long)14L)) 
	    = Nil;
    temp = frame_serial_number_0();
    SVREF(def_structure_block_near_mouse_cache_variable,FIX((SI_Long)15L)) 
	    = temp;
    return VALUES_1(def_structure_block_near_mouse_cache_variable);
}

/* CLEAR-CACHED-BLOCK-NEAR-MOUSE */
Object clear_cached_block_near_mouse(image_plane)
    Object image_plane;
{
    Object workstation, cache, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value;

    x_note_fn_call(129,38);
    workstation = ISVREF(ISVREF(ISVREF(image_plane,(SI_Long)2L),
	    (SI_Long)2L),(SI_Long)2L);
    cache = ISVREF(workstation,(SI_Long)42L);
    SVREF(cache,FIX((SI_Long)3L)) = Nil;
    SVREF(cache,FIX((SI_Long)11L)) = Nil;
    frame_serial_number_setf_arg = frame_serial_number_0();
    old = ISVREF(cache,(SI_Long)12L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(cache,FIX((SI_Long)12L)) = svref_new_value;
    SVREF(cache,FIX((SI_Long)14L)) = Nil;
    old = ISVREF(cache,(SI_Long)15L);
    new_1 = Nil;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    return VALUES_1(SVREF(cache,FIX((SI_Long)15L)) = svref_new_value);
}

/* CACHE-BLOCK-NEAR-MOUSE */
Object cache_block_near_mouse(block_qm,x_in_window,y_in_window,image_plane)
    Object block_qm, x_in_window, y_in_window, image_plane;
{
    Object workstation, cache, workspace_qm, svref_new_value;
    Object frame_serial_number_setf_arg, old, new_1;

    x_note_fn_call(129,39);
    workstation = ISVREF(ISVREF(ISVREF(image_plane,(SI_Long)2L),
	    (SI_Long)2L),(SI_Long)2L);
    cache = ISVREF(workstation,(SI_Long)42L);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm) {
	SVREF(cache,FIX((SI_Long)1L)) = x_in_window;
	SVREF(cache,FIX((SI_Long)2L)) = y_in_window;
	SVREF(cache,FIX((SI_Long)3L)) = image_plane;
	svref_new_value = ISVREF(image_plane,(SI_Long)1L);
	SVREF(cache,FIX((SI_Long)4L)) = svref_new_value;
	SVREF(cache,FIX((SI_Long)11L)) = workspace_qm;
	frame_serial_number_setf_arg = ISVREF(workspace_qm,(SI_Long)3L);
	old = ISVREF(cache,(SI_Long)12L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(cache,FIX((SI_Long)12L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)15L);
	SVREF(cache,FIX((SI_Long)5L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)16L);
	SVREF(cache,FIX((SI_Long)6L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)17L);
	SVREF(cache,FIX((SI_Long)7L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)18L);
	SVREF(cache,FIX((SI_Long)8L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)11L);
	SVREF(cache,FIX((SI_Long)9L)) = svref_new_value;
	svref_new_value = ISVREF(image_plane,(SI_Long)12L);
	SVREF(cache,FIX((SI_Long)10L)) = svref_new_value;
	svref_new_value = ISVREF(workspace_qm,(SI_Long)25L);
	SVREF(cache,FIX((SI_Long)13L)) = svref_new_value;
	SVREF(cache,FIX((SI_Long)14L)) = block_qm;
	frame_serial_number_setf_arg = block_qm ? ISVREF(block_qm,
		(SI_Long)3L) : Qnil;
	old = ISVREF(cache,(SI_Long)15L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	SVREF(cache,FIX((SI_Long)15L)) = svref_new_value;
	return VALUES_1(cache);
    }
    else
	return VALUES_1(Nil);
}

/* CACHED-BLOCK-NEAR-MOUSE */
Object cached_block_near_mouse(x_in_window,y_in_window,image_plane)
    Object x_in_window, y_in_window, image_plane;
{
    Object workstation, workspace_qm, cache_qm, image_plane_1;
    Object reference_serial_number, gensymed_symbol, x, y, xa, ya, temp_1;
    char temp;

    x_note_fn_call(129,40);
    workstation = ISVREF(ISVREF(ISVREF(image_plane,(SI_Long)2L),
	    (SI_Long)2L),(SI_Long)2L);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    cache_qm = ISVREF(workstation,(SI_Long)42L);
    if (workspace_qm && cache_qm) {
	if (FIXNUM_EQ(x_in_window,ISVREF(cache_qm,(SI_Long)1L)) && 
		FIXNUM_EQ(y_in_window,ISVREF(cache_qm,(SI_Long)2L)) && 
		EQ(image_plane,ISVREF(cache_qm,(SI_Long)3L))) {
	    image_plane_1 = ISVREF(cache_qm,(SI_Long)3L);
	    reference_serial_number = ISVREF(cache_qm,(SI_Long)4L);
	    temp = FIXNUM_EQ(ISVREF(image_plane_1,(SI_Long)1L),
		    reference_serial_number);
	}
	else
	    temp = TRUEP(Nil);
	if (temp ? EQ(workspace_qm,ISVREF(cache_qm,(SI_Long)11L)) : 
		    TRUEP(Nil)) {
	    gensymed_symbol = ISVREF(ISVREF(cache_qm,(SI_Long)11L),
		    (SI_Long)3L);
	    x = ISVREF(cache_qm,(SI_Long)11L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(cache_qm,(SI_Long)12L);
		if (FIXNUMP(y))
		    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp = FIXNUM_LT(xa,ya);
		    if (temp);
		    else
			temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (((((((temp ? FIXNUM_EQ(ISVREF(image_plane,(SI_Long)15L),
		ISVREF(cache_qm,(SI_Long)5L)) : TRUEP(Nil)) ? 
		FIXNUM_EQ(ISVREF(image_plane,(SI_Long)16L),ISVREF(cache_qm,
		(SI_Long)6L)) : TRUEP(Nil)) ? FIXNUM_EQ(ISVREF(image_plane,
		(SI_Long)17L),ISVREF(cache_qm,(SI_Long)7L)) : TRUEP(Nil)) ?
		 FIXNUM_EQ(ISVREF(image_plane,(SI_Long)18L),
		ISVREF(cache_qm,(SI_Long)8L)) : TRUEP(Nil)) ? 
		FIXNUM_EQ(ISVREF(image_plane,(SI_Long)11L),ISVREF(cache_qm,
		(SI_Long)9L)) : TRUEP(Nil)) ? FIXNUM_EQ(ISVREF(image_plane,
		(SI_Long)12L),ISVREF(cache_qm,(SI_Long)10L)) : TRUEP(Nil)) 
		? FIXNUM_EQ(ISVREF(workspace_qm,(SI_Long)25L),
		ISVREF(cache_qm,(SI_Long)13L)) : TRUEP(Nil)) {
	    temp =  !TRUEP(ISVREF(cache_qm,(SI_Long)14L));
	    if (temp);
	    else {
		gensymed_symbol = ISVREF(ISVREF(cache_qm,(SI_Long)14L),
			(SI_Long)3L);
		x = ISVREF(cache_qm,(SI_Long)14L);
		temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
			Qavailable_frame_vector) : TRUEP(Qnil);
		if (temp);
		else
		    temp = FIXNUMP(gensymed_symbol) ? 
			    IFIX(gensymed_symbol) == (SI_Long)-1L : TRUEP(Nil);
		if (temp);
		else {
		    x = gensymed_symbol;
		    y = ISVREF(cache_qm,(SI_Long)15L);
		    if (FIXNUMP(y))
			temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		    else if (FIXNUMP(x))
			temp = TRUEP(Nil);
		    else {
			xa = M_CAR(y);
			ya = M_CAR(x);
			temp = FIXNUM_LT(xa,ya);
			if (temp);
			else
			    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				    M_CDR(x)) : TRUEP(Qnil);
		    }
		}
		temp =  !temp;
	    }
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = ISVREF(cache_qm,(SI_Long)14L);
	    return VALUES_2(temp_1,T);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* GENERATE-SPOT-FOR-WORKSPACE */
Object generate_spot_for_workspace(workspace,mouse_pointer)
    Object workspace, mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, x_in_workspace;
    Object y_in_workspace, temp, key_code, unicode, block_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(129,41);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window && x_in_workspace && 
	    y_in_workspace) {
	temp = generate_spot_if_in_workspace_frame(workspace,mouse_pointer);
	if (temp)
	    return VALUES_1(temp);
	else {
	    key_code = ISVREF(mouse_pointer,(SI_Long)8L);
	    if (IFIX(FIXNUM_LOGAND(key_code,Unicode_bit)) != (SI_Long)0L) {
		unicode = FIXNUM_LOGAND(Unicode_character_bits,key_code);
		temp = num_len(3,FIX((SI_Long)0L),unicode,
			FIX((SI_Long)127L)) ? unicode : Illegal_key_index;
	    }
	    else
		temp = FIXNUM_LOGAND(Key_index_bits,key_code);
	    if (EQ(temp,FIX((SI_Long)770L)) || EQ(temp,FIX((SI_Long)772L)) 
		    || EQ(temp,FIX((SI_Long)774L)) || EQ(temp,
		    FIX((SI_Long)776L)))
		clear_cached_block_near_mouse(image_plane);
	    block_qm = find_block_near_mouse_on_workspace(x_in_window,
		    y_in_window,image_plane);
	    if ( !TRUEP(block_qm))
		return push_last_spot(mouse_pointer,
			make_workspace_background_spot_1(),Nil);
	    else {
		generate_spot_from_frame_if_approprate(block_qm,mouse_pointer);
		if (selection_handles_visible_p(block_qm,image_plane))
		    generate_spot_for_selection_handle(block_qm,mouse_pointer);
		if (ISVREF(ISVREF(mouse_pointer,(SI_Long)5L),(SI_Long)3L)) {
		    gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block_qm,
			    (SI_Long)1L),(SI_Long)11L),(SI_Long)0L),
			    (SI_Long)1L);
		    gensymed_symbol_1 = block_qm;
		    gensymed_symbol_2 = mouse_pointer;
		    return inline_funcall_2(gensymed_symbol,
			    gensymed_symbol_1,gensymed_symbol_2);
		}
		else
		    return VALUES_1(Nil);
	    }
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Kxor;                /* :xor */

static Object Qwhite;              /* white */

static Object Qblack;              /* black */

static Object Qtransparent;        /* transparent */

static Object Qbackground;         /* background */

static Object Qforeground;         /* foreground */

static Object Qworkspace_foreground;  /* workspace-foreground */

/* GENERATE-SPOT-IF-IN-WORKSPACE-FRAME */
Object generate_spot_if_in_workspace_frame(workspace,mouse_pointer)
    Object workspace, mouse_pointer;
{
    Object image_plane, x_in_window, y_in_window, x_in_workspace;
    Object y_in_workspace, left, top, right, bottom, scale;
    Object left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, current_window_1;
    Object drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor;
    SI_Long gensymed_symbol, value, gensymed_symbol_1, unshifted_result;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(29);
    Object result;

    x_note_fn_call(129,42);
    SAVE_STACK();
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    if (image_plane && x_in_window && y_in_window && x_in_workspace && 
	    y_in_workspace) {
	left = ISVREF(image_plane,(SI_Long)19L);
	top = ISVREF(image_plane,(SI_Long)20L);
	right = ISVREF(image_plane,(SI_Long)21L);
	bottom = ISVREF(image_plane,(SI_Long)22L);
	if ( !(FIXNUM_LE(left,x_in_window) && FIXNUM_LT(x_in_window,right) 
		&& FIXNUM_LE(top,y_in_window) && FIXNUM_LT(y_in_window,
		bottom))) {
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    value = IFIX(x_in_workspace) - (SI_Long)4L;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	    left_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    value = IFIX(y_in_workspace) - (SI_Long)4L;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	    top_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	    gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	    scale = Current_image_x_scale;
	    value = IFIX(x_in_workspace) + (SI_Long)4L;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	    right_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	    gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	    scale = Current_image_y_scale;
	    value = IFIX(y_in_workspace) + (SI_Long)4L;
	    if (IFIX(scale) == (SI_Long)4096L)
		gensymed_symbol_1 = value;
	    else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
		    scale) && FIXNUM_LT(scale,
		    Isqrt_of_most_positive_fixnum) && 
		    IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value 
		    && value < IFIX(Isqrt_of_most_positive_fixnum)) {
		unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
		gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	    }
	    else
		gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	    bottom_edge_of_draw_area = FIX(gensymed_symbol + 
		    gensymed_symbol_1);
	    PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		    28);
	      PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		      27);
		PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
			26);
		  PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
			  25);
		    LOCK(On_window_without_drawing);
		    if (PUSH_UNWIND_PROTECT(1)) {
			current_window_1 = ISVREF(ISVREF(image_plane,
				(SI_Long)2L),(SI_Long)2L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
				24);
			  drawing_on_window = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
				  23);
			    current_drawing_transfer_mode = 
				    EQ(Current_drawing_transfer_mode,Kxor) 
				    ? Current_drawing_transfer_mode : 
				    ISVREF(Current_window,(SI_Long)30L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
				    22);
			      type_of_current_window = 
				      ISVREF(Current_window,(SI_Long)1L);
			      PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
				      21);
				current_native_window_qm = 
					ISVREF(Current_window,(SI_Long)17L);
				PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
					20);
				  current_color_map = 
					  ISVREF(Current_window,(SI_Long)20L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
					  19);
				    temp = ISVREF(Current_color_map,
					    (SI_Long)5L);
				    if (temp);
				    else
					temp = map_to_color_value_1(Qwhite);
				    current_background_color_value = temp;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					    18);
				      temp = ISVREF(Current_color_map,
					      (SI_Long)4L);
				      if (temp);
				      else
					  temp = map_to_color_value_1(Qblack);
				      current_foreground_color_value = temp;
				      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					      17);
					current_frame_transform_qm = Nil;
					current_image_x_scale = 
						ISVREF(image_plane,
						(SI_Long)11L);
					current_image_y_scale = 
						ISVREF(image_plane,
						(SI_Long)12L);
					current_x_origin_of_drawing = 
						ISVREF(image_plane,
						(SI_Long)13L);
					current_y_origin_of_drawing = 
						ISVREF(image_plane,
						(SI_Long)14L);
					PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
						16);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
						  15);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
						    14);
					      PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
						      13);
						PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
							12);
						  LOCK(For_image_plane);
						  if (PUSH_UNWIND_PROTECT(0)) {
						      current_pane = 
							      ISVREF(image_plane,
							      (SI_Long)2L);
						      current_image_plane 
							      = image_plane;
						      loose_left_edge_of_visible_workspace_area 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)23L);
						      loose_top_edge_of_visible_workspace_area 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)24L);
						      loose_right_edge_of_visible_workspace_area 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)25L);
						      loose_bottom_edge_of_visible_workspace_area 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)26L);
						      color_or_metacolor = 
							      ISVREF(image_plane,
							      (SI_Long)5L) 
							      ? 
							      ISVREF(ISVREF(image_plane,
							      (SI_Long)5L),
							      (SI_Long)22L) 
							      : Nil;
						      if (color_or_metacolor);
						      else
							  color_or_metacolor 
								  = Qblack;
						      if (EQ(color_or_metacolor,
							      Qtransparent) 
							      || 
							      EQ(color_or_metacolor,
							      Qbackground)) {
							  background_color_or_metacolor 
								  = 
								  ISVREF(image_plane,
								  (SI_Long)5L) 
								  ? 
								  ISVREF(ISVREF(image_plane,
								  (SI_Long)5L),
								  (SI_Long)21L) 
								  : Nil;
							  if (background_color_or_metacolor);
							  else
							      background_color_or_metacolor 
								      = Qwhite;
							  if (EQ(background_color_or_metacolor,
								  Qforeground) 
								  || 
								  EQ(background_color_or_metacolor,
								  Qworkspace_foreground)) 
								      {
							      temp = 
								      ISVREF(Current_color_map,
								      (SI_Long)4L);
							      if (temp);
							      else
								  temp = 
									  map_to_color_value_1(Qblack);
							      current_foreground_color_value 
								      = temp;
							  }
							  else if (EQ(background_color_or_metacolor,
								  Qtransparent) 
								  || 
								  EQ(background_color_or_metacolor,
								  Qbackground)) 
								      {
							      temp = 
								      ISVREF(Current_color_map,
								      (SI_Long)5L);
							      if (temp);
							      else
								  temp = 
									  map_to_color_value_1(Qwhite);
							      current_foreground_color_value 
								      = temp;
							  }
							  else
							      current_foreground_color_value 
								      = 
								      EQ(background_color_or_metacolor,
								      ISVREF(Current_color_map,
								      (SI_Long)6L)) 
								      ? 
								      ISVREF(Current_color_map,
								      (SI_Long)7L) 
								      : 
								      map_to_color_value_1(background_color_or_metacolor);
						      }
						      else if (EQ(color_or_metacolor,
							      Qforeground) 
							      || 
							      EQ(color_or_metacolor,
							      Qworkspace_foreground)) 
								  {
							  temp = 
								  ISVREF(Current_color_map,
								  (SI_Long)4L);
							  if (temp);
							  else
							      temp = 
								      map_to_color_value_1(Qblack);
							  current_foreground_color_value 
								  = temp;
						      }
						      else
							  current_foreground_color_value 
								  = 
								  EQ(color_or_metacolor,
								  ISVREF(Current_color_map,
								  (SI_Long)6L)) 
								  ? 
								  ISVREF(Current_color_map,
								  (SI_Long)7L) 
								  : 
								  map_to_color_value_1(color_or_metacolor);
						      PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
							      11);
							PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
								10);
							  PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
								  9);
							    PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
								    8);
							      PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
								      7);
								PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
									6);
								  PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
									  5);
								    color_or_metacolor 
									    = 
									    ISVREF(image_plane,
									    (SI_Long)5L) 
									    ?
									     
									    ISVREF(ISVREF(image_plane,
									    (SI_Long)5L),
									    (SI_Long)21L) 
									    :
									     
									    Nil;
								    if (color_or_metacolor);
								    else
									color_or_metacolor 
										= 
										Qwhite;
								    if (EQ(color_or_metacolor,
									    Qtransparent) 
									    || 
									    EQ(color_or_metacolor,
									    Qbackground)) 
										{
									temp 
										= 
										ISVREF(Current_color_map,
										(SI_Long)5L);
									if (temp);
									else
									    temp 
										    = 
										    map_to_color_value_1(Qwhite);
									current_background_color_value 
										= 
										temp;
								    }
								    else if (EQ(color_or_metacolor,
									    Qforeground) 
									    || 
									    EQ(color_or_metacolor,
									    Qworkspace_foreground)) 
										{
									temp 
										= 
										ISVREF(image_plane,
										(SI_Long)5L) 
										?
										 
										ISVREF(ISVREF(image_plane,
										(SI_Long)5L),
										(SI_Long)22L) 
										:
										 
										Nil;
									if (temp);
									else
									    temp 
										    = 
										    Qblack;
									color_or_metacolor 
										= 
										temp;
									if (EQ(color_or_metacolor,
										Qtransparent) 
										|| 
										EQ(color_or_metacolor,
										Qbackground)) 
										    {
									    background_color_or_metacolor 
										    = 
										    ISVREF(image_plane,
										    (SI_Long)5L) 
										    ?
										     
										    ISVREF(ISVREF(image_plane,
										    (SI_Long)5L),
										    (SI_Long)21L) 
										    :
										     
										    Nil;
									    if (background_color_or_metacolor);
									    else
										background_color_or_metacolor 
											= 
											Qwhite;
									    if (EQ(background_color_or_metacolor,
										    Qforeground) 
										    || 
										    EQ(background_color_or_metacolor,
										    Qworkspace_foreground)) 
											{
										temp 
											= 
											ISVREF(Current_color_map,
											(SI_Long)4L);
										if (temp);
										else
										    temp 
											    = 
											    map_to_color_value_1(Qblack);
										current_background_color_value 
											= 
											temp;
									    }
									    else if (EQ(background_color_or_metacolor,
										    Qtransparent) 
										    || 
										    EQ(background_color_or_metacolor,
										    Qbackground)) 
											{
										temp 
											= 
											ISVREF(Current_color_map,
											(SI_Long)5L);
										if (temp);
										else
										    temp 
											    = 
											    map_to_color_value_1(Qwhite);
										current_background_color_value 
											= 
											temp;
									    }
									    else
										current_background_color_value 
											= 
											EQ(background_color_or_metacolor,
											ISVREF(Current_color_map,
											(SI_Long)6L)) 
											?
											 
											ISVREF(Current_color_map,
											(SI_Long)7L) 
											:
											 
											map_to_color_value_1(background_color_or_metacolor);
									}
									else if (EQ(color_or_metacolor,
										Qforeground) 
										|| 
										EQ(color_or_metacolor,
										Qworkspace_foreground)) 
										    {
									    temp 
										    = 
										    ISVREF(Current_color_map,
										    (SI_Long)4L);
									    if (temp);
									    else
										temp 
											= 
											map_to_color_value_1(Qblack);
									    current_background_color_value 
										    = 
										    temp;
									}
									else
									    current_background_color_value 
										    = 
										    EQ(color_or_metacolor,
										    ISVREF(Current_color_map,
										    (SI_Long)6L)) 
										    ?
										     
										    ISVREF(Current_color_map,
										    (SI_Long)7L) 
										    :
										     
										    map_to_color_value_1(color_or_metacolor);
								    }
								    else
									current_background_color_value 
										= 
										EQ(color_or_metacolor,
										ISVREF(Current_color_map,
										(SI_Long)6L)) 
										?
										 
										ISVREF(Current_color_map,
										(SI_Long)7L) 
										:
										 
										map_to_color_value_1(color_or_metacolor);
								    PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
									    4);
								      current_image_x_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_image_y_scale 
									      = 
									      FIX((SI_Long)4096L);
								      current_x_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      current_y_origin_of_drawing 
									      = 
									      FIX((SI_Long)0L);
								      PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
									      3);
									PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
										2);
									  PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
										  1);
									    PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
										    0);
									      track_mouse_over_frame(mouse_pointer,
										      ISVREF(ISVREF(image_plane,
										      (SI_Long)10L),
										      (SI_Long)2L),
										      workspace,
										      ISVREF(image_plane,
										      (SI_Long)15L),
										      ISVREF(image_plane,
										      (SI_Long)16L),
										      ISVREF(image_plane,
										      (SI_Long)17L),
										      ISVREF(image_plane,
										      (SI_Long)18L));
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
						  UNLOCK(For_image_plane);
						  CONTINUE_UNWINDING(0);
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
		    POP_UNWIND_PROTECT(1);
		    UNLOCK(On_window_without_drawing);
		    CONTINUE_UNWINDING(1);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    RESTORE_STACK();
	    return VALUES_1(T);
	}
	else {
	    RESTORE_STACK();
	    return VALUES_1(Nil);
	}
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

static Object Qframe_transforms_of_block;  /* frame-transforms-of-block */

/* GENERATE-SPOT-FROM-FRAME-IF-APPROPRATE */
Object generate_spot_from_frame_if_approprate(block,mouse_pointer)
    Object block, mouse_pointer;
{
    Object image_plane, x_in_workspace, y_in_workspace, x_in_window;
    Object y_in_window, scale, left_edge_of_draw_area, top_edge_of_draw_area;
    Object right_edge_of_draw_area, bottom_edge_of_draw_area, current_window_1;
    Object drawing_on_window, current_drawing_transfer_mode;
    Object type_of_current_window, current_native_window_qm, current_color_map;
    Object temp, current_background_color_value;
    Object current_foreground_color_value, current_frame_transform_qm;
    Object current_image_x_scale, current_image_y_scale;
    Object current_x_origin_of_drawing, current_y_origin_of_drawing;
    Object current_pane, current_image_plane;
    Object loose_left_edge_of_visible_workspace_area;
    Object loose_top_edge_of_visible_workspace_area;
    Object loose_right_edge_of_visible_workspace_area;
    Object loose_bottom_edge_of_visible_workspace_area, color_or_metacolor;
    Object background_color_or_metacolor, frame_transforms_of_block;
    Object frame_description_reference, gensymed_symbol_2, left_edge_of_block;
    Object top_edge_of_block, right_edge_of_block, bottom_edge_of_block;
    Object left_edge_of_frame, top_edge_of_frame, right_edge_of_frame;
    Object bottom_edge_of_frame;
    SI_Long gensymed_symbol, value, gensymed_symbol_1, unshifted_result, left;
    SI_Long top, right, bottom;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(29);
    Object result;

    x_note_fn_call(129,43);
    SAVE_STACK();
    image_plane = image_plane_blackboard_function(mouse_pointer);
    x_in_workspace = x_in_workspace_blackboard_function(mouse_pointer);
    y_in_workspace = y_in_workspace_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (image_plane && x_in_workspace && y_in_workspace && x_in_window && 
	    y_in_window) {
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = IFIX(x_in_workspace) - (SI_Long)4L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	left_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = IFIX(y_in_workspace) - (SI_Long)4L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	top_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_x_origin_of_drawing);
	scale = Current_image_x_scale;
	value = IFIX(x_in_workspace) + (SI_Long)4L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	right_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	gensymed_symbol = IFIX(Current_y_origin_of_drawing);
	scale = Current_image_y_scale;
	value = IFIX(y_in_workspace) + (SI_Long)4L;
	if (IFIX(scale) == (SI_Long)4096L)
	    gensymed_symbol_1 = value;
	else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,scale) 
		&& FIXNUM_LT(scale,Isqrt_of_most_positive_fixnum) && 
		IFIX(Minus_of_isqrt_of_most_positive_fixnum) < value && 
		value < IFIX(Isqrt_of_most_positive_fixnum)) {
	    unshifted_result = IFIX(scale) * value + (SI_Long)2048L;
	    gensymed_symbol_1 = unshifted_result >>  -  - (SI_Long)12L;
	}
	else
	    gensymed_symbol_1 = IFIX(scalef_function(scale,FIX(value)));
	bottom_edge_of_draw_area = FIX(gensymed_symbol + gensymed_symbol_1);
	PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_draw_area,Qbottom_edge_of_draw_area,bottom_edge_of_draw_area,
		28);
	  PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_draw_area,Qright_edge_of_draw_area,right_edge_of_draw_area,
		  27);
	    PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_draw_area,Qtop_edge_of_draw_area,top_edge_of_draw_area,
		    26);
	      PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_draw_area,Qleft_edge_of_draw_area,left_edge_of_draw_area,
		      25);
		LOCK(On_window_without_drawing);
		if (PUSH_UNWIND_PROTECT(1)) {
		    current_window_1 = ISVREF(ISVREF(image_plane,
			    (SI_Long)2L),(SI_Long)2L);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_window,Qcurrent_window,current_window_1,
			    24);
		      drawing_on_window = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Drawing_on_window,Qdrawing_on_window,drawing_on_window,
			      23);
			current_drawing_transfer_mode = 
				EQ(Current_drawing_transfer_mode,Kxor) ? 
				Current_drawing_transfer_mode : 
				ISVREF(Current_window,(SI_Long)30L);
			PUSH_SPECIAL_WITH_SYMBOL(Current_drawing_transfer_mode,Qcurrent_drawing_transfer_mode,current_drawing_transfer_mode,
				22);
			  type_of_current_window = ISVREF(Current_window,
				  (SI_Long)1L);
			  PUSH_SPECIAL_WITH_SYMBOL(Type_of_current_window,Qtype_of_current_window,type_of_current_window,
				  21);
			    current_native_window_qm = 
				    ISVREF(Current_window,(SI_Long)17L);
			    PUSH_SPECIAL_WITH_SYMBOL(Current_native_window_qm,Qcurrent_native_window_qm,current_native_window_qm,
				    20);
			      current_color_map = ISVREF(Current_window,
				      (SI_Long)20L);
			      PUSH_SPECIAL_WITH_SYMBOL(Current_color_map,Qcurrent_color_map,current_color_map,
				      19);
				temp = ISVREF(Current_color_map,(SI_Long)5L);
				if (temp);
				else
				    temp = map_to_color_value_1(Qwhite);
				current_background_color_value = temp;
				PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
					18);
				  temp = ISVREF(Current_color_map,(SI_Long)4L);
				  if (temp);
				  else
				      temp = map_to_color_value_1(Qblack);
				  current_foreground_color_value = temp;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
					  17);
				    current_frame_transform_qm = Nil;
				    current_image_x_scale = 
					    ISVREF(image_plane,(SI_Long)11L);
				    current_image_y_scale = 
					    ISVREF(image_plane,(SI_Long)12L);
				    current_x_origin_of_drawing = 
					    ISVREF(image_plane,(SI_Long)13L);
				    current_y_origin_of_drawing = 
					    ISVREF(image_plane,(SI_Long)14L);
				    PUSH_SPECIAL_WITH_SYMBOL(Current_y_origin_of_drawing,Qcurrent_y_origin_of_drawing,current_y_origin_of_drawing,
					    16);
				      PUSH_SPECIAL_WITH_SYMBOL(Current_x_origin_of_drawing,Qcurrent_x_origin_of_drawing,current_x_origin_of_drawing,
					      15);
					PUSH_SPECIAL_WITH_SYMBOL(Current_image_y_scale,Qcurrent_image_y_scale,current_image_y_scale,
						14);
					  PUSH_SPECIAL_WITH_SYMBOL(Current_image_x_scale,Qcurrent_image_x_scale,current_image_x_scale,
						  13);
					    PUSH_SPECIAL_WITH_SYMBOL(Current_frame_transform_qm,Qcurrent_frame_transform_qm,current_frame_transform_qm,
						    12);
					      LOCK(For_image_plane);
					      if (PUSH_UNWIND_PROTECT(0)) {
						  current_pane = 
							  ISVREF(image_plane,
							  (SI_Long)2L);
						  current_image_plane = 
							  image_plane;
						  loose_left_edge_of_visible_workspace_area 
							  = 
							  ISVREF(image_plane,
							  (SI_Long)23L);
						  loose_top_edge_of_visible_workspace_area 
							  = 
							  ISVREF(image_plane,
							  (SI_Long)24L);
						  loose_right_edge_of_visible_workspace_area 
							  = 
							  ISVREF(image_plane,
							  (SI_Long)25L);
						  loose_bottom_edge_of_visible_workspace_area 
							  = 
							  ISVREF(image_plane,
							  (SI_Long)26L);
						  color_or_metacolor = 
							  ISVREF(image_plane,
							  (SI_Long)5L) ? 
							  ISVREF(ISVREF(image_plane,
							  (SI_Long)5L),
							  (SI_Long)22L) : Nil;
						  if (color_or_metacolor);
						  else
						      color_or_metacolor = 
							      Qblack;
						  if (EQ(color_or_metacolor,
							  Qtransparent) || 
							  EQ(color_or_metacolor,
							  Qbackground)) {
						      background_color_or_metacolor 
							      = 
							      ISVREF(image_plane,
							      (SI_Long)5L) 
							      ? 
							      ISVREF(ISVREF(image_plane,
							      (SI_Long)5L),
							      (SI_Long)21L) 
							      : Nil;
						      if (background_color_or_metacolor);
						      else
							  background_color_or_metacolor 
								  = Qwhite;
						      if (EQ(background_color_or_metacolor,
							      Qforeground) 
							      || 
							      EQ(background_color_or_metacolor,
							      Qworkspace_foreground)) 
								  {
							  temp = 
								  ISVREF(Current_color_map,
								  (SI_Long)4L);
							  if (temp);
							  else
							      temp = 
								      map_to_color_value_1(Qblack);
							  current_foreground_color_value 
								  = temp;
						      }
						      else if (EQ(background_color_or_metacolor,
							      Qtransparent) 
							      || 
							      EQ(background_color_or_metacolor,
							      Qbackground)) {
							  temp = 
								  ISVREF(Current_color_map,
								  (SI_Long)5L);
							  if (temp);
							  else
							      temp = 
								      map_to_color_value_1(Qwhite);
							  current_foreground_color_value 
								  = temp;
						      }
						      else
							  current_foreground_color_value 
								  = 
								  EQ(background_color_or_metacolor,
								  ISVREF(Current_color_map,
								  (SI_Long)6L)) 
								  ? 
								  ISVREF(Current_color_map,
								  (SI_Long)7L) 
								  : 
								  map_to_color_value_1(background_color_or_metacolor);
						  }
						  else if (EQ(color_or_metacolor,
							  Qforeground) || 
							  EQ(color_or_metacolor,
							  Qworkspace_foreground)) 
							      {
						      temp = 
							      ISVREF(Current_color_map,
							      (SI_Long)4L);
						      if (temp);
						      else
							  temp = 
								  map_to_color_value_1(Qblack);
						      current_foreground_color_value 
							      = temp;
						  }
						  else
						      current_foreground_color_value 
							      = 
							      EQ(color_or_metacolor,
							      ISVREF(Current_color_map,
							      (SI_Long)6L)) 
							      ? 
							      ISVREF(Current_color_map,
							      (SI_Long)7L) 
							      : 
							      map_to_color_value_1(color_or_metacolor);
						  PUSH_SPECIAL_WITH_SYMBOL(Current_foreground_color_value,Qcurrent_foreground_color_value,current_foreground_color_value,
							  11);
						    PUSH_SPECIAL_WITH_SYMBOL(Loose_bottom_edge_of_visible_workspace_area,Qloose_bottom_edge_of_visible_workspace_area,loose_bottom_edge_of_visible_workspace_area,
							    10);
						      PUSH_SPECIAL_WITH_SYMBOL(Loose_right_edge_of_visible_workspace_area,Qloose_right_edge_of_visible_workspace_area,loose_right_edge_of_visible_workspace_area,
							      9);
							PUSH_SPECIAL_WITH_SYMBOL(Loose_top_edge_of_visible_workspace_area,Qloose_top_edge_of_visible_workspace_area,loose_top_edge_of_visible_workspace_area,
								8);
							  PUSH_SPECIAL_WITH_SYMBOL(Loose_left_edge_of_visible_workspace_area,Qloose_left_edge_of_visible_workspace_area,loose_left_edge_of_visible_workspace_area,
								  7);
							    PUSH_SPECIAL_WITH_SYMBOL(Current_image_plane,Qcurrent_image_plane,current_image_plane,
								    6);
							      PUSH_SPECIAL_WITH_SYMBOL(Current_pane,Qcurrent_pane,current_pane,
								      5);
								color_or_metacolor 
									= 
									ISVREF(image_plane,
									(SI_Long)5L) 
									? 
									ISVREF(ISVREF(image_plane,
									(SI_Long)5L),
									(SI_Long)21L) 
									: Nil;
								if (color_or_metacolor);
								else
								    color_or_metacolor 
									    = 
									    Qwhite;
								if (EQ(color_or_metacolor,
									Qtransparent) 
									|| 
									EQ(color_or_metacolor,
									Qbackground)) 
									    {
								    temp = 
									    ISVREF(Current_color_map,
									    (SI_Long)5L);
								    if (temp);
								    else
									temp 
										= 
										map_to_color_value_1(Qwhite);
								    current_background_color_value 
									    = 
									    temp;
								}
								else if (EQ(color_or_metacolor,
									Qforeground) 
									|| 
									EQ(color_or_metacolor,
									Qworkspace_foreground)) 
									    {
								    temp = 
									    ISVREF(image_plane,
									    (SI_Long)5L) 
									    ?
									     
									    ISVREF(ISVREF(image_plane,
									    (SI_Long)5L),
									    (SI_Long)22L) 
									    :
									     
									    Nil;
								    if (temp);
								    else
									temp 
										= 
										Qblack;
								    color_or_metacolor 
									    = 
									    temp;
								    if (EQ(color_or_metacolor,
									    Qtransparent) 
									    || 
									    EQ(color_or_metacolor,
									    Qbackground)) 
										{
									background_color_or_metacolor 
										= 
										ISVREF(image_plane,
										(SI_Long)5L) 
										?
										 
										ISVREF(ISVREF(image_plane,
										(SI_Long)5L),
										(SI_Long)21L) 
										:
										 
										Nil;
									if (background_color_or_metacolor);
									else
									    background_color_or_metacolor 
										    = 
										    Qwhite;
									if (EQ(background_color_or_metacolor,
										Qforeground) 
										|| 
										EQ(background_color_or_metacolor,
										Qworkspace_foreground)) 
										    {
									    temp 
										    = 
										    ISVREF(Current_color_map,
										    (SI_Long)4L);
									    if (temp);
									    else
										temp 
											= 
											map_to_color_value_1(Qblack);
									    current_background_color_value 
										    = 
										    temp;
									}
									else if (EQ(background_color_or_metacolor,
										Qtransparent) 
										|| 
										EQ(background_color_or_metacolor,
										Qbackground)) 
										    {
									    temp 
										    = 
										    ISVREF(Current_color_map,
										    (SI_Long)5L);
									    if (temp);
									    else
										temp 
											= 
											map_to_color_value_1(Qwhite);
									    current_background_color_value 
										    = 
										    temp;
									}
									else
									    current_background_color_value 
										    = 
										    EQ(background_color_or_metacolor,
										    ISVREF(Current_color_map,
										    (SI_Long)6L)) 
										    ?
										     
										    ISVREF(Current_color_map,
										    (SI_Long)7L) 
										    :
										     
										    map_to_color_value_1(background_color_or_metacolor);
								    }
								    else if (EQ(color_or_metacolor,
									    Qforeground) 
									    || 
									    EQ(color_or_metacolor,
									    Qworkspace_foreground)) 
										{
									temp 
										= 
										ISVREF(Current_color_map,
										(SI_Long)4L);
									if (temp);
									else
									    temp 
										    = 
										    map_to_color_value_1(Qblack);
									current_background_color_value 
										= 
										temp;
								    }
								    else
									current_background_color_value 
										= 
										EQ(color_or_metacolor,
										ISVREF(Current_color_map,
										(SI_Long)6L)) 
										?
										 
										ISVREF(Current_color_map,
										(SI_Long)7L) 
										:
										 
										map_to_color_value_1(color_or_metacolor);
								}
								else
								    current_background_color_value 
									    = 
									    EQ(color_or_metacolor,
									    ISVREF(Current_color_map,
									    (SI_Long)6L)) 
									    ?
									     
									    ISVREF(Current_color_map,
									    (SI_Long)7L) 
									    :
									     
									    map_to_color_value_1(color_or_metacolor);
								PUSH_SPECIAL_WITH_SYMBOL(Current_background_color_value,Qcurrent_background_color_value,current_background_color_value,
									4);
								  frame_transforms_of_block 
									  = 
									  get_lookup_slot_value_given_default(block,
									  Qframe_transforms_of_block,
									  Nil);
								  if (frame_transforms_of_block);
								  else {
								      SAVE_VALUES(VALUES_1(Nil));
								      goto end_1;
								  }
								  temp = 
									  FIRST(frame_transforms_of_block);
								  frame_description_reference 
									  = 
									  ISVREF(CDR(temp),
									  (SI_Long)5L);
								  if (frame_description_reference);
								  else {
								      SAVE_VALUES(VALUES_1(Nil));
								      goto end_1;
								  }
								  gensymed_symbol_2 
									  = 
									  ISVREF(block,
									  (SI_Long)14L);
								  gensymed_symbol_2 
									  = 
									  gensymed_symbol_2 
									  ?
									   
									  ISVREF(gensymed_symbol_2,
									  (SI_Long)0L) 
									  :
									   
									  FIX((SI_Long)0L);
								  left_edge_of_block 
									  = 
									  gensymed_symbol_2;
								  gensymed_symbol_2 
									  = 
									  ISVREF(block,
									  (SI_Long)14L);
								  gensymed_symbol_2 
									  = 
									  gensymed_symbol_2 
									  ?
									   
									  ISVREF(gensymed_symbol_2,
									  (SI_Long)1L) 
									  :
									   
									  FIX((SI_Long)0L);
								  top_edge_of_block 
									  = 
									  gensymed_symbol_2;
								  gensymed_symbol_2 
									  = 
									  ISVREF(block,
									  (SI_Long)14L);
								  gensymed_symbol_2 
									  = 
									  gensymed_symbol_2 
									  ?
									   
									  ISVREF(gensymed_symbol_2,
									  (SI_Long)2L) 
									  :
									   
									  FIX((SI_Long)0L);
								  right_edge_of_block 
									  = 
									  gensymed_symbol_2;
								  gensymed_symbol_2 
									  = 
									  ISVREF(block,
									  (SI_Long)14L);
								  gensymed_symbol_2 
									  = 
									  gensymed_symbol_2 
									  ?
									   
									  ISVREF(gensymed_symbol_2,
									  (SI_Long)3L) 
									  :
									   
									  FIX((SI_Long)0L);
								  bottom_edge_of_block 
									  = 
									  gensymed_symbol_2;
								  gensymed_symbol 
									  = 
									  IFIX(Current_x_origin_of_drawing);
								  if (IFIX(Current_image_x_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(left_edge_of_block);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_x_scale) 
									  && 
									  FIXNUM_LT(Current_image_x_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  left_edge_of_block) 
									  && 
									  FIXNUM_LT(left_edge_of_block,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_x_scale,
									      left_edge_of_block)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_x_scale,
									      left_edge_of_block));
								  left = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol 
									  = 
									  IFIX(Current_y_origin_of_drawing);
								  if (IFIX(Current_image_y_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(top_edge_of_block);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_y_scale) 
									  && 
									  FIXNUM_LT(Current_image_y_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  top_edge_of_block) 
									  && 
									  FIXNUM_LT(top_edge_of_block,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_y_scale,
									      top_edge_of_block)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_y_scale,
									      top_edge_of_block));
								  top = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol 
									  = 
									  IFIX(Current_x_origin_of_drawing);
								  if (IFIX(Current_image_x_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(right_edge_of_block);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_x_scale) 
									  && 
									  FIXNUM_LT(Current_image_x_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  right_edge_of_block) 
									  && 
									  FIXNUM_LT(right_edge_of_block,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_x_scale,
									      right_edge_of_block)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_x_scale,
									      right_edge_of_block));
								  right = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  gensymed_symbol 
									  = 
									  IFIX(Current_y_origin_of_drawing);
								  if (IFIX(Current_image_y_scale) 
									  == 
									  (SI_Long)4096L)
								      gensymed_symbol_1 
									      = 
									      IFIX(bottom_edge_of_block);
								  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  Current_image_y_scale) 
									  && 
									  FIXNUM_LT(Current_image_y_scale,
									  Isqrt_of_most_positive_fixnum) 
									  && 
									  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
									  bottom_edge_of_block) 
									  && 
									  FIXNUM_LT(bottom_edge_of_block,
									  Isqrt_of_most_positive_fixnum)) 
									      {
								      unshifted_result 
									      = 
									      IFIX(FIXNUM_TIMES(Current_image_y_scale,
									      bottom_edge_of_block)) 
									      + 
									      (SI_Long)2048L;
								      gensymed_symbol_1 
									      = 
									      unshifted_result 
									      >> 
									       
									      - 
									       
									      - 
									      (SI_Long)12L;
								  }
								  else
								      gensymed_symbol_1 
									      = 
									      IFIX(scalef_function(Current_image_y_scale,
									      bottom_edge_of_block));
								  bottom = 
									  gensymed_symbol 
									  + 
									  gensymed_symbol_1;
								  if (left 
									  <= 
									  IFIX(x_in_window) 
									  && 
									  IFIX(x_in_window) 
									  < 
									  right 
									  && 
									  top 
									  <= 
									  IFIX(y_in_window) 
									  && 
									  IFIX(y_in_window) 
									  < 
									  bottom) 
									      {
								      SAVE_VALUES(VALUES_1(Nil));
								      goto end_1;
								  }
								  left_edge_of_frame 
									  = 
									  FIXNUM_MINUS(left_edge_of_block,
									  ISVREF(frame_description_reference,
									  (SI_Long)4L));
								  top_edge_of_frame 
									  = 
									  FIXNUM_MINUS(top_edge_of_block,
									  ISVREF(frame_description_reference,
									  (SI_Long)5L));
								  right_edge_of_frame 
									  = 
									  FIXNUM_ADD(right_edge_of_block,
									  ISVREF(frame_description_reference,
									  (SI_Long)6L));
								  bottom_edge_of_frame 
									  = 
									  FIXNUM_ADD(bottom_edge_of_block,
									  ISVREF(frame_description_reference,
									  (SI_Long)7L));
								  PUSH_SPECIAL_WITH_SYMBOL(Bottom_edge_of_frame,Qbottom_edge_of_frame,bottom_edge_of_frame,
									  3);
								    PUSH_SPECIAL_WITH_SYMBOL(Right_edge_of_frame,Qright_edge_of_frame,right_edge_of_frame,
									    2);
								      PUSH_SPECIAL_WITH_SYMBOL(Top_edge_of_frame,Qtop_edge_of_frame,top_edge_of_frame,
									      1);
									PUSH_SPECIAL_WITH_SYMBOL(Left_edge_of_frame,Qleft_edge_of_frame,left_edge_of_frame,
										0);
									  gensymed_symbol 
										  = 
										  IFIX(Current_x_origin_of_drawing);
									  if (IFIX(Current_image_x_scale) 
										  == 
										  (SI_Long)4096L)
									      gensymed_symbol_1 
										      = 
										      IFIX(Left_edge_of_frame);
									  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Current_image_x_scale) 
										  && 
										  FIXNUM_LT(Current_image_x_scale,
										  Isqrt_of_most_positive_fixnum) 
										  && 
										  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Left_edge_of_frame) 
										  && 
										  FIXNUM_LT(Left_edge_of_frame,
										  Isqrt_of_most_positive_fixnum)) 
										      {
									      unshifted_result 
										      = 
										      IFIX(FIXNUM_TIMES(Current_image_x_scale,
										      Left_edge_of_frame)) 
										      + 
										      (SI_Long)2048L;
									      gensymed_symbol_1 
										      = 
										      unshifted_result 
										      >> 
										       
										      - 
										       
										      - 
										      (SI_Long)12L;
									  }
									  else
									      gensymed_symbol_1 
										      = 
										      IFIX(scalef_function(Current_image_x_scale,
										      Left_edge_of_frame));
									  left 
										  = 
										  gensymed_symbol 
										  + 
										  gensymed_symbol_1;
									  gensymed_symbol 
										  = 
										  IFIX(Current_y_origin_of_drawing);
									  if (IFIX(Current_image_y_scale) 
										  == 
										  (SI_Long)4096L)
									      gensymed_symbol_1 
										      = 
										      IFIX(Top_edge_of_frame);
									  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Current_image_y_scale) 
										  && 
										  FIXNUM_LT(Current_image_y_scale,
										  Isqrt_of_most_positive_fixnum) 
										  && 
										  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Top_edge_of_frame) 
										  && 
										  FIXNUM_LT(Top_edge_of_frame,
										  Isqrt_of_most_positive_fixnum)) 
										      {
									      unshifted_result 
										      = 
										      IFIX(FIXNUM_TIMES(Current_image_y_scale,
										      Top_edge_of_frame)) 
										      + 
										      (SI_Long)2048L;
									      gensymed_symbol_1 
										      = 
										      unshifted_result 
										      >> 
										       
										      - 
										       
										      - 
										      (SI_Long)12L;
									  }
									  else
									      gensymed_symbol_1 
										      = 
										      IFIX(scalef_function(Current_image_y_scale,
										      Top_edge_of_frame));
									  top 
										  = 
										  gensymed_symbol 
										  + 
										  gensymed_symbol_1;
									  gensymed_symbol 
										  = 
										  IFIX(Current_x_origin_of_drawing);
									  if (IFIX(Current_image_x_scale) 
										  == 
										  (SI_Long)4096L)
									      gensymed_symbol_1 
										      = 
										      IFIX(Right_edge_of_frame);
									  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Current_image_x_scale) 
										  && 
										  FIXNUM_LT(Current_image_x_scale,
										  Isqrt_of_most_positive_fixnum) 
										  && 
										  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Right_edge_of_frame) 
										  && 
										  FIXNUM_LT(Right_edge_of_frame,
										  Isqrt_of_most_positive_fixnum)) 
										      {
									      unshifted_result 
										      = 
										      IFIX(FIXNUM_TIMES(Current_image_x_scale,
										      Right_edge_of_frame)) 
										      + 
										      (SI_Long)2048L;
									      gensymed_symbol_1 
										      = 
										      unshifted_result 
										      >> 
										       
										      - 
										       
										      - 
										      (SI_Long)12L;
									  }
									  else
									      gensymed_symbol_1 
										      = 
										      IFIX(scalef_function(Current_image_x_scale,
										      Right_edge_of_frame));
									  right 
										  = 
										  gensymed_symbol 
										  + 
										  gensymed_symbol_1;
									  gensymed_symbol 
										  = 
										  IFIX(Current_y_origin_of_drawing);
									  if (IFIX(Current_image_y_scale) 
										  == 
										  (SI_Long)4096L)
									      gensymed_symbol_1 
										      = 
										      IFIX(Bottom_edge_of_frame);
									  else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Current_image_y_scale) 
										  && 
										  FIXNUM_LT(Current_image_y_scale,
										  Isqrt_of_most_positive_fixnum) 
										  && 
										  FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
										  Bottom_edge_of_frame) 
										  && 
										  FIXNUM_LT(Bottom_edge_of_frame,
										  Isqrt_of_most_positive_fixnum)) 
										      {
									      unshifted_result 
										      = 
										      IFIX(FIXNUM_TIMES(Current_image_y_scale,
										      Bottom_edge_of_frame)) 
										      + 
										      (SI_Long)2048L;
									      gensymed_symbol_1 
										      = 
										      unshifted_result 
										      >> 
										       
										      - 
										       
										      - 
										      (SI_Long)12L;
									  }
									  else
									      gensymed_symbol_1 
										      = 
										      IFIX(scalef_function(Current_image_y_scale,
										      Bottom_edge_of_frame));
									  bottom 
										  = 
										  gensymed_symbol 
										  + 
										  gensymed_symbol_1;
									  if ( 
										  !(left 
										  <= 
										  IFIX(x_in_window) 
										  && 
										  IFIX(x_in_window) 
										  < 
										  right 
										  && 
										  top 
										  <= 
										  IFIX(y_in_window) 
										  && 
										  IFIX(y_in_window) 
										  < 
										  bottom)) 
										      {
									      SAVE_VALUES(VALUES_1(Nil));
									      POP_SPECIAL();
									      POP_SPECIAL();
									      POP_SPECIAL();
									      POP_SPECIAL();
									      goto end_1;
									  }
									  SAVE_VALUES(track_mouse_over_frame(mouse_pointer,
										  ISVREF(frame_description_reference,
										  (SI_Long)2L),
										  block,
										  Left_edge_of_frame,
										  Top_edge_of_frame,
										  Right_edge_of_frame,
										  Bottom_edge_of_frame));
									POP_SPECIAL();
								      POP_SPECIAL();
								    POP_SPECIAL();
								  POP_SPECIAL();
								end_1:;
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
					      UNLOCK(For_image_plane);
					      CONTINUE_UNWINDING(0);
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
		POP_UNWIND_PROTECT(1);
		UNLOCK(On_window_without_drawing);
		CONTINUE_UNWINDING(1);
		result = RESTORE_VALUES();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	RESTORE_STACK();
	return result;
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

Object All_optional_modules_for_display = UNBOUND;

static Object Qent;                /* ent */

static Object Qal;                 /* al */

static Object Qjp;                 /* jp */

static Object Qjl;                 /* jl */

static Object Qg1;                 /* g1 */

static Object Qkorean;             /* korean */

static Object Qnupec;              /* nupec */

static Object Qjapanese;           /* japanese */

static Object Qchinese;            /* chinese */

static Object Qgfi;                /* gfi */

static Object Qicp;                /* icp */

static Object Qgsi;                /* gsi */

/* LIST-LOADED-USER-VISIBLE-MODULES */
Object list_loaded_user_visible_modules()
{
    Object module_entry, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, code, temp;
    SI_Long gensymed_symbol;
    char temp_1;

    x_note_fn_call(129,44);
    module_entry = Nil;
    ab_loop_list_ = All_optional_modules_for_display;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(module_entry,Qent)) {
	code = M_CAR(M_CDR(Radio_button_status_flags_1));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)65536L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_ent_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qal)) {
	code = M_CAR(M_CDR(Radio_button_status_flags));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)32768L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_al_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qjp)) {
	code = M_CAR(M_CDR(Popup_frames_available));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)16384L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_jp_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qjl)) {
	code = M_CAR(M_CDR(Index_of_open_windows));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)8192L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_jl_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qg1)) {
	code = M_CAR(M_CDR(Edit_type_alias_mapping));
	temp = FIXNUMP(code) ? ((IFIX(code) & (SI_Long)4096L) != 
		(SI_Long)0L ? T : Nil) : Qnil;
	if (temp);
	else
	    temp = M_CAR(M_CDR(Cache_g1_semantics_graph));
    }
    else if (EQ(module_entry,Qkorean)) {
	code = M_CAR(M_CDR(Get_object_on_kb_workspace_for_item));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)2048L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_korean_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qnupec)) {
	code = M_CAR(M_CDR(Journal_shutout_scan_p));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)256L) != 
		(SI_Long)0L ? M_CAR(M_CDR(Cache_nupec_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qjapanese)) {
	code = M_CAR(M_CDR(Pop_fonts_stack));
	if (FIXNUMP(code)) {
	    gensymed_symbol = IFIX(code) & (SI_Long)128L;
	    temp_1 = gensymed_symbol != (SI_Long)0L;
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? M_CAR(M_CDR(Cache_japanese_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qchinese)) {
	code = M_CAR(M_CDR(Reclaim_fonts_stack));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)32L) != (SI_Long)0L 
		? M_CAR(M_CDR(Cache_chinese_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qgfi)) {
	code = M_CAR(M_CDR(Gfi_list_of_converters));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)8L) != (SI_Long)0L ?
		 M_CAR(M_CDR(Cache_gfi_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qicp)) {
	code = M_CAR(M_CDR(Listed_continuation_servers));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)4L) != (SI_Long)0L ?
		 M_CAR(M_CDR(Cache_icp_semantics_graph)) : Nil;
    }
    else if (EQ(module_entry,Qgsi)) {
	code = M_CAR(M_CDR(Overflow_byte_count));
	temp = FIXNUMP(code) && (IFIX(code) & (SI_Long)1L) != (SI_Long)0L ?
		 M_CAR(M_CDR(Cache_gsi_semantics_graph)) : Nil;
    }
    else
	temp = Qnil;
    if (temp ?  !TRUEP(invisible_optional_module_p(module_entry)) : 
		TRUEP(Nil)) {
	ab_loopvar__2 = gensym_cons_1(module_entry,Nil);
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

DEFINE_VARIABLE_WITH_SYMBOL(Gensym_logo_style, Qgensym_logo_style);

static Object array_constant_3;    /* # */

static Object Qnew_large_with_tagline;  /* new-large-with-tagline */

static Object array_constant_4;    /* # */

static Object Qnew_small;          /* new-small */

static Object array_constant_5;    /* # */

static Object Qnew_large;          /* new-large */

static Object array_constant_6;    /* # */

static Object Qnew_large_2;        /* new-large-2 */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object Qold;                /* old */

/* GET-GENSYM-LOGO-STYLE */
Object get_gensym_logo_style()
{
    Object style;

    x_note_fn_call(129,45);
    style = get_gensym_environment_variable(array_constant_3);
    if ( !TRUEP(style))
	Gensym_logo_style = Qnew_large_with_tagline;
    else if (string_equalw(style,array_constant_4))
	Gensym_logo_style = Qnew_small;
    else if (string_equalw(style,array_constant_5))
	Gensym_logo_style = Qnew_large;
    else if (string_equalw(style,array_constant_6))
	Gensym_logo_style = Qnew_large_2;
    else if (string_equalw(style,array_constant_7))
	Gensym_logo_style = Qnew_large_with_tagline;
    else if (string_equalw(style,array_constant_8))
	Gensym_logo_style = Qold;
    else
	Gensym_logo_style = Qnew_large_with_tagline;
    return VALUES_1(Gensym_logo_style);
}

static Object string_constant_4;   /* "G2" */

static Object string_constant_5;   /* "Gensym  G2" */

/* MAKE-TEXT-FOR-GENSYM-G2 */
Object make_text_for_gensym_g2()
{
    x_note_fn_call(129,46);
    return slot_value_cons_1(copy_text_string(EQ(Gensym_logo_style,
	    Qnew_large) || EQ(Gensym_logo_style,Qnew_large_2) || 
	    EQ(Gensym_logo_style,Qnew_large_with_tagline) ? 
	    string_constant_4 : string_constant_5),Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_6;   /* "Multi-threading " */

static Object string_constant_7;   /* "G2~c with " */

static Object list_constant_3;     /* # */

/* MAKE-TEXT-FOR-PRODUCT-AND-OPTIONS */
Object make_text_for_product_and_options()
{
    Object user_visible_optional_modules_loaded, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, schar_arg_2, schar_new_value, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, thing;
    Declare_special(5);

    x_note_fn_call(129,47);
    user_visible_optional_modules_loaded = list_loaded_user_visible_modules();
    if (user_visible_optional_modules_loaded) {
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
		  tformat(1,string_constant_6);
		  tformat(2,string_constant_7,FIX((SI_Long)174L));
		  write_symbol_list(5,user_visible_optional_modules_loaded,
			  Nil,Qand,Nil,list_constant_3);
		  if (EQ(Current_twriting_output_type,Qwide_string)) {
		      thing = (SI_Long)8232L;
		      twrite_wide_character(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		  }
		  else {
		      if ( 
			      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			      Total_length_of_current_gensym_string))
			  extend_current_gensym_string(0);
		      temp = Current_gensym_string;
		      schar_arg_2 = Fill_pointer_for_current_gensym_string;
		      thing = (SI_Long)8232L;
		      schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
			      CHAR_CODE(FIX(thing)) : FIX(thing));
		      SET_SCHAR(temp,schar_arg_2,schar_new_value);
		      temp = 
			      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		      Fill_pointer_for_current_gensym_string = temp;
		  }
		  reclaim_gensym_list_1(user_visible_optional_modules_loaded);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return slot_value_cons_1(temp_1,Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsystem_version;     /* system-version */

static Object array_constant_9;    /* # */

static Object string_constant_8;   /* "~d." */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

static Object array_constant_14;   /* # */

/* MAKE-TEXT-FOR-TYPE-OF-G2-LICENSE */
Object make_text_for_type_of_g2_license()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object code, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(129,48);
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
	      twrite_system_version_in_g2_title(1,get(Current_system_name,
		      Qsystem_version,_));
	      if (Build_comment_string) {
		  twrite_beginning_of_wide_string(array_constant_9,
			  FIX((SI_Long)2L));
		  tformat(2,string_constant_8,External_version);
		  if (IFIX(Revision_number_of_current_gensym_product_line) 
			  < (SI_Long)10L)
		      twrite_beginning_of_wide_string(array_constant_10,
			      FIX((SI_Long)1L));
		  tformat(2,string_constant_8,
			  Revision_number_of_current_gensym_product_line);
		  twrite_general_string(Build_comment_string);
		  twrite_beginning_of_wide_string(array_constant_11,
			  FIX((SI_Long)1L));
	      }
	      code = M_CAR(M_CDR(Redo_saved_changes));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	      if (temp);
	      else
		  temp = TRUEP(SECOND(Old_eval_cons_list));
	      if (temp)
		  twrite_beginning_of_wide_string(array_constant_12,
			  FIX((SI_Long)10L));
	      code = M_CAR(M_CDR(Sparse_known_pathnames_list));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
	      if (temp)
		  twrite_beginning_of_wide_string(array_constant_13,
			  FIX((SI_Long)17L));
	      code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
	      if (temp)
		  twrite_beginning_of_wide_string(array_constant_14,
			  FIX((SI_Long)11L));
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return slot_value_list_2(temp_1,stringw(FIX((SI_Long)8232L)));
}

/* MAKE-TEXT-FOR-LOCAL-IDENTIFICATION */
Object make_text_for_local_identification()
{
    x_note_fn_call(129,49);
    return slot_value_cons_1(write_local_identification_info_text_string(),
	    Nil);
}

Object Interrim_no_mark_logo_p = UNBOUND;

static Object string_constant_9;   /* " Gensym  G2" */

static Object Qprogram_title_format;  /* program-title-format */

static Object Qgensym_logo;        /* gensym-logo */

static Object Qnew_gensym_logo;    /* new-gensym-logo */

static Object Qlarge_new_gensym_logo;  /* large-new-gensym-logo */

static Object Qlarge_new_gensym_logo_with_tagline;  /* large-new-gensym-logo-with-tagline */

static Object Qnew_large_logo_program_title_format;  /* new-large-logo-program-title-format */

static Object Qnew_small_logo_program_title_format;  /* new-small-logo-program-title-format */

static Object Qnew_small_logo_new_copyright_format;  /* new-small-logo-new-copyright-format */

static Object Qnew_copyright_format;  /* new-copyright-format */

static Object Qnew_large_logo_new_copyright_format;  /* new-large-logo-new-copyright-format */

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object Qfine_print_format;  /* fine-print-format */

static Object Qcredits_table_format;  /* credits-table-format */

static Object Kcredits_workspace_frame_style;  /* :credits-workspace-frame-style */

static Object Knew_credits_workspace_frame_style;  /* :new-credits-workspace-frame-style */

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

/* DISPLAY-CREDITS */
Object display_credits varargs_1(int, n)
{
    Object a_particular_workstation_only_qm, gensym_logo_style, workstation;
    Object ab_loop_list_, gensym_window, temp, temp_1, logo, g2, temp_2;
    Object temp_3, temp_4, workspace;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(129,50);
    INIT_ARGS_nonrelocating();
    a_particular_workstation_only_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensym_logo_style = Interrim_no_mark_logo_p ? Qold : Gensym_logo_style;
    PUSH_SPECIAL_WITH_SYMBOL(Gensym_logo_style,Qgensym_logo_style,gensym_logo_style,
	    0);
      workstation = Nil;
      ab_loop_list_ = Workstations_in_service;
      gensym_window = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      workstation = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      gensym_window = ISVREF(workstation,(SI_Long)1L);
      if ( !TRUEP(a_particular_workstation_only_qm) || EQ(workstation,
	      a_particular_workstation_only_qm)) {
	  if (Interrim_no_mark_logo_p)
	      temp = slot_value_cons_1(slot_value_list_2(Nil,
		      make_text_cell(2,
		      slot_value_cons_1(copy_text_string(string_constant_9),
		      Nil),Qprogram_title_format)),Nil);
	  else {
	      if (EQ(Gensym_logo_style,Qold))
		  temp_1 = Qgensym_logo;
	      else if (EQ(Gensym_logo_style,Qnew_small))
		  temp_1 = Qnew_gensym_logo;
	      else if (EQ(Gensym_logo_style,Qnew_large) || 
		      EQ(Gensym_logo_style,Qnew_large_2))
		  temp_1 = Qlarge_new_gensym_logo;
	      else if (EQ(Gensym_logo_style,Qnew_large_with_tagline))
		  temp_1 = Qlarge_new_gensym_logo_with_tagline;
	      else
		  temp_1 = Qnil;
	      logo = make_icon_cell(temp_1,FIX((SI_Long)20L),
		      FIX((SI_Long)20L),FIX((SI_Long)20L),FIX((SI_Long)10L));
	      temp_1 = make_text_for_gensym_g2();
	      if (EQ(Gensym_logo_style,Qnew_large) || EQ(Gensym_logo_style,
		      Qnew_large_2) || EQ(Gensym_logo_style,
		      Qnew_large_with_tagline))
		  temp = Qnew_large_logo_program_title_format;
	      else if (EQ(Gensym_logo_style,Qnew_small))
		  temp = Qnew_small_logo_program_title_format;
	      else if (EQ(Gensym_logo_style,Qold))
		  temp = Qprogram_title_format;
	      else
		  temp = Qnil;
	      g2 = make_text_cell(2,temp_1,temp);
	      temp = EQ(Gensym_logo_style,Qnew_large_2) ? 
		      slot_value_list_2(slot_value_list_2(Nil,logo),
		      slot_value_list_2(Nil,g2)) : 
		      slot_value_cons_1(slot_value_list_2(logo,g2),Nil);
	  }
	  if (EQ(Gensym_logo_style,Qnew_large) || EQ(Gensym_logo_style,
		  Qnew_large_2) || EQ(Gensym_logo_style,
		  Qnew_large_with_tagline))
	      temp_2 = Nil;
	  else if (EQ(Gensym_logo_style,Qnew_small))
	      temp_2 = make_text_cell(2,make_empty_text(),
		      Qnew_small_logo_new_copyright_format);
	  else if (EQ(Gensym_logo_style,Qold))
	      temp_2 = make_text_cell(2,make_empty_text(),
		      Qnew_copyright_format);
	  else
	      temp_2 = Qnil;
	  temp_3 = make_text_for_product_and_options();
	  temp_4 = make_text_for_type_of_g2_license();
	  temp_1 = make_text_for_local_identification();
	  temp_1 = nconc2(temp_3,nconc2(temp_4,nconc2(temp_1,
		  copy_for_slot_value(Copyright_boilerplate_lines_of_text_1))));
	  if (EQ(Gensym_logo_style,Qnew_large) || EQ(Gensym_logo_style,
		  Qnew_large_2) || EQ(Gensym_logo_style,
		  Qnew_large_with_tagline))
	      temp_4 = Qnew_large_logo_new_copyright_format;
	  else if (EQ(Gensym_logo_style,Qnew_small))
	      temp_4 = Qnew_small_logo_new_copyright_format;
	  else
	      temp_4 = Qnew_copyright_format;
	  temp_1 = slot_value_list_2(temp_2,make_text_cell(2,temp_1,temp_4));
	  workspace = make_workspace(4,Qtemporary_workspace,Nil,
		  make_or_reformat_table(3,nconc2(temp,
		  slot_value_list_2(temp_1,slot_value_list_2(Nil,
		  make_text_cell(2,
		  copy_for_slot_value(Copyright_boilerplate_lines_of_text_2),
		  Qfine_print_format)))),Qcredits_table_format,Nil),
		  FIX((SI_Long)0L));
	  set_frame_style_of_block(workspace,EQ(Gensym_logo_style,Qold) ? 
		  Kcredits_workspace_frame_style : 
		  Knew_credits_workspace_frame_style);
	  put_workspace_on_pane_function(workspace,
		  detail_pane(gensym_window),Qright,Qbottom,Nil,
		  FIX((SI_Long)50L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
      }
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    return force_process_drawing();
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* TITLE-BLOCK-TABLE-P */
Object title_block_table_p(table)
    Object table;
{
    x_note_fn_call(129,51);
    return VALUES_1(EQ(get_lookup_slot_value_given_default(ISVREF(table,
	    (SI_Long)16L),Qname_or_names_for_frame,Nil),
	    Qcredits_table_format) ? T : Nil);
}

/* IMAGE-PLANE-HAS-TITLE-BLOCK-P */
Object image_plane_has_title_block_p(image_plane)
    Object image_plane;
{
    Object workspace_qm;

    x_note_fn_call(129,52);
    workspace_qm = ISVREF(image_plane,(SI_Long)5L);
    if (workspace_qm)
	return title_block_workspace_p(workspace_qm);
    else
	return VALUES_1(Nil);
}

/* TITLE-BLOCK-WORKSPACE-P */
Object title_block_workspace_p(workspace)
    Object workspace;
{
    Object sub_class_bit_vector, sole_subblock_on_temporary_workspace_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(129,53);
    sub_class_bit_vector = ISVREF(ISVREF(workspace,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Temporary_workspace_class_description,(SI_Long)18L));
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
    sole_subblock_on_temporary_workspace_qm = (temp ? 
	    TRUEP(has_only_one_subblock_p(workspace)) : TRUEP(Nil)) ? 
	    first_subblock(workspace) : Nil;
    if (sole_subblock_on_temporary_workspace_qm) {
	sub_class_bit_vector = 
		ISVREF(ISVREF(sole_subblock_on_temporary_workspace_qm,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return title_block_table_p(sole_subblock_on_temporary_workspace_qm);
    else
	return VALUES_1(Nil);
}

/* DELETE-ALL-TITLE-BLOCK-WORKSPACES */
Object delete_all_title_block_workspaces()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, workspace;
    char temp;
    Declare_special(1);

    x_note_fn_call(129,54);
  next_loop:
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    workspace = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qtemporary_workspace);
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop;
	  goto next_loop_2;
	end_loop:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_1;
      workspace = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (title_block_workspace_p(workspace)) {
	  delete_frame(workspace);
	  temp = TRUEP(T);
	  goto end_1;
      }
      goto next_loop_1;
    end_loop_1:
      temp = TRUEP(Qnil);
    end_1:;
    POP_SPECIAL();
    if ( !temp)
	goto end_loop_2;
    goto next_loop;
  end_loop_2:
    return VALUES_1(Qnil);
}

/* SPOT-GENERATOR-FOR-CREDITS-TABLE-FORMAT */
Object spot_generator_for_credits_table_format(table,mouse_pointer)
    Object table, mouse_pointer;
{
    x_note_fn_call(129,55);
    generate_output_only_table_spot(table,mouse_pointer,
	    make_credits_table_spot_1());
    return VALUES_1(Nil);
}

/* DRAW-FOR-ICON-CELL */
Object draw_for_icon_cell(icon_cell)
    Object icon_cell;
{
    x_note_fn_call(129,56);
    return VALUES_1(icon_cell);
}

/* COMPUTE-MINIMUM-RIGHT-EDGE-FOR-ICON-CELL */
Object compute_minimum_right_edge_for_icon_cell(icon_cell)
    Object icon_cell;
{
    Object gensymed_symbol;

    x_note_fn_call(129,57);
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    return VALUES_1(gensymed_symbol);
}

/* COMPUTE-MINIMUM-BOTTOM-EDGE-FOR-ICON-CELL */
Object compute_minimum_bottom_edge_for_icon_cell(icon_cell)
    Object icon_cell;
{
    Object gensymed_symbol;

    x_note_fn_call(129,58);
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    return VALUES_1(gensymed_symbol);
}

/* RESIZE-FOR-ICON-CELL */
Object resize_for_icon_cell(icon_cell,available_width,available_height,
	    other_data)
    Object icon_cell, available_width, available_height, other_data;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, subblock;
    Object temp, temp_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4;

    x_note_fn_call(129,59);
    gensymed_symbol = ACCESS_ONCE(ISVREF(icon_cell,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    temp = subblock;
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(available_width);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)1L;
    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(available_height);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_3 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
    gensymed_symbol_3 = (SI_Long)1L;
    gensymed_symbol_2 = gensymed_symbol_2 >>  -  - gensymed_symbol_3;
    gensymed_symbol_1 = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    shift_block(temp,temp_1,FIX(gensymed_symbol_1 - gensymed_symbol_2));
    goto next_loop;
  end_loop:;
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(available_width);
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(icon_cell,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(available_height);
    return change_edges_of_block(icon_cell,Nil,Nil,temp,
	    FIX(gensymed_symbol_1 + gensymed_symbol_2));
}

/* MAKE-ICON-CELL */
Object make_icon_cell(entity_class,left_margin,top_margin,right_margin,
	    bottom_margin)
    Object entity_class, left_margin, top_margin, right_margin, bottom_margin;
{
    x_note_fn_call(129,60);
    return make_icon_cell_for_entity(make_entity(1,entity_class),
	    left_margin,top_margin,right_margin,bottom_margin);
}

static Object Qicon_cell;          /* icon-cell */

/* MAKE-ICON-CELL-FOR-ENTITY */
Object make_icon_cell_for_entity(entity,left_margin,top_margin,
	    right_margin,bottom_margin)
    Object entity, left_margin, top_margin, right_margin, bottom_margin;
{
    Object icon_cell, gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(129,61);
    icon_cell = make_frame(Qicon_cell);
    shift_block(entity,left_margin,top_margin);
    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(right_margin);
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(entity,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(bottom_margin);
    change_edges_of_block(icon_cell,Nil,Nil,temp,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2));
    add_subblock(entity,icon_cell);
    return VALUES_1(icon_cell);
}

/* SPOT-GENERATOR-FOR-HELP-TABLE-FORMAT */
Object spot_generator_for_help_table_format(table,mouse_pointer)
    Object table, mouse_pointer;
{
    x_note_fn_call(129,62);
    generate_output_only_table_spot(table,mouse_pointer,
	    make_output_only_table_spot_1());
    return VALUES_1(Nil);
}

static Object Kfirst;              /* :first */

/* UI-COMMAND-NAME-FOR-DESCRIBE-KEYMAP */
Object ui_command_name_for_describe_keymap(name)
    Object name;
{
    Object cmd_qm;

    x_note_fn_call(129,63);
    cmd_qm = find_ui_command(1,name);
    if (cmd_qm)
	return remove_character_from_wide_string(FIX((SI_Long)38L),
		translated_string_for_symbol(3,ISVREF(cmd_qm,(SI_Long)2L),
		Kfirst,T));
    else
	return VALUES_1(name);
}

static Object Qmenu;               /* menu */

static Object Qmenu_item;          /* menu-item */

static Object string_constant_10;  /* "~a ~a" */

static Object array_constant_15;   /* # */

static Object Qhelp_key_name_format;  /* help-key-name-format */

static Object Qhelp_key_binding_format;  /* help-key-binding-format */

static Object Qhelp_title_format;  /* help-title-format */

/* DESCRIBE-KEYMAP-INTO-TABLE-ROWS */
Object describe_keymap_into_table_rows(name,bindings)
    Object name, bindings;
{
    Object row, rows, key_patterns_and_classes, previous_handler, temp;
    Object current_localization_purpose_qm, sublist, bucket, key_pattern;
    Object handlers, class_1, handler, options, ab_loop_list_, ab_loop_desetq_;
    Object c, ab_loop_list__1, handler_string, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object new_handler, key_string, key_cell, pretty, handler_cell, element;
    SI_Long row_length, bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(7);
    Object result;

    x_note_fn_call(129,64);
    SAVE_STACK();
    row = Nil;
    rows = Nil;
    key_patterns_and_classes = Nil;
    previous_handler = Nil;
    row_length = (SI_Long)4L;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,6);
      if (bindings) {
	  LOCK(Localization_context);
	  if (PUSH_UNWIND_PROTECT(1)) {
	      push_item_to_end_of_current_localization_domains(Qmenu);
	      LOCK(Localization_context);
	      if (PUSH_UNWIND_PROTECT(0)) {
		  temp = Current_localization_purpose_qm;
		  if (temp);
		  else
		      temp = Qmenu_item;
		  current_localization_purpose_qm = temp;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
			  5);
		    sublist = bindings;
		    bucket = Nil;
		    key_pattern = Nil;
		    handlers = Nil;
		  next_loop:
		    if ( !TRUEP(sublist))
			goto end_loop;
		    bucket = CAR(sublist);
		    key_pattern = FIRST(bucket);
		    handlers = CDR(bucket);
		    class_1 = Nil;
		    handler = Nil;
		    options = Nil;
		    ab_loop_list_ = handlers;
		    ab_loop_desetq_ = Nil;
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    ab_loop_desetq_ = M_CAR(ab_loop_list_);
		    class_1 = CAR(ab_loop_desetq_);
		    temp = CDR(ab_loop_desetq_);
		    handler = CAR(temp);
		    temp = CDR(ab_loop_desetq_);
		    options = CDR(temp);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (CONSP(handler) || find_ui_command(1,handler)) {
			temp_1 = EQ(class_1,T);
			if (temp_1);
			else
			    temp_1 = SYMBOLP(class_1) ? 
				    TRUEP(lookup_global_or_kb_specific_property_value(class_1,
				    Class_description_gkbprop)) : TRUEP(Qnil);
			if (temp_1);
			else if (CONSP(class_1)) {
			    c = Nil;
			    ab_loop_list__1 = class_1;
			  next_loop_2:
			    if ( !TRUEP(ab_loop_list__1))
				goto end_loop_2;
			    c = M_CAR(ab_loop_list__1);
			    ab_loop_list__1 = M_CDR(ab_loop_list__1);
			    if ( 
				    !TRUEP(lookup_global_or_kb_specific_property_value(c,
				    Class_description_gkbprop))) {
				temp_1 = TRUEP(Nil);
				goto end_1;
			    }
			    goto next_loop_2;
			  end_loop_2:
			    temp_1 = TRUEP(T);
			    goto end_1;
			    temp_1 = TRUEP(Qnil);
			  end_1:;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			handler_string = CONSP(handler) ? 
				translated_string_for_symbol(1,
				SECOND(handler)) : Nil;
			if (handler_string) {
			    current_wide_string_list = Qdo_not_use;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
				    4);
			      wide_string_bv16 = 
				      allocate_byte_vector_16(FIX((SI_Long)2048L 
				      + (SI_Long)3L));
			      bv16_length = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
			      aref_arg_2 = bv16_length - (SI_Long)2L;
			      aref_new_value = (SI_Long)2048L & 
				      (SI_Long)65535L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      aref_arg_2 = bv16_length - (SI_Long)1L;
			      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      aref_arg_2,aref_new_value);
			      UBYTE_16_ISASET_1(wide_string_bv16,
				      (SI_Long)2048L,(SI_Long)0L);
			      current_wide_string = wide_string_bv16;
			      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				      3);
				fill_pointer_for_current_wide_string = 
					FIX((SI_Long)0L);
				PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					2);
				  length_1 = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				  total_length_of_current_wide_string = 
					  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)2L) + 
					  ((UBYTE_16_ISAREF_1(Current_wide_string,
					  length_1 - (SI_Long)1L) & 
					  (SI_Long)8191L) << (SI_Long)16L));
				  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					  1);
				    current_twriting_output_type = 
					    Qwide_string;
				    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					    0);
				      tformat(3,string_constant_10,
					      array_constant_15,
					      handler_string);
				      temp = copy_out_current_wide_string();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			    reclaim_wide_string(handler_string);
			    new_handler = temp;
			}
			else
			    new_handler = handler;
			if ( !EQ(new_handler,previous_handler) ||  
				!TRUEP(CDR(sublist))) {
			    if (key_patterns_and_classes) {
				current_wide_string_list = Qdo_not_use;
				PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
					4);
				  wide_string_bv16 = 
					  allocate_byte_vector_16(FIX((SI_Long)2048L 
					  + (SI_Long)3L));
				  bv16_length = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
				  aref_arg_2 = bv16_length - (SI_Long)2L;
				  aref_new_value = (SI_Long)2048L & 
					  (SI_Long)65535L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  aref_arg_2 = bv16_length - (SI_Long)1L;
				  aref_new_value = (SI_Long)57344L | 
					  (SI_Long)0L;
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  aref_arg_2,aref_new_value);
				  UBYTE_16_ISASET_1(wide_string_bv16,
					  (SI_Long)2048L,(SI_Long)0L);
				  current_wide_string = wide_string_bv16;
				  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
					  3);
				    fill_pointer_for_current_wide_string = 
					    FIX((SI_Long)0L);
				    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
					    2);
				      length_1 = 
					      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
				      total_length_of_current_wide_string 
					      = 
					      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)2L) + 
					      ((UBYTE_16_ISAREF_1(Current_wide_string,
					      length_1 - (SI_Long)1L) & 
					      (SI_Long)8191L) << 
					      (SI_Long)16L));
				      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
					      1);
					current_twriting_output_type = 
						Qwide_string;
					PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
						0);
					  twrite_key_patterns_and_classes(nreverse(key_patterns_and_classes));
					  key_string = 
						  copy_out_current_wide_string();
					POP_SPECIAL();
				      POP_SPECIAL();
				    POP_SPECIAL();
				  POP_SPECIAL();
				POP_SPECIAL();
				key_cell = make_text_cell(2,
					slot_value_cons_1(key_string,Nil),
					Qhelp_key_name_format);
				pretty = text_string_p(previous_handler) ? 
					copy_text_string(previous_handler) 
					: 
					ui_command_name_for_describe_keymap(previous_handler);
				handler_cell = make_text_cell(2,
					slot_value_cons_1(pretty,Nil),
					Qhelp_key_binding_format);
				element = Nil;
				ab_loop_list__1 = key_patterns_and_classes;
			      next_loop_3:
				if ( !TRUEP(ab_loop_list__1))
				    goto end_loop_3;
				element = M_CAR(ab_loop_list__1);
				ab_loop_list__1 = M_CDR(ab_loop_list__1);
				reclaim_slot_value_cons_1(element);
				goto next_loop_3;
			      end_loop_3:;
				reclaim_slot_value_list_1(key_patterns_and_classes);
				key_patterns_and_classes = Nil;
				Row = slot_value_cons_1(key_cell,Row);
				Row = slot_value_cons_1(handler_cell,Row);
				if (Nil || IFIX(length(Row)) == row_length) {
				    temp = nreverse(Row);
				    rows = slot_value_cons_1(temp,rows);
				    Row = Nil;
				}
			    }
			    key_patterns_and_classes = 
				    slot_value_cons_1(slot_value_cons_1(key_pattern,
				    class_1),key_patterns_and_classes);
			    previous_handler = new_handler;
			}
			else
			    key_patterns_and_classes = 
				    slot_value_cons_1(slot_value_cons_1(key_pattern,
				    class_1),key_patterns_and_classes);
		    }
		    goto next_loop_1;
		  end_loop_1:;
		    sublist = M_CDR(sublist);
		    goto next_loop;
		  end_loop:;
		    if (key_patterns_and_classes) {
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
			  UBYTE_16_ISASET_1(wide_string_bv16,
				  (SI_Long)2048L,(SI_Long)0L);
			  current_wide_string = wide_string_bv16;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
				  3);
			    fill_pointer_for_current_wide_string = 
				    FIX((SI_Long)0L);
			    PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				    2);
			      length_1 = 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			      total_length_of_current_wide_string = 
				      FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)2L) + 
				      ((UBYTE_16_ISAREF_1(Current_wide_string,
				      length_1 - (SI_Long)1L) & 
				      (SI_Long)8191L) << (SI_Long)16L));
			      PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				      1);
				current_twriting_output_type = Qwide_string;
				PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
					0);
				  twrite_key_patterns_and_classes(nreverse(key_patterns_and_classes));
				  key_string = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			key_cell = make_text_cell(2,
				slot_value_cons_1(key_string,Nil),
				Qhelp_key_name_format);
			pretty = text_string_p(previous_handler) ? 
				copy_text_string(previous_handler) : 
				ui_command_name_for_describe_keymap(previous_handler);
			handler_cell = make_text_cell(2,
				slot_value_cons_1(pretty,Nil),
				Qhelp_key_binding_format);
			element = Nil;
			ab_loop_list_ = key_patterns_and_classes;
		      next_loop_4:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_4;
			element = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			reclaim_slot_value_cons_1(element);
			goto next_loop_4;
		      end_loop_4:;
			reclaim_slot_value_list_1(key_patterns_and_classes);
			key_patterns_and_classes = Nil;
			Row = slot_value_cons_1(key_cell,Row);
			Row = slot_value_cons_1(handler_cell,Row);
			if (T || IFIX(length(Row)) == row_length) {
			    temp = nreverse(Row);
			    rows = slot_value_cons_1(temp,rows);
			    Row = Nil;
			}
		    }
		    temp = slot_value_cons_1(slot_value_list_4(Nil,Nil,Nil,
			    make_text_cell(2,slot_value_cons_1(name,Nil),
			    Qhelp_title_format)),Nil);
		    temp = nconc2(temp,nreverse(rows));
		  POP_SPECIAL();
		  SAVE_VALUES(VALUES_1(temp));
	      }
	      POP_UNWIND_PROTECT(0);
	      UNLOCK(Localization_context);
	      CONTINUE_UNWINDING(0);
	      result = RESTORE_VALUES();
	      SAVE_VALUES(VALUES_1(result));
	      remove_last_item_in_current_localization_domains();
	  }
	  POP_UNWIND_PROTECT(1);
	  UNLOCK(Localization_context);
	  CONTINUE_UNWINDING(1);
	  result = RESTORE_VALUES();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qkeymap_named;       /* keymap-named */

/* DESCRIBE-WORKSTATION-CONTEXT-KEYMAPS */
Object describe_workstation_context_keymaps(context_description,frame_qm)
    Object context_description, frame_qm;
{
    Object keymap_name, ab_loop_list_, keymap_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(129,65);
    keymap_name = Nil;
    ab_loop_list_ = ISVREF(context_description,(SI_Long)4L);
    keymap_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    keymap_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    keymap_qm = getfq_function_no_default(INLINE_SYMBOL_PLIST(keymap_name),
	    Qkeymap_named);
    if (keymap_qm && keymap_enabled_p(keymap_qm) &&  
	    !TRUEP(keymap_private_p(keymap_qm))) {
	ab_loopvar__2 = describe_keymap(keymap_qm,frame_qm);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
    }
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* DESCRIBE-WORKSTATION-CONTEXT-STACK */
Object describe_workstation_context_stack(frame_qm)
    Object frame_qm;
{
    Object context_name_qm, context_description, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(129,66);
    context_name_qm = ISVREF(Current_workstation_context,(SI_Long)1L);
    context_description = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(context_name_qm))
	goto end_loop;
    context_description = find_workstation_context(1,context_name_qm);
    ab_loopvar__2 = 
	    describe_workstation_context_keymaps(context_description,frame_qm);
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    context_name_qm = find_workstation_context(1,
	    ISVREF(context_description,(SI_Long)2L));
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qhelp_table_format;  /* help-table-format */

static Object Qthick_workspace_frame_style;  /* thick-workspace-frame-style */

/* MAKE-HELP-WORKSPACE */
Object make_help_workspace(frame_qm)
    Object frame_qm;
{
    Object table_rows, table, workspace;

    x_note_fn_call(129,67);
    table_rows = describe_workstation_context_stack(frame_qm);
    table = make_or_reformat_table(5,table_rows,Qhelp_table_format,Nil,Nil,T);
    workspace = make_workspace(4,Qtemporary_workspace,Nil,table,
	    FIX((SI_Long)10L));
    set_frame_style_of_block(workspace,Qthick_workspace_frame_style);
    return VALUES_1(workspace);
}

static Object Qspecial_character_help_text_cell_format;  /* special-character-help-text-cell-format */

static Object Qchar_lesspw_function;  /* char-lesspw-function */

/* MAKE-DIACRITIC-TABLE-ROW */
Object make_diacritic_table_row(name,key_for_accent)
    Object name, key_for_accent;
{
    Object text_cell_format_name, name_column, type_in_sequence_column;
    Object wide_character, code, match_for_key_for_accent, presentation;
    Object lowercase_qm, base_qm, type_ins_qm, ab_loop_list_;
    Object base_and_presentations_characters, ab_loopvar_, ab_loopvar__1;
    Object ab_loop_desetq_, temp, c, ab_loop_list__1, ab_loop_it_, temp_1;
    char temp_2;

    x_note_fn_call(129,68);
    text_cell_format_name = Qspecial_character_help_text_cell_format;
    name_column = make_text_cell(2,
	    convert_text_string_to_text(copy_text_string(name)),
	    text_cell_format_name);
    type_in_sequence_column = make_text_cell(2,
	    make_text_for_special_character_type_ins(key_for_accent),
	    text_cell_format_name);
    wide_character = ATOM(key_for_accent) ? key_for_accent : 
	    CAR(key_for_accent);
    code = wide_character;
    if (IFIX(code) < (SI_Long)127L)
	match_for_key_for_accent = (SI_Long)65L <= IFIX(code) && 
		IFIX(code) <= (SI_Long)90L ? FIX(IFIX(code) + 
		(SI_Long)32L) : code;
    else {
	match_for_key_for_accent = unicode_lowercase_if_uppercase(code);
	if (match_for_key_for_accent);
	else
	    match_for_key_for_accent = code;
    }
    presentation = Nil;
    lowercase_qm = Nil;
    base_qm = Nil;
    type_ins_qm = Nil;
    ab_loop_list_ = Editor_special_character_alist;
    base_and_presentations_characters = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    presentation = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    lowercase_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    base_qm = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    type_ins_qm = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (base_qm) {
	if (LISTP(type_ins_qm)) {
	    c = Nil;
	    ab_loop_list__1 = type_ins_qm;
	    ab_loop_it_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    c = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    code = match_for_key_for_accent;
	    if (IFIX(code) < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp_1 = unicode_lowercase_if_uppercase(code);
		if (temp_1);
		else
		    temp_1 = code;
	    }
	    code = c;
	    if (IFIX(code) < (SI_Long)127L)
		temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
	    }
	    ab_loop_it_ = NUM_EQ(temp_1,temp) ? T : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_1:;
	}
	else {
	    code = match_for_key_for_accent;
	    if (IFIX(code) < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp_1 = unicode_lowercase_if_uppercase(code);
		if (temp_1);
		else
		    temp_1 = code;
	    }
	    code = type_ins_qm;
	    if (IFIX(code) < (SI_Long)127L)
		temp = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
			(SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	    else {
		temp = unicode_lowercase_if_uppercase(code);
		if (temp);
		else
		    temp = code;
	    }
	    temp_2 = NUM_EQ(temp_1,temp);
	}
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	ab_loopvar__1 = gensym_cons_1(gensym_cons_1(base_qm,presentation),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    base_and_presentations_characters = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
    }
    goto next_loop;
  end_loop:
    base_and_presentations_characters = 
	    sort_list(base_and_presentations_characters,
	    SYMBOL_FUNCTION(Qchar_lesspw_function),SYMBOL_FUNCTION(Qcar));
    temp = make_text_cell(2,
	    make_text_for_diacritic_table_row_with_presentations(base_and_presentations_characters),
	    text_cell_format_name);
    temp = slot_value_list_4(temp,make_text_cell(2,
	    make_text_for_diacritic_table_row_with_type_ins(base_and_presentations_characters),
	    text_cell_format_name),type_in_sequence_column,name_column);
    reclaim_gensym_tree_1(base_and_presentations_characters);
    return VALUES_1(temp);
    return VALUES_1(Qnil);
}

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

/* TWRITE-HELP-TABLE-CHARACTER */
Object twrite_help_table_character(wide_character)
    Object wide_character;
{
    Object char_or_string, temp, schar_arg_2, schar_new_value, thing_1;
    SI_Long thing;

    x_note_fn_call(129,69);
    if ( !(FIXNUMP(wide_character) && FIXNUM_LE(FIX((SI_Long)0L),
	    wide_character) && FIXNUM_LE(wide_character,FIX((SI_Long)255L))))
	char_or_string = wide_character;
    else
	switch (INTEGER_TO_UNSIGNED_CHAR(wide_character)) {
	  case 9:
	    char_or_string = array_constant_16;
	    break;
	  case 32:
	    char_or_string = array_constant_17;
	    break;
	  case 13:
	    char_or_string = array_constant_18;
	    break;
	  case 160:
	    char_or_string = array_constant_19;
	    break;
	  default:
	    char_or_string = wide_character;
	    break;
	}
    if (FIXNUMP(char_or_string)) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)32L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)32L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing_1 = char_or_string;
	    return twrite_wide_character(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing_1 = char_or_string;
	    schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ? 
		    CHAR_CODE(thing_1) : thing_1);
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	    return VALUES_1(Fill_pointer_for_current_gensym_string);
	}
    }
    else
	return twrite_general_string(char_or_string);
}

static Object string_constant_11;  /* " " */

static Object Qab_slot_value;      /* slot-value */

/* MAKE-TEXT-FOR-DIACRITIC-TABLE-ROW-WITH-PRESENTATIONS */
Object make_text_for_diacritic_table_row_with_presentations(base_and_presentations_characters)
    Object base_and_presentations_characters;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object presentation, more_qm, ab_loop_list_, temp, temp_1, temp_2;
    Object gensym_list_of_wide_strings, string_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_cons, svref_new_value, gensymed_symbol;
    Object short_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(129,70);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      current_wide_string = new_wide_string;
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
	      presentation = Nil;
	      more_qm = Nil;
	      ab_loop_list_ = base_and_presentations_characters;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      temp = CAR(ab_loop_list_);
	      presentation = CDR(temp);
	      more_qm = CDR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      twrite_help_table_character(presentation);
	      if (more_qm)
		  tformat(1,string_constant_11);
	      goto next_loop;
	    end_loop:;
	      temp_1 = Current_wide_string;
	      temp_2 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_2) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_2) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp_1,IFIX(temp_2),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_slot_value_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_slot_value_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_slot_value_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_slot_value_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp_1 = short_string;
    }
    else
	temp_1 = string_1;
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp);
}

/* MAKE-TEXT-FOR-DIACRITIC-TABLE-ROW-WITH-TYPE-INS */
Object make_text_for_diacritic_table_row_with_type_ins(base_and_presentations_characters)
    Object base_and_presentations_characters;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object base_character, more_qm, ab_loop_list_, temp, temp_1, temp_2;
    Object gensym_list_of_wide_strings, string_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_cons, svref_new_value, gensymed_symbol;
    Object short_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(129,71);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      current_wide_string = new_wide_string;
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
	      base_character = Nil;
	      more_qm = Nil;
	      ab_loop_list_ = base_and_presentations_characters;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      temp = CAR(ab_loop_list_);
	      base_character = CAR(temp);
	      more_qm = CDR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      twrite_help_table_character(base_character);
	      if (more_qm)
		  tformat(1,string_constant_11);
	      goto next_loop;
	    end_loop:;
	      temp_1 = Current_wide_string;
	      temp_2 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_2) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_2) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp_1,IFIX(temp_2),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_slot_value_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_slot_value_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp_1 = Available_slot_value_conses_vector;
	temp_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp_1,temp_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp_1 = Available_slot_value_conses_tail_vector;
	    temp_2 = Current_thread_index;
	    SVREF(temp_1,temp_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp_1 = short_string;
    }
    else
	temp_1 = string_1;
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp);
}

static Object string_constant_12;  /* "Alt+i " */

static Object string_constant_13;  /* "Alt+i" */

static Object string_constant_14;  /* " or " */

static Object string_constant_15;  /* ", or " */

static Object array_constant_20;   /* # */

/* MAKE-TEXT-FOR-SPECIAL-CHARACTER-TYPE-INS */
Object make_text_for_special_character_type_ins(type_ins)
    Object type_ins;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object l, temp, temp_1, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object svref_new_value, gensymed_symbol, short_string, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(129,72);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
	    4);
      current_wide_string = new_wide_string;
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
	      if (ATOM(type_ins)) {
		  tformat(1,string_constant_12);
		  twrite_help_table_character(type_ins);
	      }
	      else {
		  l = type_ins;
		next_loop:
		  if ( !TRUEP(l))
		      goto end_loop;
		  tformat(1,string_constant_13);
		  twrite_help_table_character(CAR(l));
		  if (CDR(l)) {
		      if ( !TRUEP(CDDR(l)))
			  twrite_general_string(EQ(l,type_ins) ? 
				  string_constant_14 : string_constant_15);
		      else
			  twrite_beginning_of_wide_string(array_constant_20,
				  FIX((SI_Long)2L));
		  }
		  l = M_CDR(l);
		  goto next_loop;
		end_loop:;
	      }
	      temp = Current_wide_string;
	      temp_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(temp_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(temp_1) >>  -  - 
		      (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(temp_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = ISVREF(Available_slot_value_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_slot_value_conses_vector;
	temp_1 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,temp_1) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_slot_value_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_slot_value_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp = short_string;
    }
    else
	temp = string_1;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_1;
  end_loop_1:
    temp_2 = ab_loopvar_;
    goto end_1;
    temp_2 = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return VALUES_1(temp_2);
}

static Object array_constant_21;   /* # */

static Object array_constant_22;   /* # */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

/* MAKE-DIACRITIC-HEADER-TABLE-ROW */
Object make_diacritic_header_table_row()
{
    Object text_cell_format_name, temp, temp_1, temp_2;

    x_note_fn_call(129,73);
    text_cell_format_name = Qspecial_character_help_text_cell_format;
    temp = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_21,
	    FIX((SI_Long)18L))),text_cell_format_name);
    temp_1 = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_22,
	    FIX((SI_Long)15L))),text_cell_format_name);
    temp_2 = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_23,
	    FIX((SI_Long)16L))),text_cell_format_name);
    return slot_value_list_4(temp,temp_1,temp_2,make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_24,
	    FIX((SI_Long)9L))),text_cell_format_name));
}

static Object array_constant_25;   /* # */

/* MAKE-STANDALONE-HEADER-TABLE-ROW */
Object make_standalone_header_table_row()
{
    Object text_cell_format_name, temp, temp_1, temp_2;

    x_note_fn_call(129,74);
    text_cell_format_name = Qspecial_character_help_text_cell_format;
    temp = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_25,
	    FIX((SI_Long)17L))),text_cell_format_name);
    temp_1 = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_23,
	    FIX((SI_Long)16L))),text_cell_format_name);
    temp_2 = make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_25,
	    FIX((SI_Long)17L))),text_cell_format_name);
    return slot_value_list_4(temp,temp_1,temp_2,make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_23,
	    FIX((SI_Long)16L))),text_cell_format_name));
}

/* MAKE-STANDALONE-SPECIAL-CHARACTER-ROWS */
Object make_standalone_special_character_rows()
{
    Object l, row_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, columns_qm;
    Object number_of_columns_so_far, row, ab_loopvar__3, l_old_value, temp;
    Declare_special(1);

    x_note_fn_call(129,75);
    l = Editor_special_character_alist;
    row_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    columns_qm = Nil;
    number_of_columns_so_far = FIX((SI_Long)0L);
    row = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
    next_loop_1:
      l_old_value = l;
      temp = FIRST(l_old_value);
      l = REST(l_old_value);
      columns_qm = make_standalone_special_character_row_if_necessary(temp);
      if (columns_qm) {
	  ab_loopvar__3 = columns_qm;
	  if (ab_loopvar__3) {
	      if (ab_loopvar__2)
		  M_CDR(ab_loopvar__2) = ab_loopvar__3;
	      else
		  Row = ab_loopvar__3;
	      ab_loopvar__2 = last(ab_loopvar__3,_);
	  }
	  number_of_columns_so_far = FIXNUM_ADD1(number_of_columns_so_far);
      }
      if ( !TRUEP(l))
	  goto end_loop;
      if (IFIX(number_of_columns_so_far) > (SI_Long)1L)
	  goto end_loop;
      goto next_loop_1;
    end_loop:
      row_qm = Row;
      goto end_1;
      row_qm = Qnil;
    end_1:;
    POP_SPECIAL();
    if (row_qm) {
	ab_loopvar__2 = slot_value_cons_1(row_qm,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    if ( !TRUEP(l))
	goto end_loop_1;
    goto next_loop;
  end_loop_1:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* MAKE-STANDALONE-SPECIAL-CHARACTER-ROW-IF-NECESSARY */
Object make_standalone_special_character_row_if_necessary(editor_special_character_alist_entry)
    Object editor_special_character_alist_entry;
{
    Object text_cell_format_name, gensymed_symbol, presentation, lowercase_qm;
    Object base_qm, type_ins_qm, wide_string_bv16, new_wide_string;
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, gensym_list_of_wide_strings, string_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object svref_new_value, short_string, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(129,76);
    text_cell_format_name = Qspecial_character_help_text_cell_format;
    gensymed_symbol = editor_special_character_alist_entry;
    presentation = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    lowercase_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    base_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    type_ins_qm = CAR(gensymed_symbol);
    if ( !TRUEP(base_qm) && type_ins_qm) {
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		4);
	  current_wide_string = new_wide_string;
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
		  twrite_help_table_character(presentation);
		  temp = Current_wide_string;
		  temp_1 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(temp_1) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(temp_1) >>  -  - 
			  (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp,IFIX(temp_1),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list_ = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	string_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_slot_value_conses_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,temp_1) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_slot_value_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = ISVREF(Available_slot_value_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_slot_value_conses_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,temp_1) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_slot_value_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_slot_value_conses_tail_vector;
		temp_1 = Current_thread_index;
		SVREF(temp,temp_1) = Nil;
	    }
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_slot_value_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp = short_string;
	}
	else
	    temp = string_1;
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_slot_value);
	ab_loopvar__2 = gensymed_symbol;
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
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
	temp_2 = make_text_cell(2,temp_2,text_cell_format_name);
	return slot_value_list_2(temp_2,make_text_cell(2,
		make_text_for_special_character_type_ins(type_ins_qm),
		text_cell_format_name));
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_26;   /* # */

static Object Qspecial_character_help_header_text_cell_format;  /* special-character-help-header-text-cell-format */

static Object list_constant_4;     /* # */

/* MAKE-DIACRITIC-HELP-TABLE-ROWS */
Object make_diacritic_help_table_rows()
{
    Object temp, temp_1, name, key_for_accent, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp_2;

    x_note_fn_call(129,77);
    temp = slot_value_cons_1(slot_value_list_4(Nil,Nil,Nil,
	    make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_26,
	    FIX((SI_Long)34L))),
	    Qspecial_character_help_header_text_cell_format)),Nil);
    temp_1 = slot_value_cons_1(make_diacritic_header_table_row(),Nil);
    name = Nil;
    key_for_accent = Nil;
    ab_loop_list_ = list_constant_4;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp_2 = CDR(ab_loop_desetq_);
    key_for_accent = CAR(temp_2);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = slot_value_cons_1(make_diacritic_table_row(name,
	    key_for_accent),Nil);
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
    return VALUES_1(nconc2(temp,nconc2(temp_1,temp_2)));
}

static Object array_constant_27;   /* # */

/* MAKE-STANDALONE-SPECIAL-CHARACTER-HELP-TABLE-ROWS */
Object make_standalone_special_character_help_table_rows()
{
    Object temp, temp_1;

    x_note_fn_call(129,78);
    temp = slot_value_cons_1(slot_value_list_4(Nil,Nil,Nil,
	    make_text_cell(2,
	    convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_27,
	    FIX((SI_Long)29L))),
	    Qspecial_character_help_header_text_cell_format)),Nil);
    temp_1 = slot_value_cons_1(make_standalone_header_table_row(),Nil);
    return VALUES_1(nconc2(temp,nconc2(temp_1,
	    make_standalone_special_character_rows())));
}

/* MAKE-SPECIAL-CHARACTER-HELP-TABLE */
Object make_special_character_help_table()
{
    Object temp, temp_1, temp_2, table_rows;

    x_note_fn_call(129,79);
    temp = make_diacritic_help_table_rows();
    temp_1 = make_standalone_special_character_help_table_rows();
    temp_2 = get_language_for_current_workstation_if_any();
    if (temp_2);
    else
	temp_2 = Language_parameters ? ISVREF(Language_parameters,
		(SI_Long)22L) : Qnil;
    if (temp_2);
    else
	temp_2 = Default_language;
    table_rows = nconc2(temp,nconc2(temp_1,
	    make_hex_code_help_table_rows(temp_2)));
    return make_or_reformat_table(3,table_rows,Qhelp_table_format,Nil);
}

static Object Qkanji;              /* kanji */

static Object Qhangul;             /* hangul */

static Object Qrussian;            /* russian */

static Object Qcyrillic;           /* cyrillic */

static Object Qunicode;            /* unicode */

static Object string_constant_16;  /* "Hangul (KS C 5601)" */

static Object string_constant_17;  /* "Cyrillic (ISO 8859-5)" */

static Object string_constant_18;  /* "Kanji (JIS)" */

static Object string_constant_19;  /* "Unicode 2.0" */

static Object string_constant_20;  /* "For ~a" */

static Object list_constant_5;     /* # */

static Object string_constant_21;  /* "Unicode" */

static Object string_constant_22;  /* "Enter Alt+i followed by a ~d-digit ~a hex code.  ~
				    *              ~%Precede with x to force hex interpretation if ~
				    *              the first digit is ambiguous. - e.g. \"xC49A\""
				    */

/* MAKE-HEX-CODE-HELP-TABLE-ROWS */
Object make_hex_code_help_table_rows(language)
    Object language;
{
    Object script, charset_name, temp;
    SI_Long code_digit_length;

    x_note_fn_call(129,80);
    if (EQ(language,Qjapanese))
	script = Qkanji;
    else if (EQ(language,Qkorean))
	script = Qhangul;
    else if (EQ(language,Qrussian))
	script = Qcyrillic;
    else
	script = Qunicode;
    if (EQ(script,Qhangul))
	charset_name = string_constant_16;
    else if (EQ(script,Qcyrillic))
	charset_name = string_constant_17;
    else if (EQ(script,Qkanji))
	charset_name = string_constant_18;
    else if (EQ(script,Qunicode))
	charset_name = string_constant_19;
    else
	charset_name = Qnil;
    code_digit_length = EQ(script,Qcyrillic) ? (SI_Long)2L : (SI_Long)4L;
    temp = slot_value_list_4(Nil,Nil,Nil,make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(2,
	    string_constant_20,memq_function(language,list_constant_5) ? 
	    language : string_constant_21)),
	    Qspecial_character_help_header_text_cell_format));
    return slot_value_list_2(temp,slot_value_list_4(Nil,Nil,Nil,
	    make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(3,
	    string_constant_22,FIX(code_digit_length),charset_name)),
	    Qspecial_character_help_text_cell_format)));
}

/* PUT-UP-SPECIAL-CHARACTER-HELP-WORKSPACE */
Object put_up_special_character_help_workspace()
{
    Object special_character_help_workspace, special_character_help_table;
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(129,81);
    special_character_help_workspace = make_workspace(4,
	    Qtemporary_workspace,Nil,Nil,FIX((SI_Long)0L));
    special_character_help_table = make_special_character_help_table();
    gensymed_symbol = ISVREF(special_character_help_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(special_character_help_workspace,
	    (SI_Long)17L));
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(special_character_help_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(ISVREF(special_character_help_workspace,
	    (SI_Long)17L));
    add_to_workspace(4,special_character_help_table,
	    special_character_help_workspace,temp,FIX(gensymed_symbol_1 + 
	    gensymed_symbol_2));
    return put_workspace_on_pane_function(special_character_help_workspace,
	    Current_workstation_detail_pane,Qright,Qbottom,Nil,
	    FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

static Object Qreturn_from_breakpoint;  /* return-from-breakpoint */

/* IMMEDIATELY-RETURN-FROM-BREAKPOINT */
Object immediately_return_from_breakpoint(value)
    Object value;
{
    Object gensymed_symbol, structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,82);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = Return_from_breakpoint_task;
    if (CAS_SYMBOL(Qreturn_from_breakpoint_task,gensymed_symbol,Nil)) {
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
    if (Inside_breakpoint_p) {
	result = VALUES_1(value);
	THROW(Qreturn_from_breakpoint,result);
    }
    else
	return VALUES_1(Nil);
}

static Object Qimmediately_return_from_breakpoint;  /* immediately-return-from-breakpoint */

/* RETURN-FROM-BREAKPOINT */
Object return_from_breakpoint varargs_1(int, n)
{
    Object value, immediate_task_schedule_modify_arg_3;
    Object immediate_task_schedule_modify_arg_7, structure_being_reclaimed;
    Object temp, temp_1, svref_new_value, def_structure_schedule_task_variable;
    Object new_task;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(129,83);
    INIT_ARGS_nonrelocating();
    value = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (Inside_breakpoint_p &&  !TRUEP(Return_from_breakpoint_task)) {
	immediate_task_schedule_modify_arg_3 = 
		SYMBOL_FUNCTION(Qimmediately_return_from_breakpoint);
	immediate_task_schedule_modify_arg_7 = value;
	if (Return_from_breakpoint_task) {
	    if (EQ(Return_from_breakpoint_task,Current_schedule_task))
		Current_schedule_task = Nil;
	    if (ISVREF(Return_from_breakpoint_task,(SI_Long)6L))
		cancel_and_reclaim_scheduled_queue_element_1(Return_from_breakpoint_task);
	    inline_note_reclaim_cons(Return_from_breakpoint_task,Nil);
	    structure_being_reclaimed = Return_from_breakpoint_task;
	    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		    0);
	      reclaim_schedule_task_args(ISVREF(Return_from_breakpoint_task,
		      (SI_Long)9L));
	      temp = Return_from_breakpoint_task;
	      SVREF(temp,FIX((SI_Long)9L)) = Nil;
	    POP_SPECIAL();
	    temp = Return_from_breakpoint_task;
	    temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
		    IFIX(Current_thread_index));
	    SVREF(temp,FIX((SI_Long)0L)) = temp_1;
	    temp = Chain_of_available_schedule_tasks_vector;
	    temp_1 = Current_thread_index;
	    svref_new_value = Return_from_breakpoint_task;
	    SVREF(temp,temp_1) = svref_new_value;
	}
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
	new_task = def_structure_schedule_task_variable;
	SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
	SVREF(new_task,FIX((SI_Long)9L)) = Nil;
	SVREF(new_task,FIX((SI_Long)10L)) = Nil;
	SVREF(new_task,FIX((SI_Long)7L)) = Qimmediately_return_from_breakpoint;
	SVREF(new_task,FIX((SI_Long)8L)) = 
		immediate_task_schedule_modify_arg_3;
	ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
	SVREF(new_task,FIX((SI_Long)13L)) = 
		immediate_task_schedule_modify_arg_7;
	temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
	SVREF(new_task,FIX((SI_Long)11L)) = temp;
	temp = 
		constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
		(SI_Long)0L),new_task);
	SVREF(new_task,FIX((SI_Long)6L)) = temp;
	Return_from_breakpoint_task = new_task;
	return VALUES_1(Return_from_breakpoint_task);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_23;  /* "Disabling debugging by changing the \"Tracing and breakpoints enabled?\" ~
				    *      debugging parameter to \"no\".  Please edit the debugging parameters to ~
				    *      reenable debugging."
				    */

static Object Qmessage_and_breakpoint_overrides;  /* message-and-breakpoint-overrides */

/* DEBUGGER-DISABLE-DEBUGGING */
Object debugger_disable_debugging()
{
    x_note_fn_call(129,84);
    notify_user(1,string_constant_23);
    change_slot_value(3,Debugging_parameters,
	    Qmessage_and_breakpoint_overrides,Nil);
    return return_from_breakpoint(0);
}

DEFINE_VARIABLE_WITH_SYMBOL(Allow_debugger_pause, Qallow_debugger_pause);

DEFINE_VARIABLE_WITH_SYMBOL(Computation_instance_at_breakpoint, Qcomputation_instance_at_breakpoint);

DEFINE_VARIABLE_WITH_SYMBOL(Computation_frame_at_breakpoint, Qcomputation_frame_at_breakpoint);

DEFINE_VARIABLE_WITH_SYMBOL(All_computation_instances_above_breakpoint, Qall_computation_instances_above_breakpoint);

DEFINE_VARIABLE_WITH_SYMBOL(May_return_from_breakpoint, Qmay_return_from_breakpoint);

DEFINE_VARIABLE_WITH_SYMBOL(Pane_for_debugger_pause, Qpane_for_debugger_pause);

static Object string_constant_24;  /* "System will remain paused at this breakpoint.  ~
				    *                   Use \"Continue From Breakpoint\" to resume execution."
				    */

static Object Qpause;              /* pause */

/* DEBUGGER-PAUSE */
Object debugger_pause(pane)
    Object pane;
{
    x_note_fn_call(129,85);
    if (Allow_debugger_pause && Inside_breakpoint_p) {
	notify_user(1,string_constant_24);
	Pane_for_debugger_pause = pane;
	return return_from_breakpoint(1,Qpause);
    }
    else
	return VALUES_1(Nil);
}

/* COMPUTATION-FRAME-AT-BREAKPOINT-DEPENDS-ON-BLOCK-P */
Object computation_frame_at_breakpoint_depends_on_block_p(block)
    Object block;
{
    Object temp;

    x_note_fn_call(129,86);
    temp = Computation_frame_at_breakpoint && ( !((SI_Long)0L != 
	    (IFIX(ISVREF(Computation_frame_at_breakpoint,(SI_Long)5L)) & 
	    (SI_Long)262144L)) || (SI_Long)0L != (IFIX(ISVREF(block,
	    (SI_Long)5L)) & (SI_Long)262144L)) ? 
	    existence_depends_on_p(Computation_frame_at_breakpoint,block) :
	     Qnil;
    return VALUES_1(temp);
}

/* BREAK-OUT-OF-DEBUG-MESSAGES */
Object break_out_of_debug_messages()
{
    Object workstation, ab_loop_list_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, queue_sublist, event;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(129,87);
    SAVE_STACK();
    if ( !TRUEP(System_has_paused)) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
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
				    poll_workstation();
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
	queue_sublist = ISVREF(ISVREF(workstation,(SI_Long)2L),(SI_Long)1L);
	event = Nil;
      next_loop_1:
	if ( !TRUEP(queue_sublist))
	    goto end_loop_1;
	event = M_CAR(queue_sublist);
	queue_sublist = M_CDR(queue_sublist);
	if (IFIX(ISVREF(event,(SI_Long)1L)) == (SI_Long)26L) {
	    debugger_pause(detail_pane(ISVREF(workstation,(SI_Long)1L)));
	    result = VALUES_0();
	    RESTORE_STACK();
	    return result;
	}
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	RESTORE_STACK();
	return VALUES_1(Qnil);
    }
    else {
	RESTORE_STACK();
	return VALUES_1(Nil);
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Breakpoints_enabled_p, Qbreakpoints_enabled_p);

static Object Qg2_defstruct_structure_name_halt_info_g2_struct;  /* g2-defstruct-structure-name::halt-info-g2-struct */

/* PAUSE-DURING-DEBUG */
Object pause_during_debug(message_or_halt_info)
    Object message_or_halt_info;
{
    x_note_fn_call(129,88);
    if (Breakpoints_enabled_p &&  !TRUEP(Inside_breakpoint_p)) {
	pause_for_internal_error_or_debug(message_or_halt_info,T);
	if (SIMPLE_VECTOR_P(message_or_halt_info) && 
		EQ(ISVREF(message_or_halt_info,(SI_Long)0L),
		Qg2_defstruct_structure_name_halt_info_g2_struct))
	    reclaim_halt_info(message_or_halt_info);
	Pane_for_debugger_pause = Nil;
    }
    return VALUES_1(Nil);
}

/* PAUSE-FOR-INTERNAL-ERROR */
Object pause_for_internal_error(message_1)
    Object message_1;
{
    x_note_fn_call(129,89);
    pause_for_internal_error_or_debug(message_1,Nil);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug, Qresult_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug);

static Object Qtext;               /* text */

static Object Qbreakpoint_message;  /* breakpoint-message */

static Object Qbutton;             /* button */

static Object array_constant_28;   /* # */

static Object Qdisable_debugging;  /* disable-debugging */

static Object array_constant_29;   /* # */

static Object array_constant_30;   /* # */

static Object Qab_continue;        /* continue */

static Object Qitem;               /* item */

static Object Qitem_causing_breakpoint;  /* item-causing-breakpoint */

static Object Qabort_message;      /* abort-message */

static Object array_constant_31;   /* # */

static Object Qok;                 /* ok */

static Object Qbreakpoint;         /* breakpoint */

static Object Qinternal_error;     /* internal-error */

static Object Qfinish_dialog_for_pause_for_internal_error_or_debug;  /* finish-dialog-for-pause-for-internal-error-or-debug */

static Object Qnone;               /* none */

/* ENTER-DIALOG-FOR-PAUSE-FOR-INTERNAL-ERROR-OR-DEBUG */
Object enter_dialog_for_pause_for_internal_error_or_debug(message_or_halt_info,
	    debug_case_qm)
    Object message_or_halt_info, debug_case_qm;
{
    Object temp, halt_info_qm, message_1, temp_1, temp_2, workstation;
    Object ab_loop_list_, stack, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, current_workstation_context;
    Object type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(129,90);
    SAVE_STACK();
    if (SIMPLE_VECTOR_P(message_or_halt_info) && 
	    EQ(ISVREF(message_or_halt_info,(SI_Long)0L),
	    Qg2_defstruct_structure_name_halt_info_g2_struct)) {
	temp = ISVREF(message_or_halt_info,(SI_Long)8L);
	result = VALUES_2(message_or_halt_info,temp);
    }
    else
	result = VALUES_2(Nil,message_or_halt_info);
    MVS_2(result,halt_info_qm,message_1);
    if (debug_case_qm) {
	temp = eval_list_3(Qtext,copy_text_string(message_1),
		Qbreakpoint_message);
	temp_1 = eval_list_2(temp,eval_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_28,
		FIX((SI_Long)17L)),Qdisable_debugging));
	temp_2 = Allow_debugger_pause ? eval_cons_1(eval_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_29,
		FIX((SI_Long)5L)),Qpause),Nil) : Nil;
	temp = eval_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_30,
		FIX((SI_Long)8L)),Qab_continue);
	temp = nconc2(temp_1,nconc2(temp_2,eval_list_2(temp,
		eval_list_3(Qitem,Current_computation_frame,
		Qitem_causing_breakpoint))));
    }
    else {
	temp = eval_list_3(Qtext,copy_text_string(message_1),Qabort_message);
	temp = eval_list_2(temp,eval_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_31,
		FIX((SI_Long)2L)),Qok));
    }
    Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug = 
	    enter_dialog_for_t2(5,debug_case_qm ? Qbreakpoint : 
	    Qinternal_error,temp,
	    Qfinish_dialog_for_pause_for_internal_error_or_debug,Nil,Nil);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    stack = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    stack = ISVREF(workstation,(SI_Long)17L);
    ab_loopvar__2 = gensym_cons_1(gensym_cons_1(workstation,stack),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
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
				if ( !TRUEP(debug_case_qm)) {
				    temp = copy_text_string(message_1);
				    enter_dialog(15,temp,
					    copy_constant_wide_string_given_length(array_constant_31,
					    FIX((SI_Long)2L)),Qnone,
					    Qreturn_from_breakpoint,Nil,
					    Nil,Nil,Nil,Nil,Nil,Nil,Nil,
					    Nil,Nil,T);
				}
				else if (native_debugger_dialog_p(Current_workstation_window) 
					&& halt_info_qm)
				    post_native_debugger_dialog(halt_info_qm,
					    Computation_frame_at_breakpoint,
					    Current_workstation_window);
				else
				    post_classic_debugger_dialog(message_1);
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
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

static Object Qdebugger_pause;     /* debugger-pause */

static Object Qadditional;         /* additional */

static Object Qcancel;             /* cancel */

static Object Qdebugger_disable_debugging;  /* debugger-disable-debugging */

/* POST-CLASSIC-DEBUGGER-DIALOG */
Object post_classic_debugger_dialog(message_1)
    Object message_1;
{
    Object temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;

    x_note_fn_call(129,91);
    temp = copy_text_string(message_1);
    temp_1 = copy_constant_wide_string_given_length(array_constant_28,
	    FIX((SI_Long)17L));
    temp_2 = Allow_debugger_pause ? 
	    copy_constant_wide_string_given_length(array_constant_29,
	    FIX((SI_Long)5L)) : 
	    copy_constant_wide_string_given_length(array_constant_30,
	    FIX((SI_Long)8L));
    temp_3 = Allow_debugger_pause ? Qdebugger_pause : Qreturn_from_breakpoint;
    temp_4 = Allow_debugger_pause ? 
	    slot_value_cons_1(Current_workstation_detail_pane,Nil) : Qnil;
    temp_5 = Allow_debugger_pause ? 
	    copy_constant_wide_string_given_length(array_constant_30,
	    FIX((SI_Long)8L)) : Nil;
    temp_6 = Allow_debugger_pause ? Qreturn_from_breakpoint : Nil;
    temp_7 = Allow_debugger_pause ? Qadditional : Qcancel;
    return enter_dialog(16,temp,temp_1,temp_2,Qdebugger_disable_debugging,
	    Nil,temp_3,temp_4,Nil,Nil,temp_5,temp_6,Nil,temp_7,Nil,T,
	    make_short_representation(1,Current_computation_frame));
}

/* DEBUGGER-GET-BREAKPOINTS */
Object debugger_get_breakpoints(procedure)
    Object procedure;
{
    Object breakpoints, bkpt, ab_loop_list_, line, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, fixnum_list;

    x_note_fn_call(129,92);
    breakpoints = get_dynamic_breakpoints_internal(1,procedure);
    bkpt = Nil;
    ab_loop_list_ = breakpoints;
    line = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    bkpt = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    line = dynamic_breakpoint_line_func(bkpt);
    ab_loopvar__2 = eval_cons_1(dynamic_breakpoint_enabled_p(bkpt) ? line :
	     FIXNUM_LOGIOR(line,Editor_disabled_breakpoint_flag),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    fixnum_list = ab_loopvar_;
    goto end_1;
    fixnum_list = Qnil;
  end_1:;
    reclaim_eval_list_1(breakpoints);
    return VALUES_1(fixnum_list);
}

static Object array_constant_32;   /* # */

static Object string_constant_25;  /* "G2 Break in ~NF" */

static Object string_constant_26;  /* ", line ~d" */

static Object string_constant_27;  /* ", instruction ~d" */

static Object Qsource_stepping;    /* source-stepping */

static Object Qbreakpoints;        /* breakpoints */

static Object Qtab_width;          /* tab-width */

/* POST-NATIVE-DEBUGGER-DIALOG */
Object post_native_debugger_dialog(halt_info,computation_frame,gensym_window)
    Object halt_info, computation_frame, gensym_window;
{
    Object gensymed_symbol, sub_class_bit_vector, source_code, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object title, gensymed_symbol_4, car_new_value_1, options, temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp, car_new_value;
    Declare_special(5);

    x_note_fn_call(129,93);
    gensymed_symbol = ISVREF(computation_frame,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
	source_code = convert_text_to_text_string(1,
		procedure_definition_function(computation_frame));
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	if (temp) {
	    temp_1 = ISVREF(computation_frame,(SI_Long)16L);
	    source_code = convert_text_to_text_string(1,CDR(temp_1));
	}
	else
	    source_code = copy_wide_string(array_constant_32);
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
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(2,string_constant_25,computation_frame);
	      if (ISVREF(halt_info,(SI_Long)6L))
		  tformat(2,string_constant_26,ISVREF(halt_info,(SI_Long)6L));
	      tformat(2,string_constant_27,ISVREF(halt_info,(SI_Long)5L));
	      title = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_4 = gensymed_symbol;
    M_CAR(gensymed_symbol_4) = Qsource_stepping;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    car_new_value = EQ(Source_stepping_level,FIX((SI_Long)1L));
    M_CAR(gensymed_symbol_4) = car_new_value ? T : Nil;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = Qbreakpoints;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    car_new_value_1 = debugger_get_breakpoints(computation_frame);
    M_CAR(gensymed_symbol_4) = car_new_value_1;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    M_CAR(gensymed_symbol_4) = Qtab_width;
    gensymed_symbol_4 = M_CDR(gensymed_symbol_4);
    car_new_value_1 = ISVREF(Editor_parameters,(SI_Long)25L);
    M_CAR(gensymed_symbol_4) = car_new_value_1;
    options = gensymed_symbol;
    temp_1 = ISVREF(halt_info,(SI_Long)6L);
    if (temp_1);
    else
	temp_1 = IFIX(ISVREF(halt_info,(SI_Long)5L)) == (SI_Long)0L ? 
		FIX((SI_Long)1L) : FIX((SI_Long)-1L);
    temp_2 = ISVREF(halt_info,(SI_Long)7L);
    if (temp_2);
    else
	temp_2 = array_constant_2;
    manage_debugger_dialog(8,gensym_window,Debugger_dialog_create,temp_1,
	    title,temp_2,source_code,ISVREF(halt_info,(SI_Long)4L),options);
    reclaim_wide_string(title);
    reclaim_wide_string(source_code);
    return reclaim_eval_tree_1(options);
}

/* CANCEL-NATIVE-DEBUGGER-DIALOG */
Object cancel_native_debugger_dialog(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(129,94);
    if (native_debugger_dialog_p(gensym_window))
	return manage_debugger_dialog(2,gensym_window,Debugger_dialog_cancel);
    else
	return VALUES_1(Nil);
}

/* FINISH-DIALOG-FOR-PAUSE-FOR-INTERNAL-ERROR-OR-DEBUG */
Object finish_dialog_for_pause_for_internal_error_or_debug(dialog_sequence_number,
	    client_item)
    Object dialog_sequence_number, client_item;
{
    Object temp;

    x_note_fn_call(129,95);
    temp = 
	    EQL(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug,
	    dialog_sequence_number) ? 
	    execute_breakpoint_button(leave_dialog_for_t2(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug)) 
	    : Nil;
    remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
	    ISVREF(client_item,(SI_Long)26L));
    return VALUES_1(temp);
}

/* EXECUTE-BREAKPOINT-BUTTON */
Object execute_breakpoint_button(button)
    Object button;
{
    x_note_fn_call(129,96);
    if (EQ(button,Qdisable_debugging))
	return debugger_disable_debugging();
    else if (EQ(button,Qpause))
	return debugger_pause(Nil);
    else if (EQ(button,Qab_continue))
	return return_from_breakpoint(0);
    else if (EQ(button,Qok))
	return return_from_breakpoint(0);
    else
	return VALUES_1(Nil);
}

/* LEAVE-DIALOG-FOR-PAUSE-FOR-INTERNAL-ERROR-OR-DEBUG */
Object leave_dialog_for_pause_for_internal_error_or_debug(workstations_with_their_stacks)
    Object workstations_with_their_stacks;
{
    Object workstation, ab_loop_list_, stack, gensym_window, temp;
    Object current_stack, ab_loop_it_, current_workstation_1;
    Object current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, current_workstation_context;
    Object type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm, x;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(129,97);
    SAVE_STACK();
    leave_dialog_for_t2(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    stack = Nil;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = assq_function(workstation,workstations_with_their_stacks);
    stack = CDR(temp);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if (native_debugger_dialog_p(gensym_window))
	cancel_native_debugger_dialog(gensym_window);
    current_stack = ISVREF(workstation,(SI_Long)17L);
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(current_stack))
	goto end_loop_1;
    ab_loop_it_ = EQUAL(stack,current_stack) ? T : Nil;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    current_stack = M_CDR(current_stack);
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1) {
	LOCK(For_workstation);
	if (PUSH_UNWIND_PROTECT(0)) {
	    current_workstation_1 = workstation;
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
				  next_loop_2:
				    temp = ISVREF(workstation,(SI_Long)17L);
				    if ( !TRUEP(CDR(temp)))
					goto end_loop_2;
				    if (EQ(stack,ISVREF(workstation,
					    (SI_Long)17L)))
					goto end_loop_2;
				    abort_current_workstation_context(Type_of_current_workstation_context);
				    goto next_loop_2;
				  end_loop_2:;
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
    goto next_loop;
  end_loop:;
    x = Nil;
    ab_loop_list_ = workstations_with_their_stacks;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    x = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_cons_1(x);
    goto next_loop_3;
  end_loop_3:
    reclaim_gensym_list_1(workstations_with_their_stacks);
    RESTORE_STACK();
    return VALUES_1(Qnil);
}

static Object Qg2_set_g2_state;    /* g2-set-g2-state */

static Object array_constant_33;   /* # */

/* PAUSE-FOR-INTERNAL-ERROR-OR-DEBUG */
Object pause_for_internal_error_or_debug(message_or_halt_info,debug_case_qm)
    Object message_or_halt_info, debug_case_qm;
{
    Object computation_instance_at_breakpoint, computation_frame_at_breakpoint;
    Object all_computation_instances_above_breakpoint;
    Object may_return_from_breakpoint;
    Object result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug;
    Object workstations_with_their_stacks, return_value, code;
    char temp;
    Declare_special(5);

    x_note_fn_call(129,98);
    system_pause(2,Kabort, !TRUEP(debug_case_qm) ? T : Nil);
    computation_instance_at_breakpoint = Current_computation_instance;
    PUSH_SPECIAL_WITH_SYMBOL(Computation_instance_at_breakpoint,Qcomputation_instance_at_breakpoint,computation_instance_at_breakpoint,
	    4);
      computation_frame_at_breakpoint = Current_computation_frame;
      PUSH_SPECIAL_WITH_SYMBOL(Computation_frame_at_breakpoint,Qcomputation_frame_at_breakpoint,computation_frame_at_breakpoint,
	      3);
	all_computation_instances_above_breakpoint = debug_case_qm ? 
		list_callers_of_computation_instance(Computation_instance_at_breakpoint) 
		: Nil;
	PUSH_SPECIAL_WITH_SYMBOL(All_computation_instances_above_breakpoint,Qall_computation_instances_above_breakpoint,all_computation_instances_above_breakpoint,
		2);
	  may_return_from_breakpoint = T;
	  PUSH_SPECIAL_WITH_SYMBOL(May_return_from_breakpoint,Qmay_return_from_breakpoint,may_return_from_breakpoint,
		  1);
	    result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug 
		    = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug,Qresult_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug,result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug,
		    0);
	      workstations_with_their_stacks = 
		      enter_dialog_for_pause_for_internal_error_or_debug(message_or_halt_info,
		      debug_case_qm);
	      return_value = run_scheduler_for_breakpoint();
	      leave_dialog_for_pause_for_internal_error_or_debug(workstations_with_their_stacks);
	      if (debug_case_qm) {
		  if (EQ(return_value,Qpause)) {
		      if (Computation_instance_at_breakpoint && 
			      Show_procedure_invocation_hierarchy_on_debugger_pause_p) 
				  {
			  code = M_CAR(M_CDR(Sparse_known_pathnames_list));
			  temp = FIXNUMP(code) ? (IFIX(code) & 
				  (SI_Long)512L) != (SI_Long)0L : TRUEP(Qnil);
			  if (temp);
			  else
			      temp = 
				      TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
			  if (temp);
			  else {
			      code = M_CAR(M_CDR(Redo_saved_changes));
			      temp = FIXNUMP(code) ? (IFIX(code) & 
				      (SI_Long)64L) != (SI_Long)0L : 
				      TRUEP(Qnil);
			      if (temp);
			      else
				  temp = 
					  TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
			      if (temp);
			      else
				  temp = TRUEP(SECOND(Old_eval_cons_list));
			  }
			  if (temp);
			  else {
			      code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
			      temp = FIXNUMP(code) ? (IFIX(code) & 
				      (SI_Long)1024L) != (SI_Long)0L : 
				      TRUEP(Qnil);
			      if (temp);
			      else
				  temp = 
					  TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
			  }
			  temp =  !temp;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  graph_detailed_procedures(3,Nil,Nil,
				  All_computation_instances_above_breakpoint);
		      return_value = run_scheduler_for_breakpoint();
		  }
		  reclaim_gensym_list_1(All_computation_instances_above_breakpoint);
		  All_computation_instances_above_breakpoint = Nil;
		  if (May_return_from_breakpoint)
		      validate_executing_statements_and_procedures();
		  system_resume();
		  if (CONSP(return_value) && EQ(CAR(return_value),
			  Qg2_set_g2_state)) {
		      return_from_g2_set_g2_state(CDR(return_value));
		      reclaim_eval_cons_1(return_value);
		  }
		  maybe_schedule_service_workstations(T);
		  if ( !TRUEP(May_return_from_breakpoint)) {
		      Current_computation_instance = Nil;
		      Current_schedule_task = Nil;
		      raw_stack_error_1(FIX((SI_Long)-1L),Qerror,
			      copy_constant_wide_string_given_length(array_constant_33,
			      FIX((SI_Long)56L)));
		  }
	      }
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* RECLAIM-STATUS-TABLE-FRAME-SERIAL-NUMBER-VALUE */
Object reclaim_status_table_frame_serial_number_value(fsn,gensymed_symbol)
    Object fsn, gensymed_symbol;
{
    x_note_fn_call(129,99);
    reclaim_frame_serial_number(fsn);
    return VALUES_1(Nil);
}

static Object Qchanging_mode;      /* changing-mode */

/* CHANGE-MODE */
Object change_mode()
{
    Object doing_password_change_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,100);
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)18L))) {
	doing_password_change_p = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Doing_password_change_p,Qdoing_password_change_p,doing_password_change_p,
		0);
	  result = enter_user_settings_editor(Qchanging_mode);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qpassword_change;    /* password-change */

/* ENTER-CHANGE-PASSWORD-DIALOG */
Object enter_change_password_dialog()
{
    Object doing_password_change_p;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,101);
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)18L))) {
	doing_password_change_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Doing_password_change_p,Qdoing_password_change_p,doing_password_change_p,
		0);
	  result = enter_user_settings_editor(Qpassword_change);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* COMPILE-NAME?-FOR-SLOT */
Object compile_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(129,102);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object string_constant_28;  /* "~a" */

/* TWRITE-LOGIN-FAILURE-TRANSLATION-SYMBOL */
Object twrite_login_failure_translation_symbol(symbol)
    Object symbol;
{
    Object string_1, temp, schar_arg_2, schar_new_value;
    SI_Long thing;

    x_note_fn_call(129,103);
    string_1 = string_for_localized_symbol(symbol);
    tformat(2,string_constant_28,string_1);
    if ( !TRUEP(sentence_end_punctuation_qm(string_1))) {
	if (EQ(Current_twriting_output_type,Qwide_string)) {
	    thing = (SI_Long)46L;
	    twrite_wide_character(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	}
	else {
	    if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		    Total_length_of_current_gensym_string))
		extend_current_gensym_string(0);
	    temp = Current_gensym_string;
	    schar_arg_2 = Fill_pointer_for_current_gensym_string;
	    thing = (SI_Long)46L;
	    schar_new_value = CODE_CHAR(CHARACTERP(FIX(thing)) ? 
		    CHAR_CODE(FIX(thing)) : FIX(thing));
	    SET_SCHAR(temp,schar_arg_2,schar_new_value);
	    temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	    Fill_pointer_for_current_gensym_string = temp;
	}
    }
    return reclaim_text_string(string_1);
}

static Object Qg2_login_prompt;    /* g2-login-prompt */

static Object string_constant_29;  /* "Please modify user settings." */

/* G2-LOGIN-PROMPT-MESSAGE */
Object g2_login_prompt_message()
{
    Object translation_qm, temp;

    x_note_fn_call(129,104);
    translation_qm = translation_for_symbol_qm(1,Qg2_login_prompt);
    temp = translation_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_29);
}

static Object Qg2_alias_prompt;    /* g2-alias-prompt */

static Object string_constant_30;  /* "Please enter user mode alias." */

/* G2-ALIAS-PROMPT-MESSAGE */
Object g2_alias_prompt_message()
{
    Object translation_qm, temp;

    x_note_fn_call(129,105);
    translation_qm = translation_for_symbol_qm(1,Qg2_alias_prompt);
    temp = translation_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_30);
}

static Object Qg2_password_change_prompt;  /* g2-password-change-prompt */

static Object string_constant_31;  /* "Change your password." */

/* G2-PASSWORD-CHANGE-PROMPT-MESSAGE */
Object g2_password_change_prompt_message()
{
    Object translation_qm, temp;

    x_note_fn_call(129,106);
    translation_qm = translation_for_symbol_qm(1,Qg2_password_change_prompt);
    temp = translation_qm;
    if (temp)
	return VALUES_1(temp);
    else
	return VALUES_1(string_constant_31);
}

static Object Qpassword_change_dialog;  /* password-change-dialog */

static Object Qsimple_message;     /* simple-message */

static Object string_constant_32;  /* "~a~%" */

static Object Qab_simple_condition;  /* simple-condition */

static Object Qg2_login_dialog;    /* g2-login-dialog */

static Object Qalias_creation;     /* alias-creation */

/* WRITE-G2-LOGIN-COMMENTS-FROM-SLOT */
Object write_g2_login_comments_from_slot(value,g2_login)
    Object value, g2_login;
{
    Object temp, current_localization_purpose_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(1);
    Object result;

    x_note_fn_call(129,107);
    SAVE_STACK();
    if (Doing_password_change_p) {
	LOCK(Localization_context);
	if (PUSH_UNWIND_PROTECT(1)) {
	    push_item_to_end_of_current_localization_domains(Qpassword_change_dialog);
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = Current_localization_purpose_qm;
		if (temp);
		else
		    temp = Qsimple_message;
		current_localization_purpose_qm = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
			0);
		  tformat(2,string_constant_32,
			  g2_password_change_prompt_message());
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(0);
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = Current_localization_purpose_qm;
		if (temp);
		else
		    temp = Qab_simple_condition;
		current_localization_purpose_qm = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
			0);
		  temp = value ? 
			  twrite_login_failure_translation_symbol(value) : Nil;
		POP_SPECIAL();
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    SAVE_VALUES(VALUES_1(result));
	    remove_last_item_in_current_localization_domains();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Localization_context);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	LOCK(Localization_context);
	if (PUSH_UNWIND_PROTECT(1)) {
	    push_item_to_end_of_current_localization_domains(Qg2_login_dialog);
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = Current_localization_purpose_qm;
		if (temp);
		else
		    temp = Qsimple_message;
		current_localization_purpose_qm = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
			0);
		  if (EQ(ISVREF(g2_login,(SI_Long)25L),Qalias_creation))
		      tformat(2,string_constant_32,g2_alias_prompt_message());
		  else
		      tformat(2,string_constant_32,g2_login_prompt_message());
		POP_SPECIAL();
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(0);
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(0)) {
		temp = Current_localization_purpose_qm;
		if (temp);
		else
		    temp = Qab_simple_condition;
		current_localization_purpose_qm = temp;
		PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
			0);
		  temp = value ? 
			  twrite_login_failure_translation_symbol(value) : Nil;
		POP_SPECIAL();
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    SAVE_VALUES(VALUES_1(result));
	    remove_last_item_in_current_localization_domains();
	}
	POP_UNWIND_PROTECT(1);
	UNLOCK(Localization_context);
	CONTINUE_UNWINDING(1);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
}

Object The_type_description_of_g2_login_state = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_g2_login_states, Qchain_of_available_g2_login_states);

DEFINE_VARIABLE_WITH_SYMBOL(G2_login_state_count, Qg2_login_state_count);

Object Chain_of_available_g2_login_states_vector = UNBOUND;

/* G2-LOGIN-STATE-STRUCTURE-MEMORY-USAGE */
Object g2_login_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(129,108);
    temp = G2_login_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-G2-LOGIN-STATE-COUNT */
Object outstanding_g2_login_state_count()
{
    Object def_structure_g2_login_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(129,109);
    gensymed_symbol = IFIX(G2_login_state_count);
    def_structure_g2_login_state_variable = Chain_of_available_g2_login_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_g2_login_state_variable))
	goto end_loop;
    def_structure_g2_login_state_variable = 
	    ISVREF(def_structure_g2_login_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-G2-LOGIN-STATE-1 */
Object reclaim_g2_login_state_1(g2_login_state)
    Object g2_login_state;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(129,110);
    inline_note_reclaim_cons(g2_login_state,Nil);
    structure_being_reclaimed = g2_login_state;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      release_mouse_pointers(ISVREF(g2_login_state,(SI_Long)1L));
      SVREF(g2_login_state,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(g2_login_state,(SI_Long)2L));
      SVREF(g2_login_state,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_g2_login_states_vector,
	    IFIX(Current_thread_index));
    SVREF(g2_login_state,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_g2_login_states_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = g2_login_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-G2-LOGIN-STATE */
Object reclaim_structure_for_g2_login_state(g2_login_state)
    Object g2_login_state;
{
    x_note_fn_call(129,111);
    return reclaim_g2_login_state_1(g2_login_state);
}

static Object Qg2_defstruct_structure_name_g2_login_state_g2_struct;  /* g2-defstruct-structure-name::g2-login-state-g2-struct */

/* MAKE-PERMANENT-G2-LOGIN-STATE-STRUCTURE-INTERNAL */
Object make_permanent_g2_login_state_structure_internal()
{
    Object def_structure_g2_login_state_variable;
    Object defstruct_g2_g2_login_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(129,112);
    def_structure_g2_login_state_variable = Nil;
    atomic_incff_symval(Qg2_login_state_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_g2_login_state_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_g2_login_state_variable = the_array;
	SVREF(defstruct_g2_g2_login_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_g2_login_state_g2_struct;
	SVREF(defstruct_g2_g2_login_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_g2_login_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_g2_login_state_variable = 
		defstruct_g2_g2_login_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_g2_login_state_variable);
}

/* MAKE-G2-LOGIN-STATE-1 */
Object make_g2_login_state_1(g2_login,g2_login_table,g2_login_workspace,
	    image_plane_with_g2_login_workspace,g2_login_subcommand_menu)
    Object g2_login, g2_login_table, g2_login_workspace;
    Object image_plane_with_g2_login_workspace, g2_login_subcommand_menu;
{
    Object def_structure_g2_login_state_variable, temp, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(129,113);
    def_structure_g2_login_state_variable = 
	    ISVREF(Chain_of_available_g2_login_states_vector,
	    IFIX(Current_thread_index));
    if (def_structure_g2_login_state_variable) {
	temp = Chain_of_available_g2_login_states_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_g2_login_state_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_g2_login_state_g2_struct;
    }
    else
	def_structure_g2_login_state_variable = 
		make_permanent_g2_login_state_structure_internal();
    inline_note_allocate_cons(def_structure_g2_login_state_variable,Nil);
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)3L)) = g2_login;
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)4L)) = 
	    g2_login_table;
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)5L)) = 
	    g2_login_workspace;
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)6L)) = 
	    image_plane_with_g2_login_workspace;
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)7L)) = 
	    g2_login_subcommand_menu;
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)1L)) = Nil;
    temp = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_g2_login_state_variable,FIX((SI_Long)2L)) = temp;
    return VALUES_1(def_structure_g2_login_state_variable);
}

static Object Qlogged_in;          /* logged-in */

static Object Qchanging_kbs;       /* changing-kbs */

/* CLEAN-UP-WORKSTATION-CONTEXT-FOR-G2-LOGIN-STATE */
Object clean_up_workstation_context_for_g2_login_state(g2_login_state)
    Object g2_login_state;
{
    Object svref_arg_1, gensymed_symbol, x, y, xa, ya, gensymed_symbol_1;
    char temp;

    x_note_fn_call(129,114);
    if (native_login_dialog_p(Current_workstation_window))
	cancel_native_login_dialog(Current_workstation_window);
    if ( !EQ(Qlogged_in,ISVREF(Current_workstation,(SI_Long)28L))) {
	if (ISVREF(Current_workstation,(SI_Long)18L))
	    log_out_workstation(Current_workstation);
	else {
	    svref_arg_1 = Current_workstation;
	    SVREF(svref_arg_1,FIX((SI_Long)28L)) = Qchanging_kbs;
	}
    }
    gensymed_symbol = ISVREF(ISVREF(g2_login_state,(SI_Long)3L),(SI_Long)3L);
    x = ISVREF(g2_login_state,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(g2_login_state,(SI_Long)2L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp)
	delete_frame(ISVREF(g2_login_state,(SI_Long)3L));
    gensymed_symbol = ISVREF(ISVREF(g2_login_state,(SI_Long)5L),(SI_Long)3L);
    x = ISVREF(g2_login_state,(SI_Long)5L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(g2_login_state,(SI_Long)2L);
	if (FIXNUMP(y))
	    temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	else if (FIXNUMP(x))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(y);
	    ya = M_CAR(x);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    if ( !temp)
	delete_frame(ISVREF(g2_login_state,(SI_Long)5L));
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_g2_login_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)1L);
    gensymed_symbol_1 = g2_login_state;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_restrictions, Qkb_restrictions);

static Object Qg2_login;           /* g2-login */

static Object list_constant_6;     /* # */

static Object Qinitial_g2_user_mode_for_this_kb;  /* initial-g2-user-mode-for-this-kb */

static Object Qadministrator;      /* administrator */

static Object Qreloading;          /* reloading */

static Object Qg2_window;          /* g2-window */

static Object Qg2_login_comments;  /* g2-login-comments */

static Object Qnew_password_must_be_at_least_4_characters_long;  /* new-password-must-be-at-least-4-characters-long */

/* ENTER-USER-SETTINGS-EDITOR */
Object enter_user_settings_editor(how_entered)
    Object how_entered;
{
    Object g2_login, default_mode_for_this_kb, svref_arg_1, svref_new_value_1;
    Object no_need_to_edit_qm, reason_for_failure, temp, g2_login_state;
    SI_Long svref_new_value;
    char password_change_case_qm, modal_case_qm;
    Declare_stack_pointer;
    Declare_catch(2);
    Object result;

    x_note_fn_call(129,115);
    SAVE_STACK();
    g2_login = make_frame(Qg2_login);
    svref_new_value = IFIX(ISVREF(g2_login,(SI_Long)5L)) | (SI_Long)524288L;
    ISVREF(g2_login,(SI_Long)5L) = FIX(svref_new_value);
    password_change_case_qm = EQ(how_entered,Qpassword_change);
    modal_case_qm =  !TRUEP(memq_function(how_entered,list_constant_6));
    ISVREF(g2_login,(SI_Long)25L) = how_entered;
    default_mode_for_this_kb = get_slot_value_function(Kb_restrictions,
	    Qinitial_g2_user_mode_for_this_kb,Nil);
    if (default_mode_for_this_kb);
    else
	default_mode_for_this_kb = Qadministrator;
    svref_arg_1 = Current_workstation;
    svref_new_value_1 = EQ(Qreloading,how_entered) &&  
	    !TRUEP(Relations_tag_list) ? default_mode_for_this_kb : Nil;
    if (svref_new_value_1);
    else
	svref_new_value_1 = Current_g2_user_mode_qm;
    if (svref_new_value_1);
    else
	svref_new_value_1 = default_mode_for_this_kb;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = svref_new_value_1;
    if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)23L))) {
	svref_arg_1 = Current_workstation;
	SVREF(svref_arg_1,FIX((SI_Long)23L)) = Qg2_window;
    }
    set_session_info_in_g2_login(Current_workstation,g2_login);
    if ( !TRUEP(memq_function(how_entered,list_constant_6)))
	result = finish_g2_login(g2_login,Current_workstation,
		modal_case_qm ? T : Nil);
    else
	result = VALUES_1(Nil);
    MVS_2(result,no_need_to_edit_qm,reason_for_failure);
    if (no_need_to_edit_qm) {
	delete_frame(g2_login);
	RESTORE_STACK();
	return VALUES_1(T);
    }
    else {
	if ( !TRUEP(reason_for_failure) && password_change_case_qm)
	    change_slot_value(3,g2_login,Qg2_login_comments,
		    Qnew_password_must_be_at_least_4_characters_long);
	else {
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(g2_login,Qg2_login_comments);
	    set_lookup_slot_value_1(g2_login,Qg2_login_comments,
		    reason_for_failure);
	}
	if (Doing_password_change_p) {
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(1)) {
		push_item_to_end_of_current_localization_domains(Qpassword_change_dialog);
		LOCK(Localization_context);
		if (PUSH_UNWIND_PROTECT(0)) {
		    push_item_to_end_of_current_localization_domains(Qpassword_change);
		    temp = enter_context_in_current_workstation(3,
			    Qg2_login,make_user_settings_editor_state(3,
			    g2_login,modal_case_qm ? T : Nil,
			    password_change_case_qm ? T : Nil),
			    modal_case_qm ? T : Nil);
		    remove_last_item_in_current_localization_domains();
		    SAVE_VALUES(VALUES_1(temp));
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Localization_context);
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		SAVE_VALUES(VALUES_1(result));
		remove_last_item_in_current_localization_domains();
	    }
	    POP_UNWIND_PROTECT(1);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(1);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
	else {
	    LOCK(Localization_context);
	    if (PUSH_UNWIND_PROTECT(1)) {
		push_item_to_end_of_current_localization_domains(Qg2_login_dialog);
		LOCK(Localization_context);
		if (PUSH_UNWIND_PROTECT(0)) {
		    push_item_to_end_of_current_localization_domains(Qg2_login);
		    g2_login_state = make_user_settings_editor_state(4,
			    g2_login,modal_case_qm ? T : Nil,
			    password_change_case_qm ? T : Nil,
			    EQ(how_entered,Qalias_creation) ? T : Nil);
		    temp = enter_user_settings_editor_1(1,g2_login_state);
		    remove_last_item_in_current_localization_domains();
		    SAVE_VALUES(VALUES_1(temp));
		}
		POP_UNWIND_PROTECT(0);
		UNLOCK(Localization_context);
		CONTINUE_UNWINDING(0);
		result = RESTORE_VALUES();
		SAVE_VALUES(VALUES_1(result));
		remove_last_item_in_current_localization_domains();
	    }
	    POP_UNWIND_PROTECT(1);
	    UNLOCK(Localization_context);
	    CONTINUE_UNWINDING(1);
	    result = RESTORE_VALUES();
	    RESTORE_STACK();
	    return result;
	}
    }
}

/* ENTER-CHANGE-USER-MODE-IN-RUNNING */
Object enter_change_user_mode_in_running(how_entered,workstation)
    Object how_entered, workstation;
{
    Object g2_login, default_mode_for_this_kb, svref_new_value_1, temp;
    Object no_need_to_edit_qm;
    SI_Long svref_new_value;

    x_note_fn_call(129,116);
    g2_login = make_frame(Qg2_login);
    svref_new_value = IFIX(ISVREF(g2_login,(SI_Long)5L)) | (SI_Long)524288L;
    ISVREF(g2_login,(SI_Long)5L) = FIX(svref_new_value);
    ISVREF(g2_login,(SI_Long)25L) = how_entered;
    default_mode_for_this_kb = get_slot_value_function(Kb_restrictions,
	    Qinitial_g2_user_mode_for_this_kb,Nil);
    if (default_mode_for_this_kb);
    else
	default_mode_for_this_kb = Qadministrator;
    svref_new_value_1 = EQ(how_entered,Qreloading) &&  
	    !TRUEP(Relations_tag_list) ? default_mode_for_this_kb : Nil;
    if (svref_new_value_1);
    else
	svref_new_value_1 = ISVREF(workstation,(SI_Long)19L);
    if (svref_new_value_1);
    else
	svref_new_value_1 = default_mode_for_this_kb;
    SVREF(workstation,FIX((SI_Long)19L)) = svref_new_value_1;
    if ( !TRUEP(ISVREF(workstation,(SI_Long)23L)))
	SVREF(workstation,FIX((SI_Long)23L)) = Qg2_window;
    set_session_info_in_g2_login(workstation,g2_login);
    temp =  !TRUEP(memq_function(how_entered,list_constant_6)) ? 
	    finish_g2_login(g2_login,workstation,T) : Nil;
    no_need_to_edit_qm = temp;
    if (no_need_to_edit_qm) {
	delete_frame(g2_login);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qattribute;          /* attribute */

static Object Qcenter;             /* center */

static Object Qtop;                /* top */

/* ENTER-USER-SETTINGS-EDITOR-1 */
Object enter_user_settings_editor_1 varargs_1(int, n)
{
    Object g2_login_state;
    Object image_plane_qm, temp, current_localization_purpose_qm;
    Object svref_new_value;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(129,117);
    INIT_ARGS_nonrelocating();
    g2_login_state = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    image_plane_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (native_login_dialog_p(Current_workstation_window)) {
	LOCK(Localization_context);
	if (PUSH_UNWIND_PROTECT(0)) {
	    temp = Current_localization_purpose_qm;
	    if (temp);
	    else
		temp = Qattribute;
	    current_localization_purpose_qm = temp;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_localization_purpose_qm,Qcurrent_localization_purpose_qm,current_localization_purpose_qm,
		    0);
	      post_native_login_dialog(1,g2_login_state);
	    POP_SPECIAL();
	}
	POP_UNWIND_PROTECT(0);
	UNLOCK(Localization_context);
	CONTINUE_UNWINDING(0);
    }
    else {
	svref_new_value = image_plane_qm;
	if (svref_new_value);
	else
	    svref_new_value = 
		    put_workspace_on_pane_function(ISVREF(g2_login_state,
		    (SI_Long)5L),Current_workstation_detail_pane,Qcenter,
		    Qtop,Nil,FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
	SVREF(g2_login_state,FIX((SI_Long)6L)) = svref_new_value;
    }
    result = enter_context_in_current_workstation(3,Qg2_login,
	    g2_login_state, 
	    !TRUEP(memq_function(ISVREF(ISVREF(g2_login_state,(SI_Long)3L),
	    (SI_Long)25L),list_constant_6)) ? T : Nil);
    RESTORE_STACK();
    return result;
}

static Object Quser_settings_editor_workspace;  /* user-settings-editor-workspace */

static Object Qg2_login_user_name_qm;  /* g2-login-user-name? */

static Object Qdisconnect;         /* disconnect */

static Object Qend;                /* end */

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object string_constant_33;  /* "User Mode Alias Creation" */

static Object string_constant_34;  /* "User Settings Editor" */

/* MAKE-USER-SETTINGS-EDITOR-STATE */
Object make_user_settings_editor_state varargs_1(int, n)
{
    Object g2_login, modal_case_qm, password_change_case_qm;
    Object alias_creation_qm, g2_login_workspace, workspace_margin;
    Object g2_login_table, g2_login_subcommand_menu, gensymed_symbol, temp;
    Object cancel_or_disconnect_qm, image_plane_with_g2_login_workspace;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(129,118);
    INIT_ARGS_nonrelocating();
    g2_login = REQUIRED_ARG_nonrelocating();
    modal_case_qm = REQUIRED_ARG_nonrelocating();
    password_change_case_qm = REQUIRED_ARG_nonrelocating();
    alias_creation_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    g2_login_workspace = make_workspace(4,Quser_settings_editor_workspace,
	    Nil,Nil,FIX((SI_Long)10L));
    workspace_margin = ISVREF(g2_login_workspace,(SI_Long)17L);
    if (alias_creation_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(g2_login,Qg2_login_user_name_qm);
	set_lookup_slot_value_1(g2_login,Qg2_login_user_name_qm,Nil);
	g2_login_table = make_alias_creation_attribute_table(g2_login);
    }
    else
	g2_login_table = password_change_case_qm ? 
		make_password_change_attributes_table(g2_login) : 
		make_g2_login_attributes_table(g2_login);
    g2_login_subcommand_menu = make_subcommand_menu(1,
	    slot_value_list_3(Qcancel,Qdisconnect,Qend));
    if (New_g2_classic_ui_p) {
	change_slot_value(3,g2_login_workspace,
		Qworkspace_background_color_qm,get_ui_parameter(1,
		Qsystem_workspace_background_color));
	change_slot_value(3,g2_login_workspace,Qtitle_bar_caption_text,
		convert_text_string_to_text(alias_creation_qm ? 
		copy_text_string(string_constant_33) : 
		copy_text_string(string_constant_34)));
    }
    gensymed_symbol = ISVREF(g2_login_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(g2_login_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    add_to_workspace(4,g2_login_subcommand_menu,g2_login_workspace,temp,
	    FIX(gensymed_symbol_1 + gensymed_symbol_2));
    gensymed_symbol = ISVREF(g2_login_subcommand_menu,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    gensymed_symbol = ISVREF(g2_login_subcommand_menu,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    add_to_workspace(4,g2_login_table,g2_login_workspace,temp,gensymed_symbol);
    enable_or_disable_subcommand(3,g2_login_subcommand_menu,Qend,Nil);
    cancel_or_disconnect_qm = modal_case_qm ? 
	    (EQ(Current_workstation_window,System_window) ? Nil : 
	    Qdisconnect) : Qcancel;
    enable_or_disable_subcommand(3,g2_login_subcommand_menu,Qcancel, 
	    !EQ(cancel_or_disconnect_qm,Qcancel) ? T : Nil);
    enable_or_disable_subcommand(3,g2_login_subcommand_menu,Qdisconnect, 
	    !EQ(cancel_or_disconnect_qm,Qdisconnect) ? T : Nil);
    if (password_change_case_qm) {
	image_plane_with_g2_login_workspace = 
		put_workspace_on_pane_function(g2_login_workspace,
		Current_workstation_detail_pane,Qcenter,Qtop,Nil,
		FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
	return make_g2_login_state_1(g2_login,g2_login_table,
		g2_login_workspace,image_plane_with_g2_login_workspace,
		g2_login_subcommand_menu);
    }
    else
	return make_g2_login_state_1(g2_login,g2_login_table,
		g2_login_workspace,Nil,g2_login_subcommand_menu);
}

Object G2_login_attributes_to_show = UNBOUND;

/* MAKE-G2-LOGIN-ATTRIBUTES-TABLE */
Object make_g2_login_attributes_table(g2_login)
    Object g2_login;
{
    x_note_fn_call(129,119);
    return make_attributes_table(6,g2_login,Nil,Nil,Nil,Nil,
	    G2_login_attributes_to_show);
}

Object Alias_creation_attributes_to_show = UNBOUND;

/* MAKE-ALIAS-CREATION-ATTRIBUTE-TABLE */
Object make_alias_creation_attribute_table(g2_login)
    Object g2_login;
{
    x_note_fn_call(129,120);
    return make_attributes_table(6,g2_login,Nil,Nil,Nil,Nil,
	    Alias_creation_attributes_to_show);
}

Object Password_change_attributes_to_show = UNBOUND;

/* MAKE-PASSWORD-CHANGE-ATTRIBUTES-TABLE */
Object make_password_change_attributes_table(g2_login)
    Object g2_login;
{
    x_note_fn_call(129,121);
    return make_attributes_table(6,g2_login,Nil,Nil,Nil,Nil,
	    Password_change_attributes_to_show);
}

/* VALID-WORKSTATION-CONTEXT-P-FOR-G2-LOGIN-STATE */
Object valid_workstation_context_p_for_g2_login_state(g2_login_state)
    Object g2_login_state;
{
    Object gensymed_symbol, gensymed_symbol_1, x, y, xa, ya;
    char temp;

    x_note_fn_call(129,122);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_g2_login_state,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)4L);
    gensymed_symbol_1 = g2_login_state;
    if (inline_funcall_1(gensymed_symbol,gensymed_symbol_1)) {
	gensymed_symbol = ISVREF(ISVREF(g2_login_state,(SI_Long)3L),
		(SI_Long)3L);
	x = ISVREF(g2_login_state,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(g2_login_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(g2_login_state,(SI_Long)4L),
		(SI_Long)3L);
	x = ISVREF(g2_login_state,(SI_Long)4L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(g2_login_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(ISVREF(g2_login_state,(SI_Long)5L),
		(SI_Long)3L);
	x = ISVREF(g2_login_state,(SI_Long)5L);
	temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(g2_login_state,(SI_Long)2L);
	    if (FIXNUMP(y))
		temp = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
	    else if (FIXNUMP(x))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(y);
		ya = M_CAR(x);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	return VALUES_1( !temp ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* ENTER-KEYS-IN-G2-LOGIN-STATE */
Object enter_keys_in_g2_login_state(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(129,123);
    return do_end_button_for_g2_login();
}

static Object Quser_password;      /* user-password */

/* MOUSE-DOWN-ON-ATTRIBUTE-VALUE-IN-G2-LOGIN-STATE */
Object mouse_down_on_attribute_value_in_g2_login_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1, image_plane, g2_login_state, text_cell;
    Object g2_login_qm, slot_name_qm, type_of_slot_qm;
    Object user_password_editing_case_qm, specific_format_qm;
    Object result;

    x_note_fn_call(129,124);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    g2_login_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    text_cell = text_cell_of_table_blackboard_function(mouse_pointer);
    if (mouse_pointer_1 && image_plane && g2_login_state && text_cell) {
	if (EQ(image_plane,ISVREF(g2_login_state,(SI_Long)6L))) {
	    result = get_slot_represented_by_text_cell_if_any(text_cell);
	    MVS_2(result,g2_login_qm,slot_name_qm);
	    if (slot_name_qm) {
		if ( !(EQ(slot_name_qm,Qg2_login_comments) || 
			EQ(ISVREF(g2_login_qm,(SI_Long)25L),
			Qpassword_change) && EQ(slot_name_qm,
			Qg2_login_user_name_qm))) {
		    type_of_slot_qm = type_of_slot_if_editable(2,
			    ISVREF(ISVREF(g2_login_qm,(SI_Long)1L),
			    (SI_Long)1L),slot_name_qm);
		    user_password_editing_case_qm = type_of_slot_qm ? 
			    (EQ(SECOND(type_of_slot_qm),Quser_password) ? 
			    T : Nil) : Qnil;
		    specific_format_qm = user_password_editing_case_qm ? 
			    create_blob_edit_box_format() : Nil;
		    return enter_editing_context(5,g2_login_qm,
			    slot_name_qm,user_password_editing_case_qm ? 
			    make_empty_text() : Nil,Nil,specific_format_qm);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else
	    return mouse_down_on_otherwise_in_g2_login_state(mouse_pointer_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qdo_g2_login_subcommand;  /* do-g2-login-subcommand */

/* MOUSE-DOWN-ON-SUBCOMMAND-MENU-BUTTON-IN-G2-LOGIN-STATE */
Object mouse_down_on_subcommand_menu_button_in_g2_login_state(mouse_pointer)
    Object mouse_pointer;
{
    Object g2_login_state, image_plane, mouse_pointer_1;

    x_note_fn_call(129,125);
    g2_login_state = 
	    workstation_context_specifics_blackboard_function(mouse_pointer);
    image_plane = image_plane_blackboard_function(mouse_pointer);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (g2_login_state && image_plane && mouse_pointer_1) {
	if (EQ(image_plane,ISVREF(g2_login_state,(SI_Long)6L))) {
	    establish_next_workstation_context_continuation(Qdo_g2_login_subcommand,
		    Nil,Nil,Nil);
	    return enter_subcommand_context(mouse_pointer_1);
	}
	else
	    return mouse_down_on_otherwise_in_g2_login_state(mouse_pointer_1);
    }
    else
	return VALUES_1(Nil);
}

/* MOUSE-DOWN-ON-OTHERWISE-IN-G2-LOGIN-STATE */
Object mouse_down_on_otherwise_in_g2_login_state(mouse_pointer)
    Object mouse_pointer;
{
    Object mouse_pointer_1;

    x_note_fn_call(129,126);
    mouse_pointer_1 = mouse_pointer_blackboard_function(mouse_pointer);
    if (mouse_pointer_1) {
	if ( !TRUEP(ISVREF(Current_workstation,(SI_Long)18L)))
	    return run_top_level_event_handler(mouse_pointer_1);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* DO-G2-LOGIN-SUBCOMMAND */
Object do_g2_login_subcommand(workstation_context)
    Object workstation_context;
{
    Object subcommand_menu_or_error_code, button_info;

    x_note_fn_call(129,127);
    subcommand_menu_or_error_code = ISVREF(Current_workstation,(SI_Long)33L);
    button_info = ISVREF(Current_workstation,(SI_Long)34L);
    if ( !EQ(Kabort,subcommand_menu_or_error_code))
	return do_g2_login_button(button_info);
    else
	return VALUES_1(Nil);
}

/* DO-G2-LOGIN-BUTTON */
Object do_g2_login_button(button)
    Object button;
{
    x_note_fn_call(129,128);
    if (EQ(button,Qend))
	return do_end_button_for_g2_login();
    else if (EQ(button,Qcancel))
	return abort_current_workstation_context(Qg2_login);
    else if (EQ(button,Qdisconnect)) {
	abort_current_workstation_context(Qg2_login);
	return close_telewindows_connection(Current_workstation_window);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qg2_login_user_mode;  /* g2-login-user-mode */

static Object string_constant_35;  /* "Can not choose user mode to non-existend user mode" */

static Object Qduplicate_new_password_required;  /* duplicate-new-password-required */

static Object string_constant_36;  /* "Sorry, but parent user mode for this alias is incorrect." */

/* DO-END-BUTTON-FOR-G2-LOGIN */
Object do_end_button_for_g2_login()
{
    Object g2_login_state, g2_login, how_entered, frame_reference, temp;
    Object success_qm, reason_for_failure, gensymed_symbol, xa, ya, temp_2;
    char temp_1;
    Object result;

    x_note_fn_call(129,129);
    g2_login_state = Specific_structure_for_current_workstation_context;
    g2_login = ISVREF(g2_login_state,(SI_Long)3L);
    how_entered = ISVREF(g2_login,(SI_Long)25L);
    frame_reference = Current_frame_serial_number;
    if ( 
	    !TRUEP(is_user_mode_present(get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_mode,Nil)))) {
	notify_user(2,string_constant_28,string_constant_35);
	return VALUES_2(Nil,Nil);
    }
    if (EQ(how_entered,Qpassword_change)) {
	if ( !TRUEP(ISVREF(g2_login,(SI_Long)30L)))
	    result = VALUES_2(Nil,Qduplicate_new_password_required);
	else {
	    temp = get_lookup_slot_value_given_default(g2_login,
		    Qg2_login_user_name_qm,Nil);
	    result = encode_and_check_password_change_information(4,temp,
		    ISVREF(g2_login,(SI_Long)26L),ISVREF(g2_login,
		    (SI_Long)28L),ISVREF(g2_login,(SI_Long)30L));
	}
    }
    else if (EQ(how_entered,Qalias_creation)) {
	if (is_user_mode_present(get_lookup_slot_value_given_default(g2_login,
		Qg2_login_user_mode,Nil))) {
	    if (check_alias_for_possible_name(get_lookup_slot_value_given_default(g2_login,
		    Qg2_login_user_name_qm,Nil)))
		result = make_new_alias(g2_login);
	    else
		result = VALUES_1(Nil);
	}
	else
	    result = notify_user(1,string_constant_36);
    }
    else
	result = finish_g2_login(g2_login,Current_workstation,
		EQ(ISVREF(Current_workstation,(SI_Long)18L),Qg2_login) ? T 
		: Nil);
    MVS_2(result,success_qm,reason_for_failure);
    gensymed_symbol = ISVREF(g2_login,(SI_Long)3L);
    temp_1 = SIMPLE_VECTOR_P(g2_login) ? EQ(ISVREF(g2_login,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp_1);
    else
	temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp_1);
    else if (FIXNUMP(frame_reference))
	temp_1 = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_reference,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp_1 = TRUEP(Nil);
    else {
	xa = M_CAR(frame_reference);
	ya = M_CAR(gensymed_symbol);
	temp_1 = FIXNUM_LT(xa,ya);
	if (temp_1);
	else
	    temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_reference),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if (temp_1) {
	abort_g2(0);
	return VALUES_1(Nil);
    }
    else if (success_qm)
	return return_from_current_workstation_context(1,Qg2_login);
    else {
	change_slot_value(3,g2_login,Qg2_login_comments,reason_for_failure);
	enable_or_disable_subcommand(3,ISVREF(g2_login_state,(SI_Long)7L),
		Qend,Nil);
	if (too_many_login_attempts_from_this_source(g2_login) && 
		ISVREF(Current_workstation,(SI_Long)18L) &&  
		!EQ(Current_workstation_window,System_window) && 
		EQ(ISVREF(Current_workstation_window,(SI_Long)1L),Qicp)) {
	    temp = Current_workstation;
	    temp_2 = get_lookup_slot_value_given_default(g2_login,
		    Qg2_login_user_name_qm,Nil);
	    notice_tw_disconnect(temp,temp_2,
		    get_lookup_slot_value_given_default(g2_login,
		    Qg2_login_user_mode,Nil));
	    abort_current_workstation_context(Qg2_login);
	    return close_telewindows_connection(Current_workstation_window);
	}
	else
	    return VALUES_1(Nil);
    }
}

Object Maximum_number_of_login_attempts_permitted_per_window = UNBOUND;

static Object Qg2_login_attempts_counter;  /* g2-login-attempts-counter */

static Object Qg2_defstruct_structure_name_t2_nonce_data_g2_struct;  /* g2-defstruct-structure-name::t2-nonce-data-g2-struct */

/* TOO-MANY-LOGIN-ATTEMPTS-FROM-THIS-SOURCE */
Object too_many_login_attempts_from_this_source(source)
    Object source;
{
    Object x2, sub_class_bit_vector, g2_login_attempts_counter_new_value;
    Object number_of_attempts;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(129,130);
    if (Relations_tag_list) {
	if (SIMPLE_VECTOR_P(source) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(source)) > (SI_Long)2L &&  
		!EQ(ISVREF(source,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(source,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(source,(SI_Long)1L),
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
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    g2_login_attempts_counter_new_value = 
		    FIXNUM_ADD1(get_lookup_slot_value_given_default(source,
		    Qg2_login_attempts_counter,FIX((SI_Long)0L)));
	    number_of_attempts = set_non_savable_lookup_slot_value(source,
		    Qg2_login_attempts_counter,
		    g2_login_attempts_counter_new_value);
	}
	else if (SIMPLE_VECTOR_P(source) && EQ(ISVREF(source,(SI_Long)0L),
		Qg2_defstruct_structure_name_t2_nonce_data_g2_struct)) {
	    number_of_attempts = FIXNUM_ADD1(ISVREF(source,(SI_Long)4L));
	    SVREF(source,FIX((SI_Long)4L)) = number_of_attempts;
	}
	else
	    number_of_attempts = 
		    FIXNUM_ADD1(Maximum_number_of_login_attempts_permitted_per_window);
	return VALUES_1(FIXNUM_GE(number_of_attempts,
		Maximum_number_of_login_attempts_permitted_per_window) ? T 
		: Nil);
    }
    else
	return VALUES_1(Nil);
}

/* G2-SET-MAXIMUM-LOGIN-ATTEMPTS */
Object g2_set_maximum_login_attempts(number_as_evaluation_value)
    Object number_as_evaluation_value;
{
    Object number, value_1, prior_value;

    x_note_fn_call(129,131);
    number = number_as_evaluation_value;
    value_1 = Nil;
    prior_value = Maximum_number_of_login_attempts_permitted_per_window;
    Maximum_number_of_login_attempts_permitted_per_window = number;
    value_1 = prior_value;
    return VALUES_1(value_1);
}

static Object Qg2_login_user_password_qm;  /* g2-login-user-password? */

static Object Quser_mode;          /* user-mode */

static Object Qlanguage;           /* language */

static Object Qwindow_style;       /* window-style */

/* FINISH-G2-LOGIN */
Object finish_g2_login(g2_login,workstation,modal_case_qm)
    Object g2_login, workstation, modal_case_qm;
{
    Object temp, temp_1, svref_new_value, temp_2, temp_3, user_settings_plist;

    x_note_fn_call(129,132);
    temp = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_name_qm,Nil);
    temp_1 = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_password_qm,Nil);
    svref_new_value = encode_password_via_md5(temp,temp_1,ISVREF(g2_login,
	    (SI_Long)24L));
    ISVREF(g2_login,(SI_Long)24L) = svref_new_value;
    if ( !TRUEP(ISVREF(workstation,(SI_Long)22L))) {
	temp_2 = get_lookup_slot_value_given_default(g2_login,
		Qg2_login_user_name_qm,Nil) ? gensym_list_2(Quser_name,
		stringw(get_lookup_slot_value_given_default(g2_login,
		Qg2_login_user_name_qm,Nil))) : Nil;
	temp_3 = ISVREF(g2_login,(SI_Long)24L) ? 
		gensym_list_2(Qmd5_password,stringw(ISVREF(g2_login,
		(SI_Long)24L))) : Nil;
	temp = get_lookup_slot_value_given_default(g2_login,
		Qg2_login_user_mode,Nil) ? gensym_list_2(Quser_mode,
		stringw(get_lookup_slot_value_given_default(g2_login,
		Qg2_login_user_mode,Nil))) : Nil;
	temp_1 = ISVREF(g2_login,(SI_Long)21L) ? gensym_list_2(Qlanguage,
		stringw(ISVREF(g2_login,(SI_Long)21L))) : Nil;
	user_settings_plist = nconc2(temp_2,nconc2(temp_3,nconc2(temp,
		nconc2(temp_1,ISVREF(g2_login,(SI_Long)22L) ? 
		gensym_list_2(Qwindow_style,stringw(ISVREF(g2_login,
		(SI_Long)22L))) : Nil))));
	offer_g2_user_settings_back_to_telewindows(workstation,
		user_settings_plist);
	reclaim_gensym_list_1(user_settings_plist);
    }
    temp_3 = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_name_qm,Nil);
    temp = ISVREF(g2_login,(SI_Long)24L);
    temp_1 = get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_mode,Nil);
    return log_in_workstation(8,workstation,temp_3,temp,temp_1,
	    ISVREF(g2_login,(SI_Long)20L),modal_case_qm,ISVREF(g2_login,
	    (SI_Long)21L),ISVREF(g2_login,(SI_Long)22L));
}

/* ENCODE-AND-CHECK-PASSWORD-CHANGE-INFORMATION */
Object encode_and_check_password_change_information varargs_1(int, n)
{
    Object user_name, clear_old_password, clear_new_password_1;
    Object clear_new_password_2_qm, encoded_old_password;
    Object encoded_new_password_1, encoded_new_password_2_qm, result_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(129,133);
    INIT_ARGS_nonrelocating();
    user_name = REQUIRED_ARG_nonrelocating();
    clear_old_password = REQUIRED_ARG_nonrelocating();
    clear_new_password_1 = REQUIRED_ARG_nonrelocating();
    clear_new_password_2_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    encoded_old_password = encode_password_via_md5(user_name,
	    clear_old_password,Nil);
    encoded_new_password_1 = encode_password_via_md5(user_name,
	    clear_new_password_1,Nil);
    encoded_new_password_2_qm = clear_new_password_2_qm ? 
	    encode_password_via_md5(user_name,clear_new_password_2_qm,Nil) 
	    : Nil;
    if (SYMBOLP(clear_old_password))
	clear_old_password = symbol_namew(clear_old_password);
    if (SYMBOLP(clear_new_password_1))
	clear_new_password_1 = symbol_namew(clear_new_password_1);
    result_1 = change_user_password_if_appropriate(user_name,
	    encoded_old_password,clear_old_password,clear_new_password_1,
	    encoded_new_password_1,encoded_new_password_2_qm);
    return VALUES_2( !TRUEP(result_1) ? T : Nil,result_1);
}

/* VALID-PASSWORD-CHARACTERS-P */
Object valid_password_characters_p(password_string)
    Object password_string;
{
    Object character_1, gensymed_symbol;
    SI_Long i, length_1, ab_loop_bind_;

    x_note_fn_call(129,134);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(password_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(password_string,length_1 - 
	    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(password_string,length_1 - 
	    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L);
    character_1 = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    character_1 = FIX(UBYTE_16_ISAREF_1(password_string,i));
    gensymed_symbol = character_1;
    if ( !((SI_Long)97L <= IFIX(gensymed_symbol) && IFIX(gensymed_symbol) 
	    <= (SI_Long)122L || (SI_Long)65L <= IFIX(gensymed_symbol) && 
	    IFIX(gensymed_symbol) <= (SI_Long)90L || (SI_Long)48L <= 
	    IFIX(gensymed_symbol) && IFIX(gensymed_symbol) <= (SI_Long)57L))
	return VALUES_1(Nil);
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

static Object Qunknown_user;       /* unknown-user */

static Object Qinitializing_the_password_of_user_with_existing_password;  /* initializing-the-password-of-user-with-existing-password */

static Object Qpassword_required;  /* password-required */

static Object Qunknown_user_or_bad_password;  /* unknown-user-or-bad-password */

static Object Qnew_password_required;  /* new-password-required */

static Object Qnew_password_does_not_match_its_duplicate;  /* new-password-does-not-match-its-duplicate */

static Object Qnew_password_too_long;  /* new-password-too-long */

static Object Qnew_password_has_invalid_characters;  /* new-password-has-invalid-characters */

static Object Qcannot_find_g2_ok_file;  /* cannot-find-g2-ok-file */

static Object string_constant_37;  /* "" */

/* CHANGE-USER-PASSWORD-IF-APPROPRIATE */
Object change_user_password_if_appropriate(user_name_symbol,
	    encoded_old_password,clear_old_password,clear_new_password,
	    encoded_new_password_1,encoded_new_password_2_qm)
    Object user_name_symbol, encoded_old_password, clear_old_password;
    Object clear_new_password, encoded_new_password_1;
    Object encoded_new_password_2_qm;
{
    volatile Object user_name_string;
    Object authorization_entry_qm;
    volatile Object ok_pathname_qm;
    volatile Object namestring_qm;
    Object setting_initial_password_qm;
    Object error_symbol_for_incorrect_old_password_qm, end1, end2;
    Object ab_loop_iter_flag_, temp, temp_1, string2, car_arg, car_new_value;
    SI_Long length1, length2, index1, ab_loop_bind_, index2, ab_loop_bind__1;
    SI_Long code;
    char temp_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(129,135);
    SAVE_STACK();
    user_name_string = Qunbound_in_protected_let;
    authorization_entry_qm = Qunbound_in_protected_let;
    ok_pathname_qm = Qunbound_in_protected_let;
    namestring_qm = Qunbound_in_protected_let;
    setting_initial_password_qm = Qunbound_in_protected_let;
    error_symbol_for_incorrect_old_password_qm = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	user_name_string = copy_symbol_name(2,user_name_symbol,Nil);
	authorization_entry_qm = assq_function(user_name_symbol,
		Authorized_users_list);
	ok_pathname_qm = Nil;
	namestring_qm = Nil;
	end1 = text_string_length(clear_old_password);
	end2 = text_string_length(array_constant_2);
	length1 = IFIX(end1) - (SI_Long)0L;
	length2 = IFIX(end2) - (SI_Long)0L;
	if (length1 == length2) {
	    index1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(end1);
	    index2 = (SI_Long)0L;
	    ab_loop_bind__1 = IFIX(end2);
	    ab_loop_iter_flag_ = T;
	  next_loop:
	    if (index1 >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_iter_flag_))
		index2 = index2 + (SI_Long)1L;
	    if (index2 >= ab_loop_bind__1)
		goto end_loop;
	    code = UBYTE_16_ISAREF_1(clear_old_password,index1);
	    if (code < (SI_Long)127L)
		temp = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp = unicode_lowercase_if_uppercase(FIX(code));
		if (temp);
		else
		    temp = FIX(code);
	    }
	    code = UBYTE_16_ISAREF_1(array_constant_2,index2);
	    if (code < (SI_Long)127L)
		temp_1 = (SI_Long)65L <= code && code <= (SI_Long)90L ? 
			FIX(code + (SI_Long)32L) : FIX(code);
	    else {
		temp_1 = unicode_lowercase_if_uppercase(FIX(code));
		if (temp_1);
		else
		    temp_1 = FIX(code);
	    }
	    if ( !NUM_EQ(temp,temp_1)) {
		setting_initial_password_qm = Nil;
		goto end_1;
	    }
	    ab_loop_iter_flag_ = Nil;
	    index1 = index1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    setting_initial_password_qm = T;
	    goto end_1;
	    setting_initial_password_qm = Qnil;
	  end_1:;
	}
	else
	    setting_initial_password_qm = Nil;
	if (setting_initial_password_qm) {
	    if ( !TRUEP(authorization_entry_qm))
		error_symbol_for_incorrect_old_password_qm = Qunknown_user;
	    else {
		temp = CDR(authorization_entry_qm);
		if ( !TRUEP(string_equalw(array_constant_2,CAR(temp))))
		    error_symbol_for_incorrect_old_password_qm = 
			    Qinitializing_the_password_of_user_with_existing_password;
		else
		    error_symbol_for_incorrect_old_password_qm = Qnil;
	    }
	}
	else if ( !TRUEP(encoded_old_password))
	    error_symbol_for_incorrect_old_password_qm = Qpassword_required;
	else {
	    temp_2 =  !TRUEP(authorization_entry_qm);
	    if (temp_2);
	    else {
		string2 = SECOND(authorization_entry_qm);
		end1 = text_string_length(encoded_old_password);
		end2 = text_string_length(SECOND(authorization_entry_qm));
		length1 = IFIX(end1) - (SI_Long)0L;
		length2 = IFIX(end2) - (SI_Long)0L;
		if (length1 == length2) {
		    index1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(end1);
		    index2 = (SI_Long)0L;
		    ab_loop_bind__1 = IFIX(end2);
		    ab_loop_iter_flag_ = T;
		  next_loop_1:
		    if (index1 >= ab_loop_bind_)
			goto end_loop_1;
		    if ( !TRUEP(ab_loop_iter_flag_))
			index2 = index2 + (SI_Long)1L;
		    if (index2 >= ab_loop_bind__1)
			goto end_loop_1;
		    if ( !(UBYTE_16_ISAREF_1(encoded_old_password,index1) 
			    == UBYTE_16_ISAREF_1(string2,index2))) {
			temp_2 = TRUEP(Nil);
			goto end_2;
		    }
		    ab_loop_iter_flag_ = Nil;
		    index1 = index1 + (SI_Long)1L;
		    goto next_loop_1;
		  end_loop_1:
		    temp_2 = TRUEP(T);
		    goto end_2;
		    temp_2 = TRUEP(Qnil);
		  end_2:;
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_2 =  !temp_2;
	    }
	    if (temp_2)
		error_symbol_for_incorrect_old_password_qm = 
			Qunknown_user_or_bad_password;
	    else
		error_symbol_for_incorrect_old_password_qm = Qnil;
	}
	temp = error_symbol_for_incorrect_old_password_qm;
	if (temp)
	    SAVE_VALUES(VALUES_1(temp));
	else if ( !TRUEP(encoded_new_password_1))
	    SAVE_VALUES(VALUES_1(Qnew_password_required));
	else {
	    if (encoded_new_password_2_qm) {
		end1 = text_string_length(encoded_new_password_1);
		end2 = text_string_length(encoded_new_password_2_qm);
		length1 = IFIX(end1) - (SI_Long)0L;
		length2 = IFIX(end2) - (SI_Long)0L;
		if (length1 == length2) {
		    index1 = (SI_Long)0L;
		    ab_loop_bind_ = IFIX(end1);
		    index2 = (SI_Long)0L;
		    ab_loop_bind__1 = IFIX(end2);
		    ab_loop_iter_flag_ = T;
		  next_loop_2:
		    if (index1 >= ab_loop_bind_)
			goto end_loop_2;
		    if ( !TRUEP(ab_loop_iter_flag_))
			index2 = index2 + (SI_Long)1L;
		    if (index2 >= ab_loop_bind__1)
			goto end_loop_2;
		    if ( !(UBYTE_16_ISAREF_1(encoded_new_password_1,
			    index1) == 
			    UBYTE_16_ISAREF_1(encoded_new_password_2_qm,
			    index2))) {
			temp_2 = TRUEP(Nil);
			goto end_3;
		    }
		    ab_loop_iter_flag_ = Nil;
		    index1 = index1 + (SI_Long)1L;
		    goto next_loop_2;
		  end_loop_2:
		    temp_2 = TRUEP(T);
		    goto end_3;
		    temp_2 = TRUEP(Qnil);
		  end_3:;
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_2 =  !temp_2;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		SAVE_VALUES(VALUES_1(Qnew_password_does_not_match_its_duplicate));
	    else if (FIXNUM_LT(text_string_length(clear_new_password),
		    Minimum_g2_password_length))
		SAVE_VALUES(VALUES_1(Qnew_password_must_be_at_least_4_characters_long));
	    else if (FIXNUM_GT(text_string_length(clear_new_password),
		    Maximum_g2_password_length))
		SAVE_VALUES(VALUES_1(Qnew_password_too_long));
	    else if ( !TRUEP(valid_password_characters_p(clear_new_password)))
		SAVE_VALUES(VALUES_1(Qnew_password_has_invalid_characters));
	    else {
		ok_pathname_qm = g2_ok_file_probe();
		if (ok_pathname_qm) {
		    namestring_qm = gensym_namestring(1,ok_pathname_qm);
		    temp_2 = TRUEP(namestring_qm);
		}
		else
		    temp_2 = TRUEP(Nil);
		if ( !temp_2)
		    SAVE_VALUES(VALUES_1(Qcannot_find_g2_ok_file));
		else {
		    temp = 
			    save_new_user_password_in_g2_ok_file(namestring_qm,
			    user_name_string,setting_initial_password_qm ? 
			    string_constant_37 : encoded_old_password,
			    encoded_new_password_1);
		    if (temp)
			SAVE_VALUES(VALUES_1(temp));
		    else {
			car_arg = CDR(authorization_entry_qm);
			car_new_value = 
				copy_text_string(encoded_new_password_1);
			M_CAR(car_arg) = car_new_value;
			SAVE_VALUES(VALUES_1(Nil));
		    }
		}
	    }
	}
    }
    POP_UNWIND_PROTECT(0);
    if (namestring_qm) {
	if ( !EQ(namestring_qm,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_qm);
    }
    if (ok_pathname_qm) {
	if ( !EQ(ok_pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(ok_pathname_qm);
    }
    if (user_name_string) {
	if ( !EQ(user_name_string,Qunbound_in_protected_let))
	    reclaim_text_string(user_name_string);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_38;  /* "~a \"~a\" ~a ~a ~a" */

/* SAVE-NEW-USER-PASSWORD-IN-G2-OK-FILE */
Object save_new_user_password_in_g2_ok_file(file_name,user_name,
	    old_password_hashed,new_password_hashed)
    Object file_name, user_name, old_password_hashed, new_password_hashed;
{
    Object g2passwdexe_file_name;
    volatile Object command_line;
    volatile Object message_text_string;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(5);
    Object result;

    x_note_fn_call(129,136);
    SAVE_STACK();
    g2passwdexe_file_name = Qunbound_in_protected_let;
    command_line = Qunbound_in_protected_let;
    message_text_string = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	g2passwdexe_file_name = G2passwdexe;
	command_line = tformat_text_string(6,string_constant_38,
		g2passwdexe_file_name,file_name,user_name,
		old_password_hashed,new_password_hashed);
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
		  twrite_standard_secure_g2_notification_header();
		  temp = saving_new_password_format_control_string();
		  tformat(4,temp,user_name,g2passwdexe_file_name,file_name);
		  message_text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SAVE_VALUES(pass_command_to_g2passwd(command_line,
		message_text_string));
    }
    POP_UNWIND_PROTECT(0);
    if (message_text_string) {
	if ( !EQ(message_text_string,Qunbound_in_protected_let))
	    reclaim_text_string(message_text_string);
    }
    if (command_line) {
	if ( !EQ(command_line,Qunbound_in_protected_let))
	    reclaim_text_string(command_line);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qg2passwd_executable_cannot_be_found;  /* g2passwd-executable-cannot-be-found */

static Object Qproblem_saving_password_in_g2_ok_file;  /* problem-saving-password-in-g2-ok-file */

static Object string_constant_39;  /* "~%~a." */

/* PASS-COMMAND-TO-G2PASSWD */
Object pass_command_to_g2passwd(command_line,message_text_string)
    Object command_line, message_text_string;
{
    Object temp, result_gensym_float;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(129,137);
    temp =  !TRUEP(g2passwd_probe_file()) ? 
	    Qg2passwd_executable_cannot_be_found : Qnil;
    if (temp)
	return VALUES_1(temp);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    result_gensym_float = c_spawn_executable_process(command_line);
	    arg = DOUBLE_FLOAT_TO_DOUBLE(result_gensym_float);
	    arg_1 = -1.0;
	    if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
		    !inline_nanp_for_comparison(arg_1))
		result = VALUES_1(Qproblem_saving_password_in_g2_ok_file);
	    else {
		notify_user_at_console_and_on_logbook(2,string_constant_39,
			message_text_string);
		result = VALUES_1(Nil);
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
}

static Object string_constant_40;  /* "Changing password for user ~s, running ~s outside of G2 on the G2 OK file ~s" */

/* SAVING-NEW-PASSWORD-FORMAT-CONTROL-STRING */
Object saving_new_password_format_control_string()
{
    x_note_fn_call(129,138);
    return VALUES_1(string_constant_40);
}

static Object array_constant_34;   /* # */

static Object array_constant_35;   /* # */

static Object array_constant_36;   /* # */

static Object array_constant_37;   /* # */

static Object Qok_file_not_found;  /* ok-file-not-found */

static Object Qinvalid_user_name;  /* invalid-user-name */

static Object string_constant_41;  /* "~a \"~a\" ~a ~a ~a ~a ~a" */

static Object string_constant_42;  /* "Updated ~a: added a user entry for ~a" */

/* ADD-NEW-USER-ENCODING-AS-NEEDED */
Object add_new_user_encoding_as_needed(user_name,clear_password,
	    list_of_modes,universal_date)
    Object user_name, clear_password, list_of_modes, universal_date;
{
    volatile Object error_symbol_qm;
    Object write_symbols_in_lower_case_qm;
    volatile Object user_name_as_string;
    Object encoded_password;
    volatile Object mode_string;
    volatile Object decay_date;
    volatile Object operation_name_for_add;
    volatile Object ok_file_namestring_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object mode, rest_1, ab_loop_list_, g2passwdexe_file_name;
    volatile Object command_line;
    volatile Object message_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(6);
    Object result;

    x_note_fn_call(129,139);
    SAVE_STACK();
    error_symbol_qm = Qunbound_in_protected_let;
    write_symbols_in_lower_case_qm = Qunbound_in_protected_let;
    user_name_as_string = Qunbound_in_protected_let;
    encoded_password = Qunbound_in_protected_let;
    mode_string = Qunbound_in_protected_let;
    decay_date = Qunbound_in_protected_let;
    operation_name_for_add = Qunbound_in_protected_let;
    ok_file_namestring_qm = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    5);
      if (PUSH_UNWIND_PROTECT(1)) {
	  error_symbol_qm = Nil;
	  Write_symbols_in_lower_case_qm = T;
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
		    twrite(user_name);
		    user_name_as_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  encoded_password = encode_password_via_md5(user_name,
		  clear_password,Nil);
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
		    twrite(array_constant_34);
		    mode = Nil;
		    rest_1 = Nil;
		    ab_loop_list_ = list_of_modes;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    mode = CAR(ab_loop_list_);
		    rest_1 = CDR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    twrite(mode);
		    if (rest_1)
			twrite(array_constant_35);
		    goto next_loop;
		  end_loop:;
		    twrite(array_constant_36);
		    mode_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
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
		    twrite(universal_date);
		    decay_date = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  operation_name_for_add = copy_wide_string(array_constant_37);
	  ok_file_namestring_qm = g2_ok_file_probe() ? gensym_namestring(1,
		  Authorizing_ok_pathname) : Nil;
	  if ( !TRUEP(ok_file_namestring_qm))
	      error_symbol_qm = Qok_file_not_found;
	  if (invalid_user_name_p(user_name_as_string))
	      error_symbol_qm = Qinvalid_user_name;
	  if ( !TRUEP(error_symbol_qm)) {
	      g2passwdexe_file_name = Qunbound_in_protected_let;
	      command_line = Qunbound_in_protected_let;
	      message_text_string = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  g2passwdexe_file_name = G2passwdexe;
		  command_line = tformat_text_string(8,string_constant_41,
			  g2passwdexe_file_name,ok_file_namestring_qm,
			  operation_name_for_add,user_name_as_string,
			  encoded_password,mode_string,decay_date);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    twrite_standard_secure_g2_notification_header();
			    tformat(3,string_constant_42,
				    ok_file_namestring_qm,user_name_as_string);
			    message_text_string = 
				    copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  error_symbol_qm = pass_command_to_g2passwd(command_line,
			  message_text_string);
	      }
	      POP_UNWIND_PROTECT(0);
	      if (message_text_string) {
		  if ( !EQ(message_text_string,Qunbound_in_protected_let))
		      reclaim_text_string(message_text_string);
	      }
	      if (command_line) {
		  if ( !EQ(command_line,Qunbound_in_protected_let))
		      reclaim_text_string(command_line);
	      }
	      CONTINUE_UNWINDING(0);
	  }
	  if ( !TRUEP(error_symbol_qm))
	      enter_authorized_user(user_name,encoded_password,
		      list_of_modes,universal_date,T);
	  SAVE_VALUES(VALUES_1(error_symbol_qm));
      }
      POP_UNWIND_PROTECT(1);
      if (ok_file_namestring_qm) {
	  if ( !EQ(ok_file_namestring_qm,Qunbound_in_protected_let)) {
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(ok_file_namestring_qm) 
		      != (SI_Long)0L)
		  reclaim_wide_string(ok_file_namestring_qm);
	  }
      }
      if (operation_name_for_add) {
	  if ( !EQ(operation_name_for_add,Qunbound_in_protected_let))
	      reclaim_text_string(operation_name_for_add);
      }
      if (decay_date) {
	  if ( !EQ(decay_date,Qunbound_in_protected_let))
	      reclaim_text_string(decay_date);
      }
      if (mode_string) {
	  if ( !EQ(mode_string,Qunbound_in_protected_let))
	      reclaim_text_string(mode_string);
      }
      if (user_name_as_string) {
	  if ( !EQ(user_name_as_string,Qunbound_in_protected_let))
	      reclaim_text_string(user_name_as_string);
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant_38;   /* # */

static Object array_constant_39;   /* # */

static Object Qcan_not_write_tmp_file;  /* can-not-write-tmp-file */

static Object string_constant_43;  /* "~a \"~a\" ~a ~a \"~a\" ~a ~a" */

static Object string_constant_44;  /* "x" */

static Object string_constant_45;  /* "Updated ~a: deleted the user entry for ~a" */

/* DELETE-USER */
Object delete_user(user_name)
    Object user_name;
{
    volatile Object error_symbol_qm;
    Object write_symbols_in_lower_case_qm;
    volatile Object user_name_as_string;
    volatile Object operation_name_for_delete;
    volatile Object ok_file_namestring_qm;
    volatile Object tmp_file_namestring;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object copy, svref_new_value, temp, g2passwdexe_file_name;
    volatile Object command_line;
    volatile Object message_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(6);
    Object result;

    x_note_fn_call(129,140);
    SAVE_STACK();
    error_symbol_qm = Qunbound_in_protected_let;
    write_symbols_in_lower_case_qm = Qunbound_in_protected_let;
    user_name_as_string = Qunbound_in_protected_let;
    operation_name_for_delete = Qunbound_in_protected_let;
    ok_file_namestring_qm = Qunbound_in_protected_let;
    tmp_file_namestring = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    5);
      if (PUSH_UNWIND_PROTECT(1)) {
	  error_symbol_qm = Nil;
	  Write_symbols_in_lower_case_qm = T;
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
		    twrite(user_name);
		    user_name_as_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  operation_name_for_delete = copy_wide_string(array_constant_38);
	  ok_file_namestring_qm = g2_ok_file_probe() ? gensym_namestring(1,
		  Authorizing_ok_pathname) : Nil;
	  copy = copy_gensym_pathname(Authorizing_ok_pathname);
	  svref_new_value = copy_wide_string(array_constant_39);
	  SVREF(copy,FIX((SI_Long)4L)) = svref_new_value;
	  temp = gensym_namestring(1,copy);
	  reclaim_gensym_pathname(copy);
	  tmp_file_namestring = temp;
	  if ( !TRUEP(ok_file_namestring_qm))
	      error_symbol_qm = Qok_file_not_found;
	  if ( !TRUEP(error_symbol_qm)) {
	      if ( !TRUEP(gensym_probe_file_for_write(tmp_file_namestring)))
		  error_symbol_qm = Qcan_not_write_tmp_file;
	  }
	  if ( !TRUEP(error_symbol_qm)) {
	      g2passwdexe_file_name = Qunbound_in_protected_let;
	      command_line = Qunbound_in_protected_let;
	      message_text_string = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  g2passwdexe_file_name = G2passwdexe;
		  command_line = tformat_text_string(8,string_constant_43,
			  g2passwdexe_file_name,ok_file_namestring_qm,
			  operation_name_for_delete,user_name_as_string,
			  tmp_file_namestring,string_constant_44,
			  string_constant_44);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    twrite_standard_secure_g2_notification_header();
			    tformat(3,string_constant_45,
				    ok_file_namestring_qm,user_name_as_string);
			    message_text_string = 
				    copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  error_symbol_qm = pass_command_to_g2passwd(command_line,
			  message_text_string);
	      }
	      POP_UNWIND_PROTECT(0);
	      if (message_text_string) {
		  if ( !EQ(message_text_string,Qunbound_in_protected_let))
		      reclaim_text_string(message_text_string);
	      }
	      if (command_line) {
		  if ( !EQ(command_line,Qunbound_in_protected_let))
		      reclaim_text_string(command_line);
	      }
	      CONTINUE_UNWINDING(0);
	  }
	  if ( !TRUEP(error_symbol_qm))
	      remove_authorized_user(user_name);
	  SAVE_VALUES(VALUES_1(error_symbol_qm));
      }
      POP_UNWIND_PROTECT(1);
      if (tmp_file_namestring) {
	  if ( !EQ(tmp_file_namestring,Qunbound_in_protected_let))
	      reclaim_text_string(tmp_file_namestring);
      }
      if (ok_file_namestring_qm) {
	  if ( !EQ(ok_file_namestring_qm,Qunbound_in_protected_let)) {
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(ok_file_namestring_qm) 
		      != (SI_Long)0L)
		  reclaim_wide_string(ok_file_namestring_qm);
	  }
      }
      if (operation_name_for_delete) {
	  if ( !EQ(operation_name_for_delete,Qunbound_in_protected_let))
	      reclaim_text_string(operation_name_for_delete);
      }
      if (user_name_as_string) {
	  if ( !EQ(user_name_as_string,Qunbound_in_protected_let))
	      reclaim_text_string(user_name_as_string);
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object array_constant_40;   /* # */

static Object array_constant_41;   /* # */

static Object array_constant_42;   /* # */

static Object string_constant_46;  /* "Updated ~a: modified the password-validity entry ~
				    *                   for ~a"
				    */

/* CHANGE-USERS-PASSWORD-DECAY-DATE */
Object change_users_password_decay_date(user_name,universal_date)
    Object user_name, universal_date;
{
    volatile Object error_symbol_qm;
    Object write_symbols_in_lower_case_qm;
    volatile Object user_name_as_string;
    volatile Object decay_date;
    volatile Object operation_name;
    volatile Object ok_file_namestring_qm;
    volatile Object dummy_encoded_password;
    volatile Object dummy_mode_list;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object g2passwdexe_file_name;
    volatile Object command_line;
    volatile Object message_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(6);
    Object result;

    x_note_fn_call(129,141);
    SAVE_STACK();
    error_symbol_qm = Qunbound_in_protected_let;
    write_symbols_in_lower_case_qm = Qunbound_in_protected_let;
    user_name_as_string = Qunbound_in_protected_let;
    decay_date = Qunbound_in_protected_let;
    operation_name = Qunbound_in_protected_let;
    ok_file_namestring_qm = Qunbound_in_protected_let;
    dummy_encoded_password = Qunbound_in_protected_let;
    dummy_mode_list = Qunbound_in_protected_let;
    PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_in_lower_case_qm,Qwrite_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
	    5);
      if (PUSH_UNWIND_PROTECT(1)) {
	  error_symbol_qm = Nil;
	  Write_symbols_in_lower_case_qm = T;
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
		    twrite(user_name);
		    user_name_as_string = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
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
		    twrite(universal_date);
		    decay_date = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  operation_name = copy_wide_string(array_constant_40);
	  ok_file_namestring_qm = g2_ok_file_probe() ? gensym_namestring(1,
		  Authorizing_ok_pathname) : Nil;
	  dummy_encoded_password = copy_wide_string(array_constant_41);
	  dummy_mode_list = copy_wide_string(array_constant_42);
	  if ( !TRUEP(ok_file_namestring_qm))
	      error_symbol_qm = Qok_file_not_found;
	  if ( !TRUEP(error_symbol_qm)) {
	      g2passwdexe_file_name = Qunbound_in_protected_let;
	      command_line = Qunbound_in_protected_let;
	      message_text_string = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  g2passwdexe_file_name = G2passwdexe;
		  command_line = tformat_text_string(8,string_constant_41,
			  g2passwdexe_file_name,ok_file_namestring_qm,
			  operation_name,user_name_as_string,
			  dummy_encoded_password,dummy_mode_list,decay_date);
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
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    twrite_standard_secure_g2_notification_header();
			    tformat(3,string_constant_46,
				    ok_file_namestring_qm,user_name_as_string);
			    message_text_string = 
				    copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  error_symbol_qm = pass_command_to_g2passwd(command_line,
			  message_text_string);
	      }
	      POP_UNWIND_PROTECT(0);
	      if (message_text_string) {
		  if ( !EQ(message_text_string,Qunbound_in_protected_let))
		      reclaim_text_string(message_text_string);
	      }
	      if (command_line) {
		  if ( !EQ(command_line,Qunbound_in_protected_let))
		      reclaim_text_string(command_line);
	      }
	      CONTINUE_UNWINDING(0);
	  }
	  if ( !TRUEP(error_symbol_qm))
	      set_validity_of_user_password(user_name,universal_date);
	  SAVE_VALUES(VALUES_1(error_symbol_qm));
      }
      POP_UNWIND_PROTECT(1);
      if (dummy_mode_list) {
	  if ( !EQ(dummy_mode_list,Qunbound_in_protected_let))
	      reclaim_text_string(dummy_mode_list);
      }
      if (dummy_encoded_password) {
	  if ( !EQ(dummy_encoded_password,Qunbound_in_protected_let))
	      reclaim_text_string(dummy_encoded_password);
      }
      if (ok_file_namestring_qm) {
	  if ( !EQ(ok_file_namestring_qm,Qunbound_in_protected_let)) {
	      if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(ok_file_namestring_qm) 
		      != (SI_Long)0L)
		  reclaim_wide_string(ok_file_namestring_qm);
	  }
      }
      if (operation_name) {
	  if ( !EQ(operation_name,Qunbound_in_protected_let))
	      reclaim_text_string(operation_name);
      }
      if (decay_date) {
	  if ( !EQ(decay_date,Qunbound_in_protected_let))
	      reclaim_text_string(decay_date);
      }
      if (user_name_as_string) {
	  if ( !EQ(user_name_as_string,Qunbound_in_protected_let))
	      reclaim_text_string(user_name_as_string);
      }
      CONTINUE_UNWINDING(1);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qformat_frame;       /* format-frame */

static Object Qblob_edit_box_format;  /* blob-edit-box-format */

/* CREATE-BLOB-EDIT-BOX-FORMAT */
Object create_blob_edit_box_format()
{
    Object temp;

    x_note_fn_call(129,142);
    temp = get_instance_with_name_if_any(Qformat_frame,Qblob_edit_box_format);
    if (temp)
	return VALUES_1(temp);
    else
	return make_format_frame(Qblob_edit_box_format);
}

static Object string_constant_47;  /* "Reinstall authorized users?~
				    *              ~%~%This action reads in the ~
				    *              G2 ok file (~s) and installs that file's set ~
				    *              of authorized users, passwords, and user modes.~
				    *              ~%~%This does not affect ~
				    *              logged-in users until they log off or change their G2 user mode."
				    */

static Object Qread_ok_file_again;  /* read-ok-file-again */

/* REINSTALL-AUTHORIZED-USERS */
Object reinstall_authorized_users()
{
    Object pathname_qm, namestring_1;

    x_note_fn_call(129,143);
    pathname_qm = g2_ok_file_probe();
    if (pathname_qm) {
	namestring_1 = gensym_namestring(1,pathname_qm);
	confirm_or_cancel(3,tformat_text_string(2,string_constant_47,
		namestring_1),Qread_ok_file_again,Nil);
	reclaim_text_string(namestring_1);
	return reclaim_gensym_pathname(pathname_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_43;   /* # */

/* G2-REINSTALL-AUTHORIZED-USERS */
Object g2_reinstall_authorized_users()
{
    Object value_1, fresh_error_string_qm, temp;

    x_note_fn_call(129,144);
    value_1 = Nil;
    fresh_error_string_qm = read_ok_file_again();
    temp = fresh_error_string_qm;
    if (temp);
    else
	temp = copy_text_string(array_constant_43);
    value_1 = temp;
    temp = copy_as_wide_string(value_1);
    return VALUES_1(temp);
}

static Object string_constant_48;  /* "Reinstalling authorized users from ~s." */

static Object string_constant_49;  /* "~%~a" */

static Object string_constant_50;  /* "~a~%Please wait . . . " */

static Object string_constant_51;  /* "Reinstallation of authorized users completed " */

static Object string_constant_52;  /* "unsuccessfully! ERROR: ~a" */

static Object string_constant_53;  /* "successfully." */

/* READ-OK-FILE-AGAIN */
Object read_ok_file_again()
{
    volatile Object pathname_qm;
    volatile Object namestring_1;
    volatile Object completion_message;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object message_text_string;
    volatile Object error_qm;
    Object temp, current_long_operation_notification_workspace;
    Object frame_serial_number, kb_serial_number;
    Object fixnum_time_at_start_of_current_long_notification;
    Object doing_long_operation_with_notification_qm;
    Object long_operation_notification_has_been_put_up_qm, gensymed_symbol_2;
    Object xa, ya;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, gensymed_symbol;
    SI_Long gensymed_symbol_1;
    char temp_1;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(5);
    Object result;

    x_note_fn_call(129,145);
    SAVE_STACK();
    pathname_qm = Qunbound_in_protected_let;
    namestring_1 = Qunbound_in_protected_let;
    completion_message = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(1)) {
	pathname_qm = g2_ok_file_probe();
	namestring_1 = pathname_qm ? gensym_namestring(1,pathname_qm) : Nil;
	completion_message = Nil;
	if (pathname_qm) {
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
		      twrite_standard_secure_g2_notification_header();
		      tformat(2,string_constant_48,namestring_1);
		      message_text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user_at_console_and_on_logbook(2,string_constant_49,
		    message_text_string);
	    error_qm = Nil;
	    temp = make_message(1,tformat_text_string(2,string_constant_50,
		    message_text_string));
	    current_long_operation_notification_workspace = 
		    make_workspace(6,Qtemporary_workspace,Nil,temp,Nil,
		    Width_for_prominent_notification_workspaces,
		    Height_for_prominent_notification_workspaces);
	    PUSH_SPECIAL_WITH_SYMBOL(Current_long_operation_notification_workspace,Qcurrent_long_operation_notification_workspace,current_long_operation_notification_workspace,
		    3);
	      frame_serial_number = 
		      copy_frame_serial_number(Current_frame_serial_number);
	      kb_serial_number = Current_kb_serial_number;
	      fixnum_time_at_start_of_current_long_notification = 
		      c_native_clock_ticks_or_cache(Nil,Nil);
	      PUSH_SPECIAL_WITH_SYMBOL(Fixnum_time_at_start_of_current_long_notification,Qfixnum_time_at_start_of_current_long_notification,fixnum_time_at_start_of_current_long_notification,
		      2);
		if (PUSH_UNWIND_PROTECT(0)) {
		    doing_long_operation_with_notification_qm = T;
		    long_operation_notification_has_been_put_up_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Long_operation_notification_has_been_put_up_qm,Qlong_operation_notification_has_been_put_up_qm,long_operation_notification_has_been_put_up_qm,
			    1);
		      PUSH_SPECIAL_WITH_SYMBOL(Doing_long_operation_with_notification_qm,Qdoing_long_operation_with_notification_qm,doing_long_operation_with_notification_qm,
			      0);
			if ( !TRUEP(Nil)) {
			    if (Doing_long_operation_with_notification_qm 
				    &&  
				    !TRUEP(Long_operation_notification_has_been_put_up_qm)) 
					{
				gensymed_symbol = 
					IFIX(c_native_clock_ticks_or_cache(Nil,
					Nil));
				gensymed_symbol_1 = 
					IFIX(Fixnum_time_at_start_of_current_long_notification);
				if (gensymed_symbol >= gensymed_symbol_1)
				    temp = FIX(gensymed_symbol - 
					    gensymed_symbol_1);
				else {
				    gensymed_symbol = gensymed_symbol - 
					    gensymed_symbol_1;
				    gensymed_symbol = gensymed_symbol + 
					    IFIX(Most_positive_fixnum);
				    temp = FIX(gensymed_symbol + (SI_Long)1L);
				}
				temp_1 = FIXNUM_GE(temp,
					fixnum_time_interval(FIX((SI_Long)0L)));
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1)
				put_up_long_operation_notification_now();
			}
			error_qm = 
				read_ok_file_just_for_updating_user_data(namestring_1);
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		POP_UNWIND_PROTECT(0);
		if (FIXNUM_EQ(Current_kb_serial_number,kb_serial_number)) {
		    gensymed_symbol_2 = 
			    ISVREF(Current_long_operation_notification_workspace,
			    (SI_Long)3L);
		    temp_1 = 
			    SIMPLE_VECTOR_P(Current_long_operation_notification_workspace) 
			    ? 
			    EQ(ISVREF(Current_long_operation_notification_workspace,
			    (SI_Long)1L),Qavailable_frame_vector) : 
			    TRUEP(Qnil);
		    if (temp_1);
		    else
			temp_1 = FIXNUMP(gensymed_symbol_2) ? 
				IFIX(gensymed_symbol_2) == (SI_Long)-1L : 
				TRUEP(Nil);
		    if (temp_1);
		    else if (FIXNUMP(frame_serial_number))
			temp_1 = FIXNUMP(gensymed_symbol_2) ? 
				FIXNUM_LT(frame_serial_number,
				gensymed_symbol_2) : TRUEP(T);
		    else if (FIXNUMP(gensymed_symbol_2))
			temp_1 = TRUEP(Nil);
		    else {
			xa = M_CAR(frame_serial_number);
			ya = M_CAR(gensymed_symbol_2);
			temp_1 = FIXNUM_LT(xa,ya);
			if (temp_1);
			else
			    temp_1 = FIXNUM_EQ(xa,ya) ? 
				    FIXNUM_LT(M_CDR(frame_serial_number),
				    M_CDR(gensymed_symbol_2)) : TRUEP(Qnil);
		    }
		    temp_1 =  !temp_1;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    delete_frame(Current_long_operation_notification_workspace);
		reclaim_frame_serial_number(frame_serial_number);
		CONTINUE_UNWINDING(0);
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
		      twrite_standard_secure_g2_notification_header();
		      tformat(1,string_constant_51);
		      if (error_qm)
			  tformat(2,string_constant_52,error_qm);
		      else
			  tformat(1,string_constant_53);
		      completion_message = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_user_at_console_and_on_logbook(2,string_constant_49,
		    completion_message);
	    SAVE_VALUES(VALUES_1(error_qm));
	}
	else
	    SAVE_VALUES(VALUES_1(Nil));
    }
    POP_UNWIND_PROTECT(1);
    if (completion_message) {
	if ( !EQ(completion_message,Qunbound_in_protected_let))
	    reclaim_text_string(completion_message);
    }
    if (namestring_1) {
	if ( !EQ(namestring_1,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_1);
    }
    if (pathname_qm) {
	if ( !EQ(pathname_qm,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_qm);
    }
    CONTINUE_UNWINDING(1);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object string_constant_54;  /* "Secure G2: (" */

static Object string_constant_55;  /* "; User: ~a)  " */

static Object string_constant_56;  /* ")  " */

/* TWRITE-STANDARD-SECURE-G2-NOTIFICATION-HEADER */
Object twrite_standard_secure_g2_notification_header()
{
    Object user_qm;

    x_note_fn_call(129,146);
    tformat(1,string_constant_54);
    twrite_current_real_time();
    user_qm = Servicing_workstation_qm ? ISVREF(Current_workstation,
	    (SI_Long)20L) : Nil;
    if (user_qm)
	return tformat(2,string_constant_55,user_qm);
    else
	return tformat(1,string_constant_56);
}

/* TWRITE-CURRENT-REAL-TIME */
Object twrite_current_real_time()
{
    Object seconds, minutes, hours, day, month, year;
    Object result;

    x_note_fn_call(129,147);
    result = get_decoded_real_time();
    MVS_6(result,seconds,minutes,hours,day,month,year);
    return print_decoded_time(seconds,minutes,hours,day,month,year);
}

static Object Qbuild_symbol;       /* build-symbol */

static Object Kall;                /* :all */

static Object Qos_user_name;       /* os-user-name */

static Object Qdiscard_user_settings;  /* discard-user-settings */

static Object Qwindow;             /* window */

static Object Qcjk_language;       /* cjk-language */

static Object Qinit_string;        /* init-string */

static Object Qnetwork_host_name;  /* network-host-name */

static Object Qos_type;            /* os-type */

static Object Qreroute_problem_report;  /* reroute-problem-report */

/* SET-SESSION-INFO-IN-WORKSTATION */
Object set_session_info_in_workstation(gensym_window,workstation)
    Object gensym_window, workstation;
{
    Object value_qm, temp;

    x_note_fn_call(129,148);
    value_qm = get_gensym_window_parameter(gensym_window,Quser_name);
    if (value_qm) {
	if (EQ(Qbuild_symbol,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qbuild_symbol,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)20L));
	SVREF(workstation,FIX((SI_Long)20L)) = temp;
    }
    if ( !TRUEP(ISVREF(workstation,(SI_Long)20L))) {
	value_qm = get_gensym_window_parameter(gensym_window,Qos_user_name);
	if (value_qm) {
	    if (EQ(Qbuild_symbol,Qbuild_symbol))
		temp = intern_text_string(1,
			copy_text_string_with_case_conversion(value_qm,Kall));
	    else if (EQ(Qbuild_symbol,Qpassword))
		temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	    else
		temp = copy_for_slot_value(value_qm);
	    reclaim_slot_value(ISVREF(workstation,(SI_Long)20L));
	    SVREF(workstation,FIX((SI_Long)20L)) = temp;
	}
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qmd5_password);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)21L));
	SVREF(workstation,FIX((SI_Long)21L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,
	    Qdiscard_user_settings);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)22L));
	SVREF(workstation,FIX((SI_Long)22L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Quser_mode);
    if (value_qm) {
	if (EQ(Qbuild_symbol,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qbuild_symbol,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)19L));
	SVREF(workstation,FIX((SI_Long)19L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qwindow);
    if (value_qm) {
	if (EQ(Qbuild_symbol,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qbuild_symbol,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)23L));
	SVREF(workstation,FIX((SI_Long)23L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qlanguage);
    if (value_qm) {
	if (EQ(Qbuild_symbol,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qbuild_symbol,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)27L));
	SVREF(workstation,FIX((SI_Long)27L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qwindow_style);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)50L));
	SVREF(workstation,FIX((SI_Long)50L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qcjk_language);
    if (value_qm) {
	if (EQ(Qbuild_symbol,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qbuild_symbol,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)49L));
	SVREF(workstation,FIX((SI_Long)49L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qinit_string);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)26L));
	SVREF(workstation,FIX((SI_Long)26L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qnetwork_host_name);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)38L));
	SVREF(workstation,FIX((SI_Long)38L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qos_user_name);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)39L));
	SVREF(workstation,FIX((SI_Long)39L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,Qos_type);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)43L));
	SVREF(workstation,FIX((SI_Long)43L)) = temp;
    }
    value_qm = get_gensym_window_parameter(gensym_window,
	    Qreroute_problem_report);
    if (value_qm) {
	if (EQ(Qnil,Qbuild_symbol))
	    temp = intern_text_string(1,
		    copy_text_string_with_case_conversion(value_qm,Kall));
	else if (EQ(Qnil,Qpassword))
	    temp = FIXNUMP(value_qm) ? Nil : copy_for_slot_value(value_qm);
	else
	    temp = copy_for_slot_value(value_qm);
	reclaim_slot_value(ISVREF(workstation,(SI_Long)40L));
	SVREF(workstation,FIX((SI_Long)40L)) = temp;
    }
    temp = copy_managed_float(Current_real_time);
    reclaim_slot_value(ISVREF(workstation,(SI_Long)24L));
    return VALUES_1(SVREF(workstation,FIX((SI_Long)24L)) = temp);
}

static Object Qg2_login_window_name_or_class;  /* g2-login-window-name-or-class */

static Object Qg2_login_specific_language_for_this_g2_window_qm;  /* g2-login-specific-language-for-this-g2-window? */

static Object Qg2_login_style_specifically_for_this_workstation_qm;  /* g2-login-style-specifically-for-this-workstation? */

static Object Qg2_login_init_string_qm;  /* g2-login-init-string? */

/* SET-SESSION-INFO-IN-G2-LOGIN */
Object set_session_info_in_g2_login(workstation,g2_login)
    Object workstation, g2_login;
{
    Object svref_new_value;

    x_note_fn_call(129,149);
    reclaim_slot_value(get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_name_qm,Nil));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_user_name_qm);
    set_lookup_slot_value_1(g2_login,Qg2_login_user_name_qm,
	    copy_for_slot_value(ISVREF(workstation,(SI_Long)20L)));
    reclaim_slot_value(ISVREF(g2_login,(SI_Long)24L));
    svref_new_value = copy_for_slot_value(ISVREF(workstation,(SI_Long)21L));
    ISVREF(g2_login,(SI_Long)24L) = svref_new_value;
    reclaim_slot_value(get_lookup_slot_value_given_default(g2_login,
	    Qg2_login_user_mode,Nil));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_user_mode);
    set_lookup_slot_value_1(g2_login,Qg2_login_user_mode,
	    copy_for_slot_value(ISVREF(workstation,(SI_Long)19L)));
    reclaim_slot_value(ISVREF(g2_login,(SI_Long)20L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_window_name_or_class);
    svref_new_value = copy_for_slot_value(ISVREF(workstation,(SI_Long)23L));
    SVREF(g2_login,FIX((SI_Long)20L)) = svref_new_value;
    reclaim_slot_value(ISVREF(g2_login,(SI_Long)21L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,
		Qg2_login_specific_language_for_this_g2_window_qm);
    svref_new_value = copy_for_slot_value(ISVREF(workstation,(SI_Long)27L));
    SVREF(g2_login,FIX((SI_Long)21L)) = svref_new_value;
    reclaim_slot_value(ISVREF(g2_login,(SI_Long)22L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,
		Qg2_login_style_specifically_for_this_workstation_qm);
    svref_new_value = copy_for_slot_value(ISVREF(workstation,(SI_Long)50L));
    SVREF(g2_login,FIX((SI_Long)22L)) = svref_new_value;
    reclaim_slot_value(ISVREF(g2_login,(SI_Long)23L));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_init_string_qm);
    svref_new_value = copy_for_slot_value(ISVREF(workstation,(SI_Long)26L));
    SVREF(g2_login,FIX((SI_Long)23L)) = svref_new_value;
    return VALUES_1(Nil);
}

static Object Qg2_user_name;       /* g2-user-name */

static Object Qg2_user_mode;       /* g2-user-mode */

static Object Qspecific_language_for_this_g2_window_qm;  /* specific-language-for-this-g2-window? */

static Object Qg2_window_initial_window_configuration_string_qm;  /* g2-window-initial-window-configuration-string? */

static Object Qg2_window_style;    /* g2-window-style */

static Object Qg2_window_network_host_name_qm;  /* g2-window-network-host-name? */

static Object Qg2_window_os_user_name_qm;  /* g2-window-os-user-name? */

static Object Qg2_window_os_type_qm;  /* g2-window-os-type? */

static Object Qg2_window_time_of_last_connection_qm;  /* g2-window-time-of-last-connection? */

static Object Qg2_window_reroute_problem_report_qm;  /* g2-window-reroute-problem-report? */

static Object Qg2_connection_status;  /* g2-connection-status */

static Object Qconnected;          /* connected */

/* SET-SESSION-INFO-IN-G2-WINDOW */
Object set_session_info_in_g2_window(workstation,g2_window)
    Object workstation, g2_window;
{
    Object temp, temp_1;

    x_note_fn_call(129,150);
    temp = get_lookup_slot_value_given_default(g2_window,Qg2_user_name,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)20L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_user_name,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)20L)));
    temp = get_lookup_slot_value_given_default(g2_window,Qg2_user_mode,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)19L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_user_mode,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)19L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qspecific_language_for_this_g2_window_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)27L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,
		Qspecific_language_for_this_g2_window_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)27L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_initial_window_configuration_string_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)26L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,
		Qg2_window_initial_window_configuration_string_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)26L)));
    temp = get_lookup_slot_value_given_default(g2_window,Qg2_window_style,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)50L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_window_style,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)50L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_network_host_name_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)38L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_window_network_host_name_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)38L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_os_user_name_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)39L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_window_os_user_name_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)39L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_os_type_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)43L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_window_os_type_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)43L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_time_of_last_connection_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)24L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,
		Qg2_window_time_of_last_connection_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)24L)));
    temp = get_lookup_slot_value_given_default(g2_window,
	    Qg2_window_reroute_problem_report_qm,Nil);
    temp_1 = ISVREF(workstation,(SI_Long)40L);
    if ( !EQL(temp,temp_1))
	change_slot_value(3,g2_window,Qg2_window_reroute_problem_report_qm,
		copy_for_slot_value(ISVREF(workstation,(SI_Long)40L)));
    copy_gensym_window_attributes_into_g2_window(ISVREF(workstation,
	    (SI_Long)1L));
    if ( !EQ(get_lookup_slot_value(g2_window,Qg2_connection_status),
	    Qconnected))
	return change_slot_value(3,g2_window,Qg2_connection_status,Qconnected);
    else
	return VALUES_1(Nil);
}

static Object Qui_client_session;  /* ui-client-session */

static Object Qui_client_session_user_mode;  /* ui-client-session-user-mode */

/* UPDATE-USER-MODE-STATE */
Object update_user_mode_state(frame,new_mode)
    Object frame, new_mode;
{
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object present_value, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;

    x_note_fn_call(129,151);
    gensymed_symbol = ISVREF(frame,(SI_Long)1L);
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
    if (temp) {
	present_value = get_slot_value_function(frame,
		Qui_client_session_user_mode,Nil);
	if ( !EQ(present_value,new_mode))
	    return change_slot_value(3,frame,Qui_client_session_user_mode,
		    new_mode);
	else
	    return VALUES_1(Nil);
    }
    else {
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
	if (temp)
	    return update_ab_side_tw_user_mode(new_mode,frame,ISVREF(frame,
		    (SI_Long)20L));
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_login_class_description,(SI_Long)18L));
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2 ? T : Nil;
	    }
	    else
		temp_1 = Nil;
	    if (temp_1)
		return VALUES_1(temp_1);
	    else
		return VALUES_1(Qt);
	}
    }
}

/* UPDATE-AB-SIDE-TW-USER-MODE */
Object update_ab_side_tw_user_mode(new_mode,g2_window_qm,workstation_qm)
    Object new_mode, g2_window_qm, workstation_qm;
{
    Object present_value, current_workstation_1, current_workstation_window;
    Object current_g2_window_for_this_workstation_qm;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object new_g2_classic_ui_p, servicing_workstation_qm;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(12);
    Object result;

    x_note_fn_call(129,152);
    SAVE_STACK();
    present_value = g2_window_qm ? 
	    get_lookup_slot_value_given_default(g2_window_qm,Qg2_user_mode,
	    Nil) : Nil;
    if ( !EQ(present_value,new_mode)) {
	if (g2_window_qm)
	    change_slot_value(3,g2_window_qm,Qg2_user_mode,new_mode);
	if (workstation_qm)
	    SVREF(workstation_qm,FIX((SI_Long)19L)) = new_mode;
	if (Servicing_workstation_qm)
	    Current_g2_user_mode_qm = new_mode;
	decache_dynamic_menus(2,Quser_mode,workstation_qm);
	if (native_menu_bar_really_needs_updating_p(workstation_qm)) {
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
				ISVREF(Current_workstation_window,
				(SI_Long)17L);
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
					  ISVREF(Current_workstation,
					  (SI_Long)19L);
				  PUSH_SPECIAL_WITH_SYMBOL(Current_g2_user_mode_qm,Qcurrent_g2_user_mode_qm,current_g2_user_mode_qm,
					  2);
				    new_g2_classic_ui_p = 
					    get_value_for_current_workstation_new_g2_classic_ui_p();
				    PUSH_SPECIAL_WITH_SYMBOL(New_g2_classic_ui_p,Qnew_g2_classic_ui_p,new_g2_classic_ui_p,
					    1);
				      servicing_workstation_qm = T;
				      PUSH_SPECIAL_WITH_SYMBOL(Servicing_workstation_qm,Qservicing_workstation_qm,servicing_workstation_qm,
					      0);
					temp = 
						update_native_menu_bar(workstation_qm);
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
		SAVE_VALUES(VALUES_1(temp));
	    }
	    POP_UNWIND_PROTECT(0);
	    UNLOCK(For_workstation);
	    CONTINUE_UNWINDING(0);
	    result = RESTORE_VALUES();
	    temp = result;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    result = VALUES_1(temp);
    RESTORE_STACK();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Event_handler_args, Qevent_handler_args);

static Object list_constant_7;     /* # */

/* NAME-OF-EXPORTED-EVENT-HANDLER? */
Object name_of_exported_event_handler_qm(name)
    Object name;
{
    x_note_fn_call(129,153);
    return memq_function(name,list_constant_7);
}

static Object Qinternal;           /* internal */

static Object Quser;               /* user */

static Object Qexecute_user_menu_choice_if_possible;  /* execute-user-menu-choice-if-possible */

static Object Qstart_generic_command;  /* start-generic-command */

static Object Qnew_style_event_handler;  /* new-style-event-handler */

static Object Qexecute_raw_event_handler;  /* execute-raw-event-handler */

static Object Qstart_ui_command;   /* start-ui-command */

static Object Qexecute_simple_event_handler;  /* execute-simple-event-handler */

/* RUN-EVENT-HANDLER */
Object run_event_handler(event_interpretation,mouse_pointer)
    Object event_interpretation, mouse_pointer;
{
    Object namespace, name, pretty_name, event_handler_args, command_qm;
    Object frame_qm, index_of_top_of_backtrace_stack, temp, svref_arg_2;
    Object temp_1;
    Declare_special(3);
    Object result;

    x_note_fn_call(129,154);
    namespace = CONSP(event_interpretation) ? FIRST(event_interpretation) :
	     Qinternal;
    name = CONSP(event_interpretation) ? SECOND(event_interpretation) : 
	    event_interpretation;
    pretty_name = event_handler_pretty_name(name);
    event_handler_args = CONSP(event_interpretation) ? 
	    THIRD(event_interpretation) : Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Event_handler_args,Qevent_handler_args,event_handler_args,
	    2);
      command_qm = Nil;
      frame_qm = Nil;
      reference_mouse_pointer(mouse_pointer);
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
	    SVREF(temp,svref_arg_2) = pretty_name;
	}
	if (EQ(namespace,Quser)) {
	    frame_qm = most_interesting_frame(mouse_pointer);
	    if (frame_qm && name_of_user_menu_choice_qm(name,frame_qm)) {
		if (command_permitted_p(name,frame_qm)) {
		    index_of_top_of_backtrace_stack = 
			    Index_of_top_of_backtrace_stack;
		    PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			    0);
		      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
			      Size_of_basic_backtrace_information),
			      Maximum_index_in_backtrace_stack_for_internal_error)) 
				  {
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
			  SVREF(temp,svref_arg_2) = 
				  Qexecute_user_menu_choice_if_possible;
		      }
		      execute_user_menu_choice_if_possible(name,frame_qm);
		    POP_SPECIAL();
		}
	    }
	    else if (generic_name_of_exported_ui_command_qm(name)) {
		index_of_top_of_backtrace_stack = 
			Index_of_top_of_backtrace_stack;
		PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			0);
		  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
			  Size_of_basic_backtrace_information),
			  Maximum_index_in_backtrace_stack_for_internal_error)) 
			      {
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
		      SVREF(temp,svref_arg_2) = Qstart_generic_command;
		  }
		  start_generic_command(name,mouse_pointer);
		POP_SPECIAL();
	    }
	    else if (name_of_exported_event_handler_qm(name) && 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
		    Qnew_style_event_handler)) {
		index_of_top_of_backtrace_stack = 
			Index_of_top_of_backtrace_stack;
		PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			0);
		  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
			  Size_of_basic_backtrace_information),
			  Maximum_index_in_backtrace_stack_for_internal_error)) 
			      {
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
		      SVREF(temp,svref_arg_2) = Qexecute_raw_event_handler;
		  }
		  temp_1 = SYMBOL_FUNCTION(name);
		  FUNCALL_1(temp_1,mouse_pointer);
		POP_SPECIAL();
	    }
	    else;
	}
	else if (EQ(namespace,Qinternal)) {
	    command_qm = find_ui_command(1,name);
	    if (command_qm) {
		index_of_top_of_backtrace_stack = 
			Index_of_top_of_backtrace_stack;
		PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			0);
		  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
			  Size_of_basic_backtrace_information),
			  Maximum_index_in_backtrace_stack_for_internal_error)) 
			      {
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
		      SVREF(temp,svref_arg_2) = Qstart_ui_command;
		  }
		  start_ui_command(2,command_qm,mouse_pointer);
		POP_SPECIAL();
	    }
	    else if (getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
		    Qnew_style_event_handler)) {
		index_of_top_of_backtrace_stack = 
			Index_of_top_of_backtrace_stack;
		PUSH_SPECIAL_WITH_SYMBOL(Index_of_top_of_backtrace_stack,Qindex_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
			0);
		  if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
			  Size_of_basic_backtrace_information),
			  Maximum_index_in_backtrace_stack_for_internal_error)) 
			      {
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
		      SVREF(temp,svref_arg_2) = Qexecute_simple_event_handler;
		  }
		  temp_1 = SYMBOL_FUNCTION(name);
		  FUNCALL_1(temp_1,mouse_pointer);
		POP_SPECIAL();
	    }
	    else;
	}
      POP_SPECIAL();
      result = release_mouse_pointer_if_any(mouse_pointer);
    POP_SPECIAL();
    return result;
}

/* NOTHING */
Object nothing(mouse_pointer)
    Object mouse_pointer;
{
    x_note_fn_call(129,155);
    return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

/* PERMIT-GENERIC-UI-COMMAND-P */
Object permit_generic_ui_command_p(command)
    Object command;
{
    x_note_fn_call(129,156);
    return VALUES_1( !TRUEP(memq_function(ISVREF(command,(SI_Long)1L),
	    list_constant_8)) ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Listed_print_to_server_command, Qlisted_print_to_server_command);

static Object Qstart_generic;      /* start-generic */

static Object Qprint_to_server;    /* print-to-server */

static Object Qui_command_named;   /* ui-command-named */

static Object Qui_commands_with_menu_name;  /* ui-commands-with-menu-name */

static Object Qg2_defstruct_structure_name_partial_command_g2_struct;  /* g2-defstruct-structure-name::partial-command-g2-struct */

/* START-GENERIC-COMMAND */
Object start_generic_command(menu_name,mouse_pointer)
    Object menu_name, mouse_pointer;
{
    Object ui_command_context, car_arg, car_new_value, commands, command;
    Object ab_loop_list_, pc_qm, ab_loop_it_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, applicable_commands, menu_item_qm;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,157);
    ui_command_context = Qstart_generic;
    PUSH_SPECIAL_WITH_SYMBOL(Ui_command_context,Qui_command_context,ui_command_context,
	    0);
      if (EQ(menu_name,Qprint) && 
	      print_means_print_to_server_in_configurations_p()) {
	  if ( !TRUEP(CAR(Listed_print_to_server_command))) {
	      car_arg = Listed_print_to_server_command;
	      car_new_value = 
		      getfq_function_no_default(INLINE_SYMBOL_PLIST(Qprint_to_server),
		      Qui_command_named);
	      M_CAR(car_arg) = car_new_value;
	  }
	  commands = Listed_print_to_server_command;
      }
      else
	  commands = 
		  getfq_function_no_default(INLINE_SYMBOL_PLIST(menu_name),
		  Qui_commands_with_menu_name);
      command = Nil;
      ab_loop_list_ = commands;
      pc_qm = Nil;
      ab_loop_it_ = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      command = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      pc_qm = permit_generic_ui_command_p(command) ? 
	      make_initial_partial_command(command,mouse_pointer) : Qnil;
      ab_loop_it_ = pc_qm;
      if (ab_loop_it_) {
	  ab_loopvar__2 = slot_value_cons_1(ab_loop_it_,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
      }
      goto next_loop;
    end_loop:
      applicable_commands = ab_loopvar_;
      goto end_1;
      applicable_commands = Qnil;
    end_1:;
      menu_item_qm = Nil;
      if ( !TRUEP(commands))
	  result = VALUES_1(Nil);
      else if ( !TRUEP(applicable_commands))
	  result = VALUES_1(Nil);
      else if ( !TRUEP(command_permitted_p(menu_name,
	      most_interesting_frame(mouse_pointer))))
	  result = reclaim_menu_items(applicable_commands);
      else if (CONSP(applicable_commands) &&  
		  !TRUEP(CDR(applicable_commands))) {
	  pursue_partial_command(2,FIRST(applicable_commands),mouse_pointer);
	  result = reclaim_slot_value_list_1(applicable_commands);
      }
      else {
	  menu_item_qm = 
		  specific_menu_item_for_generic_command_qm(menu_name,
		  mouse_pointer);
	  if ( !TRUEP(menu_item_qm))
	      result = reclaim_menu_items(applicable_commands);
	  else if (SIMPLE_VECTOR_P(menu_item_qm) && EQ(ISVREF(menu_item_qm,
		  (SI_Long)0L),
		  Qg2_defstruct_structure_name_partial_command_g2_struct)) {
	      pursue_partial_command(2,menu_item_qm,mouse_pointer);
	      result = reclaim_menu_items(applicable_commands);
	  }
	  else {
	      reclaim_menu_item(menu_item_qm);
	      result = reclaim_menu_items(applicable_commands);
	  }
      }
    POP_SPECIAL();
    return result;
}

/* SPECIFIC-MENU-ITEM-FOR-GENERIC-COMMAND? */
Object specific_menu_item_for_generic_command_qm(menu_name,mouse_pointer)
    Object menu_name, mouse_pointer;
{
    Object menu_description_qm;

    x_note_fn_call(129,158);
    menu_description_qm = find_menu_for_spot(ISVREF(mouse_pointer,
	    (SI_Long)5L));
    if (menu_description_qm)
	return find_menu_item(menu_name,menu_description_qm,mouse_pointer,Nil);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_user_mode_alias = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_user_mode_aliass, Qchain_of_available_user_mode_aliass);

DEFINE_VARIABLE_WITH_SYMBOL(User_mode_alias_count, Quser_mode_alias_count);

Object Chain_of_available_user_mode_aliass_vector = UNBOUND;

/* USER-MODE-ALIAS-STRUCTURE-MEMORY-USAGE */
Object user_mode_alias_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(129,159);
    temp = User_mode_alias_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-USER-MODE-ALIAS-COUNT */
Object outstanding_user_mode_alias_count()
{
    Object def_structure_user_mode_alias_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(129,160);
    gensymed_symbol = IFIX(User_mode_alias_count);
    def_structure_user_mode_alias_variable = 
	    Chain_of_available_user_mode_aliass;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_user_mode_alias_variable))
	goto end_loop;
    def_structure_user_mode_alias_variable = 
	    ISVREF(def_structure_user_mode_alias_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-USER-MODE-ALIAS-1 */
Object reclaim_user_mode_alias_1(user_mode_alias)
    Object user_mode_alias;
{
    Object structure_being_reclaimed, managed_float, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(129,161);
    inline_note_reclaim_cons(user_mode_alias,Nil);
    structure_being_reclaimed = user_mode_alias;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      managed_float = ISVREF(user_mode_alias,(SI_Long)3L);
      reclaim_managed_simple_float_array_of_length_1(managed_float);
      SVREF(user_mode_alias,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_user_mode_aliass_vector,
	    IFIX(Current_thread_index));
    SVREF(user_mode_alias,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_user_mode_aliass_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = user_mode_alias;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-USER-MODE-ALIAS */
Object reclaim_structure_for_user_mode_alias(user_mode_alias)
    Object user_mode_alias;
{
    x_note_fn_call(129,162);
    return reclaim_user_mode_alias_1(user_mode_alias);
}

static Object Qg2_defstruct_structure_name_user_mode_alias_g2_struct;  /* g2-defstruct-structure-name::user-mode-alias-g2-struct */

/* MAKE-PERMANENT-USER-MODE-ALIAS-STRUCTURE-INTERNAL */
Object make_permanent_user_mode_alias_structure_internal()
{
    Object def_structure_user_mode_alias_variable;
    Object defstruct_g2_user_mode_alias_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(129,163);
    def_structure_user_mode_alias_variable = Nil;
    atomic_incff_symval(Quser_mode_alias_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_user_mode_alias_variable = Nil;
	gensymed_symbol = (SI_Long)5L;
	the_array = make_array(1,FIX(gensymed_symbol));
	i = (SI_Long)0L;
	ab_loop_bind_ = gensymed_symbol;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	ISVREF(the_array,i) = Nil;
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
	defstruct_g2_user_mode_alias_variable = the_array;
	SVREF(defstruct_g2_user_mode_alias_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_user_mode_alias_g2_struct;
	def_structure_user_mode_alias_variable = 
		defstruct_g2_user_mode_alias_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_user_mode_alias_variable);
}

/* MAKE-USER-MODE-ALIAS-1 */
Object make_user_mode_alias_1()
{
    Object def_structure_user_mode_alias_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(129,164);
    def_structure_user_mode_alias_variable = 
	    ISVREF(Chain_of_available_user_mode_aliass_vector,
	    IFIX(Current_thread_index));
    if (def_structure_user_mode_alias_variable) {
	svref_arg_1 = Chain_of_available_user_mode_aliass_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_user_mode_alias_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_user_mode_alias_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_user_mode_alias_g2_struct;
    }
    else
	def_structure_user_mode_alias_variable = 
		make_permanent_user_mode_alias_structure_internal();
    inline_note_allocate_cons(def_structure_user_mode_alias_variable,Nil);
    SVREF(def_structure_user_mode_alias_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_user_mode_alias_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_user_mode_alias_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_user_mode_alias_variable,FIX((SI_Long)4L)) = Nil;
    return VALUES_1(def_structure_user_mode_alias_variable);
}

/* WRITE-USER-MODE-ALIAS-FOR-KB */
Object write_user_mode_alias_for_kb(alias)
    Object alias;
{
    x_note_fn_call(129,165);
    write_char_for_kb(CHR('|'));
    write_element_for_kb(ISVREF(alias,(SI_Long)1L));
    write_element_for_kb(ISVREF(alias,(SI_Long)2L));
    write_element_for_kb(ISVREF(alias,(SI_Long)3L));
    return write_element_for_kb(ISVREF(alias,(SI_Long)4L));
}

/* READ-USER-MODE-ALIAS-FOR-KB */
Object read_user_mode_alias_for_kb()
{
    Object alias, svref_new_value;

    x_note_fn_call(129,166);
    alias = make_user_mode_alias_1();
    svref_new_value = read_element_for_kb(Nil);
    SVREF(alias,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = read_element_for_kb(Nil);
    SVREF(alias,FIX((SI_Long)2L)) = svref_new_value;
    svref_new_value = read_element_for_kb(Nil);
    SVREF(alias,FIX((SI_Long)3L)) = svref_new_value;
    svref_new_value = read_element_for_kb(Nil);
    SVREF(alias,FIX((SI_Long)4L)) = svref_new_value;
    return VALUES_1(alias);
}

static Object Qg2_user_mode_for_login;  /* g2-user-mode-for-login */

/* IS-USER-MODE-PRESENT */
Object is_user_mode_present(alias_name)
    Object alias_name;
{
    Object modes, mode, ab_loop_list_;

    x_note_fn_call(129,167);
    modes = compute_category_members(Qg2_user_mode_for_login);
    mode = Nil;
    ab_loop_list_ = modes;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mode = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(alias_name,mode))
	return VALUES_1(T);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object string_constant_57;  /* "Sorry, but alias or user mode with name ~a already exist." */

static Object string_constant_58;  /* "Sorry, but alias name ~a is incorrect because ~a" */

/* CHECK-ALIAS-FOR-POSSIBLE-NAME */
Object check_alias_for_possible_name(alias_name)
    Object alias_name;
{
    Object error_value;

    x_note_fn_call(129,168);
    if (is_user_mode_present(alias_name)) {
	notify_user(2,string_constant_57,alias_name);
	return VALUES_1(Nil);
    }
    error_value = validate_as_possible_user_mode(alias_name);
    if (error_value) {
	notify_user(3,string_constant_58,alias_name,
		string_for_localized_symbol(error_value));
	return VALUES_1(Nil);
    }
    return VALUES_1(T);
}

static Object list_constant_9;     /* # */

/* ADD-ALIAS-TO-CONFIGURATION */
Object add_alias_to_configuration(slot_name,frame,alias_name,alias_parent)
    Object slot_name, frame, alias_name, alias_parent;
{
    Object configuration, clause, ab_loop_list_, mode_restriction;
    Object ab_loop_list__1, mode_name, ab_loop_list__2;

    x_note_fn_call(129,169);
    configuration = copy_for_slot_value(get_slot_value_function(frame,
	    slot_name,Nil));
    clause = Nil;
    ab_loop_list_ = configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_9)) {
	mode_restriction = Nil;
	ab_loop_list__1 = CDR(clause);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	mode_restriction = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	mode_name = Nil;
	ab_loop_list__2 = SECOND(mode_restriction);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	mode_name = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if (EQ(mode_name,alias_parent)) {
	    nconc2(SECOND(mode_restriction),gensym_cons_1(alias_name,Nil));
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
      end_1:;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    return set_slot_value_function(frame,slot_name,configuration,Nil);
}

/* DELETE-ALIAS-FROM-CONFIGURATION */
Object delete_alias_from_configuration(slot_name,frame,alias_name)
    Object slot_name, frame, alias_name;
{
    Object configuration, clause, ab_loop_list_, mode_restriction;
    Object ab_loop_list__1, alias, ab_loop_list__2, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, alias_list;

    x_note_fn_call(129,170);
    configuration = copy_for_slot_value(get_slot_value_function(frame,
	    slot_name,Nil));
    clause = Nil;
    ab_loop_list_ = configuration;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_9)) {
	mode_restriction = Nil;
	ab_loop_list__1 = CDR(clause);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	mode_restriction = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	alias = Nil;
	ab_loop_list__2 = SECOND(mode_restriction);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	alias = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if ( !EQ(alias,alias_name)) {
	    ab_loopvar__2 = gensym_cons_1(alias,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_2;
      end_loop_2:
	alias_list = ab_loopvar_;
	goto end_1;
	alias_list = Qnil;
      end_1:;
	reclaim_gensym_list_1(SECOND(mode_restriction));
	M_SECOND(mode_restriction) = alias_list;
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    return set_slot_value_function(frame,slot_name,configuration,Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Kb_configuration, Qkb_configuration);

static Object Quser_mode_aliases;  /* user-mode-aliases */

static Object Qmain_menu_user_restrictions;  /* main-menu-user-restrictions */

static Object Qglobal_keyboard_command_user_restrictions;  /* global-keyboard-command-user-restrictions */

static Object Qobject_configuration;  /* object-configuration */

static Object Qinstance_configuration;  /* instance-configuration */

/* DELETE-EXISTED-ALIAS */
Object delete_existed_alias(alias_name)
    Object alias_name;
{
    Object aliases, alias, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, new_aliases, scope_conses, item;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(129,171);
    aliases = copy_for_slot_value(get_slot_value_function(Kb_configuration,
	    Quser_mode_aliases,Nil));
    alias = Nil;
    ab_loop_list_ = aliases;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    alias = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(alias_name,ISVREF(alias,(SI_Long)1L))) {
	ab_loopvar__2 = gensym_cons_1(alias,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    new_aliases = ab_loopvar_;
    goto end_1;
    new_aliases = Qnil;
  end_1:;
    reclaim_gensym_list_1(aliases);
    set_slot_value_function(Kb_configuration,Quser_mode_aliases,
	    new_aliases,Nil);
    add_or_delete_mode_name_from_directory_of_names(alias_name,T);
    delete_alias_from_configuration(Qmain_menu_user_restrictions,
	    Kb_configuration,alias_name);
    delete_alias_from_configuration(Qglobal_keyboard_command_user_restrictions,
	    Kb_configuration,alias_name);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    item = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qitem);
    next_loop_1:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_2:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_1;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_1;
	  goto next_loop_2;
	end_loop_1:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_2;
      item = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      delete_alias_from_configuration(Qobject_configuration,item,alias_name);
      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
	  delete_alias_from_configuration(Qinstance_configuration,item,
		  alias_name);
      goto next_loop_1;
    end_loop_2:;
    POP_SPECIAL();
    return VALUES_1(T);
}

/* COMPARE-ALIASES-RESTRICTIONS */
Object compare_aliases_restrictions(clauses,alias_name1,alias_name2)
    Object clauses, alias_name1, alias_name2;
{
    Object clause, ab_loop_list_, mode_restriction, ab_loop_list__1;
    Object alias1_present, alias2_present, mode_name, ab_loop_list__2;

    x_note_fn_call(129,172);
    clause = Nil;
    ab_loop_list_ = clauses;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(FIRST(clause),list_constant_9)) {
	mode_restriction = Nil;
	ab_loop_list__1 = CDR(clause);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	mode_restriction = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	alias1_present = Nil;
	alias2_present = Nil;
	mode_name = Nil;
	ab_loop_list__2 = SECOND(mode_restriction);
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	mode_name = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	if (EQ(mode_name,alias_name1))
	    alias1_present = T;
	if (EQ(mode_name,alias_name2))
	    alias2_present = T;
	goto next_loop_2;
      end_loop_2:;
	if ( !EQ(alias1_present,alias2_present))
	    return VALUES_1(Nil);
	goto next_loop_1;
      end_loop_1:;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(T);
}

/* COMPARE-ALIASES */
Object compare_aliases(alias1,alias2)
    Object alias1, alias2;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, item;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(129,173);
    if ( 
	    !TRUEP(compare_aliases_restrictions(get_lookup_slot_value_given_default(Kb_configuration,
	    Qmain_menu_user_restrictions,Nil),alias1,alias2))) {
	result = VALUES_1(Evaluation_false_value);
	goto end_compare_aliases;
    }
    if ( 
	    !TRUEP(compare_aliases_restrictions(get_lookup_slot_value_given_default(Kb_configuration,
	    Qglobal_keyboard_command_user_restrictions,Nil),alias1,alias2))) {
	result = VALUES_1(Evaluation_false_value);
	goto end_compare_aliases;
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
      if ( !TRUEP(compare_aliases_restrictions(get_lookup_slot_value(item,
	      Qobject_configuration),alias1,alias2))) {
	  result = VALUES_1(Evaluation_false_value);
	  POP_SPECIAL();
	  goto end_compare_aliases;
      }
      sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
      if (temp) {
	  if ( !TRUEP(compare_aliases_restrictions(ISVREF(item,
		  (SI_Long)23L),alias1,alias2))) {
	      result = VALUES_1(Evaluation_false_value);
	      POP_SPECIAL();
	      goto end_compare_aliases;
	  }
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    result = VALUES_1(Evaluation_true_value);
  end_compare_aliases:
    return result;
}

/* G2-ADD-ALIAS */
Object g2_add_alias(alias_name,parent_mode)
    Object alias_name, parent_mode;
{
    Object g2_login;

    x_note_fn_call(129,174);
    if ( !(is_user_mode_present(parent_mode) && 
	    check_alias_for_possible_name(alias_name)))
	return VALUES_1(Evaluation_false_value);
    g2_login = make_frame(Qg2_login);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_user_name_qm);
    set_lookup_slot_value_1(g2_login,Qg2_login_user_name_qm,alias_name);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(g2_login,Qg2_login_user_mode);
    set_lookup_slot_value_1(g2_login,Qg2_login_user_mode,parent_mode);
    make_new_alias(g2_login);
    return VALUES_1(Evaluation_true_value);
}

/* G2-DELETE-ALIAS */
Object g2_delete_alias(alias_name)
    Object alias_name;
{
    x_note_fn_call(129,175);
    if (delete_existed_alias(alias_name))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* IS-ALIAS-PRESENT */
Object is_alias_present(alias_name)
    Object alias_name;
{
    x_note_fn_call(129,176);
    if (is_user_mode_present(alias_name))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

static Object Qnew_attribute_description_format;  /* new-attribute-description-format */

static Object Qattribute_description_format;  /* attribute-description-format */

static Object Qfont_for_attribute_tables;  /* font-for-attribute-tables */

static Object Qnew_attributes_table_format;  /* new-attributes-table-format */

static Object Qattributes_table_format;  /* attributes-table-format */

static Object string_constant_59;  /* "Alias name" */

static Object string_constant_60;  /* "Parent user mode name" */

static Object string_constant_61;  /* "Date of alias creation" */

static Object string_constant_62;  /* "Who created the alias" */

static Object string_constant_63;  /* "User Mode Aliases" */

/* PUT-UP-ALIASES-TABLE */
Object put_up_aliases_table(user_mode_aliases)
    Object user_mode_aliases;
{
    Object cell_format, table_format, rows, table, user_mode_alias;
    Object ab_loop_list_, alias_name, parent_user_mode;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, date_of_alias_creation, who_created_the_alias, temp_1, temp_2;
    Object workspace;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(129,177);
    cell_format = New_g2_classic_ui_p ? Qnew_attribute_description_format :
	     
	    choose_font_format_per_fonts_table(Qattribute_description_format,
	    Qfont_for_attribute_tables);
    table_format = New_g2_classic_ui_p ? Qnew_attributes_table_format : 
	    Qattributes_table_format;
    rows = Nil;
    table = Nil;
    user_mode_alias = Nil;
    ab_loop_list_ = user_mode_aliases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    user_mode_alias = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    alias_name = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(2,
	    string_constant_28,ISVREF(user_mode_alias,(SI_Long)1L))),
	    cell_format);
    parent_user_mode = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(2,
	    string_constant_28,ISVREF(user_mode_alias,(SI_Long)2L))),
	    cell_format);
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
	      twrite_unix_time(1,ISVREF(user_mode_alias,(SI_Long)3L));
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    date_of_alias_creation = make_text_cell(2,
	    convert_text_string_to_text(temp),cell_format);
    who_created_the_alias = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(2,
	    string_constant_28,ISVREF(user_mode_alias,(SI_Long)4L))),
	    cell_format);
    rows = gensym_cons_1(gensym_list_4(alias_name,parent_user_mode,
	    date_of_alias_creation,who_created_the_alias),rows);
    goto next_loop;
  end_loop:;
    temp_1 = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(1,
	    string_constant_59)),cell_format);
    temp_2 = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(1,
	    string_constant_60)),cell_format);
    temp = make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(1,
	    string_constant_61)),cell_format);
    temp = gensym_list_4(temp_1,temp_2,temp,make_text_cell(2,
	    convert_text_string_to_text(tformat_text_string(1,
	    string_constant_62)),cell_format));
    rows = gensym_cons_1(temp,rows);
    table = make_or_reformat_table(3,rows,table_format,Nil);
    workspace = make_workspace(4,Qtemporary_workspace,Nil,table,
	    New_g2_classic_ui_p ? FIX((SI_Long)0L) : FIX((SI_Long)2L));
    if (New_g2_classic_ui_p)
	change_slot_value(3,workspace,Qworkspace_background_color_qm,
		get_ui_parameter(1,Qsystem_workspace_background_color));
    change_slot_value(3,workspace,Qtitle_bar_caption_text,
	    convert_text_string_to_text(copy_text_string(string_constant_63)));
    return post_workspace_in_pane_function(workspace,
	    Current_workstation_detail_pane,Nil,Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

void run_INIT()
{
    Object named_dynamic_extent_description, temp;
    Object reclaim_structure_for_block_near_mouse_cache_1, temp_1, temp_2;
    Object reclaim_structure_for_g2_login_state_1;
    Object clean_up_workstation_context_for_g2_login_state_1;
    Object valid_workstation_context_p_for_g2_login_state_1, gensymed_symbol;
    Object reclaim_structure_for_user_mode_alias_1;
    Object AB_package, Qis_alias_present;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qg2_delete_alias;
    Object Qg2_add_alias, Qcompare_aliases, Quser_interface, Qconfigure;
    Object Quser_mode_alias, Qreclaim_structure;
    Object Qoutstanding_user_mode_alias_count;
    Object Quser_mode_alias_structure_memory_usage, Qutilities2;
    Object string_constant_128, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_127, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qmove_selection;
    Object Qtransfer_selection, Qclone_selection, Qdelete_selection;
    Object Qselection_properties, Qselection_full_scale, Qnothing;
    Object Qselect_area, Quser_mouse_tracking, Qg2_reinstall_authorized_users;
    Object list_constant_10, Qformat_description, string_constant_126;
    Object Qinvisible_text_format, string_constant_125;
    Object Qmaximum_g2_password_length, Qminimum_g2_password_length;
    Object Qg2_set_maximum_login_attempts;
    Object Qmouse_down_on_otherwise_in_g2_login_state;
    Object Qmouse_down_on_subcommand_menu_button_in_g2_login_state;
    Object Qmouse_down_on_attribute_value_in_g2_login_state;
    Object Qenter_keys_in_g2_login_state, Qg2_login_state;
    Object Qvalid_workstation_context_p, list_constant_41;
    Object Qg2_login_second_new_password_qm, Qg2_login_first_new_password_qm;
    Object Qg2_login_old_password_qm, list_constant_40, list_constant_39;
    Object string_constant_124, list_constant_38, string_constant_123;
    Object string_constant_76, Qclean_up_workstation_context;
    Object string_constant_122, Qhandle_login_dialog_message;
    Object Qselection_style_of_workstation_context_type;
    Object Qtop_level_is_selection_style, Qoutstanding_g2_login_state_count;
    Object Qg2_login_state_structure_memory_usage, string_constant_121;
    Object string_constant_120, Qslot_value_writer;
    Object Qwrite_g2_login_comments_from_slot, string_constant_119;
    Object string_constant_118, string_constant_117, Qwrite_symbol_from_slot;
    Object Qg2_login_window_designation, string_constant_116;
    Object Quse_slot_value_compiler_for_default_overrides_p, Qname_qm;
    Object Qslot_value_compiler, Qcompile_name_qm_for_slot;
    Object string_constant_115, Qconfirm_new_password, Qnew_password;
    Object Qold_password, Qg2_window_specific_language;
    Object Qg2_window_name_or_class, string_constant_114, string_constant_113;
    Object string_constant_112, string_constant_111, list_constant_18;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103;
    Object Qmemory_management_table_text_cell_format_for_labels;
    Object string_constant_102;
    Object Qmemory_management_table_text_cell_format_for_headers;
    Object string_constant_101;
    Object Qmemory_management_table_text_cell_format_for_data;
    Object string_constant_100, Qmemory_management_table_format;
    Object Qslot_value_reclaimer;
    Object Qreclaim_status_table_frame_serial_number_value;
    Object Qstatus_table_frame_serial_number, Qrun, list_constant_37;
    Object list_constant_36, list_constant_35, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object list_constant_30, list_constant_29, list_constant_28;
    Object list_constant_27, list_constant_26, list_constant_25;
    Object string_constant_99, list_constant_24, string_constant_98;
    Object list_constant_23, string_constant_97, list_constant_22;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_92, list_constant_21;
    Object string_constant_91, string_constant_90, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object string_constant_85, string_constant_84, string_constant_83;
    Object Qspot_generator_for_help_table_format, Qtable_format_spot_generator;
    Object string_constant_82, Qclasses_which_define, Qresize;
    Object Qresize_for_icon_cell, Qcompute_minimum_bottom_edge;
    Object Qcompute_minimum_bottom_edge_for_icon_cell;
    Object Qcompute_minimum_right_edge;
    Object Qcompute_minimum_right_edge_for_icon_cell, Qdraw;
    Object Qdraw_for_icon_cell, string_constant_81, list_constant_20;
    Object string_constant_80, list_constant_19, Qsmall_gensym_logo;
    Object Qcreate_gensym_logo_description, string_constant_79;
    Object string_constant_78, string_constant_77, Qentity, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object Qspot_generator_for_credits_table_format, string_constant_68;
    Object list_constant_17, list_constant_16, list_constant_15;
    Object list_constant_14, array_constant_44, array_constant_45, Qgspan;
    Object Qget_gensym_logo_style, list_constant_13, Kfuncall;
    Object list_constant_12, Qall_optional_modules_for_display, Qgenerate_spot;
    Object Qworkspace, Qgenerate_spot_for_workspace, Qblock_near_mouse_cache;
    Object Qoutstanding_block_near_mouse_cache_count;
    Object Qblock_near_mouse_cache_structure_memory_usage, string_constant_67;
    Object string_constant_66, list_constant_11, Qedit_cursor;
    Object Qsmall_edit_cursor, Qnamed_dynamic_extent_description;
    Object string_constant_65, Qrun_top_level_event_handler;
    Object Qsystem_icon_title_string, Qsystem_window_title_string;
    Object string_constant_64, Qlaunch_ab, Qlaunch_function_qm;
    Object Qsystem_run_function, Qsystem_top_level_function;
    Object Qrun_ab_process_top_level;

    x_note_fn_call(129,178);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qab = STATIC_SYMBOL("AB",AB_package);
    Qrun_ab = STATIC_SYMBOL("RUN-AB",AB_package);
    Qrun_ab_process_top_level = STATIC_SYMBOL("RUN-AB-PROCESS-TOP-LEVEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrun_ab_process_top_level,
	    STATIC_FUNCTION(run_ab_process_top_level,NIL,FALSE,1,1));
    Qsystem_top_level_function = STATIC_SYMBOL("SYSTEM-TOP-LEVEL-FUNCTION",
	    AB_package);
    mutate_global_property(Qab,Qrun_ab_process_top_level,
	    Qsystem_top_level_function);
    Qsystem_run_function = STATIC_SYMBOL("SYSTEM-RUN-FUNCTION",AB_package);
    mutate_global_property(Qab,Qrun_ab,Qsystem_run_function);
    Qlaunch_function_qm = STATIC_SYMBOL("LAUNCH-FUNCTION\?",AB_package);
    Qlaunch_ab = STATIC_SYMBOL("LAUNCH-AB",AB_package);
    SET_SYMBOL_FUNCTION(Qlaunch_ab,STATIC_FUNCTION(launch_ab,NIL,FALSE,0,0));
    set_get(Qab,Qlaunch_function_qm,Qlaunch_ab);
    string_constant_64 = 
	    STATIC_STRING("Gensym G2 Real-Time Rule Engine - Server");
    Qsystem_window_title_string = 
	    STATIC_SYMBOL("SYSTEM-WINDOW-TITLE-STRING",AB_package);
    mutate_global_property(Qab,string_constant_64,Qsystem_window_title_string);
    string_constant_4 = STATIC_STRING("G2");
    Qsystem_icon_title_string = STATIC_SYMBOL("SYSTEM-ICON-TITLE-STRING",
	    AB_package);
    mutate_global_property(Qab,string_constant_4,Qsystem_icon_title_string);
    Qcatcher = STATIC_SYMBOL("CATCHER",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qside_effected_value = STATIC_SYMBOL("SIDE-EFFECTED-VALUE",AB_package);
    Quser_name = STATIC_SYMBOL("USER-NAME",AB_package);
    Qpassword = STATIC_SYMBOL("PASSWORD",AB_package);
    Qmd5_password = STATIC_SYMBOL("MD5-PASSWORD",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    if (Initial_java_class == UNBOUND)
	Initial_java_class = Nil;
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    Qtop_level_error_catcher = STATIC_SYMBOL("TOP-LEVEL-ERROR-CATCHER",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qwarn_user_of_previously_aborted_g2 = 
	    STATIC_SYMBOL("WARN-USER-OF-PREVIOUSLY-ABORTED-G2",AB_package);
    SET_SYMBOL_FUNCTION(Qwarn_user_of_previously_aborted_g2,
	    STATIC_FUNCTION(warn_user_of_previously_aborted_g2,NIL,FALSE,0,0));
    Qtask_to_warn_user_of_previously_aborted_g2 = 
	    STATIC_SYMBOL("TASK-TO-WARN-USER-OF-PREVIOUSLY-ABORTED-G2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrun_ab,STATIC_FUNCTION(run_ab,NIL,FALSE,1,1));
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    string_constant = STATIC_STRING("reset");
    Qpaused = STATIC_SYMBOL("PAUSED",AB_package);
    string_constant_1 = STATIC_STRING("paused");
    Qrunning = STATIC_SYMBOL("RUNNING",AB_package);
    string_constant_2 = STATIC_STRING("running");
    Qabort_g2 = STATIC_SYMBOL("ABORT",AB_package);
    string_constant_3 = STATIC_STRING("abort");
    array_constant_2 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
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
    Qcenter_origin = STATIC_SYMBOL("CENTER-ORIGIN",AB_package);
    list_constant = STATIC_LIST((SI_Long)9L,Qshift_left_ten_percent,
	    Qshift_right_ten_percent,Qshift_left_one_percent,
	    Qshift_right_one_percent,Qshift_up_ten_percent,
	    Qshift_down_ten_percent,Qshift_up_one_percent,
	    Qshift_down_one_percent,Qcenter_origin);
    Qriding_workspace_x_offset_qm = 
	    STATIC_SYMBOL("RIDING-WORKSPACE-X-OFFSET\?",AB_package);
    Qriding_workspace_y_offset_qm = 
	    STATIC_SYMBOL("RIDING-WORKSPACE-Y-OFFSET\?",AB_package);
    Qscale_workspace = STATIC_SYMBOL("SCALE-WORKSPACE",AB_package);
    Qmove_workspace = STATIC_SYMBOL("MOVE-WORKSPACE",AB_package);
    Qmove_workspaces_beyond_window_margin = 
	    STATIC_SYMBOL("MOVE-WORKSPACES-BEYOND-WINDOW-MARGIN",AB_package);
    Qscale_to_fit = STATIC_SYMBOL("SCALE-TO-FIT",AB_package);
    Qmaximum_scale_to_fit = STATIC_SYMBOL("MAXIMUM-SCALE-TO-FIT",AB_package);
    Qfull_scale = STATIC_SYMBOL("FULL-SCALE",AB_package);
    Qnormalized_full_scale = STATIC_SYMBOL("NORMALIZED-FULL-SCALE",AB_package);
    Qone_quarter_the_scale = STATIC_SYMBOL("ONE-QUARTER-THE-SCALE",AB_package);
    Qfour_times_the_scale = STATIC_SYMBOL("FOUR-TIMES-THE-SCALE",AB_package);
    Qtwenty_percent_smaller = STATIC_SYMBOL("TWENTY-PERCENT-SMALLER",
	    AB_package);
    Qtwenty_percent_bigger = STATIC_SYMBOL("TWENTY-PERCENT-BIGGER",AB_package);
    Qtwenty_percent_narrower = STATIC_SYMBOL("TWENTY-PERCENT-NARROWER",
	    AB_package);
    Qtwenty_percent_wider = STATIC_SYMBOL("TWENTY-PERCENT-WIDER",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)10L,Qscale_to_fit,
	    Qmaximum_scale_to_fit,Qfull_scale,Qnormalized_full_scale,
	    Qone_quarter_the_scale,Qfour_times_the_scale,
	    Qtwenty_percent_smaller,Qtwenty_percent_bigger,
	    Qtwenty_percent_narrower,Qtwenty_percent_wider);
    list_constant_2 = STATIC_LIST((SI_Long)8L,Qfull_scale,
	    Qnormalized_full_scale,Qone_quarter_the_scale,
	    Qfour_times_the_scale,Qtwenty_percent_smaller,
	    Qtwenty_percent_bigger,Qtwenty_percent_narrower,
	    Qtwenty_percent_wider);
    Qrun_top_level_event_handler = 
	    STATIC_SYMBOL("RUN-TOP-LEVEL-EVENT-HANDLER",AB_package);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qrun_top_level_event_handler,
	    Qrun_top_level_event_handler,Qnew_style_event_handler);
    Qtop_level = STATIC_SYMBOL("TOP-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qrun_top_level_event_handler,
	    STATIC_FUNCTION(run_top_level_event_handler,NIL,FALSE,1,1));
    Scalable_mouse_leeway = FIX((SI_Long)7L);
    Constant_mouse_leeway = FIX((SI_Long)3L);
    Minimum_x_scale_for_picking = FIX((SI_Long)1024L);
    Minimum_width_or_height_for_picking_in_window_units = FIX((SI_Long)3L);
    string_constant_65 = STATIC_STRING("FINDING-OBJECT-NEAR-MOUSE");
    if (Finding_object_near_mouse == UNBOUND)
	Finding_object_near_mouse = make_recursive_lock(2,Kname,
		string_constant_65);
    Qfinding_object_near_mouse = STATIC_SYMBOL("FINDING-OBJECT-NEAR-MOUSE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qfinding_object_near_mouse,
	    Finding_object_near_mouse);
    Qrun = STATIC_SYMBOL("RUN",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qfinding_object_near_mouse,
	    Qrun,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qfinding_object_near_mouse,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qtable = STATIC_SYMBOL("TABLE",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Kwithout_text = STATIC_SYMBOL("WITHOUT-TEXT",Pkeyword);
    Kjust_text = STATIC_SYMBOL("JUST-TEXT",Pkeyword);
    Ktight = STATIC_SYMBOL("TIGHT",Pkeyword);
    Qsmall_edit_cursor = STATIC_SYMBOL("SMALL-EDIT-CURSOR",AB_package);
    Qedit_cursor = STATIC_SYMBOL("EDIT-CURSOR",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qsmall_edit_cursor,
	    Qedit_cursor);
    Unselectable_classes_of_objects = list_constant_11;
    Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct = 
	    STATIC_SYMBOL("BLOCK-NEAR-MOUSE-CACHE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qblock_near_mouse_cache = STATIC_SYMBOL("BLOCK-NEAR-MOUSE-CACHE",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct,
	    Qblock_near_mouse_cache,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qblock_near_mouse_cache,
	    Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_block_near_mouse_cache == UNBOUND)
	The_type_description_of_block_near_mouse_cache = Nil;
    string_constant_66 = 
	    STATIC_STRING("43Dy8m83fOy1n83fOy8n8k1l8n0000001l1n8y83-2ty0k3Cyk0k0");
    temp = The_type_description_of_block_near_mouse_cache;
    The_type_description_of_block_near_mouse_cache = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_66));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_block_near_mouse_cache_g2_struct,
	    The_type_description_of_block_near_mouse_cache,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qblock_near_mouse_cache,
	    The_type_description_of_block_near_mouse_cache,
	    Qtype_description_of_type);
    Qoutstanding_block_near_mouse_cache_count = 
	    STATIC_SYMBOL("OUTSTANDING-BLOCK-NEAR-MOUSE-CACHE-COUNT",
	    AB_package);
    Qblock_near_mouse_cache_structure_memory_usage = 
	    STATIC_SYMBOL("BLOCK-NEAR-MOUSE-CACHE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_67 = STATIC_STRING("1q83fOy8s83-Kqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_block_near_mouse_cache_count);
    push_optimized_constant(Qblock_near_mouse_cache_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_67));
    Qchain_of_available_block_near_mouse_caches = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-BLOCK-NEAR-MOUSE-CACHES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_block_near_mouse_caches,
	    Chain_of_available_block_near_mouse_caches);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_block_near_mouse_caches,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qblock_near_mouse_cache_count = 
	    STATIC_SYMBOL("BLOCK-NEAR-MOUSE-CACHE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qblock_near_mouse_cache_count,
	    Block_near_mouse_cache_count);
    record_system_variable(Qblock_near_mouse_cache_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_block_near_mouse_caches_vector == UNBOUND)
	Chain_of_available_block_near_mouse_caches_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qblock_near_mouse_cache_structure_memory_usage,
	    STATIC_FUNCTION(block_near_mouse_cache_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_block_near_mouse_cache_count,
	    STATIC_FUNCTION(outstanding_block_near_mouse_cache_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_block_near_mouse_cache_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_block_near_mouse_cache,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qblock_near_mouse_cache,
	    reclaim_structure_for_block_near_mouse_cache_1);
    Qgenerate_spot_for_workspace = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-WORKSPACE",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_workspace,
	    STATIC_FUNCTION(generate_spot_for_workspace,NIL,FALSE,2,2));
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qgenerate_spot_for_workspace);
    set_get(Qworkspace,Qgenerate_spot,temp_1);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_1 = CONS(Qworkspace,temp);
    mutate_global_property(Qgenerate_spot,temp_1,Qclasses_which_define);
    Kxor = STATIC_SYMBOL("XOR",Pkeyword);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qworkspace_foreground = STATIC_SYMBOL("WORKSPACE-FOREGROUND",AB_package);
    Qframe_transforms_of_block = STATIC_SYMBOL("FRAME-TRANSFORMS-OF-BLOCK",
	    AB_package);
    Qall_optional_modules_for_display = 
	    STATIC_SYMBOL("ALL-OPTIONAL-MODULES-FOR-DISPLAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qall_optional_modules_for_display,
	    All_optional_modules_for_display);
    Qgsi = STATIC_SYMBOL("GSI",AB_package);
    list_constant_12 = STATIC_CONS(Qgsi,Qnil);
    SET_SYMBOL_VALUE(Qall_optional_modules_for_display,list_constant_12);
    Qent = STATIC_SYMBOL("ENT",AB_package);
    Qal = STATIC_SYMBOL("AL",AB_package);
    Qjp = STATIC_SYMBOL("JP",AB_package);
    Qjl = STATIC_SYMBOL("JL",AB_package);
    Qg1 = STATIC_SYMBOL("G1",AB_package);
    Qkorean = STATIC_SYMBOL("KOREAN",AB_package);
    Qnupec = STATIC_SYMBOL("NUPEC",AB_package);
    Qjapanese = STATIC_SYMBOL("JAPANESE",AB_package);
    Qchinese = STATIC_SYMBOL("CHINESE",AB_package);
    Qgfi = STATIC_SYMBOL("GFI",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qgensym_logo_style = STATIC_SYMBOL("GENSYM-LOGO-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_logo_style,Gensym_logo_style);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qget_gensym_logo_style = STATIC_SYMBOL("GET-GENSYM-LOGO-STYLE",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qget_gensym_logo_style);
    record_system_variable(Qgensym_logo_style,Qrun,list_constant_13,Qnil,
	    Qnil,Qnil,Qnil);
    array_constant_3 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)95L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)89L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    Qnew_large_with_tagline = STATIC_SYMBOL("NEW-LARGE-WITH-TAGLINE",
	    AB_package);
    array_constant_4 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    Qnew_small = STATIC_SYMBOL("NEW-SMALL",AB_package);
    array_constant_5 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    Qnew_large = STATIC_SYMBOL("NEW-LARGE",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    Qnew_large_2 = STATIC_SYMBOL("NEW-LARGE-2",AB_package);
    array_constant_7 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)87L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)11L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)12L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)13L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)16L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)17L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)18L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)19L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)20L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)21L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)31L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qold = STATIC_SYMBOL("OLD",AB_package);
    SET_SYMBOL_FUNCTION(Qget_gensym_logo_style,
	    STATIC_FUNCTION(get_gensym_logo_style,NIL,FALSE,0,0));
    string_constant_5 = STATIC_STRING("Gensym  G2");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_6 = STATIC_STRING("Multi-threading ");
    string_constant_7 = STATIC_STRING("G2~c with ");
    array_constant_44 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)0L,(SI_Long)8482L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_44,(SI_Long)7L,(SI_Long)57344L);
    list_constant_14 = STATIC_CONS(Qicp,array_constant_44);
    list_constant_15 = STATIC_CONS(Qgsi,array_constant_44);
    Qgspan = STATIC_SYMBOL("GSPAN",AB_package);
    array_constant_45 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)0L,(SI_Long)174L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_45,(SI_Long)7L,(SI_Long)57344L);
    list_constant_16 = STATIC_CONS(Qgspan,array_constant_45);
    list_constant_17 = STATIC_CONS(Qgfi,array_constant_44);
    list_constant_3 = STATIC_LIST((SI_Long)4L,list_constant_14,
	    list_constant_15,list_constant_16,list_constant_17);
    Qsystem_version = STATIC_SYMBOL("SYSTEM-VERSION",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    string_constant_8 = STATIC_STRING("~d.");
    array_constant_10 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    array_constant_12 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)13L,(SI_Long)85L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)16L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)23L,(SI_Long)57344L);
    array_constant_14 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    Interrim_no_mark_logo_p = T;
    string_constant_9 = STATIC_STRING(" Gensym  G2");
    Qprogram_title_format = STATIC_SYMBOL("PROGRAM-TITLE-FORMAT",AB_package);
    Qgensym_logo = STATIC_SYMBOL("GENSYM-LOGO",AB_package);
    Qnew_gensym_logo = STATIC_SYMBOL("NEW-GENSYM-LOGO",AB_package);
    Qlarge_new_gensym_logo = STATIC_SYMBOL("LARGE-NEW-GENSYM-LOGO",AB_package);
    Qlarge_new_gensym_logo_with_tagline = 
	    STATIC_SYMBOL("LARGE-NEW-GENSYM-LOGO-WITH-TAGLINE",AB_package);
    Qnew_large_logo_program_title_format = 
	    STATIC_SYMBOL("NEW-LARGE-LOGO-PROGRAM-TITLE-FORMAT",AB_package);
    Qnew_small_logo_program_title_format = 
	    STATIC_SYMBOL("NEW-SMALL-LOGO-PROGRAM-TITLE-FORMAT",AB_package);
    Qnew_small_logo_new_copyright_format = 
	    STATIC_SYMBOL("NEW-SMALL-LOGO-NEW-COPYRIGHT-FORMAT",AB_package);
    Qnew_copyright_format = STATIC_SYMBOL("NEW-COPYRIGHT-FORMAT",AB_package);
    Qnew_large_logo_new_copyright_format = 
	    STATIC_SYMBOL("NEW-LARGE-LOGO-NEW-COPYRIGHT-FORMAT",AB_package);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    Qfine_print_format = STATIC_SYMBOL("FINE-PRINT-FORMAT",AB_package);
    Qcredits_table_format = STATIC_SYMBOL("CREDITS-TABLE-FORMAT",AB_package);
    Kcredits_workspace_frame_style = 
	    STATIC_SYMBOL("CREDITS-WORKSPACE-FRAME-STYLE",Pkeyword);
    Knew_credits_workspace_frame_style = 
	    STATIC_SYMBOL("NEW-CREDITS-WORKSPACE-FRAME-STYLE",Pkeyword);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    string_constant_68 = STATIC_STRING("1r83*ny832Py83-Ry83=Dyk83=Nyk");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qcredits_table_format,
	    regenerate_optimized_constant(string_constant_68),
	    Qformat_description);
    Qspot_generator_for_credits_table_format = 
	    STATIC_SYMBOL("SPOT-GENERATOR-FOR-CREDITS-TABLE-FORMAT",
	    AB_package);
    Qtable_format_spot_generator = 
	    STATIC_SYMBOL("TABLE-FORMAT-SPOT-GENERATOR",AB_package);
    mutate_global_property(Qcredits_table_format,
	    Qspot_generator_for_credits_table_format,
	    Qtable_format_spot_generator);
    SET_SYMBOL_FUNCTION(Qspot_generator_for_credits_table_format,
	    STATIC_FUNCTION(spot_generator_for_credits_table_format,NIL,
	    FALSE,2,2));
    string_constant_69 = 
	    STATIC_STRING("13Ty83-Qy83-Ny83-Ry83-By083wy083byk83ay3Ry83Wy3Gy83cyk83kyk83ny1l83iQy83ty3-Wy83sy3-4y83uyk83-7y3a+y83*3y3S+y83*+y3q+y83iy35Ky");
    mutate_global_property(Qprogram_title_format,
	    regenerate_optimized_constant(string_constant_69),
	    Qformat_description);
    string_constant_70 = 
	    STATIC_STRING("13Ty83-Qy83-Ny838Ay83-By083wy083byk83ay3Gy83Wy3Gy83cy3Gy83kyk83ny1l83iQy83ty3-Wy83sy3-4y83uyk83-7y3a+y83*3y3S+y83*+y3q+y83iy35Ky");
    mutate_global_property(Qnew_small_logo_program_title_format,
	    regenerate_optimized_constant(string_constant_70),
	    Qformat_description);
    string_constant_71 = 
	    STATIC_STRING("13Ry83-Qy83-Ny838Ay83-By083wy083byk83ay3Gy83Wy3Gy83cy3Gy83kyk83ny1l83iQy83ty3-Wy83sy3-4y83uyk83-7y3a+y83*3y3S+y83*+y3q+y");
    mutate_global_property(Qnew_large_logo_program_title_format,
	    regenerate_optimized_constant(string_constant_71),
	    Qformat_description);
    string_constant_72 = 
	    STATIC_STRING("13Py83-Qy83-Ny83-Ry83byk83ayk83Wy3Gy83ayk83kyk83-=yz83iy38Sy83wy083ny1l83-uy83ty3Iy83sy3Ey83uym83-7y3C+y");
    mutate_global_property(Qnew_copyright_format,
	    regenerate_optimized_constant(string_constant_72),
	    Qformat_description);
    string_constant_73 = 
	    STATIC_STRING("13Py83-Qy83-Ny838Ay83byk83ayk83Wy3Gy83ayk83kyk83-=yz83iy38Sy83wy083ny1l83-uy83ty3Iy83sy3Ey83uym83-7y3C+y");
    mutate_global_property(Qnew_small_logo_new_copyright_format,
	    regenerate_optimized_constant(string_constant_73),
	    Qformat_description);
    string_constant_74 = 
	    STATIC_STRING("13Py83-Qy83-Ny838Ay83by3Ky83ayk83Wy3Ky83ayk83kyk83-=yz83iy38Sy83wy083ny1l83-uy83ty3Iy83sy3Ey83uym83-7y3C+y");
    mutate_global_property(Qnew_large_logo_new_copyright_format,
	    regenerate_optimized_constant(string_constant_74),
	    Qformat_description);
    string_constant_75 = 
	    STATIC_STRING("13Py83-Qy83-Ny83-Ry83by3Ky83ayq83Wy3Ky83cyu83kyk83-=yk83iy33my83wy083ny1l83-ry83tyz83syw83uyk83-7y3C+y");
    mutate_global_property(Qfine_print_format,
	    regenerate_optimized_constant(string_constant_75),
	    Qformat_description);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_18 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qgensym_logo,list_constant_18);
    string_constant_76 = STATIC_STRING("0");
    Qcreate_gensym_logo_description = 
	    STATIC_SYMBOL("CREATE-GENSYM-LOGO-DESCRIPTION",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_gensym_logo_description,
	    STATIC_FUNCTION(create_gensym_logo_description,NIL,FALSE,1,1));
    string_constant_77 = 
	    STATIC_STRING("1l4z8r8u8u838sy838sy01n8w9kq001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_78 = STATIC_STRING("1n8q1m838sy1l83-+y1m8u1n8w9kq");
    temp = regenerate_optimized_constant(string_constant_76);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_gensym_logo_description);
    temp_2 = regenerate_optimized_constant(string_constant_77);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_gensym_logo_description);
    add_class_to_environment(9,Qgensym_logo,list_constant_18,Nil,temp,Nil,
	    temp_2,list_constant_18,
	    regenerate_optimized_constant(string_constant_78),Nil);
    Qsmall_gensym_logo = STATIC_SYMBOL("SMALL-GENSYM-LOGO",AB_package);
    list_constant_19 = STATIC_CONS(Qgensym_logo,Qnil);
    check_if_superior_classes_are_defined(Qsmall_gensym_logo,list_constant_19);
    string_constant_79 = 
	    STATIC_STRING("1l4z8r8u8u83aSy83aSy01n8w9kl001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_80 = STATIC_STRING("1n8q1m83aSy1l838sy1m8u1n8w9kl");
    temp = regenerate_optimized_constant(string_constant_76);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_gensym_logo_description);
    temp_2 = regenerate_optimized_constant(string_constant_79);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_gensym_logo_description);
    add_class_to_environment(9,Qsmall_gensym_logo,list_constant_19,Nil,
	    temp,Nil,temp_2,list_constant_19,
	    regenerate_optimized_constant(string_constant_80),Nil);
    Qicon_cell = STATIC_SYMBOL("ICON-CELL",AB_package);
    list_constant_20 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qicon_cell,list_constant_20);
    string_constant_81 = STATIC_STRING("1m8q1m83-*My1l9k");
    temp = regenerate_optimized_constant(string_constant_76);
    temp_2 = regenerate_optimized_constant(string_constant_76);
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qicon_cell,list_constant_20,Nil,temp,Nil,
	    temp_2,list_constant_20,
	    regenerate_optimized_constant(string_constant_81),Nil);
    Icon_cell_class_description = 
	    lookup_global_or_kb_specific_property_value(Qicon_cell,
	    Class_description_gkbprop);
    Qdraw_for_icon_cell = STATIC_SYMBOL("DRAW-FOR-ICON-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qdraw_for_icon_cell,
	    STATIC_FUNCTION(draw_for_icon_cell,NIL,FALSE,1,1));
    Qdraw = STATIC_SYMBOL("DRAW",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qdraw_for_icon_cell);
    set_get(Qicon_cell,Qdraw,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdraw),
	    Qclasses_which_define);
    temp_1 = CONS(Qicon_cell,temp);
    mutate_global_property(Qdraw,temp_1,Qclasses_which_define);
    Qcompute_minimum_right_edge_for_icon_cell = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-RIGHT-EDGE-FOR-ICON-CELL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_minimum_right_edge_for_icon_cell,
	    STATIC_FUNCTION(compute_minimum_right_edge_for_icon_cell,NIL,
	    FALSE,1,1));
    Qcompute_minimum_right_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-RIGHT-EDGE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcompute_minimum_right_edge_for_icon_cell);
    set_get(Qicon_cell,Qcompute_minimum_right_edge,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcompute_minimum_right_edge),
	    Qclasses_which_define);
    temp_1 = CONS(Qicon_cell,temp);
    mutate_global_property(Qcompute_minimum_right_edge,temp_1,
	    Qclasses_which_define);
    Qcompute_minimum_bottom_edge_for_icon_cell = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-BOTTOM-EDGE-FOR-ICON-CELL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompute_minimum_bottom_edge_for_icon_cell,
	    STATIC_FUNCTION(compute_minimum_bottom_edge_for_icon_cell,NIL,
	    FALSE,1,1));
    Qcompute_minimum_bottom_edge = 
	    STATIC_SYMBOL("COMPUTE-MINIMUM-BOTTOM-EDGE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qcompute_minimum_bottom_edge_for_icon_cell);
    set_get(Qicon_cell,Qcompute_minimum_bottom_edge,temp_1);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcompute_minimum_bottom_edge),
	    Qclasses_which_define);
    temp_1 = CONS(Qicon_cell,temp);
    mutate_global_property(Qcompute_minimum_bottom_edge,temp_1,
	    Qclasses_which_define);
    Qresize_for_icon_cell = STATIC_SYMBOL("RESIZE-FOR-ICON-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qresize_for_icon_cell,
	    STATIC_FUNCTION(resize_for_icon_cell,NIL,FALSE,4,4));
    Qresize = STATIC_SYMBOL("RESIZE",AB_package);
    temp_1 = SYMBOL_FUNCTION(Qresize_for_icon_cell);
    set_get(Qicon_cell,Qresize,temp_1);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qresize),
	    Qclasses_which_define);
    temp_1 = CONS(Qicon_cell,temp);
    mutate_global_property(Qresize,temp_1,Qclasses_which_define);
    Qhelp_table_format = STATIC_SYMBOL("HELP-TABLE-FORMAT",AB_package);
    string_constant_82 = 
	    STATIC_STRING("1z83*ny83=wy083=Dyk83=Nyk8308yk830Ayk8309yk8307yk");
    mutate_global_property(Qhelp_table_format,
	    regenerate_optimized_constant(string_constant_82),
	    Qformat_description);
    Qspot_generator_for_help_table_format = 
	    STATIC_SYMBOL("SPOT-GENERATOR-FOR-HELP-TABLE-FORMAT",AB_package);
    mutate_global_property(Qhelp_table_format,
	    Qspot_generator_for_help_table_format,
	    Qtable_format_spot_generator);
    SET_SYMBOL_FUNCTION(Qspot_generator_for_help_table_format,
	    STATIC_FUNCTION(spot_generator_for_help_table_format,NIL,FALSE,
	    2,2));
    Qhelp_title_format = STATIC_SYMBOL("HELP-TITLE-FORMAT",AB_package);
    string_constant_83 = 
	    STATIC_STRING("13Py83-Qy83-By083wy83-cy83byn83aym83Wyv83cym83kyk83-=yu83ny1l83-ry83ty3Gy83sy3Cy83uyk83-7y3K+y83iy3=Ty");
    mutate_global_property(Qhelp_title_format,
	    regenerate_optimized_constant(string_constant_83),
	    Qformat_description);
    Qhelp_key_name_format = STATIC_SYMBOL("HELP-KEY-NAME-FORMAT",AB_package);
    string_constant_84 = 
	    STATIC_STRING("13Py83-Qy83-By083wy83-by83byn83aym83Wyv83cym83kyk83-=yu83ny1l83-ry83tyz83syw83uyk83-7y3K+y83iy3=Ty");
    mutate_global_property(Qhelp_key_name_format,
	    regenerate_optimized_constant(string_constant_84),
	    Qformat_description);
    Qhelp_key_binding_format = STATIC_SYMBOL("HELP-KEY-BINDING-FORMAT",
	    AB_package);
    string_constant_85 = 
	    STATIC_STRING("13Ny83-Qy83-By083byv83aym83Wyn83cym83kyk83-=y3Gy83ny1l83-ry83tyz83syw83uyk83-7y3K+y83iy31Qy");
    mutate_global_property(Qhelp_key_binding_format,
	    regenerate_optimized_constant(string_constant_85),
	    Qformat_description);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    Qmenu = STATIC_SYMBOL("MENU",AB_package);
    Qmenu_item = STATIC_SYMBOL("MENU-ITEM",AB_package);
    string_constant_10 = STATIC_STRING("~a ~a");
    array_constant_15 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    Qkeymap_named = STATIC_SYMBOL("KEYMAP-NAMED",AB_package);
    Qthick_workspace_frame_style = 
	    STATIC_SYMBOL("THICK-WORKSPACE-FRAME-STYLE",AB_package);
    Qspecial_character_help_text_cell_format = 
	    STATIC_SYMBOL("SPECIAL-CHARACTER-HELP-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_86 = 
	    STATIC_STRING("13Py83-Qy83-By083wy83*hy83byn83aym83Wyv83cym83kyk83-=yu83ny1l83-ry83ty3Ey83syz83uyk83-7y3K+y83iy3=Ty");
    mutate_global_property(Qspecial_character_help_text_cell_format,
	    regenerate_optimized_constant(string_constant_86),
	    Qformat_description);
    Qspecial_character_help_header_text_cell_format = 
	    STATIC_SYMBOL("SPECIAL-CHARACTER-HELP-HEADER-TEXT-CELL-FORMAT",
	    AB_package);
    string_constant_87 = 
	    STATIC_STRING("13Ty83-Qy83-By083wy83-cy83byn83ayp83Wyv83cyp83kyk83-=yu83-Ny83*2y83*Ky83fy83ny1l83-ry83ty3Ey83syz83uyk83-7y3K+y83iy3=4y");
    mutate_global_property(Qspecial_character_help_header_text_cell_format,
	    regenerate_optimized_constant(string_constant_87),
	    Qformat_description);
    Qchar_lesspw_function = STATIC_SYMBOL("CHAR-LESSPW-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qchar_lesspw_function,
	    STATIC_FUNCTION(char_lesspw_function,NIL,FALSE,2,2));
    array_constant_16 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)57344L);
    string_constant_11 = STATIC_STRING(" ");
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    string_constant_12 = STATIC_STRING("Alt+i ");
    string_constant_13 = STATIC_STRING("Alt+i");
    string_constant_14 = STATIC_STRING(" or ");
    string_constant_15 = STATIC_STRING(", or ");
    array_constant_20 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)57344L);
    array_constant_21 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)23L,(SI_Long)57344L);
    array_constant_22 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)23L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)24L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)27L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)32L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)33L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)38L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)39L,(SI_Long)57344L);
    string_constant_88 = STATIC_STRING("Grave");
    list_constant_26 = STATIC_LIST((SI_Long)2L,string_constant_88,
	    FIX((SI_Long)96L));
    string_constant_89 = STATIC_STRING("Acute");
    list_constant_27 = STATIC_LIST((SI_Long)2L,string_constant_89,
	    FIX((SI_Long)39L));
    string_constant_90 = STATIC_STRING("Circumflex");
    list_constant_28 = STATIC_LIST((SI_Long)2L,string_constant_90,
	    FIX((SI_Long)94L));
    string_constant_91 = STATIC_STRING("Umlaut");
    list_constant_21 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)58L),
	    FIX((SI_Long)34L));
    list_constant_29 = STATIC_LIST((SI_Long)2L,string_constant_91,
	    list_constant_21);
    string_constant_92 = STATIC_STRING("Tilde");
    list_constant_30 = STATIC_LIST((SI_Long)2L,string_constant_92,
	    FIX((SI_Long)126L));
    string_constant_93 = STATIC_STRING("Ligature");
    list_constant_31 = STATIC_LIST((SI_Long)2L,string_constant_93,
	    FIX((SI_Long)101L));
    string_constant_94 = STATIC_STRING("Slash");
    list_constant_32 = STATIC_LIST((SI_Long)2L,string_constant_94,
	    FIX((SI_Long)47L));
    string_constant_95 = STATIC_STRING("Cedilla");
    list_constant_33 = STATIC_LIST((SI_Long)2L,string_constant_95,
	    FIX((SI_Long)44L));
    string_constant_96 = STATIC_STRING("Ring");
    list_constant_22 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)79L),
	    FIX((SI_Long)111L),FIX((SI_Long)48L));
    list_constant_34 = STATIC_LIST((SI_Long)2L,string_constant_96,
	    list_constant_22);
    string_constant_97 = STATIC_STRING("Double Acute");
    list_constant_23 = STATIC_CONS(FIX((SI_Long)61L),Qnil);
    list_constant_35 = STATIC_LIST((SI_Long)2L,string_constant_97,
	    list_constant_23);
    string_constant_98 = STATIC_STRING("Breve");
    list_constant_24 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)85L),
	    FIX((SI_Long)117L));
    list_constant_36 = STATIC_LIST((SI_Long)2L,string_constant_98,
	    list_constant_24);
    string_constant_99 = STATIC_STRING("Dot Above");
    list_constant_25 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)73L),
	    FIX((SI_Long)105L));
    list_constant_37 = STATIC_LIST((SI_Long)2L,string_constant_99,
	    list_constant_25);
    list_constant_4 = STATIC_LIST((SI_Long)12L,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_33,list_constant_34,list_constant_35,
	    list_constant_36,list_constant_37);
    array_constant_27 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)24L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)25L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)28L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)29L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)57344L);
    Qkanji = STATIC_SYMBOL("KANJI",AB_package);
    Qhangul = STATIC_SYMBOL("HANGUL",AB_package);
    Qrussian = STATIC_SYMBOL("RUSSIAN",AB_package);
    Qcyrillic = STATIC_SYMBOL("CYRILLIC",AB_package);
    Qunicode = STATIC_SYMBOL("UNICODE",AB_package);
    string_constant_16 = STATIC_STRING("Hangul (KS C 5601)");
    string_constant_17 = STATIC_STRING("Cyrillic (ISO 8859-5)");
    string_constant_18 = STATIC_STRING("Kanji (JIS)");
    string_constant_19 = STATIC_STRING("Unicode 2.0");
    string_constant_20 = STATIC_STRING("For ~a");
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qjapanese,Qkorean,Qrussian);
    string_constant_21 = STATIC_STRING("Unicode");
    string_constant_22 = 
	    STATIC_STRING("Enter Alt+i followed by a ~d-digit ~a hex code.  ~\n             ~%Precede with x to force hex interpretation if ~\n             the first digit is ambiguous. - e.g. \"xC49A\"");
    if (Inside_breakpoint_p == UNBOUND)
	Inside_breakpoint_p = Nil;
    Qreturn_from_breakpoint_task = 
	    STATIC_SYMBOL("RETURN-FROM-BREAKPOINT-TASK",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qreturn_from_breakpoint_task,
	    Return_from_breakpoint_task);
    record_system_variable(Qreturn_from_breakpoint_task,Qrun,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qreturn_from_breakpoint = STATIC_SYMBOL("RETURN-FROM-BREAKPOINT",
	    AB_package);
    Qimmediately_return_from_breakpoint = 
	    STATIC_SYMBOL("IMMEDIATELY-RETURN-FROM-BREAKPOINT",AB_package);
    SET_SYMBOL_FUNCTION(Qimmediately_return_from_breakpoint,
	    STATIC_FUNCTION(immediately_return_from_breakpoint,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qreturn_from_breakpoint,
	    STATIC_FUNCTION(return_from_breakpoint,NIL,TRUE,0,1));
    string_constant_23 = 
	    STATIC_STRING("Disabling debugging by changing the \"Tracing and breakpoints enabled\?\" ~\n     debugging parameter to \"no\".  Please edit the debugging parameters to ~\n     reenable debugging.");
    Qmessage_and_breakpoint_overrides = 
	    STATIC_SYMBOL("MESSAGE-AND-BREAKPOINT-OVERRIDES",AB_package);
    if (Allow_debugger_pause == UNBOUND)
	Allow_debugger_pause = T;
    if (Show_procedure_invocation_hierarchy_on_debugger_pause_p == UNBOUND)
	Show_procedure_invocation_hierarchy_on_debugger_pause_p = T;
    if (Computation_instance_at_breakpoint == UNBOUND)
	Computation_instance_at_breakpoint = Nil;
    if (Computation_frame_at_breakpoint == UNBOUND)
	Computation_frame_at_breakpoint = Nil;
    if (All_computation_instances_above_breakpoint == UNBOUND)
	All_computation_instances_above_breakpoint = Nil;
    if (May_return_from_breakpoint == UNBOUND)
	May_return_from_breakpoint = Nil;
    if (Pane_for_debugger_pause == UNBOUND)
	Pane_for_debugger_pause = Nil;
    string_constant_24 = 
	    STATIC_STRING("System will remain paused at this breakpoint.  ~\n                  Use \"Continue From Breakpoint\" to resume execution.");
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    if (Breakpoints_enabled_p == UNBOUND)
	Breakpoints_enabled_p = T;
    Qg2_defstruct_structure_name_halt_info_g2_struct = 
	    STATIC_SYMBOL("HALT-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug 
	    == UNBOUND)
	Result_of_enter_dialog_for_t2_for_pause_for_internal_error_or_debug 
		= Nil;
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qbreakpoint_message = STATIC_SYMBOL("BREAKPOINT-MESSAGE",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    array_constant_28 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)16L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)57344L);
    Qdisable_debugging = STATIC_SYMBOL("DISABLE-DEBUGGING",AB_package);
    array_constant_29 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)57344L);
    array_constant_30 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)15L,(SI_Long)57344L);
    Qab_continue = STATIC_SYMBOL("CONTINUE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qitem_causing_breakpoint = STATIC_SYMBOL("ITEM-CAUSING-BREAKPOINT",
	    AB_package);
    Qabort_message = STATIC_SYMBOL("ABORT-MESSAGE",AB_package);
    array_constant_31 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)57344L);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qbreakpoint = STATIC_SYMBOL("BREAKPOINT",AB_package);
    Qinternal_error = STATIC_SYMBOL("INTERNAL-ERROR",AB_package);
    Qfinish_dialog_for_pause_for_internal_error_or_debug = 
	    STATIC_SYMBOL("FINISH-DIALOG-FOR-PAUSE-FOR-INTERNAL-ERROR-OR-DEBUG",
	    AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qdebugger_pause = STATIC_SYMBOL("DEBUGGER-PAUSE",AB_package);
    SET_SYMBOL_FUNCTION(Qdebugger_pause,STATIC_FUNCTION(debugger_pause,NIL,
	    FALSE,1,1));
    Qadditional = STATIC_SYMBOL("ADDITIONAL",AB_package);
    Qcancel = STATIC_SYMBOL("CANCEL",AB_package);
    Qdebugger_disable_debugging = 
	    STATIC_SYMBOL("DEBUGGER-DISABLE-DEBUGGING",AB_package);
    SET_SYMBOL_FUNCTION(Qdebugger_disable_debugging,
	    STATIC_FUNCTION(debugger_disable_debugging,NIL,FALSE,0,0));
    array_constant_32 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)5L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)21L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)24L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)25L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_32,(SI_Long)31L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("G2 Break in ~NF");
    string_constant_26 = STATIC_STRING(", line ~d");
    string_constant_27 = STATIC_STRING(", instruction ~d");
    Qsource_stepping = STATIC_SYMBOL("SOURCE-STEPPING",AB_package);
    Qbreakpoints = STATIC_SYMBOL("BREAKPOINTS",AB_package);
    Qtab_width = STATIC_SYMBOL("TAB-WIDTH",AB_package);
    SET_SYMBOL_FUNCTION(Qfinish_dialog_for_pause_for_internal_error_or_debug,
	    STATIC_FUNCTION(finish_dialog_for_pause_for_internal_error_or_debug,
	    NIL,FALSE,2,2));
    Qg2_set_g2_state = STATIC_SYMBOL("G2-SET-G2-STATE",AB_package);
    array_constant_33 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)0L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)1L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)22L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)28L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)35L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)36L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)37L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)41L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)42L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)43L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)44L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)46L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)47L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)48L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)49L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)50L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)51L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)52L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)54L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)55L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)62L,(SI_Long)56L);
    UBYTE_16_ISASET_1(array_constant_33,(SI_Long)63L,(SI_Long)57344L);
    Qstatus_table_frame_serial_number = 
	    STATIC_SYMBOL("STATUS-TABLE-FRAME-SERIAL-NUMBER",AB_package);
    Qreclaim_status_table_frame_serial_number_value = 
	    STATIC_SYMBOL("RECLAIM-STATUS-TABLE-FRAME-SERIAL-NUMBER-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_status_table_frame_serial_number_value,
	    STATIC_FUNCTION(reclaim_status_table_frame_serial_number_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qstatus_table_frame_serial_number,
	    SYMBOL_FUNCTION(Qreclaim_status_table_frame_serial_number_value),
	    Qslot_value_reclaimer);
    Qmemory_management_table_format = 
	    STATIC_SYMBOL("MEMORY-MANAGEMENT-TABLE-FORMAT",AB_package);
    string_constant_100 = 
	    STATIC_STRING("1z83*ny83=wy083=Dyk83=Nyl8308yl830Ayl8309yl8307yl");
    mutate_global_property(Qmemory_management_table_format,
	    regenerate_optimized_constant(string_constant_100),
	    Qformat_description);
    Qmemory_management_table_text_cell_format_for_data = 
	    STATIC_SYMBOL("MEMORY-MANAGEMENT-TABLE-TEXT-CELL-FORMAT-FOR-DATA",
	    AB_package);
    string_constant_101 = 
	    STATIC_STRING("1x83-Qy83wy83-by83kyk83byn83ayn83Wyn83cyn");
    mutate_global_property(Qmemory_management_table_text_cell_format_for_data,
	    regenerate_optimized_constant(string_constant_101),
	    Qformat_description);
    Qmemory_management_table_text_cell_format_for_headers = 
	    STATIC_SYMBOL("MEMORY-MANAGEMENT-TABLE-TEXT-CELL-FORMAT-FOR-HEADERS",
	    AB_package);
    string_constant_102 = 
	    STATIC_STRING("13Dy83-Qy83wy83-cy83kyk83-Ny083*Ky083byn83ayn83Wyn83cyn");
    mutate_global_property(Qmemory_management_table_text_cell_format_for_headers,
	    regenerate_optimized_constant(string_constant_102),
	    Qformat_description);
    Qmemory_management_table_text_cell_format_for_labels = 
	    STATIC_SYMBOL("MEMORY-MANAGEMENT-TABLE-TEXT-CELL-FORMAT-FOR-LABELS",
	    AB_package);
    string_constant_103 = 
	    STATIC_STRING("1x83-Qy83wy083kyk83byr83ayn83Wyp83cyn");
    mutate_global_property(Qmemory_management_table_text_cell_format_for_labels,
	    regenerate_optimized_constant(string_constant_103),
	    Qformat_description);
    if (Doing_password_change_p == UNBOUND)
	Doing_password_change_p = Nil;
    Qchanging_mode = STATIC_SYMBOL("CHANGING-MODE",AB_package);
    Qpassword_change = STATIC_SYMBOL("PASSWORD-CHANGE",AB_package);
    Qg2_login = STATIC_SYMBOL("G2-LOGIN",AB_package);
    check_if_superior_classes_are_defined(Qg2_login,list_constant_18);
    string_constant_104 = 
	    STATIC_STRING("13Dy4z8r83C8y83C8y838Uy838Uy00001p1l8l1m8p83C8y1l83Ey1l83Fy1l83-3y000004z8r83NDy83NDy838Uy838Uy00001n1m8p83E*y1l83Ey1l8l000004z8");
    string_constant_105 = 
	    STATIC_STRING("r83NEy83NEy838Uy838Uy00001n1m8p831ny1l83Ey1l8l000004z8r83NCy83NCy838Uy838Uy00001n1m8p831=y1l83Ey1l8l000004z8r83NFy83NFy838Uy838U");
    string_constant_106 = 
	    STATIC_STRING("y00001n1m8p83C9y1l8o1l8l000004z8r83NAy83NAy838Uy838Uy00001n1m8p831fy1l8o1l8l000004z8r83NBy83NBy838Uy838Uy00001n1m8p830Ky1l8o1l8l");
    string_constant_107 = 
	    STATIC_STRING("000004z8r83N6y83N6y838Uy838Uy00001n1m8p01l8o1l8l000004z8r83N0y83N0y838Uy838Uy0k001m1l83Ey1l8l000004z8r83N2y83N2y838Uy838Uy00001m");
    string_constant_108 = 
	    STATIC_STRING("1l8o1l8l000004z8r83N5y83N5y838Uy838Uy00001m1l8o1l8l000004z8r83N7y83N7y838Uy838Uy00001n1m8p831ny1l8o1l8l000004z8r83N1y83N1y838Uy8");
    string_constant_109 = 
	    STATIC_STRING("38Uy00001n1m8p831ny1l8o1l8l000004z8r83N4y83N4y838Uy838Uy00001n1m8p831ny1l8o1l8l000004z8r83N3y83N3y838Uy838Uy00001m1l8o1l8l000004");
    string_constant_110 = 
	    STATIC_STRING("z8r83N9y83N9y838Uy838Uy00001n1m8p831ny1l8o1l8l000004z8r83N8y83N8y838Uy838Uy00001m1l8o1l8l00000");
    string_constant_111 = 
	    STATIC_STRING("13Fy8q1m838Uy1l83-+y1q83C8y01m8p83C8y83Ey83Fy83-3y1p83NDy01m8p83E*y83Ey8l1p83NEy01m8p831ny83Ey8l1p83NCy01m8p831=y83Ey8l1p83NFy01");
    string_constant_112 = 
	    STATIC_STRING("m8p83C9y8o8l1p83NAy01m8p831fy8o8l1p83NBy01m8p830Ky8o8l1p83N6y01m8p08o8l1o83N0yk83Ey8l1o83N2y08o8l1o83N5y08o8l1p83N7y01m8p831ny8o");
    string_constant_113 = 
	    STATIC_STRING("8l1p83N1y01m8p831ny8o8l1p83N4y01m8p831ny8o8l1o83N3y08o8l1p83N9y01m8p831ny8o8l1o83N8y08o8l");
    temp = regenerate_optimized_constant(string_constant_76);
    temp_2 = regenerate_optimized_constant(list(7,string_constant_104,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110));
    add_class_to_environment(9,Qg2_login,list_constant_18,Nil,temp,Nil,
	    temp_2,list_constant_18,
	    regenerate_optimized_constant(LIST_3(string_constant_111,
	    string_constant_112,string_constant_113)),Nil);
    G2_login_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_login,
	    Class_description_gkbprop);
    string_constant_114 = STATIC_STRING("1l1m83C8y1m9k83-S-y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_114));
    Qg2_login_user_name_qm = STATIC_SYMBOL("G2-LOGIN-USER-NAME\?",AB_package);
    alias_slot_name(3,Qg2_login_user_name_qm,Quser_name,Qg2_login);
    Qg2_login_user_password_qm = STATIC_SYMBOL("G2-LOGIN-USER-PASSWORD\?",
	    AB_package);
    alias_slot_name(3,Qg2_login_user_password_qm,Qpassword,Qg2_login);
    Qg2_login_user_mode = STATIC_SYMBOL("G2-LOGIN-USER-MODE",AB_package);
    Qg2_user_mode = STATIC_SYMBOL("G2-USER-MODE",AB_package);
    alias_slot_name(3,Qg2_login_user_mode,Qg2_user_mode,Qg2_login);
    Qg2_login_window_name_or_class = 
	    STATIC_SYMBOL("G2-LOGIN-WINDOW-NAME-OR-CLASS",AB_package);
    Qg2_window_name_or_class = STATIC_SYMBOL("G2-WINDOW-NAME-OR-CLASS",
	    AB_package);
    alias_slot_name(3,Qg2_login_window_name_or_class,
	    Qg2_window_name_or_class,Qg2_login);
    Qg2_login_specific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("G2-LOGIN-SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",
	    AB_package);
    Qg2_window_specific_language = 
	    STATIC_SYMBOL("G2-WINDOW-SPECIFIC-LANGUAGE",AB_package);
    alias_slot_name(3,Qg2_login_specific_language_for_this_g2_window_qm,
	    Qg2_window_specific_language,Qg2_login);
    Qg2_login_style_specifically_for_this_workstation_qm = 
	    STATIC_SYMBOL("G2-LOGIN-STYLE-SPECIFICALLY-FOR-THIS-WORKSTATION\?",
	    AB_package);
    Qg2_window_style = STATIC_SYMBOL("G2-WINDOW-STYLE",AB_package);
    alias_slot_name(3,Qg2_login_style_specifically_for_this_workstation_qm,
	    Qg2_window_style,Qg2_login);
    Qg2_login_init_string_qm = STATIC_SYMBOL("G2-LOGIN-INIT-STRING\?",
	    AB_package);
    Qinit_string = STATIC_SYMBOL("INIT-STRING",AB_package);
    alias_slot_name(3,Qg2_login_init_string_qm,Qinit_string,Qg2_login);
    Qg2_login_old_password_qm = STATIC_SYMBOL("G2-LOGIN-OLD-PASSWORD\?",
	    AB_package);
    Qold_password = STATIC_SYMBOL("OLD-PASSWORD",AB_package);
    alias_slot_name(3,Qg2_login_old_password_qm,Qold_password,Qg2_login);
    Qg2_login_first_new_password_qm = 
	    STATIC_SYMBOL("G2-LOGIN-FIRST-NEW-PASSWORD\?",AB_package);
    Qnew_password = STATIC_SYMBOL("NEW-PASSWORD",AB_package);
    alias_slot_name(3,Qg2_login_first_new_password_qm,Qnew_password,Qg2_login);
    Qg2_login_second_new_password_qm = 
	    STATIC_SYMBOL("G2-LOGIN-SECOND-NEW-PASSWORD\?",AB_package);
    Qconfirm_new_password = STATIC_SYMBOL("CONFIRM-NEW-PASSWORD",AB_package);
    alias_slot_name(3,Qg2_login_second_new_password_qm,
	    Qconfirm_new_password,Qg2_login);
    string_constant_115 = STATIC_STRING("1m1m83E*y83-2y1m83E*y1m9k83Zy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_115));
    Qname_qm = STATIC_SYMBOL("NAME\?",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qname_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qcompile_name_qm_for_slot = STATIC_SYMBOL("COMPILE-NAME\?-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_name_qm_for_slot,
	    STATIC_FUNCTION(compile_name_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qname_qm,
	    SYMBOL_FUNCTION(Qcompile_name_qm_for_slot),Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qname_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_116 = STATIC_STRING("1m1m83C9y83xiy1m83C9y83xgy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_116));
    Qg2_login_window_designation = 
	    STATIC_SYMBOL("G2-LOGIN-WINDOW-DESIGNATION",AB_package);
    mutate_global_property(Qg2_login_window_designation,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    string_constant_28 = STATIC_STRING("~a");
    string_constant_117 = STATIC_STRING("1l1m83a3y1m9k83-VQy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_117));
    Qg2_login_prompt = STATIC_SYMBOL("G2-LOGIN-PROMPT",AB_package);
    string_constant_29 = STATIC_STRING("Please modify user settings.");
    string_constant_118 = STATIC_STRING("1l1m83a3y1m9k83-VFy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_118));
    Qg2_alias_prompt = STATIC_SYMBOL("G2-ALIAS-PROMPT",AB_package);
    string_constant_30 = STATIC_STRING("Please enter user mode alias.");
    string_constant_119 = STATIC_STRING("1l1m83a3y1m9k83-VUy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_119));
    Qg2_password_change_prompt = STATIC_SYMBOL("G2-PASSWORD-CHANGE-PROMPT",
	    AB_package);
    string_constant_31 = STATIC_STRING("Change your password.");
    Qpassword_change_dialog = STATIC_SYMBOL("PASSWORD-CHANGE-DIALOG",
	    AB_package);
    Qsimple_message = STATIC_SYMBOL("SIMPLE-MESSAGE",AB_package);
    string_constant_32 = STATIC_STRING("~a~%");
    Qab_simple_condition = STATIC_SYMBOL("SIMPLE-CONDITION",AB_package);
    Qg2_login_dialog = STATIC_SYMBOL("G2-LOGIN-DIALOG",AB_package);
    Qalias_creation = STATIC_SYMBOL("ALIAS-CREATION",AB_package);
    Qg2_login_comments = STATIC_SYMBOL("G2-LOGIN-COMMENTS",AB_package);
    Qwrite_g2_login_comments_from_slot = 
	    STATIC_SYMBOL("WRITE-G2-LOGIN-COMMENTS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_g2_login_comments_from_slot,
	    STATIC_FUNCTION(write_g2_login_comments_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qg2_login_comments,
	    SYMBOL_FUNCTION(Qwrite_g2_login_comments_from_slot),
	    Qslot_value_writer);
    Qg2_defstruct_structure_name_g2_login_state_g2_struct = 
	    STATIC_SYMBOL("G2-LOGIN-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_login_state = STATIC_SYMBOL("G2-LOGIN-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_g2_login_state_g2_struct,
	    Qg2_login_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qg2_login_state,
	    Qg2_defstruct_structure_name_g2_login_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_g2_login_state == UNBOUND)
	The_type_description_of_g2_login_state = Nil;
    string_constant_120 = 
	    STATIC_STRING("43Dy8m83hby1o83hby83-Sy8n8k1l83-Sy0000001m1n8y83-3oy1p838Uy83xZy83xay83-=Fy83xYy1m8x83-Syksk0k0");
    temp = The_type_description_of_g2_login_state;
    The_type_description_of_g2_login_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_120));
    mutate_global_property(Qg2_defstruct_structure_name_g2_login_state_g2_struct,
	    The_type_description_of_g2_login_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qg2_login_state,
	    The_type_description_of_g2_login_state,Qtype_description_of_type);
    Qoutstanding_g2_login_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-G2-LOGIN-STATE-COUNT",AB_package);
    Qg2_login_state_structure_memory_usage = 
	    STATIC_SYMBOL("G2-LOGIN-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_121 = STATIC_STRING("1q83hby8s83-VRy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_g2_login_state_count);
    push_optimized_constant(Qg2_login_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_121));
    Qchain_of_available_g2_login_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-G2-LOGIN-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_g2_login_states,
	    Chain_of_available_g2_login_states);
    record_system_variable(Qchain_of_available_g2_login_states,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qg2_login_state_count = STATIC_SYMBOL("G2-LOGIN-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2_login_state_count,G2_login_state_count);
    record_system_variable(Qg2_login_state_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_g2_login_states_vector == UNBOUND)
	Chain_of_available_g2_login_states_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qg2_login_state_structure_memory_usage,
	    STATIC_FUNCTION(g2_login_state_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_g2_login_state_count,
	    STATIC_FUNCTION(outstanding_g2_login_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_g2_login_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_g2_login_state,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qg2_login_state,
	    reclaim_structure_for_g2_login_state_1);
    Qtop_level_is_selection_style = 
	    STATIC_SYMBOL("TOP-LEVEL-IS-SELECTION-STYLE",AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qg2_login_state,Qtop_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    make_context_description(Qg2_login,Qtop_level,Qt,Qnil);
    Qenter_keys_in_g2_login_state = 
	    STATIC_SYMBOL("ENTER-KEYS-IN-G2-LOGIN-STATE",AB_package);
    Qmouse_down_on_attribute_value_in_g2_login_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-ON-ATTRIBUTE-VALUE-IN-G2-LOGIN-STATE",
	    AB_package);
    Qmouse_down_on_subcommand_menu_button_in_g2_login_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-ON-SUBCOMMAND-MENU-BUTTON-IN-G2-LOGIN-STATE",
	    AB_package);
    Qmouse_down_on_otherwise_in_g2_login_state = 
	    STATIC_SYMBOL("MOUSE-DOWN-ON-OTHERWISE-IN-G2-LOGIN-STATE",
	    AB_package);
    Qhandle_login_dialog_message = 
	    STATIC_SYMBOL("HANDLE-LOGIN-DIALOG-MESSAGE",AB_package);
    string_constant_122 = 
	    STATIC_STRING("1p1n83GMy8k9k1n830Dy83Aoy9l1n830Dy83A0y9m1n830Dy8k9n1n395y8k9o");
    Qinternal = STATIC_SYMBOL("INTERNAL",AB_package);
    clear_optimized_constants();
    push_optimized_constant(Qenter_keys_in_g2_login_state);
    push_optimized_constant(Qmouse_down_on_attribute_value_in_g2_login_state);
    push_optimized_constant(Qmouse_down_on_subcommand_menu_button_in_g2_login_state);
    push_optimized_constant(Qmouse_down_on_otherwise_in_g2_login_state);
    push_optimized_constant(Qhandle_login_dialog_message);
    make_keymap(Qg2_login,Qg2_login,
	    regenerate_optimized_constant(string_constant_122),Qinternal,
	    Qnil,Qnil,Qnil,Qnil);
    add_keymap_to_workstation_context(Qg2_login,Qg2_login);
    Qclean_up_workstation_context = 
	    STATIC_SYMBOL("CLEAN-UP-WORKSTATION-CONTEXT",AB_package);
    Qlogged_in = STATIC_SYMBOL("LOGGED-IN",AB_package);
    Qchanging_kbs = STATIC_SYMBOL("CHANGING-KBS",AB_package);
    clean_up_workstation_context_for_g2_login_state_1 = 
	    STATIC_FUNCTION(clean_up_workstation_context_for_g2_login_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_workstation_context,
	    Qg2_login_state,clean_up_workstation_context_for_g2_login_state_1);
    Quser_settings_editor_workspace = 
	    STATIC_SYMBOL("USER-SETTINGS-EDITOR-WORKSPACE",AB_package);
    list_constant_38 = STATIC_CONS(Qtemporary_workspace,Qnil);
    check_if_superior_classes_are_defined(Quser_settings_editor_workspace,
	    list_constant_38);
    string_constant_123 = 
	    STATIC_STRING("1l4z8r83*Ly83*Ly83dgy83dgy0u001n1l8l1l8o1m8p83*7y00000");
    string_constant_124 = STATIC_STRING("1n8q1m83dgy1l8318y1m83*Lyu");
    temp = regenerate_optimized_constant(string_constant_76);
    temp_2 = regenerate_optimized_constant(string_constant_123);
    add_class_to_environment(9,Quser_settings_editor_workspace,
	    list_constant_38,Nil,temp,Nil,temp_2,list_constant_38,
	    regenerate_optimized_constant(string_constant_124),Nil);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qchanging_mode,
	    Qpassword_change,Qalias_creation);
    Qinitial_g2_user_mode_for_this_kb = 
	    STATIC_SYMBOL("INITIAL-G2-USER-MODE-FOR-THIS-KB",AB_package);
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    Qreloading = STATIC_SYMBOL("RELOADING",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    Qnew_password_must_be_at_least_4_characters_long = 
	    STATIC_SYMBOL("NEW-PASSWORD-MUST-BE-AT-LEAST-4-CHARACTERS-LONG",
	    AB_package);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qdisconnect = STATIC_SYMBOL("DISCONNECT",AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    string_constant_33 = STATIC_STRING("User Mode Alias Creation");
    string_constant_34 = STATIC_STRING("User Settings Editor");
    register_button_label_for_internationalization(Qcancel);
    register_button_label_for_internationalization(Qdisconnect);
    register_button_label_for_internationalization(Qend);
    list_constant_39 = STATIC_LIST((SI_Long)6L,Qg2_login_comments,
	    Qg2_login_user_name_qm,Qg2_login_user_password_qm,
	    Qg2_login_window_name_or_class,Qg2_login_user_mode,
	    Qg2_login_specific_language_for_this_g2_window_qm);
    G2_login_attributes_to_show = list_constant_39;
    list_constant_40 = STATIC_LIST((SI_Long)3L,Qg2_login_comments,
	    Qg2_login_user_name_qm,Qg2_login_user_mode);
    Alias_creation_attributes_to_show = list_constant_40;
    list_constant_41 = STATIC_LIST((SI_Long)5L,Qg2_login_comments,
	    Qg2_login_user_name_qm,Qg2_login_old_password_qm,
	    Qg2_login_first_new_password_qm,Qg2_login_second_new_password_qm);
    Password_change_attributes_to_show = list_constant_41;
    Qvalid_workstation_context_p = 
	    STATIC_SYMBOL("VALID-WORKSTATION-CONTEXT-P",AB_package);
    valid_workstation_context_p_for_g2_login_state_1 = 
	    STATIC_FUNCTION(valid_workstation_context_p_for_g2_login_state,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qvalid_workstation_context_p,
	    Qg2_login_state,valid_workstation_context_p_for_g2_login_state_1);
    mutate_global_property(Qenter_keys_in_g2_login_state,
	    Qenter_keys_in_g2_login_state,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qenter_keys_in_g2_login_state,
	    STATIC_FUNCTION(enter_keys_in_g2_login_state,NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_on_attribute_value_in_g2_login_state,
	    Qmouse_down_on_attribute_value_in_g2_login_state,
	    Qnew_style_event_handler);
    Quser_password = STATIC_SYMBOL("USER-PASSWORD",AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_down_on_attribute_value_in_g2_login_state,
	    STATIC_FUNCTION(mouse_down_on_attribute_value_in_g2_login_state,
	    NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_on_subcommand_menu_button_in_g2_login_state,
	    Qmouse_down_on_subcommand_menu_button_in_g2_login_state,
	    Qnew_style_event_handler);
    Qdo_g2_login_subcommand = STATIC_SYMBOL("DO-G2-LOGIN-SUBCOMMAND",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmouse_down_on_subcommand_menu_button_in_g2_login_state,
	    STATIC_FUNCTION(mouse_down_on_subcommand_menu_button_in_g2_login_state,
	    NIL,FALSE,1,1));
    mutate_global_property(Qmouse_down_on_otherwise_in_g2_login_state,
	    Qmouse_down_on_otherwise_in_g2_login_state,
	    Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qmouse_down_on_otherwise_in_g2_login_state,
	    STATIC_FUNCTION(mouse_down_on_otherwise_in_g2_login_state,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qdo_g2_login_subcommand,
	    STATIC_FUNCTION(do_g2_login_subcommand,NIL,FALSE,1,1));
    string_constant_35 = 
	    STATIC_STRING("Can not choose user mode to non-existend user mode");
    Qduplicate_new_password_required = 
	    STATIC_SYMBOL("DUPLICATE-NEW-PASSWORD-REQUIRED",AB_package);
    string_constant_36 = 
	    STATIC_STRING("Sorry, but parent user mode for this alias is incorrect.");
    Maximum_number_of_login_attempts_permitted_per_window = FIX((SI_Long)5L);
    Qg2_login_attempts_counter = STATIC_SYMBOL("G2-LOGIN-ATTEMPTS-COUNTER",
	    AB_package);
    Qg2_defstruct_structure_name_t2_nonce_data_g2_struct = 
	    STATIC_SYMBOL("T2-NONCE-DATA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_set_maximum_login_attempts = 
	    STATIC_SYMBOL("G2-SET-MAXIMUM-LOGIN-ATTEMPTS",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_set_maximum_login_attempts,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_set_maximum_login_attempts,
	    STATIC_FUNCTION(g2_set_maximum_login_attempts,NIL,FALSE,1,1));
    Quser_mode = STATIC_SYMBOL("USER-MODE",AB_package);
    Qlanguage = STATIC_SYMBOL("LANGUAGE",AB_package);
    Qwindow_style = STATIC_SYMBOL("WINDOW-STYLE",AB_package);
    Qminimum_g2_password_length = 
	    STATIC_SYMBOL("MINIMUM-G2-PASSWORD-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qminimum_g2_password_length,FIX((SI_Long)4L));
    Qmaximum_g2_password_length = 
	    STATIC_SYMBOL("MAXIMUM-G2-PASSWORD-LENGTH",AB_package);
    SET_SYMBOL_VALUE(Qmaximum_g2_password_length,FIX((SI_Long)499L));
    Qunknown_user = STATIC_SYMBOL("UNKNOWN-USER",AB_package);
    Qinitializing_the_password_of_user_with_existing_password = 
	    STATIC_SYMBOL("INITIALIZING-THE-PASSWORD-OF-USER-WITH-EXISTING-PASSWORD",
	    AB_package);
    Qpassword_required = STATIC_SYMBOL("PASSWORD-REQUIRED",AB_package);
    Qunknown_user_or_bad_password = 
	    STATIC_SYMBOL("UNKNOWN-USER-OR-BAD-PASSWORD",AB_package);
    Qnew_password_required = STATIC_SYMBOL("NEW-PASSWORD-REQUIRED",AB_package);
    Qnew_password_does_not_match_its_duplicate = 
	    STATIC_SYMBOL("NEW-PASSWORD-DOES-NOT-MATCH-ITS-DUPLICATE",
	    AB_package);
    Qnew_password_too_long = STATIC_SYMBOL("NEW-PASSWORD-TOO-LONG",AB_package);
    Qnew_password_has_invalid_characters = 
	    STATIC_SYMBOL("NEW-PASSWORD-HAS-INVALID-CHARACTERS",AB_package);
    Qcannot_find_g2_ok_file = STATIC_SYMBOL("CANNOT-FIND-G2-OK-FILE",
	    AB_package);
    string_constant_37 = STATIC_STRING("");
    string_constant_38 = STATIC_STRING("~a \"~a\" ~a ~a ~a");
    Qg2passwd_executable_cannot_be_found = 
	    STATIC_SYMBOL("G2PASSWD-EXECUTABLE-CANNOT-BE-FOUND",AB_package);
    Qproblem_saving_password_in_g2_ok_file = 
	    STATIC_SYMBOL("PROBLEM-SAVING-PASSWORD-IN-G2-OK-FILE",AB_package);
    string_constant_39 = STATIC_STRING("~%~a.");
    string_constant_40 = 
	    STATIC_STRING("Changing password for user ~s, running ~s outside of G2 on the G2 OK file ~s");
    array_constant_34 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)0L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)1L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_34,(SI_Long)7L,(SI_Long)57344L);
    array_constant_35 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_35,(SI_Long)7L,(SI_Long)57344L);
    array_constant_36 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)1L,(SI_Long)34L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_36,(SI_Long)7L,(SI_Long)57344L);
    array_constant_37 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_37,(SI_Long)7L,(SI_Long)57344L);
    Qok_file_not_found = STATIC_SYMBOL("OK-FILE-NOT-FOUND",AB_package);
    Qinvalid_user_name = STATIC_SYMBOL("INVALID-USER-NAME",AB_package);
    string_constant_41 = STATIC_STRING("~a \"~a\" ~a ~a ~a ~a ~a");
    string_constant_42 = 
	    STATIC_STRING("Updated ~a: added a user entry for ~a");
    array_constant_38 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_38,(SI_Long)15L,(SI_Long)57344L);
    array_constant_39 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)1L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)2L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_39,(SI_Long)7L,(SI_Long)57344L);
    Qcan_not_write_tmp_file = STATIC_SYMBOL("CAN-NOT-WRITE-TMP-FILE",
	    AB_package);
    string_constant_43 = STATIC_STRING("~a \"~a\" ~a ~a \"~a\" ~a ~a");
    string_constant_44 = STATIC_STRING("x");
    string_constant_45 = 
	    STATIC_STRING("Updated ~a: deleted the user entry for ~a");
    array_constant_40 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)0L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)5L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)6L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)12L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_40,(SI_Long)23L,(SI_Long)57344L);
    array_constant_41 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)8L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)13L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)14L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)16L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)18L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_41,(SI_Long)31L,(SI_Long)57344L);
    array_constant_42 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)5L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_42,(SI_Long)23L,(SI_Long)57344L);
    string_constant_46 = 
	    STATIC_STRING("Updated ~a: modified the password-validity entry ~\n                  for ~a");
    Qformat_frame = STATIC_SYMBOL("FORMAT-FRAME",AB_package);
    Qblob_edit_box_format = STATIC_SYMBOL("BLOB-EDIT-BOX-FORMAT",AB_package);
    string_constant_125 = 
	    STATIC_STRING("13Jy83-My83ny1l83-Koy83ty3Gy83syz83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=y3My83-By083-Ny83fy83*ky83fy");
    mutate_global_property(Qblob_edit_box_format,
	    regenerate_optimized_constant(string_constant_125),
	    Qformat_description);
    Qinvisible_text_format = STATIC_SYMBOL("INVISIBLE-TEXT-FORMAT",AB_package);
    string_constant_126 = STATIC_STRING("1p83-My83-Ny83*Gy83*Ky83*Gy");
    mutate_global_property(Qinvisible_text_format,
	    regenerate_optimized_constant(string_constant_126),
	    Qformat_description);
    string_constant_47 = 
	    string_append2(STATIC_STRING("Reinstall authorized users\?~\n             ~%~%This action reads in the ~\n             G2 ok file (~s) and installs that file\'s set ~\n             of authorized users, password"),
	    STATIC_STRING("s, and user modes.~\n             ~%~%This does not affect ~\n             logged-in users until they log off or change their G2 user mode."));
    Qread_ok_file_again = STATIC_SYMBOL("READ-OK-FILE-AGAIN",AB_package);
    Qg2_reinstall_authorized_users = 
	    STATIC_SYMBOL("G2-REINSTALL-AUTHORIZED-USERS",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_reinstall_authorized_users,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    array_constant_43 = STATIC_ARRAY(list_constant_10,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)0L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)1L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_43,(SI_Long)7L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qg2_reinstall_authorized_users,
	    STATIC_FUNCTION(g2_reinstall_authorized_users,NIL,FALSE,0,0));
    string_constant_48 = 
	    STATIC_STRING("Reinstalling authorized users from ~s.");
    string_constant_49 = STATIC_STRING("~%~a");
    string_constant_50 = STATIC_STRING("~a~%Please wait . . . ");
    string_constant_51 = 
	    STATIC_STRING("Reinstallation of authorized users completed ");
    string_constant_52 = STATIC_STRING("unsuccessfully! ERROR: ~a");
    string_constant_53 = STATIC_STRING("successfully.");
    SET_SYMBOL_FUNCTION(Qread_ok_file_again,
	    STATIC_FUNCTION(read_ok_file_again,NIL,FALSE,0,0));
    string_constant_54 = STATIC_STRING("Secure G2: (");
    string_constant_55 = STATIC_STRING("; User: ~a)  ");
    string_constant_56 = STATIC_STRING(")  ");
    Qbuild_symbol = STATIC_SYMBOL("BUILD-SYMBOL",AB_package);
    Kall = STATIC_SYMBOL("ALL",Pkeyword);
    Qos_user_name = STATIC_SYMBOL("OS-USER-NAME",AB_package);
    Qdiscard_user_settings = STATIC_SYMBOL("DISCARD-USER-SETTINGS",AB_package);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qcjk_language = STATIC_SYMBOL("CJK-LANGUAGE",AB_package);
    Qnetwork_host_name = STATIC_SYMBOL("NETWORK-HOST-NAME",AB_package);
    Qos_type = STATIC_SYMBOL("OS-TYPE",AB_package);
    Qreroute_problem_report = STATIC_SYMBOL("REROUTE-PROBLEM-REPORT",
	    AB_package);
    Qg2_user_name = STATIC_SYMBOL("G2-USER-NAME",AB_package);
    Qspecific_language_for_this_g2_window_qm = 
	    STATIC_SYMBOL("SPECIFIC-LANGUAGE-FOR-THIS-G2-WINDOW\?",AB_package);
    Qg2_window_initial_window_configuration_string_qm = 
	    STATIC_SYMBOL("G2-WINDOW-INITIAL-WINDOW-CONFIGURATION-STRING\?",
	    AB_package);
    Qg2_window_network_host_name_qm = 
	    STATIC_SYMBOL("G2-WINDOW-NETWORK-HOST-NAME\?",AB_package);
    Qg2_window_os_user_name_qm = STATIC_SYMBOL("G2-WINDOW-OS-USER-NAME\?",
	    AB_package);
    Qg2_window_os_type_qm = STATIC_SYMBOL("G2-WINDOW-OS-TYPE\?",AB_package);
    Qg2_window_time_of_last_connection_qm = 
	    STATIC_SYMBOL("G2-WINDOW-TIME-OF-LAST-CONNECTION\?",AB_package);
    Qg2_window_reroute_problem_report_qm = 
	    STATIC_SYMBOL("G2-WINDOW-REROUTE-PROBLEM-REPORT\?",AB_package);
    Qg2_connection_status = STATIC_SYMBOL("G2-CONNECTION-STATUS",AB_package);
    Qconnected = STATIC_SYMBOL("CONNECTED",AB_package);
    Qui_client_session = STATIC_SYMBOL("UI-CLIENT-SESSION",AB_package);
    Qui_client_session_user_mode = 
	    STATIC_SYMBOL("UI-CLIENT-SESSION-USER-MODE",AB_package);
    if (Event_handler_args == UNBOUND)
	Event_handler_args = Nil;
    Quser_mouse_tracking = STATIC_SYMBOL("USER-MOUSE-TRACKING",AB_package);
    Qselect_area = STATIC_SYMBOL("SELECT-AREA",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Quser_mouse_tracking,
	    Qselect_area);
    Quser = STATIC_SYMBOL("USER",AB_package);
    Qexecute_user_menu_choice_if_possible = 
	    STATIC_SYMBOL("EXECUTE-USER-MENU-CHOICE-IF-POSSIBLE",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_user_menu_choice_if_possible,
	    STATIC_FUNCTION(execute_user_menu_choice_if_possible,NIL,FALSE,
	    2,2));
    Qstart_generic_command = STATIC_SYMBOL("START-GENERIC-COMMAND",AB_package);
    Qexecute_raw_event_handler = STATIC_SYMBOL("EXECUTE-RAW-EVENT-HANDLER",
	    AB_package);
    Qstart_ui_command = STATIC_SYMBOL("START-UI-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qstart_ui_command,STATIC_FUNCTION(start_ui_command,
	    NIL,TRUE,2,3));
    Qexecute_simple_event_handler = 
	    STATIC_SYMBOL("EXECUTE-SIMPLE-EVENT-HANDLER",AB_package);
    Qnothing = STATIC_SYMBOL("NOTHING",AB_package);
    mutate_global_property(Qnothing,Qnothing,Qnew_style_event_handler);
    SET_SYMBOL_FUNCTION(Qnothing,STATIC_FUNCTION(nothing,NIL,FALSE,1,1));
    Qselection_full_scale = STATIC_SYMBOL("SELECTION-FULL-SCALE",AB_package);
    Qselection_properties = STATIC_SYMBOL("SELECTION-PROPERTIES",AB_package);
    Qdelete_selection = STATIC_SYMBOL("DELETE-SELECTION",AB_package);
    Qclone_selection = STATIC_SYMBOL("CLONE-SELECTION",AB_package);
    Qtransfer_selection = STATIC_SYMBOL("TRANSFER-SELECTION",AB_package);
    Qmove_selection = STATIC_SYMBOL("MOVE-SELECTION",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)6L,Qselection_full_scale,
	    Qselection_properties,Qdelete_selection,Qclone_selection,
	    Qtransfer_selection,Qmove_selection);
    if (Listed_print_to_server_command == UNBOUND)
	Listed_print_to_server_command = LIST_1(Nil);
    Qstart_generic = STATIC_SYMBOL("START-GENERIC",AB_package);
    Qprint_to_server = STATIC_SYMBOL("PRINT-TO-SERVER",AB_package);
    Qui_command_named = STATIC_SYMBOL("UI-COMMAND-NAMED",AB_package);
    Qui_commands_with_menu_name = 
	    STATIC_SYMBOL("UI-COMMANDS-WITH-MENU-NAME",AB_package);
    Qg2_defstruct_structure_name_partial_command_g2_struct = 
	    STATIC_SYMBOL("PARTIAL-COMMAND-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qstart_generic_command,
	    STATIC_FUNCTION(start_generic_command,NIL,FALSE,2,2));
    Qg2_defstruct_structure_name_user_mode_alias_g2_struct = 
	    STATIC_SYMBOL("USER-MODE-ALIAS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Quser_mode_alias = STATIC_SYMBOL("USER-MODE-ALIAS",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_user_mode_alias_g2_struct,
	    Quser_mode_alias,Qab_name_of_unique_structure_type);
    mutate_global_property(Quser_mode_alias,
	    Qg2_defstruct_structure_name_user_mode_alias_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_user_mode_alias == UNBOUND)
	The_type_description_of_user_mode_alias = Nil;
    string_constant_127 = 
	    STATIC_STRING("43Dy8m83oKy1n83oKy8n8k1l8n0000000kpk0k0");
    temp = The_type_description_of_user_mode_alias;
    The_type_description_of_user_mode_alias = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_127));
    mutate_global_property(Qg2_defstruct_structure_name_user_mode_alias_g2_struct,
	    The_type_description_of_user_mode_alias,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Quser_mode_alias,
	    The_type_description_of_user_mode_alias,Qtype_description_of_type);
    Qoutstanding_user_mode_alias_count = 
	    STATIC_SYMBOL("OUTSTANDING-USER-MODE-ALIAS-COUNT",AB_package);
    Quser_mode_alias_structure_memory_usage = 
	    STATIC_SYMBOL("USER-MODE-ALIAS-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_128 = STATIC_STRING("1q83oKy8s83-vly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_user_mode_alias_count);
    push_optimized_constant(Quser_mode_alias_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_128));
    Qchain_of_available_user_mode_aliass = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-USER-MODE-ALIASS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_user_mode_aliass,
	    Chain_of_available_user_mode_aliass);
    record_system_variable(Qchain_of_available_user_mode_aliass,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Quser_mode_alias_count = STATIC_SYMBOL("USER-MODE-ALIAS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Quser_mode_alias_count,User_mode_alias_count);
    record_system_variable(Quser_mode_alias_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_user_mode_aliass_vector == UNBOUND)
	Chain_of_available_user_mode_aliass_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Quser_mode_alias_structure_memory_usage,
	    STATIC_FUNCTION(user_mode_alias_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_user_mode_alias_count,
	    STATIC_FUNCTION(outstanding_user_mode_alias_count,NIL,FALSE,0,0));
    reclaim_structure_for_user_mode_alias_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_user_mode_alias,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Quser_mode_alias,
	    reclaim_structure_for_user_mode_alias_1);
    Qg2_user_mode_for_login = STATIC_SYMBOL("G2-USER-MODE-FOR-LOGIN",
	    AB_package);
    string_constant_57 = 
	    STATIC_STRING("Sorry, but alias or user mode with name ~a already exist.");
    string_constant_58 = 
	    STATIC_STRING("Sorry, but alias name ~a is incorrect because ~a");
    Qconfigure = STATIC_SYMBOL("CONFIGURE",AB_package);
    Quser_interface = STATIC_SYMBOL("USER-INTERFACE",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qconfigure,Quser_interface);
    Quser_mode_aliases = STATIC_SYMBOL("USER-MODE-ALIASES",AB_package);
    Qmain_menu_user_restrictions = 
	    STATIC_SYMBOL("MAIN-MENU-USER-RESTRICTIONS",AB_package);
    Qglobal_keyboard_command_user_restrictions = 
	    STATIC_SYMBOL("GLOBAL-KEYBOARD-COMMAND-USER-RESTRICTIONS",
	    AB_package);
    Qobject_configuration = STATIC_SYMBOL("OBJECT-CONFIGURATION",AB_package);
    Qinstance_configuration = STATIC_SYMBOL("INSTANCE-CONFIGURATION",
	    AB_package);
    Qkb_configuration = STATIC_SYMBOL("KB-CONFIGURATION",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qkb_configuration,Kb_configuration);
    Qcompare_aliases = STATIC_SYMBOL("COMPARE-ALIASES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qcompare_aliases,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qcompare_aliases,STATIC_FUNCTION(compare_aliases,
	    NIL,FALSE,2,2));
    Qg2_add_alias = STATIC_SYMBOL("G2-ADD-ALIAS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_add_alias,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_add_alias,STATIC_FUNCTION(g2_add_alias,NIL,
	    FALSE,2,2));
    Qg2_delete_alias = STATIC_SYMBOL("G2-DELETE-ALIAS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_delete_alias,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_delete_alias,STATIC_FUNCTION(g2_delete_alias,
	    NIL,FALSE,1,1));
    Qis_alias_present = STATIC_SYMBOL("IS-ALIAS-PRESENT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qis_alias_present,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qis_alias_present,STATIC_FUNCTION(is_alias_present,
	    NIL,FALSE,1,1));
    Qnew_attribute_description_format = 
	    STATIC_SYMBOL("NEW-ATTRIBUTE-DESCRIPTION-FORMAT",AB_package);
    Qattribute_description_format = 
	    STATIC_SYMBOL("ATTRIBUTE-DESCRIPTION-FORMAT",AB_package);
    Qfont_for_attribute_tables = STATIC_SYMBOL("FONT-FOR-ATTRIBUTE-TABLES",
	    AB_package);
    Qnew_attributes_table_format = 
	    STATIC_SYMBOL("NEW-ATTRIBUTES-TABLE-FORMAT",AB_package);
    Qattributes_table_format = STATIC_SYMBOL("ATTRIBUTES-TABLE-FORMAT",
	    AB_package);
    string_constant_59 = STATIC_STRING("Alias name");
    string_constant_60 = STATIC_STRING("Parent user mode name");
    string_constant_61 = STATIC_STRING("Date of alias creation");
    string_constant_62 = STATIC_STRING("Who created the alias");
    string_constant_63 = STATIC_STRING("User Mode Aliases");
}
