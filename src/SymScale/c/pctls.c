/* pctls.c
 * Input file:  proc-utils.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pctls.h"


static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object Qproc;               /* proc */

/* RECLAIM-PROC-ALIST-HEAD-AND-TEMPORARY-CONSTANTS */
Object reclaim_proc_alist_head_and_temporary_constants(alist,tail)
    Object alist, tail;
{
    Object trailer_qm, alist_cons, value_cons, temporary_constant_qm, temp;
    Object svref_arg_2, proc_cons;

    x_note_fn_call(160,0);
    trailer_qm = Nil;
    alist_cons = alist;
    value_cons = Nil;
    temporary_constant_qm = Nil;
  next_loop:
    if (EQ(alist_cons,tail))
	goto end_loop;
    value_cons = CAR(alist_cons);
    temporary_constant_qm = CDR(value_cons);
    if (SIMPLE_VECTOR_P(temporary_constant_qm) && 
	    EQ(ISVREF(temporary_constant_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	reclaim_temporary_constant_1(temporary_constant_qm);
    inline_note_reclaim_cons(value_cons,Qproc);
    if (ISVREF(Available_proc_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = value_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
    }
    else {
	temp = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
    }
    M_CDR(value_cons) = Nil;
    trailer_qm = alist_cons;
    alist_cons = CDR(alist_cons);
    goto next_loop;
  end_loop:
    if (trailer_qm) {
	if (alist &&  !((SI_Long)0L == inline_debugging_consing())) {
	    proc_cons = alist;
	  next_loop_1:
	    inline_note_reclaim_cons(proc_cons,Qproc);
	    if (EQ(proc_cons,trailer_qm))
		goto end_1;
	    else if ( !TRUEP(proc_cons))
		goto end_1;
	    else
		proc_cons = CDR(proc_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = alist;
	    temp = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_qm;
	}
	else {
	    temp = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_qm;
	}
	M_CDR(trailer_qm) = Nil;
    }
    return VALUES_1(Qnil);
}

/* RECLAIM-PROC-ALIST */
Object reclaim_proc_alist(alist)
    Object alist;
{
    Object trailer_qm, alist_cons, value_cons, temporary_constant_qm, temp;
    Object svref_arg_2, proc_cons;

    x_note_fn_call(160,1);
    trailer_qm = Nil;
    alist_cons = alist;
    value_cons = Nil;
    temporary_constant_qm = Nil;
  next_loop:
    if ( !TRUEP(alist_cons))
	goto end_loop;
    value_cons = CAR(alist_cons);
    temporary_constant_qm = CDR(value_cons);
    if (SIMPLE_VECTOR_P(temporary_constant_qm) && 
	    EQ(ISVREF(temporary_constant_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct))
	reclaim_temporary_constant_1(temporary_constant_qm);
    inline_note_reclaim_cons(value_cons,Qproc);
    if (ISVREF(Available_proc_conses_tail_vector,IFIX(Current_thread_index))) {
	temp = ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = value_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
    }
    else {
	temp = Available_proc_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
	temp = Available_proc_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = value_cons;
    }
    M_CDR(value_cons) = Nil;
    trailer_qm = alist_cons;
    alist_cons = CDR(alist_cons);
    goto next_loop;
  end_loop:
    if (trailer_qm) {
	if (alist &&  !((SI_Long)0L == inline_debugging_consing())) {
	    proc_cons = alist;
	  next_loop_1:
	    inline_note_reclaim_cons(proc_cons,Qproc);
	    if (EQ(proc_cons,trailer_qm))
		goto end_1;
	    else if ( !TRUEP(proc_cons))
		goto end_1;
	    else
		proc_cons = CDR(proc_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	if (ISVREF(Available_proc_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = alist;
	    temp = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_qm;
	}
	else {
	    temp = Available_proc_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = alist;
	    temp = Available_proc_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = trailer_qm;
	}
	M_CDR(trailer_qm) = Nil;
    }
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_alist, Qprocedure_alist);

Object Procedure_evaluator_prop = UNBOUND;

/* RECLAIM-CODE-BODY-ENTRY-POINTS-VALUE */
Object reclaim_code_body_entry_points_value(entry_point_array,gensymed_symbol)
    Object entry_point_array, gensymed_symbol;
{
    x_note_fn_call(160,2);
    if (entry_point_array)
	reclaim_managed_array(entry_point_array);
    return VALUES_1(Nil);
}

/* PROCEDURE-DEFINITION-OF-CODE-BODY-FUNCTION */
Object procedure_definition_of_code_body_function(code_body)
    Object code_body;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,3);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      temp = ISVREF(Code_body,(SI_Long)2L);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* CODE-BODY-BYTE-CODE-BODY-FUNCTION */
Object code_body_byte_code_body_function(code_body)
    Object code_body;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,4);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      temp = ISVREF(Code_body,(SI_Long)8L);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* CODE-BODY-ENTRY-POINTS-FUNCTION */
Object code_body_entry_points_function(code_body)
    Object code_body;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,5);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      temp = ISVREF(Code_body,(SI_Long)9L);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* PUT-P-CODE-ARRAY-WHERE-SLOT-IS-ABSENT */
Object put_p_code_array_where_slot_is_absent(code_body,p_code_array)
    Object code_body, p_code_array;
{
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,6);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      if (p_code_array) {
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(ISVREF(p_code_array,(SI_Long)1L));
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  reclaim_slot_value(FIXNUM_LE(ISVREF(p_code_array,(SI_Long)1L),
		  Maximum_in_place_array_size) ? ISVREF(p_code_array,
		  index_1 + IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(p_code_array,(index_1 >>  -  - 
		  (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L));
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
	  reclaim_managed_array(p_code_array);
      }
      result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_code_body_invocation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_code_body_invocations, Qchain_of_available_code_body_invocations);

DEFINE_VARIABLE_WITH_SYMBOL(Code_body_invocation_count, Qcode_body_invocation_count);

Object Chain_of_available_code_body_invocations_vector = UNBOUND;

/* CODE-BODY-INVOCATION-STRUCTURE-MEMORY-USAGE */
Object code_body_invocation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(160,7);
    temp = Code_body_invocation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)22L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CODE-BODY-INVOCATION-COUNT */
Object outstanding_code_body_invocation_count()
{
    Object def_structure_code_body_invocation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,8);
    gensymed_symbol = IFIX(Code_body_invocation_count);
    def_structure_code_body_invocation_variable = 
	    Chain_of_available_code_body_invocations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_code_body_invocation_variable))
	goto end_loop;
    def_structure_code_body_invocation_variable = 
	    ISVREF(def_structure_code_body_invocation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CODE-BODY-INVOCATION-1 */
Object reclaim_code_body_invocation_1(code_body_invocation)
    Object code_body_invocation;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(160,9);
    inline_note_reclaim_cons(code_body_invocation,Nil);
    structure_being_reclaimed = code_body_invocation;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(code_body_invocation,(SI_Long)7L);
      if (CAS_SVREF(code_body_invocation,(SI_Long)7L,gensymed_symbol,Nil)) {
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
      SVREF(code_body_invocation,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(code_body_invocation,(SI_Long)9L));
      SVREF(code_body_invocation,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_code_body_invocations_vector,
	    IFIX(Current_thread_index));
    SVREF(code_body_invocation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_code_body_invocations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = code_body_invocation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CODE-BODY-INVOCATION */
Object reclaim_structure_for_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    x_note_fn_call(160,10);
    return reclaim_code_body_invocation_1(code_body_invocation);
}

static Object Qg2_defstruct_structure_name_code_body_invocation_g2_struct;  /* g2-defstruct-structure-name::code-body-invocation-g2-struct */

/* MAKE-PERMANENT-CODE-BODY-INVOCATION-STRUCTURE-INTERNAL */
Object make_permanent_code_body_invocation_structure_internal()
{
    Object def_structure_code_body_invocation_variable;
    Object defstruct_g2_code_body_invocation_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(160,11);
    def_structure_code_body_invocation_variable = Nil;
    atomic_incff_symval(Qcode_body_invocation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_code_body_invocation_variable = Nil;
	gensymed_symbol_1 = (SI_Long)22L;
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
	defstruct_g2_code_body_invocation_variable = the_array;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_code_body_invocation_g2_struct;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)5L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)6L)) 
		= Nil;
	SVREF(defstruct_g2_code_body_invocation_variable,FIX((SI_Long)7L)) 
		= Nil;
	def_structure_code_body_invocation_variable = 
		defstruct_g2_code_body_invocation_variable;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)6L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_code_body_invocations_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_code_body_invocations_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_code_body_invocation_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_code_body_invocation_variable);
}

/* MAKE-CODE-BODY-INVOCATION-1 */
Object make_code_body_invocation_1()
{
    Object def_structure_code_body_invocation_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(160,12);
    def_structure_code_body_invocation_variable = 
	    ISVREF(Chain_of_available_code_body_invocations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_code_body_invocation_variable) {
	svref_arg_1 = Chain_of_available_code_body_invocations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_code_body_invocation_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_code_body_invocation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct;
    }
    else
	def_structure_code_body_invocation_variable = 
		make_permanent_code_body_invocation_structure_internal();
    inline_note_allocate_cons(def_structure_code_body_invocation_variable,Nil);
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_code_body_invocation_variable,FIX((SI_Long)21L)) = Nil;
    return VALUES_1(def_structure_code_body_invocation_variable);
}

/* PROCEDURE-INVOCATION-OF-CODE-BODY-FUNCTION */
Object procedure_invocation_of_code_body_function(code_body)
    Object code_body;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,13);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      temp = ISVREF(Code_body,(SI_Long)11L);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

/* CODE-BODY-OF-INVOCATION-FUNCTION */
Object code_body_of_invocation_function(code_body)
    Object code_body;
{
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,14);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      temp = ISVREF(Code_body,(SI_Long)8L);
      result = VALUES_1(temp);
    POP_SPECIAL();
    return result;
}

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

/* CODE-BODY-INVOCATION? */
Object code_body_invocation_qm(item)
    Object item;
{
    Object type_name, temp;

    x_note_fn_call(160,15);
    if (SIMPLE_VECTOR_P(item)) {
	type_name = ISVREF(item,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct) 
		? T : Nil;
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) 
		    ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* NEED-TO-WAIT-AFTER-ATTEMPTING-RULE-SCHEDULING */
Object need_to_wait_after_attempting_rule_scheduling(code_body_invocation)
    Object code_body_invocation;
{
    Object temp;

    x_note_fn_call(160,16);
    temp = ISVREF(code_body_invocation,(SI_Long)17L);
    return VALUES_1(temp);
}

/* REMOVE-COMPLETION-NOTIFICATION-COLLECTION-IF-EMPTY */
Object remove_completion_notification_collection_if_empty(code_body_invocation)
    Object code_body_invocation;
{
    Object back_pointer, svref_arg_1;

    x_note_fn_call(160,17);
    back_pointer = 
	    need_to_wait_after_attempting_rule_scheduling(code_body_invocation);
    if ( !TRUEP(CAR(back_pointer))) {
	reclaim_eval_list_1(back_pointer);
	svref_arg_1 = Current_computation_instance;
	SVREF(svref_arg_1,FIX((SI_Long)17L)) = Nil;
    }
    return VALUES_1(Nil);
}

/* SET-UP-COMPLETION-NOTIFICATION-COLLECTION */
Object set_up_completion_notification_collection(code_body_invocation)
    Object code_body_invocation;
{
    Object svref_new_value;

    x_note_fn_call(160,18);
    svref_new_value = eval_list_2(Nil,code_body_invocation);
    return VALUES_1(SVREF(code_body_invocation,FIX((SI_Long)17L)) = 
	    svref_new_value);
}

Object The_type_description_of_remote_procedure_call = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_remote_procedure_calls, Qchain_of_available_remote_procedure_calls);

DEFINE_VARIABLE_WITH_SYMBOL(Remote_procedure_call_count, Qremote_procedure_call_count);

Object Chain_of_available_remote_procedure_calls_vector = UNBOUND;

/* REMOTE-PROCEDURE-CALL-STRUCTURE-MEMORY-USAGE */
Object remote_procedure_call_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(160,19);
    temp = Remote_procedure_call_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)27L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-REMOTE-PROCEDURE-CALL-COUNT */
Object outstanding_remote_procedure_call_count()
{
    Object def_structure_remote_procedure_call_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,20);
    gensymed_symbol = IFIX(Remote_procedure_call_count);
    def_structure_remote_procedure_call_variable = 
	    Chain_of_available_remote_procedure_calls;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_remote_procedure_call_variable))
	goto end_loop;
    def_structure_remote_procedure_call_variable = 
	    ISVREF(def_structure_remote_procedure_call_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-REMOTE-PROCEDURE-CALL-1 */
Object reclaim_remote_procedure_call_1(remote_procedure_call)
    Object remote_procedure_call;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(160,21);
    inline_note_reclaim_cons(remote_procedure_call,Nil);
    structure_being_reclaimed = remote_procedure_call;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(remote_procedure_call,(SI_Long)7L);
      if (CAS_SVREF(remote_procedure_call,(SI_Long)7L,gensymed_symbol,Nil)) {
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
      SVREF(remote_procedure_call,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(remote_procedure_call,(SI_Long)9L));
      SVREF(remote_procedure_call,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_remote_procedure_calls_vector,
	    IFIX(Current_thread_index));
    SVREF(remote_procedure_call,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_remote_procedure_calls_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = remote_procedure_call;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-REMOTE-PROCEDURE-CALL */
Object reclaim_structure_for_remote_procedure_call(remote_procedure_call)
    Object remote_procedure_call;
{
    x_note_fn_call(160,22);
    return reclaim_remote_procedure_call_1(remote_procedure_call);
}

static Object Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;  /* g2-defstruct-structure-name::remote-procedure-call-g2-struct */

/* MAKE-PERMANENT-REMOTE-PROCEDURE-CALL-STRUCTURE-INTERNAL */
Object make_permanent_remote_procedure_call_structure_internal()
{
    Object def_structure_remote_procedure_call_variable;
    Object defstruct_g2_remote_procedure_call_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(160,23);
    def_structure_remote_procedure_call_variable = Nil;
    atomic_incff_symval(Qremote_procedure_call_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_remote_procedure_call_variable = Nil;
	gensymed_symbol_1 = (SI_Long)27L;
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
	defstruct_g2_remote_procedure_call_variable = the_array;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_remote_procedure_call_variable,
		FIX((SI_Long)21L)) = Nil;
	def_structure_remote_procedure_call_variable = 
		defstruct_g2_remote_procedure_call_variable;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)17L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_remote_procedure_calls_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_remote_procedure_calls_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_remote_procedure_call_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_remote_procedure_call_variable);
}

/* MAKE-REMOTE-PROCEDURE-CALL-INTERNAL-1 */
Object make_remote_procedure_call_internal_1(remote_procedure_identifier_of_call,
	    remote_procedure_declaration_of_call,
	    remote_procedure_call_icp_socket,
	    remote_procedure_call_icp_interface)
    Object remote_procedure_identifier_of_call;
    Object remote_procedure_declaration_of_call;
    Object remote_procedure_call_icp_socket;
    Object remote_procedure_call_icp_interface;
{
    Object def_structure_remote_procedure_call_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(160,24);
    def_structure_remote_procedure_call_variable = 
	    ISVREF(Chain_of_available_remote_procedure_calls_vector,
	    IFIX(Current_thread_index));
    if (def_structure_remote_procedure_call_variable) {
	svref_arg_1 = Chain_of_available_remote_procedure_calls_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_remote_procedure_call_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_remote_procedure_call_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct;
    }
    else
	def_structure_remote_procedure_call_variable = 
		make_permanent_remote_procedure_call_structure_internal();
    inline_note_allocate_cons(def_structure_remote_procedure_call_variable,
	    Nil);
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)22L)) 
	    = remote_procedure_identifier_of_call;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)23L)) 
	    = remote_procedure_declaration_of_call;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)24L)) 
	    = remote_procedure_call_icp_socket;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)25L)) 
	    = remote_procedure_call_icp_interface;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)18L)) 
	    = Nil;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)19L)) 
	    = Nil;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)20L)) 
	    = Nil;
    SVREF(def_structure_remote_procedure_call_variable,FIX((SI_Long)21L)) 
	    = Nil;
    ISVREF(def_structure_remote_procedure_call_variable,(SI_Long)26L) = 
	    FIX((SI_Long)-1L);
    return VALUES_1(def_structure_remote_procedure_call_variable);
}

/* MAKE-INCOMING-REMOTE-PROCEDURE-CALL */
Object make_incoming_remote_procedure_call(remote_procedure_identifier_of_call,
	    remote_procedure_call_icp_socket)
    Object remote_procedure_identifier_of_call;
    Object remote_procedure_call_icp_socket;
{
    Object rpc;

    x_note_fn_call(160,25);
    rpc = 
	    make_remote_procedure_call_internal_1(remote_procedure_identifier_of_call,
	    Nil,remote_procedure_call_icp_socket,Nil);
    SVREF(rpc,FIX((SI_Long)8L)) = Nil;
    reclaim_frame_serial_number(ISVREF(rpc,(SI_Long)9L));
    SVREF(rpc,FIX((SI_Long)9L)) = Nil;
    SVREF(rpc,FIX((SI_Long)10L)) = Nil;
    SVREF(rpc,FIX((SI_Long)11L)) = Nil;
    SVREF(rpc,FIX((SI_Long)12L)) = Nil;
    SVREF(rpc,FIX((SI_Long)13L)) = Nil;
    SVREF(rpc,FIX((SI_Long)14L)) = Nil;
    SVREF(rpc,FIX((SI_Long)15L)) = Nil;
    SVREF(rpc,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(rpc);
}

/* RECLAIM-INCOMING-REMOTE-PROCEDURE-CALL */
Object reclaim_incoming_remote_procedure_call(remote_procedure_call)
    Object remote_procedure_call;
{
    Object temp;

    x_note_fn_call(160,26);
    temp = SIMPLE_VECTOR_P(remote_procedure_call) && 
	    EQ(ISVREF(remote_procedure_call,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct) ?
	     reclaim_remote_procedure_call_1(remote_procedure_call) : Nil;
    return VALUES_1(temp);
}

/* MAKE-OUTGOING-REMOTE-PROCEDURE-CALL */
Object make_outgoing_remote_procedure_call(remote_procedure_identifier_of_call,
	    remote_procedure_declaration_of_call,
	    remote_procedure_call_icp_socket,
	    remote_procedure_call_icp_interface)
    Object remote_procedure_identifier_of_call;
    Object remote_procedure_declaration_of_call;
    Object remote_procedure_call_icp_socket;
    Object remote_procedure_call_icp_interface;
{
    Object rpc;

    x_note_fn_call(160,27);
    rpc = 
	    make_remote_procedure_call_internal_1(remote_procedure_identifier_of_call,
	    remote_procedure_declaration_of_call,
	    remote_procedure_call_icp_socket,
	    remote_procedure_call_icp_interface);
    SVREF(rpc,FIX((SI_Long)8L)) = Nil;
    SVREF(rpc,FIX((SI_Long)14L)) = Nil;
    SVREF(rpc,FIX((SI_Long)15L)) = Nil;
    SVREF(rpc,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(rpc);
}

/* RECLAIM-OUTGOING-REMOTE-PROCEDURE-CALL */
Object reclaim_outgoing_remote_procedure_call(remote_procedure_call)
    Object remote_procedure_call;
{
    Object temp;

    x_note_fn_call(160,28);
    temp = reclaim_remote_procedure_call_1(remote_procedure_call);
    return VALUES_1(temp);
}

Object The_type_description_of_system_rpc = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_system_rpcs, Qchain_of_available_system_rpcs);

DEFINE_VARIABLE_WITH_SYMBOL(System_rpc_count, Qsystem_rpc_count);

Object Chain_of_available_system_rpcs_vector = UNBOUND;

/* SYSTEM-RPC-STRUCTURE-MEMORY-USAGE */
Object system_rpc_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(160,29);
    temp = System_rpc_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SYSTEM-RPC-COUNT */
Object outstanding_system_rpc_count()
{
    Object def_structure_system_rpc_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,30);
    gensymed_symbol = IFIX(System_rpc_count);
    def_structure_system_rpc_variable = Chain_of_available_system_rpcs;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_system_rpc_variable))
	goto end_loop;
    def_structure_system_rpc_variable = 
	    ISVREF(def_structure_system_rpc_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SYSTEM-RPC-1 */
Object reclaim_system_rpc_1(system_rpc)
    Object system_rpc;
{
    Object temp, svref_arg_2;

    x_note_fn_call(160,31);
    inline_note_reclaim_cons(system_rpc,Nil);
    temp = ISVREF(Chain_of_available_system_rpcs_vector,
	    IFIX(Current_thread_index));
    SVREF(system_rpc,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_system_rpcs_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = system_rpc;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SYSTEM-RPC */
Object reclaim_structure_for_system_rpc(system_rpc)
    Object system_rpc;
{
    x_note_fn_call(160,32);
    return reclaim_system_rpc_1(system_rpc);
}

static Object Qg2_defstruct_structure_name_system_rpc_g2_struct;  /* g2-defstruct-structure-name::system-rpc-g2-struct */

/* MAKE-PERMANENT-SYSTEM-RPC-STRUCTURE-INTERNAL */
Object make_permanent_system_rpc_structure_internal()
{
    Object def_structure_system_rpc_variable, defstruct_g2_system_rpc_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(160,33);
    def_structure_system_rpc_variable = Nil;
    atomic_incff_symval(Qsystem_rpc_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_system_rpc_variable = Nil;
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
	defstruct_g2_system_rpc_variable = the_array;
	SVREF(defstruct_g2_system_rpc_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_system_rpc_g2_struct;
	def_structure_system_rpc_variable = defstruct_g2_system_rpc_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_system_rpc_variable);
}

/* MAKE-SYSTEM-RPC-1 */
Object make_system_rpc_1(system_rpc_lisp_function,
	    system_rpc_argument_types,system_rpc_return_types)
    Object system_rpc_lisp_function, system_rpc_argument_types;
    Object system_rpc_return_types;
{
    Object def_structure_system_rpc_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(160,34);
    def_structure_system_rpc_variable = 
	    ISVREF(Chain_of_available_system_rpcs_vector,
	    IFIX(Current_thread_index));
    if (def_structure_system_rpc_variable) {
	svref_arg_1 = Chain_of_available_system_rpcs_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_system_rpc_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_system_rpc_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_system_rpc_g2_struct;
    }
    else
	def_structure_system_rpc_variable = 
		make_permanent_system_rpc_structure_internal();
    inline_note_allocate_cons(def_structure_system_rpc_variable,Nil);
    SVREF(def_structure_system_rpc_variable,FIX((SI_Long)1L)) = 
	    system_rpc_lisp_function;
    SVREF(def_structure_system_rpc_variable,FIX((SI_Long)2L)) = 
	    system_rpc_argument_types;
    SVREF(def_structure_system_rpc_variable,FIX((SI_Long)3L)) = 
	    system_rpc_return_types;
    return VALUES_1(def_structure_system_rpc_variable);
}

/* PROCEDURE-INVOCATION-HASH */
Object procedure_invocation_hash(invocation)
    Object invocation;
{
    Object temp;

    x_note_fn_call(160,35);
    temp = FIX(SXHASH_SYMBOL_1(invocation) & IFIX(Most_positive_fixnum));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_procedure_invocations_hash_vector_43_vectors, Qavailable_procedure_invocations_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_procedure_invocations_hash_vector_43_vectors, Qcount_of_procedure_invocations_hash_vector_43_vectors);

Object Available_procedure_invocations_hash_vector_43_vectors_vector = UNBOUND;

/* PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object procedure_invocations_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(160,36);
    temp = Count_of_procedure_invocations_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTORS */
Object out_procedure_invocations_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(160,37);
    temp = 
	    FIXNUM_MINUS(Count_of_procedure_invocations_hash_vector_43_vectors,
	    length(Available_procedure_invocations_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_procedure_invocations_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(160,38);
    atomic_incff_symval(Qcount_of_procedure_invocations_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-PROCEDURE-INVOCATIONS-HASH-VECTOR */
Object make_procedure_invocations_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(160,39);
    if (ISVREF(Available_procedure_invocations_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_procedure_invocations_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_procedure_invocations_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_procedure_invocations_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_procedure_invocations_hash_vector_43_vectors_vector,
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
		make_permanent_procedure_invocations_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-PROCEDURE-INVOCATIONS-HASH-VECTOR */
Object reclaim_procedure_invocations_hash_vector(procedure_invocations_hash_vector_43_vector)
    Object procedure_invocations_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(160,40);
    svref_arg_1 = 
	    Available_procedure_invocations_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = procedure_invocations_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_procedure_invocations_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-PROCEDURE-INVOCATIONS-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_procedure_invocations_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(160,41);
    node = make_skip_list_element_1(hash,Qsentinel_node,tail ? Qhead : 
	    Qtail,FIX((SI_Long)20L));
    next = allocate_managed_simple_vector_for_skip_list(FIX((SI_Long)21L));
    i = (SI_Long)0L;
  next_loop:
    if (i > (SI_Long)20L)
	goto end_loop;
    svref_new_value = MAKE_ATOMIC_REF(tail,(SI_Long)0L);
    ISVREF(next,i) = svref_new_value;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    SVREF(node,FIX((SI_Long)0L)) = next;
    return VALUES_1(node);
}

/* RECLAIM-PROCEDURE-INVOCATIONS-TREE-FOR-HASH-NODES */
Object reclaim_procedure_invocations_tree_for_hash_nodes(procedure_invocations_tree_for_hash_skip_list,
	    tail)
    Object procedure_invocations_tree_for_hash_skip_list, tail;
{
    Object next_element, key, entry;

    x_note_fn_call(160,42);
    next_element = Nil;
    key = Nil;
    entry = Nil;
  next_loop:
    if (EQ(procedure_invocations_tree_for_hash_skip_list,tail))
	goto end_loop;
    next_element = 
	    ATOMIC_REF_OBJECT(ISVREF(ISVREF(procedure_invocations_tree_for_hash_skip_list,
	    (SI_Long)0L),(SI_Long)0L));
    key = ISVREF(procedure_invocations_tree_for_hash_skip_list,(SI_Long)2L);
    entry = ISVREF(procedure_invocations_tree_for_hash_skip_list,(SI_Long)3L);
    reclaim_skip_list_element(procedure_invocations_tree_for_hash_skip_list);
    procedure_invocations_tree_for_hash_skip_list = next_element;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-PROCEDURE-INVOCATIONS-TREE */
Object clear_procedure_invocations_tree(procedure_invocations_tree_for_hash_skip_list)
    Object procedure_invocations_tree_for_hash_skip_list;
{
    Object head, tail, element_qm;

    x_note_fn_call(160,43);
    head = M_CAR(M_CDR(procedure_invocations_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(procedure_invocations_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_procedure_invocations_tree_for_hash_nodes(element_qm,tail);
    return VALUES_1(procedure_invocations_tree_for_hash_skip_list);
}

static Object Qprocedure_invocations_tree_for_hash;  /* procedure-invocations-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-PROCEDURE-INVOCATIONS */
Object make_procedure_invocations()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(160,44);
    new_vector = make_procedure_invocations_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_procedure_invocations_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_procedure_invocations_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qprocedure_invocations_tree_for_hash;
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

/* FLATTEN-PROCEDURE-INVOCATIONS */
Object flatten_procedure_invocations(procedure_invocations_hash_table)
    Object procedure_invocations_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(160,45);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(procedure_invocations_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-PROCEDURE-INVOCATIONS-TABLE */
Object clear_procedure_invocations_table(procedure_invocations_hash_table)
    Object procedure_invocations_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(160,46);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_procedure_invocations_tree(ISVREF(procedure_invocations_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-PROCEDURE-INVOCATIONS */
Object reclaim_procedure_invocations(procedure_invocations_hash_table)
    Object procedure_invocations_hash_table;
{
    Object procedure_invocations_tree_for_hash_skip_list, head, tail;
    Object element_qm, last_1, next_qm, temp, svref_arg_2, temp_1;
    SI_Long index_1;

    x_note_fn_call(160,47);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    procedure_invocations_tree_for_hash_skip_list = 
	    ISVREF(procedure_invocations_hash_table,index_1);
    head = M_CAR(M_CDR(procedure_invocations_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(procedure_invocations_tree_for_hash_skip_list));
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    if ( !EQ(element_qm,tail))
	reclaim_procedure_invocations_tree_for_hash_nodes(element_qm,tail);
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(procedure_invocations_tree_for_hash_skip_list) = Nil;
    M_CADR(procedure_invocations_tree_for_hash_skip_list) = Nil;
    M_CAR(procedure_invocations_tree_for_hash_skip_list) = Nil;
    if (procedure_invocations_tree_for_hash_skip_list) {
	last_1 = procedure_invocations_tree_for_hash_skip_list;
	next_qm = Nil;
      next_loop_1:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_1;
	inline_note_reclaim_cons(last_1,Qlookup);
	last_1 = next_qm;
	goto next_loop_1;
      end_loop_1:
	inline_note_reclaim_cons(last_1,Qlookup);
	if (ISVREF(Available_lookup_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_lookup_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = procedure_invocations_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = 
		    procedure_invocations_tree_for_hash_skip_list;
	    temp = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(procedure_invocations_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp_1 = 
	    reclaim_procedure_invocations_hash_vector(procedure_invocations_hash_table);
    return VALUES_1(temp_1);
}

/* PROCEDURE-DEFINITION-FUNCTION */
Object procedure_definition_function(procedure)
    Object procedure;
{
    x_note_fn_call(160,48);
    return VALUES_1(ISVREF(procedure,(SI_Long)27L));
}

static Object Qhas_empty_code_body_qm;  /* has-empty-code-body? */

/* HAS-EMPTY-CODE-BODY-P */
Object has_empty_code_body_p(procedure)
    Object procedure;
{
    Object temp;

    x_note_fn_call(160,49);
    temp = get_lookup_slot_value_given_default(procedure,
	    Qhas_empty_code_body_qm,Nil);
    return VALUES_1(temp);
}

/* PUSH-ONE-PROCEDURE-INVOCATION */
Object push_one_procedure_invocation(invocation,procedure)
    Object invocation, procedure;
{
    Object old_tree_qm, new_tree, temp;
    SI_Long gensymed_symbol, temp_1;

    x_note_fn_call(160,50);
    old_tree_qm = ISVREF(procedure,(SI_Long)26L);
    if ( !TRUEP(old_tree_qm)) {
	new_tree = make_procedure_invocations();
	if ( !TRUEP(CAS_SVREF(procedure,(SI_Long)26L,old_tree_qm,new_tree)))
	    reclaim_procedure_invocations(new_tree);
    }
    gensymed_symbol = IFIX(procedure_invocation_hash(invocation));
    temp = ISVREF(procedure,(SI_Long)26L);
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = set_skip_list_entry(SVREF(temp,FIX(temp_1)),FIX((SI_Long)20L),
	    Qeq,Nil,T,invocation,FIX(gensymed_symbol),invocation);
    return VALUES_1(temp);
}

/* DELETE-ONE-PROCEDURE-INVOCATION */
Object delete_one_procedure_invocation(invocation,procedure)
    Object invocation, procedure;
{
    Object invocations;
    SI_Long gensymed_symbol, temp;

    x_note_fn_call(160,51);
    invocations = ISVREF(procedure,(SI_Long)26L);
    gensymed_symbol = IFIX(procedure_invocation_hash(invocation));
    temp = gensymed_symbol % (SI_Long)43L;
    delete_skip_list_entry(SYMBOL_FUNCTION(Qeq),invocation,
	    SVREF(invocations,FIX(temp)),FIX((SI_Long)20L),
	    FIX(gensymed_symbol));
    return VALUES_1(Nil);
}

/* INITIAL-INLINED-CALLS */
Object initial_inlined_calls(procedure)
    Object procedure;
{
    x_note_fn_call(160,52);
    return VALUES_1(Nil);
}

/* GET-INLINED-CALLS */
Object get_inlined_calls(proc)
    Object proc;
{
    Object free_references_qm, ref, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, denotations_qm, d, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4, temp, name_list_qm;

    x_note_fn_call(160,53);
    free_references_qm = free_references_from_procedure(proc);
    ref = Nil;
    ab_loop_list_ = free_references_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ref = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    denotations_qm = 
	    extract_inlined_procedures_from_free_reference_vector(ref);
    d = Nil;
    ab_loop_list__1 = denotations_qm;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    d = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (CONSP(d)) {
	temp = convert_class_qualified_list_to_keyword_symbol(d);
	reclaim_gensym_list_1(d);
    }
    else
	temp = d;
    ab_loopvar__4 = eval_cons_1(temp,Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    goto next_loop_1;
  end_loop_1:
    reclaim_gensym_list_1(denotations_qm);
    goto end_1;
    ab_loopvar__2 = Qnil;
  end_1:;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop;
  end_loop:
    name_list_qm = ab_loopvar_;
    goto end_2;
    name_list_qm = Qnil;
  end_2:;
    reclaim_gensym_list_1(free_references_qm);
    temp = allocate_evaluation_sequence(name_list_qm);
    return VALUES_1(temp);
}

/* PROCEDURE? */
Object procedure_qm(block)
    Object block;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(160,54);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
    return VALUES_1(temp);
}

/* RECLAIM-PROCEDURE-INVOCATIONS-VALUE */
Object reclaim_procedure_invocations_value(invocations,procedure)
    Object invocations, procedure;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,55);
  next_loop:
    gensymed_symbol = ISVREF(procedure,(SI_Long)26L);
    gensymed_symbol_1 = Nil;
    if (CAS_SVREF(procedure,(SI_Long)26L,gensymed_symbol,gensymed_symbol_1))
	goto end_1;
    goto next_loop;
  end_loop:
  end_1:
    reclaim_procedure_invocations(invocations);
    return VALUES_1(Nil);
}

/* ARGUMENT-LIST-DESCRIPTION-FUNCTION */
Object argument_list_description_function(procedure)
    Object procedure;
{
    x_note_fn_call(160,56);
    return VALUES_1(ISVREF(procedure,(SI_Long)24L));
}

/* RETURNED-VALUES-DESCRIPTION-FUNCTION */
Object returned_values_description_function(procedure)
    Object procedure;
{
    x_note_fn_call(160,57);
    return VALUES_1(ISVREF(procedure,(SI_Long)25L));
}

static Object Qn_compiles_this_session;  /* n-compiles-this-session */

/* N-COMPILES-THIS-SESSION-FUNCTION */
Object n_compiles_this_session_function(procedure)
    Object procedure;
{
    Object temp;

    x_note_fn_call(160,58);
    temp = get_lookup_slot_value_given_default(procedure,
	    Qn_compiles_this_session,FIX((SI_Long)0L));
    return VALUES_1(temp);
}

static Object Qprocedure_flags;    /* procedure-flags */

/* CLEAR-PROCEDURE-COMPILATION-FRAME-FLAGS */
Object clear_procedure_compilation_frame_flags(procedure)
    Object procedure;
{
    SI_Long svref_new_value;

    x_note_fn_call(160,59);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_flags);
    svref_new_value = IFIX(ISVREF(procedure,(SI_Long)29L)) &  ~(SI_Long)1L;
    ISVREF(procedure,(SI_Long)29L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_flags);
    svref_new_value = IFIX(ISVREF(procedure,(SI_Long)29L)) &  ~(SI_Long)2L;
    ISVREF(procedure,(SI_Long)29L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_flags);
    svref_new_value = IFIX(ISVREF(procedure,(SI_Long)29L)) &  ~(SI_Long)4L;
    ISVREF(procedure,(SI_Long)29L) = FIX(svref_new_value);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_flags);
    svref_new_value = IFIX(ISVREF(procedure,(SI_Long)29L)) &  ~(SI_Long)8L;
    return VALUES_1(ISVREF(procedure,(SI_Long)29L) = FIX(svref_new_value));
}

static Object Kgeneral_description;  /* :general-description */

/* VAR-TYPE-FROM-INDEX-FUNCTION */
Object var_type_from_index_function(description_vector,index_1)
    Object description_vector, index_1;
{
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(160,60);
    gensymed_symbol = IFIX(index_1) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(description_vector,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(description_vector,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description))
	gensymed_symbol_1 = 
		getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
    return VALUES_1(gensymed_symbol_1);
}

/* COLLECT-TYPES-INTO-LIST-USING-PHRASE-CONSES */
Object collect_types_into_list_using_phrase_conses(description_vector)
    Object description_vector;
{
    Object value, parsed_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,61);
    if (description_vector) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(ISVREF(description_vector,(SI_Long)1L));
	value = Nil;
	parsed_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value = FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(description_vector,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(description_vector,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	parsed_value = CONSP(value) && EQ(CAR(value),Kgeneral_description) 
		? getfq_function_no_default(CDR(value),Ktype) : value;
	ab_loopvar__2 = phrase_cons(parsed_value,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-DESCRIPTION-INTO-LIST-USING-PHRASE-CONSES */
Object collect_description_into_list_using_phrase_conses(description_vector)
    Object description_vector;
{
    Object description_list, index_1, name, description, copied_description;
    Object temp;

    x_note_fn_call(160,62);
    if (description_vector) {
	description_list = Nil;
	index_1 = FIX((SI_Long)0L);
	name = Nil;
	description = Nil;
	copied_description = Nil;
      next_loop:
	temp = ISVREF(description_vector,(SI_Long)1L);
	if ( !NUM_LT(index_1,temp))
	    goto end_loop;
	name = FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(description_vector,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(description_vector,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	index_1 = FIXNUM_ADD1(index_1);
	description = FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(description_vector,
		IFIX(FIXNUM_ADD(index_1,Managed_array_index_offset))) : 
		ISVREF(ISVREF(description_vector,(IFIX(index_1) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(index_1) & (SI_Long)1023L);
	index_1 = FIXNUM_ADD1(index_1);
	if (CONSP(description) && EQ(CAR(description),Kgeneral_description)) {
	    copied_description = 
		    copy_tree_using_phrase_conses(CDR(description));
	    copied_description = phrase_cons(name,copied_description);
	}
	else if (CONSP(description)) {
	    copied_description = copy_tree_using_phrase_conses(description);
	    copied_description = phrase_cons(name,copied_description);
	}
	else
	    copied_description = phrase_list_2(name,description);
	if (description_list)
	    nconc2(description_list,phrase_cons(copied_description,Nil));
	else
	    description_list = phrase_cons(copied_description,Nil);
	goto next_loop;
      end_loop:;
	return VALUES_1(description_list);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-TYPES-INTO-LIST-USING-GENSYM-CONSES */
Object collect_types_into_list_using_gensym_conses(description_vector)
    Object description_vector;
{
    Object value, parsed_value, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,63);
    if (description_vector) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(ISVREF(description_vector,(SI_Long)1L));
	value = Nil;
	parsed_value = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	value = FIXNUM_LE(ISVREF(description_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(description_vector,
		index_1 + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(description_vector,(index_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	parsed_value = CONSP(value) && EQ(CAR(value),Kgeneral_description) 
		? getfq_function_no_default(CDR(value),Ktype) : value;
	ab_loopvar__2 = gensym_cons_1(parsed_value,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	index_1 = index_1 + (SI_Long)2L;
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* VAR-COUNT */
Object var_count(description_vector)
    Object description_vector;
{
    Object temp_1;
    SI_Long temp;

    x_note_fn_call(160,64);
    if (description_vector) {
	temp = IFIX(ISVREF(description_vector,(SI_Long)1L)) / (SI_Long)2L;
	temp_1 = FIX(temp);
    }
    else
	temp_1 = FIX((SI_Long)0L);
    return VALUES_1(temp_1);
}

/* CODE-BODIES-FUNCTION */
Object code_bodies_function(procedure)
    Object procedure;
{
    Object temp;

    x_note_fn_call(160,65);
    temp = ISVREF(procedure,(SI_Long)28L);
    return VALUES_1(temp);
}

Object Procedure_code_bodies_slot_name = UNBOUND;

static Object Qprocedure_code_bodies_3_dot_0_beta;  /* procedure-code-bodies-3.0-beta */

/* PUT-PROCEDURE-CODE-BODIES-3.0-BETA */
Object put_procedure_code_bodies_3_dot_0_beta(procedure,new_code_bodies,
	    initializing_qm)
    Object procedure, new_code_bodies, initializing_qm;
{
    x_note_fn_call(160,66);
    if (initializing_qm &&  !TRUEP(compilations_up_to_date_p(procedure)) 
	    && Loading_kb_p) {
	reclaim_slot_value(new_code_bodies);
	new_code_bodies = Nil;
	note_frame_with_compilation_removed(procedure);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_code_bodies_3_dot_0_beta);
    SVREF(procedure,FIX((SI_Long)28L)) = new_code_bodies;
    return VALUES_1(new_code_bodies);
}

/* PUT-CODE-BODIES-3.0-ALPHA-WHERE-SLOT-IS-ABSENT */
Object put_code_bodies_3_dot_0_alpha_where_slot_is_absent(procedure,
	    old_code_bodies)
    Object procedure, old_code_bodies;
{
    x_note_fn_call(160,67);
    reclaim_slot_value(old_code_bodies);
    return VALUES_1(Nil);
}

/* PUT-PROCEDURE-FREE-REFERENCES-WHERE-SLOT-IS-ABSENT */
Object put_procedure_free_references_where_slot_is_absent(procedure,
	    old_references)
    Object procedure, old_references;
{
    x_note_fn_call(160,68);
    reclaim_slot_value(old_references);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(List_of_previously_optimized_procedures, Qlist_of_previously_optimized_procedures);

/* PUT-OPTIMIZE-PROCEDURE-CODE?-WHERE-SLOT-IS-ABSENT */
Object put_optimize_procedure_code_qm_where_slot_is_absent(procedure,
	    previously_optimized_qm)
    Object procedure, previously_optimized_qm;
{
    x_note_fn_call(160,69);
    if (previously_optimized_qm)
	List_of_previously_optimized_procedures = gensym_cons_1(procedure,
		List_of_previously_optimized_procedures);
    return VALUES_1(Nil);
}

/* RECOMPILE-PREVIOUSLY-OPTIMIZED-PROCEDURES */
Object recompile_previously_optimized_procedures()
{
    Object procedure, ab_loop_list_;

    x_note_fn_call(160,70);
    procedure = Nil;
    ab_loop_list_ = List_of_previously_optimized_procedures;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    procedure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    recompile_item(procedure);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(List_of_previously_optimized_procedures);
    List_of_previously_optimized_procedures = Nil;
    return VALUES_1(Nil);
}

static Object Qparse_results_qm;   /* parse-results? */

/* PUT-PARSE-RESULTS? */
Object put_parse_results_qm(procedure,old_parse,initializing_qm)
    Object procedure, old_parse, initializing_qm;
{
    x_note_fn_call(160,71);
    if (initializing_qm && ( !TRUEP(compilations_up_to_date_p(procedure)) 
	    ||  !TRUEP(block_can_be_inlined_p(procedure)) ||  
	    !TRUEP(cached_parses_up_to_date_p(procedure))) && Loading_kb_p) {
	reclaim_slot_value(old_parse);
	old_parse = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qparse_results_qm);
    set_lookup_slot_value_1(procedure,Qparse_results_qm,old_parse);
    return VALUES_1(old_parse);
}

static Object Qmd5_identifier_qm;  /* md5-identifier? */

/* PUT-MD5-IDENTIFIER? */
Object put_md5_identifier_qm(procedure,wide_string_qm,initializing_qm)
    Object procedure, wide_string_qm, initializing_qm;
{
    x_note_fn_call(160,72);
    if (initializing_qm && ( !TRUEP(compilations_up_to_date_p(procedure)) 
	    ||  !TRUEP(block_can_be_inlined_p(procedure)) ||  
	    !(IFIX(Kb_flags) >= (SI_Long)265L)) && Loading_kb_p) {
	reclaim_slot_value(wide_string_qm);
	wide_string_qm = Nil;
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qmd5_identifier_qm);
    set_lookup_slot_value_1(procedure,Qmd5_identifier_qm,wide_string_qm);
    return VALUES_1(wide_string_qm);
}

/* CODE-BODY-NUMBER-OF-CODE-BODY */
Object code_body_number_of_code_body(code_body_to_check)
    Object code_body_to_check;
{
    Object procedure_qm_1, code_bodies, sibling_code_body, ab_loop_list_;
    Object ab_loop_iter_flag_;
    SI_Long count_1;

    x_note_fn_call(160,73);
    procedure_qm_1 = ISVREF(code_body_to_check,(SI_Long)2L);
    code_bodies = procedure_qm_1 ? ISVREF(procedure_qm_1,(SI_Long)28L) : Nil;
    sibling_code_body = Nil;
    ab_loop_list_ = code_bodies;
    count_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    sibling_code_body = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	count_1 = count_1 + (SI_Long)1L;
    if (EQ(code_body_to_check,sibling_code_body))
	return VALUES_1(FIX(count_1));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX((SI_Long)0L));
    return VALUES_1(Qnil);
}

/* COMPRESS-ANNOTATION-INFO-FOR-SAVING */
Object compress_annotation_info_for_saving(actual_lookup_structure_qm)
    Object actual_lookup_structure_qm;
{
    Object info, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(160,74);
    info = Nil;
    ab_loop_list_ = actual_lookup_structure_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(compress_annotation_list_for_saving(info),Nil);
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

/* COMPRESS-ANNOTATION-LIST-FOR-SAVING */
Object compress_annotation_list_for_saving(info)
    Object info;
{
    x_note_fn_call(160,75);
    return VALUES_1(info);
}

/* GET-ANNOTATION-FOR-ADDRESS-IF-ANY */
Object get_annotation_for_address_if_any(address,code_body)
    Object address, code_body;
{
    Object actual_lookup_structure_qm, start_address, line_number;
    Object character_number, next_start_address, ab_loop_list_, temp;
    Object non_wrapped_line_index, non_wrapped_character_index;
    Object non_wrapped_character_index_past_linebreak;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,76);
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      actual_lookup_structure_qm = 
	      get_lookup_structure_if_any(ISVREF(Code_body,(SI_Long)2L));
      if (actual_lookup_structure_qm) {
	  start_address = Nil;
	  line_number = Nil;
	  character_number = Nil;
	  next_start_address = Nil;
	  ab_loop_list_ = nth(code_body_number_of_code_body(Code_body),
		  actual_lookup_structure_qm);
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  temp = CAR(ab_loop_list_);
	  start_address = CAR(temp);
	  temp = CAR(ab_loop_list_);
	  temp = CDR(temp);
	  line_number = CAR(temp);
	  temp = CAR(ab_loop_list_);
	  temp = CDR(temp);
	  temp = CDR(temp);
	  character_number = CAR(temp);
	  temp = CDR(ab_loop_list_);
	  temp = CAR(temp);
	  next_start_address = CAR(temp);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (NUM_LE(start_address,address) && ( 
		  !TRUEP(next_start_address) || FIXNUM_LT(address,
		  next_start_address))) {
	      temp = ISVREF(ISVREF(Code_body,(SI_Long)2L),(SI_Long)27L);
	      result = convert_to_non_word_wrapped_text_position(CDR(temp),
		      line_number,character_number);
	      MVS_3(result,non_wrapped_line_index,
		      non_wrapped_character_index,
		      non_wrapped_character_index_past_linebreak);
	      temp = FIXNUM_ADD1(FIXNUM_MINUS(non_wrapped_character_index,
		      non_wrapped_character_index_past_linebreak));
	      result = VALUES_5(line_number,character_number,
		      non_wrapped_line_index,non_wrapped_character_index,temp);
	      goto end_1;
	  }
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	end_1:;
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* GET-ADDRESS-FOR-LINE-FROM-ANNOTATION-IF-ANY */
Object get_address_for_line_from_annotation_if_any(line,procedure)
    Object line, procedure;
{
    Object actual_lookup_structure_qm, start_address_qm, nth_code_body_qm;
    Object temp, procedure_text, non_word_wrapped_procedure_text;
    Object code_body_specific_annotations, ab_loop_list_, ab_loop_iter_flag_;
    Object start_address, line_number, char_index, ab_loop_list__1;
    Object non_word_wrapped_line_index_qm, ab_loop_desetq_;
    SI_Long nth_code_body;
    char temp_1;

    x_note_fn_call(160,77);
    actual_lookup_structure_qm = get_lookup_structure_if_any(procedure);
    if (actual_lookup_structure_qm) {
	start_address_qm = Nil;
	nth_code_body_qm = Nil;
	temp = ISVREF(procedure,(SI_Long)27L);
	procedure_text = CDR(temp);
	non_word_wrapped_procedure_text = 
		convert_to_non_word_wrapped_text(1,procedure_text);
	code_body_specific_annotations = Nil;
	ab_loop_list_ = actual_lookup_structure_qm;
	nth_code_body = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	code_body_specific_annotations = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    nth_code_body = nth_code_body + (SI_Long)1L;
	start_address = Nil;
	line_number = Nil;
	char_index = Nil;
	ab_loop_list__1 = code_body_specific_annotations;
	non_word_wrapped_line_index_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	start_address = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	line_number = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	char_index = CAR(temp);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	non_word_wrapped_line_index_qm = 
		determine_corrected_text_position_if_necessary(5,
		line_number,char_index,non_word_wrapped_procedure_text,
		procedure_text,FIX((SI_Long)1L));
	if (non_word_wrapped_line_index_qm && 
		FIXNUM_EQ(non_word_wrapped_line_index_qm,line)) {
	    start_address_qm = start_address;
	    nth_code_body_qm = FIX(nth_code_body);
	    temp_1 = TRUEP(T);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1)
	    goto end_loop;
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	reclaim_text(non_word_wrapped_procedure_text);
	return VALUES_2(start_address_qm,nth_code_body_qm);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* PROCEDURE-CODE-BODY-GIVEN-NUMBER */
Object procedure_code_body_given_number(procedure,code_body_number)
    Object procedure, code_body_number;
{
    Object temp;

    x_note_fn_call(160,78);
    temp = nthcdr(code_body_number,ISVREF(procedure,(SI_Long)28L));
    return VALUES_1(CAR(temp));
}

/* SURROUNDING-CODE-BODY? */
Object surrounding_code_body_qm(code_body_to_check)
    Object code_body_to_check;
{
    Object surrounding_number_qm;

    x_note_fn_call(160,79);
    surrounding_number_qm = ISVREF(code_body_to_check,(SI_Long)3L);
    if (surrounding_number_qm)
	return procedure_code_body_given_number(ISVREF(code_body_to_check,
		(SI_Long)2L),surrounding_number_qm);
    else
	return VALUES_1(Nil);
}

static Object string_constant;     /* "Aborting procedure invocations of ~NF before compiling this procedure." */

/* COMPILE-PROCEDURE-DEFINITION-FOR-SLOT */
Object compile_procedure_definition_for_slot varargs_1(int, n)
{
    Object parsed_definition, procedure, gensymed_symbol;
    Object invocations, scope_conses, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, prin, prins_to_abort, ab_loopvar_;
    Object ab_loopvar__1, ab_less_than_branch_qm_, temp, invocation;
    Object ab_loop_list_;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(160,80);
    INIT_ARGS_nonrelocating();
    parsed_definition = REQUIRED_ARG_nonrelocating();
    procedure = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    invocations = ISVREF(procedure,(SI_Long)26L);
    if (invocations) {
	scope_conses = Scope_conses;
	ab_hash_table_ = invocations;
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	prin = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  prins_to_abort = Nil;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
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
	  prin = M_CDR(ab_entry_cons_);
	  ab_loopvar__1 = gensym_cons_1(prin,Nil);
	  if (ab_loopvar_)
	      M_CDR(ab_loopvar_) = ab_loopvar__1;
	  else
	      prins_to_abort = ab_loopvar__1;
	  ab_loopvar_ = ab_loopvar__1;
	  goto next_loop;
	end_loop_3:
	  invocation = Nil;
	  ab_loop_list_ = prins_to_abort;
	next_loop_4:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_4;
	  invocation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  temp = invocation;
	  signal_procedure_invocation_error(temp,Qerror,FIX((SI_Long)1L),
		  tformat_text_string(2,string_constant,procedure),Nil);
	  goto next_loop_4;
	end_loop_4:;
	  reclaim_gensym_list_1(prins_to_abort);
	POP_SPECIAL();
    }
    compile_procedure_definition(procedure,parsed_definition);
    return VALUES_1(T);
}

static Object Qclass_of_procedure_invocation;  /* class-of-procedure-invocation */

static Object Qprocedure_invocation;  /* procedure-invocation */

static Object Qincomplete;         /* incomplete */

static Object Qprocedure_definition;  /* procedure-definition */

static Object Qdynamic_breakpoint_settings;  /* dynamic-breakpoint-settings */

/* PUT-PROCEDURE-DEFINITION */
Object put_procedure_definition(procedure,procedure_definition,initializing_qm)
    Object procedure, procedure_definition, initializing_qm;
{
    Object sub_class_bit_vector, car_new_value, temp_1, breakpoint;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(160,81);
    if (initializing_qm &&  !(IFIX(Kb_flags) >= (SI_Long)217L) && 
		Loading_kb_p) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(procedure,Qclass_of_procedure_invocation);
	SVREF(procedure,FIX((SI_Long)20L)) = Qprocedure_invocation;
    }
    if (initializing_qm &&  !TRUEP(compilations_up_to_date_p(procedure))) {
	sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Method_declaration_class_description,
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
    if (temp ? TRUEP(Loading_kb_p) : TRUEP(Nil)) {
	reclaim_slot_value(CAR(procedure_definition));
	car_new_value = No_value;
	M_CAR(procedure_definition) = car_new_value;
	note_frame_with_compilation_removed(procedure);
	update_frame_status(procedure,Qincomplete,T);
    }
    analyze_export_info_for_parsability(procedure,procedure_definition);
    if (EQ(CAR(procedure_definition),No_value))
	change_slot_value(3,procedure,Procedure_code_bodies_slot_name,Nil);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(procedure,Qprocedure_definition);
    SVREF(procedure,FIX((SI_Long)27L)) = procedure_definition;
    if ( !TRUEP(initializing_qm)) {
	temp_1 = ISVREF(procedure,(SI_Long)8L);
	temp =  !TRUEP(CAR(temp_1));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	breakpoint = Nil;
	ab_loop_list_ = get_lookup_slot_value_given_default(procedure,
		Qdynamic_breakpoint_settings,Nil);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	breakpoint = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = dynamic_breakpoint_line_func(breakpoint);
	ab_loopvar__2 = gensym_cons_1(gensym_list_2(temp_1,
		dynamic_breakpoint_status_func(breakpoint)),Nil);
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
	adjust_dynamic_breakpoints(procedure,temp_1);
    }
    return VALUES_1(procedure_definition);
}

Object Dynamic_breakpoint_enabled = UNBOUND;

Object Dynamic_breakpoint_disabled = UNBOUND;

Object Dynamic_breakpoint_valid = UNBOUND;

Object Dynamic_breakpoint_invalid = UNBOUND;

/* MAKE-DYNAMIC-BREAKPOINT */
Object make_dynamic_breakpoint(dynamic_breakpoint_address,
	    dynamic_breakpoint_line,dynamic_breakpoint_nth_code_body,
	    dynamic_breakpoint_status,dynamic_breakpoint_validity)
    Object dynamic_breakpoint_address, dynamic_breakpoint_line;
    Object dynamic_breakpoint_nth_code_body, dynamic_breakpoint_status;
    Object dynamic_breakpoint_validity;
{
    x_note_fn_call(160,82);
    return slot_value_cons_1(dynamic_breakpoint_address,
	    slot_value_cons_1(dynamic_breakpoint_line,
	    slot_value_cons_1(dynamic_breakpoint_nth_code_body,
	    slot_value_cons_1(dynamic_breakpoint_status,
	    slot_value_cons_1(dynamic_breakpoint_validity,Nil)))));
}

/* DYNAMIC-BREAKPOINT-LINE-FUNC */
Object dynamic_breakpoint_line_func(dp)
    Object dp;
{
    Object temp;

    x_note_fn_call(160,83);
    temp = CDR(dp);
    return VALUES_1(CAR(temp));
}

/* DYNAMIC-BREAKPOINT-STATUS-FUNC */
Object dynamic_breakpoint_status_func(dp)
    Object dp;
{
    Object temp;

    x_note_fn_call(160,84);
    temp = CDDDR(dp);
    return VALUES_1(CAR(temp));
}

/* DYNAMIC-BREAKPOINT-VALIDITY-FUNC */
Object dynamic_breakpoint_validity_func(dp)
    Object dp;
{
    Object temp;

    x_note_fn_call(160,85);
    temp = CDDDDR(dp);
    return VALUES_1(CAR(temp));
}

/* DYNAMIC-BREAKPOINT-ENABLED-P */
Object dynamic_breakpoint_enabled_p(dynamic_breakpoint)
    Object dynamic_breakpoint;
{
    Object temp;

    x_note_fn_call(160,86);
    temp = CDDDR(dynamic_breakpoint);
    return VALUES_1(EQ(CAR(temp),Dynamic_breakpoint_enabled) ? T : Nil);
}

/* DYNAMIC-BREAKPOINT-VALID-P */
Object dynamic_breakpoint_valid_p(dynamic_breakpoint)
    Object dynamic_breakpoint;
{
    Object temp;

    x_note_fn_call(160,87);
    temp = CDDDDR(dynamic_breakpoint);
    return VALUES_1(EQ(CAR(temp),Dynamic_breakpoint_valid) ? T : Nil);
}

/* GET-DYNAMIC-BREAKPOINT-AT-LINE? */
Object get_dynamic_breakpoint_at_line_qm(procedure,line)
    Object procedure, line;
{
    Object dynamic_breakpoint, ab_loop_list_, breakpoint_line, temp;

    x_note_fn_call(160,88);
    dynamic_breakpoint = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(procedure,
	    Qdynamic_breakpoint_settings,Nil);
    breakpoint_line = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dynamic_breakpoint = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = CDR(dynamic_breakpoint);
    breakpoint_line = CAR(temp);
    if (EQL(breakpoint_line,line))
	return VALUES_1(dynamic_breakpoint);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_1;   /* "there ~a invalid dynamic breakpoint~a on line~a" */

static Object string_constant_2;   /* "are" */

static Object string_constant_3;   /* "is an" */

static Object string_constant_4;   /* "s" */

static Object string_constant_5;   /* "" */

static Object string_constant_6;   /* " ~a" */

static Object string_constant_7;   /* ", " */

static Object string_constant_8;   /* " and " */

/* WRITE-INVALID-DYNAMIC-BREAKPOINT-NOTE */
Object write_invalid_dynamic_breakpoint_note(lines,gensymed_symbol)
    Object lines, gensymed_symbol;
{
    Object line, rest_1, ab_loop_list_;

    x_note_fn_call(160,89);
    tformat(4,string_constant_1,CDR(lines) ? string_constant_2 : 
	    string_constant_3,CDR(lines) ? string_constant_4 : 
	    string_constant_5,CDR(lines) ? string_constant_4 : 
	    string_constant_5);
    line = Nil;
    rest_1 = Nil;
    ab_loop_list_ = lines;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line = CAR(ab_loop_list_);
    rest_1 = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tformat(2,string_constant_6,line);
    if ( !TRUEP(rest_1))
	goto end_loop;
    twrite_general_string(CDR(rest_1) ? string_constant_7 : string_constant_8);
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object Qinvalid_dynamic_breakpoint;  /* invalid-dynamic-breakpoint */

/* ADJUST-INVALID-DYNAMIC-BREAKPOINT-FRAME-NOTE */
Object adjust_invalid_dynamic_breakpoint_frame_note(procedure)
    Object procedure;
{
    Object dynamic_breakpoint, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp, invalid_breakpoints_qm;

    x_note_fn_call(160,90);
    delete_frame_note_if_any(Qinvalid_dynamic_breakpoint,procedure);
    dynamic_breakpoint = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(procedure,
	    Qdynamic_breakpoint_settings,Nil);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    dynamic_breakpoint = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(dynamic_breakpoint_valid_p(dynamic_breakpoint))) {
	temp = CDR(dynamic_breakpoint);
	ab_loopvar__2 = slot_value_cons_1(CAR(temp),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    invalid_breakpoints_qm = ab_loopvar_;
    goto end_1;
    invalid_breakpoints_qm = Qnil;
  end_1:;
    if (invalid_breakpoints_qm)
	add_frame_note(3,Qinvalid_dynamic_breakpoint,procedure,
		sort_list(invalid_breakpoints_qm,SYMBOL_FUNCTION(Qnum_lt),
		Nil));
    return VALUES_1(Nil);
}

/* ADD-DYNAMIC-BREAKPOINT */
Object add_dynamic_breakpoint(procedure,address_qm,line,status,
	    nth_code_body_qm)
    Object procedure, address_qm, line, status, nth_code_body_qm;
{
    Object dynamic_breakpoints_qm, temp, temp_1;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object dynamic_breakpoint_settings_new_value;

    x_note_fn_call(160,91);
    dynamic_breakpoints_qm = get_lookup_slot_value_given_default(procedure,
	    Qdynamic_breakpoint_settings,Nil);
    if ( !TRUEP(get_dynamic_breakpoint_at_line_qm(procedure,line))) {
	temp = address_qm;
	if (temp);
	else
	    temp = FIX((SI_Long)-1L);
	temp_1 = nth_code_body_qm;
	if (temp_1);
	else
	    temp_1 = FIX((SI_Long)-1L);
	slot_value_push_modify_macro_arg = make_dynamic_breakpoint(temp,
		line,temp_1,status,address_qm ? Dynamic_breakpoint_valid : 
		Dynamic_breakpoint_invalid);
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value_given_default(procedure,
		Qdynamic_breakpoint_settings,Nil);
	dynamic_breakpoint_settings_new_value = slot_value_cons_1(car_1,cdr_1);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(procedure,Qdynamic_breakpoint_settings);
	set_lookup_slot_value_1(procedure,Qdynamic_breakpoint_settings,
		dynamic_breakpoint_settings_new_value);
	adjust_invalid_dynamic_breakpoint_frame_note(procedure);
    }
    return VALUES_2(address_qm, !TRUEP(dynamic_breakpoints_qm) ? T : Nil);
}

/* DELETE-ALL-DYNAMIC-BREAKPOINTS */
Object delete_all_dynamic_breakpoints(procedure)
    Object procedure;
{
    x_note_fn_call(160,92);
    if (get_lookup_slot_value_given_default(procedure,
	    Qdynamic_breakpoint_settings,Nil)) {
	delete_frame_note_if_any(Qinvalid_dynamic_breakpoint,procedure);
	reclaim_slot_value_tree_1(get_lookup_slot_value_given_default(procedure,
		Qdynamic_breakpoint_settings,Nil));
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(procedure,Qdynamic_breakpoint_settings);
	set_lookup_slot_value_1(procedure,Qdynamic_breakpoint_settings,Nil);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

/* DELETE-DYNAMIC-BREAKPOINT */
Object delete_dynamic_breakpoint(procedure,line)
    Object procedure, line;
{
    Object breakpoint_qm, new_breakpoints;

    x_note_fn_call(160,93);
    breakpoint_qm = get_dynamic_breakpoint_at_line_qm(procedure,line);
    if (breakpoint_qm) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(procedure,Qdynamic_breakpoint_settings);
	new_breakpoints = set_lookup_slot_value_1(procedure,
		Qdynamic_breakpoint_settings,
		delete_gensym_element_1(breakpoint_qm,
		get_lookup_slot_value_given_default(procedure,
		Qdynamic_breakpoint_settings,Nil)));
	adjust_invalid_dynamic_breakpoint_frame_note(procedure);
	return VALUES_2(T, !TRUEP(new_breakpoints) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* TURN-ON-DYNAMIC-BREAKPOINT */
Object turn_on_dynamic_breakpoint(procedure,line)
    Object procedure, line;
{
    Object breakpoint_qm, car_arg;

    x_note_fn_call(160,94);
    breakpoint_qm = get_dynamic_breakpoint_at_line_qm(procedure,line);
    if (breakpoint_qm && dynamic_breakpoint_valid_p(breakpoint_qm)) {
	car_arg = CDDDR(breakpoint_qm);
	return VALUES_1(M_CAR(car_arg) = Dynamic_breakpoint_enabled);
    }
    else
	return VALUES_1(Nil);
}

/* TURN-OFF-DYNAMIC-BREAKPOINT */
Object turn_off_dynamic_breakpoint(procedure,line)
    Object procedure, line;
{
    Object breakpoint_qm, car_arg;

    x_note_fn_call(160,95);
    breakpoint_qm = get_dynamic_breakpoint_at_line_qm(procedure,line);
    if (breakpoint_qm && dynamic_breakpoint_valid_p(breakpoint_qm)) {
	car_arg = CDDDR(breakpoint_qm);
	return VALUES_1(M_CAR(car_arg) = Dynamic_breakpoint_disabled);
    }
    else
	return VALUES_1(Nil);
}

static Object Qframe_status_and_notes;  /* frame-status-and-notes */

static Object Qstack_change;       /* stack-change */

/* ADJUST-DYNAMIC-BREAKPOINTS */
Object adjust_dynamic_breakpoints(procedure,info)
    Object procedure, info;
{
    Object slot_description, new_cons, temp, svref_arg_2, svref_new_value;
    Object gensymed_symbol, gensymed_symbol_1, stack_of_slot_value_changes;
    Object line, status, ab_loop_list_, ab_loop_desetq_, temp_1;
    Object frame_and_slot_or_atom, ab_loop_it_, stack_change_pop_store, cons_1;
    Object next_cons;
    char temp_2;
    Declare_special(1);

    x_note_fn_call(160,96);
    slot_description = 
	    get_slot_description_of_class_description_function(Qframe_status_and_notes,
	    ISVREF(procedure,(SI_Long)1L),Nil);
    new_cons = ISVREF(Available_stack_change_conses_vector,
	    IFIX(Current_thread_index));
    if (new_cons) {
	temp = Available_stack_change_conses_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = M_CDR(new_cons);
	SVREF(temp,svref_arg_2) = svref_new_value;
	if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index)))) {
	    temp = Available_stack_change_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = Nil;
	}
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_stack_change_cons_pool();
    if (Nil)
	gensymed_symbol_1 = nconc2(stack_change_list_2(procedure,
		slot_description),stack_change_cons_1(Nil,Nil));
    else {
	new_cons = ISVREF(Available_stack_change_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp = Available_stack_change_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_stack_change_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp = Available_stack_change_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_stack_change_cons_pool();
	M_CAR(gensymed_symbol_1) = procedure;
	M_CDR(gensymed_symbol_1) = slot_description;
	inline_note_allocate_cons(gensymed_symbol_1,Qstack_change);
    }
    M_CAR(gensymed_symbol) = gensymed_symbol_1;
    temp = Stack_of_slot_value_changes;
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qstack_change);
    stack_of_slot_value_changes = gensymed_symbol;
    PUSH_SPECIAL_WITH_SYMBOL(Stack_of_slot_value_changes,Qstack_of_slot_value_changes,stack_of_slot_value_changes,
	    0);
      delete_all_dynamic_breakpoints(procedure);
      line = Nil;
      status = Nil;
      ab_loop_list_ = nreverse(info);
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      line = CAR(ab_loop_desetq_);
      temp_1 = CDR(ab_loop_desetq_);
      status = CAR(temp_1);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      set_dynamic_breakpoint_internal(4,procedure,line,status,Nil);
      goto next_loop;
    end_loop:;
      temp_2 = TRUEP(Suppress_updating_of_slot_value_representations_qm);
      if (temp_2);
      else if (M_CDR(Stack_of_slot_value_changes)) {
	  frame_and_slot_or_atom = Nil;
	  ab_loop_list_ = M_CDR(Stack_of_slot_value_changes);
	  ab_loop_it_ = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  frame_and_slot_or_atom = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (ATOM(frame_and_slot_or_atom))
	      goto end_loop_1;
	  temp_2 = EQ(slot_description,M_CDR(frame_and_slot_or_atom));
	  if (temp_2);
	  else {
	      temp_1 = M_CDR(frame_and_slot_or_atom);
	      temp_2 = CONSP(temp_1) ? EQ(slot_description,
		      SECOND(frame_and_slot_or_atom)) && EQ(Nil,
		      THIRD(frame_and_slot_or_atom)) && EQ(Nil,
		      CDDDR(frame_and_slot_or_atom)) : TRUEP(Nil);
	  }
	  ab_loop_it_ = temp_2 ? (EQ(procedure,
		  M_CAR(frame_and_slot_or_atom)) ? T : Nil) : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp_2 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_2 = TRUEP(Nil);
      if ( !temp_2)
	  update_all_representations_of_slot(procedure,slot_description,
		  Nil,Nil);
      if (ISVREF(slot_description,(SI_Long)14L))
	  update_frame_name_references(procedure);
      stack_change_pop_store = Nil;
      cons_1 = Stack_of_slot_value_changes;
      if (cons_1) {
	  stack_change_pop_store = M_CAR(cons_1);
	  next_cons = M_CDR(cons_1);
	  inline_note_reclaim_cons(cons_1,Qstack_change);
	  if (ISVREF(Available_stack_change_conses_tail_vector,
		  IFIX(Current_thread_index))) {
	      temp = ISVREF(Available_stack_change_conses_tail_vector,
		      IFIX(Current_thread_index));
	      M_CDR(temp) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  else {
	      temp = Available_stack_change_conses_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	      temp = Available_stack_change_conses_tail_vector;
	      svref_arg_2 = Current_thread_index;
	      SVREF(temp,svref_arg_2) = cons_1;
	  }
	  M_CDR(cons_1) = Nil;
      }
      else
	  next_cons = Nil;
      Stack_of_slot_value_changes = next_cons;
      reclaim_stack_change_tree_1(stack_change_pop_store);
      if (Stack_of_slot_value_changes) {
	  temp_1 = M_CAR(Stack_of_slot_value_changes);
	  temp_2 = ATOM(temp_1);
      }
      else
	  temp_2 = TRUEP(Nil);
      if (temp_2 ?  !TRUEP(Suppress_use_of_stack_of_slot_value_changes_p) :
	       TRUEP(Nil))
	  do_deferred_updates_to_representations_in_tables();
    POP_SPECIAL();
    reclaim_gensym_tree_1(info);
    return VALUES_1(Nil);
}

/* INITIAL-DYNAMIC-BREAKPOINTS */
Object initial_dynamic_breakpoints(procedure)
    Object procedure;
{
    x_note_fn_call(160,97);
    return VALUES_1(Nil);
}

static Object Qline_number;        /* line-number */

static Object Qis_enabled;         /* is-enabled */

static Object Qis_valid;           /* is-valid */

/* GET-DYNAMIC-BREAKPOINTS */
Object get_dynamic_breakpoints(proc)
    Object proc;
{
    Object breakpoint, ab_loop_list_, eval_list, ab_loopvar_, ab_loopvar__1;
    Object gensymed_symbol, gensymed_symbol_1, temp, car_new_value;

    x_note_fn_call(160,98);
    breakpoint = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(proc,
	    Qdynamic_breakpoint_settings,Nil);
    eval_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    breakpoint = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = make_eval_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qline_number;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDR(breakpoint);
    car_new_value = CAR(temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qis_enabled;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = CDDDR(breakpoint);
    car_new_value = EQ(CAR(temp),Dynamic_breakpoint_enabled) ? 
	    Evaluation_true_value : Evaluation_false_value;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qis_valid;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = dynamic_breakpoint_valid_p(breakpoint) ? 
	    Evaluation_true_value : Evaluation_false_value;
    M_CAR(gensymed_symbol_1) = car_new_value;
    ab_loopvar__1 = 
	    eval_cons_1(allocate_evaluation_structure(gensymed_symbol),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	eval_list = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    goto next_loop;
  end_loop:
    temp = allocate_evaluation_sequence(eval_list);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* SET-DYNAMIC-BREAKPOINTS */
Object set_dynamic_breakpoints(proc,new_value)
    Object proc, new_value;
{
    Object gensymed_symbol, held_vector, struct_1, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, temp;
    SI_Long next_index, length_1;

    x_note_fn_call(160,99);
    gensymed_symbol = new_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    struct_1 = Nil;
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
    struct_1 = validated_elt;
    temp = estructure_slot(struct_1,Qline_number,Nil);
    ab_loopvar__2 = gensym_cons_1(gensym_list_2(temp,
	    evaluation_truth_value_is_true_p(estructure_slot(struct_1,
	    Qis_enabled,Nil)) ? Dynamic_breakpoint_enabled : 
	    Dynamic_breakpoint_disabled),Nil);
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
    adjust_dynamic_breakpoints(proc,temp);
    return VALUES_1(Nil);
}

static Object Qprocedure;          /* procedure */

/* INITIALIZE-FOR-PROCEDURE */
Object initialize_for_procedure(procedure)
    Object procedure;
{
    Object frame, sub_vector_qm, method_function_qm, temp_1;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(160,100);
    frame = procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qprocedure)) {
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
    temp =  !TRUEP(ISVREF(procedure,(SI_Long)27L));
    if (temp);
    else
	temp =  !TRUEP(get_slot_value_function(procedure,
		Procedure_code_bodies_slot_name,Nil));
    if (temp);
    else {
	temp_1 = ISVREF(procedure,(SI_Long)27L);
	temp = EQ(CAR(temp_1),No_value);
    }
    if (temp)
	return update_frame_status(procedure,Qincomplete,Nil);
    else
	return VALUES_1(Nil);
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-PROCEDURE */
Object deactivate_subclass_of_entity_for_procedure(procedure)
    Object procedure;
{
    x_note_fn_call(160,101);
    if ( !((SI_Long)0L != (IFIX(ISVREF(procedure,(SI_Long)4L)) & 
	    (SI_Long)16777216L)))
	return abort_procedure_invocations_of_procedure(procedure);
    else
	return VALUES_1(Nil);
}

static Object string_constant_9;   /* "Aborting procedure invocations of ~NF before deactivating this ~
				    *                procedure."
				    */

/* ABORT-PROCEDURE-INVOCATIONS-OF-PROCEDURE */
Object abort_procedure_invocations_of_procedure(procedure)
    Object procedure;
{
    Object invocations, scope_conses, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, invocation_to_abort;
    Object ab_less_than_branch_qm_, gensymed_symbol, temp;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(160,102);
    invocations = ISVREF(procedure,(SI_Long)26L);
    if (invocations) {
	scope_conses = Scope_conses;
	ab_hash_table_ = invocations;
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	invocation_to_abort = Nil;
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
	  invocation_to_abort = M_CDR(ab_entry_cons_);
	  if (true_base_of_procedure_invocation_stack_p(invocation_to_abort))
	      abort_procedure_invocation(1,invocation_to_abort);
	  else {
	      temp = invocation_to_abort;
	      signal_procedure_invocation_error(temp,Qerror,
		      FIX((SI_Long)1L),tformat_text_string(2,
		      string_constant_9,procedure),Nil);
	  }
	  goto next_loop;
	end_loop_3:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* CLEANUP-FOR-PROCEDURE */
Object cleanup_for_procedure(procedure)
    Object procedure;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,103);
    abort_procedure_invocations_of_procedure(procedure);
    frame = procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qprocedure)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-PROCEDURE */
Object note_runs_while_inactive_change_for_procedure(procedure)
    Object procedure;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,104);
    frame = procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)18L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qprocedure)) {
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
    if ( !((SI_Long)0L != (IFIX(ISVREF(procedure,(SI_Long)4L)) & 
	    (SI_Long)16777216L)) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(procedure,(SI_Long)5L)) & (SI_Long)1L)))
	return abort_procedure_invocations_of_procedure(procedure);
    else
	return VALUES_1(Nil);
}

/* MANUALLY-DISABLE-FOR-PROCEDURE */
Object manually_disable_for_procedure(procedure)
    Object procedure;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,105);
    frame = procedure;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)47L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qprocedure)) {
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
    if ((SI_Long)0L != (IFIX(ISVREF(procedure,(SI_Long)4L)) & 
	    (SI_Long)16777216L))
	return abort_procedure_invocations_of_procedure(procedure);
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_procedure_invocation = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_procedure_invocations, Qchain_of_available_procedure_invocations);

DEFINE_VARIABLE_WITH_SYMBOL(Procedure_invocation_count, Qprocedure_invocation_count);

Object Chain_of_available_procedure_invocations_vector = UNBOUND;

/* PROCEDURE-INVOCATION-STRUCTURE-MEMORY-USAGE */
Object procedure_invocation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(160,106);
    temp = Procedure_invocation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)28L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PROCEDURE-INVOCATION-COUNT */
Object outstanding_procedure_invocation_count()
{
    Object def_structure_procedure_invocation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,107);
    gensymed_symbol = IFIX(Procedure_invocation_count);
    def_structure_procedure_invocation_variable = 
	    Chain_of_available_procedure_invocations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_procedure_invocation_variable))
	goto end_loop;
    def_structure_procedure_invocation_variable = 
	    ISVREF(def_structure_procedure_invocation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PROCEDURE-INVOCATION-1 */
Object reclaim_procedure_invocation_1(procedure_invocation)
    Object procedure_invocation;
{
    Object structure_being_reclaimed, gensymed_symbol, temp, svref_arg_2;
    Declare_special(2);

    x_note_fn_call(160,108);
    inline_note_reclaim_cons(procedure_invocation,Nil);
    structure_being_reclaimed = procedure_invocation;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(procedure_invocation,(SI_Long)7L);
      if (CAS_SVREF(procedure_invocation,(SI_Long)7L,gensymed_symbol,Nil)) {
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
      SVREF(procedure_invocation,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(procedure_invocation,(SI_Long)9L));
      SVREF(procedure_invocation,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_procedure_invocations_vector,
	    IFIX(Current_thread_index));
    SVREF(procedure_invocation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_procedure_invocations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = procedure_invocation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PROCEDURE-INVOCATION */
Object reclaim_structure_for_procedure_invocation(procedure_invocation)
    Object procedure_invocation;
{
    x_note_fn_call(160,109);
    return reclaim_procedure_invocation_1(procedure_invocation);
}

/* MAKE-PERMANENT-PROCEDURE-INVOCATION-STRUCTURE-INTERNAL */
Object make_permanent_procedure_invocation_structure_internal()
{
    Object def_structure_procedure_invocation_variable;
    Object defstruct_g2_procedure_invocation_variable, the_array, temp;
    Object svref_arg_2;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(160,110);
    def_structure_procedure_invocation_variable = Nil;
    atomic_incff_symval(Qprocedure_invocation_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_procedure_invocation_variable = Nil;
	gensymed_symbol_1 = (SI_Long)28L;
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
	defstruct_g2_procedure_invocation_variable = the_array;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_procedure_invocation_g2_struct;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)5L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)6L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)7L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)8L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,FIX((SI_Long)9L)) 
		= Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_procedure_invocation_variable,
		FIX((SI_Long)21L)) = Nil;
	def_structure_procedure_invocation_variable = 
		defstruct_g2_procedure_invocation_variable;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)1L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)3L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)4L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)5L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)6L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)8L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)15L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)16L)) = Nil;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)17L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = ISVREF(Chain_of_available_procedure_invocations_vector,
		IFIX(Current_thread_index));
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_procedure_invocations_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = def_structure_procedure_invocation_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_procedure_invocation_variable);
}

/* MAKE-PROCEDURE-INVOCATION-1 */
Object make_procedure_invocation_1()
{
    Object def_structure_procedure_invocation_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(160,111);
    def_structure_procedure_invocation_variable = 
	    ISVREF(Chain_of_available_procedure_invocations_vector,
	    IFIX(Current_thread_index));
    if (def_structure_procedure_invocation_variable) {
	svref_arg_1 = Chain_of_available_procedure_invocations_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_procedure_invocation_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_procedure_invocation_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_procedure_invocation_g2_struct;
    }
    else
	def_structure_procedure_invocation_variable = 
		make_permanent_procedure_invocation_structure_internal();
    inline_note_allocate_cons(def_structure_procedure_invocation_variable,Nil);
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_procedure_invocation_variable,FIX((SI_Long)21L)) = Nil;
    return VALUES_1(def_structure_procedure_invocation_variable);
}

/* PROCEDURE-INVOCATION? */
Object procedure_invocation_qm(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(160,112);
    temp = SIMPLE_VECTOR_P(thing) ? (EQ(ISVREF(thing,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) ? 
	    T : Nil) : Qnil;
    return VALUES_1(temp);
}

/* CALLING-PROCEDURE-INVOCATION */
Object calling_procedure_invocation(code_body_invocation)
    Object code_body_invocation;
{
    x_note_fn_call(160,113);
    if (code_body_invocation) {
      next_loop:
	code_body_invocation = ISVREF(code_body_invocation,(SI_Long)12L);
	if ( !TRUEP(code_body_invocation))
	    return VALUES_1(Nil);
	if (SIMPLE_VECTOR_P(code_body_invocation) && 
		EQ(ISVREF(code_body_invocation,(SI_Long)0L),
		Qg2_defstruct_structure_name_procedure_invocation_g2_struct))
	    return VALUES_1(code_body_invocation);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* FIND-PROCEDURE-INVOCATION-IN-MODULE */
Object find_procedure_invocation_in_module(procedure_invocation,module)
    Object procedure_invocation, module;
{
    Object callee, caller_qm, procedure;

    x_note_fn_call(160,114);
    callee = procedure_invocation;
    caller_qm = Nil;
    procedure = Nil;
  next_loop:
    if ( !TRUEP(callee))
	goto end_loop;
    caller_qm = calling_procedure_invocation(callee);
    procedure = ISVREF(callee,(SI_Long)23L);
    if (EQ(module,get_module_block_is_in(procedure)))
	return VALUES_1(procedure);
    callee = caller_qm;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* FIND-CALLING-PROCEDURE-INVOCATION-IN-MODULE */
Object find_calling_procedure_invocation_in_module(procedure,module)
    Object procedure, module;
{
    Object invocations, scope_conses, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, invocation, procedure_deletion_qm;
    Object ab_less_than_branch_qm_, gensymed_symbol, temp;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,115);
    if (procedure) {
	invocations = ISVREF(procedure,(SI_Long)26L);
	if (invocations) {
	    scope_conses = Scope_conses;
	    ab_hash_table_ = invocations;
	    ab_table_length_ = (SI_Long)0L;
	    ab_index_ = (SI_Long)0L;
	    ab_tree_form_ = Nil;
	    ab_node_stack_ = Nil;
	    ab_current_node_ = Nil;
	    ab_current_alist_ = Nil;
	    ab_entry_cons_ = Nil;
	    ab_skip_list_p_ = Nil;
	    ab_tail_node_ = Nil;
	    invocation = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      procedure_deletion_qm = Nil;
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
	      invocation = M_CDR(ab_entry_cons_);
	      procedure_deletion_qm = 
		      find_procedure_invocation_in_module(invocation,module);
	      if (procedure_deletion_qm) {
		  result = VALUES_1(procedure_deletion_qm);
		  goto end_1;
	      }
	      goto next_loop;
	    end_loop_3:
	      result = VALUES_1(Qnil);
	    end_1:;
	    POP_SPECIAL();
	    return result;
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-PROCEDURE-INVOCATION */
Object cleanup_for_procedure_invocation(procedure_invocation)
    Object procedure_invocation;
{
    Object procedure_invocation_structure, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,116);
    procedure_invocation_structure = ISVREF(procedure_invocation,(SI_Long)20L);
    if (procedure_invocation_structure) {
	ISVREF(procedure_invocation,(SI_Long)20L) = Nil;
	SVREF(procedure_invocation_structure,FIX((SI_Long)27L)) = Nil;
	abort_procedure_invocation(1,procedure_invocation_structure);
    }
    frame = procedure_invocation;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qprocedure_invocation)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_1(method_function_qm,frame);
    else
	return VALUES_1(Nil);
}

/* SET-TRACING-AND-BREAKPOINTS-OF-PROCEDURE-INVOCATION */
Object set_tracing_and_breakpoints_of_procedure_invocation(procedure_invocation,
	    new_tracing_and_breakpoints)
    Object procedure_invocation, new_tracing_and_breakpoints;
{
    x_note_fn_call(160,117);
    reclaim_slot_value(ISVREF(procedure_invocation,(SI_Long)22L));
    return VALUES_1(SVREF(procedure_invocation,FIX((SI_Long)22L)) = 
	    new_tracing_and_breakpoints);
}

/* SET-TRACING-AND-BREAKPOINTS-OF-PROCEDURE-INVOCATIONS */
Object set_tracing_and_breakpoints_of_procedure_invocations(block,
	    new_breakpoints)
    Object block, new_breakpoints;
{
    Object invocations, scope_conses, ab_hash_table_, ab_tree_form_;
    Object ab_node_stack_, ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, invocation, ab_less_than_branch_qm_;
    Object gensymed_symbol, temp;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(160,118);
    invocations = ISVREF(block,(SI_Long)26L);
    if (invocations) {
	scope_conses = Scope_conses;
	ab_hash_table_ = invocations;
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	ab_skip_list_p_ = Nil;
	ab_tail_node_ = Nil;
	invocation = Nil;
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
	  invocation = M_CDR(ab_entry_cons_);
	  set_tracing_and_breakpoints_of_procedure_invocation(invocation,
		  copy_for_slot_value(new_breakpoints));
	  goto next_loop;
	end_loop_3:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* GET-CURRENT-PROCEDURE-INVOCATION-FRAME-IF-ANY */
Object get_current_procedure_invocation_frame_if_any()
{
    Object type_name, procedure_invocation_qm_1;
    char temp;

    x_note_fn_call(160,119);
    if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    procedure_invocation_qm_1 = temp ? ISVREF(Current_computation_instance,
	    (SI_Long)11L) : Nil;
    if (procedure_invocation_qm_1)
	return VALUES_1(ISVREF(procedure_invocation_qm_1,(SI_Long)27L));
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qtruth_value;        /* truth-value */

static Object Qiteration_state;    /* iteration-state */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

static Object string_constant_10;  /* "~NF" */

static Object string_constant_11;  /* "<error printing argument, ~a>" */

/* WRITE-PROCEDURE-ARGUMENT-LIST */
Object write_procedure_argument_list(args)
    Object args;
{
    Object arg, ab_loop_list_, first_time_qm, ab_loop_iter_flag_;
    Object managed_number_or_value, temp, gensymed_symbol, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object x2;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_1;
    Object result;

    x_note_fn_call(160,120);
    arg = Nil;
    ab_loop_list_ = args;
    first_time_qm = T;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    arg = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	first_time_qm = Nil;
    if ( !TRUEP(first_time_qm))
	twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
    if (SIMPLE_VECTOR_P(arg) && EQ(ISVREF(arg,(SI_Long)0L),
	    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) {
	managed_number_or_value = ISVREF(arg,(SI_Long)1L);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(managed_number_or_value) != 
		(SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
		== (SI_Long)1L)
	    temp = aref1(managed_number_or_value,FIX((SI_Long)0L));
	else
	    temp = managed_number_or_value;
	print_constant(2,temp,ISVREF(arg,(SI_Long)2L));
    }
    else {
	gensymed_symbol = arg;
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
	      next_loop_1:
		if (level < ab_loop_bind_)
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_2:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
	      next_loop_3:
		if ( !TRUEP(marked))
		    goto end_loop_2;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_2 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_2,temp);
		MVS_2(result,succ,marked);
		goto next_loop_3;
	      end_loop_2:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    write_evaluation_value(1,arg);
	else {
	    if (SIMPLE_VECTOR_P(arg) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(arg)) > (SI_Long)2L &&  
		    !EQ(ISVREF(arg,(SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(arg,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		tformat(2,string_constant_10,arg);
	    else
		tformat(2,string_constant_11,arg);
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Within_writing_procedure_invocation_p, Qwithin_writing_procedure_invocation_p);

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object Qab_gensym;          /* gensym */

/* WRITE-PROCEDURE-INVOCATION-INSTANCE-FROM-SLOT */
Object write_procedure_invocation_instance_from_slot(invocation,ignored_frame)
    Object invocation, ignored_frame;
{
    Object x2, gensymed_symbol, sub_class_bit_vector;
    Object procedure_invocation_structure_qm;
    Object within_writing_procedure_invocation_p, base_code_body_invocation_qm;
    Object environment_vector_qm, frame_serial_number, procedure;
    Object argument_count, argument, xa, ya, gensym_pop_store, cons_1;
    Object next_cons, temp_1, svref_arg_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, index_1;
    SI_Long ab_loop_bind_;
    char temp;
    Declare_special(1);

    x_note_fn_call(160,121);
    if (SIMPLE_VECTOR_P(invocation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(invocation)) > (SI_Long)2L &&  
	    !EQ(ISVREF(invocation,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(invocation,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Procedure_invocation_class_description,
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
    if (temp)
	procedure_invocation_structure_qm = ISVREF(invocation,(SI_Long)20L);
    else if (SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct))
	procedure_invocation_structure_qm = invocation;
    else
	procedure_invocation_structure_qm = Nil;
    if ( !TRUEP(procedure_invocation_structure_qm) || 
	    memq_function(invocation,Within_writing_procedure_invocation_p))
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)24L));
    else {
	within_writing_procedure_invocation_p = gensym_cons_1(invocation,
		Within_writing_procedure_invocation_p);
	PUSH_SPECIAL_WITH_SYMBOL(Within_writing_procedure_invocation_p,Qwithin_writing_procedure_invocation_p,within_writing_procedure_invocation_p,
		0);
	  base_code_body_invocation_qm = procedure_invocation_structure_qm;
	  environment_vector_qm = base_code_body_invocation_qm ? 
		  ISVREF(base_code_body_invocation_qm,(SI_Long)2L) : Qnil;
	  frame_serial_number = base_code_body_invocation_qm ? 
		  ISVREF(base_code_body_invocation_qm,(SI_Long)9L) : Qnil;
	  procedure = ISVREF(procedure_invocation_structure_qm,(SI_Long)23L);
	  argument_count = var_count(ISVREF(procedure,(SI_Long)24L));
	  denote_component_of_block(3,T,Nil,procedure);
	  twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)1L));
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = IFIX(argument_count);
	  argument = Nil;
	next_loop:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  argument = environment_vector_qm ? ISVREF(environment_vector_qm,
		  index_1) : Qnil;
	  if ( !(index_1 == (SI_Long)0L))
	      twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)2L));
	  temp = SIMPLE_VECTOR_P(argument) ? EQ(ISVREF(argument,
		  (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp);
	  else {
	      if (SIMPLE_VECTOR_P(argument) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(argument)) > 
		      (SI_Long)2L &&  !EQ(ISVREF(argument,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(argument,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp) {
		  gensymed_symbol = ISVREF(argument,(SI_Long)3L);
		  temp = SIMPLE_VECTOR_P(argument) ? EQ(ISVREF(argument,
			  (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = FIXNUMP(gensymed_symbol) ? 
			      IFIX(gensymed_symbol) == (SI_Long)-1L : 
			      TRUEP(Nil);
		  if (temp);
		  else if (FIXNUMP(frame_serial_number))
		      temp = FIXNUMP(gensymed_symbol) ? 
			      FIXNUM_LT(frame_serial_number,
			      gensymed_symbol) : TRUEP(T);
		  else if (FIXNUMP(gensymed_symbol))
		      temp = TRUEP(Nil);
		  else {
		      xa = M_CAR(frame_serial_number);
		      ya = M_CAR(gensymed_symbol);
		      temp = FIXNUM_LT(xa,ya);
		      if (temp);
		      else
			  temp = FIXNUM_EQ(xa,ya) ? 
				  FIXNUM_LT(M_CDR(frame_serial_number),
				  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
		  }
	      }
	      else
		  temp = TRUEP(Nil);
	  }
	  if (temp)
	      write_stored_value(Nil);
	  else
	      write_stored_value(argument);
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop;
	end_loop:;
	  twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)1L));
	  gensym_pop_store = Nil;
	  cons_1 = Within_writing_procedure_invocation_p;
	  if (cons_1) {
	      gensym_pop_store = M_CAR(cons_1);
	      next_cons = M_CDR(cons_1);
	      inline_note_reclaim_cons(cons_1,Qab_gensym);
	      if (ISVREF(Available_gensym_conses_tail_vector,
		      IFIX(Current_thread_index))) {
		  temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			  IFIX(Current_thread_index));
		  M_CDR(temp_1) = cons_1;
		  temp_1 = Available_gensym_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      else {
		  temp_1 = Available_gensym_conses_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
		  temp_1 = Available_gensym_conses_tail_vector;
		  svref_arg_2 = Current_thread_index;
		  SVREF(temp_1,svref_arg_2) = cons_1;
	      }
	      M_CDR(cons_1) = Nil;
	  }
	  else
	      next_cons = Nil;
	  Within_writing_procedure_invocation_p = next_cons;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qexecute_computation_instance;  /* execute-computation-instance */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* ENQUEUE-IMMEDIATE-CODE-BODY-INVOCATION */
Object enqueue_immediate_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    Object immediate_task_schedule_modify_arg_3;
    Object immediate_task_schedule_modify_arg_7, schedule_task_qm;
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(1);

    x_note_fn_call(160,122);
    immediate_task_schedule_modify_arg_3 = 
	    SYMBOL_FUNCTION(Qexecute_computation_instance);
    immediate_task_schedule_modify_arg_7 = code_body_invocation;
    schedule_task_qm = ISVREF(code_body_invocation,(SI_Long)7L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	structure_being_reclaimed = schedule_task_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	  SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = schedule_task_qm;
    }
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
    new_task = def_structure_schedule_task_variable;
    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
    SVREF(new_task,FIX((SI_Long)10L)) = T;
    SVREF(new_task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
    SVREF(new_task,FIX((SI_Long)8L)) = immediate_task_schedule_modify_arg_3;
    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(new_task,FIX((SI_Long)13L)) = immediate_task_schedule_modify_arg_7;
    temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
    SVREF(new_task,FIX((SI_Long)11L)) = temp;
    temp = constant_queue_push_right(ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index)),new_task);
    SVREF(new_task,FIX((SI_Long)6L)) = temp;
    SVREF(code_body_invocation,FIX((SI_Long)7L)) = new_task;
    return VALUES_1(Nil);
}

/* FILO-ENQUEUE-IMMEDIATE-CODE-BODY-INVOCATION */
Object filo_enqueue_immediate_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    Object immediate_task_schedule_modify_arg_3;
    Object immediate_task_schedule_modify_arg_7, schedule_task_qm;
    Object structure_being_reclaimed, temp, svref_arg_2;
    Object def_structure_schedule_task_variable, svref_new_value, new_task;
    Declare_special(1);

    x_note_fn_call(160,123);
    immediate_task_schedule_modify_arg_3 = 
	    SYMBOL_FUNCTION(Qexecute_computation_instance);
    immediate_task_schedule_modify_arg_7 = code_body_invocation;
    schedule_task_qm = ISVREF(code_body_invocation,(SI_Long)7L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	structure_being_reclaimed = schedule_task_qm;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		0);
	  reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	  SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp = ISVREF(Chain_of_available_schedule_tasks_vector,
		IFIX(Current_thread_index));
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_schedule_tasks_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = schedule_task_qm;
    }
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
    new_task = def_structure_schedule_task_variable;
    SVREF(new_task,FIX((SI_Long)4L)) = Higher_than_any_priority;
    SVREF(new_task,FIX((SI_Long)9L)) = Nil;
    SVREF(new_task,FIX((SI_Long)10L)) = T;
    SVREF(new_task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
    SVREF(new_task,FIX((SI_Long)8L)) = immediate_task_schedule_modify_arg_3;
    ISVREF(new_task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(new_task,FIX((SI_Long)13L)) = immediate_task_schedule_modify_arg_7;
    temp = ISVREF(Immediate_task_queue_vector,(SI_Long)0L);
    SVREF(new_task,FIX((SI_Long)11L)) = temp;
    temp = constant_queue_push_left(ISVREF(Immediate_task_queue_vector,
	    IFIX(Current_thread_index)),new_task);
    SVREF(new_task,FIX((SI_Long)6L)) = temp;
    SVREF(code_body_invocation,FIX((SI_Long)7L)) = new_task;
    return VALUES_1(Nil);
}

/* SCHEDULE-COMPUTATION-INSTANCE-EXECUTION */
Object schedule_computation_instance_execution(computation_instance,
	    priority,containing_frame)
    Object computation_instance, priority, containing_frame;
{
    Object type_name, parallel_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(160,124);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	parallel_qm = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct) 
		? T : Nil;
	if (parallel_qm);
	else
	    parallel_qm = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) 
		    ? T : Nil;
    }
    else
	parallel_qm = Nil;
    old = Nil;
    new_1 = Nil;
  next_loop:
    old = ISVREF(computation_instance,(SI_Long)7L);
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
    SVREF(task,FIX((SI_Long)4L)) = priority;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = parallel_qm;
    g2_p =  !((SI_Long)0L != (IFIX(ISVREF(containing_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L));
    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
	    Current_real_time,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    SVREF(task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
    temp = SYMBOL_FUNCTION(Qexecute_computation_instance);
    SVREF(task,FIX((SI_Long)8L)) = temp;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)13L)) = computation_instance;
    new_1 = task;
    if (CAS_SVREF(computation_instance,(SI_Long)7L,old,new_1)) {
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
    return VALUES_1(Nil);
}

/* SCHEDULE-COMPUTATION-INSTANCE-EXECUTION-FOR-BREAKPOINT */
Object schedule_computation_instance_execution_for_breakpoint(computation_instance)
    Object computation_instance;
{
    Object type_name, parallel_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(160,125);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	parallel_qm = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct) 
		? T : Nil;
	if (parallel_qm);
	else
	    parallel_qm = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) 
		    ? T : Nil;
    }
    else
	parallel_qm = Nil;
    old = Nil;
    new_1 = Nil;
  next_loop:
    old = ISVREF(computation_instance,(SI_Long)7L);
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
    temp = Priority_of_current_task;
    SVREF(task,FIX((SI_Long)4L)) = temp;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = parallel_qm;
    g2_p =  !TRUEP(Nil);
    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
	    Current_real_time,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    SVREF(task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
    temp = SYMBOL_FUNCTION(Qexecute_computation_instance);
    SVREF(task,FIX((SI_Long)8L)) = temp;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)13L)) = computation_instance;
    new_1 = task;
    if (CAS_SVREF(computation_instance,(SI_Long)7L,old,new_1)) {
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
    return VALUES_1(Nil);
}

/* SCHEDULE-PUSHED-COMPUTATION-INSTANCE-EXECUTION */
Object schedule_pushed_computation_instance_execution(computation_instance,
	    priority,containing_frame)
    Object computation_instance, priority, containing_frame;
{
    Object type_name, parallel_qm, old, new_1;
    Object def_structure_schedule_task_variable, temp, svref_arg_2;
    Object svref_new_value, task, ctask, p, v, q, structure_being_reclaimed;
    char g2_p;
    double aref_new_value;
    Declare_special(1);

    x_note_fn_call(160,126);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	parallel_qm = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct) 
		? T : Nil;
	if (parallel_qm);
	else
	    parallel_qm = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) 
		    ? T : Nil;
    }
    else
	parallel_qm = Nil;
    old = Nil;
    new_1 = Nil;
  next_loop:
    old = ISVREF(computation_instance,(SI_Long)7L);
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
    SVREF(task,FIX((SI_Long)4L)) = priority;
    SVREF(task,FIX((SI_Long)5L)) = Nil;
    SVREF(task,FIX((SI_Long)9L)) = Nil;
    SVREF(task,FIX((SI_Long)10L)) = parallel_qm;
    g2_p =  !((SI_Long)0L != (IFIX(ISVREF(containing_frame,(SI_Long)4L)) & 
	    (SI_Long)16777216L));
    SVREF(task,FIX((SI_Long)3L)) = g2_p ? T : Nil;
    temp = ISVREF(task,(SI_Long)1L);
    aref_new_value = DFLOAT_ISAREF_1(g2_p ? Current_g2_time : 
	    Current_real_time,(SI_Long)0L);
    DFLOAT_ISASET_1(temp,(SI_Long)0L,aref_new_value);
    SVREF(task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
    temp = SYMBOL_FUNCTION(Qexecute_computation_instance);
    SVREF(task,FIX((SI_Long)8L)) = temp;
    ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
    SVREF(task,FIX((SI_Long)13L)) = computation_instance;
    new_1 = task;
    if (CAS_SVREF(computation_instance,(SI_Long)7L,old,new_1)) {
	task = new_1;
	ctask =  !TRUEP(ISVREF(task,(SI_Long)3L)) ? T : Nil;
	if (ctask);
	else
	    ctask = System_is_running;
	p = ISVREF(task,(SI_Long)4L);
	v = ctask ? Current_task_queue_vector : Deferred_task_queue_vector;
	q = ISVREF(v,IFIX(p));
	SVREF(task,FIX((SI_Long)11L)) = q;
	temp = constant_queue_push_left(q,task);
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
    return VALUES_1(Nil);
}

/* FETCH-AND-ENTER-NEXT-CURRENT-COMPUTATION-INSTANCE */
Object fetch_and_enter_next_current_computation_instance(priority)
    Object priority;
{
    Object time_1, time_slice_expired_qm, fixnum_time_limit_qm;
    Object schedule_task_qm, computation_instance, gensymed_symbol;
    Object structure_being_reclaimed, temp_1, svref_arg_2, temp_2;
    char temp, immediate_task_qm;
    Declare_special(1);

    x_note_fn_call(160,127);
    Current_computation_instance = Nil;
    if (Time_to_check_network_events) {
	temp = TRUEP(g2_event_ready_p());
	if (temp);
	else {
	    Time_to_check_network_events = Nil;
	    temp = TRUEP(Time_to_check_network_events);
	}
    }
    else
	temp = TRUEP(Nil);
    if ( !temp) {
	time_1 = c_native_clock_ticks_or_cache(Nil,Nil);
	time_slice_expired_qm = time_slice_expired_p_given_time(time_1);
	fixnum_time_limit_qm = Nil;
	schedule_task_qm = Nil;
      next_loop:
	schedule_task_qm = 
		next_scheduled_task_for_function(Qexecute_computation_instance,
		time_slice_expired_qm ? Higher_than_any_priority : priority);
	if ( !TRUEP(schedule_task_qm))
	    goto end_loop;
	computation_instance = ISVREF(schedule_task_qm,(SI_Long)13L);
	immediate_task_qm = FIXNUM_EQ(ISVREF(schedule_task_qm,(SI_Long)4L),
		Higher_than_any_priority);
	gensymed_symbol = Nil;
      next_loop_1:
	gensymed_symbol = ISVREF(computation_instance,(SI_Long)7L);
	if (CAS_SVREF(computation_instance,(SI_Long)7L,gensymed_symbol,Nil)) {
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
		temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		SVREF(gensymed_symbol,FIX((SI_Long)0L)) = temp_1;
		temp_1 = Chain_of_available_schedule_tasks_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = gensymed_symbol;
	    }
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
      end_1:;
	if (queue_invocation_for_lock_if_necessary(computation_instance)) {
	    if (Profiling_enabled_qm)
		posit_profiling_structure(computation_instance);
	    fixnum_time_limit_qm = 
		    enter_or_reclaim_computation_instance_context(computation_instance);
	    if (Current_computation_instance) {
		if ( !immediate_task_qm)
		    Cached_fixnum_start_time = time_1;
		temp_2 = fixnum_time_limit_qm;
		goto end_2;
	    }
	}
	goto next_loop;
      end_loop:
	temp_2 = Qnil;
      end_2:;
    }
    else
	temp_2 = Nil;
    return VALUES_1(temp_2);
}

DEFINE_VARIABLE_WITH_SYMBOL(Forgive_long_procedure_instruction_qm, Qforgive_long_procedure_instruction_qm);

static Object string_constant_12;  /* "~a statements may not be executed within simulation procedures." */

/* NOT-A-SIMULATOR-PROCEDURE-INSTRUCTION */
Object not_a_simulator_procedure_instruction(instruction_name_string,
	    top_of_stack)
    Object instruction_name_string, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(160,128);
    top_of_stack_1 = top_of_stack;
    message_1 = tformat_stack_error_text_string(2,string_constant_12,
	    instruction_name_string);
    return raw_stack_error_named_error(top_of_stack_1,message_1);
}

/* PRINT-VAR-SPOT-FOR-STACK */
Object print_var_spot_for_stack varargs_1(int, n)
{
    Object var_spot, environment_description;
    Object var_spot_defined_in_environment_description_qm, var_spot_index;
    Object var_name_qm, var_description_qm, gensymed_symbol_1;
    SI_Long nesting, local_index, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,129);
    INIT_ARGS_nonrelocating();
    var_spot = REQUIRED_ARG_nonrelocating();
    environment_description = REQUIRED_ARG_nonrelocating();
    var_spot_defined_in_environment_description_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    var_spot_index = SECOND(var_spot);
    nesting = IFIX(var_spot_index) >>  -  - (SI_Long)10L;
    local_index = IFIX(var_spot_index) & (SI_Long)1023L;
    var_name_qm = Nil;
    var_description_qm = Nil;
    if ((nesting == (SI_Long)0L || 
	    var_spot_defined_in_environment_description_qm) && 
	    environment_description) {
	gensymed_symbol = local_index * (SI_Long)2L;
	var_name_qm = FIXNUM_LE(ISVREF(environment_description,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(environment_description,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(environment_description,(gensymed_symbol >>  
		-  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	gensymed_symbol = local_index * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(environment_description,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(environment_description,(gensymed_symbol >>  
		-  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description)) {
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    var_description_qm = gensymed_symbol_1;
	}
	else
	    var_description_qm = Nil;
    }
    print_name_of_variable_and_description_1(4,var_name_qm,
	    var_description_qm,FIX(nesting),FIX(local_index));
    return VALUES_1(Nil);
}

/* PRINT-VAR-SPOT-FOR-STACK-USING-NAME-AND-DESCRIPTION */
Object print_var_spot_for_stack_using_name_and_description varargs_1(int, n)
{
    Object var_spot, var_spot_name, var_spot_description;
    Object var_spot_defined_in_environment_description_qm, var_spot_index;
    Object name_qm, description_qm;
    SI_Long nesting, local_index;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,130);
    INIT_ARGS_nonrelocating();
    var_spot = REQUIRED_ARG_nonrelocating();
    var_spot_name = REQUIRED_ARG_nonrelocating();
    var_spot_description = REQUIRED_ARG_nonrelocating();
    var_spot_defined_in_environment_description_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    var_spot_index = SECOND(var_spot);
    nesting = IFIX(var_spot_index) >>  -  - (SI_Long)10L;
    local_index = IFIX(var_spot_index) & (SI_Long)1023L;
    name_qm = Nil;
    description_qm = Nil;
    if (nesting == (SI_Long)0L || 
	    var_spot_defined_in_environment_description_qm) {
	name_qm = var_spot_name;
	description_qm = var_spot_description;
    }
    print_name_of_variable_and_description_1(4,name_qm,description_qm,
	    FIX(nesting),FIX(local_index));
    return VALUES_1(Nil);
}

/* NAMED-VAR-SPOT-P */
Object named_var_spot_p(var_spot,environment_description)
    Object var_spot, environment_description;
{
    Object var_spot_index, gensymed_symbol;
    SI_Long nesting, local_index, gensymed_symbol_1;

    x_note_fn_call(160,131);
    var_spot_index = SECOND(var_spot);
    nesting = IFIX(var_spot_index) >>  -  - (SI_Long)10L;
    local_index = IFIX(var_spot_index) & (SI_Long)1023L;
    if (nesting == (SI_Long)0L) {
	gensymed_symbol = environment_description;
	gensymed_symbol_1 = local_index * (SI_Long)2L;
	return VALUES_1( ! !(gensymed_symbol_1 < 
		IFIX(ISVREF(gensymed_symbol,(SI_Long)1L)) ? 
		(FIXNUM_LE(ISVREF(environment_description,(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		TRUEP(ISVREF(environment_description,gensymed_symbol_1 + 
		IFIX(Managed_array_index_offset))) : 
		TRUEP(ISVREF(ISVREF(environment_description,
		(gensymed_symbol_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol_1 & (SI_Long)1023L))) : TRUEP(Nil)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* PRINT-VAR-SPOT-TYPE-FOR-STACK */
Object print_var_spot_type_for_stack(var_spot,environment_description)
    Object var_spot, environment_description;
{
    Object var_spot_index, gensymed_symbol_1, temp, temp_1;
    SI_Long nesting, local_index, gensymed_symbol;

    x_note_fn_call(160,132);
    var_spot_index = SECOND(var_spot);
    nesting = IFIX(var_spot_index) >>  -  - (SI_Long)10L;
    local_index = IFIX(var_spot_index) & (SI_Long)1023L;
    if (nesting == (SI_Long)0L && environment_description) {
	gensymed_symbol = local_index * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(environment_description,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(environment_description,(gensymed_symbol >>  
		-  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description)) {
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    temp = gensymed_symbol_1;
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    if (nesting == (SI_Long)0L && environment_description) {
	gensymed_symbol = local_index * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(environment_description,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(environment_description,(gensymed_symbol >>  
		-  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description))
	    gensymed_symbol_1 = 
		    getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	temp_1 = gensymed_symbol_1;
    }
    else
	temp_1 = Nil;
    print_type_of_variable_description(temp,temp_1);
    return VALUES_1(Nil);
}

/* PRINT-NAME-OF-VARIABLE-DESCRIPTION */
Object print_name_of_variable_description(variable_description)
    Object variable_description;
{
    x_note_fn_call(160,133);
    return print_name_of_variable_description_1(1,variable_description);
}

static Object Kreturn_value;       /* :return-value */

static Object string_constant_13;  /* "RETURN-VALUE-~a" */

static Object array_constant_4;    /* # */

static Object string_constant_14;  /* "LOCAL-~a" */

static Object string_constant_15;  /* "LOCAL-~a-~a" */

/* PRINT-NAME-OF-VARIABLE-DESCRIPTION-1 */
Object print_name_of_variable_description_1 varargs_1(int, n)
{
    Object variable_description;
    Object nesting_qm, index_qm, name_qm, description_plist, name_was_found_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,134);
    INIT_ARGS_nonrelocating();
    variable_description = REQUIRED_ARG_nonrelocating();
    nesting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    name_qm = CAR(variable_description);
    description_plist = CDR(variable_description);
    name_was_found_qm = T;
    if (name_qm && SYMBOLP(name_qm))
	twrite_symbol(2,name_qm,T);
    else if (CONSP(name_qm) && EQ(CAR(name_qm),Qthe))
	print_designation(name_qm);
    else if (getfq_function_no_default(description_plist,Kreturn_value))
	tformat(2,string_constant_13,
		getfq_function_no_default(description_plist,Kreturn_value));
    else {
	name_was_found_qm = Nil;
	if ( !TRUEP(nesting_qm) ||  !TRUEP(index_qm))
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)7L));
	else if (IFIX(nesting_qm) == (SI_Long)0L)
	    tformat(2,string_constant_14,index_qm);
	else
	    tformat(3,string_constant_15,nesting_qm,index_qm);
    }
    return VALUES_1(name_was_found_qm);
}

/* PRINT-NAME-OF-VARIABLE-AND-DESCRIPTION */
Object print_name_of_variable_and_description(variable_name,
	    variable_description)
    Object variable_name, variable_description;
{
    x_note_fn_call(160,135);
    return print_name_of_variable_and_description_1(2,variable_name,
	    variable_description);
}

/* PRINT-NAME-OF-VARIABLE-AND-DESCRIPTION-1 */
Object print_name_of_variable_and_description_1 varargs_1(int, n)
{
    Object name_qm, variable_description;
    Object nesting_qm, index_qm, name_was_found_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,136);
    INIT_ARGS_nonrelocating();
    name_qm = REQUIRED_ARG_nonrelocating();
    variable_description = REQUIRED_ARG_nonrelocating();
    nesting_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    index_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    name_was_found_qm = T;
    if (name_qm && SYMBOLP(name_qm))
	twrite_symbol(2,name_qm,T);
    else if (CONSP(name_qm) && EQ(CAR(name_qm),Qthe))
	print_designation(name_qm);
    else if (EQ(CAR(variable_description),Kreturn_value))
	tformat(2,string_constant_13,CDR(variable_description));
    else {
	name_was_found_qm = Nil;
	if ( !TRUEP(nesting_qm) ||  !TRUEP(index_qm))
	    twrite_beginning_of_wide_string(array_constant_4,FIX((SI_Long)7L));
	else if (IFIX(nesting_qm) == (SI_Long)0L)
	    tformat(2,string_constant_14,index_qm);
	else
	    tformat(3,string_constant_15,nesting_qm,index_qm);
    }
    return VALUES_1(name_was_found_qm);
}

static Object array_constant_5;    /* # */

static Object string_constant_16;  /* "~NT" */

static Object Qitem_or_datum;      /* item-or-datum */

static Object array_constant_6;    /* # */

/* PRINT-TYPE-OF-VARIABLE-DESCRIPTION */
Object print_type_of_variable_description(description_qm,type_qm)
    Object description_qm, type_qm;
{
    x_note_fn_call(160,137);
    if (getfq_function_no_default(description_qm,Kenvironment))
	return twrite_beginning_of_wide_string(array_constant_5,
		FIX((SI_Long)30L));
    else if (getfq_function_no_default(description_qm,Kreturn_value))
	return tformat(2,string_constant_16,Qitem_or_datum);
    else if (valid_type_specification_p(type_qm))
	return write_type_specification(type_qm);
    else
	return twrite_beginning_of_wide_string(array_constant_6,
		FIX((SI_Long)9L));
}

static Object Qvar_spot;           /* var-spot */

static Object string_constant_17;  /* ";~%" */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

/* WRITE-CODE-BODY-ENVIRONMENT */
Object write_code_body_environment(environment_description,environment_qm)
    Object environment_description, environment_qm;
{
    Object some_printed_qm, var_spot, value;
    SI_Long index_1, ab_loop_repeat_, ab_loop_bind_;

    x_note_fn_call(160,138);
    some_printed_qm = Nil;
    if ( !TRUEP(environment_description));
    else if ( !TRUEP(environment_qm)) {
	var_spot = proc_list_2(Qvar_spot,FIX((SI_Long)0L));
	index_1 = (SI_Long)0L;
	ab_loop_repeat_ = IFIX(var_count(environment_description));
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	M_SECOND(var_spot) = FIX(index_1);
	if (some_printed_qm)
	    tformat(1,string_constant_17);
	some_printed_qm = T;
	twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)2L));
	print_var_spot_for_stack(2,var_spot,environment_description);
	twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
	print_var_spot_type_for_stack(var_spot,environment_description);
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	reclaim_proc_list_1(var_spot);
    }
    else {
	var_spot = proc_list_2(Qvar_spot,FIX((SI_Long)0L));
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(environment_qm));
	ab_loop_repeat_ = IFIX(length(environment_description));
	value = Nil;
      next_loop_1:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop_1;
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop_1;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	value = ISVREF(environment_qm,index_1);
	M_SECOND(var_spot) = FIX(index_1);
	if (named_var_spot_p(var_spot,environment_description)) {
	    if (some_printed_qm)
		tformat(1,string_constant_17);
	    some_printed_qm = T;
	    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)2L));
	    print_var_spot_for_stack(2,var_spot,environment_description);
	    twrite_beginning_of_wide_string(array_constant_8,FIX((SI_Long)2L));
	    print_var_spot_type_for_stack(var_spot,environment_description);
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)3L));
	    write_stored_value(value);
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:
	reclaim_proc_list_1(var_spot);
    }
    if ( !TRUEP(some_printed_qm))
	twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)26L));
    return VALUES_1(Nil);
}

static Object string_constant_18;  /* "~%Stack:" */

static Object string_constant_19;  /* "~%No values on stack" */

static Object string_constant_20;  /* " (top ~a values not shown)" */

static Object string_constant_21;  /* "~%~a = " */

/* WRITE-STACK-CONTENTS */
Object write_stack_contents varargs_1(int, n)
{
    Object stack_qm, top_of_stack_qm;
    Object depth;
    SI_Long index_1, ab_loop_bind_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,139);
    INIT_ARGS_nonrelocating();
    stack_qm = REQUIRED_ARG_nonrelocating();
    top_of_stack_qm = REQUIRED_ARG_nonrelocating();
    depth = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     FIX((SI_Long)20L);
    END_ARGS_nonrelocating();
    if (stack_qm) {
	tformat(1,string_constant_18);
	if (IFIX(top_of_stack_qm) < (SI_Long)0L)
	    return tformat(1,string_constant_19);
	else if (FIXNUM_GT(top_of_stack_qm,depth)) {
	    tformat(2,string_constant_20,FIXNUM_MINUS(top_of_stack_qm,depth));
	    index_1 = IFIX(FIXNUM_MINUS(top_of_stack_qm,depth));
	    ab_loop_bind_ = IFIX(top_of_stack_qm);
	  next_loop:
	    if (index_1 > ab_loop_bind_)
		goto end_loop;
	    tformat(2,string_constant_21,FIX(index_1));
	    write_stored_value(ISVREF(stack_qm,index_1));
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else {
	    index_1 = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(top_of_stack_qm);
	  next_loop_1:
	    if (index_1 > ab_loop_bind_)
		goto end_loop_1;
	    tformat(2,string_constant_21,FIX(index_1));
	    write_stored_value(ISVREF(stack_qm,index_1));
	    index_1 = index_1 + (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_11;   /* # */

static Object string_constant_22;  /* "<DEBUG DATA: ~a>" */

static Object array_constant_12;   /* # */

/* WRITE-STORED-VALUE */
Object write_stored_value(value)
    Object value;
{
    Object x2, gensymed_symbol, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_1, temp_2, entry_hash;
    Object evaluation_value_writing_target_length_qm, managed_number_or_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,140);
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant_11,
		FIX((SI_Long)8L));
    else {
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return tformat(2,string_constant_10,value);
	else {
	    gensymed_symbol = value;
	    temp = FIXNUMP(gensymed_symbol);
	    if (temp);
	    else
		temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			(SI_Long)0L ? 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			== (SI_Long)1L : TRUEP(Qnil);
	    if (temp);
	    else
		temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			TRUEP(Qnil);
	    if (temp);
	    else
		temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			!= (SI_Long)0L;
	    if (temp);
	    else if (CONSP(gensymed_symbol)) {
		gensymed_symbol = M_CDR(gensymed_symbol);
		temp = EQ(gensymed_symbol,Qtruth_value);
		if (temp);
		else
		    temp = EQ(gensymed_symbol,Qiteration_state);
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
		  next_loop:
		    if (level < ab_loop_bind_)
			goto end_loop;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_1:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_2:
		    if ( !TRUEP(marked))
			goto end_loop_1;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
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
		    temp = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? TRUEP(ISVREF(curr,
			    (SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		evaluation_value_writing_target_length_qm = 
			Maximum_length_for_writing_evaluation_values;
		PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
			0);
		  result = write_evaluation_value(1,value);
		POP_SPECIAL();
		return result;
	    }
	    else if (SIMPLE_VECTOR_P(value) && EQ(ISVREF(value,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			{
		evaluation_value_writing_target_length_qm = 
			Maximum_length_for_writing_evaluation_values;
		PUSH_SPECIAL_WITH_SYMBOL(Evaluation_value_writing_target_length_qm,Qevaluation_value_writing_target_length_qm,evaluation_value_writing_target_length_qm,
			0);
		  managed_number_or_value = ISVREF(value,(SI_Long)1L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      temp_2 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      temp_2 = aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else
		      temp_2 = managed_number_or_value;
		  result = print_constant(2,temp_2,ISVREF(value,(SI_Long)2L));
		POP_SPECIAL();
		return result;
	    }
	    else if (Allow_internal_procedure_environment_printing_qm)
		return tformat(2,string_constant_22,value);
	    else
		return twrite_beginning_of_wide_string(array_constant_12,
			FIX((SI_Long)15L));
	}
    }
}

/* WAKE-UP-CODE-BODY-INVOCATION */
Object wake_up_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    Object schedule_task_qm;
    char temp;
    double arg, arg_1;

    x_note_fn_call(160,141);
    clear_event_detectors(code_body_invocation);
    schedule_task_qm = ISVREF(code_body_invocation,(SI_Long)7L);
    if (schedule_task_qm && ISVREF(schedule_task_qm,(SI_Long)6L)) {
	arg = DFLOAT_ISAREF_1(ISVREF(schedule_task_qm,(SI_Long)1L),
		(SI_Long)0L);
	arg_1 = DFLOAT_ISAREF_1(ISVREF(schedule_task_qm,(SI_Long)3L) ? 
		Current_g2_time : Current_real_time,(SI_Long)0L);
	temp = arg <= arg_1 &&  !inline_nanp_for_comparison(arg) ?  
		!inline_nanp_for_comparison(arg_1) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if ( !temp)
	schedule_computation_instance_execution(code_body_invocation,
		ISVREF(code_body_invocation,(SI_Long)10L),
		ISVREF(ISVREF(code_body_invocation,(SI_Long)11L),
		(SI_Long)23L));
    return VALUES_1(Nil);
}

/* WAKE-UP-CODE-BODY-INVOCATION-IMMEDIATELY */
Object wake_up_code_body_invocation_immediately(code_body_invocation)
    Object code_body_invocation;
{
    Object temp;

    x_note_fn_call(160,142);
    clear_event_detectors(code_body_invocation);
    temp = filo_enqueue_immediate_code_body_invocation(code_body_invocation);
    return VALUES_1(temp);
}

/* SIGNAL-WRONG-NUMBER-OF-ARGUMENTS-STACK-ERROR */
Object signal_wrong_number_of_arguments_stack_error(top_of_stack,procedure,
	    arg_restp_index,var_count_1,arg_count)
    Object top_of_stack, procedure, arg_restp_index, var_count_1, arg_count;
{
    Object temp;

    x_note_fn_call(160,143);
    temp = raw_stack_error_named_error(top_of_stack,
	    make_wrong_number_of_arguments_error_text(procedure,
	    arg_restp_index,var_count_1,arg_count));
    return VALUES_1(temp);
}

static Object string_constant_23;  /* "The wrong number of arguments were passed to ~NF from ~NF.  It needs~
				    *      ~a~a argument~a but received ~a."
				    */

static Object string_constant_24;  /* " at least " */

static Object string_constant_25;  /* " " */

/* MAKE-WRONG-NUMBER-OF-ARGUMENTS-ERROR-TEXT */
Object make_wrong_number_of_arguments_error_text(procedure,arg_restp_index,
	    var_count_1,arg_count)
    Object procedure, arg_restp_index, var_count_1, arg_count;
{
    Object temp;

    x_note_fn_call(160,144);
    temp = tformat_stack_error_text_string(7,string_constant_23,procedure,
	    Current_computation_frame,arg_restp_index ? string_constant_24 
	    : string_constant_25,var_count_1,IFIX(var_count_1) == 
	    (SI_Long)1L ? string_constant_5 : string_constant_4,arg_count);
    return VALUES_1(temp);
}

static Object Kall_remaining;      /* :all-remaining */

static Object Qab_class;           /* class */

static Object Qhandle;             /* handle */

static Object Kkind;               /* :kind */

static Object Qfloat_array;        /* float-array */

/* PREPARE-PROCEDURE-ARGUMENT-LIST-FOR-STACK-PROCEDURE */
Object prepare_procedure_argument_list_for_stack_procedure(procedure,
	    local_stack,top_of_arguments_on_stack,argument_count,
	    arguments_known_to_be_correct_p_qm)
    Object procedure, local_stack, top_of_arguments_on_stack, argument_count;
    Object arguments_known_to_be_correct_p_qm;
{
    Object sub_class_bit_vector, local_procedure_qm, method_declaration_qm;
    Object argument_descriptions, generated_argument_list;
    Object argument_restp_index, value, i, gensymed_symbol_3, temp, temp_2;
    Object arg_index, description, stack_value, name, type, ab_loop_iter_flag_;
    Object new_cons, temp_3, temp_4, svref_new_value, x2, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, amf_result, new_float;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, stack_index, ab_loop_bind_;
    char temp_1, logical_qm;
    double aref_new_value;

    x_note_fn_call(160,145);
    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
	local_procedure_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	local_procedure_qm = Nil;
    if (local_procedure_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Method_declaration_class_description,
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
	    method_declaration_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    method_declaration_qm = Nil;
    }
    else
	method_declaration_qm = Nil;
    argument_descriptions = local_procedure_qm ? ISVREF(procedure,
	    (SI_Long)24L) : 
	    remote_procedure_argument_description_function(procedure);
    generated_argument_list = Nil;
    argument_restp_index = Nil;
    value = Nil;
    i = FIXNUM_SUB1(var_count(argument_descriptions));
    if ((SI_Long)0L <= IFIX(i)) {
	gensymed_symbol = IFIX(i) * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_3 = FIXNUM_LE(ISVREF(argument_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(argument_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_3) && EQ(CAR(gensymed_symbol_3),
		Kgeneral_description)) {
	    gensymed_symbol_3 = CDR(gensymed_symbol_3);
	    temp = gensymed_symbol_3;
	}
	else
	    temp = Nil;
	temp_1 = TRUEP(getf(temp,Kall_remaining,_));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	argument_restp_index = i;
    if ( !TRUEP(arguments_known_to_be_correct_p_qm) && 
	    (argument_restp_index ? FIXNUM_LT(argument_count,
	    argument_restp_index) : FIXNUM_NE(argument_count,
	    var_count(argument_descriptions)))) {
	temp = argument_restp_index;
	temp_2 = argument_restp_index;
	if (temp_2);
	else
	    temp_2 = var_count(argument_descriptions);
	signal_wrong_number_of_arguments_stack_error(top_of_arguments_on_stack,
		procedure,temp,temp_2,argument_count);
    }
    stack_index = IFIX(FIXNUM_ADD1(FIXNUM_MINUS(top_of_arguments_on_stack,
	    argument_count)));
    ab_loop_bind_ = IFIX(top_of_arguments_on_stack);
    arg_index = FIX((SI_Long)0L);
    description = Nil;
    stack_value = Nil;
    name = Nil;
    type = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if (stack_index > ab_loop_bind_)
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	arg_index = argument_restp_index && FIXNUM_EQ(arg_index,
		argument_restp_index) ? arg_index : FIXNUM_ADD1(arg_index);
    gensymed_symbol = IFIX(arg_index) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_3 = FIXNUM_LE(ISVREF(argument_descriptions,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(argument_descriptions,gensymed_symbol + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_3) && EQ(CAR(gensymed_symbol_3),
	    Kgeneral_description)) {
	gensymed_symbol_3 = CDR(gensymed_symbol_3);
	description = gensymed_symbol_3;
    }
    else
	description = Nil;
    stack_value = ISVREF(local_stack,stack_index);
    gensymed_symbol = IFIX(arg_index) * (SI_Long)2L;
    name = FIXNUM_LE(ISVREF(argument_descriptions,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(argument_descriptions,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    gensymed_symbol = IFIX(arg_index) * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_3 = FIXNUM_LE(ISVREF(argument_descriptions,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(argument_descriptions,gensymed_symbol + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_3) && EQ(CAR(gensymed_symbol_3),
	    Kgeneral_description))
	gensymed_symbol_3 = 
		getfq_function_no_default(CDR(gensymed_symbol_3),Ktype);
    type = gensymed_symbol_3;
    if (arguments_known_to_be_correct_p_qm || method_declaration_qm) {
	value = stack_value;
	new_cons = ISVREF(Available_eval_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    temp_3 = Available_eval_conses_vector;
	    temp_4 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(temp_3,temp_4) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index)))) {
		temp_3 = Available_eval_conses_tail_vector;
		temp_4 = Current_thread_index;
		SVREF(temp_3,temp_4) = Nil;
	    }
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_eval_cons_pool();
	M_CAR(gensymed_symbol_3) = value;
	M_CDR(gensymed_symbol_3) = generated_argument_list;
	inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	generated_argument_list = gensymed_symbol_3;
    }
    else if (CONSP(type) && EQ(M_CAR(type),Qab_class) || EQ(type,
	    Qitem_or_datum)) {
	value = stack_value;
	temp_1 = EQ(type,Qitem_or_datum);
	if (temp_1);
	else {
	    if (SIMPLE_VECTOR_P(value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(value,(SI_Long)1L),
			Qavailable_frame_vector)) {
		x2 = ISVREF(value,(SI_Long)1L);
		gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if (gensymed_symbol_3) {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(type)),
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		}
		else
		    temp_1 = TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	if (temp_1) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_eval_conses_vector;
		temp_4 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,temp_4) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_eval_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = Nil;
		}
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_3) = value;
	    M_CDR(gensymed_symbol_3) = generated_argument_list;
	    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	    generated_argument_list = gensymed_symbol_3;
	}
	else if (EQ(Qhandle,getfq_function_no_default(description,Kkind)) 
		&& FIXNUMP(value)) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_eval_conses_vector;
		temp_4 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,temp_4) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_eval_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = Nil;
		}
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_3) = value;
	    M_CDR(gensymed_symbol_3) = generated_argument_list;
	    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	    generated_argument_list = gensymed_symbol_3;
	}
	else {
	    reclaim_eval_list_1(generated_argument_list);
	    procedure_argument_list_error(top_of_arguments_on_stack,
		    procedure,name,type,value);
	}
    }
    else {
	if (SIMPLE_VECTOR_P(stack_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(stack_value)) > (SI_Long)2L 
		&&  !EQ(ISVREF(stack_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(stack_value,(SI_Long)1L);
	    gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol_3 = Nil;
	if (gensymed_symbol_3) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    logical_qm = EQ(ISVREF(stack_value,(SI_Long)20L),Qtruth_value);
	    value = ISVREF(stack_value,(SI_Long)23L);
	    if (logical_qm) {
		if (FIXNUM_EQ(value,Truth))
		    value = Evaluation_true_value;
		else if (FIXNUM_EQ(value,Falsity))
		    value = Evaluation_false_value;
		else
		    value = eval_cons_1(value,Qtruth_value);
	    }
	    else
		value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			(SI_Long)0L ? copy_wide_string(value) : 
			FIXNUMP(value) || SYMBOLP(value) ? value : 
			copy_evaluation_value_1(value);
	    ISVREF(local_stack,stack_index) = value;
	}
	else
	    value = stack_value;
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    reclaim_eval_list_1(generated_argument_list);
	    procedure_argument_list_error(top_of_arguments_on_stack,
		    procedure,name,type,value);
	}
	else if (evaluation_value_of_type_p(value,type)) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_eval_conses_vector;
		temp_4 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,temp_4) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_eval_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = Nil;
		}
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_eval_cons_pool();
	    M_CAR(gensymed_symbol_3) = value;
	    M_CDR(gensymed_symbol_3) = generated_argument_list;
	    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	    generated_argument_list = gensymed_symbol_3;
	}
	else if (EQ(type,Qfloat) && FIXNUMP(value)) {
	    new_cons = ISVREF(Available_eval_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		temp_3 = Available_eval_conses_vector;
		temp_4 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(temp_3,temp_4) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_eval_conses_vector,
			IFIX(Current_thread_index)))) {
		    temp_3 = Available_eval_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = Nil;
		}
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_eval_cons_pool();
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp_3 = Vector_of_simple_float_array_pools;
		temp_4 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp_3,FIX((SI_Long)1L)) = temp_4;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
		if (ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_3 = 
			    ISVREF(Available_float_array_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_3) = amf_available_array_cons_qm;
		    temp_3 = Available_float_array_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
		}
		else {
		    temp_3 = Available_float_array_conses_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
		    temp_3 = Available_float_array_conses_tail_vector;
		    temp_4 = Current_thread_index;
		    SVREF(temp_3,temp_4) = amf_available_array_cons_qm;
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
	    aref_new_value = (double)IFIX(value);
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	    M_CAR(gensymed_symbol_3) = new_float;
	    M_CDR(gensymed_symbol_3) = generated_argument_list;
	    inline_note_allocate_cons(gensymed_symbol_3,Qeval);
	    generated_argument_list = gensymed_symbol_3;
	}
	else {
	    reclaim_eval_list_1(generated_argument_list);
	    procedure_argument_list_error(top_of_arguments_on_stack,
		    procedure,name,type,value);
	}
    }
    ab_loop_iter_flag_ = Nil;
    stack_index = stack_index + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return nreverse(generated_argument_list);
}

static Object string_constant_26;  /* "Internal G2 error: bad procedure ~a while preparing arguments." */

static Object string_constant_27;  /* "Attempt to pass an inactive item as argument number ~A to ~
				    *                the procedure ~NF which cannot refer to inactive items."
				    */

/* PREPARE-PROCEDURE-ARGUMENT-LIST-IN-PLACE-FOR-STACK-PROCEDURE */
Object prepare_procedure_argument_list_in_place_for_stack_procedure(procedure,
	    local_stack,top_of_arguments_on_stack,argument_count,
	    arguments_known_to_be_correct_p_qm)
    Object procedure, local_stack, top_of_arguments_on_stack, argument_count;
    Object arguments_known_to_be_correct_p_qm;
{
    Object sub_class_bit_vector, argument_descriptions, last_index;
    Object gensymed_symbol_3, temp_1, formal_arg_restp_index;
    Object switching_role_service_types_qm, current_computation_flags;
    Object bottom_of_arguments_on_stack, value, x2, inactive_item_index;
    Object arg_index, type, ab_loop_iter_flag_, gensymed_symbol_4;
    Object amf_available_array_cons_qm, amf_array, temp_2, temp_3, amf_result;
    Object new_float, name;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, stack_index, ab_loop_bind_;
    char temp, logical_qm;
    double aref_new_value;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,146);
    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
    if ( !temp) {
	result = tformat_stack_error_text_string(2,string_constant_26,
		procedure);
	goto end_prepare_procedure_argument_list_in_place_for_stack_procedure;
    }
    argument_descriptions = ISVREF(procedure,(SI_Long)24L);
    last_index = FIXNUM_SUB1(var_count(argument_descriptions));
    if ((SI_Long)0L <= IFIX(last_index)) {
	gensymed_symbol = IFIX(last_index) * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_3 = FIXNUM_LE(ISVREF(argument_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(argument_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_3) && EQ(CAR(gensymed_symbol_3),
		Kgeneral_description)) {
	    gensymed_symbol_3 = CDR(gensymed_symbol_3);
	    temp_1 = gensymed_symbol_3;
	}
	else
	    temp_1 = Nil;
	temp = TRUEP(getf(temp_1,Kall_remaining,_));
    }
    else
	temp = TRUEP(Nil);
    formal_arg_restp_index = temp ? last_index : Nil;
    if ( !TRUEP(arguments_known_to_be_correct_p_qm) && 
	    (formal_arg_restp_index ? FIXNUM_LT(argument_count,
	    formal_arg_restp_index) : FIXNUM_NE(argument_count,
	    var_count(argument_descriptions)))) {
	temp_1 = formal_arg_restp_index;
	if (temp_1);
	else
	    temp_1 = var_count(argument_descriptions);
	result = make_wrong_number_of_arguments_error_text(procedure,
		formal_arg_restp_index,temp_1,argument_count);
	goto end_prepare_procedure_argument_list_in_place_for_stack_procedure;
    }
    switching_role_service_types_qm = (IFIX(Current_computation_flags) & 
	    (SI_Long)16L) != (SI_Long)0L ? ( !((SI_Long)0L != 
	    (IFIX(ISVREF(procedure,(SI_Long)4L)) & (SI_Long)33554432L)) ? 
	    T : Nil) : Qnil;
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      if (switching_role_service_types_qm)
	  Current_computation_flags = FIX(IFIX(Current_computation_flags) 
		  &  ~(SI_Long)16L);
      bottom_of_arguments_on_stack = 
	      FIXNUM_ADD1(FIXNUM_MINUS(top_of_arguments_on_stack,
	      argument_count));
      if (switching_role_service_types_qm) {
	  stack_index = IFIX(bottom_of_arguments_on_stack);
	  ab_loop_bind_ = IFIX(top_of_arguments_on_stack);
	  value = Nil;
	next_loop:
	  if (stack_index > ab_loop_bind_)
	      goto end_loop;
	  value = ISVREF(local_stack,stack_index);
	  if (SIMPLE_VECTOR_P(value) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		  !EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	      x2 = ISVREF(value,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp ?  !TRUEP(serve_item_p(value)) : TRUEP(Nil)) {
	      inactive_item_index = FIX(stack_index - 
		      IFIX(bottom_of_arguments_on_stack) + (SI_Long)1L);
	      goto end_1;
	  }
	  stack_index = stack_index + (SI_Long)1L;
	  goto next_loop;
	end_loop:
	  inactive_item_index = Qnil;
	end_1:;
      }
      else
	  inactive_item_index = Nil;
      if (inactive_item_index) {
	  result = tformat_stack_error_text_string(3,string_constant_27,
		  inactive_item_index,procedure);
	  POP_SPECIAL();
	  goto end_prepare_procedure_argument_list_in_place_for_stack_procedure;
      }
      temp = TRUEP(arguments_known_to_be_correct_p_qm);
      if (temp);
      else {
	  sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		  (SI_Long)19L);
	  superior_class_bit_number = 
		  IFIX(ISVREF(Method_declaration_class_description,
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
      if ( !temp) {
	  stack_index = IFIX(bottom_of_arguments_on_stack);
	  ab_loop_bind_ = IFIX(top_of_arguments_on_stack);
	  value = Nil;
	  arg_index = FIX((SI_Long)0L);
	  type = Nil;
	  ab_loop_iter_flag_ = T;
	next_loop_1:
	  if (stack_index > ab_loop_bind_)
	      goto end_loop_1;
	  value = ISVREF(local_stack,stack_index);
	  if ( !TRUEP(ab_loop_iter_flag_))
	      arg_index = formal_arg_restp_index && FIXNUM_EQ(arg_index,
		      formal_arg_restp_index) ? arg_index : 
		      FIXNUM_ADD1(arg_index);
	  gensymed_symbol = IFIX(arg_index) * (SI_Long)2L + (SI_Long)1L;
	  gensymed_symbol_3 = FIXNUM_LE(ISVREF(argument_descriptions,
		  (SI_Long)1L),Maximum_in_place_array_size) ? 
		  ISVREF(argument_descriptions,gensymed_symbol + 
		  IFIX(Managed_array_index_offset)) : 
		  ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  
		  -  - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		  (SI_Long)1023L);
	  if (CONSP(gensymed_symbol_3) && EQ(CAR(gensymed_symbol_3),
		  Kgeneral_description))
	      gensymed_symbol_3 = 
		      getfq_function_no_default(CDR(gensymed_symbol_3),Ktype);
	  type = gensymed_symbol_3;
	  if (EQ(type,Qitem_or_datum))
	      temp_1 = T;
	  else if (CONSP(type) && EQ(M_CAR(type),Qab_class)) {
	      if (SIMPLE_VECTOR_P(value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(value,(SI_Long)1L);
		  gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol_3 = Nil;
	      if (gensymed_symbol_3) {
		  gensymed_symbol_4 = 
			  lookup_global_or_kb_specific_property_value(M_CAR(M_CDR(type)),
			  Class_description_gkbprop);
		  if (gensymed_symbol_4) {
		      sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			      (SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp_1 = (SI_Long)0L < gensymed_symbol ? T : Nil;
		      }
		      else
			  temp_1 = Nil;
		  }
		  else
		      temp_1 = Nil;
	      }
	      else
		  temp_1 = Nil;
	  }
	  else {
	      if (SIMPLE_VECTOR_P(value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(value,(SI_Long)1L);
		  gensymed_symbol_3 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? x2 : Qnil;
	      }
	      else
		  gensymed_symbol_3 = Nil;
	      if (gensymed_symbol_3) {
		  sub_class_bit_vector = ISVREF(gensymed_symbol_3,
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Parameter_class_description,
			  (SI_Long)18L));
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
	      if (temp) {
		  logical_qm = EQ(ISVREF(value,(SI_Long)20L),Qtruth_value);
		  value = ISVREF(value,(SI_Long)23L);
		  if (logical_qm) {
		      if (FIXNUM_EQ(value,Truth))
			  value = Evaluation_true_value;
		      else if (FIXNUM_EQ(value,Falsity))
			  value = Evaluation_false_value;
		      else
			  value = eval_cons_1(value,Qtruth_value);
		  }
		  else
		      value = INLINE_UNSIGNED_BYTE_16_VECTOR_P(value) != 
			      (SI_Long)0L ? copy_wide_string(value) : 
			      FIXNUMP(value) || SYMBOLP(value) ? value : 
			      copy_evaluation_value_1(value);
		  ISVREF(local_stack,stack_index) = value;
	      }
	      if (SIMPLE_VECTOR_P(value) && 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L 
		      &&  !EQ(ISVREF(value,(SI_Long)1L),
		      Qavailable_frame_vector)) {
		  x2 = ISVREF(value,(SI_Long)1L);
		  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			  Qg2_defstruct_structure_name_class_description_g2_struct) 
			  ? TRUEP(x2) : TRUEP(Qnil);
	      }
	      else
		  temp = TRUEP(Nil);
	      if (temp)
		  temp_1 = Nil;
	      else if (evaluation_value_of_type_p(value,type))
		  temp_1 = T;
	      else if (EQ(type,Qfloat) && FIXNUMP(value)) {
		  amf_available_array_cons_qm = 
			  ISVREF(Vector_of_simple_float_array_pools,
			  (SI_Long)1L);
		  if (amf_available_array_cons_qm) {
		      amf_array = M_CAR(amf_available_array_cons_qm);
		      temp_2 = Vector_of_simple_float_array_pools;
		      temp_3 = M_CDR(amf_available_array_cons_qm);
		      SVREF(temp_2,FIX((SI_Long)1L)) = temp_3;
		      inline_note_reclaim_cons(amf_available_array_cons_qm,
			      Qfloat_array);
		      if (ISVREF(Available_float_array_conses_tail_vector,
			      IFIX(Current_thread_index))) {
			  temp_2 = 
				  ISVREF(Available_float_array_conses_tail_vector,
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
		  aref_new_value = (double)IFIX(value);
		  DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		  ISVREF(local_stack,stack_index) = new_float;
		  temp_1 = T;
	      }
	      else
		  temp_1 = Nil;
	  }
	  if ( !TRUEP(temp_1)) {
	      gensymed_symbol = IFIX(arg_index) * (SI_Long)2L;
	      name = FIXNUM_LE(ISVREF(argument_descriptions,(SI_Long)1L),
		      Maximum_in_place_array_size) ? 
		      ISVREF(argument_descriptions,gensymed_symbol + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(argument_descriptions,(gensymed_symbol 
		      >>  -  - (SI_Long)10L) + (SI_Long)2L),
		      gensymed_symbol & (SI_Long)1023L);
	      result = make_procedure_argument_list_error_text(procedure,
		      name,type,value);
	      POP_SPECIAL();
	      goto end_prepare_procedure_argument_list_in_place_for_stack_procedure;
	  }
	  ab_loop_iter_flag_ = Nil;
	  stack_index = stack_index + (SI_Long)1L;
	  goto next_loop_1;
	end_loop_1:;
      }
    POP_SPECIAL();
    result = VALUES_1(Nil);
  end_prepare_procedure_argument_list_in_place_for_stack_procedure:
    return result;
}

/* PROCEDURE-ARGUMENT-LIST-ERROR */
Object procedure_argument_list_error(top_of_arguments_on_stack,procedure,
	    name,type,value)
    Object top_of_arguments_on_stack, procedure, name, type, value;
{
    x_note_fn_call(160,147);
    return raw_stack_error_named_error(top_of_arguments_on_stack,
	    make_procedure_argument_list_error_text(procedure,name,type,
	    value));
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object array_constant_13;   /* # */

static Object string_constant_28;  /* " argument of ~NF is declared to take values of type ~
				    *        ~NT, but instead it received "
				    */

static Object string_constant_29;  /* "~NF, an instance of the class ~a." */

static Object Qdatum;              /* datum */

static Object string_constant_30;  /* "  Note that if you intended to pass the value of this variable, you ~
				    *          must use a COLLECT DATA statement to fetch its value."
				    */

/* MAKE-PROCEDURE-ARGUMENT-LIST-ERROR-TEXT */
Object make_procedure_argument_list_error_text(procedure,name,type,value)
    Object procedure, name, type, value;
{
    Object text_string, snapshots, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_special(7);

    x_note_fn_call(160,148);
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
		  twrite_beginning_of_wide_string(array_constant_13,
			  FIX((SI_Long)4L));
		  print_name_of_variable_and_description(name,type);
		  tformat(3,string_constant_28,procedure,type);
		  if (SIMPLE_VECTOR_P(value) && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			  (SI_Long)2L &&  !EQ(ISVREF(value,(SI_Long)1L),
			  Qavailable_frame_vector)) {
		      x2 = ISVREF(value,(SI_Long)1L);
		      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			      (SI_Long)0L),
			      Qg2_defstruct_structure_name_class_description_g2_struct) 
			      ? TRUEP(x2) : TRUEP(Qnil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      tformat(3,string_constant_29,value,
			      ISVREF(ISVREF(value,(SI_Long)1L),(SI_Long)1L));
		  else {
		      write_stored_value(value);
		      twrite_character(FIX((SI_Long)46L));
		  }
		  if (type_specification_subtype_p(type,Qdatum)) {
		      if (SIMPLE_VECTOR_P(value) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(value,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(value,(SI_Long)1L);
			  gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
				  EQ(ISVREF(x2,(SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? x2 : Qnil;
		      }
		      else
			  gensymed_symbol = Nil;
		      if (gensymed_symbol) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Variable_class_description,
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
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_2 = gensymed_symbol_2 << 
				      gensymed_symbol_3;
			      gensymed_symbol_1 = gensymed_symbol_1 & 
				      gensymed_symbol_2;
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
		      tformat(1,string_constant_30);
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

static Object string_constant_31;  /* "~NA requires ~a argument~a and received ~a." */

static Object string_constant_32;  /* " argument of ~NA is declared to take values of type ~
				    *                    ~a, but this procedure received a bad value instead."
				    */

static Object Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct;  /* g2-defstruct-structure-name::receiving-resumable-object-g2-struct */

static Object Qunsigned_vector_16;  /* unsigned-vector-16 */

static Object string_constant_33;  /* " argument of ~NA is declared to take values of type ~
				    *                         ~NT, but it received NO-VALUE."
				    */

static Object list_constant;       /* # */

static Object string_constant_34;  /* " argument of ~NA is declared to take values of type ~
				    *                         ~NT, but it received ~NF, ~
				    *                         an instance of the class ~a."
				    */

static Object Qlong;               /* long */

static Object list_constant_1;     /* # */

static Object string_constant_35;  /* " argument of ~NA is declared to take values ~
				    *                         of type ~NT, but it received "
				    */

static Object array_constant_14;   /* # */

static Object string_constant_36;  /* " argument of ~NA is declared to take instances  ~
				    *                          of the class ~a, but it received the value "
				    */

static Object string_constant_37;  /* " argument of ~NF is declared to take instances of the ~
				    *                       class ~a, but it received ~NF, ~
				    *                       an instance of the class ~a."
				    */

/* GET-PROCEDURE-ARGUMENT-LIST-ERROR-IF-ANY */
Object get_procedure_argument_list_error_if_any(procedure,argument_list,
	    icp_socket)
    Object procedure, argument_list, icp_socket;
{
    Object system_rpc_p, argument_descriptions, arg_count;
    Object procedure_or_procedure_name, temp, temp_1, temp_2, arg_name, type;
    Object argument_qm, ab_loop_list_, argument_cons, ab_loop_iter_flag_;
    Object gensymed_symbol_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object skip_list, key_value, marked, pred, curr, succ, reference;
    Object entry_hash, type1, type2, handled_object_qm, frame, symbol;
    Object sub_class_bit_vector;
    SI_Long index_1, ab_loop_bind_, gensymed_symbol, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind__1, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(160,149);
    system_rpc_p = SIMPLE_VECTOR_P(procedure) ? (EQ(ISVREF(procedure,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_system_rpc_g2_struct) ? T : Nil) :
	     Qnil;
    argument_descriptions = Nil;
    arg_count = Nil;
    procedure_or_procedure_name = Nil;
    if (system_rpc_p) {
	argument_descriptions = ISVREF(procedure,(SI_Long)2L);
	procedure_or_procedure_name = ISVREF(procedure,(SI_Long)1L);
    }
    else {
	argument_descriptions = ISVREF(procedure,(SI_Long)24L);
	procedure_or_procedure_name = procedure;
    }
    arg_count = var_count(argument_descriptions);
    if (FIXNUM_NE(arg_count,length(argument_list))) {
	temp = procedure_or_procedure_name;
	temp_1 = var_count(argument_descriptions);
	temp_2 = IFIX(var_count(argument_descriptions)) == (SI_Long)1L ? 
		string_constant_5 : string_constant_4;
	return tformat_text_string(5,string_constant_31,temp,temp_1,temp_2,
		length(argument_list));
    }
    else {
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(arg_count);
	arg_name = Nil;
	type = Nil;
	argument_qm = Nil;
	ab_loop_list_ = argument_list;
	argument_cons = argument_list;
	ab_loop_iter_flag_ = T;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = index_1 * (SI_Long)2L;
	arg_name = FIXNUM_LE(ISVREF(argument_descriptions,(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(argument_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(argument_descriptions,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		ISVREF(argument_descriptions,gensymed_symbol + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(argument_descriptions,(gensymed_symbol >>  - 
		 - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		(SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description))
	    gensymed_symbol_1 = 
		    getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	type = gensymed_symbol_1;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument_qm = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    argument_cons = M_CDR(argument_cons);
	if ( !TRUEP(argument_cons))
	    goto end_loop;
	if ( !(system_rpc_p || argument_qm)) {
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
		      twrite_beginning_of_wide_string(array_constant_13,
			      FIX((SI_Long)4L));
		      print_name_of_variable_and_description(arg_name,type);
		      tformat(3,string_constant_32,
			      procedure_or_procedure_name,type);
		      result = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	if ( !(SIMPLE_VECTOR_P(argument_qm) && EQ(ISVREF(argument_qm,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct))) 
		    {
	    if (CONSP(argument_qm) && EQ(M_CDR(argument_qm),
		    Qunsigned_vector_16)) {
		temp_2 = M_CAR(argument_qm);
		reclaim_eval_cons_1(argument_qm);
		argument_qm = temp_2;
		M_CAR(argument_cons) = argument_qm;
	    }
	    if ( !TRUEP(argument_qm)) {
		if ( !TRUEP(type_specification_type_p(argument_qm,type))) {
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
			      twrite_beginning_of_wide_string(array_constant_13,
				      FIX((SI_Long)4L));
			      print_name_of_variable_and_description(arg_name,
				      type);
			      tformat(3,string_constant_33,
				      procedure_or_procedure_name,type);
			      result = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    return result;
		}
	    }
	    else if (system_rpc_p ? valid_type_specification_p(type) && 
		    type_specification_subtype_in_kb_p(type,list_constant) 
		    : TRUEP(valid_datum_type_specification_p(type))) {
		gensymed_symbol_1 = argument_qm;
		temp_3 = FIXNUMP(gensymed_symbol_1);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = INLINE_LONG_VECTOR_P(gensymed_symbol_1) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = gensymed_symbol_1 ? 
			    SYMBOLP(gensymed_symbol_1) : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
			    != (SI_Long)0L;
		if (temp_3);
		else if (CONSP(gensymed_symbol_1)) {
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    temp_3 = EQ(gensymed_symbol_1,Qtruth_value);
		    if (temp_3);
		    else
			temp_3 = EQ(gensymed_symbol_1,Qiteration_state);
		    if (temp_3);
		    else if (SYMBOLP(gensymed_symbol_1)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol_1;
			key_hash_value = 
				SXHASH_SYMBOL_1(gensymed_symbol_1) & 
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
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_3:
			if ( !TRUEP(marked))
			    goto end_loop_2;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
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
			temp_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		if ( !temp_3) {
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
			      twrite_beginning_of_wide_string(array_constant_13,
				      FIX((SI_Long)4L));
			      print_name_of_variable_and_description(arg_name,
				      type);
			      tformat(5,string_constant_34,
				      procedure_or_procedure_name,type,
				      argument_qm,
				      ISVREF(ISVREF(argument_qm,
				      (SI_Long)1L),(SI_Long)1L));
			      result = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    return result;
		}
		type1 = type;
		type2 = evaluation_value_type(argument_qm);
		temp_3 = EQ(type1,type2);
		if (temp_3);
		else
		    temp_3 = EQ(type1,Qnumber) ? EQ(type2,Qnumber) || 
			    EQ(type2,Qinteger) || EQ(type2,Qfloat) || 
			    EQ(type2,Qlong) || 
			    lookup_global_or_kb_specific_property_value(type2,
			    Numeric_data_type_gkbprop) : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = EQ(type2,Qnumber) ? EQ(type1,Qnumber) || 
			    EQ(type1,Qinteger) || EQ(type1,Qfloat) || 
			    EQ(type1,Qlong) || 
			    lookup_global_or_kb_specific_property_value(type1,
			    Numeric_data_type_gkbprop) : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = EQ(type1,Qinteger) || memq_function(type1,
			    list_constant_1) ? EQ(type2,Qinteger) || 
			    memq_function(type2,list_constant_1) : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = 
			    TRUEP(type_specification_subtype_p(evaluation_value_type(argument_qm),
			    type));
		if ( !temp_3) {
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
			      twrite_beginning_of_wide_string(array_constant_13,
				      FIX((SI_Long)4L));
			      print_name_of_variable_and_description(arg_name,
				      type);
			      tformat(3,string_constant_35,
				      procedure_or_procedure_name,type);
			      write_evaluation_value(1,argument_qm);
			      twrite_beginning_of_wide_string(array_constant_14,
				      FIX((SI_Long)1L));
			      result = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    return result;
		}
	    }
	    else if (EQ(type,Qitem_or_datum));
	    else {
		gensymed_symbol_1 = argument_qm;
		temp_3 = FIXNUMP(gensymed_symbol_1);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol_1) 
			    != (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = INLINE_LONG_VECTOR_P(gensymed_symbol_1) != 
			    (SI_Long)0L ? 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol_1)) 
			    == (SI_Long)1L : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = gensymed_symbol_1 ? 
			    SYMBOLP(gensymed_symbol_1) : TRUEP(Qnil);
		if (temp_3);
		else
		    temp_3 = 
			    INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol_1) 
			    != (SI_Long)0L;
		if (temp_3);
		else if (CONSP(gensymed_symbol_1)) {
		    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
		    temp_3 = EQ(gensymed_symbol_1,Qtruth_value);
		    if (temp_3);
		    else
			temp_3 = EQ(gensymed_symbol_1,Qiteration_state);
		    if (temp_3);
		    else if (SYMBOLP(gensymed_symbol_1)) {
			skip_list = CDR(Defined_evaluation_value_types);
			key_value = gensymed_symbol_1;
			key_hash_value = 
				SXHASH_SYMBOL_1(gensymed_symbol_1) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind__1 = bottom_level;
		      next_loop_4:
			if (level < ab_loop_bind__1)
			    goto end_loop_4;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_5:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
		      next_loop_6:
			if ( !TRUEP(marked))
			    goto end_loop_5;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp_2 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp_2);
			MVS_2(result,succ,marked);
			goto next_loop_6;
		      end_loop_5:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
			temp_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? TRUEP(ISVREF(curr,
				(SI_Long)3L)) : TRUEP(Nil)) : TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		if (temp_3) {
		    if (class_type_specification_p(type)) {
			if (FIXNUMP(argument_qm))
			    handled_object_qm = 
				    get_item_from_local_handle(argument_qm,
				    icp_socket);
			else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(argument_qm) 
				!= (SI_Long)0L)
			    handled_object_qm = the_item_having_uuid(Nil,
				    argument_qm);
			else
			    handled_object_qm = Nil;
			if (handled_object_qm) {
			    frame = handled_object_qm;
			    symbol = M_CAR(M_CDR(type));
			    gensymed_symbol_1 = 
				    lookup_global_or_kb_specific_property_value(symbol,
				    Class_description_gkbprop);
			    if (gensymed_symbol_1) {
				sub_class_bit_vector = ISVREF(ISVREF(frame,
					(SI_Long)1L),(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(gensymed_symbol_1,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol = gensymed_symbol & 
					    gensymed_symbol_2;
				    temp_3 = (SI_Long)0L < gensymed_symbol;
				}
				else
				    temp_3 = TRUEP(Nil);
			    }
			    else
				temp_3 = TRUEP(Nil);
			}
			else
			    temp_3 = TRUEP(Nil);
			if (temp_3) {
			    reclaim_evaluation_value(argument_qm);
			    M_CAR(argument_cons) = handled_object_qm;
			    goto end_transform_handled_object_if_possible;
			}
		    }
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
			      twrite_beginning_of_wide_string(array_constant_13,
				      FIX((SI_Long)4L));
			      print_name_of_variable_and_description(arg_name,
				      type);
			      tformat(3,string_constant_36,
				      procedure_or_procedure_name,
				      M_CAR(M_CDR(type)));
			      write_evaluation_value(1,argument_qm);
			      twrite_beginning_of_wide_string(array_constant_14,
				      FIX((SI_Long)1L));
			      result = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    return result;
		  end_transform_handled_object_if_possible:;
		}
		else {
		    frame = argument_qm;
		    symbol = M_CAR(M_CDR(type));
		    gensymed_symbol_1 = 
			    lookup_global_or_kb_specific_property_value(symbol,
			    Class_description_gkbprop);
		    if (gensymed_symbol_1) {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_1,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_2;
			    temp_3 = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp_3 = TRUEP(Nil);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if ( !temp_3) {
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
				  twrite_beginning_of_wide_string(array_constant_13,
					  FIX((SI_Long)4L));
				  print_name_of_variable_and_description(arg_name,
					  type);
				  tformat(5,string_constant_37,procedure,
					  M_CAR(M_CDR(type)),argument_qm,
					  ISVREF(ISVREF(argument_qm,
					  (SI_Long)1L),(SI_Long)1L));
				  result = copy_out_current_wide_string();
				POP_SPECIAL();
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
			return result;
		    }
		}
	    }
	}
	ab_loop_iter_flag_ = Nil;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

/* RECLAIM-LISP-CALL-ARGUMENT-LIST */
Object reclaim_lisp_call_argument_list(argument_list)
    Object argument_list;
{
    Object arg_trailer, argument_cons, argument, eval_cons, temp, svref_arg_2;

    x_note_fn_call(160,150);
    if (argument_list) {
	arg_trailer = Nil;
	argument_cons = argument_list;
	argument = Nil;
      next_loop:
	if ( !TRUEP(argument_cons))
	    goto end_loop;
	argument = M_CAR(argument_cons);
	if ( !(FIXNUMP(argument) || SYMBOLP(argument) || 
		SIMPLE_VECTOR_P(argument)))
	    reclaim_if_evaluation_value_1(argument);
	arg_trailer = argument_cons;
	argument_cons = M_CDR(argument_cons);
	goto next_loop;
      end_loop:
	if (argument_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	    eval_cons = argument_list;
	  next_loop_1:
	    inline_note_reclaim_cons(eval_cons,Qeval);
	    if (EQ(eval_cons,arg_trailer))
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
	    M_CDR(temp) = argument_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = arg_trailer;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = argument_list;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = arg_trailer;
	}
	M_CDR(arg_trailer) = Nil;
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object Top_level_procedure_invocations_array = UNBOUND;

Object Minimum_available_procedure_invocation_index = UNBOUND;

Object Procedure_invocations_lock = UNBOUND;

/* REGISTER-TOP-LEVEL-PROCEDURE-INVOCATION-1 */
Object register_top_level_procedure_invocation_1(procedure_invocation)
    Object procedure_invocation;
{
    Object top_array, svref_arg_1;
    SI_Long length_1, min_index, index_1, svref_arg_2;

    x_note_fn_call(160,151);
    top_array = Top_level_procedure_invocations_array;
    length_1 = IFIX(ISVREF(top_array,(SI_Long)1L));
    min_index = IFIX(Minimum_available_procedure_invocation_index);
    index_1 = min_index;
    min_index = min_index + (SI_Long)1L;
    if (length_1 == index_1) {
	top_array = adjust_managed_array(2,top_array,FIX(min_index));
	Top_level_procedure_invocations_array = top_array;
    }
    else {
      next_loop:
	if ( !(min_index < length_1 && (FIXNUM_LE(ISVREF(top_array,
		(SI_Long)1L),Maximum_in_place_array_size) ? 
		TRUEP(ISVREF(top_array,min_index + 
		IFIX(Managed_array_index_offset))) : 
		TRUEP(ISVREF(ISVREF(top_array,(min_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),min_index & (SI_Long)1023L)))))
	    goto end_loop;
	min_index = min_index + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    Minimum_available_procedure_invocation_index = FIX(min_index);
    if (FIXNUM_LE(ISVREF(top_array,(SI_Long)1L),Maximum_in_place_array_size)) {
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(top_array,svref_arg_2) = procedure_invocation;
    }
    else {
	svref_arg_1 = ISVREF(top_array,(index_1 >>  -  - (SI_Long)10L) + 
		(SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = procedure_invocation;
    }
    ISVREF(procedure_invocation,(SI_Long)24L) = FIX(index_1);
    return VALUES_1(Nil);
}

/* DEREGISTER-TOP-LEVEL-PROCEDURE-INVOCATION-1 */
Object deregister_top_level_procedure_invocation_1(procedure_invocation)
    Object procedure_invocation;
{
    Object svref_arg_1;
    SI_Long index_1, svref_arg_2;

    x_note_fn_call(160,152);
    index_1 = IFIX(ISVREF(procedure_invocation,(SI_Long)24L));
    if (index_1 < IFIX(Minimum_available_procedure_invocation_index))
	Minimum_available_procedure_invocation_index = FIX(index_1);
    if (FIXNUM_LE(ISVREF(Top_level_procedure_invocations_array,
	    (SI_Long)1L),Maximum_in_place_array_size)) {
	svref_arg_1 = Top_level_procedure_invocations_array;
	svref_arg_2 = index_1 + IFIX(Managed_array_index_offset);
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    else {
	svref_arg_1 = ISVREF(Top_level_procedure_invocations_array,
		(index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = index_1 & (SI_Long)1023L;
	ISVREF(svref_arg_1,svref_arg_2) = Nil;
    }
    return VALUES_1(Nil);
}

/* INSTALL-PROCEDURE-INVOCATION-COMPLETION-FORM-FUNCTION */
Object install_procedure_invocation_completion_form_function(procedure_invocation,
	    completion_form)
    Object procedure_invocation, completion_form;
{
    x_note_fn_call(160,153);
    return VALUES_1(SVREF(procedure_invocation,FIX((SI_Long)26L)) = 
	    completion_form);
}

/* INSTALL-CODE-BODY-INVOCATION-COMPLETION-FORM */
Object install_code_body_invocation_completion_form(code_body_invocation,
	    completion_form)
    Object code_body_invocation, completion_form;
{
    Object procedure_invocation;

    x_note_fn_call(160,154);
    procedure_invocation = ISVREF(code_body_invocation,(SI_Long)11L);
    return VALUES_1(SVREF(procedure_invocation,FIX((SI_Long)26L)) = 
	    completion_form);
}

static Object Kerror_string;       /* :error-string */

/* GENERATE-PROCEDURE-INVOCATION-ERROR */
Object generate_procedure_invocation_error varargs_1(int, n)
{
    Object top_of_stack_qm, format_string;
    Object arg1, arg2, arg3;
    Declare_varargs_nonrelocating;

    x_note_fn_call(160,155);
    INIT_ARGS_nonrelocating();
    top_of_stack_qm = REQUIRED_ARG_nonrelocating();
    format_string = REQUIRED_ARG_nonrelocating();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (EQ(top_of_stack_qm,Kerror_string))
	return tformat_text_string(4,format_string,arg1,arg2,arg3);
    else if (top_of_stack_qm)
	return tformat_stack_error_text_string(4,format_string,arg1,arg2,arg3);
    else {
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(5,FIX((SI_Long)1L),format_string,arg1,arg2,arg3);
	return VALUES_1(Nil);
    }
}

static Object Qstart;              /* start */

static Object Qcall;               /* call */

static Object string_constant_38;  /* "Cannot ~a method-declaration ~NF.  ~a" */

static Object string_constant_39;  /* "start" */

static Object string_constant_40;  /* "call" */

static Object string_constant_41;  /* "~NW" */

static Object string_constant_42;  /* "Cannot execute ~NF because it is ~a." */

static Object Qprocedure_invocaton;  /* procedure-invocaton */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object string_constant_43;  /* "The class of procedure invocation attribute of ~NF, ~a, was ~
				    *           not procedure-invocation or a subclass of procedure-invocation."
				    */

static Object string_constant_44;  /* "Call to ~NF has argument count mismatch." */

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

/* GENERATE-PROCEDURE-AND-CODE-BODY-INVOCATION-IN-PLACE */
Object generate_procedure_and_code_body_invocation_in_place(procedure,
	    calling_code_body_qm,local_stack,top_of_arguments_on_stack,
	    incoming_argument_count,simulation_procedure_qm,
	    completion_form_qm,top_of_stack_qm,
	    arguments_known_to_be_correct_p,prepare_p,thread_qm)
    Object procedure, calling_code_body_qm, local_stack;
    Object top_of_arguments_on_stack, incoming_argument_count;
    Object simulation_procedure_qm, completion_form_qm, top_of_stack_qm;
    Object arguments_known_to_be_correct_p, prepare_p, thread_qm;
{
    Object saved_procedure, invocation_class, argument_count;
    Object sub_class_bit_vector, error_text_qm, temp_1, skip_list, key_value;
    Object marked, pred, curr, succ, reference, temp_2, entry_hash;
    Object gensymed_symbol_3, tail, head, new_cons, temp_3, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, def_structure_procedure_invocation_variable;
    Object invocation, invocation_frame_qm, proc_push_modify_macro_arg, car_1;
    Object cdr_1, procedure_tracing_qm, base_code_body, byte_code_body;
    Object called_environment_array_length, called_environment;
    Object initial_stack_index, ab_loop_iter_flag_;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_, stack_index, index_1, non_argument_index;
    char temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(160,156);
    SAVE_STACK();
    saved_procedure = Nil;
    invocation_class = Nil;
    argument_count = Nil;
    if (prepare_p) {
	if (EQ(prepare_p,Qstart) || EQ(prepare_p,Qcall)) {
	    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_declaration_class_description,
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
	    saved_procedure = procedure;
	    procedure = get_specific_method_for_stack(saved_procedure,
		    local_stack,
		    FIXNUM_ADD1(FIXNUM_MINUS(top_of_arguments_on_stack,
		    incoming_argument_count)),incoming_argument_count);
	    temp = TRUEP(error_text_p(procedure));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result = generate_procedure_invocation_error(5,top_of_stack_qm,
		    string_constant_38,EQ(prepare_p,Qstart) ? 
		    string_constant_39 : string_constant_40,
		    saved_procedure,procedure);
	    RESTORE_STACK();
	    return result;
	}
	error_text_qm = 
		prepare_procedure_argument_list_in_place_for_stack_procedure(procedure,
		local_stack,top_of_arguments_on_stack,
		incoming_argument_count,arguments_known_to_be_correct_p);
	if (error_text_qm) {
	    temp_1 = generate_procedure_invocation_error(3,top_of_stack_qm,
		    string_constant_41,error_text_qm);
	    reclaim_error_text(error_text_qm);
	    RESTORE_STACK();
	    return VALUES_1(temp_1);
	}
    }
    temp_1 = ISVREF(procedure,(SI_Long)8L);
    if ( !( !TRUEP(CAR(temp_1)) && ((SI_Long)0L != (IFIX(ISVREF(procedure,
	    (SI_Long)5L)) & (SI_Long)1L) ||  !TRUEP(Inside_breakpoint_p) 
	    && (SI_Long)0L != (IFIX(ISVREF(procedure,(SI_Long)4L)) & 
	    (SI_Long)16777216L) &&  !((SI_Long)0L != 
	    (IFIX(ISVREF(procedure,(SI_Long)4L)) & (SI_Long)8192L))))) {
	temp_1 = procedure;
	result = generate_procedure_invocation_error(4,top_of_stack_qm,
		string_constant_42,temp_1,reason_not_runnable(procedure));
	RESTORE_STACK();
	return result;
    }
    else {
	invocation_class = ISVREF(procedure,(SI_Long)20L);
	if (invocation_class &&  !EQ(invocation_class,Qprocedure_invocaton)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = invocation_class;
	    key_hash_value = SXHASH_SYMBOL_1(invocation_class) & 
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
	    gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol_3)) {
		gensymed_symbol_3 = invocation_class;
		temp_2 = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
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
		    temp_3 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_3,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_3 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = Nil;
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
		    temp_3 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_3,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_3 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = Nil;
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
		gensymed_symbol_3 = set_skip_list_entry(temp_2,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol_3,
			temp_1,gensymed_symbol_4);
	    }
	    global_properties = gensymed_symbol_3;
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
	    gensymed_symbol_3 = resulting_value;
	    if (gensymed_symbol_3) {
		sub_class_bit_vector = ISVREF(gensymed_symbol_3,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_invocation_class_description,
			(SI_Long)18L));
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
	    }
	    else
		temp = TRUEP(Nil);
	    temp =  !temp;
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    result = generate_procedure_invocation_error(4,top_of_stack_qm,
		    string_constant_43,procedure,invocation_class);
	    RESTORE_STACK();
	    return result;
	}
	else {
	    argument_count = ISVREF(procedure,(SI_Long)23L);
	    if (FIXNUM_NE(incoming_argument_count,argument_count)) {
		result = generate_procedure_invocation_error(3,
			top_of_stack_qm,string_constant_44,procedure);
		RESTORE_STACK();
		return result;
	    }
	    else {
		def_structure_procedure_invocation_variable = 
			ISVREF(Chain_of_available_procedure_invocations_vector,
			IFIX(Current_thread_index));
		if (def_structure_procedure_invocation_variable) {
		    temp_3 = Chain_of_available_procedure_invocations_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_procedure_invocation_variable,
			    (SI_Long)0L);
		    SVREF(temp_3,svref_arg_2) = svref_new_value;
		    SVREF(def_structure_procedure_invocation_variable,
			    FIX((SI_Long)0L)) = 
			    Qg2_defstruct_structure_name_procedure_invocation_g2_struct;
		}
		else
		    def_structure_procedure_invocation_variable = 
			    make_permanent_procedure_invocation_structure_internal();
		inline_note_allocate_cons(def_structure_procedure_invocation_variable,
			Nil);
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)7L)) = Nil;
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)9L)) = Nil;
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)18L)) = Nil;
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)19L)) = Nil;
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)20L)) = Nil;
		SVREF(def_structure_procedure_invocation_variable,
			FIX((SI_Long)21L)) = Nil;
		invocation = def_structure_procedure_invocation_variable;
		invocation_frame_qm = invocation_class ? 
			make_procedure_invocation_frame(invocation_class,
			(SI_Long)0L != (IFIX(ISVREF(procedure,
			(SI_Long)4L)) & (SI_Long)16777216L) ? T : Nil) : Nil;
		if (invocation_frame_qm)
		    ISVREF(invocation_frame_qm,(SI_Long)20L) = invocation;
		if (Profiling_enabled_qm)
		    increment_profiling_calls(procedure);
		temp_3 = copy_frame_serial_number(Current_frame_serial_number);
		SVREF(invocation,FIX((SI_Long)9L)) = temp_3;
		push_one_procedure_invocation(invocation,procedure);
		if (calling_code_body_qm) {
		    proc_push_modify_macro_arg = invocation;
		    car_1 = proc_push_modify_macro_arg;
		    cdr_1 = ISVREF(calling_code_body_qm,(SI_Long)13L);
		    temp_3 = proc_cons_1(car_1,cdr_1);
		    SVREF(calling_code_body_qm,FIX((SI_Long)13L)) = temp_3;
		}
		if (calling_code_body_qm &&  
			!(SIMPLE_VECTOR_P(calling_code_body_qm) && 
			EQ(ISVREF(calling_code_body_qm,(SI_Long)0L),
			Qg2_defstruct_structure_name_rule_instance_g2_struct)) 
			&& ISVREF(calling_code_body_qm,(SI_Long)11L))
		    SVREF(invocation,FIX((SI_Long)24L)) = Nil;
		else {
		    LOCK(Procedure_invocations_lock);
		    if (PUSH_UNWIND_PROTECT(0))
			register_top_level_procedure_invocation_1(invocation);
		    POP_UNWIND_PROTECT(0);
		    UNLOCK(Procedure_invocations_lock);
		    CONTINUE_UNWINDING(0);
		}
		SVREF(invocation,FIX((SI_Long)23L)) = procedure;
		procedure_tracing_qm = get_lookup_slot_value(procedure,
			Qtracing_and_breakpoints);
		temp_3 = procedure_tracing_qm ? 
			copy_for_slot_value(procedure_tracing_qm) : Nil;
		SVREF(invocation,FIX((SI_Long)22L)) = temp_3;
		SVREF(invocation,FIX((SI_Long)25L)) = simulation_procedure_qm;
		SVREF(invocation,FIX((SI_Long)26L)) = completion_form_qm;
		SVREF(invocation,FIX((SI_Long)27L)) = invocation_frame_qm;
		SVREF(invocation,FIX((SI_Long)12L)) = calling_code_body_qm;
		ISVREF(invocation,(SI_Long)3L) = FIX((SI_Long)0L);
		temp_3 = ISVREF(procedure,(SI_Long)21L);
		SVREF(invocation,FIX((SI_Long)10L)) = temp_3;
		SVREF(invocation,FIX((SI_Long)11L)) = invocation;
		SVREF(invocation,FIX((SI_Long)13L)) = Nil;
		base_code_body = M_CAR(ISVREF(procedure,(SI_Long)28L));
		temp_3 = ISVREF(base_code_body,(SI_Long)4L);
		SVREF(invocation,FIX((SI_Long)5L)) = temp_3;
		temp_3 = ISVREF(base_code_body,(SI_Long)5L);
		SVREF(invocation,FIX((SI_Long)6L)) = temp_3;
		SVREF(invocation,FIX((SI_Long)8L)) = base_code_body;
		byte_code_body = ISVREF(base_code_body,(SI_Long)8L);
		SVREF(invocation,FIX((SI_Long)1L)) = byte_code_body;
		temp_3 = ISVREF(byte_code_body,(SI_Long)3L);
		SVREF(invocation,FIX((SI_Long)4L)) = temp_3;
		called_environment_array_length = ISVREF(base_code_body,
			(SI_Long)6L);
		called_environment = IFIX(called_environment_array_length) 
			== (SI_Long)0L ? Nil : 
			allocate_managed_simple_vector(buffer_size_for_partial_buffer(called_environment_array_length,
			Environment_allocation_schemes));
		SVREF(invocation,FIX((SI_Long)2L)) = called_environment;
		if ( !(IFIX(called_environment_array_length) == (SI_Long)0L)) {
		    initial_stack_index = 
			    FIXNUM_ADD1(FIXNUM_MINUS(top_of_arguments_on_stack,
			    argument_count));
		    stack_index = IFIX(initial_stack_index);
		    ab_loop_bind_ = IFIX(top_of_arguments_on_stack);
		    index_1 = (SI_Long)0L;
		    ab_loop_iter_flag_ = T;
		  next_loop_12:
		    if (stack_index > ab_loop_bind_)
			goto end_loop_12;
		    if ( !TRUEP(ab_loop_iter_flag_))
			index_1 = index_1 + (SI_Long)1L;
		    temp_3 = ISVREF(local_stack,stack_index);
		    ISVREF(called_environment,index_1) = temp_3;
		    ISVREF(local_stack,stack_index) = Nil;
		    ab_loop_iter_flag_ = Nil;
		    stack_index = stack_index + (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    non_argument_index = IFIX(argument_count);
		    ab_loop_bind_ = 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(called_environment));
		  next_loop_13:
		    if (non_argument_index >= ab_loop_bind_)
			goto end_loop_13;
		    ISVREF(called_environment,non_argument_index) = Nil;
		    non_argument_index = non_argument_index + (SI_Long)1L;
		    goto next_loop_13;
		  end_loop_13:;
		}
		if (thread_qm)
		    SVREF(invocation,FIX((SI_Long)21L)) = thread_qm;
		maybe_set_lock_for_invocation(invocation,procedure);
		RESTORE_STACK();
		return VALUES_1(invocation);
	    }
	}
    }
}

/* MAKE-PROCEDURE-INVOCATION-FRAME */
Object make_procedure_invocation_frame(class_1,runs_while_inactive_qm)
    Object class_1, runs_while_inactive_qm;
{
    Object new_invocation, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long svref_new_value;

    x_note_fn_call(160,157);
    if (runs_while_inactive_qm) {
	new_invocation = make_frame(class_1);
	set_permanent_and_propagate(new_invocation,Nil);
	svref_new_value = IFIX(ISVREF(new_invocation,(SI_Long)5L)) | 
		(SI_Long)524288L;
	ISVREF(new_invocation,(SI_Long)5L) = FIX(svref_new_value);
	gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(new_invocation,
		(SI_Long)1L),(SI_Long)11L),(SI_Long)30L),(SI_Long)1L);
	gensymed_symbol_1 = new_invocation;
	inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
	temp = new_invocation;
    }
    else
	temp = make_transient_item(class_1);
    return VALUES_1(temp);
}

/* GENERATE-CODE-BODY-INVOCATION */
Object generate_code_body_invocation(code_body_to_call,calling_code_body,
	    thread_qm)
    Object code_body_to_call, calling_code_body, thread_qm;
{
    Object invocation, proc_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value, byte_code_body, environment_length, new_vector;
    Object called_environment;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,158);
    invocation = make_code_body_invocation_1();
    if (thread_qm)
	SVREF(invocation,FIX((SI_Long)21L)) = thread_qm;
    proc_push_modify_macro_arg = invocation;
    car_1 = proc_push_modify_macro_arg;
    cdr_1 = ISVREF(calling_code_body,(SI_Long)13L);
    svref_new_value = proc_cons_1(car_1,cdr_1);
    SVREF(calling_code_body,FIX((SI_Long)13L)) = svref_new_value;
    SVREF(invocation,FIX((SI_Long)12L)) = calling_code_body;
    SVREF(invocation,FIX((SI_Long)8L)) = code_body_to_call;
    byte_code_body = ISVREF(code_body_to_call,(SI_Long)8L);
    SVREF(invocation,FIX((SI_Long)1L)) = byte_code_body;
    svref_new_value = ISVREF(byte_code_body,(SI_Long)3L);
    if (svref_new_value);
    else
	svref_new_value = 
		ISVREF(ISVREF(M_CAR(ISVREF(ISVREF(code_body_to_call,
		(SI_Long)2L),(SI_Long)28L)),(SI_Long)8L),(SI_Long)3L);
    SVREF(invocation,FIX((SI_Long)4L)) = svref_new_value;
    ISVREF(invocation,(SI_Long)3L) = FIX((SI_Long)0L);
    svref_new_value = copy_frame_serial_number(Current_frame_serial_number);
    SVREF(invocation,FIX((SI_Long)9L)) = svref_new_value;
    svref_new_value = ISVREF(calling_code_body,(SI_Long)10L);
    SVREF(invocation,FIX((SI_Long)10L)) = svref_new_value;
    svref_new_value = ISVREF(calling_code_body,(SI_Long)11L);
    SVREF(invocation,FIX((SI_Long)11L)) = svref_new_value;
    SVREF(invocation,FIX((SI_Long)13L)) = Nil;
    svref_new_value = ISVREF(code_body_to_call,(SI_Long)4L);
    SVREF(invocation,FIX((SI_Long)5L)) = svref_new_value;
    svref_new_value = ISVREF(code_body_to_call,(SI_Long)5L);
    SVREF(invocation,FIX((SI_Long)6L)) = svref_new_value;
    environment_length = ISVREF(code_body_to_call,(SI_Long)6L);
    if (IFIX(environment_length) != (SI_Long)0L) {
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
	called_environment = new_vector;
    }
    else
	called_environment = Nil;
    SVREF(invocation,FIX((SI_Long)2L)) = called_environment;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(environment_length);
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    ISVREF(called_environment,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    return VALUES_1(invocation);
}

DEFINE_VARIABLE_WITH_SYMBOL(Closing_procedure_invocation, Qclosing_procedure_invocation);

/* CLOSE-PROCEDURE-INVOCATION */
Object close_procedure_invocation(procedure_invocation_to_delete)
    Object procedure_invocation_to_delete;
{
    Object procedure, completion_form_qm, procedure_invocation_frame;
    Object closing_procedure_invocation, temp, temp_1;
    Object structure_being_reclaimed, gensymed_symbol, svref_arg_2;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(160,159);
    SAVE_STACK();
    procedure = ISVREF(procedure_invocation_to_delete,(SI_Long)23L);
    completion_form_qm = ISVREF(procedure_invocation_to_delete,(SI_Long)26L);
    procedure_invocation_frame = ISVREF(procedure_invocation_to_delete,
	    (SI_Long)27L);
    delete_one_procedure_invocation(procedure_invocation_to_delete,procedure);
    if (ISVREF(procedure_invocation_to_delete,(SI_Long)24L)) {
	LOCK(Procedure_invocations_lock);
	if (PUSH_UNWIND_PROTECT(0))
	    deregister_top_level_procedure_invocation_1(procedure_invocation_to_delete);
	POP_UNWIND_PROTECT(0);
	UNLOCK(Procedure_invocations_lock);
	CONTINUE_UNWINDING(0);
    }
    if (completion_form_qm) {
	closing_procedure_invocation = procedure_invocation_to_delete;
	PUSH_SPECIAL_WITH_SYMBOL(Closing_procedure_invocation,Qclosing_procedure_invocation,closing_procedure_invocation,
		0);
	  temp = SYMBOL_FUNCTION(CAR(completion_form_qm));
	  FUNCALL_1(temp,completion_form_qm);
	  temp_1 = Closing_procedure_invocation;
	  SVREF(temp_1,FIX((SI_Long)26L)) = Nil;
	POP_SPECIAL();
    }
    if (procedure_invocation_frame) {
	ISVREF(procedure_invocation_frame,(SI_Long)20L) = Nil;
	SVREF(procedure_invocation_to_delete,FIX((SI_Long)27L)) = Nil;
	delete_frame(procedure_invocation_frame);
    }
    inline_note_reclaim_cons(procedure_invocation_to_delete,Nil);
    structure_being_reclaimed = procedure_invocation_to_delete;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop:
      gensymed_symbol = ISVREF(procedure_invocation_to_delete,(SI_Long)7L);
      if (CAS_SVREF(procedure_invocation_to_delete,(SI_Long)7L,
	      gensymed_symbol,Nil)) {
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
	      temp_1 = ISVREF(Chain_of_available_schedule_tasks_vector,
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
      SVREF(procedure_invocation_to_delete,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(procedure_invocation_to_delete,
	      (SI_Long)9L));
      SVREF(procedure_invocation_to_delete,FIX((SI_Long)9L)) = Nil;
    POP_SPECIAL();
    temp_1 = ISVREF(Chain_of_available_procedure_invocations_vector,
	    IFIX(Current_thread_index));
    SVREF(procedure_invocation_to_delete,FIX((SI_Long)0L)) = temp_1;
    temp_1 = Chain_of_available_procedure_invocations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp_1,svref_arg_2) = procedure_invocation_to_delete;
    RESTORE_STACK();
    return VALUES_1(Nil);
}

/* RECLAIM-CODE-BODY-ENVIRONMENT-VALUES */
Object reclaim_code_body_environment_values(code_body_environment_to_reclaim,
	    environment_description,start_qm,end_qm)
    Object code_body_environment_to_reclaim, environment_description, start_qm;
    Object end_qm;
{
    Object temp, value_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,160);
    temp = start_qm;
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    index_1 = IFIX(temp);
    temp = end_qm;
    if (temp);
    else
	temp = SIMPLE_ARRAY_ANY_1_LENGTH(code_body_environment_to_reclaim);
    ab_loop_bind_ = IFIX(temp);
    value_qm = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    value_qm = ISVREF(code_body_environment_to_reclaim,index_1);
    ISVREF(code_body_environment_to_reclaim,index_1) = Nil;
    if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm))) {
	if ( !(FIXNUMP(value_qm) || SYMBOLP(value_qm) || 
		SIMPLE_VECTOR_P(value_qm)))
	    reclaim_if_evaluation_value_1(value_qm);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* MODIFY-CODE-BODY-ENVIRONMENT-VAR-SPOT */
Object modify_code_body_environment_var_spot(code_body_invocation,
	    var_spot_index,value)
    Object code_body_invocation, var_spot_index, value;
{
    Object environment_vector, thing;
    SI_Long nesting, local_index, ab_loop_repeat_;

    x_note_fn_call(160,161);
    nesting = IFIX(var_spot_index) >>  -  - (SI_Long)10L;
    local_index = IFIX(var_spot_index) & (SI_Long)1023L;
    ab_loop_repeat_ = nesting;
  next_loop:
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    code_body_invocation = ISVREF(code_body_invocation,(SI_Long)12L);
    goto next_loop;
  end_loop:;
    environment_vector = ISVREF(code_body_invocation,(SI_Long)2L);
    thing = ISVREF(environment_vector,local_index);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    ISVREF(environment_vector,local_index) = value;
    return VALUES_1(value);
}

/* CLOSE-CODE-BODY-INVOCATION */
Object close_code_body_invocation(code_body_invocation)
    Object code_body_invocation;
{
    Object code_bodies_to_close, called_invocations_qm, invocation;
    Object proc_pop_store, cons_1, next_cons, temp, svref_arg_2;

    x_note_fn_call(160,162);
    code_bodies_to_close = proc_cons_1(code_body_invocation,Nil);
    code_body_invocation = Nil;
    called_invocations_qm = Nil;
  next_loop:
    if ( !TRUEP(code_bodies_to_close))
	goto end_loop;
    code_body_invocation = CAR(code_bodies_to_close);
    called_invocations_qm = ISVREF(code_body_invocation,(SI_Long)13L);
    if (called_invocations_qm) {
	invocation = FIRST(called_invocations_qm);
	if (SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_remote_procedure_call_g2_struct))
	    abort_outgoing_remote_procedure_call(invocation);
	else
	    code_bodies_to_close = proc_cons_1(invocation,
		    code_bodies_to_close);
    }
    else {
	proc_pop_store = Nil;
	cons_1 = code_bodies_to_close;
	if (cons_1) {
	    proc_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qproc);
	    if (ISVREF(Available_proc_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_proc_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_proc_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	code_bodies_to_close = next_cons;
	close_code_body_invocation_1(proc_pop_store);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLOSE-CODE-BODY-INVOCATION-1 */
Object close_code_body_invocation_1(code_body_invocation)
    Object code_body_invocation;
{
    Object code_body_environment_vector, calling_code_body_invocation_qm;
    Object lock_holder, temp, gensymed_symbol, structure_being_reclaimed;
    Object svref_arg_2, wake_ups, variable, ab_loop_list_;
    Object pruned_interest_list, last_1, next_qm, gensymed_symbol_1, temp_1;
    Object trailer, cons_1;
    Declare_special(2);

    x_note_fn_call(160,163);
    code_body_environment_vector = ISVREF(code_body_invocation,(SI_Long)2L);
    calling_code_body_invocation_qm = ISVREF(code_body_invocation,
	    (SI_Long)12L);
    if (EQ(code_body_invocation,Current_computation_instance))
	Current_computation_instance = Nil;
    if (memq_function(code_body_invocation,
	    All_computation_instances_above_breakpoint)) {
	All_computation_instances_above_breakpoint = 
		delete_gensym_element_1(code_body_invocation,
		All_computation_instances_above_breakpoint);
	May_return_from_breakpoint = Nil;
    }
    clear_event_detectors(code_body_invocation);
    clean_up_ri_completion_notification_collection_back_pointer(code_body_invocation);
    if (ISVREF(code_body_invocation,(SI_Long)20L))
	release_lock(code_body_invocation);
    lock_holder = ISVREF(code_body_invocation,(SI_Long)19L);
    if (lock_holder) {
	temp = delete_proc_element_1(code_body_invocation,
		ISVREF(lock_holder,(SI_Long)18L));
	SVREF(lock_holder,FIX((SI_Long)18L)) = temp;
	SVREF(code_body_invocation,FIX((SI_Long)19L)) = Nil;
    }
    if (code_body_environment_vector)
	reclaim_environment_vector(code_body_environment_vector);
    gensymed_symbol = Nil;
  next_loop:
    gensymed_symbol = ISVREF(code_body_invocation,(SI_Long)7L);
    if (CAS_SVREF(code_body_invocation,(SI_Long)7L,gensymed_symbol,Nil)) {
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
    wake_ups = ISVREF(code_body_invocation,(SI_Long)14L);
    variable = Nil;
    ab_loop_list_ = wake_ups;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    variable = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pruned_interest_list = delete_eval_element_1(code_body_invocation,
	    ISVREF(variable,(SI_Long)36L));
    ISVREF(variable,(SI_Long)36L) = pruned_interest_list;
    if ( !TRUEP(pruned_interest_list) &&  !TRUEP(ISVREF(variable,
	    (SI_Long)38L)))
	withdraw_backward_chaining(variable);
    goto next_loop_1;
  end_loop_1:
    if (wake_ups) {
	last_1 = wake_ups;
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
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = wake_ups;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    SVREF(code_body_invocation,FIX((SI_Long)14L)) = Nil;
    if (calling_code_body_invocation_qm) {
	gensymed_symbol = code_body_invocation;
	gensymed_symbol_1 = ISVREF(calling_code_body_invocation_qm,
		(SI_Long)13L);
	if (gensymed_symbol_1) {
	    if (EQ(M_CAR(gensymed_symbol_1),gensymed_symbol)) {
		temp_1 = M_CDR(gensymed_symbol_1);
		inline_note_reclaim_cons(gensymed_symbol_1,Qproc);
		if (ISVREF(Available_proc_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_proc_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = gensymed_symbol_1;
		    temp = Available_proc_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
		}
		else {
		    temp = Available_proc_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
		    temp = Available_proc_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = gensymed_symbol_1;
		}
		M_CDR(gensymed_symbol_1) = Nil;
		gensymed_symbol_1 = temp_1;
	    }
	    else {
		trailer = gensymed_symbol_1;
		cons_1 = M_CDR(gensymed_symbol_1);
	      next_loop_3:
		if ( !TRUEP(cons_1))
		    goto end_loop_3;
		if (EQ(M_CAR(cons_1),gensymed_symbol)) {
		    temp = M_CDR(cons_1);
		    M_CDR(trailer) = temp;
		    inline_note_reclaim_cons(cons_1,Qproc);
		    if (ISVREF(Available_proc_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = ISVREF(Available_proc_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_proc_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_proc_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_proc_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		    goto end_loop_3;
		}
		trailer = cons_1;
		cons_1 = M_CDR(cons_1);
		goto next_loop_3;
	      end_loop_3:
		goto end_2;
		gensymed_symbol_1 = Qnil;
	      end_2:;
	    }
	}
	else
	    gensymed_symbol_1 = Nil;
	SVREF(calling_code_body_invocation_qm,FIX((SI_Long)13L)) = 
		gensymed_symbol_1;
    }
    if (SIMPLE_VECTOR_P(code_body_invocation) && 
	    EQ(ISVREF(code_body_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct))
	temp_1 = close_procedure_invocation(code_body_invocation);
    else {
	inline_note_reclaim_cons(code_body_invocation,Nil);
	structure_being_reclaimed = code_body_invocation;
	PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
		1);
	  gensymed_symbol = Nil;
	next_loop_4:
	  gensymed_symbol = ISVREF(code_body_invocation,(SI_Long)7L);
	  if (CAS_SVREF(code_body_invocation,(SI_Long)7L,gensymed_symbol,
		      Nil)) {
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
	      goto end_3;
	  }
	  goto next_loop_4;
	end_loop_4:
	end_3:;
	  SVREF(code_body_invocation,FIX((SI_Long)7L)) = Nil;
	  reclaim_frame_serial_number(ISVREF(code_body_invocation,
		  (SI_Long)9L));
	  SVREF(code_body_invocation,FIX((SI_Long)9L)) = Nil;
	POP_SPECIAL();
	temp = ISVREF(Chain_of_available_code_body_invocations_vector,
		IFIX(Current_thread_index));
	SVREF(code_body_invocation,FIX((SI_Long)0L)) = temp;
	temp = Chain_of_available_code_body_invocations_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = code_body_invocation;
	temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

/* CLEAN-UP-RI-COMPLETION-NOTIFICATION-COLLECTION-BACK-POINTER */
Object clean_up_ri_completion_notification_collection_back_pointer(code_body_invocation)
    Object code_body_invocation;
{
    Object ri_completion_notification_collection_back_pointer_qm;

    x_note_fn_call(160,164);
    ri_completion_notification_collection_back_pointer_qm = 
	    ISVREF(code_body_invocation,(SI_Long)17L);
    if (ri_completion_notification_collection_back_pointer_qm) {
	M_CADR(ri_completion_notification_collection_back_pointer_qm) = Nil;
	SVREF(code_body_invocation,FIX((SI_Long)17L)) = Nil;
    }
    return VALUES_1(Nil);
}

static Object Qitem_reference;     /* item-reference */

static Object Qplace_reference;    /* place-reference */

static Object Qaction_cache;       /* action-cache */

/* VALID-ITEM-OR-EVALUATION-VALUE-P */
Object valid_item_or_evaluation_value_p(value,frame_serial_number,
	    type_spec_for_validation_qm)
    Object value, frame_serial_number, type_spec_for_validation_qm;
{
    Object thing, gensymed_symbol, xa, ya, temp_1;
    char temp;

    x_note_fn_call(160,165);
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L) {
	temp = EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector);
	if (temp);
	else {
	    thing = ISVREF(value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    : TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensymed_symbol = ISVREF(value,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(value) ? EQ(ISVREF(value,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp ? TRUEP(serve_item_p(value)) : TRUEP(Nil)) {
	    temp_1 =  !TRUEP(type_spec_for_validation_qm) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(type_spec_for_validation_qm,Qitem_or_datum) || 
			valid_class_type_specification_p(type_spec_for_validation_qm) 
			? type_specification_type_p(value,
			type_spec_for_validation_qm) : Qnil;
	}
	else
	    temp_1 = Nil;
    }
    else if (CONSP(value) && EQ(M_CDR(value),Qitem_reference))
	temp_1 = ISVREF(M_CAR(value),(SI_Long)3L);
    else if (CONSP(value) && EQ(M_CDR(value),Qplace_reference))
	temp_1 = evaluation_place_reference_valid_p(value);
    else if (CONSP(value) && EQ(M_CDR(value),Qaction_cache))
	temp_1 = validate_evaluation_action_cache(value,frame_serial_number);
    else if (type_spec_for_validation_qm)
	temp_1 = EQ(type_spec_for_validation_qm,Qitem_or_datum) || 
		valid_datum_type_specification_p(type_spec_for_validation_qm) 
		? type_specification_type_p(value,
		type_spec_for_validation_qm) : Qnil;
    else
	temp_1 = value;
    return VALUES_1(temp_1);
}

/* VALIDATE-CODE-BODY-INVOCATION-ENVIRONMENT */
Object validate_code_body_invocation_environment(invocation_to_validate,
	    validate_item_classes_also_qm,do_not_validate_code_body_callers_qm)
    Object invocation_to_validate, validate_item_classes_also_qm;
    Object do_not_validate_code_body_callers_qm;
{
    Object current_computation_flags, procedure_invocation_qm_1;
    Object procedure_qm_1, code_body_invocation_to_examine;
    Object code_body_to_examine, code_body_environment_to_examine;
    Object frame_serial_number, value_qm, svref_new_value;
    Object environment_description, item_type_qm, x2, gensymed_symbol_1;
    Object temp_1;
    SI_Long environment_length, index_1, ab_loop_bind_, gensymed_symbol;
    char temp;
    Declare_special(1);

    x_note_fn_call(160,166);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL_WITH_SYMBOL(Current_computation_flags,Qcurrent_computation_flags,current_computation_flags,
	    0);
      procedure_invocation_qm_1 = ISVREF(invocation_to_validate,(SI_Long)11L);
      procedure_qm_1 = procedure_invocation_qm_1 ? 
	      ISVREF(procedure_invocation_qm_1,(SI_Long)23L) : Nil;
      if (procedure_qm_1) {
	  if ((SI_Long)0L != (IFIX(ISVREF(procedure_qm_1,(SI_Long)4L)) & 
		  (SI_Long)33554432L))
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	  else
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
      }
      if ( !TRUEP(validate_item_classes_also_qm)) {
	  code_body_invocation_to_examine = invocation_to_validate;
	  code_body_to_examine = Nil;
	  code_body_environment_to_examine = Nil;
	  environment_length = (SI_Long)0L;
	  frame_serial_number = Nil;
	next_loop:
	  code_body_to_examine = ISVREF(code_body_invocation_to_examine,
		  (SI_Long)8L);
	  code_body_environment_to_examine = 
		  ISVREF(code_body_invocation_to_examine,(SI_Long)2L);
	  environment_length = IFIX(ISVREF(code_body_to_examine,(SI_Long)6L));
	  frame_serial_number = ISVREF(code_body_invocation_to_examine,
		  (SI_Long)9L);
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = environment_length;
	  value_qm = Nil;
	next_loop_1:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop;
	  value_qm = ISVREF(code_body_environment_to_examine,index_1);
	  if (value_qm) {
	      svref_new_value = validate_item_or_evaluation_value(value_qm,
		      frame_serial_number,Nil);
	      ISVREF(code_body_environment_to_examine,index_1) = 
		      svref_new_value;
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop_1;
	end_loop:;
	  if (do_not_validate_code_body_callers_qm ||  
		  !(SIMPLE_VECTOR_P(code_body_invocation_to_examine) && 
		  EQ(ISVREF(code_body_invocation_to_examine,(SI_Long)0L),
		  Qg2_defstruct_structure_name_code_body_invocation_g2_struct)))
	      goto end_loop_1;
	  code_body_invocation_to_examine = 
		  ISVREF(code_body_invocation_to_examine,(SI_Long)12L);
	  goto next_loop;
	end_loop_1:;
      }
      else {
	  code_body_invocation_to_examine = invocation_to_validate;
	  code_body_to_examine = Nil;
	  code_body_environment_to_examine = Nil;
	  environment_length = (SI_Long)0L;
	  environment_description = Nil;
	  frame_serial_number = Nil;
	next_loop_2:
	  code_body_to_examine = ISVREF(code_body_invocation_to_examine,
		  (SI_Long)8L);
	  code_body_environment_to_examine = 
		  ISVREF(code_body_invocation_to_examine,(SI_Long)2L);
	  environment_length = IFIX(ISVREF(code_body_to_examine,(SI_Long)6L));
	  environment_description = ISVREF(code_body_to_examine,(SI_Long)7L);
	  frame_serial_number = ISVREF(code_body_invocation_to_examine,
		  (SI_Long)9L);
	  index_1 = (SI_Long)0L;
	  ab_loop_bind_ = environment_length;
	  value_qm = Nil;
	  item_type_qm = Nil;
	next_loop_3:
	  if (index_1 >= ab_loop_bind_)
	      goto end_loop_2;
	  value_qm = ISVREF(code_body_environment_to_examine,index_1);
	  if (SIMPLE_VECTOR_P(value_qm) && 
		  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_qm)) > (SI_Long)2L 
		  &&  !EQ(ISVREF(value_qm,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(value_qm,(SI_Long)1L);
	      temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		      Qg2_defstruct_structure_name_class_description_g2_struct) 
		      ? TRUEP(x2) : TRUEP(Qnil);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
	      gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
		      (SI_Long)1L),Maximum_in_place_array_size) ? 
		      ISVREF(environment_description,gensymed_symbol + 
		      IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(environment_description,
		      (gensymed_symbol >>  -  - (SI_Long)10L) + 
		      (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
	      if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		      Kgeneral_description))
		  gensymed_symbol_1 = 
			  getfq_function_no_default(CDR(gensymed_symbol_1),
			  Ktype);
	      item_type_qm = gensymed_symbol_1;
	  }
	  else
	      item_type_qm = Nil;
	  if (value_qm) {
	      svref_new_value = validate_item_or_evaluation_value(value_qm,
		      frame_serial_number,item_type_qm);
	      ISVREF(code_body_environment_to_examine,index_1) = 
		      svref_new_value;
	  }
	  index_1 = index_1 + (SI_Long)1L;
	  goto next_loop_3;
	end_loop_2:;
	  if (do_not_validate_code_body_callers_qm ||  
		  !(SIMPLE_VECTOR_P(code_body_invocation_to_examine) && 
		  EQ(ISVREF(code_body_invocation_to_examine,(SI_Long)0L),
		  Qg2_defstruct_structure_name_code_body_invocation_g2_struct)))
	      goto end_loop_3;
	  code_body_invocation_to_examine = 
		  ISVREF(code_body_invocation_to_examine,(SI_Long)12L);
	  goto next_loop_2;
	end_loop_3:;
      }
      temp_1 = Nil;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* VALIDATE-COMPUTATION-INSTANCE-ENVIRONMENT */
Object validate_computation_instance_environment(computation_instance,
	    validate_item_classes_also_qm,do_not_validate_code_body_callers_qm)
    Object computation_instance, validate_item_classes_also_qm;
    Object do_not_validate_code_body_callers_qm;
{
    Object type_name, temp_1;
    char temp;

    x_note_fn_call(160,167);
    if (SIMPLE_VECTOR_P(computation_instance)) {
	type_name = ISVREF(computation_instance,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = 
		validate_code_body_invocation_environment(computation_instance,
		validate_item_classes_also_qm,
		do_not_validate_code_body_callers_qm);
    else if (SIMPLE_VECTOR_P(computation_instance) && 
	    EQ(ISVREF(computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))
	temp_1 = validate_rule_context_vector(ISVREF(computation_instance,
		(SI_Long)2L),ISVREF(ISVREF(computation_instance,
		(SI_Long)8L),(SI_Long)34L),ISVREF(computation_instance,
		(SI_Long)11L),ISVREF(computation_instance,(SI_Long)8L),Nil);
    else
	temp_1 = Qnil;
    return VALUES_1(temp_1);
}

/* VALIDATE-ENVIRONMENT-FOR-CODE-BODY-INVOCATION-TREE */
Object validate_environment_for_code_body_invocation_tree(code_body_invocation)
    Object code_body_invocation;
{
    Object called_code_body_invocation, ab_loop_list_, type_name;
    char temp;

    x_note_fn_call(160,168);
    validate_computation_instance_environment(code_body_invocation,T,T);
    called_code_body_invocation = Nil;
    ab_loop_list_ = ISVREF(code_body_invocation,(SI_Long)13L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    called_code_body_invocation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(called_code_body_invocation)) {
	type_name = ISVREF(called_code_body_invocation,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	validate_environment_for_code_body_invocation_tree(called_code_body_invocation);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* VALIDATE-ALL-PROCEDURE-INVOCATIONS-1 */
Object validate_all_procedure_invocations_1()
{
    Object top_array, procedure_invocation_qm_1;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,169);
    top_array = Top_level_procedure_invocations_array;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(top_array,(SI_Long)1L));
    procedure_invocation_qm_1 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    procedure_invocation_qm_1 = FIXNUM_LE(ISVREF(top_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(top_array,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(top_array,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    if (procedure_invocation_qm_1)
	validate_environment_for_code_body_invocation_tree(procedure_invocation_qm_1);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* CODE-BODY-INVOCATION-LOCAL-NAME-VALUE */
Object code_body_invocation_local_name_value(code_body_invocation,local_name)
    Object code_body_invocation, local_name;
{
    Object var_spot, ab_loop_list_;
    SI_Long index_1;

    x_note_fn_call(160,170);
    index_1 = (SI_Long)0L;
    var_spot = Nil;
    ab_loop_list_ = ISVREF(ISVREF(code_body_invocation,(SI_Long)8L),
	    (SI_Long)7L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var_spot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(local_name,M_CAR(var_spot)))
	return VALUES_1(ISVREF(ISVREF(code_body_invocation,(SI_Long)2L),
		index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SET-CODE-BODY-INVOCATION-LOCAL-NAME-VALUE */
Object set_code_body_invocation_local_name_value(code_body_invocation,
	    local_name,new_value)
    Object code_body_invocation, local_name, new_value;
{
    Object local_var_vector, description, var_name, thing;
    SI_Long description_index, ab_loop_bind_, local_var_index;

    x_note_fn_call(160,171);
    local_var_vector = ISVREF(code_body_invocation,(SI_Long)2L);
    description = ISVREF(ISVREF(code_body_invocation,(SI_Long)8L),(SI_Long)7L);
    description_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(description,(SI_Long)1L));
    var_name = Nil;
  next_loop:
    if (description_index >= ab_loop_bind_)
	goto end_loop;
    var_name = FIXNUM_LE(ISVREF(description,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(description,
	    description_index + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(description,(description_index >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),description_index & (SI_Long)1023L);
    if (EQ(local_name,var_name)) {
	local_var_index = description_index >>  -  - (SI_Long)1L;
	thing = ISVREF(local_var_vector,local_var_index);
	if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	    reclaim_if_evaluation_value_1(thing);
	ISVREF(local_var_vector,local_var_index) = new_value;
	return VALUES_1(new_value);
    }
    description_index = description_index + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* SET-LOCAL-NAME-VALUE-VALIDATING-ENVIRONMENT */
Object set_local_name_value_validating_environment(invocation,variable,value)
    Object invocation, variable, value;
{
    Object procedure;

    x_note_fn_call(160,172);
    procedure = ISVREF(invocation,(SI_Long)23L);
    if ( !(IFIX(FIXNUM_LOGAND(Procedure_invalidates_environment_union_mask,
	    ISVREF(procedure,(SI_Long)29L))) == (SI_Long)0L))
	validate_computation_instance_environment(invocation,Nil,Nil);
    set_code_body_invocation_local_name_value(invocation,variable,value);
    update_code_body_invocation_frame_serial_number(invocation);
    return VALUES_1(value);
}

static Object Qwake_up_code_body_invocation;  /* wake-up-code-body-invocation */

/* START-PROCEDURE-INVOCATION-IN-PLACE */
Object start_procedure_invocation_in_place(procedure,priority_qm,wait_qm,
	    local_stack,top_of_arguments_on_stack,argument_count,
	    simulator_procedure_qm,completion_form_qm,top_of_stack_qm,
	    validated_args_p,prepare_p)
    Object procedure, priority_qm, wait_qm, local_stack;
    Object top_of_arguments_on_stack, argument_count, simulator_procedure_qm;
    Object completion_form_qm, top_of_stack_qm, validated_args_p, prepare_p;
{
    Object new_invocation_qm, actual_priority, gensymed_symbol;
    Object gensymed_symbol_1, temp_1, type_name, old, new_1;
    Object def_structure_schedule_task_variable, temp_3, svref_arg_2;
    Object svref_new_value, task, structure_being_reclaimed;
    char gensymed_symbol_2, temp_2, svref_new_value_1;
    double gensymed_symbol_3, temp, gensymed_symbol_4, aref_new_value;
    Declare_special(1);

    x_note_fn_call(160,173);
    new_invocation_qm = 
	    generate_procedure_and_code_body_invocation_in_place(procedure,
	    Nil,local_stack,top_of_arguments_on_stack,argument_count,
	    simulator_procedure_qm,completion_form_qm,top_of_stack_qm,
	    validated_args_p,prepare_p,Nil);
    if (SIMPLE_VECTOR_P(new_invocation_qm) && EQ(ISVREF(new_invocation_qm,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct)) {
	if (priority_qm)
	    actual_priority = SVREF(new_invocation_qm,FIX((SI_Long)10L)) = 
		    priority_qm;
	else
	    actual_priority = ISVREF(new_invocation_qm,(SI_Long)10L);
	if (wait_qm) {
	    gensymed_symbol = new_invocation_qm;
	    gensymed_symbol_1 = actual_priority;
	    gensymed_symbol_2 = (SI_Long)0L != (IFIX(ISVREF(procedure,
		    (SI_Long)4L)) & (SI_Long)16777216L);
	    gensymed_symbol_3 = DFLOAT_ISAREF_1(gensymed_symbol_2 ? 
		    Current_real_time : Current_g2_time,(SI_Long)0L);
	    if (FIXNUMP(wait_qm))
		temp = (double)IFIX(wait_qm);
	    else if (INLINE_LONG_VECTOR_P(wait_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wait_qm)) == (SI_Long)1L) {
		temp_1 = convert_g2longint_to_double(aref1(wait_qm,
			FIX((SI_Long)0L)));
		temp = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	    }
	    else
		temp = DFLOAT_ISAREF_1(wait_qm,(SI_Long)0L);
	    reclaim_evaluation_quantity(wait_qm);
	    gensymed_symbol_4 = temp;
	    gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
	    if (SIMPLE_VECTOR_P(gensymed_symbol)) {
		type_name = ISVREF(gensymed_symbol,(SI_Long)0L);
		temp_2 = EQ(type_name,
			Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
		if (temp_2);
		else
		    temp_2 = EQ(type_name,
			    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		old = Nil;
		new_1 = Nil;
	      next_loop:
		old = ISVREF(gensymed_symbol,(SI_Long)7L);
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_3 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_3,svref_arg_2) = svref_new_value;
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
		temp_3 = ISVREF(task,(SI_Long)1L);
		DFLOAT_ISASET_1(temp_3,(SI_Long)0L,gensymed_symbol_3);
		temp_3 = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
		svref_new_value_1 =  !gensymed_symbol_2;
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		SVREF(task,FIX((SI_Long)4L)) = gensymed_symbol_1;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = Qwake_up_code_body_invocation;
		temp_3 = SYMBOL_FUNCTION(Qwake_up_code_body_invocation);
		SVREF(task,FIX((SI_Long)8L)) = temp_3;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)13L)) = gensymed_symbol;
		new_1 = task;
		if (CAS_SVREF(gensymed_symbol,(SI_Long)7L,old,new_1)) {
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
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = old;
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
		    temp_3 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
		    temp_3 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = new_1;
		}
		goto next_loop;
	      end_loop:
	      end_1:;
	    }
	    else {
		old = Nil;
		new_1 = Nil;
	      next_loop_1:
		old = ISVREF(gensymed_symbol,(SI_Long)7L);
		def_structure_schedule_task_variable = 
			ISVREF(Chain_of_available_schedule_tasks_vector,
			IFIX(Current_thread_index));
		if (def_structure_schedule_task_variable) {
		    temp_3 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = 
			    ISVREF(def_structure_schedule_task_variable,
			    (SI_Long)0L);
		    SVREF(temp_3,svref_arg_2) = svref_new_value;
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
		temp_3 = ISVREF(task,(SI_Long)1L);
		DFLOAT_ISASET_1(temp_3,(SI_Long)0L,gensymed_symbol_3);
		temp_3 = ISVREF(task,(SI_Long)1L);
		aref_new_value = -1.0;
		DFLOAT_ISASET_1(temp_3,(SI_Long)1L,aref_new_value);
		svref_new_value_1 =  !gensymed_symbol_2;
		SVREF(task,FIX((SI_Long)3L)) = svref_new_value_1 ? T : Nil;
		SVREF(task,FIX((SI_Long)4L)) = gensymed_symbol_1;
		SVREF(task,FIX((SI_Long)5L)) = Nil;
		SVREF(task,FIX((SI_Long)9L)) = Nil;
		SVREF(task,FIX((SI_Long)10L)) = Nil;
		SVREF(task,FIX((SI_Long)7L)) = Qexecute_computation_instance;
		temp_3 = SYMBOL_FUNCTION(Qexecute_computation_instance);
		SVREF(task,FIX((SI_Long)8L)) = temp_3;
		ISVREF(task,(SI_Long)12L) = FIX((SI_Long)1L);
		SVREF(task,FIX((SI_Long)13L)) = gensymed_symbol;
		new_1 = task;
		if (CAS_SVREF(gensymed_symbol,(SI_Long)7L,old,new_1)) {
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
			svref_arg_2 = Current_thread_index;
			SVREF(temp_3,svref_arg_2) = old;
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
		    temp_3 = 
			    ISVREF(Chain_of_available_schedule_tasks_vector,
			    IFIX(Current_thread_index));
		    SVREF(new_1,FIX((SI_Long)0L)) = temp_3;
		    temp_3 = Chain_of_available_schedule_tasks_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_3,svref_arg_2) = new_1;
		}
		goto next_loop_1;
	      end_loop_1:
	      end_2:;
	    }
	}
	else
	    schedule_computation_instance_execution(new_invocation_qm,
		    actual_priority,procedure);
    }
    return VALUES_1(new_invocation_qm);
}

/* START-PROCEDURE-INVOCATION-IN-PLACE-IMMEDIATELY */
Object start_procedure_invocation_in_place_immediately(procedure,
	    local_stack,top_of_arguments_on_stack,argument_count,
	    simulator_procedure_qm,completion_form_qm,top_of_stack_qm)
    Object procedure, local_stack, top_of_arguments_on_stack, argument_count;
    Object simulator_procedure_qm, completion_form_qm, top_of_stack_qm;
{
    Object new_invocation_qm;

    x_note_fn_call(160,174);
    new_invocation_qm = 
	    generate_procedure_and_code_body_invocation_in_place(procedure,
	    Nil,local_stack,top_of_arguments_on_stack,argument_count,
	    simulator_procedure_qm,completion_form_qm,top_of_stack_qm,Nil,
	    Nil,Nil);
    if (SIMPLE_VECTOR_P(new_invocation_qm) && EQ(ISVREF(new_invocation_qm,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct))
	filo_enqueue_immediate_code_body_invocation(new_invocation_qm);
    return VALUES_1(new_invocation_qm);
}

/* START-DEFERRED-PROCEDURE-INVOCATION-IN-PLACE */
Object start_deferred_procedure_invocation_in_place(code_body_invocation)
    Object code_body_invocation;
{
    x_note_fn_call(160,175);
    schedule_computation_instance_execution(code_body_invocation,
	    ISVREF(code_body_invocation,(SI_Long)10L),
	    ISVREF(ISVREF(code_body_invocation,(SI_Long)11L),(SI_Long)23L));
    return VALUES_1(Nil);
}

/* LOCAL-BASE-OF-PROCEDURE-INVOCATION-STACK */
Object local_base_of_procedure_invocation_stack(procedure_invocation)
    Object procedure_invocation;
{
    Object callee, caller_qm, temp;

    x_note_fn_call(160,176);
    callee = procedure_invocation;
    caller_qm = Nil;
  next_loop:
    caller_qm = calling_procedure_invocation(callee);
    if ( !TRUEP(caller_qm))
	goto end_loop;
    callee = caller_qm;
    goto next_loop;
  end_loop:
    temp = callee;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* TRUE-BASE-OF-PROCEDURE-INVOCATION-STACK-P */
Object true_base_of_procedure_invocation_stack_p(procedure_invocation)
    Object procedure_invocation;
{
    Object temp;

    x_note_fn_call(160,177);
    temp =  !TRUEP(ISVREF(procedure_invocation,(SI_Long)12L)) ? T : Nil;
    return VALUES_1(temp);
}

/* UPDATE-CODE-BODY-INVOCATION-FRAME-SERIAL-NUMBER */
Object update_code_body_invocation_frame_serial_number(first_code_body_invocation)
    Object first_code_body_invocation;
{
    Object invocation_to_reset, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value;

    x_note_fn_call(160,178);
    invocation_to_reset = first_code_body_invocation;
  next_loop:
    frame_serial_number_setf_arg = Current_frame_serial_number;
    old = ISVREF(invocation_to_reset,(SI_Long)9L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(invocation_to_reset,FIX((SI_Long)9L)) = svref_new_value;
    if ( !(SIMPLE_VECTOR_P(invocation_to_reset) && 
	    EQ(ISVREF(invocation_to_reset,(SI_Long)0L),
	    Qg2_defstruct_structure_name_code_body_invocation_g2_struct)))
	goto end_loop;
    invocation_to_reset = ISVREF(invocation_to_reset,(SI_Long)12L);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object array_constant_15;   /* # */

/* ABORT-PROCEDURE-INVOCATION */
Object abort_procedure_invocation varargs_1(int, n)
{
    Object procedure_invocation;
    Object suppress_error_signal_to_callers_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, x2, gensymed_symbol, sub_class_bit_vector, invocations;
    Object scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_;
    Object ab_skip_list_p_, ab_tail_node_, invocation_qm;
    Object ab_less_than_branch_qm_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long ab_table_length_, ab_index_;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(160,179);
    INIT_ARGS_nonrelocating();
    procedure_invocation = REQUIRED_ARG_nonrelocating();
    suppress_error_signal_to_callers_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(procedure_invocation) && 
	    EQ(ISVREF(procedure_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct)) {
	if (suppress_error_signal_to_callers_qm || 
		true_base_of_procedure_invocation_stack_p(procedure_invocation))
	    return close_code_body_invocation(procedure_invocation);
	else {
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
		      twrite_beginning_of_wide_string(array_constant_15,
			      FIX((SI_Long)9L));
		      write_procedure_invocation_instance_from_slot(procedure_invocation,
			      Nil);
		      twrite_beginning_of_wide_string(array_constant_14,
			      FIX((SI_Long)1L));
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return signal_procedure_invocation_error(procedure_invocation,
		    Qerror,FIX((SI_Long)1L),temp,Nil);
	}
    }
    else {
	if (SIMPLE_VECTOR_P(procedure_invocation) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure_invocation)) > 
		(SI_Long)2L &&  !EQ(ISVREF(procedure_invocation,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(procedure_invocation,(SI_Long)1L);
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
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	if (temp_1) {
	    invocations = ISVREF(procedure_invocation,(SI_Long)26L);
	    if (invocations) {
		scope_conses = Scope_conses;
		ab_hash_table_ = invocations;
		ab_table_length_ = (SI_Long)0L;
		ab_index_ = (SI_Long)0L;
		ab_tree_form_ = Nil;
		ab_node_stack_ = Nil;
		ab_current_node_ = Nil;
		ab_current_alist_ = Nil;
		ab_entry_cons_ = Nil;
		ab_skip_list_p_ = Nil;
		ab_tail_node_ = Nil;
		invocation_qm = Nil;
		PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
			0);
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
			  ab_entry_cons_ = 
				  scope_cons(ISVREF(ab_current_node_,
				  (SI_Long)2L),ISVREF(ab_current_node_,
				  (SI_Long)3L));
		  }
		  else if (ab_current_node_) {
		      ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		      if (ab_current_node_) {
			  ab_less_than_branch_qm_ = Nil;
			next_loop_1:
			  ab_less_than_branch_qm_ = 
				  ISVREF(ab_current_node_,(SI_Long)1L);
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
			  ab_current_alist_ = ISVREF(ab_current_node_,
				  (SI_Long)3L);
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
			      ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T :
				       Nil;
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
		  invocation_qm = M_CDR(ab_entry_cons_);
		  abort_procedure_invocation(2,invocation_qm,
			  suppress_error_signal_to_callers_qm);
		  goto next_loop;
		end_loop_3:
		  result = VALUES_1(Qnil);
		POP_SPECIAL();
		return result;
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    if (SIMPLE_VECTOR_P(procedure_invocation) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(procedure_invocation)) 
		    > (SI_Long)2L &&  !EQ(ISVREF(procedure_invocation,
		    (SI_Long)1L),Qavailable_frame_vector)) {
		x2 = ISVREF(procedure_invocation,(SI_Long)1L);
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
			IFIX(ISVREF(Procedure_invocation_class_description,
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
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return abort_procedure_invocation(2,
			ISVREF(procedure_invocation,(SI_Long)20L),
			suppress_error_signal_to_callers_qm);
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* ABORT-CODE-BODY-INVOCATION */
Object abort_code_body_invocation(invocation)
    Object invocation;
{
    Object temp;

    x_note_fn_call(160,180);
    temp = SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct) ?
	     abort_outgoing_remote_procedure_call(invocation) : 
	    close_code_body_invocation(invocation);
    return VALUES_1(temp);
}

/* CLEAR-PROCEDURE-INVOCATIONS-1 */
Object clear_procedure_invocations_1()
{
    Object top_array, invocation_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,181);
    top_array = Top_level_procedure_invocations_array;
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(top_array,(SI_Long)1L));
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    invocation_qm = Nil;
  next_loop_1:
    invocation_qm = FIXNUM_LE(ISVREF(top_array,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(top_array,index_1 + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(top_array,
	    (index_1 >>  -  - (SI_Long)10L) + (SI_Long)2L),index_1 & 
	    (SI_Long)1023L);
    if ( !(invocation_qm && 
	    abort_running_while_running_procedure_invocations(invocation_qm)))
	goto end_loop_1;
    goto next_loop_1;
  end_loop_1:;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* ABORT-RUNNING-WHILE-RUNNING-PROCEDURE-INVOCATIONS */
Object abort_running_while_running_procedure_invocations(procedure_invocation)
    Object procedure_invocation;
{
    Object invocation_to_abort, temp;

    x_note_fn_call(160,182);
    invocation_to_abort = 
	    find_running_while_running_procedure_invocation(procedure_invocation);
    if (invocation_to_abort) {
	if (true_base_of_procedure_invocation_stack_p(procedure_invocation))
	    abort_procedure_invocation(1,procedure_invocation);
	else
	    signal_error_to_running_while_running_invocation(procedure_invocation);
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* FIND-RUNNING-WHILE-RUNNING-PROCEDURE-INVOCATION */
Object find_running_while_running_procedure_invocation(invocation)
    Object invocation;
{
    Object block, temp_1, sub_invocation, ab_loop_list_, result_1;
    char temp;

    x_note_fn_call(160,183);
    if (SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct)) {
	block = ISVREF(invocation,(SI_Long)23L);
	temp =  !((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)4L)) & 
		(SI_Long)16777216L));
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = invocation;
    else {
	sub_invocation = Nil;
	ab_loop_list_ = ISVREF(invocation,(SI_Long)13L);
	result_1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_invocation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result_1 = 
		find_running_while_running_procedure_invocation(sub_invocation);
	if (result_1) {
	    temp_1 = result_1;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = Nil;
	goto end_1;
	temp_1 = Qnil;
      end_1:;
    }
    return VALUES_1(temp_1);
}

static Object string_constant_45;  /* "Aborting procedure invocations while resetting G2." */

/* SIGNAL-ERROR-TO-RUNNING-WHILE-RUNNING-INVOCATION */
Object signal_error_to_running_while_running_invocation(invocation)
    Object invocation;
{
    x_note_fn_call(160,184);
    signal_procedure_invocation_error(invocation,Qerror,FIX((SI_Long)1L),
	    tformat_text_string(1,string_constant_45),Nil);
    return VALUES_1(Nil);
}

/* SIGNAL-PROCEDURE-INVOCATION-ERROR */
Object signal_procedure_invocation_error(procedure_invocation,error_name,
	    error_level,error_text_string,error_arguments)
    Object procedure_invocation, error_name, error_level, error_text_string;
    Object error_arguments;
{
    x_note_fn_call(160,185);
    return signal_code_body_invocation_error(9,procedure_invocation,Qerror,
	    error_level,error_text_string,Nil,Nil,Nil,Nil,Nil);
}

static Object string_constant_46;  /* "~%Aborting procedure stack from " */

static Object string_constant_47;  /* "." */

/* SIGNAL-CODE-BODY-INVOCATION-ERROR */
Object signal_code_body_invocation_error varargs_1(int, n)
{
    Object code_body_invocation, error_1, error_level, error_text;
    Object byte_code_body_qm, program_counter_qm, stack_qm, top_of_stack_qm;
    Object suppress_debugging_info_qm;
    Object computation_frame_qm, computation_component_particulars_qm;
    Object error_text_local, code_body_invocation_error_handler_qm;
    Object procedure_invocation, base_of_stack;
    Object calling_code_body_invocation_qm, calling_remote_procedure_call_qm;
    Object calling_g2gl_call_invocation_qm, error_message, temp, x2;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(7);

    x_note_fn_call(160,186);
    INIT_ARGS_nonrelocating();
    code_body_invocation = REQUIRED_ARG_nonrelocating();
    error_1 = REQUIRED_ARG_nonrelocating();
    error_level = REQUIRED_ARG_nonrelocating();
    error_text = REQUIRED_ARG_nonrelocating();
    byte_code_body_qm = REQUIRED_ARG_nonrelocating();
    program_counter_qm = REQUIRED_ARG_nonrelocating();
    stack_qm = REQUIRED_ARG_nonrelocating();
    top_of_stack_qm = REQUIRED_ARG_nonrelocating();
    suppress_debugging_info_qm = REQUIRED_ARG_nonrelocating();
    computation_frame_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    computation_component_particulars_qm = OPTIONAL_ARG_P_nonrelocating() ?
	     OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    error_text_local = copy_wide_string(CONSP(error_text) ? 
	    FIRST(error_text) : error_text);
    code_body_invocation_error_handler_qm = 
	    find_error_handler_for_code_body_invocation(error_1,
	    code_body_invocation);
    procedure_invocation = ISVREF(code_body_invocation,(SI_Long)11L);
    base_of_stack = 
	    local_base_of_procedure_invocation_stack(procedure_invocation);
    calling_code_body_invocation_qm = ISVREF(base_of_stack,(SI_Long)12L);
    calling_remote_procedure_call_qm = 
	    SIMPLE_VECTOR_P(calling_code_body_invocation_qm) && 
	    EQ(ISVREF(calling_code_body_invocation_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct) 
	    && ISVREF(calling_code_body_invocation_qm,(SI_Long)22L) ? 
	    calling_code_body_invocation_qm : Nil;
    calling_g2gl_call_invocation_qm = 
	    g2gl_call_invocation_p_function(calling_code_body_invocation_qm) 
	    ? calling_code_body_invocation_qm : Nil;
    if (suppress_debugging_info_qm && code_body_invocation_error_handler_qm)
	error_message = error_text;
    else {
	temp = computation_frame_qm;
	if (temp);
	else
	    temp = ISVREF(procedure_invocation,(SI_Long)23L);
	temp = generate_standard_error_message(error_1,error_text,temp,
		computation_frame_qm ? 
		computation_component_particulars_qm : Nil,
		code_body_invocation,byte_code_body_qm,byte_code_body_qm 
		&&  !EQ(byte_code_body_qm,ISVREF(code_body_invocation,
		(SI_Long)1L)) ? ISVREF(byte_code_body_qm,(SI_Long)3L) : 
		ISVREF(code_body_invocation,(SI_Long)4L),
		program_counter_qm,stack_qm,top_of_stack_qm,
		ISVREF(code_body_invocation,(SI_Long)2L));
	reclaim_error_text(error_text);
	error_message = temp;
    }
    if (SIMPLE_VECTOR_P(error_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(error_1)) > (SI_Long)2L &&  
	    !EQ(ISVREF(error_1,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(error_1,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	setup_source_info_for_error_object(error_1);
    if (code_body_invocation_error_handler_qm)
	handle_error_in_code_body_invocation(code_body_invocation_error_handler_qm,
		code_body_invocation,error_1,error_message);
    else {
	if (calling_remote_procedure_call_qm)
	    remote_procedure_call_being_aborted(calling_remote_procedure_call_qm,
		    error_message,error_1);
	else if (calling_g2gl_call_invocation_qm)
	    handle_g2gl_call_invocation_error(calling_g2gl_call_invocation_qm,
		    error_message,error_1);
	else if (registered_and_active_default_error_handler_p() && 
		pass_loop_check_for_user_defined_default_error_handler_p(code_body_invocation) 
		&& invoke_user_defined_default_error_handler(error_1,
		error_message));
	else {
	    if (FIXNUM_LE(error_level,Warning_message_level) &&  
		    !TRUEP(Debugging_reset)) {
		if ( !TRUEP(Defer_notifications_qm))
		    break_out_of_debug_messages();
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
			      tformat(2,string_constant_41,error_message);
			      tformat(1,string_constant_46);
			      write_procedure_invocation_instance_from_slot(base_of_stack,
				      Nil);
			      tformat(1,string_constant_47);
			      temp = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    notify_user_1(temp);
		    if (Snapshots_of_related_blocks) {
			reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
			Snapshots_of_related_blocks = Nil;
		    }
		  POP_SPECIAL();
		POP_SPECIAL();
	    }
	    reclaim_error_text(error_message);
	    if (SIMPLE_VECTOR_P(error_1) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(error_1)) > (SI_Long)2L 
		    &&  !EQ(ISVREF(error_1,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(error_1,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? (SI_Long)0L != (IFIX(ISVREF(error_1,(SI_Long)5L)) 
		    & (SI_Long)262144L) : TRUEP(Nil))
		delete_frame(error_1);
	}
	abort_procedure_invocation(2,base_of_stack,T);
    }
    return reclaim_error_text(error_text_local);
}

/* PROPAGATE-ERROR-TO-CODE-BODY-INVOCATION */
Object propagate_error_to_code_body_invocation(code_body_invocation,
	    error_1,error_level,error_message)
    Object code_body_invocation, error_1, error_level, error_message;
{
    x_note_fn_call(160,187);
    return signal_code_body_invocation_error(9,code_body_invocation,
	    error_1,error_level,error_message,Nil,Nil,Nil,Nil,Nil);
}

/* FIND-ERROR-HANDLER-FOR-CODE-BODY-INVOCATION */
Object find_error_handler_for_code_body_invocation(error_name_or_object,
	    code_body_invocation)
    Object error_name_or_object, code_body_invocation;
{
    Object x2, class_1, caller_qm, code_body, code_body_error_handler_spec_qm;
    Object type_name, temp_1, gensymed_symbol;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(160,188);
    if (SIMPLE_VECTOR_P(error_name_or_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(error_name_or_object)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(error_name_or_object,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(error_name_or_object,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    class_1 = temp ? ISVREF(ISVREF(error_name_or_object,(SI_Long)1L),
	    (SI_Long)1L) : 
	    map_error_symbol_to_class_name(error_name_or_object);
    caller_qm = code_body_invocation;
    code_body = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Code_body,Qcode_body,code_body,0);
      code_body_error_handler_spec_qm = Nil;
    next_loop:
      if (SIMPLE_VECTOR_P(caller_qm)) {
	  type_name = ISVREF(caller_qm,(SI_Long)0L);
	  temp = EQ(type_name,
		  Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	  if (temp);
	  else
	      temp = EQ(type_name,
		      Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
      }
      else
	  temp = TRUEP(Nil);
      if ( !temp)
	  goto end_loop;
      Code_body = ISVREF(caller_qm,(SI_Long)8L);
      code_body_error_handler_spec_qm = ISVREF(Code_body,(SI_Long)10L);
      if (code_body_error_handler_spec_qm) {
	  temp_1 = THIRD(code_body_error_handler_spec_qm);
	  if (CONSP(temp_1)) {
	      gensymed_symbol = 
		      lookup_global_or_kb_specific_property_value(class_1,
		      Class_description_gkbprop);
	      if (gensymed_symbol) {
		  temp_1 = THIRD(code_body_error_handler_spec_qm);
		  temp = TRUEP(memq_function(SECOND(temp_1),
			  ISVREF(gensymed_symbol,(SI_Long)2L)));
	      }
	      else
		  temp = TRUEP(Nil);
	  }
	  else
	      temp = TRUEP(T);
      }
      else
	  temp = TRUEP(Nil);
      if (temp ? TRUEP(ISVREF(caller_qm,(SI_Long)12L)) : TRUEP(Nil)) {
	  result = VALUES_1(caller_qm);
	  goto end_1;
      }
      caller_qm = ISVREF(caller_qm,(SI_Long)12L);
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* HANDLE-ERROR-IN-CODE-BODY-INVOCATION */
Object handle_error_in_code_body_invocation(protected_code_body_invocation,
	    erroneous_code_body_invocation,error_name_or_error_object,
	    error_message)
    Object protected_code_body_invocation, erroneous_code_body_invocation;
    Object error_name_or_error_object, error_message;
{
    Object handling_code_body_invocation, called_code_bodies, handler_spec, x2;
    Object new_style_error_qm, temp, error_argument, error_text_argument;
    Object called_code_body, ab_loop_list_, gensymed_symbol, handler_address;
    Object error_name_var_spot, error_text_var_spot, svref_new_value;
    Object text_string;
    char new_style_handler_qm, old_style_handler_qm;
    Object result;

    x_note_fn_call(160,189);
    handling_code_body_invocation = ISVREF(protected_code_body_invocation,
	    (SI_Long)12L);
    called_code_bodies = 
	    copy_list_using_proc_conses_1(ISVREF(handling_code_body_invocation,
	    (SI_Long)13L));
    handler_spec = ISVREF(ISVREF(protected_code_body_invocation,
	    (SI_Long)8L),(SI_Long)10L);
    if (SIMPLE_VECTOR_P(error_name_or_error_object) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(error_name_or_error_object)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(error_name_or_error_object,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(error_name_or_error_object,(SI_Long)1L);
	new_style_error_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	new_style_error_qm = Nil;
    temp = THIRD(handler_spec);
    new_style_handler_qm = CONSP(temp);
    old_style_handler_qm =  !new_style_handler_qm;
    result = map_between_error_styles(error_name_or_error_object,
	    error_message,new_style_error_qm,new_style_handler_qm ? T : Nil);
    MVS_2(result,error_argument,error_text_argument);
    called_code_body = Nil;
    ab_loop_list_ = called_code_bodies;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    called_code_body = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    abort_code_body_invocation(called_code_body);
    goto next_loop;
  end_loop:;
    reclaim_proc_list_1(called_code_bodies);
    gensymed_symbol = handler_spec;
    handler_address = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    error_name_var_spot = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    error_text_var_spot = CAR(gensymed_symbol);
    svref_new_value = 
	    FIXNUM_LE(ISVREF(ISVREF(ISVREF(handling_code_body_invocation,
	    (SI_Long)8L),(SI_Long)9L),(SI_Long)1L),
	    Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(ISVREF(handling_code_body_invocation,
	    (SI_Long)8L),(SI_Long)9L),IFIX(FIXNUM_ADD(handler_address,
	    Managed_array_index_offset))) : 
	    ISVREF(ISVREF(ISVREF(ISVREF(handling_code_body_invocation,
	    (SI_Long)8L),(SI_Long)9L),(IFIX(handler_address) >>  -  - 
	    (SI_Long)10L) + (SI_Long)2L),IFIX(handler_address) & 
	    (SI_Long)1023L);
    SVREF(handling_code_body_invocation,FIX((SI_Long)3L)) = svref_new_value;
    if (SYMBOLP(error_argument))
	modify_code_body_environment_var_spot(handling_code_body_invocation,
		error_name_var_spot,error_argument);
    else {
	modify_code_body_environment_var_spot(handling_code_body_invocation,
		error_name_var_spot,error_argument);
	update_code_body_invocation_frame_serial_number(handling_code_body_invocation);
    }
    if (old_style_handler_qm) {
	text_string = CONSP(error_text_argument) ? 
		FIRST(error_text_argument) : error_text_argument;
	reclaim_error_text_but_not_string(error_text_argument);
	modify_code_body_environment_var_spot(handling_code_body_invocation,
		error_text_var_spot,text_string);
	if (new_style_error_qm) {
	    if ((SI_Long)0L != (IFIX(ISVREF(error_name_or_error_object,
		    (SI_Long)5L)) & (SI_Long)262144L))
		delete_frame(error_name_or_error_object);
	}
    }
    else if (new_style_error_qm)
	reclaim_error_text(error_message);
    else
	reclaim_error_text_but_not_string(error_message);
    return wake_up_code_body_invocation_immediately(handling_code_body_invocation);
}

static Object Qnever;              /* never */

/* CLEAR-COMPUTATION-CONTEXT-VARIABLES */
Object clear_computation_context_variables()
{
    x_note_fn_call(160,190);
    Current_computation_flags = FIX((SI_Long)0L);
    Current_computation_activity = FIX((SI_Long)0L);
    Current_computation_component_particulars = Nil;
    Current_computation_frame = Nil;
    Current_computation_instance = Nil;
    Current_computation_style = Nil;
    Current_environment = Nil;
    Evaluating_simulator_procedure_qm = Nil;
    if (Explanation_variables)
	reclaim_explanation_variables();
    Stack_expiration = Qnever;
    Variables_that_did_not_have_values = Nil;
    return VALUES_1(Nil);
}

static Object Qdefault;            /* default */

static Object Qsimulated_value;    /* simulated-value */

/* ENTER-COMPUTATION-CONTEXT-FOR-INVOCATION */
Object enter_computation_context_for_invocation(invocation,
	    dont_validate_environment_qm)
    Object invocation, dont_validate_environment_qm;
{
    Object current_procedure_invocation, procedure_qm_1, default_time_limit_qm;
    Object specific_time_limit_qm, uninterrupted_procedure_time_error_qm;
    Object gensymed_symbol_2, temp;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(160,191);
    current_procedure_invocation = ISVREF(invocation,(SI_Long)11L);
    procedure_qm_1 = ISVREF(current_procedure_invocation,(SI_Long)23L);
    default_time_limit_qm = ISVREF(Timing_parameters,(SI_Long)30L);
    specific_time_limit_qm = procedure_qm_1 ? ISVREF(procedure_qm_1,
	    (SI_Long)22L) : Nil;
    uninterrupted_procedure_time_error_qm = EQ(specific_time_limit_qm,
	    Qdefault) ? (default_time_limit_qm ? 
	    fixnum_time_interval(FIX((SI_Long)1000L * 
	    IFIX(default_time_limit_qm))) : Nil) : specific_time_limit_qm ?
	     fixnum_time_interval(FIX((SI_Long)1000L * 
	    IFIX(specific_time_limit_qm))) : Nil;
    gensymed_symbol = (SI_Long)384L;
    gensymed_symbol_1 = (SI_Long)0L != (IFIX(ISVREF(procedure_qm_1,
	    (SI_Long)4L)) & (SI_Long)33554432L) ? (SI_Long)16L : (SI_Long)0L;
    Current_computation_flags = FIX(gensymed_symbol + gensymed_symbol_1);
    Current_computation_activity = FIX((SI_Long)0L);
    Current_computation_component_particulars = Nil;
    Current_computation_style = Nil;
    if (Explanation_variables)
	reclaim_explanation_variables();
    Stack_expiration = Qnever;
    Variables_that_did_not_have_values = Nil;
    Current_computation_frame = procedure_qm_1;
    Current_computation_instance = invocation;
    Evaluating_simulator_procedure_qm = 
	    ISVREF(current_procedure_invocation,(SI_Long)25L);
    Current_environment = Evaluating_simulator_procedure_qm ? 
	    Qsimulated_value : Qprocedure;
    if (Profiling_enabled_qm)
	posit_profiling_structure(procedure_qm_1);
    if ( !TRUEP(dont_validate_environment_qm))
	validate_computation_instance_environment(invocation,Nil,Nil);
    gensymed_symbol_2 = get_lookup_slot_value(Current_computation_frame,
	    Qtracing_and_breakpoints);
    if ((gensymed_symbol_2 || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(Current_computation_frame,
		gensymed_symbol_2);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) {
	    temp = Current_computation_frame;
	    issue_tracing_and_breakpoints_entry_message(temp,
		    enter_procedure_invocation_trace_message(current_procedure_invocation,
		    invocation));
	}
    }
    return VALUES_1(uninterrupted_procedure_time_error_qm);
}

/* EXIT-COMPUTATION-CONTEXT-FOR-CODE-BODY-INVOCATION */
Object exit_computation_context_for_code_body_invocation(code_body_invocation,
	    program_counter,suppress_exit_context_qm)
    Object code_body_invocation, program_counter, suppress_exit_context_qm;
{
    Object temp;

    x_note_fn_call(160,192);
    SVREF(code_body_invocation,FIX((SI_Long)3L)) = program_counter;
    if ( !TRUEP(suppress_exit_context_qm)) {
	if (Saved_warning_level) {
	    if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		    IFIX(Tracing_message_level) > (SI_Long)0L) && 
		    ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		    !TRUEP(in_order_p(Current_computation_frame))) {
		temp = Current_computation_frame;
		issue_tracing_and_breakpoint_exit_message(temp,
			code_body_invocation_exit_breakpoint_context_message(Current_computation_frame));
	    }
	    Warning_message_level = Saved_warning_level;
	    Tracing_message_level = Saved_tracing_level;
	    Breakpoint_level = Saved_breakpoint_level;
	    Source_stepping_level = Saved_source_stepping_level;
	}
    }
    if ( !(SIMPLE_VECTOR_P(code_body_invocation) && 
	    EQ(ISVREF(code_body_invocation,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)))
	return update_code_body_invocation_frame_serial_number(code_body_invocation);
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Check_for_circular_formula_paths_qm, Qcheck_for_circular_formula_paths_qm);

static Object Qcell_array;         /* cell-array */

static Object Qempty_expression_cell;  /* empty-expression-cell */

static Object Qparent_frame;       /* parent-frame */

static Object Qcell_array_element;  /* cell-array-element */

static Object Qsimulator;          /* simulator */

static Object Qinference_engine;   /* inference-engine */

static Object string_constant_48;  /* "Executing ~NF for ~NF." */

static Object string_constant_49;  /* "Executing formula for ~NF." */

/* ENTER-COMPUTATION-CONTEXT-FOR-VARIABLE-FORMULA */
Object enter_computation_context_for_variable_formula(formula_invocation)
    Object formula_invocation;
{
    Object variable, generic_formula_qm, frame_serial_number, gensymed_symbol;
    Object xa, ya, expression_cell_parent, g2_cell_array, expression_cell;
    Object byte_code_body, computation_style_qm, backward_chaining_allowed_qm;
    Object network_access_attempt_qm, temp_1, new_vector, local_var_vector;
    Object svref_new_value;
    SI_Long index_1, ab_loop_bind_, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long gensymed_symbol_6;
    char temp;

    x_note_fn_call(160,193);
    variable = ISVREF(formula_invocation,(SI_Long)8L);
    generic_formula_qm = ISVREF(formula_invocation,(SI_Long)9L);
    frame_serial_number = ISVREF(formula_invocation,(SI_Long)10L);
    if (generic_formula_qm) {
	gensymed_symbol = ISVREF(generic_formula_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(generic_formula_qm) ? 
		EQ(ISVREF(generic_formula_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    expression_cell_parent = temp ? generic_formula_qm : variable;
    g2_cell_array = 
	    get_lookup_slot_value_given_default(expression_cell_parent,
	    Qcell_array,Nil);
    expression_cell = g2_cell_array ? 
	    (FIXNUM_LE(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(SI_Long)0L + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(ISVREF(g2_cell_array,(SI_Long)3L),(SI_Long)2L),
	    (SI_Long)0L)) : Nil;
    byte_code_body = expression_cell ? ISVREF(expression_cell,
	    (SI_Long)10L) : Nil;
    computation_style_qm = expression_cell ? ISVREF(expression_cell,
	    (SI_Long)3L) : Nil;
    backward_chaining_allowed_qm = computation_style_qm ? 
	    ISVREF(computation_style_qm,(SI_Long)24L) : Nil;
    network_access_attempt_qm = computation_style_qm ? 
	    ISVREF(computation_style_qm,(SI_Long)32L) : Nil;
    if (byte_code_body) {
	temp_1 = var_count(ISVREF(byte_code_body,(SI_Long)4L));
	new_vector = 
		allocate_managed_simple_vector(buffer_size_for_partial_buffer(temp_1,
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
	local_var_vector = new_vector;
    }
    else
	local_var_vector = Nil;
    if (generic_formula_qm) {
	gensymed_symbol = ISVREF(generic_formula_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(generic_formula_qm) ? 
		EQ(ISVREF(generic_formula_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	cancel_formula_for_backward_chaining(variable);
	return VALUES_1(Nil);
    }
    if ( !TRUEP(expression_cell) ||  ! !EQ(ISVREF(expression_cell,
	    (SI_Long)2L),Qempty_expression_cell)) {
	cancel_formula_for_backward_chaining(variable);
	return VALUES_1(Nil);
    }
    SVREF(formula_invocation,FIX((SI_Long)1L)) = byte_code_body;
    svref_new_value = ISVREF(byte_code_body,(SI_Long)3L);
    SVREF(formula_invocation,FIX((SI_Long)4L)) = svref_new_value;
    if (EQ(expression_cell_parent,generic_formula_qm)) {
	svref_new_value = get_lookup_slot_value_given_default(variable,
		Qparent_frame,Nil);
	SVREF(local_var_vector,FIX((SI_Long)1L)) = svref_new_value;
    }
    SVREF(formula_invocation,FIX((SI_Long)2L)) = local_var_vector;
    ISVREF(formula_invocation,(SI_Long)3L) = FIX((SI_Long)0L);
    gensymed_symbol_1 = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) 
	    & (SI_Long)1048576L) && 
	    explanation_related_features_enabled_func_qm() ? (SI_Long)1L : 
	    (SI_Long)0L;
    gensymed_symbol_2 = (SI_Long)0L != (IFIX(ISVREF(expression_cell_parent,
	    (SI_Long)4L)) & (SI_Long)33554432L) ? (SI_Long)16L : (SI_Long)0L;
    gensymed_symbol_3 = EQ(network_access_attempt_qm,Qwrite) ? 
	    (SI_Long)32L : (SI_Long)0L;
    gensymed_symbol_4 = EQ(network_access_attempt_qm,Qread) ? (SI_Long)64L 
	    : (SI_Long)0L;
    gensymed_symbol_5 =  !TRUEP(backward_chaining_allowed_qm) ? 
	    (SI_Long)128L : (SI_Long)0L;
    gensymed_symbol_6 =  !TRUEP(backward_chaining_allowed_qm) ? 
	    (SI_Long)256L : (SI_Long)0L;
    Current_computation_flags = FIX(gensymed_symbol_1 + gensymed_symbol_2 
	    + gensymed_symbol_3 + gensymed_symbol_4 + gensymed_symbol_5 + 
	    gensymed_symbol_6);
    Current_computation_activity = FIX((SI_Long)0L);
    Current_computation_component_particulars = 
	    slot_value_list_2(Qcell_array_element,ISVREF(expression_cell,
	    (SI_Long)5L));
    svref_new_value = Current_computation_component_particulars;
    SVREF(formula_invocation,FIX((SI_Long)12L)) = svref_new_value;
    Current_computation_frame = expression_cell_parent;
    Current_computation_instance = formula_invocation;
    Current_computation_style = computation_style_qm;
    Current_environment = EQ(Qsimulator,ISVREF(Current_computation_style,
	    (SI_Long)27L)) ? Qsimulated_value : Qinference_engine;
    Evaluating_simulator_procedure_qm = Nil;
    Stack_expiration = Qnever;
    Variables_that_did_not_have_values = Nil;
    if (Explanation_variables)
	reclaim_explanation_variables();
    Check_for_circular_formula_paths_qm = ISVREF(variable,(SI_Long)35L) ? 
	    T : Nil;
    gensymed_symbol = get_lookup_slot_value(expression_cell_parent,
	    Qtracing_and_breakpoints);
    if ((gensymed_symbol || Saved_warning_level ||  
	    !FIXNUMP(Breakpoint_level) || IFIX(Breakpoint_level) > 
	    (SI_Long)0L || IFIX(Tracing_message_level) > (SI_Long)0L || 
	    IFIX(Source_stepping_level) > (SI_Long)0L) &&  
	    !TRUEP(Debugging_reset) && ISVREF(Debugging_parameters,
	    (SI_Long)22L)) {
	modify_tracing_and_breakpoints_context_on_entry(expression_cell_parent,
		gensymed_symbol);
	if (IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L)
	    issue_tracing_and_breakpoints_entry_message(expression_cell_parent,
		    generic_formula_qm ? tformat_text_string(3,
		    string_constant_48,generic_formula_qm,variable) : 
		    tformat_text_string(2,string_constant_49,variable));
    }
    open_wake_up_collection_function(Nil);
    return VALUES_1(Nil);
}

static Object string_constant_50;  /* "Returning from execution of ~NF for ~NF." */

static Object string_constant_51;  /* "Returning from execution of the formula of ~NF." */

static Object Qab_slot_value;      /* slot-value */

/* EXIT-COMPUTATION-CONTEXT-FOR-VARIABLE-FORMULA */
Object exit_computation_context_for_variable_formula(formula_invocation)
    Object formula_invocation;
{
    Object generic_formula_qm, variable, component_particulars;
    Object gensymed_symbol, slot_value_list, slot_value_list_tail;
    Object slot_value_cons, temp, svref_arg_2, structure_being_reclaimed;
    Declare_special(2);

    x_note_fn_call(160,194);
    generic_formula_qm = ISVREF(formula_invocation,(SI_Long)9L);
    variable = ISVREF(formula_invocation,(SI_Long)8L);
    component_particulars = ISVREF(formula_invocation,(SI_Long)12L);
    gensymed_symbol = generic_formula_qm;
    if (gensymed_symbol);
    else
	gensymed_symbol = variable;
    if (Saved_warning_level) {
	if ((IFIX(Breakpoint_level) > (SI_Long)0L || 
		IFIX(Tracing_message_level) > (SI_Long)0L) && 
		ISVREF(Debugging_parameters,(SI_Long)22L) &&  
		!TRUEP(in_order_p(gensymed_symbol)))
	    issue_tracing_and_breakpoint_exit_message(gensymed_symbol,
		    generic_formula_qm ? tformat_text_string(3,
		    string_constant_50,generic_formula_qm,variable) : 
		    tformat_text_string(2,string_constant_51,variable));
	Warning_message_level = Saved_warning_level;
	Tracing_message_level = Saved_tracing_level;
	Breakpoint_level = Saved_breakpoint_level;
	Source_stepping_level = Saved_source_stepping_level;
    }
    slot_value_list = component_particulars;
    slot_value_list_tail = M_CDR(component_particulars);
    if (slot_value_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	slot_value_cons = slot_value_list;
      next_loop:
	inline_note_reclaim_cons(slot_value_cons,Qab_slot_value);
	if (EQ(slot_value_cons,slot_value_list_tail))
	    goto end_1;
	else if ( !TRUEP(slot_value_cons))
	    goto end_1;
	else
	    slot_value_cons = CDR(slot_value_cons);
	goto next_loop;
      end_loop:
      end_1:;
    }
    if (ISVREF(Available_slot_value_conses_tail_vector,
	    IFIX(Current_thread_index))) {
	temp = ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index));
	M_CDR(temp) = slot_value_list;
	temp = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_list_tail;
    }
    else {
	temp = Available_slot_value_conses_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_list;
	temp = Available_slot_value_conses_tail_vector;
	svref_arg_2 = Current_thread_index;
	SVREF(temp,svref_arg_2) = slot_value_list_tail;
    }
    M_CDR(slot_value_list_tail) = Nil;
    reclaim_environment_vector(ISVREF(formula_invocation,(SI_Long)2L));
    clear_computation_context_variables();
    ISVREF(variable,(SI_Long)34L) = Nil;
    inline_note_reclaim_cons(formula_invocation,Nil);
    structure_being_reclaimed = formula_invocation;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    1);
      gensymed_symbol = Nil;
    next_loop_1:
      gensymed_symbol = ISVREF(formula_invocation,(SI_Long)7L);
      if (CAS_SVREF(formula_invocation,(SI_Long)7L,gensymed_symbol,Nil)) {
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
	  goto end_2;
      }
      goto next_loop_1;
    end_loop_1:
    end_2:;
      SVREF(formula_invocation,FIX((SI_Long)7L)) = Nil;
      reclaim_frame_serial_number(ISVREF(formula_invocation,(SI_Long)10L));
      SVREF(formula_invocation,FIX((SI_Long)10L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_formula_invocations_vector,
	    IFIX(Current_thread_index));
    SVREF(formula_invocation,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_formula_invocations_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = formula_invocation;
    return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

/* ENTER-OR-RECLAIM-COMPUTATION-INSTANCE-CONTEXT */
Object enter_or_reclaim_computation_instance_context(computation_instance)
    Object computation_instance;
{
    Object temp, type_name;
    char temp_1;

    x_note_fn_call(160,195);
    if (SIMPLE_VECTOR_P(computation_instance) && 
	    EQ(ISVREF(computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct))
	temp = enter_or_reclaim_rule_instance_context(computation_instance,
		Nil);
    else {
	if (SIMPLE_VECTOR_P(computation_instance)) {
	    type_name = ISVREF(computation_instance,(SI_Long)0L);
	    temp_1 = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp_1);
	    else
		temp_1 = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = 
		    enter_computation_context_for_invocation(computation_instance,
		    Nil);
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_formula_invocation_g2_struct))
	    temp = 
		    enter_computation_context_for_variable_formula(computation_instance);
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

static Object array_constant_16;   /* # */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

/* ENTER-PROCEDURE-INVOCATION-TRACE-MESSAGE */
Object enter_procedure_invocation_trace_message(current_procedure_invocation,
	    code_body_invocation)
    Object current_procedure_invocation, code_body_invocation;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object code_body_caller, type_name;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);
    Object result;

    x_note_fn_call(160,196);
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
	      Forgive_long_procedure_instruction_qm = T;
	      if (IFIX(ISVREF(code_body_invocation,(SI_Long)3L)) == 
		      (SI_Long)0L &&  
		      !(SIMPLE_VECTOR_P(code_body_invocation) && 
		      EQ(ISVREF(code_body_invocation,(SI_Long)0L),
		      Qg2_defstruct_structure_name_code_body_invocation_g2_struct))) 
			  {
		  twrite_beginning_of_wide_string(array_constant_16,
			  FIX((SI_Long)22L));
		  write_procedure_invocation_instance_from_slot(current_procedure_invocation,
			  Nil);
		  code_body_caller = ISVREF(code_body_invocation,(SI_Long)12L);
		  if ( !TRUEP(code_body_caller))
		      twrite_beginning_of_wide_string(array_constant_17,
			      FIX((SI_Long)36L));
		  else {
		      if (SIMPLE_VECTOR_P(code_body_caller)) {
			  type_name = ISVREF(code_body_caller,(SI_Long)0L);
			  temp = EQ(type_name,
				  Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
			  if (temp);
			  else
			      temp = EQ(type_name,
				      Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp) {
			  twrite_beginning_of_wide_string(array_constant_18,
				  FIX((SI_Long)14L));
			  write_procedure_invocation_instance_from_slot(ISVREF(code_body_caller,
				  (SI_Long)11L),Nil);
		      }
		      else
			  twrite_beginning_of_wide_string(array_constant_19,
				  FIX((SI_Long)39L));
		  }
	      }
	      else {
		  twrite_beginning_of_wide_string(array_constant_20,
			  FIX((SI_Long)22L));
		  write_procedure_invocation_instance_from_slot(current_procedure_invocation,
			  Nil);
	      }
	      twrite_character(FIX((SI_Long)46L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qmethod_declaration;  /* method-declaration */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* INITIALIZE-FOR-METHOD-DECLARATION */
Object initialize_for_method_declaration(method_declaration)
    Object method_declaration;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,197);
    frame = method_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmethod_declaration)) {
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
    return update_frame_status(method_declaration,
	    get_lookup_slot_value_given_default(method_declaration,
	    Qname_or_names_for_frame,Nil) ? Qnil : Qincomplete,Nil);
}

/* NOTE-NAME-CHANGE-FOR-METHOD-DECLARATION */
Object note_name_change_for_method_declaration(method_declaration,
	    old_names,initializing_p)
    Object method_declaration, old_names, initializing_p;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,198);
    update_frame_status(method_declaration,
	    get_lookup_slot_value_given_default(method_declaration,
	    Qname_or_names_for_frame,Nil) ? Qnil : Qincomplete,Nil);
    frame = method_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)10L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmethod_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    if (method_function_qm)
	return inline_funcall_3(method_function_qm,frame,old_names,
		initializing_p);
    else
	return VALUES_1(Nil);
}

/* METHOD-FOR-THIS-INVOCATION */
Object method_for_this_invocation(invocation)
    Object invocation;
{
    Object procedure, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(160,199);
    procedure = SIMPLE_VECTOR_P(invocation) && EQ(ISVREF(invocation,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct) ? 
	    ISVREF(invocation,(SI_Long)23L) : Nil;
    if (procedure) {
	sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
	return VALUES_1(procedure);
    else
	return VALUES_1(Nil);
}

/* LOCK-FOR-THIS-METHOD-INVOCATION */
Object lock_for_this_method_invocation(invocation)
    Object invocation;
{
    Object locals;

    x_note_fn_call(160,200);
    locals = ISVREF(invocation,(SI_Long)2L);
    if (locals)
	return VALUES_1(ISVREF(locals,(SI_Long)0L));
    else
	return VALUES_1(Nil);
}

/* MAYBE-SET-LOCK-FOR-INVOCATION */
Object maybe_set_lock_for_invocation(invocation,procedure)
    Object invocation, procedure;
{
    Object sub_class_bit_vector, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(160,201);
    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
    if (temp ? TRUEP(ISVREF(procedure,(SI_Long)32L)) : TRUEP(Nil)) {
	svref_new_value = 
		get_reference_to_item(lock_for_this_method_invocation(invocation));
	return VALUES_1(SVREF(invocation,FIX((SI_Long)20L)) = svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

static Object Qinvocation_locking_this_object;  /* invocation-locking-this-object */

/* RELEASE-LOCK */
Object release_lock(invocation)
    Object invocation;
{
    Object lock_reference_qm, item_or_value, lock_qm, invocations_list;
    Object waiting_invocation, ab_loop_list_;

    x_note_fn_call(160,202);
    lock_reference_qm = ISVREF(invocation,(SI_Long)20L);
    item_or_value = lock_reference_qm;
    lock_qm = CONSP(item_or_value) && EQ(M_CDR(item_or_value),
	    Qitem_reference) ? ISVREF(M_CAR(item_or_value),(SI_Long)3L) : 
	    item_or_value;
    if (lock_reference_qm) {
	reclaim_evaluation_item_reference(lock_reference_qm);
	SVREF(invocation,FIX((SI_Long)20L)) = Nil;
    }
    if (lock_qm && EQ(get_lookup_slot_value_given_default(lock_qm,
	    Qinvocation_locking_this_object,Nil),invocation))
	set_non_savable_lookup_slot_value(lock_qm,
		Qinvocation_locking_this_object,Nil);
    invocations_list = ISVREF(invocation,(SI_Long)18L);
    waiting_invocation = Nil;
    ab_loop_list_ = invocations_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    waiting_invocation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    SVREF(waiting_invocation,FIX((SI_Long)19L)) = Nil;
    wake_up_code_body_invocation(waiting_invocation);
    goto next_loop;
  end_loop:;
    reclaim_proc_list_1(invocations_list);
    return VALUES_1(SVREF(invocation,FIX((SI_Long)18L)) = Nil);
}

static Object Klock_aquired;       /* :lock-aquired */

static Object Klock_held_by_thread;  /* :lock-held-by-thread */

/* QUEUE-INVOCATION-FOR-LOCK-IF-NECESSARY */
Object queue_invocation_for_lock_if_necessary(invocation)
    Object invocation;
{
    Object type_name, item_or_value, lock_qm, locker_qm;
    Object proc_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    char temp;

    x_note_fn_call(160,203);
    if (SIMPLE_VECTOR_P(invocation)) {
	type_name = ISVREF(invocation,(SI_Long)0L);
	temp = EQ(type_name,
		Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	if (temp);
	else
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	item_or_value = ISVREF(invocation,(SI_Long)20L);
	lock_qm = CONSP(item_or_value) && EQ(M_CDR(item_or_value),
		Qitem_reference) ? ISVREF(M_CAR(item_or_value),
		(SI_Long)3L) : item_or_value;
	if (lock_qm) {
	    locker_qm = get_lookup_slot_value_given_default(lock_qm,
		    Qinvocation_locking_this_object,Nil);
	    if ( !TRUEP(locker_qm)) {
		set_non_savable_lookup_slot_value(lock_qm,
			Qinvocation_locking_this_object,invocation);
		if ( !TRUEP(ISVREF(invocation,(SI_Long)21L)))
		    SVREF(invocation,FIX((SI_Long)21L)) = invocation;
		return VALUES_1(Klock_aquired);
	    }
	    else if (EQ(ISVREF(locker_qm,(SI_Long)21L),ISVREF(invocation,
		    (SI_Long)21L)))
		return VALUES_1(Klock_held_by_thread);
	    else {
		proc_push_modify_macro_arg = invocation;
		car_1 = proc_push_modify_macro_arg;
		cdr_1 = ISVREF(locker_qm,(SI_Long)18L);
		svref_new_value = proc_cons_1(car_1,cdr_1);
		SVREF(locker_qm,FIX((SI_Long)18L)) = svref_new_value;
		SVREF(invocation,FIX((SI_Long)19L)) = locker_qm;
		return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(T);
    }
    else
	return VALUES_1(T);
}

/* PROCEDURE-METHOD-NAME-FUNCTION */
Object procedure_method_name_function(method)
    Object method;
{
    x_note_fn_call(160,204);
    return VALUES_1(ISVREF(method,(SI_Long)30L));
}

/* PROCEDURE-METHOD-CLASS-FUNCTION */
Object procedure_method_class_function(method)
    Object method;
{
    x_note_fn_call(160,205);
    return VALUES_1(ISVREF(method,(SI_Long)31L));
}

static Object Qab_method;          /* method */

/* INITIALIZE-AFTER-READING-FOR-METHOD */
Object initialize_after_reading_for_method(method)
    Object method;
{
    Object frame, sub_vector_qm, method_function_qm, name_qm, class_qm;
    Object new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,206);
    frame = method;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)4L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qab_method)) {
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
    if ( !(IFIX(Kb_flags) >= (SI_Long)261L)) {
	name_qm = ISVREF(method,(SI_Long)30L);
	class_qm = ISVREF(method,(SI_Long)31L);
	if (class_qm && name_qm) {
	    new_value = make_unique_slot_name_symbol(class_qm,name_qm);
	    return initialize_slot_description_value(method,
		    get_slot_description_of_class_description_function(Qname_or_names_for_frame,
		    ISVREF(method,(SI_Long)1L),Nil),new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-METHOD */
Object cleanup_for_method(method)
    Object method;
{
    Object frame, sub_vector_qm, method_function_qm, method_name_qm;
    Object method_class_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(160,207);
    frame = method;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qab_method)) {
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
    method_name_qm = ISVREF(method,(SI_Long)30L);
    method_class_qm = ISVREF(method,(SI_Long)31L);
    if (method_name_qm && method_class_qm)
	unregister_method_declaration(method_name_qm,method,method_class_qm);
    if (method_name_qm)
	return analyze_compiled_items_for_consistency(method_name_qm);
    else
	return VALUES_1(Nil);
}

static Object Qprocedure_method_name;  /* procedure-method-name */

/* PUT-PROCEDURE-METHOD-NAME */
Object put_procedure_method_name(method,method_name,initializing_qm)
    Object method, method_name, initializing_qm;
{
    Object method_class_qm;

    x_note_fn_call(160,208);
    method_class_qm = ISVREF(method,(SI_Long)31L);
    if (initializing_qm) {
	if (method_name && method_class_qm)
	    register_method_declaration(method_name,method,method_class_qm);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(method,Qprocedure_method_name);
    SVREF(method,FIX((SI_Long)30L)) = method_name;
    return VALUES_1(method_name);
}

static Object Qprocedure_method_class;  /* procedure-method-class */

/* PUT-PROCEDURE-METHOD-CLASS */
Object put_procedure_method_class(method,method_class,initializing_qm)
    Object method, method_class, initializing_qm;
{
    Object method_name_qm;

    x_note_fn_call(160,209);
    if (initializing_qm) {
	method_name_qm = ISVREF(method,(SI_Long)30L);
	if (method_class && method_name_qm)
	    register_method_declaration(method_name_qm,method,method_class);
    }
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(method,Qprocedure_method_class);
    SVREF(method,FIX((SI_Long)31L)) = method_class;
    return VALUES_1(method_class);
}

static Object string_constant_52;  /* "~(~nq~)" */

static Object array_constant_21;   /* # */

/* WRITE-PROCEDURE-METHOD-NAME-FROM-SLOT */
Object write_procedure_method_name_from_slot(value,method)
    Object value, method;
{
    Object method_class_qm;

    x_note_fn_call(160,210);
    method_class_qm = ISVREF(method,(SI_Long)31L);
    if (value && method_class_qm)
	return tformat(3,string_constant_52,value,method_class_qm);
    else
	return twrite_beginning_of_wide_string(array_constant_21,
		FIX((SI_Long)4L));
}

Object Procedure_methods_of_class_kbprop = UNBOUND;

/* GET-PROCEDURE-METHODS-OF-CLASS */
Object get_procedure_methods_of_class(class_name)
    Object class_name;
{
    x_note_fn_call(160,211);
    return lookup_kb_specific_property_value(class_name,
	    Procedure_methods_of_class_kbprop);
}

Object Classes_of_procedure_method_kbprop = UNBOUND;

/* REGISTER-METHOD-DECLARATION */
Object register_method_declaration(specific_method_name,
	    specific_method_frame,class_1)
    Object specific_method_name, specific_method_frame, class_1;
{
    Object named_procedure_method_list_qm, new_method_alist;
    Object procedure_methods_qm, temp;

    x_note_fn_call(160,212);
    named_procedure_method_list_qm = 
	    get_named_procedure_methods_for_class(specific_method_name,
	    class_1);
    if ( !TRUEP(named_procedure_method_list_qm)) {
	new_method_alist = 
		gensym_cons_1(gensym_list_2(specific_method_name,
		specific_method_frame),Nil);
	procedure_methods_qm = lookup_kb_specific_property_value(class_1,
		Procedure_methods_of_class_kbprop);
	temp =  !TRUEP(procedure_methods_qm) ? new_method_alist : 
		nconc2(procedure_methods_qm,new_method_alist);
	mutate_kb_specific_property_value(class_1,temp,
		Procedure_methods_of_class_kbprop);
	temp = increment_class_count_of_method(specific_method_name,class_1);
    }
    else if (memq_function(specific_method_frame,
	    named_procedure_method_list_qm))
	temp = Nil;
    else {
	nconc2(named_procedure_method_list_qm,
		gensym_cons_1(specific_method_frame,Nil));
	temp = increment_class_count_of_method(specific_method_name,class_1);
    }
    return VALUES_1(temp);
}

/* UNREGISTER-METHOD-DECLARATION */
Object unregister_method_declaration(specific_method_name,
	    specific_method_frame,class_1)
    Object specific_method_name, specific_method_frame, class_1;
{
    Object named_procedure_method_list_qm, procedure_methods_qm, temp;

    x_note_fn_call(160,213);
    named_procedure_method_list_qm = 
	    get_named_procedure_methods_for_class(specific_method_name,
	    class_1);
    procedure_methods_qm = lookup_kb_specific_property_value(class_1,
	    Procedure_methods_of_class_kbprop);
    if (named_procedure_method_list_qm && 
	    memq_function(specific_method_frame,
	    named_procedure_method_list_qm)) {
	named_procedure_method_list_qm = 
		delete_gensym_element_1(specific_method_frame,
		named_procedure_method_list_qm);
	if (named_procedure_method_list_qm &&  
		!TRUEP(CDR(named_procedure_method_list_qm))) {
	    if ( !TRUEP(CDR(procedure_methods_qm))) {
		reclaim_gensym_tree_1(procedure_methods_qm);
		mutate_kb_specific_property_value(class_1,Nil,
			Procedure_methods_of_class_kbprop);
	    }
	    else {
		temp = 
			delete_gensym_element_1(named_procedure_method_list_qm,
			lookup_kb_specific_property_value(class_1,
			Procedure_methods_of_class_kbprop));
		mutate_kb_specific_property_value(class_1,temp,
			Procedure_methods_of_class_kbprop);
		reclaim_gensym_list_1(named_procedure_method_list_qm);
	    }
	}
	temp = decrement_class_count_of_method(specific_method_name,class_1);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* INCREMENT-CLASS-COUNT-OF-METHOD */
Object increment_class_count_of_method(specific_method_name,class_1)
    Object specific_method_name, class_1;
{
    Object class_count_list_qm, class_count_cons_qm, cdr_new_value;

    x_note_fn_call(160,214);
    class_count_list_qm = 
	    lookup_kb_specific_property_value(specific_method_name,
	    Classes_of_procedure_method_kbprop);
    class_count_cons_qm = class_count_list_qm ? assq_function(class_1,
	    class_count_list_qm) : Qnil;
    if (class_count_cons_qm) {
	cdr_new_value = FIXNUM_ADD1(CDR(class_count_cons_qm));
	M_CDR(class_count_cons_qm) = cdr_new_value;
    }
    else if ( !TRUEP(class_count_list_qm))
	mutate_kb_specific_property_value(specific_method_name,
		gensym_cons_1(gensym_cons_1(class_1,FIX((SI_Long)1L)),Nil),
		Classes_of_procedure_method_kbprop);
    else
	nconc2(class_count_list_qm,gensym_cons_1(gensym_cons_1(class_1,
		FIX((SI_Long)1L)),Nil));
    return VALUES_1(Nil);
}

/* DECREMENT-CLASS-COUNT-OF-METHOD */
Object decrement_class_count_of_method(specific_method_name,class_1)
    Object specific_method_name, class_1;
{
    Object class_count_list_qm, class_count_cons_qm, class_count_qm, temp;
    Object cdr_new_value;

    x_note_fn_call(160,215);
    class_count_list_qm = 
	    lookup_kb_specific_property_value(specific_method_name,
	    Classes_of_procedure_method_kbprop);
    class_count_cons_qm = class_count_list_qm ? assq_function(class_1,
	    class_count_list_qm) : Qnil;
    class_count_qm = class_count_cons_qm ? CDR(class_count_cons_qm) : Qnil;
    if (class_count_cons_qm) {
	if (IFIX(class_count_qm) <= (SI_Long)1L) {
	    temp = delete_gensym_element_1(class_count_cons_qm,
		    class_count_list_qm);
	    mutate_kb_specific_property_value(specific_method_name,temp,
		    Classes_of_procedure_method_kbprop);
	    reclaim_gensym_cons_1(class_count_cons_qm);
	}
	else {
	    cdr_new_value = FIXNUM_SUB1(class_count_qm);
	    M_CDR(class_count_cons_qm) = cdr_new_value;
	}
    }
    return VALUES_1(Nil);
}

/* GET-NAMED-PROCEDURE-METHODS-FOR-CLASS */
Object get_named_procedure_methods_for_class(specific_method_name,class_1)
    Object specific_method_name, class_1;
{
    Object procedure_methods_qm, temp;

    x_note_fn_call(160,216);
    procedure_methods_qm = lookup_kb_specific_property_value(class_1,
	    Procedure_methods_of_class_kbprop);
    temp = procedure_methods_qm ? assq_function(specific_method_name,
	    procedure_methods_qm) : Qnil;
    return VALUES_1(temp);
}

/* VERIFY-METHOD-DISPATCH */
Object verify_method_dispatch(specific_method,argument_count_qm,
	    test_if_method_not_bad_qm,test_if_method_serve_item_p)
    Object specific_method, argument_count_qm, test_if_method_not_bad_qm;
    Object test_if_method_serve_item_p;
{
    Object temp;

    x_note_fn_call(160,217);
    if (( !TRUEP(argument_count_qm) || EQ(ISVREF(specific_method,
	    (SI_Long)23L),argument_count_qm)) && ( 
	    !TRUEP(test_if_method_not_bad_qm) || 
	    frame_not_bad_p(specific_method))) {
	temp =  !TRUEP(test_if_method_serve_item_p) ? T : Nil;
	if (temp);
	else
	    temp = serve_item_p(specific_method);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object array_constant_22;   /* # */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

/* METHOD-DISPATCH-ERROR */
Object method_dispatch_error(specific_method,argument_count_qm,
	    test_if_method_not_bad_qm,test_if_method_serve_item_p)
    Object specific_method, argument_count_qm, test_if_method_not_bad_qm;
    Object test_if_method_serve_item_p;
{
    Object temp;

    x_note_fn_call(160,218);
    if (argument_count_qm &&  !EQ(ISVREF(specific_method,(SI_Long)23L),
	    argument_count_qm))
	temp = array_constant_22;
    else if (test_if_method_not_bad_qm &&  
	    !TRUEP(frame_not_bad_p(specific_method)))
	temp = array_constant_23;
    else if (test_if_method_serve_item_p &&  
	    !TRUEP(serve_item_p(specific_method)))
	temp = array_constant_24;
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* DUPLICATE-SPECIFIC-METHODS-P */
Object duplicate_specific_methods_p(method_name,method_class,argument_count)
    Object method_name, method_class, argument_count;
{
    Object specific_method, temp, ab_loop_list_;
    SI_Long method_count;

    x_note_fn_call(160,219);
    specific_method = Nil;
    temp = get_named_procedure_methods_for_class(method_name,method_class);
    ab_loop_list_ = CDR(temp);
    method_count = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    specific_method = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (FIXNUM_EQ(ISVREF(specific_method,(SI_Long)23L),argument_count))
	method_count = method_count + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = method_count > (SI_Long)1L ? T : Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* GET-SPECIFIC-METHODS-FOR-CLASS-OR-SUPERIOR-CLASS */
Object get_specific_methods_for_class_or_superior_class(method_declaration_name,
	    class_1)
    Object method_declaration_name, class_1;
{
    Object class_description_qm, method_name_and_method_list_qm;
    Object method_list_qm, inherited_class, ab_loop_list_;

    x_note_fn_call(160,220);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    method_name_and_method_list_qm = Nil;
    method_list_qm = Nil;
    if (class_description_qm) {
	inherited_class = Nil;
	ab_loop_list_ = ISVREF(class_description_qm,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	inherited_class = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	method_name_and_method_list_qm = 
		get_named_procedure_methods_for_class(method_declaration_name,
		inherited_class);
	if (method_name_and_method_list_qm)
	    method_list_qm = M_CDR(method_name_and_method_list_qm);
	if (method_list_qm)
	    goto end_loop;
	goto next_loop;
      end_loop:;
    }
    else {
	method_name_and_method_list_qm = 
		get_named_procedure_methods_for_class(method_declaration_name,
		class_1);
	if (method_name_and_method_list_qm)
	    method_list_qm = M_CDR(method_name_and_method_list_qm);
    }
    return VALUES_1(method_list_qm);
}

static Object array_constant_25;   /* # */

/* GET-SPECIFIC-METHOD-FOR-ARG-LIST-GIVEN-NAME */
Object get_specific_method_for_arg_list_given_name(method_name,
	    argument_list,icp_socket)
    Object method_name, argument_list, icp_socket;
{
    Object first_arg_qm, first_arg_from_handle, x2, gensymed_symbol;
    Object first_arg_class_description_qm, argument_count, method_or_error;
    Object temp;

    x_note_fn_call(160,221);
    first_arg_qm = argument_list ? M_CAR(argument_list) : Qnil;
    first_arg_from_handle = FIXNUMP(first_arg_qm) ? 
	    get_item_from_local_handle(first_arg_qm,icp_socket) : first_arg_qm;
    if (SIMPLE_VECTOR_P(first_arg_from_handle) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_arg_from_handle)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(first_arg_from_handle,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(first_arg_from_handle,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    first_arg_class_description_qm = gensymed_symbol && 
	    ISVREF(gensymed_symbol,(SI_Long)16L) ? 
	    ISVREF(first_arg_from_handle,(SI_Long)1L) : Nil;
    argument_count = length(argument_list);
    method_or_error = first_arg_class_description_qm ? 
	    get_specific_method(method_name,first_arg_class_description_qm,
	    argument_count,Nil,T,T) : array_constant_25;
    if (text_string_p(method_or_error))
	temp = copy_text_string(method_or_error);
    else {
	if (FIXNUMP(first_arg_qm))
	    M_CAR(argument_list) = first_arg_from_handle;
	temp = method_or_error;
    }
    return VALUES_1(temp);
}

/* GET-SPECIFIC-METHOD-FOR-STACK-GIVEN-NAME */
Object get_specific_method_for_stack_given_name(method_name,stack,
	    first_argument_index,argument_count)
    Object method_name, stack, first_argument_index, argument_count;
{
    Object first_arg_qm, x2, gensymed_symbol, first_arg_class_description_qm;
    Object temp_1;
    char temp;

    x_note_fn_call(160,222);
    first_arg_qm = ISVREF(stack,IFIX(first_argument_index));
    if (first_arg_qm) {
	if (SIMPLE_VECTOR_P(first_arg_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(first_arg_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(first_arg_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(first_arg_qm,(SI_Long)1L);
	    gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		    (SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? x2 : Qnil;
	}
	else
	    gensymed_symbol = Nil;
	temp = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		(SI_Long)16L)) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    first_arg_class_description_qm = temp ? ISVREF(first_arg_qm,
	    (SI_Long)1L) : Nil;
    temp_1 = first_arg_class_description_qm ? 
	    get_specific_method(method_name,first_arg_class_description_qm,
	    argument_count,Nil,T,T) : array_constant_25;
    return VALUES_1(temp_1);
}

static Object array_constant_26;   /* # */

/* GET-SPECIFIC-METHOD-FOR-STACK */
Object get_specific_method_for_stack(method_declaration,stack,
	    first_argument_index,argument_count)
    Object method_declaration, stack, first_argument_index, argument_count;
{
    Object method_declaration_name_or_names_qm, method_declaration_name_qm;
    Object temp;

    x_note_fn_call(160,223);
    method_declaration_name_or_names_qm = 
	    get_lookup_slot_value_given_default(method_declaration,
	    Qname_or_names_for_frame,Nil);
    method_declaration_name_qm = method_declaration_name_or_names_qm ? 
	    (CONSP(method_declaration_name_or_names_qm) ? 
	    M_CAR(method_declaration_name_or_names_qm) : 
	    method_declaration_name_or_names_qm) : Qnil;
    temp =  !TRUEP(method_declaration_name_qm) ? array_constant_26 : 
	    get_specific_method_for_stack_given_name(method_declaration_name_qm,
	    stack,first_argument_index,argument_count);
    return VALUES_1(temp);
}

/* GET-NEXT-SPECIFIC-METHOD */
Object get_next_specific_method(method_name,currently_executing_class,
	    argument_count,original_argument_class_description)
    Object method_name, currently_executing_class, argument_count;
    Object original_argument_class_description;
{
    Object temp;

    x_note_fn_call(160,224);
    temp = get_specific_method(method_name,
	    original_argument_class_description,argument_count,
	    currently_executing_class,T,T);
    return VALUES_1(temp);
}

Object Action_method_reference_class = UNBOUND;

static Object Qsystem_item;        /* system-item */

static Object array_constant_27;   /* # */

static Object array_constant_28;   /* # */

/* GET-SPECIFIC-METHOD */
Object get_specific_method(method_declaration_name,class_description,
	    argument_count_qm,search_after_class_qm,
	    test_if_method_not_bad_qm,test_if_method_serve_item_p_qm)
    Object method_declaration_name, class_description, argument_count_qm;
    Object search_after_class_qm, test_if_method_not_bad_qm;
    Object test_if_method_serve_item_p_qm;
{
    Object inherited_class, temp, ab_loop_list_, method_list_qm;
    Object method_name_qm, verified_specific_method_qm;
    Object non_unique_method_error_p_qm, specific_method_error_string_qm;
    Object cached_dispatching_error_string_qm, specific_method;
    Object ab_loop_list__1, dispatch_error_string_qm;

    x_note_fn_call(160,225);
    inherited_class = Nil;
    if (search_after_class_qm) {
	temp = memq_function(search_after_class_qm,
		ISVREF(class_description,(SI_Long)2L));
	ab_loop_list_ = CDR(temp);
    }
    else
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
    method_list_qm = Nil;
    method_name_qm = Nil;
    verified_specific_method_qm = Nil;
    non_unique_method_error_p_qm = Nil;
    specific_method_error_string_qm = Nil;
    cached_dispatching_error_string_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    inherited_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    method_list_qm = 
	    get_named_procedure_methods_for_class(method_declaration_name,
	    inherited_class);
    method_name_qm = method_list_qm ? M_CAR(method_list_qm) : Qnil;
    if (EQ(method_name_qm,method_declaration_name)) {
	specific_method = Nil;
	ab_loop_list__1 = M_CDR(method_list_qm);
	dispatch_error_string_qm = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	specific_method = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	dispatch_error_string_qm = method_dispatch_error(specific_method,
		argument_count_qm,test_if_method_not_bad_qm,
		test_if_method_serve_item_p_qm);
	if ( !TRUEP(dispatch_error_string_qm)) {
	    if (argument_count_qm) {
		verified_specific_method_qm = specific_method;
		goto end_loop_1;
	    }
	    else if (verified_specific_method_qm) {
		non_unique_method_error_p_qm = specific_method;
		goto end_loop_1;
	    }
	    else
		verified_specific_method_qm = specific_method;
	}
	else if ( !TRUEP(verified_specific_method_qm))
	    cached_dispatching_error_string_qm = dispatch_error_string_qm;
	goto next_loop_1;
      end_loop_1:;
    }
    if (verified_specific_method_qm || non_unique_method_error_p_qm || 
	    EQ(inherited_class,Qsystem_item))
	goto end_loop;
    goto next_loop;
  end_loop:
    if (non_unique_method_error_p_qm)
	specific_method_error_string_qm = array_constant_27;
    else if (verified_specific_method_qm)
	specific_method_error_string_qm = Nil;
    else if (cached_dispatching_error_string_qm)
	specific_method_error_string_qm = cached_dispatching_error_string_qm;
    else
	specific_method_error_string_qm = array_constant_28;
    temp = specific_method_error_string_qm;
    if (temp);
    else
	temp = verified_specific_method_qm;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* CHECK-FOR-MATCHING-METHODS */
Object check_for_matching_methods(current_frame,
	    method_class_for_current_frame,previous_frame)
    Object current_frame, method_class_for_current_frame, previous_frame;
{
    Object temp, temp_1;

    x_note_fn_call(160,226);
    if (EQ(ISVREF(current_frame,(SI_Long)30L),ISVREF(previous_frame,
	    (SI_Long)30L)) && EQ(method_class_for_current_frame,
	    ISVREF(previous_frame,(SI_Long)31L)) && 
	    FIXNUM_EQ(ISVREF(current_frame,(SI_Long)23L),
	    ISVREF(previous_frame,(SI_Long)23L))) {
	temp = ISVREF(current_frame,(SI_Long)30L);
	temp_1 = ISVREF(current_frame,(SI_Long)23L);
	return VALUES_3(temp,method_class_for_current_frame,temp_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qsimulation_initial_value;  /* simulation-initial-value */

static Object Qembedded_rule_qm;   /* embedded-rule? */

/* GET-BYTE-CODE-BODY-IF-ANY */
Object get_byte_code_body_if_any(item,computation_component_particulars_qm)
    Object item, computation_component_particulars_qm;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, sub_class_bit_vector;
    Object base_code_body_qm, embedded_rule_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(160,227);
    if (CONSP(computation_component_particulars_qm) && 
	    EQ(M_CAR(computation_component_particulars_qm),
	    Qcell_array_element)) {
	gensymed_symbol = ISVREF(get_lookup_slot_value_given_default(item,
		Qcell_array,Nil),(SI_Long)3L);
	gensymed_symbol_1 = SECOND(computation_component_particulars_qm);
	if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(item,
		Qcell_array,Nil),(SI_Long)3L),(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    temp = ISVREF(get_lookup_slot_value_given_default(item,
		    Qcell_array,Nil),(SI_Long)3L);
	    temp = ISVREF(temp,IFIX(FIXNUM_ADD(gensymed_symbol_1,
		    Managed_array_index_offset)));
	}
	else
	    temp = ISVREF(ISVREF(gensymed_symbol,(IFIX(gensymed_symbol_1) 
		    >>  -  - (SI_Long)10L) + (SI_Long)2L),
		    IFIX(gensymed_symbol_1) & (SI_Long)1023L);
	return VALUES_1(ISVREF(temp,(SI_Long)10L));
    }
    else if (CONSP(computation_component_particulars_qm) && 
	    EQ(M_CAR(computation_component_particulars_qm),
	    Qsimulation_initial_value)) {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Generic_simulation_formula_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(ISVREF(item,(SI_Long)21L));
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Simulation_subtable_class_description,
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1)
		return VALUES_1(ISVREF(item,(SI_Long)24L));
	    else
		return VALUES_1(Qnil);
	}
    }
    else {
	gensymed_symbol = ISVREF(item,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_2;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(ISVREF(item,(SI_Long)31L));
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
		temp_1 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		base_code_body_qm = ISVREF(item,(SI_Long)28L) ? 
			M_CAR(ISVREF(item,(SI_Long)28L)) : Nil;
		if (base_code_body_qm)
		    return VALUES_1(ISVREF(base_code_body_qm,(SI_Long)8L));
		else
		    return VALUES_1(Nil);
	    }
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Function_definition_class_description,
			(SI_Long)18L));
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
		    gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		    gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		    temp_1 = (SI_Long)0L < gensymed_symbol_2;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1)
		    return VALUES_1(ISVREF(item,(SI_Long)20L));
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Generic_simulation_formula_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
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
		    if (temp_1)
			return VALUES_1(ISVREF(item,(SI_Long)20L));
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Simulation_subtable_class_description,
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
			    gensymed_symbol_4 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_3 = gensymed_symbol_3 << 
				    gensymed_symbol_4;
			    gensymed_symbol_2 = gensymed_symbol_2 & 
				    gensymed_symbol_3;
			    temp_1 = (SI_Long)0L < gensymed_symbol_2;
			}
			else
			    temp_1 = TRUEP(Nil);
			if (temp_1)
			    return VALUES_1(ISVREF(item,(SI_Long)23L));
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(Action_button_class_description,
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
				temp_1 = (SI_Long)0L < gensymed_symbol_2;
			    }
			    else
				temp_1 = TRUEP(Nil);
			    if (temp_1) {
				embedded_rule_qm = 
					get_slot_value_function(item,
					Qembedded_rule_qm,Nil);
				if (embedded_rule_qm)
				    return VALUES_1(ISVREF(embedded_rule_qm,
					    (SI_Long)31L));
				else
				    return VALUES_1(Nil);
			    }
			    else {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(User_menu_choice_class_description,
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
				    gensymed_symbol_3 = gensymed_symbol_3 
					    << gensymed_symbol_4;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    & gensymed_symbol_3;
				    temp_1 = (SI_Long)0L < gensymed_symbol_2;
				}
				else
				    temp_1 = TRUEP(Nil);
				if (temp_1) {
				    embedded_rule_qm = ISVREF(item,
					    (SI_Long)24L);
				    if (embedded_rule_qm)
					return VALUES_1(ISVREF(embedded_rule_qm,
						(SI_Long)31L));
				    else
					return VALUES_1(Nil);
				}
				else
				    return VALUES_1(Nil);
			    }
			}
		    }
		}
	    }
	}
    }
}

/* ITEM-CURRENTLY-CONTAINS-COMPILED-VALUE */
Object item_currently_contains_compiled_value(item)
    Object item;
{
    Object cell_array_qm;
    char temp;

    x_note_fn_call(160,228);
    temp = TRUEP(get_byte_code_body_if_any(item,Nil));
    if (temp);
    else {
	cell_array_qm = get_lookup_slot_value_given_default(item,
		Qcell_array,Nil);
	temp = cell_array_qm ? TRUEP(ISVREF(cell_array_qm,(SI_Long)3L)) : 
		TRUEP(Qnil);
    }
    return VALUES_1( ! !temp ? T : Nil);
}

static Object string_constant_53;  /* "For procedure ~NF, arg ~S, = ~NA, expected to be of type ~NT" */

static Object string_constant_54;  /* "For procedure ~NF, arg ~S expected to be of type ~NT, not ~NT" */

static Object string_constant_55;  /* "Procedure ~NF expects to be called with ~S arguments, but is declared to take ~S" */

/* CHECK-PROCEDURE-ARGLIST */
Object check_procedure_arglist(procedure,argument_types_or_arg_vector,
	    runtime_nil_ok)
    Object procedure, argument_types_or_arg_vector, runtime_nil_ok;
{
    Object arg_count, args, gensymed_symbol_1, arg_type, x, temp;
    SI_Long ab_loop_bind_, i, gensymed_symbol;
    char actual;

    x_note_fn_call(160,229);
    arg_count = ISVREF(procedure,(SI_Long)23L);
    if (arg_count);
    else
	arg_count = FIX((SI_Long)0L);
    if (FIXNUM_EQ(arg_count,length(argument_types_or_arg_vector))) {
	args = ISVREF(procedure,(SI_Long)24L);
	actual = VECTORP(argument_types_or_arg_vector);
	ab_loop_bind_ = IFIX(arg_count);
	i = (SI_Long)0L;
      next_loop:
	if (i >= ab_loop_bind_)
	    goto end_loop;
	gensymed_symbol = i * (SI_Long)2L + (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_LE(ISVREF(args,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(args,gensymed_symbol 
		+ IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(args,
		(gensymed_symbol >>  -  - (SI_Long)10L) + (SI_Long)2L),
		gensymed_symbol & (SI_Long)1023L);
	if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		Kgeneral_description))
	    gensymed_symbol_1 = 
		    getfq_function_no_default(CDR(gensymed_symbol_1),Ktype);
	arg_type = gensymed_symbol_1;
	x = elt(argument_types_or_arg_vector,FIX(i));
	if ( !(actual ? ( !TRUEP(x) ? TRUEP(runtime_nil_ok) : 
		TRUEP(type_specification_type_p(x,arg_type))) : 
		TRUEP(type_specification_subtype_p(x,arg_type)))) {
	    gensymed_symbol = i * (SI_Long)2L;
	    temp = FIXNUM_LE(ISVREF(args,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(args,
		    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(args,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    gensymed_symbol = i * (SI_Long)2L + (SI_Long)1L;
	    gensymed_symbol_1 = FIXNUM_LE(ISVREF(args,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(args,
		    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(args,(gensymed_symbol >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & 
		    (SI_Long)1023L);
	    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
		    Kgeneral_description))
		gensymed_symbol_1 = 
			getfq_function_no_default(CDR(gensymed_symbol_1),
			Ktype);
	    return VALUES_5(actual ? string_constant_53 : 
		    string_constant_54,procedure,temp,x,gensymed_symbol_1);
	}
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else {
	temp = length(argument_types_or_arg_vector);
	return VALUES_4(string_constant_55,procedure,temp,arg_count);
    }
}

/* START-LOCAL-REPRESENTATION-CALLBACK */
Object start_local_representation_callback(representation,argument_list)
    Object representation, argument_list;
{
    Object procedure, serial_number, gensymed_symbol, xa, ya, arg_count;
    Object arg_vector, argument, ab_loop_list_, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, error_qm;
    Object thing;
    SI_Long i, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(160,230);
    procedure = ISVREF(representation,(SI_Long)10L);
    serial_number = ISVREF(representation,(SI_Long)11L);
    if (SYMBOLP(procedure))
	FUNCALL_1(procedure,argument_list);
    else {
	gensymed_symbol = ISVREF(procedure,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(procedure) ? EQ(ISVREF(procedure,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if (temp);
	else if (runnable_p_function(procedure)) {
	    arg_count = length(argument_list);
	    arg_vector = allocate_managed_simple_vector(arg_count);
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(arg_count);
	    argument = Nil;
	    ab_loop_list_ = argument_list;
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    argument = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ISVREF(arg_vector,i) = argument;
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:
	    result = check_procedure_arglist(procedure,arg_vector,T);
	    MVS_5(result,gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    if (gensymed_symbol)
		notify_user(5,gensymed_symbol,gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    error_qm = gensymed_symbol;
	    if (error_qm) {
		ab_loop_bind_ = IFIX(arg_count);
		i = (SI_Long)0L;
	      next_loop_1:
		if (i >= ab_loop_bind_)
		    goto end_loop_1;
		thing = ISVREF(arg_vector,i);
		if ( !(FIXNUMP(thing) || SYMBOLP(thing) || 
			SIMPLE_VECTOR_P(thing)))
		    reclaim_if_evaluation_value_1(thing);
		i = i + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    else
		start_procedure_invocation_in_place(procedure,Nil,Nil,
			arg_vector,FIXNUM_SUB1(arg_count),arg_count,Nil,
			Nil,Nil,Nil,Nil);
	    reclaim_managed_simple_vector(arg_vector);
	    reclaim_eval_list_1(argument_list);
	}
	else;
    }
    return VALUES_1(Nil);
}

static Object array_constant_29;   /* # */

static Object string_constant_56;  /* " of " */

/* DENOTE-COMPONENT-OF-BLOCK-1-FOR-PROCEDURE-INVOCATION */
Object denote_component_of_block_1_for_procedure_invocation()
{
    Object type_name;
    char temp;

    x_note_fn_call(160,231);
    if (BOUNDP(Qcurrent_computation_instance)) {
	if (SIMPLE_VECTOR_P(Current_computation_instance)) {
	    type_name = ISVREF(Current_computation_instance,(SI_Long)0L);
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp);
	    else
		temp = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return write_procedure_invocation_instance_from_slot(ISVREF(Current_computation_instance,
		(SI_Long)11L),Nil);
    else {
	twrite_beginning_of_wide_string(array_constant_29,FIX((SI_Long)13L));
	return denote_component_of_block_1(Qcurrent_computation_frame,
		string_constant_56);
    }
}

static Object Qg2_defstruct_structure_name_inference_background_collection_g2_struct;  /* g2-defstruct-structure-name::inference-background-collection-g2-struct */

/* GET-FRAME-FOR-COMPUTATION-INSTANCE */
Object get_frame_for_computation_instance(computation_instance)
    Object computation_instance;
{
    Object type_name, procedure_invocation;
    char temp;

    x_note_fn_call(160,232);
    if ( !TRUEP(computation_instance))
	return VALUES_1(Nil);
    else {
	if (SIMPLE_VECTOR_P(computation_instance)) {
	    type_name = ISVREF(computation_instance,(SI_Long)0L);
	    temp = EQ(type_name,
		    Qg2_defstruct_structure_name_code_body_invocation_g2_struct);
	    if (temp);
	    else
		temp = EQ(type_name,
			Qg2_defstruct_structure_name_procedure_invocation_g2_struct);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    procedure_invocation = ISVREF(computation_instance,(SI_Long)11L);
	    if (procedure_invocation)
		return VALUES_1(ISVREF(procedure_invocation,(SI_Long)23L));
	    else
		return VALUES_1(Nil);
	}
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct))
	    return VALUES_1(ISVREF(computation_instance,(SI_Long)8L));
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_formula_invocation_g2_struct))
	    return VALUES_1(ISVREF(computation_instance,(SI_Long)8L));
	else if (SIMPLE_VECTOR_P(computation_instance) && 
		EQ(ISVREF(computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_inference_background_collection_g2_struct))
	    return VALUES_1(ISVREF(computation_instance,(SI_Long)1L));
	else
	    return VALUES_1(computation_instance);
    }
}

/* NAME-AND-CLASS-FOR-COMPUTATION-INSTANCE */
Object name_and_class_for_computation_instance(computation_instance)
    Object computation_instance;
{
    Object frame_qm, x2, class_description_qm, class_qm, gensymed_symbol;
    Object sub_class_bit_vector, name_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(160,233);
    frame_qm = get_frame_for_computation_instance(computation_instance);
    if (SIMPLE_VECTOR_P(frame_qm) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L &&  
	    !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(frame_qm,(SI_Long)1L);
	class_description_qm = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	class_description_qm = Nil;
    class_qm = class_description_qm ? ISVREF(class_description_qm,
	    (SI_Long)1L) : Nil;
    if (class_qm) {
	if (SIMPLE_VECTOR_P(frame_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_qm)) > (SI_Long)2L && 
		 !EQ(ISVREF(frame_qm,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_qm,(SI_Long)1L);
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
    }
    else
	temp = TRUEP(Nil);
    name_qm = temp ? get_or_make_up_designation_for_block(frame_qm) : Nil;
    return VALUES_2(name_qm,class_qm);
}

static Object string_constant_57;  /* " has exceeded the warning limit for uninterrupted procedure execution!  ~
				    *        This procedure has been executing for ~a seconds."
				    */

/* WRITE-PROCEDURE-TIME-WARNING */
Object write_procedure_time_warning(procedure_invocation,elapsed_time)
    Object procedure_invocation, elapsed_time;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(160,234);
    SAVE_STACK();
    if ((SI_Long)1L <= IFIX(Warning_message_level) &&  
		!TRUEP(Debugging_reset)) {
	if ( !TRUEP(Defer_notifications_qm))
	    break_out_of_debug_messages();
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
		      write_warning_message_header(FIX((SI_Long)1L));
		      write_procedure_invocation_instance_from_slot(procedure_invocation,
			      Nil);
		      tformat(2,string_constant_57,
			      DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(elapsed_time) 
			      / (double)IFIX(Fixnum_time_units_per_second)));
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	    result = RESTORE_VALUES();
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

static Object string_constant_58;  /* "Uninterrupted procedure execution time limit exceeded!  This procedure ~
				    *      has executed for ~a seconds."
				    */

/* SIGNAL-PROCEDURE-TIME-ERROR */
Object signal_procedure_time_error(elapsed_time,top_of_stack)
    Object elapsed_time, top_of_stack;
{
    Object top_of_stack_1, message_1;

    x_note_fn_call(160,235);
    top_of_stack_1 = top_of_stack;
    message_1 = tformat_stack_error_text_string(2,string_constant_58,
	    DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(elapsed_time) / 
	    (double)IFIX(Fixnum_time_units_per_second)));
    return raw_stack_error_named_error(top_of_stack_1,message_1);
}

static Object string_constant_59;  /* "Exiting execution of ~NF." */

/* CODE-BODY-INVOCATION-EXIT-BREAKPOINT-CONTEXT-MESSAGE */
Object code_body_invocation_exit_breakpoint_context_message(procedure)
    Object procedure;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(160,236);
    sub_class_bit_vector = ISVREF(ISVREF(procedure,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
	return tformat_text_string(2,string_constant_59,procedure);
    else
	return VALUES_1(Nil);
}

void proc_utils_INIT()
{
    Object temp, temp_1, reclaim_structure_for_code_body_invocation_1;
    Object reclaim_structure_for_remote_procedure_call_1;
    Object reclaim_structure_for_system_rpc_1, temp_2;
    Object write_invalid_dynamic_breakpoint_note_1;
    Object reclaim_structure_for_procedure_invocation_1;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, AB_package, list_constant_16;
    Object Qaction_method_reference_class, Qclasses_of_procedure_method;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_gensym_tree_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qprocedure_methods_of_class, Qslot_value_writer;
    Object Qwrite_procedure_method_name_from_slot, Qslot_putter;
    Object Qput_procedure_method_class, Qput_procedure_method_name;
    Object Qclasses_which_define, Qcleanup, Qcleanup_for_method;
    Object Qqualified_name, Qinitialize_after_reading;
    Object Qinitialize_after_reading_for_method;
    Object Qsubstitute_class_and_kb_flags, Qspecific_procedure_method;
    Object string_constant_142, string_constant_141, string_constant_140;
    Object string_constant_139, string_constant_138, list_constant_19;
    Object Qcreate_icon_description, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, Qnote_name_change;
    Object Qnote_name_change_for_method_declaration, Qinitialize;
    Object Qinitialize_for_method_declaration, Qprocedure_method;
    Object string_constant_130, string_constant_129, string_constant_128;
    Object string_constant_127, string_constant_126, string_constant_125;
    Object string_constant_124, string_constant_123, string_constant_122;
    Object string_constant_121, string_constant_120, string_constant_119;
    Object string_constant_118, string_constant_117, string_constant_116;
    Object string_constant_115, string_constant_114, string_constant_113;
    Object string_constant_112, Qproc_utils;
    Object Qclear_computation_context_variables, string_constant_111;
    Object Qminimum_available_procedure_invocation_index, list_constant_18;
    Object Qtop_level_procedure_invocations_array, Qallocate_managed_array;
    Object Kfuncall, Qinterval, Qseconds, list_constant_17, Qevaluation_value;
    Object Qab_or, list_constant_5, Qschedule_computation_instance_execution;
    Object Qcleanup_for_procedure_invocation, string_constant_110;
    Object list_constant_3, string_constant_109, string_constant_108;
    Object Qreclaim_structure, Qoutstanding_procedure_invocation_count;
    Object Qprocedure_invocation_structure_memory_usage, Qutilities2;
    Object string_constant_107, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_106, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qmanually_disable;
    Object Qmanually_disable_for_procedure, Qnote_runs_while_inactive_change;
    Object Qnote_runs_while_inactive_change_for_procedure;
    Object Qcleanup_for_procedure, Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_procedure;
    Object Qinitialize_for_procedure, Qset_dynamic_breakpoints;
    Object Qget_dynamic_breakpoints, Qinitial_dynamic_breakpoints;
    Object list_constant_15, list_constant_6, Qdynamic_breakpoints;
    Object list_constant_14, list_constant_13, list_constant_12, Qab_structure;
    Object list_constant_11, list_constant_10, list_constant_9;
    Object list_constant_8, Qvirtual_attributes_local_to_class;
    Object Qframe_note_writer_1, Kinvalid, Qdynamic_breakpoint_invalid, Kvalid;
    Object Qdynamic_breakpoint_valid, Kdisabled, Qdynamic_breakpoint_disabled;
    Object Kenabled, Qdynamic_breakpoint_enabled, Qput_procedure_definition;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_procedure_definition_for_slot;
    Object Qput_md5_identifier_qm, Qput_parse_results_qm;
    Object Qrecompile_previously_optimized_procedures, Qabsent_slot_putter;
    Object Qput_optimize_procedure_code_qm_where_slot_is_absent;
    Object Qoptimize_procedure_code_qm;
    Object Qput_procedure_free_references_where_slot_is_absent;
    Object Qprocedure_free_references;
    Object Qput_code_bodies_3_dot_0_alpha_where_slot_is_absent;
    Object Qcode_bodies_3_dot_0_alpha, Qput_procedure_code_bodies_3_dot_0_beta;
    Object Qdisassembled_code, Qtext, Quninterrupted_procedure_execution_limit;
    Object Quninterrupted_procedure_execution_limit_qm, Qslot_value_reclaimer;
    Object Qreclaim_procedure_invocations_value, Qprocedure_invocations;
    Object Qget_inlined_calls, Qinitial_inlined_calls, list_constant_7;
    Object Qinlined_calls, list_constant_4, Qno_item, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, Qentity, Qitem;
    Object Qout_procedure_invocations_hash_vector_43_vectors;
    Object Qprocedure_invocations_hash_vector_43_vector_memory_usage;
    Object string_constant_73, Qsystem_rpc, Qoutstanding_system_rpc_count;
    Object Qsystem_rpc_structure_memory_usage, string_constant_72;
    Object string_constant_71, Qremote_procedure_call;
    Object Qoutstanding_remote_procedure_call_count;
    Object Qremote_procedure_call_structure_memory_usage, string_constant_70;
    Object string_constant_69, Qcode_body_invocation;
    Object Qoutstanding_code_body_invocation_count;
    Object Qcode_body_invocation_structure_memory_usage, string_constant_68;
    Object string_constant_67, Qput_p_code_array_where_slot_is_absent;
    Object Qp_code_array, Qreclaim_code_body_entry_points_value;
    Object Qcode_body_entry_points, string_constant_66, string_constant_65;
    Object list_constant_2, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object Qdependent_frame, Qprocedure_evaluator;

    x_note_fn_call(160,237);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qproc = STATIC_SYMBOL("PROC",AB_package);
    if (Procedure_alist == UNBOUND)
	Procedure_alist = Nil;
    Qprocedure_evaluator = STATIC_SYMBOL("PROCEDURE-EVALUATOR",AB_package);
    Procedure_evaluator_prop = Qprocedure_evaluator;
    Qevaluating_simulator_procedure_qm = 
	    STATIC_SYMBOL("EVALUATING-SIMULATOR-PROCEDURE\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qevaluating_simulator_procedure_qm,
	    Evaluating_simulator_procedure_qm);
    Qproc_utils = STATIC_SYMBOL("PROC-UTILS",AB_package);
    record_system_variable(Qevaluating_simulator_procedure_qm,Qproc_utils,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    if (Datum_type == UNBOUND)
	Datum_type = Nil;
    Qcode_body = STATIC_SYMBOL("CODE-BODY",AB_package);
    Qdependent_frame = STATIC_SYMBOL("DEPENDENT-FRAME",AB_package);
    list_constant_2 = STATIC_CONS(Qdependent_frame,Qnil);
    check_if_superior_classes_are_defined(Qcode_body,list_constant_2);
    string_constant_60 = STATIC_STRING("0");
    string_constant_61 = 
	    STATIC_STRING("1t4z8r83YGy83YGy83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83bCy83bCy83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83Z7y83Z7y83I8y83I8y0000");
    string_constant_62 = 
	    STATIC_STRING("1n1l8o1l8l1l83Cy000004z8r83V*y83V*y83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83Kcy83Kcy83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83Kby");
    string_constant_63 = 
	    STATIC_STRING("83Kby83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83I9y83I9y83I8y83I8y00001n1l8o1l8l1l83Cy000004z8r83IAy83IAy83I8y83I8y00001n1l8o1l8l1");
    string_constant_64 = 
	    STATIC_STRING("l83Cy000004z8r83IBy83IBy83I8y83I8y00001n1l8o1l8l1l83Cy00000");
    string_constant_65 = 
	    STATIC_STRING("1v8q1m83I8y1l83=fy1p83YGy08o8l83Cy1p83bCy08o8l83Cy1p83Z7y08o8l83Cy1p83V*y08o8l83Cy1p83Kcy08o8l83Cy1p83Kby08o8l83Cy1p83I9y08o8l83");
    string_constant_66 = STATIC_STRING("Cy1p83IAy08o8l83Cy1p83IBy08o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_60);
    temp_1 = regenerate_optimized_constant(LIST_4(string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64));
    add_class_to_environment(9,Qcode_body,list_constant_2,Nil,temp,Nil,
	    temp_1,list_constant_2,
	    regenerate_optimized_constant(LIST_2(string_constant_65,
	    string_constant_66)),Nil);
    Qcode_body_entry_points = STATIC_SYMBOL("CODE-BODY-ENTRY-POINTS",
	    AB_package);
    Qreclaim_code_body_entry_points_value = 
	    STATIC_SYMBOL("RECLAIM-CODE-BODY-ENTRY-POINTS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_code_body_entry_points_value,
	    STATIC_FUNCTION(reclaim_code_body_entry_points_value,NIL,FALSE,
	    2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qcode_body_entry_points,
	    SYMBOL_FUNCTION(Qreclaim_code_body_entry_points_value),
	    Qslot_value_reclaimer);
    Qp_code_array = STATIC_SYMBOL("P-CODE-ARRAY",AB_package);
    Qput_p_code_array_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-P-CODE-ARRAY-WHERE-SLOT-IS-ABSENT",AB_package);
    SET_SYMBOL_FUNCTION(Qput_p_code_array_where_slot_is_absent,
	    STATIC_FUNCTION(put_p_code_array_where_slot_is_absent,NIL,
	    FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qp_code_array,
	    SYMBOL_FUNCTION(Qput_p_code_array_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qg2_defstruct_structure_name_code_body_invocation_g2_struct = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcode_body_invocation = STATIC_SYMBOL("CODE-BODY-INVOCATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_code_body_invocation_g2_struct,
	    Qcode_body_invocation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qcode_body_invocation,
	    Qg2_defstruct_structure_name_code_body_invocation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_code_body_invocation == UNBOUND)
	The_type_description_of_code_body_invocation = Nil;
    string_constant_67 = 
	    STATIC_STRING("43Dy8m833my1o833my830Ey8n8k1l830Ey0000001m1m8x830Ey1m830ly83sDyk3Iyk0k0");
    temp = The_type_description_of_code_body_invocation;
    The_type_description_of_code_body_invocation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_67));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_code_body_invocation_g2_struct,
	    The_type_description_of_code_body_invocation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qcode_body_invocation,
	    The_type_description_of_code_body_invocation,
	    Qtype_description_of_type);
    Qoutstanding_code_body_invocation_count = 
	    STATIC_SYMBOL("OUTSTANDING-CODE-BODY-INVOCATION-COUNT",AB_package);
    Qcode_body_invocation_structure_memory_usage = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_68 = STATIC_STRING("1q833my8s83-Mry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_code_body_invocation_count);
    push_optimized_constant(Qcode_body_invocation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_68));
    Qchain_of_available_code_body_invocations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CODE-BODY-INVOCATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_code_body_invocations,
	    Chain_of_available_code_body_invocations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_code_body_invocations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcode_body_invocation_count = 
	    STATIC_SYMBOL("CODE-BODY-INVOCATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcode_body_invocation_count,
	    Code_body_invocation_count);
    record_system_variable(Qcode_body_invocation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_code_body_invocations_vector == UNBOUND)
	Chain_of_available_code_body_invocations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qcode_body_invocation_structure_memory_usage,
	    STATIC_FUNCTION(code_body_invocation_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_code_body_invocation_count,
	    STATIC_FUNCTION(outstanding_code_body_invocation_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_code_body_invocation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_code_body_invocation,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcode_body_invocation,
	    reclaim_structure_for_code_body_invocation_1);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qremote_procedure_call = STATIC_SYMBOL("REMOTE-PROCEDURE-CALL",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_call_g2_struct,
	    Qremote_procedure_call,Qab_name_of_unique_structure_type);
    mutate_global_property(Qremote_procedure_call,
	    Qg2_defstruct_structure_name_remote_procedure_call_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_remote_procedure_call == UNBOUND)
	The_type_description_of_remote_procedure_call = Nil;
    string_constant_69 = 
	    STATIC_STRING("43Dy8m83mFy1p83mFy833my830Ey8n8k1l833my0000001m1n8y83-5Oy1o83-Bgy83-Bfy83-Bdy83-Bcy1m8x833myk3Nyk0k0");
    temp = The_type_description_of_remote_procedure_call;
    The_type_description_of_remote_procedure_call = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_69));
    mutate_global_property(Qg2_defstruct_structure_name_remote_procedure_call_g2_struct,
	    The_type_description_of_remote_procedure_call,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qremote_procedure_call,
	    The_type_description_of_remote_procedure_call,
	    Qtype_description_of_type);
    Qoutstanding_remote_procedure_call_count = 
	    STATIC_SYMBOL("OUTSTANDING-REMOTE-PROCEDURE-CALL-COUNT",
	    AB_package);
    Qremote_procedure_call_structure_memory_usage = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_70 = STATIC_STRING("1q83mFy8s83-m3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_remote_procedure_call_count);
    push_optimized_constant(Qremote_procedure_call_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_70));
    Qchain_of_available_remote_procedure_calls = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-REMOTE-PROCEDURE-CALLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_remote_procedure_calls,
	    Chain_of_available_remote_procedure_calls);
    record_system_variable(Qchain_of_available_remote_procedure_calls,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qremote_procedure_call_count = 
	    STATIC_SYMBOL("REMOTE-PROCEDURE-CALL-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_procedure_call_count,
	    Remote_procedure_call_count);
    record_system_variable(Qremote_procedure_call_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_remote_procedure_calls_vector == UNBOUND)
	Chain_of_available_remote_procedure_calls_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qremote_procedure_call_structure_memory_usage,
	    STATIC_FUNCTION(remote_procedure_call_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_remote_procedure_call_count,
	    STATIC_FUNCTION(outstanding_remote_procedure_call_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_remote_procedure_call_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_remote_procedure_call,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qremote_procedure_call,
	    reclaim_structure_for_remote_procedure_call_1);
    Qg2_defstruct_structure_name_system_rpc_g2_struct = 
	    STATIC_SYMBOL("SYSTEM-RPC-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsystem_rpc = STATIC_SYMBOL("SYSTEM-RPC",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_system_rpc_g2_struct,
	    Qsystem_rpc,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsystem_rpc,
	    Qg2_defstruct_structure_name_system_rpc_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_system_rpc == UNBOUND)
	The_type_description_of_system_rpc = Nil;
    string_constant_71 = 
	    STATIC_STRING("43Dy8m83nby1n83nby8n8k1l8n0000001l1n8y83-60y1n83-EEy83-EAy83-EFykok0k0");
    temp = The_type_description_of_system_rpc;
    The_type_description_of_system_rpc = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_71));
    mutate_global_property(Qg2_defstruct_structure_name_system_rpc_g2_struct,
	    The_type_description_of_system_rpc,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsystem_rpc,The_type_description_of_system_rpc,
	    Qtype_description_of_type);
    Qoutstanding_system_rpc_count = 
	    STATIC_SYMBOL("OUTSTANDING-SYSTEM-RPC-COUNT",AB_package);
    Qsystem_rpc_structure_memory_usage = 
	    STATIC_SYMBOL("SYSTEM-RPC-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_72 = STATIC_STRING("1q83nby8s83-rqy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_system_rpc_count);
    push_optimized_constant(Qsystem_rpc_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_72));
    Qchain_of_available_system_rpcs = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SYSTEM-RPCS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_system_rpcs,
	    Chain_of_available_system_rpcs);
    record_system_variable(Qchain_of_available_system_rpcs,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qsystem_rpc_count = STATIC_SYMBOL("SYSTEM-RPC-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsystem_rpc_count,System_rpc_count);
    record_system_variable(Qsystem_rpc_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_system_rpcs_vector == UNBOUND)
	Chain_of_available_system_rpcs_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsystem_rpc_structure_memory_usage,
	    STATIC_FUNCTION(system_rpc_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_system_rpc_count,
	    STATIC_FUNCTION(outstanding_system_rpc_count,NIL,FALSE,0,0));
    reclaim_structure_for_system_rpc_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_system_rpc,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsystem_rpc,
	    reclaim_structure_for_system_rpc_1);
    Qavailable_procedure_invocations_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_procedure_invocations_hash_vector_43_vectors,
	    Available_procedure_invocations_hash_vector_43_vectors);
    record_system_variable(Qavailable_procedure_invocations_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_procedure_invocations_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_procedure_invocations_hash_vector_43_vectors,
	    Count_of_procedure_invocations_hash_vector_43_vectors);
    record_system_variable(Qcount_of_procedure_invocations_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_procedure_invocations_hash_vector_43_vectors_vector == 
	    UNBOUND)
	Available_procedure_invocations_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_procedure_invocations_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qprocedure_invocations_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATIONS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_73 = STATIC_STRING("1q83-9Qy83*9y83t7y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_procedure_invocations_hash_vector_43_vectors);
    push_optimized_constant(Qprocedure_invocations_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_73));
    SET_SYMBOL_FUNCTION(Qprocedure_invocations_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(procedure_invocations_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_procedure_invocations_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_procedure_invocations_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qprocedure_invocations_tree_for_hash = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATIONS-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qitem,Qentity);
    check_if_superior_classes_are_defined(Qprocedure,list_constant_3);
    string_constant_74 = 
	    STATIC_STRING("1n1m8v83=Vy1l8t1m83-Cy53-PyProcedures provide a means of encoding multi-threaded, ~\n                structured programs.");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_75 = 
	    STATIC_STRING("13Gy4z8r83--y83--y83=Vy83=Vy00001p1l8l1m8p83-*y1m83Dy53*uyWill allow 0 or more author entries. each author entry may have a date");
    string_constant_76 = 
	    STATIC_STRING(". ~\nauthors: ([ name: symbol, date: gensym-time ] * ), ~\neditor-grammar: struct, defining-class: item, writable: true\n1l83Ey1l83");
    string_constant_77 = 
	    STATIC_STRING("Uy000004z8r83W4y83W4y83=Vy83=Vy0k001n1l8l1l83Hy1l83Ny000004z8r83-0y83-0y83=Vy83=Vy00001q1l8l1m8p83-0y1l83Fy1l83Ey1l83Uy1m83Dy53-");
    string_constant_78 = 
	    STATIC_STRING("Fy(to replace authors attribute; however, no documentation is available at this time)000004z8r83-Fy83-Fy83=Vy83=Vy00001q1l8l1m8p");
    string_constant_79 = 
	    STATIC_STRING("01l83Cy1m83Dy53KyAlias as procedure-name\?1l83Uy1l83*-y000004z8r83-py83-py83=Vy83=Vy00001q1l83Ey1l8l1l8z1l83Cy1m8p83-py1m83Dy53*Q");
    string_constant_80 = 
	    STATIC_STRING("y[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or default &lt;integer&gt;), ~\nbreakpoint-level");
    string_constant_81 = 
	    STATIC_STRING(": (or default &lt;integer&gt;)]000004z8r8u8u83=Vy83=Vy01s8w9k3-My3-My1p1p83Jy1mkk1m3-Myk1m3-My3-My1mk3-My1p83Jy1mww1m3iyw1m3iy3K");
    string_constant_82 = 
	    STATIC_STRING("y1mw3Ky1p83Jy1mw3iy1m3iy3iy1m3iy3uy1mw3uy1p83Jy1m3cy3Qy1m3-Ay3Qy1m3-Ay3cy1m3cy3cy1p83Jy1m3cy3-*y1m3-Ay3-*y1m3-Ay3-Ay1m3cy3-Ay03*");
    string_constant_83 = 
	    STATIC_STRING("dy3*dy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r833ky833ky83=Vy83=Vy00001q1m8p837xy1l8o1l8l1l8z1l");
    string_constant_84 = 
	    STATIC_STRING("83Cy1m83Dy530+yThe name of a subclass of procedure-invocation (or procedure-invocation ~\n       itself).  Within this procedure,");
    string_constant_85 = 
	    STATIC_STRING(" the expression \"this ~\n       procedure-invocation\" will return a unique instance of this class for ~\n       this execution of ");
    string_constant_86 = 
	    STATIC_STRING("this procedure.000004z8r833ry833ry83=Vy83=Vy0q001p1m8p83-Yy1l8o1l8l1l8z1l83Cy000004z8r834ny834ny83=Vy83=Vy083Py001p1m8p838Gy1l8o");
    string_constant_87 = 
	    STATIC_STRING("1l8z1l8l1l83Cy000004z8r835*y835*y83=Vy83=Vy0k001o1l8o1l8l1l83Cy1m83Dy53TyExport: integer, writable = false000004z8r835=y835=y83=");
    string_constant_88 = 
	    STATIC_STRING("Vy83=Vy00001o1l8o1l8l1l83Cy1m83Dy53jyExport list of type descriptors, writable = false000004z8r836Cy836Cy83=Vy83=Vy00001o1l8o1l8");
    string_constant_89 = 
	    STATIC_STRING("l1l83Cy1m83Dy53jyExport list of type descriptors, writable = false000004z8r836=y836=y83=Vy83=Vy00001o1l8o1l8l1l83Hy1m83Dy53byExp");
    string_constant_90 = 
	    STATIC_STRING("ort - debugging, process monitoring\?\?\?000004z8r834Qy834Qy83=Vy83=Vy00001r1o8p834Qy83Gy83=Vy1l8o1l8l1l83Cy1l83-3y1l83-5y1m83Dy5zE");
    string_constant_91 = 
	    STATIC_STRING("xport as text.000004z8r836-y836-y83=Vy83=Vy00001o1l8o1l8l1l83Cy1l83Uy000004z8r836*y836*y83=Vy83=Vy0l001o1l8o1l8l1l83Cy1m83Dy53cy");
    string_constant_92 = 
	    STATIC_STRING("Add attribute-mimics for individual flags.000004z8r83Xdy83Xdy83=Vy83=Vy00001m1l8l1l83Cy000004z8r83V2y83V2y83=Vy83=Vy00001m1l8l1l");
    string_constant_93 = 
	    STATIC_STRING("83Cy000004z8r83KBy83KBy83=Vy83=Vy00001m1l8l1l83Cy000004z8r83RHy83RHy83=Vy83=Vy00001m1l8l1l83Cy00000");
    string_constant_94 = 
	    STATIC_STRING("13Iy8q1p83=Vy1m83Ry83-+y1m8v83=Vy8t1m83-Cy53-PyProcedures provide a means of encoding multi-threaded, ~\n                structur");
    string_constant_95 = 
	    STATIC_STRING("ed programs.1o83--y01m8p83-*y1m83Dy53*uyWill allow 0 or more author entries. each author entry may have a date. ~\nauthors: ([ na");
    string_constant_96 = 
	    STATIC_STRING("me: symbol, date: gensym-time ] * ), ~\neditor-grammar: struct, defining-class: item, writable: true\n1p83W4yk8l83Hy83Ny1n83-0y01m");
    string_constant_97 = 
	    STATIC_STRING("8p83-0y1q83-Fy08l1m8p083Cy1m83Dy53KyAlias as procedure-name\?1r83-py083Ey8l8z83Cy1m8p83-py1m8u1s8w9k3-My3-My1p1p83Jy1mkk1m3-Myk1m");
    string_constant_98 = 
	    STATIC_STRING("3-My3-My1mk3-My1p83Jy1mww1m3iyw1m3iy3Ky1mw3Ky1p83Jy1mw3iy1m3iy3iy1m3iy3uy1mw3uy1p83Jy1m3cy3Qy1m3-Ay3Qy1m3-Ay3cy1m3cy3cy1p83Jy1m3");
    string_constant_99 = 
	    STATIC_STRING("cy3-*y1m3-Ay3-*y1m3-Ay3-Ay1m3cy3-Ay03*dy3*dy1s833ky01m8p837xy8o8l8z83Cy1m83Dy530+yThe name of a subclass of procedure-invocation");
    string_constant_100 = 
	    STATIC_STRING(" (or procedure-invocation ~\n       itself).  Within this procedure, the expression \"this ~\n       procedure-invocation\" will ret");
    string_constant_101 = 
	    STATIC_STRING("urn a unique instance of this class for ~\n       this execution of this procedure.1r833ryq1m8p83-Yy8o8l8z83Cy1r834ny83Py1m8p838G");
    string_constant_102 = 
	    STATIC_STRING("y8o8z8l83Cy1q835*yk8o8l83Cy1m83Dy53TyExport: integer, writable = false1q835=y08o8l83Cy1m83Dy53jyExport list of type descriptors,");
    string_constant_103 = 
	    STATIC_STRING(" writable = false1q836Cy08o8l83Cy1m83Dy53jyExport list of type descriptors, writable = false1q836=y08o8l83Hy1m83Dy53byExport - d");
    string_constant_104 = 
	    STATIC_STRING("ebugging, process monitoring\?\?\?1t834Qy01o8p834Qy83Gy83=Vy8o8l83Cy83-3y83-5y1m83Dy5zExport as text.1q836-y08o8l83Cy83Uy1q836*yl8o");
    string_constant_105 = 
	    STATIC_STRING("8l83Cy1m83Dy53cyAdd attribute-mimics for individual flags.1o83Xdy08l83Cy1o83V2y08l83Cy1o83KBy08l83Cy1o83RHy08l83Cy");
    temp = regenerate_optimized_constant(string_constant_74);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(19,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80,string_constant_81,
	    string_constant_82,string_constant_83,string_constant_84,
	    string_constant_85,string_constant_86,string_constant_87,
	    string_constant_88,string_constant_89,string_constant_90,
	    string_constant_91,string_constant_92,string_constant_93));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qprocedure,list_constant_3,Nil,temp,Nil,
	    temp_1,list_constant_3,regenerate_optimized_constant(list(12,
	    string_constant_94,string_constant_95,string_constant_96,
	    string_constant_97,string_constant_98,string_constant_99,
	    string_constant_100,string_constant_101,string_constant_102,
	    string_constant_103,string_constant_104,string_constant_105)),Nil);
    Procedure_class_description = 
	    lookup_global_or_kb_specific_property_value(Qprocedure,
	    Class_description_gkbprop);
    Qhas_empty_code_body_qm = STATIC_SYMBOL("HAS-EMPTY-CODE-BODY\?",
	    AB_package);
    Qinlined_calls = STATIC_SYMBOL("INLINED-CALLS",AB_package);
    temp_2 = CONS(Qinlined_calls,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    Qvirtual_attributes_local_to_class = 
	    STATIC_SYMBOL("VIRTUAL-ATTRIBUTES-LOCAL-TO-CLASS",AB_package);
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qprocedure),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qinlined_calls,temp);
    set_property_value_function(get_symbol_properties_function(Qprocedure),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qsequence,Qsymbol);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_5 = STATIC_CONS(Qno_item,Qnil);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_4,
	    list_constant_5);
    Qinitial_inlined_calls = STATIC_SYMBOL("INITIAL-INLINED-CALLS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_inlined_calls,
	    STATIC_FUNCTION(initial_inlined_calls,NIL,FALSE,1,1));
    Qget_inlined_calls = STATIC_SYMBOL("GET-INLINED-CALLS",AB_package);
    SET_SYMBOL_FUNCTION(Qget_inlined_calls,
	    STATIC_FUNCTION(get_inlined_calls,NIL,FALSE,1,1));
    add_virtual_attribute(Qinlined_calls,list_constant_6,list_constant_7,
	    Qnil,SYMBOL_FUNCTION(Qinitial_inlined_calls),
	    SYMBOL_FUNCTION(Qget_inlined_calls),Nil);
    Qprocedure_invocations = STATIC_SYMBOL("PROCEDURE-INVOCATIONS",AB_package);
    Qreclaim_procedure_invocations_value = 
	    STATIC_SYMBOL("RECLAIM-PROCEDURE-INVOCATIONS-VALUE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_procedure_invocations_value,
	    STATIC_FUNCTION(reclaim_procedure_invocations_value,NIL,FALSE,
	    2,2));
    mutate_global_property(Qprocedure_invocations,
	    SYMBOL_FUNCTION(Qreclaim_procedure_invocations_value),
	    Qslot_value_reclaimer);
    Qn_compiles_this_session = STATIC_SYMBOL("N-COMPILES-THIS-SESSION",
	    AB_package);
    Quninterrupted_procedure_execution_limit_qm = 
	    STATIC_SYMBOL("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT\?",
	    AB_package);
    Quninterrupted_procedure_execution_limit = 
	    STATIC_SYMBOL("UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT",
	    AB_package);
    alias_slot_name(3,Quninterrupted_procedure_execution_limit_qm,
	    Quninterrupted_procedure_execution_limit,Qprocedure);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    alias_slot_name(3,Qprocedure_definition,Qtext,Qprocedure);
    Qprocedure_flags = STATIC_SYMBOL("PROCEDURE-FLAGS",AB_package);
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    Qprocedure_code_bodies_3_dot_0_beta = 
	    STATIC_SYMBOL("PROCEDURE-CODE-BODIES-3.0-BETA",AB_package);
    Procedure_code_bodies_slot_name = Qprocedure_code_bodies_3_dot_0_beta;
    Qdisassembled_code = STATIC_SYMBOL("DISASSEMBLED-CODE",AB_package);
    alias_slot_name(3,Qprocedure_code_bodies_3_dot_0_beta,
	    Qdisassembled_code,Qnil);
    Qput_procedure_code_bodies_3_dot_0_beta = 
	    STATIC_SYMBOL("PUT-PROCEDURE-CODE-BODIES-3.0-BETA",AB_package);
    SET_SYMBOL_FUNCTION(Qput_procedure_code_bodies_3_dot_0_beta,
	    STATIC_FUNCTION(put_procedure_code_bodies_3_dot_0_beta,NIL,
	    FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qprocedure_code_bodies_3_dot_0_beta,
	    SYMBOL_FUNCTION(Qput_procedure_code_bodies_3_dot_0_beta),
	    Qslot_putter);
    Qcode_bodies_3_dot_0_alpha = STATIC_SYMBOL("CODE-BODIES-3.0-ALPHA",
	    AB_package);
    Qput_code_bodies_3_dot_0_alpha_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CODE-BODIES-3.0-ALPHA-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_code_bodies_3_dot_0_alpha_where_slot_is_absent,
	    STATIC_FUNCTION(put_code_bodies_3_dot_0_alpha_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcode_bodies_3_dot_0_alpha,
	    SYMBOL_FUNCTION(Qput_code_bodies_3_dot_0_alpha_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qprocedure_free_references = STATIC_SYMBOL("PROCEDURE-FREE-REFERENCES",
	    AB_package);
    Qput_procedure_free_references_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-PROCEDURE-FREE-REFERENCES-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_procedure_free_references_where_slot_is_absent,
	    STATIC_FUNCTION(put_procedure_free_references_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qprocedure_free_references,
	    SYMBOL_FUNCTION(Qput_procedure_free_references_where_slot_is_absent),
	    Qabsent_slot_putter);
    if (List_of_previously_optimized_procedures == UNBOUND)
	List_of_previously_optimized_procedures = Nil;
    Qoptimize_procedure_code_qm = 
	    STATIC_SYMBOL("OPTIMIZE-PROCEDURE-CODE\?",AB_package);
    Qput_optimize_procedure_code_qm_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-OPTIMIZE-PROCEDURE-CODE\?-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_optimize_procedure_code_qm_where_slot_is_absent,
	    STATIC_FUNCTION(put_optimize_procedure_code_qm_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qoptimize_procedure_code_qm,
	    SYMBOL_FUNCTION(Qput_optimize_procedure_code_qm_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qrecompile_previously_optimized_procedures = 
	    STATIC_SYMBOL("RECOMPILE-PREVIOUSLY-OPTIMIZED-PROCEDURES",
	    AB_package);
    temp_2 = adjoin(2,Qrecompile_previously_optimized_procedures,
	    List_of_once_only_switched_post_loading_functions);
    List_of_once_only_switched_post_loading_functions = temp_2;
    temp_2 = adjoin(2,Qrecompile_previously_optimized_procedures,
	    List_of_switched_and_module_post_loading_functions);
    List_of_switched_and_module_post_loading_functions = temp_2;
    SET_SYMBOL_FUNCTION(Qrecompile_previously_optimized_procedures,
	    STATIC_FUNCTION(recompile_previously_optimized_procedures,NIL,
	    FALSE,0,0));
    Qparse_results_qm = STATIC_SYMBOL("PARSE-RESULTS\?",AB_package);
    Qput_parse_results_qm = STATIC_SYMBOL("PUT-PARSE-RESULTS\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_parse_results_qm,
	    STATIC_FUNCTION(put_parse_results_qm,NIL,FALSE,3,3));
    mutate_global_property(Qparse_results_qm,
	    SYMBOL_FUNCTION(Qput_parse_results_qm),Qslot_putter);
    Qmd5_identifier_qm = STATIC_SYMBOL("MD5-IDENTIFIER\?",AB_package);
    Qput_md5_identifier_qm = STATIC_SYMBOL("PUT-MD5-IDENTIFIER\?",AB_package);
    SET_SYMBOL_FUNCTION(Qput_md5_identifier_qm,
	    STATIC_FUNCTION(put_md5_identifier_qm,NIL,FALSE,3,3));
    mutate_global_property(Qmd5_identifier_qm,
	    SYMBOL_FUNCTION(Qput_md5_identifier_qm),Qslot_putter);
    string_constant = 
	    STATIC_STRING("Aborting procedure invocations of ~NF before compiling this procedure.");
    Qcompile_procedure_definition_for_slot = 
	    STATIC_SYMBOL("COMPILE-PROCEDURE-DEFINITION-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_procedure_definition_for_slot,
	    STATIC_FUNCTION(compile_procedure_definition_for_slot,NIL,TRUE,
	    3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qprocedure_definition,
	    SYMBOL_FUNCTION(Qcompile_procedure_definition_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qprocedure_definition,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qclass_of_procedure_invocation = 
	    STATIC_SYMBOL("CLASS-OF-PROCEDURE-INVOCATION",AB_package);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qdynamic_breakpoint_settings = 
	    STATIC_SYMBOL("DYNAMIC-BREAKPOINT-SETTINGS",AB_package);
    Qput_procedure_definition = STATIC_SYMBOL("PUT-PROCEDURE-DEFINITION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_procedure_definition,
	    STATIC_FUNCTION(put_procedure_definition,NIL,FALSE,3,3));
    mutate_global_property(Qprocedure_definition,
	    SYMBOL_FUNCTION(Qput_procedure_definition),Qslot_putter);
    Qdynamic_breakpoint_enabled = 
	    STATIC_SYMBOL("DYNAMIC-BREAKPOINT-ENABLED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_breakpoint_enabled,
	    Dynamic_breakpoint_enabled);
    Kenabled = STATIC_SYMBOL("ENABLED",Pkeyword);
    SET_SYMBOL_VALUE(Qdynamic_breakpoint_enabled,Kenabled);
    Qdynamic_breakpoint_disabled = 
	    STATIC_SYMBOL("DYNAMIC-BREAKPOINT-DISABLED",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_breakpoint_disabled,
	    Dynamic_breakpoint_disabled);
    Kdisabled = STATIC_SYMBOL("DISABLED",Pkeyword);
    SET_SYMBOL_VALUE(Qdynamic_breakpoint_disabled,Kdisabled);
    Qdynamic_breakpoint_valid = STATIC_SYMBOL("DYNAMIC-BREAKPOINT-VALID",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_breakpoint_valid,
	    Dynamic_breakpoint_valid);
    Kvalid = STATIC_SYMBOL("VALID",Pkeyword);
    SET_SYMBOL_VALUE(Qdynamic_breakpoint_valid,Kvalid);
    Qdynamic_breakpoint_invalid = 
	    STATIC_SYMBOL("DYNAMIC-BREAKPOINT-INVALID",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_breakpoint_invalid,
	    Dynamic_breakpoint_invalid);
    Kinvalid = STATIC_SYMBOL("INVALID",Pkeyword);
    SET_SYMBOL_VALUE(Qdynamic_breakpoint_invalid,Kinvalid);
    Qinvalid_dynamic_breakpoint = 
	    STATIC_SYMBOL("INVALID-DYNAMIC-BREAKPOINT",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_1 = 
	    STATIC_STRING("there ~a invalid dynamic breakpoint~a on line~a");
    string_constant_2 = STATIC_STRING("are");
    string_constant_3 = STATIC_STRING("is an");
    string_constant_4 = STATIC_STRING("s");
    string_constant_5 = STATIC_STRING("");
    string_constant_6 = STATIC_STRING(" ~a");
    string_constant_7 = STATIC_STRING(", ");
    string_constant_8 = STATIC_STRING(" and ");
    write_invalid_dynamic_breakpoint_note_1 = 
	    STATIC_FUNCTION(write_invalid_dynamic_breakpoint_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qinvalid_dynamic_breakpoint,
	    write_invalid_dynamic_breakpoint_note_1,Qframe_note_writer_1);
    Qframe_status_and_notes = STATIC_SYMBOL("FRAME-STATUS-AND-NOTES",
	    AB_package);
    Qstack_change = STATIC_SYMBOL("STACK-CHANGE",AB_package);
    Qdynamic_breakpoints = STATIC_SYMBOL("DYNAMIC-BREAKPOINTS",AB_package);
    temp_2 = CONS(Qdynamic_breakpoints,All_virtual_attributes);
    All_virtual_attributes = temp_2;
    temp = get_property_value_function(3,
	    get_symbol_properties_function(Qprocedure),
	    Qvirtual_attributes_local_to_class,Nil);
    temp_2 = CONS(Qdynamic_breakpoints,temp);
    set_property_value_function(get_symbol_properties_function(Qprocedure),
	    Qvirtual_attributes_local_to_class,temp_2);
    Qline_number = STATIC_SYMBOL("LINE-NUMBER",AB_package);
    Qis_enabled = STATIC_SYMBOL("IS-ENABLED",AB_package);
    Qis_valid = STATIC_SYMBOL("IS-VALID",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qline_number,Qinteger);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_8 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_10 = STATIC_CONS(Qis_enabled,list_constant_8);
    list_constant_11 = STATIC_CONS(Qis_valid,list_constant_8);
    list_constant_12 = STATIC_LIST((SI_Long)3L,list_constant_9,
	    list_constant_10,list_constant_11);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qand,Qline_number,Qis_enabled);
    list_constant_14 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_12,list_constant_13);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_14);
    Qinitial_dynamic_breakpoints = 
	    STATIC_SYMBOL("INITIAL-DYNAMIC-BREAKPOINTS",AB_package);
    SET_SYMBOL_FUNCTION(Qinitial_dynamic_breakpoints,
	    STATIC_FUNCTION(initial_dynamic_breakpoints,NIL,FALSE,1,1));
    Qget_dynamic_breakpoints = STATIC_SYMBOL("GET-DYNAMIC-BREAKPOINTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_dynamic_breakpoints,
	    STATIC_FUNCTION(get_dynamic_breakpoints,NIL,FALSE,1,1));
    Qset_dynamic_breakpoints = STATIC_SYMBOL("SET-DYNAMIC-BREAKPOINTS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qset_dynamic_breakpoints,
	    STATIC_FUNCTION(set_dynamic_breakpoints,NIL,FALSE,2,2));
    add_virtual_attribute(Qdynamic_breakpoints,list_constant_6,
	    list_constant_15,Qnil,
	    SYMBOL_FUNCTION(Qinitial_dynamic_breakpoints),
	    SYMBOL_FUNCTION(Qget_dynamic_breakpoints),
	    SYMBOL_FUNCTION(Qset_dynamic_breakpoints));
    Qinitialize_for_procedure = STATIC_SYMBOL("INITIALIZE-FOR-PROCEDURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_procedure,
	    STATIC_FUNCTION(initialize_for_procedure,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_procedure);
    set_get(Qprocedure,Qinitialize,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_procedure = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-PROCEDURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_procedure,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_procedure,
	    NIL,FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_procedure);
    set_get(Qprocedure,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    string_constant_9 = 
	    STATIC_STRING("Aborting procedure invocations of ~NF before deactivating this ~\n               procedure.");
    Qcleanup_for_procedure = STATIC_SYMBOL("CLEANUP-FOR-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_procedure,
	    STATIC_FUNCTION(cleanup_for_procedure,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_procedure);
    set_get(Qprocedure,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qnote_runs_while_inactive_change_for_procedure = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE-FOR-PROCEDURE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_procedure,
	    STATIC_FUNCTION(note_runs_while_inactive_change_for_procedure,
	    NIL,FALSE,1,1));
    Qnote_runs_while_inactive_change = 
	    STATIC_SYMBOL("NOTE-RUNS-WHILE-INACTIVE-CHANGE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qnote_runs_while_inactive_change_for_procedure);
    set_get(Qprocedure,Qnote_runs_while_inactive_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_runs_while_inactive_change),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure,temp);
    mutate_global_property(Qnote_runs_while_inactive_change,temp_2,
	    Qclasses_which_define);
    Qmanually_disable_for_procedure = 
	    STATIC_SYMBOL("MANUALLY-DISABLE-FOR-PROCEDURE",AB_package);
    SET_SYMBOL_FUNCTION(Qmanually_disable_for_procedure,
	    STATIC_FUNCTION(manually_disable_for_procedure,NIL,FALSE,1,1));
    Qmanually_disable = STATIC_SYMBOL("MANUALLY-DISABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qmanually_disable_for_procedure);
    set_get(Qprocedure,Qmanually_disable,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qmanually_disable),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure,temp);
    mutate_global_property(Qmanually_disable,temp_2,Qclasses_which_define);
    mutate_global_property(Qg2_defstruct_structure_name_procedure_invocation_g2_struct,
	    Qprocedure_invocation,Qab_name_of_unique_structure_type);
    mutate_global_property(Qprocedure_invocation,
	    Qg2_defstruct_structure_name_procedure_invocation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_procedure_invocation == UNBOUND)
	The_type_description_of_procedure_invocation = Nil;
    string_constant_106 = 
	    STATIC_STRING("43Dy8m831jy1p831jy833my830Ey8n8k1l833my0000001l1m8x833myk3Oyk0k0");
    temp = The_type_description_of_procedure_invocation;
    The_type_description_of_procedure_invocation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_106));
    mutate_global_property(Qg2_defstruct_structure_name_procedure_invocation_g2_struct,
	    The_type_description_of_procedure_invocation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qprocedure_invocation,
	    The_type_description_of_procedure_invocation,
	    Qtype_description_of_type);
    Qoutstanding_procedure_invocation_count = 
	    STATIC_SYMBOL("OUTSTANDING-PROCEDURE-INVOCATION-COUNT",AB_package);
    Qprocedure_invocation_structure_memory_usage = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_107 = STATIC_STRING("1q831jy8s83-kRy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_procedure_invocation_count);
    push_optimized_constant(Qprocedure_invocation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_107));
    Qchain_of_available_procedure_invocations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PROCEDURE-INVOCATIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_procedure_invocations,
	    Chain_of_available_procedure_invocations);
    record_system_variable(Qchain_of_available_procedure_invocations,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qprocedure_invocation_count = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qprocedure_invocation_count,
	    Procedure_invocation_count);
    record_system_variable(Qprocedure_invocation_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_procedure_invocations_vector == UNBOUND)
	Chain_of_available_procedure_invocations_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qprocedure_invocation_structure_memory_usage,
	    STATIC_FUNCTION(procedure_invocation_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_procedure_invocation_count,
	    STATIC_FUNCTION(outstanding_procedure_invocation_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_procedure_invocation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_procedure_invocation,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qprocedure_invocation,
	    reclaim_structure_for_procedure_invocation_1);
    check_if_superior_classes_are_defined(Qprocedure_invocation,
	    list_constant_3);
    string_constant_108 = STATIC_STRING("1m1m8v831jy1l83ey");
    string_constant_109 = 
	    STATIC_STRING("1l4z8r83YIy83YIy831jy831jy00001n1l8o1l8l1l83Hy00000");
    string_constant_110 = 
	    STATIC_STRING("1n8q1o831jy1m83Ry83-+y1m8v831jy83ey1p83YIy08o8l83Hy");
    temp = regenerate_optimized_constant(string_constant_108);
    temp_1 = regenerate_optimized_constant(string_constant_109);
    add_class_to_environment(9,Qprocedure_invocation,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(string_constant_110),Nil);
    Procedure_invocation_class_description = 
	    lookup_global_or_kb_specific_property_value(Qprocedure_invocation,
	    Class_description_gkbprop);
    Qcleanup_for_procedure_invocation = 
	    STATIC_SYMBOL("CLEANUP-FOR-PROCEDURE-INVOCATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_procedure_invocation,
	    STATIC_FUNCTION(cleanup_for_procedure_invocation,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_procedure_invocation);
    set_get(Qprocedure_invocation,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qprocedure_invocation,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_10 = STATIC_STRING("~NF");
    string_constant_11 = STATIC_STRING("<error printing argument, ~a>");
    if (Within_writing_procedure_invocation_p == UNBOUND)
	Within_writing_procedure_invocation_p = Nil;
    array_constant_1 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)24L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)57344L);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qexecute_computation_instance = 
	    STATIC_SYMBOL("EXECUTE-COMPUTATION-INSTANCE",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qschedule_computation_instance_execution = 
	    STATIC_SYMBOL("SCHEDULE-COMPUTATION-INSTANCE-EXECUTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qschedule_computation_instance_execution,
	    STATIC_FUNCTION(schedule_computation_instance_execution,NIL,
	    FALSE,3,3));
    Qforgive_long_procedure_instruction_qm = 
	    STATIC_SYMBOL("FORGIVE-LONG-PROCEDURE-INSTRUCTION\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qforgive_long_procedure_instruction_qm,
	    Forgive_long_procedure_instruction_qm);
    record_system_variable(Qforgive_long_procedure_instruction_qm,
	    Qproc_utils,Nil,Qnil,Qnil,Qnil,Qnil);
    if (Code_body == UNBOUND)
	Code_body = Nil;
    string_constant_12 = 
	    STATIC_STRING("~a statements may not be executed within simulation procedures.");
    Kreturn_value = STATIC_SYMBOL("RETURN-VALUE",Pkeyword);
    string_constant_13 = STATIC_STRING("RETURN-VALUE-~a");
    array_constant_4 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)57344L);
    string_constant_14 = STATIC_STRING("LOCAL-~a");
    string_constant_15 = STATIC_STRING("LOCAL-~a-~a");
    array_constant_5 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)30L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)57344L);
    string_constant_16 = STATIC_STRING("~NT");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)57344L);
    if (Allow_internal_procedure_environment_printing_qm == UNBOUND)
	Allow_internal_procedure_environment_printing_qm = Nil;
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    string_constant_17 = STATIC_STRING(";~%");
    array_constant_7 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)57344L);
    string_constant_18 = STATIC_STRING("~%Stack:");
    string_constant_19 = STATIC_STRING("~%No values on stack");
    string_constant_20 = STATIC_STRING(" (top ~a values not shown)");
    string_constant_21 = STATIC_STRING("~%~a = ");
    array_constant_11 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    string_constant_22 = STATIC_STRING("<DEBUG DATA: ~a>");
    array_constant_12 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)57344L);
    Qwake_up_code_body_invocation = 
	    STATIC_SYMBOL("WAKE-UP-CODE-BODY-INVOCATION",AB_package);
    SET_SYMBOL_FUNCTION(Qwake_up_code_body_invocation,
	    STATIC_FUNCTION(wake_up_code_body_invocation,NIL,FALSE,1,1));
    string_constant_23 = 
	    STATIC_STRING("The wrong number of arguments were passed to ~NF from ~NF.  It needs~\n     ~a~a argument~a but received ~a.");
    string_constant_24 = STATIC_STRING(" at least ");
    string_constant_25 = STATIC_STRING(" ");
    Kall_remaining = STATIC_SYMBOL("ALL-REMAINING",Pkeyword);
    Qhandle = STATIC_SYMBOL("HANDLE",AB_package);
    Kkind = STATIC_SYMBOL("KIND",Pkeyword);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    string_constant_26 = 
	    STATIC_STRING("Internal G2 error: bad procedure ~a while preparing arguments.");
    string_constant_27 = 
	    STATIC_STRING("Attempt to pass an inactive item as argument number ~A to ~\n               the procedure ~NF which cannot refer to inactive items.");
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    array_constant_13 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    string_constant_28 = 
	    STATIC_STRING(" argument of ~NF is declared to take values of type ~\n       ~NT, but instead it received ");
    string_constant_29 = STATIC_STRING("~NF, an instance of the class ~a.");
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    string_constant_30 = 
	    STATIC_STRING("  Note that if you intended to pass the value of this variable, you ~\n         must use a COLLECT DATA statement to fetch its value.");
    string_constant_31 = 
	    STATIC_STRING("~NA requires ~a argument~a and received ~a.");
    string_constant_32 = 
	    STATIC_STRING(" argument of ~NA is declared to take values of type ~\n                   ~a, but this procedure received a bad value instead.");
    Qg2_defstruct_structure_name_receiving_resumable_object_g2_struct = 
	    STATIC_SYMBOL("RECEIVING-RESUMABLE-OBJECT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qunsigned_vector_16 = STATIC_SYMBOL("UNSIGNED-VECTOR-16",AB_package);
    string_constant_33 = 
	    STATIC_STRING(" argument of ~NA is declared to take values of type ~\n                        ~NT, but it received NO-VALUE.");
    Qevaluation_value = STATIC_SYMBOL("EVALUATION-VALUE",AB_package);
    list_constant_17 = STATIC_CONS(list_constant_5,Qnil);
    list_constant = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qevaluation_value,
	    list_constant_17);
    string_constant_34 = 
	    STATIC_STRING(" argument of ~NA is declared to take values of type ~\n                        ~NT, but it received ~NF, ~\n                        an instance of the class ~a.");
    Qlong = STATIC_SYMBOL("LONG",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qseconds,Qinterval);
    string_constant_35 = 
	    STATIC_STRING(" argument of ~NA is declared to take values ~\n                        of type ~NT, but it received ");
    array_constant_14 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)57344L);
    string_constant_36 = 
	    STATIC_STRING(" argument of ~NA is declared to take instances  ~\n                         of the class ~a, but it received the value ");
    string_constant_37 = 
	    STATIC_STRING(" argument of ~NF is declared to take instances of the ~\n                      class ~a, but it received ~NF, ~\n                      an instance of the class ~a.");
    Qtop_level_procedure_invocations_array = 
	    STATIC_SYMBOL("TOP-LEVEL-PROCEDURE-INVOCATIONS-ARRAY",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtop_level_procedure_invocations_array,
	    Top_level_procedure_invocations_array);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qallocate_managed_array = STATIC_SYMBOL("ALLOCATE-MANAGED-ARRAY",
	    AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Kfuncall,
	    Qallocate_managed_array,FIX((SI_Long)0L));
    record_system_variable(Qtop_level_procedure_invocations_array,
	    Qproc_utils,list_constant_18,Qnil,Qnil,Qnil,Qnil);
    Qminimum_available_procedure_invocation_index = 
	    STATIC_SYMBOL("MINIMUM-AVAILABLE-PROCEDURE-INVOCATION-INDEX",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qminimum_available_procedure_invocation_index,
	    Minimum_available_procedure_invocation_index);
    record_system_variable(Qminimum_available_procedure_invocation_index,
	    Qproc_utils,FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    string_constant_111 = STATIC_STRING("PROCEDURE-INVOCATION-LOCK");
    if (Procedure_invocations_lock == UNBOUND)
	Procedure_invocations_lock = make_recursive_lock(2,Kname,
		string_constant_111);
    Kerror_string = STATIC_SYMBOL("ERROR-STRING",Pkeyword);
    Qstart = STATIC_SYMBOL("START",AB_package);
    Qcall = STATIC_SYMBOL("CALL",AB_package);
    string_constant_38 = 
	    STATIC_STRING("Cannot ~a method-declaration ~NF.  ~a");
    string_constant_39 = STATIC_STRING("start");
    string_constant_40 = STATIC_STRING("call");
    string_constant_41 = STATIC_STRING("~NW");
    string_constant_42 = STATIC_STRING("Cannot execute ~NF because it is ~a.");
    Qprocedure_invocaton = STATIC_SYMBOL("PROCEDURE-INVOCATON",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    string_constant_43 = 
	    STATIC_STRING("The class of procedure invocation attribute of ~NF, ~a, was ~\n          not procedure-invocation or a subclass of procedure-invocation.");
    string_constant_44 = 
	    STATIC_STRING("Call to ~NF has argument count mismatch.");
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    if (Closing_procedure_invocation == UNBOUND)
	Closing_procedure_invocation = Nil;
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    Qaction_cache = STATIC_SYMBOL("ACTION-CACHE",AB_package);
    array_constant_15 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)15L,(SI_Long)57344L);
    string_constant_45 = 
	    STATIC_STRING("Aborting procedure invocations while resetting G2.");
    string_constant_46 = STATIC_STRING("~%Aborting procedure stack from ");
    string_constant_47 = STATIC_STRING(".");
    Qclear_computation_context_variables = 
	    STATIC_SYMBOL("CLEAR-COMPUTATION-CONTEXT-VARIABLES",AB_package);
    def_bombout_clean_up_function(Qclear_computation_context_variables);
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    SET_SYMBOL_FUNCTION(Qclear_computation_context_variables,
	    STATIC_FUNCTION(clear_computation_context_variables,NIL,FALSE,
	    0,0));
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qsimulated_value = STATIC_SYMBOL("SIMULATED-VALUE",AB_package);
    Qcheck_for_circular_formula_paths_qm = 
	    STATIC_SYMBOL("CHECK-FOR-CIRCULAR-FORMULA-PATHS\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcheck_for_circular_formula_paths_qm,
	    Check_for_circular_formula_paths_qm);
    record_system_variable(Qcheck_for_circular_formula_paths_qm,
	    Qproc_utils,Nil,Qnil,Qnil,Qnil,Qnil);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    Qsimulator = STATIC_SYMBOL("SIMULATOR",AB_package);
    Qinference_engine = STATIC_SYMBOL("INFERENCE-ENGINE",AB_package);
    string_constant_48 = STATIC_STRING("Executing ~NF for ~NF.");
    string_constant_49 = STATIC_STRING("Executing formula for ~NF.");
    string_constant_50 = 
	    STATIC_STRING("Returning from execution of ~NF for ~NF.");
    string_constant_51 = 
	    STATIC_STRING("Returning from execution of the formula of ~NF.");
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_16 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)10L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)31L,(SI_Long)57344L);
    array_constant_17 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)16L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)21L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)26L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)27L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)28L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)32L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)33L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)35L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)39L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)35L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)36L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)37L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)46L,(SI_Long)39L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)47L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)30L,(SI_Long)22L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)31L,(SI_Long)57344L);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    list_constant_19 = STATIC_CONS(Qprocedure,Qnil);
    check_if_superior_classes_are_defined(Qmethod_declaration,
	    list_constant_19);
    string_constant_112 = STATIC_STRING("1m1m8v837Cy1l8t");
    string_constant_113 = 
	    STATIC_STRING("1y4z8r83-Fy83-Fy837Cy837Cy00001q1l8l1m8p83-ky1l83Cy1m83Dy53KyAlias as procedure-name\?1l83Uy1l83*-y000004z8r83-py83-py837Cy837Cy0");
    string_constant_114 = 
	    STATIC_STRING("0001q1l83Ey1l8l1l83Cy1m8p01l8z1m83Dy53*Qy[warning-message-level: (or default &lt;integer&gt;), ~\ntracing-message-level: (or defa");
    string_constant_115 = 
	    STATIC_STRING("ult &lt;integer&gt;), ~\nbreakpoint-level: (or default &lt;integer&gt;)]000004z8r83Z0y83Z0y837Cy837Cy00001o1l83Ey1l8l1l83Cy1m8p83");
    string_constant_116 = 
	    STATIC_STRING("Ky000004z8r8u8u837Cy837Cy01s8w9k3-My3-My1p1p83Jy1mkk1m3-Myk1m3-My3-My1mk3-My1n83jy1mww1m3iy3Ky1p83Jy1mw3iy1m3iy3iy1m3iy3uy1mw3uy");
    string_constant_117 = 
	    STATIC_STRING("1n83jy1m3cy3Qy1m3-Ay3cy1p83Jy1m3cy3-*y1m3-Ay3-*y1m3-Ay3-Ay1m3cy3-Ay03*dy3*dy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY clas");
    string_constant_118 = 
	    STATIC_STRING("s definition000004z8r833ky833ky837Cy837Cy00001q1m8p01l8o1l8l1l83Cy1l8z1m83Dy530+yThe name of a subclass of procedure-invocation ");
    string_constant_119 = 
	    STATIC_STRING("(or procedure-invocation ~\n       itself).  Within this procedure, the expression \"this ~\n       procedure-invocation\" will retu");
    string_constant_120 = 
	    STATIC_STRING("rn a unique instance of this class for ~\n       this execution of this procedure.000004z8r833ry833ry837Cy837Cy0q001p1m8p01l8o1l8");
    string_constant_121 = 
	    STATIC_STRING("l1l83Cy1l8z000004z8r834ny834ny837Cy837Cy083Py001p1m8p01l8o1l8l1l83Cy1l8z000004z8r835*y835*y837Cy837Cy00001o1l8o1l8l1l83Cy1m83Dy5");
    string_constant_122 = 
	    STATIC_STRING("3TyExport: integer, writable = false000004z8r835=y835=y837Cy837Cy00001o1l8o1l8l1l83Cy1m83Dy53jyExport list of type descriptors, ");
    string_constant_123 = 
	    STATIC_STRING("writable = false000004z8r836Cy836Cy837Cy837Cy00001o1l8o1l8l1l83Cy1m83Dy53jyExport list of type descriptors, writable = false0000");
    string_constant_124 = 
	    STATIC_STRING("04z8r836=y836=y837Cy837Cy00001o1l8o1l8l1l83Hy1m83Dy53byExport - debugging, process monitoring\?\?\?000004z8r834Qy834Qy837Cy837Cy000");
    string_constant_125 = 
	    STATIC_STRING("01r1m8p01l8o1l8l1l83Cy1l83-3y1l83-5y1m83Dy5zExport as text.000004z8r836-y836-y837Cy837Cy00001o1l8o1l8l1l83Cy1l83Uy000004z8r836*y");
    string_constant_126 = 
	    STATIC_STRING("836*y837Cy837Cy0k001o1l8o1l8l1l83Cy1m83Dy53cyAdd attribute-mimics for individual flags.00000");
    string_constant_127 = 
	    STATIC_STRING("13Cy8q1o837Cy1l83=Vy1m8v837Cy8t1p83-Fy08l1m8p83-ky83Cy1q83-py083Ey8l83Cy1m8p01q83Z0y083Ey8l83Cy1m8p83Ky1m8u1s8w9k3-My3-My1p1p83J");
    string_constant_128 = 
	    STATIC_STRING("y1mkk1m3-Myk1m3-My3-My1mk3-My1n83jy1mww1m3iy3Ky1p83Jy1mw3iy1m3iy3iy1m3iy3uy1mw3uy1n83jy1m3cy3Qy1m3-Ay3cy1p83Jy1m3cy3-*y1m3-Ay3-*");
    string_constant_129 = 
	    STATIC_STRING("y1m3-Ay3-Ay1m3cy3-Ay03*dy3*dy1q833ky01m8p08o8l83Cy1q833ryq1m8p08o8l83Cy1q834ny83Py1m8p08o8l83Cy1p835*y08o8l83Cy1p835=y08o8l83Cy1");
    string_constant_130 = 
	    STATIC_STRING("p836Cy08o8l83Cy1p836=y08o8l83Hy1s834Qy01m8p08o8l83Cy83-3y83-5y1q836-y08o8l83Cy83Uy1p836*yk8o8l83Cy");
    temp = regenerate_optimized_constant(string_constant_112);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(list(14,string_constant_113,
	    string_constant_114,string_constant_115,string_constant_116,
	    string_constant_117,string_constant_118,string_constant_119,
	    string_constant_120,string_constant_121,string_constant_122,
	    string_constant_123,string_constant_124,string_constant_125,
	    string_constant_126));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qmethod_declaration,list_constant_19,Nil,
	    temp,Nil,temp_1,list_constant_19,
	    regenerate_optimized_constant(LIST_4(string_constant_127,
	    string_constant_128,string_constant_129,string_constant_130)),Nil);
    Method_declaration_class_description = 
	    lookup_global_or_kb_specific_property_value(Qmethod_declaration,
	    Class_description_gkbprop);
    Qprocedure_method = STATIC_SYMBOL("PROCEDURE-METHOD",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    mutate_global_property(Qprocedure_method,CONS(Qmethod_declaration,
	    Kb_flag_when_specific_procedure_method_died),
	    Qsubstitute_class_and_kb_flags);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qinitialize_for_method_declaration = 
	    STATIC_SYMBOL("INITIALIZE-FOR-METHOD-DECLARATION",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_method_declaration,
	    STATIC_FUNCTION(initialize_for_method_declaration,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_method_declaration);
    set_get(Qmethod_declaration,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qmethod_declaration,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qnote_name_change_for_method_declaration = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-METHOD-DECLARATION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_method_declaration,
	    STATIC_FUNCTION(note_name_change_for_method_declaration,NIL,
	    FALSE,3,3));
    Qnote_name_change = STATIC_SYMBOL("NOTE-NAME-CHANGE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qnote_name_change_for_method_declaration);
    set_get(Qmethod_declaration,Qnote_name_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp_2 = CONS(Qmethod_declaration,temp);
    mutate_global_property(Qnote_name_change,temp_2,Qclasses_which_define);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    check_if_superior_classes_are_defined(Qab_method,list_constant_19);
    string_constant_131 = 
	    STATIC_STRING("1n1m8v834My1l8t1m83-Cy53=8yAttributes exported currently:\n<ul>\n<li>class of procedure invocation,\n<li>default procedure priority");
    string_constant_132 = 
	    STATIC_STRING(",\n<li>uninterrupted procedure execution limit,\n<li>text,\n<li>qualified name (instead of names)<br></ul>");
    string_constant_133 = 
	    STATIC_STRING("1o4z8r8u8u834My834My01s8w9k3-My3-My1p1p83Jy1mkk1m3-Myk1m3-My3-My1mk3-My1n83jy1mww1m3iy3Ky1n83jy1mw3iy1m3iy3uy1n83jy1m3cy3Qy1m3-A");
    string_constant_134 = 
	    STATIC_STRING("y3cy1n83jy1m3cy3-*y1m3-Ay3-Ay03*dy3*dy001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83YKy83YKy834My83");
    string_constant_135 = 
	    STATIC_STRING("4My00001r1l8o1l8l1l83Cy1l83Fy1m8p83YKy1l83*-y1m83Dy53Xyexport, writable = false, type string00008k4z8r83YJy83YJy834My834My00001p");
    string_constant_136 = 
	    STATIC_STRING("1l8o1l8l1l83Cy1l83*-y1m83Dy53kyexport, writable = false, type class-name (symbol)00008k4z8r83A5y83A5y834My834My00001q1l8o1l8l1l8");
    string_constant_137 = STATIC_STRING("3Cy1l8z1l83-5y1m8p83Ky00000");
    string_constant_138 = 
	    STATIC_STRING("1q8q1p834My1l83=Vy1m8v834My8t1m83-Cy53=8yAttributes exported currently:\n<ul>\n<li>class of procedure invocation,\n<li>default proc");
    string_constant_139 = 
	    STATIC_STRING("edure priority,\n<li>uninterrupted procedure execution limit,\n<li>text,\n<li>qualified name (instead of names)<br></ul>1m8u1s8w9k3");
    string_constant_140 = 
	    STATIC_STRING("-My3-My1p1p83Jy1mkk1m3-Myk1m3-My3-My1mk3-My1n83jy1mww1m3iy3Ky1n83jy1mw3iy1m3iy3uy1n83jy1m3cy3Qy1m3-Ay3cy1n83jy1m3cy3-*y1m3-Ay3-A");
    string_constant_141 = 
	    STATIC_STRING("y03*dy3*dy1t83YKy08o8l83Cy83Fy1m8p83YKy83*-y1m83Dy53Xyexport, writable = false, type string1r83YJy08o8l83Cy83*-y1m83Dy53kyexport");
    string_constant_142 = 
	    STATIC_STRING(", writable = false, type class-name (symbol)1s83A5y08o8l83Cy8z83-5y1m8p83Ky");
    temp = regenerate_optimized_constant(LIST_2(string_constant_131,
	    string_constant_132));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_133,
	    string_constant_134,string_constant_135,string_constant_136,
	    string_constant_137));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qab_method,list_constant_19,Nil,temp,Nil,
	    temp_1,list_constant_19,
	    regenerate_optimized_constant(LIST_5(string_constant_138,
	    string_constant_139,string_constant_140,string_constant_141,
	    string_constant_142)),Nil);
    Method_class_description = 
	    lookup_global_or_kb_specific_property_value(Qab_method,
	    Class_description_gkbprop);
    Qinvocation_locking_this_object = 
	    STATIC_SYMBOL("INVOCATION-LOCKING-THIS-OBJECT",AB_package);
    Klock_aquired = STATIC_SYMBOL("LOCK-AQUIRED",Pkeyword);
    Klock_held_by_thread = STATIC_SYMBOL("LOCK-HELD-BY-THREAD",Pkeyword);
    Qspecific_procedure_method = STATIC_SYMBOL("SPECIFIC-PROCEDURE-METHOD",
	    AB_package);
    mutate_global_property(Qspecific_procedure_method,CONS(Qab_method,
	    Kb_flag_when_specific_procedure_method_died),
	    Qsubstitute_class_and_kb_flags);
    Qinitialize_after_reading_for_method = 
	    STATIC_SYMBOL("INITIALIZE-AFTER-READING-FOR-METHOD",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_after_reading_for_method,
	    STATIC_FUNCTION(initialize_after_reading_for_method,NIL,FALSE,
	    1,1));
    Qinitialize_after_reading = STATIC_SYMBOL("INITIALIZE-AFTER-READING",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_after_reading_for_method);
    set_get(Qab_method,Qinitialize_after_reading,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize_after_reading),
	    Qclasses_which_define);
    temp_2 = CONS(Qab_method,temp);
    mutate_global_property(Qinitialize_after_reading,temp_2,
	    Qclasses_which_define);
    Qprocedure_method_name = STATIC_SYMBOL("PROCEDURE-METHOD-NAME",AB_package);
    Qqualified_name = STATIC_SYMBOL("QUALIFIED-NAME",AB_package);
    alias_slot_name(3,Qprocedure_method_name,Qqualified_name,Qab_method);
    Qcleanup_for_method = STATIC_SYMBOL("CLEANUP-FOR-METHOD",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_method,
	    STATIC_FUNCTION(cleanup_for_method,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_method);
    set_get(Qab_method,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qab_method,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qput_procedure_method_name = STATIC_SYMBOL("PUT-PROCEDURE-METHOD-NAME",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_procedure_method_name,
	    STATIC_FUNCTION(put_procedure_method_name,NIL,FALSE,3,3));
    mutate_global_property(Qprocedure_method_name,
	    SYMBOL_FUNCTION(Qput_procedure_method_name),Qslot_putter);
    Qprocedure_method_class = STATIC_SYMBOL("PROCEDURE-METHOD-CLASS",
	    AB_package);
    Qput_procedure_method_class = 
	    STATIC_SYMBOL("PUT-PROCEDURE-METHOD-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_procedure_method_class,
	    STATIC_FUNCTION(put_procedure_method_class,NIL,FALSE,3,3));
    mutate_global_property(Qprocedure_method_class,
	    SYMBOL_FUNCTION(Qput_procedure_method_class),Qslot_putter);
    string_constant_52 = STATIC_STRING("~(~nq~)");
    array_constant_21 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_procedure_method_name_from_slot = 
	    STATIC_SYMBOL("WRITE-PROCEDURE-METHOD-NAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_procedure_method_name_from_slot,
	    STATIC_FUNCTION(write_procedure_method_name_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qprocedure_method_name,
	    SYMBOL_FUNCTION(Qwrite_procedure_method_name_from_slot),
	    Qslot_value_writer);
    Qprocedure_methods_of_class = 
	    STATIC_SYMBOL("PROCEDURE-METHODS-OF-CLASS",AB_package);
    Kb_specific_property_names = CONS(Qprocedure_methods_of_class,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qprocedure_methods_of_class,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_gensym_tree_function = 
	    STATIC_SYMBOL("RECLAIM-GENSYM-TREE-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_gensym_tree_function,
	    STATIC_FUNCTION(reclaim_gensym_tree_function,NIL,FALSE,1,1));
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qprocedure_methods_of_class,
	    Qreclaim_gensym_tree_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Procedure_methods_of_class_kbprop = Qprocedure_methods_of_class;
    Qclasses_of_procedure_method = 
	    STATIC_SYMBOL("CLASSES-OF-PROCEDURE-METHOD",AB_package);
    Kb_specific_property_names = CONS(Qclasses_of_procedure_method,
	    Kb_specific_property_names);
    mutate_global_property(Qclasses_of_procedure_method,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    mutate_global_property(Qclasses_of_procedure_method,
	    Qreclaim_gensym_tree_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Classes_of_procedure_method_kbprop = Qclasses_of_procedure_method;
    array_constant_22 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)13L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)18L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)20L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)21L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)23L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)26L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)28L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)30L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)31L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)35L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)36L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)38L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)39L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)40L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)41L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)42L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)43L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)44L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)45L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)46L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)47L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)54L,(SI_Long)48L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)55L,(SI_Long)57344L);
    array_constant_23 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)18L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)19L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)20L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)21L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)22L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)30L,(SI_Long)23L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)31L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)26L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)31L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)32L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)34L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)35L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)39L,(SI_Long)57344L);
    array_constant_25 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)64L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)13L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)14L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)17L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)19L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)21L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)23L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)27L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)29L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)31L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)32L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)33L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)34L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)35L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)38L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)39L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)41L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)42L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)43L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)44L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)46L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)47L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)48L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)49L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)50L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)51L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)52L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)53L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)54L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)56L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)57L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)62L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)63L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)10L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)13L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)17L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)24L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)28L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)30L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)31L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)32L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)34L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)35L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)38L,(SI_Long)36L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)39L,(SI_Long)57344L);
    Qaction_method_reference_class = 
	    STATIC_SYMBOL("ACTION-METHOD-REFERENCE-CLASS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qaction_method_reference_class,
	    Action_method_reference_class);
    Qsystem_item = STATIC_SYMBOL("SYSTEM-ITEM",AB_package);
    SET_SYMBOL_VALUE(Qaction_method_reference_class,Qsystem_item);
    array_constant_27 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)56L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)16L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)18L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)24L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)30L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)33L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)34L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)35L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)36L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)37L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)38L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)39L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)41L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)42L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)43L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)44L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)45L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)46L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)54L,(SI_Long)47L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)55L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)16L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)18L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)25L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)31L,(SI_Long)57344L);
    Qsimulation_initial_value = STATIC_SYMBOL("SIMULATION-INITIAL-VALUE",
	    AB_package);
    Qembedded_rule_qm = STATIC_SYMBOL("EMBEDDED-RULE\?",AB_package);
    string_constant_53 = 
	    STATIC_STRING("For procedure ~NF, arg ~S, = ~NA, expected to be of type ~NT");
    string_constant_54 = 
	    STATIC_STRING("For procedure ~NF, arg ~S expected to be of type ~NT, not ~NT");
    string_constant_55 = 
	    STATIC_STRING("Procedure ~NF expects to be called with ~S arguments, but is declared to take ~S");
    Qcurrent_computation_instance = 
	    STATIC_SYMBOL("CURRENT-COMPUTATION-INSTANCE",AB_package);
    array_constant_29 = STATIC_ARRAY(list_constant_16,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)57344L);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_56 = STATIC_STRING(" of ");
    Qg2_defstruct_structure_name_inference_background_collection_g2_struct 
	    = STATIC_SYMBOL("INFERENCE-BACKGROUND-COLLECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_57 = 
	    STATIC_STRING(" has exceeded the warning limit for uninterrupted procedure execution!  ~\n       This procedure has been executing for ~a seconds.");
    string_constant_58 = 
	    STATIC_STRING("Uninterrupted procedure execution time limit exceeded!  This procedure ~\n     has executed for ~a seconds.");
    string_constant_59 = STATIC_STRING("Exiting execution of ~NF.");
}
