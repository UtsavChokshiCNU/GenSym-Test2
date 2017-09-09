/* cells.c
 * Input file:  cells.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cells.h"


DEFINE_VARIABLE_WITH_SYMBOL(Cell_index_currently_being_registered, Qcell_index_currently_being_registered);

static Object Qpermanent_computation_style_p;  /* permanent-computation-style-p */

/* PUT-COMPUTATION-STYLE-REFERENCE-COUNT-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_reference_count_where_slot_is_absent(frame,
	    slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(155,0);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,Qpermanent_computation_style_p);
    SVREF(frame,FIX((SI_Long)16L)) = T;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_request_event_updates;  /* computation-style-may-request-event-updates */

/* PUT-COMPUTATION-STYLE-INVOKABLE-VIA-FORWARD-CHAINING-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_invokable_via_forward_chaining_where_slot_is_absent(frame,
	    slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(155,1);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,
		Qcomputation_style_may_request_event_updates);
    SVREF(frame,FIX((SI_Long)23L)) = slot_value;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_provide_data_on_request;  /* computation-style-may-provide-data-on-request */

/* PUT-COMPUTATION-STYLE-INVOKABLE-VIA-BACKWARD-CHAINING-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_invokable_via_backward_chaining_where_slot_is_absent(frame,
	    slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(155,2);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,
		Qcomputation_style_may_provide_data_on_request);
    SVREF(frame,FIX((SI_Long)25L)) = slot_value;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_request_data_seeking;  /* computation-style-may-request-data-seeking */

/* PUT-COMPUTATION-STYLE-MAY-CAUSE-BACKWARD-CHAINING-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_may_cause_backward_chaining_where_slot_is_absent(frame,
	    slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(155,3);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,
		Qcomputation_style_may_request_data_seeking);
    SVREF(frame,FIX((SI_Long)24L)) = slot_value;
    return VALUES_1(Nil);
}

static Object Qcomputation_style_may_provide_event_updates;  /* computation-style-may-provide-event-updates */

/* PUT-COMPUTATION-STYLE-MAY-CAUSE-FORWARD-CHAINING-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_may_cause_forward_chaining_where_slot_is_absent(frame,
	    slot_value)
    Object frame, slot_value;
{
    x_note_fn_call(155,4);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(frame,
		Qcomputation_style_may_provide_event_updates);
    SVREF(frame,FIX((SI_Long)26L)) = slot_value;
    return VALUES_1(Nil);
}

/* PUT-COMPUTATION-STYLE-TRACE-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_trace_message_level_where_slot_is_absent(computation_style,
	    old_value)
    Object computation_style, old_value;
{
    x_note_fn_call(155,5);
    convert_absent_slot_to_tracing_and_breakpoints(computation_style,
	    old_value,FIX((SI_Long)0L),Tracing_shift);
    return VALUES_1(Nil);
}

/* PUT-COMPUTATION-STYLE-WARNING-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_warning_message_level_where_slot_is_absent(computation_style,
	    old_value)
    Object computation_style, old_value;
{
    x_note_fn_call(155,6);
    convert_absent_slot_to_tracing_and_breakpoints(computation_style,
	    old_value,FIX((SI_Long)2L),Warning_shift);
    return VALUES_1(Nil);
}

/* PUT-COMPUTATION-STYLE-BREAK-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT */
Object put_computation_style_break_message_level_where_slot_is_absent(computation_style,
	    old_value)
    Object computation_style, old_value;
{
    x_note_fn_call(155,7);
    convert_absent_slot_to_tracing_and_breakpoints(computation_style,
	    old_value,FIX((SI_Long)0L),Breakpoint_shift);
    return VALUES_1(Nil);
}

static Object Qcomputation_style_tracing_and_breakpoints;  /* computation-style-tracing-and-breakpoints */

/* CONVERT-ABSENT-SLOT-TO-TRACING-AND-BREAKPOINTS */
Object convert_absent_slot_to_tracing_and_breakpoints(computation_style,
	    old_value,default_old_value,shift)
    Object computation_style, old_value, default_old_value, shift;
{
    Object computation_style_tracing_and_breakpoints, svref_new_value;

    x_note_fn_call(155,8);
    if ( !EQL(default_old_value,old_value)) {
	computation_style_tracing_and_breakpoints = 
		ISVREF(computation_style,(SI_Long)22L);
	if (computation_style_tracing_and_breakpoints);
	else
	    computation_style_tracing_and_breakpoints = 
		    Completely_unspecified_debugging_code;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(computation_style,
		    Qcomputation_style_tracing_and_breakpoints);
	svref_new_value = 
		logior(logandc2(computation_style_tracing_and_breakpoints,
		ash(Message_field_mask,shift)),ash(old_value,shift));
	return VALUES_1(SVREF(computation_style,FIX((SI_Long)22L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulator;          /* simulator */

/* COMPUTE-HASH-OF-COMPUTATION-STYLE */
Object compute_hash_of_computation_style(computation_style)
    Object computation_style;
{
    Object temp, gensymed_symbol, temp_1;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, result_1, temp_3;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    double temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(155,9);
    temp = ISVREF(computation_style,(SI_Long)18L);
    gensymed_symbol = ISVREF(computation_style,(SI_Long)19L);
    if (FIXNUMP(gensymed_symbol))
	temp_1 = IFIX(gensymed_symbol) < (SI_Long)0L ? 
		FIXNUM_NEGATE(gensymed_symbol) : gensymed_symbol;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_2 = DFLOAT_ISAREF_1(gensymed_symbol,(SI_Long)0L);
	    temp_1 = LONG_TO_FIXNUM(inline_floor_1(ABS(temp_2)));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp_1 = FIX((SI_Long)0L);
    temp = logxor(temp,temp_1);
    gensymed_symbol = ISVREF(computation_style,(SI_Long)20L);
    if (FIXNUMP(gensymed_symbol))
	temp_1 = IFIX(gensymed_symbol) < (SI_Long)0L ? 
		FIXNUM_NEGATE(gensymed_symbol) : gensymed_symbol;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp_2 = DFLOAT_ISAREF_1(gensymed_symbol,(SI_Long)0L);
	    temp_1 = LONG_TO_FIXNUM(inline_floor_1(ABS(temp_2)));
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    else
	temp_1 = FIX((SI_Long)0L);
    temp = logxor(temp,temp_1);
    gensymed_symbol_1 = ISVREF(computation_style,(SI_Long)21L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)6L;
    result_1 = IFIX(FIXNUM_LOGXOR(temp,FIX(gensymed_symbol_1 << 
	    gensymed_symbol_2)));
    temp_3 = result_1 ^ IFIX(ash(ISVREF(computation_style,(SI_Long)22L) ? 
	    ISVREF(computation_style,(SI_Long)22L) : FIX((SI_Long)0L),
	    FIX((SI_Long)7L)));
    gensymed_symbol_1 = ISVREF(computation_style,(SI_Long)23L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)14L;
    temp_3 = temp_3 ^ gensymed_symbol_1 << gensymed_symbol_2;
    gensymed_symbol_1 = ISVREF(computation_style,(SI_Long)24L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)15L;
    temp_3 = temp_3 ^ gensymed_symbol_1 << gensymed_symbol_2;
    gensymed_symbol_1 = ISVREF(computation_style,(SI_Long)25L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)16L;
    result_1 = temp_3 ^ gensymed_symbol_1 << gensymed_symbol_2;
    gensymed_symbol_1 = result_1;
    gensymed_symbol_2 = ISVREF(computation_style,(SI_Long)26L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_3 = (SI_Long)17L;
    gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
    gensymed_symbol_3 = EQ(Qsimulator,ISVREF(computation_style,
	    (SI_Long)27L)) ? (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_4 = (SI_Long)18L;
    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
    gensymed_symbol_4 = ISVREF(computation_style,(SI_Long)28L) ? 
	    (SI_Long)1L : (SI_Long)0L;
    gensymed_symbol_5 = (SI_Long)19L;
    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
    result_1 = gensymed_symbol_1 ^ gensymed_symbol_2 ^ gensymed_symbol_3 ^ 
	    gensymed_symbol_4;
    temp = ISVREF(computation_style,(SI_Long)32L);
    if (EQ(temp,Qread))
	result_1 = result_1 ^ (SI_Long)1048576L;
    else if (EQ(temp,Qwrite))
	result_1 = result_1 ^ (SI_Long)2097152L;
    return VALUES_1(FIX(result_1));
}

/* COMPUTATION-STYLE-EQUAL */
Object computation_style_equal(first_computation_style,
	    permanent_computation_style)
    Object first_computation_style, permanent_computation_style;
{
    Object gensymed_symbol, gensymed_symbol_1, temp_1, temp_2;
    char temp;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(155,10);
    if (FIXNUM_EQ(ISVREF(first_computation_style,(SI_Long)18L),
	    ISVREF(permanent_computation_style,(SI_Long)18L))) {
	gensymed_symbol = ISVREF(first_computation_style,(SI_Long)19L);
	gensymed_symbol_1 = ISVREF(permanent_computation_style,(SI_Long)19L);
	temp =  !TRUEP(gensymed_symbol) ?  !TRUEP(gensymed_symbol_1) : 
		TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) && FIXNUMP(gensymed_symbol_1) ?
		     FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
		    TRUEP(Qnil);
	if (temp);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L && 
		INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) == 
		(SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		arg = DFLOAT_ISAREF_1(gensymed_symbol,(SI_Long)0L);
		arg_1 = DFLOAT_ISAREF_1(gensymed_symbol_1,(SI_Long)0L);
		temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(first_computation_style,(SI_Long)20L);
	gensymed_symbol_1 = ISVREF(permanent_computation_style,(SI_Long)20L);
	temp =  !TRUEP(gensymed_symbol) ?  !TRUEP(gensymed_symbol_1) : 
		TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) && FIXNUMP(gensymed_symbol_1) ?
		     FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
		    TRUEP(Qnil);
	if (temp);
	else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		(SI_Long)1L && 
		INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) == 
		(SI_Long)1L) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		arg = DFLOAT_ISAREF_1(gensymed_symbol,(SI_Long)0L);
		arg_1 = DFLOAT_ISAREF_1(gensymed_symbol_1,(SI_Long)0L);
		temp = arg == arg_1 &&  !inline_nanp_for_comparison(arg) ? 
			 !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)21L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)21L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)22L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)22L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)23L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)23L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)24L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)24L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)25L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)25L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)26L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)26L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)27L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)27L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = ISVREF(first_computation_style,(SI_Long)28L);
	temp_2 = ISVREF(permanent_computation_style,(SI_Long)28L);
	temp = EQL(temp_1,temp_2);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(EQ(ISVREF(first_computation_style,(SI_Long)32L),
		ISVREF(permanent_computation_style,(SI_Long)32L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* COMPARE-COMPUTATION-STYLES-FOR-INSTALLATION-DIFFERENCES */
Object compare_computation_styles_for_installation_differences(new_computation_style,
	    old_computation_style_qm)
    Object new_computation_style, old_computation_style_qm;
{
    Object temp, temp_1, scan_task_reschedule_needed_qm, gensymed_symbol;
    Object gensymed_symbol_1;
    char recompile_needed_qm, temp_2;
    double arg, arg_1;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(155,11);
    if ( !TRUEP(old_computation_style_qm))
	return VALUES_2(T,T);
    else if (computation_style_equal(new_computation_style,
	    old_computation_style_qm))
	return VALUES_2(Nil,Nil);
    else {
	temp = ISVREF(new_computation_style,(SI_Long)23L);
	temp_1 = ISVREF(old_computation_style_qm,(SI_Long)23L);
	recompile_needed_qm =  !EQL(temp,temp_1);
	temp = ISVREF(new_computation_style,(SI_Long)18L);
	temp_1 = ISVREF(old_computation_style_qm,(SI_Long)18L);
	scan_task_reschedule_needed_qm =  !EQL(temp,temp_1) ? T : Nil;
	if (scan_task_reschedule_needed_qm);
	else {
	    gensymed_symbol = ISVREF(new_computation_style,(SI_Long)19L);
	    gensymed_symbol_1 = ISVREF(old_computation_style_qm,(SI_Long)19L);
	    temp_2 =  !TRUEP(gensymed_symbol) ?  !TRUEP(gensymed_symbol_1) 
		    : TRUEP(Qnil);
	    if (temp_2);
	    else
		temp_2 = FIXNUMP(gensymed_symbol) && 
			FIXNUMP(gensymed_symbol_1) ? 
			FIXNUM_EQ(gensymed_symbol,gensymed_symbol_1) : 
			TRUEP(Qnil);
	    if (temp_2);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) == 
		    (SI_Long)1L && 
		    INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) == 
		    (SI_Long)1L) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    arg = DFLOAT_ISAREF_1(gensymed_symbol,(SI_Long)0L);
		    arg_1 = DFLOAT_ISAREF_1(gensymed_symbol_1,(SI_Long)0L);
		    temp_2 = arg == arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    scan_task_reschedule_needed_qm =  !temp_2 ? T : Nil;
	}
	return VALUES_2(recompile_needed_qm ? T : Nil,
		scan_task_reschedule_needed_qm);
    }
}

static Object Qcomputation_style_priority;  /* computation-style-priority */

static Object Qcomputation_style_scan_interval;  /* computation-style-scan-interval */

static Object Qcomputation_style_initial_scan_wait_interval;  /* computation-style-initial-scan-wait-interval */

static Object Qcomputation_style_update_only_when_shown;  /* computation-style-update-only-when-shown */

static Object Qcomputation_style_value_domain;  /* computation-style-value-domain */

static Object Qcomputation_style_update_after_edits;  /* computation-style-update-after-edits */

static Object Qcomputation_style_network_access_attempt;  /* computation-style-network-access-attempt */

/* COPY-COMPUTATION-STYLE */
Object copy_computation_style(target_computation_style,
	    dynamic_computation_style)
    Object target_computation_style, dynamic_computation_style;
{
    Object svref_new_value;

    x_note_fn_call(155,12);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_priority);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)18L);
    SVREF(target_computation_style,FIX((SI_Long)18L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_scan_interval);
    svref_new_value = copy_for_slot_value(ISVREF(dynamic_computation_style,
	    (SI_Long)19L));
    SVREF(target_computation_style,FIX((SI_Long)19L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_initial_scan_wait_interval);
    svref_new_value = copy_for_slot_value(ISVREF(dynamic_computation_style,
	    (SI_Long)20L));
    SVREF(target_computation_style,FIX((SI_Long)20L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_update_only_when_shown);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)21L);
    SVREF(target_computation_style,FIX((SI_Long)21L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_tracing_and_breakpoints);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)22L);
    SVREF(target_computation_style,FIX((SI_Long)22L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_may_request_event_updates);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)23L);
    SVREF(target_computation_style,FIX((SI_Long)23L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_may_request_data_seeking);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)24L);
    SVREF(target_computation_style,FIX((SI_Long)24L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_may_provide_data_on_request);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)25L);
    SVREF(target_computation_style,FIX((SI_Long)25L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_may_provide_event_updates);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)26L);
    SVREF(target_computation_style,FIX((SI_Long)26L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_value_domain);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)27L);
    SVREF(target_computation_style,FIX((SI_Long)27L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_update_after_edits);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)28L);
    SVREF(target_computation_style,FIX((SI_Long)28L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(target_computation_style,
		Qcomputation_style_network_access_attempt);
    svref_new_value = ISVREF(dynamic_computation_style,(SI_Long)32L);
    SVREF(target_computation_style,FIX((SI_Long)32L)) = svref_new_value;
    return VALUES_1(target_computation_style);
}

Object Number_of_buckets_in_computation_style_set = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Set_of_all_permanent_computation_style, Qset_of_all_permanent_computation_style);

static Object Qcomputation_style;  /* computation-style */

/* MAKE-COMPUTATION-STYLE-FUNCTION */
Object make_computation_style_function()
{
    x_note_fn_call(155,13);
    return make_frame(Qcomputation_style);
}

/* INITIALIZE-SET-OF-ALL-PERMANENT-COMPUTATION-STYLE */
Object initialize_set_of_all_permanent_computation_style()
{
    x_note_fn_call(155,14);
    return allocate_managed_array(1,
	    Number_of_buckets_in_computation_style_set);
}

/* RECLAIM-SET-OF-ALL-PERMANENT-COMPUTATION-STYLE */
Object reclaim_set_of_all_permanent_computation_style(the_set)
    Object the_set;
{
    x_note_fn_call(155,15);
    return reclaim_slot_value(the_set);
}

/* FIND-MATCHING-PERMANENT-COMPUTATION-STYLE-IF-ANY */
Object find_matching_permanent_computation_style_if_any(computation_style)
    Object computation_style;
{
    Object candiate_computation_style_qm;
    SI_Long temp, bucket_index;

    x_note_fn_call(155,16);
    temp = IFIX(compute_hash_of_computation_style(computation_style));
    temp = temp % IFIX(Number_of_buckets_in_computation_style_set);
    bucket_index = temp;
    candiate_computation_style_qm = 
	    FIXNUM_LE(ISVREF(Set_of_all_permanent_computation_style,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(Set_of_all_permanent_computation_style,bucket_index + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(Set_of_all_permanent_computation_style,
	    (bucket_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    bucket_index & (SI_Long)1023L);
  next_loop:
    if ( !TRUEP(candiate_computation_style_qm) || 
	    computation_style_equal(computation_style,
	    candiate_computation_style_qm))
	goto end_loop;
    candiate_computation_style_qm = ISVREF(candiate_computation_style_qm,
	    (SI_Long)17L);
    goto next_loop;
  end_loop:
    return VALUES_1(candiate_computation_style_qm);
    return VALUES_1(Qnil);
}

/* ADD-COMPUTATION-STYLE-TO-SET-OF-ALL-PERMANENT-COMPUTATION-STYLES */
Object add_computation_style_to_set_of_all_permanent_computation_styles(permanent_computation_style)
    Object permanent_computation_style;
{
    Object temp_1;
    SI_Long temp, bucket_index, svref_arg_2;

    x_note_fn_call(155,17);
    temp = 
	    IFIX(compute_hash_of_computation_style(permanent_computation_style));
    temp = temp % IFIX(Number_of_buckets_in_computation_style_set);
    bucket_index = temp;
    temp_1 = FIXNUM_LE(ISVREF(Set_of_all_permanent_computation_style,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(Set_of_all_permanent_computation_style,bucket_index + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(Set_of_all_permanent_computation_style,
	    (bucket_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    bucket_index & (SI_Long)1023L);
    ISVREF(permanent_computation_style,(SI_Long)17L) = temp_1;
    if (FIXNUM_LE(ISVREF(Set_of_all_permanent_computation_style,
	    (SI_Long)1L),Maximum_in_place_array_size)) {
	temp_1 = Set_of_all_permanent_computation_style;
	svref_arg_2 = bucket_index + IFIX(Managed_array_index_offset);
	return VALUES_1(ISVREF(temp_1,svref_arg_2) = 
		permanent_computation_style);
    }
    else {
	temp_1 = ISVREF(Set_of_all_permanent_computation_style,
		(bucket_index >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = bucket_index & (SI_Long)1023L;
	return VALUES_1(ISVREF(temp_1,svref_arg_2) = 
		permanent_computation_style);
    }
}

static Object Qframe_flags;        /* frame-flags */

/* REGISTER-USE-OF-COMPUTATION-STYLE */
Object register_use_of_computation_style(computation_style)
    Object computation_style;
{
    Object temp, new_computation_style;
    SI_Long svref_new_value;

    x_note_fn_call(155,18);
    temp = ISVREF(computation_style,(SI_Long)16L) ? computation_style : Nil;
    if (temp);
    else
	temp = 
		find_matching_permanent_computation_style_if_any(computation_style);
    if (temp)
	return VALUES_1(temp);
    else {
	new_computation_style = 
		copy_computation_style(make_frame(Qcomputation_style),
		computation_style);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(new_computation_style,
		    Qpermanent_computation_style_p);
	SVREF(new_computation_style,FIX((SI_Long)16L)) = T;
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(computation_style,Qframe_flags);
	svref_new_value = IFIX(ISVREF(computation_style,(SI_Long)4L)) | 
		(SI_Long)1L;
	ISVREF(computation_style,(SI_Long)4L) = FIX(svref_new_value);
	if (Noting_changes_to_kb_p) {
	    svref_new_value = IFIX(ISVREF(computation_style,(SI_Long)5L)) 
		    | (SI_Long)4L;
	    ISVREF(computation_style,(SI_Long)5L) = FIX(svref_new_value);
	}
	add_computation_style_to_set_of_all_permanent_computation_styles(new_computation_style);
	return VALUES_1(new_computation_style);
    }
}

/* DEREGISTER-USE-OF-COMPUTATION-STYLE */
Object deregister_use_of_computation_style(permanent_computation_style)
    Object permanent_computation_style;
{
    x_note_fn_call(155,19);
    return VALUES_1(Nil);
}

/* GET-OR-MAKE-ENTRY-TO-SET-OF-ALL-PERMANENT-COMPUTATION-STYLES */
Object get_or_make_entry_to_set_of_all_permanent_computation_styles(incomming_computation_style)
    Object incomming_computation_style;
{
    Object temp;

    x_note_fn_call(155,20);
    temp = 
	    find_matching_permanent_computation_style_if_any(incomming_computation_style);
    if (temp)
	return VALUES_1(temp);
    else
	return add_computation_style_to_set_of_all_permanent_computation_styles(incomming_computation_style);
}

/* SAVABLE-COMPUTATION-STYLE-P */
Object savable_computation_style_p(computation_style_instance)
    Object computation_style_instance;
{
    Object computation_style;
    SI_Long bucket_index, ab_loop_bind_;

    x_note_fn_call(155,21);
    bucket_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(Number_of_buckets_in_computation_style_set);
  next_loop:
    if (bucket_index >= ab_loop_bind_)
	goto end_loop;
    computation_style = 
	    FIXNUM_LE(ISVREF(Set_of_all_permanent_computation_style,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(Set_of_all_permanent_computation_style,bucket_index + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(Set_of_all_permanent_computation_style,
	    (bucket_index >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    bucket_index & (SI_Long)1023L);
  next_loop_1:
    if ( !TRUEP(computation_style))
	goto end_loop_1;
    if (EQ(computation_style,computation_style_instance))
	goto end_1;
    computation_style = ISVREF(computation_style,(SI_Long)17L);
    goto next_loop_1;
  end_loop_1:
  end_1:;
    bucket_index = bucket_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* G2-CELL-ARRAY-MANAGED-ARRAY-FUNCTION */
Object g2_cell_array_managed_array_function(g2_cell_array)
    Object g2_cell_array;
{
    x_note_fn_call(155,22);
    return VALUES_1(ISVREF(g2_cell_array,(SI_Long)3L));
}

/* REBUILD-BACKPOINTERS-OF-G2-CELL-ARRAY */
Object rebuild_backpointers_of_g2_cell_array(parent_frame,g2_cell_array)
    Object parent_frame, g2_cell_array;
{
    x_note_fn_call(155,23);
    ISVREF(g2_cell_array,(SI_Long)2L) = parent_frame;
    rebuild_backpointers_of_cells_of_g2_cell_array(g2_cell_array,parent_frame);
    return VALUES_1(Nil);
}

/* RECLAIM-G2-CELL-ARRAY-PARENT-FRAME-VALUE */
Object reclaim_g2_cell_array_parent_frame_value(parent_frame,g2_cell_array)
    Object parent_frame, g2_cell_array;
{
    x_note_fn_call(155,24);
    ISVREF(g2_cell_array,(SI_Long)2L) = Nil;
    return VALUES_1(Nil);
}

static Object Qdependent_frame_has_no_owner;  /* dependent-frame-has-no-owner */

/* COPY-FRAME-FOR-G2-CELL-ARRAY */
Object copy_frame_for_g2_cell_array(g2_cell_array)
    Object g2_cell_array;
{
    Object gensymed_symbol, old_current_block_of_dependent_frame;

    x_note_fn_call(155,25);
    gensymed_symbol = Nil;
    old_current_block_of_dependent_frame = Current_block_of_dependent_frame;
    Current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    gensymed_symbol = clone_frame(1,g2_cell_array);
    Current_block_of_dependent_frame = old_current_block_of_dependent_frame;
    return VALUES_1(gensymed_symbol);
}

static Object Qcell_array;         /* cell-array */

/* SCHEDULE-G2-CELL-ARRAY-UPDATE */
Object schedule_g2_cell_array_update(block)
    Object block;
{
    Object g2_cell_array, managed_array, cell;
    SI_Long cell_count, index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,26);
    g2_cell_array = get_lookup_slot_value_given_default(block,Qcell_array,Nil);
    managed_array = g2_cell_array ? ISVREF(g2_cell_array,(SI_Long)3L) : Nil;
    cell_count = managed_array ? IFIX(ISVREF(managed_array,(SI_Long)1L)) : 
	    (SI_Long)0L;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = cell_count;
    cell = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      Cell = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	      Maximum_in_place_array_size) ? ISVREF(managed_array,index_1 
	      + IFIX(Managed_array_index_offset)) : 
	      ISVREF(ISVREF(managed_array,(index_1 >>  -  - (SI_Long)10L) 
	      + (SI_Long)2L),index_1 & (SI_Long)1023L);
      if (Cell)
	  update_g2_cell_value(block,g2_cell_array,FIX(index_1),Cell);
      index_1 = index_1 + (SI_Long)1L;
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* UPDATE-G2-CELL-VALUE */
Object update_g2_cell_value(block,g2_cell_array,index_1,cell)
    Object block, g2_cell_array, index_1, cell;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,27);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      gensymed_symbol = ISVREF(Cell,(SI_Long)1L);
      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
      superior_class_bit_number = 
	      IFIX(ISVREF(G2_expression_cell_class_description,(SI_Long)18L));
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
	  result = schedule_expression_cell_execution(block,index_1,T);
      else {
	  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(G2_designation_cell_class_description,
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
	      result = compute_new_designation_cell_value(g2_cell_array,
		      index_1,Cell);
	  else {
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(G2_query_cell_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
		  result = compute_new_query_cell_value(g2_cell_array,
			  index_1,Cell);
	      else
		  result = VALUES_1(Qnil);
	  }
      }
    POP_SPECIAL();
    return result;
}

/* INITIALIZE-G2-CELL-ARRAY */
Object initialize_g2_cell_array(g2_cell_array)
    Object g2_cell_array;
{
    Object parent_frame;

    x_note_fn_call(155,28);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    if ((SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	begin_g2_cell_array_evaluations(g2_cell_array);
    return VALUES_1(Nil);
}

/* INITIALIZE-G2-CELL-ARRAY-AFTER-READING */
Object initialize_g2_cell_array_after_reading(g2_cell_array)
    Object g2_cell_array;
{
    x_note_fn_call(155,29);
    initialize_g2_cell_array(g2_cell_array);
    return VALUES_1(Nil);
}

/* CLEANUP-G2-CELL-ARRAY */
Object cleanup_g2_cell_array(g2_cell_array)
    Object g2_cell_array;
{
    Object parent_frame;

    x_note_fn_call(155,30);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    if ((SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	shutdown_g2_cell_array_evaluations(g2_cell_array);
    return VALUES_1(Nil);
}

/* NOTE-G2-CELL-ARRAY-RUNS-WHILE-INACTIVE-CHANGE */
Object note_g2_cell_array_runs_while_inactive_change(g2_cell_array,
	    parent_frame)
    Object g2_cell_array, parent_frame;
{
    x_note_fn_call(155,31);
    if ((SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	begin_g2_cell_array_evaluations(g2_cell_array);
    else if ( !((SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)5L)) & 
	    (SI_Long)1L)))
	shutdown_g2_cell_array_evaluations(g2_cell_array);
    return VALUES_1(Nil);
}

/* ACTIVATE-G2-CELL-ARRAY */
Object activate_g2_cell_array(g2_cell_array)
    Object g2_cell_array;
{
    x_note_fn_call(155,32);
    begin_g2_cell_array_evaluations(g2_cell_array);
    return VALUES_1(Nil);
}

/* BEGIN-G2-CELL-ARRAY-EVALUATIONS */
Object begin_g2_cell_array_evaluations(g2_cell_array)
    Object g2_cell_array;
{
    Object managed_array;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(155,33);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if (managed_array) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	activate_cell_of_g2_cell_array_1(FIXNUM_LE(ISVREF(managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_array,index_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* ACTIVATE-CELL-OF-G2-CELL-ARRAY */
Object activate_cell_of_g2_cell_array(g2_cell_array,index_1)
    Object g2_cell_array, index_1;
{
    x_note_fn_call(155,34);
    activate_cell_of_g2_cell_array_1(FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,
	    (SI_Long)3L),(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(IFIX(index_1) 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
	    (SI_Long)1023L));
    return VALUES_1(Nil);
}

/* ACTIVATE-CELL-OF-G2-CELL-ARRAY-1 */
Object activate_cell_of_g2_cell_array_1(cell_qm)
    Object cell_qm;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(155,35);
    if (cell_qm) {
	gensymed_symbol = ISVREF(cell_qm,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
	    activate_g2_expression_cell(cell_qm);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_query_cell_class_description,(SI_Long)18L));
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
		activate_g2_query_cell(cell_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_designation_cell_class_description,
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
		    activate_g2_designation_cell(cell_qm);
	    }
	}
    }
    return VALUES_1(Nil);
}

/* DEACTIVATE-G2-CELL-ARRAY */
Object deactivate_g2_cell_array(g2_cell_array)
    Object g2_cell_array;
{
    Object parent_frame;

    x_note_fn_call(155,36);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    if ( !((SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L)))
	shutdown_g2_cell_array_evaluations(g2_cell_array);
    return VALUES_1(Nil);
}

/* SHUTDOWN-G2-CELL-ARRAY-EVALUATIONS */
Object shutdown_g2_cell_array_evaluations(g2_cell_array)
    Object g2_cell_array;
{
    Object managed_array;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(155,37);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if (managed_array) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	deactivate_cell_of_g2_cell_array_1(FIXNUM_LE(ISVREF(managed_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(managed_array,index_1 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L));
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* DEACTIVATE-CELL-OF-G2-CELL-ARRAY */
Object deactivate_cell_of_g2_cell_array(g2_cell_array,cell_index)
    Object g2_cell_array, cell_index;
{
    x_note_fn_call(155,38);
    deactivate_cell_of_g2_cell_array_1(FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,
	    (SI_Long)3L),(SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(cell_index,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (IFIX(cell_index) >>  -  - (SI_Long)10L) + (SI_Long)2L),
	    IFIX(cell_index) & (SI_Long)1023L));
    return VALUES_1(Nil);
}

/* DEACTIVATE-CELL-OF-G2-CELL-ARRAY-1 */
Object deactivate_cell_of_g2_cell_array_1(cell_qm)
    Object cell_qm;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(155,39);
    if (cell_qm) {
	gensymed_symbol = ISVREF(cell_qm,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
	    deactivate_g2_expression_cell(cell_qm);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_query_cell_class_description,(SI_Long)18L));
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
		deactivate_g2_query_cell(cell_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_designation_cell_class_description,
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
		    deactivate_g2_designation_cell(cell_qm);
	    }
	}
    }
    return VALUES_1(Nil);
}

/* DELETE-CELL-FROM-G2-CELL-ARRAY */
Object delete_cell_from_g2_cell_array(g2_cell_array,index_1)
    Object g2_cell_array, index_1;
{
    Object managed_array, temp;
    SI_Long svref_arg_2;

    x_note_fn_call(155,40);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    delete_all_frame_notes_for_component_particular(Current_computation_component_particulars,
	    Current_computation_frame);
    delete_frame(FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L));
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(index_1,Managed_array_index_offset);
	SVREF(managed_array,temp) = Nil;
    }
    else {
	temp = ISVREF(managed_array,(IFIX(index_1) >>  -  - (SI_Long)10L) 
		+ (SI_Long)2L);
	svref_arg_2 = IFIX(index_1) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    temp = shrink_or_delete_managed_array_null_elements(managed_array);
    SVREF(g2_cell_array,FIX((SI_Long)3L)) = temp;
    return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* REMOVE-COMPILATIONS-FROM-OBSOLETE-CELL-ARRAY */
Object remove_compilations_from_obsolete_cell_array(g2_cell_array_qm)
    Object g2_cell_array_qm;
{
    Object managed_array, cell, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long cell_count, index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,41);
    if (g2_cell_array_qm) {
	managed_array = ISVREF(g2_cell_array_qm,(SI_Long)3L);
	cell_count = managed_array ? IFIX(ISVREF(managed_array,
		(SI_Long)1L)) : (SI_Long)0L;
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = cell_count;
	cell = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  Cell = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(managed_array,
		  index_1 + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	  if (SIMPLE_VECTOR_P(Cell) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Cell)) > (SI_Long)2L &&  
		  !EQ(ISVREF(Cell,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(Cell,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      gensymed_symbol = ISVREF(Cell,(SI_Long)1L);
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(G2_expression_cell_class_description,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
		  remove_compilation_from_obsolete_expression_cell(Cell);
	      else {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(G2_query_cell_class_description,
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp);
		  else {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(G2_designation_cell_class_description,
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
		  }
		  if (temp);
	      }
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* FIND-NEW-LOCATION-FOR-CELL */
Object find_new_location_for_cell(g2_cell_array)
    Object g2_cell_array;
{
    Object managed_array, svref_new_value;
    SI_Long new_location, array_length, index_1, ab_loop_bind_;

    x_note_fn_call(155,42);
    new_location = (SI_Long)-1L;
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if ( !TRUEP(managed_array)) {
	managed_array = allocate_managed_array(1,FIX((SI_Long)1L));
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	SVREF(g2_cell_array,FIX((SI_Long)3L)) = managed_array;
	new_location = (SI_Long)0L;
    }
    else {
	array_length = IFIX(ISVREF(managed_array,(SI_Long)1L));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = array_length;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !(FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? TRUEP(ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset))) : 
		TRUEP(ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L)))) {
	    new_location = index_1;
	    goto end_1;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	new_location = array_length;
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	svref_new_value = adjust_managed_array(2,managed_array,
		FIX(array_length + (SI_Long)1L));
	SVREF(g2_cell_array,FIX((SI_Long)3L)) = svref_new_value;
      end_1:;
    }
    return VALUES_1(FIX(new_location));
}

static Object Qcell_array_element;  /* cell-array-element */

/* ANALYZE-G2-CELL-ARRAY-FOR-CONSISTENCY */
Object analyze_g2_cell_array_for_consistency(g2_cell_array)
    Object g2_cell_array;
{
    Object managed_array, current_computation_component_particulars;
    Object second_arg;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,43);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if (managed_array) {
	current_computation_component_particulars = 
		slot_value_list_2(Qcell_array_element,FIX((SI_Long)0L));
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		0);
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  second_arg = Current_computation_component_particulars;
	  M_SECOND(second_arg) = FIX(index_1);
	  analyze_cell_for_consistency_1(FIXNUM_LE(ISVREF(managed_array,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(managed_array,index_1 + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L));
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  reclaim_slot_value_list_1(Current_computation_component_particulars);
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* ANALYZE-CELL-FOR-CONSISTENCY-1 */
Object analyze_cell_for_consistency_1(cell_qm)
    Object cell_qm;
{
    Object gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(155,44);
    if (cell_qm) {
	gensymed_symbol = ISVREF(cell_qm,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
	    analyze_g2_expression_cell_for_consistency(cell_qm);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_query_cell_class_description,(SI_Long)18L));
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
		analyze_g2_query_cell_for_consistency(cell_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(G2_designation_cell_class_description,
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
		    analyze_g2_designation_cell_for_consistency(cell_qm);
	    }
	}
    }
    return VALUES_1(Nil);
}

/* G2-CELL-ARRAY-EXPRESSION-CELLS-HAVE-BYTE-CODE-BODIES-P */
Object g2_cell_array_expression_cells_have_byte_code_bodies_p(g2_cell_array)
    Object g2_cell_array;
{
    Object managed_array, cell_qm, expression_cells_have_byte_code_bodies_qm;
    Object sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(155,45);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if (managed_array) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
	cell_qm = Nil;
	expression_cells_have_byte_code_bodies_qm = T;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	cell_qm = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (cell_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(cell_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_expression_cell_class_description,
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
	if (temp) {
	    if ( !TRUEP(g2_expression_cell_byte_code_body_function(cell_qm)))
		expression_cells_have_byte_code_bodies_qm = Nil;
	}
	if ( !TRUEP(expression_cells_have_byte_code_bodies_qm))
	    goto end_loop;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(expression_cells_have_byte_code_bodies_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COPY-FRAME-FOR-G2-CELL-ARRAY-CELL */
Object copy_frame_for_g2_cell_array_cell(g2_cell_array_cell)
    Object g2_cell_array_cell;
{
    Object gensymed_symbol, old_current_block_of_dependent_frame;

    x_note_fn_call(155,46);
    gensymed_symbol = Nil;
    old_current_block_of_dependent_frame = Current_block_of_dependent_frame;
    Current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    gensymed_symbol = clone_frame(1,g2_cell_array_cell);
    Current_block_of_dependent_frame = old_current_block_of_dependent_frame;
    return VALUES_1(gensymed_symbol);
}

/* RECLAIM-G2-DESIGNATION-CELL-FRAME-SERIAL-NUMBER?-VALUE */
Object reclaim_g2_designation_cell_frame_serial_number_qm_value(serial_number,
	    g2_designation_cell)
    Object serial_number, g2_designation_cell;
{
    x_note_fn_call(155,47);
    reclaim_frame_serial_number(serial_number);
    ISVREF(g2_designation_cell,(SI_Long)5L) = Nil;
    return VALUES_1(Nil);
}

/* G2-EXPRESSION-CELL-BYTE-CODE-BODY-FUNCTION */
Object g2_expression_cell_byte_code_body_function(g2_expression_cell)
    Object g2_expression_cell;
{
    x_note_fn_call(155,48);
    return VALUES_1(ISVREF(g2_expression_cell,(SI_Long)10L));
}

/* PUT-G2-EXPRESSION-CELL-EXPRESSION-WHERE-SLOT-IS-ABSENT */
Object put_g2_expression_cell_expression_where_slot_is_absent(ignored_frame,
	    expression)
    Object ignored_frame, expression;
{
    x_note_fn_call(155,49);
    reclaim_slot_value(expression);
    return VALUES_1(Nil);
}

/* RECLAIM-G2-EXPRESSION-CELL-G2-CELL-ARRAY-VALUE */
Object reclaim_g2_expression_cell_g2_cell_array_value(parent_array,
	    g2_expression_cell)
    Object parent_array, g2_expression_cell;
{
    x_note_fn_call(155,50);
    ISVREF(g2_expression_cell,(SI_Long)4L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-G2-EXPRESSION-CELL-COMPUTATION-STYLE-VALUE */
Object reclaim_g2_expression_cell_computation_style_value(computation_style,
	    gensymed_symbol)
    Object computation_style, gensymed_symbol;
{
    x_note_fn_call(155,51);
    deregister_use_of_computation_style(computation_style);
    return VALUES_1(Nil);
}

/* RECLAIM-G2-EXPRESSION-CELL-CACHED-VALUE-VALUE */
Object reclaim_g2_expression_cell_cached_value_value(item_or_evaluation_value_qm,
	    gensymed_symbol)
    Object item_or_evaluation_value_qm, gensymed_symbol;
{
    x_note_fn_call(155,52);
    if ( !(FIXNUMP(item_or_evaluation_value_qm) || 
	    SYMBOLP(item_or_evaluation_value_qm) || 
	    SIMPLE_VECTOR_P(item_or_evaluation_value_qm)))
	reclaim_if_evaluation_value_1(item_or_evaluation_value_qm);
    return VALUES_1(Nil);
}

static Object Qg2_expression_cell;  /* g2-expression-cell */

/* COPY-FRAME-FOR-G2-EXPRESSION-CELL */
Object copy_frame_for_g2_expression_cell(g2_expression_cell)
    Object g2_expression_cell;
{
    Object frame, sub_vector_qm, method_function_qm, result_1, gensymed_symbol;
    Object old_current_block_of_dependent_frame, svref_new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(155,53);
    frame = g2_expression_cell;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)17L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_expression_cell)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    result_1 = method_function_qm ? inline_funcall_1(method_function_qm,
	    frame) : Nil;
    gensymed_symbol = Nil;
    old_current_block_of_dependent_frame = Current_block_of_dependent_frame;
    Current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = ISVREF(g2_expression_cell,(SI_Long)3L);
    gensymed_symbol = register_use_of_computation_style(SVREF(result_1,
	    FIX((SI_Long)3L)) = svref_new_value);
    Current_block_of_dependent_frame = old_current_block_of_dependent_frame;
    return VALUES_1(result_1);
}

/* REBUILD-BACKPOINTERS-OF-CELLS-OF-G2-CELL-ARRAY */
Object rebuild_backpointers_of_cells_of_g2_cell_array(g2_cell_array,
	    parent_frame)
    Object g2_cell_array, parent_frame;
{
    Object managed_array, cell, sub_class_bit_vector, svref_arg_1;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,54);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    if (managed_array) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
	cell = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  Cell = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(managed_array,
		  index_1 + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	  if (Cell) {
	      sub_class_bit_vector = ISVREF(ISVREF(Cell,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(G2_expression_cell_class_description,
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
	  if (temp) {
	      svref_arg_1 = Cell;
	      ISVREF(svref_arg_1,(SI_Long)4L) = g2_cell_array;
	      svref_arg_1 = Cell;
	      ISVREF(svref_arg_1,(SI_Long)5L) = FIX(index_1);
	      rebuild_backpointers_of_g2_expression_cell_chaining_links(Cell,
		      parent_frame);
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* REBUILD-BACKPOINTERS-OF-G2-EXPRESSION-CELL-CHAINING-LINKS */
Object rebuild_backpointers_of_g2_expression_cell_chaining_links(g2_expression_cell,
	    parent_frame)
    Object g2_expression_cell, parent_frame;
{
    Object forward_chaining_link, ab_loop_list_, ab_loop_desetq_;

    x_note_fn_call(155,55);
    forward_chaining_link = Nil;
    ab_loop_list_ = ISVREF(g2_expression_cell,(SI_Long)11L);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    forward_chaining_link = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    redirect_chaining_link_recipient(forward_chaining_link,parent_frame);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PUT-G2-EXPRESSION-CELL-CHAINING-LINKS */
Object put_g2_expression_cell_chaining_links(g2_expression_cell,
	    chaining_links,gensymed_symbol)
    Object g2_expression_cell, chaining_links, gensymed_symbol;
{
    Object old_links, current_block_of_dependent_frame;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,56);
    old_links = ISVREF(g2_expression_cell,(SI_Long)11L);
    current_block_of_dependent_frame = Loading_kb_p ? 
	    Qdependent_frame_has_no_owner : Current_block_of_dependent_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(g2_expression_cell,FIX((SI_Long)11L)) = chaining_links;
      deinstall_chaining_links(old_links);
      install_chaining_links(chaining_links);
      result = VALUES_1(chaining_links);
    POP_SPECIAL();
    return result;
}

static Object Qg2_expression_cell_chaining_links;  /* g2-expression-cell-chaining-links */

/* CLEANUP-FOR-G2-EXPRESSION-CELL */
Object cleanup_for_g2_expression_cell(g2_expression_cell)
    Object g2_expression_cell;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(155,57);
    frame = g2_expression_cell;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_expression_cell)) {
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
    return change_slot_value(3,g2_expression_cell,
	    Qg2_expression_cell_chaining_links,Nil);
}

static Object Qcell_class;         /* cell-class */

/* CONVERT-CELL-TYPE-TO-TYPE-SPECIFICATION */
Object convert_cell_type_to_type_specification(cell_type)
    Object cell_type;
{
    x_note_fn_call(155,58);
    if (CONSP(cell_type) && EQ(CAR(cell_type),Qcell_class))
	return make_class_type_specification(CDR(cell_type));
    else
	return VALUES_1(cell_type);
}

static Object Qg2_query_cell;      /* g2-query-cell */

/* REGISTER-QUERY-CELL */
Object register_query_cell(g2_cell_array)
    Object g2_cell_array;
{
    Object new_location, managed_array, query_cell, temp;
    SI_Long svref_arg_2;

    x_note_fn_call(155,59);
    new_location = find_new_location_for_cell(g2_cell_array);
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    query_cell = make_frame(Qg2_query_cell);
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = FIXNUM_ADD(new_location,Managed_array_index_offset);
	SVREF(managed_array,temp) = query_cell;
    }
    else {
	temp = ISVREF(managed_array,(IFIX(new_location) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = IFIX(new_location) & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = query_cell;
    }
    return VALUES_1(new_location);
}

/* ACTIVATE-G2-QUERY-CELL */
Object activate_g2_query_cell(query_cell)
    Object query_cell;
{
    x_note_fn_call(155,60);
    return VALUES_1(Nil);
}

/* DEACTIVATE-G2-QUERY-CELL */
Object deactivate_g2_query_cell(query_cell)
    Object query_cell;
{
    x_note_fn_call(155,61);
    return VALUES_1(Nil);
}

/* RECLAIM-QUERY-CELL-CACHED-VALUE */
Object reclaim_query_cell_cached_value(query_cell_cached_value,frames_qm)
    Object query_cell_cached_value, frames_qm;
{
    Object last_1, next_qm, temp, svref_arg_2, trailer, value_cons_qm, value;
    Object eval_cons;

    x_note_fn_call(155,62);
    if (frames_qm) {
	if (query_cell_cached_value) {
	    last_1 = query_cell_cached_value;
	    next_qm = Nil;
	  next_loop:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop;
	    inline_note_reclaim_cons(last_1,Qeval);
	    last_1 = next_qm;
	    goto next_loop;
	  end_loop:
	    inline_note_reclaim_cons(last_1,Qeval);
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = query_cell_cached_value;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    else {
		temp = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = query_cell_cached_value;
		temp = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	}
    }
    else {
	trailer = CDR(query_cell_cached_value);
	value_cons_qm = Nil;
	value = Nil;
      next_loop_1:
	value_cons_qm = CDR(trailer);
	if ( !TRUEP(value_cons_qm))
	    goto end_loop_1;
	value = CAR(value_cons_qm);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	    reclaim_managed_simple_float_array_of_length_1(value);
	else if (text_string_p(value))
	    reclaim_text_string(value);
	trailer = value_cons_qm;
	goto next_loop_1;
      end_loop_1:
	if (query_cell_cached_value &&  !((SI_Long)0L == 
		inline_debugging_consing())) {
	    eval_cons = query_cell_cached_value;
	  next_loop_2:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,trailer))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_2;
	  end_loop_2:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = query_cell_cached_value;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = query_cell_cached_value;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer;
	}
	M_CDR(trailer) = Nil;
    }
    return VALUES_1(Nil);
}

Object The_type_description_of_query_cell_stream = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_query_cell_streams, Qchain_of_available_query_cell_streams);

DEFINE_VARIABLE_WITH_SYMBOL(Query_cell_stream_count, Qquery_cell_stream_count);

Object Chain_of_available_query_cell_streams_vector = UNBOUND;

/* QUERY-CELL-STREAM-STRUCTURE-MEMORY-USAGE */
Object query_cell_stream_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(155,63);
    temp = Query_cell_stream_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-QUERY-CELL-STREAM-COUNT */
Object outstanding_query_cell_stream_count()
{
    Object def_structure_query_cell_stream_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(155,64);
    gensymed_symbol = IFIX(Query_cell_stream_count);
    def_structure_query_cell_stream_variable = 
	    Chain_of_available_query_cell_streams;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_query_cell_stream_variable))
	goto end_loop;
    def_structure_query_cell_stream_variable = 
	    ISVREF(def_structure_query_cell_stream_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-QUERY-CELL-STREAM-1-1 */
Object reclaim_query_cell_stream_1_1(query_cell_stream)
    Object query_cell_stream;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(155,65);
    inline_note_reclaim_cons(query_cell_stream,Nil);
    structure_being_reclaimed = query_cell_stream;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(query_cell_stream,(SI_Long)2L));
      SVREF(query_cell_stream,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_query_cell_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(query_cell_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_query_cell_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = query_cell_stream;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-QUERY-CELL-STREAM */
Object reclaim_structure_for_query_cell_stream(query_cell_stream)
    Object query_cell_stream;
{
    x_note_fn_call(155,66);
    return reclaim_query_cell_stream_1_1(query_cell_stream);
}

static Object Qg2_defstruct_structure_name_query_cell_stream_g2_struct;  /* g2-defstruct-structure-name::query-cell-stream-g2-struct */

/* MAKE-PERMANENT-QUERY-CELL-STREAM-STRUCTURE-INTERNAL */
Object make_permanent_query_cell_stream_structure_internal()
{
    Object def_structure_query_cell_stream_variable;
    Object defstruct_g2_query_cell_stream_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(155,67);
    def_structure_query_cell_stream_variable = Nil;
    atomic_incff_symval(Qquery_cell_stream_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_query_cell_stream_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_query_cell_stream_variable = the_array;
	SVREF(defstruct_g2_query_cell_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_query_cell_stream_g2_struct;
	def_structure_query_cell_stream_variable = 
		defstruct_g2_query_cell_stream_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_query_cell_stream_variable);
}

/* MAKE-QUERY-CELL-STREAM-1-1 */
Object make_query_cell_stream_1_1(query_cell_stream_cached_value,
	    query_cell_stream_frame_serial_number,
	    query_cell_stream_current_position)
    Object query_cell_stream_cached_value;
    Object query_cell_stream_frame_serial_number;
    Object query_cell_stream_current_position;
{
    Object def_structure_query_cell_stream_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(155,68);
    def_structure_query_cell_stream_variable = 
	    ISVREF(Chain_of_available_query_cell_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_query_cell_stream_variable) {
	svref_arg_1 = Chain_of_available_query_cell_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_query_cell_stream_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_query_cell_stream_g2_struct;
    }
    else
	def_structure_query_cell_stream_variable = 
		make_permanent_query_cell_stream_structure_internal();
    inline_note_allocate_cons(def_structure_query_cell_stream_variable,Nil);
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)1L)) = 
	    query_cell_stream_cached_value;
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)2L)) = 
	    query_cell_stream_frame_serial_number;
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)3L)) = 
	    query_cell_stream_current_position;
    return VALUES_1(def_structure_query_cell_stream_variable);
}

/* MAKE-QUERY-CELL-STREAM-TO-CACHED-VALUE */
Object make_query_cell_stream_to_cached_value(query_cell_cached_value,
	    frame_serial_number_qm)
    Object query_cell_cached_value, frame_serial_number_qm;
{
    Object def_structure_query_cell_stream_variable, temp, svref_arg_2;
    Object svref_new_value, new_stream;

    x_note_fn_call(155,69);
    def_structure_query_cell_stream_variable = 
	    ISVREF(Chain_of_available_query_cell_streams_vector,
	    IFIX(Current_thread_index));
    if (def_structure_query_cell_stream_variable) {
	temp = Chain_of_available_query_cell_streams_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_query_cell_stream_variable,
		(SI_Long)0L);
	SVREF(temp,svref_arg_2) = svref_new_value;
	SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_query_cell_stream_g2_struct;
    }
    else
	def_structure_query_cell_stream_variable = 
		make_permanent_query_cell_stream_structure_internal();
    inline_note_allocate_cons(def_structure_query_cell_stream_variable,Nil);
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)1L)) = 
	    query_cell_cached_value;
    temp = copy_frame_serial_number(frame_serial_number_qm);
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)2L)) = temp;
    temp = CDR(query_cell_cached_value);
    SVREF(def_structure_query_cell_stream_variable,FIX((SI_Long)3L)) = temp;
    new_stream = def_structure_query_cell_stream_variable;
    temp = FIXNUM_ADD1(CAR(query_cell_cached_value));
    M_CAR(query_cell_cached_value) = temp;
    return VALUES_1(new_stream);
}

/* RECLAIM-QUERY-CELL-STREAM */
Object reclaim_query_cell_stream(query_cell_cached_value_stream)
    Object query_cell_cached_value_stream;
{
    Object gensymed_symbol, gensymed_symbol_1, structure_being_reclaimed, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(155,70);
    gensymed_symbol = ISVREF(query_cell_cached_value_stream,(SI_Long)1L);
    gensymed_symbol_1 = FIXNUM_SUB1(CAR(gensymed_symbol));
    if (IFIX(gensymed_symbol_1) == (SI_Long)0L)
	reclaim_query_cell_cached_value(gensymed_symbol,
		ISVREF(query_cell_cached_value_stream,(SI_Long)2L));
    else
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
    inline_note_reclaim_cons(query_cell_cached_value_stream,Nil);
    structure_being_reclaimed = query_cell_cached_value_stream;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_frame_serial_number(ISVREF(query_cell_cached_value_stream,
	      (SI_Long)2L));
      SVREF(query_cell_cached_value_stream,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_query_cell_streams_vector,
	    IFIX(Current_thread_index));
    SVREF(query_cell_cached_value_stream,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_query_cell_streams_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = query_cell_cached_value_stream;
    return VALUES_1(Nil);
}

/* REGISTER-QUERY-CELL-DESIGNATION */
Object register_query_cell_designation(g2_cell_array,index_1,
	    generic_designation,cell_type)
    Object g2_cell_array, index_1, generic_designation, cell_type;
{
    Object query_cell, svref_new_value;

    x_note_fn_call(155,71);
    query_cell = FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(IFIX(index_1) 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
	    (SI_Long)1023L);
    reclaim_slot_value(ISVREF(query_cell,(SI_Long)2L));
    reclaim_slot_value(ISVREF(query_cell,(SI_Long)3L));
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = copy_for_slot_value(generic_designation);
    SVREF(query_cell,FIX((SI_Long)2L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = copy_for_slot_value(cell_type);
    SVREF(query_cell,FIX((SI_Long)3L)) = svref_new_value;
    update_query_cell_cached_value(query_cell,g2_cell_array,index_1,Nil,Nil);
    return VALUES_1(Nil);
}

/* QUERY-CELL-STREAM-ITERATE-TO-UNDELETED-FRAME */
Object query_cell_stream_iterate_to_undeleted_frame(query_cell_stream_with_deleted_frame)
    Object query_cell_stream_with_deleted_frame;
{
    Object stored_frame_serial_number, temp, position_cons, gensymed_symbol, x;
    Object xa, ya;
    char temp_1;

    x_note_fn_call(155,72);
    stored_frame_serial_number = 
	    ISVREF(query_cell_stream_with_deleted_frame,(SI_Long)2L);
    temp = ISVREF(query_cell_stream_with_deleted_frame,(SI_Long)3L);
    position_cons = CDR(temp);
  next_loop:
    temp_1 =  !TRUEP(position_cons);
    if (temp_1);
    else {
	gensymed_symbol = ISVREF(CAR(position_cons),(SI_Long)3L);
	x = CAR(position_cons);
	temp_1 = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else if (FIXNUMP(stored_frame_serial_number))
	    temp_1 = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(stored_frame_serial_number,gensymed_symbol) :
		     TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(stored_frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(stored_frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp_1 =  !temp_1;
    }
    if (temp_1)
	goto end_loop;
    goto next_loop;
  end_loop:
    SVREF(query_cell_stream_with_deleted_frame,FIX((SI_Long)3L)) = 
	    position_cons;
    return VALUES_1( !TRUEP(position_cons) ? T : Nil);
    return VALUES_1(Qnil);
}

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object Qlong;               /* long */

static Object list_constant;       /* # */

/* COMPUTE-NEW-QUERY-CELL-VALUE */
Object compute_new_query_cell_value(g2_cell_array,index_1,query_cell)
    Object g2_cell_array, index_1, query_cell;
{
    Object parent_frame, cell_type, frame_type_qm, raw_type;
    Object current_computation_frame, new_values, frame, ab_loop_list_, x2;
    Object gensymed_symbol, gensymed_symbol_1, sub_class_bit_vector;
    Object temporary_constant, type1, type2, element, value_cons, temp_1;
    Object new_cache_qm, new_frame_serial_number_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,73);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    cell_type = ISVREF(query_cell,(SI_Long)3L);
    frame_type_qm = CONSP(cell_type) ? (EQ(CAR(cell_type),Qcell_class) ? T 
	    : Nil) : Qnil;
    raw_type = frame_type_qm ? CDR(cell_type) : cell_type;
    current_computation_frame = parent_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      new_values = serve_eval_list_of_designation_values(ISVREF(query_cell,
	      (SI_Long)2L));
      if (frame_type_qm) {
	  frame = Nil;
	  ab_loop_list_ = new_values;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (SIMPLE_VECTOR_P(frame) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > (SI_Long)2L &&  
		  !EQ(ISVREF(frame,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(frame,(SI_Long)1L);
	      gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? x2 : Qnil;
	  }
	  else
	      gensymed_symbol = Nil;
	  if (gensymed_symbol) {
	      gensymed_symbol_1 = 
		      lookup_global_or_kb_specific_property_value(raw_type,
		      Class_description_gkbprop);
	      if (gensymed_symbol_1) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
		  sub_class_vector_index = superior_class_bit_number >>  - 
			   - (SI_Long)3L;
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
	  if ( !temp) {
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
      else {
	  temporary_constant = Nil;
	  ab_loop_list_ = new_values;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  temporary_constant = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (SIMPLE_VECTOR_P(temporary_constant) && 
		  EQ(ISVREF(temporary_constant,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	      type1 = ISVREF(temporary_constant,(SI_Long)2L);
	      type2 = raw_type;
	      temp = EQ(type1,type2);
	      if (temp);
	      else
		  temp = EQ(type1,Qnumber) ? EQ(type2,Qnumber) || EQ(type2,
			  Qinteger) || EQ(type2,Qfloat) || EQ(type2,Qlong) 
			  || 
			  lookup_global_or_kb_specific_property_value(type2,
			  Numeric_data_type_gkbprop) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = EQ(type2,Qnumber) ? EQ(type1,Qnumber) || EQ(type1,
			  Qinteger) || EQ(type1,Qfloat) || EQ(type1,Qlong) 
			  || 
			  lookup_global_or_kb_specific_property_value(type1,
			  Numeric_data_type_gkbprop) : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = EQ(type1,Qinteger) || memq_function(type1,
			  list_constant) ? EQ(type2,Qinteger) || 
			  memq_function(type2,list_constant) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if ( !temp) {
	      temp = TRUEP(Nil);
	      goto end_2;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp = TRUEP(T);
	  goto end_2;
	  temp = TRUEP(Qnil);
	end_2:;
      }
      if ( !temp) {
	  element = Nil;
	  ab_loop_list_ = new_values;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  element = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (SIMPLE_VECTOR_P(element) && EQ(ISVREF(element,(SI_Long)0L),
		  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	      reclaim_temporary_constant_1(element);
	  goto next_loop_2;
	end_loop_2:;
	  reclaim_eval_list_1(new_values);
	  new_values = Nil;
      }
      if ( !TRUEP(frame_type_qm)) {
	  value_cons = new_values;
	  temporary_constant = Nil;
	next_loop_3:
	  if ( !TRUEP(value_cons))
	      goto end_loop_3;
	  temporary_constant = CAR(value_cons);
	  temp_1 = ISVREF(temporary_constant,(SI_Long)1L);
	  SVREF(temporary_constant,FIX((SI_Long)1L)) = Nil;
	  reclaim_temporary_constant_1(temporary_constant);
	  M_CAR(value_cons) = temp_1;
	  value_cons = M_CDR(value_cons);
	  goto next_loop_3;
	end_loop_3:;
      }
      new_cache_qm = new_values ? eval_cons_1(FIX((SI_Long)1L),new_values) 
	      : Nil;
      new_frame_serial_number_qm = new_values && frame_type_qm ? 
	      copy_frame_serial_number(Current_frame_serial_number) : Nil;
      update_query_cell_cached_value(query_cell,g2_cell_array,index_1,
	      new_cache_qm,new_frame_serial_number_qm);
      reclaim_frame_serial_number(new_frame_serial_number_qm);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qquery_cell_updated;  /* query-cell-updated */

/* UPDATE-QUERY-CELL-CACHED-VALUE */
Object update_query_cell_cached_value(query_cell,g2_cell_array,index_1,
	    new_cache_qm,frame_serial_number_qm)
    Object query_cell, g2_cell_array, index_1, new_cache_qm;
    Object frame_serial_number_qm;
{
    Object old_value_stream_qm, old_cache_qm, gensymed_symbol;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value, method;
    Object frame, temp, generic_method_name, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5;
    SI_Long id, temp_1;

    x_note_fn_call(155,74);
    old_value_stream_qm = Nil;
    old_cache_qm = ISVREF(query_cell,(SI_Long)4L);
    if (old_cache_qm || new_cache_qm) {
	if (old_cache_qm) {
	    old_value_stream_qm = 
		    make_query_cell_stream_to_cached_value(old_cache_qm,
		    ISVREF(query_cell,(SI_Long)5L));
	    gensymed_symbol = FIXNUM_SUB1(CAR(old_cache_qm));
	    if (IFIX(gensymed_symbol) == (SI_Long)0L)
		reclaim_query_cell_cached_value(old_cache_qm,
			ISVREF(query_cell,(SI_Long)5L));
	    else
		M_CAR(old_cache_qm) = gensymed_symbol;
	}
	ISVREF(query_cell,(SI_Long)4L) = new_cache_qm;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = ISVREF(query_cell,(SI_Long)5L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(query_cell,(SI_Long)5L) = svref_new_value;
	method = Qquery_cell_updated;
	frame = ISVREF(g2_cell_array,(SI_Long)2L);
	temp = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L);
	generic_method_name = method;
	id = (SI_Long)0L;
      next_loop:
	if (id >= IFIX(Maximum_number_of_generic_methods))
	    goto end_loop;
	if (EQ(ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
		id),generic_method_name)) {
	    temp_1 = id;
	    goto end_1;
	}
	id = id + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = id;
	goto end_1;
	temp_1 = IFIX(Qnil);
      end_1:;
	gensymed_symbol = ISVREF(ISVREF(temp,temp_1),(SI_Long)1L);
	gensymed_symbol_1 = frame;
	gensymed_symbol_2 = g2_cell_array;
	gensymed_symbol_3 = index_1;
	gensymed_symbol_4 = old_value_stream_qm;
	gensymed_symbol_5 = new_cache_qm ? 
		make_query_cell_stream_to_cached_value(new_cache_qm,
		frame_serial_number_qm) : Nil;
	inline_funcall_5(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5);
    }
    return VALUES_1(Nil);
}

/* RECLAIM-G2-QUERY-CELL-CACHED-VALUE-VALUE */
Object reclaim_g2_query_cell_cached_value_value(cached_value,g2_query_cell)
    Object cached_value, g2_query_cell;
{
    Object gensymed_symbol;

    x_note_fn_call(155,75);
    gensymed_symbol = FIXNUM_SUB1(CAR(cached_value));
    if (IFIX(gensymed_symbol) == (SI_Long)0L)
	reclaim_query_cell_cached_value(cached_value,ISVREF(g2_query_cell,
		(SI_Long)5L));
    else
	M_CAR(cached_value) = gensymed_symbol;
    ISVREF(g2_query_cell,(SI_Long)4L) = Nil;
    reclaim_frame_serial_number(ISVREF(g2_query_cell,(SI_Long)5L));
    ISVREF(g2_query_cell,(SI_Long)5L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-G2-QUERY-CELL-FRAME-SERIAL-NUMBER?-VALUE */
Object reclaim_g2_query_cell_frame_serial_number_qm_value(serial_number,
	    gensymed_symbol)
    Object serial_number, gensymed_symbol;
{
    x_note_fn_call(155,76);
    return VALUES_1(Nil);
}

/* ANALYZE-G2-QUERY-CELL-FOR-CONSISTENCY */
Object analyze_g2_query_cell_for_consistency(query_cell)
    Object query_cell;
{
    Object designation_qm;

    x_note_fn_call(155,77);
    designation_qm = ISVREF(query_cell,(SI_Long)2L);
    if (designation_qm)
	return analyze_compiled_form(designation_qm,Nil,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qg2_designation_cell;  /* g2-designation-cell */

/* REGISTER-DESIGNATION-CELL */
Object register_designation_cell(g2_cell_array,unique_designation,cell_type)
    Object g2_cell_array, unique_designation, cell_type;
{
    Object managed_array, new_cell, temp;
    SI_Long new_location, svref_arg_2;

    x_note_fn_call(155,78);
    new_location = IFIX(find_new_location_for_cell(g2_cell_array));
    managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
    new_cell = make_frame(Qg2_designation_cell);
    if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = new_location + IFIX(Managed_array_index_offset);
	ISVREF(managed_array,svref_arg_2) = new_cell;
    }
    else {
	temp = ISVREF(managed_array,(new_location >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = new_location & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = new_cell;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    temp = copy_for_slot_value(unique_designation);
    SVREF(new_cell,FIX((SI_Long)2L)) = temp;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    temp = copy_for_slot_value(cell_type);
    SVREF(new_cell,FIX((SI_Long)3L)) = temp;
    return VALUES_1(FIX(new_location));
}

/* REGISTER-DESIGNATION-CELL-DESIGNATION */
Object register_designation_cell_designation(g2_cell_array,index_1,
	    unique_designation,cell_type)
    Object g2_cell_array, index_1, unique_designation, cell_type;
{
    Object designation_cell, svref_new_value;

    x_note_fn_call(155,79);
    designation_cell = FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(IFIX(index_1) 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
	    (SI_Long)1023L);
    reclaim_slot_value(ISVREF(designation_cell,(SI_Long)2L));
    reclaim_slot_value(ISVREF(designation_cell,(SI_Long)3L));
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = copy_for_slot_value(unique_designation);
    SVREF(designation_cell,FIX((SI_Long)2L)) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = copy_for_slot_value(cell_type);
    SVREF(designation_cell,FIX((SI_Long)3L)) = svref_new_value;
    update_designation_cell_cached_value(designation_cell,g2_cell_array,
	    index_1,Nil,Nil);
    return VALUES_1(Nil);
}

/* ACTIVATE-G2-DESIGNATION-CELL */
Object activate_g2_designation_cell(designation_cell)
    Object designation_cell;
{
    x_note_fn_call(155,80);
    return VALUES_1(Nil);
}

/* DEACTIVATE-G2-DESIGNATION-CELL */
Object deactivate_g2_designation_cell(designation_cell)
    Object designation_cell;
{
    x_note_fn_call(155,81);
    return VALUES_1(Nil);
}

/* COMPUTE-NEW-DESIGNATION-CELL-VALUE */
Object compute_new_designation_cell_value(g2_cell_array,index_1,
	    designation_cell)
    Object g2_cell_array, index_1, designation_cell;
{
    Object type, current_computation_frame, new_value_qm, x2, gensymed_symbol;
    Object gensymed_symbol_1, sub_class_bit_vector, type1, type2, temp_1;
    Object new_frame_serial_number_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,82);
    type = ISVREF(designation_cell,(SI_Long)3L);
    current_computation_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	    0);
      new_value_qm = evaluate_designation(ISVREF(designation_cell,
	      (SI_Long)2L),Nil);
      if (new_value_qm) {
	  if (CONSP(type) && EQ(CAR(type),Qcell_class)) {
	      if (SIMPLE_VECTOR_P(new_value_qm) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_value_qm)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(new_value_qm,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(new_value_qm,(SI_Long)1L);
		  gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol = Nil;
	      if (gensymed_symbol) {
		  gensymed_symbol_1 = 
			  lookup_global_or_kb_specific_property_value(CDR(type),
			  Class_description_gkbprop);
		  if (gensymed_symbol_1) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
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
	      if ( !temp) {
		  if (SIMPLE_VECTOR_P(new_value_qm) && 
			  EQ(ISVREF(new_value_qm,(SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		      reclaim_temporary_constant_1(new_value_qm);
		  new_value_qm = Nil;
	      }
	  }
	  else {
	      temp =  !(SIMPLE_VECTOR_P(new_value_qm) && 
		      EQ(ISVREF(new_value_qm,(SI_Long)0L),
		      Qg2_defstruct_structure_name_temporary_constant_g2_struct));
	      if (temp);
	      else {
		  type1 = type;
		  type2 = ISVREF(new_value_qm,(SI_Long)2L);
		  temp =  !(EQ(type1,type2) || EQ(type1,Qnumber) && 
			  (EQ(type2,Qnumber) || EQ(type2,Qinteger) || 
			  EQ(type2,Qfloat) || EQ(type2,Qlong) || 
			  lookup_global_or_kb_specific_property_value(type2,
			  Numeric_data_type_gkbprop)) || EQ(type2,Qnumber) 
			  && (EQ(type1,Qnumber) || EQ(type1,Qinteger) || 
			  EQ(type1,Qfloat) || EQ(type1,Qlong) || 
			  lookup_global_or_kb_specific_property_value(type1,
			  Numeric_data_type_gkbprop)) || (EQ(type1,
			  Qinteger) || memq_function(type1,list_constant)) 
			  && (EQ(type2,Qinteger) || memq_function(type2,
			  list_constant)));
	      }
	      if (temp) {
		  if (SIMPLE_VECTOR_P(new_value_qm) && 
			  EQ(ISVREF(new_value_qm,(SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct))
		      reclaim_temporary_constant_1(new_value_qm);
		  new_value_qm = Nil;
	      }
	      else {
		  temp_1 = ISVREF(new_value_qm,(SI_Long)1L);
		  SVREF(new_value_qm,FIX((SI_Long)1L)) = Nil;
		  reclaim_temporary_constant_1(new_value_qm);
		  new_value_qm = temp_1;
	      }
	  }
      }
      new_frame_serial_number_qm = new_value_qm && CONSP(type) && 
	      EQ(CAR(type),Qcell_class) ? 
	      copy_frame_serial_number(Current_frame_serial_number) : Nil;
      update_designation_cell_cached_value(designation_cell,g2_cell_array,
	      index_1,new_value_qm,new_frame_serial_number_qm);
      reclaim_frame_serial_number(new_frame_serial_number_qm);
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

static Object Qdesignation_cell_updated;  /* designation-cell-updated */

/* UPDATE-DESIGNATION-CELL-CACHED-VALUE */
Object update_designation_cell_cached_value(designation_cell,g2_cell_array,
	    index_1,new_cache_qm,frame_serial_number_qm)
    Object designation_cell, g2_cell_array, index_1, new_cache_qm;
    Object frame_serial_number_qm;
{
    Object old_cache_qm, old_frame_serial_number_qm;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value, method;
    Object frame, temp, generic_method_name, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, xa, ya, gensymed_symbol_5;
    SI_Long id, temp_1;
    char temp_2;

    x_note_fn_call(155,83);
    old_cache_qm = ISVREF(designation_cell,(SI_Long)4L);
    old_frame_serial_number_qm = ISVREF(designation_cell,(SI_Long)5L);
    if (old_cache_qm || new_cache_qm) {
	ISVREF(designation_cell,(SI_Long)4L) = new_cache_qm;
	frame_serial_number_setf_arg = frame_serial_number_qm;
	old = ISVREF(designation_cell,(SI_Long)5L);
	new_1 = frame_serial_number_setf_arg;
	svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && 
		(FIXNUMP(new_1) ||  !TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(designation_cell,(SI_Long)5L) = svref_new_value;
	method = Qdesignation_cell_updated;
	frame = ISVREF(g2_cell_array,(SI_Long)2L);
	temp = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L);
	generic_method_name = method;
	id = (SI_Long)0L;
      next_loop:
	if (id >= IFIX(Maximum_number_of_generic_methods))
	    goto end_loop;
	if (EQ(ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
		id),generic_method_name)) {
	    temp_1 = id;
	    goto end_1;
	}
	id = id + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp_1 = id;
	goto end_1;
	temp_1 = IFIX(Qnil);
      end_1:;
	gensymed_symbol = ISVREF(ISVREF(temp,temp_1),(SI_Long)1L);
	gensymed_symbol_1 = frame;
	gensymed_symbol_2 = g2_cell_array;
	gensymed_symbol_3 = index_1;
	temp_2 =  !TRUEP(old_frame_serial_number_qm);
	if (temp_2);
	else {
	    gensymed_symbol_4 = ISVREF(old_cache_qm,(SI_Long)3L);
	    temp_2 = SIMPLE_VECTOR_P(old_cache_qm) ? 
		    EQ(ISVREF(old_cache_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_2);
	    else
		temp_2 = FIXNUMP(gensymed_symbol_4) ? 
			IFIX(gensymed_symbol_4) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp_2);
	    else if (FIXNUMP(old_frame_serial_number_qm))
		temp_2 = FIXNUMP(gensymed_symbol_4) ? 
			FIXNUM_LT(old_frame_serial_number_qm,
			gensymed_symbol_4) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_4))
		temp_2 = TRUEP(Nil);
	    else {
		xa = M_CAR(old_frame_serial_number_qm);
		ya = M_CAR(gensymed_symbol_4);
		temp_2 = FIXNUM_LT(xa,ya);
		if (temp_2);
		else
		    temp_2 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(old_frame_serial_number_qm),
			    M_CDR(gensymed_symbol_4)) : TRUEP(Qnil);
	    }
	    temp_2 =  !temp_2;
	}
	gensymed_symbol_4 = temp_2 ? old_cache_qm : Nil;
	gensymed_symbol_5 = new_cache_qm;
	inline_funcall_5(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4,
		gensymed_symbol_5);
	if (old_cache_qm &&  !TRUEP(old_frame_serial_number_qm))
	    old_cache_qm = 
		    reclaim_managed_number_or_value_function(old_cache_qm);
    }
    return VALUES_1(Nil);
}

/* ANALYZE-G2-DESIGNATION-CELL-FOR-CONSISTENCY */
Object analyze_g2_designation_cell_for_consistency(g2_designation_cell)
    Object g2_designation_cell;
{
    Object designation_qm;

    x_note_fn_call(155,84);
    designation_qm = ISVREF(g2_designation_cell,(SI_Long)2L);
    if (designation_qm)
	return analyze_compiled_form(designation_qm,Nil,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qempty_expression_cell;  /* empty-expression-cell */

/* MAKE-EMPTY-EXPRESSION-CELL */
Object make_empty_expression_cell(g2_cell_array)
    Object g2_cell_array;
{
    Object current_block_of_dependent_frame, new_location, managed_array;
    Object new_cell, temp;
    SI_Long svref_arg_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(155,85);
    current_block_of_dependent_frame = Qdependent_frame_has_no_owner;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      new_location = find_new_location_for_cell(g2_cell_array);
      managed_array = ISVREF(g2_cell_array,(SI_Long)3L);
      new_cell = make_frame(Qg2_expression_cell);
      if (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	      Maximum_in_place_array_size)) {
	  temp = FIXNUM_ADD(new_location,Managed_array_index_offset);
	  SVREF(managed_array,temp) = new_cell;
      }
      else {
	  temp = ISVREF(managed_array,(IFIX(new_location) >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L);
	  svref_arg_2 = IFIX(new_location) & (SI_Long)1023L;
	  ISVREF(temp,svref_arg_2) = new_cell;
      }
      ISVREF(new_cell,(SI_Long)4L) = g2_cell_array;
      ISVREF(new_cell,(SI_Long)5L) = new_location;
      if (Noting_changes_to_kb_p)
	  note_change_to_dependent_frame_1();
      SVREF(new_cell,FIX((SI_Long)2L)) = Qempty_expression_cell;
      result = VALUES_1(new_location);
    POP_SPECIAL();
    return result;
}

static Object Qg2_expression_cell_byte_code_body;  /* g2-expression-cell-byte-code-body */

static Object Qg2_expression_cell_value_type;  /* g2-expression-cell-value-type */

/* REMOVE-COMPILATION-FROM-OBSOLETE-EXPRESSION-CELL */
Object remove_compilation_from_obsolete_expression_cell(expression_cell)
    Object expression_cell;
{
    x_note_fn_call(155,86);
    change_slot_value(3,expression_cell,Qg2_expression_cell_byte_code_body,
	    Nil);
    change_slot_value(3,expression_cell,Qg2_expression_cell_chaining_links,
	    Nil);
    return change_slot_value(3,expression_cell,
	    Qg2_expression_cell_value_type,Qempty_expression_cell);
}

static Object Qg2_lambda;          /* g2-lambda */

static Object Qschedule_expression_cell_execution_for_true_value_update;  /* schedule-expression-cell-execution-for-true-value-update */

/* REGISTER-EXPRESSION-CELL-DURING-COMPILATION */
Object register_expression_cell_during_compilation varargs_1(int, n)
{
    Object g2_cell_array, index_1, cell_installed_in_parent_qm;
    Object expression_qm, cell_value_type_specification_qm, domain_qm;
    Object attribute_qm, expression_cell, old_computation_style_qm;
    Object recompile_qm, reschedule_scan_qm, svref_new_value, temp;
    Object argument_and_type_list_qm, first_pass_compiled_expression_qm;
    Object temp_1, binding_name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loop_desetq_, byte_code_body_qm, chaining_links;
    char temp_2;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(155,87);
    INIT_ARGS_nonrelocating();
    g2_cell_array = REQUIRED_ARG_nonrelocating();
    index_1 = REQUIRED_ARG_nonrelocating();
    cell_installed_in_parent_qm = REQUIRED_ARG_nonrelocating();
    expression_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    cell_value_type_specification_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    domain_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    attribute_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    expression_cell = FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(IFIX(index_1) 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
	    (SI_Long)1023L);
    old_computation_style_qm = ISVREF(expression_cell,(SI_Long)3L);
    result = compare_computation_styles_for_installation_differences(Current_computation_style,
	    old_computation_style_qm);
    MVS_2(result,recompile_qm,reschedule_scan_qm);
    if (old_computation_style_qm)
	deregister_use_of_computation_style(old_computation_style_qm);
    if (Noting_changes_to_kb_p)
	note_change_to_dependent_frame_1();
    svref_new_value = 
	    register_use_of_computation_style(Current_computation_style);
    SVREF(expression_cell,FIX((SI_Long)3L)) = svref_new_value;
    if (expression_qm) {
	reclaim_slot_value(ISVREF(expression_cell,(SI_Long)2L));
	change_slot_value(3,expression_cell,
		Qg2_expression_cell_byte_code_body,Nil);
	change_slot_value(3,expression_cell,
		Qg2_expression_cell_chaining_links,Nil);
	if (CONSP(expression_qm) && EQ(M_CAR(expression_qm),Qg2_lambda)) {
	    temp = SECOND(expression_qm);
	    expression_qm = THIRD(expression_qm);
	    argument_and_type_list_qm = temp;
	}
	else
	    argument_and_type_list_qm = Nil;
	if (domain_qm && attribute_qm)
	    first_pass_compiled_expression_qm = 
		    compile_generic_formula(expression_qm,domain_qm,
		    attribute_qm,ISVREF(g2_cell_array,(SI_Long)2L));
	else {
	    temp_1 = expression_qm;
	    binding_name = Nil;
	    ab_loop_list_ = argument_and_type_list_qm;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    binding_name = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = gensym_cons_1(binding_name,Nil);
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
	    first_pass_compiled_expression_qm = compile_expression(temp_1,
		    Nil,temp);
	}
	byte_code_body_qm = first_pass_compiled_expression_qm ? 
		compile_expression_cell_for_stack(first_pass_compiled_expression_qm,
		argument_and_type_list_qm,
		cell_value_type_specification_qm) : Nil;
	chaining_links = byte_code_body_qm && 
		ISVREF(Current_computation_style,(SI_Long)23L) ? 
		generate_cell_chaining_links(Qschedule_expression_cell_execution_for_true_value_update,
		ISVREF(g2_cell_array,(SI_Long)2L),index_1,expression_qm) : Nil;
	if (Noting_changes_to_kb_p)
	    note_change_to_dependent_frame_1();
	svref_new_value =  !TRUEP(byte_code_body_qm) ||  
		!TRUEP(ISVREF(byte_code_body_qm,(SI_Long)4L)) ? 
		Qempty_expression_cell : 
		copy_for_slot_value(cell_value_type_specification_qm);
	SVREF(expression_cell,FIX((SI_Long)2L)) = svref_new_value;
	change_slot_value(3,expression_cell,
		Qg2_expression_cell_byte_code_body,byte_code_body_qm);
	change_slot_value(3,expression_cell,
		Qg2_expression_cell_chaining_links,chaining_links);
    }
    else if (recompile_qm)
	recompile_item(Current_block_of_dependent_frame);
    if (reschedule_scan_qm && cell_installed_in_parent_qm) {
	temp = ISVREF(Current_block_of_dependent_frame,(SI_Long)8L);
	temp_2 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != 
		(IFIX(ISVREF(Current_block_of_dependent_frame,
		(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(Current_block_of_dependent_frame,
		(SI_Long)4L)) & (SI_Long)16777216L) &&  !((SI_Long)0L != 
		(IFIX(ISVREF(Current_block_of_dependent_frame,
		(SI_Long)4L)) & (SI_Long)8192L)) : TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	schedule_or_deschedule_g2_expression_cell_cyclic_task(expression_cell,
		Nil,Nil);
    return VALUES_1(Nil);
}

/* REGISTER-EXPRESSION-CELL-DURING-SLOT-PUTTER */
Object register_expression_cell_during_slot_putter(g2_cell_array,index_1,
	    cell_previously_installed_in_parent_qm)
    Object g2_cell_array, index_1, cell_previously_installed_in_parent_qm;
{
    Object expression_cell, computation_style, parent_frame, temp;
    Object parent_runnable_qm;

    x_note_fn_call(155,88);
    expression_cell = FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(IFIX(index_1) 
	    >>  -  - (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & 
	    (SI_Long)1023L);
    computation_style = ISVREF(expression_cell,(SI_Long)3L);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    temp = ISVREF(parent_frame,(SI_Long)8L);
    if ( !TRUEP(CAR(temp))) {
	parent_runnable_qm = (SI_Long)0L != (IFIX(ISVREF(parent_frame,
		(SI_Long)5L)) & (SI_Long)1L) ? T : Nil;
	if (parent_runnable_qm);
	else
	    parent_runnable_qm =  !TRUEP(Inside_breakpoint_p) && 
		    (SI_Long)0L != (IFIX(ISVREF(parent_frame,(SI_Long)4L)) 
		    & (SI_Long)16777216L) ? ( !((SI_Long)0L != 
		    (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
		    (SI_Long)8192L)) ? T : Nil) : Qnil;
    }
    else
	parent_runnable_qm = Nil;
    if (parent_runnable_qm &&  !TRUEP(cell_previously_installed_in_parent_qm))
	activate_g2_expression_cell(expression_cell);
    if (parent_runnable_qm && (System_is_running || (SI_Long)0L != 
	    (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & (SI_Long)16777216L)) 
	    && ISVREF(computation_style,(SI_Long)28L)) {
	schedule_expression_cell_execution(ISVREF(g2_cell_array,
		(SI_Long)2L),index_1,Nil);
	update_expression_cell_cached_value(expression_cell,g2_cell_array,
		index_1,Nil,Nil);
    }
    else if (parent_runnable_qm && System_has_paused &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(parent_frame,(SI_Long)4L)) & (SI_Long)16777216L)) 
	    && ISVREF(computation_style,(SI_Long)28L) && ( 
	    !TRUEP(ISVREF(computation_style,(SI_Long)21L)) || 
	    showing_p(parent_frame,Nil)))
	attempt_expression_cell_execution_during_slot_putter(expression_cell);
    else
	update_expression_cell_cached_value(expression_cell,g2_cell_array,
		index_1,Nil,Nil);
    return VALUES_1(Nil);
}

/* ACTIVATE-G2-EXPRESSION-CELL */
Object activate_g2_expression_cell(expression_cell)
    Object expression_cell;
{
    x_note_fn_call(155,89);
    schedule_or_deschedule_g2_expression_cell_cyclic_task(expression_cell,T,T);
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

static Object Qattempt_expression_cell_execution;  /* attempt-expression-cell-execution */

/* SCHEDULE-OR-DESCHEDULE-G2-EXPRESSION-CELL-CYCLIC-TASK */
Object schedule_or_deschedule_g2_expression_cell_cyclic_task(expression_cell,
	    initial_wait_qm,parent_being_activated_qm)
    Object expression_cell, initial_wait_qm, parent_being_activated_qm;
{
    Object computation_style, gensymed_symbol, structure_being_reclaimed, temp;
    Object svref_arg_2, scan_interval_qm, initial_wait_interval, parent_frame;
    Object temp_1, old, new_1, def_structure_schedule_task_variable;
    Object svref_new_value, task;
    char temp_2, svref_new_value_1;
    double arg, arg_1, gensymed_symbol_1, gensymed_symbol_2, aref_new_value;
    Declare_special(1);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(155,90);
    computation_style = ISVREF(expression_cell,(SI_Long)3L);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(expression_cell,(SI_Long)9L);
    if (CAS_SVREF(expression_cell,(SI_Long)9L,gensymed_symbol,Nil)) {
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
    if (computation_style) {
	scan_interval_qm = ISVREF(computation_style,(SI_Long)19L);
	initial_wait_interval = initial_wait_qm ? ISVREF(computation_style,
		(SI_Long)20L) : FIX((SI_Long)0L);
	parent_frame = ISVREF(ISVREF(expression_cell,(SI_Long)4L),(SI_Long)2L);
	temp_1 = ISVREF(parent_frame,(SI_Long)8L);
	if (( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != 
		(IFIX(ISVREF(parent_frame,(SI_Long)5L)) & (SI_Long)1L) ||  
		!TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
		(IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
		(SI_Long)16777216L) &&  !((SI_Long)0L != 
		(IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
		(SI_Long)8192L))) || parent_being_activated_qm) && 
		scan_interval_qm) {
	    temp_2 = FIXNUMP(scan_interval_qm) ? IFIX(scan_interval_qm) > 
		    (SI_Long)0L : TRUEP(Qnil);
	    if (temp_2);
	    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(scan_interval_qm) != 
		    (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(scan_interval_qm)) == 
		    (SI_Long)1L) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    arg = DFLOAT_ISAREF_1(scan_interval_qm,(SI_Long)0L);
		    arg_1 = 0.0;
		    temp_2 = arg > arg_1 &&  
			    !inline_nanp_for_comparison(arg) ?  
			    !inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
		}
		POP_LOCAL_ALLOCATION(0,0);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2 ?  !TRUEP(ISVREF(computation_style,(SI_Long)21L)) || 
		showing_p(parent_frame,Nil) : TRUEP(Nil)) {
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = ISVREF(expression_cell,(SI_Long)9L);
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
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)2L)) = Nil;
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)9L)) = Nil;
		task = def_structure_schedule_task_variable;
		temp = ISVREF(task,(SI_Long)1L);
		gensymed_symbol_1 = DFLOAT_ISAREF_1(Current_g2_time,
			(SI_Long)0L);
		gensymed_symbol_2 = FIXNUMP(initial_wait_interval) ? 
			(double)IFIX(initial_wait_interval) : 
			DFLOAT_ISAREF_1(initial_wait_interval,(SI_Long)0L);
		aref_new_value = gensymed_symbol_1 + gensymed_symbol_2;
		DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
		temp = ISVREF(task,(SI_Long)1L);
		aref_new_value = FIXNUMP(scan_interval_qm) ? 
			(double)IFIX(scan_interval_qm) : 
			DFLOAT_ISAREF_1(scan_interval_qm,(SI_Long)0L);
		DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
		svref_new_value_1 =  !((SI_Long)0L != 
			(IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
			(SI_Long)16777216L));
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		temp = ISVREF(computation_style,(SI_Long)18L);
		SVREF(task,FIX((SI_Long)4L)) = temp;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = 
			Qattempt_expression_cell_execution;
		temp = SYMBOL_FUNCTION(Qattempt_expression_cell_execution);
		SVREF(task,FIX((SI_Long)8L)) = temp;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
		SVREF(task,FIX((SI_Long)13L)) = expression_cell;
		SVREF(task,FIX((SI_Long)14L)) = Nil;
		svref_new_value_1 = (SI_Long)0L != 
			(IFIX(ISVREF(parent_frame,(SI_Long)4L)) & 
			(SI_Long)33554432L);
		SVREF(task,FIX((SI_Long)15L)) = svref_new_value_1 ? T : Nil;
		new_1 = task;
		if (CAS_SVREF(expression_cell,(SI_Long)9L,old,new_1)) {
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
			temp = 
				ISVREF(Chain_of_available_schedule_tasks_vector,
				IFIX(Current_thread_index));
			SVREF(old,FIX((SI_Long)0L)) = temp;
			temp = Chain_of_available_schedule_tasks_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = old;
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
		    temp = ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(new_1,FIX((SI_Long)0L)) = temp;
		    temp = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = new_1;
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	}
    }
    return VALUES_1(Nil);
}

/* DEACTIVATE-G2-EXPRESSION-CELL */
Object deactivate_g2_expression_cell(expression_cell)
    Object expression_cell;
{
    x_note_fn_call(155,91);
    cancel_expression_cell_computation(expression_cell);
    return VALUES_1(Nil);
}

/* ATTEMPT-EXPRESSION-CELL-EXECUTION-DURING-SLOT-PUTTER */
Object attempt_expression_cell_execution_during_slot_putter(expression_cell)
    Object expression_cell;
{
    Object priority_of_current_task, block;
    Declare_special(1);

    x_note_fn_call(155,92);
    priority_of_current_task = ISVREF(ISVREF(expression_cell,(SI_Long)3L),
	    (SI_Long)18L);
    PUSH_SPECIAL_WITH_SYMBOL(Priority_of_current_task,Qpriority_of_current_task,priority_of_current_task,
	    0);
      block = ISVREF(ISVREF(expression_cell,(SI_Long)4L),(SI_Long)2L);
      attempt_expression_cell_execution(expression_cell,Nil,(SI_Long)0L != 
	      (IFIX(ISVREF(block,(SI_Long)4L)) & (SI_Long)33554432L) ? T : 
	      Nil);
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* SCHEDULE-EXPRESSION-CELL-EXECUTION-FOR-TRUE-VALUE-UPDATE */
Object schedule_expression_cell_execution_for_true_value_update(containing_block,
	    index_1,ignored_frame,ignored_slot,ignored_old_value,
	    ignored_class_if_specific_qm)
    Object containing_block, index_1, ignored_frame, ignored_slot;
    Object ignored_old_value, ignored_class_if_specific_qm;
{
    Object temp;

    x_note_fn_call(155,93);
    temp = ISVREF(containing_block,(SI_Long)8L);
    if ( !TRUEP(CAR(temp)) && ((SI_Long)0L != 
	    (IFIX(ISVREF(containing_block,(SI_Long)5L)) & (SI_Long)1L) ||  
	    !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
	    (IFIX(ISVREF(containing_block,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(containing_block,(SI_Long)4L)) & (SI_Long)8192L))))
	return schedule_expression_cell_execution(containing_block,index_1,
		Nil);
    else
	return VALUES_1(Nil);
}

/* SCHEDULE-EXPRESSION-CELL-EXECUTION */
Object schedule_expression_cell_execution(containing_block,index_1,
	    override_update_when_shown_qm)
    Object containing_block, index_1, override_update_when_shown_qm;
{
    Object g2_cell_array, managed_array, expression_cell, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(155,94);
    g2_cell_array = get_lookup_slot_value_given_default(containing_block,
	    Qcell_array,Nil);
    managed_array = g2_cell_array ? ISVREF(g2_cell_array,(SI_Long)3L) : Nil;
    expression_cell = SIMPLE_VECTOR_P(managed_array) && 
	    EQ(ISVREF(managed_array,(SI_Long)0L),
	    Managed_array_unique_marker) && FIXNUM_LT(index_1,
	    ISVREF(managed_array,(SI_Long)1L)) ? 
	    (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L)) :
	     Nil;
    if (expression_cell) {
	sub_class_bit_vector = ISVREF(ISVREF(expression_cell,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
	schedule_expression_cell_execution_given_cell(expression_cell,
		containing_block,override_update_when_shown_qm);
    return VALUES_1(Nil);
}

/* SCHEDULE-EXPRESSION-CELL-EXECUTION-GIVEN-CELL */
Object schedule_expression_cell_execution_given_cell(expression_cell,
	    containing_block,override_update_when_shown_qm)
    Object expression_cell, containing_block, override_update_when_shown_qm;
{
    Object schedule_task_qm, computation_style, old, new_1;
    Object def_structure_schedule_task_variable, temp_1, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char temp, g2_p, svref_new_value_1;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(155,95);
    temp =  ! !EQ(ISVREF(expression_cell,(SI_Long)2L),Qempty_expression_cell);
    if (temp);
    else {
	schedule_task_qm = ISVREF(expression_cell,(SI_Long)7L);
	temp = schedule_task_qm ? ISVREF(schedule_task_qm,(SI_Long)6L) || 
		EQ(schedule_task_qm,Current_schedule_task) : TRUEP(Qnil);
    }
    if ( !temp) {
	computation_style = ISVREF(expression_cell,(SI_Long)3L);
	if (override_update_when_shown_qm ||  
		!TRUEP(ISVREF(computation_style,(SI_Long)21L)) || 
		showing_p(containing_block,Nil)) {
	    old = Nil;
	    new_1 = Nil;
	  next_loop:
	    old = ISVREF(expression_cell,(SI_Long)7L);
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
	    temp_1 = ISVREF(computation_style,(SI_Long)18L);
	    SVREF(task,FIX((SI_Long)4L)) = temp_1;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = Nil;
	    SVREF(task,FIX((SI_Long)10L)) = Nil;
	    g2_p =  !((SI_Long)0L != (IFIX(ISVREF(containing_block,
		    (SI_Long)4L)) & (SI_Long)16777216L));
	    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
	    temp_1 = ISVREF(task,(SI_Long)1L);
	    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
		    Current_real_time,(SI_Long)0L);
	    DFLOAT_ISASET_1(temp_1,(SI_Long)0L,aref_new_value);
	    SVREF(task,FIX((SI_Long)7L)) = Qattempt_expression_cell_execution;
	    temp_1 = SYMBOL_FUNCTION(Qattempt_expression_cell_execution);
	    SVREF(task,FIX((SI_Long)8L)) = temp_1;
	    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)3L);
	    SVREF(task,FIX((SI_Long)13L)) = expression_cell;
	    SVREF(task,FIX((SI_Long)14L)) = Nil;
	    svref_new_value_1 = (SI_Long)0L != 
		    (IFIX(ISVREF(containing_block,(SI_Long)4L)) & 
		    (SI_Long)33554432L);
	    SVREF(task,FIX((SI_Long)15L)) = svref_new_value_1 ? T : Nil;
	    new_1 = task;
	    if (CAS_SVREF(expression_cell,(SI_Long)7L,old,new_1)) {
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
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(new_1,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = new_1;
	    }
	    goto next_loop;
	  end_loop:
	  end_1:;
	}
    }
    return VALUES_1(Nil);
}

/* EXPRESSION-CELL-COMPUTATION-IN-PROGRESS-P */
Object expression_cell_computation_in_progress_p(containing_block,index_1)
    Object containing_block, index_1;
{
    Object g2_cell_array, managed_array, expression_cell, sub_class_bit_vector;
    Object schedule_task_qm, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(155,96);
    g2_cell_array = get_lookup_slot_value_given_default(containing_block,
	    Qcell_array,Nil);
    managed_array = g2_cell_array ? ISVREF(g2_cell_array,(SI_Long)3L) : Nil;
    expression_cell = managed_array && FIXNUM_LT(index_1,
	    ISVREF(managed_array,(SI_Long)1L)) ? 
	    (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L)) :
	     Nil;
    if (expression_cell) {
	sub_class_bit_vector = ISVREF(ISVREF(expression_cell,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
    if (temp) {
	schedule_task_qm = ISVREF(expression_cell,(SI_Long)7L);
	temp_1 =  ! !(schedule_task_qm && (ISVREF(schedule_task_qm,
		(SI_Long)6L) || EQ(schedule_task_qm,
		Current_schedule_task))) ? T : Nil;
	if (temp_1);
	else
	    temp_1 =  ! !TRUEP(ISVREF(expression_cell,(SI_Long)8L)) ? T : Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CANCEL-SCHEDULED-EXPRESSION-CELL-EXECUTION */
Object cancel_scheduled_expression_cell_execution(containing_block,index_1)
    Object containing_block, index_1;
{
    Object g2_cell_array, managed_array, expression_cell, sub_class_bit_vector;
    Object gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    Object ab_loop_list_, temp_1, gensymed_symbol_6, gensymed_symbol_7;
    Object eval_cons, svref_arg_2, structure_being_reclaimed;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);

    x_note_fn_call(155,97);
    g2_cell_array = get_lookup_slot_value_given_default(containing_block,
	    Qcell_array,Nil);
    managed_array = g2_cell_array ? ISVREF(g2_cell_array,(SI_Long)3L) : Nil;
    expression_cell = managed_array && FIXNUM_LT(index_1,
	    ISVREF(managed_array,(SI_Long)1L)) ? 
	    (FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,
	    IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
	    ISVREF(ISVREF(managed_array,(IFIX(index_1) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L)) :
	     Nil;
    if (expression_cell) {
	sub_class_bit_vector = ISVREF(ISVREF(expression_cell,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(G2_expression_cell_class_description,
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
    if (temp) {
	gensymed_symbol_3 = expression_cell;
	gensymed_symbol_4 = ISVREF(gensymed_symbol_3,(SI_Long)8L);
	gensymed_symbol_5 = Nil;
	ab_loop_list_ = gensymed_symbol_4;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	gensymed_symbol_5 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = delete_eval_element_1(gensymed_symbol_3,
		ISVREF(gensymed_symbol_5,(SI_Long)36L));
	ISVREF(gensymed_symbol_5,(SI_Long)36L) = temp_1;
	if ( !TRUEP(ISVREF(gensymed_symbol_5,(SI_Long)38L)))
	    ISVREF(gensymed_symbol_5,(SI_Long)38L) = gensymed_symbol_3;
	goto next_loop;
      end_loop:
	ISVREF(gensymed_symbol_3,(SI_Long)8L) = Nil;
	if (gensymed_symbol_4) {
	    gensymed_symbol_5 = gensymed_symbol_4;
	    gensymed_symbol_6 = Nil;
	    gensymed_symbol_7 = Nil;
	  next_loop_1:
	    gensymed_symbol_6 = CAR(gensymed_symbol_5);
	    gensymed_symbol_7 = CDR(gensymed_symbol_5);
	    if (EQ(ISVREF(gensymed_symbol_6,(SI_Long)38L),gensymed_symbol_3)) {
		ISVREF(gensymed_symbol_6,(SI_Long)38L) = Nil;
		if ( !TRUEP(ISVREF(gensymed_symbol_6,(SI_Long)36L)))
		    withdraw_backward_chaining(gensymed_symbol_6);
	    }
	    if ( !TRUEP(gensymed_symbol_7))
		goto end_loop_1;
	    gensymed_symbol_5 = gensymed_symbol_7;
	    goto next_loop_1;
	  end_loop_1:
	    if (gensymed_symbol_4 &&  !((SI_Long)0L == 
		    inline_debugging_consing())) {
		eval_cons = gensymed_symbol_4;
	      next_loop_2:
		inline_note_reclaim_cons(eval_cons,Qeval);
		if (EQ(eval_cons,gensymed_symbol_5))
		    goto end_1;
		else if ( !TRUEP(eval_cons))
		    goto end_1;
		else
		    eval_cons = CDR(eval_cons);
		goto next_loop_2;
	      end_loop_2:
	      end_1:;
	    }
	    if (ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_eval_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = gensymed_symbol_4;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_5;
	    }
	    else {
		temp_1 = Available_eval_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_4;
		temp_1 = Available_eval_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_5;
	    }
	    M_CDR(gensymed_symbol_5) = Nil;
	}
	gensymed_symbol_3 = Nil;
      next_loop_3:
	gensymed_symbol_3 = ISVREF(expression_cell,(SI_Long)7L);
	if (CAS_SVREF(expression_cell,(SI_Long)7L,gensymed_symbol_3,Nil)) {
	    if (gensymed_symbol_3) {
		if (EQ(gensymed_symbol_3,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(gensymed_symbol_3,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol_3);
		inline_note_reclaim_cons(gensymed_symbol_3,Nil);
		structure_being_reclaimed = gensymed_symbol_3;
		PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
			0);
		  reclaim_schedule_task_args(ISVREF(gensymed_symbol_3,
			  (SI_Long)9L));
		  SVREF(gensymed_symbol_3,FIX((SI_Long)9L)) = Nil;
		POP_SPECIAL();
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol_3,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol_3;
	    }
	    goto end_2;
	}
	goto next_loop_3;
      end_loop_3:
      end_2:;
	update_expression_cell_cached_value(expression_cell,
		ISVREF(expression_cell,(SI_Long)4L),ISVREF(expression_cell,
		(SI_Long)5L),Nil,Nil);
    }
    return VALUES_1(Nil);
}

static Object Qsimulated_value;    /* simulated-value */

static Object Qinference_engine;   /* inference-engine */

static Object Qnever;              /* never */

static Object list_constant_1;     /* # */

/* ATTEMPT-EXPRESSION-CELL-EXECUTION */
Object attempt_expression_cell_execution(expression_cell,argument_list,
	    allow_inactive_objects_qm)
    Object expression_cell, argument_list, allow_inactive_objects_qm;
{
    Object g2_cell_array, parent_frame, byte_code_body, cell_type;
    Object result_value_qm, computation_style, backward_chaining_allowed_qm;
    Object current_block_of_dependent_frame, current_computation_style;
    Object network_access_attempt_qm, current_computation_flags;
    Object current_computation_activity;
    Object current_computation_component_particulars;
    Object current_computation_frame, current_computation_instance;
    Object current_environment, evaluating_simulator_procedure_qm;
    Object explanation_variables, saved_warning_level, saved_tracing_level;
    Object saved_breakpoint_level, gensymed_symbol_5;
    Object structure_being_reclaimed, temp, svref_arg_2, temp_1, new_vector;
    Object environment_vector, argument, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, index_1, ab_loop_bind_;
    SI_Long argument_count, argument_index;
    Declare_special(14);

    x_note_fn_call(155,98);
    g2_cell_array = ISVREF(expression_cell,(SI_Long)4L);
    parent_frame = ISVREF(g2_cell_array,(SI_Long)2L);
    byte_code_body = ISVREF(expression_cell,(SI_Long)10L);
    cell_type = ISVREF(expression_cell,(SI_Long)2L);
    result_value_qm = Nil;
    computation_style = ISVREF(expression_cell,(SI_Long)3L);
    backward_chaining_allowed_qm = ISVREF(computation_style,(SI_Long)24L);
    current_block_of_dependent_frame = parent_frame;
    PUSH_SPECIAL_WITH_SYMBOL(Current_block_of_dependent_frame,Qcurrent_block_of_dependent_frame,current_block_of_dependent_frame,
	    13);
      current_computation_style = computation_style;
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_style,Qcurrent_computation_style,current_computation_style,
	      12);
	network_access_attempt_qm = ISVREF(computation_style,(SI_Long)32L);
	gensymed_symbol = allow_inactive_objects_qm ? (SI_Long)16L : 
		(SI_Long)0L;
	gensymed_symbol_1 = EQ(network_access_attempt_qm,Qwrite) ? 
		(SI_Long)32L : (SI_Long)0L;
	gensymed_symbol_2 = EQ(network_access_attempt_qm,Qread) ? 
		(SI_Long)64L : (SI_Long)0L;
	gensymed_symbol_3 =  !TRUEP(backward_chaining_allowed_qm) ? 
		(SI_Long)128L : (SI_Long)0L;
	gensymed_symbol_4 =  !TRUEP(backward_chaining_allowed_qm) ? 
		(SI_Long)256L : (SI_Long)0L;
	current_computation_flags = FIX(gensymed_symbol + 
		gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3 
		+ gensymed_symbol_4);
	PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
		11);
	  current_computation_activity = FIX((SI_Long)0L);
	  PUSH_SPECIAL_WITH_SYMBOL(Current_computation_activity,Qcurrent_computation_activity,current_computation_activity,
		  10);
	    current_computation_component_particulars = 
		    slot_value_list_2(Qcell_array_element,
		    ISVREF(expression_cell,(SI_Long)5L));
	    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_component_particulars,Qcurrent_computation_component_particulars,current_computation_component_particulars,
		    9);
	      current_computation_frame = parent_frame;
	      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
		      8);
		current_computation_instance = expression_cell;
		PUSH_SPECIAL_WITH_SYMBOL(Current_computation_instance,Qcurrent_computation_instance,current_computation_instance,
			7);
		  current_environment = EQ(Qsimulator,
			  ISVREF(Current_computation_style,(SI_Long)27L)) ?
			   Qsimulated_value : Qinference_engine;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_environment,Qcurrent_environment,current_environment,
			  6);
		    evaluating_simulator_procedure_qm = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(Evaluating_simulator_procedure_qm,Qevaluating_simulator_procedure_qm,evaluating_simulator_procedure_qm,
			    5);
		      explanation_variables = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Explanation_variables,Qexplanation_variables,explanation_variables,
			      4);
			saved_warning_level = Nil;
			PUSH_SPECIAL_WITH_SYMBOL(Saved_warning_level,Qsaved_warning_level,saved_warning_level,
				3);
			  saved_tracing_level = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Saved_tracing_level,Qsaved_tracing_level,saved_tracing_level,
				  2);
			    saved_breakpoint_level = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Saved_breakpoint_level,Qsaved_breakpoint_level,saved_breakpoint_level,
				    1);
			      gensymed_symbol_5 = Nil;
			    next_loop:
			      gensymed_symbol_5 = ISVREF(expression_cell,
				      (SI_Long)7L);
			      if (CAS_SVREF(expression_cell,(SI_Long)7L,
				      gensymed_symbol_5,Nil)) {
				  if (gensymed_symbol_5) {
				      if (EQ(gensymed_symbol_5,
					      Current_schedule_task))
					  Current_schedule_task = Nil;
				      if (ISVREF(gensymed_symbol_5,
					      (SI_Long)6L))
					  cancel_and_reclaim_scheduled_queue_element_1(gensymed_symbol_5);
				      inline_note_reclaim_cons(gensymed_symbol_5,
					      Nil);
				      structure_being_reclaimed = 
					      gensymed_symbol_5;
				      PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
					      0);
					reclaim_schedule_task_args(ISVREF(gensymed_symbol_5,
						(SI_Long)9L));
					SVREF(gensymed_symbol_5,
						FIX((SI_Long)9L)) = Nil;
				      POP_SPECIAL();
				      temp = 
					      ISVREF(Chain_of_available_schedule_tasks_vector,
					      IFIX(Current_thread_index));
				      SVREF(gensymed_symbol_5,
					      FIX((SI_Long)0L)) = temp;
				      temp = 
					      Chain_of_available_schedule_tasks_vector;
				      svref_arg_2 = Current_thread_index;
				      SVREF(temp,svref_arg_2) = 
					      gensymed_symbol_5;
				  }
				  goto end_1;
			      }
			      goto next_loop;
			    end_loop:
			    end_1:;
			      if ( ! !EQ(ISVREF(expression_cell,
				      (SI_Long)2L),Qempty_expression_cell)) {
				  gensymed_symbol_5 = 
					  ISVREF(Current_computation_style,
					  (SI_Long)22L);
				  if ((gensymed_symbol_5 || 
					  Saved_warning_level ||  
					  !FIXNUMP(Breakpoint_level) || 
					  IFIX(Breakpoint_level) > 
					  (SI_Long)0L || 
					  IFIX(Tracing_message_level) > 
					  (SI_Long)0L || 
					  IFIX(Source_stepping_level) > 
					  (SI_Long)0L) &&  
					  !TRUEP(Debugging_reset) && 
					  ISVREF(Debugging_parameters,
					  (SI_Long)22L)) {
				      modify_tracing_and_breakpoints_context_on_entry(Current_computation_frame,
					      gensymed_symbol_5);
				      if (IFIX(Breakpoint_level) > 
					      (SI_Long)0L || 
					      IFIX(Tracing_message_level) 
					      > (SI_Long)0L) {
					  temp_1 = Current_computation_frame;
					  issue_tracing_and_breakpoints_entry_message(temp_1,
						  enter_skipped_cell_evaluation_message());
				      }
				  }
				  update_expression_cell_cached_value(expression_cell,
					  g2_cell_array,
					  ISVREF(expression_cell,
					  (SI_Long)5L),Nil,Nil);
				  if (Saved_warning_level) {
				      if ((IFIX(Breakpoint_level) > 
					      (SI_Long)0L || 
					      IFIX(Tracing_message_level) 
					      > (SI_Long)0L) && 
					      ISVREF(Debugging_parameters,
					      (SI_Long)22L) &&  
					      !TRUEP(in_order_p(Current_computation_frame))) 
						  {
					  temp_1 = Current_computation_frame;
					  issue_tracing_and_breakpoint_exit_message(temp_1,
						  exit_skipped_cell_evaluation_message());
				      }
				      Warning_message_level = 
					      Saved_warning_level;
				      Tracing_message_level = 
					      Saved_tracing_level;
				      Breakpoint_level = 
					      Saved_breakpoint_level;
				      Source_stepping_level = 
					      Saved_source_stepping_level;
				  }
			      }
			      else {
				  gensymed_symbol_5 = 
					  ISVREF(Current_computation_style,
					  (SI_Long)22L);
				  if ((gensymed_symbol_5 || 
					  Saved_warning_level ||  
					  !FIXNUMP(Breakpoint_level) || 
					  IFIX(Breakpoint_level) > 
					  (SI_Long)0L || 
					  IFIX(Tracing_message_level) > 
					  (SI_Long)0L || 
					  IFIX(Source_stepping_level) > 
					  (SI_Long)0L) &&  
					  !TRUEP(Debugging_reset) && 
					  ISVREF(Debugging_parameters,
					  (SI_Long)22L)) {
				      modify_tracing_and_breakpoints_context_on_entry(Current_computation_frame,
					      gensymed_symbol_5);
				      if (IFIX(Breakpoint_level) > 
					      (SI_Long)0L || 
					      IFIX(Tracing_message_level) 
					      > (SI_Long)0L) {
					  temp_1 = Current_computation_frame;
					  issue_tracing_and_breakpoints_entry_message(temp_1,
						  enter_cell_evaluation_message());
				      }
				  }
				  open_wake_up_collection_function(Nil);
				  if (Profiling_enabled_qm) {
				      increment_profiling_calls(parent_frame);
				      posit_profiling_structure(parent_frame);
				  }
				  temp_1 = var_count(ISVREF(byte_code_body,
					  (SI_Long)4L));
				  new_vector = 
					  allocate_managed_simple_vector(buffer_size_for_partial_buffer(temp_1,
					  Environment_allocation_schemes));
				  index_1 = (SI_Long)0L;
				  ab_loop_bind_ = 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(new_vector));
				next_loop_1:
				  if (index_1 >= ab_loop_bind_)
				      goto end_loop_1;
				  ISVREF(new_vector,index_1) = Nil;
				  index_1 = index_1 + (SI_Long)1L;
				  goto next_loop_1;
				end_loop_1:;
				  environment_vector = new_vector;
				  argument_count = IFIX(length(argument_list));
				  argument = Nil;
				  ab_loop_list_ = argument_list;
				  argument_index = (SI_Long)1L;
				  ab_loop_iter_flag_ = T;
				next_loop_2:
				  if ( !TRUEP(ab_loop_list_))
				      goto end_loop_2;
				  argument = M_CAR(ab_loop_list_);
				  ab_loop_list_ = M_CDR(ab_loop_list_);
				  if ( !TRUEP(ab_loop_iter_flag_))
				      argument_index = argument_index + 
					      (SI_Long)1L;
				  ISVREF(environment_vector,
					  argument_index) = argument;
				  ab_loop_iter_flag_ = Nil;
				  goto next_loop_2;
				end_loop_2:;
				  Stack_expiration = Qnever;
				  temp_1 = ISVREF(byte_code_body,(SI_Long)3L);
				  stack_eval(byte_code_body,temp_1,
					  environment_vector,
					  c_native_clock_ticks_or_cache(Nil,
					  Nil),Nil,FIX((SI_Long)0L));
				  if ( ! !TRUEP(Stack_expiration)) {
				      result_value_qm = 
					      ISVREF(environment_vector,
					      (SI_Long)0L);
				      if ( !TRUEP(result_value_qm))
					  Stack_expiration = Nil;
				      else
					  SVREF(environment_vector,
						  FIX((SI_Long)0L)) = Nil;
				  }
				  argument_index = (SI_Long)1L;
				  ab_loop_bind_ = argument_count;
				next_loop_3:
				  if (argument_index > ab_loop_bind_)
				      goto end_loop_3;
				  ISVREF(environment_vector,
					  argument_index) = Nil;
				  argument_index = argument_index + 
					  (SI_Long)1L;
				  goto next_loop_3;
				end_loop_3:;
				  reclaim_environment_vector(environment_vector);
				  if (backward_chaining_allowed_qm &&  
					  !TRUEP(result_value_qm))
				      set_wake_ups_function(Nil);
				  clean_up_wake_ups_state_if_any();
				  update_expression_cell_cached_value(expression_cell,
					  g2_cell_array,
					  ISVREF(expression_cell,
					  (SI_Long)5L),result_value_qm,
					  type_specification_subtype_p(list_constant_1,
					  cell_type));
				  if (Saved_warning_level) {
				      if ((IFIX(Breakpoint_level) > 
					      (SI_Long)0L || 
					      IFIX(Tracing_message_level) 
					      > (SI_Long)0L) && 
					      ISVREF(Debugging_parameters,
					      (SI_Long)22L) &&  
					      !TRUEP(in_order_p(Current_computation_frame))) 
						  {
					  temp_1 = Current_computation_frame;
					  issue_tracing_and_breakpoint_exit_message(temp_1,
						  exit_cell_expression_evaluation_message(result_value_qm));
				      }
				      Warning_message_level = 
					      Saved_warning_level;
				      Tracing_message_level = 
					      Saved_tracing_level;
				      Breakpoint_level = 
					      Saved_breakpoint_level;
				      Source_stepping_level = 
					      Saved_source_stepping_level;
				  }
			      }
			      reclaim_slot_value_list_1(Current_computation_component_particulars);
			      temp_1 = clear_computation_context_variables();
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
    return VALUES_1(temp_1);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

/* ENTER-SKIPPED-CELL-EVALUATION-MESSAGE */
Object enter_skipped_cell_evaluation_message()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(155,99);
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
	      twrite_beginning_of_wide_string(array_constant,
		      FIX((SI_Long)32L));
	      denote_component_of_block(1,T);
	      twrite_beginning_of_wide_string(array_constant_1,
		      FIX((SI_Long)54L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object array_constant_2;    /* # */

static Object string_constant;     /* "." */

/* EXIT-SKIPPED-CELL-EVALUATION-MESSAGE */
Object exit_skipped_cell_evaluation_message()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(155,100);
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
	      twrite_beginning_of_wide_string(array_constant_2,
		      FIX((SI_Long)30L));
	      denote_component_of_block(1,T);
	      twrite(string_constant);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

/* ENTER-CELL-EVALUATION-MESSAGE */
Object enter_cell_evaluation_message()
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(155,101);
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
	      twrite_beginning_of_wide_string(array_constant_3,
		      FIX((SI_Long)30L));
	      denote_component_of_block(1,T);
	      twrite_beginning_of_wide_string(array_constant_4,
		      FIX((SI_Long)1L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_1;   /* "~NV was the value for " */

static Object array_constant_5;    /* # */

/* EXIT-CELL-EXPRESSION-EVALUATION-MESSAGE */
Object exit_cell_expression_evaluation_message(result_value_qm)
    Object result_value_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(155,102);
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
	      if (result_value_qm)
		  tformat(2,string_constant_1,result_value_qm);
	      else
		  twrite_beginning_of_wide_string(array_constant_5,
			  FIX((SI_Long)26L));
	      denote_component_of_block(1,T);
	      twrite(string_constant);
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CANCEL-EXPRESSION-CELL-COMPUTATION */
Object cancel_expression_cell_computation(expression_cell)
    Object expression_cell;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object ab_loop_list_, temp, gensymed_symbol_3, gensymed_symbol_4;
    Object eval_cons, svref_arg_2, structure_being_reclaimed;
    Declare_special(1);

    x_note_fn_call(155,103);
    gensymed_symbol = expression_cell;
    gensymed_symbol_1 = ISVREF(gensymed_symbol,(SI_Long)8L);
    gensymed_symbol_2 = Nil;
    ab_loop_list_ = gensymed_symbol_1;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    gensymed_symbol_2 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = delete_eval_element_1(gensymed_symbol,ISVREF(gensymed_symbol_2,
	    (SI_Long)36L));
    ISVREF(gensymed_symbol_2,(SI_Long)36L) = temp;
    if ( !TRUEP(ISVREF(gensymed_symbol_2,(SI_Long)38L)))
	ISVREF(gensymed_symbol_2,(SI_Long)38L) = gensymed_symbol;
    goto next_loop;
  end_loop:
    ISVREF(gensymed_symbol,(SI_Long)8L) = Nil;
    if (gensymed_symbol_1) {
	gensymed_symbol_2 = gensymed_symbol_1;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
      next_loop_1:
	gensymed_symbol_3 = CAR(gensymed_symbol_2);
	gensymed_symbol_4 = CDR(gensymed_symbol_2);
	if (EQ(ISVREF(gensymed_symbol_3,(SI_Long)38L),gensymed_symbol)) {
	    ISVREF(gensymed_symbol_3,(SI_Long)38L) = Nil;
	    if ( !TRUEP(ISVREF(gensymed_symbol_3,(SI_Long)36L)))
		withdraw_backward_chaining(gensymed_symbol_3);
	}
	if ( !TRUEP(gensymed_symbol_4))
	    goto end_loop_1;
	gensymed_symbol_2 = gensymed_symbol_4;
	goto next_loop_1;
      end_loop_1:
	if (gensymed_symbol_1 &&  !((SI_Long)0L == 
		    inline_debugging_consing())) {
	    eval_cons = gensymed_symbol_1;
	  next_loop_2:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,gensymed_symbol_2))
		goto end_1;
	    else if ( !TRUEP(eval_cons))
		goto end_1;
	    else
		eval_cons = CDR(eval_cons);
	    goto next_loop_2;
	  end_loop_2:
	  end_1:;
	}
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = gensymed_symbol_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = gensymed_symbol_2;
	}
	M_CDR(gensymed_symbol_2) = Nil;
    }
    gensymed_symbol = Nil;
  next_loop_3:
    gensymed_symbol = ISVREF(expression_cell,(SI_Long)7L);
    if (CAS_SVREF(expression_cell,(SI_Long)7L,gensymed_symbol,Nil)) {
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
    goto next_loop_3;
  end_loop_3:
  end_2:;
    gensymed_symbol = Nil;
  next_loop_4:
    gensymed_symbol = ISVREF(expression_cell,(SI_Long)9L);
    if (CAS_SVREF(expression_cell,(SI_Long)9L,gensymed_symbol,Nil)) {
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
	goto end_3;
    }
    goto next_loop_4;
  end_loop_4:
  end_3:;
    update_expression_cell_cached_value(expression_cell,
	    ISVREF(expression_cell,(SI_Long)4L),ISVREF(expression_cell,
	    (SI_Long)5L),Nil,Nil);
    return VALUES_1(Nil);
}

static Object Qobsolete_datum;     /* obsolete-datum */

static Object Qexpression_cell_updated;  /* expression-cell-updated */

/* UPDATE-EXPRESSION-CELL-CACHED-VALUE */
Object update_expression_cell_cached_value(expression_cell,g2_cell_array,
	    index_1,new_cache_qm,cache_obsolete_value_qm)
    Object expression_cell, g2_cell_array, index_1, new_cache_qm;
    Object cache_obsolete_value_qm;
{
    Object old_cache_qm, old_cache_encapsulated_qm, method, frame, temp;
    Object generic_method_name, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5;
    SI_Long id, temp_1;

    x_note_fn_call(155,104);
    old_cache_qm = ISVREF(expression_cell,(SI_Long)6L);
    old_cache_encapsulated_qm = Nil;
    if ( !TRUEP(new_cache_qm) && cache_obsolete_value_qm && old_cache_qm) {
	old_cache_encapsulated_qm = T;
	new_cache_qm = CONSP(old_cache_qm) && EQ(M_CDR(old_cache_qm),
		Qobsolete_datum) ? old_cache_qm : eval_cons_1(old_cache_qm,
		Qobsolete_datum);
    }
    ISVREF(expression_cell,(SI_Long)6L) = new_cache_qm;
    method = Qexpression_cell_updated;
    frame = ISVREF(g2_cell_array,(SI_Long)2L);
    temp = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L);
    generic_method_name = method;
    id = (SI_Long)0L;
  next_loop:
    if (id >= IFIX(Maximum_number_of_generic_methods))
	goto end_loop;
    if (EQ(ISVREF(Table_to_map_generic_method_id_to_generic_method_name,
	    id),generic_method_name)) {
	temp_1 = id;
	goto end_1;
    }
    id = id + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp_1 = id;
    goto end_1;
    temp_1 = IFIX(Qnil);
  end_1:;
    gensymed_symbol = ISVREF(ISVREF(temp,temp_1),(SI_Long)1L);
    gensymed_symbol_1 = frame;
    gensymed_symbol_2 = g2_cell_array;
    gensymed_symbol_3 = index_1;
    gensymed_symbol_4 = old_cache_qm;
    gensymed_symbol_5 = new_cache_qm;
    inline_funcall_5(gensymed_symbol,gensymed_symbol_1,gensymed_symbol_2,
	    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    if (old_cache_qm &&  !TRUEP(old_cache_encapsulated_qm)) {
	if ( !(FIXNUMP(old_cache_qm) || SYMBOLP(old_cache_qm) || 
		SIMPLE_VECTOR_P(old_cache_qm)))
	    reclaim_if_evaluation_value_1(old_cache_qm);
    }
    return VALUES_1(Nil);
}

/* ANALYZE-G2-EXPRESSION-CELL-FOR-CONSISTENCY */
Object analyze_g2_expression_cell_for_consistency(expression_cell)
    Object expression_cell;
{
    Object byte_code_body_qm;

    x_note_fn_call(155,105);
    byte_code_body_qm = ISVREF(expression_cell,(SI_Long)10L);
    if (byte_code_body_qm)
	analyze_byte_code_body_for_free_reference_consistency(byte_code_body_qm);
    return VALUES_1(Nil);
}

/* EVENT-UPDATE-STATUS-OF-CELL-ARRAY-SHOWING */
Object event_update_status_of_cell_array_showing(block,now_showing_qm)
    Object block, now_showing_qm;
{
    Object g2_cell_array_qm, managed_array_qm, cell_qm, sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol, gensymed_symbol_1;
    SI_Long gensymed_symbol_2;
    char temp;

    x_note_fn_call(155,106);
    g2_cell_array_qm = get_lookup_slot_value_given_default(block,
	    Qcell_array,Nil);
    managed_array_qm = g2_cell_array_qm ? ISVREF(g2_cell_array_qm,
	    (SI_Long)3L) : Nil;
    if (managed_array_qm) {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(managed_array_qm,(SI_Long)1L));
	cell_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	cell_qm = FIXNUM_LE(ISVREF(managed_array_qm,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(managed_array_qm,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(managed_array_qm,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	if (cell_qm) {
	    sub_class_bit_vector = ISVREF(ISVREF(cell_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(G2_expression_cell_class_description,
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
	    schedule_or_deschedule_g2_expression_cell_cyclic_task(cell_qm,
		    Nil,Nil);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

static Object Qab_gensym;          /* gensym */

/* RECOMPILE-CELL-ARRAY */
Object recompile_cell_array(block)
    Object block;
{
    Object cell_indexes_in_use, gensymed_symbol, gensymed_symbol_1;
    Object sub_class_bit_vector, managed_array, cell_annotations, row_part;
    Object ab_loop_list_, cell_part, ab_loop_list__1, contents_qm;
    Object compiled_cell_qm, cell_index_qm, cell_qm, managed_array_length_1;
    Object ab_loop_iter_flag_, cell, x2, cell_place_reference;
    Object gensymed_symbol_5, last_1, next_qm, temp_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long managed_array_length, cell_index;
    char temp;
    Declare_special(1);

    x_note_fn_call(155,107);
    cell_indexes_in_use = Nil;
    gensymed_symbol = ISVREF(block,(SI_Long)1L);
    gensymed_symbol_1 = 
	    lookup_global_or_kb_specific_property_value(Qnew_table,
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
	managed_array = ISVREF(get_lookup_slot_value_given_default(block,
		Qcell_array,Nil),(SI_Long)3L);
	managed_array_length = managed_array ? IFIX(ISVREF(managed_array,
		(SI_Long)1L)) : (SI_Long)0L;
	if (managed_array_length == (SI_Long)0L)
	    return VALUES_1(Nil);
	cell_annotations = ISVREF(block,(SI_Long)18L);
	row_part = Nil;
	ab_loop_list_ = get_subpart_collection(cell_annotations,Qsubparts,
		Qrow);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	row_part = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	cell_part = Nil;
	ab_loop_list__1 = get_subpart_collection(row_part,Qsubparts,Qcell);
	contents_qm = Nil;
	compiled_cell_qm = Nil;
	cell_index_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	cell_part = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	contents_qm = get_simple_part_feature(cell_part,Qcell_contents);
	if (CONSP(contents_qm)) {
	    cell_qm = M_CAR(contents_qm);
	    compiled_cell_qm = compiled_cell_expression_p(cell_qm) ? 
		    cell_qm : Qnil;
	}
	else
	    compiled_cell_qm = Nil;
	cell_index_qm = compiled_cell_qm ? 
		get_simple_part_feature(compiled_cell_qm,
		Qexpression_cell_index) : Qnil;
	if (cell_index_qm)
	    cell_indexes_in_use = gensym_cons_1(cell_index_qm,
		    cell_indexes_in_use);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    managed_array = Nil;
    managed_array_length_1 = Nil;
    cell_index = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop_2:
    managed_array = ISVREF(get_lookup_slot_value_given_default(block,
	    Qcell_array,Nil),(SI_Long)3L);
    managed_array_length_1 = managed_array ? ISVREF(managed_array,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    if ( !TRUEP(ab_loop_iter_flag_))
	cell_index = cell_index + (SI_Long)1L;
    if ( !(cell_index < IFIX(managed_array_length_1)))
	goto end_loop_2;
    cell = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(managed_array,cell_index 
	    + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(managed_array,(cell_index >>  -  - (SI_Long)10L) 
	    + (SI_Long)2L),cell_index & (SI_Long)1023L);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      if (Cell) {
	  gensymed_symbol = ISVREF(block,(SI_Long)1L);
	  gensymed_symbol_1 = 
		  lookup_global_or_kb_specific_property_value(Qnew_table,
		  Class_description_gkbprop);
	  if (gensymed_symbol_1) {
	      sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	      superior_class_bit_number = IFIX(ISVREF(gensymed_symbol_1,
		      (SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_2 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
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
	      if ( !TRUEP(memq_function(FIX(cell_index),
			  cell_indexes_in_use))) {
		  if (SIMPLE_VECTOR_P(Cell) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Cell)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(Cell,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(Cell,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp) {
		      gensymed_symbol = ISVREF(Cell,(SI_Long)1L);
		      sub_class_bit_vector = ISVREF(gensymed_symbol,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(G2_expression_cell_class_description,
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
			  temp = (SI_Long)0L < gensymed_symbol_2;
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  remove_compilation_from_obsolete_expression_cell(Cell);
		      else {
			  sub_class_bit_vector = ISVREF(gensymed_symbol,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(G2_query_cell_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol_2 = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_3 = (SI_Long)1L;
			      gensymed_symbol_4 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_3 = gensymed_symbol_3 << 
				      gensymed_symbol_4;
			      gensymed_symbol_2 = gensymed_symbol_2 & 
				      gensymed_symbol_3;
			      temp = (SI_Long)0L < gensymed_symbol_2;
			  }
			  else
			      temp = TRUEP(Nil);
			  if (temp);
			  else {
			      sub_class_bit_vector = 
				      ISVREF(gensymed_symbol,(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(G2_designation_cell_class_description,
				      (SI_Long)18L));
			      sub_class_vector_index = 
				      superior_class_bit_number >>  -  - 
				      (SI_Long)3L;
			      if (sub_class_vector_index < 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					  {
				  gensymed_symbol_2 = 
					  UBYTE_8_ISAREF_1(sub_class_bit_vector,
					  sub_class_vector_index);
				  gensymed_symbol_3 = (SI_Long)1L;
				  gensymed_symbol_4 = 
					  superior_class_bit_number & 
					  (SI_Long)7L;
				  gensymed_symbol_3 = gensymed_symbol_3 << 
					  gensymed_symbol_4;
				  gensymed_symbol_2 = gensymed_symbol_2 & 
					  gensymed_symbol_3;
				  temp = (SI_Long)0L < gensymed_symbol_2;
			      }
			      else
				  temp = TRUEP(Nil);
			  }
			  if (temp);
		      }
		  }
	      }
	  }
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)36L),(SI_Long)1L);
	  gensymed_symbol_1 = block;
	  gensymed_symbol_2 = cell_index;
	  cell_place_reference = inline_funcall_2(gensymed_symbol,
		  gensymed_symbol_1,FIX(gensymed_symbol_2));
	  gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(block,(SI_Long)1L),
		  (SI_Long)11L),(SI_Long)37L),(SI_Long)1L);
	  gensymed_symbol_1 = block;
	  gensymed_symbol_5 = ISVREF(M_CAR(cell_place_reference),(SI_Long)0L);
	  inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		  gensymed_symbol_5);
	  reclaim_evaluation_place_reference(cell_place_reference);
      }
    POP_SPECIAL();
    ab_loop_iter_flag_ = Nil;
    goto next_loop_2;
  end_loop_2:;
    if (cell_indexes_in_use) {
	if (cell_indexes_in_use) {
	    last_1 = cell_indexes_in_use;
	    next_qm = Nil;
	  next_loop_3:
	    next_qm = M_CDR(last_1);
	    if ( !TRUEP(next_qm))
		goto end_loop_3;
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    last_1 = next_qm;
	    goto next_loop_3;
	  end_loop_3:
	    inline_note_reclaim_cons(last_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cell_indexes_in_use;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cell_indexes_in_use;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = last_1;
	    }
	    M_CDR(last_1) = Nil;
	    return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

void cells_INIT()
{
    Object temp, temp_1, temp_2, reclaim_structure_for_query_cell_stream_1;
    Object Qgeneric_method_lambda_list, list_constant_13;
    Object Qrecompile_expression_at_component_particulars;
    Object Qcomponent_particulars, AB_package, list_constant_12;
    Object Qplace_reference_of_cell, Qcell_index, list_constant_11;
    Object Qgenerate_designation_of_cell, Qg2_cell_array_index;
    Object list_constant_10, Qnew_cache_qm, Qold_cache_qm, Qindex;
    Object list_constant_9, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object list_constant_8, Qnew_value_qm, Qold_value_qm;
    Object Qslot_value_reclaimer;
    Object Qreclaim_g2_query_cell_frame_serial_number_qm_value;
    Object Qg2_query_cell_frame_serial_number_qm;
    Object Qreclaim_g2_query_cell_cached_value_value;
    Object Qg2_query_cell_cached_value, Qinterval, Qseconds, list_constant_7;
    Object Qnew_stream, Qold_value_stream_qm, Qquery_cell_stream;
    Object Qreclaim_structure, Qoutstanding_query_cell_stream_count;
    Object Qquery_cell_stream_structure_memory_usage, Qutilities2;
    Object string_constant_31, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_30, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qclasses_which_define, Qcleanup;
    Object Qcleanup_for_g2_expression_cell, Qslot_putter;
    Object Qput_g2_expression_cell_chaining_links, Qcopy_frame;
    Object Qcopy_frame_for_g2_expression_cell;
    Object Qreclaim_g2_expression_cell_cached_value_value;
    Object Qg2_expression_cell_cached_value;
    Object Qreclaim_g2_expression_cell_computation_style_value;
    Object Qg2_expression_cell_computation_style;
    Object Qreclaim_g2_expression_cell_g2_cell_array_value;
    Object Qg2_expression_cell_g2_cell_array, Qabsent_slot_putter;
    Object Qput_g2_expression_cell_expression_where_slot_is_absent;
    Object Qg2_expression_cell_expression, string_constant_29;
    Object string_constant_28, list_constant_6, string_constant_27;
    Object string_constant_26, string_constant_25, string_constant_24;
    Object string_constant_23, string_constant_2;
    Object Qreclaim_g2_designation_cell_frame_serial_number_qm_value;
    Object Qg2_designation_cell_frame_serial_number_qm, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, Qg2_cell_array_cell;
    Object Qcopy_frame_for_g2_cell_array_cell, string_constant_16;
    Object list_constant_5, string_constant_15, Qg2_cell_array;
    Object Qcopy_frame_for_g2_cell_array;
    Object Qreclaim_g2_cell_array_parent_frame_value;
    Object Qg2_cell_array_parent_frame, string_constant_14, string_constant_13;
    Object Qdependent_frame, Qreclaim_set_of_all_permanent_computation_style;
    Object Qinitialize_set_of_all_permanent_computation_style;
    Object Qmake_computation_style_function, list_constant_4, Qcells, Kfuncall;
    Object list_constant_3;
    Object Qput_computation_style_break_message_level_where_slot_is_absent;
    Object Qcomputation_style_break_message_level;
    Object Qput_computation_style_warning_message_level_where_slot_is_absent;
    Object Qcomputation_style_warning_message_level;
    Object Qput_computation_style_trace_message_level_where_slot_is_absent;
    Object Qcomputation_style_trace_message_level;
    Object Qput_computation_style_may_cause_forward_chaining_where_slot_is_absent;
    Object Qcomputation_style_may_cause_forward_chaining;
    Object Qput_computation_style_may_cause_backward_chaining_where_slot_is_absent;
    Object Qcomputation_style_may_cause_backward_chaining;
    Object Qput_computation_style_invokable_via_backward_chaining_where_slot_is_absent;
    Object Qcomputation_style_invokable_via_backward_chaining;
    Object Qput_computation_style_invokable_via_forward_chaining_where_slot_is_absent;
    Object Qcomputation_style_invokable_via_forward_chaining;
    Object Qput_computation_style_reference_count_where_slot_is_absent;
    Object Qcomputation_style_reference_count, string_constant_12;
    Object string_constant_11, string_constant_10, list_constant_2;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, Kno_initial_value;

    x_note_fn_call(155,108);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qcell_index_currently_being_registered = 
	    STATIC_SYMBOL("CELL-INDEX-CURRENTLY-BEING-REGISTERED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcell_index_currently_being_registered,
	    Cell_index_currently_being_registered);
    Qcells = STATIC_SYMBOL("CELLS",AB_package);
    record_system_variable(Qcell_index_currently_being_registered,Qcells,
	    Nil,Qnil,Qnil,Qnil,Qt);
    Qcurrent_computation_style = STATIC_SYMBOL("CURRENT-COMPUTATION-STYLE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_computation_style,
	    Current_computation_style);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    record_system_variable(Qcurrent_computation_style,Qcells,
	    Kno_initial_value,Qnil,Qnil,Qnil,Qt);
    Qcomputation_style = STATIC_SYMBOL("COMPUTATION-STYLE",AB_package);
    list_constant_2 = STATIC_CONS(Qblock,Qnil);
    check_if_superior_classes_are_defined(Qcomputation_style,list_constant_2);
    string_constant_2 = STATIC_STRING("1l1l8t");
    string_constant_3 = 
	    STATIC_STRING("13Dy4z8r83Xjy83Xjy836hy836hy00001n1l8o1l83Cy1l8l000004z8r83IWy83IWy836hy836hy00001n1l8o1l83Hy1l8l000004z8r83IXy83IXy836hy836hy0l");
    string_constant_4 = 
	    STATIC_STRING("001n1l8o1l83Cy1l8l000004z8r83IYy83IYy836hy836hy00001n1l8o1l83Cy1l8l000004z8r83IQy83IQy836hy836hy0m001n1l8o1l83Cy1l8l000004z8r83I");
    string_constant_5 = 
	    STATIC_STRING("cy83Icy836hy836hy08k001n1l8o1l83Cy1l8l000004z8r83Iay83Iay836hy836hy00001n1l8o1l83Cy1l8l000004z8r83IUy83IUy836hy836hy08k001n1l8o1");
    string_constant_6 = 
	    STATIC_STRING("l83Cy1l8l000004z8r83ITy83ITy836hy836hy00001n1l8o1l83Cy1l8l000004z8r83IRy83IRy836hy836hy08k001n1l8o1l83Cy1l8l000004z8r83ISy83ISy8");
    string_constant_7 = 
	    STATIC_STRING("36hy836hy00001n1l8o1l83Cy1l8l000004z8r83Idy83Idy836hy836hy0837*y001n1l8o1l83Cy1l8l000004z8r83Iby83Iby836hy836hy08k001n1l8o1l83Cy");
    string_constant_8 = 
	    STATIC_STRING("1l8l000004z8r83IZy83IZy836hy836hy00001n1l8o1l83Cy1l8l000004z8r83W-y83W-y836hy836hy00001n1l8l1l8o1l83Hy000004z8r83W+y83W+y836hy83");
    string_constant_9 = 
	    STATIC_STRING("6hy00001n1l8l1l8o1l83Hy000004z8r83IVy83IVy836hy836hy00001n1l8o1l83Cy1l8l00000");
    string_constant_10 = 
	    STATIC_STRING("13Fy8q1n836hy1l9k8t1p83Xjy08o83Cy8l1p83IWy08o83Hy8l1p83IXyl8o83Cy8l1p83IYy08o83Cy8l1p83IQym8o83Cy8l1p83Icy8k8o83Cy8l1p83Iay08o83");
    string_constant_11 = 
	    STATIC_STRING("Cy8l1p83IUy8k8o83Cy8l1p83ITy08o83Cy8l1p83IRy8k8o83Cy8l1p83ISy08o83Cy8l1p83Idy837*y8o83Cy8l1p83Iby8k8o83Cy8l1p83IZy08o83Cy8l1o83W");
    string_constant_12 = 
	    STATIC_STRING("-y08o83Hy1o83W+y08o83Hy1p83IVy08o83Cy8l");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(list(7,string_constant_3,
	    string_constant_4,string_constant_5,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9));
    clear_optimized_constants();
    push_optimized_constant(Qblock);
    add_class_to_environment(9,Qcomputation_style,list_constant_2,Nil,temp,
	    Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(LIST_3(string_constant_10,
	    string_constant_11,string_constant_12)),Nil);
    Qpermanent_computation_style_p = 
	    STATIC_SYMBOL("PERMANENT-COMPUTATION-STYLE-P",AB_package);
    Qcomputation_style_reference_count = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-REFERENCE-COUNT",AB_package);
    Qput_computation_style_reference_count_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-REFERENCE-COUNT-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_reference_count_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_reference_count_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qcomputation_style_reference_count,
	    SYMBOL_FUNCTION(Qput_computation_style_reference_count_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_may_request_event_updates = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    Qcomputation_style_invokable_via_forward_chaining = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-INVOKABLE-VIA-FORWARD-CHAINING",
	    AB_package);
    Qput_computation_style_invokable_via_forward_chaining_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-INVOKABLE-VIA-FORWARD-CHAINING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_invokable_via_forward_chaining_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_invokable_via_forward_chaining_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_invokable_via_forward_chaining,
	    SYMBOL_FUNCTION(Qput_computation_style_invokable_via_forward_chaining_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_may_provide_data_on_request = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-PROVIDE-DATA-ON-REQUEST",
	    AB_package);
    Qcomputation_style_invokable_via_backward_chaining = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-INVOKABLE-VIA-BACKWARD-CHAINING",
	    AB_package);
    Qput_computation_style_invokable_via_backward_chaining_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-INVOKABLE-VIA-BACKWARD-CHAINING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_invokable_via_backward_chaining_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_invokable_via_backward_chaining_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_invokable_via_backward_chaining,
	    SYMBOL_FUNCTION(Qput_computation_style_invokable_via_backward_chaining_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_may_request_data_seeking = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-REQUEST-DATA-SEEKING",
	    AB_package);
    Qcomputation_style_may_cause_backward_chaining = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-CAUSE-BACKWARD-CHAINING",
	    AB_package);
    Qput_computation_style_may_cause_backward_chaining_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-MAY-CAUSE-BACKWARD-CHAINING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_may_cause_backward_chaining_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_may_cause_backward_chaining_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_may_cause_backward_chaining,
	    SYMBOL_FUNCTION(Qput_computation_style_may_cause_backward_chaining_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_may_provide_event_updates = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-PROVIDE-EVENT-UPDATES",
	    AB_package);
    Qcomputation_style_may_cause_forward_chaining = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-MAY-CAUSE-FORWARD-CHAINING",
	    AB_package);
    Qput_computation_style_may_cause_forward_chaining_where_slot_is_absent 
	    = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-MAY-CAUSE-FORWARD-CHAINING-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_may_cause_forward_chaining_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_may_cause_forward_chaining_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_may_cause_forward_chaining,
	    SYMBOL_FUNCTION(Qput_computation_style_may_cause_forward_chaining_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_trace_message_level = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-TRACE-MESSAGE-LEVEL",AB_package);
    Qput_computation_style_trace_message_level_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-TRACE-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_trace_message_level_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_trace_message_level_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_trace_message_level,
	    SYMBOL_FUNCTION(Qput_computation_style_trace_message_level_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_warning_message_level = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-WARNING-MESSAGE-LEVEL",
	    AB_package);
    Qput_computation_style_warning_message_level_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-WARNING-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_warning_message_level_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_warning_message_level_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_warning_message_level,
	    SYMBOL_FUNCTION(Qput_computation_style_warning_message_level_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_break_message_level = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-BREAK-MESSAGE-LEVEL",AB_package);
    Qput_computation_style_break_message_level_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-COMPUTATION-STYLE-BREAK-MESSAGE-LEVEL-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_computation_style_break_message_level_where_slot_is_absent,
	    STATIC_FUNCTION(put_computation_style_break_message_level_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcomputation_style_break_message_level,
	    SYMBOL_FUNCTION(Qput_computation_style_break_message_level_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcomputation_style_tracing_and_breakpoints = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qcomputation_style_priority = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-PRIORITY",AB_package);
    Qcomputation_style_scan_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-SCAN-INTERVAL",AB_package);
    Qcomputation_style_initial_scan_wait_interval = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-INITIAL-SCAN-WAIT-INTERVAL",
	    AB_package);
    Qcomputation_style_update_only_when_shown = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    Qcomputation_style_value_domain = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-VALUE-DOMAIN",AB_package);
    Qcomputation_style_update_after_edits = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-UPDATE-AFTER-EDITS",AB_package);
    Qcomputation_style_network_access_attempt = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-NETWORK-ACCESS-ATTEMPT",
	    AB_package);
    Number_of_buckets_in_computation_style_set = FIX((SI_Long)23L);
    Qset_of_all_permanent_computation_style = 
	    STATIC_SYMBOL("SET-OF-ALL-PERMANENT-COMPUTATION-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qset_of_all_permanent_computation_style,
	    Set_of_all_permanent_computation_style);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qinitialize_set_of_all_permanent_computation_style = 
	    STATIC_SYMBOL("INITIALIZE-SET-OF-ALL-PERMANENT-COMPUTATION-STYLE",
	    AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qinitialize_set_of_all_permanent_computation_style);
    Qreclaim_set_of_all_permanent_computation_style = 
	    STATIC_SYMBOL("RECLAIM-SET-OF-ALL-PERMANENT-COMPUTATION-STYLE",
	    AB_package);
    record_system_variable(Qset_of_all_permanent_computation_style,Qcells,
	    list_constant_3,Qnil,Qnil,
	    Qreclaim_set_of_all_permanent_computation_style,Qt);
    Qthe_only_dynamic_computation_style = 
	    STATIC_SYMBOL("THE-ONLY-DYNAMIC-COMPUTATION-STYLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qthe_only_dynamic_computation_style,
	    The_only_dynamic_computation_style);
    Qmake_computation_style_function = 
	    STATIC_SYMBOL("MAKE-COMPUTATION-STYLE-FUNCTION",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Kfuncall,
	    Qmake_computation_style_function);
    record_system_variable(Qthe_only_dynamic_computation_style,Qcells,
	    list_constant_4,Qnil,Qnil,Qnil,Qt);
    SET_SYMBOL_FUNCTION(Qmake_computation_style_function,
	    STATIC_FUNCTION(make_computation_style_function,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qinitialize_set_of_all_permanent_computation_style,
	    STATIC_FUNCTION(initialize_set_of_all_permanent_computation_style,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qreclaim_set_of_all_permanent_computation_style,
	    STATIC_FUNCTION(reclaim_set_of_all_permanent_computation_style,
	    NIL,FALSE,1,1));
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_5 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Qg2_cell_array,list_constant_5);
    string_constant_13 = 
	    STATIC_STRING("1m4z8r83MZy83MZy83MXy83MXy00001o1l8o1l8l1l83Hy1l83Uy000004z8r83MYy83MYy83MXy83MXy00001n1l8o1l8l1l83Cy00000");
    string_constant_14 = 
	    STATIC_STRING("1o8q1n83MXy1l83=fy8t1q83MZy08o8l83Hy83Uy1p83MYy08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(string_constant_13);
    add_class_to_environment(9,Qg2_cell_array,list_constant_5,Nil,temp,Nil,
	    temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_14),Nil);
    G2_cell_array_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_cell_array,
	    Class_description_gkbprop);
    Qg2_cell_array_parent_frame = 
	    STATIC_SYMBOL("G2-CELL-ARRAY-PARENT-FRAME",AB_package);
    Qreclaim_g2_cell_array_parent_frame_value = 
	    STATIC_SYMBOL("RECLAIM-G2-CELL-ARRAY-PARENT-FRAME-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_cell_array_parent_frame_value,
	    STATIC_FUNCTION(reclaim_g2_cell_array_parent_frame_value,NIL,
	    FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qg2_cell_array_parent_frame,
	    SYMBOL_FUNCTION(Qreclaim_g2_cell_array_parent_frame_value),
	    Qslot_value_reclaimer);
    Qdependent_frame_has_no_owner = 
	    STATIC_SYMBOL("DEPENDENT-FRAME-HAS-NO-OWNER",AB_package);
    Qcopy_frame_for_g2_cell_array = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-G2-CELL-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_g2_cell_array,
	    STATIC_FUNCTION(copy_frame_for_g2_cell_array,NIL,FALSE,1,1));
    Qcopy_frame = STATIC_SYMBOL("COPY-FRAME",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_g2_cell_array);
    set_get(Qg2_cell_array,Qcopy_frame,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_cell_array,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    Qg2_cell_array_cell = STATIC_SYMBOL("G2-CELL-ARRAY-CELL",AB_package);
    check_if_superior_classes_are_defined(Qg2_cell_array_cell,list_constant_5);
    string_constant_15 = STATIC_STRING("0");
    string_constant_16 = STATIC_STRING("1m8q1n835Fy1l83=fy8t");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(string_constant_15);
    add_class_to_environment(9,Qg2_cell_array_cell,list_constant_5,Nil,
	    temp,Nil,temp_1,list_constant_5,
	    regenerate_optimized_constant(string_constant_16),Nil);
    G2_cell_array_cell_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_cell_array_cell,
	    Class_description_gkbprop);
    Qcopy_frame_for_g2_cell_array_cell = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-G2-CELL-ARRAY-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_g2_cell_array_cell,
	    STATIC_FUNCTION(copy_frame_for_g2_cell_array_cell,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_g2_cell_array_cell);
    set_get(Qg2_cell_array_cell,Qcopy_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_cell_array_cell,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qg2_query_cell = STATIC_SYMBOL("G2-QUERY-CELL",AB_package);
    list_constant_6 = STATIC_CONS(Qg2_cell_array_cell,Qnil);
    check_if_superior_classes_are_defined(Qg2_query_cell,list_constant_6);
    string_constant_17 = 
	    STATIC_STRING("1o4z8r83NKy83NKy83NHy83NHy00001n1l8o1l8l1l83Cy000004z8r83NLy83NLy83NHy83NHy00001n1l8o1l8l1l83Cy000004z8r83NIy83NIy83NHy83NHy0000");
    string_constant_18 = 
	    STATIC_STRING("1m1l8o1l8l000004z8r83NJy83NJy83NHy83NHy00001m1l8o1l8l00000");
    string_constant_19 = 
	    STATIC_STRING("1q8q1n83NHy1l835Fy8t1p83NKy08o8l83Cy1p83NLy08o8l83Cy1o83NIy08o8l1o83NJy08o8l");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_17,
	    string_constant_18));
    add_class_to_environment(9,Qg2_query_cell,list_constant_6,Nil,temp,Nil,
	    temp_1,list_constant_6,
	    regenerate_optimized_constant(string_constant_19),Nil);
    G2_query_cell_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_query_cell,
	    Class_description_gkbprop);
    Qg2_designation_cell = STATIC_SYMBOL("G2-DESIGNATION-CELL",AB_package);
    check_if_superior_classes_are_defined(Qg2_designation_cell,
	    list_constant_6);
    string_constant_20 = 
	    STATIC_STRING("1o4z8r83Mey83Mey83Mcy83Mcy00001n1l8o1l8l1l83Cy000004z8r83Mgy83Mgy83Mcy83Mcy00001n1l8o1l8l1l83Cy000004z8r83Mdy83Mdy83Mcy83Mcy0000");
    string_constant_21 = 
	    STATIC_STRING("1m1l8o1l8l000004z8r83Mfy83Mfy83Mcy83Mcy00001m1l8o1l8l00000");
    string_constant_22 = 
	    STATIC_STRING("1q8q1n83Mcy1l835Fy8t1p83Mey08o8l83Cy1p83Mgy08o8l83Cy1o83Mdy08o8l1o83Mfy08o8l");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_20,
	    string_constant_21));
    add_class_to_environment(9,Qg2_designation_cell,list_constant_6,Nil,
	    temp,Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(string_constant_22),Nil);
    G2_designation_cell_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_designation_cell,
	    Class_description_gkbprop);
    Qg2_designation_cell_frame_serial_number_qm = 
	    STATIC_SYMBOL("G2-DESIGNATION-CELL-FRAME-SERIAL-NUMBER\?",
	    AB_package);
    Qreclaim_g2_designation_cell_frame_serial_number_qm_value = 
	    STATIC_SYMBOL("RECLAIM-G2-DESIGNATION-CELL-FRAME-SERIAL-NUMBER\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_designation_cell_frame_serial_number_qm_value,
	    STATIC_FUNCTION(reclaim_g2_designation_cell_frame_serial_number_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_designation_cell_frame_serial_number_qm,
	    SYMBOL_FUNCTION(Qreclaim_g2_designation_cell_frame_serial_number_qm_value),
	    Qslot_value_reclaimer);
    Qg2_expression_cell = STATIC_SYMBOL("G2-EXPRESSION-CELL",AB_package);
    check_if_superior_classes_are_defined(Qg2_expression_cell,list_constant_6);
    string_constant_23 = 
	    STATIC_STRING("1v4z8r83Mry83Mry83Miy83Miy00001n1l8o1l8l1l83Cy000004z8r83Mmy83Mmy83Miy83Miy00001o1l8o1l8l1l83Cy1l83Uy000004z8r83Moy83Moy83Miy83M");
    string_constant_24 = 
	    STATIC_STRING("iy00001o1l8o1l8l1l83Hy1l83Uy000004z8r83Mpy83Mpy83Miy83Miy00001m1l8o1l8l000004z8r83Mky83Mky83Miy83Miy00001n1l8o1l8l1l83Uy000004z8");
    string_constant_25 = 
	    STATIC_STRING("r83Msy83Msy83Miy83Miy00001n1l8o1l8l1l83Uy000004z8r83bny83bny83Miy83Miy00001n1l8o1l8l1l83Uy000004z8r83Mny83Mny83Miy83Miy00001n1l8");
    string_constant_26 = 
	    STATIC_STRING("o1l8l1l83Uy000004z8r83Mjy83Mjy83Miy83Miy00001n1l8o1l8l1l83Cy000004z8r83Mly83Mly83Miy83Miy00001n1l8o1l8l1l83Cy000004z8r83Mqy83Mqy");
    string_constant_27 = STATIC_STRING("83Miy83Miy00001n1l8o1l8l1l83Uy00000");
    string_constant_28 = 
	    STATIC_STRING("1x8q1n83Miy1l835Fy8t1p83Mry08o8l83Cy1q83Mmy08o8l83Cy83Uy1q83Moy08o8l83Hy83Uy1o83Mpy08o8l1p83Mky08o8l83Uy1p83Msy08o8l83Uy1p83bny0");
    string_constant_29 = 
	    STATIC_STRING("8o8l83Uy1p83Mny08o8l83Uy1p83Mjy08o8l83Cy1p83Mly08o8l83Cy1p83Mqy08o8l83Uy");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_23,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27));
    add_class_to_environment(9,Qg2_expression_cell,list_constant_6,Nil,
	    temp,Nil,temp_1,list_constant_6,
	    regenerate_optimized_constant(LIST_2(string_constant_28,
	    string_constant_29)),Nil);
    G2_expression_cell_class_description = 
	    lookup_global_or_kb_specific_property_value(Qg2_expression_cell,
	    Class_description_gkbprop);
    Qg2_expression_cell_expression = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-EXPRESSION",AB_package);
    Qput_g2_expression_cell_expression_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-G2-EXPRESSION-CELL-EXPRESSION-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_expression_cell_expression_where_slot_is_absent,
	    STATIC_FUNCTION(put_g2_expression_cell_expression_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_expression_cell_expression,
	    SYMBOL_FUNCTION(Qput_g2_expression_cell_expression_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qg2_expression_cell_g2_cell_array = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-G2-CELL-ARRAY",AB_package);
    Qreclaim_g2_expression_cell_g2_cell_array_value = 
	    STATIC_SYMBOL("RECLAIM-G2-EXPRESSION-CELL-G2-CELL-ARRAY-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_g2_cell_array_value,
	    STATIC_FUNCTION(reclaim_g2_expression_cell_g2_cell_array_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_expression_cell_g2_cell_array,
	    SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_g2_cell_array_value),
	    Qslot_value_reclaimer);
    Qg2_expression_cell_computation_style = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-COMPUTATION-STYLE",AB_package);
    Qreclaim_g2_expression_cell_computation_style_value = 
	    STATIC_SYMBOL("RECLAIM-G2-EXPRESSION-CELL-COMPUTATION-STYLE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_computation_style_value,
	    STATIC_FUNCTION(reclaim_g2_expression_cell_computation_style_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_expression_cell_computation_style,
	    SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_computation_style_value),
	    Qslot_value_reclaimer);
    Qg2_expression_cell_cached_value = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-CACHED-VALUE",AB_package);
    Qreclaim_g2_expression_cell_cached_value_value = 
	    STATIC_SYMBOL("RECLAIM-G2-EXPRESSION-CELL-CACHED-VALUE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_cached_value_value,
	    STATIC_FUNCTION(reclaim_g2_expression_cell_cached_value_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_expression_cell_cached_value,
	    SYMBOL_FUNCTION(Qreclaim_g2_expression_cell_cached_value_value),
	    Qslot_value_reclaimer);
    Qcopy_frame_for_g2_expression_cell = 
	    STATIC_SYMBOL("COPY-FRAME-FOR-G2-EXPRESSION-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_frame_for_g2_expression_cell,
	    STATIC_FUNCTION(copy_frame_for_g2_expression_cell,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcopy_frame_for_g2_expression_cell);
    set_get(Qg2_expression_cell,Qcopy_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcopy_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_expression_cell,temp);
    mutate_global_property(Qcopy_frame,temp_2,Qclasses_which_define);
    Qg2_expression_cell_chaining_links = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-CHAINING-LINKS",AB_package);
    Qput_g2_expression_cell_chaining_links = 
	    STATIC_SYMBOL("PUT-G2-EXPRESSION-CELL-CHAINING-LINKS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_g2_expression_cell_chaining_links,
	    STATIC_FUNCTION(put_g2_expression_cell_chaining_links,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qg2_expression_cell_chaining_links,
	    SYMBOL_FUNCTION(Qput_g2_expression_cell_chaining_links),
	    Qslot_putter);
    Qcleanup_for_g2_expression_cell = 
	    STATIC_SYMBOL("CLEANUP-FOR-G2-EXPRESSION-CELL",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_g2_expression_cell,
	    STATIC_FUNCTION(cleanup_for_g2_expression_cell,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_g2_expression_cell);
    set_get(Qg2_expression_cell,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_expression_cell,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qcell_class = STATIC_SYMBOL("CELL-CLASS",AB_package);
    Qg2_defstruct_structure_name_query_cell_stream_g2_struct = 
	    STATIC_SYMBOL("QUERY-CELL-STREAM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qquery_cell_stream = STATIC_SYMBOL("QUERY-CELL-STREAM",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_query_cell_stream_g2_struct,
	    Qquery_cell_stream,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qquery_cell_stream,
	    Qg2_defstruct_structure_name_query_cell_stream_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_query_cell_stream == UNBOUND)
	The_type_description_of_query_cell_stream = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83lvy1n83lvy8n8k1l8n0000001m1n8y83-5Dy1n83-9iy83-9ky83-9jy1m83My83-Aoykok0k0");
    temp = The_type_description_of_query_cell_stream;
    The_type_description_of_query_cell_stream = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_30));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_query_cell_stream_g2_struct,
	    The_type_description_of_query_cell_stream,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qquery_cell_stream,
	    The_type_description_of_query_cell_stream,
	    Qtype_description_of_type);
    Qoutstanding_query_cell_stream_count = 
	    STATIC_SYMBOL("OUTSTANDING-QUERY-CELL-STREAM-COUNT",AB_package);
    Qquery_cell_stream_structure_memory_usage = 
	    STATIC_SYMBOL("QUERY-CELL-STREAM-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_31 = STATIC_STRING("1q83lvy8s83-kwy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_query_cell_stream_count);
    push_optimized_constant(Qquery_cell_stream_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_query_cell_streams = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-QUERY-CELL-STREAMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_query_cell_streams,
	    Chain_of_available_query_cell_streams);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_query_cell_streams,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qquery_cell_stream_count = STATIC_SYMBOL("QUERY-CELL-STREAM-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qquery_cell_stream_count,
	    Query_cell_stream_count);
    record_system_variable(Qquery_cell_stream_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_query_cell_streams_vector == UNBOUND)
	Chain_of_available_query_cell_streams_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qquery_cell_stream_structure_memory_usage,
	    STATIC_FUNCTION(query_cell_stream_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_query_cell_stream_count,
	    STATIC_FUNCTION(outstanding_query_cell_stream_count,NIL,FALSE,
	    0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_query_cell_stream_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_query_cell_stream,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qquery_cell_stream,
	    reclaim_structure_for_query_cell_stream_1);
    Qquery_cell_updated = STATIC_SYMBOL("QUERY-CELL-UPDATED",AB_package);
    Qcell_index = STATIC_SYMBOL("CELL-INDEX",AB_package);
    Qold_value_stream_qm = STATIC_SYMBOL("OLD-VALUE-STREAM\?",AB_package);
    Qnew_stream = STATIC_SYMBOL("NEW-STREAM",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)5L,Qblock,Qcell_array,
	    Qcell_index,Qold_value_stream_qm,Qnew_stream);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qquery_cell_updated,list_constant_7,
	    Qgeneric_method_lambda_list);
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qseconds,Qinterval);
    Qg2_query_cell_cached_value = 
	    STATIC_SYMBOL("G2-QUERY-CELL-CACHED-VALUE",AB_package);
    Qreclaim_g2_query_cell_cached_value_value = 
	    STATIC_SYMBOL("RECLAIM-G2-QUERY-CELL-CACHED-VALUE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_query_cell_cached_value_value,
	    STATIC_FUNCTION(reclaim_g2_query_cell_cached_value_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qg2_query_cell_cached_value,
	    SYMBOL_FUNCTION(Qreclaim_g2_query_cell_cached_value_value),
	    Qslot_value_reclaimer);
    Qg2_query_cell_frame_serial_number_qm = 
	    STATIC_SYMBOL("G2-QUERY-CELL-FRAME-SERIAL-NUMBER\?",AB_package);
    Qreclaim_g2_query_cell_frame_serial_number_qm_value = 
	    STATIC_SYMBOL("RECLAIM-G2-QUERY-CELL-FRAME-SERIAL-NUMBER\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_g2_query_cell_frame_serial_number_qm_value,
	    STATIC_FUNCTION(reclaim_g2_query_cell_frame_serial_number_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qg2_query_cell_frame_serial_number_qm,
	    SYMBOL_FUNCTION(Qreclaim_g2_query_cell_frame_serial_number_qm_value),
	    Qslot_value_reclaimer);
    Qdesignation_cell_updated = STATIC_SYMBOL("DESIGNATION-CELL-UPDATED",
	    AB_package);
    Qold_value_qm = STATIC_SYMBOL("OLD-VALUE\?",AB_package);
    Qnew_value_qm = STATIC_SYMBOL("NEW-VALUE\?",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)5L,Qblock,Qcell_array,
	    Qcell_index,Qold_value_qm,Qnew_value_qm);
    mutate_global_property(Qdesignation_cell_updated,list_constant_8,
	    Qgeneric_method_lambda_list);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    Qg2_expression_cell_byte_code_body = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-BYTE-CODE-BODY",AB_package);
    Qg2_expression_cell_value_type = 
	    STATIC_SYMBOL("G2-EXPRESSION-CELL-VALUE-TYPE",AB_package);
    Qg2_lambda = STATIC_SYMBOL("G2-LAMBDA",AB_package);
    Qschedule_expression_cell_execution_for_true_value_update = 
	    STATIC_SYMBOL("SCHEDULE-EXPRESSION-CELL-EXECUTION-FOR-TRUE-VALUE-UPDATE",
	    AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qattempt_expression_cell_execution = 
	    STATIC_SYMBOL("ATTEMPT-EXPRESSION-CELL-EXECUTION",AB_package);
    SET_SYMBOL_FUNCTION(Qschedule_expression_cell_execution_for_true_value_update,
	    STATIC_FUNCTION(schedule_expression_cell_execution_for_true_value_update,
	    NIL,FALSE,6,6));
    Qsimulated_value = STATIC_SYMBOL("SIMULATED-VALUE",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    Qobsolete_datum = STATIC_SYMBOL("OBSOLETE-DATUM",AB_package);
    list_constant_1 = STATIC_CONS(Qobsolete_datum,Qnil);
    SET_SYMBOL_FUNCTION(Qattempt_expression_cell_execution,
	    STATIC_FUNCTION(attempt_expression_cell_execution,NIL,FALSE,3,3));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)25L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)28L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)39L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)45L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)48L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)49L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)50L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)51L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)52L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)53L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)62L,(SI_Long)54L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)63L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)19L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)20L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)28L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)39L,(SI_Long)57344L);
    string_constant = STATIC_STRING(".");
    array_constant_3 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)39L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING("~NV was the value for ");
    array_constant_5 = STATIC_ARRAY(list_constant_9,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)57344L);
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    Qnew_table = STATIC_SYMBOL("NEW-TABLE",AB_package);
    Qsubparts = STATIC_SYMBOL("SUBPARTS",AB_package);
    Qrow = STATIC_SYMBOL("ROW",AB_package);
    Qcell = STATIC_SYMBOL("CELL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcell,Cell);
    Qcell_contents = STATIC_SYMBOL("CELL-CONTENTS",AB_package);
    Qexpression_cell_index = STATIC_SYMBOL("EXPRESSION-CELL-INDEX",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    Qold_cache_qm = STATIC_SYMBOL("OLD-CACHE\?",AB_package);
    Qnew_cache_qm = STATIC_SYMBOL("NEW-CACHE\?",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)5L,Qblock,Qcell_array,Qindex,
	    Qold_cache_qm,Qnew_cache_qm);
    mutate_global_property(Qexpression_cell_updated,list_constant_10,
	    Qgeneric_method_lambda_list);
    Qgenerate_designation_of_cell = 
	    STATIC_SYMBOL("GENERATE-DESIGNATION-OF-CELL",AB_package);
    Qg2_cell_array_index = STATIC_SYMBOL("G2-CELL-ARRAY-INDEX",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qblock,Qg2_cell_array_index);
    mutate_global_property(Qgenerate_designation_of_cell,list_constant_11,
	    Qgeneric_method_lambda_list);
    Qplace_reference_of_cell = STATIC_SYMBOL("PLACE-REFERENCE-OF-CELL",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qblock,Qcell_index);
    mutate_global_property(Qplace_reference_of_cell,list_constant_12,
	    Qgeneric_method_lambda_list);
    Qrecompile_expression_at_component_particulars = 
	    STATIC_SYMBOL("RECOMPILE-EXPRESSION-AT-COMPONENT-PARTICULARS",
	    AB_package);
    Qcomponent_particulars = STATIC_SYMBOL("COMPONENT-PARTICULARS",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qblock,Qcomponent_particulars);
    mutate_global_property(Qrecompile_expression_at_component_particulars,
	    list_constant_13,Qgeneric_method_lambda_list);
}
